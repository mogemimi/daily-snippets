#pragma once

#include "Forward.h"
#include "ASTVisitor.h"
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class Scope final {
private:
    std::shared_ptr<Scope> parent;
    std::unordered_map<std::string, std::shared_ptr<Entity>> variables;

public:
    Scope();
    explicit Scope(std::shared_ptr<Scope> parentIn);

    std::shared_ptr<Scope> getParent() const;

    std::shared_ptr<Entity> getEntity(const std::string& name) const;

    void defineVariable(const std::shared_ptr<Entity>& v);
};

class IdentifierResolver final : public ASTVisitor {
private:
    std::vector<std::shared_ptr<Scope>> scopeStack;

public:
    IdentifierResolver();

    std::shared_ptr<Scope> getCurrentScope();
    void pushScope(const std::shared_ptr<Scope>& scope);
    void popScope();

    void visit(const std::shared_ptr<FunctionDecl>& decl) override;
    void visit(const std::shared_ptr<VariableDecl>& decl) override;
    void visit(const std::shared_ptr<NamedDecl>& decl) override;
};
