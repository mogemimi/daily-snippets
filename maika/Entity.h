#pragma once

#include "Forward.h"
#include <memory>
#include <string>
#include <vector>

enum class EntityKind {
    Type,
    Variable,
};

class Entity final {
private:
    std::string name;
    std::weak_ptr<NamedDecl> decl;
    std::shared_ptr<Type> type;
    EntityKind kind;

public:
    Entity(const std::string& name, const std::shared_ptr<NamedDecl>& decl);

    Entity(const std::string& name, const std::shared_ptr<Type>& type);

    EntityKind getKind() const;

    std::string getName() const;

    std::shared_ptr<NamedDecl> getDecl() const;

    std::shared_ptr<Type> getType() const;
};
