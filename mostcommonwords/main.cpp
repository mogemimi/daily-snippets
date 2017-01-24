// Copyright (c) 2017 mogemimi. Distributed under the MIT license.

#include "EditDistance.h"
#include "WordDiff.h"
#include "Optional.h"
#include "CommandLineParser.h"
#include "WordSegmenter.h"
#include "StringHelper.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <experimental/optional>
#include <iomanip>
#include <cassert>
#include <functional>
#include <random>
#include <unordered_map>

using namespace somera;
using somera::CommandLineParser;
using somera::Optional;
using somera::NullOpt;

namespace {

void SetupCommandLineParser(CommandLineParser & parser)
{
    using Type = somera::CommandLineArgumentType;
    parser.setUsageText("mostcommonwords [options ...] [C/C++ file ...]");
    parser.addArgument("-h", Type::Flag, "Display available options");
    parser.addArgument("-help", Type::Flag, "Display available options");
    parser.addArgument("-v", Type::Flag, "Display version");
    parser.addArgument("-dict", Type::JoinedOrSeparate, "Dictionary file");
}

bool ReadTextFile(
    const std::string& path,
    const std::function<void(const std::string&)>& callback)
{
    std::ifstream input(path, std::ios::binary);
    if (!input) {
        std::cerr << "error: Cannot open the file. " << path << std::endl;
        return false;
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
        // TODO: The word must be a UTF-8 encoded string but this function
        // does not validate that the word is UTF-8 string.
        callback(word);
    }
    return true;
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
    if (parser.exists("-v")) {
        std::cout << "mostcommonwords version 0.1.0 (Jan 24, 2017)" << std::endl;
        return 0;
    }
    if (parser.getPaths().empty()) {
        std::cerr << "error: no input file" << std::endl;
        return 1;
    }

    std::vector<std::string> dictionaryPaths = parser.getValues("-dict");
    
    std::unordered_map<std::string, int> wordFrequencies;
    
    WordSegmenter segmenter;
    auto onPartOfSpeech = [&](const PartOfSpeech& p) {
        if (p.tag != PartOfSpeechTag::Word) {
            return;
        }
        auto iter = wordFrequencies.find(p.text);
        if (iter == std::end(wordFrequencies)) {
            wordFrequencies.emplace(p.text, 1);
        }
        else {
            ++iter->second;
        }
    };

    for (auto & path : parser.getPaths()) {
        ReadTextFile(path, [&](const std::string& text) {
            segmenter.Parse(text, onPartOfSpeech);
        });
    }

    struct WordFreq {
        std::string word;
        int frequency = 0;
    };
    std::vector<WordFreq> words;
    for (const auto& pair : wordFrequencies) {
        WordFreq f;
        f.word = pair.first;
        f.frequency = pair.second;
        words.push_back(std::move(f));
    }

    std::stable_sort(std::begin(words), std::end(words), [](auto & a, auto & b) {
        return a.frequency > b.frequency;
    });

    for (auto & w : words) {
        std::cout << w.word << "\t" << w.frequency << std::endl;
    }

    return 0;
}
