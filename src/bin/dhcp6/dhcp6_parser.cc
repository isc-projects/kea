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
      case 210: // value
      case 214: // map_value
      case 255: // ddns_replace_client_name_value
      case 289: // db_type
      case 383: // hr_mode
      case 519: // duid_type
      case 554: // ncr_protocol_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 192: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 191: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 190: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 189: // "constant string"
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
      case 210: // value
      case 214: // map_value
      case 255: // ddns_replace_client_name_value
      case 289: // db_type
      case 383: // hr_mode
      case 519: // duid_type
      case 554: // ncr_protocol_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 192: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 191: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 190: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 189: // "constant string"
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
      case 210: // value
      case 214: // map_value
      case 255: // ddns_replace_client_name_value
      case 289: // db_type
      case 383: // hr_mode
      case 519: // duid_type
      case 554: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 192: // "boolean"
        value.move< bool > (that.value);
        break;

      case 191: // "floating point"
        value.move< double > (that.value);
        break;

      case 190: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 189: // "constant string"
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
            case 189: // "constant string"

#line 268 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< std::string > (); }
#line 398 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 190: // "integer"

#line 268 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 405 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 191: // "floating point"

#line 268 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< double > (); }
#line 412 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 192: // "boolean"

#line 268 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< bool > (); }
#line 419 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 210: // value

#line 268 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 426 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 214: // map_value

#line 268 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 433 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 255: // ddns_replace_client_name_value

#line 268 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 440 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 289: // db_type

#line 268 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 447 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 383: // hr_mode

#line 268 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 454 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 519: // duid_type

#line 268 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 461 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 554: // ncr_protocol_value

#line 268 "dhcp6_parser.yy" // lalr1.cc:672
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
      case 210: // value
      case 214: // map_value
      case 255: // ddns_replace_client_name_value
      case 289: // db_type
      case 383: // hr_mode
      case 519: // duid_type
      case 554: // ncr_protocol_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 192: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 191: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 190: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 189: // "constant string"
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
#line 277 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 727 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 4:
#line 278 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.CONFIG; }
#line 733 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 6:
#line 279 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP6; }
#line 739 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 8:
#line 280 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 745 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 10:
#line 281 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.SUBNET6; }
#line 751 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 12:
#line 282 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.POOLS; }
#line 757 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 14:
#line 283 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 763 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 16:
#line 284 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 769 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 18:
#line 285 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP6; }
#line 775 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 20:
#line 286 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 781 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 22:
#line 287 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 787 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 24:
#line 288 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 793 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 26:
#line 289 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 799 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 28:
#line 290 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.LOGGING; }
#line 805 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 30:
#line 291 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 811 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 32:
#line 299 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 817 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 33:
#line 300 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 823 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 34:
#line 301 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 829 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 35:
#line 302 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 835 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 36:
#line 303 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 841 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 37:
#line 304 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 847 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 38:
#line 305 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 853 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 39:
#line 308 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 862 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 40:
#line 313 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 873 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 41:
#line 318 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 883 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 42:
#line 324 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 889 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 45:
#line 331 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 898 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 46:
#line 335 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 908 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 47:
#line 342 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 917 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 48:
#line 345 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // list parsing complete. Put any sanity checking here
}
#line 925 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 51:
#line 353 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 934 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 52:
#line 357 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 943 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 53:
#line 364 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // List parsing about to start
}
#line 951 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 54:
#line 366 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 960 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 57:
#line 375 "dhcp6_parser.yy" // lalr1.cc:907
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 969 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 58:
#line 379 "dhcp6_parser.yy" // lalr1.cc:907
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 978 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 59:
#line 390 "dhcp6_parser.yy" // lalr1.cc:907
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 989 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 60:
#line 400 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1000 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 61:
#line 405 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 428 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 435 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1036 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 72:
#line 443 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1046 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 73:
#line 447 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No global parameter is required
    // parsing completed
}
#line 1055 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 125:
#line 509 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1063 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 126:
#line 511 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr datadir(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1073 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 127:
#line 517 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1082 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 128:
#line 522 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1091 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 129:
#line 527 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1100 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 130:
#line 532 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1109 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 131:
#line 537 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1118 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 132:
#line 542 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1127 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 133:
#line 547 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1136 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 134:
#line 552 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1145 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 135:
#line 557 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1154 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 136:
#line 562 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1163 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 137:
#line 567 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1172 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 138:
#line 572 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1181 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 139:
#line 577 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1190 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 140:
#line 582 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1199 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 141:
#line 587 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1208 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 142:
#line 592 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1216 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 143:
#line 594 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1225 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 144:
#line 600 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1233 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 145:
#line 603 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1241 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 146:
#line 606 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1249 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 147:
#line 609 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1257 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 148:
#line 612 "dhcp6_parser.yy" // lalr1.cc:907
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1266 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 149:
#line 618 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1274 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 150:
#line 620 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1284 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 151:
#line 626 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1292 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 152:
#line 628 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1302 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 153:
#line 634 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1310 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 154:
#line 636 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1320 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 155:
#line 642 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1328 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 156:
#line 644 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1338 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 157:
#line 650 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1346 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 158:
#line 652 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1356 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 159:
#line 658 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1367 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 160:
#line 663 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1377 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 161:
#line 669 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1387 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 162:
#line 673 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1396 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 170:
#line 689 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1407 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 171:
#line 694 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1416 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 172:
#line 699 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1425 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 173:
#line 705 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1436 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 174:
#line 710 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1447 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 175:
#line 717 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1458 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 176:
#line 722 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1469 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 177:
#line 729 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1480 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 178:
#line 734 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1489 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 183:
#line 747 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1499 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 184:
#line 751 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1509 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 208:
#line 784 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1517 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 209:
#line 786 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1526 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 210:
#line 791 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1532 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 211:
#line 792 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1538 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 212:
#line 793 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1544 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 213:
#line 794 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1550 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 214:
#line 797 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1558 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 215:
#line 799 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1568 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 216:
#line 805 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1576 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 217:
#line 807 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1586 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 218:
#line 813 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1594 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 219:
#line 815 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1604 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 220:
#line 821 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1613 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 221:
#line 826 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1621 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 222:
#line 828 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1631 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 223:
#line 834 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1640 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 224:
#line 839 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1649 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 225:
#line 844 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1658 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 226:
#line 849 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1667 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 227:
#line 854 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1676 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 228:
#line 859 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1685 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 229:
#line 864 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1694 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 230:
#line 869 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1703 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 231:
#line 874 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1712 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 232:
#line 879 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1720 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 233:
#line 881 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1730 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 234:
#line 887 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1739 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 235:
#line 892 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1747 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 236:
#line 894 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1757 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 237:
#line 900 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1765 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 238:
#line 902 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1775 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 239:
#line 908 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1783 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 240:
#line 910 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1793 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 241:
#line 916 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1804 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 242:
#line 921 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1813 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 246:
#line 931 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1821 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 247:
#line 933 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 1841 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 248:
#line 949 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1852 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 249:
#line 954 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1861 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 254:
#line 967 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1870 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 255:
#line 972 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1879 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 256:
#line 977 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1890 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 257:
#line 982 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1899 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 263:
#line 996 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1908 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 264:
#line 1001 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1917 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 265:
#line 1008 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1928 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 266:
#line 1013 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1937 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 267:
#line 1018 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1948 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 268:
#line 1023 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1957 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 273:
#line 1036 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1967 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 274:
#line 1040 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1977 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 275:
#line 1046 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1987 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 276:
#line 1050 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1997 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 282:
#line 1065 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2005 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 283:
#line 1067 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2015 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 284:
#line 1073 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2023 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 285:
#line 1075 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2032 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 286:
#line 1081 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2043 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 287:
#line 1086 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2053 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 296:
#line 1104 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2062 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 297:
#line 1109 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2071 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 298:
#line 1114 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2080 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 299:
#line 1119 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2089 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 300:
#line 1124 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2098 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 301:
#line 1129 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2107 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 302:
#line 1137 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2118 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 303:
#line 1142 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2127 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 308:
#line 1162 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2137 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 309:
#line 1166 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 2163 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 310:
#line 1188 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2173 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 311:
#line 1192 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2183 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 349:
#line 1241 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2191 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 350:
#line 1243 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2201 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 351:
#line 1249 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2209 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 352:
#line 1251 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2219 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 353:
#line 1257 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2227 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 354:
#line 1259 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2237 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 355:
#line 1265 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2245 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 356:
#line 1267 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2255 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 357:
#line 1273 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2266 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 358:
#line 1278 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2275 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 359:
#line 1283 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2283 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 360:
#line 1285 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2292 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 361:
#line 1290 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2298 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 362:
#line 1291 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2304 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 363:
#line 1292 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2310 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 364:
#line 1293 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2316 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 365:
#line 1296 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2325 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 366:
#line 1301 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2334 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 367:
#line 1309 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2345 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 368:
#line 1314 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2354 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 373:
#line 1329 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2364 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 374:
#line 1333 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 2372 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 409:
#line 1379 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2383 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 410:
#line 1384 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2392 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 411:
#line 1392 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2401 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 412:
#line 1395 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // parsing completed
}
#line 2409 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 417:
#line 1411 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2419 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 418:
#line 1415 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2431 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 419:
#line 1426 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2441 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 420:
#line 1430 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2453 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 436:
#line 1462 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2462 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 438:
#line 1469 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2470 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 439:
#line 1471 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2480 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 440:
#line 1477 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2488 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 441:
#line 1479 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2498 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 442:
#line 1485 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2506 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 443:
#line 1487 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2516 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 445:
#line 1495 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2524 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 446:
#line 1497 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2534 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 447:
#line 1503 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2543 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 448:
#line 1512 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2554 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 449:
#line 1517 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2563 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 454:
#line 1536 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2573 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 455:
#line 1540 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2582 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 456:
#line 1548 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2592 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 457:
#line 1552 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2601 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 472:
#line 1585 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2609 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 473:
#line 1587 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2619 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 476:
#line 1597 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2628 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 477:
#line 1602 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2637 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 478:
#line 1610 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2648 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 479:
#line 1615 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2657 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 484:
#line 1630 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2667 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 485:
#line 1634 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2677 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 486:
#line 1640 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2687 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 487:
#line 1644 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2696 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 497:
#line 1662 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2704 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 498:
#line 1664 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2714 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 499:
#line 1670 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2722 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 500:
#line 1672 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 2749 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 501:
#line 1695 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2757 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 502:
#line 1697 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 2786 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 503:
#line 1725 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2797 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 504:
#line 1730 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2806 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 509:
#line 1745 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2816 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 510:
#line 1749 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2828 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 511:
#line 1757 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2838 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 512:
#line 1761 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2850 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 526:
#line 1786 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2858 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 527:
#line 1788 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2868 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 528:
#line 1794 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2877 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 529:
#line 1799 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2885 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 530:
#line 1801 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2895 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 531:
#line 1807 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2904 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 532:
#line 1812 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2913 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 533:
#line 1820 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2924 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 534:
#line 1825 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2933 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 539:
#line 1838 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2943 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 540:
#line 1842 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2952 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 541:
#line 1847 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2962 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 542:
#line 1851 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2971 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 558:
#line 1878 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2982 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 559:
#line 1883 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2991 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 560:
#line 1888 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3002 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 561:
#line 1893 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3011 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 562:
#line 1898 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3019 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 563:
#line 1900 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3029 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 564:
#line 1906 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3037 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 565:
#line 1908 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3047 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 566:
#line 1914 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3055 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 567:
#line 1916 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3065 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 568:
#line 1922 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3073 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 569:
#line 1924 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3083 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 570:
#line 1930 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3094 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 571:
#line 1935 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3103 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 572:
#line 1943 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3114 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 573:
#line 1948 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3123 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 576:
#line 1957 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3131 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 577:
#line 1959 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3141 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 578:
#line 1968 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3152 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 579:
#line 1973 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3161 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 582:
#line 1982 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3171 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 583:
#line 1986 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3181 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 596:
#line 2011 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3189 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 597:
#line 2013 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3199 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 598:
#line 2019 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3208 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 599:
#line 2027 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3219 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 600:
#line 2032 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3230 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 612:
#line 2054 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 3238 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 613:
#line 2056 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3247 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 614:
#line 2061 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3253 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 615:
#line 2062 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3259 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 616:
#line 2063 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3265 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 617:
#line 2066 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3274 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 618:
#line 2071 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3282 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 619:
#line 2073 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3292 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 620:
#line 2079 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3301 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 621:
#line 2084 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3310 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 622:
#line 2091 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3319 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 623:
#line 2098 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3330 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 624:
#line 2103 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3339 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 632:
#line 2119 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3347 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 633:
#line 2121 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3357 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 634:
#line 2127 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3365 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 635:
#line 2129 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3375 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 636:
#line 2137 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3383 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 637:
#line 2139 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 3423 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 638:
#line 2177 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3434 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 639:
#line 2182 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3445 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 640:
#line 2189 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3455 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 641:
#line 2193 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3465 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 662:
#line 2223 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3474 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 663:
#line 2228 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3482 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 664:
#line 2230 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3492 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 665:
#line 2236 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3500 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 666:
#line 2238 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3510 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 667:
#line 2244 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3519 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 668:
#line 2249 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3527 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 669:
#line 2251 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3537 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 670:
#line 2257 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3546 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 671:
#line 2262 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3555 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 672:
#line 2267 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3563 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 673:
#line 2269 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3572 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 674:
#line 2275 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3578 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 675:
#line 2276 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3584 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 676:
#line 2279 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3592 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 677:
#line 2281 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3602 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 678:
#line 2288 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3611 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 679:
#line 2294 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3620 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 680:
#line 2300 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3628 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 681:
#line 2302 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3637 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 682:
#line 2308 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3645 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 683:
#line 2310 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3655 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 684:
#line 2317 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3663 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 685:
#line 2319 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3673 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 686:
#line 2326 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3681 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 687:
#line 2328 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3691 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 688:
#line 2336 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3699 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 689:
#line 2338 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3708 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 690:
#line 2343 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3716 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 691:
#line 2345 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3725 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 692:
#line 2350 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3733 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 693:
#line 2352 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3742 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 694:
#line 2359 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3753 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 695:
#line 2364 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3763 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 696:
#line 2370 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3773 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 697:
#line 2374 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No config_control params are required
    // parsing completed
}
#line 3782 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 702:
#line 2389 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3793 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 703:
#line 2394 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3802 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 704:
#line 2399 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3811 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 705:
#line 2409 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3822 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 706:
#line 2414 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3831 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 707:
#line 2419 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3841 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 708:
#line 2423 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // parsing completed
}
#line 3849 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 712:
#line 2439 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3860 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 713:
#line 2444 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3869 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 716:
#line 2456 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3879 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 717:
#line 2460 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3887 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 727:
#line 2477 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3896 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 728:
#line 2482 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3904 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 729:
#line 2484 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3914 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 730:
#line 2490 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3925 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 731:
#line 2495 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3934 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 734:
#line 2504 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3944 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 735:
#line 2508 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3952 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 743:
#line 2523 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3960 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 744:
#line 2525 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3970 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 745:
#line 2531 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3979 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 746:
#line 2536 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3988 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 747:
#line 2541 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3997 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 748:
#line 2546 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4005 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 749:
#line 2548 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4015 "dhcp6_parser.cc" // lalr1.cc:907
    break;


#line 4019 "dhcp6_parser.cc" // lalr1.cc:907
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


  const short Dhcp6Parser::yypact_ninf_ = -921;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     197,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,    41,    43,    73,    85,
      87,    97,   101,   145,   206,   208,   220,   221,   232,   247,
     259,   268,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,    43,  -130,    25,   111,    27,   621,   135,   178,
     181,   157,    66,   261,     4,   409,   -89,   123,  -921,   236,
     274,   282,   279,   292,  -921,  -921,  -921,  -921,  -921,   293,
    -921,    37,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,   294,   315,   319,   322,   362,   393,
     402,   403,   405,   412,   413,   415,  -921,   416,   417,   419,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,   421,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,    48,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,   423,  -921,
      92,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,   426,   427,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,   125,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,   140,  -921,
    -921,  -921,  -921,  -921,   428,  -921,   429,   430,  -921,  -921,
    -921,  -921,  -921,  -921,   177,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,   357,   384,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,   431,  -921,  -921,   433,  -921,  -921,  -921,   436,
    -921,  -921,   434,   410,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,   437,   443,  -921,
    -921,  -921,  -921,   445,   432,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,   260,  -921,  -921,
    -921,   450,  -921,  -921,   453,  -921,   454,   455,  -921,  -921,
     456,   464,  -921,  -921,  -921,  -921,  -921,  -921,  -921,   264,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,   273,  -921,  -921,  -921,
     465,   291,  -921,  -921,  -921,  -921,    43,    43,  -921,   283,
     469,   470,   471,   472,   476,  -921,    25,  -921,   480,   481,
     482,   484,   486,   496,   313,   314,   320,   323,   325,   326,
     327,   329,   328,   316,   318,   331,   501,   332,   334,   335,
     524,   525,   527,   529,   530,   531,   532,   533,   534,   535,
     536,   537,   538,   539,   540,   557,   558,   559,   560,   375,
     562,   563,   566,   567,   568,   569,   111,  -921,   570,   388,
      27,  -921,   571,   572,   573,   574,   575,   391,   390,   579,
     580,   581,   621,  -921,   582,   135,  -921,   583,   398,   585,
     400,   401,   178,  -921,   588,   589,   590,   592,   593,   595,
     596,  -921,   181,  -921,   597,   599,   414,   601,   602,   603,
     418,  -921,    66,   604,   420,   422,  -921,   261,   607,   609,
      75,  -921,   424,   611,   613,   435,   614,   438,   439,   615,
     617,   440,   441,   618,   619,   620,   622,   409,  -921,   -89,
    -921,   623,   444,   123,  -921,  -921,  -921,   626,   624,   630,
      43,    43,    43,  -921,   451,   632,   635,   636,   637,   640,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,   457,  -921,  -921,  -921,   -11,   458,   459,   644,
     645,   646,   648,   463,   -10,   652,   653,   654,   655,   657,
     671,   672,   679,   678,   680,  -921,   681,   648,   682,   473,
     502,   685,  -921,   687,  -921,  -921,   688,   694,   511,   512,
     513,  -921,  -921,   687,   514,   705,  -921,   526,  -921,   528,
    -921,   541,  -921,  -921,  -921,   687,   687,   687,   542,   543,
     544,   546,  -921,   547,   548,  -921,   549,   550,   551,  -921,
    -921,   552,  -921,  -921,  -921,   553,    43,  -921,  -921,   554,
     555,  -921,   556,  -921,  -921,   126,   564,  -921,  -921,   -11,
     584,   586,   587,  -921,  -921,   708,  -921,  -921,    43,   111,
     -89,  -921,  -921,  -921,  -921,   123,    27,   275,   275,   707,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,   709,
     712,   713,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
     714,   -75,    43,    15,   625,   715,   717,   721,   214,    58,
      95,  -921,   409,  -921,  -921,   722,  -921,  -921,   739,   740,
    -921,  -921,  -921,  -921,  -921,   -65,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,   707,  -921,   317,   340,   343,
     344,  -921,  -921,  -921,  -921,   755,   756,   764,   767,   768,
    -921,   770,   773,  -921,  -921,  -921,   774,   775,   778,   779,
    -921,   346,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,   347,  -921,   780,   781,  -921,  -921,   783,
     782,  -921,  -921,   786,   792,  -921,  -921,   790,   794,  -921,
    -921,   793,   795,  -921,  -921,  -921,    52,  -921,  -921,  -921,
     796,  -921,  -921,  -921,    63,  -921,  -921,  -921,  -921,   350,
    -921,  -921,  -921,    99,  -921,  -921,   797,   798,  -921,  -921,
     799,   801,  -921,   803,   804,   807,   808,   809,   810,   353,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,   811,
     812,   814,  -921,  -921,  -921,  -921,   354,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,   360,  -921,
    -921,  -921,   361,  -921,   109,  -921,   631,  -921,   813,   818,
    -921,  -921,   816,   820,  -921,  -921,  -921,   817,  -921,   821,
    -921,  -921,  -921,  -921,   822,   824,   825,   826,   610,   639,
     634,   641,   642,   830,   647,   649,   831,   832,   834,   650,
     651,   656,   659,   275,  -921,  -921,   275,  -921,   707,   621,
    -921,   709,    66,  -921,   712,   261,  -921,   713,   704,  -921,
     714,   -75,  -921,  -921,    15,  -921,   838,   625,  -921,   256,
     715,  -921,   181,  -921,   717,     4,  -921,   721,   660,   661,
     662,   663,   664,   665,   214,  -921,   839,   840,   666,   667,
     668,    58,  -921,   841,   842,    95,  -921,  -921,   -12,   722,
    -921,  -921,   853,   844,   135,  -921,   739,   178,  -921,   740,
     856,  -921,  -921,   228,   673,   677,   683,  -921,  -921,  -921,
    -921,  -921,   684,  -921,  -921,   686,   691,   693,  -921,  -921,
    -921,  -921,  -921,   383,  -921,   385,  -921,   859,  -921,   862,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,   386,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,   695,  -921,
    -921,   857,  -921,  -921,  -921,  -921,  -921,   879,   891,  -921,
    -921,  -921,  -921,  -921,   887,  -921,   387,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,    56,   711,  -921,  -921,  -921,
    -921,   716,   723,  -921,  -921,   893,  -921,  -921,  -921,  -921,
    -921,   395,  -921,  -921,  -921,  -921,  -921,  -921,   726,   396,
    -921,   397,  -921,   727,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
     704,  -921,  -921,   894,   729,  -921,   256,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,   900,   736,   930,   -12,
    -921,  -921,  -921,  -921,  -921,  -921,   746,  -921,  -921,   932,
    -921,   750,  -921,  -921,   936,  -921,  -921,   235,  -921,    35,
     936,  -921,  -921,   942,   946,   950,  -921,   407,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,   972,   789,   800,   802,   979,
      35,  -921,   806,  -921,  -921,  -921,   815,  -921,  -921,  -921
  };

  const unsigned short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   161,     9,
     310,    11,   486,    13,   511,    15,   541,    17,   411,    19,
     419,    21,   456,    23,   275,    25,   640,    27,   707,    29,
     696,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     543,     0,   421,   458,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   705,   688,   690,   692,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   125,   694,
     159,   173,   175,   177,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   157,     0,     0,     0,
     142,   149,   151,   302,   409,   448,   499,   501,   359,   367,
     248,   265,   256,   241,   578,   533,   267,   286,   599,     0,
     623,   636,   638,   153,   155,   712,   124,     0,    74,    76,
      77,    78,    79,    80,    81,    82,    83,    84,   112,   113,
     114,    85,   118,   119,   120,   121,   122,   123,   116,   117,
     110,    88,    89,    90,    91,   107,    92,    94,    93,    98,
      99,    86,   111,    87,    96,    97,   105,   106,   108,    95,
     100,   101,   102,   103,   104,   109,   115,   170,     0,   169,
       0,   163,   165,   166,   167,   168,   478,   503,   349,   351,
     353,     0,     0,   357,   355,   572,   348,   314,   315,   316,
     317,   318,   319,   320,   321,   337,   338,   339,   342,   343,
     344,   345,   346,   347,   340,   341,     0,   312,   325,   326,
     327,   330,   331,   333,   328,   329,   322,   323,   335,   336,
     324,   332,   334,   497,   496,   492,   493,   491,     0,   488,
     490,   494,   495,   526,     0,   529,     0,     0,   525,   519,
     520,   518,   523,   524,     0,   513,   515,   516,   521,   522,
     517,   570,   558,   560,   562,   564,   566,   568,   557,   554,
     555,   556,     0,   544,   545,   549,   550,   547,   551,   552,
     553,   548,     0,   438,   221,     0,   442,   440,   445,     0,
     434,   435,     0,   422,   423,   425,   437,   426,   427,   428,
     444,   429,   430,   431,   432,   433,   472,     0,     0,   470,
     471,   474,   475,     0,   459,   460,   462,   463,   464,   465,
     466,   467,   468,   469,   282,   284,   279,     0,   277,   280,
     281,     0,   663,   665,     0,   668,     0,     0,   672,   676,
       0,     0,   680,   682,   684,   686,   661,   659,   660,     0,
     642,   644,   645,   646,   647,   648,   649,   650,   651,   652,
     653,   654,   655,   656,   657,   658,     0,   709,   711,   702,
       0,     0,   698,   700,   701,    48,     0,     0,    41,     0,
       0,     0,     0,     0,     0,    59,     0,    61,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    73,     0,     0,
       0,   162,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   311,     0,     0,   487,     0,     0,     0,
       0,     0,     0,   512,     0,     0,     0,     0,     0,     0,
       0,   542,     0,   412,     0,     0,     0,     0,     0,     0,
       0,   420,     0,     0,     0,     0,   457,     0,     0,     0,
       0,   276,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   641,     0,
     708,     0,     0,     0,   697,    52,    45,     0,     0,     0,
       0,     0,     0,    63,     0,     0,     0,     0,     0,     0,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,     0,   139,   140,   141,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   622,     0,     0,     0,     0,
       0,     0,    75,     0,   172,   164,     0,     0,     0,     0,
       0,   365,   366,     0,     0,     0,   313,     0,   489,     0,
     528,     0,   531,   532,   514,     0,     0,     0,     0,     0,
       0,     0,   546,     0,     0,   436,     0,     0,     0,   447,
     424,     0,   476,   477,   461,     0,     0,   278,   662,     0,
       0,   667,     0,   670,   671,     0,     0,   678,   679,     0,
       0,     0,     0,   643,   710,     0,   704,   699,     0,     0,
       0,   689,   691,   693,   126,     0,     0,     0,     0,   179,
     158,   144,   145,   146,   147,   148,   143,   150,   152,   304,
     413,   450,    42,   500,   502,   361,   362,   363,   364,   360,
     369,     0,    49,     0,     0,     0,   535,   269,     0,     0,
       0,   637,     0,   154,   156,     0,    53,   171,   480,   505,
     350,   352,   354,   358,   356,     0,   498,   527,   530,   571,
     559,   561,   563,   565,   567,   569,   439,   222,   443,   441,
     446,   473,   283,   285,   664,   666,   669,   674,   675,   673,
     677,   681,   683,   685,   687,   179,    46,     0,     0,     0,
       0,   208,   214,   216,   218,     0,     0,     0,     0,     0,
     232,     0,     0,   235,   237,   239,     0,     0,     0,     0,
     207,     0,   185,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   199,   206,   200,   201,   202,   197,   198,
     203,   204,   205,     0,   183,     0,   180,   181,   308,     0,
     305,   306,   417,     0,   414,   415,   454,     0,   451,   452,
     373,     0,   370,   371,   254,   255,     0,   250,   252,   253,
       0,   263,   264,   260,     0,   258,   261,   262,   246,     0,
     243,   245,   582,     0,   580,   539,     0,   536,   537,   273,
       0,   270,   271,     0,     0,     0,     0,     0,     0,     0,
     288,   290,   291,   292,   293,   294,   295,   612,   618,     0,
       0,     0,   611,   608,   609,   610,     0,   601,   603,   606,
     604,   605,   607,   632,   634,   631,   629,   630,     0,   625,
     627,   628,     0,   716,     0,   714,    55,   484,     0,   481,
     482,   509,     0,   506,   507,   576,   575,     0,   574,     0,
      71,   706,   695,   160,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   174,   176,     0,   178,     0,     0,
     303,     0,   421,   410,     0,   458,   449,     0,     0,   368,
       0,     0,   249,   266,     0,   257,     0,     0,   242,   584,
       0,   579,   543,   534,     0,     0,   268,     0,     0,     0,
       0,     0,     0,     0,     0,   287,     0,     0,     0,     0,
       0,     0,   600,     0,     0,     0,   624,   639,     0,     0,
     713,    57,     0,    56,     0,   479,     0,     0,   504,     0,
       0,   573,   703,     0,     0,     0,     0,   220,   223,   224,
     225,   226,     0,   234,   227,     0,     0,     0,   229,   230,
     231,   228,   186,     0,   182,     0,   307,     0,   416,     0,
     453,   408,   388,   389,   390,   392,   393,   394,   381,   382,
     397,   398,   399,   402,   403,   404,   405,   406,   407,   400,
     401,   377,   378,   379,   380,   386,   387,   385,   391,     0,
     375,   383,   395,   396,   384,   372,   251,   259,     0,   244,
     596,     0,   594,   595,   591,   592,   593,     0,   585,   586,
     588,   589,   590,   581,     0,   538,     0,   272,   296,   297,
     298,   299,   300,   301,   289,     0,     0,   617,   620,   621,
     602,     0,     0,   626,   730,     0,   728,   726,   720,   724,
     725,     0,   718,   722,   723,   721,   715,    54,     0,     0,
     483,     0,   508,     0,   210,   211,   212,   213,   209,   215,
     217,   219,   233,   236,   238,   240,   184,   309,   418,   455,
       0,   374,   247,     0,     0,   583,     0,   540,   274,   614,
     615,   616,   613,   619,   633,   635,     0,     0,     0,     0,
     717,    58,   485,   510,   577,   376,     0,   598,   587,     0,
     727,     0,   719,   597,     0,   729,   734,     0,   732,     0,
       0,   731,   743,     0,     0,     0,   748,     0,   736,   738,
     739,   740,   741,   742,   733,     0,     0,     0,     0,     0,
       0,   735,     0,   745,   746,   747,     0,   737,   744,   749
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,    -5,  -921,  -544,
    -921,   392,  -921,  -921,  -921,  -921,   285,  -921,  -528,  -921,
    -921,  -921,   -74,  -921,  -921,  -921,   577,  -921,  -921,  -921,
    -921,   330,   519,  -921,  -921,   -70,   -58,   -38,   -31,   -30,
     -20,   -17,     1,     9,    12,    13,  -921,    14,    16,    19,
      24,  -921,   337,    26,  -921,    29,  -921,    30,  -921,    32,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,   321,   545,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,   243,  -921,
      62,  -921,  -662,    68,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,   -46,  -921,  -696,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,    45,  -921,  -921,
    -921,  -921,  -921,    54,  -685,  -921,  -921,  -921,  -921,    49,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,    39,  -921,
    -921,  -921,    42,   488,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,    44,  -921,  -921,  -921,  -921,  -921,  -921,  -920,  -921,
    -921,  -921,    69,  -921,  -921,  -921,    70,   561,  -921,  -921,
    -918,  -921,  -917,  -921,    38,  -921,    40,  -921,    36,  -921,
    -921,  -921,  -916,  -921,  -921,  -921,  -921,    61,  -921,  -921,
    -128,   933,  -921,  -921,  -921,  -921,  -921,    72,  -921,  -921,
    -921,    71,  -921,   505,  -921,   -69,  -921,  -921,  -921,  -921,
    -921,   -68,  -921,  -921,  -921,  -921,  -921,    -3,  -921,  -921,
    -921,    74,  -921,  -921,  -921,    77,  -921,   503,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,    23,
    -921,  -921,  -921,    31,   565,  -921,  -921,   -56,  -921,   -15,
    -921,  -921,  -921,  -921,  -921,    28,  -921,  -921,  -921,    33,
     576,  -921,  -921,  -921,  -921,  -921,  -921,  -921,   -60,  -921,
    -921,  -921,    59,  -921,  -921,  -921,    64,  -921,   522,   303,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -915,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,    76,  -921,  -921,  -921,  -117,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,    50,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,    53,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,   333,   504,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,   358,   497,  -921,  -921,  -921,  -921,
    -921,  -921,  -921,   369,   507,   -61,  -921,  -921,    55,  -921,
    -921,  -112,  -921,  -921,  -921,  -921,  -921,  -921,  -138,  -921,
    -921,  -152,  -921,  -921,  -921,  -921,  -921,  -921,  -921
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   693,    92,    93,    43,    72,    89,    90,   717,   896,
     992,   993,   780,    45,    74,   101,   102,   103,   410,    47,
      75,   157,   158,   159,   418,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   440,   686,   176,   441,   177,   442,   178,   463,   179,
     464,   180,   436,   181,   420,    49,    76,   210,   211,   212,
     468,   213,   182,   421,   183,   422,   184,   423,   805,   806,
     807,   936,   781,   782,   783,   914,  1128,   784,   915,   785,
     916,   786,   917,   787,   788,   505,   789,   790,   791,   792,
     793,   794,   795,   796,   797,   798,   923,   799,   800,   926,
     801,   927,   802,   928,   185,   453,   839,   840,   841,   956,
     186,   450,   826,   827,   828,   829,   187,   452,   834,   835,
     836,   837,   188,   451,   189,   456,   850,   851,   852,   965,
      65,    84,   357,   358,   359,   518,   360,   519,   190,   457,
     859,   860,   861,   862,   863,   864,   865,   866,   191,   443,
     809,   810,   811,   939,    51,    77,   246,   247,   248,   474,
     249,   475,   250,   476,   251,   480,   252,   479,   192,   448,
     699,   254,   255,   193,   449,   821,   822,   823,   948,  1059,
    1060,   194,   444,    59,    81,   813,   814,   815,   942,    61,
      82,   322,   323,   324,   325,   326,   327,   328,   504,   329,
     508,   330,   507,   331,   332,   509,   333,   195,   445,   817,
     818,   819,   945,    63,    83,   343,   344,   345,   346,   347,
     513,   348,   349,   350,   351,   257,   472,   898,   899,   900,
     994,    53,    78,   268,   269,   270,   484,   196,   446,   197,
     447,   260,   473,   902,   903,   904,   997,    55,    79,   284,
     285,   286,   487,   287,   288,   489,   289,   290,   198,   455,
     846,   847,   848,   962,    57,    80,   302,   303,   304,   305,
     495,   306,   496,   307,   497,   308,   498,   309,   499,   310,
     500,   311,   494,   262,   481,   907,   908,  1000,   199,   454,
     843,   844,   959,  1077,  1078,  1079,  1080,  1081,  1143,  1082,
     200,   458,   876,   877,   878,   976,  1152,   879,   880,   977,
     881,   882,   201,   202,   460,   888,   889,   890,   983,   891,
     984,   203,   461,   204,   462,    67,    85,   379,   380,   381,
     382,   523,   383,   524,   384,   385,   526,   386,   387,   388,
     529,   749,   389,   530,   390,   391,   392,   533,   393,   534,
     394,   535,   395,   536,   104,   412,   105,   413,   106,   414,
     205,   419,    71,    87,   401,   402,   403,   541,   404,   107,
     411,    69,    86,   396,   397,   206,   465,   894,   895,   988,
    1111,  1112,  1113,  1114,  1158,  1115,  1156,  1177,  1178,  1179,
    1187,  1188,  1189,  1195,  1190,  1191,  1192,  1193,  1199
  };

  const unsigned short
  Dhcp6Parser::yytable_[] =
  {
     100,   156,   209,   226,   264,   278,   298,   227,   320,   339,
     356,   376,    40,   873,   341,   342,   803,   261,   833,   228,
     214,   258,   271,   282,   300,   398,   334,   352,  1052,   377,
    1053,  1054,  1058,  1064,   824,    94,   321,   340,   692,   229,
     416,    32,   292,   207,   208,   417,   230,   231,    33,   905,
      34,   466,    35,   692,   314,   951,   467,   232,   952,    91,
     233,   215,   259,   272,   283,   301,   954,   335,   353,   955,
     378,   136,   137,   155,   256,   267,   281,   299,   234,   867,
      44,   695,   696,   697,   698,   723,   235,   313,   766,   236,
     237,   238,    46,   239,    48,   470,   240,   729,   730,   731,
     471,   241,   960,   242,    50,   961,   243,   244,    52,   245,
     136,   137,   989,   253,   825,   990,   265,   279,   266,   280,
     354,   355,   108,   109,   824,   831,   110,   832,   482,   111,
     112,   113,   314,   483,   315,   316,   399,   400,   317,   318,
     319,   136,   137,   485,   681,   682,   683,   684,   486,   136,
     137,  1104,    54,  1105,  1106,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,    99,   136,   137,
     492,   685,  1149,  1150,  1151,   493,    95,   868,   869,   870,
     871,   354,   355,    99,   136,   137,    96,    97,    98,  1182,
     135,   138,  1183,  1184,  1185,  1186,   139,   140,   141,   142,
     143,   263,   144,    56,    99,    58,    99,   145,   136,   137,
    1052,   134,  1053,  1054,  1058,  1064,   146,    60,    62,   147,
     883,   884,    36,    37,    38,    39,   148,   223,  1180,    64,
     224,  1181,   405,   135,   149,   150,   135,    99,   151,   152,
    1124,  1125,  1126,  1127,    66,    99,   273,   274,   275,   276,
     277,   136,   137,   520,   136,   137,    68,   537,   521,   833,
     153,   154,   538,   155,  1023,    70,   539,   406,   747,   748,
     223,   540,   291,   224,    99,   873,   407,   408,   292,   293,
     294,   295,   296,   297,   543,   409,   761,   415,   424,   544,
      99,   762,   763,   764,   765,   766,   767,   768,   769,   770,
     771,   772,   773,   774,   775,   776,   777,   778,   779,   425,
     466,   135,   314,   426,    99,   910,   427,   314,   336,   315,
     316,   337,   338,   853,   854,   855,   856,   857,   858,   136,
     137,   314,   100,   539,   136,   137,   543,   470,   911,   933,
     933,   912,   913,   957,   934,   935,   974,   981,   958,  1070,
    1071,   975,   982,   985,   537,   501,   428,    99,   986,   987,
      99,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,   933,   502,   482,  1140,
     520,  1136,   156,  1137,  1141,  1148,   209,   429,  1159,   485,
     492,   545,   546,  1160,  1162,  1163,   430,   431,   226,   432,
    1200,   264,   227,   512,   214,  1201,   433,   434,   278,   435,
     437,   438,   261,   439,   228,   459,   258,   469,   298,   271,
     477,   478,   488,   490,   491,   517,   282,   506,   320,   503,
     510,   514,   511,   339,   229,    99,   300,   515,   341,   342,
      99,   230,   231,   516,   522,   215,   334,   525,   527,   528,
     531,   352,   232,   376,    99,   233,   321,   259,   532,   542,
     272,   340,   547,   548,   549,   550,   551,   283,   398,   256,
     552,   377,   267,   234,   554,   555,   556,   301,   557,   281,
     558,   235,   136,   137,   236,   237,   238,   335,   239,   299,
     559,   240,   353,   560,   561,   572,   241,   569,   242,   570,
     562,   243,   244,   563,   245,   564,   565,   566,   253,   567,
     568,   571,   378,   265,   573,   266,   574,   575,   576,   577,
     279,   578,   280,   579,   580,   581,   582,   583,   584,   585,
     586,   587,   588,   589,   590,   671,   672,   673,   361,   362,
     363,   364,   365,   366,   367,   368,   369,   370,   371,   372,
     373,   591,   592,   593,   594,   595,   596,   597,   374,   375,
     598,   599,   600,   601,   603,   606,   607,   608,   609,   610,
     604,   611,   612,   613,   614,   615,   617,   619,   620,   621,
     622,   623,   625,   626,   627,   156,   628,   629,    99,   630,
     631,   633,   209,   634,   635,   636,   637,   638,   641,   398,
     639,   645,   642,   646,   643,   649,   648,   650,   652,   655,
     214,   656,   659,   660,   661,   651,   662,   665,   653,   654,
     668,   669,   657,   658,   666,   872,   885,   670,   376,   675,
     674,   743,   676,   677,   678,   679,   680,   687,   688,   689,
     690,   691,   694,   874,   886,    34,   377,   700,   701,   702,
     703,   215,   713,   756,   704,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   705,   706,   127,   128,
     129,   130,   131,   132,   707,   708,   135,   709,   710,   712,
     715,   714,   716,   718,   875,   887,   216,   378,   217,   719,
     720,   721,   722,   724,   136,   137,   218,   219,   220,   221,
     222,   138,   725,   755,   804,   726,   808,   727,   750,   812,
     816,   820,   842,   223,   845,   838,   224,   145,   849,   893,
     728,   732,   733,   734,   225,   735,   736,   737,   738,   739,
     740,   741,   742,   744,   745,   746,   897,   901,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   918,
     919,   127,   128,   129,   130,   131,   132,   133,   920,   135,
     314,   921,   922,   752,   924,   753,   754,   925,   929,   930,
     153,   154,   931,   932,   938,   941,   937,   136,   137,   940,
     219,   220,   943,   222,   138,   944,   946,   947,   950,   949,
    1007,   964,   953,   963,   967,   966,   223,   968,   969,   224,
      99,   970,   971,   972,   973,   978,   979,   225,   980,   995,
     991,   996,   998,   999,  1009,  1001,  1003,  1002,  1004,  1005,
    1006,  1008,  1011,  1010,  1012,  1015,  1016,  1013,  1017,  1014,
    1018,  1019,  1068,  1095,  1096,  1101,  1102,  1118,  1020,  1021,
    1088,  1089,  1090,  1091,  1092,  1093,  1097,  1098,  1099,  1117,
    1123,  1144,  1129,   153,   154,   226,  1130,  1138,   320,   227,
    1139,   339,  1131,  1132,  1031,  1133,   341,   342,  1032,   261,
    1134,   228,  1135,   258,  1142,  1072,   334,  1145,   298,   352,
    1033,   356,  1062,    99,  1146,  1147,   321,  1157,  1166,   340,
    1153,   229,  1051,  1075,  1169,  1154,   300,   872,   230,   231,
    1034,   885,  1155,  1073,  1107,  1161,  1164,  1035,  1036,   232,
     264,  1167,   233,   278,   259,   874,  1170,   335,  1037,   886,
     353,  1038,  1109,  1063,  1171,  1173,   256,  1174,   271,  1175,
     234,   282,  1108,  1176,  1076,  1061,  1196,   301,   235,  1039,
    1197,   236,   237,   238,  1198,   239,  1074,  1040,   240,   299,
    1041,  1042,  1043,   241,  1044,   242,   875,  1045,   243,   244,
     887,   245,  1046,  1110,  1047,   253,  1202,  1048,  1049,   272,
    1050,  1203,   283,  1206,  1057,   602,  1055,   830,  1056,   711,
    1204,   267,  1205,   553,   281,  1208,   751,   760,   909,   757,
    1024,  1022,  1069,  1067,  1209,  1066,  1087,  1086,   647,  1025,
    1026,  1065,  1165,  1027,   312,   605,  1028,   640,  1094,  1120,
     644,  1030,  1029,  1085,   632,  1119,  1084,  1122,   906,  1168,
    1121,  1100,   265,   759,   266,   279,  1083,   280,  1103,   758,
     667,   663,  1194,   616,  1116,   892,   664,  1172,  1207,     0,
     618,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1031,     0,   624,     0,
    1032,     0,  1072,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1033,     0,  1062,  1107,     0,     0,     0,     0,
    1075,     0,     0,     0,  1051,     0,     0,     0,     0,     0,
    1073,     0,  1034,  1109,     0,     0,     0,     0,     0,  1035,
    1036,     0,     0,  1108,     0,     0,     0,     0,     0,     0,
    1037,     0,     0,  1038,     0,  1063,     0,     0,     0,     0,
       0,  1076,     0,     0,     0,     0,     0,  1061,     0,     0,
       0,  1039,     0,  1074,  1110,     0,     0,     0,     0,  1040,
       0,     0,  1041,  1042,  1043,     0,  1044,     0,     0,  1045,
       0,     0,     0,     0,  1046,     0,  1047,     0,     0,  1048,
    1049,     0,  1050,     0,     0,     0,  1057,     0,  1055,     0,
    1056
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    77,    82,    83,
      84,    85,    17,   709,    83,    83,   678,    77,   703,    77,
      76,    77,    78,    79,    80,    86,    82,    83,   948,    85,
     948,   948,   948,   948,   109,    10,    82,    83,   582,    77,
       3,     0,   107,    16,    17,     8,    77,    77,     5,   114,
       7,     3,     9,   597,    66,     3,     8,    77,     6,   189,
      77,    76,    77,    78,    79,    80,     3,    82,    83,     6,
      85,    83,    84,   162,    77,    78,    79,    80,    77,    21,
       7,    91,    92,    93,    94,   613,    77,    21,    30,    77,
      77,    77,     7,    77,     7,     3,    77,   625,   626,   627,
       8,    77,     3,    77,     7,     6,    77,    77,     7,    77,
      83,    84,     3,    77,   189,     6,    78,    79,    78,    79,
     116,   117,    11,    12,   109,   110,    15,   112,     3,    18,
      19,    20,    66,     8,    68,    69,    13,    14,    72,    73,
      74,    83,    84,     3,   155,   156,   157,   158,     8,    83,
      84,   163,     7,   165,   166,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,   189,    83,    84,
       3,   192,   126,   127,   128,     8,   161,   129,   130,   131,
     132,   116,   117,   189,    83,    84,   171,   172,   173,   164,
      65,    90,   167,   168,   169,   170,    95,    96,    97,    98,
      99,    76,   101,     7,   189,     7,   189,   106,    83,    84,
    1140,    64,  1140,  1140,  1140,  1140,   115,     7,     7,   118,
     135,   136,   189,   190,   191,   192,   125,   102,     3,     7,
     105,     6,     6,    65,   133,   134,    65,   189,   137,   138,
      22,    23,    24,    25,     7,   189,    78,    79,    80,    81,
      82,    83,    84,     3,    83,    84,     7,     3,     8,   954,
     159,   160,     8,   162,   936,     7,     3,     3,   152,   153,
     102,     8,   101,   105,   189,   981,     4,     8,   107,   108,
     109,   110,   111,   112,     3,     3,    21,     4,     4,     8,
     189,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,     4,
       3,    65,    66,     4,   189,     8,     4,    66,    67,    68,
      69,    70,    71,   119,   120,   121,   122,   123,   124,    83,
      84,    66,   416,     3,    83,    84,     3,     3,     8,     3,
       3,     8,     8,     3,     8,     8,     3,     3,     8,   103,
     104,     8,     8,     3,     3,     8,     4,   189,     8,     8,
     189,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,     3,     3,     3,     3,
       3,     8,   466,     8,     8,     8,   470,     4,     3,     3,
       3,   406,   407,     8,     8,     8,     4,     4,   482,     4,
       3,   485,   482,     3,   470,     8,     4,     4,   492,     4,
       4,     4,   482,     4,   482,     4,   482,     4,   502,   485,
       4,     4,     4,     4,     4,     3,   492,     4,   512,     8,
       4,     4,     8,   517,   482,   189,   502,     4,   517,   517,
     189,   482,   482,     8,     4,   470,   512,     4,     4,     4,
       4,   517,   482,   537,   189,   482,   512,   482,     4,     4,
     485,   517,   189,     4,     4,     4,     4,   492,   539,   482,
       4,   537,   485,   482,     4,     4,     4,   502,     4,   492,
       4,   482,    83,    84,   482,   482,   482,   512,   482,   502,
       4,   482,   517,   190,   190,     4,   482,   191,   482,   191,
     190,   482,   482,   190,   482,   190,   190,   190,   482,   190,
     192,   190,   537,   485,   192,   485,   192,   192,     4,     4,
     492,     4,   492,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   550,   551,   552,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,     4,     4,     4,     4,   190,     4,     4,   159,   160,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     192,   190,   192,     4,     4,     4,     4,     4,   190,     4,
     190,   190,     4,     4,     4,   669,     4,     4,   189,     4,
       4,     4,   676,     4,   190,     4,     4,     4,     4,   670,
     192,     4,   192,     4,   192,     4,   192,     4,     4,     4,
     676,     4,     4,     4,     4,   190,     4,     4,   190,   190,
       4,     7,   192,   192,   190,   709,   710,     7,   712,     7,
     189,   646,     7,     7,     7,     5,   189,   189,   189,     5,
       5,     5,   189,   709,   710,     7,   712,     5,     5,     5,
       5,   676,   189,   668,     7,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,     5,     5,    57,    58,
      59,    60,    61,    62,     5,     7,    65,     7,     7,     7,
       5,   189,     5,     5,   709,   710,    75,   712,    77,     5,
     189,   189,   189,   189,    83,    84,    85,    86,    87,    88,
      89,    90,     7,     5,     7,   189,     7,   189,   154,     7,
       7,     7,     7,   102,     7,   100,   105,   106,     7,     7,
     189,   189,   189,   189,   113,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   189,     7,     7,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,     4,
       4,    57,    58,    59,    60,    61,    62,    63,     4,    65,
      66,     4,     4,   189,     4,   189,   189,     4,     4,     4,
     159,   160,     4,     4,     3,     3,     6,    83,    84,     6,
      86,    87,     6,    89,    90,     3,     6,     3,     3,     6,
     190,     3,     6,     6,     3,     6,   102,     4,     4,   105,
     189,     4,     4,     4,     4,     4,     4,   113,     4,     6,
     189,     3,     6,     3,   190,     8,     4,     6,     4,     4,
       4,   192,   190,   192,     4,     4,     4,   190,     4,   190,
     190,   190,     4,     4,     4,     4,     4,     3,   192,   190,
     190,   190,   190,   190,   190,   190,   190,   190,   190,     6,
       4,     4,   189,   159,   160,   939,   189,     8,   942,   939,
       8,   945,   189,   189,   948,   189,   945,   945,   948,   939,
     189,   939,   189,   939,   189,   959,   942,     8,   962,   945,
     948,   965,   948,   189,     3,     8,   942,     4,     4,   945,
     189,   939,   948,   959,     4,   189,   962,   981,   939,   939,
     948,   985,   189,   959,   988,   189,   189,   948,   948,   939,
     994,   192,   939,   997,   939,   981,   190,   942,   948,   985,
     945,   948,   988,   948,     4,   189,   939,     5,   994,   189,
     939,   997,   988,     7,   959,   948,     4,   962,   939,   948,
       4,   939,   939,   939,     4,   939,   959,   948,   939,   962,
     948,   948,   948,   939,   948,   939,   981,   948,   939,   939,
     985,   939,   948,   988,   948,   939,     4,   948,   948,   994,
     948,   192,   997,     4,   948,   466,   948,   702,   948,   597,
     190,   994,   190,   416,   997,   189,   659,   676,   755,   669,
     938,   933,   957,   954,   189,   951,   967,   965,   520,   939,
     941,   950,  1140,   942,    81,   470,   944,   512,   974,   996,
     517,   947,   945,   964,   502,   994,   962,   999,   725,  1146,
     997,   981,   994,   675,   994,   997,   960,   997,   985,   670,
     543,   537,  1180,   482,   989,   712,   539,  1159,  1200,    -1,
     485,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1140,    -1,   492,    -1,
    1140,    -1,  1146,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1140,    -1,  1140,  1159,    -1,    -1,    -1,    -1,
    1146,    -1,    -1,    -1,  1140,    -1,    -1,    -1,    -1,    -1,
    1146,    -1,  1140,  1159,    -1,    -1,    -1,    -1,    -1,  1140,
    1140,    -1,    -1,  1159,    -1,    -1,    -1,    -1,    -1,    -1,
    1140,    -1,    -1,  1140,    -1,  1140,    -1,    -1,    -1,    -1,
      -1,  1146,    -1,    -1,    -1,    -1,    -1,  1140,    -1,    -1,
      -1,  1140,    -1,  1146,  1159,    -1,    -1,    -1,    -1,  1140,
      -1,    -1,  1140,  1140,  1140,    -1,  1140,    -1,    -1,  1140,
      -1,    -1,    -1,    -1,  1140,    -1,  1140,    -1,    -1,  1140,
    1140,    -1,  1140,    -1,    -1,    -1,  1140,    -1,  1140,    -1,
    1140
  };

  const unsigned short
  Dhcp6Parser::yystos_[] =
  {
       0,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,     0,     5,     7,     9,   189,   190,   191,   192,
     210,   211,   212,   217,     7,   226,     7,   232,     7,   268,
       7,   367,     7,   444,     7,   460,     7,   477,     7,   396,
       7,   402,     7,   426,     7,   343,     7,   538,     7,   584,
       7,   575,   218,   213,   227,   233,   269,   368,   445,   461,
     478,   397,   403,   427,   344,   539,   585,   576,   210,   219,
     220,   189,   215,   216,    10,   161,   171,   172,   173,   189,
     225,   228,   229,   230,   567,   569,   571,   582,    11,    12,
      15,    18,    19,    20,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    83,    84,    90,    95,
      96,    97,    98,    99,   101,   106,   115,   118,   125,   133,
     134,   137,   138,   159,   160,   162,   225,   234,   235,   236,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   256,   258,   260,   262,
     264,   266,   275,   277,   279,   317,   323,   329,   335,   337,
     351,   361,   381,   386,   394,   420,   450,   452,   471,   501,
     513,   525,   526,   534,   536,   573,   588,    16,    17,   225,
     270,   271,   272,   274,   450,   452,    75,    77,    85,    86,
      87,    88,    89,   102,   105,   113,   225,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   250,   251,
     252,   253,   256,   258,   260,   262,   369,   370,   371,   373,
     375,   377,   379,   381,   384,   385,   420,   438,   450,   452,
     454,   471,   496,    76,   225,   377,   379,   420,   446,   447,
     448,   450,   452,    78,    79,    80,    81,    82,   225,   377,
     379,   420,   450,   452,   462,   463,   464,   466,   467,   469,
     470,   101,   107,   108,   109,   110,   111,   112,   225,   420,
     450,   452,   479,   480,   481,   482,   484,   486,   488,   490,
     492,   494,   394,    21,    66,    68,    69,    72,    73,    74,
     225,   297,   404,   405,   406,   407,   408,   409,   410,   412,
     414,   416,   417,   419,   450,   452,    67,    70,    71,   225,
     297,   408,   414,   428,   429,   430,   431,   432,   434,   435,
     436,   437,   450,   452,   116,   117,   225,   345,   346,   347,
     349,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   159,   160,   225,   450,   452,   540,
     541,   542,   543,   545,   547,   548,   550,   551,   552,   555,
     557,   558,   559,   561,   563,   565,   586,   587,   588,    13,
      14,   577,   578,   579,   581,     6,     3,     4,     8,     3,
     231,   583,   568,   570,   572,     4,     3,     8,   237,   574,
     267,   276,   278,   280,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   265,     4,     4,     4,
     254,   257,   259,   362,   395,   421,   451,   453,   382,   387,
     324,   336,   330,   318,   502,   472,   338,   352,   514,     4,
     527,   535,   537,   261,   263,   589,     3,     8,   273,     4,
       3,     8,   439,   455,   372,   374,   376,     4,     4,   380,
     378,   497,     3,     8,   449,     3,     8,   465,     4,   468,
       4,     4,     3,     8,   495,   483,   485,   487,   489,   491,
     493,     8,     3,     8,   411,   298,     4,   415,   413,   418,
       4,     8,     3,   433,     4,     4,     8,     3,   348,   350,
       3,     8,     4,   544,   546,     4,   549,     4,     4,   553,
     556,     4,     4,   560,   562,   564,   566,     3,     8,     3,
       8,   580,     4,     3,     8,   210,   210,   189,     4,     4,
       4,     4,     4,   229,     4,     4,     4,     4,     4,     4,
     190,   190,   190,   190,   190,   190,   190,   190,   192,   191,
     191,   190,     4,   192,   192,   192,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   190,     4,     4,     4,     4,
       4,     4,   235,     4,   192,   271,     4,     4,     4,     4,
       4,   190,   192,     4,     4,     4,   370,     4,   447,     4,
     190,     4,   190,   190,   463,     4,     4,     4,     4,     4,
       4,     4,   481,     4,     4,   190,     4,     4,     4,   192,
     406,     4,   192,   192,   430,     4,     4,   346,   192,     4,
       4,   190,     4,   190,   190,     4,     4,   192,   192,     4,
       4,     4,     4,   541,   587,     4,   190,   578,     4,     7,
       7,   210,   210,   210,   189,     7,     7,     7,     7,     5,
     189,   155,   156,   157,   158,   192,   255,   189,   189,     5,
       5,     5,   212,   214,   189,    91,    92,    93,    94,   383,
       5,     5,     5,     5,     7,     5,     5,     5,     7,     7,
       7,   214,     7,   189,   189,     5,     5,   221,     5,     5,
     189,   189,   189,   221,   189,     7,   189,   189,   189,   221,
     221,   221,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   210,   189,   189,   189,   152,   153,   554,
     154,   255,   189,   189,   189,     5,   210,   234,   586,   577,
     270,    21,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
     225,   285,   286,   287,   290,   292,   294,   296,   297,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   310,
     311,   313,   315,   285,     7,   281,   282,   283,     7,   363,
     364,   365,     7,   398,   399,   400,     7,   422,   423,   424,
       7,   388,   389,   390,   109,   189,   325,   326,   327,   328,
     219,   110,   112,   327,   331,   332,   333,   334,   100,   319,
     320,   321,     7,   503,   504,     7,   473,   474,   475,     7,
     339,   340,   341,   119,   120,   121,   122,   123,   124,   353,
     354,   355,   356,   357,   358,   359,   360,    21,   129,   130,
     131,   132,   225,   299,   450,   452,   515,   516,   517,   520,
     521,   523,   524,   135,   136,   225,   450,   452,   528,   529,
     530,   532,   540,     7,   590,   591,   222,     7,   440,   441,
     442,     7,   456,   457,   458,   114,   482,   498,   499,   281,
       8,     8,     8,     8,   288,   291,   293,   295,     4,     4,
       4,     4,     4,   309,     4,     4,   312,   314,   316,     4,
       4,     4,     4,     3,     8,     8,   284,     6,     3,   366,
       6,     3,   401,     6,     3,   425,     6,     3,   391,     6,
       3,     3,     6,     6,     3,     6,   322,     3,     8,   505,
       3,     6,   476,     6,     3,   342,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,   518,   522,     4,     4,
       4,     3,     8,   531,   533,     3,     8,     8,   592,     3,
       6,   189,   223,   224,   443,     6,     3,   459,     6,     3,
     500,     8,     6,     4,     4,     4,     4,   190,   192,   190,
     192,   190,     4,   190,   190,     4,     4,     4,   190,   190,
     192,   190,   286,   285,   283,   369,   365,   404,   400,   428,
     424,   225,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   250,   251,   252,   253,   256,   258,   260,
     262,   297,   361,   373,   375,   377,   379,   381,   385,   392,
     393,   420,   450,   452,   496,   390,   326,   332,     4,   320,
     103,   104,   225,   297,   420,   450,   452,   506,   507,   508,
     509,   510,   512,   504,   479,   475,   345,   341,   190,   190,
     190,   190,   190,   190,   354,     4,     4,   190,   190,   190,
     516,     4,     4,   529,   163,   165,   166,   225,   297,   450,
     452,   593,   594,   595,   596,   598,   591,     6,     3,   446,
     442,   462,   458,     4,    22,    23,    24,    25,   289,   189,
     189,   189,   189,   189,   189,   189,     8,     8,     8,     8,
       3,     8,   189,   511,     4,     8,     3,     8,     8,   126,
     127,   128,   519,   189,   189,   189,   599,     4,   597,     3,
       8,   189,     8,     8,   189,   393,     4,   192,   508,     4,
     190,     4,   594,   189,     5,   189,     7,   600,   601,   602,
       3,     6,   164,   167,   168,   169,   170,   603,   604,   605,
     607,   608,   609,   610,   601,   606,     4,     4,     4,   611,
       3,     8,     4,   192,   190,   190,     4,   604,   189,   189
  };

  const unsigned short
  Dhcp6Parser::yyr1_[] =
  {
       0,   193,   195,   194,   196,   194,   197,   194,   198,   194,
     199,   194,   200,   194,   201,   194,   202,   194,   203,   194,
     204,   194,   205,   194,   206,   194,   207,   194,   208,   194,
     209,   194,   210,   210,   210,   210,   210,   210,   210,   211,
     213,   212,   214,   215,   215,   216,   216,   218,   217,   219,
     219,   220,   220,   222,   221,   223,   223,   224,   224,   225,
     227,   226,   228,   228,   229,   229,   229,   229,   229,   229,
     231,   230,   233,   232,   234,   234,   235,   235,   235,   235,
     235,   235,   235,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   235,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   235,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   235,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   235,   235,   235,   237,   236,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   254,   253,   255,   255,   255,   255,   255,   257,
     256,   259,   258,   261,   260,   263,   262,   265,   264,   267,
     266,   269,   268,   270,   270,   271,   271,   271,   271,   271,
     273,   272,   274,   276,   275,   278,   277,   280,   279,   281,
     281,   282,   282,   284,   283,   285,   285,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   288,   287,
     289,   289,   289,   289,   291,   290,   293,   292,   295,   294,
     296,   298,   297,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   309,   308,   310,   312,   311,   314,   313,   316,
     315,   318,   317,   319,   319,   320,   322,   321,   324,   323,
     325,   325,   326,   326,   327,   328,   330,   329,   331,   331,
     332,   332,   332,   333,   334,   336,   335,   338,   337,   339,
     339,   340,   340,   342,   341,   344,   343,   345,   345,   345,
     346,   346,   348,   347,   350,   349,   352,   351,   353,   353,
     354,   354,   354,   354,   354,   354,   355,   356,   357,   358,
     359,   360,   362,   361,   363,   363,   364,   364,   366,   365,
     368,   367,   369,   369,   370,   370,   370,   370,   370,   370,
     370,   370,   370,   370,   370,   370,   370,   370,   370,   370,
     370,   370,   370,   370,   370,   370,   370,   370,   370,   370,
     370,   370,   370,   370,   370,   370,   370,   370,   370,   372,
     371,   374,   373,   376,   375,   378,   377,   380,   379,   382,
     381,   383,   383,   383,   383,   384,   385,   387,   386,   388,
     388,   389,   389,   391,   390,   392,   392,   393,   393,   393,
     393,   393,   393,   393,   393,   393,   393,   393,   393,   393,
     393,   393,   393,   393,   393,   393,   393,   393,   393,   393,
     393,   393,   393,   393,   393,   393,   393,   393,   393,   395,
     394,   397,   396,   398,   398,   399,   399,   401,   400,   403,
     402,   404,   404,   405,   405,   406,   406,   406,   406,   406,
     406,   406,   406,   406,   406,   407,   408,   409,   411,   410,
     413,   412,   415,   414,   416,   418,   417,   419,   421,   420,
     422,   422,   423,   423,   425,   424,   427,   426,   428,   428,
     429,   429,   430,   430,   430,   430,   430,   430,   430,   430,
     430,   431,   433,   432,   434,   435,   436,   437,   439,   438,
     440,   440,   441,   441,   443,   442,   445,   444,   446,   446,
     447,   447,   447,   447,   447,   447,   447,   449,   448,   451,
     450,   453,   452,   455,   454,   456,   456,   457,   457,   459,
     458,   461,   460,   462,   462,   463,   463,   463,   463,   463,
     463,   463,   463,   463,   463,   463,   465,   464,   466,   468,
     467,   469,   470,   472,   471,   473,   473,   474,   474,   476,
     475,   478,   477,   479,   479,   480,   480,   481,   481,   481,
     481,   481,   481,   481,   481,   481,   481,   481,   483,   482,
     485,   484,   487,   486,   489,   488,   491,   490,   493,   492,
     495,   494,   497,   496,   498,   498,   500,   499,   502,   501,
     503,   503,   505,   504,   506,   506,   507,   507,   508,   508,
     508,   508,   508,   508,   508,   509,   511,   510,   512,   514,
     513,   515,   515,   516,   516,   516,   516,   516,   516,   516,
     516,   516,   518,   517,   519,   519,   519,   520,   522,   521,
     523,   524,   525,   527,   526,   528,   528,   529,   529,   529,
     529,   529,   531,   530,   533,   532,   535,   534,   537,   536,
     539,   538,   540,   540,   541,   541,   541,   541,   541,   541,
     541,   541,   541,   541,   541,   541,   541,   541,   541,   541,
     541,   541,   542,   544,   543,   546,   545,   547,   549,   548,
     550,   551,   553,   552,   554,   554,   556,   555,   557,   558,
     560,   559,   562,   561,   564,   563,   566,   565,   568,   567,
     570,   569,   572,   571,   574,   573,   576,   575,   577,   577,
     578,   578,   580,   579,   581,   583,   582,   585,   584,   586,
     586,   587,   589,   588,   590,   590,   592,   591,   593,   593,
     594,   594,   594,   594,   594,   594,   594,   595,   597,   596,
     599,   598,   600,   600,   602,   601,   603,   603,   604,   604,
     604,   604,   604,   606,   605,   607,   608,   609,   611,   610
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     0,     4,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     6,     0,     6,     0,     6,     0,
       1,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       3,     0,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     0,     4,     3,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     0,     6,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     1,     1,     1,     1,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     0,     6,     3,     0,     6,     0,     4,     1,
       3,     1,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     6,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     0,     4,     3,     3,     3,     0,     4
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
  "\"tcp-nodelay\"", "\"max-row-errors\"", "\"preferred-lifetime\"",
  "\"min-preferred-lifetime\"", "\"max-preferred-lifetime\"",
  "\"valid-lifetime\"", "\"min-valid-lifetime\"", "\"max-valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"calculate-tee-times\"",
  "\"t1-percent\"", "\"t2-percent\"", "\"decline-probation-period\"",
  "\"server-tag\"", "\"ddns-send-updates\"", "\"ddns-override-no-update\"",
  "\"ddns-override-client-update\"", "\"ddns-replace-client-name\"",
  "\"ddns-generated-prefix\"", "\"ddns-qualifying-suffix\"", "\"subnet6\"",
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
  "t2_percent", "decline_probation_period", "ddns_send_updates",
  "ddns_override_no_update", "ddns_override_client_update",
  "ddns_replace_client_name", "$@23", "ddns_replace_client_name_value",
  "ddns_generated_prefix", "$@24", "ddns_qualifying_suffix", "$@25",
  "hostname_char_set", "$@26", "hostname_char_replacement", "$@27",
  "server_tag", "$@28", "interfaces_config", "$@29", "sub_interfaces6",
  "$@30", "interfaces_config_params", "interfaces_config_param",
  "interfaces_list", "$@31", "re_detect", "lease_database", "$@32",
  "hosts_database", "$@33", "hosts_databases", "$@34", "database_list",
  "not_empty_database_list", "database", "$@35", "database_map_params",
  "database_map_param", "database_type", "$@36", "db_type", "user", "$@37",
  "password", "$@38", "host", "$@39", "port", "name", "$@40", "persist",
  "lfc_interval", "readonly", "connect_timeout", "reconnect_wait_time",
  "max_row_errors", "request_timeout", "tcp_keepalive", "tcp_nodelay",
  "contact_points", "$@41", "max_reconnect_tries", "keyspace", "$@42",
  "consistency", "$@43", "serial_consistency", "$@44", "sanity_checks",
  "$@45", "sanity_checks_params", "sanity_checks_param", "lease_checks",
  "$@46", "mac_sources", "$@47", "mac_sources_list", "mac_sources_value",
  "duid_id", "string_id", "host_reservation_identifiers", "$@48",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@49",
  "hooks_libraries", "$@50", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@51",
  "sub_hooks_library", "$@52", "hooks_params", "hooks_param", "library",
  "$@53", "parameters", "$@54", "expired_leases_processing", "$@55",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@56",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@57",
  "sub_subnet6", "$@58", "subnet6_params", "subnet6_param", "subnet",
  "$@59", "interface", "$@60", "interface_id", "$@61", "client_class",
  "$@62", "require_client_classes", "$@63", "reservation_mode", "$@64",
  "hr_mode", "id", "rapid_commit", "shared_networks", "$@65",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@66", "shared_network_params", "shared_network_param",
  "option_def_list", "$@67", "sub_option_def_list", "$@68",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@69", "sub_option_def", "$@70",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@71",
  "option_def_record_types", "$@72", "space", "$@73", "option_def_space",
  "option_def_encapsulate", "$@74", "option_def_array", "option_data_list",
  "$@75", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@76", "sub_option_data", "$@77",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@78",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@79", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@80", "sub_pool6", "$@81",
  "pool_params", "pool_param", "pool_entry", "$@82", "user_context",
  "$@83", "comment", "$@84", "pd_pools_list", "$@85",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@86", "sub_pd_pool", "$@87", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@88", "pd_prefix_len", "excluded_prefix", "$@89",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@90",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@91", "sub_reservation", "$@92", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@93", "prefixes", "$@94", "duid", "$@95", "hw_address", "$@96",
  "hostname", "$@97", "flex_id_value", "$@98",
  "reservation_client_classes", "$@99", "relay", "$@100", "relay_map",
  "ip_address", "$@101", "client_classes", "$@102", "client_classes_list",
  "client_class_entry", "$@103", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@104", "only_if_required",
  "server_id", "$@105", "server_id_params", "server_id_param",
  "server_id_type", "$@106", "duid_type", "htype", "identifier", "$@107",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@108",
  "control_socket_params", "control_socket_param", "socket_type", "$@109",
  "socket_name", "$@110", "dhcp_queue_control", "$@111", "dhcp_ddns",
  "$@112", "sub_dhcp_ddns", "$@113", "dhcp_ddns_params", "dhcp_ddns_param",
  "enable_updates", "qualifying_suffix", "$@114", "server_ip", "$@115",
  "server_port", "sender_ip", "$@116", "sender_port", "max_queue_size",
  "ncr_protocol", "$@117", "ncr_protocol_value", "ncr_format", "$@118",
  "dep_override_no_update", "dep_override_client_update",
  "dep_replace_client_name", "$@119", "dep_generated_prefix", "$@120",
  "dep_hostname_char_set", "$@121", "dep_hostname_char_replacement",
  "$@122", "dhcp4_json_object", "$@123", "dhcpddns_json_object", "$@124",
  "control_agent_json_object", "$@125", "config_control", "$@126",
  "sub_config_control", "$@127", "config_control_params",
  "config_control_param", "config_databases", "$@128",
  "config_fetch_wait_time", "logging_object", "$@129", "sub_logging",
  "$@130", "logging_params", "logging_param", "loggers", "$@131",
  "loggers_entries", "logger_entry", "$@132", "logger_params",
  "logger_param", "debuglevel", "severity", "$@133", "output_options_list",
  "$@134", "output_options_list_content", "output_entry", "$@135",
  "output_params_list", "output_params", "output", "$@136", "flush",
  "maxsize", "maxver", "pattern", "$@137", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short
  Dhcp6Parser::yyrline_[] =
  {
       0,   277,   277,   277,   278,   278,   279,   279,   280,   280,
     281,   281,   282,   282,   283,   283,   284,   284,   285,   285,
     286,   286,   287,   287,   288,   288,   289,   289,   290,   290,
     291,   291,   299,   300,   301,   302,   303,   304,   305,   308,
     313,   313,   324,   327,   328,   331,   335,   342,   342,   349,
     350,   353,   357,   364,   364,   371,   372,   375,   379,   390,
     400,   400,   415,   416,   420,   421,   422,   423,   424,   425,
     428,   428,   443,   443,   452,   453,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   473,   474,   475,   476,   477,   478,   479,   480,   481,
     482,   483,   484,   485,   486,   487,   488,   489,   490,   491,
     492,   493,   494,   495,   496,   497,   498,   499,   500,   501,
     502,   503,   504,   505,   506,   509,   509,   517,   522,   527,
     532,   537,   542,   547,   552,   557,   562,   567,   572,   577,
     582,   587,   592,   592,   600,   603,   606,   609,   612,   618,
     618,   626,   626,   634,   634,   642,   642,   650,   650,   658,
     658,   669,   669,   678,   679,   682,   683,   684,   685,   686,
     689,   689,   699,   705,   705,   717,   717,   729,   729,   739,
     740,   743,   744,   747,   747,   757,   758,   761,   762,   763,
     764,   765,   766,   767,   768,   769,   770,   771,   772,   773,
     774,   775,   776,   777,   778,   779,   780,   781,   784,   784,
     791,   792,   793,   794,   797,   797,   805,   805,   813,   813,
     821,   826,   826,   834,   839,   844,   849,   854,   859,   864,
     869,   874,   879,   879,   887,   892,   892,   900,   900,   908,
     908,   916,   916,   926,   927,   929,   931,   931,   949,   949,
     959,   960,   963,   964,   967,   972,   977,   977,   987,   988,
     991,   992,   993,   996,  1001,  1008,  1008,  1018,  1018,  1028,
    1029,  1032,  1033,  1036,  1036,  1046,  1046,  1056,  1057,  1058,
    1061,  1062,  1065,  1065,  1073,  1073,  1081,  1081,  1092,  1093,
    1096,  1097,  1098,  1099,  1100,  1101,  1104,  1109,  1114,  1119,
    1124,  1129,  1137,  1137,  1150,  1151,  1154,  1155,  1162,  1162,
    1188,  1188,  1199,  1200,  1204,  1205,  1206,  1207,  1208,  1209,
    1210,  1211,  1212,  1213,  1214,  1215,  1216,  1217,  1218,  1219,
    1220,  1221,  1222,  1223,  1224,  1225,  1226,  1227,  1228,  1229,
    1230,  1231,  1232,  1233,  1234,  1235,  1236,  1237,  1238,  1241,
    1241,  1249,  1249,  1257,  1257,  1265,  1265,  1273,  1273,  1283,
    1283,  1290,  1291,  1292,  1293,  1296,  1301,  1309,  1309,  1320,
    1321,  1325,  1326,  1329,  1329,  1337,  1338,  1341,  1342,  1343,
    1344,  1345,  1346,  1347,  1348,  1349,  1350,  1351,  1352,  1353,
    1354,  1355,  1356,  1357,  1358,  1359,  1360,  1361,  1362,  1363,
    1364,  1365,  1366,  1367,  1368,  1369,  1370,  1371,  1372,  1379,
    1379,  1392,  1392,  1401,  1402,  1405,  1406,  1411,  1411,  1426,
    1426,  1440,  1441,  1444,  1445,  1448,  1449,  1450,  1451,  1452,
    1453,  1454,  1455,  1456,  1457,  1460,  1462,  1467,  1469,  1469,
    1477,  1477,  1485,  1485,  1493,  1495,  1495,  1503,  1512,  1512,
    1524,  1525,  1530,  1531,  1536,  1536,  1548,  1548,  1560,  1561,
    1566,  1567,  1572,  1573,  1574,  1575,  1576,  1577,  1578,  1579,
    1580,  1583,  1585,  1585,  1593,  1595,  1597,  1602,  1610,  1610,
    1622,  1623,  1626,  1627,  1630,  1630,  1640,  1640,  1649,  1650,
    1653,  1654,  1655,  1656,  1657,  1658,  1659,  1662,  1662,  1670,
    1670,  1695,  1695,  1725,  1725,  1737,  1738,  1741,  1742,  1745,
    1745,  1757,  1757,  1769,  1770,  1773,  1774,  1775,  1776,  1777,
    1778,  1779,  1780,  1781,  1782,  1783,  1786,  1786,  1794,  1799,
    1799,  1807,  1812,  1820,  1820,  1830,  1831,  1834,  1835,  1838,
    1838,  1847,  1847,  1856,  1857,  1860,  1861,  1865,  1866,  1867,
    1868,  1869,  1870,  1871,  1872,  1873,  1874,  1875,  1878,  1878,
    1888,  1888,  1898,  1898,  1906,  1906,  1914,  1914,  1922,  1922,
    1930,  1930,  1943,  1943,  1953,  1954,  1957,  1957,  1968,  1968,
    1978,  1979,  1982,  1982,  1992,  1993,  1996,  1997,  2000,  2001,
    2002,  2003,  2004,  2005,  2006,  2009,  2011,  2011,  2019,  2027,
    2027,  2039,  2040,  2043,  2044,  2045,  2046,  2047,  2048,  2049,
    2050,  2051,  2054,  2054,  2061,  2062,  2063,  2066,  2071,  2071,
    2079,  2084,  2091,  2098,  2098,  2108,  2109,  2112,  2113,  2114,
    2115,  2116,  2119,  2119,  2127,  2127,  2137,  2137,  2177,  2177,
    2189,  2189,  2199,  2200,  2203,  2204,  2205,  2206,  2207,  2208,
    2209,  2210,  2211,  2212,  2213,  2214,  2215,  2216,  2217,  2218,
    2219,  2220,  2223,  2228,  2228,  2236,  2236,  2244,  2249,  2249,
    2257,  2262,  2267,  2267,  2275,  2276,  2279,  2279,  2288,  2294,
    2300,  2300,  2308,  2308,  2317,  2317,  2326,  2326,  2336,  2336,
    2343,  2343,  2350,  2350,  2359,  2359,  2370,  2370,  2380,  2381,
    2385,  2386,  2389,  2389,  2399,  2409,  2409,  2419,  2419,  2430,
    2431,  2435,  2439,  2439,  2451,  2452,  2456,  2456,  2464,  2465,
    2468,  2469,  2470,  2471,  2472,  2473,  2474,  2477,  2482,  2482,
    2490,  2490,  2500,  2501,  2504,  2504,  2512,  2513,  2516,  2517,
    2518,  2519,  2520,  2523,  2523,  2531,  2536,  2541,  2546,  2546
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
#line 5439 "dhcp6_parser.cc" // lalr1.cc:1218
#line 2554 "dhcp6_parser.yy" // lalr1.cc:1219


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
