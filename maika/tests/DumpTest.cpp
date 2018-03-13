#include "AST/ASTContext.h"
#include "AST/ASTDumper.h"
#include "Basic/Diagnostic.h"
#include "Driver/Driver.h"
#include "Sema/Entity.h"
#include "Sema/IdentifierResolver.h"
#include "Sema/TypeInferer.h"
#include "Sema/TypeResolver.h"
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

    auto diag = std::make_shared<DiagnosticHandler>();

    MyDriver driver;
    auto [astContext, ok] = driver.parseString(source, diag);
    REQUIRE(ok);

    ASTDumper dumper;
    ASTTraverser traverser;
    traverser.traverse(astContext, dumper);
    REQUIRE(!diag->hasError());

    REQUIRE(dumper.getResult() == expect);
}

TEST_CASE("TypeInfer", "[type-inference]")
{
    constexpr auto source = R"(
function sub(a, b) {
    if (a) {
        return --b;
    }
    return a - b;
}

function main() {
    let a = 42;
    let b = 70;
    let c = 3.14 * (a + b);
    let d = 2.71828;
    let x = sub(a, b);
    let y = sub(c, d);
    let z = sub;
    let w = z(a, b);
    let v = function(m, n) {
        if (m == n) {
            return "temp";
        }
        return "abc";
    };
    let t = v(4, 5);
    return !(x == y);
}
)";
    auto diag = std::make_shared<DiagnosticHandler>();

    MyDriver driver;
    auto [astContext, ok] = driver.parseString(source, diag);
    REQUIRE(ok);

    ASTTraverser traverser;
    IdentifierContext context;

    IdentifierResolver resolver(&context, diag);
    traverser.traverse(astContext, resolver);
    REQUIRE(!diag->hasError());

    TypeResolver typeResolver(diag);
    traverser.traverse(astContext, typeResolver);
    REQUIRE(!diag->hasError());

    ASTDumper dumper;
    traverser.traverse(astContext, dumper);
    REQUIRE(!diag->hasError());
    // printf("%s\n", dumper.getResult().c_str());
}
