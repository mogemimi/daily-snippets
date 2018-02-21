#pragma once

#include "ASTDumper.h"
#include "Forward.h"
#include "location.hh"
#include <string>
#include <vector>
#include <memory>

class Decl {
protected:
    std::shared_ptr<Type> type;
    yy::location location;

public:
    virtual ~Decl() = default;
    virtual void traverse(ASTVisitor& visitor) = 0;
    virtual std::string dump(ASTDumper& dumper) const = 0;

    yy::location getLocation() const;

    std::shared_ptr<Type> getType() const;
    void setType(const std::shared_ptr<Type>& t);
};

class NamedDecl final
    : public Decl
    , public std::enable_shared_from_this<NamedDecl> {
private:
    std::string name;
    std::shared_ptr<const Entity> entity;

public:
    std::string getName() const;

    std::shared_ptr<const Entity> getEntity() const;
    void setEntity(const std::shared_ptr<const Entity>& entity);

    void traverse(ASTVisitor& visitor) override;
    std::string dump(ASTDumper&) const override;

    static std::shared_ptr<NamedDecl> make(
        const yy::location& loc,
        const std::string& v);
};

class FunctionDecl final
    : public Decl
    , public std::enable_shared_from_this<FunctionDecl> {
public:
    std::shared_ptr<NamedDecl> namedDecl;
    std::vector<std::shared_ptr<ParmVarDecl>> arguments;
    std::shared_ptr<CompoundStmt> compoundStmt;

    void traverse(ASTVisitor& visitor) override;
    std::string dump(ASTDumper& dumper) const override;

    static std::shared_ptr<FunctionDecl> make(
        const yy::location& loc,
        const std::shared_ptr<NamedDecl>& n,
        const std::vector<std::shared_ptr<ParmVarDecl>>& a,
        const std::shared_ptr<CompoundStmt>& s);
};

class ParmVarDecl final
    : public Decl
    , public std::enable_shared_from_this<ParmVarDecl> {
public:
    std::shared_ptr<NamedDecl> name;
    std::shared_ptr<NamedDecl> type;

    void traverse(ASTVisitor& visitor) override;
    std::string dump(ASTDumper& dumper) const override;

    static std::shared_ptr<ParmVarDecl> make(
        const yy::location& loc,
        const std::shared_ptr<NamedDecl>& name);

    static std::shared_ptr<ParmVarDecl> make(
        const yy::location& loc,
        const std::shared_ptr<NamedDecl>& name,
        const std::shared_ptr<NamedDecl>& type);
};

class VariableDecl final
    : public Decl
    , public std::enable_shared_from_this<VariableDecl> {
public:
    std::shared_ptr<NamedDecl> namedDecl;
    std::shared_ptr<Expr> expr;

    void traverse(ASTVisitor& visitor) override;
    std::string dump(ASTDumper& dumper) const override;

    static std::shared_ptr<VariableDecl> make(
        const yy::location& loc,
        const std::shared_ptr<NamedDecl>& n);
    static std::shared_ptr<VariableDecl> make(
        const yy::location& loc,
        const std::shared_ptr<NamedDecl>& n,
        const std::shared_ptr<Expr>& e);
};
