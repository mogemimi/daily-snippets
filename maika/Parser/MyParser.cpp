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
      case 62: // call_signature
        value.move< CallSignature > (that.value);
        break;

      case 89: // array_literal
        value.move< std::shared_ptr<ArrayLiteral> > (that.value);
        break;

      case 97: // binary_expression
      case 98: // assignment_expression
        value.move< std::shared_ptr<BinaryOperator> > (that.value);
        break;

      case 84: // binding_declaration
        value.move< std::shared_ptr<BindingDecl> > (that.value);
        break;

      case 51: // "bool_literal"
        value.move< std::shared_ptr<BoolLiteral> > (that.value);
        break;

      case 95: // call_expression
        value.move< std::shared_ptr<CallExpr> > (that.value);
        break;

      case 67: // class_declaration
        value.move< std::shared_ptr<ClassDecl> > (that.value);
        break;

      case 71: // compound_statement
        value.move< std::shared_ptr<CompoundStmt> > (that.value);
        break;

      case 81: // const_definition
        value.move< std::shared_ptr<ConstDecl> > (that.value);
        break;

      case 59: // translation_unit_declaration
      case 69: // member_declaration
      case 79: // for_range_init
        value.move< std::shared_ptr<Decl> > (that.value);
        break;

      case 82: // decomposition_definition
        value.move< std::shared_ptr<DecompositionDecl> > (that.value);
        break;

      case 50: // "double_literal"
        value.move< std::shared_ptr<DoubleLiteral> > (that.value);
        break;

      case 86: // literal
      case 87: // primary_expression
      case 100: // expression
        value.move< std::shared_ptr<Expr> > (that.value);
        break;

      case 78: // for_range_statement
        value.move< std::shared_ptr<ForRangeStmt> > (that.value);
        break;

      case 76: // for_statement
        value.move< std::shared_ptr<ForStmt> > (that.value);
        break;

      case 60: // function_definition
        value.move< std::shared_ptr<FunctionDecl> > (that.value);
        break;

      case 61: // function_expression
        value.move< std::shared_ptr<FunctionExpr> > (that.value);
        break;

      case 74: // if_statement
        value.move< std::shared_ptr<IfStmt> > (that.value);
        break;

      case 49: // "integer_literal"
        value.move< std::shared_ptr<IntegerLiteral> > (that.value);
        break;

      case 91: // map_entry
        value.move< std::shared_ptr<MapEntry> > (that.value);
        break;

      case 90: // map_literal
        value.move< std::shared_ptr<MapLiteral> > (that.value);
        break;

      case 93: // member_expression
        value.move< std::shared_ptr<MemberExpr> > (that.value);
        break;

      case 48: // "identifier"
      case 63: // binding_identifier
      case 66: // type_specifier
        value.move< std::shared_ptr<NamedDecl> > (that.value);
        break;

      case 88: // null_literal
        value.move< std::shared_ptr<NullLiteral> > (that.value);
        break;

      case 65: // parameter_variable
        value.move< std::shared_ptr<ParmVarDecl> > (that.value);
        break;

      case 73: // return_statement
        value.move< std::shared_ptr<ReturnStmt> > (that.value);
        break;

      case 70: // statement
      case 77: // for_init_statement
        value.move< std::shared_ptr<Stmt> > (that.value);
        break;

      case 52: // "string_literal"
        value.move< std::shared_ptr<StringLiteral> > (that.value);
        break;

      case 94: // subscript_expression
        value.move< std::shared_ptr<SubscriptExpr> > (that.value);
        break;

      case 57: // translation_unit
        value.move< std::shared_ptr<TranslationUnitDecl> > (that.value);
        break;

      case 96: // unary_expression
        value.move< std::shared_ptr<UnaryOperator> > (that.value);
        break;

      case 80: // variable_definition
        value.move< std::shared_ptr<VariableDecl> > (that.value);
        break;

      case 75: // while_statement
        value.move< std::shared_ptr<WhileStmt> > (that.value);
        break;

      case 83: // binding_declarations
        value.move< std::vector<std::shared_ptr<BindingDecl>> > (that.value);
        break;

      case 58: // translation_unit_declarations
      case 68: // member_declaration_list
        value.move< std::vector<std::shared_ptr<Decl>> > (that.value);
        break;

      case 99: // expression_list
        value.move< std::vector<std::shared_ptr<Expr>> > (that.value);
        break;

      case 92: // map_entry_list
        value.move< std::vector<std::shared_ptr<MapEntry>> > (that.value);
        break;

      case 64: // parameter_variables
        value.move< std::vector<std::shared_ptr<ParmVarDecl>> > (that.value);
        break;

      case 72: // statement_list
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
      case 62: // call_signature
        value.copy< CallSignature > (that.value);
        break;

      case 89: // array_literal
        value.copy< std::shared_ptr<ArrayLiteral> > (that.value);
        break;

      case 97: // binary_expression
      case 98: // assignment_expression
        value.copy< std::shared_ptr<BinaryOperator> > (that.value);
        break;

      case 84: // binding_declaration
        value.copy< std::shared_ptr<BindingDecl> > (that.value);
        break;

      case 51: // "bool_literal"
        value.copy< std::shared_ptr<BoolLiteral> > (that.value);
        break;

      case 95: // call_expression
        value.copy< std::shared_ptr<CallExpr> > (that.value);
        break;

      case 67: // class_declaration
        value.copy< std::shared_ptr<ClassDecl> > (that.value);
        break;

      case 71: // compound_statement
        value.copy< std::shared_ptr<CompoundStmt> > (that.value);
        break;

      case 81: // const_definition
        value.copy< std::shared_ptr<ConstDecl> > (that.value);
        break;

      case 59: // translation_unit_declaration
      case 69: // member_declaration
      case 79: // for_range_init
        value.copy< std::shared_ptr<Decl> > (that.value);
        break;

      case 82: // decomposition_definition
        value.copy< std::shared_ptr<DecompositionDecl> > (that.value);
        break;

      case 50: // "double_literal"
        value.copy< std::shared_ptr<DoubleLiteral> > (that.value);
        break;

      case 86: // literal
      case 87: // primary_expression
      case 100: // expression
        value.copy< std::shared_ptr<Expr> > (that.value);
        break;

      case 78: // for_range_statement
        value.copy< std::shared_ptr<ForRangeStmt> > (that.value);
        break;

      case 76: // for_statement
        value.copy< std::shared_ptr<ForStmt> > (that.value);
        break;

      case 60: // function_definition
        value.copy< std::shared_ptr<FunctionDecl> > (that.value);
        break;

      case 61: // function_expression
        value.copy< std::shared_ptr<FunctionExpr> > (that.value);
        break;

      case 74: // if_statement
        value.copy< std::shared_ptr<IfStmt> > (that.value);
        break;

      case 49: // "integer_literal"
        value.copy< std::shared_ptr<IntegerLiteral> > (that.value);
        break;

      case 91: // map_entry
        value.copy< std::shared_ptr<MapEntry> > (that.value);
        break;

      case 90: // map_literal
        value.copy< std::shared_ptr<MapLiteral> > (that.value);
        break;

      case 93: // member_expression
        value.copy< std::shared_ptr<MemberExpr> > (that.value);
        break;

      case 48: // "identifier"
      case 63: // binding_identifier
      case 66: // type_specifier
        value.copy< std::shared_ptr<NamedDecl> > (that.value);
        break;

      case 88: // null_literal
        value.copy< std::shared_ptr<NullLiteral> > (that.value);
        break;

      case 65: // parameter_variable
        value.copy< std::shared_ptr<ParmVarDecl> > (that.value);
        break;

      case 73: // return_statement
        value.copy< std::shared_ptr<ReturnStmt> > (that.value);
        break;

      case 70: // statement
      case 77: // for_init_statement
        value.copy< std::shared_ptr<Stmt> > (that.value);
        break;

      case 52: // "string_literal"
        value.copy< std::shared_ptr<StringLiteral> > (that.value);
        break;

      case 94: // subscript_expression
        value.copy< std::shared_ptr<SubscriptExpr> > (that.value);
        break;

      case 57: // translation_unit
        value.copy< std::shared_ptr<TranslationUnitDecl> > (that.value);
        break;

      case 96: // unary_expression
        value.copy< std::shared_ptr<UnaryOperator> > (that.value);
        break;

      case 80: // variable_definition
        value.copy< std::shared_ptr<VariableDecl> > (that.value);
        break;

      case 75: // while_statement
        value.copy< std::shared_ptr<WhileStmt> > (that.value);
        break;

      case 83: // binding_declarations
        value.copy< std::vector<std::shared_ptr<BindingDecl>> > (that.value);
        break;

      case 58: // translation_unit_declarations
      case 68: // member_declaration_list
        value.copy< std::vector<std::shared_ptr<Decl>> > (that.value);
        break;

      case 99: // expression_list
        value.copy< std::vector<std::shared_ptr<Expr>> > (that.value);
        break;

      case 92: // map_entry_list
        value.copy< std::vector<std::shared_ptr<MapEntry>> > (that.value);
        break;

      case 64: // parameter_variables
        value.copy< std::vector<std::shared_ptr<ParmVarDecl>> > (that.value);
        break;

      case 72: // statement_list
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

#line 766 "Parser/MyParser.cpp" // lalr1.cc:745

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
      case 62: // call_signature
        yylhs.value.build< CallSignature > ();
        break;

      case 89: // array_literal
        yylhs.value.build< std::shared_ptr<ArrayLiteral> > ();
        break;

      case 97: // binary_expression
      case 98: // assignment_expression
        yylhs.value.build< std::shared_ptr<BinaryOperator> > ();
        break;

      case 84: // binding_declaration
        yylhs.value.build< std::shared_ptr<BindingDecl> > ();
        break;

      case 51: // "bool_literal"
        yylhs.value.build< std::shared_ptr<BoolLiteral> > ();
        break;

      case 95: // call_expression
        yylhs.value.build< std::shared_ptr<CallExpr> > ();
        break;

      case 67: // class_declaration
        yylhs.value.build< std::shared_ptr<ClassDecl> > ();
        break;

      case 71: // compound_statement
        yylhs.value.build< std::shared_ptr<CompoundStmt> > ();
        break;

      case 81: // const_definition
        yylhs.value.build< std::shared_ptr<ConstDecl> > ();
        break;

      case 59: // translation_unit_declaration
      case 69: // member_declaration
      case 79: // for_range_init
        yylhs.value.build< std::shared_ptr<Decl> > ();
        break;

      case 82: // decomposition_definition
        yylhs.value.build< std::shared_ptr<DecompositionDecl> > ();
        break;

      case 50: // "double_literal"
        yylhs.value.build< std::shared_ptr<DoubleLiteral> > ();
        break;

      case 86: // literal
      case 87: // primary_expression
      case 100: // expression
        yylhs.value.build< std::shared_ptr<Expr> > ();
        break;

      case 78: // for_range_statement
        yylhs.value.build< std::shared_ptr<ForRangeStmt> > ();
        break;

      case 76: // for_statement
        yylhs.value.build< std::shared_ptr<ForStmt> > ();
        break;

      case 60: // function_definition
        yylhs.value.build< std::shared_ptr<FunctionDecl> > ();
        break;

      case 61: // function_expression
        yylhs.value.build< std::shared_ptr<FunctionExpr> > ();
        break;

      case 74: // if_statement
        yylhs.value.build< std::shared_ptr<IfStmt> > ();
        break;

      case 49: // "integer_literal"
        yylhs.value.build< std::shared_ptr<IntegerLiteral> > ();
        break;

      case 91: // map_entry
        yylhs.value.build< std::shared_ptr<MapEntry> > ();
        break;

      case 90: // map_literal
        yylhs.value.build< std::shared_ptr<MapLiteral> > ();
        break;

      case 93: // member_expression
        yylhs.value.build< std::shared_ptr<MemberExpr> > ();
        break;

      case 48: // "identifier"
      case 63: // binding_identifier
      case 66: // type_specifier
        yylhs.value.build< std::shared_ptr<NamedDecl> > ();
        break;

      case 88: // null_literal
        yylhs.value.build< std::shared_ptr<NullLiteral> > ();
        break;

      case 65: // parameter_variable
        yylhs.value.build< std::shared_ptr<ParmVarDecl> > ();
        break;

      case 73: // return_statement
        yylhs.value.build< std::shared_ptr<ReturnStmt> > ();
        break;

      case 70: // statement
      case 77: // for_init_statement
        yylhs.value.build< std::shared_ptr<Stmt> > ();
        break;

      case 52: // "string_literal"
        yylhs.value.build< std::shared_ptr<StringLiteral> > ();
        break;

      case 94: // subscript_expression
        yylhs.value.build< std::shared_ptr<SubscriptExpr> > ();
        break;

      case 57: // translation_unit
        yylhs.value.build< std::shared_ptr<TranslationUnitDecl> > ();
        break;

      case 96: // unary_expression
        yylhs.value.build< std::shared_ptr<UnaryOperator> > ();
        break;

      case 80: // variable_definition
        yylhs.value.build< std::shared_ptr<VariableDecl> > ();
        break;

      case 75: // while_statement
        yylhs.value.build< std::shared_ptr<WhileStmt> > ();
        break;

      case 83: // binding_declarations
        yylhs.value.build< std::vector<std::shared_ptr<BindingDecl>> > ();
        break;

      case 58: // translation_unit_declarations
      case 68: // member_declaration_list
        yylhs.value.build< std::vector<std::shared_ptr<Decl>> > ();
        break;

      case 99: // expression_list
        yylhs.value.build< std::vector<std::shared_ptr<Expr>> > ();
        break;

      case 92: // map_entry_list
        yylhs.value.build< std::vector<std::shared_ptr<MapEntry>> > ();
        break;

      case 64: // parameter_variables
        yylhs.value.build< std::vector<std::shared_ptr<ParmVarDecl>> > ();
        break;

      case 72: // statement_list
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
#line 177 "Parser/MyParser.yy" // lalr1.cc:859
    { driver.ast.translationUnit = TranslationUnitDecl::make(toLoc(yylhs.location), std::vector<std::shared_ptr<Decl>>{}); }
#line 1041 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 178 "Parser/MyParser.yy" // lalr1.cc:859
    { driver.ast.translationUnit = TranslationUnitDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::vector<std::shared_ptr<Decl>> > ()); }
#line 1047 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 182 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Decl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Decl> > ()); }
#line 1053 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 183 "Parser/MyParser.yy" // lalr1.cc:859
    { yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Decl> > ()); yylhs.value.as< std::vector<std::shared_ptr<Decl>> > () = std::move(yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ()); }
#line 1059 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 187 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[0].value.as< std::shared_ptr<ClassDecl> > (); }
#line 1065 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 188 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[0].value.as< std::shared_ptr<FunctionDecl> > (); }
#line 1071 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 192 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<FunctionDecl> > () = FunctionDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), std::get<0>(yystack_[1].value.as< CallSignature > ()), std::get<1>(yystack_[1].value.as< CallSignature > ()), yystack_[0].value.as< std::shared_ptr<CompoundStmt> > ()); }
#line 1077 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 196 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<FunctionExpr> > () = FunctionExpr::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), std::get<0>(yystack_[1].value.as< CallSignature > ()), std::get<1>(yystack_[1].value.as< CallSignature > ()), yystack_[0].value.as< std::shared_ptr<CompoundStmt> > ()); }
#line 1083 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 200 "Parser/MyParser.yy" // lalr1.cc:859
    { std::get<1>(yylhs.value.as< CallSignature > ()) = nullptr; }
#line 1089 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 201 "Parser/MyParser.yy" // lalr1.cc:859
    { std::get<1>(yylhs.value.as< CallSignature > ()) = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1095 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 202 "Parser/MyParser.yy" // lalr1.cc:859
    { std::get<0>(yylhs.value.as< CallSignature > ()) = yystack_[1].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > (); std::get<1>(yylhs.value.as< CallSignature > ()) = nullptr; }
#line 1101 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 203 "Parser/MyParser.yy" // lalr1.cc:859
    { std::get<0>(yylhs.value.as< CallSignature > ()) = yystack_[3].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > (); std::get<1>(yylhs.value.as< CallSignature > ()) = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1107 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 207 "Parser/MyParser.yy" // lalr1.cc:859
    { }
#line 1113 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 208 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NamedDecl> > () = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1119 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 212 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<ParmVarDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<ParmVarDecl> > ()); }
#line 1125 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 213 "Parser/MyParser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<ParmVarDecl> > ()); yylhs.value.as< std::vector<std::shared_ptr<ParmVarDecl>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > ()); }
#line 1131 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 217 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ParmVarDecl> > () = ParmVarDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1137 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 218 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ParmVarDecl> > () = ParmVarDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1143 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 222 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NamedDecl> > () = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1149 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 226 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ClassDecl> > () = ClassDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), std::vector<std::shared_ptr<Decl>>{}); }
#line 1155 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 227 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ClassDecl> > () = ClassDecl::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<NamedDecl> > (), yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ()); }
#line 1161 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 231 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Decl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Decl> > ()); }
#line 1167 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 232 "Parser/MyParser.yy" // lalr1.cc:859
    { yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Decl> > ()); yylhs.value.as< std::vector<std::shared_ptr<Decl>> > () = std::move(yystack_[1].value.as< std::vector<std::shared_ptr<Decl>> > ()); }
#line 1173 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 236 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[0].value.as< std::shared_ptr<FunctionDecl> > (); }
#line 1179 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 237 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[1].value.as< std::shared_ptr<VariableDecl> > (); }
#line 1185 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 238 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[1].value.as< std::shared_ptr<ConstDecl> > (); }
#line 1191 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 242 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<CompoundStmt> > (); }
#line 1197 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 243 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[1].value.as< std::shared_ptr<Expr> > (); }
#line 1203 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 244 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ReturnStmt> > (); }
#line 1209 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 245 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<VariableDecl> > ()); }
#line 1215 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 246 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<ConstDecl> > ()); }
#line 1221 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 247 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<DecompositionDecl> > ()); }
#line 1227 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 248 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<IfStmt> > (); }
#line 1233 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 249 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<WhileStmt> > (); }
#line 1239 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 250 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ForStmt> > (); }
#line 1245 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 251 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ForRangeStmt> > (); }
#line 1251 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 255 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CompoundStmt> > () = CompoundStmt::make(toLoc(yylhs.location), std::vector<std::shared_ptr<Stmt>>{}); }
#line 1257 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 256 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CompoundStmt> > () = CompoundStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ()); }
#line 1263 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 260 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Stmt>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1269 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 261 "Parser/MyParser.yy" // lalr1.cc:859
    { yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Stmt> > ()); yylhs.value.as< std::vector<std::shared_ptr<Stmt>> > () = std::move(yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ()); }
#line 1275 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 265 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ReturnStmt> > () = ReturnStmt::make(toLoc(yylhs.location)); }
#line 1281 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 266 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ReturnStmt> > () = ReturnStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1287 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 272 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IfStmt> > () = IfStmt::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1293 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 273 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IfStmt> > () = IfStmt::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[2].value.as< std::shared_ptr<Stmt> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1299 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 277 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<WhileStmt> > () = WhileStmt::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1305 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 281 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ForStmt> > () = ForStmt::make(toLoc(yylhs.location), yystack_[5].value.as< std::shared_ptr<Stmt> > (), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1311 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 285 "Parser/MyParser.yy" // lalr1.cc:859
    { }
#line 1317 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 286 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[1].value.as< std::shared_ptr<Expr> > (); }
#line 1323 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 287 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<VariableDecl> > ()); }
#line 1329 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 291 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ForRangeStmt> > () = ForRangeStmt::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Decl> > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1335 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 295 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1341 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 296 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > (), nullptr, nullptr); }
#line 1347 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 297 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = ConstDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > (), nullptr, nullptr); }
#line 1353 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 298 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = DecompositionDecl::make(toLoc(yylhs.location), yystack_[1].value.as< std::vector<std::shared_ptr<BindingDecl>> > ()); }
#line 1359 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 299 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Decl> > () = DecompositionDecl::make(toLoc(yylhs.location), yystack_[1].value.as< std::vector<std::shared_ptr<BindingDecl>> > ()); }
#line 1365 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 303 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VariableDecl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > (), nullptr, nullptr); }
#line 1371 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 304 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VariableDecl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), nullptr, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1377 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 305 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VariableDecl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > (), nullptr); }
#line 1383 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 306 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VariableDecl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<NamedDecl> > (), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1389 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 310 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ConstDecl> > () = ConstDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > (), nullptr, nullptr); }
#line 1395 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 311 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ConstDecl> > () = ConstDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), nullptr, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1401 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 312 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ConstDecl> > () = ConstDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > (), nullptr); }
#line 1407 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 313 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ConstDecl> > () = ConstDecl::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<NamedDecl> > (), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1413 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 317 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<DecompositionDecl> > () = DecompositionDecl::make(toLoc(yylhs.location), yystack_[3].value.as< std::vector<std::shared_ptr<BindingDecl>> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1419 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 318 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<DecompositionDecl> > () = DecompositionDecl::make(toLoc(yylhs.location), yystack_[3].value.as< std::vector<std::shared_ptr<BindingDecl>> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1425 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 322 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<BindingDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<BindingDecl> > ()); }
#line 1431 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 323 "Parser/MyParser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<BindingDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<BindingDecl> > ()); yylhs.value.as< std::vector<std::shared_ptr<BindingDecl>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<BindingDecl>> > ()); }
#line 1437 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 327 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BindingDecl> > () = BindingDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1443 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 331 "Parser/MyParser.yy" // lalr1.cc:859
    { }
#line 1449 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 332 "Parser/MyParser.yy" // lalr1.cc:859
    { }
#line 1455 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 336 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<IntegerLiteral> > (); }
#line 1461 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 337 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<DoubleLiteral> > (); }
#line 1467 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 338 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<BoolLiteral> > (); }
#line 1473 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 339 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<StringLiteral> > (); }
#line 1479 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 356 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<Expr> > (); }
#line 1485 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 357 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<NullLiteral> > (); }
#line 1491 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 358 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = DeclRefExpr::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1497 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 359 "Parser/MyParser.yy" // lalr1.cc:859
    { std::swap(yylhs.value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1503 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 360 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<ArrayLiteral> > (); }
#line 1509 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 361 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<MapLiteral> > (); }
#line 1515 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 365 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullLiteral> > () = NullLiteral::make(toLoc(yylhs.location)); }
#line 1521 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 369 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ArrayLiteral> > () = ArrayLiteral::make(toLoc(yylhs.location), std::vector<std::shared_ptr<Expr>>{}); }
#line 1527 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 370 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ArrayLiteral> > () = ArrayLiteral::make(toLoc(yylhs.location), yystack_[2].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1533 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 374 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MapLiteral> > () = MapLiteral::make(toLoc(yylhs.location), std::vector<std::shared_ptr<MapEntry>>{}); }
#line 1539 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 375 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MapLiteral> > () = MapLiteral::make(toLoc(yylhs.location), yystack_[2].value.as< std::vector<std::shared_ptr<MapEntry>> > ()); }
#line 1545 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 379 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MapEntry> > () = MapEntry::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1551 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 383 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<MapEntry>> > ().push_back(yystack_[0].value.as< std::shared_ptr<MapEntry> > ()); }
#line 1557 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 384 "Parser/MyParser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<MapEntry>> > ().push_back(yystack_[0].value.as< std::shared_ptr<MapEntry> > ()); yylhs.value.as< std::vector<std::shared_ptr<MapEntry>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<MapEntry>> > ()); }
#line 1563 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 388 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MemberExpr> > () = MemberExpr::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1569 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 392 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<SubscriptExpr> > () = SubscriptExpr::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1575 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 396 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CallExpr> > () = CallExpr::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), std::vector<std::shared_ptr<Expr>>{}); }
#line 1581 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 397 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CallExpr> > () = CallExpr::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1587 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 401 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PreInc, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1593 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 402 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PreDec, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1599 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 403 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PostInc, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1605 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 404 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PostDec, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1611 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 405 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::Plus, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1617 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 406 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::Minus, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1623 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 407 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::LogicalNot, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1629 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 411 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Add, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1635 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 412 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Subtract, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1641 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 413 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Multiply, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1647 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 414 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Divide, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1653 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 415 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Mod, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1659 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 416 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Equal, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1665 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 417 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::NotEqual, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1671 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 418 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::LogicalAnd, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1677 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 419 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::LogicalOr, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1683 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 420 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::GreaterThan, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1689 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 421 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::GreaterThanOrEqual, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1695 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 422 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::LessThan, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1701 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 423 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::LessThanOrEqual, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1707 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 427 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<BinaryOperator> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Assign, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1713 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 431 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Expr>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1719 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 432 "Parser/MyParser.yy" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<Expr>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Expr> > ()); yylhs.value.as< std::vector<std::shared_ptr<Expr>> > () = std::move(yystack_[2].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1725 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 436 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<Expr> > (); }
#line 1731 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 437 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<BinaryOperator> > (); }
#line 1737 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 438 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<BinaryOperator> > (); }
#line 1743 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 439 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<UnaryOperator> > (); }
#line 1749 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 440 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<CallExpr> > (); }
#line 1755 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 441 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<MemberExpr> > (); }
#line 1761 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 442 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<SubscriptExpr> > (); }
#line 1767 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 443 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<FunctionExpr> > (); }
#line 1773 "Parser/MyParser.cpp" // lalr1.cc:859
    break;


#line 1777 "Parser/MyParser.cpp" // lalr1.cc:859
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


  const signed char MyParser::yypact_ninf_ = -99;

  const signed char MyParser::yytable_ninf_ = -58;

  const short int
  MyParser::yypact_[] =
  {
     -21,   -35,   -19,    23,   -21,   -99,   -99,   -99,    36,     0,
     -99,   -99,     2,    32,    35,    33,    37,    25,   -99,     5,
     -99,   -99,    30,    55,   -99,    70,   -99,    41,    82,    80,
      80,    95,    84,   290,   290,   290,   290,   290,   307,   -99,
     222,    85,   250,   -11,   -10,   109,   119,   120,   -99,   -99,
     -99,   -99,   -99,   -99,   -99,   -99,   -99,   111,   -99,   -99,
     -99,   -99,   -99,   115,   121,   132,   -99,    81,   -99,   -99,
     -99,   -99,   -99,   -99,   -99,   -99,   -99,   343,     8,     9,
     -99,   -99,   -99,   -99,   -99,   -99,   -99,    80,   -99,   -99,
     -99,   -99,   -99,   -99,   375,   -99,   148,   -99,   154,   155,
     407,   -99,    36,   -99,   439,   146,   146,   307,   307,   193,
     -99,   -99,   -99,   -99,   -99,   -99,   -99,   307,   307,   307,
     307,   307,   307,   307,   307,   307,   307,   307,   307,   307,
     307,   279,   307,   -99,   157,   307,    80,   307,    80,   -99,
     -99,   -99,   307,   176,   307,   180,   307,    32,   -99,   -99,
      34,   -99,    79,   471,   503,   -99,    -7,    -1,   166,   307,
     167,   181,   535,   695,   112,   112,    -3,    -3,    -3,   757,
     726,   788,   788,   284,   284,   284,   284,   -99,    91,   695,
     567,   -99,   695,   211,   695,   212,   -99,   407,   -99,   695,
     -99,   695,   -99,   213,   146,   214,   152,   152,   146,     4,
     146,   -99,   599,   307,   -99,   -99,   -99,   307,   -99,   307,
     307,   307,   -99,   307,   177,   -99,    96,    97,   307,   631,
     695,   695,   695,   695,   152,   -99,   -99,   663,   152,   -99,
     152,   -99,   -99
  };

  const unsigned char
  MyParser::yydefact_[] =
  {
       2,     0,     0,     0,     3,     4,     7,     6,     0,     0,
       1,     5,     0,     0,     0,    10,    18,     0,    16,     0,
       8,    21,     0,     0,    25,     0,    23,     0,     0,     0,
       0,    12,     0,     0,     0,     0,     0,     0,     0,    38,
       0,    14,     0,     0,     0,     0,     0,     0,    82,    78,
      72,    73,    74,    75,   124,    40,    28,     0,    30,    34,
      35,    36,    37,     0,     0,     0,    76,   117,    77,    80,
      81,   122,   123,   121,   120,   119,   118,     0,    57,    61,
      22,    24,    26,    27,    20,    11,    19,     0,    17,    99,
      98,    94,    95,   100,     0,    83,     0,    88,    70,    70,
     115,    15,     0,    42,     0,     0,     0,     0,     0,     0,
      39,    41,    31,    32,    33,    96,    97,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    29,     0,     0,     0,     0,     0,    13,
      79,    85,    71,     0,    71,     0,     0,     0,    43,    69,
       0,    67,     0,     0,     0,    48,     0,     0,    78,     0,
       0,     0,     0,   114,   102,   101,   103,   104,   105,   108,
     109,   106,   107,   113,   111,   112,   110,    92,     0,   115,
       0,    90,    58,    59,    62,    63,    89,     0,    86,   116,
      84,    87,     9,     0,     0,     0,     0,     0,     0,    53,
       0,    54,     0,     0,    50,    49,    93,     0,    91,     0,
       0,     0,    68,     0,    44,    46,     0,     0,     0,     0,
      60,    64,    65,    66,     0,    55,    56,     0,     0,    45,
       0,    51,    47
  };

  const short int
  MyParser::yypgoto_[] =
  {
     -99,   -99,   -99,   216,    51,   -99,   122,   -99,   -99,   189,
     -25,   -99,   -99,   198,   -54,   -12,   -99,   -99,   -99,   -99,
     -99,   -99,   -99,   -99,    -8,    52,   -99,   -98,    40,   129,
     -99,   149,   -99,   -99,   -99,    87,   -99,   -99,   -99,   -99,
     -99,   -99,   -99,   100,   -38
  };

  const short int
  MyParser::yydefgoto_[] =
  {
      -1,     3,     4,     5,     6,    54,    13,   102,    17,    18,
      85,     7,    25,    26,    55,    56,    57,    58,    59,    60,
      61,   159,    62,   160,    63,    64,    65,   150,   151,   143,
      66,    67,    68,    69,    70,    97,    98,    71,    72,    73,
      74,    75,    76,    99,    77
  };

  const short int
  MyParser::yytable_[] =
  {
      94,    20,   100,   111,   104,    86,    27,   135,   152,    33,
      34,   135,   137,     8,   105,   106,     1,    27,   198,    35,
      36,    37,   131,    10,   200,     2,   132,    14,    15,     9,
      38,   134,    19,    39,    40,   136,   -57,    78,    79,   136,
     138,   199,    41,    42,    43,    44,    45,   201,    46,    47,
      16,    31,    48,    49,    50,    51,    52,    53,    32,    19,
     193,    12,   139,    21,    29,    24,    28,   194,    30,   153,
     154,   162,     1,    82,    22,    23,    24,    28,    78,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   179,   180,   115,   116,   182,    80,   184,
     216,   161,   217,    79,   187,   195,   189,     1,   191,    22,
      23,   183,   194,   185,    83,    33,    34,   206,   120,   121,
     122,   202,   225,   226,   207,    35,    36,    37,    84,   194,
     194,    87,    16,   101,   107,   192,    38,   131,    19,   110,
      40,   132,   214,   215,   108,   109,   134,   112,    41,    42,
      43,    44,    45,   113,    46,    47,    33,    34,    48,    49,
      50,    51,    52,    53,   114,   219,    35,    36,    37,   189,
     229,   220,   221,   222,   231,   223,   232,    38,   141,    19,
     227,    40,    89,    90,    91,    92,    93,   142,   144,    41,
      42,    43,    44,    45,   149,    46,    47,    33,    34,    48,
      49,    50,    51,    52,    53,   181,   188,    35,    36,    37,
     190,   -52,   203,   204,   209,   210,   211,   213,    38,   224,
      11,    88,    40,    81,   147,   155,    33,    34,   145,   186,
      41,   178,   156,   157,   212,     0,    35,    36,    37,     0,
      48,   158,    50,    51,    52,    53,     0,    38,     0,     0,
       0,    40,    95,    96,    33,    34,     0,     0,     0,    41,
       0,     0,     0,     0,    35,    36,    37,     0,     0,    48,
      49,    50,    51,    52,    53,    38,     0,     0,     0,    40,
       0,     0,   103,    33,    34,     0,     0,    41,   118,   119,
     120,   121,   122,    35,    36,    37,     0,    48,    49,    50,
      51,    52,    53,     0,    38,   177,     0,     0,    40,   131,
       0,    33,    34,   132,     0,    38,    41,     0,   134,    40,
       0,    35,    36,    37,     0,     0,    48,    49,    50,    51,
      52,    53,    38,     0,     0,     0,    40,    48,    49,    50,
      51,    52,    53,     0,    41,     0,   117,   118,   119,   120,
     121,   122,     0,     0,    48,    49,    50,    51,    52,    53,
     123,   124,   125,   126,   127,   128,   129,   130,   131,     0,
       0,     0,   132,     0,     0,   133,     0,   134,   117,   118,
     119,   120,   121,   122,     0,     0,     0,     0,     0,     0,
       0,     0,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   140,     0,     0,   132,     0,     0,     0,     0,   134,
     117,   118,   119,   120,   121,   122,     0,     0,     0,     0,
       0,     0,     0,     0,   123,   124,   125,   126,   127,   128,
     129,   130,   131,     0,     0,     0,   132,     0,   146,     0,
       0,   134,   117,   118,   119,   120,   121,   122,     0,     0,
       0,     0,     0,     0,     0,     0,   123,   124,   125,   126,
     127,   128,   129,   130,   131,     0,     0,     0,   132,     0,
       0,   148,     0,   134,   117,   118,   119,   120,   121,   122,
       0,     0,     0,     0,     0,     0,     0,     0,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   196,     0,     0,
     132,     0,     0,     0,     0,   134,   117,   118,   119,   120,
     121,   122,     0,     0,     0,     0,     0,     0,     0,     0,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   197,
       0,     0,   132,     0,     0,     0,     0,   134,   117,   118,
     119,   120,   121,   122,     0,     0,     0,     0,     0,     0,
       0,     0,   123,   124,   125,   126,   127,   128,   129,   130,
     131,     0,     0,     0,   132,     0,     0,   205,     0,   134,
     117,   118,   119,   120,   121,   122,     0,     0,     0,     0,
       0,     0,     0,     0,   123,   124,   125,   126,   127,   128,
     129,   130,   131,     0,     0,     0,   132,   208,     0,     0,
       0,   134,   117,   118,   119,   120,   121,   122,     0,     0,
       0,     0,     0,     0,     0,     0,   123,   124,   125,   126,
     127,   128,   129,   130,   131,     0,     0,     0,   132,     0,
       0,   218,     0,   134,   117,   118,   119,   120,   121,   122,
       0,     0,     0,     0,     0,     0,     0,     0,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   228,     0,     0,
     132,     0,     0,     0,     0,   134,   117,   118,   119,   120,
     121,   122,     0,     0,     0,     0,     0,     0,     0,     0,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   230,
       0,     0,   132,     0,     0,     0,     0,   134,   117,   118,
     119,   120,   121,   122,     0,     0,     0,     0,     0,     0,
       0,     0,   123,   124,   125,   126,   127,   128,   129,   130,
     131,     0,     0,     0,   132,     0,     0,     0,     0,   134,
     118,   119,   120,   121,   122,     0,     0,     0,     0,     0,
       0,     0,     0,   123,     0,   125,   126,   127,   128,   129,
     130,   131,     0,     0,     0,   132,     0,     0,     0,     0,
     134,   118,   119,   120,   121,   122,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   125,   126,   127,   128,
     129,   130,   131,     0,     0,     0,   132,     0,     0,     0,
       0,   134,   118,   119,   120,   121,   122,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   127,
     128,   129,   130,   131,     0,     0,     0,   132,     0,     0,
       0,     0,   134
  };

  const short int
  MyParser::yycheck_[] =
  {
      38,    13,    40,    57,    42,    30,    14,     3,   106,     4,
       5,     3,     3,    48,    25,    25,    37,    25,    25,    14,
      15,    16,    25,     0,    25,    46,    29,    27,    26,    48,
      25,    34,    27,    28,    29,    31,    32,    48,    48,    31,
      31,    48,    37,    38,    39,    40,    41,    48,    43,    44,
      48,    26,    47,    48,    49,    50,    51,    52,    33,    27,
      26,    25,    87,    28,    31,    14,    14,    33,    31,   107,
     108,   109,    37,    32,    39,    40,    25,    25,    48,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,    14,    15,   135,    28,   137,
     198,   109,   200,    48,   142,    26,   144,    37,   146,    39,
      40,   136,    33,   138,    32,     4,     5,    26,     6,     7,
       8,   159,    26,    26,    33,    14,    15,    16,    48,    33,
      33,    36,    48,    48,    25,   147,    25,    25,    27,    28,
      29,    29,   196,   197,    25,    25,    34,    32,    37,    38,
      39,    40,    41,    32,    43,    44,     4,     5,    47,    48,
      49,    50,    51,    52,    32,   203,    14,    15,    16,   207,
     224,   209,   210,   211,   228,   213,   230,    25,    30,    27,
     218,    29,    33,    34,    35,    36,    37,    33,    33,    37,
      38,    39,    40,    41,    48,    43,    44,     4,     5,    47,
      48,    49,    50,    51,    52,    48,    30,    14,    15,    16,
      30,    45,    45,    32,     3,     3,     3,     3,    25,    42,
       4,    32,    29,    25,   102,    32,     4,     5,    99,   142,
      37,   131,    39,    40,   194,    -1,    14,    15,    16,    -1,
      47,    48,    49,    50,    51,    52,    -1,    25,    -1,    -1,
      -1,    29,    30,    31,     4,     5,    -1,    -1,    -1,    37,
      -1,    -1,    -1,    -1,    14,    15,    16,    -1,    -1,    47,
      48,    49,    50,    51,    52,    25,    -1,    -1,    -1,    29,
      -1,    -1,    32,     4,     5,    -1,    -1,    37,     4,     5,
       6,     7,     8,    14,    15,    16,    -1,    47,    48,    49,
      50,    51,    52,    -1,    25,    26,    -1,    -1,    29,    25,
      -1,     4,     5,    29,    -1,    25,    37,    -1,    34,    29,
      -1,    14,    15,    16,    -1,    -1,    47,    48,    49,    50,
      51,    52,    25,    -1,    -1,    -1,    29,    47,    48,    49,
      50,    51,    52,    -1,    37,    -1,     3,     4,     5,     6,
       7,     8,    -1,    -1,    47,    48,    49,    50,    51,    52,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    29,    -1,    -1,    32,    -1,    34,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    -1,    29,    -1,    -1,    -1,    -1,    34,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    29,    -1,    31,    -1,
      -1,    34,     3,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    29,    -1,
      -1,    32,    -1,    34,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    -1,    -1,
      29,    -1,    -1,    -1,    -1,    34,     3,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      -1,    -1,    29,    -1,    -1,    -1,    -1,    34,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    29,    -1,    -1,    32,    -1,    34,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    29,    30,    -1,    -1,
      -1,    34,     3,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    29,    -1,
      -1,    32,    -1,    34,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    -1,    -1,
      29,    -1,    -1,    -1,    -1,    34,     3,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      -1,    -1,    29,    -1,    -1,    -1,    -1,    34,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,    34,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    17,    -1,    19,    20,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,
      34,     4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    19,    20,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    29,    -1,    -1,    -1,
      -1,    34,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    29,    -1,    -1,
      -1,    -1,    34
  };

  const unsigned char
  MyParser::yystos_[] =
  {
       0,    37,    46,    57,    58,    59,    60,    67,    48,    48,
       0,    59,    25,    62,    27,    26,    48,    64,    65,    27,
      71,    28,    39,    40,    60,    68,    69,    80,    81,    31,
      31,    26,    33,     4,     5,    14,    15,    16,    25,    28,
      29,    37,    38,    39,    40,    41,    43,    44,    47,    48,
      49,    50,    51,    52,    61,    70,    71,    72,    73,    74,
      75,    76,    78,    80,    81,    82,    86,    87,    88,    89,
      90,    93,    94,    95,    96,    97,    98,   100,    48,    48,
      28,    69,    32,    32,    48,    66,    66,    36,    65,    87,
      87,    87,    87,    87,   100,    30,    31,    91,    92,    99,
     100,    48,    63,    32,   100,    25,    25,    25,    25,    25,
      28,    70,    32,    32,    32,    14,    15,     3,     4,     5,
       6,     7,     8,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    29,    32,    34,     3,    31,     3,    31,    66,
      26,    30,    33,    85,    33,    85,    31,    62,    32,    48,
      83,    84,    83,   100,   100,    32,    39,    40,    48,    77,
      79,    80,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,    26,    99,   100,
     100,    48,   100,    66,   100,    66,    91,   100,    30,   100,
      30,   100,    71,    26,    33,    26,    26,    26,    25,    48,
      25,    48,   100,    45,    32,    32,    26,    33,    30,     3,
       3,     3,    84,     3,    70,    70,    83,    83,    32,   100,
     100,   100,   100,   100,    42,    26,    26,   100,    26,    70,
      26,    70,    70
  };

  const unsigned char
  MyParser::yyr1_[] =
  {
       0,    56,    57,    57,    58,    58,    59,    59,    60,    61,
      62,    62,    62,    62,    63,    63,    64,    64,    65,    65,
      66,    67,    67,    68,    68,    69,    69,    69,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    71,    71,
      72,    72,    73,    73,    74,    74,    75,    76,    77,    77,
      77,    78,    79,    79,    79,    79,    79,    80,    80,    80,
      80,    81,    81,    81,    81,    82,    82,    83,    83,    84,
      85,    85,    86,    86,    86,    86,    87,    87,    87,    87,
      87,    87,    88,    89,    89,    90,    90,    91,    92,    92,
      93,    94,    95,    95,    96,    96,    96,    96,    96,    96,
      96,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    98,    99,    99,   100,   100,   100,
     100,   100,   100,   100,   100
  };

  const unsigned char
  MyParser::yyr2_[] =
  {
       0,     2,     0,     1,     1,     2,     1,     1,     4,     4,
       2,     4,     3,     5,     0,     1,     1,     3,     1,     3,
       1,     4,     5,     1,     2,     1,     2,     2,     1,     2,
       1,     2,     2,     2,     1,     1,     1,     1,     2,     3,
       1,     2,     2,     3,     5,     7,     5,     8,     1,     2,
       2,     7,     1,     2,     2,     4,     4,     2,     4,     4,
       6,     2,     4,     4,     6,     6,     6,     1,     3,     1,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     2,     4,     3,     4,     3,     1,     3,
       3,     4,     3,     4,     2,     2,     2,     2,     2,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     3,     1,     1,     1,
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
  "\"?\"", "\"->\"", "\"func\"", "\"return\"", "\"let\"", "\"const\"",
  "\"if\"", "\"else\"", "\"while\"", "\"for\"", "\"in\"", "\"class\"",
  "\"null\"", "\"identifier\"", "\"integer_literal\"",
  "\"double_literal\"", "\"bool_literal\"", "\"string_literal\"",
  "\"then\"", "\"unary_plus\"", "\"unary_minus\"", "$accept",
  "translation_unit", "translation_unit_declarations",
  "translation_unit_declaration", "function_definition",
  "function_expression", "call_signature", "binding_identifier",
  "parameter_variables", "parameter_variable", "type_specifier",
  "class_declaration", "member_declaration_list", "member_declaration",
  "statement", "compound_statement", "statement_list", "return_statement",
  "if_statement", "while_statement", "for_statement", "for_init_statement",
  "for_range_statement", "for_range_init", "variable_definition",
  "const_definition", "decomposition_definition", "binding_declarations",
  "binding_declaration", "comma_opt", "literal", "primary_expression",
  "null_literal", "array_literal", "map_literal", "map_entry",
  "map_entry_list", "member_expression", "subscript_expression",
  "call_expression", "unary_expression", "binary_expression",
  "assignment_expression", "expression_list", "expression", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  MyParser::yyrline_[] =
  {
       0,   177,   177,   178,   182,   183,   187,   188,   192,   196,
     200,   201,   202,   203,   207,   208,   212,   213,   217,   218,
     222,   226,   227,   231,   232,   236,   237,   238,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   255,   256,
     260,   261,   265,   266,   272,   273,   277,   281,   285,   286,
     287,   291,   295,   296,   297,   298,   299,   303,   304,   305,
     306,   310,   311,   312,   313,   317,   318,   322,   323,   327,
     331,   332,   336,   337,   338,   339,   356,   357,   358,   359,
     360,   361,   365,   369,   370,   374,   375,   379,   383,   384,
     388,   392,   396,   397,   401,   402,   403,   404,   405,   406,
     407,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     420,   421,   422,   423,   427,   431,   432,   436,   437,   438,
     439,   440,   441,   442,   443
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
#line 2439 "Parser/MyParser.cpp" // lalr1.cc:1167
#line 446 "Parser/MyParser.yy" // lalr1.cc:1168


void yy::MyParser::error(const location_type& l, const std::string& m)
{
    driver.error(toLoc(l), m);
}
