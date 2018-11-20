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
      case 191: // value
      case 195: // map_value
      case 247: // db_type
      case 336: // hr_mode
      case 472: // duid_type
      case 507: // ncr_protocol_value
      case 514: // replace_client_name_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 173: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 172: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 171: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 170: // "constant string"
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
      case 191: // value
      case 195: // map_value
      case 247: // db_type
      case 336: // hr_mode
      case 472: // duid_type
      case 507: // ncr_protocol_value
      case 514: // replace_client_name_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 173: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 172: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 171: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 170: // "constant string"
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
      case 191: // value
      case 195: // map_value
      case 247: // db_type
      case 336: // hr_mode
      case 472: // duid_type
      case 507: // ncr_protocol_value
      case 514: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 173: // "boolean"
        value.move< bool > (that.value);
        break;

      case 172: // "floating point"
        value.move< double > (that.value);
        break;

      case 171: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 170: // "constant string"
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
            case 170: // "constant string"

#line 248 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< std::string > (); }
#line 398 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 171: // "integer"

#line 248 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 405 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 172: // "floating point"

#line 248 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< double > (); }
#line 412 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 173: // "boolean"

#line 248 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< bool > (); }
#line 419 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 191: // value

#line 248 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 426 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 195: // map_value

#line 248 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 433 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 247: // db_type

#line 248 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 440 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 336: // hr_mode

#line 248 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 447 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 472: // duid_type

#line 248 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 454 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 507: // ncr_protocol_value

#line 248 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 461 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 514: // replace_client_name_value

#line 248 "dhcp6_parser.yy" // lalr1.cc:672
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
      case 191: // value
      case 195: // map_value
      case 247: // db_type
      case 336: // hr_mode
      case 472: // duid_type
      case 507: // ncr_protocol_value
      case 514: // replace_client_name_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 173: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 172: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 171: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 170: // "constant string"
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
#line 257 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 727 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 4:
#line 258 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.CONFIG; }
#line 733 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 6:
#line 259 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP6; }
#line 739 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 8:
#line 260 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 745 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 10:
#line 261 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.SUBNET6; }
#line 751 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 12:
#line 262 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.POOLS; }
#line 757 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 14:
#line 263 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 763 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 16:
#line 264 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 769 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 18:
#line 265 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP6; }
#line 775 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 20:
#line 266 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 781 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 22:
#line 267 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 787 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 24:
#line 268 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 793 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 26:
#line 269 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 799 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 28:
#line 270 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.LOGGING; }
#line 805 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 30:
#line 271 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 811 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 32:
#line 279 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 817 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 33:
#line 280 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 823 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 34:
#line 281 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 829 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 35:
#line 282 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 835 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 36:
#line 283 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 841 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 37:
#line 284 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 847 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 38:
#line 285 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 853 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 39:
#line 288 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 862 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 40:
#line 293 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 873 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 41:
#line 298 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 883 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 42:
#line 304 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 889 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 45:
#line 311 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 898 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 46:
#line 315 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 908 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 47:
#line 322 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 917 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 48:
#line 325 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // list parsing complete. Put any sanity checking here
}
#line 925 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 51:
#line 333 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 934 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 52:
#line 337 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 943 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 53:
#line 344 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // List parsing about to start
}
#line 951 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 54:
#line 346 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 960 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 57:
#line 355 "dhcp6_parser.yy" // lalr1.cc:907
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 969 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 58:
#line 359 "dhcp6_parser.yy" // lalr1.cc:907
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 978 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 59:
#line 370 "dhcp6_parser.yy" // lalr1.cc:907
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 989 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 60:
#line 380 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1000 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 61:
#line 385 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 408 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 415 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1036 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 72:
#line 423 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1046 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 73:
#line 427 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No global parameter is required
    // parsing completed
}
#line 1055 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 107:
#line 471 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1064 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 108:
#line 476 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1073 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 109:
#line 481 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1082 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 110:
#line 486 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1091 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 111:
#line 491 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1100 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 112:
#line 496 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1108 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 113:
#line 498 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1118 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 114:
#line 504 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1129 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 115:
#line 509 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1139 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 116:
#line 515 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1149 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 117:
#line 519 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1158 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 125:
#line 535 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1169 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 126:
#line 540 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1178 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 127:
#line 545 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1187 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 128:
#line 551 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1198 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 129:
#line 556 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1209 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 130:
#line 563 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1220 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 131:
#line 568 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1231 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 132:
#line 575 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1242 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 133:
#line 580 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1251 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 138:
#line 593 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1261 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 139:
#line 597 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1271 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 160:
#line 627 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1279 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 161:
#line 629 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1288 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 162:
#line 634 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1294 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 163:
#line 635 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1300 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 164:
#line 636 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1306 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 165:
#line 637 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1312 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 166:
#line 640 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1320 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 167:
#line 642 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1330 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 168:
#line 648 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1338 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 169:
#line 650 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1348 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 170:
#line 656 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1356 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 171:
#line 658 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1366 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 172:
#line 664 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1375 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 173:
#line 669 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1383 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 174:
#line 671 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1393 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 175:
#line 677 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1402 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 176:
#line 682 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1411 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 177:
#line 687 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1420 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 178:
#line 692 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1429 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 179:
#line 697 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1438 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 180:
#line 702 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1447 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 181:
#line 707 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1456 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 182:
#line 712 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1465 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 183:
#line 717 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1473 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 184:
#line 719 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1483 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 185:
#line 725 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1492 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 186:
#line 730 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1500 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 187:
#line 732 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1510 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 188:
#line 738 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1521 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 189:
#line 743 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1530 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 193:
#line 753 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1538 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 194:
#line 755 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 771 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1569 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 196:
#line 776 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1578 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 201:
#line 789 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1587 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 202:
#line 794 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1596 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 203:
#line 799 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1607 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 204:
#line 804 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1616 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 210:
#line 818 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1625 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 211:
#line 823 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1634 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 212:
#line 830 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1645 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 213:
#line 835 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1654 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 214:
#line 840 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1665 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 215:
#line 845 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1674 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 220:
#line 858 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1684 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 221:
#line 862 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1694 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 222:
#line 868 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1704 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 223:
#line 872 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1714 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 229:
#line 887 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1722 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 230:
#line 889 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1732 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 231:
#line 895 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1740 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 232:
#line 897 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1749 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 233:
#line 903 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1760 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 234:
#line 908 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1770 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 243:
#line 926 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1779 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 244:
#line 931 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1788 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 245:
#line 936 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1797 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 246:
#line 941 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1806 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 247:
#line 946 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1815 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 248:
#line 951 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1824 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 249:
#line 959 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1835 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 250:
#line 964 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1844 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 255:
#line 984 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1854 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 256:
#line 988 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 1010 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1890 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 258:
#line 1014 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1900 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 281:
#line 1048 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1908 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 282:
#line 1050 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1918 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 283:
#line 1056 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1926 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 284:
#line 1058 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1936 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 285:
#line 1064 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1944 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 286:
#line 1066 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1954 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 287:
#line 1072 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1962 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 288:
#line 1074 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1972 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 289:
#line 1080 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1983 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 290:
#line 1085 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1992 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 291:
#line 1090 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2000 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 292:
#line 1092 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2009 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 293:
#line 1097 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2015 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 294:
#line 1098 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2021 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 295:
#line 1099 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2027 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 296:
#line 1100 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2033 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 297:
#line 1103 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2042 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 298:
#line 1108 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2051 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 299:
#line 1116 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2062 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 300:
#line 1121 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2071 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 305:
#line 1136 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2081 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 306:
#line 1140 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 2089 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 326:
#line 1171 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2100 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 327:
#line 1176 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2109 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 328:
#line 1184 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2118 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 329:
#line 1187 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // parsing completed
}
#line 2126 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 334:
#line 1203 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2136 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 335:
#line 1207 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 1218 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2158 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 337:
#line 1222 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 1254 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2179 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 355:
#line 1261 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2187 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 356:
#line 1263 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2197 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 357:
#line 1269 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2205 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 358:
#line 1271 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2215 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 359:
#line 1277 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2223 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 360:
#line 1279 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2233 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 362:
#line 1287 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2241 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 363:
#line 1289 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2251 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 364:
#line 1295 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2260 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 365:
#line 1304 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2271 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 366:
#line 1309 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2280 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 371:
#line 1328 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2290 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 372:
#line 1332 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2299 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 373:
#line 1340 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2309 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 374:
#line 1344 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2318 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 389:
#line 1377 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2326 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 390:
#line 1379 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2336 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 393:
#line 1389 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2345 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 394:
#line 1394 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2354 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 395:
#line 1402 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2365 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 396:
#line 1407 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2374 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 401:
#line 1422 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2384 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 402:
#line 1426 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2394 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 403:
#line 1432 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2404 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 404:
#line 1436 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2413 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 414:
#line 1454 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2421 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 415:
#line 1456 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2431 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 416:
#line 1462 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2439 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 417:
#line 1464 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 1487 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2474 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 419:
#line 1489 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 1517 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2514 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 421:
#line 1522 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2523 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 426:
#line 1537 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2533 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 427:
#line 1541 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 1549 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2555 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 429:
#line 1553 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 1578 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2575 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 444:
#line 1580 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2585 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 445:
#line 1586 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2594 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 446:
#line 1591 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2602 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 447:
#line 1593 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2612 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 448:
#line 1599 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2621 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 449:
#line 1604 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2630 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 450:
#line 1612 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2641 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 451:
#line 1617 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2650 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 456:
#line 1630 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2660 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 457:
#line 1634 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2669 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 458:
#line 1639 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2679 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 459:
#line 1643 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2688 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 475:
#line 1670 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2699 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 476:
#line 1675 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2708 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 477:
#line 1680 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2719 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 478:
#line 1685 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2728 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 479:
#line 1690 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2736 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 480:
#line 1692 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2746 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 481:
#line 1698 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2754 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 482:
#line 1700 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2764 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 483:
#line 1706 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2772 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 484:
#line 1708 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2782 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 485:
#line 1714 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2790 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 486:
#line 1716 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2800 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 487:
#line 1722 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2811 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 488:
#line 1727 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2820 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 489:
#line 1735 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2831 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 490:
#line 1740 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2840 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 493:
#line 1749 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2848 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 494:
#line 1751 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2858 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 495:
#line 1760 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2869 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 496:
#line 1765 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2878 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 499:
#line 1774 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2888 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 500:
#line 1778 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2898 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 513:
#line 1803 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2906 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 514:
#line 1805 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2916 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 515:
#line 1811 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2925 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 516:
#line 1819 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2936 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 517:
#line 1824 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2947 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 529:
#line 1846 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2955 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 530:
#line 1848 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2964 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 531:
#line 1853 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2970 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 532:
#line 1854 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2976 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 533:
#line 1855 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2982 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 534:
#line 1858 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2991 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 535:
#line 1863 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2999 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 536:
#line 1865 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3009 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 537:
#line 1871 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3018 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 538:
#line 1876 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3027 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 539:
#line 1883 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3036 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 540:
#line 1890 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3047 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 541:
#line 1895 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3056 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 549:
#line 1911 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3064 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 550:
#line 1913 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3074 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 551:
#line 1919 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3082 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 552:
#line 1921 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3092 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 553:
#line 1929 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3100 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 554:
#line 1931 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 1947 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3129 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 556:
#line 1952 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3140 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 557:
#line 1959 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3150 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 558:
#line 1963 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3160 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 579:
#line 1993 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3169 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 580:
#line 1998 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3177 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 581:
#line 2000 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3187 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 582:
#line 2006 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3195 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 583:
#line 2008 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3205 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 584:
#line 2014 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3214 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 585:
#line 2019 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3222 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 586:
#line 2021 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3232 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 587:
#line 2027 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3241 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 588:
#line 2032 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3250 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 589:
#line 2037 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3258 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 590:
#line 2039 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3267 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 591:
#line 2045 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3273 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 592:
#line 2046 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3279 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 593:
#line 2049 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3287 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 594:
#line 2051 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3297 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 595:
#line 2057 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3306 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 596:
#line 2062 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3315 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 597:
#line 2067 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3323 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 598:
#line 2069 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3332 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 599:
#line 2075 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3340 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 600:
#line 2078 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3348 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 601:
#line 2081 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3356 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 602:
#line 2084 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3364 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 603:
#line 2087 "dhcp6_parser.yy" // lalr1.cc:907
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3373 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 604:
#line 2093 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3381 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 605:
#line 2095 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3391 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 606:
#line 2101 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3399 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 607:
#line 2103 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3409 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 608:
#line 2109 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3417 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 609:
#line 2111 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3427 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 610:
#line 2119 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3435 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 611:
#line 2121 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3444 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 612:
#line 2126 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3452 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 613:
#line 2128 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3461 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 614:
#line 2133 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3469 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 615:
#line 2135 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3478 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 616:
#line 2142 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3488 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 617:
#line 2146 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3496 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 618:
#line 2151 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3507 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 619:
#line 2156 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3517 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 620:
#line 2162 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3527 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 621:
#line 2166 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No config_control params are required
    // parsing completed
}
#line 3536 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 626:
#line 2181 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3547 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 627:
#line 2186 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3556 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 628:
#line 2196 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3567 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 629:
#line 2201 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3576 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 630:
#line 2206 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3586 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 631:
#line 2210 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // parsing completed
}
#line 3594 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 635:
#line 2226 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3605 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 636:
#line 2231 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3614 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 639:
#line 2243 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3624 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 640:
#line 2247 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3632 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 650:
#line 2264 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3641 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 651:
#line 2269 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3649 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 652:
#line 2271 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3659 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 653:
#line 2277 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3670 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 654:
#line 2282 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3679 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 657:
#line 2291 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3689 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 658:
#line 2295 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3697 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 665:
#line 2309 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3705 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 666:
#line 2311 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3715 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 667:
#line 2317 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3724 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 668:
#line 2322 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3733 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 669:
#line 2327 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3742 "dhcp6_parser.cc" // lalr1.cc:907
    break;


#line 3746 "dhcp6_parser.cc" // lalr1.cc:907
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


  const short Dhcp6Parser::yypact_ninf_ = -820;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     425,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,   102,    46,    99,   114,
     125,   133,   144,   148,   179,   204,   206,   217,   219,   242,
     251,   257,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,    46,    22,    44,    45,    64,   230,    69,    33,
     244,   205,    53,   194,   -23,   364,    81,    57,  -820,   268,
     262,   280,   278,   287,  -820,  -820,  -820,  -820,  -820,   288,
    -820,    56,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,   290,   301,   311,   312,   328,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,   344,  -820,  -820,  -820,  -820,
      97,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,   345,  -820,   128,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,   346,   372,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,   135,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,   182,
    -820,  -820,  -820,  -820,  -820,   378,  -820,   399,   403,  -820,
    -820,  -820,  -820,  -820,  -820,   185,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,   333,   365,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,   384,  -820,  -820,   413,  -820,  -820,  -820,
     427,  -820,  -820,   433,   439,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,   442,   445,
    -820,  -820,  -820,  -820,   444,   450,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,   186,  -820,
    -820,  -820,   451,  -820,  -820,   452,  -820,   453,   454,  -820,
    -820,   455,   456,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
     225,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,   232,  -820,
    -820,  -820,  -820,   233,  -820,  -820,  -820,    46,    46,  -820,
     284,   457,   458,   460,   461,   463,  -820,    44,  -820,    57,
     464,   465,   466,   467,   468,   302,   305,   306,   307,   308,
     471,   476,   477,   478,   479,   480,   494,   498,   499,   500,
     503,   504,   505,   506,   507,   508,   342,   511,   512,   513,
      45,  -820,   514,   347,    64,  -820,   515,   520,   521,   522,
     523,   357,   356,   526,   527,   528,   531,   230,  -820,   532,
      69,  -820,   533,   367,   535,   369,   375,    33,  -820,   539,
     543,   544,   546,   547,   548,   551,  -820,   244,  -820,   553,
     554,   389,   555,   557,   558,   390,  -820,    53,   560,   394,
     396,  -820,   194,   566,   567,   106,  -820,   400,   568,   570,
     404,   572,   406,   407,   591,   592,   424,   426,   594,   596,
     598,   599,   364,  -820,   600,    81,  -820,   601,    57,  -820,
    -820,  -820,   602,   603,   604,    46,    46,    46,  -820,   245,
     605,   606,   607,   608,   611,  -820,  -820,  -820,  -820,  -820,
     438,   612,   613,   614,   615,   459,   616,   618,   619,   620,
     621,   622,   625,   626,   627,   628,  -820,   629,   615,   630,
    -820,   633,  -820,  -820,   634,   635,   462,   472,   473,  -820,
    -820,   359,   633,   474,   638,  -820,   481,  -820,   482,  -820,
     483,  -820,  -820,  -820,   633,   633,   633,   484,   485,   486,
     487,  -820,   488,   489,  -820,   490,   491,   492,  -820,  -820,
     493,  -820,  -820,  -820,   495,    46,  -820,  -820,   496,   497,
    -820,   501,  -820,  -820,   -61,   510,  -820,  -820,   -25,   502,
     509,   516,  -820,   636,  -820,   642,  -820,    46,    45,    81,
    -820,  -820,  -820,  -820,    57,    64,   143,   143,   641,  -820,
     643,   657,   661,  -820,  -820,  -820,   662,   -31,    46,   237,
     525,   663,   666,   667,   218,   118,    84,  -820,   364,  -820,
    -820,   668,   669,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,   -19,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,   670,   641,
    -820,   249,   258,   259,   270,  -820,  -820,  -820,  -820,   645,
     674,   676,   677,   678,  -820,   679,   680,  -820,   681,   683,
     684,  -820,   277,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,   300,  -820,   685,   617,  -820,  -820,   686,   623,  -820,
    -820,   687,   691,  -820,  -820,   689,   693,  -820,  -820,   692,
     694,  -820,  -820,  -820,   138,  -820,  -820,  -820,   695,  -820,
    -820,  -820,   160,  -820,  -820,  -820,  -820,   303,  -820,  -820,
    -820,   377,  -820,  -820,   696,   697,  -820,  -820,   698,   700,
    -820,   701,   702,   703,   704,   705,   706,   304,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,   707,   708,   709,
    -820,  -820,  -820,  -820,   336,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,   337,  -820,  -820,  -820,
     348,   519,  -820,   710,   711,  -820,  -820,   712,   714,  -820,
    -820,  -820,   682,  -820,  -820,   410,  -820,   713,  -820,  -820,
    -820,  -820,   716,   717,   718,   719,   556,   436,   559,   542,
     561,   720,   562,   563,   721,   564,   565,   569,   143,  -820,
    -820,   143,  -820,   641,   230,  -820,   643,    53,  -820,   657,
     194,  -820,   661,   379,  -820,   662,   -31,  -820,  -820,   237,
    -820,   722,   525,  -820,   190,   663,  -820,   244,  -820,   666,
     -23,  -820,   667,   573,   574,   575,   576,   577,   578,   218,
    -820,   724,   725,   579,   580,   581,   118,  -820,   727,   733,
      84,  -820,  -820,  -820,   732,   736,    69,  -820,   668,    33,
    -820,   669,   737,  -820,   134,   670,  -820,  -820,   416,   529,
     583,   584,  -820,  -820,  -820,  -820,  -820,   585,  -820,  -820,
     586,  -820,  -820,  -820,  -820,   349,  -820,   358,  -820,   735,
    -820,   749,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,   366,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,   588,  -820,  -820,   755,  -820,
    -820,  -820,  -820,  -820,   752,   758,  -820,  -820,  -820,  -820,
    -820,   754,  -820,   381,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,   -27,   593,  -820,  -820,  -820,  -820,   595,   610,
    -820,  -820,   650,   388,  -820,   391,  -820,   653,  -820,   762,
    -820,  -820,  -820,  -820,  -820,   401,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,   379,  -820,  -820,   764,   640,
    -820,   190,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,   765,   655,   767,   134,  -820,
    -820,   659,  -820,  -820,   770,  -820,   665,  -820,  -820,   771,
    -820,  -820,   437,  -820,     8,   771,  -820,  -820,   768,   773,
     777,   420,  -820,  -820,  -820,  -820,  -820,  -820,   780,   654,
     660,   672,     8,  -820,   675,  -820,  -820,  -820,  -820,  -820
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
     336,    21,   373,    23,   222,    25,   557,    27,   630,    29,
     620,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     460,     0,   338,   375,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   628,   610,   612,   614,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   616,   618,
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
     227,   228,     0,   580,   582,     0,   585,     0,     0,   589,
     593,     0,     0,   597,   604,   606,   608,   578,   576,   577,
       0,   559,   561,   562,   563,   564,   565,   566,   567,   568,
     569,   570,   571,   572,   573,   574,   575,   635,     0,   632,
     634,   626,   625,     0,   622,   624,    48,     0,     0,    41,
       0,     0,     0,     0,     0,     0,    59,     0,    61,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    73,     0,     0,     0,   117,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   258,     0,
       0,   404,     0,     0,     0,     0,     0,     0,   429,     0,
       0,     0,     0,     0,     0,     0,   459,     0,   329,     0,
       0,     0,     0,     0,     0,     0,   337,     0,     0,     0,
       0,   374,     0,     0,     0,     0,   223,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   558,     0,     0,   631,     0,     0,   621,
      52,    45,     0,     0,     0,     0,     0,     0,    63,     0,
       0,     0,     0,     0,     0,   107,   108,   109,   110,   111,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   539,     0,     0,     0,
      75,     0,   127,   119,     0,     0,     0,     0,     0,   297,
     298,     0,     0,     0,     0,   260,     0,   406,     0,   445,
       0,   448,   449,   431,     0,     0,     0,     0,     0,     0,
       0,   463,     0,     0,   353,     0,     0,     0,   364,   341,
       0,   393,   394,   378,     0,     0,   225,   579,     0,     0,
     584,     0,   587,   588,     0,     0,   595,   596,     0,     0,
       0,     0,   560,     0,   633,     0,   623,     0,     0,     0,
     611,   613,   615,   617,     0,     0,     0,     0,   134,   113,
     251,   330,   367,    42,   417,   419,   301,     0,    49,     0,
       0,     0,   452,   216,     0,     0,     0,   554,     0,    53,
     126,   397,   422,   282,   284,   286,   293,   294,   295,   296,
     292,   290,   288,     0,   415,   444,   447,   488,   476,   478,
     480,   482,   484,   486,   356,   174,   360,   358,   363,   390,
     230,   232,   581,   583,   586,   591,   592,   590,   594,   599,
     600,   601,   602,   603,   598,   605,   607,   609,     0,   134,
      46,     0,     0,     0,     0,   160,   166,   168,   170,     0,
       0,     0,     0,     0,   183,     0,     0,   186,     0,     0,
       0,   159,     0,   140,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   154,   155,   156,   157,   152,   153,
     158,     0,   138,     0,   135,   136,   255,     0,   252,   253,
     334,     0,   331,   332,   371,     0,   368,   369,   305,     0,
     302,   303,   201,   202,     0,   197,   199,   200,     0,   210,
     211,   207,     0,   205,   208,   209,   193,     0,   190,   192,
     499,     0,   497,   456,     0,   453,   454,   220,     0,   217,
     218,     0,     0,     0,     0,     0,     0,     0,   235,   237,
     238,   239,   240,   241,   242,   529,   535,     0,     0,     0,
     528,   525,   526,   527,     0,   518,   520,   523,   521,   522,
     524,   549,   551,   548,   546,   547,     0,   542,   544,   545,
       0,    55,   401,     0,   398,   399,   426,     0,   423,   424,
     493,   492,     0,   491,   639,     0,   637,     0,    71,   629,
     619,   115,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   129,
     131,     0,   133,     0,     0,   250,     0,   338,   327,     0,
     375,   366,     0,     0,   300,     0,     0,   196,   213,     0,
     204,     0,     0,   189,   501,     0,   496,   460,   451,     0,
       0,   215,     0,     0,     0,     0,     0,     0,     0,     0,
     234,     0,     0,     0,     0,     0,     0,   517,     0,     0,
       0,   541,   556,    57,     0,    56,     0,   396,     0,     0,
     421,     0,     0,   490,     0,     0,   636,   627,     0,     0,
       0,     0,   172,   175,   176,   177,   178,     0,   185,   179,
       0,   180,   181,   182,   141,     0,   137,     0,   254,     0,
     333,     0,   370,   325,   320,   322,   313,   314,   309,   310,
     311,   312,   318,   319,   317,   321,     0,   307,   315,   323,
     324,   316,   304,   198,   206,     0,   191,   513,     0,   511,
     512,   508,   509,   510,     0,   502,   503,   505,   506,   507,
     498,     0,   455,     0,   219,   243,   244,   245,   246,   247,
     248,   236,     0,     0,   534,   537,   538,   519,     0,     0,
     543,    54,     0,     0,   400,     0,   425,     0,   653,     0,
     651,   649,   643,   647,   648,     0,   641,   645,   646,   644,
     638,   162,   163,   164,   165,   161,   167,   169,   171,   184,
     187,   139,   256,   335,   372,     0,   306,   194,     0,     0,
     500,     0,   457,   221,   531,   532,   533,   530,   536,   550,
     552,    58,   402,   427,   494,     0,     0,     0,     0,   640,
     308,     0,   515,   504,     0,   650,     0,   642,   514,     0,
     652,   657,     0,   655,     0,     0,   654,   665,     0,     0,
       0,     0,   659,   661,   662,   663,   664,   656,     0,     0,
       0,     0,     0,   658,     0,   667,   668,   669,   660,   666
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,    14,  -820,  -447,
    -820,   115,  -820,  -820,  -820,  -820,   132,  -820,  -337,  -820,
    -820,  -820,   -74,  -820,  -820,  -820,   432,  -820,  -820,  -820,
    -820,   199,   392,   -70,   -58,   -55,   -38,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,   216,   429,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,   169,  -820,    -4,  -820,  -573,
       6,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,   -46,  -820,  -603,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,   -15,
    -820,  -820,  -820,  -820,  -820,    -8,  -596,  -820,  -820,  -820,
    -820,    -9,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
     -21,  -820,  -820,  -820,   -17,   402,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,   -20,  -820,  -820,  -820,  -820,  -820,  -820,
    -819,  -820,  -820,  -820,    10,  -820,  -820,  -820,    16,   446,
    -820,  -820,  -815,  -820,  -813,  -820,   -34,  -820,   -32,  -820,
    -805,  -820,  -820,  -820,  -804,  -820,  -820,  -820,  -820,    11,
    -820,  -820,  -164,   787,  -820,  -820,  -820,  -820,  -820,    20,
    -820,  -820,  -820,    23,  -820,   428,  -820,   -41,  -820,  -820,
    -820,  -820,  -820,   -40,  -820,  -820,  -820,  -820,  -820,   -12,
    -820,  -820,  -820,    19,  -820,  -820,  -820,    24,  -820,   421,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,   -26,  -820,  -820,  -820,   -18,   469,  -820,  -820,   -62,
    -820,   -50,  -820,  -820,  -820,  -820,  -820,   -24,  -820,  -820,
    -820,   -16,   449,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
     -36,  -820,  -820,  -820,    12,  -820,  -820,  -820,    13,  -820,
     448,   246,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -803,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,    17,  -820,  -820,  -820,  -145,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,     2,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,     0,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,   273,
     422,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,
    -820,  -820,  -820,  -820,  -820,  -820,  -820,  -820,  -344,   414,
    -820,  -820,  -820,  -820,  -820,  -820,   309,   418,  -820,  -820,
    -820,   -10,  -820,  -820,  -152,  -820,  -820,  -820,  -820,  -820,
    -820,  -168,  -820,  -820,  -183,  -820,  -820,  -820,  -820,  -820
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   604,    92,    93,    43,    72,    89,    90,   620,   801,
     894,   895,   352,    45,    74,   101,   102,   103,   361,    47,
      75,   140,   141,   142,   143,   144,   145,   146,   147,   380,
     148,   371,    49,    76,   175,   176,   177,   402,   178,   149,
     372,   150,   373,   151,   374,   713,   714,   715,   841,   692,
     693,   694,   822,  1015,   695,   823,   696,   824,   697,   825,
     698,   699,   440,   700,   701,   702,   703,   704,   705,   706,
     707,   708,   831,   709,   710,   834,   152,   390,   747,   748,
     749,   861,   153,   387,   734,   735,   736,   737,   154,   389,
     742,   743,   744,   745,   155,   388,   156,   393,   758,   759,
     760,   870,    65,    84,   308,   309,   310,   453,   311,   454,
     157,   394,   767,   768,   769,   770,   771,   772,   773,   774,
     158,   381,   717,   718,   719,   844,    51,    77,   197,   198,
     199,   408,   200,   409,   201,   410,   202,   415,   203,   414,
     204,   413,   630,   205,   206,   159,   386,   729,   730,   731,
     853,   946,   947,   160,   382,    59,    81,   721,   722,   723,
     847,    61,    82,   273,   274,   275,   276,   277,   278,   279,
     439,   280,   443,   281,   442,   282,   283,   444,   284,   161,
     383,   725,   726,   727,   850,    63,    83,   294,   295,   296,
     297,   298,   448,   299,   300,   301,   302,   208,   406,   803,
     804,   805,   896,    53,    78,   219,   220,   221,   419,   162,
     384,   163,   385,   211,   407,   807,   808,   809,   899,    55,
      79,   235,   236,   237,   422,   238,   239,   424,   240,   241,
     164,   392,   754,   755,   756,   867,    57,    80,   253,   254,
     255,   256,   430,   257,   431,   258,   432,   259,   433,   260,
     434,   261,   435,   262,   429,   213,   416,   812,   813,   902,
     165,   391,   751,   752,   864,   964,   965,   966,   967,   968,
    1028,   969,   166,   395,   784,   785,   786,   881,  1037,   787,
     788,   882,   789,   790,   167,   168,   397,   796,   797,   798,
     888,   799,   889,   169,   398,   170,   399,    67,    85,   330,
     331,   332,   333,   458,   334,   459,   335,   336,   461,   337,
     338,   339,   464,   657,   340,   465,   341,   342,   343,   468,
     664,   344,   469,   345,   470,   346,   471,   104,   363,   105,
     364,   106,   365,   171,   369,   370,    71,    87,   353,   354,
     355,   477,   107,   362,    69,    86,   348,   349,   350,   474,
     815,   816,   904,  1005,  1006,  1007,  1008,  1047,  1009,  1045,
    1062,  1063,  1064,  1071,  1072,  1073,  1078,  1074,  1075,  1076
  };

  const unsigned short
  Dhcp6Parser::yytable_[] =
  {
     100,   139,   174,   192,   215,   229,   249,   193,   271,   290,
     307,   327,   781,   741,   179,   209,   222,   233,   251,   194,
     285,   303,   195,   328,   711,   489,   180,   210,   223,   234,
     252,    40,   286,   304,   939,   329,   272,   291,   940,   196,
     941,   212,   292,   293,   216,   230,   217,   231,   944,   945,
     951,    33,   108,    34,    94,    35,   109,   603,   110,   367,
     732,   111,   112,   113,   368,   207,   218,   232,   250,   351,
     243,   603,   264,   655,   656,   305,   306,   810,   172,   173,
     122,  1034,  1035,  1036,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   224,   225,   226,   227,   228,   123,   124,
     400,   265,    32,   266,   267,   401,    44,   268,   269,   270,
     123,   124,   659,   660,   661,   662,   122,   189,   123,   124,
     190,    46,   125,   126,   127,   128,   129,   214,   130,   123,
     124,   404,    48,   131,   123,   124,   405,   775,   417,   733,
      50,   856,   132,   418,   857,   133,   680,    99,   663,   123,
     124,    52,   134,   189,  1067,    54,   190,  1068,  1069,  1070,
     135,   136,   675,   859,   137,   138,   860,   676,   677,   678,
     679,   680,   681,   682,   683,   684,   685,   686,   687,   688,
     689,   690,   265,   123,   124,   420,    56,    95,   427,   455,
     421,   265,    91,   428,   456,   631,    96,    97,    98,   123,
     124,   791,   792,    99,   305,   306,   939,   637,   638,   639,
     940,    58,   941,    60,    99,    99,    36,    37,    38,    39,
     944,   945,   951,    99,    62,   347,    64,    99,   472,   776,
     777,   778,   779,   473,    99,   475,   478,   122,   265,    99,
     476,   479,   265,   287,   266,   267,   288,   289,   478,    66,
     673,   121,   400,   593,    99,   123,   124,   818,    68,   123,
     124,   475,   478,   741,    70,   357,   819,   820,   925,   114,
     115,   116,   117,   404,   356,   957,   958,   122,   821,   998,
     838,   999,  1000,   781,   358,   839,   359,   181,    99,   182,
     360,   122,   366,   100,   375,   123,   124,   183,   184,   185,
     186,   187,   188,   838,    99,   376,   862,   879,   840,   123,
     124,   863,   880,    99,   189,   377,   378,   190,   131,   761,
     762,   763,   764,   765,   766,   191,   139,   242,   732,   739,
     174,   740,   379,   243,   244,   245,   246,   247,   248,   886,
     890,   436,   179,   192,   887,   891,   215,   193,   396,   403,
     411,   472,   838,   229,   180,   209,   892,  1021,   222,   194,
      99,   417,   195,   249,    99,   233,  1022,   210,   437,  1025,
     223,   480,   481,   271,  1026,   251,   412,   234,   290,   196,
     865,   212,   423,   866,   455,   285,   216,   252,   217,  1033,
     303,   420,   438,   230,   427,   231,  1042,   286,   327,  1043,
      99,   272,   304,   425,  1048,   207,   291,   426,   218,  1049,
     328,   292,   293,   905,    99,   232,   906,   441,   114,   115,
     116,   117,   329,  1082,   120,   250,   122,   265,  1083,   123,
     124,   445,   626,   627,   628,   629,  1011,  1012,  1013,  1014,
    1065,   446,   447,  1066,   123,   124,   449,   184,   185,   450,
     187,   188,   451,   452,   482,   457,   460,   462,   463,   466,
     467,   483,   484,   189,   485,   486,   190,   487,   490,   491,
     492,   493,   494,   495,   191,   500,   496,   497,   498,   499,
     501,   502,   503,   504,   505,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   506,   590,
     591,   592,   507,   508,   509,   325,   326,   510,   511,   512,
     513,   514,   515,   516,   139,   517,   518,   519,   521,   524,
     522,   174,   691,   691,   525,   526,   527,   528,   529,   530,
     531,   532,   533,   179,    99,   534,   536,   538,   539,   540,
     541,   780,   793,   544,   327,   180,   542,   545,   546,    99,
     547,   548,   549,   782,   794,   550,   328,   552,   553,   555,
     554,   556,   557,   558,   560,   783,   795,   561,   329,   562,
     564,   565,   568,   567,   569,   570,   571,   572,   573,   651,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,   574,   575,   576,   578,   577,
     579,   670,   580,   581,   583,   585,   587,   746,   599,   913,
     588,   589,   594,   595,   596,   597,   598,   600,   601,   602,
     843,   606,    34,   607,   608,   609,   846,   611,   610,   605,
     612,   613,   623,   617,   614,   615,   616,   618,   619,   621,
     622,   668,   624,   625,   632,   633,   658,   669,   712,   826,
     716,   634,   635,   636,   640,   641,   642,   643,   644,   645,
     646,   647,   648,   649,   720,   650,   652,   653,   724,   728,
     750,   654,   665,   753,   757,   802,   806,   814,   827,   666,
     828,   829,   830,   832,   833,   835,   667,   836,   837,   893,
     903,   842,   845,   848,   849,   851,   852,   855,   854,  1016,
     869,   858,   868,   872,   871,   873,   874,   875,   876,   877,
     878,   883,   884,   885,   898,   915,   897,   901,   900,   907,
     908,   909,   910,   911,   917,   920,   955,   912,   982,   983,
     914,   988,   916,   918,   919,   921,   922,   989,   991,   992,
     738,   997,   923,  1023,   975,   976,   977,   978,   979,   980,
     984,   985,   986,  1017,  1018,  1019,  1020,  1024,  1027,  1029,
    1030,  1031,  1032,  1038,   691,  1039,  1046,   691,  1051,  1054,
     192,  1056,  1079,   271,   193,  1059,   290,  1080,  1061,   933,
    1040,  1081,   209,   934,  1084,   285,   194,   671,   303,   195,
     959,   949,   520,   249,   210,   935,   307,   286,   936,   488,
     304,   272,   962,   950,   291,   251,   196,   938,   212,   292,
     293,   674,   780,  1052,   963,   937,   793,   252,   960,   942,
    1041,   943,   215,  1044,   782,   229,  1055,  1085,   794,  1058,
    1001,  1086,   207,   523,   222,  1060,   783,   233,   817,   926,
     795,   948,  1003,  1087,   924,  1089,   223,   956,   953,   234,
     954,   974,   961,   973,  1004,   250,   928,   566,  1002,   981,
     927,  1050,   216,   535,   217,   230,   952,   231,   263,   930,
     929,   932,   994,   563,   931,   559,   543,   996,   993,   811,
     971,   972,   970,   995,   218,   551,  1053,   232,   987,   537,
     990,   800,   586,   584,   582,  1010,  1057,  1077,   672,  1088,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   933,     0,     0,     0,   934,     0,   959,     0,     0,
       0,     0,     0,   949,     0,     0,     0,   935,     0,   962,
     936,     0,     0,     0,  1001,   950,     0,     0,     0,   938,
       0,   963,     0,     0,     0,   960,  1003,   937,     0,     0,
       0,   942,     0,   943,     0,     0,     0,     0,  1004,     0,
       0,     0,  1002,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   948,     0,     0,     0,     0,     0,   961
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    77,    82,    83,
      84,    85,   615,   609,    76,    77,    78,    79,    80,    77,
      82,    83,    77,    85,   597,   369,    76,    77,    78,    79,
      80,    17,    82,    83,   853,    85,    82,    83,   853,    77,
     853,    77,    83,    83,    78,    79,    78,    79,   853,   853,
     853,     5,     7,     7,    10,     9,    11,   504,    13,     3,
      91,    16,    17,    18,     8,    77,    78,    79,    80,    12,
      89,   518,    19,   134,   135,    98,    99,    96,    14,    15,
      47,   108,   109,   110,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    60,    61,    62,    63,    64,    65,    66,
       3,    48,     0,    50,    51,     8,     7,    54,    55,    56,
      65,    66,   137,   138,   139,   140,    47,    84,    65,    66,
      87,     7,    77,    78,    79,    80,    81,    58,    83,    65,
      66,     3,     7,    88,    65,    66,     8,    19,     3,   170,
       7,     3,    97,     8,     6,   100,    28,   170,   173,    65,
      66,     7,   107,    84,   146,     7,    87,   149,   150,   151,
     115,   116,    19,     3,   119,   120,     6,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    48,    65,    66,     3,     7,   143,     3,     3,
       8,    48,   170,     8,     8,   532,   152,   153,   154,    65,
      66,   117,   118,   170,    98,    99,  1025,   544,   545,   546,
    1025,     7,  1025,     7,   170,   170,   170,   171,   172,   173,
    1025,  1025,  1025,   170,     7,   144,     7,   170,     3,   111,
     112,   113,   114,     8,   170,     3,     3,    47,    48,   170,
       8,     8,    48,    49,    50,    51,    52,    53,     3,     7,
     594,    46,     3,     8,   170,    65,    66,     8,     7,    65,
      66,     3,     3,   859,     7,     3,     8,     8,   841,    39,
      40,    41,    42,     3,     6,    85,    86,    47,     8,   145,
       3,   147,   148,   886,     4,     8,     8,    57,   170,    59,
       3,    47,     4,   367,     4,    65,    66,    67,    68,    69,
      70,    71,    72,     3,   170,     4,     3,     3,     8,    65,
      66,     8,     8,   170,    84,     4,     4,    87,    88,   101,
     102,   103,   104,   105,   106,    95,   400,    83,    91,    92,
     404,    94,     4,    89,    90,    91,    92,    93,    94,     3,
       3,     8,   404,   417,     8,     8,   420,   417,     4,     4,
       4,     3,     3,   427,   404,   417,     8,     8,   420,   417,
     170,     3,   417,   437,   170,   427,     8,   417,     3,     3,
     420,   357,   358,   447,     8,   437,     4,   427,   452,   417,
       3,   417,     4,     6,     3,   447,   420,   437,   420,     8,
     452,     3,     8,   427,     3,   427,     8,   447,   472,     8,
     170,   447,   452,     4,     3,   417,   452,     4,   420,     8,
     472,   452,   452,     3,   170,   427,     6,     4,    39,    40,
      41,    42,   472,     3,    45,   437,    47,    48,     8,    65,
      66,     4,    73,    74,    75,    76,    20,    21,    22,    23,
       3,     8,     3,     6,    65,    66,     4,    68,    69,     4,
      71,    72,     8,     3,   170,     4,     4,     4,     4,     4,
       4,     4,     4,    84,     4,     4,    87,     4,     4,     4,
       4,     4,     4,   171,    95,     4,   171,   171,   171,   171,
       4,     4,     4,     4,     4,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,     4,   485,
     486,   487,     4,     4,     4,   141,   142,     4,     4,     4,
       4,     4,     4,   171,   588,     4,     4,     4,     4,     4,
     173,   595,   596,   597,     4,     4,     4,     4,   171,   173,
       4,     4,     4,   595,   170,     4,     4,     4,   171,     4,
     171,   615,   616,     4,   618,   595,   171,     4,     4,   170,
       4,     4,     4,   615,   616,     4,   618,     4,     4,     4,
     171,     4,     4,   173,     4,   615,   616,   173,   618,   173,
       4,     4,     4,   173,     4,   171,     4,   171,   171,   565,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,     4,     4,   173,     4,   173,
       4,   587,     4,     4,     4,     4,     4,    82,   170,   173,
       7,     7,     7,     7,     7,     7,     5,     5,     5,     5,
       3,     5,     7,     5,     5,     5,     3,     5,     7,   170,
       5,     5,   170,   518,     7,     7,     7,     7,     5,     5,
       5,     5,   170,   170,   170,     7,   136,     5,     7,     4,
       7,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,     7,   170,   170,   170,     7,     7,
       7,   170,   170,     7,     7,     7,     7,     7,     4,   170,
       4,     4,     4,     4,     4,     4,   170,     4,     4,   170,
       8,     6,     6,     6,     3,     6,     3,     3,     6,   170,
       3,     6,     6,     3,     6,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     3,   173,     6,     3,     6,     6,
       4,     4,     4,     4,     4,     4,     4,   171,     4,     4,
     171,     4,   171,   171,   171,   171,   171,     4,     6,     3,
     608,     4,   173,     8,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   170,   170,   170,   170,     8,   170,     4,
       8,     3,     8,   170,   838,   170,     4,   841,     4,     4,
     844,     4,     4,   847,   844,     5,   850,     4,     7,   853,
     170,     4,   844,   853,     4,   847,   844,   588,   850,   844,
     864,   853,   400,   867,   844,   853,   870,   847,   853,   367,
     850,   847,   864,   853,   850,   867,   844,   853,   844,   850,
     850,   595,   886,   173,   864,   853,   890,   867,   864,   853,
     170,   853,   896,   170,   886,   899,   171,   173,   890,   170,
     904,   171,   844,   404,   896,   170,   886,   899,   669,   843,
     890,   853,   904,   171,   838,   170,   896,   862,   856,   899,
     859,   872,   864,   870,   904,   867,   846,   455,   904,   879,
     844,  1025,   896,   417,   896,   899,   855,   899,    81,   849,
     847,   852,   898,   452,   850,   447,   427,   901,   896,   633,
     867,   869,   865,   899,   896,   437,  1031,   899,   886,   420,
     890,   618,   478,   475,   472,   905,  1048,  1065,   589,  1082,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1025,    -1,    -1,    -1,  1025,    -1,  1031,    -1,    -1,
      -1,    -1,    -1,  1025,    -1,    -1,    -1,  1025,    -1,  1031,
    1025,    -1,    -1,    -1,  1048,  1025,    -1,    -1,    -1,  1025,
      -1,  1031,    -1,    -1,    -1,  1031,  1048,  1025,    -1,    -1,
      -1,  1025,    -1,  1025,    -1,    -1,    -1,    -1,  1048,    -1,
      -1,    -1,  1048,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1025,    -1,    -1,    -1,    -1,    -1,  1031
  };

  const unsigned short
  Dhcp6Parser::yystos_[] =
  {
       0,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,     0,     5,     7,     9,   170,   171,   172,   173,
     191,   192,   193,   198,     7,   207,     7,   213,     7,   226,
       7,   320,     7,   397,     7,   413,     7,   430,     7,   349,
       7,   355,     7,   379,     7,   296,     7,   491,     7,   538,
       7,   530,   199,   194,   208,   214,   227,   321,   398,   414,
     431,   350,   356,   380,   297,   492,   539,   531,   191,   200,
     201,   170,   196,   197,    10,   143,   152,   153,   154,   170,
     206,   209,   210,   211,   521,   523,   525,   536,     7,    11,
      13,    16,    17,    18,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    65,    66,    77,    78,    79,    80,    81,
      83,    88,    97,   100,   107,   115,   116,   119,   120,   206,
     215,   216,   217,   218,   219,   220,   221,   222,   224,   233,
     235,   237,   270,   276,   282,   288,   290,   304,   314,   339,
     347,   373,   403,   405,   424,   454,   466,   478,   479,   487,
     489,   527,    14,    15,   206,   228,   229,   230,   232,   403,
     405,    57,    59,    67,    68,    69,    70,    71,    72,    84,
      87,    95,   206,   217,   218,   219,   220,   322,   323,   324,
     326,   328,   330,   332,   334,   337,   338,   373,   391,   403,
     405,   407,   424,   449,    58,   206,   330,   332,   373,   399,
     400,   401,   403,   405,    60,    61,    62,    63,    64,   206,
     330,   332,   373,   403,   405,   415,   416,   417,   419,   420,
     422,   423,    83,    89,    90,    91,    92,    93,    94,   206,
     373,   403,   405,   432,   433,   434,   435,   437,   439,   441,
     443,   445,   447,   347,    19,    48,    50,    51,    54,    55,
      56,   206,   255,   357,   358,   359,   360,   361,   362,   363,
     365,   367,   369,   370,   372,   403,   405,    49,    52,    53,
     206,   255,   361,   367,   381,   382,   383,   384,   385,   387,
     388,   389,   390,   403,   405,    98,    99,   206,   298,   299,
     300,   302,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   141,   142,   206,   403,   405,
     493,   494,   495,   496,   498,   500,   501,   503,   504,   505,
     508,   510,   511,   512,   515,   517,   519,   144,   540,   541,
     542,    12,   206,   532,   533,   534,     6,     3,     4,     8,
       3,   212,   537,   522,   524,   526,     4,     3,     8,   528,
     529,   225,   234,   236,   238,     4,     4,     4,     4,     4,
     223,   315,   348,   374,   404,   406,   340,   277,   289,   283,
     271,   455,   425,   291,   305,   467,     4,   480,   488,   490,
       3,     8,   231,     4,     3,     8,   392,   408,   325,   327,
     329,     4,     4,   335,   333,   331,   450,     3,     8,   402,
       3,     8,   418,     4,   421,     4,     4,     3,     8,   448,
     436,   438,   440,   442,   444,   446,     8,     3,     8,   364,
     256,     4,   368,   366,   371,     4,     8,     3,   386,     4,
       4,     8,     3,   301,   303,     3,     8,     4,   497,   499,
       4,   502,     4,     4,   506,   509,     4,     4,   513,   516,
     518,   520,     3,     8,   543,     3,     8,   535,     3,     8,
     191,   191,   170,     4,     4,     4,     4,     4,   210,   532,
       4,     4,     4,     4,     4,   171,   171,   171,   171,   171,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   171,     4,     4,     4,
     216,     4,   173,   229,     4,     4,     4,     4,     4,   171,
     173,     4,     4,     4,     4,   323,     4,   400,     4,   171,
       4,   171,   171,   416,     4,     4,     4,     4,     4,     4,
       4,   434,     4,     4,   171,     4,     4,     4,   173,   359,
       4,   173,   173,   383,     4,     4,   299,   173,     4,     4,
     171,     4,   171,   171,     4,     4,   173,   173,     4,     4,
       4,     4,   494,     4,   541,     4,   533,     4,     7,     7,
     191,   191,   191,     8,     7,     7,     7,     7,     5,   170,
       5,     5,     5,   193,   195,   170,     5,     5,     5,     5,
       7,     5,     5,     5,     7,     7,     7,   195,     7,     5,
     202,     5,     5,   170,   170,   170,    73,    74,    75,    76,
     336,   202,   170,     7,   170,   170,   170,   202,   202,   202,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   191,   170,   170,   170,   134,   135,   507,   136,   137,
     138,   139,   140,   173,   514,   170,   170,   170,     5,     5,
     191,   215,   540,   532,   228,    19,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,   206,   243,   244,   245,   248,   250,   252,   254,   255,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   267,
     268,   243,     7,   239,   240,   241,     7,   316,   317,   318,
       7,   351,   352,   353,     7,   375,   376,   377,     7,   341,
     342,   343,    91,   170,   278,   279,   280,   281,   200,    92,
      94,   280,   284,   285,   286,   287,    82,   272,   273,   274,
       7,   456,   457,     7,   426,   427,   428,     7,   292,   293,
     294,   101,   102,   103,   104,   105,   106,   306,   307,   308,
     309,   310,   311,   312,   313,    19,   111,   112,   113,   114,
     206,   257,   403,   405,   468,   469,   470,   473,   474,   476,
     477,   117,   118,   206,   403,   405,   481,   482,   483,   485,
     493,   203,     7,   393,   394,   395,     7,   409,   410,   411,
      96,   435,   451,   452,     7,   544,   545,   239,     8,     8,
       8,     8,   246,   249,   251,   253,     4,     4,     4,     4,
       4,   266,     4,     4,   269,     4,     4,     4,     3,     8,
       8,   242,     6,     3,   319,     6,     3,   354,     6,     3,
     378,     6,     3,   344,     6,     3,     3,     6,     6,     3,
       6,   275,     3,     8,   458,     3,     6,   429,     6,     3,
     295,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,   471,   475,     4,     4,     4,     3,     8,   484,   486,
       3,     8,     8,   170,   204,   205,   396,     6,     3,   412,
       6,     3,   453,     8,   546,     3,     6,     6,     4,     4,
       4,     4,   171,   173,   171,   173,   171,     4,   171,   171,
       4,   171,   171,   173,   244,   243,   241,   322,   318,   357,
     353,   381,   377,   206,   217,   218,   219,   220,   255,   314,
     326,   328,   330,   332,   334,   338,   345,   346,   373,   403,
     405,   449,   343,   279,   285,     4,   273,    85,    86,   206,
     255,   373,   403,   405,   459,   460,   461,   462,   463,   465,
     457,   432,   428,   298,   294,   171,   171,   171,   171,   171,
     171,   307,     4,     4,   171,   171,   171,   469,     4,     4,
     482,     6,     3,   399,   395,   415,   411,     4,   145,   147,
     148,   206,   255,   403,   405,   547,   548,   549,   550,   552,
     545,    20,    21,    22,    23,   247,   170,   170,   170,   170,
     170,     8,     8,     8,     8,     3,     8,   170,   464,     4,
       8,     3,     8,     8,   108,   109,   110,   472,   170,   170,
     170,   170,     8,     8,   170,   553,     4,   551,     3,     8,
     346,     4,   173,   461,     4,   171,     4,   548,   170,     5,
     170,     7,   554,   555,   556,     3,     6,   146,   149,   150,
     151,   557,   558,   559,   561,   562,   563,   555,   560,     4,
       4,     4,     3,     8,     4,   173,   171,   171,   558,   170
  };

  const unsigned short
  Dhcp6Parser::yyr1_[] =
  {
       0,   174,   176,   175,   177,   175,   178,   175,   179,   175,
     180,   175,   181,   175,   182,   175,   183,   175,   184,   175,
     185,   175,   186,   175,   187,   175,   188,   175,   189,   175,
     190,   175,   191,   191,   191,   191,   191,   191,   191,   192,
     194,   193,   195,   196,   196,   197,   197,   199,   198,   200,
     200,   201,   201,   203,   202,   204,   204,   205,   205,   206,
     208,   207,   209,   209,   210,   210,   210,   210,   210,   210,
     212,   211,   214,   213,   215,   215,   216,   216,   216,   216,
     216,   216,   216,   216,   216,   216,   216,   216,   216,   216,
     216,   216,   216,   216,   216,   216,   216,   216,   216,   216,
     216,   216,   216,   216,   216,   216,   216,   217,   218,   219,
     220,   221,   223,   222,   225,   224,   227,   226,   228,   228,
     229,   229,   229,   229,   229,   231,   230,   232,   234,   233,
     236,   235,   238,   237,   239,   239,   240,   240,   242,   241,
     243,   243,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     246,   245,   247,   247,   247,   247,   249,   248,   251,   250,
     253,   252,   254,   256,   255,   257,   258,   259,   260,   261,
     262,   263,   264,   266,   265,   267,   269,   268,   271,   270,
     272,   272,   273,   275,   274,   277,   276,   278,   278,   279,
     279,   280,   281,   283,   282,   284,   284,   285,   285,   285,
     286,   287,   289,   288,   291,   290,   292,   292,   293,   293,
     295,   294,   297,   296,   298,   298,   298,   299,   299,   301,
     300,   303,   302,   305,   304,   306,   306,   307,   307,   307,
     307,   307,   307,   308,   309,   310,   311,   312,   313,   315,
     314,   316,   316,   317,   317,   319,   318,   321,   320,   322,
     322,   323,   323,   323,   323,   323,   323,   323,   323,   323,
     323,   323,   323,   323,   323,   323,   323,   323,   323,   323,
     323,   325,   324,   327,   326,   329,   328,   331,   330,   333,
     332,   335,   334,   336,   336,   336,   336,   337,   338,   340,
     339,   341,   341,   342,   342,   344,   343,   345,   345,   346,
     346,   346,   346,   346,   346,   346,   346,   346,   346,   346,
     346,   346,   346,   346,   346,   346,   348,   347,   350,   349,
     351,   351,   352,   352,   354,   353,   356,   355,   357,   357,
     358,   358,   359,   359,   359,   359,   359,   359,   359,   359,
     359,   359,   360,   361,   362,   364,   363,   366,   365,   368,
     367,   369,   371,   370,   372,   374,   373,   375,   375,   376,
     376,   378,   377,   380,   379,   381,   381,   382,   382,   383,
     383,   383,   383,   383,   383,   383,   383,   383,   384,   386,
     385,   387,   388,   389,   390,   392,   391,   393,   393,   394,
     394,   396,   395,   398,   397,   399,   399,   400,   400,   400,
     400,   400,   400,   400,   402,   401,   404,   403,   406,   405,
     408,   407,   409,   409,   410,   410,   412,   411,   414,   413,
     415,   415,   416,   416,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   418,   417,   419,   421,   420,   422,   423,
     425,   424,   426,   426,   427,   427,   429,   428,   431,   430,
     432,   432,   433,   433,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   436,   435,   438,   437,   440,
     439,   442,   441,   444,   443,   446,   445,   448,   447,   450,
     449,   451,   451,   453,   452,   455,   454,   456,   456,   458,
     457,   459,   459,   460,   460,   461,   461,   461,   461,   461,
     461,   461,   462,   464,   463,   465,   467,   466,   468,   468,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   471,
     470,   472,   472,   472,   473,   475,   474,   476,   477,   478,
     480,   479,   481,   481,   482,   482,   482,   482,   482,   484,
     483,   486,   485,   488,   487,   490,   489,   492,   491,   493,
     493,   494,   494,   494,   494,   494,   494,   494,   494,   494,
     494,   494,   494,   494,   494,   494,   494,   494,   494,   495,
     497,   496,   499,   498,   500,   502,   501,   503,   504,   506,
     505,   507,   507,   509,   508,   510,   511,   513,   512,   514,
     514,   514,   514,   514,   516,   515,   518,   517,   520,   519,
     522,   521,   524,   523,   526,   525,   528,   527,   529,   527,
     531,   530,   532,   532,   533,   533,   535,   534,   537,   536,
     539,   538,   540,   540,   541,   543,   542,   544,   544,   546,
     545,   547,   547,   548,   548,   548,   548,   548,   548,   548,
     549,   551,   550,   553,   552,   554,   554,   556,   555,   557,
     557,   558,   558,   558,   558,   560,   559,   561,   562,   563
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     0,
       4,     1,     1,     0,     4,     3,     3,     0,     4,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     1,     0,     6,     0,     6,
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
  "override_no_update", "override_client_update", "replace_client_name",
  "$@111", "replace_client_name_value", "generated_prefix", "$@112",
  "hostname_char_set", "$@113", "hostname_char_replacement", "$@114",
  "dhcp4_json_object", "$@115", "dhcpddns_json_object", "$@116",
  "control_agent_json_object", "$@117", "config_control", "$@118", "$@119",
  "sub_config_control", "$@120", "config_control_params",
  "config_control_param", "config_databases", "$@121", "logging_object",
  "$@122", "sub_logging", "$@123", "logging_params", "logging_param",
  "loggers", "$@124", "loggers_entries", "logger_entry", "$@125",
  "logger_params", "logger_param", "debuglevel", "severity", "$@126",
  "output_options_list", "$@127", "output_options_list_content",
  "output_entry", "$@128", "output_params_list", "output_params", "output",
  "$@129", "flush", "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short
  Dhcp6Parser::yyrline_[] =
  {
       0,   257,   257,   257,   258,   258,   259,   259,   260,   260,
     261,   261,   262,   262,   263,   263,   264,   264,   265,   265,
     266,   266,   267,   267,   268,   268,   269,   269,   270,   270,
     271,   271,   279,   280,   281,   282,   283,   284,   285,   288,
     293,   293,   304,   307,   308,   311,   315,   322,   322,   329,
     330,   333,   337,   344,   344,   351,   352,   355,   359,   370,
     380,   380,   395,   396,   400,   401,   402,   403,   404,   405,
     408,   408,   423,   423,   432,   433,   438,   439,   440,   441,
     442,   443,   444,   445,   446,   447,   448,   449,   450,   451,
     452,   453,   454,   455,   456,   457,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   471,   476,   481,
     486,   491,   496,   496,   504,   504,   515,   515,   524,   525,
     528,   529,   530,   531,   532,   535,   535,   545,   551,   551,
     563,   563,   575,   575,   585,   586,   589,   590,   593,   593,
     603,   604,   607,   608,   609,   610,   611,   612,   613,   614,
     615,   616,   617,   618,   619,   620,   621,   622,   623,   624,
     627,   627,   634,   635,   636,   637,   640,   640,   648,   648,
     656,   656,   664,   669,   669,   677,   682,   687,   692,   697,
     702,   707,   712,   717,   717,   725,   730,   730,   738,   738,
     748,   749,   751,   753,   753,   771,   771,   781,   782,   785,
     786,   789,   794,   799,   799,   809,   810,   813,   814,   815,
     818,   823,   830,   830,   840,   840,   850,   851,   854,   855,
     858,   858,   868,   868,   878,   879,   880,   883,   884,   887,
     887,   895,   895,   903,   903,   914,   915,   918,   919,   920,
     921,   922,   923,   926,   931,   936,   941,   946,   951,   959,
     959,   972,   973,   976,   977,   984,   984,  1010,  1010,  1021,
    1022,  1026,  1027,  1028,  1029,  1030,  1031,  1032,  1033,  1034,
    1035,  1036,  1037,  1038,  1039,  1040,  1041,  1042,  1043,  1044,
    1045,  1048,  1048,  1056,  1056,  1064,  1064,  1072,  1072,  1080,
    1080,  1090,  1090,  1097,  1098,  1099,  1100,  1103,  1108,  1116,
    1116,  1127,  1128,  1132,  1133,  1136,  1136,  1144,  1145,  1148,
    1149,  1150,  1151,  1152,  1153,  1154,  1155,  1156,  1157,  1158,
    1159,  1160,  1161,  1162,  1163,  1164,  1171,  1171,  1184,  1184,
    1193,  1194,  1197,  1198,  1203,  1203,  1218,  1218,  1232,  1233,
    1236,  1237,  1240,  1241,  1242,  1243,  1244,  1245,  1246,  1247,
    1248,  1249,  1252,  1254,  1259,  1261,  1261,  1269,  1269,  1277,
    1277,  1285,  1287,  1287,  1295,  1304,  1304,  1316,  1317,  1322,
    1323,  1328,  1328,  1340,  1340,  1352,  1353,  1358,  1359,  1364,
    1365,  1366,  1367,  1368,  1369,  1370,  1371,  1372,  1375,  1377,
    1377,  1385,  1387,  1389,  1394,  1402,  1402,  1414,  1415,  1418,
    1419,  1422,  1422,  1432,  1432,  1441,  1442,  1445,  1446,  1447,
    1448,  1449,  1450,  1451,  1454,  1454,  1462,  1462,  1487,  1487,
    1517,  1517,  1529,  1530,  1533,  1534,  1537,  1537,  1549,  1549,
    1561,  1562,  1565,  1566,  1567,  1568,  1569,  1570,  1571,  1572,
    1573,  1574,  1575,  1578,  1578,  1586,  1591,  1591,  1599,  1604,
    1612,  1612,  1622,  1623,  1626,  1627,  1630,  1630,  1639,  1639,
    1648,  1649,  1652,  1653,  1657,  1658,  1659,  1660,  1661,  1662,
    1663,  1664,  1665,  1666,  1667,  1670,  1670,  1680,  1680,  1690,
    1690,  1698,  1698,  1706,  1706,  1714,  1714,  1722,  1722,  1735,
    1735,  1745,  1746,  1749,  1749,  1760,  1760,  1770,  1771,  1774,
    1774,  1784,  1785,  1788,  1789,  1792,  1793,  1794,  1795,  1796,
    1797,  1798,  1801,  1803,  1803,  1811,  1819,  1819,  1831,  1832,
    1835,  1836,  1837,  1838,  1839,  1840,  1841,  1842,  1843,  1846,
    1846,  1853,  1854,  1855,  1858,  1863,  1863,  1871,  1876,  1883,
    1890,  1890,  1900,  1901,  1904,  1905,  1906,  1907,  1908,  1911,
    1911,  1919,  1919,  1929,  1929,  1947,  1947,  1959,  1959,  1969,
    1970,  1973,  1974,  1975,  1976,  1977,  1978,  1979,  1980,  1981,
    1982,  1983,  1984,  1985,  1986,  1987,  1988,  1989,  1990,  1993,
    1998,  1998,  2006,  2006,  2014,  2019,  2019,  2027,  2032,  2037,
    2037,  2045,  2046,  2049,  2049,  2057,  2062,  2067,  2067,  2075,
    2078,  2081,  2084,  2087,  2093,  2093,  2101,  2101,  2109,  2109,
    2119,  2119,  2126,  2126,  2133,  2133,  2142,  2142,  2151,  2151,
    2162,  2162,  2172,  2173,  2177,  2178,  2181,  2181,  2196,  2196,
    2206,  2206,  2217,  2218,  2222,  2226,  2226,  2238,  2239,  2243,
    2243,  2251,  2252,  2255,  2256,  2257,  2258,  2259,  2260,  2261,
    2264,  2269,  2269,  2277,  2277,  2287,  2288,  2291,  2291,  2299,
    2300,  2303,  2304,  2305,  2306,  2309,  2309,  2317,  2322,  2327
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
#line 5051 "dhcp6_parser.cc" // lalr1.cc:1218
#line 2332 "dhcp6_parser.yy" // lalr1.cc:1219


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
