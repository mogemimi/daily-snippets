#pragma once

#include "ASTVisitor.h"
#include "Forward.h"
#include "Scope.h"
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

public:
    explicit IdentifierResolver(IdentifierContext* context);

    std::shared_ptr<Scope> getCurrentScope();
    void pushScope(const std::shared_ptr<Scope>& scope);
    void popScope();

    void visit(const std::shared_ptr<DeclRefExpr>& decl) override;
    void visit(const std::shared_ptr<FunctionDecl>& decl) override;
    void visit(const std::shared_ptr<ParmVarDecl>& decl) override;
    void visit(const std::shared_ptr<VariableDecl>& decl) override;
};