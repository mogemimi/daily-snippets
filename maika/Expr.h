#pragma once

#include "Forward.h"
#include "Stmt.h"
#include <string>
#include <vector>
#include <memory>

class Expr : public Stmt {
protected:
    std::shared_ptr<Type> type;

public:
    virtual ~Expr() = default;

    std::shared_ptr<Type> getType() const;
    void setType(const std::shared_ptr<Type>& t);
};

class IntegerLiteral final
    : public Expr
    , public std::enable_shared_from_this<IntegerLiteral> {
public:
    int64_t value;

    void traverse(ASTVisitor& visitor) override;
    std::string dump(ASTDumper&) const override;

    static std::shared_ptr<IntegerLiteral> make(int64_t v);
};

class DoubleLiteral final
    : public Expr
    , public std::enable_shared_from_this<DoubleLiteral> {
public:
    double value;

    void traverse(ASTVisitor& visitor) override;
    std::string dump(ASTDumper&) const override;

    static std::shared_ptr<DoubleLiteral> make(double v);
};

class BoolLiteral final
    : public Expr
    , public std::enable_shared_from_this<BoolLiteral> {
public:
    bool value;

    void traverse(ASTVisitor& visitor) override;
    std::string dump(ASTDumper&) const override;

    static std::shared_ptr<BoolLiteral> make(bool v);
};

class CallExpr final
    : public Expr
    , public std::enable_shared_from_this<CallExpr> {
public:
    std::shared_ptr<NamedDecl> namedDecl;
    std::vector<std::shared_ptr<Expr>> arguments;

    void traverse(ASTVisitor& visitor) override;
    std::string dump(ASTDumper&) const override;

    static std::shared_ptr<CallExpr> make(
        const std::shared_ptr<NamedDecl>& n,
        const std::vector<std::shared_ptr<Expr>>& a);
};

class AssignmentOperator final
    : public Expr
    , public std::enable_shared_from_this<AssignmentOperator> {
public:
    std::shared_ptr<NamedDecl> lhs;
    std::shared_ptr<Expr> rhs;

    void traverse(ASTVisitor& visitor) override;
    std::string dump(ASTDumper& dumper) const override;

    static std::shared_ptr<AssignmentOperator> make(
        const std::shared_ptr<NamedDecl>& l,
        const std::shared_ptr<Expr>& r);
};

enum class BinaryOperatorKind {
    Add,
    Subtract,
    Multiply,
    Divide,
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
        BinaryOperatorKind k,
        const std::shared_ptr<Expr>& l,
        const std::shared_ptr<Expr>& r);
};

class DeclRefExpr final
    : public Expr
    , public std::enable_shared_from_this<DeclRefExpr> {
public:
    std::shared_ptr<Decl> decl;

    void traverse(ASTVisitor& visitor) override;
    std::string dump(ASTDumper& dumper) const override;

    static std::shared_ptr<DeclRefExpr> make(const std::shared_ptr<Decl>& d);
};
