#include "TypeInferer.h"
#include "Decl.h"
#include "Entity.h"
#include "Expr.h"
#include "IdentifierResolver.h"
#include "Stmt.h"
#include <cassert>
#include <sstream>
#include <utility>

namespace {

std::shared_ptr<Type> prune(const std::shared_ptr<Type>& type)
{
    auto typeVariable = std::dynamic_pointer_cast<TypeVariable>(type);
    if (typeVariable) {
        if (auto instance = typeVariable->getType()) {
            return instance;
        }
    }
    return type;
}

std::shared_ptr<Type> substitution(const std::shared_ptr<Type>& type)
{
    // TODO: check DAG (directed acyclic graph), not cycle graph.
    auto prev = type;
    auto next = prune(prev);
    while (prev != next) {
        std::swap(next, prev);
        next = prune(prev);
    }
    return next;
}

// std::shared_ptr<const Type> unify(const std::shared_ptr<const Type>& type)
//{
//    const auto typeVariable = std::dynamic_pointer_cast<const TypeVariable>(type);
//    if (!typeVariable) {
//        return type;
//    }
//
//    auto t = typeVariable;
//    while (t) {
//        const auto a = t->getType();
//        const auto v = std::dynamic_pointer_cast<const TypeVariable>(a);
//        if (!v) {
//            return a;
//        }
//        t = v;
//        assert(t != typeVariable);
//    }
//    return t;
//}

std::shared_ptr<Type> instantiate(TypeEnvironment& env, const std::shared_ptr<ReturnType>& ret)
{
    auto callable = TypeInferer::infer(env, ret->callableType);
    auto function = std::dynamic_pointer_cast<FunctionType>(callable);
    if (!function) {
        return ret;
    }

    if (function->parameterTypes.size() != ret->argumentTypes.size()) {
        // TODO: need to handle error
        std::printf("too few arguments to function '%s'\n", function->dump().c_str());
        return ret;
    }

    for (size_t i = 0; i < function->parameterTypes.size(); ++i) {
        auto param = TypeInferer::infer(env, function->parameterTypes[i]);
        if (auto v = std::dynamic_pointer_cast<TypeVariable>(param)) {
            auto arg = TypeInferer::infer(env, ret->argumentTypes[i]);
            env.variables.emplace(v->getTypeID(), arg);
        }
    }

    return TypeInferer::infer(env, function->returnType);
}

void unify(TypeEnvironment& env, const std::shared_ptr<Type>& t1, const std::shared_ptr<Type>& t2)
{
    if (auto v = std::dynamic_pointer_cast<TypeVariable>(t1)) {
        env.variables.emplace(v->getTypeID(), t2);
    }
}

} // end of anonymous namespace

std::shared_ptr<Type> TypeInferer::infer(TypeEnvironment& env, const std::shared_ptr<Type>& type)
{
    assert(type);

    const auto t = substitution(type);

    if (auto v = std::dynamic_pointer_cast<BuiltinType>(t)) {
        unify(env, type, v);
        return v;
    }

    if (auto v = std::dynamic_pointer_cast<TypeVariable>(t)) {
        auto iter = env.variables.find(v->getTypeID());
        if (iter != std::end(env.variables)) {
            assert(iter->second);
            return iter->second;
        }
        return v;
    }

    if (auto ret = std::dynamic_pointer_cast<ReturnType>(t)) {
        TypeEnvironment innerEnv = env;
        auto result = instantiate(innerEnv, ret);
        unify(env, type, result);
        return result;
    }

    return t;
}
