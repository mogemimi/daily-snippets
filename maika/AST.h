#pragma once

#include "ASTDumper.h"
#include "Decl.h"
#include "Expr.h"
#include "Stmt.h"
#include "Type.h"
#include <cassert>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class AST final {
public:
    std::shared_ptr<TranslationUnitDecl> translationUnit;

    std::string dump() const
    {
        ASTDumper dumper(true);
        assert(translationUnit);
        return translationUnit->dump(dumper);
    }
};
