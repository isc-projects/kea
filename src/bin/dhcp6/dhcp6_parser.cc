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
      case 194: // value
      case 198: // map_value
      case 252: // db_type
      case 345: // hr_mode
      case 481: // duid_type
      case 516: // ncr_protocol_value
      case 523: // replace_client_name_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 176: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 175: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 174: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 173: // "constant string"
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
      case 194: // value
      case 198: // map_value
      case 252: // db_type
      case 345: // hr_mode
      case 481: // duid_type
      case 516: // ncr_protocol_value
      case 523: // replace_client_name_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 176: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 175: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 174: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 173: // "constant string"
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
      case 194: // value
      case 198: // map_value
      case 252: // db_type
      case 345: // hr_mode
      case 481: // duid_type
      case 516: // ncr_protocol_value
      case 523: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 176: // "boolean"
        value.move< bool > (that.value);
        break;

      case 175: // "floating point"
        value.move< double > (that.value);
        break;

      case 174: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 173: // "constant string"
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
      case 173: // "constant string"
#line 251 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < std::string > (); }
#line 404 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 174: // "integer"
#line 251 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 410 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 175: // "floating point"
#line 251 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < double > (); }
#line 416 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 176: // "boolean"
#line 251 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < bool > (); }
#line 422 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 194: // value
#line 251 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 198: // map_value
#line 251 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 434 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 252: // db_type
#line 251 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 440 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 345: // hr_mode
#line 251 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 446 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 481: // duid_type
#line 251 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 452 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 516: // ncr_protocol_value
#line 251 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 458 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 523: // replace_client_name_value
#line 251 "dhcp6_parser.yy" // lalr1.cc:676
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
      case 194: // value
      case 198: // map_value
      case 252: // db_type
      case 345: // hr_mode
      case 481: // duid_type
      case 516: // ncr_protocol_value
      case 523: // replace_client_name_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 176: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 175: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 174: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 173: // "constant string"
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
#line 260 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 730 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 4:
#line 261 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.CONFIG; }
#line 736 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 6:
#line 262 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP6; }
#line 742 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 8:
#line 263 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 748 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 10:
#line 264 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.SUBNET6; }
#line 754 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 12:
#line 265 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.POOLS; }
#line 760 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 14:
#line 266 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 766 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 16:
#line 267 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 772 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 18:
#line 268 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP6; }
#line 778 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 20:
#line 269 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 784 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 22:
#line 270 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 790 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 24:
#line 271 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 796 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 26:
#line 272 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 802 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 28:
#line 273 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.LOGGING; }
#line 808 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 30:
#line 274 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 814 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 32:
#line 282 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 820 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 33:
#line 283 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 826 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 34:
#line 284 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 832 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 35:
#line 285 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 838 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 36:
#line 286 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 844 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 37:
#line 287 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 850 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 38:
#line 288 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 856 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 39:
#line 291 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 865 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 40:
#line 296 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 876 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 41:
#line 301 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 886 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 42:
#line 307 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 892 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 45:
#line 314 "dhcp6_parser.yy" // lalr1.cc:919
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 901 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 46:
#line 318 "dhcp6_parser.yy" // lalr1.cc:919
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 911 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 47:
#line 325 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 920 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 48:
#line 328 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // list parsing complete. Put any sanity checking here
}
#line 928 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 51:
#line 336 "dhcp6_parser.yy" // lalr1.cc:919
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 937 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 52:
#line 340 "dhcp6_parser.yy" // lalr1.cc:919
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 946 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 53:
#line 347 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // List parsing about to start
}
#line 954 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 54:
#line 349 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 963 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 57:
#line 358 "dhcp6_parser.yy" // lalr1.cc:919
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 972 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 58:
#line 362 "dhcp6_parser.yy" // lalr1.cc:919
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 981 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 59:
#line 373 "dhcp6_parser.yy" // lalr1.cc:919
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 992 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 60:
#line 383 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1003 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 61:
#line 388 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 411 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 418 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1039 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 72:
#line 426 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1049 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 73:
#line 430 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No global parameter is required
    // parsing completed
}
#line 1058 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 110:
#line 477 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1066 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 111:
#line 479 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1076 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 112:
#line 485 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1085 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 113:
#line 490 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1094 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 114:
#line 495 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1103 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 115:
#line 500 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1112 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 116:
#line 505 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 117:
#line 510 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1129 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 118:
#line 512 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1139 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 119:
#line 518 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1150 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 120:
#line 523 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1160 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 121:
#line 529 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1170 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 122:
#line 533 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1179 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 130:
#line 549 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1190 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 131:
#line 554 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1199 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 132:
#line 559 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1208 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 133:
#line 565 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1219 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 134:
#line 570 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1230 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 135:
#line 577 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1241 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 136:
#line 582 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1252 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 137:
#line 589 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1263 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 138:
#line 594 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1272 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 143:
#line 607 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1282 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 144:
#line 611 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1292 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 167:
#line 643 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1300 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 168:
#line 645 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1309 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 169:
#line 650 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1315 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 170:
#line 651 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1321 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 171:
#line 652 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1327 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 172:
#line 653 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1333 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 173:
#line 656 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1341 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 174:
#line 658 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1351 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 175:
#line 664 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1359 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 176:
#line 666 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1369 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 177:
#line 672 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1377 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 178:
#line 674 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1387 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 179:
#line 680 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1396 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 180:
#line 685 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1404 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 181:
#line 687 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1414 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 182:
#line 693 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1423 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 183:
#line 698 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1432 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 184:
#line 703 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1441 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 185:
#line 708 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1450 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 186:
#line 713 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1459 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 187:
#line 718 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1468 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 188:
#line 723 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1477 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 189:
#line 728 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1486 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 190:
#line 733 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1494 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 191:
#line 735 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1504 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 192:
#line 741 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1513 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 193:
#line 746 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1521 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 194:
#line 748 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1531 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 195:
#line 754 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1539 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 196:
#line 756 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1549 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 197:
#line 762 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1557 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 198:
#line 764 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1567 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 199:
#line 770 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1578 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 200:
#line 775 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1587 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 204:
#line 785 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1595 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 205:
#line 787 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 1615 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 206:
#line 803 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1626 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 207:
#line 808 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1635 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 212:
#line 821 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1644 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 213:
#line 826 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1653 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 214:
#line 831 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1664 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 215:
#line 836 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1673 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 221:
#line 850 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1682 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 222:
#line 855 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1691 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 223:
#line 862 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1702 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 224:
#line 867 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1711 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 225:
#line 872 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1722 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 226:
#line 877 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1731 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 231:
#line 890 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1741 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 232:
#line 894 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1751 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 233:
#line 900 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1761 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 234:
#line 904 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1771 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 240:
#line 919 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1779 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 241:
#line 921 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1789 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 242:
#line 927 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1797 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 243:
#line 929 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1806 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 244:
#line 935 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1817 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 245:
#line 940 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1827 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 254:
#line 958 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1836 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 255:
#line 963 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1845 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 256:
#line 968 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1854 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 257:
#line 973 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1863 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 258:
#line 978 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1872 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 259:
#line 983 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1881 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 260:
#line 991 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1892 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 261:
#line 996 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1901 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 266:
#line 1016 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1911 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 267:
#line 1020 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 1937 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 268:
#line 1042 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1947 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 269:
#line 1046 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1957 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 292:
#line 1080 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1965 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 293:
#line 1082 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1975 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 294:
#line 1088 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1983 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 295:
#line 1090 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1993 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 296:
#line 1096 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2001 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 297:
#line 1098 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2011 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 298:
#line 1104 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2019 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 299:
#line 1106 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2029 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 300:
#line 1112 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2040 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 301:
#line 1117 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2049 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 302:
#line 1122 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2057 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 303:
#line 1124 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2066 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 304:
#line 1129 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2072 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 305:
#line 1130 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2078 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 306:
#line 1131 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2084 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 307:
#line 1132 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2090 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 308:
#line 1135 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2099 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 309:
#line 1140 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2108 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 310:
#line 1148 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2119 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 311:
#line 1153 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2128 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 316:
#line 1168 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2138 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 317:
#line 1172 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 2146 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 337:
#line 1203 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2157 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 338:
#line 1208 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2166 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 339:
#line 1216 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2175 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 340:
#line 1219 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 2183 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 345:
#line 1235 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2193 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 346:
#line 1239 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2205 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 347:
#line 1250 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2215 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 348:
#line 1254 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2227 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 364:
#line 1286 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2236 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 366:
#line 1293 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2244 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 367:
#line 1295 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2254 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 368:
#line 1301 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2262 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 369:
#line 1303 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2272 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 370:
#line 1309 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2280 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 371:
#line 1311 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2290 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 373:
#line 1319 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2298 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 374:
#line 1321 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2308 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 375:
#line 1327 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2317 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 376:
#line 1336 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2328 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 377:
#line 1341 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2337 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 382:
#line 1360 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2347 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 383:
#line 1364 "dhcp6_parser.yy" // lalr1.cc:919
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2356 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 384:
#line 1372 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2366 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 385:
#line 1376 "dhcp6_parser.yy" // lalr1.cc:919
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2375 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 400:
#line 1409 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2383 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 401:
#line 1411 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2393 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 404:
#line 1421 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2402 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 405:
#line 1426 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2411 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 406:
#line 1434 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2422 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 407:
#line 1439 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2431 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 412:
#line 1454 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2441 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 413:
#line 1458 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2451 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 414:
#line 1464 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2461 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 415:
#line 1468 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2470 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 425:
#line 1486 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2478 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 426:
#line 1488 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2488 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 427:
#line 1494 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2496 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 428:
#line 1496 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 2523 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 429:
#line 1519 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2531 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 430:
#line 1521 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 2560 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 431:
#line 1549 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2571 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 432:
#line 1554 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2580 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 437:
#line 1569 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2590 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 438:
#line 1573 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2602 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 439:
#line 1581 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2612 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 440:
#line 1585 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2624 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 454:
#line 1610 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2632 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 455:
#line 1612 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2642 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 456:
#line 1618 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2651 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 457:
#line 1623 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2659 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 458:
#line 1625 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2669 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 459:
#line 1631 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2678 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 460:
#line 1636 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2687 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 461:
#line 1644 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2698 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 462:
#line 1649 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2707 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 467:
#line 1662 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2717 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 468:
#line 1666 "dhcp6_parser.yy" // lalr1.cc:919
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2726 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 469:
#line 1671 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2736 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 470:
#line 1675 "dhcp6_parser.yy" // lalr1.cc:919
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2745 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 486:
#line 1702 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2756 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 487:
#line 1707 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2765 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 488:
#line 1712 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2776 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 489:
#line 1717 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2785 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 490:
#line 1722 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2793 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 491:
#line 1724 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2803 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 492:
#line 1730 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2811 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 493:
#line 1732 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2821 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 494:
#line 1738 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2829 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 495:
#line 1740 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2839 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 496:
#line 1746 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2847 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 497:
#line 1748 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2857 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 498:
#line 1754 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2868 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 499:
#line 1759 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2877 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 500:
#line 1767 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2888 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 501:
#line 1772 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2897 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 504:
#line 1781 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2905 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 505:
#line 1783 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2915 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 506:
#line 1792 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2926 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 507:
#line 1797 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2935 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 510:
#line 1806 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2945 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 511:
#line 1810 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2955 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 524:
#line 1835 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2963 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 525:
#line 1837 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2973 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 526:
#line 1843 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2982 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 527:
#line 1851 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2993 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 528:
#line 1856 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3004 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 540:
#line 1878 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 3012 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 541:
#line 1880 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3021 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 542:
#line 1885 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3027 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 543:
#line 1886 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3033 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 544:
#line 1887 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3039 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 545:
#line 1890 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3048 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 546:
#line 1895 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3056 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 547:
#line 1897 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3066 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 548:
#line 1903 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3075 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 549:
#line 1908 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3084 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 550:
#line 1915 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3093 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 551:
#line 1922 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3104 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 552:
#line 1927 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3113 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 560:
#line 1943 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3121 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 561:
#line 1945 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3131 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 562:
#line 1951 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3139 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 563:
#line 1953 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3149 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 564:
#line 1961 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3157 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 565:
#line 1963 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 3197 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 566:
#line 2001 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3208 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 567:
#line 2006 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3219 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 568:
#line 2013 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3229 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 569:
#line 2017 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3239 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 590:
#line 2047 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3248 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 591:
#line 2052 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3256 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 592:
#line 2054 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3266 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 593:
#line 2060 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3274 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 594:
#line 2062 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3284 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 595:
#line 2068 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3293 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 596:
#line 2073 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3301 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 597:
#line 2075 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3311 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 598:
#line 2081 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3320 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 599:
#line 2086 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3329 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 600:
#line 2091 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3337 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 601:
#line 2093 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3346 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 602:
#line 2099 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3352 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 603:
#line 2100 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3358 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 604:
#line 2103 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3366 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 605:
#line 2105 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3376 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 606:
#line 2111 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3385 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 607:
#line 2116 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3394 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 608:
#line 2121 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3402 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 609:
#line 2123 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3411 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 610:
#line 2129 "dhcp6_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3419 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 611:
#line 2132 "dhcp6_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3427 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 612:
#line 2135 "dhcp6_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3435 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 613:
#line 2138 "dhcp6_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3443 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 614:
#line 2141 "dhcp6_parser.yy" // lalr1.cc:919
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3452 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 615:
#line 2147 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3460 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 616:
#line 2149 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3470 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 617:
#line 2155 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3478 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 618:
#line 2157 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3488 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 619:
#line 2163 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3496 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 620:
#line 2165 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3506 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 621:
#line 2173 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3514 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 622:
#line 2175 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3523 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 623:
#line 2180 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3531 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 624:
#line 2182 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3540 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 625:
#line 2187 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3548 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 626:
#line 2189 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3557 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 627:
#line 2196 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3568 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 628:
#line 2201 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3578 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 629:
#line 2207 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3588 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 630:
#line 2211 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No config_control params are required
    // parsing completed
}
#line 3597 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 634:
#line 2225 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3608 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 635:
#line 2230 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3617 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 636:
#line 2240 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3628 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 637:
#line 2245 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3637 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 638:
#line 2250 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3647 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 639:
#line 2254 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 3655 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 643:
#line 2270 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3666 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 644:
#line 2275 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3675 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 647:
#line 2287 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3685 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 648:
#line 2291 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 3693 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 658:
#line 2308 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3702 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 659:
#line 2313 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3710 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 660:
#line 2315 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3720 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 661:
#line 2321 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3731 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 662:
#line 2326 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3740 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 665:
#line 2335 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3750 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 666:
#line 2339 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 3758 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 673:
#line 2353 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3766 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 674:
#line 2355 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3776 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 675:
#line 2361 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3785 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 676:
#line 2366 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3794 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 677:
#line 2371 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3803 "dhcp6_parser.cc" // lalr1.cc:919
    break;


#line 3807 "dhcp6_parser.cc" // lalr1.cc:919
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


  const short Dhcp6Parser::yypact_ninf_ = -845;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     427,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,    44,    36,    41,    66,
      80,    94,   101,   168,   177,   194,   215,   226,   228,   279,
     286,   287,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,    36,  -113,    23,    67,    56,   238,   126,   384,
     131,   225,    69,   410,   -19,   361,    -4,   283,  -845,   291,
     300,   301,   306,   340,  -845,  -845,  -845,  -845,  -845,   347,
    -845,   136,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,   355,   357,   364,   365,   373,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,   381,  -845,  -845,  -845,
    -845,  -845,   137,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,   392,  -845,
     138,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,   394,   396,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,   149,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,   152,  -845,  -845,  -845,  -845,  -845,   402,
    -845,   408,   409,  -845,  -845,  -845,  -845,  -845,  -845,   156,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,   380,   362,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,   406,  -845,  -845,
     414,  -845,  -845,  -845,   417,  -845,  -845,   415,   423,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,   424,   428,  -845,  -845,  -845,  -845,   425,   433,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,   158,  -845,  -845,  -845,   434,  -845,  -845,   435,
    -845,   437,   438,  -845,  -845,   439,   440,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,   160,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,   180,  -845,  -845,  -845,   189,  -845,  -845,  -845,    36,
      36,  -845,   272,   450,   451,   452,   453,   454,  -845,    23,
    -845,   455,   463,   464,   465,   466,   468,   299,   302,   303,
     307,   324,   471,   476,   495,   496,   497,   498,   499,   500,
     503,   504,   505,   506,   507,   508,   509,   510,   511,   343,
     514,   515,   516,   517,    67,  -845,   518,   255,    56,  -845,
     520,   521,   522,   523,   524,   358,   353,   527,   529,   531,
     238,  -845,   532,   126,  -845,   533,   366,   534,   368,   369,
     384,  -845,   535,   540,   541,   542,   543,   546,   548,  -845,
     131,  -845,   549,   550,   382,   551,   554,   555,   385,  -845,
      69,   556,   386,   388,  -845,   410,   561,   564,    32,  -845,
     395,   566,   568,   400,   569,   401,   403,   572,   574,   404,
     405,   575,   596,   597,   598,   361,  -845,    -4,  -845,   599,
     283,  -845,  -845,  -845,   600,   602,   604,    36,    36,    36,
    -845,   432,   605,   606,   607,   608,   601,  -845,  -845,  -845,
    -845,  -845,   443,   612,   613,   614,   615,   447,    53,   616,
     618,   619,   620,   621,   622,   624,   625,   626,   627,  -845,
     628,   615,   629,   632,  -845,   633,  -845,  -845,   634,   635,
     458,   459,   469,  -845,  -845,   633,   470,   637,  -845,   472,
    -845,   473,  -845,   474,  -845,  -845,  -845,   633,   633,   633,
     475,   477,   478,   479,  -845,   480,   481,  -845,   482,   483,
     484,  -845,  -845,   485,  -845,  -845,  -845,   486,    36,  -845,
    -845,   487,   488,  -845,   489,  -845,  -845,   134,   502,  -845,
    -845,   -86,   490,   491,   492,  -845,  -845,   644,  -845,    36,
      67,    -4,  -845,  -845,  -845,  -845,   283,    56,   218,   218,
     659,  -845,   660,   661,   662,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,   663,   -54,    36,   124,   586,   665,   666,
     667,    -9,   162,   -17,  -845,   361,   668,  -845,  -845,   669,
     670,  -845,  -845,  -845,  -845,  -845,   -50,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,   659,  -845,   195,   212,   229,   231,  -845,  -845,  -845,
    -845,   674,   675,   676,   677,   678,  -845,   679,   680,  -845,
    -845,  -845,   681,   682,   683,  -845,   233,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,   257,  -845,   684,
     623,  -845,  -845,   685,   686,  -845,  -845,   687,   689,  -845,
    -845,   688,   692,  -845,  -845,   690,   694,  -845,  -845,  -845,
      63,  -845,  -845,  -845,   693,  -845,  -845,  -845,    85,  -845,
    -845,  -845,  -845,   258,  -845,  -845,  -845,   115,  -845,  -845,
     695,   697,  -845,  -845,   696,   700,  -845,   701,   702,   703,
     704,   705,   706,   267,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,   707,   708,   709,  -845,  -845,  -845,  -845,
     281,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,   284,  -845,  -845,  -845,   319,  -845,   159,  -845,
     525,  -845,   698,   711,  -845,  -845,   710,   712,  -845,  -845,
    -845,   713,  -845,   714,  -845,  -845,  -845,  -845,   715,   718,
     719,   720,   544,   512,   552,   553,   557,   721,   558,   559,
     723,   724,   726,   560,   562,   563,   218,  -845,  -845,   218,
    -845,   659,   238,  -845,   660,    69,  -845,   661,   410,  -845,
     662,   273,  -845,   663,   -54,  -845,  -845,   124,  -845,   731,
     586,  -845,   251,   665,  -845,   131,  -845,   666,   -19,  -845,
     667,   567,   570,   571,   573,   576,   577,    -9,  -845,   733,
     734,   578,   579,   580,   162,  -845,   736,   738,   -17,  -845,
    -845,   222,   668,  -845,  -845,   737,   743,   126,  -845,   669,
     384,  -845,   670,   744,  -845,  -845,   150,   582,   583,   584,
    -845,  -845,  -845,  -845,  -845,   585,  -845,  -845,   587,   588,
     589,  -845,  -845,  -845,  -845,   323,  -845,   329,  -845,   741,
    -845,   751,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,   330,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,   590,  -845,  -845,   760,  -845,
    -845,  -845,  -845,  -845,   757,   763,  -845,  -845,  -845,  -845,
    -845,   759,  -845,   350,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,   151,   595,  -845,  -845,  -845,  -845,   603,   610,
    -845,  -845,   765,  -845,  -845,  -845,  -845,  -845,   372,  -845,
    -845,  -845,  -845,  -845,  -845,   638,   375,  -845,   389,  -845,
     640,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,   273,  -845,  -845,
     766,   609,  -845,   251,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,   767,   636,   768,   222,  -845,  -845,  -845,
    -845,  -845,  -845,   645,  -845,  -845,   769,  -845,   655,  -845,
    -845,   770,  -845,  -845,   199,  -845,   -47,   770,  -845,  -845,
     771,   775,   776,   399,  -845,  -845,  -845,  -845,  -845,  -845,
     782,   617,   658,   673,   -47,  -845,   656,  -845,  -845,  -845,
    -845,  -845
  };

  const unsigned short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   121,     9,
     268,    11,   414,    13,   439,    15,   469,    17,   339,    19,
     347,    21,   384,    23,   233,    25,   568,    27,   638,    29,
     629,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     471,     0,   349,   386,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   636,   621,   623,   625,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   110,   627,
     119,   133,   135,   137,     0,     0,     0,     0,     0,   117,
     260,   337,   376,   427,   429,   302,   310,   206,   223,   214,
     199,   506,   461,   225,   244,   527,     0,   551,   564,   566,
     643,   109,     0,    74,    76,    77,    78,    79,    80,    81,
     106,    84,    85,    86,    87,   103,    88,    90,    89,    94,
      95,    82,   107,    83,    92,    93,   101,   102,   104,    91,
      96,    97,    98,    99,   100,   105,   108,   130,     0,   129,
       0,   123,   125,   126,   127,   128,   406,   431,   292,   294,
     296,     0,     0,   300,   298,   500,   291,   272,   273,   274,
     275,     0,   270,   279,   280,   281,   284,   285,   287,   282,
     283,   276,   277,   289,   290,   278,   286,   288,   425,   424,
     420,   421,   419,     0,   416,   418,   422,   423,   454,     0,
     457,     0,     0,   453,   447,   448,   446,   451,   452,     0,
     441,   443,   444,   449,   450,   445,   498,   486,   488,   490,
     492,   494,   496,   485,   482,   483,   484,     0,   472,   473,
     477,   478,   475,   479,   480,   481,   476,     0,   366,   180,
       0,   370,   368,   373,     0,   362,   363,     0,   350,   351,
     353,   365,   354,   355,   356,   372,   357,   358,   359,   360,
     361,   400,     0,     0,   398,   399,   402,   403,     0,   387,
     388,   390,   391,   392,   393,   394,   395,   396,   397,   240,
     242,   237,     0,   235,   238,   239,     0,   591,   593,     0,
     596,     0,     0,   600,   604,     0,     0,   608,   615,   617,
     619,   589,   587,   588,     0,   570,   572,   573,   574,   575,
     576,   577,   578,   579,   580,   581,   582,   583,   584,   585,
     586,     0,   640,   642,   634,     0,   631,   633,    48,     0,
       0,    41,     0,     0,     0,     0,     0,     0,    59,     0,
      61,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    73,     0,     0,     0,   122,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   269,     0,     0,   415,     0,     0,     0,     0,     0,
       0,   440,     0,     0,     0,     0,     0,     0,     0,   470,
       0,   340,     0,     0,     0,     0,     0,     0,     0,   348,
       0,     0,     0,     0,   385,     0,     0,     0,     0,   234,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   569,     0,   639,     0,
       0,   630,    52,    45,     0,     0,     0,     0,     0,     0,
      63,     0,     0,     0,     0,     0,     0,   112,   113,   114,
     115,   116,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   550,
       0,     0,     0,     0,    75,     0,   132,   124,     0,     0,
       0,     0,     0,   308,   309,     0,     0,     0,   271,     0,
     417,     0,   456,     0,   459,   460,   442,     0,     0,     0,
       0,     0,     0,     0,   474,     0,     0,   364,     0,     0,
       0,   375,   352,     0,   404,   405,   389,     0,     0,   236,
     590,     0,     0,   595,     0,   598,   599,     0,     0,   606,
     607,     0,     0,     0,     0,   571,   641,     0,   632,     0,
       0,     0,   622,   624,   626,   111,     0,     0,     0,     0,
     139,   118,   262,   341,   378,    42,   428,   430,   304,   305,
     306,   307,   303,   312,     0,    49,     0,     0,     0,   463,
     227,     0,     0,     0,   565,     0,     0,    53,   131,   408,
     433,   293,   295,   297,   301,   299,     0,   426,   455,   458,
     499,   487,   489,   491,   493,   495,   497,   367,   181,   371,
     369,   374,   401,   241,   243,   592,   594,   597,   602,   603,
     601,   605,   610,   611,   612,   613,   614,   609,   616,   618,
     620,   139,    46,     0,     0,     0,     0,   167,   173,   175,
     177,     0,     0,     0,     0,     0,   190,     0,     0,   193,
     195,   197,     0,     0,     0,   166,     0,   145,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   159,   160,
     161,   162,   157,   158,   163,   164,   165,     0,   143,     0,
     140,   141,   266,     0,   263,   264,   345,     0,   342,   343,
     382,     0,   379,   380,   316,     0,   313,   314,   212,   213,
       0,   208,   210,   211,     0,   221,   222,   218,     0,   216,
     219,   220,   204,     0,   201,   203,   510,     0,   508,   467,
       0,   464,   465,   231,     0,   228,   229,     0,     0,     0,
       0,     0,     0,     0,   246,   248,   249,   250,   251,   252,
     253,   540,   546,     0,     0,     0,   539,   536,   537,   538,
       0,   529,   531,   534,   532,   533,   535,   560,   562,   559,
     557,   558,     0,   553,   555,   556,     0,   647,     0,   645,
      55,   412,     0,   409,   410,   437,     0,   434,   435,   504,
     503,     0,   502,     0,    71,   637,   628,   120,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   134,   136,     0,
     138,     0,     0,   261,     0,   349,   338,     0,   386,   377,
       0,     0,   311,     0,     0,   207,   224,     0,   215,     0,
       0,   200,   512,     0,   507,   471,   462,     0,     0,   226,
       0,     0,     0,     0,     0,     0,     0,     0,   245,     0,
       0,     0,     0,     0,     0,   528,     0,     0,     0,   552,
     567,     0,     0,   644,    57,     0,    56,     0,   407,     0,
       0,   432,     0,     0,   501,   635,     0,     0,     0,     0,
     179,   182,   183,   184,   185,     0,   192,   186,     0,     0,
       0,   187,   188,   189,   146,     0,   142,     0,   265,     0,
     344,     0,   381,   336,   331,   333,   324,   325,   320,   321,
     322,   323,   329,   330,   328,   332,     0,   318,   326,   334,
     335,   327,   315,   209,   217,     0,   202,   524,     0,   522,
     523,   519,   520,   521,     0,   513,   514,   516,   517,   518,
     509,     0,   466,     0,   230,   254,   255,   256,   257,   258,
     259,   247,     0,     0,   545,   548,   549,   530,     0,     0,
     554,   661,     0,   659,   657,   651,   655,   656,     0,   649,
     653,   654,   652,   646,    54,     0,     0,   411,     0,   436,
       0,   169,   170,   171,   172,   168,   174,   176,   178,   191,
     194,   196,   198,   144,   267,   346,   383,     0,   317,   205,
       0,     0,   511,     0,   468,   232,   542,   543,   544,   541,
     547,   561,   563,     0,     0,     0,     0,   648,    58,   413,
     438,   505,   319,     0,   526,   515,     0,   658,     0,   650,
     525,     0,   660,   665,     0,   663,     0,     0,   662,   673,
       0,     0,     0,     0,   667,   669,   670,   671,   672,   664,
       0,     0,     0,     0,     0,   666,     0,   675,   676,   677,
     668,   674
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,    -5,  -845,  -468,
    -845,   196,  -845,  -845,  -845,  -845,   173,  -845,  -455,  -845,
    -845,  -845,   -74,  -845,  -845,  -845,   426,  -845,  -845,  -845,
    -845,   183,   393,  -845,  -845,   -70,   -58,   -38,   -31,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,   203,   398,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,   121,  -845,   -43,
    -845,  -581,   -39,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,   -46,  -845,  -609,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,   -36,  -845,  -845,  -845,  -845,
    -845,   -29,  -600,  -845,  -845,  -845,  -845,   -28,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,   -32,  -845,  -845,  -845,
     -34,   407,  -845,  -845,  -845,  -845,  -845,  -845,  -845,   -37,
    -845,  -845,  -845,  -845,  -845,  -845,  -844,  -845,  -845,  -845,
      -2,  -845,  -845,  -845,     1,   436,  -845,  -845,  -833,  -845,
    -831,  -845,   -44,  -845,   -20,  -845,   -30,  -845,  -845,  -845,
    -830,  -845,  -845,  -845,  -845,    -1,  -845,  -845,  -178,   780,
    -845,  -845,  -845,  -845,  -845,     7,  -845,  -845,  -845,    12,
    -845,   418,  -845,   -68,  -845,  -845,  -845,  -845,  -845,   -33,
    -845,  -845,  -845,  -845,  -845,    -3,  -845,  -845,  -845,    10,
    -845,  -845,  -845,    13,  -845,   419,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,   -27,  -845,  -845,
    -845,   -26,   457,  -845,  -845,   -56,  -845,   -15,  -845,  -845,
    -845,  -845,  -845,   -35,  -845,  -845,  -845,   -25,   445,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,   -63,  -845,  -845,  -845,
      11,  -845,  -845,  -845,     3,  -845,   444,   237,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -829,  -845,  -845,  -845,  -845,  -845,  -845,  -845,    16,
    -845,  -845,  -845,  -167,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,     0,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,    -7,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,   268,   421,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,   304,   422,  -845,  -845,  -845,  -845,  -845,
    -845,   308,   420,   -61,  -845,  -845,     4,  -845,  -845,  -158,
    -845,  -845,  -845,  -845,  -845,  -845,  -176,  -845,  -845,  -191,
    -845,  -845,  -845,  -845,  -845
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   606,    92,    93,    43,    72,    89,    90,   628,   810,
     905,   906,   695,    45,    74,   101,   102,   103,   363,    47,
      75,   142,   143,   144,   371,   145,   146,   147,   148,   149,
     150,   382,   151,   373,    49,    76,   180,   181,   182,   406,
     183,   152,   374,   153,   375,   154,   376,   719,   720,   721,
     849,   696,   697,   698,   828,  1025,   699,   829,   700,   830,
     701,   831,   702,   703,   443,   704,   705,   706,   707,   708,
     709,   710,   711,   712,   837,   713,   714,   840,   715,   841,
     716,   842,   155,   393,   753,   754,   755,   869,   156,   390,
     740,   741,   742,   743,   157,   392,   748,   749,   750,   751,
     158,   391,   159,   396,   764,   765,   766,   878,    65,    84,
     312,   313,   314,   456,   315,   457,   160,   397,   773,   774,
     775,   776,   777,   778,   779,   780,   161,   383,   723,   724,
     725,   852,    51,    77,   201,   202,   203,   412,   204,   413,
     205,   414,   206,   418,   207,   417,   162,   388,   612,   209,
     210,   163,   389,   735,   736,   737,   861,   956,   957,   164,
     384,    59,    81,   727,   728,   729,   855,    61,    82,   277,
     278,   279,   280,   281,   282,   283,   442,   284,   446,   285,
     445,   286,   287,   447,   288,   165,   385,   731,   732,   733,
     858,    63,    83,   298,   299,   300,   301,   302,   451,   303,
     304,   305,   306,   212,   410,   812,   813,   814,   907,    53,
      78,   223,   224,   225,   422,   166,   386,   167,   387,   215,
     411,   816,   817,   818,   910,    55,    79,   239,   240,   241,
     425,   242,   243,   427,   244,   245,   168,   395,   760,   761,
     762,   875,    57,    80,   257,   258,   259,   260,   433,   261,
     434,   262,   435,   263,   436,   264,   437,   265,   438,   266,
     432,   217,   419,   821,   822,   913,   169,   394,   757,   758,
     872,   974,   975,   976,   977,   978,  1040,   979,   170,   398,
     790,   791,   792,   889,  1049,   793,   794,   890,   795,   796,
     171,   172,   400,   802,   803,   804,   896,   805,   897,   173,
     401,   174,   402,    67,    85,   334,   335,   336,   337,   461,
     338,   462,   339,   340,   464,   341,   342,   343,   467,   660,
     344,   468,   345,   346,   347,   471,   667,   348,   472,   349,
     473,   350,   474,   104,   365,   105,   366,   106,   367,   175,
     372,    71,    87,   355,   356,   357,   479,   107,   364,    69,
      86,   351,   352,   176,   403,   808,   809,   901,  1008,  1009,
    1010,  1011,  1055,  1012,  1053,  1074,  1075,  1076,  1083,  1084,
    1085,  1090,  1086,  1087,  1088
  };

  const unsigned short
  Dhcp6Parser::yytable_[] =
  {
     100,   141,   179,   196,   219,   233,   253,   197,   275,   294,
     311,   331,    40,   787,   216,   296,   747,   949,   717,   198,
     184,   213,   226,   237,   255,   353,   289,   307,   950,   332,
     951,   955,   961,    94,   220,   234,   276,   295,   605,   199,
     738,    33,   247,    34,    32,    35,   200,   208,    44,   819,
     297,   123,   124,   605,   662,   663,   664,   665,   221,   235,
      91,   185,   214,   227,   238,   256,   864,   290,   308,   865,
     333,   177,   178,    46,   211,   222,   236,   254,   108,   109,
     634,   110,   309,   310,   111,   112,   113,    48,   867,   268,
     666,   868,   640,   641,   642,   767,   768,   769,   770,   771,
     772,    50,  1079,   797,   798,  1080,  1081,  1082,    52,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   873,   739,
     269,   874,   270,   271,   123,   124,   272,   273,   274,   608,
     609,   610,   611,   309,   310,   123,   124,   123,   124,   369,
     404,   408,   125,   140,   370,   405,   409,   126,   127,   128,
     129,   130,   420,   131,    99,   423,    99,   421,   132,   430,
     424,   458,   902,   475,   431,   903,   459,   133,   476,    95,
     134,  1021,  1022,  1023,  1024,    54,   122,   135,    96,    97,
      98,   122,   781,   477,    56,   136,   137,   218,   478,   138,
     139,   682,   480,   949,   123,   124,    99,   481,   404,   123,
     124,    58,  1077,   824,   950,  1078,   951,   955,   961,    36,
      37,    38,    39,   193,   140,   477,   194,   246,   738,   745,
     825,   746,    60,   247,   248,   249,   250,   251,   252,    99,
     123,   124,   480,    62,   408,    64,   846,   826,   677,   827,
      99,   847,    99,   678,   679,   680,   681,   682,   683,   684,
     685,   686,   687,   688,   689,   690,   691,   692,   693,   694,
     846,   870,  1046,  1047,  1048,   848,   871,   747,   935,   269,
     887,   658,   659,   269,   121,   888,   782,   783,   784,   785,
     114,   115,   116,   117,   894,   787,    66,   898,   122,   895,
     123,   124,   899,    68,    70,   100,   354,   358,   186,    99,
     187,   122,   269,   359,    99,   360,   123,   124,   188,   189,
     190,   191,   192,   125,   361,   114,   115,   116,   117,   123,
     124,   120,   475,   122,   269,   193,   846,   900,   194,   132,
     141,  1033,   420,  1037,   179,    99,   195,  1034,  1038,   967,
     968,   123,   124,   362,   189,   190,   196,   192,   125,   219,
     197,   368,   184,   458,   482,   483,   233,   216,  1045,   377,
     193,   378,   198,   194,   213,   440,   253,   226,   379,   380,
    1001,   195,  1002,  1003,   237,  1056,   275,   381,   423,   220,
    1057,   294,   199,  1059,   255,   399,   234,   296,   439,   200,
     208,    99,   430,   185,   289,    99,   407,  1060,   415,   307,
     416,   331,  1094,   221,   276,   214,   426,  1095,   227,   295,
     235,    99,   428,   429,   441,   238,   353,   211,   444,   332,
     222,   448,   297,   449,    99,   256,   450,   236,   452,   123,
     124,   526,   453,   454,   122,   290,   455,   254,   460,   463,
     308,   465,   466,   469,   470,   484,    99,   228,   229,   230,
     231,   232,   123,   124,   485,   486,   487,   488,   489,   491,
     333,   269,   291,   270,   271,   292,   293,   492,   493,   494,
     495,   193,   496,   497,   194,   502,   498,   499,   123,   124,
     503,   500,   592,   593,   594,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   501,   504,
     505,   506,   507,   508,   509,   329,   330,   510,   511,   512,
     513,   514,   515,   516,   517,   518,   141,   519,   520,   521,
     522,   523,   525,   179,   528,   529,   530,   531,   532,   534,
     353,   535,   533,   536,    99,   537,   539,   541,   543,   547,
     542,   184,   544,   545,   548,   549,   550,   551,   786,   799,
     552,   331,   553,   555,   556,   558,   557,    99,   559,   560,
     563,   561,   564,   654,   565,   567,   788,   800,   568,   332,
     571,   570,   572,   574,   573,   575,   577,   576,   578,   581,
     579,   580,   185,    99,   672,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
     582,   583,   584,   587,   589,   595,   600,   789,   801,   590,
     333,   591,   596,   597,   598,   599,   601,   602,   603,   604,
     607,   613,    34,   614,   615,   616,   851,   618,   617,   619,
     620,   631,   632,   621,   622,   623,   625,   626,   627,   629,
     630,   661,   633,   635,   636,   637,   638,   639,   643,   671,
     644,   645,   646,   647,   648,   649,   650,   651,   652,   653,
     655,   656,   657,   668,   669,   670,   718,   722,   726,   730,
     734,   752,   756,   759,   763,   807,   811,   815,   832,   833,
     834,   835,   836,   838,   839,   843,   844,   845,   921,   854,
     850,   853,   857,   856,   859,   860,   862,   863,   904,   866,
     877,   876,   879,   880,   908,   881,   882,   883,   884,   885,
     886,   891,   892,   893,   909,   912,   911,   624,   920,   916,
     915,   914,   917,   918,   919,   925,   922,   928,   929,   923,
     930,   924,   926,   927,   931,   965,   932,   992,   993,   933,
     998,   985,   999,  1014,   986,   987,  1015,   988,  1020,  1035,
     989,   990,   994,   995,   996,  1026,  1027,  1028,  1029,  1036,
    1030,  1031,  1032,  1039,  1041,  1042,  1043,  1044,  1050,  1054,
    1063,  1066,  1068,   673,  1071,  1091,  1051,  1073,   196,  1092,
    1093,   275,   197,  1052,   294,  1064,  1096,   943,   744,   216,
     296,   944,   823,  1097,   198,   490,   213,   524,   969,   289,
     676,   253,   307,   945,   311,   959,   527,   934,   936,   276,
    1067,  1058,   295,  1061,   199,   948,   972,   952,  1070,   255,
     786,   200,   208,   946,   799,   297,   970,  1004,  1072,  1101,
     947,   954,  1098,   219,   966,   963,   233,   214,   788,   964,
     290,   953,   800,   308,   983,  1006,   960,  1099,   984,   211,
     991,   226,   938,   937,   237,  1005,   538,   973,   958,  1062,
     256,   267,   962,   220,   940,   569,   234,   939,   562,   971,
     942,   941,   254,   820,   566,   546,  1065,  1019,   981,   789,
     540,  1016,  1017,   801,   554,  1018,  1007,   221,   982,   980,
     235,  1000,   227,   806,   997,   238,   585,   586,  1069,   674,
     675,  1089,   588,  1100,   222,     0,  1013,   236,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   943,     0,     0,     0,   944,     0,   969,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   945,
       0,   959,  1004,     0,     0,     0,     0,   972,     0,     0,
       0,   948,     0,   952,     0,     0,     0,   970,     0,   946,
    1006,     0,     0,     0,     0,     0,   947,   954,     0,     0,
    1005,     0,     0,     0,     0,     0,     0,   953,     0,     0,
       0,     0,   960,     0,     0,     0,     0,     0,   973,     0,
       0,     0,     0,     0,   958,     0,     0,     0,     0,     0,
     971,  1007
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    77,    82,    83,
      84,    85,    17,   622,    77,    83,   616,   861,   599,    77,
      76,    77,    78,    79,    80,    86,    82,    83,   861,    85,
     861,   861,   861,    10,    78,    79,    82,    83,   506,    77,
      94,     5,    92,     7,     0,     9,    77,    77,     7,    99,
      83,    68,    69,   521,   140,   141,   142,   143,    78,    79,
     173,    76,    77,    78,    79,    80,     3,    82,    83,     6,
      85,    15,    16,     7,    77,    78,    79,    80,    11,    12,
     535,    14,   101,   102,    17,    18,    19,     7,     3,    20,
     176,     6,   547,   548,   549,   104,   105,   106,   107,   108,
     109,     7,   149,   120,   121,   152,   153,   154,     7,    42,
      43,    44,    45,    46,    47,    48,    49,    50,     3,   173,
      51,     6,    53,    54,    68,    69,    57,    58,    59,    76,
      77,    78,    79,   101,   102,    68,    69,    68,    69,     3,
       3,     3,    75,   147,     8,     8,     8,    80,    81,    82,
      83,    84,     3,    86,   173,     3,   173,     8,    91,     3,
       8,     3,     3,     3,     8,     6,     8,   100,     8,   146,
     103,    21,    22,    23,    24,     7,    50,   110,   155,   156,
     157,    50,    20,     3,     7,   118,   119,    61,     8,   122,
     123,    29,     3,  1037,    68,    69,   173,     8,     3,    68,
      69,     7,     3,     8,  1037,     6,  1037,  1037,  1037,   173,
     174,   175,   176,    87,   147,     3,    90,    86,    94,    95,
       8,    97,     7,    92,    93,    94,    95,    96,    97,   173,
      68,    69,     3,     7,     3,     7,     3,     8,    20,     8,
     173,     8,   173,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
       3,     3,   111,   112,   113,     8,     8,   867,   849,    51,
       3,   137,   138,    51,    49,     8,   114,   115,   116,   117,
      42,    43,    44,    45,     3,   894,     7,     3,    50,     8,
      68,    69,     8,     7,     7,   369,    13,     6,    60,   173,
      62,    50,    51,     3,   173,     4,    68,    69,    70,    71,
      72,    73,    74,    75,     8,    42,    43,    44,    45,    68,
      69,    48,     3,    50,    51,    87,     3,     8,    90,    91,
     404,     8,     3,     3,   408,   173,    98,     8,     8,    88,
      89,    68,    69,     3,    71,    72,   420,    74,    75,   423,
     420,     4,   408,     3,   359,   360,   430,   420,     8,     4,
      87,     4,   420,    90,   420,     3,   440,   423,     4,     4,
     148,    98,   150,   151,   430,     3,   450,     4,     3,   423,
       8,   455,   420,     8,   440,     4,   430,   455,     8,   420,
     420,   173,     3,   408,   450,   173,     4,     8,     4,   455,
       4,   475,     3,   423,   450,   420,     4,     8,   423,   455,
     430,   173,     4,     4,     8,   430,   477,   420,     4,   475,
     423,     4,   455,     8,   173,   440,     3,   430,     4,    68,
      69,   176,     4,     8,    50,   450,     3,   440,     4,     4,
     455,     4,     4,     4,     4,   173,   173,    63,    64,    65,
      66,    67,    68,    69,     4,     4,     4,     4,     4,     4,
     475,    51,    52,    53,    54,    55,    56,     4,     4,     4,
       4,    87,     4,   174,    90,     4,   174,   174,    68,    69,
       4,   174,   487,   488,   489,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   174,     4,
       4,     4,     4,     4,     4,   144,   145,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   590,   174,     4,     4,
       4,     4,     4,   597,     4,     4,     4,     4,     4,   176,
     591,     4,   174,     4,   173,     4,     4,     4,     4,     4,
     174,   597,   174,   174,     4,     4,     4,     4,   622,   623,
       4,   625,     4,     4,     4,     4,   174,   173,     4,     4,
       4,   176,   176,   568,   176,     4,   622,   623,     4,   625,
       4,   176,     4,     4,   174,   174,     4,   174,     4,     4,
     176,   176,   597,   173,   589,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
       4,     4,     4,     4,     4,   173,     5,   622,   623,     7,
     625,     7,     7,     7,     7,     7,   173,     5,     5,     5,
     173,     5,     7,     5,     5,     5,     3,     5,     7,     5,
       5,   173,   173,     7,     7,     7,     7,     5,     5,     5,
       5,   139,   173,   173,     7,   173,   173,   173,   173,     5,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,     7,     7,     7,     7,
       7,    85,     7,     7,     7,     7,     7,     7,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   176,     3,
       6,     6,     3,     6,     6,     3,     6,     3,   173,     6,
       3,     6,     6,     3,     6,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     3,     3,     6,   521,   174,     4,
       6,     8,     4,     4,     4,     4,   174,     4,     4,   176,
       4,   174,   174,   174,   174,     4,   174,     4,     4,   176,
       4,   174,     4,     6,   174,   174,     3,   174,     4,     8,
     174,   174,   174,   174,   174,   173,   173,   173,   173,     8,
     173,   173,   173,   173,     4,     8,     3,     8,   173,     4,
       4,     4,     4,   590,     5,     4,   173,     7,   852,     4,
       4,   855,   852,   173,   858,   176,     4,   861,   615,   852,
     858,   861,   671,   176,   852,   369,   852,   404,   872,   855,
     597,   875,   858,   861,   878,   861,   408,   846,   851,   855,
     174,   173,   858,   173,   852,   861,   872,   861,   173,   875,
     894,   852,   852,   861,   898,   858,   872,   901,   173,   173,
     861,   861,   174,   907,   870,   864,   910,   852,   894,   867,
     855,   861,   898,   858,   878,   901,   861,   174,   880,   852,
     887,   907,   854,   852,   910,   901,   420,   872,   861,  1037,
     875,    81,   863,   907,   857,   458,   910,   855,   450,   872,
     860,   858,   875,   636,   455,   430,  1043,   912,   875,   894,
     423,   907,   909,   898,   440,   910,   901,   907,   877,   873,
     910,   898,   907,   625,   894,   910,   475,   477,  1056,   591,
     596,  1077,   480,  1094,   907,    -1,   902,   910,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1037,    -1,    -1,    -1,  1037,    -1,  1043,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1037,
      -1,  1037,  1056,    -1,    -1,    -1,    -1,  1043,    -1,    -1,
      -1,  1037,    -1,  1037,    -1,    -1,    -1,  1043,    -1,  1037,
    1056,    -1,    -1,    -1,    -1,    -1,  1037,  1037,    -1,    -1,
    1056,    -1,    -1,    -1,    -1,    -1,    -1,  1037,    -1,    -1,
      -1,    -1,  1037,    -1,    -1,    -1,    -1,    -1,  1043,    -1,
      -1,    -1,    -1,    -1,  1037,    -1,    -1,    -1,    -1,    -1,
    1043,  1056
  };

  const unsigned short
  Dhcp6Parser::yystos_[] =
  {
       0,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,     0,     5,     7,     9,   173,   174,   175,   176,
     194,   195,   196,   201,     7,   210,     7,   216,     7,   231,
       7,   329,     7,   406,     7,   422,     7,   439,     7,   358,
       7,   364,     7,   388,     7,   305,     7,   500,     7,   546,
       7,   538,   202,   197,   211,   217,   232,   330,   407,   423,
     440,   359,   365,   389,   306,   501,   547,   539,   194,   203,
     204,   173,   199,   200,    10,   146,   155,   156,   157,   173,
     209,   212,   213,   214,   530,   532,   534,   544,    11,    12,
      14,    17,    18,    19,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    68,    69,    75,    80,    81,    82,    83,
      84,    86,    91,   100,   103,   110,   118,   119,   122,   123,
     147,   209,   218,   219,   220,   222,   223,   224,   225,   226,
     227,   229,   238,   240,   242,   279,   285,   291,   297,   299,
     313,   323,   343,   348,   356,   382,   412,   414,   433,   463,
     475,   487,   488,   496,   498,   536,   550,    15,    16,   209,
     233,   234,   235,   237,   412,   414,    60,    62,    70,    71,
      72,    73,    74,    87,    90,    98,   209,   222,   223,   224,
     225,   331,   332,   333,   335,   337,   339,   341,   343,   346,
     347,   382,   400,   412,   414,   416,   433,   458,    61,   209,
     339,   341,   382,   408,   409,   410,   412,   414,    63,    64,
      65,    66,    67,   209,   339,   341,   382,   412,   414,   424,
     425,   426,   428,   429,   431,   432,    86,    92,    93,    94,
      95,    96,    97,   209,   382,   412,   414,   441,   442,   443,
     444,   446,   448,   450,   452,   454,   456,   356,    20,    51,
      53,    54,    57,    58,    59,   209,   260,   366,   367,   368,
     369,   370,   371,   372,   374,   376,   378,   379,   381,   412,
     414,    52,    55,    56,   209,   260,   370,   376,   390,   391,
     392,   393,   394,   396,   397,   398,   399,   412,   414,   101,
     102,   209,   307,   308,   309,   311,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   144,
     145,   209,   412,   414,   502,   503,   504,   505,   507,   509,
     510,   512,   513,   514,   517,   519,   520,   521,   524,   526,
     528,   548,   549,   550,    13,   540,   541,   542,     6,     3,
       4,     8,     3,   215,   545,   531,   533,   535,     4,     3,
       8,   221,   537,   230,   239,   241,   243,     4,     4,     4,
       4,     4,   228,   324,   357,   383,   413,   415,   344,   349,
     286,   298,   292,   280,   464,   434,   300,   314,   476,     4,
     489,   497,   499,   551,     3,     8,   236,     4,     3,     8,
     401,   417,   334,   336,   338,     4,     4,   342,   340,   459,
       3,     8,   411,     3,     8,   427,     4,   430,     4,     4,
       3,     8,   457,   445,   447,   449,   451,   453,   455,     8,
       3,     8,   373,   261,     4,   377,   375,   380,     4,     8,
       3,   395,     4,     4,     8,     3,   310,   312,     3,     8,
       4,   506,   508,     4,   511,     4,     4,   515,   518,     4,
       4,   522,   525,   527,   529,     3,     8,     3,     8,   543,
       3,     8,   194,   194,   173,     4,     4,     4,     4,     4,
     213,     4,     4,     4,     4,     4,     4,   174,   174,   174,
     174,   174,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   174,
       4,     4,     4,     4,   219,     4,   176,   234,     4,     4,
       4,     4,     4,   174,   176,     4,     4,     4,   332,     4,
     409,     4,   174,     4,   174,   174,   425,     4,     4,     4,
       4,     4,     4,     4,   443,     4,     4,   174,     4,     4,
       4,   176,   368,     4,   176,   176,   392,     4,     4,   308,
     176,     4,     4,   174,     4,   174,   174,     4,     4,   176,
     176,     4,     4,     4,     4,   503,   549,     4,   541,     4,
       7,     7,   194,   194,   194,   173,     7,     7,     7,     7,
       5,   173,     5,     5,     5,   196,   198,   173,    76,    77,
      78,    79,   345,     5,     5,     5,     5,     7,     5,     5,
       5,     7,     7,     7,   198,     7,     5,     5,   205,     5,
       5,   173,   173,   173,   205,   173,     7,   173,   173,   173,
     205,   205,   205,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   194,   173,   173,   173,   137,   138,
     516,   139,   140,   141,   142,   143,   176,   523,   173,   173,
     173,     5,   194,   218,   548,   540,   233,    20,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,   209,   248,   249,   250,   253,
     255,   257,   259,   260,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   272,   273,   275,   277,   248,     7,   244,
     245,   246,     7,   325,   326,   327,     7,   360,   361,   362,
       7,   384,   385,   386,     7,   350,   351,   352,    94,   173,
     287,   288,   289,   290,   203,    95,    97,   289,   293,   294,
     295,   296,    85,   281,   282,   283,     7,   465,   466,     7,
     435,   436,   437,     7,   301,   302,   303,   104,   105,   106,
     107,   108,   109,   315,   316,   317,   318,   319,   320,   321,
     322,    20,   114,   115,   116,   117,   209,   262,   412,   414,
     477,   478,   479,   482,   483,   485,   486,   120,   121,   209,
     412,   414,   490,   491,   492,   494,   502,     7,   552,   553,
     206,     7,   402,   403,   404,     7,   418,   419,   420,    99,
     444,   460,   461,   244,     8,     8,     8,     8,   251,   254,
     256,   258,     4,     4,     4,     4,     4,   271,     4,     4,
     274,   276,   278,     4,     4,     4,     3,     8,     8,   247,
       6,     3,   328,     6,     3,   363,     6,     3,   387,     6,
       3,   353,     6,     3,     3,     6,     6,     3,     6,   284,
       3,     8,   467,     3,     6,   438,     6,     3,   304,     6,
       3,     4,     4,     4,     4,     4,     4,     3,     8,   480,
     484,     4,     4,     4,     3,     8,   493,   495,     3,     8,
       8,   554,     3,     6,   173,   207,   208,   405,     6,     3,
     421,     6,     3,   462,     8,     6,     4,     4,     4,     4,
     174,   176,   174,   176,   174,     4,   174,   174,     4,     4,
       4,   174,   174,   176,   249,   248,   246,   331,   327,   366,
     362,   390,   386,   209,   222,   223,   224,   225,   260,   323,
     335,   337,   339,   341,   343,   347,   354,   355,   382,   412,
     414,   458,   352,   288,   294,     4,   282,    88,    89,   209,
     260,   382,   412,   414,   468,   469,   470,   471,   472,   474,
     466,   441,   437,   307,   303,   174,   174,   174,   174,   174,
     174,   316,     4,     4,   174,   174,   174,   478,     4,     4,
     491,   148,   150,   151,   209,   260,   412,   414,   555,   556,
     557,   558,   560,   553,     6,     3,   408,   404,   424,   420,
       4,    21,    22,    23,    24,   252,   173,   173,   173,   173,
     173,   173,   173,     8,     8,     8,     8,     3,     8,   173,
     473,     4,     8,     3,     8,     8,   111,   112,   113,   481,
     173,   173,   173,   561,     4,   559,     3,     8,   173,     8,
       8,   173,   355,     4,   176,   470,     4,   174,     4,   556,
     173,     5,   173,     7,   562,   563,   564,     3,     6,   149,
     152,   153,   154,   565,   566,   567,   569,   570,   571,   563,
     568,     4,     4,     4,     3,     8,     4,   176,   174,   174,
     566,   173
  };

  const unsigned short
  Dhcp6Parser::yyr1_[] =
  {
       0,   177,   179,   178,   180,   178,   181,   178,   182,   178,
     183,   178,   184,   178,   185,   178,   186,   178,   187,   178,
     188,   178,   189,   178,   190,   178,   191,   178,   192,   178,
     193,   178,   194,   194,   194,   194,   194,   194,   194,   195,
     197,   196,   198,   199,   199,   200,   200,   202,   201,   203,
     203,   204,   204,   206,   205,   207,   207,   208,   208,   209,
     211,   210,   212,   212,   213,   213,   213,   213,   213,   213,
     215,   214,   217,   216,   218,   218,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     221,   220,   222,   223,   224,   225,   226,   228,   227,   230,
     229,   232,   231,   233,   233,   234,   234,   234,   234,   234,
     236,   235,   237,   239,   238,   241,   240,   243,   242,   244,
     244,   245,   245,   247,   246,   248,   248,   249,   249,   249,
     249,   249,   249,   249,   249,   249,   249,   249,   249,   249,
     249,   249,   249,   249,   249,   249,   249,   251,   250,   252,
     252,   252,   252,   254,   253,   256,   255,   258,   257,   259,
     261,   260,   262,   263,   264,   265,   266,   267,   268,   269,
     271,   270,   272,   274,   273,   276,   275,   278,   277,   280,
     279,   281,   281,   282,   284,   283,   286,   285,   287,   287,
     288,   288,   289,   290,   292,   291,   293,   293,   294,   294,
     294,   295,   296,   298,   297,   300,   299,   301,   301,   302,
     302,   304,   303,   306,   305,   307,   307,   307,   308,   308,
     310,   309,   312,   311,   314,   313,   315,   315,   316,   316,
     316,   316,   316,   316,   317,   318,   319,   320,   321,   322,
     324,   323,   325,   325,   326,   326,   328,   327,   330,   329,
     331,   331,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   332,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   332,   334,   333,   336,   335,   338,   337,   340,   339,
     342,   341,   344,   343,   345,   345,   345,   345,   346,   347,
     349,   348,   350,   350,   351,   351,   353,   352,   354,   354,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   357,   356,   359,
     358,   360,   360,   361,   361,   363,   362,   365,   364,   366,
     366,   367,   367,   368,   368,   368,   368,   368,   368,   368,
     368,   368,   368,   369,   370,   371,   373,   372,   375,   374,
     377,   376,   378,   380,   379,   381,   383,   382,   384,   384,
     385,   385,   387,   386,   389,   388,   390,   390,   391,   391,
     392,   392,   392,   392,   392,   392,   392,   392,   392,   393,
     395,   394,   396,   397,   398,   399,   401,   400,   402,   402,
     403,   403,   405,   404,   407,   406,   408,   408,   409,   409,
     409,   409,   409,   409,   409,   411,   410,   413,   412,   415,
     414,   417,   416,   418,   418,   419,   419,   421,   420,   423,
     422,   424,   424,   425,   425,   425,   425,   425,   425,   425,
     425,   425,   425,   425,   427,   426,   428,   430,   429,   431,
     432,   434,   433,   435,   435,   436,   436,   438,   437,   440,
     439,   441,   441,   442,   442,   443,   443,   443,   443,   443,
     443,   443,   443,   443,   443,   443,   445,   444,   447,   446,
     449,   448,   451,   450,   453,   452,   455,   454,   457,   456,
     459,   458,   460,   460,   462,   461,   464,   463,   465,   465,
     467,   466,   468,   468,   469,   469,   470,   470,   470,   470,
     470,   470,   470,   471,   473,   472,   474,   476,   475,   477,
     477,   478,   478,   478,   478,   478,   478,   478,   478,   478,
     480,   479,   481,   481,   481,   482,   484,   483,   485,   486,
     487,   489,   488,   490,   490,   491,   491,   491,   491,   491,
     493,   492,   495,   494,   497,   496,   499,   498,   501,   500,
     502,   502,   503,   503,   503,   503,   503,   503,   503,   503,
     503,   503,   503,   503,   503,   503,   503,   503,   503,   503,
     504,   506,   505,   508,   507,   509,   511,   510,   512,   513,
     515,   514,   516,   516,   518,   517,   519,   520,   522,   521,
     523,   523,   523,   523,   523,   525,   524,   527,   526,   529,
     528,   531,   530,   533,   532,   535,   534,   537,   536,   539,
     538,   540,   540,   541,   543,   542,   545,   544,   547,   546,
     548,   548,   549,   551,   550,   552,   552,   554,   553,   555,
     555,   556,   556,   556,   556,   556,   556,   556,   557,   559,
     558,   561,   560,   562,   562,   564,   563,   565,   565,   566,
     566,   566,   566,   568,   567,   569,   570,   571
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
       0,     4,     3,     3,     3,     3,     3,     0,     4,     0,
       6,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     6,     0,     6,     0,     6,     0,
       1,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     3,     3,     3,     3,     3,     3,
       0,     4,     3,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     0,     6,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     1,     1,     1,     1,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     1,     3,
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
       4,     1,     3,     1,     0,     6,     0,     6,     0,     4,
       1,     3,     1,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     0,     4,     3,     3,     3
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
  "\"consistency\"", "\"serial-consistency\"", "\"request-timeout\"",
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
  "config_control_param", "config_databases", "$@123", "logging_object",
  "$@124", "sub_logging", "$@125", "logging_params", "logging_param",
  "loggers", "$@126", "loggers_entries", "logger_entry", "$@127",
  "logger_params", "logger_param", "debuglevel", "severity", "$@128",
  "output_options_list", "$@129", "output_options_list_content",
  "output_entry", "$@130", "output_params_list", "output_params", "output",
  "$@131", "flush", "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short
  Dhcp6Parser::yyrline_[] =
  {
       0,   260,   260,   260,   261,   261,   262,   262,   263,   263,
     264,   264,   265,   265,   266,   266,   267,   267,   268,   268,
     269,   269,   270,   270,   271,   271,   272,   272,   273,   273,
     274,   274,   282,   283,   284,   285,   286,   287,   288,   291,
     296,   296,   307,   310,   311,   314,   318,   325,   325,   332,
     333,   336,   340,   347,   347,   354,   355,   358,   362,   373,
     383,   383,   398,   399,   403,   404,   405,   406,   407,   408,
     411,   411,   426,   426,   435,   436,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     477,   477,   485,   490,   495,   500,   505,   510,   510,   518,
     518,   529,   529,   538,   539,   542,   543,   544,   545,   546,
     549,   549,   559,   565,   565,   577,   577,   589,   589,   599,
     600,   603,   604,   607,   607,   617,   618,   621,   622,   623,
     624,   625,   626,   627,   628,   629,   630,   631,   632,   633,
     634,   635,   636,   637,   638,   639,   640,   643,   643,   650,
     651,   652,   653,   656,   656,   664,   664,   672,   672,   680,
     685,   685,   693,   698,   703,   708,   713,   718,   723,   728,
     733,   733,   741,   746,   746,   754,   754,   762,   762,   770,
     770,   780,   781,   783,   785,   785,   803,   803,   813,   814,
     817,   818,   821,   826,   831,   831,   841,   842,   845,   846,
     847,   850,   855,   862,   862,   872,   872,   882,   883,   886,
     887,   890,   890,   900,   900,   910,   911,   912,   915,   916,
     919,   919,   927,   927,   935,   935,   946,   947,   950,   951,
     952,   953,   954,   955,   958,   963,   968,   973,   978,   983,
     991,   991,  1004,  1005,  1008,  1009,  1016,  1016,  1042,  1042,
    1053,  1054,  1058,  1059,  1060,  1061,  1062,  1063,  1064,  1065,
    1066,  1067,  1068,  1069,  1070,  1071,  1072,  1073,  1074,  1075,
    1076,  1077,  1080,  1080,  1088,  1088,  1096,  1096,  1104,  1104,
    1112,  1112,  1122,  1122,  1129,  1130,  1131,  1132,  1135,  1140,
    1148,  1148,  1159,  1160,  1164,  1165,  1168,  1168,  1176,  1177,
    1180,  1181,  1182,  1183,  1184,  1185,  1186,  1187,  1188,  1189,
    1190,  1191,  1192,  1193,  1194,  1195,  1196,  1203,  1203,  1216,
    1216,  1225,  1226,  1229,  1230,  1235,  1235,  1250,  1250,  1264,
    1265,  1268,  1269,  1272,  1273,  1274,  1275,  1276,  1277,  1278,
    1279,  1280,  1281,  1284,  1286,  1291,  1293,  1293,  1301,  1301,
    1309,  1309,  1317,  1319,  1319,  1327,  1336,  1336,  1348,  1349,
    1354,  1355,  1360,  1360,  1372,  1372,  1384,  1385,  1390,  1391,
    1396,  1397,  1398,  1399,  1400,  1401,  1402,  1403,  1404,  1407,
    1409,  1409,  1417,  1419,  1421,  1426,  1434,  1434,  1446,  1447,
    1450,  1451,  1454,  1454,  1464,  1464,  1473,  1474,  1477,  1478,
    1479,  1480,  1481,  1482,  1483,  1486,  1486,  1494,  1494,  1519,
    1519,  1549,  1549,  1561,  1562,  1565,  1566,  1569,  1569,  1581,
    1581,  1593,  1594,  1597,  1598,  1599,  1600,  1601,  1602,  1603,
    1604,  1605,  1606,  1607,  1610,  1610,  1618,  1623,  1623,  1631,
    1636,  1644,  1644,  1654,  1655,  1658,  1659,  1662,  1662,  1671,
    1671,  1680,  1681,  1684,  1685,  1689,  1690,  1691,  1692,  1693,
    1694,  1695,  1696,  1697,  1698,  1699,  1702,  1702,  1712,  1712,
    1722,  1722,  1730,  1730,  1738,  1738,  1746,  1746,  1754,  1754,
    1767,  1767,  1777,  1778,  1781,  1781,  1792,  1792,  1802,  1803,
    1806,  1806,  1816,  1817,  1820,  1821,  1824,  1825,  1826,  1827,
    1828,  1829,  1830,  1833,  1835,  1835,  1843,  1851,  1851,  1863,
    1864,  1867,  1868,  1869,  1870,  1871,  1872,  1873,  1874,  1875,
    1878,  1878,  1885,  1886,  1887,  1890,  1895,  1895,  1903,  1908,
    1915,  1922,  1922,  1932,  1933,  1936,  1937,  1938,  1939,  1940,
    1943,  1943,  1951,  1951,  1961,  1961,  2001,  2001,  2013,  2013,
    2023,  2024,  2027,  2028,  2029,  2030,  2031,  2032,  2033,  2034,
    2035,  2036,  2037,  2038,  2039,  2040,  2041,  2042,  2043,  2044,
    2047,  2052,  2052,  2060,  2060,  2068,  2073,  2073,  2081,  2086,
    2091,  2091,  2099,  2100,  2103,  2103,  2111,  2116,  2121,  2121,
    2129,  2132,  2135,  2138,  2141,  2147,  2147,  2155,  2155,  2163,
    2163,  2173,  2173,  2180,  2180,  2187,  2187,  2196,  2196,  2207,
    2207,  2217,  2218,  2222,  2225,  2225,  2240,  2240,  2250,  2250,
    2261,  2262,  2266,  2270,  2270,  2282,  2283,  2287,  2287,  2295,
    2296,  2299,  2300,  2301,  2302,  2303,  2304,  2305,  2308,  2313,
    2313,  2321,  2321,  2331,  2332,  2335,  2335,  2343,  2344,  2347,
    2348,  2349,  2350,  2353,  2353,  2361,  2366,  2371
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
#line 5142 "dhcp6_parser.cc" // lalr1.cc:1242
#line 2376 "dhcp6_parser.yy" // lalr1.cc:1243


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
