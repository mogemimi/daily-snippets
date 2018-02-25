#include "Scope.h"
#include "Decl.h"
#include "Entity.h"
#include "Expr.h"
#include "Stmt.h"
#include <cassert>
#include <utility>

Scope::Scope(const std::shared_ptr<const Scope>& parentIn)
    : parent(parentIn)
{
}

std::shared_ptr<const Scope> Scope::getParent() const
{
    return parent;
}

std::shared_ptr<Entity> Scope::getEntity(const std::string& name) const
{
    auto iter = variables.find(name);
    if (iter != std::end(variables)) {
        return iter->second;
    }
    if (parent) {
        return parent->getEntity(name);
    }
    return nullptr;
}

void Scope::defineVariable(const std::shared_ptr<Entity>& v)
{
    assert(v);
    variables.emplace(v->getName(), v);
}
