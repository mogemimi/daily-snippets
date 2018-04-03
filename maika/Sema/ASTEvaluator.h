#pragma once

#include "AST/ASTVisitor.h"
#include "AST/Type.h"
#include "Basic/Forward.h"
#include <memory>
#include <tuple>

enum class ASTEvaluateResult {
    StaticEvaluation,
    RuntimeEvaluation,
    SemanticError,
};

class ASTEvaluator final {
public:
    static std::tuple<std::unique_ptr<Value>, ASTEvaluateResult>
    evaluate(const std::shared_ptr<Expr>& expr, const std::shared_ptr<DiagnosticHandler>& diag);
};
