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

struct Param {
    size_t start1;
    size_t size1;
    size_t start2;
    size_t size2;
};

std::vector<DiffHunk<char>> computeDiff_LinearSpace(const std::string& text1, const std::string& text2)
{
    if (text1.empty() || text2.empty()) {
        // TODO: Not implemented
        assert(false && "TODO");
        return {};
    }

    std::vector<size_t> vertices(text2.size(), 0);
    std::vector<Param> stack;
    
    {
        Param param;
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

        if (param.size1 == 0) {
            vertices[param.start2] = param.start1;
            continue;
        }
        if (param.size2 == 0) {
            vertices[param.start2] = param.start1;
            continue;
        }

//        if ((param.start1 == param.end1) && (param.start2 == param.end2)) {
//            vertices[param.start2] = param.start1;
//            continue;
//        }
//
//        if (param.start1 == param.end1) {
//            for (size_t i = param.start2; i < param.end2; ++i) {
//                vertices[i] = param.start1;
//            }
//            continue;
//        }
//        if (param.start2 == param.end2) {
//            vertices[param.start2] = param.start1;
//            continue;
//        }

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
                k = i;
            }
        }
        vertices[centerX - 1] = param.start1 + k;

        {
            Param newParam;
            newParam.start1 = param.start1;
            newParam.size1 = k;
            newParam.start2 = param.start2;
            newParam.size2 = sizeOverTwo;
            assert(newParam.size1 <= param.size1);
            assert(newParam.size2 <= param.size2);
            stack.push_back(std::move(newParam));
        }
        {
            Param newParam;
            newParam.start1 = k;
            newParam.size1 = param.size1 - k;
            newParam.start2 = centerX;
            newParam.size2 = param.size2 - sizeOverTwo;
            assert(newParam.size1 <= param.size1);
            assert(newParam.size2 <= param.size2);
            stack.push_back(std::move(newParam));
        }
    }

#if 1
    // NOTE: Show LCS string
    std::cout << "LCS = ";
    for (size_t x = 0; x < vertices.size(); ++x) {
        size_t y = vertices[x];
        if (text1[y] == text2[x]) {
            std::cout << text1[y];
        }
    }
    std::cout << std::endl;
#endif

    for (size_t x = 0; x < vertices.size(); ++x) {
        size_t y = vertices[x];
        if (text1[y] == text2[x]) {
            std::cout << "[=] " << text1[y] << std::endl;
        }
        else {
            std::cout << "[-] " << text1[y] << std::endl;
            std::cout << "[+] " << text2[x] << std::endl;
        }
    }
    std::cout << std::endl;

    std::vector<DiffHunk<char>> hunks;

//    int row = rows - 1;
//    int column = columns - 1;
//    Optional<int> longestCommonSubsequence;
//
//    while ((row > 0) && (column > 0)) {
//        // edit costs
//        const auto deletion = mat(row - 1, column);
//        const auto insertion = mat(row, column - 1);
//        const auto equality = mat(row - 1, column - 1);
//
//        if (longestCommonSubsequence
//            && (*longestCommonSubsequence == mat(row, column))
//            && (text1[row - 1] == text2[column - 1])) {
//            DiffHunk<char> hunk;
//            hunk.text = text1[row - 1];
//            hunk.operation = DiffOperation::Equality;
//            hunks.push_back(std::move(hunk));
//            --row;
//            --column;
//            continue;
//        }
//
//        longestCommonSubsequence = NullOpt;
//
//        if ((text1[row - 1] == text2[column - 1])
//            && (equality < deletion)
//            && (equality < insertion)) {
//            DiffHunk<char> hunk;
//            hunk.text = text1[row - 1];
//            hunk.operation = DiffOperation::Equality;
//            hunks.push_back(std::move(hunk));
//            --row;
//            --column;
//            longestCommonSubsequence = mat(row, column);
//        }
//        else if (deletion < insertion) {
//            DiffHunk<char> hunk;
//            hunk.text = text1[row - 1];
//            hunk.operation = DiffOperation::Deletion;
//            hunks.push_back(std::move(hunk));
//            --row;
//        }
//        else {
//            DiffHunk<char> hunk;
//            hunk.text = text2[column - 1];
//            hunk.operation = DiffOperation::Insertion;
//            hunks.push_back(std::move(hunk));
//            --column;
//        }
//    }
//
//    while (column > 0) {
//        DiffHunk<char> hunk;
//        hunk.text = text2[column - 1];
//        hunk.operation = DiffOperation::Insertion;
//        hunks.push_back(std::move(hunk));
//        --column;
//    }
//
//    while (row > 0) {
//        DiffHunk<char> hunk;
//        hunk.text = text1[row - 1];
//        hunk.operation = DiffOperation::Deletion;
//        hunks.push_back(std::move(hunk));
//        --row;
//    }
//
//    std::reverse(std::begin(hunks), std::end(hunks));
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

    {
        std::string a = "kjihgf";
        std::string b = "kjiHeDcbA";
        PrintTable(a, b, 0, a.size(), 0, b.size());
    }

    std::string a = "AbcDeHijk";
    std::string b = "abcdefghijk";
    PrintTable(a, b, 0, a.size(), 0, b.size());

//    std::string b = "AbcDeHijk";
//    std::string a = "fghijk";
//    std::reverse(b.begin(), b.end());
//    std::reverse(a.begin(), a.end());
//    PrintTable(a, b, 0, a.size() - 1, 0, b.size() - 1);

    auto diff = computeDiff_LinearSpace(a, b);
    for (auto & d : diff) {
        std::cout << static_cast<int>(d.operation) << " " << d.text << std::endl;
    }
    return 0;
}
