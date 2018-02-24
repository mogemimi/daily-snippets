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
{
}

std::shared_ptr<NamedDecl> Entity::getDecl() const
{
    return decl.lock();
}

std::string Entity::getName() const
{
    return name;
}
