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
#include "AST/ASTContext.h"
#include "AST/Decl.h"
#include "AST/Expr.h"
#include "AST/Stmt.h"
#include "Basic/Location.h"
#include "Basic/Forward.h"
#include <memory>
#include <string>
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
#include "Driver/Driver.h"

namespace {
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
%token IN                   "in"
%token CLASS                "class"
%token NULL                 "null"

%token <std::shared_ptr<NamedDecl>>                 IDENTIFIER "identifier"
%token <std::shared_ptr<IntegerLiteral>>            INTEGER_LITERAL "integer_literal"
%token <std::shared_ptr<DoubleLiteral>>             DOUBLE_LITERAL "double_literal"
%token <std::shared_ptr<BoolLiteral>>               BOOL_LITERAL "bool_literal"
%token <std::shared_ptr<StringLiteral>>             STRING_LITERAL "string_literal"
%type  <std::shared_ptr<NullLiteral>>               null_literal
%type  <std::shared_ptr<Expr>>                      literal
%type  <std::shared_ptr<ArrayLiteral>>              array_literal
%type  <std::shared_ptr<MapLiteral>>                map_literal
%type  <std::vector<std::shared_ptr<MapEntry>>>     map_entry_list
%type  <std::shared_ptr<MapEntry>>                  map_entry
%type  <std::shared_ptr<Expr>>                      primary_expression
%type  <std::shared_ptr<Expr>>                      expression
%type  <std::vector<std::shared_ptr<Expr>>>         expression_list
%type  <std::shared_ptr<UnaryOperator>>             unary_expression
%type  <std::shared_ptr<BinaryOperator>>            binary_expression
%type  <std::shared_ptr<BinaryOperator>>            assignment_expression                
%type  <std::shared_ptr<Stmt>>                      statement
%type  <std::vector<std::shared_ptr<Stmt>>>         statement_list
%type  <std::shared_ptr<NamedDecl>>                 binding_identifier
%type  <std::shared_ptr<MemberExpr>>                member_expression
%type  <std::shared_ptr<SubscriptExpr>>             subscript_expression
%type  <std::shared_ptr<CallExpr>>                  call_expression
%type  <std::vector<std::shared_ptr<ParmVarDecl>>>  parameter_variables
%type  <std::shared_ptr<ParmVarDecl>>               parameter_variable
%type  <std::shared_ptr<CompoundStmt>>              compound_statement
%type  <std::shared_ptr<ReturnStmt>>                return_statement
%type  <std::shared_ptr<IfStmt>>                    if_statement
%type  <std::shared_ptr<WhileStmt>>                 while_statement
%type  <std::shared_ptr<ForStmt>>                   for_statement
%type  <std::shared_ptr<Stmt>>                      for_init_statement
%type  <std::shared_ptr<ForRangeStmt>>              for_range_statement
%type  <std::shared_ptr<Decl>>                      for_range_init
%type  <std::shared_ptr<FunctionDecl>>              function_definition
%type  <std::shared_ptr<FunctionExpr>>              function_expression
%type  <CallSignature>                              call_signature
%type  <std::shared_ptr<VariableDecl>>              variable_definition
%type  <std::shared_ptr<ConstDecl>>                 const_definition
%type  <std::shared_ptr<DecompositionDecl>>         decomposition_definition
%type  <std::vector<std::shared_ptr<BindingDecl>>>  binding_declarations
%type  <std::shared_ptr<BindingDecl>>               binding_declaration
%type  <std::shared_ptr<NamedDecl>>                 type_specifier
%type  <std::shared_ptr<ClassDecl>>                 class_declaration
%type  <std::vector<std::shared_ptr<Decl>>>         member_declaration_list
%type  <std::shared_ptr<Decl>>                      member_declaration
%type  <std::vector<std::shared_ptr<Decl>>>         translation_unit_declarations
%type  <std::shared_ptr<Decl>>                      translation_unit_declaration
%type  <std::shared_ptr<TranslationUnitDecl>>       translation_unit

%%
%start translation_unit;

translation_unit:
  %empty                        { driver.ast.translationUnit = TranslationUnitDecl::make(toLoc(@$), std::vector<std::shared_ptr<Decl>>{}); }
| translation_unit_declarations { driver.ast.translationUnit = TranslationUnitDecl::make(toLoc(@$), $1); }
;

translation_unit_declarations:
  translation_unit_declaration                                { $$.push_back($1); }
| translation_unit_declarations translation_unit_declaration  { $1.push_back($2); $$ = std::move($1); }
;

translation_unit_declaration:
  class_declaration   { $$ = $1; }
| function_definition { $$ = $1; }
;

function_definition:
  "function" "identifier" call_signature compound_statement { $$ = FunctionDecl::make(toLoc(@$), $2, std::get<0>($3), std::get<1>($3), $4); }
;

function_expression:
  "function" binding_identifier call_signature compound_statement { $$ = FunctionExpr::make(toLoc(@$), $2, std::get<0>($3), std::get<1>($3), $4); }
;

call_signature:
  "(" ")"                                         { std::get<1>($$) = nullptr; }
| "(" ")" ":" type_specifier                      { std::get<1>($$) = $4; }
| "(" parameter_variables ")"                     { std::get<0>($$) = $2; std::get<1>($$) = nullptr; }
| "(" parameter_variables ")" ":" type_specifier  { std::get<0>($$) = $2; std::get<1>($$) = $5; }
;

binding_identifier:
  %empty        { }
| "identifier"  { $$ = $1; }
;

parameter_variables:
  parameter_variable                          { $$.push_back($1); }
| parameter_variables "," parameter_variable  { $1.push_back($3); $$ = std::move($1); }
;

parameter_variable:
  "identifier"                    { $$ = ParmVarDecl::make(toLoc(@$), $1); }
| "identifier" ":" type_specifier { $$ = ParmVarDecl::make(toLoc(@$), $1, $3); }
;

type_specifier:
  "identifier"  { $$ = $1; }
;

class_declaration:
  "class" "identifier" "{" "}"                          { $$ = ClassDecl::make(toLoc(@$), $2, std::vector<std::shared_ptr<Decl>>{}); }
| "class" "identifier" "{" member_declaration_list "}"  { $$ = ClassDecl::make(toLoc(@$), $2, $4); }
;

member_declaration_list:
  member_declaration                          { $$.push_back($1); }
| member_declaration_list member_declaration  { $1.push_back($2); $$ = std::move($1); }
;

member_declaration:
  function_definition     { $$ = $1; }
| variable_definition ";" { $$ = $1; }
| const_definition ";"    { $$ = $1; }
;

statement:
  compound_statement            { $$ = $1; }
| expression ";"                { $$ = $1; }
| return_statement              { $$ = $1; }
| variable_definition ";"       { $$ = DeclStmt::make(toLoc(@$), $1); }
| const_definition ";"          { $$ = DeclStmt::make(toLoc(@$), $1); }
| decomposition_definition ";"  { $$ = DeclStmt::make(toLoc(@$), $1); }
| if_statement                  { $$ = $1; }
| while_statement               { $$ = $1; }
| for_statement                 { $$ = $1; }
| for_range_statement           { $$ = $1; }
;

compound_statement:
  "{" "}"                 { $$ = CompoundStmt::make(toLoc(@$), std::vector<std::shared_ptr<Stmt>>{}); }
| "{" statement_list "}"  { $$ = CompoundStmt::make(toLoc(@$), $2); }
;

statement_list:
  statement                 { $$.push_back($1); }
| statement_list statement  { $1.push_back($2); $$ = std::move($1); }
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

for_range_statement:
  "for" "(" for_range_init "in" expression ")" statement  { $$ = ForRangeStmt::make(toLoc(@$), $3, $5, $7); }
;

for_range_init:
  "identifier"                          { $$ = $1; }
| "let" "identifier"                    { $$ = VariableDecl::make(toLoc(@$), $2); }
| "const" "identifier"                  { $$ = ConstDecl::make(toLoc(@$), $2); }
| "let" "(" binding_declarations ")"    { $$ = DecompositionDecl::make(toLoc(@$), $3); }
| "const" "(" binding_declarations ")"  { $$ = DecompositionDecl::make(toLoc(@$), $3); }
;

variable_definition:
  "let" "identifier"                { $$ = VariableDecl::make(toLoc(@$), $2); }
| "let" "identifier" "=" expression { $$ = VariableDecl::make(toLoc(@$), $2, $4); }
;

const_definition:
  "const" "identifier"                { $$ = ConstDecl::make(toLoc(@$), $2); }
| "const" "identifier" "=" expression { $$ = ConstDecl::make(toLoc(@$), $2, $4); }
;

decomposition_definition:
  "let" "(" binding_declarations ")" "=" expression { $$ = DecompositionDecl::make(toLoc(@$), $3, $6); }
| "const" "(" binding_declarations ")" "=" expression { $$ = DecompositionDecl::make(toLoc(@$), $3, $6); }
;

binding_declarations:
  binding_declaration                           { $$.push_back($1); }
| binding_declarations "," binding_declaration  { $1.push_back($3); $$ = std::move($1); }
;

binding_declaration:
  "identifier"  { $$ = BindingDecl::make(toLoc(@$), $1); }
;

comma_opt:
  %empty  { }
| ","     { }
;

literal:
  "integer_literal" { $$ = $1; }
| "double_literal"  { $$ = $1; }
| "bool_literal"    { $$ = $1; }
| "string_literal"  { $$ = $1; }
;

%left ",";
%right "=";
%left "||";
%left "&&";
%left "==" "!=";
%left "<=" ">=" "<" ">";
%left "+" "-";
%left "*" "/" "%";
%left "unary_plus" "unary_minus";
%right "++" "--" "!";
%left "." "[" "]";
%nonassoc "(" ")";

primary_expression:
  literal                 { $$ = $1; }
| null_literal            { $$ = $1; }
| "identifier"            { $$ = DeclRefExpr::make(toLoc(@$), $1); }
| "(" expression ")"      { std::swap($$, $2); }
| array_literal           { $$ = $1; }
| map_literal             { $$ = $1; }
;

null_literal:
  "null"  { $$ = NullLiteral::make(toLoc(@$)); }
;

array_literal:
  "[" "]"                           { $$ = ArrayLiteral::make(toLoc(@$), std::vector<std::shared_ptr<Expr>>{}); }
| "[" expression_list comma_opt "]" { $$ = ArrayLiteral::make(toLoc(@$), $2); }
;

map_literal:
  "[" ":" "]"                       { $$ = MapLiteral::make(toLoc(@$), std::vector<std::shared_ptr<MapEntry>>{}); }
| "[" map_entry_list comma_opt "]"  { $$ = MapLiteral::make(toLoc(@$), $2); }
;

map_entry:
  expression ":" expression     { $$ = MapEntry::make(toLoc(@$), $1, $3); }
;

map_entry_list:
  map_entry                     { $$.push_back($1); }
| map_entry_list "," map_entry  { $1.push_back($3); $$ = std::move($1); }
;

member_expression:
  expression "." "identifier" { $$ = MemberExpr::make(toLoc(@$), $1, $3); }
;

subscript_expression:
  expression "[" expression "]" { $$ = SubscriptExpr::make(toLoc(@$), $1, $3); }
;

call_expression:
  expression "(" ")"                  { $$ = CallExpr::make(toLoc(@$), $1, std::vector<std::shared_ptr<Expr>>{}); }
| expression "(" expression_list ")"  { $$ = CallExpr::make(toLoc(@$), $1, $3); }
;

unary_expression:
  "++" primary_expression                     { $$ = UnaryOperator::make(toLoc(@$), UnaryOperatorKind::PreInc, $2); }
| "--" primary_expression                     { $$ = UnaryOperator::make(toLoc(@$), UnaryOperatorKind::PreDec, $2); }
| primary_expression "++"                     { $$ = UnaryOperator::make(toLoc(@$), UnaryOperatorKind::PostInc, $1); }
| primary_expression "--"                     { $$ = UnaryOperator::make(toLoc(@$), UnaryOperatorKind::PostDec, $1); }
| "+" primary_expression %prec "unary_plus"   { $$ = UnaryOperator::make(toLoc(@$), UnaryOperatorKind::Plus, $2); }
| "-" primary_expression %prec "unary_minus"  { $$ = UnaryOperator::make(toLoc(@$), UnaryOperatorKind::Minus, $2); }
| "!" primary_expression                      { $$ = UnaryOperator::make(toLoc(@$), UnaryOperatorKind::LogicalNot, $2); }
;

binary_expression:
  expression "+" expression         { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::Add, $1, $3); }
| expression "-" expression         { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::Subtract, $1, $3); }
| expression "*" expression         { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::Multiply, $1, $3); }
| expression "/" expression         { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::Divide, $1, $3); }
| expression "%" expression         { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::Mod, $1, $3); }
| expression "==" expression        { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::Equal, $1, $3); }
| expression "!=" expression        { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::NotEqual, $1, $3); }
| expression "&&" expression        { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::LogicalAnd, $1, $3); }
| expression "||" expression        { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::LogicalOr, $1, $3); }
| expression ">" expression         { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::GreaterThan, $1, $3); }
| expression ">=" expression        { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::GreaterThanOrEqual, $1, $3); }
| expression "<" expression         { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::LessThan, $1, $3); }
| expression "<=" expression        { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::LessThanOrEqual, $1, $3); }
;

assignment_expression:
  expression "=" expression         { $$ = BinaryOperator::make(toLoc(@$), BinaryOperatorKind::Assign, $1, $3); }
;

expression_list:
  expression                        { $$.push_back($1); }
| expression_list "," expression    { $1.push_back($3); $$ = std::move($1); }
;

expression:
  primary_expression                { $$ = $1; }
| assignment_expression             { $$ = $1; }
| binary_expression                 { $$ = $1; }
| unary_expression                  { $$ = $1; }
| call_expression                   { $$ = $1; }
| member_expression                 { $$ = $1; }
| subscript_expression              { $$ = $1; }
| function_expression               { $$ = $1; }
;

%%

void yy::MyParser::error(const location_type& l, const std::string& m)
{
    driver.error(toLoc(l), m);
}
