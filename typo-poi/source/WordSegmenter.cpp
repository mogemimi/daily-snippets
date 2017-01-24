// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "WordSegmenter.h"
#include <cassert>
#include <cstdint>
#include <vector>
#include <regex>
#include <unordered_set>

namespace somera {
namespace {

bool IsSeparator(char32_t c)
{
    // NOTE: Ascii characters without alphabet, numbers and [-'].
    std::string separators = "!\"#$%&()*+,./:;<=>?@[\\]^`{|}~";
    assert(std::is_sorted(separators.begin(), separators.end()));
    return std::binary_search(std::begin(separators), std::end(separators), c);
}

bool IsConcatenator(char32_t c)
{
    std::string separators = "'-";
    assert(std::is_sorted(separators.begin(), separators.end()));
    return std::binary_search(std::begin(separators), std::end(separators), c);
}

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
    std::function<void(const PartOfSpeech&)> callback)
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
            callback({prefix, PartOfSpeechTag::Integer});
        }
        else if (std::regex_match(prefix, std::regex(R"(0x[\dA-Fa-f]+)"))) {
            // hex integer
            callback({prefix, PartOfSpeechTag::IntegerHex});
        }
        else if (std::regex_match(prefix, std::regex(R"(0b[01]+)"))) {
            // binary integer
            callback({prefix, PartOfSpeechTag::IntegerBinary});
        }
        else if (std::regex_match(prefix, std::regex(R"((\d*\.\d+|\d+\.\d*)f?)"))) {
            // float number
            callback({prefix, PartOfSpeechTag::FloatNumber});
        }
        else {
            callback({prefix, PartOfSpeechTag::Word});
        }

        if (!suffix.empty()) {
            callback({suffix, PartOfSpeechTag::Symbol});
        }
    };
    auto flushSeparator = [&] {
        if (!separator.empty()) {
            callback({separator, PartOfSpeechTag::Spaces});
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

} // end anonymous namespace

void WordSegmenter::Parse(
    const std::string& str,
    std::function<void(const PartOfSpeech&)> callback)
{
    auto splitStrings = SplitBySpace(str);

    for (auto & tuple : splitStrings) {
        auto & text = std::get<0>(tuple);
        auto & tag = std::get<1>(tuple);
        if (tag == PartOfSpeechTag::Spaces) {
            callback(PartOfSpeech{text, PartOfSpeechTag::Spaces});
            continue;
        }
        if (std::regex_match(text, std::regex(R"(git@\w+\..+)"))) {
            callback(PartOfSpeech{text, PartOfSpeechTag::GitUrl});
            continue;
        }
        if (std::regex_match(text, std::regex(R"((http|https|ftp)://.+)"))) {
            callback(PartOfSpeech{text, PartOfSpeechTag::Url});
            continue;
        }
        TokenizeByAsciiSymbols(text, callback);
    }
}

} // namespace somera
