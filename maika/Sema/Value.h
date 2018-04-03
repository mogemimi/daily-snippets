#pragma once

#include "Basic/Forward.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

enum class ValueKind : std::uint8_t {
    Int64,
    Double,
    Bool,
    String,
    // Object,
    // Array,
    // Map,
    Null,
};

class Value {
public:
    virtual ~Value() = default;

    virtual ValueKind getKind() const noexcept = 0;
};

class Int64Value final : public Value {
private:
    int64_t value;

public:
    explicit Int64Value(int64_t v)
        : value(v)
    {
    }

    ValueKind getKind() const noexcept { return ValueKind::Int64; }

    void setValue(int64_t v) noexcept { value = v; }

    int64_t getValue() const noexcept { return value; }
};

class DoubleValue final : public Value {
private:
    double value;

public:
    explicit DoubleValue(double v)
        : value(v)
    {
    }

    ValueKind getKind() const noexcept { return ValueKind::Double; }

    void setValue(double v) noexcept { value = v; }

    double getValue() const noexcept { return value; }
};

class StringValue final : public Value {
private:
    std::string value;

public:
    explicit StringValue(const std::string& v)
        : value(v)
    {
    }

    ValueKind getKind() const noexcept { return ValueKind::String; }

    void setValue(const std::string& v) { value = v; }

    std::string getValue() const { return value; }
};

class BoolValue final : public Value {
private:
    bool value;

public:
    explicit BoolValue(bool v)
        : value(v)
    {
    }

    ValueKind getKind() const noexcept { return ValueKind::Bool; }

    void setValue(bool v) noexcept { value = v; }

    bool getValue() const noexcept { return value; }
};

class NullValue final : public Value {
public:
    ValueKind getKind() const noexcept { return ValueKind::Null; }
};

// TODO: move other header file
template <typename To, typename From>
std::unique_ptr<To> StaticUniquePointerCast(std::unique_ptr<From>&& old)
{
    std::unique_ptr<To> p{static_cast<To*>(old.release())};
    return p;
}
