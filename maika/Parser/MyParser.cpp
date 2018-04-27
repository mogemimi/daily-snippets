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
      case 58: // call_signature
        value.move< CallSignature > (that.value);
        break;

      case 77: // array_literal
        value.move< std::shared_ptr<ArrayLiteral> > (that.value);
        break;

      case 84: // binary_expression
      case 85: // assignment_expression
        value.move< std::shared_ptr<BinaryOperator> > (that.value);
        break;

      case 48: // "bool_literal"
        value.move< std::shared_ptr<BoolLiteral> > (that.value);
        break;

      case 82: // call_expression
        value.move< std::shared_ptr<CallExpr> > (that.value);
        break;

      case 64: // compound_statement
        value.move< std::shared_ptr<CompoundStmt> > (that.value);
        break;

      case 72: // const_definition
        value.move< std::shared_ptr<ConstDecl> > (that.value);
        break;

      case 47: // "double_literal"
        value.move< std::shared_ptr<DoubleLiteral> > (that.value);
        break;

      case 74: // literal
      case 75: // primary_expression
      case 87: // expression
        value.move< std::shared_ptr<Expr> > (that.value);
        break;

      case 69: // for_statement
        value.move< std::shared_ptr<ForStmt> > (that.value);
        break;

      case 56: // function_definition
        value.move< std::shared_ptr<FunctionDecl> > (that.value);
        break;

      case 57: // function_expression
        value.move< std::shared_ptr<FunctionExpr> > (that.value);
        break;

      case 67: // if_statement
        value.move< std::shared_ptr<IfStmt> > (that.value);
        break;

      case 46: // "integer_literal"
        value.move< std::shared_ptr<IntegerLiteral> > (that.value);
        break;

      case 79: // map_entry
        value.move< std::shared_ptr<MapEntry> > (that.value);
        break;

      case 78: // map_literal
        value.move< std::shared_ptr<MapLiteral> > (that.value);
        break;

      case 81: // member_expression
        value.move< std::shared_ptr<MemberExpr> > (that.value);
        break;

      case 45: // "identifier"
      case 59: // binding_identifier
      case 62: // type_specifier
        value.move< std::shared_ptr<NamedDecl> > (that.value);
        break;

      case 76: // null_literal
        value.move< std::shared_ptr<NullLiteral> > (that.value);
        break;

      case 61: // parameter_variable
        value.move< std::shared_ptr<ParmVarDecl> > (that.value);
        break;

      case 66: // return_statement
        value.move< std::shared_ptr<ReturnStmt> > (that.value);
        break;

      case 63: // statement
      case 70: // for_init_statement
        value.move< std::shared_ptr<Stmt> > (that.value);
        break;

      case 49: // "string_literal"
        value.move< std::shared_ptr<StringLiteral> > (that.value);
        break;

      case 54: // translation_unit
        value.move< std::shared_ptr<TranslationUnitDecl> > (that.value);
        break;

      case 83: // unary_expression
        value.move< std::shared_ptr<UnaryOperator> > (that.value);
        break;

      case 71: // variable_definition
        value.move< std::shared_ptr<VariableDecl> > (that.value);
        break;

      case 68: // while_statement
        value.move< std::shared_ptr<WhileStmt> > (that.value);
        break;

      case 86: // expression_list
        value.move< std::vector<std::shared_ptr<Expr>> > (that.value);
        break;

      case 55: // function_definitions
        value.move< std::vector<std::shared_ptr<FunctionDecl>> > (that.value);
        break;

      case 80: // map_entry_list
        value.move< std::vector<std::shared_ptr<MapEntry>> > (that.value);
        break;

      case 60: // parameter_variables
        value.move< std::vector<std::shared_ptr<ParmVarDecl>> > (that.value);
        break;

      case 65: // statement_list
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
      case 58: // call_signature
        value.copy< CallSignature > (that.value);
        break;

      case 77: // array_literal
        value.copy< std::shared_ptr<ArrayLiteral> > (that.value);
        break;

      case 84: // binary_expression
      case 85: // assignment_expression
        value.copy< std::shared_ptr<BinaryOperator> > (that.value);
        break;

      case 48: // "bool_literal"
        value.copy< std::shared_ptr<BoolLiteral> > (that.value);
        break;

      case 82: // call_expression
        value.copy< std::shared_ptr<CallExpr> > (that.value);
        break;

      case 64: // compound_statement
        value.copy< std::shared_ptr<CompoundStmt> > (that.value);
        break;

      case 72: // const_definition
        value.copy< std::shared_ptr<ConstDecl> > (that.value);
        break;

      case 47: // "double_literal"
        value.copy< std::shared_ptr<DoubleLiteral> > (that.value);
        break;

      case 74: // literal
      case 75: // primary_expression
      case 87: // expression
        value.copy< std::shared_ptr<Expr> > (that.value);
        break;

      case 69: // for_statement
        value.copy< std::shared_ptr<ForStmt> > (that.value);
        break;

      case 56: // function_definition
        value.copy< std::shared_ptr<FunctionDecl> > (that.value);
        break;

      case 57: // function_expression
        value.copy< std::shared_ptr<FunctionExpr> > (that.value);
        break;

      case 67: // if_statement
        value.copy< std::shared_ptr<IfStmt> > (that.value);
        break;

      case 46: // "integer_literal"
        value.copy< std::shared_ptr<IntegerLiteral> > (that.value);
        break;

      case 79: // map_entry
        value.copy< std::shared_ptr<MapEntry> > (that.value);
        break;

      case 78: // map_literal
        value.copy< std::shared_ptr<MapLiteral> > (that.value);
        break;

      case 81: // member_expression
        value.copy< std::shared_ptr<MemberExpr> > (that.value);
        break;

      case 45: // "identifier"
      case 59: // binding_identifier
      case 62: // type_specifier
        value.copy< std::shared_ptr<NamedDecl> > (that.value);
        break;

      case 76: // null_literal
        value.copy< std::shared_ptr<NullLiteral> > (that.value);
        break;

      case 61: // parameter_variable
        value.copy< std::shared_ptr<ParmVarDecl> > (that.value);
        break;

      case 66: // return_statement
        value.copy< std::shared_ptr<ReturnStmt> > (that.value);
        break;

      case 63: // statement
      case 70: // for_init_statement
        value.copy< std::shared_ptr<Stmt> > (that.value);
        break;

      case 49: // "string_literal"
        value.copy< std::shared_ptr<StringLiteral> > (that.value);
        break;

      case 54: // translation_unit
        value.copy< std::shared_ptr<TranslationUnitDecl> > (that.value);
        break;

      case 83: // unary_expression
        value.copy< std::shared_ptr<UnaryOperator> > (that.value);
        break;

      case 71: // variable_definition
        value.copy< std::shared_ptr<VariableDecl> > (that.value);
        break;

      case 68: // while_statement
        value.copy< std::shared_ptr<WhileStmt> > (that.value);
        break;

      case 86: // expression_list
        value.copy< std::vector<std::shared_ptr<Expr>> > (that.value);
        break;

      case 55: // function_definitions
        value.copy< std::vector<std::shared_ptr<FunctionDecl>> > (that.value);
        break;

      case 80: // map_entry_list
        value.copy< std::vector<std::shared_ptr<MapEntry>> > (that.value);
        break;

      case 60: // parameter_variables
        value.copy< std::vector<std::shared_ptr<ParmVarDecl>> > (that.value);
        break;

      case 65: // statement_list
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

#line 704 "Parser/MyParser.cpp" // lalr1.cc:745

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
      case 58: // call_signature
        yylhs.value.build< CallSignature > ();
        break;

      case 77: // array_literal
        yylhs.value.build< std::shared_ptr<ArrayLiteral> > ();
        break;

      case 84: // binary_expression
      case 85: // assignment_expression
        yylhs.value.build< std::shared_ptr<BinaryOperator> > ();
        break;

      case 48: // "bool_literal"
        yylhs.value.build< std::shared_ptr<BoolLiteral> > ();
        break;

      case 82: // call_expression
        yylhs.value.build< std::shared_ptr<CallExpr> > ();
        break;

      case 64: // compound_statement
        yylhs.value.build< std::shared_ptr<CompoundStmt> > ();
        break;

      case 72: // const_definition
        yylhs.value.build< std::shared_ptr<ConstDecl> > ();
        break;

      case 47: // "double_literal"
        yylhs.value.build< std::shared_ptr<DoubleLiteral> > ();
        break;

      case 74: // literal
      case 75: // primary_expression
      case 87: // expression
        yylhs.value.build< std::shared_ptr<Expr> > ();
        break;

      case 69: // for_statement
        yylhs.value.build< std::shared_ptr<ForStmt> > ();
        break;

      case 56: // function_definition
        yylhs.value.build< std::shared_ptr<FunctionDecl> > ();
        break;

      case 57: // function_expression
        yylhs.value.build< std::shared_ptr<FunctionExpr> > ();
        break;

      case 67: // if_statement
        yylhs.value.build< std::shared_ptr<IfStmt> > ();
        break;

      case 46: // "integer_literal"
        yylhs.value.build< std::shared_ptr<IntegerLiteral> > ();
        break;

      case 79: // map_entry
        yylhs.value.build< std::shared_ptr<MapEntry> > ();
        break;

      case 78: // map_literal
        yylhs.value.build< std::shared_ptr<MapLiteral> > ();
        break;

      case 81: // member_expression
        yylhs.value.build< std::shared_ptr<MemberExpr> > ();
        break;

      case 45: // "identifier"
      case 59: // binding_identifier
      case 62: // type_specifier
        yylhs.value.build< std::shared_ptr<NamedDecl> > ();
        break;

      case 76: // null_literal
        yylhs.value.build< std::shared_ptr<NullLiteral> > ();
        break;

      case 61: // parameter_variable
        yylhs.value.build< std::shared_ptr<ParmVarDecl> > ();
        break;

      case 66: // return_statement
        yylhs.value.build< std::shared_ptr<ReturnStmt> > ();
        break;

      case 63: // statement
      case 70: // for_init_statement
        yylhs.value.build< std::shared_ptr<Stmt> > ();
        break;

      case 49: // "string_literal"
        yylhs.value.build< std::shared_ptr<StringLiteral> > ();
        break;

      case 54: // translation_unit
        yylhs.value.build< std::shared_ptr<TranslationUnitDecl> > ();
        break;

      case 83: // unary_expression
        yylhs.value.build< std::shared_ptr<UnaryOperator> > ();
        break;

      case 71: // variable_definition
        yylhs.value.build< std::shared_ptr<VariableDecl> > ();
        break;

      case 68: // while_statement
        yylhs.value.build< std::shared_ptr<WhileStmt> > ();
        break;

      case 86: // expression_list
        yylhs.value.build< std::vector<std::shared_ptr<Expr>> > ();
        break;

      case 55: // function_definitions
        yylhs.value.build< std::vector<std::shared_ptr<FunctionDecl>> > ();
        break;

      case 80: // map_entry_list
        yylhs.value.build< std::vector<std::shared_ptr<MapEntry>> > ();
        break;

      case 60: // parameter_variables
        yylhs.value.build< std::vector<std::shared_ptr<ParmVarDecl>> > ();
        break;

      case 65: // statement_list
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
#line 164 "Parser/MyParser.yy" // lalr1.cc:859
    { driver.ast.translationUnit = TranslationUnitDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::vector<std::shared_ptr<FunctionDecl>> > ()); }
#line 948 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 168 "Parser/MyParser.yy" // lalr1.cc:859
    { }
#line 954 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 169 "Parser/MyParser.yy" // lalr1.cc:859
    { yystack_[1].value.as< std::vector<std::shared_ptr<FunctionDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<FunctionDecl> > ()); yylhs.value.as< std::vector<std::shared_ptr<FunctionDecl>> > () = std::move(yystack_[1].value.as< std::vector<std::shared_ptr<FunctionDecl>> > ()); }
#line 960 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 173 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<FunctionDecl> > () = FunctionDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), std::get<0>(yystack_[1].value.as< CallSignature > ()), std::get<1>(yystack_[1].value.as< CallSignature > ()), yystack_[0].value.as< std::shared_ptr<CompoundStmt> > ()); }
#line 966 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 177 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<FunctionExpr> > () = FunctionExpr::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), std::get<0>(yystack_[1].value.as< CallSignature > ()), std::get<1>(yystack_[1].value.as< CallSignature > ()), yystack_[0].value.as< std::shared_ptr<CompoundStmt> > ()); }
#line 972 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 181 "Parser/MyParser.yy" // lalr1.cc:859
    { std::get<1>(yylhs.value.as< CallSignature > ()) = nullptr; }
#line 978 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 182 "Parser/MyParser.yy" // lalr1.cc:859
    { std::get<1>(yylhs.value.as< CallSignature > ()) = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 984 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 183 "Parser/MyParser.yy" // lalr1.cc:859
    { std::get<0>(yylhs.value.as< CallSignature > ()) = yystack_[1].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > (); std::get<1>(yylhs.value.as< CallSignature > ()) = nullptr; }
#line 990 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 184 "Parser/MyParser.yy" // lalr1.cc:859
    { std::get<0>(yylhs.value.as< CallSignature > ()) = yystack_[3].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > (); std::get<1>(yylhs.value.as< CallSignature > ()) = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 996 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 188 "Parser/MyParser.yy" // lalr1.cc:859
    { }
#line 1002 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 189 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NamedDecl> > () = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1008 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 193 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<ParmVarDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<ParmVarDecl> > ()); }
#line 1014 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 194 "Parser/MyParser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<ParmVarDecl> > ()); yylhs.value.as< std::vector<std::shared_ptr<ParmVarDecl>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > ()); }
#line 1020 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 198 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ParmVarDecl> > () = ParmVarDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1026 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 199 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ParmVarDecl> > () = ParmVarDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1032 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 203 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NamedDecl> > () = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1038 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 207 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<CompoundStmt> > (); }
#line 1044 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 208 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[1].value.as< std::shared_ptr<Expr> > (); }
#line 1050 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 209 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ReturnStmt> > (); }
#line 1056 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 210 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<VariableDecl> > ()); }
#line 1062 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 211 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<ConstDecl> > ()); }
#line 1068 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 212 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<IfStmt> > (); }
#line 1074 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 213 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<WhileStmt> > (); }
#line 1080 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 214 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ForStmt> > (); }
#line 1086 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 218 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CompoundStmt> > () = CompoundStmt::make(toLoc(yylhs.location), std::vector<std::shared_ptr<Stmt>>{}); }
#line 1092 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 219 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CompoundStmt> > () = CompoundStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ()); }
#line 1098 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 223 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Stmt>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1104 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 224 "Parser/MyParser.yy" // lalr1.cc:859
    { yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Stmt> > ()); yylhs.value.as< std::vector<std::shared_ptr<Stmt>> > () = std::move(yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ()); }
#line 1110 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 228 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ReturnStmt> > () = ReturnStmt::make(toLoc(yylhs.location)); }
#line 1116 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 229 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ReturnStmt> > () = ReturnStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1122 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 235 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IfStmt> > () = IfStmt::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1128 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 236 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IfStmt> > () = IfStmt::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[2].value.as< std::shared_ptr<Stmt> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1134 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 240 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<WhileStmt> > () = WhileStmt::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1140 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 244 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ForStmt> > () = ForStmt::make(toLoc(yylhs.location), yystack_[5].value.as< std::shared_ptr<Stmt> > (), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1146 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 248 "Parser/MyParser.yy" // lalr1.cc:859
    { }
#line 1152 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 249 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[1].value.as< std::shared_ptr<Expr> > (); }
#line 1158 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 250 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<VariableDecl> > ()); }
#line 1164 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 254 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VariableDecl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1170 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 255 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VariableDecl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1176 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 259 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ConstDecl> > () = ConstDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1182 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 260 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ConstDecl> > () = ConstDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1188 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 264 "Parser/MyParser.yy" // lalr1.cc:859
    { }
#line 1194 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 265 "Parser/MyParser.yy" // lalr1.cc:859
    { }
#line 1200 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 269 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<IntegerLiteral> > (); }
#line 1206 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 270 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<DoubleLiteral> > (); }
#line 1212 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 271 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<BoolLiteral> > (); }
#line 1218 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 272 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<StringLiteral> > (); }
#line 1224 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 289 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<Expr> > (); }
#line 1230 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 290 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<NullLiteral> > (); }
#line 1236 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 291 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = DeclRefExpr::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1242 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 292 "Parser/MyParser.yy" // lalr1.cc:859
    { std::swap(yylhs.value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1248 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 293 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<ArrayLiteral> > (); }
#line 1254 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 294 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<MapLiteral> > (); }
#line 1260 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 298 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullLiteral> > () = NullLiteral::make(toLoc(yylhs.location)); }
#line 1266 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 302 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ArrayLiteral> > () = ArrayLiteral::make(toLoc(yylhs.location), std::vector<std::shared_ptr<Expr>>{}); }
#line 1272 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 303 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ArrayLiteral> > () = ArrayLiteral::make(toLoc(yylhs.location), yystack_[2].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1278 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 307 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MapLiteral> > () = MapLiteral::make(toLoc(yylhs.location), yystack_[2].value.as< std::vector<std::shared_ptr<MapEntry>> > ()); }
#line 1284 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 311 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MapEntry> > () = MapEntry::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1290 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 315 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<MapEntry>> > ().push_back(yystack_[0].value.as< std::shared_ptr<MapEntry> > ()); }
#line 1296 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 316 "Parser/MyParser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<MapEntry>> > ().push_back(yystack_[0].value.as< std::shared_ptr<MapEntry> > ()); yylhs.value.as< std::vector<std::shared_ptr<MapEntry>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<MapEntry>> > ()); }
#line 1302 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 320 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MemberExpr> > () = MemberExpr::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1308 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 324 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CallExpr> > () = CallExpr::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), std::vector<std::shared_ptr<Expr>>{}); }
#line 1314 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 325 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CallExpr> > () = CallExpr::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1320 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 329 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PreInc, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1326 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 330 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PreDec, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1332 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 331 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PostInc, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1338 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 332 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PostDec, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1344 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 333 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::Plus, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1350 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 334 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::Minus, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1356 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 335 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::LogicalNot, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1362 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 339 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Add, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1368 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 340 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Subtract, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1374 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 341 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Multiply, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1380 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 342 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Divide, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1386 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 343 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Mod, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1392 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 344 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Equal, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1398 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 345 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::NotEqual, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1404 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 346 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::LogicalAnd, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1410 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 347 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::LogicalOr, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1416 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 348 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::GreaterThan, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1422 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 349 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::GreaterThanOrEqual, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1428 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 350 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::LessThan, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1434 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 351 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::LessThanOrEqual, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1440 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 355 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Assign, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1446 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 359 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Expr>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1452 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 360 "Parser/MyParser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<Expr>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Expr> > ()); yylhs.value.as< std::vector<std::shared_ptr<Expr>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1458 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 364 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<Expr> > (); }
#line 1464 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 365 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<BinaryOperator> > (); }
#line 1470 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 366 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<BinaryOperator> > (); }
#line 1476 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 367 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<UnaryOperator> > (); }
#line 1482 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 368 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<CallExpr> > (); }
#line 1488 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 369 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<MemberExpr> > (); }
#line 1494 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 370 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<FunctionExpr> > (); }
#line 1500 "Parser/MyParser.cpp" // lalr1.cc:859
    break;


#line 1504 "Parser/MyParser.cpp" // lalr1.cc:859
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


  const signed char MyParser::yypact_ninf_ = -43;

  const signed char MyParser::yytable_ninf_ = -1;

  const short int
  MyParser::yypact_[] =
  {
     -43,    20,   -10,   -43,   -16,   -43,    10,   -15,    11,    14,
      16,   -12,   -43,   103,   -43,    -4,    -4,    18,     3,   616,
     616,   616,   616,   616,   299,   -43,   241,     5,   247,    13,
      22,    58,    59,    60,   -43,   -43,   -43,   -43,   -43,   -43,
     -43,   -43,   -43,   149,   -43,   -43,   -43,   -43,     7,    54,
     -43,    17,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,
     346,   -43,   -43,   -43,    -4,   -43,   -43,   -43,   -43,   -43,
     -43,   369,   -43,   -43,    55,    57,   393,   -43,    10,   -43,
     425,    39,    89,   299,   299,     8,   -43,   -43,   -43,   -43,
     -43,   -43,   299,   299,   299,   299,   299,   299,   299,   299,
     299,   299,   299,   299,   299,   299,   293,   -43,    48,   -43,
     -43,   299,    66,   299,    67,   299,    11,   -43,   299,   299,
     448,   472,   -43,   299,    68,   496,   566,     9,     9,    -6,
      -6,    -6,   610,   588,   632,   632,     2,     2,     2,     2,
     -43,    -8,   566,   -43,   -43,   393,   -43,   566,   -43,   566,
     -43,   566,   566,   195,   195,   519,   -43,   -43,   -43,   299,
      61,   -43,   299,   195,   542,   -43,   195,   -43
  };

  const unsigned char
  MyParser::yydefact_[] =
  {
       3,     0,     2,     1,     0,     4,     0,     0,     0,     7,
      15,     0,    13,     0,     5,     0,     0,     9,     0,     0,
       0,     0,     0,     0,     0,    26,     0,    11,     0,     0,
       0,     0,     0,     0,    55,    51,    45,    46,    47,    48,
      94,    28,    18,     0,    20,    23,    24,    25,     0,     0,
      49,    88,    50,    53,    54,    93,    92,    91,    90,    89,
       0,    17,     8,    16,     0,    14,    70,    69,    65,    66,
      71,     0,    56,    60,    43,    43,    86,    12,     0,    30,
       0,    39,    41,     0,     0,     0,    27,    29,    21,    22,
      67,    68,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    19,     0,    10,
      52,    44,     0,    44,     0,     0,     0,    31,     0,     0,
       0,     0,    36,     0,     0,     0,    85,    73,    72,    74,
      75,    76,    79,    80,    77,    78,    84,    82,    83,    81,
      63,     0,    86,    62,    61,     0,    58,    87,    57,    59,
       6,    40,    42,     0,     0,     0,    38,    37,    64,     0,
      32,    34,     0,     0,     0,    33,     0,    35
  };

  const signed char
  MyParser::yypgoto_[] =
  {
     -43,   -43,   -43,   -43,   -43,    23,   -43,   -43,    80,   -13,
     -42,    -3,   -43,   -43,   -43,   -43,   -43,   -43,    19,   -43,
      28,   -43,    43,   -43,   -43,   -43,    -5,   -43,   -43,   -43,
     -43,   -43,   -43,    -1,   -24
  };

  const signed char
  MyParser::yydefgoto_[] =
  {
      -1,     1,     2,     5,    40,     8,    78,    11,    12,    62,
      41,    42,    43,    44,    45,    46,    47,   123,    48,    49,
     112,    50,    51,    52,    53,    54,    73,    74,    55,    56,
      57,    58,    59,    75,    60
  };

  const unsigned char
  MyParser::yytable_[] =
  {
      71,    87,    76,    63,    80,    14,    93,    94,    95,    96,
      97,     9,    19,    20,    17,    95,    96,    97,   158,   106,
       3,    18,    21,    22,    23,   159,     4,   106,   108,     6,
      10,    90,    91,    24,   106,     7,   108,    26,    13,    88,
     122,    61,   118,   108,    27,    15,    29,    16,    10,    64,
      77,   109,    34,    35,    36,    37,    38,    39,    81,   120,
     121,   125,    66,    67,    68,    69,    70,    82,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   142,    83,    84,    85,    89,   145,   111,   147,
     113,   149,   119,   143,   151,   152,   146,   148,    65,   155,
     156,   116,   163,   114,   124,   141,   144,    19,    20,     0,
       0,   160,   161,   150,     0,     0,     0,    21,    22,    23,
       0,   165,     0,     0,   167,     0,     0,     0,    24,     0,
      13,    25,    26,     0,     0,   147,     0,     0,   164,    27,
      28,    29,    30,    31,     0,    32,    33,    34,    35,    36,
      37,    38,    39,    19,    20,     0,     0,     0,     0,     0,
       0,     0,     0,    21,    22,    23,     0,     0,     0,     0,
       0,     0,     0,     0,    24,     0,    13,    86,    26,     0,
       0,     0,     0,     0,     0,    27,    28,    29,    30,    31,
       0,    32,    33,    34,    35,    36,    37,    38,    39,    19,
      20,     0,     0,     0,     0,     0,     0,     0,     0,    21,
      22,    23,     0,     0,     0,     0,     0,     0,     0,     0,
      24,     0,    13,     0,    26,     0,     0,     0,     0,     0,
       0,    27,    28,    29,    30,    31,     0,    32,    33,    34,
      35,    36,    37,    38,    39,    19,    20,     0,     0,     0,
       0,    19,    20,     0,     0,    21,    22,    23,     0,     0,
       0,    21,    22,    23,     0,     0,    24,     0,     0,     0,
      26,    72,    24,     0,     0,     0,    26,    27,     0,    79,
       0,     0,     0,    27,     0,    34,    35,    36,    37,    38,
      39,    34,    35,    36,    37,    38,    39,    19,    20,     0,
       0,     0,     0,    19,    20,     0,     0,    21,    22,    23,
       0,     0,     0,    21,    22,    23,     0,     0,    24,   140,
       0,     0,    26,     0,    24,     0,     0,     0,    26,    27,
       0,     0,     0,     0,     0,    27,     0,    34,    35,    36,
      37,    38,    39,    34,    35,    36,    37,    38,    39,    92,
      93,    94,    95,    96,    97,     0,     0,     0,     0,     0,
       0,     0,     0,    98,    99,   100,   101,   102,   103,   104,
     105,   106,    92,    93,    94,    95,    96,    97,   107,     0,
     108,     0,     0,     0,     0,     0,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   110,    92,    93,    94,    95,
      96,    97,     0,   108,     0,     0,     0,     0,     0,     0,
      98,    99,   100,   101,   102,   103,   104,   105,   106,     0,
       0,     0,     0,     0,   115,     0,     0,   108,    92,    93,
      94,    95,    96,    97,     0,     0,     0,     0,     0,     0,
       0,     0,    98,    99,   100,   101,   102,   103,   104,   105,
     106,    92,    93,    94,    95,    96,    97,   117,     0,   108,
       0,     0,     0,     0,     0,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   153,    92,    93,    94,    95,    96,
      97,     0,   108,     0,     0,     0,     0,     0,     0,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   154,    92,
      93,    94,    95,    96,    97,     0,   108,     0,     0,     0,
       0,     0,     0,    98,    99,   100,   101,   102,   103,   104,
     105,   106,    92,    93,    94,    95,    96,    97,   157,     0,
     108,     0,     0,     0,     0,     0,    98,    99,   100,   101,
     102,   103,   104,   105,   106,    92,    93,    94,    95,    96,
      97,   162,     0,   108,     0,     0,     0,     0,     0,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   166,    92,
      93,    94,    95,    96,    97,     0,   108,     0,     0,     0,
       0,     0,     0,    98,    99,   100,   101,   102,   103,   104,
     105,   106,    93,    94,    95,    96,    97,     0,     0,     0,
     108,     0,     0,     0,     0,    98,     0,   100,   101,   102,
     103,   104,   105,   106,    93,    94,    95,    96,    97,     0,
       0,     0,   108,     0,     0,     0,     0,     0,     0,   100,
     101,   102,   103,   104,   105,   106,    93,    94,    95,    96,
      97,    24,     0,     0,   108,    26,     0,     0,     0,     0,
       0,     0,     0,   102,   103,   104,   105,   106,     0,     0,
      34,    35,    36,    37,    38,    39,   108
  };

  const short int
  MyParser::yycheck_[] =
  {
      24,    43,    26,    16,    28,     8,     4,     5,     6,     7,
       8,    26,     4,     5,    26,     6,     7,     8,    26,    25,
       0,    33,    14,    15,    16,    33,    36,    25,    34,    45,
      45,    14,    15,    25,    25,    25,    34,    29,    27,    32,
      32,    45,     3,    34,    36,    31,    38,    31,    45,    31,
      45,    64,    44,    45,    46,    47,    48,    49,    45,    83,
      84,    85,    19,    20,    21,    22,    23,    45,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,    25,    25,    25,    32,   111,    33,   113,
      33,   115,     3,    45,   118,   119,    30,    30,    18,   123,
      32,    78,    41,    75,    85,   106,   111,     4,     5,    -1,
      -1,   153,   154,   116,    -1,    -1,    -1,    14,    15,    16,
      -1,   163,    -1,    -1,   166,    -1,    -1,    -1,    25,    -1,
      27,    28,    29,    -1,    -1,   159,    -1,    -1,   162,    36,
      37,    38,    39,    40,    -1,    42,    43,    44,    45,    46,
      47,    48,    49,     4,     5,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    14,    15,    16,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    25,    -1,    27,    28,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    37,    38,    39,    40,
      -1,    42,    43,    44,    45,    46,    47,    48,    49,     4,
       5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    14,
      15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    27,    -1,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    37,    38,    39,    40,    -1,    42,    43,    44,
      45,    46,    47,    48,    49,     4,     5,    -1,    -1,    -1,
      -1,     4,     5,    -1,    -1,    14,    15,    16,    -1,    -1,
      -1,    14,    15,    16,    -1,    -1,    25,    -1,    -1,    -1,
      29,    30,    25,    -1,    -1,    -1,    29,    36,    -1,    32,
      -1,    -1,    -1,    36,    -1,    44,    45,    46,    47,    48,
      49,    44,    45,    46,    47,    48,    49,     4,     5,    -1,
      -1,    -1,    -1,     4,     5,    -1,    -1,    14,    15,    16,
      -1,    -1,    -1,    14,    15,    16,    -1,    -1,    25,    26,
      -1,    -1,    29,    -1,    25,    -1,    -1,    -1,    29,    36,
      -1,    -1,    -1,    -1,    -1,    36,    -1,    44,    45,    46,
      47,    48,    49,    44,    45,    46,    47,    48,    49,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    17,    18,    19,    20,    21,    22,    23,
      24,    25,     3,     4,     5,     6,     7,     8,    32,    -1,
      34,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,     3,     4,     5,     6,
       7,     8,    -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    31,    -1,    -1,    34,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,     3,     4,     5,     6,     7,     8,    32,    -1,    34,
      -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,     3,     4,     5,     6,     7,
       8,    -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,     3,
       4,     5,     6,     7,     8,    -1,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    17,    18,    19,    20,    21,    22,    23,
      24,    25,     3,     4,     5,     6,     7,     8,    32,    -1,
      34,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,    25,     3,     4,     5,     6,     7,
       8,    32,    -1,    34,    -1,    -1,    -1,    -1,    -1,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,     3,
       4,     5,     6,     7,     8,    -1,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    17,    18,    19,    20,    21,    22,    23,
      24,    25,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      34,    -1,    -1,    -1,    -1,    17,    -1,    19,    20,    21,
      22,    23,    24,    25,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,    19,
      20,    21,    22,    23,    24,    25,     4,     5,     6,     7,
       8,    25,    -1,    -1,    34,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      44,    45,    46,    47,    48,    49,    34
  };

  const unsigned char
  MyParser::yystos_[] =
  {
       0,    54,    55,     0,    36,    56,    45,    25,    58,    26,
      45,    60,    61,    27,    64,    31,    31,    26,    33,     4,
       5,    14,    15,    16,    25,    28,    29,    36,    37,    38,
      39,    40,    42,    43,    44,    45,    46,    47,    48,    49,
      57,    63,    64,    65,    66,    67,    68,    69,    71,    72,
      74,    75,    76,    77,    78,    81,    82,    83,    84,    85,
      87,    45,    62,    62,    31,    61,    75,    75,    75,    75,
      75,    87,    30,    79,    80,    86,    87,    45,    59,    32,
      87,    45,    45,    25,    25,    25,    28,    63,    32,    32,
      14,    15,     3,     4,     5,     6,     7,     8,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    32,    34,    62,
      26,    33,    73,    33,    73,    31,    58,    32,     3,     3,
      87,    87,    32,    70,    71,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      26,    86,    87,    45,    79,    87,    30,    87,    30,    87,
      64,    87,    87,    26,    26,    87,    32,    32,    26,    33,
      63,    63,    32,    41,    87,    63,    26,    63
  };

  const unsigned char
  MyParser::yyr1_[] =
  {
       0,    53,    54,    55,    55,    56,    57,    58,    58,    58,
      58,    59,    59,    60,    60,    61,    61,    62,    63,    63,
      63,    63,    63,    63,    63,    63,    64,    64,    65,    65,
      66,    66,    67,    67,    68,    69,    70,    70,    70,    71,
      71,    72,    72,    73,    73,    74,    74,    74,    74,    75,
      75,    75,    75,    75,    75,    76,    77,    77,    78,    79,
      80,    80,    81,    82,    82,    83,    83,    83,    83,    83,
      83,    83,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    85,    86,    86,    87,    87,
      87,    87,    87,    87,    87
  };

  const unsigned char
  MyParser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     4,     4,     2,     4,     3,
       5,     0,     1,     1,     3,     1,     3,     1,     1,     2,
       1,     2,     2,     1,     1,     1,     2,     3,     1,     2,
       2,     3,     5,     7,     5,     8,     1,     2,     2,     2,
       4,     2,     4,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     2,     4,     4,     3,
       1,     3,     3,     3,     4,     2,     2,     2,     2,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     3,     1,     1,
       1,     1,     1,     1,     1
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
  "\"else\"", "\"while\"", "\"for\"", "\"null\"", "\"identifier\"",
  "\"integer_literal\"", "\"double_literal\"", "\"bool_literal\"",
  "\"string_literal\"", "\"then\"", "\"unary_plus\"", "\"unary_minus\"",
  "$accept", "translation_unit", "function_definitions",
  "function_definition", "function_expression", "call_signature",
  "binding_identifier", "parameter_variables", "parameter_variable",
  "type_specifier", "statement", "compound_statement", "statement_list",
  "return_statement", "if_statement", "while_statement", "for_statement",
  "for_init_statement", "variable_definition", "const_definition",
  "comma_opt", "literal", "primary_expression", "null_literal",
  "array_literal", "map_literal", "map_entry", "map_entry_list",
  "member_expression", "call_expression", "unary_expression",
  "binary_expression", "assignment_expression", "expression_list",
  "expression", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  MyParser::yyrline_[] =
  {
       0,   164,   164,   168,   169,   173,   177,   181,   182,   183,
     184,   188,   189,   193,   194,   198,   199,   203,   207,   208,
     209,   210,   211,   212,   213,   214,   218,   219,   223,   224,
     228,   229,   235,   236,   240,   244,   248,   249,   250,   254,
     255,   259,   260,   264,   265,   269,   270,   271,   272,   289,
     290,   291,   292,   293,   294,   298,   302,   303,   307,   311,
     315,   316,   320,   324,   325,   329,   330,   331,   332,   333,
     334,   335,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   355,   359,   360,   364,   365,
     366,   367,   368,   369,   370
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
#line 2098 "Parser/MyParser.cpp" // lalr1.cc:1167
#line 373 "Parser/MyParser.yy" // lalr1.cc:1168


void yy::MyParser::error(const location_type& l, const std::string& m)
{
    driver.error(toLoc(l), m);
}
