// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

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
#line 34 "dhcp6_parser.yy"

#include <dhcp6/parser_context.h>

#line 51 "dhcp6_parser.cc"


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

#line 14 "dhcp6_parser.yy"
namespace isc { namespace dhcp {
#line 143 "dhcp6_parser.cc"


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
#if PARSER6_DEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
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
      return yystos_[+state];
  }

  Dhcp6Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Dhcp6Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 224: // value
      case 228: // map_value
      case 269: // ddns_replace_client_name_value
      case 309: // db_type
      case 415: // hr_mode
      case 551: // duid_type
      case 594: // ncr_protocol_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 207: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 206: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 205: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 204: // "constant string"
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
      case 224: // value
      case 228: // map_value
      case 269: // ddns_replace_client_name_value
      case 309: // db_type
      case 415: // hr_mode
      case 551: // duid_type
      case 594: // ncr_protocol_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 207: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 206: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 205: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 204: // "constant string"
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
  Dhcp6Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 224: // value
      case 228: // map_value
      case 269: // ddns_replace_client_name_value
      case 309: // db_type
      case 415: // hr_mode
      case 551: // duid_type
      case 594: // ncr_protocol_value
        value.copy< ElementPtr > (that.value);
        break;

      case 207: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 206: // "floating point"
        value.copy< double > (that.value);
        break;

      case 205: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 204: // "constant string"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  Dhcp6Parser::stack_symbol_type&
  Dhcp6Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 224: // value
      case 228: // map_value
      case 269: // ddns_replace_client_name_value
      case 309: // db_type
      case 415: // hr_mode
      case 551: // duid_type
      case 594: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 207: // "boolean"
        value.move< bool > (that.value);
        break;

      case 206: // "floating point"
        value.move< double > (that.value);
        break;

      case 205: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 204: // "constant string"
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
      case 204: // "constant string"
#line 285 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 443 "dhcp6_parser.cc"
        break;

      case 205: // "integer"
#line 285 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 449 "dhcp6_parser.cc"
        break;

      case 206: // "floating point"
#line 285 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 455 "dhcp6_parser.cc"
        break;

      case 207: // "boolean"
#line 285 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 461 "dhcp6_parser.cc"
        break;

      case 224: // value
#line 285 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 467 "dhcp6_parser.cc"
        break;

      case 228: // map_value
#line 285 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 473 "dhcp6_parser.cc"
        break;

      case 269: // ddns_replace_client_name_value
#line 285 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 479 "dhcp6_parser.cc"
        break;

      case 309: // db_type
#line 285 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 485 "dhcp6_parser.cc"
        break;

      case 415: // hr_mode
#line 285 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 491 "dhcp6_parser.cc"
        break;

      case 551: // duid_type
#line 285 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 497 "dhcp6_parser.cc"
        break;

      case 594: // ncr_protocol_value
#line 285 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 503 "dhcp6_parser.cc"
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
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
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
      {
        goto yydefault;
      }

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
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
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
      case 224: // value
      case 228: // map_value
      case 269: // ddns_replace_client_name_value
      case 309: // db_type
      case 415: // hr_mode
      case 551: // duid_type
      case 594: // ncr_protocol_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 207: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 206: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 205: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 204: // "constant string"
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
#line 294 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 770 "dhcp6_parser.cc"
    break;

  case 4:
#line 295 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 776 "dhcp6_parser.cc"
    break;

  case 6:
#line 296 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 782 "dhcp6_parser.cc"
    break;

  case 8:
#line 297 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 788 "dhcp6_parser.cc"
    break;

  case 10:
#line 298 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 794 "dhcp6_parser.cc"
    break;

  case 12:
#line 299 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 800 "dhcp6_parser.cc"
    break;

  case 14:
#line 300 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 806 "dhcp6_parser.cc"
    break;

  case 16:
#line 301 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 812 "dhcp6_parser.cc"
    break;

  case 18:
#line 302 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 818 "dhcp6_parser.cc"
    break;

  case 20:
#line 303 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 824 "dhcp6_parser.cc"
    break;

  case 22:
#line 304 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 830 "dhcp6_parser.cc"
    break;

  case 24:
#line 305 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 836 "dhcp6_parser.cc"
    break;

  case 26:
#line 306 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 842 "dhcp6_parser.cc"
    break;

  case 28:
#line 307 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 848 "dhcp6_parser.cc"
    break;

  case 30:
#line 315 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 854 "dhcp6_parser.cc"
    break;

  case 31:
#line 316 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 860 "dhcp6_parser.cc"
    break;

  case 32:
#line 317 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 866 "dhcp6_parser.cc"
    break;

  case 33:
#line 318 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 872 "dhcp6_parser.cc"
    break;

  case 34:
#line 319 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 878 "dhcp6_parser.cc"
    break;

  case 35:
#line 320 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 884 "dhcp6_parser.cc"
    break;

  case 36:
#line 321 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 890 "dhcp6_parser.cc"
    break;

  case 37:
#line 324 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 899 "dhcp6_parser.cc"
    break;

  case 38:
#line 329 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 910 "dhcp6_parser.cc"
    break;

  case 39:
#line 334 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 920 "dhcp6_parser.cc"
    break;

  case 40:
#line 340 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 926 "dhcp6_parser.cc"
    break;

  case 43:
#line 347 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 936 "dhcp6_parser.cc"
    break;

  case 44:
#line 352 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 947 "dhcp6_parser.cc"
    break;

  case 45:
#line 360 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 956 "dhcp6_parser.cc"
    break;

  case 46:
#line 363 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 964 "dhcp6_parser.cc"
    break;

  case 49:
#line 371 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 973 "dhcp6_parser.cc"
    break;

  case 50:
#line 375 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 982 "dhcp6_parser.cc"
    break;

  case 51:
#line 382 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 990 "dhcp6_parser.cc"
    break;

  case 52:
#line 384 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 999 "dhcp6_parser.cc"
    break;

  case 55:
#line 393 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1008 "dhcp6_parser.cc"
    break;

  case 56:
#line 397 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1017 "dhcp6_parser.cc"
    break;

  case 57:
#line 408 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1028 "dhcp6_parser.cc"
    break;

  case 58:
#line 417 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1039 "dhcp6_parser.cc"
    break;

  case 59:
#line 422 "dhcp6_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1052 "dhcp6_parser.cc"
    break;

  case 60:
#line 432 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    // Prevent against duplicate.
    ctx.unique("Dhcp6", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 1067 "dhcp6_parser.cc"
    break;

  case 61:
#line 441 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1077 "dhcp6_parser.cc"
    break;

  case 62:
#line 449 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1087 "dhcp6_parser.cc"
    break;

  case 63:
#line 453 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1096 "dhcp6_parser.cc"
    break;

  case 127:
#line 527 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1105 "dhcp6_parser.cc"
    break;

  case 128:
#line 530 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1115 "dhcp6_parser.cc"
    break;

  case 129:
#line 536 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1125 "dhcp6_parser.cc"
    break;

  case 130:
#line 542 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1135 "dhcp6_parser.cc"
    break;

  case 131:
#line 548 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1145 "dhcp6_parser.cc"
    break;

  case 132:
#line 554 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1155 "dhcp6_parser.cc"
    break;

  case 133:
#line 560 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1165 "dhcp6_parser.cc"
    break;

  case 134:
#line 566 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1175 "dhcp6_parser.cc"
    break;

  case 135:
#line 572 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1185 "dhcp6_parser.cc"
    break;

  case 136:
#line 578 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1195 "dhcp6_parser.cc"
    break;

  case 137:
#line 584 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1205 "dhcp6_parser.cc"
    break;

  case 138:
#line 590 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1215 "dhcp6_parser.cc"
    break;

  case 139:
#line 596 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1225 "dhcp6_parser.cc"
    break;

  case 140:
#line 602 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1235 "dhcp6_parser.cc"
    break;

  case 141:
#line 608 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1245 "dhcp6_parser.cc"
    break;

  case 142:
#line 614 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1255 "dhcp6_parser.cc"
    break;

  case 143:
#line 620 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1265 "dhcp6_parser.cc"
    break;

  case 144:
#line 626 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1275 "dhcp6_parser.cc"
    break;

  case 145:
#line 632 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1285 "dhcp6_parser.cc"
    break;

  case 146:
#line 638 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1294 "dhcp6_parser.cc"
    break;

  case 147:
#line 641 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1303 "dhcp6_parser.cc"
    break;

  case 148:
#line 647 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1311 "dhcp6_parser.cc"
    break;

  case 149:
#line 650 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1319 "dhcp6_parser.cc"
    break;

  case 150:
#line 653 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1327 "dhcp6_parser.cc"
    break;

  case 151:
#line 656 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1335 "dhcp6_parser.cc"
    break;

  case 152:
#line 659 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1344 "dhcp6_parser.cc"
    break;

  case 153:
#line 665 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1353 "dhcp6_parser.cc"
    break;

  case 154:
#line 668 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1363 "dhcp6_parser.cc"
    break;

  case 155:
#line 674 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1372 "dhcp6_parser.cc"
    break;

  case 156:
#line 677 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1382 "dhcp6_parser.cc"
    break;

  case 157:
#line 683 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1392 "dhcp6_parser.cc"
    break;

  case 158:
#line 689 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1402 "dhcp6_parser.cc"
    break;

  case 159:
#line 695 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1411 "dhcp6_parser.cc"
    break;

  case 160:
#line 698 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1421 "dhcp6_parser.cc"
    break;

  case 161:
#line 704 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1430 "dhcp6_parser.cc"
    break;

  case 162:
#line 707 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1440 "dhcp6_parser.cc"
    break;

  case 163:
#line 713 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1450 "dhcp6_parser.cc"
    break;

  case 164:
#line 719 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 165:
#line 725 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1470 "dhcp6_parser.cc"
    break;

  case 166:
#line 731 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1479 "dhcp6_parser.cc"
    break;

  case 167:
#line 734 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1489 "dhcp6_parser.cc"
    break;

  case 168:
#line 740 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1499 "dhcp6_parser.cc"
    break;

  case 169:
#line 746 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1511 "dhcp6_parser.cc"
    break;

  case 170:
#line 752 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1521 "dhcp6_parser.cc"
    break;

  case 171:
#line 758 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1531 "dhcp6_parser.cc"
    break;

  case 172:
#line 762 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1540 "dhcp6_parser.cc"
    break;

  case 180:
#line 778 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1552 "dhcp6_parser.cc"
    break;

  case 181:
#line 784 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1561 "dhcp6_parser.cc"
    break;

  case 182:
#line 789 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1571 "dhcp6_parser.cc"
    break;

  case 183:
#line 795 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1583 "dhcp6_parser.cc"
    break;

  case 184:
#line 801 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1594 "dhcp6_parser.cc"
    break;

  case 185:
#line 808 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1606 "dhcp6_parser.cc"
    break;

  case 186:
#line 814 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1617 "dhcp6_parser.cc"
    break;

  case 187:
#line 821 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1629 "dhcp6_parser.cc"
    break;

  case 188:
#line 827 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1638 "dhcp6_parser.cc"
    break;

  case 193:
#line 840 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1648 "dhcp6_parser.cc"
    break;

  case 194:
#line 844 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1658 "dhcp6_parser.cc"
    break;

  case 220:
#line 879 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1667 "dhcp6_parser.cc"
    break;

  case 221:
#line 882 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1676 "dhcp6_parser.cc"
    break;

  case 222:
#line 887 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1682 "dhcp6_parser.cc"
    break;

  case 223:
#line 888 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1688 "dhcp6_parser.cc"
    break;

  case 224:
#line 889 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1694 "dhcp6_parser.cc"
    break;

  case 225:
#line 890 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1700 "dhcp6_parser.cc"
    break;

  case 226:
#line 893 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1709 "dhcp6_parser.cc"
    break;

  case 227:
#line 896 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1719 "dhcp6_parser.cc"
    break;

  case 228:
#line 902 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1728 "dhcp6_parser.cc"
    break;

  case 229:
#line 905 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1738 "dhcp6_parser.cc"
    break;

  case 230:
#line 911 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1747 "dhcp6_parser.cc"
    break;

  case 231:
#line 914 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1757 "dhcp6_parser.cc"
    break;

  case 232:
#line 920 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1767 "dhcp6_parser.cc"
    break;

  case 233:
#line 926 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1776 "dhcp6_parser.cc"
    break;

  case 234:
#line 929 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1786 "dhcp6_parser.cc"
    break;

  case 235:
#line 935 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1796 "dhcp6_parser.cc"
    break;

  case 236:
#line 941 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1806 "dhcp6_parser.cc"
    break;

  case 237:
#line 947 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1816 "dhcp6_parser.cc"
    break;

  case 238:
#line 953 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1826 "dhcp6_parser.cc"
    break;

  case 239:
#line 959 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1836 "dhcp6_parser.cc"
    break;

  case 240:
#line 965 "dhcp6_parser.yy"
                                                               {
    ctx.unique("disable-dhcp-on-db-loss", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("disable-dhcp-on-db-loss", n);
}
#line 1846 "dhcp6_parser.cc"
    break;

  case 241:
#line 971 "dhcp6_parser.yy"
                                                                     {
    ctx.unique("enable-connection-recovery", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-connection-recovery", n);
}
#line 1856 "dhcp6_parser.cc"
    break;

  case 242:
#line 977 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1866 "dhcp6_parser.cc"
    break;

  case 243:
#line 983 "dhcp6_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1876 "dhcp6_parser.cc"
    break;

  case 244:
#line 989 "dhcp6_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1886 "dhcp6_parser.cc"
    break;

  case 245:
#line 995 "dhcp6_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1896 "dhcp6_parser.cc"
    break;

  case 246:
#line 1001 "dhcp6_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1905 "dhcp6_parser.cc"
    break;

  case 247:
#line 1004 "dhcp6_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1915 "dhcp6_parser.cc"
    break;

  case 248:
#line 1010 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1925 "dhcp6_parser.cc"
    break;

  case 249:
#line 1016 "dhcp6_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1934 "dhcp6_parser.cc"
    break;

  case 250:
#line 1019 "dhcp6_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1944 "dhcp6_parser.cc"
    break;

  case 251:
#line 1025 "dhcp6_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1953 "dhcp6_parser.cc"
    break;

  case 252:
#line 1028 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1963 "dhcp6_parser.cc"
    break;

  case 253:
#line 1034 "dhcp6_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1972 "dhcp6_parser.cc"
    break;

  case 254:
#line 1037 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1982 "dhcp6_parser.cc"
    break;

  case 255:
#line 1043 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1994 "dhcp6_parser.cc"
    break;

  case 256:
#line 1049 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2003 "dhcp6_parser.cc"
    break;

  case 260:
#line 1059 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2012 "dhcp6_parser.cc"
    break;

  case 261:
#line 1062 "dhcp6_parser.yy"
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
#line 2032 "dhcp6_parser.cc"
    break;

  case 262:
#line 1078 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2044 "dhcp6_parser.cc"
    break;

  case 263:
#line 1084 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2053 "dhcp6_parser.cc"
    break;

  case 268:
#line 1097 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2062 "dhcp6_parser.cc"
    break;

  case 269:
#line 1102 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2071 "dhcp6_parser.cc"
    break;

  case 270:
#line 1107 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2083 "dhcp6_parser.cc"
    break;

  case 271:
#line 1113 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2092 "dhcp6_parser.cc"
    break;

  case 277:
#line 1127 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2101 "dhcp6_parser.cc"
    break;

  case 278:
#line 1132 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2110 "dhcp6_parser.cc"
    break;

  case 279:
#line 1139 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2122 "dhcp6_parser.cc"
    break;

  case 280:
#line 1145 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2131 "dhcp6_parser.cc"
    break;

  case 281:
#line 1152 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2143 "dhcp6_parser.cc"
    break;

  case 282:
#line 1158 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2154 "dhcp6_parser.cc"
    break;

  case 291:
#line 1177 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2164 "dhcp6_parser.cc"
    break;

  case 292:
#line 1183 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2174 "dhcp6_parser.cc"
    break;

  case 293:
#line 1189 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2184 "dhcp6_parser.cc"
    break;

  case 294:
#line 1195 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2196 "dhcp6_parser.cc"
    break;

  case 295:
#line 1201 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2205 "dhcp6_parser.cc"
    break;

  case 300:
#line 1214 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2215 "dhcp6_parser.cc"
    break;

  case 301:
#line 1218 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2225 "dhcp6_parser.cc"
    break;

  case 302:
#line 1224 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2235 "dhcp6_parser.cc"
    break;

  case 303:
#line 1228 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2245 "dhcp6_parser.cc"
    break;

  case 309:
#line 1243 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2254 "dhcp6_parser.cc"
    break;

  case 310:
#line 1246 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2264 "dhcp6_parser.cc"
    break;

  case 311:
#line 1252 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2273 "dhcp6_parser.cc"
    break;

  case 312:
#line 1255 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2282 "dhcp6_parser.cc"
    break;

  case 313:
#line 1261 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2294 "dhcp6_parser.cc"
    break;

  case 314:
#line 1267 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2304 "dhcp6_parser.cc"
    break;

  case 323:
#line 1285 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2314 "dhcp6_parser.cc"
    break;

  case 324:
#line 1291 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2324 "dhcp6_parser.cc"
    break;

  case 325:
#line 1297 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2334 "dhcp6_parser.cc"
    break;

  case 326:
#line 1303 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2344 "dhcp6_parser.cc"
    break;

  case 327:
#line 1309 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2354 "dhcp6_parser.cc"
    break;

  case 328:
#line 1315 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2364 "dhcp6_parser.cc"
    break;

  case 329:
#line 1324 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2376 "dhcp6_parser.cc"
    break;

  case 330:
#line 1330 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2385 "dhcp6_parser.cc"
    break;

  case 335:
#line 1350 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2395 "dhcp6_parser.cc"
    break;

  case 336:
#line 1354 "dhcp6_parser.yy"
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
#line 2421 "dhcp6_parser.cc"
    break;

  case 337:
#line 1376 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2431 "dhcp6_parser.cc"
    break;

  case 338:
#line 1380 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2441 "dhcp6_parser.cc"
    break;

  case 384:
#line 1437 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2450 "dhcp6_parser.cc"
    break;

  case 385:
#line 1440 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2460 "dhcp6_parser.cc"
    break;

  case 386:
#line 1446 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2469 "dhcp6_parser.cc"
    break;

  case 387:
#line 1449 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2479 "dhcp6_parser.cc"
    break;

  case 388:
#line 1455 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2488 "dhcp6_parser.cc"
    break;

  case 389:
#line 1458 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2498 "dhcp6_parser.cc"
    break;

  case 390:
#line 1464 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2507 "dhcp6_parser.cc"
    break;

  case 391:
#line 1467 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2517 "dhcp6_parser.cc"
    break;

  case 392:
#line 1473 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2529 "dhcp6_parser.cc"
    break;

  case 393:
#line 1479 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2538 "dhcp6_parser.cc"
    break;

  case 394:
#line 1484 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2548 "dhcp6_parser.cc"
    break;

  case 395:
#line 1490 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2558 "dhcp6_parser.cc"
    break;

  case 396:
#line 1496 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2568 "dhcp6_parser.cc"
    break;

  case 397:
#line 1502 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2577 "dhcp6_parser.cc"
    break;

  case 398:
#line 1505 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2586 "dhcp6_parser.cc"
    break;

  case 399:
#line 1510 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2592 "dhcp6_parser.cc"
    break;

  case 400:
#line 1511 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2598 "dhcp6_parser.cc"
    break;

  case 401:
#line 1512 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2604 "dhcp6_parser.cc"
    break;

  case 402:
#line 1513 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2610 "dhcp6_parser.cc"
    break;

  case 403:
#line 1516 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2620 "dhcp6_parser.cc"
    break;

  case 404:
#line 1522 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2630 "dhcp6_parser.cc"
    break;

  case 405:
#line 1530 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2642 "dhcp6_parser.cc"
    break;

  case 406:
#line 1536 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2651 "dhcp6_parser.cc"
    break;

  case 411:
#line 1551 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2661 "dhcp6_parser.cc"
    break;

  case 412:
#line 1555 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2669 "dhcp6_parser.cc"
    break;

  case 455:
#line 1609 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2681 "dhcp6_parser.cc"
    break;

  case 456:
#line 1615 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2690 "dhcp6_parser.cc"
    break;

  case 457:
#line 1623 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2699 "dhcp6_parser.cc"
    break;

  case 458:
#line 1626 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2707 "dhcp6_parser.cc"
    break;

  case 463:
#line 1642 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2717 "dhcp6_parser.cc"
    break;

  case 464:
#line 1646 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2729 "dhcp6_parser.cc"
    break;

  case 465:
#line 1657 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2739 "dhcp6_parser.cc"
    break;

  case 466:
#line 1661 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2751 "dhcp6_parser.cc"
    break;

  case 482:
#line 1693 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2761 "dhcp6_parser.cc"
    break;

  case 484:
#line 1701 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2770 "dhcp6_parser.cc"
    break;

  case 485:
#line 1704 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2780 "dhcp6_parser.cc"
    break;

  case 486:
#line 1710 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2789 "dhcp6_parser.cc"
    break;

  case 487:
#line 1713 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2799 "dhcp6_parser.cc"
    break;

  case 488:
#line 1719 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2808 "dhcp6_parser.cc"
    break;

  case 489:
#line 1722 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2818 "dhcp6_parser.cc"
    break;

  case 491:
#line 1730 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2827 "dhcp6_parser.cc"
    break;

  case 492:
#line 1733 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2837 "dhcp6_parser.cc"
    break;

  case 493:
#line 1739 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2847 "dhcp6_parser.cc"
    break;

  case 494:
#line 1749 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2859 "dhcp6_parser.cc"
    break;

  case 495:
#line 1755 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2868 "dhcp6_parser.cc"
    break;

  case 500:
#line 1774 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2878 "dhcp6_parser.cc"
    break;

  case 501:
#line 1778 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2887 "dhcp6_parser.cc"
    break;

  case 502:
#line 1786 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2897 "dhcp6_parser.cc"
    break;

  case 503:
#line 1790 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2906 "dhcp6_parser.cc"
    break;

  case 518:
#line 1823 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2915 "dhcp6_parser.cc"
    break;

  case 519:
#line 1826 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2925 "dhcp6_parser.cc"
    break;

  case 522:
#line 1836 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2935 "dhcp6_parser.cc"
    break;

  case 523:
#line 1842 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2945 "dhcp6_parser.cc"
    break;

  case 524:
#line 1851 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2957 "dhcp6_parser.cc"
    break;

  case 525:
#line 1857 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2966 "dhcp6_parser.cc"
    break;

  case 530:
#line 1872 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2976 "dhcp6_parser.cc"
    break;

  case 531:
#line 1876 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2986 "dhcp6_parser.cc"
    break;

  case 532:
#line 1882 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2996 "dhcp6_parser.cc"
    break;

  case 533:
#line 1886 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3006 "dhcp6_parser.cc"
    break;

  case 543:
#line 1905 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3015 "dhcp6_parser.cc"
    break;

  case 544:
#line 1908 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3025 "dhcp6_parser.cc"
    break;

  case 545:
#line 1914 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3033 "dhcp6_parser.cc"
    break;

  case 546:
#line 1916 "dhcp6_parser.yy"
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
#line 3060 "dhcp6_parser.cc"
    break;

  case 547:
#line 1939 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3068 "dhcp6_parser.cc"
    break;

  case 548:
#line 1941 "dhcp6_parser.yy"
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
#line 3097 "dhcp6_parser.cc"
    break;

  case 549:
#line 1969 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3109 "dhcp6_parser.cc"
    break;

  case 550:
#line 1975 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3118 "dhcp6_parser.cc"
    break;

  case 555:
#line 1990 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3128 "dhcp6_parser.cc"
    break;

  case 556:
#line 1994 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3140 "dhcp6_parser.cc"
    break;

  case 557:
#line 2002 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3150 "dhcp6_parser.cc"
    break;

  case 558:
#line 2006 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3162 "dhcp6_parser.cc"
    break;

  case 572:
#line 2031 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3171 "dhcp6_parser.cc"
    break;

  case 573:
#line 2034 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3181 "dhcp6_parser.cc"
    break;

  case 574:
#line 2040 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3191 "dhcp6_parser.cc"
    break;

  case 575:
#line 2046 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3200 "dhcp6_parser.cc"
    break;

  case 576:
#line 2049 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3210 "dhcp6_parser.cc"
    break;

  case 577:
#line 2055 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3220 "dhcp6_parser.cc"
    break;

  case 578:
#line 2061 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3230 "dhcp6_parser.cc"
    break;

  case 579:
#line 2070 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3242 "dhcp6_parser.cc"
    break;

  case 580:
#line 2076 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3251 "dhcp6_parser.cc"
    break;

  case 585:
#line 2089 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3261 "dhcp6_parser.cc"
    break;

  case 586:
#line 2093 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3270 "dhcp6_parser.cc"
    break;

  case 587:
#line 2098 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3280 "dhcp6_parser.cc"
    break;

  case 588:
#line 2102 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3289 "dhcp6_parser.cc"
    break;

  case 604:
#line 2129 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3301 "dhcp6_parser.cc"
    break;

  case 605:
#line 2135 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3310 "dhcp6_parser.cc"
    break;

  case 606:
#line 2140 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3322 "dhcp6_parser.cc"
    break;

  case 607:
#line 2146 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3331 "dhcp6_parser.cc"
    break;

  case 608:
#line 2151 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3340 "dhcp6_parser.cc"
    break;

  case 609:
#line 2154 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3350 "dhcp6_parser.cc"
    break;

  case 610:
#line 2160 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3359 "dhcp6_parser.cc"
    break;

  case 611:
#line 2163 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3369 "dhcp6_parser.cc"
    break;

  case 612:
#line 2169 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3378 "dhcp6_parser.cc"
    break;

  case 613:
#line 2172 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3388 "dhcp6_parser.cc"
    break;

  case 614:
#line 2178 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3397 "dhcp6_parser.cc"
    break;

  case 615:
#line 2181 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3407 "dhcp6_parser.cc"
    break;

  case 616:
#line 2187 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3419 "dhcp6_parser.cc"
    break;

  case 617:
#line 2193 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3428 "dhcp6_parser.cc"
    break;

  case 618:
#line 2201 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3440 "dhcp6_parser.cc"
    break;

  case 619:
#line 2207 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3449 "dhcp6_parser.cc"
    break;

  case 622:
#line 2216 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3458 "dhcp6_parser.cc"
    break;

  case 623:
#line 2219 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3468 "dhcp6_parser.cc"
    break;

  case 624:
#line 2228 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3480 "dhcp6_parser.cc"
    break;

  case 625:
#line 2234 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3489 "dhcp6_parser.cc"
    break;

  case 628:
#line 2243 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3499 "dhcp6_parser.cc"
    break;

  case 629:
#line 2247 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3509 "dhcp6_parser.cc"
    break;

  case 642:
#line 2272 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3518 "dhcp6_parser.cc"
    break;

  case 643:
#line 2275 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3528 "dhcp6_parser.cc"
    break;

  case 644:
#line 2281 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3538 "dhcp6_parser.cc"
    break;

  case 645:
#line 2290 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3550 "dhcp6_parser.cc"
    break;

  case 646:
#line 2296 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3561 "dhcp6_parser.cc"
    break;

  case 658:
#line 2318 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3570 "dhcp6_parser.cc"
    break;

  case 659:
#line 2321 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3579 "dhcp6_parser.cc"
    break;

  case 660:
#line 2326 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3585 "dhcp6_parser.cc"
    break;

  case 661:
#line 2327 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3591 "dhcp6_parser.cc"
    break;

  case 662:
#line 2328 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3597 "dhcp6_parser.cc"
    break;

  case 663:
#line 2331 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3607 "dhcp6_parser.cc"
    break;

  case 664:
#line 2337 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3616 "dhcp6_parser.cc"
    break;

  case 665:
#line 2340 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3626 "dhcp6_parser.cc"
    break;

  case 666:
#line 2346 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3636 "dhcp6_parser.cc"
    break;

  case 667:
#line 2352 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3646 "dhcp6_parser.cc"
    break;

  case 668:
#line 2360 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3656 "dhcp6_parser.cc"
    break;

  case 669:
#line 2368 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3668 "dhcp6_parser.cc"
    break;

  case 670:
#line 2374 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3677 "dhcp6_parser.cc"
    break;

  case 678:
#line 2390 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3686 "dhcp6_parser.cc"
    break;

  case 679:
#line 2393 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3696 "dhcp6_parser.cc"
    break;

  case 680:
#line 2399 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3705 "dhcp6_parser.cc"
    break;

  case 681:
#line 2402 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3715 "dhcp6_parser.cc"
    break;

  case 682:
#line 2411 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3727 "dhcp6_parser.cc"
    break;

  case 683:
#line 2417 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3738 "dhcp6_parser.cc"
    break;

  case 692:
#line 2436 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3748 "dhcp6_parser.cc"
    break;

  case 693:
#line 2442 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3757 "dhcp6_parser.cc"
    break;

  case 694:
#line 2445 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3767 "dhcp6_parser.cc"
    break;

  case 695:
#line 2451 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3777 "dhcp6_parser.cc"
    break;

  case 696:
#line 2457 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3786 "dhcp6_parser.cc"
    break;

  case 697:
#line 2460 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3795 "dhcp6_parser.cc"
    break;

  case 698:
#line 2467 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3807 "dhcp6_parser.cc"
    break;

  case 699:
#line 2473 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3818 "dhcp6_parser.cc"
    break;

  case 700:
#line 2480 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3828 "dhcp6_parser.cc"
    break;

  case 701:
#line 2484 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3838 "dhcp6_parser.cc"
    break;

  case 722:
#line 2514 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3848 "dhcp6_parser.cc"
    break;

  case 723:
#line 2521 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3857 "dhcp6_parser.cc"
    break;

  case 724:
#line 2524 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3867 "dhcp6_parser.cc"
    break;

  case 725:
#line 2530 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3876 "dhcp6_parser.cc"
    break;

  case 726:
#line 2533 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3886 "dhcp6_parser.cc"
    break;

  case 727:
#line 2539 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3896 "dhcp6_parser.cc"
    break;

  case 728:
#line 2545 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3905 "dhcp6_parser.cc"
    break;

  case 729:
#line 2548 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3915 "dhcp6_parser.cc"
    break;

  case 730:
#line 2554 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3925 "dhcp6_parser.cc"
    break;

  case 731:
#line 2560 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3935 "dhcp6_parser.cc"
    break;

  case 732:
#line 2566 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3944 "dhcp6_parser.cc"
    break;

  case 733:
#line 2569 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3953 "dhcp6_parser.cc"
    break;

  case 734:
#line 2575 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3959 "dhcp6_parser.cc"
    break;

  case 735:
#line 2576 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3965 "dhcp6_parser.cc"
    break;

  case 736:
#line 2579 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3974 "dhcp6_parser.cc"
    break;

  case 737:
#line 2582 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3984 "dhcp6_parser.cc"
    break;

  case 738:
#line 2589 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3994 "dhcp6_parser.cc"
    break;

  case 739:
#line 2596 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4004 "dhcp6_parser.cc"
    break;

  case 740:
#line 2603 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4013 "dhcp6_parser.cc"
    break;

  case 741:
#line 2606 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4022 "dhcp6_parser.cc"
    break;

  case 742:
#line 2612 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4031 "dhcp6_parser.cc"
    break;

  case 743:
#line 2615 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4041 "dhcp6_parser.cc"
    break;

  case 744:
#line 2622 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4050 "dhcp6_parser.cc"
    break;

  case 745:
#line 2625 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4060 "dhcp6_parser.cc"
    break;

  case 746:
#line 2632 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4069 "dhcp6_parser.cc"
    break;

  case 747:
#line 2635 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4079 "dhcp6_parser.cc"
    break;

  case 748:
#line 2644 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4091 "dhcp6_parser.cc"
    break;

  case 749:
#line 2650 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4101 "dhcp6_parser.cc"
    break;

  case 750:
#line 2656 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4111 "dhcp6_parser.cc"
    break;

  case 751:
#line 2660 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4120 "dhcp6_parser.cc"
    break;

  case 756:
#line 2675 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4132 "dhcp6_parser.cc"
    break;

  case 757:
#line 2681 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4141 "dhcp6_parser.cc"
    break;

  case 758:
#line 2686 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4151 "dhcp6_parser.cc"
    break;

  case 759:
#line 2694 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4163 "dhcp6_parser.cc"
    break;

  case 760:
#line 2700 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4172 "dhcp6_parser.cc"
    break;

  case 763:
#line 2712 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4182 "dhcp6_parser.cc"
    break;

  case 764:
#line 2716 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4190 "dhcp6_parser.cc"
    break;

  case 774:
#line 2733 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4200 "dhcp6_parser.cc"
    break;

  case 775:
#line 2739 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4209 "dhcp6_parser.cc"
    break;

  case 776:
#line 2742 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4219 "dhcp6_parser.cc"
    break;

  case 777:
#line 2748 "dhcp6_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4231 "dhcp6_parser.cc"
    break;

  case 778:
#line 2754 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4240 "dhcp6_parser.cc"
    break;

  case 781:
#line 2763 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4250 "dhcp6_parser.cc"
    break;

  case 782:
#line 2767 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4258 "dhcp6_parser.cc"
    break;

  case 790:
#line 2782 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4267 "dhcp6_parser.cc"
    break;

  case 791:
#line 2785 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4277 "dhcp6_parser.cc"
    break;

  case 792:
#line 2791 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4287 "dhcp6_parser.cc"
    break;

  case 793:
#line 2797 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4297 "dhcp6_parser.cc"
    break;

  case 794:
#line 2803 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4307 "dhcp6_parser.cc"
    break;

  case 795:
#line 2809 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4316 "dhcp6_parser.cc"
    break;

  case 796:
#line 2812 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4326 "dhcp6_parser.cc"
    break;


#line 4330 "dhcp6_parser.cc"

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
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
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
      error_token.state = state_type (yyn);
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
    std::ptrdiff_t yycount = 0;
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
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[+yystate];
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
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
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
    std::ptrdiff_t yyi = 0;
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


  const short Dhcp6Parser::yypact_ninf_ = -970;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     378,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,    37,    33,    62,    74,    76,
      78,    93,    97,   103,   107,   117,   126,   132,   147,   154,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,    33,  -149,
     106,   116,    27,   539,   170,   186,   274,   119,    63,   284,
     -72,   525,   337,  -970,   193,   202,   207,   220,   217,  -970,
     224,  -970,  -970,  -970,  -970,  -970,  -970,   237,   255,   268,
     295,   297,   309,   354,   362,   365,   372,   385,   387,   388,
     395,  -970,   403,   404,   413,   414,   422,  -970,  -970,  -970,
     424,   426,   428,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
     429,   432,   433,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,   434,  -970,  -970,  -970,  -970,  -970,  -970,   435,
    -970,   436,  -970,    60,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,   438,  -970,    91,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,   440,
     442,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,    94,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,   109,  -970,  -970,  -970,  -970,  -970,
     444,  -970,   445,   448,  -970,  -970,  -970,  -970,  -970,  -970,
     134,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,   302,   379,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,   446,  -970,
    -970,   449,  -970,  -970,  -970,   451,  -970,  -970,   450,   453,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,   460,   464,  -970,  -970,  -970,  -970,   461,
     469,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,   140,  -970,  -970,  -970,   476,  -970,  -970,
     479,  -970,   480,   481,  -970,  -970,   485,   488,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,   144,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,   490,   150,  -970,  -970,  -970,  -970,    33,
      33,  -970,    11,   491,  -970,   492,   493,   494,   500,   501,
     503,   304,   305,   307,   311,   312,   316,   319,   321,   266,
     308,   322,   323,   326,   331,   504,   334,   336,   338,   342,
     343,   507,   542,   547,   346,   347,   348,   553,   555,   557,
     558,   560,   561,   562,   375,   376,   377,   594,   595,   596,
     597,   607,   608,   610,   611,   612,   412,   616,   617,   619,
     623,   624,   625,   423,   627,  -970,   116,  -970,   636,   441,
      27,  -970,   638,   639,   643,   645,   646,   447,   454,   647,
     650,   651,   539,  -970,   659,   170,  -970,   661,   462,   662,
     463,   465,   186,  -970,   665,   667,   668,   669,   675,   676,
     677,  -970,   274,  -970,   692,   694,   495,   695,   697,   701,
     499,  -970,    63,   703,   502,   505,  -970,   284,   704,   706,
     163,  -970,   506,   707,   710,   497,   711,   511,   514,   716,
     717,   515,   516,   720,   721,   722,   723,   525,  -970,   724,
     530,   337,  -970,  -970,  -970,   732,   536,   533,   731,   733,
     734,   735,   752,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,   535,  -970,  -970,
    -970,  -970,  -970,  -115,   554,   556,  -970,  -970,  -970,   754,
     766,   769,   770,   771,   572,   310,  -970,  -970,  -970,   772,
     774,   775,   776,   777,   779,   780,   781,   782,  -970,   783,
     786,   789,   792,   577,   582,  -970,   795,  -970,   796,  -970,
    -970,   797,   801,   583,   603,   604,  -970,  -970,   796,   605,
     803,  -970,   609,  -970,   613,  -970,   614,  -970,  -970,  -970,
     796,   796,   796,   615,   618,   620,   621,  -970,   622,   626,
    -970,   628,   629,   630,  -970,  -970,   631,  -970,  -970,  -970,
     632,   771,  -970,  -970,   633,   634,  -970,   635,  -970,  -970,
     201,   641,  -970,  -970,  -115,   637,   640,   642,  -970,   806,
    -970,  -970,    33,   116,  -970,   337,    27,   296,   296,   809,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,   813,
     814,   820,   821,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,   -82,    33,   303,   719,   822,   833,   835,   270,   212,
       2,   -45,   225,   525,  -970,  -970,   836,  -970,  -970,   838,
     840,  -970,  -970,  -970,  -970,  -970,   -48,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,   809,  -970,   152,   190,
     199,  -970,  -970,  -970,  -970,   844,   845,   846,   847,   848,
    -970,   849,   850,   851,   852,  -970,  -970,  -970,   853,   854,
     855,   856,  -970,   200,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,   209,  -970,   857,
     858,  -970,  -970,   859,   861,  -970,  -970,   860,   864,  -970,
    -970,   862,   866,  -970,  -970,   865,   867,  -970,  -970,  -970,
      48,  -970,  -970,  -970,   868,  -970,  -970,  -970,   198,  -970,
    -970,  -970,  -970,   210,  -970,  -970,  -970,   242,  -970,  -970,
     869,   870,  -970,  -970,   872,   876,  -970,   877,   878,   879,
     880,   881,   882,   211,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,   883,   884,   885,  -970,  -970,  -970,  -970,
     227,  -970,  -970,  -970,  -970,  -970,  -970,   886,   887,   888,
    -970,   244,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,   278,  -970,  -970,  -970,   889,  -970,   890,
    -970,  -970,  -970,   280,  -970,  -970,  -970,  -970,  -970,   290,
    -970,   262,  -970,   658,  -970,   874,   892,  -970,  -970,   891,
     893,  -970,  -970,  -970,   895,  -970,   894,  -970,  -970,  -970,
     897,   900,   901,   902,   693,   700,   705,   702,   708,   904,
     709,   712,   713,   714,   907,   908,   911,   726,   728,   727,
     738,   296,  -970,  -970,   296,  -970,   809,   539,  -970,   813,
      63,  -970,   814,   284,  -970,   820,   698,  -970,   821,   -82,
    -970,  -970,   303,  -970,   914,   719,  -970,   196,   822,  -970,
     274,  -970,   833,   -72,  -970,   835,   744,   745,   746,   757,
     760,   785,   270,  -970,   920,   967,   791,   794,   798,   212,
    -970,   799,   805,   839,     2,  -970,   973,   998,   -45,  -970,
     811,  1036,   863,  1039,   225,  -970,  -970,   161,   836,  -970,
    -970,  1043,   896,   170,  -970,   838,   186,  -970,   840,  1046,
    -970,  -970,   398,   871,   873,   875,  -970,  -970,  -970,  -970,
    -970,   898,  -970,  -970,  -970,  -970,   899,   905,   906,  -970,
    -970,  -970,  -970,  -970,   299,  -970,   306,  -970,  1044,  -970,
    1045,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,   313,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,   909,  -970,  -970,
    1051,  -970,  -970,  -970,  -970,  -970,  1048,  1055,  -970,  -970,
    -970,  -970,  -970,  1052,  -970,   339,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,   246,   910,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,   912,   913,  -970,  -970,   915,  -970,
      33,  -970,  -970,  1057,  -970,  -970,  -970,  -970,  -970,   341,
    -970,  -970,  -970,  -970,  -970,  -970,   916,   349,  -970,   367,
    -970,   917,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,   698,  -970,
    -970,  1058,   918,  -970,   196,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  1059,   919,  1060,   161,
    -970,  -970,  -970,  -970,  -970,  -970,   922,  -970,  -970,  1054,
    -970,   923,  -970,  -970,  1063,  -970,  -970,   279,  -970,     8,
    1063,  -970,  -970,  1061,  1067,  1068,  -970,   380,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  1069,   921,   924,   925,  1070,
       8,  -970,   927,  -970,  -970,  -970,   928,  -970,  -970,  -970
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    62,     7,   171,     9,   337,    11,
     532,    13,   557,    15,   587,    17,   457,    19,   465,    21,
     502,    23,   302,    25,   700,    27,   750,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   589,     0,   467,   504,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    60,
       0,   127,   748,   169,   183,   185,   187,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   166,     0,     0,     0,     0,     0,   146,   153,   155,
       0,     0,     0,   329,   455,   494,   405,   545,   547,   397,
       0,     0,     0,   262,   279,   270,   255,   624,   579,   294,
     313,   645,     0,   281,   669,   682,   698,   159,   161,     0,
     759,     0,   126,     0,    64,    66,    67,    68,    69,    70,
      71,    72,    73,    74,   105,   106,   107,   108,   109,    75,
     113,   114,   115,   116,   117,   118,   119,   120,   111,   112,
     121,   122,   123,   100,   125,    78,    79,    80,    81,    97,
      82,    84,    83,   124,    88,    89,    76,   102,   103,   104,
     101,    77,    86,    87,    95,    96,    98,    85,    90,    91,
      92,    93,    94,    99,   110,   180,     0,   179,     0,   173,
     175,   176,   177,   178,   524,   549,   384,   386,   388,     0,
       0,   392,   390,   618,   383,   341,   342,   343,   344,   345,
     346,   347,   348,   367,   368,   369,   370,   371,   374,   375,
     376,   377,   378,   379,   380,   381,   372,   373,   382,     0,
     339,   352,   353,   354,   357,   358,   361,   362,   363,   360,
     355,   356,   349,   350,   365,   366,   351,   359,   364,   543,
     542,   538,   539,   537,     0,   534,   536,   540,   541,   572,
       0,   575,     0,     0,   571,   565,   566,   564,   569,   570,
       0,   559,   561,   562,   567,   568,   563,   616,   604,   606,
     608,   610,   612,   614,   603,   600,   601,   602,     0,   590,
     591,   595,   596,   593,   597,   598,   599,   594,     0,   484,
     233,     0,   488,   486,   491,     0,   480,   481,     0,   468,
     469,   471,   483,   472,   473,   474,   490,   475,   476,   477,
     478,   479,   518,     0,     0,   516,   517,   520,   521,     0,
     505,   506,   508,   509,   510,   511,   512,   513,   514,   515,
     309,   311,   306,     0,   304,   307,   308,     0,   723,   725,
       0,   728,     0,     0,   732,   736,     0,     0,   740,   742,
     744,   746,   721,   719,   720,     0,   702,   704,   716,   705,
     706,   707,   708,   709,   710,   711,   712,   713,   714,   715,
     717,   718,   756,     0,     0,   752,   754,   755,    46,     0,
       0,    39,     0,     0,    59,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    57,     0,    63,     0,     0,
       0,   172,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   338,     0,     0,   533,     0,     0,     0,
       0,     0,     0,   558,     0,     0,     0,     0,     0,     0,
       0,   588,     0,   458,     0,     0,     0,     0,     0,     0,
       0,   466,     0,     0,     0,     0,   503,     0,     0,     0,
       0,   303,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   701,     0,
       0,     0,   751,    50,    43,     0,     0,     0,     0,     0,
       0,     0,     0,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,     0,   164,   165,
     143,   144,   145,     0,     0,     0,   157,   158,   163,     0,
       0,     0,     0,     0,     0,     0,   394,   395,   396,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   668,     0,
       0,     0,     0,     0,     0,   168,     0,    65,     0,   182,
     174,     0,     0,     0,     0,     0,   403,   404,     0,     0,
       0,   340,     0,   535,     0,   574,     0,   577,   578,   560,
       0,     0,     0,     0,     0,     0,     0,   592,     0,     0,
     482,     0,     0,     0,   493,   470,     0,   522,   523,   507,
       0,     0,   305,   722,     0,     0,   727,     0,   730,   731,
       0,     0,   738,   739,     0,     0,     0,     0,   703,     0,
     758,   753,     0,     0,   128,     0,     0,     0,     0,   189,
     167,   148,   149,   150,   151,   152,   147,   154,   156,   331,
     459,   496,   407,    40,   546,   548,   399,   400,   401,   402,
     398,     0,    47,     0,     0,     0,   581,   296,     0,     0,
       0,     0,     0,     0,   160,   162,     0,    51,   181,   526,
     551,   385,   387,   389,   393,   391,     0,   544,   573,   576,
     617,   605,   607,   609,   611,   613,   615,   485,   234,   489,
     487,   492,   519,   310,   312,   724,   726,   729,   734,   735,
     733,   737,   741,   743,   745,   747,   189,    44,     0,     0,
       0,   220,   226,   228,   230,     0,     0,     0,     0,     0,
     246,     0,     0,     0,     0,   249,   251,   253,     0,     0,
       0,     0,   219,     0,   195,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   209,   210,   211,   218,   212,
     213,   214,   207,   208,   215,   216,   217,     0,   193,     0,
     190,   191,   335,     0,   332,   333,   463,     0,   460,   461,
     500,     0,   497,   498,   411,     0,   408,   409,   268,   269,
       0,   264,   266,   267,     0,   277,   278,   274,     0,   272,
     275,   276,   260,     0,   257,   259,   628,     0,   626,   585,
       0,   582,   583,   300,     0,   297,   298,     0,     0,     0,
       0,     0,     0,     0,   315,   317,   318,   319,   320,   321,
     322,   658,   664,     0,     0,     0,   657,   654,   655,   656,
       0,   647,   649,   652,   650,   651,   653,     0,     0,     0,
     290,     0,   283,   285,   286,   287,   288,   289,   678,   680,
     677,   675,   676,     0,   671,   673,   674,     0,   693,     0,
     696,   689,   690,     0,   684,   686,   687,   688,   691,     0,
     763,     0,   761,    53,   530,     0,   527,   528,   555,     0,
     552,   553,   622,   621,     0,   620,     0,    61,   749,   170,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   184,   186,     0,   188,     0,     0,   330,     0,
     467,   456,     0,   504,   495,     0,     0,   406,     0,     0,
     263,   280,     0,   271,     0,     0,   256,   630,     0,   625,
     589,   580,     0,     0,   295,     0,     0,     0,     0,     0,
       0,     0,     0,   314,     0,     0,     0,     0,     0,     0,
     646,     0,     0,     0,     0,   282,     0,     0,     0,   670,
       0,     0,     0,     0,     0,   683,   699,     0,     0,   760,
      55,     0,    54,     0,   525,     0,     0,   550,     0,     0,
     619,   757,     0,     0,     0,     0,   232,   235,   236,   237,
     238,     0,   248,   239,   240,   241,     0,     0,     0,   243,
     244,   245,   242,   196,     0,   192,     0,   334,     0,   462,
       0,   499,   454,   429,   430,   431,   433,   434,   435,   419,
     420,   438,   439,   440,   441,   442,   445,   446,   447,   448,
     449,   450,   451,   452,   443,   444,   453,   415,   416,   417,
     418,   427,   428,   424,   425,   426,   423,   432,     0,   413,
     421,   436,   437,   422,   410,   265,   273,     0,   258,   642,
       0,   640,   641,   637,   638,   639,     0,   631,   632,   634,
     635,   636,   627,     0,   584,     0,   299,   323,   324,   325,
     326,   327,   328,   316,     0,     0,   663,   666,   667,   648,
     291,   292,   293,   284,     0,     0,   672,   692,     0,   695,
       0,   685,   777,     0,   775,   773,   767,   771,   772,     0,
     765,   769,   770,   768,   762,    52,     0,     0,   529,     0,
     554,     0,   222,   223,   224,   225,   221,   227,   229,   231,
     247,   250,   252,   254,   194,   336,   464,   501,     0,   412,
     261,     0,     0,   629,     0,   586,   301,   660,   661,   662,
     659,   665,   679,   681,   694,   697,     0,     0,     0,     0,
     764,    56,   531,   556,   623,   414,     0,   644,   633,     0,
     774,     0,   766,   643,     0,   776,   781,     0,   779,     0,
       0,   778,   790,     0,     0,     0,   795,     0,   783,   785,
     786,   787,   788,   789,   780,     0,     0,     0,     0,     0,
       0,   782,     0,   792,   793,   794,     0,   784,   791,   796
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,   -10,  -970,  -562,  -970,
     396,  -970,  -970,  -970,  -970,   356,  -970,  -585,  -970,  -970,
    -970,   -71,  -970,  -970,  -970,  -970,  -970,  -970,   179,   590,
    -970,  -970,   -59,   -43,   -42,   -40,   -39,   -28,   -27,   -26,
     -23,   -21,   -15,    -9,    -3,  -970,    -1,    17,    18,    20,
    -970,   397,    25,  -970,    28,  -970,    30,    32,    35,  -970,
      38,  -970,    40,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,   384,   592,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,   314,  -970,    98,  -970,  -676,   102,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,   -67,
    -970,  -714,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,    80,  -970,  -970,  -970,  -970,  -970,
      87,  -698,  -970,  -970,  -970,  -970,    85,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,    54,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,    77,  -970,  -970,  -970,    81,   549,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,    69,  -970,  -970,  -970,  -970,
    -970,  -970,  -969,  -970,  -970,  -970,   104,  -970,  -970,  -970,
     108,   598,  -970,  -970,  -968,  -970,  -967,  -970,    51,  -970,
      55,  -970,    42,    45,    46,    50,  -970,  -970,  -970,  -961,
    -970,  -970,  -970,  -970,    99,  -970,  -970,  -122,  1021,  -970,
    -970,  -970,  -970,  -970,   113,  -970,  -970,  -970,   111,  -970,
     567,  -970,   -66,  -970,  -970,  -970,  -970,  -970,   -47,  -970,
    -970,  -970,  -970,  -970,    13,  -970,  -970,  -970,   120,  -970,
    -970,  -970,   125,  -970,   569,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,    57,  -970,  -970,  -970,
      70,   644,  -970,  -970,   -55,  -970,     1,  -970,  -970,  -970,
    -970,  -970,    64,  -970,  -970,  -970,    79,   648,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,   -57,  -970,  -970,  -970,   121,
    -970,  -970,  -970,   124,  -970,   649,   390,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -960,  -970,  -970,  -970,  -970,  -970,  -970,  -970,   129,  -970,
    -970,  -970,   -86,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
     110,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,   105,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,    96,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,   408,   585,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,  -970,
    -970,  -970,  -970,   455,   584,  -970,  -970,  -970,  -970,  -970,
    -970,   100,  -970,  -970,   -95,  -970,  -970,  -970,  -970,  -970,
    -970,  -114,  -970,  -970,  -128,  -970,  -970,  -970,  -970,  -970,
    -970,  -970
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     714,    87,    88,    41,    68,    84,    85,   738,   943,  1051,
    1052,   802,    43,    70,    90,   423,    45,    71,   153,   154,
     155,   425,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     451,   706,   174,   452,   175,   453,   176,   177,   178,   481,
     179,   482,   180,   181,   182,   183,   445,   184,   185,   427,
      47,    72,   218,   219,   220,   488,   221,   186,   428,   187,
     429,   188,   430,   829,   830,   831,   984,   803,   804,   805,
     960,  1206,   806,   961,   807,   962,   808,   963,   809,   810,
     525,   811,   812,   813,   814,   815,   816,   817,   818,   819,
     820,   821,   822,   969,   823,   824,   974,   825,   975,   826,
     976,   189,   470,   863,   864,   865,  1004,   190,   467,   850,
     851,   852,   853,   191,   469,   858,   859,   860,   861,   192,
     468,   193,   477,   911,   912,   913,   914,   915,   194,   473,
     874,   875,   876,  1013,    63,    80,   373,   374,   375,   538,
     376,   539,   195,   474,   883,   884,   885,   886,   887,   888,
     889,   890,   196,   457,   833,   834,   835,   987,    49,    73,
     259,   260,   261,   494,   262,   495,   263,   496,   264,   500,
     265,   499,   197,   198,   199,   200,   463,   720,   270,   271,
     201,   460,   845,   846,   847,   996,  1128,  1129,   202,   458,
      57,    77,   837,   838,   839,   990,    59,    78,   338,   339,
     340,   341,   342,   343,   344,   524,   345,   528,   346,   527,
     347,   348,   529,   349,   203,   459,   841,   842,   843,   993,
      61,    79,   359,   360,   361,   362,   363,   533,   364,   365,
     366,   367,   273,   492,   945,   946,   947,  1053,    51,    74,
     284,   285,   286,   504,   204,   461,   205,   462,   276,   493,
     949,   950,   951,  1056,    53,    75,   300,   301,   302,   507,
     303,   304,   509,   305,   306,   206,   472,   870,   871,   872,
    1010,    55,    76,   318,   319,   320,   321,   515,   322,   516,
     323,   517,   324,   518,   325,   519,   326,   520,   327,   514,
     278,   501,   954,   955,  1059,   207,   471,   867,   868,  1007,
    1146,  1147,  1148,  1149,  1150,  1221,  1151,   208,   475,   900,
     901,   902,  1024,  1230,   903,   904,  1025,   905,   906,   209,
     210,   478,   923,   924,   925,  1036,   926,  1037,   211,   479,
     933,   934,   935,   936,  1041,   937,   938,  1043,   212,   480,
      65,    81,   395,   396,   397,   398,   543,   399,   544,   400,
     401,   546,   402,   403,   404,   549,   770,   405,   550,   406,
     407,   408,   553,   409,   554,   410,   555,   411,   556,   213,
     426,    67,    82,   414,   415,   416,   559,   417,   214,   484,
     941,   942,  1047,  1189,  1190,  1191,  1192,  1238,  1193,  1236,
    1257,  1258,  1259,  1267,  1268,  1269,  1275,  1270,  1271,  1272,
    1273,  1279
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     152,   217,   234,   280,   294,   314,    38,   336,   355,   372,
     392,   337,   356,   357,   235,   897,   277,   222,   274,   287,
     298,   316,   827,   350,   368,   857,   393,  1118,  1119,  1120,
     236,   237,   358,   238,   239,  1127,  1133,    30,    31,   848,
      32,   713,    33,   215,   216,   240,   241,   242,   127,   128,
     243,   999,   244,   744,  1000,    86,   370,   371,   245,   701,
     702,   703,   704,   486,   246,   750,   751,   752,   487,    42,
     247,   308,   248,   223,   275,   288,   299,   317,   952,   351,
     369,    44,   394,    46,   329,    48,   272,   283,   297,   315,
     249,   250,   705,   251,   490,   127,   128,   502,   252,   491,
      50,   253,   503,   254,    52,   255,   918,   919,   256,   713,
      54,   257,   505,   258,    56,   266,    89,   506,   267,   268,
     127,   128,   849,   269,    58,   281,   295,    91,    92,   282,
     296,    93,   151,    60,    94,    95,    96,   512,   330,    62,
     331,   332,   513,   540,   333,   334,   335,   557,   541,   907,
     908,   909,   558,   561,    64,   486,   127,   128,   562,   151,
     957,    66,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,  1262,   124,   561,  1263,  1264,  1265,  1266,   958,   418,
     126,  1002,   490,   981,  1003,   419,   151,   959,   982,   127,
     128,   420,   981,  1005,  1022,   565,   129,   983,  1006,  1023,
     422,   130,   131,   132,   133,   134,   135,   136,   421,   137,
    1029,   151,   424,   891,   138,  1030,   330,    34,    35,    36,
      37,   431,   786,   139,   125,  1008,   140,  1034,  1009,  1118,
    1119,  1120,  1035,   141,   127,   128,   279,  1127,  1133,   432,
     125,   142,   143,   127,   128,  1048,   144,   151,  1049,   145,
     125,   330,   433,   146,   289,   290,   291,   292,   293,   127,
     128,  1038,  1260,  1044,   231,  1261,  1039,   232,  1045,   127,
     128,   370,   371,   557,   147,   148,   149,   150,  1046,   434,
     231,   435,   981,   232,   857,   127,   128,  1214,  1084,   502,
     521,  1139,  1140,   436,  1215,   897,  1218,   781,   127,   128,
     151,  1219,   782,   783,   784,   785,   786,   787,   788,   789,
     790,   791,   792,   793,   794,   795,   796,   797,   798,   799,
     800,   801,   540,  1182,  1239,  1183,  1184,  1226,   125,  1240,
     412,   413,   505,   892,   893,   894,   895,  1242,   437,   330,
     352,   331,   332,   353,   354,   151,   438,   127,   128,   439,
     512,   330,   768,   769,   151,  1243,   440,   127,   128,   927,
     928,   929,   522,  1280,  1227,  1228,  1229,   307,  1281,   441,
     151,   442,   443,   308,   309,   310,   311,   312,   313,   444,
     151,   877,   878,   879,   880,   881,   882,   446,   447,   563,
     564,   716,   717,   718,   719,   152,   151,   448,   449,   217,
    1202,  1203,  1204,  1205,   848,   855,   450,   856,   454,   930,
     455,   234,   456,   464,   280,   222,   465,   466,   476,   483,
     485,   294,   489,   235,   497,   277,   498,   274,   508,   510,
     287,   314,   511,   526,   523,   530,   532,   298,   531,   236,
     237,   336,   238,   239,   534,   337,   355,   316,   535,   536,
     356,   357,   537,   581,   240,   241,   242,   350,   151,   243,
     542,   244,   368,   545,   547,   548,   392,   245,   151,   551,
     358,   223,   552,   246,   560,   566,   567,   568,   569,   247,
     151,   248,   393,   275,   570,   571,   288,   572,   587,   573,
     574,   593,   575,   299,   582,   272,   576,   577,   283,   249,
     250,   578,   251,   317,   579,   297,   580,   252,   583,   584,
     253,   585,   254,   351,   255,   315,   586,   256,   369,   588,
     257,   589,   258,   693,   266,   590,   594,   267,   268,   591,
     592,   595,   269,   596,   597,   598,   281,   599,   394,   600,
     282,   601,   602,   295,   603,   604,   605,   296,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,   606,   607,   608,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   609,   610,
     611,   612,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   613,   614,   125,   615,   616,   617,   618,   127,   128,
     619,   620,   152,   621,   224,   217,   225,   622,   623,   624,
     625,   626,   127,   128,   226,   227,   228,   229,   230,   129,
     628,   222,   631,   632,   130,   131,   132,   633,   629,   634,
     635,   638,   636,   231,   639,   640,   232,   138,   896,   910,
     920,   637,   392,   642,   233,   644,   646,   645,   647,   650,
     648,   651,   652,   653,   898,   916,   921,   931,   393,   654,
     655,   656,   777,   377,   378,   379,   380,   381,   382,   383,
     384,   385,   386,   387,   388,   389,   658,   223,   659,   661,
     660,   662,   676,   390,   391,   663,   664,   666,   670,   667,
     671,   674,   668,   673,   675,   677,   678,   147,   148,   679,
     680,   681,   682,   683,   684,   685,   686,   687,   689,   151,
     899,   917,   922,   932,   394,   690,   692,   694,   695,   700,
     696,   697,   698,   151,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   699,   707,   709,
     708,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   710,   125,   330,   711,   712,   715,   721,    32,   722,
     723,   734,   725,   724,   726,   727,   735,   741,   728,   729,
     730,   127,   128,   731,   227,   228,   732,   230,   129,   733,
     736,   737,   739,   130,   131,   132,   740,   742,   743,   745,
     746,   776,   231,   747,   771,   232,   828,   748,   749,   753,
     832,   836,   754,   233,   755,   756,   757,   840,   844,   866,
     758,   862,   759,   760,   761,   762,   763,   765,   766,   767,
     869,   773,   873,   940,   774,   944,   775,   948,   964,   965,
     966,   967,   968,   970,   971,   972,   973,   977,   978,   979,
     980,   986,  1050,   985,   989,   988,   991,   992,   994,   995,
     998,   997,   778,  1012,  1001,  1011,   147,   148,  1014,  1015,
    1054,  1016,  1017,  1018,  1019,  1020,  1021,  1026,  1027,  1028,
    1031,  1032,  1033,  1040,  1042,  1055,  1058,  1057,  1066,  1196,
    1061,  1062,   151,  1060,  1063,  1064,  1065,  1067,  1071,  1069,
    1068,  1076,  1077,  1070,  1072,  1078,   234,  1073,  1137,   336,
    1074,  1075,   355,   337,  1164,  1092,   356,   357,   235,  1117,
     277,  1079,   274,  1080,  1081,   350,  1141,  1093,   368,   314,
    1142,  1131,   372,  1082,   236,   237,   358,   238,   239,  1157,
    1158,  1159,  1144,  1094,  1095,   316,  1096,  1097,   896,   240,
     241,   242,  1160,   910,   243,  1161,   244,   920,  1098,  1099,
    1100,  1165,   245,  1101,   898,  1102,  1185,  1174,   246,   916,
    1186,  1103,   280,   921,   247,   294,   248,  1104,   275,   931,
    1162,   351,  1187,  1105,   369,  1106,  1166,  1132,   287,  1167,
     272,   298,  1175,  1168,   249,   250,  1170,   251,  1145,  1130,
    1171,   317,   252,  1107,  1108,   253,  1109,   254,  1177,   255,
    1143,  1110,   256,   315,  1111,   257,  1112,   258,  1113,   266,
     899,  1114,   267,   268,  1115,   917,  1116,   269,  1123,   922,
    1178,  1124,  1125,  1180,  1172,   932,  1126,  1121,  1188,  1195,
    1201,  1122,  1216,  1217,   288,  1222,  1223,   299,  1224,  1254,
    1225,  1237,  1246,  1249,  1251,  1276,   283,   764,  1179,   297,
    1256,  1277,  1278,  1282,  1286,  1207,   627,  1208,   854,  1209,
     780,   772,   630,  1083,  1085,  1138,  1135,  1136,  1173,   672,
     956,  1163,  1156,  1087,  1155,  1086,  1245,  1134,   328,   665,
     641,  1088,  1210,  1211,   281,  1089,   669,   295,   282,  1212,
    1213,   296,  1198,  1220,  1231,  1091,  1232,  1233,  1090,  1234,
    1241,  1244,  1200,  1197,  1250,  1247,  1253,  1255,  1283,  1284,
    1285,  1288,  1289,  1154,  1153,  1199,   953,  1152,  1248,  1169,
    1181,   939,   688,  1176,  1252,   691,  1274,  1092,  1194,   643,
     779,  1117,  1287,  1141,     0,     0,     0,  1142,     0,  1093,
     649,     0,     0,  1131,     0,     0,     0,     0,  1185,  1144,
    1235,   657,  1186,     0,     0,  1094,  1095,     0,  1096,  1097,
       0,     0,     0,     0,  1187,     0,     0,     0,     0,     0,
    1098,  1099,  1100,     0,     0,  1101,     0,  1102,     0,     0,
       0,     0,     0,  1103,     0,     0,     0,     0,     0,  1104,
       0,     0,     0,     0,     0,  1105,     0,  1106,     0,  1132,
       0,     0,     0,     0,     0,  1145,     0,     0,     0,     0,
       0,  1130,     0,     0,     0,  1107,  1108,  1143,  1109,     0,
    1188,     0,     0,  1110,     0,     0,  1111,     0,  1112,     0,
    1113,     0,     0,  1114,     0,     0,  1115,     0,  1116,     0,
    1123,     0,     0,  1124,  1125,     0,     0,     0,  1126,  1121,
       0,     0,     0,  1122
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,    78,    79,    79,    73,   729,    73,    72,    73,    74,
      75,    76,   698,    78,    79,   723,    81,   996,   996,   996,
      73,    73,    79,    73,    73,   996,   996,     0,     5,   121,
       7,   603,     9,    16,    17,    73,    73,    73,    93,    94,
      73,     3,    73,   638,     6,   204,   128,   129,    73,   174,
     175,   176,   177,     3,    73,   650,   651,   652,     8,     7,
      73,   119,    73,    72,    73,    74,    75,    76,   126,    78,
      79,     7,    81,     7,    21,     7,    73,    74,    75,    76,
      73,    73,   207,    73,     3,    93,    94,     3,    73,     8,
       7,    73,     8,    73,     7,    73,   151,   152,    73,   671,
       7,    73,     3,    73,     7,    73,    10,     8,    73,    73,
      93,    94,   204,    73,     7,    74,    75,    11,    12,    74,
      75,    15,   204,     7,    18,    19,    20,     3,    75,     7,
      77,    78,     8,     3,    81,    82,    83,     3,     8,   147,
     148,   149,     8,     3,     7,     3,    93,    94,     8,   204,
       8,     7,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,   183,    73,     3,   186,   187,   188,   189,     8,     6,
      84,     3,     3,     3,     6,     3,   204,     8,     8,    93,
      94,     4,     3,     3,     3,   204,   100,     8,     8,     8,
       3,   105,   106,   107,   108,   109,   110,   111,     8,   113,
       3,   204,     8,    21,   118,     8,    75,   204,   205,   206,
     207,     4,    30,   127,    74,     3,   130,     3,     6,  1218,
    1218,  1218,     8,   137,    93,    94,    86,  1218,  1218,     4,
      74,   145,   146,    93,    94,     3,   150,   204,     6,   153,
      74,    75,     4,   157,    88,    89,    90,    91,    92,    93,
      94,     3,     3,     3,   114,     6,     8,   117,     8,    93,
      94,   128,   129,     3,   178,   179,   180,   181,     8,     4,
     114,     4,     3,   117,  1002,    93,    94,     8,   984,     3,
       8,   115,   116,     4,     8,  1029,     3,    21,    93,    94,
     204,     8,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,     3,   182,     3,   184,   185,     8,    74,     8,
      13,    14,     3,   141,   142,   143,   144,     8,     4,    75,
      76,    77,    78,    79,    80,   204,     4,    93,    94,     4,
       3,    75,   171,   172,   204,     8,     4,    93,    94,   154,
     155,   156,     3,     3,   138,   139,   140,   113,     8,     4,
     204,     4,     4,   119,   120,   121,   122,   123,   124,     4,
     204,   131,   132,   133,   134,   135,   136,     4,     4,   419,
     420,   101,   102,   103,   104,   486,   204,     4,     4,   490,
      22,    23,    24,    25,   121,   122,     4,   124,     4,   204,
       4,   502,     4,     4,   505,   490,     4,     4,     4,     4,
       4,   512,     4,   502,     4,   502,     4,   502,     4,     4,
     505,   522,     4,     4,     8,     4,     3,   512,     8,   502,
     502,   532,   502,   502,     4,   532,   537,   522,     4,     8,
     537,   537,     3,   207,   502,   502,   502,   532,   204,   502,
       4,   502,   537,     4,     4,     4,   557,   502,   204,     4,
     537,   490,     4,   502,     4,     4,     4,     4,     4,   502,
     204,   502,   557,   502,     4,     4,   505,     4,     4,   205,
     205,     4,   205,   512,   206,   502,   205,   205,   505,   502,
     502,   205,   502,   522,   205,   512,   205,   502,   206,   206,
     502,   205,   502,   532,   502,   522,   205,   502,   537,   205,
     502,   205,   502,     7,   502,   207,     4,   502,   502,   207,
     207,     4,   502,   207,   207,   207,   505,     4,   557,     4,
     505,     4,     4,   512,     4,     4,     4,   512,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   207,   207,   207,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,     4,     4,
       4,     4,    63,    64,    65,    66,    67,    68,    69,    70,
      71,     4,     4,    74,     4,     4,     4,   205,    93,    94,
       4,     4,   693,     4,    85,   696,    87,     4,     4,     4,
     207,     4,    93,    94,    95,    96,    97,    98,    99,   100,
       4,   696,     4,     4,   105,   106,   107,     4,   207,     4,
       4,     4,   205,   114,     4,     4,   117,   118,   729,   730,
     731,   207,   733,     4,   125,     4,     4,   205,   205,     4,
     205,     4,     4,     4,   729,   730,   731,   732,   733,     4,
       4,     4,   692,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,     4,   696,     4,     4,
     205,     4,   205,   178,   179,     4,   207,     4,     4,   207,
       4,     4,   207,   207,     4,     4,   205,   178,   179,   205,
       4,     4,   207,   207,     4,     4,     4,     4,     4,   204,
     729,   730,   731,   732,   733,   205,     4,   204,     7,   204,
       7,     7,     7,   204,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,     5,   204,     5,
     204,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,     5,    74,    75,     5,     5,   204,     5,     7,     5,
       5,   204,     5,     7,     5,     5,   204,   204,     7,     7,
       7,    93,    94,     7,    96,    97,     7,    99,   100,     7,
       5,     5,     5,   105,   106,   107,     5,   204,   204,   204,
       7,     5,   114,   204,   173,   117,     7,   204,   204,   204,
       7,     7,   204,   125,   204,   204,   204,     7,     7,     7,
     204,   112,   204,   204,   204,   204,   204,   204,   204,   204,
       7,   204,     7,     7,   204,     7,   204,     7,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     3,   204,     6,     3,     6,     6,     3,     6,     3,
       3,     6,   693,     3,     6,     6,   178,   179,     6,     3,
       6,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     3,     3,     6,   205,     3,
       6,     4,   204,     8,     4,     4,     4,   207,     4,   207,
     205,     4,     4,   205,   205,     4,   987,   205,     4,   990,
     207,   207,   993,   990,     4,   996,   993,   993,   987,   996,
     987,   205,   987,   205,   207,   990,  1007,   996,   993,  1010,
    1007,   996,  1013,   205,   987,   987,   993,   987,   987,   205,
     205,   205,  1007,   996,   996,  1010,   996,   996,  1029,   987,
     987,   987,   205,  1034,   987,   205,   987,  1038,   996,   996,
     996,     4,   987,   996,  1029,   996,  1047,     4,   987,  1034,
    1047,   996,  1053,  1038,   987,  1056,   987,   996,   987,  1044,
     205,   990,  1047,   996,   993,   996,   205,   996,  1053,   205,
     987,  1056,     4,   205,   987,   987,   207,   987,  1007,   996,
     205,  1010,   987,   996,   996,   987,   996,   987,   207,   987,
    1007,   996,   987,  1010,   996,   987,   996,   987,   996,   987,
    1029,   996,   987,   987,   996,  1034,   996,   987,   996,  1038,
       4,   996,   996,     4,   205,  1044,   996,   996,  1047,     6,
       4,   996,     8,     8,  1053,     4,     8,  1056,     3,     5,
       8,     4,     4,     4,     4,     4,  1053,   671,   205,  1056,
       7,     4,     4,     4,     4,   204,   486,   204,   722,   204,
     696,   684,   490,   981,   986,  1005,   999,  1002,  1034,   540,
     776,  1022,  1015,   989,  1013,   987,  1218,   998,    77,   532,
     502,   990,   204,   204,  1053,   992,   537,  1056,  1053,   204,
     204,  1056,  1055,   204,   204,   995,   204,   204,   993,   204,
     204,   204,  1058,  1053,   205,   207,   204,   204,   207,   205,
     205,   204,   204,  1012,  1010,  1056,   746,  1008,  1224,  1029,
    1044,   733,   557,  1038,  1239,   561,  1260,  1218,  1048,   505,
     695,  1218,  1280,  1224,    -1,    -1,    -1,  1224,    -1,  1218,
     512,    -1,    -1,  1218,    -1,    -1,    -1,    -1,  1239,  1224,
    1180,   522,  1239,    -1,    -1,  1218,  1218,    -1,  1218,  1218,
      -1,    -1,    -1,    -1,  1239,    -1,    -1,    -1,    -1,    -1,
    1218,  1218,  1218,    -1,    -1,  1218,    -1,  1218,    -1,    -1,
      -1,    -1,    -1,  1218,    -1,    -1,    -1,    -1,    -1,  1218,
      -1,    -1,    -1,    -1,    -1,  1218,    -1,  1218,    -1,  1218,
      -1,    -1,    -1,    -1,    -1,  1224,    -1,    -1,    -1,    -1,
      -1,  1218,    -1,    -1,    -1,  1218,  1218,  1224,  1218,    -1,
    1239,    -1,    -1,  1218,    -1,    -1,  1218,    -1,  1218,    -1,
    1218,    -1,    -1,  1218,    -1,    -1,  1218,    -1,  1218,    -1,
    1218,    -1,    -1,  1218,  1218,    -1,    -1,    -1,  1218,  1218,
      -1,    -1,    -1,  1218
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
       0,     5,     7,     9,   204,   205,   206,   207,   224,   225,
     226,   231,     7,   240,     7,   244,     7,   288,     7,   396,
       7,   476,     7,   492,     7,   509,     7,   428,     7,   434,
       7,   458,     7,   372,     7,   578,     7,   609,   232,   227,
     241,   245,   289,   397,   477,   493,   510,   429,   435,   459,
     373,   579,   610,   224,   233,   234,   204,   229,   230,    10,
     242,    11,    12,    15,    18,    19,    20,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    84,    93,    94,   100,
     105,   106,   107,   108,   109,   110,   111,   113,   118,   127,
     130,   137,   145,   146,   150,   153,   157,   178,   179,   180,
     181,   204,   239,   246,   247,   248,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   270,   272,   274,   275,   276,   278,
     280,   281,   282,   283,   285,   286,   295,   297,   299,   339,
     345,   351,   357,   359,   366,   380,   390,   410,   411,   412,
     413,   418,   426,   452,   482,   484,   503,   533,   545,   557,
     558,   566,   576,   607,   616,    16,    17,   239,   290,   291,
     292,   294,   482,   484,    85,    87,    95,    96,    97,    98,
      99,   114,   117,   125,   239,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   264,   265,
     266,   267,   270,   272,   274,   275,   276,   278,   280,   398,
     399,   400,   402,   404,   406,   408,   410,   411,   412,   413,
     416,   417,   452,   470,   482,   484,   486,   503,   528,    86,
     239,   406,   408,   452,   478,   479,   480,   482,   484,    88,
      89,    90,    91,    92,   239,   406,   408,   452,   482,   484,
     494,   495,   496,   498,   499,   501,   502,   113,   119,   120,
     121,   122,   123,   124,   239,   452,   482,   484,   511,   512,
     513,   514,   516,   518,   520,   522,   524,   526,   426,    21,
      75,    77,    78,    81,    82,    83,   239,   317,   436,   437,
     438,   439,   440,   441,   442,   444,   446,   448,   449,   451,
     482,   484,    76,    79,    80,   239,   317,   440,   446,   460,
     461,   462,   463,   464,   466,   467,   468,   469,   482,   484,
     128,   129,   239,   374,   375,   376,   378,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     178,   179,   239,   482,   484,   580,   581,   582,   583,   585,
     587,   588,   590,   591,   592,   595,   597,   598,   599,   601,
     603,   605,    13,    14,   611,   612,   613,   615,     6,     3,
       4,     8,     3,   243,     8,   249,   608,   287,   296,   298,
     300,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   284,     4,     4,     4,     4,
       4,   268,   271,   273,     4,     4,     4,   391,   427,   453,
     419,   483,   485,   414,     4,     4,     4,   346,   358,   352,
     340,   534,   504,   367,   381,   546,     4,   360,   559,   567,
     577,   277,   279,     4,   617,     4,     3,     8,   293,     4,
       3,     8,   471,   487,   401,   403,   405,     4,     4,   409,
     407,   529,     3,     8,   481,     3,     8,   497,     4,   500,
       4,     4,     3,     8,   527,   515,   517,   519,   521,   523,
     525,     8,     3,     8,   443,   318,     4,   447,   445,   450,
       4,     8,     3,   465,     4,     4,     8,     3,   377,   379,
       3,     8,     4,   584,   586,     4,   589,     4,     4,   593,
     596,     4,     4,   600,   602,   604,   606,     3,     8,   614,
       4,     3,     8,   224,   224,   204,     4,     4,     4,     4,
       4,     4,     4,   205,   205,   205,   205,   205,   205,   205,
     205,   207,   206,   206,   206,   205,   205,     4,   205,   205,
     207,   207,   207,     4,     4,     4,   207,   207,   207,     4,
       4,     4,     4,     4,     4,     4,   207,   207,   207,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   205,     4,
       4,     4,     4,     4,     4,   207,     4,   247,     4,   207,
     291,     4,     4,     4,     4,     4,   205,   207,     4,     4,
       4,   399,     4,   479,     4,   205,     4,   205,   205,   495,
       4,     4,     4,     4,     4,     4,     4,   513,     4,     4,
     205,     4,     4,     4,   207,   438,     4,   207,   207,   462,
       4,     4,   375,   207,     4,     4,   205,     4,   205,   205,
       4,     4,   207,   207,     4,     4,     4,     4,   581,     4,
     205,   612,     4,     7,   204,     7,     7,     7,     7,     5,
     204,   174,   175,   176,   177,   207,   269,   204,   204,     5,
       5,     5,     5,   226,   228,   204,   101,   102,   103,   104,
     415,     5,     5,     5,     7,     5,     5,     5,     7,     7,
       7,     7,     7,     7,   204,   204,     5,     5,   235,     5,
       5,   204,   204,   204,   235,   204,     7,   204,   204,   204,
     235,   235,   235,   204,   204,   204,   204,   204,   204,   204,
     204,   204,   204,   204,   228,   204,   204,   204,   171,   172,
     594,   173,   269,   204,   204,   204,     5,   224,   246,   611,
     290,    21,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,   239,   305,   306,   307,   310,   312,   314,   316,
     317,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   332,   333,   335,   337,   305,     7,   301,
     302,   303,     7,   392,   393,   394,     7,   430,   431,   432,
       7,   454,   455,   456,     7,   420,   421,   422,   121,   204,
     347,   348,   349,   350,   233,   122,   124,   349,   353,   354,
     355,   356,   112,   341,   342,   343,     7,   535,   536,     7,
     505,   506,   507,     7,   368,   369,   370,   131,   132,   133,
     134,   135,   136,   382,   383,   384,   385,   386,   387,   388,
     389,    21,   141,   142,   143,   144,   239,   319,   482,   484,
     547,   548,   549,   552,   553,   555,   556,   147,   148,   149,
     239,   361,   362,   363,   364,   365,   482,   484,   151,   152,
     239,   482,   484,   560,   561,   562,   564,   154,   155,   156,
     204,   482,   484,   568,   569,   570,   571,   573,   574,   580,
       7,   618,   619,   236,     7,   472,   473,   474,     7,   488,
     489,   490,   126,   514,   530,   531,   301,     8,     8,     8,
     308,   311,   313,   315,     4,     4,     4,     4,     4,   331,
       4,     4,     4,     4,   334,   336,   338,     4,     4,     4,
       4,     3,     8,     8,   304,     6,     3,   395,     6,     3,
     433,     6,     3,   457,     6,     3,   423,     6,     3,     3,
       6,     6,     3,     6,   344,     3,     8,   537,     3,     6,
     508,     6,     3,   371,     6,     3,     4,     4,     4,     4,
       4,     4,     3,     8,   550,   554,     4,     4,     4,     3,
       8,     4,     4,     4,     3,     8,   563,   565,     3,     8,
       4,   572,     4,   575,     3,     8,     8,   620,     3,     6,
     204,   237,   238,   475,     6,     3,   491,     6,     3,   532,
       8,     6,     4,     4,     4,     4,   205,   207,   205,   207,
     205,     4,   205,   205,   207,   207,     4,     4,     4,   205,
     205,   207,   205,   306,   305,   303,   398,   394,   436,   432,
     460,   456,   239,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   264,   265,   266,   267,
     270,   272,   274,   275,   276,   278,   280,   317,   390,   402,
     404,   406,   408,   410,   411,   412,   413,   417,   424,   425,
     452,   482,   484,   528,   422,   348,   354,     4,   342,   115,
     116,   239,   317,   452,   482,   484,   538,   539,   540,   541,
     542,   544,   536,   511,   507,   374,   370,   205,   205,   205,
     205,   205,   205,   383,     4,     4,   205,   205,   205,   548,
     207,   205,   205,   362,     4,     4,   561,   207,     4,   205,
       4,   569,   182,   184,   185,   239,   317,   482,   484,   621,
     622,   623,   624,   626,   619,     6,     3,   478,   474,   494,
     490,     4,    22,    23,    24,    25,   309,   204,   204,   204,
     204,   204,   204,   204,     8,     8,     8,     8,     3,     8,
     204,   543,     4,     8,     3,     8,     8,   138,   139,   140,
     551,   204,   204,   204,   204,   224,   627,     4,   625,     3,
       8,   204,     8,     8,   204,   425,     4,   207,   540,     4,
     205,     4,   622,   204,     5,   204,     7,   628,   629,   630,
       3,     6,   183,   186,   187,   188,   189,   631,   632,   633,
     635,   636,   637,   638,   629,   634,     4,     4,     4,   639,
       3,     8,     4,   207,   205,   205,     4,   632,   204,   204
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   208,   210,   209,   211,   209,   212,   209,   213,   209,
     214,   209,   215,   209,   216,   209,   217,   209,   218,   209,
     219,   209,   220,   209,   221,   209,   222,   209,   223,   209,
     224,   224,   224,   224,   224,   224,   224,   225,   227,   226,
     228,   229,   229,   230,   230,   232,   231,   233,   233,   234,
     234,   236,   235,   237,   237,   238,   238,   239,   241,   240,
     243,   242,   245,   244,   246,   246,   247,   247,   247,   247,
     247,   247,   247,   247,   247,   247,   247,   247,   247,   247,
     247,   247,   247,   247,   247,   247,   247,   247,   247,   247,
     247,   247,   247,   247,   247,   247,   247,   247,   247,   247,
     247,   247,   247,   247,   247,   247,   247,   247,   247,   247,
     247,   247,   247,   247,   247,   247,   247,   247,   247,   247,
     247,   247,   247,   247,   247,   247,   247,   249,   248,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   268,   267,   269,   269,
     269,   269,   269,   271,   270,   273,   272,   274,   275,   277,
     276,   279,   278,   280,   281,   282,   284,   283,   285,   287,
     286,   289,   288,   290,   290,   291,   291,   291,   291,   291,
     293,   292,   294,   296,   295,   298,   297,   300,   299,   301,
     301,   302,   302,   304,   303,   305,   305,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     308,   307,   309,   309,   309,   309,   311,   310,   313,   312,
     315,   314,   316,   318,   317,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   331,   330,   332,   334,
     333,   336,   335,   338,   337,   340,   339,   341,   341,   342,
     344,   343,   346,   345,   347,   347,   348,   348,   349,   350,
     352,   351,   353,   353,   354,   354,   354,   355,   356,   358,
     357,   360,   359,   361,   361,   362,   362,   362,   362,   362,
     362,   363,   364,   365,   367,   366,   368,   368,   369,   369,
     371,   370,   373,   372,   374,   374,   374,   375,   375,   377,
     376,   379,   378,   381,   380,   382,   382,   383,   383,   383,
     383,   383,   383,   384,   385,   386,   387,   388,   389,   391,
     390,   392,   392,   393,   393,   395,   394,   397,   396,   398,
     398,   399,   399,   399,   399,   399,   399,   399,   399,   399,
     399,   399,   399,   399,   399,   399,   399,   399,   399,   399,
     399,   399,   399,   399,   399,   399,   399,   399,   399,   399,
     399,   399,   399,   399,   399,   399,   399,   399,   399,   399,
     399,   399,   399,   399,   401,   400,   403,   402,   405,   404,
     407,   406,   409,   408,   410,   411,   412,   414,   413,   415,
     415,   415,   415,   416,   417,   419,   418,   420,   420,   421,
     421,   423,   422,   424,   424,   425,   425,   425,   425,   425,
     425,   425,   425,   425,   425,   425,   425,   425,   425,   425,
     425,   425,   425,   425,   425,   425,   425,   425,   425,   425,
     425,   425,   425,   425,   425,   425,   425,   425,   425,   425,
     425,   425,   425,   425,   425,   427,   426,   429,   428,   430,
     430,   431,   431,   433,   432,   435,   434,   436,   436,   437,
     437,   438,   438,   438,   438,   438,   438,   438,   438,   438,
     438,   439,   440,   441,   443,   442,   445,   444,   447,   446,
     448,   450,   449,   451,   453,   452,   454,   454,   455,   455,
     457,   456,   459,   458,   460,   460,   461,   461,   462,   462,
     462,   462,   462,   462,   462,   462,   462,   463,   465,   464,
     466,   467,   468,   469,   471,   470,   472,   472,   473,   473,
     475,   474,   477,   476,   478,   478,   479,   479,   479,   479,
     479,   479,   479,   481,   480,   483,   482,   485,   484,   487,
     486,   488,   488,   489,   489,   491,   490,   493,   492,   494,
     494,   495,   495,   495,   495,   495,   495,   495,   495,   495,
     495,   495,   497,   496,   498,   500,   499,   501,   502,   504,
     503,   505,   505,   506,   506,   508,   507,   510,   509,   511,
     511,   512,   512,   513,   513,   513,   513,   513,   513,   513,
     513,   513,   513,   513,   515,   514,   517,   516,   519,   518,
     521,   520,   523,   522,   525,   524,   527,   526,   529,   528,
     530,   530,   532,   531,   534,   533,   535,   535,   537,   536,
     538,   538,   539,   539,   540,   540,   540,   540,   540,   540,
     540,   541,   543,   542,   544,   546,   545,   547,   547,   548,
     548,   548,   548,   548,   548,   548,   548,   548,   550,   549,
     551,   551,   551,   552,   554,   553,   555,   556,   557,   559,
     558,   560,   560,   561,   561,   561,   561,   561,   563,   562,
     565,   564,   567,   566,   568,   568,   569,   569,   569,   569,
     569,   569,   570,   572,   571,   573,   575,   574,   577,   576,
     579,   578,   580,   580,   581,   581,   581,   581,   581,   581,
     581,   581,   581,   581,   581,   581,   581,   581,   581,   581,
     581,   581,   582,   584,   583,   586,   585,   587,   589,   588,
     590,   591,   593,   592,   594,   594,   596,   595,   597,   598,
     600,   599,   602,   601,   604,   603,   606,   605,   608,   607,
     610,   609,   611,   611,   612,   612,   614,   613,   615,   617,
     616,   618,   618,   620,   619,   621,   621,   622,   622,   622,
     622,   622,   622,   622,   623,   625,   624,   627,   626,   628,
     628,   630,   629,   631,   631,   632,   632,   632,   632,   632,
     634,   633,   635,   636,   637,   639,   638
  };

  const signed char
  Dhcp6Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     0,     4,     0,     1,     1,
       3,     0,     4,     0,     1,     1,     3,     2,     0,     4,
       0,     6,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     3,     3,     0,
       4,     0,     4,     3,     3,     3,     0,     4,     3,     0,
       6,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     6,     0,     6,     0,     6,     0,
       1,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     3,     0,
       4,     0,     4,     0,     4,     0,     6,     1,     3,     1,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     0,
       6,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     3,     3,     3,     0,     4,     1,
       1,     1,     1,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     6,     0,     4,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     0,     4,     0,     4,     0,     4,
       1,     0,     4,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     0,     4,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     1,     0,     4,     0,     6,     1,     3,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     3,     0,     4,     3,     3,     3,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     3,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     0,     4,     1,     1,     0,     4,     3,     3,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     1,     0,     6,     3,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     3,     3,     3,     0,     4
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
  "\"reconnect-wait-time\"", "\"disable-dhcp-on-db-loss\"",
  "\"enable-connection-recovery\"", "\"keyspace\"", "\"consistency\"",
  "\"serial-consistency\"", "\"request-timeout\"", "\"tcp-keepalive\"",
  "\"tcp-nodelay\"", "\"max-row-errors\"", "\"preferred-lifetime\"",
  "\"min-preferred-lifetime\"", "\"max-preferred-lifetime\"",
  "\"valid-lifetime\"", "\"min-valid-lifetime\"", "\"max-valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"calculate-tee-times\"",
  "\"t1-percent\"", "\"t2-percent\"", "\"cache-threshold\"",
  "\"cache-max-age\"", "\"decline-probation-period\"", "\"server-tag\"",
  "\"statistic-default-sample-count\"", "\"statistic-default-sample-age\"",
  "\"ddns-send-updates\"", "\"ddns-override-no-update\"",
  "\"ddns-override-client-update\"", "\"ddns-replace-client-name\"",
  "\"ddns-generated-prefix\"", "\"ddns-qualifying-suffix\"",
  "\"ddns-update-on-renew\"", "\"ddns-use-conflict-resolution\"",
  "\"store-extended-info\"", "\"subnet6\"", "\"option-def\"",
  "\"option-data\"", "\"name\"", "\"data\"", "\"code\"", "\"space\"",
  "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"shared-networks\"", "\"pools\"",
  "\"pool\"", "\"pd-pools\"", "\"prefix\"", "\"prefix-len\"",
  "\"excluded-prefix\"", "\"excluded-prefix-len\"", "\"delegated-len\"",
  "\"user-context\"", "\"comment\"", "\"subnet\"", "\"interface\"",
  "\"interface-id\"", "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"",
  "\"disabled\"", "\"out-of-pool\"", "\"global\"", "\"all\"",
  "\"reservations-global\"", "\"reservations-in-subnet\"",
  "\"reservations-out-of-pool\"", "\"mac-sources\"",
  "\"relay-supplied-options\"", "\"host-reservation-identifiers\"",
  "\"sanity-checks\"", "\"lease-checks\"", "\"client-classes\"",
  "\"require-client-classes\"", "\"test\"", "\"only-if-required\"",
  "\"client-class\"", "\"reservations\"", "\"ip-addresses\"",
  "\"prefixes\"", "\"duid\"", "\"hw-address\"", "\"hostname\"",
  "\"flex-id\"", "\"relay\"", "\"ip-address\"", "\"hooks-libraries\"",
  "\"library\"", "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"", "\"server-id\"",
  "\"LLT\"", "\"EN\"", "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"",
  "\"enterprise-id\"", "\"dhcp4o6-port\"", "\"multi-threading\"",
  "\"enable-multi-threading\"", "\"thread-pool-size\"",
  "\"packet-queue-size\"", "\"control-socket\"", "\"socket-type\"",
  "\"socket-name\"", "\"dhcp-queue-control\"", "\"enable-queue\"",
  "\"queue-type\"", "\"capacity\"", "\"dhcp-ddns\"", "\"enable-updates\"",
  "\"qualifying-suffix\"", "\"server-ip\"", "\"server-port\"",
  "\"sender-ip\"", "\"sender-port\"", "\"max-queue-size\"",
  "\"ncr-protocol\"", "\"ncr-format\"", "\"override-no-update\"",
  "\"override-client-update\"", "\"replace-client-name\"",
  "\"generated-prefix\"", "\"UDP\"", "\"TCP\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"hostname-char-set\"", "\"hostname-char-replacement\"",
  "\"ip-reservations-unique\"", "\"loggers\"", "\"output_options\"",
  "\"output\"", "\"debuglevel\"", "\"severity\"", "\"flush\"",
  "\"maxsize\"", "\"maxver\"", "\"pattern\"", "TOPLEVEL_JSON",
  "TOPLEVEL_DHCP6", "SUB_DHCP6", "SUB_INTERFACES6", "SUB_SUBNET6",
  "SUB_POOL6", "SUB_PD_POOL", "SUB_RESERVATION", "SUB_OPTION_DEFS",
  "SUB_OPTION_DEF", "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY",
  "SUB_DHCP_DDNS", "SUB_CONFIG_CONTROL", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "$@11", "$@12", "$@13", "$@14", "value", "sub_json", "map2", "$@15",
  "map_value", "map_content", "not_empty_map", "list_generic", "$@16",
  "list_content", "not_empty_list", "list_strings", "$@17",
  "list_strings_content", "not_empty_list_strings", "unknown_map_entry",
  "syntax_map", "$@18", "global_object", "$@19", "sub_dhcp6", "$@20",
  "global_params", "global_param", "data_directory", "$@21",
  "preferred_lifetime", "min_preferred_lifetime", "max_preferred_lifetime",
  "valid_lifetime", "min_valid_lifetime", "max_valid_lifetime",
  "renew_timer", "rebind_timer", "calculate_tee_times", "t1_percent",
  "t2_percent", "cache_threshold", "cache_max_age",
  "decline_probation_period", "ddns_send_updates",
  "ddns_override_no_update", "ddns_override_client_update",
  "ddns_replace_client_name", "$@22", "ddns_replace_client_name_value",
  "ddns_generated_prefix", "$@23", "ddns_qualifying_suffix", "$@24",
  "ddns_update_on_renew", "ddns_use_conflict_resolution",
  "hostname_char_set", "$@25", "hostname_char_replacement", "$@26",
  "store_extended_info", "statistic_default_sample_count",
  "statistic_default_sample_age", "server_tag", "$@27",
  "ip_reservations_unique", "interfaces_config", "$@28", "sub_interfaces6",
  "$@29", "interfaces_config_params", "interfaces_config_param",
  "interfaces_list", "$@30", "re_detect", "lease_database", "$@31",
  "hosts_database", "$@32", "hosts_databases", "$@33", "database_list",
  "not_empty_database_list", "database", "$@34", "database_map_params",
  "database_map_param", "database_type", "$@35", "db_type", "user", "$@36",
  "password", "$@37", "host", "$@38", "port", "name", "$@39", "persist",
  "lfc_interval", "readonly", "connect_timeout", "reconnect_wait_time",
  "disable_dhcp_on_db_loss", "enable_connection_recovery",
  "max_row_errors", "request_timeout", "tcp_keepalive", "tcp_nodelay",
  "contact_points", "$@40", "max_reconnect_tries", "keyspace", "$@41",
  "consistency", "$@42", "serial_consistency", "$@43", "sanity_checks",
  "$@44", "sanity_checks_params", "sanity_checks_param", "lease_checks",
  "$@45", "mac_sources", "$@46", "mac_sources_list", "mac_sources_value",
  "duid_id", "string_id", "host_reservation_identifiers", "$@47",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@48",
  "dhcp_multi_threading", "$@49", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@50", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@51",
  "sub_hooks_library", "$@52", "hooks_params", "hooks_param", "library",
  "$@53", "parameters", "$@54", "expired_leases_processing", "$@55",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@56",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@57",
  "sub_subnet6", "$@58", "subnet6_params", "subnet6_param", "subnet",
  "$@59", "interface", "$@60", "interface_id", "$@61", "client_class",
  "$@62", "require_client_classes", "$@63", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "reservation_mode",
  "$@64", "hr_mode", "id", "rapid_commit", "shared_networks", "$@65",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@66", "shared_network_params", "shared_network_param",
  "option_def_list", "$@67", "sub_option_def_list", "$@68",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@69", "sub_option_def", "$@70",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@71",
  "option_def_record_types", "$@72", "space", "$@73", "option_def_space",
  "option_def_encapsulate", "$@74", "option_def_array", "option_data_list",
  "$@75", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@76", "sub_option_data", "$@77",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@78",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@79", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@80", "sub_pool6", "$@81",
  "pool_params", "pool_param", "pool_entry", "$@82", "user_context",
  "$@83", "comment", "$@84", "pd_pools_list", "$@85",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@86", "sub_pd_pool", "$@87", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@88", "pd_prefix_len", "excluded_prefix", "$@89",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@90",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@91", "sub_reservation", "$@92", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@93", "prefixes", "$@94", "duid", "$@95", "hw_address", "$@96",
  "hostname", "$@97", "flex_id_value", "$@98",
  "reservation_client_classes", "$@99", "relay", "$@100", "relay_map",
  "ip_address", "$@101", "client_classes", "$@102", "client_classes_list",
  "client_class_entry", "$@103", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@104", "only_if_required",
  "server_id", "$@105", "server_id_params", "server_id_param",
  "server_id_type", "$@106", "duid_type", "htype", "identifier", "$@107",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@108",
  "control_socket_params", "control_socket_param", "socket_type", "$@109",
  "socket_name", "$@110", "dhcp_queue_control", "$@111",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@112", "capacity", "arbitrary_map_entry", "$@113",
  "dhcp_ddns", "$@114", "sub_dhcp_ddns", "$@115", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "dep_qualifying_suffix", "$@116",
  "server_ip", "$@117", "server_port", "sender_ip", "$@118", "sender_port",
  "max_queue_size", "ncr_protocol", "$@119", "ncr_protocol_value",
  "ncr_format", "$@120", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@121",
  "dep_generated_prefix", "$@122", "dep_hostname_char_set", "$@123",
  "dep_hostname_char_replacement", "$@124", "config_control", "$@125",
  "sub_config_control", "$@126", "config_control_params",
  "config_control_param", "config_databases", "$@127",
  "config_fetch_wait_time", "loggers", "$@128", "loggers_entries",
  "logger_entry", "$@129", "logger_params", "logger_param", "debuglevel",
  "severity", "$@130", "output_options_list", "$@131",
  "output_options_list_content", "output_entry", "$@132",
  "output_params_list", "output_params", "output", "$@133", "flush",
  "maxsize", "maxver", "pattern", "$@134", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const short
  Dhcp6Parser::yyrline_[] =
  {
       0,   294,   294,   294,   295,   295,   296,   296,   297,   297,
     298,   298,   299,   299,   300,   300,   301,   301,   302,   302,
     303,   303,   304,   304,   305,   305,   306,   306,   307,   307,
     315,   316,   317,   318,   319,   320,   321,   324,   329,   329,
     340,   343,   344,   347,   352,   360,   360,   367,   368,   371,
     375,   382,   382,   389,   390,   393,   397,   408,   417,   417,
     432,   432,   449,   449,   458,   459,   464,   465,   466,   467,
     468,   469,   470,   471,   472,   473,   474,   475,   476,   477,
     478,   479,   480,   481,   482,   483,   484,   485,   486,   487,
     488,   489,   490,   491,   492,   493,   494,   495,   496,   497,
     498,   499,   500,   501,   502,   503,   504,   505,   506,   507,
     508,   509,   510,   511,   512,   513,   514,   515,   516,   517,
     518,   519,   520,   521,   522,   523,   524,   527,   527,   536,
     542,   548,   554,   560,   566,   572,   578,   584,   590,   596,
     602,   608,   614,   620,   626,   632,   638,   638,   647,   650,
     653,   656,   659,   665,   665,   674,   674,   683,   689,   695,
     695,   704,   704,   713,   719,   725,   731,   731,   740,   746,
     746,   758,   758,   767,   768,   771,   772,   773,   774,   775,
     778,   778,   789,   795,   795,   808,   808,   821,   821,   832,
     833,   836,   837,   840,   840,   850,   851,   854,   855,   856,
     857,   858,   859,   860,   861,   862,   863,   864,   865,   866,
     867,   868,   869,   870,   871,   872,   873,   874,   875,   876,
     879,   879,   887,   888,   889,   890,   893,   893,   902,   902,
     911,   911,   920,   926,   926,   935,   941,   947,   953,   959,
     965,   971,   977,   983,   989,   995,  1001,  1001,  1010,  1016,
    1016,  1025,  1025,  1034,  1034,  1043,  1043,  1054,  1055,  1057,
    1059,  1059,  1078,  1078,  1089,  1090,  1093,  1094,  1097,  1102,
    1107,  1107,  1118,  1119,  1122,  1123,  1124,  1127,  1132,  1139,
    1139,  1152,  1152,  1165,  1166,  1169,  1170,  1171,  1172,  1173,
    1174,  1177,  1183,  1189,  1195,  1195,  1206,  1207,  1210,  1211,
    1214,  1214,  1224,  1224,  1234,  1235,  1236,  1239,  1240,  1243,
    1243,  1252,  1252,  1261,  1261,  1273,  1274,  1277,  1278,  1279,
    1280,  1281,  1282,  1285,  1291,  1297,  1303,  1309,  1315,  1324,
    1324,  1338,  1339,  1342,  1343,  1350,  1350,  1376,  1376,  1387,
    1388,  1392,  1393,  1394,  1395,  1396,  1397,  1398,  1399,  1400,
    1401,  1402,  1403,  1404,  1405,  1406,  1407,  1408,  1409,  1410,
    1411,  1412,  1413,  1414,  1415,  1416,  1417,  1418,  1419,  1420,
    1421,  1422,  1423,  1424,  1425,  1426,  1427,  1428,  1429,  1430,
    1431,  1432,  1433,  1434,  1437,  1437,  1446,  1446,  1455,  1455,
    1464,  1464,  1473,  1473,  1484,  1490,  1496,  1502,  1502,  1510,
    1511,  1512,  1513,  1516,  1522,  1530,  1530,  1542,  1543,  1547,
    1548,  1551,  1551,  1559,  1560,  1563,  1564,  1565,  1566,  1567,
    1568,  1569,  1570,  1571,  1572,  1573,  1574,  1575,  1576,  1577,
    1578,  1579,  1580,  1581,  1582,  1583,  1584,  1585,  1586,  1587,
    1588,  1589,  1590,  1591,  1592,  1593,  1594,  1595,  1596,  1597,
    1598,  1599,  1600,  1601,  1602,  1609,  1609,  1623,  1623,  1632,
    1633,  1636,  1637,  1642,  1642,  1657,  1657,  1671,  1672,  1675,
    1676,  1679,  1680,  1681,  1682,  1683,  1684,  1685,  1686,  1687,
    1688,  1691,  1693,  1699,  1701,  1701,  1710,  1710,  1719,  1719,
    1728,  1730,  1730,  1739,  1749,  1749,  1762,  1763,  1768,  1769,
    1774,  1774,  1786,  1786,  1798,  1799,  1804,  1805,  1810,  1811,
    1812,  1813,  1814,  1815,  1816,  1817,  1818,  1821,  1823,  1823,
    1832,  1834,  1836,  1842,  1851,  1851,  1864,  1865,  1868,  1869,
    1872,  1872,  1882,  1882,  1892,  1893,  1896,  1897,  1898,  1899,
    1900,  1901,  1902,  1905,  1905,  1914,  1914,  1939,  1939,  1969,
    1969,  1982,  1983,  1986,  1987,  1990,  1990,  2002,  2002,  2014,
    2015,  2018,  2019,  2020,  2021,  2022,  2023,  2024,  2025,  2026,
    2027,  2028,  2031,  2031,  2040,  2046,  2046,  2055,  2061,  2070,
    2070,  2081,  2082,  2085,  2086,  2089,  2089,  2098,  2098,  2107,
    2108,  2111,  2112,  2116,  2117,  2118,  2119,  2120,  2121,  2122,
    2123,  2124,  2125,  2126,  2129,  2129,  2140,  2140,  2151,  2151,
    2160,  2160,  2169,  2169,  2178,  2178,  2187,  2187,  2201,  2201,
    2212,  2213,  2216,  2216,  2228,  2228,  2239,  2240,  2243,  2243,
    2253,  2254,  2257,  2258,  2261,  2262,  2263,  2264,  2265,  2266,
    2267,  2270,  2272,  2272,  2281,  2290,  2290,  2303,  2304,  2307,
    2308,  2309,  2310,  2311,  2312,  2313,  2314,  2315,  2318,  2318,
    2326,  2327,  2328,  2331,  2337,  2337,  2346,  2352,  2360,  2368,
    2368,  2379,  2380,  2383,  2384,  2385,  2386,  2387,  2390,  2390,
    2399,  2399,  2411,  2411,  2424,  2425,  2428,  2429,  2430,  2431,
    2432,  2433,  2436,  2442,  2442,  2451,  2457,  2457,  2467,  2467,
    2480,  2480,  2490,  2491,  2494,  2495,  2496,  2497,  2498,  2499,
    2500,  2501,  2502,  2503,  2504,  2505,  2506,  2507,  2508,  2509,
    2510,  2511,  2514,  2521,  2521,  2530,  2530,  2539,  2545,  2545,
    2554,  2560,  2566,  2566,  2575,  2576,  2579,  2579,  2589,  2596,
    2603,  2603,  2612,  2612,  2622,  2622,  2632,  2632,  2644,  2644,
    2656,  2656,  2666,  2667,  2671,  2672,  2675,  2675,  2686,  2694,
    2694,  2707,  2708,  2712,  2712,  2720,  2721,  2724,  2725,  2726,
    2727,  2728,  2729,  2730,  2733,  2739,  2739,  2748,  2748,  2759,
    2760,  2763,  2763,  2771,  2772,  2775,  2776,  2777,  2778,  2779,
    2782,  2782,  2791,  2797,  2803,  2809,  2809
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
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Dhcp6Parser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
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


#line 14 "dhcp6_parser.yy"
} } // isc::dhcp
#line 5840 "dhcp6_parser.cc"

#line 2818 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
