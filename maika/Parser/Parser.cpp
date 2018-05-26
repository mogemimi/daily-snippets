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

#line 37 "Parser/Parser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "Parser.h"

// User implementation prologue.

#line 51 "Parser/Parser.cpp" // lalr1.cc:412
// Unqualified %code blocks.
#line 52 "Parser/Parser.yy" // lalr1.cc:413

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

#line 76 "Parser/Parser.cpp" // lalr1.cc:413


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
#line 162 "Parser/Parser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
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
  Parser::Parser (Driver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 106: // binary_op
        value.move< BinaryOperatorKind > (that.value);
        break;

      case 68: // call_signature
        value.move< CallSignature > (that.value);
        break;

      case 97: // array_literal
        value.move< std::shared_ptr<ArrayLiteral> > (that.value);
        break;

      case 107: // binary_expression
      case 110: // assignment_expression
        value.move< std::shared_ptr<BinaryOperator> > (that.value);
        break;

      case 91: // binding_declaration
        value.move< std::shared_ptr<BindingDecl> > (that.value);
        break;

      case 53: // "bool_literal"
        value.move< std::shared_ptr<BoolLiteral> > (that.value);
        break;

      case 103: // call_expression
        value.move< std::shared_ptr<CallExpr> > (that.value);
        break;

      case 73: // class_declaration
        value.move< std::shared_ptr<ClassDecl> > (that.value);
        break;

      case 77: // compound_statement
        value.move< std::shared_ptr<CompoundStmt> > (that.value);
        break;

      case 108: // conditional_expression
        value.move< std::shared_ptr<ConditionalOperator> > (that.value);
        break;

      case 88: // const_definition
        value.move< std::shared_ptr<ConstDecl> > (that.value);
        break;

      case 65: // translation_unit_declaration
      case 75: // member_declaration
      case 85: // for_range_init
        value.move< std::shared_ptr<Decl> > (that.value);
        break;

      case 89: // decomposition_definition
        value.move< std::shared_ptr<DecompositionDecl> > (that.value);
        break;

      case 86: // defer_statement
        value.move< std::shared_ptr<DeferStmt> > (that.value);
        break;

      case 52: // "double_literal"
        value.move< std::shared_ptr<DoubleLiteral> > (that.value);
        break;

      case 93: // literal
      case 94: // primary_expression
      case 112: // expression
        value.move< std::shared_ptr<Expr> > (that.value);
        break;

      case 84: // for_range_statement
        value.move< std::shared_ptr<ForRangeStmt> > (that.value);
        break;

      case 82: // for_statement
        value.move< std::shared_ptr<ForStmt> > (that.value);
        break;

      case 66: // function_definition
        value.move< std::shared_ptr<FunctionDecl> > (that.value);
        break;

      case 67: // function_expression
        value.move< std::shared_ptr<FunctionExpr> > (that.value);
        break;

      case 80: // if_statement
        value.move< std::shared_ptr<IfStmt> > (that.value);
        break;

      case 51: // "integer_literal"
        value.move< std::shared_ptr<IntegerLiteral> > (that.value);
        break;

      case 99: // map_entry
        value.move< std::shared_ptr<MapEntry> > (that.value);
        break;

      case 98: // map_literal
        value.move< std::shared_ptr<MapLiteral> > (that.value);
        break;

      case 101: // member_expression
        value.move< std::shared_ptr<MemberExpr> > (that.value);
        break;

      case 50: // "identifier"
      case 69: // binding_identifier
      case 72: // type_specifier
        value.move< std::shared_ptr<NamedDecl> > (that.value);
        break;

      case 104: // null_conditional_expression
        value.move< std::shared_ptr<NullConditionalOperator> > (that.value);
        break;

      case 96: // null_literal
        value.move< std::shared_ptr<NullLiteral> > (that.value);
        break;

      case 95: // parenthesized_expression
        value.move< std::shared_ptr<ParenExpr> > (that.value);
        break;

      case 71: // parameter_variable
        value.move< std::shared_ptr<ParmVarDecl> > (that.value);
        break;

      case 79: // return_statement
        value.move< std::shared_ptr<ReturnStmt> > (that.value);
        break;

      case 76: // statement
      case 83: // for_init_statement
        value.move< std::shared_ptr<Stmt> > (that.value);
        break;

      case 54: // "string_literal"
        value.move< std::shared_ptr<StringLiteral> > (that.value);
        break;

      case 102: // subscript_expression
        value.move< std::shared_ptr<SubscriptExpr> > (that.value);
        break;

      case 63: // translation_unit
        value.move< std::shared_ptr<TranslationUnitDecl> > (that.value);
        break;

      case 105: // unary_expression
        value.move< std::shared_ptr<UnaryOperator> > (that.value);
        break;

      case 87: // variable_definition
        value.move< std::shared_ptr<VariableDecl> > (that.value);
        break;

      case 81: // while_statement
        value.move< std::shared_ptr<WhileStmt> > (that.value);
        break;

      case 90: // binding_declarations
        value.move< std::vector<std::shared_ptr<BindingDecl>> > (that.value);
        break;

      case 64: // translation_unit_declarations
      case 74: // member_declaration_list
        value.move< std::vector<std::shared_ptr<Decl>> > (that.value);
        break;

      case 111: // expression_list
        value.move< std::vector<std::shared_ptr<Expr>> > (that.value);
        break;

      case 100: // map_entry_list
        value.move< std::vector<std::shared_ptr<MapEntry>> > (that.value);
        break;

      case 70: // parameter_variables
        value.move< std::vector<std::shared_ptr<ParmVarDecl>> > (that.value);
        break;

      case 78: // statement_list
        value.move< std::vector<std::shared_ptr<Stmt>> > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 106: // binary_op
        value.copy< BinaryOperatorKind > (that.value);
        break;

      case 68: // call_signature
        value.copy< CallSignature > (that.value);
        break;

      case 97: // array_literal
        value.copy< std::shared_ptr<ArrayLiteral> > (that.value);
        break;

      case 107: // binary_expression
      case 110: // assignment_expression
        value.copy< std::shared_ptr<BinaryOperator> > (that.value);
        break;

      case 91: // binding_declaration
        value.copy< std::shared_ptr<BindingDecl> > (that.value);
        break;

      case 53: // "bool_literal"
        value.copy< std::shared_ptr<BoolLiteral> > (that.value);
        break;

      case 103: // call_expression
        value.copy< std::shared_ptr<CallExpr> > (that.value);
        break;

      case 73: // class_declaration
        value.copy< std::shared_ptr<ClassDecl> > (that.value);
        break;

      case 77: // compound_statement
        value.copy< std::shared_ptr<CompoundStmt> > (that.value);
        break;

      case 108: // conditional_expression
        value.copy< std::shared_ptr<ConditionalOperator> > (that.value);
        break;

      case 88: // const_definition
        value.copy< std::shared_ptr<ConstDecl> > (that.value);
        break;

      case 65: // translation_unit_declaration
      case 75: // member_declaration
      case 85: // for_range_init
        value.copy< std::shared_ptr<Decl> > (that.value);
        break;

      case 89: // decomposition_definition
        value.copy< std::shared_ptr<DecompositionDecl> > (that.value);
        break;

      case 86: // defer_statement
        value.copy< std::shared_ptr<DeferStmt> > (that.value);
        break;

      case 52: // "double_literal"
        value.copy< std::shared_ptr<DoubleLiteral> > (that.value);
        break;

      case 93: // literal
      case 94: // primary_expression
      case 112: // expression
        value.copy< std::shared_ptr<Expr> > (that.value);
        break;

      case 84: // for_range_statement
        value.copy< std::shared_ptr<ForRangeStmt> > (that.value);
        break;

      case 82: // for_statement
        value.copy< std::shared_ptr<ForStmt> > (that.value);
        break;

      case 66: // function_definition
        value.copy< std::shared_ptr<FunctionDecl> > (that.value);
        break;

      case 67: // function_expression
        value.copy< std::shared_ptr<FunctionExpr> > (that.value);
        break;

      case 80: // if_statement
        value.copy< std::shared_ptr<IfStmt> > (that.value);
        break;

      case 51: // "integer_literal"
        value.copy< std::shared_ptr<IntegerLiteral> > (that.value);
        break;

      case 99: // map_entry
        value.copy< std::shared_ptr<MapEntry> > (that.value);
        break;

      case 98: // map_literal
        value.copy< std::shared_ptr<MapLiteral> > (that.value);
        break;

      case 101: // member_expression
        value.copy< std::shared_ptr<MemberExpr> > (that.value);
        break;

      case 50: // "identifier"
      case 69: // binding_identifier
      case 72: // type_specifier
        value.copy< std::shared_ptr<NamedDecl> > (that.value);
        break;

      case 104: // null_conditional_expression
        value.copy< std::shared_ptr<NullConditionalOperator> > (that.value);
        break;

      case 96: // null_literal
        value.copy< std::shared_ptr<NullLiteral> > (that.value);
        break;

      case 95: // parenthesized_expression
        value.copy< std::shared_ptr<ParenExpr> > (that.value);
        break;

      case 71: // parameter_variable
        value.copy< std::shared_ptr<ParmVarDecl> > (that.value);
        break;

      case 79: // return_statement
        value.copy< std::shared_ptr<ReturnStmt> > (that.value);
        break;

      case 76: // statement
      case 83: // for_init_statement
        value.copy< std::shared_ptr<Stmt> > (that.value);
        break;

      case 54: // "string_literal"
        value.copy< std::shared_ptr<StringLiteral> > (that.value);
        break;

      case 102: // subscript_expression
        value.copy< std::shared_ptr<SubscriptExpr> > (that.value);
        break;

      case 63: // translation_unit
        value.copy< std::shared_ptr<TranslationUnitDecl> > (that.value);
        break;

      case 105: // unary_expression
        value.copy< std::shared_ptr<UnaryOperator> > (that.value);
        break;

      case 87: // variable_definition
        value.copy< std::shared_ptr<VariableDecl> > (that.value);
        break;

      case 81: // while_statement
        value.copy< std::shared_ptr<WhileStmt> > (that.value);
        break;

      case 90: // binding_declarations
        value.copy< std::vector<std::shared_ptr<BindingDecl>> > (that.value);
        break;

      case 64: // translation_unit_declarations
      case 74: // member_declaration_list
        value.copy< std::vector<std::shared_ptr<Decl>> > (that.value);
        break;

      case 111: // expression_list
        value.copy< std::vector<std::shared_ptr<Expr>> > (that.value);
        break;

      case 100: // map_entry_list
        value.copy< std::vector<std::shared_ptr<MapEntry>> > (that.value);
        break;

      case 70: // parameter_variables
        value.copy< std::vector<std::shared_ptr<ParmVarDecl>> > (that.value);
        break;

      case 78: // statement_list
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
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
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
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
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
    #line 43 "Parser/Parser.yy" // lalr1.cc:745
{
    // Initialize the initial location.
    yyla.location.begin.filename = yyla.location.end.filename = &driver.file;
}

#line 806 "Parser/Parser.cpp" // lalr1.cc:745

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
      case 106: // binary_op
        yylhs.value.build< BinaryOperatorKind > ();
        break;

      case 68: // call_signature
        yylhs.value.build< CallSignature > ();
        break;

      case 97: // array_literal
        yylhs.value.build< std::shared_ptr<ArrayLiteral> > ();
        break;

      case 107: // binary_expression
      case 110: // assignment_expression
        yylhs.value.build< std::shared_ptr<BinaryOperator> > ();
        break;

      case 91: // binding_declaration
        yylhs.value.build< std::shared_ptr<BindingDecl> > ();
        break;

      case 53: // "bool_literal"
        yylhs.value.build< std::shared_ptr<BoolLiteral> > ();
        break;

      case 103: // call_expression
        yylhs.value.build< std::shared_ptr<CallExpr> > ();
        break;

      case 73: // class_declaration
        yylhs.value.build< std::shared_ptr<ClassDecl> > ();
        break;

      case 77: // compound_statement
        yylhs.value.build< std::shared_ptr<CompoundStmt> > ();
        break;

      case 108: // conditional_expression
        yylhs.value.build< std::shared_ptr<ConditionalOperator> > ();
        break;

      case 88: // const_definition
        yylhs.value.build< std::shared_ptr<ConstDecl> > ();
        break;

      case 65: // translation_unit_declaration
      case 75: // member_declaration
      case 85: // for_range_init
        yylhs.value.build< std::shared_ptr<Decl> > ();
        break;

      case 89: // decomposition_definition
        yylhs.value.build< std::shared_ptr<DecompositionDecl> > ();
        break;

      case 86: // defer_statement
        yylhs.value.build< std::shared_ptr<DeferStmt> > ();
        break;

      case 52: // "double_literal"
        yylhs.value.build< std::shared_ptr<DoubleLiteral> > ();
        break;

      case 93: // literal
      case 94: // primary_expression
      case 112: // expression
        yylhs.value.build< std::shared_ptr<Expr> > ();
        break;

      case 84: // for_range_statement
        yylhs.value.build< std::shared_ptr<ForRangeStmt> > ();
        break;

      case 82: // for_statement
        yylhs.value.build< std::shared_ptr<ForStmt> > ();
        break;

      case 66: // function_definition
        yylhs.value.build< std::shared_ptr<FunctionDecl> > ();
        break;

      case 67: // function_expression
        yylhs.value.build< std::shared_ptr<FunctionExpr> > ();
        break;

      case 80: // if_statement
        yylhs.value.build< std::shared_ptr<IfStmt> > ();
        break;

      case 51: // "integer_literal"
        yylhs.value.build< std::shared_ptr<IntegerLiteral> > ();
        break;

      case 99: // map_entry
        yylhs.value.build< std::shared_ptr<MapEntry> > ();
        break;

      case 98: // map_literal
        yylhs.value.build< std::shared_ptr<MapLiteral> > ();
        break;

      case 101: // member_expression
        yylhs.value.build< std::shared_ptr<MemberExpr> > ();
        break;

      case 50: // "identifier"
      case 69: // binding_identifier
      case 72: // type_specifier
        yylhs.value.build< std::shared_ptr<NamedDecl> > ();
        break;

      case 104: // null_conditional_expression
        yylhs.value.build< std::shared_ptr<NullConditionalOperator> > ();
        break;

      case 96: // null_literal
        yylhs.value.build< std::shared_ptr<NullLiteral> > ();
        break;

      case 95: // parenthesized_expression
        yylhs.value.build< std::shared_ptr<ParenExpr> > ();
        break;

      case 71: // parameter_variable
        yylhs.value.build< std::shared_ptr<ParmVarDecl> > ();
        break;

      case 79: // return_statement
        yylhs.value.build< std::shared_ptr<ReturnStmt> > ();
        break;

      case 76: // statement
      case 83: // for_init_statement
        yylhs.value.build< std::shared_ptr<Stmt> > ();
        break;

      case 54: // "string_literal"
        yylhs.value.build< std::shared_ptr<StringLiteral> > ();
        break;

      case 102: // subscript_expression
        yylhs.value.build< std::shared_ptr<SubscriptExpr> > ();
        break;

      case 63: // translation_unit
        yylhs.value.build< std::shared_ptr<TranslationUnitDecl> > ();
        break;

      case 105: // unary_expression
        yylhs.value.build< std::shared_ptr<UnaryOperator> > ();
        break;

      case 87: // variable_definition
        yylhs.value.build< std::shared_ptr<VariableDecl> > ();
        break;

      case 81: // while_statement
        yylhs.value.build< std::shared_ptr<WhileStmt> > ();
        break;

      case 90: // binding_declarations
        yylhs.value.build< std::vector<std::shared_ptr<BindingDecl>> > ();
        break;

      case 64: // translation_unit_declarations
      case 74: // member_declaration_list
        yylhs.value.build< std::vector<std::shared_ptr<Decl>> > ();
        break;

      case 111: // expression_list
        yylhs.value.build< std::vector<std::shared_ptr<Expr>> > ();
        break;

      case 100: // map_entry_list
        yylhs.value.build< std::vector<std::shared_ptr<MapEntry>> > ();
        break;

      case 70: // parameter_variables
        yylhs.value.build< std::vector<std::shared_ptr<ParmVarDecl>> > ();
        break;

      case 78: // statement_list
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
#line 204 "Parser/Parser.yy" // lalr1.cc:859
    { driver.ast.translationUnit = TranslationUnitDecl::make(toLoc(yylhs.location), std::vector<std::shared_ptr<Decl>>{}); }
#line 1101 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 205 "Parser/Parser.yy" // lalr1.cc:859
    { driver.ast.translationUnit = TranslationUnitDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::vector<std::shared_ptr<Decl>> > ()); }
#line 1107 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 209 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Decl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Decl> > ()); }
#line 1113 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 210 "Parser/Parser.yy" // lalr1.cc:859
    { yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Decl> > ()); yylhs.value.as< std::vector<std::shared_ptr<Decl>> > () = std::move(yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ()); }
#line 1119 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 214 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[0].value.as< std::shared_ptr<ClassDecl> > (); }
#line 1125 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 215 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[0].value.as< std::shared_ptr<FunctionDecl> > (); }
#line 1131 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 219 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<FunctionDecl> > () = FunctionDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), std::get<0>(yystack_[1].value.as< CallSignature > ()), std::get<1>(yystack_[1].value.as< CallSignature > ()), yystack_[0].value.as< std::shared_ptr<CompoundStmt> > ()); }
#line 1137 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 223 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<FunctionExpr> > () = FunctionExpr::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), std::get<0>(yystack_[1].value.as< CallSignature > ()), std::get<1>(yystack_[1].value.as< CallSignature > ()), yystack_[0].value.as< std::shared_ptr<CompoundStmt> > ()); }
#line 1143 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 227 "Parser/Parser.yy" // lalr1.cc:859
    { std::get<1>(yylhs.value.as< CallSignature > ()) = nullptr; }
#line 1149 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 228 "Parser/Parser.yy" // lalr1.cc:859
    { std::get<1>(yylhs.value.as< CallSignature > ()) = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1155 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 229 "Parser/Parser.yy" // lalr1.cc:859
    { std::get<0>(yylhs.value.as< CallSignature > ()) = yystack_[1].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > (); std::get<1>(yylhs.value.as< CallSignature > ()) = nullptr; }
#line 1161 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 230 "Parser/Parser.yy" // lalr1.cc:859
    { std::get<0>(yylhs.value.as< CallSignature > ()) = yystack_[3].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > (); std::get<1>(yylhs.value.as< CallSignature > ()) = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1167 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 234 "Parser/Parser.yy" // lalr1.cc:859
    { }
#line 1173 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 235 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NamedDecl> > () = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1179 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 239 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<ParmVarDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<ParmVarDecl> > ()); }
#line 1185 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 240 "Parser/Parser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<ParmVarDecl> > ()); yylhs.value.as< std::vector<std::shared_ptr<ParmVarDecl>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > ()); }
#line 1191 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 244 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ParmVarDecl> > () = ParmVarDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1197 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 245 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ParmVarDecl> > () = ParmVarDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1203 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 249 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NamedDecl> > () = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1209 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 253 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ClassDecl> > () = ClassDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), std::vector<std::shared_ptr<Decl>>{}); }
#line 1215 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 254 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ClassDecl> > () = ClassDecl::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<NamedDecl> > (), yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ()); }
#line 1221 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 258 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Decl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Decl> > ()); }
#line 1227 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 259 "Parser/Parser.yy" // lalr1.cc:859
    { yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Decl> > ()); yylhs.value.as< std::vector<std::shared_ptr<Decl>> > () = std::move(yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ()); }
#line 1233 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 263 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[0].value.as< std::shared_ptr<FunctionDecl> > (); }
#line 1239 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 264 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[1].value.as< std::shared_ptr<VariableDecl> > (); }
#line 1245 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 265 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[1].value.as< std::shared_ptr<ConstDecl> > (); }
#line 1251 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 269 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<CompoundStmt> > (); }
#line 1257 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 270 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[1].value.as< std::shared_ptr<Expr> > (); }
#line 1263 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 271 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ReturnStmt> > (); }
#line 1269 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 272 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<VariableDecl> > ()); }
#line 1275 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 273 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<ConstDecl> > ()); }
#line 1281 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 274 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<DecompositionDecl> > ()); }
#line 1287 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 275 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<IfStmt> > (); }
#line 1293 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 276 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<WhileStmt> > (); }
#line 1299 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 277 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ForStmt> > (); }
#line 1305 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 278 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ForRangeStmt> > (); }
#line 1311 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 279 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<DeferStmt> > (); }
#line 1317 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 283 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CompoundStmt> > () = CompoundStmt::make(toLoc(yylhs.location), std::vector<std::shared_ptr<Stmt>>{}); }
#line 1323 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 284 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CompoundStmt> > () = CompoundStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ()); }
#line 1329 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 288 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Stmt>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1335 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 289 "Parser/Parser.yy" // lalr1.cc:859
    { yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Stmt> > ()); yylhs.value.as< std::vector<std::shared_ptr<Stmt>> > () = std::move(yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ()); }
#line 1341 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 293 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ReturnStmt> > () = ReturnStmt::make(toLoc(yylhs.location)); }
#line 1347 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 294 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ReturnStmt> > () = ReturnStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1353 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 298 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IfStmt> > () = IfStmt::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1359 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 299 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IfStmt> > () = IfStmt::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[2].value.as< std::shared_ptr<Stmt> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1365 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 303 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<WhileStmt> > () = WhileStmt::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1371 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 307 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ForStmt> > () = ForStmt::make(toLoc(yylhs.location), yystack_[5].value.as< std::shared_ptr<Stmt> > (), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1377 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 311 "Parser/Parser.yy" // lalr1.cc:859
    { }
#line 1383 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 312 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[1].value.as< std::shared_ptr<Expr> > (); }
#line 1389 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 313 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<VariableDecl> > ()); }
#line 1395 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 317 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ForRangeStmt> > () = ForRangeStmt::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Decl> > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1401 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 321 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1407 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 322 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > (), nullptr, nullptr); }
#line 1413 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 323 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = ConstDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > (), nullptr, nullptr); }
#line 1419 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 324 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = DecompositionDecl::make(toLoc(yylhs.location), yystack_[1].value.as< std::vector<std::shared_ptr<BindingDecl>> > ()); }
#line 1425 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 325 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = DecompositionDecl::make(toLoc(yylhs.location), yystack_[1].value.as< std::vector<std::shared_ptr<BindingDecl>> > ()); }
#line 1431 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 329 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<DeferStmt> > () = DeferStmt::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1437 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 333 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VariableDecl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > (), nullptr, nullptr); }
#line 1443 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 334 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VariableDecl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), nullptr, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1449 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 335 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VariableDecl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > (), nullptr); }
#line 1455 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 336 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VariableDecl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<NamedDecl> > (), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1461 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 340 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ConstDecl> > () = ConstDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > (), nullptr, nullptr); }
#line 1467 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 341 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ConstDecl> > () = ConstDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), nullptr, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1473 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 342 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ConstDecl> > () = ConstDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > (), nullptr); }
#line 1479 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 343 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ConstDecl> > () = ConstDecl::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<NamedDecl> > (), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1485 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 347 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<DecompositionDecl> > () = DecompositionDecl::make(toLoc(yylhs.location), yystack_[3].value.as< std::vector<std::shared_ptr<BindingDecl>> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1491 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 348 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<DecompositionDecl> > () = DecompositionDecl::make(toLoc(yylhs.location), yystack_[3].value.as< std::vector<std::shared_ptr<BindingDecl>> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1497 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 352 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<BindingDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<BindingDecl> > ()); }
#line 1503 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 353 "Parser/Parser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<BindingDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<BindingDecl> > ()); yylhs.value.as< std::vector<std::shared_ptr<BindingDecl>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<BindingDecl>> > ()); }
#line 1509 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 357 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BindingDecl> > () = BindingDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1515 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 361 "Parser/Parser.yy" // lalr1.cc:859
    { }
#line 1521 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 362 "Parser/Parser.yy" // lalr1.cc:859
    { }
#line 1527 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 366 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<IntegerLiteral> > (); }
#line 1533 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 367 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<DoubleLiteral> > (); }
#line 1539 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 368 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<BoolLiteral> > (); }
#line 1545 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 369 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<StringLiteral> > (); }
#line 1551 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 373 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<Expr> > (); }
#line 1557 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 374 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<NullLiteral> > (); }
#line 1563 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 375 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = DeclRefExpr::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1569 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 376 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<ParenExpr> > (); }
#line 1575 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 377 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<ArrayLiteral> > (); }
#line 1581 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 378 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<MapLiteral> > (); }
#line 1587 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 379 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<CallExpr> > (); }
#line 1593 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 380 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<MemberExpr> > (); }
#line 1599 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 381 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<SubscriptExpr> > (); }
#line 1605 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 382 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<NullConditionalOperator> > (); }
#line 1611 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 386 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ParenExpr> > () = ParenExpr::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1617 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 390 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullLiteral> > () = NullLiteral::make(toLoc(yylhs.location)); }
#line 1623 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 394 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ArrayLiteral> > () = ArrayLiteral::make(toLoc(yylhs.location), std::vector<std::shared_ptr<Expr>>{}); }
#line 1629 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 395 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ArrayLiteral> > () = ArrayLiteral::make(toLoc(yylhs.location), yystack_[2].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1635 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 399 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MapLiteral> > () = MapLiteral::make(toLoc(yylhs.location), std::vector<std::shared_ptr<MapEntry>>{}); }
#line 1641 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 400 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MapLiteral> > () = MapLiteral::make(toLoc(yylhs.location), yystack_[2].value.as< std::vector<std::shared_ptr<MapEntry>> > ()); }
#line 1647 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 404 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MapEntry> > () = MapEntry::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1653 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 408 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<MapEntry>> > ().push_back(yystack_[0].value.as< std::shared_ptr<MapEntry> > ()); }
#line 1659 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 409 "Parser/Parser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<MapEntry>> > ().push_back(yystack_[0].value.as< std::shared_ptr<MapEntry> > ()); yylhs.value.as< std::vector<std::shared_ptr<MapEntry>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<MapEntry>> > ()); }
#line 1665 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 413 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MemberExpr> > () = MemberExpr::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1671 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 417 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<SubscriptExpr> > () = SubscriptExpr::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1677 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 421 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CallExpr> > () = CallExpr::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), std::vector<std::shared_ptr<Expr>>{}); }
#line 1683 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 422 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CallExpr> > () = CallExpr::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1689 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 426 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullConditionalOperator> > () = NullConditionalOperator::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<Expr> > (), MemberExpr::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ())); }
#line 1695 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 427 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullConditionalOperator> > () = NullConditionalOperator::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Expr> > (), SubscriptExpr::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::shared_ptr<Expr> > ())); }
#line 1701 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 428 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullConditionalOperator> > () = NullConditionalOperator::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<Expr> > (), CallExpr::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<Expr> > (), std::vector<std::shared_ptr<Expr>>{})); }
#line 1707 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 429 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullConditionalOperator> > () = NullConditionalOperator::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Expr> > (), CallExpr::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::vector<std::shared_ptr<Expr>> > ())); }
#line 1713 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 433 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PreInc, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1719 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 434 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PreDec, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1725 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 435 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PostInc, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1731 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 436 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PostDec, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1737 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 437 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::Plus, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1743 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 438 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::Minus, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1749 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 439 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::LogicalNot, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1755 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 443 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::Add; }
#line 1761 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 444 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::Subtract; }
#line 1767 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 445 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::Multiply; }
#line 1773 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 446 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::Divide; }
#line 1779 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 447 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::Mod; }
#line 1785 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 448 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::Equal; }
#line 1791 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 449 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::NotEqual; }
#line 1797 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 450 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::LogicalAnd; }
#line 1803 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 451 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::LogicalOr; }
#line 1809 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 452 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::GreaterThan; }
#line 1815 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 453 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::GreaterThanOrEqual; }
#line 1821 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 454 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::LessThan; }
#line 1827 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 455 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::LessThanOrEqual; }
#line 1833 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 456 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::NullCoalescing; }
#line 1839 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 460 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), yystack_[1].value.as< BinaryOperatorKind > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1845 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 464 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ConditionalOperator> > () = ConditionalOperator::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1851 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 468 "Parser/Parser.yy" // lalr1.cc:859
    { }
#line 1857 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 472 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Assign, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1863 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 476 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Expr>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1869 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 477 "Parser/Parser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<Expr>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Expr> > ()); yylhs.value.as< std::vector<std::shared_ptr<Expr>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1875 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 481 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<Expr> > (); }
#line 1881 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 482 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<BinaryOperator> > (); }
#line 1887 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 483 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<BinaryOperator> > (); }
#line 1893 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 484 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<UnaryOperator> > (); }
#line 1899 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 485 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<ConditionalOperator> > (); }
#line 1905 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 486 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<FunctionExpr> > (); }
#line 1911 "Parser/Parser.cpp" // lalr1.cc:859
    break;


#line 1915 "Parser/Parser.cpp" // lalr1.cc:859
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
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const signed char Parser::yypact_ninf_ = -116;

  const signed char Parser::yytable_ninf_ = -60;

  const short int
  Parser::yypact_[] =
  {
      63,   -31,   -22,    50,    63,  -116,  -116,  -116,    37,    39,
    -116,  -116,   -17,    46,   -14,    34,    53,    52,  -116,     7,
    -116,  -116,    31,    77,  -116,    55,  -116,    68,    71,    78,
      78,    94,    82,   -12,   -12,   -12,   -12,   -12,   399,  -116,
     289,    91,   340,     5,    38,   119,   120,   121,   232,  -116,
    -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,   181,  -116,
    -116,  -116,  -116,  -116,  -116,   116,   117,   118,  -116,   100,
    -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,
    -116,  -116,   451,    13,    22,  -116,  -116,  -116,  -116,  -116,
    -116,  -116,    78,  -116,    45,    45,    45,    45,    45,   473,
    -116,   123,  -116,   122,   124,   497,  -116,    37,  -116,   519,
     104,   104,   399,   399,   283,  -116,  -116,  -116,  -116,  -116,
    -116,  -116,  -116,   348,   399,   106,    92,   399,   399,  -116,
    -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,
    -116,  -116,  -116,  -116,   399,   399,    78,   399,    78,  -116,
      92,  -116,  -116,   399,   128,   399,   129,   399,    46,  -116,
    -116,    56,  -116,    72,   541,   565,  -116,    42,    44,   114,
     399,   115,   130,   589,  -116,    76,   771,   611,  -116,   391,
     399,   113,   645,   771,   792,   771,   161,   771,   162,  -116,
     497,  -116,   771,  -116,   771,  -116,   163,   104,   164,   232,
     232,   104,    40,   104,  -116,   667,   399,  -116,  -116,  -116,
     399,  -116,  -116,    80,   689,  -116,   399,   399,   399,   399,
    -116,   399,   125,  -116,    86,    97,   399,   723,  -116,  -116,
     792,   771,   771,   771,   771,   232,  -116,  -116,   747,   232,
    -116,   232,  -116,  -116
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       2,     0,     0,     0,     3,     4,     7,     6,     0,     0,
       1,     5,     0,     0,     0,    10,    18,     0,    16,     0,
       8,    21,     0,     0,    25,     0,    23,     0,     0,     0,
       0,    12,     0,     0,     0,     0,     0,     0,     0,    39,
       0,    14,     0,     0,     0,     0,     0,     0,     0,    89,
      80,    74,    75,    76,    77,   137,    41,    28,     0,    30,
      34,    35,    36,    37,    38,     0,     0,     0,    78,   132,
      81,    79,    82,    83,    85,    86,    84,    87,   135,   134,
     136,   133,     0,    59,    63,    22,    24,    26,    27,    20,
      11,    19,     0,    17,   110,   109,   105,   106,   111,     0,
      90,     0,    95,    72,    72,   130,    15,     0,    43,     0,
       0,     0,     0,     0,     0,    58,    40,    42,    31,    32,
      33,   107,   108,     0,     0,     0,   128,     0,     0,   113,
     112,   114,   115,   116,   119,   120,   117,   118,   124,   122,
     123,   121,    29,   125,     0,     0,     0,     0,     0,    13,
       0,    88,    92,    73,     0,    73,     0,     0,     0,    44,
      71,     0,    69,     0,     0,     0,    49,     0,     0,    80,
       0,     0,     0,     0,    99,     0,   130,     0,    97,     0,
       0,     0,     0,   129,   126,    60,    61,    64,    65,    96,
       0,    93,   131,    91,    94,     9,     0,     0,     0,     0,
       0,     0,    54,     0,    55,     0,     0,    51,    50,   100,
       0,    98,   103,     0,     0,   101,     0,     0,     0,     0,
      70,     0,    45,    47,     0,     0,     0,     0,   104,   102,
     127,    62,    66,    67,    68,     0,    56,    57,     0,     0,
      46,     0,    52,    48
  };

  const short int
  Parser::yypgoto_[] =
  {
    -116,  -116,  -116,   166,     4,  -116,    64,  -116,  -116,   140,
     -24,  -116,  -116,   149,   -48,   -11,  -116,  -116,  -116,  -116,
    -116,  -116,  -116,  -116,  -116,   -10,     6,  -116,  -104,   -21,
      73,  -116,   103,  -116,  -116,  -116,  -116,    25,  -116,  -116,
    -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,  -115,
     -37
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,     5,     6,    55,    13,   107,    17,    18,
      90,     7,    25,    26,    56,    57,    58,    59,    60,    61,
      62,   170,    63,   171,    64,    65,    66,    67,   161,   162,
     154,    68,    69,    70,    71,    72,    73,   102,   103,    74,
      75,    76,    77,    78,   144,    79,    80,   127,    81,   104,
      82
  };

  const short int
  Parser::yytable_[] =
  {
     115,    99,    20,   105,    27,   109,    91,   163,   175,    15,
     117,    33,    34,    38,    21,    27,   145,    40,    24,     8,
      28,    35,    36,    37,     1,   147,    22,    23,     9,    24,
     110,    28,    38,    16,    19,    39,    40,    49,    50,    51,
      52,    53,    54,   145,   146,    41,    42,    43,    44,    45,
      10,    46,    47,   148,    48,    83,    49,    50,    51,    52,
      53,    54,    12,   111,   213,    29,    14,   201,   149,   203,
     123,   146,   -59,    19,   124,   164,   165,   173,    31,   125,
     150,    83,   196,    85,    30,    32,   176,   177,    84,   197,
     182,   183,   202,     1,   204,    22,    23,   224,   198,   225,
      87,     1,   209,    88,   172,   197,   228,   184,   185,   210,
     187,     2,   236,   210,   121,   122,   190,   179,   192,   197,
     194,   180,   186,   237,   188,   123,   181,    84,    89,   124,
     197,    92,    16,   205,   125,   126,    94,    95,    96,    97,
      98,   106,   176,   214,   112,   113,   114,   195,   118,   119,
     120,   222,   223,   152,   160,   153,   178,   155,   191,   193,
     -53,   206,   207,   215,   217,   218,   219,   221,   235,   227,
      11,   158,    93,   192,    86,     0,   220,   156,   189,   230,
     231,   232,   233,     0,   234,    33,    34,   240,     0,   238,
       0,   242,     0,   243,     0,    35,    36,    37,     0,     0,
       0,     0,     0,     0,     0,     0,    38,     0,    19,   116,
      40,     0,     0,     0,     0,     0,     0,     0,     0,    41,
      42,    43,    44,    45,     0,    46,    47,     0,    48,     0,
      49,    50,    51,    52,    53,    54,    33,    34,     0,     0,
       0,     0,     0,     0,     0,     0,    35,    36,    37,     0,
       0,     0,     0,     0,     0,     0,     0,    38,     0,    19,
       0,    40,     0,     0,     0,     0,     0,     0,     0,     0,
      41,    42,    43,    44,    45,     0,    46,    47,     0,    48,
       0,    49,    50,    51,    52,    53,    54,    33,    34,     0,
       0,     0,     0,    33,    34,     0,     0,    35,    36,    37,
       0,     0,     0,    35,    36,    37,     0,     0,    38,     0,
       0,     0,    40,     0,    38,   166,     0,     0,    40,   100,
     101,    41,     0,   167,   168,     0,     0,    41,     0,     0,
       0,     0,    49,   169,    51,    52,    53,    54,    49,    50,
      51,    52,    53,    54,    33,    34,     0,     0,     0,     0,
       0,     0,    33,    34,    35,    36,    37,     0,     0,     0,
       0,     0,    35,    36,    37,    38,     0,     0,     0,    40,
       0,     0,   108,    38,   174,     0,     0,    40,    41,     0,
       0,     0,     0,     0,     0,     0,    41,     0,     0,    49,
      50,    51,    52,    53,    54,    33,    34,    49,    50,    51,
      52,    53,    54,    33,    34,    35,    36,    37,     0,     0,
       0,     0,     0,    35,    36,    37,    38,   212,     0,     0,
      40,     0,     0,     0,    38,     0,     0,     0,    40,    41,
       0,     0,     0,     0,     0,     0,     0,    41,     0,     0,
      49,    50,    51,    52,    53,    54,     0,     0,    49,    50,
      51,    52,    53,    54,   128,   129,   130,   131,   132,   133,
       0,     0,     0,     0,     0,     0,     0,     0,   134,   135,
     136,   137,   138,   139,   140,   141,   128,   129,   130,   131,
     132,   133,     0,   142,     0,     0,     0,   143,     0,     0,
     134,   135,   136,   137,   138,   139,   140,   141,     0,   151,
     128,   129,   130,   131,   132,   133,     0,     0,     0,   143,
       0,     0,     0,     0,   134,   135,   136,   137,   138,   139,
     140,   141,   128,   129,   130,   131,   132,   133,   157,     0,
       0,     0,     0,   143,     0,     0,   134,   135,   136,   137,
     138,   139,   140,   141,   128,   129,   130,   131,   132,   133,
       0,   159,     0,     0,     0,   143,     0,     0,   134,   135,
     136,   137,   138,   139,   140,   141,     0,   199,   128,   129,
     130,   131,   132,   133,     0,     0,     0,   143,     0,     0,
       0,     0,   134,   135,   136,   137,   138,   139,   140,   141,
       0,   200,   128,   129,   130,   131,   132,   133,     0,     0,
       0,   143,     0,     0,     0,     0,   134,   135,   136,   137,
     138,   139,   140,   141,   128,   129,   130,   131,   132,   133,
       0,   208,     0,     0,     0,   143,     0,     0,   134,   135,
     136,   137,   138,   139,   140,   141,     0,     0,     0,     0,
       0,   211,     0,     0,     0,     0,     0,   143,   128,   129,
     130,   131,   132,   133,     0,     0,     0,     0,     0,     0,
       0,     0,   134,   135,   136,   137,   138,   139,   140,   141,
     128,   129,   130,   131,   132,   133,   216,     0,     0,     0,
       0,   143,     0,     0,   134,   135,   136,   137,   138,   139,
     140,   141,   128,   129,   130,   131,   132,   133,     0,   226,
       0,     0,     0,   143,     0,     0,   134,   135,   136,   137,
     138,   139,   140,   141,     0,     0,     0,     0,     0,   229,
       0,     0,     0,     0,     0,   143,   128,   129,   130,   131,
     132,   133,     0,     0,     0,     0,     0,     0,     0,     0,
     134,   135,   136,   137,   138,   139,   140,   141,     0,   239,
     128,   129,   130,   131,   132,   133,     0,     0,     0,   143,
       0,     0,     0,     0,   134,   135,   136,   137,   138,   139,
     140,   141,     0,   241,   128,   129,   130,   131,   132,   133,
       0,     0,     0,   143,     0,     0,     0,     0,   134,   135,
     136,   137,   138,   139,   140,   141,   129,   130,   131,   132,
     133,     0,     0,     0,     0,     0,     0,   143,     0,   134,
     135,   136,   137,   138,   139,   140,   141,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   143
  };

  const short int
  Parser::yycheck_[] =
  {
      48,    38,    13,    40,    14,    42,    30,   111,   123,    26,
      58,     4,     5,    25,    28,    25,     3,    29,    14,    50,
      14,    14,    15,    16,    38,     3,    40,    41,    50,    25,
      25,    25,    25,    50,    27,    28,    29,    49,    50,    51,
      52,    53,    54,     3,    31,    38,    39,    40,    41,    42,
       0,    44,    45,    31,    47,    50,    49,    50,    51,    52,
      53,    54,    25,    25,   179,    31,    27,    25,    92,    25,
      25,    31,    32,    27,    29,   112,   113,   114,    26,    34,
      35,    50,    26,    28,    31,    33,   123,   124,    50,    33,
     127,   128,    50,    38,    50,    40,    41,   201,    26,   203,
      32,    38,    26,    32,   114,    33,    26,   144,   145,    33,
     147,    48,    26,    33,    14,    15,   153,    25,   155,    33,
     157,    29,   146,    26,   148,    25,    34,    50,    50,    29,
      33,    37,    50,   170,    34,    35,    33,    34,    35,    36,
      37,    50,   179,   180,    25,    25,    25,   158,    32,    32,
      32,   199,   200,    30,    50,    33,    50,    33,    30,    30,
      46,    46,    32,    50,     3,     3,     3,     3,    43,   206,
       4,   107,    32,   210,    25,    -1,   197,   104,   153,   216,
     217,   218,   219,    -1,   221,     4,     5,   235,    -1,   226,
      -1,   239,    -1,   241,    -1,    14,    15,    16,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    28,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      39,    40,    41,    42,    -1,    44,    45,    -1,    47,    -1,
      49,    50,    51,    52,    53,    54,     4,     5,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    14,    15,    16,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,
      -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    -1,    44,    45,    -1,    47,
      -1,    49,    50,    51,    52,    53,    54,     4,     5,    -1,
      -1,    -1,    -1,     4,     5,    -1,    -1,    14,    15,    16,
      -1,    -1,    -1,    14,    15,    16,    -1,    -1,    25,    -1,
      -1,    -1,    29,    -1,    25,    32,    -1,    -1,    29,    30,
      31,    38,    -1,    40,    41,    -1,    -1,    38,    -1,    -1,
      -1,    -1,    49,    50,    51,    52,    53,    54,    49,    50,
      51,    52,    53,    54,     4,     5,    -1,    -1,    -1,    -1,
      -1,    -1,     4,     5,    14,    15,    16,    -1,    -1,    -1,
      -1,    -1,    14,    15,    16,    25,    -1,    -1,    -1,    29,
      -1,    -1,    32,    25,    26,    -1,    -1,    29,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    49,
      50,    51,    52,    53,    54,     4,     5,    49,    50,    51,
      52,    53,    54,     4,     5,    14,    15,    16,    -1,    -1,
      -1,    -1,    -1,    14,    15,    16,    25,    26,    -1,    -1,
      29,    -1,    -1,    -1,    25,    -1,    -1,    -1,    29,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,
      49,    50,    51,    52,    53,    54,    -1,    -1,    49,    50,
      51,    52,    53,    54,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,     3,     4,     5,     6,
       7,     8,    -1,    32,    -1,    -1,    -1,    36,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,    -1,    26,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,     3,     4,     5,     6,     7,     8,    31,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,     3,     4,     5,     6,     7,     8,
      -1,    32,    -1,    -1,    -1,    36,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    -1,    26,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    36,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,     3,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,     3,     4,     5,     6,     7,     8,
      -1,    32,    -1,    -1,    -1,    36,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    -1,    -1,    -1,    -1,    -1,    36,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
       3,     4,     5,     6,     7,     8,    31,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,     3,     4,     5,     6,     7,     8,    -1,    32,
      -1,    -1,    -1,    36,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    -1,    -1,    -1,    -1,    36,     3,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,    -1,    26,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    -1,    26,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    17,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,    38,    48,    63,    64,    65,    66,    73,    50,    50,
       0,    65,    25,    68,    27,    26,    50,    70,    71,    27,
      77,    28,    40,    41,    66,    74,    75,    87,    88,    31,
      31,    26,    33,     4,     5,    14,    15,    16,    25,    28,
      29,    38,    39,    40,    41,    42,    44,    45,    47,    49,
      50,    51,    52,    53,    54,    67,    76,    77,    78,    79,
      80,    81,    82,    84,    86,    87,    88,    89,    93,    94,
      95,    96,    97,    98,   101,   102,   103,   104,   105,   107,
     108,   110,   112,    50,    50,    28,    75,    32,    32,    50,
      72,    72,    37,    71,    94,    94,    94,    94,    94,   112,
      30,    31,    99,   100,   111,   112,    50,    69,    32,   112,
      25,    25,    25,    25,    25,    76,    28,    76,    32,    32,
      32,    14,    15,    25,    29,    34,    35,   109,     3,     4,
       5,     6,     7,     8,    17,    18,    19,    20,    21,    22,
      23,    24,    32,    36,   106,     3,    31,     3,    31,    72,
      35,    26,    30,    33,    92,    33,    92,    31,    68,    32,
      50,    90,    91,    90,   112,   112,    32,    40,    41,    50,
      83,    85,    87,   112,    26,   111,   112,   112,    50,    25,
      29,    34,   112,   112,   112,   112,    72,   112,    72,    99,
     112,    30,   112,    30,   112,    77,    26,    33,    26,    26,
      26,    25,    50,    25,    50,   112,    46,    32,    32,    26,
      33,    30,    26,   111,   112,    50,    31,     3,     3,     3,
      91,     3,    76,    76,    90,    90,    32,   112,    26,    30,
     112,   112,   112,   112,   112,    43,    26,    26,   112,    26,
      76,    26,    76,    76
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    62,    63,    63,    64,    64,    65,    65,    66,    67,
      68,    68,    68,    68,    69,    69,    70,    70,    71,    71,
      72,    73,    73,    74,    74,    75,    75,    75,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    77,
      77,    78,    78,    79,    79,    80,    80,    81,    82,    83,
      83,    83,    84,    85,    85,    85,    85,    85,    86,    87,
      87,    87,    87,    88,    88,    88,    88,    89,    89,    90,
      90,    91,    92,    92,    93,    93,    93,    93,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    95,    96,
      97,    97,    98,    98,    99,   100,   100,   101,   102,   103,
     103,   104,   104,   104,   104,   105,   105,   105,   105,   105,
     105,   105,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   107,   108,   109,   110,
     111,   111,   112,   112,   112,   112,   112,   112
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     0,     1,     1,     2,     1,     1,     4,     4,
       2,     4,     3,     5,     0,     1,     1,     3,     1,     3,
       1,     4,     5,     1,     2,     1,     2,     2,     1,     2,
       1,     2,     2,     2,     1,     1,     1,     1,     1,     2,
       3,     1,     2,     2,     3,     5,     7,     5,     8,     1,
       2,     2,     7,     1,     2,     2,     4,     4,     2,     2,
       4,     4,     6,     2,     4,     4,     6,     6,     6,     1,
       3,     1,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       2,     4,     3,     4,     3,     1,     3,     3,     4,     3,
       4,     4,     5,     4,     5,     2,     2,     2,     2,     2,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     5,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"=\"", "\"-\"", "\"+\"",
  "\"*\"", "\"/\"", "\"%\"", "\"-=\"", "\"+=\"", "\"*=\"", "\"/=\"",
  "\"%=\"", "\"++\"", "\"--\"", "\"!\"", "\"&&\"", "\"||\"", "\"==\"",
  "\"!=\"", "\"<=\"", "\">=\"", "\"<\"", "\">\"", "\"(\"", "\")\"",
  "\"{\"", "\"}\"", "\"[\"", "\"]\"", "\":\"", "\";\"", "\",\"", "\".\"",
  "\"?\"", "\"??\"", "\"->\"", "\"func\"", "\"return\"", "\"let\"",
  "\"const\"", "\"if\"", "\"else\"", "\"while\"", "\"for\"", "\"in\"",
  "\"defer\"", "\"class\"", "\"null\"", "\"identifier\"",
  "\"integer_literal\"", "\"double_literal\"", "\"bool_literal\"",
  "\"string_literal\"", "\"conditional_expression\"", "\"binary_op\"",
  "\"unary_plus\"", "\"unary_minus\"", "\"ternary_question\"",
  "\"grouping\"", "\"then\"", "$accept", "translation_unit",
  "translation_unit_declarations", "translation_unit_declaration",
  "function_definition", "function_expression", "call_signature",
  "binding_identifier", "parameter_variables", "parameter_variable",
  "type_specifier", "class_declaration", "member_declaration_list",
  "member_declaration", "statement", "compound_statement",
  "statement_list", "return_statement", "if_statement", "while_statement",
  "for_statement", "for_init_statement", "for_range_statement",
  "for_range_init", "defer_statement", "variable_definition",
  "const_definition", "decomposition_definition", "binding_declarations",
  "binding_declaration", "comma_opt", "literal", "primary_expression",
  "parenthesized_expression", "null_literal", "array_literal",
  "map_literal", "map_entry", "map_entry_list", "member_expression",
  "subscript_expression", "call_expression", "null_conditional_expression",
  "unary_expression", "binary_op", "binary_expression",
  "conditional_expression", "ternary_question", "assignment_expression",
  "expression_list", "expression", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   204,   204,   205,   209,   210,   214,   215,   219,   223,
     227,   228,   229,   230,   234,   235,   239,   240,   244,   245,
     249,   253,   254,   258,   259,   263,   264,   265,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   283,
     284,   288,   289,   293,   294,   298,   299,   303,   307,   311,
     312,   313,   317,   321,   322,   323,   324,   325,   329,   333,
     334,   335,   336,   340,   341,   342,   343,   347,   348,   352,
     353,   357,   361,   362,   366,   367,   368,   369,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   386,   390,
     394,   395,   399,   400,   404,   408,   409,   413,   417,   421,
     422,   426,   427,   428,   429,   433,   434,   435,   436,   437,
     438,   439,   443,   444,   445,   446,   447,   448,   449,   450,
     451,   452,   453,   454,   455,   456,   460,   464,   468,   472,
     476,   477,   481,   482,   483,   484,   485,   486
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
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
  Parser::yy_reduce_print_ (int yyrule)
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
#line 2589 "Parser/Parser.cpp" // lalr1.cc:1167
#line 489 "Parser/Parser.yy" // lalr1.cc:1168


void yy::Parser::error(const location_type& l, const std::string& m)
{
    driver.error(toLoc(l), m);
}
