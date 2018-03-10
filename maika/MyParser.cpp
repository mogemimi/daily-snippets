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

#line 37 "MyParser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "MyParser.h"

// User implementation prologue.

#line 51 "MyParser.cpp" // lalr1.cc:412
// Unqualified %code blocks.
#line 35 "MyParser.yy" // lalr1.cc:413

#include "MyDriver.h"

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
} // end of anonymous namespace 

#line 69 "MyParser.cpp" // lalr1.cc:413


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
#line 155 "MyParser.cpp" // lalr1.cc:479

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
      case 46: // "bool_literal"
        value.move< std::shared_ptr<BoolLiteral> > (that.value);
        break;

      case 68: // call_expression
        value.move< std::shared_ptr<CallExpr> > (that.value);
        break;

      case 56: // compound_statement
        value.move< std::shared_ptr<CompoundStmt> > (that.value);
        break;

      case 45: // "double_literal"
        value.move< std::shared_ptr<DoubleLiteral> > (that.value);
        break;

      case 64: // literal
      case 65: // primary_expression
      case 70: // expression
        value.move< std::shared_ptr<Expr> > (that.value);
        break;

      case 61: // for_statement
        value.move< std::shared_ptr<ForStmt> > (that.value);
        break;

      case 52: // function_definition
        value.move< std::shared_ptr<FunctionDecl> > (that.value);
        break;

      case 59: // if_statement
        value.move< std::shared_ptr<IfStmt> > (that.value);
        break;

      case 44: // "integer_literal"
        value.move< std::shared_ptr<IntegerLiteral> > (that.value);
        break;

      case 67: // member_expression
        value.move< std::shared_ptr<MemberExpr> > (that.value);
        break;

      case 43: // "identifier"
        value.move< std::shared_ptr<NamedDecl> > (that.value);
        break;

      case 54: // parameter_variable
        value.move< std::shared_ptr<ParmVarDecl> > (that.value);
        break;

      case 58: // return_statement
        value.move< std::shared_ptr<ReturnStmt> > (that.value);
        break;

      case 55: // statement
      case 62: // for_init_statement
        value.move< std::shared_ptr<Stmt> > (that.value);
        break;

      case 47: // "string_literal"
        value.move< std::shared_ptr<StringLiteral> > (that.value);
        break;

      case 50: // translation_unit
        value.move< std::shared_ptr<TranslationUnitDecl> > (that.value);
        break;

      case 66: // unary_expression
        value.move< std::shared_ptr<UnaryOperator> > (that.value);
        break;

      case 63: // variable_definition
        value.move< std::shared_ptr<VariableDecl> > (that.value);
        break;

      case 60: // while_statement
        value.move< std::shared_ptr<WhileStmt> > (that.value);
        break;

      case 69: // expression_list
        value.move< std::vector<std::shared_ptr<Expr>> > (that.value);
        break;

      case 51: // function_definitions
        value.move< std::vector<std::shared_ptr<FunctionDecl>> > (that.value);
        break;

      case 53: // parameter_variables
        value.move< std::vector<std::shared_ptr<ParmVarDecl>> > (that.value);
        break;

      case 57: // statement_list
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
      case 46: // "bool_literal"
        value.copy< std::shared_ptr<BoolLiteral> > (that.value);
        break;

      case 68: // call_expression
        value.copy< std::shared_ptr<CallExpr> > (that.value);
        break;

      case 56: // compound_statement
        value.copy< std::shared_ptr<CompoundStmt> > (that.value);
        break;

      case 45: // "double_literal"
        value.copy< std::shared_ptr<DoubleLiteral> > (that.value);
        break;

      case 64: // literal
      case 65: // primary_expression
      case 70: // expression
        value.copy< std::shared_ptr<Expr> > (that.value);
        break;

      case 61: // for_statement
        value.copy< std::shared_ptr<ForStmt> > (that.value);
        break;

      case 52: // function_definition
        value.copy< std::shared_ptr<FunctionDecl> > (that.value);
        break;

      case 59: // if_statement
        value.copy< std::shared_ptr<IfStmt> > (that.value);
        break;

      case 44: // "integer_literal"
        value.copy< std::shared_ptr<IntegerLiteral> > (that.value);
        break;

      case 67: // member_expression
        value.copy< std::shared_ptr<MemberExpr> > (that.value);
        break;

      case 43: // "identifier"
        value.copy< std::shared_ptr<NamedDecl> > (that.value);
        break;

      case 54: // parameter_variable
        value.copy< std::shared_ptr<ParmVarDecl> > (that.value);
        break;

      case 58: // return_statement
        value.copy< std::shared_ptr<ReturnStmt> > (that.value);
        break;

      case 55: // statement
      case 62: // for_init_statement
        value.copy< std::shared_ptr<Stmt> > (that.value);
        break;

      case 47: // "string_literal"
        value.copy< std::shared_ptr<StringLiteral> > (that.value);
        break;

      case 50: // translation_unit
        value.copy< std::shared_ptr<TranslationUnitDecl> > (that.value);
        break;

      case 66: // unary_expression
        value.copy< std::shared_ptr<UnaryOperator> > (that.value);
        break;

      case 63: // variable_definition
        value.copy< std::shared_ptr<VariableDecl> > (that.value);
        break;

      case 60: // while_statement
        value.copy< std::shared_ptr<WhileStmt> > (that.value);
        break;

      case 69: // expression_list
        value.copy< std::vector<std::shared_ptr<Expr>> > (that.value);
        break;

      case 51: // function_definitions
        value.copy< std::vector<std::shared_ptr<FunctionDecl>> > (that.value);
        break;

      case 53: // parameter_variables
        value.copy< std::vector<std::shared_ptr<ParmVarDecl>> > (that.value);
        break;

      case 57: // statement_list
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
    #line 26 "MyParser.yy" // lalr1.cc:745
{
    // Initialize the initial location.
    yyla.location.begin.filename = yyla.location.end.filename = &driver.file;
}

#line 619 "MyParser.cpp" // lalr1.cc:745

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
      case 46: // "bool_literal"
        yylhs.value.build< std::shared_ptr<BoolLiteral> > ();
        break;

      case 68: // call_expression
        yylhs.value.build< std::shared_ptr<CallExpr> > ();
        break;

      case 56: // compound_statement
        yylhs.value.build< std::shared_ptr<CompoundStmt> > ();
        break;

      case 45: // "double_literal"
        yylhs.value.build< std::shared_ptr<DoubleLiteral> > ();
        break;

      case 64: // literal
      case 65: // primary_expression
      case 70: // expression
        yylhs.value.build< std::shared_ptr<Expr> > ();
        break;

      case 61: // for_statement
        yylhs.value.build< std::shared_ptr<ForStmt> > ();
        break;

      case 52: // function_definition
        yylhs.value.build< std::shared_ptr<FunctionDecl> > ();
        break;

      case 59: // if_statement
        yylhs.value.build< std::shared_ptr<IfStmt> > ();
        break;

      case 44: // "integer_literal"
        yylhs.value.build< std::shared_ptr<IntegerLiteral> > ();
        break;

      case 67: // member_expression
        yylhs.value.build< std::shared_ptr<MemberExpr> > ();
        break;

      case 43: // "identifier"
        yylhs.value.build< std::shared_ptr<NamedDecl> > ();
        break;

      case 54: // parameter_variable
        yylhs.value.build< std::shared_ptr<ParmVarDecl> > ();
        break;

      case 58: // return_statement
        yylhs.value.build< std::shared_ptr<ReturnStmt> > ();
        break;

      case 55: // statement
      case 62: // for_init_statement
        yylhs.value.build< std::shared_ptr<Stmt> > ();
        break;

      case 47: // "string_literal"
        yylhs.value.build< std::shared_ptr<StringLiteral> > ();
        break;

      case 50: // translation_unit
        yylhs.value.build< std::shared_ptr<TranslationUnitDecl> > ();
        break;

      case 66: // unary_expression
        yylhs.value.build< std::shared_ptr<UnaryOperator> > ();
        break;

      case 63: // variable_definition
        yylhs.value.build< std::shared_ptr<VariableDecl> > ();
        break;

      case 60: // while_statement
        yylhs.value.build< std::shared_ptr<WhileStmt> > ();
        break;

      case 69: // expression_list
        yylhs.value.build< std::vector<std::shared_ptr<Expr>> > ();
        break;

      case 51: // function_definitions
        yylhs.value.build< std::vector<std::shared_ptr<FunctionDecl>> > ();
        break;

      case 53: // parameter_variables
        yylhs.value.build< std::vector<std::shared_ptr<ParmVarDecl>> > ();
        break;

      case 57: // statement_list
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
#line 127 "MyParser.yy" // lalr1.cc:859
    { driver.ast.translationUnit = TranslationUnitDecl::make(yylhs.location, yystack_[0].value.as< std::vector<std::shared_ptr<FunctionDecl>> > ()); }
#line 824 "MyParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 131 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<FunctionDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<FunctionDecl> > ()); }
#line 830 "MyParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 132 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<FunctionDecl>> > () = appendVector(yystack_[1].value.as< std::shared_ptr<FunctionDecl> > (), yystack_[0].value.as< std::vector<std::shared_ptr<FunctionDecl>> > ()); }
#line 836 "MyParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 136 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<FunctionDecl> > () = FunctionDecl::make(yylhs.location, yystack_[4].value.as< std::shared_ptr<NamedDecl> > (), yystack_[2].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > (), yystack_[0].value.as< std::shared_ptr<CompoundStmt> > ()); }
#line 842 "MyParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 140 "MyParser.yy" // lalr1.cc:859
    { }
#line 848 "MyParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 141 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<ParmVarDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<ParmVarDecl> > ()); }
#line 854 "MyParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 142 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<ParmVarDecl>> > () = appendVector(yystack_[2].value.as< std::shared_ptr<ParmVarDecl> > (), yystack_[0].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > ()); }
#line 860 "MyParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 146 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ParmVarDecl> > () = ParmVarDecl::make(yylhs.location, yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 866 "MyParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 147 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ParmVarDecl> > () = ParmVarDecl::make(yylhs.location, yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 872 "MyParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 151 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[1].value.as< std::shared_ptr<Expr> > (); }
#line 878 "MyParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 152 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ReturnStmt> > (); }
#line 884 "MyParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 153 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(yystack_[1].value.as< std::shared_ptr<VariableDecl> > ()); }
#line 890 "MyParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 154 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<IfStmt> > (); }
#line 896 "MyParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 155 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<WhileStmt> > (); }
#line 902 "MyParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 156 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ForStmt> > (); }
#line 908 "MyParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 157 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<CompoundStmt> > (); }
#line 914 "MyParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 161 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CompoundStmt> > () = CompoundStmt::make(std::vector<std::shared_ptr<Stmt>>{}); }
#line 920 "MyParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 162 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CompoundStmt> > () = CompoundStmt::make(yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ()); }
#line 926 "MyParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 166 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Stmt>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 932 "MyParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 167 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Stmt>> > () = appendVector(yystack_[1].value.as< std::shared_ptr<Stmt> > (), yystack_[0].value.as< std::vector<std::shared_ptr<Stmt>> > ()); }
#line 938 "MyParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 171 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ReturnStmt> > () = ReturnStmt::make(); }
#line 944 "MyParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 172 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ReturnStmt> > () = ReturnStmt::make(yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 950 "MyParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 178 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IfStmt> > () = IfStmt::make(yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 956 "MyParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 179 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IfStmt> > () = IfStmt::make(yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[2].value.as< std::shared_ptr<Stmt> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 962 "MyParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 183 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<WhileStmt> > () = WhileStmt::make(yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 968 "MyParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 187 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ForStmt> > () = ForStmt::make(yystack_[5].value.as< std::shared_ptr<Stmt> > (), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 974 "MyParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 191 "MyParser.yy" // lalr1.cc:859
    { }
#line 980 "MyParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 192 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[1].value.as< std::shared_ptr<Expr> > (); }
#line 986 "MyParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 193 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(yystack_[1].value.as< std::shared_ptr<VariableDecl> > ()); }
#line 992 "MyParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 197 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VariableDecl> > () = VariableDecl::make(yylhs.location, yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 998 "MyParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 198 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VariableDecl> > () = VariableDecl::make(yylhs.location, yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1004 "MyParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 202 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<IntegerLiteral> > (); }
#line 1010 "MyParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 203 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<DoubleLiteral> > (); }
#line 1016 "MyParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 204 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<BoolLiteral> > (); }
#line 1022 "MyParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 205 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<StringLiteral> > (); }
#line 1028 "MyParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 218 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<Expr> > (); }
#line 1034 "MyParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 219 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = DeclRefExpr::make(yylhs.location, yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1040 "MyParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 220 "MyParser.yy" // lalr1.cc:859
    { std::swap(yylhs.value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1046 "MyParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 224 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(yylhs.location, UnaryOperatorKind::PreInc, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1052 "MyParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 225 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(yylhs.location, UnaryOperatorKind::PreDec, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1058 "MyParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 226 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(yylhs.location, UnaryOperatorKind::PostInc, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1064 "MyParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 227 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(yylhs.location, UnaryOperatorKind::PostDec, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1070 "MyParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 228 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(yylhs.location, UnaryOperatorKind::Plus, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1076 "MyParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 229 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(yylhs.location, UnaryOperatorKind::Minus, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1082 "MyParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 230 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(yylhs.location, UnaryOperatorKind::LogicalNot, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1088 "MyParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 234 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MemberExpr> > () = MemberExpr::make(yylhs.location, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1094 "MyParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 238 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CallExpr> > () = CallExpr::make(yylhs.location, DeclRefExpr::make(yystack_[3].location, yystack_[3].value.as< std::shared_ptr<NamedDecl> > ()), yystack_[1].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1100 "MyParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 242 "MyParser.yy" // lalr1.cc:859
    { }
#line 1106 "MyParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 243 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Expr>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1112 "MyParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 244 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Expr>> > () = appendVector(yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1118 "MyParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 248 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<Expr> > (); }
#line 1124 "MyParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 249 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = BinaryOperator::make(yylhs.location, BinaryOperatorKind::Add, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1130 "MyParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 250 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = BinaryOperator::make(yylhs.location, BinaryOperatorKind::Subtract, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1136 "MyParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 251 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = BinaryOperator::make(yylhs.location, BinaryOperatorKind::Multiply, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1142 "MyParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 252 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = BinaryOperator::make(yylhs.location, BinaryOperatorKind::Divide, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1148 "MyParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 253 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = BinaryOperator::make(yylhs.location, BinaryOperatorKind::Mod, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1154 "MyParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 254 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = BinaryOperator::make(yylhs.location, BinaryOperatorKind::Assign, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1160 "MyParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 255 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = BinaryOperator::make(yylhs.location, BinaryOperatorKind::Equal, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1166 "MyParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 256 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = BinaryOperator::make(yylhs.location, BinaryOperatorKind::NotEqual, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1172 "MyParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 257 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = BinaryOperator::make(yylhs.location, BinaryOperatorKind::LogicalAnd, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1178 "MyParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 258 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = BinaryOperator::make(yylhs.location, BinaryOperatorKind::LogicalOr, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1184 "MyParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 259 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<UnaryOperator> > (); }
#line 1190 "MyParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 260 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<CallExpr> > (); }
#line 1196 "MyParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 261 "MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<MemberExpr> > (); }
#line 1202 "MyParser.cpp" // lalr1.cc:859
    break;


#line 1206 "MyParser.cpp" // lalr1.cc:859
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


  const signed char MyParser::yypact_ninf_ = -36;

  const signed char MyParser::yytable_ninf_ = -1;

  const short int
  MyParser::yypact_[] =
  {
     -35,   -34,    16,   -36,   -35,    -4,   -36,   -36,   -12,     4,
      14,     9,     1,    28,   -12,   -36,    53,   -36,   -36,   295,
     295,   295,   295,   295,    60,   -36,   105,    17,    18,    36,
      37,    41,   -36,   -36,   -36,   -36,    97,   -36,    42,   -36,
     -36,   -36,   -36,    39,   -36,     8,   -36,   -36,   -36,     0,
     -36,   -36,   -36,   -36,   -36,   -36,     7,   -36,   157,    69,
      60,    60,   141,    60,   -36,   -36,   -36,   -36,   -36,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,   -36,
      30,   -36,   -36,    60,   189,   213,   -36,    60,    45,   237,
      56,   245,   311,    22,    22,    49,    49,    49,   277,   194,
     318,   318,   -36,   311,    97,    97,   269,   -36,   -36,   -36,
      60,    44,   -36,    60,   -36,    97,   287,   -36,    97,   -36
  };

  const unsigned char
  MyParser::yydefact_[] =
  {
       0,     0,     0,     2,     3,     0,     1,     4,     6,     9,
       0,     7,     0,     0,     6,    10,     0,     5,     8,     0,
       0,     0,     0,     0,     0,    18,     0,     0,     0,     0,
       0,    38,    33,    34,    35,    36,    20,    17,     0,    12,
      14,    15,    16,     0,    37,    52,    63,    65,    64,     0,
      38,    45,    44,    40,    41,    46,     0,    22,     0,    31,
       0,     0,     0,    49,    21,    19,    13,    42,    43,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    11,
       0,    39,    23,     0,     0,     0,    28,     0,     0,     0,
       0,    50,    58,    54,    53,    55,    56,    57,    61,    62,
      59,    60,    47,    32,     0,     0,     0,    30,    29,    48,
      49,    24,    26,     0,    51,     0,     0,    25,     0,    27
  };

  const short int
  MyParser::yypgoto_[] =
  {
     -36,   -36,    75,   -36,    73,   -36,    10,    80,    52,   -36,
     -36,   -36,   -36,   -36,    46,   -36,   148,   -36,   -36,   -36,
       6,   -24
  };

  const signed char
  MyParser::yydefgoto_[] =
  {
      -1,     2,     3,     4,    10,    11,    36,    37,    38,    39,
      40,    41,    42,    87,    43,    44,    45,    46,    47,    48,
      90,    49
  };

  const unsigned char
  MyParser::yytable_[] =
  {
      56,     1,    58,    69,    70,    71,    72,    73,    74,     5,
      69,    70,    71,    72,    73,    74,     6,    75,    76,    77,
      78,     8,    67,    68,    75,    76,    77,    78,    72,    73,
      74,     9,    79,    81,    80,    12,    84,    85,    89,    91,
      13,    80,    14,    60,    15,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,    16,    80,    19,    20,   103,
      59,    61,    62,   106,    19,    20,    63,    21,    22,    23,
      65,    66,    83,   102,    21,    22,    23,   107,    24,     7,
      16,    25,   109,    80,   115,    24,    91,    18,    64,   116,
      26,    27,    28,    17,    29,    30,    31,    32,    33,    34,
      35,    19,    20,    31,    32,    33,    34,    35,    88,    19,
      20,    21,    22,    23,   111,   112,   114,     0,     0,    21,
      22,    23,    24,     0,    16,   117,     0,     0,   119,     0,
      24,     0,     0,     0,    26,    27,    28,    57,    29,    30,
      31,    32,    33,    34,    35,    19,    20,     0,    31,    32,
      33,    34,    35,     0,     0,    21,    22,    23,     0,     0,
      69,    70,    71,    72,    73,    74,    24,    51,    52,    53,
      54,    55,     0,    86,    75,    76,    77,    78,     0,    27,
       0,     0,     0,     0,    31,    32,    33,    34,    35,    82,
       0,    80,    69,    70,    71,    72,    73,    74,    70,    71,
      72,    73,    74,     0,     0,     0,    75,    76,    77,    78,
       0,    75,     0,    77,    78,   104,    69,    70,    71,    72,
      73,    74,     0,    80,     0,     0,     0,     0,    80,     0,
      75,    76,    77,    78,     0,     0,     0,     0,     0,   105,
      69,    70,    71,    72,    73,    74,     0,    80,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,     0,     0,
       0,     0,    75,    76,    77,    78,     0,     0,     0,   108,
       0,    80,    69,    70,    71,    72,    73,    74,   110,    80,
       0,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      69,    70,    71,    72,    73,    74,    77,    78,     0,     0,
       0,   113,     0,    80,    75,    76,    77,    78,     0,     0,
       0,    80,     0,   118,    69,    70,    71,    72,    73,    74,
      24,    80,    70,    71,    72,    73,    74,     0,    75,    76,
      77,    78,     0,     0,     0,     0,     0,     0,    50,    32,
      33,    34,    35,     0,     0,    80,     0,     0,     0,     0,
       0,     0,    80
  };

  const signed char
  MyParser::yycheck_[] =
  {
      24,    36,    26,     3,     4,     5,     6,     7,     8,    43,
       3,     4,     5,     6,     7,     8,     0,    17,    18,    19,
      20,    25,    14,    15,    17,    18,    19,    20,     6,     7,
       8,    43,    32,    26,    34,    31,    60,    61,    62,    63,
      26,    34,    33,    25,    43,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    27,    34,     4,     5,    83,
      43,    25,    25,    87,     4,     5,    25,    14,    15,    16,
      28,    32,     3,    43,    14,    15,    16,    32,    25,     4,
      27,    28,    26,    34,    40,    25,   110,    14,    36,   113,
      37,    38,    39,    13,    41,    42,    43,    44,    45,    46,
      47,     4,     5,    43,    44,    45,    46,    47,    62,     4,
       5,    14,    15,    16,   104,   105,   110,    -1,    -1,    14,
      15,    16,    25,    -1,    27,   115,    -1,    -1,   118,    -1,
      25,    -1,    -1,    -1,    37,    38,    39,    32,    41,    42,
      43,    44,    45,    46,    47,     4,     5,    -1,    43,    44,
      45,    46,    47,    -1,    -1,    14,    15,    16,    -1,    -1,
       3,     4,     5,     6,     7,     8,    25,    19,    20,    21,
      22,    23,    -1,    32,    17,    18,    19,    20,    -1,    38,
      -1,    -1,    -1,    -1,    43,    44,    45,    46,    47,    32,
      -1,    34,     3,     4,     5,     6,     7,     8,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    17,    18,    19,    20,
      -1,    17,    -1,    19,    20,    26,     3,     4,     5,     6,
       7,     8,    -1,    34,    -1,    -1,    -1,    -1,    34,    -1,
      17,    18,    19,    20,    -1,    -1,    -1,    -1,    -1,    26,
       3,     4,     5,     6,     7,     8,    -1,    34,     3,     4,
       5,     6,     7,     8,    17,    18,    19,    20,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    -1,    -1,    -1,    32,
      -1,    34,     3,     4,     5,     6,     7,     8,    33,    34,
      -1,     4,     5,     6,     7,     8,    17,    18,    19,    20,
       3,     4,     5,     6,     7,     8,    19,    20,    -1,    -1,
      -1,    32,    -1,    34,    17,    18,    19,    20,    -1,    -1,
      -1,    34,    -1,    26,     3,     4,     5,     6,     7,     8,
      25,    34,     4,     5,     6,     7,     8,    -1,    17,    18,
      19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      45,    46,    47,    -1,    -1,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    34
  };

  const unsigned char
  MyParser::yystos_[] =
  {
       0,    36,    50,    51,    52,    43,     0,    51,    25,    43,
      53,    54,    31,    26,    33,    43,    27,    56,    53,     4,
       5,    14,    15,    16,    25,    28,    37,    38,    39,    41,
      42,    43,    44,    45,    46,    47,    55,    56,    57,    58,
      59,    60,    61,    63,    64,    65,    66,    67,    68,    70,
      43,    65,    65,    65,    65,    65,    70,    32,    70,    43,
      25,    25,    25,    25,    57,    28,    32,    14,    15,     3,
       4,     5,     6,     7,     8,    17,    18,    19,    20,    32,
      34,    26,    32,     3,    70,    70,    32,    62,    63,    70,
      69,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    43,    70,    26,    26,    70,    32,    32,    26,
      33,    55,    55,    32,    69,    40,    70,    55,    26,    55
  };

  const unsigned char
  MyParser::yyr1_[] =
  {
       0,    49,    50,    51,    51,    52,    53,    53,    53,    54,
      54,    55,    55,    55,    55,    55,    55,    55,    56,    56,
      57,    57,    58,    58,    59,    59,    60,    61,    62,    62,
      62,    63,    63,    64,    64,    64,    64,    65,    65,    65,
      66,    66,    66,    66,    66,    66,    66,    67,    68,    69,
      69,    69,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70
  };

  const unsigned char
  MyParser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     6,     0,     1,     3,     1,
       3,     2,     1,     2,     1,     1,     1,     1,     2,     3,
       1,     2,     2,     3,     5,     7,     5,     8,     1,     2,
       2,     2,     4,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     2,     2,     2,     2,     2,     3,     4,     0,
       1,     3,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     1
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
  "\"?\"", "\"function\"", "\"return\"", "\"let\"", "\"if\"", "\"else\"",
  "\"while\"", "\"for\"", "\"identifier\"", "\"integer_literal\"",
  "\"double_literal\"", "\"bool_literal\"", "\"string_literal\"",
  "\"then\"", "$accept", "translation_unit", "function_definitions",
  "function_definition", "parameter_variables", "parameter_variable",
  "statement", "compound_statement", "statement_list", "return_statement",
  "if_statement", "while_statement", "for_statement", "for_init_statement",
  "variable_definition", "literal", "primary_expression",
  "unary_expression", "member_expression", "call_expression",
  "expression_list", "expression", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  MyParser::yyrline_[] =
  {
       0,   127,   127,   131,   132,   136,   140,   141,   142,   146,
     147,   151,   152,   153,   154,   155,   156,   157,   161,   162,
     166,   167,   171,   172,   178,   179,   183,   187,   191,   192,
     193,   197,   198,   202,   203,   204,   205,   218,   219,   220,
     224,   225,   226,   227,   228,   229,   230,   234,   238,   242,
     243,   244,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261
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
#line 1707 "MyParser.cpp" // lalr1.cc:1167
#line 264 "MyParser.yy" // lalr1.cc:1168


void yy::MyParser::error(const location_type& l, const std::string& m)
{
    driver.error (l, m);
}
