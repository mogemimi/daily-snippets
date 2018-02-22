#pragma once

#include <cassert>
#include <memory>
#include <string>
#include <vector>

enum class BuiltinTypeKind {
    // Int32,
    // Int64,
    // UInt32,
    // UInt64,
    Bool,
    Int,
    Double,
    // String,
    Void,
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

using TypeVariableIndex = uint64_t;

class TypeVariable final : public Type {
private:
    TypeVariableIndex index;
    std::shared_ptr<const Type> type;

public:
    std::string dump() const override
    {
        if (type) {
            return type->dump();
        }
        return "T(" + std::to_string(index) + ")";
    }

    void setType(const std::shared_ptr<const Type>& t)
    {
        assert(t);
        assert(!this->type);
        assert(!std::dynamic_pointer_cast<const TypeVariable>(type));
        this->type = t;
    }

    static std::shared_ptr<TypeVariable> make()
    {
        static TypeVariableIndex typeIndexCounter = 10000;
        ++typeIndexCounter;

        auto type = std::make_shared<TypeVariable>();
        type->index = typeIndexCounter;
        return type;
    }
};

class BuiltinType final : public Type {
public:
    BuiltinTypeKind kind;

    std::string dump() const override
    {
        switch (kind) {
        case BuiltinTypeKind::Bool: return "bool";
        case BuiltinTypeKind::Int: return "int";
        case BuiltinTypeKind::Double: return "double";
        case BuiltinTypeKind::Void: return "void";
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

class FunctionType final : public Type {
public:
    std::shared_ptr<const Type> returnType;                  // TODO: tuple
    std::vector<std::shared_ptr<const Type>> parameterTypes; // TODO: tuple

    std::string dump() const override
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

        return "(" + params + ") => (" + returnType->dump() + ")";
    }

    static std::shared_ptr<FunctionType> make()
    {
        auto type = std::make_shared<FunctionType>();

        // TODO: Not implemented
        type->returnType = BuiltinType::make(BuiltinTypeKind::Void);

        return type;
    }
};
