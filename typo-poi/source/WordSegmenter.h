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
    CplusplusKeywords,
    Integer,
    FloatNumber,
    DoxygenKeywords,
    UserDefined,
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
private:
    std::set<std::string> dictionary;

public:
    void setDictionary(const std::set<std::string>& dictionary);

    void parse(
        const std::string& text,
        std::function<void(const PartOfSpeech&)> callback);

private:
    void parse(
        const std::string& text,
        std::function<void(const PartOfSpeech&)> callback,
        bool recursive);
};

struct IdentifierWordSegmenter {
    static std::vector<std::string> parse(const std::string& text);
};

} // namespace somera
