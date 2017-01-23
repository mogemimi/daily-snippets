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
#include <random>

namespace {

using namespace somera;

//void PrintTable(
//    const std::string& a,
//    const std::string& b,
//    size_t startA,
//    size_t sizeA,
//    size_t startB,
//    size_t sizeB)
//{
//    std::cout << "  ";
//    for (size_t i = 0; i <= b.size(); ++i) {
//        std::cout << std::setw(3) << std::setfill(' ') << ((i == 0) ? ' ' :  b[i - 1]);
//    }
//    std::cout << std::endl;
//    std::cout << "  ";
//    for (size_t i = 0; i <= b.size(); ++i) {
//        std::cout << std::setw(3) << std::setfill(' ') << i;
//    }
//    std::cout << std::endl;
//    for (size_t i = startA + 1; i <= sizeA; ++i) {
//        std::cout << a[i - 1] << ' ';
//        auto column = computeLevenshteinColumn(a, b, startA, i, startB, sizeB);
//        for (auto c : column) {
//            std::cout << std::setw(3) << std::setfill(' ') << c;
//        }
//        std::cout << std::endl;
//    }
//    std::cout << std::endl;
//}

bool IsDiffValid(
    const std::vector<DiffHunk<char>>& hunks,
    const std::string& a,
    const std::string& b)
{
    std::string x;
    std::string y;
    for (auto & hunk : hunks) {
        if (hunk.operation == DiffOperation::Equality) {
            x += hunk.text;
            y += hunk.text;
        }
        else if (hunk.operation == DiffOperation::Deletion) {
            x += hunk.text;
        }
        else if (hunk.operation == DiffOperation::Insertion) {
            y += hunk.text;
        }
    }
    return (x == a) && (y == b);
}

size_t GetEditScriptCount(const std::vector<DiffHunk<char>>& hunks)
{
    size_t count = 0;
    for (auto & hunk : hunks) {
        count += hunk.text.size();
    }
    return count;
}

size_t GetLCSLength(const std::vector<DiffHunk<char>>& hunks)
{
    size_t count = 0;
    for (auto & hunk : hunks) {
        if (hunk.operation == DiffOperation::Equality) {
            count += hunk.text.size();
        }
    }
    return count;
}

void PrintDiff(const std::vector<DiffHunk<char>>& diff)
{
    for (auto & d : diff) {
        std::cout << (d.operation == DiffOperation::Equality ? "[=]" : (d.operation == DiffOperation::Deletion) ? "[-]" : "[+]")
            << " " << d.text << std::endl;
    }
    std::cout << std::endl;
}

void TestCases()
{
    std::vector<std::pair<std::string, std::string>> pairs;
    pairs.emplace_back("abCD", "CD");
    pairs.emplace_back("ab", "abCD");
    pairs.emplace_back("", "a");
    pairs.emplace_back("", "aa");
    pairs.emplace_back("", "aaa");
    pairs.emplace_back("", "aaaa");
    pairs.emplace_back("", "aaaaa");
    pairs.emplace_back("", "aaaaaa");
    pairs.emplace_back("a", "");
    pairs.emplace_back("aa", "");
    pairs.emplace_back("aaa", "");
    pairs.emplace_back("aaaa", "");
    pairs.emplace_back("aaaaa", "");
    pairs.emplace_back("aaaaaa", "");
    pairs.emplace_back("a", "ab");
    pairs.emplace_back("b", "ab");
    pairs.emplace_back("a", "");
    pairs.emplace_back("ab", "a");
    pairs.emplace_back("abb", "a");
    pairs.emplace_back("abbb", "a");
    pairs.emplace_back("abbbb", "a");
    pairs.emplace_back("c", "abcde");
    pairs.emplace_back("AbcDeHijk", "abcdefghijk");
    pairs.emplace_back("a", "bb");
    pairs.emplace_back("aa", "bbb");
    pairs.emplace_back("aaa", "bbbb");
    pairs.emplace_back("aaaa", "bbbbb");
    pairs.emplace_back("a", "b");
    pairs.emplace_back("aa", "b");
    pairs.emplace_back("aaa", "bb");
    pairs.emplace_back("aaaa", "bbb");
    pairs.emplace_back("aaaaa", "bbbb");
    pairs.emplace_back("bAbabABab", "bABabABABbaba");
    pairs.emplace_back("AbAbabABababababAbababAbababAbabsdhej", "bABabbbABabABABbabababAbabAbABAbbAbb");
    pairs.emplace_back(
        "cbdbFbcaFEbcFEdEaddEdEbdaEEEEcdEbbFFccdFdbEFFFbcEbaFFEcabFbFEccccFFdadbcdcaFFEdEFaFFdE",
        "bccafedefcdcdbdcadcbdaaeedbfbcecefbbcfcfcbfbeebdedeedbfddbaadcccdfbabfffffdcfbfffedafb");

#if 1
    // Random test case generator
    std::mt19937 random(10000);
    for (int k = 0; k < 50; ++k) {
        std::string x;
        std::string y;
        for (int i = 0; i < 1000; ++i) {
            auto a = "abcdEF";
            auto b = "abcdef";
            if (random() % 3 == 0) {
                x += a[random() % 6];
            }
            if (random() % 3 == 0) {
                y += b[random() % 6];
            }
        }
        pairs.emplace_back(x, y);
    }
#endif

    for (auto & p : pairs) {
        auto & text1 = p.first;
        auto & text2 = p.second;
        auto a = computeDiff_LinearSpace(text1, text2);
        auto b = computeDiff_DynamicProgramming(text1, text2);
        auto c = computeDiff_ONDGreedyAlgorithm(text1, text2);
        auto d = computeDiff_WeavingLinearSpace(text1, text2);

        auto result = IsDiffValid(a, text1, text2) &&
            (GetEditScriptCount(a) == GetEditScriptCount(b)) &&
            (GetEditScriptCount(a) == GetEditScriptCount(c)) &&
            (GetEditScriptCount(a) == GetEditScriptCount(d)) &&
            (GetLCSLength(a) == GetLCSLength(b)) &&
            (GetLCSLength(a) == GetLCSLength(c)) &&
            (GetLCSLength(a) == GetLCSLength(d));
        std::cout << std::boolalpha << result << std::endl;

        if (!result) {
            PrintDiff(a);
            PrintDiff(b);
            PrintDiff(c);
            PrintDiff(d);
            std::cout << std::endl;
            std::cout << "Shortes Edit Script:" << std::endl;
            std::cout << GetEditScriptCount(a) << std::endl;
            std::cout << GetEditScriptCount(b) << std::endl;
            std::cout << GetEditScriptCount(c) << std::endl;
            std::cout << GetEditScriptCount(d) << std::endl;
        }
    }
}

template <class Function>
void measurePerformanceTime(Function f)
{
    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;
    using std::chrono::nanoseconds;
    using std::chrono::duration_cast;

    auto start = high_resolution_clock::now();

    f();

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);

    std::cout
        << "Measured time (ns) : " << duration.count() << " ns" << std::endl;
    std::cout
        << "Measured time (sec): "
        << duration_cast<std::chrono::duration<double>>(end - start).count()
        << " seconds" << std::endl;
}

void PerformanceTest()
{
    std::vector<std::pair<std::string, std::string>> pairs;

    // NOTE: (k = 100, i < 10000)
    // computeDiff_DynamicProgramming
    // Measured time (ns) : 92631244844 ns
    // Measured time (sec): 92.6312 seconds
    // computeDiff_ONDGreedyAlgorithm
    // Measured time (ns) : 392679788818 ns
    // Measured time (sec): 392.68 seconds
    // computeDiff_LinearSpace
    // Measured time (ns) : 137508316370 ns
    // Measured time (sec): 137.508 seconds

    // NOTE: k = 1, i < 46000, btw 46000 * 46000 < INT_MAX (= 2147483647)
    // computeDiff_DynamicProgramming
    // Measured time (ns) : 41782002335 ns
    // Measured time (sec): 41.782 seconds
    // computeDiff_ONDGreedyAlgorithm
    // Measured time (ns) : 159242225383 ns
    // Measured time (sec): 159.242 seconds
    // computeDiff_LinearSpace
    // Measured time (ns) : 36663023867 ns
    // Measured time (sec): 36.663 seconds
    // computeDiff_WeavingLinearSpace
    // Measured time (ns) : 5907292422 ns
    // Measured time (sec): 5.90729 seconds

    // NOTE: k = 10, i < 5000
    // computeDiff_DynamicProgramming
    // Measured time (ns) : 2759831585 ns
    // Measured time (sec): 2.75983 seconds
    // computeDiff_ONDGreedyAlgorithm
    // Measured time (ns) : 13060874448 ns
    // Measured time (sec): 13.0609 seconds
    // computeDiff_LinearSpace
    // Measured time (ns) : 4450071900 ns
    // Measured time (sec): 4.45007 seconds
    // computeDiff_WeavingLinearSpace
    // Measured time (ns) : 735983596 ns
    // Measured time (sec): 0.735984 seconds

    // NOTE: k = 100000, i < 20
    // computeDiff_DynamicProgramming
    // Measured time (ns) : 857451980 ns
    // Measured time (sec): 0.857452 seconds
    // computeDiff_ONDGreedyAlgorithm
    // Measured time (ns) : 3071924040 ns
    // Measured time (sec): 3.07192 seconds
    // computeDiff_LinearSpace
    // Measured time (ns) : 1686588532 ns
    // Measured time (sec): 1.68659 seconds
    // computeDiff_WeavingLinearSpace
    // Measured time (ns) : 1460913501 ns
    // Measured time (sec): 1.46091 seconds

    std::mt19937 random(10000);
    for (int k = 0; k < 100000; ++k) {
        std::string x;
        std::string y;
        for (int i = 0; i < 20; ++i) {
            std::string a = "abcdefghIJK";
            std::string b = "abcdefghXYZ";
            if (random() % 3 == 0) {
                x += a[random() % a.size()];
            }
            if (random() % 3 == 0) {
                y += b[random() % b.size()];
            }
        }
        pairs.emplace_back(x, y);
    }

    size_t dummy = 0;
    measurePerformanceTime([&] {
        for (auto & p : pairs) {
            auto & text1 = p.first;
            auto & text2 = p.second;
            auto b = computeDiff_DynamicProgramming(text1, text2);
            dummy += b.size();
        }
    });

    measurePerformanceTime([&] {
        for (auto & p : pairs) {
            auto & text1 = p.first;
            auto & text2 = p.second;
            auto c = computeDiff_ONDGreedyAlgorithm(text1, text2);
            dummy += c.size();
        }
    });

    measurePerformanceTime([&] {
        for (auto & p : pairs) {
            auto & text1 = p.first;
            auto & text2 = p.second;
            auto a = computeDiff_LinearSpace(text1, text2);
            dummy += a.size();
        }
    });

    measurePerformanceTime([&] {
        for (auto & p : pairs) {
            auto & text1 = p.first;
            auto & text2 = p.second;
            auto a = computeDiff_WeavingLinearSpace(text1, text2);
            dummy += a.size();
        }
    });
}

} // unnamed namespace

int main(int argc, char *argv[])
{
    TestCases();
    PerformanceTest();

//    std::string text1 = "AbcDeHijk";
//    std::string text2 = "abcdefghijk";
////    PrintDiff(computeDiff_LinearSpace(text1, text2));
//    PrintDiff(computeDiff_WeavingLinearSpace(text1, text2));
////    PrintDiff(computeDiff_DynamicProgramming(text1, text2));

    return 0;
}
