// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#include "ConsoleColor.h"
#include "Replacement.h"
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
    using Type = somera::CommandLineArgumentType;
    parser.setUsageText("typo-poi [options ...] [C/C++ file ...]");
    parser.addArgument("-h", Type::Flag, "Display available options");
    parser.addArgument("-help", Type::Flag, "Display available options");
    parser.addArgument("-v", Type::Flag, "Display version");
    parser.addArgument("-dict", Type::JoinedOrSeparate, "Dictionary file");
}

struct UTF8Character {
    std::string buffer;
    somera::SourceRange byteRange;
    std::size_t column = 0;
    std::size_t line = 0;
};

class UTF8Chunk {
public:
    UTF8Chunk()
    {
    }

    UTF8Chunk(UTF8Chunk && other)
    {
        buffer = std::move(other.buffer);
        byteRange = std::move(other.byteRange);
        range = std::move(other.range);
    }

    UTF8Chunk & operator=(UTF8Chunk && other)
    {
        buffer = std::move(other.buffer);
        byteRange = std::move(other.byteRange);
        range = std::move(other.range);
        return *this;
    }

    UTF8Chunk& operator+=(const UTF8Character& c)
    {
        if (buffer.empty()) {
            assert(byteRange.GetOffset() == 0);
            assert(byteRange.GetLength() == 0);
            buffer = c.buffer;
            byteRange = somera::SourceRange(
                c.byteRange.GetOffset(),
                c.byteRange.GetLength());
            range = somera::SourceRange(c.column, 1);
            return *this;
        }

        assert(!buffer.empty());
        assert(buffer.size() == byteRange.GetLength());
        assert(!byteRange.Contains(c.byteRange));
        assert(byteRange.GetLength() > 0 && range.GetLength() > 0);
        assert(byteRange.GetOffset() + byteRange.GetLength() == c.byteRange.GetOffset());
        assert(range.GetOffset() + range.GetLength() == c.column);

        buffer += c.buffer;
        byteRange = somera::SourceRange(
            byteRange.GetOffset(),
            byteRange.GetLength() + c.byteRange.GetLength());
        range = somera::SourceRange(
            range.GetOffset(),
            range.GetLength() + 1);
        return *this;
    }

    std::string GetString() const noexcept
    {
        return buffer;
    }

    bool Empty() const noexcept
    {
        assert(buffer.empty()
            ? (byteRange.GetLength() == 0 && range.GetLength() == 0)
            : (byteRange.GetLength() > 0 && range.GetLength() > 0));
        return buffer.empty();
    }

    void Clear() noexcept
    {
        buffer.clear();
        byteRange = somera::SourceRange(0, 0);
        range = somera::SourceRange(0, 0);
    }

private:
    std::string buffer;
    somera::SourceRange byteRange;
    somera::SourceRange range;
};

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

void ReadUTF8TextFile(
    const std::string& path, const std::function<void(UTF8Character&&)>& callback)
{
    std::error_code errorCode;
    auto fileSize = somera::FileSystem::getFileSize(path, errorCode);

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
    std::size_t byteIndex = 0;
    std::size_t utf8CharacterCount = 0;
    std::size_t lineCount = 1;
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
            std::cerr
                << "error: Invalid UTF-8 byte sequence at "
                << path
                << ":"
                << lineCount
                << ":"
                << columnCount
                << "."
                << std::endl;
            break;
        }

        const auto readBytes = getNumBytesForUTF8(buffer.front());

        assert(readBytes <= readableSize);
        assert((byteIndex + readBytes) <= fileSize);

        UTF8Character character;
        character.buffer.assign(reinterpret_cast<char*>(buffer.data()), readBytes);
        character.column = columnCount;
        character.line = lineCount;
        character.byteRange = somera::SourceRange(byteIndex, readBytes);

        assert(callback);
        callback(std::move(character));

        byteIndex += readBytes;
        utf8CharacterCount++;
        columnCount++;

        if (readBytes < readableSize) {
            input.seekg(byteIndex, std::ios_base::beg);
        }

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

void ReadTextFileWithoutPedanticMode(somera::TypoMan & typos, const std::string& path)
{
    auto onWord = [&](const std::string& sourceString) {
        somera::TypoSource source;
        source.location.filePath = path;
        typos.computeFromSentence(sourceString, source);
    };
    auto flush = [&](UTF8Chunk && chunk) {
        somera::WordSegmenter segmenter;
        segmenter.parse(chunk.GetString(), [&](const somera::PartOfSpeech& word) {
            onWord(word.text);
        });
    };
    UTF8Chunk currentLine;
    UTF8Chunk word;
    ReadUTF8TextFile(path, [&](UTF8Character && character) {
        currentLine += character;
        if (IsSpace(character.buffer)) {
            if (!word.Empty()) {
                UTF8Chunk temp;
                std::swap(word, temp);
                flush(std::move(temp));
            }
            currentLine.Clear();
            return;
        }
        word += character;
    });
}

void showTypoInConsole(const somera::Typo& typo)
{
    const auto& misspelledWord = typo.misspelledWord;
    const auto& corrections = typo.corrections;
    if (corrections.empty()) {
        return;
    }

    using somera::DiffOperation;
    using somera::TerminalColor;
    {
        auto & correction = corrections.front();
        auto hunks = somera::computeDiff(misspelledWord, correction);
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
        for (int i = indentSpaces - static_cast<int>(misspelledWord.size()); i > 0; --i) {
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
            auto hunks = somera::computeDiff(misspelledWord, correction);
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
        std::cout << "typo-poi version 0.1.0 (July 19, 2016)" << std::endl;
        return 0;
    }
    if (parser.getPaths().empty()) {
        std::cerr << "error: no input file" << std::endl;
        return 1;
    }

    std::vector<std::string> dictionaryPaths = parser.getValues("-dict");

    auto spellChecker = somera::SpellCheckerFactory::Create();
    for (auto & path : dictionaryPaths) {
        ReadDictionaryFile(path, [&](const std::string& word) {
            spellChecker->AddWord(word);
        });
    }

    somera::TypoMan typos;
    typos.setSpellChecker(spellChecker);
    typos.setStrictWhiteSpace(false);
    typos.setStrictHyphen(false);
    typos.setMinimumWordSize(3);
    typos.setMaxCorrectWordCount(4);
    typos.setCacheEnabled(true);
    typos.setCacheSize(100);
    typos.setFoundCallback([](const somera::Typo& typo) -> void
    {
        showTypoInConsole(typo);
    });

    for (auto & path : parser.getPaths()) {
        auto ext = std::get<1>(somera::FileSystem::splitExtension(path));
        if (ext == ".png"
            || ext == ".jpg"
            || ext == "exe"
            || ext == ".DS_Store"
            || ext == ".o"
            || ext == ".a"
            || ext == ".d"
            || ext == ".lib"
            || ext == ".dll") {
            continue;
        }
        ReadTextFileWithoutPedanticMode(typos, path);
    }

    return 0;
}
