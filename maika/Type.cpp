#include "Type.h"

namespace {

std::string stringify(const std::vector<std::shared_ptr<Type>>& types)
{
    std::string result;
    bool needToInsertComma = false;
    for (const auto& t : types) {
        if (needToInsertComma) {
            result += ", ";
        }
        assert(t);
        result += t->dump();
        needToInsertComma = true;
    }
    return result;
}

} // end of anonymous namespace

std::string FunctionType::dump() const
{
    return stringify(parameterTypes) + " -> " + returnType->dump();
}

std::shared_ptr<FunctionType>
FunctionType::make(const std::shared_ptr<Type>& to, const std::vector<std::shared_ptr<Type>>& from)
{
    auto type = std::make_shared<FunctionType>();
    type->returnType = to;
    type->parameterTypes = from;
    return type;
}

std::string ReturnType::dump() const
{
    return "((" + callableType->dump() + ")(" + stringify(argumentTypes) + "))";
}

std::shared_ptr<ReturnType> ReturnType::make(
    const std::shared_ptr<Type>& callableType,
    const std::vector<std::shared_ptr<Type>>& argumentTypes)
{
    auto type = std::make_shared<ReturnType>();
    type->callableType = callableType;
    type->argumentTypes = argumentTypes;
    return type;
}

std::string TypeVariable::dump() const
{
    //    if (instance) {
    //        return instance->dump();
    //    }
    return "<" + std::to_string(id) + ">";
}

TypeID TypeVariable::getTypeID() const
{
    return id;
}

std::shared_ptr<Type> TypeVariable::getType() const
{
    return instance;
}

void TypeVariable::setType(const std::shared_ptr<Type>& typeIn)
{
    assert(typeIn);
    instance = typeIn;
}

std::shared_ptr<TypeVariable> TypeVariable::make()
{
    static TypeID nextID = 100;
    ++nextID;

    auto type = std::make_shared<TypeVariable>();
    type->id = nextID;
    return type;
}

std::string BuiltinType::dump() const
{
    switch (kind) {
    case BuiltinTypeKind::Bool: return "bool";
    case BuiltinTypeKind::Int: return "int";
    case BuiltinTypeKind::Double: return "double";
    case BuiltinTypeKind::Void: return "void";
    case BuiltinTypeKind::Any: return "any";
    }
    return "builtin";
}

std::shared_ptr<BuiltinType> BuiltinType::make(BuiltinTypeKind kind)
{
    auto type = std::make_shared<BuiltinType>();
    type->kind = kind;
    return type;
}

TypeScope::TypeScope(const std::shared_ptr<const TypeScope>& parentIn)
    : parent(parentIn)
{
}

std::shared_ptr<const TypeScope> TypeScope::getParent() const
{
    return parent;
}

std::shared_ptr<Type> TypeScope::getType(const std::string& name) const
{
    auto iter = types.find(name);
    if (iter != std::end(types)) {
        return iter->second;
    }
    if (parent) {
        return parent->getType(name);
    }
    return nullptr;
}

void TypeScope::defineType(const std::string& name, const std::shared_ptr<Type>& type)
{
    assert(type);
    types.emplace(name, type);
}

TypeEnvironment::TypeEnvironment()
{
    identifiers = std::make_shared<TypeScope>();
    aliases = std::make_shared<TypeScope>();
}

TypeEnvironment::TypeEnvironment(const std::shared_ptr<TypeEnvironment>& parent)
{
    assert(parent);
    assert(parent->identifiers);
    assert(parent->aliases);
    identifiers = std::make_shared<TypeScope>(parent->identifiers);
    aliases = std::make_shared<TypeScope>(parent->aliases);
}

std::shared_ptr<Type> TypeEnvironment::getIdent(const std::string& name) const
{
    assert(identifiers);
    return identifiers->getType(name);
}

std::shared_ptr<Type> TypeEnvironment::getAlias(const std::string& name) const
{
    assert(aliases);
    return aliases->getType(name);
}

void TypeEnvironment::defineIdent(const std::string& name, const std::shared_ptr<Type>& type)
{
    assert(type);
    assert(!name.empty());
    assert(identifiers);
    return identifiers->defineType(name, type);
}

void TypeEnvironment::defineAlias(const std::string& name, const std::shared_ptr<Type>& type)
{
    assert(type);
    assert(!name.empty());
    assert(aliases);
    return aliases->defineType(name, type);
}
