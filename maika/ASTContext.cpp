#include "ASTContext.h"
#include "ASTDumper.h"
#include "Decl.h"
#include "Expr.h"
#include "Stmt.h"
#include "Type.h"
#include <cassert>
#include <utility>

std::string ASTContext::dump() const
{
    assert(translationUnit);
    ASTDumper dumper;
    ASTTraverser traverser;
    traverser.traverse(*this, dumper);
    return dumper.result;
}
