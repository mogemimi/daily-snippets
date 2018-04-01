#include "Sema/TypeChecker.h"
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

} // end of anonymous namespace

TypeChecker::TypeChecker(const std::shared_ptr<DiagnosticHandler>& diagIn)
    : diag(diagIn)
{
    assert(diag);
}

void TypeChecker::error(const Location& l, const std::string& err)
{
    assert(diag);
    diag->error(l, err);
}

void TypeChecker::visit(const std::shared_ptr<CallExpr>& expr, Invoke&& traverse)
{
    traverse();
}

void TypeChecker::visit(const std::shared_ptr<FunctionExpr>& expr, Invoke&& traverse)
{
    traverse();
}

void TypeChecker::visit(const std::shared_ptr<BinaryOperator>& expr, Invoke&& traverse)
{
    traverse();
}

void TypeChecker::visit(const std::shared_ptr<UnaryOperator>& expr, Invoke&& traverse)
{
    traverse();
}

void TypeChecker::visit(const std::shared_ptr<DeclRefExpr>& expr, Invoke&& traverse)
{
    traverse();
}
