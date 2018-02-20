#include "Entity.h"
#include "AST.h"
#include "Decl.h"
#include "Expr.h"
#include "Stmt.h"
#include <cassert>
#include <utility>

Entity::Entity(const std::string& nameIn, const std::shared_ptr<Decl>& declIn)
    : name(nameIn)
    , decl(declIn)
{
}

std::shared_ptr<Decl> Entity::getDecl() const
{
    return decl.lock();
}

std::string Entity::getName() const
{
    return name;
}
