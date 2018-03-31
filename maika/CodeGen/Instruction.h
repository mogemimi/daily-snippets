#pragma once

#include "CodeGen/Opcode.h"
#include <cstdint>
#include <memory>
#include <string>

enum class ValueKind {
    Int64,
    Double,
    Bool,
    String,
    // Object,
    // Array,
    // Map,
    // None,
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
    explicit Int64Value(int64_t v) : value(v) {}

    ValueKind getKind() const noexcept { return ValueKind::Int64; }

    void setValue(int64_t v) { value = v; }

    int64_t getValue() const { return value; }
};

class DoubleValue final : public Value {
private:
    double value;

public:
    explicit DoubleValue(double v) : value(v) {}

    ValueKind getKind() const noexcept { return ValueKind::Double; }

    void setValue(double v) { value = v; }

    double getValue() const { return value; }
};

class StringValue final : public Value {
private:
    std::string value;

public:
    explicit StringValue(const std::string& v) : value(v) {}

    ValueKind getKind() const noexcept { return ValueKind::String; }

    void setValue(const std::string& v) { value = v; }

    std::string getValue() const { return value; }
};

class BoolValue final : public Value {
private:
    bool value;

public:
    explicit BoolValue(bool v) : value(v) {}

    ValueKind getKind() const noexcept { return ValueKind::Bool; }

    void setValue(bool v) { value = v; }

    bool getValue() const { return value; }
};

class Instruction final {
public:
    Opcode opcode;
    std::shared_ptr<Value> operand;

    Opcode getOpcode() const { return opcode; }

    bool isBinaryOp() const;
};
