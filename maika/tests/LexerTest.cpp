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
bool lexerCheck(const std::shared_ptr<DiagnosticHandler>& diag, const std::string& source)
{
    MyDriver driver;
    auto [astContext, ok] = driver.parseString(source, diag);
    return ok;
}
} // end of anonymous namespace

TEST_CASE("lexer can treat basic sources consistently", "[lexer]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    SECTION("lexer can deal with an empty source.")
    {
        constexpr auto source = "";
        REQUIRE(lexerCheck(diag, source));
        REQUIRE(!diag->hasError());
    }
    SECTION("lexer can skip UTF-8 BOM if it's present")
    {
        constexpr auto source = "\xEF\xBB\xBF"
                                "function f() {}\n";
        REQUIRE(lexerCheck(diag, source));
        REQUIRE(!diag->hasError());
    }
    SECTION("lexer can skip CRLF if it's present")
    {
        constexpr auto source = "function f() {}\r\n";
        REQUIRE(lexerCheck(diag, source));
        REQUIRE(!diag->hasError());
    }
    SECTION("lexer can treat BCPL-style comments")
    {
        constexpr auto source = R"(
// foo
function f() { // bar
    // TODO
	/// NOTE
	// // //
	// /*  */
	//*
	////////////
}
)";
        REQUIRE(lexerCheck(diag, source));
        REQUIRE(!diag->hasError());
    }
    SECTION("lexer can treat C-style comments")
    {
        constexpr auto source = R"(
/* aaa */
function f() { /*
	aaa
	// TODO
	{
*/
	/******
	aaaaaaa
	******/
}
)";
        REQUIRE(lexerCheck(diag, source));
        REQUIRE(!diag->hasError());
    }
    SECTION("lexer can treat C-style comments")
    {
        constexpr auto source = R"(
function f(/*){*/
}
)";
        REQUIRE(!lexerCheck(diag, source));
        REQUIRE(diag->hasError());
    }
}
