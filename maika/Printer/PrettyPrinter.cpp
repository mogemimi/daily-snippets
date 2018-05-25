#include "Printer/PrettyPrinter.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Stmt.h"
#include "AST/Type.h"
#include <cassert>
#include <sstream>
#include <utility>

namespace {

std::string makeIndent(int level)
{
    std::stringstream ss;
    for (int i = 0; i < level; i++) {
        ss << "    ";
    }
    return ss.str();
}

template <class Dumper>
void dump(Dumper* dumper, const std::string& name, const std::vector<std::string>& options)
{
    const auto indent = makeIndent(dumper->level);
    dumper->result += indent + name;
    for (const auto& opt : options) {
        dumper->result += " '";
        dumper->result += opt;
        dumper->result += "'";
    }
    dumper->result += "\n";
}

template <class Dumper, class Traverser>
void dump(
    Dumper* dumper,
    const std::string& name,
    const std::vector<std::string>& options,
    Traverser&& traverse)
{
    dump(dumper, name, options);

    dumper->level += 1;
    traverse();
    dumper->level -= 1;
    assert(dumper->level >= 0);
}

} // end of anonymous namespace

std::string PrettyPrinter::getResult() const
{
    return dumpContext.result;
}

void PrettyPrinter::visit(const std::shared_ptr<CompoundStmt>& stmt, Invoke&& traverse)
{
    for (auto& s : stmt->getStatements()) {
        dumpContext.result += makeIndent(dumpContext.level);
        s->traverse(*this);
        if (auto e = std::dynamic_pointer_cast<Expr>(s)) {
            dumpContext.result += ";";
            dumpContext.result += "\n";
        }
    }
}

void PrettyPrinter::visit(const std::shared_ptr<DeclStmt>& stmt, Invoke&& traverse)
{
    traverse();
}

void PrettyPrinter::visit(const std::shared_ptr<ReturnStmt>& stmt, Invoke&& traverse)
{
    dumpContext.result += "return";

    if (auto expr = stmt->getExpr()) {
        dumpContext.result += " ";
        ++dumpContext.level;
        expr->traverse(*this);
        --dumpContext.level;
        assert(dumpContext.level >= 0);
    }
    dumpContext.result += ";\n";
}

void PrettyPrinter::visit(const std::shared_ptr<IfStmt>& stmt, Invoke&& traverse)
{
    const auto indent = makeIndent(dumpContext.level);
    dumpContext.result += "if (";

    if (auto cond = stmt->getCond()) {
        cond->traverse(*this);
    }
    dumpContext.result += ")";
    dumpContext.result += " ";
    dumpContext.result += "{\n";

    if (auto then = stmt->getThen()) {
        ++dumpContext.level;
        then->traverse(*this);
        --dumpContext.level;
        assert(dumpContext.level >= 0);
    }

    if (auto elseStmt = stmt->getElse()) {
        ++dumpContext.level;
        elseStmt->traverse(*this);
        --dumpContext.level;
        assert(dumpContext.level >= 0);
    }

    dumpContext.result += indent + "}\n";
    assert(dumpContext.level >= 0);
}

void PrettyPrinter::visit(const std::shared_ptr<WhileStmt>& stmt, Invoke&& traverse)
{
    const auto indent = makeIndent(dumpContext.level);
    dumpContext.result += "while (";

    if (auto cond = stmt->getCond()) {
        cond->traverse(*this);
    }
    dumpContext.result += ")";
    dumpContext.result += " ";
    dumpContext.result += "{\n";

    if (auto body = stmt->getBody()) {
        ++dumpContext.level;
        body->traverse(*this);
        --dumpContext.level;
        assert(dumpContext.level >= 0);
    }

    dumpContext.result += indent + "}\n";
    assert(dumpContext.level >= 0);
}

void PrettyPrinter::visit(const std::shared_ptr<ForStmt>& stmt, Invoke&& traverse)
{
    const auto indent = makeIndent(dumpContext.level);
    dumpContext.result += "for (";

    if (auto init = stmt->getInit()) {
        init->traverse(*this);
    }
    dumpContext.result += ";";
    if (auto cond = stmt->getCond()) {
        dumpContext.result += " ";
        cond->traverse(*this);
    }
    dumpContext.result += ";";
    if (auto inc = stmt->getInc()) {
        dumpContext.result += " ";
        inc->traverse(*this);
    }
    dumpContext.result += ")";
    dumpContext.result += " ";
    dumpContext.result += "{\n";

    if (auto body = stmt->getBody()) {
        ++dumpContext.level;
        body->traverse(*this);
        --dumpContext.level;
        assert(dumpContext.level >= 0);
    }

    dumpContext.result += indent + "}\n";
    assert(dumpContext.level >= 0);
}

void PrettyPrinter::visit(const std::shared_ptr<CallExpr>& expr, Invoke&& traverse)
{
    if (auto callee = expr->getCallee()) {
        callee->traverse(*this);
    }
    bool needToInsertSpace = false;
    dumpContext.result += "(";
    for (auto& arg : expr->getArguments()) {
        if (needToInsertSpace) {
            dumpContext.result += ", ";
        }
        arg->traverse(*this);
        needToInsertSpace = true;
    }
    dumpContext.result += ")";
}

void PrettyPrinter::visit(const std::shared_ptr<FunctionExpr>& expr, Invoke&& traverse)
{
    std::vector<std::string> options;
    if (auto namedDecl = expr->getNamedDecl()) {
        options.push_back(namedDecl->getName());
    }
    if (auto type = expr->getType()) {
        options.push_back(type->dump());
    }
    dump(&dumpContext, "FunctionExpr", options, std::move(traverse));
}

void PrettyPrinter::visit(const std::shared_ptr<IntegerLiteral>& expr)
{
    dumpContext.result += std::to_string(expr->getValue());
}

void PrettyPrinter::visit(const std::shared_ptr<DoubleLiteral>& expr)
{
    dumpContext.result += std::to_string(expr->getValue());
}

void PrettyPrinter::visit(const std::shared_ptr<BoolLiteral>& expr)
{
    dumpContext.result += (expr->getValue() ? "true" : "false");
}

void PrettyPrinter::visit(const std::shared_ptr<StringLiteral>& expr)
{
    dumpContext.result += ('"' + expr->getValue() + '"');
}

void PrettyPrinter::visit(const std::shared_ptr<NullLiteral>& expr)
{
    dumpContext.result += "null";
}

void PrettyPrinter::visit(const std::shared_ptr<BinaryOperator>& expr, Invoke&& traverse)
{
    auto op = BinaryOperator::toString(expr->getKind());

    if (auto lhs = expr->getLHS()) {
        lhs->traverse(*this);
    }

    dumpContext.result += " ";
    dumpContext.result += op;
    dumpContext.result += " ";

    if (auto rhs = expr->getRHS()) {
        rhs->traverse(*this);
    }
}

void PrettyPrinter::visit(const std::shared_ptr<UnaryOperator>& expr, Invoke&& traverse)
{
    auto [op, isPre] = [&]() -> std::tuple<std::string, bool> {
        switch (expr->getKind()) {
        case UnaryOperatorKind::LogicalNot: return std::make_tuple("!", false);
        case UnaryOperatorKind::Plus: return std::make_tuple("+", false);
        case UnaryOperatorKind::Minus: return std::make_tuple("-", false);
        case UnaryOperatorKind::PreDec: return std::make_tuple("--", true);
        case UnaryOperatorKind::PreInc: return std::make_tuple("++", true);
        case UnaryOperatorKind::PostDec: return std::make_tuple("--", false);
        case UnaryOperatorKind::PostInc: return std::make_tuple("++", false);
        }
    }();

    if (isPre) {
        dumpContext.result += op;
        traverse();
    }
    else {
        traverse();
        dumpContext.result += op;
    }
}

void PrettyPrinter::visit(const std::shared_ptr<DeclRefExpr>& expr, Invoke&& traverse)
{
    if (auto namedDecl = expr->getNamedDecl()) {
        dumpContext.result += namedDecl->getName();
    }
    traverse();
}

void PrettyPrinter::visit(const std::shared_ptr<ParenExpr>& expr, Invoke&& traverse)
{
    if (auto subExpr = expr->getSubExpr()) {
        if (auto subParen = std::dynamic_pointer_cast<ParenExpr>(subExpr)) {
            subParen->traverse(*this);
            return;
        }
        if (auto declRef = std::dynamic_pointer_cast<DeclRefExpr>(subExpr)) {
            declRef->traverse(*this);
            return;
        }
    }

    dumpContext.result += "(";
    traverse();
    dumpContext.result += ")";
}

void PrettyPrinter::visit(const std::shared_ptr<MemberExpr>& expr, Invoke&& traverse)
{
    std::vector<std::string> options;
    if (auto namedDecl = expr->getMemberDecl()) {
        options.push_back(namedDecl->getName());
        if (auto type = namedDecl->getType()) {
            options.push_back(type->dump());
        }
    }
    dump(&dumpContext, "MemberExpr", options, std::move(traverse));
}

void PrettyPrinter::visit(const std::shared_ptr<TranslationUnitDecl>& decl, Invoke&& traverse)
{
    dumpContext.level = 0;
    traverse();
}

void PrettyPrinter::visit(const std::shared_ptr<FunctionDecl>& decl, Invoke&& traverse)
{
    const auto indent = makeIndent(dumpContext.level);
    dumpContext.result += indent + "func ";
    if (auto namedDecl = decl->getNamedDecl()) {
        dumpContext.result += namedDecl->getName();
    }
    dumpContext.result += "(";
    {
        ++dumpContext.level;
        bool needToInsertComma = false;
        for (const auto& param : decl->getParameters()) {
            if (needToInsertComma) {
                dumpContext.result += ", ";
            }
            auto namedDecl = param->getNamedDecl();
            assert(namedDecl);
            dumpContext.result += namedDecl->getName();
            if (auto typeAnnotation = param->getTypeAnnotation()) {
                assert(typeAnnotation);
                dumpContext.result += ": ";
                dumpContext.result += typeAnnotation->getName();
            }
            needToInsertComma = true;
        }
        --dumpContext.level;
    }
    dumpContext.result += ")";

    if (auto returnType = decl->getReturnType()) {
        dumpContext.result += "-> ";
        dumpContext.result += returnType->getName();
    }

    dumpContext.result += " " + indent;
    dumpContext.result += "{\n";

    {
        ++dumpContext.level;

        auto body = decl->getBody();
        assert(body);
        body->traverse(*this);

        --dumpContext.level;
        assert(dumpContext.level >= 0);
    }

    dumpContext.result += indent + "}\n";
}

void PrettyPrinter::visit(const std::shared_ptr<VariableDecl>& decl, Invoke&& traverse)
{
    dumpContext.result += "let ";
    if (auto namedDecl = decl->getNamedDecl()) {
        dumpContext.result += namedDecl->getName();
    }

    if (auto type = decl->getType()) {
        dumpContext.result += ": ";
        dumpContext.result += type->dump();
    }

    if (auto expr = decl->getExpr()) {
        dumpContext.result += " = ";
        expr->traverse(*this);
    }
}

void PrettyPrinter::visit(const std::shared_ptr<ConstDecl>& decl, Invoke&& traverse)
{
    dumpContext.result += "const ";
    if (auto namedDecl = decl->getNamedDecl()) {
        dumpContext.result += namedDecl->getName();
    }

    if (auto type = decl->getType()) {
        dumpContext.result += ": ";
        dumpContext.result += type->dump();
    }

    if (auto expr = decl->getExpr()) {
        dumpContext.result += " = ";
        expr->traverse(*this);
    }
}
