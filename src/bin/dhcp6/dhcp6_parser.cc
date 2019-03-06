// A Bison parser, made by GNU Bison 3.3.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2019 Free Software Foundation, Inc.

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
#line 34 "dhcp6_parser.yy" // lalr1.cc:435

#include <dhcp6/parser_context.h>

#line 51 "dhcp6_parser.cc" // lalr1.cc:435


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
    while (false)
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

#line 14 "dhcp6_parser.yy" // lalr1.cc:510
namespace isc { namespace dhcp {
#line 146 "dhcp6_parser.cc" // lalr1.cc:510

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
        std::string yyr;
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
              else
                goto append;

            append:
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

  Dhcp6Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  Dhcp6Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Dhcp6Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Dhcp6Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Dhcp6Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Dhcp6Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Dhcp6Parser::symbol_number_type
  Dhcp6Parser::by_state::type_get () const YY_NOEXCEPT
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
      case 250: // db_type
      case 339: // hr_mode
      case 475: // duid_type
      case 510: // ncr_protocol_value
      case 517: // replace_client_name_value
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

#if 201103L <= YY_CPLUSPLUS
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
      case 250: // db_type
      case 339: // hr_mode
      case 475: // duid_type
      case 510: // ncr_protocol_value
      case 517: // replace_client_name_value
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

#if YY_CPLUSPLUS < 201103L
  Dhcp6Parser::stack_symbol_type&
  Dhcp6Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 192: // value
      case 196: // map_value
      case 250: // db_type
      case 339: // hr_mode
      case 475: // duid_type
      case 510: // ncr_protocol_value
      case 517: // replace_client_name_value
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
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
      case 171: // "constant string"
#line 249 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < std::string > (); }
#line 404 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 172: // "integer"
#line 249 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 410 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 173: // "floating point"
#line 249 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < double > (); }
#line 416 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 174: // "boolean"
#line 249 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < bool > (); }
#line 422 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 192: // value
#line 249 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 196: // map_value
#line 249 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 434 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 250: // db_type
#line 249 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 440 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 339: // hr_mode
#line 249 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 446 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 475: // duid_type
#line 249 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 452 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 510: // ncr_protocol_value
#line 249 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 458 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 517: // replace_client_name_value
#line 249 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 464 "dhcp6_parser.cc" // lalr1.cc:676
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
#if 201103L <= YY_CPLUSPLUS
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

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
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
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
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
  | yyreduce -- do a reduction.  |
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
      case 250: // db_type
      case 339: // hr_mode
      case 475: // duid_type
      case 510: // ncr_protocol_value
      case 517: // replace_client_name_value
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
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
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
#line 258 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 730 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 4:
#line 259 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.CONFIG; }
#line 736 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 6:
#line 260 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP6; }
#line 742 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 8:
#line 261 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 748 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 10:
#line 262 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.SUBNET6; }
#line 754 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 12:
#line 263 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.POOLS; }
#line 760 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 14:
#line 264 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 766 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 16:
#line 265 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 772 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 18:
#line 266 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP6; }
#line 778 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 20:
#line 267 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 784 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 22:
#line 268 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 790 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 24:
#line 269 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 796 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 26:
#line 270 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 802 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 28:
#line 271 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.LOGGING; }
#line 808 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 30:
#line 272 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 814 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 32:
#line 280 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 820 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 33:
#line 281 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 826 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 34:
#line 282 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 832 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 35:
#line 283 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 838 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 36:
#line 284 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 844 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 37:
#line 285 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 850 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 38:
#line 286 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 856 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 39:
#line 289 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 865 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 40:
#line 294 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 876 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 41:
#line 299 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 886 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 42:
#line 305 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 892 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 45:
#line 312 "dhcp6_parser.yy" // lalr1.cc:919
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 901 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 46:
#line 316 "dhcp6_parser.yy" // lalr1.cc:919
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 911 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 47:
#line 323 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 920 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 48:
#line 326 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // list parsing complete. Put any sanity checking here
}
#line 928 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 51:
#line 334 "dhcp6_parser.yy" // lalr1.cc:919
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 937 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 52:
#line 338 "dhcp6_parser.yy" // lalr1.cc:919
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 946 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 53:
#line 345 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // List parsing about to start
}
#line 954 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 54:
#line 347 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 963 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 57:
#line 356 "dhcp6_parser.yy" // lalr1.cc:919
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 972 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 58:
#line 360 "dhcp6_parser.yy" // lalr1.cc:919
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 981 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 59:
#line 371 "dhcp6_parser.yy" // lalr1.cc:919
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 992 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 60:
#line 381 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1003 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 61:
#line 386 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1016 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 70:
#line 409 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 1029 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 71:
#line 416 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1039 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 72:
#line 424 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1049 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 73:
#line 428 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No global parameter is required
    // parsing completed
}
#line 1058 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 109:
#line 474 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1066 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 110:
#line 476 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1076 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 111:
#line 482 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1085 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 112:
#line 487 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1094 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 113:
#line 492 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1103 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 114:
#line 497 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1112 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 115:
#line 502 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 116:
#line 507 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1129 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 117:
#line 509 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1139 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 118:
#line 515 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1150 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 119:
#line 520 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1160 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 120:
#line 526 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1170 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 121:
#line 530 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1179 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 129:
#line 546 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1190 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 130:
#line 551 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1199 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 131:
#line 556 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1208 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 132:
#line 562 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1219 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 133:
#line 567 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1230 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 134:
#line 574 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1241 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 135:
#line 579 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1252 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 136:
#line 586 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1263 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 137:
#line 591 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1272 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 142:
#line 604 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1282 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 143:
#line 608 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1292 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 164:
#line 638 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1300 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 165:
#line 640 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1309 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 166:
#line 645 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1315 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 167:
#line 646 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1321 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 168:
#line 647 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1327 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 169:
#line 648 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1333 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 170:
#line 651 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1341 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 171:
#line 653 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1351 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 172:
#line 659 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1359 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 173:
#line 661 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1369 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 174:
#line 667 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1377 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 175:
#line 669 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1387 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 176:
#line 675 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1396 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 177:
#line 680 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1404 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 178:
#line 682 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1414 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 179:
#line 688 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1423 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 180:
#line 693 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1432 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 181:
#line 698 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1441 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 182:
#line 703 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1450 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 183:
#line 708 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1459 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 184:
#line 713 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1468 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 185:
#line 718 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1477 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 186:
#line 723 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1486 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 187:
#line 728 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1494 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 188:
#line 730 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1504 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 189:
#line 736 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1513 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 190:
#line 741 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1521 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 191:
#line 743 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1531 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 192:
#line 749 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1542 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 193:
#line 754 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1551 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 197:
#line 764 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1559 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 198:
#line 766 "dhcp6_parser.yy" // lalr1.cc:919
    {

    if ( (string(yystack_[0].value.as < std::string > ()) == "none") ||
         (string(yystack_[0].value.as < std::string > ()) == "warn") ||
         (string(yystack_[0].value.as < std::string > ()) == "fix") ||
         (string(yystack_[0].value.as < std::string > ()) == "fix-del") ||
         (string(yystack_[0].value.as < std::string > ()) == "del")) {
        ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
        ctx.stack_.back()->set("lease-checks", user);
        ctx.leave();
    } else {
        error(yystack_[0].location, "Unsupported 'lease-checks value: " + string(yystack_[0].value.as < std::string > ()) +
              ", supported values are: none, warn, fix, fix-del, del");
    }
}
#line 1579 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 199:
#line 782 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1590 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 200:
#line 787 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1599 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 205:
#line 800 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1608 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 206:
#line 805 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1617 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 207:
#line 810 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1628 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 208:
#line 815 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1637 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 214:
#line 829 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1646 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 215:
#line 834 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1655 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 216:
#line 841 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1666 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 217:
#line 846 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1675 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 218:
#line 851 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1686 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 219:
#line 856 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1695 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 224:
#line 869 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1705 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 225:
#line 873 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1715 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 226:
#line 879 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1725 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 227:
#line 883 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1735 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 233:
#line 898 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1743 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 234:
#line 900 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1753 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 235:
#line 906 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1761 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 236:
#line 908 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1770 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 237:
#line 914 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1781 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 238:
#line 919 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1791 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 247:
#line 937 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1800 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 248:
#line 942 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1809 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 249:
#line 947 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1818 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 250:
#line 952 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1827 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 251:
#line 957 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1836 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 252:
#line 962 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1845 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 253:
#line 970 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1856 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 254:
#line 975 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1865 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 259:
#line 995 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1875 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 260:
#line 999 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 1901 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 261:
#line 1021 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1911 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 262:
#line 1025 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1921 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 285:
#line 1059 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1929 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 286:
#line 1061 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1939 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 287:
#line 1067 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1947 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 288:
#line 1069 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1957 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 289:
#line 1075 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1965 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 290:
#line 1077 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1975 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 291:
#line 1083 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1983 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 292:
#line 1085 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1993 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 293:
#line 1091 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2004 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 294:
#line 1096 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2013 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 295:
#line 1101 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2021 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 296:
#line 1103 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2030 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 297:
#line 1108 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2036 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 298:
#line 1109 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2042 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 299:
#line 1110 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2048 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 300:
#line 1111 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2054 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 301:
#line 1114 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2063 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 302:
#line 1119 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2072 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 303:
#line 1127 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2083 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 304:
#line 1132 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2092 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 309:
#line 1147 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2102 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 310:
#line 1151 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 2110 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 330:
#line 1182 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2121 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 331:
#line 1187 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2130 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 332:
#line 1195 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2139 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 333:
#line 1198 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 2147 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 338:
#line 1214 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2157 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 339:
#line 1218 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2169 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 340:
#line 1229 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2179 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 341:
#line 1233 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2191 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 357:
#line 1265 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2200 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 359:
#line 1272 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2208 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 360:
#line 1274 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2218 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 361:
#line 1280 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2226 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 362:
#line 1282 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2236 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 363:
#line 1288 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2244 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 364:
#line 1290 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2254 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 366:
#line 1298 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2262 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 367:
#line 1300 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2272 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 368:
#line 1306 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2281 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 369:
#line 1315 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2292 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 370:
#line 1320 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2301 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 375:
#line 1339 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2311 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 376:
#line 1343 "dhcp6_parser.yy" // lalr1.cc:919
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2320 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 377:
#line 1351 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2330 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 378:
#line 1355 "dhcp6_parser.yy" // lalr1.cc:919
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2339 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 393:
#line 1388 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2347 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 394:
#line 1390 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2357 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 397:
#line 1400 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2366 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 398:
#line 1405 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2375 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 399:
#line 1413 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2386 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 400:
#line 1418 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2395 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 405:
#line 1433 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2405 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 406:
#line 1437 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2415 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 407:
#line 1443 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2425 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 408:
#line 1447 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2434 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 418:
#line 1465 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2442 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 419:
#line 1467 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2452 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 420:
#line 1473 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2460 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 421:
#line 1475 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr parent = ctx.stack_.back();
    ElementPtr user_context = yystack_[0].value.as < ElementPtr > ();
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
#line 2487 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 422:
#line 1498 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2495 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 423:
#line 1500 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr parent = ctx.stack_.back();
    ElementPtr user_context(new MapElement(ctx.loc2pos(yystack_[3].location)));
    ElementPtr comment(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
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
#line 2524 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 424:
#line 1528 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2535 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 425:
#line 1533 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2544 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 430:
#line 1548 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2554 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 431:
#line 1552 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2566 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 432:
#line 1560 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2576 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 433:
#line 1564 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2588 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 447:
#line 1589 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2596 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 448:
#line 1591 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2606 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 449:
#line 1597 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2615 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 450:
#line 1602 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2623 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 451:
#line 1604 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2633 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 452:
#line 1610 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2642 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 453:
#line 1615 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2651 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 454:
#line 1623 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2662 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 455:
#line 1628 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2671 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 460:
#line 1641 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2681 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 461:
#line 1645 "dhcp6_parser.yy" // lalr1.cc:919
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2690 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 462:
#line 1650 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2700 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 463:
#line 1654 "dhcp6_parser.yy" // lalr1.cc:919
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2709 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 479:
#line 1681 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2720 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 480:
#line 1686 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2729 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 481:
#line 1691 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2740 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 482:
#line 1696 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2749 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 483:
#line 1701 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2757 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 484:
#line 1703 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2767 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 485:
#line 1709 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2775 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 486:
#line 1711 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2785 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 487:
#line 1717 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2793 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 488:
#line 1719 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2803 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 489:
#line 1725 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2811 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 490:
#line 1727 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2821 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 491:
#line 1733 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2832 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 492:
#line 1738 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2841 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 493:
#line 1746 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2852 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 494:
#line 1751 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2861 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 497:
#line 1760 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2869 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 498:
#line 1762 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2879 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 499:
#line 1771 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2890 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 500:
#line 1776 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2899 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 503:
#line 1785 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2909 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 504:
#line 1789 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2919 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 517:
#line 1814 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2927 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 518:
#line 1816 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2937 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 519:
#line 1822 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2946 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 520:
#line 1830 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2957 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 521:
#line 1835 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2968 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 533:
#line 1857 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2976 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 534:
#line 1859 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2985 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 535:
#line 1864 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2991 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 536:
#line 1865 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2997 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 537:
#line 1866 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3003 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 538:
#line 1869 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3012 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 539:
#line 1874 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3020 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 540:
#line 1876 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3030 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 541:
#line 1882 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3039 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 542:
#line 1887 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3048 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 543:
#line 1894 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3057 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 544:
#line 1901 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3068 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 545:
#line 1906 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3077 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 553:
#line 1922 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3085 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 554:
#line 1924 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3095 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 555:
#line 1930 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3103 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 556:
#line 1932 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3113 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 557:
#line 1940 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3121 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 558:
#line 1942 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr qc = yystack_[0].value.as < ElementPtr > ();
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
#line 3161 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 559:
#line 1980 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3172 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 560:
#line 1985 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3183 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 561:
#line 1992 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3193 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 562:
#line 1996 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3203 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 583:
#line 2026 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3212 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 584:
#line 2031 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3220 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 585:
#line 2033 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3230 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 586:
#line 2039 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3238 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 587:
#line 2041 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3248 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 588:
#line 2047 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3257 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 589:
#line 2052 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3265 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 590:
#line 2054 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3275 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 591:
#line 2060 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3284 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 592:
#line 2065 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3293 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 593:
#line 2070 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3301 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 594:
#line 2072 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3310 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 595:
#line 2078 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3316 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 596:
#line 2079 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3322 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 597:
#line 2082 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3330 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 598:
#line 2084 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3340 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 599:
#line 2090 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3349 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 600:
#line 2095 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3358 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 601:
#line 2100 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3366 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 602:
#line 2102 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3375 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 603:
#line 2108 "dhcp6_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3383 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 604:
#line 2111 "dhcp6_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3391 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 605:
#line 2114 "dhcp6_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3399 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 606:
#line 2117 "dhcp6_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3407 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 607:
#line 2120 "dhcp6_parser.yy" // lalr1.cc:919
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3416 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 608:
#line 2126 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3424 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 609:
#line 2128 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3434 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 610:
#line 2134 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3442 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 611:
#line 2136 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3452 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 612:
#line 2142 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3460 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 613:
#line 2144 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3470 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 614:
#line 2152 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3478 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 615:
#line 2154 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3487 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 616:
#line 2159 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3495 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 617:
#line 2161 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3504 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 618:
#line 2166 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3512 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 619:
#line 2168 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3521 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 620:
#line 2175 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3532 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 621:
#line 2180 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3542 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 622:
#line 2186 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3552 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 623:
#line 2190 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No config_control params are required
    // parsing completed
}
#line 3561 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 627:
#line 2204 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3572 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 628:
#line 2209 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3581 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 629:
#line 2219 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3592 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 630:
#line 2224 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3601 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 631:
#line 2229 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3611 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 632:
#line 2233 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 3619 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 636:
#line 2249 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3630 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 637:
#line 2254 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3639 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 640:
#line 2266 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3649 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 641:
#line 2270 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 3657 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 651:
#line 2287 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3666 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 652:
#line 2292 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3674 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 653:
#line 2294 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3684 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 654:
#line 2300 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3695 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 655:
#line 2305 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3704 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 658:
#line 2314 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3714 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 659:
#line 2318 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 3722 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 666:
#line 2332 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3730 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 667:
#line 2334 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3740 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 668:
#line 2340 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3749 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 669:
#line 2345 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3758 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 670:
#line 2350 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3767 "dhcp6_parser.cc" // lalr1.cc:919
    break;


#line 3771 "dhcp6_parser.cc" // lalr1.cc:919
            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
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
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

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


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
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


  const short Dhcp6Parser::yypact_ninf_ = -827;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     417,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,    44,    65,    50,    58,
      66,    70,    78,   101,   111,   118,   122,   126,   138,   147,
     158,   169,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,    65,  -120,    27,    69,    23,   237,   196,    36,
     181,   137,    71,   200,   -37,   368,    54,   174,  -827,   197,
     203,   224,   235,   242,  -827,  -827,  -827,  -827,  -827,   265,
    -827,    42,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,   296,   298,   317,   319,   323,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,   345,  -827,  -827,  -827,
    -827,    68,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,   355,  -827,   136,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,   361,
     364,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,   165,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,   185,  -827,  -827,  -827,  -827,  -827,   365,  -827,   383,
     387,  -827,  -827,  -827,  -827,  -827,  -827,   188,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,   334,   255,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,   343,  -827,  -827,   402,  -827,
    -827,  -827,   405,  -827,  -827,   408,   328,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
     414,   415,  -827,  -827,  -827,  -827,   412,   419,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
     227,  -827,  -827,  -827,   421,  -827,  -827,   422,  -827,   424,
     433,  -827,  -827,   444,   446,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,   238,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
     253,  -827,  -827,  -827,   256,  -827,  -827,  -827,    65,    65,
    -827,   252,   447,   448,   449,   450,   451,  -827,    27,  -827,
     454,   457,   460,   461,   462,   463,   297,   299,   300,   301,
     304,   464,   466,   470,   473,   475,   476,   477,   478,   479,
     480,   481,   483,   484,   485,   499,   500,   501,   336,   502,
     503,   505,    69,  -827,   508,   339,    23,  -827,   510,   512,
     513,   514,   515,   348,   349,   517,   520,   521,   237,  -827,
     522,   196,  -827,   523,   356,   528,   362,   363,    36,  -827,
     529,   532,   533,   536,   537,   538,   539,  -827,   181,  -827,
     540,   541,   374,   545,   547,   548,   379,  -827,    71,   550,
     381,   382,  -827,   200,   553,   554,   190,  -827,   386,   555,
     558,   393,   563,   396,   398,   565,   567,   416,   418,   584,
     585,   587,   589,   368,  -827,   590,    54,  -827,   591,   174,
    -827,  -827,  -827,   592,   594,   595,    65,    65,    65,  -827,
     428,   596,   597,   598,   599,   602,  -827,  -827,  -827,  -827,
    -827,   437,   605,   606,   607,   608,   442,   366,   609,   611,
     612,   613,   614,   615,   617,   618,   619,   620,  -827,   621,
     608,   622,  -827,   625,  -827,  -827,   627,   628,   453,   465,
     467,  -827,  -827,   625,   468,   630,  -827,   469,  -827,   471,
    -827,   472,  -827,  -827,  -827,   625,   625,   625,   474,   482,
     486,   487,  -827,   488,   489,  -827,   490,   491,   492,  -827,
    -827,   493,  -827,  -827,  -827,   494,    65,  -827,  -827,   495,
     496,  -827,   497,  -827,  -827,   176,   498,  -827,  -827,   -34,
     504,   506,   507,  -827,   629,  -827,   636,  -827,    65,    69,
      54,  -827,  -827,  -827,  -827,   174,    23,   184,   184,   637,
    -827,   639,   640,   641,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,   642,   -52,    65,   139,   542,   643,   644,   645,
      57,   112,    12,  -827,   368,  -827,  -827,   647,   648,  -827,
    -827,  -827,  -827,  -827,   -49,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,   649,
     637,  -827,   283,   284,   285,   293,  -827,  -827,  -827,  -827,
     665,   666,   667,   668,   669,  -827,   670,   672,  -827,   675,
     676,   677,  -827,   310,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,   311,  -827,   678,   616,  -827,  -827,   679,   680,
    -827,  -827,   681,   683,  -827,  -827,   682,   686,  -827,  -827,
     684,   688,  -827,  -827,  -827,   140,  -827,  -827,  -827,   687,
    -827,  -827,  -827,   163,  -827,  -827,  -827,  -827,   312,  -827,
    -827,  -827,   189,  -827,  -827,   689,   691,  -827,  -827,   690,
     694,  -827,   695,   696,   697,   698,   699,   700,   321,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,   701,   702,
     703,  -827,  -827,  -827,  -827,   327,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,   331,  -827,  -827,
    -827,   335,   511,  -827,   692,   705,  -827,  -827,   704,   706,
    -827,  -827,  -827,   707,  -827,  -827,   254,  -827,   708,  -827,
    -827,  -827,  -827,   709,   712,   713,   714,   549,   518,   551,
     546,   552,   715,   556,   557,   718,   559,   560,   561,   184,
    -827,  -827,   184,  -827,   637,   237,  -827,   639,    71,  -827,
     640,   200,  -827,   641,   390,  -827,   642,   -52,  -827,  -827,
     139,  -827,   721,   542,  -827,   250,   643,  -827,   181,  -827,
     644,   -37,  -827,   645,   562,   564,   566,   568,   569,   570,
      57,  -827,   722,   723,   571,   572,   573,   112,  -827,   726,
     729,    12,  -827,  -827,  -827,   731,   736,   196,  -827,   647,
      36,  -827,   648,   742,  -827,    26,   649,  -827,  -827,   423,
     576,   577,   578,  -827,  -827,  -827,  -827,  -827,   579,  -827,
    -827,   580,  -827,  -827,  -827,  -827,   337,  -827,   338,  -827,
     744,  -827,   745,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,   354,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,   583,  -827,  -827,   751,
    -827,  -827,  -827,  -827,  -827,   748,   754,  -827,  -827,  -827,
    -827,  -827,   750,  -827,   358,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,   302,   588,  -827,  -827,  -827,  -827,   593,
     601,  -827,  -827,   633,   378,  -827,   385,  -827,   634,  -827,
     756,  -827,  -827,  -827,  -827,  -827,   395,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,   390,  -827,  -827,   757,
     624,  -827,   250,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,   758,   604,   759,    26,
    -827,  -827,   635,  -827,  -827,   760,  -827,   654,  -827,  -827,
     761,  -827,  -827,   347,  -827,     5,   761,  -827,  -827,   762,
     763,   765,   397,  -827,  -827,  -827,  -827,  -827,  -827,   766,
     646,   656,   660,     5,  -827,   674,  -827,  -827,  -827,  -827,
    -827
  };

  const unsigned short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   120,     9,
     261,    11,   407,    13,   432,    15,   462,    17,   332,    19,
     340,    21,   377,    23,   226,    25,   561,    27,   631,    29,
     622,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     464,     0,   342,   379,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   629,   614,   616,   618,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   109,   620,
     118,   132,   134,   136,     0,     0,     0,     0,     0,   116,
     253,   330,   369,   420,   422,   295,   303,   199,   216,   207,
     192,   499,   454,   218,   237,   520,     0,   544,   557,   559,
     108,     0,    74,    76,    77,    78,    79,    80,    81,   106,
      84,    85,    86,    87,   103,    88,    90,    89,    94,    95,
      82,   107,    83,    92,    93,   101,   102,   104,    91,    96,
      97,    98,    99,   100,   105,   129,     0,   128,     0,   122,
     124,   125,   126,   127,   399,   424,   285,   287,   289,     0,
       0,   293,   291,   493,   284,   265,   266,   267,   268,     0,
     263,   272,   273,   274,   277,   278,   280,   275,   276,   269,
     270,   282,   283,   271,   279,   281,   418,   417,   413,   414,
     412,     0,   409,   411,   415,   416,   447,     0,   450,     0,
       0,   446,   440,   441,   439,   444,   445,     0,   434,   436,
     437,   442,   443,   438,   491,   479,   481,   483,   485,   487,
     489,   478,   475,   476,   477,     0,   465,   466,   470,   471,
     468,   472,   473,   474,   469,     0,   359,   177,     0,   363,
     361,   366,     0,   355,   356,     0,   343,   344,   346,   358,
     347,   348,   349,   365,   350,   351,   352,   353,   354,   393,
       0,     0,   391,   392,   395,   396,     0,   380,   381,   383,
     384,   385,   386,   387,   388,   389,   390,   233,   235,   230,
       0,   228,   231,   232,     0,   584,   586,     0,   589,     0,
       0,   593,   597,     0,     0,   601,   608,   610,   612,   582,
     580,   581,     0,   563,   565,   566,   567,   568,   569,   570,
     571,   572,   573,   574,   575,   576,   577,   578,   579,   636,
       0,   633,   635,   627,     0,   624,   626,    48,     0,     0,
      41,     0,     0,     0,     0,     0,     0,    59,     0,    61,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    73,     0,     0,     0,   121,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   262,
       0,     0,   408,     0,     0,     0,     0,     0,     0,   433,
       0,     0,     0,     0,     0,     0,     0,   463,     0,   333,
       0,     0,     0,     0,     0,     0,     0,   341,     0,     0,
       0,     0,   378,     0,     0,     0,     0,   227,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   562,     0,     0,   632,     0,     0,
     623,    52,    45,     0,     0,     0,     0,     0,     0,    63,
       0,     0,     0,     0,     0,     0,   111,   112,   113,   114,
     115,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   543,     0,
       0,     0,    75,     0,   131,   123,     0,     0,     0,     0,
       0,   301,   302,     0,     0,     0,   264,     0,   410,     0,
     449,     0,   452,   453,   435,     0,     0,     0,     0,     0,
       0,     0,   467,     0,     0,   357,     0,     0,     0,   368,
     345,     0,   397,   398,   382,     0,     0,   229,   583,     0,
       0,   588,     0,   591,   592,     0,     0,   599,   600,     0,
       0,     0,     0,   564,     0,   634,     0,   625,     0,     0,
       0,   615,   617,   619,   110,     0,     0,     0,     0,   138,
     117,   255,   334,   371,    42,   421,   423,   297,   298,   299,
     300,   296,   305,     0,    49,     0,     0,     0,   456,   220,
       0,     0,     0,   558,     0,    53,   130,   401,   426,   286,
     288,   290,   294,   292,     0,   419,   448,   451,   492,   480,
     482,   484,   486,   488,   490,   360,   178,   364,   362,   367,
     394,   234,   236,   585,   587,   590,   595,   596,   594,   598,
     603,   604,   605,   606,   607,   602,   609,   611,   613,     0,
     138,    46,     0,     0,     0,     0,   164,   170,   172,   174,
       0,     0,     0,     0,     0,   187,     0,     0,   190,     0,
       0,     0,   163,     0,   144,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   158,   159,   160,   161,   156,
     157,   162,     0,   142,     0,   139,   140,   259,     0,   256,
     257,   338,     0,   335,   336,   375,     0,   372,   373,   309,
       0,   306,   307,   205,   206,     0,   201,   203,   204,     0,
     214,   215,   211,     0,   209,   212,   213,   197,     0,   194,
     196,   503,     0,   501,   460,     0,   457,   458,   224,     0,
     221,   222,     0,     0,     0,     0,     0,     0,     0,   239,
     241,   242,   243,   244,   245,   246,   533,   539,     0,     0,
       0,   532,   529,   530,   531,     0,   522,   524,   527,   525,
     526,   528,   553,   555,   552,   550,   551,     0,   546,   548,
     549,     0,    55,   405,     0,   402,   403,   430,     0,   427,
     428,   497,   496,     0,   495,   640,     0,   638,     0,    71,
     630,   621,   119,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     133,   135,     0,   137,     0,     0,   254,     0,   342,   331,
       0,   379,   370,     0,     0,   304,     0,     0,   200,   217,
       0,   208,     0,     0,   193,   505,     0,   500,   464,   455,
       0,     0,   219,     0,     0,     0,     0,     0,     0,     0,
       0,   238,     0,     0,     0,     0,     0,     0,   521,     0,
       0,     0,   545,   560,    57,     0,    56,     0,   400,     0,
       0,   425,     0,     0,   494,     0,     0,   637,   628,     0,
       0,     0,     0,   176,   179,   180,   181,   182,     0,   189,
     183,     0,   184,   185,   186,   145,     0,   141,     0,   258,
       0,   337,     0,   374,   329,   324,   326,   317,   318,   313,
     314,   315,   316,   322,   323,   321,   325,     0,   311,   319,
     327,   328,   320,   308,   202,   210,     0,   195,   517,     0,
     515,   516,   512,   513,   514,     0,   506,   507,   509,   510,
     511,   502,     0,   459,     0,   223,   247,   248,   249,   250,
     251,   252,   240,     0,     0,   538,   541,   542,   523,     0,
       0,   547,    54,     0,     0,   404,     0,   429,     0,   654,
       0,   652,   650,   644,   648,   649,     0,   642,   646,   647,
     645,   639,   166,   167,   168,   169,   165,   171,   173,   175,
     188,   191,   143,   260,   339,   376,     0,   310,   198,     0,
       0,   504,     0,   461,   225,   535,   536,   537,   534,   540,
     554,   556,    58,   406,   431,   498,     0,     0,     0,     0,
     641,   312,     0,   519,   508,     0,   651,     0,   643,   518,
       0,   653,   658,     0,   656,     0,     0,   655,   666,     0,
       0,     0,     0,   660,   662,   663,   664,   665,   657,     0,
       0,     0,     0,     0,   659,     0,   668,   669,   670,   661,
     667
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,    43,  -827,  -456,
    -827,   191,  -827,  -827,  -827,  -827,    98,  -827,  -451,  -827,
    -827,  -827,   -74,  -827,  -827,  -827,   411,  -827,  -827,  -827,
    -827,   199,   371,  -827,  -827,   -62,   -46,   -45,   -43,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,   193,   380,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,   131,  -827,   -30,
    -827,  -572,   -23,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,   -70,  -827,  -605,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,   -48,  -827,  -827,  -827,  -827,  -827,   -38,  -592,  -827,
    -827,  -827,  -827,   -22,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,   -33,  -827,  -827,  -827,   -35,   392,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,   -31,  -827,  -827,  -827,  -827,
    -827,  -827,  -826,  -827,  -827,  -827,   -10,  -827,  -827,  -827,
       1,   432,  -827,  -827,  -825,  -827,  -824,  -827,   -36,  -827,
     -32,  -827,   -42,  -827,  -827,  -827,  -821,  -827,  -827,  -827,
    -827,    -5,  -827,  -827,  -174,   772,  -827,  -827,  -827,  -827,
    -827,     6,  -827,  -827,  -827,     7,  -827,   410,  -827,   -76,
    -827,  -827,  -827,  -827,  -827,   -69,  -827,  -827,  -827,  -827,
    -827,   -11,  -827,  -827,  -827,     9,  -827,  -827,  -827,     8,
    -827,   407,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,   -29,  -827,  -827,  -827,   -28,   445,  -827,
    -827,   -58,  -827,   -24,  -827,  -827,  -827,  -827,  -827,   -27,
    -827,  -827,  -827,   -26,   443,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,   -60,  -827,  -827,  -827,     2,  -827,  -827,  -827,
      10,  -827,   439,   245,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -818,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,    14,  -827,  -827,  -827,  -150,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,    -4,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
      -7,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,   261,   420,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,
    -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,  -827,   292,
     409,  -827,  -827,  -827,  -827,  -827,  -827,   305,   425,  -827,
    -827,  -827,   -16,  -827,  -827,  -158,  -827,  -827,  -827,  -827,
    -827,  -827,  -172,  -827,  -827,  -191,  -827,  -827,  -827,  -827,
    -827
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   605,    92,    93,    43,    72,    89,    90,   626,   802,
     895,   896,   692,    45,    74,   101,   102,   103,   362,    47,
      75,   141,   142,   143,   370,   144,   145,   146,   147,   148,
     149,   381,   150,   372,    49,    76,   178,   179,   180,   404,
     181,   151,   373,   152,   374,   153,   375,   714,   715,   716,
     842,   693,   694,   695,   823,  1016,   696,   824,   697,   825,
     698,   826,   699,   700,   441,   701,   702,   703,   704,   705,
     706,   707,   708,   709,   832,   710,   711,   835,   154,   392,
     748,   749,   750,   862,   155,   389,   735,   736,   737,   738,
     156,   391,   743,   744,   745,   746,   157,   390,   158,   395,
     759,   760,   761,   871,    65,    84,   310,   311,   312,   454,
     313,   455,   159,   396,   768,   769,   770,   771,   772,   773,
     774,   775,   160,   382,   718,   719,   720,   845,    51,    77,
     199,   200,   201,   410,   202,   411,   203,   412,   204,   416,
     205,   415,   161,   387,   611,   207,   208,   162,   388,   730,
     731,   732,   854,   947,   948,   163,   383,    59,    81,   722,
     723,   724,   848,    61,    82,   275,   276,   277,   278,   279,
     280,   281,   440,   282,   444,   283,   443,   284,   285,   445,
     286,   164,   384,   726,   727,   728,   851,    63,    83,   296,
     297,   298,   299,   300,   449,   301,   302,   303,   304,   210,
     408,   804,   805,   806,   897,    53,    78,   221,   222,   223,
     420,   165,   385,   166,   386,   213,   409,   808,   809,   810,
     900,    55,    79,   237,   238,   239,   423,   240,   241,   425,
     242,   243,   167,   394,   755,   756,   757,   868,    57,    80,
     255,   256,   257,   258,   431,   259,   432,   260,   433,   261,
     434,   262,   435,   263,   436,   264,   430,   215,   417,   813,
     814,   903,   168,   393,   752,   753,   865,   965,   966,   967,
     968,   969,  1029,   970,   169,   397,   785,   786,   787,   882,
    1038,   788,   789,   883,   790,   791,   170,   171,   399,   797,
     798,   799,   889,   800,   890,   172,   400,   173,   401,    67,
      85,   332,   333,   334,   335,   459,   336,   460,   337,   338,
     462,   339,   340,   341,   465,   658,   342,   466,   343,   344,
     345,   469,   665,   346,   470,   347,   471,   348,   472,   104,
     364,   105,   365,   106,   366,   174,   371,    71,    87,   354,
     355,   356,   478,   107,   363,    69,    86,   350,   351,   352,
     475,   816,   817,   905,  1006,  1007,  1008,  1009,  1048,  1010,
    1046,  1063,  1064,  1065,  1072,  1073,  1074,  1079,  1075,  1076,
    1077
  };

  const unsigned short
  Dhcp6Parser::yytable_[] =
  {
     100,   140,   177,   194,   217,   231,   251,   294,   273,   292,
     309,   329,   274,   293,   295,   195,   782,   214,   182,   211,
     224,   235,   253,   742,   287,   305,   712,   330,   940,   941,
     942,   196,   197,   946,   198,   206,   952,    94,   175,   176,
     733,   245,   218,   232,    32,   368,   219,   233,   811,   604,
     369,    91,   183,   212,   225,   236,   254,    44,   288,   306,
      40,   331,   307,   308,   604,    46,   209,   220,   234,   252,
      33,   402,    34,    48,    35,   267,   403,    50,   123,   124,
     108,   109,   632,   110,   122,    52,   111,   112,   113,   123,
     124,   266,   123,   124,   638,   639,   640,   226,   227,   228,
     229,   230,   123,   124,   660,   661,   662,   663,    54,   114,
     115,   116,   117,   118,   119,   120,   121,   122,    56,   734,
     267,   191,   268,   269,   192,    58,   270,   271,   272,    60,
     792,   793,   776,    62,    99,   123,   124,   123,   124,   406,
     664,   681,   125,   857,   407,    64,   858,   126,   127,   128,
     129,   130,  1068,   131,    66,  1069,  1070,  1071,   132,   762,
     763,   764,   765,   766,   767,    68,   860,   133,   418,   861,
     134,    95,   999,   419,  1000,  1001,    70,   135,   123,   124,
      96,    97,    98,    99,   121,   136,   137,   353,   421,   138,
     139,   428,   866,   422,    99,   867,   429,    99,    99,   349,
     940,   941,   942,   357,   676,   946,   358,    99,   952,   677,
     678,   679,   680,   681,   682,   683,   684,   685,   686,   687,
     688,   689,   690,   691,   777,   778,   779,   780,   359,   122,
     456,   733,   740,   267,   741,   457,    36,    37,    38,    39,
      99,   473,    99,   360,   122,   361,   474,   123,   124,   267,
     289,   268,   269,   290,   291,   216,   476,   906,   438,   479,
     907,   477,   123,   124,   480,   244,   123,   124,   742,   367,
     926,   245,   246,   247,   248,   249,   250,   114,   115,   116,
     117,   191,   782,    99,   192,   122,   402,   476,   479,   307,
     308,   819,   820,   821,   100,   184,   406,   185,   122,   267,
     376,   822,   377,   123,   124,   186,   187,   188,   189,   190,
     125,   656,   657,   839,   839,   863,   123,   124,   840,   841,
     864,   378,   191,   379,   880,   192,   132,   380,   140,   881,
     887,   448,   177,   193,   891,   888,   958,   959,   473,   892,
     839,   418,   437,   893,   194,  1022,  1023,   217,   182,   398,
    1066,   439,    99,  1067,   231,    99,   195,  1026,   214,   405,
     211,   456,  1027,   224,   251,   413,  1034,    99,   414,   424,
     235,    99,   196,   197,   273,   198,   206,   294,   274,   292,
     253,   421,   183,   293,   295,   218,  1043,   426,   428,   219,
     287,   427,   232,  1044,   212,   305,   233,   225,  1049,   329,
    1083,   481,   482,  1050,   236,  1084,   442,   209,    99,   446,
     220,  1035,  1036,  1037,   254,   330,   447,   234,   450,   451,
     452,    99,   453,   483,   288,   458,   461,   252,   463,   306,
     114,   115,   116,   117,   123,   124,   120,   464,   122,   267,
     607,   608,   609,   610,  1012,  1013,  1014,  1015,   467,   331,
     468,   484,   485,   486,   487,   488,   123,   124,   490,   187,
     188,   491,   190,   125,   492,   493,   494,   495,   501,   496,
     502,   497,   498,   499,   503,   191,   500,   504,   192,   505,
     506,   507,   508,   509,   510,   511,   193,   512,   513,   514,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   515,   516,   517,   519,   520,   518,   521,
     327,   328,   523,   524,   526,   140,   527,   528,   529,   530,
     531,   533,   177,   532,   534,   535,   537,   539,   540,   591,
     592,   593,   541,   545,   542,   543,   546,   547,   182,    99,
     548,   549,   550,   551,   553,   554,   555,   781,   794,   556,
     329,   557,   558,   559,   561,   562,   563,   565,   566,   569,
     568,    99,   570,   783,   795,   571,   330,   572,   573,   575,
     574,   576,   183,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,   579,   580,
     577,   581,   578,   582,   584,   586,   588,   784,   796,   594,
     331,   589,   590,   595,   596,   597,   598,   599,   600,   652,
     601,   602,   603,   606,   612,    34,   613,   614,   615,   844,
     617,   616,   618,   619,   629,   747,   620,   621,   622,   624,
     625,   671,   627,   628,   669,   659,   630,   634,   631,   633,
     635,   670,   636,   637,   713,   641,   717,   721,   725,   729,
     751,   754,   758,   642,   803,   807,   815,   643,   644,   645,
     646,   647,   648,   649,   650,   651,   653,   654,   655,   827,
     828,   829,   830,   831,   833,   666,   834,   667,   668,   836,
     837,   838,   894,   847,   843,   846,   850,   849,   852,   853,
     855,   856,   914,   859,   870,   869,   872,   873,   898,   874,
     875,   876,   877,   878,   879,   884,   885,   886,   899,   902,
     901,   623,   739,   909,   908,   904,   910,   911,   912,   918,
     916,   913,   921,   915,   917,   956,   983,   984,   919,   920,
     989,   922,   923,   990,   976,   924,   977,   992,   978,   993,
     979,   980,   981,   985,   986,   987,   998,  1017,  1018,  1019,
    1020,  1021,  1024,  1025,  1028,  1030,  1031,  1032,  1033,  1039,
    1047,  1052,  1055,  1057,  1040,  1060,  1080,  1081,  1062,  1082,
    1085,   194,  1041,   522,   273,   294,  1056,   292,   274,   489,
     934,   293,   295,   195,   939,   214,   525,   211,   672,   675,
     287,   960,   935,   305,   251,   961,   950,   309,  1053,   196,
     197,   818,   198,   206,  1042,  1045,  1059,   963,   936,   937,
     253,   938,   945,   781,   927,   957,   925,   794,   943,   954,
    1086,   212,   944,   217,   288,  1061,   231,   306,  1087,   783,
     951,  1002,  1088,   795,   209,  1003,   974,   929,   955,   224,
     975,   964,   235,   949,   254,  1090,   928,  1004,   567,   982,
     536,   953,  1051,   265,   962,   930,   931,   252,   560,   932,
     564,   218,   933,   784,   232,   219,   538,   796,   233,   994,
     995,   544,   973,   225,   996,   997,   236,   552,   972,   812,
     971,  1005,  1054,   988,   991,   801,   220,   674,   587,   234,
    1011,  1058,  1089,   583,  1078,   673,     0,     0,     0,     0,
       0,   585,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   934,     0,     0,     0,   939,     0,   960,     0,
       0,     0,   961,     0,   935,     0,     0,     0,   950,     0,
       0,     0,     0,     0,   963,  1002,     0,     0,     0,  1003,
     936,   937,     0,   938,   945,     0,     0,     0,     0,     0,
     943,  1004,     0,     0,   944,     0,     0,     0,     0,     0,
       0,     0,   951,     0,     0,     0,     0,     0,   964,     0,
       0,     0,     0,     0,     0,   949,     0,     0,     0,     0,
       0,   962,     0,     0,     0,  1005
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    83,    82,    83,
      84,    85,    82,    83,    83,    77,   621,    77,    76,    77,
      78,    79,    80,   615,    82,    83,   598,    85,   854,   854,
     854,    77,    77,   854,    77,    77,   854,    10,    15,    16,
      92,    90,    78,    79,     0,     3,    78,    79,    97,   505,
       8,   171,    76,    77,    78,    79,    80,     7,    82,    83,
      17,    85,    99,   100,   520,     7,    77,    78,    79,    80,
       5,     3,     7,     7,     9,    49,     8,     7,    66,    67,
      11,    12,   533,    14,    48,     7,    17,    18,    19,    66,
      67,    20,    66,    67,   545,   546,   547,    61,    62,    63,
      64,    65,    66,    67,   138,   139,   140,   141,     7,    40,
      41,    42,    43,    44,    45,    46,    47,    48,     7,   171,
      49,    85,    51,    52,    88,     7,    55,    56,    57,     7,
     118,   119,    20,     7,   171,    66,    67,    66,    67,     3,
     174,    29,    73,     3,     8,     7,     6,    78,    79,    80,
      81,    82,   147,    84,     7,   150,   151,   152,    89,   102,
     103,   104,   105,   106,   107,     7,     3,    98,     3,     6,
     101,   144,   146,     8,   148,   149,     7,   108,    66,    67,
     153,   154,   155,   171,    47,   116,   117,    13,     3,   120,
     121,     3,     3,     8,   171,     6,     8,   171,   171,   145,
    1026,  1026,  1026,     6,    20,  1026,     3,   171,  1026,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,   112,   113,   114,   115,     4,    48,
       3,    92,    93,    49,    95,     8,   171,   172,   173,   174,
     171,     3,   171,     8,    48,     3,     8,    66,    67,    49,
      50,    51,    52,    53,    54,    59,     3,     3,     3,     3,
       6,     8,    66,    67,     8,    84,    66,    67,   860,     4,
     842,    90,    91,    92,    93,    94,    95,    40,    41,    42,
      43,    85,   887,   171,    88,    48,     3,     3,     3,    99,
     100,     8,     8,     8,   368,    58,     3,    60,    48,    49,
       4,     8,     4,    66,    67,    68,    69,    70,    71,    72,
      73,   135,   136,     3,     3,     3,    66,    67,     8,     8,
       8,     4,    85,     4,     3,    88,    89,     4,   402,     8,
       3,     3,   406,    96,     3,     8,    86,    87,     3,     8,
       3,     3,     8,     8,   418,     8,     8,   421,   406,     4,
       3,     8,   171,     6,   428,   171,   418,     3,   418,     4,
     418,     3,     8,   421,   438,     4,     8,   171,     4,     4,
     428,   171,   418,   418,   448,   418,   418,   453,   448,   453,
     438,     3,   406,   453,   453,   421,     8,     4,     3,   421,
     448,     4,   428,     8,   418,   453,   428,   421,     3,   473,
       3,   358,   359,     8,   428,     8,     4,   418,   171,     4,
     421,   109,   110,   111,   438,   473,     8,   428,     4,     4,
       8,   171,     3,   171,   448,     4,     4,   438,     4,   453,
      40,    41,    42,    43,    66,    67,    46,     4,    48,    49,
      74,    75,    76,    77,    21,    22,    23,    24,     4,   473,
       4,     4,     4,     4,     4,     4,    66,    67,     4,    69,
      70,     4,    72,    73,     4,     4,     4,     4,     4,   172,
       4,   172,   172,   172,     4,    85,   172,     4,    88,     4,
       4,     4,     4,     4,     4,     4,    96,     4,     4,     4,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,     4,     4,     4,     4,     4,   172,     4,
     142,   143,     4,   174,     4,   589,     4,     4,     4,     4,
     172,     4,   596,   174,     4,     4,     4,     4,   172,   486,
     487,   488,     4,     4,   172,   172,     4,     4,   596,   171,
       4,     4,     4,     4,     4,     4,   172,   621,   622,     4,
     624,     4,     4,   174,     4,   174,   174,     4,     4,     4,
     174,   171,     4,   621,   622,   172,   624,     4,   172,     4,
     172,     4,   596,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,     4,     4,
     174,     4,   174,     4,     4,     4,     4,   621,   622,   171,
     624,     7,     7,     7,     7,     7,     7,     5,   171,   566,
       5,     5,     5,   171,     5,     7,     5,     5,     5,     3,
       5,     7,     5,     5,   171,    83,     7,     7,     7,     7,
       5,   588,     5,     5,     5,   137,   171,     7,   171,   171,
     171,     5,   171,   171,     7,   171,     7,     7,     7,     7,
       7,     7,     7,   171,     7,     7,     7,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,     4,
       4,     4,     4,     4,     4,   171,     4,   171,   171,     4,
       4,     4,   171,     3,     6,     6,     3,     6,     6,     3,
       6,     3,   174,     6,     3,     6,     6,     3,     6,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,     3,
       6,   520,   614,     4,     6,     8,     4,     4,     4,     4,
     174,   172,     4,   172,   172,     4,     4,     4,   172,   172,
       4,   172,   172,     4,   172,   174,   172,     6,   172,     3,
     172,   172,   172,   172,   172,   172,     4,   171,   171,   171,
     171,   171,     8,     8,   171,     4,     8,     3,     8,   171,
       4,     4,     4,     4,   171,     5,     4,     4,     7,     4,
       4,   845,   171,   402,   848,   851,   172,   851,   848,   368,
     854,   851,   851,   845,   854,   845,   406,   845,   589,   596,
     848,   865,   854,   851,   868,   865,   854,   871,   174,   845,
     845,   670,   845,   845,   171,   171,   171,   865,   854,   854,
     868,   854,   854,   887,   844,   863,   839,   891,   854,   857,
     174,   845,   854,   897,   848,   171,   900,   851,   172,   887,
     854,   905,   172,   891,   845,   905,   871,   847,   860,   897,
     873,   865,   900,   854,   868,   171,   845,   905,   456,   880,
     418,   856,  1026,    81,   865,   848,   850,   868,   448,   851,
     453,   897,   853,   887,   900,   897,   421,   891,   900,   897,
     899,   428,   870,   897,   900,   902,   900,   438,   868,   634,
     866,   905,  1032,   887,   891,   624,   897,   595,   479,   900,
     906,  1049,  1083,   473,  1066,   590,    -1,    -1,    -1,    -1,
      -1,   476,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1026,    -1,    -1,    -1,  1026,    -1,  1032,    -1,
      -1,    -1,  1032,    -1,  1026,    -1,    -1,    -1,  1026,    -1,
      -1,    -1,    -1,    -1,  1032,  1049,    -1,    -1,    -1,  1049,
    1026,  1026,    -1,  1026,  1026,    -1,    -1,    -1,    -1,    -1,
    1026,  1049,    -1,    -1,  1026,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1026,    -1,    -1,    -1,    -1,    -1,  1032,    -1,
      -1,    -1,    -1,    -1,    -1,  1026,    -1,    -1,    -1,    -1,
      -1,  1032,    -1,    -1,    -1,  1049
  };

  const unsigned short
  Dhcp6Parser::yystos_[] =
  {
       0,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,     0,     5,     7,     9,   171,   172,   173,   174,
     192,   193,   194,   199,     7,   208,     7,   214,     7,   229,
       7,   323,     7,   400,     7,   416,     7,   433,     7,   352,
       7,   358,     7,   382,     7,   299,     7,   494,     7,   540,
       7,   532,   200,   195,   209,   215,   230,   324,   401,   417,
     434,   353,   359,   383,   300,   495,   541,   533,   192,   201,
     202,   171,   197,   198,    10,   144,   153,   154,   155,   171,
     207,   210,   211,   212,   524,   526,   528,   538,    11,    12,
      14,    17,    18,    19,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    66,    67,    73,    78,    79,    80,    81,
      82,    84,    89,    98,   101,   108,   116,   117,   120,   121,
     207,   216,   217,   218,   220,   221,   222,   223,   224,   225,
     227,   236,   238,   240,   273,   279,   285,   291,   293,   307,
     317,   337,   342,   350,   376,   406,   408,   427,   457,   469,
     481,   482,   490,   492,   530,    15,    16,   207,   231,   232,
     233,   235,   406,   408,    58,    60,    68,    69,    70,    71,
      72,    85,    88,    96,   207,   220,   221,   222,   223,   325,
     326,   327,   329,   331,   333,   335,   337,   340,   341,   376,
     394,   406,   408,   410,   427,   452,    59,   207,   333,   335,
     376,   402,   403,   404,   406,   408,    61,    62,    63,    64,
      65,   207,   333,   335,   376,   406,   408,   418,   419,   420,
     422,   423,   425,   426,    84,    90,    91,    92,    93,    94,
      95,   207,   376,   406,   408,   435,   436,   437,   438,   440,
     442,   444,   446,   448,   450,   350,    20,    49,    51,    52,
      55,    56,    57,   207,   258,   360,   361,   362,   363,   364,
     365,   366,   368,   370,   372,   373,   375,   406,   408,    50,
      53,    54,   207,   258,   364,   370,   384,   385,   386,   387,
     388,   390,   391,   392,   393,   406,   408,    99,   100,   207,
     301,   302,   303,   305,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   142,   143,   207,
     406,   408,   496,   497,   498,   499,   501,   503,   504,   506,
     507,   508,   511,   513,   514,   515,   518,   520,   522,   145,
     542,   543,   544,    13,   534,   535,   536,     6,     3,     4,
       8,     3,   213,   539,   525,   527,   529,     4,     3,     8,
     219,   531,   228,   237,   239,   241,     4,     4,     4,     4,
       4,   226,   318,   351,   377,   407,   409,   338,   343,   280,
     292,   286,   274,   458,   428,   294,   308,   470,     4,   483,
     491,   493,     3,     8,   234,     4,     3,     8,   395,   411,
     328,   330,   332,     4,     4,   336,   334,   453,     3,     8,
     405,     3,     8,   421,     4,   424,     4,     4,     3,     8,
     451,   439,   441,   443,   445,   447,   449,     8,     3,     8,
     367,   259,     4,   371,   369,   374,     4,     8,     3,   389,
       4,     4,     8,     3,   304,   306,     3,     8,     4,   500,
     502,     4,   505,     4,     4,   509,   512,     4,     4,   516,
     519,   521,   523,     3,     8,   545,     3,     8,   537,     3,
       8,   192,   192,   171,     4,     4,     4,     4,     4,   211,
       4,     4,     4,     4,     4,     4,   172,   172,   172,   172,
     172,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   172,     4,
       4,     4,   217,     4,   174,   232,     4,     4,     4,     4,
       4,   172,   174,     4,     4,     4,   326,     4,   403,     4,
     172,     4,   172,   172,   419,     4,     4,     4,     4,     4,
       4,     4,   437,     4,     4,   172,     4,     4,     4,   174,
     362,     4,   174,   174,   386,     4,     4,   302,   174,     4,
       4,   172,     4,   172,   172,     4,     4,   174,   174,     4,
       4,     4,     4,   497,     4,   543,     4,   535,     4,     7,
       7,   192,   192,   192,   171,     7,     7,     7,     7,     5,
     171,     5,     5,     5,   194,   196,   171,    74,    75,    76,
      77,   339,     5,     5,     5,     5,     7,     5,     5,     5,
       7,     7,     7,   196,     7,     5,   203,     5,     5,   171,
     171,   171,   203,   171,     7,   171,   171,   171,   203,   203,
     203,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   192,   171,   171,   171,   135,   136,   510,   137,
     138,   139,   140,   141,   174,   517,   171,   171,   171,     5,
       5,   192,   216,   542,   534,   231,    20,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,   207,   246,   247,   248,   251,   253,   255,   257,
     258,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     270,   271,   246,     7,   242,   243,   244,     7,   319,   320,
     321,     7,   354,   355,   356,     7,   378,   379,   380,     7,
     344,   345,   346,    92,   171,   281,   282,   283,   284,   201,
      93,    95,   283,   287,   288,   289,   290,    83,   275,   276,
     277,     7,   459,   460,     7,   429,   430,   431,     7,   295,
     296,   297,   102,   103,   104,   105,   106,   107,   309,   310,
     311,   312,   313,   314,   315,   316,    20,   112,   113,   114,
     115,   207,   260,   406,   408,   471,   472,   473,   476,   477,
     479,   480,   118,   119,   207,   406,   408,   484,   485,   486,
     488,   496,   204,     7,   396,   397,   398,     7,   412,   413,
     414,    97,   438,   454,   455,     7,   546,   547,   242,     8,
       8,     8,     8,   249,   252,   254,   256,     4,     4,     4,
       4,     4,   269,     4,     4,   272,     4,     4,     4,     3,
       8,     8,   245,     6,     3,   322,     6,     3,   357,     6,
       3,   381,     6,     3,   347,     6,     3,     3,     6,     6,
       3,     6,   278,     3,     8,   461,     3,     6,   432,     6,
       3,   298,     6,     3,     4,     4,     4,     4,     4,     4,
       3,     8,   474,   478,     4,     4,     4,     3,     8,   487,
     489,     3,     8,     8,   171,   205,   206,   399,     6,     3,
     415,     6,     3,   456,     8,   548,     3,     6,     6,     4,
       4,     4,     4,   172,   174,   172,   174,   172,     4,   172,
     172,     4,   172,   172,   174,   247,   246,   244,   325,   321,
     360,   356,   384,   380,   207,   220,   221,   222,   223,   258,
     317,   329,   331,   333,   335,   337,   341,   348,   349,   376,
     406,   408,   452,   346,   282,   288,     4,   276,    86,    87,
     207,   258,   376,   406,   408,   462,   463,   464,   465,   466,
     468,   460,   435,   431,   301,   297,   172,   172,   172,   172,
     172,   172,   310,     4,     4,   172,   172,   172,   472,     4,
       4,   485,     6,     3,   402,   398,   418,   414,     4,   146,
     148,   149,   207,   258,   406,   408,   549,   550,   551,   552,
     554,   547,    21,    22,    23,    24,   250,   171,   171,   171,
     171,   171,     8,     8,     8,     8,     3,     8,   171,   467,
       4,     8,     3,     8,     8,   109,   110,   111,   475,   171,
     171,   171,   171,     8,     8,   171,   555,     4,   553,     3,
       8,   349,     4,   174,   464,     4,   172,     4,   550,   171,
       5,   171,     7,   556,   557,   558,     3,     6,   147,   150,
     151,   152,   559,   560,   561,   563,   564,   565,   557,   562,
       4,     4,     4,     3,     8,     4,   174,   172,   172,   560,
     171
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
     217,   217,   217,   217,   217,   217,   217,   217,   217,   219,
     218,   220,   221,   222,   223,   224,   226,   225,   228,   227,
     230,   229,   231,   231,   232,   232,   232,   232,   232,   234,
     233,   235,   237,   236,   239,   238,   241,   240,   242,   242,
     243,   243,   245,   244,   246,   246,   247,   247,   247,   247,
     247,   247,   247,   247,   247,   247,   247,   247,   247,   247,
     247,   247,   247,   247,   249,   248,   250,   250,   250,   250,
     252,   251,   254,   253,   256,   255,   257,   259,   258,   260,
     261,   262,   263,   264,   265,   266,   267,   269,   268,   270,
     272,   271,   274,   273,   275,   275,   276,   278,   277,   280,
     279,   281,   281,   282,   282,   283,   284,   286,   285,   287,
     287,   288,   288,   288,   289,   290,   292,   291,   294,   293,
     295,   295,   296,   296,   298,   297,   300,   299,   301,   301,
     301,   302,   302,   304,   303,   306,   305,   308,   307,   309,
     309,   310,   310,   310,   310,   310,   310,   311,   312,   313,
     314,   315,   316,   318,   317,   319,   319,   320,   320,   322,
     321,   324,   323,   325,   325,   326,   326,   326,   326,   326,
     326,   326,   326,   326,   326,   326,   326,   326,   326,   326,
     326,   326,   326,   326,   326,   328,   327,   330,   329,   332,
     331,   334,   333,   336,   335,   338,   337,   339,   339,   339,
     339,   340,   341,   343,   342,   344,   344,   345,   345,   347,
     346,   348,   348,   349,   349,   349,   349,   349,   349,   349,
     349,   349,   349,   349,   349,   349,   349,   349,   349,   349,
     351,   350,   353,   352,   354,   354,   355,   355,   357,   356,
     359,   358,   360,   360,   361,   361,   362,   362,   362,   362,
     362,   362,   362,   362,   362,   362,   363,   364,   365,   367,
     366,   369,   368,   371,   370,   372,   374,   373,   375,   377,
     376,   378,   378,   379,   379,   381,   380,   383,   382,   384,
     384,   385,   385,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   387,   389,   388,   390,   391,   392,   393,   395,
     394,   396,   396,   397,   397,   399,   398,   401,   400,   402,
     402,   403,   403,   403,   403,   403,   403,   403,   405,   404,
     407,   406,   409,   408,   411,   410,   412,   412,   413,   413,
     415,   414,   417,   416,   418,   418,   419,   419,   419,   419,
     419,   419,   419,   419,   419,   419,   419,   421,   420,   422,
     424,   423,   425,   426,   428,   427,   429,   429,   430,   430,
     432,   431,   434,   433,   435,   435,   436,   436,   437,   437,
     437,   437,   437,   437,   437,   437,   437,   437,   437,   439,
     438,   441,   440,   443,   442,   445,   444,   447,   446,   449,
     448,   451,   450,   453,   452,   454,   454,   456,   455,   458,
     457,   459,   459,   461,   460,   462,   462,   463,   463,   464,
     464,   464,   464,   464,   464,   464,   465,   467,   466,   468,
     470,   469,   471,   471,   472,   472,   472,   472,   472,   472,
     472,   472,   472,   474,   473,   475,   475,   475,   476,   478,
     477,   479,   480,   481,   483,   482,   484,   484,   485,   485,
     485,   485,   485,   487,   486,   489,   488,   491,   490,   493,
     492,   495,   494,   496,   496,   497,   497,   497,   497,   497,
     497,   497,   497,   497,   497,   497,   497,   497,   497,   497,
     497,   497,   497,   498,   500,   499,   502,   501,   503,   505,
     504,   506,   507,   509,   508,   510,   510,   512,   511,   513,
     514,   516,   515,   517,   517,   517,   517,   517,   519,   518,
     521,   520,   523,   522,   525,   524,   527,   526,   529,   528,
     531,   530,   533,   532,   534,   534,   535,   537,   536,   539,
     538,   541,   540,   542,   542,   543,   545,   544,   546,   546,
     548,   547,   549,   549,   550,   550,   550,   550,   550,   550,
     550,   551,   553,   552,   555,   554,   556,   556,   558,   557,
     559,   559,   560,   560,   560,   560,   562,   561,   563,   564,
     565
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
       1,     1,     1,     1,     0,     4,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     0,     4,     3,
       0,     4,     0,     6,     1,     3,     1,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     0,     6,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     1,     1,     1,
       1,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     6,     0,     4,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     0,
       4,     0,     4,     0,     4,     1,     0,     4,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       0,     4,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     1,     1,     0,     4,     0,
       6,     1,     3,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     3,     0,
       4,     3,     3,     3,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     0,     4,     1,     1,     0,     4,     3,
       3,     0,     4,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     4,     1,     3,     1,     0,     6,     0,
       6,     0,     4,     1,     3,     1,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     0,     4,     3,     3,
       3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp6Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"", "\"data-directory\"",
  "\"config-control\"", "\"config-databases\"", "\"interfaces-config\"",
  "\"interfaces\"", "\"re-detect\"", "\"lease-database\"",
  "\"hosts-database\"", "\"hosts-databases\"", "\"type\"", "\"memfile\"",
  "\"mysql\"", "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"",
  "\"host\"", "\"port\"", "\"persist\"", "\"lfc-interval\"",
  "\"readonly\"", "\"connect-timeout\"", "\"contact-points\"",
  "\"max-reconnect-tries\"", "\"reconnect-wait-time\"", "\"keyspace\"",
  "\"request-timeout\"", "\"tcp-keepalive\"", "\"tcp-nodelay\"",
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
  "sanity_checks", "$@38", "sanity_checks_params", "sanity_checks_param",
  "lease_checks", "$@39", "mac_sources", "$@40", "mac_sources_list",
  "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@41",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@42",
  "hooks_libraries", "$@43", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@44",
  "sub_hooks_library", "$@45", "hooks_params", "hooks_param", "library",
  "$@46", "parameters", "$@47", "expired_leases_processing", "$@48",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@49",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@50",
  "sub_subnet6", "$@51", "subnet6_params", "subnet6_param", "subnet",
  "$@52", "interface", "$@53", "interface_id", "$@54", "client_class",
  "$@55", "require_client_classes", "$@56", "reservation_mode", "$@57",
  "hr_mode", "id", "rapid_commit", "shared_networks", "$@58",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@59", "shared_network_params", "shared_network_param",
  "option_def_list", "$@60", "sub_option_def_list", "$@61",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@62", "sub_option_def", "$@63",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@64",
  "option_def_record_types", "$@65", "space", "$@66", "option_def_space",
  "option_def_encapsulate", "$@67", "option_def_array", "option_data_list",
  "$@68", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@69", "sub_option_data", "$@70",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@71",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@72", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@73", "sub_pool6", "$@74",
  "pool_params", "pool_param", "pool_entry", "$@75", "user_context",
  "$@76", "comment", "$@77", "pd_pools_list", "$@78",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@79", "sub_pd_pool", "$@80", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@81", "pd_prefix_len", "excluded_prefix", "$@82",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@83",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@84", "sub_reservation", "$@85", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@86", "prefixes", "$@87", "duid", "$@88", "hw_address", "$@89",
  "hostname", "$@90", "flex_id_value", "$@91",
  "reservation_client_classes", "$@92", "relay", "$@93", "relay_map",
  "ip_address", "$@94", "client_classes", "$@95", "client_classes_list",
  "client_class_entry", "$@96", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@97", "only_if_required",
  "server_id", "$@98", "server_id_params", "server_id_param",
  "server_id_type", "$@99", "duid_type", "htype", "identifier", "$@100",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@101",
  "control_socket_params", "control_socket_param", "socket_type", "$@102",
  "socket_name", "$@103", "dhcp_queue_control", "$@104", "dhcp_ddns",
  "$@105", "sub_dhcp_ddns", "$@106", "dhcp_ddns_params", "dhcp_ddns_param",
  "enable_updates", "qualifying_suffix", "$@107", "server_ip", "$@108",
  "server_port", "sender_ip", "$@109", "sender_port", "max_queue_size",
  "ncr_protocol", "$@110", "ncr_protocol_value", "ncr_format", "$@111",
  "override_no_update", "override_client_update", "replace_client_name",
  "$@112", "replace_client_name_value", "generated_prefix", "$@113",
  "hostname_char_set", "$@114", "hostname_char_replacement", "$@115",
  "dhcp4_json_object", "$@116", "dhcpddns_json_object", "$@117",
  "control_agent_json_object", "$@118", "config_control", "$@119",
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
     463,   464,   465,   466,   467,   468,   469,   470,   471,   474,
     474,   482,   487,   492,   497,   502,   507,   507,   515,   515,
     526,   526,   535,   536,   539,   540,   541,   542,   543,   546,
     546,   556,   562,   562,   574,   574,   586,   586,   596,   597,
     600,   601,   604,   604,   614,   615,   618,   619,   620,   621,
     622,   623,   624,   625,   626,   627,   628,   629,   630,   631,
     632,   633,   634,   635,   638,   638,   645,   646,   647,   648,
     651,   651,   659,   659,   667,   667,   675,   680,   680,   688,
     693,   698,   703,   708,   713,   718,   723,   728,   728,   736,
     741,   741,   749,   749,   759,   760,   762,   764,   764,   782,
     782,   792,   793,   796,   797,   800,   805,   810,   810,   820,
     821,   824,   825,   826,   829,   834,   841,   841,   851,   851,
     861,   862,   865,   866,   869,   869,   879,   879,   889,   890,
     891,   894,   895,   898,   898,   906,   906,   914,   914,   925,
     926,   929,   930,   931,   932,   933,   934,   937,   942,   947,
     952,   957,   962,   970,   970,   983,   984,   987,   988,   995,
     995,  1021,  1021,  1032,  1033,  1037,  1038,  1039,  1040,  1041,
    1042,  1043,  1044,  1045,  1046,  1047,  1048,  1049,  1050,  1051,
    1052,  1053,  1054,  1055,  1056,  1059,  1059,  1067,  1067,  1075,
    1075,  1083,  1083,  1091,  1091,  1101,  1101,  1108,  1109,  1110,
    1111,  1114,  1119,  1127,  1127,  1138,  1139,  1143,  1144,  1147,
    1147,  1155,  1156,  1159,  1160,  1161,  1162,  1163,  1164,  1165,
    1166,  1167,  1168,  1169,  1170,  1171,  1172,  1173,  1174,  1175,
    1182,  1182,  1195,  1195,  1204,  1205,  1208,  1209,  1214,  1214,
    1229,  1229,  1243,  1244,  1247,  1248,  1251,  1252,  1253,  1254,
    1255,  1256,  1257,  1258,  1259,  1260,  1263,  1265,  1270,  1272,
    1272,  1280,  1280,  1288,  1288,  1296,  1298,  1298,  1306,  1315,
    1315,  1327,  1328,  1333,  1334,  1339,  1339,  1351,  1351,  1363,
    1364,  1369,  1370,  1375,  1376,  1377,  1378,  1379,  1380,  1381,
    1382,  1383,  1386,  1388,  1388,  1396,  1398,  1400,  1405,  1413,
    1413,  1425,  1426,  1429,  1430,  1433,  1433,  1443,  1443,  1452,
    1453,  1456,  1457,  1458,  1459,  1460,  1461,  1462,  1465,  1465,
    1473,  1473,  1498,  1498,  1528,  1528,  1540,  1541,  1544,  1545,
    1548,  1548,  1560,  1560,  1572,  1573,  1576,  1577,  1578,  1579,
    1580,  1581,  1582,  1583,  1584,  1585,  1586,  1589,  1589,  1597,
    1602,  1602,  1610,  1615,  1623,  1623,  1633,  1634,  1637,  1638,
    1641,  1641,  1650,  1650,  1659,  1660,  1663,  1664,  1668,  1669,
    1670,  1671,  1672,  1673,  1674,  1675,  1676,  1677,  1678,  1681,
    1681,  1691,  1691,  1701,  1701,  1709,  1709,  1717,  1717,  1725,
    1725,  1733,  1733,  1746,  1746,  1756,  1757,  1760,  1760,  1771,
    1771,  1781,  1782,  1785,  1785,  1795,  1796,  1799,  1800,  1803,
    1804,  1805,  1806,  1807,  1808,  1809,  1812,  1814,  1814,  1822,
    1830,  1830,  1842,  1843,  1846,  1847,  1848,  1849,  1850,  1851,
    1852,  1853,  1854,  1857,  1857,  1864,  1865,  1866,  1869,  1874,
    1874,  1882,  1887,  1894,  1901,  1901,  1911,  1912,  1915,  1916,
    1917,  1918,  1919,  1922,  1922,  1930,  1930,  1940,  1940,  1980,
    1980,  1992,  1992,  2002,  2003,  2006,  2007,  2008,  2009,  2010,
    2011,  2012,  2013,  2014,  2015,  2016,  2017,  2018,  2019,  2020,
    2021,  2022,  2023,  2026,  2031,  2031,  2039,  2039,  2047,  2052,
    2052,  2060,  2065,  2070,  2070,  2078,  2079,  2082,  2082,  2090,
    2095,  2100,  2100,  2108,  2111,  2114,  2117,  2120,  2126,  2126,
    2134,  2134,  2142,  2142,  2152,  2152,  2159,  2159,  2166,  2166,
    2175,  2175,  2186,  2186,  2196,  2197,  2201,  2204,  2204,  2219,
    2219,  2229,  2229,  2240,  2241,  2245,  2249,  2249,  2261,  2262,
    2266,  2266,  2274,  2275,  2278,  2279,  2280,  2281,  2282,  2283,
    2284,  2287,  2292,  2292,  2300,  2300,  2310,  2311,  2314,  2314,
    2322,  2323,  2326,  2327,  2328,  2329,  2332,  2332,  2340,  2345,
    2350
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


#line 14 "dhcp6_parser.yy" // lalr1.cc:1242
} } // isc::dhcp
#line 5098 "dhcp6_parser.cc" // lalr1.cc:1242
#line 2355 "dhcp6_parser.yy" // lalr1.cc:1243


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
