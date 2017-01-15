// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "StringHelper.h"
#include <algorithm>
#include <cassert>
#include <cstdarg>
#include <iterator>
#include <type_traits>
#include <utility>

namespace somera {
namespace {

std::string UnsafeToFormatString(char const* format, std::va_list arg)
{
    std::va_list copiedArguments;
    va_copy(copiedArguments, arg);
#ifdef _MSC_VER
    char buffer[2048];
    std::memset(buffer, 0, sizeof(buffer));
    auto const length = vsnprintf_s(buffer, _countof(buffer), format, copiedArguments);
    static_assert(std::is_signed<decltype(length)>::value, "");
    va_end(copiedArguments);
    assert(length > 0);
    std::string result(buffer, length);
    assert(result.size() == static_cast<std::size_t>(length));
#else
#if __cplusplus >= 201103L
    using std::vsnprintf;
#endif
    auto const length = vsnprintf(nullptr, 0, format, copiedArguments);
    static_assert(std::is_signed<decltype(length)>::value, "");
    va_end(copiedArguments);
    assert(length > 0);
    std::string result(length + 1, '\0');
    vsnprintf(&result.front(), result.size(), format, arg);
    assert(result.back() == '\0');
    result.resize(length);
#endif
    return result;
}

} // unnamed namespace

bool StringHelper::startWith(const std::string& text, const std::string& prefix)
{
    return (text.size() >= prefix.size())
        && (text.compare(0, prefix.size(), prefix) == 0);
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

std::string StringHelper::toLower(const std::string& source)
{
    std::string output = source;
    std::transform(output.begin(), output.end(), output.begin(), ::tolower);
    return output;
}

std::string StringHelper::toUpper(const std::string& source)
{
    std::string output = source;
    std::transform(output.begin(), output.end(), output.begin(), ::toupper);
    return output;
}

std::string StringHelper::replace(
    const std::string& source,
    const std::string& from,
    const std::string& to)
{
    if (from.empty()) {
        return source;
    }
    auto result = source;
    std::string::size_type start = 0;
    while ((start = result.find(from, start)) != std::string::npos) {
        result.replace(start, from.length(), to);
        start += to.length();
    }
    return result;
}

std::vector<std::string>
StringHelper::split(const std::string& source, char separator)
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

std::string StringHelper::trimRight(const std::string& source, char separator)
{
    const auto func = [&](char c){ return c != separator; };
    std::string result(
        std::begin(source),
        std::find_if(std::rbegin(source), std::rend(source), func).base());
    return result;
}

std::string StringHelper::trimLeft(const std::string& source, char separator)
{
    const auto func = [&](char c){ return c != separator; };
    std::string result(
        std::find_if(std::begin(source), std::end(source), func),
        std::end(source));
    return result;
}

std::string StringHelper::trimRight(
    const std::string& source,
    std::function<bool(char)> isSeparator)
{
    auto func = std::not1(std::move(isSeparator));
    std::string result(
        std::begin(source),
        std::find_if(std::rbegin(source), std::rend(source), func).base());
    return result;
}

std::string StringHelper::trimLeft(
    const std::string& source,
    std::function<bool(char)> isSeparator)
{
    auto func = std::not1(std::move(isSeparator));
    std::string result(
        std::find_if(std::begin(source), std::end(source), func),
        std::end(source));
    return result;
}

std::string StringHelper::format(char const* formatText, ...)
{
    std::va_list arg;
    va_start(arg, formatText);
    auto result = UnsafeToFormatString(formatText, arg);
    va_end(arg);
    return result;
}

} // namespace somera
