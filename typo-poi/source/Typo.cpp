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

template <class Container, typename Func>
void eraseIf(Container & container, Func func)
{
    container.erase(std::remove_if(
        std::begin(container), std::end(container), func),
        std::end(container));
}

} // unnamed namespace

TypoCache::TypoCache()
    : maxCacheSize(20)
{
    setCapacity(maxCacheSize);
}

bool TypoCache::exists(const std::string& misspelledWord) const
{
    auto iter = std::find_if(std::rbegin(typos), std::rend(typos), [&](const TypoCacheInfo& info) {
        return info.misspelledWord == misspelledWord;
    });
    return (iter != std::rend(typos));
}

void TypoCache::setCapacity(size_t capacity)
{
    assert(capacity > 1);
    maxCacheSize = std::max<size_t>(10, capacity);
    if (typos.size() > maxCacheSize) {
        typos.resize(maxCacheSize);
        typos.shrink_to_fit();
    }
    if (typos.capacity() < maxCacheSize) {
        typos.reserve(maxCacheSize);
    }
    assert(typos.size() <= maxCacheSize);
    assert(typos.capacity() <= maxCacheSize);
}

void TypoCache::insert(Typo && typo)
{
    assert(typos.size() <= typos.capacity());

    auto iter = std::find_if(std::rbegin(typos), std::rend(typos), [&](const TypoCacheInfo& info) {
        return info.misspelledWord == typo.misspelledWord;
    });

    if (iter == std::rend(typos)) {
        if (typos.size() > 10) {
            std::sort(std::rbegin(typos), std::next(std::rbegin(typos), typos.size() / 3),
                [](const TypoCacheInfo& a, const TypoCacheInfo& b) {
                    return a.count > b.count;
                });
        }
        if (typos.size() >= maxCacheSize) {
            assert(maxCacheSize > 0);
            assert(!typos.empty());
            typos.erase(std::begin(typos));
        }
        assert(typos.size() <= typos.capacity());
        TypoCacheInfo cacheInfo;
        cacheInfo.misspelledWord = std::move(typo.misspelledWord);
        cacheInfo.count = 1;
        typos.push_back(std::move(cacheInfo));
    }
    else {
        TypoCacheInfo cacheInfo;
        std::swap(*iter, cacheInfo);
        cacheInfo.count++;
        typos.erase(std::next(iter).base());
    }
}

TypoMan::TypoMan() noexcept
    : minimumWordSize(3)
    , maxCorrectWordCount(4)
    , isStrictWhiteSpace(true)
    , isStrictHyphen(true)
    , isStrictLetterCase(true)
{
    spellChecker = SpellCheckerFactory::Create();
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
        if (isCacheEnabled && cache.exists(word)) {
            return;
        }
        computeFromWord(word);
    });
}

void TypoMan::computeFromWord(const std::string& word)
{
    if (word.empty()) {
        return;
    }
    if (static_cast<int>(word.size()) < minimumWordSize) {
        return;
    }
    if (isCacheEnabled && cache.exists(word)) {
        return;
    }

    auto suggestResult = spellChecker->Suggest(word);
    if (suggestResult.suggestions.empty()) {
        return;
    }
    if (!isStrictWhiteSpace) {
        for (auto & correction : suggestResult.suggestions) {
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
            if (filtered == word) {
                return;
            }
            correction = filtered;
        }
        eraseIf(suggestResult.suggestions, [&](const std::string& correction) {
            return correction.empty();
        });
    }
    if (!isStrictHyphen) {
        for (auto & correction : suggestResult.suggestions) {
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
            if (filtered == word) {
                return;
            }
            correction = filtered;
        }
        eraseIf(suggestResult.suggestions, [&](const std::string& correction) {
            return correction.empty();
        });
    }

    assert(maxCorrectWordCount > 0);
    if (static_cast<int>(suggestResult.suggestions.size()) > maxCorrectWordCount) {
        suggestResult.suggestions.resize(maxCorrectWordCount);
    }

    Typo typo;
    typo.misspelledWord = word;
    typo.corrections = std::move(suggestResult.suggestions);
    if (onFoundTypo && !typo.corrections.empty()) {
        onFoundTypo(typo);
    }
    if (isCacheEnabled) {
        cache.insert(std::move(typo));
    }
}

void TypoMan::setSpellChecker(const std::shared_ptr<SpellChecker>& spellCheckerIn)
{
    this->spellChecker = spellCheckerIn;
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

void TypoMan::setCacheEnabled(bool cacheEnabled)
{
    this->isCacheEnabled = cacheEnabled;
}

void TypoMan::setCacheSize(std::size_t cacheSize)
{
    assert(cacheSize > 0);
    this->cache.setCapacity(cacheSize);
}

void TypoMan::setFoundCallback(std::function<void(const Typo&)> callback)
{
    assert(callback);
    onFoundTypo = callback;
}

} // namespace somera
