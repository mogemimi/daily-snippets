#pragma once

#include <functional>
#include <string>

namespace StringHelper {

bool startWith(const std::string& text, const std::string& prefix);

bool endWith(const std::string& text, const std::string& suffix);

std::string trimRight(const std::string& source, char separator);

std::string trimLeft(const std::string& source, char separator);

std::string trimRight(const std::string& source, std::function<bool(char)> isSeparator);

std::string trimLeft(const std::string& source, std::function<bool(char)> isSeparator);

} // namespace StringHelper
