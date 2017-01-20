// Copyright (c) 2017 mogemimi. Distributed under the MIT license.

#include "EditDistance.h"
#include "WordDiff.h"
#include "Optional.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <experimental/optional>
#include <iomanip>
#include <cassert>
#include <functional>

namespace {

using namespace somera;

std::vector<int> computeLevenshteinColumn(
    const std::string& text1,
    const std::string& text2,
    const std::size_t start1,
    const std::size_t size1,
    const std::size_t start2,
    const std::size_t size2,
    const bool reversedIteration = false)
{
    // NOTE:
    // This algorithm is based on dynamic programming, using only linear space.
    // It is O(N^2) time and O(N) space algorithm.

    assert(!text2.empty());
    assert(size2 > 0);
    assert((start2 + size2) <= text2.size());
    const auto columns = static_cast<int>(size2) + 1;
    assert(columns > 0);
    std::vector<int> c1(columns);
    std::vector<int> c2(columns);

    for (int i = 0; i < columns; ++i) {
        c1[i] = i;
    }

    if (size1 == 0) {
        return c1;
    }

    assert(!text1.empty());
    assert(size1 > 0);
    assert((start1 + size1) <= text1.size());
    const auto rows = static_cast<int>(size1) + 1;

    std::function<bool(int, int)> equal;
    if (!reversedIteration) {
        equal = [&](int a, int b) -> bool {
            return text1[a + start1] == text2[b + start2];
        };
    }
    else {
        equal = [&](int a, int b) -> bool {
            assert(size1 > 0);
            assert(size2 > 0);
            return text1[(start1 + size1 - 1) - a] == text2[(start2 + size2 - 1) - b];
        };
    }

    for (int row = 1; row < rows; row++) {
        c2[0] = row;
        for (int column = 1; column < columns; column++) {
            auto minCost = std::min(c1[column], c2[column - 1]) + 1;
            if (equal(row - 1, column - 1)) {
                minCost = std::min(c1[column - 1], minCost);
            }
            c2[column] = minCost;
        }
        // NOTE: Use std::swap() function instead of "c1 = c2" to assign faster.
        std::swap(c1, c2);
    }
    return c1;
}

struct SubstringRange {
    size_t start1;
    size_t size1;
    size_t start2;
    size_t size2;
};

DiffHunk<char> MakeDiffHunk(char text, DiffOperation operation)
{
    DiffHunk<char> hunk;
    hunk.text = text;
    hunk.operation = operation;
    return hunk;
}

std::vector<DiffHunk<char>> computeDiff_LinearSpace(const std::string& text1, const std::string& text2)
{
    // NOTE:
    // This algorithm is based on Hirschberg's linear-space LCS algorithm in
    // "A linear space algorithm for computing maximal common subsequences",
    // Communications of the ACM, Volume 18 Issue 6, June 1975, pages 341-343

    if (text2.empty()) {
        std::vector<DiffHunk<char>> hunks;
        if (!text1.empty()) {
            DiffHunk<char> hunk1;
            hunk1.operation = DiffOperation::Deletion;
            hunk1.text = text1;
            hunks.push_back(std::move(hunk1));
        }
        return hunks;
    }

    assert(!text2.empty());

    std::vector<size_t> vertices(text2.size());
    std::vector<SubstringRange> stack;
    
    {
        SubstringRange param;
        param.start1 = 0;
        param.size1 = text1.size();
        param.start2 = 0;
        param.size2 = text2.size();
        stack.push_back(std::move(param));
    }

    while (!stack.empty()) {
        auto param = std::move(stack.back());
        stack.pop_back();

        assert((param.start1 + param.size1) <= text1.size());
        assert((param.start2 + param.size2) <= text2.size());

        if ((param.size1 == 1) && (param.size2 == 1)) {
            vertices[param.start2] = param.start1;
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
            continue;
        }

        if (param.size1 == 0) {
            for (size_t i = 0; i < param.size2; ++i) {
                vertices[param.start2 + i] = param.start1;
            }
            continue;
        }
        if (param.size1 == 1) {
            size_t y = param.start1;
            for (size_t i = 0; i < param.size2; ++i) {
                vertices[param.start2 + i] = y;
                if (text1[param.start1] == text2[param.start2 + i]) {
                    ++y;
                }
            }
            continue;
        }

        assert(param.size1 >= 1);
        assert(param.size2 >= 1);

        const auto sizeOverTwo = param.size2 / 2;
        const auto centerX = param.start2 + sizeOverTwo;
        auto leftColumn = computeLevenshteinColumn(
            text2,
            text1,
            param.start2,
            sizeOverTwo,
            param.start1,
            param.size1,
            false);
        auto rightColumn = computeLevenshteinColumn(
            text2,
            text1,
            centerX,
            param.size2 - sizeOverTwo,
            param.start1,
            param.size1,
            true);

        assert(leftColumn.size() == rightColumn.size());
        assert(leftColumn.size() >= 2);

        size_t k = 0;
        int minVertex = std::numeric_limits<int>::max();
        for (size_t i = 1; i < leftColumn.size(); ++i) {
            auto c = leftColumn[i] + rightColumn[rightColumn.size() - i];
            if (c < minVertex) {
                minVertex = c;
                k = i - 1;
            }
        }
        vertices[centerX - 1] = param.start1 + k;

        {
            SubstringRange newParam;
            newParam.start1 = param.start1;
            newParam.size1 = k + 1;
            newParam.start2 = param.start2;
            newParam.size2 = sizeOverTwo;
            assert(newParam.size1 <= param.size1);
            assert(newParam.size2 <= param.size2);
            assert(newParam.size1 > 0);
            assert(newParam.size2 > 0);
            stack.push_back(std::move(newParam));
        }
        {
            SubstringRange newParam;
            newParam.start1 = param.start1 + (k + 1);
            newParam.size1 = param.size1 - (k + 1);
            newParam.start2 = centerX;
            newParam.size2 = param.size2 - sizeOverTwo;
            assert(newParam.size1 <= param.size1);
            assert(newParam.size2 <= param.size2);
            stack.push_back(std::move(newParam));
        }
    }

    std::vector<DiffHunk<char>> hunks;
    size_t y = 0;
    for (size_t x = 0; x < vertices.size(); ++x) {
        for (; (y < vertices[x]) && (y < text1.size()); ++y) {
            hunks.push_back(MakeDiffHunk(text1[y], DiffOperation::Deletion));
        }
        if ((x + 1 < vertices.size()) && ((vertices[x] + 1) == vertices[x + 1])) {
            if (text1[y] == text2[x]) {
                // NOTE: equality
                hunks.push_back(MakeDiffHunk(text1[y], DiffOperation::Equality));
            }
            else {
                // NOTE: substition
                hunks.push_back(MakeDiffHunk(text1[y], DiffOperation::Deletion));
                hunks.push_back(MakeDiffHunk(text2[x], DiffOperation::Insertion));
            }
            ++y;
        }
        else if (((x + 1) >= vertices.size()) && (text1[y] == text2[x])) {
            // NOTE: suffix match
            hunks.push_back(MakeDiffHunk(text1[y], DiffOperation::Equality));
        }
        else if (((x + 1) >= vertices.size()) || (vertices[x] == vertices[x + 1])) {
            hunks.push_back(MakeDiffHunk(text2[x], DiffOperation::Insertion));
        }
    }
    return hunks;
}

void PrintTable(
    const std::string& a,
    const std::string& b,
    size_t startA,
    size_t sizeA,
    size_t startB,
    size_t sizeB)
{
    std::cout << "  ";
    for (size_t i = 0; i <= b.size(); ++i) {
        std::cout << std::setw(3) << std::setfill(' ') << ((i == 0) ? ' ' :  b[i - 1]);
    }
    std::cout << std::endl;
    std::cout << "  ";
    for (size_t i = 0; i <= b.size(); ++i) {
        std::cout << std::setw(3) << std::setfill(' ') << i;
    }
    std::cout << std::endl;
    for (size_t i = startA + 1; i <= sizeA; ++i) {
        std::cout << a[i - 1] << ' ';
        auto column = computeLevenshteinColumn(a, b, startA, i, startB, sizeB);
        for (auto c : column) {
            std::cout << std::setw(3) << std::setfill(' ') << c;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

} // unnamed namespace

int main(int argc, char *argv[])
{
//    {
//        std::string a = "jk";
//        std::string b = "Hijk";
//        PrintTable(a, b, 0, a.size(), 0, b.size());
//    }
//    {
//        std::string a = "abcdEfghi";
//        std::string b = "E";
//        PrintTable(a, b, 0, a.size(), 0, b.size());
//    }
//    {
//        std::string a = "kjihgf";
//        std::string b = "kjiHeDcbA";
//        PrintTable(a, b, 0, a.size(), 0, b.size());
//    }
//    {
//        std::string a = "AbcDeHijk";
//        std::string b = "abcdefghijk";
//        PrintTable(a, b, 0, a.size(), 0, b.size());
//    }

        std::string text1 = "AbcDeHijk";
        std::string text2 = "abcdefghijk";
//        std::string text1 = "AbAbabABababababAbababAbababAbabsdhej";
//        std::string text2 = "bABabbbABabABABbabababAbabAbABAbbAbb";
//        std::string text1 = "b";
//        std::string text2 = "ab";
//        std::string text1 = "c";
//        std::string text2 = "abcde";
//        std::string text1 = "a";
//        std::string text2 = "ab";
//        std::string text1 = "";
//        std::string text2 = "a";
//        std::string text1 = "ab";
//        std::string text2 = "abCD";
//        std::string text1 = "abCD";
//        std::string text2 = "CD";
        PrintTable(text1, text2, 0, text1.size(), 0, text2.size());

    auto diff = computeDiff_LinearSpace(text1, text2);
    for (auto & d : diff) {
        std::cout << (d.operation == DiffOperation::Equality ? "[=]" : (d.operation == DiffOperation::Deletion) ? "[-]" : "[+]") << " " << d.text << std::endl;
    }

    std::cout << std::endl;
    for (auto & d : diff) {
        std::cout << (d.operation == DiffOperation::Equality ? "=" : (d.operation == DiffOperation::Deletion) ? "-" : "+");
    }
    std::cout << std::endl;

    return 0;
}
