// Copyright (c) 2017 mogemimi. Distributed under the MIT license.

#include "StringHelper.h"
#include <iostream>
#include <fstream>
#include <array>
#include <unordered_map>
#include <experimental/optional>
#include <random>
#include <iomanip>
#include <locale>
#include <regex>
#include <sstream>
#include <cassert>

namespace {

struct UnicodeCharacterData {
    char32_t codeValue;
    std::string characterName;
    std::string generalCategory;
    std::string canonicalCombiningClasses;
    std::string bidirectionalCategory;
    std::string characterDecompositionMapping;
    std::string decimalDigitValue;
    std::string digitValue;
    std::string numericValue;
    std::string mirrored;
    std::string unicode_1_0_name;
    std::string commentField10646;
    std::experimental::optional<char32_t> uppercaseMapping;
    std::experimental::optional<char32_t> lowercaseMapping;
    std::experimental::optional<char32_t> titlecaseMapping;
};

std::experimental::optional<char32_t> ToCodeValueFromHexString(const std::string& s)
{
    if (s.empty()) {
        return std::experimental::nullopt;
    }
    return static_cast<char32_t>(std::stoi(s, nullptr, 16));
}

void PrintStat(const std::vector<UnicodeCharacterData>& datas)
{
    int upper = 0;
    int title = 0;
    int lower = 0;
    int maxCodePoint = 0;

    for (auto & data : datas) {
//        std::cout
//            << std::hex << data.codeValue
//            << " "
//            << data.characterName << std::endl;

        if (data.generalCategory == "Lt") {
            title++;
        }
        if (data.generalCategory == "Lu") {
            upper++;
        }
        if (data.generalCategory == "Ll") {
            lower++;
        }
        maxCodePoint = std::max(maxCodePoint, static_cast<int>(data.codeValue));
    }

    std::cout
        << "Lt: " << title << std::endl
        << "Lu: " << upper << std::endl
        << "Ll: " << lower << std::endl
        << "All: " << datas.size() << std::endl
        << "CodePoint: " << maxCodePoint << std::endl;
}

std::vector<UnicodeCharacterData> ReadUnicodeDataFile(const std::string& path)
{
    std::vector<UnicodeCharacterData> datas;

    std::ifstream ifs(path);

    if (!ifs) {
        std::cerr << "Cannot open the file: '" << path << "'";
        return {};
    }

    std::string line;
    while (std::getline(ifs, line)) {
        auto words = somera::StringHelper::split(line, ';');
        if (words.size() != 15) {
            continue;
        }
        UnicodeCharacterData data;
        data.codeValue = *ToCodeValueFromHexString(words[0]);
        data.characterName = words[1];
        data.generalCategory = words[2];
        data.canonicalCombiningClasses = words[3];
        data.bidirectionalCategory = words[4];
        data.characterDecompositionMapping = words[5];
        data.decimalDigitValue = words[6];
        data.digitValue = words[7];
        data.numericValue = words[8];
        data.mirrored = words[9];
        data.unicode_1_0_name = words[10];
        data.commentField10646 = words[11];
        data.uppercaseMapping = ToCodeValueFromHexString(words[12]);
        data.lowercaseMapping = ToCodeValueFromHexString(words[13]);
        data.titlecaseMapping = ToCodeValueFromHexString(words[14]);
        datas.push_back(std::move(data));
    }
    return datas;
}

struct UnicodeCapitalDesc {
    char32_t lowerCase;
    char32_t upperCase;
};

struct UnicodeCapitalDesc2 {
    char32_t character;
    char32_t lowerCase;
    char32_t upperCase;
};

template <class Function>
void measurePerformanceTime(Function f)
{
    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;
    using std::chrono::nanoseconds;
    using std::chrono::duration_cast;

	auto start = high_resolution_clock::now();

    f();

	auto end = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(end - start);

	std::cout
        << "Measured time (ns) : " << duration.count() << " ns" << std::endl;
    std::cout
        << "Measured time (sec): "
        << duration_cast<std::chrono::duration<double>>(end - start).count()
        << " seconds" << std::endl;
}

void GenerateUnicodeCapitalizationTable(const std::vector<UnicodeCharacterData>& unicodeDatas)
{
    std::vector<UnicodeCapitalDesc> capitalDescs;
    std::unordered_map<char32_t, std::size_t> indices;

    for (auto & data : unicodeDatas) {
        if (data.codeValue < 128) {
            continue;
        }

        if (data.generalCategory == "Lu") {
            if (*data.lowercaseMapping == 0) {
                continue;
            }

            UnicodeCapitalDesc desc;
            desc.upperCase = data.codeValue;
            desc.lowerCase = *data.lowercaseMapping;
            capitalDescs.push_back(desc);
        }
        else if (data.generalCategory == "Ll") {
            if (*data.uppercaseMapping == 0) {
                continue;
            }

            UnicodeCapitalDesc desc;
            desc.lowerCase = data.codeValue;
            desc.upperCase = *data.uppercaseMapping;
            capitalDescs.push_back(desc);
        }
    }

    std::stable_sort(std::begin(capitalDescs), std::end(capitalDescs), [](auto & a, auto & b) {
        if (a.upperCase == b.upperCase) {
            return a.lowerCase < b.lowerCase;
        }
        return a.upperCase < b.upperCase;
    });
    capitalDescs.erase(std::unique(std::begin(capitalDescs), std::end(capitalDescs), [](auto & a, auto & b) {
        return (a.lowerCase == b.lowerCase) && (a.upperCase == b.upperCase);
    }), std::end(capitalDescs));

    std::cout << "constexpr std::array<UnicodeCapitalDesc, " << capitalDescs.size() << "> capitalDescs = {{";
    int columnCount = 0;
    constexpr int maxColumnCount = 5;
    for (auto & desc : capitalDescs) {
        if (columnCount == 0) {
            // NOTE: indentation
            std::cout << "\n" << "    ";
        }
        else {
            std::cout << ", ";
        }
        std::cout
            << "{"
            << "0x" << std::setfill('0') << std::setw(4) << std::hex << desc.lowerCase
            << ", "
            << "0x" << std::setfill('0') << std::setw(4) << std::hex << desc.upperCase
            << "}";
        ++columnCount;
        if (columnCount >= maxColumnCount) {
            std::cout << ",";
            columnCount = 0;
        }
    }
    std::cout << "\n" << "}};" << std::endl;
}

constexpr UnicodeCapitalDesc2 letterCaseDescs[203] = {
    {0x0370, 0x0371, 0x0370}, {0x0371, 0x0371, 0x0370}, {0x0372, 0x0373, 0x0372},
    {0x0373, 0x0373, 0x0372}, {0x0376, 0x0377, 0x0376}, {0x0377, 0x0377, 0x0376},
    {0x037b, 0x037b, 0x03fd}, {0x037c, 0x037c, 0x03fe}, {0x037d, 0x037d, 0x03ff},
    {0x037f, 0x03f3, 0x037f}, {0x0386, 0x03ac, 0x0386}, {0x0388, 0x03ad, 0x0388},
    {0x0389, 0x03ae, 0x0389}, {0x038a, 0x03af, 0x038a}, {0x038c, 0x03cc, 0x038c},
    {0x038e, 0x03cd, 0x038e}, {0x038f, 0x03ce, 0x038f}, {0x0391, 0x03b1, 0x0391},
    {0x0392, 0x03b2, 0x0392}, {0x0393, 0x03b3, 0x0393}, {0x0394, 0x03b4, 0x0394},
    {0x0395, 0x03b5, 0x0395}, {0x0396, 0x03b6, 0x0396}, {0x0397, 0x03b7, 0x0397},
    {0x0398, 0x03b8, 0x0398}, {0x0399, 0x03b9, 0x0399}, {0x039a, 0x03ba, 0x039a},
    {0x039b, 0x03bb, 0x039b}, {0x039c, 0x03bc, 0x039c}, {0x039d, 0x03bd, 0x039d},
    {0x039e, 0x03be, 0x039e}, {0x039f, 0x03bf, 0x039f}, {0x03a0, 0x03c0, 0x03a0},
    {0x03a1, 0x03c1, 0x03a1}, {0x03a3, 0x03c3, 0x03a3}, {0x03a4, 0x03c4, 0x03a4},
    {0x03a5, 0x03c5, 0x03a5}, {0x03a6, 0x03c6, 0x03a6}, {0x03a7, 0x03c7, 0x03a7},
    {0x03a8, 0x03c8, 0x03a8}, {0x03a9, 0x03c9, 0x03a9}, {0x03aa, 0x03ca, 0x03aa},
    {0x03ab, 0x03cb, 0x03ab}, {0x03ac, 0x03ac, 0x0386}, {0x03ad, 0x03ad, 0x0388},
    {0x03ae, 0x03ae, 0x0389}, {0x03af, 0x03af, 0x038a}, {0x03b1, 0x03b1, 0x0391},
    {0x03b2, 0x03b2, 0x0392}, {0x03b3, 0x03b3, 0x0393}, {0x03b4, 0x03b4, 0x0394},
    {0x03b5, 0x03b5, 0x0395}, {0x03b6, 0x03b6, 0x0396}, {0x03b7, 0x03b7, 0x0397},
    {0x03b8, 0x03b8, 0x0398}, {0x03b9, 0x03b9, 0x0399}, {0x03ba, 0x03ba, 0x039a},
    {0x03bb, 0x03bb, 0x039b}, {0x03bc, 0x03bc, 0x039c}, {0x03bd, 0x03bd, 0x039d},
    {0x03be, 0x03be, 0x039e}, {0x03bf, 0x03bf, 0x039f}, {0x03c0, 0x03c0, 0x03a0},
    {0x03c1, 0x03c1, 0x03a1}, {0x03c2, 0x03c2, 0x03a3}, {0x03c3, 0x03c3, 0x03a3},
    {0x03c4, 0x03c4, 0x03a4}, {0x03c5, 0x03c5, 0x03a5}, {0x03c6, 0x03c6, 0x03a6},
    {0x03c7, 0x03c7, 0x03a7}, {0x03c8, 0x03c8, 0x03a8}, {0x03c9, 0x03c9, 0x03a9},
    {0x03ca, 0x03ca, 0x03aa}, {0x03cb, 0x03cb, 0x03ab}, {0x03cc, 0x03cc, 0x038c},
    {0x03cd, 0x03cd, 0x038e}, {0x03ce, 0x03ce, 0x038f}, {0x03cf, 0x03d7, 0x03cf},
    {0x03d0, 0x03d0, 0x0392}, {0x03d1, 0x03d1, 0x0398}, {0x03d5, 0x03d5, 0x03a6},
    {0x03d6, 0x03d6, 0x03a0}, {0x03d7, 0x03d7, 0x03cf}, {0x03d8, 0x03d9, 0x03d8},
    {0x03d9, 0x03d9, 0x03d8}, {0x03da, 0x03db, 0x03da}, {0x03db, 0x03db, 0x03da},
    {0x03dc, 0x03dd, 0x03dc}, {0x03dd, 0x03dd, 0x03dc}, {0x03de, 0x03df, 0x03de},
    {0x03df, 0x03df, 0x03de}, {0x03e0, 0x03e1, 0x03e0}, {0x03e1, 0x03e1, 0x03e0},
    {0x03e2, 0x03e3, 0x03e2}, {0x03e3, 0x03e3, 0x03e2}, {0x03e4, 0x03e5, 0x03e4},
    {0x03e5, 0x03e5, 0x03e4}, {0x03e6, 0x03e7, 0x03e6}, {0x03e7, 0x03e7, 0x03e6},
    {0x03e8, 0x03e9, 0x03e8}, {0x03e9, 0x03e9, 0x03e8}, {0x03ea, 0x03eb, 0x03ea},
    {0x03eb, 0x03eb, 0x03ea}, {0x03ec, 0x03ed, 0x03ec}, {0x03ed, 0x03ed, 0x03ec},
    {0x03ee, 0x03ef, 0x03ee}, {0x03ef, 0x03ef, 0x03ee}, {0x03f0, 0x03f0, 0x039a},
    {0x03f1, 0x03f1, 0x03a1}, {0x03f2, 0x03f2, 0x03f9}, {0x03f3, 0x03f3, 0x037f},
    {0x03f4, 0x03b8, 0x03f4}, {0x03f5, 0x03f5, 0x0395}, {0x03f7, 0x03f8, 0x03f7},
    {0x03f8, 0x03f8, 0x03f7}, {0x03f9, 0x03f2, 0x03f9}, {0x03fa, 0x03fb, 0x03fa},
    {0x03fb, 0x03fb, 0x03fa}, {0x03fd, 0x037b, 0x03fd}, {0x03fe, 0x037c, 0x03fe},
    {0x03ff, 0x037d, 0x03ff}, {0x0401, 0x0451, 0x0401}, {0x0405, 0x0455, 0x0405},
    {0x0406, 0x0456, 0x0406}, {0x0410, 0x0430, 0x0410}, {0x0411, 0x0431, 0x0411},
    {0x0412, 0x0432, 0x0412}, {0x0413, 0x0433, 0x0413}, {0x0414, 0x0434, 0x0414},
    {0x0415, 0x0435, 0x0415}, {0x0416, 0x0436, 0x0416}, {0x0417, 0x0437, 0x0417},
    {0x0418, 0x0438, 0x0418}, {0x0419, 0x0439, 0x0419}, {0x041a, 0x043a, 0x041a},
    {0x041b, 0x043b, 0x041b}, {0x041c, 0x043c, 0x041c}, {0x041d, 0x043d, 0x041d},
    {0x041e, 0x043e, 0x041e}, {0x041f, 0x043f, 0x041f}, {0x0420, 0x0440, 0x0420},
    {0x0421, 0x0441, 0x0421}, {0x0422, 0x0442, 0x0422}, {0x0423, 0x0443, 0x0423},
    {0x0424, 0x0444, 0x0424}, {0x0425, 0x0445, 0x0425}, {0x0426, 0x0446, 0x0426},
    {0x0427, 0x0447, 0x0427}, {0x0428, 0x0448, 0x0428}, {0x0429, 0x0449, 0x0429},
    {0x042a, 0x044a, 0x042a}, {0x042b, 0x044b, 0x042b}, {0x042c, 0x044c, 0x042c},
    {0x042d, 0x044d, 0x042d}, {0x042e, 0x044e, 0x042e}, {0x042f, 0x044f, 0x042f},
    {0x0430, 0x0430, 0x0410}, {0x0431, 0x0431, 0x0411}, {0x0432, 0x0432, 0x0412},
    {0x0433, 0x0433, 0x0413}, {0x0434, 0x0434, 0x0414}, {0x0435, 0x0435, 0x0415},
    {0x0436, 0x0436, 0x0416}, {0x0437, 0x0437, 0x0417}, {0x0438, 0x0438, 0x0418},
    {0x0439, 0x0439, 0x0419}, {0x043a, 0x043a, 0x041a}, {0x043b, 0x043b, 0x041b},
    {0x043c, 0x043c, 0x041c}, {0x043d, 0x043d, 0x041d}, {0x043e, 0x043e, 0x041e},
    {0x043f, 0x043f, 0x041f}, {0x0440, 0x0440, 0x0420}, {0x0441, 0x0441, 0x0421},
    {0x0442, 0x0442, 0x0422}, {0x0443, 0x0443, 0x0423}, {0x0444, 0x0444, 0x0424},
    {0x0445, 0x0445, 0x0425}, {0x0446, 0x0446, 0x0426}, {0x0447, 0x0447, 0x0427},
    {0x0448, 0x0448, 0x0428}, {0x0449, 0x0449, 0x0429}, {0x044a, 0x044a, 0x042a},
    {0x044b, 0x044b, 0x042b}, {0x044c, 0x044c, 0x042c}, {0x044d, 0x044d, 0x042d},
    {0x044e, 0x044e, 0x042e}, {0x044f, 0x044f, 0x042f}, {0x0451, 0x0451, 0x0401},
    {0x0460, 0x0461, 0x0460}, {0x0462, 0x0463, 0x0462}, {0x0464, 0x0465, 0x0464},
    {0x0466, 0x0467, 0x0466}, {0x0468, 0x0469, 0x0468}, {0x046a, 0x046b, 0x046a},
    {0x046c, 0x046d, 0x046c}, {0x046e, 0x046f, 0x046e}, {0x0470, 0x0471, 0x0470},
    {0x0472, 0x0473, 0x0472}, {0x0474, 0x0475, 0x0474}, {0x1e9e, 0x00df, 0x1e9e},
    {0xa64a, 0xa64b, 0xa64a}, {0xa656, 0xa657, 0xa656}
};

template<class T, size_t N>
constexpr size_t getSizeOfArray(T (&)[N]) { return N; }

constexpr char32_t toLowerCharacters[592] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 0, 0, 0, 0, 0,
    0, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 181, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
    240, 241, 242, 243, 244, 245, 246, 0, 248, 249, 250, 251, 252, 253, 254, 223,
    224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
    240, 241, 242, 243, 244, 245, 246, 0, 248, 249, 250, 251, 252, 253, 254, 255,
    257, 257, 259, 259, 261, 261, 263, 263, 265, 265, 267, 267, 269, 269, 271, 271,
    273, 273, 275, 275, 277, 277, 279, 279, 281, 281, 283, 283, 285, 285, 287, 287,
    289, 289, 291, 291, 293, 293, 295, 295, 297, 297, 299, 299, 301, 301, 303, 303,
    105, 305, 307, 307, 309, 309, 311, 311, 312, 314, 314, 316, 316, 318, 318, 320,
    320, 322, 322, 324, 324, 326, 326, 328, 328, 329, 331, 331, 333, 333, 335, 335,
    337, 337, 339, 339, 341, 341, 343, 343, 345, 345, 347, 347, 349, 349, 351, 351,
    353, 353, 355, 355, 357, 357, 359, 359, 361, 361, 363, 363, 365, 365, 367, 367,
    369, 369, 371, 371, 373, 373, 375, 375, 255, 378, 378, 380, 380, 382, 382, 383,
    384, 595, 387, 387, 389, 389, 596, 392, 392, 598, 599, 396, 396, 397, 477, 601,
    603, 402, 402, 608, 611, 405, 617, 616, 409, 409, 410, 411, 623, 626, 414, 629,
    417, 417, 419, 419, 421, 421, 640, 424, 424, 643, 426, 427, 429, 429, 648, 432,
    432, 650, 651, 436, 436, 438, 438, 658, 441, 441, 442, 0, 445, 445, 446, 447,
    0, 0, 0, 0, 454, 454, 454, 457, 457, 457, 460, 460, 460, 462, 462, 464,
    464, 466, 466, 468, 468, 470, 470, 472, 472, 474, 474, 476, 476, 477, 479, 479,
    481, 481, 483, 483, 485, 485, 487, 487, 489, 489, 491, 491, 493, 493, 495, 495,
    496, 499, 499, 499, 501, 501, 405, 447, 505, 505, 507, 507, 509, 509, 511, 511,
    513, 513, 515, 515, 517, 517, 519, 519, 521, 521, 523, 523, 525, 525, 527, 527,
    529, 529, 531, 531, 533, 533, 535, 535, 537, 537, 539, 539, 541, 541, 543, 543,
    414, 545, 547, 547, 549, 549, 551, 551, 553, 553, 555, 555, 557, 557, 559, 559,
    561, 561, 563, 563, 564, 565, 566, 567, 568, 569, 11365, 572, 572, 410, 11366, 575,
    576, 578, 578, 384, 649, 652, 583, 583, 585, 585, 587, 587, 589, 589, 591, 591,
};

constexpr char32_t toUpperCharacters[592] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 0, 0, 0, 0, 0,
    0, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 924, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
    208, 209, 210, 211, 212, 213, 214, 0, 216, 217, 218, 219, 220, 221, 222, 0,
    192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
    208, 209, 210, 211, 212, 213, 214, 0, 216, 217, 218, 219, 220, 221, 222, 376,
    256, 256, 258, 258, 260, 260, 262, 262, 264, 264, 266, 266, 268, 268, 270, 270,
    272, 272, 274, 274, 276, 276, 278, 278, 280, 280, 282, 282, 284, 284, 286, 286,
    288, 288, 290, 290, 292, 292, 294, 294, 296, 296, 298, 298, 300, 300, 302, 302,
    304, 73, 306, 306, 308, 308, 310, 310, 0, 313, 313, 315, 315, 317, 317, 319,
    319, 321, 321, 323, 323, 325, 325, 327, 327, 0, 330, 330, 332, 332, 334, 334,
    336, 336, 338, 338, 340, 340, 342, 342, 344, 344, 346, 346, 348, 348, 350, 350,
    352, 352, 354, 354, 356, 356, 358, 358, 360, 360, 362, 362, 364, 364, 366, 366,
    368, 368, 370, 370, 372, 372, 374, 374, 376, 377, 377, 379, 379, 381, 381, 83,
    579, 385, 386, 386, 388, 388, 390, 391, 391, 393, 394, 395, 395, 0, 398, 399,
    400, 401, 401, 403, 404, 502, 406, 407, 408, 408, 573, 0, 412, 413, 544, 415,
    416, 416, 418, 418, 420, 420, 422, 423, 423, 425, 0, 0, 428, 428, 430, 431,
    431, 433, 434, 435, 435, 437, 437, 439, 440, 440, 0, 0, 444, 444, 0, 503,
    0, 0, 0, 0, 452, 452, 452, 455, 455, 455, 458, 458, 458, 461, 461, 463,
    463, 465, 465, 467, 467, 469, 469, 471, 471, 473, 473, 475, 475, 398, 478, 478,
    480, 480, 482, 482, 484, 484, 486, 486, 488, 488, 490, 490, 492, 492, 494, 494,
    0, 497, 497, 497, 500, 500, 502, 503, 504, 504, 506, 506, 508, 508, 510, 510,
    512, 512, 514, 514, 516, 516, 518, 518, 520, 520, 522, 522, 524, 524, 526, 526,
    528, 528, 530, 530, 532, 532, 534, 534, 536, 536, 538, 538, 540, 540, 542, 542,
    544, 0, 546, 546, 548, 548, 550, 550, 552, 552, 554, 554, 556, 556, 558, 558,
    560, 560, 562, 562, 0, 0, 0, 0, 0, 0, 570, 571, 571, 573, 574, 11390,
    11391, 577, 577, 579, 580, 581, 582, 582, 584, 584, 586, 586, 588, 588, 590, 590,
};

struct UnicodeHelper {
public:
    bool IsLower(char32_t c)
    {
        if (c < getSizeOfArray(toLowerCharacters)) {
            return toLowerCharacters[c] == c;
        }

        UnicodeCapitalDesc2 desc;
        desc.character = c;
        auto iter = std::lower_bound(std::begin(letterCaseDescs), std::end(letterCaseDescs), desc, [](auto & a, auto & b) {
            return a.character < b.character;
        });
        if (iter == std::end(letterCaseDescs)) {
            return false;
        }
        return iter->lowerCase == c;
    }

    bool IsUpper(char32_t c)
    {
        if (c < getSizeOfArray(toUpperCharacters)) {
            return toUpperCharacters[c] == c;
        }

        UnicodeCapitalDesc2 desc;
        desc.character = c;
        auto iter = std::lower_bound(std::begin(letterCaseDescs), std::end(letterCaseDescs), desc, [](auto & a, auto & b) {
            return a.character < b.character;
        });
        if (iter == std::end(letterCaseDescs)) {
            return false;
        }
        return iter->upperCase == c;
    }

    char32_t ToLower(char32_t c)
    {
        if (c < getSizeOfArray(toLowerCharacters)) {
            return toLowerCharacters[c];
        }

        UnicodeCapitalDesc2 desc;
        desc.character = c;
        auto iter = std::lower_bound(std::begin(letterCaseDescs), std::end(letterCaseDescs), desc, [](auto & a, auto & b) {
            return a.character < b.character;
        });
        if (iter == std::end(letterCaseDescs)) {
            return c;
        }
        return iter->lowerCase;
    }

    char32_t ToUpper(char32_t c)
    {
        if (c < getSizeOfArray(toUpperCharacters)) {
            return toUpperCharacters[c];
        }

        UnicodeCapitalDesc2 desc;
        desc.character = c;
        auto iter = std::lower_bound(std::begin(letterCaseDescs), std::end(letterCaseDescs), desc, [](auto & a, auto & b) {
            return a.character < b.character;
        });
        if (iter == std::end(letterCaseDescs)) {
            return c;
        }
        return iter->upperCase;
    }
};

void PerformanceTest(const std::vector<UnicodeCharacterData>& unicodeDatas)
{
    std::vector<UnicodeCapitalDesc> capitalDescs;
    std::unordered_map<char32_t, std::size_t> indices;

    for (auto & data : unicodeDatas) {
        if (data.generalCategory == "Lu") {
            UnicodeCapitalDesc desc;
            desc.upperCase = data.codeValue;
            desc.lowerCase = *data.lowercaseMapping;
            capitalDescs.push_back(desc);
        }
        else if (data.generalCategory == "Ll") {
            UnicodeCapitalDesc desc;
            desc.lowerCase = data.codeValue;
            desc.upperCase = *data.uppercaseMapping;
            capitalDescs.push_back(desc);
        }
    }

    std::stable_sort(std::begin(capitalDescs), std::end(capitalDescs), [](auto & a, auto & b) {
        if (a.upperCase == b.upperCase) {
            return a.lowerCase < b.lowerCase;
        }
        return a.upperCase < b.upperCase;
    });
    capitalDescs.erase(std::unique(std::begin(capitalDescs), std::end(capitalDescs), [](auto & a, auto & b) {
        return (a.lowerCase == b.lowerCase) && (a.upperCase == b.upperCase);
    }), std::end(capitalDescs));

    std::cout << "size: " << capitalDescs.size() << std::endl;

    for (std::size_t i = 0; i < capitalDescs.size(); ++i) {
        indices.emplace(capitalDescs[i].lowerCase, i);
        indices.emplace(capitalDescs[i].upperCase, i);
    }

    auto isLower = [&](char32_t c) {
        auto iter = indices.find(c);
        if (iter == std::end(indices)) {
            return false;
        }
        return capitalDescs[iter->second].lowerCase == c;
    };

    auto isUpper = [&](char32_t c) {
        auto iter = indices.find(c);
        if (iter == std::end(indices)) {
            return false;
        }
        return capitalDescs[iter->second].upperCase == c;
    };

    std::vector<UnicodeCapitalDesc2> capitalDescs2;
    for (auto & data : unicodeDatas) {
        if (data.generalCategory == "Lu") {
            UnicodeCapitalDesc2 desc;
            desc.character = data.codeValue;
            desc.upperCase = data.codeValue;
            desc.lowerCase = *data.lowercaseMapping;
            capitalDescs2.push_back(desc);
        }
        else if (data.generalCategory == "Ll") {
            UnicodeCapitalDesc2 desc;
            desc.character = data.codeValue;
            desc.lowerCase = data.codeValue;
            desc.upperCase = *data.uppercaseMapping;
            capitalDescs2.push_back(desc);
        }
    }

    auto isLower2 = [&](char32_t c) {
        UnicodeCapitalDesc2 desc;
        desc.character = c;
        auto iter = std::lower_bound(std::begin(capitalDescs2), std::end(capitalDescs2), desc, [](auto & a, auto & b) {
            return a.character < b.character;
        });
        if (iter == std::end(capitalDescs2)) {
            return false;
        }
        return iter->lowerCase == c;
    };

    auto isUpper2 = [&](char32_t c) {
        UnicodeCapitalDesc2 desc;
        desc.character = c;
        auto iter = std::lower_bound(std::begin(capitalDescs2), std::end(capitalDescs2), desc, [](auto & a, auto & b) {
            return a.character < b.character;
        });
        if (iter == std::end(capitalDescs2)) {
            return false;
        }
        return iter->upperCase == c;
    };

    std::u32string testData;
    for (int i = 0; i < 50; ++i) {
        for (auto & data : unicodeDatas) {
            testData.push_back(data.codeValue);
        }
    }
    for (int i = 0; i < 1000; ++i) {
        testData.push_back((i % 26) + U'A');
        testData.push_back((i % 26) + U'a');
        testData.push_back((i % 10) + U'0');
    }

    std::mt19937 mt(10000);
    std::shuffle(std::begin(testData), std::end(testData), mt);

    UnicodeHelper helper;

    int dummy = 0;
    measurePerformanceTime([&] {
        for (auto c : testData) {
            dummy += isLower(c) ? 1 : 2;
            dummy += isUpper(c) ? 1 : 2;
        }
    });

    measurePerformanceTime([&] {
        for (auto c : testData) {
            dummy += isLower2(c) ? 1 : 2;
            dummy += isUpper2(c) ? 1 : 2;
        }
    });

    measurePerformanceTime([&] {
        for (auto c : testData) {
            dummy += helper.IsLower(c) ? 1 : 2;
            dummy += helper.IsUpper(c) ? 1 : 2;
        }
    });

    measurePerformanceTime([&] {
        for (auto c : testData) {
            dummy += ::islower(c) ? 1 : 2;
            dummy += ::isupper(c) ? 1 : 2;
        }
    });

    std::cout << "dummy=" << dummy << std::endl;
}

void PrintLowerCharacters(char32_t from, char32_t to, const std::vector<UnicodeCharacterData>& unicodeDatas)
{
    assert(from <= to);
    const char32_t maxCount = (to + 1) - from;
    std::cout << "constexpr char32_t toLowerCharacters[" << maxCount << "] = {";
    for (char32_t c = from; c <= to; ++c) {
        constexpr int columnCount = 16;
        if (c % columnCount == 0) {
            std::cout << "\n    ";
        }
        else {
            std::cout << ", ";
        }
        
        auto iter = std::find_if(std::begin(unicodeDatas), std::end(unicodeDatas), [&](auto & a) {
            return a.codeValue == c;
        });

        if (iter == std::end(unicodeDatas)) {
            std::cout << "0";
        }
        else if (iter->generalCategory == "Ll") {
            std::cout << c;
        }
        else if (iter->lowercaseMapping) {
            std::cout << *iter->lowercaseMapping;
        }
        else {
            std::cout << "0";
        }

        if ((c + 1) % columnCount == 0) {
            std::cout << ",";
        }
    }
    std::cout << "\n};" << std::endl;
}

void PrintUpperCharacters(char32_t from, char32_t to, const std::vector<UnicodeCharacterData>& unicodeDatas)
{
    assert(from <= to);
    const char32_t maxCount = (to + 1) - from;
    std::cout << "constexpr char32_t toUpperCharacters[" << maxCount << "] = {";
    for (char32_t c = from; c <= to; ++c) {
        constexpr int columnCount = 16;
        if (c % columnCount == 0) {
            std::cout << "\n    ";
        }
        else {
            std::cout << ", ";
        }
        
        auto iter = std::find_if(std::begin(unicodeDatas), std::end(unicodeDatas), [&](auto & a) {
            return a.codeValue == c;
        });

        if (iter == std::end(unicodeDatas)) {
            std::cout << "0";
        }
        else if (iter->generalCategory == "Lu") {
            std::cout << c;
        }
        else if (iter->uppercaseMapping) {
            std::cout << *iter->uppercaseMapping;
        }
        else {
            std::cout << "0";
        }

        if ((c + 1) % columnCount == 0) {
            std::cout << ",";
        }
    }
    std::cout << "\n};" << std::endl;
}

void GenerateUnicodeCapitalizationTable2(
    const std::vector<UnicodeCharacterData>& unicodeDatas,
    const std::vector<char32_t>& commonlyUsedCharacters)
{
    std::vector<UnicodeCapitalDesc2> capitalDescs;
    for (auto & data : unicodeDatas) {
        if (data.codeValue <= 0x024F) {
            continue;
        }
        
        if (data.generalCategory == "Lu") {
            if (*data.lowercaseMapping == 0) {
                continue;
            }
            UnicodeCapitalDesc2 desc;
            desc.character = data.codeValue;
            desc.upperCase = data.codeValue;
            desc.lowerCase = *data.lowercaseMapping;
            capitalDescs.push_back(desc);
        }
        else if (data.generalCategory == "Ll") {
            if (*data.uppercaseMapping == 0) {
                continue;
            }
            UnicodeCapitalDesc2 desc;
            desc.character = data.codeValue;
            desc.lowerCase = data.codeValue;
            desc.upperCase = *data.uppercaseMapping;
            capitalDescs.push_back(desc);
        }
    }

    capitalDescs.erase(std::remove_if(std::begin(capitalDescs), std::end(capitalDescs), [&](auto & a) {
        if ((0x0080 <= a.character) && (a.character <= 0x00FF)) {
            // Latin-1 Supplement
            return false;
        }
        if ((0x0100 <= a.character) && (a.character <= 0x017F)) {
            // Latin Extended-A
            return false;
        }
        if ((0x0180 <= a.character) && (a.character <= 0x024F)) {
            // Latin Extended-B
            return false;
        }
        if ((0x0370 <= a.character) && (a.character <= 0x03FF)) {
            // Greek and Coptic
            return false;
        }
        auto iter = std::find(std::begin(commonlyUsedCharacters), std::end(commonlyUsedCharacters), a.character);
        if (iter != std::end(commonlyUsedCharacters)) {
            return false;
        }
        return iter == std::end(commonlyUsedCharacters);
    }), std::end(capitalDescs));

    std::stable_sort(std::begin(capitalDescs), std::end(capitalDescs), [](auto & a, auto & b) {
        return a.character < b.character;
    });
    capitalDescs.erase(std::unique(std::begin(capitalDescs), std::end(capitalDescs), [](auto & a, auto & b) {
        return a.character == b.character;
    }), std::end(capitalDescs));

    std::cout << "constexpr UnicodeCapitalDesc2 capitalDescs[" << capitalDescs.size() << "] = {";
    int columnCount = 0;
    constexpr int maxColumnCount = 3;
    for (auto & desc : capitalDescs) {
        if (columnCount == 0) {
            // NOTE: indentation
            std::cout << "\n" << "    ";
        }
        else {
            std::cout << ", ";
        }
        std::cout
            << "{"
            << "0x" << std::setfill('0') << std::setw(4) << std::hex << desc.character
            << ", "
            << "0x" << std::setfill('0') << std::setw(4) << std::hex << desc.lowerCase
            << ", "
            << "0x" << std::setfill('0') << std::setw(4) << std::hex << desc.upperCase
            << "}";
        ++columnCount;
        if (columnCount >= maxColumnCount) {
            std::cout << ",";
            columnCount = 0;
        }
    }
    std::cout << "\n" << "};" << std::endl;
}

std::vector<char32_t> ExtractUnicodeCodePointStringsFromTextFile(const std::string& filePath)
{
    std::ifstream ifs(filePath);
    std::string source((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    for (auto & c : source) {
        if (::isspace(c)) {
            c = ' ';
        }
    }
    auto splits = somera::StringHelper::split(source, " ");
    
    std::vector<char32_t> codePoints;
    
    for (auto & s : splits) {
        if (std::regex_match(s, std::regex(R"(U\+[\dA-Fa-f]{4})"))) {
            auto codePoint = *ToCodeValueFromHexString(s.substr(2, 4));
            codePoints.push_back(codePoint);
        }
    }
    
    return codePoints;
}

void SortMarkdownSections(const std::string& filePath)
{
    struct MarkdownSection {
        std::string title;
        std::vector<std::string> codes;
    };

    std::ifstream ifs(filePath);

    std::vector<MarkdownSection> marks;
    std::string line;
    while (std::getline(ifs, line)) {
        if (line.empty()) {
            continue;
        }

        if (somera::StringHelper::startWith(line, "##")) {
            MarkdownSection mark;
            mark.title = line;
            while (std::getline(ifs, line)) {
                if (line == "```") {
                    break;
                }
            }
            while (std::getline(ifs, line)) {
                if (std::regex_match(line, std::regex(R"(U\+[\dA-Fa-f]{4})"))) {
                    mark.codes.push_back(line);
                }
                else if (line == "```") {
                    break;
                }
            }
            marks.push_back(mark);
        }
    }

    std::stable_sort(std::begin(marks), std::end(marks), [](auto & a, auto & b) {
        return a.title < b.title;
    });

    for (auto & mark : marks) {
        std::stable_sort(std::begin(mark.codes), std::end(mark.codes), [](auto & a, auto & b) {
            return a < b;
        });

        mark.codes.erase(std::unique(std::begin(mark.codes), std::end(mark.codes), [](auto & a, auto & b) {
            return a == b;
        }), std::end(mark.codes));
    }

    for (auto & mark : marks) {
        std::cout << mark.title << std::endl;
        std::cout << std::endl << "```" << std::endl;
        
        for (auto & c : mark.codes) {
            std::cout << c << std::endl;
        }
        std::cout << "```" << std::endl << std::endl;
    }
}

std::string ToUnicodeCodePointString(char32_t codePoint)
{
    std::stringstream ss;
    ss << "U+" << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << codePoint;
    return ss.str();
}

void PrintExtractedUnicodeCodePointStringsFromTextFile(const std::string& filePath)
{
    auto codePoints = ExtractUnicodeCodePointStringsFromTextFile(filePath);
    for (auto c : codePoints) {
        if (c < 128) {
            continue;
        }
        std::cout << ToUnicodeCodePointString(c) << std::endl;
    }
}

} // unnamed namespace

int main(int argc, char *argv[])
{
    // NOTE: http://www.unicode.org/Public/UNIDATA/UnicodeData.txt
    auto unicodeDatas = ReadUnicodeDataFile(
        "UnicodeData.txt");

    auto codePoints = ExtractUnicodeCodePointStringsFromTextFile(
        "CommonlyUsedUnicodeCharacters.md");

//    PerformanceTest(unicodeDatas);
//    GenerateUnicodeCapitalizationTable(unicodeDatas);
//    GenerateUnicodeCapitalizationTable2(unicodeDatas, codePoints);

//    PrintLowerCharacters(0x0000, 0x024F, unicodeDatas);
//    PrintUpperCharacters(0x0000, 0x024F, unicodeDatas);

//    SortMarkdownSections("CommonlyUsedUnicodeCharacters.md");

    return 0;
}
