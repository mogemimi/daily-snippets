#pragma once

#include "CodeGen/Opcode.h"
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

class Instruction final {
public:
    Opcode opcode : 8;
    std::int32_t operand : 32;

    // TODO: unused member variable:
    // std::int32_t location : 24;

    Opcode getOpcode() const { return opcode; }

    std::int32_t getOperand() const { return operand; }

    bool isBinaryOp() const;
};

struct BytecodeProgram final {
    std::vector<int64_t> int64Constants;
    std::vector<double> doubleConstants;
    std::vector<std::string> stringConstants;
    std::vector<std::shared_ptr<Instruction>> instructions;
};
