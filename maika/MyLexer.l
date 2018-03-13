%{
#include "AST/ASTContext.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Stmt.h"
#include "AST/Type.h"
#include "MyDriver.h"
#include "MyParser.h"

#include <cerrno>
#include <climits>
#include <cstdlib>
#include <string>

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

%option header-file="MyLexer.h"
%option outfile="MyLexer.cpp"
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
    driver.visitComment(loc, CommentKind::C, comment + yytext);
    comment.clear();
}
<CSTYLE_COMMENT>\n      loc.lines(yyleng); comment += yytext;
<CSTYLE_COMMENT>.       comment += yytext;

"//".*      driver.visitComment(loc, CommentKind::BCPL, yytext);
{blank}+    loc.step();
{crlf}+     loc.lines(yyleng); loc.step();
^{utf8_bom} loc.step();

"-"         return yy::MyParser::make_MINUS(loc);
"+"         return yy::MyParser::make_PLUS(loc);
"*"         return yy::MyParser::make_STAR(loc);
"/"         return yy::MyParser::make_SLASH(loc);
"%"         return yy::MyParser::make_MOD(loc);
"="         return yy::MyParser::make_ASSIGN(loc);
"-="        return yy::MyParser::make_SUB_ASSIGN(loc);
"+="        return yy::MyParser::make_ADD_ASSIGN(loc);
"*="        return yy::MyParser::make_MUL_ASSIGN(loc);
"/="        return yy::MyParser::make_DIV_ASSIGN(loc);
"%="        return yy::MyParser::make_MOD_ASSIGN(loc);
"++"        return yy::MyParser::make_PLUS_PLUS(loc);
"--"        return yy::MyParser::make_MINUS_MINUS(loc);
"!"         return yy::MyParser::make_LOGICAL_NOT(loc);
"&&"        return yy::MyParser::make_LOGICAL_AND(loc);
"||"        return yy::MyParser::make_LOGICAL_OR(loc);
"=="        return yy::MyParser::make_EQUAL(loc);
"!="        return yy::MyParser::make_NOT_EQUAL(loc);
"<="        return yy::MyParser::make_LESS_THAN_EQUAL(loc);
">="        return yy::MyParser::make_GREATER_THAN_EQUAL(loc);
"<"         return yy::MyParser::make_LESS_THAN(loc);
">"         return yy::MyParser::make_GREATER_THAN(loc);
"("         return yy::MyParser::make_LEFT_PARENTHESIS(loc);
")"         return yy::MyParser::make_RIGHT_PARENTHESIS(loc);
"{"         return yy::MyParser::make_LEFT_CURLY_BRACKET(loc);
"}"         return yy::MyParser::make_RIGHT_CURLY_BRACKET(loc);
"["         return yy::MyParser::make_LEFT_SQUARE_BRACKET(loc);
"]"         return yy::MyParser::make_RIGHT_SQUARE_BRACKET(loc);
":"         return yy::MyParser::make_COLON(loc);
";"         return yy::MyParser::make_SEMICOLON(loc);
","         return yy::MyParser::make_COMMA(loc);
"."         return yy::MyParser::make_DOT(loc);
"?"         return yy::MyParser::make_QUESTION(loc);

"function"  return yy::MyParser::make_FUNCTION(loc);
"return"    return yy::MyParser::make_RETURN(loc);
"let"       return yy::MyParser::make_LET(loc);
"const"     return yy::MyParser::make_CONST(loc);
"if"        return yy::MyParser::make_IF(loc);
"else"      return yy::MyParser::make_ELSE(loc);
"while"     return yy::MyParser::make_WHILE(loc);
"for"       return yy::MyParser::make_FOR(loc);
"true"      return yy::MyParser::make_BOOL_LITERAL(BoolLiteral::make(loc, true), loc);
"false"     return yy::MyParser::make_BOOL_LITERAL(BoolLiteral::make(loc, false), loc);

\"(\\.|[^\\"])*\" return yy::MyParser::make_STRING_LITERAL(StringLiteral::make(loc, yytext), loc);

{integer} {
    errno = 0;
    const auto n = strtol(yytext, nullptr, 10);
    if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE)) {
        driver.error(loc, "integer is out of range");
    }
    return yy::MyParser::make_INTEGER_LITERAL(IntegerLiteral::make(loc, n), loc);
}

{double} {
    errno = 0;
    const auto d = strtod(yytext, nullptr);
    if (errno == ERANGE) {
        driver.error(loc, "double is out of range");
    }
    return yy::MyParser::make_DOUBLE_LITERAL(DoubleLiteral::make(loc, d), loc);
}

{identifier}    return yy::MyParser::make_IDENTIFIER(NamedDecl::make(loc, yytext), loc);
.               driver.error(loc, "invalid character");
<<EOF>>         return yy::MyParser::make_END(loc);

%%

void MyDriver::scanBegin()
{
    yy_flex_debug = this->traceScanning;
    loc.initialize();
}

void MyDriver::scanEnd()
{
    if (this->defer) {
        this->defer();
        this->defer = nullptr;
    }
}
