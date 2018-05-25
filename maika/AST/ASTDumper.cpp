#include "AST/ASTDumper.h"
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

std::string makeIndent(int level)
{
    std::stringstream ss;
    for (int i = 0; i < level; i++) {
        ss << "  ";
    }
    return ss.str();
}

template <class Dumper>
void dump(Dumper* dumper, const std::string& name, const std::vector<std::string>& options)
{
    const auto indent = makeIndent(dumper->level);
    dumper->result += indent + name;
    for (const auto& opt : options) {
        dumper->result += " '";
        dumper->result += opt;
        dumper->result += "'";
    }
    dumper->result += "\n";
}

template <class Dumper, class Traverser>
void dump(
    Dumper* dumper,
    const std::string& name,
    const std::vector<std::string>& options,
    Traverser&& traverse)
{
    dump(dumper, name, options);

    ++dumper->level;
    traverse();
    --dumper->level;
    assert(dumper->level >= 0);
}

} // end of anonymous namespace

std::string ASTDumper::getResult() const
{
    return dumpContext.result;
}

void ASTDumper::visit(const std::shared_ptr<CompoundStmt>& stmt, Invoke&& traverse)
{
    dump(&dumpContext, "CompoundStmt", {}, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<DeclStmt>& stmt, Invoke&& traverse)
{
    dump(&dumpContext, "DeclStmt", {}, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<ReturnStmt>& stmt, Invoke&& traverse)
{
    dump(&dumpContext, "ReturnStmt", {}, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<IfStmt>& stmt, Invoke&& traverse)
{
    dump(&dumpContext, "IfStmt", {}, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<WhileStmt>& stmt, Invoke&& traverse)
{
    dump(&dumpContext, "WhileStmt", {}, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<ForStmt>& stmt, Invoke&& traverse)
{
    dump(&dumpContext, "ForStmt", {}, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<ForRangeStmt>& stmt, Invoke&& traverse)
{
    dump(&dumpContext, "ForRangeStmt", {}, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<CallExpr>& expr, Invoke&& traverse)
{
    std::vector<std::string> options;
    if (auto type = expr->getType()) {
        options.push_back(type->dump());
    }
    dump(&dumpContext, "CallExpr", options, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<FunctionExpr>& expr, Invoke&& traverse)
{
    std::vector<std::string> options;
    if (auto namedDecl = expr->getNamedDecl()) {
        options.push_back(namedDecl->getName());
    }
    if (auto type = expr->getType()) {
        options.push_back(type->dump());
    }
    dump(&dumpContext, "FunctionExpr", options, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<IntegerLiteral>& expr)
{
    std::vector<std::string> options;
    options.push_back(std::to_string(expr->getValue()));
    if (auto type = expr->getType()) {
        options.push_back(type->dump());
    }
    dump(&dumpContext, "IntegerLiteral", options);
}

void ASTDumper::visit(const std::shared_ptr<DoubleLiteral>& expr)
{
    std::vector<std::string> options;
    options.push_back(std::to_string(expr->getValue()));
    if (auto type = expr->getType()) {
        options.push_back(type->dump());
    }
    dump(&dumpContext, "DoubleLiteral", options);
}

void ASTDumper::visit(const std::shared_ptr<BoolLiteral>& expr)
{
    std::vector<std::string> options;
    options.push_back(expr->getValue() ? "true" : "false");
    if (auto type = expr->getType()) {
        options.push_back(type->dump());
    }
    dump(&dumpContext, "BoolLiteral", options);
}

void ASTDumper::visit(const std::shared_ptr<StringLiteral>& expr)
{
    std::vector<std::string> options;
    options.push_back(expr->getValue());
    if (auto type = expr->getType()) {
        options.push_back(type->dump());
    }
    dump(&dumpContext, "StringLiteral", options);
}

void ASTDumper::visit(const std::shared_ptr<NullLiteral>& expr)
{
    std::vector<std::string> options;
    if (auto type = expr->getType()) {
        options.push_back(type->dump());
    }
    dump(&dumpContext, "NullLiteral", options);
}

void ASTDumper::visit(const std::shared_ptr<BinaryOperator>& expr, Invoke&& traverse)
{
    std::vector<std::string> options;

    auto op = BinaryOperator::toString(expr->getKind());
    options.push_back(op);
    if (auto type = expr->getType()) {
        options.push_back(type->dump());
    }
    dump(&dumpContext, "BinaryOperator", options, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<UnaryOperator>& expr, Invoke&& traverse)
{
    std::vector<std::string> options;

    auto op = UnaryOperator::toString(expr->getKind());
    options.push_back(op);
    if (auto type = expr->getType()) {
        options.push_back(type->dump());
    }
    dump(&dumpContext, "UnaryOperator", options, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<DeclRefExpr>& expr, Invoke&& traverse)
{
    std::vector<std::string> options;
    if (auto namedDecl = expr->getNamedDecl()) {
        options.push_back(namedDecl->getName());
        if (auto type = namedDecl->getType()) {
            options.push_back(type->dump());
        }
    }
    dump(&dumpContext, "DeclRefExpr", options, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<ParenExpr>& expr, Invoke&& traverse)
{
    std::vector<std::string> options;
    dump(&dumpContext, "ParenExpr", options, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<MemberExpr>& expr, Invoke&& traverse)
{
    std::vector<std::string> options;
    if (auto namedDecl = expr->getMemberDecl()) {
        options.push_back(namedDecl->getName());
        if (auto type = namedDecl->getType()) {
            options.push_back(type->dump());
        }
    }
    dump(&dumpContext, "MemberExpr", options, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<SubscriptExpr>& expr, Invoke&& traverse)
{
    std::vector<std::string> options;
    if (auto type = expr->getType()) {
        options.push_back(type->dump());
    }
    dump(&dumpContext, "SubscriptExpr", options, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<ArrayLiteral>& expr, Invoke&& traverse)
{
    std::vector<std::string> options;
    if (auto type = expr->getType()) {
        options.push_back(type->dump());
    }
    dump(&dumpContext, "ArrayLiteral", options, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<MapEntry>& expr, Invoke&& traverse)
{
    std::vector<std::string> options;
    dump(&dumpContext, "MapEntry", options, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<MapLiteral>& expr, Invoke&& traverse)
{
    std::vector<std::string> options;
    if (auto type = expr->getType()) {
        options.push_back(type->dump());
    }
    dump(&dumpContext, "MapLiteral", options, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<ImplicitStaticCastExpr>& expr, Invoke&& traverse)
{
    std::vector<std::string> options;
    if (auto type = expr->getType()) {
        options.push_back(type->dump());
    }
    dump(&dumpContext, "ImplicitStaticCastExpr", options, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<TranslationUnitDecl>& decl, Invoke&& traverse)
{
    dump(&dumpContext, "TranslationUnitDecl", {}, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<FunctionDecl>& decl, Invoke&& traverse)
{
    std::vector<std::string> options;
    if (auto namedDecl = decl->getNamedDecl()) {
        options.push_back(namedDecl->getName());
        if (auto type = namedDecl->getType()) {
            options.push_back(type->dump());
        }
    }
    dump(&dumpContext, "FunctionDecl", options, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<ParmVarDecl>& decl, Invoke&& traverse)
{
    std::vector<std::string> options;

    auto namedDecl = decl->getNamedDecl();
    assert(namedDecl);
    options.push_back(namedDecl->getName());

    if (auto typeAnnotation = decl->getTypeAnnotation()) {
        options.push_back(typeAnnotation->getName());
    }
    if (auto type = namedDecl->getType()) {
        options.push_back(type->dump());
    }
    dump(&dumpContext, "ParmVarDecl", options, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<VariableDecl>& decl, Invoke&& traverse)
{
    std::vector<std::string> options;
    if (auto namedDecl = decl->getNamedDecl()) {
        options.push_back(namedDecl->getName());
        if (auto type = namedDecl->getType()) {
            options.push_back(type->dump());
        }
    }
    dump(&dumpContext, "VariableDecl", options, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<ConstDecl>& decl, Invoke&& traverse)
{
    std::vector<std::string> options;
    if (auto namedDecl = decl->getNamedDecl()) {
        options.push_back(namedDecl->getName());
        if (auto type = namedDecl->getType()) {
            options.push_back(type->dump());
        }
    }
    dump(&dumpContext, "ConstDecl", options, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<BindingDecl>& decl, Invoke&& traverse)
{
    std::vector<std::string> options;
    if (auto namedDecl = decl->getNamedDecl()) {
        options.push_back(namedDecl->getName());
        if (auto type = namedDecl->getType()) {
            options.push_back(type->dump());
        }
    }
    dump(&dumpContext, "BindingDecl", options, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<DecompositionDecl>& decl, Invoke&& traverse)
{
    std::vector<std::string> options;
    dump(&dumpContext, "DecompositionDecl", options, std::move(traverse));
}
