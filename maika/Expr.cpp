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
    assert(namedDecl);
    visitor.visit(this);
    namedDecl->traverse(visitor);
    for (const auto& arg : arguments) {
        arg->traverse(visitor);
    }
}

std::string CallExpr::dump(ASTDumper& dumper) const
{
    assert(namedDecl);
    std::string s = "(" + namedDecl->getName();
    for (const auto& arg : arguments) {
        s += " ";
        s += arg->dump(dumper);
    }
    s += ")";
    return s;
}

std::shared_ptr<CallExpr> CallExpr::make(
    const std::shared_ptr<NamedDecl>& n,
    const std::vector<std::shared_ptr<Expr>>& a)
{
    auto expr = std::make_shared<CallExpr>();
    expr->namedDecl = n;
    expr->arguments = a;
    return expr;
}

void AssignmentOperator::traverse(ASTVisitor& visitor)
{
    assert(lhs);
    assert(rhs);
    lhs->traverse(visitor);
    rhs->traverse(visitor);
}

std::string AssignmentOperator::dump(ASTDumper& dumper) const
{
    assert(lhs);
    assert(rhs);
    std::string s = "(= " + lhs->dump(dumper) + " " + rhs->dump(dumper) + ")";
    return s;
}

std::shared_ptr<AssignmentOperator> AssignmentOperator::make(
    const std::shared_ptr<NamedDecl>& l,
    const std::shared_ptr<Expr>& r)
{
    auto expr = std::make_shared<AssignmentOperator>();
    expr->lhs = l;
    expr->rhs = r;
    return expr;
}

void BinaryOperator::traverse(ASTVisitor& visitor)
{
    assert(lhs);
    assert(rhs);
    lhs->traverse(visitor);
    rhs->traverse(visitor);
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
        }
    }();
    std::string s = "(" + k + " " + lhs->dump(dumper) + " " + rhs->dump(dumper) + ")";
    return s;
}

std::shared_ptr<BinaryOperator> BinaryOperator::make(
    BinaryOperatorKind k,
    const std::shared_ptr<Expr>& l,
    const std::shared_ptr<Expr>& r)
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
    decl->traverse(visitor);
}

std::string DeclRefExpr::dump(ASTDumper& dumper) const
{
    assert(decl);
    return decl->dump(dumper);
}

std::shared_ptr<DeclRefExpr> DeclRefExpr::make(const std::shared_ptr<Decl>& d)
{
    auto expr = std::make_shared<DeclRefExpr>();
    expr->decl = d;
    return expr;
}
