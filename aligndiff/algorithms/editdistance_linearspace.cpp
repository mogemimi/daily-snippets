// Copyright (c) 2017 mogemimi. Distributed under the MIT license.

#include "aligndiff.h"
#include <cassert>

namespace aligndiff {

int computeLevenshteinDistance_LinearSpace(
    const std::string& text1,
    const std::string& text2)
{
    // NOTE:
    // This algorithm is based on dynamic programming, using only linear space.
    // It is O(N^2) time and O(N) space algorithm.

    const auto rows = static_cast<int>(text1.size()) + 1;
    const auto columns = static_cast<int>(text2.size()) + 1;
    std::vector<int> c1(columns);
    std::vector<int> c2(columns);

    for (int i = 0; i < columns; ++i) {
        c1[i] = i;
    }

    for (int row = 1; row < rows; row++) {
        c2[0] = row;
        for (int column = 1; column < columns; column++) {
            auto minCost = std::min(c1[column], c2[column - 1]) + 1;
            if (text1[row - 1] == text2[column - 1]) {
                minCost = std::min(c1[column - 1], minCost);
            }
            c2[column] = minCost;
        }
        // NOTE: Use std::swap() function instead of "c1 = c2" to assign faster.
        std::swap(c1, c2);
    }
    return c1.back();
}

} // namespace aligndiff
