#pragma once

#include "Basic/Forward.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Scope final {
private:
    std::shared_ptr<const Scope> outer;
    std::unordered_map<std::string, std::shared_ptr<Entity>> variables;

public:
    Scope() = default;
    explicit Scope(const std::shared_ptr<const Scope>& outer);

    std::shared_ptr<const Scope> getOuter() const;

    std::shared_ptr<Entity> lookup(const std::string& name) const;

    std::shared_ptr<Entity> findAlt(const std::string& name) const;

    void insert(const std::shared_ptr<Entity>& v);
};
