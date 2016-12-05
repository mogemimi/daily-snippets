// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#pragma once

#include <string>
#include <vector>

namespace somera {

struct EditDistance {
    ///@param left UTF-8 string
    ///@param right UTF-8 string
    static double closestMatchFuzzyDistance(
        const std::string& left,
        const std::string& right);

    ///@param left UTF-8 string
    ///@param right UTF-8 string
    static double jaroWinklerDistance(
        const std::string& left,
        const std::string& right);

    ///@param left UTF-8 string
    ///@param right UTF-8 string
    static int levenshteinDistance(
        const std::string& left,
        const std::string& right);

    ///@param left UTF-8 string
    ///@param right UTF-8 string
    static int levenshteinDistance_ONDGreedyAlgorithm(
        const std::string& left,
        const std::string& right);

    ///@param left UTF-8 string
    ///@param right UTF-8 string
    static int computeLCSLengthInLinearSpace(
        const std::string& left,
        const std::string& right);

    ///@param left UTF-8 string
    ///@param right UTF-8 string
    static std::vector<int> LCS_Column(
        const std::string& left,
        const std::string& right,
        std::size_t m,
        std::size_t n);
};

} // namespace somera
