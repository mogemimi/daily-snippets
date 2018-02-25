#pragma once

#include "ASTVisitor.h"
#include "Forward.h"
#include "Type.h"
#include "location.hh"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class IdentifierContext;

class TypeResolver final : public ASTVisitor {
    std::vector<std::shared_ptr<TypeEnvironment>> scopeStack;
    int rank = 0;
    std::vector<std::shared_ptr<NamedDecl>> nonTypedNames;
    std::shared_ptr<const Type> lastReturnType;

public:
    TypeResolver();
    std::shared_ptr<TypeEnvironment> getCurrentScope();
    void pushScope(const std::shared_ptr<TypeEnvironment>& scope);
    void popScope();

    void error(const yy::location& l, const std::string& err);

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
