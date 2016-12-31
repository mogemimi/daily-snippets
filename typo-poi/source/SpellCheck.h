// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#pragma once

#include "SpellChecker.h"
#include <string>
#include <vector>

namespace somera {

struct NativeSpellCheckOptions {
    std::string language = "en_US";
};

struct NativeSpellChecker {
    static std::string correctSpelling(const std::string& word);

    static std::string correctSpelling(
        const std::string& word,
        const NativeSpellCheckOptions& options);

    static std::vector<std::string> findClosestWords(const std::string& word);

    static std::vector<std::string> findClosestWords(
        const std::string& word,
        const NativeSpellCheckOptions& options);
};

std::shared_ptr<SpellChecker> CreateSpellCheckerMac();

} // namespace somera
