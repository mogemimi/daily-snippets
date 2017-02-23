// Copyright (c) 2017 mogemimi. Distributed under the MIT license.

#include "aligndiff.h"
#include <cassert>
#include <cstdlib>

namespace aligndiff {

int computeLCSLength_ONDGreedyAlgorithm(
    const std::string& text1,
    const std::string& text2)
{
    // NOTE:
    // This algorithm is based on Myers's An O((M+N)D) Greedy Algorithm in
    // "An O(ND)Difference Algorithm and Its Variations",
    // Algorithmica (1986), pages 251-266.

    if (text1.empty() || text2.empty()) {
        return 0;
    }

    const auto M = static_cast<int>(text1.size());
    const auto N = static_cast<int>(text2.size());

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

    std::vector<int> lcsLengths(M + N + 1);
    lcsLengths[1 + offset] = 0;

    for (int d = 0; d <= maxD; ++d) {
        const int startK = -std::min(d, (N * 2) - d);
        const int endK = std::min(d, (M * 2) - d);

        assert((-N <= startK) && (endK <= M));
        assert(std::abs(startK % 2) == (d % 2));
        assert(std::abs(endK % 2) == (d % 2));
        assert((d > N) ? (startK == -(N * 2 - d)) : (startK == -d));
        assert((d > M) ? (endK == (M * 2 - d)) : (endK == d));

        for (int k = startK; k <= endK; k += 2) {
            assert((-N <= k) && (k <= M));
            assert(std::abs(k % 2) == (d % 2));

            const auto kOffset = k + offset;

            int x = 0;
            int lcsLength = 0;
            if (k == startK) {
                // NOTE: Move directly from vertex(x, y - 1) to vertex(x, y)
                x = vertices[kOffset + 1];
                lcsLength = lcsLengths[kOffset + 1];
            }
            else if (k == endK) {
                // NOTE: Move directly from vertex(x - 1, y) to vertex(x, y)
                x = vertices[kOffset - 1] + 1;
                lcsLength = lcsLengths[kOffset - 1];
            }
            else if (vertices[kOffset - 1] < vertices[kOffset + 1]) {
                // NOTE: Move from vertex(k + 1) to vertex(k)
                // vertex(k + 1) is ahead of vertex(k - 1).
                assert(-N < k && k < M);
                assert((k != -d) && (k != -N));
                assert((k != d) && (k != M));
                x = vertices[kOffset + 1];
                lcsLength = lcsLengths[kOffset + 1];
            }
            else {
                // NOTE: Move from vertex(k - 1) to vertex(k)
                // vertex(k - 1) is ahead of vertex(k + 1).
                assert(-N < k && k < M);
                assert((k != -d) && (k != -N));
                assert((k != d) && (k != M));
                assert(vertices[kOffset - 1] >= vertices[kOffset + 1]);
                x = vertices[kOffset - 1] + 1;
                lcsLength = lcsLengths[kOffset - 1];
            }

            // NOTE: `k` is defined from `x - y = k`.
            int y = x - k;
            assert(x >= 0 && y >= 0);

#if !defined(NDEBUG)
            if (d == 0) {
                assert((x == 0) && (y == 0) && (k == 0));
            }
#endif

            while (x < M && y < N && text1[x] == text2[y]) {
                // NOTE: This loop finds a possibly empty sequence
                // of diagonal edges called a 'snake'.
                x += 1;
                y += 1;
                lcsLength += 1;
            }

            if (x >= M && y >= N) {
                return lcsLength;
            }

            vertices[kOffset] = x;
            lcsLengths[kOffset] = lcsLength;
        }
    }
    return 0;
}

} // namespace aligndiff
