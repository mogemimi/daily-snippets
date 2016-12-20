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
    parser.setUsageText("approximate-winter [options ...] [C/C++ file ...]");
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

void PrintDiff(const std::vector<somera::DiffHunk<char>>& diffHunks)
{
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

void TestCase(const std::string& a, const std::string& b)
{
    auto x = somera::EditDistance::levenshteinDistance_DynamicProgramming(a, b);
    auto y = somera::EditDistance::levenshteinDistance_ONDGreedyAlgorithm(a, b);
    std::cout
        << x << (x == y ? " == " : " != ") << y
        << "  (" << a << ", " << b << ")" << std::endl;

    PrintDiff(somera::computeDiff(a, b));
    PrintDiff(somera::computeDiff_ONDGreedyAlgorithm(a, b));
}

std::string Reverse(std::string && s)
{
    std::reverse(std::begin(s), std::end(s));
    return s;
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
//    std::cout
//        << "Measured time (sec): "
//        << duration_cast<std::chrono::duration<double>>(end - start).count()
//        << " seconds" << std::endl;
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
    TestCase("xc", "xxc");
    TestCase("xxc", "xc");
    TestCase("vertex", "index");
    TestCase("vertices", "vertex");
    TestCase("vertices", "indices");
    TestCase("indices", "vertices");
    TestCase(Reverse("indices"), Reverse("vertices"));
    TestCase("vertices2", "indices");
    TestCase("vert", "ind");
    TestCase("a", "b");
    TestCase("aa", "bb");
    TestCase("a", "bbbbb");
    TestCase("aaaaa", "bbbbb");
    TestCase("AGCTCTATAGATA", "TCGCTGATAGTTTCTAAGAGAGAGCT");
    TestCase("TCGCTGATAGTTTCTAAGAGAGAGCT", "AGCTCTATAGATA");
    TestCase(Reverse("TCGCTGATAGTTTCTAAGAGAGAGCT"), Reverse("AGCTCTATAGATA"));

    measurePerformanceTime([] {
//        auto f = somera::EditDistance::levenshteinDistance_DynamicProgramming;
        auto f = somera::computeDiff_DynamicProgramming;
        f("xxxxxxxxxxxxxxxxxxxxxx", "AGCTCTATAGATAAGCTCTATAGATA");
        f("AGCTCTATAGAAGCAGCTCATAGATAAGCTCTATAGATATCTATAGAT", "xxxxxxxxxxxxxxxxxxxxxx");
    });

    measurePerformanceTime([] {
//        auto f = somera::EditDistance::levenshteinDistance_ONDGreedyAlgorithm;
        auto f = somera::computeDiff_ONDGreedyAlgorithm;
        f("xxxxxxxxxxxxxxxxxxxxxx", "AGCTCTATAGATAAGCTCTATAGATA");
        f("AGCTCTATAGAAGCAGCTCATAGATAAGCTCTATAGATATCTATAGAT", "xxxxxxxxxxxxxxxxxxxxxx");
    });

    return 0;
}
