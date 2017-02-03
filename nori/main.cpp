// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "MSBuild.h"
#include "XcodeProject.h"
#include "somera/CommandLineParser.h"
#include "somera/FileSystem.h"
#include "somera/StringHelper.h"
#include "somera/SubprocessHelper.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using somera::CommandLineParser;
namespace StringHelper = somera::StringHelper;
namespace FileSystem = somera::FileSystem;

namespace {

void setupCommandLineParser(CommandLineParser & parser)
{
    using somera::CommandLineArgumentType;
    parser.setUsageText("nori [options ...] [build file ...]");
    parser.addArgument("-h", CommandLineArgumentType::Flag, "Display available options");
    parser.addArgument("-help", CommandLineArgumentType::Flag, "Display available options");
    parser.addArgument("-I", CommandLineArgumentType::JoinedOrSeparate,
        "Add directory to include search path");
    parser.addArgument("-L", CommandLineArgumentType::JoinedOrSeparate,
        "Add directory to library search path");
    parser.addArgument("-D", CommandLineArgumentType::JoinedOrSeparate,
        "Add predefined macro");
    parser.addArgument("-l", CommandLineArgumentType::JoinedOrSeparate,
        "Search the library when linking");
    parser.addArgument("-O", CommandLineArgumentType::Flag, "Specify the optimization level");
    parser.addArgument("-O0", CommandLineArgumentType::Flag, "Specify the optimization level");
    parser.addArgument("-O1", CommandLineArgumentType::Flag, "Specify the optimization level");
    parser.addArgument("-O2", CommandLineArgumentType::Flag, "Specify the optimization level");
    parser.addArgument("-O3", CommandLineArgumentType::Flag, "Specify the optimization level");
    parser.addArgument("-O4", CommandLineArgumentType::Flag, "Specify the optimization level");
    parser.addArgument("-Ofast", CommandLineArgumentType::Flag, "Specify the optimization level");
    parser.addArgument("-Os", CommandLineArgumentType::Flag, "Specify the optimization level");
    parser.addArgument("-Oz", CommandLineArgumentType::Flag, "Specify the optimization level");
    parser.addArgument("-Og", CommandLineArgumentType::Flag, "Specify the optimization level");
    parser.addArgument("-W", CommandLineArgumentType::JoinedOrSeparate, "Specify a warning option");
    parser.addArgument("-fno-exceptions", CommandLineArgumentType::Flag, "no-exceptions");
    parser.addArgument("-fno-rtti", CommandLineArgumentType::Flag, "no-rtti");
    parser.addArgument("-generator=", CommandLineArgumentType::JoinedOrSeparate,
        "The output formats to generate. Supported format\n"
        "are \"xcode\", \"msbuild\", \"cmake\", \"gyp\", or \"gn\".");
    parser.addArgument("-c", CommandLineArgumentType::JoinedOrSeparate, "TODO");
    parser.addArgument("-o", CommandLineArgumentType::JoinedOrSeparate, "Write output to <file>");
    parser.addArgument("-generator-output=", CommandLineArgumentType::JoinedOrSeparate,
        "Generate build files under the <dir>");
    parser.addArgument("-verbose", CommandLineArgumentType::Flag,
        "Provide additional status output");
    parser.addArgument("-std=", CommandLineArgumentType::JoinedOrSeparate,
        "Language standard to compile for");
    parser.addArgument("-stdlib=", CommandLineArgumentType::JoinedOrSeparate,
        "C++ standard library to use");
}

#if 0

std::string fileToString(const std::string& source)
{
    std::ifstream input(source);
    std::string line;
    std::stringstream stream;
    while (input && std::getline(input, line)) {
        line = somera::StringHelper::replace(line, "\\", "\\\\");
        line = somera::StringHelper::replace(line, "\"", "\\\"");
        line = somera::StringHelper::replace(line, "\r", "\\r");
        line = somera::StringHelper::replace(line, "\t", "  ");
        stream << "\"";
        stream << line;
        stream << "\\n\"\n";
    }
    return stream.str();
}

#endif

void sortByName(std::vector<std::string>& names)
{
    std::sort(std::begin(names), std::end(names),
        [](const auto& a, const auto& b) {
            return StringHelper::toLower(a) < StringHelper::toLower(b);
        });
    names.erase(
        std::unique(std::begin(names), std::end(names)), std::end(names));
}

std::string getAuthorName()
{
    std::error_code err;
    std::string result;
    std::tie(result, err) = somera::SubprocessHelper::call("git config user.name");

    if (err) {
        return "";
    }
    return somera::StringHelper::replace(result, "\n", "");
}

template <class Container, typename Func>
auto eraseIf(Container & container, Func func)
{
    return container.erase(
        std::remove_if(std::begin(container), std::end(container), func),
        std::end(container));
}

} // unnamed namespace

int main(int argc, char *argv[])
{
    CommandLineParser parser;
    setupCommandLineParser(parser);
    parser.parse(argc, argv);

    auto printVerbose = [&](const std::string& text) {
        static const bool verbose = parser.exists("-verbose");
        if (verbose) {
            std::cout << text << std::endl;
        }
    };

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

    somera::CompileOptions options;

    for (auto & path : parser.getValues("-I")) {
        printVerbose("[-I] "+ path);
        options.includeSearchPaths.push_back(path);
    }
    for (auto & path : parser.getValues("-L")) {
        printVerbose("[-L] " + path);
        options.librarySearchPaths.push_back(path);
    }
    for (auto & definition : parser.getValues("-D")) {
        printVerbose("[-D] " + definition);
        options.preprocessorDefinitions.push_back(definition);
    }
    for (auto & path : parser.getValues("-l")) {
        printVerbose("[-l] " + path);
        options.libraries.push_back(path);
    }
    for (auto & path : parser.getPaths()) {
        printVerbose("[Path] " + path);
        options.sources.push_back(path);
    }

    eraseIf(options.sources, [](const std::string& path) {
        return somera::StringHelper::startWith(path, "*");
    });

    if (auto path = parser.getValue("-generator-output=")) {
        options.generatorOutputDirectory = *path;
    }
    options.productName = "MyHoge";
    if (auto path = parser.getValue("-o")) {
        options.productName = *path;
    }
    options.targetName = options.productName;
    options.author = getAuthorName();

    if (auto value = parser.getValue("-std=")) {
        options.buildSettings.emplace("-std=", *value);
    }
    if (auto value = parser.getValue("-stdlib=")) {
        options.buildSettings.emplace("-stdlib=", *value);
    }

    options.enableCppExceptions = !parser.exists("-fno-exceptions");
    options.enableCppRtti = !parser.exists("-fno-rtti");

    for (auto & path : options.includeSearchPaths) {
        if (FileSystem::isAbsolute(path)) {
            continue;
        }
        path = FileSystem::relative(path, options.generatorOutputDirectory);
        printVerbose("[-I (Relative)] " + path);
    }
    for (auto & path : options.librarySearchPaths) {
        if (FileSystem::isAbsolute(path)) {
            continue;
        }
        path = FileSystem::relative(path, options.generatorOutputDirectory);
        printVerbose("[-L (Relative)] " + path);
    }
    for (auto & path : options.libraries) {
        if (FileSystem::isAbsolute(path)) {
            continue;
        }
        path = FileSystem::relative(path, options.generatorOutputDirectory);
        printVerbose("[-l (Relative)] " + path);
    }
    for (auto & path : options.sources) {
        if (FileSystem::isAbsolute(path)) {
            continue;
        }
        path = FileSystem::relative(path, options.generatorOutputDirectory);
        printVerbose("[Path (Relative)] " + path);
    }
    sortByName(options.libraries);
    sortByName(options.sources);

    if (auto generator = parser.getValue("-generator=")) {
        if (*generator == "xcode") {
            auto error = somera::Xcode::GenerateXcodeProject(options);
            if (error.hasError) {
                std::cerr << error.description << std::endl;
                return 1;
            }
            std::cout << "Generated." << std::endl;
        }
        else if (*generator == "msbuild") {
            auto error = somera::MSBuild::GenerateMSBuildProject(options);
            if (error.hasError) {
                std::cerr << error.description << std::endl;
                return 1;
            }
            std::cout << "Generated." << std::endl;
        }
    }

    return 0;
}
