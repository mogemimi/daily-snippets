#pragma once

#include "AST/ASTVisitor.h"
#include "Basic/Forward.h"
#include <memory>
#include <string>
#include <vector>

class ASTFormatter final : public ASTVisitor {
public:
    void visit(const std::shared_ptr<IfStmt>& stmt, Invoke&& traverse) override;
    void visit(const std::shared_ptr<WhileStmt>& stmt, Invoke&& traverse) override;
    void visit(const std::shared_ptr<ForStmt>& stmt, Invoke&& traverse) override;
    void visit(const std::shared_ptr<ForRangeStmt>& stmt, Invoke&& traverse) override;

    void visit(const std::shared_ptr<ParenExpr>& expr, Invoke&& traverse) override;
};
