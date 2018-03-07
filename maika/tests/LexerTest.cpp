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
function main() {
    let a = 1;
    let b = -3.46969e+15;
    let c = "a\n\"aaa";
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
