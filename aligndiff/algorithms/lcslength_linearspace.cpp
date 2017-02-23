// Copyright (c) 2017 mogemimi. Distributed under the MIT license.

#include "aligndiff.h"
#include <cassert>

namespace aligndiff {
namespace {

std::vector<int> LCS_Column(
    const std::string& x,
    const std::string& y,
    std::size_t m,
    std::size_t n)
{
#if 0
    // NOTE: Algorithms on Strings, p266, LCS-COLUMN(x,m,y,n)
    std::vector<int> c1(m + 1);
    for (auto & c : c1) {
        c = 0;
    }
    std::vector<int> c2(m + 1);
    for (std::size_t j = 0; j < n; ++j) {
        c2[0] = 0;
        for (std::size_t i = 0; i < m; ++i) {
            if (x[i] == y[j]) {
                c2[i + 1] = c1[i] + 1;
            }
            else {
                c2[i + 1] = std::max(c1[i + 1], c2[i]);
            }
        }
        c1 = c2;
    }
    return c1;
#else
    const auto rows = static_cast<int>(x.size()) + 1;
    const auto columns = static_cast<int>(y.size()) + 1;

    std::vector<int> c1(columns);
    for (int i = 0; i < columns; ++i) {
        c1[i] = i;
    }
    std::vector<int> c2(columns);

    for (int row = 1; row < rows; row++) {
        c2[0] = row;
        for (int column = 1; column < columns; column++) {
            auto minCost = std::min(c1[column], c2[column - 1]) + 1;
            if (x[row - 1] == y[column - 1]) {
                minCost = std::min(c1[column - 1], minCost);
            }
            c2[column] = minCost;
        }
        c1 = c2;
    }

    return c1;
#endif
}

} // end of anonymous namespace

int computeLCSLength_LinearSpace(const std::string& text1, const std::string& text2)
{
    auto lcsColumn = LCS_Column(text1, text2, static_cast<int>(text1.size()), static_cast<int>(text2.size()));
    auto lcsLength = lcsColumn.back();

#if 0
    std::printf("{");
    for (int i = 0; i < (int)lcsColumn.size(); ++i) {
        std::printf("%2d, ", lcsColumn[i]);
    }
    std::printf("}\n");
#endif

    return lcsLength;
}

} // namespace aligndiff
