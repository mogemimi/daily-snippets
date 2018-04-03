#pragma once

#include <cstdint>

enum class Opcode : std::int8_t {
    Exit = 0,

    Label,

    DefineVariable,
    LoadVariable,
    StoreVariable,

    // JumpIf,
    JumpIfNot,

    Add,
    Sub,
    Mul,
    Div,
    Mod,

    CompareEqual,
    CompareNotEqual,
    CompareLessThan,
    CompareLessThanOrEqual,
    CompareGreaterThan,
    CompareGreaterThanOrEqual,

    // operand: int64
    ConstantInt64,
    ConstantDouble,
    ConstantBool,
    ConstantString,
    ConstantNull,

    TypeCastFromInt64ToDouble,
};
