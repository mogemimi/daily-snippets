// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "somera/CommandLineParser.h"
#include "somera/StringHelper.h"
#include <iostream>
#include <fstream>
#include <regex>

using namespace somera;

namespace {

void setupCommandLineParser(CommandLineParser & parser)
{
    using somera::CommandLineArgumentType::Flag;
    using somera::CommandLineArgumentType::JoinedOrSeparate;
    parser.setUsageText("pomdog-refactor [options ...] [source file ...]");
    parser.addArgument("-h", Flag, "Display available options");
    parser.addArgument("-help", Flag, "Display available options");
}

std::string trimLastLineBreaks(const std::string& text)
{
    return StringHelper::trimRight(text, '\n') + '\n';
}

std::string replaceHeaderWithPragmaOnce(const std::string& text)
{
    std::regex re(R"(#ifndef POMDOG_[A-Z0-9_]*_HPP\n#define POMDOG_[A-Z0-9_]*_HPP\n((.*\n)*)\n#endif \/\/ POMDOG_[A-Z0-9_]*_HPP)");
    return std::regex_replace(text, re, "#pragma once\n$1");
}

std::string replaceLicenseYear(const std::string& text)
{
    return StringHelper::replace(
        text,
        "2013-2015 mogemimi.",
        "2013-2016 mogemimi.");
}

std::string replaceLicense(const std::string& text)
{
    return StringHelper::replace(
        text,
"// Copyright (c) 2013-2016 mogemimi.\n"
"// Distributed under the MIT license. See LICENSE.md file for details.",
"// Copyright (c) 2013-2016 mogemimi. Distributed under the MIT license.");
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

    text = replaceHeaderWithPragmaOnce(text);
    text = trimLastLineBreaks(text);
    text = replaceLicenseYear(text);
    text = replaceLicense(text);

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
    std::cout << "ok" << std::endl;
    return 0;
}
