#pragma once

#include "Forward.h"
#include <memory>
#include <string>
#include <vector>

class Stmt {
public:
    virtual ~Stmt() = default;
    virtual void traverse(ASTVisitor& visitor) = 0;
};

class CompoundStmt final
    : public Stmt
    , public std::enable_shared_from_this<CompoundStmt> {
private:
    std::vector<std::shared_ptr<Stmt>> statements;

public:
    void traverse(ASTVisitor& visitor) override;

    static std::shared_ptr<CompoundStmt> make(const std::vector<std::shared_ptr<Stmt>>& s);
};

class DeclStmt final
    : public Stmt
    , public std::enable_shared_from_this<DeclStmt> {
private:
    std::shared_ptr<Decl> decl;

public:
    void traverse(ASTVisitor& visitor) override;

    static std::shared_ptr<DeclStmt> make(const std::shared_ptr<Decl>& d);
};

class ReturnStmt final
    : public Stmt
    , public std::enable_shared_from_this<ReturnStmt> {
private:
    std::shared_ptr<Expr> expr;

public:
    void traverse(ASTVisitor& visitor) override;

    std::shared_ptr<Expr> getExpr() const;

    static std::shared_ptr<ReturnStmt> make();
    static std::shared_ptr<ReturnStmt> make(const std::shared_ptr<Expr>& e);
};

class IfStmt final
    : public Stmt
    , public std::enable_shared_from_this<IfStmt> {
private:
    std::shared_ptr<Expr> condExpr;
    std::shared_ptr<Stmt> thenStmt;
    std::shared_ptr<Stmt> elseStmt;

public:
    void traverse(ASTVisitor& visitor) override;

    std::shared_ptr<Expr> getCond() const;

    std::shared_ptr<Stmt> getThen() const;

    std::shared_ptr<Stmt> getElse() const;

    static std::shared_ptr<IfStmt> make(const std::shared_ptr<Decl>& d);
};
