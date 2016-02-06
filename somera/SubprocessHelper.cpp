// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "SubprocessHelper.h"
#include <cassert>
#include <cstdio>
#include <utility>

namespace somera {

std::string SubprocessHelper::call(const std::string& command)
{
    assert(!command.empty());
    constexpr int maxBufferSize = 255;
    char buffer[maxBufferSize];
    ::FILE* stream = ::popen(command.c_str(), "r");
    if (stream == nullptr) {
        ::pclose(stream);
        return "";
    }
    std::string output;
    while (::fgets(buffer, maxBufferSize, stream) != nullptr) {
        output.append(buffer);
    }
    ::pclose(stream);
    return std::move(output);
}

} // namespace somera
