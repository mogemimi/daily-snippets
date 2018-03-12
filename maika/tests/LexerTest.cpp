#include "ASTContext.h"
#include "ASTDumper.h"
#include "Diagnostic.h"
#include "Entity.h"
#include "MyDriver.h"
#include <iostream>
#include <sstream>

#include "catch.hpp"

TEST_CASE("Lexer", "[lexer]")
{
    constexpr auto source = R"(
function min(a : int, b : int) : int {
    if (a < b) {
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
    printf("%s\n", dumper.getResult().c_str());
}
