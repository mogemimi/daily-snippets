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

void setupCommandLineParser(CommandLineParser & parser)
{
    using somera::CommandLineArgumentType::Flag;
    using somera::CommandLineArgumentType::JoinedOrSeparate;
    parser.setUsageText("textcxx [options ...] [C/C++ file ...]");
    parser.addArgument("-h", Flag, "Display available options");
    parser.addArgument("-help", Flag, "Display available options");
}

struct Character {
    std::string word;
    std::size_t positionInBinary;
    std::size_t column;
    std::size_t line;
};

void readUTF8TextFile(
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

bool isSpace(const std::string& c)
{
    if (c.size() == 1) {
        return ::isspace(c.front()) != 0;
    }
    if (c == "\xE3\x80\x80") {
        return true;
    }
    return false;
}

bool isSeparator(const std::string& c)
{
    if (c.size() != 1) {
        return false;
    }

    std::string op = "!\"#()*+,-./:<>?[\\]`~";
#if 0
    std::sort(std::begin(op), std::end(op));
    std::cout << '"';
    for (auto o : op) {
        std::string escapeCharacters = "\"\\\'";
        if (std::binary_search(std::begin(escapeCharacters), std::end(escapeCharacters), o)) {
            std::cout << '\\';
        }
        std::cout << o;
    }
    std::cout << '"' << std::endl;
    assert(std::is_sorted(std::begin(op), std::end(op)));
#endif
    return std::binary_search(std::begin(op), std::end(op), c.front());
}

void readSourceCode(const std::string& path)
{
    std::string word;
    readUTF8TextFile(path, [&](Character && character) {
        if (isSpace(character.word) || isSeparator(character.word)) {
            if (!word.empty()) {
                std::cout << word << std::endl;
            }
            word.clear();
            return;
        }
        word += character.word;
    });
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

    for (auto & path : parser.getPaths()) {
        readSourceCode(path);
    }
    return 0;
}
