// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#pragma once

#include <string>
#include <vector>

namespace somera {

enum class DiffOperation {
    Equality = 0,
    Insertion = 1,
    Deletion = -1,
};

struct DiffHunk {
    std::string text;
    DiffOperation operation;
};

std::vector<DiffHunk> computeDiff(const std::string& text1, const std::string& text2);

std::string computeLCSLinearSpace(
    const std::string& text1,
    const std::string& text2);

std::string computeLCSLinearSpace(
    const std::string& text1,
    const std::string& text2,
    std::size_t m,
    std::size_t n);

} // namespace somera
