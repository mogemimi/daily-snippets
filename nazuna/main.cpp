// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "somera/CommandLineParser.h"
#include "somera/FileSystem.h"
#include "somera/Optional.h"
#include "somera/StringHelper.h"
#include <iostream>
#include <fstream>

using somera::CommandLineParser;
using somera::Optional;
using somera::NullOpt;
namespace StringHelper = somera::StringHelper;

namespace {

void setupCommandLineParser(CommandLineParser & parser)
{
    using somera::CommandLineArgumentType::Flag;
    using somera::CommandLineArgumentType::JoinedOrSeparate;
    parser.setUsageText("nazuna [options ...] [C/C++ file ...]");
    parser.addArgument("-h", Flag, "Display available options");
    parser.addArgument("-help", Flag, "Display available options");
}

std::string removeUnnecessaryWhitespace(const std::string& text)
{
    using StringHelper::trimRight;
    std::string result;
    for (auto & line : StringHelper::split(text, '\n')) {
        result += trimRight(trimRight(line, ' '), '\t');
        result += '\n';
    }
    return std::move(result);
}

std::string replaceHardTabsWithWhiteSpaces(const std::string& text)
{
    constexpr auto spaces = "    ";
    return StringHelper::replace(text, "\t", spaces);
}

std::string replaceCRLFWithLF(const std::string& text)
{
    return StringHelper::replace(text, "\r\n", "\n");
}

std::string trimLastLineBreaks(const std::string& text)
{
    return StringHelper::trimRight(text, '\n') + '\n';
}

void refactorSourceCode(const std::string& path)
{
    std::ifstream input(path);
    if (!input) {
        return;
    }
    std::istreambuf_iterator<char> start(input);
    std::istreambuf_iterator<char> end;
    std::string text(start, end);
    input.close();

    std::ofstream output(path, std::ios::out | std::ios::trunc);
    if (!output) {
        return;
    }
    text = replaceCRLFWithLF(text);
    text = replaceHardTabsWithWhiteSpaces(text);
    text = removeUnnecessaryWhitespace(text);
    text = trimLastLineBreaks(text);
    output << text;
}

} // unnamed namespace

int main(int argc, char *argv[])
{
    CommandLineParser parser;
    setupCommandLineParser(parser);
    parser.parse(argc, argv);

    if (parser.hasParseError()) {
        std::cerr << parser.getErrorMessage() << std::endl;
        return 1;
    }
    if (parser.exists("-h") || parser.exists("-help")) {
        std::cout << parser.getHelpText() << std::endl;
        return 0;
    }
    if (parser.getPaths().empty()) {
        std::cerr << "error: no input file" << std::endl;
        return 1;
    }

    for (auto & path : parser.getPaths()) {
        refactorSourceCode(path);
    }
    return 0;
}
