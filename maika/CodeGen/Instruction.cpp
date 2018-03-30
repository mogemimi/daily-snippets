#include "CodeGen/Instruction.h"

namespace {

bool isBinaryOp(Opcode opcode) noexcept
{
    switch (opcode) {
    case Opcode::Add:
    case Opcode::Sub:
    case Opcode::Mul:
    case Opcode::Div:
    case Opcode::CompareEqual:
    case Opcode::CompareGreaterThan:
    case Opcode::CompareGreaterThanOrEqual:
    case Opcode::CompareLessThan:
    case Opcode::CompareLessThanOrEqual:
        return true;
        break;
    default:
        break;
    }
    return false;
}

} // end of anonymous namespace

bool Instruction::isBinaryOp() const
{
    return ::isBinaryOp(opcode);
}
