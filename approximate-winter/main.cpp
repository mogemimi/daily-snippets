// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#include "EditDistance.h"
#include "WordDiff.h"
#include "WordSegmenter.h"
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
    return hash;
}

uint32_t HistogramHashing_SortByLetterFrequency(const std::string& word)
{
    // NOTE:
    // '#' is number 0 to 9.
    // '@' is symbols and other characters.
    //
    //   JQXZWKVFBYGHMDPUCLTRONSAIE#@
    //   jqxzwkvfbyghmdpucltronsaie#@
    // 0b0000000000000000000000000000

    std::array<int, 128> offsets = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 4, 19, 11, 
        14, 2, 20, 17, 16, 3, 27, 22, 10, 15, 6, 7, 13, 26, 8, 5, 9, 
        12, 21, 23, 25, 18, 24, 0, 0, 0, 0, 0, 0, 4, 19, 11, 14, 2, 
        20, 17, 16, 3, 27, 22, 10, 15, 6, 7, 13, 26, 8, 5, 9, 12, 21, 
        23, 25, 18, 24, 0, 0, 0, 0, 0
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
    return hash;
}

uint32_t HistogramHashing(const std::string& word)
{
#if 1
    return HistogramHashing_Alphabet(word);
#else
    return HistogramHashing_SortByLetterFrequency(word);
#endif
}

void TestCase_HistogramHashing()
{
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

void SpellCheck_SizeHashing_Internal(
    const std::string& input,
    const std::vector<std::string>& dictionary,
    std::vector<std::string> & corrections,
    bool & exaxtMatching,
    const std::function<int(const std::string&, const std::string&)>& levenshteinDistance,
    int inputHash,
    int threshold)
{
    for (auto & word : dictionary) {
        const auto wordHash = SizeHash(word);
        if (std::abs(wordHash - inputHash) >= threshold) {
            continue;
        }
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

std::vector<std::string> SpellCheck_SizeHashing(
    const std::string& input,
    const std::vector<std::string>& dictionary)
{
    const auto inputHash = SizeHash(input);
    const auto threshold = 3;
    
    std::vector<std::string> corrections;
    
    bool exactMatching = false;
    SpellCheck_SizeHashing_Internal(
        input,
        dictionary,
        corrections,
        exactMatching,
        somera::EditDistance::levenshteinDistance_ONDGreedyAlgorithm,
        inputHash,
        threshold);

    return corrections;
}

std::vector<std::string> SpellCheck_HistogramHashinging_Internal(
    const std::string& input,
    const std::unordered_map<uint32_t, std::vector<std::string>>& hashedDictionary,
    const std::function<int(const std::string&, const std::string&)>& levenshteinDistance)
{
    const auto inputSizeHash = SizeHash(input);
    const auto threshold = 3;
    
    std::vector<std::string> corrections;
    
    const int maxHashLength = 28;
    const auto inputHistogramHashing = HistogramHashing(input);

    for (int i = 0; i <= maxHashLength; ++i) {
        const uint32_t bitmask = ((static_cast<uint32_t>(1) << i) >> 1);
        const uint32_t xorBits = inputHistogramHashing ^ bitmask;
        
        auto iter = hashedDictionary.find(xorBits);
        if (iter == std::end(hashedDictionary)) {
            continue;
        }
        const auto& dictionary = iter->second;

        bool exactMatching = false;
        SpellCheck_SizeHashing_Internal(
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

std::vector<std::string> SpellCheck_HistogramHashinging(
    const std::string& input,
    const std::unordered_map<uint32_t, std::vector<std::string>>& hashedDictionary)
{
    return SpellCheck_HistogramHashinging_Internal(
        input,
        hashedDictionary,
        somera::EditDistance::levenshteinDistance_ONDGreedyAlgorithm);
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
        });
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
        auto distanceA = somera::EditDistance::levenshteinDistance_ONDGreedyAlgorithm(inputWord, a);
        auto distanceB = somera::EditDistance::levenshteinDistance_ONDGreedyAlgorithm(inputWord, b);
        return distanceA < distanceB;
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

    auto dictionarySourcePath = *parser.getValue("-dict");

    std::vector<std::string> dictionary;
    std::unordered_map<uint32_t, std::vector<std::string>> hashedDictionary;

    ReadDictionaryFile(dictionarySourcePath, [&](const std::string& word) {
        dictionary.push_back(word);
        
        auto histogramHash = HistogramHashing(word);
        auto iter = hashedDictionary.find(histogramHash);
        if (iter == std::end(hashedDictionary)) {
            std::vector<std::string> dict;
            hashedDictionary.emplace(histogramHash, std::move(dict));
            iter = hashedDictionary.find(histogramHash);
        }
        assert(iter != std::end(hashedDictionary));
        iter->second.push_back(word);
    });

//    PrintLetterFrequency(dictionary);

    std::cout << "dictionary words: " << dictionary.size() << std::endl;
    std::cout << "hash indices: " << hashedDictionary.size() << std::endl;
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
    };

    measurePerformanceTime([&] {
        auto spellCheck = SpellCheck_Innocent;
        auto & dict = dictionary;
        for (auto & inputWord : inputWords) {
            Print(spellCheck, inputWord, dict);
        }
    });

    std::cout << "------------------" << std::endl;

    measurePerformanceTime([&] {
        auto spellCheck = SpellCheck_SizeHashing;
        auto & dict = dictionary;
        for (auto & inputWord : inputWords) {
            Print(spellCheck, inputWord, dict);
        }
    });

    std::cout << "------------------" << std::endl;

    measurePerformanceTime([&] {
        auto spellCheck = SpellCheck_HistogramHashinging;
        auto & dict = hashedDictionary;
        for (auto & inputWord : inputWords) {
            Print(spellCheck, inputWord, dict);
        }
    });

    std::cout << "------------------" << std::endl;

    measurePerformanceTime([&] {
        auto spellCheck = SpellCheck_HistogramHashinging_ONDThreshold;
        auto & dict = hashedDictionary;
        for (auto & inputWord : inputWords) {
            Print(spellCheck, inputWord, dict);
        }
    });

    return 0;
}
