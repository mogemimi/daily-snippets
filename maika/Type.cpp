#include "Type.h"

std::string TypeVariable::dump() const
{
    if (type) {
        return type->dump();
    }
    return "<" + std::to_string(index) + ">";
}

TypeIndex TypeVariable::getTypeIndex() const
{
    return index;
}

void TypeVariable::setType(const std::shared_ptr<const Type>& typeIn)
{
    type = typeIn;
}

std::shared_ptr<const Type> TypeVariable::getType() const
{
    return type;
}

std::shared_ptr<TypeVariable> TypeVariable::make(TypeIndex index)
{
    auto type = std::make_shared<TypeVariable>();
    type->index = index;
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

std::string FunctionType::dump() const
{
    assert(returnType);

    std::string params;
    bool needToSpace = false;
    for (const auto& param : parameterTypes) {
        if (needToSpace) {
            params += " ";
        }
        params += param->dump();
        needToSpace = true;
    }
    if (parameterTypes.empty()) {
        params = "void";
    }

    return "(" + params + ") -> (" + returnType->dump() + ")";
}

std::shared_ptr<FunctionType> FunctionType::make()
{
    auto type = std::make_shared<FunctionType>();

    // TODO: Not implemented
    type->returnType = BuiltinType::make(BuiltinTypeKind::Void);

    return type;
}

TypeEnvironment::TypeEnvironment()
{
}

TypeEnvironment::TypeEnvironment(const std::shared_ptr<const TypeEnvironment>& parentIn)
    : parent(parentIn)
{
}

TypeIndex TypeEnvironment::getNextIndex()
{
    static TypeIndex nextIndex = 100;
    ++nextIndex;
    return nextIndex;
}

std::shared_ptr<const TypeEnvironment> TypeEnvironment::getParent() const
{
    return parent;
}

std::shared_ptr<Type> TypeEnvironment::getType(const std::string& name) const
{
    auto iter = typeDefinitions.find(name);
    if (iter != std::end(typeDefinitions)) {
        return iter->second;
    }
    if (parent) {
        return parent->getType(name);
    }
    return nullptr;
}

void TypeEnvironment::defineType(const std::string& name, const std::shared_ptr<Type>& type)
{
    assert(type);
    typeDefinitions.emplace(name, type);
}
