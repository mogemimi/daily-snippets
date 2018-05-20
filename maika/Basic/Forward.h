#pragma once

// NOTE: Basic
class Location;
class Position;

// NOTE: Preprocessor
class Comment;
enum class CommentKind;

// NOTE: ADT (Abstract data types)
class Value;
class BoolValue;
class DoubleValue;
class Int64Value;
class StringValue;
class NullValue;

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
class ForRangeStmt;

// NOTE: AST::Expr
class Expr;
class CallExpr;
class FunctionExpr;
class IntegerLiteral;
class DoubleLiteral;
class BoolLiteral;
class StringLiteral;
class NullLiteral;
class BinaryOperator;
class UnaryOperator;
class DeclRefExpr;
class MemberExpr;
class SubscriptExpr;
class ArrayLiteral;
class MapEntry;
class MapLiteral;
class ImplicitStaticCastExpr;

enum class BinaryOperatorKind;

// NOTE: AST::Decl
class Decl;
class FunctionDecl;
class NamedDecl;
class ParmVarDecl;
class TranslationUnitDecl;
class VariableDecl;
class ConstDecl;
class BindingDecl;
class DecompositionDecl;

// NOTE: AST::Type
class Type;

enum class BuiltinTypeKind;

// NOTE: Sema
class Entity;
class Scope;

// NOTE: Diagnostic
class DiagnosticHandler;

// NOTE: Tools
class PrettyPrinter;
