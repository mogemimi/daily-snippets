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
      case 107: // binary_op
        value.move< BinaryOperatorKind > (that.value);
        break;

      case 69: // call_signature
        value.move< CallSignature > (that.value);
        break;

      case 89: // variable_decl_specifier
        value.move< VariableDeclSpecifier > (that.value);
        break;

      case 98: // array_literal
        value.move< std::shared_ptr<ArrayLiteral> > (that.value);
        break;

      case 108: // binary_expression
      case 111: // assignment_expression
        value.move< std::shared_ptr<BinaryOperator> > (that.value);
        break;

      case 92: // binding_declaration
        value.move< std::shared_ptr<BindingDecl> > (that.value);
        break;

      case 54: // "bool_literal"
        value.move< std::shared_ptr<BoolLiteral> > (that.value);
        break;

      case 104: // call_expression
        value.move< std::shared_ptr<CallExpr> > (that.value);
        break;

      case 74: // class_declaration
        value.move< std::shared_ptr<ClassDecl> > (that.value);
        break;

      case 78: // compound_statement
        value.move< std::shared_ptr<CompoundStmt> > (that.value);
        break;

      case 109: // conditional_expression
        value.move< std::shared_ptr<ConditionalOperator> > (that.value);
        break;

      case 66: // translation_unit_declaration
      case 76: // member_declaration
      case 86: // for_range_init
        value.move< std::shared_ptr<Decl> > (that.value);
        break;

      case 90: // decomposition_definition
        value.move< std::shared_ptr<DecompositionDecl> > (that.value);
        break;

      case 87: // defer_statement
        value.move< std::shared_ptr<DeferStmt> > (that.value);
        break;

      case 53: // "double_literal"
        value.move< std::shared_ptr<DoubleLiteral> > (that.value);
        break;

      case 94: // literal
      case 95: // primary_expression
      case 113: // expression
        value.move< std::shared_ptr<Expr> > (that.value);
        break;

      case 85: // for_range_statement
        value.move< std::shared_ptr<ForRangeStmt> > (that.value);
        break;

      case 83: // for_statement
        value.move< std::shared_ptr<ForStmt> > (that.value);
        break;

      case 67: // function_definition
        value.move< std::shared_ptr<FunctionDecl> > (that.value);
        break;

      case 68: // function_expression
        value.move< std::shared_ptr<FunctionExpr> > (that.value);
        break;

      case 81: // if_statement
        value.move< std::shared_ptr<IfStmt> > (that.value);
        break;

      case 52: // "integer_literal"
        value.move< std::shared_ptr<IntegerLiteral> > (that.value);
        break;

      case 100: // map_entry
        value.move< std::shared_ptr<MapEntry> > (that.value);
        break;

      case 99: // map_literal
        value.move< std::shared_ptr<MapLiteral> > (that.value);
        break;

      case 102: // member_expression
        value.move< std::shared_ptr<MemberExpr> > (that.value);
        break;

      case 51: // "identifier"
      case 70: // binding_identifier
      case 73: // type_specifier
        value.move< std::shared_ptr<NamedDecl> > (that.value);
        break;

      case 105: // null_conditional_expression
        value.move< std::shared_ptr<NullConditionalOperator> > (that.value);
        break;

      case 97: // null_literal
        value.move< std::shared_ptr<NullLiteral> > (that.value);
        break;

      case 96: // parenthesized_expression
        value.move< std::shared_ptr<ParenExpr> > (that.value);
        break;

      case 72: // parameter_variable
        value.move< std::shared_ptr<ParmVarDecl> > (that.value);
        break;

      case 80: // return_statement
        value.move< std::shared_ptr<ReturnStmt> > (that.value);
        break;

      case 77: // statement
      case 84: // for_init_statement
        value.move< std::shared_ptr<Stmt> > (that.value);
        break;

      case 55: // "string_literal"
        value.move< std::shared_ptr<StringLiteral> > (that.value);
        break;

      case 103: // subscript_expression
        value.move< std::shared_ptr<SubscriptExpr> > (that.value);
        break;

      case 64: // translation_unit
        value.move< std::shared_ptr<TranslationUnitDecl> > (that.value);
        break;

      case 106: // unary_expression
        value.move< std::shared_ptr<UnaryOperator> > (that.value);
        break;

      case 88: // variable_definition
        value.move< std::shared_ptr<VariableDecl> > (that.value);
        break;

      case 82: // while_statement
        value.move< std::shared_ptr<WhileStmt> > (that.value);
        break;

      case 91: // binding_declarations
        value.move< std::vector<std::shared_ptr<BindingDecl>> > (that.value);
        break;

      case 65: // translation_unit_declarations
      case 75: // member_declaration_list
        value.move< std::vector<std::shared_ptr<Decl>> > (that.value);
        break;

      case 112: // expression_list
        value.move< std::vector<std::shared_ptr<Expr>> > (that.value);
        break;

      case 101: // map_entry_list
        value.move< std::vector<std::shared_ptr<MapEntry>> > (that.value);
        break;

      case 71: // parameter_variables
        value.move< std::vector<std::shared_ptr<ParmVarDecl>> > (that.value);
        break;

      case 79: // statement_list
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
      case 107: // binary_op
        value.copy< BinaryOperatorKind > (that.value);
        break;

      case 69: // call_signature
        value.copy< CallSignature > (that.value);
        break;

      case 89: // variable_decl_specifier
        value.copy< VariableDeclSpecifier > (that.value);
        break;

      case 98: // array_literal
        value.copy< std::shared_ptr<ArrayLiteral> > (that.value);
        break;

      case 108: // binary_expression
      case 111: // assignment_expression
        value.copy< std::shared_ptr<BinaryOperator> > (that.value);
        break;

      case 92: // binding_declaration
        value.copy< std::shared_ptr<BindingDecl> > (that.value);
        break;

      case 54: // "bool_literal"
        value.copy< std::shared_ptr<BoolLiteral> > (that.value);
        break;

      case 104: // call_expression
        value.copy< std::shared_ptr<CallExpr> > (that.value);
        break;

      case 74: // class_declaration
        value.copy< std::shared_ptr<ClassDecl> > (that.value);
        break;

      case 78: // compound_statement
        value.copy< std::shared_ptr<CompoundStmt> > (that.value);
        break;

      case 109: // conditional_expression
        value.copy< std::shared_ptr<ConditionalOperator> > (that.value);
        break;

      case 66: // translation_unit_declaration
      case 76: // member_declaration
      case 86: // for_range_init
        value.copy< std::shared_ptr<Decl> > (that.value);
        break;

      case 90: // decomposition_definition
        value.copy< std::shared_ptr<DecompositionDecl> > (that.value);
        break;

      case 87: // defer_statement
        value.copy< std::shared_ptr<DeferStmt> > (that.value);
        break;

      case 53: // "double_literal"
        value.copy< std::shared_ptr<DoubleLiteral> > (that.value);
        break;

      case 94: // literal
      case 95: // primary_expression
      case 113: // expression
        value.copy< std::shared_ptr<Expr> > (that.value);
        break;

      case 85: // for_range_statement
        value.copy< std::shared_ptr<ForRangeStmt> > (that.value);
        break;

      case 83: // for_statement
        value.copy< std::shared_ptr<ForStmt> > (that.value);
        break;

      case 67: // function_definition
        value.copy< std::shared_ptr<FunctionDecl> > (that.value);
        break;

      case 68: // function_expression
        value.copy< std::shared_ptr<FunctionExpr> > (that.value);
        break;

      case 81: // if_statement
        value.copy< std::shared_ptr<IfStmt> > (that.value);
        break;

      case 52: // "integer_literal"
        value.copy< std::shared_ptr<IntegerLiteral> > (that.value);
        break;

      case 100: // map_entry
        value.copy< std::shared_ptr<MapEntry> > (that.value);
        break;

      case 99: // map_literal
        value.copy< std::shared_ptr<MapLiteral> > (that.value);
        break;

      case 102: // member_expression
        value.copy< std::shared_ptr<MemberExpr> > (that.value);
        break;

      case 51: // "identifier"
      case 70: // binding_identifier
      case 73: // type_specifier
        value.copy< std::shared_ptr<NamedDecl> > (that.value);
        break;

      case 105: // null_conditional_expression
        value.copy< std::shared_ptr<NullConditionalOperator> > (that.value);
        break;

      case 97: // null_literal
        value.copy< std::shared_ptr<NullLiteral> > (that.value);
        break;

      case 96: // parenthesized_expression
        value.copy< std::shared_ptr<ParenExpr> > (that.value);
        break;

      case 72: // parameter_variable
        value.copy< std::shared_ptr<ParmVarDecl> > (that.value);
        break;

      case 80: // return_statement
        value.copy< std::shared_ptr<ReturnStmt> > (that.value);
        break;

      case 77: // statement
      case 84: // for_init_statement
        value.copy< std::shared_ptr<Stmt> > (that.value);
        break;

      case 55: // "string_literal"
        value.copy< std::shared_ptr<StringLiteral> > (that.value);
        break;

      case 103: // subscript_expression
        value.copy< std::shared_ptr<SubscriptExpr> > (that.value);
        break;

      case 64: // translation_unit
        value.copy< std::shared_ptr<TranslationUnitDecl> > (that.value);
        break;

      case 106: // unary_expression
        value.copy< std::shared_ptr<UnaryOperator> > (that.value);
        break;

      case 88: // variable_definition
        value.copy< std::shared_ptr<VariableDecl> > (that.value);
        break;

      case 82: // while_statement
        value.copy< std::shared_ptr<WhileStmt> > (that.value);
        break;

      case 91: // binding_declarations
        value.copy< std::vector<std::shared_ptr<BindingDecl>> > (that.value);
        break;

      case 65: // translation_unit_declarations
      case 75: // member_declaration_list
        value.copy< std::vector<std::shared_ptr<Decl>> > (that.value);
        break;

      case 112: // expression_list
        value.copy< std::vector<std::shared_ptr<Expr>> > (that.value);
        break;

      case 101: // map_entry_list
        value.copy< std::vector<std::shared_ptr<MapEntry>> > (that.value);
        break;

      case 71: // parameter_variables
        value.copy< std::vector<std::shared_ptr<ParmVarDecl>> > (that.value);
        break;

      case 79: // statement_list
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
      case 107: // binary_op
        yylhs.value.build< BinaryOperatorKind > ();
        break;

      case 69: // call_signature
        yylhs.value.build< CallSignature > ();
        break;

      case 89: // variable_decl_specifier
        yylhs.value.build< VariableDeclSpecifier > ();
        break;

      case 98: // array_literal
        yylhs.value.build< std::shared_ptr<ArrayLiteral> > ();
        break;

      case 108: // binary_expression
      case 111: // assignment_expression
        yylhs.value.build< std::shared_ptr<BinaryOperator> > ();
        break;

      case 92: // binding_declaration
        yylhs.value.build< std::shared_ptr<BindingDecl> > ();
        break;

      case 54: // "bool_literal"
        yylhs.value.build< std::shared_ptr<BoolLiteral> > ();
        break;

      case 104: // call_expression
        yylhs.value.build< std::shared_ptr<CallExpr> > ();
        break;

      case 74: // class_declaration
        yylhs.value.build< std::shared_ptr<ClassDecl> > ();
        break;

      case 78: // compound_statement
        yylhs.value.build< std::shared_ptr<CompoundStmt> > ();
        break;

      case 109: // conditional_expression
        yylhs.value.build< std::shared_ptr<ConditionalOperator> > ();
        break;

      case 66: // translation_unit_declaration
      case 76: // member_declaration
      case 86: // for_range_init
        yylhs.value.build< std::shared_ptr<Decl> > ();
        break;

      case 90: // decomposition_definition
        yylhs.value.build< std::shared_ptr<DecompositionDecl> > ();
        break;

      case 87: // defer_statement
        yylhs.value.build< std::shared_ptr<DeferStmt> > ();
        break;

      case 53: // "double_literal"
        yylhs.value.build< std::shared_ptr<DoubleLiteral> > ();
        break;

      case 94: // literal
      case 95: // primary_expression
      case 113: // expression
        yylhs.value.build< std::shared_ptr<Expr> > ();
        break;

      case 85: // for_range_statement
        yylhs.value.build< std::shared_ptr<ForRangeStmt> > ();
        break;

      case 83: // for_statement
        yylhs.value.build< std::shared_ptr<ForStmt> > ();
        break;

      case 67: // function_definition
        yylhs.value.build< std::shared_ptr<FunctionDecl> > ();
        break;

      case 68: // function_expression
        yylhs.value.build< std::shared_ptr<FunctionExpr> > ();
        break;

      case 81: // if_statement
        yylhs.value.build< std::shared_ptr<IfStmt> > ();
        break;

      case 52: // "integer_literal"
        yylhs.value.build< std::shared_ptr<IntegerLiteral> > ();
        break;

      case 100: // map_entry
        yylhs.value.build< std::shared_ptr<MapEntry> > ();
        break;

      case 99: // map_literal
        yylhs.value.build< std::shared_ptr<MapLiteral> > ();
        break;

      case 102: // member_expression
        yylhs.value.build< std::shared_ptr<MemberExpr> > ();
        break;

      case 51: // "identifier"
      case 70: // binding_identifier
      case 73: // type_specifier
        yylhs.value.build< std::shared_ptr<NamedDecl> > ();
        break;

      case 105: // null_conditional_expression
        yylhs.value.build< std::shared_ptr<NullConditionalOperator> > ();
        break;

      case 97: // null_literal
        yylhs.value.build< std::shared_ptr<NullLiteral> > ();
        break;

      case 96: // parenthesized_expression
        yylhs.value.build< std::shared_ptr<ParenExpr> > ();
        break;

      case 72: // parameter_variable
        yylhs.value.build< std::shared_ptr<ParmVarDecl> > ();
        break;

      case 80: // return_statement
        yylhs.value.build< std::shared_ptr<ReturnStmt> > ();
        break;

      case 77: // statement
      case 84: // for_init_statement
        yylhs.value.build< std::shared_ptr<Stmt> > ();
        break;

      case 55: // "string_literal"
        yylhs.value.build< std::shared_ptr<StringLiteral> > ();
        break;

      case 103: // subscript_expression
        yylhs.value.build< std::shared_ptr<SubscriptExpr> > ();
        break;

      case 64: // translation_unit
        yylhs.value.build< std::shared_ptr<TranslationUnitDecl> > ();
        break;

      case 106: // unary_expression
        yylhs.value.build< std::shared_ptr<UnaryOperator> > ();
        break;

      case 88: // variable_definition
        yylhs.value.build< std::shared_ptr<VariableDecl> > ();
        break;

      case 82: // while_statement
        yylhs.value.build< std::shared_ptr<WhileStmt> > ();
        break;

      case 91: // binding_declarations
        yylhs.value.build< std::vector<std::shared_ptr<BindingDecl>> > ();
        break;

      case 65: // translation_unit_declarations
      case 75: // member_declaration_list
        yylhs.value.build< std::vector<std::shared_ptr<Decl>> > ();
        break;

      case 112: // expression_list
        yylhs.value.build< std::vector<std::shared_ptr<Expr>> > ();
        break;

      case 101: // map_entry_list
        yylhs.value.build< std::vector<std::shared_ptr<MapEntry>> > ();
        break;

      case 71: // parameter_variables
        yylhs.value.build< std::vector<std::shared_ptr<ParmVarDecl>> > ();
        break;

      case 79: // statement_list
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
#line 205 "Parser/Parser.yy" // lalr1.cc:859
    { driver.ast.translationUnit = TranslationUnitDecl::make(toLoc(yylhs.location), std::vector<std::shared_ptr<Decl>>{}); }
#line 1101 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 206 "Parser/Parser.yy" // lalr1.cc:859
    { driver.ast.translationUnit = TranslationUnitDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::vector<std::shared_ptr<Decl>> > ()); }
#line 1107 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 210 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Decl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Decl> > ()); }
#line 1113 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 211 "Parser/Parser.yy" // lalr1.cc:859
    { yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Decl> > ()); yylhs.value.as< std::vector<std::shared_ptr<Decl>> > () = std::move(yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ()); }
#line 1119 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 215 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[0].value.as< std::shared_ptr<ClassDecl> > (); }
#line 1125 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 216 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[0].value.as< std::shared_ptr<FunctionDecl> > (); }
#line 1131 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 220 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<FunctionDecl> > () = FunctionDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), std::get<0>(yystack_[1].value.as< CallSignature > ()), std::get<1>(yystack_[1].value.as< CallSignature > ()), yystack_[0].value.as< std::shared_ptr<CompoundStmt> > ()); }
#line 1137 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 224 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<FunctionExpr> > () = FunctionExpr::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), std::get<0>(yystack_[1].value.as< CallSignature > ()), std::get<1>(yystack_[1].value.as< CallSignature > ()), yystack_[0].value.as< std::shared_ptr<CompoundStmt> > ()); }
#line 1143 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 228 "Parser/Parser.yy" // lalr1.cc:859
    { std::get<1>(yylhs.value.as< CallSignature > ()) = nullptr; }
#line 1149 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 229 "Parser/Parser.yy" // lalr1.cc:859
    { std::get<1>(yylhs.value.as< CallSignature > ()) = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1155 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 230 "Parser/Parser.yy" // lalr1.cc:859
    { std::get<0>(yylhs.value.as< CallSignature > ()) = yystack_[1].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > (); std::get<1>(yylhs.value.as< CallSignature > ()) = nullptr; }
#line 1161 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 231 "Parser/Parser.yy" // lalr1.cc:859
    { std::get<0>(yylhs.value.as< CallSignature > ()) = yystack_[3].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > (); std::get<1>(yylhs.value.as< CallSignature > ()) = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1167 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 235 "Parser/Parser.yy" // lalr1.cc:859
    { }
#line 1173 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 236 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NamedDecl> > () = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1179 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 240 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<ParmVarDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<ParmVarDecl> > ()); }
#line 1185 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 241 "Parser/Parser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<ParmVarDecl> > ()); yylhs.value.as< std::vector<std::shared_ptr<ParmVarDecl>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > ()); }
#line 1191 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 245 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ParmVarDecl> > () = ParmVarDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1197 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 246 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ParmVarDecl> > () = ParmVarDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1203 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 250 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NamedDecl> > () = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1209 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 254 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ClassDecl> > () = ClassDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), std::vector<std::shared_ptr<Decl>>{}); }
#line 1215 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 255 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ClassDecl> > () = ClassDecl::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<NamedDecl> > (), yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ()); }
#line 1221 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 259 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Decl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Decl> > ()); }
#line 1227 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 260 "Parser/Parser.yy" // lalr1.cc:859
    { yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Decl> > ()); yylhs.value.as< std::vector<std::shared_ptr<Decl>> > () = std::move(yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ()); }
#line 1233 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 264 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[0].value.as< std::shared_ptr<FunctionDecl> > (); }
#line 1239 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 265 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[1].value.as< std::shared_ptr<VariableDecl> > (); }
#line 1245 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 269 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<CompoundStmt> > (); }
#line 1251 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 270 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[1].value.as< std::shared_ptr<Expr> > (); }
#line 1257 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 271 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ReturnStmt> > (); }
#line 1263 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 272 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<VariableDecl> > ()); }
#line 1269 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 273 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<DecompositionDecl> > ()); }
#line 1275 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 274 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<IfStmt> > (); }
#line 1281 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 275 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<WhileStmt> > (); }
#line 1287 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 276 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ForStmt> > (); }
#line 1293 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 277 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ForRangeStmt> > (); }
#line 1299 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 278 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<DeferStmt> > (); }
#line 1305 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 282 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CompoundStmt> > () = CompoundStmt::make(toLoc(yylhs.location), std::vector<std::shared_ptr<Stmt>>{}); }
#line 1311 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 283 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CompoundStmt> > () = CompoundStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ()); }
#line 1317 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 287 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Stmt>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1323 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 288 "Parser/Parser.yy" // lalr1.cc:859
    { yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Stmt> > ()); yylhs.value.as< std::vector<std::shared_ptr<Stmt>> > () = std::move(yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ()); }
#line 1329 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 292 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ReturnStmt> > () = ReturnStmt::make(toLoc(yylhs.location)); }
#line 1335 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 293 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ReturnStmt> > () = ReturnStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1341 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 297 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IfStmt> > () = IfStmt::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1347 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 298 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IfStmt> > () = IfStmt::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[2].value.as< std::shared_ptr<Stmt> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1353 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 302 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<WhileStmt> > () = WhileStmt::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1359 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 306 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ForStmt> > () = ForStmt::make(toLoc(yylhs.location), yystack_[5].value.as< std::shared_ptr<Stmt> > (), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1365 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 310 "Parser/Parser.yy" // lalr1.cc:859
    { }
#line 1371 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 311 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[1].value.as< std::shared_ptr<Expr> > (); }
#line 1377 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 312 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<VariableDecl> > ()); }
#line 1383 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 316 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ForRangeStmt> > () = ForRangeStmt::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Decl> > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1389 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 320 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1395 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 321 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > (), yystack_[1].value.as< VariableDeclSpecifier > (), nullptr, nullptr); }
#line 1401 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 322 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = DecompositionDecl::make(toLoc(yylhs.location), yystack_[3].value.as< VariableDeclSpecifier > (), yystack_[1].value.as< std::vector<std::shared_ptr<BindingDecl>> > ()); }
#line 1407 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 326 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<DeferStmt> > () = DeferStmt::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1413 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 330 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VariableDecl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > (), yystack_[1].value.as< VariableDeclSpecifier > (), nullptr, nullptr); }
#line 1419 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 331 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VariableDecl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[3].value.as< VariableDeclSpecifier > (), nullptr, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1425 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 332 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VariableDecl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[3].value.as< VariableDeclSpecifier > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > (), nullptr); }
#line 1431 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 333 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VariableDecl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<NamedDecl> > (), yystack_[5].value.as< VariableDeclSpecifier > (), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1437 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 337 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< VariableDeclSpecifier > () = VariableDeclSpecifier::Let; }
#line 1443 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 338 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< VariableDeclSpecifier > () = VariableDeclSpecifier::Var; }
#line 1449 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 339 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< VariableDeclSpecifier > () = VariableDeclSpecifier::Const; }
#line 1455 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 343 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<DecompositionDecl> > () = DecompositionDecl::make(toLoc(yylhs.location), yystack_[5].value.as< VariableDeclSpecifier > (), yystack_[3].value.as< std::vector<std::shared_ptr<BindingDecl>> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1461 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 347 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<BindingDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<BindingDecl> > ()); }
#line 1467 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 348 "Parser/Parser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<BindingDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<BindingDecl> > ()); yylhs.value.as< std::vector<std::shared_ptr<BindingDecl>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<BindingDecl>> > ()); }
#line 1473 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 352 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BindingDecl> > () = BindingDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1479 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 356 "Parser/Parser.yy" // lalr1.cc:859
    { }
#line 1485 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 357 "Parser/Parser.yy" // lalr1.cc:859
    { }
#line 1491 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 361 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<IntegerLiteral> > (); }
#line 1497 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 362 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<DoubleLiteral> > (); }
#line 1503 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 363 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<BoolLiteral> > (); }
#line 1509 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 364 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<StringLiteral> > (); }
#line 1515 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 368 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<Expr> > (); }
#line 1521 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 369 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<NullLiteral> > (); }
#line 1527 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 370 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = DeclRefExpr::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1533 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 371 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<ParenExpr> > (); }
#line 1539 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 372 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<ArrayLiteral> > (); }
#line 1545 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 373 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<MapLiteral> > (); }
#line 1551 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 374 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<CallExpr> > (); }
#line 1557 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 375 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<MemberExpr> > (); }
#line 1563 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 376 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<SubscriptExpr> > (); }
#line 1569 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 377 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<NullConditionalOperator> > (); }
#line 1575 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 381 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ParenExpr> > () = ParenExpr::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1581 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 385 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullLiteral> > () = NullLiteral::make(toLoc(yylhs.location)); }
#line 1587 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 389 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ArrayLiteral> > () = ArrayLiteral::make(toLoc(yylhs.location), std::vector<std::shared_ptr<Expr>>{}); }
#line 1593 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 390 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ArrayLiteral> > () = ArrayLiteral::make(toLoc(yylhs.location), yystack_[2].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1599 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 394 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MapLiteral> > () = MapLiteral::make(toLoc(yylhs.location), std::vector<std::shared_ptr<MapEntry>>{}); }
#line 1605 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 395 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MapLiteral> > () = MapLiteral::make(toLoc(yylhs.location), yystack_[2].value.as< std::vector<std::shared_ptr<MapEntry>> > ()); }
#line 1611 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 399 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MapEntry> > () = MapEntry::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1617 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 403 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<MapEntry>> > ().push_back(yystack_[0].value.as< std::shared_ptr<MapEntry> > ()); }
#line 1623 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 404 "Parser/Parser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<MapEntry>> > ().push_back(yystack_[0].value.as< std::shared_ptr<MapEntry> > ()); yylhs.value.as< std::vector<std::shared_ptr<MapEntry>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<MapEntry>> > ()); }
#line 1629 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 408 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MemberExpr> > () = MemberExpr::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1635 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 412 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<SubscriptExpr> > () = SubscriptExpr::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1641 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 416 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CallExpr> > () = CallExpr::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), std::vector<std::shared_ptr<Expr>>{}); }
#line 1647 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 417 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CallExpr> > () = CallExpr::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1653 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 421 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullConditionalOperator> > () = NullConditionalOperator::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<Expr> > (), MemberExpr::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ())); }
#line 1659 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 422 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullConditionalOperator> > () = NullConditionalOperator::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Expr> > (), SubscriptExpr::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::shared_ptr<Expr> > ())); }
#line 1665 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 423 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullConditionalOperator> > () = NullConditionalOperator::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<Expr> > (), CallExpr::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<Expr> > (), std::vector<std::shared_ptr<Expr>>{})); }
#line 1671 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 424 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullConditionalOperator> > () = NullConditionalOperator::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Expr> > (), CallExpr::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::vector<std::shared_ptr<Expr>> > ())); }
#line 1677 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 428 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PreInc, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1683 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 429 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PreDec, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1689 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 430 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PostInc, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1695 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 431 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PostDec, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1701 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 432 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::Plus, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1707 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 433 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::Minus, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1713 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 434 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::LogicalNot, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1719 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 438 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::Add; }
#line 1725 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 439 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::Subtract; }
#line 1731 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 440 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::Multiply; }
#line 1737 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 441 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::Divide; }
#line 1743 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 442 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::Mod; }
#line 1749 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 443 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::Equal; }
#line 1755 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 444 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::NotEqual; }
#line 1761 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 445 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::LogicalAnd; }
#line 1767 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 446 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::LogicalOr; }
#line 1773 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 447 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::GreaterThan; }
#line 1779 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 448 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::GreaterThanOrEqual; }
#line 1785 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 449 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::LessThan; }
#line 1791 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 450 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::LessThanOrEqual; }
#line 1797 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 451 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< BinaryOperatorKind > () = BinaryOperatorKind::NullCoalescing; }
#line 1803 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 455 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), yystack_[1].value.as< BinaryOperatorKind > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1809 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 459 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ConditionalOperator> > () = ConditionalOperator::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1815 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 463 "Parser/Parser.yy" // lalr1.cc:859
    { }
#line 1821 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 467 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Assign, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1827 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 471 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Expr>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1833 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 472 "Parser/Parser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<Expr>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Expr> > ()); yylhs.value.as< std::vector<std::shared_ptr<Expr>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1839 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 476 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<Expr> > (); }
#line 1845 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 477 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<BinaryOperator> > (); }
#line 1851 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 478 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<BinaryOperator> > (); }
#line 1857 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 479 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<UnaryOperator> > (); }
#line 1863 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 480 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<ConditionalOperator> > (); }
#line 1869 "Parser/Parser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 481 "Parser/Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<FunctionExpr> > (); }
#line 1875 "Parser/Parser.cpp" // lalr1.cc:859
    break;


#line 1879 "Parser/Parser.cpp" // lalr1.cc:859
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


  const signed char Parser::yypact_ninf_ = -112;

  const signed char Parser::yytable_ninf_ = -56;

  const short int
  Parser::yypact_[] =
  {
       9,   -40,   -25,    25,     9,  -112,  -112,  -112,     2,     4,
    -112,  -112,   -11,    23,    84,    10,    20,    -9,  -112,   148,
    -112,  -112,  -112,  -112,  -112,  -112,   104,  -112,    29,    32,
      33,    33,    50,    49,   -17,   -17,   -17,   -17,   -17,   370,
    -112,   258,    59,   310,    35,    89,    93,   252,  -112,  -112,
    -112,  -112,  -112,  -112,  -112,  -112,  -112,   200,  -112,  -112,
    -112,  -112,  -112,  -112,    98,    -3,   103,  -112,   102,  -112,
    -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,
    -112,   423,  -112,  -112,  -112,    11,  -112,  -112,  -112,    33,
    -112,    94,    94,    94,    94,    94,    71,  -112,    91,  -112,
     107,   110,   445,  -112,     2,  -112,   467,   370,   370,    14,
    -112,  -112,  -112,  -112,    96,  -112,  -112,  -112,   318,   370,
      97,    28,   370,   370,  -112,  -112,  -112,  -112,  -112,  -112,
    -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,   370,
     370,    33,  -112,    28,  -112,  -112,   370,   119,   370,   130,
     370,    23,  -112,   489,   513,  -112,   114,   370,   124,   118,
      -2,   537,  -112,    47,  -112,  -112,    72,   719,   559,  -112,
     362,   370,   116,   593,   719,   213,   719,   175,  -112,   445,
    -112,   719,  -112,   719,  -112,   252,   252,   615,   370,  -112,
      96,    13,  -112,   176,    96,  -112,   370,  -112,  -112,    73,
     637,  -112,   370,   370,   136,  -112,   370,   671,    75,   370,
    -112,  -112,  -112,   213,   719,   252,   695,   252,  -112,   719,
    -112,   252,  -112,  -112
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       2,     0,     0,     0,     3,     4,     7,     6,     0,     0,
       1,     5,     0,     0,     0,    10,    18,     0,    16,     0,
       8,    21,    59,    60,    61,    25,     0,    23,     0,     0,
       0,     0,    12,     0,     0,     0,     0,     0,     0,     0,
      37,     0,    14,     0,     0,     0,     0,     0,    83,    74,
      68,    69,    70,    71,   131,    39,    27,     0,    29,    32,
      33,    34,    35,    36,     0,     0,     0,    72,   126,    75,
      73,    76,    77,    79,    80,    78,    81,   129,   128,   130,
     127,     0,    22,    24,    26,    55,    20,    11,    19,     0,
      17,   104,   103,    99,   100,   105,     0,    84,     0,    89,
      66,    66,   124,    15,     0,    41,     0,     0,     0,     0,
      54,    38,    40,    30,     0,    31,   101,   102,     0,     0,
       0,   122,     0,     0,   107,   106,   108,   109,   110,   113,
     114,   111,   112,   118,   116,   117,   115,    28,   119,     0,
       0,     0,    13,     0,    82,    86,    67,     0,    67,     0,
       0,     0,    42,     0,     0,    47,    74,     0,     0,     0,
       0,     0,    65,     0,    63,    93,     0,   124,     0,    91,
       0,     0,     0,     0,   123,   120,    56,    57,    90,     0,
      87,   125,    85,    88,     9,     0,     0,     0,     0,    49,
       0,    52,    48,     0,     0,    94,     0,    92,    97,     0,
       0,    95,     0,     0,    43,    45,     0,     0,     0,     0,
      64,    98,    96,   121,    58,     0,     0,     0,    53,    62,
      44,     0,    50,    46
  };

  const short int
  Parser::yypgoto_[] =
  {
    -112,  -112,  -112,   177,     6,  -112,    78,  -112,  -112,   150,
     -26,  -112,  -112,   158,   -47,   -10,  -112,  -112,  -112,  -112,
    -112,  -112,  -112,  -112,  -112,   -13,    -5,  -112,     5,     3,
     105,  -112,   120,  -112,  -112,  -112,  -112,    39,  -112,  -112,
    -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,  -111,
     -37
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,     5,     6,    54,    13,   104,    17,    18,
      87,     7,    26,    27,    55,    56,    57,    58,    59,    60,
      61,   157,    62,   158,    63,    64,    65,    66,   163,   164,
     147,    67,    68,    69,    70,    71,    72,    99,   100,    73,
      74,    75,    76,    77,   139,    78,    79,   122,    80,   101,
      81
  };

  const short int
  Parser::yytable_[] =
  {
     110,    28,    96,    20,   102,    88,   106,   166,    39,    29,
     112,     8,    41,    28,   140,    15,   140,    32,    34,    35,
      25,    29,   114,   190,    33,    10,     9,    12,    36,    37,
      38,    14,    25,    48,    49,    50,    51,    52,    53,    39,
      16,    30,   141,    41,   141,   -55,   155,     1,    85,   191,
      19,    31,    42,   170,    22,    23,    24,   171,     2,   199,
     107,    84,   172,   142,    48,   156,    50,    51,    52,    53,
     153,   154,   161,   193,   123,   124,   125,   126,   127,   128,
     194,   167,   168,    85,    86,   173,   174,    89,   129,   130,
     131,   132,   133,   134,   135,   136,   159,   144,   195,   211,
      16,   218,   175,   176,   160,   196,   196,   138,   194,   179,
     103,   181,    21,   183,   108,   177,   116,   117,   109,   118,
     187,   145,     1,   119,    22,    23,    24,   118,   120,   143,
     113,   119,    82,   167,   200,   115,   120,   121,   204,   205,
     146,   184,     1,   148,    22,    23,    24,   162,   169,   180,
     189,   207,    34,    35,    91,    92,    93,    94,    95,   181,
     182,   -51,    36,    37,    38,   213,   214,   201,   220,   216,
     222,   188,   219,    39,   223,    19,    40,    41,   203,   209,
     215,    11,   151,    90,    83,   178,    42,    43,    22,    23,
      24,    44,     0,    45,    46,   208,    47,   210,    48,    49,
      50,    51,    52,    53,    34,    35,   149,     0,     0,     0,
       0,     0,     0,     0,    36,    37,    38,   124,   125,   126,
     127,   128,     0,     0,     0,    39,     0,    19,   111,    41,
     129,   130,   131,   132,   133,   134,   135,   136,    42,    43,
      22,    23,    24,    44,     0,    45,    46,     0,    47,   138,
      48,    49,    50,    51,    52,    53,    34,    35,     0,     0,
       0,     0,    34,    35,     0,     0,    36,    37,    38,     0,
       0,     0,    36,    37,    38,     0,     0,    39,     0,    19,
       0,    41,     0,    39,     0,     0,     0,    41,    97,    98,
      42,    43,    22,    23,    24,    44,    42,    45,    46,     0,
      47,     0,    48,    49,    50,    51,    52,    53,    48,    49,
      50,    51,    52,    53,    34,    35,     0,     0,     0,     0,
       0,     0,    34,    35,    36,    37,    38,     0,     0,     0,
       0,     0,    36,    37,    38,    39,     0,     0,     0,    41,
       0,     0,   105,    39,   165,     0,     0,    41,    42,     0,
       0,     0,     0,     0,     0,     0,    42,     0,     0,     0,
      48,    49,    50,    51,    52,    53,    34,    35,    48,    49,
      50,    51,    52,    53,    34,    35,    36,    37,    38,     0,
       0,     0,     0,     0,    36,    37,    38,    39,   198,     0,
       0,    41,     0,     0,     0,    39,     0,     0,     0,    41,
      42,     0,     0,     0,     0,     0,     0,     0,    42,     0,
       0,     0,    48,    49,    50,    51,    52,    53,     0,     0,
      48,    49,    50,    51,    52,    53,   123,   124,   125,   126,
     127,   128,     0,     0,     0,     0,     0,     0,     0,     0,
     129,   130,   131,   132,   133,   134,   135,   136,   123,   124,
     125,   126,   127,   128,     0,   137,     0,     0,     0,   138,
       0,     0,   129,   130,   131,   132,   133,   134,   135,   136,
     123,   124,   125,   126,   127,   128,   150,     0,     0,     0,
       0,   138,     0,     0,   129,   130,   131,   132,   133,   134,
     135,   136,   123,   124,   125,   126,   127,   128,     0,   152,
       0,     0,     0,   138,     0,     0,   129,   130,   131,   132,
     133,   134,   135,   136,     0,   185,   123,   124,   125,   126,
     127,   128,     0,     0,     0,   138,     0,     0,     0,     0,
     129,   130,   131,   132,   133,   134,   135,   136,     0,   186,
     123,   124,   125,   126,   127,   128,     0,     0,     0,   138,
       0,     0,     0,     0,   129,   130,   131,   132,   133,   134,
     135,   136,   123,   124,   125,   126,   127,   128,     0,   192,
       0,     0,     0,   138,     0,     0,   129,   130,   131,   132,
     133,   134,   135,   136,     0,     0,     0,     0,     0,   197,
       0,     0,     0,     0,     0,   138,   123,   124,   125,   126,
     127,   128,     0,     0,     0,     0,     0,     0,     0,     0,
     129,   130,   131,   132,   133,   134,   135,   136,   123,   124,
     125,   126,   127,   128,   202,     0,     0,     0,     0,   138,
       0,     0,   129,   130,   131,   132,   133,   134,   135,   136,
     123,   124,   125,   126,   127,   128,     0,   206,     0,     0,
       0,   138,     0,     0,   129,   130,   131,   132,   133,   134,
     135,   136,     0,     0,     0,     0,     0,   212,     0,     0,
       0,     0,     0,   138,   123,   124,   125,   126,   127,   128,
       0,     0,     0,     0,     0,     0,     0,     0,   129,   130,
     131,   132,   133,   134,   135,   136,     0,   217,   123,   124,
     125,   126,   127,   128,     0,     0,     0,   138,     0,     0,
       0,     0,   129,   130,   131,   132,   133,   134,   135,   136,
       0,   221,   123,   124,   125,   126,   127,   128,     0,     0,
       0,   138,     0,     0,     0,     0,   129,   130,   131,   132,
     133,   134,   135,   136,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   138
  };

  const short int
  Parser::yycheck_[] =
  {
      47,    14,    39,    13,    41,    31,    43,   118,    25,    14,
      57,    51,    29,    26,     3,    26,     3,    26,     4,     5,
      14,    26,    25,    25,    33,     0,    51,    25,    14,    15,
      16,    27,    26,    50,    51,    52,    53,    54,    55,    25,
      51,    31,    31,    29,    31,    32,    32,    38,    51,    51,
      27,    31,    38,    25,    40,    41,    42,    29,    49,   170,
      25,    32,    34,    89,    50,    51,    52,    53,    54,    55,
     107,   108,   109,    26,     3,     4,     5,     6,     7,     8,
      33,   118,   119,    51,    51,   122,   123,    37,    17,    18,
      19,    20,    21,    22,    23,    24,   109,    26,    26,    26,
      51,    26,   139,   140,   109,    33,    33,    36,    33,   146,
      51,   148,    28,   150,    25,   141,    14,    15,    25,    25,
     157,    30,    38,    29,    40,    41,    42,    25,    34,    35,
      32,    29,    28,   170,   171,    32,    34,    35,   185,   186,
      33,   151,    38,    33,    40,    41,    42,    51,    51,    30,
      32,   188,     4,     5,    34,    35,    36,    37,    38,   196,
      30,    47,    14,    15,    16,   202,   203,    51,   215,   206,
     217,    47,   209,    25,   221,    27,    28,    29,     3,     3,
      44,     4,   104,    33,    26,   146,    38,    39,    40,    41,
      42,    43,    -1,    45,    46,   190,    48,   194,    50,    51,
      52,    53,    54,    55,     4,     5,   101,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    14,    15,    16,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    25,    -1,    27,    28,    29,
      17,    18,    19,    20,    21,    22,    23,    24,    38,    39,
      40,    41,    42,    43,    -1,    45,    46,    -1,    48,    36,
      50,    51,    52,    53,    54,    55,     4,     5,    -1,    -1,
      -1,    -1,     4,     5,    -1,    -1,    14,    15,    16,    -1,
      -1,    -1,    14,    15,    16,    -1,    -1,    25,    -1,    27,
      -1,    29,    -1,    25,    -1,    -1,    -1,    29,    30,    31,
      38,    39,    40,    41,    42,    43,    38,    45,    46,    -1,
      48,    -1,    50,    51,    52,    53,    54,    55,    50,    51,
      52,    53,    54,    55,     4,     5,    -1,    -1,    -1,    -1,
      -1,    -1,     4,     5,    14,    15,    16,    -1,    -1,    -1,
      -1,    -1,    14,    15,    16,    25,    -1,    -1,    -1,    29,
      -1,    -1,    32,    25,    26,    -1,    -1,    29,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    -1,
      50,    51,    52,    53,    54,    55,     4,     5,    50,    51,
      52,    53,    54,    55,     4,     5,    14,    15,    16,    -1,
      -1,    -1,    -1,    -1,    14,    15,    16,    25,    26,    -1,
      -1,    29,    -1,    -1,    -1,    25,    -1,    -1,    -1,    29,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    -1,    50,    51,    52,    53,    54,    55,    -1,    -1,
      50,    51,    52,    53,    54,    55,     3,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,     3,     4,
       5,     6,     7,     8,    -1,    32,    -1,    -1,    -1,    36,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
       3,     4,     5,     6,     7,     8,    31,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,     3,     4,     5,     6,     7,     8,    -1,    32,
      -1,    -1,    -1,    36,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,    -1,    26,     3,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,    -1,    26,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,     3,     4,     5,     6,     7,     8,    -1,    32,
      -1,    -1,    -1,    36,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    -1,    -1,    -1,    -1,    36,     3,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,     3,     4,
       5,     6,     7,     8,    31,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
       3,     4,     5,     6,     7,     8,    -1,    32,    -1,    -1,
      -1,    36,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,
      -1,    -1,    -1,    36,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    -1,    26,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    36,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,     3,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,    38,    49,    64,    65,    66,    67,    74,    51,    51,
       0,    66,    25,    69,    27,    26,    51,    71,    72,    27,
      78,    28,    40,    41,    42,    67,    75,    76,    88,    89,
      31,    31,    26,    33,     4,     5,    14,    15,    16,    25,
      28,    29,    38,    39,    43,    45,    46,    48,    50,    51,
      52,    53,    54,    55,    68,    77,    78,    79,    80,    81,
      82,    83,    85,    87,    88,    89,    90,    94,    95,    96,
      97,    98,    99,   102,   103,   104,   105,   106,   108,   109,
     111,   113,    28,    76,    32,    51,    51,    73,    73,    37,
      72,    95,    95,    95,    95,    95,   113,    30,    31,   100,
     101,   112,   113,    51,    70,    32,   113,    25,    25,    25,
      77,    28,    77,    32,    25,    32,    14,    15,    25,    29,
      34,    35,   110,     3,     4,     5,     6,     7,     8,    17,
      18,    19,    20,    21,    22,    23,    24,    32,    36,   107,
       3,    31,    73,    35,    26,    30,    33,    93,    33,    93,
      31,    69,    32,   113,   113,    32,    51,    84,    86,    88,
      89,   113,    51,    91,    92,    26,   112,   113,   113,    51,
      25,    29,    34,   113,   113,   113,   113,    73,   100,   113,
      30,   113,    30,   113,    78,    26,    26,   113,    47,    32,
      25,    51,    32,    26,    33,    26,    33,    30,    26,   112,
     113,    51,    31,     3,    77,    77,    32,   113,    91,     3,
      92,    26,    30,   113,   113,    44,   113,    26,    26,   113,
      77,    26,    77,    77
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    63,    64,    64,    65,    65,    66,    66,    67,    68,
      69,    69,    69,    69,    70,    70,    71,    71,    72,    72,
      73,    74,    74,    75,    75,    76,    76,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    78,    78,    79,
      79,    80,    80,    81,    81,    82,    83,    84,    84,    84,
      85,    86,    86,    86,    87,    88,    88,    88,    88,    89,
      89,    89,    90,    91,    91,    92,    93,    93,    94,    94,
      94,    94,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    96,    97,    98,    98,    99,    99,   100,   101,
     101,   102,   103,   104,   104,   105,   105,   105,   105,   106,
     106,   106,   106,   106,   106,   106,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     108,   109,   110,   111,   112,   112,   113,   113,   113,   113,
     113,   113
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     0,     1,     1,     2,     1,     1,     4,     4,
       2,     4,     3,     5,     0,     1,     1,     3,     1,     3,
       1,     4,     5,     1,     2,     1,     2,     1,     2,     1,
       2,     2,     1,     1,     1,     1,     1,     2,     3,     1,
       2,     2,     3,     5,     7,     5,     8,     1,     2,     2,
       7,     1,     2,     4,     2,     2,     4,     4,     6,     1,
       1,     1,     6,     1,     3,     1,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     2,     4,     3,     4,     3,     1,
       3,     3,     4,     3,     4,     4,     5,     4,     5,     2,
       2,     2,     2,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     5,     1,     3,     1,     3,     1,     1,     1,     1,
       1,     1
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
  "\"var\"", "\"const\"", "\"if\"", "\"else\"", "\"while\"", "\"for\"",
  "\"in\"", "\"defer\"", "\"class\"", "\"null\"", "\"identifier\"",
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
  "variable_decl_specifier", "decomposition_definition",
  "binding_declarations", "binding_declaration", "comma_opt", "literal",
  "primary_expression", "parenthesized_expression", "null_literal",
  "array_literal", "map_literal", "map_entry", "map_entry_list",
  "member_expression", "subscript_expression", "call_expression",
  "null_conditional_expression", "unary_expression", "binary_op",
  "binary_expression", "conditional_expression", "ternary_question",
  "assignment_expression", "expression_list", "expression", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   205,   205,   206,   210,   211,   215,   216,   220,   224,
     228,   229,   230,   231,   235,   236,   240,   241,   245,   246,
     250,   254,   255,   259,   260,   264,   265,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   282,   283,   287,
     288,   292,   293,   297,   298,   302,   306,   310,   311,   312,
     316,   320,   321,   322,   326,   330,   331,   332,   333,   337,
     338,   339,   343,   347,   348,   352,   356,   357,   361,   362,
     363,   364,   368,   369,   370,   371,   372,   373,   374,   375,
     376,   377,   381,   385,   389,   390,   394,   395,   399,   403,
     404,   408,   412,   416,   417,   421,   422,   423,   424,   428,
     429,   430,   431,   432,   433,   434,   438,   439,   440,   441,
     442,   443,   444,   445,   446,   447,   448,   449,   450,   451,
     455,   459,   463,   467,   471,   472,   476,   477,   478,   479,
     480,   481
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
#line 2533 "Parser/Parser.cpp" // lalr1.cc:1167
#line 484 "Parser/Parser.yy" // lalr1.cc:1168


void yy::Parser::error(const location_type& l, const std::string& m)
{
    driver.error(toLoc(l), m);
}
