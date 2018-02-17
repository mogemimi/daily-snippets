#pragma once

#include "MyParser.h"
#include <string>
#include <sstream>
#include <map>
#include <tuple>

enum class CommentKind {
    C,    // /* comment */
    BCPL, // // comment
};

struct Comment {
    yy::location location;
    CommentKind kind;
    std::string text;

    std::string dump()
    {
        auto style = [&]() -> std::string {
        switch (kind) {
            case CommentKind::BCPL: return "BCPL";
            case CommentKind::C: return "C";
            }
        }();
        std::stringstream ss;
        ss << location << ": Comment Style = " << style << "\n" << text;
        return ss.str();
    }
};

class MyDriver final {
public:
    AST ast;
    std::string file;
    bool trace_scanning;
    std::vector<Comment> comments;

    void scanBegin();
    void scanEnd();

    std::tuple<std::string, bool> parse(const std::string& filename);

    void visitComment(const yy::location& l, CommentKind kind, const std::string& comment);
    void error(const yy::location& l, const std::string& m);
    void error(const std::string& m);
};

// Tell Flex the lexer's prototype ...
#define YY_DECL yy::MyParser::symbol_type yylex(MyDriver& driver)
// ... and declare it for the parser's sake.
YY_DECL;
