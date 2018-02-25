#pragma once

#include <cassert>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Type {
public:
    virtual ~Type() = default;
    virtual std::string dump() const = 0;
};

class FunctionType final : public Type {
private:
    std::shared_ptr<Type> returnType;
    std::vector<std::shared_ptr<Type>> parameterTypes;

public:
    std::string dump() const override;

    static std::shared_ptr<FunctionType>
    make(const std::shared_ptr<Type>& to, const std::vector<std::shared_ptr<Type>>& from);
};

class ReturnType final : public Type {
private:
    std::shared_ptr<Type> callableType;
    std::vector<std::shared_ptr<Type>> argumentTypes;

public:
    std::string dump() const override;

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

    static std::shared_ptr<BuiltinType> make(BuiltinTypeKind kind);
};

class TypeScope final {
private:
    std::shared_ptr<const TypeScope> parent;
    std::unordered_map<std::string, std::shared_ptr<Type>> types;

public:
    TypeScope() = default;
    explicit TypeScope(const std::shared_ptr<const TypeScope>& parentIn);

    std::shared_ptr<const TypeScope> getParent() const;

    std::shared_ptr<Type> getType(const std::string& name) const;

    void defineType(const std::string& name, const std::shared_ptr<Type>& type);
};

class TypeEnvironment final {
private:
    std::shared_ptr<TypeScope> identifiers;
    std::shared_ptr<TypeScope> aliases;

public:
    std::vector<std::shared_ptr<Type>> returnTypes;

public:
    TypeEnvironment();
    explicit TypeEnvironment(const std::shared_ptr<TypeEnvironment>& parentIn);

    std::shared_ptr<Type> getIdent(const std::string& name) const;

    std::shared_ptr<Type> getAlias(const std::string& name) const;

    void defineIdent(const std::string& name, const std::shared_ptr<Type>& type);

    void defineAlias(const std::string& name, const std::shared_ptr<Type>& type);
};
