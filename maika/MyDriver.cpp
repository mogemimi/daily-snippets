#include "MyDriver.h"
#include "Diagnostic.h"
#include "MyParser.h"

#define YY_NO_UNISTD_H 1
#include "MyLexer.h"

std::tuple<ASTContext, bool>
MyDriver::parseFile(const std::string& filename, const std::shared_ptr<DiagnosticHandler>& diagIn)
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
    yy::MyParser parser(*this);
    const auto resultCode = parser.parse();
    scanEnd();

    const auto ok = (resultCode == 0);
    return std::make_tuple(ast, ok);
}

std::tuple<ASTContext, bool>
MyDriver::parseString(const std::string& text, const std::shared_ptr<DiagnosticHandler>& diagIn)
{
    this->traceScanning = false;
    this->file.clear();
    this->sourceText = text;
    this->diag = diagIn;

    assert(diag);

    auto state = yy_scan_string(sourceText.c_str());
    this->defer = [state] { yy_delete_buffer(state); };

    scanBegin();
    yy::MyParser parser(*this);
    const auto resultCode = parser.parse();
    scanEnd();

    const auto ok = (resultCode == 0);
    return std::make_tuple(ast, ok);
}

void MyDriver::visitComment(const yy::location& l, CommentKind kind, const std::string& text)
{
    Comment comment;
    comment.location = l;
    comment.kind = kind;
    comment.text = text;
    comments.push_back(comment);
}

void MyDriver::error(const yy::location& l, const std::string& m)
{
    assert(diag);
    diag->error(l, m);
}

void MyDriver::error(const std::string& m)
{
    assert(diag);
    diag->error(m);
}
