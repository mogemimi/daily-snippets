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

constexpr UnicodeCapitalDesc2 letterCaseDescs[303] = {
    {0x00b5, 0x00b5, 0x039c}, {0x00c0, 0x00e0, 0x00c0}, {0x00c1, 0x00e1, 0x00c1},
    {0x00c2, 0x00e2, 0x00c2}, {0x00c3, 0x00e3, 0x00c3}, {0x00c4, 0x00e4, 0x00c4},
    {0x00c5, 0x00e5, 0x00c5}, {0x00c6, 0x00e6, 0x00c6}, {0x00c7, 0x00e7, 0x00c7},
    {0x00c8, 0x00e8, 0x00c8}, {0x00c9, 0x00e9, 0x00c9}, {0x00ca, 0x00ea, 0x00ca},
    {0x00cb, 0x00eb, 0x00cb}, {0x00cc, 0x00ec, 0x00cc}, {0x00cd, 0x00ed, 0x00cd},
    {0x00ce, 0x00ee, 0x00ce}, {0x00cf, 0x00ef, 0x00cf}, {0x00d0, 0x00f0, 0x00d0},
    {0x00d1, 0x00f1, 0x00d1}, {0x00d2, 0x00f2, 0x00d2}, {0x00d3, 0x00f3, 0x00d3},
    {0x00d4, 0x00f4, 0x00d4}, {0x00d5, 0x00f5, 0x00d5}, {0x00d6, 0x00f6, 0x00d6},
    {0x00d8, 0x00f8, 0x00d8}, {0x00d9, 0x00f9, 0x00d9}, {0x00da, 0x00fa, 0x00da},
    {0x00db, 0x00fb, 0x00db}, {0x00dc, 0x00fc, 0x00dc}, {0x00dd, 0x00fd, 0x00dd},
    {0x00de, 0x00fe, 0x00de}, {0x00e0, 0x00e0, 0x00c0}, {0x00e1, 0x00e1, 0x00c1},
    {0x00e2, 0x00e2, 0x00c2}, {0x00e3, 0x00e3, 0x00c3}, {0x00e4, 0x00e4, 0x00c4},
    {0x00e5, 0x00e5, 0x00c5}, {0x00e6, 0x00e6, 0x00c6}, {0x00e7, 0x00e7, 0x00c7},
    {0x00e8, 0x00e8, 0x00c8}, {0x00e9, 0x00e9, 0x00c9}, {0x00ea, 0x00ea, 0x00ca},
    {0x00eb, 0x00eb, 0x00cb}, {0x00ec, 0x00ec, 0x00cc}, {0x00ed, 0x00ed, 0x00cd},
    {0x00ee, 0x00ee, 0x00ce}, {0x00ef, 0x00ef, 0x00cf}, {0x00f0, 0x00f0, 0x00d0},
    {0x00f1, 0x00f1, 0x00d1}, {0x00f2, 0x00f2, 0x00d2}, {0x00f3, 0x00f3, 0x00d3},
    {0x00f4, 0x00f4, 0x00d4}, {0x00f5, 0x00f5, 0x00d5}, {0x00f6, 0x00f6, 0x00d6},
    {0x00f8, 0x00f8, 0x00d8}, {0x00f9, 0x00f9, 0x00d9}, {0x00fa, 0x00fa, 0x00da},
    {0x00fb, 0x00fb, 0x00db}, {0x00fc, 0x00fc, 0x00dc}, {0x00fd, 0x00fd, 0x00dd},
    {0x00fe, 0x00fe, 0x00de}, {0x00ff, 0x00ff, 0x0178}, {0x0100, 0x0101, 0x0100},
    {0x0101, 0x0101, 0x0100}, {0x0102, 0x0103, 0x0102}, {0x0103, 0x0103, 0x0102},
    {0x0104, 0x0105, 0x0104}, {0x0105, 0x0105, 0x0104}, {0x0106, 0x0107, 0x0106},
    {0x0107, 0x0107, 0x0106}, {0x010a, 0x010b, 0x010a}, {0x010b, 0x010b, 0x010a},
    {0x010c, 0x010d, 0x010c}, {0x010d, 0x010d, 0x010c}, {0x010e, 0x010f, 0x010e},
    {0x010f, 0x010f, 0x010e}, {0x0110, 0x0111, 0x0110}, {0x0111, 0x0111, 0x0110},
    {0x0112, 0x0113, 0x0112}, {0x0113, 0x0113, 0x0112}, {0x0116, 0x0117, 0x0116},
    {0x0117, 0x0117, 0x0116}, {0x0118, 0x0119, 0x0118}, {0x0119, 0x0119, 0x0118},
    {0x011a, 0x011b, 0x011a}, {0x011b, 0x011b, 0x011a}, {0x011e, 0x011f, 0x011e},
    {0x011f, 0x011f, 0x011e}, {0x0122, 0x0123, 0x0122}, {0x0123, 0x0123, 0x0122},
    {0x012a, 0x012b, 0x012a}, {0x012b, 0x012b, 0x012a}, {0x012e, 0x012f, 0x012e},
    {0x012f, 0x012f, 0x012e}, {0x0130, 0x0069, 0x0130}, {0x0131, 0x0131, 0x0049},
    {0x0136, 0x0137, 0x0136}, {0x0137, 0x0137, 0x0136}, {0x0139, 0x013a, 0x0139},
    {0x013a, 0x013a, 0x0139}, {0x013b, 0x013c, 0x013b}, {0x013c, 0x013c, 0x013b},
    {0x013d, 0x013e, 0x013d}, {0x013e, 0x013e, 0x013d}, {0x013f, 0x0140, 0x013f},
    {0x0140, 0x0140, 0x013f}, {0x0141, 0x0142, 0x0141}, {0x0142, 0x0142, 0x0141},
    {0x0143, 0x0144, 0x0143}, {0x0144, 0x0144, 0x0143}, {0x0145, 0x0146, 0x0145},
    {0x0146, 0x0146, 0x0145}, {0x0147, 0x0148, 0x0147}, {0x0148, 0x0148, 0x0147},
    {0x014c, 0x014d, 0x014c}, {0x014d, 0x014d, 0x014c}, {0x0150, 0x0151, 0x0150},
    {0x0151, 0x0151, 0x0150}, {0x0152, 0x0153, 0x0152}, {0x0153, 0x0153, 0x0152},
    {0x0154, 0x0155, 0x0154}, {0x0155, 0x0155, 0x0154}, {0x0156, 0x0157, 0x0156},
    {0x0157, 0x0157, 0x0156}, {0x0158, 0x0159, 0x0158}, {0x0159, 0x0159, 0x0158},
    {0x015a, 0x015b, 0x015a}, {0x015b, 0x015b, 0x015a}, {0x015e, 0x015f, 0x015e},
    {0x015f, 0x015f, 0x015e}, {0x0160, 0x0161, 0x0160}, {0x0161, 0x0161, 0x0160},
    {0x0162, 0x0163, 0x0162}, {0x0163, 0x0163, 0x0162}, {0x0164, 0x0165, 0x0164},
    {0x0165, 0x0165, 0x0164}, {0x016a, 0x016b, 0x016a}, {0x016b, 0x016b, 0x016a},
    {0x016e, 0x016f, 0x016e}, {0x016f, 0x016f, 0x016e}, {0x0170, 0x0171, 0x0170},
    {0x0171, 0x0171, 0x0170}, {0x0172, 0x0173, 0x0172}, {0x0173, 0x0173, 0x0172},
    {0x0178, 0x00ff, 0x0178}, {0x0179, 0x017a, 0x0179}, {0x017a, 0x017a, 0x0179},
    {0x017b, 0x017c, 0x017b}, {0x017c, 0x017c, 0x017b}, {0x017d, 0x017e, 0x017d},
    {0x017e, 0x017e, 0x017d}, {0x0386, 0x03ac, 0x0386}, {0x0388, 0x03ad, 0x0388},
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
    {0x03cd, 0x03cd, 0x038e}, {0x03ce, 0x03ce, 0x038f}, {0x03d0, 0x03d0, 0x0392},
    {0x03d1, 0x03d1, 0x0398}, {0x03d5, 0x03d5, 0x03a6}, {0x03d6, 0x03d6, 0x03a0},
    {0x03f0, 0x03f0, 0x039a}, {0x03f1, 0x03f1, 0x03a1}, {0x03f4, 0x03b8, 0x03f4},
    {0x03f5, 0x03f5, 0x0395}, {0x0401, 0x0451, 0x0401}, {0x0410, 0x0430, 0x0410},
    {0x0411, 0x0431, 0x0411}, {0x0412, 0x0432, 0x0412}, {0x0413, 0x0433, 0x0413},
    {0x0414, 0x0434, 0x0414}, {0x0415, 0x0435, 0x0415}, {0x0416, 0x0436, 0x0416},
    {0x0417, 0x0437, 0x0417}, {0x0418, 0x0438, 0x0418}, {0x0419, 0x0439, 0x0419},
    {0x041a, 0x043a, 0x041a}, {0x041b, 0x043b, 0x041b}, {0x041c, 0x043c, 0x041c},
    {0x041d, 0x043d, 0x041d}, {0x041e, 0x043e, 0x041e}, {0x041f, 0x043f, 0x041f},
    {0x0420, 0x0440, 0x0420}, {0x0421, 0x0441, 0x0421}, {0x0422, 0x0442, 0x0422},
    {0x0423, 0x0443, 0x0423}, {0x0424, 0x0444, 0x0424}, {0x0425, 0x0445, 0x0425},
    {0x0426, 0x0446, 0x0426}, {0x0427, 0x0447, 0x0427}, {0x0428, 0x0448, 0x0428},
    {0x0429, 0x0449, 0x0429}, {0x042a, 0x044a, 0x042a}, {0x042b, 0x044b, 0x042b},
    {0x042c, 0x044c, 0x042c}, {0x042d, 0x044d, 0x042d}, {0x042e, 0x044e, 0x042e},
    {0x042f, 0x044f, 0x042f}, {0x0430, 0x0430, 0x0410}, {0x0431, 0x0431, 0x0411},
    {0x0432, 0x0432, 0x0412}, {0x0433, 0x0433, 0x0413}, {0x0434, 0x0434, 0x0414},
    {0x0435, 0x0435, 0x0415}, {0x0436, 0x0436, 0x0416}, {0x0437, 0x0437, 0x0417},
    {0x0438, 0x0438, 0x0418}, {0x0439, 0x0439, 0x0419}, {0x043a, 0x043a, 0x041a},
    {0x043b, 0x043b, 0x041b}, {0x043c, 0x043c, 0x041c}, {0x043d, 0x043d, 0x041d},
    {0x043e, 0x043e, 0x041e}, {0x043f, 0x043f, 0x041f}, {0x0440, 0x0440, 0x0420},
    {0x0441, 0x0441, 0x0421}, {0x0442, 0x0442, 0x0422}, {0x0443, 0x0443, 0x0423},
    {0x0444, 0x0444, 0x0424}, {0x0445, 0x0445, 0x0425}, {0x0446, 0x0446, 0x0426},
    {0x0447, 0x0447, 0x0427}, {0x0448, 0x0448, 0x0428}, {0x0449, 0x0449, 0x0429},
    {0x044a, 0x044a, 0x042a}, {0x044b, 0x044b, 0x042b}, {0x044c, 0x044c, 0x042c},
    {0x044d, 0x044d, 0x042d}, {0x044e, 0x044e, 0x042e}, {0x044f, 0x044f, 0x042f},
    {0x0451, 0x0451, 0x0401}, {0x1c80, 0x1c80, 0x0412}, {0x1c81, 0x1c81, 0x0414},
    {0x1c82, 0x1c82, 0x041e}, {0x1c83, 0x1c83, 0x0421}, {0x1c84, 0x1c84, 0x0422},
    {0x1c85, 0x1c85, 0x0422}, {0x1c86, 0x1c86, 0x042a}, {0x1e9e, 0x00df, 0x1e9e},
    {0x1fbe, 0x1fbe, 0x0399}, {0x2126, 0x03c9, 0x2126}, {0x212b, 0x00e5, 0x212b},
};

constexpr char32_t toLowerCharacters[128] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
    64, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 91, 92, 93, 94, 95,
    96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
};

constexpr char32_t toUpperCharacters[128] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
    64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
    96, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 123, 124, 125, 126, 127,
};

struct UnicodeHelper {
public:
    bool IsLower(char32_t c)
    {
        if (c < 128) {
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
        if (c < 128) {
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
        if (c < 128) {
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
        if (c < 128) {
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

void PrintLowerCharacters()
{
    std::cout << "constexpr char32_t toLowerCharacters[128] = {";
    for (char32_t c = 0; c < 128; ++c) {
        constexpr int columnCount = 16;
        if (c % columnCount == 0) {
            std::cout << "\n    ";
        }
        else {
            std::cout << ", ";
        }
        if ((U'A' <= c) && (c <= U'Z')) {
            std::cout << (c - U'A' + U'a');
        }
        else if ((U'a' <= c) && (c <= U'z')) {
            std::cout << c;
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

void PrintUpperCharacters()
{
    std::cout << "constexpr char32_t toUpperCharacters[128] = {";
    for (char32_t c = 0; c < 128; ++c) {
        constexpr int columnCount = 16;
        if (c % columnCount == 0) {
            std::cout << "\n    ";
        }
        else {
            std::cout << ", ";
        }
        if ((U'a' <= c) && (c <= U'z')) {
            std::cout << (c - U'a' + U'A');
        }
        else if ((U'A' <= c) && (c <= U'Z')) {
            std::cout << c;
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

struct UnicodeBlockRange {
    char32_t from;
    char32_t to;
};

void GenerateUnicodeCapitalizationTable2(
    const std::vector<UnicodeCharacterData>& unicodeDatas,
    const std::vector<char32_t>& commonlyUsedCharacters)
{
    std::vector<UnicodeCapitalDesc2> capitalDescs;
    for (auto & data : unicodeDatas) {
        if (data.codeValue < 128) {
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
        auto iter = std::find(std::begin(commonlyUsedCharacters), std::end(commonlyUsedCharacters), a.character);
        if (iter != std::end(commonlyUsedCharacters)) {
            return false;
        }
        iter = std::find(std::begin(commonlyUsedCharacters), std::end(commonlyUsedCharacters), a.lowerCase);
        if (iter != std::end(commonlyUsedCharacters)) {
            return false;
        }
        iter = std::find(std::begin(commonlyUsedCharacters), std::end(commonlyUsedCharacters), a.upperCase);
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
        
        if (line.front() == '#') {
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
    GenerateUnicodeCapitalizationTable2(unicodeDatas, codePoints);

//    PrintLowerCharacters();
//    PrintUpperCharacters();

//    std::cout << ::isupper('1') << ::islower('1') << std::endl;
//    std::cout << ::isupper('=') << ::islower('=') << std::endl;
//    std::cout << ::isupper('A') << ::islower('A') << std::endl;
//    std::cout << ::isupper('a') << ::islower('a') << std::endl;

//    SortMarkdownSections("CommonlyUsedUnicodeCharacters.md");

    return 0;
}
