// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#include "somera/CommandLineParser.h"
#include "somera/FileSystem.h"
#include "somera/Optional.h"
#include "somera/StringHelper.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <set>

using somera::CommandLineParser;
using somera::Optional;
using somera::NullOpt;
namespace FileSystem = somera::FileSystem;
namespace StringHelper = somera::StringHelper;

namespace {

void setupCommandLineParser(CommandLineParser & parser)
{
    using somera::CommandLineArgumentType::Flag;
    using somera::CommandLineArgumentType::JoinedOrSeparate;
    parser.setUsageText("matoi [directory path]");
    parser.addArgument("-h", Flag, "Display available options");
    parser.addArgument("-help", Flag, "Display available options");
}

void refactorSourceCode(const std::string& path)
{
    if (FileSystem::isDirectory(path)) {
        std::cerr << "error: " << path << " is directory, not text file." << std::endl;
        return;
    }

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

    std::vector<std::set<std::string>> includeSetStack;
    includeSetStack.push_back(std::set<std::string>{});

    auto lines = StringHelper::split(text, '\n');
    const auto lastLine = lines.back();
    lines.pop_back();
    text.clear();
    for (const auto& line : lines) {
        using StringHelper::trimLeft;
        using StringHelper::trimRight;
        std::string chunk;
        chunk = trimRight(trimRight(line, ' '), '\t');
        chunk = trimLeft(trimLeft(chunk, ' '), '\t');

        if (!StringHelper::startWith(chunk, "#include")) {
            if (StringHelper::startWith(chunk, "#if")) {
                includeSetStack.push_back(std::set<std::string>{});
            }
            else if (StringHelper::startWith(chunk, "#elif")
                || StringHelper::startWith(chunk, "#else")) {
                if (includeSetStack.empty()) {
                    std::cout << "Warning: preprocessor mismatch" << std::endl;
                }
                if (!includeSetStack.empty()) {
                    includeSetStack.pop_back();
                }
                includeSetStack.push_back(std::set<std::string>{});
            }
            else if (StringHelper::startWith(chunk, "#endif")) {
                if (includeSetStack.empty()) {
                    std::cout << "Warning: preprocessor mismatch" << std::endl;
                }
                if (!includeSetStack.empty()) {
                    includeSetStack.pop_back();
                }
            }
            text += line;
            text += '\n';
            continue;
        }

        auto findInclude = [&includeSetStack](const std::string& headerPath) -> bool {
            for (const auto& includes : includeSetStack) {
                auto iter = includes.find(headerPath);
                if (iter != std::end(includes)) {
                    return true;
                }
            }
            return false;
        };

        if (!findInclude(chunk)) {
            text += line;
            text += '\n';
            assert(!includeSetStack.empty());
            auto & includes = includeSetStack.back();
            includes.emplace(std::move(chunk));
            continue;
        }
        std::cout << "Found the dup: '" << chunk << "' at " << path << std::endl;
    }
    text += lastLine;

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
