#include "TypeInferer.h"
#include "Decl.h"
#include "Entity.h"
#include "Expr.h"
#include "IdentifierResolver.h"
#include "Stmt.h"
#include <cassert>
#include <sstream>
#include <unordered_set>
#include <utility>

namespace {

std::shared_ptr<Type> fresh(
    TypeEnvironment& env,
    std::unordered_set<TypeID>& processed,
    std::unordered_set<std::shared_ptr<Type>>& processedTypes,
    const std::shared_ptr<Type>& type);

std::shared_ptr<Type> prune(const std::shared_ptr<Type>& type)
{
    assert(type);
    if (type->getKind() == TypeKind::TypeVariable) {
        auto typeVariable = std::static_pointer_cast<TypeVariable>(type);
        assert(typeVariable == std::dynamic_pointer_cast<TypeVariable>(type));
        if (auto instance = typeVariable->getType()) {
            return instance;
        }
    }
    return type;
}

std::shared_ptr<Type> instantiate(
    TypeEnvironment& env,
    std::unordered_set<TypeID>& processed,
    std::unordered_set<std::shared_ptr<Type>>& processedTypes,
    const std::shared_ptr<ReturnType>& ret)
{
    const auto callable = fresh(env, processed, processedTypes, ret->callableType);

    assert(callable);
    if (callable->getKind() != TypeKind::FunctionType) {
        return ret;
    }
    if (processedTypes.find(callable) != std::end(processedTypes)) {
        // NOTE: recursive calls
        return BuiltinType::make(BuiltinTypeKind::Any);
    }
    processedTypes.emplace(callable);

    const auto function = std::static_pointer_cast<FunctionType>(callable);
    assert(function == std::dynamic_pointer_cast<FunctionType>(callable));

    if (function->parameterTypes.size() != ret->argumentTypes.size()) {
        // TODO: need to handle error
        std::printf("too few arguments to function '%s'\n", function->dump().c_str());
        return ret;
    }

    for (size_t i = 0; i < function->parameterTypes.size(); ++i) {
        assert(i < function->parameterTypes.size());
        assert(i < ret->argumentTypes.size());

        const auto param = fresh(env, processed, processedTypes, function->parameterTypes[i]);

        if (param->getKind() == TypeKind::TypeVariable) {
            auto v = std::static_pointer_cast<TypeVariable>(param);
            assert(v == std::dynamic_pointer_cast<TypeVariable>(param));
            auto arg = fresh(env, processed, processedTypes, ret->argumentTypes[i]);
            env.variables.emplace(v->getTypeID(), arg);
        }
    }

    return fresh(env, processed, processedTypes, function->returnType);
}

void unify(TypeEnvironment& env, const std::shared_ptr<Type>& t1, const std::shared_ptr<Type>& t2)
{
    assert(t1);
    assert(t2);

    if (t1->getKind() == TypeKind::TypeVariable) {
        const auto v = std::static_pointer_cast<TypeVariable>(t1);
        assert(v == std::dynamic_pointer_cast<TypeVariable>(t1));
        env.variables.emplace(v->getTypeID(), t2);
    }
}

std::shared_ptr<Type> fresh(
    TypeEnvironment& env,
    std::unordered_set<TypeID>& processed,
    std::unordered_set<std::shared_ptr<Type>>& processedTypes,
    const std::shared_ptr<Type>& type)
{
    assert(type);

    switch (type->getKind()) {
    case TypeKind::TypeVariable: {
        auto v = std::static_pointer_cast<TypeVariable>(type);
        assert(v == std::dynamic_pointer_cast<TypeVariable>(type));
        auto iter = env.variables.find(v->getTypeID());
        if (iter != std::end(env.variables)) {
            assert(iter->second);
            return iter->second;
        }

        auto pruned = prune(v);
        if (pruned == type) {
            return pruned;
        }
        unify(env, v, pruned);

        if (processed.find(v->getTypeID()) != std::end(processed)) {
            // NOTE: This type definition has a circular dependency.
            return pruned;
        }
        processed.emplace(v->getTypeID());
        return fresh(env, processed, processedTypes, pruned);
        break;
    }
    case TypeKind::BuiltinType: {
        auto t = std::static_pointer_cast<BuiltinType>(type);
        assert(t == std::dynamic_pointer_cast<BuiltinType>(type));
        return t;
        break;
    }
    case TypeKind::ReturnType: {
        auto ret = std::static_pointer_cast<ReturnType>(type);
        assert(ret == std::dynamic_pointer_cast<ReturnType>(type));
        TypeEnvironment innerEnv = env;
        auto result = instantiate(innerEnv, processed, processedTypes, ret);
        return result;
        break;
    }
    case TypeKind::FunctionType: {
        break;
    }
    }
    return type;
}

} // end of anonymous namespace

std::shared_ptr<Type> TypeInferer::infer(TypeEnvironment& env, const std::shared_ptr<Type>& type)
{
    assert(type);
    std::unordered_set<TypeID> processed;
    std::unordered_set<std::shared_ptr<Type>> processedTypes;
    return fresh(env, processed, processedTypes, type);
}
