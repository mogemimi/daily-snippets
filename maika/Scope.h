#pragma once

#include "Forward.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Scope final {
private:
    std::shared_ptr<const Scope> parent;
    std::unordered_map<std::string, std::shared_ptr<Entity>> variables;

public:
    Scope() = default;
    explicit Scope(const std::shared_ptr<const Scope>& parentIn);

    std::shared_ptr<const Scope> getParent() const;

    std::shared_ptr<Entity> getEntity(const std::string& name) const;

    void defineVariable(const std::shared_ptr<Entity>& v);
};
