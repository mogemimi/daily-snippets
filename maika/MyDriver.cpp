#include "MyDriver.h"
#include "MyParser.h"

std::tuple<std::string, bool> MyDriver::parse(const std::string& filename)
{
    this->trace_scanning = false;
    this->file = filename;
    scanBegin();
    yy::MyParser parser(*this);
    const auto resultCode = parser.parse();
    scanEnd();

    if (resultCode != 0) {
        return std::make_tuple("", false);
    }
    return std::make_tuple(ast.dump(), true);
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
    std::cerr << l << ": " << m << std::endl;
}

void MyDriver::error(const std::string& m)
{
    std::cerr << m << std::endl;
}
