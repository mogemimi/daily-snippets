#pragma once

#include "AST/ASTDumper.h"
#include "Basic/Forward.h"
#include "Basic/Location.h"
#include <memory>
#include <string>
#include <vector>

class Decl {
protected:
    std::shared_ptr<Type> type;
    Location location;

public:
    virtual ~Decl() = default;
    virtual void traverse(ASTVisitor& visitor) = 0;

    std::shared_ptr<Type> getType() const;
    void setType(const std::shared_ptr<Type>& t);

    Location getLocation() const;
};

class TranslationUnitDecl final
    : public Decl
    , public std::enable_shared_from_this<TranslationUnitDecl> {
public:
    std::vector<std::shared_ptr<FunctionDecl>> functionDecls;

    void traverse(ASTVisitor& visitor) override;

    static std::shared_ptr<TranslationUnitDecl>
    make(const Location& loc, const std::vector<std::shared_ptr<FunctionDecl>>& n);
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

    static std::shared_ptr<NamedDecl> make(const Location& loc, const std::string& v);
};

class FunctionDecl final
    : public Decl
    , public std::enable_shared_from_this<FunctionDecl> {
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

    static std::shared_ptr<FunctionDecl> make(
        const Location& loc,
        const std::shared_ptr<NamedDecl>& n,
        const std::vector<std::shared_ptr<ParmVarDecl>>& a,
        const std::shared_ptr<NamedDecl>& returnType,
        const std::shared_ptr<CompoundStmt>& s);
};

class ParmVarDecl final
    : public Decl
    , public std::enable_shared_from_this<ParmVarDecl> {
private:
    std::shared_ptr<NamedDecl> namedDecl;
    std::shared_ptr<NamedDecl> typeAnnotation;

public:
    void traverse(ASTVisitor& visitor) override;

    std::shared_ptr<NamedDecl> getNamedDecl() const { return namedDecl; }
    std::shared_ptr<NamedDecl> getTypeAnnotation() const { return typeAnnotation; }

    static std::shared_ptr<ParmVarDecl>
    make(const Location& loc, const std::shared_ptr<NamedDecl>& name);

    static std::shared_ptr<ParmVarDecl> make(
        const Location& loc,
        const std::shared_ptr<NamedDecl>& name,
        const std::shared_ptr<NamedDecl>& typeAnnotation);
};

class VariableDecl final
    : public Decl
    , public std::enable_shared_from_this<VariableDecl> {
private:
    std::shared_ptr<NamedDecl> namedDecl;
    std::shared_ptr<Expr> expr;

public:
    void traverse(ASTVisitor& visitor) override;

    std::shared_ptr<NamedDecl> getNamedDecl() const { return namedDecl; }
    std::shared_ptr<Expr> getExpr() const { return expr; }

    static std::shared_ptr<VariableDecl>
    make(const Location& loc, const std::shared_ptr<NamedDecl>& n);

    static std::shared_ptr<VariableDecl>
    make(const Location& loc, const std::shared_ptr<NamedDecl>& n, const std::shared_ptr<Expr>& e);
};

class ConstDecl final
    : public Decl
    , public std::enable_shared_from_this<ConstDecl> {
private:
    std::shared_ptr<NamedDecl> namedDecl;
    std::shared_ptr<Expr> expr;

public:
    void traverse(ASTVisitor& visitor) override;

    std::shared_ptr<NamedDecl> getNamedDecl() const { return namedDecl; }
    std::shared_ptr<Expr> getExpr() const { return expr; }

    static std::shared_ptr<ConstDecl>
    make(const Location& loc, const std::shared_ptr<NamedDecl>& n);

    static std::shared_ptr<ConstDecl>
    make(const Location& loc, const std::shared_ptr<NamedDecl>& n, const std::shared_ptr<Expr>& e);
};
