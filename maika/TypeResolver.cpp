#include "TypeResolver.h"
#include "AST.h"
#include "Decl.h"
#include "Entity.h"
#include "Expr.h"
#include "IdentifierResolver.h"
#include "Stmt.h"
#include <cassert>
#include <sstream>
#include <utility>

// void TypeResolver::unifySymbols(const IdentifierContext& context)
//{
//    for (const auto& entity : context.entities) {
//        auto decl = entity->getDecl();
//        assert(decl);
//
//        if (decl->getType()) {
//            continue;
//        }
//
//
//    }
//}

void TypeResolver::visit(const std::shared_ptr<FunctionDecl>& decl) {}

void TypeResolver::visit(const std::shared_ptr<VariableDecl>& decl) {}

void TypeResolver::visit(const std::shared_ptr<NamedDecl>& decl) {}

void ASTDumper2::visit(const std::shared_ptr<DeclStmt>& decl) {}

void ASTDumper2::visit(const std::shared_ptr<CallExpr>& decl) {}

void ASTDumper2::visit(const std::shared_ptr<IntegerLiteral>& decl) {}

void ASTDumper2::visit(const std::shared_ptr<DoubleLiteral>& decl) {}
void ASTDumper2::visit(const std::shared_ptr<BoolLiteral>& decl) {}
void ASTDumper2::visit(const std::shared_ptr<BinaryOperator>& decl) {}
void ASTDumper2::visit(const std::shared_ptr<DeclRefExpr>& decl) {}

void ASTDumper2::visit(const std::shared_ptr<FunctionDecl>& decl) {}
void ASTDumper2::visit(const std::shared_ptr<ParmVarDecl>& decl) {}
void ASTDumper2::visit(const std::shared_ptr<VariableDecl>& decl) {}
