#pragma once

#include "MyParser.h"
#include <functional>
#include <map>
#include <sstream>
#include <string>
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
private:
    std::function<void()> defer;
    bool traceScanning;

public:
    std::string file;
    std::string sourceText;
    AST ast;
    std::vector<Comment> comments;

    std::tuple<std::string, bool> parseFile(const std::string& filename);
    std::tuple<std::string, bool> parseString(const std::string& text);

    void scanBegin();
    void scanEnd();

    void visitComment(const yy::location& l, CommentKind kind, const std::string& comment);
    void error(const yy::location& l, const std::string& m);
    void error(const std::string& m);
};

// Tell Flex the lexer's prototype ...
#define YY_DECL yy::MyParser::symbol_type yylex(MyDriver& driver)
// ... and declare it for the parser's sake.
YY_DECL;
