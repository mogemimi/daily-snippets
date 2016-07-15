// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#pragma once

#include <string>

namespace somera {

std::u32string toUtf32(const std::string& s);

std::string toUtf8(const std::u32string& s);

} // namespace somera
