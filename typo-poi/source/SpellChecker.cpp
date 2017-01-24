// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "SpellChecker.h"
#include "EditDistance.h"
#include "StringHelper.h"
#include "Optional.h"
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

struct SpellSuggestion {
    std::string word;
    Optional<double> similarity;
};

struct SpellCheckResultInternal {
    std::vector<SpellSuggestion> suggestions;

    ///@brief `true` if the word is correctly spelled; `false` otherwise.
    bool correctlySpelled;
};

void SpellCheckInternal(
    const std::string& input,
    const std::vector<std::string>& dictionary,
    std::vector<SpellSuggestion> & suggestions,
    bool & exactMatching,
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

        const auto similarity = closestMatchFuzzySimilarity(input, word, distanceThreshold);
        if (similarity == 1.0) {
            // exaxt matching
            SpellSuggestion suggestion;
            suggestion.word = word;
            suggestion.similarity = similarity;
            suggestions.insert(std::begin(suggestions), std::move(suggestion));
            exactMatching = true;
            break;
        }
        else if (similarity >= similarityThreshold) {
            similarityThreshold = std::max(similarity, similarityThreshold);
            gapSizeThreshold = std::max<std::size_t>(gapSize, 1);
            assert(similarityThreshold <= 1.0);
            SpellSuggestion suggestion;
            suggestion.word = word;
            suggestion.similarity = similarity;
            suggestions.push_back(std::move(suggestion));
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

void SortSuggestions(const std::string& word, std::vector<SpellSuggestion>& suggestions)
{
    for (auto & suggestion : suggestions) {
        if (!suggestion.similarity) {
            suggestion.similarity = somera::closestMatchFuzzySimilarity(word, suggestion.word);
        }
    }

    std::sort(std::begin(suggestions), std::end(suggestions), [&](const SpellSuggestion& a, const SpellSuggestion& b) {
        assert(a.similarity);
        assert(b.similarity);
        if (*a.similarity != *b.similarity) {
            return *a.similarity > *b.similarity;
        }
        const auto distanceA = somera::levenshteinDistance_DynamicProgramming_ReplacementCost1(word, a.word);
        const auto distanceB = somera::levenshteinDistance_DynamicProgramming_ReplacementCost1(word, b.word);
        if (distanceA != distanceB) {
            return distanceA < distanceB;
        }
        const auto prefixA = ComputePrefixLength(word, a.word);
        const auto prefixB = ComputePrefixLength(word, b.word);
        if (prefixA != prefixB) {
            return prefixA > prefixB;
        }
        const auto gapA = ComputeGapSize(word.size(), a.word.size());
        const auto gapB = ComputeGapSize(word.size(), b.word.size());
        if (gapA != gapB) {
            return gapA < gapB;
        }
        const auto surfixA = ComputeSurfixLength(word, a.word);
        const auto surfixB = ComputeSurfixLength(word, b.word);
        return surfixA > surfixB;
    });
}

SpellCheckResultInternal SpellCheck_SignatureHashinging_Internal(
    const std::string& input,
    const std::unordered_map<uint32_t, std::vector<std::string>>& hashedDictionary,
    const std::function<uint32_t(const std::string&)>& histogramHashing,
    const int maxHashLength,
    const int distanceThreshold)
{
    std::size_t gapSizeThreshold = 2;

    SpellCheckResultInternal result;
    result.correctlySpelled = false;

    const auto inputHistogramHashing = histogramHashing(input);
    const auto inputWordSize = StringLength(input);

    const auto sizeAsDouble = static_cast<double>(inputWordSize);
    double similarityThreshold = std::max((sizeAsDouble - std::min(sizeAsDouble, 2.0)) / sizeAsDouble, 0.5);

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

Optional<SpellSuggestion> ExistWordSignatureHashingingInternal(
    const std::string& input,
    const std::unordered_map<uint32_t, std::vector<std::string>>& hashedDictionary)
{
    std::size_t gapSizeThreshold = 1;
    const int distanceThreshold = 1;

    SpellCheckResultInternal result;
    result.correctlySpelled = false;

    const auto inputWordSize = StringLength(input);

    double similarityThreshold = 0.8;

    const auto histogramHashing = SignatureHashingFromAsciiAlphabet;
    const auto inputHistogramHashing = histogramHashing(input);

    auto iter = hashedDictionary.find(inputHistogramHashing);
    if (iter == std::end(hashedDictionary)) {
        return NullOpt;
    }
    const auto& dictionary = iter->second;

    Optional<SpellSuggestion> currentSuggestion;

    for (auto & word : dictionary) {
        const auto gapSize = ComputeGapSize(StringLength(word), inputWordSize);
        if (gapSize > gapSizeThreshold) {
            continue;
        }

        const auto similarity = closestMatchFuzzySimilarity(input, word, distanceThreshold);
        if (similarity == 1.0) {
            // exaxt matching
            SpellSuggestion suggestion;
            suggestion.word = word;
            suggestion.similarity = similarity;
            return suggestion;
        }
        else if (similarity >= similarityThreshold) {
            similarityThreshold = std::max(similarity, similarityThreshold);
            gapSizeThreshold = std::max<std::size_t>(gapSize, 1);
            assert(similarityThreshold <= 1.0);
            SpellSuggestion suggestion;
            suggestion.word = word;
            suggestion.similarity = similarity;
            currentSuggestion = std::move(suggestion);
        }
    }
    return currentSuggestion;
}

SpellCheckResultInternal SuggestInternal(
    const std::string& word,
    const std::unordered_map<uint32_t, std::vector<std::string>>& hashedDictionary)
{
    const auto distanceThreshold = std::min(static_cast<int>(word.size()), 10);
    return SpellCheck_SignatureHashinging_Internal(
        word,
        hashedDictionary,
        SignatureHashingFromAsciiAlphabet,
        28,
        distanceThreshold);
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

SpellCheckResultInternal SuggestLetterCase(
    const std::string& word,
    const std::unordered_map<uint32_t, std::vector<std::string>>& hashedDictionary)
{
    auto result = SuggestInternal(word, hashedDictionary);
    if (result.suggestions.empty()) {
        return result;
    }

    auto letterCase = GetLetterCase(word);
    for (auto & suggestion : result.suggestions) {
        auto suggestionLetterCase = GetLetterCase(suggestion.word);
        if (suggestionLetterCase == LetterCase::LowerCase) {
            TransformLetterCase(suggestion.word, letterCase);
        }
    }
    return result;
}

template <typename T>
void ResizeSuggestions(T & suggestions, std::size_t elementCount)
{
    if (suggestions.size() > elementCount) {
        suggestions.resize(elementCount);
    }
}

void SeparateWords(
    const std::string& word,
    const std::unordered_map<uint32_t, std::vector<std::string>>& hashedDictionary,
    std::vector<SpellSuggestion> & suggestions)
{
    constexpr std::size_t prefixMinSize = 2;
    constexpr std::size_t suffixMinSize = 2;
    constexpr std::size_t minSize = 6;
    static_assert(minSize >= prefixMinSize + suffixMinSize, "");

    if ((word.size() < minSize) || (word.size() > 23)) {
        return;
    }

    double maxSimilarity = 0.75;

    const auto end = word.size() - (suffixMinSize - 1);
    for (std::size_t separator = prefixMinSize; separator < end; ++separator) {
        const auto prefix = word.substr(0, separator);
        const auto suffix = word.substr(separator);

        auto prefixSuggestion = ExistWordSignatureHashingingInternal(prefix, hashedDictionary);
        if (!prefixSuggestion) {
            continue;
        }
        auto suffixSuggestion = ExistWordSignatureHashingingInternal(suffix, hashedDictionary);
        if (!suffixSuggestion) {
            continue;
        }

        assert(prefixSuggestion);
        assert(suffixSuggestion);
        assert(prefixSuggestion->similarity);
        assert(suffixSuggestion->similarity);

        auto similarity = (*prefixSuggestion->similarity + *suffixSuggestion->similarity) / 2.0;
        if (similarity < maxSimilarity) {
            continue;
        }
        maxSimilarity = similarity;

        {
            auto letterCase = GetLetterCase(prefix);
            auto suggestionLetterCase = GetLetterCase(prefixSuggestion->word);
            if (suggestionLetterCase == LetterCase::LowerCase) {
                TransformLetterCase(prefixSuggestion->word, letterCase);
            }
        }
        {
            auto letterCase = GetLetterCase(suffix);
            auto suggestionLetterCase = GetLetterCase(suffixSuggestion->word);
            if (suggestionLetterCase == LetterCase::LowerCase) {
                TransformLetterCase(suffixSuggestion->word, letterCase);
            }
        }

        auto concatWithoutSpace = prefixSuggestion->word + suffixSuggestion->word;
        auto found = std::find_if(std::begin(suggestions), std::end(suggestions), [&](const SpellSuggestion& s) {
            return s.word == concatWithoutSpace;
        });
        if (found != std::end(suggestions)) {
            // NOTE: "accept able" and "acceptable" are duplication.
            continue;
        }

        SpellSuggestion result;
        result.word = prefixSuggestion->word + " " + suffixSuggestion->word;

        suggestions.push_back(std::move(result));
    }
}

SpellCheckResult ConvertToSpellCheckResult(SpellCheckResultInternal& spellCheck)
{
    SpellCheckResult result;
    result.correctlySpelled = spellCheck.correctlySpelled;
    for (auto & suggestion : spellCheck.suggestions) {
        result.suggestions.push_back(suggestion.word);
    }
    return result;
}

enum class CharacterType {
    Segmenter,
    Lowercase,
    Uppercase,
};

CharacterType getCharaterType(char32_t c)
{
    ///@todo Support for other Unicode characters.
    if (u'A' <= c && c <= u'Z') {
        return CharacterType::Uppercase;
    }
    if (u'a' <= c && c <= u'z') {
        return CharacterType::Lowercase;
    }
    if (u'0' <= c && c <= u'9') {
        return CharacterType::Segmenter;
    }
    return CharacterType::Segmenter;
}

struct PartOfIdentifier {
    std::string word;
    bool isSegmenter;
};

std::vector<PartOfIdentifier> parseIdentifier(const std::string& text)
{
    std::vector<PartOfIdentifier> words;
    std::string wordBuffer;

    auto flush = [&](bool isSegmenter) {
        PartOfIdentifier partOfIdentifier;
        partOfIdentifier.word = wordBuffer;
        partOfIdentifier.isSegmenter = isSegmenter;
        words.push_back(std::move(partOfIdentifier));
        wordBuffer.clear();
    };

    CharacterType startType = CharacterType::Segmenter;

    for (auto iter = std::begin(text); iter != std::end(text); ++iter) {
        const auto c = *iter;
        if (wordBuffer.empty()) {
            wordBuffer += c;
            startType = getCharaterType(c);
            continue;
        }

        assert(!wordBuffer.empty());
        const auto type = getCharaterType(c);

        if (startType == CharacterType::Segmenter) {
            if (type == CharacterType::Segmenter) {
                wordBuffer += c;
                continue;
            }
            else {
                flush(true);
                wordBuffer += c;
                startType = type;
                continue;
            }
        }
        else if (startType == CharacterType::Uppercase) {
            if (type == CharacterType::Lowercase) {
                wordBuffer += c;
                continue;
            }
            else if (type == CharacterType::Uppercase) {
                if (getCharaterType(wordBuffer.back()) == CharacterType::Lowercase) {
                    assert(startType == CharacterType::Uppercase);
                    assert(type == CharacterType::Uppercase);
                    flush(false);
                    wordBuffer += c;
                    startType = type;
                    continue;
                }
            }
            else {
                flush(false);
                wordBuffer += c;
                startType = type;
                continue;
            }
        }

        if (type != getCharaterType(wordBuffer.back())) {
            flush(startType == CharacterType::Segmenter);
            wordBuffer += c;
            startType = type;
            continue;
        }
        wordBuffer += c;
    }

    if (!wordBuffer.empty()) {
        flush(startType == CharacterType::Segmenter);
    }
    return words;
}

void ParseIdentifier(
    const std::string& word,
    const std::unordered_map<uint32_t, std::vector<std::string>>& hashedDictionary,
    SpellCheckResultInternal & result)
{
    bool exactMatching = true;
    bool misspellingFound = false;

    auto parseResult = parseIdentifier(word);
    if (parseResult.size() <= 1) {
        return;
    }

    std::vector<std::string> concatSuggestions;
    auto concatnate = [&](const std::string& w) {
        if (concatSuggestions.empty()) {
            concatSuggestions.push_back(w);
            return;
        }
        for (auto & concatString : concatSuggestions) {
            concatString += w;
        }
    };

    for (auto & p : parseResult) {
        if (p.isSegmenter) {
            concatnate(p.word);
            continue;
        }
        auto result1 = SuggestLetterCase(p.word, hashedDictionary);
        if (result1.correctlySpelled) {
            concatnate(p.word);
            misspellingFound = true;
            continue;
        }
        exactMatching = false;
        if (result1.suggestions.empty()) {
            concatnate(p.word);
            continue;
        }

        misspellingFound = true;
        SortSuggestions(p.word, result1.suggestions);
        ResizeSuggestions(result1.suggestions, 2);

        // NOTE: Generating combinations
        std::vector<std::string> tempSuggestions;
        std::swap(concatSuggestions, tempSuggestions);
        if (tempSuggestions.empty()) {
            tempSuggestions.push_back("");
        }
        for (auto & cs : tempSuggestions) {
            for (auto & ss : result1.suggestions) {
                concatSuggestions.push_back(cs + ss.word);
            }
        }
    }

    if (!misspellingFound) {
        return;
    }

    for (auto & cs : concatSuggestions) {
        SpellSuggestion suggestion;
        suggestion.word = cs;
        result.suggestions.push_back(std::move(suggestion));
    }
    result.correctlySpelled = exactMatching;
}

SpellCheckResult SpellCheckerSignatureHashing::Suggest(const std::string& word)
{
    constexpr std::size_t maxSuggestions = 8;

    auto result = SuggestLetterCase(word, hashedDictionary);
    if (result.correctlySpelled) {
        SortSuggestions(word, result.suggestions);
        ResizeSuggestions(result.suggestions, maxSuggestions);
        return ConvertToSpellCheckResult(result);
    }

    ParseIdentifier(word, hashedDictionary, result);

    if (result.correctlySpelled) {
        SortSuggestions(word, result.suggestions);
        ResizeSuggestions(result.suggestions, maxSuggestions);
        return ConvertToSpellCheckResult(result);
    }

    SeparateWords(word, hashedDictionary, result.suggestions);

    SortSuggestions(word, result.suggestions);
    ResizeSuggestions(result.suggestions, maxSuggestions);

    return ConvertToSpellCheckResult(result);
}

} // unnamed namespace

std::shared_ptr<SpellChecker> SpellCheckerFactory::Create()
{
    return std::make_shared<SpellCheckerSignatureHashing>();
}

} // namespace somera
