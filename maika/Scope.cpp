#include "Scope.h"
#include "Decl.h"
#include "Entity.h"
#include "Expr.h"
#include "Stmt.h"
#include <cassert>
#include <utility>

Scope::Scope(const std::shared_ptr<const Scope>& outerIn)
    : outer(outerIn)
{
}

std::shared_ptr<const Scope> Scope::getOuter() const
{
    return outer;
}

std::shared_ptr<Entity> Scope::lookup(const std::string& name) const
{
    auto iter = variables.find(name);
    if (iter != std::end(variables)) {
        return iter->second;
    }
    if (outer) {
        return outer->lookup(name);
    }
    return nullptr;
}

void Scope::insert(const std::shared_ptr<Entity>& v)
{
    assert(v);
    variables.emplace(v->getName(), v);
}
