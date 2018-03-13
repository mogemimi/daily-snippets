#include "AST/ASTContext.h"
#include "AST/ASTDumper.h"
#include "Diagnostic.h"
#include "Formatter.h"
#include "MyDriver.h"
#include "Sema/Entity.h"
#include <iostream>
#include <sstream>

#include "catch.hpp"

TEST_CASE("lexer can treat basic sources consistently", "[lexer]")
{
    auto diag = std::make_shared<DiagnosticHandler>();
    MyDriver driver;

    SECTION("lexer can deal with an empty source.")
    {
        constexpr auto source = "";
        auto [astContext, ok] = driver.parseString(source, diag);
        REQUIRE(ok);
        REQUIRE(!diag->hasError());
    }
    SECTION("lexer can skip UTF-8 BOM if it's present")
    {
        constexpr auto source = "\xEF\xBB\xBF"
                                "function f() {}\n";
        auto [astContext, ok] = driver.parseString(source, diag);
        REQUIRE(ok);
        REQUIRE(!diag->hasError());
    }
    SECTION("lexer can skip CRLF if it's present")
    {
        constexpr auto source = "function f() {}\r\n";
        auto [astContext, ok] = driver.parseString(source, diag);
        REQUIRE(ok);
        REQUIRE(!diag->hasError());
    }
}

TEST_CASE("parser can treat basic sources consistently", "[parser]")
{
    auto diag = std::make_shared<DiagnosticHandler>();
    MyDriver driver;

    SECTION("parser can deal with an empty source.")
    {
        constexpr auto source = " \t";
        auto [astContext, ok] = driver.parseString(source, diag);
        REQUIRE(ok);
        REQUIRE(!diag->hasError());
    }
}

TEST_CASE("Lexer", "[lexer]")
{
    constexpr auto source = R"(
function min(a : int, b : int) : int {
    // TODO: Replace with '?' operator.
    if (a < b) {
		const c = 42;
        return a;
    }
    return b;
}
)";

    auto diag = std::make_shared<DiagnosticHandler>();

    MyDriver driver;
    auto [astContext, ok] = driver.parseString(source, diag);
    REQUIRE(ok);

    ASTTraverser traverser;

    ASTDumper dumper;
    traverser.traverse(astContext, dumper);
    REQUIRE(!diag->hasError());
    // printf("%s\n", dumper.getResult().c_str());

    Formatter formatter;
    traverser.traverse(astContext, formatter);
    REQUIRE(!diag->hasError());
    printf("%s\n", formatter.getResult().c_str());
}
