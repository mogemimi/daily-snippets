#pragma once

#include "Forward.h"
#include <string>
#include <vector>
#include <memory>

class Stmt {
public:
    virtual ~Stmt() = default;
    virtual void traverse(ASTVisitor& visitor) = 0;
    virtual std::string dump(ASTDumper& dumper) const = 0;
};

class CompoundStmt final : public Stmt {
public:
    std::vector<std::shared_ptr<Stmt>> statements;

    void traverse(ASTVisitor& visitor) override;
    std::string dump(ASTDumper& dumper) const override;

    static std::shared_ptr<CompoundStmt> make(
        const std::vector<std::shared_ptr<Stmt>>& s);
};

class DeclStmt final
    : public Stmt
    , public std::enable_shared_from_this<DeclStmt> {
public:
    std::shared_ptr<Decl> decl;

    void traverse(ASTVisitor& visitor) override;
    std::string dump(ASTDumper& dumper) const override;

    static std::shared_ptr<DeclStmt> make(const std::shared_ptr<Decl>& d);
};

class ReturnStmt final : public Stmt {
public:
    std::shared_ptr<Expr> expr;

    void traverse(ASTVisitor& visitor) override;
    std::string dump(ASTDumper& dumper) const override;

    static std::shared_ptr<ReturnStmt> make();
    static std::shared_ptr<ReturnStmt> make(const std::shared_ptr<Expr>& e);
};
