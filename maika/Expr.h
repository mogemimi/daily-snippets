#pragma once

#include "Forward.h"
#include "Stmt.h"
#include "location.hh"
#include <memory>
#include <string>
#include <vector>

class Expr : public Stmt {
protected:
    std::shared_ptr<const Type> type;
    yy::location location;

public:
    virtual ~Expr() = default;

    yy::location getLocation() const;

    std::shared_ptr<const Type> getType() const;
    void setType(const std::shared_ptr<const Type>& t);
};

class IntegerLiteral final
    : public Expr
    , public std::enable_shared_from_this<IntegerLiteral> {
public:
    int64_t value;

    void traverse(ASTVisitor& visitor) override;
    std::string dump(ASTDumper&) const override;

    static std::shared_ptr<IntegerLiteral> make(const yy::location& loc, int64_t v);
};

class DoubleLiteral final
    : public Expr
    , public std::enable_shared_from_this<DoubleLiteral> {
public:
    double value;

    void traverse(ASTVisitor& visitor) override;
    std::string dump(ASTDumper&) const override;

    static std::shared_ptr<DoubleLiteral> make(const yy::location& loc, double v);
};

class BoolLiteral final
    : public Expr
    , public std::enable_shared_from_this<BoolLiteral> {
public:
    bool value;

    void traverse(ASTVisitor& visitor) override;
    std::string dump(ASTDumper&) const override;

    static std::shared_ptr<BoolLiteral> make(const yy::location& loc, bool v);
};

class CallExpr final
    : public Expr
    , public std::enable_shared_from_this<CallExpr> {
public:
    std::shared_ptr<Expr> callee;
    std::vector<std::shared_ptr<Expr>> arguments;

    void traverse(ASTVisitor& visitor) override;
    std::string dump(ASTDumper&) const override;

    static std::shared_ptr<CallExpr> make(
        const yy::location& loc,
        const std::shared_ptr<Expr>& fn,
        const std::vector<std::shared_ptr<Expr>>& args);
};

enum class BinaryOperatorKind {
    Add,
    Subtract,
    Multiply,
    Divide,
    Assign,
    Equal,
    NotEqual,
    LogicalAnd, // &&
    LogicalOr,  // ||

    // LogicalNot, // !
    // And, // &
    // Xor, // ^
    // Or, // |
};

class BinaryOperator final
    : public Expr
    , public std::enable_shared_from_this<BinaryOperator> {
public:
    BinaryOperatorKind kind;
    std::shared_ptr<Expr> lhs;
    std::shared_ptr<Expr> rhs;

    void traverse(ASTVisitor& visitor) override;
    std::string dump(ASTDumper& dumper) const override;

    static std::shared_ptr<BinaryOperator> make(
        const yy::location& loc,
        BinaryOperatorKind k,
        const std::shared_ptr<Expr>& l,
        const std::shared_ptr<Expr>& r);
};

class DeclRefExpr final
    : public Expr
    , public std::enable_shared_from_this<DeclRefExpr> {
public:
    std::shared_ptr<NamedDecl> decl;

    void traverse(ASTVisitor& visitor) override;
    std::string dump(ASTDumper& dumper) const override;

    static std::shared_ptr<DeclRefExpr>
    make(const yy::location& loc, const std::shared_ptr<NamedDecl>& d);
};
