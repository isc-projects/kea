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
      case 195: // value
      case 199: // map_value
      case 253: // db_type
      case 346: // hr_mode
      case 482: // duid_type
      case 517: // ncr_protocol_value
      case 524: // replace_client_name_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 177: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 176: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 175: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 174: // "constant string"
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
      case 195: // value
      case 199: // map_value
      case 253: // db_type
      case 346: // hr_mode
      case 482: // duid_type
      case 517: // ncr_protocol_value
      case 524: // replace_client_name_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 177: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 176: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 175: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 174: // "constant string"
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
      case 195: // value
      case 199: // map_value
      case 253: // db_type
      case 346: // hr_mode
      case 482: // duid_type
      case 517: // ncr_protocol_value
      case 524: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 177: // "boolean"
        value.move< bool > (that.value);
        break;

      case 176: // "floating point"
        value.move< double > (that.value);
        break;

      case 175: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 174: // "constant string"
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
            case 174: // "constant string"

#line 253 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< std::string > (); }
#line 398 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 175: // "integer"

#line 253 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< int64_t > (); }
#line 405 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 176: // "floating point"

#line 253 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< double > (); }
#line 412 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 177: // "boolean"

#line 253 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< bool > (); }
#line 419 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 195: // value

#line 253 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 426 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 199: // map_value

#line 253 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 433 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 253: // db_type

#line 253 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 440 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 346: // hr_mode

#line 253 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 447 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 482: // duid_type

#line 253 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 454 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 517: // ncr_protocol_value

#line 253 "dhcp6_parser.yy" // lalr1.cc:672
        { yyoutput << yysym.value.template as< ElementPtr > (); }
#line 461 "dhcp6_parser.cc" // lalr1.cc:672
        break;

      case 524: // replace_client_name_value

#line 253 "dhcp6_parser.yy" // lalr1.cc:672
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
      case 195: // value
      case 199: // map_value
      case 253: // db_type
      case 346: // hr_mode
      case 482: // duid_type
      case 517: // ncr_protocol_value
      case 524: // replace_client_name_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 177: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 176: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 175: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 174: // "constant string"
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
#line 262 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 727 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 4:
#line 263 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.CONFIG; }
#line 733 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 6:
#line 264 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP6; }
#line 739 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 8:
#line 265 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 745 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 10:
#line 266 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.SUBNET6; }
#line 751 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 12:
#line 267 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.POOLS; }
#line 757 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 14:
#line 268 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 763 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 16:
#line 269 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 769 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 18:
#line 270 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP6; }
#line 775 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 20:
#line 271 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 781 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 22:
#line 272 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 787 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 24:
#line 273 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 793 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 26:
#line 274 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 799 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 28:
#line 275 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.LOGGING; }
#line 805 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 30:
#line 276 "dhcp6_parser.yy" // lalr1.cc:907
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 811 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 32:
#line 284 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 817 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 33:
#line 285 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as< double > (), ctx.loc2pos(yystack_[0].location))); }
#line 823 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 34:
#line 286 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 829 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 35:
#line 287 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 835 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 36:
#line 288 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 841 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 37:
#line 289 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 847 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 38:
#line 290 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 853 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 39:
#line 293 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as< ElementPtr > ());
}
#line 862 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 40:
#line 298 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 873 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 41:
#line 303 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 883 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 42:
#line 309 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 889 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 45:
#line 316 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 898 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 46:
#line 320 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as< std::string > (), yystack_[0].value.as< ElementPtr > ());
                  }
#line 908 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 47:
#line 327 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 917 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 48:
#line 330 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // list parsing complete. Put any sanity checking here
}
#line 925 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 51:
#line 338 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 934 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 52:
#line 342 "dhcp6_parser.yy" // lalr1.cc:907
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as< ElementPtr > ());
                  }
#line 943 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 53:
#line 349 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // List parsing about to start
}
#line 951 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 54:
#line 351 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 960 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 57:
#line 360 "dhcp6_parser.yy" // lalr1.cc:907
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 969 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 58:
#line 364 "dhcp6_parser.yy" // lalr1.cc:907
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 978 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 59:
#line 375 "dhcp6_parser.yy" // lalr1.cc:907
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as< std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 989 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 60:
#line 385 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1000 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 61:
#line 390 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 413 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 420 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1036 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 72:
#line 428 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1046 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 73:
#line 432 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No global parameter is required
    // parsing completed
}
#line 1055 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 109:
#line 478 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1063 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 110:
#line 480 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr datadir(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1073 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 111:
#line 486 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1082 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 112:
#line 491 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1091 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 113:
#line 496 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1100 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 114:
#line 501 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1109 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 115:
#line 506 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1118 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 116:
#line 511 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1126 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 117:
#line 513 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1136 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 118:
#line 519 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1147 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 119:
#line 524 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1157 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 120:
#line 530 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1167 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 121:
#line 534 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1176 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 129:
#line 550 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1187 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 130:
#line 555 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1196 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 131:
#line 560 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1205 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 132:
#line 566 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1216 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 133:
#line 571 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1227 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 134:
#line 578 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1238 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 135:
#line 583 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1249 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 136:
#line 590 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1260 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 137:
#line 595 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1269 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 142:
#line 608 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1279 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 143:
#line 612 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1289 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 166:
#line 644 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1297 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 167:
#line 646 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1306 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 168:
#line 651 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1312 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 169:
#line 652 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1318 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 170:
#line 653 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1324 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 171:
#line 654 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1330 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 172:
#line 657 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1338 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 173:
#line 659 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr user(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1348 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 174:
#line 665 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1356 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 175:
#line 667 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1366 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 176:
#line 673 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1374 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 177:
#line 675 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr h(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1384 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 178:
#line 681 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr p(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1393 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 179:
#line 686 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1401 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 180:
#line 688 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1411 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 181:
#line 694 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1420 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 182:
#line 699 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1429 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 183:
#line 704 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1438 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 184:
#line 709 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1447 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 185:
#line 714 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1456 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 186:
#line 719 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1465 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 187:
#line 724 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1474 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 188:
#line 729 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1483 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 189:
#line 734 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1491 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 190:
#line 736 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1501 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 191:
#line 742 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr n(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1510 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 192:
#line 747 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1518 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 193:
#line 749 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1528 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 194:
#line 755 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1536 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 195:
#line 757 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1546 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 196:
#line 763 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1554 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 197:
#line 765 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1564 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 198:
#line 771 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1575 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 199:
#line 776 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1584 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 203:
#line 786 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1592 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 204:
#line 788 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 1612 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 205:
#line 804 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1623 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 206:
#line 809 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1632 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 211:
#line 822 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1641 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 212:
#line 827 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1650 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 213:
#line 832 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1661 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 214:
#line 837 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1670 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 220:
#line 851 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1679 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 221:
#line 856 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1688 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 222:
#line 863 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1699 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 223:
#line 868 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1708 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 224:
#line 873 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1719 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 225:
#line 878 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1728 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 230:
#line 891 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1738 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 231:
#line 895 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1748 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 232:
#line 901 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1758 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 233:
#line 905 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1768 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 239:
#line 920 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1776 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 240:
#line 922 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1786 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 241:
#line 928 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1794 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 242:
#line 930 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 1803 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 243:
#line 936 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1814 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 244:
#line 941 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1824 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 253:
#line 959 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1833 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 254:
#line 964 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1842 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 255:
#line 969 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1851 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 256:
#line 974 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1860 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 257:
#line 979 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1869 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 258:
#line 984 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1878 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 259:
#line 992 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1889 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 260:
#line 997 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1898 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 265:
#line 1017 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1908 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 266:
#line 1021 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 1934 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 267:
#line 1043 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1944 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 268:
#line 1047 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1954 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 291:
#line 1081 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1962 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 292:
#line 1083 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1972 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 293:
#line 1089 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1980 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 294:
#line 1091 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1990 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 295:
#line 1097 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1998 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 296:
#line 1099 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2008 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 297:
#line 1105 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2016 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 298:
#line 1107 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2026 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 299:
#line 1113 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2037 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 300:
#line 1118 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2046 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 301:
#line 1123 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2054 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 302:
#line 1125 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 2063 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 303:
#line 1130 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2069 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 304:
#line 1131 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2075 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 305:
#line 1132 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2081 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 306:
#line 1133 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2087 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 307:
#line 1136 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr id(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2096 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 308:
#line 1141 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2105 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 309:
#line 1149 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2116 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 310:
#line 1154 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2125 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 315:
#line 1169 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2135 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 316:
#line 1173 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 2143 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 336:
#line 1204 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2154 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 337:
#line 1209 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2163 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 338:
#line 1217 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2172 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 339:
#line 1220 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // parsing completed
}
#line 2180 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 344:
#line 1236 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2190 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 345:
#line 1240 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2202 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 346:
#line 1251 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2212 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 347:
#line 1255 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2224 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 363:
#line 1287 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr code(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2233 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 365:
#line 1294 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2241 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 366:
#line 1296 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2251 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 367:
#line 1302 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2259 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 368:
#line 1304 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2269 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 369:
#line 1310 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2277 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 370:
#line 1312 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr space(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2287 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 372:
#line 1320 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2295 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 373:
#line 1322 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2305 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 374:
#line 1328 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2314 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 375:
#line 1337 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2325 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 376:
#line 1342 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2334 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 381:
#line 1361 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2344 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 382:
#line 1365 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2353 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 383:
#line 1373 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2363 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 384:
#line 1377 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2372 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 399:
#line 1410 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2380 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 400:
#line 1412 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr data(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2390 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 403:
#line 1422 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2399 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 404:
#line 1427 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2408 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 405:
#line 1435 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2419 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 406:
#line 1440 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2428 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 411:
#line 1455 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2438 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 412:
#line 1459 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2448 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 413:
#line 1465 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2458 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 414:
#line 1469 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2467 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 424:
#line 1487 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2475 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 425:
#line 1489 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2485 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 426:
#line 1495 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2493 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 427:
#line 1497 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 2520 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 428:
#line 1520 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2528 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 429:
#line 1522 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 2557 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 430:
#line 1550 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2568 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 431:
#line 1555 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2577 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 436:
#line 1570 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2587 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 437:
#line 1574 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2599 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 438:
#line 1582 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2609 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 439:
#line 1586 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2621 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 453:
#line 1611 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2629 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 454:
#line 1613 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2639 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 455:
#line 1619 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2648 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 456:
#line 1624 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2656 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 457:
#line 1626 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2666 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 458:
#line 1632 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2675 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 459:
#line 1637 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2684 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 460:
#line 1645 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2695 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 461:
#line 1650 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2704 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 466:
#line 1663 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2714 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 467:
#line 1667 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2723 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 468:
#line 1672 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2733 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 469:
#line 1676 "dhcp6_parser.yy" // lalr1.cc:907
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2742 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 485:
#line 1703 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2753 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 486:
#line 1708 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2762 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 487:
#line 1713 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2773 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 488:
#line 1718 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2782 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 489:
#line 1723 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2790 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 490:
#line 1725 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr d(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2800 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 491:
#line 1731 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2808 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 492:
#line 1733 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2818 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 493:
#line 1739 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2826 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 494:
#line 1741 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr host(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2836 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 495:
#line 1747 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2844 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 496:
#line 1749 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2854 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 497:
#line 1755 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2865 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 498:
#line 1760 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2874 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 499:
#line 1768 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2885 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 500:
#line 1773 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2894 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 503:
#line 1782 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2902 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 504:
#line 1784 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2912 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 505:
#line 1793 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2923 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 506:
#line 1798 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2932 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 509:
#line 1807 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2942 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 510:
#line 1811 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2952 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 523:
#line 1836 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2960 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 524:
#line 1838 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr test(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2970 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 525:
#line 1844 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2979 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 526:
#line 1852 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2990 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 527:
#line 1857 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3001 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 539:
#line 1879 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 3009 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 540:
#line 1881 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3018 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 541:
#line 1886 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3024 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 542:
#line 1887 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3030 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 543:
#line 1888 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3036 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 544:
#line 1891 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3045 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 545:
#line 1896 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3053 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 546:
#line 1898 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr id(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3063 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 547:
#line 1904 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3072 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 548:
#line 1909 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3081 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 549:
#line 1916 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr time(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3090 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 550:
#line 1923 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3101 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 551:
#line 1928 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3110 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 559:
#line 1944 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3118 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 560:
#line 1946 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3128 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 561:
#line 1952 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3136 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 562:
#line 1954 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr name(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3146 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 563:
#line 1962 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3154 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 564:
#line 1964 "dhcp6_parser.yy" // lalr1.cc:907
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
#line 3194 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 565:
#line 2002 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3205 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 566:
#line 2007 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3216 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 567:
#line 2014 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3226 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 568:
#line 2018 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3236 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 589:
#line 2048 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3245 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 590:
#line 2053 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3253 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 591:
#line 2055 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3263 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 592:
#line 2061 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3271 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 593:
#line 2063 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3281 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 594:
#line 2069 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3290 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 595:
#line 2074 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3298 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 596:
#line 2076 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3308 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 597:
#line 2082 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3317 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 598:
#line 2087 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3326 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 599:
#line 2092 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3334 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 600:
#line 2094 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3343 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 601:
#line 2100 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3349 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 602:
#line 2101 "dhcp6_parser.yy" // lalr1.cc:907
    { yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3355 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 603:
#line 2104 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3363 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 604:
#line 2106 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3373 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 605:
#line 2112 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3382 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 606:
#line 2117 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3391 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 607:
#line 2122 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3399 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 608:
#line 2124 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3408 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 609:
#line 2130 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3416 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 610:
#line 2133 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3424 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 611:
#line 2136 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3432 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 612:
#line 2139 "dhcp6_parser.yy" // lalr1.cc:907
    {
      yylhs.value.as< ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3440 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 613:
#line 2142 "dhcp6_parser.yy" // lalr1.cc:907
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3449 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 614:
#line 2148 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3457 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 615:
#line 2150 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3467 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 616:
#line 2156 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3475 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 617:
#line 2158 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3485 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 618:
#line 2164 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3493 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 619:
#line 2166 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr s(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3503 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 620:
#line 2174 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3511 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 621:
#line 2176 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3520 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 622:
#line 2181 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3528 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 623:
#line 2183 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3537 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 624:
#line 2188 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3545 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 625:
#line 2190 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as< ElementPtr > ());
    ctx.leave();
}
#line 3554 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 626:
#line 2197 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3565 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 627:
#line 2202 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3575 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 628:
#line 2208 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3585 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 629:
#line 2212 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // No config_control params are required
    // parsing completed
}
#line 3594 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 634:
#line 2227 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3605 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 635:
#line 2232 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3614 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 636:
#line 2237 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr value(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3623 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 637:
#line 2247 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3634 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 638:
#line 2252 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3643 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 639:
#line 2257 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3653 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 640:
#line 2261 "dhcp6_parser.yy" // lalr1.cc:907
    {
    // parsing completed
}
#line 3661 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 644:
#line 2277 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3672 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 645:
#line 2282 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3681 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 648:
#line 2294 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3691 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 649:
#line 2298 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3699 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 659:
#line 2315 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3708 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 660:
#line 2320 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3716 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 661:
#line 2322 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3726 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 662:
#line 2328 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3737 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 663:
#line 2333 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3746 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 666:
#line 2342 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3756 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 667:
#line 2346 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.stack_.pop_back();
}
#line 3764 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 674:
#line 2360 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3772 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 675:
#line 2362 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as< std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3782 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 676:
#line 2368 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as< bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3791 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 677:
#line 2373 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3800 "dhcp6_parser.cc" // lalr1.cc:907
    break;

  case 678:
#line 2378 "dhcp6_parser.yy" // lalr1.cc:907
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as< int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3809 "dhcp6_parser.cc" // lalr1.cc:907
    break;


#line 3813 "dhcp6_parser.cc" // lalr1.cc:907
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


  const short Dhcp6Parser::yypact_ninf_ = -837;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     418,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,    57,    65,    64,    66,
      68,    87,    91,   126,   133,   148,   164,   184,   195,   203,
     229,   230,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,    65,   -95,    27,    69,    22,   234,    72,    39,
     196,   188,    41,   262,   -53,   375,    96,   144,  -837,   242,
     249,   269,   263,   281,  -837,  -837,  -837,  -837,  -837,   307,
    -837,    94,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,   309,   316,   317,   323,   341,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,   347,  -837,  -837,  -837,
    -837,   123,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,   353,  -837,   140,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,   357,
     367,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,   141,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,   178,  -837,  -837,  -837,  -837,  -837,   369,  -837,   385,
     410,  -837,  -837,  -837,  -837,  -837,  -837,   187,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,   416,   352,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,   417,  -837,  -837,   423,  -837,
    -837,  -837,   424,  -837,  -837,   422,   390,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
     433,   435,  -837,  -837,  -837,  -837,   434,   440,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
     191,  -837,  -837,  -837,   442,  -837,  -837,   443,  -837,   444,
     445,  -837,  -837,   446,   448,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,   260,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
     261,  -837,  -837,  -837,   449,   264,  -837,  -837,  -837,  -837,
      65,    65,  -837,   280,   451,   452,   453,   456,   459,  -837,
      27,  -837,   462,   463,   464,   465,   466,   467,   297,   298,
     299,   300,   301,   474,   475,   477,   478,   479,   480,   481,
     482,   483,   485,   486,   487,   488,   489,   490,   491,   492,
     322,   494,   495,   509,    69,  -837,   510,   338,    22,  -837,
     512,   513,   514,   518,   519,   349,   348,   523,   524,   525,
     234,  -837,   526,    72,  -837,   527,   362,   531,   363,   364,
      39,  -837,   532,   536,   537,   539,   540,   541,   542,  -837,
     196,  -837,   543,   544,   378,   546,   551,   552,   381,  -837,
      41,   553,   382,   383,  -837,   262,   557,   558,   -17,  -837,
     388,   560,   562,   394,   567,   400,   419,   568,   569,   415,
     420,   570,   589,   591,   592,   375,  -837,   594,    96,  -837,
     595,   425,   144,  -837,  -837,  -837,   599,   598,   600,    65,
      65,    65,  -837,   432,   601,   602,   603,   604,   608,  -837,
    -837,  -837,  -837,  -837,   441,   609,   611,   612,   613,   447,
     221,   614,   617,   618,   619,   620,   621,   623,   624,   625,
     626,  -837,   627,   613,   629,  -837,   632,  -837,  -837,   633,
     634,   457,   468,   469,  -837,  -837,   632,   470,   638,  -837,
     472,  -837,   473,  -837,   476,  -837,  -837,  -837,   632,   632,
     632,   484,   493,   496,   497,  -837,   498,   499,  -837,   500,
     501,   502,  -837,  -837,   503,  -837,  -837,  -837,   504,    65,
    -837,  -837,   505,   506,  -837,   507,  -837,  -837,   -98,   508,
    -837,  -837,    34,   511,   515,   516,  -837,   635,  -837,   636,
    -837,  -837,    65,    69,    96,  -837,  -837,  -837,  -837,   144,
      22,   193,   193,   642,  -837,   644,   645,   646,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,   647,   -50,    65,   315,
     571,   648,   649,   652,   152,   138,   128,  -837,   375,  -837,
    -837,   653,   654,  -837,  -837,  -837,  -837,  -837,   -49,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,   655,   642,  -837,   267,   278,   279,   320,
    -837,  -837,  -837,  -837,   659,   660,   661,   662,   664,  -837,
     665,   678,  -837,  -837,  -837,   679,   680,   682,  -837,   321,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
     332,  -837,   681,   615,  -837,  -837,   685,   622,  -837,  -837,
     686,   690,  -837,  -837,   688,   692,  -837,  -837,   691,   693,
    -837,  -837,  -837,   119,  -837,  -837,  -837,   694,  -837,  -837,
    -837,   166,  -837,  -837,  -837,  -837,   333,  -837,  -837,  -837,
     176,  -837,  -837,   695,   696,  -837,  -837,   697,   699,  -837,
     684,   700,   701,   702,   703,   704,   334,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,   705,   706,   707,  -837,
    -837,  -837,  -837,   335,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,   336,  -837,  -837,  -837,   344,
     538,  -837,   708,   710,  -837,  -837,   709,   713,  -837,  -837,
    -837,   711,  -837,  -837,   197,  -837,   712,  -837,  -837,  -837,
    -837,   716,   717,   718,   719,   455,   521,   549,   548,   554,
     722,   555,   556,   723,   724,   728,   559,   561,   563,   193,
    -837,  -837,   193,  -837,   642,   234,  -837,   644,    41,  -837,
     645,   262,  -837,   646,   389,  -837,   647,   -50,  -837,  -837,
     315,  -837,   729,   571,  -837,    77,   648,  -837,   196,  -837,
     649,   -53,  -837,   652,   564,   566,   572,   573,   574,   575,
     152,  -837,   731,   733,   576,   577,   578,   138,  -837,   734,
     738,   128,  -837,  -837,  -837,   737,   714,    72,  -837,   653,
      39,  -837,   654,   740,  -837,    13,   655,  -837,  -837,   398,
     580,   581,   582,  -837,  -837,  -837,  -837,  -837,   583,  -837,
    -837,   584,   585,   586,  -837,  -837,  -837,  -837,   345,  -837,
     351,  -837,   753,  -837,   754,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,   360,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,   590,  -837,
    -837,   741,  -837,  -837,  -837,  -837,  -837,   755,   743,  -837,
    -837,  -837,  -837,  -837,   757,  -837,   361,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,   104,   593,  -837,  -837,  -837,
    -837,   596,   597,  -837,  -837,   605,   380,  -837,   387,  -837,
     606,  -837,   762,  -837,  -837,  -837,  -837,  -837,   397,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
     389,  -837,  -837,   764,   631,  -837,    77,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
     765,   607,   768,    13,  -837,  -837,   637,  -837,  -837,   769,
    -837,   640,  -837,  -837,   766,  -837,  -837,   412,  -837,   -18,
     766,  -837,  -837,   771,   772,   773,   399,  -837,  -837,  -837,
    -837,  -837,  -837,   774,   639,   650,   651,   -18,  -837,   641,
    -837,  -837,  -837,  -837,  -837
  };

  const unsigned short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   120,     9,
     267,    11,   413,    13,   438,    15,   468,    17,   338,    19,
     346,    21,   383,    23,   232,    25,   567,    27,   639,    29,
     628,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     470,     0,   348,   385,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   637,   620,   622,   624,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   109,   626,
     118,   132,   134,   136,     0,     0,     0,     0,     0,   116,
     259,   336,   375,   426,   428,   301,   309,   205,   222,   213,
     198,   505,   460,   224,   243,   526,     0,   550,   563,   565,
     108,     0,    74,    76,    77,    78,    79,    80,    81,   106,
      84,    85,    86,    87,   103,    88,    90,    89,    94,    95,
      82,   107,    83,    92,    93,   101,   102,   104,    91,    96,
      97,    98,    99,   100,   105,   129,     0,   128,     0,   122,
     124,   125,   126,   127,   405,   430,   291,   293,   295,     0,
       0,   299,   297,   499,   290,   271,   272,   273,   274,     0,
     269,   278,   279,   280,   283,   284,   286,   281,   282,   275,
     276,   288,   289,   277,   285,   287,   424,   423,   419,   420,
     418,     0,   415,   417,   421,   422,   453,     0,   456,     0,
       0,   452,   446,   447,   445,   450,   451,     0,   440,   442,
     443,   448,   449,   444,   497,   485,   487,   489,   491,   493,
     495,   484,   481,   482,   483,     0,   471,   472,   476,   477,
     474,   478,   479,   480,   475,     0,   365,   179,     0,   369,
     367,   372,     0,   361,   362,     0,   349,   350,   352,   364,
     353,   354,   355,   371,   356,   357,   358,   359,   360,   399,
       0,     0,   397,   398,   401,   402,     0,   386,   387,   389,
     390,   391,   392,   393,   394,   395,   396,   239,   241,   236,
       0,   234,   237,   238,     0,   590,   592,     0,   595,     0,
       0,   599,   603,     0,     0,   607,   614,   616,   618,   588,
     586,   587,     0,   569,   571,   572,   573,   574,   575,   576,
     577,   578,   579,   580,   581,   582,   583,   584,   585,   644,
       0,   641,   643,   634,     0,     0,   630,   632,   633,    48,
       0,     0,    41,     0,     0,     0,     0,     0,     0,    59,
       0,    61,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    73,     0,     0,     0,   121,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   268,     0,     0,   414,     0,     0,     0,     0,     0,
       0,   439,     0,     0,     0,     0,     0,     0,     0,   469,
       0,   339,     0,     0,     0,     0,     0,     0,     0,   347,
       0,     0,     0,     0,   384,     0,     0,     0,     0,   233,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   568,     0,     0,   640,
       0,     0,     0,   629,    52,    45,     0,     0,     0,     0,
       0,     0,    63,     0,     0,     0,     0,     0,     0,   111,
     112,   113,   114,   115,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   549,     0,     0,     0,    75,     0,   131,   123,     0,
       0,     0,     0,     0,   307,   308,     0,     0,     0,   270,
       0,   416,     0,   455,     0,   458,   459,   441,     0,     0,
       0,     0,     0,     0,     0,   473,     0,     0,   363,     0,
       0,     0,   374,   351,     0,   403,   404,   388,     0,     0,
     235,   589,     0,     0,   594,     0,   597,   598,     0,     0,
     605,   606,     0,     0,     0,     0,   570,     0,   642,     0,
     636,   631,     0,     0,     0,   621,   623,   625,   110,     0,
       0,     0,     0,   138,   117,   261,   340,   377,    42,   427,
     429,   303,   304,   305,   306,   302,   311,     0,    49,     0,
       0,     0,   462,   226,     0,     0,     0,   564,     0,    53,
     130,   407,   432,   292,   294,   296,   300,   298,     0,   425,
     454,   457,   498,   486,   488,   490,   492,   494,   496,   366,
     180,   370,   368,   373,   400,   240,   242,   591,   593,   596,
     601,   602,   600,   604,   609,   610,   611,   612,   613,   608,
     615,   617,   619,     0,   138,    46,     0,     0,     0,     0,
     166,   172,   174,   176,     0,     0,     0,     0,     0,   189,
       0,     0,   192,   194,   196,     0,     0,     0,   165,     0,
     144,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   158,   159,   160,   161,   156,   157,   162,   163,   164,
       0,   142,     0,   139,   140,   265,     0,   262,   263,   344,
       0,   341,   342,   381,     0,   378,   379,   315,     0,   312,
     313,   211,   212,     0,   207,   209,   210,     0,   220,   221,
     217,     0,   215,   218,   219,   203,     0,   200,   202,   509,
       0,   507,   466,     0,   463,   464,   230,     0,   227,   228,
       0,     0,     0,     0,     0,     0,     0,   245,   247,   248,
     249,   250,   251,   252,   539,   545,     0,     0,     0,   538,
     535,   536,   537,     0,   528,   530,   533,   531,   532,   534,
     559,   561,   558,   556,   557,     0,   552,   554,   555,     0,
      55,   411,     0,   408,   409,   436,     0,   433,   434,   503,
     502,     0,   501,   648,     0,   646,     0,    71,   638,   627,
     119,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     133,   135,     0,   137,     0,     0,   260,     0,   348,   337,
       0,   385,   376,     0,     0,   310,     0,     0,   206,   223,
       0,   214,     0,     0,   199,   511,     0,   506,   470,   461,
       0,     0,   225,     0,     0,     0,     0,     0,     0,     0,
       0,   244,     0,     0,     0,     0,     0,     0,   527,     0,
       0,     0,   551,   566,    57,     0,    56,     0,   406,     0,
       0,   431,     0,     0,   500,     0,     0,   645,   635,     0,
       0,     0,     0,   178,   181,   182,   183,   184,     0,   191,
     185,     0,     0,     0,   186,   187,   188,   145,     0,   141,
       0,   264,     0,   343,     0,   380,   335,   330,   332,   323,
     324,   319,   320,   321,   322,   328,   329,   327,   331,     0,
     317,   325,   333,   334,   326,   314,   208,   216,     0,   201,
     523,     0,   521,   522,   518,   519,   520,     0,   512,   513,
     515,   516,   517,   508,     0,   465,     0,   229,   253,   254,
     255,   256,   257,   258,   246,     0,     0,   544,   547,   548,
     529,     0,     0,   553,    54,     0,     0,   410,     0,   435,
       0,   662,     0,   660,   658,   652,   656,   657,     0,   650,
     654,   655,   653,   647,   168,   169,   170,   171,   167,   173,
     175,   177,   190,   193,   195,   197,   143,   266,   345,   382,
       0,   316,   204,     0,     0,   510,     0,   467,   231,   541,
     542,   543,   540,   546,   560,   562,    58,   412,   437,   504,
       0,     0,     0,     0,   649,   318,     0,   525,   514,     0,
     659,     0,   651,   524,     0,   661,   666,     0,   664,     0,
       0,   663,   674,     0,     0,     0,     0,   668,   670,   671,
     672,   673,   665,     0,     0,     0,     0,     0,   667,     0,
     676,   677,   678,   669,   675
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,    43,  -837,  -460,
    -837,   266,  -837,  -837,  -837,  -837,   165,  -837,  -472,  -837,
    -837,  -837,   -74,  -837,  -837,  -837,   426,  -837,  -837,  -837,
    -837,   205,   395,  -837,  -837,   -62,   -46,   -45,   -43,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,   186,   421,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,   150,  -837,   -19,
    -837,  -576,    -7,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,   -70,  -837,  -609,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,   -35,  -837,  -837,  -837,  -837,
    -837,   -37,  -596,  -837,  -837,  -837,  -837,   -23,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,   -33,  -837,  -837,  -837,
     -26,   401,  -837,  -837,  -837,  -837,  -837,  -837,  -837,   -44,
    -837,  -837,  -837,  -837,  -837,  -837,  -836,  -837,  -837,  -837,
      -9,  -837,  -837,  -837,     1,   438,  -837,  -837,  -835,  -837,
    -834,  -837,   -36,  -837,   -32,  -837,   -42,  -837,  -837,  -837,
    -831,  -837,  -837,  -837,  -837,    -6,  -837,  -837,  -179,   781,
    -837,  -837,  -837,  -837,  -837,     3,  -837,  -837,  -837,     7,
    -837,   429,  -837,   -76,  -837,  -837,  -837,  -837,  -837,   -69,
    -837,  -837,  -837,  -837,  -837,   -11,  -837,  -837,  -837,     5,
    -837,  -837,  -837,     8,  -837,   411,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,   -39,  -837,  -837,
    -837,   -31,   458,  -837,  -837,   -58,  -837,   -24,  -837,  -837,
    -837,  -837,  -837,   -40,  -837,  -837,  -837,   -30,   454,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,   -60,  -837,  -837,  -837,
       2,  -837,  -837,  -837,     9,  -837,   450,   247,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -828,  -837,  -837,  -837,  -837,  -837,  -837,  -837,    12,
    -837,  -837,  -837,  -157,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,    -5,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,    -8,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,   270,   427,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,   295,   413,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,   303,   428,  -837,  -837,  -837,   -16,  -837,  -837,
    -162,  -837,  -837,  -837,  -837,  -837,  -837,  -177,  -837,  -837,
    -193,  -837,  -837,  -837,  -837,  -837
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   609,    92,    93,    43,    72,    89,    90,   630,   810,
     905,   906,   698,    45,    74,   101,   102,   103,   364,    47,
      75,   141,   142,   143,   372,   144,   145,   146,   147,   148,
     149,   383,   150,   374,    49,    76,   178,   179,   180,   406,
     181,   151,   375,   152,   376,   153,   377,   722,   723,   724,
     852,   699,   700,   701,   831,  1028,   702,   832,   703,   833,
     704,   834,   705,   706,   443,   707,   708,   709,   710,   711,
     712,   713,   714,   715,   840,   716,   717,   843,   718,   844,
     719,   845,   154,   394,   756,   757,   758,   872,   155,   391,
     743,   744,   745,   746,   156,   393,   751,   752,   753,   754,
     157,   392,   158,   397,   767,   768,   769,   881,    65,    84,
     310,   311,   312,   456,   313,   457,   159,   398,   776,   777,
     778,   779,   780,   781,   782,   783,   160,   384,   726,   727,
     728,   855,    51,    77,   199,   200,   201,   412,   202,   413,
     203,   414,   204,   418,   205,   417,   161,   389,   615,   207,
     208,   162,   390,   738,   739,   740,   864,   959,   960,   163,
     385,    59,    81,   730,   731,   732,   858,    61,    82,   275,
     276,   277,   278,   279,   280,   281,   442,   282,   446,   283,
     445,   284,   285,   447,   286,   164,   386,   734,   735,   736,
     861,    63,    83,   296,   297,   298,   299,   300,   451,   301,
     302,   303,   304,   210,   410,   812,   813,   814,   907,    53,
      78,   221,   222,   223,   422,   165,   387,   166,   388,   213,
     411,   816,   817,   818,   910,    55,    79,   237,   238,   239,
     425,   240,   241,   427,   242,   243,   167,   396,   763,   764,
     765,   878,    57,    80,   255,   256,   257,   258,   433,   259,
     434,   260,   435,   261,   436,   262,   437,   263,   438,   264,
     432,   215,   419,   821,   822,   913,   168,   395,   760,   761,
     875,   977,   978,   979,   980,   981,  1043,   982,   169,   399,
     793,   794,   795,   892,  1052,   796,   797,   893,   798,   799,
     170,   171,   401,   805,   806,   807,   899,   808,   900,   172,
     402,   173,   403,    67,    85,   332,   333,   334,   335,   461,
     336,   462,   337,   338,   464,   339,   340,   341,   467,   662,
     342,   468,   343,   344,   345,   471,   669,   346,   472,   347,
     473,   348,   474,   104,   366,   105,   367,   106,   368,   174,
     373,    71,    87,   355,   356,   357,   480,   358,   107,   365,
      69,    86,   350,   351,   352,   477,   824,   825,   915,  1018,
    1019,  1020,  1021,  1062,  1022,  1060,  1077,  1078,  1079,  1086,
    1087,  1088,  1093,  1089,  1090,  1091
  };

  const unsigned short
  Dhcp6Parser::yytable_[] =
  {
     100,   140,   177,   194,   217,   231,   251,   294,   273,   292,
     309,   329,   274,   293,   295,   195,   790,   214,   182,   211,
     224,   235,   253,   750,   287,   305,   720,   330,   952,   953,
     954,   196,   197,   958,   198,   206,   964,    94,   175,   176,
     660,   661,   218,   232,   245,   741,   219,   233,   608,   307,
     308,   819,   183,   212,   225,   236,   254,    32,   288,   306,
      40,   331,   266,   608,   636,   267,   209,   220,   234,   252,
      33,    44,    34,    46,    35,    48,   642,   643,   644,    91,
     108,   109,   123,   124,   110,   307,   308,   111,   112,   113,
     122,   123,   124,   267,    50,   268,   269,   370,    52,   270,
     271,   272,   371,   226,   227,   228,   229,   230,   123,   124,
     123,   124,   114,   115,   116,   117,   118,   119,   120,   121,
     122,    99,   867,   122,   742,   868,   404,   191,   122,   267,
     192,   405,  1082,    54,   216,  1083,  1084,  1085,   123,   124,
      56,   123,   124,   408,   420,   125,   123,   124,   409,   421,
     126,   127,   128,   129,   130,    58,   131,   353,   354,   784,
     191,   132,  1011,   192,  1012,  1013,   970,   971,   685,   870,
     133,    60,   871,   134,    95,   664,   665,   666,   667,   876,
     135,   423,   877,    96,    97,    98,   424,    99,   136,   137,
     430,    62,   138,   139,   458,   431,    99,   123,   124,   459,
     916,    99,    64,   917,   952,   953,   954,   123,   124,   958,
      66,   668,   964,    99,   680,    99,  1049,  1050,  1051,   681,
     682,   683,   684,   685,   686,   687,   688,   689,   690,   691,
     692,   693,   694,   695,   696,   697,    68,    70,   121,    36,
      37,    38,    39,    99,   349,   267,    99,   122,   359,   800,
     801,    99,   360,   785,   786,   787,   788,   770,   771,   772,
     773,   774,   775,   475,   478,   123,   124,   482,   476,   479,
     404,   362,   483,   361,   750,   827,   938,   114,   115,   116,
     117,   478,   482,   244,   363,   122,   828,   829,   790,   245,
     246,   247,   248,   249,   250,   184,   100,   185,   611,   612,
     613,   614,    99,   123,   124,   186,   187,   188,   189,   190,
     125,   369,    99,   378,   267,   289,   268,   269,   290,   291,
     379,   380,   191,   408,   849,   192,   132,   381,   830,   850,
     140,   123,   124,   193,   177,   849,   873,   890,   897,   901,
     851,   874,   891,   898,   902,   382,   194,   475,   849,   217,
     182,   400,   903,  1036,   420,   440,   231,   407,   195,  1037,
     214,   415,   211,  1040,   458,   224,   251,    99,  1041,  1048,
      99,   416,   235,   426,   196,   197,   273,   198,   206,   294,
     274,   292,   253,   423,   183,   293,   295,   218,  1057,   428,
     430,   219,   287,   450,   232,  1058,   212,   305,   233,   225,
    1063,   329,  1097,   484,   485,  1064,   236,  1098,    99,   209,
     741,   748,   220,   749,   429,  1080,   254,   330,  1081,   234,
    1024,  1025,  1026,  1027,   439,   441,   288,   444,   448,   252,
     449,   306,   114,   115,   116,   117,    99,   452,   120,   453,
     122,   267,   454,   455,   123,   124,   460,   463,   465,   466,
     469,   331,   470,   481,   486,   487,   488,   489,   123,   124,
     490,   187,   188,   491,   190,   125,   493,   494,   495,   496,
     497,   498,   499,   500,   501,   502,   503,   191,   504,   505,
     192,   506,   507,   508,   509,   510,   511,   512,   193,   513,
     514,   515,   516,   517,   518,   519,   520,   521,   522,   523,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   524,   526,   527,   529,   530,   531,   140,
     327,   328,   532,   533,   534,   535,   177,   536,   537,   538,
     540,   542,   595,   596,   597,   544,   548,   543,   545,   546,
     549,   550,   182,   551,   552,   553,   554,   556,   557,    99,
     559,   789,   802,   558,   329,   560,   561,   564,   562,   565,
     566,   568,   569,    99,   572,   571,   573,   791,   803,   574,
     330,   575,   578,   579,   582,   576,   183,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,   580,   583,   577,   584,   585,   581,   587,   589,
     590,   792,   804,   592,   331,   593,   598,   594,   599,   600,
     601,   602,   656,   603,   605,   604,   606,   607,   854,   616,
      34,   610,   617,   618,   619,   857,   621,   620,   622,   623,
     923,   633,   624,   625,   626,   675,   628,   629,   631,   632,
     673,   674,   634,   635,   637,   638,   639,   640,   663,   721,
     641,   725,   729,   733,   737,   759,   762,   755,   645,   766,
     811,   815,   823,   835,   836,   837,   838,   646,   839,   841,
     647,   648,   649,   650,   651,   652,   653,   654,   655,   657,
     658,   659,   842,   846,   847,   670,   848,   853,   884,   671,
     672,   856,   859,   860,   862,   863,   866,   865,   924,   880,
     869,   879,   883,   882,   885,   886,   887,   888,   889,   894,
     895,   896,   904,   909,   908,   911,   912,  1005,   918,   914,
     919,   920,   921,   922,   925,   926,   928,   931,   932,   927,
     929,   930,   933,   968,   934,   995,   935,   996,  1001,   988,
     936,   989,  1002,  1004,  1010,  1044,  1046,   990,   991,   992,
     993,   997,   998,   999,  1029,  1030,  1031,  1032,  1033,  1034,
    1035,  1038,  1039,  1045,  1042,  1047,  1061,  1053,  1066,  1069,
    1054,  1055,  1071,  1076,  1074,  1094,  1095,  1096,  1099,  1056,
    1059,   194,  1070,   747,   273,   294,   679,   292,   274,   627,
     946,   293,   295,   195,   951,   214,   492,   211,   676,   525,
     287,   972,   947,   305,   251,   973,   962,   309,  1067,   196,
     197,  1073,   198,   206,  1075,  1104,  1100,   975,   948,   949,
     253,   950,   957,   789,   826,  1101,  1102,   802,   955,   528,
     966,   212,   956,   217,   288,   939,   231,   306,   969,   791,
     963,  1014,   937,   803,   209,  1015,   994,   967,   941,   224,
     987,   976,   235,   961,   254,   986,   940,  1016,   539,   570,
     965,  1065,   265,   943,   974,   942,   567,   252,   945,   944,
    1007,   218,  1009,   792,   232,   219,  1006,   804,   233,   563,
    1008,   541,   985,   225,   547,   820,   236,   984,   983,  1068,
     555,  1017,  1000,  1003,   678,   591,   220,   677,   809,   234,
    1023,  1072,   586,  1092,  1103,     0,   588,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   946,     0,     0,     0,
     951,     0,   972,     0,     0,     0,   973,     0,   947,     0,
       0,     0,   962,     0,     0,     0,     0,     0,   975,  1014,
       0,     0,     0,  1015,   948,   949,     0,   950,   957,     0,
       0,     0,     0,     0,   955,  1016,     0,     0,   956,     0,
       0,     0,     0,     0,     0,     0,   963,     0,     0,     0,
       0,     0,   976,     0,     0,     0,     0,     0,     0,   961,
       0,     0,     0,     0,     0,   974,     0,     0,     0,  1017
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    83,    82,    83,
      84,    85,    82,    83,    83,    77,   625,    77,    76,    77,
      78,    79,    80,   619,    82,    83,   602,    85,   864,   864,
     864,    77,    77,   864,    77,    77,   864,    10,    16,    17,
     138,   139,    78,    79,    93,    95,    78,    79,   508,   102,
     103,   100,    76,    77,    78,    79,    80,     0,    82,    83,
      17,    85,    21,   523,   536,    52,    77,    78,    79,    80,
       5,     7,     7,     7,     9,     7,   548,   549,   550,   174,
      11,    12,    69,    70,    15,   102,   103,    18,    19,    20,
      51,    69,    70,    52,     7,    54,    55,     3,     7,    58,
      59,    60,     8,    64,    65,    66,    67,    68,    69,    70,
      69,    70,    43,    44,    45,    46,    47,    48,    49,    50,
      51,   174,     3,    51,   174,     6,     3,    88,    51,    52,
      91,     8,   150,     7,    62,   153,   154,   155,    69,    70,
       7,    69,    70,     3,     3,    76,    69,    70,     8,     8,
      81,    82,    83,    84,    85,     7,    87,    13,    14,    21,
      88,    92,   149,    91,   151,   152,    89,    90,    30,     3,
     101,     7,     6,   104,   147,   141,   142,   143,   144,     3,
     111,     3,     6,   156,   157,   158,     8,   174,   119,   120,
       3,     7,   123,   124,     3,     8,   174,    69,    70,     8,
       3,   174,     7,     6,  1040,  1040,  1040,    69,    70,  1040,
       7,   177,  1040,   174,    21,   174,   112,   113,   114,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,     7,     7,    50,   174,
     175,   176,   177,   174,   148,    52,   174,    51,     6,   121,
     122,   174,     3,   115,   116,   117,   118,   105,   106,   107,
     108,   109,   110,     3,     3,    69,    70,     3,     8,     8,
       3,     8,     8,     4,   870,     8,   852,    43,    44,    45,
      46,     3,     3,    87,     3,    51,     8,     8,   897,    93,
      94,    95,    96,    97,    98,    61,   370,    63,    77,    78,
      79,    80,   174,    69,    70,    71,    72,    73,    74,    75,
      76,     4,   174,     4,    52,    53,    54,    55,    56,    57,
       4,     4,    88,     3,     3,    91,    92,     4,     8,     8,
     404,    69,    70,    99,   408,     3,     3,     3,     3,     3,
       8,     8,     8,     8,     8,     4,   420,     3,     3,   423,
     408,     4,     8,     8,     3,     3,   430,     4,   420,     8,
     420,     4,   420,     3,     3,   423,   440,   174,     8,     8,
     174,     4,   430,     4,   420,   420,   450,   420,   420,   455,
     450,   455,   440,     3,   408,   455,   455,   423,     8,     4,
       3,   423,   450,     3,   430,     8,   420,   455,   430,   423,
       3,   475,     3,   360,   361,     8,   430,     8,   174,   420,
      95,    96,   423,    98,     4,     3,   440,   475,     6,   430,
      22,    23,    24,    25,     8,     8,   450,     4,     4,   440,
       8,   455,    43,    44,    45,    46,   174,     4,    49,     4,
      51,    52,     8,     3,    69,    70,     4,     4,     4,     4,
       4,   475,     4,     4,   174,     4,     4,     4,    69,    70,
       4,    72,    73,     4,    75,    76,     4,     4,     4,     4,
       4,     4,   175,   175,   175,   175,   175,    88,     4,     4,
      91,     4,     4,     4,     4,     4,     4,     4,    99,     4,
       4,     4,     4,     4,     4,     4,     4,   175,     4,     4,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,     4,     4,   177,     4,     4,     4,   593,
     145,   146,     4,     4,   175,   177,   600,     4,     4,     4,
       4,     4,   489,   490,   491,     4,     4,   175,   175,   175,
       4,     4,   600,     4,     4,     4,     4,     4,     4,   174,
       4,   625,   626,   175,   628,     4,     4,     4,   177,   177,
     177,     4,     4,   174,     4,   177,     4,   625,   626,   175,
     628,     4,     4,     4,     4,   175,   600,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   177,     4,   175,     4,     4,   177,     4,     4,
     175,   625,   626,     4,   628,     7,   174,     7,     7,     7,
       7,     7,   569,     5,     5,   174,     5,     5,     3,     5,
       7,   174,     5,     5,     5,     3,     5,     7,     5,     5,
     175,   174,     7,     7,     7,   592,     7,     5,     5,     5,
       5,     5,   174,   174,   174,     7,   174,   174,   140,     7,
     174,     7,     7,     7,     7,     7,     7,    86,   174,     7,
       7,     7,     7,     4,     4,     4,     4,   174,     4,     4,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,     4,     4,     4,   174,     4,     6,     4,   174,
     174,     6,     6,     3,     6,     3,     3,     6,   177,     3,
       6,     6,     3,     6,     4,     4,     4,     4,     4,     4,
       4,     4,   174,     3,     6,     6,     3,     3,     6,     8,
       4,     4,     4,     4,   175,   177,     4,     4,     4,   175,
     175,   175,     4,     4,   175,     4,   175,     4,     4,   175,
     177,   175,     4,     6,     4,     4,     3,   175,   175,   175,
     175,   175,   175,   175,   174,   174,   174,   174,   174,   174,
     174,     8,     8,     8,   174,     8,     4,   174,     4,     4,
     174,   174,     4,     7,     5,     4,     4,     4,     4,   174,
     174,   855,   175,   618,   858,   861,   600,   861,   858,   523,
     864,   861,   861,   855,   864,   855,   370,   855,   593,   404,
     858,   875,   864,   861,   878,   875,   864,   881,   177,   855,
     855,   174,   855,   855,   174,   174,   177,   875,   864,   864,
     878,   864,   864,   897,   674,   175,   175,   901,   864,   408,
     867,   855,   864,   907,   858,   854,   910,   861,   873,   897,
     864,   915,   849,   901,   855,   915,   890,   870,   857,   907,
     883,   875,   910,   864,   878,   881,   855,   915,   420,   458,
     866,  1040,    81,   860,   875,   858,   455,   878,   863,   861,
     909,   907,   912,   897,   910,   907,   907,   901,   910,   450,
     910,   423,   880,   907,   430,   638,   910,   878,   876,  1046,
     440,   915,   897,   901,   599,   482,   907,   594,   628,   910,
     916,  1063,   475,  1080,  1097,    -1,   478,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1040,    -1,    -1,    -1,
    1040,    -1,  1046,    -1,    -1,    -1,  1046,    -1,  1040,    -1,
      -1,    -1,  1040,    -1,    -1,    -1,    -1,    -1,  1046,  1063,
      -1,    -1,    -1,  1063,  1040,  1040,    -1,  1040,  1040,    -1,
      -1,    -1,    -1,    -1,  1040,  1063,    -1,    -1,  1040,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1040,    -1,    -1,    -1,
      -1,    -1,  1046,    -1,    -1,    -1,    -1,    -1,    -1,  1040,
      -1,    -1,    -1,    -1,    -1,  1046,    -1,    -1,    -1,  1063
  };

  const unsigned short
  Dhcp6Parser::yystos_[] =
  {
       0,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,     0,     5,     7,     9,   174,   175,   176,   177,
     195,   196,   197,   202,     7,   211,     7,   217,     7,   232,
       7,   330,     7,   407,     7,   423,     7,   440,     7,   359,
       7,   365,     7,   389,     7,   306,     7,   501,     7,   548,
       7,   539,   203,   198,   212,   218,   233,   331,   408,   424,
     441,   360,   366,   390,   307,   502,   549,   540,   195,   204,
     205,   174,   200,   201,    10,   147,   156,   157,   158,   174,
     210,   213,   214,   215,   531,   533,   535,   546,    11,    12,
      15,    18,    19,    20,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    69,    70,    76,    81,    82,    83,    84,
      85,    87,    92,   101,   104,   111,   119,   120,   123,   124,
     210,   219,   220,   221,   223,   224,   225,   226,   227,   228,
     230,   239,   241,   243,   280,   286,   292,   298,   300,   314,
     324,   344,   349,   357,   383,   413,   415,   434,   464,   476,
     488,   489,   497,   499,   537,    16,    17,   210,   234,   235,
     236,   238,   413,   415,    61,    63,    71,    72,    73,    74,
      75,    88,    91,    99,   210,   223,   224,   225,   226,   332,
     333,   334,   336,   338,   340,   342,   344,   347,   348,   383,
     401,   413,   415,   417,   434,   459,    62,   210,   340,   342,
     383,   409,   410,   411,   413,   415,    64,    65,    66,    67,
      68,   210,   340,   342,   383,   413,   415,   425,   426,   427,
     429,   430,   432,   433,    87,    93,    94,    95,    96,    97,
      98,   210,   383,   413,   415,   442,   443,   444,   445,   447,
     449,   451,   453,   455,   457,   357,    21,    52,    54,    55,
      58,    59,    60,   210,   261,   367,   368,   369,   370,   371,
     372,   373,   375,   377,   379,   380,   382,   413,   415,    53,
      56,    57,   210,   261,   371,   377,   391,   392,   393,   394,
     395,   397,   398,   399,   400,   413,   415,   102,   103,   210,
     308,   309,   310,   312,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   145,   146,   210,
     413,   415,   503,   504,   505,   506,   508,   510,   511,   513,
     514,   515,   518,   520,   521,   522,   525,   527,   529,   148,
     550,   551,   552,    13,    14,   541,   542,   543,   545,     6,
       3,     4,     8,     3,   216,   547,   532,   534,   536,     4,
       3,     8,   222,   538,   231,   240,   242,   244,     4,     4,
       4,     4,     4,   229,   325,   358,   384,   414,   416,   345,
     350,   287,   299,   293,   281,   465,   435,   301,   315,   477,
       4,   490,   498,   500,     3,     8,   237,     4,     3,     8,
     402,   418,   335,   337,   339,     4,     4,   343,   341,   460,
       3,     8,   412,     3,     8,   428,     4,   431,     4,     4,
       3,     8,   458,   446,   448,   450,   452,   454,   456,     8,
       3,     8,   374,   262,     4,   378,   376,   381,     4,     8,
       3,   396,     4,     4,     8,     3,   311,   313,     3,     8,
       4,   507,   509,     4,   512,     4,     4,   516,   519,     4,
       4,   523,   526,   528,   530,     3,     8,   553,     3,     8,
     544,     4,     3,     8,   195,   195,   174,     4,     4,     4,
       4,     4,   214,     4,     4,     4,     4,     4,     4,   175,
     175,   175,   175,   175,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   175,     4,     4,     4,   220,     4,   177,   235,     4,
       4,     4,     4,     4,   175,   177,     4,     4,     4,   333,
       4,   410,     4,   175,     4,   175,   175,   426,     4,     4,
       4,     4,     4,     4,     4,   444,     4,     4,   175,     4,
       4,     4,   177,   369,     4,   177,   177,   393,     4,     4,
     309,   177,     4,     4,   175,     4,   175,   175,     4,     4,
     177,   177,     4,     4,     4,     4,   504,     4,   551,     4,
     175,   542,     4,     7,     7,   195,   195,   195,   174,     7,
       7,     7,     7,     5,   174,     5,     5,     5,   197,   199,
     174,    77,    78,    79,    80,   346,     5,     5,     5,     5,
       7,     5,     5,     5,     7,     7,     7,   199,     7,     5,
     206,     5,     5,   174,   174,   174,   206,   174,     7,   174,
     174,   174,   206,   206,   206,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   195,   174,   174,   174,
     138,   139,   517,   140,   141,   142,   143,   144,   177,   524,
     174,   174,   174,     5,     5,   195,   219,   550,   541,   234,
      21,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,   210,   249,
     250,   251,   254,   256,   258,   260,   261,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   273,   274,   276,   278,
     249,     7,   245,   246,   247,     7,   326,   327,   328,     7,
     361,   362,   363,     7,   385,   386,   387,     7,   351,   352,
     353,    95,   174,   288,   289,   290,   291,   204,    96,    98,
     290,   294,   295,   296,   297,    86,   282,   283,   284,     7,
     466,   467,     7,   436,   437,   438,     7,   302,   303,   304,
     105,   106,   107,   108,   109,   110,   316,   317,   318,   319,
     320,   321,   322,   323,    21,   115,   116,   117,   118,   210,
     263,   413,   415,   478,   479,   480,   483,   484,   486,   487,
     121,   122,   210,   413,   415,   491,   492,   493,   495,   503,
     207,     7,   403,   404,   405,     7,   419,   420,   421,   100,
     445,   461,   462,     7,   554,   555,   245,     8,     8,     8,
       8,   252,   255,   257,   259,     4,     4,     4,     4,     4,
     272,     4,     4,   275,   277,   279,     4,     4,     4,     3,
       8,     8,   248,     6,     3,   329,     6,     3,   364,     6,
       3,   388,     6,     3,   354,     6,     3,     3,     6,     6,
       3,     6,   285,     3,     8,   468,     3,     6,   439,     6,
       3,   305,     6,     3,     4,     4,     4,     4,     4,     4,
       3,     8,   481,   485,     4,     4,     4,     3,     8,   494,
     496,     3,     8,     8,   174,   208,   209,   406,     6,     3,
     422,     6,     3,   463,     8,   556,     3,     6,     6,     4,
       4,     4,     4,   175,   177,   175,   177,   175,     4,   175,
     175,     4,     4,     4,   175,   175,   177,   250,   249,   247,
     332,   328,   367,   363,   391,   387,   210,   223,   224,   225,
     226,   261,   324,   336,   338,   340,   342,   344,   348,   355,
     356,   383,   413,   415,   459,   353,   289,   295,     4,   283,
      89,    90,   210,   261,   383,   413,   415,   469,   470,   471,
     472,   473,   475,   467,   442,   438,   308,   304,   175,   175,
     175,   175,   175,   175,   317,     4,     4,   175,   175,   175,
     479,     4,     4,   492,     6,     3,   409,   405,   425,   421,
       4,   149,   151,   152,   210,   261,   413,   415,   557,   558,
     559,   560,   562,   555,    22,    23,    24,    25,   253,   174,
     174,   174,   174,   174,   174,   174,     8,     8,     8,     8,
       3,     8,   174,   474,     4,     8,     3,     8,     8,   112,
     113,   114,   482,   174,   174,   174,   174,     8,     8,   174,
     563,     4,   561,     3,     8,   356,     4,   177,   471,     4,
     175,     4,   558,   174,     5,   174,     7,   564,   565,   566,
       3,     6,   150,   153,   154,   155,   567,   568,   569,   571,
     572,   573,   565,   570,     4,     4,     4,     3,     8,     4,
     177,   175,   175,   568,   174
  };

  const unsigned short
  Dhcp6Parser::yyr1_[] =
  {
       0,   178,   180,   179,   181,   179,   182,   179,   183,   179,
     184,   179,   185,   179,   186,   179,   187,   179,   188,   179,
     189,   179,   190,   179,   191,   179,   192,   179,   193,   179,
     194,   179,   195,   195,   195,   195,   195,   195,   195,   196,
     198,   197,   199,   200,   200,   201,   201,   203,   202,   204,
     204,   205,   205,   207,   206,   208,   208,   209,   209,   210,
     212,   211,   213,   213,   214,   214,   214,   214,   214,   214,
     216,   215,   218,   217,   219,   219,   220,   220,   220,   220,
     220,   220,   220,   220,   220,   220,   220,   220,   220,   220,
     220,   220,   220,   220,   220,   220,   220,   220,   220,   220,
     220,   220,   220,   220,   220,   220,   220,   220,   220,   222,
     221,   223,   224,   225,   226,   227,   229,   228,   231,   230,
     233,   232,   234,   234,   235,   235,   235,   235,   235,   237,
     236,   238,   240,   239,   242,   241,   244,   243,   245,   245,
     246,   246,   248,   247,   249,   249,   250,   250,   250,   250,
     250,   250,   250,   250,   250,   250,   250,   250,   250,   250,
     250,   250,   250,   250,   250,   250,   252,   251,   253,   253,
     253,   253,   255,   254,   257,   256,   259,   258,   260,   262,
     261,   263,   264,   265,   266,   267,   268,   269,   270,   272,
     271,   273,   275,   274,   277,   276,   279,   278,   281,   280,
     282,   282,   283,   285,   284,   287,   286,   288,   288,   289,
     289,   290,   291,   293,   292,   294,   294,   295,   295,   295,
     296,   297,   299,   298,   301,   300,   302,   302,   303,   303,
     305,   304,   307,   306,   308,   308,   308,   309,   309,   311,
     310,   313,   312,   315,   314,   316,   316,   317,   317,   317,
     317,   317,   317,   318,   319,   320,   321,   322,   323,   325,
     324,   326,   326,   327,   327,   329,   328,   331,   330,   332,
     332,   333,   333,   333,   333,   333,   333,   333,   333,   333,
     333,   333,   333,   333,   333,   333,   333,   333,   333,   333,
     333,   335,   334,   337,   336,   339,   338,   341,   340,   343,
     342,   345,   344,   346,   346,   346,   346,   347,   348,   350,
     349,   351,   351,   352,   352,   354,   353,   355,   355,   356,
     356,   356,   356,   356,   356,   356,   356,   356,   356,   356,
     356,   356,   356,   356,   356,   356,   358,   357,   360,   359,
     361,   361,   362,   362,   364,   363,   366,   365,   367,   367,
     368,   368,   369,   369,   369,   369,   369,   369,   369,   369,
     369,   369,   370,   371,   372,   374,   373,   376,   375,   378,
     377,   379,   381,   380,   382,   384,   383,   385,   385,   386,
     386,   388,   387,   390,   389,   391,   391,   392,   392,   393,
     393,   393,   393,   393,   393,   393,   393,   393,   394,   396,
     395,   397,   398,   399,   400,   402,   401,   403,   403,   404,
     404,   406,   405,   408,   407,   409,   409,   410,   410,   410,
     410,   410,   410,   410,   412,   411,   414,   413,   416,   415,
     418,   417,   419,   419,   420,   420,   422,   421,   424,   423,
     425,   425,   426,   426,   426,   426,   426,   426,   426,   426,
     426,   426,   426,   428,   427,   429,   431,   430,   432,   433,
     435,   434,   436,   436,   437,   437,   439,   438,   441,   440,
     442,   442,   443,   443,   444,   444,   444,   444,   444,   444,
     444,   444,   444,   444,   444,   446,   445,   448,   447,   450,
     449,   452,   451,   454,   453,   456,   455,   458,   457,   460,
     459,   461,   461,   463,   462,   465,   464,   466,   466,   468,
     467,   469,   469,   470,   470,   471,   471,   471,   471,   471,
     471,   471,   472,   474,   473,   475,   477,   476,   478,   478,
     479,   479,   479,   479,   479,   479,   479,   479,   479,   481,
     480,   482,   482,   482,   483,   485,   484,   486,   487,   488,
     490,   489,   491,   491,   492,   492,   492,   492,   492,   494,
     493,   496,   495,   498,   497,   500,   499,   502,   501,   503,
     503,   504,   504,   504,   504,   504,   504,   504,   504,   504,
     504,   504,   504,   504,   504,   504,   504,   504,   504,   505,
     507,   506,   509,   508,   510,   512,   511,   513,   514,   516,
     515,   517,   517,   519,   518,   520,   521,   523,   522,   524,
     524,   524,   524,   524,   526,   525,   528,   527,   530,   529,
     532,   531,   534,   533,   536,   535,   538,   537,   540,   539,
     541,   541,   542,   542,   544,   543,   545,   547,   546,   549,
     548,   550,   550,   551,   553,   552,   554,   554,   556,   555,
     557,   557,   558,   558,   558,   558,   558,   558,   558,   559,
     561,   560,   563,   562,   564,   564,   566,   565,   567,   567,
     568,   568,   568,   568,   570,   569,   571,   572,   573
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     3,     3,     3,     3,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     6,     0,     6,     0,     6,     0,     1,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     0,
       4,     3,     0,     4,     0,     4,     0,     4,     0,     6,
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
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     0,     6,     3,     0,     6,     0,
       4,     1,     3,     1,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     0,     4,     3,     3,     3
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
  "\"tcp-nodelay\"", "\"preferred-lifetime\"", "\"valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"decline-probation-period\"",
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
  "$@21", "global_params", "global_param", "data_directory", "$@22",
  "preferred_lifetime", "valid_lifetime", "renew_timer", "rebind_timer",
  "decline_probation_period", "server_tag", "$@23", "interfaces_config",
  "$@24", "sub_interfaces6", "$@25", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@26", "re_detect",
  "lease_database", "$@27", "hosts_database", "$@28", "hosts_databases",
  "$@29", "database_list", "not_empty_database_list", "database", "$@30",
  "database_map_params", "database_map_param", "database_type", "$@31",
  "db_type", "user", "$@32", "password", "$@33", "host", "$@34", "port",
  "name", "$@35", "persist", "lfc_interval", "readonly", "connect_timeout",
  "reconnect_wait_time", "request_timeout", "tcp_keepalive", "tcp_nodelay",
  "contact_points", "$@36", "max_reconnect_tries", "keyspace", "$@37",
  "consistency", "$@38", "serial_consistency", "$@39", "sanity_checks",
  "$@40", "sanity_checks_params", "sanity_checks_param", "lease_checks",
  "$@41", "mac_sources", "$@42", "mac_sources_list", "mac_sources_value",
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
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short
  Dhcp6Parser::yyrline_[] =
  {
       0,   262,   262,   262,   263,   263,   264,   264,   265,   265,
     266,   266,   267,   267,   268,   268,   269,   269,   270,   270,
     271,   271,   272,   272,   273,   273,   274,   274,   275,   275,
     276,   276,   284,   285,   286,   287,   288,   289,   290,   293,
     298,   298,   309,   312,   313,   316,   320,   327,   327,   334,
     335,   338,   342,   349,   349,   356,   357,   360,   364,   375,
     385,   385,   400,   401,   405,   406,   407,   408,   409,   410,
     413,   413,   428,   428,   437,   438,   443,   444,   445,   446,
     447,   448,   449,   450,   451,   452,   453,   454,   455,   456,
     457,   458,   459,   460,   461,   462,   463,   464,   465,   466,
     467,   468,   469,   470,   471,   472,   473,   474,   475,   478,
     478,   486,   491,   496,   501,   506,   511,   511,   519,   519,
     530,   530,   539,   540,   543,   544,   545,   546,   547,   550,
     550,   560,   566,   566,   578,   578,   590,   590,   600,   601,
     604,   605,   608,   608,   618,   619,   622,   623,   624,   625,
     626,   627,   628,   629,   630,   631,   632,   633,   634,   635,
     636,   637,   638,   639,   640,   641,   644,   644,   651,   652,
     653,   654,   657,   657,   665,   665,   673,   673,   681,   686,
     686,   694,   699,   704,   709,   714,   719,   724,   729,   734,
     734,   742,   747,   747,   755,   755,   763,   763,   771,   771,
     781,   782,   784,   786,   786,   804,   804,   814,   815,   818,
     819,   822,   827,   832,   832,   842,   843,   846,   847,   848,
     851,   856,   863,   863,   873,   873,   883,   884,   887,   888,
     891,   891,   901,   901,   911,   912,   913,   916,   917,   920,
     920,   928,   928,   936,   936,   947,   948,   951,   952,   953,
     954,   955,   956,   959,   964,   969,   974,   979,   984,   992,
     992,  1005,  1006,  1009,  1010,  1017,  1017,  1043,  1043,  1054,
    1055,  1059,  1060,  1061,  1062,  1063,  1064,  1065,  1066,  1067,
    1068,  1069,  1070,  1071,  1072,  1073,  1074,  1075,  1076,  1077,
    1078,  1081,  1081,  1089,  1089,  1097,  1097,  1105,  1105,  1113,
    1113,  1123,  1123,  1130,  1131,  1132,  1133,  1136,  1141,  1149,
    1149,  1160,  1161,  1165,  1166,  1169,  1169,  1177,  1178,  1181,
    1182,  1183,  1184,  1185,  1186,  1187,  1188,  1189,  1190,  1191,
    1192,  1193,  1194,  1195,  1196,  1197,  1204,  1204,  1217,  1217,
    1226,  1227,  1230,  1231,  1236,  1236,  1251,  1251,  1265,  1266,
    1269,  1270,  1273,  1274,  1275,  1276,  1277,  1278,  1279,  1280,
    1281,  1282,  1285,  1287,  1292,  1294,  1294,  1302,  1302,  1310,
    1310,  1318,  1320,  1320,  1328,  1337,  1337,  1349,  1350,  1355,
    1356,  1361,  1361,  1373,  1373,  1385,  1386,  1391,  1392,  1397,
    1398,  1399,  1400,  1401,  1402,  1403,  1404,  1405,  1408,  1410,
    1410,  1418,  1420,  1422,  1427,  1435,  1435,  1447,  1448,  1451,
    1452,  1455,  1455,  1465,  1465,  1474,  1475,  1478,  1479,  1480,
    1481,  1482,  1483,  1484,  1487,  1487,  1495,  1495,  1520,  1520,
    1550,  1550,  1562,  1563,  1566,  1567,  1570,  1570,  1582,  1582,
    1594,  1595,  1598,  1599,  1600,  1601,  1602,  1603,  1604,  1605,
    1606,  1607,  1608,  1611,  1611,  1619,  1624,  1624,  1632,  1637,
    1645,  1645,  1655,  1656,  1659,  1660,  1663,  1663,  1672,  1672,
    1681,  1682,  1685,  1686,  1690,  1691,  1692,  1693,  1694,  1695,
    1696,  1697,  1698,  1699,  1700,  1703,  1703,  1713,  1713,  1723,
    1723,  1731,  1731,  1739,  1739,  1747,  1747,  1755,  1755,  1768,
    1768,  1778,  1779,  1782,  1782,  1793,  1793,  1803,  1804,  1807,
    1807,  1817,  1818,  1821,  1822,  1825,  1826,  1827,  1828,  1829,
    1830,  1831,  1834,  1836,  1836,  1844,  1852,  1852,  1864,  1865,
    1868,  1869,  1870,  1871,  1872,  1873,  1874,  1875,  1876,  1879,
    1879,  1886,  1887,  1888,  1891,  1896,  1896,  1904,  1909,  1916,
    1923,  1923,  1933,  1934,  1937,  1938,  1939,  1940,  1941,  1944,
    1944,  1952,  1952,  1962,  1962,  2002,  2002,  2014,  2014,  2024,
    2025,  2028,  2029,  2030,  2031,  2032,  2033,  2034,  2035,  2036,
    2037,  2038,  2039,  2040,  2041,  2042,  2043,  2044,  2045,  2048,
    2053,  2053,  2061,  2061,  2069,  2074,  2074,  2082,  2087,  2092,
    2092,  2100,  2101,  2104,  2104,  2112,  2117,  2122,  2122,  2130,
    2133,  2136,  2139,  2142,  2148,  2148,  2156,  2156,  2164,  2164,
    2174,  2174,  2181,  2181,  2188,  2188,  2197,  2197,  2208,  2208,
    2218,  2219,  2223,  2224,  2227,  2227,  2237,  2247,  2247,  2257,
    2257,  2268,  2269,  2273,  2277,  2277,  2289,  2290,  2294,  2294,
    2302,  2303,  2306,  2307,  2308,  2309,  2310,  2311,  2312,  2315,
    2320,  2320,  2328,  2328,  2338,  2339,  2342,  2342,  2350,  2351,
    2354,  2355,  2356,  2357,  2360,  2360,  2368,  2373,  2378
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
#line 5135 "dhcp6_parser.cc" // lalr1.cc:1218
#line 2383 "dhcp6_parser.yy" // lalr1.cc:1219


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
