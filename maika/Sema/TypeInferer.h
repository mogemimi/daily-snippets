#pragma once

#include "AST/ASTVisitor.h"
#include "AST/Type.h"
#include "Basic/Forward.h"
#include "Parser/location.hh"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

struct TypeEnvironment {
    std::unordered_map<TypeID, std::shared_ptr<Type>> variables;
};

class TypeInferer final {
public:
    static std::shared_ptr<Type> infer(TypeEnvironment& env, const std::shared_ptr<Type>& type);
};
