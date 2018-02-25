#include "ASTContext.h"
#include "ASTDumper2.h"
#include "Entity.h"
#include "IdentifierResolver.h"
#include "MyDriver.h"
#include "TypeResolver.h"
#include <iostream>
#include <sstream>

#include "catch.hpp"

TEST_CASE("ASTDump", "[ast-dump]")
{
    constexpr auto source = R"(
function mul(a: int, b: int) {
    return a * b;
}

function main() {
    let a = 95 / 4;
    let b = 3.141592;
    let c = mul(a + a, b);
    let d = true;
    let e = (d != false);
    return (c + 4) * (a - 75);
}
)";

    constexpr auto expect = R"(TranslationUnitDecl
  FunctionDecl 'mul'
    ParmVarDecl 'a' 'int'
    ParmVarDecl 'b' 'int'
    CompoundStmt
      ReturnStmt
        BinaryOperator '*'
          DeclRefExpr 'a'
          DeclRefExpr 'b'
  FunctionDecl 'main'
    CompoundStmt
      DeclStmt
        VariableDecl 'a'
          BinaryOperator '/'
            IntegerLiteral '95'
            IntegerLiteral '4'
      DeclStmt
        VariableDecl 'b'
          DoubleLiteral '3.141592'
      DeclStmt
        VariableDecl 'c'
          CallExpr
            DeclRefExpr 'mul'
            BinaryOperator '+'
              DeclRefExpr 'a'
              DeclRefExpr 'a'
            DeclRefExpr 'b'
      DeclStmt
        VariableDecl 'd'
          BoolLiteral 'true'
      DeclStmt
        VariableDecl 'e'
          BinaryOperator '!='
            DeclRefExpr 'd'
            BoolLiteral 'false'
      ReturnStmt
        BinaryOperator '*'
          BinaryOperator '+'
            DeclRefExpr 'c'
            IntegerLiteral '4'
          BinaryOperator '-'
            DeclRefExpr 'a'
            IntegerLiteral '75'
)";

    MyDriver driver;
    auto [astContext, ok] = driver.parseString(source);
    REQUIRE(ok);

    ASTDumper2 dumper;
    ASTTraverser traverser;
    traverser.traverse(astContext, dumper);

    REQUIRE(dumper.result == expect);
}

TEST_CASE("TypeInfer", "[type-inference]")
{
    constexpr auto source = R"(
function sub(a, b) {
    return a - b;
}

function main() {
    let a = sub(42, 7);
//    let a = 42;
//    let b = 70;
//    let c = a + b;
//    let d = 2.71828;
//    let x = sub(a, b);
//    let y = sub(c, d);
//    let z = sub;
//    let w = z(a, b);
//    return x == y;
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

    TypeResolver typeResolver;
    {
        ASTTraverser traverser;
        traverser.traverse(astContext, typeResolver);
    }

    ASTDumper2 dumper;
    {
        ASTTraverser traverser;
        traverser.traverse(astContext, dumper);
        printf("%s\n", dumper.result.c_str());
    }
}
