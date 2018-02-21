#pragma once

#include "Forward.h"
#include "ASTVisitor.h"
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class IdentifierContext;

class TypeEnv {
public:
};

class TypeResolver final : public ASTVisitor {
public:
//    std::unordered_map<TypeVariableIndex, std::shared_ptr<Type>> types;
//    std::unordered_map<std::shared_ptr<Decl>, TypeVariableIndex> decls;
//    std::unordered_map<std::shared_ptr<Expr>, TypeVariableIndex> exprs;
//
//    void unifySymbols(const IdentifierContext& context);

    void visit(const std::shared_ptr<FunctionDecl>& decl) override;
    void visit(const std::shared_ptr<VariableDecl>& decl) override;
    void visit(const std::shared_ptr<NamedDecl>& decl) override;
};

class ASTDumper2 final : public ASTVisitor {
private:
    std::string indent = "  ";

public:
    void visit(const std::shared_ptr<DeclStmt>& decl) override;

    void visit(const std::shared_ptr<CallExpr>& decl) override;
    void visit(const std::shared_ptr<IntegerLiteral>& decl) override;
    void visit(const std::shared_ptr<DoubleLiteral>& decl) override;
    void visit(const std::shared_ptr<BoolLiteral>& decl) override;
    void visit(const std::shared_ptr<AssignmentOperator>& decl) override;
    void visit(const std::shared_ptr<BinaryOperator>& decl) override;
    void visit(const std::shared_ptr<DeclRefExpr>& decl) override;

    void visit(const std::shared_ptr<FunctionDecl>& decl) override;
    void visit(const std::shared_ptr<ParmVarDecl>& decl) override;
    void visit(const std::shared_ptr<VariableDecl>& decl) override;
};
