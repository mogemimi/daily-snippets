#pragma once

#include "Forward.h"
#include <memory>
#include <string>
#include <vector>

enum class EntityKind {
    Type,
    Variable,
    Constant,
};

class Entity final {
private:
    std::string name;
    std::weak_ptr<NamedDecl> decl;
    std::shared_ptr<Type> type;
    EntityKind kind;

public:
    EntityKind getKind() const;

    std::string getName() const;

    std::shared_ptr<NamedDecl> getDecl() const;

    std::shared_ptr<Type> getType() const;

    static std::shared_ptr<Entity>
    makeVariable(const std::string& name, const std::shared_ptr<NamedDecl>& decl);

    static std::shared_ptr<Entity>
    makeConst(const std::string& name, const std::shared_ptr<NamedDecl>& decl);

    static std::shared_ptr<Entity>
    makeType(const std::string& name, const std::shared_ptr<Type>& type);
};
