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
      case 182: // value
      case 186: // map_value
      case 236: // db_type
      case 320: // hr_mode
      case 456: // duid_type
      case 489: // ncr_protocol_value
      case 497: // replace_client_name_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 165: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 164: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 163: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 162: // "constant string"
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
      case 182: // value
      case 186: // map_value
      case 236: // db_type
      case 320: // hr_mode
      case 456: // duid_type
      case 489: // ncr_protocol_value
      case 497: // replace_client_name_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 165: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 164: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 163: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 162: // "constant string"
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
      case 182: // value
      case 186: // map_value
      case 236: // db_type
      case 320: // hr_mode
      case 456: // duid_type
      case 489: // ncr_protocol_value
      case 497: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 165: // "boolean"
        value.move< bool > (that.value);
        break;

      case 164: // "floating point"
        value.move< double > (that.value);
        break;

      case 163: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 162: // "constant string"
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
            case 162: // "constant string"

#line 238 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< std::string > (); }
#line 398 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 163: // "integer"

#line 238 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 405 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 164: // "floating point"

#line 238 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< double > (); }
#line 412 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 165: // "boolean"

#line 238 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< bool > (); }
#line 419 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 182: // value

#line 238 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 426 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 186: // map_value

#line 238 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 433 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 236: // db_type

#line 238 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 440 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 320: // hr_mode

#line 238 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 447 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 456: // duid_type

#line 238 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 454 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 489: // ncr_protocol_value

#line 238 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 461 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 497: // replace_client_name_value

#line 238 "dhcp6_parser.yy" // lalr1.cc:672
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
      case 182: // value
      case 186: // map_value
      case 236: // db_type
      case 320: // hr_mode
      case 456: // duid_type
      case 489: // ncr_protocol_value
      case 497: // replace_client_name_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 165: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 164: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 163: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 162: // "constant string"
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
#line 247 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 727 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 4:
#line 248 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.CONFIG; }
#line 733 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 6:
#line 249 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP6; }
#line 739 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 8:
#line 250 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 745 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 10:
#line 251 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.SUBNET6; }
#line 751 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 12:
#line 252 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.POOLS; }
#line 757 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 14:
#line 253 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 763 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 16:
#line 254 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 769 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 18:
#line 255 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP6; }
#line 775 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 20:
#line 256 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 781 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 22:
#line 257 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 787 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 24:
#line 258 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 793 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 26:
#line 259 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 799 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 28:
#line 260 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.LOGGING; }
#line 805 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 30:
#line 268 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 811 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 31:
#line 269 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 817 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 32:
#line 270 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 823 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 33:
#line 271 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 829 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 34:
#line 272 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 835 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 35:
#line 273 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 841 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 36:
#line 274 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 847 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 37:
#line 277 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 856 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 38:
#line 282 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 867 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 39:
#line 287 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 877 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 40:
#line 293 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 883 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 43:
#line 300 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 892 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 44:
#line 304 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 902 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 45:
#line 311 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 911 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 46:
#line 314 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // list parsing complete. Put any sanity checking here
}
#line 919 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 49:
#line 322 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 928 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 50:
#line 326 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 937 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 51:
#line 333 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // List parsing about to start
}
#line 945 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 52:
#line 335 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 954 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 55:
#line 344 "dhcp6_parser.yy" // lalr1.cc:907
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 963 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 56:
#line 348 "dhcp6_parser.yy" // lalr1.cc:907
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 972 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 57:
#line 359 "dhcp6_parser.yy" // lalr1.cc:907
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 983 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 58:
#line 369 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 994 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 59:
#line 374 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1007 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 68:
#line 397 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 1020 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 69:
#line 404 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1030 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 70:
#line 412 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1040 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 71:
#line 416 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No global parameter is required
    // parsing completed
}
#line 1049 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 100:
#line 455 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1058 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 101:
#line 460 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1067 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 102:
#line 465 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1076 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 103:
#line 470 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1085 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 104:
#line 475 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1094 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 105:
#line 480 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1105 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 106:
#line 485 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1115 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 107:
#line 491 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1125 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 108:
#line 495 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1134 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 116:
#line 511 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1145 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 117:
#line 516 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1154 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 118:
#line 521 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1163 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 119:
#line 527 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1174 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 120:
#line 532 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1185 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 121:
#line 539 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1196 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 122:
#line 544 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1207 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 123:
#line 551 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1218 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 124:
#line 556 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1227 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 129:
#line 569 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1237 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 130:
#line 573 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1247 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 152:
#line 604 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1255 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 153:
#line 606 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1264 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 154:
#line 611 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1270 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 155:
#line 612 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1276 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 156:
#line 613 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1282 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 157:
#line 614 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1288 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 158:
#line 617 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1296 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 159:
#line 619 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1306 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 160:
#line 625 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1314 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 161:
#line 627 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1324 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 162:
#line 633 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1332 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 163:
#line 635 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1342 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 164:
#line 641 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1351 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 165:
#line 646 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1359 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 166:
#line 648 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1369 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 167:
#line 654 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1378 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 168:
#line 659 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1387 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 169:
#line 664 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1396 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 170:
#line 669 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1405 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 171:
#line 674 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1414 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 172:
#line 679 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1423 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 173:
#line 684 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1432 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 174:
#line 689 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1441 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 175:
#line 694 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1449 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 176:
#line 696 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1459 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 177:
#line 702 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1468 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 178:
#line 707 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1476 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 179:
#line 709 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1486 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 180:
#line 715 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1495 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 181:
#line 720 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1506 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 182:
#line 725 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1515 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 187:
#line 738 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1524 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 188:
#line 743 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1533 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 189:
#line 748 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1544 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 190:
#line 753 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1553 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 196:
#line 767 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1562 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 197:
#line 772 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1571 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 198:
#line 779 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1582 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 199:
#line 784 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1591 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 200:
#line 789 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1602 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 201:
#line 794 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1611 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 206:
#line 807 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1621 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 207:
#line 811 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1631 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 208:
#line 817 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1641 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 209:
#line 821 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1651 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 215:
#line 836 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1659 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 216:
#line 838 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1669 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 217:
#line 844 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1677 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 218:
#line 846 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1686 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 219:
#line 852 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1697 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 220:
#line 857 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1707 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 229:
#line 875 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1716 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 230:
#line 880 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1725 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 231:
#line 885 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1734 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 232:
#line 890 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1743 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 233:
#line 895 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1752 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 234:
#line 900 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1761 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 235:
#line 908 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1772 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 236:
#line 913 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1781 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 241:
#line 933 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1791 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 242:
#line 937 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 1817 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 243:
#line 959 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1827 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 244:
#line 963 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1837 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 267:
#line 997 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1845 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 268:
#line 999 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1855 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 269:
#line 1005 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1863 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 270:
#line 1007 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1873 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 271:
#line 1013 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1881 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 272:
#line 1015 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1891 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 273:
#line 1021 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1899 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 274:
#line 1023 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1909 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 275:
#line 1029 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1920 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 276:
#line 1034 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1929 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 277:
#line 1039 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 1937 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 278:
#line 1041 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1946 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 279:
#line 1046 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 1952 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 280:
#line 1047 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 1958 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 281:
#line 1048 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 1964 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 282:
#line 1051 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 1973 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 283:
#line 1056 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 1982 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 284:
#line 1064 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 1993 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 285:
#line 1069 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2002 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 290:
#line 1084 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2012 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 291:
#line 1088 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 2020 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 311:
#line 1119 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2031 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 312:
#line 1124 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2040 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 313:
#line 1132 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2049 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 314:
#line 1135 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // parsing completed
}
#line 2057 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 319:
#line 1151 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2067 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 320:
#line 1155 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2079 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 321:
#line 1166 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2089 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 322:
#line 1170 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2101 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 338:
#line 1202 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2110 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 340:
#line 1209 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2118 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 341:
#line 1211 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2128 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 342:
#line 1217 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2136 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 343:
#line 1219 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2146 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 344:
#line 1225 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2154 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 345:
#line 1227 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2164 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 347:
#line 1235 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2172 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 348:
#line 1237 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2182 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 349:
#line 1243 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2191 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 350:
#line 1252 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2202 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 351:
#line 1257 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2211 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 356:
#line 1276 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2221 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 357:
#line 1280 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2230 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 358:
#line 1288 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2240 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 359:
#line 1292 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2249 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 374:
#line 1325 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2257 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 375:
#line 1327 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2267 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 378:
#line 1337 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2276 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 379:
#line 1342 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2285 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 380:
#line 1350 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2296 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 381:
#line 1355 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2305 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 386:
#line 1370 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2315 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 387:
#line 1374 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2325 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 388:
#line 1380 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2335 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 389:
#line 1384 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2344 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 399:
#line 1402 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2352 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 400:
#line 1404 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2362 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 401:
#line 1410 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2370 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 402:
#line 1412 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 2397 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 403:
#line 1435 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2405 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 404:
#line 1437 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 2434 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 405:
#line 1465 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2445 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 406:
#line 1470 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2454 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 411:
#line 1485 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2464 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 412:
#line 1489 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2476 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 413:
#line 1497 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2486 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 414:
#line 1501 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2498 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 428:
#line 1526 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2506 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 429:
#line 1528 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2516 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 430:
#line 1534 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2525 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 431:
#line 1539 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2533 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 432:
#line 1541 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2543 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 433:
#line 1547 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2552 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 434:
#line 1552 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2561 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 435:
#line 1560 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2572 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 436:
#line 1565 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2581 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 441:
#line 1578 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2591 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 442:
#line 1582 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2600 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 443:
#line 1587 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2610 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 444:
#line 1591 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2619 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 460:
#line 1618 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2630 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 461:
#line 1623 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2639 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 462:
#line 1628 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2650 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 463:
#line 1633 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2659 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 464:
#line 1638 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2667 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 465:
#line 1640 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2677 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 466:
#line 1646 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2685 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 467:
#line 1648 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2695 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 468:
#line 1654 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2703 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 469:
#line 1656 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2713 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 470:
#line 1662 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2721 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 471:
#line 1664 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2731 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 472:
#line 1670 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2742 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 473:
#line 1675 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2751 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 474:
#line 1683 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2762 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 475:
#line 1688 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2771 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 478:
#line 1697 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2779 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 479:
#line 1699 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2789 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 480:
#line 1708 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2800 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 481:
#line 1713 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2809 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 484:
#line 1722 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2819 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 485:
#line 1726 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2829 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 498:
#line 1751 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2837 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 499:
#line 1753 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2847 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 500:
#line 1759 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2856 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 501:
#line 1767 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2867 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 502:
#line 1772 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2878 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 514:
#line 1794 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2886 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 515:
#line 1796 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2895 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 516:
#line 1801 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2901 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 517:
#line 1802 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2907 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 518:
#line 1803 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2913 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 519:
#line 1806 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2922 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 520:
#line 1811 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2930 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 521:
#line 1813 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 2940 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 522:
#line 1819 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 2949 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 523:
#line 1824 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 2958 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 524:
#line 1831 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 2967 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 525:
#line 1838 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 2978 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 526:
#line 1843 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2987 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 534:
#line 1859 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2995 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 535:
#line 1861 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3005 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 536:
#line 1867 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3013 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 537:
#line 1869 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3023 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 538:
#line 1877 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3034 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 539:
#line 1882 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3045 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 540:
#line 1889 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3055 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 541:
#line 1893 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3065 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 561:
#line 1922 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3074 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 562:
#line 1927 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3082 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 563:
#line 1929 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3092 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 564:
#line 1935 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3100 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 565:
#line 1937 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3110 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 566:
#line 1943 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3119 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 567:
#line 1948 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3127 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 568:
#line 1950 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3137 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 569:
#line 1956 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3146 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 570:
#line 1961 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3155 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 571:
#line 1966 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3163 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 572:
#line 1968 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3172 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 573:
#line 1974 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3178 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 574:
#line 1975 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3184 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 575:
#line 1978 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3192 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 576:
#line 1980 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3202 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 577:
#line 1986 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-include-fqdn", b);
}
#line 3211 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 578:
#line 1991 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3220 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 579:
#line 1996 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3229 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 580:
#line 2001 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3237 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 581:
#line 2003 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3246 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 582:
#line 2009 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3254 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 583:
#line 2012 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3262 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 584:
#line 2015 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3270 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 585:
#line 2018 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3278 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 586:
#line 2021 "dhcp6_parser.yy" // lalr1.cc:907
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3287 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 587:
#line 2027 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3295 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 588:
#line 2029 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3305 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 589:
#line 2037 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3313 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 590:
#line 2039 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3322 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 591:
#line 2044 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3330 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 592:
#line 2046 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3339 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 593:
#line 2051 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3347 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 594:
#line 2053 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3356 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 595:
#line 2064 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3367 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 596:
#line 2069 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3376 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 597:
#line 2074 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3386 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 598:
#line 2078 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // parsing completed
}
#line 3394 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 602:
#line 2094 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3405 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 603:
#line 2099 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3414 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 606:
#line 2111 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3424 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 607:
#line 2115 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3432 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 617:
#line 2132 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3441 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 618:
#line 2137 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3449 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 619:
#line 2139 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3459 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 620:
#line 2145 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3470 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 621:
#line 2150 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3479 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 624:
#line 2159 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3489 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 625:
#line 2163 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3497 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 632:
#line 2177 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3505 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 633:
#line 2179 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3515 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 634:
#line 2185 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3524 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 635:
#line 2190 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3533 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 636:
#line 2195 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3542 "dhcp6_parser.cc" // lalr1.cc:907
    break;


#line 3546 "dhcp6_parser.cc" // lalr1.cc:907
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


  const short Dhcp6Parser::yypact_ninf_ = -786;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     444,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,    47,    41,    58,   115,   125,
     126,   136,   137,   153,   171,   175,   217,   219,   225,   250,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,    41,    -8,
      17,    63,    26,   221,    67,   427,   429,   108,    65,   121,
     -42,   456,   134,  -786,   252,   261,   269,   272,   278,  -786,
    -786,  -786,  -786,  -786,   312,  -786,    33,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,   317,   324,   327,
     329,   339,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,   340,  -786,  -786,  -786,    68,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,   341,  -786,    92,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
     344,   347,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,   139,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,   142,  -786,  -786,  -786,  -786,  -786,
     348,  -786,   349,   350,  -786,  -786,  -786,  -786,  -786,  -786,
     148,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,   288,   306,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,   307,  -786,
    -786,   353,  -786,  -786,  -786,   354,  -786,  -786,   351,   359,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,   360,   361,  -786,  -786,  -786,  -786,   355,
     366,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,   158,  -786,  -786,  -786,   367,  -786,  -786,
     369,  -786,   371,   373,  -786,  -786,   374,   376,   378,  -786,
    -786,  -786,  -786,  -786,   172,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,   173,  -786,  -786,  -786,    41,    41,  -786,   165,   381,
     384,   386,   388,   393,  -786,    17,  -786,   394,   395,   397,
     399,   226,   243,   245,   253,   257,   403,   405,   406,   407,
     409,   411,   414,   417,   423,   425,   428,   430,   431,   270,
     432,   433,    63,  -786,   435,   275,    26,  -786,   437,   438,
     439,   440,   441,   283,   282,   446,   449,   452,   453,   454,
     221,  -786,   455,    67,  -786,   459,   303,   461,   308,   310,
     427,  -786,   464,   465,   466,   472,   473,   474,   476,  -786,
     429,  -786,   477,   478,   320,   490,   491,   492,   332,  -786,
      65,   494,   334,   335,  -786,   121,   500,   501,   -10,  -786,
     343,   507,   508,   358,   518,   362,   363,   519,   520,   365,
     368,   372,   527,   528,   456,  -786,   530,   134,  -786,  -786,
    -786,   532,   531,   533,    41,    41,    41,  -786,   534,   535,
     536,   539,  -786,  -786,  -786,  -786,  -786,   540,   541,   544,
     543,   377,   546,   547,   548,   550,   551,   552,   553,   554,
    -786,   555,   556,  -786,   559,  -786,  -786,   563,   564,   396,
     408,   424,  -786,  -786,   127,   559,   426,   580,   583,  -786,
     445,  -786,   447,  -786,   448,  -786,  -786,  -786,   559,   559,
     559,   450,   451,   457,   458,  -786,   460,   462,  -786,   463,
     467,   468,  -786,  -786,   469,  -786,  -786,  -786,   470,    41,
    -786,  -786,   471,   475,  -786,   479,  -786,  -786,   -33,   480,
    -786,  -786,  -786,   -41,   481,  -786,   582,  -786,    41,    63,
     134,  -786,  -786,  -786,    26,   185,   185,   599,   601,   607,
     608,  -786,  -786,  -786,   609,   -37,    41,   147,   610,   614,
     145,   131,    -3,   456,  -786,  -786,   616,   619,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,   620,   -51,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,   621,  -786,   193,   220,   227,  -786,  -786,  -786,  -786,
     630,   631,   632,   634,   635,  -786,   636,   638,  -786,   640,
     641,   642,   643,  -786,   244,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,   246,  -786,   644,   645,  -786,  -786,
     646,   648,  -786,  -786,   647,   651,  -786,  -786,   649,   653,
    -786,  -786,   652,   654,  -786,  -786,  -786,   183,  -786,  -786,
    -786,   655,  -786,  -786,  -786,   292,  -786,  -786,  -786,  -786,
     311,  -786,  -786,   656,   657,  -786,   659,   660,   661,   662,
     663,   664,   247,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,   665,   666,   667,  -786,  -786,  -786,  -786,   248,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,   260,  -786,  -786,  -786,   262,   487,  -786,   668,   669,
    -786,  -786,   670,   672,  -786,  -786,   671,   675,  -786,  -786,
    -786,   673,  -786,  -786,   319,  -786,  -786,  -786,  -786,   676,
     678,   679,   680,   496,   514,   510,   521,   522,   683,   525,
     526,   686,   529,   537,   538,   542,   185,  -786,  -786,   185,
    -786,   599,   221,  -786,   601,    65,  -786,   607,   121,  -786,
     608,   385,  -786,   609,   -37,  -786,  -786,   147,  -786,    35,
     610,  -786,   -42,  -786,   614,   545,   549,   557,   558,   560,
     561,   145,  -786,   687,   689,   566,   567,   569,   131,  -786,
     690,   691,    -3,  -786,  -786,  -786,   692,   693,    67,  -786,
     616,   427,  -786,   619,   429,  -786,   620,   695,  -786,   255,
     621,  -786,    37,   565,   572,   579,  -786,  -786,  -786,  -786,
    -786,   581,  -786,  -786,   587,  -786,  -786,  -786,  -786,  -786,
     264,  -786,   271,  -786,   694,  -786,   696,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,   274,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,   697,  -786,  -786,  -786,  -786,  -786,   698,   704,  -786,
    -786,  -786,  -786,  -786,   289,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,   234,   588,  -786,  -786,  -786,  -786,   590,
     591,  -786,  -786,   593,   291,  -786,   302,  -786,   701,  -786,
     594,  -786,   706,  -786,  -786,  -786,  -786,  -786,   304,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,   385,  -786,
     707,   595,  -786,    35,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,   709,   596,   710,
     255,  -786,  -786,   604,  -786,  -786,   711,  -786,   611,  -786,
    -786,   708,  -786,  -786,   323,  -786,   -80,   708,  -786,  -786,
     713,   714,   715,   305,  -786,  -786,  -786,  -786,  -786,  -786,
     740,   598,   613,   615,   -80,  -786,   623,  -786,  -786,  -786,
    -786,  -786
  };

  const unsigned short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   107,     9,   243,    11,
     388,    13,   413,    15,   443,    17,   313,    19,   321,    21,
     358,    23,   208,    25,   540,    27,   597,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   445,     0,   323,   360,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     595,   589,   591,   593,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   105,   119,   121,   123,     0,     0,     0,
       0,     0,   235,   311,   350,   401,   403,   284,   181,   198,
     189,   480,   200,   219,   501,     0,   525,   538,    99,     0,
      72,    74,    75,    76,    77,    78,    81,    82,    83,    84,
      85,    87,    86,    91,    92,    79,    80,    89,    90,    97,
      98,    88,    93,    94,    95,    96,   116,     0,   115,     0,
     109,   111,   112,   113,   114,   380,   405,   267,   269,   271,
       0,     0,   277,   275,   273,   435,   474,   266,   247,   248,
     249,   250,     0,   245,   254,   255,   256,   259,   260,   262,
     257,   258,   251,   252,   264,   265,   253,   261,   263,   399,
     398,   394,   395,   393,     0,   390,   392,   396,   397,   428,
       0,   431,     0,     0,   427,   421,   422,   420,   425,   426,
       0,   415,   417,   418,   423,   424,   419,   472,   460,   462,
     464,   466,   468,   470,   459,   456,   457,   458,     0,   446,
     447,   451,   452,   449,   453,   454,   455,   450,     0,   340,
     165,     0,   344,   342,   347,     0,   336,   337,     0,   324,
     325,   327,   339,   328,   329,   330,   346,   331,   332,   333,
     334,   335,   374,     0,     0,   372,   373,   376,   377,     0,
     361,   362,   364,   365,   366,   367,   368,   369,   370,   371,
     215,   217,   212,     0,   210,   213,   214,     0,   562,   564,
       0,   567,     0,     0,   571,   575,     0,     0,     0,   580,
     587,   560,   558,   559,     0,   542,   544,   545,   546,   547,
     548,   549,   550,   551,   552,   553,   554,   555,   556,   557,
     602,     0,   599,   601,    46,     0,     0,    39,     0,     0,
       0,     0,     0,     0,    57,     0,    59,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    71,     0,     0,     0,   108,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   244,     0,     0,   389,     0,     0,     0,     0,     0,
       0,   414,     0,     0,     0,     0,     0,     0,     0,   444,
       0,   314,     0,     0,     0,     0,     0,     0,     0,   322,
       0,     0,     0,     0,   359,     0,     0,     0,     0,   209,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   541,     0,     0,   598,    50,
      43,     0,     0,     0,     0,     0,     0,    61,     0,     0,
       0,     0,   100,   101,   102,   103,   104,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     524,     0,     0,    73,     0,   118,   110,     0,     0,     0,
       0,     0,   282,   283,     0,     0,     0,     0,     0,   246,
       0,   391,     0,   430,     0,   433,   434,   416,     0,     0,
       0,     0,     0,     0,     0,   448,     0,     0,   338,     0,
       0,     0,   349,   326,     0,   378,   379,   363,     0,     0,
     211,   561,     0,     0,   566,     0,   569,   570,     0,     0,
     577,   578,   579,     0,     0,   543,     0,   600,     0,     0,
       0,   590,   592,   594,     0,     0,     0,   125,   237,   315,
     352,    40,   402,   404,   286,     0,    47,     0,     0,   202,
       0,     0,     0,     0,    51,   117,   382,   407,   268,   270,
     272,   279,   280,   281,   278,   276,   274,   437,     0,   400,
     429,   432,   473,   461,   463,   465,   467,   469,   471,   341,
     166,   345,   343,   348,   375,   216,   218,   563,   565,   568,
     573,   574,   572,   576,   582,   583,   584,   585,   586,   581,
     588,     0,    44,     0,     0,     0,   152,   158,   160,   162,
       0,     0,     0,     0,     0,   175,     0,     0,   178,     0,
       0,     0,     0,   151,     0,   131,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   145,   146,   147,   148,
     143,   144,   149,   150,     0,   129,     0,   126,   127,   241,
       0,   238,   239,   319,     0,   316,   317,   356,     0,   353,
     354,   290,     0,   287,   288,   187,   188,     0,   183,   185,
     186,     0,   196,   197,   193,     0,   191,   194,   195,   484,
       0,   482,   206,     0,   203,   204,     0,     0,     0,     0,
       0,     0,     0,   221,   223,   224,   225,   226,   227,   228,
     514,   520,     0,     0,     0,   513,   510,   511,   512,     0,
     503,   505,   508,   506,   507,   509,   534,   536,   533,   531,
     532,     0,   527,   529,   530,     0,    53,   386,     0,   383,
     384,   411,     0,   408,   409,   441,     0,   438,   439,   478,
     477,     0,   476,   606,     0,   604,    69,   596,   106,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   120,   122,     0,
     124,     0,     0,   236,     0,   323,   312,     0,   360,   351,
       0,     0,   285,     0,     0,   182,   199,     0,   190,   486,
       0,   481,     0,   201,     0,     0,     0,     0,     0,     0,
       0,     0,   220,     0,     0,     0,     0,     0,     0,   502,
       0,     0,     0,   526,   539,    55,     0,    54,     0,   381,
       0,     0,   406,     0,   445,   436,     0,     0,   475,     0,
       0,   603,     0,     0,     0,     0,   164,   167,   168,   169,
     170,     0,   177,   171,     0,   172,   173,   174,   180,   132,
       0,   128,     0,   240,     0,   318,     0,   355,   310,   305,
     307,   298,   299,   294,   295,   296,   297,   303,   304,   302,
     306,     0,   292,   300,   308,   309,   301,   289,   184,   192,
     498,     0,   496,   497,   493,   494,   495,     0,   487,   488,
     490,   491,   492,   483,     0,   205,   229,   230,   231,   232,
     233,   234,   222,     0,     0,   519,   522,   523,   504,     0,
       0,   528,    52,     0,     0,   385,     0,   410,     0,   440,
       0,   620,     0,   618,   616,   610,   614,   615,     0,   608,
     612,   613,   611,   605,   154,   155,   156,   157,   153,   159,
     161,   163,   176,   179,   130,   242,   320,   357,     0,   291,
       0,     0,   485,     0,   207,   516,   517,   518,   515,   521,
     535,   537,    56,   387,   412,   442,   479,     0,     0,     0,
       0,   607,   293,     0,   500,   489,     0,   617,     0,   609,
     499,     0,   619,   624,     0,   622,     0,     0,   621,   632,
       0,     0,     0,     0,   626,   628,   629,   630,   631,   623,
       0,     0,     0,     0,     0,   625,     0,   634,   635,   636,
     627,   633
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,     6,  -786,    89,  -786,
    -786,  -786,  -786,  -786,  -786,   204,  -786,  -374,  -786,  -786,
    -786,   -70,  -786,  -786,  -786,   352,  -786,  -786,  -786,  -786,
     223,   410,   -66,   -56,   -55,   -54,  -786,  -786,  -786,  -786,
    -786,   229,   401,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,    -4,  -786,  -541,    -5,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,   -34,  -786,
    -559,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,   -14,  -554,  -786,
    -786,  -786,  -786,   -16,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,   -18,  -786,  -786,  -786,   -19,   370,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,   -22,  -786,  -786,  -786,  -786,
    -786,  -786,  -785,  -786,  -786,  -786,     7,  -786,  -786,  -786,
      10,   418,  -786,  -786,  -781,  -786,  -778,  -786,   -32,  -786,
     -21,  -786,  -777,  -786,  -786,  -786,  -776,  -786,  -786,  -786,
    -786,     4,  -786,  -786,  -158,   734,  -786,  -786,  -786,  -786,
    -786,    15,  -786,  -786,  -786,    19,  -786,   398,  -786,   -65,
    -786,  -786,  -786,  -786,  -786,   -58,  -786,  -786,  -786,  -786,
    -786,    12,  -786,  -786,  -786,    16,  -786,  -786,  -786,    21,
    -786,   400,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,   -17,  -786,  -786,  -786,   -11,   436,  -786,
    -786,   -44,  -786,    -6,  -786,  -786,  -786,  -786,  -786,   -15,
    -786,  -786,  -786,    -7,   442,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,   -13,  -786,  -786,  -786,
     -20,  -786,   420,   249,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -775,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,    29,  -786,  -786,  -786,  -142,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,     8,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
       9,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,   267,
     402,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,  -786,
    -786,  -786,  -786,  -786,   294,   404,  -786,  -786,  -786,    -2,
    -786,  -786,  -145,  -786,  -786,  -786,  -786,  -786,  -786,  -160,
    -786,  -786,  -175,  -786,  -786,  -786,  -786,  -786
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     562,    87,    88,    41,    68,    84,    85,   575,   746,   836,
     837,   643,    43,    70,    96,    97,    98,   339,    45,    71,
     129,   130,   131,   132,   133,   134,   135,   136,   347,    47,
      72,   159,   160,   161,   374,   162,   137,   348,   138,   349,
     139,   350,   666,   667,   668,   789,   644,   645,   646,   769,
     958,   647,   770,   648,   771,   649,   772,   650,   651,   413,
     652,   653,   654,   655,   656,   657,   658,   659,   660,   778,
     661,   662,   781,   663,   140,   362,   687,   688,   689,   690,
     141,   364,   695,   696,   697,   698,   142,   363,   143,   366,
     703,   704,   705,   812,    63,    80,   293,   294,   295,   426,
     296,   427,   144,   367,   712,   713,   714,   715,   716,   717,
     718,   719,   145,   356,   670,   671,   672,   792,    49,    73,
     182,   183,   184,   380,   185,   381,   186,   382,   187,   387,
     188,   386,   189,   385,   584,   190,   191,   146,   361,   682,
     683,   684,   801,   891,   892,   147,   357,    57,    77,   674,
     675,   676,   795,    59,    78,   258,   259,   260,   261,   262,
     263,   264,   412,   265,   416,   266,   415,   267,   268,   417,
     269,   148,   358,   678,   679,   680,   798,    61,    79,   279,
     280,   281,   282,   283,   421,   284,   285,   286,   287,   193,
     378,   748,   749,   750,   838,    51,    74,   204,   205,   206,
     392,   149,   359,   150,   360,   196,   379,   752,   753,   754,
     841,    53,    75,   220,   221,   222,   395,   223,   224,   397,
     225,   226,   197,   388,   756,   757,   758,   844,    55,    76,
     238,   239,   240,   241,   403,   242,   404,   243,   405,   244,
     406,   245,   407,   246,   408,   247,   402,   198,   389,   761,
     762,   847,   151,   365,   700,   701,   809,   907,   908,   909,
     910,   911,   970,   912,   152,   368,   729,   730,   731,   823,
     978,   732,   733,   824,   734,   735,   153,   154,   370,   741,
     742,   743,   830,   744,   831,   155,   371,    65,    81,   314,
     315,   316,   317,   431,   318,   432,   319,   320,   434,   321,
     322,   323,   437,   612,   324,   438,   325,   326,   327,   328,
     442,   619,   329,   443,    99,   341,   100,   342,   101,   343,
     102,   340,    67,    82,   331,   332,   333,   446,   764,   765,
     849,   948,   949,   950,   951,   989,   952,   987,  1004,  1005,
    1006,  1013,  1014,  1015,  1020,  1016,  1017,  1018
  };

  const unsigned short
  Dhcp6Parser::yytable_[] =
  {
      95,   128,   158,   177,   200,   214,   234,   178,   256,   275,
     292,   311,   726,   694,   277,   664,   884,   179,   180,   181,
     885,   278,    38,   886,   889,   890,   896,    89,   163,   194,
     207,   218,   236,   228,   270,   288,   345,   312,   156,   157,
     759,   346,   201,   215,   257,   276,    31,    30,    32,   685,
      33,   290,   291,   202,   216,   954,   955,   956,   957,  1009,
     115,   116,  1010,  1011,  1012,    42,   164,   195,   208,   219,
     237,   372,   271,   289,   103,   313,   373,   104,   105,   106,
     114,   250,   249,   290,   291,   192,   203,   217,   235,   115,
     116,   614,   615,   616,   617,   376,   610,   611,   115,   116,
     377,   107,   108,   109,   110,   111,   112,   113,   114,   736,
     737,   250,   114,   251,   252,   900,   901,   253,   254,   255,
      94,   585,    44,   199,   618,   686,   115,   116,   115,   116,
     115,   116,    46,    48,   592,   593,   594,   117,   118,   119,
     120,   121,   390,    50,    52,   393,   173,   391,   720,   174,
     394,   400,   113,    90,    86,   122,   401,   631,   123,    94,
      54,   428,    91,    92,    93,   124,   429,   250,   272,   251,
     252,   273,   274,   125,   126,   444,   447,   127,    56,    94,
     445,   448,    58,   884,   115,   116,   804,   885,    94,   805,
     886,   889,   890,   896,   115,   116,   372,    94,   581,   582,
     583,   766,   626,    34,    35,    36,    37,   627,   628,   629,
     630,   631,   632,   633,   634,   635,   636,   637,   638,   639,
     640,   641,   642,   447,    60,    94,    62,    94,   767,    94,
     376,   250,    64,   685,   692,   768,   693,   721,   722,   723,
     724,   706,   707,   708,   709,   710,   711,   786,   870,   786,
     821,   828,   787,   694,   788,   822,   829,    66,   334,   107,
     108,   109,   110,   832,   335,   444,   114,   786,   833,   726,
     834,   330,   964,   336,   390,    95,   165,   968,   166,   965,
     337,   338,   969,    94,   115,   116,   167,   168,   169,   170,
     171,   172,   428,    94,   393,   807,   409,   974,   808,   983,
     173,   250,   128,   174,   175,   400,   158,   990,  1024,   410,
     984,   176,   991,  1025,   810,   411,   344,   811,   115,   116,
     177,   351,   850,   200,   178,   851,  1007,   451,   352,  1008,
     214,   353,   163,   354,   179,   180,   181,   975,   976,   977,
     234,   449,   450,   355,   369,   375,   194,    94,   383,   207,
     256,   384,   396,   398,   399,   275,   218,   414,   418,   419,
     277,   201,   420,   424,   422,   423,   236,   278,   215,   425,
     164,   430,   202,   433,   311,   435,   270,   436,   439,   216,
     440,   288,   441,    94,   195,   452,   257,   208,   453,   462,
     454,   276,   455,   941,   219,   942,   943,   456,   458,   459,
     312,   460,   192,   461,   237,   203,   463,   467,   464,   468,
     469,   470,   217,   471,   271,   472,   465,    94,   473,   289,
     466,   474,   235,   107,   108,   109,   110,   475,   112,   476,
     114,   250,   477,   480,   478,   479,   481,   482,   313,   484,
     485,   487,   488,   489,   490,   491,   492,   493,   115,   116,
     494,   168,   169,   495,   171,   172,   496,   497,   498,   500,
     551,   552,   553,   502,   173,   504,   503,   174,   508,   509,
     510,   505,   114,   506,   114,   176,   511,   512,   513,   128,
     514,   516,   517,   518,   158,   209,   210,   211,   212,   213,
     115,   116,   115,   116,   519,   520,   521,   522,   524,   525,
     526,   725,   738,   311,   528,   529,   173,   227,   531,   174,
     163,   532,   533,   228,   229,   230,   231,   232,   233,   115,
     116,   534,   535,   538,   539,   536,   537,   727,   739,   312,
     540,   543,   544,   541,   546,   606,   548,   542,   549,   563,
     550,   554,   555,   556,   557,   558,   559,    94,   164,   560,
      32,   564,   565,   566,   622,   567,   568,   569,   578,   561,
     570,   571,   572,   573,   574,   728,   740,   313,   576,   577,
     579,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   587,   580,   621,   586,    94,
     588,    94,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,   665,   589,   669,   590,
     591,   613,   595,   596,   673,   677,   681,   699,    94,   597,
     598,   702,   599,   747,   600,   601,   751,   755,   763,   602,
     603,   604,   605,   607,   773,   774,   775,   608,   776,   777,
     779,   609,   780,   620,   782,   783,   784,   785,   791,   835,
     790,   794,   793,   796,   797,   799,   800,   803,   802,   856,
     814,   806,   813,   815,   816,   817,   818,   819,   820,   825,
     826,   827,   840,   858,   839,   843,   842,   845,   846,   857,
     852,   848,   853,   854,   855,   860,   859,   861,   862,   863,
     864,   923,   865,   924,   929,   930,   933,   457,   932,   940,
     866,   971,   966,   867,   967,   868,   972,   973,   916,   985,
     988,   993,   917,   996,   998,  1003,  1001,  1021,  1022,  1023,
     918,   919,   177,   920,   921,   256,   178,   959,   275,   925,
     926,   878,   927,   277,   960,   879,   179,   180,   181,   902,
     278,   961,   292,   962,  1026,   880,   881,   882,   194,   963,
     979,   270,   980,   981,   288,   982,   986,   894,   725,   997,
     994,   257,   738,  1027,   276,   905,  1000,   883,   200,   887,
     691,   214,   623,  1002,   234,   903,  1028,   486,  1029,   944,
     888,   869,   483,   625,   727,  1031,   195,   871,   739,   271,
     898,   899,   289,   914,   207,   895,   915,   218,   530,   922,
     236,   873,   872,   906,   192,   946,   201,   897,   499,   215,
     992,   248,   875,   893,   874,   945,   877,   202,   523,   876,
     216,   904,   728,   935,   938,   527,   740,   934,   937,   501,
     515,   995,   208,   939,   936,   219,   928,   760,   237,   913,
     745,   931,   507,   947,   624,   999,   545,  1019,   953,  1030,
     203,   547,     0,   217,     0,     0,   235,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   878,     0,
       0,     0,   879,   902,     0,     0,     0,     0,     0,     0,
       0,     0,   880,   881,   882,     0,     0,     0,     0,     0,
     944,     0,     0,     0,   894,     0,     0,     0,     0,   905,
       0,     0,     0,     0,   883,     0,   887,     0,     0,   903,
       0,     0,     0,     0,     0,     0,   946,   888,     0,     0,
       0,     0,     0,     0,     0,     0,   945,     0,     0,     0,
       0,     0,   895,     0,     0,     0,     0,   906,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     893,     0,     0,     0,   947,   904
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    76,    73,    78,    79,
      80,    81,   571,   567,    79,   556,   801,    73,    73,    73,
     801,    79,    16,   801,   801,   801,   801,    10,    72,    73,
      74,    75,    76,    84,    78,    79,     3,    81,    12,    13,
      91,     8,    74,    75,    78,    79,     5,     0,     7,    86,
       9,    93,    94,    74,    75,    18,    19,    20,    21,   139,
      63,    64,   142,   143,   144,     7,    72,    73,    74,    75,
      76,     3,    78,    79,    11,    81,     8,    14,    15,    16,
      45,    46,    17,    93,    94,    73,    74,    75,    76,    63,
      64,   132,   133,   134,   135,     3,   129,   130,    63,    64,
       8,    38,    39,    40,    41,    42,    43,    44,    45,   112,
     113,    46,    45,    48,    49,    80,    81,    52,    53,    54,
     162,   495,     7,    56,   165,   162,    63,    64,    63,    64,
      63,    64,     7,     7,   508,   509,   510,    74,    75,    76,
      77,    78,     3,     7,     7,     3,    79,     8,    17,    82,
       8,     3,    44,   136,   162,    92,     8,    26,    95,   162,
       7,     3,   145,   146,   147,   102,     8,    46,    47,    48,
      49,    50,    51,   110,   111,     3,     3,   114,     7,   162,
       8,     8,     7,   968,    63,    64,     3,   968,   162,     6,
     968,   968,   968,   968,    63,    64,     3,   162,    71,    72,
      73,     8,    17,   162,   163,   164,   165,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,     3,     7,   162,     7,   162,     8,   162,
       3,    46,     7,    86,    87,     8,    89,   106,   107,   108,
     109,    96,    97,    98,    99,   100,   101,     3,   789,     3,
       3,     3,     8,   807,     8,     8,     8,     7,     6,    38,
      39,    40,    41,     3,     3,     3,    45,     3,     8,   828,
       8,   137,     8,     4,     3,   345,    55,     3,    57,     8,
       8,     3,     8,   162,    63,    64,    65,    66,    67,    68,
      69,    70,     3,   162,     3,     3,     8,     8,     6,     8,
      79,    46,   372,    82,    83,     3,   376,     3,     3,     3,
       8,    90,     8,     8,     3,     8,     4,     6,    63,    64,
     390,     4,     3,   393,   390,     6,     3,   162,     4,     6,
     400,     4,   376,     4,   390,   390,   390,   103,   104,   105,
     410,   335,   336,     4,     4,     4,   390,   162,     4,   393,
     420,     4,     4,     4,     4,   425,   400,     4,     4,     8,
     425,   393,     3,     8,     4,     4,   410,   425,   400,     3,
     376,     4,   393,     4,   444,     4,   420,     4,     4,   400,
       4,   425,     4,   162,   390,     4,   420,   393,     4,   163,
       4,   425,     4,   138,   400,   140,   141,     4,     4,     4,
     444,     4,   390,     4,   410,   393,   163,     4,   163,     4,
       4,     4,   400,     4,   420,     4,   163,   162,     4,   425,
     163,     4,   410,    38,    39,    40,    41,     4,    43,     4,
      45,    46,     4,   163,     4,     4,     4,     4,   444,     4,
     165,     4,     4,     4,     4,     4,   163,   165,    63,    64,
       4,    66,    67,     4,    69,    70,     4,     4,     4,     4,
     454,   455,   456,     4,    79,     4,   163,    82,     4,     4,
       4,   163,    45,   163,    45,    90,     4,     4,     4,   549,
       4,     4,     4,   163,   554,    58,    59,    60,    61,    62,
      63,    64,    63,    64,     4,     4,     4,   165,     4,   165,
     165,   571,   572,   573,     4,     4,    79,    78,   165,    82,
     554,     4,     4,    84,    85,    86,    87,    88,    89,    63,
      64,   163,     4,     4,     4,   163,   163,   571,   572,   573,
     165,     4,     4,   165,     4,   529,     4,   165,     7,   162,
       7,     7,     7,     7,     5,     5,     5,   162,   554,     5,
       7,     5,     5,     5,   548,     5,     5,     5,   162,   470,
       7,     7,     7,     7,     5,   571,   572,   573,     5,     5,
     162,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,     5,   162,     5,   162,   162,
       7,   162,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,     7,   162,     7,   162,
     162,   131,   162,   162,     7,     7,     7,     7,   162,   162,
     162,     7,   162,     7,   162,   162,     7,     7,     7,   162,
     162,   162,   162,   162,     4,     4,     4,   162,     4,     4,
       4,   162,     4,   162,     4,     4,     4,     4,     3,   162,
       6,     3,     6,     6,     3,     6,     3,     3,     6,   163,
       3,     6,     6,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     3,   163,     6,     3,     6,     6,     3,   165,
       4,     8,     4,     4,     4,   163,   165,     4,   163,   163,
       4,     4,   163,     4,     4,     4,     3,   345,     6,     4,
     163,     4,     8,   165,     8,   163,     8,     3,   163,     8,
       4,     4,   163,     4,     4,     7,     5,     4,     4,     4,
     163,   163,   792,   163,   163,   795,   792,   162,   798,   163,
     163,   801,   163,   798,   162,   801,   792,   792,   792,   809,
     798,   162,   812,   162,     4,   801,   801,   801,   792,   162,
     162,   795,   162,   162,   798,   162,   162,   801,   828,   163,
     165,   795,   832,   165,   798,   809,   162,   801,   838,   801,
     566,   841,   549,   162,   844,   809,   163,   376,   163,   849,
     801,   786,   372,   554,   828,   162,   792,   791,   832,   795,
     804,   807,   798,   812,   838,   801,   814,   841,   428,   821,
     844,   794,   792,   809,   792,   849,   838,   803,   390,   841,
     968,    77,   797,   801,   795,   849,   800,   838,   420,   798,
     841,   809,   828,   840,   844,   425,   832,   838,   843,   393,
     410,   973,   838,   846,   841,   841,   828,   588,   844,   810,
     573,   832,   400,   849,   550,   990,   444,  1007,   850,  1024,
     838,   447,    -1,   841,    -1,    -1,   844,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   968,    -1,
      -1,    -1,   968,   973,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   968,   968,   968,    -1,    -1,    -1,    -1,    -1,
     990,    -1,    -1,    -1,   968,    -1,    -1,    -1,    -1,   973,
      -1,    -1,    -1,    -1,   968,    -1,   968,    -1,    -1,   973,
      -1,    -1,    -1,    -1,    -1,    -1,   990,   968,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   990,    -1,    -1,    -1,
      -1,    -1,   968,    -1,    -1,    -1,    -1,   973,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     968,    -1,    -1,    -1,   990,   973
  };

  const unsigned short
  Dhcp6Parser::yystos_[] =
  {
       0,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
       0,     5,     7,     9,   162,   163,   164,   165,   182,   183,
     184,   189,     7,   198,     7,   204,     7,   215,     7,   304,
       7,   381,     7,   397,     7,   414,     7,   333,     7,   339,
       7,   363,     7,   280,     7,   473,     7,   508,   190,   185,
     199,   205,   216,   305,   382,   398,   415,   334,   340,   364,
     281,   474,   509,   182,   191,   192,   162,   187,   188,    10,
     136,   145,   146,   147,   162,   197,   200,   201,   202,   500,
     502,   504,   506,    11,    14,    15,    16,    38,    39,    40,
      41,    42,    43,    44,    45,    63,    64,    74,    75,    76,
      77,    78,    92,    95,   102,   110,   111,   114,   197,   206,
     207,   208,   209,   210,   211,   212,   213,   222,   224,   226,
     260,   266,   272,   274,   288,   298,   323,   331,   357,   387,
     389,   438,   450,   462,   463,   471,    12,    13,   197,   217,
     218,   219,   221,   387,   389,    55,    57,    65,    66,    67,
      68,    69,    70,    79,    82,    83,    90,   197,   208,   209,
     210,   211,   306,   307,   308,   310,   312,   314,   316,   318,
     321,   322,   357,   375,   387,   389,   391,   408,   433,    56,
     197,   314,   316,   357,   383,   384,   385,   387,   389,    58,
      59,    60,    61,    62,   197,   314,   316,   357,   387,   389,
     399,   400,   401,   403,   404,   406,   407,    78,    84,    85,
      86,    87,    88,    89,   197,   357,   387,   389,   416,   417,
     418,   419,   421,   423,   425,   427,   429,   431,   331,    17,
      46,    48,    49,    52,    53,    54,   197,   244,   341,   342,
     343,   344,   345,   346,   347,   349,   351,   353,   354,   356,
     387,   389,    47,    50,    51,   197,   244,   345,   351,   365,
     366,   367,   368,   369,   371,   372,   373,   374,   387,   389,
      93,    94,   197,   282,   283,   284,   286,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   197,   387,   389,   475,   476,   477,   478,   480,   482,
     483,   485,   486,   487,   490,   492,   493,   494,   495,   498,
     137,   510,   511,   512,     6,     3,     4,     8,     3,   203,
     507,   501,   503,   505,     4,     3,     8,   214,   223,   225,
     227,     4,     4,     4,     4,     4,   299,   332,   358,   388,
     390,   324,   261,   273,   267,   439,   275,   289,   451,     4,
     464,   472,     3,     8,   220,     4,     3,     8,   376,   392,
     309,   311,   313,     4,     4,   319,   317,   315,   409,   434,
       3,     8,   386,     3,     8,   402,     4,   405,     4,     4,
       3,     8,   432,   420,   422,   424,   426,   428,   430,     8,
       3,     8,   348,   245,     4,   352,   350,   355,     4,     8,
       3,   370,     4,     4,     8,     3,   285,   287,     3,     8,
       4,   479,   481,     4,   484,     4,     4,   488,   491,     4,
       4,     4,   496,   499,     3,     8,   513,     3,     8,   182,
     182,   162,     4,     4,     4,     4,     4,   201,     4,     4,
       4,     4,   163,   163,   163,   163,   163,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     163,     4,     4,   207,     4,   165,   218,     4,     4,     4,
       4,     4,   163,   165,     4,     4,     4,     4,     4,   307,
       4,   384,     4,   163,     4,   163,   163,   400,     4,     4,
       4,     4,     4,     4,     4,   418,     4,     4,   163,     4,
       4,     4,   165,   343,     4,   165,   165,   367,     4,     4,
     283,   165,     4,     4,   163,     4,   163,   163,     4,     4,
     165,   165,   165,     4,     4,   476,     4,   511,     4,     7,
       7,   182,   182,   182,     7,     7,     7,     5,     5,     5,
       5,   184,   186,   162,     5,     5,     5,     5,     5,     5,
       7,     7,     7,     7,     5,   193,     5,     5,   162,   162,
     162,    71,    72,    73,   320,   193,   162,     5,     7,   162,
     162,   162,   193,   193,   193,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   182,   162,   162,   162,
     129,   130,   489,   131,   132,   133,   134,   135,   165,   497,
     162,     5,   182,   206,   510,   217,    17,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,   197,   232,   233,   234,   237,   239,   241,
     243,   244,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   256,   257,   259,   232,     7,   228,   229,   230,     7,
     300,   301,   302,     7,   335,   336,   337,     7,   359,   360,
     361,     7,   325,   326,   327,    86,   162,   262,   263,   264,
     265,   191,    87,    89,   264,   268,   269,   270,   271,     7,
     440,   441,     7,   276,   277,   278,    96,    97,    98,    99,
     100,   101,   290,   291,   292,   293,   294,   295,   296,   297,
      17,   106,   107,   108,   109,   197,   246,   387,   389,   452,
     453,   454,   457,   458,   460,   461,   112,   113,   197,   387,
     389,   465,   466,   467,   469,   475,   194,     7,   377,   378,
     379,     7,   393,   394,   395,     7,   410,   411,   412,    91,
     419,   435,   436,     7,   514,   515,     8,     8,     8,   235,
     238,   240,   242,     4,     4,     4,     4,     4,   255,     4,
       4,   258,     4,     4,     4,     4,     3,     8,     8,   231,
       6,     3,   303,     6,     3,   338,     6,     3,   362,     6,
       3,   328,     6,     3,     3,     6,     6,     3,     6,   442,
       3,     6,   279,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   455,   459,     4,     4,     4,     3,     8,
     468,   470,     3,     8,     8,   162,   195,   196,   380,     6,
       3,   396,     6,     3,   413,     6,     3,   437,     8,   516,
       3,     6,     4,     4,     4,     4,   163,   165,   163,   165,
     163,     4,   163,   163,     4,   163,   163,   165,   163,   233,
     232,   230,   306,   302,   341,   337,   365,   361,   197,   208,
     209,   210,   211,   244,   298,   310,   312,   314,   316,   318,
     322,   329,   330,   357,   387,   389,   433,   327,   263,   269,
      80,    81,   197,   244,   357,   387,   389,   443,   444,   445,
     446,   447,   449,   441,   282,   278,   163,   163,   163,   163,
     163,   163,   291,     4,     4,   163,   163,   163,   453,     4,
       4,   466,     6,     3,   383,   379,   399,   395,   416,   412,
       4,   138,   140,   141,   197,   244,   387,   389,   517,   518,
     519,   520,   522,   515,    18,    19,    20,    21,   236,   162,
     162,   162,   162,   162,     8,     8,     8,     8,     3,     8,
     448,     4,     8,     3,     8,   103,   104,   105,   456,   162,
     162,   162,   162,     8,     8,     8,   162,   523,     4,   521,
       3,     8,   330,     4,   165,   445,     4,   163,     4,   518,
     162,     5,   162,     7,   524,   525,   526,     3,     6,   139,
     142,   143,   144,   527,   528,   529,   531,   532,   533,   525,
     530,     4,     4,     4,     3,     8,     4,   165,   163,   163,
     528,   162
  };

  const unsigned short
  Dhcp6Parser::yyr1_[] =
  {
       0,   166,   168,   167,   169,   167,   170,   167,   171,   167,
     172,   167,   173,   167,   174,   167,   175,   167,   176,   167,
     177,   167,   178,   167,   179,   167,   180,   167,   181,   167,
     182,   182,   182,   182,   182,   182,   182,   183,   185,   184,
     186,   187,   187,   188,   188,   190,   189,   191,   191,   192,
     192,   194,   193,   195,   195,   196,   196,   197,   199,   198,
     200,   200,   201,   201,   201,   201,   201,   201,   203,   202,
     205,   204,   206,   206,   207,   207,   207,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   207,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   207,   207,   207,   207,
     208,   209,   210,   211,   212,   214,   213,   216,   215,   217,
     217,   218,   218,   218,   218,   218,   220,   219,   221,   223,
     222,   225,   224,   227,   226,   228,   228,   229,   229,   231,
     230,   232,   232,   233,   233,   233,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   233,   235,   234,   236,   236,   236,   236,   238,   237,
     240,   239,   242,   241,   243,   245,   244,   246,   247,   248,
     249,   250,   251,   252,   253,   255,   254,   256,   258,   257,
     259,   261,   260,   262,   262,   263,   263,   264,   265,   267,
     266,   268,   268,   269,   269,   269,   270,   271,   273,   272,
     275,   274,   276,   276,   277,   277,   279,   278,   281,   280,
     282,   282,   282,   283,   283,   285,   284,   287,   286,   289,
     288,   290,   290,   291,   291,   291,   291,   291,   291,   292,
     293,   294,   295,   296,   297,   299,   298,   300,   300,   301,
     301,   303,   302,   305,   304,   306,   306,   307,   307,   307,
     307,   307,   307,   307,   307,   307,   307,   307,   307,   307,
     307,   307,   307,   307,   307,   307,   307,   309,   308,   311,
     310,   313,   312,   315,   314,   317,   316,   319,   318,   320,
     320,   320,   321,   322,   324,   323,   325,   325,   326,   326,
     328,   327,   329,   329,   330,   330,   330,   330,   330,   330,
     330,   330,   330,   330,   330,   330,   330,   330,   330,   330,
     330,   332,   331,   334,   333,   335,   335,   336,   336,   338,
     337,   340,   339,   341,   341,   342,   342,   343,   343,   343,
     343,   343,   343,   343,   343,   343,   343,   344,   345,   346,
     348,   347,   350,   349,   352,   351,   353,   355,   354,   356,
     358,   357,   359,   359,   360,   360,   362,   361,   364,   363,
     365,   365,   366,   366,   367,   367,   367,   367,   367,   367,
     367,   367,   367,   368,   370,   369,   371,   372,   373,   374,
     376,   375,   377,   377,   378,   378,   380,   379,   382,   381,
     383,   383,   384,   384,   384,   384,   384,   384,   384,   386,
     385,   388,   387,   390,   389,   392,   391,   393,   393,   394,
     394,   396,   395,   398,   397,   399,   399,   400,   400,   400,
     400,   400,   400,   400,   400,   400,   400,   400,   402,   401,
     403,   405,   404,   406,   407,   409,   408,   410,   410,   411,
     411,   413,   412,   415,   414,   416,   416,   417,   417,   418,
     418,   418,   418,   418,   418,   418,   418,   418,   418,   418,
     420,   419,   422,   421,   424,   423,   426,   425,   428,   427,
     430,   429,   432,   431,   434,   433,   435,   435,   437,   436,
     439,   438,   440,   440,   442,   441,   443,   443,   444,   444,
     445,   445,   445,   445,   445,   445,   445,   446,   448,   447,
     449,   451,   450,   452,   452,   453,   453,   453,   453,   453,
     453,   453,   453,   453,   455,   454,   456,   456,   456,   457,
     459,   458,   460,   461,   462,   464,   463,   465,   465,   466,
     466,   466,   466,   466,   468,   467,   470,   469,   472,   471,
     474,   473,   475,   475,   476,   476,   476,   476,   476,   476,
     476,   476,   476,   476,   476,   476,   476,   476,   476,   476,
     476,   477,   479,   478,   481,   480,   482,   484,   483,   485,
     486,   488,   487,   489,   489,   491,   490,   492,   493,   494,
     496,   495,   497,   497,   497,   497,   497,   499,   498,   501,
     500,   503,   502,   505,   504,   507,   506,   509,   508,   510,
     510,   511,   513,   512,   514,   514,   516,   515,   517,   517,
     518,   518,   518,   518,   518,   518,   518,   519,   521,   520,
     523,   522,   524,   524,   526,   525,   527,   527,   528,   528,
     528,   528,   530,   529,   531,   532,   533
  };

  const unsigned char
  Dhcp6Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     0,     4,     0,     1,     1,
       3,     0,     4,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     0,     6,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     0,     6,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       6,     0,     6,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     3,     0,     4,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     0,     6,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     1,
       1,     1,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     6,     0,     4,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       0,     4,     0,     4,     0,     4,     1,     0,     4,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     4,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     1,     1,     0,     4,
       0,     6,     1,     3,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     3,
       0,     4,     3,     3,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     0,     4,     1,     1,     0,     4,     3,     3,     3,
       0,     4,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     6,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     0,     4,     3,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp6Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"re-detect\"",
  "\"lease-database\"", "\"hosts-database\"", "\"hosts-databases\"",
  "\"type\"", "\"memfile\"", "\"mysql\"", "\"postgresql\"", "\"cql\"",
  "\"user\"", "\"password\"", "\"host\"", "\"port\"", "\"persist\"",
  "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
  "\"contact-points\"", "\"max-reconnect-tries\"",
  "\"reconnect-wait-time\"", "\"keyspace\"", "\"request-timeout\"",
  "\"tcp-keepalive\"", "\"tcp-nodelay\"", "\"max-row-errors\"",
  "\"preferred-lifetime\"", "\"valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"decline-probation-period\"", "\"subnet6\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"pools\"", "\"pool\"", "\"pd-pools\"",
  "\"prefix\"", "\"prefix-len\"", "\"excluded-prefix\"",
  "\"excluded-prefix-len\"", "\"delegated-len\"", "\"user-context\"",
  "\"comment\"", "\"subnet\"", "\"interface\"", "\"interface-id\"",
  "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"all\"", "\"shared-networks\"", "\"mac-sources\"",
  "\"relay-supplied-options\"", "\"host-reservation-identifiers\"",
  "\"client-classes\"", "\"require-client-classes\"", "\"test\"",
  "\"only-if-required\"", "\"client-class\"", "\"reservations\"",
  "\"ip-addresses\"", "\"prefixes\"", "\"duid\"", "\"hw-address\"",
  "\"hostname\"", "\"flex-id\"", "\"relay\"", "\"ip-address\"",
  "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
  "\"expired-leases-processing\"", "\"reclaim-timer-wait-time\"",
  "\"flush-reclaimed-timer-wait-time\"", "\"hold-reclaimed-time\"",
  "\"max-reclaim-leases\"", "\"max-reclaim-time\"",
  "\"unwarned-reclaim-cycles\"", "\"server-id\"", "\"LLT\"", "\"EN\"",
  "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"", "\"enterprise-id\"",
  "\"dhcp4o6-port\"", "\"control-socket\"", "\"socket-type\"",
  "\"socket-name\"", "\"dhcp-ddns\"", "\"enable-updates\"",
  "\"qualifying-suffix\"", "\"server-ip\"", "\"server-port\"",
  "\"sender-ip\"", "\"sender-port\"", "\"max-queue-size\"",
  "\"ncr-protocol\"", "\"ncr-format\"", "\"always-include-fqdn\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"UDP\"", "\"TCP\"",
  "\"JSON\"", "\"when-present\"", "\"never\"", "\"always\"",
  "\"when-not-present\"", "\"Logging\"", "\"loggers\"",
  "\"output_options\"", "\"output\"", "\"debuglevel\"", "\"severity\"",
  "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"Dhcp4\"", "\"DhcpDdns\"",
  "\"Control-agent\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP6", "SUB_DHCP6",
  "SUB_INTERFACES6", "SUB_SUBNET6", "SUB_POOL6", "SUB_PD_POOL",
  "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "SUB_LOGGING",
  "\"constant string\"", "\"integer\"", "\"floating point\"",
  "\"boolean\"", "$accept", "start", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "$@13", "$@14",
  "value", "sub_json", "map2", "$@15", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@16", "list_content",
  "not_empty_list", "list_strings", "$@17", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@18",
  "global_objects", "global_object", "dhcp6_object", "$@19", "sub_dhcp6",
  "$@20", "global_params", "global_param", "preferred_lifetime",
  "valid_lifetime", "renew_timer", "rebind_timer",
  "decline_probation_period", "interfaces_config", "$@21",
  "sub_interfaces6", "$@22", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@23", "re_detect",
  "lease_database", "$@24", "hosts_database", "$@25", "hosts_databases",
  "$@26", "database_list", "not_empty_database_list", "database", "$@27",
  "database_map_params", "database_map_param", "database_type", "$@28",
  "db_type", "user", "$@29", "password", "$@30", "host", "$@31", "port",
  "name", "$@32", "persist", "lfc_interval", "readonly", "connect_timeout",
  "reconnect_wait_time", "request_timeout", "tcp_keepalive", "tcp_nodelay",
  "contact_points", "$@33", "max_reconnect_tries", "keyspace", "$@34",
  "max_row_errors", "mac_sources", "$@35", "mac_sources_list",
  "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@36",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@37",
  "hooks_libraries", "$@38", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@39",
  "sub_hooks_library", "$@40", "hooks_params", "hooks_param", "library",
  "$@41", "parameters", "$@42", "expired_leases_processing", "$@43",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@44",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@45",
  "sub_subnet6", "$@46", "subnet6_params", "subnet6_param", "subnet",
  "$@47", "interface", "$@48", "interface_id", "$@49", "client_class",
  "$@50", "require_client_classes", "$@51", "reservation_mode", "$@52",
  "hr_mode", "id", "rapid_commit", "shared_networks", "$@53",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@54", "shared_network_params", "shared_network_param",
  "option_def_list", "$@55", "sub_option_def_list", "$@56",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@57", "sub_option_def", "$@58",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@59",
  "option_def_record_types", "$@60", "space", "$@61", "option_def_space",
  "option_def_encapsulate", "$@62", "option_def_array", "option_data_list",
  "$@63", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@64", "sub_option_data", "$@65",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@66",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@67", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@68", "sub_pool6", "$@69",
  "pool_params", "pool_param", "pool_entry", "$@70", "user_context",
  "$@71", "comment", "$@72", "pd_pools_list", "$@73",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@74", "sub_pd_pool", "$@75", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@76", "pd_prefix_len", "excluded_prefix", "$@77",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@78",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@79", "sub_reservation", "$@80", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@81", "prefixes", "$@82", "duid", "$@83", "hw_address", "$@84",
  "hostname", "$@85", "flex_id_value", "$@86",
  "reservation_client_classes", "$@87", "relay", "$@88", "relay_map",
  "ip_address", "$@89", "client_classes", "$@90", "client_classes_list",
  "client_class_entry", "$@91", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@92", "only_if_required",
  "server_id", "$@93", "server_id_params", "server_id_param",
  "server_id_type", "$@94", "duid_type", "htype", "identifier", "$@95",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@96",
  "control_socket_params", "control_socket_param", "socket_type", "$@97",
  "socket_name", "$@98", "dhcp_ddns", "$@99", "sub_dhcp_ddns", "$@100",
  "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "qualifying_suffix", "$@101", "server_ip", "$@102", "server_port",
  "sender_ip", "$@103", "sender_port", "max_queue_size", "ncr_protocol",
  "$@104", "ncr_protocol_value", "ncr_format", "$@105",
  "always_include_fqdn", "override_no_update", "override_client_update",
  "replace_client_name", "$@106", "replace_client_name_value",
  "generated_prefix", "$@107", "dhcp4_json_object", "$@108",
  "dhcpddns_json_object", "$@109", "control_agent_json_object", "$@110",
  "logging_object", "$@111", "sub_logging", "$@112", "logging_params",
  "logging_param", "loggers", "$@113", "loggers_entries", "logger_entry",
  "$@114", "logger_params", "logger_param", "debuglevel", "severity",
  "$@115", "output_options_list", "$@116", "output_options_list_content",
  "output_entry", "$@117", "output_params_list", "output_params", "output",
  "$@118", "flush", "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short
  Dhcp6Parser::yyrline_[] =
  {
       0,   247,   247,   247,   248,   248,   249,   249,   250,   250,
     251,   251,   252,   252,   253,   253,   254,   254,   255,   255,
     256,   256,   257,   257,   258,   258,   259,   259,   260,   260,
     268,   269,   270,   271,   272,   273,   274,   277,   282,   282,
     293,   296,   297,   300,   304,   311,   311,   318,   319,   322,
     326,   333,   333,   340,   341,   344,   348,   359,   369,   369,
     384,   385,   389,   390,   391,   392,   393,   394,   397,   397,
     412,   412,   421,   422,   427,   428,   429,   430,   431,   432,
     433,   434,   435,   436,   437,   438,   439,   440,   441,   442,
     443,   444,   445,   446,   447,   448,   449,   450,   451,   452,
     455,   460,   465,   470,   475,   480,   480,   491,   491,   500,
     501,   504,   505,   506,   507,   508,   511,   511,   521,   527,
     527,   539,   539,   551,   551,   561,   562,   565,   566,   569,
     569,   579,   580,   583,   584,   585,   586,   587,   588,   589,
     590,   591,   592,   593,   594,   595,   596,   597,   598,   599,
     600,   601,   604,   604,   611,   612,   613,   614,   617,   617,
     625,   625,   633,   633,   641,   646,   646,   654,   659,   664,
     669,   674,   679,   684,   689,   694,   694,   702,   707,   707,
     715,   720,   720,   730,   731,   734,   735,   738,   743,   748,
     748,   758,   759,   762,   763,   764,   767,   772,   779,   779,
     789,   789,   799,   800,   803,   804,   807,   807,   817,   817,
     827,   828,   829,   832,   833,   836,   836,   844,   844,   852,
     852,   863,   864,   867,   868,   869,   870,   871,   872,   875,
     880,   885,   890,   895,   900,   908,   908,   921,   922,   925,
     926,   933,   933,   959,   959,   970,   971,   975,   976,   977,
     978,   979,   980,   981,   982,   983,   984,   985,   986,   987,
     988,   989,   990,   991,   992,   993,   994,   997,   997,  1005,
    1005,  1013,  1013,  1021,  1021,  1029,  1029,  1039,  1039,  1046,
    1047,  1048,  1051,  1056,  1064,  1064,  1075,  1076,  1080,  1081,
    1084,  1084,  1092,  1093,  1096,  1097,  1098,  1099,  1100,  1101,
    1102,  1103,  1104,  1105,  1106,  1107,  1108,  1109,  1110,  1111,
    1112,  1119,  1119,  1132,  1132,  1141,  1142,  1145,  1146,  1151,
    1151,  1166,  1166,  1180,  1181,  1184,  1185,  1188,  1189,  1190,
    1191,  1192,  1193,  1194,  1195,  1196,  1197,  1200,  1202,  1207,
    1209,  1209,  1217,  1217,  1225,  1225,  1233,  1235,  1235,  1243,
    1252,  1252,  1264,  1265,  1270,  1271,  1276,  1276,  1288,  1288,
    1300,  1301,  1306,  1307,  1312,  1313,  1314,  1315,  1316,  1317,
    1318,  1319,  1320,  1323,  1325,  1325,  1333,  1335,  1337,  1342,
    1350,  1350,  1362,  1363,  1366,  1367,  1370,  1370,  1380,  1380,
    1389,  1390,  1393,  1394,  1395,  1396,  1397,  1398,  1399,  1402,
    1402,  1410,  1410,  1435,  1435,  1465,  1465,  1477,  1478,  1481,
    1482,  1485,  1485,  1497,  1497,  1509,  1510,  1513,  1514,  1515,
    1516,  1517,  1518,  1519,  1520,  1521,  1522,  1523,  1526,  1526,
    1534,  1539,  1539,  1547,  1552,  1560,  1560,  1570,  1571,  1574,
    1575,  1578,  1578,  1587,  1587,  1596,  1597,  1600,  1601,  1605,
    1606,  1607,  1608,  1609,  1610,  1611,  1612,  1613,  1614,  1615,
    1618,  1618,  1628,  1628,  1638,  1638,  1646,  1646,  1654,  1654,
    1662,  1662,  1670,  1670,  1683,  1683,  1693,  1694,  1697,  1697,
    1708,  1708,  1718,  1719,  1722,  1722,  1732,  1733,  1736,  1737,
    1740,  1741,  1742,  1743,  1744,  1745,  1746,  1749,  1751,  1751,
    1759,  1767,  1767,  1779,  1780,  1783,  1784,  1785,  1786,  1787,
    1788,  1789,  1790,  1791,  1794,  1794,  1801,  1802,  1803,  1806,
    1811,  1811,  1819,  1824,  1831,  1838,  1838,  1848,  1849,  1852,
    1853,  1854,  1855,  1856,  1859,  1859,  1867,  1867,  1877,  1877,
    1889,  1889,  1899,  1900,  1903,  1904,  1905,  1906,  1907,  1908,
    1909,  1910,  1911,  1912,  1913,  1914,  1915,  1916,  1917,  1918,
    1919,  1922,  1927,  1927,  1935,  1935,  1943,  1948,  1948,  1956,
    1961,  1966,  1966,  1974,  1975,  1978,  1978,  1986,  1991,  1996,
    2001,  2001,  2009,  2012,  2015,  2018,  2021,  2027,  2027,  2037,
    2037,  2044,  2044,  2051,  2051,  2064,  2064,  2074,  2074,  2085,
    2086,  2090,  2094,  2094,  2106,  2107,  2111,  2111,  2119,  2120,
    2123,  2124,  2125,  2126,  2127,  2128,  2129,  2132,  2137,  2137,
    2145,  2145,  2155,  2156,  2159,  2159,  2167,  2168,  2171,  2172,
    2173,  2174,  2177,  2177,  2185,  2190,  2195
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
#line 4811 "dhcp6_parser.cc" // lalr1.cc:1218
#line 2200 "dhcp6_parser.yy" // lalr1.cc:1219


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
