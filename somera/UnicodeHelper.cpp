// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#include "UnicodeHelper.h"

namespace somera {

bool UnicodeHelper::isGreekAndCoptic(char32_t utf32Character)
{
    // NOTE:
    // Accoding to this paper ( http://unicode.org/charts/PDF/U0370.pdf ),
    // a range of "Greek and Coptic" is 0370-03FF.
    return (0x0370 <= utf32Character && utf32Character <= 0x03FF);
}

bool UnicodeHelper::isLetterlikeSymbols(char32_t utf32Character)
{
    // NOTE:
    // Accoding to this paper ( http://www.unicode.org/charts/PDF/U2100.pdf ),
    // a range of "Letterlike Symbols" is 2100-214F.
    return (0x2100 <= utf32Character && utf32Character <= 0x214F);
}

bool UnicodeHelper::isEnclosedAlphanumerics(char32_t utf32Character)
{
    // NOTE:
    // Accoding to this paper ( http://unicode.org/charts/PDF/U2460.pdf ),
    // a range of "Enclosed Alphanumerics" is 2460-24FF.
    return (0x2460 <= utf32Character && utf32Character <= 0x24FF);
}

bool UnicodeHelper::isBoxDrawing(char32_t utf32Character)
{
    // NOTE:
    // Accoding to this paper ( http://unicode.org/charts/PDF/U2500.pdf ),
    // a range of "Box Drawing" is 2500-257F.
    return (0x2500 <= utf32Character && utf32Character <= 0x257F);
}

bool UnicodeHelper::isBlockElements(char32_t utf32Character)
{
    // NOTE:
    // Accoding to this paper ( http://unicode.org/charts/PDF/U2580.pdf ),
    // a range of "Block Elements" is 2580-259F.
    return (0x2580 <= utf32Character && utf32Character <= 0x259F);
}

bool UnicodeHelper::isMiscellaneousSymbols(char32_t utf32Character)
{
    // NOTE:
    // Accoding to this paper ( http://unicode.org/charts/PDF/U2600.pdf ),
    // a range of "Miscellaneous Symbols" is 2600-26FF.
    return (0x2600 <= utf32Character && utf32Character <= 0x26FF);
}

bool UnicodeHelper::isCJKSymbolsAndPunctuation(char32_t utf32Character)
{
    // NOTE:
    // Accoding to this paper ( http://www.unicode.org/charts/PDF/U3000.pdf ),
    // a range of "CJK Symbols and Punctuation" is 3000-303F.
    return (0x3000 <= utf32Character && utf32Character <= 0x303F);
}

bool UnicodeHelper::isHiragana(char32_t utf32Character)
{
    // NOTE:
    // Accoding to this paper ( http://www.unicode.org/charts/PDF/U3040.pdf ),
    // a range of "Hiragana" is 3040-309F.
    return (0x3040 <= utf32Character && utf32Character <= 0x309F);
}

bool UnicodeHelper::isKatakana(char32_t utf32Character)
{
    // NOTE:
    // Accoding to this paper ( http://www.unicode.org/charts/PDF/U30A0.pdf ),
    // a range of "Katakana" is 30A0-30FF.
    return (0x30A0 <= utf32Character && utf32Character <= 0x30FF);
}

bool UnicodeHelper::isBopomofo(char32_t utf32Character)
{
    // NOTE:
    // Accoding to this paper ( http://unicode.org/charts/PDF/U3100.pdf ),
    // a range of "Bopomofo" is 3100-312F.
    return (0x3100 <= utf32Character && utf32Character <= 0x312F);
}

bool UnicodeHelper::isHangulCompatibilityJamo(char32_t utf32Character)
{
    // NOTE:
    // Accoding to this paper ( http://unicode.org/charts/PDF/U3130.pdf ),
    // a range of "Hangul Compatibility Jamo" is 3130-318F.
    return (0x3130 <= utf32Character && utf32Character <= 0x318F);
}

bool UnicodeHelper::isKanbun(char32_t utf32Character)
{
    // NOTE:
    // Accoding to this paper ( http://unicode.org/charts/PDF/U3190.pdf ),
    // a range of "Kanbun" is 3190-319F.
    return (0x3190 <= utf32Character && utf32Character <= 0x319F);
}

bool UnicodeHelper::isBopomofoExtended(char32_t utf32Character)
{
    // NOTE:
    // Accoding to this paper ( http://unicode.org/charts/PDF/U31A0.pdf ),
    // a range of "Bopomofo Extended" is 31A0-31BF.
    return (0x31A0 <= utf32Character && utf32Character <= 0x31BF);
}

bool UnicodeHelper::isCJKStrokes(char32_t utf32Character)
{
    // NOTE:
    // Accoding to this paper ( http://unicode.org/charts/PDF/U31C0.pdf ),
    // a range of "CJK Strokes" is 31C0-31EF.
    return (0x31C0 <= utf32Character && utf32Character <= 0x31EF);
}

bool UnicodeHelper::isKatakanaPhoneticExtensions(char32_t utf32Character)
{
    // NOTE:
    // Accoding to this paper ( http://unicode.org/charts/PDF/U31F0.pdf ),
    // a range of "Katakana Phonetic Extensions" is 31F0-31FF.
    return (0x31F0 <= utf32Character && utf32Character <= 0x31FF);
}

bool UnicodeHelper::isEnclosedCJKLettersAndMonths(char32_t utf32Character)
{
    // NOTE:
    // Accoding to this paper ( http://unicode.org/charts/PDF/U3200.pdf ),
    // a range of "Enclosed CJK Letters and Months" is 3200-32FF.
    return (0x3200 <= utf32Character && utf32Character <= 0x32FF);
}

bool UnicodeHelper::isCJKCompatibility(char32_t utf32Character)
{
    // NOTE:
    // Accoding to this paper ( http://unicode.org/charts/PDF/U3300.pdf ),
    // a range of "CJK Compatibility" is 3300-33FF.
    return (0x3300 <= utf32Character && utf32Character <= 0x33FF);
}

bool UnicodeHelper::isHalfwidthAndFullwidthForms(char32_t utf32Character)
{
    // NOTE:
    // Accoding to this paper ( http://www.unicode.org/charts/PDF/UFF00.pdf ),
    // a range of "Halfwidth and Fullwidth Forms" is FF00-FFEF.
    return (0xFF00 <= utf32Character && utf32Character <= 0xFFEF);
}

bool UnicodeHelper::isHalfWidthKatakana(char32_t utf32Character)
{
    // NOTE:
    // Accoding to this paper ( http://www.unicode.org/charts/PDF/UFF00.pdf ),
    // a range of "Halfwidth katakana" is FF61-FF9F.
    return (0xFF61 <= utf32Character && utf32Character <= 0xFF9F);
}

bool UnicodeHelper::isCJKUnifiedIdeographs(char32_t utf32Character)
{
    // NOTE:
    // Accoding to this paper ( http://unicode.org/charts/PDF/U4E00.pdf ),
    // a range of "CJK Unified Ideographs" is 4E00-9FD5.
    return (0x4E00 <= utf32Character && utf32Character <= 0x9FD5);
}

bool UnicodeHelper::isCJKUnifiedIdeographsExtensionA(char32_t utf32Character)
{
    // NOTE:
    // Accoding to this paper ( http://www.unicode.org/charts/PDF/U3400.pdf ),
    // a range of "CJK Unified Ideographs Extension A" is 3400-4DB5.
    return (0x3400 <= utf32Character && utf32Character <= 0x4DBF);
}

bool UnicodeHelper::isMathematicalAlphanumericSymbols(char32_t utf32Character)
{
    // NOTE:
    // Accoding to this paper ( http://unicode.org/charts/PDF/U1D400.pdf ),
    // a range of "Mathematical Alphanumeric Symbols" is 1D400-1D7FF.
    return (0x1D400 <= utf32Character && utf32Character <= 0x1D7FF);
}

bool UnicodeHelper::isMiscellaneousSymbolsAndPictographs(char32_t utf32Character)
{
    // NOTE:
    // Accoding to this paper ( http://www.unicode.org/charts/PDF/U1F300.pdf ),
    // a range of "Miscellaneous Symbols and Pictographs" is 1F300-1F5FF.
    return (0x1F300 <= utf32Character && utf32Character <= 0x1F5FF);
}

bool UnicodeHelper::isEmoticons(char32_t utf32Character)
{
    // NOTE:
    // Accoding to this paper ( http://www.unicode.org/charts/PDF/U1F600.pdf ),
    // a range of "Emoticons" is 1F600-1F64F.
    return (0x1F600 <= utf32Character && utf32Character <= 0x1F64F);
}

} // namespace somera
