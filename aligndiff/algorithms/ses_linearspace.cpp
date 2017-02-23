// Copyright (c) 2017 mogemimi. Distributed under the MIT license.

#include "aligndiff.h"
#include <cassert>
#include <functional>

namespace aligndiff {

namespace {

// NOTE: Returns output as the `c1` vector reference.
void computeLevenshteinColumn(
    const std::string& text1,
    const std::string& text2,
    const std::size_t start1,
    const std::size_t size1,
    const std::size_t start2,
    const std::size_t size2,
    std::vector<size_t> & c1,
    std::vector<size_t> & c2,
    const bool reversedIteration = false)
{
    // NOTE:
    // This algorithm is based on dynamic programming, using only linear space.
    // It is O(N^2) time and O(N) space algorithm.

    assert(!text2.empty());
    assert(size2 > 0);
    assert((start2 + size2) <= text2.size());
    const auto columns = size2 + 1;
    assert(columns > 0);
    c1.resize(columns);
    c2.resize(columns);

    for (size_t i = 0; i < columns; ++i) {
        c1[i] = i;
    }

    if (size1 == 0) {
        return;
    }

    assert(!text1.empty());
    assert(size1 > 0);
    assert((start1 + size1) <= text1.size());
    const auto rows = size1 + 1;

    std::function<bool(size_t, size_t)> equal;
    if (!reversedIteration) {
        equal = [&](size_t a, size_t b) -> bool {
            return text1[a + start1] == text2[b + start2];
        };
    }
    else {
        equal = [&](size_t a, size_t b) -> bool {
            assert(size1 > 0);
            assert(size2 > 0);
            return text1[(start1 + size1) - (1 + a)] == text2[(start2 + size2) - (1 + b)];
        };
    }

    for (size_t row = 1; row < rows; row++) {
        c2[0] = row;
        for (size_t column = 1; column < columns; column++) {
            auto minCost = std::min(c1[column], c2[column - 1]) + 1;
            if (equal(row - 1, column - 1)) {
                minCost = std::min(c1[column - 1], minCost);
            }
            c2[column] = minCost;
        }
        // NOTE: Use std::swap() function instead of "c1 = c2" to assign faster.
        std::swap(c1, c2);
    }
}

struct SubstringRange {
    size_t start1;
    size_t size1;
    size_t start2;
    size_t size2;
};

} // end of anonymous namespace

std::vector<DiffEdit> computeShortestEditScript_LinearSpace(
    const std::string& text1,
    const std::string& text2)
{
    // NOTE:
    // This algorithm is based on Hirschberg's linear-space LCS algorithm in
    // "A linear space algorithm for computing maximal common subsequences",
    // Communications of the ACM, Volume 18 Issue 6, June 1975, pages 341-343

    std::vector<size_t> vertices(text2.size() + 1);
    std::vector<SubstringRange> stack;

    {
        SubstringRange param;
        param.start1 = 0;
        param.size1 = text1.size();
        param.start2 = 0;
        param.size2 = text2.size();
        stack.push_back(std::move(param));
    }

    std::vector<size_t> forwardColumn;
    std::vector<size_t> reverseColumn;
    std::vector<size_t> bufferColumn;

    forwardColumn.reserve(text1.size() + 1);
    reverseColumn.reserve(text1.size() + 1);
    bufferColumn.reserve(text1.size() + 1);

    while (!stack.empty()) {
        auto param = std::move(stack.back());
        stack.pop_back();

        assert((param.start1 + param.size1) <= text1.size());
        assert((param.start2 + param.size2) <= text2.size());

        if ((param.size1 == 0) || (param.size2 == 0)) {
            for (size_t i = 0; i <= param.size2; ++i) {
                vertices[param.start2 + i] = param.start1;
            }
            continue;
        }
        if (param.size2 == 1) {
            size_t k = 0;
            for (; k < param.size1; ++k) {
                if (text1[param.start1 + k] == text2[param.start2]) {
                    break;
                }
            }
            vertices[param.start2] = param.start1 + k;
            vertices[param.start2 + 1] = param.start1 + std::min(k + 1, param.size1);
            continue;
        }
        if (param.size1 == 1) {
            size_t y = param.start1;
            for (size_t i = 0; i < param.size2; ++i) {
                vertices[param.start2 + i] = y;
                if (text1[param.start1] == text2[param.start2 + i]) {
                    y = std::min(y + 1, param.start1 + param.size1);
                }
            }
            vertices[param.start2 + param.size2] = y;
            continue;
        }

        assert(param.size1 >= 2);
        assert(param.size2 >= 2);

        const auto sizeOverTwo = param.size2 / 2;
        const auto centerX = param.start2 + sizeOverTwo;
        computeLevenshteinColumn(
            text2,
            text1,
            param.start2,
            sizeOverTwo,
            param.start1,
            param.size1,
            forwardColumn,
            bufferColumn,
            false);
        computeLevenshteinColumn(
            text2,
            text1,
            centerX,
            param.size2 - sizeOverTwo,
            param.start1,
            param.size1,
            reverseColumn,
            bufferColumn,
            true);

        assert(forwardColumn.size() == reverseColumn.size());
        assert(forwardColumn.size() >= 2);
        assert(forwardColumn.capacity() == text1.size() + 1);
        assert(reverseColumn.capacity() == text1.size() + 1);
        assert(bufferColumn.capacity() == text1.size() + 1);

        size_t k = 0;
        size_t minVertex = std::numeric_limits<size_t>::max();
        for (size_t i = 0; i < forwardColumn.size(); ++i) {
            auto c = forwardColumn[i] + reverseColumn[reverseColumn.size() - (i + 1)];
            if (c < minVertex) {
                minVertex = c;
                k = i;
            }
        }

        {
            SubstringRange newParam;
            newParam.start1 = param.start1;
            newParam.size1 = k;
            newParam.start2 = param.start2;
            newParam.size2 = sizeOverTwo;
            assert(newParam.size1 <= param.size1);
            assert(newParam.size2 <= param.size2);
            assert(newParam.size2 > 0);
            stack.push_back(std::move(newParam));
        }
        {
            SubstringRange newParam;
            newParam.start1 = param.start1 + k;
            newParam.size1 = param.size1 - k;
            newParam.start2 = centerX;
            newParam.size2 = param.size2 - sizeOverTwo;
            assert(newParam.size1 <= param.size1);
            assert(newParam.size2 <= param.size2);
            stack.push_back(std::move(newParam));
        }
    }

#if !defined(NDEBUG) && defined(DEBUG)
    {
        size_t prev = 0;
        for (auto & v : vertices) {
            assert(v >= prev);
            assert(v <= text1.size());
            prev = v;
        }
    }
#endif

    std::vector<DiffEdit> edits;
    size_t y = 0;
    for (size_t x = 0; (x + 1) < vertices.size(); ++x) {
        for (; ((y + 1) < vertices[x + 1]) && (y < text1.size()); ++y) {
            edits.push_back(makeDiffEdit(text1[y], DiffOperation::Deletion));
        }
        if ((x + 1 < vertices.size()) && ((y + 1) == vertices[x + 1])) {
            if (text1[y] == text2[x]) {
                // NOTE: equality
                edits.push_back(makeDiffEdit(text1[y], DiffOperation::Equality));
            }
            else {
                // NOTE: substition
                edits.push_back(makeDiffEdit(text1[y], DiffOperation::Deletion));
                edits.push_back(makeDiffEdit(text2[x], DiffOperation::Insertion));
            }
            ++y;
            continue;
        }
        if (((x + 1) >= vertices.size()) || (vertices[x] == vertices[x + 1])) {
            edits.push_back(makeDiffEdit(text2[x], DiffOperation::Insertion));
        }
    }
    for (; y < text1.size(); ++y) {
        edits.push_back(makeDiffEdit(text1[y], DiffOperation::Deletion));
    }
    return edits;
}

} // namespace aligndiff
