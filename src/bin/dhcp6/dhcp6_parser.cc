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
      case 203: // value
      case 207: // map_value
      case 268: // db_type
      case 361: // hr_mode
      case 497: // duid_type
      case 532: // ncr_protocol_value
      case 539: // replace_client_name_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 185: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 184: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 183: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 182: // "constant string"
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
      case 203: // value
      case 207: // map_value
      case 268: // db_type
      case 361: // hr_mode
      case 497: // duid_type
      case 532: // ncr_protocol_value
      case 539: // replace_client_name_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 185: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 184: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 183: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 182: // "constant string"
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
      case 203: // value
      case 207: // map_value
      case 268: // db_type
      case 361: // hr_mode
      case 497: // duid_type
      case 532: // ncr_protocol_value
      case 539: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 185: // "boolean"
        value.move< bool > (that.value);
        break;

      case 184: // "floating point"
        value.move< double > (that.value);
        break;

      case 183: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 182: // "constant string"
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
            case 182: // "constant string"

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< std::string > (); }
#line 398 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 183: // "integer"

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 405 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 184: // "floating point"

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< double > (); }
#line 412 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 185: // "boolean"

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< bool > (); }
#line 419 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 203: // value

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 426 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 207: // map_value

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 433 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 268: // db_type

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 440 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 361: // hr_mode

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 447 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 497: // duid_type

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 454 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 532: // ncr_protocol_value

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 461 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 539: // replace_client_name_value

#line 261 "dhcp6_parser.yy" // lalr1.cc:672
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
      case 203: // value
      case 207: // map_value
      case 268: // db_type
      case 361: // hr_mode
      case 497: // duid_type
      case 532: // ncr_protocol_value
      case 539: // replace_client_name_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 185: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 184: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 183: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 182: // "constant string"
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
#line 270 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 727 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 4:
#line 271 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.CONFIG; }
#line 733 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 6:
#line 272 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP6; }
#line 739 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 8:
#line 273 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 745 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 10:
#line 274 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.SUBNET6; }
#line 751 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 12:
#line 275 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.POOLS; }
#line 757 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 14:
#line 276 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 763 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 16:
#line 277 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 769 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 18:
#line 278 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP6; }
#line 775 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 20:
#line 279 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 781 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 22:
#line 280 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 787 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 24:
#line 281 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 793 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 26:
#line 282 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 799 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 28:
#line 283 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.LOGGING; }
#line 805 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 30:
#line 284 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 811 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 32:
#line 292 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 817 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 33:
#line 293 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 823 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 34:
#line 294 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 829 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 35:
#line 295 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 835 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 36:
#line 296 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 841 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 37:
#line 297 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 847 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 38:
#line 298 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 853 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 39:
#line 301 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 862 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 40:
#line 306 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 873 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 41:
#line 311 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 883 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 42:
#line 317 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 889 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 45:
#line 324 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 898 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 46:
#line 328 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 908 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 47:
#line 335 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 917 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 48:
#line 338 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // list parsing complete. Put any sanity checking here
}
#line 925 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 51:
#line 346 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 934 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 52:
#line 350 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 943 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 53:
#line 357 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // List parsing about to start
}
#line 951 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 54:
#line 359 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 960 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 57:
#line 368 "dhcp6_parser.yy" // lalr1.cc:907
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 969 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 58:
#line 372 "dhcp6_parser.yy" // lalr1.cc:907
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 978 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 59:
#line 383 "dhcp6_parser.yy" // lalr1.cc:907
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 989 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 60:
#line 393 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1000 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 61:
#line 398 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 421 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 428 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1036 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 72:
#line 436 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1046 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 73:
#line 440 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No global parameter is required
    // parsing completed
}
#line 1055 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 119:
#line 496 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1063 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 120:
#line 498 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr datadir(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1073 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 121:
#line 504 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1082 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 122:
#line 509 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1091 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 123:
#line 514 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1100 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 124:
#line 519 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1109 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 125:
#line 524 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1118 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 126:
#line 529 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1127 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 127:
#line 534 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1136 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 128:
#line 539 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1145 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 129:
#line 544 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1154 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 130:
#line 549 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1163 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 131:
#line 554 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1172 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 132:
#line 559 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1181 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 133:
#line 564 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1189 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 134:
#line 566 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1199 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 135:
#line 572 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1210 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 136:
#line 577 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1220 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 137:
#line 583 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1230 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 138:
#line 587 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1239 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 146:
#line 603 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1250 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 147:
#line 608 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1259 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 148:
#line 613 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1268 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 149:
#line 619 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1279 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 150:
#line 624 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1290 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 151:
#line 631 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1301 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 152:
#line 636 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1312 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 153:
#line 643 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1323 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 154:
#line 648 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1332 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 159:
#line 661 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1342 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 160:
#line 665 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1352 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 183:
#line 697 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1360 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 184:
#line 699 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1369 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 185:
#line 704 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1375 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 186:
#line 705 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1381 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 187:
#line 706 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1387 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 188:
#line 707 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1393 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 189:
#line 710 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1401 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 190:
#line 712 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1411 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 191:
#line 718 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1419 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 192:
#line 720 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1429 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 193:
#line 726 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1437 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 194:
#line 728 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1447 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 195:
#line 734 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1456 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 196:
#line 739 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1464 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 197:
#line 741 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1474 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 198:
#line 747 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1483 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 199:
#line 752 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1492 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 200:
#line 757 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1501 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 201:
#line 762 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1510 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 202:
#line 767 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1519 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 203:
#line 772 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1528 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 204:
#line 777 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1537 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 205:
#line 782 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1546 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 206:
#line 787 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1554 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 207:
#line 789 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1564 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 208:
#line 795 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1573 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 209:
#line 800 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1581 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 210:
#line 802 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1591 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 211:
#line 808 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1599 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 212:
#line 810 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1609 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 213:
#line 816 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1617 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 214:
#line 818 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1627 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 215:
#line 824 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1638 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 216:
#line 829 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1647 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 220:
#line 839 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1655 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 221:
#line 841 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 1675 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 222:
#line 857 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1686 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 223:
#line 862 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1695 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 228:
#line 875 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1704 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 229:
#line 880 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1713 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 230:
#line 885 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1724 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 231:
#line 890 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1733 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 237:
#line 904 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1742 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 238:
#line 909 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1751 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 239:
#line 916 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1762 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 240:
#line 921 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1771 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 241:
#line 926 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1782 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 242:
#line 931 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1791 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 247:
#line 944 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1801 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 248:
#line 948 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1811 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 249:
#line 954 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1821 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 250:
#line 958 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1831 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 256:
#line 973 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1839 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 257:
#line 975 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1849 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 258:
#line 981 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1857 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 259:
#line 983 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1866 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 260:
#line 989 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1877 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 261:
#line 994 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1887 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 270:
#line 1012 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1896 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 271:
#line 1017 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1905 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 272:
#line 1022 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1914 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 273:
#line 1027 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1923 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 274:
#line 1032 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1932 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 275:
#line 1037 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1941 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 276:
#line 1045 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1952 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 277:
#line 1050 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1961 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 282:
#line 1070 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1971 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 283:
#line 1074 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 1997 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 284:
#line 1096 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2007 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 285:
#line 1100 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2017 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 315:
#line 1141 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2025 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 316:
#line 1143 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2035 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 317:
#line 1149 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2043 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 318:
#line 1151 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2053 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 319:
#line 1157 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2061 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 320:
#line 1159 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2071 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 321:
#line 1165 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2079 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 322:
#line 1167 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2089 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 323:
#line 1173 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2100 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 324:
#line 1178 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2109 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 325:
#line 1183 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2117 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 326:
#line 1185 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2126 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 327:
#line 1190 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2132 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 328:
#line 1191 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2138 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 329:
#line 1192 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2144 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 330:
#line 1193 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2150 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 331:
#line 1196 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2159 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 332:
#line 1201 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2168 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 333:
#line 1209 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2179 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 334:
#line 1214 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2188 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 339:
#line 1229 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2198 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 340:
#line 1233 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 2206 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 367:
#line 1271 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2217 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 368:
#line 1276 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2226 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 369:
#line 1284 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2235 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 370:
#line 1287 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // parsing completed
}
#line 2243 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 375:
#line 1303 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2253 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 376:
#line 1307 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2265 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 377:
#line 1318 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2275 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 378:
#line 1322 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2287 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 394:
#line 1354 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2296 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 396:
#line 1361 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2304 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 397:
#line 1363 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2314 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 398:
#line 1369 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2322 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 399:
#line 1371 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2332 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 400:
#line 1377 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2340 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 401:
#line 1379 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2350 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 403:
#line 1387 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2358 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 404:
#line 1389 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2368 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 405:
#line 1395 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2377 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 406:
#line 1404 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2388 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 407:
#line 1409 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2397 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 412:
#line 1428 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2407 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 413:
#line 1432 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2416 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 414:
#line 1440 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2426 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 415:
#line 1444 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2435 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 430:
#line 1477 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2443 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 431:
#line 1479 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2453 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 434:
#line 1489 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2462 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 435:
#line 1494 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2471 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 436:
#line 1502 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2482 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 437:
#line 1507 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2491 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 442:
#line 1522 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2501 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 443:
#line 1526 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2511 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 444:
#line 1532 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2521 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 445:
#line 1536 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2530 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 455:
#line 1554 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2538 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 456:
#line 1556 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2548 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 457:
#line 1562 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2556 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 458:
#line 1564 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 2583 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 459:
#line 1587 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2591 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 460:
#line 1589 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 2620 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 461:
#line 1617 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2631 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 462:
#line 1622 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2640 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 467:
#line 1637 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2650 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 468:
#line 1641 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2662 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 469:
#line 1649 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2672 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 470:
#line 1653 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2684 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 484:
#line 1678 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2692 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 485:
#line 1680 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2702 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 486:
#line 1686 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2711 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 487:
#line 1691 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2719 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 488:
#line 1693 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2729 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 489:
#line 1699 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2738 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 490:
#line 1704 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2747 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 491:
#line 1712 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2758 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 492:
#line 1717 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2767 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 497:
#line 1730 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2777 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 498:
#line 1734 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2786 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 499:
#line 1739 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2796 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 500:
#line 1743 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2805 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 516:
#line 1770 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2816 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 517:
#line 1775 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2825 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 518:
#line 1780 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2836 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 519:
#line 1785 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2845 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 520:
#line 1790 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2853 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 521:
#line 1792 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2863 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 522:
#line 1798 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2871 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 523:
#line 1800 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2881 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 524:
#line 1806 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2889 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 525:
#line 1808 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2899 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 526:
#line 1814 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2907 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 527:
#line 1816 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2917 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 528:
#line 1822 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2928 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 529:
#line 1827 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2937 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 530:
#line 1835 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2948 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 531:
#line 1840 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2957 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 534:
#line 1849 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2965 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 535:
#line 1851 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2975 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 536:
#line 1860 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2986 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 537:
#line 1865 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2995 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 540:
#line 1874 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3005 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 541:
#line 1878 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3015 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 554:
#line 1903 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3023 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 555:
#line 1905 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3033 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 556:
#line 1911 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3042 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 557:
#line 1919 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3053 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 558:
#line 1924 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3064 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 570:
#line 1946 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 3072 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 571:
#line 1948 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3081 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 572:
#line 1953 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3087 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 573:
#line 1954 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3093 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 574:
#line 1955 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3099 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 575:
#line 1958 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3108 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 576:
#line 1963 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3116 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 577:
#line 1965 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3126 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 578:
#line 1971 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3135 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 579:
#line 1976 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3144 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 580:
#line 1983 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3153 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 581:
#line 1990 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3164 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 582:
#line 1995 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3173 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 590:
#line 2011 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3181 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 591:
#line 2013 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3191 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 592:
#line 2019 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3199 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 593:
#line 2021 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3209 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 594:
#line 2029 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3217 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 595:
#line 2031 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 3257 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 596:
#line 2069 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3268 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 597:
#line 2074 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3279 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 598:
#line 2081 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3289 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 599:
#line 2085 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3299 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 620:
#line 2115 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3308 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 621:
#line 2120 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3316 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 622:
#line 2122 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3326 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 623:
#line 2128 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3334 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 624:
#line 2130 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3344 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 625:
#line 2136 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3353 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 626:
#line 2141 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3361 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 627:
#line 2143 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3371 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 628:
#line 2149 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3380 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 629:
#line 2154 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3389 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 630:
#line 2159 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3397 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 631:
#line 2161 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3406 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 632:
#line 2167 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3412 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 633:
#line 2168 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3418 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 634:
#line 2171 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3426 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 635:
#line 2173 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3436 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 636:
#line 2179 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3445 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 637:
#line 2184 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3454 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 638:
#line 2189 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3462 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 639:
#line 2191 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3471 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 640:
#line 2197 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3479 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 641:
#line 2200 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3487 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 642:
#line 2203 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3495 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 643:
#line 2206 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3503 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 644:
#line 2209 "dhcp6_parser.yy" // lalr1.cc:907
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3512 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 645:
#line 2215 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3520 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 646:
#line 2217 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3530 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 647:
#line 2223 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3538 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 648:
#line 2225 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3548 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 649:
#line 2231 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3556 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 650:
#line 2233 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3566 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 651:
#line 2241 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3574 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 652:
#line 2243 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3583 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 653:
#line 2248 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3591 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 654:
#line 2250 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3600 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 655:
#line 2255 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3608 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 656:
#line 2257 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3617 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 657:
#line 2264 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3628 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 658:
#line 2269 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3638 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 659:
#line 2275 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3648 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 660:
#line 2279 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No config_control params are required
    // parsing completed
}
#line 3657 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 665:
#line 2294 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3668 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 666:
#line 2299 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3677 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 667:
#line 2304 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3686 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 668:
#line 2314 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3697 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 669:
#line 2319 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3706 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 670:
#line 2324 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3716 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 671:
#line 2328 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // parsing completed
}
#line 3724 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 675:
#line 2344 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3735 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 676:
#line 2349 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3744 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 679:
#line 2361 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3754 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 680:
#line 2365 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3762 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 690:
#line 2382 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3771 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 691:
#line 2387 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3779 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 692:
#line 2389 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3789 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 693:
#line 2395 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3800 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 694:
#line 2400 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3809 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 697:
#line 2409 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3819 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 698:
#line 2413 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3827 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 706:
#line 2428 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3835 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 707:
#line 2430 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3845 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 708:
#line 2436 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3854 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 709:
#line 2441 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3863 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 710:
#line 2446 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3872 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 711:
#line 2451 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3880 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 712:
#line 2453 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 3890 "dhcp6_parser.cc" // lalr1.cc:907
    break;


#line 3894 "dhcp6_parser.cc" // lalr1.cc:907
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


  const short Dhcp6Parser::yypact_ninf_ = -875;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     480,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,    45,    70,    59,    69,
      78,   131,   133,   135,   144,   146,   173,   184,   197,   206,
     207,   219,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,    70,  -139,    30,    79,    41,   280,    81,   164,
     172,    39,    43,   444,   -28,   464,  -103,    93,  -875,   236,
     224,   239,   242,   255,  -875,  -875,  -875,  -875,  -875,   274,
    -875,    75,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,   299,   301,   308,   317,   318,   339,
     341,   345,   347,   349,   351,   361,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,   362,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,    85,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,   381,  -875,   113,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,   383,
     391,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,   138,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,   141,  -875,
    -875,  -875,  -875,  -875,   401,  -875,   405,   415,  -875,  -875,
    -875,  -875,  -875,  -875,   169,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,   359,   421,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,   418,  -875,  -875,   423,  -875,  -875,  -875,   425,
    -875,  -875,   422,   438,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,   439,   440,  -875,
    -875,  -875,  -875,   443,   455,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,   185,  -875,  -875,
    -875,   462,  -875,  -875,   463,  -875,   466,   467,  -875,  -875,
     473,   486,  -875,  -875,  -875,  -875,  -875,   199,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,   200,  -875,  -875,  -875,   487,   212,
    -875,  -875,  -875,  -875,    70,    70,  -875,   311,   492,   493,
     494,   495,   496,  -875,    30,  -875,   497,   498,   505,   506,
     507,   510,   340,   342,   343,   346,   350,   352,   353,   354,
     337,   348,   355,   360,   513,   520,   523,   524,   526,   534,
     540,   541,   542,   543,   544,   545,   546,   547,   548,   549,
     550,   372,   552,   554,   555,   556,   557,   558,    79,  -875,
     559,   380,    41,  -875,   562,   563,   564,   565,   566,   389,
     386,   569,   573,   574,   280,  -875,   575,    81,  -875,   576,
     398,   578,   400,   403,   164,  -875,   580,   583,   587,   590,
     591,   608,   610,  -875,   172,  -875,   615,   616,   441,   617,
     618,   619,   442,  -875,    43,   621,   445,   446,  -875,   444,
     624,   625,    65,  -875,   447,   629,   632,   456,   634,   457,
     458,   638,   639,   459,   460,   658,   659,   464,  -875,  -103,
    -875,   661,   483,    93,  -875,  -875,  -875,   663,   662,   664,
      70,    70,    70,  -875,   488,   665,   666,   667,   668,   671,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,   499,   672,   673,   674,   675,   501,   363,   680,
     681,   682,   683,   684,   685,   687,   688,   689,   690,  -875,
     691,   675,   692,   512,   518,   696,  -875,   697,  -875,  -875,
     698,   699,   525,   527,   528,  -875,  -875,   697,   529,   701,
    -875,   530,  -875,   531,  -875,   532,  -875,  -875,  -875,   697,
     697,   697,   533,   535,   536,   537,  -875,   538,   539,  -875,
     551,   553,   560,  -875,  -875,   561,  -875,  -875,  -875,   567,
      70,  -875,  -875,   568,   570,  -875,   571,  -875,  -875,    36,
     521,  -875,  -875,   159,   572,  -875,  -875,   700,  -875,  -875,
      70,    79,  -103,  -875,  -875,  -875,  -875,    93,    41,   260,
     260,   709,  -875,   715,   716,   717,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,   718,   -37,    70,   -33,   596,   719,
     720,   721,   257,   122,    35,  -875,   464,  -875,  -875,   722,
    -875,  -875,   723,   724,  -875,  -875,  -875,  -875,  -875,   -61,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,   709,  -875,   221,   225,   248,   261,  -875,  -875,
    -875,  -875,   676,   702,   728,   730,   732,  -875,   733,   734,
    -875,  -875,  -875,   735,   736,   737,  -875,   262,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,   276,  -875,
     738,   742,  -875,  -875,   740,   744,  -875,  -875,   745,   752,
    -875,  -875,   750,   754,  -875,  -875,   753,   755,  -875,  -875,
    -875,    83,  -875,  -875,  -875,   756,  -875,  -875,  -875,    97,
    -875,  -875,  -875,  -875,   310,  -875,  -875,  -875,   186,  -875,
    -875,   757,   758,  -875,  -875,   759,   761,  -875,   762,   763,
     764,   765,   766,   767,   331,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,   768,   769,   770,  -875,  -875,  -875,
    -875,   332,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,   333,  -875,  -875,  -875,   334,  -875,   254,
    -875,   593,  -875,   771,   773,  -875,  -875,   772,   776,  -875,
    -875,  -875,   774,  -875,   775,  -875,  -875,  -875,  -875,   779,
     780,   781,   782,   577,   595,   604,   603,   606,   786,   609,
     611,   787,   789,   791,   613,   614,   620,   260,  -875,  -875,
     260,  -875,   709,   280,  -875,   715,    43,  -875,   716,   444,
    -875,   717,   436,  -875,   718,   -37,  -875,  -875,   -33,  -875,
     794,   596,  -875,    89,   719,  -875,   172,  -875,   720,   -28,
    -875,   721,   623,   626,   627,   628,   630,   631,   257,  -875,
     795,   796,   633,   635,   637,   122,  -875,   797,   798,    35,
    -875,  -875,   124,   722,  -875,  -875,   801,   800,    81,  -875,
     723,   164,  -875,   724,   804,  -875,  -875,   451,   622,   642,
     644,  -875,  -875,  -875,  -875,  -875,   645,  -875,  -875,   647,
     652,   654,  -875,  -875,  -875,  -875,   344,  -875,   373,  -875,
     807,  -875,   809,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,   374,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,   655,  -875,  -875,   808,  -875,  -875,  -875,
    -875,  -875,   813,   835,  -875,  -875,  -875,  -875,  -875,   833,
    -875,   385,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
      40,   669,  -875,  -875,  -875,  -875,   670,   677,  -875,  -875,
     844,  -875,  -875,  -875,  -875,  -875,   394,  -875,  -875,  -875,
    -875,  -875,  -875,   712,   395,  -875,   404,  -875,   725,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,   436,  -875,  -875,   846,   714,
    -875,    89,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,   850,   686,   868,   124,  -875,  -875,  -875,  -875,  -875,
    -875,   741,  -875,  -875,   743,  -875,   746,  -875,  -875,   876,
    -875,  -875,   388,  -875,   154,   876,  -875,  -875,   897,   898,
     900,  -875,   414,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
     910,   731,   747,   748,   911,   154,  -875,   751,  -875,  -875,
    -875,   760,  -875,  -875,  -875
  };

  const unsigned short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   137,     9,
     284,    11,   444,    13,   469,    15,   499,    17,   369,    19,
     377,    21,   414,    23,   249,    25,   598,    27,   670,    29,
     659,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     501,     0,   379,   416,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   668,   651,   653,   655,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   119,   657,
     135,   149,   151,   153,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   133,   276,   367,   406,
     457,   459,   325,   333,   222,   239,   230,   215,   536,   491,
     241,   260,   557,     0,   581,   594,   596,   647,   649,   675,
     118,     0,    74,    76,    77,    78,    79,    80,    81,    82,
      83,    84,   112,   113,   114,    85,   110,    88,    89,    90,
      91,   107,    92,    94,    93,    98,    99,    86,   111,    87,
      96,    97,   105,   106,   108,    95,   100,   101,   102,   103,
     104,   116,   117,   109,   115,   146,     0,   145,     0,   139,
     141,   142,   143,   144,   436,   461,   315,   317,   319,     0,
       0,   323,   321,   530,   314,   288,   289,   290,   291,   292,
     293,   294,   295,   311,   312,   313,     0,   286,   299,   300,
     301,   304,   305,   307,   302,   303,   296,   297,   309,   310,
     298,   306,   308,   455,   454,   450,   451,   449,     0,   446,
     448,   452,   453,   484,     0,   487,     0,     0,   483,   477,
     478,   476,   481,   482,     0,   471,   473,   474,   479,   480,
     475,   528,   516,   518,   520,   522,   524,   526,   515,   512,
     513,   514,     0,   502,   503,   507,   508,   505,   509,   510,
     511,   506,     0,   396,   196,     0,   400,   398,   403,     0,
     392,   393,     0,   380,   381,   383,   395,   384,   385,   386,
     402,   387,   388,   389,   390,   391,   430,     0,     0,   428,
     429,   432,   433,     0,   417,   418,   420,   421,   422,   423,
     424,   425,   426,   427,   256,   258,   253,     0,   251,   254,
     255,     0,   621,   623,     0,   626,     0,     0,   630,   634,
       0,     0,   638,   645,   619,   617,   618,     0,   600,   602,
     603,   604,   605,   606,   607,   608,   609,   610,   611,   612,
     613,   614,   615,   616,     0,   672,   674,   665,     0,     0,
     661,   663,   664,    48,     0,     0,    41,     0,     0,     0,
       0,     0,     0,    59,     0,    61,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    73,
       0,     0,     0,   138,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   285,     0,     0,   445,     0,
       0,     0,     0,     0,     0,   470,     0,     0,     0,     0,
       0,     0,     0,   500,     0,   370,     0,     0,     0,     0,
       0,     0,     0,   378,     0,     0,     0,     0,   415,     0,
       0,     0,     0,   250,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   599,     0,
     671,     0,     0,     0,   660,    52,    45,     0,     0,     0,
       0,     0,     0,    63,     0,     0,     0,     0,     0,     0,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   580,
       0,     0,     0,     0,     0,     0,    75,     0,   148,   140,
       0,     0,     0,     0,     0,   331,   332,     0,     0,     0,
     287,     0,   447,     0,   486,     0,   489,   490,   472,     0,
       0,     0,     0,     0,     0,     0,   504,     0,     0,   394,
       0,     0,     0,   405,   382,     0,   434,   435,   419,     0,
       0,   252,   620,     0,     0,   625,     0,   628,   629,     0,
       0,   636,   637,     0,     0,   601,   673,     0,   667,   662,
       0,     0,     0,   652,   654,   656,   120,     0,     0,     0,
       0,   155,   134,   278,   371,   408,    42,   458,   460,   327,
     328,   329,   330,   326,   335,     0,    49,     0,     0,     0,
     493,   243,     0,     0,     0,   595,     0,   648,   650,     0,
      53,   147,   438,   463,   316,   318,   320,   324,   322,     0,
     456,   485,   488,   529,   517,   519,   521,   523,   525,   527,
     397,   197,   401,   399,   404,   431,   257,   259,   622,   624,
     627,   632,   633,   631,   635,   640,   641,   642,   643,   644,
     639,   646,   155,    46,     0,     0,     0,     0,   183,   189,
     191,   193,     0,     0,     0,     0,     0,   206,     0,     0,
     209,   211,   213,     0,     0,     0,   182,     0,   161,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   175,
     176,   177,   178,   173,   174,   179,   180,   181,     0,   159,
       0,   156,   157,   282,     0,   279,   280,   375,     0,   372,
     373,   412,     0,   409,   410,   339,     0,   336,   337,   228,
     229,     0,   224,   226,   227,     0,   237,   238,   234,     0,
     232,   235,   236,   220,     0,   217,   219,   540,     0,   538,
     497,     0,   494,   495,   247,     0,   244,   245,     0,     0,
       0,     0,     0,     0,     0,   262,   264,   265,   266,   267,
     268,   269,   570,   576,     0,     0,     0,   569,   566,   567,
     568,     0,   559,   561,   564,   562,   563,   565,   590,   592,
     589,   587,   588,     0,   583,   585,   586,     0,   679,     0,
     677,    55,   442,     0,   439,   440,   467,     0,   464,   465,
     534,   533,     0,   532,     0,    71,   669,   658,   136,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   150,   152,
       0,   154,     0,     0,   277,     0,   379,   368,     0,   416,
     407,     0,     0,   334,     0,     0,   223,   240,     0,   231,
       0,     0,   216,   542,     0,   537,   501,   492,     0,     0,
     242,     0,     0,     0,     0,     0,     0,     0,     0,   261,
       0,     0,     0,     0,     0,     0,   558,     0,     0,     0,
     582,   597,     0,     0,   676,    57,     0,    56,     0,   437,
       0,     0,   462,     0,     0,   531,   666,     0,     0,     0,
       0,   195,   198,   199,   200,   201,     0,   208,   202,     0,
       0,     0,   203,   204,   205,   162,     0,   158,     0,   281,
       0,   374,     0,   411,   366,   354,   355,   356,   358,   359,
     360,   347,   348,   363,   364,   365,   343,   344,   345,   346,
     352,   353,   351,   357,     0,   341,   349,   361,   362,   350,
     338,   225,   233,     0,   218,   554,     0,   552,   553,   549,
     550,   551,     0,   543,   544,   546,   547,   548,   539,     0,
     496,     0,   246,   270,   271,   272,   273,   274,   275,   263,
       0,     0,   575,   578,   579,   560,     0,     0,   584,   693,
       0,   691,   689,   683,   687,   688,     0,   681,   685,   686,
     684,   678,    54,     0,     0,   441,     0,   466,     0,   185,
     186,   187,   188,   184,   190,   192,   194,   207,   210,   212,
     214,   160,   283,   376,   413,     0,   340,   221,     0,     0,
     541,     0,   498,   248,   572,   573,   574,   571,   577,   591,
     593,     0,     0,     0,     0,   680,    58,   443,   468,   535,
     342,     0,   556,   545,     0,   690,     0,   682,   555,     0,
     692,   697,     0,   695,     0,     0,   694,   706,     0,     0,
       0,   711,     0,   699,   701,   702,   703,   704,   705,   696,
       0,     0,     0,     0,     0,     0,   698,     0,   708,   709,
     710,     0,   700,   707,   712
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,    54,  -875,  -502,
    -875,   134,  -875,  -875,  -875,  -875,   268,  -875,  -476,  -875,
    -875,  -875,   -74,  -875,  -875,  -875,   579,  -875,  -875,  -875,
    -875,   287,   489,  -875,  -875,   -70,   -46,   -40,   -36,   -22,
     -17,   -14,     3,     7,    10,    15,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,   288,   490,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,   213,  -875,    37,  -875,  -622,    47,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
     -21,  -875,  -650,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,    24,  -875,  -875,  -875,  -875,  -875,    31,  -641,
    -875,  -875,  -875,  -875,    33,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,    17,  -875,  -875,  -875,    20,   452,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,    19,  -875,  -875,  -875,
    -875,  -875,  -875,  -874,  -875,  -875,  -875,    50,  -875,  -875,
    -875,    55,   500,  -875,  -875,  -869,  -875,  -867,  -875,   -11,
    -875,    -5,  -875,    18,  -875,  -875,  -875,  -866,  -875,  -875,
    -875,  -875,    46,  -875,  -875,  -136,   870,  -875,  -875,  -875,
    -875,  -875,    57,  -875,  -875,  -875,    56,  -875,   469,  -875,
     -69,  -875,  -875,  -875,  -875,  -875,   -66,  -875,  -875,  -875,
    -875,  -875,   -58,  -875,  -875,  -875,    58,  -875,  -875,  -875,
      61,  -875,   468,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,     6,  -875,  -875,  -875,    13,   508,
    -875,  -875,   -53,  -875,   -29,  -875,  -875,  -875,  -875,  -875,
       5,  -875,  -875,  -875,    11,   502,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,   -62,  -875,  -875,  -875,    49,  -875,  -875,
    -875,    48,  -875,   503,   284,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -864,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,    60,  -875,  -875,  -875,
    -123,  -875,  -875,  -875,  -875,  -875,  -875,  -875,    34,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,    32,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,   304,   465,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,   -73,  -875,   -51,  -875,
    -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,  -875,
     338,   470,  -875,  -875,  -875,  -875,  -875,  -875,  -875,   356,
     471,   -44,  -875,  -875,    38,  -875,  -875,  -128,  -875,  -875,
    -875,  -875,  -875,  -875,  -147,  -875,  -875,  -166,  -875,  -875,
    -875,  -875,  -875,  -875,  -875
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   647,    92,    93,    43,    72,    89,    90,   671,   851,
     946,   947,   736,    45,    74,   101,   102,   103,   388,    47,
      75,   151,   152,   153,   396,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   414,   167,
     398,    49,    76,   198,   199,   200,   440,   201,   168,   399,
     169,   400,   170,   401,   760,   761,   762,   890,   737,   738,
     739,   869,  1073,   740,   870,   741,   871,   742,   872,   743,
     744,   477,   745,   746,   747,   748,   749,   750,   751,   752,
     753,   878,   754,   755,   881,   756,   882,   757,   883,   171,
     425,   794,   795,   796,   910,   172,   422,   781,   782,   783,
     784,   173,   424,   789,   790,   791,   792,   174,   423,   175,
     428,   805,   806,   807,   919,    65,    84,   337,   338,   339,
     490,   340,   491,   176,   429,   814,   815,   816,   817,   818,
     819,   820,   821,   177,   415,   764,   765,   766,   893,    51,
      77,   226,   227,   228,   446,   229,   447,   230,   448,   231,
     452,   232,   451,   178,   420,   653,   234,   235,   179,   421,
     776,   777,   778,   902,  1004,  1005,   180,   416,    59,    81,
     768,   769,   770,   896,    61,    82,   302,   303,   304,   305,
     306,   307,   308,   476,   309,   480,   310,   479,   311,   312,
     481,   313,   181,   417,   772,   773,   774,   899,    63,    83,
     323,   324,   325,   326,   327,   485,   328,   329,   330,   331,
     237,   444,   853,   854,   855,   948,    53,    78,   248,   249,
     250,   456,   182,   418,   183,   419,   240,   445,   857,   858,
     859,   951,    55,    79,   264,   265,   266,   459,   267,   268,
     461,   269,   270,   184,   427,   801,   802,   803,   916,    57,
      80,   282,   283,   284,   285,   467,   286,   468,   287,   469,
     288,   470,   289,   471,   290,   472,   291,   466,   242,   453,
     862,   863,   954,   185,   426,   798,   799,   913,  1022,  1023,
    1024,  1025,  1026,  1088,  1027,   186,   430,   831,   832,   833,
     930,  1097,   834,   835,   931,   836,   837,   187,   188,   432,
     843,   844,   845,   937,   846,   938,   189,   433,   190,   434,
      67,    85,   357,   358,   359,   360,   495,   361,   496,   362,
     363,   498,   364,   365,   366,   501,   703,   367,   502,   368,
     369,   370,   505,   710,   371,   506,   191,   435,   192,   436,
     104,   390,   105,   391,   106,   392,   193,   397,    71,    87,
     379,   380,   381,   511,   382,   107,   389,    69,    86,   374,
     375,   194,   437,   849,   850,   942,  1056,  1057,  1058,  1059,
    1103,  1060,  1101,  1122,  1123,  1124,  1132,  1133,  1134,  1140,
    1135,  1136,  1137,  1138,  1144
  };

  const unsigned short
  Dhcp6Parser::yytable_[] =
  {
     100,   150,   197,   214,   244,   258,   278,   215,   300,   319,
     336,   354,   372,   828,   321,   241,   788,   322,   758,   236,
     247,   261,   279,   202,   238,   251,   262,   280,   997,   314,
     332,   216,   355,   998,   373,   999,  1003,   217,  1009,   272,
      94,   218,   376,    91,   646,    32,   860,   203,   239,   252,
     263,   281,   149,   315,   333,   219,   356,   195,   196,   646,
     220,   301,   320,   221,   293,   779,    44,   245,   259,   779,
     786,    40,   787,   246,   260,    33,    46,    34,   394,    35,
     222,   334,   335,   395,   223,    48,   905,   224,   438,   906,
     108,   109,   225,   439,   110,   233,   128,   111,   112,   113,
     908,   677,   294,   909,   295,   296,   377,   378,   297,   298,
     299,   130,   131,   683,   684,   685,   442,   130,   131,   130,
     131,   443,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,    50,   129,
      52,   454,    54,   822,   457,   780,   455,   129,   294,   458,
     243,    56,   723,    58,    99,   130,   131,   130,   131,  1094,
    1095,  1096,   132,   838,   839,   130,   131,   133,   134,   135,
     136,   137,   464,   138,   334,   335,   211,   465,   139,   212,
      60,   701,   702,   294,    95,  1015,  1016,   140,   492,   914,
     141,    62,   915,   493,    96,    97,    98,   142,   130,   131,
     130,   131,   507,   509,    64,   143,   144,   508,   510,   145,
     146,   997,    99,    66,    68,   513,   998,    99,   999,  1003,
     514,  1009,   129,    99,   438,    99,    70,   384,   509,   865,
     129,   147,   148,   866,   149,   253,   254,   255,   256,   257,
     130,   131,   383,   385,   823,   824,   825,   826,   130,   131,
     386,   513,    36,    37,    38,    39,   867,   943,   387,   211,
     944,    99,   212,    99,   442,   887,   271,   788,   976,   868,
     888,    99,   272,   273,   274,   275,   276,   277,   393,   887,
    1049,   718,  1050,  1051,   889,   828,   719,   720,   721,   722,
     723,   724,   725,   726,   727,   728,   729,   730,   731,   732,
     733,   734,   735,   402,    99,   403,    99,   705,   706,   707,
     708,  1127,   404,   911,  1128,  1129,  1130,  1131,   912,   294,
     100,   405,   406,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   928,   935,   939,   507,   129,   929,
     936,   940,   941,   407,   709,   408,    99,   887,   204,   409,
     205,   410,  1081,   411,    99,   412,   130,   131,   206,   207,
     208,   209,   210,   132,   150,   413,   431,   473,   197,   808,
     809,   810,   811,   812,   813,   211,   454,  1085,   212,   139,
     214,  1082,  1086,   244,   215,   441,   213,   449,   492,   202,
     258,  1125,   241,  1093,  1126,   450,   236,  1104,   457,   247,
     278,   238,  1105,  1107,   251,   460,   261,   464,   216,   462,
     300,   262,  1108,   203,   217,   319,   279,  1145,   218,   463,
     321,   280,  1146,   322,   474,   239,   475,   478,   252,   482,
     483,   314,   219,   354,   372,   263,   332,   220,   515,   516,
     221,   484,    99,   486,   487,   281,   245,   649,   650,   651,
     652,   488,   246,   259,   355,   315,   373,   222,   489,   260,
     333,   223,    99,   301,   224,   376,   494,   497,   320,   225,
     499,   500,   233,  1069,  1070,  1071,  1072,   503,   356,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     504,   512,   127,   517,   129,   294,   518,   519,   520,   521,
     522,   524,   525,   294,   316,   295,   296,   317,   318,   526,
     527,   528,   130,   131,   529,   207,   208,   542,   210,   132,
     130,   131,   538,   530,   543,   531,   532,   544,   545,   533,
     546,   211,   539,   534,   212,   535,   536,   537,   547,   540,
     130,   131,   213,   541,   548,   549,   550,   551,   552,   553,
     554,   555,   556,   557,   558,   559,   560,   150,   561,   562,
     563,   564,   565,   567,   197,   568,   570,   571,   572,   573,
     574,   576,   575,   577,   633,   634,   635,   578,   579,   581,
     583,   584,   585,   586,   589,   202,   587,   590,   376,   827,
     840,   591,   354,   372,   592,   593,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   203,
     829,   841,   594,   355,   595,   373,   147,   148,    99,   597,
     598,   600,   601,   602,   599,   605,    99,   603,   609,   610,
     606,   607,   612,   613,   830,   842,   614,   356,   616,   615,
     617,   618,   619,   620,   621,   622,    99,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,   623,   624,   697,   627,   628,   630,   704,   631,
     636,   632,   637,   638,   639,   640,   641,   643,   644,   645,
     873,   642,    34,   648,   713,   654,   655,   656,   657,   793,
     659,   658,   660,   661,   667,   665,   662,   663,   664,   666,
     668,   669,   670,   672,   673,   712,   874,   674,   679,   675,
     676,   678,   680,   681,   682,   686,   759,   687,   688,   689,
     690,   691,   763,   767,   771,   775,   797,   800,   804,   848,
     852,   856,   875,   692,   876,   693,   877,   879,   880,   884,
     885,   886,   694,   695,   891,   892,   894,   895,  1119,   696,
     698,   897,   699,   700,   711,   898,   900,   901,   904,   903,
     961,   918,   907,   917,   921,   920,   922,   923,   924,   925,
     926,   927,   932,   933,   934,   945,   950,   949,   952,   953,
     962,   956,   955,   957,   958,   959,   960,   963,   964,   965,
     966,   969,   967,   970,   968,   971,   972,   973,  1013,  1040,
    1041,  1046,  1047,  1063,  1074,   974,  1033,  1062,  1068,  1034,
    1035,  1036,  1089,  1037,  1038,  1083,  1042,  1084,  1043,   214,
    1044,  1090,   300,   215,  1075,   319,  1076,  1077,   984,  1078,
     321,   241,   985,   322,  1079,   236,  1080,  1087,  1091,  1017,
     238,  1092,   278,   314,  1006,   336,   332,   216,  1102,  1007,
    1111,  1098,  1099,   217,  1114,  1019,   986,   218,   279,  1100,
    1020,   827,   987,   280,   239,   840,   988,   315,  1052,  1115,
     333,   219,  1116,  1008,   244,   301,   220,   258,   320,   221,
     989,   996,   829,  1121,  1021,   990,   841,   281,   991,  1054,
     247,  1000,  1018,   261,  1106,   251,   222,  1001,   262,  1112,
     223,  1141,  1142,   224,  1143,   992,   830,  1109,   225,   993,
     842,   233,   994,  1055,  1147,  1151,  1148,   995,   714,   252,
    1002,  1053,   263,  1118,   785,   864,   717,   566,  1120,   977,
    1149,  1150,   569,  1153,   975,  1014,  1011,   245,  1032,  1031,
     259,  1012,  1154,   246,   611,   979,   260,  1039,   978,  1110,
    1010,   292,   980,   604,   580,   981,  1065,   608,  1067,   983,
     982,  1064,  1066,   861,  1029,   582,   588,  1030,  1113,  1045,
     847,  1048,   625,   523,  1028,   716,  1117,   596,  1139,  1152,
     626,  1061,     0,   629,     0,     0,     0,     0,   715,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   984,     0,     0,     0,   985,     0,  1017,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1006,     0,     0,
    1052,     0,  1007,  1019,     0,     0,     0,     0,  1020,   986,
       0,     0,     0,     0,     0,   987,     0,     0,     0,   988,
       0,  1054,     0,     0,     0,     0,  1008,     0,     0,     0,
       0,     0,  1021,   989,   996,     0,     0,     0,   990,     0,
    1018,   991,     0,     0,  1000,  1055,     0,     0,     0,     0,
    1001,     0,     0,  1053,     0,     0,     0,     0,   992,     0,
       0,     0,   993,     0,     0,   994,     0,     0,     0,     0,
     995,     0,     0,  1002
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    77,    82,    83,
      84,    85,    85,   663,    83,    77,   657,    83,   640,    77,
      78,    79,    80,    76,    77,    78,    79,    80,   902,    82,
      83,    77,    85,   902,    85,   902,   902,    77,   902,   100,
      10,    77,    86,   182,   546,     0,   107,    76,    77,    78,
      79,    80,   155,    82,    83,    77,    85,    16,    17,   561,
      77,    82,    83,    77,    21,   102,     7,    78,    79,   102,
     103,    17,   105,    78,    79,     5,     7,     7,     3,     9,
      77,   109,   110,     8,    77,     7,     3,    77,     3,     6,
      11,    12,    77,     8,    15,    77,    57,    18,    19,    20,
       3,   577,    59,     6,    61,    62,    13,    14,    65,    66,
      67,    76,    77,   589,   590,   591,     3,    76,    77,    76,
      77,     8,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,     7,    58,
       7,     3,     7,    21,     3,   182,     8,    58,    59,     8,
      69,     7,    30,     7,   182,    76,    77,    76,    77,   119,
     120,   121,    83,   128,   129,    76,    77,    88,    89,    90,
      91,    92,     3,    94,   109,   110,    95,     8,    99,    98,
       7,   145,   146,    59,   154,    96,    97,   108,     3,     3,
     111,     7,     6,     8,   164,   165,   166,   118,    76,    77,
      76,    77,     3,     3,     7,   126,   127,     8,     8,   130,
     131,  1085,   182,     7,     7,     3,  1085,   182,  1085,  1085,
       8,  1085,    58,   182,     3,   182,     7,     3,     3,     8,
      58,   152,   153,     8,   155,    71,    72,    73,    74,    75,
      76,    77,     6,     4,   122,   123,   124,   125,    76,    77,
       8,     3,   182,   183,   184,   185,     8,     3,     3,    95,
       6,   182,    98,   182,     3,     3,    94,   908,   890,     8,
       8,   182,   100,   101,   102,   103,   104,   105,     4,     3,
     156,    21,   158,   159,     8,   935,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     4,   182,     4,   182,   148,   149,   150,
     151,   157,     4,     3,   160,   161,   162,   163,     8,    59,
     394,     4,     4,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,     3,     3,     3,     3,    58,     8,
       8,     8,     8,     4,   185,     4,   182,     3,    68,     4,
      70,     4,     8,     4,   182,     4,    76,    77,    78,    79,
      80,    81,    82,    83,   438,     4,     4,     8,   442,   112,
     113,   114,   115,   116,   117,    95,     3,     3,    98,    99,
     454,     8,     8,   457,   454,     4,   106,     4,     3,   442,
     464,     3,   454,     8,     6,     4,   454,     3,     3,   457,
     474,   454,     8,     8,   457,     4,   464,     3,   454,     4,
     484,   464,     8,   442,   454,   489,   474,     3,   454,     4,
     489,   474,     8,   489,     3,   454,     8,     4,   457,     4,
       8,   484,   454,   507,   507,   464,   489,   454,   384,   385,
     454,     3,   182,     4,     4,   474,   457,    84,    85,    86,
      87,     8,   457,   464,   507,   484,   507,   454,     3,   464,
     489,   454,   182,   484,   454,   509,     4,     4,   489,   454,
       4,     4,   454,    22,    23,    24,    25,     4,   507,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
       4,     4,    56,   182,    58,    59,     4,     4,     4,     4,
       4,     4,     4,    59,    60,    61,    62,    63,    64,     4,
       4,     4,    76,    77,     4,    79,    80,     4,    82,    83,
      76,    77,   185,   183,     4,   183,   183,     4,     4,   183,
       4,    95,   184,   183,    98,   183,   183,   183,     4,   184,
      76,    77,   106,   183,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   183,     4,   631,     4,     4,
       4,     4,     4,     4,   638,   185,     4,     4,     4,     4,
       4,   185,   183,     4,   520,   521,   522,     4,     4,     4,
       4,   183,     4,   183,     4,   638,   183,     4,   632,   663,
     664,     4,   666,   666,     4,     4,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   638,
     663,   664,     4,   666,     4,   666,   152,   153,   182,     4,
       4,     4,     4,     4,   183,     4,   182,   185,     4,     4,
     185,   185,   185,     4,   663,   664,     4,   666,     4,   183,
     183,   183,     4,     4,   185,   185,   182,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,     4,     4,   610,     4,   183,     4,   147,     7,
     182,     7,     7,     7,     7,     7,     5,     5,     5,     5,
       4,   182,     7,   182,   630,     5,     5,     5,     5,    93,
       5,     7,     5,     5,   182,   561,     7,     7,     7,     7,
     182,     5,     5,     5,     5,     5,     4,   182,     7,   182,
     182,   182,   182,   182,   182,   182,     7,   182,   182,   182,
     182,   182,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     4,   182,     4,   182,     4,     4,     4,     4,
       4,     4,   182,   182,     6,     3,     6,     3,     5,   182,
     182,     6,   182,   182,   182,     3,     6,     3,     3,     6,
     183,     3,     6,     6,     3,     6,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   182,     3,     6,     6,     3,
     185,     6,     8,     4,     4,     4,     4,   183,   185,   183,
       4,     4,   183,     4,   183,     4,   183,   183,     4,     4,
       4,     4,     4,     3,   182,   185,   183,     6,     4,   183,
     183,   183,     4,   183,   183,     8,   183,     8,   183,   893,
     183,     8,   896,   893,   182,   899,   182,   182,   902,   182,
     899,   893,   902,   899,   182,   893,   182,   182,     3,   913,
     893,     8,   916,   896,   902,   919,   899,   893,     4,   902,
       4,   182,   182,   893,     4,   913,   902,   893,   916,   182,
     913,   935,   902,   916,   893,   939,   902,   896,   942,   183,
     899,   893,     4,   902,   948,   896,   893,   951,   899,   893,
     902,   902,   935,     7,   913,   902,   939,   916,   902,   942,
     948,   902,   913,   951,   182,   948,   893,   902,   951,   185,
     893,     4,     4,   893,     4,   902,   935,   182,   893,   902,
     939,   893,   902,   942,     4,     4,   185,   902,   631,   948,
     902,   942,   951,   182,   656,   712,   638,   438,   182,   892,
     183,   183,   442,   182,   887,   911,   905,   948,   921,   919,
     951,   908,   182,   948,   492,   895,   951,   928,   893,  1085,
     904,    81,   896,   484,   454,   898,   950,   489,   953,   901,
     899,   948,   951,   679,   916,   457,   464,   918,  1091,   935,
     666,   939,   507,   394,   914,   637,  1104,   474,  1125,  1145,
     509,   943,    -1,   513,    -1,    -1,    -1,    -1,   632,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1085,    -1,    -1,    -1,  1085,    -1,  1091,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1085,    -1,    -1,
    1104,    -1,  1085,  1091,    -1,    -1,    -1,    -1,  1091,  1085,
      -1,    -1,    -1,    -1,    -1,  1085,    -1,    -1,    -1,  1085,
      -1,  1104,    -1,    -1,    -1,    -1,  1085,    -1,    -1,    -1,
      -1,    -1,  1091,  1085,  1085,    -1,    -1,    -1,  1085,    -1,
    1091,  1085,    -1,    -1,  1085,  1104,    -1,    -1,    -1,    -1,
    1085,    -1,    -1,  1104,    -1,    -1,    -1,    -1,  1085,    -1,
      -1,    -1,  1085,    -1,    -1,  1085,    -1,    -1,    -1,    -1,
    1085,    -1,    -1,  1085
  };

  const unsigned short
  Dhcp6Parser::yystos_[] =
  {
       0,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,     0,     5,     7,     9,   182,   183,   184,   185,
     203,   204,   205,   210,     7,   219,     7,   225,     7,   247,
       7,   345,     7,   422,     7,   438,     7,   455,     7,   374,
       7,   380,     7,   404,     7,   321,     7,   516,     7,   563,
       7,   554,   211,   206,   220,   226,   248,   346,   423,   439,
     456,   375,   381,   405,   322,   517,   564,   555,   203,   212,
     213,   182,   208,   209,    10,   154,   164,   165,   166,   182,
     218,   221,   222,   223,   546,   548,   550,   561,    11,    12,
      15,    18,    19,    20,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      76,    77,    83,    88,    89,    90,    91,    92,    94,    99,
     108,   111,   118,   126,   127,   130,   131,   152,   153,   155,
     218,   227,   228,   229,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   245,   254,   256,
     258,   295,   301,   307,   313,   315,   329,   339,   359,   364,
     372,   398,   428,   430,   449,   479,   491,   503,   504,   512,
     514,   542,   544,   552,   567,    16,    17,   218,   249,   250,
     251,   253,   428,   430,    68,    70,    78,    79,    80,    81,
      82,    95,    98,   106,   218,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   347,   348,   349,   351,
     353,   355,   357,   359,   362,   363,   398,   416,   428,   430,
     432,   449,   474,    69,   218,   355,   357,   398,   424,   425,
     426,   428,   430,    71,    72,    73,    74,    75,   218,   355,
     357,   398,   428,   430,   440,   441,   442,   444,   445,   447,
     448,    94,   100,   101,   102,   103,   104,   105,   218,   398,
     428,   430,   457,   458,   459,   460,   462,   464,   466,   468,
     470,   472,   372,    21,    59,    61,    62,    65,    66,    67,
     218,   276,   382,   383,   384,   385,   386,   387,   388,   390,
     392,   394,   395,   397,   428,   430,    60,    63,    64,   218,
     276,   386,   392,   406,   407,   408,   409,   410,   412,   413,
     414,   415,   428,   430,   109,   110,   218,   323,   324,   325,
     327,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   218,   428,   430,   518,   519,   520,
     521,   523,   525,   526,   528,   529,   530,   533,   535,   536,
     537,   540,   542,   544,   565,   566,   567,    13,    14,   556,
     557,   558,   560,     6,     3,     4,     8,     3,   224,   562,
     547,   549,   551,     4,     3,     8,   230,   553,   246,   255,
     257,   259,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   244,   340,   373,   399,   429,   431,
     360,   365,   302,   314,   308,   296,   480,   450,   316,   330,
     492,     4,   505,   513,   515,   543,   545,   568,     3,     8,
     252,     4,     3,     8,   417,   433,   350,   352,   354,     4,
       4,   358,   356,   475,     3,     8,   427,     3,     8,   443,
       4,   446,     4,     4,     3,     8,   473,   461,   463,   465,
     467,   469,   471,     8,     3,     8,   389,   277,     4,   393,
     391,   396,     4,     8,     3,   411,     4,     4,     8,     3,
     326,   328,     3,     8,     4,   522,   524,     4,   527,     4,
       4,   531,   534,     4,     4,   538,   541,     3,     8,     3,
       8,   559,     4,     3,     8,   203,   203,   182,     4,     4,
       4,     4,     4,   222,     4,     4,     4,     4,     4,     4,
     183,   183,   183,   183,   183,   183,   183,   183,   185,   184,
     184,   183,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   183,
       4,     4,     4,     4,     4,     4,   228,     4,   185,   250,
       4,     4,     4,     4,     4,   183,   185,     4,     4,     4,
     348,     4,   425,     4,   183,     4,   183,   183,   441,     4,
       4,     4,     4,     4,     4,     4,   459,     4,     4,   183,
       4,     4,     4,   185,   384,     4,   185,   185,   408,     4,
       4,   324,   185,     4,     4,   183,     4,   183,   183,     4,
       4,   185,   185,     4,     4,   519,   566,     4,   183,   557,
       4,     7,     7,   203,   203,   203,   182,     7,     7,     7,
       7,     5,   182,     5,     5,     5,   205,   207,   182,    84,
      85,    86,    87,   361,     5,     5,     5,     5,     7,     5,
       5,     5,     7,     7,     7,   207,     7,   182,   182,     5,
       5,   214,     5,     5,   182,   182,   182,   214,   182,     7,
     182,   182,   182,   214,   214,   214,   182,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   182,   203,   182,   182,
     182,   145,   146,   532,   147,   148,   149,   150,   151,   185,
     539,   182,     5,   203,   227,   565,   556,   249,    21,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,   218,   264,   265,   266,
     269,   271,   273,   275,   276,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   288,   289,   291,   293,   264,     7,
     260,   261,   262,     7,   341,   342,   343,     7,   376,   377,
     378,     7,   400,   401,   402,     7,   366,   367,   368,   102,
     182,   303,   304,   305,   306,   212,   103,   105,   305,   309,
     310,   311,   312,    93,   297,   298,   299,     7,   481,   482,
       7,   451,   452,   453,     7,   317,   318,   319,   112,   113,
     114,   115,   116,   117,   331,   332,   333,   334,   335,   336,
     337,   338,    21,   122,   123,   124,   125,   218,   278,   428,
     430,   493,   494,   495,   498,   499,   501,   502,   128,   129,
     218,   428,   430,   506,   507,   508,   510,   518,     7,   569,
     570,   215,     7,   418,   419,   420,     7,   434,   435,   436,
     107,   460,   476,   477,   260,     8,     8,     8,     8,   267,
     270,   272,   274,     4,     4,     4,     4,     4,   287,     4,
       4,   290,   292,   294,     4,     4,     4,     3,     8,     8,
     263,     6,     3,   344,     6,     3,   379,     6,     3,   403,
       6,     3,   369,     6,     3,     3,     6,     6,     3,     6,
     300,     3,     8,   483,     3,     6,   454,     6,     3,   320,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
     496,   500,     4,     4,     4,     3,     8,   509,   511,     3,
       8,     8,   571,     3,     6,   182,   216,   217,   421,     6,
       3,   437,     6,     3,   478,     8,     6,     4,     4,     4,
       4,   183,   185,   183,   185,   183,     4,   183,   183,     4,
       4,     4,   183,   183,   185,   265,   264,   262,   347,   343,
     382,   378,   406,   402,   218,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   276,   339,   351,   353,
     355,   357,   359,   363,   370,   371,   398,   428,   430,   474,
     368,   304,   310,     4,   298,    96,    97,   218,   276,   398,
     428,   430,   484,   485,   486,   487,   488,   490,   482,   457,
     453,   323,   319,   183,   183,   183,   183,   183,   183,   332,
       4,     4,   183,   183,   183,   494,     4,     4,   507,   156,
     158,   159,   218,   276,   428,   430,   572,   573,   574,   575,
     577,   570,     6,     3,   424,   420,   440,   436,     4,    22,
      23,    24,    25,   268,   182,   182,   182,   182,   182,   182,
     182,     8,     8,     8,     8,     3,     8,   182,   489,     4,
       8,     3,     8,     8,   119,   120,   121,   497,   182,   182,
     182,   578,     4,   576,     3,     8,   182,     8,     8,   182,
     371,     4,   185,   486,     4,   183,     4,   573,   182,     5,
     182,     7,   579,   580,   581,     3,     6,   157,   160,   161,
     162,   163,   582,   583,   584,   586,   587,   588,   589,   580,
     585,     4,     4,     4,   590,     3,     8,     4,   185,   183,
     183,     4,   583,   182,   182
  };

  const unsigned short
  Dhcp6Parser::yyr1_[] =
  {
       0,   186,   188,   187,   189,   187,   190,   187,   191,   187,
     192,   187,   193,   187,   194,   187,   195,   187,   196,   187,
     197,   187,   198,   187,   199,   187,   200,   187,   201,   187,
     202,   187,   203,   203,   203,   203,   203,   203,   203,   204,
     206,   205,   207,   208,   208,   209,   209,   211,   210,   212,
     212,   213,   213,   215,   214,   216,   216,   217,   217,   218,
     220,   219,   221,   221,   222,   222,   222,   222,   222,   222,
     224,   223,   226,   225,   227,   227,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   230,
     229,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   244,   243,   246,   245,   248,   247,   249,
     249,   250,   250,   250,   250,   250,   252,   251,   253,   255,
     254,   257,   256,   259,   258,   260,   260,   261,   261,   263,
     262,   264,   264,   265,   265,   265,   265,   265,   265,   265,
     265,   265,   265,   265,   265,   265,   265,   265,   265,   265,
     265,   265,   265,   267,   266,   268,   268,   268,   268,   270,
     269,   272,   271,   274,   273,   275,   277,   276,   278,   279,
     280,   281,   282,   283,   284,   285,   287,   286,   288,   290,
     289,   292,   291,   294,   293,   296,   295,   297,   297,   298,
     300,   299,   302,   301,   303,   303,   304,   304,   305,   306,
     308,   307,   309,   309,   310,   310,   310,   311,   312,   314,
     313,   316,   315,   317,   317,   318,   318,   320,   319,   322,
     321,   323,   323,   323,   324,   324,   326,   325,   328,   327,
     330,   329,   331,   331,   332,   332,   332,   332,   332,   332,
     333,   334,   335,   336,   337,   338,   340,   339,   341,   341,
     342,   342,   344,   343,   346,   345,   347,   347,   348,   348,
     348,   348,   348,   348,   348,   348,   348,   348,   348,   348,
     348,   348,   348,   348,   348,   348,   348,   348,   348,   348,
     348,   348,   348,   348,   348,   350,   349,   352,   351,   354,
     353,   356,   355,   358,   357,   360,   359,   361,   361,   361,
     361,   362,   363,   365,   364,   366,   366,   367,   367,   369,
     368,   370,   370,   371,   371,   371,   371,   371,   371,   371,
     371,   371,   371,   371,   371,   371,   371,   371,   371,   371,
     371,   371,   371,   371,   371,   371,   371,   373,   372,   375,
     374,   376,   376,   377,   377,   379,   378,   381,   380,   382,
     382,   383,   383,   384,   384,   384,   384,   384,   384,   384,
     384,   384,   384,   385,   386,   387,   389,   388,   391,   390,
     393,   392,   394,   396,   395,   397,   399,   398,   400,   400,
     401,   401,   403,   402,   405,   404,   406,   406,   407,   407,
     408,   408,   408,   408,   408,   408,   408,   408,   408,   409,
     411,   410,   412,   413,   414,   415,   417,   416,   418,   418,
     419,   419,   421,   420,   423,   422,   424,   424,   425,   425,
     425,   425,   425,   425,   425,   427,   426,   429,   428,   431,
     430,   433,   432,   434,   434,   435,   435,   437,   436,   439,
     438,   440,   440,   441,   441,   441,   441,   441,   441,   441,
     441,   441,   441,   441,   443,   442,   444,   446,   445,   447,
     448,   450,   449,   451,   451,   452,   452,   454,   453,   456,
     455,   457,   457,   458,   458,   459,   459,   459,   459,   459,
     459,   459,   459,   459,   459,   459,   461,   460,   463,   462,
     465,   464,   467,   466,   469,   468,   471,   470,   473,   472,
     475,   474,   476,   476,   478,   477,   480,   479,   481,   481,
     483,   482,   484,   484,   485,   485,   486,   486,   486,   486,
     486,   486,   486,   487,   489,   488,   490,   492,   491,   493,
     493,   494,   494,   494,   494,   494,   494,   494,   494,   494,
     496,   495,   497,   497,   497,   498,   500,   499,   501,   502,
     503,   505,   504,   506,   506,   507,   507,   507,   507,   507,
     509,   508,   511,   510,   513,   512,   515,   514,   517,   516,
     518,   518,   519,   519,   519,   519,   519,   519,   519,   519,
     519,   519,   519,   519,   519,   519,   519,   519,   519,   519,
     520,   522,   521,   524,   523,   525,   527,   526,   528,   529,
     531,   530,   532,   532,   534,   533,   535,   536,   538,   537,
     539,   539,   539,   539,   539,   541,   540,   543,   542,   545,
     544,   547,   546,   549,   548,   551,   550,   553,   552,   555,
     554,   556,   556,   557,   557,   559,   558,   560,   562,   561,
     564,   563,   565,   565,   566,   568,   567,   569,   569,   571,
     570,   572,   572,   573,   573,   573,   573,   573,   573,   573,
     574,   576,   575,   578,   577,   579,   579,   581,   580,   582,
     582,   583,   583,   583,   583,   583,   585,   584,   586,   587,
     588,   590,   589
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       6,     0,     6,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     3,     0,
       4,     0,     4,     0,     4,     0,     6,     1,     3,     1,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     0,
       6,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     1,     1,     1,
       1,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     0,
       4,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     0,     4,     0,     4,
       0,     4,     1,     0,     4,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     4,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     1,     1,     0,     4,     0,     6,     1,     3,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     3,     0,     4,     3,     3,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     3,     3,     0,     4,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     1,     1,     0,     6,     3,     0,     6,
       0,     4,     1,     3,     1,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     3,     3,
       3,     0,     4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp6Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"", "\"data-directory\"",
  "\"config-control\"", "\"config-databases\"",
  "\"config-fetch-wait-time\"", "\"interfaces-config\"", "\"interfaces\"",
  "\"re-detect\"", "\"lease-database\"", "\"hosts-database\"",
  "\"hosts-databases\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"", "\"host\"",
  "\"port\"", "\"persist\"", "\"lfc-interval\"", "\"readonly\"",
  "\"connect-timeout\"", "\"contact-points\"", "\"max-reconnect-tries\"",
  "\"reconnect-wait-time\"", "\"keyspace\"", "\"consistency\"",
  "\"serial-consistency\"", "\"request-timeout\"", "\"tcp-keepalive\"",
  "\"tcp-nodelay\"", "\"preferred-lifetime\"",
  "\"min-preferred-lifetime\"", "\"max-preferred-lifetime\"",
  "\"valid-lifetime\"", "\"min-valid-lifetime\"", "\"max-valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"calculate-tee-times\"",
  "\"t1-percent\"", "\"t2-percent\"", "\"decline-probation-period\"",
  "\"server-tag\"", "\"subnet6\"", "\"option-def\"", "\"option-data\"",
  "\"name\"", "\"data\"", "\"code\"", "\"space\"", "\"csv-format\"",
  "\"always-send\"", "\"record-types\"", "\"encapsulate\"", "\"array\"",
  "\"pools\"", "\"pool\"", "\"pd-pools\"", "\"prefix\"", "\"prefix-len\"",
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
  "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"", "\"Dhcp4\"",
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
  "$@21", "global_params", "global_param", "data_directory", "$@22",
  "preferred_lifetime", "min_preferred_lifetime", "max_preferred_lifetime",
  "valid_lifetime", "min_valid_lifetime", "max_valid_lifetime",
  "renew_timer", "rebind_timer", "calculate_tee_times", "t1_percent",
  "t2_percent", "decline_probation_period", "server_tag", "$@23",
  "interfaces_config", "$@24", "sub_interfaces6", "$@25",
  "interfaces_config_params", "interfaces_config_param", "interfaces_list",
  "$@26", "re_detect", "lease_database", "$@27", "hosts_database", "$@28",
  "hosts_databases", "$@29", "database_list", "not_empty_database_list",
  "database", "$@30", "database_map_params", "database_map_param",
  "database_type", "$@31", "db_type", "user", "$@32", "password", "$@33",
  "host", "$@34", "port", "name", "$@35", "persist", "lfc_interval",
  "readonly", "connect_timeout", "reconnect_wait_time", "request_timeout",
  "tcp_keepalive", "tcp_nodelay", "contact_points", "$@36",
  "max_reconnect_tries", "keyspace", "$@37", "consistency", "$@38",
  "serial_consistency", "$@39", "sanity_checks", "$@40",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@41",
  "mac_sources", "$@42", "mac_sources_list", "mac_sources_value",
  "duid_id", "string_id", "host_reservation_identifiers", "$@43",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@44",
  "hooks_libraries", "$@45", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@46",
  "sub_hooks_library", "$@47", "hooks_params", "hooks_param", "library",
  "$@48", "parameters", "$@49", "expired_leases_processing", "$@50",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@51",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@52",
  "sub_subnet6", "$@53", "subnet6_params", "subnet6_param", "subnet",
  "$@54", "interface", "$@55", "interface_id", "$@56", "client_class",
  "$@57", "require_client_classes", "$@58", "reservation_mode", "$@59",
  "hr_mode", "id", "rapid_commit", "shared_networks", "$@60",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@61", "shared_network_params", "shared_network_param",
  "option_def_list", "$@62", "sub_option_def_list", "$@63",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@64", "sub_option_def", "$@65",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@66",
  "option_def_record_types", "$@67", "space", "$@68", "option_def_space",
  "option_def_encapsulate", "$@69", "option_def_array", "option_data_list",
  "$@70", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@71", "sub_option_data", "$@72",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@73",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@74", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@75", "sub_pool6", "$@76",
  "pool_params", "pool_param", "pool_entry", "$@77", "user_context",
  "$@78", "comment", "$@79", "pd_pools_list", "$@80",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@81", "sub_pd_pool", "$@82", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@83", "pd_prefix_len", "excluded_prefix", "$@84",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@85",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@86", "sub_reservation", "$@87", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@88", "prefixes", "$@89", "duid", "$@90", "hw_address", "$@91",
  "hostname", "$@92", "flex_id_value", "$@93",
  "reservation_client_classes", "$@94", "relay", "$@95", "relay_map",
  "ip_address", "$@96", "client_classes", "$@97", "client_classes_list",
  "client_class_entry", "$@98", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@99", "only_if_required",
  "server_id", "$@100", "server_id_params", "server_id_param",
  "server_id_type", "$@101", "duid_type", "htype", "identifier", "$@102",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@103",
  "control_socket_params", "control_socket_param", "socket_type", "$@104",
  "socket_name", "$@105", "dhcp_queue_control", "$@106", "dhcp_ddns",
  "$@107", "sub_dhcp_ddns", "$@108", "dhcp_ddns_params", "dhcp_ddns_param",
  "enable_updates", "qualifying_suffix", "$@109", "server_ip", "$@110",
  "server_port", "sender_ip", "$@111", "sender_port", "max_queue_size",
  "ncr_protocol", "$@112", "ncr_protocol_value", "ncr_format", "$@113",
  "override_no_update", "override_client_update", "replace_client_name",
  "$@114", "replace_client_name_value", "generated_prefix", "$@115",
  "hostname_char_set", "$@116", "hostname_char_replacement", "$@117",
  "dhcp4_json_object", "$@118", "dhcpddns_json_object", "$@119",
  "control_agent_json_object", "$@120", "config_control", "$@121",
  "sub_config_control", "$@122", "config_control_params",
  "config_control_param", "config_databases", "$@123",
  "config_fetch_wait_time", "logging_object", "$@124", "sub_logging",
  "$@125", "logging_params", "logging_param", "loggers", "$@126",
  "loggers_entries", "logger_entry", "$@127", "logger_params",
  "logger_param", "debuglevel", "severity", "$@128", "output_options_list",
  "$@129", "output_options_list_content", "output_entry", "$@130",
  "output_params_list", "output_params", "output", "$@131", "flush",
  "maxsize", "maxver", "pattern", "$@132", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short
  Dhcp6Parser::yyrline_[] =
  {
       0,   270,   270,   270,   271,   271,   272,   272,   273,   273,
     274,   274,   275,   275,   276,   276,   277,   277,   278,   278,
     279,   279,   280,   280,   281,   281,   282,   282,   283,   283,
     284,   284,   292,   293,   294,   295,   296,   297,   298,   301,
     306,   306,   317,   320,   321,   324,   328,   335,   335,   342,
     343,   346,   350,   357,   357,   364,   365,   368,   372,   383,
     393,   393,   408,   409,   413,   414,   415,   416,   417,   418,
     421,   421,   436,   436,   445,   446,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   496,
     496,   504,   509,   514,   519,   524,   529,   534,   539,   544,
     549,   554,   559,   564,   564,   572,   572,   583,   583,   592,
     593,   596,   597,   598,   599,   600,   603,   603,   613,   619,
     619,   631,   631,   643,   643,   653,   654,   657,   658,   661,
     661,   671,   672,   675,   676,   677,   678,   679,   680,   681,
     682,   683,   684,   685,   686,   687,   688,   689,   690,   691,
     692,   693,   694,   697,   697,   704,   705,   706,   707,   710,
     710,   718,   718,   726,   726,   734,   739,   739,   747,   752,
     757,   762,   767,   772,   777,   782,   787,   787,   795,   800,
     800,   808,   808,   816,   816,   824,   824,   834,   835,   837,
     839,   839,   857,   857,   867,   868,   871,   872,   875,   880,
     885,   885,   895,   896,   899,   900,   901,   904,   909,   916,
     916,   926,   926,   936,   937,   940,   941,   944,   944,   954,
     954,   964,   965,   966,   969,   970,   973,   973,   981,   981,
     989,   989,  1000,  1001,  1004,  1005,  1006,  1007,  1008,  1009,
    1012,  1017,  1022,  1027,  1032,  1037,  1045,  1045,  1058,  1059,
    1062,  1063,  1070,  1070,  1096,  1096,  1107,  1108,  1112,  1113,
    1114,  1115,  1116,  1117,  1118,  1119,  1120,  1121,  1122,  1123,
    1124,  1125,  1126,  1127,  1128,  1129,  1130,  1131,  1132,  1133,
    1134,  1135,  1136,  1137,  1138,  1141,  1141,  1149,  1149,  1157,
    1157,  1165,  1165,  1173,  1173,  1183,  1183,  1190,  1191,  1192,
    1193,  1196,  1201,  1209,  1209,  1220,  1221,  1225,  1226,  1229,
    1229,  1237,  1238,  1241,  1242,  1243,  1244,  1245,  1246,  1247,
    1248,  1249,  1250,  1251,  1252,  1253,  1254,  1255,  1256,  1257,
    1258,  1259,  1260,  1261,  1262,  1263,  1264,  1271,  1271,  1284,
    1284,  1293,  1294,  1297,  1298,  1303,  1303,  1318,  1318,  1332,
    1333,  1336,  1337,  1340,  1341,  1342,  1343,  1344,  1345,  1346,
    1347,  1348,  1349,  1352,  1354,  1359,  1361,  1361,  1369,  1369,
    1377,  1377,  1385,  1387,  1387,  1395,  1404,  1404,  1416,  1417,
    1422,  1423,  1428,  1428,  1440,  1440,  1452,  1453,  1458,  1459,
    1464,  1465,  1466,  1467,  1468,  1469,  1470,  1471,  1472,  1475,
    1477,  1477,  1485,  1487,  1489,  1494,  1502,  1502,  1514,  1515,
    1518,  1519,  1522,  1522,  1532,  1532,  1541,  1542,  1545,  1546,
    1547,  1548,  1549,  1550,  1551,  1554,  1554,  1562,  1562,  1587,
    1587,  1617,  1617,  1629,  1630,  1633,  1634,  1637,  1637,  1649,
    1649,  1661,  1662,  1665,  1666,  1667,  1668,  1669,  1670,  1671,
    1672,  1673,  1674,  1675,  1678,  1678,  1686,  1691,  1691,  1699,
    1704,  1712,  1712,  1722,  1723,  1726,  1727,  1730,  1730,  1739,
    1739,  1748,  1749,  1752,  1753,  1757,  1758,  1759,  1760,  1761,
    1762,  1763,  1764,  1765,  1766,  1767,  1770,  1770,  1780,  1780,
    1790,  1790,  1798,  1798,  1806,  1806,  1814,  1814,  1822,  1822,
    1835,  1835,  1845,  1846,  1849,  1849,  1860,  1860,  1870,  1871,
    1874,  1874,  1884,  1885,  1888,  1889,  1892,  1893,  1894,  1895,
    1896,  1897,  1898,  1901,  1903,  1903,  1911,  1919,  1919,  1931,
    1932,  1935,  1936,  1937,  1938,  1939,  1940,  1941,  1942,  1943,
    1946,  1946,  1953,  1954,  1955,  1958,  1963,  1963,  1971,  1976,
    1983,  1990,  1990,  2000,  2001,  2004,  2005,  2006,  2007,  2008,
    2011,  2011,  2019,  2019,  2029,  2029,  2069,  2069,  2081,  2081,
    2091,  2092,  2095,  2096,  2097,  2098,  2099,  2100,  2101,  2102,
    2103,  2104,  2105,  2106,  2107,  2108,  2109,  2110,  2111,  2112,
    2115,  2120,  2120,  2128,  2128,  2136,  2141,  2141,  2149,  2154,
    2159,  2159,  2167,  2168,  2171,  2171,  2179,  2184,  2189,  2189,
    2197,  2200,  2203,  2206,  2209,  2215,  2215,  2223,  2223,  2231,
    2231,  2241,  2241,  2248,  2248,  2255,  2255,  2264,  2264,  2275,
    2275,  2285,  2286,  2290,  2291,  2294,  2294,  2304,  2314,  2314,
    2324,  2324,  2335,  2336,  2340,  2344,  2344,  2356,  2357,  2361,
    2361,  2369,  2370,  2373,  2374,  2375,  2376,  2377,  2378,  2379,
    2382,  2387,  2387,  2395,  2395,  2405,  2406,  2409,  2409,  2417,
    2418,  2421,  2422,  2423,  2424,  2425,  2428,  2428,  2436,  2441,
    2446,  2451,  2451
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
#line 5265 "dhcp6_parser.cc" // lalr1.cc:1218
#line 2459 "dhcp6_parser.yy" // lalr1.cc:1219


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
