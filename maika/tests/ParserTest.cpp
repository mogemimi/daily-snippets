#include "AST/ASTContext.h"
#include "AST/ASTDumper.h"
#include "Basic/Diagnostic.h"
#include "Driver/Driver.h"
#include "Printer/PrettyPrinter.h"
#include "Sema/Entity.h"
#include <iostream>
#include <sstream>

#include "catch.hpp"

namespace {
bool parse(const std::shared_ptr<DiagnosticHandler>& diag, const std::string& source)
{
    MyDriver driver;
    auto [astContext, ok] = driver.parseString(source, diag);
    return ok && !diag->hasError();
}
} // end of anonymous namespace

TEST_CASE("parser can treat basic sources consistently", "[parser]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    SECTION("parser can deal with an empty source.")
    {
        constexpr auto source = " \t";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat null literal")
    {
        constexpr auto source = "function f() { return null; }\n";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can not use trailing commas with parameters")
    {
        constexpr auto source = "function f(a, b, c,) {}\n";
        REQUIRE(!parse(diag, source));
    }
    SECTION("parser can not use trailing commas with arguments")
    {
        constexpr auto source = "function f() { g(a, b, c,); }\n";
        REQUIRE(!parse(diag, source));
    }
    SECTION("parser can treat subscript expression")
    {
        constexpr auto source = R"(
        function g(x) { return x; }
        function f() {
            let a = [40, 41, 42];
            a[0] = a[1];
            a[1] = a[0] + a[2];
            a[g(3)] = g(a[0]);
            a = [4, 3, 2, 1];
        })";
        REQUIRE(parse(diag, source));
    }
}

TEST_CASE("parser can treat array literal", "[parser]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    SECTION("parser can treat array literal")
    {
        constexpr auto source = "function f() { return [1, 2, 3, 4]; }\n";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat empty array literal")
    {
        constexpr auto source = "function f() { return []; }\n";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat single array literal")
    {
        constexpr auto source = "function f() { return [42]; }\n";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat trailing comma")
    {
        constexpr auto source = "function f() { return [1, 2, 3, 4,]; }\n";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser cannot allow trailing comma without elements")
    {
        constexpr auto source = "function f() { return [,]; }\n";
        REQUIRE(!parse(diag, source));
    }
    SECTION("parser cannot allow comma without elements")
    {
        constexpr auto source = "function f() { return [, 2]; }\n";
        REQUIRE(!parse(diag, source));
    }
}

TEST_CASE("parser can treat map literal", "[parser]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    SECTION("parser can treat map literal")
    {
        constexpr auto source = R"(function f() { return ["a": 1, "b": 2, "c": 3]; })";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat empty map literal")
    {
        constexpr auto source = "function f() { return [:]; }\n";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat single map literal")
    {
        constexpr auto source = R"(function f() { return ["a" : 42]; })";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat trailing comma with map literal")
    {
        constexpr auto source = R"(function f() { return ["a" : 42,]; })";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser cannot allow comma without elements")
    {
        constexpr auto source = R"(function f() { return [, "a" : 42,]; })";
        REQUIRE(!parse(diag, source));
    }
#if 0
	// ECMAScript-like map literal
	SECTION("parser can treat map literal")
	{
		constexpr auto source = "function f() { return {\"a\": 1, \"b\": 2, \"c\": 3}; }\n";
		REQUIRE(parse(diag, source));
	}
	SECTION("parser can treat single map literal")
	{
		constexpr auto source = "function f() { return {\"a\": 42}; }\n";
		REQUIRE(parse(diag, source));
	}
	SECTION("parser can treat trailing comma with map literal")
	{
		constexpr auto source = "function f() { return {\"a\": 42,}; }\n";
		REQUIRE(parse(diag, source));
	}
	SECTION("parser cannot allow trailing comma without elements")
	{
		constexpr auto source = "function f() { return {,}; }\n";
		REQUIRE(!parse(diag, source));
	}
	SECTION("parser cannot allow comma without elements")
	{
		constexpr auto source = "function f() { return {, \"a\":42}; }\n";
		REQUIRE(!parse(diag, source));
	}
	SECTION("block scope and unary expression, not binary expression with map and integer literals")
	{
		constexpr auto source = "function f() { {} - 1; }\n";
		REQUIRE(parse(diag, source));
	}
	SECTION("block scope (not map literal) and empty statement.")
	{
		constexpr auto source = "function f() { {}; }\n";
		REQUIRE(parse(diag, source));
	}
	SECTION("empty map literal can be used as an experession statement with parentheses.")
	{
		constexpr auto source = "function f() { ({}); }\n";
		REQUIRE(parse(diag, source));
	}
	SECTION("map literal can't be used as an experession statement.")
	{
		constexpr auto source = "function f() { {\"a\":42}; }\n";
		REQUIRE(!parse(diag, source));
	}
	SECTION("map literal can be used as an experession statement with parentheses.")
	{
		constexpr auto source = "function f() { ({\"a\":42}); }\n";
		REQUIRE(parse(diag, source));
	}
	SECTION("map literal with indexer can't be used as an experession statement.")
	{
		constexpr auto source = "function f() { {\"a\":42}[\"a\"]; }\n";
		REQUIRE(!parse(diag, source));
	}
	SECTION("map literal with indexer can be used as an experession statement with parentheses.")
	{
		constexpr auto source = "function f() { ({\"a\":42})[\"a\"]; }\n";
		REQUIRE(parse(diag, source));
	}
#endif
}

TEST_CASE("parser can treat if, while, for and for...in statements", "[parser]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    SECTION("parser can treat if statement")
    {
        constexpr auto source = R"(function f() {
            let a = 42;
            if (a > 0) {}
            //if (let b = a) {} // TODO: Not implemented
        })";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat while statement")
    {
        constexpr auto source = R"(function f() {
            let i = 0;
            while (i < 42) {
                ++i;
            }
        })";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat for statement")
    {
        constexpr auto source = R"(function f() {
            for (let i = 0; i < 42; i++) {
                print(i);
            }
        })";
        REQUIRE(parse(diag, source));
    }
    SECTION("parser can treat for...in statement")
    {
        constexpr auto source = R"(function f() {
            let a = [42, 43, 44];
            let m;
            for (m in a) { print(m); }
            for (let n in a) { print(n); }
            for (const n in a) { print(n); }
        })";
        REQUIRE(parse(diag, source));
    }
}
