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
    parser.setUsageText("glsl-include [directory path]");
    parser.addArgument("-h", Flag, "Display available options");
    parser.addArgument("-help", Flag, "Display available options");
}

std::string includeGLSLFilesRecursive(const std::string& path, std::set<std::string> & includes)
{
    if (FileSystem::isDirectory(path)) {
        std::cerr << "error: " << path << " is directory, not text file." << std::endl;
        return "";
    }

    std::ifstream input(path);
    if (!input) {
        return "";
    }
    std::istreambuf_iterator<char> start(input);
    std::istreambuf_iterator<char> end;
    std::string text(start, end);
    input.close();

    auto currentDirectory = FileSystem::getDirectoryName(FileSystem::normalize(path));

    auto lines = StringHelper::split(text, '\n');
    text.clear();
    for (const auto& line : lines) {
        std::regex includeRegex(R"(\s*#\s*include\s+\"([\w\.\/\\]+)\")");
        std::smatch match;

        bool matched = std::regex_match(line, match, includeRegex);
        if (!matched || match.size() != 2) {
            text += line;
            text += '\n';
            continue;
        }

        auto includePath = FileSystem::join(currentDirectory,  match[1]);
        if (includes.find(includePath) == includes.end()) {
            includes.insert(includePath);
            text += includeGLSLFilesRecursive(includePath, includes);
        }
        text += '\n';
    }

    return text;
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
        std::set<std::string> includes;
        includes.insert(FileSystem::normalize(path));
        std::cout << includeGLSLFilesRecursive(path, includes);
    }

    return 0;
}
