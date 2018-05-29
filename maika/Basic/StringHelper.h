#pragma once

#include <functional>
#include <string>
#include <vector>

namespace StringHelper {

bool startWith(const std::string& text, const std::string& prefix);

bool endWith(const std::string& text, const std::string& suffix);

std::string trimRight(const std::string& source, char separator);

std::string trimLeft(const std::string& source, char separator);

std::string trimRight(const std::string& source, std::function<bool(char)> isSeparator);

std::string trimLeft(const std::string& source, std::function<bool(char)> isSeparator);

std::vector<std::string> split(const std::string& source, char separator);

std::vector<std::string> split(const std::string& source, const std::string& separator);

std::string join(const std::vector<std::string>& source, char separator);

} // namespace StringHelper
