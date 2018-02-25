#include "IdentifierResolver.h"
#include "Decl.h"
#include "Entity.h"
#include "Expr.h"
#include "Stmt.h"
#include <cassert>
#include <utility>

IdentifierResolver::IdentifierResolver(IdentifierContext* contextIn)
    : context(contextIn)
{
    auto scope = std::make_shared<Scope>();
    pushScope(scope);
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

void IdentifierResolver::visit(const std::shared_ptr<DeclRefExpr>& expr)
{
    auto scope = getCurrentScope();
    assert(scope);

    auto ident = expr->decl;
    assert(ident);

    auto entity = scope->getEntity(ident->getName());
    if (!entity) {
        // TODO: need to handle error
        printf("warning: unknown identifier '%s'\n", ident->getName().c_str());
        return;
    }
    ident->setEntity(entity);
}

void IdentifierResolver::visit(const std::shared_ptr<FunctionDecl>& decl)
{
    auto functionName = decl->namedDecl;
    if (functionName) {
        auto scope = getCurrentScope();
        assert(scope);

        auto namedDecl = decl->namedDecl;
        assert(namedDecl);

        auto name = namedDecl->getName();
        auto entity = std::make_shared<Entity>(name, namedDecl);
        namedDecl->setEntity(entity);

        scope->defineVariable(entity);
        if (context) {
            context->entities.push_back(entity);
        }
    }

    auto scope = std::make_shared<Scope>(getCurrentScope());
    pushScope(scope);
}

void IdentifierResolver::visit(const std::shared_ptr<ParmVarDecl>& decl)
{
    auto scope = getCurrentScope();
    assert(scope);

    auto namedDecl = decl->namedDecl;
    assert(namedDecl);

    auto name = namedDecl->getName();
    auto entity = std::make_shared<Entity>(name, namedDecl);
    namedDecl->setEntity(entity);

    scope->defineVariable(entity);
    if (context) {
        context->entities.push_back(entity);
    }
}

void IdentifierResolver::visit(const std::shared_ptr<VariableDecl>& decl)
{
    auto scope = getCurrentScope();
    assert(scope);

    auto namedDecl = decl->namedDecl;
    assert(namedDecl);

    auto name = namedDecl->getName();
    auto entity = std::make_shared<Entity>(name, namedDecl);
    namedDecl->setEntity(entity);

    scope->defineVariable(entity);
    if (context) {
        context->entities.push_back(entity);
    }
}
