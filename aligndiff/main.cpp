// Copyright (c) 2017 mogemimi. Distributed under the MIT license.

#include "aligndiff.h"
#include "utility.h"
#include <iostream>
#include <cassert>
#include <string>

namespace {

void showHelpMessage()
{
    std::printf(
        "usage: [-h or other options] [strings...]\n"
        "\n"
        "  -help                         Display available options\n"
        "  -levdist <string1> <string2>  Compute levenshtein distance\n"
        "  -lcslen  <string1> <string2>  Compute the length of \"LCS\" of two strings\n"
        "  -lcs     <string1> <string2>  Display longest-common subsequence (LCS)\n"
        "  -ses     <string1> <string2>  Print shortest edit script (SES)\n"
        "  -diff    <string1> <string2>  Print UNIX's 'diff' like edit script\n"
        "  -align   <string1> <string2>  Print optimal alignment between two strings\n"
        "  -table   <string1> <string2>  Print 'M x N' dynamic programming table\n");
}

void printEditDist(const std::string& a, const std::string& b)
{
    auto distance = aligndiff::computeLevenshteinDistance_ONDGreedyAlgorithm(a, b);
    std::printf("%d\n", distance);
}

void printLCSLength(const std::string& a, const std::string& b)
{
    auto length = aligndiff::computeLCSLength_ONDGreedyAlgorithm(a, b);
    std::printf("%d\n", length);
}

void printLCS(const std::string& a, const std::string& b)
{
    auto ses = aligndiff::computeShortestEditScript_WeaveingLinearSpace(a, b);
    auto lcs = aligndiff::convertToLCS(ses);
    std::printf("%s\n", lcs.c_str());
}

void printSES(const std::string& a, const std::string& b)
{
    auto ses = aligndiff::computeShortestEditScript_WeaveingLinearSpace(a, b);
    for (const auto& edit : ses) {
        switch (edit.operation) {
        case aligndiff::DiffOperation::Equality:
            std::printf("= %c\n", edit.character);
            break;
        case aligndiff::DiffOperation::Insertion:
            std::printf("+ %c\n", edit.character);
            break;
        case aligndiff::DiffOperation::Deletion:
            std::printf("- %c\n", edit.character);
            break;
        }
    }
}

void printDiff(const std::string& a, const std::string& b)
{
    auto ses = aligndiff::computeShortestEditScript_WeaveingLinearSpace(a, b);
    aligndiff::sortDiffEdits(ses);

    auto diffHunks = aligndiff::convertToDiffHunk(ses);
    for (const auto& hunk : diffHunks) {
        switch (hunk.operation) {
        case aligndiff::DiffOperation::Equality:
            std::printf("= %s\n", hunk.text.c_str());
            break;
        case aligndiff::DiffOperation::Insertion:
            std::printf("+ %s\n", hunk.text.c_str());
            break;
        case aligndiff::DiffOperation::Deletion:
            std::printf("- %s\n", hunk.text.c_str());
            break;
        }
    }
}

void printAlign(const std::string& a, const std::string& b)
{
    auto ses = aligndiff::computeShortestEditScript_WeaveingLinearSpace(a, b);
    for (const auto& edit : ses) {
        switch (edit.operation) {
        case aligndiff::DiffOperation::Equality:
        case aligndiff::DiffOperation::Deletion:
            std::printf("%c", edit.character);
            break;
        case aligndiff::DiffOperation::Insertion:
            std::printf("-");
            break;
        }
    }
    std::printf("\n");
    for (const auto& edit : ses) {
        switch (edit.operation) {
        case aligndiff::DiffOperation::Equality:
        case aligndiff::DiffOperation::Insertion:
            std::printf("%c", edit.character);
            break;
        case aligndiff::DiffOperation::Deletion:
            std::printf("-");
            break;
        }
    }
    std::printf("\n");
}

void printTable(const std::string& a, const std::string& b)
{
    aligndiff::printEditGraphTableAsString(a, b);
}

} // end of anonymous namespace

int main(int argc, const char *argv[])
{
    auto arg = aligndiff::parseArguments(argc, argv);

    if ((arg.operation.empty() && arg.parameters.empty()) ||
        (arg.operation == "-h") ||
        (arg.operation == "-help")) {
        showHelpMessage();
        return 0;
    }

    if (arg.operation == "-levdist") {
        if (arg.parameters.size() != 2) {
            std::fprintf(stderr, "error: please specify two strings.\n");
            return 1;
        }
        printEditDist(arg.parameters[0], arg.parameters[1]);
    }
    else if (arg.operation == "-lcslen") {
        if (arg.parameters.size() != 2) {
            std::fprintf(stderr, "error: please specify two strings.\n");
            return 1;
        }
        printLCSLength(arg.parameters[0], arg.parameters[1]);
    }
    else if (arg.operation == "-lcs") {
        if (arg.parameters.size() != 2) {
            std::fprintf(stderr, "error: please specify two strings.\n");
            return 1;
        }
        printLCS(arg.parameters[0], arg.parameters[1]);
    }
    else if (arg.operation == "-ses") {
        if (arg.parameters.size() != 2) {
            std::fprintf(stderr, "error: please specify two strings.\n");
            return 1;
        }
        printSES(arg.parameters[0], arg.parameters[1]);
    }
    else if (arg.operation == "-diff") {
        if (arg.parameters.size() != 2) {
            std::fprintf(stderr, "error: please specify two strings.\n");
            return 1;
        }
        printDiff(arg.parameters[0], arg.parameters[1]);
    }
    else if (arg.operation == "-align") {
        if (arg.parameters.size() != 2) {
            std::fprintf(stderr, "error: please specify two strings.\n");
            return 1;
        }
        printAlign(arg.parameters[0], arg.parameters[1]);
    }
    else if (arg.operation == "-table") {
        if (arg.parameters.size() != 2) {
            std::fprintf(stderr, "error: please specify two strings.\n");
            return 1;
        }
        printTable(arg.parameters[0], arg.parameters[1]);
    }
    else if (!arg.operation.empty()) {
        std::fprintf(stderr, "error: unknown argument %s\n", arg.operation.c_str());
        return 1;
    }
    else {
        showHelpMessage();
        return 0;
    }

    return 0;
}
