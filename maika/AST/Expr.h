#pragma once

#include "AST/Stmt.h"
#include "Basic/Forward.h"
#include <memory>
#include <string>
#include <vector>

enum class ExprValueKind {
    LValue,
    RValue,
};

class Expr : public Stmt {
protected:
    std::shared_ptr<Type> type;
    ExprValueKind valueKind;

public:
    virtual ~Expr() = default;

    bool isLValue() const { return getValueKind() == ExprValueKind::LValue; }

    ExprValueKind getValueKind() const { return valueKind; }
    void setValueKind(ExprValueKind k) { valueKind = k; }

    // TODO: for constant folding
    // bool isEvaluatable();

    std::shared_ptr<Type> getType() const;
    void setType(const std::shared_ptr<Type>& t);
};

class IntegerLiteral final
    : public Expr
    , public std::enable_shared_from_this<IntegerLiteral> {
private:
    int64_t value;

public:
    void traverse(ASTVisitor& visitor) override;

    int64_t getValue() const noexcept { return value; }

    static std::shared_ptr<IntegerLiteral> make(const Location& loc, int64_t v);
};

class DoubleLiteral final
    : public Expr
    , public std::enable_shared_from_this<DoubleLiteral> {
private:
    double value;

public:
    void traverse(ASTVisitor& visitor) override;

    double getValue() const noexcept { return value; }

    static std::shared_ptr<DoubleLiteral> make(const Location& loc, double v);
};

class BoolLiteral final
    : public Expr
    , public std::enable_shared_from_this<BoolLiteral> {
private:
    bool value;

public:
    void traverse(ASTVisitor& visitor) override;

    bool getValue() const noexcept { return value; }

    static std::shared_ptr<BoolLiteral> make(const Location& loc, bool v);
};

class StringLiteral final
    : public Expr
    , public std::enable_shared_from_this<StringLiteral> {
private:
    std::string value;

public:
    void traverse(ASTVisitor& visitor) override;

    std::string getValue() const noexcept { return value; }

    static std::shared_ptr<StringLiteral> make(const Location& loc, const std::string& v);
};

class NullLiteral final
    : public Expr
    , public std::enable_shared_from_this<NullLiteral> {
public:
    void traverse(ASTVisitor& visitor) override;

    static std::shared_ptr<NullLiteral> make(const Location& loc);
};

class CallExpr final
    : public Expr
    , public std::enable_shared_from_this<CallExpr> {
private:
    std::shared_ptr<Expr> callee;
    std::vector<std::shared_ptr<Expr>> arguments;

public:
    void traverse(ASTVisitor& visitor) override;

    std::shared_ptr<Expr> getCallee() const { return callee; }
    std::vector<std::shared_ptr<Expr>> getArguments() const { return arguments; }

    static std::shared_ptr<CallExpr> make(
        const Location& loc,
        const std::shared_ptr<Expr>& fn,
        const std::vector<std::shared_ptr<Expr>>& args);
};

class FunctionExpr final
    : public Expr
    , public std::enable_shared_from_this<FunctionExpr> {
private:
    std::shared_ptr<NamedDecl> namedDecl;
    std::vector<std::shared_ptr<ParmVarDecl>> parameters;
    std::shared_ptr<NamedDecl> returnType;
    std::shared_ptr<CompoundStmt> compoundStmt;

public:
    void traverse(ASTVisitor& visitor) override;

    std::shared_ptr<NamedDecl> getNamedDecl() const;

    const std::vector<std::shared_ptr<ParmVarDecl>>& getParameters() const;

    std::shared_ptr<NamedDecl> getReturnType() const;

    std::shared_ptr<CompoundStmt> getBody() const;

    static std::shared_ptr<FunctionExpr> make(
        const Location& loc,
        const std::shared_ptr<NamedDecl>& n,
        const std::vector<std::shared_ptr<ParmVarDecl>>& parameters,
        const std::shared_ptr<NamedDecl>& returnType,
        const std::shared_ptr<CompoundStmt>& s);
};

enum class BinaryOperatorKind {
    Add,
    Subtract,
    Multiply,
    Divide,
    Mod,
    Assign,
    Equal,
    NotEqual,
    LogicalAnd,         // &&
    LogicalOr,          // ||
    GreaterThan,        // >
    GreaterThanOrEqual, // >=
    LessThan,           // <
    LessThanOrEqual,    // <=

    // And, // &
    // Xor, // ^
    // Or, // |
};

class BinaryOperator final
    : public Expr
    , public std::enable_shared_from_this<BinaryOperator> {
private:
    BinaryOperatorKind kind;
    std::shared_ptr<Expr> lhs;
    std::shared_ptr<Expr> rhs;

public:
    void traverse(ASTVisitor& visitor) override;

    static bool isMultiplicativeOp(BinaryOperatorKind kind);
    bool isMultiplicativeOp() const;

    static bool isAdditiveOp(BinaryOperatorKind kind);
    bool isAdditiveOp() const;

    static bool isEqualityOp(BinaryOperatorKind kind);
    bool isEqualityOp() const;

    static bool isComparisonOp(BinaryOperatorKind kind);
    bool isComparisonOp() const;

    static bool isLogicalOp(BinaryOperatorKind kind);
    bool isLogicalOp() const;

    static bool isAssignmentOp(BinaryOperatorKind kind);
    bool isAssignmentOp() const;

    BinaryOperatorKind getKind() const { return kind; }

    std::shared_ptr<Expr> getLHS() const { return lhs; }
    std::shared_ptr<Expr> getRHS() const { return rhs; }

    void setLHS(const std::shared_ptr<Expr>& e) { lhs = e; }
    void setRHS(const std::shared_ptr<Expr>& e) { rhs = e; }

    static std::shared_ptr<BinaryOperator> make(
        const Location& loc,
        BinaryOperatorKind k,
        const std::shared_ptr<Expr>& l,
        const std::shared_ptr<Expr>& r);

    static std::string toString(BinaryOperatorKind kind);
};

enum class UnaryOperatorKind {
    PostInc,
    PostDec,
    PreInc,
    PreDec,
    // AddrOf,
    // Deref,
    Plus,
    Minus,
    LogicalNot, // !
};

class UnaryOperator final
    : public Expr
    , public std::enable_shared_from_this<UnaryOperator> {
private:
    UnaryOperatorKind kind;
    std::shared_ptr<Expr> subExpr;

public:
    void traverse(ASTVisitor& visitor) override;

    UnaryOperatorKind getKind() const { return kind; }

    std::shared_ptr<Expr> getSubExpr() const { return subExpr; }

    void setSubExpr(const std::shared_ptr<Expr>& s) { subExpr = s; }

    static std::shared_ptr<UnaryOperator>
    make(const Location& loc, UnaryOperatorKind k, const std::shared_ptr<Expr>& e);

    static std::string toString(UnaryOperatorKind kind);
};

class DeclRefExpr final
    : public Expr
    , public std::enable_shared_from_this<DeclRefExpr> {
private:
    std::shared_ptr<NamedDecl> decl;

public:
    void traverse(ASTVisitor& visitor) override;

    std::shared_ptr<NamedDecl> getNamedDecl() const { return decl; }

    static std::shared_ptr<DeclRefExpr>
    make(const Location& loc, const std::shared_ptr<NamedDecl>& d);
};

class MemberExpr final
    : public Expr
    , public std::enable_shared_from_this<MemberExpr> {
private:
    std::shared_ptr<Expr> base;
    std::shared_ptr<NamedDecl> memberDecl;

public:
    void traverse(ASTVisitor& visitor) override;

    std::shared_ptr<Expr> getBase() const;

    std::shared_ptr<NamedDecl> getMemberDecl() const;

    static std::shared_ptr<MemberExpr> make(
        const Location& loc,
        const std::shared_ptr<Expr>& base,
        const std::shared_ptr<NamedDecl>& d);
};

class SubscriptExpr final
    : public Expr
    , public std::enable_shared_from_this<SubscriptExpr> {
private:
    std::shared_ptr<Expr> base;
    std::shared_ptr<Expr> index;

public:
    void traverse(ASTVisitor& visitor) override;

    std::shared_ptr<Expr> getBase() const;

    std::shared_ptr<Expr> getIndex() const;

    static std::shared_ptr<SubscriptExpr> make(
        const Location& loc,
        const std::shared_ptr<Expr>& base,
        const std::shared_ptr<Expr>& index);
};

class ArrayLiteral final
    : public Expr
    , public std::enable_shared_from_this<ArrayLiteral> {
private:
    std::vector<std::shared_ptr<Expr>> initializers;

public:
    void traverse(ASTVisitor& visitor) override;

    std::vector<std::shared_ptr<Expr>> getInits() const { return initializers; }

    static std::shared_ptr<ArrayLiteral>
    make(const Location& loc, const std::vector<std::shared_ptr<Expr>>& inits);
};

class MapEntry final
    : public Expr
    , public std::enable_shared_from_this<MapEntry> {
private:
    std::shared_ptr<Expr> key;
    std::shared_ptr<Expr> value;

public:
    void traverse(ASTVisitor& visitor);

    std::shared_ptr<Expr> getKey() const { return key; }
    std::shared_ptr<Expr> getValue() const { return value; }

    static std::shared_ptr<MapEntry>
    make(const Location& loc, const std::shared_ptr<Expr>& key, const std::shared_ptr<Expr>& value);
};

class MapLiteral final
    : public Expr
    , public std::enable_shared_from_this<MapLiteral> {
private:
    std::vector<std::shared_ptr<MapEntry>> entries;

public:
    void traverse(ASTVisitor& visitor) override;

    std::vector<std::shared_ptr<MapEntry>> getEntries() const { return entries; }

    static std::shared_ptr<MapLiteral>
    make(const Location& loc, const std::vector<std::shared_ptr<MapEntry>>& entries);
};

class ImplicitStaticCastExpr final
    : public Expr
    , public std::enable_shared_from_this<ImplicitStaticCastExpr> {
private:
    std::shared_ptr<Expr> subExpr;

public:
    void traverse(ASTVisitor& visitor) override;

    std::shared_ptr<Expr> getSubExpr() const { return subExpr; }

    static std::shared_ptr<ImplicitStaticCastExpr>
    make(const Location& loc, const std::shared_ptr<Expr>& e);
};
