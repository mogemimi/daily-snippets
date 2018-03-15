#pragma once

#include "AST/ASTVisitor.h"
#include "AST/Type.h"
#include "Basic/Forward.h"
#include "Sema/TypeInferer.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class SemaChecker final : public ASTVisitor {
    std::shared_ptr<DiagnosticHandler> diag;

public:
    explicit SemaChecker(const std::shared_ptr<DiagnosticHandler>& diag);

    void error(const Location& l, const std::string& err);

	void visit(const std::shared_ptr<IfStmt>& stmt, Invoke&& traverse) override;
	void visit(const std::shared_ptr<WhileStmt>& stmt, Invoke&& traverse) override;
	void visit(const std::shared_ptr<ForStmt>& stmt, Invoke&& traverse) override;

    void visit(const std::shared_ptr<CallExpr>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<FunctionExpr>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<BinaryOperator>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<UnaryOperator>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<DeclRefExpr>& expr, Invoke&& traverse) override;
};
