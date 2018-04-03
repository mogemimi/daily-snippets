#include "Sema/SemaChecker.h"
#include "AST/ASTContext.h"
#include "AST/ASTDumper.h"
#include "Basic/Diagnostic.h"
#include "Driver/Driver.h"
#include "Sema/Entity.h"
#include "Sema/IdentifierResolver.h"

#include "catch.hpp"

namespace {
bool semaCheck(const std::shared_ptr<DiagnosticHandler>& diag, const std::string& source)
{
    MyDriver driver;
    auto [astContext, ok] = driver.parseString(source, diag);
    REQUIRE(ok);

    ASTTraverser traverser;
    IdentifierContext context;

    IdentifierResolver resolver(&context, diag);
    traverser.traverse(astContext, resolver);
    REQUIRE(!diag->hasError());

    SemaChecker semaChecker(diag);
    traverser.traverse(astContext, semaChecker);
    return !diag->hasError();
}
} // end of anonymous namespace

TEST_CASE("const can be defined as constant data types", "[semacheck]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    SECTION("const can be defined as constant data types")
    {
        constexpr auto source = R"(function f() { const a = 42; })";
        REQUIRE(semaCheck(diag, source));
    }
    SECTION("const cannot be reassigned.")
    {
        constexpr auto source = R"(function f() {
            const a = 42;
            a = 100;
        })";
        REQUIRE(!semaCheck(diag, source));
        REQUIRE(
            stream->hasError("3:13: error: 'a' cannot be reassigned because it is a constant."));
    }
    SECTION("typename cannot be assigned.")
    {
        constexpr auto source = R"(function f() { int = 42; })";
        REQUIRE(!semaCheck(diag, source));
        REQUIRE(stream->hasError(
            "1:16: error: 'int' cannot be assigned because it only refers to a type."));
    }
}

TEST_CASE("lvalue and rvalue", "[semacheck]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    SECTION("The left-hand side of an assignment must be a variable.")
    {
        constexpr auto source = R"(function test() { 4 = 2; })";
        REQUIRE(!semaCheck(diag, source));
        REQUIRE(stream->hasError(
            "1:19: error: The left-hand side of an assignment must be a variable."));
    }
    SECTION("The left-hand side of an assignment must be a variable.")
    {
        constexpr auto source = R"(function test() { "a" = "a"; })";
        REQUIRE(!semaCheck(diag, source));
        REQUIRE(stream->hasError(
            "1:19: error: The left-hand side of an assignment must be a variable."));
    }
    SECTION("The LHS is correctly a variable.")
    {
        constexpr auto source = R"(function test() { let a = "a"; })";
        REQUIRE(semaCheck(diag, source));
    }
    SECTION("The left-hand side of an assignment must be a variable.")
    {
        constexpr auto source = R"(function test() {
            let a;
            let b;
            a = b = 2;
        })";
        REQUIRE(semaCheck(diag, source));
    }
    SECTION("The left-hand side of an assignment must be a variable.")
    {
        constexpr auto source = R"(function test() {
            let a;
            (a) = 2;
        })";
        REQUIRE(semaCheck(diag, source));
    }
    SECTION("The left-hand side of an assignment must be a variable.")
    {
        constexpr auto source = R"(function test() {
            let a;
            let b;
            a = (b = 2);
        })";
        REQUIRE(semaCheck(diag, source));
    }
    SECTION("The left-hand side of an assignment must be a variable.")
    {
        constexpr auto source = R"(function test() {
            let a;
            let b;
            (a = b) = 2;
        })";
        REQUIRE(!semaCheck(diag, source));
        REQUIRE(stream->hasError(
            "4:14: error: The left-hand side of an assignment must be a variable."));
    }
    SECTION("Function call is rvalue.")
    {
        constexpr auto source = R"(function f() { f() = 2; })";
        REQUIRE(!semaCheck(diag, source));
    }
}
