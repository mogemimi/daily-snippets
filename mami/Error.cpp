// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#include "Error.h"

namespace somera {

// MARK: Error

Error::operator bool() const noexcept
{
    return description.operator bool();
}

std::string Error::What() const noexcept
{
    std::string what;
    bool needToSeparate = false;
    if (description) {
        what += *description;
        needToSeparate = true;
    }
    if (file) {
        if (needToSeparate) {
            what += ", ";
        }
        what += *file;
        needToSeparate = true;
    }
    if (line) {
        if (needToSeparate) {
            what += ", Line=";
        }
        what += *line;
    }
    return what;
}

Error MakeError(const std::string& description)
{
    Error error;
    error.description = description;
    return error;
}

} // namespace somera
