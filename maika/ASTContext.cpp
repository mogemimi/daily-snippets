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
    ASTDumper dumper(true);
    assert(translationUnit);
    return translationUnit->dump(dumper);
}
