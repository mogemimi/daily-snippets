#pragma once

#include "Basic/Forward.h"
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

    virtual void visit(const std::shared_ptr<DeclStmt>& stmt) {}
    virtual void visit(const std::shared_ptr<DeclStmt>& stmt, Invoke&& traverse)
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

    virtual void visit(const std::shared_ptr<IfStmt>& stmt) {}
    virtual void visit(const std::shared_ptr<IfStmt>& stmt, Invoke&& traverse)
    {
        visit(stmt);
        traverse();
    }

    virtual void visit(const std::shared_ptr<WhileStmt>& stmt) {}
    virtual void visit(const std::shared_ptr<WhileStmt>& stmt, Invoke&& traverse)
    {
        visit(stmt);
        traverse();
    }

    virtual void visit(const std::shared_ptr<ForStmt>& stmt) {}
    virtual void visit(const std::shared_ptr<ForStmt>& stmt, Invoke&& traverse)
    {
        visit(stmt);
        traverse();
    }

    virtual void visit(const std::shared_ptr<ForRangeStmt>& stmt) {}
    virtual void visit(const std::shared_ptr<ForRangeStmt>& stmt, Invoke&& traverse)
    {
        visit(stmt);
        traverse();
    }

    virtual void visit(const std::shared_ptr<DeferStmt>& stmt) {}
    virtual void visit(const std::shared_ptr<DeferStmt>& stmt, Invoke&& traverse)
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

    virtual void visit(const std::shared_ptr<FunctionExpr>& expr) {}
    virtual void visit(const std::shared_ptr<FunctionExpr>& expr, Invoke&& traverse)
    {
        visit(expr);
        traverse();
    }

    virtual void visit(const std::shared_ptr<IntegerLiteral>& expr) {}
    virtual void visit(const std::shared_ptr<DoubleLiteral>& expr) {}
    virtual void visit(const std::shared_ptr<BoolLiteral>& expr) {}
    virtual void visit(const std::shared_ptr<StringLiteral>& expr) {}
    virtual void visit(const std::shared_ptr<NullLiteral>& expr) {}

    virtual void visit(const std::shared_ptr<BinaryOperator>& expr) {}
    virtual void visit(const std::shared_ptr<BinaryOperator>& expr, Invoke&& traverse)
    {
        visit(expr);
        traverse();
    }

    virtual void visit(const std::shared_ptr<UnaryOperator>& expr) {}
    virtual void visit(const std::shared_ptr<UnaryOperator>& expr, Invoke&& traverse)
    {
        visit(expr);
        traverse();
    }

    virtual void visit(const std::shared_ptr<ConditionalOperator>& expr) {}
    virtual void visit(const std::shared_ptr<ConditionalOperator>& expr, Invoke&& traverse)
    {
        visit(expr);
        traverse();
    }

    virtual void visit(const std::shared_ptr<NullConditionalOperator>& expr) {}
    virtual void visit(const std::shared_ptr<NullConditionalOperator>& expr, Invoke&& traverse)
    {
        visit(expr);
        traverse();
    }

    virtual void visit(const std::shared_ptr<ParenExpr>& expr) {}
    virtual void visit(const std::shared_ptr<ParenExpr>& expr, Invoke&& traverse)
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

    virtual void visit(const std::shared_ptr<MemberExpr>& expr) {}
    virtual void visit(const std::shared_ptr<MemberExpr>& expr, Invoke&& traverse)
    {
        visit(expr);
        traverse();
    }

    virtual void visit(const std::shared_ptr<SubscriptExpr>& expr) {}
    virtual void visit(const std::shared_ptr<SubscriptExpr>& expr, Invoke&& traverse)
    {
        visit(expr);
        traverse();
    }

    virtual void visit(const std::shared_ptr<ArrayLiteral>& expr) {}
    virtual void visit(const std::shared_ptr<ArrayLiteral>& expr, Invoke&& traverse)
    {
        visit(expr);
        traverse();
    }

    virtual void visit(const std::shared_ptr<MapEntry>& expr) {}
    virtual void visit(const std::shared_ptr<MapEntry>& expr, Invoke&& traverse)
    {
        visit(expr);
        traverse();
    }

    virtual void visit(const std::shared_ptr<MapLiteral>& expr) {}
    virtual void visit(const std::shared_ptr<MapLiteral>& expr, Invoke&& traverse)
    {
        visit(expr);
        traverse();
    }

    virtual void visit(const std::shared_ptr<ImplicitStaticCastExpr>& expr) {}
    virtual void visit(const std::shared_ptr<ImplicitStaticCastExpr>& expr, Invoke&& traverse)
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

    virtual void visit(const std::shared_ptr<BindingDecl>& decl) {}
    virtual void visit(const std::shared_ptr<BindingDecl>& decl, Invoke&& traverse)
    {
        visit(decl);
        traverse();
    }

    virtual void visit(const std::shared_ptr<DecompositionDecl>& decl) {}
    virtual void visit(const std::shared_ptr<DecompositionDecl>& decl, Invoke&& traverse)
    {
        visit(decl);
        traverse();
    }

    virtual void visit(const std::shared_ptr<ClassDecl>& decl) {}
    virtual void visit(const std::shared_ptr<ClassDecl>& decl, Invoke&& traverse)
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
