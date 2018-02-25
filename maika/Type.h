#pragma once

#include <cassert>
#include <memory>
#include <string>
#include <unordered_map>
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
    Any,
};

using TypeIndex = uint64_t;

class Type {
public:
    virtual ~Type() = default;
    virtual std::string dump() const = 0;
    // virtual TypeIndex getTypeIndex() const = 0;
};

class TypeVariable final : public Type {
private:
    TypeIndex index;
    std::shared_ptr<const Type> type;

public:
    std::string dump() const override;
    TypeIndex getTypeIndex() const;

    void setType(const std::shared_ptr<const Type>& type);
    std::shared_ptr<const Type> getType() const;

    static std::shared_ptr<TypeVariable> make(TypeIndex index);
};

class BuiltinType final : public Type {
public:
    BuiltinTypeKind kind;

    std::string dump() const override;

    static std::shared_ptr<BuiltinType> make(BuiltinTypeKind kind);
};

class FunctionType final : public Type {
public:
    std::shared_ptr<const Type> returnType; // TODO: tuple
    std::vector<std::shared_ptr<const Type>> parameterTypes;

    std::string dump() const override;

    static std::shared_ptr<FunctionType> make();
};

class TypeEnvironment final {
private:
    std::shared_ptr<const TypeEnvironment> parent;
    std::unordered_map<TypeIndex, TypeIndex> typeIndices;
    std::unordered_map<std::string, std::shared_ptr<Type>> typeDefinitions;

public:
    TypeEnvironment();
    explicit TypeEnvironment(const std::shared_ptr<const TypeEnvironment>& parentIn);

    TypeIndex getNextIndex();

    std::shared_ptr<const TypeEnvironment> getParent() const;

    std::shared_ptr<Type> getType(const std::string& name) const;

    void defineType(const std::string& name, const std::shared_ptr<Type>& type);
};
