// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#pragma once

#include <string>
#include <map>

namespace somera {
namespace HttpUtility {

std::string encodeURIComponent(const std::string& source);

std::string stringify(
    const std::map<std::string, std::string>& params);

} // namespace HttpUtility
} // namespace somera
