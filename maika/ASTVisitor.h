#pragma once

#include "Forward.h"
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class ASTVisitor {
public:
    virtual ~ASTVisitor() = default;

    virtual void visit(FunctionDecl* decl) {}
    virtual void visit(VariableDecl* decl) {}
    virtual void visit(NamedDecl* decl) {}
    virtual void visit(CallExpr* decl) {}
};

class Entity {
public:
    std::string name;
};

class Scope final {
private:
    std::shared_ptr<Scope> parent;
    std::unordered_map<std::string, std::shared_ptr<Entity>> variables;

public:
    Scope();
    explicit Scope(std::shared_ptr<Scope> parentIn);

    std::shared_ptr<Scope> getParent() const;

    std::shared_ptr<Entity> getEntity(const std::string& name) const;

    void defineVariable(const std::shared_ptr<Entity>& v);
};

class IdentifierResolver final : public ASTVisitor {
private:
    std::vector<std::shared_ptr<Scope>> scopeStack;

public:
    IdentifierResolver();

    std::shared_ptr<Scope> getCurrentScope();
    void pushScope();
    void popScope();

    void visit(FunctionDecl* decl) override;
    void visit(VariableDecl* decl) override;
    void visit(NamedDecl* decl) override;
};

class TypeEnv {
public:
};

class TypeSolver final : public ASTVisitor {
public:
    void visit(FunctionDecl* decl) override;
    void visit(VariableDecl* decl) override;
    void visit(NamedDecl* decl) override;
};

class ASTTraverser final {
public:
    void traverse(const AST& ast, ASTVisitor& visitor);
};
