#include "ASTDumper2.h"
#include "ASTContext.h"
#include "Decl.h"
#include "Entity.h"
#include "Expr.h"
#include "Stmt.h"
#include <cassert>
#include <sstream>
#include <utility>

namespace {

template <class Dumper, class Traverser>
void dump(Dumper* dumper, const std::string& name, bool breakLine, Traverser&& traverse)
{
    const auto currentIndent = dumper->GetIndent();
    dumper->result += currentIndent + "(" + name;
    if (breakLine) {
        dumper->result += "\n";
    }

    dumper->SetIndent(currentIndent + "  ");
    traverse();
    dumper->SetIndent(currentIndent);

    dumper->result += currentIndent + ")";
    if (breakLine) {
        dumper->result += "\n";
    }
}

template <class Dumper> void dump(Dumper* dumper, const std::string& name)
{
    const auto currentIndent = dumper->GetIndent();
    dumper->result += currentIndent + "(" + name + ")\n";
}

} // end of anonymous namespace

void ASTDumper2::visit(const std::shared_ptr<CompoundStmt>& stmt, Invoke&& traverse)
{
    dump(this, "CompoundStmt", true, std::move(traverse));
}

void ASTDumper2::visit(const std::shared_ptr<ReturnStmt>& decl, Invoke&& traverse)
{
    dump(this, "ReturnStmt", true, std::move(traverse));
}

void ASTDumper2::visit(const std::shared_ptr<DeclStmt>& decl, Invoke&& traverse)
{
    dump(this, "DeclStmt", true, std::move(traverse));
}

void ASTDumper2::visit(const std::shared_ptr<CallExpr>& decl, Invoke&& traverse)
{
    dump(this, "CallExpr", true, std::move(traverse));
}

void ASTDumper2::visit(const std::shared_ptr<IntegerLiteral>& decl)
{
    dump(this, "IntegerLiteral");
}

void ASTDumper2::visit(const std::shared_ptr<DoubleLiteral>& decl)
{
    dump(this, "DoubleLiteral");
}

void ASTDumper2::visit(const std::shared_ptr<BoolLiteral>& decl)
{
    dump(this, "BoolLiteral");
}

void ASTDumper2::visit(const std::shared_ptr<BinaryOperator>& decl, Invoke&& traverse)
{
    dump(this, "BinaryOperator", true, std::move(traverse));
}

void ASTDumper2::visit(const std::shared_ptr<DeclRefExpr>& decl, Invoke&& traverse)
{
    dump(this, "DeclRefExpr", true, std::move(traverse));
}

void ASTDumper2::visit(const std::shared_ptr<FunctionDecl>& decl, Invoke&& traverse)
{
    dump(this, "FunctionDecl", true, std::move(traverse));
}

void ASTDumper2::visit(const std::shared_ptr<ParmVarDecl>& decl, Invoke&& traverse)
{
    dump(this, "ParmVarDecl", true, std::move(traverse));
}

void ASTDumper2::visit(const std::shared_ptr<VariableDecl>& decl, Invoke&& traverse)
{
    dump(this, "VariableDecl", true, std::move(traverse));
}

void ASTDumper2::visit(const std::shared_ptr<NamedDecl>& decl)
{
    dump(this, "NamedDecl " + decl->getName());
}
