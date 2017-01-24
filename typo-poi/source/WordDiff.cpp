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

DiffEdit<char> MakeDiffEdit(char character, DiffOperation operation)
{
    DiffEdit<char> edit;
    edit.character = character;
    edit.operation = operation;
    return edit;
}

} // unnamed namespace

std::vector<DiffEdit<char>> computeShortestEditScript_DynamicProgramming(
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

    std::vector<DiffEdit<char>> edits;

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
            edits.push_back(MakeDiffEdit(text1[row - 1], DiffOperation::Equality));
            --row;
            --column;
            continue;
        }

        longestCommonSubsequence = NullOpt;

        if ((text1[row - 1] == text2[column - 1])
            && (equality < deletion)
            && (equality < insertion)) {
            edits.push_back(MakeDiffEdit(text1[row - 1], DiffOperation::Equality));
            --row;
            --column;
            longestCommonSubsequence = mat(row, column);
        }
        else if (deletion < insertion) {
            edits.push_back(MakeDiffEdit(text1[row - 1], DiffOperation::Deletion));
            --row;
        }
        else {
            edits.push_back(MakeDiffEdit(text2[column - 1], DiffOperation::Insertion));
            --column;
        }
    }

    while (column > 0) {
        edits.push_back(MakeDiffEdit(text2[column - 1], DiffOperation::Insertion));
        --column;
    }
    while (row > 0) {
        edits.push_back(MakeDiffEdit(text1[row - 1], DiffOperation::Deletion));
        --row;
    }

    std::reverse(std::begin(edits), std::end(edits));
    return edits;
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

std::vector<DiffEdit<char>> GenerateDiffEdits(
    const std::shared_ptr<Vertex>& path,
    const std::string& text1,
    const std::string& text2)
{
    std::vector<DiffEdit<char>> edits;

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
            edits.push_back(MakeDiffEdit(text2[p0.y], DiffOperation::Insertion));
        }
        else if (p0.y == p1.y) {
            edits.push_back(MakeDiffEdit(text1[p0.x], DiffOperation::Deletion));
        }
        else {
            edits.push_back(MakeDiffEdit(text1[p0.x], DiffOperation::Equality));
        }
    }
    return edits;
}

} // unnamed namespace

std::vector<DiffEdit<char>> computeShortestEditScript_ONDGreedyAlgorithm(
    const std::string& text1,
    const std::string& text2)
{
    // NOTE:
    // This algorithm is based on Myers's An O((M+N)D) Greedy Algorithm in
    // "An O(ND)Difference Algorithm and Its Variations",
    // Algorithmica (1986), pages 251-266.

    if (text1.empty() || text2.empty()) {
        std::vector<DiffEdit<char>> edits;
        for (const auto& c : text1) {
            edits.push_back(MakeDiffEdit(c, DiffOperation::Deletion));
        }
        for (const auto& c : text2) {
            edits.push_back(MakeDiffEdit(c, DiffOperation::Insertion));
        }
        return edits;
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
                return GenerateDiffEdits(paths[kOffset], text1, text2);
            }
        }
    }

    // NOTE: In this case, D must be == M + N.
    assert(false);
    return {};
}

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

} // unnamed namespace

std::vector<DiffEdit<char>> computeShortestEditScript_LinearSpace(
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

    std::vector<DiffEdit<char>> edits;
    size_t y = 0;
    for (size_t x = 0; (x + 1) < vertices.size(); ++x) {
        for (; ((y + 1) < vertices[x + 1]) && (y < text1.size()); ++y) {
            edits.push_back(MakeDiffEdit(text1[y], DiffOperation::Deletion));
        }
        if ((x + 1 < vertices.size()) && ((y + 1) == vertices[x + 1])) {
            if (text1[y] == text2[x]) {
                // NOTE: equality
                edits.push_back(MakeDiffEdit(text1[y], DiffOperation::Equality));
            }
            else {
                // NOTE: substition
                edits.push_back(MakeDiffEdit(text1[y], DiffOperation::Deletion));
                edits.push_back(MakeDiffEdit(text2[x], DiffOperation::Insertion));
            }
            ++y;
            continue;
        }
        if (((x + 1) >= vertices.size()) || (vertices[x] == vertices[x + 1])) {
            edits.push_back(MakeDiffEdit(text2[x], DiffOperation::Insertion));
        }
    }
    for (; y < text1.size(); ++y) {
        edits.push_back(MakeDiffEdit(text1[y], DiffOperation::Deletion));
    }
    return edits;
}

namespace {

void weaving_edist(long * frame, const char t[], const long n, const char p[], const long m)
{
    assert(frame != nullptr);

	for (long depth = 0; depth < n + m - 1; depth++) {
        const auto warpStart = (depth < m)
            ? m - depth
            : depth - (m - 2);

        const auto warpEnd = (depth < n)
            ? depth + m
            : ((n - 1) * 2) + m - depth;

		for (long warpIndex = warpStart; warpIndex <= warpEnd; warpIndex += 2) {
			const auto col = (depth + warpIndex - m) >> 1;
			const auto row = (depth - warpIndex + m) >> 1;

            // NOTE: del = delete from pattern, downward; ins = insert to pattern, rightward
			const auto del = frame[warpIndex + 1] + 1;
			const auto ins = frame[warpIndex - 1] + 1;
			auto repl = frame[warpIndex];
			if (t[col] == p[row]) {
				if (del < ins && del < repl) {
					repl = del;
				}
                else if (ins < del && ins < repl) {
					repl = ins;
				}
			}
            else {
                assert(t[col] != p[row]);
                constexpr bool lcsSwitch = true;
				repl += 1;
				if (del <= ins && (lcsSwitch || del < repl)) {
					repl = del;
				}
                else if (ins < del && (lcsSwitch || ins < repl)) {
					repl = ins;
				}
			}

			frame[warpIndex] = repl;
		}
	}
}

void fillFrame(long * frame, const long n, const long m)
{
	for (long i = 0; i < n + m + 1; i++) {
		frame[i] = std::abs(m - i);  // m (pattern, left) frame
	}
}

// NOTE: Returns output as the `c1` vector reference.
void computeLevenshteinColumn_Weaving(
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

    std::vector<long> frame;
    frame.resize(size1 + size2 + 1);
    fillFrame(frame.data(), size1, size2);

    if (!reversedIteration) {
        weaving_edist(frame.data(), text1.data() + start1, size1, text2.data() + start2, size2);
    }
    else {
        std::string t1(text1.data() + start1, size1);
        std::string t2(text2.data() + start2, size2);
        std::reverse(t1.begin(), t1.end());
        std::reverse(t2.begin(), t2.end());
        weaving_edist(frame.data(), t1.data(), size1, t2.data(), size2);
    }

    for (size_t i = 0; i < columns; ++i) {
        c1[i] = frame[(frame.size() - 1) - i];
    }
}

} // unnamed namespace

std::vector<DiffEdit<char>> computeShortestEditScript_WeaveingLinearSpace(
    const std::string& text1,
    const std::string& text2)
{
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
        computeLevenshteinColumn_Weaving(
            text2,
            text1,
            param.start2,
            sizeOverTwo,
            param.start1,
            param.size1,
            forwardColumn,
            bufferColumn,
            false);
        computeLevenshteinColumn_Weaving(
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

    std::vector<DiffEdit<char>> edits;
    size_t y = 0;
    for (size_t x = 0; (x + 1) < vertices.size(); ++x) {
        for (; ((y + 1) < vertices[x + 1]) && (y < text1.size()); ++y) {
            edits.push_back(MakeDiffEdit(text1[y], DiffOperation::Deletion));
        }
        if ((x + 1 < vertices.size()) && ((y + 1) == vertices[x + 1])) {
            if (text1[y] == text2[x]) {
                // NOTE: equality
                edits.push_back(MakeDiffEdit(text1[y], DiffOperation::Equality));
            }
            else {
                // NOTE: substition
                edits.push_back(MakeDiffEdit(text1[y], DiffOperation::Deletion));
                edits.push_back(MakeDiffEdit(text2[x], DiffOperation::Insertion));
            }
            ++y;
            continue;
        }
        if (((x + 1) >= vertices.size()) || (vertices[x] == vertices[x + 1])) {
            edits.push_back(MakeDiffEdit(text2[x], DiffOperation::Insertion));
        }
    }
    for (; y < text1.size(); ++y) {
        edits.push_back(MakeDiffEdit(text1[y], DiffOperation::Deletion));
    }
    return edits;
}

namespace {

void SortHunks(std::vector<DiffEdit<char>> & edits)
{
    for (size_t k = 0; k < edits.size(); ++k) {
        bool swapped = false;
        for (size_t i = 1 + (k % 2); i < edits.size(); i += 2) {
            auto & a = edits[i - 1];
            auto & b = edits[i];
            if ((a.operation == DiffOperation::Insertion) && (b.operation == DiffOperation::Deletion)) {
                std::swap(a, b);
                swapped = true;
            }
            else if ((a.character == b.character) && (a.operation < b.operation)) {
                static_assert(DiffOperation::Deletion < DiffOperation::Equality, "");
                static_assert(DiffOperation::Equality < DiffOperation::Insertion, "");
                std::swap(a, b);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

std::vector<DiffHunk<char>> ToDiffHunk(const std::vector<DiffEdit<char>>& edits)
{
    std::vector<DiffHunk<char>> hunks;
    for (const auto& edit : edits) {
        if (hunks.empty() || (hunks.back().operation != edit.operation)) {
            DiffHunk<char> hunk;
            hunk.text = edit.character;
            hunk.operation = edit.operation;
            hunks.push_back(std::move(hunk));
        }
        else {
            assert(hunks.back().operation == edit.operation);
            hunks.back().text += edit.character;
        }
    }
    return hunks;
}

} // unnamed namespace

std::vector<DiffHunk<char>> computeDiff(
    const std::string& text1,
    const std::string& text2)
{
#if 1
    return computeDiff_LinearSpace(text1, text2);
#elif 1
    return computeDiff_ONDGreedyAlgorithm(text1, text2);
#else
    return computeDiff_DynamicProgramming(text1, text2);
#endif
}

std::vector<DiffHunk<char>> computeDiff_DynamicProgramming(
    const std::string& text1,
    const std::string& text2)
{
    auto editScript = computeShortestEditScript_DynamicProgramming(text1, text2);
    SortHunks(editScript);
    return ToDiffHunk(editScript);
}

std::vector<DiffHunk<char>> computeDiff_ONDGreedyAlgorithm(
    const std::string& text1,
    const std::string& text2)
{
    auto editScript = computeShortestEditScript_ONDGreedyAlgorithm(text1, text2);
    SortHunks(editScript);
    return ToDiffHunk(editScript);
}

std::vector<DiffHunk<char>> computeDiff_LinearSpace(
    const std::string& text1,
    const std::string& text2)
{
    auto editScript = computeShortestEditScript_LinearSpace(text1, text2);
    SortHunks(editScript);
    return ToDiffHunk(editScript);
}

std::vector<DiffHunk<char>> computeDiff_WeavingLinearSpace(
    const std::string& text1,
    const std::string& text2)
{
    auto editScript = computeShortestEditScript_WeaveingLinearSpace(text1, text2);
    SortHunks(editScript);
    return ToDiffHunk(editScript);
}

} // namespace somera
