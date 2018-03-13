#pragma once

#include "AST/ASTVisitor.h"
#include "Basic/Forward.h"
#include "Sema/Scope.h"
#include <memory>
#include <string>
#include <vector>

struct IdentifierContext {
    std::vector<std::shared_ptr<Entity>> entities;
};

class IdentifierResolver final : public ASTVisitor {
private:
    std::vector<std::shared_ptr<Scope>> scopeStack;
    IdentifierContext* context;
    std::shared_ptr<DiagnosticHandler> diag;

public:
    IdentifierResolver(IdentifierContext* context, const std::shared_ptr<DiagnosticHandler>& diag);

    std::shared_ptr<Scope> getCurrentScope();
    void pushScope(const std::shared_ptr<Scope>& scope);
    void popScope();

    void error(const Location& l, const std::string& err);

    void visit(const std::shared_ptr<CompoundStmt>& stmt, Invoke&& traverse) override;
    void visit(const std::shared_ptr<IfStmt>& stmt, Invoke&& traverse) override;
    void visit(const std::shared_ptr<WhileStmt>& stmt, Invoke&& traverse) override;
    void visit(const std::shared_ptr<ForStmt>& stmt, Invoke&& traverse) override;

    void visit(const std::shared_ptr<FunctionExpr>& expr, Invoke&& traverse) override;

    void visit(const std::shared_ptr<DeclRefExpr>& decl, Invoke&& traverse) override;
    void visit(const std::shared_ptr<FunctionDecl>& decl, Invoke&& traverse) override;
    void visit(const std::shared_ptr<ParmVarDecl>& decl, Invoke&& traverse) override;
    void visit(const std::shared_ptr<VariableDecl>& decl, Invoke&& traverse) override;
    void visit(const std::shared_ptr<ConstDecl>& decl, Invoke&& traverse) override;
};
