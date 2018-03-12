#pragma once

// NOTE: AST
class ASTContext;
class ASTVisitor;

// NOTE: AST::Stmt
class Stmt;
class CompoundStmt;
class DeclStmt;
class ReturnStmt;
class IfStmt;
class WhileStmt;
class ForStmt;

// NOTE: AST::Expr
class Expr;
class CallExpr;
class FunctionExpr;
class IntegerLiteral;
class DoubleLiteral;
class BoolLiteral;
class StringLiteral;
class BinaryOperator;
class UnaryOperator;
class DeclRefExpr;
class MemberExpr;

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

// NOTE: Diagnostic
class DiagnosticHandler;

// NOTE: Tools
class Formatter;
