#include "ASTContext.h"
#include "ASTDumper.h"
#include "Diagnostic.h"
#include "Entity.h"
#include "Formatter.h"
#include "MyDriver.h"
#include <iostream>
#include <sstream>

#include "catch.hpp"

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
