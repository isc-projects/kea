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
      case 223: // value
      case 227: // map_value
      case 268: // ddns_replace_client_name_value
      case 308: // db_type
      case 413: // hr_mode
      case 549: // duid_type
      case 592: // ncr_protocol_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 206: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 205: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 204: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 203: // "constant string"
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
      case 223: // value
      case 227: // map_value
      case 268: // ddns_replace_client_name_value
      case 308: // db_type
      case 413: // hr_mode
      case 549: // duid_type
      case 592: // ncr_protocol_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 206: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 205: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 204: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 203: // "constant string"
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
      case 223: // value
      case 227: // map_value
      case 268: // ddns_replace_client_name_value
      case 308: // db_type
      case 413: // hr_mode
      case 549: // duid_type
      case 592: // ncr_protocol_value
        value.copy< ElementPtr > (that.value);
        break;

      case 206: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 205: // "floating point"
        value.copy< double > (that.value);
        break;

      case 204: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 203: // "constant string"
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
      case 223: // value
      case 227: // map_value
      case 268: // ddns_replace_client_name_value
      case 308: // db_type
      case 413: // hr_mode
      case 549: // duid_type
      case 592: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 206: // "boolean"
        value.move< bool > (that.value);
        break;

      case 205: // "floating point"
        value.move< double > (that.value);
        break;

      case 204: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 203: // "constant string"
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
      case 203: // "constant string"
#line 284 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 443 "dhcp6_parser.cc"
        break;

      case 204: // "integer"
#line 284 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 449 "dhcp6_parser.cc"
        break;

      case 205: // "floating point"
#line 284 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 455 "dhcp6_parser.cc"
        break;

      case 206: // "boolean"
#line 284 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 461 "dhcp6_parser.cc"
        break;

      case 223: // value
#line 284 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 467 "dhcp6_parser.cc"
        break;

      case 227: // map_value
#line 284 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 473 "dhcp6_parser.cc"
        break;

      case 268: // ddns_replace_client_name_value
#line 284 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 479 "dhcp6_parser.cc"
        break;

      case 308: // db_type
#line 284 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 485 "dhcp6_parser.cc"
        break;

      case 413: // hr_mode
#line 284 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 491 "dhcp6_parser.cc"
        break;

      case 549: // duid_type
#line 284 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 497 "dhcp6_parser.cc"
        break;

      case 592: // ncr_protocol_value
#line 284 "dhcp6_parser.yy"
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
      case 223: // value
      case 227: // map_value
      case 268: // ddns_replace_client_name_value
      case 308: // db_type
      case 413: // hr_mode
      case 549: // duid_type
      case 592: // ncr_protocol_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 206: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 205: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 204: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 203: // "constant string"
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
#line 293 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 770 "dhcp6_parser.cc"
    break;

  case 4:
#line 294 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 776 "dhcp6_parser.cc"
    break;

  case 6:
#line 295 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 782 "dhcp6_parser.cc"
    break;

  case 8:
#line 296 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 788 "dhcp6_parser.cc"
    break;

  case 10:
#line 297 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 794 "dhcp6_parser.cc"
    break;

  case 12:
#line 298 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 800 "dhcp6_parser.cc"
    break;

  case 14:
#line 299 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 806 "dhcp6_parser.cc"
    break;

  case 16:
#line 300 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 812 "dhcp6_parser.cc"
    break;

  case 18:
#line 301 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 818 "dhcp6_parser.cc"
    break;

  case 20:
#line 302 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 824 "dhcp6_parser.cc"
    break;

  case 22:
#line 303 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 830 "dhcp6_parser.cc"
    break;

  case 24:
#line 304 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 836 "dhcp6_parser.cc"
    break;

  case 26:
#line 305 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 842 "dhcp6_parser.cc"
    break;

  case 28:
#line 306 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 848 "dhcp6_parser.cc"
    break;

  case 30:
#line 314 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 854 "dhcp6_parser.cc"
    break;

  case 31:
#line 315 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 860 "dhcp6_parser.cc"
    break;

  case 32:
#line 316 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 866 "dhcp6_parser.cc"
    break;

  case 33:
#line 317 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 872 "dhcp6_parser.cc"
    break;

  case 34:
#line 318 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 878 "dhcp6_parser.cc"
    break;

  case 35:
#line 319 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 884 "dhcp6_parser.cc"
    break;

  case 36:
#line 320 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 890 "dhcp6_parser.cc"
    break;

  case 37:
#line 323 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 899 "dhcp6_parser.cc"
    break;

  case 38:
#line 328 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 910 "dhcp6_parser.cc"
    break;

  case 39:
#line 333 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 920 "dhcp6_parser.cc"
    break;

  case 40:
#line 339 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 926 "dhcp6_parser.cc"
    break;

  case 43:
#line 346 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 936 "dhcp6_parser.cc"
    break;

  case 44:
#line 351 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 947 "dhcp6_parser.cc"
    break;

  case 45:
#line 359 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 956 "dhcp6_parser.cc"
    break;

  case 46:
#line 362 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 964 "dhcp6_parser.cc"
    break;

  case 49:
#line 370 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 973 "dhcp6_parser.cc"
    break;

  case 50:
#line 374 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 982 "dhcp6_parser.cc"
    break;

  case 51:
#line 381 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 990 "dhcp6_parser.cc"
    break;

  case 52:
#line 383 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 999 "dhcp6_parser.cc"
    break;

  case 55:
#line 392 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1008 "dhcp6_parser.cc"
    break;

  case 56:
#line 396 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1017 "dhcp6_parser.cc"
    break;

  case 57:
#line 407 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1028 "dhcp6_parser.cc"
    break;

  case 58:
#line 416 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1039 "dhcp6_parser.cc"
    break;

  case 59:
#line 421 "dhcp6_parser.yy"
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
#line 431 "dhcp6_parser.yy"
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
#line 440 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1077 "dhcp6_parser.cc"
    break;

  case 62:
#line 448 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1087 "dhcp6_parser.cc"
    break;

  case 63:
#line 452 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1096 "dhcp6_parser.cc"
    break;

  case 127:
#line 526 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1105 "dhcp6_parser.cc"
    break;

  case 128:
#line 529 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1115 "dhcp6_parser.cc"
    break;

  case 129:
#line 535 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1125 "dhcp6_parser.cc"
    break;

  case 130:
#line 541 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1135 "dhcp6_parser.cc"
    break;

  case 131:
#line 547 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1145 "dhcp6_parser.cc"
    break;

  case 132:
#line 553 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1155 "dhcp6_parser.cc"
    break;

  case 133:
#line 559 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1165 "dhcp6_parser.cc"
    break;

  case 134:
#line 565 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1175 "dhcp6_parser.cc"
    break;

  case 135:
#line 571 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1185 "dhcp6_parser.cc"
    break;

  case 136:
#line 577 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1195 "dhcp6_parser.cc"
    break;

  case 137:
#line 583 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1205 "dhcp6_parser.cc"
    break;

  case 138:
#line 589 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1215 "dhcp6_parser.cc"
    break;

  case 139:
#line 595 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1225 "dhcp6_parser.cc"
    break;

  case 140:
#line 601 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1235 "dhcp6_parser.cc"
    break;

  case 141:
#line 607 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1245 "dhcp6_parser.cc"
    break;

  case 142:
#line 613 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1255 "dhcp6_parser.cc"
    break;

  case 143:
#line 619 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1265 "dhcp6_parser.cc"
    break;

  case 144:
#line 625 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1275 "dhcp6_parser.cc"
    break;

  case 145:
#line 631 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1285 "dhcp6_parser.cc"
    break;

  case 146:
#line 637 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1294 "dhcp6_parser.cc"
    break;

  case 147:
#line 640 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1303 "dhcp6_parser.cc"
    break;

  case 148:
#line 646 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1311 "dhcp6_parser.cc"
    break;

  case 149:
#line 649 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1319 "dhcp6_parser.cc"
    break;

  case 150:
#line 652 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1327 "dhcp6_parser.cc"
    break;

  case 151:
#line 655 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1335 "dhcp6_parser.cc"
    break;

  case 152:
#line 658 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1344 "dhcp6_parser.cc"
    break;

  case 153:
#line 664 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1353 "dhcp6_parser.cc"
    break;

  case 154:
#line 667 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1363 "dhcp6_parser.cc"
    break;

  case 155:
#line 673 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1372 "dhcp6_parser.cc"
    break;

  case 156:
#line 676 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1382 "dhcp6_parser.cc"
    break;

  case 157:
#line 682 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1392 "dhcp6_parser.cc"
    break;

  case 158:
#line 688 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1402 "dhcp6_parser.cc"
    break;

  case 159:
#line 694 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1411 "dhcp6_parser.cc"
    break;

  case 160:
#line 697 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1421 "dhcp6_parser.cc"
    break;

  case 161:
#line 703 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1430 "dhcp6_parser.cc"
    break;

  case 162:
#line 706 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1440 "dhcp6_parser.cc"
    break;

  case 163:
#line 712 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1450 "dhcp6_parser.cc"
    break;

  case 164:
#line 718 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 165:
#line 724 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1470 "dhcp6_parser.cc"
    break;

  case 166:
#line 730 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1479 "dhcp6_parser.cc"
    break;

  case 167:
#line 733 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1489 "dhcp6_parser.cc"
    break;

  case 168:
#line 739 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1499 "dhcp6_parser.cc"
    break;

  case 169:
#line 745 "dhcp6_parser.yy"
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
#line 751 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1521 "dhcp6_parser.cc"
    break;

  case 171:
#line 757 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1531 "dhcp6_parser.cc"
    break;

  case 172:
#line 761 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1540 "dhcp6_parser.cc"
    break;

  case 180:
#line 777 "dhcp6_parser.yy"
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
#line 783 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1561 "dhcp6_parser.cc"
    break;

  case 182:
#line 788 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1571 "dhcp6_parser.cc"
    break;

  case 183:
#line 794 "dhcp6_parser.yy"
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
#line 800 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1594 "dhcp6_parser.cc"
    break;

  case 185:
#line 807 "dhcp6_parser.yy"
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
#line 813 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1617 "dhcp6_parser.cc"
    break;

  case 187:
#line 820 "dhcp6_parser.yy"
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
#line 826 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1638 "dhcp6_parser.cc"
    break;

  case 193:
#line 839 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1648 "dhcp6_parser.cc"
    break;

  case 194:
#line 843 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1658 "dhcp6_parser.cc"
    break;

  case 219:
#line 877 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1667 "dhcp6_parser.cc"
    break;

  case 220:
#line 880 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1676 "dhcp6_parser.cc"
    break;

  case 221:
#line 885 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1682 "dhcp6_parser.cc"
    break;

  case 222:
#line 886 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1688 "dhcp6_parser.cc"
    break;

  case 223:
#line 887 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1694 "dhcp6_parser.cc"
    break;

  case 224:
#line 888 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1700 "dhcp6_parser.cc"
    break;

  case 225:
#line 891 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1709 "dhcp6_parser.cc"
    break;

  case 226:
#line 894 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1719 "dhcp6_parser.cc"
    break;

  case 227:
#line 900 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1728 "dhcp6_parser.cc"
    break;

  case 228:
#line 903 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1738 "dhcp6_parser.cc"
    break;

  case 229:
#line 909 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1747 "dhcp6_parser.cc"
    break;

  case 230:
#line 912 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1757 "dhcp6_parser.cc"
    break;

  case 231:
#line 918 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1767 "dhcp6_parser.cc"
    break;

  case 232:
#line 924 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1776 "dhcp6_parser.cc"
    break;

  case 233:
#line 927 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1786 "dhcp6_parser.cc"
    break;

  case 234:
#line 933 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1796 "dhcp6_parser.cc"
    break;

  case 235:
#line 939 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1806 "dhcp6_parser.cc"
    break;

  case 236:
#line 945 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1816 "dhcp6_parser.cc"
    break;

  case 237:
#line 951 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1826 "dhcp6_parser.cc"
    break;

  case 238:
#line 957 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1836 "dhcp6_parser.cc"
    break;

  case 239:
#line 963 "dhcp6_parser.yy"
                                                               {
    ctx.unique("disable-dhcp-on-db-loss", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("disable-dhcp-on-db-loss", n);
}
#line 1846 "dhcp6_parser.cc"
    break;

  case 240:
#line 969 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1856 "dhcp6_parser.cc"
    break;

  case 241:
#line 975 "dhcp6_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1866 "dhcp6_parser.cc"
    break;

  case 242:
#line 981 "dhcp6_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1876 "dhcp6_parser.cc"
    break;

  case 243:
#line 987 "dhcp6_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1886 "dhcp6_parser.cc"
    break;

  case 244:
#line 993 "dhcp6_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1895 "dhcp6_parser.cc"
    break;

  case 245:
#line 996 "dhcp6_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1905 "dhcp6_parser.cc"
    break;

  case 246:
#line 1002 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1915 "dhcp6_parser.cc"
    break;

  case 247:
#line 1008 "dhcp6_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1924 "dhcp6_parser.cc"
    break;

  case 248:
#line 1011 "dhcp6_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1934 "dhcp6_parser.cc"
    break;

  case 249:
#line 1017 "dhcp6_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1943 "dhcp6_parser.cc"
    break;

  case 250:
#line 1020 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1953 "dhcp6_parser.cc"
    break;

  case 251:
#line 1026 "dhcp6_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1962 "dhcp6_parser.cc"
    break;

  case 252:
#line 1029 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1972 "dhcp6_parser.cc"
    break;

  case 253:
#line 1035 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1984 "dhcp6_parser.cc"
    break;

  case 254:
#line 1041 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1993 "dhcp6_parser.cc"
    break;

  case 258:
#line 1051 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2002 "dhcp6_parser.cc"
    break;

  case 259:
#line 1054 "dhcp6_parser.yy"
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
#line 2022 "dhcp6_parser.cc"
    break;

  case 260:
#line 1070 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2034 "dhcp6_parser.cc"
    break;

  case 261:
#line 1076 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2043 "dhcp6_parser.cc"
    break;

  case 266:
#line 1089 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2052 "dhcp6_parser.cc"
    break;

  case 267:
#line 1094 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2061 "dhcp6_parser.cc"
    break;

  case 268:
#line 1099 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2073 "dhcp6_parser.cc"
    break;

  case 269:
#line 1105 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2082 "dhcp6_parser.cc"
    break;

  case 275:
#line 1119 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2091 "dhcp6_parser.cc"
    break;

  case 276:
#line 1124 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2100 "dhcp6_parser.cc"
    break;

  case 277:
#line 1131 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2112 "dhcp6_parser.cc"
    break;

  case 278:
#line 1137 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2121 "dhcp6_parser.cc"
    break;

  case 279:
#line 1144 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2133 "dhcp6_parser.cc"
    break;

  case 280:
#line 1150 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2144 "dhcp6_parser.cc"
    break;

  case 289:
#line 1169 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2154 "dhcp6_parser.cc"
    break;

  case 290:
#line 1175 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2164 "dhcp6_parser.cc"
    break;

  case 291:
#line 1181 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2174 "dhcp6_parser.cc"
    break;

  case 292:
#line 1187 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2186 "dhcp6_parser.cc"
    break;

  case 293:
#line 1193 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2195 "dhcp6_parser.cc"
    break;

  case 298:
#line 1206 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2205 "dhcp6_parser.cc"
    break;

  case 299:
#line 1210 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2215 "dhcp6_parser.cc"
    break;

  case 300:
#line 1216 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2225 "dhcp6_parser.cc"
    break;

  case 301:
#line 1220 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2235 "dhcp6_parser.cc"
    break;

  case 307:
#line 1235 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2244 "dhcp6_parser.cc"
    break;

  case 308:
#line 1238 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2254 "dhcp6_parser.cc"
    break;

  case 309:
#line 1244 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2263 "dhcp6_parser.cc"
    break;

  case 310:
#line 1247 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2272 "dhcp6_parser.cc"
    break;

  case 311:
#line 1253 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2284 "dhcp6_parser.cc"
    break;

  case 312:
#line 1259 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2294 "dhcp6_parser.cc"
    break;

  case 321:
#line 1277 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2304 "dhcp6_parser.cc"
    break;

  case 322:
#line 1283 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2314 "dhcp6_parser.cc"
    break;

  case 323:
#line 1289 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2324 "dhcp6_parser.cc"
    break;

  case 324:
#line 1295 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2334 "dhcp6_parser.cc"
    break;

  case 325:
#line 1301 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2344 "dhcp6_parser.cc"
    break;

  case 326:
#line 1307 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2354 "dhcp6_parser.cc"
    break;

  case 327:
#line 1316 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2366 "dhcp6_parser.cc"
    break;

  case 328:
#line 1322 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2375 "dhcp6_parser.cc"
    break;

  case 333:
#line 1342 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2385 "dhcp6_parser.cc"
    break;

  case 334:
#line 1346 "dhcp6_parser.yy"
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
#line 2411 "dhcp6_parser.cc"
    break;

  case 335:
#line 1368 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2421 "dhcp6_parser.cc"
    break;

  case 336:
#line 1372 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2431 "dhcp6_parser.cc"
    break;

  case 382:
#line 1429 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2440 "dhcp6_parser.cc"
    break;

  case 383:
#line 1432 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2450 "dhcp6_parser.cc"
    break;

  case 384:
#line 1438 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2459 "dhcp6_parser.cc"
    break;

  case 385:
#line 1441 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2469 "dhcp6_parser.cc"
    break;

  case 386:
#line 1447 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2478 "dhcp6_parser.cc"
    break;

  case 387:
#line 1450 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2488 "dhcp6_parser.cc"
    break;

  case 388:
#line 1456 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2497 "dhcp6_parser.cc"
    break;

  case 389:
#line 1459 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2507 "dhcp6_parser.cc"
    break;

  case 390:
#line 1465 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2519 "dhcp6_parser.cc"
    break;

  case 391:
#line 1471 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2528 "dhcp6_parser.cc"
    break;

  case 392:
#line 1476 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2538 "dhcp6_parser.cc"
    break;

  case 393:
#line 1482 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2548 "dhcp6_parser.cc"
    break;

  case 394:
#line 1488 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2558 "dhcp6_parser.cc"
    break;

  case 395:
#line 1494 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2567 "dhcp6_parser.cc"
    break;

  case 396:
#line 1497 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2576 "dhcp6_parser.cc"
    break;

  case 397:
#line 1502 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2582 "dhcp6_parser.cc"
    break;

  case 398:
#line 1503 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2588 "dhcp6_parser.cc"
    break;

  case 399:
#line 1504 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2594 "dhcp6_parser.cc"
    break;

  case 400:
#line 1505 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2600 "dhcp6_parser.cc"
    break;

  case 401:
#line 1508 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2610 "dhcp6_parser.cc"
    break;

  case 402:
#line 1514 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2620 "dhcp6_parser.cc"
    break;

  case 403:
#line 1522 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2632 "dhcp6_parser.cc"
    break;

  case 404:
#line 1528 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2641 "dhcp6_parser.cc"
    break;

  case 409:
#line 1543 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2651 "dhcp6_parser.cc"
    break;

  case 410:
#line 1547 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2659 "dhcp6_parser.cc"
    break;

  case 453:
#line 1601 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2671 "dhcp6_parser.cc"
    break;

  case 454:
#line 1607 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2680 "dhcp6_parser.cc"
    break;

  case 455:
#line 1615 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2689 "dhcp6_parser.cc"
    break;

  case 456:
#line 1618 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2697 "dhcp6_parser.cc"
    break;

  case 461:
#line 1634 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2707 "dhcp6_parser.cc"
    break;

  case 462:
#line 1638 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2719 "dhcp6_parser.cc"
    break;

  case 463:
#line 1649 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2729 "dhcp6_parser.cc"
    break;

  case 464:
#line 1653 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2741 "dhcp6_parser.cc"
    break;

  case 480:
#line 1685 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2751 "dhcp6_parser.cc"
    break;

  case 482:
#line 1693 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2760 "dhcp6_parser.cc"
    break;

  case 483:
#line 1696 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2770 "dhcp6_parser.cc"
    break;

  case 484:
#line 1702 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2779 "dhcp6_parser.cc"
    break;

  case 485:
#line 1705 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2789 "dhcp6_parser.cc"
    break;

  case 486:
#line 1711 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2798 "dhcp6_parser.cc"
    break;

  case 487:
#line 1714 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2808 "dhcp6_parser.cc"
    break;

  case 489:
#line 1722 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2817 "dhcp6_parser.cc"
    break;

  case 490:
#line 1725 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2827 "dhcp6_parser.cc"
    break;

  case 491:
#line 1731 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2837 "dhcp6_parser.cc"
    break;

  case 492:
#line 1741 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2849 "dhcp6_parser.cc"
    break;

  case 493:
#line 1747 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2858 "dhcp6_parser.cc"
    break;

  case 498:
#line 1766 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2868 "dhcp6_parser.cc"
    break;

  case 499:
#line 1770 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2877 "dhcp6_parser.cc"
    break;

  case 500:
#line 1778 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2887 "dhcp6_parser.cc"
    break;

  case 501:
#line 1782 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2896 "dhcp6_parser.cc"
    break;

  case 516:
#line 1815 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2905 "dhcp6_parser.cc"
    break;

  case 517:
#line 1818 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2915 "dhcp6_parser.cc"
    break;

  case 520:
#line 1828 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2925 "dhcp6_parser.cc"
    break;

  case 521:
#line 1834 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2935 "dhcp6_parser.cc"
    break;

  case 522:
#line 1843 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2947 "dhcp6_parser.cc"
    break;

  case 523:
#line 1849 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2956 "dhcp6_parser.cc"
    break;

  case 528:
#line 1864 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2966 "dhcp6_parser.cc"
    break;

  case 529:
#line 1868 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2976 "dhcp6_parser.cc"
    break;

  case 530:
#line 1874 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2986 "dhcp6_parser.cc"
    break;

  case 531:
#line 1878 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2996 "dhcp6_parser.cc"
    break;

  case 541:
#line 1897 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3005 "dhcp6_parser.cc"
    break;

  case 542:
#line 1900 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3015 "dhcp6_parser.cc"
    break;

  case 543:
#line 1906 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3023 "dhcp6_parser.cc"
    break;

  case 544:
#line 1908 "dhcp6_parser.yy"
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
#line 3050 "dhcp6_parser.cc"
    break;

  case 545:
#line 1931 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3058 "dhcp6_parser.cc"
    break;

  case 546:
#line 1933 "dhcp6_parser.yy"
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
#line 3087 "dhcp6_parser.cc"
    break;

  case 547:
#line 1961 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3099 "dhcp6_parser.cc"
    break;

  case 548:
#line 1967 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3108 "dhcp6_parser.cc"
    break;

  case 553:
#line 1982 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3118 "dhcp6_parser.cc"
    break;

  case 554:
#line 1986 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3130 "dhcp6_parser.cc"
    break;

  case 555:
#line 1994 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3140 "dhcp6_parser.cc"
    break;

  case 556:
#line 1998 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3152 "dhcp6_parser.cc"
    break;

  case 570:
#line 2023 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3161 "dhcp6_parser.cc"
    break;

  case 571:
#line 2026 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3171 "dhcp6_parser.cc"
    break;

  case 572:
#line 2032 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3181 "dhcp6_parser.cc"
    break;

  case 573:
#line 2038 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3190 "dhcp6_parser.cc"
    break;

  case 574:
#line 2041 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3200 "dhcp6_parser.cc"
    break;

  case 575:
#line 2047 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3210 "dhcp6_parser.cc"
    break;

  case 576:
#line 2053 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3220 "dhcp6_parser.cc"
    break;

  case 577:
#line 2062 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3232 "dhcp6_parser.cc"
    break;

  case 578:
#line 2068 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3241 "dhcp6_parser.cc"
    break;

  case 583:
#line 2081 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3251 "dhcp6_parser.cc"
    break;

  case 584:
#line 2085 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3260 "dhcp6_parser.cc"
    break;

  case 585:
#line 2090 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3270 "dhcp6_parser.cc"
    break;

  case 586:
#line 2094 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3279 "dhcp6_parser.cc"
    break;

  case 602:
#line 2121 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3291 "dhcp6_parser.cc"
    break;

  case 603:
#line 2127 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3300 "dhcp6_parser.cc"
    break;

  case 604:
#line 2132 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3312 "dhcp6_parser.cc"
    break;

  case 605:
#line 2138 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3321 "dhcp6_parser.cc"
    break;

  case 606:
#line 2143 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3330 "dhcp6_parser.cc"
    break;

  case 607:
#line 2146 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3340 "dhcp6_parser.cc"
    break;

  case 608:
#line 2152 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3349 "dhcp6_parser.cc"
    break;

  case 609:
#line 2155 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3359 "dhcp6_parser.cc"
    break;

  case 610:
#line 2161 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3368 "dhcp6_parser.cc"
    break;

  case 611:
#line 2164 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3378 "dhcp6_parser.cc"
    break;

  case 612:
#line 2170 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3387 "dhcp6_parser.cc"
    break;

  case 613:
#line 2173 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3397 "dhcp6_parser.cc"
    break;

  case 614:
#line 2179 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3409 "dhcp6_parser.cc"
    break;

  case 615:
#line 2185 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3418 "dhcp6_parser.cc"
    break;

  case 616:
#line 2193 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3430 "dhcp6_parser.cc"
    break;

  case 617:
#line 2199 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3439 "dhcp6_parser.cc"
    break;

  case 620:
#line 2208 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3448 "dhcp6_parser.cc"
    break;

  case 621:
#line 2211 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3458 "dhcp6_parser.cc"
    break;

  case 622:
#line 2220 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3470 "dhcp6_parser.cc"
    break;

  case 623:
#line 2226 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3479 "dhcp6_parser.cc"
    break;

  case 626:
#line 2235 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3489 "dhcp6_parser.cc"
    break;

  case 627:
#line 2239 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3499 "dhcp6_parser.cc"
    break;

  case 640:
#line 2264 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3508 "dhcp6_parser.cc"
    break;

  case 641:
#line 2267 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3518 "dhcp6_parser.cc"
    break;

  case 642:
#line 2273 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3528 "dhcp6_parser.cc"
    break;

  case 643:
#line 2282 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3540 "dhcp6_parser.cc"
    break;

  case 644:
#line 2288 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3551 "dhcp6_parser.cc"
    break;

  case 656:
#line 2310 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3560 "dhcp6_parser.cc"
    break;

  case 657:
#line 2313 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3569 "dhcp6_parser.cc"
    break;

  case 658:
#line 2318 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3575 "dhcp6_parser.cc"
    break;

  case 659:
#line 2319 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3581 "dhcp6_parser.cc"
    break;

  case 660:
#line 2320 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3587 "dhcp6_parser.cc"
    break;

  case 661:
#line 2323 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3597 "dhcp6_parser.cc"
    break;

  case 662:
#line 2329 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3606 "dhcp6_parser.cc"
    break;

  case 663:
#line 2332 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3616 "dhcp6_parser.cc"
    break;

  case 664:
#line 2338 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3626 "dhcp6_parser.cc"
    break;

  case 665:
#line 2344 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3636 "dhcp6_parser.cc"
    break;

  case 666:
#line 2352 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3646 "dhcp6_parser.cc"
    break;

  case 667:
#line 2360 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3658 "dhcp6_parser.cc"
    break;

  case 668:
#line 2366 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3667 "dhcp6_parser.cc"
    break;

  case 676:
#line 2382 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3676 "dhcp6_parser.cc"
    break;

  case 677:
#line 2385 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3686 "dhcp6_parser.cc"
    break;

  case 678:
#line 2391 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3695 "dhcp6_parser.cc"
    break;

  case 679:
#line 2394 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3705 "dhcp6_parser.cc"
    break;

  case 680:
#line 2403 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3717 "dhcp6_parser.cc"
    break;

  case 681:
#line 2409 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3728 "dhcp6_parser.cc"
    break;

  case 690:
#line 2428 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3738 "dhcp6_parser.cc"
    break;

  case 691:
#line 2434 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3747 "dhcp6_parser.cc"
    break;

  case 692:
#line 2437 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3757 "dhcp6_parser.cc"
    break;

  case 693:
#line 2443 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3767 "dhcp6_parser.cc"
    break;

  case 694:
#line 2449 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3776 "dhcp6_parser.cc"
    break;

  case 695:
#line 2452 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3785 "dhcp6_parser.cc"
    break;

  case 696:
#line 2459 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3797 "dhcp6_parser.cc"
    break;

  case 697:
#line 2465 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3808 "dhcp6_parser.cc"
    break;

  case 698:
#line 2472 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3818 "dhcp6_parser.cc"
    break;

  case 699:
#line 2476 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3828 "dhcp6_parser.cc"
    break;

  case 720:
#line 2506 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3838 "dhcp6_parser.cc"
    break;

  case 721:
#line 2513 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3847 "dhcp6_parser.cc"
    break;

  case 722:
#line 2516 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3857 "dhcp6_parser.cc"
    break;

  case 723:
#line 2522 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3866 "dhcp6_parser.cc"
    break;

  case 724:
#line 2525 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3876 "dhcp6_parser.cc"
    break;

  case 725:
#line 2531 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3886 "dhcp6_parser.cc"
    break;

  case 726:
#line 2537 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3895 "dhcp6_parser.cc"
    break;

  case 727:
#line 2540 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3905 "dhcp6_parser.cc"
    break;

  case 728:
#line 2546 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3915 "dhcp6_parser.cc"
    break;

  case 729:
#line 2552 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3925 "dhcp6_parser.cc"
    break;

  case 730:
#line 2558 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3934 "dhcp6_parser.cc"
    break;

  case 731:
#line 2561 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3943 "dhcp6_parser.cc"
    break;

  case 732:
#line 2567 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3949 "dhcp6_parser.cc"
    break;

  case 733:
#line 2568 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3955 "dhcp6_parser.cc"
    break;

  case 734:
#line 2571 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3964 "dhcp6_parser.cc"
    break;

  case 735:
#line 2574 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3974 "dhcp6_parser.cc"
    break;

  case 736:
#line 2581 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3984 "dhcp6_parser.cc"
    break;

  case 737:
#line 2588 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3994 "dhcp6_parser.cc"
    break;

  case 738:
#line 2595 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4003 "dhcp6_parser.cc"
    break;

  case 739:
#line 2598 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4012 "dhcp6_parser.cc"
    break;

  case 740:
#line 2604 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4021 "dhcp6_parser.cc"
    break;

  case 741:
#line 2607 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4031 "dhcp6_parser.cc"
    break;

  case 742:
#line 2614 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4040 "dhcp6_parser.cc"
    break;

  case 743:
#line 2617 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4050 "dhcp6_parser.cc"
    break;

  case 744:
#line 2624 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4059 "dhcp6_parser.cc"
    break;

  case 745:
#line 2627 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4069 "dhcp6_parser.cc"
    break;

  case 746:
#line 2636 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4081 "dhcp6_parser.cc"
    break;

  case 747:
#line 2642 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4091 "dhcp6_parser.cc"
    break;

  case 748:
#line 2648 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4101 "dhcp6_parser.cc"
    break;

  case 749:
#line 2652 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4110 "dhcp6_parser.cc"
    break;

  case 754:
#line 2667 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4122 "dhcp6_parser.cc"
    break;

  case 755:
#line 2673 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4131 "dhcp6_parser.cc"
    break;

  case 756:
#line 2678 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4141 "dhcp6_parser.cc"
    break;

  case 757:
#line 2686 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4153 "dhcp6_parser.cc"
    break;

  case 758:
#line 2692 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4162 "dhcp6_parser.cc"
    break;

  case 761:
#line 2704 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4172 "dhcp6_parser.cc"
    break;

  case 762:
#line 2708 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4180 "dhcp6_parser.cc"
    break;

  case 772:
#line 2725 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4190 "dhcp6_parser.cc"
    break;

  case 773:
#line 2731 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4199 "dhcp6_parser.cc"
    break;

  case 774:
#line 2734 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4209 "dhcp6_parser.cc"
    break;

  case 775:
#line 2740 "dhcp6_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4221 "dhcp6_parser.cc"
    break;

  case 776:
#line 2746 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4230 "dhcp6_parser.cc"
    break;

  case 779:
#line 2755 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4240 "dhcp6_parser.cc"
    break;

  case 780:
#line 2759 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4248 "dhcp6_parser.cc"
    break;

  case 788:
#line 2774 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4257 "dhcp6_parser.cc"
    break;

  case 789:
#line 2777 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4267 "dhcp6_parser.cc"
    break;

  case 790:
#line 2783 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4277 "dhcp6_parser.cc"
    break;

  case 791:
#line 2789 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4287 "dhcp6_parser.cc"
    break;

  case 792:
#line 2795 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4297 "dhcp6_parser.cc"
    break;

  case 793:
#line 2801 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4306 "dhcp6_parser.cc"
    break;

  case 794:
#line 2804 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4316 "dhcp6_parser.cc"
    break;


#line 4320 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -967;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     379,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,    39,    33,    36,    97,   103,
     117,   153,   184,   191,   205,   209,   234,   244,   247,   257,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,    33,  -146,
      49,   116,    52,   540,    24,   186,    29,    -7,   137,   269,
     -65,   526,   119,  -967,    65,    93,   110,   262,   297,  -967,
     296,  -967,  -967,  -967,  -967,  -967,  -967,   306,   310,   335,
     389,   397,   403,   404,   409,   412,   413,   414,   416,   417,
     418,  -967,   419,   420,   421,   422,   423,  -967,  -967,  -967,
     424,   425,   426,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
     428,   429,   432,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,   433,  -967,  -967,  -967,  -967,  -967,  -967,   434,
    -967,   435,  -967,    48,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,   436,  -967,    58,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,   438,
     440,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,    75,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,   189,  -967,  -967,  -967,  -967,  -967,
     442,  -967,   444,   445,  -967,  -967,  -967,  -967,  -967,  -967,
     232,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,   348,   449,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,   376,  -967,
    -967,   450,  -967,  -967,  -967,   451,  -967,  -967,   448,   455,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,   460,   464,  -967,  -967,  -967,  -967,   461,
     470,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,   250,  -967,  -967,  -967,   474,  -967,  -967,
     476,  -967,   479,   480,  -967,  -967,   481,   484,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,   263,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,   485,   283,  -967,  -967,  -967,  -967,    33,
      33,  -967,   292,   488,  -967,   490,   492,   494,   496,   500,
     501,   249,   304,   305,   307,   308,   312,   313,   317,   301,
     309,   319,   321,   324,   325,   506,   327,   332,   333,   337,
     339,   537,   542,   545,   344,   345,   347,   550,   551,   553,
     555,   557,   558,   560,   359,   360,   377,   578,   580,   594,
     595,   596,   597,   607,   608,   610,   411,   612,   613,   616,
     617,   619,   623,   437,   624,  -967,   116,  -967,   625,   441,
      52,  -967,   626,   627,   636,   638,   644,   446,   443,   647,
     648,   650,   540,  -967,   651,    24,  -967,   657,   459,   661,
     462,   463,   186,  -967,   664,   665,   666,   667,   668,   669,
     675,  -967,    29,  -967,   676,   677,   495,   692,   694,   696,
     499,  -967,   137,   697,   502,   503,  -967,   269,   698,   702,
     162,  -967,   504,   703,   707,   508,   709,   510,   511,   712,
     715,   514,   515,   718,   719,   720,   721,   526,  -967,   722,
     523,   119,  -967,  -967,  -967,   724,   728,   533,   730,   731,
     732,   733,   736,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,   539,  -967,  -967,
    -967,  -967,  -967,   107,   554,   556,  -967,  -967,  -967,   753,
     755,   766,   769,   768,   573,   100,  -967,  -967,  -967,   772,
     773,   774,   775,   776,   778,   779,   780,   781,  -967,   782,
     783,   786,   789,   577,   582,  -967,   794,  -967,   795,  -967,
    -967,   796,   797,   583,   603,   604,  -967,  -967,   795,   605,
     802,  -967,   611,  -967,   614,  -967,   615,  -967,  -967,  -967,
     795,   795,   795,   618,   621,   622,   628,  -967,   629,   630,
    -967,   631,   632,   633,  -967,  -967,   634,  -967,  -967,  -967,
     635,   768,  -967,  -967,   637,   639,  -967,   640,  -967,  -967,
     171,   641,  -967,  -967,   107,   642,   643,   645,  -967,   805,
    -967,  -967,    33,   116,  -967,   119,    52,   294,   294,   804,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,   809,
     812,   813,   815,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,   -83,    33,   291,   716,   819,   821,   822,   219,    64,
       7,   -44,   154,   526,  -967,  -967,   823,  -967,  -967,   832,
     834,  -967,  -967,  -967,  -967,  -967,   -58,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,   804,  -967,   289,   295,
     303,  -967,  -967,  -967,  -967,   840,   843,   845,   846,   847,
    -967,   848,   849,   850,  -967,  -967,  -967,   851,   852,   853,
     854,  -967,   352,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,   355,  -967,   855,   856,  -967,
    -967,   857,   859,  -967,  -967,   858,   862,  -967,  -967,   860,
     864,  -967,  -967,   863,   865,  -967,  -967,  -967,    78,  -967,
    -967,  -967,   866,  -967,  -967,  -967,    89,  -967,  -967,  -967,
    -967,   356,  -967,  -967,  -967,   136,  -967,  -967,   867,   868,
    -967,  -967,   869,   871,  -967,   874,   875,   876,   877,   878,
     879,   362,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,   880,   881,   882,  -967,  -967,  -967,  -967,   363,  -967,
    -967,  -967,  -967,  -967,  -967,   883,   884,   885,  -967,   364,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,   366,  -967,  -967,  -967,   886,  -967,   887,  -967,  -967,
    -967,   372,  -967,  -967,  -967,  -967,  -967,   374,  -967,   140,
    -967,   689,  -967,   888,   890,  -967,  -967,   889,   893,  -967,
    -967,  -967,   891,  -967,   892,  -967,  -967,  -967,   896,   897,
     899,   900,   656,   691,   701,   700,   704,   903,   705,   706,
     708,   907,   908,   911,   713,   714,   725,   717,   294,  -967,
    -967,   294,  -967,   804,   540,  -967,   809,   137,  -967,   812,
     269,  -967,   813,   699,  -967,   815,   -83,  -967,  -967,   291,
    -967,   924,   716,  -967,   170,   819,  -967,    29,  -967,   821,
     -65,  -967,   822,   726,   742,   743,   744,   758,   764,   219,
    -967,   936,   955,   770,   792,   799,    64,  -967,   787,   803,
     811,     7,  -967,   983,   995,   -44,  -967,   831,   996,   836,
    1037,   154,  -967,  -967,   195,   823,  -967,  -967,  1040,  1044,
      24,  -967,   832,   186,  -967,   834,  1045,  -967,  -967,   381,
     861,   870,   872,  -967,  -967,  -967,  -967,  -967,   873,  -967,
    -967,  -967,   894,   895,   904,  -967,  -967,  -967,  -967,  -967,
     378,  -967,   380,  -967,  1042,  -967,  1047,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,   382,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,   906,  -967,  -967,  1048,  -967,  -967,  -967,
    -967,  -967,  1049,  1050,  -967,  -967,  -967,  -967,  -967,  1051,
    -967,   384,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
     179,   909,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
     910,   912,  -967,  -967,   913,  -967,    33,  -967,  -967,  1052,
    -967,  -967,  -967,  -967,  -967,   388,  -967,  -967,  -967,  -967,
    -967,  -967,   914,   391,  -967,   392,  -967,   915,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,   699,  -967,  -967,  1054,   905,  -967,
     170,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  1056,   898,  1057,   195,  -967,  -967,  -967,  -967,
    -967,  -967,   916,  -967,  -967,  1060,  -967,   917,  -967,  -967,
    1055,  -967,  -967,   228,  -967,     8,  1055,  -967,  -967,  1063,
    1064,  1065,  -967,   394,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  1066,   918,   902,   919,  1067,     8,  -967,   922,  -967,
    -967,  -967,   923,  -967,  -967,  -967
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    62,     7,   171,     9,   335,    11,
     530,    13,   555,    15,   585,    17,   455,    19,   463,    21,
     500,    23,   300,    25,   698,    27,   748,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   587,     0,   465,   502,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    60,
       0,   127,   746,   169,   183,   185,   187,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   166,     0,     0,     0,     0,     0,   146,   153,   155,
       0,     0,     0,   327,   453,   492,   403,   543,   545,   395,
       0,     0,     0,   260,   277,   268,   253,   622,   577,   292,
     311,   643,     0,   279,   667,   680,   696,   159,   161,     0,
     757,     0,   126,     0,    64,    66,    67,    68,    69,    70,
      71,    72,    73,    74,   105,   106,   107,   108,   109,    75,
     113,   114,   115,   116,   117,   118,   119,   120,   111,   112,
     121,   122,   123,   100,   125,    78,    79,    80,    81,    97,
      82,    84,    83,   124,    88,    89,    76,   102,   103,   104,
     101,    77,    86,    87,    95,    96,    98,    85,    90,    91,
      92,    93,    94,    99,   110,   180,     0,   179,     0,   173,
     175,   176,   177,   178,   522,   547,   382,   384,   386,     0,
       0,   390,   388,   616,   381,   339,   340,   341,   342,   343,
     344,   345,   346,   365,   366,   367,   368,   369,   372,   373,
     374,   375,   376,   377,   378,   379,   370,   371,   380,     0,
     337,   350,   351,   352,   355,   356,   359,   360,   361,   358,
     353,   354,   347,   348,   363,   364,   349,   357,   362,   541,
     540,   536,   537,   535,     0,   532,   534,   538,   539,   570,
       0,   573,     0,     0,   569,   563,   564,   562,   567,   568,
       0,   557,   559,   560,   565,   566,   561,   614,   602,   604,
     606,   608,   610,   612,   601,   598,   599,   600,     0,   588,
     589,   593,   594,   591,   595,   596,   597,   592,     0,   482,
     232,     0,   486,   484,   489,     0,   478,   479,     0,   466,
     467,   469,   481,   470,   471,   472,   488,   473,   474,   475,
     476,   477,   516,     0,     0,   514,   515,   518,   519,     0,
     503,   504,   506,   507,   508,   509,   510,   511,   512,   513,
     307,   309,   304,     0,   302,   305,   306,     0,   721,   723,
       0,   726,     0,     0,   730,   734,     0,     0,   738,   740,
     742,   744,   719,   717,   718,     0,   700,   702,   714,   703,
     704,   705,   706,   707,   708,   709,   710,   711,   712,   713,
     715,   716,   754,     0,     0,   750,   752,   753,    46,     0,
       0,    39,     0,     0,    59,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    57,     0,    63,     0,     0,
       0,   172,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   336,     0,     0,   531,     0,     0,     0,
       0,     0,     0,   556,     0,     0,     0,     0,     0,     0,
       0,   586,     0,   456,     0,     0,     0,     0,     0,     0,
       0,   464,     0,     0,     0,     0,   501,     0,     0,     0,
       0,   301,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   699,     0,
       0,     0,   749,    50,    43,     0,     0,     0,     0,     0,
       0,     0,     0,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,     0,   164,   165,
     143,   144,   145,     0,     0,     0,   157,   158,   163,     0,
       0,     0,     0,     0,     0,     0,   392,   393,   394,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   666,     0,
       0,     0,     0,     0,     0,   168,     0,    65,     0,   182,
     174,     0,     0,     0,     0,     0,   401,   402,     0,     0,
       0,   338,     0,   533,     0,   572,     0,   575,   576,   558,
       0,     0,     0,     0,     0,     0,     0,   590,     0,     0,
     480,     0,     0,     0,   491,   468,     0,   520,   521,   505,
       0,     0,   303,   720,     0,     0,   725,     0,   728,   729,
       0,     0,   736,   737,     0,     0,     0,     0,   701,     0,
     756,   751,     0,     0,   128,     0,     0,     0,     0,   189,
     167,   148,   149,   150,   151,   152,   147,   154,   156,   329,
     457,   494,   405,    40,   544,   546,   397,   398,   399,   400,
     396,     0,    47,     0,     0,     0,   579,   294,     0,     0,
       0,     0,     0,     0,   160,   162,     0,    51,   181,   524,
     549,   383,   385,   387,   391,   389,     0,   542,   571,   574,
     615,   603,   605,   607,   609,   611,   613,   483,   233,   487,
     485,   490,   517,   308,   310,   722,   724,   727,   732,   733,
     731,   735,   739,   741,   743,   745,   189,    44,     0,     0,
       0,   219,   225,   227,   229,     0,     0,     0,     0,     0,
     244,     0,     0,     0,   247,   249,   251,     0,     0,     0,
       0,   218,     0,   195,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   209,   210,   217,   211,   212,   213,
     207,   208,   214,   215,   216,     0,   193,     0,   190,   191,
     333,     0,   330,   331,   461,     0,   458,   459,   498,     0,
     495,   496,   409,     0,   406,   407,   266,   267,     0,   262,
     264,   265,     0,   275,   276,   272,     0,   270,   273,   274,
     258,     0,   255,   257,   626,     0,   624,   583,     0,   580,
     581,   298,     0,   295,   296,     0,     0,     0,     0,     0,
       0,     0,   313,   315,   316,   317,   318,   319,   320,   656,
     662,     0,     0,     0,   655,   652,   653,   654,     0,   645,
     647,   650,   648,   649,   651,     0,     0,     0,   288,     0,
     281,   283,   284,   285,   286,   287,   676,   678,   675,   673,
     674,     0,   669,   671,   672,     0,   691,     0,   694,   687,
     688,     0,   682,   684,   685,   686,   689,     0,   761,     0,
     759,    53,   528,     0,   525,   526,   553,     0,   550,   551,
     620,   619,     0,   618,     0,    61,   747,   170,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   184,
     186,     0,   188,     0,     0,   328,     0,   465,   454,     0,
     502,   493,     0,     0,   404,     0,     0,   261,   278,     0,
     269,     0,     0,   254,   628,     0,   623,   587,   578,     0,
       0,   293,     0,     0,     0,     0,     0,     0,     0,     0,
     312,     0,     0,     0,     0,     0,     0,   644,     0,     0,
       0,     0,   280,     0,     0,     0,   668,     0,     0,     0,
       0,     0,   681,   697,     0,     0,   758,    55,     0,    54,
       0,   523,     0,     0,   548,     0,     0,   617,   755,     0,
       0,     0,     0,   231,   234,   235,   236,   237,     0,   246,
     238,   239,     0,     0,     0,   241,   242,   243,   240,   196,
       0,   192,     0,   332,     0,   460,     0,   497,   452,   427,
     428,   429,   431,   432,   433,   417,   418,   436,   437,   438,
     439,   440,   443,   444,   445,   446,   447,   448,   449,   450,
     441,   442,   451,   413,   414,   415,   416,   425,   426,   422,
     423,   424,   421,   430,     0,   411,   419,   434,   435,   420,
     408,   263,   271,     0,   256,   640,     0,   638,   639,   635,
     636,   637,     0,   629,   630,   632,   633,   634,   625,     0,
     582,     0,   297,   321,   322,   323,   324,   325,   326,   314,
       0,     0,   661,   664,   665,   646,   289,   290,   291,   282,
       0,     0,   670,   690,     0,   693,     0,   683,   775,     0,
     773,   771,   765,   769,   770,     0,   763,   767,   768,   766,
     760,    52,     0,     0,   527,     0,   552,     0,   221,   222,
     223,   224,   220,   226,   228,   230,   245,   248,   250,   252,
     194,   334,   462,   499,     0,   410,   259,     0,     0,   627,
       0,   584,   299,   658,   659,   660,   657,   663,   677,   679,
     692,   695,     0,     0,     0,     0,   762,    56,   529,   554,
     621,   412,     0,   642,   631,     0,   772,     0,   764,   641,
       0,   774,   779,     0,   777,     0,     0,   776,   788,     0,
       0,     0,   793,     0,   781,   783,   784,   785,   786,   787,
     778,     0,     0,     0,     0,     0,     0,   780,     0,   790,
     791,   792,     0,   782,   789,   794
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,   -10,  -967,  -559,  -967,
     199,  -967,  -967,  -967,  -967,   350,  -967,  -597,  -967,  -967,
    -967,   -71,  -967,  -967,  -967,  -967,  -967,  -967,   385,   588,
    -967,  -967,   -59,   -43,   -42,   -40,   -39,   -28,   -27,   -26,
     -23,   -21,   -15,    -9,    -3,  -967,    -1,    17,    18,    20,
    -967,   393,    25,  -967,    28,  -967,    30,    32,    35,  -967,
      38,  -967,    40,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,   383,   590,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,   311,  -967,    98,  -967,  -676,   104,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,   -67,
    -967,  -714,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,    81,  -967,  -967,  -967,  -967,  -967,    88,
    -698,  -967,  -967,  -967,  -967,    86,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,    57,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,    74,  -967,  -967,  -967,    79,   552,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,    71,  -967,  -967,  -967,  -967,  -967,
    -967,  -966,  -967,  -967,  -967,   105,  -967,  -967,  -967,   109,
     592,  -967,  -967,  -965,  -967,  -964,  -967,    51,  -967,    55,
    -967,    42,    45,    46,    50,  -967,  -967,  -967,  -958,  -967,
    -967,  -967,  -967,   101,  -967,  -967,  -119,  1022,  -967,  -967,
    -967,  -967,  -967,   111,  -967,  -967,  -967,   123,  -967,   571,
    -967,   -66,  -967,  -967,  -967,  -967,  -967,   -47,  -967,  -967,
    -967,  -967,  -967,    13,  -967,  -967,  -967,   122,  -967,  -967,
    -967,   131,  -967,   585,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,    76,  -967,  -967,  -967,    77,
     646,  -967,  -967,   -55,  -967,     1,  -967,  -967,  -967,  -967,
    -967,    80,  -967,  -967,  -967,    83,   620,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,   -57,  -967,  -967,  -967,   120,  -967,
    -967,  -967,   124,  -967,   654,   387,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -957,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,   125,  -967,  -967,
    -967,   -86,  -967,  -967,  -967,  -967,  -967,  -967,  -967,   112,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,   102,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
      99,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,   406,   584,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,   447,   587,  -967,  -967,  -967,  -967,  -967,  -967,
     113,  -967,  -967,   -91,  -967,  -967,  -967,  -967,  -967,  -967,
    -111,  -967,  -967,  -130,  -967,  -967,  -967,  -967,  -967,  -967,
    -967
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     714,    87,    88,    41,    68,    84,    85,   738,   941,  1048,
    1049,   801,    43,    70,    90,   423,    45,    71,   153,   154,
     155,   425,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     451,   706,   174,   452,   175,   453,   176,   177,   178,   481,
     179,   482,   180,   181,   182,   183,   445,   184,   185,   427,
      47,    72,   218,   219,   220,   488,   221,   186,   428,   187,
     429,   188,   430,   827,   828,   829,   981,   802,   803,   804,
     958,  1202,   805,   959,   806,   960,   807,   961,   808,   809,
     525,   810,   811,   812,   813,   814,   815,   816,   817,   818,
     819,   820,   967,   821,   822,   971,   823,   972,   824,   973,
     189,   470,   861,   862,   863,  1001,   190,   467,   848,   849,
     850,   851,   191,   469,   856,   857,   858,   859,   192,   468,
     193,   477,   909,   910,   911,   912,   913,   194,   473,   872,
     873,   874,  1010,    63,    80,   373,   374,   375,   538,   376,
     539,   195,   474,   881,   882,   883,   884,   885,   886,   887,
     888,   196,   457,   831,   832,   833,   984,    49,    73,   259,
     260,   261,   494,   262,   495,   263,   496,   264,   500,   265,
     499,   197,   198,   199,   200,   463,   720,   270,   271,   201,
     460,   843,   844,   845,   993,  1124,  1125,   202,   458,    57,
      77,   835,   836,   837,   987,    59,    78,   338,   339,   340,
     341,   342,   343,   344,   524,   345,   528,   346,   527,   347,
     348,   529,   349,   203,   459,   839,   840,   841,   990,    61,
      79,   359,   360,   361,   362,   363,   533,   364,   365,   366,
     367,   273,   492,   943,   944,   945,  1050,    51,    74,   284,
     285,   286,   504,   204,   461,   205,   462,   276,   493,   947,
     948,   949,  1053,    53,    75,   300,   301,   302,   507,   303,
     304,   509,   305,   306,   206,   472,   868,   869,   870,  1007,
      55,    76,   318,   319,   320,   321,   515,   322,   516,   323,
     517,   324,   518,   325,   519,   326,   520,   327,   514,   278,
     501,   952,   953,  1056,   207,   471,   865,   866,  1004,  1142,
    1143,  1144,  1145,  1146,  1217,  1147,   208,   475,   898,   899,
     900,  1021,  1226,   901,   902,  1022,   903,   904,   209,   210,
     478,   921,   922,   923,  1033,   924,  1034,   211,   479,   931,
     932,   933,   934,  1038,   935,   936,  1040,   212,   480,    65,
      81,   395,   396,   397,   398,   543,   399,   544,   400,   401,
     546,   402,   403,   404,   549,   770,   405,   550,   406,   407,
     408,   553,   409,   554,   410,   555,   411,   556,   213,   426,
      67,    82,   414,   415,   416,   559,   417,   214,   484,   939,
     940,  1044,  1185,  1186,  1187,  1188,  1234,  1189,  1232,  1253,
    1254,  1255,  1263,  1264,  1265,  1271,  1266,  1267,  1268,  1269,
    1275
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     152,   217,   234,   280,   294,   314,    38,   336,   355,   372,
     392,   337,   356,   357,   235,   895,   277,   222,   274,   287,
     298,   316,   825,   350,   368,   855,   393,  1114,  1115,  1116,
     236,   237,   358,   238,   239,  1123,  1129,   846,    31,    30,
      32,   744,    33,    42,   713,   240,   241,   242,   127,   128,
     243,   486,   244,   750,   751,   752,   487,    86,   245,    89,
     308,   490,   370,   371,   246,   124,   491,   950,   215,   216,
     247,   418,   248,   223,   275,   288,   299,   317,   502,   351,
     369,   996,   394,   503,   997,   889,   272,   283,   297,   315,
     249,   250,   999,   251,   786,  1000,   419,   125,   252,   127,
     128,   253,   125,   254,    44,   255,   916,   917,   256,   279,
      46,   257,   713,   258,   420,   266,   127,   128,   267,   268,
     847,   127,   128,   269,    48,   281,   295,    91,    92,   282,
     296,    93,   412,   413,    94,    95,    96,   231,   151,  1005,
     232,   307,  1006,  1045,   127,   128,  1046,   308,   309,   310,
     311,   312,   313,   905,   906,   907,   127,   128,   329,   151,
      50,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
    1258,    52,   505,  1259,  1260,  1261,  1262,   506,    54,   126,
     716,   717,   718,   719,   890,   891,   892,   893,   127,   128,
     151,   330,    56,   331,   332,   129,    58,   333,   334,   335,
     130,   131,   132,   133,   134,   135,   136,   151,   137,   127,
     128,  1256,   151,   138,  1257,   512,    34,    35,    36,    37,
     513,    60,   139,   125,   330,   140,   127,   128,  1114,  1115,
    1116,    62,   141,   540,    64,   151,  1123,  1129,   541,   125,
     142,   143,   127,   128,    66,   144,   557,   151,   145,   330,
     421,   558,   146,   289,   290,   291,   292,   293,   127,   128,
     701,   702,   703,   704,  1135,  1136,   561,   127,   128,   370,
     371,   562,   486,   147,   148,   149,   150,   955,   561,   231,
     422,   855,   232,   956,   424,  1080,   490,   925,   926,   927,
     431,   957,   895,   705,   432,   781,  1223,  1224,  1225,   151,
     782,   783,   784,   785,   786,   787,   788,   789,   790,   791,
     792,   793,   794,   795,   796,   797,   798,   799,   800,   433,
     151,   768,   769,   330,   352,   331,   332,   353,   354,   875,
     876,   877,   878,   879,   880,   978,   521,   928,   978,  1002,
     979,   127,   128,   980,  1003,  1019,  1026,  1031,   330,  1035,
    1020,  1027,  1032,   151,  1036,  1041,  1178,   557,  1179,  1180,
    1042,   978,  1043,   502,   523,  1214,  1210,   540,  1211,   151,
    1215,  1235,  1222,   434,   505,   512,  1236,  1276,   151,  1238,
    1239,   435,  1277,  1198,  1199,  1200,  1201,   436,   437,   563,
     564,   846,   853,   438,   854,   152,   439,   440,   441,   217,
     442,   443,   444,   446,   447,   448,   449,   450,   454,   455,
     456,   234,   464,   465,   280,   222,   466,   476,   483,   485,
     489,   294,   497,   235,   498,   277,   508,   274,   510,   511,
     287,   314,   522,   573,   526,   530,   531,   298,   532,   236,
     237,   336,   238,   239,   534,   337,   355,   316,   535,   536,
     356,   357,   151,   537,   240,   241,   242,   350,   542,   243,
     545,   244,   368,   547,   548,   551,   392,   245,   552,   560,
     358,   223,   566,   246,   567,   565,   568,   151,   569,   247,
     570,   248,   393,   275,   571,   572,   288,   581,   574,   575,
     587,   576,   577,   299,   582,   272,   578,   579,   283,   249,
     250,   580,   251,   317,   583,   297,   584,   252,   585,   586,
     253,   588,   254,   351,   255,   315,   589,   256,   369,   590,
     257,   593,   258,   591,   266,   592,   594,   267,   268,   595,
     596,   597,   269,   598,   599,   600,   281,   601,   394,   602,
     282,   603,   604,   295,   605,   606,   607,   296,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,   609,   608,   610,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   611,   612,
     613,   614,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   615,   616,   125,   617,   618,   619,   620,   127,   128,
     621,   622,   152,   623,   224,   217,   225,   624,   626,   628,
     631,   632,   127,   128,   226,   227,   228,   229,   230,   129,
     633,   222,   634,   625,   130,   131,   132,   629,   635,   637,
     636,   638,   639,   231,   640,   642,   232,   138,   894,   908,
     918,   644,   392,   645,   233,   646,   647,   648,   650,   651,
     652,   653,   654,   655,   896,   914,   919,   929,   393,   656,
     658,   659,   777,   377,   378,   379,   380,   381,   382,   383,
     384,   385,   386,   387,   388,   389,   661,   223,   662,   660,
     663,   666,   670,   390,   391,   664,   671,   674,   667,   668,
     673,   675,   676,   677,   678,   679,   680,   147,   148,   681,
     682,   683,   684,   685,   686,   687,   689,   690,   692,   151,
     897,   915,   920,   930,   394,   693,   694,   695,   696,   697,
     698,   699,   700,   151,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   707,   709,   708,
     710,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   711,   125,   330,   712,    32,   715,   721,   722,   723,
     734,   725,   724,   726,   727,   735,   741,   728,   729,   730,
     731,   127,   128,   732,   227,   228,   733,   230,   129,   736,
     737,   739,   740,   130,   131,   132,   742,   743,   745,   746,
     776,   826,   231,   771,   747,   232,   830,   748,   749,   834,
     838,   753,   842,   233,   754,   755,   864,   860,   867,   871,
     938,   756,   757,   758,   759,   760,   761,   762,   763,   942,
     765,   946,   766,   767,   962,   773,   774,   963,   775,   964,
     965,   966,   968,   969,   970,   974,   975,   976,   977,   983,
    1063,   982,   986,   985,   988,   989,   991,   992,   995,   994,
     764,  1009,   998,  1008,  1012,  1011,   147,   148,  1013,  1014,
    1015,  1016,  1017,  1018,  1023,  1024,  1025,  1028,  1029,  1030,
    1037,  1039,  1047,  1052,  1051,  1054,  1055,  1064,  1058,  1057,
    1059,  1060,   151,  1061,  1062,  1065,  1066,  1068,  1067,  1069,
    1070,  1072,  1073,   234,  1071,  1074,   336,  1075,  1076,   355,
     337,  1078,  1088,   356,   357,   235,  1113,   277,  1133,   274,
    1153,  1077,   350,  1137,  1089,   368,   314,  1138,  1127,   372,
    1160,   236,   237,   358,   238,   239,  1154,  1155,  1156,  1140,
    1090,  1091,   316,  1092,  1093,   894,   240,   241,   242,  1161,
     908,   243,  1157,   244,   918,  1094,  1095,  1096,  1158,   245,
    1097,   896,  1098,  1181,  1162,   246,   914,  1182,  1099,   280,
     919,   247,   294,   248,  1100,   275,   929,  1170,   351,  1183,
    1101,   369,  1102,  1166,  1128,   287,  1163,   272,   298,  1171,
    1174,   249,   250,  1164,   251,  1141,  1126,  1167,   317,   252,
    1103,  1104,   253,  1105,   254,  1168,   255,  1139,  1106,   256,
     315,  1107,   257,  1108,   258,  1109,   266,   897,  1110,   267,
     268,  1111,   915,  1112,   269,  1119,   920,  1173,  1120,  1121,
    1175,  1176,   930,  1122,  1117,  1184,  1191,  1192,  1118,  1197,
    1212,   288,  1218,  1220,   299,  1213,  1233,  1219,  1242,  1221,
    1245,  1247,  1252,   283,  1203,  1250,   297,  1272,  1273,  1274,
    1278,  1282,   852,  1204,   627,  1205,  1206,   772,   778,   780,
     630,  1081,  1079,  1134,  1131,  1132,  1152,   954,  1169,  1151,
    1159,  1083,   672,  1082,   641,  1241,  1130,  1207,  1208,   328,
    1085,   281,  1246,   665,   295,   282,  1280,  1209,   296,  1216,
    1084,  1243,  1227,  1228,  1087,  1229,  1230,  1237,  1240,  1249,
    1251,  1086,   669,  1281,  1279,  1284,  1285,  1193,  1194,  1150,
    1148,  1149,   649,   951,  1244,  1196,  1195,  1172,  1165,   937,
    1177,   688,   779,  1088,  1248,  1270,  1283,  1113,   691,  1137,
       0,   643,     0,  1138,     0,  1089,     0,     0,  1190,  1127,
       0,     0,     0,     0,  1181,  1140,  1231,     0,  1182,     0,
       0,  1090,  1091,     0,  1092,  1093,   657,     0,     0,     0,
    1183,     0,     0,     0,     0,     0,  1094,  1095,  1096,     0,
       0,  1097,     0,  1098,     0,     0,     0,     0,     0,  1099,
       0,     0,     0,     0,     0,  1100,     0,     0,     0,     0,
       0,  1101,     0,  1102,     0,  1128,     0,     0,     0,     0,
       0,  1141,     0,     0,     0,     0,     0,  1126,     0,     0,
       0,  1103,  1104,  1139,  1105,     0,  1184,     0,     0,  1106,
       0,     0,  1107,     0,  1108,     0,  1109,     0,     0,  1110,
       0,     0,  1111,     0,  1112,     0,  1119,     0,     0,  1120,
    1121,     0,     0,     0,  1122,  1117,     0,     0,     0,  1118
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,    78,    79,    79,    73,   729,    73,    72,    73,    74,
      75,    76,   698,    78,    79,   723,    81,   993,   993,   993,
      73,    73,    79,    73,    73,   993,   993,   120,     5,     0,
       7,   638,     9,     7,   603,    73,    73,    73,    92,    93,
      73,     3,    73,   650,   651,   652,     8,   203,    73,    10,
     118,     3,   127,   128,    73,    72,     8,   125,    16,    17,
      73,     6,    73,    72,    73,    74,    75,    76,     3,    78,
      79,     3,    81,     8,     6,    21,    73,    74,    75,    76,
      73,    73,     3,    73,    30,     6,     3,    73,    73,    92,
      93,    73,    73,    73,     7,    73,   150,   151,    73,    85,
       7,    73,   671,    73,     4,    73,    92,    93,    73,    73,
     203,    92,    93,    73,     7,    74,    75,    11,    12,    74,
      75,    15,    13,    14,    18,    19,    20,   113,   203,     3,
     116,   112,     6,     3,    92,    93,     6,   118,   119,   120,
     121,   122,   123,   146,   147,   148,    92,    93,    21,   203,
       7,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
     182,     7,     3,   185,   186,   187,   188,     8,     7,    83,
     100,   101,   102,   103,   140,   141,   142,   143,    92,    93,
     203,    74,     7,    76,    77,    99,     7,    80,    81,    82,
     104,   105,   106,   107,   108,   109,   110,   203,   112,    92,
      93,     3,   203,   117,     6,     3,   203,   204,   205,   206,
       8,     7,   126,    73,    74,   129,    92,    93,  1214,  1214,
    1214,     7,   136,     3,     7,   203,  1214,  1214,     8,    73,
     144,   145,    92,    93,     7,   149,     3,   203,   152,    74,
       8,     8,   156,    87,    88,    89,    90,    91,    92,    93,
     173,   174,   175,   176,   114,   115,     3,    92,    93,   127,
     128,     8,     3,   177,   178,   179,   180,     8,     3,   113,
       3,   999,   116,     8,     8,   981,     3,   153,   154,   155,
       4,     8,  1026,   206,     4,    21,   137,   138,   139,   203,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,     4,
     203,   170,   171,    74,    75,    76,    77,    78,    79,   130,
     131,   132,   133,   134,   135,     3,     8,   203,     3,     3,
       8,    92,    93,     8,     8,     3,     3,     3,    74,     3,
       8,     8,     8,   203,     8,     3,   181,     3,   183,   184,
       8,     3,     8,     3,     8,     3,     8,     3,     8,   203,
       8,     3,     8,     4,     3,     3,     8,     3,   203,     8,
       8,     4,     8,    22,    23,    24,    25,     4,     4,   419,
     420,   120,   121,     4,   123,   486,     4,     4,     4,   490,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   502,     4,     4,   505,   490,     4,     4,     4,     4,
       4,   512,     4,   502,     4,   502,     4,   502,     4,     4,
     505,   522,     3,   204,     4,     4,     8,   512,     3,   502,
     502,   532,   502,   502,     4,   532,   537,   522,     4,     8,
     537,   537,   203,     3,   502,   502,   502,   532,     4,   502,
       4,   502,   537,     4,     4,     4,   557,   502,     4,     4,
     537,   490,     4,   502,     4,   203,     4,   203,     4,   502,
       4,   502,   557,   502,     4,     4,   505,   206,   204,   204,
       4,   204,   204,   512,   205,   502,   204,   204,   505,   502,
     502,   204,   502,   522,   205,   512,   205,   502,   204,   204,
     502,   204,   502,   532,   502,   522,   204,   502,   537,   206,
     502,     4,   502,   206,   502,   206,     4,   502,   502,     4,
     206,   206,   502,   206,     4,     4,   505,     4,   557,     4,
     505,     4,     4,   512,     4,   206,   206,   512,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,     4,   206,     4,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,     4,     4,
       4,     4,    62,    63,    64,    65,    66,    67,    68,    69,
      70,     4,     4,    73,     4,   204,     4,     4,    92,    93,
       4,     4,   693,     4,    84,   696,    86,     4,     4,     4,
       4,     4,    92,    93,    94,    95,    96,    97,    98,    99,
       4,   696,     4,   206,   104,   105,   106,   206,     4,   206,
     204,     4,     4,   113,     4,     4,   116,   117,   729,   730,
     731,     4,   733,   204,   124,     4,   204,   204,     4,     4,
       4,     4,     4,     4,   729,   730,   731,   732,   733,     4,
       4,     4,   692,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,     4,   696,     4,   204,
       4,     4,     4,   177,   178,   206,     4,     4,   206,   206,
     206,     4,   204,     4,   204,   204,     4,   177,   178,     4,
     206,   206,     4,     4,     4,     4,     4,   204,     4,   203,
     729,   730,   731,   732,   733,     7,   203,     7,     7,     7,
       7,     5,   203,   203,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,   203,     5,   203,
       5,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,     5,    73,    74,     5,     7,   203,     5,     5,     5,
     203,     5,     7,     5,     5,   203,   203,     7,     7,     7,
       7,    92,    93,     7,    95,    96,     7,    98,    99,     5,
       5,     5,     5,   104,   105,   106,   203,   203,   203,     7,
       5,     7,   113,   172,   203,   116,     7,   203,   203,     7,
       7,   203,     7,   124,   203,   203,     7,   111,     7,     7,
       7,   203,   203,   203,   203,   203,   203,   203,   203,     7,
     203,     7,   203,   203,     4,   203,   203,     4,   203,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     3,
     204,     6,     3,     6,     6,     3,     6,     3,     3,     6,
     671,     3,     6,     6,     3,     6,   177,   178,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   203,     3,     6,     6,     3,   206,     6,     8,
       4,     4,   203,     4,     4,   204,   206,     4,   204,   204,
     204,     4,     4,   984,   206,     4,   987,   204,   204,   990,
     987,   204,   993,   990,   990,   984,   993,   984,     4,   984,
     204,   206,   987,  1004,   993,   990,  1007,  1004,   993,  1010,
       4,   984,   984,   990,   984,   984,   204,   204,   204,  1004,
     993,   993,  1007,   993,   993,  1026,   984,   984,   984,     4,
    1031,   984,   204,   984,  1035,   993,   993,   993,   204,   984,
     993,  1026,   993,  1044,   204,   984,  1031,  1044,   993,  1050,
    1035,   984,  1053,   984,   993,   984,  1041,     4,   987,  1044,
     993,   990,   993,   206,   993,  1050,   204,   984,  1053,     4,
       4,   984,   984,   204,   984,  1004,   993,   204,  1007,   984,
     993,   993,   984,   993,   984,   204,   984,  1004,   993,   984,
    1007,   993,   984,   993,   984,   993,   984,  1026,   993,   984,
     984,   993,  1031,   993,   984,   993,  1035,   206,   993,   993,
     204,     4,  1041,   993,   993,  1044,     6,     3,   993,     4,
       8,  1050,     4,     3,  1053,     8,     4,     8,     4,     8,
       4,     4,     7,  1050,   203,     5,  1053,     4,     4,     4,
       4,     4,   722,   203,   486,   203,   203,   684,   693,   696,
     490,   983,   978,  1002,   996,   999,  1012,   776,  1031,  1010,
    1019,   986,   540,   984,   502,  1214,   995,   203,   203,    77,
     989,  1050,   204,   532,  1053,  1050,   204,   203,  1053,   203,
     987,   206,   203,   203,   992,   203,   203,   203,   203,   203,
     203,   990,   537,   204,   206,   203,   203,  1050,  1052,  1009,
    1005,  1007,   512,   746,  1220,  1055,  1053,  1035,  1026,   733,
    1041,   557,   695,  1214,  1235,  1256,  1276,  1214,   561,  1220,
      -1,   505,    -1,  1220,    -1,  1214,    -1,    -1,  1045,  1214,
      -1,    -1,    -1,    -1,  1235,  1220,  1176,    -1,  1235,    -1,
      -1,  1214,  1214,    -1,  1214,  1214,   522,    -1,    -1,    -1,
    1235,    -1,    -1,    -1,    -1,    -1,  1214,  1214,  1214,    -1,
      -1,  1214,    -1,  1214,    -1,    -1,    -1,    -1,    -1,  1214,
      -1,    -1,    -1,    -1,    -1,  1214,    -1,    -1,    -1,    -1,
      -1,  1214,    -1,  1214,    -1,  1214,    -1,    -1,    -1,    -1,
      -1,  1220,    -1,    -1,    -1,    -1,    -1,  1214,    -1,    -1,
      -1,  1214,  1214,  1220,  1214,    -1,  1235,    -1,    -1,  1214,
      -1,    -1,  1214,    -1,  1214,    -1,  1214,    -1,    -1,  1214,
      -1,    -1,  1214,    -1,  1214,    -1,  1214,    -1,    -1,  1214,
    1214,    -1,    -1,    -1,  1214,  1214,    -1,    -1,    -1,  1214
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
       0,     5,     7,     9,   203,   204,   205,   206,   223,   224,
     225,   230,     7,   239,     7,   243,     7,   287,     7,   394,
       7,   474,     7,   490,     7,   507,     7,   426,     7,   432,
       7,   456,     7,   370,     7,   576,     7,   607,   231,   226,
     240,   244,   288,   395,   475,   491,   508,   427,   433,   457,
     371,   577,   608,   223,   232,   233,   203,   228,   229,    10,
     241,    11,    12,    15,    18,    19,    20,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    83,    92,    93,    99,
     104,   105,   106,   107,   108,   109,   110,   112,   117,   126,
     129,   136,   144,   145,   149,   152,   156,   177,   178,   179,
     180,   203,   238,   245,   246,   247,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   269,   271,   273,   274,   275,   277,
     279,   280,   281,   282,   284,   285,   294,   296,   298,   337,
     343,   349,   355,   357,   364,   378,   388,   408,   409,   410,
     411,   416,   424,   450,   480,   482,   501,   531,   543,   555,
     556,   564,   574,   605,   614,    16,    17,   238,   289,   290,
     291,   293,   480,   482,    84,    86,    94,    95,    96,    97,
      98,   113,   116,   124,   238,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   263,   264,
     265,   266,   269,   271,   273,   274,   275,   277,   279,   396,
     397,   398,   400,   402,   404,   406,   408,   409,   410,   411,
     414,   415,   450,   468,   480,   482,   484,   501,   526,    85,
     238,   404,   406,   450,   476,   477,   478,   480,   482,    87,
      88,    89,    90,    91,   238,   404,   406,   450,   480,   482,
     492,   493,   494,   496,   497,   499,   500,   112,   118,   119,
     120,   121,   122,   123,   238,   450,   480,   482,   509,   510,
     511,   512,   514,   516,   518,   520,   522,   524,   424,    21,
      74,    76,    77,    80,    81,    82,   238,   316,   434,   435,
     436,   437,   438,   439,   440,   442,   444,   446,   447,   449,
     480,   482,    75,    78,    79,   238,   316,   438,   444,   458,
     459,   460,   461,   462,   464,   465,   466,   467,   480,   482,
     127,   128,   238,   372,   373,   374,   376,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     177,   178,   238,   480,   482,   578,   579,   580,   581,   583,
     585,   586,   588,   589,   590,   593,   595,   596,   597,   599,
     601,   603,    13,    14,   609,   610,   611,   613,     6,     3,
       4,     8,     3,   242,     8,   248,   606,   286,   295,   297,
     299,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   283,     4,     4,     4,     4,
       4,   267,   270,   272,     4,     4,     4,   389,   425,   451,
     417,   481,   483,   412,     4,     4,     4,   344,   356,   350,
     338,   532,   502,   365,   379,   544,     4,   358,   557,   565,
     575,   276,   278,     4,   615,     4,     3,     8,   292,     4,
       3,     8,   469,   485,   399,   401,   403,     4,     4,   407,
     405,   527,     3,     8,   479,     3,     8,   495,     4,   498,
       4,     4,     3,     8,   525,   513,   515,   517,   519,   521,
     523,     8,     3,     8,   441,   317,     4,   445,   443,   448,
       4,     8,     3,   463,     4,     4,     8,     3,   375,   377,
       3,     8,     4,   582,   584,     4,   587,     4,     4,   591,
     594,     4,     4,   598,   600,   602,   604,     3,     8,   612,
       4,     3,     8,   223,   223,   203,     4,     4,     4,     4,
       4,     4,     4,   204,   204,   204,   204,   204,   204,   204,
     204,   206,   205,   205,   205,   204,   204,     4,   204,   204,
     206,   206,   206,     4,     4,     4,   206,   206,   206,     4,
       4,     4,     4,     4,     4,     4,   206,   206,   206,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   204,     4,
       4,     4,     4,     4,     4,   206,     4,   246,     4,   206,
     290,     4,     4,     4,     4,     4,   204,   206,     4,     4,
       4,   397,     4,   477,     4,   204,     4,   204,   204,   493,
       4,     4,     4,     4,     4,     4,     4,   511,     4,     4,
     204,     4,     4,     4,   206,   436,     4,   206,   206,   460,
       4,     4,   373,   206,     4,     4,   204,     4,   204,   204,
       4,     4,   206,   206,     4,     4,     4,     4,   579,     4,
     204,   610,     4,     7,   203,     7,     7,     7,     7,     5,
     203,   173,   174,   175,   176,   206,   268,   203,   203,     5,
       5,     5,     5,   225,   227,   203,   100,   101,   102,   103,
     413,     5,     5,     5,     7,     5,     5,     5,     7,     7,
       7,     7,     7,     7,   203,   203,     5,     5,   234,     5,
       5,   203,   203,   203,   234,   203,     7,   203,   203,   203,
     234,   234,   234,   203,   203,   203,   203,   203,   203,   203,
     203,   203,   203,   203,   227,   203,   203,   203,   170,   171,
     592,   172,   268,   203,   203,   203,     5,   223,   245,   609,
     289,    21,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,   238,   304,   305,   306,   309,   311,   313,   315,   316,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   330,   331,   333,   335,   304,     7,   300,   301,   302,
       7,   390,   391,   392,     7,   428,   429,   430,     7,   452,
     453,   454,     7,   418,   419,   420,   120,   203,   345,   346,
     347,   348,   232,   121,   123,   347,   351,   352,   353,   354,
     111,   339,   340,   341,     7,   533,   534,     7,   503,   504,
     505,     7,   366,   367,   368,   130,   131,   132,   133,   134,
     135,   380,   381,   382,   383,   384,   385,   386,   387,    21,
     140,   141,   142,   143,   238,   318,   480,   482,   545,   546,
     547,   550,   551,   553,   554,   146,   147,   148,   238,   359,
     360,   361,   362,   363,   480,   482,   150,   151,   238,   480,
     482,   558,   559,   560,   562,   153,   154,   155,   203,   480,
     482,   566,   567,   568,   569,   571,   572,   578,     7,   616,
     617,   235,     7,   470,   471,   472,     7,   486,   487,   488,
     125,   512,   528,   529,   300,     8,     8,     8,   307,   310,
     312,   314,     4,     4,     4,     4,     4,   329,     4,     4,
       4,   332,   334,   336,     4,     4,     4,     4,     3,     8,
       8,   303,     6,     3,   393,     6,     3,   431,     6,     3,
     455,     6,     3,   421,     6,     3,     3,     6,     6,     3,
       6,   342,     3,     8,   535,     3,     6,   506,     6,     3,
     369,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,   548,   552,     4,     4,     4,     3,     8,     4,     4,
       4,     3,     8,   561,   563,     3,     8,     4,   570,     4,
     573,     3,     8,     8,   618,     3,     6,   203,   236,   237,
     473,     6,     3,   489,     6,     3,   530,     8,     6,     4,
       4,     4,     4,   204,   206,   204,   206,   204,     4,   204,
     204,   206,     4,     4,     4,   204,   204,   206,   204,   305,
     304,   302,   396,   392,   434,   430,   458,   454,   238,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   263,   264,   265,   266,   269,   271,   273,   274,
     275,   277,   279,   316,   388,   400,   402,   404,   406,   408,
     409,   410,   411,   415,   422,   423,   450,   480,   482,   526,
     420,   346,   352,     4,   340,   114,   115,   238,   316,   450,
     480,   482,   536,   537,   538,   539,   540,   542,   534,   509,
     505,   372,   368,   204,   204,   204,   204,   204,   204,   381,
       4,     4,   204,   204,   204,   546,   206,   204,   204,   360,
       4,     4,   559,   206,     4,   204,     4,   567,   181,   183,
     184,   238,   316,   480,   482,   619,   620,   621,   622,   624,
     617,     6,     3,   476,   472,   492,   488,     4,    22,    23,
      24,    25,   308,   203,   203,   203,   203,   203,   203,   203,
       8,     8,     8,     8,     3,     8,   203,   541,     4,     8,
       3,     8,     8,   137,   138,   139,   549,   203,   203,   203,
     203,   223,   625,     4,   623,     3,     8,   203,     8,     8,
     203,   423,     4,   206,   538,     4,   204,     4,   620,   203,
       5,   203,     7,   626,   627,   628,     3,     6,   182,   185,
     186,   187,   188,   629,   630,   631,   633,   634,   635,   636,
     627,   632,     4,     4,     4,   637,     3,     8,     4,   206,
     204,   204,     4,   630,   203,   203
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   207,   209,   208,   210,   208,   211,   208,   212,   208,
     213,   208,   214,   208,   215,   208,   216,   208,   217,   208,
     218,   208,   219,   208,   220,   208,   221,   208,   222,   208,
     223,   223,   223,   223,   223,   223,   223,   224,   226,   225,
     227,   228,   228,   229,   229,   231,   230,   232,   232,   233,
     233,   235,   234,   236,   236,   237,   237,   238,   240,   239,
     242,   241,   244,   243,   245,   245,   246,   246,   246,   246,
     246,   246,   246,   246,   246,   246,   246,   246,   246,   246,
     246,   246,   246,   246,   246,   246,   246,   246,   246,   246,
     246,   246,   246,   246,   246,   246,   246,   246,   246,   246,
     246,   246,   246,   246,   246,   246,   246,   246,   246,   246,
     246,   246,   246,   246,   246,   246,   246,   246,   246,   246,
     246,   246,   246,   246,   246,   246,   246,   248,   247,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   267,   266,   268,   268,
     268,   268,   268,   270,   269,   272,   271,   273,   274,   276,
     275,   278,   277,   279,   280,   281,   283,   282,   284,   286,
     285,   288,   287,   289,   289,   290,   290,   290,   290,   290,
     292,   291,   293,   295,   294,   297,   296,   299,   298,   300,
     300,   301,   301,   303,   302,   304,   304,   305,   305,   305,
     305,   305,   305,   305,   305,   305,   305,   305,   305,   305,
     305,   305,   305,   305,   305,   305,   305,   305,   305,   307,
     306,   308,   308,   308,   308,   310,   309,   312,   311,   314,
     313,   315,   317,   316,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   329,   328,   330,   332,   331,   334,
     333,   336,   335,   338,   337,   339,   339,   340,   342,   341,
     344,   343,   345,   345,   346,   346,   347,   348,   350,   349,
     351,   351,   352,   352,   352,   353,   354,   356,   355,   358,
     357,   359,   359,   360,   360,   360,   360,   360,   360,   361,
     362,   363,   365,   364,   366,   366,   367,   367,   369,   368,
     371,   370,   372,   372,   372,   373,   373,   375,   374,   377,
     376,   379,   378,   380,   380,   381,   381,   381,   381,   381,
     381,   382,   383,   384,   385,   386,   387,   389,   388,   390,
     390,   391,   391,   393,   392,   395,   394,   396,   396,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   399,   398,   401,   400,   403,   402,   405,   404,
     407,   406,   408,   409,   410,   412,   411,   413,   413,   413,
     413,   414,   415,   417,   416,   418,   418,   419,   419,   421,
     420,   422,   422,   423,   423,   423,   423,   423,   423,   423,
     423,   423,   423,   423,   423,   423,   423,   423,   423,   423,
     423,   423,   423,   423,   423,   423,   423,   423,   423,   423,
     423,   423,   423,   423,   423,   423,   423,   423,   423,   423,
     423,   423,   423,   425,   424,   427,   426,   428,   428,   429,
     429,   431,   430,   433,   432,   434,   434,   435,   435,   436,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   437,
     438,   439,   441,   440,   443,   442,   445,   444,   446,   448,
     447,   449,   451,   450,   452,   452,   453,   453,   455,   454,
     457,   456,   458,   458,   459,   459,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   461,   463,   462,   464,   465,
     466,   467,   469,   468,   470,   470,   471,   471,   473,   472,
     475,   474,   476,   476,   477,   477,   477,   477,   477,   477,
     477,   479,   478,   481,   480,   483,   482,   485,   484,   486,
     486,   487,   487,   489,   488,   491,   490,   492,   492,   493,
     493,   493,   493,   493,   493,   493,   493,   493,   493,   493,
     495,   494,   496,   498,   497,   499,   500,   502,   501,   503,
     503,   504,   504,   506,   505,   508,   507,   509,   509,   510,
     510,   511,   511,   511,   511,   511,   511,   511,   511,   511,
     511,   511,   513,   512,   515,   514,   517,   516,   519,   518,
     521,   520,   523,   522,   525,   524,   527,   526,   528,   528,
     530,   529,   532,   531,   533,   533,   535,   534,   536,   536,
     537,   537,   538,   538,   538,   538,   538,   538,   538,   539,
     541,   540,   542,   544,   543,   545,   545,   546,   546,   546,
     546,   546,   546,   546,   546,   546,   548,   547,   549,   549,
     549,   550,   552,   551,   553,   554,   555,   557,   556,   558,
     558,   559,   559,   559,   559,   559,   561,   560,   563,   562,
     565,   564,   566,   566,   567,   567,   567,   567,   567,   567,
     568,   570,   569,   571,   573,   572,   575,   574,   577,   576,
     578,   578,   579,   579,   579,   579,   579,   579,   579,   579,
     579,   579,   579,   579,   579,   579,   579,   579,   579,   579,
     580,   582,   581,   584,   583,   585,   587,   586,   588,   589,
     591,   590,   592,   592,   594,   593,   595,   596,   598,   597,
     600,   599,   602,   601,   604,   603,   606,   605,   608,   607,
     609,   609,   610,   610,   612,   611,   613,   615,   614,   616,
     616,   618,   617,   619,   619,   620,   620,   620,   620,   620,
     620,   620,   621,   623,   622,   625,   624,   626,   626,   628,
     627,   629,   629,   630,   630,   630,   630,   630,   632,   631,
     633,   634,   635,   637,   636
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     3,     0,     4,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     0,     6,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     3,     3,     3,     0,     4,     1,     1,     1,
       1,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     0,     6,     3,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       3,     3,     3,     0,     4
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
  "\"reconnect-wait-time\"", "\"disable-dhcp-on-db-loss\"", "\"keyspace\"",
  "\"consistency\"", "\"serial-consistency\"", "\"request-timeout\"",
  "\"tcp-keepalive\"", "\"tcp-nodelay\"", "\"max-row-errors\"",
  "\"preferred-lifetime\"", "\"min-preferred-lifetime\"",
  "\"max-preferred-lifetime\"", "\"valid-lifetime\"",
  "\"min-valid-lifetime\"", "\"max-valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"calculate-tee-times\"", "\"t1-percent\"",
  "\"t2-percent\"", "\"cache-threshold\"", "\"cache-max-age\"",
  "\"decline-probation-period\"", "\"server-tag\"",
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
  "disable_dhcp_on_db_loss", "max_row_errors", "request_timeout",
  "tcp_keepalive", "tcp_nodelay", "contact_points", "$@40",
  "max_reconnect_tries", "keyspace", "$@41", "consistency", "$@42",
  "serial_consistency", "$@43", "sanity_checks", "$@44",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@45",
  "mac_sources", "$@46", "mac_sources_list", "mac_sources_value",
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
       0,   293,   293,   293,   294,   294,   295,   295,   296,   296,
     297,   297,   298,   298,   299,   299,   300,   300,   301,   301,
     302,   302,   303,   303,   304,   304,   305,   305,   306,   306,
     314,   315,   316,   317,   318,   319,   320,   323,   328,   328,
     339,   342,   343,   346,   351,   359,   359,   366,   367,   370,
     374,   381,   381,   388,   389,   392,   396,   407,   416,   416,
     431,   431,   448,   448,   457,   458,   463,   464,   465,   466,
     467,   468,   469,   470,   471,   472,   473,   474,   475,   476,
     477,   478,   479,   480,   481,   482,   483,   484,   485,   486,
     487,   488,   489,   490,   491,   492,   493,   494,   495,   496,
     497,   498,   499,   500,   501,   502,   503,   504,   505,   506,
     507,   508,   509,   510,   511,   512,   513,   514,   515,   516,
     517,   518,   519,   520,   521,   522,   523,   526,   526,   535,
     541,   547,   553,   559,   565,   571,   577,   583,   589,   595,
     601,   607,   613,   619,   625,   631,   637,   637,   646,   649,
     652,   655,   658,   664,   664,   673,   673,   682,   688,   694,
     694,   703,   703,   712,   718,   724,   730,   730,   739,   745,
     745,   757,   757,   766,   767,   770,   771,   772,   773,   774,
     777,   777,   788,   794,   794,   807,   807,   820,   820,   831,
     832,   835,   836,   839,   839,   849,   850,   853,   854,   855,
     856,   857,   858,   859,   860,   861,   862,   863,   864,   865,
     866,   867,   868,   869,   870,   871,   872,   873,   874,   877,
     877,   885,   886,   887,   888,   891,   891,   900,   900,   909,
     909,   918,   924,   924,   933,   939,   945,   951,   957,   963,
     969,   975,   981,   987,   993,   993,  1002,  1008,  1008,  1017,
    1017,  1026,  1026,  1035,  1035,  1046,  1047,  1049,  1051,  1051,
    1070,  1070,  1081,  1082,  1085,  1086,  1089,  1094,  1099,  1099,
    1110,  1111,  1114,  1115,  1116,  1119,  1124,  1131,  1131,  1144,
    1144,  1157,  1158,  1161,  1162,  1163,  1164,  1165,  1166,  1169,
    1175,  1181,  1187,  1187,  1198,  1199,  1202,  1203,  1206,  1206,
    1216,  1216,  1226,  1227,  1228,  1231,  1232,  1235,  1235,  1244,
    1244,  1253,  1253,  1265,  1266,  1269,  1270,  1271,  1272,  1273,
    1274,  1277,  1283,  1289,  1295,  1301,  1307,  1316,  1316,  1330,
    1331,  1334,  1335,  1342,  1342,  1368,  1368,  1379,  1380,  1384,
    1385,  1386,  1387,  1388,  1389,  1390,  1391,  1392,  1393,  1394,
    1395,  1396,  1397,  1398,  1399,  1400,  1401,  1402,  1403,  1404,
    1405,  1406,  1407,  1408,  1409,  1410,  1411,  1412,  1413,  1414,
    1415,  1416,  1417,  1418,  1419,  1420,  1421,  1422,  1423,  1424,
    1425,  1426,  1429,  1429,  1438,  1438,  1447,  1447,  1456,  1456,
    1465,  1465,  1476,  1482,  1488,  1494,  1494,  1502,  1503,  1504,
    1505,  1508,  1514,  1522,  1522,  1534,  1535,  1539,  1540,  1543,
    1543,  1551,  1552,  1555,  1556,  1557,  1558,  1559,  1560,  1561,
    1562,  1563,  1564,  1565,  1566,  1567,  1568,  1569,  1570,  1571,
    1572,  1573,  1574,  1575,  1576,  1577,  1578,  1579,  1580,  1581,
    1582,  1583,  1584,  1585,  1586,  1587,  1588,  1589,  1590,  1591,
    1592,  1593,  1594,  1601,  1601,  1615,  1615,  1624,  1625,  1628,
    1629,  1634,  1634,  1649,  1649,  1663,  1664,  1667,  1668,  1671,
    1672,  1673,  1674,  1675,  1676,  1677,  1678,  1679,  1680,  1683,
    1685,  1691,  1693,  1693,  1702,  1702,  1711,  1711,  1720,  1722,
    1722,  1731,  1741,  1741,  1754,  1755,  1760,  1761,  1766,  1766,
    1778,  1778,  1790,  1791,  1796,  1797,  1802,  1803,  1804,  1805,
    1806,  1807,  1808,  1809,  1810,  1813,  1815,  1815,  1824,  1826,
    1828,  1834,  1843,  1843,  1856,  1857,  1860,  1861,  1864,  1864,
    1874,  1874,  1884,  1885,  1888,  1889,  1890,  1891,  1892,  1893,
    1894,  1897,  1897,  1906,  1906,  1931,  1931,  1961,  1961,  1974,
    1975,  1978,  1979,  1982,  1982,  1994,  1994,  2006,  2007,  2010,
    2011,  2012,  2013,  2014,  2015,  2016,  2017,  2018,  2019,  2020,
    2023,  2023,  2032,  2038,  2038,  2047,  2053,  2062,  2062,  2073,
    2074,  2077,  2078,  2081,  2081,  2090,  2090,  2099,  2100,  2103,
    2104,  2108,  2109,  2110,  2111,  2112,  2113,  2114,  2115,  2116,
    2117,  2118,  2121,  2121,  2132,  2132,  2143,  2143,  2152,  2152,
    2161,  2161,  2170,  2170,  2179,  2179,  2193,  2193,  2204,  2205,
    2208,  2208,  2220,  2220,  2231,  2232,  2235,  2235,  2245,  2246,
    2249,  2250,  2253,  2254,  2255,  2256,  2257,  2258,  2259,  2262,
    2264,  2264,  2273,  2282,  2282,  2295,  2296,  2299,  2300,  2301,
    2302,  2303,  2304,  2305,  2306,  2307,  2310,  2310,  2318,  2319,
    2320,  2323,  2329,  2329,  2338,  2344,  2352,  2360,  2360,  2371,
    2372,  2375,  2376,  2377,  2378,  2379,  2382,  2382,  2391,  2391,
    2403,  2403,  2416,  2417,  2420,  2421,  2422,  2423,  2424,  2425,
    2428,  2434,  2434,  2443,  2449,  2449,  2459,  2459,  2472,  2472,
    2482,  2483,  2486,  2487,  2488,  2489,  2490,  2491,  2492,  2493,
    2494,  2495,  2496,  2497,  2498,  2499,  2500,  2501,  2502,  2503,
    2506,  2513,  2513,  2522,  2522,  2531,  2537,  2537,  2546,  2552,
    2558,  2558,  2567,  2568,  2571,  2571,  2581,  2588,  2595,  2595,
    2604,  2604,  2614,  2614,  2624,  2624,  2636,  2636,  2648,  2648,
    2658,  2659,  2663,  2664,  2667,  2667,  2678,  2686,  2686,  2699,
    2700,  2704,  2704,  2712,  2713,  2716,  2717,  2718,  2719,  2720,
    2721,  2722,  2725,  2731,  2731,  2740,  2740,  2751,  2752,  2755,
    2755,  2763,  2764,  2767,  2768,  2769,  2770,  2771,  2774,  2774,
    2783,  2789,  2795,  2801,  2801
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
#line 5828 "dhcp6_parser.cc"

#line 2810 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
