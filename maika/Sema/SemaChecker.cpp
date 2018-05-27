#include "Sema/SemaChecker.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Stmt.h"
#include "Basic/Diagnostic.h"
#include "Sema/ASTEvaluator.h"
#include "Sema/Entity.h"
#include "Sema/IdentifierResolver.h"
#include "Sema/Value.h"
#include <cassert>
#include <sstream>
#include <utility>

namespace {

bool hasConstantReassignedError(
    const std::shared_ptr<Expr>& lhs, const std::shared_ptr<DiagnosticHandler>& diag)
{
    assert(lhs);
    assert(diag);
    auto declRef = std::dynamic_pointer_cast<DeclRefExpr>(lhs);
    if (!declRef) {
        return false;
    }
    auto namedDecl = declRef->getNamedDecl();
    if (!namedDecl) {
        return false;
    }
    auto entity = namedDecl->getEntity();
    if (!entity) {
        return false;
    }
    if (entity->getKind() == EntityKind::Constant) {
        diag->error(
            namedDecl->getLocation(),
            "'" + namedDecl->getName() + "' cannot be reassigned because it is a constant.");
        return true;
    }
    if (entity->getKind() == EntityKind::Type) {
        diag->error(
            namedDecl->getLocation(),
            "'" + namedDecl->getName() + "' cannot be assigned because it only refers to a type.");
        return true;
    }
    if (entity->getKind() != EntityKind::Variable) {
        diag->error(lhs->getLocation(), "Cannot assign to '" + namedDecl->getName() + "'.");
        return true;
    }
    return false;
}

} // end of anonymous namespace

SemaChecker::SemaChecker(const std::shared_ptr<DiagnosticHandler>& diagIn)
    : diag(diagIn)
{
    assert(diag);
}

void SemaChecker::error(const Location& l, const std::string& err)
{
    assert(diag);
    diag->error(l, err);
}

void SemaChecker::visit(const std::shared_ptr<IfStmt>& stmt, Invoke&& traverse)
{
    if (!stmt->getThen()) {
        diag->warn(stmt->getLocation(), "if statement has empty body");
    }

    traverse();
}

void SemaChecker::visit(const std::shared_ptr<WhileStmt>& stmt, Invoke&& traverse)
{
    if (!stmt->getBody()) {
        diag->warn(stmt->getLocation(), "while statement has empty body");
    }

    traverse();
}

void SemaChecker::visit(const std::shared_ptr<ForStmt>& stmt, Invoke&& traverse)
{
    if (!stmt->getBody()) {
        diag->warn(stmt->getLocation(), "for statement has empty body");
    }

    traverse();
}

void SemaChecker::visit(const std::shared_ptr<CallExpr>& expr, Invoke&& traverse)
{
    traverse();
}

void SemaChecker::visit(const std::shared_ptr<FunctionExpr>& expr, Invoke&& traverse)
{
    traverse();
}

void SemaChecker::visit(const std::shared_ptr<BinaryOperator>& expr, Invoke&& traverse)
{
    traverse();

    if (expr->isAssignmentOp()) {
        const auto lhs = expr->getLHS();
        assert(lhs);
        if (hasConstantReassignedError(lhs, diag)) {
            return;
        }

        if (!lhs->isLValue()) {
            error(lhs->getLocation(), "The left-hand side of an assignment must be a variable.");
            return;
        }
    }
}

void SemaChecker::visit(const std::shared_ptr<UnaryOperator>& expr, Invoke&& traverse)
{
    traverse();
}

void SemaChecker::visit(const std::shared_ptr<DeclRefExpr>& expr, Invoke&& traverse)
{
    traverse();
}

void SemaChecker::visit(const std::shared_ptr<ParenExpr>& expr, Invoke&& traverse)
{
    traverse();

    auto subExpr = expr->getSubExpr();
    assert(subExpr);
    expr->setValueKind(subExpr->getValueKind());
}

namespace {

template <class ValueType, class LiteralType>
std::shared_ptr<Expr> makeLiteral(const std::shared_ptr<Expr>& expr, const Value* value)
{
    auto v = static_cast<const ValueType*>(value)->getValue();
    auto literal = LiteralType::make(expr->getLocation(), v);
    literal->setType(expr->getType());
    return literal;
}

std::shared_ptr<Expr>
constantFolding(const std::shared_ptr<Expr>& expr, const std::shared_ptr<DiagnosticHandler>& diag)
{
    auto [value, evalResult] = ASTEvaluator::evaluate(expr, diag);

    if (evalResult != ASTEvaluateResult::StaticEvaluation) {
        return expr;
    }
    if (value->getKind() == ValueKind::Int64) {
        return makeLiteral<Int64Value, IntegerLiteral>(expr, value.get());
    }
    if (value->getKind() == ValueKind::Double) {
        return makeLiteral<DoubleValue, DoubleLiteral>(expr, value.get());
    }
    if (value->getKind() == ValueKind::Bool) {
        return makeLiteral<BoolValue, BoolLiteral>(expr, value.get());
    }
    if (value->getKind() == ValueKind::String) {
        return makeLiteral<StringValue, StringLiteral>(expr, value.get());
    }
    return expr;
}

} // end of anonymous namespace

Optimizer::Optimizer(const std::shared_ptr<DiagnosticHandler>& diagIn)
    : diag(diagIn)
{
    assert(diag);
}

void Optimizer::error(const Location& l, const std::string& err)
{
    assert(diag);
    diag->error(l, err);
}

void Optimizer::visit(const std::shared_ptr<BinaryOperator>& expr, Invoke&& traverse)
{
    traverse();

    expr->setLHS(constantFolding(expr->getLHS(), diag));
    expr->setRHS(constantFolding(expr->getRHS(), diag));
}

void Optimizer::visit(const std::shared_ptr<UnaryOperator>& expr, Invoke&& traverse)
{
    traverse();
}

void Optimizer::visit(const std::shared_ptr<DeclRefExpr>& expr, Invoke&& traverse)
{
    traverse();
}

void Optimizer::visit(const std::shared_ptr<VariableDecl>& decl, Invoke&& traverse)
{
    traverse();

    if (auto expr = decl->getExpr()) {
        decl->setExpr(constantFolding(expr, diag));
    }
}
