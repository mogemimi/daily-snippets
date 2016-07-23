// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#include "Error.h"
#include <sstream>

namespace somera {

Error::operator bool() const noexcept
{
    return description.operator bool();
}

std::string Error::What() const noexcept
{
    std::stringstream what;
    bool needToSeparate = false;
    if (description) {
        what << "error: ";
        what << *description;
        needToSeparate = true;
    }
    if (file) {
        if (needToSeparate) {
            what << ", ";
        }
        what << *file;
        needToSeparate = true;
    }
    if (line) {
        if (needToSeparate) {
            what << ", Line=";
        }
        what << *line;
    }
    return what.str();
}

Error MakeError(const std::string& description)
{
    Error error;
    error.description = description;
    return error;
}

Error MakeError(const std::error_code& errorCode)
{
    Error error;
    error.description = errorCode.message();
    return error;
}

Error MakeError(const std::string& description, const char* file, int line)
{
    Error error;
    error.description = description;
    error.file = file;
    error.line = line;
    return error;
}

} // namespace somera
