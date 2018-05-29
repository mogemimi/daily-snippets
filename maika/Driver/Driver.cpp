#include "Driver/Driver.h"
#include "Basic/Diagnostic.h"
#include "Parser/Parser.h"

#define YY_NO_UNISTD_H 1
#include "Parser/Lexer.h"

std::tuple<ASTContext, bool>
Driver::parseFile(const std::string& filename, const std::shared_ptr<DiagnosticHandler>& diagIn)
{
    this->traceScanning = false;
    this->file = filename;
    this->sourceText.clear();
    this->diag = diagIn;

    assert(diag);
    diag->setProgramName(file);

    if (file.empty()) {
        yyin = stdin;
    }
    else if (!(yyin = fopen(file.c_str(), "r"))) {
        error("cannot open " + file + ": " + strerror(errno));
        return std::make_tuple(ast, false);
    }
    this->defer = [] { fclose(yyin); };

    scanBegin();
    yy::Parser parser(*this);
    const auto resultCode = parser.parse();
    scanEnd();

    const auto ok = (resultCode == 0);
    return std::make_tuple(ast, ok);
}

std::tuple<ASTContext, bool>
Driver::parseString(const std::string& text, const std::shared_ptr<DiagnosticHandler>& diagIn)
{
    this->traceScanning = false;
    this->file.clear();
    this->sourceText = text;
    this->diag = diagIn;

    assert(diag);

    auto state = yy_scan_bytes(sourceText.c_str(), static_cast<int>(sourceText.size()));
    this->defer = [state] { yy_delete_buffer(state); };

    scanBegin();
    yy::Parser parser(*this);
    const auto resultCode = parser.parse();
    scanEnd();

    const auto ok = (resultCode == 0);
    return std::make_tuple(ast, ok);
}

void Driver::visitComment(const Location& loc, CommentKind kind, const std::string& text)
{
    auto comment = Comment::make(loc, kind, text);
    ast.comments.push_back(std::move(comment));
}

void Driver::error(const Location& l, const std::string& m)
{
    assert(diag);
    diag->error(l, m);
}

void Driver::error(const std::string& m)
{
    assert(diag);
    diag->error(m);
}
