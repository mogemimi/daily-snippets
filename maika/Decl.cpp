#include "Decl.h"
#include "ASTVisitor.h"
#include "Expr.h"
#include "Stmt.h"
#include <cassert>
#include <utility>

std::shared_ptr<Type> Decl::getType() const
{
    return type;
}

void Decl::setType(const std::shared_ptr<Type>& t)
{
    assert(!type);
    assert(t);
    type = t;
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

std::shared_ptr<NamedDecl> NamedDecl::make(const std::string& v)
{
    auto decl = std::make_shared<NamedDecl>();
    decl->name = v;
    return decl;
}

void FunctionDecl::traverse(ASTVisitor& visitor)
{
    assert(compoundStmt);
    visitor.visit(shared_from_this());
    if (namedDecl) {
        namedDecl->traverse(visitor);
    }
    for (const auto& arg : arguments) {
        arg->traverse(visitor);
    }
    compoundStmt->traverse(visitor);
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
    const std::shared_ptr<NamedDecl>& n,
    const std::vector<std::shared_ptr<NamedDecl>>& a,
    const std::shared_ptr<CompoundStmt>& s)
{
    auto decl = std::make_shared<FunctionDecl>();
    decl->namedDecl = n;
    decl->arguments = a;
    decl->compoundStmt = s;
    return decl;
}

void VariableDecl::traverse(ASTVisitor& visitor)
{
    assert(namedDecl);
    assert(expr);
    visitor.visit(shared_from_this());
    namedDecl->traverse(visitor);
    expr->traverse(visitor);
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

std::shared_ptr<VariableDecl> VariableDecl::make(const std::shared_ptr<NamedDecl>& n)
{
    auto decl = std::make_shared<VariableDecl>();
    decl->namedDecl = n;
    return decl;
}

std::shared_ptr<VariableDecl> VariableDecl::make(
    const std::shared_ptr<NamedDecl>& n,
    const std::shared_ptr<Expr>& e)
{
    auto decl = std::make_shared<VariableDecl>();
    decl->namedDecl = n;
    decl->expr = e;
    return decl;
}
