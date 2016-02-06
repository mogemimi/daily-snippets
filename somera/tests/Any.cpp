// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "Any.h"
#include <gtest/iutest_switch.hpp>

using namespace somera;
using somera::Any;

TEST(Any, FirstCase)
{
    Any x = std::string("Chuck Norris");

    ASSERT_EQ(typeid(std::string), x.type());
    ASSERT_TRUE(x.is<std::string>());
    EXPECT_EQ(std::string("Chuck Norris"), x.as<std::string>());
    EXPECT_EQ("Chuck Norris", x.as<std::string>());
}

TEST(Any, SharedPointer)
{
    {
        Any x = std::make_shared<std::string>("Chuck Norris");
        ASSERT_EQ(typeid(std::shared_ptr<std::string>), x.type());
        ASSERT_TRUE(x.is<std::shared_ptr<std::string>>());
        EXPECT_EQ(std::string("Chuck Norris"), *x.as<std::shared_ptr<std::string>>());
        EXPECT_EQ("Chuck Norris", *x.as<std::shared_ptr<std::string>>());
    }
    {
        auto original = std::make_shared<std::string>("Chuck Norris");
        auto copied = original;
        Any x = copied;

        ASSERT_EQ(typeid(std::shared_ptr<std::string>), x.type());
        ASSERT_TRUE(x.is<std::shared_ptr<std::string>>());
        EXPECT_EQ(std::string("Chuck Norris"), *x.as<std::shared_ptr<std::string>>());
        EXPECT_EQ("Chuck Norris", *x.as<std::shared_ptr<std::string>>());
        EXPECT_EQ(original, x.as<std::shared_ptr<std::string>>());
    }
    {
        auto original = std::make_shared<std::string>("Chuck Norris");
        auto copied = original;
        Any x = std::move(copied);

        ASSERT_EQ(typeid(std::shared_ptr<std::string>), x.type());
        ASSERT_TRUE(x.is<std::shared_ptr<std::string>>());
        EXPECT_EQ(std::string("Chuck Norris"), *x.as<std::shared_ptr<std::string>>());
        EXPECT_EQ("Chuck Norris", *x.as<std::shared_ptr<std::string>>());
        EXPECT_EQ(original, x.as<std::shared_ptr<std::string>>());
    }
    {
        Any x = std::make_shared<std::string>("Chuck Norris");
        ASSERT_EQ(typeid(std::shared_ptr<std::string>), x.type());

        auto copied = x.as<std::shared_ptr<std::string>>();

        EXPECT_EQ("Chuck Norris", *copied);
        EXPECT_EQ(copied, x.as<std::shared_ptr<std::string>>());

        auto moved = std::move(x.as<std::shared_ptr<std::string>>());

        EXPECT_EQ(copied, moved);
        EXPECT_EQ("Chuck Norris", *moved);
        EXPECT_NE(moved, x.as<std::shared_ptr<std::string>>());
    }
}
