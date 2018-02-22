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
    std::vector<std::shared_ptr<FunctionDecl>> functionDecls;

    std::string dump() const
    {
        ASTDumper dumper(true);
        std::string s;
        bool needToBreakLine = false;
        for (auto& funcDecl : functionDecls) {
            assert(funcDecl);
            if (needToBreakLine) {
                s += "\n";
                needToBreakLine = false;
            }
            s += funcDecl->dump(dumper);
            needToBreakLine = true;
        }
        return s;
    }
};
