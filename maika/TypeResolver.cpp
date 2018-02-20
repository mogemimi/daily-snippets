#include "TypeResolver.h"
#include "IdentifierResolver.h"
#include "AST.h"
#include "Decl.h"
#include "Entity.h"
#include "Expr.h"
#include "Stmt.h"
#include <cassert>
#include <sstream>
#include <utility>

//void TypeResolver::unifySymbols(const IdentifierContext& context)
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

void TypeResolver::visit(const std::shared_ptr<FunctionDecl>& decl)
{
}

void TypeResolver::visit(const std::shared_ptr<VariableDecl>& decl)
{
}

void TypeResolver::visit(const std::shared_ptr<NamedDecl>& decl)
{
}
