#include "ASTDumper.h"
#include "ASTContext.h"
#include "Decl.h"
#include "Entity.h"
#include "Expr.h"
#include "Stmt.h"
#include "Type.h"
#include <cassert>
#include <sstream>
#include <utility>

namespace {

template <class Dumper>
void dump(Dumper* dumper, const std::string& name, const std::vector<std::string>& options)
{
    const auto currentIndent = dumper->getIndent();
    dumper->result += currentIndent + name;
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

    const auto currentIndent = dumper->getIndent();
    dumper->setIndent(currentIndent + "  ");
    traverse();
    dumper->setIndent(currentIndent);
}

} // end of anonymous namespace

void ASTDumper::visit(const std::shared_ptr<CompoundStmt>& stmt, Invoke&& traverse)
{
    dump(this, "CompoundStmt", {}, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<ReturnStmt>& stmt, Invoke&& traverse)
{
    dump(this, "ReturnStmt", {}, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<DeclStmt>& stmt, Invoke&& traverse)
{
    dump(this, "DeclStmt", {}, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<CallExpr>& expr, Invoke&& traverse)
{
    std::vector<std::string> options;
    if (auto type = expr->getType()) {
        options.push_back(type->dump());
    }
    dump(this, "CallExpr", options, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<IntegerLiteral>& expr)
{
    std::vector<std::string> options;
    options.push_back(std::to_string(expr->getValue()));
    if (auto type = expr->getType()) {
        options.push_back(type->dump());
    }
    dump(this, "IntegerLiteral", options);
}

void ASTDumper::visit(const std::shared_ptr<DoubleLiteral>& expr)
{
    std::vector<std::string> options;
    options.push_back(std::to_string(expr->getValue()));
    if (auto type = expr->getType()) {
        options.push_back(type->dump());
    }
    dump(this, "DoubleLiteral", options);
}

void ASTDumper::visit(const std::shared_ptr<BoolLiteral>& expr)
{
    std::vector<std::string> options;
    options.push_back(expr->getValue() ? "true" : "false");
    if (auto type = expr->getType()) {
        options.push_back(type->dump());
    }
    dump(this, "BoolLiteral", options);
}

void ASTDumper::visit(const std::shared_ptr<BinaryOperator>& expr, Invoke&& traverse)
{
    std::vector<std::string> options;

    std::string op = [&]() -> std::string {
        switch (expr->getKind()) {
        case BinaryOperatorKind::Assign: return "=";
        case BinaryOperatorKind::Add: return "+";
        case BinaryOperatorKind::Subtract: return "-";
        case BinaryOperatorKind::Divide: return "/";
        case BinaryOperatorKind::Multiply: return "*";
        case BinaryOperatorKind::Equal: return "==";
        case BinaryOperatorKind::NotEqual: return "!=";
        case BinaryOperatorKind::LogicalAnd: return "&&";
        case BinaryOperatorKind::LogicalOr: return "||";
        }
        return "<unknown>";
    }();
    options.push_back(op);
    if (auto type = expr->getType()) {
        options.push_back(type->dump());
    }
    dump(this, "BinaryOperator", options, std::move(traverse));
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
    dump(this, "DeclRefExpr", options, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<TranslationUnitDecl>& decl, Invoke&& traverse)
{
    dump(this, "TranslationUnitDecl", {}, std::move(traverse));
}

void ASTDumper::visit(const std::shared_ptr<FunctionDecl>& decl, Invoke&& traverse)
{
    std::vector<std::string> options;
    if (decl->namedDecl) {
        options.push_back(decl->namedDecl->getName());
        if (auto type = decl->namedDecl->getType()) {
            options.push_back(type->dump());
        }
    }
    dump(this, "FunctionDecl", options, std::move(traverse));
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
    dump(this, "ParmVarDecl", options, std::move(traverse));
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
    dump(this, "VariableDecl", options, std::move(traverse));
}
