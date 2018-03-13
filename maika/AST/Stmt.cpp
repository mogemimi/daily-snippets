#include "AST/Stmt.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "ASTDumper.h"
#include "ASTVisitor.h"
#include <cassert>
#include <utility>

void CompoundStmt::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this(), [&] {
        for (const auto& statement : statements) {
            assert(statement);
            statement->traverse(visitor);
        }
    });
}

std::shared_ptr<CompoundStmt> CompoundStmt::make(const std::vector<std::shared_ptr<Stmt>>& s)
{
    auto stmt = std::make_shared<CompoundStmt>();
    stmt->statements = s;
    return stmt;
}

void DeclStmt::traverse(ASTVisitor& visitor)
{
    assert(decl);

    visitor.visit(shared_from_this(), [&] { decl->traverse(visitor); });
}

std::shared_ptr<DeclStmt> DeclStmt::make(const std::shared_ptr<Decl>& d)
{
    auto expr = std::make_shared<DeclStmt>();
    expr->decl = d;
    return expr;
}

void ReturnStmt::traverse(ASTVisitor& visitor)
{
    assert(expr);
    visitor.visit(shared_from_this(), [&] { expr->traverse(visitor); });
}

std::shared_ptr<Expr> ReturnStmt::getExpr() const
{
    return expr;
}

std::shared_ptr<ReturnStmt> ReturnStmt::make()
{
    auto stmt = std::make_shared<ReturnStmt>();
    return stmt;
}

std::shared_ptr<ReturnStmt> ReturnStmt::make(const std::shared_ptr<Expr>& e)
{
    auto stmt = std::make_shared<ReturnStmt>();
    stmt->expr = e;
    return stmt;
}

void IfStmt::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this(), [&] {
        if (condExpr) {
            condExpr->traverse(visitor);
        }
        if (thenStmt) {
            thenStmt->traverse(visitor);
        }
        if (elseStmt) {
            elseStmt->traverse(visitor);
        }
    });
}

std::shared_ptr<Expr> IfStmt::getCond() const
{
    return condExpr;
}

std::shared_ptr<Stmt> IfStmt::getThen() const
{
    return thenStmt;
}

std::shared_ptr<Stmt> IfStmt::getElse() const
{
    return elseStmt;
}

std::shared_ptr<IfStmt>
IfStmt::make(const std::shared_ptr<Expr>& condExpr, const std::shared_ptr<Stmt>& thenStmt)
{
    auto stmt = std::make_shared<IfStmt>();
    stmt->condExpr = condExpr;
    stmt->thenStmt = thenStmt;
    return stmt;
}

std::shared_ptr<IfStmt> IfStmt::make(
    const std::shared_ptr<Expr>& condExpr,
    const std::shared_ptr<Stmt>& thenStmt,
    const std::shared_ptr<Stmt>& elseStmt)
{
    auto stmt = std::make_shared<IfStmt>();
    stmt->condExpr = condExpr;
    stmt->thenStmt = thenStmt;
    stmt->elseStmt = elseStmt;
    return stmt;
}

void WhileStmt::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this(), [&] {
        if (condExpr) {
            condExpr->traverse(visitor);
        }
        if (bodyStmt) {
            bodyStmt->traverse(visitor);
        }
    });
}

std::shared_ptr<Expr> WhileStmt::getCond() const
{
    return condExpr;
}

std::shared_ptr<Stmt> WhileStmt::getBody() const
{
    return bodyStmt;
}

std::shared_ptr<WhileStmt>
WhileStmt::make(const std::shared_ptr<Expr>& condExpr, const std::shared_ptr<Stmt>& bodyStmt)
{
    auto stmt = std::make_shared<WhileStmt>();
    stmt->condExpr = condExpr;
    stmt->bodyStmt = bodyStmt;
    return stmt;
}

void ForStmt::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this(), [&] {
        if (initStmt) {
            initStmt->traverse(visitor);
        }
        if (condExpr) {
            condExpr->traverse(visitor);
        }
        if (incExpr) {
            incExpr->traverse(visitor);
        }
        if (bodyStmt) {
            bodyStmt->traverse(visitor);
        }
    });
}

std::shared_ptr<Stmt> ForStmt::getInit() const
{
    return initStmt;
}

std::shared_ptr<Expr> ForStmt::getCond() const
{
    return condExpr;
}

std::shared_ptr<Expr> ForStmt::getInc() const
{
    return incExpr;
}

std::shared_ptr<Stmt> ForStmt::getBody() const
{
    return bodyStmt;
}

std::shared_ptr<ForStmt> ForStmt::make(
    const std::shared_ptr<Stmt>& initStmt,
    const std::shared_ptr<Expr>& condExpr,
    const std::shared_ptr<Expr>& incExpr,
    const std::shared_ptr<Stmt>& bodyStmt)
{
    auto stmt = std::make_shared<ForStmt>();
    stmt->initStmt = initStmt;
    stmt->condExpr = condExpr;
    stmt->incExpr = incExpr;
    stmt->bodyStmt = bodyStmt;
    return stmt;
}
