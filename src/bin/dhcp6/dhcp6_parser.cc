// A Bison parser, made by GNU Bison 3.5.4.

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
      case 220: // value
      case 224: // map_value
      case 265: // ddns_replace_client_name_value
      case 302: // db_type
      case 403: // hr_mode
      case 539: // duid_type
      case 582: // ncr_protocol_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 202: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 201: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 200: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 199: // "constant string"
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
      case 220: // value
      case 224: // map_value
      case 265: // ddns_replace_client_name_value
      case 302: // db_type
      case 403: // hr_mode
      case 539: // duid_type
      case 582: // ncr_protocol_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 202: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 201: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 200: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 199: // "constant string"
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
      case 220: // value
      case 224: // map_value
      case 265: // ddns_replace_client_name_value
      case 302: // db_type
      case 403: // hr_mode
      case 539: // duid_type
      case 582: // ncr_protocol_value
        value.copy< ElementPtr > (that.value);
        break;

      case 202: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 201: // "floating point"
        value.copy< double > (that.value);
        break;

      case 200: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 199: // "constant string"
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
      case 220: // value
      case 224: // map_value
      case 265: // ddns_replace_client_name_value
      case 302: // db_type
      case 403: // hr_mode
      case 539: // duid_type
      case 582: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 202: // "boolean"
        value.move< bool > (that.value);
        break;

      case 201: // "floating point"
        value.move< double > (that.value);
        break;

      case 200: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 199: // "constant string"
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
      case 199: // "constant string"
#line 280 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 443 "dhcp6_parser.cc"
        break;

      case 200: // "integer"
#line 280 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 449 "dhcp6_parser.cc"
        break;

      case 201: // "floating point"
#line 280 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 455 "dhcp6_parser.cc"
        break;

      case 202: // "boolean"
#line 280 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 461 "dhcp6_parser.cc"
        break;

      case 220: // value
#line 280 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 467 "dhcp6_parser.cc"
        break;

      case 224: // map_value
#line 280 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 473 "dhcp6_parser.cc"
        break;

      case 265: // ddns_replace_client_name_value
#line 280 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 479 "dhcp6_parser.cc"
        break;

      case 302: // db_type
#line 280 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 485 "dhcp6_parser.cc"
        break;

      case 403: // hr_mode
#line 280 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 491 "dhcp6_parser.cc"
        break;

      case 539: // duid_type
#line 280 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 497 "dhcp6_parser.cc"
        break;

      case 582: // ncr_protocol_value
#line 280 "dhcp6_parser.yy"
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
      case 220: // value
      case 224: // map_value
      case 265: // ddns_replace_client_name_value
      case 302: // db_type
      case 403: // hr_mode
      case 539: // duid_type
      case 582: // ncr_protocol_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 202: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 201: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 200: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 199: // "constant string"
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
#line 289 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 770 "dhcp6_parser.cc"
    break;

  case 4:
#line 290 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 776 "dhcp6_parser.cc"
    break;

  case 6:
#line 291 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 782 "dhcp6_parser.cc"
    break;

  case 8:
#line 292 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 788 "dhcp6_parser.cc"
    break;

  case 10:
#line 293 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 794 "dhcp6_parser.cc"
    break;

  case 12:
#line 294 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 800 "dhcp6_parser.cc"
    break;

  case 14:
#line 295 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 806 "dhcp6_parser.cc"
    break;

  case 16:
#line 296 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 812 "dhcp6_parser.cc"
    break;

  case 18:
#line 297 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 818 "dhcp6_parser.cc"
    break;

  case 20:
#line 298 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 824 "dhcp6_parser.cc"
    break;

  case 22:
#line 299 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 830 "dhcp6_parser.cc"
    break;

  case 24:
#line 300 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 836 "dhcp6_parser.cc"
    break;

  case 26:
#line 301 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 842 "dhcp6_parser.cc"
    break;

  case 28:
#line 302 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.LOGGING; }
#line 848 "dhcp6_parser.cc"
    break;

  case 30:
#line 303 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 854 "dhcp6_parser.cc"
    break;

  case 32:
#line 311 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 860 "dhcp6_parser.cc"
    break;

  case 33:
#line 312 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 866 "dhcp6_parser.cc"
    break;

  case 34:
#line 313 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 872 "dhcp6_parser.cc"
    break;

  case 35:
#line 314 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 878 "dhcp6_parser.cc"
    break;

  case 36:
#line 315 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 884 "dhcp6_parser.cc"
    break;

  case 37:
#line 316 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 890 "dhcp6_parser.cc"
    break;

  case 38:
#line 317 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 896 "dhcp6_parser.cc"
    break;

  case 39:
#line 320 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 905 "dhcp6_parser.cc"
    break;

  case 40:
#line 325 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 916 "dhcp6_parser.cc"
    break;

  case 41:
#line 330 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 926 "dhcp6_parser.cc"
    break;

  case 42:
#line 336 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 932 "dhcp6_parser.cc"
    break;

  case 45:
#line 343 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 941 "dhcp6_parser.cc"
    break;

  case 46:
#line 347 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 951 "dhcp6_parser.cc"
    break;

  case 47:
#line 354 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 960 "dhcp6_parser.cc"
    break;

  case 48:
#line 357 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 968 "dhcp6_parser.cc"
    break;

  case 51:
#line 365 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 977 "dhcp6_parser.cc"
    break;

  case 52:
#line 369 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 986 "dhcp6_parser.cc"
    break;

  case 53:
#line 376 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 994 "dhcp6_parser.cc"
    break;

  case 54:
#line 378 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1003 "dhcp6_parser.cc"
    break;

  case 57:
#line 387 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1012 "dhcp6_parser.cc"
    break;

  case 58:
#line 391 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1021 "dhcp6_parser.cc"
    break;

  case 59:
#line 402 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1032 "dhcp6_parser.cc"
    break;

  case 60:
#line 412 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1043 "dhcp6_parser.cc"
    break;

  case 61:
#line 417 "dhcp6_parser.yy"
                                {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1056 "dhcp6_parser.cc"
    break;

  case 70:
#line 441 "dhcp6_parser.yy"
                    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 1069 "dhcp6_parser.cc"
    break;

  case 71:
#line 448 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1079 "dhcp6_parser.cc"
    break;

  case 72:
#line 456 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1089 "dhcp6_parser.cc"
    break;

  case 73:
#line 460 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1098 "dhcp6_parser.cc"
    break;

  case 129:
#line 526 "dhcp6_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1106 "dhcp6_parser.cc"
    break;

  case 130:
#line 528 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1116 "dhcp6_parser.cc"
    break;

  case 131:
#line 534 "dhcp6_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1125 "dhcp6_parser.cc"
    break;

  case 132:
#line 539 "dhcp6_parser.yy"
                                                             {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1134 "dhcp6_parser.cc"
    break;

  case 133:
#line 544 "dhcp6_parser.yy"
                                                             {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1143 "dhcp6_parser.cc"
    break;

  case 134:
#line 549 "dhcp6_parser.yy"
                                             {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1152 "dhcp6_parser.cc"
    break;

  case 135:
#line 554 "dhcp6_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1161 "dhcp6_parser.cc"
    break;

  case 136:
#line 559 "dhcp6_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1170 "dhcp6_parser.cc"
    break;

  case 137:
#line 564 "dhcp6_parser.yy"
                                       {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1179 "dhcp6_parser.cc"
    break;

  case 138:
#line 569 "dhcp6_parser.yy"
                                         {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1188 "dhcp6_parser.cc"
    break;

  case 139:
#line 574 "dhcp6_parser.yy"
                                                       {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1197 "dhcp6_parser.cc"
    break;

  case 140:
#line 579 "dhcp6_parser.yy"
                                   {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1206 "dhcp6_parser.cc"
    break;

  case 141:
#line 584 "dhcp6_parser.yy"
                                   {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1215 "dhcp6_parser.cc"
    break;

  case 142:
#line 589 "dhcp6_parser.yy"
                                                                 {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1224 "dhcp6_parser.cc"
    break;

  case 143:
#line 594 "dhcp6_parser.yy"
                                                   {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1233 "dhcp6_parser.cc"
    break;

  case 144:
#line 599 "dhcp6_parser.yy"
                                                               {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1242 "dhcp6_parser.cc"
    break;

  case 145:
#line 604 "dhcp6_parser.yy"
                                                                       {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1251 "dhcp6_parser.cc"
    break;

  case 146:
#line 609 "dhcp6_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1259 "dhcp6_parser.cc"
    break;

  case 147:
#line 611 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1268 "dhcp6_parser.cc"
    break;

  case 148:
#line 617 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1276 "dhcp6_parser.cc"
    break;

  case 149:
#line 620 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1284 "dhcp6_parser.cc"
    break;

  case 150:
#line 623 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1292 "dhcp6_parser.cc"
    break;

  case 151:
#line 626 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1300 "dhcp6_parser.cc"
    break;

  case 152:
#line 629 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1309 "dhcp6_parser.cc"
    break;

  case 153:
#line 635 "dhcp6_parser.yy"
                                             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1317 "dhcp6_parser.cc"
    break;

  case 154:
#line 637 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1327 "dhcp6_parser.cc"
    break;

  case 155:
#line 643 "dhcp6_parser.yy"
                                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1335 "dhcp6_parser.cc"
    break;

  case 156:
#line 645 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1345 "dhcp6_parser.cc"
    break;

  case 157:
#line 651 "dhcp6_parser.yy"
                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1353 "dhcp6_parser.cc"
    break;

  case 158:
#line 653 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1363 "dhcp6_parser.cc"
    break;

  case 159:
#line 659 "dhcp6_parser.yy"
                                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1371 "dhcp6_parser.cc"
    break;

  case 160:
#line 661 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1381 "dhcp6_parser.cc"
    break;

  case 161:
#line 667 "dhcp6_parser.yy"
                                                       {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1390 "dhcp6_parser.cc"
    break;

  case 162:
#line 672 "dhcp6_parser.yy"
                                                                             {
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1399 "dhcp6_parser.cc"
    break;

  case 163:
#line 677 "dhcp6_parser.yy"
                                                                         {
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1408 "dhcp6_parser.cc"
    break;

  case 164:
#line 682 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1416 "dhcp6_parser.cc"
    break;

  case 165:
#line 684 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1426 "dhcp6_parser.cc"
    break;

  case 166:
#line 690 "dhcp6_parser.yy"
                                     {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1437 "dhcp6_parser.cc"
    break;

  case 167:
#line 695 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1447 "dhcp6_parser.cc"
    break;

  case 168:
#line 701 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1457 "dhcp6_parser.cc"
    break;

  case 169:
#line 705 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1466 "dhcp6_parser.cc"
    break;

  case 177:
#line 721 "dhcp6_parser.yy"
                            {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1477 "dhcp6_parser.cc"
    break;

  case 178:
#line 726 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1486 "dhcp6_parser.cc"
    break;

  case 179:
#line 731 "dhcp6_parser.yy"
                                   {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1495 "dhcp6_parser.cc"
    break;

  case 180:
#line 736 "dhcp6_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1506 "dhcp6_parser.cc"
    break;

  case 181:
#line 741 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1517 "dhcp6_parser.cc"
    break;

  case 182:
#line 748 "dhcp6_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1528 "dhcp6_parser.cc"
    break;

  case 183:
#line 753 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1539 "dhcp6_parser.cc"
    break;

  case 184:
#line 760 "dhcp6_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1550 "dhcp6_parser.cc"
    break;

  case 185:
#line 765 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1559 "dhcp6_parser.cc"
    break;

  case 190:
#line 778 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1569 "dhcp6_parser.cc"
    break;

  case 191:
#line 782 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1579 "dhcp6_parser.cc"
    break;

  case 215:
#line 815 "dhcp6_parser.yy"
                    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1587 "dhcp6_parser.cc"
    break;

  case 216:
#line 817 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1596 "dhcp6_parser.cc"
    break;

  case 217:
#line 822 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1602 "dhcp6_parser.cc"
    break;

  case 218:
#line 823 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1608 "dhcp6_parser.cc"
    break;

  case 219:
#line 824 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1614 "dhcp6_parser.cc"
    break;

  case 220:
#line 825 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1620 "dhcp6_parser.cc"
    break;

  case 221:
#line 828 "dhcp6_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1628 "dhcp6_parser.cc"
    break;

  case 222:
#line 830 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1638 "dhcp6_parser.cc"
    break;

  case 223:
#line 836 "dhcp6_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1646 "dhcp6_parser.cc"
    break;

  case 224:
#line 838 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1656 "dhcp6_parser.cc"
    break;

  case 225:
#line 844 "dhcp6_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1664 "dhcp6_parser.cc"
    break;

  case 226:
#line 846 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1674 "dhcp6_parser.cc"
    break;

  case 227:
#line 852 "dhcp6_parser.yy"
                         {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1683 "dhcp6_parser.cc"
    break;

  case 228:
#line 857 "dhcp6_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1691 "dhcp6_parser.cc"
    break;

  case 229:
#line 859 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1701 "dhcp6_parser.cc"
    break;

  case 230:
#line 865 "dhcp6_parser.yy"
                               {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1710 "dhcp6_parser.cc"
    break;

  case 231:
#line 870 "dhcp6_parser.yy"
                                         {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1719 "dhcp6_parser.cc"
    break;

  case 232:
#line 875 "dhcp6_parser.yy"
                                 {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1728 "dhcp6_parser.cc"
    break;

  case 233:
#line 880 "dhcp6_parser.yy"
                                               {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1737 "dhcp6_parser.cc"
    break;

  case 234:
#line 885 "dhcp6_parser.yy"
                                                       {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1746 "dhcp6_parser.cc"
    break;

  case 235:
#line 890 "dhcp6_parser.yy"
                                             {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1755 "dhcp6_parser.cc"
    break;

  case 236:
#line 895 "dhcp6_parser.yy"
                                               {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1764 "dhcp6_parser.cc"
    break;

  case 237:
#line 900 "dhcp6_parser.yy"
                                           {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1773 "dhcp6_parser.cc"
    break;

  case 238:
#line 905 "dhcp6_parser.yy"
                                       {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1782 "dhcp6_parser.cc"
    break;

  case 239:
#line 910 "dhcp6_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1790 "dhcp6_parser.cc"
    break;

  case 240:
#line 912 "dhcp6_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1800 "dhcp6_parser.cc"
    break;

  case 241:
#line 918 "dhcp6_parser.yy"
                                                       {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1809 "dhcp6_parser.cc"
    break;

  case 242:
#line 923 "dhcp6_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1817 "dhcp6_parser.cc"
    break;

  case 243:
#line 925 "dhcp6_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1827 "dhcp6_parser.cc"
    break;

  case 244:
#line 931 "dhcp6_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1835 "dhcp6_parser.cc"
    break;

  case 245:
#line 933 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1845 "dhcp6_parser.cc"
    break;

  case 246:
#line 939 "dhcp6_parser.yy"
                                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1853 "dhcp6_parser.cc"
    break;

  case 247:
#line 941 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1863 "dhcp6_parser.cc"
    break;

  case 248:
#line 947 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1874 "dhcp6_parser.cc"
    break;

  case 249:
#line 952 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1883 "dhcp6_parser.cc"
    break;

  case 253:
#line 962 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1891 "dhcp6_parser.cc"
    break;

  case 254:
#line 964 "dhcp6_parser.yy"
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
#line 1911 "dhcp6_parser.cc"
    break;

  case 255:
#line 980 "dhcp6_parser.yy"
                         {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1922 "dhcp6_parser.cc"
    break;

  case 256:
#line 985 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1931 "dhcp6_parser.cc"
    break;

  case 261:
#line 998 "dhcp6_parser.yy"
               {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1940 "dhcp6_parser.cc"
    break;

  case 262:
#line 1003 "dhcp6_parser.yy"
                   {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1949 "dhcp6_parser.cc"
    break;

  case 263:
#line 1008 "dhcp6_parser.yy"
                                                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1960 "dhcp6_parser.cc"
    break;

  case 264:
#line 1013 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1969 "dhcp6_parser.cc"
    break;

  case 270:
#line 1027 "dhcp6_parser.yy"
                           {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1978 "dhcp6_parser.cc"
    break;

  case 271:
#line 1032 "dhcp6_parser.yy"
                  {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1987 "dhcp6_parser.cc"
    break;

  case 272:
#line 1039 "dhcp6_parser.yy"
                                               {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1998 "dhcp6_parser.cc"
    break;

  case 273:
#line 1044 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2007 "dhcp6_parser.cc"
    break;

  case 274:
#line 1051 "dhcp6_parser.yy"
                                           {
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2018 "dhcp6_parser.cc"
    break;

  case 275:
#line 1056 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2029 "dhcp6_parser.cc"
    break;

  case 284:
#line 1075 "dhcp6_parser.yy"
                                                             {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2038 "dhcp6_parser.cc"
    break;

  case 285:
#line 1080 "dhcp6_parser.yy"
                                                 {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2047 "dhcp6_parser.cc"
    break;

  case 286:
#line 1085 "dhcp6_parser.yy"
                                                   {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2056 "dhcp6_parser.cc"
    break;

  case 287:
#line 1090 "dhcp6_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2067 "dhcp6_parser.cc"
    break;

  case 288:
#line 1095 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2076 "dhcp6_parser.cc"
    break;

  case 293:
#line 1108 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2086 "dhcp6_parser.cc"
    break;

  case 294:
#line 1112 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2096 "dhcp6_parser.cc"
    break;

  case 295:
#line 1118 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2106 "dhcp6_parser.cc"
    break;

  case 296:
#line 1122 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2116 "dhcp6_parser.cc"
    break;

  case 302:
#line 1137 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2124 "dhcp6_parser.cc"
    break;

  case 303:
#line 1139 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2134 "dhcp6_parser.cc"
    break;

  case 304:
#line 1145 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2142 "dhcp6_parser.cc"
    break;

  case 305:
#line 1147 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2151 "dhcp6_parser.cc"
    break;

  case 306:
#line 1153 "dhcp6_parser.yy"
                                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2162 "dhcp6_parser.cc"
    break;

  case 307:
#line 1158 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2172 "dhcp6_parser.cc"
    break;

  case 316:
#line 1176 "dhcp6_parser.yy"
                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2181 "dhcp6_parser.cc"
    break;

  case 317:
#line 1181 "dhcp6_parser.yy"
                                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2190 "dhcp6_parser.cc"
    break;

  case 318:
#line 1186 "dhcp6_parser.yy"
                                                       {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2199 "dhcp6_parser.cc"
    break;

  case 319:
#line 1191 "dhcp6_parser.yy"
                                                     {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2208 "dhcp6_parser.cc"
    break;

  case 320:
#line 1196 "dhcp6_parser.yy"
                                                 {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2217 "dhcp6_parser.cc"
    break;

  case 321:
#line 1201 "dhcp6_parser.yy"
                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2226 "dhcp6_parser.cc"
    break;

  case 322:
#line 1209 "dhcp6_parser.yy"
                      {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2237 "dhcp6_parser.cc"
    break;

  case 323:
#line 1214 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2246 "dhcp6_parser.cc"
    break;

  case 328:
#line 1234 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2256 "dhcp6_parser.cc"
    break;

  case 329:
#line 1238 "dhcp6_parser.yy"
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
#line 2282 "dhcp6_parser.cc"
    break;

  case 330:
#line 1260 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2292 "dhcp6_parser.cc"
    break;

  case 331:
#line 1264 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2302 "dhcp6_parser.cc"
    break;

  case 370:
#line 1314 "dhcp6_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2310 "dhcp6_parser.cc"
    break;

  case 371:
#line 1316 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2320 "dhcp6_parser.cc"
    break;

  case 372:
#line 1322 "dhcp6_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2328 "dhcp6_parser.cc"
    break;

  case 373:
#line 1324 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2338 "dhcp6_parser.cc"
    break;

  case 374:
#line 1330 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2346 "dhcp6_parser.cc"
    break;

  case 375:
#line 1332 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2356 "dhcp6_parser.cc"
    break;

  case 376:
#line 1338 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2364 "dhcp6_parser.cc"
    break;

  case 377:
#line 1340 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2374 "dhcp6_parser.cc"
    break;

  case 378:
#line 1346 "dhcp6_parser.yy"
                                               {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2385 "dhcp6_parser.cc"
    break;

  case 379:
#line 1351 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2394 "dhcp6_parser.cc"
    break;

  case 380:
#line 1356 "dhcp6_parser.yy"
                                   {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2402 "dhcp6_parser.cc"
    break;

  case 381:
#line 1358 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2411 "dhcp6_parser.cc"
    break;

  case 382:
#line 1363 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2417 "dhcp6_parser.cc"
    break;

  case 383:
#line 1364 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2423 "dhcp6_parser.cc"
    break;

  case 384:
#line 1365 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2429 "dhcp6_parser.cc"
    break;

  case 385:
#line 1366 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2435 "dhcp6_parser.cc"
    break;

  case 386:
#line 1369 "dhcp6_parser.yy"
                     {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2444 "dhcp6_parser.cc"
    break;

  case 387:
#line 1374 "dhcp6_parser.yy"
                                         {
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2453 "dhcp6_parser.cc"
    break;

  case 388:
#line 1381 "dhcp6_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2464 "dhcp6_parser.cc"
    break;

  case 389:
#line 1386 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2473 "dhcp6_parser.cc"
    break;

  case 394:
#line 1401 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2483 "dhcp6_parser.cc"
    break;

  case 395:
#line 1405 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2491 "dhcp6_parser.cc"
    break;

  case 431:
#line 1452 "dhcp6_parser.yy"
                            {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2502 "dhcp6_parser.cc"
    break;

  case 432:
#line 1457 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2511 "dhcp6_parser.cc"
    break;

  case 433:
#line 1465 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2520 "dhcp6_parser.cc"
    break;

  case 434:
#line 1468 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2528 "dhcp6_parser.cc"
    break;

  case 439:
#line 1484 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2538 "dhcp6_parser.cc"
    break;

  case 440:
#line 1488 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2550 "dhcp6_parser.cc"
    break;

  case 441:
#line 1499 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2560 "dhcp6_parser.cc"
    break;

  case 442:
#line 1503 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2572 "dhcp6_parser.cc"
    break;

  case 458:
#line 1535 "dhcp6_parser.yy"
                         {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2581 "dhcp6_parser.cc"
    break;

  case 460:
#line 1542 "dhcp6_parser.yy"
                      {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2589 "dhcp6_parser.cc"
    break;

  case 461:
#line 1544 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2599 "dhcp6_parser.cc"
    break;

  case 462:
#line 1550 "dhcp6_parser.yy"
                                      {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2607 "dhcp6_parser.cc"
    break;

  case 463:
#line 1552 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2617 "dhcp6_parser.cc"
    break;

  case 464:
#line 1558 "dhcp6_parser.yy"
             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2625 "dhcp6_parser.cc"
    break;

  case 465:
#line 1560 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2635 "dhcp6_parser.cc"
    break;

  case 467:
#line 1568 "dhcp6_parser.yy"
                                    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2643 "dhcp6_parser.cc"
    break;

  case 468:
#line 1570 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2653 "dhcp6_parser.cc"
    break;

  case 469:
#line 1576 "dhcp6_parser.yy"
                                      {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2662 "dhcp6_parser.cc"
    break;

  case 470:
#line 1585 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2673 "dhcp6_parser.cc"
    break;

  case 471:
#line 1590 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2682 "dhcp6_parser.cc"
    break;

  case 476:
#line 1609 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2692 "dhcp6_parser.cc"
    break;

  case 477:
#line 1613 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2701 "dhcp6_parser.cc"
    break;

  case 478:
#line 1621 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2711 "dhcp6_parser.cc"
    break;

  case 479:
#line 1625 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2720 "dhcp6_parser.cc"
    break;

  case 494:
#line 1658 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2728 "dhcp6_parser.cc"
    break;

  case 495:
#line 1660 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2738 "dhcp6_parser.cc"
    break;

  case 498:
#line 1670 "dhcp6_parser.yy"
                                                 {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2747 "dhcp6_parser.cc"
    break;

  case 499:
#line 1675 "dhcp6_parser.yy"
                                                   {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2756 "dhcp6_parser.cc"
    break;

  case 500:
#line 1683 "dhcp6_parser.yy"
                  {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2767 "dhcp6_parser.cc"
    break;

  case 501:
#line 1688 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2776 "dhcp6_parser.cc"
    break;

  case 506:
#line 1703 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2786 "dhcp6_parser.cc"
    break;

  case 507:
#line 1707 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2796 "dhcp6_parser.cc"
    break;

  case 508:
#line 1713 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2806 "dhcp6_parser.cc"
    break;

  case 509:
#line 1717 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2816 "dhcp6_parser.cc"
    break;

  case 519:
#line 1736 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2824 "dhcp6_parser.cc"
    break;

  case 520:
#line 1738 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2834 "dhcp6_parser.cc"
    break;

  case 521:
#line 1744 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2842 "dhcp6_parser.cc"
    break;

  case 522:
#line 1746 "dhcp6_parser.yy"
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
#line 2869 "dhcp6_parser.cc"
    break;

  case 523:
#line 1769 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2877 "dhcp6_parser.cc"
    break;

  case 524:
#line 1771 "dhcp6_parser.yy"
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
#line 2906 "dhcp6_parser.cc"
    break;

  case 525:
#line 1799 "dhcp6_parser.yy"
                        {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2917 "dhcp6_parser.cc"
    break;

  case 526:
#line 1804 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2926 "dhcp6_parser.cc"
    break;

  case 531:
#line 1819 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2936 "dhcp6_parser.cc"
    break;

  case 532:
#line 1823 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2948 "dhcp6_parser.cc"
    break;

  case 533:
#line 1831 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2958 "dhcp6_parser.cc"
    break;

  case 534:
#line 1835 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2970 "dhcp6_parser.cc"
    break;

  case 548:
#line 1860 "dhcp6_parser.yy"
                  {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2978 "dhcp6_parser.cc"
    break;

  case 549:
#line 1862 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2988 "dhcp6_parser.cc"
    break;

  case 550:
#line 1868 "dhcp6_parser.yy"
                                        {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2997 "dhcp6_parser.cc"
    break;

  case 551:
#line 1873 "dhcp6_parser.yy"
                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3005 "dhcp6_parser.cc"
    break;

  case 552:
#line 1875 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3015 "dhcp6_parser.cc"
    break;

  case 553:
#line 1881 "dhcp6_parser.yy"
                                                       {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3024 "dhcp6_parser.cc"
    break;

  case 554:
#line 1886 "dhcp6_parser.yy"
                                              {
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3033 "dhcp6_parser.cc"
    break;

  case 555:
#line 1894 "dhcp6_parser.yy"
                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3044 "dhcp6_parser.cc"
    break;

  case 556:
#line 1899 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3053 "dhcp6_parser.cc"
    break;

  case 561:
#line 1912 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3063 "dhcp6_parser.cc"
    break;

  case 562:
#line 1916 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3072 "dhcp6_parser.cc"
    break;

  case 563:
#line 1921 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3082 "dhcp6_parser.cc"
    break;

  case 564:
#line 1925 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3091 "dhcp6_parser.cc"
    break;

  case 580:
#line 1952 "dhcp6_parser.yy"
                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3102 "dhcp6_parser.cc"
    break;

  case 581:
#line 1957 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3111 "dhcp6_parser.cc"
    break;

  case 582:
#line 1962 "dhcp6_parser.yy"
                   {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3122 "dhcp6_parser.cc"
    break;

  case 583:
#line 1967 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3131 "dhcp6_parser.cc"
    break;

  case 584:
#line 1972 "dhcp6_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3139 "dhcp6_parser.cc"
    break;

  case 585:
#line 1974 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3149 "dhcp6_parser.cc"
    break;

  case 586:
#line 1980 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3157 "dhcp6_parser.cc"
    break;

  case 587:
#line 1982 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3167 "dhcp6_parser.cc"
    break;

  case 588:
#line 1988 "dhcp6_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3175 "dhcp6_parser.cc"
    break;

  case 589:
#line 1990 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3185 "dhcp6_parser.cc"
    break;

  case 590:
#line 1996 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3193 "dhcp6_parser.cc"
    break;

  case 591:
#line 1998 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3203 "dhcp6_parser.cc"
    break;

  case 592:
#line 2004 "dhcp6_parser.yy"
                                           {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3214 "dhcp6_parser.cc"
    break;

  case 593:
#line 2009 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3223 "dhcp6_parser.cc"
    break;

  case 594:
#line 2017 "dhcp6_parser.yy"
             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3234 "dhcp6_parser.cc"
    break;

  case 595:
#line 2022 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3243 "dhcp6_parser.cc"
    break;

  case 598:
#line 2031 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3251 "dhcp6_parser.cc"
    break;

  case 599:
#line 2033 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3261 "dhcp6_parser.cc"
    break;

  case 600:
#line 2042 "dhcp6_parser.yy"
                               {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3272 "dhcp6_parser.cc"
    break;

  case 601:
#line 2047 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3281 "dhcp6_parser.cc"
    break;

  case 604:
#line 2056 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3291 "dhcp6_parser.cc"
    break;

  case 605:
#line 2060 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3301 "dhcp6_parser.cc"
    break;

  case 618:
#line 2085 "dhcp6_parser.yy"
                        {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3309 "dhcp6_parser.cc"
    break;

  case 619:
#line 2087 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3319 "dhcp6_parser.cc"
    break;

  case 620:
#line 2093 "dhcp6_parser.yy"
                                                 {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3328 "dhcp6_parser.cc"
    break;

  case 621:
#line 2101 "dhcp6_parser.yy"
                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3339 "dhcp6_parser.cc"
    break;

  case 622:
#line 2106 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3350 "dhcp6_parser.cc"
    break;

  case 634:
#line 2128 "dhcp6_parser.yy"
                     {
    ctx.enter(ctx.DUID_TYPE);
}
#line 3358 "dhcp6_parser.cc"
    break;

  case 635:
#line 2130 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3367 "dhcp6_parser.cc"
    break;

  case 636:
#line 2135 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3373 "dhcp6_parser.cc"
    break;

  case 637:
#line 2136 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3379 "dhcp6_parser.cc"
    break;

  case 638:
#line 2137 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3385 "dhcp6_parser.cc"
    break;

  case 639:
#line 2140 "dhcp6_parser.yy"
                           {
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3394 "dhcp6_parser.cc"
    break;

  case 640:
#line 2145 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3402 "dhcp6_parser.cc"
    break;

  case 641:
#line 2147 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3412 "dhcp6_parser.cc"
    break;

  case 642:
#line 2153 "dhcp6_parser.yy"
                         {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3421 "dhcp6_parser.cc"
    break;

  case 643:
#line 2158 "dhcp6_parser.yy"
                                           {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3430 "dhcp6_parser.cc"
    break;

  case 644:
#line 2165 "dhcp6_parser.yy"
                                         {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3439 "dhcp6_parser.cc"
    break;

  case 645:
#line 2172 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3450 "dhcp6_parser.cc"
    break;

  case 646:
#line 2177 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3459 "dhcp6_parser.cc"
    break;

  case 654:
#line 2193 "dhcp6_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3467 "dhcp6_parser.cc"
    break;

  case 655:
#line 2195 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3477 "dhcp6_parser.cc"
    break;

  case 656:
#line 2201 "dhcp6_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3485 "dhcp6_parser.cc"
    break;

  case 657:
#line 2203 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3495 "dhcp6_parser.cc"
    break;

  case 658:
#line 2212 "dhcp6_parser.yy"
                                       {
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3506 "dhcp6_parser.cc"
    break;

  case 659:
#line 2217 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3517 "dhcp6_parser.cc"
    break;

  case 668:
#line 2236 "dhcp6_parser.yy"
                                         {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3526 "dhcp6_parser.cc"
    break;

  case 669:
#line 2241 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3534 "dhcp6_parser.cc"
    break;

  case 670:
#line 2243 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3544 "dhcp6_parser.cc"
    break;

  case 671:
#line 2249 "dhcp6_parser.yy"
                                 {
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3553 "dhcp6_parser.cc"
    break;

  case 672:
#line 2254 "dhcp6_parser.yy"
                            {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3561 "dhcp6_parser.cc"
    break;

  case 673:
#line 2256 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3570 "dhcp6_parser.cc"
    break;

  case 674:
#line 2263 "dhcp6_parser.yy"
                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3581 "dhcp6_parser.cc"
    break;

  case 675:
#line 2268 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3592 "dhcp6_parser.cc"
    break;

  case 676:
#line 2275 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3602 "dhcp6_parser.cc"
    break;

  case 677:
#line 2279 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3612 "dhcp6_parser.cc"
    break;

  case 698:
#line 2309 "dhcp6_parser.yy"
                                             {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3621 "dhcp6_parser.cc"
    break;

  case 699:
#line 2314 "dhcp6_parser.yy"
                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3629 "dhcp6_parser.cc"
    break;

  case 700:
#line 2316 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3639 "dhcp6_parser.cc"
    break;

  case 701:
#line 2322 "dhcp6_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3647 "dhcp6_parser.cc"
    break;

  case 702:
#line 2324 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3657 "dhcp6_parser.cc"
    break;

  case 703:
#line 2330 "dhcp6_parser.yy"
                                       {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3666 "dhcp6_parser.cc"
    break;

  case 704:
#line 2335 "dhcp6_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3674 "dhcp6_parser.cc"
    break;

  case 705:
#line 2337 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3684 "dhcp6_parser.cc"
    break;

  case 706:
#line 2343 "dhcp6_parser.yy"
                                       {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3693 "dhcp6_parser.cc"
    break;

  case 707:
#line 2348 "dhcp6_parser.yy"
                                             {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3702 "dhcp6_parser.cc"
    break;

  case 708:
#line 2353 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3710 "dhcp6_parser.cc"
    break;

  case 709:
#line 2355 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3719 "dhcp6_parser.cc"
    break;

  case 710:
#line 2361 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3725 "dhcp6_parser.cc"
    break;

  case 711:
#line 2362 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3731 "dhcp6_parser.cc"
    break;

  case 712:
#line 2365 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3739 "dhcp6_parser.cc"
    break;

  case 713:
#line 2367 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3749 "dhcp6_parser.cc"
    break;

  case 714:
#line 2374 "dhcp6_parser.yy"
                                                         {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3758 "dhcp6_parser.cc"
    break;

  case 715:
#line 2380 "dhcp6_parser.yy"
                                                                 {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3767 "dhcp6_parser.cc"
    break;

  case 716:
#line 2386 "dhcp6_parser.yy"
                                             {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3775 "dhcp6_parser.cc"
    break;

  case 717:
#line 2388 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3784 "dhcp6_parser.cc"
    break;

  case 718:
#line 2394 "dhcp6_parser.yy"
                                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3792 "dhcp6_parser.cc"
    break;

  case 719:
#line 2396 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3802 "dhcp6_parser.cc"
    break;

  case 720:
#line 2403 "dhcp6_parser.yy"
                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3810 "dhcp6_parser.cc"
    break;

  case 721:
#line 2405 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3820 "dhcp6_parser.cc"
    break;

  case 722:
#line 2412 "dhcp6_parser.yy"
                                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3828 "dhcp6_parser.cc"
    break;

  case 723:
#line 2414 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3838 "dhcp6_parser.cc"
    break;

  case 724:
#line 2423 "dhcp6_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3846 "dhcp6_parser.cc"
    break;

  case 725:
#line 2425 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3855 "dhcp6_parser.cc"
    break;

  case 726:
#line 2430 "dhcp6_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3863 "dhcp6_parser.cc"
    break;

  case 727:
#line 2432 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3872 "dhcp6_parser.cc"
    break;

  case 728:
#line 2437 "dhcp6_parser.yy"
                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3880 "dhcp6_parser.cc"
    break;

  case 729:
#line 2439 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3889 "dhcp6_parser.cc"
    break;

  case 730:
#line 2446 "dhcp6_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3900 "dhcp6_parser.cc"
    break;

  case 731:
#line 2451 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3910 "dhcp6_parser.cc"
    break;

  case 732:
#line 2457 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3920 "dhcp6_parser.cc"
    break;

  case 733:
#line 2461 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 3929 "dhcp6_parser.cc"
    break;

  case 738:
#line 2476 "dhcp6_parser.yy"
                                   {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3940 "dhcp6_parser.cc"
    break;

  case 739:
#line 2481 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3949 "dhcp6_parser.cc"
    break;

  case 740:
#line 2486 "dhcp6_parser.yy"
                                                             {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3958 "dhcp6_parser.cc"
    break;

  case 741:
#line 2496 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3969 "dhcp6_parser.cc"
    break;

  case 742:
#line 2501 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3978 "dhcp6_parser.cc"
    break;

  case 743:
#line 2506 "dhcp6_parser.yy"
                            {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3988 "dhcp6_parser.cc"
    break;

  case 744:
#line 2510 "dhcp6_parser.yy"
                                {
    // parsing completed
}
#line 3996 "dhcp6_parser.cc"
    break;

  case 748:
#line 2526 "dhcp6_parser.yy"
                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4007 "dhcp6_parser.cc"
    break;

  case 749:
#line 2531 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4016 "dhcp6_parser.cc"
    break;

  case 752:
#line 2543 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4026 "dhcp6_parser.cc"
    break;

  case 753:
#line 2547 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4034 "dhcp6_parser.cc"
    break;

  case 763:
#line 2564 "dhcp6_parser.yy"
                                     {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4043 "dhcp6_parser.cc"
    break;

  case 764:
#line 2569 "dhcp6_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4051 "dhcp6_parser.cc"
    break;

  case 765:
#line 2571 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4061 "dhcp6_parser.cc"
    break;

  case 766:
#line 2577 "dhcp6_parser.yy"
                                    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4072 "dhcp6_parser.cc"
    break;

  case 767:
#line 2582 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4081 "dhcp6_parser.cc"
    break;

  case 770:
#line 2591 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4091 "dhcp6_parser.cc"
    break;

  case 771:
#line 2595 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4099 "dhcp6_parser.cc"
    break;

  case 779:
#line 2610 "dhcp6_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4107 "dhcp6_parser.cc"
    break;

  case 780:
#line 2612 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4117 "dhcp6_parser.cc"
    break;

  case 781:
#line 2618 "dhcp6_parser.yy"
                           {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4126 "dhcp6_parser.cc"
    break;

  case 782:
#line 2623 "dhcp6_parser.yy"
                               {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4135 "dhcp6_parser.cc"
    break;

  case 783:
#line 2628 "dhcp6_parser.yy"
                             {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4144 "dhcp6_parser.cc"
    break;

  case 784:
#line 2633 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4152 "dhcp6_parser.cc"
    break;

  case 785:
#line 2635 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4162 "dhcp6_parser.cc"
    break;


#line 4166 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -961;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     403,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,    50,    36,    45,    47,
      51,    65,    75,   119,   154,   164,   186,   197,   198,   208,
     259,   279,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,    36,  -155,    26,   685,    31,   209,    91,   105,
     108,    21,    81,   262,   -25,   205,   -52,    86,  -961,   122,
     159,   284,   286,   306,  -961,  -961,  -961,  -961,  -961,   308,
    -961,    43,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,   309,   322,   323,   324,   326,   335,
     346,   348,   349,   369,   395,   396,  -961,   399,   402,   413,
     418,   419,  -961,  -961,  -961,   422,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,   428,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,    76,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,   430,  -961,    93,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,   431,
     432,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,   100,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,   113,  -961,  -961,
    -961,  -961,  -961,   434,  -961,   435,   438,  -961,  -961,  -961,
    -961,  -961,  -961,   121,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,   333,   340,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,   408,  -961,  -961,   439,  -961,  -961,  -961,   440,  -961,
    -961,   437,   443,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,   445,   446,  -961,  -961,
    -961,  -961,   444,   459,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,   176,  -961,  -961,  -961,
     462,  -961,  -961,   464,  -961,   465,   466,  -961,  -961,   474,
     475,  -961,  -961,  -961,  -961,  -961,  -961,  -961,   203,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,   221,  -961,  -961,  -961,   478,
     240,  -961,  -961,  -961,  -961,    36,    36,  -961,   264,   479,
     480,   481,   482,   483,  -961,    26,  -961,   484,   485,   486,
     490,   491,   493,   298,   299,   300,   301,   302,   304,   312,
     314,   305,   315,   316,   318,   502,   319,   320,   329,   332,
     334,   511,   520,   522,   336,   531,   535,   536,   537,   540,
     541,   542,   543,   547,   548,   549,   550,   551,   552,   568,
     569,   375,   570,   580,   598,   601,   604,   607,   609,   685,
    -961,   610,   414,    31,  -961,   613,   614,   616,   617,   619,
     424,   425,   622,   624,   625,   209,  -961,   626,    91,  -961,
     627,   436,   628,   441,   442,   105,  -961,   630,   633,   634,
     635,   636,   639,   640,  -961,   108,  -961,   641,   642,   447,
     644,   645,   646,   449,  -961,    81,   651,   455,   457,  -961,
     262,   656,   657,   -54,  -961,   460,   659,   660,   467,   661,
     473,   476,   662,   670,   477,   487,   671,   673,   674,   677,
     205,  -961,   -52,  -961,   678,   488,    86,  -961,  -961,  -961,
     679,   514,   683,    36,    36,    36,  -961,   494,   687,   688,
     691,   692,   680,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,   503,  -961,  -961,  -961,  -961,
    -961,  -105,   507,   508,  -961,   696,   703,   704,   705,   512,
     155,   708,   709,   710,   712,   711,   714,   715,   716,   747,
     748,  -961,   749,   750,   751,   752,   523,   524,   755,  -961,
     756,  -961,  -961,   757,   758,   565,   566,   567,  -961,  -961,
     756,   571,   760,  -961,   574,  -961,   575,  -961,   576,  -961,
    -961,  -961,   756,   756,   756,   577,   578,   581,   582,  -961,
     583,   589,  -961,   591,   592,   593,  -961,  -961,   594,  -961,
    -961,  -961,   596,    36,  -961,  -961,   597,   599,  -961,   600,
    -961,  -961,   102,   528,  -961,  -961,  -105,   602,   603,   605,
    -961,  -961,   763,  -961,  -961,    36,   685,   -52,  -961,  -961,
    -961,  -961,    86,    31,   106,   106,   762,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,   772,   790,   793,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,   798,   -48,    36,
      70,   706,   800,   801,   803,   245,    68,   145,   195,    94,
     205,  -961,  -961,   804,  -961,  -961,   805,   807,  -961,  -961,
    -961,  -961,  -961,   -68,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,   762,  -961,   303,   307,   313,   321,  -961,
    -961,  -961,  -961,   811,   812,   813,   814,   815,  -961,   816,
     819,  -961,  -961,  -961,   820,   821,   823,   824,  -961,   337,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,   339,  -961,   825,   681,  -961,  -961,   826,   707,  -961,
    -961,   828,   827,  -961,  -961,   829,   833,  -961,  -961,   831,
     835,  -961,  -961,  -961,   107,  -961,  -961,  -961,   834,  -961,
    -961,  -961,   166,  -961,  -961,  -961,  -961,   373,  -961,  -961,
    -961,   211,  -961,  -961,   836,   838,  -961,  -961,   837,   841,
    -961,   842,   843,   844,   845,   846,   847,   374,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,   848,   849,   852,
    -961,  -961,  -961,  -961,   377,  -961,  -961,  -961,  -961,  -961,
    -961,   854,   855,   856,  -961,   380,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,   381,  -961,  -961,
    -961,   857,  -961,   858,  -961,  -961,  -961,   383,  -961,  -961,
    -961,  -961,  -961,   384,  -961,   272,  -961,   664,  -961,   839,
     861,  -961,  -961,   859,   863,  -961,  -961,  -961,   860,  -961,
     864,  -961,  -961,  -961,  -961,   865,   867,   868,   869,   667,
     637,   675,   672,   676,   873,   682,   686,   874,   875,   876,
     689,   690,   693,   694,   106,  -961,  -961,   106,  -961,   762,
     209,  -961,   772,    81,  -961,   790,   262,  -961,   793,   517,
    -961,   798,   -48,  -961,  -961,    70,  -961,   877,   706,  -961,
      -1,   800,  -961,   108,  -961,   801,   -25,  -961,   803,   697,
     698,   699,   700,   701,   702,   245,  -961,   879,   881,   713,
     719,   721,    68,  -961,   722,   730,   735,   145,  -961,   883,
     884,   195,  -961,   734,   887,   737,   888,    94,  -961,  -961,
     147,   804,  -961,  -961,   890,   900,    91,  -961,   805,   105,
    -961,   807,   889,  -961,  -961,   405,   740,   742,   744,  -961,
    -961,  -961,  -961,  -961,   745,  -961,  -961,   753,   771,   778,
    -961,  -961,  -961,  -961,  -961,   387,  -961,   390,  -961,   896,
    -961,   897,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,   393,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,   781,  -961,  -961,   903,  -961,  -961,  -961,  -961,  -961,
     906,   905,  -961,  -961,  -961,  -961,  -961,   938,  -961,   394,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,    97,   784,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,   787,   809,
    -961,  -961,   840,  -961,    36,  -961,  -961,   907,  -961,  -961,
    -961,  -961,  -961,   404,  -961,  -961,  -961,  -961,  -961,  -961,
     850,   410,  -961,   411,  -961,   851,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,   517,  -961,  -961,   946,   759,  -961,    -1,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
     947,   754,   951,   147,  -961,  -961,  -961,  -961,  -961,  -961,
     853,  -961,  -961,   984,  -961,   862,  -961,  -961,   985,  -961,
    -961,   273,  -961,   -14,   985,  -961,  -961,   993,   996,  1007,
    -961,   412,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  1009,
     830,   866,   870,  1026,   -14,  -961,   872,  -961,  -961,  -961,
     878,  -961,  -961,  -961
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   168,     9,
     330,    11,   508,    13,   533,    15,   563,    17,   433,    19,
     441,    21,   478,    23,   295,    25,   676,    27,   743,    29,
     732,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     565,     0,   443,   480,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   741,   724,   726,   728,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   129,   730,
     166,   180,   182,   184,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   164,     0,     0,     0,
       0,     0,   146,   153,   155,     0,   322,   431,   470,   521,
     523,   380,   388,   255,   272,   263,   248,   600,   555,   287,
     306,   621,     0,   274,   645,   658,   674,   157,   159,   748,
     128,     0,    74,    76,    77,    78,    79,    80,    81,    82,
      83,    84,   112,   113,   114,    85,   118,   119,   120,   121,
     122,   123,   116,   117,   124,   125,   126,   110,    88,    89,
      90,    91,   107,    92,    94,    93,   127,    98,    99,    86,
     111,    87,    96,    97,   105,   106,   108,    95,   100,   101,
     102,   103,   104,   109,   115,   177,     0,   176,     0,   170,
     172,   173,   174,   175,   500,   525,   370,   372,   374,     0,
       0,   378,   376,   594,   369,   334,   335,   336,   337,   338,
     339,   340,   341,   357,   358,   359,   362,   363,   364,   365,
     366,   367,   360,   361,   368,     0,   332,   345,   346,   347,
     350,   351,   353,   348,   349,   342,   343,   355,   356,   344,
     352,   354,   519,   518,   514,   515,   513,     0,   510,   512,
     516,   517,   548,     0,   551,     0,     0,   547,   541,   542,
     540,   545,   546,     0,   535,   537,   538,   543,   544,   539,
     592,   580,   582,   584,   586,   588,   590,   579,   576,   577,
     578,     0,   566,   567,   571,   572,   569,   573,   574,   575,
     570,     0,   460,   228,     0,   464,   462,   467,     0,   456,
     457,     0,   444,   445,   447,   459,   448,   449,   450,   466,
     451,   452,   453,   454,   455,   494,     0,     0,   492,   493,
     496,   497,     0,   481,   482,   484,   485,   486,   487,   488,
     489,   490,   491,   302,   304,   299,     0,   297,   300,   301,
       0,   699,   701,     0,   704,     0,     0,   708,   712,     0,
       0,   716,   718,   720,   722,   697,   695,   696,     0,   678,
     680,   681,   682,   683,   684,   685,   686,   687,   688,   689,
     690,   691,   692,   693,   694,     0,   745,   747,   738,     0,
       0,   734,   736,   737,    48,     0,     0,    41,     0,     0,
       0,     0,     0,     0,    59,     0,    61,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      73,     0,     0,     0,   169,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   331,     0,     0,   509,
       0,     0,     0,     0,     0,     0,   534,     0,     0,     0,
       0,     0,     0,     0,   564,     0,   434,     0,     0,     0,
       0,     0,     0,     0,   442,     0,     0,     0,     0,   479,
       0,     0,     0,     0,   296,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   677,     0,   744,     0,     0,     0,   733,    52,    45,
       0,     0,     0,     0,     0,     0,    63,     0,     0,     0,
       0,     0,     0,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,     0,   162,   163,   143,   144,
     145,     0,     0,     0,   161,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   644,     0,     0,     0,     0,     0,     0,     0,    75,
       0,   179,   171,     0,     0,     0,     0,     0,   386,   387,
       0,     0,     0,   333,     0,   511,     0,   550,     0,   553,
     554,   536,     0,     0,     0,     0,     0,     0,     0,   568,
       0,     0,   458,     0,     0,     0,   469,   446,     0,   498,
     499,   483,     0,     0,   298,   698,     0,     0,   703,     0,
     706,   707,     0,     0,   714,   715,     0,     0,     0,     0,
     679,   746,     0,   740,   735,     0,     0,     0,   725,   727,
     729,   130,     0,     0,     0,     0,   186,   165,   148,   149,
     150,   151,   152,   147,   154,   156,   324,   435,   472,    42,
     522,   524,   382,   383,   384,   385,   381,   390,     0,    49,
       0,     0,     0,   557,   289,     0,     0,     0,     0,     0,
       0,   158,   160,     0,    53,   178,   502,   527,   371,   373,
     375,   379,   377,     0,   520,   549,   552,   593,   581,   583,
     585,   587,   589,   591,   461,   229,   465,   463,   468,   495,
     303,   305,   700,   702,   705,   710,   711,   709,   713,   717,
     719,   721,   723,   186,    46,     0,     0,     0,     0,   215,
     221,   223,   225,     0,     0,     0,     0,     0,   239,     0,
       0,   242,   244,   246,     0,     0,     0,     0,   214,     0,
     192,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   206,   213,   207,   208,   209,   204,   205,   210,   211,
     212,     0,   190,     0,   187,   188,   328,     0,   325,   326,
     439,     0,   436,   437,   476,     0,   473,   474,   394,     0,
     391,   392,   261,   262,     0,   257,   259,   260,     0,   270,
     271,   267,     0,   265,   268,   269,   253,     0,   250,   252,
     604,     0,   602,   561,     0,   558,   559,   293,     0,   290,
     291,     0,     0,     0,     0,     0,     0,     0,   308,   310,
     311,   312,   313,   314,   315,   634,   640,     0,     0,     0,
     633,   630,   631,   632,     0,   623,   625,   628,   626,   627,
     629,     0,     0,     0,   283,     0,   276,   278,   279,   280,
     281,   282,   654,   656,   653,   651,   652,     0,   647,   649,
     650,     0,   669,     0,   672,   665,   666,     0,   660,   662,
     663,   664,   667,     0,   752,     0,   750,    55,   506,     0,
     503,   504,   531,     0,   528,   529,   598,   597,     0,   596,
       0,    71,   742,   731,   167,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   181,   183,     0,   185,     0,
       0,   323,     0,   443,   432,     0,   480,   471,     0,     0,
     389,     0,     0,   256,   273,     0,   264,     0,     0,   249,
     606,     0,   601,   565,   556,     0,     0,   288,     0,     0,
       0,     0,     0,     0,     0,     0,   307,     0,     0,     0,
       0,     0,     0,   622,     0,     0,     0,     0,   275,     0,
       0,     0,   646,     0,     0,     0,     0,     0,   659,   675,
       0,     0,   749,    57,     0,    56,     0,   501,     0,     0,
     526,     0,     0,   595,   739,     0,     0,     0,     0,   227,
     230,   231,   232,   233,     0,   241,   234,     0,     0,     0,
     236,   237,   238,   235,   193,     0,   189,     0,   327,     0,
     438,     0,   475,   430,   409,   410,   411,   413,   414,   415,
     402,   403,   418,   419,   420,   423,   424,   425,   426,   427,
     428,   421,   422,   429,   398,   399,   400,   401,   407,   408,
     406,   412,     0,   396,   404,   416,   417,   405,   393,   258,
     266,     0,   251,   618,     0,   616,   617,   613,   614,   615,
       0,   607,   608,   610,   611,   612,   603,     0,   560,     0,
     292,   316,   317,   318,   319,   320,   321,   309,     0,     0,
     639,   642,   643,   624,   284,   285,   286,   277,     0,     0,
     648,   668,     0,   671,     0,   661,   766,     0,   764,   762,
     756,   760,   761,     0,   754,   758,   759,   757,   751,    54,
       0,     0,   505,     0,   530,     0,   217,   218,   219,   220,
     216,   222,   224,   226,   240,   243,   245,   247,   191,   329,
     440,   477,     0,   395,   254,     0,     0,   605,     0,   562,
     294,   636,   637,   638,   635,   641,   655,   657,   670,   673,
       0,     0,     0,     0,   753,    58,   507,   532,   599,   397,
       0,   620,   609,     0,   763,     0,   755,   619,     0,   765,
     770,     0,   768,     0,     0,   767,   779,     0,     0,     0,
     784,     0,   772,   774,   775,   776,   777,   778,   769,     0,
       0,     0,     0,     0,     0,   771,     0,   781,   782,   783,
       0,   773,   780,   785
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,    -5,  -961,   448,
    -961,  -961,  -961,  -961,  -961,  -961,   317,  -961,  -573,  -961,
    -961,  -961,   -74,  -961,  -961,  -961,   615,  -961,  -961,  -961,
    -961,   356,   555,  -961,  -961,   -62,   -42,   -24,   -22,   -21,
     -18,    -4,    10,    13,    14,    15,  -961,    16,    27,    30,
      32,  -961,   367,    34,  -961,    35,  -961,    37,  -961,    38,
    -961,    42,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
     352,   572,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,   275,  -961,    72,  -961,  -669,    79,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,   -66,  -961,  -703,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
      56,  -961,  -961,  -961,  -961,  -961,    64,  -692,  -961,  -961,
    -961,  -961,    62,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
      33,  -961,  -961,  -961,  -961,  -961,  -961,  -961,    54,  -961,
    -961,  -961,    53,   525,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,    49,  -961,  -961,  -961,  -961,  -961,  -961,  -960,  -961,
    -961,  -961,    83,  -961,  -961,  -961,    87,   573,  -961,  -961,
    -958,  -961,  -957,  -961,    44,  -961,    52,  -961,    48,  -961,
    -961,  -961,  -956,  -961,  -961,  -961,  -961,    78,  -961,  -961,
    -139,   991,  -961,  -961,  -961,  -961,  -961,    88,  -961,  -961,
    -961,    92,  -961,   553,  -961,   -76,  -961,  -961,  -961,  -961,
    -961,   -70,  -961,  -961,  -961,  -961,  -961,   -40,  -961,  -961,
    -961,    95,  -961,  -961,  -961,    90,  -961,   544,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,    39,
    -961,  -961,  -961,    40,   584,  -961,  -961,   -58,  -961,    -2,
    -961,  -961,  -961,  -961,  -961,    28,  -961,  -961,  -961,    46,
     579,  -961,  -961,  -961,  -961,  -961,  -961,  -961,   -47,  -961,
    -961,  -961,    80,  -961,  -961,  -961,    77,  -961,   585,   338,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -955,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,    96,  -961,  -961,  -961,  -120,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,    67,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,    60,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,    55,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,   364,   546,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,   407,   554,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,   415,   556,   -72,  -961,  -961,    63,  -961,  -961,  -118,
    -961,  -961,  -961,  -961,  -961,  -961,  -141,  -961,  -961,  -158,
    -961,  -961,  -961,  -961,  -961,  -961,  -961
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   710,    92,    93,    43,    72,    89,    90,   735,   937,
    1044,  1045,   798,    45,    74,   101,   102,   103,   419,    47,
      75,   161,   162,   163,   427,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   451,   703,   180,   452,   181,   453,   182,   476,   183,
     477,   184,   185,   186,   187,   445,   188,   429,    49,    76,
     218,   219,   220,   481,   221,   189,   430,   190,   431,   191,
     432,   823,   824,   825,   977,   799,   800,   801,   955,  1190,
     802,   956,   803,   957,   804,   958,   805,   806,   518,   807,
     808,   809,   810,   811,   812,   813,   814,   815,   816,   964,
     817,   818,   967,   819,   968,   820,   969,   192,   465,   857,
     858,   859,   997,   193,   462,   844,   845,   846,   847,   194,
     464,   852,   853,   854,   855,   195,   463,   196,   472,   905,
     906,   907,   908,   909,   197,   468,   868,   869,   870,  1006,
      65,    84,   366,   367,   368,   531,   369,   532,   198,   469,
     877,   878,   879,   880,   881,   882,   883,   884,   199,   455,
     827,   828,   829,   980,    51,    77,   255,   256,   257,   487,
     258,   488,   259,   489,   260,   493,   261,   492,   200,   460,
     716,   263,   264,   201,   461,   839,   840,   841,   989,  1112,
    1113,   202,   456,    59,    81,   831,   832,   833,   983,    61,
      82,   331,   332,   333,   334,   335,   336,   337,   517,   338,
     521,   339,   520,   340,   341,   522,   342,   203,   457,   835,
     836,   837,   986,    63,    83,   352,   353,   354,   355,   356,
     526,   357,   358,   359,   360,   266,   485,   939,   940,   941,
    1046,    53,    78,   277,   278,   279,   497,   204,   458,   205,
     459,   269,   486,   943,   944,   945,  1049,    55,    79,   293,
     294,   295,   500,   296,   297,   502,   298,   299,   206,   467,
     864,   865,   866,  1003,    57,    80,   311,   312,   313,   314,
     508,   315,   509,   316,   510,   317,   511,   318,   512,   319,
     513,   320,   507,   271,   494,   948,   949,  1052,   207,   466,
     861,   862,  1000,  1130,  1131,  1132,  1133,  1134,  1205,  1135,
     208,   470,   894,   895,   896,  1017,  1214,   897,   898,  1018,
     899,   900,   209,   210,   473,   917,   918,   919,  1029,   920,
    1030,   211,   474,   927,   928,   929,   930,  1034,   931,   932,
    1036,   212,   475,    67,    85,   388,   389,   390,   391,   536,
     392,   537,   393,   394,   539,   395,   396,   397,   542,   767,
     398,   543,   399,   400,   401,   546,   402,   547,   403,   548,
     404,   549,   104,   421,   105,   422,   106,   423,   213,   428,
      71,    87,   410,   411,   412,   554,   413,   107,   420,    69,
      86,   405,   406,   214,   478,   935,   936,  1040,  1173,  1174,
    1175,  1176,  1222,  1177,  1220,  1241,  1242,  1243,  1251,  1252,
    1253,  1259,  1254,  1255,  1256,  1257,  1263
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     100,   160,   217,   234,   273,   287,   307,   350,   329,   348,
     365,   385,    40,   351,   407,   235,   330,   349,   222,   267,
     280,   291,   309,   891,   343,   361,   821,   386,   851,  1105,
     270,  1106,  1107,  1111,  1117,   236,    94,   265,   276,   290,
     308,    33,   301,    34,    91,    35,   425,   215,   216,   946,
      32,   426,    44,   237,    46,   238,   239,   741,    48,   240,
     698,   699,   700,   701,   842,   363,   364,   138,   323,   747,
     748,   749,    50,   241,   223,   268,   281,   292,   310,   479,
     344,   362,    52,   387,   480,   139,   140,   242,   137,   885,
     243,   244,   245,   246,   363,   364,   483,   702,   784,   408,
     409,   484,   322,   495,   247,  1123,  1124,   248,   496,   249,
     992,   250,   251,   993,   252,   253,   498,   139,   140,   254,
     159,   499,   274,   288,   505,   262,    54,   779,   414,   506,
     275,   289,   780,   781,   782,   783,   784,   785,   786,   787,
     788,   789,   790,   791,   792,   793,   794,   795,   796,   797,
     323,   843,   324,   325,   139,   140,   326,   327,   328,   138,
    1246,    56,   415,  1247,  1248,  1249,  1250,   139,   140,   995,
     272,    58,   996,   138,    99,   323,   138,   139,   140,   533,
     139,   140,   842,   849,   534,   850,   282,   283,   284,   285,
     286,   139,   140,    60,   139,   140,   231,    95,    99,   232,
     886,   887,   888,   889,    62,    64,   550,    96,    97,    98,
     231,   551,   300,   232,  1001,    66,   323,  1002,   301,   302,
     303,   304,   305,   306,   552,    99,  1211,  1212,  1213,   553,
      99,   139,   140,   139,   140,    36,    37,    38,    39,   921,
     922,   923,  1105,   556,  1106,  1107,  1111,  1117,   557,   712,
     713,   714,   715,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   765,   766,    68,    99,   129,   130,
     131,   132,   133,   134,   135,  1041,  1244,   138,  1042,  1245,
      99,   139,   140,   901,   902,   903,    70,   224,   416,   225,
      99,   139,   140,   924,   417,   139,   140,   226,   227,   228,
     229,   230,   141,   851,    99,    99,   479,    99,  1075,   418,
     552,   951,   424,   433,   231,   952,   556,   232,   148,   891,
    1166,   953,  1167,  1168,   483,   233,   434,   435,   436,   954,
     437,   323,   345,   324,   325,   346,   347,   912,   913,   438,
     974,   514,   974,   515,    99,   975,    99,   976,   139,   140,
     439,   100,   440,   441,   370,   371,   372,   373,   374,   375,
     376,   377,   378,   379,   380,   381,   382,   871,   872,   873,
     874,   875,   876,   442,   383,   384,   998,  1015,   157,   158,
    1022,   999,  1016,  1027,  1031,  1023,  1037,   550,  1028,  1032,
     974,  1038,  1039,   495,    99,  1198,  1202,   533,  1199,   443,
     444,  1203,  1210,   446,    99,   160,   447,  1223,    99,   217,
     558,   559,  1224,   498,   505,  1264,   516,   448,  1226,  1227,
    1265,   234,   449,   450,   273,   222,   454,  1186,  1187,  1188,
    1189,   287,   471,   235,   482,   490,   491,   267,   501,   503,
     280,   307,   504,   519,   523,   524,   525,   291,   270,   527,
     528,   329,   529,   236,   350,   265,   348,   309,   276,   330,
     351,    99,   530,   560,   349,   290,   535,   343,   538,   540,
     541,   237,   361,   238,   239,   308,   385,   240,   544,   545,
     407,   223,   555,   561,   562,   563,   564,   565,   567,   568,
     569,   241,   386,   268,   570,   571,   281,   572,   573,   574,
     575,   576,   577,   292,   578,   242,   585,   581,   243,   244,
     245,   246,   579,   310,   580,   591,   582,   583,   584,   586,
     587,   686,   247,   344,   592,   248,   593,   249,   362,   250,
     251,   588,   252,   253,   589,   595,   590,   254,   594,   596,
     597,   598,   274,   262,   599,   600,   601,   602,   387,   288,
     275,   603,   604,   605,   606,   607,   608,   289,   688,   689,
     690,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   609,   610,   612,   611,   129,   130,   131,   132,
     133,   134,   135,   136,   613,   138,   323,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,   614,   139,   140,   615,   227,   228,   616,   230,
     141,   617,   160,   618,   620,   407,   621,   623,   624,   217,
     625,   626,   231,   627,   628,   232,   630,   629,   631,   632,
     634,   636,   638,   233,   642,   222,   637,   643,   644,   645,
     646,   639,   640,   647,   648,   650,   651,   652,   653,   654,
     655,   656,   890,   904,   914,   658,   385,   659,   761,   660,
     662,   663,   665,   666,   667,   669,   672,   668,   892,   910,
     915,   925,   386,   670,   673,   676,   671,   677,   678,   674,
     774,   679,   682,   685,   979,   696,   157,   158,   683,   675,
     687,   223,   768,   691,   692,   693,   108,   109,   694,   695,
     110,   706,   697,   111,   112,   113,   704,   705,   707,   708,
     982,   711,    34,   717,   718,   719,    99,   720,   721,   722,
     723,   724,   731,   732,   893,   911,   916,   926,   387,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   725,   726,   727,   728,   729,   730,
     733,   734,   736,   737,   738,   739,   740,   743,   773,   822,
     742,   139,   140,   744,   745,   746,   750,   751,   141,   826,
     752,   753,   754,   142,   143,   144,   145,   146,   755,   147,
     756,   757,   758,   759,   148,   760,   762,   830,   763,   764,
     834,   770,   771,   149,   772,   838,   150,   860,   863,   856,
     867,   934,   938,   151,   942,   959,   960,   961,   962,   963,
     965,   152,   153,   966,   970,   971,   154,   972,   973,   155,
     985,   978,   981,   156,   984,   987,   988,   990,   991,  1060,
     994,  1005,  1004,  1007,  1008,  1047,  1009,  1010,  1011,  1012,
    1013,  1014,  1019,  1020,   157,   158,  1021,   159,  1024,  1025,
    1026,  1033,  1035,  1043,  1048,  1050,  1051,  1059,  1053,  1055,
    1054,  1056,  1057,  1058,  1062,  1061,  1063,  1064,  1067,  1068,
    1069,  1121,  1065,  1148,    99,  1149,  1066,  1158,  1159,  1070,
    1071,  1162,  1164,  1185,  1073,  1072,  1179,  1141,  1142,  1143,
    1144,  1145,  1146,  1180,  1200,  1201,   234,  1206,  1208,   329,
     350,  1221,   348,  1150,  1207,  1083,   351,   330,   235,  1151,
     349,  1152,   267,  1104,  1154,   343,  1125,  1084,   361,   307,
    1155,  1115,   365,   270,  1126,  1156,  1161,  1163,   236,  1191,
     265,  1192,  1128,  1193,  1194,   309,  1209,  1085,   890,  1114,
    1230,  1233,  1195,   904,  1234,  1235,   237,   914,   238,   239,
    1127,  1231,   240,   308,   892,  1086,  1169,  1087,  1088,   910,
    1196,  1089,   273,   915,  1170,   287,   241,  1197,   268,   925,
    1204,   344,  1171,  1215,   362,  1090,  1216,  1116,   280,  1238,
     242,   291,  1240,   243,   244,   245,   246,  1260,  1129,  1091,
    1261,   310,  1092,  1093,  1094,  1095,   276,   247,  1217,   290,
     248,  1262,   249,  1266,   250,   251,  1096,   252,   253,  1097,
     893,  1098,   254,  1099,  1100,   911,  1101,  1102,   262,   916,
    1270,  1103,  1267,  1108,   619,   926,   848,  1110,  1172,  1218,
     566,  1109,   775,   769,   281,   778,   709,   292,   950,  1225,
    1228,  1076,  1237,  1074,  1122,   622,  1119,  1120,   664,  1139,
    1157,  1239,  1140,  1229,  1147,  1078,  1268,  1077,   633,  1118,
    1269,  1272,   321,  1080,   661,  1079,  1081,  1273,   657,  1184,
    1137,   947,   635,  1082,   641,  1138,  1181,  1182,  1232,  1153,
     274,  1160,  1165,   288,   933,  1183,   680,  1136,   275,   777,
     649,   289,   776,  1258,  1178,  1236,  1271,     0,   681,     0,
     684,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1083,     0,
       0,     0,     0,     0,  1125,     0,  1104,     0,     0,     0,
    1084,     0,  1126,     0,  1115,     0,     0,     0,     0,  1169,
    1128,     0,     0,     0,     0,     0,     0,  1170,     0,  1219,
    1085,     0,  1114,     0,     0,  1171,     0,     0,  1127,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1086,     0,
    1087,  1088,     0,     0,  1089,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1090,     0,
    1116,     0,     0,     0,     0,     0,  1129,     0,     0,     0,
       0,     0,  1091,     0,     0,  1092,  1093,  1094,  1095,     0,
       0,  1172,     0,     0,     0,     0,     0,     0,     0,  1096,
       0,     0,  1097,     0,  1098,     0,  1099,  1100,     0,  1101,
    1102,     0,     0,     0,  1103,     0,  1108,     0,     0,     0,
    1110,     0,     0,     0,  1109
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    83,    82,    83,
      84,    85,    17,    83,    86,    77,    82,    83,    76,    77,
      78,    79,    80,   726,    82,    83,   695,    85,   720,   989,
      77,   989,   989,   989,   989,    77,    10,    77,    78,    79,
      80,     5,   110,     7,   199,     9,     3,    16,    17,   117,
       0,     8,     7,    77,     7,    77,    77,   630,     7,    77,
     165,   166,   167,   168,   112,   119,   120,    68,    69,   642,
     643,   644,     7,    77,    76,    77,    78,    79,    80,     3,
      82,    83,     7,    85,     8,    86,    87,    77,    67,    21,
      77,    77,    77,    77,   119,   120,     3,   202,    30,    13,
      14,     8,    21,     3,    77,   106,   107,    77,     8,    77,
       3,    77,    77,     6,    77,    77,     3,    86,    87,    77,
     172,     8,    78,    79,     3,    77,     7,    21,     6,     8,
      78,    79,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      69,   199,    71,    72,    86,    87,    75,    76,    77,    68,
     174,     7,     3,   177,   178,   179,   180,    86,    87,     3,
      79,     7,     6,    68,   199,    69,    68,    86,    87,     3,
      86,    87,   112,   113,     8,   115,    81,    82,    83,    84,
      85,    86,    87,     7,    86,    87,   105,   171,   199,   108,
     132,   133,   134,   135,     7,     7,     3,   181,   182,   183,
     105,     8,   104,   108,     3,     7,    69,     6,   110,   111,
     112,   113,   114,   115,     3,   199,   129,   130,   131,     8,
     199,    86,    87,    86,    87,   199,   200,   201,   202,   145,
     146,   147,  1202,     3,  1202,  1202,  1202,  1202,     8,    94,
      95,    96,    97,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,   162,   163,     7,   199,    59,    60,
      61,    62,    63,    64,    65,     3,     3,    68,     6,     6,
     199,    86,    87,   138,   139,   140,     7,    78,     4,    80,
     199,    86,    87,   199,     8,    86,    87,    88,    89,    90,
      91,    92,    93,   995,   199,   199,     3,   199,   977,     3,
       3,     8,     4,     4,   105,     8,     3,   108,   109,  1022,
     173,     8,   175,   176,     3,   116,     4,     4,     4,     8,
       4,    69,    70,    71,    72,    73,    74,   142,   143,     4,
       3,     8,     3,     3,   199,     8,   199,     8,    86,    87,
       4,   425,     4,     4,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   122,   123,   124,
     125,   126,   127,     4,   169,   170,     3,     3,   169,   170,
       3,     8,     8,     3,     3,     8,     3,     3,     8,     8,
       3,     8,     8,     3,   199,     8,     3,     3,     8,     4,
       4,     8,     8,     4,   199,   479,     4,     3,   199,   483,
     415,   416,     8,     3,     3,     3,     8,     4,     8,     8,
       8,   495,     4,     4,   498,   483,     4,    22,    23,    24,
      25,   505,     4,   495,     4,     4,     4,   495,     4,     4,
     498,   515,     4,     4,     4,     8,     3,   505,   495,     4,
       4,   525,     8,   495,   530,   495,   530,   515,   498,   525,
     530,   199,     3,   199,   530,   505,     4,   525,     4,     4,
       4,   495,   530,   495,   495,   515,   550,   495,     4,     4,
     552,   483,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   495,   550,   495,     4,     4,   498,     4,   200,   200,
     200,   200,   200,   505,   200,   495,     4,   202,   495,   495,
     495,   495,   200,   515,   200,     4,   201,   201,   200,   200,
     200,     7,   495,   525,     4,   495,     4,   495,   530,   495,
     495,   202,   495,   495,   202,     4,   202,   495,   202,     4,
       4,     4,   498,   495,     4,     4,     4,     4,   550,   505,
     498,     4,     4,     4,     4,     4,     4,   505,   563,   564,
     565,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,     4,     4,     4,   200,    59,    60,    61,    62,
      63,    64,    65,    66,     4,    68,    69,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,     4,    86,    87,     4,    89,    90,     4,    92,
      93,     4,   686,     4,     4,   687,   202,     4,     4,   693,
       4,     4,   105,     4,   200,   108,     4,   202,     4,     4,
       4,     4,     4,   116,     4,   693,   200,     4,     4,     4,
       4,   200,   200,     4,     4,     4,     4,   200,     4,     4,
       4,   202,   726,   727,   728,     4,   730,   202,   663,   202,
       4,     4,   202,     4,     4,     4,     4,   200,   726,   727,
     728,   729,   730,   200,     4,     4,   200,     4,     4,   202,
     685,     4,     4,     4,     3,     5,   169,   170,   200,   202,
       7,   693,   164,   199,     7,     7,    11,    12,     7,     7,
      15,     5,   199,    18,    19,    20,   199,   199,     5,     5,
       3,   199,     7,     5,     5,     5,   199,     5,     7,     5,
       5,     5,   199,   199,   726,   727,   728,   729,   730,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,     7,     7,     7,     7,     7,     7,
       5,     5,     5,     5,   199,   199,   199,     7,     5,     7,
     199,    86,    87,   199,   199,   199,   199,   199,    93,     7,
     199,   199,   199,    98,    99,   100,   101,   102,   199,   104,
     199,   199,   199,   199,   109,   199,   199,     7,   199,   199,
       7,   199,   199,   118,   199,     7,   121,     7,     7,   103,
       7,     7,     7,   128,     7,     4,     4,     4,     4,     4,
       4,   136,   137,     4,     4,     4,   141,     4,     4,   144,
       3,     6,     6,   148,     6,     6,     3,     6,     3,   202,
       6,     3,     6,     6,     3,     6,     4,     4,     4,     4,
       4,     4,     4,     4,   169,   170,     4,   172,     4,     4,
       4,     4,     4,   199,     3,     6,     3,   200,     8,     4,
       6,     4,     4,     4,   202,   200,   200,     4,     4,     4,
       4,     4,   200,     4,   199,     4,   200,     4,     4,   200,
     200,     4,     4,     4,   200,   202,     6,   200,   200,   200,
     200,   200,   200,     3,     8,     8,   980,     4,     3,   983,
     986,     4,   986,   200,     8,   989,   986,   983,   980,   200,
     986,   200,   980,   989,   202,   983,  1000,   989,   986,  1003,
     200,   989,  1006,   980,  1000,   200,   202,   200,   980,   199,
     980,   199,  1000,   199,   199,  1003,     8,   989,  1022,   989,
       4,     4,   199,  1027,   200,     4,   980,  1031,   980,   980,
    1000,   202,   980,  1003,  1022,   989,  1040,   989,   989,  1027,
     199,   989,  1046,  1031,  1040,  1049,   980,   199,   980,  1037,
     199,   983,  1040,   199,   986,   989,   199,   989,  1046,     5,
     980,  1049,     7,   980,   980,   980,   980,     4,  1000,   989,
       4,  1003,   989,   989,   989,   989,  1046,   980,   199,  1049,
     980,     4,   980,     4,   980,   980,   989,   980,   980,   989,
    1022,   989,   980,   989,   989,  1027,   989,   989,   980,  1031,
       4,   989,   202,   989,   479,  1037,   719,   989,  1040,   199,
     425,   989,   686,   676,  1046,   693,   598,  1049,   773,   199,
     199,   979,   199,   974,   998,   483,   992,   995,   533,  1006,
    1027,   199,  1008,  1202,  1015,   982,   200,   980,   495,   991,
     200,   199,    81,   985,   530,   983,   986,   199,   525,  1051,
    1003,   743,   498,   988,   505,  1005,  1046,  1048,  1208,  1022,
    1046,  1031,  1037,  1049,   730,  1049,   550,  1001,  1046,   692,
     515,  1049,   687,  1244,  1041,  1223,  1264,    -1,   552,    -1,
     556,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1202,    -1,
      -1,    -1,    -1,    -1,  1208,    -1,  1202,    -1,    -1,    -1,
    1202,    -1,  1208,    -1,  1202,    -1,    -1,    -1,    -1,  1223,
    1208,    -1,    -1,    -1,    -1,    -1,    -1,  1223,    -1,  1164,
    1202,    -1,  1202,    -1,    -1,  1223,    -1,    -1,  1208,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1202,    -1,
    1202,  1202,    -1,    -1,  1202,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1202,    -1,
    1202,    -1,    -1,    -1,    -1,    -1,  1208,    -1,    -1,    -1,
      -1,    -1,  1202,    -1,    -1,  1202,  1202,  1202,  1202,    -1,
      -1,  1223,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1202,
      -1,    -1,  1202,    -1,  1202,    -1,  1202,  1202,    -1,  1202,
    1202,    -1,    -1,    -1,  1202,    -1,  1202,    -1,    -1,    -1,
    1202,    -1,    -1,    -1,  1202
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,     0,     5,     7,     9,   199,   200,   201,   202,
     220,   221,   222,   227,     7,   236,     7,   242,     7,   281,
       7,   387,     7,   464,     7,   480,     7,   497,     7,   416,
       7,   422,     7,   446,     7,   363,     7,   566,     7,   612,
       7,   603,   228,   223,   237,   243,   282,   388,   465,   481,
     498,   417,   423,   447,   364,   567,   613,   604,   220,   229,
     230,   199,   225,   226,    10,   171,   181,   182,   183,   199,
     235,   238,   239,   240,   595,   597,   599,   610,    11,    12,
      15,    18,    19,    20,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    86,
      87,    93,    98,    99,   100,   101,   102,   104,   109,   118,
     121,   128,   136,   137,   141,   144,   148,   169,   170,   172,
     235,   244,   245,   246,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     266,   268,   270,   272,   274,   275,   276,   277,   279,   288,
     290,   292,   330,   336,   342,   348,   350,   357,   371,   381,
     401,   406,   414,   440,   470,   472,   491,   521,   533,   545,
     546,   554,   564,   601,   616,    16,    17,   235,   283,   284,
     285,   287,   470,   472,    78,    80,    88,    89,    90,    91,
      92,   105,   108,   116,   235,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   260,   261,   262,   263,
     266,   268,   270,   272,   274,   389,   390,   391,   393,   395,
     397,   399,   401,   404,   405,   440,   458,   470,   472,   474,
     491,   516,    79,   235,   397,   399,   440,   466,   467,   468,
     470,   472,    81,    82,    83,    84,    85,   235,   397,   399,
     440,   470,   472,   482,   483,   484,   486,   487,   489,   490,
     104,   110,   111,   112,   113,   114,   115,   235,   440,   470,
     472,   499,   500,   501,   502,   504,   506,   508,   510,   512,
     514,   414,    21,    69,    71,    72,    75,    76,    77,   235,
     310,   424,   425,   426,   427,   428,   429,   430,   432,   434,
     436,   437,   439,   470,   472,    70,    73,    74,   235,   310,
     428,   434,   448,   449,   450,   451,   452,   454,   455,   456,
     457,   470,   472,   119,   120,   235,   365,   366,   367,   369,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   169,   170,   235,   470,   472,   568,   569,
     570,   571,   573,   575,   576,   578,   579,   580,   583,   585,
     586,   587,   589,   591,   593,   614,   615,   616,    13,    14,
     605,   606,   607,   609,     6,     3,     4,     8,     3,   241,
     611,   596,   598,   600,     4,     3,     8,   247,   602,   280,
     289,   291,   293,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   278,     4,     4,     4,     4,
       4,   264,   267,   269,     4,   382,   415,   441,   471,   473,
     402,   407,   337,   349,   343,   331,   522,   492,   358,   372,
     534,     4,   351,   547,   555,   565,   271,   273,   617,     3,
       8,   286,     4,     3,     8,   459,   475,   392,   394,   396,
       4,     4,   400,   398,   517,     3,     8,   469,     3,     8,
     485,     4,   488,     4,     4,     3,     8,   515,   503,   505,
     507,   509,   511,   513,     8,     3,     8,   431,   311,     4,
     435,   433,   438,     4,     8,     3,   453,     4,     4,     8,
       3,   368,   370,     3,     8,     4,   572,   574,     4,   577,
       4,     4,   581,   584,     4,     4,   588,   590,   592,   594,
       3,     8,     3,     8,   608,     4,     3,     8,   220,   220,
     199,     4,     4,     4,     4,     4,   239,     4,     4,     4,
       4,     4,     4,   200,   200,   200,   200,   200,   200,   200,
     200,   202,   201,   201,   200,     4,   200,   200,   202,   202,
     202,     4,     4,     4,   202,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   200,     4,     4,     4,     4,     4,     4,     4,   245,
       4,   202,   284,     4,     4,     4,     4,     4,   200,   202,
       4,     4,     4,   390,     4,   467,     4,   200,     4,   200,
     200,   483,     4,     4,     4,     4,     4,     4,     4,   501,
       4,     4,   200,     4,     4,     4,   202,   426,     4,   202,
     202,   450,     4,     4,   366,   202,     4,     4,   200,     4,
     200,   200,     4,     4,   202,   202,     4,     4,     4,     4,
     569,   615,     4,   200,   606,     4,     7,     7,   220,   220,
     220,   199,     7,     7,     7,     7,     5,   199,   165,   166,
     167,   168,   202,   265,   199,   199,     5,     5,     5,   222,
     224,   199,    94,    95,    96,    97,   403,     5,     5,     5,
       5,     7,     5,     5,     5,     7,     7,     7,     7,     7,
       7,   199,   199,     5,     5,   231,     5,     5,   199,   199,
     199,   231,   199,     7,   199,   199,   199,   231,   231,   231,
     199,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   220,   199,   199,   199,   162,   163,   582,   164,   265,
     199,   199,   199,     5,   220,   244,   614,   605,   283,    21,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,   235,   298,
     299,   300,   303,   305,   307,   309,   310,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   323,   324,   326,
     328,   298,     7,   294,   295,   296,     7,   383,   384,   385,
       7,   418,   419,   420,     7,   442,   443,   444,     7,   408,
     409,   410,   112,   199,   338,   339,   340,   341,   229,   113,
     115,   340,   344,   345,   346,   347,   103,   332,   333,   334,
       7,   523,   524,     7,   493,   494,   495,     7,   359,   360,
     361,   122,   123,   124,   125,   126,   127,   373,   374,   375,
     376,   377,   378,   379,   380,    21,   132,   133,   134,   135,
     235,   312,   470,   472,   535,   536,   537,   540,   541,   543,
     544,   138,   139,   140,   235,   352,   353,   354,   355,   356,
     470,   472,   142,   143,   235,   470,   472,   548,   549,   550,
     552,   145,   146,   147,   199,   470,   472,   556,   557,   558,
     559,   561,   562,   568,     7,   618,   619,   232,     7,   460,
     461,   462,     7,   476,   477,   478,   117,   502,   518,   519,
     294,     8,     8,     8,     8,   301,   304,   306,   308,     4,
       4,     4,     4,     4,   322,     4,     4,   325,   327,   329,
       4,     4,     4,     4,     3,     8,     8,   297,     6,     3,
     386,     6,     3,   421,     6,     3,   445,     6,     3,   411,
       6,     3,     3,     6,     6,     3,     6,   335,     3,     8,
     525,     3,     6,   496,     6,     3,   362,     6,     3,     4,
       4,     4,     4,     4,     4,     3,     8,   538,   542,     4,
       4,     4,     3,     8,     4,     4,     4,     3,     8,   551,
     553,     3,     8,     4,   560,     4,   563,     3,     8,     8,
     620,     3,     6,   199,   233,   234,   463,     6,     3,   479,
       6,     3,   520,     8,     6,     4,     4,     4,     4,   200,
     202,   200,   202,   200,     4,   200,   200,     4,     4,     4,
     200,   200,   202,   200,   299,   298,   296,   389,   385,   424,
     420,   448,   444,   235,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   260,   261,   262,   263,   266,
     268,   270,   272,   274,   310,   381,   393,   395,   397,   399,
     401,   405,   412,   413,   440,   470,   472,   516,   410,   339,
     345,     4,   333,   106,   107,   235,   310,   440,   470,   472,
     526,   527,   528,   529,   530,   532,   524,   499,   495,   365,
     361,   200,   200,   200,   200,   200,   200,   374,     4,     4,
     200,   200,   200,   536,   202,   200,   200,   353,     4,     4,
     549,   202,     4,   200,     4,   557,   173,   175,   176,   235,
     310,   470,   472,   621,   622,   623,   624,   626,   619,     6,
       3,   466,   462,   482,   478,     4,    22,    23,    24,    25,
     302,   199,   199,   199,   199,   199,   199,   199,     8,     8,
       8,     8,     3,     8,   199,   531,     4,     8,     3,     8,
       8,   129,   130,   131,   539,   199,   199,   199,   199,   220,
     627,     4,   625,     3,     8,   199,     8,     8,   199,   413,
       4,   202,   528,     4,   200,     4,   622,   199,     5,   199,
       7,   628,   629,   630,     3,     6,   174,   177,   178,   179,
     180,   631,   632,   633,   635,   636,   637,   638,   629,   634,
       4,     4,     4,   639,     3,     8,     4,   202,   200,   200,
       4,   632,   199,   199
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   203,   205,   204,   206,   204,   207,   204,   208,   204,
     209,   204,   210,   204,   211,   204,   212,   204,   213,   204,
     214,   204,   215,   204,   216,   204,   217,   204,   218,   204,
     219,   204,   220,   220,   220,   220,   220,   220,   220,   221,
     223,   222,   224,   225,   225,   226,   226,   228,   227,   229,
     229,   230,   230,   232,   231,   233,   233,   234,   234,   235,
     237,   236,   238,   238,   239,   239,   239,   239,   239,   239,
     241,   240,   243,   242,   244,   244,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   247,
     246,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   264,   263,   265,   265,
     265,   265,   265,   267,   266,   269,   268,   271,   270,   273,
     272,   274,   275,   276,   278,   277,   280,   279,   282,   281,
     283,   283,   284,   284,   284,   284,   284,   286,   285,   287,
     289,   288,   291,   290,   293,   292,   294,   294,   295,   295,
     297,   296,   298,   298,   299,   299,   299,   299,   299,   299,
     299,   299,   299,   299,   299,   299,   299,   299,   299,   299,
     299,   299,   299,   299,   299,   301,   300,   302,   302,   302,
     302,   304,   303,   306,   305,   308,   307,   309,   311,   310,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   322,
     321,   323,   325,   324,   327,   326,   329,   328,   331,   330,
     332,   332,   333,   335,   334,   337,   336,   338,   338,   339,
     339,   340,   341,   343,   342,   344,   344,   345,   345,   345,
     346,   347,   349,   348,   351,   350,   352,   352,   353,   353,
     353,   353,   353,   353,   354,   355,   356,   358,   357,   359,
     359,   360,   360,   362,   361,   364,   363,   365,   365,   365,
     366,   366,   368,   367,   370,   369,   372,   371,   373,   373,
     374,   374,   374,   374,   374,   374,   375,   376,   377,   378,
     379,   380,   382,   381,   383,   383,   384,   384,   386,   385,
     388,   387,   389,   389,   390,   390,   390,   390,   390,   390,
     390,   390,   390,   390,   390,   390,   390,   390,   390,   390,
     390,   390,   390,   390,   390,   390,   390,   390,   390,   390,
     390,   390,   390,   390,   390,   390,   390,   390,   390,   390,
     392,   391,   394,   393,   396,   395,   398,   397,   400,   399,
     402,   401,   403,   403,   403,   403,   404,   405,   407,   406,
     408,   408,   409,   409,   411,   410,   412,   412,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   415,   414,   417,   416,   418,   418,   419,   419,   421,
     420,   423,   422,   424,   424,   425,   425,   426,   426,   426,
     426,   426,   426,   426,   426,   426,   426,   427,   428,   429,
     431,   430,   433,   432,   435,   434,   436,   438,   437,   439,
     441,   440,   442,   442,   443,   443,   445,   444,   447,   446,
     448,   448,   449,   449,   450,   450,   450,   450,   450,   450,
     450,   450,   450,   451,   453,   452,   454,   455,   456,   457,
     459,   458,   460,   460,   461,   461,   463,   462,   465,   464,
     466,   466,   467,   467,   467,   467,   467,   467,   467,   469,
     468,   471,   470,   473,   472,   475,   474,   476,   476,   477,
     477,   479,   478,   481,   480,   482,   482,   483,   483,   483,
     483,   483,   483,   483,   483,   483,   483,   483,   485,   484,
     486,   488,   487,   489,   490,   492,   491,   493,   493,   494,
     494,   496,   495,   498,   497,   499,   499,   500,   500,   501,
     501,   501,   501,   501,   501,   501,   501,   501,   501,   501,
     503,   502,   505,   504,   507,   506,   509,   508,   511,   510,
     513,   512,   515,   514,   517,   516,   518,   518,   520,   519,
     522,   521,   523,   523,   525,   524,   526,   526,   527,   527,
     528,   528,   528,   528,   528,   528,   528,   529,   531,   530,
     532,   534,   533,   535,   535,   536,   536,   536,   536,   536,
     536,   536,   536,   536,   538,   537,   539,   539,   539,   540,
     542,   541,   543,   544,   545,   547,   546,   548,   548,   549,
     549,   549,   549,   549,   551,   550,   553,   552,   555,   554,
     556,   556,   557,   557,   557,   557,   557,   557,   558,   560,
     559,   561,   563,   562,   565,   564,   567,   566,   568,   568,
     569,   569,   569,   569,   569,   569,   569,   569,   569,   569,
     569,   569,   569,   569,   569,   569,   569,   569,   570,   572,
     571,   574,   573,   575,   577,   576,   578,   579,   581,   580,
     582,   582,   584,   583,   585,   586,   588,   587,   590,   589,
     592,   591,   594,   593,   596,   595,   598,   597,   600,   599,
     602,   601,   604,   603,   605,   605,   606,   606,   608,   607,
     609,   611,   610,   613,   612,   614,   614,   615,   617,   616,
     618,   618,   620,   619,   621,   621,   622,   622,   622,   622,
     622,   622,   622,   623,   625,   624,   627,   626,   628,   628,
     630,   629,   631,   631,   632,   632,   632,   632,   632,   634,
     633,   635,   636,   637,   639,   638
  };

  const signed char
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     3,     3,     3,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     0,     4,     3,
       0,     6,     0,     6,     0,     6,     0,     1,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     0,
       4,     3,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     0,     4,     0,     6,     1,     3,     1,
       1,     1,     1,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     0,     6,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     1,     1,     1,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     4,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     1,     1,     0,     4,
       0,     6,     1,     3,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     3,
       0,     4,     3,     3,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     3,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     0,     4,
       1,     1,     0,     4,     3,     3,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     4,     1,     3,     1,     1,     0,     6,
       3,     0,     6,     0,     4,     1,     3,     1,     0,     6,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     0,     4,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     0,
       4,     3,     3,     3,     0,     4
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
  "\"tcp-nodelay\"", "\"max-row-errors\"", "\"preferred-lifetime\"",
  "\"min-preferred-lifetime\"", "\"max-preferred-lifetime\"",
  "\"valid-lifetime\"", "\"min-valid-lifetime\"", "\"max-valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"calculate-tee-times\"",
  "\"t1-percent\"", "\"t2-percent\"", "\"decline-probation-period\"",
  "\"server-tag\"", "\"statistic-default-sample-count\"",
  "\"statistic-default-sample-age\"", "\"ddns-send-updates\"",
  "\"ddns-override-no-update\"", "\"ddns-override-client-update\"",
  "\"ddns-replace-client-name\"", "\"ddns-generated-prefix\"",
  "\"ddns-qualifying-suffix\"", "\"store-extended-info\"", "\"subnet6\"",
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
  "\"dhcp4o6-port\"", "\"multi-threading\"", "\"enable-multi-threading\"",
  "\"thread-pool-size\"", "\"packet-queue-size\"", "\"control-socket\"",
  "\"socket-type\"", "\"socket-name\"", "\"dhcp-queue-control\"",
  "\"enable-queue\"", "\"queue-type\"", "\"capacity\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"UDP\"", "\"TCP\"",
  "\"JSON\"", "\"when-present\"", "\"never\"", "\"always\"",
  "\"when-not-present\"", "\"hostname-char-set\"",
  "\"hostname-char-replacement\"", "\"Logging\"", "\"loggers\"",
  "\"output_options\"", "\"output\"", "\"debuglevel\"", "\"severity\"",
  "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"", "\"Dhcp4\"",
  "\"DhcpDdns\"", "\"Control-agent\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP6",
  "SUB_DHCP6", "SUB_INTERFACES6", "SUB_SUBNET6", "SUB_POOL6",
  "SUB_PD_POOL", "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
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
  "preferred_lifetime", "min_preferred_lifetime", "max_preferred_lifetime",
  "valid_lifetime", "min_valid_lifetime", "max_valid_lifetime",
  "renew_timer", "rebind_timer", "calculate_tee_times", "t1_percent",
  "t2_percent", "decline_probation_period", "ddns_send_updates",
  "ddns_override_no_update", "ddns_override_client_update",
  "ddns_replace_client_name", "$@23", "ddns_replace_client_name_value",
  "ddns_generated_prefix", "$@24", "ddns_qualifying_suffix", "$@25",
  "hostname_char_set", "$@26", "hostname_char_replacement", "$@27",
  "store_extended_info", "statistic_default_sample_count",
  "statistic_default_sample_age", "server_tag", "$@28",
  "interfaces_config", "$@29", "sub_interfaces6", "$@30",
  "interfaces_config_params", "interfaces_config_param", "interfaces_list",
  "$@31", "re_detect", "lease_database", "$@32", "hosts_database", "$@33",
  "hosts_databases", "$@34", "database_list", "not_empty_database_list",
  "database", "$@35", "database_map_params", "database_map_param",
  "database_type", "$@36", "db_type", "user", "$@37", "password", "$@38",
  "host", "$@39", "port", "name", "$@40", "persist", "lfc_interval",
  "readonly", "connect_timeout", "reconnect_wait_time", "max_row_errors",
  "request_timeout", "tcp_keepalive", "tcp_nodelay", "contact_points",
  "$@41", "max_reconnect_tries", "keyspace", "$@42", "consistency", "$@43",
  "serial_consistency", "$@44", "sanity_checks", "$@45",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@46",
  "mac_sources", "$@47", "mac_sources_list", "mac_sources_value",
  "duid_id", "string_id", "host_reservation_identifiers", "$@48",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@49",
  "dhcp_multi_threading", "$@50", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@51", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@52",
  "sub_hooks_library", "$@53", "hooks_params", "hooks_param", "library",
  "$@54", "parameters", "$@55", "expired_leases_processing", "$@56",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@57",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@58",
  "sub_subnet6", "$@59", "subnet6_params", "subnet6_param", "subnet",
  "$@60", "interface", "$@61", "interface_id", "$@62", "client_class",
  "$@63", "require_client_classes", "$@64", "reservation_mode", "$@65",
  "hr_mode", "id", "rapid_commit", "shared_networks", "$@66",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@67", "shared_network_params", "shared_network_param",
  "option_def_list", "$@68", "sub_option_def_list", "$@69",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@70", "sub_option_def", "$@71",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@72",
  "option_def_record_types", "$@73", "space", "$@74", "option_def_space",
  "option_def_encapsulate", "$@75", "option_def_array", "option_data_list",
  "$@76", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@77", "sub_option_data", "$@78",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@79",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@80", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@81", "sub_pool6", "$@82",
  "pool_params", "pool_param", "pool_entry", "$@83", "user_context",
  "$@84", "comment", "$@85", "pd_pools_list", "$@86",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@87", "sub_pd_pool", "$@88", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@89", "pd_prefix_len", "excluded_prefix", "$@90",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@91",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@92", "sub_reservation", "$@93", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@94", "prefixes", "$@95", "duid", "$@96", "hw_address", "$@97",
  "hostname", "$@98", "flex_id_value", "$@99",
  "reservation_client_classes", "$@100", "relay", "$@101", "relay_map",
  "ip_address", "$@102", "client_classes", "$@103", "client_classes_list",
  "client_class_entry", "$@104", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@105", "only_if_required",
  "server_id", "$@106", "server_id_params", "server_id_param",
  "server_id_type", "$@107", "duid_type", "htype", "identifier", "$@108",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@109",
  "control_socket_params", "control_socket_param", "socket_type", "$@110",
  "socket_name", "$@111", "dhcp_queue_control", "$@112",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@113", "capacity", "arbitrary_map_entry", "$@114",
  "dhcp_ddns", "$@115", "sub_dhcp_ddns", "$@116", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "qualifying_suffix", "$@117",
  "server_ip", "$@118", "server_port", "sender_ip", "$@119", "sender_port",
  "max_queue_size", "ncr_protocol", "$@120", "ncr_protocol_value",
  "ncr_format", "$@121", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@122",
  "dep_generated_prefix", "$@123", "dep_hostname_char_set", "$@124",
  "dep_hostname_char_replacement", "$@125", "dhcp4_json_object", "$@126",
  "dhcpddns_json_object", "$@127", "control_agent_json_object", "$@128",
  "config_control", "$@129", "sub_config_control", "$@130",
  "config_control_params", "config_control_param", "config_databases",
  "$@131", "config_fetch_wait_time", "logging_object", "$@132",
  "sub_logging", "$@133", "logging_params", "logging_param", "loggers",
  "$@134", "loggers_entries", "logger_entry", "$@135", "logger_params",
  "logger_param", "debuglevel", "severity", "$@136", "output_options_list",
  "$@137", "output_options_list_content", "output_entry", "$@138",
  "output_params_list", "output_params", "output", "$@139", "flush",
  "maxsize", "maxver", "pattern", "$@140", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const short
  Dhcp6Parser::yyrline_[] =
  {
       0,   289,   289,   289,   290,   290,   291,   291,   292,   292,
     293,   293,   294,   294,   295,   295,   296,   296,   297,   297,
     298,   298,   299,   299,   300,   300,   301,   301,   302,   302,
     303,   303,   311,   312,   313,   314,   315,   316,   317,   320,
     325,   325,   336,   339,   340,   343,   347,   354,   354,   361,
     362,   365,   369,   376,   376,   383,   384,   387,   391,   402,
     412,   412,   428,   429,   433,   434,   435,   436,   437,   438,
     441,   441,   456,   456,   465,   466,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   521,   522,   523,   526,
     526,   534,   539,   544,   549,   554,   559,   564,   569,   574,
     579,   584,   589,   594,   599,   604,   609,   609,   617,   620,
     623,   626,   629,   635,   635,   643,   643,   651,   651,   659,
     659,   667,   672,   677,   682,   682,   690,   690,   701,   701,
     710,   711,   714,   715,   716,   717,   718,   721,   721,   731,
     736,   736,   748,   748,   760,   760,   770,   771,   774,   775,
     778,   778,   788,   789,   792,   793,   794,   795,   796,   797,
     798,   799,   800,   801,   802,   803,   804,   805,   806,   807,
     808,   809,   810,   811,   812,   815,   815,   822,   823,   824,
     825,   828,   828,   836,   836,   844,   844,   852,   857,   857,
     865,   870,   875,   880,   885,   890,   895,   900,   905,   910,
     910,   918,   923,   923,   931,   931,   939,   939,   947,   947,
     957,   958,   960,   962,   962,   980,   980,   990,   991,   994,
     995,   998,  1003,  1008,  1008,  1018,  1019,  1022,  1023,  1024,
    1027,  1032,  1039,  1039,  1051,  1051,  1063,  1064,  1067,  1068,
    1069,  1070,  1071,  1072,  1075,  1080,  1085,  1090,  1090,  1100,
    1101,  1104,  1105,  1108,  1108,  1118,  1118,  1128,  1129,  1130,
    1133,  1134,  1137,  1137,  1145,  1145,  1153,  1153,  1164,  1165,
    1168,  1169,  1170,  1171,  1172,  1173,  1176,  1181,  1186,  1191,
    1196,  1201,  1209,  1209,  1222,  1223,  1226,  1227,  1234,  1234,
    1260,  1260,  1271,  1272,  1276,  1277,  1278,  1279,  1280,  1281,
    1282,  1283,  1284,  1285,  1286,  1287,  1288,  1289,  1290,  1291,
    1292,  1293,  1294,  1295,  1296,  1297,  1298,  1299,  1300,  1301,
    1302,  1303,  1304,  1305,  1306,  1307,  1308,  1309,  1310,  1311,
    1314,  1314,  1322,  1322,  1330,  1330,  1338,  1338,  1346,  1346,
    1356,  1356,  1363,  1364,  1365,  1366,  1369,  1374,  1381,  1381,
    1392,  1393,  1397,  1398,  1401,  1401,  1409,  1410,  1413,  1414,
    1415,  1416,  1417,  1418,  1419,  1420,  1421,  1422,  1423,  1424,
    1425,  1426,  1427,  1428,  1429,  1430,  1431,  1432,  1433,  1434,
    1435,  1436,  1437,  1438,  1439,  1440,  1441,  1442,  1443,  1444,
    1445,  1452,  1452,  1465,  1465,  1474,  1475,  1478,  1479,  1484,
    1484,  1499,  1499,  1513,  1514,  1517,  1518,  1521,  1522,  1523,
    1524,  1525,  1526,  1527,  1528,  1529,  1530,  1533,  1535,  1540,
    1542,  1542,  1550,  1550,  1558,  1558,  1566,  1568,  1568,  1576,
    1585,  1585,  1597,  1598,  1603,  1604,  1609,  1609,  1621,  1621,
    1633,  1634,  1639,  1640,  1645,  1646,  1647,  1648,  1649,  1650,
    1651,  1652,  1653,  1656,  1658,  1658,  1666,  1668,  1670,  1675,
    1683,  1683,  1695,  1696,  1699,  1700,  1703,  1703,  1713,  1713,
    1723,  1724,  1727,  1728,  1729,  1730,  1731,  1732,  1733,  1736,
    1736,  1744,  1744,  1769,  1769,  1799,  1799,  1811,  1812,  1815,
    1816,  1819,  1819,  1831,  1831,  1843,  1844,  1847,  1848,  1849,
    1850,  1851,  1852,  1853,  1854,  1855,  1856,  1857,  1860,  1860,
    1868,  1873,  1873,  1881,  1886,  1894,  1894,  1904,  1905,  1908,
    1909,  1912,  1912,  1921,  1921,  1930,  1931,  1934,  1935,  1939,
    1940,  1941,  1942,  1943,  1944,  1945,  1946,  1947,  1948,  1949,
    1952,  1952,  1962,  1962,  1972,  1972,  1980,  1980,  1988,  1988,
    1996,  1996,  2004,  2004,  2017,  2017,  2027,  2028,  2031,  2031,
    2042,  2042,  2052,  2053,  2056,  2056,  2066,  2067,  2070,  2071,
    2074,  2075,  2076,  2077,  2078,  2079,  2080,  2083,  2085,  2085,
    2093,  2101,  2101,  2113,  2114,  2117,  2118,  2119,  2120,  2121,
    2122,  2123,  2124,  2125,  2128,  2128,  2135,  2136,  2137,  2140,
    2145,  2145,  2153,  2158,  2165,  2172,  2172,  2182,  2183,  2186,
    2187,  2188,  2189,  2190,  2193,  2193,  2201,  2201,  2212,  2212,
    2224,  2225,  2228,  2229,  2230,  2231,  2232,  2233,  2236,  2241,
    2241,  2249,  2254,  2254,  2263,  2263,  2275,  2275,  2285,  2286,
    2289,  2290,  2291,  2292,  2293,  2294,  2295,  2296,  2297,  2298,
    2299,  2300,  2301,  2302,  2303,  2304,  2305,  2306,  2309,  2314,
    2314,  2322,  2322,  2330,  2335,  2335,  2343,  2348,  2353,  2353,
    2361,  2362,  2365,  2365,  2374,  2380,  2386,  2386,  2394,  2394,
    2403,  2403,  2412,  2412,  2423,  2423,  2430,  2430,  2437,  2437,
    2446,  2446,  2457,  2457,  2467,  2468,  2472,  2473,  2476,  2476,
    2486,  2496,  2496,  2506,  2506,  2517,  2518,  2522,  2526,  2526,
    2538,  2539,  2543,  2543,  2551,  2552,  2555,  2556,  2557,  2558,
    2559,  2560,  2561,  2564,  2569,  2569,  2577,  2577,  2587,  2588,
    2591,  2591,  2599,  2600,  2603,  2604,  2605,  2606,  2607,  2610,
    2610,  2618,  2623,  2628,  2633,  2633
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
#line 5660 "dhcp6_parser.cc"

#line 2641 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
