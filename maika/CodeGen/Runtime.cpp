#include "CodeGen/Runtime.h"
#include <cassert>

namespace {

bool getConstantBoolValue(int32_t operand)
{
    assert((operand == 0) || (operand == 1));
    return (operand != 0);
}

template <typename T> const T& getConstantValue(int32_t operand, const std::vector<T>& constants)
{
    assert(operand >= 0);
    assert(operand < static_cast<int>(constants.size()));
    return constants[operand];
}

void invokeConstantBool(int32_t operand, std::vector<std::shared_ptr<Value>>& valueStack)
{
    const auto boolValue = getConstantBoolValue(operand);
    const auto value = std::make_shared<BoolValue>(boolValue);
    valueStack.push_back(value);
}

template <class ValueType, class TConstantTable>
void invokeConstant(
    int32_t operand,
    const TConstantTable& constants,
    std::vector<std::shared_ptr<Value>>& valueStack)
{
    const auto v = getConstantValue(operand, constants);
    const auto value = std::make_shared<ValueType>(v);
    valueStack.push_back(value);
}

bool invokeAdd(std::vector<std::shared_ptr<Value>>& valueStack)
{
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
    default: printf("%s\n", "runtime error: not implemented"); return false;
    }
    return true;
}

bool invokeSub(std::vector<std::shared_ptr<Value>>& valueStack)
{
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
    default: printf("%s\n", "runtime error: not implemented"); return false;
    }
    return true;
}

bool invokeMul(std::vector<std::shared_ptr<Value>>& valueStack)
{
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
    default: printf("%s\n", "runtime error: not implemented"); return false;
    }
    return true;
}

bool invokeDiv(std::vector<std::shared_ptr<Value>>& valueStack)
{
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
    default: printf("%s\n", "runtime error: not implemented"); return false;
    }
    return true;
}

bool invokeMod(std::vector<std::shared_ptr<Value>>& valueStack)
{
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
        auto v = a->getValue() % b->getValue();
        auto resultValue = std::make_shared<Int64Value>(v);
        valueStack.push_back(resultValue);
        break;
    }
    case ValueKind::Double: {
        printf("%s\n", "runtime error: invalid operands to binary expression");
        return false;
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
        auto v = a->getValue() % b->getValue();
        auto resultValue = std::make_shared<BoolValue>(v);
        valueStack.push_back(resultValue);
        break;
    }
    case ValueKind::String: {
        printf("%s\n", "runtime error: Cannot divide two strings.");
        return false;
        break;
    }
    default: printf("%s\n", "runtime error: not implemented"); return false;
    }
    return true;
}

struct CompareOperatorGreaterThan final {
    template <typename T> static bool compare(T a, T b) { return a > b; }
};

struct CompareOperatorGreaterThanOrEqual final {
    template <typename T> static bool compare(T a, T b) { return a >= b; }
};

struct CompareOperatorLessThan final {
    template <typename T> static bool compare(T a, T b) { return a < b; }
};

struct CompareOperatorLessThanOrEqual final {
    template <typename T> static bool compare(T a, T b) { return a <= b; }
};

template <class TCompareOperator>
bool invokeCompare(std::vector<std::shared_ptr<Value>>& valueStack)
{
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
        auto v = TCompareOperator::compare(a->getValue(), b->getValue());
        auto resultValue = std::make_shared<BoolValue>(v);
        valueStack.push_back(resultValue);
        break;
    }
    case ValueKind::Double: {
        auto a = std::static_pointer_cast<DoubleValue>(lhs);
        assert(a);
        auto b = std::static_pointer_cast<DoubleValue>(rhs);
        assert(b);
        auto v = TCompareOperator::compare(a->getValue(), b->getValue());
        auto resultValue = std::make_shared<BoolValue>(v);
        valueStack.push_back(resultValue);
        break;
    }
    case ValueKind::Bool: {
        // TODO: comparing two bool values
        printf("%s\n", "warning: undefined behavior when comparing two bool values.");

        auto a = std::static_pointer_cast<BoolValue>(lhs);
        assert(a);
        auto b = std::static_pointer_cast<BoolValue>(rhs);
        assert(b);
        auto v = TCompareOperator::compare(a->getValue(), b->getValue());
        auto resultValue = std::make_shared<BoolValue>(v);
        valueStack.push_back(resultValue);
        break;
    }
    case ValueKind::String: {
        printf("%s\n", "runtime error: Cannot compare two strings.");
        return false;
        break;
    }
    default: printf("%s\n", "runtime error: not implemented"); return false;
    }
    return true;
}

struct CompareOperatorEqual final {
    template <typename T> static bool compare(T a, T b) { return a == b; }
};

struct CompareOperatorNotEqual final {
    template <typename T> static bool compare(T a, T b) { return a != b; }
};

template <class TCompareOperator>
bool invokeCompareEqual(std::vector<std::shared_ptr<Value>>& valueStack)
{
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
        auto v = TCompareOperator::compare(a->getValue(), b->getValue());
        auto resultValue = std::make_shared<BoolValue>(v);
        valueStack.push_back(resultValue);
        break;
    }
    case ValueKind::Double: {
        auto a = std::static_pointer_cast<DoubleValue>(lhs);
        assert(a);
        auto b = std::static_pointer_cast<DoubleValue>(rhs);
        assert(b);
        auto v = TCompareOperator::compare(a->getValue(), b->getValue());
        auto resultValue = std::make_shared<BoolValue>(v);
        valueStack.push_back(resultValue);
        break;
    }
    case ValueKind::Bool: {
        auto a = std::static_pointer_cast<BoolValue>(lhs);
        assert(a);
        auto b = std::static_pointer_cast<BoolValue>(rhs);
        assert(b);
        auto v = TCompareOperator::compare(a->getValue(), b->getValue());
        auto resultValue = std::make_shared<BoolValue>(v);
        valueStack.push_back(resultValue);
        break;
    }
    case ValueKind::String: {
        auto a = std::static_pointer_cast<StringValue>(lhs);
        assert(a);
        auto b = std::static_pointer_cast<StringValue>(rhs);
        assert(b);
        auto v = TCompareOperator::compare(a->getValue(), b->getValue());
        auto resultValue = std::make_shared<BoolValue>(v);
        valueStack.push_back(resultValue);
        break;
    }
    default: printf("%s\n", "runtime error: not implemented"); return false;
    }
    return true;
}

std::shared_ptr<Value> passForAssignment(const std::shared_ptr<Value>& v)
{
    switch (v->getKind()) {
    case ValueKind::Null: {
        // pass by value
        return std::make_shared<NullValue>();
        break;
    }
    case ValueKind::Int64: {
        // pass by value
        auto underlyingValue = std::static_pointer_cast<Int64Value>(v);
        return std::make_shared<Int64Value>(underlyingValue->getValue());
        break;
    }
    case ValueKind::Double: {
        // pass by value
        auto underlyingValue = std::static_pointer_cast<DoubleValue>(v);
        return std::make_shared<DoubleValue>(underlyingValue->getValue());
        break;
    }
    case ValueKind::Bool: {
        // pass by value
        auto underlyingValue = std::static_pointer_cast<BoolValue>(v);
        return std::make_shared<BoolValue>(underlyingValue->getValue());
        break;
    } break;
    case ValueKind::String: {
        // pass by value
        auto underlyingValue = std::static_pointer_cast<StringValue>(v);
        return std::make_shared<StringValue>(underlyingValue->getValue());
        break;
    }
    }
    return v;
}

} // end of anonymous namespace

bool Runtime::run(const BytecodeProgram& program)
{
    for (auto& inst : program.instructions) {
        switch (inst->getOpcode()) {
        case Opcode::ConstantNull: {
            const auto value = std::make_shared<NullValue>();
            valueStack.push_back(value);
            break;
        }
        case Opcode::ConstantBool: {
            invokeConstantBool(inst->operand, valueStack);
            break;
        }
        case Opcode::ConstantDouble: {
            invokeConstant<DoubleValue>(inst->operand, program.doubleConstants, valueStack);
            break;
        }
        case Opcode::ConstantInt64: {
            invokeConstant<Int64Value>(inst->operand, program.int64Constants, valueStack);
            break;
        }
        case Opcode::ConstantString: {
            invokeConstant<StringValue>(inst->operand, program.stringConstants, valueStack);
            break;
        }
        case Opcode::DefineVariable: {
            const auto v = getConstantValue(inst->operand, program.localVariables);
#if !defined(NDEBUG)
            if (variables.find(v.name) != std::end(variables)) {
                printf("%s\n", "runtime error: local variable redifinition error");
                return false;
            }
#endif

#if !defined(NDEBUG)
            if (valueStack.empty()) {
                printf("%s\n", "runtime error: empty stack");
                return false;
            }
#endif
            auto value = valueStack.back();
            valueStack.pop_back();
            variables.emplace(v.name, passForAssignment(value));
            break;
        }
        case Opcode::LoadVariable: {
            const auto v = getConstantValue(inst->operand, program.localVariables);

            auto iter = variables.find(v.name);
#if !defined(NDEBUG)
            if (iter == std::end(variables)) {
                printf("%s\n", "runtime error: cannot find the variable");
                return false;
            }
#endif
            valueStack.push_back(iter->second);
            break;
        }
        case Opcode::Add: {
            if (!invokeAdd(valueStack)) {
                return false;
            }
            break;
        }
        case Opcode::Sub: {
            if (!invokeSub(valueStack)) {
                return false;
            }
            break;
        }
        case Opcode::Mul: {
            if (!invokeMul(valueStack)) {
                return false;
            }
            break;
        }
        case Opcode::Div: {
            if (!invokeDiv(valueStack)) {
                return false;
            }
            break;
        }
        case Opcode::Mod: {
            if (!invokeMod(valueStack)) {
                return false;
            }
            break;
        }
        case Opcode::CompareEqual: {
            if (!invokeCompareEqual<CompareOperatorEqual>(valueStack)) {
                return false;
            }
            break;
        }
        case Opcode::CompareNotEqual: {
            if (!invokeCompareEqual<CompareOperatorNotEqual>(valueStack)) {
                return false;
            }
            break;
        }
        case Opcode::CompareGreaterThan: {
            if (!invokeCompare<CompareOperatorGreaterThan>(valueStack)) {
                return false;
            }
            break;
        }
        case Opcode::CompareGreaterThanOrEqual: {
            if (!invokeCompare<CompareOperatorGreaterThan>(valueStack)) {
                return false;
            }
            break;
        }
        case Opcode::CompareLessThan: {
            if (!invokeCompare<CompareOperatorLessThan>(valueStack)) {
                return false;
            }
            break;
        }
        case Opcode::CompareLessThanOrEqual: {
            if (!invokeCompare<CompareOperatorLessThanOrEqual>(valueStack)) {
                return false;
            }
            break;
        }
        case Opcode::TypeCastFromInt64ToDouble: {
            if (valueStack.size() < 1) {
                printf("%s\n", "runtime error");
                return false;
            }
            auto sourceValue = valueStack.back();
            valueStack.pop_back();

            assert(sourceValue->getKind() == ValueKind::Int64);
#if !defined(NDEBUG)
            if (sourceValue->getKind() != ValueKind::Int64) {
                printf("%s\n", "runtime error: type of operand must be integer.");
                return false;
            }
#endif
            auto a = std::static_pointer_cast<Int64Value>(sourceValue);
            assert(a);

            const auto v = static_cast<double>(a->getValue());

            auto resultValue = std::make_shared<DoubleValue>(v);
            valueStack.push_back(resultValue);
            break;
        }
        default: break;
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
    case ValueKind::Null: {
        return "null";
        break;
    }
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

void Runtime::dump(const BytecodeProgram& program)
{
    for (auto& inst : program.instructions) {
        switch (inst->getOpcode()) {
        case Opcode::ConstantBool: {
            const auto boolValue = getConstantBoolValue(inst->getOperand());
            const auto s = boolValue ? "true" : "false";
            printf("%s %s\n", "bool", s);
            break;
        }
        case Opcode::ConstantDouble: {
            const auto doubleValue =
                getConstantValue<double>(inst->getOperand(), program.doubleConstants);
            const auto s = std::to_string(doubleValue);
            printf("%s %s\n", "double", s.c_str());
            break;
        }
        case Opcode::ConstantInt64: {
            const auto int64Value =
                getConstantValue<int64_t>(inst->getOperand(), program.int64Constants);
            const auto s = std::to_string(int64Value);
            printf("%s %s\n", "int64", s.c_str());
            break;
        }
        case Opcode::ConstantString: {
            const auto stringValue =
                getConstantValue<std::string>(inst->getOperand(), program.stringConstants);
            printf("%s %s\n", "string", stringValue.c_str());
            break;
        }
        case Opcode::ConstantNull: {
            printf("%s\n", "null");
            break;
        }
        case Opcode::DefineVariable: {
            auto variableInfo =
                getConstantValue<LocalVariable>(inst->getOperand(), program.localVariables);
            printf("%s %s\n", "var", variableInfo.name.c_str());
            break;
        }
        case Opcode::LoadVariable: {
            auto variableInfo =
                getConstantValue<LocalVariable>(inst->getOperand(), program.localVariables);
            printf("%s %s\n", "load", variableInfo.name.c_str());
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
        case Opcode::CompareEqual: {
            printf("%s\n", "comp_eq");
            break;
        }
        case Opcode::CompareNotEqual: {
            printf("%s\n", "comp_ne");
            break;
        }
        case Opcode::CompareGreaterThan: {
            printf("%s\n", "comp_g");
            break;
        }
        case Opcode::CompareGreaterThanOrEqual: {
            printf("%s\n", "comp_ge");
            break;
        }
        case Opcode::CompareLessThan: {
            printf("%s\n", "comp_l");
            break;
        }
        case Opcode::CompareLessThanOrEqual: {
            printf("%s\n", "comp_le");
            break;
        }
        default: break;
        }
    }
}
