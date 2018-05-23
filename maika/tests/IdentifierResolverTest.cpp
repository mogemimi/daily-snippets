#include "Sema/IdentifierResolver.h"
#include "AST/ASTContext.h"
#include "AST/ASTDumper.h"
#include "Basic/Diagnostic.h"
#include "Driver/Driver.h"
#include "Sema/Entity.h"

#include "catch.hpp"

namespace {
bool resolveIdentifiers(const std::shared_ptr<DiagnosticHandler>& diag, const std::string& source)
{
    Driver driver;
    auto [astContext, ok] = driver.parseString(source, diag);
    REQUIRE(ok);

    ASTTraverser traverser;
    IdentifierContext context;

    IdentifierResolver resolver(&context, diag);
    traverser.traverse(astContext, resolver);
    return !diag->hasError();
}
} // end of anonymous namespace

TEST_CASE("IdentifierResolver can resolve identifier", "[identifier-resolve]")
{
    auto stream = std::make_shared<UnitTestDiagnosticStream>();
    auto diag = std::make_shared<DiagnosticHandler>();
    diag->setStream(stream);

    SECTION("redeclared in this block.")
    {
        constexpr auto source = R"(func f() {
            let x;
            let x;
        })";
        REQUIRE(!resolveIdentifiers(diag, source));
        REQUIRE(stream->hasError("error: 'x' redeclared in this block."));
    }
    SECTION("resolver emits an undefined identifier when using unknown symbols")
    {
        constexpr auto source = R"(func f() {
            x = 42;
        })";
        REQUIRE(!resolveIdentifiers(diag, source));
        REQUIRE(stream->hasError("error: 'x' was not declared in this scope."));
    }
    SECTION("resolver emits an undefined identifier when calling unknown function")
    {
        constexpr auto source = R"(
        func f() { g(); }
        )";
        REQUIRE(!resolveIdentifiers(diag, source));
        REQUIRE(stream->hasError("error: 'g' was not declared in this scope."));
    }
    SECTION("resolving function name")
    {
        constexpr auto source = R"(
        func g() { }
        func f() { g(); }
        )";
        REQUIRE(resolveIdentifiers(diag, source));
    }
}
