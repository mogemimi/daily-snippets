#include "Sema/Scope.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Stmt.h"
#include "Sema/Entity.h"
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

std::shared_ptr<Entity> Scope::findAlt(const std::string& name) const
{
    auto iter = variables.find(name);
    if (iter != std::end(variables)) {
        return iter->second;
    }
    return nullptr;
}

void Scope::insert(const std::shared_ptr<Entity>& v)
{
    assert(v);
    assert(findAlt(v->getName()) == nullptr);
    variables.emplace(v->getName(), v);
}
