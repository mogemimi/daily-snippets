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
