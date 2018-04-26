#include "AST/ASTContext.h"
#include "AST/ASTDumper.h"
#include "Basic/Diagnostic.h"
#include "Driver/Driver.h"
#include "Printer/PrettyPrinter.h"
#include "Sema/Entity.h"
#include <iostream>
#include <sstream>

#include "catch.hpp"

TEST_CASE("parser can treat basic sources consistently", "[parser]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);
    MyDriver driver;

    SECTION("parser can deal with an empty source.")
    {
        constexpr auto source = " \t";
        auto [astContext, ok] = driver.parseString(source, diag);
        REQUIRE(ok);
        REQUIRE(!diag->hasError());
    }
    SECTION("parser can treat null literal")
    {
        constexpr auto source = "function f() { return null; }\n";
        auto [astContext, ok] = driver.parseString(source, diag);
        REQUIRE(ok);
        REQUIRE(!diag->hasError());
    }
    SECTION("parser can treat array literal")
    {
        constexpr auto source = "function f() { return [1, 2, 3, 4]; }\n";
        auto [astContext, ok] = driver.parseString(source, diag);
        REQUIRE(ok);
        REQUIRE(!diag->hasError());
    }
    SECTION("parser can treat empty array literal")
    {
        constexpr auto source = "function f() { return []; }\n";
        auto [astContext, ok] = driver.parseString(source, diag);
        REQUIRE(ok);
        REQUIRE(!diag->hasError());
    }
    SECTION("parser can treat single array literal")
    {
        constexpr auto source = "function f() { return [42]; }\n";
        auto [astContext, ok] = driver.parseString(source, diag);
        REQUIRE(ok);
        REQUIRE(!diag->hasError());
    }
    SECTION("parser can treat trailing comma")
    {
        constexpr auto source = "function f() { return [1, 2, 3, 4,]; }\n";
        auto [astContext, ok] = driver.parseString(source, diag);
        REQUIRE(ok);
        REQUIRE(!diag->hasError());
    }
    // SECTION("parser can treat map literal")
    //{
    //    constexpr auto source = "function f() { return [\"a\": 1, \"b\": 2, \"c\": 3]; }\n";
    //    auto [astContext, ok] = driver.parseString(source, diag);
    //    REQUIRE(ok);
    //    REQUIRE(!diag->hasError());
    //}
    // SECTION("parser can treat single map literal")
    //{
    //    constexpr auto source = "function f() { return [\"a\": 42]; }\n";
    //    auto [astContext, ok] = driver.parseString(source, diag);
    //    REQUIRE(ok);
    //    REQUIRE(!diag->hasError());
    //}
    // SECTION("parser can treat trailing comma")
    //{
    //    constexpr auto source = "function f() { return [\"foo\": 42,]; }\n";
    //    auto [astContext, ok] = driver.parseString(source, diag);
    //    REQUIRE(ok);
    //    REQUIRE(!diag->hasError());
    //}
}
