// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#pragma once

#include "somera/Optional.h"
#include <string>

namespace somera {

struct Error {
    somera::Optional<std::string> description;
    somera::Optional<std::string> file;
    somera::Optional<int> line;

    operator bool() const noexcept;

    std::string What() const noexcept;
};

Error MakeError(const std::string& description);

} // namespace somera
