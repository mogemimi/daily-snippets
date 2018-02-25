#include "Decl.h"
#include "ASTVisitor.h"
#include "Expr.h"
#include "Stmt.h"
#include <cassert>
#include <utility>

yy::location Decl::getLocation() const
{
    return location;
}

std::shared_ptr<const Type> Decl::getType() const
{
    return type;
}

void Decl::setType(const std::shared_ptr<const Type>& t)
{
    assert(!type);
    assert(t);
    type = t;
}

void TranslationUnitDecl::traverse(ASTVisitor& visitor)
{
    visitor.visit(shared_from_this(), [&] {
        for (const auto& funcDecl : functionDecls) {
            assert(funcDecl);
            funcDecl->traverse(visitor);
        }
    });
}

std::string TranslationUnitDecl::dump(ASTDumper& dumper) const
{
    std::string s;
    bool needToBreakLine = false;
    for (auto& funcDecl : functionDecls) {
        assert(funcDecl);
        if (needToBreakLine) {
            s += "\n";
            needToBreakLine = false;
        }
        s += funcDecl->dump(dumper);
        needToBreakLine = true;
    }
    return s;
}

std::shared_ptr<TranslationUnitDecl> TranslationUnitDecl::make(
    const yy::location& loc, const std::vector<std::shared_ptr<FunctionDecl>>& functions)
{
    auto decl = std::make_shared<TranslationUnitDecl>();
    decl->location = loc;
    decl->functionDecls = functions;
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

std::string NamedDecl::dump(ASTDumper&) const
{
    return name;
}

std::shared_ptr<NamedDecl> NamedDecl::make(const yy::location& loc, const std::string& v)
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
        for (const auto& arg : arguments) {
            arg->traverse(visitor);
        }
        compoundStmt->traverse(visitor);
    });
}

std::string FunctionDecl::dump(ASTDumper& dumper) const
{
    assert(namedDecl);
    assert(compoundStmt);
    std::string s = "(function ";
    if (namedDecl) {
        s += namedDecl->dump(dumper);
        s += " ";
    }
    s += "(";
    bool needToSpace = false;
    for (const auto& arg : arguments) {
        if (needToSpace) {
            s += " ";
        }
        s += arg->dump(dumper);
        needToSpace = true;
    }
    s += ") ";
    s += compoundStmt->dump(dumper);
    s += ")";
    return s;
}

std::shared_ptr<FunctionDecl> FunctionDecl::make(
    const yy::location& loc,
    const std::shared_ptr<NamedDecl>& n,
    const std::vector<std::shared_ptr<ParmVarDecl>>& a,
    const std::shared_ptr<CompoundStmt>& s)
{
    auto decl = std::make_shared<FunctionDecl>();
    decl->location = loc;
    decl->namedDecl = n;
    decl->arguments = a;
    decl->compoundStmt = s;
    return decl;
}

void ParmVarDecl::traverse(ASTVisitor& visitor)
{
    assert(namedDecl);
    visitor.visit(shared_from_this(), [&] { namedDecl->traverse(visitor); });
}

std::string ParmVarDecl::dump(ASTDumper& dumper) const
{
    assert(namedDecl);
    std::string s = "(" + namedDecl->dump(dumper);
    if (type) {
        s += " ";
        s += typeAnnotation->dump(dumper);
    }
    s += ")";
    return s;
}

std::shared_ptr<ParmVarDecl>
ParmVarDecl::make(const yy::location& loc, const std::shared_ptr<NamedDecl>& name)
{
    auto decl = std::make_shared<ParmVarDecl>();
    decl->location = loc;
    decl->namedDecl = name;
    return decl;
}

std::shared_ptr<ParmVarDecl> ParmVarDecl::make(
    const yy::location& loc,
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

std::string VariableDecl::dump(ASTDumper& dumper) const
{
    assert(namedDecl);
    std::string s = "(let " + namedDecl->dump(dumper);
    if (expr) {
        s += " ";
        s += expr->dump(dumper);
    }
    s += ")";
    return s;
}

std::shared_ptr<VariableDecl>
VariableDecl::make(const yy::location& loc, const std::shared_ptr<NamedDecl>& n)
{
    auto decl = std::make_shared<VariableDecl>();
    decl->location = loc;
    decl->namedDecl = n;
    return decl;
}

std::shared_ptr<VariableDecl> VariableDecl::make(
    const yy::location& loc, const std::shared_ptr<NamedDecl>& n, const std::shared_ptr<Expr>& e)
{
    auto decl = std::make_shared<VariableDecl>();
    decl->location = loc;
    decl->namedDecl = n;
    decl->expr = e;
    return decl;
}
