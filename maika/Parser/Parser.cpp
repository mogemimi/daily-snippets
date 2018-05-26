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
      case 104: // binary_op
        value.move< BinaryOperatorKind > (that.value);
        break;

      case 67: // call_signature
        value.move< CallSignature > (that.value);
        break;

      case 95: // array_literal
        value.move< std::shared_ptr<ArrayLiteral> > (that.value);
        break;

      case 105: // binary_expression
      case 108: // assignment_expression
        value.move< std::shared_ptr<BinaryOperator> > (that.value);
        break;

      case 89: // binding_declaration
        value.move< std::shared_ptr<BindingDecl> > (that.value);
        break;

      case 52: // "bool_literal"
        value.move< std::shared_ptr<BoolLiteral> > (that.value);
        break;

      case 101: // call_expression
        value.move< std::shared_ptr<CallExpr> > (that.value);
        break;

      case 72: // class_declaration
        value.move< std::shared_ptr<ClassDecl> > (that.value);
        break;

      case 76: // compound_statement
        value.move< std::shared_ptr<CompoundStmt> > (that.value);
        break;

      case 106: // conditional_expression
        value.move< std::shared_ptr<ConditionalOperator> > (that.value);
        break;

      case 86: // const_definition
        value.move< std::shared_ptr<ConstDecl> > (that.value);
        break;

      case 64: // translation_unit_declaration
      case 74: // member_declaration
      case 84: // for_range_init
        value.move< std::shared_ptr<Decl> > (that.value);
        break;

      case 87: // decomposition_definition
        value.move< std::shared_ptr<DecompositionDecl> > (that.value);
        break;

      case 51: // "double_literal"
        value.move< std::shared_ptr<DoubleLiteral> > (that.value);
        break;

      case 91: // literal
      case 92: // primary_expression
      case 110: // expression
        value.move< std::shared_ptr<Expr> > (that.value);
        break;

      case 83: // for_range_statement
        value.move< std::shared_ptr<ForRangeStmt> > (that.value);
        break;

      case 81: // for_statement
        value.move< std::shared_ptr<ForStmt> > (that.value);
        break;

      case 65: // function_definition
        value.move< std::shared_ptr<FunctionDecl> > (that.value);
        break;

      case 66: // function_expression
        value.move< std::shared_ptr<FunctionExpr> > (that.value);
        break;

      case 79: // if_statement
        value.move< std::shared_ptr<IfStmt> > (that.value);
        break;

      case 50: // "integer_literal"
        value.move< std::shared_ptr<IntegerLiteral> > (that.value);
        break;

      case 97: // map_entry
        value.move< std::shared_ptr<MapEntry> > (that.value);
        break;

      case 96: // map_literal
        value.move< std::shared_ptr<MapLiteral> > (that.value);
        break;

      case 99: // member_expression
        value.move< std::shared_ptr<MemberExpr> > (that.value);
        break;

      case 49: // "identifier"
      case 68: // binding_identifier
      case 71: // type_specifier
        value.move< std::shared_ptr<NamedDecl> > (that.value);
        break;

      case 102: // null_conditional_expression
        value.move< std::shared_ptr<NullConditionalOperator> > (that.value);
        break;

      case 94: // null_literal
        value.move< std::shared_ptr<NullLiteral> > (that.value);
        break;

      case 93: // parenthesized_expression
        value.move< std::shared_ptr<ParenExpr> > (that.value);
        break;

      case 70: // parameter_variable
        value.move< std::shared_ptr<ParmVarDecl> > (that.value);
        break;

      case 78: // return_statement
        value.move< std::shared_ptr<ReturnStmt> > (that.value);
        break;

      case 75: // statement
      case 82: // for_init_statement
        value.move< std::shared_ptr<Stmt> > (that.value);
        break;

      case 53: // "string_literal"
        value.move< std::shared_ptr<StringLiteral> > (that.value);
        break;

      case 100: // subscript_expression
        value.move< std::shared_ptr<SubscriptExpr> > (that.value);
        break;

      case 62: // translation_unit
        value.move< std::shared_ptr<TranslationUnitDecl> > (that.value);
        break;

      case 103: // unary_expression
        value.move< std::shared_ptr<UnaryOperator> > (that.value);
        break;

      case 85: // variable_definition
        value.move< std::shared_ptr<VariableDecl> > (that.value);
        break;

      case 80: // while_statement
        value.move< std::shared_ptr<WhileStmt> > (that.value);
        break;

      case 88: // binding_declarations
        value.move< std::vector<std::shared_ptr<BindingDecl>> > (that.value);
        break;

      case 63: // translation_unit_declarations
      case 73: // member_declaration_list
        value.move< std::vector<std::shared_ptr<Decl>> > (that.value);
        break;

      case 109: // expression_list
        value.move< std::vector<std::shared_ptr<Expr>> > (that.value);
        break;

      case 98: // map_entry_list
        value.move< std::vector<std::shared_ptr<MapEntry>> > (that.value);
        break;

      case 69: // parameter_variables
        value.move< std::vector<std::shared_ptr<ParmVarDecl>> > (that.value);
        break;

      case 77: // statement_list
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
      case 104: // binary_op
        value.copy< BinaryOperatorKind > (that.value);
        break;

      case 67: // call_signature
        value.copy< CallSignature > (that.value);
        break;

      case 95: // array_literal
        value.copy< std::shared_ptr<ArrayLiteral> > (that.value);
        break;

      case 105: // binary_expression
      case 108: // assignment_expression
        value.copy< std::shared_ptr<BinaryOperator> > (that.value);
        break;

      case 89: // binding_declaration
        value.copy< std::shared_ptr<BindingDecl> > (that.value);
        break;

      case 52: // "bool_literal"
        value.copy< std::shared_ptr<BoolLiteral> > (that.value);
        break;

      case 101: // call_expression
        value.copy< std::shared_ptr<CallExpr> > (that.value);
        break;

      case 72: // class_declaration
        value.copy< std::shared_ptr<ClassDecl> > (that.value);
        break;

      case 76: // compound_statement
        value.copy< std::shared_ptr<CompoundStmt> > (that.value);
        break;

      case 106: // conditional_expression
        value.copy< std::shared_ptr<ConditionalOperator> > (that.value);
        break;

      case 86: // const_definition
        value.copy< std::shared_ptr<ConstDecl> > (that.value);
        break;

      case 64: // translation_unit_declaration
      case 74: // member_declaration
      case 84: // for_range_init
        value.copy< std::shared_ptr<Decl> > (that.value);
        break;

      case 87: // decomposition_definition
        value.copy< std::shared_ptr<DecompositionDecl> > (that.value);
        break;

      case 51: // "double_literal"
        value.copy< std::shared_ptr<DoubleLiteral> > (that.value);
        break;

      case 91: // literal
      case 92: // primary_expression
      case 110: // expression
        value.copy< std::shared_ptr<Expr> > (that.value);
        break;

      case 83: // for_range_statement
        value.copy< std::shared_ptr<ForRangeStmt> > (that.value);
        break;

      case 81: // for_statement
        value.copy< std::shared_ptr<ForStmt> > (that.value);
        break;

      case 65: // function_definition
        value.copy< std::shared_ptr<FunctionDecl> > (that.value);
        break;

      case 66: // function_expression
        value.copy< std::shared_ptr<FunctionExpr> > (that.value);
        break;

      case 79: // if_statement
        value.copy< std::shared_ptr<IfStmt> > (that.value);
        break;

      case 50: // "integer_literal"
        value.copy< std::shared_ptr<IntegerLiteral> > (that.value);
        break;

      case 97: // map_entry
        value.copy< std::shared_ptr<MapEntry> > (that.value);
        break;

      case 96: // map_literal
        value.copy< std::shared_ptr<MapLiteral> > (that.value);
        break;

      case 99: // member_expression
        value.copy< std::shared_ptr<MemberExpr> > (that.value);
        break;

      case 49: // "identifier"
      case 68: // binding_identifier
      case 71: // type_specifier
        value.copy< std::shared_ptr<NamedDecl> > (that.value);
        break;

      case 102: // null_conditional_expression
        value.copy< std::shared_ptr<NullConditionalOperator> > (that.value);
        break;

      case 94: // null_literal
        value.copy< std::shared_ptr<NullLiteral> > (that.value);
        break;

      case 93: // parenthesized_expression
        value.copy< std::shared_ptr<ParenExpr> > (that.value);
        break;

      case 70: // parameter_variable
        value.copy< std::shared_ptr<ParmVarDecl> > (that.value);
        break;

      case 78: // return_statement
        value.copy< std::shared_ptr<ReturnStmt> > (that.value);
        break;

      case 75: // statement
      case 82: // for_init_statement
        value.copy< std::shared_ptr<Stmt> > (that.value);
        break;

      case 53: // "string_literal"
        value.copy< std::shared_ptr<StringLiteral> > (that.value);
        break;

      case 100: // subscript_expression
        value.copy< std::shared_ptr<SubscriptExpr> > (that.value);
        break;

      case 62: // translation_unit
        value.copy< std::shared_ptr<TranslationUnitDecl> > (that.value);
        break;

      case 103: // unary_expression
        value.copy< std::shared_ptr<UnaryOperator> > (that.value);
        break;

      case 85: // variable_definition
        value.copy< std::shared_ptr<VariableDecl> > (that.value);
        break;

      case 80: // while_statement
        value.copy< std::shared_ptr<WhileStmt> > (that.value);
        break;

      case 88: // binding_declarations
        value.copy< std::vector<std::shared_ptr<BindingDecl>> > (that.value);
        break;

      case 63: // translation_unit_declarations
      case 73: // member_declaration_list
        value.copy< std::vector<std::shared_ptr<Decl>> > (that.value);
        break;

      case 109: // expression_list
        value.copy< std::vector<std::shared_ptr<Expr>> > (that.value);
        break;

      case 98: // map_entry_list
        value.copy< std::vector<std::shared_ptr<MapEntry>> > (that.value);
        break;

      case 69: // parameter_variables
        value.copy< std::vector<std::shared_ptr<ParmVarDecl>> > (that.value);
        break;

      case 77: // statement_list
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

#line 798 "Parser/Parser.cpp" // lalr1.cc:745

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
      case 104: // binary_op
        yylhs.value.build< BinaryOperatorKind > ();
        break;

      case 67: // call_signature
        yylhs.value.build< CallSignature > ();
        break;

      case 95: // array_literal
        yylhs.value.build< std::shared_ptr<ArrayLiteral> > ();
        break;

      case 105: // binary_expression
      case 108: // assignment_expression
        yylhs.value.build< std::shared_ptr<BinaryOperator> > ();
        break;

      case 89: // binding_declaration
        yylhs.value.build< std::shared_ptr<BindingDecl> > ();
        break;

      case 52: // "bool_literal"
        yylhs.value.build< std::shared_ptr<BoolLiteral> > ();
        break;

      case 101: // call_expression
        yylhs.value.build< std::shared_ptr<CallExpr> > ();
        break;

      case 72: // class_declaration
        yylhs.value.build< std::shared_ptr<ClassDecl> > ();
        break;

      case 76: // compound_statement
        yylhs.value.build< std::shared_ptr<CompoundStmt> > ();
        break;

      case 106: // conditional_expression
        yylhs.value.build< std::shared_ptr<ConditionalOperator> > ();
        break;

      case 86: // const_definition
        yylhs.value.build< std::shared_ptr<ConstDecl> > ();
        break;

      case 64: // translation_unit_declaration
      case 74: // member_declaration
      case 84: // for_range_init
        yylhs.value.build< std::shared_ptr<Decl> > ();
        break;

      case 87: // decomposition_definition
        yylhs.value.build< std::shared_ptr<DecompositionDecl> > ();
        break;

      case 51: // "double_literal"
        yylhs.value.build< std::shared_ptr<DoubleLiteral> > ();
        break;

      case 91: // literal
      case 92: // primary_expression
      case 110: // expression
        yylhs.value.build< std::shared_ptr<Expr> > ();
        break;

      case 83: // for_range_statement
        yylhs.value.build< std::shared_ptr<ForRangeStmt> > ();
        break;

      case 81: // for_statement
        yylhs.value.build< std::shared_ptr<ForStmt> > ();
        break;

      case 65: // function_definition
        yylhs.value.build< std::shared_ptr<FunctionDecl> > ();
        break;

      case 66: // function_expression
        yylhs.value.build< std::shared_ptr<FunctionExpr> > ();
        break;

      case 79: // if_statement
        yylhs.value.build< std::shared_ptr<IfStmt> > ();
        break;

      case 50: // "integer_literal"
        yylhs.value.build< std::shared_ptr<IntegerLiteral> > ();
        break;

      case 97: // map_entry
        yylhs.value.build< std::shared_ptr<MapEntry> > ();
        break;

      case 96: // map_literal
        yylhs.value.build< std::shared_ptr<MapLiteral> > ();
        break;

      case 99: // member_expression
        yylhs.value.build< std::shared_ptr<MemberExpr> > ();
        break;

      case 49: // "identifier"
      case 68: // binding_identifier
      case 71: // type_specifier
        yylhs.value.build< std::shared_ptr<NamedDecl> > ();
        break;

      case 102: // null_conditional_expression
        yylhs.value.build< std::shared_ptr<NullConditionalOperator> > ();
        break;

      case 94: // null_literal
        yylhs.value.build< std::shared_ptr<NullLiteral> > ();
        break;

      case 93: // parenthesized_expression
        yylhs.value.build< std::shared_ptr<ParenExpr> > ();
        break;

      case 70: // parameter_variable
        yylhs.value.build< std::shared_ptr<ParmVarDecl> > ();
        break;

      case 78: // return_statement
        yylhs.value.build< std::shared_ptr<ReturnStmt> > ();
        break;

      case 75: // statement
      case 82: // for_init_statement
        yylhs.value.build< std::shared_ptr<Stmt> > ();
        break;

      case 53: // "string_literal"
        yylhs.value.build< std::shared_ptr<StringLiteral> > ();
        break;

      case 100: // subscript_expression
        yylhs.value.build< std::shared_ptr<SubscriptExpr> > ();
        break;

      case 62: // translation_unit
        yylhs.value.build< std::shared_ptr<TranslationUnitDecl> > ();
        break;

      case 103: // unary_expression
        yylhs.value.build< std::shared_ptr<UnaryOperator> > ();
        break;

      case 85: // variable_definition
        yylhs.value.build< std::shared_ptr<VariableDecl> > ();
        break;

      case 80: // while_statement
        yylhs.value.build< std::shared_ptr<WhileStmt> > ();
        break;

      case 88: // binding_declarations
        yylhs.value.build< std::vector<std::shared_ptr<BindingDecl>> > ();
        break;

      case 63: // translation_unit_declarations
      case 73: // member_declaration_list
        yylhs.value.build< std::vector<std::shared_ptr<Decl>> > ();
        break;

      case 109: // expression_list
        yylhs.value.build< std::vector<std::shared_ptr<Expr>> > ();
        break;

      case 98: // map_entry_list
        yylhs.value.build< std::vector<std::shared_ptr<MapEntry>> > ();
        break;

      case 69: // parameter_variables
        yylhs.value.build< std::vector<std::shared_ptr<ParmVarDecl>> > ();
        break;

      case 77: // statement_list
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
#line 200 "Parser/Parser.yy" // lalr1.cc:859
    { driver.ast.translationUnit = TranslationUnitDecl::make(toLoc(yylhs.location), std::vector<std::shared_ptr<Decl>>{}); }
#line 1089 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 201 "Parser/Parser.yy" // lalr1.cc:859
    { driver.ast.translationUnit = TranslationUnitDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::vector<std::shared_ptr<Decl>> > ()); }
#line 1095 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 205 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Decl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Decl> > ()); }
#line 1101 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 206 "Parser/Parser.yy" // lalr1.cc:859
    { yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Decl> > ()); yylhs.value.as< std::vector<std::shared_ptr<Decl>> > () = std::move(yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ()); }
#line 1107 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 210 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[0].value.as< std::shared_ptr<ClassDecl> > (); }
#line 1113 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 211 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[0].value.as< std::shared_ptr<FunctionDecl> > (); }
#line 1119 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 215 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<FunctionDecl> > () = FunctionDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), std::get<0>(yystack_[1].value.as< CallSignature > ()), std::get<1>(yystack_[1].value.as< CallSignature > ()), yystack_[0].value.as< std::shared_ptr<CompoundStmt> > ()); }
#line 1125 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 219 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<FunctionExpr> > () = FunctionExpr::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), std::get<0>(yystack_[1].value.as< CallSignature > ()), std::get<1>(yystack_[1].value.as< CallSignature > ()), yystack_[0].value.as< std::shared_ptr<CompoundStmt> > ()); }
#line 1131 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 223 "Parser/Parser.yy" // lalr1.cc:859
    { std::get<1>(yylhs.value.as< CallSignature > ()) = nullptr; }
#line 1137 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 224 "Parser/Parser.yy" // lalr1.cc:859
    { std::get<1>(yylhs.value.as< CallSignature > ()) = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1143 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 225 "Parser/Parser.yy" // lalr1.cc:859
    { std::get<0>(yylhs.value.as< CallSignature > ()) = yystack_[1].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > (); std::get<1>(yylhs.value.as< CallSignature > ()) = nullptr; }
#line 1149 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 226 "Parser/Parser.yy" // lalr1.cc:859
    { std::get<0>(yylhs.value.as< CallSignature > ()) = yystack_[3].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > (); std::get<1>(yylhs.value.as< CallSignature > ()) = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1155 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 230 "Parser/Parser.yy" // lalr1.cc:859
    { }
#line 1161 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 231 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NamedDecl> > () = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1167 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 235 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<ParmVarDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<ParmVarDecl> > ()); }
#line 1173 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 236 "Parser/Parser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<ParmVarDecl> > ()); yylhs.value.as< std::vector<std::shared_ptr<ParmVarDecl>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > ()); }
#line 1179 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 240 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ParmVarDecl> > () = ParmVarDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1185 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 241 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ParmVarDecl> > () = ParmVarDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1191 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 245 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NamedDecl> > () = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1197 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 249 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ClassDecl> > () = ClassDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), std::vector<std::shared_ptr<Decl>>{}); }
#line 1203 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 250 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ClassDecl> > () = ClassDecl::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<NamedDecl> > (), yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ()); }
#line 1209 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 254 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Decl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Decl> > ()); }
#line 1215 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 255 "Parser/Parser.yy" // lalr1.cc:859
    { yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Decl> > ()); yylhs.value.as< std::vector<std::shared_ptr<Decl>> > () = std::move(yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ()); }
#line 1221 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 259 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[0].value.as< std::shared_ptr<FunctionDecl> > (); }
#line 1227 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 260 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[1].value.as< std::shared_ptr<VariableDecl> > (); }
#line 1233 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 261 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[1].value.as< std::shared_ptr<ConstDecl> > (); }
#line 1239 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 265 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<CompoundStmt> > (); }
#line 1245 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 266 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[1].value.as< std::shared_ptr<Expr> > (); }
#line 1251 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 267 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ReturnStmt> > (); }
#line 1257 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 268 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<VariableDecl> > ()); }
#line 1263 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 269 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<ConstDecl> > ()); }
#line 1269 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 270 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<DecompositionDecl> > ()); }
#line 1275 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 271 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<IfStmt> > (); }
#line 1281 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 272 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<WhileStmt> > (); }
#line 1287 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 273 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ForStmt> > (); }
#line 1293 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 274 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ForRangeStmt> > (); }
#line 1299 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 278 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CompoundStmt> > () = CompoundStmt::make(toLoc(yylhs.location), std::vector<std::shared_ptr<Stmt>>{}); }
#line 1305 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 279 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CompoundStmt> > () = CompoundStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ()); }
#line 1311 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 283 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Stmt>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1317 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 284 "Parser/Parser.yy" // lalr1.cc:859
    { yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Stmt> > ()); yylhs.value.as< std::vector<std::shared_ptr<Stmt>> > () = std::move(yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ()); }
#line 1323 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 288 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ReturnStmt> > () = ReturnStmt::make(toLoc(yylhs.location)); }
#line 1329 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 289 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ReturnStmt> > () = ReturnStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1335 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 293 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IfStmt> > () = IfStmt::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1341 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 294 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IfStmt> > () = IfStmt::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[2].value.as< std::shared_ptr<Stmt> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1347 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 298 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<WhileStmt> > () = WhileStmt::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1353 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 302 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ForStmt> > () = ForStmt::make(toLoc(yylhs.location), yystack_[5].value.as< std::shared_ptr<Stmt> > (), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1359 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 306 "Parser/Parser.yy" // lalr1.cc:859
    { }
#line 1365 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 307 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[1].value.as< std::shared_ptr<Expr> > (); }
#line 1371 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 308 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<VariableDecl> > ()); }
#line 1377 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 312 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ForRangeStmt> > () = ForRangeStmt::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Decl> > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1383 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 316 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1389 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 317 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > (), nullptr, nullptr); }
#line 1395 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 318 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = ConstDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > (), nullptr, nullptr); }
#line 1401 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 319 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = DecompositionDecl::make(toLoc(yylhs.location), yystack_[1].value.as< std::vector<std::shared_ptr<BindingDecl>> > ()); }
#line 1407 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 320 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = DecompositionDecl::make(toLoc(yylhs.location), yystack_[1].value.as< std::vector<std::shared_ptr<BindingDecl>> > ()); }
#line 1413 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 324 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VariableDecl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > (), nullptr, nullptr); }
#line 1419 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 325 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VariableDecl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), nullptr, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1425 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 326 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VariableDecl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > (), nullptr); }
#line 1431 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 327 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VariableDecl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<NamedDecl> > (), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1437 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 331 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ConstDecl> > () = ConstDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > (), nullptr, nullptr); }
#line 1443 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 332 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ConstDecl> > () = ConstDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), nullptr, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1449 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 333 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ConstDecl> > () = ConstDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > (), nullptr); }
#line 1455 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 334 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ConstDecl> > () = ConstDecl::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<NamedDecl> > (), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1461 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 338 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<DecompositionDecl> > () = DecompositionDecl::make(toLoc(yylhs.location), yystack_[3].value.as< std::vector<std::shared_ptr<BindingDecl>> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1467 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 339 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<DecompositionDecl> > () = DecompositionDecl::make(toLoc(yylhs.location), yystack_[3].value.as< std::vector<std::shared_ptr<BindingDecl>> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1473 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 343 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<BindingDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<BindingDecl> > ()); }
#line 1479 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 344 "Parser/Parser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<BindingDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<BindingDecl> > ()); yylhs.value.as< std::vector<std::shared_ptr<BindingDecl>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<BindingDecl>> > ()); }
#line 1485 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 348 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BindingDecl> > () = BindingDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1491 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 352 "Parser/Parser.yy" // lalr1.cc:859
    { }
#line 1497 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 353 "Parser/Parser.yy" // lalr1.cc:859
    { }
#line 1503 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 357 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<IntegerLiteral> > (); }
#line 1509 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 358 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<DoubleLiteral> > (); }
#line 1515 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 359 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<BoolLiteral> > (); }
#line 1521 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 360 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<StringLiteral> > (); }
#line 1527 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 364 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<Expr> > (); }
#line 1533 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 365 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<NullLiteral> > (); }
#line 1539 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 366 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = DeclRefExpr::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1545 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 367 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<ParenExpr> > (); }
#line 1551 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 368 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<ArrayLiteral> > (); }
#line 1557 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 369 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<MapLiteral> > (); }
#line 1563 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 370 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<CallExpr> > (); }
#line 1569 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 371 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<MemberExpr> > (); }
#line 1575 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 372 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<SubscriptExpr> > (); }
#line 1581 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 373 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<NullConditionalOperator> > (); }
#line 1587 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 377 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ParenExpr> > () = ParenExpr::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1593 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 381 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullLiteral> > () = NullLiteral::make(toLoc(yylhs.location)); }
#line 1599 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 385 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ArrayLiteral> > () = ArrayLiteral::make(toLoc(yylhs.location), std::vector<std::shared_ptr<Expr>>{}); }
#line 1605 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 386 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ArrayLiteral> > () = ArrayLiteral::make(toLoc(yylhs.location), yystack_[2].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1611 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 390 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MapLiteral> > () = MapLiteral::make(toLoc(yylhs.location), std::vector<std::shared_ptr<MapEntry>>{}); }
#line 1617 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 391 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MapLiteral> > () = MapLiteral::make(toLoc(yylhs.location), yystack_[2].value.as< std::vector<std::shared_ptr<MapEntry>> > ()); }
#line 1623 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 395 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MapEntry> > () = MapEntry::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1629 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 399 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<MapEntry>> > ().push_back(yystack_[0].value.as< std::shared_ptr<MapEntry> > ()); }
#line 1635 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 400 "Parser/Parser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<MapEntry>> > ().push_back(yystack_[0].value.as< std::shared_ptr<MapEntry> > ()); yylhs.value.as< std::vector<std::shared_ptr<MapEntry>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<MapEntry>> > ()); }
#line 1641 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 404 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MemberExpr> > () = MemberExpr::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1647 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 408 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<SubscriptExpr> > () = SubscriptExpr::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1653 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 412 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CallExpr> > () = CallExpr::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), std::vector<std::shared_ptr<Expr>>{}); }
#line 1659 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 413 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CallExpr> > () = CallExpr::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1665 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 417 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullConditionalOperator> > () = NullConditionalOperator::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<Expr> > (), MemberExpr::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ())); }
#line 1671 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 418 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullConditionalOperator> > () = NullConditionalOperator::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Expr> > (), SubscriptExpr::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::shared_ptr<Expr> > ())); }
#line 1677 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 419 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullConditionalOperator> > () = NullConditionalOperator::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<Expr> > (), CallExpr::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<Expr> > (), std::vector<std::shared_ptr<Expr>>{})); }
#line 1683 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 420 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullConditionalOperator> > () = NullConditionalOperator::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Expr> > (), CallExpr::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::vector<std::shared_ptr<Expr>> > ())); }
#line 1689 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 424 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PreInc, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1695 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 425 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PreDec, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1701 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 426 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PostInc, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1707 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 427 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PostDec, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1713 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 428 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::Plus, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1719 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 429 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::Minus, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1725 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 430 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::LogicalNot, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1731 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 434 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::Add; }
#line 1737 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 435 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::Subtract; }
#line 1743 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 436 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::Multiply; }
#line 1749 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 437 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::Divide; }
#line 1755 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 438 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::Mod; }
#line 1761 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 439 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::Equal; }
#line 1767 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 440 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::NotEqual; }
#line 1773 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 441 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::LogicalAnd; }
#line 1779 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 442 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::LogicalOr; }
#line 1785 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 443 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::GreaterThan; }
#line 1791 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 444 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::GreaterThanOrEqual; }
#line 1797 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 445 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::LessThan; }
#line 1803 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 446 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::LessThanOrEqual; }
#line 1809 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 447 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::NullCoalescing; }
#line 1815 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 451 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), yystack_[1].value.as< BinaryOperatorKind > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1821 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 455 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ConditionalOperator> > () = ConditionalOperator::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1827 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 459 "Parser/Parser.yy" // lalr1.cc:859
    { }
#line 1833 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 463 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Assign, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1839 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 467 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Expr>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1845 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 468 "Parser/Parser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<Expr>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Expr> > ()); yylhs.value.as< std::vector<std::shared_ptr<Expr>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1851 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 472 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<Expr> > (); }
#line 1857 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 473 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<BinaryOperator> > (); }
#line 1863 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 474 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<BinaryOperator> > (); }
#line 1869 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 475 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<UnaryOperator> > (); }
#line 1875 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 476 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<ConditionalOperator> > (); }
#line 1881 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 477 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<FunctionExpr> > (); }
#line 1887 "Parser/Parser.cpp" // lalr1.cc:859
    break;


#line 1891 "Parser/Parser.cpp" // lalr1.cc:859
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


  const signed char Parser::yypact_ninf_ = -113;

  const signed char Parser::yytable_ninf_ = -58;

  const short int
  Parser::yypact_[] =
  {
     -16,   -32,   -24,    29,   -16,  -113,  -113,  -113,    13,    35,
    -113,  -113,    11,    40,    38,     4,    30,    51,  -113,     5,
    -113,  -113,    26,    31,  -113,    83,  -113,    60,    61,    45,
      45,    59,    53,   101,   101,   101,   101,   101,   379,  -113,
     292,    58,   321,   -13,    -7,    80,    92,    94,  -113,  -113,
    -113,  -113,  -113,  -113,  -113,  -113,  -113,   179,  -113,  -113,
    -113,  -113,  -113,    93,    95,    96,  -113,    56,  -113,  -113,
    -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,
     416,    10,    20,  -113,  -113,  -113,  -113,  -113,  -113,  -113,
      45,  -113,    34,    34,    34,    34,    34,   438,  -113,   110,
    -113,    98,   109,   462,  -113,    13,  -113,   484,   107,   107,
     379,   379,   263,  -113,  -113,  -113,  -113,  -113,  -113,  -113,
      84,   379,   108,   130,   379,   379,  -113,  -113,  -113,  -113,
    -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,
    -113,   379,   379,    45,   379,    45,  -113,   130,  -113,  -113,
     379,   114,   379,   128,   379,    40,  -113,  -113,    82,  -113,
     115,   506,   530,  -113,    -1,     3,    99,   379,   116,   139,
     554,  -113,   134,   736,   576,  -113,   350,   379,   123,   610,
     736,   757,   736,   171,   736,   176,  -113,   462,  -113,   736,
    -113,   736,  -113,   178,   107,   184,   221,   221,   107,     8,
     107,  -113,   632,   379,  -113,  -113,  -113,   379,  -113,  -113,
     135,   654,  -113,   379,   379,   379,   379,  -113,   379,   146,
    -113,   137,   140,   379,   688,  -113,  -113,   757,   736,   736,
     736,   736,   221,  -113,  -113,   712,   221,  -113,   221,  -113,
    -113
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       2,     0,     0,     0,     3,     4,     7,     6,     0,     0,
       1,     5,     0,     0,     0,    10,    18,     0,    16,     0,
       8,    21,     0,     0,    25,     0,    23,     0,     0,     0,
       0,    12,     0,     0,     0,     0,     0,     0,     0,    38,
       0,    14,     0,     0,     0,     0,     0,     0,    87,    78,
      72,    73,    74,    75,   135,    40,    28,     0,    30,    34,
      35,    36,    37,     0,     0,     0,    76,   130,    79,    77,
      80,    81,    83,    84,    82,    85,   133,   132,   134,   131,
       0,    57,    61,    22,    24,    26,    27,    20,    11,    19,
       0,    17,   108,   107,   103,   104,   109,     0,    88,     0,
      93,    70,    70,   128,    15,     0,    42,     0,     0,     0,
       0,     0,     0,    39,    41,    31,    32,    33,   105,   106,
       0,     0,     0,   126,     0,     0,   111,   110,   112,   113,
     114,   117,   118,   115,   116,   122,   120,   121,   119,    29,
     123,     0,     0,     0,     0,     0,    13,     0,    86,    90,
      71,     0,    71,     0,     0,     0,    43,    69,     0,    67,
       0,     0,     0,    48,     0,     0,    78,     0,     0,     0,
       0,    97,     0,   128,     0,    95,     0,     0,     0,     0,
     127,   124,    58,    59,    62,    63,    94,     0,    91,   129,
      89,    92,     9,     0,     0,     0,     0,     0,     0,    53,
       0,    54,     0,     0,    50,    49,    98,     0,    96,   101,
       0,     0,    99,     0,     0,     0,     0,    68,     0,    44,
      46,     0,     0,     0,     0,   102,   100,   125,    60,    64,
      65,    66,     0,    55,    56,     0,     0,    45,     0,    51,
      47
  };

  const short int
  Parser::yypgoto_[] =
  {
    -113,  -113,  -113,   186,     1,  -113,    86,  -113,  -113,   160,
     -25,  -113,  -113,   177,   -50,   -12,  -113,  -113,  -113,  -113,
    -113,  -113,  -113,  -113,   -11,     2,  -113,  -103,     7,   103,
    -113,   163,  -113,  -113,  -113,  -113,    62,  -113,  -113,  -113,
    -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -112,   -38
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,     5,     6,    54,    13,   105,    17,    18,
      88,     7,    25,    26,    55,    56,    57,    58,    59,    60,
      61,   167,    62,   168,    63,    64,    65,   158,   159,   151,
      66,    67,    68,    69,    70,    71,   100,   101,    72,    73,
      74,    75,    76,   141,    77,    78,   124,    79,   102,    80
  };

  const short int
  Parser::yytable_[] =
  {
      97,    20,   103,    27,   107,    89,   160,   114,   172,    33,
      34,   142,   108,   142,    27,    24,    28,     8,   109,    35,
      36,    37,     1,   144,   198,     9,    24,    28,   200,    10,
      38,     2,    19,    39,    40,    29,    81,    15,    12,   143,
     -57,   143,    82,    41,    42,    43,    44,    45,   199,    46,
      47,   145,   201,    48,    49,    50,    51,    52,    53,   120,
      16,    30,    14,   121,   210,   146,    21,    19,   122,   147,
     118,   119,   161,   162,   170,    81,     1,    31,    22,    23,
      82,   120,   173,   174,    32,   121,   179,   180,    33,    34,
     122,   123,    85,    86,    87,   221,    90,   222,    35,    36,
      37,   169,    16,   181,   182,   110,   184,   104,   193,    38,
     171,    83,   187,    40,   189,   194,   191,   111,   183,   112,
     185,     1,    41,    22,    23,   115,    38,   116,   117,   202,
      40,   150,    48,    49,    50,    51,    52,    53,   173,   211,
     149,   195,   152,   192,   188,   -52,   219,   220,   194,    48,
      49,    50,    51,    52,    53,   176,   157,   175,   190,   177,
     206,   225,   203,   233,   178,   224,   234,   207,   207,   189,
     194,   204,   212,   194,   214,   227,   228,   229,   230,   215,
     231,   216,   237,    33,    34,   235,   239,   218,   240,   232,
      11,   155,    91,    35,    36,    37,    92,    93,    94,    95,
      96,   217,    84,     0,    38,   153,    19,   113,    40,     0,
       0,     0,   186,     0,     0,     0,     0,    41,    42,    43,
      44,    45,     0,    46,    47,    33,    34,    48,    49,    50,
      51,    52,    53,     0,     0,    35,    36,    37,     0,     0,
       0,     0,     0,     0,     0,     0,    38,     0,    19,     0,
      40,     0,     0,     0,     0,     0,     0,     0,     0,    41,
      42,    43,    44,    45,     0,    46,    47,    33,    34,    48,
      49,    50,    51,    52,    53,     0,     0,    35,    36,    37,
       0,     0,     0,     0,     0,     0,     0,     0,    38,     0,
       0,     0,    40,     0,     0,   163,    33,    34,     0,     0,
       0,    41,     0,   164,   165,     0,    35,    36,    37,     0,
       0,    48,   166,    50,    51,    52,    53,    38,     0,     0,
       0,    40,    98,    99,     0,    33,    34,     0,     0,     0,
      41,     0,     0,     0,     0,    35,    36,    37,     0,     0,
      48,    49,    50,    51,    52,    53,    38,     0,     0,     0,
      40,     0,     0,   106,    33,    34,     0,     0,     0,    41,
       0,     0,     0,     0,    35,    36,    37,     0,     0,    48,
      49,    50,    51,    52,    53,    38,   209,     0,     0,    40,
       0,     0,     0,    33,    34,     0,     0,     0,    41,     0,
       0,     0,     0,    35,    36,    37,     0,     0,    48,    49,
      50,    51,    52,    53,    38,     0,     0,     0,    40,     0,
       0,     0,     0,     0,     0,     0,     0,    41,     0,   125,
     126,   127,   128,   129,   130,     0,     0,    48,    49,    50,
      51,    52,    53,   131,   132,   133,   134,   135,   136,   137,
     138,   125,   126,   127,   128,   129,   130,     0,   139,     0,
       0,     0,   140,     0,     0,   131,   132,   133,   134,   135,
     136,   137,   138,     0,   148,   125,   126,   127,   128,   129,
     130,     0,     0,     0,   140,     0,     0,     0,     0,   131,
     132,   133,   134,   135,   136,   137,   138,   125,   126,   127,
     128,   129,   130,   154,     0,     0,     0,     0,   140,     0,
       0,   131,   132,   133,   134,   135,   136,   137,   138,   125,
     126,   127,   128,   129,   130,     0,   156,     0,     0,     0,
     140,     0,     0,   131,   132,   133,   134,   135,   136,   137,
     138,     0,   196,   125,   126,   127,   128,   129,   130,     0,
       0,     0,   140,     0,     0,     0,     0,   131,   132,   133,
     134,   135,   136,   137,   138,     0,   197,   125,   126,   127,
     128,   129,   130,     0,     0,     0,   140,     0,     0,     0,
       0,   131,   132,   133,   134,   135,   136,   137,   138,   125,
     126,   127,   128,   129,   130,     0,   205,     0,     0,     0,
     140,     0,     0,   131,   132,   133,   134,   135,   136,   137,
     138,     0,     0,     0,     0,     0,   208,     0,     0,     0,
       0,     0,   140,   125,   126,   127,   128,   129,   130,     0,
       0,     0,     0,     0,     0,     0,     0,   131,   132,   133,
     134,   135,   136,   137,   138,   125,   126,   127,   128,   129,
     130,   213,     0,     0,     0,     0,   140,     0,     0,   131,
     132,   133,   134,   135,   136,   137,   138,   125,   126,   127,
     128,   129,   130,     0,   223,     0,     0,     0,   140,     0,
       0,   131,   132,   133,   134,   135,   136,   137,   138,     0,
       0,     0,     0,     0,   226,     0,     0,     0,     0,     0,
     140,   125,   126,   127,   128,   129,   130,     0,     0,     0,
       0,     0,     0,     0,     0,   131,   132,   133,   134,   135,
     136,   137,   138,     0,   236,   125,   126,   127,   128,   129,
     130,     0,     0,     0,   140,     0,     0,     0,     0,   131,
     132,   133,   134,   135,   136,   137,   138,     0,   238,   125,
     126,   127,   128,   129,   130,     0,     0,     0,   140,     0,
       0,     0,     0,   131,   132,   133,   134,   135,   136,   137,
     138,   126,   127,   128,   129,   130,     0,     0,     0,     0,
       0,     0,   140,     0,   131,   132,   133,   134,   135,   136,
     137,   138,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   140
  };

  const short int
  Parser::yycheck_[] =
  {
      38,    13,    40,    14,    42,    30,   109,    57,   120,     4,
       5,     3,    25,     3,    25,    14,    14,    49,    25,    14,
      15,    16,    38,     3,    25,    49,    25,    25,    25,     0,
      25,    47,    27,    28,    29,    31,    49,    26,    25,    31,
      32,    31,    49,    38,    39,    40,    41,    42,    49,    44,
      45,    31,    49,    48,    49,    50,    51,    52,    53,    25,
      49,    31,    27,    29,   176,    90,    28,    27,    34,    35,
      14,    15,   110,   111,   112,    49,    38,    26,    40,    41,
      49,    25,   120,   121,    33,    29,   124,   125,     4,     5,
      34,    35,    32,    32,    49,   198,    37,   200,    14,    15,
      16,   112,    49,   141,   142,    25,   144,    49,    26,    25,
      26,    28,   150,    29,   152,    33,   154,    25,   143,    25,
     145,    38,    38,    40,    41,    32,    25,    32,    32,   167,
      29,    33,    48,    49,    50,    51,    52,    53,   176,   177,
      30,    26,    33,   155,    30,    46,   196,   197,    33,    48,
      49,    50,    51,    52,    53,    25,    49,    49,    30,    29,
      26,    26,    46,    26,    34,   203,    26,    33,    33,   207,
      33,    32,    49,    33,     3,   213,   214,   215,   216,     3,
     218,     3,   232,     4,     5,   223,   236,     3,   238,    43,
       4,   105,    32,    14,    15,    16,    33,    34,    35,    36,
      37,   194,    25,    -1,    25,   102,    27,    28,    29,    -1,
      -1,    -1,   150,    -1,    -1,    -1,    -1,    38,    39,    40,
      41,    42,    -1,    44,    45,     4,     5,    48,    49,    50,
      51,    52,    53,    -1,    -1,    14,    15,    16,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      39,    40,    41,    42,    -1,    44,    45,     4,     5,    48,
      49,    50,    51,    52,    53,    -1,    -1,    14,    15,    16,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,    -1,
      -1,    -1,    29,    -1,    -1,    32,     4,     5,    -1,    -1,
      -1,    38,    -1,    40,    41,    -1,    14,    15,    16,    -1,
      -1,    48,    49,    50,    51,    52,    53,    25,    -1,    -1,
      -1,    29,    30,    31,    -1,     4,     5,    -1,    -1,    -1,
      38,    -1,    -1,    -1,    -1,    14,    15,    16,    -1,    -1,
      48,    49,    50,    51,    52,    53,    25,    -1,    -1,    -1,
      29,    -1,    -1,    32,     4,     5,    -1,    -1,    -1,    38,
      -1,    -1,    -1,    -1,    14,    15,    16,    -1,    -1,    48,
      49,    50,    51,    52,    53,    25,    26,    -1,    -1,    29,
      -1,    -1,    -1,     4,     5,    -1,    -1,    -1,    38,    -1,
      -1,    -1,    -1,    14,    15,    16,    -1,    -1,    48,    49,
      50,    51,    52,    53,    25,    -1,    -1,    -1,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,     3,
       4,     5,     6,     7,     8,    -1,    -1,    48,    49,    50,
      51,    52,    53,    17,    18,    19,    20,    21,    22,    23,
      24,     3,     4,     5,     6,     7,     8,    -1,    32,    -1,
      -1,    -1,    36,    -1,    -1,    17,    18,    19,    20,    21,
      22,    23,    24,    -1,    26,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    17,
      18,    19,    20,    21,    22,    23,    24,     3,     4,     5,
       6,     7,     8,    31,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,     3,
       4,     5,     6,     7,     8,    -1,    32,    -1,    -1,    -1,
      36,    -1,    -1,    17,    18,    19,    20,    21,    22,    23,
      24,    -1,    26,     3,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    36,    -1,    -1,    -1,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    -1,    26,     3,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,     3,
       4,     5,     6,     7,     8,    -1,    32,    -1,    -1,    -1,
      36,    -1,    -1,    17,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    36,     3,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,     3,     4,     5,     6,     7,
       8,    31,    -1,    -1,    -1,    -1,    36,    -1,    -1,    17,
      18,    19,    20,    21,    22,    23,    24,     3,     4,     5,
       6,     7,     8,    -1,    32,    -1,    -1,    -1,    36,    -1,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,
      36,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,
      22,    23,    24,    -1,    26,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    17,
      18,    19,    20,    21,    22,    23,    24,    -1,    26,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    17,    18,    19,    20,    21,    22,    23,
      24,     4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,    38,    47,    62,    63,    64,    65,    72,    49,    49,
       0,    64,    25,    67,    27,    26,    49,    69,    70,    27,
      76,    28,    40,    41,    65,    73,    74,    85,    86,    31,
      31,    26,    33,     4,     5,    14,    15,    16,    25,    28,
      29,    38,    39,    40,    41,    42,    44,    45,    48,    49,
      50,    51,    52,    53,    66,    75,    76,    77,    78,    79,
      80,    81,    83,    85,    86,    87,    91,    92,    93,    94,
      95,    96,    99,   100,   101,   102,   103,   105,   106,   108,
     110,    49,    49,    28,    74,    32,    32,    49,    71,    71,
      37,    70,    92,    92,    92,    92,    92,   110,    30,    31,
      97,    98,   109,   110,    49,    68,    32,   110,    25,    25,
      25,    25,    25,    28,    75,    32,    32,    32,    14,    15,
      25,    29,    34,    35,   107,     3,     4,     5,     6,     7,
       8,    17,    18,    19,    20,    21,    22,    23,    24,    32,
      36,   104,     3,    31,     3,    31,    71,    35,    26,    30,
      33,    90,    33,    90,    31,    67,    32,    49,    88,    89,
      88,   110,   110,    32,    40,    41,    49,    82,    84,    85,
     110,    26,   109,   110,   110,    49,    25,    29,    34,   110,
     110,   110,   110,    71,   110,    71,    97,   110,    30,   110,
      30,   110,    76,    26,    33,    26,    26,    26,    25,    49,
      25,    49,   110,    46,    32,    32,    26,    33,    30,    26,
     109,   110,    49,    31,     3,     3,     3,    89,     3,    75,
      75,    88,    88,    32,   110,    26,    30,   110,   110,   110,
     110,   110,    43,    26,    26,   110,    26,    75,    26,    75,
      75
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    61,    62,    62,    63,    63,    64,    64,    65,    66,
      67,    67,    67,    67,    68,    68,    69,    69,    70,    70,
      71,    72,    72,    73,    73,    74,    74,    74,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    76,    76,
      77,    77,    78,    78,    79,    79,    80,    81,    82,    82,
      82,    83,    84,    84,    84,    84,    84,    85,    85,    85,
      85,    86,    86,    86,    86,    87,    87,    88,    88,    89,
      90,    90,    91,    91,    91,    91,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    93,    94,    95,    95,
      96,    96,    97,    98,    98,    99,   100,   101,   101,   102,
     102,   102,   102,   103,   103,   103,   103,   103,   103,   103,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   105,   106,   107,   108,   109,   109,
     110,   110,   110,   110,   110,   110
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     0,     1,     1,     2,     1,     1,     4,     4,
       2,     4,     3,     5,     0,     1,     1,     3,     1,     3,
       1,     4,     5,     1,     2,     1,     2,     2,     1,     2,
       1,     2,     2,     2,     1,     1,     1,     1,     2,     3,
       1,     2,     2,     3,     5,     7,     5,     8,     1,     2,
       2,     7,     1,     2,     2,     4,     4,     2,     4,     4,
       6,     2,     4,     4,     6,     6,     6,     1,     3,     1,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     2,     4,
       3,     4,     3,     1,     3,     3,     4,     3,     4,     4,
       5,     4,     5,     2,     2,     2,     2,     2,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     5,     1,     3,     1,     3,
       1,     1,     1,     1,     1,     1
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
  "\"class\"", "\"null\"", "\"identifier\"", "\"integer_literal\"",
  "\"double_literal\"", "\"bool_literal\"", "\"string_literal\"",
  "\"ternary_question\"", "\"conditional_expression\"", "\"binary_op\"",
  "\"unary_plus\"", "\"unary_minus\"", "\"grouping\"", "\"then\"",
  "$accept", "translation_unit", "translation_unit_declarations",
  "translation_unit_declaration", "function_definition",
  "function_expression", "call_signature", "binding_identifier",
  "parameter_variables", "parameter_variable", "type_specifier",
  "class_declaration", "member_declaration_list", "member_declaration",
  "statement", "compound_statement", "statement_list", "return_statement",
  "if_statement", "while_statement", "for_statement", "for_init_statement",
  "for_range_statement", "for_range_init", "variable_definition",
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
       0,   200,   200,   201,   205,   206,   210,   211,   215,   219,
     223,   224,   225,   226,   230,   231,   235,   236,   240,   241,
     245,   249,   250,   254,   255,   259,   260,   261,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   278,   279,
     283,   284,   288,   289,   293,   294,   298,   302,   306,   307,
     308,   312,   316,   317,   318,   319,   320,   324,   325,   326,
     327,   331,   332,   333,   334,   338,   339,   343,   344,   348,
     352,   353,   357,   358,   359,   360,   364,   365,   366,   367,
     368,   369,   370,   371,   372,   373,   377,   381,   385,   386,
     390,   391,   395,   399,   400,   404,   408,   412,   413,   417,
     418,   419,   420,   424,   425,   426,   427,   428,   429,   430,
     434,   435,   436,   437,   438,   439,   440,   441,   442,   443,
     444,   445,   446,   447,   451,   455,   459,   463,   467,   468,
     472,   473,   474,   475,   476,   477
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
#line 2556 "Parser/Parser.cpp" // lalr1.cc:1167
#line 480 "Parser/Parser.yy" // lalr1.cc:1168


void yy::Parser::error(const location_type& l, const std::string& m)
{
    driver.error(toLoc(l), m);
}
