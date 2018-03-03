#include "IdentifierResolver.h"
#include "Decl.h"
#include "Entity.h"
#include "Expr.h"
#include "Stmt.h"
#include "Type.h"
#include <cassert>
#include <utility>

IdentifierResolver::IdentifierResolver(IdentifierContext* contextIn)
    : context(contextIn)
{
    auto scope = std::make_shared<Scope>();
    pushScope(scope);

    scope->insert(std::make_shared<Entity>("int", BuiltinType::make(BuiltinTypeKind::Int)));
    scope->insert(std::make_shared<Entity>("bool", BuiltinType::make(BuiltinTypeKind::Bool)));
    scope->insert(std::make_shared<Entity>("double", BuiltinType::make(BuiltinTypeKind::Double)));
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
    std::cerr << l << ": " << err << std::endl;
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

void IdentifierResolver::visit(const std::shared_ptr<FunctionDecl>& decl, Invoke&& traverse)
{
    auto namedDecl = decl->namedDecl;
    if (namedDecl) {
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

    auto entity = std::make_shared<Entity>(namedDecl->getName(), namedDecl);
    scope->insert(entity);
    namedDecl->setEntity(entity);

    if (context) {
        context->entities.push_back(entity);
    }

    traverse();
}
