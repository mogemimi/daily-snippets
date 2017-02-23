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
    for (int i = 1; i < argc; i++) {
        auto argument = argv[i];
        if (argument[0] == '-') {
            result.operation = argument;
        }
        else {
            result.parameters.push_back(argument);
        }
    }
    return result;
}

} // namespace aligndiff
