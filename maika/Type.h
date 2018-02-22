#pragma once

#include <memory>
#include <string>

enum class BuiltinTypeKind {
    // Int32,
    // Int64,
    // UInt32,
    // UInt64,
    Bool,
    Int,
    Double,
    // String,
};

enum class TypeKind {
    Any,
    BuiltinTypeKind,
};

class Type {
public:
    virtual ~Type() = default;
    virtual std::string dump() const = 0;
};

class AnyType final : public Type {
public:
    std::string dump() const override { return "any"; }

    static std::shared_ptr<AnyType> make()
    {
        auto type = std::make_shared<AnyType>();
        return type;
    }
};

class FunctionType final : public Type {
public:
    std::string dump() const override { return "function()"; }

    static std::shared_ptr<FunctionType> make()
    {
        auto type = std::make_shared<FunctionType>();
        return type;
    }
};

using TypeVariableIndex = uint64_t;

// class TypeVariable final : public Type {
// private:
//    TypeVariableIndex index;
//
// public:
//    std::string dump() const override
//    {
//        return "T(" + std::to_string(index) + ")";
//    }
//
//    static std::shared_ptr<TypeVariable> make()
//    {
//        static TypeVariableIndex typeIndexCounter = 10000;
//        ++typeIndexCounter;
//
//        auto type = std::make_shared<TypeVariable>();
//        type->index = typeIndexCounter;
//        return type;
//    }
//};

class BuiltinType final : public Type {
public:
    BuiltinTypeKind kind;

    std::string dump() const override
    {
        switch (kind) {
        case BuiltinTypeKind::Bool: return "bool";
        case BuiltinTypeKind::Int: return "int";
        case BuiltinTypeKind::Double: return "double";
        }
        return "builtin";
    }

    static std::shared_ptr<BuiltinType> make(BuiltinTypeKind kind)
    {
        auto type = std::make_shared<BuiltinType>();
        type->kind = kind;
        return type;
    }
};
