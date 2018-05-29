#include "Basic/StringHelper.h"
#include <algorithm>
#include <cassert>
#include <type_traits>
#include <utility>

bool StringHelper::startWith(const std::string& text, const std::string& prefix)
{
    return (text.size() >= prefix.size()) && (text.compare(0, prefix.size(), prefix) == 0);
}

bool StringHelper::endWith(const std::string& text, const std::string& suffix)
{
    if (suffix.empty()) {
        return true;
    }
    if (text.size() < suffix.size()) {
        return false;
    }
    return (text.compare(text.size() - suffix.size(), suffix.size(), suffix) == 0);
}

std::string StringHelper::trimRight(const std::string& source, char separator)
{
    const auto func = [&](char c) { return c != separator; };
    std::string result(
        std::begin(source), std::find_if(std::rbegin(source), std::rend(source), func).base());
    return result;
}

std::string StringHelper::trimLeft(const std::string& source, char separator)
{
    const auto func = [&](char c) { return c != separator; };
    std::string result(std::find_if(std::begin(source), std::end(source), func), std::end(source));
    return result;
}

std::string
StringHelper::trimRight(const std::string& source, std::function<bool(char)> isSeparator)
{
    auto func = std::not1(std::move(isSeparator));
    std::string result(
        std::begin(source), std::find_if(std::rbegin(source), std::rend(source), func).base());
    return result;
}

std::string StringHelper::trimLeft(const std::string& source, std::function<bool(char)> isSeparator)
{
    auto func = std::not1(std::move(isSeparator));
    std::string result(std::find_if(std::begin(source), std::end(source), func), std::end(source));
    return result;
}

std::vector<std::string> StringHelper::split(const std::string& source, char separator)
{
    std::vector<std::string> tokens;
    std::string::size_type start = 0;
    std::string::size_type end = 0;
    while ((end = source.find(separator, start)) != std::string::npos) {
        tokens.push_back(source.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(source.substr(start));
    return tokens;
}

std::vector<std::string>
StringHelper::split(const std::string& source, const std::string& separator)
{
    std::vector<std::string> tokens;
    std::string::size_type start = 0;
    std::string::size_type end = 0;
    while ((end = source.find(separator, start)) != std::string::npos) {
        tokens.push_back(source.substr(start, end - start));
        start = end + separator.size();
    }
    tokens.push_back(source.substr(start));
    return tokens;
}

std::string StringHelper::join(const std::vector<std::string>& source, char separator)
{
    std::string s;
    for (auto& line : source) {
        if (!s.empty()) {
            s += '\n';
        }
        s += line;
    }
    return s;
}
