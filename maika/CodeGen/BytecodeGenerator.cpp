#include "CodeGen/BytecodeGenerator.h"
#include "AST/ASTContext.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Stmt.h"
#include "AST/Type.h"
#include "Sema/Entity.h"
#include <algorithm>
#include <cassert>
#include <sstream>
#include <utility>

namespace {

} // end of anonymous namespace

void BytecodeGenerator::addInstruction(const std::shared_ptr<Instruction>& inst)
{
    program.instructions.push_back(inst);
}

void BytecodeGenerator::visit(const std::shared_ptr<CompoundStmt>& stmt, Invoke&& traverse)
{
    traverse();
}

void BytecodeGenerator::visit(const std::shared_ptr<DeclStmt>& stmt, Invoke&& traverse)
{
    traverse();
}

void BytecodeGenerator::visit(const std::shared_ptr<ReturnStmt>& stmt, Invoke&& traverse)
{
    traverse();
}

void BytecodeGenerator::visit(const std::shared_ptr<IfStmt>& stmt, Invoke&&)
{
    if (auto cond = stmt->getCond()) {
        cond->traverse(*this);
    }

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
}

void BytecodeGenerator::visit(const std::shared_ptr<ForStmt>& stmt, Invoke&& traverse)
{
    traverse();
}

void BytecodeGenerator::visit(const std::shared_ptr<CallExpr>& expr, Invoke&& traverse)
{
    traverse();
}

void BytecodeGenerator::visit(const std::shared_ptr<FunctionExpr>& expr, Invoke&& traverse)
{
    traverse();
}

void BytecodeGenerator::visit(const std::shared_ptr<IntegerLiteral>& expr)
{
    auto& constants = program.int64Constants;
    const auto index = constants.size();
    constants.push_back(expr->getValue());

    auto inst = std::make_shared<Instruction>();
    inst->opcode = Opcode::ConstantInt64;

    assert(index <= static_cast<size_t>(std::numeric_limits<decltype(inst->operand)>::max()));
    inst->operand = static_cast<int32_t>(index);

    addInstruction(inst);
}

void BytecodeGenerator::visit(const std::shared_ptr<DoubleLiteral>& expr)
{
    auto& constants = program.doubleConstants;
    const auto index = constants.size();
    constants.push_back(expr->getValue());

    auto inst = std::make_shared<Instruction>();
    inst->opcode = Opcode::ConstantDouble;

    assert(index <= static_cast<size_t>(std::numeric_limits<decltype(inst->operand)>::max()));
    inst->operand = static_cast<int32_t>(index);

    addInstruction(inst);
}

void BytecodeGenerator::visit(const std::shared_ptr<BoolLiteral>& expr)
{
    auto inst = std::make_shared<Instruction>();
    inst->opcode = Opcode::ConstantBool;
    inst->operand = expr->getValue() ? 1 : 0;
    addInstruction(inst);
}

void BytecodeGenerator::visit(const std::shared_ptr<StringLiteral>& expr)
{
    auto& constants = program.stringConstants;
    const auto index = constants.size();
    constants.push_back(expr->getValue());

    auto inst = std::make_shared<Instruction>();
    inst->opcode = Opcode::ConstantString;

    assert(index <= static_cast<size_t>(std::numeric_limits<decltype(inst->operand)>::max()));
    inst->operand = static_cast<int32_t>(index);

    addInstruction(inst);
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
        case BinaryOperatorKind::Mod: return Opcode::Mod;
        case BinaryOperatorKind::Equal: return Opcode::CompareEqual;
        case BinaryOperatorKind::NotEqual: return Opcode::CompareNotEqual;
        // case BinaryOperatorKind::LogicalAnd: return "&&";
        // case BinaryOperatorKind::LogicalOr: return "||";
        case BinaryOperatorKind::GreaterThan: return Opcode::CompareGreaterThan;
        case BinaryOperatorKind::GreaterThanOrEqual: return Opcode::CompareGreaterThanOrEqual;
        case BinaryOperatorKind::LessThan: return Opcode::CompareLessThan;
        case BinaryOperatorKind::LessThanOrEqual: return Opcode::CompareLessThanOrEqual;
        default:
            // TODO: Not implemented
            break;
        }
        return Opcode::Exit;
    }();

    auto inst = std::make_shared<Instruction>();
    inst->opcode = opcode;
    addInstruction(inst);
}

void BytecodeGenerator::visit(const std::shared_ptr<UnaryOperator>& expr, Invoke&& traverse)
{
    traverse();
}

void BytecodeGenerator::visit(const std::shared_ptr<DeclRefExpr>& expr, Invoke&& traverse)
{
    traverse();

    auto variableName = expr->getNamedDecl()->getName();
    auto iter = std::find_if(
        std::begin(program.localVariables), std::end(program.localVariables), [&](const auto& a) {
            return variableName == a.name;
        });
    assert(iter != std::end(program.localVariables));

    auto inst = std::make_shared<Instruction>();
    inst->opcode = Opcode::LoadVariable;
    inst->operand = iter->variableIndex;
    addInstruction(inst);
}

void BytecodeGenerator::visit(const std::shared_ptr<MemberExpr>& expr, Invoke&& traverse)
{
    traverse();
}

void BytecodeGenerator::visit(
    const std::shared_ptr<ImplicitStaticCastExpr>& expr, Invoke&& traverse)
{
    traverse();

    const auto [targetType, targetTypeEnabled] = TypeHelper::toBuiltinType(expr->getType());
    assert(targetTypeEnabled);
    if (!targetTypeEnabled) {
        return;
    }
    auto subExpr = expr->getSubExpr();
    const auto [sourceType, sourceTypeEnabled] = TypeHelper::toBuiltinType(subExpr->getType());
    assert(sourceTypeEnabled);
    if (!sourceTypeEnabled) {
        return;
    }

    if (targetType == BuiltinTypeKind::Double) {
        if (sourceType == BuiltinTypeKind::Int) {
            // NOTE: int64 -> double
            auto inst = std::make_shared<Instruction>();
            inst->opcode = Opcode::TypeCastFromInt64ToDouble;
            addInstruction(inst);
        }
    }
}

void BytecodeGenerator::visit(const std::shared_ptr<TranslationUnitDecl>& decl, Invoke&& traverse)
{
    traverse();
}

void BytecodeGenerator::visit(const std::shared_ptr<FunctionDecl>& decl, Invoke&& traverse)
{
    traverse();
}

void BytecodeGenerator::visit(const std::shared_ptr<VariableDecl>& decl, Invoke&& traverse)
{
    traverse();

    if (!decl->getExpr()) {
        auto inst = std::make_shared<Instruction>();
        inst->opcode = Opcode::ConstantNull;
        addInstruction(inst);
    }

    auto& variables = program.localVariables;
    const auto index = variables.size();
    LocalVariable variableInfo;
    assert(decl);
    assert(decl->getNamedDecl());
    variableInfo.name = decl->getNamedDecl()->getName();
    variableInfo.variableIndex = static_cast<int32_t>(index);
    variables.push_back(variableInfo);

    auto inst = std::make_shared<Instruction>();
    inst->opcode = Opcode::DefineVariable;

    assert(index <= static_cast<size_t>(std::numeric_limits<decltype(inst->operand)>::max()));
    inst->operand = static_cast<int32_t>(index);

    addInstruction(inst);
}

void BytecodeGenerator::visit(const std::shared_ptr<ConstDecl>& decl, Invoke&& traverse)
{
    traverse();
}
