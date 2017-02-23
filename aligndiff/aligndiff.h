// Copyright (c) 2017 mogemimi. Distributed under the MIT license.

#include <vector>
#include <string>

namespace aligndiff {

enum class DiffOperation {
    Equality = 0,
    Insertion = 1,
    Deletion = -1,
};

struct DiffEdit {
    char character;
    DiffOperation operation;
};

struct DiffHunk {
    std::string text;
    DiffOperation operation;
};

// -------------------------------
// Utility
// -------------------------------

///@brief Create a new operation of an edit-script.
DiffEdit makeDiffEdit(char character, DiffOperation operation);

///@brief Sort sequence of edits (called an edit-script) for readability, using odd-even sort.
void sortDiffEdits(std::vector<DiffEdit> & edits);

///@brief Convert edit-script to UNIX's 'diff'-like hunks.
std::vector<DiffHunk> convertToDiffHunk(const std::vector<DiffEdit>& edits);

///@brief Convert edit-script to longest common subsequence (LCS).
std::string convertToLCS(const std::vector<DiffEdit>& edits);

///@brief Print m x n DP table (called a edit-graph).
void printEditGraphTableAsString(
    const std::string& text1,
    const std::string& text2);

// -------------------------------
// Edit distance algorithms
// -------------------------------

///@brief Compute levenshtein distance using dynamic programming, in O(mn) time and O(mn) space.
int computeLevenshteinDistance_DynamicProgramming(
    const std::string& text1,
    const std::string& text2);

///@brief Compute levenshtein distance using dynamic programming with linear-space refinement, in O(mn) time and O(m) space.
int computeLevenshteinDistance_LinearSpace(
    const std::string& text1,
    const std::string& text2);

///@brief Compute levenshtein distance using O(ND) greedy algorithm, in O((m+n)D) time and O(m + n) space.
int computeLevenshteinDistance_ONDGreedyAlgorithm(
    const std::string& text1,
    const std::string& text2);

// -------------------------------
// LCS length algorithms
// -------------------------------

///@brief Compute LCS length using dynamic programming, in O(mn) time and O(mn) space.
int computeLCSLength_DynamicProgramming(
    const std::string& text1,
    const std::string& text2);

///@brief Compute LCS length using dynamic programming with linear-space refinement, in O(mn) time and O(m) space.
int computeLCSLength_LinearSpace(
    const std::string& text1,
    const std::string& text2);

///@brief Compute LCS length using O(ND) greedy algorithm, in O((m+n)D) time and O(m + n) space.
int computeLCSLength_ONDGreedyAlgorithm(
    const std::string& text1,
    const std::string& text2);

// -------------------------------
// Shortest edit script algorithms
// -------------------------------

///@brief Compute shortest edit script (SES) using dynamic programming, in O(mn) time and O(mn) space.
std::vector<DiffEdit> computeShortestEditScript_DynamicProgramming(
    const std::string& text1,
    const std::string& text2);

///@brief Compute shortest edit script (SES) using divide and conquer, in O(mn) time and O(m + n) space.
std::vector<DiffEdit> computeShortestEditScript_LinearSpace(
    const std::string& text1,
    const std::string& text2);

///@brief Compute shortest edit script (SES) using O(ND) greedy algorithm in O(mn) time and O(mn) space.
///@note This function doesn't use the 'divide and conquer' refinement (please see also Myers 1987 "Refinements 4b").
std::vector<DiffEdit> computeShortestEditScript_ONDGreedyAlgorithm(
    const std::string& text1,
    const std::string& text2);

///@brief Compute shortest edit script (SES) using divide and conquer and 'weaving' refinement, in O(mn) time and O(m + n) space.
std::vector<DiffEdit> computeShortestEditScript_WeaveingLinearSpace(
    const std::string& text1,
    const std::string& text2);

} // namespace aligndiff
