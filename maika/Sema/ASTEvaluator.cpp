#include "Sema/ASTEvaluator.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Stmt.h"
#include "Basic/Diagnostic.h"
#include "Sema/Entity.h"
#include "Sema/Value.h"
#include <cassert>
#include <utility>

namespace {

std::tuple<std::unique_ptr<Value>, ASTEvaluateResult> runtimeEvaluation()
{
    return std::make_tuple<std::unique_ptr<Value>, ASTEvaluateResult>(
        nullptr, ASTEvaluateResult::RuntimeEvaluation);
}

std::tuple<std::unique_ptr<Value>, ASTEvaluateResult> semanticError()
{
    return std::make_tuple<std::unique_ptr<Value>, ASTEvaluateResult>(
        nullptr, ASTEvaluateResult::SemanticError);
}

std::tuple<std::unique_ptr<Value>, ASTEvaluateResult> staticEvaluation(std::unique_ptr<Value>&& v)
{
    return std::make_tuple(std::move(v), ASTEvaluateResult::StaticEvaluation);
}

template <class TValue, class... Args>
std::tuple<std::unique_ptr<Value>, ASTEvaluateResult> staticEvaluation(Args&&... args)
{
    auto value = std::make_unique<TValue>(std::forward<Args>(args)...);
    auto v = StaticUniquePointerCast<TValue>(std::move(value));
    return std::make_tuple(std::move(v), ASTEvaluateResult::StaticEvaluation);
}

std::tuple<std::unique_ptr<Value>, ASTEvaluateResult> evalBinaryOp(
    const std::shared_ptr<BinaryOperator>& binaryOp,
    Int64Value* lhsValue,
    Int64Value* rhsValue,
    const std::shared_ptr<DiagnosticHandler>& diag)
{
    assert(binaryOp != nullptr);
    assert(lhsValue != nullptr);
    assert(rhsValue != nullptr);

    const auto op = binaryOp->getKind();
    const auto lhs = lhsValue->getValue();
    const auto rhs = rhsValue->getValue();

    switch (op) {
    case BinaryOperatorKind::Assign: return staticEvaluation<Int64Value>(rhs);
    case BinaryOperatorKind::Add: return staticEvaluation<Int64Value>(lhs + rhs);
    case BinaryOperatorKind::Subtract: return staticEvaluation<Int64Value>(lhs - rhs);
    case BinaryOperatorKind::Multiply: return staticEvaluation<Int64Value>(lhs * rhs);
    case BinaryOperatorKind::Divide: return staticEvaluation<Int64Value>(lhs / rhs);
    case BinaryOperatorKind::Mod: return staticEvaluation<Int64Value>(lhs % rhs);
    case BinaryOperatorKind::GreaterThan: return staticEvaluation<BoolValue>(lhs > rhs);
    case BinaryOperatorKind::GreaterThanOrEqual: return staticEvaluation<BoolValue>(lhs >= rhs);
    case BinaryOperatorKind::LessThan: return staticEvaluation<BoolValue>(lhs < rhs);
    case BinaryOperatorKind::LessThanOrEqual: return staticEvaluation<BoolValue>(lhs <= rhs);
    case BinaryOperatorKind::Equal: return staticEvaluation<BoolValue>(lhs == rhs);
    case BinaryOperatorKind::NotEqual: return staticEvaluation<BoolValue>(lhs != rhs);
    case BinaryOperatorKind::LogicalOr: return staticEvaluation<BoolValue>(lhs || rhs);
    case BinaryOperatorKind::LogicalAnd: return staticEvaluation<BoolValue>(lhs && rhs);
    }

    auto type = BuiltinType::toString(BuiltinTypeKind::Int);
    diag->error(
        "error: invalid operands of types '" + type + "' and '" + type + "' to binary 'operator" +
        BinaryOperator::toString(op) + "'");
    return semanticError();
}

std::tuple<std::unique_ptr<Value>, ASTEvaluateResult> evalBinaryOp(
    const std::shared_ptr<BinaryOperator>& binaryOp,
    DoubleValue* lhsValue,
    DoubleValue* rhsValue,
    const std::shared_ptr<DiagnosticHandler>& diag)
{
    assert(binaryOp != nullptr);
    assert(lhsValue != nullptr);
    assert(rhsValue != nullptr);

    const auto op = binaryOp->getKind();
    const auto lhs = lhsValue->getValue();
    const auto rhs = rhsValue->getValue();

    switch (op) {
    case BinaryOperatorKind::Assign: return staticEvaluation<DoubleValue>(rhs);
    case BinaryOperatorKind::Add: return staticEvaluation<DoubleValue>(lhs + rhs);
    case BinaryOperatorKind::Subtract: return staticEvaluation<DoubleValue>(lhs - rhs);
    case BinaryOperatorKind::Multiply: return staticEvaluation<DoubleValue>(lhs * rhs);
    case BinaryOperatorKind::Divide: return staticEvaluation<DoubleValue>(lhs / rhs);
    case BinaryOperatorKind::GreaterThan: return staticEvaluation<BoolValue>(lhs > rhs);
    case BinaryOperatorKind::GreaterThanOrEqual: return staticEvaluation<BoolValue>(lhs >= rhs);
    case BinaryOperatorKind::LessThan: return staticEvaluation<BoolValue>(lhs < rhs);
    case BinaryOperatorKind::LessThanOrEqual: return staticEvaluation<BoolValue>(lhs <= rhs);
    case BinaryOperatorKind::Equal: return staticEvaluation<BoolValue>(lhs == rhs);
    case BinaryOperatorKind::NotEqual: return staticEvaluation<BoolValue>(lhs != rhs);
    case BinaryOperatorKind::LogicalOr: return staticEvaluation<BoolValue>(lhs || rhs);
    case BinaryOperatorKind::LogicalAnd: return staticEvaluation<BoolValue>(lhs && rhs);
    case BinaryOperatorKind::Mod:
        // NOTE: Cannot use modulus on double
        break;
    }

    auto type = BuiltinType::toString(BuiltinTypeKind::Double);
    diag->error(
        "error: invalid operands of types '" + type + "' and '" + type + "' to binary 'operator" +
        BinaryOperator::toString(op) + "'");
    return semanticError();
}

std::tuple<std::unique_ptr<Value>, ASTEvaluateResult> evalBinaryOp(
    const std::shared_ptr<BinaryOperator>& binaryOp,
    BoolValue* lhsValue,
    BoolValue* rhsValue,
    const std::shared_ptr<DiagnosticHandler>& diag)
{
    assert(binaryOp != nullptr);
    assert(lhsValue != nullptr);
    assert(rhsValue != nullptr);

    const auto op = binaryOp->getKind();
    const auto lhs = lhsValue->getValue();
    const auto rhs = rhsValue->getValue();

    switch (op) {
    case BinaryOperatorKind::Assign: return staticEvaluation<BoolValue>(rhs);
    case BinaryOperatorKind::Equal: return staticEvaluation<BoolValue>(lhs == rhs);
    case BinaryOperatorKind::NotEqual: return staticEvaluation<BoolValue>(lhs != rhs);
    case BinaryOperatorKind::LogicalOr: return staticEvaluation<BoolValue>(lhs || rhs);
    case BinaryOperatorKind::LogicalAnd: return staticEvaluation<BoolValue>(lhs && rhs); break;
    default: break;
    }

    auto type = BuiltinType::toString(BuiltinTypeKind::Bool);
    diag->error(
        "error: invalid operands of types '" + type + "' and '" + type + "' to binary 'operator" +
        BinaryOperator::toString(op) + "'");
    return semanticError();
}

std::tuple<std::unique_ptr<Value>, ASTEvaluateResult> evalBinaryOp(
    const std::shared_ptr<BinaryOperator>& binaryOp,
    StringValue* lhsValue,
    StringValue* rhsValue,
    const std::shared_ptr<DiagnosticHandler>& diag)
{
    assert(binaryOp != nullptr);
    assert(lhsValue != nullptr);
    assert(rhsValue != nullptr);

    const auto op = binaryOp->getKind();
    const auto lhs = lhsValue->getValue();
    const auto rhs = rhsValue->getValue();

    switch (op) {
    case BinaryOperatorKind::Assign: return staticEvaluation<StringValue>(rhs);
    case BinaryOperatorKind::Add: return staticEvaluation<StringValue>(lhs + rhs);
    case BinaryOperatorKind::Equal: return staticEvaluation<BoolValue>(lhs == rhs);
    case BinaryOperatorKind::NotEqual: return staticEvaluation<BoolValue>(lhs != rhs); break;
    default: break;
    }

    auto type = BuiltinType::toString(BuiltinTypeKind::String);
    diag->error(
        "error: invalid operands of types '" + type + "' and '" + type + "' to binary 'operator" +
        BinaryOperator::toString(op) + "'");
    return semanticError();
}

std::tuple<std::unique_ptr<Value>, ASTEvaluateResult> evaluateBinaryOp(
    const std::shared_ptr<BinaryOperator>& binaryOp, const std::shared_ptr<DiagnosticHandler>& diag)
{
    auto lhsExpr = binaryOp->getLHS();
    auto rhsExpr = binaryOp->getRHS();

    if ((lhsExpr == nullptr) || (rhsExpr == nullptr)) {
        return semanticError();
    }

    auto [lhsValue, lhsResult] = ASTEvaluator::evaluate(lhsExpr, diag);
    auto [rhsValue, rhsResult] = ASTEvaluator::evaluate(rhsExpr, diag);

    if ((lhsResult == ASTEvaluateResult::SemanticError) ||
        (rhsResult == ASTEvaluateResult::SemanticError)) {
        return semanticError();
    }
    if ((lhsResult == ASTEvaluateResult::RuntimeEvaluation) ||
        (rhsResult == ASTEvaluateResult::RuntimeEvaluation)) {
        return runtimeEvaluation();
    }

    assert(lhsValue != nullptr);
    assert(rhsValue != nullptr);
    assert(lhsResult == ASTEvaluateResult::StaticEvaluation);
    assert(rhsResult == ASTEvaluateResult::StaticEvaluation);

    if (lhsValue->getKind() != rhsValue->getKind()) {
        // error: type mismatch
        diag->error(binaryOp->getLocation(), "type mismatch");
        return semanticError();
    }

    if (lhsValue->getKind() == ValueKind::Int64) {
        assert(rhsValue->getKind() == ValueKind::Int64);
        auto lhs = static_cast<Int64Value*>(lhsValue.get());
        auto rhs = static_cast<Int64Value*>(rhsValue.get());
        return evalBinaryOp(binaryOp, lhs, rhs, diag);
    }
    if (lhsValue->getKind() == ValueKind::Double) {
        assert(rhsValue->getKind() == ValueKind::Double);
        auto lhs = static_cast<DoubleValue*>(lhsValue.get());
        auto rhs = static_cast<DoubleValue*>(rhsValue.get());
        return evalBinaryOp(binaryOp, lhs, rhs, diag);
    }
    if (lhsValue->getKind() == ValueKind::Bool) {
        assert(rhsValue->getKind() == ValueKind::Bool);
        auto lhs = static_cast<BoolValue*>(lhsValue.get());
        auto rhs = static_cast<BoolValue*>(rhsValue.get());
        return evalBinaryOp(binaryOp, lhs, rhs, diag);
    }
    if (lhsValue->getKind() == ValueKind::String) {
        assert(rhsValue->getKind() == ValueKind::String);
        auto lhs = static_cast<StringValue*>(lhsValue.get());
        auto rhs = static_cast<StringValue*>(rhsValue.get());
        return evalBinaryOp(binaryOp, lhs, rhs, diag);
    }
    return runtimeEvaluation();
}

std::tuple<std::unique_ptr<Value>, ASTEvaluateResult> evaluateImplicitCast(
    const std::shared_ptr<ImplicitStaticCastExpr>& expr,
    const std::shared_ptr<DiagnosticHandler>& diag)
{
    auto subExpr = expr->getSubExpr();

    if (subExpr == nullptr) {
        return semanticError();
    }

    const auto [targetType, targetTypeEnabled] = TypeHelper::toBuiltinType(expr->getType());
    if (!targetTypeEnabled) {
        return runtimeEvaluation();
    }

    auto [value, result] = ASTEvaluator::evaluate(subExpr, diag);

    if (result == ASTEvaluateResult::SemanticError) {
        return semanticError();
    }
    if (result == ASTEvaluateResult::RuntimeEvaluation) {
        return runtimeEvaluation();
    }

    if (value->getKind() == ValueKind::Int64) {
        assert(value->getKind() == ValueKind::Int64);
        auto v = static_cast<Int64Value*>(value.get())->getValue();
        switch (targetType) {
        case BuiltinTypeKind::Int:
            return staticEvaluation<Int64Value>(static_cast<std::int64_t>(v));
        case BuiltinTypeKind::Double: return staticEvaluation<DoubleValue>(static_cast<double>(v));
        case BuiltinTypeKind::Bool: return staticEvaluation<BoolValue>(v != 0);
        default: break;
        }
        return semanticError();
    }
    if (value->getKind() == ValueKind::Double) {
        assert(value->getKind() == ValueKind::Double);
        auto v = static_cast<DoubleValue*>(value.get())->getValue();
        switch (targetType) {
        case BuiltinTypeKind::Int:
            return staticEvaluation<Int64Value>(static_cast<std::int64_t>(v));
        case BuiltinTypeKind::Double: return staticEvaluation<DoubleValue>(static_cast<double>(v));
        case BuiltinTypeKind::Bool: return staticEvaluation<BoolValue>(v != 0.0);
        default: break;
        }
        return semanticError();
    }
    if (value->getKind() == ValueKind::Bool) {
        assert(value->getKind() == ValueKind::Bool);
        auto v = static_cast<BoolValue*>(value.get())->getValue();
        switch (targetType) {
        case BuiltinTypeKind::Int: return staticEvaluation<Int64Value>(v ? 1 : 0);
        case BuiltinTypeKind::Double: return staticEvaluation<DoubleValue>(v ? 1.0 : 0.0);
        case BuiltinTypeKind::Bool: return staticEvaluation<BoolValue>(v);
        default: break;
        }
        return semanticError();
    }
    if (value->getKind() == ValueKind::String) {
        assert(value->getKind() == ValueKind::String);
        if (targetType == BuiltinTypeKind::String) {
            return staticEvaluation(std::move(value));
        }
        return semanticError();
    }
    return runtimeEvaluation();
}

} // end of anonymous namespace

std::tuple<std::unique_ptr<Value>, ASTEvaluateResult> ASTEvaluator::evaluate(
    const std::shared_ptr<Expr>& expr, const std::shared_ptr<DiagnosticHandler>& diag)
{
    if (auto e = std::dynamic_pointer_cast<IntegerLiteral>(expr)) {
        auto value = std::make_unique<Int64Value>(e->getValue());
        auto v = StaticUniquePointerCast<Value>(std::move(value));
        return std::make_tuple(std::move(v), ASTEvaluateResult::StaticEvaluation);
    }
    if (auto e = std::dynamic_pointer_cast<DoubleLiteral>(expr)) {
        auto value = std::make_unique<DoubleValue>(e->getValue());
        auto v = StaticUniquePointerCast<Value>(std::move(value));
        return std::make_tuple(std::move(v), ASTEvaluateResult::StaticEvaluation);
    }
    if (auto e = std::dynamic_pointer_cast<BoolLiteral>(expr)) {
        auto value = std::make_unique<BoolValue>(e->getValue());
        auto v = StaticUniquePointerCast<Value>(std::move(value));
        return std::make_tuple(std::move(v), ASTEvaluateResult::StaticEvaluation);
    }
    if (auto e = std::dynamic_pointer_cast<StringLiteral>(expr)) {
        auto value = std::make_unique<StringValue>(e->getValue());
        auto v = StaticUniquePointerCast<Value>(std::move(value));
        return std::make_tuple(std::move(v), ASTEvaluateResult::StaticEvaluation);
    }

    if (auto e = std::dynamic_pointer_cast<BinaryOperator>(expr)) {
        return evaluateBinaryOp(e, diag);
    }

    if (auto e = std::dynamic_pointer_cast<ImplicitStaticCastExpr>(expr)) {
        return evaluateImplicitCast(e, diag);
    }

    return runtimeEvaluation();
}
