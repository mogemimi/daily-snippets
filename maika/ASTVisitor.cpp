#include "ASTVisitor.h"
#include "AST.h"
#include "Decl.h"
#include "Expr.h"
#include "Stmt.h"
#include <cassert>
#include <utility>

void ASTTraverser::traverse(const AST& ast, ASTVisitor& visitor)
{
    ast.translationUnit->traverse(visitor);
}
