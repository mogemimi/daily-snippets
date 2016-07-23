// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#pragma once

#include "somera/Optional.h"
#include <string>
#include <system_error>

namespace somera {

struct Error {
    somera::Optional<std::string> description;
    somera::Optional<std::string> file;
    somera::Optional<int> line;

    operator bool() const noexcept;

    std::string What() const noexcept;
};

Error MakeError(const std::string& description);
Error MakeError(const std::string& description, const char* file, int line);
Error MakeError(const std::error_code& errorCode);

} // namespace somera
