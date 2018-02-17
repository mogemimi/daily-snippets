#include "ASTVisitor.h"
#include "AST.h"
#include "Decl.h"
#include "Expr.h"
#include "Stmt.h"
#include <cassert>
#include <utility>

namespace {

using TypeVariableIndex = uint64_t;
//TypeVariableIndex typeVariableIndex;
std::unordered_map<TypeVariableIndex, std::string> table2;
std::unordered_map<std::string, std::vector<const Decl*>> table;

void addDecl(const std::string& name, const Decl* decl)
{
    auto iter = table.find(name);
    if (iter == std::end(table)) {
        table.emplace(name, std::vector<const Decl*>{});
        iter = table.find(name);
    }
    iter->second.push_back(decl);
}

TypeVariableIndex makeTypeVariableIndex()
{
    static TypeVariableIndex typeIndex = 10000;
    ++typeIndex;
    return typeIndex;
}

} // end of anonymous namespace

Scope::Scope()
{
}

Scope::Scope(std::shared_ptr<Scope> parentIn)
    : parent(parentIn)
{
}

std::shared_ptr<Scope> Scope::getParent() const
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
    variables.emplace(v->name, v);
}

IdentifierResolver::IdentifierResolver()
{
    pushScope();
}

std::shared_ptr<Scope> IdentifierResolver::getCurrentScope()
{
    assert(!scopeStack.empty());
    return scopeStack.back();
}

void IdentifierResolver::pushScope()
{
    auto scope = std::make_shared<Scope>();
    scopeStack.push_back(std::move(scope));
}

void IdentifierResolver::popScope()
{
    assert(!scopeStack.empty());
    scopeStack.pop_back();
}

void IdentifierResolver::visit(FunctionDecl* decl)
{
}

void IdentifierResolver::visit(VariableDecl* decl)
{
    auto scope = getCurrentScope();

    auto var = std::make_shared<Entity>();
    var->name = decl->namedDecl->name;
    scope->defineVariable(var);
}

void IdentifierResolver::visit(NamedDecl* decl)
{
    scope
}

void TypeSolver::visit(FunctionDecl* decl)
{
}

void TypeSolver::visit(VariableDecl* decl)
{
    assert(decl->namedDecl);

    const auto typeIndex = makeTypeVariableIndex();
    addDecl(decl->namedDecl->name, decl->namedDecl.get());
    //printf("[%d] %s\n", static_cast<int>(typeIndex), decl->namedDecl->name.c_str());

    //table.emplace(decl->namedDecl->name, decl->named);
}

void TypeSolver::visit(NamedDecl* namedDecl)
{
    const auto typeIndex = makeTypeVariableIndex();
    addDecl(namedDecl->name, namedDecl);
    //printf("[%d] %s\n", static_cast<int>(typeIndex), namedDecl->name.c_str());
}

void ASTTraverser::traverse(const AST& ast, ASTVisitor& visitor)
{
    for (const auto& funcDecl : ast.functionDecls) {
        assert(funcDecl);
        funcDecl->traverse(visitor);
    }
}
