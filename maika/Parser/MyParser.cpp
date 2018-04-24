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
#line 49 "Parser/MyParser.yy" // lalr1.cc:413

#include "AST/ASTContext.h"
#include "Basic/Location.h"
#include "Driver/Driver.h"
#include <string>

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

#line 89 "Parser/MyParser.cpp" // lalr1.cc:413


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
#line 175 "Parser/MyParser.cpp" // lalr1.cc:479

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

      case 77: // literal
      case 78: // primary_expression
      case 84: // expression
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

      case 73: // initializer_list_expression
        value.move< std::shared_ptr<InitListExpr> > (that.value);
        break;

      case 46: // "integer_literal"
        value.move< std::shared_ptr<IntegerLiteral> > (that.value);
        break;

      case 76: // map_entry
        value.move< std::shared_ptr<MapEntry> > (that.value);
        break;

      case 74: // map_entry_list_expression
        value.move< std::shared_ptr<MapEntryListExpr> > (that.value);
        break;

      case 81: // member_expression
        value.move< std::shared_ptr<MemberExpr> > (that.value);
        break;

      case 45: // "identifier"
      case 59: // binding_identifier
      case 62: // type_specifier
        value.move< std::shared_ptr<NamedDecl> > (that.value);
        break;

      case 79: // null_literal
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

      case 80: // unary_expression
        value.move< std::shared_ptr<UnaryOperator> > (that.value);
        break;

      case 71: // variable_definition
        value.move< std::shared_ptr<VariableDecl> > (that.value);
        break;

      case 68: // while_statement
        value.move< std::shared_ptr<WhileStmt> > (that.value);
        break;

      case 83: // expression_list
        value.move< std::vector<std::shared_ptr<Expr>> > (that.value);
        break;

      case 55: // function_definitions
        value.move< std::vector<std::shared_ptr<FunctionDecl>> > (that.value);
        break;

      case 75: // map_entry_list
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

      case 77: // literal
      case 78: // primary_expression
      case 84: // expression
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

      case 73: // initializer_list_expression
        value.copy< std::shared_ptr<InitListExpr> > (that.value);
        break;

      case 46: // "integer_literal"
        value.copy< std::shared_ptr<IntegerLiteral> > (that.value);
        break;

      case 76: // map_entry
        value.copy< std::shared_ptr<MapEntry> > (that.value);
        break;

      case 74: // map_entry_list_expression
        value.copy< std::shared_ptr<MapEntryListExpr> > (that.value);
        break;

      case 81: // member_expression
        value.copy< std::shared_ptr<MemberExpr> > (that.value);
        break;

      case 45: // "identifier"
      case 59: // binding_identifier
      case 62: // type_specifier
        value.copy< std::shared_ptr<NamedDecl> > (that.value);
        break;

      case 79: // null_literal
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

      case 80: // unary_expression
        value.copy< std::shared_ptr<UnaryOperator> > (that.value);
        break;

      case 71: // variable_definition
        value.copy< std::shared_ptr<VariableDecl> > (that.value);
        break;

      case 68: // while_statement
        value.copy< std::shared_ptr<WhileStmt> > (that.value);
        break;

      case 83: // expression_list
        value.copy< std::vector<std::shared_ptr<Expr>> > (that.value);
        break;

      case 55: // function_definitions
        value.copy< std::vector<std::shared_ptr<FunctionDecl>> > (that.value);
        break;

      case 75: // map_entry_list
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
    #line 40 "Parser/MyParser.yy" // lalr1.cc:741
{
    // Initialize the initial location.
    yyla.location.begin.filename = yyla.location.end.filename = &driver.file;
}

#line 707 "Parser/MyParser.cpp" // lalr1.cc:741

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

      case 77: // literal
      case 78: // primary_expression
      case 84: // expression
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

      case 73: // initializer_list_expression
        yylhs.value.build< std::shared_ptr<InitListExpr> > ();
        break;

      case 46: // "integer_literal"
        yylhs.value.build< std::shared_ptr<IntegerLiteral> > ();
        break;

      case 76: // map_entry
        yylhs.value.build< std::shared_ptr<MapEntry> > ();
        break;

      case 74: // map_entry_list_expression
        yylhs.value.build< std::shared_ptr<MapEntryListExpr> > ();
        break;

      case 81: // member_expression
        yylhs.value.build< std::shared_ptr<MemberExpr> > ();
        break;

      case 45: // "identifier"
      case 59: // binding_identifier
      case 62: // type_specifier
        yylhs.value.build< std::shared_ptr<NamedDecl> > ();
        break;

      case 79: // null_literal
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

      case 80: // unary_expression
        yylhs.value.build< std::shared_ptr<UnaryOperator> > ();
        break;

      case 71: // variable_definition
        yylhs.value.build< std::shared_ptr<VariableDecl> > ();
        break;

      case 68: // while_statement
        yylhs.value.build< std::shared_ptr<WhileStmt> > ();
        break;

      case 83: // expression_list
        yylhs.value.build< std::vector<std::shared_ptr<Expr>> > ();
        break;

      case 55: // function_definitions
        yylhs.value.build< std::vector<std::shared_ptr<FunctionDecl>> > ();
        break;

      case 75: // map_entry_list
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
#line 173 "Parser/MyParser.yy" // lalr1.cc:859
    { driver.ast.translationUnit = TranslationUnitDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::vector<std::shared_ptr<FunctionDecl>> > ()); }
#line 946 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 177 "Parser/MyParser.yy" // lalr1.cc:859
    { }
#line 952 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 178 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<FunctionDecl>> > () = appendVector(yystack_[1].value.as< std::shared_ptr<FunctionDecl> > (), yystack_[0].value.as< std::vector<std::shared_ptr<FunctionDecl>> > ()); }
#line 958 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 182 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<FunctionDecl> > () = FunctionDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), std::get<0>(yystack_[1].value.as< CallSignature > ()), std::get<1>(yystack_[1].value.as< CallSignature > ()), yystack_[0].value.as< std::shared_ptr<CompoundStmt> > ()); }
#line 964 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 186 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<FunctionExpr> > () = FunctionExpr::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), std::get<0>(yystack_[1].value.as< CallSignature > ()), std::get<1>(yystack_[1].value.as< CallSignature > ()), yystack_[0].value.as< std::shared_ptr<CompoundStmt> > ()); }
#line 970 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 190 "Parser/MyParser.yy" // lalr1.cc:859
    { std::get<0>(yylhs.value.as< CallSignature > ()) = yystack_[1].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > (); std::get<1>(yylhs.value.as< CallSignature > ()) = nullptr; }
#line 976 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 191 "Parser/MyParser.yy" // lalr1.cc:859
    { std::get<0>(yylhs.value.as< CallSignature > ()) = yystack_[3].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > (); std::get<1>(yylhs.value.as< CallSignature > ()) = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 982 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 195 "Parser/MyParser.yy" // lalr1.cc:859
    { }
#line 988 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 196 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NamedDecl> > () = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 994 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 200 "Parser/MyParser.yy" // lalr1.cc:859
    { }
#line 1000 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 201 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<ParmVarDecl>> > ().push_back(yystack_[0].value.as< std::shared_ptr<ParmVarDecl> > ()); }
#line 1006 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 202 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<ParmVarDecl>> > () = appendVector(yystack_[2].value.as< std::shared_ptr<ParmVarDecl> > (), yystack_[0].value.as< std::vector<std::shared_ptr<ParmVarDecl>> > ()); }
#line 1012 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 206 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ParmVarDecl> > () = ParmVarDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1018 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 207 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ParmVarDecl> > () = ParmVarDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1024 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 211 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NamedDecl> > () = yystack_[0].value.as< std::shared_ptr<NamedDecl> > (); }
#line 1030 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 215 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[1].value.as< std::shared_ptr<Expr> > (); }
#line 1036 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 216 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ReturnStmt> > (); }
#line 1042 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 217 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<VariableDecl> > ()); }
#line 1048 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 218 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<ConstDecl> > ()); }
#line 1054 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 219 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<IfStmt> > (); }
#line 1060 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 220 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<WhileStmt> > (); }
#line 1066 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 221 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<ForStmt> > (); }
#line 1072 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 222 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[0].value.as< std::shared_ptr<CompoundStmt> > (); }
#line 1078 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 226 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CompoundStmt> > () = CompoundStmt::make(toLoc(yylhs.location), std::vector<std::shared_ptr<Stmt>>{}); }
#line 1084 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 227 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CompoundStmt> > () = CompoundStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::vector<std::shared_ptr<Stmt>> > ()); }
#line 1090 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 231 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Stmt>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1096 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 232 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Stmt>> > () = appendVector(yystack_[1].value.as< std::shared_ptr<Stmt> > (), yystack_[0].value.as< std::vector<std::shared_ptr<Stmt>> > ()); }
#line 1102 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 236 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ReturnStmt> > () = ReturnStmt::make(toLoc(yylhs.location)); }
#line 1108 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 237 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ReturnStmt> > () = ReturnStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1114 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 243 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IfStmt> > () = IfStmt::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1120 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 244 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IfStmt> > () = IfStmt::make(toLoc(yylhs.location), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[2].value.as< std::shared_ptr<Stmt> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1126 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 248 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<WhileStmt> > () = WhileStmt::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1132 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 252 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ForStmt> > () = ForStmt::make(toLoc(yylhs.location), yystack_[5].value.as< std::shared_ptr<Stmt> > (), yystack_[4].value.as< std::shared_ptr<Expr> > (), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Stmt> > ()); }
#line 1138 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 256 "Parser/MyParser.yy" // lalr1.cc:859
    { }
#line 1144 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 257 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = yystack_[1].value.as< std::shared_ptr<Expr> > (); }
#line 1150 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 258 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Stmt> > () = DeclStmt::make(toLoc(yylhs.location), yystack_[1].value.as< std::shared_ptr<VariableDecl> > ()); }
#line 1156 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 262 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VariableDecl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1162 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 263 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<VariableDecl> > () = VariableDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1168 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 267 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ConstDecl> > () = ConstDecl::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1174 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 268 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ConstDecl> > () = ConstDecl::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<NamedDecl> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1180 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 272 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<InitListExpr> > () = InitListExpr::make(toLoc(yylhs.location), yystack_[1].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1186 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 276 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MapEntryListExpr> > () = MapEntryListExpr::make(toLoc(yylhs.location), yystack_[1].value.as< std::vector<std::shared_ptr<MapEntry>> > ()); }
#line 1192 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 280 "Parser/MyParser.yy" // lalr1.cc:859
    { }
#line 1198 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 281 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<MapEntry>> > ().push_back(yystack_[0].value.as< std::shared_ptr<MapEntry> > ()); }
#line 1204 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 282 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<MapEntry>> > () = appendVector(yystack_[2].value.as< std::shared_ptr<MapEntry> > (), yystack_[0].value.as< std::vector<std::shared_ptr<MapEntry>> > ()); }
#line 1210 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 286 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MapEntry> > () = MapEntry::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1216 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 290 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<IntegerLiteral> > (); }
#line 1222 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 291 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<DoubleLiteral> > (); }
#line 1228 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 292 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<BoolLiteral> > (); }
#line 1234 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 293 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<StringLiteral> > (); }
#line 1240 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 309 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<Expr> > (); }
#line 1246 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 310 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<NullLiteral> > (); }
#line 1252 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 311 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = DeclRefExpr::make(toLoc(yylhs.location), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1258 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 312 "Parser/MyParser.yy" // lalr1.cc:859
    { std::swap(yylhs.value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1264 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 316 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<NullLiteral> > () = NullLiteral::make(toLoc(yylhs.location)); }
#line 1270 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 320 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PreInc, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1276 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 321 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PreDec, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1282 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 322 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PostInc, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1288 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 323 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::PostDec, yystack_[1].value.as< std::shared_ptr<Expr> > ()); }
#line 1294 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 324 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::Plus, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1300 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 325 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::Minus, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1306 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 326 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<UnaryOperator> > () = UnaryOperator::make(toLoc(yylhs.location), UnaryOperatorKind::LogicalNot, yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1312 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 330 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<MemberExpr> > () = MemberExpr::make(toLoc(yylhs.location), yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<NamedDecl> > ()); }
#line 1318 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 334 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<CallExpr> > () = CallExpr::make(toLoc(yylhs.location), yystack_[3].value.as< std::shared_ptr<Expr> > (), yystack_[1].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1324 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 338 "Parser/MyParser.yy" // lalr1.cc:859
    { }
#line 1330 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 339 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Expr>> > ().push_back(yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1336 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 340 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<Expr>> > () = appendVector(yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::vector<std::shared_ptr<Expr>> > ()); }
#line 1342 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 344 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<Expr> > (); }
#line 1348 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 345 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Add, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1354 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 346 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Subtract, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1360 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 347 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Multiply, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1366 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 348 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Divide, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1372 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 349 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Mod, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1378 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 350 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Assign, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1384 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 351 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::Equal, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1390 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 352 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::NotEqual, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1396 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 353 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::LogicalAnd, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1402 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 354 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::LogicalOr, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1408 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 355 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::GreaterThan, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1414 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 356 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::GreaterThanOrEqual, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1420 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 357 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::LessThan, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1426 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 358 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = BinaryOperator::make(toLoc(yylhs.location), BinaryOperatorKind::LessThanOrEqual, yystack_[2].value.as< std::shared_ptr<Expr> > (), yystack_[0].value.as< std::shared_ptr<Expr> > ()); }
#line 1432 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 359 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<UnaryOperator> > (); }
#line 1438 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 360 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<CallExpr> > (); }
#line 1444 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 361 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<MemberExpr> > (); }
#line 1450 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 362 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<FunctionExpr> > (); }
#line 1456 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 363 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<InitListExpr> > (); }
#line 1462 "Parser/MyParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 364 "Parser/MyParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<Expr> > () = yystack_[0].value.as< std::shared_ptr<MapEntryListExpr> > (); }
#line 1468 "Parser/MyParser.cpp" // lalr1.cc:859
    break;


#line 1472 "Parser/MyParser.cpp" // lalr1.cc:859
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


  const signed char MyParser::yypact_ninf_ = -112;

  const signed char MyParser::yytable_ninf_ = -1;

  const short int
  MyParser::yypact_[] =
  {
     -33,   -30,    19,  -112,   -33,     9,  -112,  -112,    -1,    21,
      32,    24,    20,    96,  -112,     7,    34,    -1,    70,    70,
      70,    70,    70,   230,  -112,   230,    42,   192,    43,    46,
      67,    68,    71,  -112,  -112,  -112,  -112,  -112,  -112,   230,
    -112,   144,  -112,    69,  -112,  -112,  -112,  -112,    74,    75,
    -112,  -112,  -112,    22,  -112,  -112,  -112,  -112,   265,  -112,
    -112,     7,  -112,  -112,  -112,  -112,  -112,  -112,   288,    78,
     312,  -112,     9,  -112,   335,   106,   110,   230,   230,    13,
      76,    87,   358,  -112,  -112,  -112,  -112,  -112,  -112,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,  -112,    81,  -112,  -112,  -112,   230,
      21,  -112,   230,   230,   390,   414,  -112,   230,    95,   438,
    -112,   230,   230,   508,    97,    97,     5,     5,     5,     1,
     530,   208,   208,     6,     6,     6,     6,   103,  -112,  -112,
    -112,   508,   508,   144,   144,   461,  -112,  -112,  -112,   508,
    -112,   105,  -112,   230,   144,   484,  -112,   144,  -112
  };

  const unsigned char
  MyParser::yydefact_[] =
  {
       3,     0,     0,     2,     3,     0,     1,     4,    11,     0,
      14,     0,    12,     0,     5,     0,     7,    11,     0,     0,
       0,     0,     0,     0,    25,    66,     9,     0,     0,     0,
       0,     0,     0,    56,    54,    48,    49,    50,    51,    44,
      87,    27,    24,     0,    18,    21,    22,    23,     0,     0,
      88,    89,    52,    69,    53,    84,    86,    85,     0,    16,
      15,     0,    13,    62,    61,    57,    58,    63,     0,     0,
      67,    10,     0,    29,     0,    38,    40,     0,     0,     0,
       0,    45,     0,    28,    26,    19,    20,    59,    60,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    66,    17,     0,     8,    55,    42,    66,
       0,    30,     0,     0,     0,     0,    35,     0,     0,     0,
      43,    44,     0,    75,    71,    70,    72,    73,    74,    78,
      79,    76,    77,    83,    81,    82,    80,     0,    64,    68,
       6,    39,    41,     0,     0,     0,    37,    36,    46,    47,
      65,    31,    33,     0,     0,     0,    32,     0,    34
  };

  const short int
  MyParser::yypgoto_[] =
  {
    -112,  -112,   133,  -112,  -112,    79,  -112,   135,  -112,    89,
    -111,    -8,   112,  -112,  -112,  -112,  -112,  -112,    77,  -112,
    -112,  -112,    33,  -112,  -112,    63,  -112,  -112,  -112,  -112,
     -62,   -23
  };

  const signed char
  MyParser::yydefgoto_[] =
  {
      -1,     2,     3,     4,    40,     9,    72,    11,    12,    60,
      41,    42,    43,    44,    45,    46,    47,   117,    48,    49,
      50,    51,    80,    81,    52,    53,    54,    55,    56,    57,
      69,    58
  };

  const unsigned char
  MyParser::yytable_[] =
  {
      68,    14,    70,     1,    74,    90,    91,    92,    93,    94,
      90,    91,    92,    93,    94,     5,    82,    18,    19,     6,
      97,    98,    99,   100,   101,   102,   103,    20,    21,    22,
     103,   103,   151,   152,     8,   105,    87,    88,    23,   105,
     105,   137,    25,   156,    10,   116,   158,   139,    13,    26,
      16,    28,    59,    17,   114,   115,   119,    33,    34,    35,
      36,    37,    38,    15,    39,    61,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
      70,    63,    64,    65,    66,    67,    70,    71,    75,   141,
     142,    76,    77,    78,   145,    23,    79,    84,    82,   149,
      18,    19,   140,    92,    93,    94,    85,    86,   108,   112,
      20,    21,    22,   113,    33,    34,    35,    36,    37,    38,
     121,    23,   103,    13,    24,    25,   138,   146,   120,   150,
     155,   105,    26,    27,    28,    29,    30,     7,    31,    32,
      33,    34,    35,    36,    37,    38,   154,    39,    18,    19,
     106,   110,    62,    83,   148,     0,   118,     0,    20,    21,
      22,     0,     0,     0,     0,     0,     0,     0,     0,    23,
       0,    13,     0,    25,     0,     0,     0,     0,     0,     0,
      26,    27,    28,    29,    30,     0,    31,    32,    33,    34,
      35,    36,    37,    38,     0,    39,    18,    19,     0,     0,
       0,     0,     0,     0,     0,     0,    20,    21,    22,     0,
       0,     0,    90,    91,    92,    93,    94,    23,     0,     0,
       0,    25,     0,     0,    73,     0,     0,     0,    26,    99,
     100,   101,   102,   103,    18,    19,    33,    34,    35,    36,
      37,    38,   105,    39,    20,    21,    22,     0,     0,     0,
       0,     0,     0,     0,     0,    23,     0,     0,     0,    25,
       0,     0,     0,     0,     0,     0,    26,     0,    89,    90,
      91,    92,    93,    94,    33,    34,    35,    36,    37,    38,
       0,    39,    95,    96,    97,    98,    99,   100,   101,   102,
     103,    89,    90,    91,    92,    93,    94,   104,     0,   105,
       0,     0,     0,     0,     0,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   107,    89,    90,    91,    92,    93,
      94,     0,   105,     0,     0,     0,     0,     0,     0,    95,
      96,    97,    98,    99,   100,   101,   102,   103,    89,    90,
      91,    92,    93,    94,     0,   109,   105,     0,     0,     0,
       0,     0,    95,    96,    97,    98,    99,   100,   101,   102,
     103,    89,    90,    91,    92,    93,    94,   111,     0,   105,
       0,     0,     0,     0,     0,    95,    96,    97,    98,    99,
     100,   101,   102,   103,     0,     0,     0,     0,     0,   122,
       0,     0,   105,    89,    90,    91,    92,    93,    94,     0,
       0,     0,     0,     0,     0,     0,     0,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   143,    89,    90,    91,
      92,    93,    94,     0,   105,     0,     0,     0,     0,     0,
       0,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     144,    89,    90,    91,    92,    93,    94,     0,   105,     0,
       0,     0,     0,     0,     0,    95,    96,    97,    98,    99,
     100,   101,   102,   103,    89,    90,    91,    92,    93,    94,
     147,     0,   105,     0,     0,     0,     0,     0,    95,    96,
      97,    98,    99,   100,   101,   102,   103,    89,    90,    91,
      92,    93,    94,   153,     0,   105,     0,     0,     0,     0,
       0,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     157,    89,    90,    91,    92,    93,    94,     0,   105,     0,
       0,     0,     0,     0,     0,    95,    96,    97,    98,    99,
     100,   101,   102,   103,    90,    91,    92,    93,    94,     0,
       0,     0,   105,     0,     0,     0,     0,    95,     0,    97,
      98,    99,   100,   101,   102,   103,     0,     0,     0,     0,
       0,     0,     0,     0,   105
  };

  const short int
  MyParser::yycheck_[] =
  {
      23,     9,    25,    36,    27,     4,     5,     6,     7,     8,
       4,     5,     6,     7,     8,    45,    39,     4,     5,     0,
      19,    20,    21,    22,    23,    24,    25,    14,    15,    16,
      25,    25,   143,   144,    25,    34,    14,    15,    25,    34,
      34,   103,    29,   154,    45,    32,   157,   109,    27,    36,
      26,    38,    45,    33,    77,    78,    79,    44,    45,    46,
      47,    48,    49,    31,    51,    31,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,    18,    19,    20,    21,    22,   109,    45,    45,   112,
     113,    45,    25,    25,   117,    25,    25,    28,   121,   122,
       4,     5,   110,     6,     7,     8,    32,    32,    30,     3,
      14,    15,    16,     3,    44,    45,    46,    47,    48,    49,
      33,    25,    25,    27,    28,    29,    45,    32,    52,    26,
     153,    34,    36,    37,    38,    39,    40,     4,    42,    43,
      44,    45,    46,    47,    48,    49,    41,    51,     4,     5,
      61,    72,    17,    41,   121,    -1,    79,    -1,    14,    15,
      16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,
      -1,    27,    -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    37,    38,    39,    40,    -1,    42,    43,    44,    45,
      46,    47,    48,    49,    -1,    51,     4,     5,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    14,    15,    16,    -1,
      -1,    -1,     4,     5,     6,     7,     8,    25,    -1,    -1,
      -1,    29,    -1,    -1,    32,    -1,    -1,    -1,    36,    21,
      22,    23,    24,    25,     4,     5,    44,    45,    46,    47,
      48,    49,    34,    51,    14,    15,    16,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,     3,     4,
       5,     6,     7,     8,    44,    45,    46,    47,    48,    49,
      -1,    51,    17,    18,    19,    20,    21,    22,    23,    24,
      25,     3,     4,     5,     6,     7,     8,    32,    -1,    34,
      -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,     3,     4,     5,     6,     7,
       8,    -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,    17,
      18,    19,    20,    21,    22,    23,    24,    25,     3,     4,
       5,     6,     7,     8,    -1,    33,    34,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,     3,     4,     5,     6,     7,     8,    32,    -1,    34,
      -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    31,
      -1,    -1,    34,     3,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,     3,     4,     5,
       6,     7,     8,    -1,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,     3,     4,     5,     6,     7,     8,    -1,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,
      22,    23,    24,    25,     3,     4,     5,     6,     7,     8,
      32,    -1,    34,    -1,    -1,    -1,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    25,     3,     4,     5,
       6,     7,     8,    32,    -1,    34,    -1,    -1,    -1,    -1,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,     3,     4,     5,     6,     7,     8,    -1,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,
      22,    23,    24,    25,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    34,    -1,    -1,    -1,    -1,    17,    -1,    19,
      20,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    34
  };

  const unsigned char
  MyParser::yystos_[] =
  {
       0,    36,    54,    55,    56,    45,     0,    55,    25,    58,
      45,    60,    61,    27,    64,    31,    26,    33,     4,     5,
      14,    15,    16,    25,    28,    29,    36,    37,    38,    39,
      40,    42,    43,    44,    45,    46,    47,    48,    49,    51,
      57,    63,    64,    65,    66,    67,    68,    69,    71,    72,
      73,    74,    77,    78,    79,    80,    81,    82,    84,    45,
      62,    31,    60,    78,    78,    78,    78,    78,    84,    83,
      84,    45,    59,    32,    84,    45,    45,    25,    25,    25,
      75,    76,    84,    65,    28,    32,    32,    14,    15,     3,
       4,     5,     6,     7,     8,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    32,    34,    62,    26,    30,    33,
      58,    32,     3,     3,    84,    84,    32,    70,    71,    84,
      52,    33,    31,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    83,    45,    83,
      64,    84,    84,    26,    26,    84,    32,    32,    75,    84,
      26,    63,    63,    32,    41,    84,    63,    26,    63
  };

  const unsigned char
  MyParser::yyr1_[] =
  {
       0,    53,    54,    55,    55,    56,    57,    58,    58,    59,
      59,    60,    60,    60,    61,    61,    62,    63,    63,    63,
      63,    63,    63,    63,    63,    64,    64,    65,    65,    66,
      66,    67,    67,    68,    69,    70,    70,    70,    71,    71,
      72,    72,    73,    74,    75,    75,    75,    76,    77,    77,
      77,    77,    78,    78,    78,    78,    79,    80,    80,    80,
      80,    80,    80,    80,    81,    82,    83,    83,    83,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84
  };

  const unsigned char
  MyParser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     4,     4,     3,     5,     0,
       1,     0,     1,     3,     1,     3,     1,     2,     1,     2,
       2,     1,     1,     1,     1,     2,     3,     1,     2,     2,
       3,     5,     7,     5,     8,     1,     2,     2,     2,     4,
       2,     4,     3,     3,     0,     1,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     2,     2,     2,
       2,     2,     2,     2,     3,     4,     0,     1,     3,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     1,     1,     1
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
  "\"string_literal\"", "\"then\"", "\"@[\"", "\"@]\"", "$accept",
  "translation_unit", "function_definitions", "function_definition",
  "function_expression", "call_signature", "binding_identifier",
  "parameter_variables", "parameter_variable", "type_specifier",
  "statement", "compound_statement", "statement_list", "return_statement",
  "if_statement", "while_statement", "for_statement", "for_init_statement",
  "variable_definition", "const_definition", "initializer_list_expression",
  "map_entry_list_expression", "map_entry_list", "map_entry", "literal",
  "primary_expression", "null_literal", "unary_expression",
  "member_expression", "call_expression", "expression_list", "expression", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  MyParser::yyrline_[] =
  {
       0,   173,   173,   177,   178,   182,   186,   190,   191,   195,
     196,   200,   201,   202,   206,   207,   211,   215,   216,   217,
     218,   219,   220,   221,   222,   226,   227,   231,   232,   236,
     237,   243,   244,   248,   252,   256,   257,   258,   262,   263,
     267,   268,   272,   276,   280,   281,   282,   286,   290,   291,
     292,   293,   309,   310,   311,   312,   316,   320,   321,   322,
     323,   324,   325,   326,   330,   334,   338,   339,   340,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364
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
#line 2038 "Parser/MyParser.cpp" // lalr1.cc:1167
#line 367 "Parser/MyParser.yy" // lalr1.cc:1168


void yy::MyParser::error(const location_type& l, const std::string& m)
{
    driver.error(toLoc(l), m);
}
