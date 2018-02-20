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
