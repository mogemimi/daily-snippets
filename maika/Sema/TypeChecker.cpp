#include "Sema/TypeChecker.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Stmt.h"
#include "Basic/Diagnostic.h"
#include "Sema/Entity.h"
#include "Sema/IdentifierResolver.h"
#include <cassert>
#include <sstream>
#include <utility>

namespace {

constexpr int anyBit = 0b00001;
constexpr int intBit = 0b00010;
constexpr int doubleBit = 0b00100;
constexpr int boolBit = 0b01000;
constexpr int stringBit = 0b10000;

int toBinaryOpTypeCastBits(BuiltinTypeKind type)
{
    switch (type) {
    case BuiltinTypeKind::Any: return anyBit;
    case BuiltinTypeKind::Int: return intBit | doubleBit;
    case BuiltinTypeKind::Double: return doubleBit;
    case BuiltinTypeKind::Bool: return intBit | doubleBit | boolBit;
    case BuiltinTypeKind::String: return stringBit;
    case BuiltinTypeKind::Void: return 0b0;
    }
    return anyBit;
}

enum class BinaryOpTypeCastResult {
    Resolved,
    ResolveOnRuntime,
    TypeMismatch,
};

std::tuple<BuiltinTypeKind, BinaryOpTypeCastResult>
inferBinaryOpTypeCast(BuiltinTypeKind a, BuiltinTypeKind b)
{
    const auto lhsBits = toBinaryOpTypeCastBits(a);
    const auto rhsBits = toBinaryOpTypeCastBits(b);

    if (((lhsBits | rhsBits) & anyBit) != 0) {
        return std::make_tuple(BuiltinTypeKind::Any, BinaryOpTypeCastResult::ResolveOnRuntime);
    }

    const auto castBits = lhsBits & rhsBits;
    if ((castBits & intBit) != 0) {
        return std::make_tuple(BuiltinTypeKind::Int, BinaryOpTypeCastResult::Resolved);
    }
    if ((castBits & doubleBit) != 0) {
        return std::make_tuple(BuiltinTypeKind::Double, BinaryOpTypeCastResult::Resolved);
    }
    if ((castBits & boolBit) != 0) {
        return std::make_tuple(BuiltinTypeKind::Bool, BinaryOpTypeCastResult::Resolved);
    }
    if ((castBits & stringBit) != 0) {
        return std::make_tuple(BuiltinTypeKind::String, BinaryOpTypeCastResult::Resolved);
    }

    return std::make_tuple(BuiltinTypeKind::Any, BinaryOpTypeCastResult::TypeMismatch);
}

} // end of anonymous namespace

TypeChecker::TypeChecker(const std::shared_ptr<DiagnosticHandler>& diagIn)
    : diag(diagIn)
{
    assert(diag);
}

void TypeChecker::error(const Location& l, const std::string& err)
{
    assert(diag);
    diag->error(l, err);
}

void TypeChecker::visit(const std::shared_ptr<CallExpr>& expr, Invoke&& traverse)
{
    traverse();
}

void TypeChecker::visit(const std::shared_ptr<FunctionExpr>& expr, Invoke&& traverse)
{
    traverse();
}

void TypeChecker::visit(const std::shared_ptr<BinaryOperator>& expr, Invoke&& traverse)
{
    traverse();

    if (expr->getKind() == BinaryOperatorKind::Assign) {
        // TODO: Not implemented
        return;
    }

    auto lhs = expr->getLHS();
    auto rhs = expr->getRHS();

    const auto [lhsType, lhsTypeEnabled] = TypeHelper::toBuiltinType(lhs->getType());
    const auto [rhsType, rhsTypeEnabled] = TypeHelper::toBuiltinType(rhs->getType());

    if (lhsType == BuiltinTypeKind::Void) {
        error(lhs->getLocation(), "lhs is 'void' type.");
        return;
    }
    if (rhsType == BuiltinTypeKind::Void) {
        error(rhs->getLocation(), "rhs is 'void' type.");
        return;
    }

    if (!lhsTypeEnabled || !rhsTypeEnabled) {
        // NOTE: resolving types on runtime, so this process is skipped
        return;
    }

    if (lhsType == rhsType) {
        // NOTE: The operator doesn't need to implicitly cast types of operands.
        return;
    }

    const auto [castType, castResult] = inferBinaryOpTypeCast(lhsType, rhsType);
    assert(castType != BuiltinTypeKind::Void);

    if (castResult == BinaryOpTypeCastResult::TypeMismatch) {
        error(expr->getLocation(), "Type mismatch");
        return;
    }

    if (castResult == BinaryOpTypeCastResult::ResolveOnRuntime) {
        // NOTE: resolving types on runtime, so this process is skipped
        return;
    }

    if (lhsType != castType) {
        assert(rhsType == castType);
        auto typeCastExpr = ImplicitStaticTypeCastExpr::make(lhs->getLocation(), lhs);
        typeCastExpr->setType(BuiltinType::make(castType));
        expr->setLHS(typeCastExpr);
    }
    else {
        assert(rhsType != castType);
        assert(lhsType == castType);
        auto typeCastExpr = ImplicitStaticTypeCastExpr::make(rhs->getLocation(), rhs);
        typeCastExpr->setType(BuiltinType::make(castType));
        expr->setRHS(typeCastExpr);
    }
}

void TypeChecker::visit(const std::shared_ptr<UnaryOperator>& expr, Invoke&& traverse)
{
    traverse();
}

void TypeChecker::visit(const std::shared_ptr<DeclRefExpr>& expr, Invoke&& traverse)
{
    traverse();
}
