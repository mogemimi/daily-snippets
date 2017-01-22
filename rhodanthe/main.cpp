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

void PrintDiff(const std::vector<DiffHunk<char>>& diff)
{
    for (auto & d : diff) {
        std::cout << (d.operation == DiffOperation::Equality ? "[=]" : (d.operation == DiffOperation::Deletion) ? "[-]" : "[+]")
            << " " << d.text << std::endl;
    }
}

} // unnamed namespace

int main(int argc, char *argv[])
{
    std::vector<std::pair<std::string, std::string>> pairs;
    pairs.emplace_back("abCD", "CD");
    pairs.emplace_back("ab", "abCD");
    pairs.emplace_back("", "a");
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

#if 0
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

        auto result = IsDiffValid(a, text1, text2) &&
            (GetEditScriptCount(a) ==GetEditScriptCount(b)) &&
            (GetEditScriptCount(a) ==GetEditScriptCount(c));
        std::cout << std::boolalpha << result << std::endl;
        
        if (!result) {
            PrintDiff(a);
            std::cout << std::endl;
            PrintDiff(b);
            std::cout << std::endl;
            PrintDiff(c);
            std::cout << std::endl;

            std::cout << "Shortes Edit Script:" << std::endl;
            std::cout << GetEditScriptCount(a) << std::endl;
            std::cout << GetEditScriptCount(b) << std::endl;
            std::cout << GetEditScriptCount(c) << std::endl;
        }
    }

    return 0;
}
