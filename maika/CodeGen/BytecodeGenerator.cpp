#include "CodeGen/BytecodeGenerator.h"
#include "AST/ASTContext.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Stmt.h"
#include "AST/Type.h"
#include "Sema/Entity.h"
#include <cassert>
#include <sstream>
#include <utility>

namespace {

} // end of anonymous namespace

void BytecodeGenerator::visit(const std::shared_ptr<CompoundStmt>& stmt, Invoke&& traverse)
{
    traverse();
    // printf("[%s]\n", "CompoundStmt");
}

void BytecodeGenerator::visit(const std::shared_ptr<DeclStmt>& stmt, Invoke&& traverse)
{
    traverse();
    printf("[%s]\n", "DeclStmt");
}

void BytecodeGenerator::visit(const std::shared_ptr<ReturnStmt>& stmt, Invoke&& traverse)
{
    traverse();
    printf("%s [%s]\n", "return", "ReturnStmt");
}

void BytecodeGenerator::visit(const std::shared_ptr<IfStmt>& stmt, Invoke&&)
{
    if (auto cond = stmt->getCond()) {
        cond->traverse(*this);
    }

    printf("%s [%s]\n", "jumpifnot", "IfStmt");

    if (auto then = stmt->getThen()) {
        then->traverse(*this);
    }

    if (auto elseStmt = stmt->getElse()) {
        elseStmt->traverse(*this);
    }
}

void BytecodeGenerator::visit(const std::shared_ptr<WhileStmt>& stmt, Invoke&& traverse)
{
    traverse();
    printf("[%s]\n", "WhileStmt");
}

void BytecodeGenerator::visit(const std::shared_ptr<ForStmt>& stmt, Invoke&& traverse)
{
    traverse();
    printf("[%s]\n", "ForStmt");
}

void BytecodeGenerator::visit(const std::shared_ptr<CallExpr>& expr, Invoke&& traverse)
{
    traverse();
    printf("[%s]\n", "CallExpr");
}

void BytecodeGenerator::visit(const std::shared_ptr<FunctionExpr>& expr, Invoke&& traverse)
{
    traverse();
    printf("[%s]\n", "FunctionExpr");
}

void BytecodeGenerator::visit(const std::shared_ptr<IntegerLiteral>& expr)
{
    auto inst = std::make_shared<Instruction>();
    inst->opcode = Opcode::ConstantInt64;
    inst->operand = std::make_shared<Int64Value>(expr->getValue());
    instructions.push_back(inst);
    // printf("%s %d [%s]\n", "int", static_cast<int>(expr->getValue()), "IntegerLiteral");
}

void BytecodeGenerator::visit(const std::shared_ptr<DoubleLiteral>& expr)
{
    auto inst = std::make_shared<Instruction>();
    inst->opcode = Opcode::ConstantDouble;
    inst->operand = std::make_shared<DoubleValue>(expr->getValue());
    instructions.push_back(inst);
    // printf("%s %lf [%s]\n", "double", expr->getValue(), "DoubleLiteral");
}

void BytecodeGenerator::visit(const std::shared_ptr<BoolLiteral>& expr)
{
    auto inst = std::make_shared<Instruction>();
    inst->opcode = Opcode::ConstantBool;
    inst->operand = std::make_shared<BoolValue>(expr->getValue());
    instructions.push_back(inst);
    // printf("%s %s [%s]\n", "bool", expr->getValue() ? "true" : "false", "BoolLiteral");
}

void BytecodeGenerator::visit(const std::shared_ptr<StringLiteral>& expr)
{
    auto inst = std::make_shared<Instruction>();
    inst->opcode = Opcode::ConstantString;
    inst->operand = std::make_shared<StringValue>(expr->getValue());
    instructions.push_back(inst);
    // printf("[%s]\n", "StringLiteral");
}

void BytecodeGenerator::visit(const std::shared_ptr<BinaryOperator>& expr, Invoke&& traverse)
{
    traverse();

    const auto opcode = [&]() -> Opcode {
        switch (expr->getKind()) {
        // case BinaryOperatorKind::Assign: return "=";
        case BinaryOperatorKind::Add: return Opcode::Add;
        case BinaryOperatorKind::Subtract: return Opcode::Sub;
        case BinaryOperatorKind::Divide: return Opcode::Div;
        case BinaryOperatorKind::Multiply: return Opcode::Mul;
        // case BinaryOperatorKind::Mod: return "%";
        // case BinaryOperatorKind::Equal: return "==";
        // case BinaryOperatorKind::NotEqual: return "!=";
        // case BinaryOperatorKind::LogicalAnd: return "&&";
        // case BinaryOperatorKind::LogicalOr: return "||";
        // case BinaryOperatorKind::GreaterThan: return ">";
        // case BinaryOperatorKind::GreaterThanOrEqual: return ">=";
        // case BinaryOperatorKind::LessThan: return "<";
        // case BinaryOperatorKind::LessThanOrEqual: return "<=";
        default:
            // TODO: Not implemented
            break;
        }
        return Opcode::Exit;
    }();

    auto inst = std::make_shared<Instruction>();
    inst->opcode = opcode;
    instructions.push_back(inst);

    // auto op = ASTHelper::toString(expr->getKind());
    // printf("%s %s [%s]\n", "bin-op", op.c_str(), "BinaryOperator");
}

void BytecodeGenerator::visit(const std::shared_ptr<UnaryOperator>& expr, Invoke&& traverse)
{
    traverse();
    printf("[%s]\n", "UnaryOperator");
}

void BytecodeGenerator::visit(const std::shared_ptr<DeclRefExpr>& expr, Invoke&& traverse)
{
    traverse();
    printf("%s %s [%s]\n", "load", expr->getNamedDecl()->getName().c_str(), "DeclRefExpr");
}

void BytecodeGenerator::visit(const std::shared_ptr<MemberExpr>& expr, Invoke&& traverse)
{
    traverse();
    printf("[%s]\n", "MemberExpr");
}

void BytecodeGenerator::visit(const std::shared_ptr<TranslationUnitDecl>& decl, Invoke&& traverse)
{
    traverse();
    // printf("[%s]\n", "TranslationUnitDecl");
}

void BytecodeGenerator::visit(const std::shared_ptr<FunctionDecl>& decl, Invoke&& traverse)
{
    std::string funcName;
    if (auto namedDecl = decl->getNamedDecl()) {
        funcName = namedDecl->getName();
    }
    printf("%s [%s]\n", funcName.c_str(), "FunctionDecl");
    traverse();
}

void BytecodeGenerator::visit(const std::shared_ptr<VariableDecl>& decl, Invoke&& traverse)
{
    traverse();
    printf("[%s]\n", "VariableDecl");
}

void BytecodeGenerator::visit(const std::shared_ptr<ConstDecl>& decl, Invoke&& traverse)
{
    traverse();
    printf("[%s]\n", "ConstDecl");
}

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
