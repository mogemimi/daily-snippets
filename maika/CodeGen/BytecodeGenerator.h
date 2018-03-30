#pragma once

#include "AST/ASTVisitor.h"
#include "Basic/Forward.h"
#include "CodeGen/Instruction.h"
#include <memory>
#include <string>
#include <vector>

class BytecodeGenerator final : public ASTVisitor {
private:
    std::vector<std::shared_ptr<Instruction>> instructions;

public:
    std::vector<std::shared_ptr<Instruction>> getInstructions() const { return instructions; }

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
    void visit(const std::shared_ptr<BinaryOperator>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<UnaryOperator>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<DeclRefExpr>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<MemberExpr>& expr, Invoke&& traverse) override;

    void visit(const std::shared_ptr<TranslationUnitDecl>& decl, Invoke&& traverse) override;
    void visit(const std::shared_ptr<FunctionDecl>& decl, Invoke&& traverse) override;
    void visit(const std::shared_ptr<VariableDecl>& decl, Invoke&& traverse) override;
    void visit(const std::shared_ptr<ConstDecl>& decl, Invoke&& traverse) override;
};

// NOTE: the following class reperesents a VM
class Runtime final {
private:
    std::vector<std::shared_ptr<Value>> valueStack;

public:
    bool run(const std::vector<std::shared_ptr<Instruction>>& instructions);

    std::string getResultString() const;

    static void dump(const std::vector<std::shared_ptr<Instruction>>& instructions);
};
