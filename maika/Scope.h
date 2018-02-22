#pragma once

#include "Forward.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

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
