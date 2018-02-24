#pragma once

#include "Forward.h"
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class ASTVisitor {
public:
    using Invoke = std::function<void()>;

    virtual ~ASTVisitor() = default;

    virtual void visit(const std::shared_ptr<CompoundStmt>& stmt) {}
    virtual void visit(const std::shared_ptr<CompoundStmt>& stmt, Invoke&& traverse)
    {
        visit(stmt);
        traverse();
    }

    virtual void visit(const std::shared_ptr<ReturnStmt>& stmt) {}
    virtual void visit(const std::shared_ptr<ReturnStmt>& stmt, Invoke&& traverse)
    {
        visit(stmt);
        traverse();
    }

    virtual void visit(const std::shared_ptr<DeclStmt>& stmt) {}
    virtual void visit(const std::shared_ptr<DeclStmt>& stmt, Invoke&& traverse)
    {
        visit(stmt);
        traverse();
    }

    virtual void visit(const std::shared_ptr<CallExpr>& expr) {}
    virtual void visit(const std::shared_ptr<CallExpr>& expr, Invoke&& traverse)
    {
        visit(expr);
        traverse();
    }

    virtual void visit(const std::shared_ptr<IntegerLiteral>& expr) {}
    virtual void visit(const std::shared_ptr<DoubleLiteral>& expr) {}
    virtual void visit(const std::shared_ptr<BoolLiteral>& expr) {}

    virtual void visit(const std::shared_ptr<BinaryOperator>& expr) {}
    virtual void visit(const std::shared_ptr<BinaryOperator>& expr, Invoke&& traverse)
    {
        visit(expr);
        traverse();
    }

    virtual void visit(const std::shared_ptr<DeclRefExpr>& expr) {}
    virtual void visit(const std::shared_ptr<DeclRefExpr>& expr, Invoke&& traverse)
    {
        visit(expr);
        traverse();
    }

    virtual void visit(const std::shared_ptr<FunctionDecl>& decl) {}
    virtual void visit(const std::shared_ptr<FunctionDecl>& decl, Invoke&& traverse)
    {
        visit(decl);
        traverse();
    }

    virtual void visit(const std::shared_ptr<ParmVarDecl>& decl) {}
    virtual void visit(const std::shared_ptr<ParmVarDecl>& decl, Invoke&& traverse)
    {
        visit(decl);
        traverse();
    }

    virtual void visit(const std::shared_ptr<TranslationUnitDecl>& decl) {}
    virtual void visit(const std::shared_ptr<TranslationUnitDecl>& decl, Invoke&& traverse)
    {
        visit(decl);
        traverse();
    }

    virtual void visit(const std::shared_ptr<VariableDecl>& decl) {}
    virtual void visit(const std::shared_ptr<VariableDecl>& decl, Invoke&& traverse)
    {
        visit(decl);
        traverse();
    }

    virtual void visit(const std::shared_ptr<NamedDecl>& decl) {}
};

class ASTTraverser final {
public:
    void traverse(const ASTContext& context, ASTVisitor& visitor);
};
