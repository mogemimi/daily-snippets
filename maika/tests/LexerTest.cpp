#include "ASTContext.h"
#include "ASTDumper.h"
#include "Entity.h"
#include "MyDriver.h"
#include <iostream>
#include <sstream>

#include "catch.hpp"

TEST_CASE("Lexer", "[lexer]")
{
    constexpr auto source = R"(
function min() {
    if ((x % a().b.c) || z != w) {
    }
}
)";

    MyDriver driver;
    auto [astContext, ok] = driver.parseString(source);
    REQUIRE(ok);

    {
        ASTDumper dumper;
        ASTTraverser traverser;
        traverser.traverse(astContext, dumper);
        printf("%s\n", dumper.getResult().c_str());
    }
}
