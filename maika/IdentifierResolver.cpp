#include "IdentifierResolver.h"
#include "Decl.h"
#include "Diagnostic.h"
#include "Entity.h"
#include "Expr.h"
#include "Stmt.h"
#include "Type.h"
#include <cassert>
#include <utility>

IdentifierResolver::IdentifierResolver(
    IdentifierContext* contextIn, const std::shared_ptr<DiagnosticHandler>& diagIn)
    : context(contextIn)
    , diag(diagIn)
{
    assert(diag);

    auto scope = std::make_shared<Scope>();
    pushScope(scope);

    scope->insert(std::make_shared<Entity>("int", BuiltinType::make(BuiltinTypeKind::Int)));
    scope->insert(std::make_shared<Entity>("bool", BuiltinType::make(BuiltinTypeKind::Bool)));
    scope->insert(std::make_shared<Entity>("double", BuiltinType::make(BuiltinTypeKind::Double)));
    scope->insert(std::make_shared<Entity>("string", BuiltinType::make(BuiltinTypeKind::String)));
    scope->insert(std::make_shared<Entity>("void", BuiltinType::make(BuiltinTypeKind::Void)));
    scope->insert(std::make_shared<Entity>("any", BuiltinType::make(BuiltinTypeKind::Any)));
}

std::shared_ptr<Scope> IdentifierResolver::getCurrentScope()
{
    assert(!scopeStack.empty());
    return scopeStack.back();
}

void IdentifierResolver::pushScope(const std::shared_ptr<Scope>& scope)
{
    scopeStack.push_back(std::move(scope));
}

void IdentifierResolver::popScope()
{
    assert(!scopeStack.empty());
    scopeStack.pop_back();
}

void IdentifierResolver::error(const yy::location& l, const std::string& err)
{
    assert(diag);
    diag->error(l, err);
}

void IdentifierResolver::visit(const std::shared_ptr<CompoundStmt>& stmt, Invoke&& traverse)
{
    traverse();
}

void IdentifierResolver::visit(const std::shared_ptr<IfStmt>& stmt, Invoke&& traverse)
{
    auto scope = std::make_shared<Scope>(getCurrentScope());
    pushScope(scope);

    traverse();

    popScope();
}

void IdentifierResolver::visit(const std::shared_ptr<WhileStmt>& stmt, Invoke&& traverse)
{
    auto scope = std::make_shared<Scope>(getCurrentScope());
    pushScope(scope);

    traverse();

    popScope();
}

void IdentifierResolver::visit(const std::shared_ptr<ForStmt>& stmt, Invoke&& traverse)
{
    auto scope = std::make_shared<Scope>(getCurrentScope());
    pushScope(scope);

    traverse();

    popScope();
}

void IdentifierResolver::visit(const std::shared_ptr<DeclRefExpr>& expr, Invoke&& traverse)
{
    auto scope = getCurrentScope();
    assert(scope);

    auto decl = expr->getNamedDecl();
    assert(decl);

    auto entity = scope->lookup(decl->getName());
    if (!entity) {
        // TODO: need to handle error
        error(decl->getLocation(), "'" + decl->getName() + "' was not declared in this scope.");
        return;
    }

    decl->setEntity(entity);

    traverse();
}

void IdentifierResolver::visit(const std::shared_ptr<FunctionExpr>& expr, Invoke&& traverse)
{
    if (auto namedDecl = expr->getNamedDecl()) {
        auto scope = getCurrentScope();
        assert(scope);

        auto entity = std::make_shared<Entity>(namedDecl->getName(), namedDecl);
        scope->insert(entity);
        namedDecl->setEntity(entity);

        if (context) {
            context->entities.push_back(entity);
        }
    }

    auto scope = std::make_shared<Scope>(getCurrentScope());
    pushScope(scope);

    traverse();

    popScope();
}

void IdentifierResolver::visit(const std::shared_ptr<FunctionDecl>& decl, Invoke&& traverse)
{
    if (auto namedDecl = decl->getNamedDecl()) {
        auto scope = getCurrentScope();
        assert(scope);

        auto entity = std::make_shared<Entity>(namedDecl->getName(), namedDecl);
        scope->insert(entity);
        namedDecl->setEntity(entity);

        if (context) {
            context->entities.push_back(entity);
        }
    }

    auto scope = std::make_shared<Scope>(getCurrentScope());
    pushScope(scope);

    traverse();

    popScope();
}

void IdentifierResolver::visit(const std::shared_ptr<ParmVarDecl>& decl, Invoke&& traverse)
{
    auto scope = getCurrentScope();
    assert(scope);

    if (auto typeAnnotation = decl->getTypeAnnotation()) {
        auto type = scope->lookup(typeAnnotation->getName());
        if (!type) {
            error(
                typeAnnotation->getLocation(),
                "'" + typeAnnotation->getName() + "' was not declared in this scope.");
            return;
        }
        if (type->getKind() != EntityKind::Type) {
            error(
                typeAnnotation->getLocation(),
                "'" + typeAnnotation->getName() + "' is not a type name.");
            return;
        }
        typeAnnotation->setEntity(type);
    }

    auto namedDecl = decl->getNamedDecl();
    assert(namedDecl);
    assert(!namedDecl->getName().empty());

    auto entity = std::make_shared<Entity>(namedDecl->getName(), namedDecl);
    scope->insert(entity);
    namedDecl->setEntity(entity);

    if (context) {
        context->entities.push_back(entity);
    }

    traverse();
}

void IdentifierResolver::visit(const std::shared_ptr<VariableDecl>& decl, Invoke&& traverse)
{
    auto scope = getCurrentScope();
    assert(scope);

    auto namedDecl = decl->getNamedDecl();
    assert(namedDecl);

    auto alt = scope->findAlt(namedDecl->getName());
    if (alt) {
        error(namedDecl->getLocation(), "'" + namedDecl->getName() + "' redeclared in this block");
        return;
    }

    auto entity = std::make_shared<Entity>(namedDecl->getName(), namedDecl);
    scope->insert(entity);
    namedDecl->setEntity(entity);

    if (context) {
        context->entities.push_back(entity);
    }

    traverse();
}
