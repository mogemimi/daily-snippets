#pragma once

#include "Forward.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class ASTVisitor {
public:
    virtual ~ASTVisitor() = default;

    virtual void visit(const std::shared_ptr<DeclStmt>& decl) {}

    virtual void visit(const std::shared_ptr<CallExpr>& decl) {}
    virtual void visit(const std::shared_ptr<IntegerLiteral>& decl) {}
    virtual void visit(const std::shared_ptr<DoubleLiteral>& decl) {}
    virtual void visit(const std::shared_ptr<BoolLiteral>& decl) {}
    virtual void visit(const std::shared_ptr<BinaryOperator>& decl) {}
    virtual void visit(const std::shared_ptr<DeclRefExpr>& decl) {}

    virtual void visit(const std::shared_ptr<FunctionDecl>& decl) {}
    virtual void visit(const std::shared_ptr<ParmVarDecl>& decl) {}
    virtual void visit(const std::shared_ptr<VariableDecl>& decl) {}
    virtual void visit(const std::shared_ptr<NamedDecl>& decl) {}
};

class ASTTraverser final {
public:
    void traverse(const AST& ast, ASTVisitor& visitor);
};
