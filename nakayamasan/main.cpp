// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#include "somera/CommandLineParser.h"
#include "somera/FileSystem.h"
#include "somera/Optional.h"
#include "somera/StringHelper.h"
#include "somera/SubprocessHelper.h"
#include <iostream>
#include <fstream>
#include <chrono>

using somera::CommandLineParser;
using somera::Optional;
using somera::NullOpt;
namespace FileSystem = somera::FileSystem;
namespace StringHelper = somera::StringHelper;
namespace SubprocessHelper = somera::SubprocessHelper;

namespace {

void setupCommandLineParser(CommandLineParser & parser)
{
    using somera::CommandLineArgumentType::Flag;
    using somera::CommandLineArgumentType::JoinedOrSeparate;
    parser.setUsageText("nakayamasan [options ...]");
    parser.addArgument("-h", Flag, "Display available options");
    parser.addArgument("-help", Flag, "Display available options");
}

std::string getTwoMonthsAgo()
{
    auto twoMonths = std::chrono::hours(24 * 30 * 2);

    using std::chrono::system_clock;
    auto now = system_clock::now();
    auto tt = system_clock::to_time_t(now - twoMonths);
    auto utcTime = *gmtime(&tt);

    return StringHelper::format("%04d-%02d-%02d", utcTime.tm_year + 1900, utcTime.tm_mon + 1, utcTime.tm_mday);
}

bool compareYyyyMmDd(const std::string& a, const std::string& b)
{
    return a < b;
}

void enumerateFileList(const std::string& directory)
{
    std::error_code err;
    std::string stringResult;
    std::tie(stringResult, err) = SubprocessHelper::call("git ls-files");

    if (err) {
        std::cerr << "error: enumerateFileList(): " << stringResult;
        return;
    }

    std::vector<std::string> olderFiles;

    const auto twoMonthsAgo = getTwoMonthsAgo();

    auto files = StringHelper::split(stringResult, '\n');
    for (auto & file : files) {
        std::tie(stringResult, err) = SubprocessHelper::call(
            "git log --date=short --pretty=format:'%ad' -n1 " + file);
        if (err) {
            std::cerr << "error: enumerateFileList()";
            return;
        }

        const auto& date = stringResult;
        if (compareYyyyMmDd(date, twoMonthsAgo)) {
            olderFiles.push_back(file);
        }
    }

    for (auto& file : olderFiles) {
        std::cout << file << std::endl;
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
        enumerateFileList(path);
    }

    return 0;
}
