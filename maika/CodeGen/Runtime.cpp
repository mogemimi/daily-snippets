#include "CodeGen/Runtime.h"
#include <cassert>

bool Runtime::run(const std::vector<std::shared_ptr<Instruction>>& instructions)
{
    for (auto & inst : instructions) {
        switch (inst->getOpcode()) {
        case Opcode::ConstantBool: {
            auto value = std::static_pointer_cast<BoolValue>(inst->operand);
            if (!value) {
                printf("%s\n", "runtime error");
                return false;
            }
            valueStack.push_back(value);
            break;
        }
        case Opcode::ConstantDouble: {
            auto value = std::static_pointer_cast<DoubleValue>(inst->operand);
            if (!value) {
                printf("%s\n", "runtime error");
                return false;
            }
            valueStack.push_back(value);
            break;
        }
        case Opcode::ConstantInt64: {
            auto value = std::static_pointer_cast<Int64Value>(inst->operand);
            if (!value) {
                printf("%s\n", "runtime error");
                return false;
            }
            valueStack.push_back(value);
            break;
        }
        case Opcode::ConstantString: {
            auto value = std::static_pointer_cast<StringValue>(inst->operand);
            if (!value) {
                printf("%s\n", "runtime error");
                return false;
            }
            valueStack.push_back(value);
            break;
        }
        case Opcode::Add: {
            if (valueStack.size() < 2) {
                printf("%s\n", "runtime error");
                return false;
            }
            auto rhs = valueStack.back();
            valueStack.pop_back();
            auto lhs = valueStack.back();
            valueStack.pop_back();

            if (lhs->getKind() != rhs->getKind()) {
                printf("%s\n", "runtime error: type mismatch");
                return false;
            }

            switch (lhs->getKind()) {
            case ValueKind::Int64: {
                auto a = std::static_pointer_cast<Int64Value>(lhs);
                assert(a);
                auto b = std::static_pointer_cast<Int64Value>(rhs);
                assert(b);
                auto v = a->getValue() + b->getValue();
                auto resultValue = std::make_shared<Int64Value>(v);
                valueStack.push_back(resultValue);
                break;
            }
            case ValueKind::Double: {
                auto a = std::static_pointer_cast<DoubleValue>(lhs);
                assert(a);
                auto b = std::static_pointer_cast<DoubleValue>(rhs);
                assert(b);
                auto v = a->getValue() + b->getValue();
                auto resultValue = std::make_shared<DoubleValue>(v);
                valueStack.push_back(resultValue);
                break;
            }
            case ValueKind::Bool: {
                // TODO: adding two bool values
                printf("%s\n", "warning: undefined behavior when adding two bool values.");
            
                auto a = std::static_pointer_cast<BoolValue>(lhs);
                assert(a);
                auto b = std::static_pointer_cast<BoolValue>(rhs);
                assert(b);
                auto v = a->getValue() + b->getValue();
                auto resultValue = std::make_shared<BoolValue>(v);
                valueStack.push_back(resultValue);
                break;
            }
            case ValueKind::String: {
                auto a = std::static_pointer_cast<StringValue>(lhs);
                assert(a);
                auto b = std::static_pointer_cast<StringValue>(rhs);
                assert(b);
                auto v = a->getValue() + b->getValue();
                auto resultValue = std::make_shared<StringValue>(v);
                valueStack.push_back(resultValue);
                break;
            }
            default:
                printf("%s\n", "runtime error: not implemented");
                return false;
            }
            break;
        }
        case Opcode::Sub: {
            if (valueStack.size() < 2) {
                printf("%s\n", "runtime error");
                return false;
            }
            auto rhs = valueStack.back();
            valueStack.pop_back();
            auto lhs = valueStack.back();
            valueStack.pop_back();

            if (lhs->getKind() != rhs->getKind()) {
                printf("%s\n", "runtime error: type mismatch");
                return false;
            }

            switch (lhs->getKind()) {
            case ValueKind::Int64: {
                auto a = std::static_pointer_cast<Int64Value>(lhs);
                assert(a);
                auto b = std::static_pointer_cast<Int64Value>(rhs);
                assert(b);
                auto v = a->getValue() - b->getValue();
                auto resultValue = std::make_shared<Int64Value>(v);
                valueStack.push_back(resultValue);
                break;
            }
            case ValueKind::Double: {
                auto a = std::static_pointer_cast<DoubleValue>(lhs);
                assert(a);
                auto b = std::static_pointer_cast<DoubleValue>(rhs);
                assert(b);
                auto v = a->getValue() - b->getValue();
                auto resultValue = std::make_shared<DoubleValue>(v);
                valueStack.push_back(resultValue);
                break;
            }
            case ValueKind::Bool: {
                // TODO: adding two bool values
                printf("%s\n", "warning: undefined behavior when subtracting two bool values.");
            
                auto a = std::static_pointer_cast<BoolValue>(lhs);
                assert(a);
                auto b = std::static_pointer_cast<BoolValue>(rhs);
                assert(b);
                auto v = a->getValue() - b->getValue();
                auto resultValue = std::make_shared<BoolValue>(v);
                valueStack.push_back(resultValue);
                break;
            }
            case ValueKind::String: {
                printf("%s\n", "runtime error: Cannot subtract two strings.");
                return false;
                break;
            }
            default:
                printf("%s\n", "runtime error: not implemented");
                return false;
            }
            break;
        }
        case Opcode::Mul: {
            if (valueStack.size() < 2) {
                printf("%s\n", "runtime error");
                return false;
            }
            auto rhs = valueStack.back();
            valueStack.pop_back();
            auto lhs = valueStack.back();
            valueStack.pop_back();

            if (lhs->getKind() != rhs->getKind()) {
                printf("%s\n", "runtime error: type mismatch");
                return false;
            }

            switch (lhs->getKind()) {
            case ValueKind::Int64: {
                auto a = std::static_pointer_cast<Int64Value>(lhs);
                assert(a);
                auto b = std::static_pointer_cast<Int64Value>(rhs);
                assert(b);
                auto v = a->getValue() * b->getValue();
                auto resultValue = std::make_shared<Int64Value>(v);
                valueStack.push_back(resultValue);
                break;
            }
            case ValueKind::Double: {
                auto a = std::static_pointer_cast<DoubleValue>(lhs);
                assert(a);
                auto b = std::static_pointer_cast<DoubleValue>(rhs);
                assert(b);
                auto v = a->getValue() * b->getValue();
                auto resultValue = std::make_shared<DoubleValue>(v);
                valueStack.push_back(resultValue);
                break;
            }
            case ValueKind::Bool: {
                // TODO: adding two bool values
                printf("%s\n", "warning: undefined behavior when multiplying two bool values.");
            
                auto a = std::static_pointer_cast<BoolValue>(lhs);
                assert(a);
                auto b = std::static_pointer_cast<BoolValue>(rhs);
                assert(b);
                auto v = a->getValue() * b->getValue();
                auto resultValue = std::make_shared<BoolValue>(v);
                valueStack.push_back(resultValue);
                break;
            }
            case ValueKind::String: {
                printf("%s\n", "runtime error: Cannot multiply two strings.");
                return false;
                break;
            }
            default:
                printf("%s\n", "runtime error: not implemented");
                return false;
            }
            break;
        }
        case Opcode::Div: {
            if (valueStack.size() < 2) {
                printf("%s\n", "runtime error");
                return false;
            }
            auto rhs = valueStack.back();
            valueStack.pop_back();
            auto lhs = valueStack.back();
            valueStack.pop_back();

            if (lhs->getKind() != rhs->getKind()) {
                printf("%s\n", "runtime error: type mismatch");
                return false;
            }

            switch (lhs->getKind()) {
            case ValueKind::Int64: {
                auto a = std::static_pointer_cast<Int64Value>(lhs);
                assert(a);
                auto b = std::static_pointer_cast<Int64Value>(rhs);
                assert(b);
                if (b->getValue() == 0) {
                    printf("%s\n", "runtime error: Division by zero");
                    return false;
                }
                auto v = a->getValue() / b->getValue();
                auto resultValue = std::make_shared<Int64Value>(v);
                valueStack.push_back(resultValue);
                break;
            }
            case ValueKind::Double: {
                auto a = std::static_pointer_cast<DoubleValue>(lhs);
                assert(a);
                auto b = std::static_pointer_cast<DoubleValue>(rhs);
                assert(b);
                if (b->getValue() == 0) {
                    printf("%s\n", "runtime error: Division by zero");
                    return false;
                }
                auto v = a->getValue() / b->getValue();
                auto resultValue = std::make_shared<DoubleValue>(v);
                valueStack.push_back(resultValue);
                break;
            }
            case ValueKind::Bool: {
                // TODO: adding two bool values
                printf("%s\n", "warning: undefined behavior when dividing two bool values.");
            
                auto a = std::static_pointer_cast<BoolValue>(lhs);
                assert(a);
                auto b = std::static_pointer_cast<BoolValue>(rhs);
                assert(b);
                if (b->getValue() == 0) {
                    printf("%s\n", "runtime error: Division by zero");
                    return false;
                }
                auto v = a->getValue() / b->getValue();
                auto resultValue = std::make_shared<BoolValue>(v);
                valueStack.push_back(resultValue);
                break;
            }
            case ValueKind::String: {
                printf("%s\n", "runtime error: Cannot divide two strings.");
                return false;
                break;
            }
            default:
                printf("%s\n", "runtime error: not implemented");
                return false;
            }
            break;
        }
        case Opcode::CompareEqual:
        case Opcode::CompareGreaterThan:
        case Opcode::CompareGreaterThanOrEqual:
        case Opcode::CompareLessThan:
        case Opcode::CompareLessThanOrEqual:
        default:
            break;
        }
    }
    return true;
}

std::string Runtime::getResultString() const
{
    if (valueStack.empty()) {
        return "";
    }

    auto result = valueStack.back();

    switch (result->getKind()) {
    case ValueKind::Int64: {
        auto v = std::static_pointer_cast<Int64Value>(result);
        return std::to_string(v->getValue());
        break;
    }
    case ValueKind::Double: {
        auto v = std::static_pointer_cast<DoubleValue>(result);
        return std::to_string(v->getValue());
        break;
    }
    case ValueKind::Bool: {
        auto v = std::static_pointer_cast<BoolValue>(result);
        return (v->getValue() ? "true" : "false");
        break;
    }
    case ValueKind::String: {
        auto v = std::static_pointer_cast<StringValue>(result);
        return v->getValue();
        break;
    }
    }

    return "";
}

void Runtime::dump(const std::vector<std::shared_ptr<Instruction>>& instructions)
{
    for (auto & inst : instructions) {
        switch (inst->getOpcode()) {
        case Opcode::ConstantBool: {
            auto value = std::static_pointer_cast<BoolValue>(inst->operand);
            assert(value);
            auto s = value->getValue() ? "true" : "false";
            printf("%s %s\n", "bool", s);
            break;
        }
        case Opcode::ConstantDouble: {
            auto value = std::static_pointer_cast<DoubleValue>(inst->operand);
            assert(value);
            auto s = std::to_string(value->getValue());
            printf("%s %s\n", "double", s.c_str());
            break;
        }
        case Opcode::ConstantInt64: {
            auto value = std::static_pointer_cast<Int64Value>(inst->operand);
            assert(value);
            auto s = std::to_string(value->getValue());
            printf("%s %s\n", "int64", s.c_str());
            break;
        }
        case Opcode::ConstantString: {
            auto value = std::static_pointer_cast<StringValue>(inst->operand);
            assert(value);
            auto s = value->getValue();
            printf("%s %s\n", "double", s.c_str());
            break;
        }
        case Opcode::Add: {
            printf("%s\n", "add");
            break;
        }
        case Opcode::Sub: {
            printf("%s\n", "sub");
            break;
        }
        case Opcode::Mul: {
            printf("%s\n", "mul");
            break;
        }
        case Opcode::Div: {
            printf("%s\n", "div");
            break;
        }
        case Opcode::CompareEqual:
        case Opcode::CompareGreaterThan:
        case Opcode::CompareGreaterThanOrEqual:
        case Opcode::CompareLessThan:
        case Opcode::CompareLessThanOrEqual:
        default:
            break;
        }
    }
}
