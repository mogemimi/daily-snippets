#include "AST/Expr.h"
#include "AST/ASTDumper.h"
#include "AST/ASTVisitor.h"
#include "AST/Decl.h"
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

void IntegerLiteral::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this());
}

std::shared_ptr<IntegerLiteral> IntegerLiteral::make(const Location& loc, int64_t v)
{
    auto expr = std::make_shared<IntegerLiteral>();
    expr->location = loc;
    expr->valueKind = ExprValueKind::RValue;
    expr->value = v;
    return expr;
}

void DoubleLiteral::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this());
}

std::shared_ptr<DoubleLiteral> DoubleLiteral::make(const Location& loc, double v)
{
    auto expr = std::make_shared<DoubleLiteral>();
    expr->location = loc;
    expr->valueKind = ExprValueKind::RValue;
    expr->value = v;
    return expr;
}

void BoolLiteral::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this());
}

std::shared_ptr<BoolLiteral> BoolLiteral::make(const Location& loc, bool v)
{
    auto expr = std::make_shared<BoolLiteral>();
    expr->location = loc;
    expr->valueKind = ExprValueKind::RValue;
    expr->value = v;
    return expr;
}

void StringLiteral::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this());
}

std::shared_ptr<StringLiteral> StringLiteral::make(const Location& loc, const std::string& v)
{
    auto expr = std::make_shared<StringLiteral>();
    expr->location = loc;
    expr->valueKind = ExprValueKind::RValue;
    expr->value = v;
    return expr;
}

void NullLiteral::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this());
}

std::shared_ptr<NullLiteral> NullLiteral::make(const Location& loc)
{
    auto expr = std::make_shared<NullLiteral>();
    expr->location = loc;
    expr->valueKind = ExprValueKind::RValue;
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

std::shared_ptr<CallExpr> CallExpr::make(
    const Location& loc,
    const std::shared_ptr<Expr>& fn,
    const std::vector<std::shared_ptr<Expr>>& args)
{
    auto expr = std::make_shared<CallExpr>();
    expr->location = loc;
    expr->valueKind = ExprValueKind::RValue;
    expr->callee = fn;
    expr->arguments = args;
    return expr;
}

void FunctionExpr::traverse(ASTVisitor& visitor)
{
    assert(compoundStmt);
    visitor.visit(shared_from_this(), [&] {
        if (namedDecl) {
            namedDecl->traverse(visitor);
        }
        for (const auto& param : parameters) {
            param->traverse(visitor);
        }
        compoundStmt->traverse(visitor);
    });
}

std::shared_ptr<NamedDecl> FunctionExpr::getNamedDecl() const
{
    return namedDecl;
}

const std::vector<std::shared_ptr<ParmVarDecl>>& FunctionExpr::getParameters() const
{
    return parameters;
}

std::shared_ptr<NamedDecl> FunctionExpr::getReturnType() const
{
    return returnType;
}

std::shared_ptr<CompoundStmt> FunctionExpr::getBody() const
{
    return compoundStmt;
}

std::shared_ptr<FunctionExpr> FunctionExpr::make(
    const Location& loc,
    const std::shared_ptr<NamedDecl>& n,
    const std::vector<std::shared_ptr<ParmVarDecl>>& parameters,
    const std::shared_ptr<NamedDecl>& returnType,
    const std::shared_ptr<CompoundStmt>& s)
{
    auto expr = std::make_shared<FunctionExpr>();
    expr->location = loc;
    expr->valueKind = ExprValueKind::RValue;
    expr->namedDecl = n;
    expr->parameters = parameters;
    expr->returnType = returnType;
    expr->compoundStmt = s;
    return expr;
}

void BinaryOperator::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this(), [&] {
        assert(lhs);
        assert(rhs);
        lhs->traverse(visitor);
        rhs->traverse(visitor);
    });
}

bool BinaryOperator::isMultiplicativeOp(BinaryOperatorKind kind)
{
    switch (kind) {
    case BinaryOperatorKind::Multiply: return true;
    case BinaryOperatorKind::Divide: return true;
    case BinaryOperatorKind::Mod: return true;
    default: break;
    }
    return false;
}

bool BinaryOperator::isMultiplicativeOp() const
{
    return isMultiplicativeOp(kind);
}

bool BinaryOperator::isAdditiveOp(BinaryOperatorKind kind)
{
    return (kind == BinaryOperatorKind::Add) || (kind == BinaryOperatorKind::Subtract);
}

bool BinaryOperator::isAdditiveOp() const
{
    return isAdditiveOp(kind);
}

bool BinaryOperator::isEqualityOp(BinaryOperatorKind kind)
{
    return (kind == BinaryOperatorKind::Equal) || (kind == BinaryOperatorKind::NotEqual);
}

bool BinaryOperator::isEqualityOp() const
{
    return isEqualityOp(kind);
}

bool BinaryOperator::isComparisonOp(BinaryOperatorKind kind)
{
    switch (kind) {
    case BinaryOperatorKind::GreaterThan: return true;
    case BinaryOperatorKind::GreaterThanOrEqual: return true;
    case BinaryOperatorKind::LessThan: return true;
    case BinaryOperatorKind::LessThanOrEqual: return true;
    default: break;
    }
    return false;
}

bool BinaryOperator::isComparisonOp() const
{
    return isComparisonOp(kind);
}

bool BinaryOperator::isLogicalOp(BinaryOperatorKind kind)
{
    return (kind == BinaryOperatorKind::LogicalAnd) || (kind == BinaryOperatorKind::LogicalOr);
}

bool BinaryOperator::isLogicalOp() const
{
    return isLogicalOp(kind);
}

bool BinaryOperator::isAssignmentOp(BinaryOperatorKind kind)
{
    return kind == BinaryOperatorKind::Assign;
}

bool BinaryOperator::isAssignmentOp() const
{
    return isAssignmentOp(kind);
}

std::shared_ptr<BinaryOperator> BinaryOperator::make(
    const Location& loc,
    BinaryOperatorKind k,
    const std::shared_ptr<Expr>& l,
    const std::shared_ptr<Expr>& r)
{
    auto expr = std::make_shared<BinaryOperator>();
    expr->location = loc;
    expr->valueKind = ExprValueKind::RValue;
    expr->kind = k;
    expr->lhs = l;
    expr->rhs = r;
    return expr;
}

std::string BinaryOperator::toString(BinaryOperatorKind kind)
{
    switch (kind) {
    case BinaryOperatorKind::Assign: return "=";
    case BinaryOperatorKind::Add: return "+";
    case BinaryOperatorKind::Subtract: return "-";
    case BinaryOperatorKind::Divide: return "/";
    case BinaryOperatorKind::Multiply: return "*";
    case BinaryOperatorKind::Mod: return "%";
    case BinaryOperatorKind::Equal: return "==";
    case BinaryOperatorKind::NotEqual: return "!=";
    case BinaryOperatorKind::LogicalAnd: return "&&";
    case BinaryOperatorKind::LogicalOr: return "||";
    case BinaryOperatorKind::GreaterThan: return ">";
    case BinaryOperatorKind::GreaterThanOrEqual: return ">=";
    case BinaryOperatorKind::LessThan: return "<";
    case BinaryOperatorKind::LessThanOrEqual: return "<=";
    }
    return "<unknown>";
}

void UnaryOperator::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this(), [&] {
        assert(subExpr);
        subExpr->traverse(visitor);
    });
}

std::shared_ptr<UnaryOperator>
UnaryOperator::make(const Location& loc, UnaryOperatorKind k, const std::shared_ptr<Expr>& e)
{
    auto expr = std::make_shared<UnaryOperator>();
    expr->location = loc;
    expr->valueKind = ExprValueKind::RValue;
    expr->kind = k;
    expr->subExpr = e;
    return expr;
}

std::string UnaryOperator::toString(UnaryOperatorKind kind)
{
    switch (kind) {
    case UnaryOperatorKind::LogicalNot: return "!";
    case UnaryOperatorKind::Plus: return "+";
    case UnaryOperatorKind::Minus: return "-";
    case UnaryOperatorKind::PreDec: return "prefix --";
    case UnaryOperatorKind::PreInc: return "prefix ++";
    case UnaryOperatorKind::PostDec: return "postfix --";
    case UnaryOperatorKind::PostInc: return "postfix ++";
    }
    return "<unknown>";
}

void DeclRefExpr::traverse(ASTVisitor& visitor)
{
    assert(decl);
    visitor.visit(shared_from_this(), [&] { decl->traverse(visitor); });
}

std::shared_ptr<DeclRefExpr>
DeclRefExpr::make(const Location& loc, const std::shared_ptr<NamedDecl>& d)
{
    auto expr = std::make_shared<DeclRefExpr>();
    expr->location = loc;
    expr->valueKind = ExprValueKind::LValue;
    expr->decl = d;
    return expr;
}

void MemberExpr::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this(), [&] {
        assert(base);
        assert(memberDecl);
        base->traverse(visitor);
        memberDecl->traverse(visitor);
    });
}

std::shared_ptr<Expr> MemberExpr::getBase() const
{
    return base;
}

std::shared_ptr<NamedDecl> MemberExpr::getMemberDecl() const
{
    return memberDecl;
}

std::shared_ptr<MemberExpr> MemberExpr::make(
    const Location& loc, const std::shared_ptr<Expr>& base, const std::shared_ptr<NamedDecl>& d)
{
    auto expr = std::make_shared<MemberExpr>();
    expr->location = loc;
    expr->valueKind = ExprValueKind::LValue;
    expr->base = base;
    expr->memberDecl = d;
    return expr;
}

void SubscriptExpr::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this(), [&] {
        assert(base);
        assert(index);
        base->traverse(visitor);
        index->traverse(visitor);
    });
}

std::shared_ptr<Expr> SubscriptExpr::getBase() const
{
    return base;
}

std::shared_ptr<Expr> SubscriptExpr::getIndex() const
{
    return index;
}

std::shared_ptr<SubscriptExpr> SubscriptExpr::make(
    const Location& loc, const std::shared_ptr<Expr>& base, const std::shared_ptr<Expr>& index)
{
    auto expr = std::make_shared<SubscriptExpr>();
    expr->location = loc;
    expr->valueKind = ExprValueKind::LValue;
    expr->base = base;
    expr->index = index;
    return expr;
}

void ArrayLiteral::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this(), [&] {
        for (const auto& init : initializers) {
            init->traverse(visitor);
        }
    });
}

std::shared_ptr<ArrayLiteral> ArrayLiteral::ArrayLiteral::make(
    const Location& loc, const std::vector<std::shared_ptr<Expr>>& inits)
{
    auto expr = std::make_shared<ArrayLiteral>();
    expr->location = loc;
    expr->initializers = inits;
    return expr;
}

void MapEntry::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this(), [&] {
        key->traverse(visitor);
        value->traverse(visitor);
    });
}

std::shared_ptr<MapEntry> MapEntry::make(
    const Location& loc, const std::shared_ptr<Expr>& key, const std::shared_ptr<Expr>& value)
{
    auto expr = std::make_shared<MapEntry>();
    expr->location = loc;
    expr->key = key;
    expr->value = value;
    return expr;
}

void MapLiteral::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this(), [&] {
        for (const auto& entry : entries) {
            entry->traverse(visitor);
        }
    });
}

std::shared_ptr<MapLiteral>
MapLiteral::make(const Location& loc, const std::vector<std::shared_ptr<MapEntry>>& entries)
{
    auto expr = std::make_shared<MapLiteral>();
    expr->location = loc;
    expr->entries = entries;
    return expr;
}

void ImplicitStaticCastExpr::traverse(ASTVisitor& visitor)
{
    assert(subExpr);
    visitor.visit(shared_from_this(), [&] { subExpr->traverse(visitor); });
}

std::shared_ptr<ImplicitStaticCastExpr>
ImplicitStaticCastExpr::make(const Location& loc, const std::shared_ptr<Expr>& e)
{
    auto expr = std::make_shared<ImplicitStaticCastExpr>();
    expr->location = loc;
    expr->valueKind = ExprValueKind::RValue;
    expr->subExpr = e;
    return expr;
}
