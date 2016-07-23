// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#include "somera/CommandLineParser.h"
#include "somera/FileSystem.h"
#include "somera/Optional.h"
#include "somera/StringHelper.h"
#include "Error.h"
#include "WhatIsThisFile.h"
#include <iostream>
#include <regex>
#include <set>

using somera::CommandLineParser;
using somera::Optional;
using somera::NullOpt;
using somera::Error;
using somera::MakeError;
using somera::WhatIsThisFile;
using somera::FileDetection;
namespace FileSystem = somera::FileSystem;
namespace StringHelper = somera::StringHelper;

namespace {

void setupCommandLineParser(CommandLineParser & parser)
{
    using somera::CommandLineArgumentType::Flag;
    using somera::CommandLineArgumentType::JoinedOrSeparate;
    parser.setUsageText("what-is-this-file [directory path]");
    parser.addArgument("-h", Flag, "Display available options");
    parser.addArgument("-help", Flag, "Display available options");
}

void readFile(const std::string& path)
{
    WhatIsThisFile witf;

    FileDetection detection;
    Error error;
    std::tie(detection, error) = witf.Detect(path);

    if (error) {
        std::cerr << error.What() << std::endl;
        return;
    }

    if (detection.type.empty()) {
        std::cerr << "error: Cannot detect the file type. " << path << std::endl;
        return;
    }

    std::cout << detection.type << std::endl;
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
        readFile(path);
    }

    return 0;
}
