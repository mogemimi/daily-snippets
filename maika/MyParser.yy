%skeleton "lalr1.cc"
%require "3.0.4"
%defines "MyParser.h"
%output "MyParser.cpp"
%define parser_class_name {MyParser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires
{
#include "ASTContext.h"
#include "Decl.h"
#include "Expr.h"
#include "Stmt.h"
#include <iostream>
#include <string>

class MyDriver;
}

%param { MyDriver& driver }

%locations
%initial-action
{
    // Initialize the initial location.
    @$.begin.filename = @$.end.filename = &driver.file;
};

%define parse.trace
%define parse.error verbose

%code
{
#include "MyDriver.h"

namespace {
template <class T>
std::vector<T> appendVector(T left, const std::vector<T>& right)
{
    std::vector<T> s;
    s.reserve(1 + right.size());
    s.push_back(left);
    s.insert(std::end(s), std::begin(right), std::end(right));
    return s;
}
} // end of anonymous namespace 
}

%define api.token.prefix {TOK_}

%token END 0                "end of file"
%token ASSIGN               "="
%token MINUS                "-"
%token PLUS                 "+"
%token STAR                 "*"
%token SLASH                "/"
%token LOGICAL_NOT          "!"
%token LOGICAL_AND          "&&"
%token LOGICAL_OR           "||"
%token EQUAL                "=="
%token NOT_EQUAL            "!="
%token LEFT_PARENTHESIS     "("
%token RIGHT_PARENTHESIS    ")"
%token LEFT_CURLY_BRACKET   "{"
%token RIGHT_CURLY_BRACKET  "}"
%token COLON                ":"
%token SEMICOLON            ";"
%token COMMA                ","
%token FUNCTION             "function"
%token RETURN               "return"
%token LET                  "let"

%token <std::shared_ptr<NamedDecl>>                 IDENTIFIER "identifier"
%token <std::shared_ptr<IntegerLiteral>>            INTEGER_LITERAL "integer_literal"
%token <std::shared_ptr<DoubleLiteral>>             DOUBLE_LITERAL "double_literal"
%token <std::shared_ptr<BoolLiteral>>               BOOL_LITERAL "bool_literal"
%token <std::shared_ptr<StringLiteral>>             STRING_LITERAL "string_literal"
%type  <std::shared_ptr<Expr>>                      literal
%type  <std::shared_ptr<Expr>>                      expression
%type  <std::vector<std::shared_ptr<Stmt>>>         statements
%type  <std::shared_ptr<Stmt>>                      statement
%type  <std::shared_ptr<CallExpr>>                  call_expression
%type  <std::vector<std::shared_ptr<Expr>>>         expressions
%type  <std::vector<std::shared_ptr<ParmVarDecl>>>  parameter_variables
%type  <std::shared_ptr<ParmVarDecl>>               parameter_variable
%type  <std::shared_ptr<CompoundStmt>>              compound_statement
%type  <std::shared_ptr<ReturnStmt>>                return_statement
%type  <std::vector<std::shared_ptr<FunctionDecl>>> function_definitions
%type  <std::shared_ptr<FunctionDecl>>              function_definition
%type  <std::shared_ptr<VariableDecl>>              variable_definition
%type  <std::shared_ptr<TranslationUnitDecl>>       translation_unit


%%
%start translation_unit;

translation_unit:
  function_definitions  { driver.ast.translationUnit = TranslationUnitDecl::make(@$, $1); }
;

function_definitions:
  function_definition                       { $$.push_back($1); }
| function_definition function_definitions  { $$ = appendVector($1, $2); }
;

function_definition:
  "function" "identifier" "(" parameter_variables ")" compound_statement { $$ = FunctionDecl::make(@$, $2, $4, $6); }
;

parameter_variables:
  %empty                                      { }
| parameter_variable                          { $$.push_back($1); }
| parameter_variable "," parameter_variables  { $$ = appendVector($1, $3); }
;

parameter_variable:
  "identifier"                  { $$ = ParmVarDecl::make(@$, $1); }
| "identifier" ":" "identifier" { $$ = ParmVarDecl::make(@$, $1, $3); }
;

compound_statement:
  "{" statements "}" { $$ = CompoundStmt::make($2); }
;

statements:
  %empty                { }
| statement statements  { $$ = appendVector($1, $2); }
;

statement:
  expression ";"            { $$ = $1; }
| return_statement          { $$ = $1; }
| variable_definition ";"   { $$ = DeclStmt::make($1); }
;

return_statement:
  "return" ";"            { $$ = ReturnStmt::make(); }
| "return" expression ";" { $$ = ReturnStmt::make($2); }
;

variable_definition:
  "let" "identifier"                { $$ = VariableDecl::make(@$, $2); }
| "let" "identifier" "=" expression { $$ = VariableDecl::make(@$, $2, $4); }
;

literal:
  "integer_literal" { $$ = $1; }
| "double_literal"  { $$ = $1; }
| "bool_literal"    { $$ = $1; }
| "string_literal"  { $$ = $1; }
;

call_expression:
  "identifier" "(" expressions ")"  { $$ = CallExpr::make(@$, DeclRefExpr::make(@1, $1), $3); }
;

expressions:
  %empty                     { }
| expression                 { $$.push_back($1); }
| expression "," expressions { $$ = appendVector($1, $3); }
;

%right "=";
%left "+" "-";
%left "*" "/";
%left "==" "!=";
%left "&&" "||";
expression:
  "identifier"                      { $$ = DeclRefExpr::make(@$, $1); };
| literal                           { $$ = $1; }
| "(" expression ")"                { std::swap($$, $2); }
| expression "+" expression         { $$ = BinaryOperator::make(@$, BinaryOperatorKind::Add, $1, $3); }
| expression "-" expression         { $$ = BinaryOperator::make(@$, BinaryOperatorKind::Subtract, $1, $3); }
| expression "*" expression         { $$ = BinaryOperator::make(@$, BinaryOperatorKind::Multiply, $1, $3); }
| expression "/" expression         { $$ = BinaryOperator::make(@$, BinaryOperatorKind::Divide, $1, $3); }
| expression "=" expression         { $$ = BinaryOperator::make(@$, BinaryOperatorKind::Assign, $1, $3); }
| expression "==" expression        { $$ = BinaryOperator::make(@$, BinaryOperatorKind::Equal, $1, $3); }
| expression "!=" expression        { $$ = BinaryOperator::make(@$, BinaryOperatorKind::NotEqual, $1, $3); }
| expression "&&" expression        { $$ = BinaryOperator::make(@$, BinaryOperatorKind::LogicalAnd, $1, $3); }
| expression "||" expression        { $$ = BinaryOperator::make(@$, BinaryOperatorKind::LogicalOr, $1, $3); }
| call_expression                   { $$ = $1; }
;

%%

void yy::MyParser::error(const location_type& l, const std::string& m)
{
    driver.error (l, m);
}
