#include "AST/Decl.h"
#include "AST/ASTVisitor.h"
#include "AST/Expr.h"
#include "AST/Stmt.h"
#include <cassert>
#include <utility>

std::shared_ptr<Type> Decl::getType() const
{
    return type;
}

void Decl::setType(const std::shared_ptr<Type>& t)
{
    assert(t);
    type = t;
}

Location Decl::getLocation() const
{
    return location;
}

void TranslationUnitDecl::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this(), [&] {
        for (const auto& decl : declarations) {
            assert(decl);
            decl->traverse(visitor);
        }
    });
}

std::shared_ptr<TranslationUnitDecl> TranslationUnitDecl::make(
    const Location& loc, const std::vector<std::shared_ptr<Decl>>& declarations)
{
    auto decl = std::make_shared<TranslationUnitDecl>();
    decl->location = loc;
    decl->declarations = declarations;
    return decl;
}

std::string NamedDecl::getName() const
{
    return name;
}

std::shared_ptr<const Entity> NamedDecl::getEntity() const
{
    return entity;
}

void NamedDecl::setEntity(const std::shared_ptr<const Entity>& entityIn)
{
    entity = entityIn;
}

void NamedDecl::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this());
}

std::shared_ptr<NamedDecl> NamedDecl::make(const Location& loc, const std::string& v)
{
    auto decl = std::make_shared<NamedDecl>();
    decl->location = loc;
    decl->name = v;
    return decl;
}

void FunctionDecl::traverse(ASTVisitor& visitor)
{
    assert(compoundStmt);
    visitor.visit(shared_from_this(), [&] {
        if (namedDecl) {
            namedDecl->traverse(visitor);
        }
        for (const auto& param : parameters) {
            param->traverse(visitor);
        }
        compoundStmt->traverse(visitor);
    });
}

std::shared_ptr<NamedDecl> FunctionDecl::getNamedDecl() const
{
    return namedDecl;
}

const std::vector<std::shared_ptr<ParmVarDecl>>& FunctionDecl::getParameters() const
{
    return parameters;
}

std::shared_ptr<NamedDecl> FunctionDecl::getReturnType() const
{
    return returnType;
}

std::shared_ptr<CompoundStmt> FunctionDecl::getBody() const
{
    return compoundStmt;
}

std::shared_ptr<FunctionDecl> FunctionDecl::make(
    const Location& loc,
    const std::shared_ptr<NamedDecl>& n,
    const std::vector<std::shared_ptr<ParmVarDecl>>& parameters,
    const std::shared_ptr<NamedDecl>& returnType,
    const std::shared_ptr<CompoundStmt>& s)
{
    auto decl = std::make_shared<FunctionDecl>();
    decl->location = loc;
    decl->namedDecl = n;
    decl->parameters = parameters;
    decl->returnType = returnType;
    decl->compoundStmt = s;
    return decl;
}

void ParmVarDecl::traverse(ASTVisitor& visitor)
{
    assert(namedDecl);
    visitor.visit(shared_from_this(), [&] { namedDecl->traverse(visitor); });
}

std::shared_ptr<ParmVarDecl>
ParmVarDecl::make(const Location& loc, const std::shared_ptr<NamedDecl>& name)
{
    auto decl = std::make_shared<ParmVarDecl>();
    decl->location = loc;
    decl->namedDecl = name;
    return decl;
}

std::shared_ptr<ParmVarDecl> ParmVarDecl::make(
    const Location& loc,
    const std::shared_ptr<NamedDecl>& name,
    const std::shared_ptr<NamedDecl>& typeAnnotation)
{
    auto decl = std::make_shared<ParmVarDecl>();
    decl->location = loc;
    decl->namedDecl = name;
    decl->typeAnnotation = typeAnnotation;
    return decl;
}

void VariableDecl::traverse(ASTVisitor& visitor)
{
    assert(namedDecl);
    visitor.visit(shared_from_this(), [&] {
        namedDecl->traverse(visitor);
        if (expr) {
            expr->traverse(visitor);
        }
    });
}

std::shared_ptr<VariableDecl>
VariableDecl::make(const Location& loc, const std::shared_ptr<NamedDecl>& n)
{
    auto decl = std::make_shared<VariableDecl>();
    decl->location = loc;
    decl->namedDecl = n;
    return decl;
}

std::shared_ptr<VariableDecl> VariableDecl::make(
    const Location& loc, const std::shared_ptr<NamedDecl>& n, const std::shared_ptr<Expr>& e)
{
    auto decl = std::make_shared<VariableDecl>();
    decl->location = loc;
    decl->namedDecl = n;
    decl->expr = e;
    return decl;
}

void ConstDecl::traverse(ASTVisitor& visitor)
{
    assert(namedDecl);
    visitor.visit(shared_from_this(), [&] {
        namedDecl->traverse(visitor);
        if (expr) {
            expr->traverse(visitor);
        }
    });
}

std::shared_ptr<ConstDecl> ConstDecl::make(const Location& loc, const std::shared_ptr<NamedDecl>& n)
{
    auto decl = std::make_shared<ConstDecl>();
    decl->location = loc;
    decl->namedDecl = n;
    return decl;
}

std::shared_ptr<ConstDecl> ConstDecl::make(
    const Location& loc, const std::shared_ptr<NamedDecl>& n, const std::shared_ptr<Expr>& e)
{
    auto decl = std::make_shared<ConstDecl>();
    decl->location = loc;
    decl->namedDecl = n;
    decl->expr = e;
    return decl;
}

void BindingDecl::traverse(ASTVisitor& visitor)
{
    assert(namedDecl);
    visitor.visit(shared_from_this(), [&] {
        namedDecl->traverse(visitor);
        if (expr) {
            expr->traverse(visitor);
        }
    });
}

std::shared_ptr<BindingDecl>
BindingDecl::make(const Location& loc, const std::shared_ptr<NamedDecl>& n)
{
    auto decl = std::make_shared<BindingDecl>();
    decl->location = loc;
    decl->namedDecl = n;
    return decl;
}

void DecompositionDecl::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this(), [&] {
        for (auto& binding : bindings) {
            assert(binding);
            binding->traverse(visitor);
        }
        if (expr) {
            expr->traverse(visitor);
        }
    });
}

std::shared_ptr<DecompositionDecl> DecompositionDecl::make(
    const Location& loc, const std::vector<std::shared_ptr<BindingDecl>>& bindings)
{
    auto decl = std::make_shared<DecompositionDecl>();
    decl->location = loc;
    decl->bindings = bindings;
    return decl;
}

std::shared_ptr<DecompositionDecl> DecompositionDecl::make(
    const Location& loc,
    const std::vector<std::shared_ptr<BindingDecl>>& bindings,
    const std::shared_ptr<Expr>& e)
{
    auto decl = std::make_shared<DecompositionDecl>();
    decl->location = loc;
    decl->bindings = bindings;
    decl->expr = e;
    return decl;
}

void ClassDecl::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this(), [&] {
        for (auto& member : members) {
            assert(member);
            member->traverse(visitor);
        }
    });
}

void ClassDecl::addMember(const std::shared_ptr<Decl>& member)
{
    assert(member);
    members.push_back(member);
}

std::shared_ptr<ClassDecl> ClassDecl::make(const Location& loc, const std::shared_ptr<NamedDecl>& n)
{
    auto decl = std::make_shared<ClassDecl>();
    decl->location = loc;
    decl->namedDecl = n;
    return decl;
}

std::shared_ptr<ClassDecl> ClassDecl::make(
    const Location& loc,
    const std::shared_ptr<NamedDecl>& n,
    const std::vector<std::shared_ptr<Decl>>& members)
{
    auto decl = std::make_shared<ClassDecl>();
    decl->location = loc;
    decl->namedDecl = n;
    decl->members = members;
    return decl;
}
