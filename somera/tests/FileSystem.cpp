// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "FileSystem.h"
#include <gtest/iutest_switch.hpp>

using namespace somera;

TEST(FileSystem, normalize)
{
    const auto normalize = FileSystem::normalize;
    EXPECT_EQ(FileSystem::getCurrentDirectory(), normalize(""));
    EXPECT_EQ(FileSystem::getCurrentDirectory(), normalize("."));
    EXPECT_EQ(FileSystem::getCurrentDirectory(), normalize("./"));

    EXPECT_EQ("/usr/local/bin", normalize("/usr/local/bin"));
    EXPECT_EQ("/usr/local/bin", normalize("/usr/local/bin/"));
    EXPECT_EQ("/usr/local/bin", normalize("/usr/local/bin/."));
    EXPECT_EQ("/usr/local/bin", normalize("/usr/local/bin/./"));
    EXPECT_EQ("/usr/local/bin", normalize("/usr/local/./bin"));
    EXPECT_EQ("/usr/local/bin", normalize("/usr/./local/bin"));
    EXPECT_EQ("/usr/local", normalize("/usr/local/bin/.."));
    EXPECT_EQ("/usr/local", normalize("/usr/local/bin/../"));
    EXPECT_EQ("/usr", normalize("/usr/local/bin/../.."));
    EXPECT_EQ("/usr", normalize("/usr/local/bin/../../"));
    EXPECT_EQ("/usr/local/bin", normalize("/usr/local/../local/bin"));
    EXPECT_EQ("/usr/local", normalize("/usr/local/../local/bin/.."));
}

TEST(FileSystem, relative)
{
    const auto relative = FileSystem::relative;
    EXPECT_EQ(".", relative("/usr/local/bin", "/usr/local/bin"));
    EXPECT_EQ(".", relative("/usr/local/bin/.", "/usr/local/bin"));
    EXPECT_EQ(".", relative("/usr/local/bin/./", "/usr/local/bin"));
    EXPECT_EQ(".", relative("/usr/local/bin/././", "/usr/local/bin"));
    EXPECT_EQ(".", relative("/usr/local/bin/./././", "/usr/local/bin"));
    EXPECT_EQ("..", relative("/usr/local/bin/..", "/usr/local/bin"));
    EXPECT_EQ("..", relative("/usr/local/bin/../", "/usr/local/bin"));
    EXPECT_EQ("..", relative("/usr/local/bin/.././", "/usr/local/bin"));
    EXPECT_EQ("..", relative("/usr/local/bin/./../", "/usr/local/bin"));
    EXPECT_EQ("../..", relative("/usr/local/bin/../../", "/usr/local/bin"));
    EXPECT_EQ("../..", relative("/usr/local/bin/../..", "/usr/local/bin"));
    EXPECT_EQ("../..", relative("/usr/local/bin/../../.", "/usr/local/bin"));
    EXPECT_EQ("../..", relative("/usr/local/bin/.././../", "/usr/local/bin"));
    EXPECT_EQ("../..", relative("/usr/local/bin/./../../", "/usr/local/bin"));

    EXPECT_EQ(".", relative("/usr/local/../local/bin", "/usr/local/bin"));
    EXPECT_EQ("..", relative("/usr/local", "/usr/local/bin"));
    EXPECT_EQ("../..", relative("/usr", "/usr/local/bin"));
    EXPECT_EQ("../..", relative("/usr/local/..", "/usr/local/bin"));
    EXPECT_EQ("../..", relative("/usr/local/../local/..", "/usr/local/bin"));

    EXPECT_EQ("gcc", relative("/usr/local/bin/gcc", "/usr/local/bin"));
    EXPECT_EQ("../opt", relative("/usr/local/opt", "/usr/local/bin"));
    EXPECT_EQ("../../share", relative("/usr/share", "/usr/local/bin"));
    EXPECT_EQ("../../share/dict", relative("/usr/share/dict", "/usr/local/bin"));
}
