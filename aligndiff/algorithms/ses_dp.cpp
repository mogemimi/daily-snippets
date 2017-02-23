// Copyright (c) 2017 mogemimi. Distributed under the MIT license.

#include "aligndiff.h"
#include "optional.h"
#include <cassert>

namespace aligndiff {

std::vector<DiffEdit> computeShortestEditScript_DynamicProgramming(
    const std::string& text1,
    const std::string& text2)
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

#if 0
    std::printf("\n");
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            std::printf("%3d", mat(row, column));
        }
        std::printf("\n");
    }
    std::printf("\n");
#endif

    std::vector<DiffEdit> edits;

    int row = rows - 1;
    int column = columns - 1;
    aligndiff::optional<int> longestCommonSubsequence;

    while ((row > 0) && (column > 0)) {
        // edit costs
        const auto deletion = mat(row - 1, column);
        const auto insertion = mat(row, column - 1);
        const auto equality = mat(row - 1, column - 1);

        if (longestCommonSubsequence
            && (*longestCommonSubsequence == mat(row, column))
            && (text1[row - 1] == text2[column - 1])) {
            edits.push_back(makeDiffEdit(text1[row - 1], DiffOperation::Equality));
            --row;
            --column;
            continue;
        }

        longestCommonSubsequence = aligndiff::nullopt;

        if ((text1[row - 1] == text2[column - 1])
            && (equality < deletion)
            && (equality < insertion)) {
            edits.push_back(makeDiffEdit(text1[row - 1], DiffOperation::Equality));
            --row;
            --column;
            longestCommonSubsequence = mat(row, column);
        }
        else if (deletion < insertion) {
            edits.push_back(makeDiffEdit(text1[row - 1], DiffOperation::Deletion));
            --row;
        }
        else {
            edits.push_back(makeDiffEdit(text2[column - 1], DiffOperation::Insertion));
            --column;
        }
    }

    while (column > 0) {
        edits.push_back(makeDiffEdit(text2[column - 1], DiffOperation::Insertion));
        --column;
    }
    while (row > 0) {
        edits.push_back(makeDiffEdit(text1[row - 1], DiffOperation::Deletion));
        --row;
    }

    std::reverse(std::begin(edits), std::end(edits));
    return edits;
}

} // namespace aligndiff
