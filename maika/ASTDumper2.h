#pragma once

#include "ASTVisitor.h"
#include "Forward.h"
#include <memory>
#include <string>
#include <vector>

class ASTDumper2 final : public ASTVisitor {
private:
    std::string indent;
    bool allowMultiLine;

public:
    std::string result;

    ASTDumper2()
        : allowMultiLine(true)
    {
    }
    explicit ASTDumper2(bool multiLine)
        : allowMultiLine(multiLine)
    {
    }

    std::string GetIndent() const
    {
        if (!allowMultiLine) {
            return "";
        }
        return indent;
    }

    void SetIndent(const std::string& i) { indent = i; }

    bool isMultiLine() { return allowMultiLine; }

    void visit(const std::shared_ptr<CompoundStmt>& stmt, Invoke&& traverse) override;
    void visit(const std::shared_ptr<ReturnStmt>& stmt, Invoke&& traverse) override;
    void visit(const std::shared_ptr<DeclStmt>& stmt, Invoke&& traverse) override;

    void visit(const std::shared_ptr<CallExpr>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<IntegerLiteral>& expr) override;
    void visit(const std::shared_ptr<DoubleLiteral>& expr) override;
    void visit(const std::shared_ptr<BoolLiteral>& expr) override;
    void visit(const std::shared_ptr<BinaryOperator>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<DeclRefExpr>& expr, Invoke&& traverse) override;

    void visit(const std::shared_ptr<FunctionDecl>& decl, Invoke&& traverse) override;
    void visit(const std::shared_ptr<ParmVarDecl>& decl, Invoke&& traverse) override;
    void visit(const std::shared_ptr<VariableDecl>& decl, Invoke&& traverse) override;
    void visit(const std::shared_ptr<NamedDecl>& decl) override;
};
