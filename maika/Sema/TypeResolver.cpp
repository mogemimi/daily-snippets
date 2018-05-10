#include "Sema/TypeResolver.h"
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

template <class ASTNode>
void substition(
    const std::shared_ptr<ASTNode>& ast,
    const std::shared_ptr<TypeVariable>& variable,
    const std::shared_ptr<Type>& type)
{
    if (variable == type) {
        return;
    }
    variable->setType(type);

    assert(ast->getType() == variable);
    ast->setType(type);
}

bool isSameType(const std::shared_ptr<Type>& a, const std::shared_ptr<Type>& b);

bool isSameTypeOrNull(const std::shared_ptr<Type>& a, const std::shared_ptr<Type>& b)
{
    if (a == nullptr) {
        return b == nullptr;
    }
    if (b == nullptr) {
        return false;
    }
    assert(a);
    assert(b);
    return isSameType(a, b);
}

bool isSameType(const std::shared_ptr<Type>& a, const std::shared_ptr<Type>& b)
{
    assert(a);
    assert(b);

    if (a->getKind() != b->getKind()) {
        return false;
    }

    switch (a->getKind()) {
    case TypeKind::TypeVariable: {
        const auto x = std::static_pointer_cast<TypeVariable>(a);
        const auto y = std::static_pointer_cast<TypeVariable>(b);
        assert(x);
        assert(y);
        return (x->getTypeID() == y->getTypeID());
    }
    case TypeKind::BuiltinType: {
        const auto x = std::static_pointer_cast<BuiltinType>(a);
        const auto y = std::static_pointer_cast<BuiltinType>(b);
        assert(x);
        assert(y);
        return (x->kind == y->kind);
    }
    case TypeKind::ArrayType: {
        assert(a->getKind() == TypeKind::ArrayType);
        assert(b->getKind() == TypeKind::ArrayType);
        const auto x = std::static_pointer_cast<ArrayType>(a);
        const auto y = std::static_pointer_cast<ArrayType>(b);
        assert(x);
        assert(y);
        return isSameTypeOrNull(x->primaryType, y->primaryType);
    }
    case TypeKind::MapType: {
        assert(a->getKind() == TypeKind::MapType);
        assert(b->getKind() == TypeKind::MapType);
        const auto x = std::static_pointer_cast<MapType>(a);
        const auto y = std::static_pointer_cast<MapType>(b);
        assert(x);
        assert(y);
        return isSameTypeOrNull(x->keyType, y->keyType) &&
               isSameTypeOrNull(x->valueType, y->valueType);
    }
    case TypeKind::TupleType: {
        const auto x = std::static_pointer_cast<TupleType>(a);
        const auto y = std::static_pointer_cast<TupleType>(b);
        assert(x);
        assert(y);
        if (x->types.size() != y->types.size()) {
            return false;
        }
        for (size_t i = 0; i < x->types.size(); i++) {
            if (!isSameType(x->types[i], y->types[i])) {
                return false;
            }
        }
        return true;
    }
    case TypeKind::ReturnType:
        // TODO: not implemented
        return false;
    case TypeKind::FunctionType:
        // TODO: not implemented
        return false;
    }
    return false;
}

bool isIntegral(const std::shared_ptr<Type>& t)
{
    if (t->getKind() != TypeKind::BuiltinType) {
        return false;
    }
    assert(std::dynamic_pointer_cast<BuiltinType>(t) != nullptr);
    const auto s = std::static_pointer_cast<BuiltinType>(t);
    switch (s->kind) {
    case BuiltinTypeKind::Int: return true;
    default: break;
    }
    return false;
}

bool isFloatingPoint(const std::shared_ptr<Type>& t)
{
    if (t->getKind() != TypeKind::BuiltinType) {
        return false;
    }
    assert(std::dynamic_pointer_cast<BuiltinType>(t) != nullptr);
    const auto s = std::static_pointer_cast<BuiltinType>(t);
    switch (s->kind) {
    case BuiltinTypeKind::Double: return true;
    default: break;
    }
    return false;
}

bool isBoolean(const std::shared_ptr<Type>& t)
{
    if (t->getKind() != TypeKind::BuiltinType) {
        return false;
    }
    assert(std::dynamic_pointer_cast<BuiltinType>(t) != nullptr);
    const auto s = std::static_pointer_cast<BuiltinType>(t);
    switch (s->kind) {
    case BuiltinTypeKind::Bool: return true;
    default: break;
    }
    return false;
}

std::shared_ptr<Type> inferReturnType(const std::shared_ptr<TypeResolverScope>& scope)
{
    if (scope->returnTypes.empty()) {
        return BuiltinType::make(BuiltinTypeKind::Void);
    }
    auto candidate = TypeInferer::infer(scope->env, scope->returnTypes.front());
    assert(candidate);
    for (const auto& ret : scope->returnTypes) {
        auto t = TypeInferer::infer(scope->env, ret);
        if (!isSameType(candidate, t)) {
            // TODO: Not implemented
            // if (t->getKind() != TypeKind::TypeVariable) {
            //     error("Type mismatch");
            // }
            return BuiltinType::make(BuiltinTypeKind::Any);
        }
    }
    return candidate;
}

std::vector<std::shared_ptr<Type>>
getParameterTypes(const std::vector<std::shared_ptr<ParmVarDecl>>& parameters)
{
    std::vector<std::shared_ptr<Type>> parameterTypes;
    for (const auto& param : parameters) {
        assert(param);
        assert(param->getType());
        parameterTypes.push_back(param->getType());
    }
    return parameterTypes;
}

constexpr int anyBit = 0b0000001;
constexpr int intBit = 0b0000010;
constexpr int doubleBit = 0b0000100;
constexpr int boolBit = 0b0001000;
constexpr int stringBit = 0b0010000;

int toBinaryOpTypeCastBits(BuiltinTypeKind type)
{
    switch (type) {
    case BuiltinTypeKind::Any: return anyBit;
    case BuiltinTypeKind::Int: return intBit | doubleBit;
    case BuiltinTypeKind::Double: return doubleBit;
    case BuiltinTypeKind::Bool: return boolBit;
    case BuiltinTypeKind::String: return stringBit;
    case BuiltinTypeKind::Void: return 0b0;
    case BuiltinTypeKind::Null: return anyBit;
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

template <class GetCond, class SetCond>
void ImplicitCastifyConditionExpr(
    const std::shared_ptr<TypeResolverScope>& scope,
    const std::shared_ptr<DiagnosticHandler>& diag,
    GetCond&& getCond,
    SetCond&& setCond)
{
    const auto condExpr = getCond();
    assert(condExpr);
    assert(condExpr->getType());

    const auto condTypeInferred = TypeInferer::infer(scope->env, condExpr->getType());

    const auto [condType, condTypeEnabled] = TypeHelper::toBuiltinType(condTypeInferred);

    if (condType == BuiltinTypeKind::Void) {
        diag->error(condExpr->getLocation(), "cond is 'void' type.");
        return;
    }

    if (!condTypeEnabled) {
        // NOTE: resolving type on runtime, so this process is skipped
        return;
    }

    if (condType == BuiltinTypeKind::Bool) {
        // NOTE: The operator doesn't need to implicitly cast types of operands.
        return;
    }

    auto typeCastExpr = ImplicitStaticCastExpr::make(condExpr->getLocation(), condExpr);
    typeCastExpr->setType(BuiltinType::make(BuiltinTypeKind::Bool));
    setCond(typeCastExpr);
}

using TypeCapability = uint64_t;
constexpr uint64_t hasBinaryOperatorAdd = 0b0000000000000001;
constexpr uint64_t hasBinaryOperatorSubtract = 0b0000000000000010;
constexpr uint64_t hasBinaryOperatorMultiply = 0b0000000000000100;
constexpr uint64_t hasBinaryOperatorDivide = 0b0000000000001000;
constexpr uint64_t hasBinaryOperatorMod = 0b0000000000010000;
constexpr uint64_t hasBinaryOperatorAssign = 0b0000000000100000;
constexpr uint64_t hasBinaryOperatorEqual = 0b0000000001000000;
constexpr uint64_t hasBinaryOperatorNotEqual = 0b0000000010000000;
constexpr uint64_t hasBinaryOperatorLogicalAnd = 0b0000000100000000;
constexpr uint64_t hasBinaryOperatorLogicalOr = 0b0000001000000000;
constexpr uint64_t hasBinaryOperatorGreaterThan = 0b0000010000000000;
constexpr uint64_t hasBinaryOperatorGreaterThanOrEqual = 0b0000100000000000;
constexpr uint64_t hasBinaryOperatorLessThan = 0b0001000000000000;
constexpr uint64_t hasBinaryOperatorLessThanOrEqual = 0b0010000000000000;

constexpr TypeCapability disableMask(TypeCapability c, uint64_t mask)
{
    return c & (~mask);
}

constexpr TypeCapability enableMask(TypeCapability c, uint64_t mask)
{
    return c | mask;
}

TypeCapability getTypeCapability(BuiltinTypeKind type)
{
    TypeCapability c = 0;
    switch (type) {
    case BuiltinTypeKind::Any:
        c = enableMask(c, hasBinaryOperatorAdd);
        c = enableMask(c, hasBinaryOperatorSubtract);
        c = enableMask(c, hasBinaryOperatorMultiply);
        c = enableMask(c, hasBinaryOperatorDivide);
        c = enableMask(c, hasBinaryOperatorMod);
        c = enableMask(c, hasBinaryOperatorAssign);
        c = enableMask(c, hasBinaryOperatorEqual);
        c = enableMask(c, hasBinaryOperatorNotEqual);
        c = enableMask(c, hasBinaryOperatorLogicalAnd);
        c = enableMask(c, hasBinaryOperatorLogicalOr);
        c = enableMask(c, hasBinaryOperatorGreaterThan);
        c = enableMask(c, hasBinaryOperatorGreaterThanOrEqual);
        c = enableMask(c, hasBinaryOperatorLessThan);
        c = enableMask(c, hasBinaryOperatorLessThanOrEqual);
        break;
    case BuiltinTypeKind::Bool:
        c = disableMask(c, hasBinaryOperatorAdd);
        c = disableMask(c, hasBinaryOperatorSubtract);
        c = disableMask(c, hasBinaryOperatorMultiply);
        c = disableMask(c, hasBinaryOperatorDivide);
        c = disableMask(c, hasBinaryOperatorMod);
        c = enableMask(c, hasBinaryOperatorAssign);
        c = enableMask(c, hasBinaryOperatorEqual);
        c = enableMask(c, hasBinaryOperatorNotEqual);
        c = enableMask(c, hasBinaryOperatorLogicalAnd);
        c = enableMask(c, hasBinaryOperatorLogicalOr);
        c = disableMask(c, hasBinaryOperatorGreaterThan);
        c = disableMask(c, hasBinaryOperatorGreaterThanOrEqual);
        c = disableMask(c, hasBinaryOperatorLessThan);
        c = disableMask(c, hasBinaryOperatorLessThanOrEqual);
        break;
    case BuiltinTypeKind::Double:
        c = enableMask(c, hasBinaryOperatorAdd);
        c = enableMask(c, hasBinaryOperatorSubtract);
        c = enableMask(c, hasBinaryOperatorMultiply);
        c = enableMask(c, hasBinaryOperatorDivide);
        c = disableMask(c, hasBinaryOperatorMod);
        c = enableMask(c, hasBinaryOperatorAssign);
        c = enableMask(c, hasBinaryOperatorEqual);
        c = enableMask(c, hasBinaryOperatorNotEqual);
        c = enableMask(c, hasBinaryOperatorLogicalAnd);
        c = enableMask(c, hasBinaryOperatorLogicalOr);
        c = enableMask(c, hasBinaryOperatorGreaterThan);
        c = enableMask(c, hasBinaryOperatorGreaterThanOrEqual);
        c = enableMask(c, hasBinaryOperatorLessThan);
        c = enableMask(c, hasBinaryOperatorLessThanOrEqual);
        break;
    case BuiltinTypeKind::Int:
        c = enableMask(c, hasBinaryOperatorAdd);
        c = enableMask(c, hasBinaryOperatorSubtract);
        c = enableMask(c, hasBinaryOperatorMultiply);
        c = enableMask(c, hasBinaryOperatorDivide);
        c = enableMask(c, hasBinaryOperatorMod);
        c = enableMask(c, hasBinaryOperatorAssign);
        c = enableMask(c, hasBinaryOperatorEqual);
        c = enableMask(c, hasBinaryOperatorNotEqual);
        c = enableMask(c, hasBinaryOperatorLogicalAnd);
        c = enableMask(c, hasBinaryOperatorLogicalOr);
        c = enableMask(c, hasBinaryOperatorGreaterThan);
        c = enableMask(c, hasBinaryOperatorGreaterThanOrEqual);
        c = enableMask(c, hasBinaryOperatorLessThan);
        c = enableMask(c, hasBinaryOperatorLessThanOrEqual);
        break;
    case BuiltinTypeKind::Null:
        c = disableMask(c, hasBinaryOperatorAdd);
        c = disableMask(c, hasBinaryOperatorSubtract);
        c = disableMask(c, hasBinaryOperatorMultiply);
        c = disableMask(c, hasBinaryOperatorDivide);
        c = disableMask(c, hasBinaryOperatorMod);
        c = enableMask(c, hasBinaryOperatorAssign);
        c = disableMask(c, hasBinaryOperatorEqual);
        c = disableMask(c, hasBinaryOperatorNotEqual);
        c = disableMask(c, hasBinaryOperatorLogicalAnd);
        c = disableMask(c, hasBinaryOperatorLogicalOr);
        c = disableMask(c, hasBinaryOperatorGreaterThan);
        c = disableMask(c, hasBinaryOperatorGreaterThanOrEqual);
        c = disableMask(c, hasBinaryOperatorLessThan);
        c = disableMask(c, hasBinaryOperatorLessThanOrEqual);
        break;
    case BuiltinTypeKind::String:
        c = enableMask(c, hasBinaryOperatorAdd);
        c = disableMask(c, hasBinaryOperatorSubtract);
        c = disableMask(c, hasBinaryOperatorMultiply);
        c = disableMask(c, hasBinaryOperatorDivide);
        c = disableMask(c, hasBinaryOperatorMod);
        c = enableMask(c, hasBinaryOperatorAssign);
        c = enableMask(c, hasBinaryOperatorEqual);
        c = enableMask(c, hasBinaryOperatorNotEqual);
        c = disableMask(c, hasBinaryOperatorLogicalAnd);
        c = disableMask(c, hasBinaryOperatorLogicalOr);
        c = disableMask(c, hasBinaryOperatorGreaterThan);
        c = disableMask(c, hasBinaryOperatorGreaterThanOrEqual);
        c = disableMask(c, hasBinaryOperatorLessThan);
        c = disableMask(c, hasBinaryOperatorLessThanOrEqual);
        break;
    case BuiltinTypeKind::Void:
        c = disableMask(c, hasBinaryOperatorAdd);
        c = disableMask(c, hasBinaryOperatorSubtract);
        c = disableMask(c, hasBinaryOperatorMultiply);
        c = disableMask(c, hasBinaryOperatorDivide);
        c = disableMask(c, hasBinaryOperatorMod);
        c = enableMask(c, hasBinaryOperatorAssign);
        c = disableMask(c, hasBinaryOperatorEqual);
        c = disableMask(c, hasBinaryOperatorNotEqual);
        c = disableMask(c, hasBinaryOperatorLogicalAnd);
        c = disableMask(c, hasBinaryOperatorLogicalOr);
        c = disableMask(c, hasBinaryOperatorGreaterThan);
        c = disableMask(c, hasBinaryOperatorGreaterThanOrEqual);
        c = disableMask(c, hasBinaryOperatorLessThan);
        c = disableMask(c, hasBinaryOperatorLessThanOrEqual);
        break;
    }
    return c;
}

TypeCapability getTypeCapability(const std::shared_ptr<Type>& type)
{
    TypeCapability c = 0;
    switch (type->getKind()) {
    case TypeKind::BuiltinType: {
        auto t = std::static_pointer_cast<BuiltinType>(type);
        assert(t == std::dynamic_pointer_cast<BuiltinType>(type));
        c = getTypeCapability(t->kind);
    } break;
    case TypeKind::ArrayType:
    case TypeKind::MapType:
    case TypeKind::TupleType:
    case TypeKind::FunctionType:
        c = disableMask(c, hasBinaryOperatorAdd);
        c = disableMask(c, hasBinaryOperatorSubtract);
        c = disableMask(c, hasBinaryOperatorMultiply);
        c = disableMask(c, hasBinaryOperatorDivide);
        c = disableMask(c, hasBinaryOperatorMod);
        c = enableMask(c, hasBinaryOperatorAssign);
        c = enableMask(c, hasBinaryOperatorEqual);
        c = enableMask(c, hasBinaryOperatorNotEqual);
        c = disableMask(c, hasBinaryOperatorLogicalAnd);
        c = disableMask(c, hasBinaryOperatorLogicalOr);
        c = disableMask(c, hasBinaryOperatorGreaterThan);
        c = disableMask(c, hasBinaryOperatorGreaterThanOrEqual);
        c = disableMask(c, hasBinaryOperatorLessThan);
        c = disableMask(c, hasBinaryOperatorLessThanOrEqual);
        break;
    case TypeKind::TypeVariable:
    case TypeKind::ReturnType:
        c = enableMask(c, hasBinaryOperatorAdd);
        c = enableMask(c, hasBinaryOperatorSubtract);
        c = enableMask(c, hasBinaryOperatorMultiply);
        c = enableMask(c, hasBinaryOperatorDivide);
        c = enableMask(c, hasBinaryOperatorMod);
        c = enableMask(c, hasBinaryOperatorAssign);
        c = enableMask(c, hasBinaryOperatorEqual);
        c = enableMask(c, hasBinaryOperatorNotEqual);
        c = enableMask(c, hasBinaryOperatorLogicalAnd);
        c = enableMask(c, hasBinaryOperatorLogicalOr);
        c = enableMask(c, hasBinaryOperatorGreaterThan);
        c = enableMask(c, hasBinaryOperatorGreaterThanOrEqual);
        c = enableMask(c, hasBinaryOperatorLessThan);
        c = enableMask(c, hasBinaryOperatorLessThanOrEqual);
        break;
    }
    return c;
}

uint64_t binaryOperatorMask(BinaryOperatorKind op)
{
    switch (op) {
    case BinaryOperatorKind::Add: return hasBinaryOperatorAdd;
    case BinaryOperatorKind::Subtract: return hasBinaryOperatorSubtract;
    case BinaryOperatorKind::Multiply: return hasBinaryOperatorMultiply;
    case BinaryOperatorKind::Divide: return hasBinaryOperatorDivide;
    case BinaryOperatorKind::Mod: return hasBinaryOperatorMod;
    case BinaryOperatorKind::Assign: return hasBinaryOperatorAssign;
    case BinaryOperatorKind::Equal: return hasBinaryOperatorEqual;
    case BinaryOperatorKind::NotEqual: return hasBinaryOperatorNotEqual;
    case BinaryOperatorKind::LogicalAnd: return hasBinaryOperatorLogicalAnd;
    case BinaryOperatorKind::LogicalOr: return hasBinaryOperatorLogicalOr;
    case BinaryOperatorKind::GreaterThan: return hasBinaryOperatorGreaterThan;
    case BinaryOperatorKind::GreaterThanOrEqual: return hasBinaryOperatorGreaterThanOrEqual;
    case BinaryOperatorKind::LessThan: return hasBinaryOperatorLessThan;
    case BinaryOperatorKind::LessThanOrEqual: return hasBinaryOperatorLessThanOrEqual;
    }
    return 0;
}

bool isBinaryOperatorValid(BinaryOperatorKind op, const std::shared_ptr<Type>& type)
{
    const auto mask = binaryOperatorMask(op);
    return (getTypeCapability(type) & mask) != 0;
}

std::string getDiagnosticString(const std::shared_ptr<Type>& type)
{
    switch (type->getKind()) {
    case TypeKind::BuiltinType:
    case TypeKind::ArrayType:
    case TypeKind::MapType:
    case TypeKind::TupleType:
    case TypeKind::FunctionType:
    case TypeKind::ReturnType: break;
    case TypeKind::TypeVariable: return "any";
    }
    return type->dump();
}

} // end of anonymous namespace

TypeResolver::TypeResolver(const std::shared_ptr<DiagnosticHandler>& diagIn)
    : diag(diagIn)
{
    assert(diag);
    auto scope = std::make_shared<TypeResolverScope>();
    pushScope(scope);
}

std::shared_ptr<TypeResolverScope> TypeResolver::getCurrentScope()
{
    assert(!scopeStack.empty());
    return scopeStack.back();
}

void TypeResolver::pushScope(const std::shared_ptr<TypeResolverScope>& scope)
{
    scopeStack.push_back(std::move(scope));
}

void TypeResolver::popScope()
{
    assert(!scopeStack.empty());
    scopeStack.pop_back();
}

void TypeResolver::error(const Location& l, const std::string& err)
{
    assert(diag);
    diag->error(l, err);
}

void TypeResolver::visit(const std::shared_ptr<CompoundStmt>& stmt, Invoke&& traverse)
{
    traverse();
}

void TypeResolver::visit(const std::shared_ptr<DeclStmt>& expr, Invoke&& traverse)
{
    traverse();
}

void TypeResolver::visit(const std::shared_ptr<ReturnStmt>& stmt, Invoke&& traverse)
{
    const auto scope = getCurrentScope();

    traverse();

    if (diag->hasError()) {
        return;
    }

    auto expr = stmt->getExpr();
    assert(expr);
    assert(expr->getType());
    scope->returnTypes.push_back(expr->getType());
}

void TypeResolver::visit(const std::shared_ptr<IfStmt>& stmt, Invoke&& traverse)
{
    traverse();

    const auto scope = getCurrentScope();

    ImplicitCastifyConditionExpr(
        scope, diag, [&] { return stmt->getCond(); }, [&](auto cond) { stmt->setCond(cond); });
    if (diag->hasError()) {
        return;
    }
}

void TypeResolver::visit(const std::shared_ptr<WhileStmt>& stmt, Invoke&& traverse)
{
    traverse();

    const auto scope = getCurrentScope();

    ImplicitCastifyConditionExpr(
        scope, diag, [&] { return stmt->getCond(); }, [&](auto cond) { stmt->setCond(cond); });
    if (diag->hasError()) {
        return;
    }
}

void TypeResolver::visit(const std::shared_ptr<ForStmt>& stmt, Invoke&& traverse)
{
    traverse();

    const auto scope = getCurrentScope();

    ImplicitCastifyConditionExpr(
        scope, diag, [&] { return stmt->getCond(); }, [&](auto cond) { stmt->setCond(cond); });
    if (diag->hasError()) {
        return;
    }
}

void TypeResolver::visit(const std::shared_ptr<CallExpr>& expr, Invoke&& traverse)
{
    traverse();

    assert(!expr->getType());

    const auto callee = expr->getCallee();
    assert(callee);

    const auto functionType = callee->getType();
    assert(functionType);

    std::vector<std::shared_ptr<Type>> argumentTypes;
    for (const auto& arg : expr->getArguments()) {
        assert(arg);
        assert(arg->getType());
        argumentTypes.push_back(arg->getType());
    }

    expr->setType(ReturnType::make(functionType, argumentTypes));
}

void TypeResolver::visit(const std::shared_ptr<FunctionExpr>& expr, Invoke&& traverse)
{
    const auto outerScope = getCurrentScope();
    const auto scope = std::make_shared<TypeResolverScope>();
    scope->env = outerScope->env;
    pushScope(scope);

    const auto typeVariable = TypeVariable::make();
    if (auto namedDecl = expr->getNamedDecl()) {
        assert(!namedDecl->getType());
        namedDecl->setType(typeVariable);
    }

    traverse();
    popScope();

    auto returnType = inferReturnType(scope);
    auto parameterTypes = getParameterTypes(expr->getParameters());
    auto functionType = FunctionType::make(std::move(returnType), std::move(parameterTypes));

    if (auto namedDecl = expr->getNamedDecl()) {
        substition(namedDecl, typeVariable, functionType);
    }

    assert(!expr->getType());
    expr->setType(functionType);
}

void TypeResolver::visit(const std::shared_ptr<IntegerLiteral>& expr)
{
    assert(!expr->getType());
    expr->setType(BuiltinType::make(BuiltinTypeKind::Int));
}

void TypeResolver::visit(const std::shared_ptr<DoubleLiteral>& expr)
{
    assert(!expr->getType());
    expr->setType(BuiltinType::make(BuiltinTypeKind::Double));
}

void TypeResolver::visit(const std::shared_ptr<BoolLiteral>& expr)
{
    assert(!expr->getType());
    expr->setType(BuiltinType::make(BuiltinTypeKind::Bool));
}

void TypeResolver::visit(const std::shared_ptr<StringLiteral>& expr)
{
    assert(!expr->getType());
    expr->setType(BuiltinType::make(BuiltinTypeKind::String));
}

void TypeResolver::visit(const std::shared_ptr<NullLiteral>& expr)
{
    assert(!expr->getType());
    expr->setType(BuiltinType::make(BuiltinTypeKind::Null));
}

void TypeResolver::visit(const std::shared_ptr<BinaryOperator>& expr, Invoke&& traverse)
{
    traverse();

    if (diag->hasError()) {
        return;
    }

    if (expr->isEqualityOp() || expr->isComparisonOp() || expr->isLogicalOp()) {
        assert(!expr->getType());
        expr->setType(BuiltinType::make(BuiltinTypeKind::Bool));
        return;
    }

    auto lhs = expr->getLHS();
    auto rhs = expr->getRHS();
    assert(lhs);
    assert(rhs);
    assert(lhs->getType());
    assert(rhs->getType());

    const auto scope = getCurrentScope();
    const auto lhsTypeInferred = TypeInferer::infer(scope->env, lhs->getType());
    const auto rhsTypeInferred = TypeInferer::infer(scope->env, rhs->getType());

    if (!isBinaryOperatorValid(expr->getKind(), lhsTypeInferred)) {
        error(
            lhs->getLocation(),
            "invalid operands to binary expression ('" + getDiagnosticString(lhsTypeInferred) +
                "' and '" + getDiagnosticString(rhsTypeInferred) + "').");
        return;
    }
    if (!isBinaryOperatorValid(expr->getKind(), rhsTypeInferred)) {
        error(
            rhs->getLocation(),
            "invalid operands to binary expression ('" + getDiagnosticString(lhsTypeInferred) +
                "' and '" + getDiagnosticString(rhsTypeInferred) + "').");
        return;
    }

    const auto [lhsType, lhsTypeEnabled] = TypeHelper::toBuiltinType(lhsTypeInferred);
    const auto [rhsType, rhsTypeEnabled] = TypeHelper::toBuiltinType(rhsTypeInferred);

    if (lhsType == BuiltinTypeKind::Void) {
        error(lhs->getLocation(), "lhs is 'void' type.");
        return;
    }
    if (rhsType == BuiltinTypeKind::Void) {
        error(rhs->getLocation(), "rhs is 'void' type.");
        return;
    }

    if (lhsTypeInferred->getKind() == TypeKind::MapType) {
        if (rhsTypeInferred->getKind() == TypeKind::MapType) {
            // NOTE: The operator doesn't need to implicitly cast types of operands.
            assert(!expr->getType());
            expr->setType(lhs->getType());
            return;
        }
        error(
            expr->getLocation(),
            "Operator '" + BinaryOperator::toString(expr->getKind()) +
                "' cannot be applied to types '" + getDiagnosticString(lhsTypeInferred) +
                "' and '" + getDiagnosticString(rhsTypeInferred) + "'.");
        return;
    }
    if (lhsTypeInferred->getKind() == TypeKind::ArrayType) {
        if (rhsTypeInferred->getKind() == TypeKind::ArrayType) {
            // NOTE: The operator doesn't need to implicitly cast types of operands.
            assert(!expr->getType());
            expr->setType(lhs->getType());
            return;
        }
        error(
            expr->getLocation(),
            "Operator '" + BinaryOperator::toString(expr->getKind()) +
                "' cannot be applied to types '" + getDiagnosticString(lhsTypeInferred) +
                "' and '" + getDiagnosticString(rhsTypeInferred) + "'.");
        return;
    }

    if (!lhsTypeEnabled || !rhsTypeEnabled) {
        // NOTE: resolving types on runtime, so this process is skipped
        assert(!expr->getType());
        expr->setType(BuiltinType::make(BuiltinTypeKind::Any));
        return;
    }

    if (lhsType == rhsType) {
        // NOTE: The operator doesn't need to implicitly cast types of operands.
        assert(!expr->getType());
        expr->setType(lhs->getType());
        return;
    }

    const auto [castType, castResult] = inferBinaryOpTypeCast(lhsType, rhsType);
    assert(castType != BuiltinTypeKind::Void);

    if (castResult == BinaryOpTypeCastResult::TypeMismatch) {
        if (expr->isAssignmentOp()) {
            assert(lhsTypeInferred);
            assert(rhsTypeInferred);
            error(
                expr->getLocation(),
                "Type '" + rhsTypeInferred->dump() + "' is not assignable to '" +
                    lhsTypeInferred->dump() + "'.");
            return;
        }

        error(
            expr->getLocation(),
            "Operator '" + BinaryOperator::toString(expr->getKind()) +
                "' cannot be applied to types '" + lhsTypeInferred->dump() + "' and '" +
                rhsTypeInferred->dump() + "'.");
        return;
    }

    if (castResult == BinaryOpTypeCastResult::ResolveOnRuntime) {
        // NOTE: resolving types on runtime, so this process is skipped
        assert(!expr->getType());

        if (expr->isAssignmentOp()) {
            expr->setType(lhs->getType());
            return;
        }

        expr->setType(BuiltinType::make(BuiltinTypeKind::Any));
        return;
    }

    if (lhsType != castType) {
        if (expr->isAssignmentOp()) {
            assert(lhsTypeInferred);
            assert(rhsTypeInferred);
            error(
                expr->getLocation(),
                "Type '" + rhsTypeInferred->dump() + "' is not assignable to '" +
                    lhsTypeInferred->dump() + "'.");
            return;
        }

        assert(rhsType == castType);
        auto typeCastExpr = ImplicitStaticCastExpr::make(lhs->getLocation(), lhs);
        typeCastExpr->setType(BuiltinType::make(castType));
        expr->setLHS(typeCastExpr);
        lhs = typeCastExpr;
    }
    else {
        assert(rhsType != castType);
        assert(lhsType == castType);
        auto typeCastExpr = ImplicitStaticCastExpr::make(rhs->getLocation(), rhs);
        typeCastExpr->setType(BuiltinType::make(castType));
        expr->setRHS(typeCastExpr);
        rhs = typeCastExpr;
    }

    assert(!expr->getType());
    expr->setType(lhs->getType());
}

void TypeResolver::visit(const std::shared_ptr<UnaryOperator>& expr, Invoke&& traverse)
{
    const auto outerScope = getCurrentScope();
    const auto scope = std::make_shared<TypeResolverScope>();
    scope->env = outerScope->env;
    pushScope(scope);

    traverse();
    popScope();

    const auto subExpr = expr->getSubExpr();
    assert(subExpr);
    assert(subExpr->getType());

    const auto t = TypeInferer::infer(scope->env, subExpr->getType());
    assert(t);

    switch (expr->getKind()) {
    case UnaryOperatorKind::Plus:
    case UnaryOperatorKind::Minus:
    case UnaryOperatorKind::PostDec:
    case UnaryOperatorKind::PreDec:
    case UnaryOperatorKind::PostInc:
    case UnaryOperatorKind::PreInc:
        if (isFloatingPoint(t) || isIntegral(t)) {
            assert(!expr->getType());
            expr->setType(t);
            return;
        }
        break;
    case UnaryOperatorKind::LogicalNot: {
        ImplicitCastifyConditionExpr(
            scope,
            diag,
            [&] { return expr->getSubExpr(); },
            [&](auto cond) { expr->setSubExpr(cond); });

        if (isBoolean(t)) {
            assert(!expr->getType());
            expr->setType(t);
            return;
        }
        expr->setType(BuiltinType::make(BuiltinTypeKind::Bool));
        return;
        break;
    }
    }
    assert(!expr->getType());
    expr->setType(subExpr->getType());
}

void TypeResolver::visit(const std::shared_ptr<DeclRefExpr>& expr, Invoke&& traverse)
{
    traverse();

    assert(!expr->getType());

    auto namedDecl = expr->getNamedDecl();
    assert(namedDecl);
    assert(namedDecl->getType());
    expr->setType(namedDecl->getType());
}

void TypeResolver::visit(const std::shared_ptr<ArrayLiteral>& expr, Invoke&& traverse)
{
    traverse();

    assert(!expr->getType());

    auto arrayType = ArrayType::make();
    auto scope = getCurrentScope();

    for (auto& init : expr->getInits()) {
        auto t = init->getType();
        if (t->getKind() == TypeKind::TypeVariable) {
            auto typeVariable = std::dynamic_pointer_cast<TypeVariable>(t);
            auto s = TypeInferer::infer(scope->env, t);
            substition(init, typeVariable, s);
        }
    }

    if (!expr->getInits().empty()) {
        // TODO: Use union type instead of type of first element
        auto first = expr->getInits().front();
        auto primaryType = first->getType();
        for (auto& init : expr->getInits()) {
            if (primaryType == init->getType()) {
                continue;
            }
            if (!isSameType(primaryType, init->getType())) {
                primaryType = nullptr;
                break;
            }
        }
        arrayType->primaryType = primaryType;
    }

    expr->setType(arrayType);
}

void TypeResolver::visit(const std::shared_ptr<MapEntry>& expr, Invoke&& traverse)
{
    traverse();

    assert(!expr->getType());

    auto key = expr->getKey();
    auto value = expr->getValue();

    assert(key);
    assert(key->getType());
    assert(value);
    assert(value->getType());

    auto scope = getCurrentScope();

    auto infer = [&](std::shared_ptr<Expr>& ast) {
        auto t = ast->getType();
        if (t->getKind() == TypeKind::TypeVariable) {
            auto typeVariable = std::dynamic_pointer_cast<TypeVariable>(t);
            auto s = TypeInferer::infer(scope->env, t);
            substition(ast, typeVariable, s);
        }
    };
    infer(key);
    infer(value);

    auto type = TupleType::make({key->getType(), value->getType()});
    expr->setType(type);
}

void TypeResolver::visit(const std::shared_ptr<MapLiteral>& expr, Invoke&& traverse)
{
    traverse();

    assert(!expr->getType());

    auto mapType = MapType::make();

    if (!expr->getEntries().empty()) {
        auto first = expr->getEntries().front();
        assert(first->getType());
        assert(first->getType()->getKind() == TypeKind::TupleType);

        auto tupleType = std::dynamic_pointer_cast<TupleType>(first->getType());
        assert(tupleType);
        assert(tupleType->types.size() == 2);

        // TODO: Use union type instead of type of first element
        for (auto& entry : expr->getEntries()) {
            if (tupleType == entry->getType()) {
                continue;
            }
            if (!isSameType(tupleType, entry->getType())) {
                tupleType = nullptr;
                break;
            }
        }

        if (tupleType != nullptr) {
            mapType->keyType = tupleType->types[0];
            mapType->valueType = tupleType->types[1];
        }
    }

    expr->setType(mapType);
}

void TypeResolver::visit(const std::shared_ptr<FunctionDecl>& decl, Invoke&& traverse)
{
    const auto outerScope = getCurrentScope();
    const auto scope = std::make_shared<TypeResolverScope>();
    scope->env = outerScope->env;
    pushScope(scope);

    const auto typeVariable = TypeVariable::make();
    if (auto namedDecl = decl->getNamedDecl()) {
        assert(!namedDecl->getType());
        namedDecl->setType(typeVariable);
    }

    traverse();
    popScope();

    auto returnType = inferReturnType(scope);
    auto parameterTypes = getParameterTypes(decl->getParameters());
    auto functionType = FunctionType::make(std::move(returnType), std::move(parameterTypes));

    if (auto namedDecl = decl->getNamedDecl()) {
        substition(namedDecl, typeVariable, functionType);
    }

    assert(!decl->getType());
    decl->setType(functionType);
}

void TypeResolver::visit(const std::shared_ptr<ParmVarDecl>& decl, Invoke&& traverse)
{
    const auto namedDecl = decl->getNamedDecl();
    assert(namedDecl);
    assert(!namedDecl->getName().empty());
    assert(!namedDecl->getType());

    if (auto typeAnnotation = decl->getTypeAnnotation()) {
        auto entity = typeAnnotation->getEntity();
        assert(entity);
        assert(entity->getKind() == EntityKind::Type);
        assert(entity->getType());
        auto type = entity->getType();
        namedDecl->setType(type);
    }
    else {
        auto typeVariable = TypeVariable::make();
        namedDecl->setType(typeVariable);
    }

    traverse();

    assert(namedDecl->getType());
    assert(!decl->getType());
    decl->setType(namedDecl->getType());
}

void TypeResolver::visit(const std::shared_ptr<VariableDecl>& decl, Invoke&& traverse)
{
    const auto namedDecl = decl->getNamedDecl();
    assert(namedDecl);
    assert(!namedDecl->getName().empty());
    assert(!namedDecl->getType());

    const auto typeVariable = TypeVariable::make();
    namedDecl->setType(typeVariable);

    traverse();

    if (diag->hasError()) {
        return;
    }

    if (auto expr = decl->getExpr()) {
        assert(expr->getType());
        auto scope = getCurrentScope();
        typeVariable->setType(expr->getType());

        auto s = TypeInferer::infer(scope->env, typeVariable);
        substition(namedDecl, typeVariable, s);
    }
    else {
        typeVariable->setType(BuiltinType::make(BuiltinTypeKind::Any));
    }

    assert(!decl->getType());
    decl->setType(BuiltinType::make(BuiltinTypeKind::Void));
}

void TypeResolver::visit(const std::shared_ptr<ConstDecl>& decl, Invoke&& traverse)
{
    const auto namedDecl = decl->getNamedDecl();
    assert(namedDecl);
    assert(!namedDecl->getName().empty());
    assert(!namedDecl->getType());

    const auto typeVariable = TypeVariable::make();
    namedDecl->setType(typeVariable);

    traverse();

    if (auto expr = decl->getExpr()) {
        assert(expr->getType());
        auto scope = getCurrentScope();
        typeVariable->setType(expr->getType());

        auto s = TypeInferer::infer(scope->env, typeVariable);
        substition(namedDecl, typeVariable, s);
    }
    else {
        typeVariable->setType(BuiltinType::make(BuiltinTypeKind::Any));
    }

    assert(!decl->getType());
    decl->setType(BuiltinType::make(BuiltinTypeKind::Void));
}

void TypeResolver::visit(const std::shared_ptr<NamedDecl>& decl)
{
    if (decl->getType()) {
        return;
    }

    auto entity = decl->getEntity();
    assert(entity);
    assert(
        (entity->getKind() == EntityKind::Variable) || (entity->getKind() == EntityKind::Constant));
    assert(entity->getDecl());
    assert(entity->getDecl()->getType());
    if (decl == entity->getDecl()) {
        return;
    }

    auto type = entity->getDecl()->getType();
    decl->setType(type);
}
