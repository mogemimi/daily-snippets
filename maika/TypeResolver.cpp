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

class ScopedFunc final {
    std::function<void()> defer;

public:
    ScopedFunc(std::function<void()>&& d)
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

std::shared_ptr<const Type> unify(const std::shared_ptr<const Type>& type)
{
    const auto typeVariable = std::dynamic_pointer_cast<const TypeVariable>(type);
    if (!typeVariable) {
        return type;
    }

    auto t = typeVariable;
    while (t) {
        const auto a = t->getType();
        const auto v = std::dynamic_pointer_cast<const TypeVariable>(a);
        if (!v) {
            return a;
        }
        t = v;
        assert(t != typeVariable);
    }
    return t;
}

} // end of anonymous namespace

TypeResolver::TypeResolver()
{
    auto scope = std::make_shared<TypeEnvironment>();
    pushScope(scope);

    scope->defineType("int", BuiltinType::make(BuiltinTypeKind::Int));
    scope->defineType("bool", BuiltinType::make(BuiltinTypeKind::Bool));
    scope->defineType("double", BuiltinType::make(BuiltinTypeKind::Double));
    scope->defineType("string", BuiltinType::make(BuiltinTypeKind::Int));
    scope->defineType("void", BuiltinType::make(BuiltinTypeKind::Void));
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
    traverse();
    assert(stmt->expr);
    assert(stmt->expr->getType());
    lastReturnType = stmt->expr->getType();
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

    auto functionType = unify(expr->callee->getType());
    assert(functionType);

    if (auto callableType = std::dynamic_pointer_cast<const FunctionType>(functionType)) {
        if (expr->arguments.size() != callableType->parameterTypes.size()) {
            error(expr->getLocation(), "Argument count mismatch");
        }

        auto returnType = callableType->returnType;
        assert(returnType);
        expr->setType(returnType);
    }
    else {
        expr->setType(BuiltinType::make(BuiltinTypeKind::Any));
    }
}

void TypeResolver::visit(const std::shared_ptr<IntegerLiteral>& expr)
{
    assert(expr->getType());
}

void TypeResolver::visit(const std::shared_ptr<DoubleLiteral>& expr)
{
    assert(expr->getType());
}

void TypeResolver::visit(const std::shared_ptr<BoolLiteral>& expr)
{
    assert(expr->getType());
}

void TypeResolver::visit(const std::shared_ptr<BinaryOperator>& expr, Invoke&& traverse)
{
    traverse();
    assert(!expr->getType());

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
        expr->setType(BuiltinType::make(BuiltinTypeKind::Bool));
        return;
    }

    assert(expr->lhs);
    assert(expr->rhs);
    assert(expr->lhs->getType());
    assert(expr->rhs->getType());

    // TODO: Not implemented
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
    const auto parentScope = getCurrentScope();
    const auto typeEnv = std::make_shared<TypeEnvironment>(parentScope);
    pushScope(typeEnv);
    ScopedFunc scoped([&] { popScope(); });

    const auto typeVariable = TypeVariable::make(typeEnv->getNextIndex());
    if (decl->namedDecl) {
        assert(!decl->namedDecl->getType());
        decl->namedDecl->setType(typeVariable);
    }

    traverse();

    assert(!decl->getType());

    auto functionType = FunctionType::make();
    if (lastReturnType) {
        functionType->returnType = lastReturnType;
    }
    for (const auto& param : decl->arguments) {
        assert(param);
        assert(param->getType());
        functionType->parameterTypes.push_back(param->getType());
    }

    typeVariable->setType(functionType);

    // NOTE: this is declaration.
    decl->setType(BuiltinType::make(BuiltinTypeKind::Void));

    lastReturnType = nullptr;
}

void TypeResolver::visit(const std::shared_ptr<ParmVarDecl>& decl, Invoke&& traverse)
{
    const auto typeEnv = getCurrentScope();

    assert(decl->namedDecl);
    assert(!decl->namedDecl->getType());

    if (decl->typeAnnotation) {
        auto type = typeEnv->getType(decl->typeAnnotation->getName());
        if (type) {
            decl->namedDecl->setType(type);
        }
    }
    else {
        const auto typeVariable = TypeVariable::make(typeEnv->getNextIndex());
        decl->namedDecl->setType(typeVariable);
    }

    traverse();

    auto type = decl->namedDecl->getType();
    assert(type);

    assert(!decl->getType());
    decl->setType(type);
}

void TypeResolver::visit(const std::shared_ptr<VariableDecl>& decl, Invoke&& traverse)
{
    assert(decl->namedDecl);
    assert(!decl->namedDecl->getType());
    auto typeEnv = getCurrentScope();

    const auto typeVariable = TypeVariable::make(typeEnv->getNextIndex());
    decl->namedDecl->setType(typeVariable);

    traverse();
    assert(!decl->getType());

    if (!decl->expr) {
        typeVariable->setType(BuiltinType::make(BuiltinTypeKind::Any));
    }
    else {
        // TODO:
        assert(decl->expr);
        assert(decl->expr->getType());
        typeVariable->setType(decl->expr->getType());
    }

    // NOTE: this is declaration.
    decl->setType(BuiltinType::make(BuiltinTypeKind::Void));
}

void TypeResolver::visit(const std::shared_ptr<NamedDecl>& decl)
{
    if (decl->getType()) {
        return;
    }

    auto typeEnv = getCurrentScope();

    auto entity = decl->getEntity();
    assert(entity);
    auto d = entity->getDecl();
    assert(d);

    if (decl == d) {
        d->setType(TypeVariable::make(typeEnv->getNextIndex()));
        return;
    }

    if (auto type = d->getType()) {
        decl->setType(type);
    }
}
