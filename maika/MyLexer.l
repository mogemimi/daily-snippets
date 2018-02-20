%{
#include "AST.h"
#include "MyLexer.h"
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

%option noyywrap nounput batch debug noinput

%{
// %option c++
// %option nounistd
// %option yyclass="MyLexer"
%}

double      [0-9]+\.[0-9]*
integer     [0-9]+
identifier  [a-zA-Z][a-zA-Z_0-9]*
blank       [ \t]

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
[\n]+       loc.lines(yyleng); loc.step();

"-"     return yy::MyParser::make_MINUS(loc);
"+"     return yy::MyParser::make_PLUS(loc);
"*"     return yy::MyParser::make_STAR(loc);
"/"     return yy::MyParser::make_SLASH(loc);
"="     return yy::MyParser::make_ASSIGN(loc);
"("     return yy::MyParser::make_LEFT_PARENTHESIS(loc);
")"     return yy::MyParser::make_RIGHT_PARENTHESIS(loc);
"{"     return yy::MyParser::make_LEFT_CURLY_BRACKET(loc);
"}"     return yy::MyParser::make_RIGHT_CURLY_BRACKET(loc);
":"     return yy::MyParser::make_COLON(loc);
";"     return yy::MyParser::make_SEMICOLON(loc);
","     return yy::MyParser::make_COMMA(loc);

"function" return yy::MyParser::make_FUNCTION(loc);
"return"   return yy::MyParser::make_RETURN(loc);
"let"      return yy::MyParser::make_LET(loc);
"true"     return yy::MyParser::make_BOOL(BoolLiteral::make(true), loc);
"false"    return yy::MyParser::make_BOOL(BoolLiteral::make(false), loc);

{integer} {
    errno = 0;
    const auto n = strtol(yytext, nullptr, 10);
    if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE)) {
        driver.error(loc, "integer is out of range");
    }
    return yy::MyParser::make_INTEGER(IntegerLiteral::make(n), loc);
}

{double} {
    errno = 0;
    const auto d = strtod(yytext, nullptr);
    if (errno == ERANGE) {
        driver.error(loc, "double is out of range");
    }
    return yy::MyParser::make_DOUBLE(DoubleLiteral::make(d), loc);
}

{identifier}    return yy::MyParser::make_IDENTIFIER(NamedDecl::make(loc, yytext), loc);
.               driver.error(loc, "invalid character");
<<EOF>>         return yy::MyParser::make_END(loc);

%%

void MyDriver::scanBegin()
{
    yy_flex_debug = trace_scanning;
    if (file.empty () || file == "-") {
        yyin = stdin;
    }
    else if (!(yyin = fopen (file.c_str (), "r")))
    {
        error ("cannot open " + file + ": " + strerror(errno));
        exit (EXIT_FAILURE);
    }
}

void MyDriver::scanEnd()
{
    fclose(yyin);
}
