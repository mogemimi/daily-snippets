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
