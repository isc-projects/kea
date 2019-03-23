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

  case 111:
#line 479 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1071 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 112:
#line 484 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1080 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 113:
#line 489 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1089 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 114:
#line 494 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1098 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 115:
#line 499 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1107 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 116:
#line 504 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1116 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 117:
#line 509 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1125 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 118:
#line 514 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1133 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 119:
#line 516 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1143 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 120:
#line 522 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1152 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 121:
#line 527 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1161 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 122:
#line 532 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1170 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 123:
#line 538 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1181 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 124:
#line 543 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1191 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 134:
#line 562 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1201 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 135:
#line 566 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1210 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 136:
#line 571 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1221 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 137:
#line 576 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1230 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 138:
#line 581 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1238 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 139:
#line 583 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1247 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 140:
#line 588 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1253 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 141:
#line 589 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1259 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 142:
#line 592 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1267 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 143:
#line 594 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1276 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 144:
#line 599 "dhcp4_parser.yy" // lalr1.cc:919
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1284 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 145:
#line 601 "dhcp4_parser.yy" // lalr1.cc:919
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1292 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 146:
#line 605 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1301 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 147:
#line 611 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1312 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 148:
#line 616 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1323 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 149:
#line 623 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1334 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 150:
#line 628 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1343 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 154:
#line 638 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1351 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 155:
#line 640 "dhcp4_parser.yy" // lalr1.cc:919
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

  case 156:
#line 656 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1382 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 157:
#line 661 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1393 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 158:
#line 668 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1404 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 159:
#line 673 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1413 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 164:
#line 686 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1423 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 165:
#line 690 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1433 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 188:
#line 722 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1441 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 189:
#line 724 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1450 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 190:
#line 729 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1456 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 191:
#line 730 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1462 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 192:
#line 731 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1468 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 193:
#line 732 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1474 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 194:
#line 735 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1482 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 195:
#line 737 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1492 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 196:
#line 743 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1500 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 197:
#line 745 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1510 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 198:
#line 751 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1518 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 199:
#line 753 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1528 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 200:
#line 759 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1537 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 201:
#line 764 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1545 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 202:
#line 766 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1555 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 203:
#line 772 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1564 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 204:
#line 777 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1573 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 205:
#line 782 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1582 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 206:
#line 787 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1591 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 207:
#line 792 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1600 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 208:
#line 797 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1609 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 209:
#line 802 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1618 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 210:
#line 807 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1626 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 211:
#line 809 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1636 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 212:
#line 815 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1644 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 213:
#line 817 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1654 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 214:
#line 823 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1662 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 215:
#line 825 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1672 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 216:
#line 831 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1680 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 217:
#line 833 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1690 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 218:
#line 839 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1699 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 219:
#line 844 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1708 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 220:
#line 849 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1719 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 221:
#line 854 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1728 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 229:
#line 870 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1737 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 230:
#line 875 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1746 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 231:
#line 880 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1755 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 232:
#line 885 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1764 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 233:
#line 890 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1773 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 234:
#line 895 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1784 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 235:
#line 900 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1793 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 240:
#line 913 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1803 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 241:
#line 917 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1813 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 242:
#line 923 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1823 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 243:
#line 927 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1833 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 249:
#line 942 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1841 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 250:
#line 944 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1851 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 251:
#line 950 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1859 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 252:
#line 952 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1868 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 253:
#line 958 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1879 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 254:
#line 963 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1889 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 263:
#line 981 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1898 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 264:
#line 986 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1907 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 265:
#line 991 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1916 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 266:
#line 996 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1925 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 267:
#line 1001 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1934 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 268:
#line 1006 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1943 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 269:
#line 1014 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1954 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 270:
#line 1019 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1963 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 275:
#line 1039 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1973 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 276:
#line 1043 "dhcp4_parser.yy" // lalr1.cc:919
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

  case 277:
#line 1065 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2009 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 278:
#line 1069 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2019 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 308:
#line 1110 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2027 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 309:
#line 1112 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2037 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 310:
#line 1118 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2045 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 311:
#line 1120 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2055 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 312:
#line 1126 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2063 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 313:
#line 1128 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2073 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 314:
#line 1134 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2081 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 315:
#line 1136 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2091 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 316:
#line 1142 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2099 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 317:
#line 1144 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2109 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 318:
#line 1150 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2117 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 319:
#line 1152 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2127 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 320:
#line 1158 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2138 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 321:
#line 1163 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2147 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 322:
#line 1168 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2155 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 323:
#line 1170 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2164 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 324:
#line 1175 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2170 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 325:
#line 1176 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2176 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 326:
#line 1177 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2182 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 327:
#line 1178 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2188 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 328:
#line 1181 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2197 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 329:
#line 1188 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2208 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 330:
#line 1193 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2217 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 335:
#line 1208 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2227 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 336:
#line 1212 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 2235 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 361:
#line 1248 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2246 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 362:
#line 1253 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2255 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 363:
#line 1261 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2264 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 364:
#line 1264 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 2272 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 369:
#line 1280 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2282 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 370:
#line 1284 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2294 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 371:
#line 1295 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2304 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 372:
#line 1299 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2316 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 388:
#line 1331 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2325 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 390:
#line 1338 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2333 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 391:
#line 1340 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2343 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 392:
#line 1346 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2351 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 393:
#line 1348 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2361 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 394:
#line 1354 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2369 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 395:
#line 1356 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2379 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 397:
#line 1364 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2387 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 398:
#line 1366 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2397 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 399:
#line 1372 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2406 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 400:
#line 1381 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2417 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 401:
#line 1386 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2426 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 406:
#line 1405 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2436 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 407:
#line 1409 "dhcp4_parser.yy" // lalr1.cc:919
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2445 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 408:
#line 1417 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2455 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 409:
#line 1421 "dhcp4_parser.yy" // lalr1.cc:919
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2464 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 424:
#line 1454 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2472 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 425:
#line 1456 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2482 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 428:
#line 1466 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2491 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 429:
#line 1471 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2500 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 430:
#line 1479 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2511 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 431:
#line 1484 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2520 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 436:
#line 1499 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2530 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 437:
#line 1503 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2540 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 438:
#line 1509 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2550 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 439:
#line 1513 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2560 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 449:
#line 1532 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2568 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 450:
#line 1534 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2578 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 451:
#line 1540 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2586 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 452:
#line 1542 "dhcp4_parser.yy" // lalr1.cc:919
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

  case 453:
#line 1565 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2621 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 454:
#line 1567 "dhcp4_parser.yy" // lalr1.cc:919
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

  case 455:
#line 1595 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2661 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 456:
#line 1600 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2670 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 461:
#line 1613 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2680 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 462:
#line 1617 "dhcp4_parser.yy" // lalr1.cc:919
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2689 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 463:
#line 1622 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2699 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 464:
#line 1626 "dhcp4_parser.yy" // lalr1.cc:919
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2708 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 484:
#line 1657 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2716 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 485:
#line 1659 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2726 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 486:
#line 1665 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2734 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 487:
#line 1667 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2744 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 488:
#line 1673 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2752 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 489:
#line 1675 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2762 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 490:
#line 1681 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2770 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 491:
#line 1683 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2780 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 492:
#line 1689 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2791 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 493:
#line 1694 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2800 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 494:
#line 1699 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2808 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 495:
#line 1701 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2818 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 496:
#line 1707 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2826 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 497:
#line 1709 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2836 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 498:
#line 1715 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2844 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 499:
#line 1717 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2854 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 500:
#line 1723 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2862 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 501:
#line 1725 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2872 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 502:
#line 1731 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2880 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 503:
#line 1733 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2890 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 504:
#line 1739 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2898 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 505:
#line 1741 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2908 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 506:
#line 1747 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2919 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 507:
#line 1752 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2928 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 508:
#line 1760 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2939 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 509:
#line 1765 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2948 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 512:
#line 1777 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2959 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 513:
#line 1782 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2968 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 516:
#line 1791 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2978 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 517:
#line 1795 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2988 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 534:
#line 1824 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2996 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 535:
#line 1826 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3006 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 536:
#line 1832 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3015 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 537:
#line 1841 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3024 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 538:
#line 1848 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3035 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 539:
#line 1853 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3044 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 547:
#line 1869 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3052 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 548:
#line 1871 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3062 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 549:
#line 1877 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3070 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 550:
#line 1879 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3080 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 551:
#line 1888 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3088 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 552:
#line 1890 "dhcp4_parser.yy" // lalr1.cc:919
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

  case 553:
#line 1926 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3137 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 554:
#line 1931 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3148 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 555:
#line 1938 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3158 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 556:
#line 1942 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3168 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 577:
#line 1972 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3177 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 578:
#line 1977 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3185 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 579:
#line 1979 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3195 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 580:
#line 1985 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3203 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 581:
#line 1987 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3213 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 582:
#line 1993 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3222 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 583:
#line 1998 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3230 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 584:
#line 2000 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3240 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 585:
#line 2006 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3249 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 586:
#line 2011 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3258 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 587:
#line 2016 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3266 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 588:
#line 2018 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3275 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 589:
#line 2024 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3281 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 590:
#line 2025 "dhcp4_parser.yy" // lalr1.cc:919
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3287 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 591:
#line 2028 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3295 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 592:
#line 2030 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3305 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 593:
#line 2036 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3314 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 594:
#line 2041 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3323 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 595:
#line 2046 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3331 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 596:
#line 2048 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3340 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 597:
#line 2054 "dhcp4_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3348 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 598:
#line 2057 "dhcp4_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3356 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 599:
#line 2060 "dhcp4_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3364 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 600:
#line 2063 "dhcp4_parser.yy" // lalr1.cc:919
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3372 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 601:
#line 2066 "dhcp4_parser.yy" // lalr1.cc:919
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3381 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 602:
#line 2072 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3389 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 603:
#line 2074 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3399 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 604:
#line 2080 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3407 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 605:
#line 2082 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3417 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 606:
#line 2088 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3425 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 607:
#line 2090 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3435 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 608:
#line 2099 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3443 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 609:
#line 2101 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3452 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 610:
#line 2106 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3460 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 611:
#line 2108 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3469 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 612:
#line 2113 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3477 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 613:
#line 2115 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3486 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 614:
#line 2120 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3497 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 615:
#line 2125 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3507 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 616:
#line 2131 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3517 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 617:
#line 2135 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // No config_control params are required
    // parsing completed
}
#line 3526 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 621:
#line 2149 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3537 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 622:
#line 2154 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3546 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 623:
#line 2164 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3557 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 624:
#line 2169 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3566 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 625:
#line 2174 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3576 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 626:
#line 2178 "dhcp4_parser.yy" // lalr1.cc:919
    {
    // parsing completed
}
#line 3584 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 630:
#line 2194 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3595 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 631:
#line 2199 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3604 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 634:
#line 2211 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3614 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 635:
#line 2215 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 3622 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 645:
#line 2232 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3631 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 646:
#line 2237 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3639 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 647:
#line 2239 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3649 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 648:
#line 2245 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3660 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 649:
#line 2250 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3669 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 652:
#line 2259 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3679 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 653:
#line 2263 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.stack_.pop_back();
}
#line 3687 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 660:
#line 2277 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3695 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 661:
#line 2279 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3705 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 662:
#line 2285 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3714 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 663:
#line 2290 "dhcp4_parser.yy" // lalr1.cc:919
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3723 "dhcp4_parser.cc" // lalr1.cc:919
    break;

  case 664:
#line 2295 "dhcp4_parser.yy" // lalr1.cc:919
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


  const short Dhcp4Parser::yypact_ninf_ = -822;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     413,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,    32,    35,    42,    56,    58,
      60,    62,    64,    66,    79,    94,   150,   152,   156,   172,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,    35,   -88,
      40,    80,    43,   189,    -6,   249,   118,   226,   251,   -49,
     349,    36,   212,  -822,   193,   206,   247,   244,   263,  -822,
    -822,  -822,  -822,  -822,   265,  -822,    81,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,   277,   308,   312,  -822,
    -822,  -822,  -822,  -822,  -822,   314,   315,   322,   323,   324,
     334,   338,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,   341,  -822,  -822,  -822,  -822,
     114,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,   342,  -822,   126,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,   360,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
     141,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,   147,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,   259,   287,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,   272,  -822,  -822,   379,
    -822,  -822,  -822,   381,  -822,  -822,   328,   350,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,   383,   387,  -822,  -822,  -822,  -822,   368,   392,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,   157,  -822,  -822,  -822,   397,  -822,  -822,   398,  -822,
     399,   401,  -822,  -822,   403,   404,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,   188,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,   276,  -822,  -822,  -822,   280,  -822,  -822,  -822,    35,
      35,  -822,   246,   420,   421,   422,   423,   434,  -822,    40,
    -822,   435,   441,   442,   261,   281,   290,   445,   446,   449,
     456,   457,   460,   294,   295,   296,   298,   325,   329,   299,
     464,   465,   490,   491,   492,   496,   498,   499,   500,   501,
     502,   503,   504,   339,   505,   509,   511,    80,  -822,   513,
     514,   516,   351,    43,  -822,   521,   524,   525,   526,   527,
     528,   364,   529,   532,   533,   189,  -822,   534,    -6,  -822,
     535,   537,   538,   539,   541,   542,   543,   544,  -822,   249,
    -822,   545,   546,   380,   548,   550,   552,   384,  -822,   226,
     555,   388,   389,  -822,   251,   556,   559,     5,  -822,   394,
     560,   561,   412,   581,   416,   417,   585,   586,   418,   419,
     589,   590,   591,   592,   349,  -822,   593,    36,  -822,   594,
     212,  -822,  -822,  -822,   595,   596,   597,    35,    35,    35,
    -822,   598,   599,   600,  -822,  -822,  -822,   431,   432,   438,
     602,   603,   606,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
     443,   607,   609,   610,   611,   612,   447,   -42,   613,   615,
     616,   617,   618,  -822,   619,   612,   620,  -822,   623,   195,
     203,  -822,  -822,   453,   454,   459,   625,   461,   462,  -822,
     623,   463,   627,  -822,   466,  -822,   623,   467,   468,   469,
     470,   471,   472,   473,  -822,   474,   475,  -822,   476,   477,
     478,  -822,  -822,   479,  -822,  -822,  -822,   480,    35,  -822,
    -822,   481,   482,  -822,   483,  -822,  -822,    20,   517,  -822,
    -822,    13,   485,   486,   487,  -822,   630,  -822,   653,  -822,
      35,    80,    36,  -822,  -822,  -822,   212,    43,   636,  -822,
    -822,  -822,   187,   187,   654,  -822,   655,   656,   657,   658,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,    75,   659,
     660,   661,   149,    49,  -822,   349,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,   662,  -822,  -822,
    -822,  -822,   137,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,   663,   654,  -822,   284,
     286,   288,   297,  -822,   301,  -822,  -822,  -822,  -822,  -822,
    -822,   667,   668,   669,   670,   671,  -822,  -822,  -822,  -822,
     672,   673,   674,   675,   676,  -822,   303,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,   307,  -822,   677,
     678,  -822,  -822,   679,   681,  -822,  -822,   680,   684,  -822,
    -822,   682,   686,  -822,  -822,   685,   687,  -822,  -822,  -822,
    -822,  -822,  -822,    91,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,    92,  -822,  -822,   688,   689,  -822,  -822,   690,   692,
    -822,   693,   694,   695,   696,   697,   698,   326,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
     332,  -822,  -822,  -822,   336,   512,  -822,   699,   700,  -822,
    -822,  -822,  -822,   652,  -822,   164,  -822,   701,  -822,  -822,
    -822,  -822,   702,   636,  -822,   704,   705,   706,   707,   522,
     531,   547,   540,   549,   708,   710,   711,   712,   551,   553,
     554,   557,   558,   187,  -822,  -822,   187,  -822,   654,   189,
    -822,   655,   226,  -822,   656,   251,  -822,   657,   430,  -822,
     658,    75,  -822,    51,   659,  -822,   249,  -822,   660,   -49,
    -822,   661,   562,   563,   564,   565,   566,   567,   149,  -822,
     713,   715,    49,  -822,  -822,  -822,   717,   718,    -6,  -822,
     662,   722,  -822,    34,   663,  -822,  -822,   569,  -822,   377,
     570,   571,   572,  -822,  -822,  -822,  -822,  -822,   573,   574,
     575,   576,  -822,  -822,  -822,  -822,  -822,  -822,   358,  -822,
     359,  -822,   719,  -822,   721,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,   362,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,   726,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,   724,   744,  -822,  -822,  -822,  -822,  -822,
     740,  -822,   369,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,   579,   580,  -822,  -822,   582,   372,  -822,   623,  -822,
     747,  -822,  -822,  -822,  -822,  -822,   390,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,   430,
    -822,   749,   583,  -822,    51,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,   750,   584,   753,    34,  -822,  -822,   588,  -822,
    -822,   754,  -822,   601,  -822,  -822,   755,  -822,  -822,   197,
    -822,   -24,   755,  -822,  -822,   756,   757,   759,   391,  -822,
    -822,  -822,  -822,  -822,  -822,   760,   614,   605,   626,   -24,
    -822,   604,  -822,  -822,  -822,  -822,  -822
  };

  const unsigned short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   134,     9,   277,    11,
     438,    13,   463,    15,   363,    17,   371,    19,   408,    21,
     242,    23,   555,    25,   625,    27,   616,    29,    47,    41,
       0,     0,     0,     0,     0,   465,     0,   373,   410,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     623,   608,   610,   612,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   614,   123,   149,     0,     0,     0,   484,
     486,   488,   147,   156,   158,     0,     0,     0,     0,     0,
       0,     0,   118,   269,   361,   400,   329,   451,   453,   322,
     220,   512,   455,   234,   253,     0,   538,   551,   553,   110,
       0,    72,    74,    75,    76,   107,   108,   109,    77,   105,
      94,    95,    96,    80,    81,   102,    82,    83,    84,    88,
      89,    78,   106,    79,    86,    87,   100,   101,   103,    97,
      98,    99,    85,    90,    91,    92,    93,   104,   136,   138,
     142,     0,   133,     0,   125,   127,   128,   129,   130,   131,
     132,   310,   312,   314,   430,   308,   316,     0,   320,   318,
     508,   307,   281,   282,   283,   304,   305,   306,   294,   295,
       0,   279,   286,   299,   300,   301,   287,   289,   290,   292,
     288,   284,   285,   302,   303,   291,   296,   297,   298,   293,
     449,   448,   444,   445,   443,     0,   440,   442,   446,   447,
     506,   494,   496,   500,   498,   504,   502,   490,   483,   477,
     481,   482,     0,   466,   467,   478,   479,   480,   474,   469,
     475,   471,   472,   473,   476,   470,     0,   390,   201,     0,
     394,   392,   397,     0,   386,   387,     0,   374,   375,   377,
     389,   378,   379,   380,   396,   381,   382,   383,   384,   385,
     424,     0,     0,   422,   423,   426,   427,     0,   411,   412,
     414,   415,   416,   417,   418,   419,   420,   421,   249,   251,
     246,     0,   244,   247,   248,     0,   578,   580,     0,   583,
       0,     0,   587,   591,     0,     0,   595,   602,   604,   606,
     576,   574,   575,     0,   557,   559,   560,   561,   562,   563,
     564,   565,   566,   567,   568,   569,   570,   571,   572,   573,
     630,     0,   627,   629,   621,     0,   618,   620,    46,     0,
       0,    39,     0,     0,     0,     0,     0,     0,    57,     0,
      59,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    71,     0,
       0,     0,     0,     0,   135,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   278,     0,     0,   439,
       0,     0,     0,     0,     0,     0,     0,     0,   464,     0,
     364,     0,     0,     0,     0,     0,     0,     0,   372,     0,
       0,     0,     0,   409,     0,     0,     0,     0,   243,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   556,     0,     0,   626,     0,
       0,   617,    50,    43,     0,     0,     0,     0,     0,     0,
      61,     0,     0,     0,   120,   121,   122,     0,     0,     0,
       0,     0,     0,   111,   112,   113,   114,   115,   116,   117,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   537,     0,     0,     0,    73,     0,     0,
       0,   146,   126,     0,     0,     0,     0,     0,     0,   328,
       0,     0,     0,   280,     0,   441,     0,     0,     0,     0,
       0,     0,     0,     0,   468,     0,     0,   388,     0,     0,
       0,   399,   376,     0,   428,   429,   413,     0,     0,   245,
     577,     0,     0,   582,     0,   585,   586,     0,     0,   593,
     594,     0,     0,     0,     0,   558,     0,   628,     0,   619,
       0,     0,     0,   609,   611,   613,     0,     0,     0,   485,
     487,   489,     0,     0,   160,   119,   271,   365,   402,   331,
      40,   452,   454,   324,   325,   326,   327,   323,     0,     0,
     457,   236,     0,     0,   552,     0,    51,   137,   140,   141,
     139,   144,   145,   143,   311,   313,   315,   432,   309,   317,
     321,   319,     0,   450,   507,   495,   497,   501,   499,   505,
     503,   491,   391,   202,   395,   393,   398,   425,   250,   252,
     579,   581,   584,   589,   590,   588,   592,   597,   598,   599,
     600,   601,   596,   603,   605,   607,     0,   160,    44,     0,
       0,     0,     0,   154,     0,   151,   153,   188,   194,   196,
     198,     0,     0,     0,     0,     0,   210,   212,   214,   216,
       0,     0,     0,     0,     0,   187,     0,   166,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   181,   182,
     183,   178,   184,   185,   186,   179,   180,     0,   164,     0,
     161,   162,   275,     0,   272,   273,   369,     0,   366,   367,
     406,     0,   403,   404,   335,     0,   332,   333,   229,   230,
     231,   232,   233,     0,   222,   224,   225,   226,   227,   228,
     516,     0,   514,   461,     0,   458,   459,   240,     0,   237,
     238,     0,     0,     0,     0,     0,     0,     0,   255,   257,
     258,   259,   260,   261,   262,   547,   549,   546,   544,   545,
       0,   540,   542,   543,     0,    53,   436,     0,   433,   434,
     492,   510,   511,     0,   634,     0,   632,     0,    69,   624,
     615,   124,     0,     0,   150,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   148,   157,     0,   159,     0,     0,
     270,     0,   373,   362,     0,   410,   401,     0,     0,   330,
       0,     0,   221,   518,     0,   513,   465,   456,     0,     0,
     235,     0,     0,     0,     0,     0,     0,     0,     0,   254,
       0,     0,     0,   539,   554,    55,     0,    54,     0,   431,
       0,     0,   509,     0,     0,   631,   622,     0,   152,     0,
       0,     0,     0,   200,   203,   204,   205,   206,     0,     0,
       0,     0,   218,   219,   207,   208,   209,   167,     0,   163,
       0,   274,     0,   368,     0,   405,   360,   354,   342,   343,
     357,   358,   359,   345,   346,   339,   340,   341,   352,   353,
     351,     0,   337,   344,   355,   356,   347,   348,   349,   350,
     334,   223,   534,     0,   532,   533,   525,   526,   530,   531,
     527,   528,   529,     0,   519,   520,   522,   523,   524,   515,
       0,   460,     0,   239,   263,   264,   265,   266,   267,   268,
     256,     0,     0,   541,    52,     0,     0,   435,     0,   648,
       0,   646,   644,   638,   642,   643,     0,   636,   640,   641,
     639,   633,   155,   190,   191,   192,   193,   189,   195,   197,
     199,   211,   213,   215,   217,   165,   276,   370,   407,     0,
     336,     0,     0,   517,     0,   462,   241,   548,   550,    56,
     437,   493,     0,     0,     0,     0,   635,   338,     0,   536,
     521,     0,   645,     0,   637,   535,     0,   647,   652,     0,
     650,     0,     0,   649,   660,     0,     0,     0,     0,   654,
     656,   657,   658,   659,   651,     0,     0,     0,     0,     0,
     653,     0,   662,   663,   664,   655,   661
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,   -46,  -822,  -472,  -822,
     240,  -822,  -822,  -822,  -822,  -822,  -822,  -516,  -822,  -822,
    -822,   -70,  -822,  -822,  -822,   415,  -822,  -822,  -822,  -822,
     175,   361,   -47,   -44,     4,    12,    15,    19,  -822,  -822,
    -822,  -822,    23,    26,  -822,  -822,   170,   357,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,   -40,  -822,  -822,  -822,  -822,  -822,
    -822,   117,  -822,   -33,  -822,  -578,   -35,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,   -26,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,   -27,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,   -54,
    -822,  -822,  -822,   -48,   355,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,   -50,  -822,  -822,  -822,  -822,  -822,  -822,  -821,
    -822,  -822,  -822,   -16,  -822,  -822,  -822,   -11,   405,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -820,  -822,   -68,
    -822,   -55,  -822,    27,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,   -15,  -822,  -822,  -178,   -63,  -822,  -822,  -822,  -822,
    -822,    -4,  -822,  -822,  -822,     0,  -822,   406,  -822,   -66,
    -822,  -822,  -822,  -822,  -822,   -64,  -822,  -822,  -822,  -822,
    -822,   -19,  -822,  -822,  -822,    -9,  -822,  -822,  -822,     3,
    -822,   414,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,   -10,  -822,  -822,  -822,    -5,   444,  -822,
    -822,   -57,  -822,   -39,  -822,   -62,  -822,  -822,  -822,    11,
    -822,  -822,  -822,    21,  -822,   437,    -7,  -822,    -3,  -822,
       8,  -822,   236,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -817,  -822,  -822,  -822,  -822,  -822,    25,  -822,  -822,  -822,
    -134,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,     9,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
     257,   409,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,
    -822,  -822,  -822,  -822,  -822,  -822,  -822,  -822,   289,   407,
    -822,  -822,  -822,  -822,  -822,  -822,   292,   411,  -822,  -822,
    -822,     2,  -822,  -822,  -136,  -822,  -822,  -822,  -822,  -822,
    -822,  -152,  -822,  -822,  -168,  -822,  -822,  -822,  -822,  -822
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     611,    87,    88,    41,    68,    84,    85,   627,   795,   876,
     877,   705,    43,    70,    96,    97,    98,   363,    45,    71,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     390,   150,   151,   152,   153,   372,   183,   184,    47,    72,
     185,   409,   186,   410,   630,   187,   411,   633,   188,   154,
     380,   155,   373,   684,   685,   686,   812,   156,   381,   157,
     382,   729,   730,   731,   836,   706,   707,   708,   815,   997,
     709,   816,   710,   817,   711,   818,   712,   713,   442,   714,
     715,   716,   717,   718,   719,   720,   721,   824,   722,   825,
     723,   826,   724,   827,   725,   726,   158,   398,   753,   754,
     755,   756,   757,   758,   759,   159,   401,   768,   769,   770,
     859,    61,    79,   311,   312,   313,   455,   314,   456,   160,
     402,   777,   778,   779,   780,   781,   782,   783,   784,   161,
     391,   733,   734,   735,   839,    49,    73,   210,   211,   212,
     419,   213,   415,   214,   416,   215,   417,   216,   420,   217,
     423,   218,   422,   162,   397,   617,   220,   163,   394,   745,
     746,   747,   848,   931,   932,   164,   392,    55,    76,   737,
     738,   739,   842,    57,    77,   276,   277,   278,   279,   280,
     281,   282,   441,   283,   445,   284,   444,   285,   286,   446,
     287,   165,   393,   741,   742,   743,   845,    59,    78,   297,
     298,   299,   300,   301,   450,   302,   303,   304,   305,   222,
     418,   797,   798,   799,   878,    51,    74,   235,   236,   237,
     427,   166,   395,   167,   396,   168,   400,   764,   765,   766,
     856,    53,    75,   252,   253,   254,   169,   377,   170,   378,
     171,   379,   258,   437,   802,   881,   259,   431,   260,   432,
     261,   434,   262,   433,   263,   436,   264,   435,   265,   430,
     229,   424,   803,   172,   399,   761,   762,   853,   953,   954,
     955,   956,   957,  1011,   958,   173,   174,   404,   790,   791,
     792,   870,   793,   871,   175,   405,   176,   406,    63,    80,
     333,   334,   335,   336,   460,   337,   461,   338,   339,   463,
     340,   341,   342,   466,   665,   343,   467,   344,   345,   346,
     470,   672,   347,   471,   348,   472,   349,   473,    99,   365,
     100,   366,   101,   367,   177,   371,    67,    82,   355,   356,
     357,   479,   102,   364,    65,    81,   351,   352,   353,   476,
     805,   806,   883,   986,   987,   988,   989,  1024,   990,  1022,
    1039,  1040,  1041,  1048,  1049,  1050,  1055,  1051,  1052,  1053
  };

  const unsigned short
  Dhcp4Parser::yytable_[] =
  {
      95,   139,   182,   201,   231,   248,   232,   274,   293,   310,
     330,   225,   295,   266,   296,   189,   223,   238,   250,   233,
     288,   306,    83,   331,   640,   727,   202,   926,   927,   203,
     644,   939,    30,   190,   224,   239,   251,   663,   289,   307,
      31,   332,    32,   610,    33,   613,   614,   615,   616,    42,
      89,   275,   294,   610,   221,   234,   249,   178,   179,   308,
     309,   180,   125,    44,   181,    46,   226,    48,   255,    50,
     227,    52,   256,    54,   230,   127,   128,   204,   109,   110,
     111,   228,    86,   257,   369,   205,    56,   198,   206,   370,
     199,   103,   207,   104,   851,   854,   208,   852,   855,   209,
     219,    58,   105,   268,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   308,   309,   127,   128,   407,   124,   125,
     268,    94,   408,  1044,   127,   128,  1045,  1046,  1047,   413,
     127,   128,   127,   128,   414,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   425,   942,   943,   124,   125,   426,
     428,   667,   668,   669,   670,   429,   664,    60,   126,    62,
     457,   127,   128,    64,    94,   458,   129,   884,   785,   786,
     885,   130,   131,   748,   749,   750,   751,   132,   752,    66,
     979,   350,   980,   981,    90,   124,   671,   133,   926,   927,
     134,   474,   939,    91,    92,    93,   475,   135,   136,   358,
    1042,   137,   138,  1043,    94,    34,    35,    36,    37,   359,
      94,   628,   629,    94,   107,   108,   109,   110,   111,    94,
     687,    94,   631,   632,   354,   688,   689,   690,   691,   692,
     693,   694,   695,   696,   697,   698,   699,   700,   701,   702,
     703,   704,   247,   800,   115,   116,   117,   118,   119,   120,
      94,   360,   361,   191,   192,   193,   268,   125,   908,   267,
     771,   772,   773,   774,   775,   776,   362,   438,   194,   368,
     127,   128,   195,   196,   197,   129,   109,   110,   111,   477,
     440,   374,   198,   480,   478,   199,   132,   407,   481,   477,
     439,   480,   808,   200,   809,   268,   810,   269,   270,    95,
     413,   271,   272,   273,   813,   811,   833,   127,   128,   814,
     833,   834,   375,   482,   483,   835,   376,   125,   383,   384,
     268,   290,   269,   270,   291,   292,   385,   386,   387,   868,
     127,   128,   127,   128,   869,   872,   448,   139,   388,   474,
     873,   240,   389,   182,   874,   403,   412,   241,   242,   243,
     244,   245,   246,   449,   247,   201,   189,    94,   231,    94,
     232,   833,   425,   225,   421,  1009,  1005,  1006,   223,   248,
    1010,   238,   457,   233,   190,   428,   453,  1016,   202,   274,
    1020,   203,   250,   443,   293,   447,   224,   451,   295,   239,
     296,   452,   288,  1025,  1059,   454,    94,   306,  1026,  1060,
     251,   459,   462,   464,   330,   465,   221,   468,   469,   234,
     289,   993,   994,   995,   996,   307,   484,   331,   226,    94,
     249,    94,   227,   275,   485,   486,   487,   488,   294,   204,
     127,   128,   255,   228,   494,   332,   256,   205,   489,   491,
     206,   593,   594,   595,   207,   492,   493,   257,   208,   497,
     498,   209,   219,   499,   495,   107,   108,   109,   110,   111,
     500,   501,  1021,   496,   502,   503,   504,   505,   510,   511,
     509,   506,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   115,   116,   117,   118,   119,
     120,   328,   329,   123,   512,   513,   514,   507,   125,   268,
     515,   508,   516,   517,   518,   519,   520,   521,   522,   524,
     523,   127,   128,   525,   196,   526,   129,   528,   529,    94,
     530,   139,   659,   198,   531,   533,   199,   182,   534,   535,
     536,   537,   538,   540,   200,   539,   541,   542,   544,   546,
     189,   547,   548,   549,   678,   550,   551,   552,   553,   555,
     556,   557,   558,   787,   559,   330,   560,   561,   190,   563,
     567,   564,   565,   568,   571,   572,   788,   570,   331,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,   573,   789,   574,   332,   575,   576,   577,
     578,   579,   580,   581,   582,   583,   584,   586,   588,   590,
      94,   599,   600,   591,   592,   596,   597,   598,   601,   602,
     603,   604,   606,   605,   607,   608,   609,   612,   618,    32,
     619,   620,   621,   634,   635,   622,   623,   625,   626,   636,
     637,   638,   639,   641,   642,   676,   643,   645,   646,   647,
     648,   649,   650,   651,   652,   653,   654,   655,   656,   657,
     658,   660,   661,   662,   666,   673,   674,   675,   677,   683,
     882,   728,   732,   736,   740,   744,   760,   763,   767,   796,
     804,   819,   820,   821,   822,   823,   828,   829,   830,   831,
     832,   838,   875,   837,   841,   840,   843,   844,   846,   847,
     850,   849,   858,   893,   857,   861,   860,   862,   863,   864,
     865,   866,   867,   880,   894,   879,   887,   886,   889,   890,
     891,   892,   898,   896,   899,   900,   901,   971,   895,   972,
     897,   975,   902,   974,   903,   904,   978,  1007,   905,  1008,
    1012,   906,  1013,   964,   965,   966,   967,   968,   969,   992,
     998,   999,  1000,  1001,  1002,  1003,  1004,  1014,  1015,  1017,
    1018,  1023,  1019,  1028,  1031,  1032,  1029,  1033,  1035,  1036,
    1056,  1057,  1038,  1058,  1061,   624,   679,   682,   527,   201,
     532,  1037,   274,   888,  1066,   293,  1063,   225,   916,   295,
     928,   296,   223,   944,   490,   288,   248,  1062,   306,   310,
     946,   934,   202,   929,   807,   203,   948,  1064,   907,   250,
     224,   917,   787,   289,   918,   909,   307,   963,   231,   935,
     232,   962,   569,   982,   949,   788,   275,   251,   970,   294,
     221,   238,   925,   233,   941,   911,   984,   945,   910,   933,
     543,  1027,   226,   789,   947,   940,   227,   249,   915,   239,
     913,   936,   912,   204,   985,   937,   950,   228,   914,   255,
     951,   205,   919,   256,   206,   562,   938,   983,   207,   234,
     920,   952,   208,   921,   257,   209,   219,   922,   566,   961,
     977,   923,   545,   976,   924,   930,   554,   960,   801,   959,
    1030,   973,   794,   585,   680,   681,   991,   589,   587,  1034,
    1054,  1065,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   916,
       0,   928,     0,     0,   944,     0,     0,     0,     0,     0,
       0,   946,   934,     0,   929,   982,     0,   948,     0,     0,
       0,     0,   917,     0,     0,   918,     0,     0,   984,     0,
     935,     0,     0,     0,     0,   949,     0,     0,     0,     0,
       0,     0,     0,   925,     0,     0,   985,     0,   945,     0,
     933,     0,     0,     0,     0,   947,     0,     0,     0,   983,
       0,     0,   936,     0,     0,     0,   937,   950,     0,     0,
       0,   951,     0,   919,     0,     0,     0,   938,     0,     0,
       0,   920,   952,     0,   921,     0,     0,     0,   922,     0,
       0,     0,   923,     0,     0,   924,   930
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    74,    77,    78,    79,
      80,    73,    78,    76,    78,    72,    73,    74,    75,    74,
      77,    78,    68,    80,   540,   603,    73,   848,   848,    73,
     546,   848,     0,    72,    73,    74,    75,    17,    77,    78,
       5,    80,     7,   515,     9,    87,    88,    89,    90,     7,
      10,    77,    78,   525,    73,    74,    75,    14,    15,   108,
     109,    18,    68,     7,    21,     7,    73,     7,    75,     7,
      73,     7,    75,     7,    80,    81,    82,    73,    27,    28,
      29,    73,   170,    75,     3,    73,     7,    93,    73,     8,
      96,    11,    73,    13,     3,     3,    73,     6,     6,    73,
      73,     7,    22,    69,    24,    25,    26,    27,    28,    29,
      30,    31,    32,   108,   109,    81,    82,     3,    67,    68,
      69,   170,     8,   147,    81,    82,   150,   151,   152,     3,
      81,    82,    81,    82,     8,    55,    56,    57,    58,    59,
      60,    61,    62,    63,     3,    94,    95,    67,    68,     8,
       3,   138,   139,   140,   141,     8,   136,     7,    78,     7,
       3,    81,    82,     7,   170,     8,    86,     3,   119,   120,
       6,    91,    92,    98,    99,   100,   101,    97,   103,     7,
     146,   145,   148,   149,   144,    67,   173,   107,  1009,  1009,
     110,     3,  1009,   153,   154,   155,     8,   117,   118,     6,
       3,   121,   122,     6,   170,   170,   171,   172,   173,     3,
     170,    16,    17,   170,    25,    26,    27,    28,    29,   170,
      33,   170,    19,    20,    12,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,   105,   106,    55,    56,    57,    58,    59,    60,
     170,     4,     8,    64,    65,    66,    69,    68,   836,    33,
     111,   112,   113,   114,   115,   116,     3,     8,    79,     4,
      81,    82,    83,    84,    85,    86,    27,    28,    29,     3,
       8,     4,    93,     3,     8,    96,    97,     3,     8,     3,
       3,     3,     8,   104,     8,    69,     8,    71,    72,   369,
       3,    75,    76,    77,     3,     8,     3,    81,    82,     8,
       3,     8,     4,   359,   360,     8,     4,    68,     4,     4,
      69,    70,    71,    72,    73,    74,     4,     4,     4,     3,
      81,    82,    81,    82,     8,     3,     8,   407,     4,     3,
       8,    92,     4,   413,     8,     4,     4,    98,    99,   100,
     101,   102,   103,     3,   105,   425,   413,   170,   428,   170,
     428,     3,     3,   425,     4,     3,     8,     8,   425,   439,
       8,   428,     3,   428,   413,     3,     8,     8,   425,   449,
       8,   425,   439,     4,   454,     4,   425,     4,   454,   428,
     454,     4,   449,     3,     3,     3,   170,   454,     8,     8,
     439,     4,     4,     4,   474,     4,   425,     4,     4,   428,
     449,    34,    35,    36,    37,   454,   170,   474,   425,   170,
     439,   170,   425,   449,     4,     4,     4,     4,   454,   425,
      81,    82,   439,   425,   173,   474,   439,   425,     4,     4,
     425,   487,   488,   489,   425,     4,     4,   439,   425,     4,
       4,   425,   425,     4,   173,    25,    26,    27,    28,    29,
       4,     4,   978,   173,     4,   171,   171,   171,     4,     4,
     171,   173,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,    55,    56,    57,    58,    59,
      60,   142,   143,    63,     4,     4,     4,   172,    68,    69,
       4,   172,     4,     4,     4,     4,     4,     4,     4,     4,
     171,    81,    82,     4,    84,     4,    86,     4,     4,   170,
       4,   591,   568,    93,   173,     4,    96,   597,     4,     4,
       4,     4,     4,     4,   104,   171,     4,     4,     4,     4,
     597,     4,     4,     4,   590,     4,     4,     4,     4,     4,
       4,   171,     4,   623,     4,   625,     4,   173,   597,     4,
       4,   173,   173,     4,     4,     4,   623,   173,   625,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   171,   623,     4,   625,   171,   171,     4,
       4,   173,   173,     4,     4,     4,     4,     4,     4,     4,
     170,   170,   170,     7,     7,     7,     7,     7,   170,     7,
       7,     5,     5,   170,     5,     5,     5,   170,     5,     7,
       5,     5,     5,   170,   170,     7,     7,     7,     5,   170,
       5,   170,   170,   170,     7,     5,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   137,   170,   170,   170,     5,    23,
       8,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     3,   170,     6,     3,     6,     6,     3,     6,     3,
       3,     6,     3,   171,     6,     3,     6,     4,     4,     4,
       4,     4,     4,     3,   173,     6,     4,     6,     4,     4,
       4,     4,     4,   173,     4,     4,     4,     4,   171,     4,
     171,     3,   171,     6,   171,   171,     4,     8,   171,     8,
       4,   173,     8,   171,   171,   171,   171,   171,   171,   170,
     170,   170,   170,   170,   170,   170,   170,     3,     8,   170,
     170,     4,   170,     4,     4,   171,   173,     4,   170,     5,
       4,     4,     7,     4,     4,   525,   591,   597,   407,   839,
     413,   170,   842,   813,   170,   845,   171,   839,   848,   845,
     848,   845,   839,   853,   369,   842,   856,   173,   845,   859,
     853,   848,   839,   848,   677,   839,   853,   171,   833,   856,
     839,   848,   872,   842,   848,   838,   845,   861,   878,   848,
     878,   859,   457,   883,   853,   872,   842,   856,   868,   845,
     839,   878,   848,   878,   851,   841,   883,   853,   839,   848,
     425,  1009,   839,   872,   853,   850,   839,   856,   847,   878,
     844,   848,   842,   839,   883,   848,   853,   839,   845,   856,
     853,   839,   848,   856,   839,   449,   848,   883,   839,   878,
     848,   853,   839,   848,   856,   839,   839,   848,   454,   858,
     880,   848,   428,   878,   848,   848,   439,   856,   642,   854,
    1014,   872,   625,   474,   592,   596,   884,   480,   477,  1025,
    1042,  1059,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1009,
      -1,  1009,    -1,    -1,  1014,    -1,    -1,    -1,    -1,    -1,
      -1,  1014,  1009,    -1,  1009,  1025,    -1,  1014,    -1,    -1,
      -1,    -1,  1009,    -1,    -1,  1009,    -1,    -1,  1025,    -1,
    1009,    -1,    -1,    -1,    -1,  1014,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1009,    -1,    -1,  1025,    -1,  1014,    -1,
    1009,    -1,    -1,    -1,    -1,  1014,    -1,    -1,    -1,  1025,
      -1,    -1,  1009,    -1,    -1,    -1,  1009,  1014,    -1,    -1,
      -1,  1014,    -1,  1009,    -1,    -1,    -1,  1009,    -1,    -1,
      -1,  1009,  1014,    -1,  1009,    -1,    -1,    -1,  1009,    -1,
      -1,    -1,  1009,    -1,    -1,  1009,  1009
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
      91,    92,    97,   107,   110,   117,   118,   121,   122,   205,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     225,   226,   227,   228,   243,   245,   251,   253,   290,   299,
     313,   323,   347,   351,   359,   385,   415,   417,   419,   430,
     432,   434,   457,   469,   470,   478,   480,   518,    14,    15,
      18,    21,   205,   230,   231,   234,   236,   239,   242,   415,
     417,    64,    65,    66,    79,    83,    84,    85,    93,    96,
     104,   205,   216,   217,   218,   219,   220,   221,   226,   227,
     331,   332,   333,   335,   337,   339,   341,   343,   345,   347,
     350,   385,   403,   415,   417,   419,   430,   432,   434,   454,
      80,   205,   343,   345,   385,   411,   412,   413,   415,   417,
      92,    98,    99,   100,   101,   102,   103,   105,   205,   385,
     415,   417,   427,   428,   429,   430,   432,   434,   436,   440,
     442,   444,   446,   448,   450,   452,   359,    33,    69,    71,
      72,    75,    76,    77,   205,   271,   369,   370,   371,   372,
     373,   374,   375,   377,   379,   381,   382,   384,   415,   417,
      70,    73,    74,   205,   271,   373,   379,   393,   394,   395,
     396,   397,   399,   400,   401,   402,   415,   417,   108,   109,
     205,   307,   308,   309,   311,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   142,   143,
     205,   415,   417,   484,   485,   486,   487,   489,   491,   492,
     494,   495,   496,   499,   501,   502,   503,   506,   508,   510,
     145,   530,   531,   532,    12,   522,   523,   524,     6,     3,
       4,     8,     3,   211,   527,   513,   515,   517,     4,     3,
       8,   519,   229,   246,     4,     4,     4,   431,   433,   435,
     244,   252,   254,     4,     4,     4,     4,     4,     4,     4,
     224,   324,   360,   386,   352,   416,   418,   348,   291,   458,
     420,   300,   314,     4,   471,   479,   481,     3,     8,   235,
     237,   240,     4,     3,     8,   336,   338,   340,   404,   334,
     342,     4,   346,   344,   455,     3,     8,   414,     3,     8,
     453,   441,   443,   447,   445,   451,   449,   437,     8,     3,
       8,   376,   272,     4,   380,   378,   383,     4,     8,     3,
     398,     4,     4,     8,     3,   310,   312,     3,     8,     4,
     488,   490,     4,   493,     4,     4,   497,   500,     4,     4,
     504,   507,   509,   511,     3,     8,   533,     3,     8,   525,
       3,     8,   190,   190,   170,     4,     4,     4,     4,     4,
     209,     4,     4,     4,   173,   173,   173,     4,     4,     4,
       4,     4,     4,   171,   171,   171,   173,   172,   172,   171,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   171,     4,     4,     4,   215,     4,     4,
       4,   173,   231,     4,     4,     4,     4,     4,     4,   171,
       4,     4,     4,   332,     4,   412,     4,     4,     4,     4,
       4,     4,     4,     4,   429,     4,     4,   171,     4,     4,
       4,   173,   371,     4,   173,   173,   395,     4,     4,   308,
     173,     4,     4,   171,     4,   171,   171,     4,     4,   173,
     173,     4,     4,     4,     4,   485,     4,   531,     4,   523,
       4,     7,     7,   190,   190,   190,     7,     7,     7,   170,
     170,   170,     7,     7,     5,   170,     5,     5,     5,     5,
     192,   194,   170,    87,    88,    89,    90,   349,     5,     5,
       5,     5,     7,     7,   194,     7,     5,   201,    16,    17,
     238,    19,    20,   241,   170,   170,   170,     5,   170,   170,
     201,   170,     7,   170,   201,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   190,
     170,   170,   170,    17,   136,   498,   137,   138,   139,   140,
     141,   173,   505,   170,   170,   170,     5,     5,   190,   214,
     530,   522,   230,    23,   247,   248,   249,    33,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,   205,   259,   260,   261,   264,
     266,   268,   270,   271,   273,   274,   275,   276,   277,   278,
     279,   280,   282,   284,   286,   288,   289,   259,     7,   255,
     256,   257,     7,   325,   326,   327,     7,   363,   364,   365,
       7,   387,   388,   389,     7,   353,   354,   355,    98,    99,
     100,   101,   103,   292,   293,   294,   295,   296,   297,   298,
       7,   459,   460,     7,   421,   422,   423,     7,   301,   302,
     303,   111,   112,   113,   114,   115,   116,   315,   316,   317,
     318,   319,   320,   321,   322,   119,   120,   205,   415,   417,
     472,   473,   474,   476,   484,   202,     7,   405,   406,   407,
     106,   436,   438,   456,     7,   534,   535,   255,     8,     8,
       8,     8,   250,     3,     8,   262,   265,   267,   269,     4,
       4,     4,     4,     4,   281,   283,   285,   287,     4,     4,
       4,     4,     4,     3,     8,     8,   258,     6,     3,   328,
       6,     3,   366,     6,     3,   390,     6,     3,   356,     6,
       3,     3,     6,   461,     3,     6,   424,     6,     3,   304,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
     475,   477,     3,     8,     8,   170,   203,   204,   408,     6,
       3,   439,     8,   536,     3,     6,     6,     4,   248,     4,
       4,     4,     4,   171,   173,   171,   173,   171,     4,     4,
       4,     4,   171,   171,   171,   171,   173,   260,   259,   257,
     331,   327,   369,   365,   393,   389,   205,   216,   217,   218,
     219,   220,   221,   226,   227,   271,   323,   341,   343,   345,
     347,   357,   358,   385,   415,   417,   430,   432,   434,   454,
     355,   293,    94,    95,   205,   271,   359,   385,   415,   417,
     430,   432,   434,   462,   463,   464,   465,   466,   468,   460,
     427,   423,   307,   303,   171,   171,   171,   171,   171,   171,
     316,     4,     4,   473,     6,     3,   411,   407,     4,   146,
     148,   149,   205,   271,   415,   417,   537,   538,   539,   540,
     542,   535,   170,    34,    35,    36,    37,   263,   170,   170,
     170,   170,   170,   170,   170,     8,     8,     8,     8,     3,
       8,   467,     4,     8,     3,     8,     8,   170,   170,   170,
       8,   201,   543,     4,   541,     3,     8,   358,     4,   173,
     464,     4,   171,     4,   538,   170,     5,   170,     7,   544,
     545,   546,     3,     6,   147,   150,   151,   152,   547,   548,
     549,   551,   552,   553,   545,   550,     4,     4,     4,     3,
       8,     4,   173,   171,   171,   548,   170
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
     215,   216,   217,   218,   219,   220,   221,   222,   224,   223,
     225,   226,   227,   229,   228,   230,   230,   231,   231,   231,
     231,   231,   231,   231,   233,   232,   235,   234,   237,   236,
     238,   238,   240,   239,   241,   241,   242,   244,   243,   246,
     245,   247,   247,   248,   250,   249,   252,   251,   254,   253,
     255,   255,   256,   256,   258,   257,   259,   259,   260,   260,
     260,   260,   260,   260,   260,   260,   260,   260,   260,   260,
     260,   260,   260,   260,   260,   260,   260,   260,   262,   261,
     263,   263,   263,   263,   265,   264,   267,   266,   269,   268,
     270,   272,   271,   273,   274,   275,   276,   277,   278,   279,
     281,   280,   283,   282,   285,   284,   287,   286,   288,   289,
     291,   290,   292,   292,   293,   293,   293,   293,   293,   294,
     295,   296,   297,   298,   300,   299,   301,   301,   302,   302,
     304,   303,   306,   305,   307,   307,   307,   308,   308,   310,
     309,   312,   311,   314,   313,   315,   315,   316,   316,   316,
     316,   316,   316,   317,   318,   319,   320,   321,   322,   324,
     323,   325,   325,   326,   326,   328,   327,   330,   329,   331,
     331,   332,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   332,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   332,   332,   332,   332,   332,   332,   332,   334,   333,
     336,   335,   338,   337,   340,   339,   342,   341,   344,   343,
     346,   345,   348,   347,   349,   349,   349,   349,   350,   352,
     351,   353,   353,   354,   354,   356,   355,   357,   357,   358,
     358,   358,   358,   358,   358,   358,   358,   358,   358,   358,
     358,   358,   358,   358,   358,   358,   358,   358,   358,   358,
     358,   360,   359,   362,   361,   363,   363,   364,   364,   366,
     365,   368,   367,   369,   369,   370,   370,   371,   371,   371,
     371,   371,   371,   371,   371,   371,   371,   372,   373,   374,
     376,   375,   378,   377,   380,   379,   381,   383,   382,   384,
     386,   385,   387,   387,   388,   388,   390,   389,   392,   391,
     393,   393,   394,   394,   395,   395,   395,   395,   395,   395,
     395,   395,   395,   396,   398,   397,   399,   400,   401,   402,
     404,   403,   405,   405,   406,   406,   408,   407,   410,   409,
     411,   411,   412,   412,   412,   412,   412,   412,   412,   414,
     413,   416,   415,   418,   417,   420,   419,   421,   421,   422,
     422,   424,   423,   426,   425,   427,   427,   428,   428,   429,
     429,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   431,   430,   433,   432,   435,   434,
     437,   436,   439,   438,   441,   440,   443,   442,   445,   444,
     447,   446,   449,   448,   451,   450,   453,   452,   455,   454,
     456,   456,   458,   457,   459,   459,   461,   460,   462,   462,
     463,   463,   464,   464,   464,   464,   464,   464,   464,   464,
     464,   464,   464,   465,   467,   466,   468,   469,   471,   470,
     472,   472,   473,   473,   473,   473,   473,   475,   474,   477,
     476,   479,   478,   481,   480,   483,   482,   484,   484,   485,
     485,   485,   485,   485,   485,   485,   485,   485,   485,   485,
     485,   485,   485,   485,   485,   485,   485,   486,   488,   487,
     490,   489,   491,   493,   492,   494,   495,   497,   496,   498,
     498,   500,   499,   501,   502,   504,   503,   505,   505,   505,
     505,   505,   507,   506,   509,   508,   511,   510,   513,   512,
     515,   514,   517,   516,   519,   518,   521,   520,   522,   522,
     523,   525,   524,   527,   526,   529,   528,   530,   530,   531,
     533,   532,   534,   534,   536,   535,   537,   537,   538,   538,
     538,   538,   538,   538,   538,   539,   541,   540,   543,   542,
     544,   544,   546,   545,   547,   547,   548,   548,   548,   548,
     550,   549,   551,   552,   553
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
       1,     3,     3,     3,     3,     3,     3,     3,     0,     4,
       3,     3,     3,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       1,     1,     0,     4,     1,     1,     3,     0,     6,     0,
       6,     1,     3,     1,     0,     4,     0,     6,     0,     6,
       0,     1,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       3,     0,     4,     3,     3,     3,     3,     3,     3,     3,
       0,     4,     0,     4,     0,     4,     0,     4,     3,     3,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     1,     1,     1,     1,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     1,     0,     6,     1,     3,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     3,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     0,     4,     1,
       1,     0,     4,     3,     3,     0,     4,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     0,     6,     0,     6,     0,     4,     1,     3,     1,
       0,     6,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     0,     6,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       0,     4,     3,     3,     3
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
     476,   479,   484,   489,   494,   499,   504,   509,   514,   514,
     522,   527,   532,   538,   538,   549,   550,   553,   554,   555,
     556,   557,   558,   559,   562,   562,   571,   571,   581,   581,
     588,   589,   592,   592,   599,   601,   605,   611,   611,   623,
     623,   633,   634,   636,   638,   638,   656,   656,   668,   668,
     678,   679,   682,   683,   686,   686,   696,   697,   700,   701,
     702,   703,   704,   705,   706,   707,   708,   709,   710,   711,
     712,   713,   714,   715,   716,   717,   718,   719,   722,   722,
     729,   730,   731,   732,   735,   735,   743,   743,   751,   751,
     759,   764,   764,   772,   777,   782,   787,   792,   797,   802,
     807,   807,   815,   815,   823,   823,   831,   831,   839,   844,
     849,   849,   859,   860,   863,   864,   865,   866,   867,   870,
     875,   880,   885,   890,   895,   895,   905,   906,   909,   910,
     913,   913,   923,   923,   933,   934,   935,   938,   939,   942,
     942,   950,   950,   958,   958,   969,   970,   973,   974,   975,
     976,   977,   978,   981,   986,   991,   996,  1001,  1006,  1014,
    1014,  1027,  1028,  1031,  1032,  1039,  1039,  1065,  1065,  1076,
    1077,  1081,  1082,  1083,  1084,  1085,  1086,  1087,  1088,  1089,
    1090,  1091,  1092,  1093,  1094,  1095,  1096,  1097,  1098,  1099,
    1100,  1101,  1102,  1103,  1104,  1105,  1106,  1107,  1110,  1110,
    1118,  1118,  1126,  1126,  1134,  1134,  1142,  1142,  1150,  1150,
    1158,  1158,  1168,  1168,  1175,  1176,  1177,  1178,  1181,  1188,
    1188,  1199,  1200,  1204,  1205,  1208,  1208,  1216,  1217,  1220,
    1221,  1222,  1223,  1224,  1225,  1226,  1227,  1228,  1229,  1230,
    1231,  1232,  1233,  1234,  1235,  1236,  1237,  1238,  1239,  1240,
    1241,  1248,  1248,  1261,  1261,  1270,  1271,  1274,  1275,  1280,
    1280,  1295,  1295,  1309,  1310,  1313,  1314,  1317,  1318,  1319,
    1320,  1321,  1322,  1323,  1324,  1325,  1326,  1329,  1331,  1336,
    1338,  1338,  1346,  1346,  1354,  1354,  1362,  1364,  1364,  1372,
    1381,  1381,  1393,  1394,  1399,  1400,  1405,  1405,  1417,  1417,
    1429,  1430,  1435,  1436,  1441,  1442,  1443,  1444,  1445,  1446,
    1447,  1448,  1449,  1452,  1454,  1454,  1462,  1464,  1466,  1471,
    1479,  1479,  1491,  1492,  1495,  1496,  1499,  1499,  1509,  1509,
    1519,  1520,  1523,  1524,  1525,  1526,  1527,  1528,  1529,  1532,
    1532,  1540,  1540,  1565,  1565,  1595,  1595,  1605,  1606,  1609,
    1610,  1613,  1613,  1622,  1622,  1631,  1632,  1635,  1636,  1640,
    1641,  1642,  1643,  1644,  1645,  1646,  1647,  1648,  1649,  1650,
    1651,  1652,  1653,  1654,  1657,  1657,  1665,  1665,  1673,  1673,
    1681,  1681,  1689,  1689,  1699,  1699,  1707,  1707,  1715,  1715,
    1723,  1723,  1731,  1731,  1739,  1739,  1747,  1747,  1760,  1760,
    1770,  1771,  1777,  1777,  1787,  1788,  1791,  1791,  1801,  1802,
    1805,  1806,  1809,  1810,  1811,  1812,  1813,  1814,  1815,  1816,
    1817,  1818,  1819,  1822,  1824,  1824,  1832,  1841,  1848,  1848,
    1858,  1859,  1862,  1863,  1864,  1865,  1866,  1869,  1869,  1877,
    1877,  1888,  1888,  1926,  1926,  1938,  1938,  1948,  1949,  1952,
    1953,  1954,  1955,  1956,  1957,  1958,  1959,  1960,  1961,  1962,
    1963,  1964,  1965,  1966,  1967,  1968,  1969,  1972,  1977,  1977,
    1985,  1985,  1993,  1998,  1998,  2006,  2011,  2016,  2016,  2024,
    2025,  2028,  2028,  2036,  2041,  2046,  2046,  2054,  2057,  2060,
    2063,  2066,  2072,  2072,  2080,  2080,  2088,  2088,  2099,  2099,
    2106,  2106,  2113,  2113,  2120,  2120,  2131,  2131,  2141,  2142,
    2146,  2149,  2149,  2164,  2164,  2174,  2174,  2185,  2186,  2190,
    2194,  2194,  2206,  2207,  2211,  2211,  2219,  2220,  2223,  2224,
    2225,  2226,  2227,  2228,  2229,  2232,  2237,  2237,  2245,  2245,
    2255,  2256,  2259,  2259,  2267,  2268,  2271,  2272,  2273,  2274,
    2277,  2277,  2285,  2290,  2295
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
#line 2300 "dhcp4_parser.yy" // lalr1.cc:1243


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
