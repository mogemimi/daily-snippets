#pragma once

#include <cassert>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

enum class TypeKind {
    FunctionType,
    ReturnType,
    TypeVariable,
    BuiltinType,
};

class Type {
public:
    virtual ~Type() = default;
    virtual std::string dump() const = 0;
    virtual TypeKind getKind() const = 0;
};

class FunctionType final : public Type {
public:
    std::shared_ptr<Type> returnType;
    std::vector<std::shared_ptr<Type>> parameterTypes;

public:
    std::string dump() const override;

    TypeKind getKind() const override;

    static std::shared_ptr<FunctionType>
    make(const std::shared_ptr<Type>& to, const std::vector<std::shared_ptr<Type>>& from);
};

class ReturnType final : public Type {
public:
    std::shared_ptr<Type> callableType;
    std::vector<std::shared_ptr<Type>> argumentTypes;

public:
    std::string dump() const override;

    TypeKind getKind() const override;

    static std::shared_ptr<ReturnType> make(
        const std::shared_ptr<Type>& callableType,
        const std::vector<std::shared_ptr<Type>>& argumentTypes);
};

using TypeID = uint64_t;

class TypeVariable final : public Type {
private:
    std::shared_ptr<Type> instance;
    TypeID id;

public:
    std::string dump() const override;

    TypeKind getKind() const override;

    TypeID getTypeID() const;

    std::shared_ptr<Type> getType() const;
    void setType(const std::shared_ptr<Type>& type);

    static std::shared_ptr<TypeVariable> make();
};

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
    Any,
};

class BuiltinType final : public Type {
public:
    BuiltinTypeKind kind;

    std::string dump() const override;

    TypeKind getKind() const override;

    static std::shared_ptr<BuiltinType> make(BuiltinTypeKind kind);
};
