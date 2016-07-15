// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#include "ConsoleColor.h"
#include "Typo.h"
#include "WordDiff.h"
#include "WordSegmenter.h"
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
    parser.setUsageText("typo-poi [options ...] [C/C++ file ...]");
    parser.addArgument("-h", Flag, "Display available options");
    parser.addArgument("-help", Flag, "Display available options");
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
    somera::TypoMan typos;
    typos.setStrictWhiteSpace(false);
    typos.setStrictHyphen(false);
    typos.setStrictLetterCase(false);
    typos.setIgnoreBritishEnglish(true);
    typos.setMinimumWordSize(3);
    typos.setMaxCorrectWordCount(4);
    typos.setFoundCallback([](const somera::Typo& typo) -> void
    {
        const auto& word = typo.typo;
        const auto& corrections = typo.corrections;
        if (corrections.empty()) {
            return;
        }

        using somera::DiffOperation;
        using somera::TerminalColor;
        {
            auto & correction = corrections.front();
            auto hunks = somera::computeDiff(word, correction);
            constexpr int indentSpaces = 18;
            std::stringstream fromStream;
            for (auto & hunk : hunks) {
                if (hunk.operation == DiffOperation::Equality) {
                    fromStream << hunk.text;
                }
                else if (hunk.operation == DiffOperation::Deletion) {
                    fromStream << somera::changeTerminalTextColor(
                        hunk.text,
                        TerminalColor::Black,
                        TerminalColor::Red);
                }
            }
            for (int i = indentSpaces - static_cast<int>(word.size()); i > 0; --i) {
                fromStream << " ";
            }
            std::stringstream toStream;
            for (auto & hunk : hunks) {
                if (hunk.operation == DiffOperation::Equality) {
                    toStream << hunk.text;
                }
                else if (hunk.operation == DiffOperation::Insertion) {
                    toStream << somera::changeTerminalTextColor(
                        hunk.text,
                        TerminalColor::White,
                        TerminalColor::Green);
                }
            }
            for (int i = indentSpaces - static_cast<int>(correction.size()); i > 0; --i) {
                toStream << " ";
            }
            std::printf("%s => %s", fromStream.str().c_str(), toStream.str().c_str());
        }

        if (corrections.size() > 1) {
            std::printf(" (");
            for (size_t i = 1; i < corrections.size(); ++i) {
                if (i > 1) {
                    std::printf(" ");
                }
                auto & correction = corrections[i];
                auto hunks = somera::computeDiff(word, correction);
                std::stringstream toStream;
                for (auto & hunk : hunks) {
                    if (hunk.operation == DiffOperation::Equality) {
                        toStream << hunk.text;
                    }
                    else if (hunk.operation == DiffOperation::Insertion) {
                        toStream << somera::changeTerminalTextColor(
                            hunk.text,
                            TerminalColor::Black,
                            TerminalColor::Blue);
                    }
                }
                std::printf("%s", toStream.str().c_str());
            }
            std::printf(")");
        }
        std::printf("\n");
    });
    auto onWord = [&](const std::string& sourceString) {
        somera::TypoSource source;
        source.file = path;
        typos.computeFromSentence(sourceString, source);
    };
    auto flush = [&](std::string && text) {
        somera::WordSegmenter segmenter;
        segmenter.parse(text, [&](const somera::PartOfSpeech& word) {
            onWord(word.text);
        });
    };
    std::string word;
    ReadUTF8TextFile(path, [&](Character && character) {
        if (IsSpace(character.word) || IsSeparator(character.word)) {
            if (!word.empty()) {
                std::string temp;
                std::swap(word, temp);
                flush(std::move(temp));
            }
            return;
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

    for (auto & path : parser.getPaths()) {
        ReadTextFileWithoutPedanticMode(path);
    }

    return 0;
}
