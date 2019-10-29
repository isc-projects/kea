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
      case 201: // value
      case 205: // map_value
      case 246: // ddns_replace_client_name_value
      case 265: // socket_type
      case 268: // outbound_interface_value
      case 290: // db_type
      case 377: // hr_mode
      case 524: // ncr_protocol_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 184: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 183: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 182: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 181: // "constant string"
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
      case 201: // value
      case 205: // map_value
      case 246: // ddns_replace_client_name_value
      case 265: // socket_type
      case 268: // outbound_interface_value
      case 290: // db_type
      case 377: // hr_mode
      case 524: // ncr_protocol_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 184: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 183: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 182: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 181: // "constant string"
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
      case 201: // value
      case 205: // map_value
      case 246: // ddns_replace_client_name_value
      case 265: // socket_type
      case 268: // outbound_interface_value
      case 290: // db_type
      case 377: // hr_mode
      case 524: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 184: // "boolean"
        value.move< bool > (that.value);
        break;

      case 183: // "floating point"
        value.move< double > (that.value);
        break;

      case 182: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 181: // "constant string"
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
      case 181: // "constant string"
#line 263 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < std::string > (); }
#line 405 "dhcp4_parser.cc"
        break;

      case 182: // "integer"
#line 263 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 411 "dhcp4_parser.cc"
        break;

      case 183: // "floating point"
#line 263 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < double > (); }
#line 417 "dhcp4_parser.cc"
        break;

      case 184: // "boolean"
#line 263 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < bool > (); }
#line 423 "dhcp4_parser.cc"
        break;

      case 201: // value
#line 263 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 429 "dhcp4_parser.cc"
        break;

      case 205: // map_value
#line 263 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 435 "dhcp4_parser.cc"
        break;

      case 246: // ddns_replace_client_name_value
#line 263 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 441 "dhcp4_parser.cc"
        break;

      case 265: // socket_type
#line 263 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 447 "dhcp4_parser.cc"
        break;

      case 268: // outbound_interface_value
#line 263 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 453 "dhcp4_parser.cc"
        break;

      case 290: // db_type
#line 263 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 459 "dhcp4_parser.cc"
        break;

      case 377: // hr_mode
#line 263 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 465 "dhcp4_parser.cc"
        break;

      case 524: // ncr_protocol_value
#line 263 "dhcp4_parser.yy"
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
      case 201: // value
      case 205: // map_value
      case 246: // ddns_replace_client_name_value
      case 265: // socket_type
      case 268: // outbound_interface_value
      case 290: // db_type
      case 377: // hr_mode
      case 524: // ncr_protocol_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 184: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 183: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 182: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 181: // "constant string"
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
#line 272 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 738 "dhcp4_parser.cc"
    break;

  case 4:
#line 273 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.CONFIG; }
#line 744 "dhcp4_parser.cc"
    break;

  case 6:
#line 274 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.DHCP4; }
#line 750 "dhcp4_parser.cc"
    break;

  case 8:
#line 275 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 756 "dhcp4_parser.cc"
    break;

  case 10:
#line 276 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.SUBNET4; }
#line 762 "dhcp4_parser.cc"
    break;

  case 12:
#line 277 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.POOLS; }
#line 768 "dhcp4_parser.cc"
    break;

  case 14:
#line 278 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 774 "dhcp4_parser.cc"
    break;

  case 16:
#line 279 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.DHCP4; }
#line 780 "dhcp4_parser.cc"
    break;

  case 18:
#line 280 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 786 "dhcp4_parser.cc"
    break;

  case 20:
#line 281 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 792 "dhcp4_parser.cc"
    break;

  case 22:
#line 282 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 798 "dhcp4_parser.cc"
    break;

  case 24:
#line 283 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 804 "dhcp4_parser.cc"
    break;

  case 26:
#line 284 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.LOGGING; }
#line 810 "dhcp4_parser.cc"
    break;

  case 28:
#line 285 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 816 "dhcp4_parser.cc"
    break;

  case 30:
#line 293 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 822 "dhcp4_parser.cc"
    break;

  case 31:
#line 294 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 828 "dhcp4_parser.cc"
    break;

  case 32:
#line 295 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp4_parser.cc"
    break;

  case 33:
#line 296 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp4_parser.cc"
    break;

  case 34:
#line 297 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp4_parser.cc"
    break;

  case 35:
#line 298 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 852 "dhcp4_parser.cc"
    break;

  case 36:
#line 299 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 858 "dhcp4_parser.cc"
    break;

  case 37:
#line 302 "dhcp4_parser.yy"
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 867 "dhcp4_parser.cc"
    break;

  case 38:
#line 307 "dhcp4_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 878 "dhcp4_parser.cc"
    break;

  case 39:
#line 312 "dhcp4_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 888 "dhcp4_parser.cc"
    break;

  case 40:
#line 318 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 894 "dhcp4_parser.cc"
    break;

  case 43:
#line 325 "dhcp4_parser.yy"
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 903 "dhcp4_parser.cc"
    break;

  case 44:
#line 329 "dhcp4_parser.yy"
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 913 "dhcp4_parser.cc"
    break;

  case 45:
#line 336 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 922 "dhcp4_parser.cc"
    break;

  case 46:
#line 339 "dhcp4_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
}
#line 930 "dhcp4_parser.cc"
    break;

  case 49:
#line 347 "dhcp4_parser.yy"
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 939 "dhcp4_parser.cc"
    break;

  case 50:
#line 351 "dhcp4_parser.yy"
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 948 "dhcp4_parser.cc"
    break;

  case 51:
#line 358 "dhcp4_parser.yy"
    {
    // List parsing about to start
}
#line 956 "dhcp4_parser.cc"
    break;

  case 52:
#line 360 "dhcp4_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 965 "dhcp4_parser.cc"
    break;

  case 55:
#line 369 "dhcp4_parser.yy"
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 974 "dhcp4_parser.cc"
    break;

  case 56:
#line 373 "dhcp4_parser.yy"
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 983 "dhcp4_parser.cc"
    break;

  case 57:
#line 384 "dhcp4_parser.yy"
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 994 "dhcp4_parser.cc"
    break;

  case 58:
#line 394 "dhcp4_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1005 "dhcp4_parser.cc"
    break;

  case 59:
#line 399 "dhcp4_parser.yy"
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
#line 423 "dhcp4_parser.yy"
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
#line 430 "dhcp4_parser.yy"
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1041 "dhcp4_parser.cc"
    break;

  case 70:
#line 438 "dhcp4_parser.yy"
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1051 "dhcp4_parser.cc"
    break;

  case 71:
#line 442 "dhcp4_parser.yy"
    {
    // No global parameter is required
    // parsing completed
}
#line 1060 "dhcp4_parser.cc"
    break;

  case 122:
#line 503 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1069 "dhcp4_parser.cc"
    break;

  case 123:
#line 508 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1078 "dhcp4_parser.cc"
    break;

  case 124:
#line 513 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1087 "dhcp4_parser.cc"
    break;

  case 125:
#line 518 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1096 "dhcp4_parser.cc"
    break;

  case 126:
#line 523 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1105 "dhcp4_parser.cc"
    break;

  case 127:
#line 528 "dhcp4_parser.yy"
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1114 "dhcp4_parser.cc"
    break;

  case 128:
#line 533 "dhcp4_parser.yy"
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1123 "dhcp4_parser.cc"
    break;

  case 129:
#line 538 "dhcp4_parser.yy"
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1132 "dhcp4_parser.cc"
    break;

  case 130:
#line 543 "dhcp4_parser.yy"
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1141 "dhcp4_parser.cc"
    break;

  case 131:
#line 548 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1149 "dhcp4_parser.cc"
    break;

  case 132:
#line 550 "dhcp4_parser.yy"
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1159 "dhcp4_parser.cc"
    break;

  case 133:
#line 556 "dhcp4_parser.yy"
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1168 "dhcp4_parser.cc"
    break;

  case 134:
#line 561 "dhcp4_parser.yy"
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1177 "dhcp4_parser.cc"
    break;

  case 135:
#line 566 "dhcp4_parser.yy"
    {
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1186 "dhcp4_parser.cc"
    break;

  case 136:
#line 571 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1195 "dhcp4_parser.cc"
    break;

  case 137:
#line 576 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1204 "dhcp4_parser.cc"
    break;

  case 138:
#line 581 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1213 "dhcp4_parser.cc"
    break;

  case 139:
#line 586 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1221 "dhcp4_parser.cc"
    break;

  case 140:
#line 588 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1230 "dhcp4_parser.cc"
    break;

  case 141:
#line 594 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1238 "dhcp4_parser.cc"
    break;

  case 142:
#line 597 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1246 "dhcp4_parser.cc"
    break;

  case 143:
#line 600 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1254 "dhcp4_parser.cc"
    break;

  case 144:
#line 603 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1262 "dhcp4_parser.cc"
    break;

  case 145:
#line 606 "dhcp4_parser.yy"
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1271 "dhcp4_parser.cc"
    break;

  case 146:
#line 612 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1279 "dhcp4_parser.cc"
    break;

  case 147:
#line 614 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1289 "dhcp4_parser.cc"
    break;

  case 148:
#line 620 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1297 "dhcp4_parser.cc"
    break;

  case 149:
#line 622 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1307 "dhcp4_parser.cc"
    break;

  case 150:
#line 628 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1315 "dhcp4_parser.cc"
    break;

  case 151:
#line 630 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1325 "dhcp4_parser.cc"
    break;

  case 152:
#line 636 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1333 "dhcp4_parser.cc"
    break;

  case 153:
#line 638 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1343 "dhcp4_parser.cc"
    break;

  case 154:
#line 644 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1354 "dhcp4_parser.cc"
    break;

  case 155:
#line 649 "dhcp4_parser.yy"
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1364 "dhcp4_parser.cc"
    break;

  case 165:
#line 668 "dhcp4_parser.yy"
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1374 "dhcp4_parser.cc"
    break;

  case 166:
#line 672 "dhcp4_parser.yy"
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1383 "dhcp4_parser.cc"
    break;

  case 167:
#line 677 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1394 "dhcp4_parser.cc"
    break;

  case 168:
#line 682 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1403 "dhcp4_parser.cc"
    break;

  case 169:
#line 687 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1411 "dhcp4_parser.cc"
    break;

  case 170:
#line 689 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1420 "dhcp4_parser.cc"
    break;

  case 171:
#line 694 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1426 "dhcp4_parser.cc"
    break;

  case 172:
#line 695 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1432 "dhcp4_parser.cc"
    break;

  case 173:
#line 698 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1440 "dhcp4_parser.cc"
    break;

  case 174:
#line 700 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1449 "dhcp4_parser.cc"
    break;

  case 175:
#line 705 "dhcp4_parser.yy"
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1457 "dhcp4_parser.cc"
    break;

  case 176:
#line 707 "dhcp4_parser.yy"
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1465 "dhcp4_parser.cc"
    break;

  case 177:
#line 711 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1474 "dhcp4_parser.cc"
    break;

  case 178:
#line 717 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1485 "dhcp4_parser.cc"
    break;

  case 179:
#line 722 "dhcp4_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1496 "dhcp4_parser.cc"
    break;

  case 180:
#line 729 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1507 "dhcp4_parser.cc"
    break;

  case 181:
#line 734 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1516 "dhcp4_parser.cc"
    break;

  case 185:
#line 744 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1524 "dhcp4_parser.cc"
    break;

  case 186:
#line 746 "dhcp4_parser.yy"
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
#line 762 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1555 "dhcp4_parser.cc"
    break;

  case 188:
#line 767 "dhcp4_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1566 "dhcp4_parser.cc"
    break;

  case 189:
#line 774 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1577 "dhcp4_parser.cc"
    break;

  case 190:
#line 779 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1586 "dhcp4_parser.cc"
    break;

  case 195:
#line 792 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1596 "dhcp4_parser.cc"
    break;

  case 196:
#line 796 "dhcp4_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1606 "dhcp4_parser.cc"
    break;

  case 220:
#line 829 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1614 "dhcp4_parser.cc"
    break;

  case 221:
#line 831 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1623 "dhcp4_parser.cc"
    break;

  case 222:
#line 836 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1629 "dhcp4_parser.cc"
    break;

  case 223:
#line 837 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1635 "dhcp4_parser.cc"
    break;

  case 224:
#line 838 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1641 "dhcp4_parser.cc"
    break;

  case 225:
#line 839 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1647 "dhcp4_parser.cc"
    break;

  case 226:
#line 842 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1655 "dhcp4_parser.cc"
    break;

  case 227:
#line 844 "dhcp4_parser.yy"
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1665 "dhcp4_parser.cc"
    break;

  case 228:
#line 850 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1673 "dhcp4_parser.cc"
    break;

  case 229:
#line 852 "dhcp4_parser.yy"
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1683 "dhcp4_parser.cc"
    break;

  case 230:
#line 858 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1691 "dhcp4_parser.cc"
    break;

  case 231:
#line 860 "dhcp4_parser.yy"
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1701 "dhcp4_parser.cc"
    break;

  case 232:
#line 866 "dhcp4_parser.yy"
    {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1710 "dhcp4_parser.cc"
    break;

  case 233:
#line 871 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1718 "dhcp4_parser.cc"
    break;

  case 234:
#line 873 "dhcp4_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1728 "dhcp4_parser.cc"
    break;

  case 235:
#line 879 "dhcp4_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1737 "dhcp4_parser.cc"
    break;

  case 236:
#line 884 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1746 "dhcp4_parser.cc"
    break;

  case 237:
#line 889 "dhcp4_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1755 "dhcp4_parser.cc"
    break;

  case 238:
#line 894 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1764 "dhcp4_parser.cc"
    break;

  case 239:
#line 899 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1773 "dhcp4_parser.cc"
    break;

  case 240:
#line 904 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1782 "dhcp4_parser.cc"
    break;

  case 241:
#line 909 "dhcp4_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1791 "dhcp4_parser.cc"
    break;

  case 242:
#line 914 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1799 "dhcp4_parser.cc"
    break;

  case 243:
#line 916 "dhcp4_parser.yy"
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1809 "dhcp4_parser.cc"
    break;

  case 244:
#line 922 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1817 "dhcp4_parser.cc"
    break;

  case 245:
#line 924 "dhcp4_parser.yy"
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1827 "dhcp4_parser.cc"
    break;

  case 246:
#line 930 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1835 "dhcp4_parser.cc"
    break;

  case 247:
#line 932 "dhcp4_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1845 "dhcp4_parser.cc"
    break;

  case 248:
#line 938 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1853 "dhcp4_parser.cc"
    break;

  case 249:
#line 940 "dhcp4_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1863 "dhcp4_parser.cc"
    break;

  case 250:
#line 946 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1872 "dhcp4_parser.cc"
    break;

  case 251:
#line 951 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1881 "dhcp4_parser.cc"
    break;

  case 252:
#line 956 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1890 "dhcp4_parser.cc"
    break;

  case 253:
#line 962 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1901 "dhcp4_parser.cc"
    break;

  case 254:
#line 967 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1910 "dhcp4_parser.cc"
    break;

  case 262:
#line 983 "dhcp4_parser.yy"
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1919 "dhcp4_parser.cc"
    break;

  case 263:
#line 988 "dhcp4_parser.yy"
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1928 "dhcp4_parser.cc"
    break;

  case 264:
#line 993 "dhcp4_parser.yy"
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1937 "dhcp4_parser.cc"
    break;

  case 265:
#line 998 "dhcp4_parser.yy"
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1946 "dhcp4_parser.cc"
    break;

  case 266:
#line 1003 "dhcp4_parser.yy"
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1955 "dhcp4_parser.cc"
    break;

  case 267:
#line 1008 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1966 "dhcp4_parser.cc"
    break;

  case 268:
#line 1013 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1975 "dhcp4_parser.cc"
    break;

  case 273:
#line 1026 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1985 "dhcp4_parser.cc"
    break;

  case 274:
#line 1030 "dhcp4_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1995 "dhcp4_parser.cc"
    break;

  case 275:
#line 1036 "dhcp4_parser.yy"
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2005 "dhcp4_parser.cc"
    break;

  case 276:
#line 1040 "dhcp4_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2015 "dhcp4_parser.cc"
    break;

  case 282:
#line 1055 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2023 "dhcp4_parser.cc"
    break;

  case 283:
#line 1057 "dhcp4_parser.yy"
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2033 "dhcp4_parser.cc"
    break;

  case 284:
#line 1063 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2041 "dhcp4_parser.cc"
    break;

  case 285:
#line 1065 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2050 "dhcp4_parser.cc"
    break;

  case 286:
#line 1071 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2061 "dhcp4_parser.cc"
    break;

  case 287:
#line 1076 "dhcp4_parser.yy"
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2071 "dhcp4_parser.cc"
    break;

  case 296:
#line 1094 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2080 "dhcp4_parser.cc"
    break;

  case 297:
#line 1099 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2089 "dhcp4_parser.cc"
    break;

  case 298:
#line 1104 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2098 "dhcp4_parser.cc"
    break;

  case 299:
#line 1109 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2107 "dhcp4_parser.cc"
    break;

  case 300:
#line 1114 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2116 "dhcp4_parser.cc"
    break;

  case 301:
#line 1119 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2125 "dhcp4_parser.cc"
    break;

  case 302:
#line 1127 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2136 "dhcp4_parser.cc"
    break;

  case 303:
#line 1132 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2145 "dhcp4_parser.cc"
    break;

  case 308:
#line 1152 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2155 "dhcp4_parser.cc"
    break;

  case 309:
#line 1156 "dhcp4_parser.yy"
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
#line 1178 "dhcp4_parser.yy"
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2191 "dhcp4_parser.cc"
    break;

  case 311:
#line 1182 "dhcp4_parser.yy"
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2201 "dhcp4_parser.cc"
    break;

  case 351:
#line 1233 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2209 "dhcp4_parser.cc"
    break;

  case 352:
#line 1235 "dhcp4_parser.yy"
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2219 "dhcp4_parser.cc"
    break;

  case 353:
#line 1241 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2227 "dhcp4_parser.cc"
    break;

  case 354:
#line 1243 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2237 "dhcp4_parser.cc"
    break;

  case 355:
#line 1249 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2245 "dhcp4_parser.cc"
    break;

  case 356:
#line 1251 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2255 "dhcp4_parser.cc"
    break;

  case 357:
#line 1257 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2263 "dhcp4_parser.cc"
    break;

  case 358:
#line 1259 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2273 "dhcp4_parser.cc"
    break;

  case 359:
#line 1265 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2281 "dhcp4_parser.cc"
    break;

  case 360:
#line 1267 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2291 "dhcp4_parser.cc"
    break;

  case 361:
#line 1273 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2299 "dhcp4_parser.cc"
    break;

  case 362:
#line 1275 "dhcp4_parser.yy"
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2309 "dhcp4_parser.cc"
    break;

  case 363:
#line 1281 "dhcp4_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2320 "dhcp4_parser.cc"
    break;

  case 364:
#line 1286 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2329 "dhcp4_parser.cc"
    break;

  case 365:
#line 1291 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2337 "dhcp4_parser.cc"
    break;

  case 366:
#line 1293 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2346 "dhcp4_parser.cc"
    break;

  case 367:
#line 1298 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2352 "dhcp4_parser.cc"
    break;

  case 368:
#line 1299 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2358 "dhcp4_parser.cc"
    break;

  case 369:
#line 1300 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2364 "dhcp4_parser.cc"
    break;

  case 370:
#line 1301 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2370 "dhcp4_parser.cc"
    break;

  case 371:
#line 1304 "dhcp4_parser.yy"
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2379 "dhcp4_parser.cc"
    break;

  case 372:
#line 1311 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2390 "dhcp4_parser.cc"
    break;

  case 373:
#line 1316 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2399 "dhcp4_parser.cc"
    break;

  case 378:
#line 1331 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2409 "dhcp4_parser.cc"
    break;

  case 379:
#line 1335 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 2417 "dhcp4_parser.cc"
    break;

  case 414:
#line 1381 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2428 "dhcp4_parser.cc"
    break;

  case 415:
#line 1386 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2437 "dhcp4_parser.cc"
    break;

  case 416:
#line 1394 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2446 "dhcp4_parser.cc"
    break;

  case 417:
#line 1397 "dhcp4_parser.yy"
    {
    // parsing completed
}
#line 2454 "dhcp4_parser.cc"
    break;

  case 422:
#line 1413 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2464 "dhcp4_parser.cc"
    break;

  case 423:
#line 1417 "dhcp4_parser.yy"
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
#line 1428 "dhcp4_parser.yy"
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2486 "dhcp4_parser.cc"
    break;

  case 425:
#line 1432 "dhcp4_parser.yy"
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
#line 1464 "dhcp4_parser.yy"
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2507 "dhcp4_parser.cc"
    break;

  case 443:
#line 1471 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2515 "dhcp4_parser.cc"
    break;

  case 444:
#line 1473 "dhcp4_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2525 "dhcp4_parser.cc"
    break;

  case 445:
#line 1479 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2533 "dhcp4_parser.cc"
    break;

  case 446:
#line 1481 "dhcp4_parser.yy"
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2543 "dhcp4_parser.cc"
    break;

  case 447:
#line 1487 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2551 "dhcp4_parser.cc"
    break;

  case 448:
#line 1489 "dhcp4_parser.yy"
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2561 "dhcp4_parser.cc"
    break;

  case 450:
#line 1497 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2569 "dhcp4_parser.cc"
    break;

  case 451:
#line 1499 "dhcp4_parser.yy"
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2579 "dhcp4_parser.cc"
    break;

  case 452:
#line 1505 "dhcp4_parser.yy"
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2588 "dhcp4_parser.cc"
    break;

  case 453:
#line 1514 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2599 "dhcp4_parser.cc"
    break;

  case 454:
#line 1519 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2608 "dhcp4_parser.cc"
    break;

  case 459:
#line 1538 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2618 "dhcp4_parser.cc"
    break;

  case 460:
#line 1542 "dhcp4_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2627 "dhcp4_parser.cc"
    break;

  case 461:
#line 1550 "dhcp4_parser.yy"
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2637 "dhcp4_parser.cc"
    break;

  case 462:
#line 1554 "dhcp4_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2646 "dhcp4_parser.cc"
    break;

  case 477:
#line 1587 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2654 "dhcp4_parser.cc"
    break;

  case 478:
#line 1589 "dhcp4_parser.yy"
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2664 "dhcp4_parser.cc"
    break;

  case 481:
#line 1599 "dhcp4_parser.yy"
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2673 "dhcp4_parser.cc"
    break;

  case 482:
#line 1604 "dhcp4_parser.yy"
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2682 "dhcp4_parser.cc"
    break;

  case 483:
#line 1612 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2693 "dhcp4_parser.cc"
    break;

  case 484:
#line 1617 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2702 "dhcp4_parser.cc"
    break;

  case 489:
#line 1632 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2712 "dhcp4_parser.cc"
    break;

  case 490:
#line 1636 "dhcp4_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2722 "dhcp4_parser.cc"
    break;

  case 491:
#line 1642 "dhcp4_parser.yy"
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2732 "dhcp4_parser.cc"
    break;

  case 492:
#line 1646 "dhcp4_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2742 "dhcp4_parser.cc"
    break;

  case 502:
#line 1665 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2750 "dhcp4_parser.cc"
    break;

  case 503:
#line 1667 "dhcp4_parser.yy"
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2760 "dhcp4_parser.cc"
    break;

  case 504:
#line 1673 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2768 "dhcp4_parser.cc"
    break;

  case 505:
#line 1675 "dhcp4_parser.yy"
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
#line 1698 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2803 "dhcp4_parser.cc"
    break;

  case 507:
#line 1700 "dhcp4_parser.yy"
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
#line 1728 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2843 "dhcp4_parser.cc"
    break;

  case 509:
#line 1733 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2852 "dhcp4_parser.cc"
    break;

  case 514:
#line 1746 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2862 "dhcp4_parser.cc"
    break;

  case 515:
#line 1750 "dhcp4_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2871 "dhcp4_parser.cc"
    break;

  case 516:
#line 1755 "dhcp4_parser.yy"
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2881 "dhcp4_parser.cc"
    break;

  case 517:
#line 1759 "dhcp4_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2890 "dhcp4_parser.cc"
    break;

  case 537:
#line 1790 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2898 "dhcp4_parser.cc"
    break;

  case 538:
#line 1792 "dhcp4_parser.yy"
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2908 "dhcp4_parser.cc"
    break;

  case 539:
#line 1798 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2916 "dhcp4_parser.cc"
    break;

  case 540:
#line 1800 "dhcp4_parser.yy"
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2926 "dhcp4_parser.cc"
    break;

  case 541:
#line 1806 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2934 "dhcp4_parser.cc"
    break;

  case 542:
#line 1808 "dhcp4_parser.yy"
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2944 "dhcp4_parser.cc"
    break;

  case 543:
#line 1814 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2952 "dhcp4_parser.cc"
    break;

  case 544:
#line 1816 "dhcp4_parser.yy"
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2962 "dhcp4_parser.cc"
    break;

  case 545:
#line 1822 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2973 "dhcp4_parser.cc"
    break;

  case 546:
#line 1827 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2982 "dhcp4_parser.cc"
    break;

  case 547:
#line 1832 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2990 "dhcp4_parser.cc"
    break;

  case 548:
#line 1834 "dhcp4_parser.yy"
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3000 "dhcp4_parser.cc"
    break;

  case 549:
#line 1840 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3008 "dhcp4_parser.cc"
    break;

  case 550:
#line 1842 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3018 "dhcp4_parser.cc"
    break;

  case 551:
#line 1848 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3026 "dhcp4_parser.cc"
    break;

  case 552:
#line 1850 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3036 "dhcp4_parser.cc"
    break;

  case 553:
#line 1856 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3044 "dhcp4_parser.cc"
    break;

  case 554:
#line 1858 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3054 "dhcp4_parser.cc"
    break;

  case 555:
#line 1864 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3062 "dhcp4_parser.cc"
    break;

  case 556:
#line 1866 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3072 "dhcp4_parser.cc"
    break;

  case 557:
#line 1872 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3080 "dhcp4_parser.cc"
    break;

  case 558:
#line 1874 "dhcp4_parser.yy"
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3090 "dhcp4_parser.cc"
    break;

  case 559:
#line 1880 "dhcp4_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3101 "dhcp4_parser.cc"
    break;

  case 560:
#line 1885 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3110 "dhcp4_parser.cc"
    break;

  case 561:
#line 1893 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3121 "dhcp4_parser.cc"
    break;

  case 562:
#line 1898 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3130 "dhcp4_parser.cc"
    break;

  case 565:
#line 1910 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3141 "dhcp4_parser.cc"
    break;

  case 566:
#line 1915 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3150 "dhcp4_parser.cc"
    break;

  case 569:
#line 1924 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3160 "dhcp4_parser.cc"
    break;

  case 570:
#line 1928 "dhcp4_parser.yy"
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3170 "dhcp4_parser.cc"
    break;

  case 587:
#line 1957 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3178 "dhcp4_parser.cc"
    break;

  case 588:
#line 1959 "dhcp4_parser.yy"
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3188 "dhcp4_parser.cc"
    break;

  case 589:
#line 1965 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3197 "dhcp4_parser.cc"
    break;

  case 590:
#line 1974 "dhcp4_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3206 "dhcp4_parser.cc"
    break;

  case 591:
#line 1981 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3217 "dhcp4_parser.cc"
    break;

  case 592:
#line 1986 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3226 "dhcp4_parser.cc"
    break;

  case 600:
#line 2002 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3234 "dhcp4_parser.cc"
    break;

  case 601:
#line 2004 "dhcp4_parser.yy"
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3244 "dhcp4_parser.cc"
    break;

  case 602:
#line 2010 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3252 "dhcp4_parser.cc"
    break;

  case 603:
#line 2012 "dhcp4_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3262 "dhcp4_parser.cc"
    break;

  case 604:
#line 2021 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3270 "dhcp4_parser.cc"
    break;

  case 605:
#line 2023 "dhcp4_parser.yy"
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
#line 3308 "dhcp4_parser.cc"
    break;

  case 606:
#line 2059 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3319 "dhcp4_parser.cc"
    break;

  case 607:
#line 2064 "dhcp4_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3330 "dhcp4_parser.cc"
    break;

  case 608:
#line 2071 "dhcp4_parser.yy"
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3340 "dhcp4_parser.cc"
    break;

  case 609:
#line 2075 "dhcp4_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3350 "dhcp4_parser.cc"
    break;

  case 630:
#line 2105 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3359 "dhcp4_parser.cc"
    break;

  case 631:
#line 2110 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3367 "dhcp4_parser.cc"
    break;

  case 632:
#line 2112 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3377 "dhcp4_parser.cc"
    break;

  case 633:
#line 2118 "dhcp4_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3386 "dhcp4_parser.cc"
    break;

  case 634:
#line 2123 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3394 "dhcp4_parser.cc"
    break;

  case 635:
#line 2125 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3404 "dhcp4_parser.cc"
    break;

  case 636:
#line 2131 "dhcp4_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3413 "dhcp4_parser.cc"
    break;

  case 637:
#line 2136 "dhcp4_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3422 "dhcp4_parser.cc"
    break;

  case 638:
#line 2141 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3430 "dhcp4_parser.cc"
    break;

  case 639:
#line 2143 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3439 "dhcp4_parser.cc"
    break;

  case 640:
#line 2149 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3445 "dhcp4_parser.cc"
    break;

  case 641:
#line 2150 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3451 "dhcp4_parser.cc"
    break;

  case 642:
#line 2153 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3459 "dhcp4_parser.cc"
    break;

  case 643:
#line 2155 "dhcp4_parser.yy"
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3469 "dhcp4_parser.cc"
    break;

  case 644:
#line 2162 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3477 "dhcp4_parser.cc"
    break;

  case 645:
#line 2164 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3487 "dhcp4_parser.cc"
    break;

  case 646:
#line 2171 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3496 "dhcp4_parser.cc"
    break;

  case 647:
#line 2177 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3505 "dhcp4_parser.cc"
    break;

  case 648:
#line 2183 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3513 "dhcp4_parser.cc"
    break;

  case 649:
#line 2185 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3522 "dhcp4_parser.cc"
    break;

  case 650:
#line 2191 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3530 "dhcp4_parser.cc"
    break;

  case 651:
#line 2193 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3540 "dhcp4_parser.cc"
    break;

  case 652:
#line 2200 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3548 "dhcp4_parser.cc"
    break;

  case 653:
#line 2202 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3558 "dhcp4_parser.cc"
    break;

  case 654:
#line 2209 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3566 "dhcp4_parser.cc"
    break;

  case 655:
#line 2211 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3576 "dhcp4_parser.cc"
    break;

  case 656:
#line 2220 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3584 "dhcp4_parser.cc"
    break;

  case 657:
#line 2222 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3593 "dhcp4_parser.cc"
    break;

  case 658:
#line 2227 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3601 "dhcp4_parser.cc"
    break;

  case 659:
#line 2229 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3610 "dhcp4_parser.cc"
    break;

  case 660:
#line 2234 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3618 "dhcp4_parser.cc"
    break;

  case 661:
#line 2236 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3627 "dhcp4_parser.cc"
    break;

  case 662:
#line 2241 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3638 "dhcp4_parser.cc"
    break;

  case 663:
#line 2246 "dhcp4_parser.yy"
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3648 "dhcp4_parser.cc"
    break;

  case 664:
#line 2252 "dhcp4_parser.yy"
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3658 "dhcp4_parser.cc"
    break;

  case 665:
#line 2256 "dhcp4_parser.yy"
    {
    // No config_control params are required
    // parsing completed
}
#line 3667 "dhcp4_parser.cc"
    break;

  case 670:
#line 2271 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3678 "dhcp4_parser.cc"
    break;

  case 671:
#line 2276 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3687 "dhcp4_parser.cc"
    break;

  case 672:
#line 2281 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3696 "dhcp4_parser.cc"
    break;

  case 673:
#line 2291 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3707 "dhcp4_parser.cc"
    break;

  case 674:
#line 2296 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3716 "dhcp4_parser.cc"
    break;

  case 675:
#line 2301 "dhcp4_parser.yy"
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3726 "dhcp4_parser.cc"
    break;

  case 676:
#line 2305 "dhcp4_parser.yy"
    {
    // parsing completed
}
#line 3734 "dhcp4_parser.cc"
    break;

  case 680:
#line 2321 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3745 "dhcp4_parser.cc"
    break;

  case 681:
#line 2326 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3754 "dhcp4_parser.cc"
    break;

  case 684:
#line 2338 "dhcp4_parser.yy"
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3764 "dhcp4_parser.cc"
    break;

  case 685:
#line 2342 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3772 "dhcp4_parser.cc"
    break;

  case 695:
#line 2359 "dhcp4_parser.yy"
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3781 "dhcp4_parser.cc"
    break;

  case 696:
#line 2364 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3789 "dhcp4_parser.cc"
    break;

  case 697:
#line 2366 "dhcp4_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3799 "dhcp4_parser.cc"
    break;

  case 698:
#line 2372 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3810 "dhcp4_parser.cc"
    break;

  case 699:
#line 2377 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3819 "dhcp4_parser.cc"
    break;

  case 702:
#line 2386 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3829 "dhcp4_parser.cc"
    break;

  case 703:
#line 2390 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3837 "dhcp4_parser.cc"
    break;

  case 711:
#line 2405 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3845 "dhcp4_parser.cc"
    break;

  case 712:
#line 2407 "dhcp4_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3855 "dhcp4_parser.cc"
    break;

  case 713:
#line 2413 "dhcp4_parser.yy"
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3864 "dhcp4_parser.cc"
    break;

  case 714:
#line 2418 "dhcp4_parser.yy"
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3873 "dhcp4_parser.cc"
    break;

  case 715:
#line 2423 "dhcp4_parser.yy"
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3882 "dhcp4_parser.cc"
    break;

  case 716:
#line 2428 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3890 "dhcp4_parser.cc"
    break;

  case 717:
#line 2430 "dhcp4_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 3900 "dhcp4_parser.cc"
    break;


#line 3904 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -896;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     479,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,    50,    22,    52,    70,    75,
      81,    96,   106,   110,   132,   138,   153,   219,   226,   255,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,    22,  -149,
      20,   150,    59,   266,    66,   207,   -39,   448,   528,   -71,
     546,  -111,   125,  -896,    60,    67,    76,   162,   188,  -896,
    -896,  -896,  -896,  -896,   198,  -896,    48,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,   265,   293,   296,  -896,
    -896,  -896,  -896,  -896,  -896,   300,   310,   317,   335,   339,
     352,   385,   386,   387,  -896,   388,   389,   390,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,   391,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,    92,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,   392,  -896,    99,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,   393,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,   163,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,   184,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,   251,   343,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,   356,  -896,
    -896,   394,  -896,  -896,  -896,   396,  -896,  -896,   359,   372,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,   397,   399,  -896,  -896,  -896,  -896,   370,
     401,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,   221,  -896,  -896,  -896,   402,  -896,  -896,
     403,  -896,   404,   406,  -896,  -896,   407,   408,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,   222,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,   231,  -896,  -896,  -896,   410,   240,  -896,  -896,
    -896,  -896,    22,    22,  -896,   235,   417,   418,   420,   421,
     423,  -896,    20,  -896,   426,   429,   431,   254,   256,   258,
     432,   435,   440,   446,   449,   450,   273,   274,   277,   278,
     287,   286,   275,   288,   292,   468,   301,   307,   308,   472,
     473,   480,   491,   495,   499,   502,   506,   507,   510,   511,
     513,   519,   520,   521,   314,   522,   524,   527,   532,   533,
     534,   150,  -896,   537,   538,   539,   361,    59,  -896,   540,
     542,   543,   544,   553,   554,   350,   562,   563,   564,   266,
    -896,   565,    66,  -896,   568,   569,   570,   571,   573,   576,
     577,   581,  -896,   207,  -896,   583,   585,   409,   586,   588,
     589,   412,  -896,   448,   590,   413,   415,  -896,   528,   598,
     599,    34,  -896,   430,   600,   601,   433,   609,   439,   441,
     613,   618,   442,   443,   620,   621,   624,   626,   546,  -896,
    -111,  -896,   627,   451,   125,  -896,  -896,  -896,   631,   632,
     633,    22,    22,    22,  -896,   634,   635,   636,  -896,  -896,
    -896,   481,   482,   483,   653,   654,   660,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,   486,  -896,  -896,  -896,
     -87,   488,   489,   666,   667,   669,   670,   671,   496,   191,
     687,   688,   689,   690,   693,  -896,   694,   671,   695,   515,
     516,   698,  -896,   699,   145,   290,  -896,  -896,   525,   526,
     529,   700,   530,   531,  -896,   699,   535,   701,  -896,   536,
    -896,   699,   541,   545,   547,   548,   549,   550,   551,  -896,
     552,   555,  -896,   556,   557,   558,  -896,  -896,   559,  -896,
    -896,  -896,   560,    22,  -896,  -896,   561,   566,  -896,   567,
    -896,  -896,    19,   572,  -896,  -896,   -87,   574,   575,   578,
    -896,  -896,   708,  -896,  -896,    22,   150,  -111,  -896,  -896,
    -896,   125,    59,   652,  -896,  -896,  -896,    80,    80,   707,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,   711,
     713,   714,   716,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,   155,   717,   718,   727,    74,   102,  -896,   546,  -896,
    -896,   728,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,   736,  -896,  -896,  -896,  -896,   157,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,   707,  -896,   242,
     246,   250,   252,  -896,   268,  -896,  -896,  -896,  -896,  -896,
    -896,   740,   741,   742,   745,   746,  -896,  -896,  -896,  -896,
     747,   748,   749,   750,   753,   754,  -896,   272,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,   276,
    -896,   709,   757,  -896,  -896,   755,   759,  -896,  -896,   758,
     760,  -896,  -896,   761,   762,  -896,  -896,   763,   765,  -896,
    -896,  -896,  -896,  -896,  -896,    37,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,    73,  -896,  -896,   764,   768,  -896,  -896,
     766,   770,  -896,   771,   772,   773,   774,   775,   776,   298,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,   304,  -896,  -896,  -896,   305,  -896,    83,  -896,
     593,  -896,   777,   778,  -896,  -896,  -896,  -896,   779,   780,
    -896,  -896,  -896,  -896,   781,   652,  -896,   784,   785,   786,
     787,   584,   608,   602,   610,   611,   791,   792,   793,   794,
     617,   619,   622,   623,   616,   625,    80,  -896,  -896,    80,
    -896,   707,   266,  -896,   711,   448,  -896,   713,   528,  -896,
     714,   492,  -896,   716,   155,  -896,    63,   717,  -896,   207,
    -896,   718,   -71,  -896,   727,   628,   629,   630,   637,   638,
     639,    74,  -896,   798,   799,   102,  -896,  -896,   195,   728,
    -896,  -896,   800,   805,    66,  -896,   736,   809,  -896,  -896,
     641,  -896,   348,   642,   643,   644,  -896,  -896,  -896,  -896,
    -896,   645,   646,   647,   648,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,   342,  -896,   344,  -896,   801,  -896,   806,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,   360,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,   811,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,   808,   814,  -896,
    -896,  -896,  -896,  -896,   810,  -896,   362,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,   649,   650,  -896,  -896,   829,
    -896,  -896,  -896,  -896,  -896,   363,  -896,  -896,  -896,  -896,
    -896,  -896,   656,   371,  -896,   699,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,   492,  -896,   830,   655,  -896,    63,  -896,
    -896,  -896,  -896,   836,   661,   841,   195,  -896,  -896,  -896,
    -896,  -896,   673,  -896,  -896,   842,  -896,   674,  -896,  -896,
     851,  -896,  -896,    93,  -896,   -14,   851,  -896,  -896,   856,
     857,   859,  -896,   374,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,   862,   686,   691,   702,   873,   -14,  -896,   712,  -896,
    -896,  -896,   724,  -896,  -896,  -896
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
     275,    23,   608,    25,   675,    27,   664,    29,    47,    41,
       0,     0,     0,     0,     0,   518,     0,   426,   463,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     673,   656,   658,   660,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   662,   154,   180,     0,     0,     0,   537,
     539,   541,   178,   187,   189,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   131,     0,     0,     0,   139,   146,
     148,   302,   414,   453,   372,   504,   506,   365,   253,   565,
     508,   267,   286,     0,   591,   604,   606,   150,   152,   680,
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
     282,   284,   279,     0,   277,   280,   281,     0,   644,   631,
       0,   634,     0,     0,   638,   642,     0,     0,   648,   650,
     652,   654,   629,   627,   628,     0,   610,   612,   613,   614,
     615,   616,   617,   618,   619,   624,   620,   621,   622,   623,
     625,   626,     0,   677,   679,   670,     0,     0,   666,   668,
     669,    46,     0,     0,    39,     0,     0,     0,     0,     0,
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
       0,     0,     0,     0,     0,     0,     0,     0,     0,   609,
       0,   676,     0,     0,     0,   665,    50,    43,     0,     0,
       0,     0,     0,     0,    61,     0,     0,     0,   133,   134,
     135,     0,     0,     0,     0,     0,     0,   122,   123,   124,
     125,   126,   127,   128,   129,   130,     0,   136,   137,   138,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   590,     0,     0,     0,     0,
       0,     0,    73,     0,     0,     0,   177,   157,     0,     0,
       0,     0,     0,     0,   371,     0,     0,     0,   313,     0,
     494,     0,     0,     0,     0,     0,     0,     0,     0,   521,
       0,     0,   441,     0,     0,     0,   452,   429,     0,   481,
     482,   466,     0,     0,   278,   630,     0,     0,   633,     0,
     636,   637,     0,     0,   646,   647,     0,     0,     0,     0,
     611,   678,     0,   672,   667,     0,     0,     0,   657,   659,
     661,     0,     0,     0,   538,   540,   542,     0,     0,   191,
     132,   141,   142,   143,   144,   145,   140,   147,   149,   304,
     418,   455,   374,    40,   505,   507,   367,   368,   369,   370,
     366,     0,     0,   510,   269,     0,     0,   605,     0,   151,
     153,     0,    51,   168,   171,   172,   170,   175,   176,   174,
     354,   356,   358,   485,   352,   360,   364,   362,     0,   503,
     560,   548,   550,   554,   552,   558,   556,   544,   444,   234,
     448,   446,   451,   478,   283,   285,   645,   632,   635,   640,
     641,   639,   643,   649,   651,   653,   655,   191,    44,     0,
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
     597,   598,     0,   593,   595,   596,     0,   684,     0,   682,
      53,   489,     0,   486,   487,   545,   563,   564,     0,     0,
      69,   674,   663,   155,     0,     0,   181,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   179,   188,     0,
     190,     0,     0,   303,     0,   426,   415,     0,   463,   454,
       0,     0,   373,     0,     0,   254,   571,     0,   566,   518,
     509,     0,     0,   268,     0,     0,     0,     0,     0,     0,
       0,     0,   287,     0,     0,     0,   592,   607,     0,     0,
     681,    55,     0,    54,     0,   484,     0,     0,   562,   671,
       0,   183,     0,     0,     0,     0,   232,   235,   236,   237,
     238,     0,     0,     0,     0,   250,   251,   239,   240,   241,
     252,   198,     0,   194,     0,   307,     0,   421,     0,   458,
     413,   397,   398,   399,   385,   386,   402,   403,   404,   388,
     389,   405,   406,   407,   408,   409,   410,   411,   412,   382,
     383,   384,   395,   396,   394,     0,   380,   387,   400,   401,
     390,   391,   392,   393,   377,   256,   587,     0,   585,   586,
     578,   579,   583,   584,   580,   581,   582,     0,   572,   573,
     575,   576,   577,   568,     0,   513,     0,   272,   296,   297,
     298,   299,   300,   301,   289,     0,     0,   594,   698,     0,
     696,   694,   688,   692,   693,     0,   686,   690,   691,   689,
     683,    52,     0,     0,   488,     0,   186,   222,   223,   224,
     225,   221,   227,   229,   231,   243,   245,   247,   249,   196,
     309,   423,   460,     0,   379,     0,     0,   570,     0,   515,
     274,   601,   603,     0,     0,     0,     0,   685,    56,   490,
     546,   381,     0,   589,   574,     0,   695,     0,   687,   588,
       0,   697,   702,     0,   700,     0,     0,   699,   711,     0,
       0,     0,   716,     0,   704,   706,   707,   708,   709,   710,
     701,     0,     0,     0,     0,     0,     0,   703,     0,   713,
     714,   715,     0,   705,   712,   717
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,   -44,  -896,  -531,  -896,
     205,  -896,  -896,  -896,  -896,  -896,  -896,  -556,  -896,  -896,
    -896,   -70,  -896,  -896,  -896,   487,  -896,  -896,  -896,  -896,
     244,   444,   -54,   -24,    -5,    -4,    -1,    11,    14,    17,
    -896,  -896,  -896,  -896,    21,    25,    28,    31,    32,    33,
    -896,   245,    35,  -896,    36,  -896,    38,  -896,    39,  -896,
    -896,  -896,   279,   463,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
      78,  -896,  -896,  -896,  -896,  -896,  -896,   211,  -896,    55,
    -896,  -643,    61,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,   -36,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,    45,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,    27,  -896,  -896,  -896,
      40,   457,  -896,  -896,  -896,  -896,  -896,  -896,  -896,    29,
    -896,  -896,  -896,  -896,  -896,  -896,  -895,  -896,  -896,  -896,
      57,  -896,  -896,  -896,    62,   494,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -894,  -896,    41,  -896,    44,  -896,
      43,  -896,  -896,  -896,  -896,  -896,  -896,  -896,    53,  -896,
    -896,  -118,   -65,  -896,  -896,  -896,  -896,  -896,    64,  -896,
    -896,  -896,    65,  -896,   474,  -896,   -72,  -896,  -896,  -896,
    -896,  -896,   -64,  -896,  -896,  -896,  -896,  -896,   -40,  -896,
    -896,  -896,    58,  -896,  -896,  -896,    68,  -896,   471,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
      26,  -896,  -896,  -896,    30,   501,  -896,  -896,   -52,  -896,
     -20,  -896,   -60,  -896,  -896,  -896,    54,  -896,  -896,  -896,
      71,  -896,   497,    -8,  -896,    -2,  -896,    10,  -896,   269,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -893,  -896,  -896,
    -896,  -896,  -896,    69,  -896,  -896,  -896,  -110,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,    46,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,   291,   464,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,  -896,   332,   460,  -896,  -896,  -896,  -896,
    -896,  -896,  -896,   340,   469,   -69,  -896,  -896,    56,  -896,
    -896,  -105,  -896,  -896,  -896,  -896,  -896,  -896,  -124,  -896,
    -896,  -143,  -896,  -896,  -896,  -896,  -896,  -896,  -896
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     674,    87,    88,    41,    68,    84,    85,   693,   860,   942,
     943,   766,    43,    70,    96,    97,    98,   396,    45,    71,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   425,   163,   164,   165,   166,   167,   168,   169,
     429,   666,   170,   430,   171,   431,   172,   448,   173,   449,
     174,   405,   205,   206,    47,    72,   207,   453,   208,   454,
     696,   209,   455,   699,   210,   175,   413,   176,   406,   744,
     745,   746,   874,   177,   414,   178,   415,   791,   792,   793,
     899,   767,   768,   769,   877,  1071,   770,   878,   771,   879,
     772,   880,   773,   774,   486,   775,   776,   777,   778,   779,
     780,   781,   782,   886,   783,   887,   784,   888,   785,   889,
     786,   787,   788,   179,   439,   815,   816,   817,   818,   819,
     820,   821,   180,   442,   830,   831,   832,   922,    61,    79,
     343,   344,   345,   499,   346,   500,   181,   443,   839,   840,
     841,   842,   843,   844,   845,   846,   182,   432,   795,   796,
     797,   902,    49,    73,   242,   243,   244,   463,   245,   459,
     246,   460,   247,   461,   248,   464,   249,   467,   250,   466,
     183,   438,   680,   252,   184,   435,   807,   808,   809,   911,
    1005,  1006,   185,   433,    55,    76,   799,   800,   801,   905,
      57,    77,   308,   309,   310,   311,   312,   313,   314,   485,
     315,   489,   316,   488,   317,   318,   490,   319,   186,   434,
     803,   804,   805,   908,    59,    78,   329,   330,   331,   332,
     333,   494,   334,   335,   336,   337,   254,   462,   862,   863,
     864,   944,    51,    74,   267,   268,   269,   471,   187,   436,
     188,   437,   189,   441,   826,   827,   828,   919,    53,    75,
     284,   285,   286,   190,   410,   191,   411,   192,   412,   290,
     481,   867,   947,   291,   475,   292,   476,   293,   478,   294,
     477,   295,   480,   296,   479,   297,   474,   261,   468,   868,
     193,   440,   823,   824,   916,  1027,  1028,  1029,  1030,  1031,
    1085,  1032,   194,   195,   445,   852,   853,   854,   933,   855,
     934,   196,   446,   197,   447,    63,    80,   365,   366,   367,
     368,   505,   369,   370,   507,   371,   372,   373,   510,   731,
     374,   511,   375,   504,   376,   377,   378,   514,   379,   515,
     380,   516,   381,   517,    99,   398,   100,   399,   101,   400,
     198,   404,    67,    82,   387,   388,   389,   522,   390,   102,
     397,    65,    81,   382,   383,   199,   450,   858,   859,   938,
    1055,  1056,  1057,  1058,  1095,  1059,  1093,  1113,  1114,  1115,
    1123,  1124,  1125,  1131,  1126,  1127,  1128,  1129,  1135
  };

  const unsigned short
  Dhcp4Parser::yytable_[] =
  {
      95,   150,   204,   223,   263,   280,   327,   306,   325,   342,
     362,   298,   384,   257,   328,   789,  1000,  1001,  1013,   224,
     211,   255,   270,   282,    83,   320,   338,    31,   363,    32,
      89,    33,    86,   253,   266,   281,   673,   729,   132,   706,
     914,   307,   326,   915,   149,   710,   673,   340,   341,   225,
      30,   402,   212,   256,   271,   283,   403,   321,   339,    42,
     364,   661,   662,   663,   664,   258,   391,   287,   226,   227,
     392,   259,   228,   288,   200,   201,   917,    44,   202,   918,
     393,   203,    46,   260,   229,   289,   939,   230,    48,   940,
     231,   109,   110,   111,   232,   451,  1116,   665,   233,  1117,
     452,   234,   457,    50,   235,   236,   237,   458,   238,   239,
      94,   240,   241,    52,   747,   264,   251,    54,   265,   748,
     749,   750,   751,   752,   753,   754,   755,   756,   757,   758,
     759,   760,   761,   762,   763,   764,   765,   385,   386,    56,
     132,   133,   300,  1118,   133,    58,  1119,  1120,  1121,  1122,
     135,   136,   340,   341,   135,   136,   262,   135,   136,   300,
      60,   103,   694,   695,   104,   730,   469,  1016,  1017,   220,
     394,   470,   221,   105,    90,   106,   107,   108,   109,   110,
     111,   112,   113,   114,    91,    92,    93,   472,  1000,  1001,
    1013,   395,   473,   135,   136,   833,   834,   835,   836,   837,
     838,    94,   401,    34,    35,    36,    37,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   501,   518,    62,   132,   133,   502,
     519,   847,   848,    64,   520,   109,   110,   111,   134,   521,
      94,   135,   136,   524,    94,   451,   137,    94,   525,   520,
     870,   138,   139,   524,   871,   457,   972,   140,   872,   482,
     873,    94,    66,   810,   811,   812,   813,   141,   814,   407,
     142,   875,   279,   865,   300,   896,   876,   143,   144,   896,
     897,   145,   146,    94,   898,   133,   135,   136,   676,   677,
     678,   679,   107,   108,   109,   110,   111,   408,   135,   136,
     409,   931,   147,   148,   416,   149,   932,   935,   518,   272,
     697,   698,   936,   937,   417,   273,   274,   275,   276,   277,
     278,   418,   279,   115,   116,   117,   118,   119,   120,   121,
     122,    94,    95,   125,   126,   127,   128,   129,   130,   419,
     213,   214,   215,   420,   133,   896,   483,   469,   526,   527,
    1079,  1048,  1080,  1049,  1050,   216,   421,   135,   136,   217,
     218,   219,   137,  1083,   484,   501,  1096,   492,  1084,   220,
    1090,  1097,   221,   140,   472,   493,    94,  1136,   497,  1099,
     222,   150,  1137,  1067,  1068,  1069,  1070,   204,    94,   422,
     423,   424,   426,   427,   428,   444,   456,   465,   487,   223,
     491,   495,   263,   496,   498,   211,   503,   506,   508,   257,
     509,   512,   513,   280,   523,   224,   528,   255,   147,   148,
     270,   529,   530,   306,   531,   532,   327,   533,   325,   253,
     535,   282,   266,   536,   328,   537,   541,   212,   538,   542,
     539,   320,   540,   281,   543,   225,   338,    94,   362,   256,
     544,   384,   271,   545,   546,   547,   548,   307,   553,   549,
     550,   258,   326,   283,   226,   227,   363,   259,   228,   551,
     552,   554,   556,   321,   555,   287,   560,   561,   339,   260,
     229,   288,   299,   230,   562,   557,   231,   648,   649,   650,
     232,   558,   559,   289,   233,   563,   575,   234,   364,   564,
     235,   236,   237,   565,   238,   239,   566,   240,   241,  1100,
     567,   568,   251,   264,   569,   570,   265,   571,   107,   108,
     109,   110,   111,   572,   573,   574,   576,   300,   577,   301,
     302,   578,   594,   303,   304,   305,   579,   580,   581,   135,
     136,   583,   584,   585,   588,   586,   589,   590,   591,   115,
     116,   117,   118,   119,   120,   121,   122,   592,   593,   125,
     126,   127,   128,   129,   130,   131,   595,   596,   597,   599,
     133,   300,   601,   602,   603,   604,   150,   605,   384,   725,
     606,   607,   204,   135,   136,   608,   218,   610,   137,   611,
     613,   612,   614,   615,   618,   220,   616,   619,   221,   620,
     211,   738,   622,   623,   626,   627,   222,   300,   322,   301,
     302,   323,   324,   629,   625,   628,   849,   632,   362,   135,
     136,   630,   633,   631,   636,   637,   634,   635,   638,    94,
     639,   642,   212,   643,   850,   645,   363,   135,   136,   646,
     647,   651,   652,   653,   147,   148,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
     657,   658,   654,   655,   656,   659,   851,   660,   364,   667,
     668,   669,   670,    94,   671,   672,   743,   675,    32,   347,
     348,   349,   350,   351,   352,   353,   354,   355,   356,   357,
     358,   359,   681,   682,   683,   684,   689,   690,   360,   361,
     685,   686,   688,   691,   692,   703,   700,   701,   708,    94,
     702,   704,   705,   737,   790,   900,   707,   709,   794,   732,
     798,   802,   711,   806,   822,   825,   712,    94,   713,   714,
     715,   716,   717,   718,   829,   857,   719,   720,   721,   722,
     723,   724,   726,   861,   881,   882,   883,   727,   728,   884,
     885,   890,   891,   892,   893,   734,   735,   894,   895,   736,
     901,   903,   904,   907,   906,   910,   956,   909,   913,   912,
     920,   921,   923,   924,   941,   925,   926,   927,   928,   929,
     930,   946,   687,   945,   958,   950,   949,   948,   952,   953,
     954,   955,   957,   960,   959,   961,   962,   963,   964,   965,
     969,   966,  1045,  1046,   967,   968,  1061,   970,  1062,  1081,
    1038,  1039,  1040,  1065,  1082,  1086,  1087,  1088,  1089,  1041,
    1042,  1043,  1066,  1072,  1073,  1074,  1075,  1076,  1077,  1078,
    1091,  1092,   223,  1094,  1102,   306,   327,  1098,   325,  1103,
    1105,   980,   257,  1106,   328,  1107,  1018,  1110,   224,   280,
     255,  1020,   342,   320,  1109,  1111,   338,   981,  1112,  1008,
    1132,  1133,   253,  1134,  1022,   849,  1138,   282,  1051,   307,
    1139,  1007,   326,  1140,   263,   999,  1021,  1142,   225,   281,
    1019,   733,   256,   850,  1141,   321,  1053,   982,   339,   534,
     739,  1009,   270,  1144,   258,   582,  1023,   226,   227,   283,
     259,   228,  1052,  1010,   266,  1145,   983,   984,  1024,  1011,
     985,   287,   260,   229,  1025,   851,   230,   288,  1054,   231,
     587,  1012,   986,   232,   271,   987,  1026,   233,   988,   289,
     234,   742,   989,   235,   236,   237,   990,   238,   239,   991,
     240,   241,   992,   993,   994,   251,   995,   996,   869,   997,
     998,  1037,  1002,   951,  1004,  1003,   973,   971,   624,  1015,
    1044,   975,  1036,   598,   974,  1101,  1014,   617,   979,   621,
     976,   977,  1064,   600,  1063,  1035,   978,   866,  1104,   856,
     609,  1047,   640,   741,   644,   264,  1033,   740,   265,   641,
    1034,  1108,  1130,  1143,     0,  1060,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   980,     0,     0,     0,     0,  1018,     0,
       0,     0,     0,  1020,     0,     0,  1051,     0,     0,   981,
       0,  1008,     0,     0,     0,     0,  1022,     0,     0,     0,
       0,     0,     0,  1007,  1053,     0,     0,   999,  1021,     0,
       0,     0,  1019,     0,     0,     0,     0,     0,     0,   982,
    1052,     0,     0,  1009,     0,     0,     0,     0,  1023,     0,
       0,     0,     0,     0,     0,  1010,  1054,     0,   983,   984,
    1024,  1011,   985,     0,     0,     0,  1025,     0,     0,     0,
       0,     0,     0,  1012,   986,     0,     0,   987,  1026,     0,
     988,     0,     0,     0,   989,     0,     0,     0,   990,     0,
       0,   991,     0,     0,   992,   993,   994,     0,   995,   996,
       0,   997,   998,     0,  1002,     0,  1004,  1003
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    78,    77,    78,    79,
      80,    76,    81,    73,    78,   658,   911,   911,   911,    73,
      72,    73,    74,    75,    68,    77,    78,     5,    80,     7,
      10,     9,   181,    73,    74,    75,   567,    18,    77,   595,
       3,    77,    78,     6,   155,   601,   577,   118,   119,    73,
       0,     3,    72,    73,    74,    75,     8,    77,    78,     7,
      80,   148,   149,   150,   151,    73,     6,    75,    73,    73,
       3,    73,    73,    75,    15,    16,     3,     7,    19,     6,
       4,    22,     7,    73,    73,    75,     3,    73,     7,     6,
      73,    28,    29,    30,    73,     3,     3,   184,    73,     6,
       8,    73,     3,     7,    73,    73,    73,     8,    73,    73,
     181,    73,    73,     7,    34,    74,    73,     7,    74,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    12,    13,     7,
      77,    78,    79,   157,    78,     7,   160,   161,   162,   163,
      91,    92,   118,   119,    91,    92,    90,    91,    92,    79,
       7,    11,    17,    18,    14,   146,     3,   104,   105,   103,
       8,     8,   106,    23,   154,    25,    26,    27,    28,    29,
      30,    31,    32,    33,   164,   165,   166,     3,  1083,  1083,
    1083,     3,     8,    91,    92,   121,   122,   123,   124,   125,
     126,   181,     4,   181,   182,   183,   184,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,     3,     3,     7,    77,    78,     8,
       8,   129,   130,     7,     3,    28,    29,    30,    88,     8,
     181,    91,    92,     3,   181,     3,    96,   181,     8,     3,
       8,   101,   102,     3,     8,     3,   899,   107,     8,     8,
       8,   181,     7,   108,   109,   110,   111,   117,   113,     4,
     120,     3,   115,   116,    79,     3,     8,   127,   128,     3,
       8,   131,   132,   181,     8,    78,    91,    92,    97,    98,
      99,   100,    26,    27,    28,    29,    30,     4,    91,    92,
       4,     3,   152,   153,     4,   155,     8,     3,     3,   102,
      20,    21,     8,     8,     4,   108,   109,   110,   111,   112,
     113,     4,   115,    57,    58,    59,    60,    61,    62,    63,
      64,   181,   402,    67,    68,    69,    70,    71,    72,     4,
      74,    75,    76,     4,    78,     3,     3,     3,   392,   393,
       8,   156,     8,   158,   159,    89,     4,    91,    92,    93,
      94,    95,    96,     3,     8,     3,     3,     8,     8,   103,
       8,     8,   106,   107,     3,     3,   181,     3,     8,     8,
     114,   451,     8,    35,    36,    37,    38,   457,   181,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   469,
       4,     4,   472,     4,     3,   457,     4,     4,     4,   469,
       4,     4,     4,   483,     4,   469,   181,   469,   152,   153,
     472,     4,     4,   493,     4,     4,   498,     4,   498,   469,
       4,   483,   472,     4,   498,     4,     4,   457,   184,     4,
     184,   493,   184,   483,     4,   469,   498,   181,   518,   469,
       4,   520,   472,     4,     4,   182,   182,   493,   183,   182,
     182,   469,   498,   483,   469,   469,   518,   469,   469,   182,
     184,   183,     4,   493,   182,   483,     4,     4,   498,   469,
     469,   483,    34,   469,     4,   184,   469,   531,   532,   533,
     469,   184,   184,   483,   469,     4,   182,   469,   518,     4,
     469,   469,   469,     4,   469,   469,     4,   469,   469,  1065,
       4,     4,   469,   472,     4,     4,   472,     4,    26,    27,
      28,    29,    30,     4,     4,     4,     4,    79,     4,    81,
      82,     4,   182,    85,    86,    87,     4,     4,     4,    91,
      92,     4,     4,     4,     4,   184,     4,     4,     4,    57,
      58,    59,    60,    61,    62,    63,    64,     4,     4,    67,
      68,    69,    70,    71,    72,    73,     4,     4,     4,     4,
      78,    79,     4,     4,     4,     4,   646,     4,   647,   623,
       4,     4,   652,    91,    92,     4,    94,     4,    96,     4,
       4,   182,     4,     4,     4,   103,   184,   184,   106,   184,
     652,   645,     4,     4,     4,     4,   114,    79,    80,    81,
      82,    83,    84,     4,   184,   182,   686,     4,   688,    91,
      92,   182,     4,   182,     4,     4,   184,   184,     4,   181,
       4,     4,   652,   182,   686,     4,   688,    91,    92,     7,
       7,     7,     7,     7,   152,   153,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
       7,     7,   181,   181,   181,     5,   686,   181,   688,   181,
     181,     5,     5,   181,     5,     5,    24,   181,     7,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,     5,     5,     5,     5,   181,   181,   152,   153,
       7,     7,     7,     5,     5,     5,   181,   181,     7,   181,
     181,   181,   181,     5,     7,     6,   181,   181,     7,   147,
       7,     7,   181,     7,     7,     7,   181,   181,   181,   181,
     181,   181,   181,   181,     7,     7,   181,   181,   181,   181,
     181,   181,   181,     7,     4,     4,     4,   181,   181,     4,
       4,     4,     4,     4,     4,   181,   181,     4,     4,   181,
       3,     6,     3,     3,     6,     3,   182,     6,     3,     6,
       6,     3,     6,     3,   181,     4,     4,     4,     4,     4,
       4,     3,   577,     6,   182,     4,     6,     8,     4,     4,
       4,     4,   184,   182,   184,     4,     4,     4,     4,   182,
     184,   182,     4,     4,   182,   182,     6,   182,     3,     8,
     182,   182,   182,     4,     8,     4,     8,     3,     8,   182,
     182,   182,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   902,     4,     4,   905,   908,   181,   908,   184,
       4,   911,   902,   182,   908,     4,   916,     5,   902,   919,
     902,   916,   922,   905,   181,   181,   908,   911,     7,   911,
       4,     4,   902,     4,   916,   935,     4,   919,   938,   905,
     184,   911,   908,   182,   944,   911,   916,     4,   902,   919,
     916,   636,   902,   935,   182,   905,   938,   911,   908,   402,
     646,   911,   944,   181,   902,   451,   916,   902,   902,   919,
     902,   902,   938,   911,   944,   181,   911,   911,   916,   911,
     911,   919,   902,   902,   916,   935,   902,   919,   938,   902,
     457,   911,   911,   902,   944,   911,   916,   902,   911,   919,
     902,   652,   911,   902,   902,   902,   911,   902,   902,   911,
     902,   902,   911,   911,   911,   902,   911,   911,   737,   911,
     911,   924,   911,   875,   911,   911,   901,   896,   501,   914,
     931,   904,   922,   469,   902,  1083,   913,   493,   910,   498,
     905,   907,   946,   472,   944,   921,   908,   708,  1088,   688,
     483,   935,   518,   651,   524,   944,   917,   647,   944,   520,
     919,  1096,  1116,  1136,    -1,   939,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1083,    -1,    -1,    -1,    -1,  1088,    -1,
      -1,    -1,    -1,  1088,    -1,    -1,  1096,    -1,    -1,  1083,
      -1,  1083,    -1,    -1,    -1,    -1,  1088,    -1,    -1,    -1,
      -1,    -1,    -1,  1083,  1096,    -1,    -1,  1083,  1088,    -1,
      -1,    -1,  1088,    -1,    -1,    -1,    -1,    -1,    -1,  1083,
    1096,    -1,    -1,  1083,    -1,    -1,    -1,    -1,  1088,    -1,
      -1,    -1,    -1,    -1,    -1,  1083,  1096,    -1,  1083,  1083,
    1088,  1083,  1083,    -1,    -1,    -1,  1088,    -1,    -1,    -1,
      -1,    -1,    -1,  1083,  1083,    -1,    -1,  1083,  1088,    -1,
    1083,    -1,    -1,    -1,  1083,    -1,    -1,    -1,  1083,    -1,
      -1,  1083,    -1,    -1,  1083,  1083,  1083,    -1,  1083,  1083,
      -1,  1083,  1083,    -1,  1083,    -1,  1083,  1083
  };

  const unsigned short
  Dhcp4Parser::yystos_[] =
  {
       0,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
       0,     5,     7,     9,   181,   182,   183,   184,   201,   202,
     203,   208,     7,   217,     7,   223,     7,   259,     7,   357,
       7,   437,     7,   453,     7,   389,     7,   395,     7,   419,
       7,   333,     7,   510,     7,   556,     7,   547,   209,   204,
     218,   224,   260,   358,   438,   454,   390,   396,   420,   334,
     511,   557,   548,   201,   210,   211,   181,   206,   207,    10,
     154,   164,   165,   166,   181,   216,   219,   220,   221,   539,
     541,   543,   554,    11,    14,    23,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    77,    78,    88,    91,    92,    96,   101,   102,
     107,   117,   120,   127,   128,   131,   132,   152,   153,   155,
     216,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   238,   239,   240,   241,   242,   243,   244,
     247,   249,   251,   253,   255,   270,   272,   278,   280,   318,
     327,   341,   351,   375,   379,   387,   413,   443,   445,   447,
     458,   460,   462,   485,   497,   498,   506,   508,   545,   560,
      15,    16,    19,    22,   216,   257,   258,   261,   263,   266,
     269,   443,   445,    74,    75,    76,    89,    93,    94,    95,
     103,   106,   114,   216,   227,   228,   229,   230,   231,   232,
     233,   234,   239,   240,   241,   242,   243,   244,   247,   249,
     251,   253,   359,   360,   361,   363,   365,   367,   369,   371,
     373,   375,   378,   413,   431,   443,   445,   447,   458,   460,
     462,   482,    90,   216,   371,   373,   413,   439,   440,   441,
     443,   445,   102,   108,   109,   110,   111,   112,   113,   115,
     216,   413,   443,   445,   455,   456,   457,   458,   460,   462,
     464,   468,   470,   472,   474,   476,   478,   480,   387,    34,
      79,    81,    82,    85,    86,    87,   216,   298,   397,   398,
     399,   400,   401,   402,   403,   405,   407,   409,   410,   412,
     443,   445,    80,    83,    84,   216,   298,   401,   407,   421,
     422,   423,   424,   425,   427,   428,   429,   430,   443,   445,
     118,   119,   216,   335,   336,   337,   339,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     152,   153,   216,   443,   445,   512,   513,   514,   515,   517,
     518,   520,   521,   522,   525,   527,   529,   530,   531,   533,
     535,   537,   558,   559,   560,    12,    13,   549,   550,   551,
     553,     6,     3,     4,     8,     3,   222,   555,   540,   542,
     544,     4,     3,     8,   546,   256,   273,     4,     4,     4,
     459,   461,   463,   271,   279,   281,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   237,     4,     4,     4,   245,
     248,   250,   352,   388,   414,   380,   444,   446,   376,   319,
     486,   448,   328,   342,     4,   499,   507,   509,   252,   254,
     561,     3,     8,   262,   264,   267,     4,     3,     8,   364,
     366,   368,   432,   362,   370,     4,   374,   372,   483,     3,
       8,   442,     3,     8,   481,   469,   471,   475,   473,   479,
     477,   465,     8,     3,     8,   404,   299,     4,   408,   406,
     411,     4,     8,     3,   426,     4,     4,     8,     3,   338,
     340,     3,     8,     4,   528,   516,     4,   519,     4,     4,
     523,   526,     4,     4,   532,   534,   536,   538,     3,     8,
       3,     8,   552,     4,     3,     8,   201,   201,   181,     4,
       4,     4,     4,     4,   220,     4,     4,     4,   184,   184,
     184,     4,     4,     4,     4,     4,     4,   182,   182,   182,
     182,   182,   184,   183,   183,   182,     4,   184,   184,   184,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   182,     4,     4,     4,     4,
       4,     4,   226,     4,     4,     4,   184,   258,     4,     4,
       4,     4,     4,     4,   182,     4,     4,     4,   360,     4,
     440,     4,     4,     4,     4,     4,     4,     4,     4,   457,
       4,     4,   182,     4,     4,     4,   184,   399,     4,   184,
     184,   423,     4,     4,   336,   184,     4,     4,   182,     4,
     182,   182,     4,     4,   184,   184,     4,     4,     4,     4,
     513,   559,     4,   182,   550,     4,     7,     7,   201,   201,
     201,     7,     7,     7,   181,   181,   181,     7,     7,     5,
     181,   148,   149,   150,   151,   184,   246,   181,   181,     5,
       5,     5,     5,   203,   205,   181,    97,    98,    99,   100,
     377,     5,     5,     5,     5,     7,     7,   205,     7,   181,
     181,     5,     5,   212,    17,    18,   265,    20,    21,   268,
     181,   181,   181,     5,   181,   181,   212,   181,     7,   181,
     212,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   201,   181,   181,   181,    18,
     146,   524,   147,   246,   181,   181,   181,     5,   201,   225,
     558,   549,   257,    24,   274,   275,   276,    34,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,   216,   286,   287,   288,
     291,   293,   295,   297,   298,   300,   301,   302,   303,   304,
     305,   306,   307,   309,   311,   313,   315,   316,   317,   286,
       7,   282,   283,   284,     7,   353,   354,   355,     7,   391,
     392,   393,     7,   415,   416,   417,     7,   381,   382,   383,
     108,   109,   110,   111,   113,   320,   321,   322,   323,   324,
     325,   326,     7,   487,   488,     7,   449,   450,   451,     7,
     329,   330,   331,   121,   122,   123,   124,   125,   126,   343,
     344,   345,   346,   347,   348,   349,   350,   129,   130,   216,
     443,   445,   500,   501,   502,   504,   512,     7,   562,   563,
     213,     7,   433,   434,   435,   116,   464,   466,   484,   282,
       8,     8,     8,     8,   277,     3,     8,   289,   292,   294,
     296,     4,     4,     4,     4,     4,   308,   310,   312,   314,
       4,     4,     4,     4,     4,     4,     3,     8,     8,   285,
       6,     3,   356,     6,     3,   394,     6,     3,   418,     6,
       3,   384,     6,     3,     3,     6,   489,     3,     6,   452,
       6,     3,   332,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   503,   505,     3,     8,     8,   564,     3,
       6,   181,   214,   215,   436,     6,     3,   467,     8,     6,
       4,   275,     4,     4,     4,     4,   182,   184,   182,   184,
     182,     4,     4,     4,     4,   182,   182,   182,   182,   184,
     182,   287,   286,   284,   359,   355,   397,   393,   421,   417,
     216,   227,   228,   229,   230,   231,   232,   233,   234,   239,
     240,   241,   242,   243,   244,   247,   249,   251,   253,   298,
     351,   369,   371,   373,   375,   385,   386,   413,   443,   445,
     458,   460,   462,   482,   383,   321,   104,   105,   216,   298,
     387,   413,   443,   445,   458,   460,   462,   490,   491,   492,
     493,   494,   496,   488,   455,   451,   335,   331,   182,   182,
     182,   182,   182,   182,   344,     4,     4,   501,   156,   158,
     159,   216,   298,   443,   445,   565,   566,   567,   568,   570,
     563,     6,     3,   439,   435,     4,   181,    35,    36,    37,
      38,   290,   181,   181,   181,   181,   181,   181,   181,     8,
       8,     8,     8,     3,     8,   495,     4,     8,     3,     8,
       8,   181,   181,   571,     4,   569,     3,     8,   181,     8,
     212,   386,     4,   184,   492,     4,   182,     4,   566,   181,
       5,   181,     7,   572,   573,   574,     3,     6,   157,   160,
     161,   162,   163,   575,   576,   577,   579,   580,   581,   582,
     573,   578,     4,     4,     4,   583,     3,     8,     4,   184,
     182,   182,     4,   576,   181,   181
  };

  const unsigned short
  Dhcp4Parser::yyr1_[] =
  {
       0,   185,   187,   186,   188,   186,   189,   186,   190,   186,
     191,   186,   192,   186,   193,   186,   194,   186,   195,   186,
     196,   186,   197,   186,   198,   186,   199,   186,   200,   186,
     201,   201,   201,   201,   201,   201,   201,   202,   204,   203,
     205,   206,   206,   207,   207,   209,   208,   210,   210,   211,
     211,   213,   212,   214,   214,   215,   215,   216,   218,   217,
     219,   219,   220,   220,   220,   220,   220,   220,   222,   221,
     224,   223,   225,   225,   226,   226,   226,   226,   226,   226,
     226,   226,   226,   226,   226,   226,   226,   226,   226,   226,
     226,   226,   226,   226,   226,   226,   226,   226,   226,   226,
     226,   226,   226,   226,   226,   226,   226,   226,   226,   226,
     226,   226,   226,   226,   226,   226,   226,   226,   226,   226,
     226,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   237,   236,   238,   239,   240,   241,   242,   243,   245,
     244,   246,   246,   246,   246,   246,   248,   247,   250,   249,
     252,   251,   254,   253,   256,   255,   257,   257,   258,   258,
     258,   258,   258,   258,   258,   260,   259,   262,   261,   264,
     263,   265,   265,   267,   266,   268,   268,   269,   271,   270,
     273,   272,   274,   274,   275,   277,   276,   279,   278,   281,
     280,   282,   282,   283,   283,   285,   284,   286,   286,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     289,   288,   290,   290,   290,   290,   292,   291,   294,   293,
     296,   295,   297,   299,   298,   300,   301,   302,   303,   304,
     305,   306,   308,   307,   310,   309,   312,   311,   314,   313,
     315,   316,   317,   319,   318,   320,   320,   321,   321,   321,
     321,   321,   322,   323,   324,   325,   326,   328,   327,   329,
     329,   330,   330,   332,   331,   334,   333,   335,   335,   335,
     336,   336,   338,   337,   340,   339,   342,   341,   343,   343,
     344,   344,   344,   344,   344,   344,   345,   346,   347,   348,
     349,   350,   352,   351,   353,   353,   354,   354,   356,   355,
     358,   357,   359,   359,   360,   360,   360,   360,   360,   360,
     360,   360,   360,   360,   360,   360,   360,   360,   360,   360,
     360,   360,   360,   360,   360,   360,   360,   360,   360,   360,
     360,   360,   360,   360,   360,   360,   360,   360,   360,   360,
     360,   362,   361,   364,   363,   366,   365,   368,   367,   370,
     369,   372,   371,   374,   373,   376,   375,   377,   377,   377,
     377,   378,   380,   379,   381,   381,   382,   382,   384,   383,
     385,   385,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   388,   387,   390,   389,   391,   391,
     392,   392,   394,   393,   396,   395,   397,   397,   398,   398,
     399,   399,   399,   399,   399,   399,   399,   399,   399,   399,
     400,   401,   402,   404,   403,   406,   405,   408,   407,   409,
     411,   410,   412,   414,   413,   415,   415,   416,   416,   418,
     417,   420,   419,   421,   421,   422,   422,   423,   423,   423,
     423,   423,   423,   423,   423,   423,   424,   426,   425,   427,
     428,   429,   430,   432,   431,   433,   433,   434,   434,   436,
     435,   438,   437,   439,   439,   440,   440,   440,   440,   440,
     440,   440,   442,   441,   444,   443,   446,   445,   448,   447,
     449,   449,   450,   450,   452,   451,   454,   453,   455,   455,
     456,   456,   457,   457,   457,   457,   457,   457,   457,   457,
     457,   457,   457,   457,   457,   457,   457,   459,   458,   461,
     460,   463,   462,   465,   464,   467,   466,   469,   468,   471,
     470,   473,   472,   475,   474,   477,   476,   479,   478,   481,
     480,   483,   482,   484,   484,   486,   485,   487,   487,   489,
     488,   490,   490,   491,   491,   492,   492,   492,   492,   492,
     492,   492,   492,   492,   492,   492,   493,   495,   494,   496,
     497,   499,   498,   500,   500,   501,   501,   501,   501,   501,
     503,   502,   505,   504,   507,   506,   509,   508,   511,   510,
     512,   512,   513,   513,   513,   513,   513,   513,   513,   513,
     513,   513,   513,   513,   513,   513,   513,   513,   513,   513,
     514,   516,   515,   517,   519,   518,   520,   521,   523,   522,
     524,   524,   526,   525,   528,   527,   529,   530,   532,   531,
     534,   533,   536,   535,   538,   537,   540,   539,   542,   541,
     544,   543,   546,   545,   548,   547,   549,   549,   550,   550,
     552,   551,   553,   555,   554,   557,   556,   558,   558,   559,
     561,   560,   562,   562,   564,   563,   565,   565,   566,   566,
     566,   566,   566,   566,   566,   567,   569,   568,   571,   570,
     572,   572,   574,   573,   575,   575,   576,   576,   576,   576,
     576,   578,   577,   579,   580,   581,   583,   582
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
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     3,     0,     4,     3,     3,     0,     4,
       1,     1,     0,     4,     0,     4,     3,     3,     0,     4,
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
  "\"socket-name\"", "\"dhcp-queue-control\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"tcp\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
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
  "dhcp_ddns", "$@108", "sub_dhcp_ddns", "$@109", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@110", "server_port",
  "sender_ip", "$@111", "sender_port", "max_queue_size", "ncr_protocol",
  "$@112", "ncr_protocol_value", "ncr_format", "$@113",
  "dep_qualifying_suffix", "$@114", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@115",
  "dep_generated_prefix", "$@116", "dep_hostname_char_set", "$@117",
  "dep_hostname_char_replacement", "$@118", "dhcp6_json_object", "$@119",
  "dhcpddns_json_object", "$@120", "control_agent_json_object", "$@121",
  "config_control", "$@122", "sub_config_control", "$@123",
  "config_control_params", "config_control_param", "config_databases",
  "$@124", "config_fetch_wait_time", "logging_object", "$@125",
  "sub_logging", "$@126", "logging_params", "logging_param", "loggers",
  "$@127", "loggers_entries", "logger_entry", "$@128", "logger_params",
  "logger_param", "debuglevel", "severity", "$@129", "output_options_list",
  "$@130", "output_options_list_content", "output_entry", "$@131",
  "output_params_list", "output_params", "output", "$@132", "flush",
  "maxsize", "maxver", "pattern", "$@133", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short
  Dhcp4Parser::yyrline_[] =
  {
       0,   272,   272,   272,   273,   273,   274,   274,   275,   275,
     276,   276,   277,   277,   278,   278,   279,   279,   280,   280,
     281,   281,   282,   282,   283,   283,   284,   284,   285,   285,
     293,   294,   295,   296,   297,   298,   299,   302,   307,   307,
     318,   321,   322,   325,   329,   336,   336,   343,   344,   347,
     351,   358,   358,   365,   366,   369,   373,   384,   394,   394,
     410,   411,   415,   416,   417,   418,   419,   420,   423,   423,
     438,   438,   447,   448,   453,   454,   455,   456,   457,   458,
     459,   460,   461,   462,   463,   464,   465,   466,   467,   468,
     469,   470,   471,   472,   473,   474,   475,   476,   477,   478,
     479,   480,   481,   482,   483,   484,   485,   486,   487,   488,
     489,   490,   491,   492,   493,   494,   495,   496,   497,   498,
     499,   500,   503,   508,   513,   518,   523,   528,   533,   538,
     543,   548,   548,   556,   561,   566,   571,   576,   581,   586,
     586,   594,   597,   600,   603,   606,   612,   612,   620,   620,
     628,   628,   636,   636,   644,   644,   655,   656,   659,   660,
     661,   662,   663,   664,   665,   668,   668,   677,   677,   687,
     687,   694,   695,   698,   698,   705,   707,   711,   717,   717,
     729,   729,   739,   740,   742,   744,   744,   762,   762,   774,
     774,   784,   785,   788,   789,   792,   792,   802,   803,   806,
     807,   808,   809,   810,   811,   812,   813,   814,   815,   816,
     817,   818,   819,   820,   821,   822,   823,   824,   825,   826,
     829,   829,   836,   837,   838,   839,   842,   842,   850,   850,
     858,   858,   866,   871,   871,   879,   884,   889,   894,   899,
     904,   909,   914,   914,   922,   922,   930,   930,   938,   938,
     946,   951,   956,   962,   962,   972,   973,   976,   977,   978,
     979,   980,   983,   988,   993,   998,  1003,  1008,  1008,  1018,
    1019,  1022,  1023,  1026,  1026,  1036,  1036,  1046,  1047,  1048,
    1051,  1052,  1055,  1055,  1063,  1063,  1071,  1071,  1082,  1083,
    1086,  1087,  1088,  1089,  1090,  1091,  1094,  1099,  1104,  1109,
    1114,  1119,  1127,  1127,  1140,  1141,  1144,  1145,  1152,  1152,
    1178,  1178,  1189,  1190,  1194,  1195,  1196,  1197,  1198,  1199,
    1200,  1201,  1202,  1203,  1204,  1205,  1206,  1207,  1208,  1209,
    1210,  1211,  1212,  1213,  1214,  1215,  1216,  1217,  1218,  1219,
    1220,  1221,  1222,  1223,  1224,  1225,  1226,  1227,  1228,  1229,
    1230,  1233,  1233,  1241,  1241,  1249,  1249,  1257,  1257,  1265,
    1265,  1273,  1273,  1281,  1281,  1291,  1291,  1298,  1299,  1300,
    1301,  1304,  1311,  1311,  1322,  1323,  1327,  1328,  1331,  1331,
    1339,  1340,  1343,  1344,  1345,  1346,  1347,  1348,  1349,  1350,
    1351,  1352,  1353,  1354,  1355,  1356,  1357,  1358,  1359,  1360,
    1361,  1362,  1363,  1364,  1365,  1366,  1367,  1368,  1369,  1370,
    1371,  1372,  1373,  1374,  1381,  1381,  1394,  1394,  1403,  1404,
    1407,  1408,  1413,  1413,  1428,  1428,  1442,  1443,  1446,  1447,
    1450,  1451,  1452,  1453,  1454,  1455,  1456,  1457,  1458,  1459,
    1462,  1464,  1469,  1471,  1471,  1479,  1479,  1487,  1487,  1495,
    1497,  1497,  1505,  1514,  1514,  1526,  1527,  1532,  1533,  1538,
    1538,  1550,  1550,  1562,  1563,  1568,  1569,  1574,  1575,  1576,
    1577,  1578,  1579,  1580,  1581,  1582,  1585,  1587,  1587,  1595,
    1597,  1599,  1604,  1612,  1612,  1624,  1625,  1628,  1629,  1632,
    1632,  1642,  1642,  1652,  1653,  1656,  1657,  1658,  1659,  1660,
    1661,  1662,  1665,  1665,  1673,  1673,  1698,  1698,  1728,  1728,
    1738,  1739,  1742,  1743,  1746,  1746,  1755,  1755,  1764,  1765,
    1768,  1769,  1773,  1774,  1775,  1776,  1777,  1778,  1779,  1780,
    1781,  1782,  1783,  1784,  1785,  1786,  1787,  1790,  1790,  1798,
    1798,  1806,  1806,  1814,  1814,  1822,  1822,  1832,  1832,  1840,
    1840,  1848,  1848,  1856,  1856,  1864,  1864,  1872,  1872,  1880,
    1880,  1893,  1893,  1903,  1904,  1910,  1910,  1920,  1921,  1924,
    1924,  1934,  1935,  1938,  1939,  1942,  1943,  1944,  1945,  1946,
    1947,  1948,  1949,  1950,  1951,  1952,  1955,  1957,  1957,  1965,
    1974,  1981,  1981,  1991,  1992,  1995,  1996,  1997,  1998,  1999,
    2002,  2002,  2010,  2010,  2021,  2021,  2059,  2059,  2071,  2071,
    2081,  2082,  2085,  2086,  2087,  2088,  2089,  2090,  2091,  2092,
    2093,  2094,  2095,  2096,  2097,  2098,  2099,  2100,  2101,  2102,
    2105,  2110,  2110,  2118,  2123,  2123,  2131,  2136,  2141,  2141,
    2149,  2150,  2153,  2153,  2162,  2162,  2171,  2177,  2183,  2183,
    2191,  2191,  2200,  2200,  2209,  2209,  2220,  2220,  2227,  2227,
    2234,  2234,  2241,  2241,  2252,  2252,  2262,  2263,  2267,  2268,
    2271,  2271,  2281,  2291,  2291,  2301,  2301,  2312,  2313,  2317,
    2321,  2321,  2333,  2334,  2338,  2338,  2346,  2347,  2350,  2351,
    2352,  2353,  2354,  2355,  2356,  2359,  2364,  2364,  2372,  2372,
    2382,  2383,  2386,  2386,  2394,  2395,  2398,  2399,  2400,  2401,
    2402,  2405,  2405,  2413,  2418,  2423,  2428,  2428
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
#line 5288 "dhcp4_parser.cc"

#line 2437 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
