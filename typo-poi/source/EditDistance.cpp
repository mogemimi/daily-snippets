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

//namespace utf8somera {
//
//utf8::iterator<std::string::const_iterator> begin(const std::string& s)
//{
//    utf8::iterator<std::string::const_iterator> it(s.begin(), s.begin(), s.end());
//    return std::move(it);
//}
//
//utf8::iterator<std::string::const_iterator> end(const std::string& s)
//{
//    utf8::iterator<std::string::const_iterator> it(s.end(), s.begin(), s.end());
//    return std::move(it);
//}
//
//template <typename Iterator>
//auto distance(Iterator first, Iterator last)
//{
//    return utf8::distance(first.base(), last.base());
//}
//
//std::size_t size(const std::string& s)
//{
//    return utf8::distance(s.begin(), s.end());
//}
//
//} // namespace utf8somera

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

} // namespace somera
