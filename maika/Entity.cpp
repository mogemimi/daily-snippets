#include "Entity.h"
#include "ASTContext.h"
#include "Decl.h"
#include "Expr.h"
#include "Stmt.h"
#include <cassert>
#include <utility>

Entity::Entity(const std::string& nameIn, const std::shared_ptr<NamedDecl>& declIn)
    : name(nameIn)
    , decl(declIn)
    , kind(EntityKind::Variable)
{
}

Entity::Entity(const std::string& nameIn, const std::shared_ptr<Type>& typeIn)
    : name(nameIn)
    , type(typeIn)
    , kind(EntityKind::Type)
{
}

EntityKind Entity::getKind() const
{
    return kind;
}

std::string Entity::getName() const
{
    return name;
}

std::shared_ptr<NamedDecl> Entity::getDecl() const
{
    assert(kind == EntityKind::Variable);
    return decl.lock();
}

std::shared_ptr<Type> Entity::getType() const
{
    assert(kind == EntityKind::Type);
    return type;
}
