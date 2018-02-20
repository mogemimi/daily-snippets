#pragma once

// NOTE: AST
class AST;
class ASTDumper;
class ASTVisitor;

// NOTE: AST::Stmt
class Stmt;
class CompoundStmt;
class ReturnStmt;

// NOTE: AST::Expr
class Expr;
class CallExpr;
class IntegerLiteral;
class DoubleLiteral;
class BoolLiteral;
class AssignmentOperator;
class BinaryOperator;
class DeclRefExpr;

// NOTE: AST::Decl
class Decl;
class FunctionDecl;
class NamedDecl;
class ParmVarDecl;
class VariableDecl;

// NOTE: AST::Type
class Type;

// NOTE: Sema
class Entity;
class Scope;
