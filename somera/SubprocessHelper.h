// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#pragma once

#include <string>
#include <system_error>
#include <tuple>

namespace somera {
namespace SubprocessHelper {

std::tuple<std::string, std::error_code> call(const std::string& command);

} // namespace SubprocessHelper
} // namespace somera
