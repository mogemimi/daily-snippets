#include "AST/ASTContext.h"
#include "AST/ASTDumper.h"
#include "AST/Comment.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Stmt.h"
#include "AST/Type.h"
#include <algorithm>
#include <cassert>
#include <utility>

std::shared_ptr<TranslationUnitDecl> ASTContext::getTranslationUnitDecl() const
{
    return translationUnit;
}

void ASTContext::buildComments()
{
    std::sort(std::begin(comments), std::end(comments), [](const auto& a, const auto& b) {
        return a->location.getBegin() < b->location.getBegin();
    });
}

std::string ASTContext::dump() const
{
    assert(translationUnit);
    ASTDumper dumper;
    ASTTraverser traverser;
    traverser.traverse(*this, dumper);
    return dumper.getResult();
}
