// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "editdistance.h"
#include "utf8.h"
#include <algorithm>
#include <array>
#include <cassert>
#include <vector>

namespace somera {
namespace {

template <typename T>
class CompensatedSumAccumulator {
private:
    T compensation = 0;

public:
    T operator()(const T& sum, const T& num)
    {
        // Kahan summation algorithm
        auto tmp = num - compensation;
        auto velvel = sum + tmp;
        compensation = (velvel - sum) - tmp;
        return velvel;
    }
};

double matchCharacter(uint32_t a, uint32_t b)
{
    constexpr auto FullMatchScore = 1.0;
    constexpr auto CapitalMatchScore = 0.9;
    constexpr auto NoMatch = 0.0;

    if (a == b) {
        return FullMatchScore;
    }
    if (::isalpha(a) && ::isalpha(b) && (::tolower(a) == ::tolower(b))) {
        return CapitalMatchScore;
    }
    return NoMatch;
}

double closestMatchDistance(const std::u32string& left, const std::u32string& right)
{
    if (left.empty() && right.empty()) {
        return 1.0;
    }

    // NOTE:
    // This algorithm is based on Boer's Closest-String Matching Algorithm in
    // Game Programming Gems 6 (pages 69, Section 1.6).

    CompensatedSumAccumulator<double> accumulator;
    double matchValue = 0;

    auto leftIter = std::begin(left);
    auto rightIter = std::begin(right);

    while (leftIter != std::end(left) && rightIter != std::end(right))
    {
        const auto matchScore = matchCharacter(*leftIter, *rightIter);
        if (matchScore > 0.0) {
            matchValue = accumulator(matchValue, matchScore);
            ++leftIter;
            ++rightIter;
            continue;
        }

        assert(std::begin(left) != std::end(left));
        assert(std::begin(right) != std::end(right));

        auto leftBest = std::end(left);
        auto rightBest = std::end(right);
        int bestCount = std::numeric_limits<int>::max();
        int leftCount = 0;
        int rightCount = 0;

        for (auto leftPoint = leftIter; leftPoint != std::end(left); ++leftPoint) {
            assert(leftCount == std::distance(leftIter, leftPoint));
            if (leftCount + rightCount >= bestCount) {
                // For fast pruning
                break;
            }

            for (auto rightPoint = rightIter; rightPoint != std::end(right); ++rightPoint) {
                assert(rightCount == std::distance(rightIter, rightPoint));
                if (leftCount + rightCount >= bestCount) {
                    // For fast pruning
                    break;
                }

                if (matchCharacter(*leftPoint, *rightPoint) > 0.0) {
                    const auto totalCount = leftCount + rightCount;
                    if (totalCount < bestCount) {
                        bestCount = totalCount;
                        leftBest = leftPoint;
                        rightBest = rightPoint;
                    }
                }
                ++rightCount;
            }
            ++leftCount;
            rightCount = 0;
        }

        leftIter = leftBest;
        rightIter = rightBest;
    }

    const auto largerSize = std::max(left.size(), right.size());

    assert(matchValue >= 0);
    return std::min(matchValue, static_cast<double>(largerSize));
}

} // unnamed namespace

double EditDistance::closestMatchFuzzyDistance(const std::string& left, const std::string& right)
{
    const auto leftUtf32 = somera::toUtf32(left);
    const auto rightUtf32 = somera::toUtf32(right);

    const auto maxLength = std::max(leftUtf32.size(), rightUtf32.size());
    const auto distance = closestMatchDistance(leftUtf32, rightUtf32) / maxLength;
    return std::min(std::max(distance, 0.0), 1.0);
}

namespace {

bool equalCharacter(char a, char b)
{
//    return matchCharacter(a, b) > 0.5;
    return a == b;
}

double getJaroDistance(const std::string& left, const std::string& right)
{
    assert(!left.empty());
    assert(!right.empty());

    std::string max = left;
    std::string min = right;
    if (left.size() <= right.size()) {
        std::swap(max, min);
    }

    assert(!max.empty());
    const auto windowSize = std::max(static_cast<int>(max.size()) / 2 - 1, 0);
    std::vector<int> matchIndices(min.size(), -1);
    std::vector<bool> matchFlags(max.size(), false);

    int matchCount = 0;

    for (int i = 0; i < static_cast<int>(min.size()); i++) {
        const auto left2 = std::max(i - windowSize, 0);
        const auto right2 = std::min(i + windowSize + 1, static_cast<int>(max.size()));
        for (int j = left2; j < right2; ++j) {
            if (!matchFlags[j] && equalCharacter(min[i], max[j])) {
                matchIndices[i] = j;
                matchFlags[j] = true;
                matchCount++;
                break;
            }
        }
    }

    if (matchCount <= 0) {
        return 0;
    }

    std::vector<char> minMatches;
    minMatches.reserve(matchCount);
    for (std::size_t i = 0; i < min.size(); i++) {
        if (matchIndices[i] != -1) {
            minMatches.push_back(min[i]);
        }
    }

    std::vector<char> maxMatches;
    maxMatches.reserve(matchCount);
    for (std::size_t i = 0; i < max.size(); i++) {
        if (matchFlags[i]) {
            maxMatches.push_back(max[i]);
        }
    }

    int transpositionCount = 0;
    for (std::size_t i = 0; i < minMatches.size(); ++i) {
        assert(i < minMatches.size());
        assert(i < maxMatches.size());
        if (!equalCharacter(minMatches[i], maxMatches[i])) {
            transpositionCount++;
        }
    }

    assert(matchCount > 0);

    const auto m = static_cast<double>(matchCount);
    const auto t = static_cast<double>(transpositionCount / 2);
    const auto jaroDistance = (m / left.size() + m / right.size() + (m - t) / m) / 3.0;
    return jaroDistance;
}

int getCommonPrefixLength(const std::string& left, const std::string& right)
{
    const auto minLength = std::min(left.size(), right.size());
    int prefix = 0;
    for (size_t i = 0; i < minLength && !equalCharacter(left[i], right[i]); i++) {
        prefix++;
    }
    return prefix;
}

} // unnamed namespace

double EditDistance::jaroWinklerDistance(const std::string& left, const std::string& right)
{
    if (left.empty() || right.empty()) {
        return 0;
    }

    constexpr auto threshold = 0.7;
    constexpr auto defaultWeight = 0.1;

    const auto jaroDistance = getJaroDistance(left, right);

    if (jaroDistance < threshold) {
        return jaroDistance;
    }

    const auto prefix = getCommonPrefixLength(left, right);
    const auto maxLength = std::max(left.size(), right.size());
    const auto weight = std::min<double>(defaultWeight, 1.0 / maxLength);
    assert(weight >= 0);

    return jaroDistance + prefix * weight * (1 - jaroDistance);
}

int EditDistance::levenshteinDistance(const std::string& left, const std::string& right)
{
    const auto rows = static_cast<int>(left.size()) + 1;
    const auto columns = static_cast<int>(right.size()) + 1;

    // NOTE:
    // left  = "type"
    // right = "typo"

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
            if (left[row - 1] == right[column - 1]) {
                minCost = std::min(mat(row - 1, column - 1), minCost);
            }
            mat(row, column) = minCost;
        }
    }
    return mat(rows - 1, columns - 1);
}

int EditDistance::levenshteinDistance_ONDGreedyAlgorithm(
    const std::string& left, const std::string& right)
{
    // NOTE:
    // This algorithm is based on Myers's An O((M+N)D) Greedy Algorithm in
    // "An O(ND)Difference Algorithm and Its Variations",
    // Algorithmica (1986), pages 251-266.

    if (left.empty() || right.empty()) {
        return static_cast<int>(std::max(left.size(), right.size()));
    }

    const auto M = static_cast<int>(left.size());
    const auto N = static_cast<int>(right.size());

    const auto maxD = M + N;
    const auto offset = N;

    std::vector<int> vertices(M + N + 1);
#if !defined(NDEBUG)
    // NOTE:
    // There is no need to initialize with the zero value for array elements,
    // but you have to assign the zero value to `vertices[1 + offset]`.
    std::fill(std::begin(vertices), std::end(vertices), -1);
#endif
    vertices[1 + offset] = 0;

    for (int d = 0; d <= maxD; ++d) {
        for (int k = -d; k <= d; k += 2) {
            if ((k < -N) || (M < k)) {
                continue;
            }
            assert((-N <= k) && (k <= M));

            int x = 0;
            if ((k == -d) || (k == -N)) {
                // NOTE: Move directly from vertex(x, y - 1) to vertex(x, y)
                x = vertices[k + 1 + offset];
            }
            else if ((k == d) || (k == M)) {
                // NOTE: Move directly from vertex(x - 1, y) to vertex(x, y)
                x = vertices[k - 1 + offset] + 1;
            }
            else if (vertices[k - 1 + offset] < vertices[k + 1 + offset]) {
                // NOTE: Move from vertex(k + 1) to vertex(k)
                // vertex(k + 1) is ahead of vertex(k - 1).
                assert(-N < k && k < M);
                assert((k != -d) && (k != -N));
                assert((k != d) && (k != M));
                x = vertices[k + 1 + offset];
            }
            else {
                // NOTE: Move from vertex(k - 1) to vertex(k)
                // vertex(k - 1) is ahead of vertex(k + 1).
                assert(-N < k && k < M);
                assert((k != -d) && (k != -N));
                assert((k != d) && (k != M));
                assert(vertices[k - 1 + offset] >= vertices[k + 1 + offset]);
                x = vertices[k - 1 + offset] + 1;
            }

            // NOTE: `k` is defined from `x - y = k`.
            int y = x - k;
            assert(x >= 0 && y >= 0);

#if !defined(NDEBUG)
            if (d == 0) {
                assert((x == 0) && (y == 0) && (k == 0));
            }
#endif

            while (x < M && y < N && left[x] == right[y]) {
                // NOTE: This loop finds a possibly empty sequence
                // of diagonal edges called a 'snake'.
                x += 1;
                y += 1;
            }

            vertices[k + offset] = x;
            if (x >= M && y >= N) {
                return d;
            }
        }
    }
    return M + N;
}

std::vector<int> EditDistance::LCS_Column(
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

int EditDistance::computeLCSLengthInLinearSpace(const std::string& left, const std::string& right)
{
    auto lcsColumn = LCS_Column(left, right, (int)left.size(), (int)right.size());
    auto lcsLength = lcsColumn.back();

#if 1
    std::printf("{");
    for (int i = 0; i < (int)lcsColumn.size(); ++i) {
        std::printf("%2d, ", lcsColumn[i]);
    }
    std::printf("}\n");
#endif

    return lcsLength;
}

} // namespace somera
