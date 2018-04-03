#include "Sema/TypeResolver.h"
#include "AST/ASTContext.h"
#include "AST/ASTDumper.h"
#include "Basic/Diagnostic.h"
#include "Driver/Driver.h"
#include "Sema/Entity.h"
#include "Sema/IdentifierResolver.h"
#include "Sema/SemaChecker.h"
#include "Sema/TypeInferer.h"

#include "catch.hpp"

namespace {
bool typeCheck(const std::shared_ptr<DiagnosticHandler>& diag, const std::string& source)
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
    REQUIRE(!diag->hasError());

    TypeResolver typeResolver(diag);
    traverser.traverse(astContext, typeResolver);
    return !diag->hasError();
}
} // end of anonymous namespace

TEST_CASE("TypeResolver can detect type mismatch", "[typecheck]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    SECTION("Type 'int' is not assignable to 'string'.")
    {
        constexpr auto source = R"(function test() {
            let a = "a";
            a = 2;
        })";
        REQUIRE(!typeCheck(diag, source));
        REQUIRE(stream->hasError("3:13: error: Type 'int' is not assignable to 'string'."));
    }
    SECTION("Implicit type conversion: int to double")
    {
        constexpr auto source = R"(function test() {
            let a = 2.0;
            a = 2;
        })";
        REQUIRE(typeCheck(diag, source));
    }
    SECTION("Type 'double' is not assignable to 'int'.")
    {
        constexpr auto source = R"(function test() {
            let a = 2;
            a = 2.0;
        })";
        REQUIRE(!typeCheck(diag, source));
        REQUIRE(stream->hasError("3:13: error: Type 'double' is not assignable to 'int'."));
    }
    SECTION("Type 'int' is not assignable to 'bool'.")
    {
        constexpr auto source = R"(function test() {
            let a = true;
            a = 1;
        })";
        REQUIRE(!typeCheck(diag, source));
        REQUIRE(stream->hasError("3:13: error: Type 'int' is not assignable to 'bool'."));
    }
    SECTION("Type 'bool' is not assignable to 'double'")
    {
        constexpr auto source = R"(function test() {
            let a = 1.0;
            a = true;
        })";
        REQUIRE(!typeCheck(diag, source));
        REQUIRE(stream->hasError("3:13: error: Type 'bool' is not assignable to 'double'."));
    }
    SECTION("Implicit type conversion: int to double")
    {
        constexpr auto source = R"(function test() {
            let a = 1.0;
            a = 1;
        })";
        REQUIRE(typeCheck(diag, source));
    }
    SECTION("Implicit type conversion: int to double")
    {
        constexpr auto source = R"(function test() {
            return 10 + 4.2;
        })";
        REQUIRE(typeCheck(diag, source));
    }
    SECTION("Operator '+' cannot be applied to types 'int' and 'string'")
    {
        constexpr auto source = R"(function test() {
            let a = 10 + "hello";
        })";
        REQUIRE(!typeCheck(diag, source));
        REQUIRE(stream->hasError(
            "2:21: error: Operator '+' cannot be applied to types 'int' and 'string'."));
    }
    SECTION("Call a function")
    {
        constexpr auto source = R"(
        function f() { return 42; }
        function test() {
            let a = 3;
            a = f();
        }
        )";
        REQUIRE(typeCheck(diag, source));
    }
    SECTION("Call a function")
    {
        constexpr auto source = R"(
        function f() { return 42; }
        function test() {
            let a = "hello";
            a = f();
        }
        )";
        REQUIRE(!typeCheck(diag, source));
        REQUIRE(stream->hasError("5:13: error: Type 'int' is not assignable to 'string'."));
    }
    SECTION("Call a function")
    {
        constexpr auto source = R"(
        function f(x) { return x; }
        function test() { return f(2.0) + 3.14; }
        )";
        REQUIRE(typeCheck(diag, source));
    }
    SECTION("Call a function")
    {
        constexpr auto source = R"(
        function f(x) { return x; }
        function test() { return 3.14 + f(2.0); }
        )";
        REQUIRE(typeCheck(diag, source));
    }
    SECTION("Operator '+' cannot be applied to types 'string' and 'double'.")
    {
        constexpr auto source = R"(
        function f(x) { return x; }
        function test() { return "hello" + f(2.0); }
        )";
        REQUIRE(!typeCheck(diag, source));
        REQUIRE(stream->hasError(
            "3:34: error: Operator '+' cannot be applied to types 'string' and 'double'."));
    }
    SECTION("Operator '+' cannot be applied to types 'double' and 'string'.")
    {
        constexpr auto source = R"(
        function f(x) { return x; }
        function test() { return f(2.0) + "hello"; }
        )";
        REQUIRE(!typeCheck(diag, source));
    }
    SECTION("Use modulus on integer")
    {
        constexpr auto source = R"(function test() { 10 % 3; })";
        REQUIRE(typeCheck(diag, source));
    }
    SECTION("invalid operands of types 'double' and 'double' to binary 'operator%'.")
    {
        constexpr auto source = R"(function test() { 42 % 3.14; })";
        REQUIRE(!typeCheck(diag, source));
        REQUIRE(stream->hasError(
            "1:24: error: invalid operands to binary expression ('int' and 'double')."));
    }
    SECTION("invalid operands of types 'double' and 'double' to binary 'operator%'.")
    {
        constexpr auto source = R"(function test() { 3.14 % 42; })";
        REQUIRE(!typeCheck(diag, source));
        REQUIRE(stream->hasError(
            "1:19: error: invalid operands to binary expression ('double' and 'int')."));
    }
    SECTION("invalid operands of types 'double' and 'double' to binary 'operator%'.")
    {
        constexpr auto source = R"(function f(x) { x % 3.14; })";
        REQUIRE(!typeCheck(diag, source));
        REQUIRE(stream->hasError(
            "1:21: error: invalid operands to binary expression ('any' and 'double')."));
    }
    SECTION("invalid operands of types 'bool' and 'bool' to binary 'operator%'.")
    {
        constexpr auto source = R"(function test() { 42 % true; })";
        REQUIRE(!typeCheck(diag, source));
        REQUIRE(stream->hasError(
            "1:24: error: invalid operands to binary expression ('int' and 'bool')."));
    }
    SECTION("invalid operands of types 'bool' and 'bool' to binary 'operator%'.")
    {
        constexpr auto source = R"(function test() { true % 42; })";
        REQUIRE(!typeCheck(diag, source));
        REQUIRE(stream->hasError(
            "1:19: error: invalid operands to binary expression ('bool' and 'int')."));
    }
    SECTION("strings can concatenate using 'operator+'")
    {
        constexpr auto source = R"(function test() { "a" + "b"; })";
        REQUIRE(typeCheck(diag, source));
    }
    SECTION("invalid operands of types 'string' and 'string' to binary 'operator*'")
    {
        constexpr auto source = R"(function test() { "a" * "b"; })";
        REQUIRE(!typeCheck(diag, source));
        REQUIRE(stream->hasError(
            "1:19: error: invalid operands to binary expression ('string' and 'string')."));
    }
    SECTION("invalid operands of types 'string' and 'string' to binary 'operator-'")
    {
        constexpr auto source = R"(function test() { "a" - "b"; })";
        REQUIRE(!typeCheck(diag, source));
        REQUIRE(stream->hasError(
            "1:19: error: invalid operands to binary expression ('string' and 'string')."));
    }
}
