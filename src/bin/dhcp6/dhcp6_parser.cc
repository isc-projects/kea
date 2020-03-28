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
      case 218: // value
      case 222: // map_value
      case 263: // ddns_replace_client_name_value
      case 297: // db_type
      case 400: // hr_mode
      case 536: // duid_type
      case 579: // ncr_protocol_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 200: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 199: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 198: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 197: // "constant string"
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
      case 218: // value
      case 222: // map_value
      case 263: // ddns_replace_client_name_value
      case 297: // db_type
      case 400: // hr_mode
      case 536: // duid_type
      case 579: // ncr_protocol_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 200: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 199: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 198: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 197: // "constant string"
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
      case 218: // value
      case 222: // map_value
      case 263: // ddns_replace_client_name_value
      case 297: // db_type
      case 400: // hr_mode
      case 536: // duid_type
      case 579: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 200: // "boolean"
        value.move< bool > (that.value);
        break;

      case 199: // "floating point"
        value.move< double > (that.value);
        break;

      case 198: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 197: // "constant string"
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
      case 197: // "constant string"
#line 276 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < std::string > (); }
#line 404 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 198: // "integer"
#line 276 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 410 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 199: // "floating point"
#line 276 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < double > (); }
#line 416 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 200: // "boolean"
#line 276 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < bool > (); }
#line 422 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 218: // value
#line 276 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 222: // map_value
#line 276 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 434 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 263: // ddns_replace_client_name_value
#line 276 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 440 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 297: // db_type
#line 276 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 446 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 400: // hr_mode
#line 276 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 452 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 536: // duid_type
#line 276 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 458 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 579: // ncr_protocol_value
#line 276 "dhcp6_parser.yy" // lalr1.cc:676
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
      case 218: // value
      case 222: // map_value
      case 263: // ddns_replace_client_name_value
      case 297: // db_type
      case 400: // hr_mode
      case 536: // duid_type
      case 579: // ncr_protocol_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 200: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 199: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 198: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 197: // "constant string"
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
#line 285 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 730 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 4:
#line 286 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.CONFIG; }
#line 736 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 6:
#line 287 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP6; }
#line 742 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 8:
#line 288 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 748 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 10:
#line 289 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.SUBNET6; }
#line 754 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 12:
#line 290 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.POOLS; }
#line 760 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 14:
#line 291 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 766 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 16:
#line 292 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 772 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 18:
#line 293 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP6; }
#line 778 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 20:
#line 294 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 784 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 22:
#line 295 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 790 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 24:
#line 296 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 796 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 26:
#line 297 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 802 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 28:
#line 298 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.LOGGING; }
#line 808 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 30:
#line 299 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 814 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 32:
#line 307 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 820 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 33:
#line 308 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 826 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 34:
#line 309 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 832 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 35:
#line 310 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 838 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 36:
#line 311 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 844 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 37:
#line 312 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 850 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 38:
#line 313 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 856 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 39:
#line 316 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 865 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 40:
#line 321 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 876 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 41:
#line 326 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 886 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 42:
#line 332 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 892 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 45:
#line 339 "dhcp6_parser.yy" // lalr1.cc:919
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 901 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 46:
#line 343 "dhcp6_parser.yy" // lalr1.cc:919
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 911 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 47:
#line 350 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 920 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 48:
#line 353 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // list parsing complete. Put any sanity checking here
}
#line 928 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 51:
#line 361 "dhcp6_parser.yy" // lalr1.cc:919
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 937 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 52:
#line 365 "dhcp6_parser.yy" // lalr1.cc:919
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 946 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 53:
#line 372 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // List parsing about to start
}
#line 954 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 54:
#line 374 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 963 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 57:
#line 383 "dhcp6_parser.yy" // lalr1.cc:919
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 972 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 58:
#line 387 "dhcp6_parser.yy" // lalr1.cc:919
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 981 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 59:
#line 398 "dhcp6_parser.yy" // lalr1.cc:919
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 992 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 60:
#line 408 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1003 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 61:
#line 413 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 436 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 443 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1039 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 72:
#line 451 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1049 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 73:
#line 455 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No global parameter is required
    // parsing completed
}
#line 1058 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 125:
#line 517 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1066 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 126:
#line 519 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1076 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 127:
#line 525 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1085 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 128:
#line 530 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1094 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 129:
#line 535 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1103 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 130:
#line 540 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1112 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 131:
#line 545 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 132:
#line 550 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1130 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 133:
#line 555 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1139 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 134:
#line 560 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1148 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 135:
#line 565 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1157 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 136:
#line 570 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1166 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 137:
#line 575 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1175 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 138:
#line 580 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1184 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 139:
#line 585 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1193 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 140:
#line 590 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1202 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 141:
#line 595 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1211 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 142:
#line 600 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1219 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 143:
#line 602 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1228 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 144:
#line 608 "dhcp6_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1236 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 145:
#line 611 "dhcp6_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1244 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 146:
#line 614 "dhcp6_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1252 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 147:
#line 617 "dhcp6_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1260 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 148:
#line 620 "dhcp6_parser.yy" // lalr1.cc:919
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1269 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 149:
#line 626 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1277 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 150:
#line 628 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1287 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 151:
#line 634 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1295 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 152:
#line 636 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1305 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 153:
#line 642 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1313 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 154:
#line 644 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1323 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 155:
#line 650 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1331 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 156:
#line 652 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1341 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 157:
#line 658 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1349 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 158:
#line 660 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1359 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 159:
#line 666 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1370 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 160:
#line 671 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1380 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 161:
#line 677 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1390 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 162:
#line 681 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1399 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 170:
#line 697 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1410 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 171:
#line 702 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1419 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 172:
#line 707 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1428 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 173:
#line 713 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1439 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 174:
#line 718 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1450 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 175:
#line 725 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1461 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 176:
#line 730 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1472 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 177:
#line 737 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1483 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 178:
#line 742 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1492 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 183:
#line 755 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1502 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 184:
#line 759 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1512 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 213:
#line 797 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1520 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 214:
#line 799 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1529 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 215:
#line 804 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1535 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 216:
#line 805 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1541 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 217:
#line 806 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1547 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 218:
#line 807 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1553 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 219:
#line 810 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1561 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 220:
#line 812 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1571 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 221:
#line 818 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1579 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 222:
#line 820 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1589 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 223:
#line 826 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1597 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 224:
#line 828 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1607 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 225:
#line 834 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1616 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 226:
#line 839 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1624 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 227:
#line 841 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1634 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 228:
#line 847 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1643 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 229:
#line 852 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1652 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 230:
#line 857 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1661 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 231:
#line 862 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1670 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 232:
#line 867 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1679 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 233:
#line 872 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1688 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 234:
#line 877 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ssl", n);
}
#line 1697 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 235:
#line 882 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1705 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 236:
#line 884 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr sslca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ssl-ca", sslca);
    ctx.leave();
}
#line 1715 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 237:
#line 890 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1723 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 238:
#line 892 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr sslc(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ssl-cert", sslc);
    ctx.leave();
}
#line 1733 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 239:
#line 898 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1741 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 240:
#line 900 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr sslk(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ssl-key", sslk);
    ctx.leave();
}
#line 1751 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 241:
#line 906 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1759 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 242:
#line 908 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr sslp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ssl-password", sslp);
    ctx.leave();
}
#line 1769 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 243:
#line 914 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1778 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 244:
#line 919 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1787 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 245:
#line 924 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1796 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 246:
#line 929 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1804 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 247:
#line 931 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1814 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 248:
#line 937 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1823 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 249:
#line 942 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1831 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 250:
#line 944 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1841 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 251:
#line 950 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1849 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 252:
#line 952 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1859 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 253:
#line 958 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1867 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 254:
#line 960 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1877 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 255:
#line 966 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1888 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 256:
#line 971 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1897 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 260:
#line 981 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1905 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 261:
#line 983 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 1925 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 262:
#line 999 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1936 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 263:
#line 1004 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1945 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 268:
#line 1017 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1954 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 269:
#line 1022 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1963 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 270:
#line 1027 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1974 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 271:
#line 1032 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1983 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 277:
#line 1046 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1992 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 278:
#line 1051 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2001 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 279:
#line 1058 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2012 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 280:
#line 1063 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2021 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 281:
#line 1068 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2032 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 282:
#line 1073 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2041 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 287:
#line 1086 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2051 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 288:
#line 1090 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2061 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 289:
#line 1096 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2071 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 290:
#line 1100 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2081 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 296:
#line 1115 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2089 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 297:
#line 1117 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2099 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 298:
#line 1123 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2107 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 299:
#line 1125 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2116 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 300:
#line 1131 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2127 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 301:
#line 1136 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2137 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 310:
#line 1154 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2146 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 311:
#line 1159 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2155 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 312:
#line 1164 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2164 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 313:
#line 1169 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2173 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 314:
#line 1174 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2182 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 315:
#line 1179 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2191 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 316:
#line 1187 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2202 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 317:
#line 1192 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2211 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 322:
#line 1212 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2221 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 323:
#line 1216 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 2247 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 324:
#line 1238 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2257 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 325:
#line 1242 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2267 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 363:
#line 1291 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2275 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 364:
#line 1293 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2285 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 365:
#line 1299 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2293 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 366:
#line 1301 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2303 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 367:
#line 1307 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2311 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 368:
#line 1309 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2321 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 369:
#line 1315 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2329 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 370:
#line 1317 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2339 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 371:
#line 1323 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2350 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 372:
#line 1328 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2359 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 373:
#line 1333 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2367 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 374:
#line 1335 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2376 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 375:
#line 1340 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2382 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 376:
#line 1341 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2388 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 377:
#line 1342 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2394 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 378:
#line 1343 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2400 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 379:
#line 1346 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2409 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 380:
#line 1351 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2418 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 381:
#line 1359 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2429 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 382:
#line 1364 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2438 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 387:
#line 1379 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2448 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 388:
#line 1383 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 2456 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 423:
#line 1429 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2467 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 424:
#line 1434 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2476 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 425:
#line 1442 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2485 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 426:
#line 1445 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 2493 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 431:
#line 1461 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2503 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 432:
#line 1465 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2515 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 433:
#line 1476 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2525 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 434:
#line 1480 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2537 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 450:
#line 1512 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2546 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 452:
#line 1519 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2554 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 453:
#line 1521 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2564 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 454:
#line 1527 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2572 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 455:
#line 1529 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2582 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 456:
#line 1535 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2590 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 457:
#line 1537 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2600 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 459:
#line 1545 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2608 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 460:
#line 1547 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2618 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 461:
#line 1553 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2627 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 462:
#line 1562 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2638 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 463:
#line 1567 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2647 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 468:
#line 1586 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2657 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 469:
#line 1590 "dhcp6_parser.yy" // lalr1.cc:919
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2666 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 470:
#line 1598 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2676 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 471:
#line 1602 "dhcp6_parser.yy" // lalr1.cc:919
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2685 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 486:
#line 1635 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2693 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 487:
#line 1637 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2703 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 490:
#line 1647 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2712 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 491:
#line 1652 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2721 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 492:
#line 1660 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2732 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 493:
#line 1665 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2741 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 498:
#line 1680 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2751 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 499:
#line 1684 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2761 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 500:
#line 1690 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2771 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 501:
#line 1694 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2780 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 511:
#line 1712 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2788 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 512:
#line 1714 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2798 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 513:
#line 1720 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2806 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 514:
#line 1722 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 2833 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 515:
#line 1745 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2841 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 516:
#line 1747 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 2870 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 517:
#line 1775 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2881 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 518:
#line 1780 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2890 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 523:
#line 1795 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2900 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 524:
#line 1799 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2912 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 525:
#line 1807 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2922 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 526:
#line 1811 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2934 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 540:
#line 1836 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2942 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 541:
#line 1838 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2952 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 542:
#line 1844 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2961 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 543:
#line 1849 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2969 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 544:
#line 1851 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2979 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 545:
#line 1857 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2988 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 546:
#line 1862 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2997 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 547:
#line 1870 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3008 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 548:
#line 1875 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3017 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 553:
#line 1888 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3027 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 554:
#line 1892 "dhcp6_parser.yy" // lalr1.cc:919
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3036 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 555:
#line 1897 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3046 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 556:
#line 1901 "dhcp6_parser.yy" // lalr1.cc:919
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3055 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 572:
#line 1928 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3066 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 573:
#line 1933 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3075 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 574:
#line 1938 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3086 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 575:
#line 1943 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3095 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 576:
#line 1948 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3103 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 577:
#line 1950 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3113 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 578:
#line 1956 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3121 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 579:
#line 1958 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3131 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 580:
#line 1964 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3139 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 581:
#line 1966 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3149 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 582:
#line 1972 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3157 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 583:
#line 1974 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3167 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 584:
#line 1980 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3178 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 585:
#line 1985 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3187 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 586:
#line 1993 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3198 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 587:
#line 1998 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3207 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 590:
#line 2007 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3215 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 591:
#line 2009 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3225 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 592:
#line 2018 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3236 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 593:
#line 2023 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3245 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 596:
#line 2032 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3255 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 597:
#line 2036 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3265 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 610:
#line 2061 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3273 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 611:
#line 2063 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3283 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 612:
#line 2069 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3292 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 613:
#line 2077 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3303 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 614:
#line 2082 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3314 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 626:
#line 2104 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 3322 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 627:
#line 2106 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3331 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 628:
#line 2111 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3337 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 629:
#line 2112 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3343 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 630:
#line 2113 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3349 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 631:
#line 2116 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3358 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 632:
#line 2121 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3366 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 633:
#line 2123 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3376 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 634:
#line 2129 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3385 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 635:
#line 2134 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3394 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 636:
#line 2141 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3403 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 637:
#line 2148 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3414 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 638:
#line 2153 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3423 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 646:
#line 2169 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3431 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 647:
#line 2171 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3441 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 648:
#line 2177 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3449 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 649:
#line 2179 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3459 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 650:
#line 2187 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3470 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 651:
#line 2192 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3481 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 660:
#line 2211 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3490 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 661:
#line 2216 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3498 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 662:
#line 2218 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3508 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 663:
#line 2224 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3517 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 664:
#line 2229 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3525 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 665:
#line 2231 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3534 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 666:
#line 2238 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3545 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 667:
#line 2243 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3556 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 668:
#line 2250 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3566 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 669:
#line 2254 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3576 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 690:
#line 2284 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3585 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 691:
#line 2289 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3593 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 692:
#line 2291 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3603 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 693:
#line 2297 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3611 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 694:
#line 2299 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3621 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 695:
#line 2305 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3630 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 696:
#line 2310 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3638 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 697:
#line 2312 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3648 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 698:
#line 2318 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3657 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 699:
#line 2323 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3666 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 700:
#line 2328 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3674 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 701:
#line 2330 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3683 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 702:
#line 2336 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3689 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 703:
#line 2337 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3695 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 704:
#line 2340 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3703 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 705:
#line 2342 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3713 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 706:
#line 2349 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3722 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 707:
#line 2355 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3731 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 708:
#line 2361 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3739 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 709:
#line 2363 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3748 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 710:
#line 2369 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3756 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 711:
#line 2371 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3766 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 712:
#line 2378 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3774 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 713:
#line 2380 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3784 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 714:
#line 2387 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3792 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 715:
#line 2389 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3802 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 716:
#line 2397 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3810 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 717:
#line 2399 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3819 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 718:
#line 2404 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3827 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 719:
#line 2406 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3836 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 720:
#line 2411 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3844 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 721:
#line 2413 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3853 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 722:
#line 2420 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3864 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 723:
#line 2425 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3874 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 724:
#line 2431 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3884 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 725:
#line 2435 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No config_control params are required
    // parsing completed
}
#line 3893 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 730:
#line 2450 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3904 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 731:
#line 2455 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3913 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 732:
#line 2460 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3922 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 733:
#line 2470 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3933 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 734:
#line 2475 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3942 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 735:
#line 2480 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3952 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 736:
#line 2484 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 3960 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 740:
#line 2500 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3971 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 741:
#line 2505 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3980 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 744:
#line 2517 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3990 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 745:
#line 2521 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 3998 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 755:
#line 2538 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4007 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 756:
#line 2543 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4015 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 757:
#line 2545 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4025 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 758:
#line 2551 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4036 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 759:
#line 2556 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4045 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 762:
#line 2565 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4055 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 763:
#line 2569 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 4063 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 771:
#line 2584 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4071 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 772:
#line 2586 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4081 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 773:
#line 2592 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4090 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 774:
#line 2597 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4099 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 775:
#line 2602 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4108 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 776:
#line 2607 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4116 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 777:
#line 2609 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4126 "dhcp6_parser.cc" // lalr1.cc:919
    break;


#line 4130 "dhcp6_parser.cc" // lalr1.cc:919
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


  const short Dhcp6Parser::yypact_ninf_ = -947;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     141,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,    67,    33,    83,    92,
     107,   123,   131,   133,   137,   148,   157,   183,   214,   216,
     222,   231,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,    33,   -49,    29,   116,    27,   499,   118,   189,
      37,    93,    68,   -10,   -64,   592,   111,    46,  -947,   117,
     244,   259,   277,   298,  -947,  -947,  -947,  -947,  -947,   310,
    -947,    88,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,   316,   373,   374,   377,   383,   387,
     393,   399,   403,   409,   422,   429,  -947,   432,   433,   441,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,   444,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,    94,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,   445,  -947,
     109,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,   446,   453,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,   129,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,   155,  -947,
    -947,  -947,  -947,  -947,   456,  -947,   460,   461,  -947,  -947,
    -947,  -947,  -947,  -947,   188,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,   296,   309,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,   313,  -947,  -947,   462,  -947,  -947,  -947,   469,
    -947,  -947,   407,   414,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,   471,   472,  -947,
    -947,  -947,  -947,   473,   477,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,   194,  -947,  -947,
    -947,   478,  -947,  -947,   479,  -947,   481,   484,  -947,  -947,
     491,   492,  -947,  -947,  -947,  -947,  -947,  -947,  -947,   232,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,   234,  -947,  -947,  -947,
     493,   248,  -947,  -947,  -947,  -947,    33,    33,  -947,   301,
     495,   496,   497,   498,   503,  -947,    29,  -947,   506,   507,
     508,   509,   512,   515,   322,   323,   325,   327,   328,   329,
     330,   332,   331,   334,   335,   337,   528,   336,   338,   339,
     533,   536,   537,   538,   539,   540,   555,   556,   563,   564,
     566,   567,   568,   569,   570,   571,   572,   573,   574,   384,
     576,   579,   580,   581,   582,   593,   116,  -947,   595,   396,
      27,  -947,   596,   597,   599,   600,   601,   410,   412,   603,
     607,   609,   499,  -947,   610,   118,  -947,   611,   418,   615,
     423,   424,   189,  -947,   616,   619,   621,   622,   623,   624,
     625,  -947,    37,  -947,   626,   627,   426,   628,   629,   630,
     437,  -947,    68,   635,   440,   442,  -947,   -10,   639,   640,
       0,  -947,   448,   641,   642,   449,   645,   452,   457,   652,
     653,   458,   459,   656,   657,   658,   660,   592,  -947,   111,
    -947,   661,   494,    46,  -947,  -947,  -947,   685,   686,   687,
      33,    33,    33,  -947,   500,   688,   691,   692,   693,   700,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,   510,  -947,  -947,  -947,   -71,   513,   516,   701,
     711,   712,   713,   521,   333,   714,   716,   717,   718,   719,
     720,   723,   724,   725,   726,  -947,   727,   728,   729,   527,
     534,   732,  -947,   747,  -947,  -947,   748,   749,   558,   559,
     560,  -947,  -947,   747,   561,   754,  -947,   565,  -947,   575,
    -947,   577,  -947,  -947,  -947,   747,   747,   747,   578,   583,
     584,   585,  -947,   586,   587,  -947,   588,   589,   594,  -947,
    -947,   598,  -947,  -947,  -947,   602,    33,  -947,  -947,   604,
     605,  -947,   606,  -947,  -947,    54,   608,  -947,  -947,   -71,
     612,   613,   614,  -947,  -947,   758,  -947,  -947,    33,   116,
     111,  -947,  -947,  -947,  -947,    46,    27,   317,   317,   757,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,   759,
     760,   761,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
     762,   -73,    33,   308,   666,   766,   769,   770,   165,   182,
     112,    16,   592,  -947,  -947,   771,  -947,  -947,   772,   783,
    -947,  -947,  -947,  -947,  -947,   -67,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,   757,  -947,   258,   261,   292,
     299,  -947,  -947,  -947,  -947,   788,   789,   790,   792,   793,
    -947,   794,   796,  -947,  -947,  -947,   800,   801,   802,   803,
     804,  -947,  -947,  -947,  -947,  -947,   300,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,   302,  -947,   806,   810,  -947,  -947,   808,
     812,  -947,  -947,   813,   815,  -947,  -947,   814,   818,  -947,
    -947,   816,   820,  -947,  -947,  -947,    43,  -947,  -947,  -947,
     819,  -947,  -947,  -947,    70,  -947,  -947,  -947,  -947,   363,
    -947,  -947,  -947,    77,  -947,  -947,   821,   823,  -947,  -947,
     822,   826,  -947,   827,   828,   829,   830,   831,   832,   364,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,   833,
     834,   835,  -947,  -947,  -947,  -947,   365,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,   366,  -947,
    -947,  -947,   836,  -947,   837,  -947,  -947,  -947,   367,  -947,
    -947,  -947,  -947,  -947,   381,  -947,   254,  -947,   633,  -947,
     838,   839,  -947,  -947,   840,   842,  -947,  -947,  -947,   841,
    -947,   844,  -947,  -947,  -947,  -947,   843,   847,   848,   849,
     618,   643,   650,   654,   659,   851,   662,   663,   852,   854,
     855,   664,   665,   667,   668,   669,   860,   861,   864,   866,
     317,  -947,  -947,   317,  -947,   757,   499,  -947,   759,    68,
    -947,   760,   -10,  -947,   761,   620,  -947,   762,   -73,  -947,
    -947,   308,  -947,   867,   666,  -947,   179,   766,  -947,    37,
    -947,   769,   -64,  -947,   770,   674,   675,   676,   677,   678,
     679,   165,  -947,   874,   875,   682,   683,   684,   182,  -947,
     879,   880,   112,  -947,   689,   881,   690,   882,    16,  -947,
    -947,   209,   771,  -947,  -947,   884,   888,   118,  -947,   772,
     189,  -947,   783,   883,  -947,  -947,   447,   696,   697,   702,
    -947,  -947,  -947,  -947,  -947,   703,  -947,  -947,   708,   710,
     730,  -947,  -947,  -947,  -947,  -947,   733,   744,   746,   755,
    -947,   382,  -947,   390,  -947,   889,  -947,   902,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,   391,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,   791,  -947,  -947,   912,
    -947,  -947,  -947,  -947,  -947,   913,   919,  -947,  -947,  -947,
    -947,  -947,   917,  -947,   392,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,   208,   797,  -947,  -947,  -947,  -947,   798,
     811,  -947,  -947,   817,  -947,    33,  -947,  -947,   925,  -947,
    -947,  -947,  -947,  -947,   401,  -947,  -947,  -947,  -947,  -947,
    -947,   824,   402,  -947,   411,  -947,   845,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,   620,  -947,  -947,
     940,   768,  -947,   179,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,   953,   795,   955,   209,  -947,
    -947,  -947,  -947,  -947,  -947,   846,  -947,  -947,   961,  -947,
     850,  -947,  -947,   984,  -947,  -947,   276,  -947,    17,   984,
    -947,  -947,   993,  1005,  1008,  -947,   413,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  1011,   825,   853,   856,  1012,    17,
    -947,   858,  -947,  -947,  -947,   859,  -947,  -947,  -947
  };

  const unsigned short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   161,     9,
     324,    11,   500,    13,   525,    15,   555,    17,   425,    19,
     433,    21,   470,    23,   289,    25,   668,    27,   735,    29,
     724,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     557,     0,   435,   472,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   733,   716,   718,   720,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   125,   722,
     159,   173,   175,   177,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   157,     0,     0,     0,
     142,   149,   151,   316,   423,   462,   513,   515,   373,   381,
     262,   279,   270,   255,   592,   547,   281,   300,   613,     0,
     637,   650,   666,   153,   155,   740,   124,     0,    74,    76,
      77,    78,    79,    80,    81,    82,    83,    84,   112,   113,
     114,    85,   118,   119,   120,   121,   122,   123,   116,   117,
     110,    88,    89,    90,    91,   107,    92,    94,    93,    98,
      99,    86,   111,    87,    96,    97,   105,   106,   108,    95,
     100,   101,   102,   103,   104,   109,   115,   170,     0,   169,
       0,   163,   165,   166,   167,   168,   492,   517,   363,   365,
     367,     0,     0,   371,   369,   586,   362,   328,   329,   330,
     331,   332,   333,   334,   335,   351,   352,   353,   356,   357,
     358,   359,   360,   361,   354,   355,     0,   326,   339,   340,
     341,   344,   345,   347,   342,   343,   336,   337,   349,   350,
     338,   346,   348,   511,   510,   506,   507,   505,     0,   502,
     504,   508,   509,   540,     0,   543,     0,     0,   539,   533,
     534,   532,   537,   538,     0,   527,   529,   530,   535,   536,
     531,   584,   572,   574,   576,   578,   580,   582,   571,   568,
     569,   570,     0,   558,   559,   563,   564,   561,   565,   566,
     567,   562,     0,   452,   226,     0,   456,   454,   459,     0,
     448,   449,     0,   436,   437,   439,   451,   440,   441,   442,
     458,   443,   444,   445,   446,   447,   486,     0,     0,   484,
     485,   488,   489,     0,   473,   474,   476,   477,   478,   479,
     480,   481,   482,   483,   296,   298,   293,     0,   291,   294,
     295,     0,   691,   693,     0,   696,     0,     0,   700,   704,
       0,     0,   708,   710,   712,   714,   689,   687,   688,     0,
     670,   672,   673,   674,   675,   676,   677,   678,   679,   680,
     681,   682,   683,   684,   685,   686,     0,   737,   739,   730,
       0,     0,   726,   728,   729,    48,     0,     0,    41,     0,
       0,     0,     0,     0,     0,    59,     0,    61,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    73,     0,     0,
       0,   162,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   325,     0,     0,   501,     0,     0,     0,
       0,     0,     0,   526,     0,     0,     0,     0,     0,     0,
       0,   556,     0,   426,     0,     0,     0,     0,     0,     0,
       0,   434,     0,     0,     0,     0,   471,     0,     0,     0,
       0,   290,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   669,     0,
     736,     0,     0,     0,   725,    52,    45,     0,     0,     0,
       0,     0,     0,    63,     0,     0,     0,     0,     0,     0,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,     0,   139,   140,   141,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   636,     0,     0,     0,     0,
       0,     0,    75,     0,   172,   164,     0,     0,     0,     0,
       0,   379,   380,     0,     0,     0,   327,     0,   503,     0,
     542,     0,   545,   546,   528,     0,     0,     0,     0,     0,
       0,     0,   560,     0,     0,   450,     0,     0,     0,   461,
     438,     0,   490,   491,   475,     0,     0,   292,   690,     0,
       0,   695,     0,   698,   699,     0,     0,   706,   707,     0,
       0,     0,     0,   671,   738,     0,   732,   727,     0,     0,
       0,   717,   719,   721,   126,     0,     0,     0,     0,   179,
     158,   144,   145,   146,   147,   148,   143,   150,   152,   318,
     427,   464,    42,   514,   516,   375,   376,   377,   378,   374,
     383,     0,    49,     0,     0,     0,   549,   283,     0,     0,
       0,     0,     0,   154,   156,     0,    53,   171,   494,   519,
     364,   366,   368,   372,   370,     0,   512,   541,   544,   585,
     573,   575,   577,   579,   581,   583,   453,   227,   457,   455,
     460,   487,   297,   299,   692,   694,   697,   702,   703,   701,
     705,   709,   711,   713,   715,   179,    46,     0,     0,     0,
       0,   213,   219,   221,   223,     0,     0,     0,     0,     0,
     246,     0,     0,   249,   251,   253,     0,     0,     0,     0,
       0,   235,   237,   239,   241,   212,     0,   185,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   199,   206,
     207,   208,   209,   210,   211,   200,   201,   202,   197,   198,
     203,   204,   205,     0,   183,     0,   180,   181,   322,     0,
     319,   320,   431,     0,   428,   429,   468,     0,   465,   466,
     387,     0,   384,   385,   268,   269,     0,   264,   266,   267,
       0,   277,   278,   274,     0,   272,   275,   276,   260,     0,
     257,   259,   596,     0,   594,   553,     0,   550,   551,   287,
       0,   284,   285,     0,     0,     0,     0,     0,     0,     0,
     302,   304,   305,   306,   307,   308,   309,   626,   632,     0,
       0,     0,   625,   622,   623,   624,     0,   615,   617,   620,
     618,   619,   621,   646,   648,   645,   643,   644,     0,   639,
     641,   642,     0,   661,     0,   664,   657,   658,     0,   652,
     654,   655,   656,   659,     0,   744,     0,   742,    55,   498,
       0,   495,   496,   523,     0,   520,   521,   590,   589,     0,
     588,     0,    71,   734,   723,   160,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   174,   176,     0,   178,     0,     0,   317,     0,   435,
     424,     0,   472,   463,     0,     0,   382,     0,     0,   263,
     280,     0,   271,     0,     0,   256,   598,     0,   593,   557,
     548,     0,     0,   282,     0,     0,     0,     0,     0,     0,
       0,     0,   301,     0,     0,     0,     0,     0,     0,   614,
       0,     0,     0,   638,     0,     0,     0,     0,     0,   651,
     667,     0,     0,   741,    57,     0,    56,     0,   493,     0,
       0,   518,     0,     0,   587,   731,     0,     0,     0,     0,
     225,   228,   229,   230,   231,     0,   248,   232,     0,     0,
       0,   243,   244,   245,   233,   234,     0,     0,     0,     0,
     186,     0,   182,     0,   321,     0,   430,     0,   467,   422,
     402,   403,   404,   406,   407,   408,   395,   396,   411,   412,
     413,   416,   417,   418,   419,   420,   421,   414,   415,   391,
     392,   393,   394,   400,   401,   399,   405,     0,   389,   397,
     409,   410,   398,   386,   265,   273,     0,   258,   610,     0,
     608,   609,   605,   606,   607,     0,   599,   600,   602,   603,
     604,   595,     0,   552,     0,   286,   310,   311,   312,   313,
     314,   315,   303,     0,     0,   631,   634,   635,   616,     0,
       0,   640,   660,     0,   663,     0,   653,   758,     0,   756,
     754,   748,   752,   753,     0,   746,   750,   751,   749,   743,
      54,     0,     0,   497,     0,   522,     0,   215,   216,   217,
     218,   214,   220,   222,   224,   247,   250,   252,   254,   236,
     238,   240,   242,   184,   323,   432,   469,     0,   388,   261,
       0,     0,   597,     0,   554,   288,   628,   629,   630,   627,
     633,   647,   649,   662,   665,     0,     0,     0,     0,   745,
      58,   499,   524,   591,   390,     0,   612,   601,     0,   755,
       0,   747,   611,     0,   757,   762,     0,   760,     0,     0,
     759,   771,     0,     0,     0,   776,     0,   764,   766,   767,
     768,   769,   770,   761,     0,     0,     0,     0,     0,     0,
     763,     0,   773,   774,   775,     0,   765,   772,   777
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,    -5,  -947,   242,
    -947,  -947,  -947,  -947,  -947,  -947,    63,  -947,  -507,  -947,
    -947,  -947,   -74,  -947,  -947,  -947,   617,  -947,  -947,  -947,
    -947,   348,   552,  -947,  -947,   -62,   -43,   -42,   -40,   -30,
     -29,   -27,   -26,     4,     5,     7,  -947,     8,     9,    10,
      11,  -947,   361,    21,  -947,    23,  -947,    24,  -947,    26,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,   347,   554,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,   271,  -947,
      62,  -947,  -652,    69,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,   -66,  -947,  -686,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,    44,  -947,  -947,  -947,
    -947,  -947,    52,  -675,  -947,  -947,  -947,  -947,    50,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,    38,  -947,  -947,
    -947,    42,   517,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
      34,  -947,  -947,  -947,  -947,  -947,  -947,  -946,  -947,  -947,
    -947,    71,  -947,  -947,  -947,    72,   562,  -947,  -947,  -944,
    -947,  -943,  -947,    30,  -947,    32,  -947,    36,  -947,  -947,
    -947,  -942,  -947,  -947,  -947,  -947,    59,  -947,  -947,  -147,
     960,  -947,  -947,  -947,  -947,  -947,    74,  -947,  -947,  -947,
      79,  -947,   541,  -947,   -76,  -947,  -947,  -947,  -947,  -947,
     -70,  -947,  -947,  -947,  -947,  -947,   -24,  -947,  -947,  -947,
      75,  -947,  -947,  -947,    78,  -947,   529,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,    35,  -947,
    -947,  -947,    25,   590,  -947,  -947,   -58,  -947,    -8,  -947,
    -947,  -947,  -947,  -947,    31,  -947,  -947,  -947,    28,   591,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,   -47,  -947,  -947,
    -947,    76,  -947,  -947,  -947,    80,  -947,   631,   340,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -939,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
      81,  -947,  -947,  -947,  -132,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,    58,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,    60,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,    53,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,   358,   542,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
    -947,   398,   531,  -947,  -947,  -947,  -947,  -947,  -947,  -947,
     406,   543,   -72,  -947,  -947,    55,  -947,  -947,  -130,  -947,
    -947,  -947,  -947,  -947,  -947,  -149,  -947,  -947,  -168,  -947,
    -947,  -947,  -947,  -947,  -947,  -947
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   693,    92,    93,    43,    72,    89,    90,   717,   918,
    1025,  1026,   785,    45,    74,   101,   102,   103,   410,    47,
      75,   157,   158,   159,   418,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   440,   686,   176,   441,   177,   442,   178,   463,   179,
     464,   180,   436,   181,   420,    49,    76,   210,   211,   212,
     468,   213,   182,   421,   183,   422,   184,   423,   815,   816,
     817,   963,   786,   787,   788,   936,  1171,   789,   937,   790,
     938,   791,   939,   792,   793,   505,   794,   795,   796,   797,
     798,   799,   800,   801,   956,   802,   957,   803,   958,   804,
     959,   805,   806,   807,   808,   945,   809,   810,   948,   811,
     949,   812,   950,   185,   453,   849,   850,   851,   983,   186,
     450,   836,   837,   838,   839,   187,   452,   844,   845,   846,
     847,   188,   451,   189,   456,   860,   861,   862,   992,    65,
      84,   357,   358,   359,   518,   360,   519,   190,   457,   869,
     870,   871,   872,   873,   874,   875,   876,   191,   443,   819,
     820,   821,   966,    51,    77,   246,   247,   248,   474,   249,
     475,   250,   476,   251,   480,   252,   479,   192,   448,   699,
     254,   255,   193,   449,   831,   832,   833,   975,  1097,  1098,
     194,   444,    59,    81,   823,   824,   825,   969,    61,    82,
     322,   323,   324,   325,   326,   327,   328,   504,   329,   508,
     330,   507,   331,   332,   509,   333,   195,   445,   827,   828,
     829,   972,    63,    83,   343,   344,   345,   346,   347,   513,
     348,   349,   350,   351,   257,   472,   920,   921,   922,  1027,
      53,    78,   268,   269,   270,   484,   196,   446,   197,   447,
     260,   473,   924,   925,   926,  1030,    55,    79,   284,   285,
     286,   487,   287,   288,   489,   289,   290,   198,   455,   856,
     857,   858,   989,    57,    80,   302,   303,   304,   305,   495,
     306,   496,   307,   497,   308,   498,   309,   499,   310,   500,
     311,   494,   262,   481,   929,   930,  1033,   199,   454,   853,
     854,   986,  1115,  1116,  1117,  1118,  1119,  1190,  1120,   200,
     458,   886,   887,   888,  1003,  1199,   889,   890,  1004,   891,
     892,   201,   202,   460,   898,   899,   900,  1010,   901,  1011,
     203,   461,   908,   909,   910,   911,  1015,   912,   913,  1017,
     204,   462,    67,    85,   379,   380,   381,   382,   523,   383,
     524,   384,   385,   526,   386,   387,   388,   529,   749,   389,
     530,   390,   391,   392,   533,   393,   534,   394,   535,   395,
     536,   104,   412,   105,   413,   106,   414,   205,   419,    71,
      87,   401,   402,   403,   541,   404,   107,   411,    69,    86,
     396,   397,   206,   465,   916,   917,  1021,  1154,  1155,  1156,
    1157,  1207,  1158,  1205,  1226,  1227,  1228,  1236,  1237,  1238,
    1244,  1239,  1240,  1241,  1242,  1248
  };

  const unsigned short
  Dhcp6Parser::yytable_[] =
  {
     100,   156,   209,   226,   264,   278,   298,   341,   320,   339,
     356,   376,    40,   342,   398,   227,   321,   340,   214,   258,
     271,   282,   300,   883,   334,   352,   813,   377,   843,  1090,
     261,  1091,  1092,  1096,   228,   229,  1102,   230,    33,    94,
      34,   834,    35,   207,   208,   292,   978,   231,   232,   979,
     233,   234,   927,   256,   267,   281,   299,   354,   355,   399,
     400,   314,   336,   315,   316,   337,   338,    32,   215,   259,
     272,   283,   301,   981,   335,   353,   982,   378,   136,   137,
     987,   235,   236,   988,   237,   238,   239,   240,   241,   313,
      44,   416,   681,   682,   683,   684,   417,   466,   242,    46,
     243,   244,   467,   245,   136,   137,   723,   135,   265,   279,
     266,   280,   470,   253,    48,   136,   137,   471,   729,   730,
     731,   354,   355,   405,   835,   136,   137,   108,   109,   685,
      50,   110,   482,    99,   111,   112,   113,   483,    52,   314,
      54,   315,   316,   291,    56,   317,   318,   319,    91,   292,
     293,   294,   295,   296,   297,    58,   136,   137,   485,   902,
     903,   904,   134,   486,    60,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,    99,   135,  1231,
      62,   492,  1232,  1233,  1234,  1235,   493,   520,    95,   263,
     136,   137,   521,   877,   136,   137,   136,   137,    96,    97,
      98,   138,   766,   905,   747,   748,   139,   140,   141,   142,
     143,    64,   144,    66,    99,   223,    99,   145,   224,    68,
      36,    37,    38,    39,    99,   537,   146,   539,    70,   147,
     538,  1090,   540,  1091,  1092,  1096,   148,   406,  1102,   135,
     314,   543,   893,   894,   149,   150,   544,  1022,   151,   135,
    1023,   466,   152,   407,   539,    99,   932,   136,   137,   933,
     136,   137,   273,   274,   275,   276,   277,   136,   137,  1229,
     314,   155,  1230,   153,   154,   408,   155,  1108,  1109,   863,
     864,   865,   866,   867,   868,   543,   223,   136,   137,   224,
     934,   409,   470,   960,   501,   960,   843,   935,   961,    99,
     962,  1061,   502,    99,   415,    99,   878,   879,   880,   881,
     424,   503,   883,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,   761,  1196,
    1197,  1198,   100,   762,   763,   764,   765,   766,   767,   768,
     769,   770,   771,   772,   773,   774,   775,   776,   777,   778,
     779,   780,   781,   782,   783,   784,   984,  1001,  1008,  1012,
    1018,   985,  1002,  1009,  1013,  1019,    99,   425,   426,    99,
    1147,   427,  1148,  1149,   537,   960,    99,   428,   314,  1020,
    1183,   429,   156,   482,  1187,   520,   209,   430,  1184,  1188,
    1195,   545,   546,   431,  1208,   485,    99,   432,   226,  1209,
    1211,   264,   214,   433,   492,   511,  1249,   512,   278,  1212,
     227,  1250,   834,   841,   258,   842,   434,   271,   298,   695,
     696,   697,   698,   435,   282,   261,   437,   438,   320,   228,
     229,   341,   230,   339,   300,   439,   321,   342,   459,   469,
     477,   340,   231,   232,   334,   233,   234,   478,   256,   352,
     488,   267,   215,   376,   490,   491,   506,   398,   281,  1167,
    1168,  1169,  1170,   510,   259,   514,   515,   272,   299,   377,
     517,   516,   522,   525,   283,   527,   235,   236,   528,   237,
     238,   239,   240,   241,   301,   531,   532,   542,   547,   548,
     549,   550,   551,   242,   335,   243,   244,   552,   245,   353,
     554,   555,   556,   557,    99,   265,   558,   266,   253,   559,
     560,   561,   279,   562,   280,   563,   564,   565,   566,   378,
     567,   568,   572,   569,   570,   571,   573,   576,   574,   575,
     577,   578,   579,   580,   581,   671,   672,   673,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   582,
     583,   127,   128,   129,   130,   131,   132,   584,   585,   135,
     586,   587,   588,   589,   590,   591,   592,   593,   594,   216,
     596,   217,   595,   597,   598,   599,   600,   136,   137,   218,
     219,   220,   221,   222,   138,   156,   604,   601,   398,   603,
     606,   607,   209,   608,   609,   610,   223,   613,   611,   224,
     145,   614,   612,   615,   617,   619,   620,   225,   214,   621,
     625,   622,   623,   626,   635,   627,   628,   629,   630,   631,
     633,   634,   636,   637,   638,   882,   895,   639,   376,   641,
     642,   743,   643,   645,   646,   649,   650,   651,   648,   652,
     653,   884,   896,   906,   377,   654,   655,   656,   657,   658,
     659,   660,   661,   756,   662,   665,   153,   154,   215,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     136,   137,   127,   128,   129,   130,   131,   132,   133,   668,
     135,   314,   666,   669,   670,   675,    99,   674,   676,   677,
     678,   885,   897,   907,   378,   679,   689,   680,   136,   137,
     687,   219,   220,   688,   222,   138,   690,   691,   694,   700,
      34,   701,   702,   703,   713,   705,   704,   223,   706,   707,
     224,   714,   708,   709,   710,   711,   712,   715,   225,   361,
     362,   363,   364,   365,   366,   367,   368,   369,   370,   371,
     372,   373,   716,   718,   719,   720,   721,   722,   724,   374,
     375,   725,   726,   755,   814,   840,   818,   822,   826,   830,
     750,   848,   727,   852,   728,   732,   855,   859,   915,   919,
     733,   734,   735,   736,   737,   738,   739,   153,   154,    99,
     923,   740,   940,   941,   942,   741,   943,   944,   946,   742,
     947,   744,   745,   746,   951,   952,   953,   954,   955,   752,
     753,   754,   964,   965,   967,   968,  1040,    99,   971,   970,
     973,   974,   976,   977,   692,   980,   991,   990,   993,   994,
    1024,   995,   996,   997,   998,   999,  1000,  1005,  1006,  1007,
    1014,  1016,  1029,  1041,  1028,  1032,  1031,  1036,  1042,  1034,
    1035,  1037,  1038,  1039,  1043,  1045,  1048,  1044,  1049,  1050,
    1046,  1047,  1051,  1052,  1056,  1057,  1054,  1053,  1058,  1055,
    1059,  1106,  1126,  1127,  1128,  1129,  1130,  1131,  1133,  1134,
    1135,  1136,  1137,  1139,  1140,  1143,  1145,  1166,  1144,  1142,
    1160,  1161,   226,  1172,  1173,   320,   341,  1185,   339,  1174,
    1175,  1069,   342,   321,   227,  1176,   340,  1177,   258,  1089,
    1186,   334,  1110,  1070,   352,   298,  1191,  1100,   356,   261,
    1111,  1192,  1193,   228,   229,  1194,   230,  1178,  1113,  1206,
    1179,   300,  1071,  1072,   882,  1073,   231,   232,   895,   233,
     234,  1180,   256,  1181,  1215,  1074,  1075,  1150,  1076,  1077,
     884,  1099,  1182,   264,   896,  1151,   278,  1218,   259,  1220,
     906,   335,  1112,  1152,   353,   299,  1223,  1101,  1216,   271,
     235,   236,   282,   237,   238,   239,   240,   241,  1114,  1078,
    1079,   301,  1080,  1081,  1082,  1083,  1084,   242,  1189,   243,
     244,  1225,   245,  1219,  1200,  1201,  1085,  1245,  1086,  1087,
     885,  1088,   253,   267,   897,  1093,   281,  1094,  1202,  1246,
     907,  1095,  1247,  1153,  1203,  1251,  1255,   757,   602,   272,
     751,  1210,   283,   760,   605,  1252,   931,  1062,  1107,  1060,
    1104,  1105,  1125,   553,  1124,  1132,  1103,   647,  1063,  1064,
    1214,   312,  1213,  1222,   616,  1066,   644,  1224,  1065,  1068,
    1067,  1253,  1162,   640,  1254,  1257,  1258,   265,  1164,   266,
     279,  1217,   280,  1165,  1163,   928,  1138,  1123,  1121,  1122,
     914,  1146,  1141,   759,   667,   618,   758,  1159,  1221,   663,
    1243,  1256,   664,   624,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1069,     0,     0,     0,     0,     0,  1110,
       0,  1089,     0,     0,     0,  1070,     0,  1111,     0,  1100,
       0,     0,     0,   632,  1150,  1113,     0,     0,     0,     0,
    1204,     0,  1151,     0,  1071,  1072,     0,  1073,     0,     0,
    1152,     0,     0,     0,     0,     0,     0,  1074,  1075,     0,
    1076,  1077,     0,  1099,     0,     0,     0,     0,     0,  1112,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1101,
       0,     0,     0,     0,     0,  1114,     0,     0,     0,     0,
       0,  1078,  1079,     0,  1080,  1081,  1082,  1083,  1084,     0,
    1153,     0,     0,     0,     0,     0,     0,     0,  1085,     0,
    1086,  1087,     0,  1088,     0,     0,     0,  1093,     0,  1094,
       0,     0,     0,  1095
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    83,    82,    83,
      84,    85,    17,    83,    86,    77,    82,    83,    76,    77,
      78,    79,    80,   709,    82,    83,   678,    85,   703,   975,
      77,   975,   975,   975,    77,    77,   975,    77,     5,    10,
       7,   114,     9,    16,    17,   112,     3,    77,    77,     6,
      77,    77,   119,    77,    78,    79,    80,   121,   122,    13,
      14,    71,    72,    73,    74,    75,    76,     0,    76,    77,
      78,    79,    80,     3,    82,    83,     6,    85,    88,    89,
       3,    77,    77,     6,    77,    77,    77,    77,    77,    21,
       7,     3,   163,   164,   165,   166,     8,     3,    77,     7,
      77,    77,     8,    77,    88,    89,   613,    70,    78,    79,
      78,    79,     3,    77,     7,    88,    89,     8,   625,   626,
     627,   121,   122,     6,   197,    88,    89,    11,    12,   200,
       7,    15,     3,   197,    18,    19,    20,     8,     7,    71,
       7,    73,    74,   106,     7,    77,    78,    79,   197,   112,
     113,   114,   115,   116,   117,     7,    88,    89,     3,   143,
     144,   145,    69,     8,     7,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,   197,    70,   172,
       7,     3,   175,   176,   177,   178,     8,     3,   169,    81,
      88,    89,     8,    21,    88,    89,    88,    89,   179,   180,
     181,    95,    30,   197,   160,   161,   100,   101,   102,   103,
     104,     7,   106,     7,   197,   107,   197,   111,   110,     7,
     197,   198,   199,   200,   197,     3,   120,     3,     7,   123,
       8,  1187,     8,  1187,  1187,  1187,   130,     3,  1187,    70,
      71,     3,   140,   141,   138,   139,     8,     3,   142,    70,
       6,     3,   146,     4,     3,   197,     8,    88,    89,     8,
      88,    89,    83,    84,    85,    86,    87,    88,    89,     3,
      71,   170,     6,   167,   168,     8,   170,   108,   109,   124,
     125,   126,   127,   128,   129,     3,   107,    88,    89,   110,
       8,     3,     3,     3,     8,     3,   981,     8,     8,   197,
       8,   963,     3,   197,     4,   197,   134,   135,   136,   137,
       4,     8,  1008,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,    21,   131,
     132,   133,   416,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,     3,     3,     3,     3,
       3,     8,     8,     8,     8,     8,   197,     4,     4,   197,
     171,     4,   173,   174,     3,     3,   197,     4,    71,     8,
       8,     4,   466,     3,     3,     3,   470,     4,     8,     8,
       8,   406,   407,     4,     3,     3,   197,     4,   482,     8,
       8,   485,   470,     4,     3,     8,     3,     3,   492,     8,
     482,     8,   114,   115,   482,   117,     4,   485,   502,    96,
      97,    98,    99,     4,   492,   482,     4,     4,   512,   482,
     482,   517,   482,   517,   502,     4,   512,   517,     4,     4,
       4,   517,   482,   482,   512,   482,   482,     4,   482,   517,
       4,   485,   470,   537,     4,     4,     4,   539,   492,    22,
      23,    24,    25,     4,   482,     4,     4,   485,   502,   537,
       3,     8,     4,     4,   492,     4,   482,   482,     4,   482,
     482,   482,   482,   482,   502,     4,     4,     4,   197,     4,
       4,     4,     4,   482,   512,   482,   482,     4,   482,   517,
       4,     4,     4,     4,   197,   485,     4,   485,   482,     4,
     198,   198,   492,   198,   492,   198,   198,   198,   198,   537,
     198,   200,     4,   199,   199,   198,   200,     4,   200,   200,
       4,     4,     4,     4,     4,   550,   551,   552,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,     4,
       4,    62,    63,    64,    65,    66,    67,     4,     4,    70,
       4,     4,     4,     4,     4,     4,     4,     4,     4,    80,
       4,    82,   198,     4,     4,     4,     4,    88,    89,    90,
      91,    92,    93,    94,    95,   669,   200,     4,   670,     4,
       4,     4,   676,     4,     4,     4,   107,     4,   198,   110,
     111,     4,   200,     4,     4,     4,   198,   118,   676,     4,
       4,   198,   198,     4,   198,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   709,   710,   200,   712,     4,
     200,   646,   200,     4,     4,     4,     4,   198,   200,     4,
     198,   709,   710,   711,   712,   198,     4,     4,   200,   200,
       4,     4,     4,   668,     4,     4,   167,   168,   676,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      88,    89,    62,    63,    64,    65,    66,    67,    68,     4,
      70,    71,   198,     7,     7,     7,   197,   197,     7,     7,
       7,   709,   710,   711,   712,     5,     5,   197,    88,    89,
     197,    91,    92,   197,    94,    95,     5,     5,   197,     5,
       7,     5,     5,     5,   197,     5,     7,   107,     5,     5,
     110,   197,     7,     7,     7,     7,     7,     5,   118,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,     5,     5,     5,   197,   197,   197,   197,   167,
     168,     7,   197,     5,     7,   702,     7,     7,     7,     7,
     162,   105,   197,     7,   197,   197,     7,     7,     7,     7,
     197,   197,   197,   197,   197,   197,   197,   167,   168,   197,
       7,   197,     4,     4,     4,   197,     4,     4,     4,   197,
       4,   197,   197,   197,     4,     4,     4,     4,     4,   197,
     197,   197,     6,     3,     6,     3,   198,   197,     3,     6,
       6,     3,     6,     3,   582,     6,     3,     6,     6,     3,
     197,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     3,   200,     6,     3,     6,     4,   198,     8,
       6,     4,     4,     4,   200,     4,     4,   198,     4,     4,
     198,   198,   198,   198,     4,     4,   198,   200,     4,   200,
       4,     4,   198,   198,   198,   198,   198,   198,     4,     4,
     198,   198,   198,     4,     4,     4,     4,     4,   198,   200,
       6,     3,   966,   197,   197,   969,   972,     8,   972,   197,
     197,   975,   972,   969,   966,   197,   972,   197,   966,   975,
       8,   969,   986,   975,   972,   989,     4,   975,   992,   966,
     986,     8,     3,   966,   966,     8,   966,   197,   986,     4,
     197,   989,   975,   975,  1008,   975,   966,   966,  1012,   966,
     966,   197,   966,   197,     4,   975,   975,  1021,   975,   975,
    1008,   975,   197,  1027,  1012,  1021,  1030,     4,   966,     4,
    1018,   969,   986,  1021,   972,   989,     5,   975,   200,  1027,
     966,   966,  1030,   966,   966,   966,   966,   966,   986,   975,
     975,   989,   975,   975,   975,   975,   975,   966,   197,   966,
     966,     7,   966,   198,   197,   197,   975,     4,   975,   975,
    1008,   975,   966,  1027,  1012,   975,  1030,   975,   197,     4,
    1018,   975,     4,  1021,   197,     4,     4,   669,   466,  1027,
     659,   197,  1030,   676,   470,   200,   755,   965,   984,   960,
     978,   981,   994,   416,   992,  1001,   977,   520,   966,   968,
    1187,    81,   197,   197,   482,   971,   517,   197,   969,   974,
     972,   198,  1027,   512,   198,   197,   197,  1027,  1030,  1027,
    1030,  1193,  1030,  1032,  1029,   725,  1008,   991,   987,   989,
     712,  1018,  1012,   675,   543,   485,   670,  1022,  1208,   537,
    1229,  1249,   539,   492,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1187,    -1,    -1,    -1,    -1,    -1,  1193,
      -1,  1187,    -1,    -1,    -1,  1187,    -1,  1193,    -1,  1187,
      -1,    -1,    -1,   502,  1208,  1193,    -1,    -1,    -1,    -1,
    1145,    -1,  1208,    -1,  1187,  1187,    -1,  1187,    -1,    -1,
    1208,    -1,    -1,    -1,    -1,    -1,    -1,  1187,  1187,    -1,
    1187,  1187,    -1,  1187,    -1,    -1,    -1,    -1,    -1,  1193,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1187,
      -1,    -1,    -1,    -1,    -1,  1193,    -1,    -1,    -1,    -1,
      -1,  1187,  1187,    -1,  1187,  1187,  1187,  1187,  1187,    -1,
    1208,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1187,    -1,
    1187,  1187,    -1,  1187,    -1,    -1,    -1,  1187,    -1,  1187,
      -1,    -1,    -1,  1187
  };

  const unsigned short
  Dhcp6Parser::yystos_[] =
  {
       0,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,     0,     5,     7,     9,   197,   198,   199,   200,
     218,   219,   220,   225,     7,   234,     7,   240,     7,   276,
       7,   384,     7,   461,     7,   477,     7,   494,     7,   413,
       7,   419,     7,   443,     7,   360,     7,   563,     7,   609,
       7,   600,   226,   221,   235,   241,   277,   385,   462,   478,
     495,   414,   420,   444,   361,   564,   610,   601,   218,   227,
     228,   197,   223,   224,    10,   169,   179,   180,   181,   197,
     233,   236,   237,   238,   592,   594,   596,   607,    11,    12,
      15,    18,    19,    20,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    88,    89,    95,   100,
     101,   102,   103,   104,   106,   111,   120,   123,   130,   138,
     139,   142,   146,   167,   168,   170,   233,   242,   243,   244,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   264,   266,   268,   270,
     272,   274,   283,   285,   287,   334,   340,   346,   352,   354,
     368,   378,   398,   403,   411,   437,   467,   469,   488,   518,
     530,   542,   543,   551,   561,   598,   613,    16,    17,   233,
     278,   279,   280,   282,   467,   469,    80,    82,    90,    91,
      92,    93,    94,   107,   110,   118,   233,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   258,   259,
     260,   261,   264,   266,   268,   270,   386,   387,   388,   390,
     392,   394,   396,   398,   401,   402,   437,   455,   467,   469,
     471,   488,   513,    81,   233,   394,   396,   437,   463,   464,
     465,   467,   469,    83,    84,    85,    86,    87,   233,   394,
     396,   437,   467,   469,   479,   480,   481,   483,   484,   486,
     487,   106,   112,   113,   114,   115,   116,   117,   233,   437,
     467,   469,   496,   497,   498,   499,   501,   503,   505,   507,
     509,   511,   411,    21,    71,    73,    74,    77,    78,    79,
     233,   305,   421,   422,   423,   424,   425,   426,   427,   429,
     431,   433,   434,   436,   467,   469,    72,    75,    76,   233,
     305,   425,   431,   445,   446,   447,   448,   449,   451,   452,
     453,   454,   467,   469,   121,   122,   233,   362,   363,   364,
     366,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   167,   168,   233,   467,   469,   565,
     566,   567,   568,   570,   572,   573,   575,   576,   577,   580,
     582,   583,   584,   586,   588,   590,   611,   612,   613,    13,
      14,   602,   603,   604,   606,     6,     3,     4,     8,     3,
     239,   608,   593,   595,   597,     4,     3,     8,   245,   599,
     275,   284,   286,   288,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   273,     4,     4,     4,
     262,   265,   267,   379,   412,   438,   468,   470,   399,   404,
     341,   353,   347,   335,   519,   489,   355,   369,   531,     4,
     544,   552,   562,   269,   271,   614,     3,     8,   281,     4,
       3,     8,   456,   472,   389,   391,   393,     4,     4,   397,
     395,   514,     3,     8,   466,     3,     8,   482,     4,   485,
       4,     4,     3,     8,   512,   500,   502,   504,   506,   508,
     510,     8,     3,     8,   428,   306,     4,   432,   430,   435,
       4,     8,     3,   450,     4,     4,     8,     3,   365,   367,
       3,     8,     4,   569,   571,     4,   574,     4,     4,   578,
     581,     4,     4,   585,   587,   589,   591,     3,     8,     3,
       8,   605,     4,     3,     8,   218,   218,   197,     4,     4,
       4,     4,     4,   237,     4,     4,     4,     4,     4,     4,
     198,   198,   198,   198,   198,   198,   198,   198,   200,   199,
     199,   198,     4,   200,   200,   200,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   198,     4,     4,     4,     4,
       4,     4,   243,     4,   200,   279,     4,     4,     4,     4,
       4,   198,   200,     4,     4,     4,   387,     4,   464,     4,
     198,     4,   198,   198,   480,     4,     4,     4,     4,     4,
       4,     4,   498,     4,     4,   198,     4,     4,     4,   200,
     423,     4,   200,   200,   447,     4,     4,   363,   200,     4,
       4,   198,     4,   198,   198,     4,     4,   200,   200,     4,
       4,     4,     4,   566,   612,     4,   198,   603,     4,     7,
       7,   218,   218,   218,   197,     7,     7,     7,     7,     5,
     197,   163,   164,   165,   166,   200,   263,   197,   197,     5,
       5,     5,   220,   222,   197,    96,    97,    98,    99,   400,
       5,     5,     5,     5,     7,     5,     5,     5,     7,     7,
       7,     7,     7,   197,   197,     5,     5,   229,     5,     5,
     197,   197,   197,   229,   197,     7,   197,   197,   197,   229,
     229,   229,   197,   197,   197,   197,   197,   197,   197,   197,
     197,   197,   197,   218,   197,   197,   197,   160,   161,   579,
     162,   263,   197,   197,   197,     5,   218,   242,   611,   602,
     278,    21,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,   233,   293,   294,   295,   298,
     300,   302,   304,   305,   307,   308,   309,   310,   311,   312,
     313,   314,   316,   318,   320,   322,   323,   324,   325,   327,
     328,   330,   332,   293,     7,   289,   290,   291,     7,   380,
     381,   382,     7,   415,   416,   417,     7,   439,   440,   441,
       7,   405,   406,   407,   114,   197,   342,   343,   344,   345,
     227,   115,   117,   344,   348,   349,   350,   351,   105,   336,
     337,   338,     7,   520,   521,     7,   490,   491,   492,     7,
     356,   357,   358,   124,   125,   126,   127,   128,   129,   370,
     371,   372,   373,   374,   375,   376,   377,    21,   134,   135,
     136,   137,   233,   307,   467,   469,   532,   533,   534,   537,
     538,   540,   541,   140,   141,   233,   467,   469,   545,   546,
     547,   549,   143,   144,   145,   197,   467,   469,   553,   554,
     555,   556,   558,   559,   565,     7,   615,   616,   230,     7,
     457,   458,   459,     7,   473,   474,   475,   119,   499,   515,
     516,   289,     8,     8,     8,     8,   296,   299,   301,   303,
       4,     4,     4,     4,     4,   326,     4,     4,   329,   331,
     333,     4,     4,     4,     4,     4,   315,   317,   319,   321,
       3,     8,     8,   292,     6,     3,   383,     6,     3,   418,
       6,     3,   442,     6,     3,   408,     6,     3,     3,     6,
       6,     3,     6,   339,     3,     8,   522,     3,     6,   493,
       6,     3,   359,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   535,   539,     4,     4,     4,     3,     8,
     548,   550,     3,     8,     4,   557,     4,   560,     3,     8,
       8,   617,     3,     6,   197,   231,   232,   460,     6,     3,
     476,     6,     3,   517,     8,     6,     4,     4,     4,     4,
     198,   200,   198,   200,   198,     4,   198,   198,     4,     4,
       4,   198,   198,   200,   198,   200,     4,     4,     4,     4,
     294,   293,   291,   386,   382,   421,   417,   445,   441,   233,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   258,   259,   260,   261,   264,   266,   268,   270,   305,
     378,   390,   392,   394,   396,   398,   402,   409,   410,   437,
     467,   469,   513,   407,   343,   349,     4,   337,   108,   109,
     233,   305,   437,   467,   469,   523,   524,   525,   526,   527,
     529,   521,   496,   492,   362,   358,   198,   198,   198,   198,
     198,   198,   371,     4,     4,   198,   198,   198,   533,     4,
       4,   546,   200,     4,   198,     4,   554,   171,   173,   174,
     233,   305,   467,   469,   618,   619,   620,   621,   623,   616,
       6,     3,   463,   459,   479,   475,     4,    22,    23,    24,
      25,   297,   197,   197,   197,   197,   197,   197,   197,   197,
     197,   197,   197,     8,     8,     8,     8,     3,     8,   197,
     528,     4,     8,     3,     8,     8,   131,   132,   133,   536,
     197,   197,   197,   197,   218,   624,     4,   622,     3,     8,
     197,     8,     8,   197,   410,     4,   200,   525,     4,   198,
       4,   619,   197,     5,   197,     7,   625,   626,   627,     3,
       6,   172,   175,   176,   177,   178,   628,   629,   630,   632,
     633,   634,   635,   626,   631,     4,     4,     4,   636,     3,
       8,     4,   200,   198,   198,     4,   629,   197,   197
  };

  const unsigned short
  Dhcp6Parser::yyr1_[] =
  {
       0,   201,   203,   202,   204,   202,   205,   202,   206,   202,
     207,   202,   208,   202,   209,   202,   210,   202,   211,   202,
     212,   202,   213,   202,   214,   202,   215,   202,   216,   202,
     217,   202,   218,   218,   218,   218,   218,   218,   218,   219,
     221,   220,   222,   223,   223,   224,   224,   226,   225,   227,
     227,   228,   228,   230,   229,   231,   231,   232,   232,   233,
     235,   234,   236,   236,   237,   237,   237,   237,   237,   237,
     239,   238,   241,   240,   242,   242,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   245,   244,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   262,   261,   263,   263,   263,   263,   263,   265,
     264,   267,   266,   269,   268,   271,   270,   273,   272,   275,
     274,   277,   276,   278,   278,   279,   279,   279,   279,   279,
     281,   280,   282,   284,   283,   286,   285,   288,   287,   289,
     289,   290,   290,   292,   291,   293,   293,   294,   294,   294,
     294,   294,   294,   294,   294,   294,   294,   294,   294,   294,
     294,   294,   294,   294,   294,   294,   294,   294,   294,   294,
     294,   294,   294,   296,   295,   297,   297,   297,   297,   299,
     298,   301,   300,   303,   302,   304,   306,   305,   307,   308,
     309,   310,   311,   312,   313,   315,   314,   317,   316,   319,
     318,   321,   320,   322,   323,   324,   326,   325,   327,   329,
     328,   331,   330,   333,   332,   335,   334,   336,   336,   337,
     339,   338,   341,   340,   342,   342,   343,   343,   344,   345,
     347,   346,   348,   348,   349,   349,   349,   350,   351,   353,
     352,   355,   354,   356,   356,   357,   357,   359,   358,   361,
     360,   362,   362,   362,   363,   363,   365,   364,   367,   366,
     369,   368,   370,   370,   371,   371,   371,   371,   371,   371,
     372,   373,   374,   375,   376,   377,   379,   378,   380,   380,
     381,   381,   383,   382,   385,   384,   386,   386,   387,   387,
     387,   387,   387,   387,   387,   387,   387,   387,   387,   387,
     387,   387,   387,   387,   387,   387,   387,   387,   387,   387,
     387,   387,   387,   387,   387,   387,   387,   387,   387,   387,
     387,   387,   387,   389,   388,   391,   390,   393,   392,   395,
     394,   397,   396,   399,   398,   400,   400,   400,   400,   401,
     402,   404,   403,   405,   405,   406,   406,   408,   407,   409,
     409,   410,   410,   410,   410,   410,   410,   410,   410,   410,
     410,   410,   410,   410,   410,   410,   410,   410,   410,   410,
     410,   410,   410,   410,   410,   410,   410,   410,   410,   410,
     410,   410,   410,   412,   411,   414,   413,   415,   415,   416,
     416,   418,   417,   420,   419,   421,   421,   422,   422,   423,
     423,   423,   423,   423,   423,   423,   423,   423,   423,   424,
     425,   426,   428,   427,   430,   429,   432,   431,   433,   435,
     434,   436,   438,   437,   439,   439,   440,   440,   442,   441,
     444,   443,   445,   445,   446,   446,   447,   447,   447,   447,
     447,   447,   447,   447,   447,   448,   450,   449,   451,   452,
     453,   454,   456,   455,   457,   457,   458,   458,   460,   459,
     462,   461,   463,   463,   464,   464,   464,   464,   464,   464,
     464,   466,   465,   468,   467,   470,   469,   472,   471,   473,
     473,   474,   474,   476,   475,   478,   477,   479,   479,   480,
     480,   480,   480,   480,   480,   480,   480,   480,   480,   480,
     482,   481,   483,   485,   484,   486,   487,   489,   488,   490,
     490,   491,   491,   493,   492,   495,   494,   496,   496,   497,
     497,   498,   498,   498,   498,   498,   498,   498,   498,   498,
     498,   498,   500,   499,   502,   501,   504,   503,   506,   505,
     508,   507,   510,   509,   512,   511,   514,   513,   515,   515,
     517,   516,   519,   518,   520,   520,   522,   521,   523,   523,
     524,   524,   525,   525,   525,   525,   525,   525,   525,   526,
     528,   527,   529,   531,   530,   532,   532,   533,   533,   533,
     533,   533,   533,   533,   533,   533,   535,   534,   536,   536,
     536,   537,   539,   538,   540,   541,   542,   544,   543,   545,
     545,   546,   546,   546,   546,   546,   548,   547,   550,   549,
     552,   551,   553,   553,   554,   554,   554,   554,   554,   554,
     555,   557,   556,   558,   560,   559,   562,   561,   564,   563,
     565,   565,   566,   566,   566,   566,   566,   566,   566,   566,
     566,   566,   566,   566,   566,   566,   566,   566,   566,   566,
     567,   569,   568,   571,   570,   572,   574,   573,   575,   576,
     578,   577,   579,   579,   581,   580,   582,   583,   585,   584,
     587,   586,   589,   588,   591,   590,   593,   592,   595,   594,
     597,   596,   599,   598,   601,   600,   602,   602,   603,   603,
     605,   604,   606,   608,   607,   610,   609,   611,   611,   612,
     614,   613,   615,   615,   617,   616,   618,   618,   619,   619,
     619,   619,   619,   619,   619,   620,   622,   621,   624,   623,
     625,   625,   627,   626,   628,   628,   629,   629,   629,   629,
     629,   631,   630,   632,   633,   634,   636,   635
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     0,     4,     0,
       4,     0,     4,     3,     3,     3,     0,     4,     3,     0,
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     1,     1,     1,     1,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     6,     0,     4,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     0,     4,     0,     4,     0,     4,     1,     0,
       4,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     4,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     1,     1,
       0,     4,     0,     6,     1,     3,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     3,     0,     4,     3,     3,     3,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     3,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     3,     3,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     4,     1,     3,     1,     1,
       0,     6,     3,     0,     6,     0,     4,     1,     3,     1,
       0,     6,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     0,     6,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     0,     4,     3,     3,     3,     0,     4
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
  "\"tcp-nodelay\"", "\"max-row-errors\"", "\"ssl\"", "\"ssl-ca\"",
  "\"ssl-cert\"", "\"ssl-key\"", "\"ssl-password\"",
  "\"preferred-lifetime\"", "\"min-preferred-lifetime\"",
  "\"max-preferred-lifetime\"", "\"valid-lifetime\"",
  "\"min-valid-lifetime\"", "\"max-valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"calculate-tee-times\"", "\"t1-percent\"",
  "\"t2-percent\"", "\"decline-probation-period\"", "\"server-tag\"",
  "\"ddns-send-updates\"", "\"ddns-override-no-update\"",
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
  "\"socket-name\"", "\"dhcp-queue-control\"", "\"enable-queue\"",
  "\"queue-type\"", "\"capacity\"", "\"dhcp-ddns\"", "\"enable-updates\"",
  "\"qualifying-suffix\"", "\"server-ip\"", "\"server-port\"",
  "\"sender-ip\"", "\"sender-port\"", "\"max-queue-size\"",
  "\"ncr-protocol\"", "\"ncr-format\"", "\"override-no-update\"",
  "\"override-client-update\"", "\"replace-client-name\"",
  "\"generated-prefix\"", "\"UDP\"", "\"TCP\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"hostname-char-set\"", "\"hostname-char-replacement\"", "\"Logging\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"",
  "\"Dhcp4\"", "\"DhcpDdns\"", "\"Control-agent\"", "TOPLEVEL_JSON",
  "TOPLEVEL_DHCP6", "SUB_DHCP6", "SUB_INTERFACES6", "SUB_SUBNET6",
  "SUB_POOL6", "SUB_PD_POOL", "SUB_RESERVATION", "SUB_OPTION_DEFS",
  "SUB_OPTION_DEF", "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY",
  "SUB_DHCP_DDNS", "SUB_LOGGING", "SUB_CONFIG_CONTROL",
  "\"constant string\"", "\"integer\"", "\"floating point\"",
  "\"boolean\"", "$accept", "start", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "$@13", "$@14",
  "$@15", "value", "sub_json", "map2", "$@16", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@17", "list_content",
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
  "max_row_errors", "ssl", "ssl_ca", "$@41", "ssl_cert", "$@42", "ssl_key",
  "$@43", "ssl_password", "$@44", "request_timeout", "tcp_keepalive",
  "tcp_nodelay", "contact_points", "$@45", "max_reconnect_tries",
  "keyspace", "$@46", "consistency", "$@47", "serial_consistency", "$@48",
  "sanity_checks", "$@49", "sanity_checks_params", "sanity_checks_param",
  "lease_checks", "$@50", "mac_sources", "$@51", "mac_sources_list",
  "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@52",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@53",
  "hooks_libraries", "$@54", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@55",
  "sub_hooks_library", "$@56", "hooks_params", "hooks_param", "library",
  "$@57", "parameters", "$@58", "expired_leases_processing", "$@59",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@60",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@61",
  "sub_subnet6", "$@62", "subnet6_params", "subnet6_param", "subnet",
  "$@63", "interface", "$@64", "interface_id", "$@65", "client_class",
  "$@66", "require_client_classes", "$@67", "reservation_mode", "$@68",
  "hr_mode", "id", "rapid_commit", "shared_networks", "$@69",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@70", "shared_network_params", "shared_network_param",
  "option_def_list", "$@71", "sub_option_def_list", "$@72",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@73", "sub_option_def", "$@74",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@75",
  "option_def_record_types", "$@76", "space", "$@77", "option_def_space",
  "option_def_encapsulate", "$@78", "option_def_array", "option_data_list",
  "$@79", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@80", "sub_option_data", "$@81",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@82",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@83", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@84", "sub_pool6", "$@85",
  "pool_params", "pool_param", "pool_entry", "$@86", "user_context",
  "$@87", "comment", "$@88", "pd_pools_list", "$@89",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@90", "sub_pd_pool", "$@91", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@92", "pd_prefix_len", "excluded_prefix", "$@93",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@94",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@95", "sub_reservation", "$@96", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@97", "prefixes", "$@98", "duid", "$@99", "hw_address", "$@100",
  "hostname", "$@101", "flex_id_value", "$@102",
  "reservation_client_classes", "$@103", "relay", "$@104", "relay_map",
  "ip_address", "$@105", "client_classes", "$@106", "client_classes_list",
  "client_class_entry", "$@107", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@108", "only_if_required",
  "server_id", "$@109", "server_id_params", "server_id_param",
  "server_id_type", "$@110", "duid_type", "htype", "identifier", "$@111",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@112",
  "control_socket_params", "control_socket_param", "socket_type", "$@113",
  "socket_name", "$@114", "dhcp_queue_control", "$@115",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@116", "capacity", "arbitrary_map_entry", "$@117",
  "dhcp_ddns", "$@118", "sub_dhcp_ddns", "$@119", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "qualifying_suffix", "$@120",
  "server_ip", "$@121", "server_port", "sender_ip", "$@122", "sender_port",
  "max_queue_size", "ncr_protocol", "$@123", "ncr_protocol_value",
  "ncr_format", "$@124", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@125",
  "dep_generated_prefix", "$@126", "dep_hostname_char_set", "$@127",
  "dep_hostname_char_replacement", "$@128", "dhcp4_json_object", "$@129",
  "dhcpddns_json_object", "$@130", "control_agent_json_object", "$@131",
  "config_control", "$@132", "sub_config_control", "$@133",
  "config_control_params", "config_control_param", "config_databases",
  "$@134", "config_fetch_wait_time", "logging_object", "$@135",
  "sub_logging", "$@136", "logging_params", "logging_param", "loggers",
  "$@137", "loggers_entries", "logger_entry", "$@138", "logger_params",
  "logger_param", "debuglevel", "severity", "$@139", "output_options_list",
  "$@140", "output_options_list_content", "output_entry", "$@141",
  "output_params_list", "output_params", "output", "$@142", "flush",
  "maxsize", "maxver", "pattern", "$@143", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short
  Dhcp6Parser::yyrline_[] =
  {
       0,   285,   285,   285,   286,   286,   287,   287,   288,   288,
     289,   289,   290,   290,   291,   291,   292,   292,   293,   293,
     294,   294,   295,   295,   296,   296,   297,   297,   298,   298,
     299,   299,   307,   308,   309,   310,   311,   312,   313,   316,
     321,   321,   332,   335,   336,   339,   343,   350,   350,   357,
     358,   361,   365,   372,   372,   379,   380,   383,   387,   398,
     408,   408,   423,   424,   428,   429,   430,   431,   432,   433,
     436,   436,   451,   451,   460,   461,   466,   467,   468,   469,
     470,   471,   472,   473,   474,   475,   476,   477,   478,   479,
     480,   481,   482,   483,   484,   485,   486,   487,   488,   489,
     490,   491,   492,   493,   494,   495,   496,   497,   498,   499,
     500,   501,   502,   503,   504,   505,   506,   507,   508,   509,
     510,   511,   512,   513,   514,   517,   517,   525,   530,   535,
     540,   545,   550,   555,   560,   565,   570,   575,   580,   585,
     590,   595,   600,   600,   608,   611,   614,   617,   620,   626,
     626,   634,   634,   642,   642,   650,   650,   658,   658,   666,
     666,   677,   677,   686,   687,   690,   691,   692,   693,   694,
     697,   697,   707,   713,   713,   725,   725,   737,   737,   747,
     748,   751,   752,   755,   755,   765,   766,   769,   770,   771,
     772,   773,   774,   775,   776,   777,   778,   779,   780,   781,
     782,   783,   784,   785,   786,   787,   788,   789,   790,   791,
     792,   793,   794,   797,   797,   804,   805,   806,   807,   810,
     810,   818,   818,   826,   826,   834,   839,   839,   847,   852,
     857,   862,   867,   872,   877,   882,   882,   890,   890,   898,
     898,   906,   906,   914,   919,   924,   929,   929,   937,   942,
     942,   950,   950,   958,   958,   966,   966,   976,   977,   979,
     981,   981,   999,   999,  1009,  1010,  1013,  1014,  1017,  1022,
    1027,  1027,  1037,  1038,  1041,  1042,  1043,  1046,  1051,  1058,
    1058,  1068,  1068,  1078,  1079,  1082,  1083,  1086,  1086,  1096,
    1096,  1106,  1107,  1108,  1111,  1112,  1115,  1115,  1123,  1123,
    1131,  1131,  1142,  1143,  1146,  1147,  1148,  1149,  1150,  1151,
    1154,  1159,  1164,  1169,  1174,  1179,  1187,  1187,  1200,  1201,
    1204,  1205,  1212,  1212,  1238,  1238,  1249,  1250,  1254,  1255,
    1256,  1257,  1258,  1259,  1260,  1261,  1262,  1263,  1264,  1265,
    1266,  1267,  1268,  1269,  1270,  1271,  1272,  1273,  1274,  1275,
    1276,  1277,  1278,  1279,  1280,  1281,  1282,  1283,  1284,  1285,
    1286,  1287,  1288,  1291,  1291,  1299,  1299,  1307,  1307,  1315,
    1315,  1323,  1323,  1333,  1333,  1340,  1341,  1342,  1343,  1346,
    1351,  1359,  1359,  1370,  1371,  1375,  1376,  1379,  1379,  1387,
    1388,  1391,  1392,  1393,  1394,  1395,  1396,  1397,  1398,  1399,
    1400,  1401,  1402,  1403,  1404,  1405,  1406,  1407,  1408,  1409,
    1410,  1411,  1412,  1413,  1414,  1415,  1416,  1417,  1418,  1419,
    1420,  1421,  1422,  1429,  1429,  1442,  1442,  1451,  1452,  1455,
    1456,  1461,  1461,  1476,  1476,  1490,  1491,  1494,  1495,  1498,
    1499,  1500,  1501,  1502,  1503,  1504,  1505,  1506,  1507,  1510,
    1512,  1517,  1519,  1519,  1527,  1527,  1535,  1535,  1543,  1545,
    1545,  1553,  1562,  1562,  1574,  1575,  1580,  1581,  1586,  1586,
    1598,  1598,  1610,  1611,  1616,  1617,  1622,  1623,  1624,  1625,
    1626,  1627,  1628,  1629,  1630,  1633,  1635,  1635,  1643,  1645,
    1647,  1652,  1660,  1660,  1672,  1673,  1676,  1677,  1680,  1680,
    1690,  1690,  1699,  1700,  1703,  1704,  1705,  1706,  1707,  1708,
    1709,  1712,  1712,  1720,  1720,  1745,  1745,  1775,  1775,  1787,
    1788,  1791,  1792,  1795,  1795,  1807,  1807,  1819,  1820,  1823,
    1824,  1825,  1826,  1827,  1828,  1829,  1830,  1831,  1832,  1833,
    1836,  1836,  1844,  1849,  1849,  1857,  1862,  1870,  1870,  1880,
    1881,  1884,  1885,  1888,  1888,  1897,  1897,  1906,  1907,  1910,
    1911,  1915,  1916,  1917,  1918,  1919,  1920,  1921,  1922,  1923,
    1924,  1925,  1928,  1928,  1938,  1938,  1948,  1948,  1956,  1956,
    1964,  1964,  1972,  1972,  1980,  1980,  1993,  1993,  2003,  2004,
    2007,  2007,  2018,  2018,  2028,  2029,  2032,  2032,  2042,  2043,
    2046,  2047,  2050,  2051,  2052,  2053,  2054,  2055,  2056,  2059,
    2061,  2061,  2069,  2077,  2077,  2089,  2090,  2093,  2094,  2095,
    2096,  2097,  2098,  2099,  2100,  2101,  2104,  2104,  2111,  2112,
    2113,  2116,  2121,  2121,  2129,  2134,  2141,  2148,  2148,  2158,
    2159,  2162,  2163,  2164,  2165,  2166,  2169,  2169,  2177,  2177,
    2187,  2187,  2199,  2200,  2203,  2204,  2205,  2206,  2207,  2208,
    2211,  2216,  2216,  2224,  2229,  2229,  2238,  2238,  2250,  2250,
    2260,  2261,  2264,  2265,  2266,  2267,  2268,  2269,  2270,  2271,
    2272,  2273,  2274,  2275,  2276,  2277,  2278,  2279,  2280,  2281,
    2284,  2289,  2289,  2297,  2297,  2305,  2310,  2310,  2318,  2323,
    2328,  2328,  2336,  2337,  2340,  2340,  2349,  2355,  2361,  2361,
    2369,  2369,  2378,  2378,  2387,  2387,  2397,  2397,  2404,  2404,
    2411,  2411,  2420,  2420,  2431,  2431,  2441,  2442,  2446,  2447,
    2450,  2450,  2460,  2470,  2470,  2480,  2480,  2491,  2492,  2496,
    2500,  2500,  2512,  2513,  2517,  2517,  2525,  2526,  2529,  2530,
    2531,  2532,  2533,  2534,  2535,  2538,  2543,  2543,  2551,  2551,
    2561,  2562,  2565,  2565,  2573,  2574,  2577,  2578,  2579,  2580,
    2581,  2584,  2584,  2592,  2597,  2602,  2607,  2607
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
#line 5605 "dhcp6_parser.cc" // lalr1.cc:1242
#line 2615 "dhcp6_parser.yy" // lalr1.cc:1243


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
