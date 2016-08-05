// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#pragma once

#include <string>

namespace somera {
namespace UnicodeHelper {

bool isGreekAndCoptic(char32_t utf32Character);

bool isLetterlikeSymbols(char32_t utf32Character);

bool isEnclosedAlphanumerics(char32_t utf32Character);

bool isBoxDrawing(char32_t utf32Character);

bool isBlockElements(char32_t utf32Character);

bool isMiscellaneousSymbols(char32_t utf32Character);

bool isCJKSymbolsAndPunctuation(char32_t utf32Character);

bool isHiragana(char32_t utf32Character);

bool isKatakana(char32_t utf32Character);

bool isBopomofo(char32_t utf32Character);

bool isHangulCompatibilityJamo(char32_t utf32Character);

bool isKanbun(char32_t utf32Character);

bool isBopomofoExtended(char32_t utf32Character);

bool isCJKStrokes(char32_t utf32Character);

bool isKatakanaPhoneticExtensions(char32_t utf32Character);

bool isEnclosedCJKLettersAndMonths(char32_t utf32Character);

bool isCJKCompatibility(char32_t utf32Character);

bool isHalfwidthAndFullwidthForms(char32_t utf32Character);

bool isHalfWidthKatakana(char32_t utf32Character);

bool isCJKUnifiedIdeographs(char32_t utf32Character);

bool isCJKUnifiedIdeographsExtensionA(char32_t utf32Character);

bool isMathematicalAlphanumericSymbols(char32_t utf32Character);

bool isMiscellaneousSymbolsAndPictographs(char32_t utf32Character);

bool isEmoticons(char32_t utf32Character);

} // namespace UnicodeHelper
} // namespace somera
