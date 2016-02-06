// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#pragma once

#include <functional>
#include <string>
#include <vector>

namespace somera {
namespace StringHelper {

bool startWith(const std::string& source, const std::string& prefix);

std::string toLower(const std::string& source);

std::string toUpper(const std::string& source);

std::string replace(
    const std::string& source,
    const std::string& from,
    const std::string& to);

std::vector<std::string> split(const std::string& source, char separator);

std::vector<std::string> split(
    const std::string& source,
    const std::string& separator);

std::string trimRight(const std::string& source, char separator);

std::string trimLeft(const std::string& source, char separator);

std::string trimRight(
    const std::string& source,
    std::function<bool(char)> isSeparator);

std::string trimLeft(
    const std::string& source,
    std::function<bool(char)> isSeparator);

std::string format(char const* formatText, ...)
#if defined(__has_attribute)
#if __has_attribute(format)
__attribute__((__format__(printf, 1, 2)));
#endif
#elif __GNUC__ >= 4
__attribute__((__format__(printf, 1, 2)));
#else
;
#endif

} // namespace StringHelper
} // namespace somera
