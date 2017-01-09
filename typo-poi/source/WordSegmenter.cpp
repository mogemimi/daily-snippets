// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "wordsegmenter.h"
#include "utf8.h"
#include <cassert>
#include <cstdint>
#include <vector>
#include <regex>
#include <unordered_set>

namespace somera {
namespace {

#if 0
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
#endif

template <typename F>
std::vector<std::u32string> splitWords(const std::u32string& text, F isSeparator)
{
    std::vector<std::u32string> words;
    std::u32string wordBuffer;

    for (const auto & c : text) {
        if (isSeparator(c)) {
            // skip space
            if (!wordBuffer.empty()) {
                words.push_back(std::move(wordBuffer));
                wordBuffer.clear();
            }
            continue;
        }
        wordBuffer += c;
    }

    if (!wordBuffer.empty()) {
        words.push_back(std::move(wordBuffer));
        wordBuffer.clear();
    }

    return words;
}

bool isCompilerKeyword(const std::string& word)
{
    static std::unordered_set<std::string> keywords = {
        "alignas",
        "alignof",
        "and",
        "and_eq",
        "asm",
        "auto",
        "bitand",
        "bitor",
        "bool",
        "break",
        "case",
        "catch",
        "char",
        "char16_t",
        "char32_t",
        "class",
        "compl",
        "concept",
        "const",
        "constexpr",
        "const_cast",
        "continue",
        "decltype",
        "default",
        "delete",
        "do",
        "double",
        "dynamic_cast",
        "else",
        "enum",
        "explicit",
        "export",
        "extern",
        "false",
        "float",
        "for",
        "friend",
        "goto",
        "if",
        "inline",
        "int",
        "long",
        "mutable",
        "namespace",
        "new",
        "noexcept",
        "not",
        "not_eq",
        "nullptr",
        "operator",
        "or",
        "or_eq",
        "private",
        "protected",
        "public",
        "register",
        "reinterpret_cast",
        "requires",
        "return",
        "short",
        "signed",
        "sizeof",
        "static",
        "static_assert",
        "static_cast",
        "struct",
        "switch",
        "template",
        "this",
        "thread_local",
        "throw",
        "true",
        "try",
        "typedef",
        "typeid",
        "typename",
        "union",
        "unsigned",
        "using",
        "virtual",
        "void",
        "volatile",
        "wchar_t",
        "while",
        "xor",
        "xor_eq"
    };

    return keywords.find(word) != std::end(keywords);
}

PartOfSpeechTag findPartOfSpeechTag(const std::string& text)
{
    {
        if (isCompilerKeyword(text)) {
            return PartOfSpeechTag::CplusplusKeywords;
        }
    }
    {
        const std::regex re(R"([A-Z]*[a-z]+)");
        if (std::regex_match(text, re)) {
            return PartOfSpeechTag::EnglishWord;
        }
    }
    {
        const std::regex re(R"(\d+)");
        if (std::regex_match(text, re)) {
            return PartOfSpeechTag::Integer;
        }
    }
    {
        const std::regex re(R"((\d*\.\d+|\d+\.\d*)f?)");
        if (std::regex_match(text, re)) {
            return PartOfSpeechTag::FloatNumber;
        }
    }
    {
        // Contractions. For example: "don't"
        const std::regex re(R"([A-Z]?[a-z]+n't)");
        if (std::regex_match(text, re)) {
            return PartOfSpeechTag::EnglishWord;
        }
    }
    {
        const std::regex re(R"(git@\w+\..+)");
        if (std::regex_match(text, re)) {
            return PartOfSpeechTag::GitUrl;
        }
    }
    {
        const std::regex re(R"((http|https|ftp)://.+)");
        if (std::regex_match(text, re)) {
            return PartOfSpeechTag::Url;
        }
    }
    {
        const std::regex re(R"((\@|\\)((f(\$|\[|\]|\{|\}))|(\$|\@|\\|\&|\~|\<|\>|\#|\%)|([a-z]{1,16})))");
        if (std::regex_match(text, re)) {
            return PartOfSpeechTag::DoxygenKeywords;
        }
    }
    return PartOfSpeechTag::Raw;
}

bool isSpace(uint32_t c)
{
    return ::isspace(c) != 0;
}

bool isAsciiSymbols(uint32_t c)
{
    return (33 <= c && c <= 47)
        || (58 <= c && c <= 64)
        || (91 <= c && c <= 96)
        || (123 <= c && c <= 126);
}

} // unnamed namespace

void WordSegmenter::setDictionary(const std::set<std::string>& dictionaryIn)
{
    for (auto & w : dictionaryIn) {
        dictionary.insert(w);
    }
}

void WordSegmenter::parse(
    const std::string& utf8Text,
    std::function<void(const PartOfSpeech&)> readWord)
{
    parse(utf8Text, readWord, true);
}

void WordSegmenter::parse(
    const std::string& utf8Text,
    std::function<void(const PartOfSpeech&)> readWord,
    bool recursive)
{
    const auto text = toUtf32(utf8Text);
    const auto words = splitWords(text,
        recursive ? isSpace : isAsciiSymbols);

    std::vector<std::u32string> candidates;

    for (const auto& word : words) {
        PartOfSpeech pos;
        pos.text = toUtf8(word);
        pos.tag = PartOfSpeechTag::Raw;

        do {
            {
                auto iter = dictionary.find(pos.text);
                if (iter != std::end(dictionary)) {
                    pos.tag = PartOfSpeechTag::UserDefined;
                    break;
                }
            }
            {
                pos.tag = findPartOfSpeechTag(pos.text);
                if (pos.tag != PartOfSpeechTag::Raw) {
                    break;
                }
            }
        } while (0);

        if (pos.tag != PartOfSpeechTag::Raw) {
            readWord(pos);
        }
        else if (recursive) {
            assert(pos.tag == PartOfSpeechTag::Raw);
            parse(pos.text, readWord, false);
        }
        else {
            assert(pos.tag == PartOfSpeechTag::Raw);
            readWord(pos);
        }

    }
}

} // namespace somera
