// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#pragma once

#include "wordsegmenter.h"
#include "somera/Optional.h"
#include <functional>
#include <map>
#include <string>
#include <vector>

namespace somera {

struct TypoSource {
    std::string file;
    //SourceRange range;
};

struct Typo {
    std::string typo;
    std::vector<std::string> corrections;
    std::vector<TypoSource> sources;
};

class TypoMan final {
private:
    somera::WordSegmenter segmenter;
    std::map<std::string, Typo> typos;
    std::function<void(const Typo&)> onFoundTypo;
    int minimumWordSize;
    int maxCorrectWordCount;
    bool isStrictWhiteSpace;
    bool isStrictHyphen;
    bool isStrictLetterCase;
    bool ignoreBritishEnglish;

public:
    TypoMan() noexcept;

    void computeFromSentence(
        const std::string& sentence, const TypoSource& source);

    void computeFromIdentifier(const std::string& identifier);

    void computeFromWord(const std::string& word);

    void setMinimumWordSize(int wordSize);

    void setMaxCorrectWordCount(int maxCount);

    void setStrictWhiteSpace(bool strictWhiteSpace);

    void setStrictHyphen(bool strictHyphen);

    void setStrictLetterCase(bool strictLetterCase);

    void setIgnoreBritishEnglish(bool ignore);

    void setFoundCallback(std::function<void(const Typo&)> callback);
};

} // namespace somera
