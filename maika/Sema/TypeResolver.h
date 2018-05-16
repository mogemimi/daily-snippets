#pragma once

#include "AST/ASTVisitor.h"
#include "AST/Type.h"
#include "Basic/Forward.h"
#include "Sema/TypeInferer.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

struct TypeResolverScope final {
    std::vector<std::shared_ptr<Type>> returnTypes;
    TypeEnvironment env;
};

class TypeResolver final : public ASTVisitor {
    std::vector<std::shared_ptr<TypeResolverScope>> scopeStack;
    std::shared_ptr<DiagnosticHandler> diag;

public:
    explicit TypeResolver(const std::shared_ptr<DiagnosticHandler>& diag);

    std::shared_ptr<TypeResolverScope> getCurrentScope();
    void pushScope(const std::shared_ptr<TypeResolverScope>& scope);
    void popScope();

    void error(const Location& l, const std::string& err);

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
    void visit(const std::shared_ptr<MemberExpr>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<SubscriptExpr>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<ArrayLiteral>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<MapEntry>& expr, Invoke&& traverse) override;
    void visit(const std::shared_ptr<MapLiteral>& expr, Invoke&& traverse) override;

    void visit(const std::shared_ptr<FunctionDecl>& decl, Invoke&& traverse) override;
    void visit(const std::shared_ptr<ParmVarDecl>& decl, Invoke&& traverse) override;
    void visit(const std::shared_ptr<VariableDecl>& decl, Invoke&& traverse) override;
    void visit(const std::shared_ptr<ConstDecl>& decl, Invoke&& traverse) override;
    void visit(const std::shared_ptr<NamedDecl>& decl) override;
};
