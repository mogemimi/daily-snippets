%{
#include "AST/ASTContext.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Stmt.h"
#include "AST/Type.h"
#include "Basic/Location.h"
#include "Driver/Driver.h"
#include "Parser/Parser.h"
#include "Parser/location.hh"

#include <cerrno>
#include <climits>
#include <cstdlib>
#include <string>
#include <memory>

// Work around an incompatibility in flex (at least versions
// 2.5.31 through 2.5.33): it generates code that does
// not conform to C89.  See Debian bug 333231
// <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.
#undef yywrap
#define yywrap() 1

namespace {
// The location of the current token.
yy::location loc;
std::string comment;
} // end of anonymous namespace
%}

%option header-file="Parser/Lexer.h"
%option outfile="Parser/Lexer.cpp"
%option noyywrap nounput batch debug noinput
%option nounistd never-interactive

decimal     [1-9]?[0-9]+
integer     -?{decimal}
double      -?({decimal}\.[0-9]*|\.[0-9]+)([eE][-+]?[0-9]+)?
identifier  [a-zA-Z][a-zA-Z_0-9]*
blank       [ \t]
utf8_bom    \xEF\xBB\xBF
crlf        (\r\n|\n)

%{
    // Code run each time a pattern is matched.
    #define YY_USER_ACTION  loc.columns(yyleng);
%}

%x CSTYLE_COMMENT
%%
%{
    // Code run each time yylex is called.
    loc.step();
%}

"/*"                    BEGIN(CSTYLE_COMMENT); comment = yytext;
<CSTYLE_COMMENT>"*/"    {
    BEGIN(INITIAL);
    driver.visitComment(toLoc(loc), CommentKind::Block, comment + yytext);
    comment.clear();
}
<CSTYLE_COMMENT>\n      loc.lines(yyleng); comment += yytext;
<CSTYLE_COMMENT>.       comment += yytext;

"//".*      driver.visitComment(toLoc(loc), CommentKind::Line, yytext);
{blank}+    loc.step();
{crlf}+     loc.lines(yyleng); loc.step();
^{utf8_bom} loc.step();

"-"         return yy::Parser::make_MINUS(loc);
"+"         return yy::Parser::make_PLUS(loc);
"*"         return yy::Parser::make_STAR(loc);
"/"         return yy::Parser::make_SLASH(loc);
"%"         return yy::Parser::make_MOD(loc);
"="         return yy::Parser::make_ASSIGN(loc);
"-="        return yy::Parser::make_SUB_ASSIGN(loc);
"+="        return yy::Parser::make_ADD_ASSIGN(loc);
"*="        return yy::Parser::make_MUL_ASSIGN(loc);
"/="        return yy::Parser::make_DIV_ASSIGN(loc);
"%="        return yy::Parser::make_MOD_ASSIGN(loc);
"++"        return yy::Parser::make_PLUS_PLUS(loc);
"--"        return yy::Parser::make_MINUS_MINUS(loc);
"!"         return yy::Parser::make_LOGICAL_NOT(loc);
"&&"        return yy::Parser::make_LOGICAL_AND(loc);
"||"        return yy::Parser::make_LOGICAL_OR(loc);
"=="        return yy::Parser::make_EQUAL(loc);
"!="        return yy::Parser::make_NOT_EQUAL(loc);
"<="        return yy::Parser::make_LESS_THAN_EQUAL(loc);
">="        return yy::Parser::make_GREATER_THAN_EQUAL(loc);
"<"         return yy::Parser::make_LESS_THAN(loc);
">"         return yy::Parser::make_GREATER_THAN(loc);
"("         return yy::Parser::make_LEFT_PARENTHESIS(loc);
")"         return yy::Parser::make_RIGHT_PARENTHESIS(loc);
"{"         return yy::Parser::make_LEFT_CURLY_BRACKET(loc);
"}"         return yy::Parser::make_RIGHT_CURLY_BRACKET(loc);
"["         return yy::Parser::make_LEFT_SQUARE_BRACKET(loc);
"]"         return yy::Parser::make_RIGHT_SQUARE_BRACKET(loc);
":"         return yy::Parser::make_COLON(loc);
";"         return yy::Parser::make_SEMICOLON(loc);
","         return yy::Parser::make_COMMA(loc);
"."         return yy::Parser::make_DOT(loc);
"?"         return yy::Parser::make_QUESTION(loc);
"??"        return yy::Parser::make_NULL_COALESCING(loc);
"->"        return yy::Parser::make_ARROW(loc);

"func"      return yy::Parser::make_FUNCTION(loc);
"return"    return yy::Parser::make_RETURN(loc);
"let"       return yy::Parser::make_LET(loc);
"var"       return yy::Parser::make_VAR(loc);
"const"     return yy::Parser::make_CONST(loc);
"if"        return yy::Parser::make_IF(loc);
"else"      return yy::Parser::make_ELSE(loc);
"while"     return yy::Parser::make_WHILE(loc);
"for"       return yy::Parser::make_FOR(loc);
"in"        return yy::Parser::make_IN(loc);
"defer"     return yy::Parser::make_DEFER(loc);
"class"     return yy::Parser::make_CLASS(loc);
"true"      return yy::Parser::make_BOOL_LITERAL(BoolLiteral::make(toLoc(loc), true), loc);
"false"     return yy::Parser::make_BOOL_LITERAL(BoolLiteral::make(toLoc(loc), false), loc);
"null"      return yy::Parser::make_NULL(loc);

\"(\\.|[^\\"])*\" {
    std::string s = yytext;

    // NOTE: Removing double quotes from string.
    assert(s.size() >= 2);
    s = s.substr(1, s.size() - 2);

    return yy::Parser::make_STRING_LITERAL(StringLiteral::make(toLoc(loc), s), loc);
}

{integer} {
    errno = 0;
    const auto n = strtol(yytext, nullptr, 10);
    if (!(INT_MIN <= n && n <= INT_MAX && errno != ERANGE)) {
        driver.error(toLoc(loc), "integer is out of range");
    }
    return yy::Parser::make_INTEGER_LITERAL(IntegerLiteral::make(toLoc(loc), n), loc);
}

{double} {
    errno = 0;
    const auto d = strtod(yytext, nullptr);
    if (errno == ERANGE) {
        driver.error(toLoc(loc), "double is out of range");
    }
    return yy::Parser::make_DOUBLE_LITERAL(DoubleLiteral::make(toLoc(loc), d), loc);
}

{identifier}    return yy::Parser::make_IDENTIFIER(NamedDecl::make(toLoc(loc), yytext), loc);
.               driver.error(toLoc(loc), "invalid character");
<<EOF>>         return yy::Parser::make_END(loc);

%%

void Driver::scanBegin()
{
    yy_flex_debug = this->traceScanning;
    loc.initialize();
}

void Driver::scanEnd()
{
    if (this->defer) {
        this->defer();
        this->defer = nullptr;
    }
}
