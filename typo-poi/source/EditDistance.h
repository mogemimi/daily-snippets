// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#pragma once

#include <string>
#include <vector>

namespace somera {

///@param left UTF-8 string
///@param right UTF-8 string
double closestMatchFuzzySimilarity(
    const std::string& left,
    const std::string& right);

///@param left UTF-8 string
///@param right UTF-8 string
double closestMatchFuzzySimilarity(
    const std::string& left,
    const std::string& right,
    int distanceThreshold);

///@param left UTF-8 string
///@param right UTF-8 string
double closestMatchFuzzySimilarity_Boer(
    const std::string& left,
    const std::string& right);

///@param left UTF-8 string
///@param right UTF-8 string
double jaroWinklerDistance(
    const std::string& left,
    const std::string& right);

///@param left UTF-8 string
///@param right UTF-8 string
int levenshteinDistance(
    const std::string& left,
    const std::string& right);

///@param left UTF-8 string
///@param right UTF-8 string
int levenshteinDistance_DynamicProgramming(
    const std::string& left,
    const std::string& right);

///@param left UTF-8 string
///@param right UTF-8 string
int levenshteinDistance_DynamicProgramming_LinearSpace(
    const std::string& left,
    const std::string& right);

///@param left UTF-8 string
///@param right UTF-8 string
int levenshteinDistance_DynamicProgramming_ReplacementCost1(
    const std::string& left,
    const std::string& right);

///@param left UTF-8 string
///@param right UTF-8 string
int levenshteinDistance_ONDGreedyAlgorithm(
    const std::string& left,
    const std::string& right);

///@param left UTF-8 string
///@param right UTF-8 string
int levenshteinDistance_ONDGreedyAlgorithm_Threshold(
    const std::string& left,
    const std::string& right,
    int threshold);

///@param left UTF-8 string
///@param right UTF-8 string
int computeLCSLength_DynamicProgramming(
    const std::string& left,
    const std::string& right);

///@param left UTF-8 string
///@param right UTF-8 string
int computeLCSLength_ONDGreedyAlgorithm(
    const std::string& left,
    const std::string& right);

///@param left UTF-8 string
///@param right UTF-8 string
int computeLCSLengthInLinearSpace(
    const std::string& left,
    const std::string& right);

///@param left UTF-8 string
///@param right UTF-8 string
std::vector<int> LCS_Column(
    const std::string& left,
    const std::string& right,
    std::size_t m,
    std::size_t n);

} // namespace somera
