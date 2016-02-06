// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "HttpUtility.h"
#include <sstream>
#include <algorithm>

namespace somera {
namespace {

char toHex(char code)
{
    constexpr auto hex = "0123456789ABCDEF";
    return hex[code & 15];
}

bool isSafeCharacter(char32_t c)
{
    constexpr char32_t characters[] =
        U"-.0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz~";
    return std::binary_search(std::begin(characters), std::end(characters), c);
}

} // unnamed namespace

std::string HttpUtility::encodeURIComponent(const std::string& source)
{
    std::stringstream stream;
    for (const auto& c : source) {
        if (isSafeCharacter(c)) {
            stream << c;
        } else {
            stream << '%' << toHex(c >> 4) << toHex(c & 15);
        }
    }
    return stream.str();
}

std::string HttpUtility::stringify(
    const std::map<std::string, std::string>& params)
{
    std::stringstream stream;
    bool needAmpersand = false;
    for (auto & pair : params) {
        if (needAmpersand) {
            stream << '&';
        }
        stream << pair.first << '=' << encodeURIComponent(pair.second);
        needAmpersand = true;
    }
    return stream.str();
}

} // namespace somera
