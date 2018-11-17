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
      case 337: // hr_mode
      case 473: // duid_type
      case 508: // ncr_protocol_value
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
      case 337: // hr_mode
      case 473: // duid_type
      case 508: // ncr_protocol_value
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
      case 337: // hr_mode
      case 473: // duid_type
      case 508: // ncr_protocol_value
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

      case 337: // hr_mode

#line 249 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 447 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 473: // duid_type

#line 249 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 454 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 508: // ncr_protocol_value

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
      case 337: // hr_mode
      case 473: // duid_type
      case 508: // ncr_protocol_value
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

  case 107:
#line 472 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1064 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 108:
#line 477 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1073 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 109:
#line 482 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1082 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 110:
#line 487 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1091 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 111:
#line 492 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1100 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 112:
#line 497 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1108 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 113:
#line 499 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1118 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 114:
#line 505 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1129 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 115:
#line 510 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1139 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 116:
#line 516 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1149 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 117:
#line 520 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1158 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 125:
#line 536 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1169 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 126:
#line 541 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1178 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 127:
#line 546 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1187 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 128:
#line 552 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1198 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 129:
#line 557 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1209 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 130:
#line 564 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1220 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 131:
#line 569 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1231 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 132:
#line 576 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1242 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 133:
#line 581 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1251 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 138:
#line 594 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1261 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 139:
#line 598 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1271 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 160:
#line 628 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1279 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 161:
#line 630 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1288 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 162:
#line 635 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1294 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 163:
#line 636 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1300 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 164:
#line 637 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1306 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 165:
#line 638 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1312 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 166:
#line 641 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1320 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 167:
#line 643 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1330 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 168:
#line 649 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1338 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 169:
#line 651 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1348 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 170:
#line 657 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1356 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 171:
#line 659 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1366 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 172:
#line 665 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1375 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 173:
#line 670 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1383 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 174:
#line 672 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1393 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 175:
#line 678 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1402 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 176:
#line 683 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1411 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 177:
#line 688 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1420 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 178:
#line 693 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1429 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 179:
#line 698 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1438 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 180:
#line 703 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1447 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 181:
#line 708 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1456 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 182:
#line 713 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1465 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 183:
#line 718 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1473 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 184:
#line 720 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1483 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 185:
#line 726 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1492 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 186:
#line 731 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1500 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 187:
#line 733 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1510 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 188:
#line 739 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1521 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 189:
#line 744 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1530 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 193:
#line 754 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1538 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 194:
#line 756 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 1558 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 195:
#line 772 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1569 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 196:
#line 777 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1578 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 201:
#line 790 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1587 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 202:
#line 795 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1596 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 203:
#line 800 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1607 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 204:
#line 805 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1616 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 210:
#line 819 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1625 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 211:
#line 824 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1634 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 212:
#line 831 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1645 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 213:
#line 836 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1654 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 214:
#line 841 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1665 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 215:
#line 846 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1674 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 220:
#line 859 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1684 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 221:
#line 863 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1694 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 222:
#line 869 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1704 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 223:
#line 873 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1714 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 229:
#line 888 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1722 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 230:
#line 890 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1732 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 231:
#line 896 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1740 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 232:
#line 898 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1749 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 233:
#line 904 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1760 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 234:
#line 909 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1770 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 243:
#line 927 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1779 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 244:
#line 932 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1788 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 245:
#line 937 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1797 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 246:
#line 942 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1806 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 247:
#line 947 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1815 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 248:
#line 952 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1824 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 249:
#line 960 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1835 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 250:
#line 965 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1844 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 255:
#line 985 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1854 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 256:
#line 989 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 1880 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 257:
#line 1011 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1890 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 258:
#line 1015 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1900 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 281:
#line 1049 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1908 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 282:
#line 1051 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1918 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 283:
#line 1057 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1926 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 284:
#line 1059 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1936 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 285:
#line 1065 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1944 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 286:
#line 1067 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1954 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 287:
#line 1073 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1962 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 288:
#line 1075 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1972 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 289:
#line 1081 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1983 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 290:
#line 1086 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1992 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 291:
#line 1091 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2000 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 292:
#line 1093 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2009 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 293:
#line 1098 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2015 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 294:
#line 1099 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2021 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 295:
#line 1100 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2027 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 296:
#line 1101 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2033 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 297:
#line 1104 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2042 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 298:
#line 1109 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2051 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 299:
#line 1117 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2062 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 300:
#line 1122 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2071 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 305:
#line 1137 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2081 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 306:
#line 1141 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 2089 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 326:
#line 1172 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2100 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 327:
#line 1177 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2109 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 328:
#line 1185 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2118 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 329:
#line 1188 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // parsing completed
}
#line 2126 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 334:
#line 1204 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2136 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 335:
#line 1208 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2148 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 336:
#line 1219 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2158 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 337:
#line 1223 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2170 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 353:
#line 1255 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2179 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 355:
#line 1262 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2187 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 356:
#line 1264 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2197 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 357:
#line 1270 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2205 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 358:
#line 1272 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2215 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 359:
#line 1278 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2223 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 360:
#line 1280 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2233 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 362:
#line 1288 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2241 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 363:
#line 1290 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2251 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 364:
#line 1296 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2260 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 365:
#line 1305 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2271 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 366:
#line 1310 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2280 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 371:
#line 1329 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2290 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 372:
#line 1333 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2299 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 373:
#line 1341 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2309 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 374:
#line 1345 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2318 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 389:
#line 1378 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2326 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 390:
#line 1380 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2336 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 393:
#line 1390 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2345 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 394:
#line 1395 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2354 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 395:
#line 1403 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2365 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 396:
#line 1408 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2374 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 401:
#line 1423 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2384 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 402:
#line 1427 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2394 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 403:
#line 1433 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2404 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 404:
#line 1437 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2413 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 414:
#line 1455 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2421 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 415:
#line 1457 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2431 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 416:
#line 1463 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2439 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 417:
#line 1465 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 2466 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 418:
#line 1488 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2474 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 419:
#line 1490 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 2503 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 420:
#line 1518 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2514 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 421:
#line 1523 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2523 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 426:
#line 1538 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2533 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 427:
#line 1542 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2545 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 428:
#line 1550 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2555 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 429:
#line 1554 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2567 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 443:
#line 1579 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2575 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 444:
#line 1581 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2585 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 445:
#line 1587 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2594 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 446:
#line 1592 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2602 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 447:
#line 1594 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2612 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 448:
#line 1600 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2621 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 449:
#line 1605 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2630 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 450:
#line 1613 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2641 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 451:
#line 1618 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2650 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 456:
#line 1631 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2660 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 457:
#line 1635 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2669 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 458:
#line 1640 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2679 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 459:
#line 1644 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2688 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 475:
#line 1671 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2699 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 476:
#line 1676 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2708 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 477:
#line 1681 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2719 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 478:
#line 1686 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2728 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 479:
#line 1691 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2736 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 480:
#line 1693 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2746 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 481:
#line 1699 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2754 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 482:
#line 1701 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2764 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 483:
#line 1707 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2772 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 484:
#line 1709 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2782 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 485:
#line 1715 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2790 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 486:
#line 1717 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2800 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 487:
#line 1723 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2811 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 488:
#line 1728 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2820 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 489:
#line 1736 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2831 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 490:
#line 1741 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2840 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 493:
#line 1750 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2848 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 494:
#line 1752 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2858 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 495:
#line 1761 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2869 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 496:
#line 1766 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2878 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 499:
#line 1775 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2888 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 500:
#line 1779 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2898 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 513:
#line 1804 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2906 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 514:
#line 1806 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2916 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 515:
#line 1812 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2925 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 516:
#line 1820 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2936 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 517:
#line 1825 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2947 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 529:
#line 1847 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2955 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 530:
#line 1849 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2964 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 531:
#line 1854 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2970 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 532:
#line 1855 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2976 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 533:
#line 1856 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2982 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 534:
#line 1859 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2991 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 535:
#line 1864 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2999 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 536:
#line 1866 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3009 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 537:
#line 1872 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3018 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 538:
#line 1877 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3027 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 539:
#line 1884 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3036 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 540:
#line 1891 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3047 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 541:
#line 1896 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3056 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 549:
#line 1912 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3064 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 550:
#line 1914 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3074 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 551:
#line 1920 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3082 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 552:
#line 1922 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3092 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 553:
#line 1930 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3100 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 554:
#line 1932 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr qc = yystack_[0].value.as< ElementPtr > ();
    ctx.stack_.back()->set("dhcp-queue-control", qc);

    if (!qc->contains("queue-type")) {
        std::stringstream msg;
        msg << "'queue-type' is required: ";
        msg  << qc->getPosition().str() << ")";
        error(yystack_[3].location, msg.str());
    }

    ctx.leave();
}
#line 3118 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 555:
#line 1948 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3129 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 556:
#line 1953 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3140 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 557:
#line 1960 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3150 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 558:
#line 1964 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3160 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 580:
#line 1995 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3169 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 581:
#line 2000 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3177 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 582:
#line 2002 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3187 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 583:
#line 2008 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3195 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 584:
#line 2010 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3205 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 585:
#line 2016 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3214 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 586:
#line 2021 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3222 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 587:
#line 2023 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3232 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 588:
#line 2029 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3241 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 589:
#line 2034 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3250 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 590:
#line 2039 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3258 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 591:
#line 2041 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3267 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 592:
#line 2047 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3273 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 593:
#line 2048 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3279 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 594:
#line 2051 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3287 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 595:
#line 2053 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3297 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 596:
#line 2059 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3306 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 597:
#line 2064 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3315 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 598:
#line 2069 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3324 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 599:
#line 2074 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3332 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 600:
#line 2076 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3341 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 601:
#line 2082 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3349 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 602:
#line 2085 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3357 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 603:
#line 2088 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3365 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 604:
#line 2091 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3373 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 605:
#line 2094 "dhcp6_parser.yy" // lalr1.cc:907
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3382 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 606:
#line 2100 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3390 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 607:
#line 2102 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3400 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 608:
#line 2108 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3408 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 609:
#line 2110 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3418 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 610:
#line 2116 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3426 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 611:
#line 2118 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3436 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 612:
#line 2126 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3444 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 613:
#line 2128 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3453 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 614:
#line 2133 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3461 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 615:
#line 2135 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3470 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 616:
#line 2140 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3478 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 617:
#line 2142 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3487 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 618:
#line 2149 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3497 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 619:
#line 2153 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3505 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 620:
#line 2158 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3516 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 621:
#line 2163 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3526 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 622:
#line 2169 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3536 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 623:
#line 2173 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No config_control params are required
    // parsing completed
}
#line 3545 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 628:
#line 2188 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3556 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 629:
#line 2193 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3565 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 630:
#line 2203 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3576 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 631:
#line 2208 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3585 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 632:
#line 2213 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3595 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 633:
#line 2217 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // parsing completed
}
#line 3603 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 637:
#line 2233 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3614 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 638:
#line 2238 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3623 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 641:
#line 2250 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3633 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 642:
#line 2254 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3641 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 652:
#line 2271 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3650 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 653:
#line 2276 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3658 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 654:
#line 2278 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3668 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 655:
#line 2284 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3679 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 656:
#line 2289 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3688 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 659:
#line 2298 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3698 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 660:
#line 2302 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3706 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 667:
#line 2316 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3714 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 668:
#line 2318 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3724 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 669:
#line 2324 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3733 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 670:
#line 2329 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3742 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 671:
#line 2334 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3751 "dhcp6_parser.cc" // lalr1.cc:907
    break;


#line 3755 "dhcp6_parser.cc" // lalr1.cc:907
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
     321,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,    51,    52,    47,    53,
      70,    80,    84,    91,   104,   108,   122,   124,   128,   141,
     172,   180,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,    52,  -107,    42,    62,    48,   231,    89,   371,
      27,   148,    34,   151,   -27,   464,    64,    43,  -824,   205,
     228,   281,   300,   311,  -824,  -824,  -824,  -824,  -824,   319,
    -824,    78,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,   320,   323,   335,   336,   339,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,   346,  -824,  -824,  -824,  -824,
     129,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,   347,  -824,   157,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,   358,   362,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,   160,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,   177,
    -824,  -824,  -824,  -824,  -824,   366,  -824,   367,   372,  -824,
    -824,  -824,  -824,  -824,  -824,   224,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,   309,   375,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,   377,  -824,  -824,   379,  -824,  -824,  -824,
     382,  -824,  -824,   383,   390,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,   392,   394,
    -824,  -824,  -824,  -824,   386,   397,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,   226,  -824,
    -824,  -824,   401,  -824,  -824,   402,  -824,   405,   407,  -824,
    -824,   411,   412,   415,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,   266,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
     272,  -824,  -824,  -824,  -824,   273,  -824,  -824,  -824,    52,
      52,  -824,   253,   426,   444,   447,   450,   452,  -824,    42,
    -824,    43,   453,   457,   459,   460,   462,   295,   322,   324,
     325,   329,   468,   469,   470,   471,   488,   489,   491,   494,
     495,   496,   501,   502,   503,   504,   505,   506,   340,   507,
     509,   510,    62,  -824,   511,   342,    48,  -824,   513,   515,
     516,   517,   518,   352,   349,   524,   527,   528,   529,   231,
    -824,   530,    89,  -824,   531,   364,   534,   369,   378,   371,
    -824,   535,   536,   539,   540,   543,   547,   549,  -824,    27,
    -824,   550,   551,   384,   555,   557,   558,   389,  -824,    34,
     560,   391,   393,  -824,   151,   562,   564,   152,  -824,   399,
     567,   570,   403,   572,   406,   408,   573,   575,   409,   410,
     425,   577,   596,   597,   598,   464,  -824,   599,    64,  -824,
     600,    43,  -824,  -824,  -824,   604,   602,   603,    52,    52,
      52,  -824,   274,   605,   606,   607,   608,   611,  -824,  -824,
    -824,  -824,  -824,   440,   612,   613,   614,   615,   449,   616,
     618,   619,   620,   621,   622,   624,   625,   626,   627,  -824,
     629,   615,   630,  -824,   633,  -824,  -824,   634,   635,   455,
     461,   472,  -824,  -824,   365,   633,   473,   638,  -824,   475,
    -824,   476,  -824,   477,  -824,  -824,  -824,   633,   633,   633,
     478,   479,   480,   481,  -824,   482,   483,  -824,   484,   485,
     486,  -824,  -824,   487,  -824,  -824,  -824,   490,    52,  -824,
    -824,   492,   493,  -824,   497,  -824,  -824,   158,   522,  -824,
    -824,  -824,   -44,   498,   499,   500,  -824,   636,  -824,   637,
    -824,    52,    62,    64,  -824,  -824,  -824,  -824,    43,    48,
     211,   211,   653,  -824,   655,   658,   659,  -824,  -824,  -824,
     660,   -33,    52,   368,   590,   666,   667,   668,    87,   142,
      57,  -824,   464,  -824,  -824,   669,   670,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,   -13,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,   671,   653,  -824,   276,   283,   284,   301,  -824,
    -824,  -824,  -824,   675,   676,   677,   678,   679,  -824,   680,
     681,  -824,   682,   683,   684,  -824,   302,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,   303,  -824,   685,   628,  -824,
    -824,   686,   687,  -824,  -824,   688,   690,  -824,  -824,   689,
     693,  -824,  -824,   691,   695,  -824,  -824,  -824,   143,  -824,
    -824,  -824,   694,  -824,  -824,  -824,   161,  -824,  -824,  -824,
    -824,   304,  -824,  -824,  -824,   212,  -824,  -824,   696,   698,
    -824,  -824,   697,   701,  -824,   702,   703,   704,   705,   706,
     707,   313,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,   708,   709,   710,  -824,  -824,  -824,  -824,   317,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
     326,  -824,  -824,  -824,   327,   544,  -824,   699,   713,  -824,
    -824,   711,   715,  -824,  -824,  -824,   712,  -824,  -824,   255,
    -824,   716,  -824,  -824,  -824,  -824,   717,   719,   720,   721,
     554,   525,   556,   545,   559,   723,   561,   563,   725,   565,
     566,   568,   211,  -824,  -824,   211,  -824,   653,   231,  -824,
     655,    34,  -824,   658,   151,  -824,   659,   381,  -824,   660,
     -33,  -824,  -824,   368,  -824,   726,   590,  -824,    86,   666,
    -824,    27,  -824,   667,   -27,  -824,   668,   569,   571,   574,
     576,   578,   579,    87,  -824,   728,   730,   580,   581,   582,
     142,  -824,   732,   735,    57,  -824,  -824,  -824,   734,   741,
      89,  -824,   669,   371,  -824,   670,   743,  -824,   118,   671,
    -824,  -824,   422,   584,   585,   586,  -824,  -824,  -824,  -824,
    -824,   587,  -824,  -824,   588,  -824,  -824,  -824,  -824,   328,
    -824,   330,  -824,   737,  -824,   752,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
     334,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,   591,
    -824,  -824,   745,  -824,  -824,  -824,  -824,  -824,   753,   760,
    -824,  -824,  -824,  -824,  -824,   756,  -824,   338,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,   361,   594,  -824,  -824,
    -824,  -824,   595,   601,  -824,  -824,   610,   344,  -824,   350,
    -824,   617,  -824,   763,  -824,  -824,  -824,  -824,  -824,   351,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,   381,
    -824,  -824,   765,   641,  -824,    86,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,   766,
     631,   769,   118,  -824,  -824,   646,  -824,  -824,   770,  -824,
     656,  -824,  -824,   772,  -824,  -824,   259,  -824,     6,   772,
    -824,  -824,   778,   780,   781,   360,  -824,  -824,  -824,  -824,
    -824,  -824,   787,   650,   661,   663,     6,  -824,   672,  -824,
    -824,  -824,  -824,  -824
  };

  const unsigned short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   116,     9,
     257,    11,   403,    13,   428,    15,   458,    17,   328,    19,
     336,    21,   373,    23,   222,    25,   557,    27,   632,    29,
     622,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     460,     0,   338,   375,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   630,   612,   614,   616,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   618,   620,
     114,   128,   130,   132,     0,     0,     0,     0,     0,   112,
     249,   326,   365,   416,   418,   299,   195,   212,   203,   188,
     495,   450,   214,   233,   516,     0,   540,   553,   555,   106,
       0,    74,    76,    77,    78,    79,    80,   105,    83,    84,
      85,    86,   102,    87,    89,    88,    93,    94,    81,    82,
      91,    92,   100,   101,   103,    90,    95,    96,    97,    98,
      99,   104,   125,     0,   124,     0,   118,   120,   121,   122,
     123,   395,   420,   281,   283,   285,     0,     0,   291,   289,
     287,   489,   280,   261,   262,   263,   264,     0,   259,   268,
     269,   270,   273,   274,   276,   271,   272,   265,   266,   278,
     279,   267,   275,   277,   414,   413,   409,   410,   408,     0,
     405,   407,   411,   412,   443,     0,   446,     0,     0,   442,
     436,   437,   435,   440,   441,     0,   430,   432,   433,   438,
     439,   434,   487,   475,   477,   479,   481,   483,   485,   474,
     471,   472,   473,     0,   461,   462,   466,   467,   464,   468,
     469,   470,   465,     0,   355,   173,     0,   359,   357,   362,
       0,   351,   352,     0,   339,   340,   342,   354,   343,   344,
     345,   361,   346,   347,   348,   349,   350,   389,     0,     0,
     387,   388,   391,   392,     0,   376,   377,   379,   380,   381,
     382,   383,   384,   385,   386,   229,   231,   226,     0,   224,
     227,   228,     0,   581,   583,     0,   586,     0,     0,   590,
     594,     0,     0,     0,   599,   606,   608,   610,   579,   577,
     578,     0,   559,   561,   562,   563,   564,   565,   566,   567,
     568,   569,   570,   571,   572,   573,   574,   575,   576,   637,
       0,   634,   636,   628,   627,     0,   624,   626,    48,     0,
       0,    41,     0,     0,     0,     0,     0,     0,    59,     0,
      61,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    73,     0,     0,     0,   117,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     258,     0,     0,   404,     0,     0,     0,     0,     0,     0,
     429,     0,     0,     0,     0,     0,     0,     0,   459,     0,
     329,     0,     0,     0,     0,     0,     0,     0,   337,     0,
       0,     0,     0,   374,     0,     0,     0,     0,   223,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   558,     0,     0,   633,
       0,     0,   623,    52,    45,     0,     0,     0,     0,     0,
       0,    63,     0,     0,     0,     0,     0,     0,   107,   108,
     109,   110,   111,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   539,
       0,     0,     0,    75,     0,   127,   119,     0,     0,     0,
       0,     0,   297,   298,     0,     0,     0,     0,   260,     0,
     406,     0,   445,     0,   448,   449,   431,     0,     0,     0,
       0,     0,     0,     0,   463,     0,     0,   353,     0,     0,
       0,   364,   341,     0,   393,   394,   378,     0,     0,   225,
     580,     0,     0,   585,     0,   588,   589,     0,     0,   596,
     597,   598,     0,     0,     0,     0,   560,     0,   635,     0,
     625,     0,     0,     0,   613,   615,   617,   619,     0,     0,
       0,     0,   134,   113,   251,   330,   367,    42,   417,   419,
     301,     0,    49,     0,     0,     0,   452,   216,     0,     0,
       0,   554,     0,    53,   126,   397,   422,   282,   284,   286,
     293,   294,   295,   296,   292,   290,   288,     0,   415,   444,
     447,   488,   476,   478,   480,   482,   484,   486,   356,   174,
     360,   358,   363,   390,   230,   232,   582,   584,   587,   592,
     593,   591,   595,   601,   602,   603,   604,   605,   600,   607,
     609,   611,     0,   134,    46,     0,     0,     0,     0,   160,
     166,   168,   170,     0,     0,     0,     0,     0,   183,     0,
       0,   186,     0,     0,     0,   159,     0,   140,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   154,   155,
     156,   157,   152,   153,   158,     0,   138,     0,   135,   136,
     255,     0,   252,   253,   334,     0,   331,   332,   371,     0,
     368,   369,   305,     0,   302,   303,   201,   202,     0,   197,
     199,   200,     0,   210,   211,   207,     0,   205,   208,   209,
     193,     0,   190,   192,   499,     0,   497,   456,     0,   453,
     454,   220,     0,   217,   218,     0,     0,     0,     0,     0,
       0,     0,   235,   237,   238,   239,   240,   241,   242,   529,
     535,     0,     0,     0,   528,   525,   526,   527,     0,   518,
     520,   523,   521,   522,   524,   549,   551,   548,   546,   547,
       0,   542,   544,   545,     0,    55,   401,     0,   398,   399,
     426,     0,   423,   424,   493,   492,     0,   491,   641,     0,
     639,     0,    71,   631,   621,   115,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   129,   131,     0,   133,     0,     0,   250,
       0,   338,   327,     0,   375,   366,     0,     0,   300,     0,
       0,   196,   213,     0,   204,     0,     0,   189,   501,     0,
     496,   460,   451,     0,     0,   215,     0,     0,     0,     0,
       0,     0,     0,     0,   234,     0,     0,     0,     0,     0,
       0,   517,     0,     0,     0,   541,   556,    57,     0,    56,
       0,   396,     0,     0,   421,     0,     0,   490,     0,     0,
     638,   629,     0,     0,     0,     0,   172,   175,   176,   177,
     178,     0,   185,   179,     0,   180,   181,   182,   141,     0,
     137,     0,   254,     0,   333,     0,   370,   325,   320,   322,
     313,   314,   309,   310,   311,   312,   318,   319,   317,   321,
       0,   307,   315,   323,   324,   316,   304,   198,   206,     0,
     191,   513,     0,   511,   512,   508,   509,   510,     0,   502,
     503,   505,   506,   507,   498,     0,   455,     0,   219,   243,
     244,   245,   246,   247,   248,   236,     0,     0,   534,   537,
     538,   519,     0,     0,   543,    54,     0,     0,   400,     0,
     425,     0,   655,     0,   653,   651,   645,   649,   650,     0,
     643,   647,   648,   646,   640,   162,   163,   164,   165,   161,
     167,   169,   171,   184,   187,   139,   256,   335,   372,     0,
     306,   194,     0,     0,   500,     0,   457,   221,   531,   532,
     533,   530,   536,   550,   552,    58,   402,   427,   494,     0,
       0,     0,     0,   642,   308,     0,   515,   504,     0,   652,
       0,   644,   514,     0,   654,   659,     0,   657,     0,     0,
     656,   667,     0,     0,     0,     0,   661,   663,   664,   665,
     666,   658,     0,     0,     0,     0,     0,   660,     0,   669,
     670,   671,   662,   668
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,    14,  -824,  -451,
    -824,   168,  -824,  -824,  -824,  -824,   164,  -824,  -423,  -824,
    -824,  -824,   -74,  -824,  -824,  -824,   427,  -824,  -824,  -824,
    -824,   238,   429,   -70,   -58,   -55,   -38,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,   240,   431,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,   169,  -824,     0,  -824,  -577,
       7,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,   -46,  -824,  -607,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,   -18,
    -824,  -824,  -824,  -824,  -824,    -9,  -600,  -824,  -824,  -824,
    -824,   -11,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
     -22,  -824,  -824,  -824,   -19,   400,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,   -23,  -824,  -824,  -824,  -824,  -824,  -824,
    -823,  -824,  -824,  -824,    11,  -824,  -824,  -824,    15,   445,
    -824,  -824,  -819,  -824,  -817,  -824,   -34,  -824,   -32,  -824,
    -809,  -824,  -824,  -824,  -808,  -824,  -824,  -824,  -824,     8,
    -824,  -824,  -164,   789,  -824,  -824,  -824,  -824,  -824,    19,
    -824,  -824,  -824,    22,  -824,   428,  -824,   -42,  -824,  -824,
    -824,  -824,  -824,   -40,  -824,  -824,  -824,  -824,  -824,   -12,
    -824,  -824,  -824,    18,  -824,  -824,  -824,    21,  -824,   424,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,   -26,  -824,  -824,  -824,   -21,   458,  -824,  -824,   -62,
    -824,   -50,  -824,  -824,  -824,  -824,  -824,   -24,  -824,  -824,
    -824,   -20,   456,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
     -35,  -824,  -824,  -824,     9,  -824,  -824,  -824,    13,  -824,
     448,   249,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -807,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,    20,  -824,  -824,  -824,  -145,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,     2,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,    -1,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,   275,
     419,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -346,
     414,  -824,  -824,  -824,  -824,  -824,  -824,   305,   418,  -824,
    -824,  -824,   -10,  -824,  -824,  -152,  -824,  -824,  -824,  -824,
    -824,  -824,  -168,  -824,  -824,  -184,  -824,  -824,  -824,  -824,
    -824
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   608,    92,    93,    43,    72,    89,    90,   624,   805,
     898,   899,   354,    45,    74,   101,   102,   103,   363,    47,
      75,   140,   141,   142,   143,   144,   145,   146,   147,   382,
     148,   373,    49,    76,   175,   176,   177,   404,   178,   149,
     374,   150,   375,   151,   376,   717,   718,   719,   845,   696,
     697,   698,   826,  1019,   699,   827,   700,   828,   701,   829,
     702,   703,   442,   704,   705,   706,   707,   708,   709,   710,
     711,   712,   835,   713,   714,   838,   152,   392,   751,   752,
     753,   865,   153,   389,   738,   739,   740,   741,   154,   391,
     746,   747,   748,   749,   155,   390,   156,   395,   762,   763,
     764,   874,    65,    84,   308,   309,   310,   455,   311,   456,
     157,   396,   771,   772,   773,   774,   775,   776,   777,   778,
     158,   383,   721,   722,   723,   848,    51,    77,   197,   198,
     199,   410,   200,   411,   201,   412,   202,   417,   203,   416,
     204,   415,   634,   205,   206,   159,   388,   733,   734,   735,
     857,   950,   951,   160,   384,    59,    81,   725,   726,   727,
     851,    61,    82,   273,   274,   275,   276,   277,   278,   279,
     441,   280,   445,   281,   444,   282,   283,   446,   284,   161,
     385,   729,   730,   731,   854,    63,    83,   294,   295,   296,
     297,   298,   450,   299,   300,   301,   302,   208,   408,   807,
     808,   809,   900,    53,    78,   219,   220,   221,   421,   162,
     386,   163,   387,   211,   409,   811,   812,   813,   903,    55,
      79,   235,   236,   237,   424,   238,   239,   426,   240,   241,
     164,   394,   758,   759,   760,   871,    57,    80,   253,   254,
     255,   256,   432,   257,   433,   258,   434,   259,   435,   260,
     436,   261,   437,   262,   431,   213,   418,   816,   817,   906,
     165,   393,   755,   756,   868,   968,   969,   970,   971,   972,
    1032,   973,   166,   397,   788,   789,   790,   885,  1041,   791,
     792,   886,   793,   794,   167,   168,   399,   800,   801,   802,
     892,   803,   893,   169,   400,   170,   401,    67,    85,   331,
     332,   333,   334,   460,   335,   461,   336,   337,   463,   338,
     339,   340,   466,   661,   341,   467,   342,   343,   344,   345,
     471,   668,   346,   472,   347,   473,   348,   474,   104,   365,
     105,   366,   106,   367,   171,   371,   372,    71,    87,   355,
     356,   357,   480,   107,   364,    69,    86,   350,   351,   352,
     477,   819,   820,   908,  1009,  1010,  1011,  1012,  1051,  1013,
    1049,  1066,  1067,  1068,  1075,  1076,  1077,  1082,  1078,  1079,
    1080
  };

  const unsigned short
  Dhcp6Parser::yytable_[] =
  {
     100,   139,   174,   192,   215,   229,   249,   193,   271,   290,
     307,   328,   785,   745,   179,   209,   222,   233,   251,   194,
     285,   303,   195,   329,   715,   492,   180,   210,   223,   234,
     252,    40,   286,   304,   943,   330,   272,   291,   944,   196,
     945,   292,   212,   293,   216,   230,   217,   231,   948,   949,
     955,    32,    94,   264,    44,   353,   607,    33,   736,    34,
      46,    35,   172,   173,    91,   207,   218,   232,   250,   108,
     607,   305,   306,   109,   122,   110,   243,    48,   111,   112,
     113,   369,   265,   814,   266,   267,   370,    50,   268,   269,
     270,    52,   123,   124,   663,   664,   665,   666,    54,   123,
     124,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     242,    56,   635,   123,   124,    58,   243,   244,   245,   246,
     247,   248,   123,   124,   641,   642,   643,   123,   124,    60,
     667,    62,   402,   122,   265,    64,   122,   403,   737,   125,
     126,   127,   128,   129,    99,   130,   860,   214,    66,   861,
     131,   123,   124,  1071,   123,   124,  1072,  1073,  1074,   132,
     406,   779,   133,   419,   863,   407,   265,   864,   420,   134,
     684,   961,   962,   189,   795,   796,   190,   135,   136,    68,
     422,   137,   138,   123,   124,   423,    95,    70,   765,   766,
     767,   768,   769,   770,   121,    96,    97,    98,    99,   265,
     287,   266,   267,   288,   289,    99,   943,   123,   124,   349,
     944,   358,   945,    99,    99,   869,   123,   124,   870,    99,
     948,   949,   955,    36,    37,    38,    39,   429,    99,   457,
     679,   359,   430,    99,   458,   680,   681,   682,   683,   684,
     685,   686,   687,   688,   689,   690,   691,   692,   693,   694,
     305,   306,   677,   780,   781,   782,   783,    99,   909,   265,
      99,   910,  1069,   745,  1002,  1070,  1003,  1004,   929,   475,
     114,   115,   116,   117,   476,   478,   481,   481,   122,   402,
     479,   482,   597,   785,   822,   360,   478,   481,   181,    99,
     182,   823,   824,   659,   660,   100,   123,   124,   183,   184,
     185,   186,   187,   188,   406,   842,   842,   866,   361,   825,
     843,   844,   867,    99,   362,   189,   883,   438,   190,   131,
     890,   884,    99,   368,   377,   891,   191,   378,   139,   894,
     475,   842,   174,   419,   895,   896,  1025,  1029,  1026,   379,
     380,   457,  1030,   381,   179,   192,  1037,   422,   215,   193,
     398,   405,  1046,   429,  1052,   229,   180,   209,  1047,  1053,
     222,   194,   413,  1086,   195,   249,   414,   233,  1087,   210,
     425,   427,   223,   483,   484,   271,   428,   251,   439,   234,
     290,   196,    99,   443,   212,   440,   447,   285,   216,   252,
     217,   448,   303,   449,   453,   230,   451,   231,   452,   286,
     454,   328,    99,   272,   304,   459,   462,   207,   291,   464,
     218,   465,   292,   329,   293,   468,   469,   232,   122,   470,
     114,   115,   116,   117,   485,   330,   120,   250,   122,   265,
     486,   224,   225,   226,   227,   228,   123,   124,   630,   631,
     632,   633,  1015,  1016,  1017,  1018,   123,   124,   487,   184,
     185,   488,   187,   188,   489,   189,   490,   493,   190,   736,
     743,   494,   744,   495,   496,   189,   497,   498,   190,  1038,
    1039,  1040,   503,   504,   505,   506,   191,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,   507,   508,   499,   509,   500,   501,   510,   511,
     512,   502,   594,   595,   596,   513,   514,   515,   516,   517,
     518,   520,   519,   521,   522,   524,   525,   527,   139,   528,
     529,   530,   531,   533,   532,   174,   695,   695,   534,   123,
     124,   535,   536,   537,   539,   541,   542,   179,   543,   547,
     548,   544,    99,   549,   550,   784,   797,   551,   328,   180,
     545,   552,    99,   553,   555,   556,   557,   786,   798,   558,
     329,   559,   560,   561,   563,   564,   567,   565,   568,   787,
     799,   571,   330,   570,   572,   573,   574,   577,   575,   578,
     576,   582,   655,   579,   580,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   581,
     583,   584,   585,   587,   589,   674,   326,   327,   591,   592,
     593,   603,   598,   599,   600,   601,   602,   604,   605,   606,
     609,   610,    34,   611,   612,   613,   627,   615,   614,   616,
     617,   847,   628,   618,   619,    99,   620,   622,   623,   625,
     626,   672,   673,   629,   636,   637,   638,   639,   640,   644,
     645,   646,   647,   648,   649,   650,   651,   652,   653,   662,
     716,   654,   720,   656,   657,   724,   728,   732,   658,   669,
     670,   671,   750,   754,   757,   761,   806,   810,   818,   830,
     831,   832,   833,   834,   836,   837,   839,   840,   841,   621,
     850,   846,   849,   853,   852,   855,   856,   858,   859,   917,
     862,   873,   872,   875,   876,   901,   877,   878,   879,   880,
     881,   882,   887,   888,   889,   897,   902,   904,   905,   919,
     907,   912,   911,   913,   914,   915,   916,   921,   918,   924,
     959,   920,   986,   922,   987,   923,   992,   925,   926,   993,
     995,   979,   927,   980,   996,  1027,   981,  1001,   982,  1033,
     983,   984,   988,   989,   990,  1020,  1021,  1022,  1023,  1024,
    1028,  1034,  1031,  1035,  1036,  1042,  1043,  1050,   695,  1055,
    1058,   695,  1044,  1060,   192,  1063,   742,   271,   193,  1065,
     290,  1045,  1083,   937,  1084,  1085,   209,   938,  1048,   285,
     194,  1088,   303,   195,   963,   953,   491,   249,   210,   939,
     307,   286,   940,  1059,   304,   272,   966,   954,   291,   251,
     196,   942,   292,   212,   293,  1056,   784,  1062,   967,   941,
     797,   252,   964,   946,  1089,   947,   215,  1064,   786,   229,
     675,   523,   798,  1090,  1005,  1091,   207,   526,   222,   678,
     787,   233,   821,  1093,   799,   952,  1007,   930,   960,   928,
     223,   957,   958,   234,   978,   977,   965,   569,  1008,   250,
     985,   932,  1006,   931,   538,  1054,   216,   956,   217,   230,
     263,   231,   934,   933,   936,   935,   998,   562,   566,   997,
     540,  1000,   976,   999,   975,   546,   815,   554,   218,   974,
    1057,   232,   991,   994,   586,   590,   588,   804,   676,  1014,
    1061,  1081,  1092,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   937,     0,     0,     0,   938,
       0,   963,     0,     0,     0,     0,     0,   953,     0,     0,
       0,   939,     0,   966,   940,     0,     0,     0,  1005,   954,
       0,     0,     0,   942,     0,   967,     0,     0,     0,   964,
    1007,   941,     0,     0,     0,   946,     0,   947,     0,     0,
       0,     0,  1008,     0,     0,     0,  1006,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   952,     0,     0,
       0,     0,     0,   965
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    77,    82,    83,
      84,    85,   619,   613,    76,    77,    78,    79,    80,    77,
      82,    83,    77,    85,   601,   371,    76,    77,    78,    79,
      80,    17,    82,    83,   857,    85,    82,    83,   857,    77,
     857,    83,    77,    83,    78,    79,    78,    79,   857,   857,
     857,     0,    10,    19,     7,    12,   507,     5,    91,     7,
       7,     9,    14,    15,   171,    77,    78,    79,    80,     7,
     521,    98,    99,    11,    47,    13,    89,     7,    16,    17,
      18,     3,    48,    96,    50,    51,     8,     7,    54,    55,
      56,     7,    65,    66,   138,   139,   140,   141,     7,    65,
      66,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      83,     7,   535,    65,    66,     7,    89,    90,    91,    92,
      93,    94,    65,    66,   547,   548,   549,    65,    66,     7,
     174,     7,     3,    47,    48,     7,    47,     8,   171,    77,
      78,    79,    80,    81,   171,    83,     3,    58,     7,     6,
      88,    65,    66,   147,    65,    66,   150,   151,   152,    97,
       3,    19,   100,     3,     3,     8,    48,     6,     8,   107,
      28,    85,    86,    84,   117,   118,    87,   115,   116,     7,
       3,   119,   120,    65,    66,     8,   144,     7,   101,   102,
     103,   104,   105,   106,    46,   153,   154,   155,   171,    48,
      49,    50,    51,    52,    53,   171,  1029,    65,    66,   145,
    1029,     6,  1029,   171,   171,     3,    65,    66,     6,   171,
    1029,  1029,  1029,   171,   172,   173,   174,     3,   171,     3,
      19,     3,     8,   171,     8,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      98,    99,   598,   111,   112,   113,   114,   171,     3,    48,
     171,     6,     3,   863,   146,     6,   148,   149,   845,     3,
      39,    40,    41,    42,     8,     3,     3,     3,    47,     3,
       8,     8,     8,   890,     8,     4,     3,     3,    57,   171,
      59,     8,     8,   135,   136,   369,    65,    66,    67,    68,
      69,    70,    71,    72,     3,     3,     3,     3,     8,     8,
       8,     8,     8,   171,     3,    84,     3,     8,    87,    88,
       3,     8,   171,     4,     4,     8,    95,     4,   402,     3,
       3,     3,   406,     3,     8,     8,     8,     3,     8,     4,
       4,     3,     8,     4,   406,   419,     8,     3,   422,   419,
       4,     4,     8,     3,     3,   429,   406,   419,     8,     8,
     422,   419,     4,     3,   419,   439,     4,   429,     8,   419,
       4,     4,   422,   359,   360,   449,     4,   439,     3,   429,
     454,   419,   171,     4,   419,     8,     4,   449,   422,   439,
     422,     8,   454,     3,     8,   429,     4,   429,     4,   449,
       3,   475,   171,   449,   454,     4,     4,   419,   454,     4,
     422,     4,   454,   475,   454,     4,     4,   429,    47,     4,
      39,    40,    41,    42,   171,   475,    45,   439,    47,    48,
       4,    60,    61,    62,    63,    64,    65,    66,    73,    74,
      75,    76,    20,    21,    22,    23,    65,    66,     4,    68,
      69,     4,    71,    72,     4,    84,     4,     4,    87,    91,
      92,     4,    94,     4,     4,    84,     4,   172,    87,   108,
     109,   110,     4,     4,     4,     4,    95,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,     4,     4,   172,     4,   172,   172,     4,     4,
       4,   172,   488,   489,   490,     4,     4,     4,     4,     4,
       4,     4,   172,     4,     4,     4,   174,     4,   592,     4,
       4,     4,     4,   174,   172,   599,   600,   601,     4,    65,
      66,     4,     4,     4,     4,     4,   172,   599,     4,     4,
       4,   172,   171,     4,     4,   619,   620,     4,   622,   599,
     172,     4,   171,     4,     4,     4,   172,   619,   620,     4,
     622,     4,     4,   174,     4,   174,     4,   174,     4,   619,
     620,     4,   622,   174,     4,   172,     4,     4,   172,     4,
     172,     4,   568,   174,   174,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   174,
       4,     4,     4,     4,     4,   591,   142,   143,     4,     7,
       7,   171,     7,     7,     7,     7,     5,     5,     5,     5,
     171,     5,     7,     5,     5,     5,   171,     5,     7,     5,
       5,     3,   171,     7,     7,   171,     7,     7,     5,     5,
       5,     5,     5,   171,   171,     7,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   137,
       7,   171,     7,   171,   171,     7,     7,     7,   171,   171,
     171,   171,    82,     7,     7,     7,     7,     7,     7,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   521,
       3,     6,     6,     3,     6,     6,     3,     6,     3,   174,
       6,     3,     6,     6,     3,     6,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   171,     3,     6,     3,   174,
       8,     4,     6,     4,     4,     4,   172,     4,   172,     4,
       4,   172,     4,   172,     4,   172,     4,   172,   172,     4,
       6,   172,   174,   172,     3,     8,   172,     4,   172,     4,
     172,   172,   172,   172,   172,   171,   171,   171,   171,   171,
       8,     8,   171,     3,     8,   171,   171,     4,   842,     4,
       4,   845,   171,     4,   848,     5,   612,   851,   848,     7,
     854,   171,     4,   857,     4,     4,   848,   857,   171,   851,
     848,     4,   854,   848,   868,   857,   369,   871,   848,   857,
     874,   851,   857,   172,   854,   851,   868,   857,   854,   871,
     848,   857,   854,   848,   854,   174,   890,   171,   868,   857,
     894,   871,   868,   857,   174,   857,   900,   171,   890,   903,
     592,   402,   894,   172,   908,   172,   848,   406,   900,   599,
     890,   903,   673,   171,   894,   857,   908,   847,   866,   842,
     900,   860,   863,   903,   876,   874,   868,   457,   908,   871,
     883,   850,   908,   848,   419,  1029,   900,   859,   900,   903,
      81,   903,   853,   851,   856,   854,   902,   449,   454,   900,
     422,   905,   873,   903,   871,   429,   637,   439,   900,   869,
    1035,   903,   890,   894,   475,   481,   478,   622,   593,   909,
    1052,  1069,  1086,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1029,    -1,    -1,    -1,  1029,
      -1,  1035,    -1,    -1,    -1,    -1,    -1,  1029,    -1,    -1,
      -1,  1029,    -1,  1035,  1029,    -1,    -1,    -1,  1052,  1029,
      -1,    -1,    -1,  1029,    -1,  1035,    -1,    -1,    -1,  1035,
    1052,  1029,    -1,    -1,    -1,  1029,    -1,  1029,    -1,    -1,
      -1,    -1,  1052,    -1,    -1,    -1,  1052,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1029,    -1,    -1,
      -1,    -1,    -1,  1035
  };

  const unsigned short
  Dhcp6Parser::yystos_[] =
  {
       0,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,     0,     5,     7,     9,   171,   172,   173,   174,
     192,   193,   194,   199,     7,   208,     7,   214,     7,   227,
       7,   321,     7,   398,     7,   414,     7,   431,     7,   350,
       7,   356,     7,   380,     7,   297,     7,   492,     7,   540,
       7,   532,   200,   195,   209,   215,   228,   322,   399,   415,
     432,   351,   357,   381,   298,   493,   541,   533,   192,   201,
     202,   171,   197,   198,    10,   144,   153,   154,   155,   171,
     207,   210,   211,   212,   523,   525,   527,   538,     7,    11,
      13,    16,    17,    18,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    65,    66,    77,    78,    79,    80,    81,
      83,    88,    97,   100,   107,   115,   116,   119,   120,   207,
     216,   217,   218,   219,   220,   221,   222,   223,   225,   234,
     236,   238,   271,   277,   283,   289,   291,   305,   315,   340,
     348,   374,   404,   406,   425,   455,   467,   479,   480,   488,
     490,   529,    14,    15,   207,   229,   230,   231,   233,   404,
     406,    57,    59,    67,    68,    69,    70,    71,    72,    84,
      87,    95,   207,   218,   219,   220,   221,   323,   324,   325,
     327,   329,   331,   333,   335,   338,   339,   374,   392,   404,
     406,   408,   425,   450,    58,   207,   331,   333,   374,   400,
     401,   402,   404,   406,    60,    61,    62,    63,    64,   207,
     331,   333,   374,   404,   406,   416,   417,   418,   420,   421,
     423,   424,    83,    89,    90,    91,    92,    93,    94,   207,
     374,   404,   406,   433,   434,   435,   436,   438,   440,   442,
     444,   446,   448,   348,    19,    48,    50,    51,    54,    55,
      56,   207,   256,   358,   359,   360,   361,   362,   363,   364,
     366,   368,   370,   371,   373,   404,   406,    49,    52,    53,
     207,   256,   362,   368,   382,   383,   384,   385,   386,   388,
     389,   390,   391,   404,   406,    98,    99,   207,   299,   300,
     301,   303,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   142,   143,   207,   404,
     406,   494,   495,   496,   497,   499,   501,   502,   504,   505,
     506,   509,   511,   512,   513,   514,   517,   519,   521,   145,
     542,   543,   544,    12,   207,   534,   535,   536,     6,     3,
       4,     8,     3,   213,   539,   524,   526,   528,     4,     3,
       8,   530,   531,   226,   235,   237,   239,     4,     4,     4,
       4,     4,   224,   316,   349,   375,   405,   407,   341,   278,
     290,   284,   272,   456,   426,   292,   306,   468,     4,   481,
     489,   491,     3,     8,   232,     4,     3,     8,   393,   409,
     326,   328,   330,     4,     4,   336,   334,   332,   451,     3,
       8,   403,     3,     8,   419,     4,   422,     4,     4,     3,
       8,   449,   437,   439,   441,   443,   445,   447,     8,     3,
       8,   365,   257,     4,   369,   367,   372,     4,     8,     3,
     387,     4,     4,     8,     3,   302,   304,     3,     8,     4,
     498,   500,     4,   503,     4,     4,   507,   510,     4,     4,
       4,   515,   518,   520,   522,     3,     8,   545,     3,     8,
     537,     3,     8,   192,   192,   171,     4,     4,     4,     4,
       4,   211,   534,     4,     4,     4,     4,     4,   172,   172,
     172,   172,   172,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   172,
       4,     4,     4,   217,     4,   174,   230,     4,     4,     4,
       4,     4,   172,   174,     4,     4,     4,     4,   324,     4,
     401,     4,   172,     4,   172,   172,   417,     4,     4,     4,
       4,     4,     4,     4,   435,     4,     4,   172,     4,     4,
       4,   174,   360,     4,   174,   174,   384,     4,     4,   300,
     174,     4,     4,   172,     4,   172,   172,     4,     4,   174,
     174,   174,     4,     4,     4,     4,   495,     4,   543,     4,
     535,     4,     7,     7,   192,   192,   192,     8,     7,     7,
       7,     7,     5,   171,     5,     5,     5,   194,   196,   171,
       5,     5,     5,     5,     7,     5,     5,     5,     7,     7,
       7,   196,     7,     5,   203,     5,     5,   171,   171,   171,
      73,    74,    75,    76,   337,   203,   171,     7,   171,   171,
     171,   203,   203,   203,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   192,   171,   171,   171,   135,
     136,   508,   137,   138,   139,   140,   141,   174,   516,   171,
     171,   171,     5,     5,   192,   216,   542,   534,   229,    19,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,   207,   244,   245,   246,   249,
     251,   253,   255,   256,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   268,   269,   244,     7,   240,   241,   242,
       7,   317,   318,   319,     7,   352,   353,   354,     7,   376,
     377,   378,     7,   342,   343,   344,    91,   171,   279,   280,
     281,   282,   201,    92,    94,   281,   285,   286,   287,   288,
      82,   273,   274,   275,     7,   457,   458,     7,   427,   428,
     429,     7,   293,   294,   295,   101,   102,   103,   104,   105,
     106,   307,   308,   309,   310,   311,   312,   313,   314,    19,
     111,   112,   113,   114,   207,   258,   404,   406,   469,   470,
     471,   474,   475,   477,   478,   117,   118,   207,   404,   406,
     482,   483,   484,   486,   494,   204,     7,   394,   395,   396,
       7,   410,   411,   412,    96,   436,   452,   453,     7,   546,
     547,   240,     8,     8,     8,     8,   247,   250,   252,   254,
       4,     4,     4,     4,     4,   267,     4,     4,   270,     4,
       4,     4,     3,     8,     8,   243,     6,     3,   320,     6,
       3,   355,     6,     3,   379,     6,     3,   345,     6,     3,
       3,     6,     6,     3,     6,   276,     3,     8,   459,     3,
       6,   430,     6,     3,   296,     6,     3,     4,     4,     4,
       4,     4,     4,     3,     8,   472,   476,     4,     4,     4,
       3,     8,   485,   487,     3,     8,     8,   171,   205,   206,
     397,     6,     3,   413,     6,     3,   454,     8,   548,     3,
       6,     6,     4,     4,     4,     4,   172,   174,   172,   174,
     172,     4,   172,   172,     4,   172,   172,   174,   245,   244,
     242,   323,   319,   358,   354,   382,   378,   207,   218,   219,
     220,   221,   256,   315,   327,   329,   331,   333,   335,   339,
     346,   347,   374,   404,   406,   450,   344,   280,   286,     4,
     274,    85,    86,   207,   256,   374,   404,   406,   460,   461,
     462,   463,   464,   466,   458,   433,   429,   299,   295,   172,
     172,   172,   172,   172,   172,   308,     4,     4,   172,   172,
     172,   470,     4,     4,   483,     6,     3,   400,   396,   416,
     412,     4,   146,   148,   149,   207,   256,   404,   406,   549,
     550,   551,   552,   554,   547,    20,    21,    22,    23,   248,
     171,   171,   171,   171,   171,     8,     8,     8,     8,     3,
       8,   171,   465,     4,     8,     3,     8,     8,   108,   109,
     110,   473,   171,   171,   171,   171,     8,     8,   171,   555,
       4,   553,     3,     8,   347,     4,   174,   462,     4,   172,
       4,   550,   171,     5,   171,     7,   556,   557,   558,     3,
       6,   147,   150,   151,   152,   559,   560,   561,   563,   564,
     565,   557,   562,     4,     4,     4,     3,     8,     4,   174,
     172,   172,   560,   171
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
     217,   217,   217,   217,   217,   217,   217,   218,   219,   220,
     221,   222,   224,   223,   226,   225,   228,   227,   229,   229,
     230,   230,   230,   230,   230,   232,   231,   233,   235,   234,
     237,   236,   239,   238,   240,   240,   241,   241,   243,   242,
     244,   244,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     247,   246,   248,   248,   248,   248,   250,   249,   252,   251,
     254,   253,   255,   257,   256,   258,   259,   260,   261,   262,
     263,   264,   265,   267,   266,   268,   270,   269,   272,   271,
     273,   273,   274,   276,   275,   278,   277,   279,   279,   280,
     280,   281,   282,   284,   283,   285,   285,   286,   286,   286,
     287,   288,   290,   289,   292,   291,   293,   293,   294,   294,
     296,   295,   298,   297,   299,   299,   299,   300,   300,   302,
     301,   304,   303,   306,   305,   307,   307,   308,   308,   308,
     308,   308,   308,   309,   310,   311,   312,   313,   314,   316,
     315,   317,   317,   318,   318,   320,   319,   322,   321,   323,
     323,   324,   324,   324,   324,   324,   324,   324,   324,   324,
     324,   324,   324,   324,   324,   324,   324,   324,   324,   324,
     324,   326,   325,   328,   327,   330,   329,   332,   331,   334,
     333,   336,   335,   337,   337,   337,   337,   338,   339,   341,
     340,   342,   342,   343,   343,   345,   344,   346,   346,   347,
     347,   347,   347,   347,   347,   347,   347,   347,   347,   347,
     347,   347,   347,   347,   347,   347,   349,   348,   351,   350,
     352,   352,   353,   353,   355,   354,   357,   356,   358,   358,
     359,   359,   360,   360,   360,   360,   360,   360,   360,   360,
     360,   360,   361,   362,   363,   365,   364,   367,   366,   369,
     368,   370,   372,   371,   373,   375,   374,   376,   376,   377,
     377,   379,   378,   381,   380,   382,   382,   383,   383,   384,
     384,   384,   384,   384,   384,   384,   384,   384,   385,   387,
     386,   388,   389,   390,   391,   393,   392,   394,   394,   395,
     395,   397,   396,   399,   398,   400,   400,   401,   401,   401,
     401,   401,   401,   401,   403,   402,   405,   404,   407,   406,
     409,   408,   410,   410,   411,   411,   413,   412,   415,   414,
     416,   416,   417,   417,   417,   417,   417,   417,   417,   417,
     417,   417,   417,   419,   418,   420,   422,   421,   423,   424,
     426,   425,   427,   427,   428,   428,   430,   429,   432,   431,
     433,   433,   434,   434,   435,   435,   435,   435,   435,   435,
     435,   435,   435,   435,   435,   437,   436,   439,   438,   441,
     440,   443,   442,   445,   444,   447,   446,   449,   448,   451,
     450,   452,   452,   454,   453,   456,   455,   457,   457,   459,
     458,   460,   460,   461,   461,   462,   462,   462,   462,   462,
     462,   462,   463,   465,   464,   466,   468,   467,   469,   469,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   472,
     471,   473,   473,   473,   474,   476,   475,   477,   478,   479,
     481,   480,   482,   482,   483,   483,   483,   483,   483,   485,
     484,   487,   486,   489,   488,   491,   490,   493,   492,   494,
     494,   495,   495,   495,   495,   495,   495,   495,   495,   495,
     495,   495,   495,   495,   495,   495,   495,   495,   495,   495,
     496,   498,   497,   500,   499,   501,   503,   502,   504,   505,
     507,   506,   508,   508,   510,   509,   511,   512,   513,   515,
     514,   516,   516,   516,   516,   516,   518,   517,   520,   519,
     522,   521,   524,   523,   526,   525,   528,   527,   530,   529,
     531,   529,   533,   532,   534,   534,   535,   535,   537,   536,
     539,   538,   541,   540,   542,   542,   543,   545,   544,   546,
     546,   548,   547,   549,   549,   550,   550,   550,   550,   550,
     550,   550,   551,   553,   552,   555,   554,   556,   556,   558,
     557,   559,   559,   560,   560,   560,   560,   562,   561,   563,
     564,   565
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
       1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     6,
       0,     6,     0,     6,     0,     1,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     0,     4,     3,     0,     4,     0,     6,
       1,     3,     1,     0,     4,     0,     6,     1,     3,     1,
       1,     1,     1,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     0,     6,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     1,     1,     1,     1,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     6,     0,     4,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     0,     4,     0,     4,     0,
       4,     1,     0,     4,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     0,     4,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     1,     0,     4,     0,     6,     1,     3,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     3,     0,     4,     3,     3,     3,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     3,     3,     3,     0,
       4,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     4,     1,     3,     1,     1,     0,     6,
       0,     6,     0,     4,     1,     3,     1,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     0,     4,     3,
       3,     3
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
  "\"tcp-keepalive\"", "\"tcp-nodelay\"", "\"preferred-lifetime\"",
  "\"valid-lifetime\"", "\"renew-timer\"", "\"rebind-timer\"",
  "\"decline-probation-period\"", "\"server-tag\"", "\"subnet6\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"pools\"", "\"pool\"", "\"pd-pools\"",
  "\"prefix\"", "\"prefix-len\"", "\"excluded-prefix\"",
  "\"excluded-prefix-len\"", "\"delegated-len\"", "\"user-context\"",
  "\"comment\"", "\"subnet\"", "\"interface\"", "\"interface-id\"",
  "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"global\"", "\"all\"", "\"shared-networks\"",
  "\"mac-sources\"", "\"relay-supplied-options\"",
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
  "\"always-include-fqdn\"", "\"override-no-update\"",
  "\"override-client-update\"", "\"replace-client-name\"",
  "\"generated-prefix\"", "\"UDP\"", "\"TCP\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"hostname-char-set\"", "\"hostname-char-replacement\"", "\"Logging\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"Dhcp4\"",
  "\"DhcpDdns\"", "\"Control-agent\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP6",
  "SUB_DHCP6", "SUB_INTERFACES6", "SUB_SUBNET6", "SUB_POOL6",
  "SUB_PD_POOL", "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
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
  "sanity_checks", "$@37", "sanity_checks_params", "sanity_checks_param",
  "lease_checks", "$@38", "mac_sources", "$@39", "mac_sources_list",
  "mac_sources_value", "duid_id", "string_id",
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
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@111", "replace_client_name_value",
  "generated_prefix", "$@112", "hostname_char_set", "$@113",
  "hostname_char_replacement", "$@114", "dhcp4_json_object", "$@115",
  "dhcpddns_json_object", "$@116", "control_agent_json_object", "$@117",
  "config_control", "$@118", "$@119", "sub_config_control", "$@120",
  "config_control_params", "config_control_param", "config_databases",
  "$@121", "logging_object", "$@122", "sub_logging", "$@123",
  "logging_params", "logging_param", "loggers", "$@124", "loggers_entries",
  "logger_entry", "$@125", "logger_params", "logger_param", "debuglevel",
  "severity", "$@126", "output_options_list", "$@127",
  "output_options_list_content", "output_entry", "$@128",
  "output_params_list", "output_params", "output", "$@129", "flush",
  "maxsize", "maxver", YY_NULLPTR
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
     463,   464,   465,   466,   467,   468,   469,   472,   477,   482,
     487,   492,   497,   497,   505,   505,   516,   516,   525,   526,
     529,   530,   531,   532,   533,   536,   536,   546,   552,   552,
     564,   564,   576,   576,   586,   587,   590,   591,   594,   594,
     604,   605,   608,   609,   610,   611,   612,   613,   614,   615,
     616,   617,   618,   619,   620,   621,   622,   623,   624,   625,
     628,   628,   635,   636,   637,   638,   641,   641,   649,   649,
     657,   657,   665,   670,   670,   678,   683,   688,   693,   698,
     703,   708,   713,   718,   718,   726,   731,   731,   739,   739,
     749,   750,   752,   754,   754,   772,   772,   782,   783,   786,
     787,   790,   795,   800,   800,   810,   811,   814,   815,   816,
     819,   824,   831,   831,   841,   841,   851,   852,   855,   856,
     859,   859,   869,   869,   879,   880,   881,   884,   885,   888,
     888,   896,   896,   904,   904,   915,   916,   919,   920,   921,
     922,   923,   924,   927,   932,   937,   942,   947,   952,   960,
     960,   973,   974,   977,   978,   985,   985,  1011,  1011,  1022,
    1023,  1027,  1028,  1029,  1030,  1031,  1032,  1033,  1034,  1035,
    1036,  1037,  1038,  1039,  1040,  1041,  1042,  1043,  1044,  1045,
    1046,  1049,  1049,  1057,  1057,  1065,  1065,  1073,  1073,  1081,
    1081,  1091,  1091,  1098,  1099,  1100,  1101,  1104,  1109,  1117,
    1117,  1128,  1129,  1133,  1134,  1137,  1137,  1145,  1146,  1149,
    1150,  1151,  1152,  1153,  1154,  1155,  1156,  1157,  1158,  1159,
    1160,  1161,  1162,  1163,  1164,  1165,  1172,  1172,  1185,  1185,
    1194,  1195,  1198,  1199,  1204,  1204,  1219,  1219,  1233,  1234,
    1237,  1238,  1241,  1242,  1243,  1244,  1245,  1246,  1247,  1248,
    1249,  1250,  1253,  1255,  1260,  1262,  1262,  1270,  1270,  1278,
    1278,  1286,  1288,  1288,  1296,  1305,  1305,  1317,  1318,  1323,
    1324,  1329,  1329,  1341,  1341,  1353,  1354,  1359,  1360,  1365,
    1366,  1367,  1368,  1369,  1370,  1371,  1372,  1373,  1376,  1378,
    1378,  1386,  1388,  1390,  1395,  1403,  1403,  1415,  1416,  1419,
    1420,  1423,  1423,  1433,  1433,  1442,  1443,  1446,  1447,  1448,
    1449,  1450,  1451,  1452,  1455,  1455,  1463,  1463,  1488,  1488,
    1518,  1518,  1530,  1531,  1534,  1535,  1538,  1538,  1550,  1550,
    1562,  1563,  1566,  1567,  1568,  1569,  1570,  1571,  1572,  1573,
    1574,  1575,  1576,  1579,  1579,  1587,  1592,  1592,  1600,  1605,
    1613,  1613,  1623,  1624,  1627,  1628,  1631,  1631,  1640,  1640,
    1649,  1650,  1653,  1654,  1658,  1659,  1660,  1661,  1662,  1663,
    1664,  1665,  1666,  1667,  1668,  1671,  1671,  1681,  1681,  1691,
    1691,  1699,  1699,  1707,  1707,  1715,  1715,  1723,  1723,  1736,
    1736,  1746,  1747,  1750,  1750,  1761,  1761,  1771,  1772,  1775,
    1775,  1785,  1786,  1789,  1790,  1793,  1794,  1795,  1796,  1797,
    1798,  1799,  1802,  1804,  1804,  1812,  1820,  1820,  1832,  1833,
    1836,  1837,  1838,  1839,  1840,  1841,  1842,  1843,  1844,  1847,
    1847,  1854,  1855,  1856,  1859,  1864,  1864,  1872,  1877,  1884,
    1891,  1891,  1901,  1902,  1905,  1906,  1907,  1908,  1909,  1912,
    1912,  1920,  1920,  1930,  1930,  1948,  1948,  1960,  1960,  1970,
    1971,  1974,  1975,  1976,  1977,  1978,  1979,  1980,  1981,  1982,
    1983,  1984,  1985,  1986,  1987,  1988,  1989,  1990,  1991,  1992,
    1995,  2000,  2000,  2008,  2008,  2016,  2021,  2021,  2029,  2034,
    2039,  2039,  2047,  2048,  2051,  2051,  2059,  2064,  2069,  2074,
    2074,  2082,  2085,  2088,  2091,  2094,  2100,  2100,  2108,  2108,
    2116,  2116,  2126,  2126,  2133,  2133,  2140,  2140,  2149,  2149,
    2158,  2158,  2169,  2169,  2179,  2180,  2184,  2185,  2188,  2188,
    2203,  2203,  2213,  2213,  2224,  2225,  2229,  2233,  2233,  2245,
    2246,  2250,  2250,  2258,  2259,  2262,  2263,  2264,  2265,  2266,
    2267,  2268,  2271,  2276,  2276,  2284,  2284,  2294,  2295,  2298,
    2298,  2306,  2307,  2310,  2311,  2312,  2313,  2316,  2316,  2324,
    2329,  2334
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
#line 5071 "dhcp6_parser.cc" // lalr1.cc:1218
#line 2339 "dhcp6_parser.yy" // lalr1.cc:1219


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
