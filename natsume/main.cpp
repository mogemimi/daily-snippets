// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#include "somera/CommandLineParser.h"
#include "somera/FileSystem.h"
#include "somera/Optional.h"
#include "somera/StringHelper.h"
#include <iostream>
#include <fstream>
#include <regex>

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
    parser.setUsageText("norichan [options ...] [build file ...]");
    parser.addArgument("-h", Flag, "Display available options");
    parser.addArgument("-help", Flag, "Display available options");
}

void renameFiles(const std::string& directory, const std::regex& searchString, const std::string& replaceString)
{
    if (!FileSystem::isDirectory(directory)) {
        // error
        std::cerr << "error: Invalid path, not directory." << std::endl;
        return;
    }

    auto result = FileSystem::readDirectory(directory);
    auto files = std::get<0>(result);
    auto error = std::get<1>(result);

    if (error) {
        // error
        std::cerr << "error: Failed to read directory." << std::endl;
        return;
    }

    std::sort(std::begin(files), std::end(files));

    for (auto & file : files) {
        auto newname = std::regex_replace(file, searchString, replaceString);
        if (newname == file) {
            continue;
        }
        if (newname.empty()) {
            continue;
        }
        error = FileSystem::rename(FileSystem::join(directory, file), FileSystem::join(directory, newname));
        if (error) {
            // error
            std::cerr << "error: Failed to rename: " << file << " => " << newname << std::endl;
            continue;
        }
        std::cout << file << " => " << newname << std::endl;
    }
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
        renameFiles(path, std::regex(R"(image_(\d+).png)"), "thumbnail_$1.png");
    }

    return 0;
}
