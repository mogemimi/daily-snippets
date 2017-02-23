// Copyright (c) 2017 mogemimi. Distributed under the MIT license.

#include "aligndiff.h"
#include <cassert>

namespace aligndiff {

int computeLCSLength_DynamicProgramming(
    const std::string& text1,
    const std::string& text2)
{
    if (text1.empty() || text2.empty()) {
        return 0;
    }

    const auto rows = static_cast<int>(text1.size()) + 1;
    const auto columns = static_cast<int>(text2.size()) + 1;

    // NOTE:
    // text1 = "type"
    // text2 = "typo"

    // NOTE:
    //   _ t y p e
    // _ 0 0 0 0 0
    // t 0 0 0 0 0
    // y 0 0 0 0 0
    // p 0 0 0 0 0
    // o 0 0 0 0 0

    std::vector<int> matrix(rows * columns, 0);

    const auto mat = [&matrix, rows, columns](int row, int column) -> auto& {
        const auto index = row + rows * column;
        assert(index < static_cast<int>(matrix.size()));
        return matrix[index];
    };

    // NOTE:
    //   _ t y p e
    // _ 0 0 0 0 0
    // t 0 0 0 0 0
    // y 0 0 0 0 0
    // p 0 0 0 0 0
    // o 0 0 0 0 0

    for (int row = 1; row < rows; row++) {
        mat(row, 0) = 0;
    }
    for (int column = 1; column < columns; column++) {
        mat(0, column) = 0;
    }

    // NOTE:
    //   _ t y p e
    // _ 0 0 0 0 0
    // t 0 1 1 1 1
    // y 0 1 2 2 2
    // p 0 1 2 3 3
    // o 0 1 2 3 3

    for (int row = 1; row < rows; row++) {
        for (int column = 1; column < columns; column++) {
            if (text1[row - 1] == text2[column - 1]) {
                mat(row, column) = mat(row - 1, column - 1) + 1;
            }
            else {
                mat(row, column) = std::max(mat(row - 1, column), mat(row, column - 1));
            }
        }
    }
    return mat(rows - 1, columns - 1);
}

} // namespace aligndiff
