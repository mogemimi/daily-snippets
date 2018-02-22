#pragma once

#include "Forward.h"
#include <memory>
#include <string>
#include <vector>

class Entity final {
private:
    std::weak_ptr<NamedDecl> decl;
    std::string name;

public:
    Entity(const std::string& name, const std::shared_ptr<NamedDecl>& decl);

    std::shared_ptr<NamedDecl> getDecl() const;
    std::string getName() const;
};
