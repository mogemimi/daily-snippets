#include "AST/ASTVisitor.h"
#include "AST/ASTContext.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Stmt.h"
#include <cassert>
#include <utility>

void ASTTraverser::traverse(const ASTContext& context, ASTVisitor& visitor)
{
    assert(context.translationUnit);
    context.translationUnit->traverse(visitor);
}
