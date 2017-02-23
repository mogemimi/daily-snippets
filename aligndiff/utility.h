// Copyright (c) 2017 mogemimi. Distributed under the MIT license.

#include <vector>
#include <string>

namespace aligndiff {

struct ArgumentsParseResult final {
    std::string executablePath;
    std::string operation;
    std::vector<std::string> parameters;
};

ArgumentsParseResult parseArguments(int argc, const char *argv[]);

} // namespace aligndiff
