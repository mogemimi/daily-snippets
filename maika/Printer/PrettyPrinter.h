#pragma once

#include "AST/ASTVisitor.h"
#include "Basic/Forward.h"
#include <memory>
#include <string>
#include <vector>

class PrettyPrinter final : public ASTVisitor {
private:
    struct DumpContext {
        std::string result;
        int level = 0;
    };

    DumpContext dumpContext;

public:
    std::string getResult() const;

    void visit(const std::shared_ptr<CompoundStmt>& stmt, Invoke&& traverse) override;
    void visit(const std::shared_ptr<DeclStmt>& stmt, Invoke&& traverse) override;
    void visit(const std::shared_ptr<ReturnStmt>& stmt, Invoke&& traverse) override;
    void visit(const std::shared_ptr<IfStmt>& stmt, Invoke&& traverse) override;
    void visit(const std::shared_ptr<WhileStmt>& stmt, Invoke&& traverse) override;
    void visit(const std::shared_ptr<ForStmt>& stmt, Invoke&& traverse) override;

    void visit(const std::shared_ptr<CallExpr>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<FunctionExpr>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<IntegerLiteral>& expr) override;
    void visit(const std::shared_ptr<DoubleLiteral>& expr) override;
    void visit(const std::shared_ptr<BoolLiteral>& expr) override;
    void visit(const std::shared_ptr<StringLiteral>& expr) override;
    void visit(const std::shared_ptr<NullLiteral>& expr) override;
    void visit(const std::shared_ptr<BinaryOperator>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<UnaryOperator>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<DeclRefExpr>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<ParenExpr>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<MemberExpr>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<SubscriptExpr>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<ArrayLiteral>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<MapEntry>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<MapLiteral>& expr, Invoke&& traverse) override;

    void visit(const std::shared_ptr<TranslationUnitDecl>& decl, Invoke&& traverse) override;
    void visit(const std::shared_ptr<FunctionDecl>& decl, Invoke&& traverse) override;
    void visit(const std::shared_ptr<VariableDecl>& decl, Invoke&& traverse) override;
    void visit(const std::shared_ptr<BindingDecl>& decl, Invoke&& traverse) override;
    void visit(const std::shared_ptr<DecompositionDecl>& decl, Invoke&& traverse) override;
    void visit(const std::shared_ptr<ClassDecl>& decl, Invoke&& traverse) override;
};
