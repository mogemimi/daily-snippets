// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#include "somera/CommandLineParser.h"
#include "somera/FileSystem.h"
#include "somera/Optional.h"
#include "somera/StringHelper.h"
#include <iostream>
#include <fstream>
#include <regex>

using somera::CommandLineParser;
using somera::Optional;
using somera::NullOpt;
namespace FileSystem = somera::FileSystem;
namespace StringHelper = somera::StringHelper;

namespace {

void setupCommandLineParser(CommandLineParser & parser)
{
    using somera::CommandLineArgumentType::Flag;
    using somera::CommandLineArgumentType::JoinedOrSeparate;
    parser.setUsageText("matoi [directory path]");
    parser.addArgument("-h", Flag, "Display available options");
    parser.addArgument("-help", Flag, "Display available options");
}

bool IsSeparator(char32_t c)
{
    // NOTE: Ascii characters without alphabet, numbers and [-.'].
    std::string separators = "!\"#$%&()*+,/:;<=>?@[\\]^`{|}~";
    assert(std::is_sorted(separators.begin(), separators.end()));
    return std::binary_search(std::begin(separators), std::end(separators), c);
}

bool IsConcatenator(char32_t c)
{
    std::string separators = "'-.";
    assert(std::is_sorted(separators.begin(), separators.end()));
    return std::binary_search(std::begin(separators), std::end(separators), c);
}

enum class PartOfSpeechTag {
    Word,
    Spaces,
    Symbol,
    GitUrl,
    Url,
    Integer,
    IntegerBinary,
    IntegerHex,
    FloatNumber,
};

class Tokenizer {
public:
    void Tokenize(
        const std::string& str,
        const std::function<void(const std::string&, PartOfSpeechTag)>& onToken);
};

std::vector<std::tuple<std::string, PartOfSpeechTag>> SplitBySpace(const std::string& str)
{
    std::vector<std::tuple<std::string, PartOfSpeechTag>> tokens;
    std::string buffer;
    std::string separator;
    auto flushBuffer = [&] {
        if (!buffer.empty()) {
            tokens.emplace_back(buffer, PartOfSpeechTag::Word);
            buffer.clear();
        }
    };
    auto flushSeparator = [&] {
        if (!separator.empty()) {
            tokens.emplace_back(separator, PartOfSpeechTag::Spaces);
            separator.clear();
        }
    };

    auto iter = str.begin();
    auto end = str.end();
    for (; iter != end; ++iter) {
        auto character = *iter;
        if (::isspace(character)) {
            flushBuffer();
            separator += character;
        }
        else {
            flushSeparator();
            buffer += character;
        }
    }
    assert(buffer.empty() || separator.empty());
    flushBuffer();
    flushSeparator();
    return tokens;
}

void TokenizeByAsciiSymbols(
    const std::string& str,
    const std::function<void(const std::string&, PartOfSpeechTag)>& onToken)
{
    std::string buffer;
    std::string separator;

    auto flushBuffer = [&] {
        if (buffer.empty()) {
            return;
        }

        auto trimRight = std::find_if(std::rbegin(buffer), std::rend(buffer),
            [&](char32_t c){ return !IsConcatenator(c); }).base();

        std::string prefix(std::begin(buffer), trimRight);
        std::string suffix(trimRight, std::end(buffer));
        buffer.clear();

        if (std::regex_match(prefix, std::regex(R"(\d+)"))) {
            // integer
            onToken(prefix, PartOfSpeechTag::Integer);
        }
        else if (std::regex_match(prefix, std::regex(R"(0x[\dA-Fa-f])"))) {
            // hex integer
            onToken(prefix, PartOfSpeechTag::IntegerHex);
        }
        else if (std::regex_match(prefix, std::regex(R"(0b[01])"))) {
            // binary integer
            onToken(prefix, PartOfSpeechTag::IntegerBinary);
        }
        else if (std::regex_match(prefix, std::regex(R"((\d*\.\d+|\d+\.\d*)f?)"))) {
            // float number
            onToken(prefix, PartOfSpeechTag::FloatNumber);
        }
        else {
            onToken(prefix, PartOfSpeechTag::Word);
        }

        if (!suffix.empty()) {
            onToken(suffix, PartOfSpeechTag::Symbol);
        }
    };
    auto flushSeparator = [&] {
        if (!separator.empty()) {
            onToken(separator, PartOfSpeechTag::Spaces);
            separator.clear();
        }
    };

    auto iter = str.begin();
    auto end = str.end();
    for (; iter != end; ++iter) {
        auto character = *iter;
        if ((IsSeparator(character)) || (buffer.empty() && IsConcatenator(character))) {
            flushBuffer();
            separator += character;
        }
        else {
            flushSeparator();
            buffer += character;
        }
    }
    assert(buffer.empty() || separator.empty());
    flushBuffer();
    flushSeparator();
}

void Tokenizer::Tokenize(
    const std::string& str,
    const std::function<void(const std::string&, PartOfSpeechTag)>& onToken)
{
    auto splitStrings = SplitBySpace(str);

    for (auto & tuple : splitStrings) {
        auto & text = std::get<0>(tuple);
        auto & tag = std::get<1>(tuple);
        if (tag == PartOfSpeechTag::Spaces) {
            onToken(text, PartOfSpeechTag::Spaces);
            continue;
        }
        if (std::regex_match(text, std::regex(R"(git@\w+\..+)"))) {
            onToken(text, PartOfSpeechTag::GitUrl);
            continue;
        }
        if (std::regex_match(text, std::regex(R"((http|https|ftp)://.+)"))) {
            onToken(text, PartOfSpeechTag::Url);
            continue;
        }
        TokenizeByAsciiSymbols(text, onToken);
    }
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
        if (c == '\0') {
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
    setupCommandLineParser(parser);
    parser.parse(argc, argv);

    if (parser.hasParseError()) {
        std::cerr << parser.getErrorMessage() << std::endl;
        return 1;
    }
    if (parser.exists("-h") || parser.exists("-help")) {
        std::cout << parser.getHelpText() << std::endl;
        return 0;
    }
    if (parser.getPaths().empty()) {
        std::cerr << "error: no input file" << std::endl;
        return 1;
    }

    Tokenizer tokenizer;
    for (auto & path : parser.getPaths()) {
        auto onToken = [&](const std::string& token, PartOfSpeechTag tag) {
            if (tag != PartOfSpeechTag::Word) {
                return;
            }
            std::cout << "[TOKEN]" << token << std::endl;
        };
        auto readText = [&](const std::string& line) {
            tokenizer.Tokenize(line, onToken);
        };
        if (!ReadTextFile(path, readText)) {
            std::cerr << "error: no input file" << std::endl;
            return 1;
        }
    }

    return 0;
}
