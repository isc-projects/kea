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
#define yylex   parser4_lex



#include "dhcp4_parser.h"


// Unqualified %code blocks.
#line 34 "dhcp4_parser.yy" // lalr1.cc:435

#include <dhcp4/parser_context.h>

#line 51 "dhcp4_parser.cc" // lalr1.cc:435


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
#if PARSER4_DEBUG

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

#else // !PARSER4_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !PARSER4_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "dhcp4_parser.yy" // lalr1.cc:510
namespace isc { namespace dhcp {
#line 146 "dhcp4_parser.cc" // lalr1.cc:510

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Dhcp4Parser::yytnamerr_ (const char *yystr)
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
  Dhcp4Parser::Dhcp4Parser (isc::dhcp::Parser4Context& ctx_yyarg)
    :
#if PARSER4_DEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      ctx (ctx_yyarg)
  {}

  Dhcp4Parser::~Dhcp4Parser ()
  {}

  Dhcp4Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  Dhcp4Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Dhcp4Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Dhcp4Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Dhcp4Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Dhcp4Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Dhcp4Parser::symbol_number_type
  Dhcp4Parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  Dhcp4Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Dhcp4Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 190: // value
      case 194: // map_value
      case 238: // socket_type
      case 241: // outbound_interface_value
      case 263: // db_type
      case 349: // hr_mode
      case 498: // ncr_protocol_value
      case 505: // replace_client_name_value
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

  Dhcp4Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 190: // value
      case 194: // map_value
      case 238: // socket_type
      case 241: // outbound_interface_value
      case 263: // db_type
      case 349: // hr_mode
      case 498: // ncr_protocol_value
      case 505: // replace_client_name_value
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
  Dhcp4Parser::stack_symbol_type&
  Dhcp4Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 190: // value
      case 194: // map_value
      case 238: // socket_type
      case 241: // outbound_interface_value
      case 263: // db_type
      case 349: // hr_mode
      case 498: // ncr_protocol_value
      case 505: // replace_client_name_value
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
  Dhcp4Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if PARSER4_DEBUG
  template <typename Base>
  void
  Dhcp4Parser::yy_print_ (std::ostream& yyo,
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
#line 250 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < std::string > (); }
#line 407 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 171: // "integer"
#line 250 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 413 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 172: // "floating point"
#line 250 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < double > (); }
#line 419 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 173: // "boolean"
#line 250 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < bool > (); }
#line 425 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 190: // value
#line 250 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 431 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 194: // map_value
#line 250 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 437 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 238: // socket_type
#line 250 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 443 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 241: // outbound_interface_value
#line 250 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 449 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 263: // db_type
#line 250 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 455 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 349: // hr_mode
#line 250 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 461 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 498: // ncr_protocol_value
#line 250 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 467 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      case 505: // replace_client_name_value
#line 250 "dhcp4_parser.yy" // lalr1.cc:676
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 473 "dhcp4_parser.cc" // lalr1.cc:676
        break;

      default:
        break;
    }
    yyo << ')';
  }
#endif

  void
  Dhcp4Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Dhcp4Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Dhcp4Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if PARSER4_DEBUG
  std::ostream&
  Dhcp4Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Dhcp4Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Dhcp4Parser::debug_level_type
  Dhcp4Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Dhcp4Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // PARSER4_DEBUG

  Dhcp4Parser::state_type
  Dhcp4Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  Dhcp4Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Dhcp4Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Dhcp4Parser::operator() ()
  {
    return parse ();
  }

  int
  Dhcp4Parser::parse ()
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
      case 190: // value
      case 194: // map_value
      case 238: // socket_type
      case 241: // outbound_interface_value
      case 263: // db_type
      case 349: // hr_mode
      case 498: // ncr_protocol_value
      case 505: // replace_client_name_value
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
#line 259 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 740 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 4:
#line 260 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.CONFIG; }
#line 746 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 6:
#line 261 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP4; }
#line 752 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 8:
#line 262 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 758 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 10:
#line 263 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.SUBNET4; }
#line 764 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 12:
#line 264 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.POOLS; }
#line 770 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 14:
#line 265 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 776 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 16:
#line 266 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP4; }
#line 782 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 18:
#line 267 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 788 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 20:
#line 268 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 794 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 22:
#line 269 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 800 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 24:
#line 270 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 806 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 26:
#line 271 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.LOGGING; }
#line 812 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 28:
#line 272 "dhcp4_parser.yy" // lalr1.cc:919
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 818 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 30:
#line 280 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 824 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 31:
#line 281 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 830 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 32:
#line 282 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 836 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 33:
#line 283 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 842 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 34:
#line 284 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 848 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 35:
#line 285 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 854 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 36:
#line 286 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 860 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 37:
#line 289 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 869 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 38:
#line 294 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 880 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 39:
#line 299 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 890 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 40:
#line 305 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 896 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 43:
#line 312 "dhcp4_parser.yy" // lalr1.cc:919
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 905 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 44:
#line 316 "dhcp4_parser.yy" // lalr1.cc:919
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 915 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 45:
#line 323 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 924 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 46:
#line 326 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // list parsing complete. Put any sanity checking here
}
#line 932 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 49:
#line 334 "dhcp4_parser.yy" // lalr1.cc:919
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 941 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 50:
#line 338 "dhcp4_parser.yy" // lalr1.cc:919
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 950 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 51:
#line 345 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // List parsing about to start
}
#line 958 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 52:
#line 347 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 967 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 55:
#line 356 "dhcp4_parser.yy" // lalr1.cc:919
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 976 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 56:
#line 360 "dhcp4_parser.yy" // lalr1.cc:919
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 985 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 57:
#line 371 "dhcp4_parser.yy" // lalr1.cc:919
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 996 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 58:
#line 381 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1007 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 59:
#line 386 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1020 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 68:
#line 410 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 1033 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 69:
#line 417 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1043 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 70:
#line 425 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1053 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 71:
#line 429 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No global parameter is required
    // parsing completed
}
#line 1062 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 112:
#line 480 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1071 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 113:
#line 485 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1080 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 114:
#line 490 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1089 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 115:
#line 495 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1098 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 116:
#line 500 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1107 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 117:
#line 505 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1116 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 118:
#line 510 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1125 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 119:
#line 515 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1133 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 120:
#line 517 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1143 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 121:
#line 523 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1152 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 122:
#line 528 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1161 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 123:
#line 533 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1170 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 124:
#line 539 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1181 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 125:
#line 544 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1191 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 135:
#line 563 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1201 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 136:
#line 567 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1210 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 137:
#line 572 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1221 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 138:
#line 577 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1230 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 139:
#line 582 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1238 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 140:
#line 584 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1247 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 141:
#line 589 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1253 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 142:
#line 590 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1259 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 143:
#line 593 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1267 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 144:
#line 595 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1276 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 145:
#line 600 "dhcp4_parser.yy" // lalr1.cc:919
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1284 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 146:
#line 602 "dhcp4_parser.yy" // lalr1.cc:919
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1292 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 147:
#line 606 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1301 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 148:
#line 612 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1312 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 149:
#line 617 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1323 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 150:
#line 624 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1334 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 151:
#line 629 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1343 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 155:
#line 639 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1351 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 156:
#line 641 "dhcp4_parser.yy" // lalr1.cc:919
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
#line 1371 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 157:
#line 657 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1382 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 158:
#line 662 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1393 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 159:
#line 669 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1404 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 160:
#line 674 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1413 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 165:
#line 687 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1423 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 166:
#line 691 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1433 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 189:
#line 723 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1441 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 190:
#line 725 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1450 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 191:
#line 730 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1456 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 192:
#line 731 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1462 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 193:
#line 732 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1468 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 194:
#line 733 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1474 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 195:
#line 736 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1482 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 196:
#line 738 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1492 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 197:
#line 744 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1500 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 198:
#line 746 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1510 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 199:
#line 752 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1518 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 200:
#line 754 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1528 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 201:
#line 760 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1537 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 202:
#line 765 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1545 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 203:
#line 767 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1555 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 204:
#line 773 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1564 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 205:
#line 778 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1573 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 206:
#line 783 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1582 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 207:
#line 788 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1591 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 208:
#line 793 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1600 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 209:
#line 798 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1609 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 210:
#line 803 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1618 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 211:
#line 808 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1626 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 212:
#line 810 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1636 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 213:
#line 816 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1644 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 214:
#line 818 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1654 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 215:
#line 824 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1662 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 216:
#line 826 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1672 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 217:
#line 832 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1680 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 218:
#line 834 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1690 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 219:
#line 840 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1699 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 220:
#line 845 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1708 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 221:
#line 850 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1719 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 222:
#line 855 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1728 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 230:
#line 871 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1737 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 231:
#line 876 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1746 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 232:
#line 881 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1755 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 233:
#line 886 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1764 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 234:
#line 891 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1773 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 235:
#line 896 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1784 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 236:
#line 901 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1793 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 241:
#line 914 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1803 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 242:
#line 918 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1813 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 243:
#line 924 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1823 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 244:
#line 928 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1833 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 250:
#line 943 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1841 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 251:
#line 945 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1851 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 252:
#line 951 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1859 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 253:
#line 953 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1868 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 254:
#line 959 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1879 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 255:
#line 964 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1889 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 264:
#line 982 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1898 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 265:
#line 987 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1907 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 266:
#line 992 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1916 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 267:
#line 997 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1925 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 268:
#line 1002 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1934 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 269:
#line 1007 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1943 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 270:
#line 1015 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1954 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 271:
#line 1020 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1963 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 276:
#line 1040 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1973 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 277:
#line 1044 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Once we reached this place, the subnet parsing is now complete.
    // If we want to, we can implement default values here.
    // In particular we can do things like this:
    // if (!ctx.stack_.back()->get("interface")) {
    //     ctx.stack_.back()->set("interface", StringElement("loopback"));
    // }
    //
    // We can also stack up one level (Dhcp4) and copy over whatever
    // global parameters we want to:
    // if (!ctx.stack_.back()->get("renew-timer")) {
    //     ElementPtr renew = ctx_stack_[...].get("renew-timer");
    //     if (renew) {
    //         ctx.stack_.back()->set("renew-timer", renew);
    //     }
    // }

    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1999 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 278:
#line 1066 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2009 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 279:
#line 1070 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2019 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 309:
#line 1111 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2027 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 310:
#line 1113 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2037 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 311:
#line 1119 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2045 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 312:
#line 1121 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2055 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 313:
#line 1127 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2063 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 314:
#line 1129 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2073 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 315:
#line 1135 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2081 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 316:
#line 1137 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2091 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 317:
#line 1143 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2099 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 318:
#line 1145 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2109 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 319:
#line 1151 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2117 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 320:
#line 1153 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2127 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 321:
#line 1159 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2138 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 322:
#line 1164 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2147 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 323:
#line 1169 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2155 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 324:
#line 1171 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2164 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 325:
#line 1176 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2170 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 326:
#line 1177 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2176 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 327:
#line 1178 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2182 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 328:
#line 1179 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2188 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 329:
#line 1182 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2197 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 330:
#line 1189 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2208 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 331:
#line 1194 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2217 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 336:
#line 1209 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2227 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 337:
#line 1213 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 2235 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 362:
#line 1249 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2246 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 363:
#line 1254 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2255 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 364:
#line 1262 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2264 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 365:
#line 1265 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 2272 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 370:
#line 1281 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2282 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 371:
#line 1285 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2294 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 372:
#line 1296 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2304 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 373:
#line 1300 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2316 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 389:
#line 1332 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2325 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 391:
#line 1339 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2333 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 392:
#line 1341 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2343 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 393:
#line 1347 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2351 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 394:
#line 1349 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2361 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 395:
#line 1355 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2369 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 396:
#line 1357 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2379 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 398:
#line 1365 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2387 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 399:
#line 1367 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2397 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 400:
#line 1373 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2406 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 401:
#line 1382 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2417 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 402:
#line 1387 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2426 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 407:
#line 1406 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2436 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 408:
#line 1410 "dhcp4_parser.yy" // lalr1.cc:919
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2445 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 409:
#line 1418 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2455 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 410:
#line 1422 "dhcp4_parser.yy" // lalr1.cc:919
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2464 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 425:
#line 1455 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2472 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 426:
#line 1457 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2482 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 429:
#line 1467 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2491 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 430:
#line 1472 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2500 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 431:
#line 1480 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2511 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 432:
#line 1485 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2520 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 437:
#line 1500 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2530 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 438:
#line 1504 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2540 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 439:
#line 1510 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2550 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 440:
#line 1514 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2560 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 450:
#line 1533 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2568 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 451:
#line 1535 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2578 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 452:
#line 1541 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2586 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 453:
#line 1543 "dhcp4_parser.yy" // lalr1.cc:919
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
#line 2613 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 454:
#line 1566 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2621 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 455:
#line 1568 "dhcp4_parser.yy" // lalr1.cc:919
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
#line 2650 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 456:
#line 1596 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2661 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 457:
#line 1601 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2670 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 462:
#line 1614 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2680 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 463:
#line 1618 "dhcp4_parser.yy" // lalr1.cc:919
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2689 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 464:
#line 1623 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2699 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 465:
#line 1627 "dhcp4_parser.yy" // lalr1.cc:919
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2708 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 485:
#line 1658 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2716 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 486:
#line 1660 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2726 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 487:
#line 1666 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2734 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 488:
#line 1668 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2744 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 489:
#line 1674 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2752 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 490:
#line 1676 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2762 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 491:
#line 1682 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2770 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 492:
#line 1684 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2780 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 493:
#line 1690 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2791 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 494:
#line 1695 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2800 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 495:
#line 1700 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2808 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 496:
#line 1702 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2818 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 497:
#line 1708 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2826 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 498:
#line 1710 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2836 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 499:
#line 1716 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2844 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 500:
#line 1718 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2854 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 501:
#line 1724 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2862 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 502:
#line 1726 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2872 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 503:
#line 1732 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2880 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 504:
#line 1734 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2890 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 505:
#line 1740 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2898 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 506:
#line 1742 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2908 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 507:
#line 1748 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2919 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 508:
#line 1753 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2928 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 509:
#line 1761 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2939 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 510:
#line 1766 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2948 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 513:
#line 1778 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2959 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 514:
#line 1783 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2968 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 517:
#line 1792 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2978 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 518:
#line 1796 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2988 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 535:
#line 1825 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2996 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 536:
#line 1827 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3006 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 537:
#line 1833 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3015 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 538:
#line 1842 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3024 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 539:
#line 1849 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3035 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 540:
#line 1854 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3044 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 548:
#line 1870 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3052 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 549:
#line 1872 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3062 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 550:
#line 1878 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3070 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 551:
#line 1880 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3080 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 552:
#line 1889 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3088 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 553:
#line 1891 "dhcp4_parser.yy" // lalr1.cc:919
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

    ConstElementPtr enable_queue = qc->get("enable-queue");
    if (enable_queue->getType() != Element::boolean) {
        std::stringstream msg;
        msg << "'enable-queue' must be boolean: ";
        msg  << "(" << qc->getPosition().str() << ")";
        error(yystack_[3].location, msg.str());
    }

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
#line 3126 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 554:
#line 1927 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3137 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 555:
#line 1932 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3148 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 556:
#line 1939 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3158 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 557:
#line 1943 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3168 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 578:
#line 1973 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3177 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 579:
#line 1978 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3185 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 580:
#line 1980 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3195 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 581:
#line 1986 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3203 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 582:
#line 1988 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3213 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 583:
#line 1994 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3222 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 584:
#line 1999 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3230 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 585:
#line 2001 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3240 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 586:
#line 2007 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3249 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 587:
#line 2012 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3258 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 588:
#line 2017 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3266 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 589:
#line 2019 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3275 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 590:
#line 2025 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3281 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 591:
#line 2026 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3287 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 592:
#line 2029 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3295 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 593:
#line 2031 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3305 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 594:
#line 2037 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3314 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 595:
#line 2042 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3323 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 596:
#line 2047 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3331 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 597:
#line 2049 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3340 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 598:
#line 2055 "dhcp4_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3348 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 599:
#line 2058 "dhcp4_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3356 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 600:
#line 2061 "dhcp4_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3364 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 601:
#line 2064 "dhcp4_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3372 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 602:
#line 2067 "dhcp4_parser.yy" // lalr1.cc:919
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3381 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 603:
#line 2073 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3389 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 604:
#line 2075 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3399 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 605:
#line 2081 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3407 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 606:
#line 2083 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3417 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 607:
#line 2089 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3425 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 608:
#line 2091 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3435 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 609:
#line 2100 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3443 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 610:
#line 2102 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3452 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 611:
#line 2107 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3460 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 612:
#line 2109 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3469 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 613:
#line 2114 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3477 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 614:
#line 2116 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3486 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 615:
#line 2121 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3497 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 616:
#line 2126 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3507 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 617:
#line 2132 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3517 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 618:
#line 2136 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No config_control params are required
    // parsing completed
}
#line 3526 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 622:
#line 2150 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3537 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 623:
#line 2155 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3546 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 624:
#line 2165 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3557 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 625:
#line 2170 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3566 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 626:
#line 2175 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3576 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 627:
#line 2179 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 3584 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 631:
#line 2195 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3595 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 632:
#line 2200 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3604 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 635:
#line 2212 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3614 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 636:
#line 2216 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 3622 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 646:
#line 2233 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3631 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 647:
#line 2238 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3639 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 648:
#line 2240 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3649 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 649:
#line 2246 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3660 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 650:
#line 2251 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3669 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 653:
#line 2260 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3679 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 654:
#line 2264 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 3687 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 661:
#line 2278 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3695 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 662:
#line 2280 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3705 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 663:
#line 2286 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3714 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 664:
#line 2291 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3723 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 665:
#line 2296 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3732 "dhcp4_parser.cc" // lalr1.cc:919
    break;


#line 3736 "dhcp4_parser.cc" // lalr1.cc:919
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
  Dhcp4Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  Dhcp4Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const short Dhcp4Parser::yypact_ninf_ = -834;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     423,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,    46,    31,    24,    84,   137,
     147,   173,   180,   182,   184,   191,   207,   211,   221,   222,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,    31,  -100,
      20,    75,    29,   198,   126,    47,   116,    45,   165,   -47,
     346,   -33,    69,  -834,   103,   202,   226,   251,   258,  -834,
    -834,  -834,  -834,  -834,   263,  -834,    48,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,   264,   274,   285,  -834,
    -834,  -834,  -834,  -834,  -834,   286,   303,   323,   324,   336,
     340,   358,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,   365,  -834,  -834,  -834,  -834,
    -834,    56,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,   375,  -834,    74,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,   378,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,   105,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,   162,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,   262,   273,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,   385,  -834,
    -834,   390,  -834,  -834,  -834,   393,  -834,  -834,   392,   290,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,   394,   398,  -834,  -834,  -834,  -834,   397,
     363,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,   168,  -834,  -834,  -834,   404,  -834,  -834,
     407,  -834,   408,   409,  -834,  -834,   410,   412,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,   176,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,   178,  -834,  -834,  -834,   192,  -834,  -834,  -834,
      31,    31,  -834,   247,   414,   425,   426,   428,   430,  -834,
      20,  -834,   431,   436,   439,   277,   280,   281,   441,   442,
     443,   451,   456,   457,   296,   311,   312,   313,   315,   318,
     314,   480,   487,   494,   495,   497,   498,   499,   500,   503,
     504,   505,   506,   507,   341,   509,   510,   511,   513,    75,
    -834,   516,   521,   522,   354,    29,  -834,   525,   527,   528,
     530,   531,   532,   366,   534,   536,   538,   198,  -834,   539,
     126,  -834,   540,   541,   543,   544,   545,   546,   547,   548,
    -834,    47,  -834,   549,   551,   386,   554,   555,   557,   389,
    -834,    45,   559,   391,   395,  -834,   165,   561,   562,   -29,
    -834,   396,   563,   566,   400,   569,   405,   406,   571,   589,
     421,   422,   592,   593,   594,   595,   346,  -834,   -33,  -834,
     596,    69,  -834,  -834,  -834,   597,   598,   601,    31,    31,
      31,  -834,   602,   603,   604,  -834,  -834,  -834,   432,   433,
     444,   605,   606,   610,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,   446,   612,   613,   614,   615,   616,   452,   153,   619,
     620,   621,   622,   623,  -834,   624,   616,   625,   628,  -834,
     629,   102,   121,  -834,  -834,   458,   459,   465,   631,   467,
     468,  -834,   629,   469,   633,  -834,   471,  -834,   629,   472,
     473,   474,   475,   476,   477,   478,  -834,   479,   481,  -834,
     482,   483,   484,  -834,  -834,   485,  -834,  -834,  -834,   486,
      31,  -834,  -834,   488,   489,  -834,   490,  -834,  -834,    15,
     520,  -834,  -834,    71,   491,   492,   493,  -834,  -834,   645,
    -834,    31,    75,   -33,  -834,  -834,  -834,    69,    29,   641,
    -834,  -834,  -834,   272,   272,   658,  -834,   659,   660,   661,
     662,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,   233,
     663,   664,   665,   235,    43,  -834,   346,   666,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,   667,
    -834,  -834,  -834,  -834,    63,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,   658,  -834,
     213,   257,   266,   289,  -834,   298,  -834,  -834,  -834,  -834,
    -834,  -834,   617,   671,   672,   673,   674,  -834,  -834,  -834,
    -834,   675,   676,   677,   678,   679,  -834,   300,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,   301,  -834,
     680,   681,  -834,  -834,   682,   684,  -834,  -834,   683,   687,
    -834,  -834,   685,   689,  -834,  -834,   688,   690,  -834,  -834,
    -834,  -834,  -834,  -834,    42,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,    60,  -834,  -834,   691,   692,  -834,  -834,   693,
     695,  -834,   696,   697,   698,   699,   700,   701,   334,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,   335,  -834,  -834,  -834,   350,  -834,    86,  -834,   515,
    -834,   702,   703,  -834,  -834,  -834,  -834,   704,   705,  -834,
    -834,  -834,  -834,   706,   641,  -834,   709,   710,   711,   712,
     550,   523,   552,   553,   556,   713,   714,   715,   716,   558,
     560,   564,   565,   567,   272,  -834,  -834,   272,  -834,   658,
     198,  -834,   659,    45,  -834,   660,   165,  -834,   661,   437,
    -834,   662,   233,  -834,   204,   663,  -834,    47,  -834,   664,
     -47,  -834,   665,   568,   570,   572,   573,   574,   575,   235,
    -834,   718,   720,    43,  -834,  -834,   206,   666,  -834,  -834,
     719,   725,   126,  -834,   667,   726,  -834,  -834,   537,  -834,
     215,   577,   578,   579,  -834,  -834,  -834,  -834,  -834,   580,
     581,   582,   583,  -834,  -834,  -834,  -834,  -834,  -834,   353,
    -834,   356,  -834,   724,  -834,   729,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,   362,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,   730,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,   734,   735,  -834,  -834,  -834,  -834,
    -834,   746,  -834,   369,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,   585,   586,  -834,  -834,   753,  -834,  -834,  -834,
    -834,  -834,   377,  -834,  -834,  -834,  -834,  -834,  -834,   588,
     380,  -834,   629,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
     437,  -834,   755,   587,  -834,   204,  -834,  -834,  -834,  -834,
     757,   591,   759,   206,  -834,  -834,  -834,  -834,  -834,   599,
    -834,  -834,   728,  -834,   607,  -834,  -834,   758,  -834,  -834,
      92,  -834,     8,   758,  -834,  -834,   760,   762,   763,   388,
    -834,  -834,  -834,  -834,  -834,  -834,   764,   608,   600,   627,
       8,  -834,   626,  -834,  -834,  -834,  -834,  -834
  };

  const unsigned short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   135,     9,   278,    11,
     439,    13,   464,    15,   364,    17,   372,    19,   409,    21,
     243,    23,   556,    25,   626,    27,   617,    29,    47,    41,
       0,     0,     0,     0,     0,   466,     0,   374,   411,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     624,   609,   611,   613,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   615,   124,   150,     0,     0,     0,   485,
     487,   489,   148,   157,   159,     0,     0,     0,     0,     0,
       0,     0,   119,   270,   362,   401,   330,   452,   454,   323,
     221,   513,   456,   235,   254,     0,   539,   552,   554,   631,
     111,     0,    72,    74,    75,    76,   107,   108,   109,    77,
     105,    94,    95,    96,    80,    81,   102,    82,    83,    84,
      88,    89,    78,   106,    79,    86,    87,   100,   101,   103,
      97,    98,    99,    85,    90,    91,    92,    93,   104,   110,
     137,   139,   143,     0,   134,     0,   126,   128,   129,   130,
     131,   132,   133,   311,   313,   315,   431,   309,   317,     0,
     321,   319,   509,   308,   282,   283,   284,   305,   306,   307,
     295,   296,     0,   280,   287,   300,   301,   302,   288,   290,
     291,   293,   289,   285,   286,   303,   304,   292,   297,   298,
     299,   294,   450,   449,   445,   446,   444,     0,   441,   443,
     447,   448,   507,   495,   497,   501,   499,   505,   503,   491,
     484,   478,   482,   483,     0,   467,   468,   479,   480,   481,
     475,   470,   476,   472,   473,   474,   477,   471,     0,   391,
     202,     0,   395,   393,   398,     0,   387,   388,     0,   375,
     376,   378,   390,   379,   380,   381,   397,   382,   383,   384,
     385,   386,   425,     0,     0,   423,   424,   427,   428,     0,
     412,   413,   415,   416,   417,   418,   419,   420,   421,   422,
     250,   252,   247,     0,   245,   248,   249,     0,   579,   581,
       0,   584,     0,     0,   588,   592,     0,     0,   596,   603,
     605,   607,   577,   575,   576,     0,   558,   560,   561,   562,
     563,   564,   565,   566,   567,   568,   569,   570,   571,   572,
     573,   574,     0,   628,   630,   622,     0,   619,   621,    46,
       0,     0,    39,     0,     0,     0,     0,     0,     0,    57,
       0,    59,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      71,     0,     0,     0,     0,     0,   136,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   279,     0,
       0,   440,     0,     0,     0,     0,     0,     0,     0,     0,
     465,     0,   365,     0,     0,     0,     0,     0,     0,     0,
     373,     0,     0,     0,     0,   410,     0,     0,     0,     0,
     244,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   557,     0,   627,
       0,     0,   618,    50,    43,     0,     0,     0,     0,     0,
       0,    61,     0,     0,     0,   121,   122,   123,     0,     0,
       0,     0,     0,     0,   112,   113,   114,   115,   116,   117,
     118,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   538,     0,     0,     0,     0,    73,
       0,     0,     0,   147,   127,     0,     0,     0,     0,     0,
       0,   329,     0,     0,     0,   281,     0,   442,     0,     0,
       0,     0,     0,     0,     0,     0,   469,     0,     0,   389,
       0,     0,     0,   400,   377,     0,   429,   430,   414,     0,
       0,   246,   578,     0,     0,   583,     0,   586,   587,     0,
       0,   594,   595,     0,     0,     0,     0,   559,   629,     0,
     620,     0,     0,     0,   610,   612,   614,     0,     0,     0,
     486,   488,   490,     0,     0,   161,   120,   272,   366,   403,
     332,    40,   453,   455,   325,   326,   327,   328,   324,     0,
       0,   458,   237,     0,     0,   553,     0,     0,    51,   138,
     141,   142,   140,   145,   146,   144,   312,   314,   316,   433,
     310,   318,   322,   320,     0,   451,   508,   496,   498,   502,
     500,   506,   504,   492,   392,   203,   396,   394,   399,   426,
     251,   253,   580,   582,   585,   590,   591,   589,   593,   598,
     599,   600,   601,   602,   597,   604,   606,   608,   161,    44,
       0,     0,     0,     0,   155,     0,   152,   154,   189,   195,
     197,   199,     0,     0,     0,     0,     0,   211,   213,   215,
     217,     0,     0,     0,     0,     0,   188,     0,   167,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   182,
     183,   184,   179,   185,   186,   187,   180,   181,     0,   165,
       0,   162,   163,   276,     0,   273,   274,   370,     0,   367,
     368,   407,     0,   404,   405,   336,     0,   333,   334,   230,
     231,   232,   233,   234,     0,   223,   225,   226,   227,   228,
     229,   517,     0,   515,   462,     0,   459,   460,   241,     0,
     238,   239,     0,     0,     0,     0,     0,     0,     0,   256,
     258,   259,   260,   261,   262,   263,   548,   550,   547,   545,
     546,     0,   541,   543,   544,     0,   635,     0,   633,    53,
     437,     0,   434,   435,   493,   511,   512,     0,     0,    69,
     625,   616,   125,     0,     0,   151,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   149,   158,     0,   160,     0,
       0,   271,     0,   374,   363,     0,   411,   402,     0,     0,
     331,     0,     0,   222,   519,     0,   514,   466,   457,     0,
       0,   236,     0,     0,     0,     0,     0,     0,     0,     0,
     255,     0,     0,     0,   540,   555,     0,     0,   632,    55,
       0,    54,     0,   432,     0,     0,   510,   623,     0,   153,
       0,     0,     0,     0,   201,   204,   205,   206,   207,     0,
       0,     0,     0,   219,   220,   208,   209,   210,   168,     0,
     164,     0,   275,     0,   369,     0,   406,   361,   355,   343,
     344,   358,   359,   360,   346,   347,   340,   341,   342,   353,
     354,   352,     0,   338,   345,   356,   357,   348,   349,   350,
     351,   335,   224,   535,     0,   533,   534,   526,   527,   531,
     532,   528,   529,   530,     0,   520,   521,   523,   524,   525,
     516,     0,   461,     0,   240,   264,   265,   266,   267,   268,
     269,   257,     0,     0,   542,   649,     0,   647,   645,   639,
     643,   644,     0,   637,   641,   642,   640,   634,    52,     0,
       0,   436,     0,   156,   191,   192,   193,   194,   190,   196,
     198,   200,   212,   214,   216,   218,   166,   277,   371,   408,
       0,   337,     0,     0,   518,     0,   463,   242,   549,   551,
       0,     0,     0,     0,   636,    56,   438,   494,   339,     0,
     537,   522,     0,   646,     0,   638,   536,     0,   648,   653,
       0,   651,     0,     0,   650,   661,     0,     0,     0,     0,
     655,   657,   658,   659,   660,   652,     0,     0,     0,     0,
       0,   654,     0,   663,   664,   665,   656,   662
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,   -31,  -834,  -487,  -834,
     183,  -834,  -834,  -834,  -834,  -834,  -834,  -524,  -834,  -834,
    -834,   -70,  -834,  -834,  -834,   402,  -834,  -834,  -834,  -834,
     186,   374,   -54,   -24,    -5,    -4,    -1,    11,  -834,  -834,
    -834,  -834,    14,    17,  -834,  -834,   177,   370,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,   -22,  -834,  -834,  -834,  -834,  -834,
    -834,   115,  -834,   -38,  -834,  -589,   -35,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,   -36,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,   -48,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,   -51,
    -834,  -834,  -834,   -45,   349,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,   -50,  -834,  -834,  -834,  -834,  -834,  -834,  -833,
    -834,  -834,  -834,   -15,  -834,  -834,  -834,   -18,   401,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -832,  -834,    19,
    -834,    22,  -834,    21,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,     7,  -834,  -834,  -179,   -65,  -834,  -834,  -834,  -834,
    -834,   -12,  -834,  -834,  -834,     0,  -834,   418,  -834,   -72,
    -834,  -834,  -834,  -834,  -834,   -64,  -834,  -834,  -834,  -834,
    -834,   -40,  -834,  -834,  -834,    25,  -834,  -834,  -834,    26,
    -834,   419,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,   -19,  -834,  -834,  -834,    -6,   447,  -834,
    -834,   -52,  -834,   -20,  -834,   -60,  -834,  -834,  -834,    23,
    -834,  -834,  -834,    27,  -834,   438,    -8,  -834,    -2,  -834,
      10,  -834,   230,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -822,  -834,  -834,  -834,  -834,  -834,    28,  -834,  -834,  -834,
    -137,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,    12,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
     254,   411,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,
    -834,  -834,  -834,  -834,  -834,  -834,  -834,  -834,   284,   413,
    -834,  -834,  -834,  -834,  -834,  -834,   293,   415,   -69,  -834,
    -834,    13,  -834,  -834,  -135,  -834,  -834,  -834,  -834,  -834,
    -834,  -154,  -834,  -834,  -169,  -834,  -834,  -834,  -834,  -834
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     612,    87,    88,    41,    68,    84,    85,   629,   799,   880,
     881,   706,    43,    70,    96,    97,    98,   364,    45,    71,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     391,   151,   152,   153,   154,   373,   185,   186,    47,    72,
     187,   411,   188,   412,   632,   189,   413,   635,   190,   155,
     381,   156,   374,   685,   686,   687,   813,   157,   382,   158,
     383,   730,   731,   732,   837,   707,   708,   709,   816,   998,
     710,   817,   711,   818,   712,   819,   713,   714,   444,   715,
     716,   717,   718,   719,   720,   721,   722,   825,   723,   826,
     724,   827,   725,   828,   726,   727,   159,   399,   754,   755,
     756,   757,   758,   759,   760,   160,   402,   769,   770,   771,
     860,    61,    79,   313,   314,   315,   457,   316,   458,   161,
     403,   778,   779,   780,   781,   782,   783,   784,   785,   162,
     392,   734,   735,   736,   840,    49,    73,   212,   213,   214,
     421,   215,   417,   216,   418,   217,   419,   218,   422,   219,
     425,   220,   424,   163,   398,   618,   222,   164,   395,   746,
     747,   748,   849,   932,   933,   165,   393,    55,    76,   738,
     739,   740,   843,    57,    77,   278,   279,   280,   281,   282,
     283,   284,   443,   285,   447,   286,   446,   287,   288,   448,
     289,   166,   394,   742,   743,   744,   846,    59,    78,   299,
     300,   301,   302,   303,   452,   304,   305,   306,   307,   224,
     420,   801,   802,   803,   882,    51,    74,   237,   238,   239,
     429,   167,   396,   168,   397,   169,   401,   765,   766,   767,
     857,    53,    75,   254,   255,   256,   170,   378,   171,   379,
     172,   380,   260,   439,   806,   885,   261,   433,   262,   434,
     263,   436,   264,   435,   265,   438,   266,   437,   267,   432,
     231,   426,   807,   173,   400,   762,   763,   854,   954,   955,
     956,   957,   958,  1012,   959,   174,   175,   405,   791,   792,
     793,   871,   794,   872,   176,   406,   177,   407,    63,    80,
     335,   336,   337,   338,   462,   339,   463,   340,   341,   465,
     342,   343,   344,   468,   667,   345,   469,   346,   347,   348,
     472,   674,   349,   473,   350,   474,   351,   475,    99,   366,
     100,   367,   101,   368,   178,   372,    67,    82,   356,   357,
     358,   480,   102,   365,    65,    81,   352,   353,   179,   408,
     797,   798,   876,   982,   983,   984,   985,  1022,   986,  1020,
    1040,  1041,  1042,  1049,  1050,  1051,  1056,  1052,  1053,  1054
  };

  const unsigned short
  Dhcp4Parser::yytable_[] =
  {
      95,   140,   184,   203,   233,   250,   297,   276,   295,   312,
     332,   268,   354,   227,   298,   728,   927,   928,   642,   204,
     191,   225,   240,   252,   646,   290,   308,   940,   333,   611,
      89,    42,   665,   223,   236,   251,    31,    83,    32,   611,
      33,   277,   296,   180,   181,   852,    30,   182,   853,   205,
     183,   370,   192,   226,   241,   253,   371,   291,   309,   409,
     334,   310,   311,   855,   410,   228,   856,   257,   206,   207,
      86,   229,   208,   258,   109,   110,   111,   415,   269,   310,
     311,   355,   416,   230,   209,   259,   103,   210,   104,   877,
     211,    44,   878,   234,   221,  1043,   235,   105,  1044,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   427,   359,
     127,   128,   139,   428,   270,   125,   271,   272,   630,   631,
     273,   274,   275,    94,   127,   128,   127,   128,   127,   128,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   242,
     633,   634,   124,   125,    46,   243,   244,   245,   246,   247,
     248,   666,   249,   126,    48,  1045,   127,   128,  1046,  1047,
    1048,   129,   786,   787,    90,   430,   130,   131,   249,   804,
     431,   459,   132,    91,    92,    93,   460,   927,   928,   476,
      50,   478,   133,   124,   477,   134,   479,    52,   940,    54,
      94,    56,   135,   136,   125,   481,   137,   138,    58,    94,
     482,    34,    35,    36,    37,   360,   232,   127,   128,   669,
     670,   671,   672,    94,    60,    94,   409,    94,    62,   200,
     139,   809,   201,   107,   108,   109,   110,   111,    64,    66,
     361,   109,   110,   111,   270,   292,   271,   272,   293,   294,
     614,   615,   616,   617,   673,    94,   127,   128,   909,   994,
     995,   996,   997,   115,   116,   117,   118,   119,   120,   362,
     478,   363,   193,   194,   195,   810,   125,   369,   375,   481,
     440,   124,   125,   270,   811,   270,   441,   196,   376,   127,
     128,   197,   198,   199,   129,   127,   128,   127,   128,   377,
     384,   200,   415,   451,   201,   132,    94,   812,   943,   944,
      95,   814,   202,   834,   834,   688,   815,   385,   835,   836,
     689,   690,   691,   692,   693,   694,   695,   696,   697,   698,
     699,   700,   701,   702,   703,   704,   705,   386,   387,   483,
     484,   749,   750,   751,   752,    94,   753,   869,   873,   140,
     388,   270,   870,   874,   389,   184,   772,   773,   774,   775,
     776,   777,   975,   476,   976,   977,   834,   203,   875,   427,
     233,  1006,   390,   191,  1007,  1010,   456,   227,    94,   404,
    1011,   250,   459,   204,    94,   225,    94,  1017,   240,   414,
    1023,   276,   423,   430,   297,  1024,   295,   223,  1026,   252,
     236,  1060,   298,   442,   445,   192,  1061,   449,   453,   290,
     450,   251,   454,   205,   308,   455,   332,   226,   461,   354,
     241,   464,   466,   467,   470,   277,   471,   485,   486,   228,
     296,   253,   206,   207,   333,   229,   208,   127,   128,   487,
     488,   291,   489,   257,   490,   492,   309,   230,   209,   258,
     493,   210,    94,   494,   211,   498,   499,   500,   221,   234,
     495,   259,   235,   496,   497,   501,   334,   594,   595,   596,
     502,   503,   107,   108,   109,   110,   111,   504,  1027,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   505,   506,   511,   510,   507,   508,   330,   331,
     509,   512,   115,   116,   117,   118,   119,   120,   513,   514,
     123,   515,   516,   517,   518,   125,   270,   519,   520,   521,
     522,   523,   524,   525,   526,   527,    94,   528,   127,   128,
     530,   198,   140,   129,   354,   531,   532,   533,   184,   535,
     200,   536,   537,   201,   538,   539,   540,   541,   542,   661,
     543,   202,   544,   546,   548,   549,   191,   550,   551,   552,
     553,   554,   555,   557,   788,   558,   332,   559,   560,   561,
     679,   562,   563,   565,   566,   569,   570,   573,   567,   572,
     574,   575,   789,   576,   333,   579,   577,   578,   192,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,   580,   581,   582,   583,   584,   585,   586,
     589,   591,   600,   601,   790,   592,   334,    94,   593,   597,
     598,   599,   603,   604,   602,   605,   606,   607,   608,   609,
     610,   820,   613,    32,   619,   620,   621,   622,   636,   637,
     623,   624,   626,   627,   628,   638,   639,   640,   641,   643,
     644,   645,   647,   648,   649,   650,   651,   652,   653,   654,
     678,   655,   656,   657,   658,   659,   660,   668,   662,   663,
     664,   675,   676,   677,   684,   729,   733,   737,   741,   745,
     761,   764,   768,   796,   800,   821,   822,   823,   824,   829,
     830,   831,   832,   833,   839,   879,   838,   842,   841,   844,
     845,   847,   848,   851,   850,   859,   895,   858,   862,   861,
     863,   864,   865,   866,   867,   868,   884,   993,   883,   625,
     888,   887,   886,   890,   891,   892,   893,   899,   900,   901,
     902,   894,   972,   896,   973,   988,   897,   898,   989,   903,
     992,   904,  1008,  1037,  1013,   905,   906,  1009,  1015,   965,
     907,   966,  1014,   967,   968,   969,   970,   999,  1000,  1001,
    1002,  1003,  1004,  1005,  1016,  1018,  1019,  1021,  1025,  1029,
    1030,  1032,  1033,  1034,  1057,  1039,  1058,  1059,  1062,  1036,
     203,  1064,   491,   276,   297,   683,   295,  1038,   680,   917,
     227,  1063,   298,   529,   945,   534,   204,   250,   225,   947,
     312,   290,   889,   808,   308,   918,  1067,   935,  1065,   908,
     223,   910,   949,   788,   942,   252,   978,   277,   571,   934,
     296,   964,   233,   926,   948,   963,   205,   251,   946,   971,
     226,   789,   911,   291,   980,   919,   309,   912,   545,   936,
     240,  1028,   228,   914,   950,   206,   207,   253,   229,   208,
     979,   937,   236,   913,   920,   921,   951,   938,   922,   257,
     230,   209,   952,   790,   210,   258,   981,   211,   941,   939,
     923,   221,   241,   924,   953,   991,   925,   259,   929,   564,
     931,   930,   915,   916,   805,   568,   990,   547,  1031,   556,
     795,   682,   962,   960,   961,   974,   681,   587,  1035,  1055,
     987,  1066,     0,   588,   590,     0,     0,     0,     0,     0,
       0,   234,     0,     0,   235,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     917,     0,     0,     0,     0,   945,     0,     0,     0,     0,
     947,     0,     0,   978,     0,     0,   918,     0,   935,     0,
       0,     0,     0,   949,     0,     0,     0,     0,     0,     0,
     934,   980,     0,     0,   926,   948,     0,     0,     0,   946,
       0,     0,     0,     0,     0,     0,   919,   979,     0,     0,
     936,     0,     0,     0,     0,   950,     0,     0,     0,     0,
       0,     0,   937,   981,     0,   920,   921,   951,   938,   922,
       0,     0,     0,   952,     0,     0,     0,     0,     0,     0,
     939,   923,     0,     0,   924,   953,     0,   925,     0,   929,
       0,   931,   930
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    78,    77,    78,    79,
      80,    76,    81,    73,    78,   604,   849,   849,   542,    73,
      72,    73,    74,    75,   548,    77,    78,   849,    80,   516,
      10,     7,    17,    73,    74,    75,     5,    68,     7,   526,
       9,    77,    78,    14,    15,     3,     0,    18,     6,    73,
      21,     3,    72,    73,    74,    75,     8,    77,    78,     3,
      80,   108,   109,     3,     8,    73,     6,    75,    73,    73,
     170,    73,    73,    75,    27,    28,    29,     3,    33,   108,
     109,    12,     8,    73,    73,    75,    11,    73,    13,     3,
      73,     7,     6,    74,    73,     3,    74,    22,     6,    24,
      25,    26,    27,    28,    29,    30,    31,    32,     3,     6,
      81,    82,   145,     8,    69,    68,    71,    72,    16,    17,
      75,    76,    77,   170,    81,    82,    81,    82,    81,    82,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    92,
      19,    20,    67,    68,     7,    98,    99,   100,   101,   102,
     103,   136,   105,    78,     7,   147,    81,    82,   150,   151,
     152,    86,   119,   120,   144,     3,    91,    92,   105,   106,
       8,     3,    97,   153,   154,   155,     8,  1010,  1010,     3,
       7,     3,   107,    67,     8,   110,     8,     7,  1010,     7,
     170,     7,   117,   118,    68,     3,   121,   122,     7,   170,
       8,   170,   171,   172,   173,     3,    80,    81,    82,   138,
     139,   140,   141,   170,     7,   170,     3,   170,     7,    93,
     145,     8,    96,    25,    26,    27,    28,    29,     7,     7,
       4,    27,    28,    29,    69,    70,    71,    72,    73,    74,
      87,    88,    89,    90,   173,   170,    81,    82,   837,    34,
      35,    36,    37,    55,    56,    57,    58,    59,    60,     8,
       3,     3,    64,    65,    66,     8,    68,     4,     4,     3,
       8,    67,    68,    69,     8,    69,     3,    79,     4,    81,
      82,    83,    84,    85,    86,    81,    82,    81,    82,     4,
       4,    93,     3,     3,    96,    97,   170,     8,    94,    95,
     370,     3,   104,     3,     3,    33,     8,     4,     8,     8,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,     4,     4,   360,
     361,    98,    99,   100,   101,   170,   103,     3,     3,   409,
       4,    69,     8,     8,     4,   415,   111,   112,   113,   114,
     115,   116,   146,     3,   148,   149,     3,   427,     8,     3,
     430,     8,     4,   415,     8,     3,     3,   427,   170,     4,
       8,   441,     3,   427,   170,   427,   170,     8,   430,     4,
       3,   451,     4,     3,   456,     8,   456,   427,     8,   441,
     430,     3,   456,     8,     4,   415,     8,     4,     4,   451,
       8,   441,     4,   427,   456,     8,   476,   427,     4,   478,
     430,     4,     4,     4,     4,   451,     4,   170,     4,   427,
     456,   441,   427,   427,   476,   427,   427,    81,    82,     4,
       4,   451,     4,   441,     4,     4,   456,   427,   427,   441,
       4,   427,   170,     4,   427,     4,     4,     4,   427,   430,
     173,   441,   430,   173,   173,     4,   476,   488,   489,   490,
       4,     4,    25,    26,    27,    28,    29,   171,   992,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   171,   171,     4,   171,   173,   172,   142,   143,
     172,     4,    55,    56,    57,    58,    59,    60,     4,     4,
      63,     4,     4,     4,     4,    68,    69,     4,     4,     4,
       4,     4,   171,     4,     4,     4,   170,     4,    81,    82,
       4,    84,   592,    86,   593,     4,     4,   173,   598,     4,
      93,     4,     4,    96,     4,     4,     4,   171,     4,   570,
       4,   104,     4,     4,     4,     4,   598,     4,     4,     4,
       4,     4,     4,     4,   624,     4,   626,   171,     4,     4,
     591,     4,   173,     4,   173,     4,     4,     4,   173,   173,
       4,   171,   624,     4,   626,     4,   171,   171,   598,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,     4,   173,   173,     4,     4,     4,     4,
       4,     4,   170,   170,   624,     7,   626,   170,     7,     7,
       7,     7,     7,     7,   170,     5,   170,     5,     5,     5,
       5,     4,   170,     7,     5,     5,     5,     5,   170,   170,
       7,     7,     7,     5,     5,   170,     5,   170,   170,   170,
       7,   170,   170,   170,   170,   170,   170,   170,   170,   170,
       5,   170,   170,   170,   170,   170,   170,   137,   170,   170,
     170,   170,   170,   170,    23,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     3,   170,     6,     3,     6,     6,
       3,     6,     3,     3,     6,     3,   173,     6,     3,     6,
       4,     4,     4,     4,     4,     4,     3,   170,     6,   526,
       4,     6,     8,     4,     4,     4,     4,     4,     4,     4,
       4,   171,     4,   171,     4,     6,   173,   171,     3,   171,
       4,   171,     8,     5,     4,   171,   171,     8,     3,   171,
     173,   171,     8,   171,   171,   171,   171,   170,   170,   170,
     170,   170,   170,   170,     8,   170,   170,     4,   170,     4,
     173,     4,   171,     4,     4,     7,     4,     4,     4,   170,
     840,   171,   370,   843,   846,   598,   846,   170,   592,   849,
     840,   173,   846,   409,   854,   415,   840,   857,   840,   854,
     860,   843,   814,   678,   846,   849,   170,   849,   171,   834,
     840,   839,   854,   873,   852,   857,   876,   843,   459,   849,
     846,   862,   882,   849,   854,   860,   840,   857,   854,   869,
     840,   873,   840,   843,   876,   849,   846,   842,   427,   849,
     882,  1010,   840,   845,   854,   840,   840,   857,   840,   840,
     876,   849,   882,   843,   849,   849,   854,   849,   849,   857,
     840,   840,   854,   873,   840,   857,   876,   840,   851,   849,
     849,   840,   882,   849,   854,   884,   849,   857,   849,   451,
     849,   849,   846,   848,   644,   456,   882,   430,  1015,   441,
     626,   597,   859,   855,   857,   873,   593,   476,  1023,  1043,
     877,  1060,    -1,   478,   481,    -1,    -1,    -1,    -1,    -1,
      -1,   882,    -1,    -1,   882,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1010,    -1,    -1,    -1,    -1,  1015,    -1,    -1,    -1,    -1,
    1015,    -1,    -1,  1023,    -1,    -1,  1010,    -1,  1010,    -1,
      -1,    -1,    -1,  1015,    -1,    -1,    -1,    -1,    -1,    -1,
    1010,  1023,    -1,    -1,  1010,  1015,    -1,    -1,    -1,  1015,
      -1,    -1,    -1,    -1,    -1,    -1,  1010,  1023,    -1,    -1,
    1010,    -1,    -1,    -1,    -1,  1015,    -1,    -1,    -1,    -1,
      -1,    -1,  1010,  1023,    -1,  1010,  1010,  1015,  1010,  1010,
      -1,    -1,    -1,  1015,    -1,    -1,    -1,    -1,    -1,    -1,
    1010,  1010,    -1,    -1,  1010,  1015,    -1,  1010,    -1,  1010,
      -1,  1010,  1010
  };

  const unsigned short
  Dhcp4Parser::yystos_[] =
  {
       0,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
       0,     5,     7,     9,   170,   171,   172,   173,   190,   191,
     192,   197,     7,   206,     7,   212,     7,   232,     7,   329,
       7,   409,     7,   425,     7,   361,     7,   367,     7,   391,
       7,   305,     7,   482,     7,   528,     7,   520,   198,   193,
     207,   213,   233,   330,   410,   426,   362,   368,   392,   306,
     483,   529,   521,   190,   199,   200,   170,   195,   196,    10,
     144,   153,   154,   155,   170,   205,   208,   209,   210,   512,
     514,   516,   526,    11,    13,    22,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    67,    68,    78,    81,    82,    86,
      91,    92,    97,   107,   110,   117,   118,   121,   122,   145,
     205,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   225,   226,   227,   228,   243,   245,   251,   253,   290,
     299,   313,   323,   347,   351,   359,   385,   415,   417,   419,
     430,   432,   434,   457,   469,   470,   478,   480,   518,   532,
      14,    15,    18,    21,   205,   230,   231,   234,   236,   239,
     242,   415,   417,    64,    65,    66,    79,    83,    84,    85,
      93,    96,   104,   205,   216,   217,   218,   219,   220,   221,
     226,   227,   331,   332,   333,   335,   337,   339,   341,   343,
     345,   347,   350,   385,   403,   415,   417,   419,   430,   432,
     434,   454,    80,   205,   343,   345,   385,   411,   412,   413,
     415,   417,    92,    98,    99,   100,   101,   102,   103,   105,
     205,   385,   415,   417,   427,   428,   429,   430,   432,   434,
     436,   440,   442,   444,   446,   448,   450,   452,   359,    33,
      69,    71,    72,    75,    76,    77,   205,   271,   369,   370,
     371,   372,   373,   374,   375,   377,   379,   381,   382,   384,
     415,   417,    70,    73,    74,   205,   271,   373,   379,   393,
     394,   395,   396,   397,   399,   400,   401,   402,   415,   417,
     108,   109,   205,   307,   308,   309,   311,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     142,   143,   205,   415,   417,   484,   485,   486,   487,   489,
     491,   492,   494,   495,   496,   499,   501,   502,   503,   506,
     508,   510,   530,   531,   532,    12,   522,   523,   524,     6,
       3,     4,     8,     3,   211,   527,   513,   515,   517,     4,
       3,     8,   519,   229,   246,     4,     4,     4,   431,   433,
     435,   244,   252,   254,     4,     4,     4,     4,     4,     4,
       4,   224,   324,   360,   386,   352,   416,   418,   348,   291,
     458,   420,   300,   314,     4,   471,   479,   481,   533,     3,
       8,   235,   237,   240,     4,     3,     8,   336,   338,   340,
     404,   334,   342,     4,   346,   344,   455,     3,     8,   414,
       3,     8,   453,   441,   443,   447,   445,   451,   449,   437,
       8,     3,     8,   376,   272,     4,   380,   378,   383,     4,
       8,     3,   398,     4,     4,     8,     3,   310,   312,     3,
       8,     4,   488,   490,     4,   493,     4,     4,   497,   500,
       4,     4,   504,   507,   509,   511,     3,     8,     3,     8,
     525,     3,     8,   190,   190,   170,     4,     4,     4,     4,
       4,   209,     4,     4,     4,   173,   173,   173,     4,     4,
       4,     4,     4,     4,   171,   171,   171,   173,   172,   172,
     171,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   171,     4,     4,     4,     4,   215,
       4,     4,     4,   173,   231,     4,     4,     4,     4,     4,
       4,   171,     4,     4,     4,   332,     4,   412,     4,     4,
       4,     4,     4,     4,     4,     4,   429,     4,     4,   171,
       4,     4,     4,   173,   371,     4,   173,   173,   395,     4,
       4,   308,   173,     4,     4,   171,     4,   171,   171,     4,
       4,   173,   173,     4,     4,     4,     4,   485,   531,     4,
     523,     4,     7,     7,   190,   190,   190,     7,     7,     7,
     170,   170,   170,     7,     7,     5,   170,     5,     5,     5,
       5,   192,   194,   170,    87,    88,    89,    90,   349,     5,
       5,     5,     5,     7,     7,   194,     7,     5,     5,   201,
      16,    17,   238,    19,    20,   241,   170,   170,   170,     5,
     170,   170,   201,   170,     7,   170,   201,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   190,   170,   170,   170,    17,   136,   498,   137,   138,
     139,   140,   141,   173,   505,   170,   170,   170,     5,   190,
     214,   530,   522,   230,    23,   247,   248,   249,    33,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,   205,   259,   260,   261,
     264,   266,   268,   270,   271,   273,   274,   275,   276,   277,
     278,   279,   280,   282,   284,   286,   288,   289,   259,     7,
     255,   256,   257,     7,   325,   326,   327,     7,   363,   364,
     365,     7,   387,   388,   389,     7,   353,   354,   355,    98,
      99,   100,   101,   103,   292,   293,   294,   295,   296,   297,
     298,     7,   459,   460,     7,   421,   422,   423,     7,   301,
     302,   303,   111,   112,   113,   114,   115,   116,   315,   316,
     317,   318,   319,   320,   321,   322,   119,   120,   205,   415,
     417,   472,   473,   474,   476,   484,     7,   534,   535,   202,
       7,   405,   406,   407,   106,   436,   438,   456,   255,     8,
       8,     8,     8,   250,     3,     8,   262,   265,   267,   269,
       4,     4,     4,     4,     4,   281,   283,   285,   287,     4,
       4,     4,     4,     4,     3,     8,     8,   258,     6,     3,
     328,     6,     3,   366,     6,     3,   390,     6,     3,   356,
       6,     3,     3,     6,   461,     3,     6,   424,     6,     3,
     304,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,   475,   477,     3,     8,     8,   536,     3,     6,   170,
     203,   204,   408,     6,     3,   439,     8,     6,     4,   248,
       4,     4,     4,     4,   171,   173,   171,   173,   171,     4,
       4,     4,     4,   171,   171,   171,   171,   173,   260,   259,
     257,   331,   327,   369,   365,   393,   389,   205,   216,   217,
     218,   219,   220,   221,   226,   227,   271,   323,   341,   343,
     345,   347,   357,   358,   385,   415,   417,   430,   432,   434,
     454,   355,   293,    94,    95,   205,   271,   359,   385,   415,
     417,   430,   432,   434,   462,   463,   464,   465,   466,   468,
     460,   427,   423,   307,   303,   171,   171,   171,   171,   171,
     171,   316,     4,     4,   473,   146,   148,   149,   205,   271,
     415,   417,   537,   538,   539,   540,   542,   535,     6,     3,
     411,   407,     4,   170,    34,    35,    36,    37,   263,   170,
     170,   170,   170,   170,   170,   170,     8,     8,     8,     8,
       3,     8,   467,     4,     8,     3,     8,     8,   170,   170,
     543,     4,   541,     3,     8,   170,     8,   201,   358,     4,
     173,   464,     4,   171,     4,   538,   170,     5,   170,     7,
     544,   545,   546,     3,     6,   147,   150,   151,   152,   547,
     548,   549,   551,   552,   553,   545,   550,     4,     4,     4,
       3,     8,     4,   173,   171,   171,   548,   170
  };

  const unsigned short
  Dhcp4Parser::yyr1_[] =
  {
       0,   174,   176,   175,   177,   175,   178,   175,   179,   175,
     180,   175,   181,   175,   182,   175,   183,   175,   184,   175,
     185,   175,   186,   175,   187,   175,   188,   175,   189,   175,
     190,   190,   190,   190,   190,   190,   190,   191,   193,   192,
     194,   195,   195,   196,   196,   198,   197,   199,   199,   200,
     200,   202,   201,   203,   203,   204,   204,   205,   207,   206,
     208,   208,   209,   209,   209,   209,   209,   209,   211,   210,
     213,   212,   214,   214,   215,   215,   215,   215,   215,   215,
     215,   215,   215,   215,   215,   215,   215,   215,   215,   215,
     215,   215,   215,   215,   215,   215,   215,   215,   215,   215,
     215,   215,   215,   215,   215,   215,   215,   215,   215,   215,
     215,   215,   216,   217,   218,   219,   220,   221,   222,   224,
     223,   225,   226,   227,   229,   228,   230,   230,   231,   231,
     231,   231,   231,   231,   231,   233,   232,   235,   234,   237,
     236,   238,   238,   240,   239,   241,   241,   242,   244,   243,
     246,   245,   247,   247,   248,   250,   249,   252,   251,   254,
     253,   255,   255,   256,   256,   258,   257,   259,   259,   260,
     260,   260,   260,   260,   260,   260,   260,   260,   260,   260,
     260,   260,   260,   260,   260,   260,   260,   260,   260,   262,
     261,   263,   263,   263,   263,   265,   264,   267,   266,   269,
     268,   270,   272,   271,   273,   274,   275,   276,   277,   278,
     279,   281,   280,   283,   282,   285,   284,   287,   286,   288,
     289,   291,   290,   292,   292,   293,   293,   293,   293,   293,
     294,   295,   296,   297,   298,   300,   299,   301,   301,   302,
     302,   304,   303,   306,   305,   307,   307,   307,   308,   308,
     310,   309,   312,   311,   314,   313,   315,   315,   316,   316,
     316,   316,   316,   316,   317,   318,   319,   320,   321,   322,
     324,   323,   325,   325,   326,   326,   328,   327,   330,   329,
     331,   331,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   332,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   332,   332,   332,   332,   332,   332,   332,   332,   334,
     333,   336,   335,   338,   337,   340,   339,   342,   341,   344,
     343,   346,   345,   348,   347,   349,   349,   349,   349,   350,
     352,   351,   353,   353,   354,   354,   356,   355,   357,   357,
     358,   358,   358,   358,   358,   358,   358,   358,   358,   358,
     358,   358,   358,   358,   358,   358,   358,   358,   358,   358,
     358,   358,   360,   359,   362,   361,   363,   363,   364,   364,
     366,   365,   368,   367,   369,   369,   370,   370,   371,   371,
     371,   371,   371,   371,   371,   371,   371,   371,   372,   373,
     374,   376,   375,   378,   377,   380,   379,   381,   383,   382,
     384,   386,   385,   387,   387,   388,   388,   390,   389,   392,
     391,   393,   393,   394,   394,   395,   395,   395,   395,   395,
     395,   395,   395,   395,   396,   398,   397,   399,   400,   401,
     402,   404,   403,   405,   405,   406,   406,   408,   407,   410,
     409,   411,   411,   412,   412,   412,   412,   412,   412,   412,
     414,   413,   416,   415,   418,   417,   420,   419,   421,   421,
     422,   422,   424,   423,   426,   425,   427,   427,   428,   428,
     429,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   429,   431,   430,   433,   432,   435,
     434,   437,   436,   439,   438,   441,   440,   443,   442,   445,
     444,   447,   446,   449,   448,   451,   450,   453,   452,   455,
     454,   456,   456,   458,   457,   459,   459,   461,   460,   462,
     462,   463,   463,   464,   464,   464,   464,   464,   464,   464,
     464,   464,   464,   464,   465,   467,   466,   468,   469,   471,
     470,   472,   472,   473,   473,   473,   473,   473,   475,   474,
     477,   476,   479,   478,   481,   480,   483,   482,   484,   484,
     485,   485,   485,   485,   485,   485,   485,   485,   485,   485,
     485,   485,   485,   485,   485,   485,   485,   485,   486,   488,
     487,   490,   489,   491,   493,   492,   494,   495,   497,   496,
     498,   498,   500,   499,   501,   502,   504,   503,   505,   505,
     505,   505,   505,   507,   506,   509,   508,   511,   510,   513,
     512,   515,   514,   517,   516,   519,   518,   521,   520,   522,
     522,   523,   525,   524,   527,   526,   529,   528,   530,   530,
     531,   533,   532,   534,   534,   536,   535,   537,   537,   538,
     538,   538,   538,   538,   538,   538,   539,   541,   540,   543,
     542,   544,   544,   546,   545,   547,   547,   548,   548,   548,
     548,   550,   549,   551,   552,   553
  };

  const unsigned char
  Dhcp4Parser::yyr2_[] =
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     0,
       4,     3,     3,     3,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     1,     1,     0,     4,     1,     1,     3,     0,     6,
       0,     6,     1,     3,     1,     0,     4,     0,     6,     0,
       6,     0,     1,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     3,     3,     3,     3,
       3,     0,     4,     0,     4,     0,     4,     0,     4,     3,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     1,     1,     1,     1,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     6,     0,     4,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     0,     4,     0,     4,     0,     4,     1,     0,     4,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     1,     0,     6,     1,     3,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     3,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     0,     4,
       1,     1,     0,     4,     3,     3,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     0,     6,     0,     6,     0,     4,     1,     3,
       1,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     0,     4,     3,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp4Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp4\"", "\"config-control\"",
  "\"config-databases\"", "\"interfaces-config\"", "\"interfaces\"",
  "\"dhcp-socket-type\"", "\"raw\"", "\"udp\"", "\"outbound-interface\"",
  "\"same-as-inbound\"", "\"use-routing\"", "\"re-detect\"",
  "\"sanity-checks\"", "\"lease-checks\"", "\"echo-client-id\"",
  "\"match-client-id\"", "\"authoritative\"", "\"next-server\"",
  "\"server-hostname\"", "\"boot-file-name\"", "\"lease-database\"",
  "\"hosts-database\"", "\"hosts-databases\"", "\"type\"", "\"memfile\"",
  "\"mysql\"", "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"",
  "\"host\"", "\"port\"", "\"persist\"", "\"lfc-interval\"",
  "\"readonly\"", "\"connect-timeout\"", "\"contact-points\"",
  "\"keyspace\"", "\"consistency\"", "\"serial-consistency\"",
  "\"max-reconnect-tries\"", "\"reconnect-wait-time\"",
  "\"request-timeout\"", "\"tcp-keepalive\"", "\"tcp-nodelay\"",
  "\"valid-lifetime\"", "\"renew-timer\"", "\"rebind-timer\"",
  "\"calculate-tee-times\"", "\"t1-percent\"", "\"t2-percent\"",
  "\"decline-probation-period\"", "\"server-tag\"", "\"subnet4\"",
  "\"4o6-interface\"", "\"4o6-interface-id\"", "\"4o6-subnet\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"shared-networks\"", "\"pools\"",
  "\"pool\"", "\"user-context\"", "\"comment\"", "\"subnet\"",
  "\"interface\"", "\"id\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"global\"", "\"all\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"",
  "\"require-client-classes\"", "\"test\"", "\"only-if-required\"",
  "\"client-class\"", "\"reservations\"", "\"duid\"", "\"hw-address\"",
  "\"circuit-id\"", "\"client-id\"", "\"hostname\"", "\"flex-id\"",
  "\"relay\"", "\"ip-address\"", "\"ip-addresses\"", "\"hooks-libraries\"",
  "\"library\"", "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"",
  "\"dhcp4o6-port\"", "\"control-socket\"", "\"socket-type\"",
  "\"socket-name\"", "\"dhcp-queue-control\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"tcp\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"hostname-char-set\"", "\"hostname-char-replacement\"", "\"Logging\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"Dhcp6\"",
  "\"DhcpDdns\"", "\"Control-agent\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP4",
  "SUB_DHCP4", "SUB_INTERFACES4", "SUB_SUBNET4", "SUB_POOL4",
  "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "SUB_LOGGING",
  "SUB_CONFIG_CONTROL", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "$@14", "value", "sub_json", "map2", "$@15", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@16", "list_content",
  "not_empty_list", "list_strings", "$@17", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@18",
  "global_objects", "global_object", "dhcp4_object", "$@19", "sub_dhcp4",
  "$@20", "global_params", "global_param", "valid_lifetime", "renew_timer",
  "rebind_timer", "calculate_tee_times", "t1_percent", "t2_percent",
  "decline_probation_period", "server_tag", "$@21", "echo_client_id",
  "match_client_id", "authoritative", "interfaces_config", "$@22",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@23", "interfaces_list", "$@24", "dhcp_socket_type", "$@25",
  "socket_type", "outbound_interface", "$@26", "outbound_interface_value",
  "re_detect", "lease_database", "$@27", "sanity_checks", "$@28",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@29",
  "hosts_database", "$@30", "hosts_databases", "$@31", "database_list",
  "not_empty_database_list", "database", "$@32", "database_map_params",
  "database_map_param", "database_type", "$@33", "db_type", "user", "$@34",
  "password", "$@35", "host", "$@36", "port", "name", "$@37", "persist",
  "lfc_interval", "readonly", "connect_timeout", "request_timeout",
  "tcp_keepalive", "tcp_nodelay", "contact_points", "$@38", "keyspace",
  "$@39", "consistency", "$@40", "serial_consistency", "$@41",
  "max_reconnect_tries", "reconnect_wait_time",
  "host_reservation_identifiers", "$@42",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@43", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@44",
  "sub_hooks_library", "$@45", "hooks_params", "hooks_param", "library",
  "$@46", "parameters", "$@47", "expired_leases_processing", "$@48",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@49",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@50",
  "sub_subnet4", "$@51", "subnet4_params", "subnet4_param", "subnet",
  "$@52", "subnet_4o6_interface", "$@53", "subnet_4o6_interface_id",
  "$@54", "subnet_4o6_subnet", "$@55", "interface", "$@56", "client_class",
  "$@57", "require_client_classes", "$@58", "reservation_mode", "$@59",
  "hr_mode", "id", "shared_networks", "$@60", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@61",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@62", "sub_option_def_list", "$@63", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@64",
  "sub_option_def", "$@65", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@66",
  "option_def_record_types", "$@67", "space", "$@68", "option_def_space",
  "option_def_encapsulate", "$@69", "option_def_array", "option_data_list",
  "$@70", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@71", "sub_option_data", "$@72",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@73",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@74", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@75", "sub_pool4", "$@76",
  "pool_params", "pool_param", "pool_entry", "$@77", "user_context",
  "$@78", "comment", "$@79", "reservations", "$@80", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@81", "sub_reservation",
  "$@82", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@83", "server_hostname", "$@84",
  "boot_file_name", "$@85", "ip_address", "$@86", "ip_addresses", "$@87",
  "duid", "$@88", "hw_address", "$@89", "client_id_value", "$@90",
  "circuit_id_value", "$@91", "flex_id_value", "$@92", "hostname", "$@93",
  "reservation_client_classes", "$@94", "relay", "$@95", "relay_map",
  "client_classes", "$@96", "client_classes_list", "client_class_entry",
  "$@97", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@98",
  "only_if_required", "dhcp4o6_port", "control_socket", "$@99",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@100", "control_socket_name", "$@101", "dhcp_queue_control", "$@102",
  "dhcp_ddns", "$@103", "sub_dhcp_ddns", "$@104", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "qualifying_suffix", "$@105",
  "server_ip", "$@106", "server_port", "sender_ip", "$@107", "sender_port",
  "max_queue_size", "ncr_protocol", "$@108", "ncr_protocol_value",
  "ncr_format", "$@109", "override_no_update", "override_client_update",
  "replace_client_name", "$@110", "replace_client_name_value",
  "generated_prefix", "$@111", "hostname_char_set", "$@112",
  "hostname_char_replacement", "$@113", "dhcp6_json_object", "$@114",
  "dhcpddns_json_object", "$@115", "control_agent_json_object", "$@116",
  "config_control", "$@117", "sub_config_control", "$@118",
  "config_control_params", "config_control_param", "config_databases",
  "$@119", "logging_object", "$@120", "sub_logging", "$@121",
  "logging_params", "logging_param", "loggers", "$@122", "loggers_entries",
  "logger_entry", "$@123", "logger_params", "logger_param", "debuglevel",
  "severity", "$@124", "output_options_list", "$@125",
  "output_options_list_content", "output_entry", "$@126",
  "output_params_list", "output_params", "output", "$@127", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short
  Dhcp4Parser::yyrline_[] =
  {
       0,   259,   259,   259,   260,   260,   261,   261,   262,   262,
     263,   263,   264,   264,   265,   265,   266,   266,   267,   267,
     268,   268,   269,   269,   270,   270,   271,   271,   272,   272,
     280,   281,   282,   283,   284,   285,   286,   289,   294,   294,
     305,   308,   309,   312,   316,   323,   323,   330,   331,   334,
     338,   345,   345,   352,   353,   356,   360,   371,   381,   381,
     397,   398,   402,   403,   404,   405,   406,   407,   410,   410,
     425,   425,   434,   435,   440,   441,   442,   443,   444,   445,
     446,   447,   448,   449,   450,   451,   452,   453,   454,   455,
     456,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   480,   485,   490,   495,   500,   505,   510,   515,
     515,   523,   528,   533,   539,   539,   550,   551,   554,   555,
     556,   557,   558,   559,   560,   563,   563,   572,   572,   582,
     582,   589,   590,   593,   593,   600,   602,   606,   612,   612,
     624,   624,   634,   635,   637,   639,   639,   657,   657,   669,
     669,   679,   680,   683,   684,   687,   687,   697,   698,   701,
     702,   703,   704,   705,   706,   707,   708,   709,   710,   711,
     712,   713,   714,   715,   716,   717,   718,   719,   720,   723,
     723,   730,   731,   732,   733,   736,   736,   744,   744,   752,
     752,   760,   765,   765,   773,   778,   783,   788,   793,   798,
     803,   808,   808,   816,   816,   824,   824,   832,   832,   840,
     845,   850,   850,   860,   861,   864,   865,   866,   867,   868,
     871,   876,   881,   886,   891,   896,   896,   906,   907,   910,
     911,   914,   914,   924,   924,   934,   935,   936,   939,   940,
     943,   943,   951,   951,   959,   959,   970,   971,   974,   975,
     976,   977,   978,   979,   982,   987,   992,   997,  1002,  1007,
    1015,  1015,  1028,  1029,  1032,  1033,  1040,  1040,  1066,  1066,
    1077,  1078,  1082,  1083,  1084,  1085,  1086,  1087,  1088,  1089,
    1090,  1091,  1092,  1093,  1094,  1095,  1096,  1097,  1098,  1099,
    1100,  1101,  1102,  1103,  1104,  1105,  1106,  1107,  1108,  1111,
    1111,  1119,  1119,  1127,  1127,  1135,  1135,  1143,  1143,  1151,
    1151,  1159,  1159,  1169,  1169,  1176,  1177,  1178,  1179,  1182,
    1189,  1189,  1200,  1201,  1205,  1206,  1209,  1209,  1217,  1218,
    1221,  1222,  1223,  1224,  1225,  1226,  1227,  1228,  1229,  1230,
    1231,  1232,  1233,  1234,  1235,  1236,  1237,  1238,  1239,  1240,
    1241,  1242,  1249,  1249,  1262,  1262,  1271,  1272,  1275,  1276,
    1281,  1281,  1296,  1296,  1310,  1311,  1314,  1315,  1318,  1319,
    1320,  1321,  1322,  1323,  1324,  1325,  1326,  1327,  1330,  1332,
    1337,  1339,  1339,  1347,  1347,  1355,  1355,  1363,  1365,  1365,
    1373,  1382,  1382,  1394,  1395,  1400,  1401,  1406,  1406,  1418,
    1418,  1430,  1431,  1436,  1437,  1442,  1443,  1444,  1445,  1446,
    1447,  1448,  1449,  1450,  1453,  1455,  1455,  1463,  1465,  1467,
    1472,  1480,  1480,  1492,  1493,  1496,  1497,  1500,  1500,  1510,
    1510,  1520,  1521,  1524,  1525,  1526,  1527,  1528,  1529,  1530,
    1533,  1533,  1541,  1541,  1566,  1566,  1596,  1596,  1606,  1607,
    1610,  1611,  1614,  1614,  1623,  1623,  1632,  1633,  1636,  1637,
    1641,  1642,  1643,  1644,  1645,  1646,  1647,  1648,  1649,  1650,
    1651,  1652,  1653,  1654,  1655,  1658,  1658,  1666,  1666,  1674,
    1674,  1682,  1682,  1690,  1690,  1700,  1700,  1708,  1708,  1716,
    1716,  1724,  1724,  1732,  1732,  1740,  1740,  1748,  1748,  1761,
    1761,  1771,  1772,  1778,  1778,  1788,  1789,  1792,  1792,  1802,
    1803,  1806,  1807,  1810,  1811,  1812,  1813,  1814,  1815,  1816,
    1817,  1818,  1819,  1820,  1823,  1825,  1825,  1833,  1842,  1849,
    1849,  1859,  1860,  1863,  1864,  1865,  1866,  1867,  1870,  1870,
    1878,  1878,  1889,  1889,  1927,  1927,  1939,  1939,  1949,  1950,
    1953,  1954,  1955,  1956,  1957,  1958,  1959,  1960,  1961,  1962,
    1963,  1964,  1965,  1966,  1967,  1968,  1969,  1970,  1973,  1978,
    1978,  1986,  1986,  1994,  1999,  1999,  2007,  2012,  2017,  2017,
    2025,  2026,  2029,  2029,  2037,  2042,  2047,  2047,  2055,  2058,
    2061,  2064,  2067,  2073,  2073,  2081,  2081,  2089,  2089,  2100,
    2100,  2107,  2107,  2114,  2114,  2121,  2121,  2132,  2132,  2142,
    2143,  2147,  2150,  2150,  2165,  2165,  2175,  2175,  2186,  2187,
    2191,  2195,  2195,  2207,  2208,  2212,  2212,  2220,  2221,  2224,
    2225,  2226,  2227,  2228,  2229,  2230,  2233,  2238,  2238,  2246,
    2246,  2256,  2257,  2260,  2260,  2268,  2269,  2272,  2273,  2274,
    2275,  2278,  2278,  2286,  2291,  2296
  };

  // Print the state stack on the debug stream.
  void
  Dhcp4Parser::yystack_print_ ()
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
  Dhcp4Parser::yy_reduce_print_ (int yyrule)
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
#endif // PARSER4_DEBUG


#line 14 "dhcp4_parser.yy" // lalr1.cc:1242
} } // isc::dhcp
#line 5048 "dhcp4_parser.cc" // lalr1.cc:1242
#line 2301 "dhcp4_parser.yy" // lalr1.cc:1243


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
