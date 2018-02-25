#include "TypeResolver.h"
#include "Decl.h"
#include "Expr.h"
#include "IdentifierResolver.h"
#include "Stmt.h"
#include <cassert>
#include <sstream>
#include <utility>

namespace {

class ScopedFunc final {
    std::function<void()> defer;

public:
    explicit ScopedFunc(std::function<void()>&& d)
        : defer(std::move(d))
    {
    }

    ~ScopedFunc()
    {
        if (defer) {
            defer();
        }
    }
};

//std::shared_ptr<Type> prune(const std::shared_ptr<Type>& type)
//{
//    auto typeVariable = std::dynamic_pointer_cast<TypeVariable>(type);
//    if (typeVariable) {
//        if (auto instance = typeVariable->getType()) {
//            return instance;
//        }
//    }
//    return type;
//}
//
//std::shared_ptr<const Type> unify(const std::shared_ptr<const Type>& type)
//{
//    const auto typeVariable = std::dynamic_pointer_cast<const TypeVariable>(type);
//    if (!typeVariable) {
//        return type;
//    }
//
//    auto t = typeVariable;
//    while (t) {
//        const auto a = t->getType();
//        const auto v = std::dynamic_pointer_cast<const TypeVariable>(a);
//        if (!v) {
//            return a;
//        }
//        t = v;
//        assert(t != typeVariable);
//    }
//    return t;
//}

} // end of anonymous namespace

TypeResolver::TypeResolver()
{
    auto env = std::make_shared<TypeEnvironment>();
    pushScope(env);

    env->defineAlias("int", BuiltinType::make(BuiltinTypeKind::Int));
    env->defineAlias("bool", BuiltinType::make(BuiltinTypeKind::Bool));
    env->defineAlias("double", BuiltinType::make(BuiltinTypeKind::Double));
    env->defineAlias("string", BuiltinType::make(BuiltinTypeKind::Int));
    env->defineAlias("void", BuiltinType::make(BuiltinTypeKind::Void));
}

std::shared_ptr<TypeEnvironment> TypeResolver::getCurrentScope()
{
    assert(!scopeStack.empty());
    return scopeStack.back();
}

void TypeResolver::pushScope(const std::shared_ptr<TypeEnvironment>& scope)
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

void TypeResolver::visit(const std::shared_ptr<ReturnStmt>& stmt, Invoke&& traverse)
{
    const auto env = getCurrentScope();

    traverse();

    assert(stmt->expr);
    assert(stmt->expr->getType());
    env->returnTypes.push_back(stmt->expr->getType());
}

void TypeResolver::visit(const std::shared_ptr<DeclStmt>& expr, Invoke&& traverse)
{
    traverse();
}

void TypeResolver::visit(const std::shared_ptr<CallExpr>& expr, Invoke&& traverse)
{
    traverse();

    assert(!expr->getType());
    assert(expr->callee);

    auto functionType = expr->callee->getType();
    assert(functionType);

    std::vector<std::shared_ptr<Type>> argumentTypes;
    for (const auto& arg : expr->arguments) {
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

void TypeResolver::visit(const std::shared_ptr<BinaryOperator>& expr, Invoke&& traverse)
{
    traverse();

    const auto logicalOp = [&]() -> bool {
        switch (expr->kind) {
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

    assert(expr->lhs);
    assert(expr->rhs);
    assert(expr->lhs->getType());
    assert(expr->rhs->getType());

    // TODO: Not implemented
    assert(!expr->getType());
    expr->setType(expr->lhs->getType());
}

void TypeResolver::visit(const std::shared_ptr<DeclRefExpr>& expr, Invoke&& traverse)
{
    traverse();

    assert(!expr->getType());
    assert(expr->decl);
    assert(expr->decl->getType());
    expr->setType(expr->decl->getType());
}

void TypeResolver::visit(const std::shared_ptr<FunctionDecl>& decl, Invoke&& traverse)
{
    const auto parentEnv = getCurrentScope();
    const auto env = std::make_shared<TypeEnvironment>(parentEnv);
    pushScope(env);
    ScopedFunc scoped([&] { popScope(); });

    const auto typeVariable = TypeVariable::make();
    if (decl->namedDecl) {
        auto namedDecl = decl->namedDecl;
        assert(namedDecl);
        assert(!namedDecl->getType());
        namedDecl->setType(typeVariable);
        parentEnv->defineIdent(namedDecl->getName(), namedDecl->getType());
    }

    traverse();

    auto returnType = [&]() -> std::shared_ptr<Type> {
        if (env->returnTypes.empty()) {
            return BuiltinType::make(BuiltinTypeKind::Void);
        }
        std::shared_ptr<Type> candidate = env->returnTypes.back();
        for (const auto& ret : env->returnTypes) {
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
    const auto env = getCurrentScope();

    const auto namedDecl = decl->namedDecl;
    assert(namedDecl);
    assert(!namedDecl->getName().empty());
    assert(!namedDecl->getType());

    if (decl->typeAnnotation) {
        auto type = env->getAlias(decl->typeAnnotation->getName());
        if (type) {
            namedDecl->setType(type);
        }

        // TODO: Not implemented
        assert(type);
    }
    else {
        auto typeVariable = TypeVariable::make();
        namedDecl->setType(typeVariable);
    }

    env->defineIdent(namedDecl->getName(), namedDecl->getType());

    traverse();

    assert(namedDecl->getType());
    assert(!decl->getType());
    decl->setType(namedDecl->getType());
}

void TypeResolver::visit(const std::shared_ptr<VariableDecl>& decl, Invoke&& traverse)
{
    const auto env = getCurrentScope();

    const auto namedDecl = decl->namedDecl;
    assert(namedDecl);
    assert(!namedDecl->getName().empty());
    assert(!namedDecl->getType());

    const auto typeVariable = TypeVariable::make();
    namedDecl->setType(typeVariable);

    env->defineIdent(namedDecl->getName(), namedDecl->getType());

    traverse();

    if (!decl->expr) {
        typeVariable->setType(BuiltinType::make(BuiltinTypeKind::Any));
    }
    else {
        assert(decl->expr);
        assert(decl->expr->getType());
        typeVariable->setType(decl->expr->getType());
    }

    assert(!decl->getType());
    decl->setType(BuiltinType::make(BuiltinTypeKind::Void));
}

void TypeResolver::visit(const std::shared_ptr<NamedDecl>& decl)
{
    if (decl->getType()) {
        return;
    }

    auto env = getCurrentScope();

    auto type = env->getIdent(decl->getName());
    if (!type) {
        error(decl->getLocation(), "'" + decl->getName() + "' was not declared in this scope.");
        return;
    }

    decl->setType(type);
}
