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

bool EqualDiff(const std::vector<DiffHunk<char>>& a, const std::vector<DiffHunk<char>>& b)
{
    if (a.size() != b.size()) {
        return false;
    }
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i].operation != b[i].operation) {
            return false;
        }
        if (a[i].text != b[i].text) {
            return false;
        }
    }
    return true;
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
    pairs.emplace_back("AbAbabABababababAbababAbababAbabsdhej", "bABabbbABabABABbabababAbabAbABAbbAbb");

    for (auto & p : pairs) {
        auto & text1 = p.first;
        auto & text2 = p.second;
        auto a = computeDiff_LinearSpace(text1, text2);
        auto b = computeDiff_DynamicProgramming(text1, text2);
        auto c = computeDiff_ONDGreedyAlgorithm(text1, text2);

        auto result = EqualDiff(a, b) && EqualDiff(a, c);
        std::cout << std::boolalpha << result << std::endl;
        
        if (!result) {
            PrintDiff(a);
            std::cout << std::endl;
            PrintDiff(b);
            std::cout << std::endl;
            PrintDiff(c);
            std::cout << std::endl;
        }
    }

    return 0;
}
