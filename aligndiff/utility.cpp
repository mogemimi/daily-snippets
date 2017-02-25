// Copyright (c) 2017 mogemimi. Distributed under the MIT license.

#include "utility.h"
#include <cassert>

namespace aligndiff {

ArgumentsParseResult parseArguments(int argc, const char *argv[])
{
    assert(argc > 0);
    assert(argv != nullptr);

    ArgumentsParseResult result;
    if (argc >= 1) {
        result.executablePath = argv[0];
    }
    if (argc >= 2) {
        auto argument = argv[1];
        if (argument[0] == '-') {
            result.operation = argument;
        }
    }
    for (int i = 2; i < argc; i++) {
        auto argument = argv[i];
        result.parameters.push_back(argument);
    }
    return result;
}

} // namespace aligndiff
