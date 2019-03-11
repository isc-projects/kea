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

#if YY_CPLUSPLUS < 201103L
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
      case 170: // "constant string"
#line 248 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < std::string > (); }
#line 404 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 171: // "integer"
#line 248 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 410 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 172: // "floating point"
#line 248 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < double > (); }
#line 416 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 173: // "boolean"
#line 248 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < bool > (); }
#line 422 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 191: // value
#line 248 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 195: // map_value
#line 248 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 434 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 247: // db_type
#line 248 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 440 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 336: // hr_mode
#line 248 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 446 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 472: // duid_type
#line 248 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 452 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 507: // ncr_protocol_value
#line 248 "dhcp6_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 458 "dhcp6_parser.cc" // lalr1.cc:676
        break;

      case 514: // replace_client_name_value
#line 248 "dhcp6_parser.yy" // lalr1.cc:676
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
#line 257 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 730 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 4:
#line 258 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.CONFIG; }
#line 736 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 6:
#line 259 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP6; }
#line 742 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 8:
#line 260 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 748 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 10:
#line 261 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.SUBNET6; }
#line 754 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 12:
#line 262 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.POOLS; }
#line 760 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 14:
#line 263 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 766 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 16:
#line 264 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 772 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 18:
#line 265 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP6; }
#line 778 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 20:
#line 266 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 784 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 22:
#line 267 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 790 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 24:
#line 268 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 796 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 26:
#line 269 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 802 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 28:
#line 270 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.LOGGING; }
#line 808 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 30:
#line 271 "dhcp6_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 814 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 32:
#line 279 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 820 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 33:
#line 280 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 826 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 34:
#line 281 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 832 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 35:
#line 282 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 838 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 36:
#line 283 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 844 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 37:
#line 284 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 850 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 38:
#line 285 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 856 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 39:
#line 288 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 865 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 40:
#line 293 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 876 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 41:
#line 298 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 886 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 42:
#line 304 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 892 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 45:
#line 311 "dhcp6_parser.yy" // lalr1.cc:919
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 901 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 46:
#line 315 "dhcp6_parser.yy" // lalr1.cc:919
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 911 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 47:
#line 322 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 920 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 48:
#line 325 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // list parsing complete. Put any sanity checking here
}
#line 928 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 51:
#line 333 "dhcp6_parser.yy" // lalr1.cc:919
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 937 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 52:
#line 337 "dhcp6_parser.yy" // lalr1.cc:919
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 946 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 53:
#line 344 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // List parsing about to start
}
#line 954 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 54:
#line 346 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 963 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 57:
#line 355 "dhcp6_parser.yy" // lalr1.cc:919
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 972 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 58:
#line 359 "dhcp6_parser.yy" // lalr1.cc:919
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 981 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 59:
#line 370 "dhcp6_parser.yy" // lalr1.cc:919
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 992 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 60:
#line 380 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1003 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 61:
#line 385 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 408 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 415 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1039 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 72:
#line 423 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1049 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 73:
#line 427 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No global parameter is required
    // parsing completed
}
#line 1058 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 108:
#line 472 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1067 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 109:
#line 477 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1076 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 110:
#line 482 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1085 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 111:
#line 487 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1094 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 112:
#line 492 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1103 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 113:
#line 497 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1111 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 114:
#line 499 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1121 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 115:
#line 505 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1132 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 116:
#line 510 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1142 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 117:
#line 516 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1152 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 118:
#line 520 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1161 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 126:
#line 536 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1172 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 127:
#line 541 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1181 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 128:
#line 546 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1190 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 129:
#line 552 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1201 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 130:
#line 557 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1212 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 131:
#line 564 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1223 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 132:
#line 569 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1234 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 133:
#line 576 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1245 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 134:
#line 581 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1254 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 139:
#line 594 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1264 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 140:
#line 598 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1274 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 161:
#line 628 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1282 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 162:
#line 630 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1291 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 163:
#line 635 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1297 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 164:
#line 636 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1303 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 165:
#line 637 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1309 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 166:
#line 638 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1315 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 167:
#line 641 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1323 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 168:
#line 643 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1333 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 169:
#line 649 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1341 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 170:
#line 651 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1351 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 171:
#line 657 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1359 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 172:
#line 659 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1369 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 173:
#line 665 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1378 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 174:
#line 670 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1386 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 175:
#line 672 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1396 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 176:
#line 678 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1405 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 177:
#line 683 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1414 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 178:
#line 688 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1423 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 179:
#line 693 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1432 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 180:
#line 698 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1441 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 181:
#line 703 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1450 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 182:
#line 708 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1459 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 183:
#line 713 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1468 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 184:
#line 718 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1476 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 185:
#line 720 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1486 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 186:
#line 726 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1495 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 187:
#line 731 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1503 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 188:
#line 733 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1513 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 189:
#line 739 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1524 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 190:
#line 744 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1533 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 194:
#line 754 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1541 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 195:
#line 756 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 1561 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 196:
#line 772 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1572 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 197:
#line 777 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1581 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 202:
#line 790 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1590 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 203:
#line 795 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1599 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 204:
#line 800 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1610 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 205:
#line 805 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1619 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 211:
#line 819 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1628 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 212:
#line 824 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1637 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 213:
#line 831 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1648 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 214:
#line 836 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1657 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 215:
#line 841 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1668 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 216:
#line 846 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1677 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 221:
#line 859 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1687 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 222:
#line 863 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1697 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 223:
#line 869 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1707 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 224:
#line 873 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1717 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 230:
#line 888 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1725 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 231:
#line 890 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1735 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 232:
#line 896 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1743 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 233:
#line 898 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1752 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 234:
#line 904 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1763 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 235:
#line 909 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1773 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 244:
#line 927 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1782 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 245:
#line 932 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1791 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 246:
#line 937 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1800 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 247:
#line 942 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1809 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 248:
#line 947 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1818 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 249:
#line 952 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1827 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 250:
#line 960 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1838 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 251:
#line 965 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1847 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 256:
#line 985 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1857 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 257:
#line 989 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 1883 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 258:
#line 1011 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1893 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 259:
#line 1015 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1903 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 282:
#line 1049 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1911 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 283:
#line 1051 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 1921 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 284:
#line 1057 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1929 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 285:
#line 1059 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 1939 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 286:
#line 1065 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1947 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 287:
#line 1067 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 1957 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 288:
#line 1073 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1965 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 289:
#line 1075 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 1975 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 290:
#line 1081 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1986 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 291:
#line 1086 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1995 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 292:
#line 1091 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2003 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 293:
#line 1093 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2012 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 294:
#line 1098 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2018 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 295:
#line 1099 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2024 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 296:
#line 1100 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2030 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 297:
#line 1101 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2036 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 298:
#line 1104 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2045 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 299:
#line 1109 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2054 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 300:
#line 1117 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2065 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 301:
#line 1122 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2074 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 306:
#line 1137 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2084 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 307:
#line 1141 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 2092 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 327:
#line 1172 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2103 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 328:
#line 1177 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2112 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 329:
#line 1185 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2121 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 330:
#line 1188 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 2129 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 335:
#line 1204 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2139 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 336:
#line 1208 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2151 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 337:
#line 1219 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2161 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 338:
#line 1223 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2173 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 354:
#line 1255 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2182 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 356:
#line 1262 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2190 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 357:
#line 1264 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2200 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 358:
#line 1270 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2208 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 359:
#line 1272 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2218 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 360:
#line 1278 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2226 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 361:
#line 1280 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
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
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2254 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 365:
#line 1296 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2263 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 366:
#line 1305 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2274 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 367:
#line 1310 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2283 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 372:
#line 1329 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2293 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 373:
#line 1333 "dhcp6_parser.yy" // lalr1.cc:919
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2302 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 374:
#line 1341 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2312 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 375:
#line 1345 "dhcp6_parser.yy" // lalr1.cc:919
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2321 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 390:
#line 1378 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2329 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 391:
#line 1380 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2339 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 394:
#line 1390 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2348 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 395:
#line 1395 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2357 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 396:
#line 1403 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2368 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 397:
#line 1408 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2377 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 402:
#line 1423 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2387 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 403:
#line 1427 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2397 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 404:
#line 1433 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2407 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 405:
#line 1437 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2416 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 415:
#line 1455 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2424 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 416:
#line 1457 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2434 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 417:
#line 1463 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2442 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 418:
#line 1465 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 2469 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 419:
#line 1488 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2477 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 420:
#line 1490 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 2506 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 421:
#line 1518 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2517 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 422:
#line 1523 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2526 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 427:
#line 1538 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2536 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 428:
#line 1542 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2548 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 429:
#line 1550 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2558 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 430:
#line 1554 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2570 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 444:
#line 1579 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2578 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 445:
#line 1581 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2588 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 446:
#line 1587 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2597 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 447:
#line 1592 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2605 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 448:
#line 1594 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2615 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 449:
#line 1600 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2624 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 450:
#line 1605 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2633 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 451:
#line 1613 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2644 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 452:
#line 1618 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2653 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 457:
#line 1631 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2663 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 458:
#line 1635 "dhcp6_parser.yy" // lalr1.cc:919
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2672 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 459:
#line 1640 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2682 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 460:
#line 1644 "dhcp6_parser.yy" // lalr1.cc:919
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2691 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 476:
#line 1671 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2702 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 477:
#line 1676 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2711 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 478:
#line 1681 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2722 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 479:
#line 1686 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2731 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 480:
#line 1691 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2739 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 481:
#line 1693 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2749 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 482:
#line 1699 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2757 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 483:
#line 1701 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2767 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 484:
#line 1707 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2775 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 485:
#line 1709 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2785 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 486:
#line 1715 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2793 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 487:
#line 1717 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2803 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 488:
#line 1723 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2814 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 489:
#line 1728 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2823 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 490:
#line 1736 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2834 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 491:
#line 1741 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2843 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 494:
#line 1750 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2851 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 495:
#line 1752 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2861 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 496:
#line 1761 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2872 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 497:
#line 1766 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2881 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 500:
#line 1775 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2891 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 501:
#line 1779 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2901 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 514:
#line 1804 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2909 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 515:
#line 1806 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 2919 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 516:
#line 1812 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 2928 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 517:
#line 1820 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 2939 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 518:
#line 1825 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2950 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 530:
#line 1847 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 2958 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 531:
#line 1849 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2967 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 532:
#line 1854 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 2973 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 533:
#line 1855 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 2979 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 534:
#line 1856 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 2985 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 535:
#line 1859 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 2994 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 536:
#line 1864 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3002 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 537:
#line 1866 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3012 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 538:
#line 1872 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3021 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 539:
#line 1877 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3030 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 540:
#line 1884 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3039 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 541:
#line 1891 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3050 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 542:
#line 1896 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3059 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 550:
#line 1912 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3067 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 551:
#line 1914 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3077 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 552:
#line 1920 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3085 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 553:
#line 1922 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3095 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 554:
#line 1930 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3103 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 555:
#line 1932 "dhcp6_parser.yy" // lalr1.cc:919
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
#line 3143 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 556:
#line 1970 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3154 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 557:
#line 1975 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3165 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 558:
#line 1982 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3175 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 559:
#line 1986 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3185 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 580:
#line 2016 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3194 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 581:
#line 2021 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3202 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 582:
#line 2023 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3212 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 583:
#line 2029 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3220 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 584:
#line 2031 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3230 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 585:
#line 2037 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3239 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 586:
#line 2042 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3247 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 587:
#line 2044 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3257 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 588:
#line 2050 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3266 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 589:
#line 2055 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3275 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 590:
#line 2060 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3283 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 591:
#line 2062 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3292 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 592:
#line 2068 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3298 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 593:
#line 2069 "dhcp6_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3304 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 594:
#line 2072 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3312 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 595:
#line 2074 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3322 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 596:
#line 2080 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3331 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 597:
#line 2085 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3340 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 598:
#line 2090 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3348 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 599:
#line 2092 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3357 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 600:
#line 2098 "dhcp6_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3365 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 601:
#line 2101 "dhcp6_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3373 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 602:
#line 2104 "dhcp6_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3381 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 603:
#line 2107 "dhcp6_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3389 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 604:
#line 2110 "dhcp6_parser.yy" // lalr1.cc:919
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3398 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 605:
#line 2116 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3406 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 606:
#line 2118 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3416 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 607:
#line 2124 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3424 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 608:
#line 2126 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3434 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 609:
#line 2132 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3442 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 610:
#line 2134 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3452 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 611:
#line 2142 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3460 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 612:
#line 2144 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3469 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 613:
#line 2149 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3477 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 614:
#line 2151 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3486 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 615:
#line 2156 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3494 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 616:
#line 2158 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3503 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 617:
#line 2165 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3514 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 618:
#line 2170 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3524 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 619:
#line 2176 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3534 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 620:
#line 2180 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // No config_control params are required
    // parsing completed
}
#line 3543 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 624:
#line 2194 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3554 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 625:
#line 2199 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3563 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 626:
#line 2209 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3574 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 627:
#line 2214 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3583 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 628:
#line 2219 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3593 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 629:
#line 2223 "dhcp6_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 3601 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 633:
#line 2239 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3612 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 634:
#line 2244 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3621 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 637:
#line 2256 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3631 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 638:
#line 2260 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 3639 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 648:
#line 2277 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3648 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 649:
#line 2282 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3656 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 650:
#line 2284 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3666 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 651:
#line 2290 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3677 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 652:
#line 2295 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3686 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 655:
#line 2304 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3696 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 656:
#line 2308 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 3704 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 663:
#line 2322 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3712 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 664:
#line 2324 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3722 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 665:
#line 2330 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3731 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 666:
#line 2335 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3740 "dhcp6_parser.cc" // lalr1.cc:919
    break;

  case 667:
#line 2340 "dhcp6_parser.yy" // lalr1.cc:919
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3749 "dhcp6_parser.cc" // lalr1.cc:919
    break;


#line 3753 "dhcp6_parser.cc" // lalr1.cc:919
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


  const short Dhcp6Parser::yypact_ninf_ = -821;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     337,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,    65,    55,    66,    90,
     108,   110,   119,   125,   136,   169,   176,   177,   217,   245,
     246,   247,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,    55,  -119,    28,    59,    25,   218,    64,   233,
     350,    47,    30,   170,   -54,   456,   -73,   165,  -821,   258,
     194,   262,   293,   267,  -821,  -821,  -821,  -821,  -821,   320,
    -821,    71,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,   324,   346,   352,   354,   355,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,   360,  -821,  -821,  -821,  -821,
      79,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,   361,  -821,    80,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,   362,   364,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,    86,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,   104,
    -821,  -821,  -821,  -821,  -821,   380,  -821,   381,   386,  -821,
    -821,  -821,  -821,  -821,  -821,   105,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,   340,   351,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,   370,  -821,  -821,   391,  -821,  -821,  -821,
     394,  -821,  -821,   392,   396,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,   398,   401,
    -821,  -821,  -821,  -821,   400,   403,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,   111,  -821,
    -821,  -821,   405,  -821,  -821,   406,  -821,   409,   418,  -821,
    -821,   419,   421,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
     120,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,   154,  -821,
    -821,  -821,   155,  -821,  -821,  -821,    55,    55,  -821,   257,
     424,   430,   432,   441,   447,  -821,    28,  -821,   448,   449,
     450,   453,   459,   289,   294,   295,   296,   298,   460,   464,
     466,   467,   468,   469,   471,   472,   474,   475,   476,   477,
     478,   479,   480,   482,   483,   317,   503,   504,   505,    59,
    -821,   506,   339,    25,  -821,   509,   510,   511,   512,   514,
     348,   353,   519,   520,   521,   218,  -821,   523,    64,  -821,
     524,   358,   526,   363,   365,   233,  -821,   527,   528,   531,
     533,   534,   535,   536,  -821,   350,  -821,   537,   540,   375,
     543,   544,   545,   377,  -821,    30,   547,   379,   382,  -821,
     170,   549,   550,    51,  -821,   383,   553,   558,   393,   559,
     395,   399,   561,   565,   402,   423,   567,   568,   569,   570,
     456,  -821,   572,   -73,  -821,   587,   165,  -821,  -821,  -821,
     590,   592,   593,    55,    55,    55,  -821,   594,   595,   596,
     597,   600,  -821,  -821,  -821,  -821,  -821,   436,   602,   603,
     604,   605,   440,   374,   606,   608,   609,   610,   611,   612,
     614,   615,   616,   617,  -821,   618,   605,   620,  -821,   623,
    -821,  -821,   624,   625,   446,   451,   452,  -821,  -821,   623,
     461,   626,  -821,   462,  -821,   465,  -821,   470,  -821,  -821,
    -821,   623,   623,   623,   473,   481,   484,   485,  -821,   486,
     487,  -821,   488,   489,   490,  -821,  -821,   491,  -821,  -821,
    -821,   492,    55,  -821,  -821,   493,   494,  -821,   495,  -821,
    -821,    26,   498,  -821,  -821,    15,   496,   497,   499,  -821,
     631,  -821,   632,  -821,    55,    59,   -73,  -821,  -821,  -821,
     165,    25,   213,   213,   634,  -821,   635,   637,   638,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,   639,   -50,    55,
     139,   556,   640,   641,   642,   229,    99,   138,  -821,   456,
    -821,  -821,   643,   645,  -821,  -821,  -821,  -821,  -821,   -39,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,   646,   634,  -821,   164,   182,   191,
     259,  -821,  -821,  -821,  -821,   664,   666,   667,   668,   669,
    -821,   670,   671,  -821,   672,   673,   674,  -821,   260,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,   270,  -821,   633,
     676,  -821,  -821,   675,   677,  -821,  -821,   678,   679,  -821,
    -821,   680,   682,  -821,  -821,   681,   685,  -821,  -821,  -821,
     167,  -821,  -821,  -821,   683,  -821,  -821,  -821,   190,  -821,
    -821,  -821,  -821,   271,  -821,  -821,  -821,   297,  -821,  -821,
     684,   688,  -821,  -821,   686,   690,  -821,   691,   692,   693,
     694,   695,   696,   273,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,   697,   698,   699,  -821,  -821,  -821,  -821,
     301,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,   304,  -821,  -821,  -821,   307,   513,  -821,   700,
     701,  -821,  -821,   702,   704,  -821,  -821,  -821,   703,  -821,
    -821,   333,  -821,   706,  -821,  -821,  -821,  -821,   705,   709,
     710,   711,   539,   532,   546,   548,   551,   712,   552,   554,
     714,   555,   557,   560,   213,  -821,  -821,   213,  -821,   634,
     218,  -821,   635,    30,  -821,   637,   170,  -821,   638,   390,
    -821,   639,   -50,  -821,  -821,   139,  -821,   715,   556,  -821,
     121,   640,  -821,   350,  -821,   641,   -54,  -821,   642,   563,
     564,   566,   571,   573,   574,   229,  -821,   716,   720,   575,
     576,   577,    99,  -821,   723,   725,   138,  -821,  -821,  -821,
     724,   728,    64,  -821,   643,   233,  -821,   645,   732,  -821,
      44,   646,  -821,  -821,   397,   562,   579,   580,  -821,  -821,
    -821,  -821,  -821,   581,  -821,  -821,   582,  -821,  -821,  -821,
    -821,   308,  -821,   311,  -821,   730,  -821,   731,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,   315,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,   583,  -821,  -821,   736,  -821,  -821,  -821,  -821,  -821,
     733,   740,  -821,  -821,  -821,  -821,  -821,   746,  -821,   318,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,   107,   585,
    -821,  -821,  -821,  -821,   586,   588,  -821,  -821,   589,   319,
    -821,   334,  -821,   591,  -821,   753,  -821,  -821,  -821,  -821,
    -821,   335,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,   390,  -821,  -821,   756,   598,  -821,   121,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,   758,   613,   759,    44,  -821,  -821,   629,  -821,  -821,
     689,  -821,   630,  -821,  -821,   757,  -821,  -821,   343,  -821,
      -5,   757,  -821,  -821,   761,   763,   764,   344,  -821,  -821,
    -821,  -821,  -821,  -821,   770,   628,   622,   644,    -5,  -821,
     650,  -821,  -821,  -821,  -821,  -821
  };

  const unsigned short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   117,     9,
     258,    11,   404,    13,   429,    15,   459,    17,   329,    19,
     337,    21,   374,    23,   223,    25,   558,    27,   628,    29,
     619,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     461,     0,   339,   376,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   626,   611,   613,   615,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   617,   115,
     129,   131,   133,     0,     0,     0,     0,     0,   113,   250,
     327,   366,   417,   419,   292,   300,   196,   213,   204,   189,
     496,   451,   215,   234,   517,     0,   541,   554,   556,   107,
       0,    74,    76,    77,    78,    79,    80,   105,    83,    84,
      85,    86,   102,    87,    89,    88,    93,    94,    81,   106,
      82,    91,    92,   100,   101,   103,    90,    95,    96,    97,
      98,    99,   104,   126,     0,   125,     0,   119,   121,   122,
     123,   124,   396,   421,   282,   284,   286,     0,     0,   290,
     288,   490,   281,   262,   263,   264,   265,     0,   260,   269,
     270,   271,   274,   275,   277,   272,   273,   266,   267,   279,
     280,   268,   276,   278,   415,   414,   410,   411,   409,     0,
     406,   408,   412,   413,   444,     0,   447,     0,     0,   443,
     437,   438,   436,   441,   442,     0,   431,   433,   434,   439,
     440,   435,   488,   476,   478,   480,   482,   484,   486,   475,
     472,   473,   474,     0,   462,   463,   467,   468,   465,   469,
     470,   471,   466,     0,   356,   174,     0,   360,   358,   363,
       0,   352,   353,     0,   340,   341,   343,   355,   344,   345,
     346,   362,   347,   348,   349,   350,   351,   390,     0,     0,
     388,   389,   392,   393,     0,   377,   378,   380,   381,   382,
     383,   384,   385,   386,   387,   230,   232,   227,     0,   225,
     228,   229,     0,   581,   583,     0,   586,     0,     0,   590,
     594,     0,     0,   598,   605,   607,   609,   579,   577,   578,
       0,   560,   562,   563,   564,   565,   566,   567,   568,   569,
     570,   571,   572,   573,   574,   575,   576,   633,     0,   630,
     632,   624,     0,   621,   623,    48,     0,     0,    41,     0,
       0,     0,     0,     0,     0,    59,     0,    61,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      73,     0,     0,     0,   118,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   259,     0,     0,   405,
       0,     0,     0,     0,     0,     0,   430,     0,     0,     0,
       0,     0,     0,     0,   460,     0,   330,     0,     0,     0,
       0,     0,     0,     0,   338,     0,     0,     0,     0,   375,
       0,     0,     0,     0,   224,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   559,     0,     0,   629,     0,     0,   620,    52,    45,
       0,     0,     0,     0,     0,     0,    63,     0,     0,     0,
       0,     0,   108,   109,   110,   111,   112,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   540,     0,     0,     0,    75,     0,
     128,   120,     0,     0,     0,     0,     0,   298,   299,     0,
       0,     0,   261,     0,   407,     0,   446,     0,   449,   450,
     432,     0,     0,     0,     0,     0,     0,     0,   464,     0,
       0,   354,     0,     0,     0,   365,   342,     0,   394,   395,
     379,     0,     0,   226,   580,     0,     0,   585,     0,   588,
     589,     0,     0,   596,   597,     0,     0,     0,     0,   561,
       0,   631,     0,   622,     0,     0,     0,   612,   614,   616,
       0,     0,     0,     0,   135,   114,   252,   331,   368,    42,
     418,   420,   294,   295,   296,   297,   293,   302,     0,    49,
       0,     0,     0,   453,   217,     0,     0,     0,   555,     0,
      53,   127,   398,   423,   283,   285,   287,   291,   289,     0,
     416,   445,   448,   489,   477,   479,   481,   483,   485,   487,
     357,   175,   361,   359,   364,   391,   231,   233,   582,   584,
     587,   592,   593,   591,   595,   600,   601,   602,   603,   604,
     599,   606,   608,   610,     0,   135,    46,     0,     0,     0,
       0,   161,   167,   169,   171,     0,     0,     0,     0,     0,
     184,     0,     0,   187,     0,     0,     0,   160,     0,   141,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     155,   156,   157,   158,   153,   154,   159,     0,   139,     0,
     136,   137,   256,     0,   253,   254,   335,     0,   332,   333,
     372,     0,   369,   370,   306,     0,   303,   304,   202,   203,
       0,   198,   200,   201,     0,   211,   212,   208,     0,   206,
     209,   210,   194,     0,   191,   193,   500,     0,   498,   457,
       0,   454,   455,   221,     0,   218,   219,     0,     0,     0,
       0,     0,     0,     0,   236,   238,   239,   240,   241,   242,
     243,   530,   536,     0,     0,     0,   529,   526,   527,   528,
       0,   519,   521,   524,   522,   523,   525,   550,   552,   549,
     547,   548,     0,   543,   545,   546,     0,    55,   402,     0,
     399,   400,   427,     0,   424,   425,   494,   493,     0,   492,
     637,     0,   635,     0,    71,   627,   618,   116,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   130,   132,     0,   134,     0,
       0,   251,     0,   339,   328,     0,   376,   367,     0,     0,
     301,     0,     0,   197,   214,     0,   205,     0,     0,   190,
     502,     0,   497,   461,   452,     0,     0,   216,     0,     0,
       0,     0,     0,     0,     0,     0,   235,     0,     0,     0,
       0,     0,     0,   518,     0,     0,     0,   542,   557,    57,
       0,    56,     0,   397,     0,     0,   422,     0,     0,   491,
       0,     0,   634,   625,     0,     0,     0,     0,   173,   176,
     177,   178,   179,     0,   186,   180,     0,   181,   182,   183,
     142,     0,   138,     0,   255,     0,   334,     0,   371,   326,
     321,   323,   314,   315,   310,   311,   312,   313,   319,   320,
     318,   322,     0,   308,   316,   324,   325,   317,   305,   199,
     207,     0,   192,   514,     0,   512,   513,   509,   510,   511,
       0,   503,   504,   506,   507,   508,   499,     0,   456,     0,
     220,   244,   245,   246,   247,   248,   249,   237,     0,     0,
     535,   538,   539,   520,     0,     0,   544,    54,     0,     0,
     401,     0,   426,     0,   651,     0,   649,   647,   641,   645,
     646,     0,   639,   643,   644,   642,   636,   163,   164,   165,
     166,   162,   168,   170,   172,   185,   188,   140,   257,   336,
     373,     0,   307,   195,     0,     0,   501,     0,   458,   222,
     532,   533,   534,   531,   537,   551,   553,    58,   403,   428,
     495,     0,     0,     0,     0,   638,   309,     0,   516,   505,
       0,   648,     0,   640,   515,     0,   650,   655,     0,   653,
       0,     0,   652,   663,     0,     0,     0,     0,   657,   659,
     660,   661,   662,   654,     0,     0,     0,     0,     0,   656,
       0,   665,   666,   667,   658,   664
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,     6,  -821,  -453,
    -821,   265,  -821,  -821,  -821,  -821,   174,  -821,  -408,  -821,
    -821,  -821,   -74,  -821,  -821,  -821,   443,  -821,  -821,  -821,
    -821,   211,   411,   -62,   -46,   -45,   -43,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,   220,   420,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,   149,  -821,   -12,  -821,  -565,
      -3,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,   -70,  -821,  -600,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,   -26,
    -821,  -821,  -821,  -821,  -821,   -19,  -584,  -821,  -821,  -821,
    -821,   -20,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
     -28,  -821,  -821,  -821,   -25,   404,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,   -31,  -821,  -821,  -821,  -821,  -821,  -821,
    -820,  -821,  -821,  -821,     1,  -821,  -821,  -821,     5,   431,
    -821,  -821,  -819,  -821,  -816,  -821,   -36,  -821,   -32,  -821,
     -42,  -821,  -821,  -821,  -813,  -821,  -821,  -821,  -821,    -4,
    -821,  -821,  -173,   769,  -821,  -821,  -821,  -821,  -821,     8,
    -821,  -821,  -821,    11,  -821,   410,  -821,   -76,  -821,  -821,
    -821,  -821,  -821,   -69,  -821,  -821,  -821,  -821,  -821,   -11,
    -821,  -821,  -821,     3,  -821,  -821,  -821,    18,  -821,   415,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,   -33,  -821,  -821,  -821,   -23,   454,  -821,  -821,   -58,
    -821,   -24,  -821,  -821,  -821,  -821,  -821,   -30,  -821,  -821,
    -821,   -29,   445,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
     -60,  -821,  -821,  -821,     9,  -821,  -821,  -821,    10,  -821,
     442,   249,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -812,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,    14,  -821,  -821,  -821,  -148,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,    -2,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,    -1,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,   263,
     413,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,  -821,
    -821,  -821,  -821,  -821,  -821,  -821,  -821,   299,   412,  -821,
    -821,  -821,  -821,  -821,  -821,   300,   414,  -821,  -821,  -821,
     -10,  -821,  -821,  -154,  -821,  -821,  -821,  -821,  -821,  -821,
    -169,  -821,  -821,  -185,  -821,  -821,  -821,  -821,  -821
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   600,    92,    93,    43,    72,    89,    90,   621,   797,
     890,   891,   687,    45,    74,   101,   102,   103,   360,    47,
      75,   140,   141,   142,   143,   144,   145,   146,   147,   378,
     148,   369,    49,    76,   176,   177,   178,   401,   179,   149,
     370,   150,   371,   151,   372,   709,   710,   711,   837,   688,
     689,   690,   818,  1011,   691,   819,   692,   820,   693,   821,
     694,   695,   438,   696,   697,   698,   699,   700,   701,   702,
     703,   704,   827,   705,   706,   830,   152,   389,   743,   744,
     745,   857,   153,   386,   730,   731,   732,   733,   154,   388,
     738,   739,   740,   741,   155,   387,   156,   392,   754,   755,
     756,   866,    65,    84,   308,   309,   310,   451,   311,   452,
     157,   393,   763,   764,   765,   766,   767,   768,   769,   770,
     158,   379,   713,   714,   715,   840,    51,    77,   197,   198,
     199,   407,   200,   408,   201,   409,   202,   413,   203,   412,
     159,   384,   606,   205,   206,   160,   385,   725,   726,   727,
     849,   942,   943,   161,   380,    59,    81,   717,   718,   719,
     843,    61,    82,   273,   274,   275,   276,   277,   278,   279,
     437,   280,   441,   281,   440,   282,   283,   442,   284,   162,
     381,   721,   722,   723,   846,    63,    83,   294,   295,   296,
     297,   298,   446,   299,   300,   301,   302,   208,   405,   799,
     800,   801,   892,    53,    78,   219,   220,   221,   417,   163,
     382,   164,   383,   211,   406,   803,   804,   805,   895,    55,
      79,   235,   236,   237,   420,   238,   239,   422,   240,   241,
     165,   391,   750,   751,   752,   863,    57,    80,   253,   254,
     255,   256,   428,   257,   429,   258,   430,   259,   431,   260,
     432,   261,   433,   262,   427,   213,   414,   808,   809,   898,
     166,   390,   747,   748,   860,   960,   961,   962,   963,   964,
    1024,   965,   167,   394,   780,   781,   782,   877,  1033,   783,
     784,   878,   785,   786,   168,   169,   396,   792,   793,   794,
     884,   795,   885,   170,   397,   171,   398,    67,    85,   330,
     331,   332,   333,   456,   334,   457,   335,   336,   459,   337,
     338,   339,   462,   653,   340,   463,   341,   342,   343,   466,
     660,   344,   467,   345,   468,   346,   469,   104,   362,   105,
     363,   106,   364,   172,   368,    71,    87,   352,   353,   354,
     475,   107,   361,    69,    86,   348,   349,   350,   472,   811,
     812,   900,  1001,  1002,  1003,  1004,  1043,  1005,  1041,  1058,
    1059,  1060,  1067,  1068,  1069,  1074,  1070,  1071,  1072
  };

  const unsigned short
  Dhcp6Parser::yytable_[] =
  {
     100,   139,   175,   192,   215,   229,   249,   292,   271,   290,
     307,   327,   272,   291,   293,   193,   777,   212,   180,   209,
     222,   233,   251,    40,   285,   303,   737,   328,   707,   935,
     936,   194,   195,   937,   196,   204,   941,   947,    94,   173,
     174,   728,   216,   230,   305,   306,   217,   231,   599,   264,
     243,    91,   181,   210,   223,   234,   252,   806,   286,   304,
      33,   329,    34,   599,    35,    32,   207,   218,   232,   250,
     108,   347,   109,    44,   366,   110,   111,   112,   265,   367,
     266,   267,   399,   403,   268,   269,   270,   400,   404,   415,
     122,   123,   265,   120,   416,   122,   123,    46,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   418,   425,   122,
     123,   121,   419,   426,   453,    48,    99,    50,   771,   454,
     729,   627,   214,   470,   122,   123,    52,   676,   471,   122,
     123,   124,    54,   633,   634,   635,   125,   126,   127,   128,
     129,  1063,   130,    56,  1064,  1065,  1066,   131,   189,   305,
     306,   190,   655,   656,   657,   658,   132,   473,   476,   133,
     651,   652,   474,   477,   122,   123,   134,   399,   121,   265,
     852,    95,   814,   853,   135,   136,    58,   351,   137,   138,
      96,    97,    98,    60,    62,   473,   122,   123,   659,   994,
     815,   995,   996,   855,   476,    99,   856,   356,    99,   816,
      99,   935,   936,   122,   123,   937,   953,   954,   941,   947,
     772,   773,   774,   775,    99,  1030,  1031,  1032,   265,   287,
     266,   267,   288,   289,    64,    36,    37,    38,    39,    99,
     728,   735,   671,   736,    99,   122,   123,   672,   673,   674,
     675,   676,   677,   678,   679,   680,   681,   682,   683,   684,
     685,   686,    66,    68,    70,   787,   788,   113,   114,   115,
     116,   265,   403,   834,   355,   121,   357,   817,   835,    99,
     359,   737,   921,   834,   858,   182,   875,   183,   836,   859,
     121,   876,   777,   122,   123,   184,   185,   186,   187,   188,
     124,    99,   100,   224,   225,   226,   227,   228,   122,   123,
     861,   358,   189,   862,   882,   190,   131,   886,    99,   883,
     470,   834,   887,   191,   415,   888,  1017,   189,  1021,  1018,
     190,   453,   418,  1022,   365,   139,  1029,  1038,   373,   175,
     757,   758,   759,   760,   761,   762,   901,   425,  1044,   902,
      99,   192,  1039,  1045,   215,   180,  1061,  1078,   434,  1062,
     374,   229,  1079,   193,   435,   212,   375,   209,   376,   377,
     222,   249,   478,   479,   395,   402,   410,   233,   411,   194,
     195,   271,   196,   204,   292,   272,   290,   251,   436,   181,
     291,   293,   216,    99,   421,   423,   217,   285,    99,   230,
     424,   210,   303,   231,   223,   439,   327,   121,   443,   445,
     444,   234,   447,    99,   207,   448,   450,   218,   449,   455,
     458,   252,   328,   460,   232,   122,   123,  1007,  1008,  1009,
    1010,   286,   461,   464,   250,   465,   304,   480,   481,   113,
     114,   115,   116,   242,   482,   119,   483,   121,   265,   243,
     244,   245,   246,   247,   248,   484,   329,   602,   603,   604,
     605,   485,   487,   488,   489,   122,   123,   490,   185,   186,
     492,   188,   124,   491,   497,   493,   494,   495,   498,   496,
     499,   500,   501,   502,   189,   503,   504,   190,   505,   506,
     507,   508,   509,   510,   511,   191,   512,   513,   514,   587,
     588,   589,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,   515,   516,   517,
     519,   139,   520,   522,   523,   524,   525,   175,   526,   527,
      99,   122,   123,   529,   530,   531,   528,   533,   535,   536,
     537,   541,   542,   180,   538,   543,   539,   544,   545,   546,
     547,   549,   776,   789,   550,   327,   551,   552,   553,   554,
     555,   557,   558,   561,   562,   559,   564,   565,   778,   790,
      99,   328,   566,   568,   567,   571,   569,   181,   647,   572,
     570,   575,   576,   577,   578,   573,   580,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     666,   582,   779,   791,   584,   329,   574,   325,   326,   585,
     586,   590,   591,   592,   593,   594,   595,   596,   597,   598,
     601,   607,    34,   608,   609,   610,   624,   612,   611,   613,
     614,   625,   626,   615,   616,   617,    99,   619,   620,   622,
     623,   628,   630,   629,   654,   631,   664,   665,   742,   838,
     632,   708,   712,   636,   716,   720,   724,   746,   749,   753,
     798,   637,   802,   810,   638,   639,   640,   641,   642,   643,
     644,   645,   646,   648,   649,   650,   661,   662,   822,   663,
     823,   824,   825,   826,   828,   829,   831,   832,   833,   839,
     842,   841,   845,   889,   844,   848,   847,   850,   851,   854,
     864,   865,   867,   868,  1055,   869,   870,   871,   872,   873,
     874,   879,   880,   881,   894,   909,   893,   897,   896,   904,
     908,   899,   903,   905,   906,   907,   913,   910,   916,   951,
     978,   911,   912,   914,   979,   915,   917,   984,   918,   985,
     987,   988,  1012,   919,   971,   972,   993,   973,  1019,  1020,
    1025,  1026,   974,  1027,   975,   976,   980,   981,   982,  1013,
    1014,  1015,  1016,  1023,  1028,  1034,  1035,  1042,  1036,  1037,
    1047,  1040,  1050,  1052,  1057,  1075,   192,  1076,  1077,   271,
     292,  1048,   290,   272,  1080,   929,   291,   293,   193,   934,
     212,   618,   209,   734,  1051,   285,   955,   930,   303,   249,
     956,   945,   307,  1082,   194,   195,   667,   196,   204,  1054,
    1056,  1081,   958,   931,   932,   251,   933,   940,   776,   486,
     518,   670,   789,   938,   813,  1083,   210,   939,   215,   286,
    1085,   229,   304,   521,   778,   946,   997,   922,   790,   207,
     998,   920,   952,   949,   222,   950,   959,   233,   944,   252,
     970,   969,   999,   924,   977,   923,   532,   948,  1046,   957,
     263,   928,   250,   926,   925,   556,   216,   563,   779,   230,
     217,   990,   791,   231,   927,   560,   991,   992,   223,   989,
     540,   234,   534,   967,   968,   966,  1000,   548,   807,  1049,
     983,   218,   796,   579,   232,   986,   668,   581,   583,   669,
    1053,  1006,  1073,  1084,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   929,     0,     0,
       0,   934,     0,   955,     0,     0,     0,   956,     0,   930,
       0,     0,     0,   945,     0,     0,     0,     0,     0,   958,
     997,     0,     0,     0,   998,   931,   932,     0,   933,   940,
       0,     0,     0,     0,     0,   938,   999,     0,     0,   939,
       0,     0,     0,     0,     0,     0,     0,   946,     0,     0,
       0,     0,     0,   959,     0,     0,     0,     0,     0,     0,
     944,     0,     0,     0,     0,     0,   957,     0,     0,     0,
    1000
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    83,    82,    83,
      84,    85,    82,    83,    83,    77,   616,    77,    76,    77,
      78,    79,    80,    17,    82,    83,   610,    85,   593,   849,
     849,    77,    77,   849,    77,    77,   849,   849,    10,    14,
      15,    91,    78,    79,    98,    99,    78,    79,   501,    19,
      89,   170,    76,    77,    78,    79,    80,    96,    82,    83,
       5,    85,     7,   516,     9,     0,    77,    78,    79,    80,
      11,   144,    13,     7,     3,    16,    17,    18,    48,     8,
      50,    51,     3,     3,    54,    55,    56,     8,     8,     3,
      65,    66,    48,    46,     8,    65,    66,     7,    39,    40,
      41,    42,    43,    44,    45,    46,    47,     3,     3,    65,
      66,    47,     8,     8,     3,     7,   170,     7,    19,     8,
     170,   529,    58,     3,    65,    66,     7,    28,     8,    65,
      66,    72,     7,   541,   542,   543,    77,    78,    79,    80,
      81,   146,    83,     7,   149,   150,   151,    88,    84,    98,
      99,    87,   137,   138,   139,   140,    97,     3,     3,   100,
     134,   135,     8,     8,    65,    66,   107,     3,    47,    48,
       3,   143,     8,     6,   115,   116,     7,    12,   119,   120,
     152,   153,   154,     7,     7,     3,    65,    66,   173,   145,
       8,   147,   148,     3,     3,   170,     6,     3,   170,     8,
     170,  1021,  1021,    65,    66,  1021,    85,    86,  1021,  1021,
     111,   112,   113,   114,   170,   108,   109,   110,    48,    49,
      50,    51,    52,    53,     7,   170,   171,   172,   173,   170,
      91,    92,    19,    94,   170,    65,    66,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,     7,     7,     7,   117,   118,    39,    40,    41,
      42,    48,     3,     3,     6,    47,     4,     8,     8,   170,
       3,   855,   837,     3,     3,    57,     3,    59,     8,     8,
      47,     8,   882,    65,    66,    67,    68,    69,    70,    71,
      72,   170,   366,    60,    61,    62,    63,    64,    65,    66,
       3,     8,    84,     6,     3,    87,    88,     3,   170,     8,
       3,     3,     8,    95,     3,     8,     8,    84,     3,     8,
      87,     3,     3,     8,     4,   399,     8,     8,     4,   403,
     101,   102,   103,   104,   105,   106,     3,     3,     3,     6,
     170,   415,     8,     8,   418,   403,     3,     3,     8,     6,
       4,   425,     8,   415,     3,   415,     4,   415,     4,     4,
     418,   435,   356,   357,     4,     4,     4,   425,     4,   415,
     415,   445,   415,   415,   450,   445,   450,   435,     8,   403,
     450,   450,   418,   170,     4,     4,   418,   445,   170,   425,
       4,   415,   450,   425,   418,     4,   470,    47,     4,     3,
       8,   425,     4,   170,   415,     4,     3,   418,     8,     4,
       4,   435,   470,     4,   425,    65,    66,    20,    21,    22,
      23,   445,     4,     4,   435,     4,   450,   170,     4,    39,
      40,    41,    42,    83,     4,    45,     4,    47,    48,    89,
      90,    91,    92,    93,    94,     4,   470,    73,    74,    75,
      76,     4,     4,     4,     4,    65,    66,     4,    68,    69,
     171,    71,    72,     4,     4,   171,   171,   171,     4,   171,
       4,     4,     4,     4,    84,     4,     4,    87,     4,     4,
       4,     4,     4,     4,     4,    95,     4,     4,   171,   483,
     484,   485,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,     4,     4,     4,
       4,   585,   173,     4,     4,     4,     4,   591,     4,   171,
     170,    65,    66,     4,     4,     4,   173,     4,     4,   171,
       4,     4,     4,   591,   171,     4,   171,     4,     4,     4,
       4,     4,   616,   617,     4,   619,   171,     4,     4,     4,
     173,     4,   173,     4,     4,   173,   173,     4,   616,   617,
     170,   619,     4,     4,   171,     4,   171,   591,   562,     4,
     171,     4,     4,     4,     4,   173,     4,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     584,     4,   616,   617,     4,   619,   173,   141,   142,     7,
       7,     7,     7,     7,     7,     5,   170,     5,     5,     5,
     170,     5,     7,     5,     5,     5,   170,     5,     7,     5,
       5,   170,   170,     7,     7,     7,   170,     7,     5,     5,
       5,   170,   170,     7,   136,   170,     5,     5,    82,     6,
     170,     7,     7,   170,     7,     7,     7,     7,     7,     7,
       7,   170,     7,     7,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,     4,   170,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     3,
       3,     6,     3,   170,     6,     3,     6,     6,     3,     6,
       6,     3,     6,     3,     5,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     3,   173,     6,     3,     6,     4,
     171,     8,     6,     4,     4,     4,     4,   171,     4,     4,
       4,   173,   171,   171,     4,   171,   171,     4,   171,     4,
       6,     3,   170,   173,   171,   171,     4,   171,     8,     8,
       4,     8,   171,     3,   171,   171,   171,   171,   171,   170,
     170,   170,   170,   170,     8,   170,   170,     4,   170,   170,
       4,   170,     4,     4,     7,     4,   840,     4,     4,   843,
     846,   173,   846,   843,     4,   849,   846,   846,   840,   849,
     840,   516,   840,   609,   171,   843,   860,   849,   846,   863,
     860,   849,   866,   171,   840,   840,   585,   840,   840,   170,
     170,   173,   860,   849,   849,   863,   849,   849,   882,   366,
     399,   591,   886,   849,   665,   171,   840,   849,   892,   843,
     170,   895,   846,   403,   882,   849,   900,   839,   886,   840,
     900,   834,   858,   852,   892,   855,   860,   895,   849,   863,
     868,   866,   900,   842,   875,   840,   415,   851,  1021,   860,
      81,   848,   863,   845,   843,   445,   892,   453,   882,   895,
     892,   894,   886,   895,   846,   450,   895,   897,   892,   892,
     425,   895,   418,   863,   865,   861,   900,   435,   629,  1027,
     882,   892,   619,   470,   895,   886,   586,   473,   476,   590,
    1044,   901,  1061,  1078,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1021,    -1,    -1,
      -1,  1021,    -1,  1027,    -1,    -1,    -1,  1027,    -1,  1021,
      -1,    -1,    -1,  1021,    -1,    -1,    -1,    -1,    -1,  1027,
    1044,    -1,    -1,    -1,  1044,  1021,  1021,    -1,  1021,  1021,
      -1,    -1,    -1,    -1,    -1,  1021,  1044,    -1,    -1,  1021,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1021,    -1,    -1,
      -1,    -1,    -1,  1027,    -1,    -1,    -1,    -1,    -1,    -1,
    1021,    -1,    -1,    -1,    -1,    -1,  1027,    -1,    -1,    -1,
    1044
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
       7,   355,     7,   379,     7,   296,     7,   491,     7,   537,
       7,   529,   199,   194,   208,   214,   227,   321,   398,   414,
     431,   350,   356,   380,   297,   492,   538,   530,   191,   200,
     201,   170,   196,   197,    10,   143,   152,   153,   154,   170,
     206,   209,   210,   211,   521,   523,   525,   535,    11,    13,
      16,    17,    18,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    65,    66,    72,    77,    78,    79,    80,    81,
      83,    88,    97,   100,   107,   115,   116,   119,   120,   206,
     215,   216,   217,   218,   219,   220,   221,   222,   224,   233,
     235,   237,   270,   276,   282,   288,   290,   304,   314,   334,
     339,   347,   373,   403,   405,   424,   454,   466,   478,   479,
     487,   489,   527,    14,    15,   206,   228,   229,   230,   232,
     403,   405,    57,    59,    67,    68,    69,    70,    71,    84,
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
     508,   510,   511,   512,   515,   517,   519,   144,   539,   540,
     541,    12,   531,   532,   533,     6,     3,     4,     8,     3,
     212,   536,   522,   524,   526,     4,     3,     8,   528,   225,
     234,   236,   238,     4,     4,     4,     4,     4,   223,   315,
     348,   374,   404,   406,   335,   340,   277,   289,   283,   271,
     455,   425,   291,   305,   467,     4,   480,   488,   490,     3,
       8,   231,     4,     3,     8,   392,   408,   325,   327,   329,
       4,     4,   333,   331,   450,     3,     8,   402,     3,     8,
     418,     4,   421,     4,     4,     3,     8,   448,   436,   438,
     440,   442,   444,   446,     8,     3,     8,   364,   256,     4,
     368,   366,   371,     4,     8,     3,   386,     4,     4,     8,
       3,   301,   303,     3,     8,     4,   497,   499,     4,   502,
       4,     4,   506,   509,     4,     4,   513,   516,   518,   520,
       3,     8,   542,     3,     8,   534,     3,     8,   191,   191,
     170,     4,     4,     4,     4,     4,   210,     4,     4,     4,
       4,     4,   171,   171,   171,   171,   171,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   171,     4,     4,     4,   216,     4,
     173,   229,     4,     4,     4,     4,     4,   171,   173,     4,
       4,     4,   323,     4,   400,     4,   171,     4,   171,   171,
     416,     4,     4,     4,     4,     4,     4,     4,   434,     4,
       4,   171,     4,     4,     4,   173,   359,     4,   173,   173,
     383,     4,     4,   299,   173,     4,     4,   171,     4,   171,
     171,     4,     4,   173,   173,     4,     4,     4,     4,   494,
       4,   540,     4,   532,     4,     7,     7,   191,   191,   191,
       7,     7,     7,     7,     5,   170,     5,     5,     5,   193,
     195,   170,    73,    74,    75,    76,   336,     5,     5,     5,
       5,     7,     5,     5,     5,     7,     7,     7,   195,     7,
       5,   202,     5,     5,   170,   170,   170,   202,   170,     7,
     170,   170,   170,   202,   202,   202,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   191,   170,   170,
     170,   134,   135,   507,   136,   137,   138,   139,   140,   173,
     514,   170,   170,   170,     5,     5,   191,   215,   539,   531,
     228,    19,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,   206,   243,   244,
     245,   248,   250,   252,   254,   255,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   267,   268,   243,     7,   239,
     240,   241,     7,   316,   317,   318,     7,   351,   352,   353,
       7,   375,   376,   377,     7,   341,   342,   343,    91,   170,
     278,   279,   280,   281,   200,    92,    94,   280,   284,   285,
     286,   287,    82,   272,   273,   274,     7,   456,   457,     7,
     426,   427,   428,     7,   292,   293,   294,   101,   102,   103,
     104,   105,   106,   306,   307,   308,   309,   310,   311,   312,
     313,    19,   111,   112,   113,   114,   206,   257,   403,   405,
     468,   469,   470,   473,   474,   476,   477,   117,   118,   206,
     403,   405,   481,   482,   483,   485,   493,   203,     7,   393,
     394,   395,     7,   409,   410,   411,    96,   435,   451,   452,
       7,   543,   544,   239,     8,     8,     8,     8,   246,   249,
     251,   253,     4,     4,     4,     4,     4,   266,     4,     4,
     269,     4,     4,     4,     3,     8,     8,   242,     6,     3,
     319,     6,     3,   354,     6,     3,   378,     6,     3,   344,
       6,     3,     3,     6,     6,     3,     6,   275,     3,     8,
     458,     3,     6,   429,     6,     3,   295,     6,     3,     4,
       4,     4,     4,     4,     4,     3,     8,   471,   475,     4,
       4,     4,     3,     8,   484,   486,     3,     8,     8,   170,
     204,   205,   396,     6,     3,   412,     6,     3,   453,     8,
     545,     3,     6,     6,     4,     4,     4,     4,   171,   173,
     171,   173,   171,     4,   171,   171,     4,   171,   171,   173,
     244,   243,   241,   322,   318,   357,   353,   381,   377,   206,
     217,   218,   219,   220,   255,   314,   326,   328,   330,   332,
     334,   338,   345,   346,   373,   403,   405,   449,   343,   279,
     285,     4,   273,    85,    86,   206,   255,   373,   403,   405,
     459,   460,   461,   462,   463,   465,   457,   432,   428,   298,
     294,   171,   171,   171,   171,   171,   171,   307,     4,     4,
     171,   171,   171,   469,     4,     4,   482,     6,     3,   399,
     395,   415,   411,     4,   145,   147,   148,   206,   255,   403,
     405,   546,   547,   548,   549,   551,   544,    20,    21,    22,
      23,   247,   170,   170,   170,   170,   170,     8,     8,     8,
       8,     3,     8,   170,   464,     4,     8,     3,     8,     8,
     108,   109,   110,   472,   170,   170,   170,   170,     8,     8,
     170,   552,     4,   550,     3,     8,   346,     4,   173,   461,
       4,   171,     4,   547,   170,     5,   170,     7,   553,   554,
     555,     3,     6,   146,   149,   150,   151,   556,   557,   558,
     560,   561,   562,   554,   559,     4,     4,     4,     3,     8,
       4,   173,   171,   171,   557,   170
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
     216,   216,   216,   216,   216,   216,   216,   216,   217,   218,
     219,   220,   221,   223,   222,   225,   224,   227,   226,   228,
     228,   229,   229,   229,   229,   229,   231,   230,   232,   234,
     233,   236,   235,   238,   237,   239,   239,   240,   240,   242,
     241,   243,   243,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   246,   245,   247,   247,   247,   247,   249,   248,   251,
     250,   253,   252,   254,   256,   255,   257,   258,   259,   260,
     261,   262,   263,   264,   266,   265,   267,   269,   268,   271,
     270,   272,   272,   273,   275,   274,   277,   276,   278,   278,
     279,   279,   280,   281,   283,   282,   284,   284,   285,   285,
     285,   286,   287,   289,   288,   291,   290,   292,   292,   293,
     293,   295,   294,   297,   296,   298,   298,   298,   299,   299,
     301,   300,   303,   302,   305,   304,   306,   306,   307,   307,
     307,   307,   307,   307,   308,   309,   310,   311,   312,   313,
     315,   314,   316,   316,   317,   317,   319,   318,   321,   320,
     322,   322,   323,   323,   323,   323,   323,   323,   323,   323,
     323,   323,   323,   323,   323,   323,   323,   323,   323,   323,
     323,   323,   325,   324,   327,   326,   329,   328,   331,   330,
     333,   332,   335,   334,   336,   336,   336,   336,   337,   338,
     340,   339,   341,   341,   342,   342,   344,   343,   345,   345,
     346,   346,   346,   346,   346,   346,   346,   346,   346,   346,
     346,   346,   346,   346,   346,   346,   346,   348,   347,   350,
     349,   351,   351,   352,   352,   354,   353,   356,   355,   357,
     357,   358,   358,   359,   359,   359,   359,   359,   359,   359,
     359,   359,   359,   360,   361,   362,   364,   363,   366,   365,
     368,   367,   369,   371,   370,   372,   374,   373,   375,   375,
     376,   376,   378,   377,   380,   379,   381,   381,   382,   382,
     383,   383,   383,   383,   383,   383,   383,   383,   383,   384,
     386,   385,   387,   388,   389,   390,   392,   391,   393,   393,
     394,   394,   396,   395,   398,   397,   399,   399,   400,   400,
     400,   400,   400,   400,   400,   402,   401,   404,   403,   406,
     405,   408,   407,   409,   409,   410,   410,   412,   411,   414,
     413,   415,   415,   416,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   416,   418,   417,   419,   421,   420,   422,
     423,   425,   424,   426,   426,   427,   427,   429,   428,   431,
     430,   432,   432,   433,   433,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   436,   435,   438,   437,
     440,   439,   442,   441,   444,   443,   446,   445,   448,   447,
     450,   449,   451,   451,   453,   452,   455,   454,   456,   456,
     458,   457,   459,   459,   460,   460,   461,   461,   461,   461,
     461,   461,   461,   462,   464,   463,   465,   467,   466,   468,
     468,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     471,   470,   472,   472,   472,   473,   475,   474,   476,   477,
     478,   480,   479,   481,   481,   482,   482,   482,   482,   482,
     484,   483,   486,   485,   488,   487,   490,   489,   492,   491,
     493,   493,   494,   494,   494,   494,   494,   494,   494,   494,
     494,   494,   494,   494,   494,   494,   494,   494,   494,   494,
     495,   497,   496,   499,   498,   500,   502,   501,   503,   504,
     506,   505,   507,   507,   509,   508,   510,   511,   513,   512,
     514,   514,   514,   514,   514,   516,   515,   518,   517,   520,
     519,   522,   521,   524,   523,   526,   525,   528,   527,   530,
     529,   531,   531,   532,   534,   533,   536,   535,   538,   537,
     539,   539,   540,   542,   541,   543,   543,   545,   544,   546,
     546,   547,   547,   547,   547,   547,   547,   547,   548,   550,
     549,   552,   551,   553,   553,   555,   554,   556,   556,   557,
     557,   557,   557,   559,   558,   560,   561,   562
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
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       6,     0,     6,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     3,     0,     4,     0,
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
  "control_agent_json_object", "$@117", "config_control", "$@118",
  "sub_config_control", "$@119", "config_control_params",
  "config_control_param", "config_databases", "$@120", "logging_object",
  "$@121", "sub_logging", "$@122", "logging_params", "logging_param",
  "loggers", "$@123", "loggers_entries", "logger_entry", "$@124",
  "logger_params", "logger_param", "debuglevel", "severity", "$@125",
  "output_options_list", "$@126", "output_options_list_content",
  "output_entry", "$@127", "output_params_list", "output_params", "output",
  "$@128", "flush", "maxsize", "maxver", YY_NULLPTR
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
     462,   463,   464,   465,   466,   467,   468,   469,   472,   477,
     482,   487,   492,   497,   497,   505,   505,   516,   516,   525,
     526,   529,   530,   531,   532,   533,   536,   536,   546,   552,
     552,   564,   564,   576,   576,   586,   587,   590,   591,   594,
     594,   604,   605,   608,   609,   610,   611,   612,   613,   614,
     615,   616,   617,   618,   619,   620,   621,   622,   623,   624,
     625,   628,   628,   635,   636,   637,   638,   641,   641,   649,
     649,   657,   657,   665,   670,   670,   678,   683,   688,   693,
     698,   703,   708,   713,   718,   718,   726,   731,   731,   739,
     739,   749,   750,   752,   754,   754,   772,   772,   782,   783,
     786,   787,   790,   795,   800,   800,   810,   811,   814,   815,
     816,   819,   824,   831,   831,   841,   841,   851,   852,   855,
     856,   859,   859,   869,   869,   879,   880,   881,   884,   885,
     888,   888,   896,   896,   904,   904,   915,   916,   919,   920,
     921,   922,   923,   924,   927,   932,   937,   942,   947,   952,
     960,   960,   973,   974,   977,   978,   985,   985,  1011,  1011,
    1022,  1023,  1027,  1028,  1029,  1030,  1031,  1032,  1033,  1034,
    1035,  1036,  1037,  1038,  1039,  1040,  1041,  1042,  1043,  1044,
    1045,  1046,  1049,  1049,  1057,  1057,  1065,  1065,  1073,  1073,
    1081,  1081,  1091,  1091,  1098,  1099,  1100,  1101,  1104,  1109,
    1117,  1117,  1128,  1129,  1133,  1134,  1137,  1137,  1145,  1146,
    1149,  1150,  1151,  1152,  1153,  1154,  1155,  1156,  1157,  1158,
    1159,  1160,  1161,  1162,  1163,  1164,  1165,  1172,  1172,  1185,
    1185,  1194,  1195,  1198,  1199,  1204,  1204,  1219,  1219,  1233,
    1234,  1237,  1238,  1241,  1242,  1243,  1244,  1245,  1246,  1247,
    1248,  1249,  1250,  1253,  1255,  1260,  1262,  1262,  1270,  1270,
    1278,  1278,  1286,  1288,  1288,  1296,  1305,  1305,  1317,  1318,
    1323,  1324,  1329,  1329,  1341,  1341,  1353,  1354,  1359,  1360,
    1365,  1366,  1367,  1368,  1369,  1370,  1371,  1372,  1373,  1376,
    1378,  1378,  1386,  1388,  1390,  1395,  1403,  1403,  1415,  1416,
    1419,  1420,  1423,  1423,  1433,  1433,  1442,  1443,  1446,  1447,
    1448,  1449,  1450,  1451,  1452,  1455,  1455,  1463,  1463,  1488,
    1488,  1518,  1518,  1530,  1531,  1534,  1535,  1538,  1538,  1550,
    1550,  1562,  1563,  1566,  1567,  1568,  1569,  1570,  1571,  1572,
    1573,  1574,  1575,  1576,  1579,  1579,  1587,  1592,  1592,  1600,
    1605,  1613,  1613,  1623,  1624,  1627,  1628,  1631,  1631,  1640,
    1640,  1649,  1650,  1653,  1654,  1658,  1659,  1660,  1661,  1662,
    1663,  1664,  1665,  1666,  1667,  1668,  1671,  1671,  1681,  1681,
    1691,  1691,  1699,  1699,  1707,  1707,  1715,  1715,  1723,  1723,
    1736,  1736,  1746,  1747,  1750,  1750,  1761,  1761,  1771,  1772,
    1775,  1775,  1785,  1786,  1789,  1790,  1793,  1794,  1795,  1796,
    1797,  1798,  1799,  1802,  1804,  1804,  1812,  1820,  1820,  1832,
    1833,  1836,  1837,  1838,  1839,  1840,  1841,  1842,  1843,  1844,
    1847,  1847,  1854,  1855,  1856,  1859,  1864,  1864,  1872,  1877,
    1884,  1891,  1891,  1901,  1902,  1905,  1906,  1907,  1908,  1909,
    1912,  1912,  1920,  1920,  1930,  1930,  1970,  1970,  1982,  1982,
    1992,  1993,  1996,  1997,  1998,  1999,  2000,  2001,  2002,  2003,
    2004,  2005,  2006,  2007,  2008,  2009,  2010,  2011,  2012,  2013,
    2016,  2021,  2021,  2029,  2029,  2037,  2042,  2042,  2050,  2055,
    2060,  2060,  2068,  2069,  2072,  2072,  2080,  2085,  2090,  2090,
    2098,  2101,  2104,  2107,  2110,  2116,  2116,  2124,  2124,  2132,
    2132,  2142,  2142,  2149,  2149,  2156,  2156,  2165,  2165,  2176,
    2176,  2186,  2187,  2191,  2194,  2194,  2209,  2209,  2219,  2219,
    2230,  2231,  2235,  2239,  2239,  2251,  2252,  2256,  2256,  2264,
    2265,  2268,  2269,  2270,  2271,  2272,  2273,  2274,  2277,  2282,
    2282,  2290,  2290,  2300,  2301,  2304,  2304,  2312,  2313,  2316,
    2317,  2318,  2319,  2322,  2322,  2330,  2335,  2340
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
#line 5072 "dhcp6_parser.cc" // lalr1.cc:1242
#line 2345 "dhcp6_parser.yy" // lalr1.cc:1243


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
