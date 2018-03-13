#include "Sema/Entity.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Stmt.h"
#include "ASTContext.h"
#include <cassert>
#include <utility>

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

std::shared_ptr<Entity>
Entity::makeVariable(const std::string& name, const std::shared_ptr<NamedDecl>& decl)
{
    auto entity = std::make_shared<Entity>();
    entity->kind = EntityKind::Variable;
    entity->name = name;
    entity->decl = decl;
    return entity;
}

std::shared_ptr<Entity>
Entity::makeConstant(const std::string& name, const std::shared_ptr<NamedDecl>& decl)
{
    auto entity = std::make_shared<Entity>();
    entity->kind = EntityKind::Constant;
    entity->name = name;
    entity->decl = decl;
    return entity;
}

std::shared_ptr<Entity> Entity::makeType(const std::string& name, const std::shared_ptr<Type>& type)
{
    auto entity = std::make_shared<Entity>();
    entity->kind = EntityKind::Type;
    entity->name = name;
    entity->type = type;
    return entity;
}
