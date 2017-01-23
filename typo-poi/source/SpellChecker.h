// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#pragma once

#include <memory>
#include <string>
#include <vector>

namespace somera {

struct SpellCheckResult {
    std::vector<std::string> suggestions;

    ///@brief `true` if the word is correctly spelled; `false` otherwise.
    bool correctlySpelled;
};

class SpellChecker {
public:
    virtual ~SpellChecker() = default;

    virtual SpellCheckResult Suggest(const std::string& word) = 0;

    virtual void AddWord(const std::string& word) = 0;

    virtual void RemoveWord(const std::string& word) = 0;
};

class SpellCheckerFactory final {
public:
    static std::shared_ptr<SpellChecker> Create();
};

} // namespace somera
