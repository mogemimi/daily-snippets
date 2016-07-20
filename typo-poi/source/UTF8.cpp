// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "utf8.h"
#include <cassert>
#include <utility>

#define USE_LLVM_CONVERTUTF 1
#if defined(USE_LLVM_CONVERTUTF)
#include "thirdparty/ConvertUTF.h"
#include <vector>
#else
#include <codecvt>
#include <locale>
#endif

namespace somera {

std::u32string toUtf32(const std::string& utf8)
{
    if (utf8.empty()) {
        return {};
    }

#if defined(USE_LLVM_CONVERTUTF)
    auto src = reinterpret_cast<const UTF8*>(utf8.data());
    auto srcEnd = reinterpret_cast<const UTF8*>(utf8.data() + utf8.size());

    std::u32string result;
    result.resize(utf8.length() + 1);
    auto dest = reinterpret_cast<UTF32*>(&result[0]);
    auto destEnd = dest + result.size();

    ConversionResult CR =
        ::ConvertUTF8toUTF32(&src, srcEnd, &dest, destEnd, strictConversion);
    assert(CR != targetExhausted);

    if (CR != conversionOK) {
        // error
        result.clear();
        return result;
    }

    result.resize(reinterpret_cast<const char32_t*>(dest) - result.data());
    result.shrink_to_fit();
    return result;
#else
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
    return convert.from_bytes(utf8);
#endif
}

std::string toUtf8(const std::u32string& utf32)
{
    if (utf32.empty()) {
        return {};
    }

#if defined(USE_LLVM_CONVERTUTF)
    auto src = reinterpret_cast<const UTF32*>(utf32.data());
    auto srcEnd = reinterpret_cast<const UTF32*>(utf32.data() + utf32.size());

    std::string result;
    result.resize(utf32.length() * UNI_MAX_UTF8_BYTES_PER_CODE_POINT + 1);
    auto dest = reinterpret_cast<UTF8*>(&result[0]);
    auto destEnd = dest + result.size();

    ConversionResult CR =
        ::ConvertUTF32toUTF8(&src, srcEnd, &dest, destEnd, strictConversion);
    assert(CR != targetExhausted);

    if (CR != conversionOK) {
        // error
        result.clear();
        return result;
    }

    result.resize(reinterpret_cast<const char*>(dest) - result.data());
    result.shrink_to_fit();
    return result;
#else
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
    return convert.to_bytes(utf32);
#endif
}

} // namespace somera
