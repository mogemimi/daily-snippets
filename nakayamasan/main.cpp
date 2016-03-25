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
    parser.addArgument("-days", JoinedOrSeparate, "Days ago");
    parser.addArgument("-month", JoinedOrSeparate, "Month ago");
}

std::chrono::hours convertFromDaysToHours(int days)
{
    return std::chrono::hours(24) * days;
}

std::chrono::hours convertFromMonthsToHours(int months)
{
    return std::chrono::hours(24) * 30 * months;
}

std::string getTimeAgo(const std::chrono::hours& hours)
{
    using std::chrono::system_clock;
    auto now = system_clock::now();
    auto tt = system_clock::to_time_t(now - hours);
    auto utcTime = *gmtime(&tt);

    return StringHelper::format("%04d-%02d-%02d", utcTime.tm_year + 1900, utcTime.tm_mon + 1, utcTime.tm_mday);
}

bool compareYyyyMmDd(const std::string& a, const std::string& b)
{
    return a < b;
}

void enumerateFileList(const std::chrono::hours& hours)
{
    std::error_code err;
    std::string stringResult;
    std::tie(stringResult, err) = SubprocessHelper::call("git ls-files");

    if (err) {
        std::cerr << "error: enumerateFileList(): " << stringResult;
        return;
    }

    std::vector<std::string> olderFiles;

    const auto timeAgo = getTimeAgo(hours);

    auto files = StringHelper::split(stringResult, '\n');
    for (auto & file : files) {
        std::tie(stringResult, err) = SubprocessHelper::call(
            "git log --date=short --pretty=format:'%ad' -n1 " + file);
        if (err) {
            std::cerr << "error: enumerateFileList()";
            return;
        }

        const auto& date = stringResult;
        if (compareYyyyMmDd(date, timeAgo)) {
            std::cout << file << std::endl;
            olderFiles.push_back(file);
        }
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

    auto hours = convertFromMonthsToHours(2);
    if (auto months = parser.getValue("-month")) {
        if (months->empty()) {
            std::cerr << "error: invalid arguments" << std::endl;
            return 1;
        }
        hours = convertFromMonthsToHours(std::atoi(months->c_str()));
    }
    if (auto days = parser.getValue("-days")) {
        if (days->empty()) {
            std::cerr << "error: invalid arguments" << std::endl;
            return 1;
        }
        hours = convertFromDaysToHours(std::atoi(days->c_str()));
    }

    enumerateFileList(hours);

    return 0;
}
