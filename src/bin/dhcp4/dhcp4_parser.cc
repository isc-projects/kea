// A Bison parser, made by GNU Bison 3.4.2.

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
#line 34 "dhcp4_parser.yy"

#include <dhcp4/parser_context.h>

#line 51 "dhcp4_parser.cc"


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

#line 14 "dhcp4_parser.yy"
namespace isc { namespace dhcp {
#line 143 "dhcp4_parser.cc"


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
      case 204: // value
      case 208: // map_value
      case 249: // ddns_replace_client_name_value
      case 268: // socket_type
      case 271: // outbound_interface_value
      case 293: // db_type
      case 380: // hr_mode
      case 535: // ncr_protocol_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 187: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 186: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 185: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 184: // "constant string"
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
      case 204: // value
      case 208: // map_value
      case 249: // ddns_replace_client_name_value
      case 268: // socket_type
      case 271: // outbound_interface_value
      case 293: // db_type
      case 380: // hr_mode
      case 535: // ncr_protocol_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 187: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 186: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 185: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 184: // "constant string"
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
      case 204: // value
      case 208: // map_value
      case 249: // ddns_replace_client_name_value
      case 268: // socket_type
      case 271: // outbound_interface_value
      case 293: // db_type
      case 380: // hr_mode
      case 535: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 187: // "boolean"
        value.move< bool > (that.value);
        break;

      case 186: // "floating point"
        value.move< double > (that.value);
        break;

      case 185: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 184: // "constant string"
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
      case 184: // "constant string"
#line 266 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < std::string > (); }
#line 405 "dhcp4_parser.cc"
        break;

      case 185: // "integer"
#line 266 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 411 "dhcp4_parser.cc"
        break;

      case 186: // "floating point"
#line 266 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < double > (); }
#line 417 "dhcp4_parser.cc"
        break;

      case 187: // "boolean"
#line 266 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < bool > (); }
#line 423 "dhcp4_parser.cc"
        break;

      case 204: // value
#line 266 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 429 "dhcp4_parser.cc"
        break;

      case 208: // map_value
#line 266 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 435 "dhcp4_parser.cc"
        break;

      case 249: // ddns_replace_client_name_value
#line 266 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 441 "dhcp4_parser.cc"
        break;

      case 268: // socket_type
#line 266 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 447 "dhcp4_parser.cc"
        break;

      case 271: // outbound_interface_value
#line 266 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 453 "dhcp4_parser.cc"
        break;

      case 293: // db_type
#line 266 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 459 "dhcp4_parser.cc"
        break;

      case 380: // hr_mode
#line 266 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 465 "dhcp4_parser.cc"
        break;

      case 535: // ncr_protocol_value
#line 266 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 471 "dhcp4_parser.cc"
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
      case 204: // value
      case 208: // map_value
      case 249: // ddns_replace_client_name_value
      case 268: // socket_type
      case 271: // outbound_interface_value
      case 293: // db_type
      case 380: // hr_mode
      case 535: // ncr_protocol_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 187: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 186: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 185: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 184: // "constant string"
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
#line 275 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 738 "dhcp4_parser.cc"
    break;

  case 4:
#line 276 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.CONFIG; }
#line 744 "dhcp4_parser.cc"
    break;

  case 6:
#line 277 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.DHCP4; }
#line 750 "dhcp4_parser.cc"
    break;

  case 8:
#line 278 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 756 "dhcp4_parser.cc"
    break;

  case 10:
#line 279 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.SUBNET4; }
#line 762 "dhcp4_parser.cc"
    break;

  case 12:
#line 280 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.POOLS; }
#line 768 "dhcp4_parser.cc"
    break;

  case 14:
#line 281 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 774 "dhcp4_parser.cc"
    break;

  case 16:
#line 282 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.DHCP4; }
#line 780 "dhcp4_parser.cc"
    break;

  case 18:
#line 283 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 786 "dhcp4_parser.cc"
    break;

  case 20:
#line 284 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 792 "dhcp4_parser.cc"
    break;

  case 22:
#line 285 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 798 "dhcp4_parser.cc"
    break;

  case 24:
#line 286 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 804 "dhcp4_parser.cc"
    break;

  case 26:
#line 287 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.LOGGING; }
#line 810 "dhcp4_parser.cc"
    break;

  case 28:
#line 288 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 816 "dhcp4_parser.cc"
    break;

  case 30:
#line 296 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 822 "dhcp4_parser.cc"
    break;

  case 31:
#line 297 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 828 "dhcp4_parser.cc"
    break;

  case 32:
#line 298 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp4_parser.cc"
    break;

  case 33:
#line 299 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp4_parser.cc"
    break;

  case 34:
#line 300 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp4_parser.cc"
    break;

  case 35:
#line 301 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 852 "dhcp4_parser.cc"
    break;

  case 36:
#line 302 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 858 "dhcp4_parser.cc"
    break;

  case 37:
#line 305 "dhcp4_parser.yy"
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 867 "dhcp4_parser.cc"
    break;

  case 38:
#line 310 "dhcp4_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 878 "dhcp4_parser.cc"
    break;

  case 39:
#line 315 "dhcp4_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 888 "dhcp4_parser.cc"
    break;

  case 40:
#line 321 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 894 "dhcp4_parser.cc"
    break;

  case 43:
#line 328 "dhcp4_parser.yy"
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 903 "dhcp4_parser.cc"
    break;

  case 44:
#line 332 "dhcp4_parser.yy"
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 913 "dhcp4_parser.cc"
    break;

  case 45:
#line 339 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 922 "dhcp4_parser.cc"
    break;

  case 46:
#line 342 "dhcp4_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
}
#line 930 "dhcp4_parser.cc"
    break;

  case 49:
#line 350 "dhcp4_parser.yy"
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 939 "dhcp4_parser.cc"
    break;

  case 50:
#line 354 "dhcp4_parser.yy"
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 948 "dhcp4_parser.cc"
    break;

  case 51:
#line 361 "dhcp4_parser.yy"
    {
    // List parsing about to start
}
#line 956 "dhcp4_parser.cc"
    break;

  case 52:
#line 363 "dhcp4_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 965 "dhcp4_parser.cc"
    break;

  case 55:
#line 372 "dhcp4_parser.yy"
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 974 "dhcp4_parser.cc"
    break;

  case 56:
#line 376 "dhcp4_parser.yy"
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 983 "dhcp4_parser.cc"
    break;

  case 57:
#line 387 "dhcp4_parser.yy"
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 994 "dhcp4_parser.cc"
    break;

  case 58:
#line 397 "dhcp4_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1005 "dhcp4_parser.cc"
    break;

  case 59:
#line 402 "dhcp4_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1018 "dhcp4_parser.cc"
    break;

  case 68:
#line 426 "dhcp4_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 1031 "dhcp4_parser.cc"
    break;

  case 69:
#line 433 "dhcp4_parser.yy"
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1041 "dhcp4_parser.cc"
    break;

  case 70:
#line 441 "dhcp4_parser.yy"
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1051 "dhcp4_parser.cc"
    break;

  case 71:
#line 445 "dhcp4_parser.yy"
    {
    // No global parameter is required
    // parsing completed
}
#line 1060 "dhcp4_parser.cc"
    break;

  case 122:
#line 506 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1069 "dhcp4_parser.cc"
    break;

  case 123:
#line 511 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1078 "dhcp4_parser.cc"
    break;

  case 124:
#line 516 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1087 "dhcp4_parser.cc"
    break;

  case 125:
#line 521 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1096 "dhcp4_parser.cc"
    break;

  case 126:
#line 526 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1105 "dhcp4_parser.cc"
    break;

  case 127:
#line 531 "dhcp4_parser.yy"
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1114 "dhcp4_parser.cc"
    break;

  case 128:
#line 536 "dhcp4_parser.yy"
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1123 "dhcp4_parser.cc"
    break;

  case 129:
#line 541 "dhcp4_parser.yy"
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1132 "dhcp4_parser.cc"
    break;

  case 130:
#line 546 "dhcp4_parser.yy"
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1141 "dhcp4_parser.cc"
    break;

  case 131:
#line 551 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1149 "dhcp4_parser.cc"
    break;

  case 132:
#line 553 "dhcp4_parser.yy"
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1159 "dhcp4_parser.cc"
    break;

  case 133:
#line 559 "dhcp4_parser.yy"
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1168 "dhcp4_parser.cc"
    break;

  case 134:
#line 564 "dhcp4_parser.yy"
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1177 "dhcp4_parser.cc"
    break;

  case 135:
#line 569 "dhcp4_parser.yy"
    {
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1186 "dhcp4_parser.cc"
    break;

  case 136:
#line 574 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1195 "dhcp4_parser.cc"
    break;

  case 137:
#line 579 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1204 "dhcp4_parser.cc"
    break;

  case 138:
#line 584 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1213 "dhcp4_parser.cc"
    break;

  case 139:
#line 589 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1221 "dhcp4_parser.cc"
    break;

  case 140:
#line 591 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1230 "dhcp4_parser.cc"
    break;

  case 141:
#line 597 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1238 "dhcp4_parser.cc"
    break;

  case 142:
#line 600 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1246 "dhcp4_parser.cc"
    break;

  case 143:
#line 603 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1254 "dhcp4_parser.cc"
    break;

  case 144:
#line 606 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1262 "dhcp4_parser.cc"
    break;

  case 145:
#line 609 "dhcp4_parser.yy"
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1271 "dhcp4_parser.cc"
    break;

  case 146:
#line 615 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1279 "dhcp4_parser.cc"
    break;

  case 147:
#line 617 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1289 "dhcp4_parser.cc"
    break;

  case 148:
#line 623 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1297 "dhcp4_parser.cc"
    break;

  case 149:
#line 625 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1307 "dhcp4_parser.cc"
    break;

  case 150:
#line 631 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1315 "dhcp4_parser.cc"
    break;

  case 151:
#line 633 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1325 "dhcp4_parser.cc"
    break;

  case 152:
#line 639 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1333 "dhcp4_parser.cc"
    break;

  case 153:
#line 641 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1343 "dhcp4_parser.cc"
    break;

  case 154:
#line 647 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1354 "dhcp4_parser.cc"
    break;

  case 155:
#line 652 "dhcp4_parser.yy"
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1364 "dhcp4_parser.cc"
    break;

  case 165:
#line 671 "dhcp4_parser.yy"
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1374 "dhcp4_parser.cc"
    break;

  case 166:
#line 675 "dhcp4_parser.yy"
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1383 "dhcp4_parser.cc"
    break;

  case 167:
#line 680 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1394 "dhcp4_parser.cc"
    break;

  case 168:
#line 685 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1403 "dhcp4_parser.cc"
    break;

  case 169:
#line 690 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1411 "dhcp4_parser.cc"
    break;

  case 170:
#line 692 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1420 "dhcp4_parser.cc"
    break;

  case 171:
#line 697 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1426 "dhcp4_parser.cc"
    break;

  case 172:
#line 698 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1432 "dhcp4_parser.cc"
    break;

  case 173:
#line 701 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1440 "dhcp4_parser.cc"
    break;

  case 174:
#line 703 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1449 "dhcp4_parser.cc"
    break;

  case 175:
#line 708 "dhcp4_parser.yy"
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1457 "dhcp4_parser.cc"
    break;

  case 176:
#line 710 "dhcp4_parser.yy"
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1465 "dhcp4_parser.cc"
    break;

  case 177:
#line 714 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1474 "dhcp4_parser.cc"
    break;

  case 178:
#line 720 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1485 "dhcp4_parser.cc"
    break;

  case 179:
#line 725 "dhcp4_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1496 "dhcp4_parser.cc"
    break;

  case 180:
#line 732 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1507 "dhcp4_parser.cc"
    break;

  case 181:
#line 737 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1516 "dhcp4_parser.cc"
    break;

  case 185:
#line 747 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1524 "dhcp4_parser.cc"
    break;

  case 186:
#line 749 "dhcp4_parser.yy"
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
#line 1544 "dhcp4_parser.cc"
    break;

  case 187:
#line 765 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1555 "dhcp4_parser.cc"
    break;

  case 188:
#line 770 "dhcp4_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1566 "dhcp4_parser.cc"
    break;

  case 189:
#line 777 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1577 "dhcp4_parser.cc"
    break;

  case 190:
#line 782 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1586 "dhcp4_parser.cc"
    break;

  case 195:
#line 795 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1596 "dhcp4_parser.cc"
    break;

  case 196:
#line 799 "dhcp4_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1606 "dhcp4_parser.cc"
    break;

  case 220:
#line 832 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1614 "dhcp4_parser.cc"
    break;

  case 221:
#line 834 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1623 "dhcp4_parser.cc"
    break;

  case 222:
#line 839 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1629 "dhcp4_parser.cc"
    break;

  case 223:
#line 840 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1635 "dhcp4_parser.cc"
    break;

  case 224:
#line 841 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1641 "dhcp4_parser.cc"
    break;

  case 225:
#line 842 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1647 "dhcp4_parser.cc"
    break;

  case 226:
#line 845 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1655 "dhcp4_parser.cc"
    break;

  case 227:
#line 847 "dhcp4_parser.yy"
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1665 "dhcp4_parser.cc"
    break;

  case 228:
#line 853 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1673 "dhcp4_parser.cc"
    break;

  case 229:
#line 855 "dhcp4_parser.yy"
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1683 "dhcp4_parser.cc"
    break;

  case 230:
#line 861 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1691 "dhcp4_parser.cc"
    break;

  case 231:
#line 863 "dhcp4_parser.yy"
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1701 "dhcp4_parser.cc"
    break;

  case 232:
#line 869 "dhcp4_parser.yy"
    {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1710 "dhcp4_parser.cc"
    break;

  case 233:
#line 874 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1718 "dhcp4_parser.cc"
    break;

  case 234:
#line 876 "dhcp4_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1728 "dhcp4_parser.cc"
    break;

  case 235:
#line 882 "dhcp4_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1737 "dhcp4_parser.cc"
    break;

  case 236:
#line 887 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1746 "dhcp4_parser.cc"
    break;

  case 237:
#line 892 "dhcp4_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1755 "dhcp4_parser.cc"
    break;

  case 238:
#line 897 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1764 "dhcp4_parser.cc"
    break;

  case 239:
#line 902 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1773 "dhcp4_parser.cc"
    break;

  case 240:
#line 907 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1782 "dhcp4_parser.cc"
    break;

  case 241:
#line 912 "dhcp4_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1791 "dhcp4_parser.cc"
    break;

  case 242:
#line 917 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1799 "dhcp4_parser.cc"
    break;

  case 243:
#line 919 "dhcp4_parser.yy"
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1809 "dhcp4_parser.cc"
    break;

  case 244:
#line 925 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1817 "dhcp4_parser.cc"
    break;

  case 245:
#line 927 "dhcp4_parser.yy"
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1827 "dhcp4_parser.cc"
    break;

  case 246:
#line 933 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1835 "dhcp4_parser.cc"
    break;

  case 247:
#line 935 "dhcp4_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1845 "dhcp4_parser.cc"
    break;

  case 248:
#line 941 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1853 "dhcp4_parser.cc"
    break;

  case 249:
#line 943 "dhcp4_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1863 "dhcp4_parser.cc"
    break;

  case 250:
#line 949 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1872 "dhcp4_parser.cc"
    break;

  case 251:
#line 954 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1881 "dhcp4_parser.cc"
    break;

  case 252:
#line 959 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1890 "dhcp4_parser.cc"
    break;

  case 253:
#line 965 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1901 "dhcp4_parser.cc"
    break;

  case 254:
#line 970 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1910 "dhcp4_parser.cc"
    break;

  case 262:
#line 986 "dhcp4_parser.yy"
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1919 "dhcp4_parser.cc"
    break;

  case 263:
#line 991 "dhcp4_parser.yy"
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1928 "dhcp4_parser.cc"
    break;

  case 264:
#line 996 "dhcp4_parser.yy"
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1937 "dhcp4_parser.cc"
    break;

  case 265:
#line 1001 "dhcp4_parser.yy"
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1946 "dhcp4_parser.cc"
    break;

  case 266:
#line 1006 "dhcp4_parser.yy"
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1955 "dhcp4_parser.cc"
    break;

  case 267:
#line 1011 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1966 "dhcp4_parser.cc"
    break;

  case 268:
#line 1016 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1975 "dhcp4_parser.cc"
    break;

  case 273:
#line 1029 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1985 "dhcp4_parser.cc"
    break;

  case 274:
#line 1033 "dhcp4_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1995 "dhcp4_parser.cc"
    break;

  case 275:
#line 1039 "dhcp4_parser.yy"
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2005 "dhcp4_parser.cc"
    break;

  case 276:
#line 1043 "dhcp4_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2015 "dhcp4_parser.cc"
    break;

  case 282:
#line 1058 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2023 "dhcp4_parser.cc"
    break;

  case 283:
#line 1060 "dhcp4_parser.yy"
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2033 "dhcp4_parser.cc"
    break;

  case 284:
#line 1066 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2041 "dhcp4_parser.cc"
    break;

  case 285:
#line 1068 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2050 "dhcp4_parser.cc"
    break;

  case 286:
#line 1074 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2061 "dhcp4_parser.cc"
    break;

  case 287:
#line 1079 "dhcp4_parser.yy"
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2071 "dhcp4_parser.cc"
    break;

  case 296:
#line 1097 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2080 "dhcp4_parser.cc"
    break;

  case 297:
#line 1102 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2089 "dhcp4_parser.cc"
    break;

  case 298:
#line 1107 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2098 "dhcp4_parser.cc"
    break;

  case 299:
#line 1112 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2107 "dhcp4_parser.cc"
    break;

  case 300:
#line 1117 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2116 "dhcp4_parser.cc"
    break;

  case 301:
#line 1122 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2125 "dhcp4_parser.cc"
    break;

  case 302:
#line 1130 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2136 "dhcp4_parser.cc"
    break;

  case 303:
#line 1135 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2145 "dhcp4_parser.cc"
    break;

  case 308:
#line 1155 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2155 "dhcp4_parser.cc"
    break;

  case 309:
#line 1159 "dhcp4_parser.yy"
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
#line 2181 "dhcp4_parser.cc"
    break;

  case 310:
#line 1181 "dhcp4_parser.yy"
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2191 "dhcp4_parser.cc"
    break;

  case 311:
#line 1185 "dhcp4_parser.yy"
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2201 "dhcp4_parser.cc"
    break;

  case 351:
#line 1236 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2209 "dhcp4_parser.cc"
    break;

  case 352:
#line 1238 "dhcp4_parser.yy"
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2219 "dhcp4_parser.cc"
    break;

  case 353:
#line 1244 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2227 "dhcp4_parser.cc"
    break;

  case 354:
#line 1246 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2237 "dhcp4_parser.cc"
    break;

  case 355:
#line 1252 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2245 "dhcp4_parser.cc"
    break;

  case 356:
#line 1254 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2255 "dhcp4_parser.cc"
    break;

  case 357:
#line 1260 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2263 "dhcp4_parser.cc"
    break;

  case 358:
#line 1262 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2273 "dhcp4_parser.cc"
    break;

  case 359:
#line 1268 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2281 "dhcp4_parser.cc"
    break;

  case 360:
#line 1270 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2291 "dhcp4_parser.cc"
    break;

  case 361:
#line 1276 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2299 "dhcp4_parser.cc"
    break;

  case 362:
#line 1278 "dhcp4_parser.yy"
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2309 "dhcp4_parser.cc"
    break;

  case 363:
#line 1284 "dhcp4_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2320 "dhcp4_parser.cc"
    break;

  case 364:
#line 1289 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2329 "dhcp4_parser.cc"
    break;

  case 365:
#line 1294 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2337 "dhcp4_parser.cc"
    break;

  case 366:
#line 1296 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2346 "dhcp4_parser.cc"
    break;

  case 367:
#line 1301 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2352 "dhcp4_parser.cc"
    break;

  case 368:
#line 1302 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2358 "dhcp4_parser.cc"
    break;

  case 369:
#line 1303 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2364 "dhcp4_parser.cc"
    break;

  case 370:
#line 1304 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2370 "dhcp4_parser.cc"
    break;

  case 371:
#line 1307 "dhcp4_parser.yy"
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2379 "dhcp4_parser.cc"
    break;

  case 372:
#line 1314 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2390 "dhcp4_parser.cc"
    break;

  case 373:
#line 1319 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2399 "dhcp4_parser.cc"
    break;

  case 378:
#line 1334 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2409 "dhcp4_parser.cc"
    break;

  case 379:
#line 1338 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 2417 "dhcp4_parser.cc"
    break;

  case 414:
#line 1384 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2428 "dhcp4_parser.cc"
    break;

  case 415:
#line 1389 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2437 "dhcp4_parser.cc"
    break;

  case 416:
#line 1397 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2446 "dhcp4_parser.cc"
    break;

  case 417:
#line 1400 "dhcp4_parser.yy"
    {
    // parsing completed
}
#line 2454 "dhcp4_parser.cc"
    break;

  case 422:
#line 1416 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2464 "dhcp4_parser.cc"
    break;

  case 423:
#line 1420 "dhcp4_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2476 "dhcp4_parser.cc"
    break;

  case 424:
#line 1431 "dhcp4_parser.yy"
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2486 "dhcp4_parser.cc"
    break;

  case 425:
#line 1435 "dhcp4_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2498 "dhcp4_parser.cc"
    break;

  case 441:
#line 1467 "dhcp4_parser.yy"
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2507 "dhcp4_parser.cc"
    break;

  case 443:
#line 1474 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2515 "dhcp4_parser.cc"
    break;

  case 444:
#line 1476 "dhcp4_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2525 "dhcp4_parser.cc"
    break;

  case 445:
#line 1482 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2533 "dhcp4_parser.cc"
    break;

  case 446:
#line 1484 "dhcp4_parser.yy"
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2543 "dhcp4_parser.cc"
    break;

  case 447:
#line 1490 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2551 "dhcp4_parser.cc"
    break;

  case 448:
#line 1492 "dhcp4_parser.yy"
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2561 "dhcp4_parser.cc"
    break;

  case 450:
#line 1500 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2569 "dhcp4_parser.cc"
    break;

  case 451:
#line 1502 "dhcp4_parser.yy"
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2579 "dhcp4_parser.cc"
    break;

  case 452:
#line 1508 "dhcp4_parser.yy"
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2588 "dhcp4_parser.cc"
    break;

  case 453:
#line 1517 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2599 "dhcp4_parser.cc"
    break;

  case 454:
#line 1522 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2608 "dhcp4_parser.cc"
    break;

  case 459:
#line 1541 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2618 "dhcp4_parser.cc"
    break;

  case 460:
#line 1545 "dhcp4_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2627 "dhcp4_parser.cc"
    break;

  case 461:
#line 1553 "dhcp4_parser.yy"
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2637 "dhcp4_parser.cc"
    break;

  case 462:
#line 1557 "dhcp4_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2646 "dhcp4_parser.cc"
    break;

  case 477:
#line 1590 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2654 "dhcp4_parser.cc"
    break;

  case 478:
#line 1592 "dhcp4_parser.yy"
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2664 "dhcp4_parser.cc"
    break;

  case 481:
#line 1602 "dhcp4_parser.yy"
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2673 "dhcp4_parser.cc"
    break;

  case 482:
#line 1607 "dhcp4_parser.yy"
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2682 "dhcp4_parser.cc"
    break;

  case 483:
#line 1615 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2693 "dhcp4_parser.cc"
    break;

  case 484:
#line 1620 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2702 "dhcp4_parser.cc"
    break;

  case 489:
#line 1635 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2712 "dhcp4_parser.cc"
    break;

  case 490:
#line 1639 "dhcp4_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2722 "dhcp4_parser.cc"
    break;

  case 491:
#line 1645 "dhcp4_parser.yy"
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2732 "dhcp4_parser.cc"
    break;

  case 492:
#line 1649 "dhcp4_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2742 "dhcp4_parser.cc"
    break;

  case 502:
#line 1668 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2750 "dhcp4_parser.cc"
    break;

  case 503:
#line 1670 "dhcp4_parser.yy"
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2760 "dhcp4_parser.cc"
    break;

  case 504:
#line 1676 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2768 "dhcp4_parser.cc"
    break;

  case 505:
#line 1678 "dhcp4_parser.yy"
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
#line 2795 "dhcp4_parser.cc"
    break;

  case 506:
#line 1701 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2803 "dhcp4_parser.cc"
    break;

  case 507:
#line 1703 "dhcp4_parser.yy"
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
#line 2832 "dhcp4_parser.cc"
    break;

  case 508:
#line 1731 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2843 "dhcp4_parser.cc"
    break;

  case 509:
#line 1736 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2852 "dhcp4_parser.cc"
    break;

  case 514:
#line 1749 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2862 "dhcp4_parser.cc"
    break;

  case 515:
#line 1753 "dhcp4_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2871 "dhcp4_parser.cc"
    break;

  case 516:
#line 1758 "dhcp4_parser.yy"
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2881 "dhcp4_parser.cc"
    break;

  case 517:
#line 1762 "dhcp4_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2890 "dhcp4_parser.cc"
    break;

  case 537:
#line 1793 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2898 "dhcp4_parser.cc"
    break;

  case 538:
#line 1795 "dhcp4_parser.yy"
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2908 "dhcp4_parser.cc"
    break;

  case 539:
#line 1801 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2916 "dhcp4_parser.cc"
    break;

  case 540:
#line 1803 "dhcp4_parser.yy"
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2926 "dhcp4_parser.cc"
    break;

  case 541:
#line 1809 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2934 "dhcp4_parser.cc"
    break;

  case 542:
#line 1811 "dhcp4_parser.yy"
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2944 "dhcp4_parser.cc"
    break;

  case 543:
#line 1817 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2952 "dhcp4_parser.cc"
    break;

  case 544:
#line 1819 "dhcp4_parser.yy"
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2962 "dhcp4_parser.cc"
    break;

  case 545:
#line 1825 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2973 "dhcp4_parser.cc"
    break;

  case 546:
#line 1830 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2982 "dhcp4_parser.cc"
    break;

  case 547:
#line 1835 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2990 "dhcp4_parser.cc"
    break;

  case 548:
#line 1837 "dhcp4_parser.yy"
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3000 "dhcp4_parser.cc"
    break;

  case 549:
#line 1843 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3008 "dhcp4_parser.cc"
    break;

  case 550:
#line 1845 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3018 "dhcp4_parser.cc"
    break;

  case 551:
#line 1851 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3026 "dhcp4_parser.cc"
    break;

  case 552:
#line 1853 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3036 "dhcp4_parser.cc"
    break;

  case 553:
#line 1859 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3044 "dhcp4_parser.cc"
    break;

  case 554:
#line 1861 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3054 "dhcp4_parser.cc"
    break;

  case 555:
#line 1867 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3062 "dhcp4_parser.cc"
    break;

  case 556:
#line 1869 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3072 "dhcp4_parser.cc"
    break;

  case 557:
#line 1875 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3080 "dhcp4_parser.cc"
    break;

  case 558:
#line 1877 "dhcp4_parser.yy"
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3090 "dhcp4_parser.cc"
    break;

  case 559:
#line 1883 "dhcp4_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3101 "dhcp4_parser.cc"
    break;

  case 560:
#line 1888 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3110 "dhcp4_parser.cc"
    break;

  case 561:
#line 1896 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3121 "dhcp4_parser.cc"
    break;

  case 562:
#line 1901 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3130 "dhcp4_parser.cc"
    break;

  case 565:
#line 1913 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3141 "dhcp4_parser.cc"
    break;

  case 566:
#line 1918 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3150 "dhcp4_parser.cc"
    break;

  case 569:
#line 1927 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3160 "dhcp4_parser.cc"
    break;

  case 570:
#line 1931 "dhcp4_parser.yy"
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3170 "dhcp4_parser.cc"
    break;

  case 587:
#line 1960 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3178 "dhcp4_parser.cc"
    break;

  case 588:
#line 1962 "dhcp4_parser.yy"
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3188 "dhcp4_parser.cc"
    break;

  case 589:
#line 1968 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3197 "dhcp4_parser.cc"
    break;

  case 590:
#line 1977 "dhcp4_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3206 "dhcp4_parser.cc"
    break;

  case 591:
#line 1984 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3217 "dhcp4_parser.cc"
    break;

  case 592:
#line 1989 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3226 "dhcp4_parser.cc"
    break;

  case 600:
#line 2005 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3234 "dhcp4_parser.cc"
    break;

  case 601:
#line 2007 "dhcp4_parser.yy"
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3244 "dhcp4_parser.cc"
    break;

  case 602:
#line 2013 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3252 "dhcp4_parser.cc"
    break;

  case 603:
#line 2015 "dhcp4_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3262 "dhcp4_parser.cc"
    break;

  case 604:
#line 2024 "dhcp4_parser.yy"
    {
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3273 "dhcp4_parser.cc"
    break;

  case 605:
#line 2029 "dhcp4_parser.yy"
    {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3284 "dhcp4_parser.cc"
    break;

  case 614:
#line 2048 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3293 "dhcp4_parser.cc"
    break;

  case 615:
#line 2053 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3301 "dhcp4_parser.cc"
    break;

  case 616:
#line 2055 "dhcp4_parser.yy"
    {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3311 "dhcp4_parser.cc"
    break;

  case 617:
#line 2061 "dhcp4_parser.yy"
    {
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3320 "dhcp4_parser.cc"
    break;

  case 618:
#line 2066 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3328 "dhcp4_parser.cc"
    break;

  case 619:
#line 2068 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3337 "dhcp4_parser.cc"
    break;

  case 620:
#line 2075 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3348 "dhcp4_parser.cc"
    break;

  case 621:
#line 2080 "dhcp4_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3359 "dhcp4_parser.cc"
    break;

  case 622:
#line 2087 "dhcp4_parser.yy"
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3369 "dhcp4_parser.cc"
    break;

  case 623:
#line 2091 "dhcp4_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3379 "dhcp4_parser.cc"
    break;

  case 644:
#line 2121 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3388 "dhcp4_parser.cc"
    break;

  case 645:
#line 2126 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3396 "dhcp4_parser.cc"
    break;

  case 646:
#line 2128 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3406 "dhcp4_parser.cc"
    break;

  case 647:
#line 2134 "dhcp4_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3415 "dhcp4_parser.cc"
    break;

  case 648:
#line 2139 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3423 "dhcp4_parser.cc"
    break;

  case 649:
#line 2141 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3433 "dhcp4_parser.cc"
    break;

  case 650:
#line 2147 "dhcp4_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3442 "dhcp4_parser.cc"
    break;

  case 651:
#line 2152 "dhcp4_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3451 "dhcp4_parser.cc"
    break;

  case 652:
#line 2157 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3459 "dhcp4_parser.cc"
    break;

  case 653:
#line 2159 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3468 "dhcp4_parser.cc"
    break;

  case 654:
#line 2165 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3474 "dhcp4_parser.cc"
    break;

  case 655:
#line 2166 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3480 "dhcp4_parser.cc"
    break;

  case 656:
#line 2169 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3488 "dhcp4_parser.cc"
    break;

  case 657:
#line 2171 "dhcp4_parser.yy"
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3498 "dhcp4_parser.cc"
    break;

  case 658:
#line 2178 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3506 "dhcp4_parser.cc"
    break;

  case 659:
#line 2180 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3516 "dhcp4_parser.cc"
    break;

  case 660:
#line 2187 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3525 "dhcp4_parser.cc"
    break;

  case 661:
#line 2193 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3534 "dhcp4_parser.cc"
    break;

  case 662:
#line 2199 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3542 "dhcp4_parser.cc"
    break;

  case 663:
#line 2201 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3551 "dhcp4_parser.cc"
    break;

  case 664:
#line 2207 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3559 "dhcp4_parser.cc"
    break;

  case 665:
#line 2209 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3569 "dhcp4_parser.cc"
    break;

  case 666:
#line 2216 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3577 "dhcp4_parser.cc"
    break;

  case 667:
#line 2218 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3587 "dhcp4_parser.cc"
    break;

  case 668:
#line 2225 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3595 "dhcp4_parser.cc"
    break;

  case 669:
#line 2227 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3605 "dhcp4_parser.cc"
    break;

  case 670:
#line 2236 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3613 "dhcp4_parser.cc"
    break;

  case 671:
#line 2238 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3622 "dhcp4_parser.cc"
    break;

  case 672:
#line 2243 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3630 "dhcp4_parser.cc"
    break;

  case 673:
#line 2245 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3639 "dhcp4_parser.cc"
    break;

  case 674:
#line 2250 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3647 "dhcp4_parser.cc"
    break;

  case 675:
#line 2252 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3656 "dhcp4_parser.cc"
    break;

  case 676:
#line 2257 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3667 "dhcp4_parser.cc"
    break;

  case 677:
#line 2262 "dhcp4_parser.yy"
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3677 "dhcp4_parser.cc"
    break;

  case 678:
#line 2268 "dhcp4_parser.yy"
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3687 "dhcp4_parser.cc"
    break;

  case 679:
#line 2272 "dhcp4_parser.yy"
    {
    // No config_control params are required
    // parsing completed
}
#line 3696 "dhcp4_parser.cc"
    break;

  case 684:
#line 2287 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3707 "dhcp4_parser.cc"
    break;

  case 685:
#line 2292 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3716 "dhcp4_parser.cc"
    break;

  case 686:
#line 2297 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3725 "dhcp4_parser.cc"
    break;

  case 687:
#line 2307 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3736 "dhcp4_parser.cc"
    break;

  case 688:
#line 2312 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3745 "dhcp4_parser.cc"
    break;

  case 689:
#line 2317 "dhcp4_parser.yy"
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3755 "dhcp4_parser.cc"
    break;

  case 690:
#line 2321 "dhcp4_parser.yy"
    {
    // parsing completed
}
#line 3763 "dhcp4_parser.cc"
    break;

  case 694:
#line 2337 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3774 "dhcp4_parser.cc"
    break;

  case 695:
#line 2342 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3783 "dhcp4_parser.cc"
    break;

  case 698:
#line 2354 "dhcp4_parser.yy"
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3793 "dhcp4_parser.cc"
    break;

  case 699:
#line 2358 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3801 "dhcp4_parser.cc"
    break;

  case 709:
#line 2375 "dhcp4_parser.yy"
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3810 "dhcp4_parser.cc"
    break;

  case 710:
#line 2380 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3818 "dhcp4_parser.cc"
    break;

  case 711:
#line 2382 "dhcp4_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3828 "dhcp4_parser.cc"
    break;

  case 712:
#line 2388 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3839 "dhcp4_parser.cc"
    break;

  case 713:
#line 2393 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3848 "dhcp4_parser.cc"
    break;

  case 716:
#line 2402 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3858 "dhcp4_parser.cc"
    break;

  case 717:
#line 2406 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3866 "dhcp4_parser.cc"
    break;

  case 725:
#line 2421 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3874 "dhcp4_parser.cc"
    break;

  case 726:
#line 2423 "dhcp4_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3884 "dhcp4_parser.cc"
    break;

  case 727:
#line 2429 "dhcp4_parser.yy"
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3893 "dhcp4_parser.cc"
    break;

  case 728:
#line 2434 "dhcp4_parser.yy"
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3902 "dhcp4_parser.cc"
    break;

  case 729:
#line 2439 "dhcp4_parser.yy"
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3911 "dhcp4_parser.cc"
    break;

  case 730:
#line 2444 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3919 "dhcp4_parser.cc"
    break;

  case 731:
#line 2446 "dhcp4_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 3929 "dhcp4_parser.cc"
    break;


#line 3933 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -900;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     385,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,    56,    28,    27,    29,    62,
      67,    79,    81,    83,   126,   133,   139,   194,   199,   236,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,    28,  -142,
      20,   167,    25,   580,    -8,   237,   -27,    66,   198,   -54,
     217,   -99,   100,  -900,    57,    77,   110,   166,   147,  -900,
    -900,  -900,  -900,  -900,   245,  -900,    40,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,   256,   266,   269,  -900,
    -900,  -900,  -900,  -900,  -900,   281,   299,   306,   316,   320,
     332,   333,   340,   362,  -900,   363,   364,   367,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,   374,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,    43,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,   375,  -900,    68,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,   376,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,    93,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,   131,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,   254,   290,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,   264,  -900,
    -900,   379,  -900,  -900,  -900,   380,  -900,  -900,   309,   324,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,   381,   382,  -900,  -900,  -900,  -900,   326,
     386,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,   141,  -900,  -900,  -900,   384,  -900,  -900,
     387,  -900,   388,   389,  -900,  -900,   390,   391,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,   158,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,   159,  -900,  -900,  -900,   392,   172,  -900,  -900,
    -900,  -900,    28,    28,  -900,   206,   393,   394,   399,   400,
     401,  -900,    20,  -900,   402,   404,   405,   223,   224,   227,
     412,   413,   414,   415,   416,   420,   242,   246,   248,   250,
     253,   252,   244,   257,   255,   438,   259,   260,   263,   440,
     447,   449,   451,   452,   453,   454,   456,   460,   462,   463,
     466,   467,   468,   470,   292,   475,   476,   478,   480,   482,
     484,   167,  -900,   486,   487,   488,   307,    25,  -900,   492,
     493,   497,   509,   510,   511,   317,   512,   516,   519,   580,
    -900,   520,    -8,  -900,   521,   523,   524,   525,   526,   527,
     529,   530,  -900,   237,  -900,   531,   532,   395,   565,   566,
     567,   396,  -900,    66,   569,   397,   398,  -900,   198,   570,
     571,   -13,  -900,   403,   574,   575,   406,   577,   407,   408,
     582,   583,   409,   410,   584,   585,   590,   594,   217,  -900,
     -99,  -900,   595,   417,   100,  -900,  -900,  -900,   597,   596,
     598,    28,    28,    28,  -900,   604,   605,   606,  -900,  -900,
    -900,   430,   431,   433,   612,   613,   599,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,   437,  -900,  -900,  -900,
     -16,   439,   441,   619,   621,   622,   623,   626,   450,   243,
     630,   631,   640,   641,   646,  -900,   650,   652,   653,   477,
     479,   657,  -900,   659,   142,   152,  -900,  -900,   481,   500,
     501,   665,   504,   505,  -900,   659,   506,   684,  -900,   508,
    -900,   659,   513,   514,   515,   517,   518,   522,   533,  -900,
     541,   542,  -900,   543,   544,   547,  -900,  -900,   548,  -900,
    -900,  -900,   549,    28,  -900,  -900,   550,   553,  -900,   554,
    -900,  -900,    14,   545,  -900,  -900,   -16,   555,   556,   557,
    -900,  -900,   688,  -900,  -900,    28,   167,   -99,  -900,  -900,
    -900,   100,    25,   672,  -900,  -900,  -900,   498,   498,   693,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,   696,
     697,   698,   700,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,   143,   709,   737,   739,    95,    73,   -14,   217,  -900,
    -900,   741,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,   742,  -900,  -900,  -900,  -900,   107,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,   693,  -900,   183,
     238,   239,   268,  -900,   280,  -900,  -900,  -900,  -900,  -900,
    -900,   746,   747,   748,   749,   751,  -900,  -900,  -900,  -900,
     752,   754,   755,   756,   757,   758,  -900,   283,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,   289,
    -900,   760,   764,  -900,  -900,   762,   766,  -900,  -900,   765,
     767,  -900,  -900,   768,   769,  -900,  -900,   770,   772,  -900,
    -900,  -900,  -900,  -900,  -900,    96,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,   121,  -900,  -900,   771,   775,  -900,  -900,
     773,   777,  -900,   759,   778,   779,   780,   781,   782,   293,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,   296,  -900,  -900,  -900,   783,  -900,   784,  -900,
    -900,  -900,   297,  -900,  -900,  -900,  -900,  -900,   303,  -900,
     202,  -900,   589,  -900,   785,   786,  -900,  -900,  -900,  -900,
     787,   788,  -900,  -900,  -900,  -900,   789,   672,  -900,   792,
     793,   794,   795,   607,   603,   615,   614,   617,   799,   800,
     801,   804,   624,   625,   627,   628,   629,   632,   498,  -900,
    -900,   498,  -900,   693,   580,  -900,   696,    66,  -900,   697,
     198,  -900,   698,   651,  -900,   700,   143,  -900,    64,   709,
    -900,   237,  -900,   737,   -54,  -900,   739,   633,   634,   635,
     636,   637,   638,    95,  -900,   807,   810,    73,  -900,   639,
     811,   642,   820,   -14,  -900,  -900,   -30,   741,  -900,  -900,
     819,   825,    -8,  -900,   742,   826,  -900,  -900,   645,  -900,
     339,   647,   648,   649,  -900,  -900,  -900,  -900,  -900,   654,
     655,   656,   658,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
     304,  -900,   310,  -900,   828,  -900,   829,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,   311,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,   830,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,   833,   840,  -900,  -900,  -900,
    -900,  -900,   837,  -900,   313,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,   662,   664,  -900,  -900,   667,  -900,    28,
    -900,  -900,   845,  -900,  -900,  -900,  -900,  -900,   323,  -900,
    -900,  -900,  -900,  -900,  -900,   671,   327,  -900,   659,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,   651,  -900,   855,   675,
    -900,    64,  -900,  -900,  -900,  -900,  -900,  -900,   864,   687,
     865,   -30,  -900,  -900,  -900,  -900,  -900,   689,  -900,  -900,
     776,  -900,   691,  -900,  -900,   875,  -900,  -900,   258,  -900,
      19,   875,  -900,  -900,   879,   881,   883,  -900,   330,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,   884,   704,   708,   710,
     894,    19,  -900,   717,  -900,  -900,  -900,   718,  -900,  -900,
    -900
  };

  const unsigned short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   165,     9,   310,    11,
     491,    13,   516,    15,   416,    17,   424,    19,   461,    21,
     275,    23,   622,    25,   689,    27,   678,    29,    47,    41,
       0,     0,     0,     0,     0,   518,     0,   426,   463,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     687,   670,   672,   674,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   676,   154,   180,     0,     0,     0,   537,
     539,   541,   178,   187,   189,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   131,     0,     0,     0,   139,   146,
     148,   302,   414,   453,   372,   504,   506,   365,   253,   565,
     508,   267,   286,     0,   591,   604,   620,   150,   152,   694,
     121,     0,    72,    74,    75,    76,    77,    78,   109,   110,
     111,    79,   107,    96,    97,    98,   115,   116,   117,   118,
     119,   120,   113,   114,    82,    83,   104,    84,    85,    86,
      90,    91,    80,   108,    81,    88,    89,   102,   103,   105,
      99,   100,   101,    87,    92,    93,    94,    95,   106,   112,
     167,   169,   173,     0,   164,     0,   156,   158,   159,   160,
     161,   162,   163,   353,   355,   357,   483,   351,   359,     0,
     363,   361,   561,   350,   314,   315,   316,   317,   318,   339,
     340,   341,   329,   330,   342,   343,   344,   345,   346,   347,
     348,   349,     0,   312,   321,   334,   335,   336,   322,   324,
     325,   327,   323,   319,   320,   337,   338,   326,   331,   332,
     333,   328,   502,   501,   497,   498,   496,     0,   493,   495,
     499,   500,   559,   547,   549,   553,   551,   557,   555,   543,
     536,   530,   534,   535,     0,   519,   520,   531,   532,   533,
     527,   522,   528,   524,   525,   526,   529,   523,     0,   443,
     233,     0,   447,   445,   450,     0,   439,   440,     0,   427,
     428,   430,   442,   431,   432,   433,   449,   434,   435,   436,
     437,   438,   477,     0,     0,   475,   476,   479,   480,     0,
     464,   465,   467,   468,   469,   470,   471,   472,   473,   474,
     282,   284,   279,     0,   277,   280,   281,     0,   658,   645,
       0,   648,     0,     0,   652,   656,     0,     0,   662,   664,
     666,   668,   643,   641,   642,     0,   624,   626,   627,   628,
     629,   630,   631,   632,   633,   638,   634,   635,   636,   637,
     639,   640,     0,   691,   693,   684,     0,     0,   680,   682,
     683,    46,     0,     0,    39,     0,     0,     0,     0,     0,
       0,    57,     0,    59,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    71,     0,     0,     0,     0,     0,   166,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     311,     0,     0,   492,     0,     0,     0,     0,     0,     0,
       0,     0,   517,     0,   417,     0,     0,     0,     0,     0,
       0,     0,   425,     0,     0,     0,     0,   462,     0,     0,
       0,     0,   276,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   623,
       0,   690,     0,     0,     0,   679,    50,    43,     0,     0,
       0,     0,     0,     0,    61,     0,     0,     0,   133,   134,
     135,     0,     0,     0,     0,     0,     0,   122,   123,   124,
     125,   126,   127,   128,   129,   130,     0,   136,   137,   138,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   590,     0,     0,     0,     0,
       0,     0,    73,     0,     0,     0,   177,   157,     0,     0,
       0,     0,     0,     0,   371,     0,     0,     0,   313,     0,
     494,     0,     0,     0,     0,     0,     0,     0,     0,   521,
       0,     0,   441,     0,     0,     0,   452,   429,     0,   481,
     482,   466,     0,     0,   278,   644,     0,     0,   647,     0,
     650,   651,     0,     0,   660,   661,     0,     0,     0,     0,
     625,   692,     0,   686,   681,     0,     0,     0,   671,   673,
     675,     0,     0,     0,   538,   540,   542,     0,     0,   191,
     132,   141,   142,   143,   144,   145,   140,   147,   149,   304,
     418,   455,   374,    40,   505,   507,   367,   368,   369,   370,
     366,     0,     0,   510,   269,     0,     0,     0,     0,   151,
     153,     0,    51,   168,   171,   172,   170,   175,   176,   174,
     354,   356,   358,   485,   352,   360,   364,   362,     0,   503,
     560,   548,   550,   554,   552,   558,   556,   544,   444,   234,
     448,   446,   451,   478,   283,   285,   659,   646,   649,   654,
     655,   653,   657,   663,   665,   667,   669,   191,    44,     0,
       0,     0,     0,   185,     0,   182,   184,   220,   226,   228,
     230,     0,     0,     0,     0,     0,   242,   244,   246,   248,
       0,     0,     0,     0,     0,     0,   219,     0,   197,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   212,
     213,   214,   209,   215,   216,   217,   210,   211,   218,     0,
     195,     0,   192,   193,   308,     0,   305,   306,   422,     0,
     419,   420,   459,     0,   456,   457,   378,     0,   375,   376,
     262,   263,   264,   265,   266,     0,   255,   257,   258,   259,
     260,   261,   569,     0,   567,   514,     0,   511,   512,   273,
       0,   270,   271,     0,     0,     0,     0,     0,     0,     0,
     288,   290,   291,   292,   293,   294,   295,   600,   602,   599,
     597,   598,     0,   593,   595,   596,     0,   615,     0,   618,
     611,   612,     0,   606,   608,   609,   610,   613,     0,   698,
       0,   696,    53,   489,     0,   486,   487,   545,   563,   564,
       0,     0,    69,   688,   677,   155,     0,     0,   181,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   179,
     188,     0,   190,     0,     0,   303,     0,   426,   415,     0,
     463,   454,     0,     0,   373,     0,     0,   254,   571,     0,
     566,   518,   509,     0,     0,   268,     0,     0,     0,     0,
       0,     0,     0,     0,   287,     0,     0,     0,   592,     0,
       0,     0,     0,     0,   605,   621,     0,     0,   695,    55,
       0,    54,     0,   484,     0,     0,   562,   685,     0,   183,
       0,     0,     0,     0,   232,   235,   236,   237,   238,     0,
       0,     0,     0,   250,   251,   239,   240,   241,   252,   198,
       0,   194,     0,   307,     0,   421,     0,   458,   413,   397,
     398,   399,   385,   386,   402,   403,   404,   388,   389,   405,
     406,   407,   408,   409,   410,   411,   412,   382,   383,   384,
     395,   396,   394,     0,   380,   387,   400,   401,   390,   391,
     392,   393,   377,   256,   587,     0,   585,   586,   578,   579,
     583,   584,   580,   581,   582,     0,   572,   573,   575,   576,
     577,   568,     0,   513,     0,   272,   296,   297,   298,   299,
     300,   301,   289,     0,     0,   594,   614,     0,   617,     0,
     607,   712,     0,   710,   708,   702,   706,   707,     0,   700,
     704,   705,   703,   697,    52,     0,     0,   488,     0,   186,
     222,   223,   224,   225,   221,   227,   229,   231,   243,   245,
     247,   249,   196,   309,   423,   460,     0,   379,     0,     0,
     570,     0,   515,   274,   601,   603,   616,   619,     0,     0,
       0,     0,   699,    56,   490,   546,   381,     0,   589,   574,
       0,   709,     0,   701,   588,     0,   711,   716,     0,   714,
       0,     0,   713,   725,     0,     0,     0,   730,     0,   718,
     720,   721,   722,   723,   724,   715,     0,     0,     0,     0,
       0,     0,   717,     0,   727,   728,   729,     0,   719,   726,
     731
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,   -23,  -900,   337,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -576,  -900,  -900,
    -900,   -70,  -900,  -900,  -900,   507,  -900,  -900,  -900,  -900,
     272,   455,   -47,   -44,    -1,    16,    18,    24,    30,    31,
    -900,  -900,  -900,  -900,    34,    35,    36,    37,    38,    42,
    -900,   274,    48,  -900,    49,  -900,    50,  -900,    52,  -900,
    -900,  -900,   273,   458,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
      59,  -900,  -900,  -900,  -900,  -900,  -900,   175,  -900,    55,
    -900,  -636,    61,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,   -39,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,    44,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,    45,  -900,  -900,  -900,
      46,   473,  -900,  -900,  -900,  -900,  -900,  -900,  -900,    39,
    -900,  -900,  -900,  -900,  -900,  -900,  -899,  -900,  -900,  -900,
      63,  -900,  -900,  -900,    69,   528,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -896,  -900,   -43,  -900,    54,  -900,
      53,  -900,  -900,  -900,  -900,  -900,  -900,  -900,    60,  -900,
    -900,  -128,   -63,  -900,  -900,  -900,  -900,  -900,    65,  -900,
    -900,  -900,    70,  -900,   495,  -900,   -66,  -900,  -900,  -900,
    -900,  -900,   -64,  -900,  -900,  -900,  -900,  -900,    -7,  -900,
    -900,  -900,    71,  -900,  -900,  -900,    72,  -900,   491,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
      22,  -900,  -900,  -900,    32,   534,  -900,  -900,   -57,  -900,
     -20,  -900,   -62,  -900,  -900,  -900,    58,  -900,  -900,  -900,
      74,  -900,   535,     0,  -900,     6,  -900,    12,  -900,   282,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -895,  -900,  -900,
    -900,  -900,  -900,    75,  -900,  -900,  -900,  -116,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,    51,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,    47,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,   308,   483,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,  -900,   348,   485,  -900,  -900,  -900,  -900,  -900,  -900,
    -900,   355,   490,   -75,  -900,  -900,    76,  -900,  -900,  -118,
    -900,  -900,  -900,  -900,  -900,  -900,  -134,  -900,  -900,  -153,
    -900,  -900,  -900,  -900,  -900,  -900,  -900
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     674,    87,    88,    41,    68,    84,    85,   693,   872,   960,
     961,   766,    43,    70,    96,    97,    98,   396,    45,    71,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   425,   163,   164,   165,   166,   167,   168,   169,
     429,   666,   170,   430,   171,   431,   172,   448,   173,   449,
     174,   405,   205,   206,    47,    72,   207,   453,   208,   454,
     696,   209,   455,   699,   210,   175,   413,   176,   406,   744,
     745,   746,   886,   177,   414,   178,   415,   791,   792,   793,
     911,   767,   768,   769,   889,  1094,   770,   890,   771,   891,
     772,   892,   773,   774,   486,   775,   776,   777,   778,   779,
     780,   781,   782,   898,   783,   899,   784,   900,   785,   901,
     786,   787,   788,   179,   439,   815,   816,   817,   818,   819,
     820,   821,   180,   442,   830,   831,   832,   934,    61,    79,
     343,   344,   345,   499,   346,   500,   181,   443,   839,   840,
     841,   842,   843,   844,   845,   846,   182,   432,   795,   796,
     797,   914,    49,    73,   242,   243,   244,   463,   245,   459,
     246,   460,   247,   461,   248,   464,   249,   467,   250,   466,
     183,   438,   680,   252,   184,   435,   807,   808,   809,   923,
    1023,  1024,   185,   433,    55,    76,   799,   800,   801,   917,
      57,    77,   308,   309,   310,   311,   312,   313,   314,   485,
     315,   489,   316,   488,   317,   318,   490,   319,   186,   434,
     803,   804,   805,   920,    59,    78,   329,   330,   331,   332,
     333,   494,   334,   335,   336,   337,   254,   462,   874,   875,
     876,   962,    51,    74,   267,   268,   269,   471,   187,   436,
     188,   437,   189,   441,   826,   827,   828,   931,    53,    75,
     284,   285,   286,   190,   410,   191,   411,   192,   412,   290,
     481,   879,   965,   291,   475,   292,   476,   293,   478,   294,
     477,   295,   480,   296,   479,   297,   474,   261,   468,   880,
     193,   440,   823,   824,   928,  1045,  1046,  1047,  1048,  1049,
    1108,  1050,   194,   195,   445,   852,   853,   854,   945,   855,
     946,   196,   446,   862,   863,   864,   865,   950,   866,   867,
     952,   197,   447,    63,    80,   365,   366,   367,   368,   505,
     369,   370,   507,   371,   372,   373,   510,   731,   374,   511,
     375,   504,   376,   377,   378,   514,   379,   515,   380,   516,
     381,   517,    99,   398,   100,   399,   101,   400,   198,   404,
      67,    82,   387,   388,   389,   522,   390,   102,   397,    65,
      81,   382,   383,   199,   450,   870,   871,   956,  1078,  1079,
    1080,  1081,  1120,  1082,  1118,  1138,  1139,  1140,  1148,  1149,
    1150,  1156,  1151,  1152,  1153,  1154,  1160
  };

  const unsigned short
  Dhcp4Parser::yytable_[] =
  {
      95,   150,   204,   223,   263,   280,   384,   306,   325,   342,
     362,   257,   327,   298,   328,   211,   255,   270,   282,   706,
     320,   338,   789,   363,  1018,   710,   224,  1019,  1031,   225,
      89,   264,   729,    31,    42,    32,    44,    33,   307,   326,
     200,   201,    86,   402,   202,    83,   451,   203,   403,   300,
     132,   452,   212,   256,   271,   283,    30,   321,   339,   149,
     364,   135,   136,   391,   340,   341,   253,   266,   281,    46,
     133,   457,   226,   258,    48,   287,   458,   135,   136,   259,
     392,   288,   262,   135,   136,   260,    50,   289,    52,   227,
      54,   228,   109,   110,   111,   220,   469,   229,   221,   926,
     299,   470,   927,   230,   231,   340,   341,   232,   233,   234,
     235,   236,   385,   386,   393,   237,   135,   136,   856,   857,
     858,   238,   239,   240,   929,   241,   251,   930,   265,  1071,
      94,  1072,  1073,    56,   472,   661,   662,   663,   664,   473,
      58,   132,   133,   300,   501,   300,    60,   301,   302,   502,
     395,   303,   304,   305,    94,   135,   136,   135,   136,   694,
     695,   518,   520,   730,   135,   136,   519,   521,  1034,  1035,
     859,   665,   697,   698,   394,   524,    94,    90,   103,  1143,
     525,   104,  1144,  1145,  1146,  1147,   451,    91,    92,    93,
     105,   882,   106,   107,   108,   109,   110,   111,   112,   113,
     114,    62,   847,   848,    94,   957,    64,  1018,   958,    94,
    1019,  1031,    34,    35,    36,    37,   833,   834,   835,   836,
     837,   838,   279,   877,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   520,   524,    66,   132,   133,   883,   884,    94,   401,
      94,   810,   811,   812,   813,   134,   814,    94,   135,   136,
     407,  1141,   482,   137,  1142,   109,   110,   111,   138,   139,
     408,   457,   484,   409,   140,   990,   885,   300,   322,   301,
     302,   323,   324,   887,   141,   416,   908,   142,   888,   135,
     136,   909,   908,   483,   143,   144,   943,   910,   145,   947,
     953,   944,   146,   417,   948,   954,   518,   908,   135,   136,
     418,   955,  1102,   469,  1106,   133,   501,   492,  1103,  1107,
     419,  1113,   147,   148,   420,   149,  1121,   493,   135,   136,
     472,  1122,    95,  1161,   497,  1124,   421,   422,  1162,   272,
     676,   677,   678,   679,   423,   273,   274,   275,   276,   277,
     278,    94,   279,   347,   348,   349,   350,   351,   352,   353,
     354,   355,   356,   357,   358,   359,   424,   426,   427,   526,
     527,   428,   360,   361,  1090,  1091,  1092,  1093,   444,   456,
     465,   150,    94,   487,   491,   495,   496,   204,   503,   498,
     528,   506,   508,   509,   512,   513,   523,   529,   530,   223,
     211,    94,   263,   531,   532,   533,   535,   257,   536,   537,
     538,   539,   255,   280,   540,   270,   541,   542,   543,   544,
     545,    94,   224,   306,   546,   225,   282,   547,   325,   264,
     553,   548,   327,   549,   328,   550,   320,   212,   551,   552,
     555,   338,   556,   554,   560,   384,   557,   558,   362,   256,
     559,   561,   271,   562,   307,   563,   564,   565,   566,   326,
     567,   363,   253,   283,   568,   266,   569,   570,   226,   258,
     571,   572,   573,   321,   574,   259,   281,   575,   339,   576,
     577,   260,   578,   287,   579,   227,   580,   228,   581,   288,
     583,   584,   585,   229,   586,   289,   588,   589,   364,   230,
     231,   590,   594,   232,   233,   234,   235,   236,   648,   649,
     650,   237,  1125,   591,   592,   593,   595,   238,   239,   240,
     596,   241,   251,   597,   599,   601,   265,   602,   603,   604,
     605,   606,   747,   607,   608,   610,   611,   748,   749,   750,
     751,   752,   753,   754,   755,   756,   757,   758,   759,   760,
     761,   762,   763,   764,   765,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,   613,
     614,   615,   384,   618,   622,   623,   150,   300,   626,   627,
     612,   629,   204,   616,   619,   620,   632,   633,   636,   637,
     625,   628,   630,   631,   638,   211,   634,   635,   639,   642,
     725,   645,   643,   646,   659,   647,   107,   108,   109,   110,
     111,   651,   652,   653,   654,   655,   849,   656,   362,   657,
     658,   660,   738,   667,   669,   668,   670,   671,   672,   850,
     860,   363,   212,    32,   675,   681,   682,   115,   116,   117,
     118,   119,   120,   121,   122,   683,   684,   125,   126,   127,
     128,   129,   130,   685,   213,   214,   215,   686,   133,   687,
     688,   689,   691,   690,   692,   700,   851,   861,   364,   216,
     703,   135,   136,   217,   218,   219,   137,   107,   108,   109,
     110,   111,    94,   220,   701,   702,   221,   140,   704,   705,
     707,   708,   709,   737,   222,   732,   743,   711,   712,   713,
     790,   714,   715,   794,   798,   802,   716,   806,   115,   116,
     117,   118,   119,   120,   121,   122,   822,   717,   125,   126,
     127,   128,   129,   130,   131,   718,   719,   720,   721,   133,
     300,   722,   723,   724,   726,   147,   148,   727,   728,   734,
     735,   736,   135,   136,   825,   218,   829,   137,   869,   873,
     893,   894,   895,   896,   220,   897,   902,   221,   903,   904,
     905,   906,   907,   937,    94,   222,   912,   913,   915,   916,
     919,   918,   922,   959,   921,   925,   924,   932,   933,   935,
     936,  1135,   938,   939,   940,   941,   942,   949,   951,   964,
     975,   963,   974,   968,   967,   966,   970,   971,   972,   973,
     976,   977,   978,   979,   980,   981,   147,   148,   982,   983,
     984,  1063,   985,   986,  1064,  1067,   987,   988,  1056,  1057,
    1058,  1059,  1060,  1061,  1069,  1084,  1066,  1068,  1085,  1089,
    1088,  1095,  1096,  1097,  1109,    94,  1104,  1105,  1098,  1099,
    1100,  1110,  1101,  1111,   223,  1112,  1114,   306,  1115,  1119,
     325,  1116,   257,   998,   327,  1123,   328,   255,  1036,  1127,
     320,   280,  1128,   338,   342,  1038,  1026,   224,  1130,  1132,
     225,  1040,  1131,  1134,   282,  1136,   999,   849,   307,  1000,
    1020,   326,  1137,  1157,  1017,  1158,  1074,  1159,  1163,  1037,
     850,  1164,   263,  1165,   256,  1166,   860,   321,  1167,  1076,
     339,  1169,  1170,  1027,   673,   270,   582,   253,  1041,   534,
     733,   283,   881,   226,   258,   587,  1025,  1075,   739,   264,
     259,  1039,  1001,  1028,   281,   742,   260,   851,  1042,  1029,
     227,   287,   228,   861,  1043,  1030,  1077,   288,   229,  1002,
    1044,  1003,   271,   289,   230,   231,   969,  1004,   232,   233,
     234,   235,   236,  1005,  1006,   266,   237,  1007,  1008,  1009,
    1010,  1011,   238,   239,   240,  1012,   241,   251,   991,   989,
    1033,  1013,  1014,  1015,   624,  1016,  1022,  1021,  1126,   993,
    1054,  1055,  1062,   992,   995,  1032,  1087,   994,   617,   621,
     878,  1053,   996,   997,  1086,  1129,   868,   598,  1065,   741,
    1070,   640,   740,  1133,  1051,  1052,   600,  1155,  1168,   644,
     641,     0,     0,     0,     0,     0,   265,     0,   609,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1083,     0,     0,   998,     0,     0,     0,
       0,  1036,     0,     0,     0,     0,  1117,     0,  1038,  1026,
       0,  1074,     0,     0,  1040,     0,     0,     0,     0,   999,
       0,     0,  1000,  1020,  1076,     0,     0,  1017,     0,     0,
       0,     0,  1037,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1075,     0,     0,     0,  1027,     0,     0,     0,
       0,  1041,     0,     0,     0,     0,     0,     0,     0,  1025,
       0,  1077,     0,     0,  1039,  1001,  1028,     0,     0,     0,
       0,  1042,  1029,     0,     0,     0,     0,  1043,  1030,     0,
       0,     0,  1002,  1044,  1003,     0,     0,     0,     0,     0,
    1004,     0,     0,     0,     0,     0,  1005,  1006,     0,     0,
    1007,  1008,  1009,  1010,  1011,     0,     0,     0,  1012,     0,
       0,     0,     0,     0,  1013,  1014,  1015,     0,  1016,  1022,
    1021
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    81,    77,    78,    79,
      80,    73,    78,    76,    78,    72,    73,    74,    75,   595,
      77,    78,   658,    80,   923,   601,    73,   923,   923,    73,
      10,    74,    18,     5,     7,     7,     7,     9,    77,    78,
      15,    16,   184,     3,    19,    68,     3,    22,     8,    79,
      77,     8,    72,    73,    74,    75,     0,    77,    78,   158,
      80,    91,    92,     6,   118,   119,    73,    74,    75,     7,
      78,     3,    73,    73,     7,    75,     8,    91,    92,    73,
       3,    75,    90,    91,    92,    73,     7,    75,     7,    73,
       7,    73,    28,    29,    30,   103,     3,    73,   106,     3,
      34,     8,     6,    73,    73,   118,   119,    73,    73,    73,
      73,    73,    12,    13,     4,    73,    91,    92,   132,   133,
     134,    73,    73,    73,     3,    73,    73,     6,    74,   159,
     184,   161,   162,     7,     3,   151,   152,   153,   154,     8,
       7,    77,    78,    79,     3,    79,     7,    81,    82,     8,
       3,    85,    86,    87,   184,    91,    92,    91,    92,    17,
      18,     3,     3,   149,    91,    92,     8,     8,   104,   105,
     184,   187,    20,    21,     8,     3,   184,   157,    11,   160,
       8,    14,   163,   164,   165,   166,     3,   167,   168,   169,
      23,     8,    25,    26,    27,    28,    29,    30,    31,    32,
      33,     7,   129,   130,   184,     3,     7,  1106,     6,   184,
    1106,  1106,   184,   185,   186,   187,   121,   122,   123,   124,
     125,   126,   115,   116,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,     3,     3,     7,    77,    78,     8,     8,   184,     4,
     184,   108,   109,   110,   111,    88,   113,   184,    91,    92,
       4,     3,     8,    96,     6,    28,    29,    30,   101,   102,
       4,     3,     8,     4,   107,   911,     8,    79,    80,    81,
      82,    83,    84,     3,   117,     4,     3,   120,     8,    91,
      92,     8,     3,     3,   127,   128,     3,     8,   131,     3,
       3,     8,   135,     4,     8,     8,     3,     3,    91,    92,
       4,     8,     8,     3,     3,    78,     3,     8,     8,     8,
       4,     8,   155,   156,     4,   158,     3,     3,    91,    92,
       3,     8,   402,     3,     8,     8,     4,     4,     8,   102,
      97,    98,    99,   100,     4,   108,   109,   110,   111,   112,
     113,   184,   115,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,     4,     4,     4,   392,
     393,     4,   155,   156,    35,    36,    37,    38,     4,     4,
       4,   451,   184,     4,     4,     4,     4,   457,     4,     3,
     184,     4,     4,     4,     4,     4,     4,     4,     4,   469,
     457,   184,   472,     4,     4,     4,     4,   469,     4,     4,
     187,   187,   469,   483,   187,   472,     4,     4,     4,     4,
       4,   184,   469,   493,     4,   469,   483,   185,   498,   472,
     186,   185,   498,   185,   498,   185,   493,   457,   185,   187,
     185,   498,     4,   186,     4,   520,   187,   187,   518,   469,
     187,     4,   472,     4,   493,     4,     4,     4,     4,   498,
       4,   518,   469,   483,     4,   472,     4,     4,   469,   469,
       4,     4,     4,   493,     4,   469,   483,   185,   498,     4,
       4,   469,     4,   483,     4,   469,     4,   469,     4,   483,
       4,     4,     4,   469,   187,   483,     4,     4,   518,   469,
     469,     4,   185,   469,   469,   469,   469,   469,   531,   532,
     533,   469,  1088,     4,     4,     4,     4,   469,   469,   469,
       4,   469,   469,     4,     4,     4,   472,     4,     4,     4,
       4,     4,    34,     4,     4,     4,     4,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,     4,
       4,     4,   647,     4,     4,     4,   646,    79,     4,     4,
     185,     4,   652,   187,   187,   187,     4,     4,     4,     4,
     187,   185,   185,   185,     4,   652,   187,   187,     4,     4,
     623,     4,   185,     7,     5,     7,    26,    27,    28,    29,
      30,     7,     7,     7,   184,   184,   686,   184,   688,     7,
       7,   184,   645,   184,     5,   184,     5,     5,     5,   686,
     687,   688,   652,     7,   184,     5,     5,    57,    58,    59,
      60,    61,    62,    63,    64,     5,     5,    67,    68,    69,
      70,    71,    72,     7,    74,    75,    76,     7,    78,     7,
       7,   184,     5,   184,     5,   184,   686,   687,   688,    89,
       5,    91,    92,    93,    94,    95,    96,    26,    27,    28,
      29,    30,   184,   103,   184,   184,   106,   107,   184,   184,
     184,     7,   184,     5,   114,   150,    24,   184,   184,   184,
       7,   184,   184,     7,     7,     7,   184,     7,    57,    58,
      59,    60,    61,    62,    63,    64,     7,   184,    67,    68,
      69,    70,    71,    72,    73,   184,   184,   184,   184,    78,
      79,   184,   184,   184,   184,   155,   156,   184,   184,   184,
     184,   184,    91,    92,     7,    94,     7,    96,     7,     7,
       4,     4,     4,     4,   103,     4,     4,   106,     4,     4,
       4,     4,     4,     4,   184,   114,     6,     3,     6,     3,
       3,     6,     3,   184,     6,     3,     6,     6,     3,     6,
       3,     5,     4,     4,     4,     4,     4,     4,     4,     3,
     187,     6,   185,     4,     6,     8,     4,     4,     4,     4,
     185,   187,   185,     4,     4,     4,   155,   156,     4,   185,
     185,     4,   185,   185,     4,     4,   187,   185,   185,   185,
     185,   185,   185,   185,     4,     6,   187,   185,     3,   184,
       4,   184,   184,   184,     4,   184,     8,     8,   184,   184,
     184,     8,   184,     3,   914,     8,   184,   917,   184,     4,
     920,   184,   914,   923,   920,   184,   920,   914,   928,     4,
     917,   931,   187,   920,   934,   928,   923,   914,     4,     4,
     914,   928,   185,   184,   931,   184,   923,   947,   917,   923,
     923,   920,     7,     4,   923,     4,   956,     4,     4,   928,
     947,   187,   962,   185,   914,   185,   953,   917,     4,   956,
     920,   184,   184,   923,   567,   962,   451,   914,   928,   402,
     636,   931,   737,   914,   914,   457,   923,   956,   646,   962,
     914,   928,   923,   923,   931,   652,   914,   947,   928,   923,
     914,   931,   914,   953,   928,   923,   956,   931,   914,   923,
     928,   923,   962,   931,   914,   914,   887,   923,   914,   914,
     914,   914,   914,   923,   923,   962,   914,   923,   923,   923,
     923,   923,   914,   914,   914,   923,   914,   914,   913,   908,
     926,   923,   923,   923,   501,   923,   923,   923,  1106,   916,
     934,   936,   943,   914,   919,   925,   964,   917,   493,   498,
     708,   933,   920,   922,   962,  1111,   688,   469,   947,   651,
     953,   518,   647,  1121,   929,   931,   472,  1141,  1161,   524,
     520,    -1,    -1,    -1,    -1,    -1,   962,    -1,   483,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   957,    -1,    -1,  1106,    -1,    -1,    -1,
      -1,  1111,    -1,    -1,    -1,    -1,  1069,    -1,  1111,  1106,
      -1,  1121,    -1,    -1,  1111,    -1,    -1,    -1,    -1,  1106,
      -1,    -1,  1106,  1106,  1121,    -1,    -1,  1106,    -1,    -1,
      -1,    -1,  1111,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1121,    -1,    -1,    -1,  1106,    -1,    -1,    -1,
      -1,  1111,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1106,
      -1,  1121,    -1,    -1,  1111,  1106,  1106,    -1,    -1,    -1,
      -1,  1111,  1106,    -1,    -1,    -1,    -1,  1111,  1106,    -1,
      -1,    -1,  1106,  1111,  1106,    -1,    -1,    -1,    -1,    -1,
    1106,    -1,    -1,    -1,    -1,    -1,  1106,  1106,    -1,    -1,
    1106,  1106,  1106,  1106,  1106,    -1,    -1,    -1,  1106,    -1,
      -1,    -1,    -1,    -1,  1106,  1106,  1106,    -1,  1106,  1106,
    1106
  };

  const unsigned short
  Dhcp4Parser::yystos_[] =
  {
       0,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
       0,     5,     7,     9,   184,   185,   186,   187,   204,   205,
     206,   211,     7,   220,     7,   226,     7,   262,     7,   360,
       7,   440,     7,   456,     7,   392,     7,   398,     7,   422,
       7,   336,     7,   521,     7,   567,     7,   558,   212,   207,
     221,   227,   263,   361,   441,   457,   393,   399,   423,   337,
     522,   568,   559,   204,   213,   214,   184,   209,   210,    10,
     157,   167,   168,   169,   184,   219,   222,   223,   224,   550,
     552,   554,   565,    11,    14,    23,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    77,    78,    88,    91,    92,    96,   101,   102,
     107,   117,   120,   127,   128,   131,   135,   155,   156,   158,
     219,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   241,   242,   243,   244,   245,   246,   247,
     250,   252,   254,   256,   258,   273,   275,   281,   283,   321,
     330,   344,   354,   378,   382,   390,   416,   446,   448,   450,
     461,   463,   465,   488,   500,   501,   509,   519,   556,   571,
      15,    16,    19,    22,   219,   260,   261,   264,   266,   269,
     272,   446,   448,    74,    75,    76,    89,    93,    94,    95,
     103,   106,   114,   219,   230,   231,   232,   233,   234,   235,
     236,   237,   242,   243,   244,   245,   246,   247,   250,   252,
     254,   256,   362,   363,   364,   366,   368,   370,   372,   374,
     376,   378,   381,   416,   434,   446,   448,   450,   461,   463,
     465,   485,    90,   219,   374,   376,   416,   442,   443,   444,
     446,   448,   102,   108,   109,   110,   111,   112,   113,   115,
     219,   416,   446,   448,   458,   459,   460,   461,   463,   465,
     467,   471,   473,   475,   477,   479,   481,   483,   390,    34,
      79,    81,    82,    85,    86,    87,   219,   301,   400,   401,
     402,   403,   404,   405,   406,   408,   410,   412,   413,   415,
     446,   448,    80,    83,    84,   219,   301,   404,   410,   424,
     425,   426,   427,   428,   430,   431,   432,   433,   446,   448,
     118,   119,   219,   338,   339,   340,   342,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     155,   156,   219,   446,   448,   523,   524,   525,   526,   528,
     529,   531,   532,   533,   536,   538,   540,   541,   542,   544,
     546,   548,   569,   570,   571,    12,    13,   560,   561,   562,
     564,     6,     3,     4,     8,     3,   225,   566,   551,   553,
     555,     4,     3,     8,   557,   259,   276,     4,     4,     4,
     462,   464,   466,   274,   282,   284,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   240,     4,     4,     4,   248,
     251,   253,   355,   391,   417,   383,   447,   449,   379,   322,
     489,   451,   331,   345,     4,   502,   510,   520,   255,   257,
     572,     3,     8,   265,   267,   270,     4,     3,     8,   367,
     369,   371,   435,   365,   373,     4,   377,   375,   486,     3,
       8,   445,     3,     8,   484,   472,   474,   478,   476,   482,
     480,   468,     8,     3,     8,   407,   302,     4,   411,   409,
     414,     4,     8,     3,   429,     4,     4,     8,     3,   341,
     343,     3,     8,     4,   539,   527,     4,   530,     4,     4,
     534,   537,     4,     4,   543,   545,   547,   549,     3,     8,
       3,     8,   563,     4,     3,     8,   204,   204,   184,     4,
       4,     4,     4,     4,   223,     4,     4,     4,   187,   187,
     187,     4,     4,     4,     4,     4,     4,   185,   185,   185,
     185,   185,   187,   186,   186,   185,     4,   187,   187,   187,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   185,     4,     4,     4,     4,
       4,     4,   229,     4,     4,     4,   187,   261,     4,     4,
       4,     4,     4,     4,   185,     4,     4,     4,   363,     4,
     443,     4,     4,     4,     4,     4,     4,     4,     4,   460,
       4,     4,   185,     4,     4,     4,   187,   402,     4,   187,
     187,   426,     4,     4,   339,   187,     4,     4,   185,     4,
     185,   185,     4,     4,   187,   187,     4,     4,     4,     4,
     524,   570,     4,   185,   561,     4,     7,     7,   204,   204,
     204,     7,     7,     7,   184,   184,   184,     7,     7,     5,
     184,   151,   152,   153,   154,   187,   249,   184,   184,     5,
       5,     5,     5,   206,   208,   184,    97,    98,    99,   100,
     380,     5,     5,     5,     5,     7,     7,     7,     7,   184,
     184,     5,     5,   215,    17,    18,   268,    20,    21,   271,
     184,   184,   184,     5,   184,   184,   215,   184,     7,   184,
     215,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   204,   184,   184,   184,    18,
     149,   535,   150,   249,   184,   184,   184,     5,   204,   228,
     569,   560,   260,    24,   277,   278,   279,    34,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,   219,   289,   290,   291,
     294,   296,   298,   300,   301,   303,   304,   305,   306,   307,
     308,   309,   310,   312,   314,   316,   318,   319,   320,   289,
       7,   285,   286,   287,     7,   356,   357,   358,     7,   394,
     395,   396,     7,   418,   419,   420,     7,   384,   385,   386,
     108,   109,   110,   111,   113,   323,   324,   325,   326,   327,
     328,   329,     7,   490,   491,     7,   452,   453,   454,     7,
     332,   333,   334,   121,   122,   123,   124,   125,   126,   346,
     347,   348,   349,   350,   351,   352,   353,   129,   130,   219,
     446,   448,   503,   504,   505,   507,   132,   133,   134,   184,
     446,   448,   511,   512,   513,   514,   516,   517,   523,     7,
     573,   574,   216,     7,   436,   437,   438,   116,   467,   469,
     487,   285,     8,     8,     8,     8,   280,     3,     8,   292,
     295,   297,   299,     4,     4,     4,     4,     4,   311,   313,
     315,   317,     4,     4,     4,     4,     4,     4,     3,     8,
       8,   288,     6,     3,   359,     6,     3,   397,     6,     3,
     421,     6,     3,   387,     6,     3,     3,     6,   492,     3,
       6,   455,     6,     3,   335,     6,     3,     4,     4,     4,
       4,     4,     4,     3,     8,   506,   508,     3,     8,     4,
     515,     4,   518,     3,     8,     8,   575,     3,     6,   184,
     217,   218,   439,     6,     3,   470,     8,     6,     4,   278,
       4,     4,     4,     4,   185,   187,   185,   187,   185,     4,
       4,     4,     4,   185,   185,   185,   185,   187,   185,   290,
     289,   287,   362,   358,   400,   396,   424,   420,   219,   230,
     231,   232,   233,   234,   235,   236,   237,   242,   243,   244,
     245,   246,   247,   250,   252,   254,   256,   301,   354,   372,
     374,   376,   378,   388,   389,   416,   446,   448,   461,   463,
     465,   485,   386,   324,   104,   105,   219,   301,   390,   416,
     446,   448,   461,   463,   465,   493,   494,   495,   496,   497,
     499,   491,   458,   454,   338,   334,   185,   185,   185,   185,
     185,   185,   347,     4,     4,   504,   187,     4,   185,     4,
     512,   159,   161,   162,   219,   301,   446,   448,   576,   577,
     578,   579,   581,   574,     6,     3,   442,   438,     4,   184,
      35,    36,    37,    38,   293,   184,   184,   184,   184,   184,
     184,   184,     8,     8,     8,     8,     3,     8,   498,     4,
       8,     3,     8,     8,   184,   184,   184,   204,   582,     4,
     580,     3,     8,   184,     8,   215,   389,     4,   187,   495,
       4,   185,     4,   577,   184,     5,   184,     7,   583,   584,
     585,     3,     6,   160,   163,   164,   165,   166,   586,   587,
     588,   590,   591,   592,   593,   584,   589,     4,     4,     4,
     594,     3,     8,     4,   187,   185,   185,     4,   587,   184,
     184
  };

  const unsigned short
  Dhcp4Parser::yyr1_[] =
  {
       0,   188,   190,   189,   191,   189,   192,   189,   193,   189,
     194,   189,   195,   189,   196,   189,   197,   189,   198,   189,
     199,   189,   200,   189,   201,   189,   202,   189,   203,   189,
     204,   204,   204,   204,   204,   204,   204,   205,   207,   206,
     208,   209,   209,   210,   210,   212,   211,   213,   213,   214,
     214,   216,   215,   217,   217,   218,   218,   219,   221,   220,
     222,   222,   223,   223,   223,   223,   223,   223,   225,   224,
     227,   226,   228,   228,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   240,   239,   241,   242,   243,   244,   245,   246,   248,
     247,   249,   249,   249,   249,   249,   251,   250,   253,   252,
     255,   254,   257,   256,   259,   258,   260,   260,   261,   261,
     261,   261,   261,   261,   261,   263,   262,   265,   264,   267,
     266,   268,   268,   270,   269,   271,   271,   272,   274,   273,
     276,   275,   277,   277,   278,   280,   279,   282,   281,   284,
     283,   285,   285,   286,   286,   288,   287,   289,   289,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   290,
     292,   291,   293,   293,   293,   293,   295,   294,   297,   296,
     299,   298,   300,   302,   301,   303,   304,   305,   306,   307,
     308,   309,   311,   310,   313,   312,   315,   314,   317,   316,
     318,   319,   320,   322,   321,   323,   323,   324,   324,   324,
     324,   324,   325,   326,   327,   328,   329,   331,   330,   332,
     332,   333,   333,   335,   334,   337,   336,   338,   338,   338,
     339,   339,   341,   340,   343,   342,   345,   344,   346,   346,
     347,   347,   347,   347,   347,   347,   348,   349,   350,   351,
     352,   353,   355,   354,   356,   356,   357,   357,   359,   358,
     361,   360,   362,   362,   363,   363,   363,   363,   363,   363,
     363,   363,   363,   363,   363,   363,   363,   363,   363,   363,
     363,   363,   363,   363,   363,   363,   363,   363,   363,   363,
     363,   363,   363,   363,   363,   363,   363,   363,   363,   363,
     363,   365,   364,   367,   366,   369,   368,   371,   370,   373,
     372,   375,   374,   377,   376,   379,   378,   380,   380,   380,
     380,   381,   383,   382,   384,   384,   385,   385,   387,   386,
     388,   388,   389,   389,   389,   389,   389,   389,   389,   389,
     389,   389,   389,   389,   389,   389,   389,   389,   389,   389,
     389,   389,   389,   389,   389,   389,   389,   389,   389,   389,
     389,   389,   389,   389,   391,   390,   393,   392,   394,   394,
     395,   395,   397,   396,   399,   398,   400,   400,   401,   401,
     402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
     403,   404,   405,   407,   406,   409,   408,   411,   410,   412,
     414,   413,   415,   417,   416,   418,   418,   419,   419,   421,
     420,   423,   422,   424,   424,   425,   425,   426,   426,   426,
     426,   426,   426,   426,   426,   426,   427,   429,   428,   430,
     431,   432,   433,   435,   434,   436,   436,   437,   437,   439,
     438,   441,   440,   442,   442,   443,   443,   443,   443,   443,
     443,   443,   445,   444,   447,   446,   449,   448,   451,   450,
     452,   452,   453,   453,   455,   454,   457,   456,   458,   458,
     459,   459,   460,   460,   460,   460,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   462,   461,   464,
     463,   466,   465,   468,   467,   470,   469,   472,   471,   474,
     473,   476,   475,   478,   477,   480,   479,   482,   481,   484,
     483,   486,   485,   487,   487,   489,   488,   490,   490,   492,
     491,   493,   493,   494,   494,   495,   495,   495,   495,   495,
     495,   495,   495,   495,   495,   495,   496,   498,   497,   499,
     500,   502,   501,   503,   503,   504,   504,   504,   504,   504,
     506,   505,   508,   507,   510,   509,   511,   511,   512,   512,
     512,   512,   512,   512,   513,   515,   514,   516,   518,   517,
     520,   519,   522,   521,   523,   523,   524,   524,   524,   524,
     524,   524,   524,   524,   524,   524,   524,   524,   524,   524,
     524,   524,   524,   524,   525,   527,   526,   528,   530,   529,
     531,   532,   534,   533,   535,   535,   537,   536,   539,   538,
     540,   541,   543,   542,   545,   544,   547,   546,   549,   548,
     551,   550,   553,   552,   555,   554,   557,   556,   559,   558,
     560,   560,   561,   561,   563,   562,   564,   566,   565,   568,
     567,   569,   569,   570,   572,   571,   573,   573,   575,   574,
     576,   576,   577,   577,   577,   577,   577,   577,   577,   578,
     580,   579,   582,   581,   583,   583,   585,   584,   586,   586,
     587,   587,   587,   587,   587,   589,   588,   590,   591,   592,
     594,   593
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     0,     4,     3,     3,     3,     3,     3,     3,     0,
       4,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     1,     1,     0,     4,     1,     1,     3,     0,     6,
       0,     6,     1,     3,     1,     0,     4,     0,     6,     0,
       6,     0,     1,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     3,     3,     3,
       3,     3,     0,     4,     0,     4,     0,     4,     0,     4,
       3,     3,     3,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     1,     1,     1,
       1,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     0,     4,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     0,     4,     0,     4,     0,     4,     1,
       0,     4,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     1,     0,     6,     1,     3,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     3,     0,     4,
       0,     6,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     3,     0,     4,
       3,     3,     0,     4,     1,     1,     0,     4,     0,     4,
       3,     3,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     0,     6,     3,     0,     6,     0,
       4,     1,     3,     1,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     0,     4,     3,     3,     3,
       0,     4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp4Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp4\"", "\"config-control\"",
  "\"config-databases\"", "\"config-fetch-wait-time\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"dhcp-socket-type\"",
  "\"raw\"", "\"udp\"", "\"outbound-interface\"", "\"same-as-inbound\"",
  "\"use-routing\"", "\"re-detect\"", "\"sanity-checks\"",
  "\"lease-checks\"", "\"echo-client-id\"", "\"match-client-id\"",
  "\"authoritative\"", "\"next-server\"", "\"server-hostname\"",
  "\"boot-file-name\"", "\"lease-database\"", "\"hosts-database\"",
  "\"hosts-databases\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"", "\"host\"",
  "\"port\"", "\"persist\"", "\"lfc-interval\"", "\"readonly\"",
  "\"connect-timeout\"", "\"contact-points\"", "\"keyspace\"",
  "\"consistency\"", "\"serial-consistency\"", "\"max-reconnect-tries\"",
  "\"reconnect-wait-time\"", "\"request-timeout\"", "\"tcp-keepalive\"",
  "\"tcp-nodelay\"", "\"max-row-errors\"", "\"valid-lifetime\"",
  "\"min-valid-lifetime\"", "\"max-valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"calculate-tee-times\"", "\"t1-percent\"",
  "\"t2-percent\"", "\"decline-probation-period\"", "\"server-tag\"",
  "\"ddns-send-updates\"", "\"ddns-override-no-update\"",
  "\"ddns-override-client-update\"", "\"ddns-replace-client-name\"",
  "\"ddns-generated-prefix\"", "\"ddns-qualifying-suffix\"", "\"subnet4\"",
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
  "\"socket-name\"", "\"dhcp-queue-control\"", "\"enable-queue\"",
  "\"queue-type\"", "\"capacity\"", "\"dhcp-ddns\"", "\"enable-updates\"",
  "\"qualifying-suffix\"", "\"server-ip\"", "\"server-port\"",
  "\"sender-ip\"", "\"sender-port\"", "\"max-queue-size\"",
  "\"ncr-protocol\"", "\"ncr-format\"", "\"override-no-update\"",
  "\"override-client-update\"", "\"replace-client-name\"",
  "\"generated-prefix\"", "\"tcp\"", "\"JSON\"", "\"when-present\"",
  "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"hostname-char-set\"", "\"hostname-char-replacement\"", "\"Logging\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"",
  "\"Dhcp6\"", "\"DhcpDdns\"", "\"Control-agent\"", "TOPLEVEL_JSON",
  "TOPLEVEL_DHCP4", "SUB_DHCP4", "SUB_INTERFACES4", "SUB_SUBNET4",
  "SUB_POOL4", "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "SUB_LOGGING",
  "SUB_CONFIG_CONTROL", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "$@14", "value", "sub_json", "map2", "$@15", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@16", "list_content",
  "not_empty_list", "list_strings", "$@17", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@18",
  "global_objects", "global_object", "dhcp4_object", "$@19", "sub_dhcp4",
  "$@20", "global_params", "global_param", "valid_lifetime",
  "min_valid_lifetime", "max_valid_lifetime", "renew_timer",
  "rebind_timer", "calculate_tee_times", "t1_percent", "t2_percent",
  "decline_probation_period", "server_tag", "$@21", "echo_client_id",
  "match_client_id", "authoritative", "ddns_send_updates",
  "ddns_override_no_update", "ddns_override_client_update",
  "ddns_replace_client_name", "$@22", "ddns_replace_client_name_value",
  "ddns_generated_prefix", "$@23", "ddns_qualifying_suffix", "$@24",
  "hostname_char_set", "$@25", "hostname_char_replacement", "$@26",
  "interfaces_config", "$@27", "interfaces_config_params",
  "interfaces_config_param", "sub_interfaces4", "$@28", "interfaces_list",
  "$@29", "dhcp_socket_type", "$@30", "socket_type", "outbound_interface",
  "$@31", "outbound_interface_value", "re_detect", "lease_database",
  "$@32", "sanity_checks", "$@33", "sanity_checks_params",
  "sanity_checks_param", "lease_checks", "$@34", "hosts_database", "$@35",
  "hosts_databases", "$@36", "database_list", "not_empty_database_list",
  "database", "$@37", "database_map_params", "database_map_param",
  "database_type", "$@38", "db_type", "user", "$@39", "password", "$@40",
  "host", "$@41", "port", "name", "$@42", "persist", "lfc_interval",
  "readonly", "connect_timeout", "request_timeout", "tcp_keepalive",
  "tcp_nodelay", "contact_points", "$@43", "keyspace", "$@44",
  "consistency", "$@45", "serial_consistency", "$@46",
  "max_reconnect_tries", "reconnect_wait_time", "max_row_errors",
  "host_reservation_identifiers", "$@47",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@48", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@49",
  "sub_hooks_library", "$@50", "hooks_params", "hooks_param", "library",
  "$@51", "parameters", "$@52", "expired_leases_processing", "$@53",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@54",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@55",
  "sub_subnet4", "$@56", "subnet4_params", "subnet4_param", "subnet",
  "$@57", "subnet_4o6_interface", "$@58", "subnet_4o6_interface_id",
  "$@59", "subnet_4o6_subnet", "$@60", "interface", "$@61", "client_class",
  "$@62", "require_client_classes", "$@63", "reservation_mode", "$@64",
  "hr_mode", "id", "shared_networks", "$@65", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@66",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@67", "sub_option_def_list", "$@68", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@69",
  "sub_option_def", "$@70", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@71",
  "option_def_record_types", "$@72", "space", "$@73", "option_def_space",
  "option_def_encapsulate", "$@74", "option_def_array", "option_data_list",
  "$@75", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@76", "sub_option_data", "$@77",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@78",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@79", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@80", "sub_pool4", "$@81",
  "pool_params", "pool_param", "pool_entry", "$@82", "user_context",
  "$@83", "comment", "$@84", "reservations", "$@85", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@86", "sub_reservation",
  "$@87", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@88", "server_hostname", "$@89",
  "boot_file_name", "$@90", "ip_address", "$@91", "ip_addresses", "$@92",
  "duid", "$@93", "hw_address", "$@94", "client_id_value", "$@95",
  "circuit_id_value", "$@96", "flex_id_value", "$@97", "hostname", "$@98",
  "reservation_client_classes", "$@99", "relay", "$@100", "relay_map",
  "client_classes", "$@101", "client_classes_list", "client_class_entry",
  "$@102", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@103",
  "only_if_required", "dhcp4o6_port", "control_socket", "$@104",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@105", "control_socket_name", "$@106", "dhcp_queue_control", "$@107",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@108", "capacity", "arbitrary_map_entry", "$@109",
  "dhcp_ddns", "$@110", "sub_dhcp_ddns", "$@111", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@112", "server_port",
  "sender_ip", "$@113", "sender_port", "max_queue_size", "ncr_protocol",
  "$@114", "ncr_protocol_value", "ncr_format", "$@115",
  "dep_qualifying_suffix", "$@116", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@117",
  "dep_generated_prefix", "$@118", "dep_hostname_char_set", "$@119",
  "dep_hostname_char_replacement", "$@120", "dhcp6_json_object", "$@121",
  "dhcpddns_json_object", "$@122", "control_agent_json_object", "$@123",
  "config_control", "$@124", "sub_config_control", "$@125",
  "config_control_params", "config_control_param", "config_databases",
  "$@126", "config_fetch_wait_time", "logging_object", "$@127",
  "sub_logging", "$@128", "logging_params", "logging_param", "loggers",
  "$@129", "loggers_entries", "logger_entry", "$@130", "logger_params",
  "logger_param", "debuglevel", "severity", "$@131", "output_options_list",
  "$@132", "output_options_list_content", "output_entry", "$@133",
  "output_params_list", "output_params", "output", "$@134", "flush",
  "maxsize", "maxver", "pattern", "$@135", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short
  Dhcp4Parser::yyrline_[] =
  {
       0,   275,   275,   275,   276,   276,   277,   277,   278,   278,
     279,   279,   280,   280,   281,   281,   282,   282,   283,   283,
     284,   284,   285,   285,   286,   286,   287,   287,   288,   288,
     296,   297,   298,   299,   300,   301,   302,   305,   310,   310,
     321,   324,   325,   328,   332,   339,   339,   346,   347,   350,
     354,   361,   361,   368,   369,   372,   376,   387,   397,   397,
     413,   414,   418,   419,   420,   421,   422,   423,   426,   426,
     441,   441,   450,   451,   456,   457,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   473,   474,   475,   476,   477,   478,   479,   480,   481,
     482,   483,   484,   485,   486,   487,   488,   489,   490,   491,
     492,   493,   494,   495,   496,   497,   498,   499,   500,   501,
     502,   503,   506,   511,   516,   521,   526,   531,   536,   541,
     546,   551,   551,   559,   564,   569,   574,   579,   584,   589,
     589,   597,   600,   603,   606,   609,   615,   615,   623,   623,
     631,   631,   639,   639,   647,   647,   658,   659,   662,   663,
     664,   665,   666,   667,   668,   671,   671,   680,   680,   690,
     690,   697,   698,   701,   701,   708,   710,   714,   720,   720,
     732,   732,   742,   743,   745,   747,   747,   765,   765,   777,
     777,   787,   788,   791,   792,   795,   795,   805,   806,   809,
     810,   811,   812,   813,   814,   815,   816,   817,   818,   819,
     820,   821,   822,   823,   824,   825,   826,   827,   828,   829,
     832,   832,   839,   840,   841,   842,   845,   845,   853,   853,
     861,   861,   869,   874,   874,   882,   887,   892,   897,   902,
     907,   912,   917,   917,   925,   925,   933,   933,   941,   941,
     949,   954,   959,   965,   965,   975,   976,   979,   980,   981,
     982,   983,   986,   991,   996,  1001,  1006,  1011,  1011,  1021,
    1022,  1025,  1026,  1029,  1029,  1039,  1039,  1049,  1050,  1051,
    1054,  1055,  1058,  1058,  1066,  1066,  1074,  1074,  1085,  1086,
    1089,  1090,  1091,  1092,  1093,  1094,  1097,  1102,  1107,  1112,
    1117,  1122,  1130,  1130,  1143,  1144,  1147,  1148,  1155,  1155,
    1181,  1181,  1192,  1193,  1197,  1198,  1199,  1200,  1201,  1202,
    1203,  1204,  1205,  1206,  1207,  1208,  1209,  1210,  1211,  1212,
    1213,  1214,  1215,  1216,  1217,  1218,  1219,  1220,  1221,  1222,
    1223,  1224,  1225,  1226,  1227,  1228,  1229,  1230,  1231,  1232,
    1233,  1236,  1236,  1244,  1244,  1252,  1252,  1260,  1260,  1268,
    1268,  1276,  1276,  1284,  1284,  1294,  1294,  1301,  1302,  1303,
    1304,  1307,  1314,  1314,  1325,  1326,  1330,  1331,  1334,  1334,
    1342,  1343,  1346,  1347,  1348,  1349,  1350,  1351,  1352,  1353,
    1354,  1355,  1356,  1357,  1358,  1359,  1360,  1361,  1362,  1363,
    1364,  1365,  1366,  1367,  1368,  1369,  1370,  1371,  1372,  1373,
    1374,  1375,  1376,  1377,  1384,  1384,  1397,  1397,  1406,  1407,
    1410,  1411,  1416,  1416,  1431,  1431,  1445,  1446,  1449,  1450,
    1453,  1454,  1455,  1456,  1457,  1458,  1459,  1460,  1461,  1462,
    1465,  1467,  1472,  1474,  1474,  1482,  1482,  1490,  1490,  1498,
    1500,  1500,  1508,  1517,  1517,  1529,  1530,  1535,  1536,  1541,
    1541,  1553,  1553,  1565,  1566,  1571,  1572,  1577,  1578,  1579,
    1580,  1581,  1582,  1583,  1584,  1585,  1588,  1590,  1590,  1598,
    1600,  1602,  1607,  1615,  1615,  1627,  1628,  1631,  1632,  1635,
    1635,  1645,  1645,  1655,  1656,  1659,  1660,  1661,  1662,  1663,
    1664,  1665,  1668,  1668,  1676,  1676,  1701,  1701,  1731,  1731,
    1741,  1742,  1745,  1746,  1749,  1749,  1758,  1758,  1767,  1768,
    1771,  1772,  1776,  1777,  1778,  1779,  1780,  1781,  1782,  1783,
    1784,  1785,  1786,  1787,  1788,  1789,  1790,  1793,  1793,  1801,
    1801,  1809,  1809,  1817,  1817,  1825,  1825,  1835,  1835,  1843,
    1843,  1851,  1851,  1859,  1859,  1867,  1867,  1875,  1875,  1883,
    1883,  1896,  1896,  1906,  1907,  1913,  1913,  1923,  1924,  1927,
    1927,  1937,  1938,  1941,  1942,  1945,  1946,  1947,  1948,  1949,
    1950,  1951,  1952,  1953,  1954,  1955,  1958,  1960,  1960,  1968,
    1977,  1984,  1984,  1994,  1995,  1998,  1999,  2000,  2001,  2002,
    2005,  2005,  2013,  2013,  2024,  2024,  2036,  2037,  2040,  2041,
    2042,  2043,  2044,  2045,  2048,  2053,  2053,  2061,  2066,  2066,
    2075,  2075,  2087,  2087,  2097,  2098,  2101,  2102,  2103,  2104,
    2105,  2106,  2107,  2108,  2109,  2110,  2111,  2112,  2113,  2114,
    2115,  2116,  2117,  2118,  2121,  2126,  2126,  2134,  2139,  2139,
    2147,  2152,  2157,  2157,  2165,  2166,  2169,  2169,  2178,  2178,
    2187,  2193,  2199,  2199,  2207,  2207,  2216,  2216,  2225,  2225,
    2236,  2236,  2243,  2243,  2250,  2250,  2257,  2257,  2268,  2268,
    2278,  2279,  2283,  2284,  2287,  2287,  2297,  2307,  2307,  2317,
    2317,  2328,  2329,  2333,  2337,  2337,  2349,  2350,  2354,  2354,
    2362,  2363,  2366,  2367,  2368,  2369,  2370,  2371,  2372,  2375,
    2380,  2380,  2388,  2388,  2398,  2399,  2402,  2402,  2410,  2411,
    2414,  2415,  2416,  2417,  2418,  2421,  2421,  2429,  2434,  2439,
    2444,  2444
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


#line 14 "dhcp4_parser.yy"
} } // isc::dhcp
#line 5345 "dhcp4_parser.cc"

#line 2453 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
