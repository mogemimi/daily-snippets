// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#pragma once

#include "Optional.h"
#include <string>
#include <sstream>
#include <vector>
#include <functional>
#include <map>
#include <set>
#include <vector>

namespace somera {

enum class CommandLineArgumentType {
    Flag,
    JoinedOrSeparate,
};

struct CommandLineArgumentHint {
    std::string name;
    std::string help;
    CommandLineArgumentType type;
    std::vector<std::string> values;
};

struct CommandLineParser {
//    void addArgument(
//        const std::string& help,
//        const std::string& type);

    void addArgument(
        const std::string& flag,
        CommandLineArgumentType type,
        const std::string& help);

    void parse(int argc, char* argv[])
    {
        this->parse(argc, const_cast<const char**>(argv));
    }

    void parse(int argc, const char* argv[]);

    bool hasParseError() const;

    std::string getHelpText() const;

    std::string getErrorMessage() const;

    std::string getExecutablePath() const;

    bool exists(const std::string& flag) const;

    Optional<std::string> getValue(const std::string& name) const;

    std::vector<std::string> getValues(const std::string& name) const;

    std::vector<std::string> getPaths() const;

    void setUsageText(const std::string& usage);

private:
    std::string executablePath;
    std::vector<CommandLineArgumentHint> hints;
    std::set<std::string> flags;
    std::vector<std::string> paths;
    std::stringstream errorMessage;
    std::string usageText;
};

} // namespace somera
