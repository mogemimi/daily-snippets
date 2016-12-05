// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#include "EditDistance.h"
#include "WordDiff.h"
#include "WordSegmenter.h"
#include "somera/CommandLineParser.h"
#include "somera/FileSystem.h"
#include "somera/Optional.h"
#include "somera/StringHelper.h"
#include <iostream>
#include <fstream>
#include <array>

#include <iomanip>

using somera::CommandLineParser;
using somera::Optional;
using somera::NullOpt;
namespace StringHelper = somera::StringHelper;

namespace {

void SetupCommandLineParser(CommandLineParser & parser)
{
    using Type = somera::CommandLineArgumentType;
    parser.setUsageText("diff-summer [options ...] [C/C++ file ...]");
    parser.addArgument("-h", Type::Flag, "Display available options");
    parser.addArgument("-help", Type::Flag, "Display available options");
    parser.addArgument("-v", Type::Flag, "Display version");
}

#if 0

int getBuildMonth()
{
    // NOTE: __DATE__ is "Mmm dd yyyy"
    if (std::strncmp(__DATE__, "Jan", 3) == 0) { return 1; }
    if (std::strncmp(__DATE__, "F", 1) == 0) { return 2; }
    if (std::strncmp(__DATE__, "Mar", 3) == 0) { return 3; }
    if (std::strncmp(__DATE__, "Ap", 2) == 0) { return 4; }
    if (std::strncmp(__DATE__, "May", 3) == 0) { return 5; }
    if (std::strncmp(__DATE__, "Jun", 3) == 0) { return 6; }
    if (std::strncmp(__DATE__, "Jul", 3) == 0) { return 7; }
    if (std::strncmp(__DATE__, "Au", 2) == 0) { return 8; }
    if (std::strncmp(__DATE__, "S", 1) == 0) { return 9; }
    if (std::strncmp(__DATE__, "O", 1) == 0) { return 10; }
    if (std::strncmp(__DATE__, "N", 1) == 0) { return 11; }
    return 12;
}

int getBuildDay()
{
    // NOTE: __DATE__ is "Mmm dd yyyy"
    int day = (__DATE__[5] - '0');
    if (__DATE__[4] >= '0') {
        day += ((__DATE__[4] - '0') * 10);
    }
    return day;
}

std::string BuildNumber()
{
    // http://stackoverflow.com/questions/11697820/how-to-use-date-and-time-predefined-macros-in-as-two-integers-then-stri

    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << getBuildMonth();
    ss << '-';
    ss << std::setfill('0') << std::setw(2) << getBuildDay();

    return ss.str();
}

#endif

void TestCase(const std::string& a, const std::string& b)
{
    auto x = somera::EditDistance::levenshteinDistance(a, b);
    auto y = somera::EditDistance::levenshteinDistance_ONDGreedyAlgorithm(a, b);
    std::cout
        << x << (x == y ? " == " : " != ") << y
        << "  (" << a << ", " << b << ")" << std::endl;

    auto diffHunks = somera::computeDiff_ONDGreedyAlgorithm(a, b);

    for (auto & hunk : diffHunks) {
        if (hunk.operation == somera::DiffOperation::Deletion) {
            std::cout << "-";
        }
        else if (hunk.operation == somera::DiffOperation::Insertion) {
            std::cout << "+";
        }
        else if (hunk.operation == somera::DiffOperation::Equality) {
            std::cout << "=";
        }
        std::cout << hunk.text;
    }
    std::cout << std::endl;
}

} // unnamed namespace

int main(int argc, char *argv[])
{
    CommandLineParser parser;
    SetupCommandLineParser(parser);
    parser.parse(argc, argv);

    if (parser.hasParseError()) {
        std::cerr << parser.getErrorMessage() << std::endl;
        return 1;
    }
    if (parser.exists("-h") || parser.exists("-help")) {
        std::cout << parser.getHelpText() << std::endl;
        return 0;
    }

    TestCase("", "");
    TestCase("", "a");
    TestCase("a", "");
    TestCase("a", "a");
    TestCase("sitting", "sitting");
    TestCase("kitten", "kitten");
    TestCase("sitting", "kitten");
    TestCase("kitten", "sitting");
    TestCase("book", "back");
    TestCase("vertices", "indices");
    TestCase("indices", "vertices");
    TestCase("vertices2", "indices");
    TestCase("vert", "ind");
    TestCase("a", "b");
    TestCase("aa", "bb");
    TestCase("a", "bbbbb");
    TestCase("aaaaa", "bbbbb");
    TestCase("AGCTCTATAGATA", "TCGCTGATAGTTTCTAAGAGAGAGCT");
    TestCase("TCGCTGATAGTTTCTAAGAGAGAGCT", "AGCTCTATAGATA");

    return 0;
}
