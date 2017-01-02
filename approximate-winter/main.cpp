// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#include "EditDistance.h"
#include "WordDiff.h"
#include "WordSegmenter.h"
#include "SpellChecker.h"
#include "SpellCheck.h"
#include "somera/CommandLineParser.h"
#include "somera/FileSystem.h"
#include "somera/Optional.h"
#include "somera/StringHelper.h"
#include <iostream>
#include <fstream>
#include <array>
#include <unordered_map>

#include <iomanip>

using somera::CommandLineParser;
using somera::Optional;
using somera::NullOpt;
namespace StringHelper = somera::StringHelper;

namespace {

void SetupCommandLineParser(CommandLineParser & parser)
{
    using Type = somera::CommandLineArgumentType;
    parser.setUsageText("approximate-winter [options ...] [C/C++ file ...]");
    parser.addArgument("-h", Type::Flag, "Display available options");
    parser.addArgument("-help", Type::Flag, "Display available options");
    parser.addArgument("-v", Type::Flag, "Display version");
    parser.addArgument("-dict", Type::JoinedOrSeparate, "Dictionary file path");
    parser.addArgument("-unittest", Type::JoinedOrSeparate, "Run unit tests");
}

int SizeHash(const std::string& word)
{
    return static_cast<int>(word.size());
}

uint32_t HistogramHashing_Alphabet(const std::string& word)
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

uint32_t HistogramHashing_CyclicN(const std::string& word, uint32_t bitCount)
{
    uint32_t hash = 0;
    for (auto & c : word) {
        hash |= (1 << (static_cast<uint32_t>(c) % bitCount));
    }
    return hash;
}

uint32_t HistogramHashing_Cyclic32(const std::string& word)
{
    return HistogramHashing_CyclicN(word, 32);
}

uint32_t HistogramHashing_Cyclic16(const std::string& word)
{
    return HistogramHashing_CyclicN(word, 16);
}

uint32_t HistogramHashing_Cyclic8(const std::string& word)
{
    return HistogramHashing_CyclicN(word, 8);
}

uint32_t HistogramHashing_Accumulate(const std::string& word)
{
    uint32_t hash = 0;
    for (auto & c : word) {
        hash += static_cast<uint32_t>(c);
    }
    return hash;
}

void TestCase_HistogramHashing()
{
    auto HistogramHashing = HistogramHashing_Alphabet;

    // NOTE:
    //       ABCDEFGHIJKLMNOPQRSTUVWXYZ#@
    //       abcdefghijklmnopqrstuvwxyz#@
    assert(0b0000000000000000000000000000 == HistogramHashing(""));
    assert(0b1000000000000000000000000000 == HistogramHashing("a"));
    assert(0b1000000000000000000000000000 == HistogramHashing("A"));
    assert(0b1000000000000000000000000000 == HistogramHashing("aA"));
    assert(0b1000000000000000000000000000 == HistogramHashing("Aa"));
    assert(0b1000000000000000000000000000 == HistogramHashing("aa"));
    assert(0b1000000000000000000000000000 == HistogramHashing("AA"));
    assert(0b1111111000000000000000011100 == HistogramHashing("ABCDEFGxyz"));
    assert(0b0000000000000011100000000010 == HistogramHashing("OPQ42"));
    assert(0b0001000000000110000100000001 == HistogramHashing("Don't"));
    assert(0b1000000000000000000000000000 == HistogramHashing("A"));
    assert(0b0100000000000000000000000000 == HistogramHashing("B"));
    assert(0b0010000000000000000000000000 == HistogramHashing("C"));
    assert(0b0001000000000000000000000000 == HistogramHashing("D"));
    assert(0b0000100000000000000000000000 == HistogramHashing("E"));
    assert(0b0000010000000000000000000000 == HistogramHashing("F"));
    assert(0b0000001000000000000000000000 == HistogramHashing("G"));
    assert(0b0000000100000000000000000000 == HistogramHashing("H"));
}

void SpellCheck_Internal(
    const std::string& input,
    const std::vector<std::string>& dictionary,
    std::vector<std::string> & corrections,
    bool & exaxtMatching,
    const std::function<int(const std::string&, const std::string&)>& levenshteinDistance,
    int inputHash,
    int threshold)
{
    for (auto & word : dictionary) {
#if 0
        const auto wordHash = SizeHash(word);
        if (std::abs(wordHash - inputHash) >= threshold) {
            continue;
        }
#endif
        auto distance = levenshteinDistance(input, word);
        if (distance == 0) {
            // exaxt matching
            corrections.clear();
            corrections.push_back(word);
            exaxtMatching = true;
            break;
        }
        else if (distance < threshold) {
            corrections.push_back(word);
        }
    }
}

std::vector<std::string> SpellCheck_Innocent(
    const std::string& input,
    const std::vector<std::string>& dictionary)
{
    const auto threshold = 3;
    std::vector<std::string> corrections;
    
    for (auto & word : dictionary) {
        auto func = somera::EditDistance::levenshteinDistance_ONDGreedyAlgorithm;
        auto distance = func(input, word);
        if (distance == 0) {
            // exaxt matching
            corrections.clear();
            corrections.push_back(word);
            break;
        }
        else if (distance < threshold) {
            corrections.push_back(word);
        }
    }
    return corrections;
}

struct SearchResult {
    std::vector<std::string> corrections;
    bool exactMatching;
};

SearchResult SpellCheck_HistogramHashinging_Internal(
    const std::string& input,
    const std::unordered_map<uint32_t, std::vector<std::string>>& hashedDictionary,
    const std::function<int(const std::string&, const std::string&)>& levenshteinDistance,
    const std::function<uint32_t(const std::string&)>& histogramHashing,
    const int maxHashLength)
{
    const auto inputSizeHash = SizeHash(input);
    const auto threshold = 3;
    
    SearchResult result;
    result.exactMatching = false;

    const auto inputHistogramHashing = histogramHashing(input);

    for (int i = 0; i <= maxHashLength; ++i) {
        const uint32_t bitmask = ((static_cast<uint32_t>(1) << i) >> 1);
        const uint32_t xorBits = inputHistogramHashing ^ bitmask;
        
        auto iter = hashedDictionary.find(xorBits);
        if (iter == std::end(hashedDictionary)) {
            continue;
        }
        const auto& dictionary = iter->second;

        bool exactMatching = false;
        SpellCheck_Internal(
            input,
            dictionary,
            result.corrections,
            exactMatching,
            levenshteinDistance,
            inputSizeHash,
            threshold);
        if (exactMatching) {
            result.exactMatching = true;
            break;
        }
    }
    return result;
}

std::vector<std::string> SpellCheck_HistogramHashinging(
    const std::string& input,
    const std::unordered_map<uint32_t, std::vector<std::string>>& hashedDictionary)
{
    return SpellCheck_HistogramHashinging_Internal(
        input,
        hashedDictionary,
        somera::EditDistance::levenshteinDistance_ONDGreedyAlgorithm,
        HistogramHashing_Alphabet,
        28).corrections;
}

std::vector<std::string> SpellCheck_HistogramHashinging_ONDThreshold(
    const std::string& input,
    const std::unordered_map<uint32_t, std::vector<std::string>>& hashedDictionary)
{
    const auto threshold = 3;
    return SpellCheck_HistogramHashinging_Internal(
        input,
        hashedDictionary,
        [threshold](const std::string& a, const std::string& b) {
            return somera::EditDistance::levenshteinDistance_ONDGreedyAlgorithm_Threshold(a, b, threshold);
        },
        HistogramHashing_Alphabet,
        28).corrections;
}

std::vector<std::string> SpellCheck_HistogramHashinging_ONDThreshold_Cyclic32(
    const std::string& input,
    const std::unordered_map<uint32_t, std::vector<std::string>>& hashedDictionary)
{
    const auto threshold = 3;
    return SpellCheck_HistogramHashinging_Internal(
        input,
        hashedDictionary,
        [threshold](const std::string& a, const std::string& b) {
            return somera::EditDistance::levenshteinDistance_ONDGreedyAlgorithm_Threshold(a, b, threshold);
        },
        HistogramHashing_Cyclic32,
        32).corrections;
}

std::vector<std::string> SpellCheck_HistogramHashinging_ONDThreshold_Cyclic16(
    const std::string& input,
    const std::unordered_map<uint32_t, std::vector<std::string>>& hashedDictionary)
{
    const auto threshold = 3;
    return SpellCheck_HistogramHashinging_Internal(
        input,
        hashedDictionary,
        [threshold](const std::string& a, const std::string& b) {
            return somera::EditDistance::levenshteinDistance_ONDGreedyAlgorithm_Threshold(a, b, threshold);
        },
        HistogramHashing_Cyclic16,
        16).corrections;
}

std::vector<std::string> SpellCheck_HistogramHashinging_ONDThreshold_Cyclic8(
    const std::string& input,
    const std::unordered_map<uint32_t, std::vector<std::string>>& hashedDictionary)
{
    const auto threshold = 3;
    return SpellCheck_HistogramHashinging_Internal(
        input,
        hashedDictionary,
        [threshold](const std::string& a, const std::string& b) {
            return somera::EditDistance::levenshteinDistance_ONDGreedyAlgorithm_Threshold(a, b, threshold);
        },
        HistogramHashing_Cyclic8,
        8).corrections;
}

std::vector<std::string> SpellCheck_AccumulateHashing(
    const std::string& input,
    const std::unordered_map<uint32_t, std::vector<std::string>>& hashedDictionary)
{
    const auto inputSizeHash = SizeHash(input);
    const auto threshold = 3;
    
    auto levenshteinDistance = [threshold](const std::string& a, const std::string& b) {
        return somera::EditDistance::levenshteinDistance_ONDGreedyAlgorithm_Threshold(a, b, threshold);
    };
    
    std::vector<std::string> corrections;
    
    const uint32_t searchRange = 128;
    const auto inputHistogramHashing = HistogramHashing_Accumulate(input);

    std::vector<uint32_t> hashes;
    for (uint32_t i = 0; i <= searchRange; ++i) {
        for (int k = 0; k < 2; ++k) {
            uint32_t hash = 0;
            if (k == 0) {
                hash = inputHistogramHashing + i;
                assert(inputHistogramHashing <= hash);
            }
            else {
                if (i == 0) {
                    hash = 0;
                }
                else if (inputHistogramHashing > i) {
                    hash = inputHistogramHashing - i;
                    assert(inputHistogramHashing >= hash);
                }
                else {
                    hash = 0;
                }
            }
            if (hash == 0) {
                continue;
            }
            hashes.push_back(hash);
        }
    }

    for (auto hash : hashes) {
        auto iter = hashedDictionary.find(hash);
        if (iter == std::end(hashedDictionary)) {
            continue;
        }
        const auto& dictionary = iter->second;

        bool exactMatching = false;
        SpellCheck_Internal(
            input,
            dictionary,
            corrections,
            exactMatching,
            levenshteinDistance,
            inputSizeHash,
            threshold);
        if (exactMatching) {
            break;
        }
    }
    return corrections;
}

std::vector<std::string> SpellCheck_SizeHashing(
    const std::string& input,
    const std::unordered_map<int, std::vector<std::string>>& hashedDictionary)
{
    const auto inputSizeHash = SizeHash(input);
    const auto threshold = 3;
    
    auto levenshteinDistance = [threshold](const std::string& a, const std::string& b) {
        return somera::EditDistance::levenshteinDistance_ONDGreedyAlgorithm_Threshold(a, b, threshold);
    };
    
    std::vector<std::string> corrections;

    const int searchRange = 1;

    std::vector<int> hashes;
    for (int i = 0; i <= searchRange; ++i) {
        for (int k = 0; k < 2; ++k) {
            int hash = 0;
            if (k == 0) {
                hash = inputSizeHash + i;
                assert(inputSizeHash <= hash);
            }
            else {
                if (i == 0) {
                    hash = 0;
                }
                else if (inputSizeHash > i) {
                    hash = inputSizeHash - i;
                    assert(inputSizeHash >= hash);
                }
                else {
                    hash = 0;
                }
            }
            if (hash == 0) {
                continue;
            }
            hashes.push_back(hash);
        }
    }

    for (auto hash : hashes) {
        auto iter = hashedDictionary.find(hash);
        if (iter == std::end(hashedDictionary)) {
            continue;
        }
        const auto& dictionary = iter->second;

        bool exactMatching = false;
        SpellCheck_Internal(
            input,
            dictionary,
            corrections,
            exactMatching,
            levenshteinDistance,
            inputSizeHash,
            threshold);
        if (exactMatching) {
            break;
        }
    }
    return corrections;
}

std::vector<std::string> SpellCheck_SizeAndHistogram(
    const std::string& input,
    const std::unordered_map<int, std::unordered_map<uint32_t, std::vector<std::string>>>& hashedDictionary2)
{
    const auto inputSizeHash = SizeHash(input);

    std::vector<std::string> corrections;

    const int searchRange = 1;

    std::vector<int> hashes;
    for (int i = 0; i <= searchRange; ++i) {
        for (int k = 0; k < 2; ++k) {
            int hash = 0;
            if (k == 0) {
                hash = inputSizeHash + i;
                assert(inputSizeHash <= hash);
            }
            else {
                if (i == 0) {
                    hash = 0;
                }
                else if (inputSizeHash > i) {
                    hash = inputSizeHash - i;
                    assert(inputSizeHash >= hash);
                }
                else {
                    hash = 0;
                }
            }
            if (hash == 0) {
                continue;
            }
            hashes.push_back(hash);
        }
    }

    for (auto hash : hashes) {
        auto iter = hashedDictionary2.find(hash);
        if (iter == std::end(hashedDictionary2)) {
            continue;
        }
        const auto& hashedDictionary = iter->second;

        auto result = SpellCheck_HistogramHashinging_Internal(
            input,
            hashedDictionary,
            somera::EditDistance::levenshteinDistance_ONDGreedyAlgorithm,
            HistogramHashing_Alphabet,
            28);

        if (result.exactMatching) {
            corrections = std::move(result.corrections);
            break;
        }
        
        // NOTE: merging
        for (auto & c : result.corrections) {
            corrections.push_back(std::move(c));
        }
    }
    return corrections;
}

template <typename SpellCheckFunc, typename Dictionary>
void Print(
    const SpellCheckFunc& spellCheck,
    const std::string& inputWord,
    const Dictionary& dictionary)
{
    auto corrections = spellCheck(inputWord, dictionary);
    if (corrections.empty()) {
        std::cout << "'" << inputWord << "' is not found." << std::endl;
        return;
    }

    if (corrections.size() == 1) {
        auto distance = somera::EditDistance::levenshteinDistance_ONDGreedyAlgorithm(inputWord, corrections.front());
        if (distance == 0) {
            std::cout << "'" << inputWord << "' is found. (exact match)" << std::endl;
            return;
        }
    }

    std::stable_sort(std::begin(corrections), std::end(corrections), [&](const std::string& a, const std::string& b) {
        auto similarA = somera::EditDistance::closestMatchFuzzySimilarity(inputWord, a);
        auto similarB = somera::EditDistance::closestMatchFuzzySimilarity(inputWord, b);
        return similarA >= similarB;
    });

    std::cout << "'" << inputWord << "' Did you mean {";
    bool comma = false;
    for (auto & word : corrections) {
        if (comma) {
            std::cout << ", ";
        }
        std::cout << word;
        comma = true;
    }
    std::cout << "}" << std::endl;
}

template <typename SpellChecker>
void Print(
    const SpellChecker& spellChecker,
    const std::string& word)
{
    auto result = spellChecker->Suggest(word);
    if (result.correctlySpelled) {
        std::cout << "'" << word << "' is found. (exact match)" << std::endl;
        return;
    }
    if (result.suggestions.empty()) {
        std::cout << "'" << word << "' is not found." << std::endl;
        return;
    }

    auto & suggestions = result.suggestions;

    std::cout << "'" << word << "' Did you mean {";
    bool comma = false;
    for (auto & suggestion : suggestions) {
        if (comma) {
            std::cout << ", ";
        }
        std::cout << suggestion;
        comma = true;
    }
    std::cout << "}" << std::endl;
}

void ReadDictionaryFile(
    const std::string& path,
    const std::function<void(const std::string&)>& callback)
{
    std::error_code errorCode;
    const auto fileSize = somera::FileSystem::getFileSize(path, errorCode);

    if (errorCode) {
        std::cerr << "error: Cannot found the file. " << path << std::endl;
        return;
    }
    if (fileSize >= std::numeric_limits<int32_t>::max()) {
        // TODO: We cannot read a file larger than 2GB.
        std::cerr << "error: File is too large to read. " << path << std::endl;
        return;
    }

    std::ifstream input(path, std::ios::binary);
    if (!input) {
        return;
    }

    std::istreambuf_iterator<char> start(input);
    std::istreambuf_iterator<char> end;

    std::string word;
    for (; start != end; ++start) {
        auto c = *start;
        if (c == '\r' || c == '\n' || c == '\0') {
            if (!word.empty()) {
                callback(word);
            }
            word.clear();
            continue;
        }
        word += c;
    }
    if (!word.empty()) {
        callback(word);
    }
}

template <class Function>
void measurePerformanceTime(Function f)
{
    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;
    using std::chrono::nanoseconds;
    using std::chrono::duration_cast;

	auto start = high_resolution_clock::now();

    f();

	auto end = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(end - start);

	std::cout
        << "Measured time (ns) : " << duration.count() << " ns" << std::endl;
    std::cout
        << "Measured time (sec): "
        << duration_cast<std::chrono::duration<double>>(end - start).count()
        << " seconds" << std::endl;
}

void PrintLetterFrequency(const std::vector<std::string>& dictionary)
{
    std::map<char, int> counts;

    int maxCount = 0;
    for (auto & word : dictionary) {
        for (auto & c : word) {
            auto iter = counts.find(c);
            if (iter == std::end(counts)) {
                counts.emplace(c, 0);
                continue;
            }
            ++iter->second;
            maxCount = std::max(maxCount, iter->second);
        }
    }

    for (auto & pair : counts) {
        auto character = pair.first;
        auto count = pair.second;
        std::cout << character << ": " << count << std::endl;
    }

    // NOTE: https://en.wikipedia.org/wiki/Letter_frequency
    std::vector<char> characters;
    for (char c = 'a'; c <= 'z'; ++c) {
        characters.push_back(c);
        auto iter = counts.find(c);
        if (iter == std::end(counts)) {
            counts.emplace(c, 0);
        }
    }
    std::stable_sort(std::begin(characters), std::end(characters), [&](char a, char b) {
        return counts[a] < counts[b];
    });

    std::cout << "characters: ";
    for (auto & c : characters) {
        std::cout << c;
    }
    std::cout << std::endl;

    std::array<int, 128> offsets;
    constexpr int alphabetCount = 26;
    constexpr int maxOffset = (alphabetCount + 2) - 1;
    for (char c = 0; c >= 0 && c <= 127; ++c) {
        assert('A' < 'Z');
        assert('a' < 'z');
        assert('0' < '9');
        if ('A' <= c && c <= 'Z') {
            assert('a' > 'A');
            auto lowerCase = c + ('a' - 'A');
            auto iter = std::find(std::begin(characters), std::end(characters), lowerCase);
            assert(iter != std::end(characters));
            auto index = std::distance(std::begin(characters), iter);
            offsets[c] = maxOffset - static_cast<int>(index);
        }
        else if ('a' <= c && c <= 'z') {
            auto iter = std::find(std::begin(characters), std::end(characters), c);
            assert(iter != std::end(characters));
            auto index = std::distance(std::begin(characters), iter);
            offsets[c] = maxOffset - static_cast<int>(index);
        }
        else if ('0' <= c && c <= '9') {
            offsets[c] = 1;
        }
        else {
            offsets[c] = 0;
        }
        assert(0 <= offsets[c] && offsets[c] <= maxOffset);
    }

    std::cout << "std::array<int, 128> offsets = {\n";
    bool comma = false;
    int linebreakCount = 0;
    for (auto & offset : offsets) {
        if (comma) {
            std::cout << ", ";
        }
        if (linebreakCount > 16) {
            std::cout << "\n";
            linebreakCount = 0;
        }
        std::cout << offset;
        comma = true;
        ++linebreakCount;
    }
    std::cout << "\n};" << std::endl;
}

void TestCase_LCS()
{
    auto lcs = somera::EditDistance::computeLCSLength_DynamicProgramming;
    assert(lcs("", "") == 0);
    assert(lcs("A", "") == 0);
    assert(lcs("", "A") == 0);
    assert(lcs("A", "A") == 1);
    assert(lcs("AG", "GA") == 1);
    assert(lcs("AA", "AA") == 2);
    assert(lcs("AGA", "GAA") == 2);
    assert(lcs("AGCAT", "AGCAT") == 5);
    assert(lcs("AAAAAGC", "AAAAA") == 5);
    assert(lcs("AAAAA", "GCAAAAA") == 5);
    assert(lcs("GCT", "AAAAAA") == 0);
    assert(lcs("AAGGCCTTAGCT", "AAGGCCAGT") == 9);
    assert(lcs("AAGGCCTTAGCT", "AGCTAAGGCCAGCAAGGTT") == 10);
}

void TestCase_DPLinearSpace()
{
    auto distance = somera::EditDistance::levenshteinDistance_DynamicProgramming_LinearSpace;
    assert(distance("", "") == 0);
    assert(distance("A", "") == 1);
    assert(distance("", "A") == 1);
    assert(distance("A", "A") == 0);
    assert(distance("AG", "GA") == 2);
    assert(distance("AA", "AA") == 0);
    assert(distance("AGA", "GAA") == 2);
    assert(distance("AGCAT", "AGCAT") == 0);
    assert(distance("AAAAAGC", "AAAAA") == 2);
    assert(distance("AAAAA", "GCAAAAA") == 2);
    assert(distance("GCT", "AAAAAA") == 9);
}

void TestCase_LCSGreedy()
{
    auto lcs = somera::EditDistance::computeLCSLength_ONDGreedyAlgorithm;
    assert(lcs("", "") == 0);
    assert(lcs("A", "") == 0);
    assert(lcs("", "A") == 0);
    assert(lcs("A", "A") == 1);
    assert(lcs("AG", "GA") == 1);
    assert(lcs("AA", "AA") == 2);
    assert(lcs("AGA", "GAA") == 2);
    assert(lcs("AGCAT", "AGCAT") == 5);
    assert(lcs("AAAAAGC", "AAAAA") == 5);
    assert(lcs("AAAAA", "GCAAAAA") == 5);
    assert(lcs("GCT", "AAAAAA") == 0);
    assert(lcs("AAGGCCTTAGCT", "AAGGCCAGT") == 9);
    assert(lcs("AAGGCCTTAGCT", "AGCTAAGGCCAGCAAGGTT") == 10);
}

void TestCase_LevenshteinDistance_ReplacementCost1()
{
    auto distance = somera::EditDistance::levenshteinDistance_DynamicProgramming_ReplacementCost1;
    assert(distance("levenshtein", "meilenstein") == 4);
    assert(distance("book", "back") == 2);
    assert(distance("book", "book") == 0);
    assert(distance("book", "bok") == 1);
    assert(distance("book", "boook") == 1);
    assert(distance("book", "bookk") == 1);
    assert(distance("book", "bbookk") == 2);
    assert(distance("AAATT", "AGCGA") == 4);
    assert(distance("AAATTATGGAAGACGATC", "AGCGATATTAGGGAAGAGA") == 8);
}

void ReadWordListFile(
    const std::string& path,
    const std::function<void(const std::string&)>& callback)
{
    std::error_code errorCode;
    const auto fileSize = somera::FileSystem::getFileSize(path, errorCode);

    if (errorCode) {
        std::cerr << "error: Cannot found the file. " << path << std::endl;
        return;
    }
    if (fileSize >= std::numeric_limits<int32_t>::max()) {
        // TODO: We cannot read a file larger than 2GB.
        std::cerr << "error: File is too large to read. " << path << std::endl;
        return;
    }

    std::ifstream input(path, std::ios::binary);
    if (!input) {
        return;
    }

    std::istreambuf_iterator<char> start(input);
    std::istreambuf_iterator<char> end;

    std::string word;
    for (; start != end; ++start) {
        auto c = *start;
        if (c == '\r' || c == '\n' || c == '\0') {
            if (!word.empty()) {
                callback(word);
            }
            word.clear();
            continue;
        }
        word += c;
    }
    if (!word.empty()) {
        callback(word);
    }
}

std::vector<std::pair<std::string, std::string>> GetMisspelledWordPairs()
{
    std::vector<std::pair<std::string, std::string>> pairs;
    ReadWordListFile(
        "/Volumes/marie/daily-snippets/approximate-winter/MisspelledWords.txt",
        [&](const std::string& line) {
            auto pairSource = somera::StringHelper::split(line, " < ");
            if (pairSource.size() != 2) {
                return;
            }
            pairs.emplace_back(pairSource.front(), pairSource.back());
        });
    return pairs;
}

void PrintMisspelledWordDistribution()
{
    auto pairs = GetMisspelledWordPairs();
    std::sort(std::begin(pairs), std::end(pairs), [](auto & a, auto & b) {
        auto x = somera::EditDistance::closestMatchFuzzySimilarity(a.first, a.second);
        auto y = somera::EditDistance::closestMatchFuzzySimilarity(b.first, b.second);
        return x < y;
    });

    for (auto & pair : pairs) {
        auto & correction = pair.first;
        auto & misspelled = pair.second;
        
        auto similarity = somera::EditDistance::closestMatchFuzzySimilarity(correction, misspelled);
        auto distance = somera::EditDistance::levenshteinDistance_ONDGreedyAlgorithm(correction, misspelled);
        if (similarity > 0.5 && similarity < 0.85) {
            std::cout << correction << "\t" << misspelled << "\t" << similarity << "\t" << distance << std::endl;
        }
    }

    double compensation = 0;
    double sum = 0;
    double minValue = 1.0;
    double maxValue = 0;
    
    constexpr int distributionCount = 20;
    std::vector<int> distribution(distributionCount, 0);
    int maxDistribution = 0;
    
    for (auto & pair : pairs) {
        auto & correction = pair.first;
        auto & misspelled = pair.second;
        
        auto similarity = somera::EditDistance::closestMatchFuzzySimilarity(correction, misspelled);
        
        // NOTE: Kahan summation algorithm
        auto tmp = similarity - compensation;
        auto velvel = sum + tmp;
        compensation = (velvel - sum) - tmp;
        sum = velvel;
        
        minValue = std::min(minValue, similarity);
        maxValue = std::max(maxValue, similarity);

        int scale = 0;
        for (; scale < distributionCount; ++scale) {
            constexpr auto unit = (1.0 / static_cast<double>(distributionCount));
            const auto next = static_cast<double>(scale + 1) * unit;
            if (similarity < next) {
                break;
            }
        }
        distribution[scale] += 1;
        maxDistribution = std::max(maxDistribution, distribution[scale]);
    }
    const auto average = sum / static_cast<double>(pairs.size());
    std::cout << "Average: " << average << std::endl;
    std::cout << "Min: " << minValue << std::endl;
    std::cout << "Max: " << maxValue << std::endl;
    
    for (int scale = 0; scale < distributionCount; ++scale) {
        constexpr auto unit = (1.0 / static_cast<double>(distributionCount));
        const auto first = static_cast<double>(scale) * unit;
        const auto last = static_cast<double>(scale + 1) * unit;
        std::printf("[%1.2lf, %1.2lf](%3d)", first, last, distribution[scale]);
        constexpr int maxAsterisk = 50;
        int asterisk = distribution[scale] * (maxAsterisk / static_cast<double>(maxDistribution));
        for (int i = 0; i < asterisk; ++i) {
            std::cout << "*";
        }
        std::cout << std::endl;
    }
}

} // unnamed namespace

int main(int argc, char *argv[])
{
    CommandLineParser parser;
    SetupCommandLineParser(parser);
    parser.parse(argc, argv);

    if (parser.hasParseError()) {
        std::cerr << parser.getErrorMessage() << std::endl;
        return 1;
    }
    if (parser.exists("-h") || parser.exists("-help")) {
        std::cout << parser.getHelpText() << std::endl;
        return 0;
    }

    if (parser.getValue("-unittest")) {
        TestCase_HistogramHashing();
        return 0;
    }

    if (!parser.getValue("-dict")) {
        std::cout << "Please specify the dictionary file path with `-dict` option." << std::endl;
        return 1;
    }

    {
        TestCase_LCS();
        TestCase_LCSGreedy();
        TestCase_DPLinearSpace();
        TestCase_LevenshteinDistance_ReplacementCost1();

        auto ok = [&](const std::string& a, const std::string& b) {
            std::cout
                << somera::EditDistance::closestMatchFuzzySimilarity(a, b)
                << " "
                << somera::EditDistance::closestMatchFuzzySimilarity_Boer(a, b)
                << std::endl;
            return somera::EditDistance::closestMatchFuzzySimilarity(a, b) == somera::EditDistance::closestMatchFuzzySimilarity_Boer(a, b);
        };
        ok("", "");
        ok("AGA", "ATA");
        ok("AAGGCCTTAGCT", "AAGGCCTTAGCT");
        ok("deferred", "defered");
        ok("AAGGCCTTAGCT", "AAGGCCAGT");
        ok("AAGGCCTTAGCT", "AGCTAAGGCCAGCAAGGTT");
    }

    auto dictionarySourcePath = *parser.getValue("-dict");
    //auto dictionarySourcePath = "/usr/share/dict/words";

    std::vector<std::string> dictionary;
    std::unordered_map<uint32_t, std::vector<std::string>> hashedDictionary;
    std::unordered_map<uint32_t, std::vector<std::string>> hashedDictionary_Accumulate;
    std::unordered_map<int, std::vector<std::string>> hashedDictionary_Size;
    std::unordered_map<int, std::unordered_map<uint32_t, std::vector<std::string>>> hashedDictionary_SizeAndSignature;
    std::unordered_map<uint32_t, std::vector<std::string>> hashedDictionary_Cyclic32;
    std::unordered_map<uint32_t, std::vector<std::string>> hashedDictionary_Cyclic16;
    std::unordered_map<uint32_t, std::vector<std::string>> hashedDictionary_Cyclic8;

    auto spellChecker = somera::SpellCheckerFactory::Create();

    ReadDictionaryFile(dictionarySourcePath, [&](const std::string& word) {
        dictionary.push_back(word);
        spellChecker->AddWord(word);
        
        {
            auto histogramHash = HistogramHashing_Alphabet(word);
            auto iter = hashedDictionary.find(histogramHash);
            if (iter == std::end(hashedDictionary)) {
                std::vector<std::string> dict;
                hashedDictionary.emplace(histogramHash, std::move(dict));
                iter = hashedDictionary.find(histogramHash);
            }
            assert(iter != std::end(hashedDictionary));
            iter->second.push_back(word);
        }
        {
            auto histogramHash = HistogramHashing_Accumulate(word);
            auto iter = hashedDictionary_Accumulate.find(histogramHash);
            if (iter == std::end(hashedDictionary_Accumulate)) {
                std::vector<std::string> dict;
                hashedDictionary_Accumulate.emplace(histogramHash, std::move(dict));
                iter = hashedDictionary_Accumulate.find(histogramHash);
            }
            assert(iter != std::end(hashedDictionary_Accumulate));
            iter->second.push_back(word);
        }
        {
            auto histogramHash = HistogramHashing_Accumulate(word);
            auto iter = hashedDictionary_Accumulate.find(histogramHash);
            if (iter == std::end(hashedDictionary_Accumulate)) {
                std::vector<std::string> dict;
                hashedDictionary_Accumulate.emplace(histogramHash, std::move(dict));
                iter = hashedDictionary_Accumulate.find(histogramHash);
            }
            assert(iter != std::end(hashedDictionary_Accumulate));
            iter->second.push_back(word);
        }
        {
            auto histogramHash = HistogramHashing_Cyclic32(word);
            auto iter = hashedDictionary_Cyclic32.find(histogramHash);
            if (iter == std::end(hashedDictionary_Cyclic32)) {
                std::vector<std::string> dict;
                hashedDictionary_Cyclic32.emplace(histogramHash, std::move(dict));
                iter = hashedDictionary_Cyclic32.find(histogramHash);
            }
            assert(iter != std::end(hashedDictionary_Cyclic32));
            iter->second.push_back(word);
        }
        {
            auto histogramHash = HistogramHashing_Cyclic16(word);
            auto iter = hashedDictionary_Cyclic16.find(histogramHash);
            if (iter == std::end(hashedDictionary_Cyclic16)) {
                std::vector<std::string> dict;
                hashedDictionary_Cyclic16.emplace(histogramHash, std::move(dict));
                iter = hashedDictionary_Cyclic16.find(histogramHash);
            }
            assert(iter != std::end(hashedDictionary_Cyclic16));
            iter->second.push_back(word);
        }
        {
            auto histogramHash = HistogramHashing_Cyclic8(word);
            auto iter = hashedDictionary_Cyclic8.find(histogramHash);
            if (iter == std::end(hashedDictionary_Cyclic8)) {
                std::vector<std::string> dict;
                hashedDictionary_Cyclic8.emplace(histogramHash, std::move(dict));
                iter = hashedDictionary_Cyclic8.find(histogramHash);
            }
            assert(iter != std::end(hashedDictionary_Cyclic8));
            iter->second.push_back(word);
        }
        {
            auto hash = SizeHash(word);
            auto iter = hashedDictionary_Size.find(hash);
            if (iter == std::end(hashedDictionary_Size)) {
                std::vector<std::string> dict;
                hashedDictionary_Size.emplace(hash, std::move(dict));
                iter = hashedDictionary_Size.find(hash);
            }
            assert(iter != std::end(hashedDictionary_Size));
            iter->second.push_back(word);
        }
        {
            auto sizeHash = SizeHash(word);
            auto iter2 = hashedDictionary_SizeAndSignature.find(sizeHash);
            if (iter2 == std::end(hashedDictionary_SizeAndSignature)) {
                std::unordered_map<std::uint32_t, std::vector<std::string>> dict;
                hashedDictionary_SizeAndSignature.emplace(sizeHash, std::move(dict));
                iter2 = hashedDictionary_SizeAndSignature.find(sizeHash);
            }
            assert(iter2 != std::end(hashedDictionary_SizeAndSignature));
            auto & histogramDictionary = iter2->second;
        
            auto histogramHash = HistogramHashing_Alphabet(word);
            auto iter = histogramDictionary.find(histogramHash);
            if (iter == std::end(histogramDictionary)) {
                std::vector<std::string> dict;
                histogramDictionary.emplace(histogramHash, std::move(dict));
                iter = histogramDictionary.find(histogramHash);
            }
            assert(iter != std::end(histogramDictionary));
            iter->second.push_back(word);
        }
    });

//    PrintLetterFrequency(dictionary);
//    PrintMisspelledWordDistribution();

    std::cout << "dictionary words: " << dictionary.size() << std::endl;
    std::cout << "hash indices (Histogram): " << hashedDictionary.size() << std::endl;
    std::cout << "hash indices (Histogram32): " << hashedDictionary_Cyclic32.size() << std::endl;
    std::cout << "hash indices (Histogram16): " << hashedDictionary_Cyclic16.size() << std::endl;
    std::cout << "hash indices (Histogram8): " << hashedDictionary_Cyclic8.size() << std::endl;
    std::cout << "hash indices (Size): " << hashedDictionary_Size.size() << std::endl;
    std::cout << "hash indices (Accumulate): " << hashedDictionary_Accumulate.size() << std::endl;
    std::cout << "------------------" << std::endl;

    std::vector<std::string> inputWords = {
        "defered",
        "deferred",
        "accepteable",
        "beleive",
        "drunkenes",
        "existance",
        "foriegn",
        "greatful",
        "wether",
        "weather",
        "whether",
        "revelant",
        "relavent",
        "relevant",
        "enviromet",
        "enviroment",
        "environment",
        "that",
        "thet",
        "thhe",
        "thh",
        "The",
        "Donald",
        "DONALD",
        "get",
        "Get",
        "tileset",
        "setOpacity",
        "CCCamera",
        "isDone",
        "xOffset",
        "OpenGL",
        "openGL",
        "opengl",
        "Opengl",
        "cpp",
        "Cpp",
        "CPP",
    };

//    measurePerformanceTime([&] {
//        auto spellCheck = SpellCheck_Innocent;
//        auto & dict = dictionary;
//        for (auto & inputWord : inputWords) {
//            Print(spellCheck, inputWord, dict);
//        }
//    });
//

//    std::cout << "------------------" << std::endl;
//
//    measurePerformanceTime([&] {
//        auto spellCheck = SpellCheck_HistogramHashinging;
//        auto & dict = hashedDictionary;
//        for (auto & inputWord : inputWords) {
//            Print(spellCheck, inputWord, dict);
//        }
//    });
//
//    std::cout << "------------------" << std::endl;
//
//    measurePerformanceTime([&] {
//        auto spellCheck = SpellCheck_HistogramHashinging_ONDThreshold;
//        auto & dict = hashedDictionary;
//        for (auto & inputWord : inputWords) {
//            Print(spellCheck, inputWord, dict);
//        }
//    });
//
//    std::cout << "------------------" << std::endl;
//
//    measurePerformanceTime([&] {
//        auto spellCheck = SpellCheck_HistogramHashinging_ONDThreshold_Cyclic32;
//        auto & dict = hashedDictionary_Cyclic32;
//        for (auto & inputWord : inputWords) {
//            Print(spellCheck, inputWord, dict);
//        }
//    });
//
//    std::cout << "------------------" << std::endl;
//
//    measurePerformanceTime([&] {
//        auto spellCheck = SpellCheck_HistogramHashinging_ONDThreshold_Cyclic16;
//        auto & dict = hashedDictionary_Cyclic16;
//        for (auto & inputWord : inputWords) {
//            Print(spellCheck, inputWord, dict);
//        }
//    });
//
//    std::cout << "------------------" << std::endl;
//
//    measurePerformanceTime([&] {
//        auto spellCheck = SpellCheck_HistogramHashinging_ONDThreshold_Cyclic8;
//        auto & dict = hashedDictionary_Cyclic8;
//        for (auto & inputWord : inputWords) {
//            Print(spellCheck, inputWord, dict);
//        }
//    });
//    
//    std::cout << "------------------" << std::endl;
//
//    measurePerformanceTime([&] {
//        auto spellCheck = SpellCheck_SizeHashing;
//        auto & dict = hashedDictionary_Size;
//        for (auto & inputWord : inputWords) {
//            Print(spellCheck, inputWord, dict);
//        }
//    });
//
//    std::cout << "------------------" << std::endl;
//
//    measurePerformanceTime([&] {
//        auto spellCheck = SpellCheck_AccumulateHashing;
//        auto & dict = hashedDictionary_Accumulate;
//        for (auto & inputWord : inputWords) {
//            Print(spellCheck, inputWord, dict);
//        }
//    });
//    
//    std::cout << "------------------" << std::endl;
//
//    measurePerformanceTime([&] {
//        auto spellCheck = SpellCheck_SizeAndHistogram;
//        auto & dict = hashedDictionary_SizeAndSignature;
//        for (auto & inputWord : inputWords) {
//            Print(spellCheck, inputWord, dict);
//        }
//    });
    
    std::cout << "------------------" << std::endl;

    measurePerformanceTime([&] {
        for (auto & word : inputWords) {
            Print(spellChecker, word);
        }
    });
    
    return 0;
}
