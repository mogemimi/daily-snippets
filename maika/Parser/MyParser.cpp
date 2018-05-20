// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

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


// First part of user declarations.

#line 37 "Parser/MyParser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "MyParser.h"

// User implementation prologue.

#line 51 "Parser/MyParser.cpp" // lalr1.cc:412
// Unqualified %code blocks.
#line 52 "Parser/MyParser.yy" // lalr1.cc:413

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

#line 76 "Parser/MyParser.cpp" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 162 "Parser/MyParser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  MyParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  MyParser::MyParser (MyDriver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  MyParser::~MyParser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  MyParser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  MyParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  MyParser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  MyParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  MyParser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  MyParser::symbol_number_type
  MyParser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  MyParser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  MyParser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 59: // call_signature
        value.move< CallSignature > (that.value);
        break;

      case 83: // array_literal
        value.move< std::shared_ptr<ArrayLiteral> > (that.value);
        break;

      case 91: // binary_expression
      case 92: // assignment_expression
        value.move< std::shared_ptr<BinaryOperator> > (that.value);
        break;

      case 78: // binding_declaration
        value.move< std::shared_ptr<BindingDecl> > (that.value);
        break;

      case 49: // "bool_literal"
        value.move< std::shared_ptr<BoolLiteral> > (that.value);
        break;

      case 89: // call_expression
        value.move< std::shared_ptr<CallExpr> > (that.value);
        break;

      case 65: // compound_statement
        value.move< std::shared_ptr<CompoundStmt> > (that.value);
        break;

      case 75: // const_definition
        value.move< std::shared_ptr<ConstDecl> > (that.value);
        break;

      case 73: // for_range_init
        value.move< std::shared_ptr<Decl> > (that.value);
        break;

      case 76: // decomposition_definition
        value.move< std::shared_ptr<DecompositionDecl> > (that.value);
        break;

      case 48: // "double_literal"
        value.move< std::shared_ptr<DoubleLiteral> > (that.value);
        break;

      case 80: // literal
      case 81: // primary_expression
      case 94: // expression
        value.move< std::shared_ptr<Expr> > (that.value);
        break;

      case 72: // for_range_statement
        value.move< std::shared_ptr<ForRangeStmt> > (that.value);
        break;

      case 70: // for_statement
        value.move< std::shared_ptr<ForStmt> > (that.value);
        break;

      case 57: // function_definition
        value.move< std::shared_ptr<FunctionDecl> > (that.value);
        break;

      case 58: // function_expression
        value.move< std::shared_ptr<FunctionExpr> > (that.value);
        break;

      case 68: // if_statement
        value.move< std::shared_ptr<IfStmt> > (that.value);
        break;

      case 47: // "integer_literal"
        value.move< std::shared_ptr<IntegerLiteral> > (that.value);
        break;

      case 85: // map_entry
        value.move< std::shared_ptr<MapEntry> > (that.value);
        break;

      case 84: // map_literal
        value.move< std::shared_ptr<MapLiteral> > (that.value);
        break;

      case 87: // member_expression
        value.move< std::shared_ptr<MemberExpr> > (that.value);
        break;

      case 46: // "identifier"
      case 60: // binding_identifier
      case 63: // type_specifier
        value.move< std::shared_ptr<NamedDecl> > (that.value);
        break;

      case 82: // null_literal
        value.move< std::shared_ptr<NullLiteral> > (that.value);
        break;

      case 62: // parameter_variable
        value.move< std::shared_ptr<ParmVarDecl> > (that.value);
        break;

      case 67: // return_statement
        value.move< std::shared_ptr<ReturnStmt> > (that.value);
        break;

      case 64: // statement
      case 71: // for_init_statement
        value.move< std::shared_ptr<Stmt> > (that.value);
        break;

      case 50: // "string_literal"
        value.move< std::shared_ptr<StringLiteral> > (that.value);
        break;

      case 88: // subscript_expression
        value.move< std::shared_ptr<SubscriptExpr> > (that.value);
        break;

      case 55: // translation_unit
        value.move< std::shared_ptr<TranslationUnitDecl> > (that.value);
        break;

      case 90: // unary_expression
        value.move< std::shared_ptr<UnaryOperator> > (that.value);
        break;

      case 74: // variable_definition
        value.move< std::shared_ptr<VariableDecl> > (that.value);
        break;

      case 69: // while_statement
        value.move< std::shared_ptr<WhileStmt> > (that.value);
        break;

      case 77: // binding_declarations
        value.move< std::vector<std::shared_ptr<BindingDecl>> > (that.value);
        break;

      case 93: // expression_list
        value.move< std::vector<std::shared_ptr<Expr>> > (that.value);
        break;

      case 56: // function_definitions
        value.move< std::vector<std::shared_ptr<FunctionDecl>> > (that.value);
        break;

      case 86: // map_entry_list
        value.move< std::vector<std::shared_ptr<MapEntry>> > (that.value);
        break;

      case 61: // parameter_variables
        value.move< std::vector<std::shared_ptr<ParmVarDecl>> > (that.value);
        break;

      case 66: // statement_list
        value.move< std::vector<std::shared_ptr<Stmt>> > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  MyParser::stack_symbol_type&
  MyParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 59: // call_signature
        value.copy< CallSignature > (that.value);
        break;

      case 83: // array_literal
        value.copy< std::shared_ptr<ArrayLiteral> > (that.value);
        break;

      case 91: // binary_expression
      case 92: // assignment_expression
        value.copy< std::shared_ptr<BinaryOperator> > (that.value);
        break;

      case 78: // binding_declaration
        value.copy< std::shared_ptr<BindingDecl> > (that.value);
        break;

      case 49: // "bool_literal"
        value.copy< std::shared_ptr<BoolLiteral> > (that.value);
        break;

      case 89: // call_expression
        value.copy< std::shared_ptr<CallExpr> > (that.value);
        break;

      case 65: // compound_statement
        value.copy< std::shared_ptr<CompoundStmt> > (that.value);
        break;

      case 75: // const_definition
        value.copy< std::shared_ptr<ConstDecl> > (that.value);
        break;

      case 73: // for_range_init
        value.copy< std::shared_ptr<Decl> > (that.value);
        break;

      case 76: // decomposition_definition
        value.copy< std::shared_ptr<DecompositionDecl> > (that.value);
        break;

      case 48: // "double_literal"
        value.copy< std::shared_ptr<DoubleLiteral> > (that.value);
        break;

      case 80: // literal
      case 81: // primary_expression
      case 94: // expression
        value.copy< std::shared_ptr<Expr> > (that.value);
        break;

      case 72: // for_range_statement
        value.copy< std::shared_ptr<ForRangeStmt> > (that.value);
        break;

      case 70: // for_statement
        value.copy< std::shared_ptr<ForStmt> > (that.value);
        break;

      case 57: // function_definition
        value.copy< std::shared_ptr<FunctionDecl> > (that.value);
        break;

      case 58: // function_expression
        value.copy< std::shared_ptr<FunctionExpr> > (that.value);
        break;

      case 68: // if_statement
        value.copy< std::shared_ptr<IfStmt> > (that.value);
        break;

      case 47: // "integer_literal"
        value.copy< std::shared_ptr<IntegerLiteral> > (that.value);
        break;

      case 85: // map_entry
        value.copy< std::shared_ptr<MapEntry> > (that.value);
        break;

      case 84: // map_literal
        value.copy< std::shared_ptr<MapLiteral> > (that.value);
        break;

      case 87: // member_expression
        value.copy< std::shared_ptr<MemberExpr> > (that.value);
        break;

      case 46: // "identifier"
      case 60: // binding_identifier
      case 63: // type_specifier
        value.copy< std::shared_ptr<NamedDecl> > (that.value);
        break;

      case 82: // null_literal
        value.copy< std::shared_ptr<NullLiteral> > (that.value);
        break;

      case 62: // parameter_variable
        value.copy< std::shared_ptr<ParmVarDecl> > (that.value);
        break;

      case 67: // return_statement
        value.copy< std::shared_ptr<ReturnStmt> > (that.value);
        break;

      case 64: // statement
      case 71: // for_init_statement
        value.copy< std::shared_ptr<Stmt> > (that.value);
        break;

      case 50: // "string_literal"
        value.copy< std::shared_ptr<StringLiteral> > (that.value);
        break;

      case 88: // subscript_expression
        value.copy< std::shared_ptr<SubscriptExpr> > (that.value);
        break;

      case 55: // translation_unit
        value.copy< std::shared_ptr<TranslationUnitDecl> > (that.value);
        break;

      case 90: // unary_expression
        value.copy< std::shared_ptr<UnaryOperator> > (that.value);
        break;

      case 74: // variable_definition
        value.copy< std::shared_ptr<VariableDecl> > (that.value);
        break;

      case 69: // while_statement
        value.copy< std::shared_ptr<WhileStmt> > (that.value);
        break;

      case 77: // binding_declarations
        value.copy< std::vector<std::shared_ptr<BindingDecl>> > (that.value);
        break;

      case 93: // expression_list
        value.copy< std::vector<std::shared_ptr<Expr>> > (that.value);
        break;

      case 56: // function_definitions
        value.copy< std::vector<std::shared_ptr<FunctionDecl>> > (that.value);
        break;

      case 86: // map_entry_list
        value.copy< std::vector<std::shared_ptr<MapEntry>> > (that.value);
        break;

      case 61: // parameter_variables
        value.copy< std::vector<std::shared_ptr<ParmVarDecl>> > (that.value);
        break;

      case 66: // statement_list
        value.copy< std::vector<std::shared_ptr<Stmt>> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  MyParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  MyParser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  MyParser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  MyParser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  MyParser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  MyParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  MyParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  MyParser::debug_level_type
  MyParser::debug_level () const
  {
    return yydebug_;
  }

  void
  MyParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline MyParser::state_type
  MyParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  MyParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  MyParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  MyParser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 43 "Parser/MyParser.yy" // lalr1.cc:745
{
    // Initialize the initial location.
    yyla.location.begin.filename = yyla.location.end.filename = &driver.file;
}

#line 752 "Parser/MyParser.cpp" // lalr1.cc:745

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 59: // call_signature
        yylhs.value.build< CallSignature > ();
        break;

      case 83: // array_literal
        yylhs.value.build< std::shared_ptr<ArrayLiteral> > ();
        break;

      case 91: // binary_expression
      case 92: // assignment_expression
        yylhs.value.build< std::shared_ptr<BinaryOperator> > ();
        break;

      case 78: // binding_declaration
        yylhs.value.build< std::shared_ptr<BindingDecl> > ();
        break;

      case 49: // "bool_literal"
        yylhs.value.build< std::shared_ptr<BoolLiteral> > ();
        break;

      case 89: // call_expression
        yylhs.value.build< std::shared_ptr<CallExpr> > ();
        break;

      case 65: // compound_statement
        yylhs.value.build< std::shared_ptr<CompoundStmt> > ();
        break;

      case 75: // const_definition
        yylhs.value.build< std::shared_ptr<ConstDecl> > ();
        break;

      case 73: // for_range_init
        yylhs.value.build< std::shared_ptr<Decl> > ();
        break;

      case 76: // decomposition_definition
        yylhs.value.build< std::shared_ptr<DecompositionDecl> > ();
        break;

      case 48: // "double_literal"
        yylhs.value.build< std::shared_ptr<DoubleLiteral> > ();
        break;

      case 80: // literal
      case 81: // primary_expression
      case 94: // expression
        yylhs.value.build< std::shared_ptr<Expr> > ();
        break;

      case 72: // for_range_statement
        yylhs.value.build< std::shared_ptr<ForRangeStmt> > ();
        break;

      case 70: // for_statement
        yylhs.value.build< std::shared_ptr<ForStmt> > ();
        break;

      case 57: // function_definition
        yylhs.value.build< std::shared_ptr<FunctionDecl> > ();
        break;

      case 58: // function_expression
        yylhs.value.build< std::shared_ptr<FunctionExpr> > ();
        break;

      case 68: // if_statement
        yylhs.value.build< std::shared_ptr<IfStmt> > ();
        break;

      case 47: // "integer_literal"
        yylhs.value.build< std::shared_ptr<IntegerLiteral> > ();
        break;

      case 85: // map_entry
        yylhs.value.build< std::shared_ptr<MapEntry> > ();
        break;

      case 84: // map_literal
        yylhs.value.build< std::shared_ptr<MapLiteral> > ();
        break;

      case 87: // member_expression
        yylhs.value.build< std::shared_ptr<MemberExpr> > ();
        break;

      case 46: // "identifier"
      case 60: // binding_identifier
      case 63: // type_specifier
        yylhs.value.build< std::shared_ptr<NamedDecl> > ();
        break;

      case 82: // null_literal
        yylhs.value.build< std::shared_ptr<NullLiteral> > ();
        break;

      case 62: // parameter_variable
        yylhs.value.build< std::shared_ptr<ParmVarDecl> > ();
        break;

      case 67: // return_statement
        yylhs.value.build< std::shared_ptr<ReturnStmt> > ();
        break;

      case 64: // statement
      case 71: // for_init_statement
        yylhs.value.build< std::shared_ptr<Stmt> > ();
        break;

      case 50: // "string_literal"
        yylhs.value.build< std::shared_ptr<StringLiteral> > ();
        break;

      case 88: // subscript_expression
        yylhs.value.build< std::shared_ptr<SubscriptExpr> > ();
        break;

      case 55: // translation_unit
        yylhs.value.build< std::shared_ptr<TranslationUnitDecl> > ();
        break;

      case 90: // unary_expression
        yylhs.value.build< std::shared_ptr<UnaryOperator> > ();
        break;

      case 74: // variable_definition
        yylhs.value.build< std::shared_ptr<VariableDecl> > ();
        break;

      case 69: // while_statement
        yylhs.value.build< std::shared_ptr<WhileStmt> > ();
        break;

      case 77: // binding_declarations
        yylhs.value.build< std::vector<std::shared_ptr<BindingDecl>> > ();
        break;

      case 93: // expression_list
        yylhs.value.build< std::vector<std::shared_ptr<Expr>> > ();
        break;

      case 56: // function_definitions
        yylhs.value.build< std::vector<std::shared_ptr<FunctionDecl>> > ();
        break;

      case 86: // map_entry_list
        yylhs.value.build< std::vector<std::shared_ptr<MapEntry>> > ();
        break;

      case 61: // parameter_variables
        yylhs.value.build< std::vector<std::shared_ptr<ParmVarDecl>> > ();
        break;

      case 66: // statement_list
        yylhs.value.build< std::vector<std::shared_ptr<Stmt>> > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 171 "Parser/MyParser.yy" // lalr1.cc:859
    { driver.ast.translationUnit = TranslationUnitDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::vector<std::shared_ptr<FunctionDecl>> > ()); }
#line 1020 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 175 "Parser/MyParser.yy" // lalr1.cc:859
    { }
#line 1026 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 176 "Parser/MyParser.yy" // lalr1.cc:859
    { yystack_[1].value.as< std::vector<std::shared_ptr<FunctionDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<FunctionDecl> > ()); yylhs.value.as< std::vector<std::shared_ptr<FunctionDecl>> > () = std::move(yystack_[1].value.as< std::vector<std::shared_ptr<FunctionDecl>> > ()); }
#line 1032 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 180 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<FunctionDecl> > () = FunctionDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), std::get<0>(yystack_[1].value.as< CallSignature > ()), std::get<1>(yystack_[1].value.as< CallSignature > ()), yystack_[0].value.as< std::shared_ptr<CompoundStmt> > ()); }
#line 1038 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 184 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<FunctionExpr> > () = FunctionExpr::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), std::get<0>(yystack_[1].value.as< CallSignature > ()), std::get<1>(yystack_[1].value.as< CallSignature > ()), yystack_[0].value.as< std::shared_ptr<CompoundStmt> > ()); }
#line 1044 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 188 "Parser/MyParser.yy" // lalr1.cc:859
    { std::get<1>(yylhs.value.as< CallSignature > ()) = nullptr; }
#line 1050 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 189 "Parser/MyParser.yy" // lalr1.cc:859
    { std::get<1>(yylhs.value.as< CallSignature > ()) = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1056 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 190 "Parser/MyParser.yy" // lalr1.cc:859
    { std::get<0>(yylhs.value.as< CallSignature > ()) = yystack_[1].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > (); std::get<1>(yylhs.value.as< CallSignature > ()) = nullptr; }
#line 1062 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 191 "Parser/MyParser.yy" // lalr1.cc:859
    { std::get<0>(yylhs.value.as< CallSignature > ()) = yystack_[3].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > (); std::get<1>(yylhs.value.as< CallSignature > ()) = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1068 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 195 "Parser/MyParser.yy" // lalr1.cc:859
    { }
#line 1074 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 196 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NamedDecl> > () = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1080 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 200 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<ParmVarDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<ParmVarDecl> > ()); }
#line 1086 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 201 "Parser/MyParser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<ParmVarDecl> > ()); yylhs.value.as< std::vector<std::shared_ptr<ParmVarDecl>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > ()); }
#line 1092 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 205 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ParmVarDecl> > () = ParmVarDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1098 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 206 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ParmVarDecl> > () = ParmVarDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1104 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 210 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NamedDecl> > () = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1110 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 214 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<CompoundStmt> > (); }
#line 1116 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 215 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[1].value.as< std::shared_ptr<Expr> > (); }
#line 1122 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 216 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ReturnStmt> > (); }
#line 1128 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 217 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<VariableDecl> > ()); }
#line 1134 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 218 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<ConstDecl> > ()); }
#line 1140 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 219 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<DecompositionDecl> > ()); }
#line 1146 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 220 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<IfStmt> > (); }
#line 1152 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 221 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<WhileStmt> > (); }
#line 1158 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 222 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ForStmt> > (); }
#line 1164 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 223 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ForRangeStmt> > (); }
#line 1170 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 227 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CompoundStmt> > () = CompoundStmt::make(toLoc(yylhs.location), std::vector<std::shared_ptr<Stmt>>{}); }
#line 1176 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 228 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CompoundStmt> > () = CompoundStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ()); }
#line 1182 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 232 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Stmt>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1188 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 233 "Parser/MyParser.yy" // lalr1.cc:859
    { yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Stmt> > ()); yylhs.value.as< std::vector<std::shared_ptr<Stmt>> > () = std::move(yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ()); }
#line 1194 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 237 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ReturnStmt> > () = ReturnStmt::make(toLoc(yylhs.location)); }
#line 1200 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 238 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ReturnStmt> > () = ReturnStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1206 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 244 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IfStmt> > () = IfStmt::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1212 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 245 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IfStmt> > () = IfStmt::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[2].value.as< std::shared_ptr<Stmt> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1218 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 249 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<WhileStmt> > () = WhileStmt::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1224 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 253 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ForStmt> > () = ForStmt::make(toLoc(yylhs.location), yystack_[5].value.as< std::shared_ptr<Stmt> > (), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1230 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 257 "Parser/MyParser.yy" // lalr1.cc:859
    { }
#line 1236 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 258 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[1].value.as< std::shared_ptr<Expr> > (); }
#line 1242 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 259 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<VariableDecl> > ()); }
#line 1248 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 263 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ForRangeStmt> > () = ForRangeStmt::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Decl> > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1254 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 267 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1260 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 268 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1266 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 269 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = ConstDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1272 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 270 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = DecompositionDecl::make(toLoc(yylhs.location), yystack_[1].value.as< std::vector<std::shared_ptr<BindingDecl>> > ()); }
#line 1278 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 271 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = DecompositionDecl::make(toLoc(yylhs.location), yystack_[1].value.as< std::vector<std::shared_ptr<BindingDecl>> > ()); }
#line 1284 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 275 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VariableDecl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1290 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 276 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VariableDecl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1296 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 280 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ConstDecl> > () = ConstDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1302 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 281 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ConstDecl> > () = ConstDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1308 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 285 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<DecompositionDecl> > () = DecompositionDecl::make(toLoc(yylhs.location), yystack_[3].value.as< std::vector<std::shared_ptr<BindingDecl>> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1314 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 286 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<DecompositionDecl> > () = DecompositionDecl::make(toLoc(yylhs.location), yystack_[3].value.as< std::vector<std::shared_ptr<BindingDecl>> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1320 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 290 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<BindingDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<BindingDecl> > ()); }
#line 1326 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 291 "Parser/MyParser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<BindingDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<BindingDecl> > ()); yylhs.value.as< std::vector<std::shared_ptr<BindingDecl>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<BindingDecl>> > ()); }
#line 1332 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 295 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BindingDecl> > () = BindingDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1338 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 299 "Parser/MyParser.yy" // lalr1.cc:859
    { }
#line 1344 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 300 "Parser/MyParser.yy" // lalr1.cc:859
    { }
#line 1350 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 304 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<IntegerLiteral> > (); }
#line 1356 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 305 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<DoubleLiteral> > (); }
#line 1362 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 306 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<BoolLiteral> > (); }
#line 1368 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 307 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<StringLiteral> > (); }
#line 1374 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 324 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<Expr> > (); }
#line 1380 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 325 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<NullLiteral> > (); }
#line 1386 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 326 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = DeclRefExpr::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1392 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 327 "Parser/MyParser.yy" // lalr1.cc:859
    { std::swap(yylhs.value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1398 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 328 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<ArrayLiteral> > (); }
#line 1404 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 329 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<MapLiteral> > (); }
#line 1410 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 333 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullLiteral> > () = NullLiteral::make(toLoc(yylhs.location)); }
#line 1416 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 337 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ArrayLiteral> > () = ArrayLiteral::make(toLoc(yylhs.location), std::vector<std::shared_ptr<Expr>>{}); }
#line 1422 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 338 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ArrayLiteral> > () = ArrayLiteral::make(toLoc(yylhs.location), yystack_[2].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1428 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 342 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MapLiteral> > () = MapLiteral::make(toLoc(yylhs.location), std::vector<std::shared_ptr<MapEntry>>{}); }
#line 1434 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 343 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MapLiteral> > () = MapLiteral::make(toLoc(yylhs.location), yystack_[2].value.as< std::vector<std::shared_ptr<MapEntry>> > ()); }
#line 1440 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 347 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MapEntry> > () = MapEntry::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1446 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 351 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<MapEntry>> > ().push_back(yystack_[0].value.as< std::shared_ptr<MapEntry> > ()); }
#line 1452 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 352 "Parser/MyParser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<MapEntry>> > ().push_back(yystack_[0].value.as< std::shared_ptr<MapEntry> > ()); yylhs.value.as< std::vector<std::shared_ptr<MapEntry>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<MapEntry>> > ()); }
#line 1458 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 356 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MemberExpr> > () = MemberExpr::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1464 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 360 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<SubscriptExpr> > () = SubscriptExpr::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1470 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 364 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CallExpr> > () = CallExpr::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), std::vector<std::shared_ptr<Expr>>{}); }
#line 1476 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 365 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CallExpr> > () = CallExpr::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1482 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 369 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PreInc, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1488 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 370 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PreDec, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1494 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 371 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PostInc, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1500 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 372 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PostDec, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1506 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 373 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::Plus, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1512 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 374 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::Minus, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1518 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 375 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::LogicalNot, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1524 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 379 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Add, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1530 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 380 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Subtract, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1536 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 381 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Multiply, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1542 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 382 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Divide, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1548 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 383 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Mod, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1554 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 384 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Equal, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1560 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 385 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::NotEqual, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1566 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 386 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::LogicalAnd, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1572 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 387 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::LogicalOr, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1578 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 388 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::GreaterThan, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1584 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 389 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::GreaterThanOrEqual, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1590 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 390 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::LessThan, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1596 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 391 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::LessThanOrEqual, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1602 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 395 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Assign, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1608 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 399 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Expr>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1614 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 400 "Parser/MyParser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<Expr>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Expr> > ()); yylhs.value.as< std::vector<std::shared_ptr<Expr>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1620 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 404 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<Expr> > (); }
#line 1626 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 405 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<BinaryOperator> > (); }
#line 1632 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 406 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<BinaryOperator> > (); }
#line 1638 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 407 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<UnaryOperator> > (); }
#line 1644 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 408 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<CallExpr> > (); }
#line 1650 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 409 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<MemberExpr> > (); }
#line 1656 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 410 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<SubscriptExpr> > (); }
#line 1662 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 411 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<FunctionExpr> > (); }
#line 1668 "Parser/MyParser.cpp" // lalr1.cc:859
    break;


#line 1672 "Parser/MyParser.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  MyParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  MyParser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char MyParser::yypact_ninf_ = -82;

  const signed char MyParser::yytable_ninf_ = -48;

  const short int
  MyParser::yypact_[] =
  {
     -82,    12,   -26,   -82,   -33,   -82,    -9,    47,     0,    24,
      28,   -12,   -82,     3,   -82,    14,    14,    41,    53,   764,
     764,   764,   764,   764,   315,   -82,   235,    58,   263,    -2,
       1,    49,    80,    82,   -82,   -82,   -82,   -82,   -82,   -82,
     -82,   -82,   -82,    98,   -82,   -82,   -82,   -82,   -82,    77,
      78,    79,   -82,    10,   -82,   -82,   -82,   -82,   -82,   -82,
     -82,   -82,   -82,   349,   -82,   -82,   -82,    14,   -82,   -82,
     -82,   -82,   -82,   -82,   381,   -82,    86,   -82,    84,    85,
     413,   -82,    -9,   -82,   445,    73,   118,    73,   119,   315,
     315,   209,   -82,   -82,   -82,   -82,   -82,   -82,   -82,   315,
     315,   315,   315,   315,   315,   315,   315,   315,   315,   315,
     315,   315,   315,   289,   315,   -82,    83,   -82,   -82,   -82,
     315,    94,   315,   100,   315,     0,   -82,   -82,    -4,   -82,
     315,    31,   315,   477,   509,   -82,    45,    46,    87,   315,
      95,    96,   541,   701,   146,   146,   -14,   -14,   -14,   763,
     732,   794,   794,    29,    29,    29,    29,   -82,    35,   701,
     573,   -82,   -82,   413,   -82,   701,   -82,   701,   -82,   139,
      73,   701,   147,   701,   162,   162,    73,     6,    73,   -82,
     605,   315,   -82,   -82,   -82,   315,   -82,   315,   -82,   315,
     108,   -82,    36,    68,   315,   637,   701,   701,   162,   -82,
     -82,   669,   162,   -82,   162,   -82,   -82
  };

  const unsigned char
  MyParser::yydefact_[] =
  {
       3,     0,     2,     1,     0,     4,     0,     0,     0,     7,
      15,     0,    13,     0,     5,     0,     0,     9,     0,     0,
       0,     0,     0,     0,     0,    28,     0,    11,     0,     0,
       0,     0,     0,     0,    68,    64,    58,    59,    60,    61,
     110,    30,    18,     0,    20,    24,    25,    26,    27,     0,
       0,     0,    62,   103,    63,    66,    67,   108,   109,   107,
     106,   105,   104,     0,    17,     8,    16,     0,    14,    85,
      84,    80,    81,    86,     0,    69,     0,    74,    56,    56,
     101,    12,     0,    32,     0,     0,    47,     0,    49,     0,
       0,     0,    29,    31,    21,    22,    23,    82,    83,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    19,     0,    10,    65,    71,
      57,     0,    57,     0,     0,     0,    33,    55,     0,    53,
       0,     0,     0,     0,     0,    38,     0,     0,    64,     0,
       0,     0,     0,   100,    88,    87,    89,    90,    91,    94,
      95,    92,    93,    99,    97,    98,    96,    78,     0,   101,
       0,    76,    75,     0,    72,   102,    70,    73,     6,     0,
       0,    48,     0,    50,     0,     0,     0,    43,     0,    44,
       0,     0,    40,    39,    79,     0,    77,     0,    54,     0,
      34,    36,     0,     0,     0,     0,    51,    52,     0,    45,
      46,     0,     0,    35,     0,    41,    37
  };

  const short int
  MyParser::yypgoto_[] =
  {
     -82,   -82,   -82,   -82,   -82,    69,   -82,   -82,   137,   -11,
     -42,    -5,   -82,   -82,   -82,   -82,   -82,   -82,   -82,   -82,
      67,   -82,   -82,   -81,    -6,    89,   -82,   163,   -82,   -82,
     -82,    39,   -82,   -82,   -82,   -82,   -82,   -82,   -82,    56,
     -24
  };

  const short int
  MyParser::yydefgoto_[] =
  {
      -1,     1,     2,     5,    40,     8,    82,    11,    12,    65,
      41,    42,    43,    44,    45,    46,    47,   139,    48,   140,
      49,    50,    51,   128,   129,   121,    52,    53,    54,    55,
      56,    77,    78,    57,    58,    59,    60,    61,    62,    79,
      63
  };

  const short int
  MyParser::yytable_[] =
  {
      74,    93,    80,    14,    84,    66,   131,    19,    20,   130,
       4,   113,     3,     6,    17,   114,     7,    21,    22,    23,
     116,    18,   169,    85,    97,    98,    87,    13,    24,   170,
      13,    25,    26,   100,   101,   102,   103,   104,   -47,    27,
      28,    29,    30,    31,    86,    32,    33,    88,    34,    35,
      36,    37,    38,    39,   113,    15,   117,   172,   114,    16,
      64,   184,   199,   116,   170,   133,   134,   142,   185,   170,
     176,   178,    67,     9,    89,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   159,
     160,   177,   179,    10,   200,   192,   163,   193,   165,    10,
     167,   170,    19,    20,    81,    90,   171,    91,   173,    94,
      95,    96,    21,    22,    23,   180,   119,   120,   122,   127,
     168,   130,   132,    24,   164,    13,    92,    26,   182,   161,
     166,   -42,   190,   191,    27,    28,    29,    30,    31,   181,
      32,    33,   187,    34,    35,    36,    37,    38,    39,   198,
     189,   125,   102,   103,   104,    68,   203,   195,   141,   162,
     205,   165,   206,   196,   188,   197,    19,    20,   123,   158,
     201,   113,     0,     0,     0,   114,    21,    22,    23,     0,
     116,     0,    69,    70,    71,    72,    73,    24,     0,    13,
       0,    26,     0,     0,     0,     0,     0,     0,    27,    28,
      29,    30,    31,     0,    32,    33,     0,    34,    35,    36,
      37,    38,    39,    19,    20,     0,     0,     0,     0,     0,
       0,     0,     0,    21,    22,    23,     0,     0,     0,     0,
       0,     0,     0,     0,    24,     0,     0,     0,    26,    19,
      20,   135,     0,     0,     0,    27,     0,   136,   137,    21,
      22,    23,     0,     0,    34,   138,    36,    37,    38,    39,
      24,     0,     0,     0,    26,    75,    76,    19,    20,     0,
       0,    27,     0,     0,     0,     0,     0,    21,    22,    23,
      34,    35,    36,    37,    38,    39,     0,     0,    24,     0,
       0,     0,    26,    19,    20,    83,     0,     0,     0,    27,
       0,     0,     0,    21,    22,    23,     0,     0,    34,    35,
      36,    37,    38,    39,    24,   157,     0,     0,    26,    19,
      20,     0,     0,     0,     0,    27,     0,     0,     0,    21,
      22,    23,     0,     0,    34,    35,    36,    37,    38,    39,
      24,     0,     0,     0,    26,     0,     0,     0,     0,     0,
       0,    27,    99,   100,   101,   102,   103,   104,     0,     0,
      34,    35,    36,    37,    38,    39,   105,   106,   107,   108,
     109,   110,   111,   112,   113,     0,     0,     0,   114,     0,
       0,   115,     0,   116,    99,   100,   101,   102,   103,   104,
       0,     0,     0,     0,     0,     0,     0,     0,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   118,     0,     0,
     114,     0,     0,     0,     0,   116,    99,   100,   101,   102,
     103,   104,     0,     0,     0,     0,     0,     0,     0,     0,
     105,   106,   107,   108,   109,   110,   111,   112,   113,     0,
       0,     0,   114,     0,   124,     0,     0,   116,    99,   100,
     101,   102,   103,   104,     0,     0,     0,     0,     0,     0,
       0,     0,   105,   106,   107,   108,   109,   110,   111,   112,
     113,     0,     0,     0,   114,     0,     0,   126,     0,   116,
      99,   100,   101,   102,   103,   104,     0,     0,     0,     0,
       0,     0,     0,     0,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   174,     0,     0,   114,     0,     0,     0,
       0,   116,    99,   100,   101,   102,   103,   104,     0,     0,
       0,     0,     0,     0,     0,     0,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   175,     0,     0,   114,     0,
       0,     0,     0,   116,    99,   100,   101,   102,   103,   104,
       0,     0,     0,     0,     0,     0,     0,     0,   105,   106,
     107,   108,   109,   110,   111,   112,   113,     0,     0,     0,
     114,     0,     0,   183,     0,   116,    99,   100,   101,   102,
     103,   104,     0,     0,     0,     0,     0,     0,     0,     0,
     105,   106,   107,   108,   109,   110,   111,   112,   113,     0,
       0,     0,   114,   186,     0,     0,     0,   116,    99,   100,
     101,   102,   103,   104,     0,     0,     0,     0,     0,     0,
       0,     0,   105,   106,   107,   108,   109,   110,   111,   112,
     113,     0,     0,     0,   114,     0,     0,   194,     0,   116,
      99,   100,   101,   102,   103,   104,     0,     0,     0,     0,
       0,     0,     0,     0,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   202,     0,     0,   114,     0,     0,     0,
       0,   116,    99,   100,   101,   102,   103,   104,     0,     0,
       0,     0,     0,     0,     0,     0,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   204,     0,     0,   114,     0,
       0,     0,     0,   116,    99,   100,   101,   102,   103,   104,
       0,     0,     0,     0,     0,     0,     0,     0,   105,   106,
     107,   108,   109,   110,   111,   112,   113,     0,     0,     0,
     114,     0,     0,     0,     0,   116,   100,   101,   102,   103,
     104,     0,     0,     0,     0,     0,     0,     0,     0,   105,
       0,   107,   108,   109,   110,   111,   112,   113,     0,     0,
       0,   114,     0,     0,     0,     0,   116,   100,   101,   102,
     103,   104,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   107,   108,   109,   110,   111,   112,   113,    24,
       0,     0,   114,    26,     0,     0,     0,   116,   100,   101,
     102,   103,   104,     0,     0,     0,     0,     0,     0,    34,
      35,    36,    37,    38,    39,   109,   110,   111,   112,   113,
       0,     0,     0,   114,     0,     0,     0,     0,   116
  };

  const short int
  MyParser::yycheck_[] =
  {
      24,    43,    26,     8,    28,    16,    87,     4,     5,     3,
      36,    25,     0,    46,    26,    29,    25,    14,    15,    16,
      34,    33,    26,    25,    14,    15,    25,    27,    25,    33,
      27,    28,    29,     4,     5,     6,     7,     8,    32,    36,
      37,    38,    39,    40,    46,    42,    43,    46,    45,    46,
      47,    48,    49,    50,    25,    31,    67,    26,    29,    31,
      46,    26,    26,    34,    33,    89,    90,    91,    33,    33,
      25,    25,    31,    26,    25,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,    46,    46,    46,    26,   176,   120,   178,   122,    46,
     124,    33,     4,     5,    46,    25,   130,    25,   132,    32,
      32,    32,    14,    15,    16,   139,    30,    33,    33,    46,
     125,     3,     3,    25,    30,    27,    28,    29,    32,    46,
      30,    44,   174,   175,    36,    37,    38,    39,    40,    44,
      42,    43,     3,    45,    46,    47,    48,    49,    50,    41,
       3,    82,     6,     7,     8,    18,   198,   181,    91,   120,
     202,   185,   204,   187,   170,   189,     4,     5,    79,   113,
     194,    25,    -1,    -1,    -1,    29,    14,    15,    16,    -1,
      34,    -1,    19,    20,    21,    22,    23,    25,    -1,    27,
      -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,
      38,    39,    40,    -1,    42,    43,    -1,    45,    46,    47,
      48,    49,    50,     4,     5,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    14,    15,    16,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,    29,     4,
       5,    32,    -1,    -1,    -1,    36,    -1,    38,    39,    14,
      15,    16,    -1,    -1,    45,    46,    47,    48,    49,    50,
      25,    -1,    -1,    -1,    29,    30,    31,     4,     5,    -1,
      -1,    36,    -1,    -1,    -1,    -1,    -1,    14,    15,    16,
      45,    46,    47,    48,    49,    50,    -1,    -1,    25,    -1,
      -1,    -1,    29,     4,     5,    32,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    14,    15,    16,    -1,    -1,    45,    46,
      47,    48,    49,    50,    25,    26,    -1,    -1,    29,     4,
       5,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    14,
      15,    16,    -1,    -1,    45,    46,    47,    48,    49,    50,
      25,    -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    36,     3,     4,     5,     6,     7,     8,    -1,    -1,
      45,    46,    47,    48,    49,    50,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    29,    -1,
      -1,    32,    -1,    34,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    -1,    -1,
      29,    -1,    -1,    -1,    -1,    34,     3,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    29,    -1,    31,    -1,    -1,    34,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    29,    -1,    -1,    32,    -1,    34,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    -1,    29,    -1,    -1,    -1,
      -1,    34,     3,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    -1,    -1,    29,    -1,
      -1,    -1,    -1,    34,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      29,    -1,    -1,    32,    -1,    34,     3,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    29,    30,    -1,    -1,    -1,    34,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    29,    -1,    -1,    32,    -1,    34,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    -1,    29,    -1,    -1,    -1,
      -1,    34,     3,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    -1,    -1,    29,    -1,
      -1,    -1,    -1,    34,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      29,    -1,    -1,    -1,    -1,    34,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,
      -1,    19,    20,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    29,    -1,    -1,    -1,    -1,    34,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    19,    20,    21,    22,    23,    24,    25,    25,
      -1,    -1,    29,    29,    -1,    -1,    -1,    34,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,    34
  };

  const unsigned char
  MyParser::yystos_[] =
  {
       0,    55,    56,     0,    36,    57,    46,    25,    59,    26,
      46,    61,    62,    27,    65,    31,    31,    26,    33,     4,
       5,    14,    15,    16,    25,    28,    29,    36,    37,    38,
      39,    40,    42,    43,    45,    46,    47,    48,    49,    50,
      58,    64,    65,    66,    67,    68,    69,    70,    72,    74,
      75,    76,    80,    81,    82,    83,    84,    87,    88,    89,
      90,    91,    92,    94,    46,    63,    63,    31,    62,    81,
      81,    81,    81,    81,    94,    30,    31,    85,    86,    93,
      94,    46,    60,    32,    94,    25,    46,    25,    46,    25,
      25,    25,    28,    64,    32,    32,    32,    14,    15,     3,
       4,     5,     6,     7,     8,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    29,    32,    34,    63,    26,    30,
      33,    79,    33,    79,    31,    59,    32,    46,    77,    78,
       3,    77,     3,    94,    94,    32,    38,    39,    46,    71,
      73,    74,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    26,    93,    94,
      94,    46,    85,    94,    30,    94,    30,    94,    65,    26,
      33,    94,    26,    94,    26,    26,    25,    46,    25,    46,
      94,    44,    32,    32,    26,    33,    30,     3,    78,     3,
      64,    64,    77,    77,    32,    94,    94,    94,    41,    26,
      26,    94,    26,    64,    26,    64,    64
  };

  const unsigned char
  MyParser::yyr1_[] =
  {
       0,    54,    55,    56,    56,    57,    58,    59,    59,    59,
      59,    60,    60,    61,    61,    62,    62,    63,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    65,    65,
      66,    66,    67,    67,    68,    68,    69,    70,    71,    71,
      71,    72,    73,    73,    73,    73,    73,    74,    74,    75,
      75,    76,    76,    77,    77,    78,    79,    79,    80,    80,
      80,    80,    81,    81,    81,    81,    81,    81,    82,    83,
      83,    84,    84,    85,    86,    86,    87,    88,    89,    89,
      90,    90,    90,    90,    90,    90,    90,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      92,    93,    93,    94,    94,    94,    94,    94,    94,    94,
      94
  };

  const unsigned char
  MyParser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     4,     4,     2,     4,     3,
       5,     0,     1,     1,     3,     1,     3,     1,     1,     2,
       1,     2,     2,     2,     1,     1,     1,     1,     2,     3,
       1,     2,     2,     3,     5,     7,     5,     8,     1,     2,
       2,     7,     1,     2,     2,     4,     4,     2,     4,     2,
       4,     6,     6,     1,     3,     1,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     2,
       4,     3,     4,     3,     1,     3,     3,     4,     3,     4,
       2,     2,     2,     2,     2,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const MyParser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"=\"", "\"-\"", "\"+\"",
  "\"*\"", "\"/\"", "\"%\"", "\"-=\"", "\"+=\"", "\"*=\"", "\"/=\"",
  "\"%=\"", "\"++\"", "\"--\"", "\"!\"", "\"&&\"", "\"||\"", "\"==\"",
  "\"!=\"", "\"<=\"", "\">=\"", "\"<\"", "\">\"", "\"(\"", "\")\"",
  "\"{\"", "\"}\"", "\"[\"", "\"]\"", "\":\"", "\";\"", "\",\"", "\".\"",
  "\"?\"", "\"function\"", "\"return\"", "\"let\"", "\"const\"", "\"if\"",
  "\"else\"", "\"while\"", "\"for\"", "\"in\"", "\"null\"",
  "\"identifier\"", "\"integer_literal\"", "\"double_literal\"",
  "\"bool_literal\"", "\"string_literal\"", "\"then\"", "\"unary_plus\"",
  "\"unary_minus\"", "$accept", "translation_unit", "function_definitions",
  "function_definition", "function_expression", "call_signature",
  "binding_identifier", "parameter_variables", "parameter_variable",
  "type_specifier", "statement", "compound_statement", "statement_list",
  "return_statement", "if_statement", "while_statement", "for_statement",
  "for_init_statement", "for_range_statement", "for_range_init",
  "variable_definition", "const_definition", "decomposition_definition",
  "binding_declarations", "binding_declaration", "comma_opt", "literal",
  "primary_expression", "null_literal", "array_literal", "map_literal",
  "map_entry", "map_entry_list", "member_expression",
  "subscript_expression", "call_expression", "unary_expression",
  "binary_expression", "assignment_expression", "expression_list",
  "expression", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  MyParser::yyrline_[] =
  {
       0,   171,   171,   175,   176,   180,   184,   188,   189,   190,
     191,   195,   196,   200,   201,   205,   206,   210,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   227,   228,
     232,   233,   237,   238,   244,   245,   249,   253,   257,   258,
     259,   263,   267,   268,   269,   270,   271,   275,   276,   280,
     281,   285,   286,   290,   291,   295,   299,   300,   304,   305,
     306,   307,   324,   325,   326,   327,   328,   329,   333,   337,
     338,   342,   343,   347,   351,   352,   356,   360,   364,   365,
     369,   370,   371,   372,   373,   374,   375,   379,   380,   381,
     382,   383,   384,   385,   386,   387,   388,   389,   390,   391,
     395,   399,   400,   404,   405,   406,   407,   408,   409,   410,
     411
  };

  // Print the state stack on the debug stream.
  void
  MyParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  MyParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG



} // yy
#line 2320 "Parser/MyParser.cpp" // lalr1.cc:1167
#line 414 "Parser/MyParser.yy" // lalr1.cc:1168


void yy::MyParser::error(const location_type& l, const std::string& m)
{
    driver.error(toLoc(l), m);
}
