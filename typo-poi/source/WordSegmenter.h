// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#pragma once

#include <string>
#include <functional>
#include <vector>
#include <set>

namespace somera {

enum class PartOfSpeechTag {
    Raw,
    EnglishWord,
    GitUrl,
    Url,
    Integer,
    FloatNumber,
    DoxygenKeywords,
//    EmailAddress,
//    Copyright,
//    LicenseDescription,
};

struct PartOfSpeech {
    PartOfSpeechTag tag;
    std::string text;
    //Range range;
};

class WordSegmenter {
public:
    void parse(
        const std::string& text,
        std::function<void(const PartOfSpeech&)> callback);

private:
    void parse(
        const std::string& text,
        std::function<void(const PartOfSpeech&)> callback,
        bool recursive);
};

} // namespace somera
