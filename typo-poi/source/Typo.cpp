// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "typo.h"
#include "editdistance.h"
#include "spellcheck.h"
#include "worddiff.h"
#include "somera/StringHelper.h"
#include <algorithm>
#include <cassert>
#include <iterator>
#include <utility>

namespace somera {
namespace {

enum class LanguageLocale {
    en_US,
    en_UK,
};

std::vector<std::string> correctWord(const std::string& word, LanguageLocale locale)
{
    NativeSpellCheckOptions options;
    options.language = [&] {
        if (locale == LanguageLocale::en_UK) {
            return "en_UK";
        }
        return "en_US";
    }();

    auto correction = somera::NativeSpellChecker::correctSpelling(word, options);
    if (correction.empty()) {
        return {};
    }
    auto corrections = somera::NativeSpellChecker::findClosestWords(word, options);
    if (corrections.size() > 4) {
        // NOTE:
        // If there are too many corrections, the program uses a lot of RAM.
        // So please should be resize the 'corrections'.
        corrections.resize(4);
    }
    if (std::find(std::begin(corrections), std::end(corrections), correction) == std::end(corrections)) {
        corrections.insert(std::begin(corrections), std::move(correction));
    }
    assert(!corrections.empty());
    return std::move(corrections);
}

bool exists(std::map<std::string, Typo>& typos, const std::string& word)
{
    return typos.find(word) != std::end(typos);
}

void addTypoSource(
    std::map<std::string, Typo>& typos,
    const std::string& word,
    TypoSource && source)
{
    auto iter = typos.find(word);
    assert(iter != std::end(typos));
    iter->second.sources.push_back(std::move(source));
}

void addTypo(std::map<std::string, Typo>& typos, Typo && typo)
{
    auto word = typo.typo;
    typos.emplace(word, std::move(typo));
}

template <class Container, typename Func>
void eraseIf(Container & container, Func func)
{
    container.erase(std::remove_if(
        std::begin(container), std::end(container), func),
        std::end(container));
}

void sortNearly(const std::string& word, std::vector<std::string> & corrections)
{
    const auto nearly = [&](auto& a, auto& b) {
        const auto fuzzyA = EditDistance::closestMatchFuzzyDistance(word, a);
        const auto fuzzyB = EditDistance::closestMatchFuzzyDistance(word, b);
        if (fuzzyA != fuzzyB) {
            return fuzzyA > fuzzyB;
        }
        const auto jwA = EditDistance::jaroWinklerDistance(word, a);
        const auto jwB = EditDistance::jaroWinklerDistance(word, b);
        if (jwA != jwB) {
            return jwA > jwB;
        }
        const auto lsA = EditDistance::levenshteinDistance(word, a);
        const auto lsB = EditDistance::levenshteinDistance(word, b);
        return lsA <= lsB;
    };
    std::sort(std::begin(corrections), std::end(corrections), nearly);
}

} // unnamed namespace

TypoMan::TypoMan() noexcept
    : minimumWordSize(3)
    , maxCorrectWordCount(4)
    , isStrictWhiteSpace(true)
    , isStrictHyphen(true)
    , isStrictLetterCase(true)
    , ignoreBritishEnglish(false)
{
    std::set<std::string> dictionary = {
        "jpg",
        "png",
        "mp3",
        "ogg",
        "json",
        "impl",
        "//!", // doxygen
        "NONINFRINGEMENT", // for MIT License
        "overrided" // => overriden
    };
    segmenter.setDictionary(dictionary);
}

void TypoMan::computeFromSentence(
    const std::string& sentence, const TypoSource& sourceIn)
{
    segmenter.parse(sentence, [&](const somera::PartOfSpeech& pos)
    {
        const auto word = pos.text;
        if (pos.tag != somera::PartOfSpeechTag::Raw &&
            pos.tag != somera::PartOfSpeechTag::EnglishWord) {
            return;
        }
        if (exists(typos, word)) {
            TypoSource source = sourceIn;
            addTypoSource(typos, word, std::move(source));
            return;
        }
        computeFromWord(word);
    });
}

void TypoMan::computeFromIdentifier(const std::string& identifier)
{
    auto words = somera::IdentifierWordSegmenter::parse(identifier);
    for (auto & word : words) {
        computeFromWord(word);
    }
}

void TypoMan::computeFromWord(const std::string& word)
{
    if (word.empty()) {
        return;
    }
    if (static_cast<int>(word.size()) < minimumWordSize) {
        return;
    }
    if (exists(typos, word)) {
        return;
    }
    auto corrections = correctWord(word, LanguageLocale::en_US);
    if (corrections.empty()) {
        return;
    }
    if (ignoreBritishEnglish) {
        std::vector<std::string> correctionsInUS;
        std::swap(corrections, correctionsInUS);
        auto correctionsInUK = correctWord(word, LanguageLocale::en_UK);
        std::set_intersection(
            std::begin(correctionsInUS),
            std::end(correctionsInUS),
            std::begin(correctionsInUK),
            std::end(correctionsInUK),
            std::back_inserter(corrections));
    }
    if (!isStrictWhiteSpace) {
        for (auto & correction : corrections) {
            auto hunks = somera::computeDiff(word, correction);
            std::string filtered;
            for (auto & hunk : hunks) {
                if (hunk.operation != DiffOperation::Equality
                    && hunk.text == " ") {
                    continue;
                }
                if (hunk.operation != DiffOperation::Deletion) {
                    filtered += hunk.text;
                }
            }
            correction = filtered;
        }
        eraseIf(corrections, [&](const std::string& correction) {
            return correction.empty();
        });
    }
    if (!isStrictHyphen) {
        for (auto & correction : corrections) {
            auto hunks = somera::computeDiff(word, correction);
            std::string filtered;
            for (auto & hunk : hunks) {
                if (hunk.operation != DiffOperation::Equality
                    && hunk.text == "-") {
                    continue;
                }
                if (hunk.operation != DiffOperation::Deletion) {
                    filtered += hunk.text;
                }
            }
            correction = filtered;
        }
        eraseIf(corrections, [&](const std::string& correction) {
            return correction.empty();
        });
    }
    if (!isStrictLetterCase) {
        eraseIf(corrections, [&](const std::string& correction) {
            return StringHelper::toLower(word) == StringHelper::toLower(correction);
        });
    }

    std::sort(std::begin(corrections), std::end(corrections));
    corrections.erase(
        std::unique(std::begin(corrections), std::end(corrections)),
        std::end(corrections));
    sortNearly(word, corrections);

    assert(maxCorrectWordCount > 0);
    if (static_cast<int>(corrections.size()) > maxCorrectWordCount) {
        corrections.resize(maxCorrectWordCount);
    }

    Typo typo;
    typo.typo = word;
    typo.corrections = std::move(corrections);
    if (onFoundTypo && !typo.corrections.empty()) {
        onFoundTypo(typo);
    }
    addTypo(typos, std::move(typo));
}

void TypoMan::setMinimumWordSize(int wordSize)
{
    assert(wordSize >= 0);
    this->minimumWordSize = std::max(wordSize, 0);
}

void TypoMan::setMaxCorrectWordCount(int maxCount)
{
    assert(maxCount > 0);
    this->maxCorrectWordCount = std::max(maxCount, 1);
}

void TypoMan::setStrictWhiteSpace(bool strictWhiteSpace)
{
    this->isStrictWhiteSpace = strictWhiteSpace;
}

void TypoMan::setStrictHyphen(bool strictHyphen)
{
    this->isStrictHyphen = strictHyphen;
}

void TypoMan::setStrictLetterCase(bool strictLetterCase)
{
    this->isStrictLetterCase = strictLetterCase;
}

void TypoMan::setIgnoreBritishEnglish(bool ignore)
{
    this->ignoreBritishEnglish = ignore;
}

void TypoMan::setFoundCallback(std::function<void(const Typo&)> callback)
{
    assert(callback);
    onFoundTypo = callback;
}

} // namespace somera
