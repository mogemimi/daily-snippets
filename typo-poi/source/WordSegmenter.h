// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#pragma once

#include <functional>
#include <string>

namespace somera {

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

struct PartOfSpeech {
    std::string text;
    PartOfSpeechTag tag;
};

class WordSegmenter {
public:
    void Parse(
        const std::string& text,
        std::function<void(const PartOfSpeech&)> callback);
};

} // namespace somera
