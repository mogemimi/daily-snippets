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

void IdentifierResolver::visit(const std::shared_ptr<FunctionDecl>& decl)
{
    auto functionName = decl->namedDecl;
    if (functionName) {
        auto scope = getCurrentScope();
        auto name = functionName->getName();
        auto var = std::make_shared<Entity>(name, decl);
        scope->defineVariable(var);
        if (context) {
            context->entities.push_back(var);
        }
    }

    auto scope = std::make_shared<Scope>(getCurrentScope());
    pushScope(scope);

    for (const auto& arg: decl->arguments) {
        auto name = arg->getName();
        auto var = std::make_shared<Entity>(name, arg);
        scope->defineVariable(var);
        if (context) {
            context->entities.push_back(var);
        }
    }
}

void IdentifierResolver::visit(const std::shared_ptr<VariableDecl>& decl)
{
    auto scope = getCurrentScope();
    assert(scope);
    assert(decl->namedDecl);

    auto name = decl->namedDecl->getName();
    auto var = std::make_shared<Entity>(name, decl);
    scope->defineVariable(var);
    if (context) {
        context->entities.push_back(var);
    }
}

void IdentifierResolver::visit(const std::shared_ptr<NamedDecl>& decl)
{
    auto scope = getCurrentScope();
    assert(scope);

    auto entity = scope->getEntity(decl->getName());
    if (!entity) {
        // TODO: need to handle error
        printf("warning: unknown identifier '%s'\n", decl->getName().c_str());
        return;
    }
    decl->setEntity(entity);
}
