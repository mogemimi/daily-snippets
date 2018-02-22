#include "TypeResolver.h"
#include "AST.h"
#include "Decl.h"
#include "Entity.h"
#include "Expr.h"
#include "IdentifierResolver.h"
#include "Stmt.h"
#include <cassert>
#include <sstream>
#include <utility>

namespace {

} // end of anonymous namespace

void TypeResolver::visit(const std::shared_ptr<CompoundStmt>& stmt, Invoke&& traverse)
{
    traverse();
}

void TypeResolver::visit(const std::shared_ptr<ReturnStmt>& stmt, Invoke&& traverse)
{
    traverse();
    assert(stmt->expr);
    assert(stmt->expr->getType());
    lastReturnType = stmt->expr->getType();
}

void TypeResolver::visit(const std::shared_ptr<DeclStmt>& decl, Invoke&& traverse)
{
    traverse();
}

void TypeResolver::visit(const std::shared_ptr<CallExpr>& decl, Invoke&& traverse)
{
    traverse();

    assert(!decl->getType());
    assert(decl->callee);
    auto returnType = decl->callee->getType();
    assert(returnType);

    decl->setType(returnType);
}

void TypeResolver::visit(const std::shared_ptr<IntegerLiteral>& decl)
{
    assert(decl->getType());
}

void TypeResolver::visit(const std::shared_ptr<DoubleLiteral>& decl)
{
    assert(decl->getType());
}

void TypeResolver::visit(const std::shared_ptr<BoolLiteral>& decl)
{
    assert(decl->getType());
}

void TypeResolver::visit(const std::shared_ptr<BinaryOperator>& decl, Invoke&& traverse)
{
    traverse();
    assert(!decl->getType());

    const auto logicalOp = [&]() -> bool {
        switch (decl->kind) {
        case BinaryOperatorKind::Equal: return true;
        case BinaryOperatorKind::NotEqual: return true;
        case BinaryOperatorKind::LogicalAnd: return true;
        case BinaryOperatorKind::LogicalOr: return true;
        default: break;
        }
        return false;
    }();

    if (logicalOp) {
        decl->setType(BuiltinType::make(BuiltinTypeKind::Bool));
        return;
    }

    assert(decl->lhs);
    assert(decl->rhs);
    assert(decl->lhs->getType());
    assert(decl->rhs->getType());
    decl->setType(decl->lhs->getType());
}

void TypeResolver::visit(const std::shared_ptr<DeclRefExpr>& decl, Invoke&& traverse)
{
    traverse();
    assert(!decl->getType());
    assert(decl->decl);
    assert(decl->decl->getType());
    decl->setType(decl->decl->getType());
}

void TypeResolver::visit(const std::shared_ptr<FunctionDecl>& decl, Invoke&& traverse)
{
    traverse();

    assert(!decl->getType());

    auto typeVariable = decl->namedDecl->getType();
    assert(typeVariable);
    if (auto v = std::dynamic_pointer_cast<TypeVariable>(typeVariable)) {
        // TODO: Not implemented

        auto type = FunctionType::make();
        if (lastReturnType) {
            type->returnType = lastReturnType;
        }

        for (const auto& param : decl->arguments) {
            assert(param);
            assert(param->getType());
            type->parameterTypes.push_back(param->getType());
        }

        v->setType(type);
    }

    // NOTE: this is declaration.
    decl->setType(BuiltinType::make(BuiltinTypeKind::Void));
}

void TypeResolver::visit(const std::shared_ptr<ParmVarDecl>& decl, Invoke&& traverse)
{
    traverse();
    assert(!decl->getType());

    auto typeVariable = decl->name->getType();
    assert(typeVariable);

    if (!decl->type) {
        if (auto v = std::dynamic_pointer_cast<TypeVariable>(typeVariable)) {
            v->setType(AnyType::make());
        }
    }
    else {
        // TODO: Not implemented
        assert(decl->type);
    }

    decl->setType(typeVariable);
}

void TypeResolver::visit(const std::shared_ptr<VariableDecl>& decl, Invoke&& traverse)
{
    traverse();
    assert(!decl->getType());

    auto typeVariable = decl->namedDecl->getType();
    assert(typeVariable);

    if (!decl->expr) {
        if (auto v = std::dynamic_pointer_cast<TypeVariable>(typeVariable)) {
            v->setType(AnyType::make());
        }
    }
    else {
        assert(decl->expr);
        assert(decl->expr->getType());
        if (auto v = std::dynamic_pointer_cast<TypeVariable>(typeVariable)) {
            v->setType(decl->expr->getType());
        }
    }

    // NOTE: this is declaration.
    decl->setType(BuiltinType::make(BuiltinTypeKind::Void));
}

void TypeResolver::visit(const std::shared_ptr<NamedDecl>& decl)
{
    if (decl->getType()) {
        return;
    }

    auto entity = decl->getEntity();
    assert(entity);
    auto d = entity->getDecl();
    assert(d);

    if (auto type = d->getType()) {
        decl->setType(type);
    }
}
