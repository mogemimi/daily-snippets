#include "AST/ASTContext.h"
#include "AST/ASTDumper.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Stmt.h"
#include "AST/Type.h"
#include <cassert>
#include <utility>

std::string ASTContext::dump() const
{
    assert(translationUnit);
    ASTDumper dumper;
    ASTTraverser traverser;
    traverser.traverse(*this, dumper);
    return dumper.getResult();
}
