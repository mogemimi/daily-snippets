#include "Expr.h"
#include "ASTDumper.h"
#include "ASTVisitor.h"
#include "Decl.h"
#include <cassert>
#include <utility>

std::shared_ptr<Type> Expr::getType() const
{
    return type;
}

void Expr::setType(const std::shared_ptr<Type>& t)
{
    assert(t);
    type = t;
}

yy::location Expr::getLocation() const
{
    return location;
}

void IntegerLiteral::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this());
}

std::string IntegerLiteral::dump(ASTDumper&) const
{
    return std::to_string(value);
}

std::shared_ptr<IntegerLiteral> IntegerLiteral::make(const yy::location& loc, int64_t v)
{
    auto expr = std::make_shared<IntegerLiteral>();
    expr->location = loc;
    expr->value = v;
    return expr;
}

void DoubleLiteral::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this());
}

std::string DoubleLiteral::dump(ASTDumper&) const
{
    return std::to_string(value);
}

std::shared_ptr<DoubleLiteral> DoubleLiteral::make(const yy::location& loc, double v)
{
    auto expr = std::make_shared<DoubleLiteral>();
    expr->location = loc;
    expr->value = v;
    return expr;
}

void BoolLiteral::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this());
}

std::string BoolLiteral::dump(ASTDumper&) const
{
    return value ? "true" : "false";
}

std::shared_ptr<BoolLiteral> BoolLiteral::make(const yy::location& loc, bool v)
{
    auto expr = std::make_shared<BoolLiteral>();
    expr->location = loc;
    expr->value = v;
    return expr;
}

void CallExpr::traverse(ASTVisitor& visitor)
{
    assert(callee);
    visitor.visit(shared_from_this(), [&] {
        callee->traverse(visitor);
        for (const auto& arg : arguments) {
            arg->traverse(visitor);
        }
    });
}

std::string CallExpr::dump(ASTDumper& dumper) const
{
    assert(callee);
    std::string s = "(" + callee->dump(dumper);
    for (const auto& arg : arguments) {
        s += " ";
        s += arg->dump(dumper);
    }
    s += ")";
    return s;
}

std::shared_ptr<CallExpr> CallExpr::make(
    const yy::location& loc,
    const std::shared_ptr<Expr>& fn,
    const std::vector<std::shared_ptr<Expr>>& args)
{
    auto expr = std::make_shared<CallExpr>();
    expr->location = loc;
    expr->callee = fn;
    expr->arguments = args;
    return expr;
}

void BinaryOperator::traverse(ASTVisitor& visitor)
{
    assert(lhs);
    assert(rhs);
    visitor.visit(shared_from_this(), [&] {
        lhs->traverse(visitor);
        rhs->traverse(visitor);
    });
}

std::string BinaryOperator::dump(ASTDumper& dumper) const
{
    assert(lhs);
    assert(rhs);
    auto k = [&]() -> std::string {
        switch (kind) {
        case BinaryOperatorKind::Add: return "+";
        case BinaryOperatorKind::Subtract: return "-";
        case BinaryOperatorKind::Multiply: return "*";
        case BinaryOperatorKind::Divide: return "/";
        case BinaryOperatorKind::Assign: return "=";
        case BinaryOperatorKind::Equal: return "==";
        case BinaryOperatorKind::NotEqual: return "!=";
        case BinaryOperatorKind::LogicalAnd: return "&&";
        case BinaryOperatorKind::LogicalOr: return "||";
        }
        return "<unknown>";
    }();
    std::string s = "(" + k + " " + lhs->dump(dumper) + " " + rhs->dump(dumper) + ")";
    return s;
}

std::shared_ptr<BinaryOperator> BinaryOperator::make(
    const yy::location& loc,
    BinaryOperatorKind k,
    const std::shared_ptr<Expr>& l,
    const std::shared_ptr<Expr>& r)
{
    auto expr = std::make_shared<BinaryOperator>();
    expr->location = loc;
    expr->kind = k;
    expr->lhs = l;
    expr->rhs = r;
    return expr;
}

void DeclRefExpr::traverse(ASTVisitor& visitor)
{
    assert(decl);
    visitor.visit(shared_from_this(), [&] { decl->traverse(visitor); });
}

std::string DeclRefExpr::dump(ASTDumper& dumper) const
{
    assert(decl);
    return decl->dump(dumper);
}

std::shared_ptr<DeclRefExpr>
DeclRefExpr::make(const yy::location& loc, const std::shared_ptr<NamedDecl>& d)
{
    auto expr = std::make_shared<DeclRefExpr>();
    expr->location = loc;
    expr->decl = d;
    return expr;
}
