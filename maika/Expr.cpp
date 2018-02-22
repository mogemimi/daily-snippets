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
    assert(!type);
    assert(t);
    type = t;
}

void IntegerLiteral::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this());
}

std::string IntegerLiteral::dump(ASTDumper&) const
{
    return std::to_string(value);
}

std::shared_ptr<IntegerLiteral> IntegerLiteral::make(int64_t v)
{
    auto decl = std::make_shared<IntegerLiteral>();
    decl->value = v;
    decl->setType(BuiltinType::make(BuiltinTypeKind::Int));
    return decl;
}

void DoubleLiteral::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this());
}

std::string DoubleLiteral::dump(ASTDumper&) const
{
    return std::to_string(value);
}

std::shared_ptr<DoubleLiteral> DoubleLiteral::make(double v)
{
    auto decl = std::make_shared<DoubleLiteral>();
    decl->value = v;
    decl->setType(BuiltinType::make(BuiltinTypeKind::Double));
    return decl;
}

void BoolLiteral::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this());
}

std::string BoolLiteral::dump(ASTDumper&) const
{
    return value ? "true" : "false";
}

std::shared_ptr<BoolLiteral> BoolLiteral::make(bool v)
{
    auto decl = std::make_shared<BoolLiteral>();
    decl->value = v;
    decl->setType(BuiltinType::make(BuiltinTypeKind::Bool));
    return decl;
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

std::shared_ptr<CallExpr>
CallExpr::make(const std::shared_ptr<Expr>& fn, const std::vector<std::shared_ptr<Expr>>& args)
{
    auto expr = std::make_shared<CallExpr>();
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
    }();
    std::string s = "(" + k + " " + lhs->dump(dumper) + " " + rhs->dump(dumper) + ")";
    return s;
}

std::shared_ptr<BinaryOperator> BinaryOperator::make(
    BinaryOperatorKind k, const std::shared_ptr<Expr>& l, const std::shared_ptr<Expr>& r)
{
    auto expr = std::make_shared<BinaryOperator>();
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

std::shared_ptr<DeclRefExpr> DeclRefExpr::make(const std::shared_ptr<NamedDecl>& d)
{
    auto expr = std::make_shared<DeclRefExpr>();
    expr->decl = d;
    return expr;
}
