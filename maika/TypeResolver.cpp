#include "TypeResolver.h"
#include "Decl.h"
#include "Entity.h"
#include "Expr.h"
#include "IdentifierResolver.h"
#include "Stmt.h"
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

} // end of anonymous namespace

TypeResolver::TypeResolver()
{
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

void TypeResolver::error(const yy::location& l, const std::string& err)
{
    std::cerr << l << ": " << err << std::endl;
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
    if (decl->namedDecl) {
        auto namedDecl = decl->namedDecl;
        assert(namedDecl);
        assert(!namedDecl->getType());
        namedDecl->setType(typeVariable);
    }

    traverse();
    popScope();

    auto returnType = [&]() -> std::shared_ptr<Type> {
        if (scope->returnTypes.empty()) {
            return BuiltinType::make(BuiltinTypeKind::Void);
        }
        std::shared_ptr<Type> candidate = scope->returnTypes.back();
        for (const auto& ret : scope->returnTypes) {
            if (candidate != ret) {
                return BuiltinType::make(BuiltinTypeKind::Any);
            }
        }
        return candidate;
    }();

    std::vector<std::shared_ptr<Type>> parameterTypes;
    for (const auto& param : decl->arguments) {
        assert(param);
        assert(param->getType());
        parameterTypes.push_back(param->getType());
    }

    auto functionType = FunctionType::make(returnType, parameterTypes);
    typeVariable->setType(functionType);

    assert(!decl->getType());
    decl->setType(BuiltinType::make(BuiltinTypeKind::Void));
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
