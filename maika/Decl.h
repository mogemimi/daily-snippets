#pragma once

#include "ASTDumper.h"
#include "Forward.h"
#include <string>
#include <vector>
#include <memory>

class Decl {
protected:
    std::shared_ptr<Type> type;

public:
    virtual ~Decl() = default;
    virtual void traverse(ASTVisitor& visitor) = 0;
    virtual std::string dump(ASTDumper& dumper) const = 0;

    std::shared_ptr<Type> getType() const;
    void setType(const std::shared_ptr<Type>& t);
};

class NamedDecl final : public Decl, public std::enable_shared_from_this<NamedDecl> {
private:
    std::string name;
    std::shared_ptr<const Entity> entity;

public:
    std::string getName() const;

    std::shared_ptr<const Entity> getEntity() const;
    void setEntity(const std::shared_ptr<const Entity>& entity);

    void traverse(ASTVisitor& visitor) override;
    std::string dump(ASTDumper&) const override;

    static std::shared_ptr<NamedDecl> make(const std::string& v);
};

class FunctionDecl final : public Decl, public std::enable_shared_from_this<FunctionDecl> {
public:
    std::shared_ptr<NamedDecl> namedDecl;
    std::vector<std::shared_ptr<NamedDecl>> arguments;
    std::shared_ptr<CompoundStmt> compoundStmt;

    void traverse(ASTVisitor& visitor) override;
    std::string dump(ASTDumper& dumper) const override;

    static std::shared_ptr<FunctionDecl> make(
        const std::shared_ptr<NamedDecl>& n,
        const std::vector<std::shared_ptr<NamedDecl>>& a,
        const std::shared_ptr<CompoundStmt>& s);
};

class VariableDecl final : public Decl, public std::enable_shared_from_this<VariableDecl> {
public:
    std::shared_ptr<NamedDecl> namedDecl;
    std::shared_ptr<Expr> expr;

    void traverse(ASTVisitor& visitor) override;
    std::string dump(ASTDumper& dumper) const override;

    static std::shared_ptr<VariableDecl> make(const std::shared_ptr<NamedDecl>& n);
    static std::shared_ptr<VariableDecl> make(
        const std::shared_ptr<NamedDecl>& n,
        const std::shared_ptr<Expr>& e);
};
