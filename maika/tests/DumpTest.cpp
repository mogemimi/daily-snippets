#include "ASTContext.h"
#include "ASTDumper2.h"
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
    REQUIRE(result.dump() == sExpression);

    // ASTDumper2 dumper;
    //{
    //    ASTTraverser traverser;
    //    traverser.traverse(driver.ast, dumper);
    //    printf("%s\n", dumper.result.c_str());
    //}
}

TEST_CASE("TypeInfer", "[type-inference]")
{
    constexpr auto source = R"(
function sub(a : int, b : int) {
	return a - b;
}

function main() {
	let a = (4 + 5) - 7;
	let b = 3.0 + (4.2 - (a * a));
	let c = 5.0 * (b = a);
	let d = true;
	let e = (c == a);
	let x;
	let y = x;
	let z = sub(b, c);
    return ((a * b) != c);
}
)";
    MyDriver driver;

    auto [astContext, ok] = driver.parseString(source);
    REQUIRE(ok);

    IdentifierContext context;
    {
        IdentifierResolver resolver(&context);
        ASTTraverser traverser;
        traverser.traverse(astContext, resolver);
    }

    // NOTE: type inference unification
    for (const auto& e : context.entities) {
        auto decl = e->getDecl();
        decl->setType(TypeVariable::make());
    }

    TypeResolver typeResolver;
    {
        ASTTraverser traverser;
        traverser.traverse(astContext, typeResolver);
    }

    for (const auto& e : context.entities) {
        auto name = e->getName();
        auto type = e->getDecl()->getType()->dump();
        auto line = e->getDecl()->getLocation().begin.line;
        printf("%8s %20s (at line %d)\n", name.c_str(), ("[" + type + "]").c_str(), line);
    }
}
