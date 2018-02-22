#include "AST.h"
#include "Entity.h"
#include "IdentifierResolver.h"
#include "MyDriver.h"
#include "TypeResolver.h"
#include <iostream>
#include <sstream>

#include "catch.hpp"

TEST_CASE("Dump", "[dump-test]")
{
	constexpr auto source = R"(
function mul(a: int, b: int) {
    return a * b;
}

function main() {
    // NOTE:
    let a = 95 / 4;
    let b = 3.1415926535;
    let c = mul(a + a, b);
    let d = (a) = c;
    return (c + 4) * (a - 75);
}
)";

	constexpr auto sExpression = R"((function mul ((a int) (b int)) (
  (return (* a b))
))
(function main () (
  (let a (/ 95 4))
  (let b 3.141593)
  (let c (mul (+ a a) b))
  (let d (= a c))
  (return (* (+ c 4) (- a 75)))
)))";
    MyDriver driver;

    auto [result, ok] = driver.parseString(source);
	REQUIRE(ok);

    IdentifierContext context;
    {
        IdentifierResolver resolver(&context);
        ASTTraverser traverser;
        traverser.traverse(driver.ast, resolver);
    }

    TypeResolver typeResolver;
    {
        ASTTraverser traverser;
        traverser.traverse(driver.ast, typeResolver);
    }

    REQUIRE(result == sExpression);
}
