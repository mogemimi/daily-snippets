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

template <typename T>
struct DiffHunk {
    std::basic_string<T> text;
    DiffOperation operation;
};

std::vector<DiffHunk<char>> computeDiff(
    const std::string& text1,
    const std::string& text2);

std::vector<DiffHunk<char>> computeDiff_DynamicProgramming(
    const std::string& text1,
    const std::string& text2);

std::vector<DiffHunk<char>> computeDiff_ONDGreedyAlgorithm(
    const std::string& text1,
    const std::string& text2);

std::string computeLCSLinearSpace(
    const std::string& text1,
    const std::string& text2);

std::string computeLCSLinearSpace(
    const std::string& text1,
    const std::string& text2,
    std::size_t m,
    std::size_t n);

} // namespace somera
