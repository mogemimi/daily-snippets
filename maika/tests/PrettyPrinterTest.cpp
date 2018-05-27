#include "Printer/PrettyPrinter.h"
#include "AST/ASTContext.h"
#include "Basic/Diagnostic.h"
#include "Driver/Driver.h"
#include "Printer/ASTFormatter.h"
#include "Sema/Entity.h"
#include <iostream>
#include <sstream>

#include "catch.hpp"

namespace {
std::string prettyPrint(const std::shared_ptr<DiagnosticHandler>& diag, const std::string& source)
{
    Driver driver;
    auto [astContext, ok] = driver.parseString(source, diag);

    REQUIRE(ok);

    ASTTraverser traverser;
    ASTFormatter formatter;
    traverser.traverse(astContext, formatter);

    PrettyPrinter printer;
    traverser.traverse(astContext, printer);
    return printer.getResult();
}
} // end of anonymous namespace

TEST_CASE("pretty print", "[prettyprinter]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    SECTION("printer prints function declaration")
    {
        constexpr auto source = "func f() {\n"
                                "}\n";
        REQUIRE(prettyPrint(diag, source) == source);
    }
    SECTION("printer prints function declaration")
    {
        constexpr auto source = "func f(a, b, c) {\n"
                                "    return (a + b) * c;\n"
                                "}\n";
        REQUIRE(prettyPrint(diag, source) == source);
    }
    SECTION("printer prints callable")
    {
        constexpr auto source = "func f(g, x) {\n"
                                "    if (g(x) < 42) {\n"
                                "        return g(x);\n"
                                "    }\n"
                                "    return g(x);\n"
                                "}\n";
        REQUIRE(prettyPrint(diag, source) == source);
    }
    SECTION("printer prints nested statements")
    {
        constexpr auto source = "func f(a, b) {\n"
                                "    for (let i = 0; i < 42; i++) {\n"
                                "        if (i <= a) {\n"
                                "            while (i >= b) {\n"
                                "                return a;\n"
                                "            }\n"
                                "            return b;\n"
                                "        }\n"
                                "        return i;\n"
                                "    }\n"
                                "    return a + b;\n"
                                "}\n";
        REQUIRE(prettyPrint(diag, source) == source);
    }
    SECTION("printer prints classes")
    {
        constexpr auto source = "class Vector2 {\n"
                                "    let x: Int = 0;\n"
                                "    let y: Int = 0;\n"
                                "    func dot(v: Vector2) -> Int {\n"
                                "        return x * v.x + y * v.y;\n"
                                "    }\n"
                                "\n"
                                "    func cross(v: Vector2) -> Int {\n"
                                "        return x * v.y - y * v.x;\n"
                                "    }\n"
                                "}\n";
        REQUIRE(prettyPrint(diag, source) == source);
    }
    SECTION("printer prints arrays")
    {
        constexpr auto source = "func f() {\n"
                                "    let x = [0, 1 + 2, (3 - 4) * 5, 6];\n"
                                "    let y = [];\n"
                                "}\n";
        REQUIRE(prettyPrint(diag, source) == source);
    }
    SECTION("printer prints maps")
    {
        constexpr auto source = "func f() {\n"
                                "    let x = [\"a\": 42, \"b\": 5];\n"
                                "    let y = [:];\n"
                                "}\n";
        REQUIRE(prettyPrint(diag, source) == source);
    }
}

TEST_CASE("ast formatter", "[astformatter]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    SECTION("printer abbreviates redundant parentheses")
    {
        constexpr auto source = "func f(a,b,c){return ((((a)+b))*((c)));}\n";
        constexpr auto expect = "func f(a, b, c) {\n"
                                "    return ((a + b) * c);\n"
                                "}\n";
        REQUIRE(prettyPrint(diag, source) == expect);
    }
    SECTION("printer does not allow single line if statements")
    {
        constexpr auto source = "func min(a, b) {\n"
                                "    if(a<b)return a;\n"
                                "    return b;\n"
                                "}\n";
        constexpr auto expect = "func min(a, b) {\n"
                                "    if (a < b) {\n"
                                "        return a;\n"
                                "    }\n"
                                "    return b;\n"
                                "}\n";
        REQUIRE(prettyPrint(diag, source) == expect);
    }
    SECTION("printer does not allow single line for-statements")
    {
        constexpr auto source = "func f() {\n"
                                "    for(let i=0;i<42;i++) print(i);\n"
                                "}\n";
        constexpr auto expect = "func f() {\n"
                                "    for (let i = 0; i < 42; i++) {\n"
                                "        print(i);\n"
                                "    }\n"
                                "}\n";
        REQUIRE(prettyPrint(diag, source) == expect);
    }
    SECTION("printer does not allow single line while-statements")
    {
        constexpr auto source = "func f(a, b) {\n"
                                "    while(a < b) a++;\n"
                                "}\n";
        constexpr auto expect = "func f(a, b) {\n"
                                "    while (a < b) {\n"
                                "        a++;\n"
                                "    }\n"
                                "}\n";
        REQUIRE(prettyPrint(diag, source) == expect);
    }
    SECTION("printer prints compound statements")
    {
        constexpr auto source = "func f(a, b) {\n"
                                "    while(a < b) a++;\n"
                                "}\n";
        constexpr auto expect = "func f(a, b) {\n"
                                "    while (a < b) {\n"
                                "        a++;\n"
                                "    }\n"
                                "}\n";
        REQUIRE(prettyPrint(diag, source) == expect);
    }
}
