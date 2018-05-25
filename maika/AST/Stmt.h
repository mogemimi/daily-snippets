#pragma once

#include "Basic/Forward.h"
#include "Basic/Location.h"
#include <memory>
#include <string>
#include <vector>

class Stmt {
protected:
    Location location;

public:
    virtual ~Stmt() = default;
    virtual void traverse(ASTVisitor& visitor) = 0;

    Location getLocation() const;
};

class CompoundStmt final
    : public Stmt
    , public std::enable_shared_from_this<CompoundStmt> {
private:
    std::vector<std::shared_ptr<Stmt>> statements;

public:
    void traverse(ASTVisitor& visitor) override;

    std::vector<std::shared_ptr<Stmt>> getStatements() const { return statements; }

    static std::shared_ptr<CompoundStmt>
    make(const Location& loc, const std::vector<std::shared_ptr<Stmt>>& s);
};

class DeclStmt final
    : public Stmt
    , public std::enable_shared_from_this<DeclStmt> {
private:
    std::shared_ptr<Decl> decl;

public:
    void traverse(ASTVisitor& visitor) override;

    static std::shared_ptr<DeclStmt> make(const Location& loc, const std::shared_ptr<Decl>& d);
};

class ReturnStmt final
    : public Stmt
    , public std::enable_shared_from_this<ReturnStmt> {
private:
    std::shared_ptr<Expr> expr;

public:
    void traverse(ASTVisitor& visitor) override;

    std::shared_ptr<Expr> getExpr() const;

    static std::shared_ptr<ReturnStmt> make(const Location& loc);
    static std::shared_ptr<ReturnStmt> make(const Location& loc, const std::shared_ptr<Expr>& e);
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

    void setCond(const std::shared_ptr<Expr>& condExpr);

    std::shared_ptr<Stmt> getThen() const;
    void setThen(const std::shared_ptr<Stmt>& t) { this->thenStmt = t; }

    std::shared_ptr<Stmt> getElse() const;
    void setElse(const std::shared_ptr<Stmt>& e) { this->elseStmt = e; }

    static std::shared_ptr<IfStmt> make(
        const Location& loc,
        const std::shared_ptr<Expr>& condExpr,
        const std::shared_ptr<Stmt>& thenStmt);

    static std::shared_ptr<IfStmt> make(
        const Location& loc,
        const std::shared_ptr<Expr>& condExpr,
        const std::shared_ptr<Stmt>& thenStmt,
        const std::shared_ptr<Stmt>& elseStmt);
};

class WhileStmt final
    : public Stmt
    , public std::enable_shared_from_this<WhileStmt> {
private:
    std::shared_ptr<Expr> condExpr;
    std::shared_ptr<Stmt> bodyStmt;

public:
    void traverse(ASTVisitor& visitor) override;

    std::shared_ptr<Expr> getCond() const;

    void setCond(const std::shared_ptr<Expr>& condExpr);

    std::shared_ptr<Stmt> getBody() const;
    void setBody(const std::shared_ptr<Stmt>& b) { this->bodyStmt = b; }

    static std::shared_ptr<WhileStmt> make(
        const Location& loc,
        const std::shared_ptr<Expr>& condExpr,
        const std::shared_ptr<Stmt>& bodyStmt);
};

class ForStmt final
    : public Stmt
    , public std::enable_shared_from_this<ForStmt> {
private:
    std::shared_ptr<Stmt> initStmt;
    std::shared_ptr<Expr> condExpr;
    std::shared_ptr<Expr> incExpr;
    std::shared_ptr<Stmt> bodyStmt;

public:
    void traverse(ASTVisitor& visitor) override;

    std::shared_ptr<Stmt> getInit() const;

    std::shared_ptr<Expr> getCond() const;

    void setCond(const std::shared_ptr<Expr>& condExpr);

    std::shared_ptr<Expr> getInc() const;

    std::shared_ptr<Stmt> getBody() const;
    void setBody(const std::shared_ptr<Stmt>& b) { this->bodyStmt = b; }

    static std::shared_ptr<ForStmt> make(
        const Location& loc,
        const std::shared_ptr<Stmt>& initStmt,
        const std::shared_ptr<Expr>& condExpr,
        const std::shared_ptr<Expr>& incExpr,
        const std::shared_ptr<Stmt>& bodyStmt);
};

class ForRangeStmt final
    : public Stmt
    , public std::enable_shared_from_this<ForRangeStmt> {
private:
    std::shared_ptr<Decl> loopVariable;
    std::shared_ptr<Expr> rangeExpr;
    std::shared_ptr<Stmt> bodyStmt;

public:
    void traverse(ASTVisitor& visitor) override;

    std::shared_ptr<Decl> getLoopVariable() const;

    std::shared_ptr<Expr> getRangeExpr() const;

    std::shared_ptr<Stmt> getBody() const;
    void setBody(const std::shared_ptr<Stmt>& b) { this->bodyStmt = b; }

    static std::shared_ptr<ForRangeStmt> make(
        const Location& loc,
        const std::shared_ptr<Decl>& loopVariable,
        const std::shared_ptr<Expr>& rangeExpr,
        const std::shared_ptr<Stmt>& bodyStmt);
};
