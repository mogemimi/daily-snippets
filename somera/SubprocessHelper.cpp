// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "SubprocessHelper.h"
#include <cassert>
#include <cstdio>
#include <utility>

namespace somera {

std::tuple<std::string, std::error_code>
SubprocessHelper::call(const std::string& command)
{
    assert(!command.empty());
    constexpr int maxBufferSize = 255;
    char buffer[maxBufferSize];
    ::FILE* stream = ::popen(command.c_str(), "r");
    if (stream == nullptr) {
        ::pclose(stream);
        // error: Failed to call popen()
        std::error_code err {errno, std::generic_category()};
        return std::make_tuple(std::string{}, std::move(err));
    }
    std::string output;
    while (::fgets(buffer, maxBufferSize, stream) != nullptr) {
        output.append(buffer);
    }
    if (::pclose(stream) != 0) {
        // error: Failed to call popen()
        std::error_code err {errno, std::generic_category()};
        return std::make_tuple(std::move(output), std::move(err));
    }
    return std::make_tuple(std::move(output), std::error_code{});
}

} // namespace somera
