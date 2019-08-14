// A Bison parser, made by GNU Bison 3.2.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018 Free Software Foundation, Inc.

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

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.


// Take the name prefix into account.
#define yylex   parser6_lex



#include "dhcp6_parser.h"


// Unqualified %code blocks.
#line 34 "dhcp6_parser.yy" // lalr1.cc:438

#include <dhcp6/parser_context.h>

#line 51 "dhcp6_parser.cc" // lalr1.cc:438


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

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
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
#if PARSER6_DEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
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

#else // !PARSER6_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !PARSER6_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "dhcp6_parser.yy" // lalr1.cc:513
namespace isc { namespace dhcp {
#line 146 "dhcp6_parser.cc" // lalr1.cc:513

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Dhcp6Parser::yytnamerr_ (const char *yystr)
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
  Dhcp6Parser::Dhcp6Parser (isc::dhcp::Parser6Context& ctx_yyarg)
    :
#if PARSER6_DEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      ctx (ctx_yyarg)
  {}

  Dhcp6Parser::~Dhcp6Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  Dhcp6Parser::by_state::by_state ()
    : state (empty_state)
  {}

  Dhcp6Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  void
  Dhcp6Parser::by_state::clear ()
  {
    state = empty_state;
  }

  void
  Dhcp6Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Dhcp6Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  Dhcp6Parser::symbol_number_type
  Dhcp6Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  Dhcp6Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Dhcp6Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 192: // value
      case 196: // map_value
      case 248: // db_type
      case 338: // hr_mode
      case 474: // duid_type
      case 509: // ncr_protocol_value
      case 516: // replace_client_name_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 174: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 173: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 172: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 171: // "constant string"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if defined __cplusplus && 201103L <= __cplusplus
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Dhcp6Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 192: // value
      case 196: // map_value
      case 248: // db_type
      case 338: // hr_mode
      case 474: // duid_type
      case 509: // ncr_protocol_value
      case 516: // replace_client_name_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 174: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 173: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 172: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 171: // "constant string"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if !defined __cplusplus || __cplusplus < 201103L
  Dhcp6Parser::stack_symbol_type&
  Dhcp6Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 192: // value
      case 196: // map_value
      case 248: // db_type
      case 338: // hr_mode
      case 474: // duid_type
      case 509: // ncr_protocol_value
      case 516: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 174: // "boolean"
        value.move< bool > (that.value);
        break;

      case 173: // "floating point"
        value.move< double > (that.value);
        break;

      case 172: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 171: // "constant string"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Dhcp6Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if PARSER6_DEBUG
  template <typename Base>
  void
  Dhcp6Parser::yy_print_ (std::ostream& yyo,
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
    switch (yytype)
    {
            case 171: // "constant string"

#line 249 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< std::string > (); }
#line 398 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 172: // "integer"

#line 249 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 405 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 173: // "floating point"

#line 249 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< double > (); }
#line 412 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 174: // "boolean"

#line 249 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< bool > (); }
#line 419 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 192: // value

#line 249 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 426 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 196: // map_value

#line 249 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 433 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 248: // db_type

#line 249 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 440 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 338: // hr_mode

#line 249 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 447 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 474: // duid_type

#line 249 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 454 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 509: // ncr_protocol_value

#line 249 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 461 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 516: // replace_client_name_value

#line 249 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 468 "dhcp6_parser.cc" // lalr1.cc:672
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  void
  Dhcp6Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Dhcp6Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if defined __cplusplus && 201103L <= __cplusplus
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Dhcp6Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if PARSER6_DEBUG
  std::ostream&
  Dhcp6Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Dhcp6Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Dhcp6Parser::debug_level_type
  Dhcp6Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Dhcp6Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // PARSER6_DEBUG

  Dhcp6Parser::state_type
  Dhcp6Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  Dhcp6Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Dhcp6Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Dhcp6Parser::operator() ()
  {
    return parse ();
  }

  int
  Dhcp6Parser::parse ()
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

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

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
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (ctx));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
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
    yypush_ ("Shifting", yyn, YY_MOVE (yyla));
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
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 192: // value
      case 196: // map_value
      case 248: // db_type
      case 338: // hr_mode
      case 474: // duid_type
      case 509: // ncr_protocol_value
      case 516: // replace_client_name_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 174: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 173: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 172: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 171: // "constant string"
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 258 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 727 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 4:
#line 259 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.CONFIG; }
#line 733 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 6:
#line 260 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP6; }
#line 739 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 8:
#line 261 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 745 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 10:
#line 262 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.SUBNET6; }
#line 751 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 12:
#line 263 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.POOLS; }
#line 757 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 14:
#line 264 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 763 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 16:
#line 265 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 769 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 18:
#line 266 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP6; }
#line 775 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 20:
#line 267 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 781 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 22:
#line 268 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 787 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 24:
#line 269 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 793 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 26:
#line 270 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 799 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 28:
#line 271 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.LOGGING; }
#line 805 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 30:
#line 272 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 811 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 32:
#line 280 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 817 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 33:
#line 281 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 823 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 34:
#line 282 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 829 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 35:
#line 283 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 835 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 36:
#line 284 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 841 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 37:
#line 285 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 847 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 38:
#line 286 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 853 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 39:
#line 289 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 862 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 40:
#line 294 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 873 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 41:
#line 299 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 883 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 42:
#line 305 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 889 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 45:
#line 312 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 898 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 46:
#line 316 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 908 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 47:
#line 323 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 917 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 48:
#line 326 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // list parsing complete. Put any sanity checking here
}
#line 925 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 51:
#line 334 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 934 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 52:
#line 338 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 943 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 53:
#line 345 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // List parsing about to start
}
#line 951 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 54:
#line 347 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 960 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 57:
#line 356 "dhcp6_parser.yy" // lalr1.cc:907
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 969 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 58:
#line 360 "dhcp6_parser.yy" // lalr1.cc:907
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 978 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 59:
#line 371 "dhcp6_parser.yy" // lalr1.cc:907
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 989 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 60:
#line 381 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1000 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 61:
#line 386 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1013 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 70:
#line 409 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 1026 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 71:
#line 416 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1036 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 72:
#line 424 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1046 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 73:
#line 428 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No global parameter is required
    // parsing completed
}
#line 1055 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 108:
#line 473 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1064 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 109:
#line 478 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1073 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 110:
#line 483 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1082 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 111:
#line 488 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1091 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 112:
#line 493 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1100 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 113:
#line 498 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1108 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 114:
#line 500 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1118 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 115:
#line 506 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1129 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 116:
#line 511 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1139 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 117:
#line 517 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1149 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 118:
#line 521 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1158 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 126:
#line 537 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1169 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 127:
#line 542 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1178 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 128:
#line 547 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1187 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 129:
#line 553 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1198 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 130:
#line 558 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1209 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 131:
#line 565 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1220 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 132:
#line 570 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1231 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 133:
#line 577 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1242 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 134:
#line 582 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1251 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 139:
#line 595 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1261 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 140:
#line 599 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1271 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 162:
#line 630 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1279 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 163:
#line 632 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1288 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 164:
#line 637 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1294 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 165:
#line 638 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1300 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 166:
#line 639 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1306 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 167:
#line 640 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1312 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 168:
#line 643 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1320 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 169:
#line 645 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1330 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 170:
#line 651 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1338 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 171:
#line 653 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1348 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 172:
#line 659 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1356 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 173:
#line 661 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1366 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 174:
#line 667 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1375 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 175:
#line 672 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1383 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 176:
#line 674 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1393 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 177:
#line 680 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1402 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 178:
#line 685 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1411 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 179:
#line 690 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1420 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 180:
#line 695 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1429 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 181:
#line 700 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1438 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 182:
#line 705 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1447 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 183:
#line 710 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1456 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 184:
#line 715 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1465 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 185:
#line 720 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1473 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 186:
#line 722 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1483 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 187:
#line 728 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1492 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 188:
#line 733 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1500 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 189:
#line 735 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1510 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 190:
#line 741 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1519 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 191:
#line 746 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1530 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 192:
#line 751 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1539 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 196:
#line 761 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1547 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 197:
#line 763 "dhcp6_parser.yy" // lalr1.cc:907
    {

    if ( (string(yystack_[0].value.as< std::string > ()) == "none") ||
         (string(yystack_[0].value.as< std::string > ()) == "warn") ||
         (string(yystack_[0].value.as< std::string > ()) == "fix") ||
         (string(yystack_[0].value.as< std::string > ()) == "fix-del") ||
         (string(yystack_[0].value.as< std::string > ()) == "del")) {
        ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
        ctx.stack_.back()->set("lease-checks", user);
        ctx.leave();
    } else {
        error(yystack_[0].location, "Unsupported 'lease-checks value: " + string(yystack_[0].value.as< std::string > ()) +
              ", supported values are: none, warn, fix, fix-del, del");
    }
}
#line 1567 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 198:
#line 779 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1578 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 199:
#line 784 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1587 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 204:
#line 797 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1596 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 205:
#line 802 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1605 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 206:
#line 807 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1616 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 207:
#line 812 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1625 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 213:
#line 826 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1634 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 214:
#line 831 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1643 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 215:
#line 838 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1654 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 216:
#line 843 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1663 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 217:
#line 848 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1674 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 218:
#line 853 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1683 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 223:
#line 866 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1693 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 224:
#line 870 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1703 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 225:
#line 876 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1713 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 226:
#line 880 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1723 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 232:
#line 895 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1731 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 233:
#line 897 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1741 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 234:
#line 903 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1749 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 235:
#line 905 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1758 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 236:
#line 911 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1769 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 237:
#line 916 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1779 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 246:
#line 934 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1788 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 247:
#line 939 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1797 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 248:
#line 944 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1806 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 249:
#line 949 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1815 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 250:
#line 954 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1824 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 251:
#line 959 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1833 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 252:
#line 967 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1844 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 253:
#line 972 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1853 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 258:
#line 992 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1863 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 259:
#line 996 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Once we reached this place, the subnet parsing is now complete.
    // If we want to, we can implement default values here.
    // In particular we can do things like this:
    // if (!ctx.stack_.back()->get("interface")) {
    //     ctx.stack_.back()->set("interface", StringElement("loopback"));
    // }
    //
    // We can also stack up one level (Dhcp6) and copy over whatever
    // global parameters we want to:
    // if (!ctx.stack_.back()->get("renew-timer")) {
    //     ElementPtr renew = ctx_stack_[...].get("renew-timer");
    //     if (renew) {
    //         ctx.stack_.back()->set("renew-timer", renew);
    //     }
    // }

    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1889 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 260:
#line 1018 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1899 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 261:
#line 1022 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1909 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 284:
#line 1056 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1917 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 285:
#line 1058 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1927 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 286:
#line 1064 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1935 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 287:
#line 1066 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1945 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 288:
#line 1072 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1953 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 289:
#line 1074 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1963 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 290:
#line 1080 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1971 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 291:
#line 1082 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1981 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 292:
#line 1088 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1992 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 293:
#line 1093 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2001 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 294:
#line 1098 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2009 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 295:
#line 1100 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2018 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 296:
#line 1105 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2024 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 297:
#line 1106 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2030 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 298:
#line 1107 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2036 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 299:
#line 1108 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2042 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 300:
#line 1111 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2051 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 301:
#line 1116 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2060 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 302:
#line 1124 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2071 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 303:
#line 1129 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2080 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 308:
#line 1144 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2090 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 309:
#line 1148 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 2098 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 329:
#line 1179 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2109 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 330:
#line 1184 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2118 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 331:
#line 1192 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2127 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 332:
#line 1195 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // parsing completed
}
#line 2135 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 337:
#line 1211 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2145 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 338:
#line 1215 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2157 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 339:
#line 1226 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2167 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 340:
#line 1230 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2179 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 356:
#line 1262 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2188 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 358:
#line 1269 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2196 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 359:
#line 1271 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2206 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 360:
#line 1277 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2214 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 361:
#line 1279 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2224 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 362:
#line 1285 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2232 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 363:
#line 1287 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2242 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 365:
#line 1295 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2250 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 366:
#line 1297 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2260 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 367:
#line 1303 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2269 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 368:
#line 1312 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2280 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 369:
#line 1317 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2289 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 374:
#line 1336 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2299 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 375:
#line 1340 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2308 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 376:
#line 1348 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2318 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 377:
#line 1352 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2327 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 392:
#line 1385 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2335 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 393:
#line 1387 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2345 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 396:
#line 1397 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2354 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 397:
#line 1402 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2363 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 398:
#line 1410 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2374 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 399:
#line 1415 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2383 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 404:
#line 1430 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2393 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 405:
#line 1434 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2403 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 406:
#line 1440 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2413 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 407:
#line 1444 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2422 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 417:
#line 1462 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2430 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 418:
#line 1464 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2440 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 419:
#line 1470 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2448 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 420:
#line 1472 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr parent = ctx.stack_.back();
    ElementPtr user_context = yystack_[0].value.as< ElementPtr > ();
    ConstElementPtr old = parent->get("user-context");

    // Handle already existing user context
    if (old) {
        // Check if it was a comment or a duplicate
        if ((old->size() != 1) || !old->contains("comment")) {
            std::stringstream msg;
            msg << "duplicate user-context entries (previous at "
                << old->getPosition().str() << ")";
            error(yystack_[3].location, msg.str());
        }
        // Merge the comment
        user_context->set("comment", old->get("comment"));
    }

    // Set the user context
    parent->set("user-context", user_context);
    ctx.leave();
}
#line 2475 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 421:
#line 1495 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2483 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 422:
#line 1497 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr parent = ctx.stack_.back();
    ElementPtr user_context(new MapElement(ctx.loc2pos(yystack_[3].location)));
    ElementPtr comment(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    user_context->set("comment", comment);

    // Handle already existing user context
    ConstElementPtr old = parent->get("user-context");
    if (old) {
        // Check for duplicate comment
        if (old->contains("comment")) {
            std::stringstream msg;
            msg << "duplicate user-context/comment entries (previous at "
                << old->getPosition().str() << ")";
            error(yystack_[3].location, msg.str());
        }
        // Merge the user context in the comment
        merge(user_context, old);
    }

    // Set the user context
    parent->set("user-context", user_context);
    ctx.leave();
}
#line 2512 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 423:
#line 1525 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2523 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 424:
#line 1530 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2532 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 429:
#line 1545 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2542 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 430:
#line 1549 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2554 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 431:
#line 1557 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2564 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 432:
#line 1561 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2576 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 446:
#line 1586 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2584 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 447:
#line 1588 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2594 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 448:
#line 1594 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2603 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 449:
#line 1599 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2611 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 450:
#line 1601 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2621 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 451:
#line 1607 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2630 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 452:
#line 1612 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2639 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 453:
#line 1620 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2650 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 454:
#line 1625 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2659 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 459:
#line 1638 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2669 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 460:
#line 1642 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2678 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 461:
#line 1647 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2688 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 462:
#line 1651 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2697 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 478:
#line 1678 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2708 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 479:
#line 1683 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2717 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 480:
#line 1688 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2728 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 481:
#line 1693 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2737 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 482:
#line 1698 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2745 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 483:
#line 1700 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2755 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 484:
#line 1706 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2763 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 485:
#line 1708 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2773 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 486:
#line 1714 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2781 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 487:
#line 1716 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2791 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 488:
#line 1722 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2799 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 489:
#line 1724 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2809 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 490:
#line 1730 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2820 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 491:
#line 1735 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2829 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 492:
#line 1743 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2840 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 493:
#line 1748 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2849 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 496:
#line 1757 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2857 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 497:
#line 1759 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2867 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 498:
#line 1768 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2878 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 499:
#line 1773 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2887 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 502:
#line 1782 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2897 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 503:
#line 1786 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2907 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 516:
#line 1811 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2915 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 517:
#line 1813 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2925 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 518:
#line 1819 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2934 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 519:
#line 1827 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2945 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 520:
#line 1832 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2956 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 532:
#line 1854 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2964 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 533:
#line 1856 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2973 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 534:
#line 1861 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2979 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 535:
#line 1862 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2985 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 536:
#line 1863 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2991 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 537:
#line 1866 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3000 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 538:
#line 1871 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3008 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 539:
#line 1873 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3018 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 540:
#line 1879 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3027 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 541:
#line 1884 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3036 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 542:
#line 1891 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3045 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 543:
#line 1898 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3056 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 544:
#line 1903 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3065 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 552:
#line 1919 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3073 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 553:
#line 1921 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3083 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 554:
#line 1927 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3091 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 555:
#line 1929 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3101 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 556:
#line 1937 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3109 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 557:
#line 1939 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr qc = yystack_[0].value.as< ElementPtr > ();
    ctx.stack_.back()->set("dhcp-queue-control", qc);

    // Doing this manually, because dhcp-queue-control
    // content is otherwise arbitrary
    if (!qc->contains("enable-queue")) {
        std::stringstream msg;
        msg << "'enable-queue' is required: ";
        msg  << "(" << qc->getPosition().str() << ")";
        error(yystack_[3].location, msg.str());
    }

    // queue-enable is mandatory
    ConstElementPtr enable_queue = qc->get("enable-queue");
    if (enable_queue->getType() != Element::boolean) {
        std::stringstream msg;
        msg << "'enable-queue' must be boolean: ";
        msg  << "(" << qc->getPosition().str() << ")";
        error(yystack_[3].location, msg.str());
     }

    // if queue-type is supplied make sure it's a string
    if (qc->contains("queue-type")) {
        ConstElementPtr queue_type = qc->get("queue-type");
        if (queue_type->getType() != Element::string) {
            std::stringstream msg;
            msg << "'queue-type' must be a string: ";
            msg  << "(" << qc->getPosition().str() << ")";
            error(yystack_[3].location, msg.str());
        }
    }

    ctx.leave();
}
#line 3149 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 558:
#line 1977 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3160 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 559:
#line 1982 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3171 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 560:
#line 1989 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3181 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 561:
#line 1993 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3191 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 582:
#line 2023 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3200 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 583:
#line 2028 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3208 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 584:
#line 2030 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3218 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 585:
#line 2036 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3226 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 586:
#line 2038 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3236 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 587:
#line 2044 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3245 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 588:
#line 2049 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3253 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 589:
#line 2051 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3263 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 590:
#line 2057 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3272 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 591:
#line 2062 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3281 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 592:
#line 2067 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3289 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 593:
#line 2069 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3298 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 594:
#line 2075 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3304 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 595:
#line 2076 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3310 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 596:
#line 2079 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3318 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 597:
#line 2081 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3328 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 598:
#line 2087 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3337 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 599:
#line 2092 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3346 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 600:
#line 2097 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3354 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 601:
#line 2099 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3363 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 602:
#line 2105 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3371 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 603:
#line 2108 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3379 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 604:
#line 2111 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3387 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 605:
#line 2114 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3395 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 606:
#line 2117 "dhcp6_parser.yy" // lalr1.cc:907
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3404 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 607:
#line 2123 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3412 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 608:
#line 2125 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3422 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 609:
#line 2131 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3430 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 610:
#line 2133 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3440 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 611:
#line 2139 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3448 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 612:
#line 2141 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3458 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 613:
#line 2149 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3466 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 614:
#line 2151 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3475 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 615:
#line 2156 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3483 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 616:
#line 2158 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3492 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 617:
#line 2163 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3500 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 618:
#line 2165 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3509 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 619:
#line 2172 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3520 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 620:
#line 2177 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3530 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 621:
#line 2183 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3540 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 622:
#line 2187 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No config_control params are required
    // parsing completed
}
#line 3549 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 626:
#line 2201 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3560 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 627:
#line 2206 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3569 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 628:
#line 2216 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3580 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 629:
#line 2221 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3589 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 630:
#line 2226 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3599 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 631:
#line 2230 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // parsing completed
}
#line 3607 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 635:
#line 2246 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3618 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 636:
#line 2251 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3627 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 639:
#line 2263 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3637 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 640:
#line 2267 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3645 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 650:
#line 2284 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3654 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 651:
#line 2289 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3662 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 652:
#line 2291 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3672 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 653:
#line 2297 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3683 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 654:
#line 2302 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3692 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 657:
#line 2311 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3702 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 658:
#line 2315 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3710 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 665:
#line 2329 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3718 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 666:
#line 2331 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3728 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 667:
#line 2337 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3737 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 668:
#line 2342 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3746 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 669:
#line 2347 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3755 "dhcp6_parser.cc" // lalr1.cc:907
    break;


#line 3759 "dhcp6_parser.cc" // lalr1.cc:907
            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
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
      yypush_ ("Shifting", YY_MOVE (error_token));
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
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Dhcp6Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  Dhcp6Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
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


  const short Dhcp6Parser::yypact_ninf_ = -824;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     336,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,    51,    55,    50,    56,
      58,    76,    80,   110,   143,   152,   163,   184,   186,   194,
     201,   208,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,    55,    54,    28,    59,    25,   238,    23,   251,
     349,    66,    29,   102,   -50,   455,    32,   242,  -824,   270,
     253,   261,   285,   266,  -824,  -824,  -824,  -824,  -824,   296,
    -824,    71,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,   297,   318,   338,   346,   348,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,   350,  -824,  -824,  -824,  -824,
     106,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,   354,  -824,   139,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,   360,   374,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,   141,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,   170,
    -824,  -824,  -824,  -824,  -824,   380,  -824,   386,   391,  -824,
    -824,  -824,  -824,  -824,  -824,   187,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,   323,   337,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,   358,  -824,  -824,   394,  -824,  -824,  -824,
     395,  -824,  -824,   397,   403,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,   404,   406,
    -824,  -824,  -824,  -824,   405,   417,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,   189,  -824,
    -824,  -824,   419,  -824,  -824,   423,  -824,   424,   430,  -824,
    -824,   432,   441,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
     213,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,   214,  -824,
    -824,  -824,   215,  -824,  -824,  -824,    55,    55,  -824,   276,
     444,   445,   446,   447,   448,  -824,    28,  -824,   449,   450,
     453,   456,   459,   292,   293,   295,   298,   299,   462,   464,
     465,   468,   469,   471,   472,   474,   475,   476,   477,   478,
     479,   480,   482,   483,   484,   340,   503,   504,   505,    59,
    -824,   506,   339,    25,  -824,   510,   511,   512,   514,   515,
     351,   352,   520,   521,   523,   238,  -824,   524,    23,  -824,
     525,   359,   526,   363,   364,   251,  -824,   528,   530,   533,
     534,   535,   536,   537,  -824,   349,  -824,   540,   542,   375,
     544,   545,   546,   377,  -824,    29,   548,   379,   381,  -824,
     102,   550,   552,   -55,  -824,   383,   558,   559,   392,   561,
     398,   399,   562,   565,   400,   401,   568,   569,   572,   587,
     455,  -824,   590,    32,  -824,   592,   242,  -824,  -824,  -824,
     595,   593,   594,    55,    55,    55,  -824,   596,   597,   598,
     599,   602,  -824,  -824,  -824,  -824,  -824,   431,   603,   604,
     605,   606,   440,   158,   607,   609,   610,   611,   612,   613,
     615,   616,   617,   618,  -824,   620,   606,   621,  -824,   624,
    -824,  -824,   625,   626,   451,   452,   461,  -824,  -824,   624,
     463,   628,  -824,   466,  -824,   467,  -824,   470,  -824,  -824,
    -824,   624,   624,   624,   473,   481,   485,   486,  -824,   487,
     488,  -824,   489,   490,   491,  -824,  -824,   492,  -824,  -824,
    -824,   493,    55,  -824,  -824,   494,   495,  -824,   496,  -824,
    -824,    -2,   499,  -824,  -824,   -10,   497,   498,   500,  -824,
     634,  -824,   635,  -824,    55,    59,    32,  -824,  -824,  -824,
     242,    25,   212,   212,   636,  -824,   638,   639,   640,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,   641,   -51,    55,
     112,   566,   643,   644,   646,    82,    99,    27,  -824,   455,
    -824,  -824,   647,   648,  -824,  -824,  -824,  -824,  -824,    22,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,   663,   636,  -824,   216,   249,   250,
     252,  -824,  -824,  -824,  -824,   629,   668,   669,   670,   671,
    -824,   672,   673,  -824,   674,   675,   676,   677,  -824,   256,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,   259,
    -824,   678,   614,  -824,  -824,   679,   680,  -824,  -824,   681,
     683,  -824,  -824,   682,   686,  -824,  -824,   684,   688,  -824,
    -824,  -824,   168,  -824,  -824,  -824,   687,  -824,  -824,  -824,
     288,  -824,  -824,  -824,  -824,   260,  -824,  -824,  -824,   353,
    -824,  -824,   689,   691,  -824,  -824,   690,   694,  -824,   695,
     696,   697,   698,   699,   700,   263,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,   701,   702,   703,  -824,  -824,
    -824,  -824,   269,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,   279,  -824,  -824,  -824,   280,   527,
    -824,   704,   705,  -824,  -824,   706,   708,  -824,  -824,  -824,
     707,  -824,  -824,   362,  -824,   710,  -824,  -824,  -824,  -824,
     709,   713,   714,   715,   549,   508,   551,   518,   553,   716,
     554,   555,   718,   556,   557,   560,   563,   212,  -824,  -824,
     212,  -824,   636,   238,  -824,   638,    29,  -824,   639,   102,
    -824,   640,   389,  -824,   641,   -51,  -824,  -824,   112,  -824,
     720,   566,  -824,    49,   643,  -824,   349,  -824,   644,   -50,
    -824,   646,   564,   567,   570,   571,   573,   574,    82,  -824,
     726,   727,   575,   576,   577,    99,  -824,   728,   729,    27,
    -824,  -824,  -824,   731,   711,    23,  -824,   647,   251,  -824,
     648,   734,  -824,   254,   663,  -824,  -824,   326,   538,   579,
     580,  -824,  -824,  -824,  -824,  -824,   581,  -824,  -824,   582,
    -824,  -824,  -824,  -824,  -824,   281,  -824,   287,  -824,   732,
    -824,   733,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,   294,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,   583,  -824,  -824,   740,  -824,
    -824,  -824,  -824,  -824,   747,   753,  -824,  -824,  -824,  -824,
    -824,   749,  -824,   316,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,   308,   588,  -824,  -824,  -824,  -824,   589,   591,
    -824,  -824,   600,   325,  -824,   327,  -824,   631,  -824,   754,
    -824,  -824,  -824,  -824,  -824,   329,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,   389,  -824,  -824,   757,   622,
    -824,    49,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,   759,   627,   760,   254,  -824,
    -824,   632,  -824,  -824,   637,  -824,   633,  -824,  -824,   758,
    -824,  -824,   382,  -824,    11,   758,  -824,  -824,   762,   763,
     764,   335,  -824,  -824,  -824,  -824,  -824,  -824,   766,   649,
     642,   645,    11,  -824,   655,  -824,  -824,  -824,  -824,  -824
  };

  const unsigned short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   117,     9,
     260,    11,   406,    13,   431,    15,   461,    17,   331,    19,
     339,    21,   376,    23,   225,    25,   560,    27,   630,    29,
     621,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     463,     0,   341,   378,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   628,   613,   615,   617,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   619,   115,
     129,   131,   133,     0,     0,     0,     0,     0,   113,   252,
     329,   368,   419,   421,   294,   302,   198,   215,   206,   191,
     498,   453,   217,   236,   519,     0,   543,   556,   558,   107,
       0,    74,    76,    77,    78,    79,    80,   105,    83,    84,
      85,    86,   102,    87,    89,    88,    93,    94,    81,   106,
      82,    91,    92,   100,   101,   103,    90,    95,    96,    97,
      98,    99,   104,   126,     0,   125,     0,   119,   121,   122,
     123,   124,   398,   423,   284,   286,   288,     0,     0,   292,
     290,   492,   283,   264,   265,   266,   267,     0,   262,   271,
     272,   273,   276,   277,   279,   274,   275,   268,   269,   281,
     282,   270,   278,   280,   417,   416,   412,   413,   411,     0,
     408,   410,   414,   415,   446,     0,   449,     0,     0,   445,
     439,   440,   438,   443,   444,     0,   433,   435,   436,   441,
     442,   437,   490,   478,   480,   482,   484,   486,   488,   477,
     474,   475,   476,     0,   464,   465,   469,   470,   467,   471,
     472,   473,   468,     0,   358,   175,     0,   362,   360,   365,
       0,   354,   355,     0,   342,   343,   345,   357,   346,   347,
     348,   364,   349,   350,   351,   352,   353,   392,     0,     0,
     390,   391,   394,   395,     0,   379,   380,   382,   383,   384,
     385,   386,   387,   388,   389,   232,   234,   229,     0,   227,
     230,   231,     0,   583,   585,     0,   588,     0,     0,   592,
     596,     0,     0,   600,   607,   609,   611,   581,   579,   580,
       0,   562,   564,   565,   566,   567,   568,   569,   570,   571,
     572,   573,   574,   575,   576,   577,   578,   635,     0,   632,
     634,   626,     0,   623,   625,    48,     0,     0,    41,     0,
       0,     0,     0,     0,     0,    59,     0,    61,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      73,     0,     0,     0,   118,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   261,     0,     0,   407,
       0,     0,     0,     0,     0,     0,   432,     0,     0,     0,
       0,     0,     0,     0,   462,     0,   332,     0,     0,     0,
       0,     0,     0,     0,   340,     0,     0,     0,     0,   377,
       0,     0,     0,     0,   226,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   561,     0,     0,   631,     0,     0,   622,    52,    45,
       0,     0,     0,     0,     0,     0,    63,     0,     0,     0,
       0,     0,   108,   109,   110,   111,   112,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   542,     0,     0,     0,    75,     0,
     128,   120,     0,     0,     0,     0,     0,   300,   301,     0,
       0,     0,   263,     0,   409,     0,   448,     0,   451,   452,
     434,     0,     0,     0,     0,     0,     0,     0,   466,     0,
       0,   356,     0,     0,     0,   367,   344,     0,   396,   397,
     381,     0,     0,   228,   582,     0,     0,   587,     0,   590,
     591,     0,     0,   598,   599,     0,     0,     0,     0,   563,
       0,   633,     0,   624,     0,     0,     0,   614,   616,   618,
       0,     0,     0,     0,   135,   114,   254,   333,   370,    42,
     420,   422,   296,   297,   298,   299,   295,   304,     0,    49,
       0,     0,     0,   455,   219,     0,     0,     0,   557,     0,
      53,   127,   400,   425,   285,   287,   289,   293,   291,     0,
     418,   447,   450,   491,   479,   481,   483,   485,   487,   489,
     359,   176,   363,   361,   366,   393,   233,   235,   584,   586,
     589,   594,   595,   593,   597,   602,   603,   604,   605,   606,
     601,   608,   610,   612,     0,   135,    46,     0,     0,     0,
       0,   162,   168,   170,   172,     0,     0,     0,     0,     0,
     185,     0,     0,   188,     0,     0,     0,     0,   161,     0,
     141,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   155,   156,   157,   158,   153,   154,   159,   160,     0,
     139,     0,   136,   137,   258,     0,   255,   256,   337,     0,
     334,   335,   374,     0,   371,   372,   308,     0,   305,   306,
     204,   205,     0,   200,   202,   203,     0,   213,   214,   210,
       0,   208,   211,   212,   196,     0,   193,   195,   502,     0,
     500,   459,     0,   456,   457,   223,     0,   220,   221,     0,
       0,     0,     0,     0,     0,     0,   238,   240,   241,   242,
     243,   244,   245,   532,   538,     0,     0,     0,   531,   528,
     529,   530,     0,   521,   523,   526,   524,   525,   527,   552,
     554,   551,   549,   550,     0,   545,   547,   548,     0,    55,
     404,     0,   401,   402,   429,     0,   426,   427,   496,   495,
       0,   494,   639,     0,   637,     0,    71,   629,   620,   116,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   130,   132,
       0,   134,     0,     0,   253,     0,   341,   330,     0,   378,
     369,     0,     0,   303,     0,     0,   199,   216,     0,   207,
       0,     0,   192,   504,     0,   499,   463,   454,     0,     0,
     218,     0,     0,     0,     0,     0,     0,     0,     0,   237,
       0,     0,     0,     0,     0,     0,   520,     0,     0,     0,
     544,   559,    57,     0,    56,     0,   399,     0,     0,   424,
       0,     0,   493,     0,     0,   636,   627,     0,     0,     0,
       0,   174,   177,   178,   179,   180,     0,   187,   181,     0,
     182,   183,   184,   190,   142,     0,   138,     0,   257,     0,
     336,     0,   373,   328,   323,   325,   316,   317,   312,   313,
     314,   315,   321,   322,   320,   324,     0,   310,   318,   326,
     327,   319,   307,   201,   209,     0,   194,   516,     0,   514,
     515,   511,   512,   513,     0,   505,   506,   508,   509,   510,
     501,     0,   458,     0,   222,   246,   247,   248,   249,   250,
     251,   239,     0,     0,   537,   540,   541,   522,     0,     0,
     546,    54,     0,     0,   403,     0,   428,     0,   653,     0,
     651,   649,   643,   647,   648,     0,   641,   645,   646,   644,
     638,   164,   165,   166,   167,   163,   169,   171,   173,   186,
     189,   140,   259,   338,   375,     0,   309,   197,     0,     0,
     503,     0,   460,   224,   534,   535,   536,   533,   539,   553,
     555,    58,   405,   430,   497,     0,     0,     0,     0,   640,
     311,     0,   518,   507,     0,   650,     0,   642,   517,     0,
     652,   657,     0,   655,     0,     0,   654,   665,     0,     0,
       0,     0,   659,   661,   662,   663,   664,   656,     0,     0,
       0,     0,     0,   658,     0,   667,   668,   669,   660,   666
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,     6,  -824,  -428,
    -824,   258,  -824,  -824,  -824,  -824,   175,  -824,  -419,  -824,
    -824,  -824,   -74,  -824,  -824,  -824,   411,  -824,  -824,  -824,
    -824,   202,   387,   -62,   -46,   -45,   -43,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,   221,   410,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,   153,  -824,   -12,  -824,  -565,
      -3,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,   -70,  -824,  -600,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
     -26,  -824,  -824,  -824,  -824,  -824,   -19,  -584,  -824,  -824,
    -824,  -824,   -20,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,   -28,  -824,  -824,  -824,   -25,   393,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,   -31,  -824,  -824,  -824,  -824,  -824,
    -824,  -823,  -824,  -824,  -824,     3,  -824,  -824,  -824,     7,
     434,  -824,  -824,  -822,  -824,  -819,  -824,   -36,  -824,   -32,
    -824,   -42,  -824,  -824,  -824,  -816,  -824,  -824,  -824,  -824,
      -1,  -824,  -824,  -174,   773,  -824,  -824,  -824,  -824,  -824,
       8,  -824,  -824,  -824,    12,  -824,   412,  -824,   -76,  -824,
    -824,  -824,  -824,  -824,   -69,  -824,  -824,  -824,  -824,  -824,
     -11,  -824,  -824,  -824,     9,  -824,  -824,  -824,    15,  -824,
     418,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,   -30,  -824,  -824,  -824,   -23,   457,  -824,  -824,
     -58,  -824,   -24,  -824,  -824,  -824,  -824,  -824,   -27,  -824,
    -824,  -824,   -29,   458,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,   -60,  -824,  -824,  -824,     2,  -824,  -824,  -824,    10,
    -824,   442,   257,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -815,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,    14,  -824,  -824,  -824,  -151,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,    -4,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,    -7,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
     271,   415,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,   301,   413,
    -824,  -824,  -824,  -824,  -824,  -824,   302,   420,  -824,  -824,
    -824,    -9,  -824,  -824,  -156,  -824,  -824,  -824,  -824,  -824,
    -824,  -171,  -824,  -824,  -186,  -824,  -824,  -824,  -824,  -824
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   600,    92,    93,    43,    72,    89,    90,   621,   799,
     893,   894,   688,    45,    74,   101,   102,   103,   360,    47,
      75,   140,   141,   142,   143,   144,   145,   146,   147,   378,
     148,   369,    49,    76,   176,   177,   178,   401,   179,   149,
     370,   150,   371,   151,   372,   711,   712,   713,   840,   689,
     690,   691,   820,  1015,   692,   821,   693,   822,   694,   823,
     695,   696,   438,   697,   698,   699,   700,   701,   702,   703,
     704,   705,   829,   706,   707,   832,   708,   152,   389,   745,
     746,   747,   860,   153,   386,   732,   733,   734,   735,   154,
     388,   740,   741,   742,   743,   155,   387,   156,   392,   756,
     757,   758,   869,    65,    84,   308,   309,   310,   451,   311,
     452,   157,   393,   765,   766,   767,   768,   769,   770,   771,
     772,   158,   379,   715,   716,   717,   843,    51,    77,   197,
     198,   199,   407,   200,   408,   201,   409,   202,   413,   203,
     412,   159,   384,   606,   205,   206,   160,   385,   727,   728,
     729,   852,   946,   947,   161,   380,    59,    81,   719,   720,
     721,   846,    61,    82,   273,   274,   275,   276,   277,   278,
     279,   437,   280,   441,   281,   440,   282,   283,   442,   284,
     162,   381,   723,   724,   725,   849,    63,    83,   294,   295,
     296,   297,   298,   446,   299,   300,   301,   302,   208,   405,
     801,   802,   803,   895,    53,    78,   219,   220,   221,   417,
     163,   382,   164,   383,   211,   406,   805,   806,   807,   898,
      55,    79,   235,   236,   237,   420,   238,   239,   422,   240,
     241,   165,   391,   752,   753,   754,   866,    57,    80,   253,
     254,   255,   256,   428,   257,   429,   258,   430,   259,   431,
     260,   432,   261,   433,   262,   427,   213,   414,   810,   811,
     901,   166,   390,   749,   750,   863,   964,   965,   966,   967,
     968,  1028,   969,   167,   394,   782,   783,   784,   880,  1037,
     785,   786,   881,   787,   788,   168,   169,   396,   794,   795,
     796,   887,   797,   888,   170,   397,   171,   398,    67,    85,
     330,   331,   332,   333,   456,   334,   457,   335,   336,   459,
     337,   338,   339,   462,   653,   340,   463,   341,   342,   343,
     466,   660,   344,   467,   345,   468,   346,   469,   104,   362,
     105,   363,   106,   364,   172,   368,    71,    87,   352,   353,
     354,   475,   107,   361,    69,    86,   348,   349,   350,   472,
     813,   814,   903,  1005,  1006,  1007,  1008,  1047,  1009,  1045,
    1062,  1063,  1064,  1071,  1072,  1073,  1078,  1074,  1075,  1076
  };

  const unsigned short
  Dhcp6Parser::yytable_[] =
  {
     100,   139,   175,   192,   215,   229,   249,   292,   271,   290,
     307,   327,   272,   291,   293,   193,   779,   212,   180,   209,
     222,   233,   251,    40,   285,   303,   739,   328,   709,   939,
     940,   194,   195,   941,   196,   204,   945,   951,    94,   173,
     174,   730,   216,   230,   305,   306,   217,   231,   264,   305,
     306,    32,   181,   210,   223,   234,   252,    44,   286,   304,
      33,   329,    34,    46,    35,    48,   207,   218,   232,   250,
     108,   121,   109,   599,   366,   110,   111,   112,   265,   367,
     266,   267,   214,    50,   268,   269,   270,    52,   599,   122,
     123,   122,   123,   122,   123,   122,   123,   121,   265,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   189,   399,
     627,   190,   243,   120,   400,   122,   123,    54,   773,   808,
     731,    99,   633,   634,   635,   122,   123,   676,   655,   656,
     657,   658,   124,   651,   652,   957,   958,   125,   126,   127,
     128,   129,   403,   130,   415,   789,   790,   404,   131,   416,
      56,   265,   287,   266,   267,   288,   289,   132,  1067,    58,
     133,  1068,  1069,  1070,   659,   122,   123,   134,   122,   123,
      60,   855,    95,   418,   856,   135,   136,   347,   419,   137,
     138,    96,    97,    98,   759,   760,   761,   762,   763,   764,
     425,    62,   453,    64,    99,   426,    99,   454,    99,    99,
      99,    66,   939,   940,   730,   737,   941,   738,    68,   945,
     951,   774,   775,   776,   777,    70,   470,   473,   476,   399,
      99,   471,   474,   477,   816,    91,    36,    37,    38,    39,
      99,   671,   602,   603,   604,   605,   672,   673,   674,   675,
     676,   677,   678,   679,   680,   681,   682,   683,   684,   685,
     686,   687,   473,   476,   351,   403,   356,   817,   818,   837,
     819,   265,   837,   861,   838,   357,   878,   839,   862,   359,
      99,   879,   885,    99,   739,   925,   355,   886,   113,   114,
     115,   116,   889,   470,   837,   779,   121,   890,   891,  1021,
     415,   858,   100,   358,   859,  1022,   182,  1025,   183,   121,
     365,   373,  1026,   265,   122,   123,   184,   185,   186,   187,
     188,   124,   224,   225,   226,   227,   228,   122,   123,   453,
     122,   123,   374,   189,  1033,   139,   190,   131,   418,   175,
     425,   434,  1048,  1042,   191,  1043,   189,  1049,  1082,   190,
     435,   192,   375,  1083,   215,   180,  1011,  1012,  1013,  1014,
     376,   229,   377,   193,   395,   212,   864,   209,   402,   865,
     222,   249,   478,   479,   410,   904,   436,   233,   905,   194,
     195,   271,   196,   204,   292,   272,   290,   251,   411,   181,
     291,   293,   216,    99,   421,  1065,   217,   285,  1066,   230,
     423,   210,   303,   231,   223,   424,   327,   121,   439,   443,
     998,   234,   999,  1000,   207,   444,   445,   218,   447,    99,
     448,   252,   328,   449,   232,   122,   123,  1034,  1035,  1036,
     450,   286,    99,   455,   250,    99,   304,   458,   460,   113,
     114,   115,   116,   242,   461,   119,   464,   121,   265,   243,
     244,   245,   246,   247,   248,   465,   329,   480,   481,   482,
     483,   484,   485,   487,   488,   122,   123,   489,   185,   186,
     490,   188,   124,   491,   492,   493,   497,   494,   498,   499,
     495,   496,   500,   501,   189,   502,   503,   190,   504,   505,
     506,   507,   508,   509,   510,   191,   511,   512,   513,   587,
     588,   589,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,   515,   516,   517,
     519,   139,   514,   520,   522,   523,   524,   175,   525,   526,
      99,   122,   123,   527,   529,   530,   528,   531,   533,   535,
     537,   536,   541,   180,   542,   538,   539,   543,   544,   545,
     546,   547,   778,   791,   549,   327,   550,   551,   552,   553,
     554,   555,   557,   558,   561,   559,   562,   564,   780,   792,
      99,   328,   565,   566,   567,   568,   571,   181,   647,   572,
     569,   570,   575,   576,   573,   574,   577,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     666,   578,   781,   793,   580,   329,   582,   325,   326,   584,
     585,   586,   595,   590,   591,   592,   593,   594,   596,   597,
     598,   601,   607,    34,   608,   609,   610,   842,   612,   611,
     613,   614,   624,   625,   615,   616,    99,   617,   619,   620,
     622,   623,   626,   824,   628,   629,   654,   630,   631,   664,
     665,   632,  1059,   710,   636,   714,   718,   722,   726,   744,
     748,   751,   637,   755,   800,   804,   638,   639,   640,   641,
     642,   643,   644,   645,   646,   648,   649,   650,   661,   662,
     812,   663,   825,   826,   827,   828,   830,   831,   833,   834,
     835,   836,   912,   845,   841,   844,   848,   847,   850,   851,
     853,   854,   914,   857,   868,   867,   870,   871,   892,   872,
     873,   874,   875,   876,   877,   882,   883,   884,   897,  1016,
     896,   900,   899,   907,   992,   902,   906,   908,   909,   910,
     916,   911,   919,   913,   955,   915,   917,   918,   920,   921,
     982,   983,   988,   989,   922,   923,   975,   991,   997,   976,
    1023,  1024,   977,   978,  1029,   979,   980,   984,   985,   986,
    1017,  1018,  1019,  1020,  1027,  1030,  1031,  1032,  1046,  1038,
    1039,  1051,  1040,  1054,  1056,  1061,  1079,  1080,  1081,   192,
    1084,  1041,   271,   292,   618,   290,   272,   486,   933,   291,
     293,   193,   938,   212,   736,   209,   518,   667,   285,   959,
     934,   303,   249,   960,   949,   307,  1052,   194,   195,  1055,
     196,   204,  1044,  1058,  1060,   962,   935,   936,   251,   937,
     944,   778,   670,   521,  1086,   791,   942,  1087,   815,   210,
     943,   215,   286,  1085,   229,   304,  1089,   780,   950,  1001,
     926,   792,   207,  1002,   924,   956,   953,   222,   954,   963,
     233,   948,   252,   974,   973,  1003,   563,   981,   928,   532,
     927,  1050,   961,   952,   263,   250,   930,   556,   929,   216,
     932,   781,   230,   217,   931,   793,   231,   994,   560,   995,
     972,   223,   993,   996,   234,   534,   971,   548,   970,  1004,
    1053,   987,   990,   540,   218,   579,   809,   232,   668,   583,
     798,   669,  1057,   581,  1077,  1010,  1088,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   933,     0,     0,     0,   938,     0,   959,     0,     0,
       0,   960,     0,   934,     0,     0,     0,   949,     0,     0,
       0,     0,     0,   962,  1001,     0,     0,     0,  1002,   935,
     936,     0,   937,   944,     0,     0,     0,     0,     0,   942,
    1003,     0,     0,   943,     0,     0,     0,     0,     0,     0,
       0,   950,     0,     0,     0,     0,     0,   963,     0,     0,
       0,     0,     0,     0,   948,     0,     0,     0,     0,     0,
     961,     0,     0,     0,  1004
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    83,    82,    83,
      84,    85,    82,    83,    83,    77,   616,    77,    76,    77,
      78,    79,    80,    17,    82,    83,   610,    85,   593,   852,
     852,    77,    77,   852,    77,    77,   852,   852,    10,    14,
      15,    92,    78,    79,    99,   100,    78,    79,    19,    99,
     100,     0,    76,    77,    78,    79,    80,     7,    82,    83,
       5,    85,     7,     7,     9,     7,    77,    78,    79,    80,
      11,    48,    13,   501,     3,    16,    17,    18,    49,     8,
      51,    52,    59,     7,    55,    56,    57,     7,   516,    66,
      67,    66,    67,    66,    67,    66,    67,    48,    49,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    85,     3,
     529,    88,    90,    47,     8,    66,    67,     7,    19,    97,
     171,   171,   541,   542,   543,    66,    67,    28,   138,   139,
     140,   141,    73,   135,   136,    86,    87,    78,    79,    80,
      81,    82,     3,    84,     3,   118,   119,     8,    89,     8,
       7,    49,    50,    51,    52,    53,    54,    98,   147,     7,
     101,   150,   151,   152,   174,    66,    67,   108,    66,    67,
       7,     3,   144,     3,     6,   116,   117,   145,     8,   120,
     121,   153,   154,   155,   102,   103,   104,   105,   106,   107,
       3,     7,     3,     7,   171,     8,   171,     8,   171,   171,
     171,     7,  1025,  1025,    92,    93,  1025,    95,     7,  1025,
    1025,   112,   113,   114,   115,     7,     3,     3,     3,     3,
     171,     8,     8,     8,     8,   171,   171,   172,   173,   174,
     171,    19,    74,    75,    76,    77,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,     3,     3,    12,     3,     3,     8,     8,     3,
       8,    49,     3,     3,     8,     4,     3,     8,     8,     3,
     171,     8,     3,   171,   858,   840,     6,     8,    40,    41,
      42,    43,     3,     3,     3,   885,    48,     8,     8,     8,
       3,     3,   366,     8,     6,     8,    58,     3,    60,    48,
       4,     4,     8,    49,    66,    67,    68,    69,    70,    71,
      72,    73,    61,    62,    63,    64,    65,    66,    67,     3,
      66,    67,     4,    85,     8,   399,    88,    89,     3,   403,
       3,     8,     3,     8,    96,     8,    85,     8,     3,    88,
       3,   415,     4,     8,   418,   403,    20,    21,    22,    23,
       4,   425,     4,   415,     4,   415,     3,   415,     4,     6,
     418,   435,   356,   357,     4,     3,     8,   425,     6,   415,
     415,   445,   415,   415,   450,   445,   450,   435,     4,   403,
     450,   450,   418,   171,     4,     3,   418,   445,     6,   425,
       4,   415,   450,   425,   418,     4,   470,    48,     4,     4,
     146,   425,   148,   149,   415,     8,     3,   418,     4,   171,
       4,   435,   470,     8,   425,    66,    67,   109,   110,   111,
       3,   445,   171,     4,   435,   171,   450,     4,     4,    40,
      41,    42,    43,    84,     4,    46,     4,    48,    49,    90,
      91,    92,    93,    94,    95,     4,   470,   171,     4,     4,
       4,     4,     4,     4,     4,    66,    67,     4,    69,    70,
       4,    72,    73,     4,   172,   172,     4,   172,     4,     4,
     172,   172,     4,     4,    85,     4,     4,    88,     4,     4,
       4,     4,     4,     4,     4,    96,     4,     4,     4,   483,
     484,   485,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,     4,     4,     4,
       4,   585,   172,   174,     4,     4,     4,   591,     4,     4,
     171,    66,    67,   172,     4,     4,   174,     4,     4,     4,
       4,   172,     4,   591,     4,   172,   172,     4,     4,     4,
       4,     4,   616,   617,     4,   619,     4,   172,     4,     4,
       4,   174,     4,   174,     4,   174,     4,   174,   616,   617,
     171,   619,     4,     4,   172,     4,     4,   591,   562,     4,
     172,   172,     4,     4,   174,   174,     4,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     584,     4,   616,   617,     4,   619,     4,   142,   143,     4,
       7,     7,   171,     7,     7,     7,     7,     5,     5,     5,
       5,   171,     5,     7,     5,     5,     5,     3,     5,     7,
       5,     5,   171,   171,     7,     7,   171,     7,     7,     5,
       5,     5,   171,     4,   171,     7,   137,   171,   171,     5,
       5,   171,     5,     7,   171,     7,     7,     7,     7,    83,
       7,     7,   171,     7,     7,     7,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
       7,   171,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   174,     3,     6,     6,     3,     6,     6,     3,
       6,     3,   174,     6,     3,     6,     6,     3,   171,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,   171,
       6,     3,     6,     4,     3,     8,     6,     4,     4,     4,
       4,   172,     4,   172,     4,   172,   172,   172,   172,   172,
       4,     4,     4,     4,   174,   172,   172,     6,     4,   172,
       8,     8,   172,   172,     4,   172,   172,   172,   172,   172,
     171,   171,   171,   171,   171,     8,     3,     8,     4,   171,
     171,     4,   171,     4,     4,     7,     4,     4,     4,   843,
       4,   171,   846,   849,   516,   849,   846,   366,   852,   849,
     849,   843,   852,   843,   609,   843,   399,   585,   846,   863,
     852,   849,   866,   863,   852,   869,   174,   843,   843,   172,
     843,   843,   171,   171,   171,   863,   852,   852,   866,   852,
     852,   885,   591,   403,   172,   889,   852,   172,   665,   843,
     852,   895,   846,   174,   898,   849,   171,   885,   852,   903,
     842,   889,   843,   903,   837,   861,   855,   895,   858,   863,
     898,   852,   866,   871,   869,   903,   453,   878,   845,   415,
     843,  1025,   863,   854,    81,   866,   848,   445,   846,   895,
     851,   885,   898,   895,   849,   889,   898,   897,   450,   898,
     868,   895,   895,   900,   898,   418,   866,   435,   864,   903,
    1031,   885,   889,   425,   895,   470,   629,   898,   586,   476,
     619,   590,  1048,   473,  1065,   904,  1082,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1025,    -1,    -1,    -1,  1025,    -1,  1031,    -1,    -1,
      -1,  1031,    -1,  1025,    -1,    -1,    -1,  1025,    -1,    -1,
      -1,    -1,    -1,  1031,  1048,    -1,    -1,    -1,  1048,  1025,
    1025,    -1,  1025,  1025,    -1,    -1,    -1,    -1,    -1,  1025,
    1048,    -1,    -1,  1025,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1025,    -1,    -1,    -1,    -1,    -1,  1031,    -1,    -1,
      -1,    -1,    -1,    -1,  1025,    -1,    -1,    -1,    -1,    -1,
    1031,    -1,    -1,    -1,  1048
  };

  const unsigned short
  Dhcp6Parser::yystos_[] =
  {
       0,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,     0,     5,     7,     9,   171,   172,   173,   174,
     192,   193,   194,   199,     7,   208,     7,   214,     7,   227,
       7,   322,     7,   399,     7,   415,     7,   432,     7,   351,
       7,   357,     7,   381,     7,   298,     7,   493,     7,   539,
       7,   531,   200,   195,   209,   215,   228,   323,   400,   416,
     433,   352,   358,   382,   299,   494,   540,   532,   192,   201,
     202,   171,   197,   198,    10,   144,   153,   154,   155,   171,
     207,   210,   211,   212,   523,   525,   527,   537,    11,    13,
      16,    17,    18,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    66,    67,    73,    78,    79,    80,    81,    82,
      84,    89,    98,   101,   108,   116,   117,   120,   121,   207,
     216,   217,   218,   219,   220,   221,   222,   223,   225,   234,
     236,   238,   272,   278,   284,   290,   292,   306,   316,   336,
     341,   349,   375,   405,   407,   426,   456,   468,   480,   481,
     489,   491,   529,    14,    15,   207,   229,   230,   231,   233,
     405,   407,    58,    60,    68,    69,    70,    71,    72,    85,
      88,    96,   207,   218,   219,   220,   221,   324,   325,   326,
     328,   330,   332,   334,   336,   339,   340,   375,   393,   405,
     407,   409,   426,   451,    59,   207,   332,   334,   375,   401,
     402,   403,   405,   407,    61,    62,    63,    64,    65,   207,
     332,   334,   375,   405,   407,   417,   418,   419,   421,   422,
     424,   425,    84,    90,    91,    92,    93,    94,    95,   207,
     375,   405,   407,   434,   435,   436,   437,   439,   441,   443,
     445,   447,   449,   349,    19,    49,    51,    52,    55,    56,
      57,   207,   256,   359,   360,   361,   362,   363,   364,   365,
     367,   369,   371,   372,   374,   405,   407,    50,    53,    54,
     207,   256,   363,   369,   383,   384,   385,   386,   387,   389,
     390,   391,   392,   405,   407,    99,   100,   207,   300,   301,
     302,   304,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   142,   143,   207,   405,   407,
     495,   496,   497,   498,   500,   502,   503,   505,   506,   507,
     510,   512,   513,   514,   517,   519,   521,   145,   541,   542,
     543,    12,   533,   534,   535,     6,     3,     4,     8,     3,
     213,   538,   524,   526,   528,     4,     3,     8,   530,   226,
     235,   237,   239,     4,     4,     4,     4,     4,   224,   317,
     350,   376,   406,   408,   337,   342,   279,   291,   285,   273,
     457,   427,   293,   307,   469,     4,   482,   490,   492,     3,
       8,   232,     4,     3,     8,   394,   410,   327,   329,   331,
       4,     4,   335,   333,   452,     3,     8,   404,     3,     8,
     420,     4,   423,     4,     4,     3,     8,   450,   438,   440,
     442,   444,   446,   448,     8,     3,     8,   366,   257,     4,
     370,   368,   373,     4,     8,     3,   388,     4,     4,     8,
       3,   303,   305,     3,     8,     4,   499,   501,     4,   504,
       4,     4,   508,   511,     4,     4,   515,   518,   520,   522,
       3,     8,   544,     3,     8,   536,     3,     8,   192,   192,
     171,     4,     4,     4,     4,     4,   211,     4,     4,     4,
       4,     4,   172,   172,   172,   172,   172,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   172,     4,     4,     4,   217,     4,
     174,   230,     4,     4,     4,     4,     4,   172,   174,     4,
       4,     4,   325,     4,   402,     4,   172,     4,   172,   172,
     418,     4,     4,     4,     4,     4,     4,     4,   436,     4,
       4,   172,     4,     4,     4,   174,   361,     4,   174,   174,
     385,     4,     4,   301,   174,     4,     4,   172,     4,   172,
     172,     4,     4,   174,   174,     4,     4,     4,     4,   496,
       4,   542,     4,   534,     4,     7,     7,   192,   192,   192,
       7,     7,     7,     7,     5,   171,     5,     5,     5,   194,
     196,   171,    74,    75,    76,    77,   338,     5,     5,     5,
       5,     7,     5,     5,     5,     7,     7,     7,   196,     7,
       5,   203,     5,     5,   171,   171,   171,   203,   171,     7,
     171,   171,   171,   203,   203,   203,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   192,   171,   171,
     171,   135,   136,   509,   137,   138,   139,   140,   141,   174,
     516,   171,   171,   171,     5,     5,   192,   216,   541,   533,
     229,    19,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,   207,   244,
     245,   246,   249,   251,   253,   255,   256,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   268,   269,   271,   244,
       7,   240,   241,   242,     7,   318,   319,   320,     7,   353,
     354,   355,     7,   377,   378,   379,     7,   343,   344,   345,
      92,   171,   280,   281,   282,   283,   201,    93,    95,   282,
     286,   287,   288,   289,    83,   274,   275,   276,     7,   458,
     459,     7,   428,   429,   430,     7,   294,   295,   296,   102,
     103,   104,   105,   106,   107,   308,   309,   310,   311,   312,
     313,   314,   315,    19,   112,   113,   114,   115,   207,   258,
     405,   407,   470,   471,   472,   475,   476,   478,   479,   118,
     119,   207,   405,   407,   483,   484,   485,   487,   495,   204,
       7,   395,   396,   397,     7,   411,   412,   413,    97,   437,
     453,   454,     7,   545,   546,   240,     8,     8,     8,     8,
     247,   250,   252,   254,     4,     4,     4,     4,     4,   267,
       4,     4,   270,     4,     4,     4,     4,     3,     8,     8,
     243,     6,     3,   321,     6,     3,   356,     6,     3,   380,
       6,     3,   346,     6,     3,     3,     6,     6,     3,     6,
     277,     3,     8,   460,     3,     6,   431,     6,     3,   297,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
     473,   477,     4,     4,     4,     3,     8,   486,   488,     3,
       8,     8,   171,   205,   206,   398,     6,     3,   414,     6,
       3,   455,     8,   547,     3,     6,     6,     4,     4,     4,
       4,   172,   174,   172,   174,   172,     4,   172,   172,     4,
     172,   172,   174,   172,   245,   244,   242,   324,   320,   359,
     355,   383,   379,   207,   218,   219,   220,   221,   256,   316,
     328,   330,   332,   334,   336,   340,   347,   348,   375,   405,
     407,   451,   345,   281,   287,     4,   275,    86,    87,   207,
     256,   375,   405,   407,   461,   462,   463,   464,   465,   467,
     459,   434,   430,   300,   296,   172,   172,   172,   172,   172,
     172,   309,     4,     4,   172,   172,   172,   471,     4,     4,
     484,     6,     3,   401,   397,   417,   413,     4,   146,   148,
     149,   207,   256,   405,   407,   548,   549,   550,   551,   553,
     546,    20,    21,    22,    23,   248,   171,   171,   171,   171,
     171,     8,     8,     8,     8,     3,     8,   171,   466,     4,
       8,     3,     8,     8,   109,   110,   111,   474,   171,   171,
     171,   171,     8,     8,   171,   554,     4,   552,     3,     8,
     348,     4,   174,   463,     4,   172,     4,   549,   171,     5,
     171,     7,   555,   556,   557,     3,     6,   147,   150,   151,
     152,   558,   559,   560,   562,   563,   564,   556,   561,     4,
       4,     4,     3,     8,     4,   174,   172,   172,   559,   171
  };

  const unsigned short
  Dhcp6Parser::yyr1_[] =
  {
       0,   175,   177,   176,   178,   176,   179,   176,   180,   176,
     181,   176,   182,   176,   183,   176,   184,   176,   185,   176,
     186,   176,   187,   176,   188,   176,   189,   176,   190,   176,
     191,   176,   192,   192,   192,   192,   192,   192,   192,   193,
     195,   194,   196,   197,   197,   198,   198,   200,   199,   201,
     201,   202,   202,   204,   203,   205,   205,   206,   206,   207,
     209,   208,   210,   210,   211,   211,   211,   211,   211,   211,
     213,   212,   215,   214,   216,   216,   217,   217,   217,   217,
     217,   217,   217,   217,   217,   217,   217,   217,   217,   217,
     217,   217,   217,   217,   217,   217,   217,   217,   217,   217,
     217,   217,   217,   217,   217,   217,   217,   217,   218,   219,
     220,   221,   222,   224,   223,   226,   225,   228,   227,   229,
     229,   230,   230,   230,   230,   230,   232,   231,   233,   235,
     234,   237,   236,   239,   238,   240,   240,   241,   241,   243,
     242,   244,   244,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   247,   246,   248,   248,   248,   248,   250,   249,
     252,   251,   254,   253,   255,   257,   256,   258,   259,   260,
     261,   262,   263,   264,   265,   267,   266,   268,   270,   269,
     271,   273,   272,   274,   274,   275,   277,   276,   279,   278,
     280,   280,   281,   281,   282,   283,   285,   284,   286,   286,
     287,   287,   287,   288,   289,   291,   290,   293,   292,   294,
     294,   295,   295,   297,   296,   299,   298,   300,   300,   300,
     301,   301,   303,   302,   305,   304,   307,   306,   308,   308,
     309,   309,   309,   309,   309,   309,   310,   311,   312,   313,
     314,   315,   317,   316,   318,   318,   319,   319,   321,   320,
     323,   322,   324,   324,   325,   325,   325,   325,   325,   325,
     325,   325,   325,   325,   325,   325,   325,   325,   325,   325,
     325,   325,   325,   325,   327,   326,   329,   328,   331,   330,
     333,   332,   335,   334,   337,   336,   338,   338,   338,   338,
     339,   340,   342,   341,   343,   343,   344,   344,   346,   345,
     347,   347,   348,   348,   348,   348,   348,   348,   348,   348,
     348,   348,   348,   348,   348,   348,   348,   348,   348,   350,
     349,   352,   351,   353,   353,   354,   354,   356,   355,   358,
     357,   359,   359,   360,   360,   361,   361,   361,   361,   361,
     361,   361,   361,   361,   361,   362,   363,   364,   366,   365,
     368,   367,   370,   369,   371,   373,   372,   374,   376,   375,
     377,   377,   378,   378,   380,   379,   382,   381,   383,   383,
     384,   384,   385,   385,   385,   385,   385,   385,   385,   385,
     385,   386,   388,   387,   389,   390,   391,   392,   394,   393,
     395,   395,   396,   396,   398,   397,   400,   399,   401,   401,
     402,   402,   402,   402,   402,   402,   402,   404,   403,   406,
     405,   408,   407,   410,   409,   411,   411,   412,   412,   414,
     413,   416,   415,   417,   417,   418,   418,   418,   418,   418,
     418,   418,   418,   418,   418,   418,   420,   419,   421,   423,
     422,   424,   425,   427,   426,   428,   428,   429,   429,   431,
     430,   433,   432,   434,   434,   435,   435,   436,   436,   436,
     436,   436,   436,   436,   436,   436,   436,   436,   438,   437,
     440,   439,   442,   441,   444,   443,   446,   445,   448,   447,
     450,   449,   452,   451,   453,   453,   455,   454,   457,   456,
     458,   458,   460,   459,   461,   461,   462,   462,   463,   463,
     463,   463,   463,   463,   463,   464,   466,   465,   467,   469,
     468,   470,   470,   471,   471,   471,   471,   471,   471,   471,
     471,   471,   473,   472,   474,   474,   474,   475,   477,   476,
     478,   479,   480,   482,   481,   483,   483,   484,   484,   484,
     484,   484,   486,   485,   488,   487,   490,   489,   492,   491,
     494,   493,   495,   495,   496,   496,   496,   496,   496,   496,
     496,   496,   496,   496,   496,   496,   496,   496,   496,   496,
     496,   496,   497,   499,   498,   501,   500,   502,   504,   503,
     505,   506,   508,   507,   509,   509,   511,   510,   512,   513,
     515,   514,   516,   516,   516,   516,   516,   518,   517,   520,
     519,   522,   521,   524,   523,   526,   525,   528,   527,   530,
     529,   532,   531,   533,   533,   534,   536,   535,   538,   537,
     540,   539,   541,   541,   542,   544,   543,   545,   545,   547,
     546,   548,   548,   549,   549,   549,   549,   549,   549,   549,
     550,   552,   551,   554,   553,   555,   555,   557,   556,   558,
     558,   559,   559,   559,   559,   561,   560,   562,   563,   564
  };

  const unsigned char
  Dhcp6Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     0,     1,     3,     5,     0,     4,     0,
       1,     1,     3,     0,     4,     0,     1,     1,     3,     2,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       0,     6,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       6,     0,     6,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     3,     0,     4,
       3,     0,     6,     1,     3,     1,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     0,     6,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     1,     1,     1,     1,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       6,     0,     4,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     0,     4,
       0,     4,     0,     4,     1,     0,     4,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       4,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     1,     1,     0,     4,     0,     6,
       1,     3,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     3,     0,     4,
       3,     3,     3,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     0,     4,     1,     1,     0,     4,     3,     3,
       0,     4,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     1,     3,     1,     0,     6,     0,     6,
       0,     4,     1,     3,     1,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     0,     4,     3,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp6Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"", "\"config-control\"",
  "\"config-databases\"", "\"interfaces-config\"", "\"interfaces\"",
  "\"re-detect\"", "\"lease-database\"", "\"hosts-database\"",
  "\"hosts-databases\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"", "\"host\"",
  "\"port\"", "\"persist\"", "\"lfc-interval\"", "\"readonly\"",
  "\"connect-timeout\"", "\"contact-points\"", "\"max-reconnect-tries\"",
  "\"reconnect-wait-time\"", "\"keyspace\"", "\"request-timeout\"",
  "\"tcp-keepalive\"", "\"tcp-nodelay\"", "\"max-row-errors\"",
  "\"preferred-lifetime\"", "\"valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"decline-probation-period\"", "\"server-tag\"",
  "\"subnet6\"", "\"option-def\"", "\"option-data\"", "\"name\"",
  "\"data\"", "\"code\"", "\"space\"", "\"csv-format\"", "\"always-send\"",
  "\"record-types\"", "\"encapsulate\"", "\"array\"", "\"pools\"",
  "\"pool\"", "\"pd-pools\"", "\"prefix\"", "\"prefix-len\"",
  "\"excluded-prefix\"", "\"excluded-prefix-len\"", "\"delegated-len\"",
  "\"user-context\"", "\"comment\"", "\"subnet\"", "\"interface\"",
  "\"interface-id\"", "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"",
  "\"disabled\"", "\"out-of-pool\"", "\"global\"", "\"all\"",
  "\"shared-networks\"", "\"mac-sources\"", "\"relay-supplied-options\"",
  "\"host-reservation-identifiers\"", "\"sanity-checks\"",
  "\"lease-checks\"", "\"client-classes\"", "\"require-client-classes\"",
  "\"test\"", "\"only-if-required\"", "\"client-class\"",
  "\"reservations\"", "\"ip-addresses\"", "\"prefixes\"", "\"duid\"",
  "\"hw-address\"", "\"hostname\"", "\"flex-id\"", "\"relay\"",
  "\"ip-address\"", "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
  "\"expired-leases-processing\"", "\"reclaim-timer-wait-time\"",
  "\"flush-reclaimed-timer-wait-time\"", "\"hold-reclaimed-time\"",
  "\"max-reclaim-leases\"", "\"max-reclaim-time\"",
  "\"unwarned-reclaim-cycles\"", "\"server-id\"", "\"LLT\"", "\"EN\"",
  "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"", "\"enterprise-id\"",
  "\"dhcp4o6-port\"", "\"control-socket\"", "\"socket-type\"",
  "\"socket-name\"", "\"dhcp-queue-control\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"UDP\"", "\"TCP\"",
  "\"JSON\"", "\"when-present\"", "\"never\"", "\"always\"",
  "\"when-not-present\"", "\"hostname-char-set\"",
  "\"hostname-char-replacement\"", "\"Logging\"", "\"loggers\"",
  "\"output_options\"", "\"output\"", "\"debuglevel\"", "\"severity\"",
  "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"Dhcp4\"", "\"DhcpDdns\"",
  "\"Control-agent\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP6", "SUB_DHCP6",
  "SUB_INTERFACES6", "SUB_SUBNET6", "SUB_POOL6", "SUB_PD_POOL",
  "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "SUB_LOGGING",
  "SUB_CONFIG_CONTROL", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "$@14", "$@15", "value", "sub_json", "map2", "$@16", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@17", "list_content",
  "not_empty_list", "list_strings", "$@18", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@19",
  "global_objects", "global_object", "dhcp6_object", "$@20", "sub_dhcp6",
  "$@21", "global_params", "global_param", "preferred_lifetime",
  "valid_lifetime", "renew_timer", "rebind_timer",
  "decline_probation_period", "server_tag", "$@22", "interfaces_config",
  "$@23", "sub_interfaces6", "$@24", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@25", "re_detect",
  "lease_database", "$@26", "hosts_database", "$@27", "hosts_databases",
  "$@28", "database_list", "not_empty_database_list", "database", "$@29",
  "database_map_params", "database_map_param", "database_type", "$@30",
  "db_type", "user", "$@31", "password", "$@32", "host", "$@33", "port",
  "name", "$@34", "persist", "lfc_interval", "readonly", "connect_timeout",
  "reconnect_wait_time", "request_timeout", "tcp_keepalive", "tcp_nodelay",
  "contact_points", "$@35", "max_reconnect_tries", "keyspace", "$@36",
  "max_row_errors", "sanity_checks", "$@37", "sanity_checks_params",
  "sanity_checks_param", "lease_checks", "$@38", "mac_sources", "$@39",
  "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@40",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@41",
  "hooks_libraries", "$@42", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@43",
  "sub_hooks_library", "$@44", "hooks_params", "hooks_param", "library",
  "$@45", "parameters", "$@46", "expired_leases_processing", "$@47",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@48",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@49",
  "sub_subnet6", "$@50", "subnet6_params", "subnet6_param", "subnet",
  "$@51", "interface", "$@52", "interface_id", "$@53", "client_class",
  "$@54", "require_client_classes", "$@55", "reservation_mode", "$@56",
  "hr_mode", "id", "rapid_commit", "shared_networks", "$@57",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@58", "shared_network_params", "shared_network_param",
  "option_def_list", "$@59", "sub_option_def_list", "$@60",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@61", "sub_option_def", "$@62",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@63",
  "option_def_record_types", "$@64", "space", "$@65", "option_def_space",
  "option_def_encapsulate", "$@66", "option_def_array", "option_data_list",
  "$@67", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@68", "sub_option_data", "$@69",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@70",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@71", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@72", "sub_pool6", "$@73",
  "pool_params", "pool_param", "pool_entry", "$@74", "user_context",
  "$@75", "comment", "$@76", "pd_pools_list", "$@77",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@78", "sub_pd_pool", "$@79", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@80", "pd_prefix_len", "excluded_prefix", "$@81",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@82",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@83", "sub_reservation", "$@84", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@85", "prefixes", "$@86", "duid", "$@87", "hw_address", "$@88",
  "hostname", "$@89", "flex_id_value", "$@90",
  "reservation_client_classes", "$@91", "relay", "$@92", "relay_map",
  "ip_address", "$@93", "client_classes", "$@94", "client_classes_list",
  "client_class_entry", "$@95", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@96", "only_if_required",
  "server_id", "$@97", "server_id_params", "server_id_param",
  "server_id_type", "$@98", "duid_type", "htype", "identifier", "$@99",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@100",
  "control_socket_params", "control_socket_param", "socket_type", "$@101",
  "socket_name", "$@102", "dhcp_queue_control", "$@103", "dhcp_ddns",
  "$@104", "sub_dhcp_ddns", "$@105", "dhcp_ddns_params", "dhcp_ddns_param",
  "enable_updates", "qualifying_suffix", "$@106", "server_ip", "$@107",
  "server_port", "sender_ip", "$@108", "sender_port", "max_queue_size",
  "ncr_protocol", "$@109", "ncr_protocol_value", "ncr_format", "$@110",
  "override_no_update", "override_client_update", "replace_client_name",
  "$@111", "replace_client_name_value", "generated_prefix", "$@112",
  "hostname_char_set", "$@113", "hostname_char_replacement", "$@114",
  "dhcp4_json_object", "$@115", "dhcpddns_json_object", "$@116",
  "control_agent_json_object", "$@117", "config_control", "$@118",
  "sub_config_control", "$@119", "config_control_params",
  "config_control_param", "config_databases", "$@120", "logging_object",
  "$@121", "sub_logging", "$@122", "logging_params", "logging_param",
  "loggers", "$@123", "loggers_entries", "logger_entry", "$@124",
  "logger_params", "logger_param", "debuglevel", "severity", "$@125",
  "output_options_list", "$@126", "output_options_list_content",
  "output_entry", "$@127", "output_params_list", "output_params", "output",
  "$@128", "flush", "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short
  Dhcp6Parser::yyrline_[] =
  {
       0,   258,   258,   258,   259,   259,   260,   260,   261,   261,
     262,   262,   263,   263,   264,   264,   265,   265,   266,   266,
     267,   267,   268,   268,   269,   269,   270,   270,   271,   271,
     272,   272,   280,   281,   282,   283,   284,   285,   286,   289,
     294,   294,   305,   308,   309,   312,   316,   323,   323,   330,
     331,   334,   338,   345,   345,   352,   353,   356,   360,   371,
     381,   381,   396,   397,   401,   402,   403,   404,   405,   406,
     409,   409,   424,   424,   433,   434,   439,   440,   441,   442,
     443,   444,   445,   446,   447,   448,   449,   450,   451,   452,
     453,   454,   455,   456,   457,   458,   459,   460,   461,   462,
     463,   464,   465,   466,   467,   468,   469,   470,   473,   478,
     483,   488,   493,   498,   498,   506,   506,   517,   517,   526,
     527,   530,   531,   532,   533,   534,   537,   537,   547,   553,
     553,   565,   565,   577,   577,   587,   588,   591,   592,   595,
     595,   605,   606,   609,   610,   611,   612,   613,   614,   615,
     616,   617,   618,   619,   620,   621,   622,   623,   624,   625,
     626,   627,   630,   630,   637,   638,   639,   640,   643,   643,
     651,   651,   659,   659,   667,   672,   672,   680,   685,   690,
     695,   700,   705,   710,   715,   720,   720,   728,   733,   733,
     741,   746,   746,   756,   757,   759,   761,   761,   779,   779,
     789,   790,   793,   794,   797,   802,   807,   807,   817,   818,
     821,   822,   823,   826,   831,   838,   838,   848,   848,   858,
     859,   862,   863,   866,   866,   876,   876,   886,   887,   888,
     891,   892,   895,   895,   903,   903,   911,   911,   922,   923,
     926,   927,   928,   929,   930,   931,   934,   939,   944,   949,
     954,   959,   967,   967,   980,   981,   984,   985,   992,   992,
    1018,  1018,  1029,  1030,  1034,  1035,  1036,  1037,  1038,  1039,
    1040,  1041,  1042,  1043,  1044,  1045,  1046,  1047,  1048,  1049,
    1050,  1051,  1052,  1053,  1056,  1056,  1064,  1064,  1072,  1072,
    1080,  1080,  1088,  1088,  1098,  1098,  1105,  1106,  1107,  1108,
    1111,  1116,  1124,  1124,  1135,  1136,  1140,  1141,  1144,  1144,
    1152,  1153,  1156,  1157,  1158,  1159,  1160,  1161,  1162,  1163,
    1164,  1165,  1166,  1167,  1168,  1169,  1170,  1171,  1172,  1179,
    1179,  1192,  1192,  1201,  1202,  1205,  1206,  1211,  1211,  1226,
    1226,  1240,  1241,  1244,  1245,  1248,  1249,  1250,  1251,  1252,
    1253,  1254,  1255,  1256,  1257,  1260,  1262,  1267,  1269,  1269,
    1277,  1277,  1285,  1285,  1293,  1295,  1295,  1303,  1312,  1312,
    1324,  1325,  1330,  1331,  1336,  1336,  1348,  1348,  1360,  1361,
    1366,  1367,  1372,  1373,  1374,  1375,  1376,  1377,  1378,  1379,
    1380,  1383,  1385,  1385,  1393,  1395,  1397,  1402,  1410,  1410,
    1422,  1423,  1426,  1427,  1430,  1430,  1440,  1440,  1449,  1450,
    1453,  1454,  1455,  1456,  1457,  1458,  1459,  1462,  1462,  1470,
    1470,  1495,  1495,  1525,  1525,  1537,  1538,  1541,  1542,  1545,
    1545,  1557,  1557,  1569,  1570,  1573,  1574,  1575,  1576,  1577,
    1578,  1579,  1580,  1581,  1582,  1583,  1586,  1586,  1594,  1599,
    1599,  1607,  1612,  1620,  1620,  1630,  1631,  1634,  1635,  1638,
    1638,  1647,  1647,  1656,  1657,  1660,  1661,  1665,  1666,  1667,
    1668,  1669,  1670,  1671,  1672,  1673,  1674,  1675,  1678,  1678,
    1688,  1688,  1698,  1698,  1706,  1706,  1714,  1714,  1722,  1722,
    1730,  1730,  1743,  1743,  1753,  1754,  1757,  1757,  1768,  1768,
    1778,  1779,  1782,  1782,  1792,  1793,  1796,  1797,  1800,  1801,
    1802,  1803,  1804,  1805,  1806,  1809,  1811,  1811,  1819,  1827,
    1827,  1839,  1840,  1843,  1844,  1845,  1846,  1847,  1848,  1849,
    1850,  1851,  1854,  1854,  1861,  1862,  1863,  1866,  1871,  1871,
    1879,  1884,  1891,  1898,  1898,  1908,  1909,  1912,  1913,  1914,
    1915,  1916,  1919,  1919,  1927,  1927,  1937,  1937,  1977,  1977,
    1989,  1989,  1999,  2000,  2003,  2004,  2005,  2006,  2007,  2008,
    2009,  2010,  2011,  2012,  2013,  2014,  2015,  2016,  2017,  2018,
    2019,  2020,  2023,  2028,  2028,  2036,  2036,  2044,  2049,  2049,
    2057,  2062,  2067,  2067,  2075,  2076,  2079,  2079,  2087,  2092,
    2097,  2097,  2105,  2108,  2111,  2114,  2117,  2123,  2123,  2131,
    2131,  2139,  2139,  2149,  2149,  2156,  2156,  2163,  2163,  2172,
    2172,  2183,  2183,  2193,  2194,  2198,  2201,  2201,  2216,  2216,
    2226,  2226,  2237,  2238,  2242,  2246,  2246,  2258,  2259,  2263,
    2263,  2271,  2272,  2275,  2276,  2277,  2278,  2279,  2280,  2281,
    2284,  2289,  2289,  2297,  2297,  2307,  2308,  2311,  2311,  2319,
    2320,  2323,  2324,  2325,  2326,  2329,  2329,  2337,  2342,  2347
  };

  // Print the state stack on the debug stream.
  void
  Dhcp6Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Dhcp6Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // PARSER6_DEBUG


#line 14 "dhcp6_parser.yy" // lalr1.cc:1218
} } // isc::dhcp
#line 5066 "dhcp6_parser.cc" // lalr1.cc:1218
#line 2352 "dhcp6_parser.yy" // lalr1.cc:1219


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
