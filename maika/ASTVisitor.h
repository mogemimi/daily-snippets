#pragma once

#include "Forward.h"
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class ASTVisitor {
public:
    virtual ~ASTVisitor() = default;

    virtual void visit(const std::shared_ptr<FunctionDecl>& decl) {}
    virtual void visit(const std::shared_ptr<VariableDecl>& decl) {}
    virtual void visit(const std::shared_ptr<NamedDecl>& decl) {}
    virtual void visit(CallExpr* decl) {}
};

class ASTTraverser final {
public:
    void traverse(const AST& ast, ASTVisitor& visitor);
};
