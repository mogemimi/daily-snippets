%skeleton "lalr1.cc"
%require "3.0.4"
%defines "Parser/MyParser.h"
%output "Parser/MyParser.cpp"
%define parser_class_name {MyParser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires
{
#include "Basic/Forward.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Stmt.h"
#include <memory>
#include <tuple>
#include <vector>

class MyDriver;

namespace yy {
class position;
class location;
} // namespace yy

using CallSignature = std::tuple<
  std::vector<std::shared_ptr<ParmVarDecl>>,
  std::shared_ptr<NamedDecl>>;

// TODO: Maybe we should use a user-defined location type instead of toLoc() function.
// https://www.gnu.org/software/bison/manual/html_node/User-Defined-Location-Type.html#User-Defined-Location-Type
Location toLoc(const yy::location& y);
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
#include "AST/ASTContext.h"
#include "Basic/Location.h"
#include "Driver/Driver.h"
#include <string>

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

Position toPosition(const yy::position& y)
{
    Position pos;
    if (y.filename) {
        pos.filename = *y.filename;
    }
    pos.line = static_cast<int>(y.line);
    pos.column = static_cast<int>(y.column);
    return pos;
}
} // end of anonymous namespace

Location toLoc(const yy::location& y)
{
    Location loc(toPosition(y.begin), toPosition(y.end));
    return loc;
}
}

%define api.token.prefix {TOK_}

%token END 0                "end of file"
%token ASSIGN               "="
%token MINUS                "-"
%token PLUS                 "+"
%token STAR                 "*"
%token SLASH                "/"
%token MOD                  "%"
%token SUB_ASSIGN           "-="
%token ADD_ASSIGN           "+="
%token MUL_ASSIGN           "*="
%token DIV_ASSIGN           "/="
%token MOD_ASSIGN           "%="
%token PLUS_PLUS            "++"
%token MINUS_MINUS          "--"
%token LOGICAL_NOT          "!"
%token LOGICAL_AND          "&&"
%token LOGICAL_OR           "||"
%token EQUAL                "=="
%token NOT_EQUAL            "!="
%token LESS_THAN_EQUAL      "<="
%token GREATER_THAN_EQUAL   ">="
%token LESS_THAN            "<"
%token GREATER_THAN         ">"
%token LEFT_PARENTHESIS     "("
%token RIGHT_PARENTHESIS    ")"
%token LEFT_CURLY_BRACKET   "{"
%token RIGHT_CURLY_BRACKET  "}"
%token LEFT_SQUARE_BRACKET  "["
%token RIGHT_SQUARE_BRACKET "]"
%token COLON                ":"
%token SEMICOLON            ";"
%token COMMA                ","
%token DOT                  "."
%token QUESTION             "?"
%token FUNCTION             "function"
%token RETURN               "return"
%token LET                  "let"
%token CONST                "const"
%token IF                   "if"
%token ELSE                 "else"
%token WHILE                "while"
%token FOR                  "for"

%token <std::shared_ptr<NamedDecl>>                 IDENTIFIER "identifier"
%token <std::shared_ptr<IntegerLiteral>>            INTEGER_LITERAL "integer_literal"
%token <std::shared_ptr<DoubleLiteral>>             DOUBLE_LITERAL "double_literal"
%token <std::shared_ptr<BoolLiteral>>               BOOL_LITERAL "bool_literal"
%token <std::shared_ptr<StringLiteral>>             STRING_LITERAL "string_literal"
%type  <std::shared_ptr<Expr>>                      literal
%type  <std::shared_ptr<Expr>>                      primary_expression
%type  <std::shared_ptr<Expr>>                      expression
%type  <std::vector<std::shared_ptr<Expr>>>         expression_list
%type  <std::shared_ptr<UnaryOperator>>             unary_expression
%type  <std::shared_ptr<Stmt>>                      statement
%type  <std::vector<std::shared_ptr<Stmt>>>         statement_list
%type  <std::shared_ptr<NamedDecl>>                 binding_identifier
%type  <std::shared_ptr<MemberExpr>>                member_expression
%type  <std::shared_ptr<CallExpr>>                  call_expression
%type  <std::vector<std::shared_ptr<ParmVarDecl>>>  parameter_variables
%type  <std::shared_ptr<ParmVarDecl>>               parameter_variable
%type  <std::shared_ptr<CompoundStmt>>              compound_statement
%type  <std::shared_ptr<ReturnStmt>>                return_statement
%type  <std::shared_ptr<IfStmt>>                    if_statement
%type  <std::shared_ptr<WhileStmt>>                 while_statement
%type  <std::shared_ptr<ForStmt>>                   for_statement
%type  <std::shared_ptr<Stmt>>                      for_init_statement
%type  <std::vector<std::shared_ptr<FunctionDecl>>> function_definitions
%type  <std::shared_ptr<FunctionDecl>>              function_definition
%type  <std::shared_ptr<FunctionExpr>>              function_expression
%type  <CallSignature>                              call_signature
%type  <std::shared_ptr<VariableDecl>>              variable_definition
%type  <std::shared_ptr<ConstDecl>>                 const_definition
%type  <std::shared_ptr<NamedDecl>>                 type_specifier
%type  <std::shared_ptr<TranslationUnitDecl>>       translation_unit


%%
%start translation_unit;

translation_unit:
  function_definitions  { driver.ast.translationUnit = TranslationUnitDecl::make(toLoc(@$), $1); }
;

function_definitions:
  %empty                                    { }
| function_definition function_definitions  { $$ = appendVector($1, $2); }
;

function_definition:
  "function" "identifier" call_signature compound_statement { $$ = FunctionDecl::make(toLoc(@$), $2, std::get<0>($3), std::get<1>($3), $4); }
;

function_expression:
  "function" binding_identifier call_signature compound_statement { $$ = FunctionExpr::make(toLoc(@$), $2, std::get<0>($3), std::get<1>($3), $4); }
;

call_signature:
  "(" parameter_variables ")"                     { std::get<0>($$) = $2; std::get<1>($$) = nullptr; }
| "(" parameter_variables ")" ":" type_specifier  { std::get<0>($$) = $2; std::get<1>($$) = $5; }
;

binding_identifier:
  %empty        { }
| "identifier"  { $$ = $1; }
;

parameter_variables:
  %empty                                      { }
| parameter_variable                          { $$.push_back($1); }
| parameter_variable "," parameter_variables  { $$ = appendVector($1, $3); }
;

parameter_variable:
  "identifier"                    { $$ = ParmVarDecl::make(toLoc(@$), $1); }
| "identifier" ":" type_specifier { $$ = ParmVarDecl::make(toLoc(@$), $1, $3); }
;

type_specifier:
  "identifier"  { $$ = $1; }
;

statement:
  expression ";"            { $$ = $1; }
| return_statement          { $$ = $1; }
| variable_definition ";"   { $$ = DeclStmt::make(toLoc(@$), $1); }
| const_definition ";"      { $$ = DeclStmt::make(toLoc(@$), $1); }
| if_statement              { $$ = $1; }
| while_statement           { $$ = $1; }
| for_statement             { $$ = $1; }
| compound_statement        { $$ = $1; }
;

compound_statement:
  "{" "}"                 { $$ = CompoundStmt::make(toLoc(@$), std::vector<std::shared_ptr<Stmt>>{}); }
| "{" statement_list "}"  { $$ = CompoundStmt::make(toLoc(@$), $2); }
;

statement_list:
  statement                 { $$.push_back($1); }
| statement statement_list  { $$ = appendVector($1, $2); }
;

return_statement:
  "return" ";"            { $$ = ReturnStmt::make(toLoc(@$)); }
| "return" expression ";" { $$ = ReturnStmt::make(toLoc(@$), $2); }
;

%nonassoc "then";
%nonassoc "else";
if_statement:
  "if" "(" expression ")" statement %prec "then"      { $$ = IfStmt::make(toLoc(@$), $3, $5); }
| "if" "(" expression ")" statement "else" statement  { $$ = IfStmt::make(toLoc(@$), $3, $5, $7); }
;

while_statement:
  "while" "(" expression ")" statement { $$ = WhileStmt::make(toLoc(@$), $3, $5); }
;

for_statement:
  "for" "(" for_init_statement expression ";" expression ")" statement  { $$ = ForStmt::make(toLoc(@$), $3, $4, $6, $8); }
;

for_init_statement:
  ";"                     { }
| expression ";"          { $$ = $1; }
| variable_definition ";" { $$ = DeclStmt::make(toLoc(@$), $1); }
;

variable_definition:
  "let" "identifier"                { $$ = VariableDecl::make(toLoc(@$), $2); }
| "let" "identifier" "=" expression { $$ = VariableDecl::make(toLoc(@$), $2, $4); }
;

const_definition:
  "const" "identifier"                { $$ = ConstDecl::make(toLoc(@$), $2); }
| "const" "identifier" "=" expression { $$ = ConstDecl::make(toLoc(@$), $2, $4); }
;

literal:
  "integer_literal" { $$ = $1; }
| "double_literal"  { $$ = $1; }
| "bool_literal"    { $$ = $1; }
| "string_literal"  { $$ = $1; }
;

%right "=";
%left "||";
%left "&&";
%left "==" "!=";
%left "<=" ">=" "<" ">";
%left "+" "-";
%left "*" "/" "%";
%right "++" "--" "!";
%left ".";
%nonassoc "(" ")";
     
primary_expression:
  literal                 { $$ = $1; }
| "identifier"            { $$ = DeclRefExpr::make(toLoc(@$), $1); }
| "(" expression ")"      { std::swap($$, $2); }
;

unary_expression:
  "++" primary_expression { $$ = UnaryOperator::make(toLoc(@$), UnaryOperatorKind::PreInc, $2); }
| "--" primary_expression { $$ = UnaryOperator::make(toLoc(@$), UnaryOperatorKind::PreDec, $2); }
| primary_expression "++" { $$ = UnaryOperator::make(toLoc(@$), UnaryOperatorKind::PostInc, $1); }
| primary_expression "--" { $$ = UnaryOperator::make(toLoc(@$), UnaryOperatorKind::PostDec, $1); }
| "+" primary_expression  { $$ = UnaryOperator::make(toLoc(@$), UnaryOperatorKind::Plus, $2); }
| "-" primary_expression  { $$ = UnaryOperator::make(toLoc(@$), UnaryOperatorKind::Minus, $2); }
| "!" primary_expression  { $$ = UnaryOperator::make(toLoc(@$), UnaryOperatorKind::LogicalNot, $2); }
;

member_expression:
  expression "." "identifier" { $$ = MemberExpr::make(toLoc(@$), $1, $3); }
;

call_expression:
  expression "(" expression_list ")"  { $$ = CallExpr::make(toLoc(@$), $1, $3); }
;

expression_list:
  %empty                          { }
| expression                      { $$.push_back($1); }
| expression "," expression_list  { $$ = appendVector($1, $3); }
;

expression:
  primary_expression                { $$ = $1; }
| expression "+" expression         { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::Add, $1, $3); }
| expression "-" expression         { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::Subtract, $1, $3); }
| expression "*" expression         { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::Multiply, $1, $3); }
| expression "/" expression         { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::Divide, $1, $3); }
| expression "%" expression         { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::Mod, $1, $3); }
| expression "=" expression         { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::Assign, $1, $3); }
| expression "==" expression        { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::Equal, $1, $3); }
| expression "!=" expression        { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::NotEqual, $1, $3); }
| expression "&&" expression        { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::LogicalAnd, $1, $3); }
| expression "||" expression        { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::LogicalOr, $1, $3); }
| expression ">" expression         { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::GreaterThan, $1, $3); }
| expression ">=" expression        { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::GreaterThanOrEqual, $1, $3); }
| expression "<" expression         { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::LessThan, $1, $3); }
| expression "<=" expression        { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::LessThanOrEqual, $1, $3); }
| unary_expression                  { $$ = $1; }
| call_expression                   { $$ = $1; }
| member_expression                 { $$ = $1; }
| function_expression               { $$ = $1; }
;

%%

void yy::MyParser::error(const location_type& l, const std::string& m)
{
    driver.error(toLoc(l), m);
}
