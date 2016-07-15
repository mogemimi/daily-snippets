// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#include "somera/CommandLineParser.h"
#include "somera/FileSystem.h"
#include "somera/Optional.h"
#include "somera/StringHelper.h"
#include "thirdparty/ConvertUTF.h"
#include <iostream>
#include <fstream>
#include <array>

using somera::CommandLineParser;
using somera::Optional;
using somera::NullOpt;
namespace StringHelper = somera::StringHelper;

namespace {

void SetupCommandLineParser(CommandLineParser & parser)
{
    using somera::CommandLineArgumentType::Flag;
    using somera::CommandLineArgumentType::JoinedOrSeparate;
    parser.setUsageText("textcxx [options ...] [C/C++ file ...]");
    parser.addArgument("-h", Flag, "Display available options");
    parser.addArgument("-help", Flag, "Display available options");
    parser.addArgument("-no-pedantic", Flag, "Pedantic mode disabled");
}

struct Character {
    std::string word;
    std::size_t positionInBinary;
    std::size_t column;
    std::size_t line;
};

void ReadUTF8TextFile(
    const std::string& path, const std::function<void(Character&&)>& callback)
{
    std::error_code errorCode;
    auto fileSize = somera::FileSystem::getFileSize(path, errorCode);

    std::ifstream input(path, std::ios::binary);
    if (!input) {
        return;
    }

    std::istreambuf_iterator<char> start(input);
    std::istreambuf_iterator<char> end;
    std::size_t byteIndex = 0;
    std::size_t utf8CharacterCount = 0;
    std::size_t lineCount = 0;
    std::size_t columnCount = 0;

    while (input && (byteIndex < fileSize)) {
        std::array<UTF8, 5> buffer;
        std::fill(std::begin(buffer), std::end(buffer), 0);

        const auto readableSize = std::min<std::size_t>(4, fileSize - byteIndex);
        assert(readableSize <= buffer.size());
        assert(byteIndex + readableSize <= fileSize);
        input.read(reinterpret_cast<char*>(buffer.data()), readableSize);

        auto source = buffer.data();
        auto sourceEnd = buffer.data() + readableSize;

        if (!isLegalUTF8Sequence(source, sourceEnd)) {
            // Error: Invalid UTF-8 byte sequence
            std::cerr << "error: Invalid UTF-8 byte sequence." << std::endl;
            break;
        }

        const auto readBytes = getNumBytesForUTF8(buffer.front());

        assert(readBytes <= readableSize);
        assert((byteIndex + readBytes) <= fileSize);

        if (readBytes < readableSize) {
            input.seekg(byteIndex, std::ios_base::beg);
        }

        Character character;
        character.word.assign(reinterpret_cast<char*>(buffer.data()), readBytes);
        character.column = columnCount;
        character.line = lineCount;
        character.positionInBinary = byteIndex;

        assert(callback);
        callback(std::move(character));

        byteIndex += readBytes;
        utf8CharacterCount++;
        columnCount++;

        if (buffer.front() == '\n') {
            lineCount++;
            columnCount = 0;
        }
    }
}

bool IsSpace(const std::string& c)
{
    if (c.size() == 1) {
        return ::isspace(c.front()) != 0;
    }
    if (c == "\xE3\x80\x80") {
        return true;
    }
    return false;
}

bool IsSeparator(const std::string& c)
{
    if (c.size() != 1) {
        return false;
    }

    std::string separators = "!\"#()*+,-./:<>?@[\\]`~";
#if 0
    std::sort(std::begin(separators), std::end(separators));
    std::cout << '"';
    for (auto separator : separators) {
        std::string escapeCharacters = "\"\\\'";
        if (std::binary_search(std::begin(escapeCharacters), std::end(escapeCharacters), separator)) {
            std::cout << '\\';
        }
        std::cout << separator;
    }
    std::cout << '"' << std::endl;
    assert(std::is_sorted(std::begin(separators), std::end(separators)));
#endif
    return std::binary_search(std::begin(separators), std::end(separators), c.front());
}

void ReadTextFileWithoutPedanticMode(const std::string& path)
{
    auto flush = [&](std::string && word) {
        std::cout << word << std::endl;
    };
    std::string word;
    ReadUTF8TextFile(path, [&](Character && character) {
        if (IsSpace(character.word) || IsSeparator(character.word)) {
            if (!word.empty()) {
                std::string temp;
                std::swap(word, temp);
                flush(std::move(temp));
            }
        }
        word += character.word;
    });
}

void ReadSourceCode(const std::string& path)
{
    auto flush = [&](std::string && word) {
        std::cout << word << std::endl;
    };
    std::string word;
    ReadUTF8TextFile(path, [&](Character && character) {
        if (IsSpace(character.word)) {
            if (!word.empty()) {
                std::string temp;
                std::swap(word, temp);
                flush(std::move(temp));
            }
        }
        word += character.word;
    });
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
    if (parser.getPaths().empty()) {
        std::cerr << "error: no input file" << std::endl;
        return 1;
    }

    if (parser.exists("-no-pedantic")) {
        for (auto & path : parser.getPaths()) {
            ReadTextFileWithoutPedanticMode(path);
        }
    }
    else {
        for (auto & path : parser.getPaths()) {
            ReadSourceCode(path);
        }
    }
    return 0;
}
