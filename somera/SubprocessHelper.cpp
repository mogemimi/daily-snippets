// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "SubprocessHelper.h"
#include <cassert>
#include <cstdio>
#include <utility>

namespace somera {
namespace {

FILE* openProcess(const char* command, const char* mode)
{
#if defined(_MSC_VER)
    return ::_popen(command, mode);
#else
    return ::popen(command, mode);
#endif
}

int closeProcess(FILE* stream)
{
#if defined(_MSC_VER)
    return ::_pclose(stream);
#else
    return ::pclose(stream);
#endif
}

} // unnamed namespace

std::tuple<std::string, std::error_code>
SubprocessHelper::call(const std::string& command)
{
    assert(!command.empty());
    constexpr int maxBufferSize = 255;
    char buffer[maxBufferSize];
    ::FILE* stream = openProcess(command.c_str(), "r");
    if (stream == nullptr) {
        closeProcess(stream);
        // error: Failed to call popen()
        std::error_code err {errno, std::generic_category()};
        return std::make_tuple(std::string{}, std::move(err));
    }
    std::string output;
    while (::fgets(buffer, maxBufferSize, stream) != nullptr) {
        output.append(buffer);
    }
    if (closeProcess(stream) != 0) {
        // error: Failed to call popen()
        std::error_code err {errno, std::generic_category()};
        return std::make_tuple(std::move(output), std::move(err));
    }
    return std::make_tuple(std::move(output), std::error_code{});
}

} // namespace somera
