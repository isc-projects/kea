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

  case 109:
#line 476 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1066 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 110:
#line 478 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1076 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 111:
#line 484 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1085 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 112:
#line 489 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1094 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 113:
#line 494 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1103 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 114:
#line 499 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1112 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 115:
#line 504 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 116:
#line 509 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1129 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 117:
#line 511 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1139 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 118:
#line 517 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1150 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 119:
#line 522 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1160 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 120:
#line 528 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1170 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 121:
#line 532 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1179 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 129:
#line 548 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1190 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 130:
#line 553 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1199 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 131:
#line 558 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1208 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 132:
#line 564 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1219 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 133:
#line 569 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1230 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 134:
#line 576 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1241 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 135:
#line 581 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1252 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 136:
#line 588 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1263 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 137:
#line 593 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1272 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 142:
#line 606 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1282 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 143:
#line 610 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1292 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 166:
#line 642 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1300 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 167:
#line 644 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1309 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 168:
#line 649 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1315 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 169:
#line 650 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1321 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 170:
#line 651 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1327 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 171:
#line 652 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1333 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 172:
#line 655 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1341 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 173:
#line 657 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1351 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 174:
#line 663 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1359 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 175:
#line 665 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1369 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 176:
#line 671 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1377 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 177:
#line 673 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1387 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 178:
#line 679 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1396 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 179:
#line 684 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1404 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 180:
#line 686 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1414 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 181:
#line 692 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1423 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 182:
#line 697 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1432 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 183:
#line 702 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1441 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 184:
#line 707 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1450 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 185:
#line 712 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1459 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 186:
#line 717 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1468 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 187:
#line 722 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1477 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 188:
#line 727 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1486 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 189:
#line 732 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1494 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 190:
#line 734 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1504 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 191:
#line 740 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1513 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 192:
#line 745 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1521 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 193:
#line 747 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1531 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 194:
#line 753 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1539 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 195:
#line 755 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1549 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 196:
#line 761 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1557 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 197:
#line 763 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1567 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 198:
#line 769 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1578 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 199:
#line 774 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1587 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 203:
#line 784 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1595 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 204:
#line 786 "dhcp6_parser.yy" // lalr1.cc:919
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

  case 205:
#line 802 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1626 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 206:
#line 807 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1635 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 211:
#line 820 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1644 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 212:
#line 825 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1653 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 213:
#line 830 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1664 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 214:
#line 835 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1673 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 220:
#line 849 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1682 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 221:
#line 854 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1691 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 222:
#line 861 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1702 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 223:
#line 866 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1711 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 224:
#line 871 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1722 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 225:
#line 876 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1731 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 230:
#line 889 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1741 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 231:
#line 893 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1751 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 232:
#line 899 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1761 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 233:
#line 903 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1771 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 239:
#line 918 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1779 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 240:
#line 920 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1789 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 241:
#line 926 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1797 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 242:
#line 928 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1806 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 243:
#line 934 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1817 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 244:
#line 939 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1827 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 253:
#line 957 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1836 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 254:
#line 962 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1845 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 255:
#line 967 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1854 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 256:
#line 972 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1863 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 257:
#line 977 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1872 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 258:
#line 982 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1881 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 259:
#line 990 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1892 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 260:
#line 995 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1901 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 265:
#line 1015 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1911 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 266:
#line 1019 "dhcp6_parser.yy" // lalr1.cc:919
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

  case 267:
#line 1041 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1947 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 268:
#line 1045 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1957 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 291:
#line 1079 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1965 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 292:
#line 1081 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1975 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 293:
#line 1087 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1983 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 294:
#line 1089 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1993 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 295:
#line 1095 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2001 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 296:
#line 1097 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2011 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 297:
#line 1103 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2019 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 298:
#line 1105 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2029 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 299:
#line 1111 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2040 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 300:
#line 1116 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2049 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 301:
#line 1121 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2057 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 302:
#line 1123 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2066 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 303:
#line 1128 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2072 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 304:
#line 1129 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2078 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 305:
#line 1130 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2084 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 306:
#line 1131 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2090 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 307:
#line 1134 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2099 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 308:
#line 1139 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2108 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 309:
#line 1147 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2119 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 310:
#line 1152 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2128 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 315:
#line 1167 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2138 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 316:
#line 1171 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 2146 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 336:
#line 1202 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2157 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 337:
#line 1207 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2166 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 338:
#line 1215 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2175 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 339:
#line 1218 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 2183 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 344:
#line 1234 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2193 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 345:
#line 1238 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2205 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 346:
#line 1249 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2215 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 347:
#line 1253 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2227 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 363:
#line 1285 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2236 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 365:
#line 1292 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2244 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 366:
#line 1294 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2254 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 367:
#line 1300 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2262 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 368:
#line 1302 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2272 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 369:
#line 1308 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2280 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 370:
#line 1310 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2290 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 372:
#line 1318 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2298 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 373:
#line 1320 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2308 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 374:
#line 1326 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2317 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 375:
#line 1335 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2328 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 376:
#line 1340 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2337 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 381:
#line 1359 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2347 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 382:
#line 1363 "dhcp6_parser.yy" // lalr1.cc:919
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2356 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 383:
#line 1371 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2366 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 384:
#line 1375 "dhcp6_parser.yy" // lalr1.cc:919
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2375 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 399:
#line 1408 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2383 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 400:
#line 1410 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2393 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 403:
#line 1420 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2402 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 404:
#line 1425 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2411 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 405:
#line 1433 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2422 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 406:
#line 1438 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2431 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 411:
#line 1453 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2441 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 412:
#line 1457 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2451 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 413:
#line 1463 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2461 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 414:
#line 1467 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2470 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 424:
#line 1485 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2478 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 425:
#line 1487 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2488 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 426:
#line 1493 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2496 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 427:
#line 1495 "dhcp6_parser.yy" // lalr1.cc:919
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

  case 428:
#line 1518 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2531 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 429:
#line 1520 "dhcp6_parser.yy" // lalr1.cc:919
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

  case 430:
#line 1548 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2571 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 431:
#line 1553 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2580 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 436:
#line 1568 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2590 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 437:
#line 1572 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2602 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 438:
#line 1580 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2612 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 439:
#line 1584 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2624 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 453:
#line 1609 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2632 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 454:
#line 1611 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2642 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 455:
#line 1617 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2651 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 456:
#line 1622 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2659 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 457:
#line 1624 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2669 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 458:
#line 1630 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2678 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 459:
#line 1635 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2687 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 460:
#line 1643 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2698 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 461:
#line 1648 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2707 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 466:
#line 1661 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2717 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 467:
#line 1665 "dhcp6_parser.yy" // lalr1.cc:919
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2726 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 468:
#line 1670 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2736 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 469:
#line 1674 "dhcp6_parser.yy" // lalr1.cc:919
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2745 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 485:
#line 1701 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2756 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 486:
#line 1706 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2765 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 487:
#line 1711 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2776 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 488:
#line 1716 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2785 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 489:
#line 1721 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2793 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 490:
#line 1723 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2803 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 491:
#line 1729 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2811 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 492:
#line 1731 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2821 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 493:
#line 1737 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2829 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 494:
#line 1739 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2839 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 495:
#line 1745 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2847 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 496:
#line 1747 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2857 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 497:
#line 1753 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2868 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 498:
#line 1758 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2877 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 499:
#line 1766 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2888 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 500:
#line 1771 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2897 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 503:
#line 1780 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2905 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 504:
#line 1782 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2915 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 505:
#line 1791 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2926 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 506:
#line 1796 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2935 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 509:
#line 1805 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2945 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 510:
#line 1809 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2955 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 523:
#line 1834 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2963 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 524:
#line 1836 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2973 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 525:
#line 1842 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2982 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 526:
#line 1850 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2993 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 527:
#line 1855 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3004 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 539:
#line 1877 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 3012 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 540:
#line 1879 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3021 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 541:
#line 1884 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3027 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 542:
#line 1885 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3033 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 543:
#line 1886 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3039 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 544:
#line 1889 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3048 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 545:
#line 1894 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3056 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 546:
#line 1896 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3066 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 547:
#line 1902 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3075 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 548:
#line 1907 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3084 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 549:
#line 1914 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3093 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 550:
#line 1921 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3104 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 551:
#line 1926 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3113 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 559:
#line 1942 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3121 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 560:
#line 1944 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3131 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 561:
#line 1950 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3139 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 562:
#line 1952 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3149 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 563:
#line 1960 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3157 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 564:
#line 1962 "dhcp6_parser.yy" // lalr1.cc:919
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

  case 565:
#line 2000 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3208 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 566:
#line 2005 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3219 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 567:
#line 2012 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3229 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 568:
#line 2016 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3239 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 589:
#line 2046 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3248 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 590:
#line 2051 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3256 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 591:
#line 2053 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3266 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 592:
#line 2059 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3274 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 593:
#line 2061 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3284 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 594:
#line 2067 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3293 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 595:
#line 2072 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3301 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 596:
#line 2074 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3311 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 597:
#line 2080 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3320 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 598:
#line 2085 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3329 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 599:
#line 2090 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3337 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 600:
#line 2092 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3346 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 601:
#line 2098 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3352 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 602:
#line 2099 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3358 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 603:
#line 2102 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3366 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 604:
#line 2104 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3376 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 605:
#line 2110 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3385 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 606:
#line 2115 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3394 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 607:
#line 2120 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3402 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 608:
#line 2122 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3411 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 609:
#line 2128 "dhcp6_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3419 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 610:
#line 2131 "dhcp6_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3427 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 611:
#line 2134 "dhcp6_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3435 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 612:
#line 2137 "dhcp6_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3443 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 613:
#line 2140 "dhcp6_parser.yy" // lalr1.cc:919
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3452 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 614:
#line 2146 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3460 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 615:
#line 2148 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3470 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 616:
#line 2154 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3478 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 617:
#line 2156 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3488 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 618:
#line 2162 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3496 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 619:
#line 2164 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3506 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 620:
#line 2172 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3514 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 621:
#line 2174 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3523 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 622:
#line 2179 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3531 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 623:
#line 2181 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3540 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 624:
#line 2186 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3548 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 625:
#line 2188 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3557 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 626:
#line 2195 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3568 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 627:
#line 2200 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3578 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 628:
#line 2206 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3588 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 629:
#line 2210 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No config_control params are required
    // parsing completed
}
#line 3597 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 633:
#line 2224 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3608 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 634:
#line 2229 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3617 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 635:
#line 2239 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3628 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 636:
#line 2244 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3637 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 637:
#line 2249 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3647 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 638:
#line 2253 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 3655 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 642:
#line 2269 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3666 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 643:
#line 2274 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3675 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 646:
#line 2286 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3685 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 647:
#line 2290 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 3693 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 657:
#line 2307 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3702 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 658:
#line 2312 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3710 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 659:
#line 2314 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3720 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 660:
#line 2320 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3731 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 661:
#line 2325 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3740 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 664:
#line 2334 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3750 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 665:
#line 2338 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 3758 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 672:
#line 2352 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3766 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 673:
#line 2354 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3776 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 674:
#line 2360 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3785 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 675:
#line 2365 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3794 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 676:
#line 2370 "dhcp6_parser.yy" // lalr1.cc:919
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


  const short Dhcp6Parser::yypact_ninf_ = -833;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     415,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,    71,    65,    68,    82,
      83,    90,    98,    99,   116,   151,   163,   200,   230,   236,
     238,   251,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,    65,    94,    27,    69,    23,   227,   107,    35,
     167,   233,    73,   268,   -52,   366,   138,   266,  -833,   285,
     302,   312,   298,   324,  -833,  -833,  -833,  -833,  -833,   335,
    -833,    37,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,   339,   345,   347,   351,   355,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,   357,  -833,  -833,  -833,
    -833,    54,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,   361,  -833,    70,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,   364,
     365,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,    76,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,   131,  -833,  -833,  -833,  -833,  -833,   367,  -833,   383,
     387,  -833,  -833,  -833,  -833,  -833,  -833,   132,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,   334,   350,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,   397,  -833,  -833,   405,  -833,
    -833,  -833,   408,  -833,  -833,   411,   419,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
     422,   436,  -833,  -833,  -833,  -833,   435,   441,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
     159,  -833,  -833,  -833,   442,  -833,  -833,   443,  -833,   444,
     446,  -833,  -833,   447,   448,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,   177,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
     187,  -833,  -833,  -833,   244,  -833,  -833,  -833,    65,    65,
    -833,   280,   450,   451,   454,   457,   460,  -833,    27,  -833,
     461,   462,   463,   464,   465,   466,   271,   297,   299,   300,
     303,   468,   472,   475,   476,   477,   478,   479,   480,   481,
     483,   484,   485,   499,   500,   501,   502,   503,   340,   504,
     505,   508,    69,  -833,   509,   341,    23,  -833,   512,   514,
     515,   516,   517,   352,   348,   519,   521,   523,   227,  -833,
     524,   107,  -833,   528,   360,   529,   362,   363,    35,  -833,
     531,   536,   537,   538,   539,   540,   541,  -833,   167,  -833,
     542,   545,   377,   548,   549,   550,   379,  -833,    73,   552,
     381,   382,  -833,   268,   555,   556,   -37,  -833,   386,   561,
     563,   394,   565,   396,   414,   567,   585,   416,   418,   586,
     587,   589,   591,   366,  -833,   592,   138,  -833,   595,   266,
    -833,  -833,  -833,   597,   596,   598,    65,    65,    65,  -833,
     429,   599,   600,   601,   603,   606,  -833,  -833,  -833,  -833,
    -833,   431,   607,   608,   609,   610,   445,   178,   611,   614,
     615,   616,   617,   618,   620,   621,   622,   623,  -833,   625,
     610,   626,  -833,   629,  -833,  -833,   630,   631,   449,   455,
     467,  -833,  -833,   629,   469,   632,  -833,   470,  -833,   471,
    -833,   473,  -833,  -833,  -833,   629,   629,   629,   474,   482,
     486,   487,  -833,   488,   489,  -833,   490,   491,   492,  -833,
    -833,   493,  -833,  -833,  -833,   494,    65,  -833,  -833,   495,
     496,  -833,   497,  -833,  -833,    40,   498,  -833,  -833,   -33,
     506,   507,   510,  -833,   633,  -833,   636,  -833,    65,    69,
     138,  -833,  -833,  -833,  -833,   266,    23,   193,   193,   638,
    -833,   641,   642,   643,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,   644,   -53,    65,   104,   530,   645,   646,   647,
     204,   134,     8,  -833,   366,  -833,  -833,   649,   650,  -833,
    -833,  -833,  -833,  -833,   -48,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,   651,
     638,  -833,   265,   278,   323,   326,  -833,  -833,  -833,  -833,
     667,   668,   669,   670,   671,  -833,   672,   673,  -833,  -833,
    -833,   674,   677,   678,  -833,   327,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,   330,  -833,   679,   624,
    -833,  -833,   680,   681,  -833,  -833,   682,   684,  -833,  -833,
     683,   687,  -833,  -833,   685,   689,  -833,  -833,  -833,   130,
    -833,  -833,  -833,   688,  -833,  -833,  -833,   153,  -833,  -833,
    -833,  -833,   338,  -833,  -833,  -833,   168,  -833,  -833,   690,
     692,  -833,  -833,   691,   695,  -833,   696,   697,   698,   699,
     700,   701,   342,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,   702,   703,   704,  -833,  -833,  -833,  -833,   349,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,   359,  -833,  -833,  -833,   378,   520,  -833,   693,   706,
    -833,  -833,   705,   707,  -833,  -833,  -833,   708,  -833,  -833,
     183,  -833,   709,  -833,  -833,  -833,  -833,   710,   713,   714,
     715,   546,   547,   551,   553,   554,   717,   557,   558,   718,
     720,   722,   559,   560,   562,   193,  -833,  -833,   193,  -833,
     638,   227,  -833,   641,    73,  -833,   642,   268,  -833,   643,
     388,  -833,   644,   -53,  -833,  -833,   104,  -833,   723,   530,
    -833,   215,   645,  -833,   167,  -833,   646,   -52,  -833,   647,
     566,   568,   569,   570,   571,   572,   204,  -833,   726,   731,
     573,   574,   575,   134,  -833,   732,   733,     8,  -833,  -833,
    -833,   735,   736,   107,  -833,   649,    35,  -833,   650,   746,
    -833,   142,   651,  -833,  -833,   124,   578,   579,   580,  -833,
    -833,  -833,  -833,  -833,   581,  -833,  -833,   582,   583,   584,
    -833,  -833,  -833,  -833,   390,  -833,   400,  -833,   750,  -833,
     751,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,   403,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,   588,  -833,  -833,   756,  -833,  -833,
    -833,  -833,  -833,   754,   760,  -833,  -833,  -833,  -833,  -833,
     757,  -833,   410,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,   103,   593,  -833,  -833,  -833,  -833,   594,   602,  -833,
    -833,   605,   413,  -833,   417,  -833,   612,  -833,   764,  -833,
    -833,  -833,  -833,  -833,   420,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,   388,  -833,  -833,   765,
     619,  -833,   215,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,   766,   590,   767,   142,
    -833,  -833,   634,  -833,  -833,   768,  -833,   637,  -833,  -833,
     769,  -833,  -833,   272,  -833,    12,   769,  -833,  -833,   770,
     775,   778,   434,  -833,  -833,  -833,  -833,  -833,  -833,   788,
     628,   648,   652,    12,  -833,   639,  -833,  -833,  -833,  -833,
    -833
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
     346,    21,   383,    23,   232,    25,   567,    27,   637,    29,
     628,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     470,     0,   348,   385,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   635,   620,   622,   624,     0,
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
     577,   578,   579,   580,   581,   582,   583,   584,   585,   642,
       0,   639,   641,   633,     0,   630,   632,    48,     0,     0,
      41,     0,     0,     0,     0,     0,     0,    59,     0,    61,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    73,     0,     0,     0,   121,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   268,
       0,     0,   414,     0,     0,     0,     0,     0,     0,   439,
       0,     0,     0,     0,     0,     0,     0,   469,     0,   339,
       0,     0,     0,     0,     0,     0,     0,   347,     0,     0,
       0,     0,   384,     0,     0,     0,     0,   233,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   568,     0,     0,   638,     0,     0,
     629,    52,    45,     0,     0,     0,     0,     0,     0,    63,
       0,     0,     0,     0,     0,     0,   111,   112,   113,   114,
     115,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   549,     0,
       0,     0,    75,     0,   131,   123,     0,     0,     0,     0,
       0,   307,   308,     0,     0,     0,   270,     0,   416,     0,
     455,     0,   458,   459,   441,     0,     0,     0,     0,     0,
       0,     0,   473,     0,     0,   363,     0,     0,     0,   374,
     351,     0,   403,   404,   388,     0,     0,   235,   589,     0,
       0,   594,     0,   597,   598,     0,     0,   605,   606,     0,
       0,     0,     0,   570,     0,   640,     0,   631,     0,     0,
       0,   621,   623,   625,   110,     0,     0,     0,     0,   138,
     117,   261,   340,   377,    42,   427,   429,   303,   304,   305,
     306,   302,   311,     0,    49,     0,     0,     0,   462,   226,
       0,     0,     0,   564,     0,    53,   130,   407,   432,   292,
     294,   296,   300,   298,     0,   425,   454,   457,   498,   486,
     488,   490,   492,   494,   496,   366,   180,   370,   368,   373,
     400,   240,   242,   591,   593,   596,   601,   602,   600,   604,
     609,   610,   611,   612,   613,   608,   615,   617,   619,     0,
     138,    46,     0,     0,     0,     0,   166,   172,   174,   176,
       0,     0,     0,     0,     0,   189,     0,     0,   192,   194,
     196,     0,     0,     0,   165,     0,   144,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   158,   159,   160,
     161,   156,   157,   162,   163,   164,     0,   142,     0,   139,
     140,   265,     0,   262,   263,   344,     0,   341,   342,   381,
       0,   378,   379,   315,     0,   312,   313,   211,   212,     0,
     207,   209,   210,     0,   220,   221,   217,     0,   215,   218,
     219,   203,     0,   200,   202,   509,     0,   507,   466,     0,
     463,   464,   230,     0,   227,   228,     0,     0,     0,     0,
       0,     0,     0,   245,   247,   248,   249,   250,   251,   252,
     539,   545,     0,     0,     0,   538,   535,   536,   537,     0,
     528,   530,   533,   531,   532,   534,   559,   561,   558,   556,
     557,     0,   552,   554,   555,     0,    55,   411,     0,   408,
     409,   436,     0,   433,   434,   503,   502,     0,   501,   646,
       0,   644,     0,    71,   636,   627,   119,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   133,   135,     0,   137,
       0,     0,   260,     0,   348,   337,     0,   385,   376,     0,
       0,   310,     0,     0,   206,   223,     0,   214,     0,     0,
     199,   511,     0,   506,   470,   461,     0,     0,   225,     0,
       0,     0,     0,     0,     0,     0,     0,   244,     0,     0,
       0,     0,     0,     0,   527,     0,     0,     0,   551,   566,
      57,     0,    56,     0,   406,     0,     0,   431,     0,     0,
     500,     0,     0,   643,   634,     0,     0,     0,     0,   178,
     181,   182,   183,   184,     0,   191,   185,     0,     0,     0,
     186,   187,   188,   145,     0,   141,     0,   264,     0,   343,
       0,   380,   335,   330,   332,   323,   324,   319,   320,   321,
     322,   328,   329,   327,   331,     0,   317,   325,   333,   334,
     326,   314,   208,   216,     0,   201,   523,     0,   521,   522,
     518,   519,   520,     0,   512,   513,   515,   516,   517,   508,
       0,   465,     0,   229,   253,   254,   255,   256,   257,   258,
     246,     0,     0,   544,   547,   548,   529,     0,     0,   553,
      54,     0,     0,   410,     0,   435,     0,   660,     0,   658,
     656,   650,   654,   655,     0,   648,   652,   653,   651,   645,
     168,   169,   170,   171,   167,   173,   175,   177,   190,   193,
     195,   197,   143,   266,   345,   382,     0,   316,   204,     0,
       0,   510,     0,   467,   231,   541,   542,   543,   540,   546,
     560,   562,    58,   412,   437,   504,     0,     0,     0,     0,
     647,   318,     0,   525,   514,     0,   657,     0,   649,   524,
       0,   659,   664,     0,   662,     0,     0,   661,   672,     0,
       0,     0,     0,   666,   668,   669,   670,   671,   663,     0,
       0,     0,     0,     0,   665,     0,   674,   675,   676,   667,
     673
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,    43,  -833,  -457,
    -833,   192,  -833,  -833,  -833,  -833,   158,  -833,  -451,  -833,
    -833,  -833,   -74,  -833,  -833,  -833,   426,  -833,  -833,  -833,
    -833,   222,   311,  -833,  -833,   -62,   -46,   -45,   -43,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,   224,   425,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,   155,  -833,   -29,
    -833,  -572,    -7,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,   -70,  -833,  -605,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,   -35,  -833,  -833,  -833,  -833,
    -833,   -21,  -592,  -833,  -833,  -833,  -833,   -23,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,   -28,  -833,  -833,  -833,
     -31,   398,  -833,  -833,  -833,  -833,  -833,  -833,  -833,   -34,
    -833,  -833,  -833,  -833,  -833,  -833,  -832,  -833,  -833,  -833,
      -9,  -833,  -833,  -833,     4,   438,  -833,  -833,  -831,  -833,
    -830,  -833,   -36,  -833,   -32,  -833,   -42,  -833,  -833,  -833,
    -827,  -833,  -833,  -833,  -833,    -5,  -833,  -833,  -178,   780,
    -833,  -833,  -833,  -833,  -833,     3,  -833,  -833,  -833,    10,
    -833,   424,  -833,   -76,  -833,  -833,  -833,  -833,  -833,   -69,
    -833,  -833,  -833,  -833,  -833,   -11,  -833,  -833,  -833,     6,
    -833,  -833,  -833,     5,  -833,   423,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,   -39,  -833,  -833,
    -833,   -26,   459,  -833,  -833,   -58,  -833,   -24,  -833,  -833,
    -833,  -833,  -833,   -40,  -833,  -833,  -833,   -25,   456,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,   -60,  -833,  -833,  -833,
      -1,  -833,  -833,  -833,     9,  -833,   440,   252,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -824,  -833,  -833,  -833,  -833,  -833,  -833,  -833,    13,
    -833,  -833,  -833,  -154,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,    -4,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,    -6,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,   269,   421,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,  -833,
    -833,  -833,  -833,   295,   427,  -833,  -833,  -833,  -833,  -833,
    -833,   306,   428,  -833,  -833,  -833,   -15,  -833,  -833,  -161,
    -833,  -833,  -833,  -833,  -833,  -833,  -177,  -833,  -833,  -193,
    -833,  -833,  -833,  -833,  -833
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   605,    92,    93,    43,    72,    89,    90,   626,   806,
     901,   902,   694,    45,    74,   101,   102,   103,   362,    47,
      75,   141,   142,   143,   370,   144,   145,   146,   147,   148,
     149,   381,   150,   372,    49,    76,   178,   179,   180,   404,
     181,   151,   373,   152,   374,   153,   375,   718,   719,   720,
     848,   695,   696,   697,   827,  1024,   698,   828,   699,   829,
     700,   830,   701,   702,   441,   703,   704,   705,   706,   707,
     708,   709,   710,   711,   836,   712,   713,   839,   714,   840,
     715,   841,   154,   392,   752,   753,   754,   868,   155,   389,
     739,   740,   741,   742,   156,   391,   747,   748,   749,   750,
     157,   390,   158,   395,   763,   764,   765,   877,    65,    84,
     310,   311,   312,   454,   313,   455,   159,   396,   772,   773,
     774,   775,   776,   777,   778,   779,   160,   382,   722,   723,
     724,   851,    51,    77,   199,   200,   201,   410,   202,   411,
     203,   412,   204,   416,   205,   415,   161,   387,   611,   207,
     208,   162,   388,   734,   735,   736,   860,   955,   956,   163,
     383,    59,    81,   726,   727,   728,   854,    61,    82,   275,
     276,   277,   278,   279,   280,   281,   440,   282,   444,   283,
     443,   284,   285,   445,   286,   164,   384,   730,   731,   732,
     857,    63,    83,   296,   297,   298,   299,   300,   449,   301,
     302,   303,   304,   210,   408,   808,   809,   810,   903,    53,
      78,   221,   222,   223,   420,   165,   385,   166,   386,   213,
     409,   812,   813,   814,   906,    55,    79,   237,   238,   239,
     423,   240,   241,   425,   242,   243,   167,   394,   759,   760,
     761,   874,    57,    80,   255,   256,   257,   258,   431,   259,
     432,   260,   433,   261,   434,   262,   435,   263,   436,   264,
     430,   215,   417,   817,   818,   909,   168,   393,   756,   757,
     871,   973,   974,   975,   976,   977,  1039,   978,   169,   397,
     789,   790,   791,   888,  1048,   792,   793,   889,   794,   795,
     170,   171,   399,   801,   802,   803,   895,   804,   896,   172,
     400,   173,   401,    67,    85,   332,   333,   334,   335,   459,
     336,   460,   337,   338,   462,   339,   340,   341,   465,   658,
     342,   466,   343,   344,   345,   469,   665,   346,   470,   347,
     471,   348,   472,   104,   364,   105,   365,   106,   366,   174,
     371,    71,    87,   354,   355,   356,   478,   107,   363,    69,
      86,   350,   351,   352,   475,   820,   821,   911,  1014,  1015,
    1016,  1017,  1058,  1018,  1056,  1073,  1074,  1075,  1082,  1083,
    1084,  1089,  1085,  1086,  1087
  };

  const unsigned short
  Dhcp6Parser::yytable_[] =
  {
     100,   140,   177,   194,   217,   231,   251,   294,   273,   292,
     309,   329,   274,   293,   295,   195,   786,   214,   182,   211,
     224,   235,   253,   746,   287,   305,   716,   330,   948,   949,
     950,   196,   197,   954,   198,   206,   960,    94,   175,   176,
     368,   737,   218,   232,   245,   369,   219,   233,   604,   307,
     308,   815,   183,   212,   225,   236,   254,   402,   288,   306,
      40,   331,   403,   604,   307,   308,   209,   220,   234,   252,
      33,    32,    34,   406,    35,    44,   123,   124,   407,   418,
     108,   109,   632,   110,   419,   122,   111,   112,   113,    46,
      48,   123,   124,   266,   638,   639,   640,    50,   226,   227,
     228,   229,   230,   123,   124,    52,    54,   660,   661,   662,
     663,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     738,    99,   191,    56,   267,   192,   268,   269,   796,   797,
     270,   271,   272,   863,   421,   428,   864,   123,   124,   422,
     429,   123,   124,   664,   125,  1020,  1021,  1022,  1023,   126,
     127,   128,   129,   130,   780,   131,   866,   122,    58,   867,
     132,  1078,   456,   681,  1079,  1080,  1081,   457,   216,   133,
      60,   872,   134,    95,   873,   123,   124,   656,   657,   135,
     473,    99,    96,    97,    98,   474,   912,   136,   137,   913,
     476,   138,   139,   267,   191,   477,    99,   192,   737,   744,
      99,   745,   123,   124,   948,   949,   950,    62,    99,   954,
     123,   124,   960,   676,  1045,  1046,  1047,   122,   677,   678,
     679,   680,   681,   682,   683,   684,   685,   686,   687,   688,
     689,   690,   691,   692,   693,   123,   124,    64,    36,    37,
      38,    39,    99,    66,   267,    68,    99,   479,   781,   782,
     783,   784,   480,   244,   607,   608,   609,   610,    70,   245,
     246,   247,   248,   249,   250,   122,   267,    91,   402,   114,
     115,   116,   117,   823,   746,  1076,   934,   122,  1077,   353,
      99,   476,   121,   123,   124,   349,   824,   184,   786,   185,
    1007,   357,  1008,  1009,   100,   123,   124,   186,   187,   188,
     189,   190,   125,   966,   967,   358,   360,    99,   766,   767,
     768,   769,   770,   771,   191,    99,   359,   192,   132,   267,
     289,   268,   269,   290,   291,   193,   479,   361,   140,   406,
     845,   825,   177,   845,   826,   846,   123,   124,   847,   367,
      99,   869,   437,   376,   194,   886,   870,   217,   182,   377,
     887,   378,   893,   438,   231,   379,   195,   894,   214,   380,
     211,   398,   897,   224,   251,   405,    99,   898,   413,   414,
     235,   424,   196,   197,   273,   198,   206,   294,   274,   292,
     253,   473,   183,   293,   295,   218,   899,   426,    99,   219,
     287,   427,   232,   845,   212,   305,   233,   225,  1032,   329,
      99,   481,   482,   418,   236,   439,  1036,   209,  1033,   442,
     220,  1037,   446,   456,   254,   330,   421,   234,  1044,   447,
     428,  1053,   448,  1059,   288,  1054,   450,   252,  1060,   306,
     114,   115,   116,   117,   123,   124,   120,  1093,   122,   267,
     451,    99,  1094,   452,   453,   496,   458,   461,   463,   331,
     464,   467,   468,   483,   484,   485,   123,   124,   486,   187,
     188,   487,   190,   125,   488,   490,   491,   492,   493,   494,
     495,   497,   501,   498,   499,   191,   502,   500,   192,   503,
     504,   505,   506,   507,   508,   509,   193,   510,   511,   512,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   513,   514,   515,   516,   517,   519,   520,
     327,   328,   521,   523,   518,   140,   526,   524,   527,   528,
     529,   530,   177,   533,   532,   534,   531,   535,   537,   591,
     592,   593,   539,   541,   540,   545,   542,   543,   182,    99,
     546,   547,   548,   549,   550,   551,   553,   785,   798,   554,
     329,   555,   556,   557,   558,   559,   561,   562,   563,   565,
     566,    99,   568,   787,   799,   569,   330,   570,   571,   572,
     573,   575,   183,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,   574,   576,
     579,   580,   577,   581,   578,   582,   584,   788,   800,   586,
     331,   588,   594,   589,   600,   590,   595,   596,   597,   652,
     598,   599,   601,   602,   603,   751,   612,    34,   606,   613,
     614,   615,   629,   617,   616,   618,   619,   850,   630,   620,
     621,   671,   622,   624,   625,   627,   628,   659,   669,   634,
     631,   670,   633,   635,   636,   717,   637,   641,   721,   725,
     729,   733,   755,   758,   762,   642,   807,   811,   819,   643,
     644,   645,   646,   647,   648,   649,   650,   651,   653,   654,
     655,   831,   832,   833,   834,   835,   837,   838,   842,   666,
     667,   843,   844,   668,   853,   849,   852,   856,   855,   858,
     859,   861,   862,   900,   865,   876,   875,   878,   879,   904,
     880,   881,   882,   883,   884,   885,   890,   891,   892,   905,
     908,   907,   623,   522,   915,   914,   910,   916,   917,   918,
     919,   924,   927,   920,   928,   921,   929,   964,   923,   922,
     991,   925,   926,   930,   931,   992,   997,   998,   932,  1001,
     984,  1000,   985,   986,   987,   988,   989,   993,   994,   995,
    1006,  1025,  1026,  1027,  1028,  1029,  1030,  1031,  1034,  1035,
    1040,  1038,  1041,  1042,  1066,  1043,  1049,  1050,  1057,  1062,
    1065,  1067,   743,  1070,  1090,  1051,  1072,   194,  1052,  1091,
     273,   294,  1092,   292,   274,  1055,   942,   293,   295,   195,
     947,   214,  1095,   211,   489,  1063,   287,   968,   943,   305,
     251,   969,   958,   309,  1096,   196,   197,  1069,   198,   206,
    1071,   672,  1100,   971,   944,   945,   253,   946,   953,   785,
     675,   935,  1097,   798,   951,   822,  1098,   212,   952,   217,
     288,   525,   231,   306,   965,   787,   959,  1010,   933,   799,
     209,  1011,   962,   963,   937,   224,   982,   972,   235,   957,
     254,   983,   990,  1012,   567,   936,   536,   961,  1061,   939,
     970,   265,   940,   252,   938,   941,  1003,   218,  1005,   788,
     232,   219,   560,   800,   233,   981,   564,  1002,   552,   225,
     538,  1004,   236,   980,   544,   979,   816,  1013,  1064,   996,
     674,   999,   220,   805,   583,   234,   673,  1019,  1068,  1088,
    1099,     0,     0,     0,   585,     0,   587,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   942,     0,     0,     0,   947,     0,   968,     0,
       0,     0,   969,     0,   943,     0,     0,     0,   958,     0,
       0,     0,     0,     0,   971,  1010,     0,     0,     0,  1011,
     944,   945,     0,   946,   953,     0,     0,     0,     0,     0,
     951,  1012,     0,     0,   952,     0,     0,     0,     0,     0,
       0,     0,   959,     0,     0,     0,     0,     0,   972,     0,
       0,     0,     0,     0,     0,   957,     0,     0,     0,     0,
       0,   970,     0,     0,     0,  1013
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    83,    82,    83,
      84,    85,    82,    83,    83,    77,   621,    77,    76,    77,
      78,    79,    80,   615,    82,    83,   598,    85,   860,   860,
     860,    77,    77,   860,    77,    77,   860,    10,    15,    16,
       3,    94,    78,    79,    92,     8,    78,    79,   505,   101,
     102,    99,    76,    77,    78,    79,    80,     3,    82,    83,
      17,    85,     8,   520,   101,   102,    77,    78,    79,    80,
       5,     0,     7,     3,     9,     7,    68,    69,     8,     3,
      11,    12,   533,    14,     8,    50,    17,    18,    19,     7,
       7,    68,    69,    20,   545,   546,   547,     7,    63,    64,
      65,    66,    67,    68,    69,     7,     7,   140,   141,   142,
     143,    42,    43,    44,    45,    46,    47,    48,    49,    50,
     173,   173,    87,     7,    51,    90,    53,    54,   120,   121,
      57,    58,    59,     3,     3,     3,     6,    68,    69,     8,
       8,    68,    69,   176,    75,    21,    22,    23,    24,    80,
      81,    82,    83,    84,    20,    86,     3,    50,     7,     6,
      91,   149,     3,    29,   152,   153,   154,     8,    61,   100,
       7,     3,   103,   146,     6,    68,    69,   137,   138,   110,
       3,   173,   155,   156,   157,     8,     3,   118,   119,     6,
       3,   122,   123,    51,    87,     8,   173,    90,    94,    95,
     173,    97,    68,    69,  1036,  1036,  1036,     7,   173,  1036,
      68,    69,  1036,    20,   111,   112,   113,    50,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    68,    69,     7,   173,   174,
     175,   176,   173,     7,    51,     7,   173,     3,   114,   115,
     116,   117,     8,    86,    76,    77,    78,    79,     7,    92,
      93,    94,    95,    96,    97,    50,    51,   173,     3,    42,
      43,    44,    45,     8,   866,     3,   848,    50,     6,    13,
     173,     3,    49,    68,    69,   147,     8,    60,   893,    62,
     148,     6,   150,   151,   368,    68,    69,    70,    71,    72,
      73,    74,    75,    88,    89,     3,     8,   173,   104,   105,
     106,   107,   108,   109,    87,   173,     4,    90,    91,    51,
      52,    53,    54,    55,    56,    98,     3,     3,   402,     3,
       3,     8,   406,     3,     8,     8,    68,    69,     8,     4,
     173,     3,     8,     4,   418,     3,     8,   421,   406,     4,
       8,     4,     3,     3,   428,     4,   418,     8,   418,     4,
     418,     4,     3,   421,   438,     4,   173,     8,     4,     4,
     428,     4,   418,   418,   448,   418,   418,   453,   448,   453,
     438,     3,   406,   453,   453,   421,     8,     4,   173,   421,
     448,     4,   428,     3,   418,   453,   428,   421,     8,   473,
     173,   358,   359,     3,   428,     8,     3,   418,     8,     4,
     421,     8,     4,     3,   438,   473,     3,   428,     8,     8,
       3,     8,     3,     3,   448,     8,     4,   438,     8,   453,
      42,    43,    44,    45,    68,    69,    48,     3,    50,    51,
       4,   173,     8,     8,     3,   174,     4,     4,     4,   473,
       4,     4,     4,   173,     4,     4,    68,    69,     4,    71,
      72,     4,    74,    75,     4,     4,     4,     4,     4,     4,
       4,   174,     4,   174,   174,    87,     4,   174,    90,     4,
       4,     4,     4,     4,     4,     4,    98,     4,     4,     4,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,     4,     4,     4,     4,     4,     4,     4,
     144,   145,     4,     4,   174,   589,     4,   176,     4,     4,
       4,     4,   596,     4,   176,     4,   174,     4,     4,   486,
     487,   488,     4,     4,   174,     4,   174,   174,   596,   173,
       4,     4,     4,     4,     4,     4,     4,   621,   622,     4,
     624,   174,     4,     4,     4,   176,     4,   176,   176,     4,
       4,   173,   176,   621,   622,     4,   624,     4,   174,     4,
     174,     4,   596,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   174,     4,
       4,     4,   176,     4,   176,     4,     4,   621,   622,     4,
     624,     4,   173,     7,   173,     7,     7,     7,     7,   566,
       7,     5,     5,     5,     5,    85,     5,     7,   173,     5,
       5,     5,   173,     5,     7,     5,     5,     3,   173,     7,
       7,   588,     7,     7,     5,     5,     5,   139,     5,     7,
     173,     5,   173,   173,   173,     7,   173,   173,     7,     7,
       7,     7,     7,     7,     7,   173,     7,     7,     7,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,     4,     4,     4,     4,     4,     4,     4,     4,   173,
     173,     4,     4,   173,     3,     6,     6,     3,     6,     6,
       3,     6,     3,   173,     6,     3,     6,     6,     3,     6,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     3,
       3,     6,   520,   402,     4,     6,     8,     4,     4,     4,
     174,     4,     4,   176,     4,   174,     4,     4,   174,   176,
       4,   174,   174,   174,   174,     4,     4,     4,   176,     3,
     174,     6,   174,   174,   174,   174,   174,   174,   174,   174,
       4,   173,   173,   173,   173,   173,   173,   173,     8,     8,
       4,   173,     8,     3,   174,     8,   173,   173,     4,     4,
       4,     4,   614,     5,     4,   173,     7,   851,   173,     4,
     854,   857,     4,   857,   854,   173,   860,   857,   857,   851,
     860,   851,     4,   851,   368,   176,   854,   871,   860,   857,
     874,   871,   860,   877,   176,   851,   851,   173,   851,   851,
     173,   589,   173,   871,   860,   860,   874,   860,   860,   893,
     596,   850,   174,   897,   860,   670,   174,   851,   860,   903,
     854,   406,   906,   857,   869,   893,   860,   911,   845,   897,
     851,   911,   863,   866,   853,   903,   877,   871,   906,   860,
     874,   879,   886,   911,   456,   851,   418,   862,  1036,   856,
     871,    81,   857,   874,   854,   859,   905,   903,   908,   893,
     906,   903,   448,   897,   906,   876,   453,   903,   438,   903,
     421,   906,   906,   874,   428,   872,   634,   911,  1042,   893,
     595,   897,   903,   624,   473,   906,   590,   912,  1059,  1076,
    1093,    -1,    -1,    -1,   476,    -1,   479,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1036,    -1,    -1,    -1,  1036,    -1,  1042,    -1,
      -1,    -1,  1042,    -1,  1036,    -1,    -1,    -1,  1036,    -1,
      -1,    -1,    -1,    -1,  1042,  1059,    -1,    -1,    -1,  1059,
    1036,  1036,    -1,  1036,  1036,    -1,    -1,    -1,    -1,    -1,
    1036,  1059,    -1,    -1,  1036,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1036,    -1,    -1,    -1,    -1,    -1,  1042,    -1,
      -1,    -1,    -1,    -1,    -1,  1036,    -1,    -1,    -1,    -1,
      -1,  1042,    -1,    -1,    -1,  1059
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
     209,   218,   219,   220,   222,   223,   224,   225,   226,   227,
     229,   238,   240,   242,   279,   285,   291,   297,   299,   313,
     323,   343,   348,   356,   382,   412,   414,   433,   463,   475,
     487,   488,   496,   498,   536,    15,    16,   209,   233,   234,
     235,   237,   412,   414,    60,    62,    70,    71,    72,    73,
      74,    87,    90,    98,   209,   222,   223,   224,   225,   331,
     332,   333,   335,   337,   339,   341,   343,   346,   347,   382,
     400,   412,   414,   416,   433,   458,    61,   209,   339,   341,
     382,   408,   409,   410,   412,   414,    63,    64,    65,    66,
      67,   209,   339,   341,   382,   412,   414,   424,   425,   426,
     428,   429,   431,   432,    86,    92,    93,    94,    95,    96,
      97,   209,   382,   412,   414,   441,   442,   443,   444,   446,
     448,   450,   452,   454,   456,   356,    20,    51,    53,    54,
      57,    58,    59,   209,   260,   366,   367,   368,   369,   370,
     371,   372,   374,   376,   378,   379,   381,   412,   414,    52,
      55,    56,   209,   260,   370,   376,   390,   391,   392,   393,
     394,   396,   397,   398,   399,   412,   414,   101,   102,   209,
     307,   308,   309,   311,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   144,   145,   209,
     412,   414,   502,   503,   504,   505,   507,   509,   510,   512,
     513,   514,   517,   519,   520,   521,   524,   526,   528,   147,
     548,   549,   550,    13,   540,   541,   542,     6,     3,     4,
       8,     3,   215,   545,   531,   533,   535,     4,     3,     8,
     221,   537,   230,   239,   241,   243,     4,     4,     4,     4,
       4,   228,   324,   357,   383,   413,   415,   344,   349,   286,
     298,   292,   280,   464,   434,   300,   314,   476,     4,   489,
     497,   499,     3,     8,   236,     4,     3,     8,   401,   417,
     334,   336,   338,     4,     4,   342,   340,   459,     3,     8,
     411,     3,     8,   427,     4,   430,     4,     4,     3,     8,
     457,   445,   447,   449,   451,   453,   455,     8,     3,     8,
     373,   261,     4,   377,   375,   380,     4,     8,     3,   395,
       4,     4,     8,     3,   310,   312,     3,     8,     4,   506,
     508,     4,   511,     4,     4,   515,   518,     4,     4,   522,
     525,   527,   529,     3,     8,   551,     3,     8,   543,     3,
       8,   194,   194,   173,     4,     4,     4,     4,     4,   213,
       4,     4,     4,     4,     4,     4,   174,   174,   174,   174,
     174,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   174,     4,
       4,     4,   219,     4,   176,   234,     4,     4,     4,     4,
       4,   174,   176,     4,     4,     4,   332,     4,   409,     4,
     174,     4,   174,   174,   425,     4,     4,     4,     4,     4,
       4,     4,   443,     4,     4,   174,     4,     4,     4,   176,
     368,     4,   176,   176,   392,     4,     4,   308,   176,     4,
       4,   174,     4,   174,   174,     4,     4,   176,   176,     4,
       4,     4,     4,   503,     4,   549,     4,   541,     4,     7,
       7,   194,   194,   194,   173,     7,     7,     7,     7,     5,
     173,     5,     5,     5,   196,   198,   173,    76,    77,    78,
      79,   345,     5,     5,     5,     5,     7,     5,     5,     5,
       7,     7,     7,   198,     7,     5,   205,     5,     5,   173,
     173,   173,   205,   173,     7,   173,   173,   173,   205,   205,
     205,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   194,   173,   173,   173,   137,   138,   516,   139,
     140,   141,   142,   143,   176,   523,   173,   173,   173,     5,
       5,   194,   218,   548,   540,   233,    20,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,   209,   248,   249,   250,   253,   255,
     257,   259,   260,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   272,   273,   275,   277,   248,     7,   244,   245,
     246,     7,   325,   326,   327,     7,   360,   361,   362,     7,
     384,   385,   386,     7,   350,   351,   352,    94,   173,   287,
     288,   289,   290,   203,    95,    97,   289,   293,   294,   295,
     296,    85,   281,   282,   283,     7,   465,   466,     7,   435,
     436,   437,     7,   301,   302,   303,   104,   105,   106,   107,
     108,   109,   315,   316,   317,   318,   319,   320,   321,   322,
      20,   114,   115,   116,   117,   209,   262,   412,   414,   477,
     478,   479,   482,   483,   485,   486,   120,   121,   209,   412,
     414,   490,   491,   492,   494,   502,   206,     7,   402,   403,
     404,     7,   418,   419,   420,    99,   444,   460,   461,     7,
     552,   553,   244,     8,     8,     8,     8,   251,   254,   256,
     258,     4,     4,     4,     4,     4,   271,     4,     4,   274,
     276,   278,     4,     4,     4,     3,     8,     8,   247,     6,
       3,   328,     6,     3,   363,     6,     3,   387,     6,     3,
     353,     6,     3,     3,     6,     6,     3,     6,   284,     3,
       8,   467,     3,     6,   438,     6,     3,   304,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,   480,   484,
       4,     4,     4,     3,     8,   493,   495,     3,     8,     8,
     173,   207,   208,   405,     6,     3,   421,     6,     3,   462,
       8,   554,     3,     6,     6,     4,     4,     4,     4,   174,
     176,   174,   176,   174,     4,   174,   174,     4,     4,     4,
     174,   174,   176,   249,   248,   246,   331,   327,   366,   362,
     390,   386,   209,   222,   223,   224,   225,   260,   323,   335,
     337,   339,   341,   343,   347,   354,   355,   382,   412,   414,
     458,   352,   288,   294,     4,   282,    88,    89,   209,   260,
     382,   412,   414,   468,   469,   470,   471,   472,   474,   466,
     441,   437,   307,   303,   174,   174,   174,   174,   174,   174,
     316,     4,     4,   174,   174,   174,   478,     4,     4,   491,
       6,     3,   408,   404,   424,   420,     4,   148,   150,   151,
     209,   260,   412,   414,   555,   556,   557,   558,   560,   553,
      21,    22,    23,    24,   252,   173,   173,   173,   173,   173,
     173,   173,     8,     8,     8,     8,     3,     8,   173,   473,
       4,     8,     3,     8,     8,   111,   112,   113,   481,   173,
     173,   173,   173,     8,     8,   173,   561,     4,   559,     3,
       8,   355,     4,   176,   470,     4,   174,     4,   556,   173,
       5,   173,     7,   562,   563,   564,     3,     6,   149,   152,
     153,   154,   565,   566,   567,   569,   570,   571,   563,   568,
       4,     4,     4,     3,     8,     4,   176,   174,   174,   566,
     173
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
     219,   219,   219,   219,   219,   219,   219,   219,   219,   221,
     220,   222,   223,   224,   225,   226,   228,   227,   230,   229,
     232,   231,   233,   233,   234,   234,   234,   234,   234,   236,
     235,   237,   239,   238,   241,   240,   243,   242,   244,   244,
     245,   245,   247,   246,   248,   248,   249,   249,   249,   249,
     249,   249,   249,   249,   249,   249,   249,   249,   249,   249,
     249,   249,   249,   249,   249,   249,   251,   250,   252,   252,
     252,   252,   254,   253,   256,   255,   258,   257,   259,   261,
     260,   262,   263,   264,   265,   266,   267,   268,   269,   271,
     270,   272,   274,   273,   276,   275,   278,   277,   280,   279,
     281,   281,   282,   284,   283,   286,   285,   287,   287,   288,
     288,   289,   290,   292,   291,   293,   293,   294,   294,   294,
     295,   296,   298,   297,   300,   299,   301,   301,   302,   302,
     304,   303,   306,   305,   307,   307,   307,   308,   308,   310,
     309,   312,   311,   314,   313,   315,   315,   316,   316,   316,
     316,   316,   316,   317,   318,   319,   320,   321,   322,   324,
     323,   325,   325,   326,   326,   328,   327,   330,   329,   331,
     331,   332,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   332,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   334,   333,   336,   335,   338,   337,   340,   339,   342,
     341,   344,   343,   345,   345,   345,   345,   346,   347,   349,
     348,   350,   350,   351,   351,   353,   352,   354,   354,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   357,   356,   359,   358,
     360,   360,   361,   361,   363,   362,   365,   364,   366,   366,
     367,   367,   368,   368,   368,   368,   368,   368,   368,   368,
     368,   368,   369,   370,   371,   373,   372,   375,   374,   377,
     376,   378,   380,   379,   381,   383,   382,   384,   384,   385,
     385,   387,   386,   389,   388,   390,   390,   391,   391,   392,
     392,   392,   392,   392,   392,   392,   392,   392,   393,   395,
     394,   396,   397,   398,   399,   401,   400,   402,   402,   403,
     403,   405,   404,   407,   406,   408,   408,   409,   409,   409,
     409,   409,   409,   409,   411,   410,   413,   412,   415,   414,
     417,   416,   418,   418,   419,   419,   421,   420,   423,   422,
     424,   424,   425,   425,   425,   425,   425,   425,   425,   425,
     425,   425,   425,   427,   426,   428,   430,   429,   431,   432,
     434,   433,   435,   435,   436,   436,   438,   437,   440,   439,
     441,   441,   442,   442,   443,   443,   443,   443,   443,   443,
     443,   443,   443,   443,   443,   445,   444,   447,   446,   449,
     448,   451,   450,   453,   452,   455,   454,   457,   456,   459,
     458,   460,   460,   462,   461,   464,   463,   465,   465,   467,
     466,   468,   468,   469,   469,   470,   470,   470,   470,   470,
     470,   470,   471,   473,   472,   474,   476,   475,   477,   477,
     478,   478,   478,   478,   478,   478,   478,   478,   478,   480,
     479,   481,   481,   481,   482,   484,   483,   485,   486,   487,
     489,   488,   490,   490,   491,   491,   491,   491,   491,   493,
     492,   495,   494,   497,   496,   499,   498,   501,   500,   502,
     502,   503,   503,   503,   503,   503,   503,   503,   503,   503,
     503,   503,   503,   503,   503,   503,   503,   503,   503,   504,
     506,   505,   508,   507,   509,   511,   510,   512,   513,   515,
     514,   516,   516,   518,   517,   519,   520,   522,   521,   523,
     523,   523,   523,   523,   525,   524,   527,   526,   529,   528,
     531,   530,   533,   532,   535,   534,   537,   536,   539,   538,
     540,   540,   541,   543,   542,   545,   544,   547,   546,   548,
     548,   549,   551,   550,   552,   552,   554,   553,   555,   555,
     556,   556,   556,   556,   556,   556,   556,   557,   559,   558,
     561,   560,   562,   562,   564,   563,   565,   565,   566,   566,
     566,   566,   568,   567,   569,   570,   571
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
       1,     3,     1,     0,     6,     0,     6,     0,     4,     1,
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
     465,   466,   467,   468,   469,   470,   471,   472,   473,   476,
     476,   484,   489,   494,   499,   504,   509,   509,   517,   517,
     528,   528,   537,   538,   541,   542,   543,   544,   545,   548,
     548,   558,   564,   564,   576,   576,   588,   588,   598,   599,
     602,   603,   606,   606,   616,   617,   620,   621,   622,   623,
     624,   625,   626,   627,   628,   629,   630,   631,   632,   633,
     634,   635,   636,   637,   638,   639,   642,   642,   649,   650,
     651,   652,   655,   655,   663,   663,   671,   671,   679,   684,
     684,   692,   697,   702,   707,   712,   717,   722,   727,   732,
     732,   740,   745,   745,   753,   753,   761,   761,   769,   769,
     779,   780,   782,   784,   784,   802,   802,   812,   813,   816,
     817,   820,   825,   830,   830,   840,   841,   844,   845,   846,
     849,   854,   861,   861,   871,   871,   881,   882,   885,   886,
     889,   889,   899,   899,   909,   910,   911,   914,   915,   918,
     918,   926,   926,   934,   934,   945,   946,   949,   950,   951,
     952,   953,   954,   957,   962,   967,   972,   977,   982,   990,
     990,  1003,  1004,  1007,  1008,  1015,  1015,  1041,  1041,  1052,
    1053,  1057,  1058,  1059,  1060,  1061,  1062,  1063,  1064,  1065,
    1066,  1067,  1068,  1069,  1070,  1071,  1072,  1073,  1074,  1075,
    1076,  1079,  1079,  1087,  1087,  1095,  1095,  1103,  1103,  1111,
    1111,  1121,  1121,  1128,  1129,  1130,  1131,  1134,  1139,  1147,
    1147,  1158,  1159,  1163,  1164,  1167,  1167,  1175,  1176,  1179,
    1180,  1181,  1182,  1183,  1184,  1185,  1186,  1187,  1188,  1189,
    1190,  1191,  1192,  1193,  1194,  1195,  1202,  1202,  1215,  1215,
    1224,  1225,  1228,  1229,  1234,  1234,  1249,  1249,  1263,  1264,
    1267,  1268,  1271,  1272,  1273,  1274,  1275,  1276,  1277,  1278,
    1279,  1280,  1283,  1285,  1290,  1292,  1292,  1300,  1300,  1308,
    1308,  1316,  1318,  1318,  1326,  1335,  1335,  1347,  1348,  1353,
    1354,  1359,  1359,  1371,  1371,  1383,  1384,  1389,  1390,  1395,
    1396,  1397,  1398,  1399,  1400,  1401,  1402,  1403,  1406,  1408,
    1408,  1416,  1418,  1420,  1425,  1433,  1433,  1445,  1446,  1449,
    1450,  1453,  1453,  1463,  1463,  1472,  1473,  1476,  1477,  1478,
    1479,  1480,  1481,  1482,  1485,  1485,  1493,  1493,  1518,  1518,
    1548,  1548,  1560,  1561,  1564,  1565,  1568,  1568,  1580,  1580,
    1592,  1593,  1596,  1597,  1598,  1599,  1600,  1601,  1602,  1603,
    1604,  1605,  1606,  1609,  1609,  1617,  1622,  1622,  1630,  1635,
    1643,  1643,  1653,  1654,  1657,  1658,  1661,  1661,  1670,  1670,
    1679,  1680,  1683,  1684,  1688,  1689,  1690,  1691,  1692,  1693,
    1694,  1695,  1696,  1697,  1698,  1701,  1701,  1711,  1711,  1721,
    1721,  1729,  1729,  1737,  1737,  1745,  1745,  1753,  1753,  1766,
    1766,  1776,  1777,  1780,  1780,  1791,  1791,  1801,  1802,  1805,
    1805,  1815,  1816,  1819,  1820,  1823,  1824,  1825,  1826,  1827,
    1828,  1829,  1832,  1834,  1834,  1842,  1850,  1850,  1862,  1863,
    1866,  1867,  1868,  1869,  1870,  1871,  1872,  1873,  1874,  1877,
    1877,  1884,  1885,  1886,  1889,  1894,  1894,  1902,  1907,  1914,
    1921,  1921,  1931,  1932,  1935,  1936,  1937,  1938,  1939,  1942,
    1942,  1950,  1950,  1960,  1960,  2000,  2000,  2012,  2012,  2022,
    2023,  2026,  2027,  2028,  2029,  2030,  2031,  2032,  2033,  2034,
    2035,  2036,  2037,  2038,  2039,  2040,  2041,  2042,  2043,  2046,
    2051,  2051,  2059,  2059,  2067,  2072,  2072,  2080,  2085,  2090,
    2090,  2098,  2099,  2102,  2102,  2110,  2115,  2120,  2120,  2128,
    2131,  2134,  2137,  2140,  2146,  2146,  2154,  2154,  2162,  2162,
    2172,  2172,  2179,  2179,  2186,  2186,  2195,  2195,  2206,  2206,
    2216,  2217,  2221,  2224,  2224,  2239,  2239,  2249,  2249,  2260,
    2261,  2265,  2269,  2269,  2281,  2282,  2286,  2286,  2294,  2295,
    2298,  2299,  2300,  2301,  2302,  2303,  2304,  2307,  2312,  2312,
    2320,  2320,  2330,  2331,  2334,  2334,  2342,  2343,  2346,  2347,
    2348,  2349,  2352,  2352,  2360,  2365,  2370
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
#line 5140 "dhcp6_parser.cc" // lalr1.cc:1242
#line 2375 "dhcp6_parser.yy" // lalr1.cc:1243


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
