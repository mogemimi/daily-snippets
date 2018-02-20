#include "Stmt.h"
#include "ASTVisitor.h"
#include "ASTDumper.h"
#include "Expr.h"
#include <cassert>
#include <utility>

void CompoundStmt::traverse(ASTVisitor& visitor)
{
    for (const auto& statement : statements) {
        assert(statement);
        statement->traverse(visitor);
    }
}

std::string CompoundStmt::dump(ASTDumper& dumper) const
{
    std::string s = "(";
    if (!statements.empty() && dumper.isMultiLine()) {
        s += "\n";
    }
    const auto oldIndent = dumper.GetIndent();
    dumper.SetIndent(oldIndent + "  ");
    bool needToSpace = false;
    for (const auto& statement : statements) {
        assert(statement);
        if (needToSpace) {
            if (dumper.isMultiLine()) {
                s += "\n";
            }
            else {
                s += " ";
            }
        }
        auto d = statement->dump(dumper);
        assert(!d.empty());
        s += dumper.GetIndent();
        s += d;
        needToSpace = true;
    }
    dumper.SetIndent(oldIndent);
    if (dumper.isMultiLine()) {
        s += "\n";
    }
    s += ")";
    return s;
}

std::shared_ptr<CompoundStmt> CompoundStmt::make(
    const std::vector<std::shared_ptr<Stmt>>& s)
{
    auto stmt = std::make_shared<CompoundStmt>();
    stmt->statements = s;
    return stmt;
}

void ReturnStmt::traverse(ASTVisitor& visitor)
{
    assert(expr);
    expr->traverse(visitor);
}

std::string ReturnStmt::dump(ASTDumper& dumper) const
{
    std::string s = "(return";
    if (expr) {
        s += " ";
        s += expr->dump(dumper);
    }
    s += ")";
    return s;
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