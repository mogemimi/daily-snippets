// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "worddiff.h"
#include "somera/Optional.h"
#include "EditDistance.h"
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <utility>
#include <functional>

namespace somera {
namespace {

void SortHunks(std::vector<DiffHunk<char>> & hunks)
{
    for (size_t k = 0; k < hunks.size(); ++k) {
        for (size_t i = 1 + (k % 2); i < hunks.size(); i += 2) {
            auto & a = hunks[i - 1];
            auto & b = hunks[i];
            if ((a.operation == DiffOperation::Insertion) && (b.operation == DiffOperation::Deletion)) {
                std::swap(a, b);
            }
        }
    }
}

void CompressHunks(std::vector<DiffHunk<char>> & hunks)
{
    std::vector<DiffHunk<char>> oldHunks;
    std::swap(hunks, oldHunks);

    SortHunks(oldHunks);

    for (auto & hunk : oldHunks) {
        if (hunks.empty() || (hunks.back().operation != hunk.operation)) {
            hunks.push_back(std::move(hunk));
        }
        else {
            assert(hunks.back().operation == hunk.operation);
            hunks.back().text += hunk.text;
        }
    }
}

} // unnamed namespace

std::vector<DiffHunk<char>> computeDiff(const std::string& text1, const std::string& text2)
{
#if 1
    return computeDiff_ONDGreedyAlgorithm(text1, text2);
#else
    return computeDiff_DynamicProgramming(text1, text2);
#endif
}

std::vector<DiffHunk<char>> computeDiff_DynamicProgramming(const std::string& text1, const std::string& text2)
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

    std::vector<DiffHunk<char>> hunks;

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
            DiffHunk<char> hunk;
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
            DiffHunk<char> hunk;
            hunk.text = text1[row - 1];
            hunk.operation = DiffOperation::Equality;
            hunks.push_back(std::move(hunk));
            --row;
            --column;
            longestCommonSubsequence = mat(row, column);
        }
        else if (deletion < insertion) {
            DiffHunk<char> hunk;
            hunk.text = text1[row - 1];
            hunk.operation = DiffOperation::Deletion;
            hunks.push_back(std::move(hunk));
            --row;
        }
        else {
            DiffHunk<char> hunk;
            hunk.text = text2[column - 1];
            hunk.operation = DiffOperation::Insertion;
            hunks.push_back(std::move(hunk));
            --column;
        }
    }

    while (column > 0) {
        DiffHunk<char> hunk;
        hunk.text = text2[column - 1];
        hunk.operation = DiffOperation::Insertion;
        hunks.push_back(std::move(hunk));
        --column;
    }

    while (row > 0) {
        DiffHunk<char> hunk;
        hunk.text = text1[row - 1];
        hunk.operation = DiffOperation::Deletion;
        hunks.push_back(std::move(hunk));
        --row;
    }

    std::reverse(std::begin(hunks), std::end(hunks));
    CompressHunks(hunks);
    return hunks;
}

namespace {

struct Vertex final {
    std::shared_ptr<Vertex> prev;
    int x;
    int y;

    Vertex(std::shared_ptr<Vertex> && prevIn, int xIn, int yIn)
        : prev(std::move(prevIn))
        , x(xIn)
        , y(yIn)
    {
    }

    void PushBack(int xIn, int yIn)
    {
        auto vertex = std::make_shared<Vertex>(std::move(prev), x, y);
        prev = std::move(vertex);
        x = xIn;
        y = yIn;
    }
};

std::vector<DiffHunk<char>> GenerateDiffHunks(
    const std::shared_ptr<Vertex>& path,
    const std::string& text1,
    const std::string& text2)
{
    std::vector<DiffHunk<char>> hunks;

    std::vector<Vertex> points;
    auto iter = path;
    while (iter != nullptr) {
        points.push_back(*iter);
        iter = iter->prev;
    }
    std::reverse(std::begin(points), std::end(points));

    for (size_t i = 0; (i + 1) < points.size(); ++i) {
        auto & p0 = points[i];
        auto & p1 = points[i + 1];
        assert(((p0.x == p1.x) && (p0.y + 1 == p1.y))
            || ((p0.x + 1 == p1.x) && (p0.y == p1.y))
            || ((p0.x + 1 == p1.x) && (p0.y + 1 == p1.y)));
        if (p0.x == p1.x) {
            DiffHunk<char> hunk;
            hunk.operation = DiffOperation::Insertion;
            hunk.text = text2[p0.y];
            hunks.push_back(std::move(hunk));
        }
        else if (p0.y == p1.y) {
            DiffHunk<char> hunk;
            hunk.operation = DiffOperation::Deletion;
            hunk.text = text1[p0.x];
            hunks.push_back(std::move(hunk));
        }
        else {
            DiffHunk<char> hunk;
            hunk.operation = DiffOperation::Equality;
            hunk.text = text1[p0.x];
            hunks.push_back(std::move(hunk));
        }
    }

    CompressHunks(hunks);
    return hunks;
}

} // unnamed namespace

std::vector<DiffHunk<char>> computeDiff_ONDGreedyAlgorithm(const std::string& text1, const std::string& text2)
{
    // NOTE:
    // This algorithm is based on Myers's An O((M+N)D) Greedy Algorithm in
    // "An O(ND)Difference Algorithm and Its Variations",
    // Algorithmica (1986), pages 251-266.

    if (text1.empty() || text2.empty()) {
        std::vector<DiffHunk<char>> hunks;
        if (!text1.empty()) {
            DiffHunk<char> hunk1;
            hunk1.operation = DiffOperation::Deletion;
            hunk1.text = text1;
            hunks.push_back(std::move(hunk1));
        }
        else if (!text2.empty()) {
            DiffHunk<char> hunk2;
            hunk2.operation = DiffOperation::Insertion;
            hunk2.text = text2;
            hunks.push_back(std::move(hunk2));
        }
        return hunks;
    }

    const auto M = static_cast<int>(text1.size());
    const auto N = static_cast<int>(text2.size());

    const auto maxD = M + N;
    const auto offset = N;

    std::vector<int> vertices(M + N + 1);
    vertices[1 + offset] = 0;

    std::vector<std::shared_ptr<Vertex>> paths(vertices.size());

    for (int d = 0; d <= maxD; ++d) {
        const int startK = -std::min(d, (N * 2) - d);
        const int endK = std::min(d, (M * 2) - d);

        assert((-N <= startK) && (endK <= M));
        assert(std::abs(startK % 2) == (d % 2));
        assert(std::abs(endK % 2) == (d % 2));
        assert((d > N) ? (startK == -(N * 2 - d)) : (startK == -d));
        assert((d > M) ? (endK == (M * 2 - d)) : (endK == d));

        // NOTE:
        // When IMPROVE_DIFFHUNK_READABILITY is defined 1,
        // * Diff(aa, bb) is -aa+bb
        // * Diff(a, bbbbb) is -a+bbbbb
        // * Diff(aaaaa, bbbbb) is -aaaaa+bbbbb
        // 
        // When IMPROVE_DIFFHUNK_READABILITY is defined 0,
        // * Diff(aa, bb) is -a+b-a+b
        // * Diff(a, bbbbb) is +b-a+bbbb
        // * Diff(aaaaa, bbbbb) is -aaaa+b-a+bbbb
#define IMPROVE_DIFFHUNK_READABILITY 1
#if (IMPROVE_DIFFHUNK_READABILITY == 1)
        const bool startKMinusOneEnabled = (-d < startK) && (-N < startK);
        const bool endKMinusOneEnabled = (endK < d) && (endK < M);
#else
        constexpr bool startKMinusOneEnabled = false;
        constexpr bool endKMinusOneEnabled = false;
#endif

        for (int k = startK; k <= endK; k += 2) {
            assert((-N <= k) && (k <= M));
            assert(std::abs(k % 2) == (d % 2));

            const auto kOffset = k + offset;

            int x = 0;
            if (k == startK && !startKMinusOneEnabled) {
                // NOTE: Move directly from vertex(x, y - 1) to vertex(x, y)
                // NOTE: In this case, V[k - 1] is out of range.
                x = vertices[kOffset + 1];
                paths[kOffset] = paths[kOffset + 1];
            }
            else if (k == endK && !endKMinusOneEnabled) {
                // NOTE: Move directly from vertex(x - 1, y) to vertex(x, y)
                // NOTE: In this case, V[k + 1] is out of range.
                x = vertices[kOffset - 1] + 1;
                paths[kOffset] = paths[kOffset - 1];
            }
            else if (vertices[kOffset - 1] < vertices[kOffset + 1]) {
                // NOTE: Move from vertex(k + 1) to vertex(k)
                // vertex(k + 1) is ahead of vertex(k - 1).
                assert(-N < k && k < M);
                assert((k != -d) && (k != -N));
                assert((k != d) && (k != M));
                x = vertices[kOffset + 1];
                paths[kOffset] = paths[kOffset + 1];
            }
            else {
                // NOTE: Move from vertex(k - 1) to vertex(k)
                // vertex(k - 1) is ahead of vertex(k + 1).
                assert(-N < k && k < M);
                assert((k != -d) && (k != -N));
                assert((k != d) && (k != M));
                assert(vertices[kOffset - 1] >= vertices[kOffset + 1]);
                x = vertices[kOffset - 1] + 1;
                paths[kOffset] = paths[kOffset - 1];
            }

            // NOTE: `k` is defined from `x - y = k`.
            int y = x - k;
            assert(x >= 0 && y >= 0);

#if !defined(NDEBUG)
            if (d == 0) {
                assert((x == 0) && (y == 0) && (k == 0));
                assert(paths[kOffset] == nullptr);
            }
#endif

            auto prev = std::move(paths[kOffset]);
            paths[kOffset] = std::make_shared<Vertex>(std::move(prev), x, y);

            while (x < M && y < N && text1[x] == text2[y]) {
                // NOTE: This loop finds a possibly empty sequence
                // of diagonal edges called a 'snake'.
                x += 1;
                y += 1;
                assert(paths[kOffset] != nullptr);
                paths[kOffset]->PushBack(x, y);
            }

            vertices[kOffset] = x;
            if (x >= M && y >= N) {
                return GenerateDiffHunks(paths[kOffset], text1, text2);
            }
        }
    }

    // NOTE: In this case, D must be == M + N.
    assert(false);
    return {};
}

namespace {

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

} // unnamed namespace

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

    while (!stack.empty()) {
        auto param = std::move(stack.back());
        stack.pop_back();

        assert((param.start1 + param.size1) <= text1.size());
        assert((param.start2 + param.size2) <= text2.size());

        if ((param.size1 == 1) && (param.size2 == 1)) {
            vertices[param.start2] = param.start1;
            vertices[param.start2 + 1] = param.start1 + 1;
            continue;
        }

        if (param.size1 == 0) {
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
        for (size_t i = 0; i < leftColumn.size(); ++i) {
            auto c = leftColumn[i] + rightColumn[rightColumn.size() - (i + 1)];
            if (c < minVertex) {
                minVertex = c;
                k = i;
            }
        }
        vertices[centerX - 1] = param.start1 + k;

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

#ifndef NDEBUG
    {
        size_t prev = 0;
        for (auto & v : vertices) {
            assert(v >= prev);
            assert(v <= text1.size());
            prev = v;
        }
    }
#endif

    std::vector<DiffHunk<char>> hunks;
    size_t y = 0;
    for (size_t x = 0; (x + 1) < vertices.size(); ++x) {
        for (; ((y + 1) < vertices[x + 1]) && (y < text1.size()); ++y) {
            hunks.push_back(MakeDiffHunk(text1[y], DiffOperation::Deletion));
        }
        if ((x + 1 < vertices.size()) && ((y + 1) == vertices[x + 1])) {
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
            continue;
        }
        if (((x + 1) >= vertices.size()) || (vertices[x] == vertices[x + 1])) {
            hunks.push_back(MakeDiffHunk(text2[x], DiffOperation::Insertion));
        }
    }
    for (; y < text1.size(); ++y) {
        hunks.push_back(MakeDiffHunk(text1[y], DiffOperation::Deletion));
    }
    CompressHunks(hunks);
    return hunks;
}

std::string computeLCSLinearSpace(
    const std::string& text1,
    const std::string& text2)
{
    return computeLCSLinearSpace(text1, text2, text1.size(), text2.size());
}

namespace {

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

} // unnamed namespace

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
        substring(text1, k, static_cast<int>(m - 1)),
        substring(text2, halfN, static_cast<int>(n - 1)),
        m - k,
        n - halfN);

    return u + v;
}

} // namespace somera
