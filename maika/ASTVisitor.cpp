#include "ASTVisitor.h"
#include "ASTContext.h"
#include "Decl.h"
#include "Expr.h"
#include "Stmt.h"
#include <cassert>
#include <utility>

void ASTTraverser::traverse(const ASTContext& context, ASTVisitor& visitor)
{
    context.translationUnit->traverse(visitor);
}
