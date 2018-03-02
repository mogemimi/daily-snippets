#pragma once

#include "ASTVisitor.h"
#include "Forward.h"
#include <memory>
#include <string>
#include <vector>

class ASTDumper final : public ASTVisitor {
private:
    std::string indent;

public:
    std::string result;

    std::string getIndent() const { return indent; }

    void setIndent(const std::string& i) { indent = i; }

    void visit(const std::shared_ptr<CompoundStmt>& stmt, Invoke&& traverse) override;
    void visit(const std::shared_ptr<ReturnStmt>& stmt, Invoke&& traverse) override;
    void visit(const std::shared_ptr<DeclStmt>& stmt, Invoke&& traverse) override;

    void visit(const std::shared_ptr<CallExpr>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<IntegerLiteral>& expr) override;
    void visit(const std::shared_ptr<DoubleLiteral>& expr) override;
    void visit(const std::shared_ptr<BoolLiteral>& expr) override;
    void visit(const std::shared_ptr<BinaryOperator>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<DeclRefExpr>& expr, Invoke&& traverse) override;

    void visit(const std::shared_ptr<TranslationUnitDecl>& decl, Invoke&& traverse) override;
    void visit(const std::shared_ptr<FunctionDecl>& decl, Invoke&& traverse) override;
    void visit(const std::shared_ptr<ParmVarDecl>& decl, Invoke&& traverse) override;
    void visit(const std::shared_ptr<VariableDecl>& decl, Invoke&& traverse) override;
};
