// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "worddiff.h"
#include "somera/Optional.h"
#include "EditDistance.h"
#include <algorithm>
#include <cassert>
#include <utility>

namespace somera {

std::vector<DiffHunk> computeDiff(const std::string& text1, const std::string& text2)
{
    if (text1.empty() && text2.empty()) {
        return {};
    }

    const auto rows = static_cast<int>(text1.size()) + 1;
    const auto columns = static_cast<int>(text2.size()) + 1;

    std::vector<int> matrix(rows * columns, 0);

    const auto mat = [&matrix, rows, columns](int row, int column) -> auto& {
        const auto index = row + rows * column;
        assert(index < static_cast<int>(matrix.size()));
        return matrix[index];
    };

    for (int row = 1; row < rows; row++) {
        mat(row, 0) = row;
    }
    for (int column = 1; column < columns; column++) {
        mat(0, column) = column;
    }

    // levenshtein distance
    for (int row = 1; row < rows; row++) {
        for (int column = 1; column < columns; column++) {
            auto minCost = std::min(mat(row - 1, column), mat(row, column - 1)) + 1;
            if (text1[row - 1] == text2[column - 1]) {
                minCost = std::min(mat(row - 1, column - 1), minCost);
            }
            mat(row, column) = minCost;
        }
    }

#if 1
    std::printf("\n");
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            std::printf("%3d", mat(row, column));
        }
        std::printf("\n");
    }
    std::printf("\n");
#endif

    std::vector<DiffHunk> hunks;

    int row = rows - 1;
    int column = columns - 1;
    Optional<int> longestCommonSubsequence;

    while ((row > 0) && (column > 0)) {
        // edit costs
        const auto deletion = mat(row - 1, column);
        const auto insertion = mat(row, column - 1);
        const auto equality = mat(row - 1, column - 1);

        if (longestCommonSubsequence
            && (*longestCommonSubsequence == mat(row, column))
            && (text1[row - 1] == text2[column - 1])) {
            DiffHunk hunk;
            hunk.text = text1[row - 1];
            hunk.operation = DiffOperation::Equality;
            hunks.push_back(std::move(hunk));
            --row;
            --column;
            continue;
        }

        longestCommonSubsequence = NullOpt;

        if ((text1[row - 1] == text2[column - 1])
            && (equality < deletion)
            && (equality < insertion)) {
            DiffHunk hunk;
            hunk.text = text1[row - 1];
            hunk.operation = DiffOperation::Equality;
            hunks.push_back(std::move(hunk));
            --row;
            --column;
            longestCommonSubsequence = mat(row, column);
        }
        else if (deletion < insertion) {
            DiffHunk hunk;
            hunk.text = text1[row - 1];
            hunk.operation = DiffOperation::Deletion;
            hunks.push_back(std::move(hunk));
            --row;
        }
        else {
            DiffHunk hunk;
            hunk.text = text2[column - 1];
            hunk.operation = DiffOperation::Insertion;
            hunks.push_back(std::move(hunk));
            --column;
        }
    }

    while (column > 0) {
        DiffHunk hunk;
        hunk.text = text2[column - 1];
        hunk.operation = DiffOperation::Insertion;
        hunks.push_back(std::move(hunk));
        --column;
    }

    while (row > 0) {
        DiffHunk hunk;
        hunk.text = text1[row - 1];
        hunk.operation = DiffOperation::Deletion;
        hunks.push_back(std::move(hunk));
        --row;
    }

    std::reverse(std::begin(hunks), std::end(hunks));
    {
        // merge
        std::vector<DiffHunk> oldHunks;
        std::swap(hunks, oldHunks);

        for (auto & h : oldHunks) {
            if (hunks.empty() || (hunks.back().operation != h.operation)) {
                hunks.push_back(std::move(h));
            }
            else {
                assert(hunks.back().operation == h.operation);
                hunks.back().text += h.text;
            }
        }
    }
    return hunks;
}

std::string computeLCSLinearSpace(
    const std::string& text1,
    const std::string& text2)
{
    return computeLCSLinearSpace(text1, text2, text1.size(), text2.size());
}

bool includeAlph(char character, const std::string& text)
{
    for (auto & c : text) {
        if (character == c) {
            return true;
        }
    }
    return false;
}


std::string substring(const std::string& text, int start, int end)
{
    assert(start <= end);
    if (start == end) {
        return "";
    }
    assert(start < end);
    return text.substr(start, end - start);
}

std::string computeLCSLinearSpace(
    const std::string& text1,
    const std::string& text2,
    std::size_t m,
    std::size_t n)
{
    assert(text1.size() <= m);
    assert(text2.size() <= n);

    if (m == 1 && includeAlph(text1[0], text2)) {
        std::string result;
        result += text1[0];
        return result;
    }
    else if (n == 1 && includeAlph(text2[0], text1)) {
        std::string result;
        result += text2[0];
        return result;
    }
    else if (m == 0 || m == 1 || n == 0 || n == 1) {
        return "";
    }

    std::vector<int> C1 = EditDistance::LCS_Column(text1, text2, m, n / 2);
    std::vector<int> P1(m + 1);

    for (int i = 0; i <= static_cast<int>(m); ++i) {
        P1[i] = i;
    }

    for (int j = static_cast<int>(n / 2) + 1; j <= static_cast<int>(n); ++j) {
        std::vector<int> C2(m + 1);
        std::vector<int> P2(m + 1);
        C2[0] = 0;
        P2[0] = 0;
        for (int i = 1; i <= static_cast<int>(m); ++i) {
            if (text1[i - 1] == text2[j - 1]) {
                C2[i] = C1[i - 1] + 1;
                P2[i] = P1[i - 1];
            }
            else if (C1[i] > C2[i - 1]) {
                C2[i] = C1[i];
                P2[i] = P1[i];
            }
            else {
                C2[i] = C2[i - 1];
                P2[i] = P2[i - 1];
            }
        }
        C1 = C2;
        P1 = P2;
    }

    auto k = P1[m - 1];
    auto halfN = static_cast<int>(n / 2);
    assert(halfN > 0);
    auto u = computeLCSLinearSpace(
        substring(text1, 0, k - 1),
        substring(text2, 0, halfN - 1),
        k,
        halfN);
    auto v = computeLCSLinearSpace(
        substring(text1, k, m - 1),
        substring(text2, halfN, n - 1),
        m - k,
        n - halfN);

    return u + v;
}

} // namespace somera
