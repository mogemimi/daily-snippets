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

bool isSameType(const std::shared_ptr<Type>& a, const std::shared_ptr<Type>& b)
{
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
        return (x->getKind() == y->getKind());
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

    auto expr = stmt->getExpr();
    assert(expr);
    assert(expr->getType());
    scope->returnTypes.push_back(expr->getType());
}

void TypeResolver::visit(const std::shared_ptr<IfStmt>& stmt, Invoke&& traverse)
{
    traverse();
}

void TypeResolver::visit(const std::shared_ptr<WhileStmt>& stmt, Invoke&& traverse)
{
    traverse();
}

void TypeResolver::visit(const std::shared_ptr<ForStmt>& stmt, Invoke&& traverse)
{
    traverse();
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

void TypeResolver::visit(const std::shared_ptr<BinaryOperator>& expr, Invoke&& traverse)
{
    traverse();

    const auto logicalOp = [&]() -> bool {
        switch (expr->getKind()) {
        case BinaryOperatorKind::Equal: return true;
        case BinaryOperatorKind::NotEqual: return true;
        case BinaryOperatorKind::LogicalAnd: return true;
        case BinaryOperatorKind::LogicalOr: return true;
        case BinaryOperatorKind::GreaterThan: return true;
        case BinaryOperatorKind::GreaterThanOrEqual: return true;
        case BinaryOperatorKind::LessThan: return true;
        case BinaryOperatorKind::LessThanOrEqual: return true;
        default: break;
        }
        return false;
    }();

    if (logicalOp) {
        assert(!expr->getType());
        expr->setType(BuiltinType::make(BuiltinTypeKind::Bool));
        return;
    }

    const auto lhs = expr->getLHS();
    const auto rhs = expr->getRHS();
    assert(lhs);
    assert(rhs);
    assert(lhs->getType());
    assert(rhs->getType());

    // TODO: Not implemented
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
    case UnaryOperatorKind::LogicalNot:
        if (isBoolean(t)) {
            assert(!expr->getType());
            expr->setType(t);
            return;
        }
        expr->setType(BuiltinType::make(BuiltinTypeKind::Bool));
        return;
        break;
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
    assert(entity->getKind() == EntityKind::Variable);
    assert(entity->getDecl());
    assert(entity->getDecl()->getType());
    if (decl == entity->getDecl()) {
        return;
    }

    auto type = entity->getDecl()->getType();
    decl->setType(type);
}
