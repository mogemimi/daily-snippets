#pragma once

#include "Forward.h"
#include "ASTVisitor.h"
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class TypeEnv {
public:
};

class TypeResolver final : public ASTVisitor {
public:
    void visit(const std::shared_ptr<FunctionDecl>& decl) override;
    void visit(const std::shared_ptr<VariableDecl>& decl) override;
    void visit(const std::shared_ptr<NamedDecl>& decl) override;
};
