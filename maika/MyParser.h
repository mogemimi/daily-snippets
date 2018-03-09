// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

/**
 ** \file MyParser.h
 ** Define the yy::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

#ifndef YY_YY_MYPARSER_H_INCLUDED
# define YY_YY_MYPARSER_H_INCLUDED
// //                    "%code requires" blocks.
#line 11 "MyParser.yy" // lalr1.cc:392

#include "ASTContext.h"
#include "Decl.h"
#include "Expr.h"
#include "Stmt.h"
#include <iostream>
#include <string>

class MyDriver;

#line 55 "MyParser.h" // lalr1.cc:392

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>
# include "stack.hh"
# include "location.hh"
#include <typeinfo>
#ifndef YYASSERT
# include <cassert>
# define YYASSERT assert
#endif


#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif


namespace yy {
#line 132 "MyParser.h" // lalr1.cc:392



  /// A char[S] buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current state.
  template <size_t S>
  struct variant
  {
    /// Type of *this.
    typedef variant<S> self_type;

    /// Empty construction.
    variant ()
      : yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    variant (const T& t)
      : yytypeid_ (&typeid (T))
    {
      YYASSERT (sizeof (T) <= S);
      new (yyas_<T> ()) T (t);
    }

    /// Destruction, allowed only if empty.
    ~variant ()
    {
      YYASSERT (!yytypeid_);
    }

    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    build ()
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T;
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    build (const T& t)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as ()
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Swap the content with \a other, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsability.
    /// Swapping between built and (possibly) non-built is done with
    /// variant::move ().
    template <typename T>
    void
    swap (self_type& other)
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == *other.yytypeid_);
      std::swap (as<T> (), other.as<T> ());
    }

    /// Move the content of \a other to this.
    ///
    /// Destroys \a other.
    template <typename T>
    void
    move (self_type& other)
    {
      build<T> ();
      swap<T> (other);
      other.destroy<T> ();
    }

    /// Copy the content of \a other to this.
    template <typename T>
    void
    copy (const self_type& other)
    {
      build<T> (other.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
    /// Prohibit blind copies.
    self_type& operator=(const self_type&);
    variant (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ ()
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[S];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };


  /// A Bison parser.
  class MyParser
  {
  public:
#ifndef YYSTYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // "bool_literal"
      char dummy1[sizeof(std::shared_ptr<BoolLiteral>)];

      // call_expression
      char dummy2[sizeof(std::shared_ptr<CallExpr>)];

      // compound_statement
      char dummy3[sizeof(std::shared_ptr<CompoundStmt>)];

      // "double_literal"
      char dummy4[sizeof(std::shared_ptr<DoubleLiteral>)];

      // literal
      // expression
      char dummy5[sizeof(std::shared_ptr<Expr>)];

      // function_definition
      char dummy6[sizeof(std::shared_ptr<FunctionDecl>)];

      // conditional_statement
      char dummy7[sizeof(std::shared_ptr<IfStmt>)];

      // "integer_literal"
      char dummy8[sizeof(std::shared_ptr<IntegerLiteral>)];

      // "identifier"
      char dummy9[sizeof(std::shared_ptr<NamedDecl>)];

      // parameter_variable
      char dummy10[sizeof(std::shared_ptr<ParmVarDecl>)];

      // return_statement
      char dummy11[sizeof(std::shared_ptr<ReturnStmt>)];

      // statement
      char dummy12[sizeof(std::shared_ptr<Stmt>)];

      // "string_literal"
      char dummy13[sizeof(std::shared_ptr<StringLiteral>)];

      // translation_unit
      char dummy14[sizeof(std::shared_ptr<TranslationUnitDecl>)];

      // variable_definition
      char dummy15[sizeof(std::shared_ptr<VariableDecl>)];

      // expressions
      char dummy16[sizeof(std::vector<std::shared_ptr<Expr>>)];

      // function_definitions
      char dummy17[sizeof(std::vector<std::shared_ptr<FunctionDecl>>)];

      // parameter_variables
      char dummy18[sizeof(std::vector<std::shared_ptr<ParmVarDecl>>)];

      // statements
      char dummy19[sizeof(std::vector<std::shared_ptr<Stmt>>)];
};

    /// Symbol semantic values.
    typedef variant<sizeof(union_type)> semantic_type;
#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m);
      location_type location;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        TOK_END = 0,
        TOK_ASSIGN = 258,
        TOK_MINUS = 259,
        TOK_PLUS = 260,
        TOK_STAR = 261,
        TOK_SLASH = 262,
        TOK_LOGICAL_NOT = 263,
        TOK_LOGICAL_AND = 264,
        TOK_LOGICAL_OR = 265,
        TOK_EQUAL = 266,
        TOK_NOT_EQUAL = 267,
        TOK_LEFT_PARENTHESIS = 268,
        TOK_RIGHT_PARENTHESIS = 269,
        TOK_LEFT_CURLY_BRACKET = 270,
        TOK_RIGHT_CURLY_BRACKET = 271,
        TOK_COLON = 272,
        TOK_SEMICOLON = 273,
        TOK_COMMA = 274,
        TOK_FUNCTION = 275,
        TOK_RETURN = 276,
        TOK_LET = 277,
        TOK_IF = 278,
        TOK_ELSE = 279,
        TOK_IDENTIFIER = 280,
        TOK_INTEGER_LITERAL = 281,
        TOK_DOUBLE_LITERAL = 282,
        TOK_BOOL_LITERAL = 283,
        TOK_STRING_LITERAL = 284
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Copy constructor.
      basic_symbol (const basic_symbol& other);

      /// Constructor for valueless symbols, and symbols from each type.

  basic_symbol (typename Base::kind_type t, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<BoolLiteral> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<CallExpr> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<CompoundStmt> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<DoubleLiteral> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<Expr> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<FunctionDecl> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<IfStmt> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<IntegerLiteral> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<NamedDecl> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<ParmVarDecl> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<ReturnStmt> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<Stmt> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<StringLiteral> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<TranslationUnitDecl> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<VariableDecl> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<Expr>> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<FunctionDecl>> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<ParmVarDecl>> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<Stmt>> v, const location_type& l);


      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    const semantic_type& v,
                    const location_type& l);

      /// Destroy the symbol.
      ~basic_symbol ();

      /// Destroy contents, and record that is empty.
      void clear ();

      /// Whether empty.
      bool empty () const;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

      /// Copy constructor.
      by_type (const by_type& other);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const;

      /// The token.
      token_type token () const;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    typedef basic_symbol<by_type> symbol_type;

    // Symbol constructors declarations.
    static inline
    symbol_type
    make_END (const location_type& l);

    static inline
    symbol_type
    make_ASSIGN (const location_type& l);

    static inline
    symbol_type
    make_MINUS (const location_type& l);

    static inline
    symbol_type
    make_PLUS (const location_type& l);

    static inline
    symbol_type
    make_STAR (const location_type& l);

    static inline
    symbol_type
    make_SLASH (const location_type& l);

    static inline
    symbol_type
    make_LOGICAL_NOT (const location_type& l);

    static inline
    symbol_type
    make_LOGICAL_AND (const location_type& l);

    static inline
    symbol_type
    make_LOGICAL_OR (const location_type& l);

    static inline
    symbol_type
    make_EQUAL (const location_type& l);

    static inline
    symbol_type
    make_NOT_EQUAL (const location_type& l);

    static inline
    symbol_type
    make_LEFT_PARENTHESIS (const location_type& l);

    static inline
    symbol_type
    make_RIGHT_PARENTHESIS (const location_type& l);

    static inline
    symbol_type
    make_LEFT_CURLY_BRACKET (const location_type& l);

    static inline
    symbol_type
    make_RIGHT_CURLY_BRACKET (const location_type& l);

    static inline
    symbol_type
    make_COLON (const location_type& l);

    static inline
    symbol_type
    make_SEMICOLON (const location_type& l);

    static inline
    symbol_type
    make_COMMA (const location_type& l);

    static inline
    symbol_type
    make_FUNCTION (const location_type& l);

    static inline
    symbol_type
    make_RETURN (const location_type& l);

    static inline
    symbol_type
    make_LET (const location_type& l);

    static inline
    symbol_type
    make_IF (const location_type& l);

    static inline
    symbol_type
    make_ELSE (const location_type& l);

    static inline
    symbol_type
    make_IDENTIFIER (const std::shared_ptr<NamedDecl>& v, const location_type& l);

    static inline
    symbol_type
    make_INTEGER_LITERAL (const std::shared_ptr<IntegerLiteral>& v, const location_type& l);

    static inline
    symbol_type
    make_DOUBLE_LITERAL (const std::shared_ptr<DoubleLiteral>& v, const location_type& l);

    static inline
    symbol_type
    make_BOOL_LITERAL (const std::shared_ptr<BoolLiteral>& v, const location_type& l);

    static inline
    symbol_type
    make_STRING_LITERAL (const std::shared_ptr<StringLiteral>& v, const location_type& l);


    /// Build a parser object.
    MyParser (MyDriver& driver_yyarg);
    virtual ~MyParser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

  private:
    /// This class is not copyable.
    MyParser (const MyParser&);
    MyParser& operator= (const MyParser&);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const signed char yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const short int yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const signed char yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const unsigned char yytable_[];

  static const unsigned char yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned char yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned char yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if YYDEBUG
  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned char yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const;

      /// The state number used to denote an empty symbol.
      enum { empty_state = -1 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, symbol_type& sym);
      /// Assignment, needed by push_back.
      stack_symbol_type& operator= (const stack_symbol_type& that);
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    void yypop_ (unsigned int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 144,     ///< Last index in yytable_.
      yynnts_ = 16,  ///< Number of nonterminal symbols.
      yyfinal_ = 6, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 30  ///< Number of tokens.
    };


    // User arguments.
    MyDriver& driver;
  };

  // Symbol number corresponding to token number t.
  inline
  MyParser::token_number_type
  MyParser::yytranslate_ (token_type t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29
    };
    const unsigned int user_token_number_max_ = 284;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  inline
  MyParser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  MyParser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  MyParser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
      switch (other.type_get ())
    {
      case 28: // "bool_literal"
        value.copy< std::shared_ptr<BoolLiteral> > (other.value);
        break;

      case 43: // call_expression
        value.copy< std::shared_ptr<CallExpr> > (other.value);
        break;

      case 37: // compound_statement
        value.copy< std::shared_ptr<CompoundStmt> > (other.value);
        break;

      case 27: // "double_literal"
        value.copy< std::shared_ptr<DoubleLiteral> > (other.value);
        break;

      case 42: // literal
      case 45: // expression
        value.copy< std::shared_ptr<Expr> > (other.value);
        break;

      case 33: // function_definition
        value.copy< std::shared_ptr<FunctionDecl> > (other.value);
        break;

      case 40: // conditional_statement
        value.copy< std::shared_ptr<IfStmt> > (other.value);
        break;

      case 26: // "integer_literal"
        value.copy< std::shared_ptr<IntegerLiteral> > (other.value);
        break;

      case 25: // "identifier"
        value.copy< std::shared_ptr<NamedDecl> > (other.value);
        break;

      case 35: // parameter_variable
        value.copy< std::shared_ptr<ParmVarDecl> > (other.value);
        break;

      case 39: // return_statement
        value.copy< std::shared_ptr<ReturnStmt> > (other.value);
        break;

      case 36: // statement
        value.copy< std::shared_ptr<Stmt> > (other.value);
        break;

      case 29: // "string_literal"
        value.copy< std::shared_ptr<StringLiteral> > (other.value);
        break;

      case 31: // translation_unit
        value.copy< std::shared_ptr<TranslationUnitDecl> > (other.value);
        break;

      case 41: // variable_definition
        value.copy< std::shared_ptr<VariableDecl> > (other.value);
        break;

      case 44: // expressions
        value.copy< std::vector<std::shared_ptr<Expr>> > (other.value);
        break;

      case 32: // function_definitions
        value.copy< std::vector<std::shared_ptr<FunctionDecl>> > (other.value);
        break;

      case 34: // parameter_variables
        value.copy< std::vector<std::shared_ptr<ParmVarDecl>> > (other.value);
        break;

      case 38: // statements
        value.copy< std::vector<std::shared_ptr<Stmt>> > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
  MyParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {
    (void) v;
      switch (this->type_get ())
    {
      case 28: // "bool_literal"
        value.copy< std::shared_ptr<BoolLiteral> > (v);
        break;

      case 43: // call_expression
        value.copy< std::shared_ptr<CallExpr> > (v);
        break;

      case 37: // compound_statement
        value.copy< std::shared_ptr<CompoundStmt> > (v);
        break;

      case 27: // "double_literal"
        value.copy< std::shared_ptr<DoubleLiteral> > (v);
        break;

      case 42: // literal
      case 45: // expression
        value.copy< std::shared_ptr<Expr> > (v);
        break;

      case 33: // function_definition
        value.copy< std::shared_ptr<FunctionDecl> > (v);
        break;

      case 40: // conditional_statement
        value.copy< std::shared_ptr<IfStmt> > (v);
        break;

      case 26: // "integer_literal"
        value.copy< std::shared_ptr<IntegerLiteral> > (v);
        break;

      case 25: // "identifier"
        value.copy< std::shared_ptr<NamedDecl> > (v);
        break;

      case 35: // parameter_variable
        value.copy< std::shared_ptr<ParmVarDecl> > (v);
        break;

      case 39: // return_statement
        value.copy< std::shared_ptr<ReturnStmt> > (v);
        break;

      case 36: // statement
        value.copy< std::shared_ptr<Stmt> > (v);
        break;

      case 29: // "string_literal"
        value.copy< std::shared_ptr<StringLiteral> > (v);
        break;

      case 31: // translation_unit
        value.copy< std::shared_ptr<TranslationUnitDecl> > (v);
        break;

      case 41: // variable_definition
        value.copy< std::shared_ptr<VariableDecl> > (v);
        break;

      case 44: // expressions
        value.copy< std::vector<std::shared_ptr<Expr>> > (v);
        break;

      case 32: // function_definitions
        value.copy< std::vector<std::shared_ptr<FunctionDecl>> > (v);
        break;

      case 34: // parameter_variables
        value.copy< std::vector<std::shared_ptr<ParmVarDecl>> > (v);
        break;

      case 38: // statements
        value.copy< std::vector<std::shared_ptr<Stmt>> > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
  MyParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  MyParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<BoolLiteral> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  MyParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<CallExpr> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  MyParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<CompoundStmt> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  MyParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<DoubleLiteral> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  MyParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<Expr> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  MyParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<FunctionDecl> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  MyParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<IfStmt> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  MyParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<IntegerLiteral> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  MyParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<NamedDecl> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  MyParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<ParmVarDecl> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  MyParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<ReturnStmt> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  MyParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<Stmt> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  MyParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<StringLiteral> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  MyParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<TranslationUnitDecl> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  MyParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<VariableDecl> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  MyParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<Expr>> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  MyParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<FunctionDecl>> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  MyParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<ParmVarDecl>> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  MyParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<Stmt>> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  template <typename Base>
  inline
  MyParser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  MyParser::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
    switch (yytype)
    {
      case 28: // "bool_literal"
        value.template destroy< std::shared_ptr<BoolLiteral> > ();
        break;

      case 43: // call_expression
        value.template destroy< std::shared_ptr<CallExpr> > ();
        break;

      case 37: // compound_statement
        value.template destroy< std::shared_ptr<CompoundStmt> > ();
        break;

      case 27: // "double_literal"
        value.template destroy< std::shared_ptr<DoubleLiteral> > ();
        break;

      case 42: // literal
      case 45: // expression
        value.template destroy< std::shared_ptr<Expr> > ();
        break;

      case 33: // function_definition
        value.template destroy< std::shared_ptr<FunctionDecl> > ();
        break;

      case 40: // conditional_statement
        value.template destroy< std::shared_ptr<IfStmt> > ();
        break;

      case 26: // "integer_literal"
        value.template destroy< std::shared_ptr<IntegerLiteral> > ();
        break;

      case 25: // "identifier"
        value.template destroy< std::shared_ptr<NamedDecl> > ();
        break;

      case 35: // parameter_variable
        value.template destroy< std::shared_ptr<ParmVarDecl> > ();
        break;

      case 39: // return_statement
        value.template destroy< std::shared_ptr<ReturnStmt> > ();
        break;

      case 36: // statement
        value.template destroy< std::shared_ptr<Stmt> > ();
        break;

      case 29: // "string_literal"
        value.template destroy< std::shared_ptr<StringLiteral> > ();
        break;

      case 31: // translation_unit
        value.template destroy< std::shared_ptr<TranslationUnitDecl> > ();
        break;

      case 41: // variable_definition
        value.template destroy< std::shared_ptr<VariableDecl> > ();
        break;

      case 44: // expressions
        value.template destroy< std::vector<std::shared_ptr<Expr>> > ();
        break;

      case 32: // function_definitions
        value.template destroy< std::vector<std::shared_ptr<FunctionDecl>> > ();
        break;

      case 34: // parameter_variables
        value.template destroy< std::vector<std::shared_ptr<ParmVarDecl>> > ();
        break;

      case 38: // statements
        value.template destroy< std::vector<std::shared_ptr<Stmt>> > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  MyParser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  MyParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 28: // "bool_literal"
        value.move< std::shared_ptr<BoolLiteral> > (s.value);
        break;

      case 43: // call_expression
        value.move< std::shared_ptr<CallExpr> > (s.value);
        break;

      case 37: // compound_statement
        value.move< std::shared_ptr<CompoundStmt> > (s.value);
        break;

      case 27: // "double_literal"
        value.move< std::shared_ptr<DoubleLiteral> > (s.value);
        break;

      case 42: // literal
      case 45: // expression
        value.move< std::shared_ptr<Expr> > (s.value);
        break;

      case 33: // function_definition
        value.move< std::shared_ptr<FunctionDecl> > (s.value);
        break;

      case 40: // conditional_statement
        value.move< std::shared_ptr<IfStmt> > (s.value);
        break;

      case 26: // "integer_literal"
        value.move< std::shared_ptr<IntegerLiteral> > (s.value);
        break;

      case 25: // "identifier"
        value.move< std::shared_ptr<NamedDecl> > (s.value);
        break;

      case 35: // parameter_variable
        value.move< std::shared_ptr<ParmVarDecl> > (s.value);
        break;

      case 39: // return_statement
        value.move< std::shared_ptr<ReturnStmt> > (s.value);
        break;

      case 36: // statement
        value.move< std::shared_ptr<Stmt> > (s.value);
        break;

      case 29: // "string_literal"
        value.move< std::shared_ptr<StringLiteral> > (s.value);
        break;

      case 31: // translation_unit
        value.move< std::shared_ptr<TranslationUnitDecl> > (s.value);
        break;

      case 41: // variable_definition
        value.move< std::shared_ptr<VariableDecl> > (s.value);
        break;

      case 44: // expressions
        value.move< std::vector<std::shared_ptr<Expr>> > (s.value);
        break;

      case 32: // function_definitions
        value.move< std::vector<std::shared_ptr<FunctionDecl>> > (s.value);
        break;

      case 34: // parameter_variables
        value.move< std::vector<std::shared_ptr<ParmVarDecl>> > (s.value);
        break;

      case 38: // statements
        value.move< std::vector<std::shared_ptr<Stmt>> > (s.value);
        break;

      default:
        break;
    }

    location = s.location;
  }

  // by_type.
  inline
  MyParser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  MyParser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  MyParser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  MyParser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  MyParser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  MyParser::by_type::type_get () const
  {
    return type;
  }

  inline
  MyParser::token_type
  MyParser::by_type::token () const
  {
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short int
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }
  // Implementation of make_symbol for each symbol type.
  MyParser::symbol_type
  MyParser::make_END (const location_type& l)
  {
    return symbol_type (token::TOK_END, l);
  }

  MyParser::symbol_type
  MyParser::make_ASSIGN (const location_type& l)
  {
    return symbol_type (token::TOK_ASSIGN, l);
  }

  MyParser::symbol_type
  MyParser::make_MINUS (const location_type& l)
  {
    return symbol_type (token::TOK_MINUS, l);
  }

  MyParser::symbol_type
  MyParser::make_PLUS (const location_type& l)
  {
    return symbol_type (token::TOK_PLUS, l);
  }

  MyParser::symbol_type
  MyParser::make_STAR (const location_type& l)
  {
    return symbol_type (token::TOK_STAR, l);
  }

  MyParser::symbol_type
  MyParser::make_SLASH (const location_type& l)
  {
    return symbol_type (token::TOK_SLASH, l);
  }

  MyParser::symbol_type
  MyParser::make_LOGICAL_NOT (const location_type& l)
  {
    return symbol_type (token::TOK_LOGICAL_NOT, l);
  }

  MyParser::symbol_type
  MyParser::make_LOGICAL_AND (const location_type& l)
  {
    return symbol_type (token::TOK_LOGICAL_AND, l);
  }

  MyParser::symbol_type
  MyParser::make_LOGICAL_OR (const location_type& l)
  {
    return symbol_type (token::TOK_LOGICAL_OR, l);
  }

  MyParser::symbol_type
  MyParser::make_EQUAL (const location_type& l)
  {
    return symbol_type (token::TOK_EQUAL, l);
  }

  MyParser::symbol_type
  MyParser::make_NOT_EQUAL (const location_type& l)
  {
    return symbol_type (token::TOK_NOT_EQUAL, l);
  }

  MyParser::symbol_type
  MyParser::make_LEFT_PARENTHESIS (const location_type& l)
  {
    return symbol_type (token::TOK_LEFT_PARENTHESIS, l);
  }

  MyParser::symbol_type
  MyParser::make_RIGHT_PARENTHESIS (const location_type& l)
  {
    return symbol_type (token::TOK_RIGHT_PARENTHESIS, l);
  }

  MyParser::symbol_type
  MyParser::make_LEFT_CURLY_BRACKET (const location_type& l)
  {
    return symbol_type (token::TOK_LEFT_CURLY_BRACKET, l);
  }

  MyParser::symbol_type
  MyParser::make_RIGHT_CURLY_BRACKET (const location_type& l)
  {
    return symbol_type (token::TOK_RIGHT_CURLY_BRACKET, l);
  }

  MyParser::symbol_type
  MyParser::make_COLON (const location_type& l)
  {
    return symbol_type (token::TOK_COLON, l);
  }

  MyParser::symbol_type
  MyParser::make_SEMICOLON (const location_type& l)
  {
    return symbol_type (token::TOK_SEMICOLON, l);
  }

  MyParser::symbol_type
  MyParser::make_COMMA (const location_type& l)
  {
    return symbol_type (token::TOK_COMMA, l);
  }

  MyParser::symbol_type
  MyParser::make_FUNCTION (const location_type& l)
  {
    return symbol_type (token::TOK_FUNCTION, l);
  }

  MyParser::symbol_type
  MyParser::make_RETURN (const location_type& l)
  {
    return symbol_type (token::TOK_RETURN, l);
  }

  MyParser::symbol_type
  MyParser::make_LET (const location_type& l)
  {
    return symbol_type (token::TOK_LET, l);
  }

  MyParser::symbol_type
  MyParser::make_IF (const location_type& l)
  {
    return symbol_type (token::TOK_IF, l);
  }

  MyParser::symbol_type
  MyParser::make_ELSE (const location_type& l)
  {
    return symbol_type (token::TOK_ELSE, l);
  }

  MyParser::symbol_type
  MyParser::make_IDENTIFIER (const std::shared_ptr<NamedDecl>& v, const location_type& l)
  {
    return symbol_type (token::TOK_IDENTIFIER, v, l);
  }

  MyParser::symbol_type
  MyParser::make_INTEGER_LITERAL (const std::shared_ptr<IntegerLiteral>& v, const location_type& l)
  {
    return symbol_type (token::TOK_INTEGER_LITERAL, v, l);
  }

  MyParser::symbol_type
  MyParser::make_DOUBLE_LITERAL (const std::shared_ptr<DoubleLiteral>& v, const location_type& l)
  {
    return symbol_type (token::TOK_DOUBLE_LITERAL, v, l);
  }

  MyParser::symbol_type
  MyParser::make_BOOL_LITERAL (const std::shared_ptr<BoolLiteral>& v, const location_type& l)
  {
    return symbol_type (token::TOK_BOOL_LITERAL, v, l);
  }

  MyParser::symbol_type
  MyParser::make_STRING_LITERAL (const std::shared_ptr<StringLiteral>& v, const location_type& l)
  {
    return symbol_type (token::TOK_STRING_LITERAL, v, l);
  }



} // yy
#line 1705 "MyParser.h" // lalr1.cc:392




#endif // !YY_YY_MYPARSER_H_INCLUDED
