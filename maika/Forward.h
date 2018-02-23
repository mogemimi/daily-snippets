#pragma once

// NOTE: AST
class AST;
class ASTDumper;
class ASTVisitor;

// NOTE: AST::Stmt
class Stmt;
class CompoundStmt;
class DeclStmt;
class ReturnStmt;

// NOTE: AST::Expr
class Expr;
class CallExpr;
class IntegerLiteral;
class DoubleLiteral;
class BoolLiteral;
class BinaryOperator;
class DeclRefExpr;

// NOTE: AST::Decl
class Decl;
class FunctionDecl;
class NamedDecl;
class ParmVarDecl;
class TranslationUnitDecl;
class VariableDecl;

// NOTE: AST::Type
class Type;

// NOTE: Sema
class Entity;
class Scope;
