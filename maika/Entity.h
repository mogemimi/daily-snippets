#pragma once

#include "Forward.h"
#include <string>
#include <vector>
#include <memory>

class Entity final {
private:
    std::weak_ptr<Decl> decl;
    std::string name;

public:
    Entity(const std::string& name, const std::shared_ptr<Decl>& decl);

    std::shared_ptr<Decl> getDecl() const;
    std::string getName() const;
};
