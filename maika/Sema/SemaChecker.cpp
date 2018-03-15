#include "Sema/SemaChecker.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Stmt.h"
#include "Basic/Diagnostic.h"
#include "Sema/Entity.h"
#include "Sema/IdentifierResolver.h"
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
