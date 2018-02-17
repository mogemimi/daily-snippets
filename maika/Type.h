#pragma once

#include <memory>

enum class BuiltinTypeKind {
    //Int32,
    //Int64,
    //UInt32,
    //UInt64,
    Bool,
    Int,
    Double,
    //String,
};

enum class TypeKind {
    Any,
    BuiltinTypeKind,
};

class Type {
public:
    virtual ~Type() = default;
};

class AnyType final : public Type {
public:
    static std::shared_ptr<AnyType> make()
    {
        auto type = std::make_shared<AnyType>();
        return type;
    }
};

class TypeVariable final : public Type {
public:
    static std::shared_ptr<TypeVariable> make()
    {
        auto type = std::make_shared<TypeVariable>();
        return type;
    }
};

class BuiltinType final : public Type {
public:
    BuiltinTypeKind kind;

    static std::shared_ptr<BuiltinType> make(BuiltinTypeKind kind)
    {
        auto type = std::make_shared<BuiltinType>();
        type->kind = kind;
        return type;
    }
};
