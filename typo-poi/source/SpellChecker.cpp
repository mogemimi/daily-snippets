// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "SpellChecker.h"
#include "EditDistance.h"
#include "StringHelper.h"
#include <cassert>
#include <cstdint>
#include <unordered_map>

namespace somera {
namespace {

uint32_t SignatureHashingFromAsciiAlphabet(const std::string& word)
{
    // NOTE:
    // '#' is number 0 to 9.
    // '@' is symbols and other characters.
    //
    //   ABCDEFGHIJKLMNOPQRSTUVWXYZ#@
    //   abcdefghijklmnopqrstuvwxyz#@
    // 0b0000000000000000000000000000

    // Example:
    //   Histogram of "Blade Runner"
    //
    //       *        *   *
    //   ** **      * *   *  *
    //   ABCDEFGHIJKLMNOPQRSTUVWXYZ#@
    //   abcdefghijklmnopqrstuvwxyz#@
    //
    //   Hash of "Blade Runner" from histogram
    //
    //   ABCDEFGHIJKLMNOPQRSTUVWXYZ#@
    //   abcdefghijklmnopqrstuvwxyz#@
    // 0b1101100000010100010010000000
#if 1
    constexpr int offsets[128] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 27, 26, 25, 
        24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 
        7, 6, 5, 4, 3, 2, 0, 0, 0, 0, 0, 0, 27, 26, 25, 24, 23, 
        22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 
        5, 4, 3, 2, 0, 0, 0, 0, 0
    };

    uint32_t hash = 0;
    for (auto & c : word) {
        if (0 <= c && c <= 127) {
            auto offset = offsets[c];
            hash |= (1 << offset);
        }
        else {
            hash |= (1 << 0);
        }
    }
#else
    constexpr int alphabetCount = 25;
    constexpr int alphabetOffset = 2;
    constexpr int numberOffset = 1;
    constexpr int symbolsOffset = 0;

    uint32_t hash = 0;
    for (auto & c : word) {
        if (65 <= c && c <= 90) {
            hash |= (1 << (alphabetCount - (c - 65) + alphabetOffset));
        }
        else if (97 <= c && c <= 122) {
            hash |= (1 << (alphabetCount - (c - 97) + alphabetOffset));
        }
        else if (48 <= c && c <= 57) {
            hash |= (1 << numberOffset);
        }
        else {
            hash |= (1 << symbolsOffset);
        }
    }
#endif
    return hash;
}

class SpellCheckerSignatureHashing final : public SpellChecker {
public:
    SpellCheckResult Suggest(const std::string& word);
    
    void AddWord(const std::string& word);
    
    void RemoveWord(const std::string& word);

private:
    std::unordered_map<uint32_t, std::vector<std::string>> hashedDictionary;
};

void SpellCheckerSignatureHashing::AddWord(const std::string& word)
{
    assert(!word.empty());

    auto signatureHash = SignatureHashingFromAsciiAlphabet(word);
    auto mapIter = hashedDictionary.find(signatureHash);
    if (mapIter == std::end(hashedDictionary)) {
        std::vector<std::string> dict;
        hashedDictionary.emplace(signatureHash, std::move(dict));
        mapIter = hashedDictionary.find(signatureHash);
    }
    assert(mapIter != std::end(hashedDictionary));
    
    auto & words = mapIter->second;
    auto wordsIter = std::lower_bound(std::begin(words), std::end(words), word);
    if ((wordsIter != std::end(words)) && (*wordsIter == word)) {
        // NOTE: The word already exists in a dictionary.
        return;
    }
    words.insert(wordsIter, word);
}

void SpellCheckerSignatureHashing::RemoveWord(const std::string& word)
{
    auto signatureHash = SignatureHashingFromAsciiAlphabet(word);
    auto mapIter = hashedDictionary.find(signatureHash);
    if (mapIter == std::end(hashedDictionary)) {
        return;
    }
    assert(mapIter != std::end(hashedDictionary));
    
    auto & words = mapIter->second;
    auto wordsIter = std::lower_bound(std::begin(words), std::end(words), word);
    if ((wordsIter != std::end(words)) && (*wordsIter == word)) {
        words.erase(wordsIter);
    }
}

size_t StringLength(const std::string& s)
{
    // TODO: This function is not supported UTF-8 strings.
    return s.size();
}

size_t ComputeGapSize(size_t a, size_t b)
{
    if (a > b) {
        assert((a - b) <= a);
        return a - b;
    }
    assert((b - a) <= b);
    return b - a;
}

void SpellCheckInternal(
    const std::string& input,
    const std::vector<std::string>& dictionary,
    std::vector<std::string> & suggestions,
    bool & exaxtMatching,
    std::size_t inputWordSize,
    std::size_t & gapSizeThreshold,
    double & similarityThreshold,
    int distanceThreshold)
{
    for (auto & word : dictionary) {
        const auto gapSize = ComputeGapSize(StringLength(word), inputWordSize);
        if (gapSize > gapSizeThreshold) {
            continue;
        }

        const auto similarity = EditDistance::closestMatchFuzzySimilarity(input, word, distanceThreshold);
        if (similarity == 1.0) {
            // exaxt matching
            suggestions.clear();
            suggestions.push_back(word);
            exaxtMatching = true;
            break;
        }
        else if (similarity >= similarityThreshold) {
            similarityThreshold = std::max(similarity, similarityThreshold);
            gapSizeThreshold = std::max<std::size_t>(gapSize, 1);
            assert(similarityThreshold <= 1.0);
            suggestions.push_back(word);
        }
    }
}

std::size_t ComputePrefixLength(const std::string& a, const std::string& b)
{
    const auto minSize = std::min(a.size(), b.size());
    std::size_t prefixLength = 0;
    for (std::size_t i = 0; i < minSize; ++i) {
        assert(i < a.size());
        assert(i < b.size());
        if (a[i] != b[i]) {
            break;
        }
        ++prefixLength;
    }
    return prefixLength;
}

std::size_t ComputeSurfixLength(const std::string& a, const std::string& b)
{
    const auto minSize = std::min(a.size(), b.size());
    std::size_t surfixLength = 0;
    for (std::size_t i = 1; i <= minSize; ++i) {
        assert(i <= a.size());
        assert(i <= b.size());
        if (a[a.size() - i] != b[b.size() - i]) {
            break;
        }
        ++surfixLength;
    }
    return surfixLength;
}

void SortSuggestions(const std::string& word, std::vector<std::string>& suggestions)
{
    std::sort(std::begin(suggestions), std::end(suggestions), [&](const std::string& a, const std::string& b) {
        const auto similarA = somera::EditDistance::closestMatchFuzzySimilarity(word, a);
        const auto similarB = somera::EditDistance::closestMatchFuzzySimilarity(word, b);
        if (similarA != similarB) {
            return similarA > similarB;
        }
        const auto distanceA = somera::EditDistance::levenshteinDistance_DynamicProgramming_ReplacementCost1(word, a);
        const auto distanceB = somera::EditDistance::levenshteinDistance_DynamicProgramming_ReplacementCost1(word, b);
        if (distanceA != distanceB) {
            return distanceA < distanceB;
        }
        const auto prefixA = ComputePrefixLength(word, a);
        const auto prefixB = ComputePrefixLength(word, b);
        if (prefixA != prefixB) {
            return prefixA > prefixB;
        }
        const auto gapA = ComputeGapSize(word.size(), a.size());
        const auto gapB = ComputeGapSize(word.size(), b.size());
        if (gapA != gapB) {
            return gapA < gapB;
        }
        const auto surfixA = ComputeSurfixLength(word, a);
        const auto surfixB = ComputeSurfixLength(word, b);
        return surfixA > surfixB;
    });
}

SpellCheckResult SpellCheck_SignatureHashinging_Internal(
    const std::string& input,
    const std::unordered_map<uint32_t, std::vector<std::string>>& hashedDictionary,
    const std::function<int(const std::string&, const std::string&)>& levenshteinDistance,
    const std::function<uint32_t(const std::string&)>& histogramHashing,
    const int maxHashLength)
{
    std::size_t gapSizeThreshold = 2;

    SpellCheckResult result;
    result.correctlySpelled = false;

    const auto inputHistogramHashing = histogramHashing(input);
    const auto inputWordSize = StringLength(input);

    const auto sizeAsDouble = static_cast<double>(inputWordSize);
    double similarityThreshold = std::max((sizeAsDouble - std::min(sizeAsDouble, 2.0)) / sizeAsDouble, 0.5);
    const auto distanceThreshold = std::min(static_cast<int>(input.size()), 10);

    for (int i = 0; i <= maxHashLength; ++i) {
        const uint32_t bitmask = ((static_cast<uint32_t>(1) << i) >> 1);
        const uint32_t xorBits = inputHistogramHashing ^ bitmask;
        
        auto iter = hashedDictionary.find(xorBits);
        if (iter == std::end(hashedDictionary)) {
            continue;
        }
        const auto& dictionary = iter->second;

        bool exactMatching = false;
        
        SpellCheckInternal(
            input,
            dictionary,
            result.suggestions,
            exactMatching,
            inputWordSize,
            gapSizeThreshold,
            similarityThreshold,
            distanceThreshold);

        if (exactMatching) {
            result.correctlySpelled = true;
            break;
        }
    }
    return result;
}

bool ExistWordSignatureHashingingInternal(
    const std::string& input,
    const std::unordered_map<uint32_t, std::vector<std::string>>& hashedDictionary)
{
    const auto histogramHashing = SignatureHashingFromAsciiAlphabet;
    const auto inputHistogramHashing = histogramHashing(input);

    auto iter = hashedDictionary.find(inputHistogramHashing);
    if (iter == std::end(hashedDictionary)) {
        return false;
    }
    const auto& dictionary = iter->second;

    for (auto & word : dictionary) {
        if ((input.size() == word.size()) && (input == word)) {
            // exaxt matching
            return true;
        }
    }
    return false;
}

SpellCheckResult SuggestInternal(
    const std::string& word,
    std::unordered_map<uint32_t, std::vector<std::string>> & hashedDictionary)
{
    return SpellCheck_SignatureHashinging_Internal(
        word,
        hashedDictionary,
        [](const std::string& a, const std::string& b) {
            return EditDistance::levenshteinDistance_ONDGreedyAlgorithm(a, b);
        },
        SignatureHashingFromAsciiAlphabet,
        28);
}

enum class LetterCase {
    LowerCase,
    UpperCase,
    UpperCamelCase,
};

LetterCase GetLetterCase(const std::string& word)
{
    ///@todo This function doesn't support UTF-8 string.
    bool isLowerCase = true;
    bool isUpperCase = true;
    bool isUpperCamelCase = true;
    if (word.empty() || (::isupper(word.front()) == 0)) {
        isUpperCamelCase = false;
    }
    for (auto c : word) {
        if (::islower(c) != 0) {
            isUpperCase = false;
        }
        if (::isupper(c) != 0) {
            isLowerCase = false;
        }
    }
    if (isLowerCase) {
        return LetterCase::LowerCase;
    }
    else if (isUpperCase) {
        return LetterCase::UpperCase;
    }
    else if (isUpperCamelCase) {
        return LetterCase::UpperCamelCase;
    }
    return LetterCase::LowerCase;
}

#if 0
void TestCase_GetLetterCase()
{
    assert(GetLetterCase("Word") == LetterCase::UpperCamelCase);
    assert(GetLetterCase("WORD") == LetterCase::UpperCase);
    assert(GetLetterCase("word") == LetterCase::LowerCase);
}
#endif

void TransformLetterCase(std::string & word, LetterCase letterCase)
{
    switch (letterCase) {
    case LetterCase::LowerCase:
        for (auto & c : word) {
            c = ::tolower(c);
        }
        break;
    case LetterCase::UpperCase:
        for (auto & c : word) {
            c = ::toupper(c);
        }
        break;
    case LetterCase::UpperCamelCase: {
        for (auto & c : word) {
            c = ::tolower(c);
        }
        if (!word.empty()) {
            auto & c = word.front();
            c = ::toupper(c);
        }
        break;
    }
    }
}

SpellCheckResult SuggestLetterCase(
    const std::string& word,
    std::unordered_map<uint32_t, std::vector<std::string>> & hashedDictionary)
{
    auto result = SuggestInternal(word, hashedDictionary);
    if (result.correctlySpelled) {
        return result;
    }
    
    auto letterCase = GetLetterCase(word);
    for (auto & suggestion : result.suggestions) {
        auto suggestionLetterCase = GetLetterCase(suggestion);
        if (suggestionLetterCase == LetterCase::LowerCase) {
            TransformLetterCase(suggestion, letterCase);
        }
    }
    return result;
}

template <typename T>
void ResizeSuggestions(T & suggestions)
{
    constexpr std::size_t maxSuggestionCount = 5;
    if (suggestions.size() > maxSuggestionCount) {
        suggestions.resize(maxSuggestionCount);
    }
}

SpellCheckResult SpellCheckerSignatureHashing::Suggest(const std::string& word)
{
    auto result = SuggestLetterCase(word, hashedDictionary);
    if (result.correctlySpelled) {
        return result;
    }

    SortSuggestions(word, result.suggestions);
    ResizeSuggestions(result.suggestions);

    {
        constexpr std::size_t prefixMinSize = 3;
        constexpr std::size_t suffixMinSize = 3;
        constexpr std::size_t minSize = 6;
        static_assert(minSize >= prefixMinSize + suffixMinSize, "");

        if ((word.size() < minSize) || (word.size() > 23)) {
            return result;
        }

        const auto end = word.size() - (suffixMinSize - 1);
        for (std::size_t separator = prefixMinSize; separator < end; ++separator) {
            const auto prefix = word.substr(0, separator);
            const auto suffix = word.substr(separator);

            if (!ExistWordSignatureHashingingInternal(StringHelper::toLower(prefix), hashedDictionary)) {
                continue;
            }
            if (!ExistWordSignatureHashingingInternal(StringHelper::toLower(suffix), hashedDictionary)) {
                continue;
            }
            result.suggestions.insert(std::begin(result.suggestions), prefix + " " + suffix);
        }
    }
    ResizeSuggestions(result.suggestions);
    return result;
}

} // unnamed namespace

std::shared_ptr<SpellChecker> SpellCheckerFactory::Create()
{
    return std::make_shared<SpellCheckerSignatureHashing>();
}

} // namespace somera
