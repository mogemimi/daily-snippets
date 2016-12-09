// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "worddiff.h"
#include "somera/Optional.h"
#include "EditDistance.h"
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <utility>

namespace somera {
namespace {

void CompressHunks(std::vector<DiffHunk> & hunks)
{
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

} // unnamed namespace

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
    CompressHunks(hunks);
    return hunks;
}

namespace {

struct Point2D {
    int x;
    int y;
};

struct Path {
    std::vector<Point2D> points;

    Path & operator=(const Path& other)
    {
        points = other.points;
        return *this;
    }

    void insert(int x, int y)
    {
        Point2D p;
        p.x = x;
        p.y = y;
        points.push_back(std::move(p));
    }
};

std::vector<DiffHunk> GenerateDiffHunks(const Path& path, const std::string& text1, const std::string& text2)
{
    std::vector<DiffHunk> hunks;
    auto & points = path.points;

    for (size_t i = 0; (i + 1) < points.size(); ++i) {
        auto & p0 = points[i];
        auto & p1 = points[i + 1];
        assert(((p0.x == p1.x) && (p0.y + 1 == p1.y))
            || ((p0.x + 1 == p1.x) && (p0.y == p1.y))
            || ((p0.x + 1 == p1.x) && (p0.y + 1 == p1.y)));
        if (p0.x == p1.x) {
            DiffHunk hunk;
            hunk.operation = DiffOperation::Insertion;
            hunk.text = text2[p0.y];
            hunks.push_back(std::move(hunk));
        }
        else if (p0.y == p1.y) {
            DiffHunk hunk;
            hunk.operation = DiffOperation::Deletion;
            hunk.text = text1[p0.x];
            hunks.push_back(std::move(hunk));
        }
        else {
            DiffHunk hunk;
            hunk.operation = DiffOperation::Equality;
            hunk.text = text1[p0.x];
            hunks.push_back(std::move(hunk));
        }
    }

    CompressHunks(hunks);
    return hunks;
}

} // unnamed namespace

std::vector<DiffHunk> computeDiff_ONDGreedyAlgorithm(const std::string& text1, const std::string& text2)
{
    // NOTE:
    // This algorithm is based on Myers's An O((M+N)D) Greedy Algorithm in
    // "An O(ND)Difference Algorithm and Its Variations",
    // Algorithmica (1986), pages 251-266.

    if (text1.empty() || text2.empty()) {
        // NOTE: In this case, we use dynamic programming algorithm.
        return computeDiff(text1, text2);
    }

    const auto M = static_cast<int>(text1.size());
    const auto N = static_cast<int>(text2.size());

    const auto maxD = M + N;
    const auto offset = N;

    std::vector<int> vertices(M + N + 1);
    vertices[1 + offset] = 0;

    std::vector<Path> paths(vertices.size());
    vertices[0 + offset] = 0;

    for (int d = 0; d <= maxD; ++d) {
#if 1
        const auto startK = -std::min(d, N - (((N % 2) == (d % 2)) ? 0 : 1));
        const auto endK = std::min(d, M - (((M % 2) == (d % 2)) ? 0 : 1));
#elif 0
        int startK = -d;
        if (startK < -N) {
            startK = -(N - (((N % 2) == (d % 2)) ? 0 : 1));
        }
        int endK = d;
        if (endK > M) {
            endK = M - (((M % 2) == (d % 2)) ? 0 : 1);
        }
#else
        int startK = -d;
        while (startK < -N) {
            startK += 2;
        }
        int endK = d;
        while (endK > M) {
            endK -= 2;
        }
#endif
        assert((-N <= startK) && (endK <= M));
        assert(std::abs(startK % 2) == (d % 2));
        assert(std::abs(endK % 2) == (d % 2));

        for (int k = startK; k <= endK; k += 2) {
            assert((-N <= k) && (k <= M));
            assert(std::abs(k % 2) == (d % 2));

            const auto kOffset = k + offset;

            int x = 0;
            if (k == startK) {
                // NOTE: Move directly from vertex(x, y - 1) to vertex(x, y)
                // NOTE: In this case, V[k - 1] is out of range.
                x = vertices[kOffset + 1];
                paths[kOffset] = paths[kOffset + 1];
            }
            else if (k == endK) {
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
                assert(paths[kOffset].points.empty());
            }
#endif
            paths[kOffset].insert(x, y);

            while (x < M && y < N && text1[x] == text2[y]) {
                // NOTE: This loop finds a possibly empty sequence
                // of diagonal edges called a 'snake'.
                x += 1;
                y += 1;
                paths[k + offset].insert(x, y);
            }

            vertices[k + offset] = x;
            if (x >= M && y >= N) {
                return GenerateDiffHunks(paths[kOffset], text1, text2);
            }
        }
    }

    assert(false);

    // NOTE: In this case, D must be == M + N.
    std::vector<DiffHunk> hunks;
    DiffHunk hunk1;
    hunk1.operation = DiffOperation::Deletion;
    hunk1.text = text1;
    hunks.push_back(std::move(hunk1));
    DiffHunk hunk2;
    hunk2.operation = DiffOperation::Insertion;
    hunk2.text = text2;
    hunks.push_back(std::move(hunk2));
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
