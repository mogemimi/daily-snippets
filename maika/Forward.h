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

// NOTE: AST::Decl
class Decl;
class FunctionDecl;
class NamedDecl;
class VariableDecl;

// NOTE: AST::Type
class Type;

// NOTE: Sema
class Entity;
class Scope;
