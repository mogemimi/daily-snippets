// Copyright (c) 2017 mogemimi. Distributed under the MIT license.

#include "aligndiff.h"
#include <cassert>

namespace aligndiff {
namespace {

void fillTable(const std::string& text1, const std::string& text2, std::vector<int> & matrix)
{
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

    matrix.resize(rows * columns, 0);

    const auto mat = [&matrix, rows, columns](int row, int column) -> auto& {
        const auto index = row + rows * column;
        assert(index < static_cast<int>(matrix.size()));
        return matrix[index];
    };

    // NOTE:
    //   _ t y p e
    // _ 0 1 2 3 4
    // t 1 0 0 0 0
    // y 2 0 0 0 0
    // p 3 0 0 0 0
    // o 4 0 0 0 0

    for (int row = 1; row < rows; row++) {
        mat(row, 0) = row;
    }
    for (int column = 1; column < columns; column++) {
        mat(0, column) = column;
    }

    // NOTE:
    //   _ t y p e
    // _ 0 1 2 3 4
    // t 1 0 1 2 3
    // y 2 1 0 1 2
    // p 3 2 1 0 1
    // o 4 3 2 1 2

    for (int row = 1; row < rows; row++) {
        for (int column = 1; column < columns; column++) {
            auto minCost = std::min(mat(row - 1, column), mat(row, column - 1)) + 1;
            if (text1[row - 1] == text2[column - 1]) {
                minCost = std::min(mat(row - 1, column - 1), minCost);
            }
            mat(row, column) = minCost;
        }
    }
}

} // end of anonymous namespace

void printEditGraphTableAsString(const std::string& text1, const std::string& text2)
{
    const auto rows = static_cast<int>(text1.size()) + 1;
    const auto columns = static_cast<int>(text2.size()) + 1;

    std::vector<int> matrix;
    fillTable(text1, text2, matrix);

    const auto mat = [&matrix, rows, columns](int row, int column) -> auto& {
        const auto index = row + rows * column;
        assert(index < static_cast<int>(matrix.size()));
        return matrix[index];
    };

    std::printf("\n");
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            std::printf("%3d", mat(row, column));
        }
        std::printf("\n");
    }
    std::printf("\n");
}

int computeLevenshteinDistance_DynamicProgramming(const std::string& text1, const std::string& text2)
{
    std::vector<int> matrix;
    fillTable(text1, text2, matrix);
    
    // NOTE: The following code is the same as "return mat(rows - 1, columns - 1);".
    return matrix.back();
}

} // namespace aligndiff
