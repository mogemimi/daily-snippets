#pragma once

#include <cstdint>

enum class Opcode : int8_t {
    Exit = 0,

    Load, // Store,
    //JumpIf,
    JumpIfNot,

    Add,
    Sub,
    Mul,
    Div,

    CompareLessThan,
    CompareLessThanOrEqual,
    CompareGreaterThan,
    CompareGreaterThanOrEqual,
    CompareEqual,

    // operand: int64
    ConstantInt64,
    ConstantDouble,
    ConstantBool,
    ConstantString,
};
