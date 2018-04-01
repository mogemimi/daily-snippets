#include "AST/ASTContext.h"
#include "AST/ASTDumper.h"
#include "Basic/Diagnostic.h"
#include "Driver/Driver.h"
#include "Sema/Entity.h"
#include "Sema/IdentifierResolver.h"

#include "catch.hpp"

namespace {
bool resolveIdentifiers(const std::shared_ptr<DiagnosticHandler>& diag, const std::string& source)
{
    MyDriver driver;
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

    SECTION("redeclared in this block.") {
        constexpr auto source = R"(function test() {
            let x;
            let x;
        })";
        REQUIRE(!resolveIdentifiers(diag, source));
        REQUIRE(stream->hasError("3:17: error: 'x' redeclared in this block."));
    }
}
