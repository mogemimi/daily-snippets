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
        return a->getLocation().getBegin() < b->getLocation().getBegin();
    });
}

std::vector<std::shared_ptr<Comment>>
ASTContext::findComments(const Position& begin, const Position& end)
{
    std::vector<std::shared_ptr<Comment>> result;

    assert(begin < end);
    if ((begin.line == end.line) && ((end.column - begin.column) <= 1)) {
        return result;
    }

    for (auto& comment : comments) {
        auto loc = comment->getLocation();
        if (end < loc.getEnd()) {
            break;
        }
        if ((begin < loc.getBegin()) && (loc.getEnd() < end)) {
            result.push_back(comment);
        }
    }
    return result;
}

std::string ASTContext::dump() const
{
    assert(translationUnit);
    ASTDumper dumper;
    ASTTraverser traverser;
    traverser.traverse(*this, dumper);
    return dumper.getResult();
}
