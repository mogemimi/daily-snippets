// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "StringHelper.h"
#include <gtest/iutest_switch.hpp>

using namespace somera;

TEST(StringHelper, startWith)
{
    const auto startWith = StringHelper::startWith;
    EXPECT_TRUE(startWith("", ""));
    EXPECT_TRUE(startWith("-", "-"));
    EXPECT_TRUE(startWith("baka and test", "baka and test"));
    EXPECT_TRUE(startWith("baka and test", "baka"));
    EXPECT_TRUE(startWith("baka", ""));
    EXPECT_FALSE(startWith("baka", "baka and test"));
    EXPECT_FALSE(startWith("", "baka"));
    EXPECT_FALSE(startWith("-baka", "baka"));
    EXPECT_FALSE(startWith("baka", "-baka"));
}

TEST(StringHelper, split)
{
    using StringHelper::split;
    {
        auto result = split("", '.');
        ASSERT_EQ(1, result.size());
        EXPECT_EQ("", result[0]);
    }
    {
        auto result = split("source.example.com", '.');
        ASSERT_EQ(3, result.size());
        EXPECT_EQ("source", result[0]);
        EXPECT_EQ("example", result[1]);
        EXPECT_EQ("com", result[2]);
    }
    {
        auto result = split("example.com.", '.');
        ASSERT_EQ(3, result.size());
        EXPECT_EQ("example", result[0]);
        EXPECT_EQ("com", result[1]);
        EXPECT_EQ("", result[2]);
    }
    {
        auto result = split("...", '.');
        ASSERT_EQ(4, result.size());
        EXPECT_EQ("", result[0]);
        EXPECT_EQ("", result[1]);
        EXPECT_EQ("", result[2]);
        EXPECT_EQ("", result[3]);
    }
    {
        auto result = split(".a..b", '.');
        ASSERT_EQ(4, result.size());
        EXPECT_EQ("", result[0]);
        EXPECT_EQ("a", result[1]);
        EXPECT_EQ("", result[2]);
        EXPECT_EQ("b", result[3]);
    }
    {
        auto result = split("", "//");
        ASSERT_EQ(1, result.size());
        EXPECT_EQ("", result[0]);
    }
    {
        auto result = split("source//example//com", "//");
        ASSERT_EQ(3, result.size());
        EXPECT_EQ("source", result[0]);
        EXPECT_EQ("example", result[1]);
        EXPECT_EQ("com", result[2]);
    }
    {
        auto result = split("example//com//", "//");
        ASSERT_EQ(3, result.size());
        EXPECT_EQ("example", result[0]);
        EXPECT_EQ("com", result[1]);
        EXPECT_EQ("", result[2]);
    }
    {
        auto result = split("//////", "//");
        ASSERT_EQ(4, result.size());
        EXPECT_EQ("", result[0]);
        EXPECT_EQ("", result[1]);
        EXPECT_EQ("", result[2]);
        EXPECT_EQ("", result[3]);
    }
    {
        auto result = split("//a////b", "//");
        ASSERT_EQ(4, result.size());
        EXPECT_EQ("", result[0]);
        EXPECT_EQ("a", result[1]);
        EXPECT_EQ("", result[2]);
        EXPECT_EQ("b", result[3]);
    }
}

TEST(StringHelper, trimRight)
{
    using StringHelper::trimRight;
    EXPECT_EQ("", trimRight("      ", ' '));
    EXPECT_EQ("hoge", trimRight("hoge    ", ' '));
    EXPECT_EQ("  hoge", trimRight("  hoge  ", ' '));
    EXPECT_EQ("    hoge", trimRight("    hoge", ' '));
}

TEST(StringHelper, trimLeft)
{
    using StringHelper::trimLeft;
    EXPECT_EQ("", trimLeft("      ", ' '));
    EXPECT_EQ("hoge    ", trimLeft("hoge    ", ' '));
    EXPECT_EQ("hoge  ", trimLeft("  hoge  ", ' '));
    EXPECT_EQ("hoge", trimLeft("    hoge", ' '));
}
