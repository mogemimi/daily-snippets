#include "CodeGen/IRGenerator.h"
#include "AST/ASTContext.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Stmt.h"
#include "AST/Type.h"
#include "Sema/Entity.h"
#include <cassert>
#include <sstream>
#include <utility>

namespace {

} // end of anonymous namespace

void IRGenerator::visit(const std::shared_ptr<CompoundStmt>& stmt, Invoke&& traverse)
{
    traverse();
    printf("[%s]\n", "CompoundStmt");
}

void IRGenerator::visit(const std::shared_ptr<DeclStmt>& stmt, Invoke&& traverse)
{
    traverse();
    printf("[%s]\n", "DeclStmt");
}

void IRGenerator::visit(const std::shared_ptr<ReturnStmt>& stmt, Invoke&& traverse)
{
    traverse();
    printf("[%s]\n", "ReturnStmt");
}

void IRGenerator::visit(const std::shared_ptr<IfStmt>& stmt, Invoke&& traverse)
{
    traverse();
    printf("[%s]\n", "IfStmt");
}

void IRGenerator::visit(const std::shared_ptr<WhileStmt>& stmt, Invoke&& traverse)
{
    traverse();
    printf("[%s]\n", "WhileStmt");
}

void IRGenerator::visit(const std::shared_ptr<ForStmt>& stmt, Invoke&& traverse)
{
    traverse();
    printf("[%s]\n", "ForStmt");
}

void IRGenerator::visit(const std::shared_ptr<CallExpr>& expr, Invoke&& traverse)
{
    traverse();
    printf("[%s]\n", "CallExpr");
}

void IRGenerator::visit(const std::shared_ptr<FunctionExpr>& expr, Invoke&& traverse)
{
    traverse();
    printf("[%s]\n", "FunctionExpr");
}

void IRGenerator::visit(const std::shared_ptr<IntegerLiteral>& expr)
{
    printf("%s %d [%s]\n", "int", static_cast<int>(expr->getValue()), "IntegerLiteral");
}

void IRGenerator::visit(const std::shared_ptr<DoubleLiteral>& expr)
{
    printf("%s %lf [%s]\n", "double", expr->getValue(), "DoubleLiteral");
}

void IRGenerator::visit(const std::shared_ptr<BoolLiteral>& expr)
{
    printf("%s %s [%s]\n", "bool", expr->getValue() ? "true" : "false", "BoolLiteral");
}

void IRGenerator::visit(const std::shared_ptr<StringLiteral>& expr)
{
    printf("[%s]\n", "StringLiteral");
}

void IRGenerator::visit(const std::shared_ptr<BinaryOperator>& expr, Invoke&& traverse)
{
    traverse();
    auto op = ASTHelper::toString(expr->getKind());
    printf("%s %s [%s]\n", "bin-op", op.c_str(), "BinaryOperator");
}

void IRGenerator::visit(const std::shared_ptr<UnaryOperator>& expr, Invoke&& traverse)
{
    traverse();
    printf("[%s]\n", "UnaryOperator");
}

void IRGenerator::visit(const std::shared_ptr<DeclRefExpr>& expr, Invoke&& traverse)
{
    traverse();
    printf("%s %s [%s]\n", "load", expr->getNamedDecl()->getName().c_str(), "DeclRefExpr");
}

void IRGenerator::visit(const std::shared_ptr<MemberExpr>& expr, Invoke&& traverse)
{
    traverse();
    printf("[%s]\n", "MemberExpr");
}

void IRGenerator::visit(const std::shared_ptr<TranslationUnitDecl>& decl, Invoke&& traverse)
{
    traverse();
    printf("[%s]\n", "TranslationUnitDecl");
}

void IRGenerator::visit(const std::shared_ptr<FunctionDecl>& decl, Invoke&& traverse)
{
    traverse();
    printf("[%s]\n", "FunctionDecl");
}

void IRGenerator::visit(const std::shared_ptr<VariableDecl>& decl, Invoke&& traverse)
{
    traverse();
    printf("[%s]\n", "VariableDecl");
}

void IRGenerator::visit(const std::shared_ptr<ConstDecl>& decl, Invoke&& traverse)
{
    traverse();
    printf("[%s]\n", "ConstDecl");
}
