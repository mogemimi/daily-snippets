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

    traverse();
}

void SemaChecker::visit(const std::shared_ptr<UnaryOperator>& expr, Invoke&& traverse)
{
    traverse();
}

void SemaChecker::visit(const std::shared_ptr<DeclRefExpr>& expr, Invoke&& traverse)
{
    traverse();
}

namespace {

std::shared_ptr<Expr>
constantFolding(const std::shared_ptr<Expr>& expr, const std::shared_ptr<DiagnosticHandler>& diag)
{
    auto [value, evalResult] = ASTEvaluator::evaluate(expr, diag);

    if (evalResult != ASTEvaluateResult::StaticEvaluation) {
        return expr;
    }

    if (value->getKind() == ValueKind::Int64) {
        auto v = static_cast<Int64Value*>(value.get())->getValue();
        auto constant = IntegerLiteral::make(expr->getLocation(), v);
        constant->setType(expr->getType());
        return constant;
    }
    if (value->getKind() == ValueKind::Double) {
        auto v = static_cast<DoubleValue*>(value.get())->getValue();
        auto constant = DoubleLiteral::make(expr->getLocation(), v);
        constant->setType(expr->getType());
        return constant;
    }
    if (value->getKind() == ValueKind::Bool) {
        auto v = static_cast<BoolValue*>(value.get())->getValue();
        auto constant = BoolLiteral::make(expr->getLocation(), v);
        constant->setType(expr->getType());
        return constant;
    }
    if (value->getKind() == ValueKind::String) {
        auto v = static_cast<StringValue*>(value.get())->getValue();
        auto constant = StringLiteral::make(expr->getLocation(), v);
        constant->setType(expr->getType());
        return constant;
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

void Optimizer::visit(const std::shared_ptr<ConstDecl>& decl, Invoke&& traverse)
{
    traverse();

    if (auto expr = decl->getExpr()) {
        decl->setExpr(constantFolding(expr, diag));
    }
}
