// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#pragma once

#include "somera/Optional.h"
#include <string>

namespace somera {

enum class TerminalColor {
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White
};

std::string changeTerminalTextColor(
    const std::string& text,
    TerminalColor textColor,
    somera::Optional<TerminalColor> backgroundColor = somera::NullOpt);

} // namespace somera
