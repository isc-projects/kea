// A Bison parser, made by GNU Bison 3.5.3.

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
      case 214: // value
      case 218: // map_value
      case 259: // ddns_replace_client_name_value
      case 294: // db_type
      case 388: // hr_mode
      case 524: // duid_type
      case 567: // ncr_protocol_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 196: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 195: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 194: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 193: // "constant string"
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
      case 214: // value
      case 218: // map_value
      case 259: // ddns_replace_client_name_value
      case 294: // db_type
      case 388: // hr_mode
      case 524: // duid_type
      case 567: // ncr_protocol_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 196: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 195: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 194: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 193: // "constant string"
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
      case 214: // value
      case 218: // map_value
      case 259: // ddns_replace_client_name_value
      case 294: // db_type
      case 388: // hr_mode
      case 524: // duid_type
      case 567: // ncr_protocol_value
        value.copy< ElementPtr > (that.value);
        break;

      case 196: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 195: // "floating point"
        value.copy< double > (that.value);
        break;

      case 194: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 193: // "constant string"
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
      case 214: // value
      case 218: // map_value
      case 259: // ddns_replace_client_name_value
      case 294: // db_type
      case 388: // hr_mode
      case 524: // duid_type
      case 567: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 196: // "boolean"
        value.move< bool > (that.value);
        break;

      case 195: // "floating point"
        value.move< double > (that.value);
        break;

      case 194: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 193: // "constant string"
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
      case 193: // "constant string"
#line 272 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 443 "dhcp6_parser.cc"
        break;

      case 194: // "integer"
#line 272 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 449 "dhcp6_parser.cc"
        break;

      case 195: // "floating point"
#line 272 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 455 "dhcp6_parser.cc"
        break;

      case 196: // "boolean"
#line 272 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 461 "dhcp6_parser.cc"
        break;

      case 214: // value
#line 272 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 467 "dhcp6_parser.cc"
        break;

      case 218: // map_value
#line 272 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 473 "dhcp6_parser.cc"
        break;

      case 259: // ddns_replace_client_name_value
#line 272 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 479 "dhcp6_parser.cc"
        break;

      case 294: // db_type
#line 272 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 485 "dhcp6_parser.cc"
        break;

      case 388: // hr_mode
#line 272 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 491 "dhcp6_parser.cc"
        break;

      case 524: // duid_type
#line 272 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 497 "dhcp6_parser.cc"
        break;

      case 567: // ncr_protocol_value
#line 272 "dhcp6_parser.yy"
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
      case 214: // value
      case 218: // map_value
      case 259: // ddns_replace_client_name_value
      case 294: // db_type
      case 388: // hr_mode
      case 524: // duid_type
      case 567: // ncr_protocol_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 196: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 195: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 194: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 193: // "constant string"
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
#line 281 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 770 "dhcp6_parser.cc"
    break;

  case 4:
#line 282 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 776 "dhcp6_parser.cc"
    break;

  case 6:
#line 283 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 782 "dhcp6_parser.cc"
    break;

  case 8:
#line 284 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 788 "dhcp6_parser.cc"
    break;

  case 10:
#line 285 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 794 "dhcp6_parser.cc"
    break;

  case 12:
#line 286 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 800 "dhcp6_parser.cc"
    break;

  case 14:
#line 287 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 806 "dhcp6_parser.cc"
    break;

  case 16:
#line 288 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 812 "dhcp6_parser.cc"
    break;

  case 18:
#line 289 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 818 "dhcp6_parser.cc"
    break;

  case 20:
#line 290 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 824 "dhcp6_parser.cc"
    break;

  case 22:
#line 291 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 830 "dhcp6_parser.cc"
    break;

  case 24:
#line 292 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 836 "dhcp6_parser.cc"
    break;

  case 26:
#line 293 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 842 "dhcp6_parser.cc"
    break;

  case 28:
#line 294 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.LOGGING; }
#line 848 "dhcp6_parser.cc"
    break;

  case 30:
#line 295 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 854 "dhcp6_parser.cc"
    break;

  case 32:
#line 303 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 860 "dhcp6_parser.cc"
    break;

  case 33:
#line 304 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 866 "dhcp6_parser.cc"
    break;

  case 34:
#line 305 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 872 "dhcp6_parser.cc"
    break;

  case 35:
#line 306 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 878 "dhcp6_parser.cc"
    break;

  case 36:
#line 307 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 884 "dhcp6_parser.cc"
    break;

  case 37:
#line 308 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 890 "dhcp6_parser.cc"
    break;

  case 38:
#line 309 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 896 "dhcp6_parser.cc"
    break;

  case 39:
#line 312 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 905 "dhcp6_parser.cc"
    break;

  case 40:
#line 317 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 916 "dhcp6_parser.cc"
    break;

  case 41:
#line 322 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 926 "dhcp6_parser.cc"
    break;

  case 42:
#line 328 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 932 "dhcp6_parser.cc"
    break;

  case 45:
#line 335 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 941 "dhcp6_parser.cc"
    break;

  case 46:
#line 339 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 951 "dhcp6_parser.cc"
    break;

  case 47:
#line 346 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 960 "dhcp6_parser.cc"
    break;

  case 48:
#line 349 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 968 "dhcp6_parser.cc"
    break;

  case 51:
#line 357 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 977 "dhcp6_parser.cc"
    break;

  case 52:
#line 361 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 986 "dhcp6_parser.cc"
    break;

  case 53:
#line 368 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 994 "dhcp6_parser.cc"
    break;

  case 54:
#line 370 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1003 "dhcp6_parser.cc"
    break;

  case 57:
#line 379 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1012 "dhcp6_parser.cc"
    break;

  case 58:
#line 383 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1021 "dhcp6_parser.cc"
    break;

  case 59:
#line 394 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1032 "dhcp6_parser.cc"
    break;

  case 60:
#line 404 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1043 "dhcp6_parser.cc"
    break;

  case 61:
#line 409 "dhcp6_parser.yy"
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
#line 432 "dhcp6_parser.yy"
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
#line 439 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1079 "dhcp6_parser.cc"
    break;

  case 72:
#line 447 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1089 "dhcp6_parser.cc"
    break;

  case 73:
#line 451 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1098 "dhcp6_parser.cc"
    break;

  case 126:
#line 514 "dhcp6_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1106 "dhcp6_parser.cc"
    break;

  case 127:
#line 516 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1116 "dhcp6_parser.cc"
    break;

  case 128:
#line 522 "dhcp6_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1125 "dhcp6_parser.cc"
    break;

  case 129:
#line 527 "dhcp6_parser.yy"
                                                             {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1134 "dhcp6_parser.cc"
    break;

  case 130:
#line 532 "dhcp6_parser.yy"
                                                             {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1143 "dhcp6_parser.cc"
    break;

  case 131:
#line 537 "dhcp6_parser.yy"
                                             {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1152 "dhcp6_parser.cc"
    break;

  case 132:
#line 542 "dhcp6_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1161 "dhcp6_parser.cc"
    break;

  case 133:
#line 547 "dhcp6_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1170 "dhcp6_parser.cc"
    break;

  case 134:
#line 552 "dhcp6_parser.yy"
                                       {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1179 "dhcp6_parser.cc"
    break;

  case 135:
#line 557 "dhcp6_parser.yy"
                                         {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1188 "dhcp6_parser.cc"
    break;

  case 136:
#line 562 "dhcp6_parser.yy"
                                                       {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1197 "dhcp6_parser.cc"
    break;

  case 137:
#line 567 "dhcp6_parser.yy"
                                   {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1206 "dhcp6_parser.cc"
    break;

  case 138:
#line 572 "dhcp6_parser.yy"
                                   {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1215 "dhcp6_parser.cc"
    break;

  case 139:
#line 577 "dhcp6_parser.yy"
                                                                 {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1224 "dhcp6_parser.cc"
    break;

  case 140:
#line 582 "dhcp6_parser.yy"
                                                   {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1233 "dhcp6_parser.cc"
    break;

  case 141:
#line 587 "dhcp6_parser.yy"
                                                               {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1242 "dhcp6_parser.cc"
    break;

  case 142:
#line 592 "dhcp6_parser.yy"
                                                                       {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1251 "dhcp6_parser.cc"
    break;

  case 143:
#line 597 "dhcp6_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1259 "dhcp6_parser.cc"
    break;

  case 144:
#line 599 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1268 "dhcp6_parser.cc"
    break;

  case 145:
#line 605 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1276 "dhcp6_parser.cc"
    break;

  case 146:
#line 608 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1284 "dhcp6_parser.cc"
    break;

  case 147:
#line 611 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1292 "dhcp6_parser.cc"
    break;

  case 148:
#line 614 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1300 "dhcp6_parser.cc"
    break;

  case 149:
#line 617 "dhcp6_parser.yy"
             {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1309 "dhcp6_parser.cc"
    break;

  case 150:
#line 623 "dhcp6_parser.yy"
                                             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1317 "dhcp6_parser.cc"
    break;

  case 151:
#line 625 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1327 "dhcp6_parser.cc"
    break;

  case 152:
#line 631 "dhcp6_parser.yy"
                                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1335 "dhcp6_parser.cc"
    break;

  case 153:
#line 633 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1345 "dhcp6_parser.cc"
    break;

  case 154:
#line 639 "dhcp6_parser.yy"
                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1353 "dhcp6_parser.cc"
    break;

  case 155:
#line 641 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1363 "dhcp6_parser.cc"
    break;

  case 156:
#line 647 "dhcp6_parser.yy"
                                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1371 "dhcp6_parser.cc"
    break;

  case 157:
#line 649 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1381 "dhcp6_parser.cc"
    break;

  case 158:
#line 655 "dhcp6_parser.yy"
                                                       {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1390 "dhcp6_parser.cc"
    break;

  case 159:
#line 660 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1398 "dhcp6_parser.cc"
    break;

  case 160:
#line 662 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1408 "dhcp6_parser.cc"
    break;

  case 161:
#line 668 "dhcp6_parser.yy"
                                     {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1419 "dhcp6_parser.cc"
    break;

  case 162:
#line 673 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1429 "dhcp6_parser.cc"
    break;

  case 163:
#line 679 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1439 "dhcp6_parser.cc"
    break;

  case 164:
#line 683 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1448 "dhcp6_parser.cc"
    break;

  case 172:
#line 699 "dhcp6_parser.yy"
                            {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1459 "dhcp6_parser.cc"
    break;

  case 173:
#line 704 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1468 "dhcp6_parser.cc"
    break;

  case 174:
#line 709 "dhcp6_parser.yy"
                                   {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1477 "dhcp6_parser.cc"
    break;

  case 175:
#line 715 "dhcp6_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1488 "dhcp6_parser.cc"
    break;

  case 176:
#line 720 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1499 "dhcp6_parser.cc"
    break;

  case 177:
#line 727 "dhcp6_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1510 "dhcp6_parser.cc"
    break;

  case 178:
#line 732 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1521 "dhcp6_parser.cc"
    break;

  case 179:
#line 739 "dhcp6_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1532 "dhcp6_parser.cc"
    break;

  case 180:
#line 744 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1541 "dhcp6_parser.cc"
    break;

  case 185:
#line 757 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1551 "dhcp6_parser.cc"
    break;

  case 186:
#line 761 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1561 "dhcp6_parser.cc"
    break;

  case 210:
#line 794 "dhcp6_parser.yy"
                    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1569 "dhcp6_parser.cc"
    break;

  case 211:
#line 796 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1578 "dhcp6_parser.cc"
    break;

  case 212:
#line 801 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1584 "dhcp6_parser.cc"
    break;

  case 213:
#line 802 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1590 "dhcp6_parser.cc"
    break;

  case 214:
#line 803 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1596 "dhcp6_parser.cc"
    break;

  case 215:
#line 804 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1602 "dhcp6_parser.cc"
    break;

  case 216:
#line 807 "dhcp6_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1610 "dhcp6_parser.cc"
    break;

  case 217:
#line 809 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1620 "dhcp6_parser.cc"
    break;

  case 218:
#line 815 "dhcp6_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1628 "dhcp6_parser.cc"
    break;

  case 219:
#line 817 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1638 "dhcp6_parser.cc"
    break;

  case 220:
#line 823 "dhcp6_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1646 "dhcp6_parser.cc"
    break;

  case 221:
#line 825 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1656 "dhcp6_parser.cc"
    break;

  case 222:
#line 831 "dhcp6_parser.yy"
                         {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1665 "dhcp6_parser.cc"
    break;

  case 223:
#line 836 "dhcp6_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1673 "dhcp6_parser.cc"
    break;

  case 224:
#line 838 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1683 "dhcp6_parser.cc"
    break;

  case 225:
#line 844 "dhcp6_parser.yy"
                               {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1692 "dhcp6_parser.cc"
    break;

  case 226:
#line 849 "dhcp6_parser.yy"
                                         {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1701 "dhcp6_parser.cc"
    break;

  case 227:
#line 854 "dhcp6_parser.yy"
                                 {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1710 "dhcp6_parser.cc"
    break;

  case 228:
#line 859 "dhcp6_parser.yy"
                                               {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1719 "dhcp6_parser.cc"
    break;

  case 229:
#line 864 "dhcp6_parser.yy"
                                                       {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1728 "dhcp6_parser.cc"
    break;

  case 230:
#line 869 "dhcp6_parser.yy"
                                             {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1737 "dhcp6_parser.cc"
    break;

  case 231:
#line 874 "dhcp6_parser.yy"
                                               {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1746 "dhcp6_parser.cc"
    break;

  case 232:
#line 879 "dhcp6_parser.yy"
                                           {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1755 "dhcp6_parser.cc"
    break;

  case 233:
#line 884 "dhcp6_parser.yy"
                                       {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1764 "dhcp6_parser.cc"
    break;

  case 234:
#line 889 "dhcp6_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1772 "dhcp6_parser.cc"
    break;

  case 235:
#line 891 "dhcp6_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1782 "dhcp6_parser.cc"
    break;

  case 236:
#line 897 "dhcp6_parser.yy"
                                                       {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1791 "dhcp6_parser.cc"
    break;

  case 237:
#line 902 "dhcp6_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1799 "dhcp6_parser.cc"
    break;

  case 238:
#line 904 "dhcp6_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1809 "dhcp6_parser.cc"
    break;

  case 239:
#line 910 "dhcp6_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1817 "dhcp6_parser.cc"
    break;

  case 240:
#line 912 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1827 "dhcp6_parser.cc"
    break;

  case 241:
#line 918 "dhcp6_parser.yy"
                                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1835 "dhcp6_parser.cc"
    break;

  case 242:
#line 920 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1845 "dhcp6_parser.cc"
    break;

  case 243:
#line 926 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1856 "dhcp6_parser.cc"
    break;

  case 244:
#line 931 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1865 "dhcp6_parser.cc"
    break;

  case 248:
#line 941 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1873 "dhcp6_parser.cc"
    break;

  case 249:
#line 943 "dhcp6_parser.yy"
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
#line 1893 "dhcp6_parser.cc"
    break;

  case 250:
#line 959 "dhcp6_parser.yy"
                         {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1904 "dhcp6_parser.cc"
    break;

  case 251:
#line 964 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1913 "dhcp6_parser.cc"
    break;

  case 256:
#line 977 "dhcp6_parser.yy"
               {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1922 "dhcp6_parser.cc"
    break;

  case 257:
#line 982 "dhcp6_parser.yy"
                   {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1931 "dhcp6_parser.cc"
    break;

  case 258:
#line 987 "dhcp6_parser.yy"
                                                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1942 "dhcp6_parser.cc"
    break;

  case 259:
#line 992 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1951 "dhcp6_parser.cc"
    break;

  case 265:
#line 1006 "dhcp6_parser.yy"
                           {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1960 "dhcp6_parser.cc"
    break;

  case 266:
#line 1011 "dhcp6_parser.yy"
                  {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1969 "dhcp6_parser.cc"
    break;

  case 267:
#line 1018 "dhcp6_parser.yy"
                                               {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1980 "dhcp6_parser.cc"
    break;

  case 268:
#line 1023 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1989 "dhcp6_parser.cc"
    break;

  case 269:
#line 1028 "dhcp6_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2000 "dhcp6_parser.cc"
    break;

  case 270:
#line 1033 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2009 "dhcp6_parser.cc"
    break;

  case 275:
#line 1046 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2019 "dhcp6_parser.cc"
    break;

  case 276:
#line 1050 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2029 "dhcp6_parser.cc"
    break;

  case 277:
#line 1056 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2039 "dhcp6_parser.cc"
    break;

  case 278:
#line 1060 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2049 "dhcp6_parser.cc"
    break;

  case 284:
#line 1075 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2057 "dhcp6_parser.cc"
    break;

  case 285:
#line 1077 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2067 "dhcp6_parser.cc"
    break;

  case 286:
#line 1083 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2075 "dhcp6_parser.cc"
    break;

  case 287:
#line 1085 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2084 "dhcp6_parser.cc"
    break;

  case 288:
#line 1091 "dhcp6_parser.yy"
                                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2095 "dhcp6_parser.cc"
    break;

  case 289:
#line 1096 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2105 "dhcp6_parser.cc"
    break;

  case 298:
#line 1114 "dhcp6_parser.yy"
                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2114 "dhcp6_parser.cc"
    break;

  case 299:
#line 1119 "dhcp6_parser.yy"
                                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2123 "dhcp6_parser.cc"
    break;

  case 300:
#line 1124 "dhcp6_parser.yy"
                                                       {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2132 "dhcp6_parser.cc"
    break;

  case 301:
#line 1129 "dhcp6_parser.yy"
                                                     {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2141 "dhcp6_parser.cc"
    break;

  case 302:
#line 1134 "dhcp6_parser.yy"
                                                 {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2150 "dhcp6_parser.cc"
    break;

  case 303:
#line 1139 "dhcp6_parser.yy"
                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2159 "dhcp6_parser.cc"
    break;

  case 304:
#line 1147 "dhcp6_parser.yy"
                      {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2170 "dhcp6_parser.cc"
    break;

  case 305:
#line 1152 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2179 "dhcp6_parser.cc"
    break;

  case 310:
#line 1172 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2189 "dhcp6_parser.cc"
    break;

  case 311:
#line 1176 "dhcp6_parser.yy"
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
#line 2215 "dhcp6_parser.cc"
    break;

  case 312:
#line 1198 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2225 "dhcp6_parser.cc"
    break;

  case 313:
#line 1202 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2235 "dhcp6_parser.cc"
    break;

  case 352:
#line 1252 "dhcp6_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2243 "dhcp6_parser.cc"
    break;

  case 353:
#line 1254 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2253 "dhcp6_parser.cc"
    break;

  case 354:
#line 1260 "dhcp6_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2261 "dhcp6_parser.cc"
    break;

  case 355:
#line 1262 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2271 "dhcp6_parser.cc"
    break;

  case 356:
#line 1268 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2279 "dhcp6_parser.cc"
    break;

  case 357:
#line 1270 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2289 "dhcp6_parser.cc"
    break;

  case 358:
#line 1276 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2297 "dhcp6_parser.cc"
    break;

  case 359:
#line 1278 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2307 "dhcp6_parser.cc"
    break;

  case 360:
#line 1284 "dhcp6_parser.yy"
                                               {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2318 "dhcp6_parser.cc"
    break;

  case 361:
#line 1289 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2327 "dhcp6_parser.cc"
    break;

  case 362:
#line 1294 "dhcp6_parser.yy"
                                   {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2335 "dhcp6_parser.cc"
    break;

  case 363:
#line 1296 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2344 "dhcp6_parser.cc"
    break;

  case 364:
#line 1301 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2350 "dhcp6_parser.cc"
    break;

  case 365:
#line 1302 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2356 "dhcp6_parser.cc"
    break;

  case 366:
#line 1303 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2362 "dhcp6_parser.cc"
    break;

  case 367:
#line 1304 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2368 "dhcp6_parser.cc"
    break;

  case 368:
#line 1307 "dhcp6_parser.yy"
                     {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2377 "dhcp6_parser.cc"
    break;

  case 369:
#line 1312 "dhcp6_parser.yy"
                                         {
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2386 "dhcp6_parser.cc"
    break;

  case 370:
#line 1320 "dhcp6_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2397 "dhcp6_parser.cc"
    break;

  case 371:
#line 1325 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2406 "dhcp6_parser.cc"
    break;

  case 376:
#line 1340 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2416 "dhcp6_parser.cc"
    break;

  case 377:
#line 1344 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2424 "dhcp6_parser.cc"
    break;

  case 413:
#line 1391 "dhcp6_parser.yy"
                            {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2435 "dhcp6_parser.cc"
    break;

  case 414:
#line 1396 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2444 "dhcp6_parser.cc"
    break;

  case 415:
#line 1404 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2453 "dhcp6_parser.cc"
    break;

  case 416:
#line 1407 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2461 "dhcp6_parser.cc"
    break;

  case 421:
#line 1423 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2471 "dhcp6_parser.cc"
    break;

  case 422:
#line 1427 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2483 "dhcp6_parser.cc"
    break;

  case 423:
#line 1438 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2493 "dhcp6_parser.cc"
    break;

  case 424:
#line 1442 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2505 "dhcp6_parser.cc"
    break;

  case 440:
#line 1474 "dhcp6_parser.yy"
                         {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2514 "dhcp6_parser.cc"
    break;

  case 442:
#line 1481 "dhcp6_parser.yy"
                      {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2522 "dhcp6_parser.cc"
    break;

  case 443:
#line 1483 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2532 "dhcp6_parser.cc"
    break;

  case 444:
#line 1489 "dhcp6_parser.yy"
                                      {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2540 "dhcp6_parser.cc"
    break;

  case 445:
#line 1491 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2550 "dhcp6_parser.cc"
    break;

  case 446:
#line 1497 "dhcp6_parser.yy"
             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2558 "dhcp6_parser.cc"
    break;

  case 447:
#line 1499 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2568 "dhcp6_parser.cc"
    break;

  case 449:
#line 1507 "dhcp6_parser.yy"
                                    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2576 "dhcp6_parser.cc"
    break;

  case 450:
#line 1509 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2586 "dhcp6_parser.cc"
    break;

  case 451:
#line 1515 "dhcp6_parser.yy"
                                      {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2595 "dhcp6_parser.cc"
    break;

  case 452:
#line 1524 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2606 "dhcp6_parser.cc"
    break;

  case 453:
#line 1529 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2615 "dhcp6_parser.cc"
    break;

  case 458:
#line 1548 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2625 "dhcp6_parser.cc"
    break;

  case 459:
#line 1552 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2634 "dhcp6_parser.cc"
    break;

  case 460:
#line 1560 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2644 "dhcp6_parser.cc"
    break;

  case 461:
#line 1564 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2653 "dhcp6_parser.cc"
    break;

  case 476:
#line 1597 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2661 "dhcp6_parser.cc"
    break;

  case 477:
#line 1599 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2671 "dhcp6_parser.cc"
    break;

  case 480:
#line 1609 "dhcp6_parser.yy"
                                                 {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2680 "dhcp6_parser.cc"
    break;

  case 481:
#line 1614 "dhcp6_parser.yy"
                                                   {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2689 "dhcp6_parser.cc"
    break;

  case 482:
#line 1622 "dhcp6_parser.yy"
                  {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2700 "dhcp6_parser.cc"
    break;

  case 483:
#line 1627 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2709 "dhcp6_parser.cc"
    break;

  case 488:
#line 1642 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2719 "dhcp6_parser.cc"
    break;

  case 489:
#line 1646 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2729 "dhcp6_parser.cc"
    break;

  case 490:
#line 1652 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2739 "dhcp6_parser.cc"
    break;

  case 491:
#line 1656 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2748 "dhcp6_parser.cc"
    break;

  case 501:
#line 1674 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2756 "dhcp6_parser.cc"
    break;

  case 502:
#line 1676 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2766 "dhcp6_parser.cc"
    break;

  case 503:
#line 1682 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2774 "dhcp6_parser.cc"
    break;

  case 504:
#line 1684 "dhcp6_parser.yy"
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
#line 2801 "dhcp6_parser.cc"
    break;

  case 505:
#line 1707 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2809 "dhcp6_parser.cc"
    break;

  case 506:
#line 1709 "dhcp6_parser.yy"
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
#line 2838 "dhcp6_parser.cc"
    break;

  case 507:
#line 1737 "dhcp6_parser.yy"
                        {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2849 "dhcp6_parser.cc"
    break;

  case 508:
#line 1742 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2858 "dhcp6_parser.cc"
    break;

  case 513:
#line 1757 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2868 "dhcp6_parser.cc"
    break;

  case 514:
#line 1761 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2880 "dhcp6_parser.cc"
    break;

  case 515:
#line 1769 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2890 "dhcp6_parser.cc"
    break;

  case 516:
#line 1773 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2902 "dhcp6_parser.cc"
    break;

  case 530:
#line 1798 "dhcp6_parser.yy"
                  {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2910 "dhcp6_parser.cc"
    break;

  case 531:
#line 1800 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2920 "dhcp6_parser.cc"
    break;

  case 532:
#line 1806 "dhcp6_parser.yy"
                                        {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2929 "dhcp6_parser.cc"
    break;

  case 533:
#line 1811 "dhcp6_parser.yy"
                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2937 "dhcp6_parser.cc"
    break;

  case 534:
#line 1813 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2947 "dhcp6_parser.cc"
    break;

  case 535:
#line 1819 "dhcp6_parser.yy"
                                                       {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2956 "dhcp6_parser.cc"
    break;

  case 536:
#line 1824 "dhcp6_parser.yy"
                                              {
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2965 "dhcp6_parser.cc"
    break;

  case 537:
#line 1832 "dhcp6_parser.yy"
                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2976 "dhcp6_parser.cc"
    break;

  case 538:
#line 1837 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2985 "dhcp6_parser.cc"
    break;

  case 543:
#line 1850 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2995 "dhcp6_parser.cc"
    break;

  case 544:
#line 1854 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3004 "dhcp6_parser.cc"
    break;

  case 545:
#line 1859 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3014 "dhcp6_parser.cc"
    break;

  case 546:
#line 1863 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3023 "dhcp6_parser.cc"
    break;

  case 562:
#line 1890 "dhcp6_parser.yy"
                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3034 "dhcp6_parser.cc"
    break;

  case 563:
#line 1895 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3043 "dhcp6_parser.cc"
    break;

  case 564:
#line 1900 "dhcp6_parser.yy"
                    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3054 "dhcp6_parser.cc"
    break;

  case 565:
#line 1905 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3063 "dhcp6_parser.cc"
    break;

  case 566:
#line 1910 "dhcp6_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3071 "dhcp6_parser.cc"
    break;

  case 567:
#line 1912 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3081 "dhcp6_parser.cc"
    break;

  case 568:
#line 1918 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3089 "dhcp6_parser.cc"
    break;

  case 569:
#line 1920 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3099 "dhcp6_parser.cc"
    break;

  case 570:
#line 1926 "dhcp6_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3107 "dhcp6_parser.cc"
    break;

  case 571:
#line 1928 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3117 "dhcp6_parser.cc"
    break;

  case 572:
#line 1934 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3125 "dhcp6_parser.cc"
    break;

  case 573:
#line 1936 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3135 "dhcp6_parser.cc"
    break;

  case 574:
#line 1942 "dhcp6_parser.yy"
                                           {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3146 "dhcp6_parser.cc"
    break;

  case 575:
#line 1947 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3155 "dhcp6_parser.cc"
    break;

  case 576:
#line 1955 "dhcp6_parser.yy"
             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3166 "dhcp6_parser.cc"
    break;

  case 577:
#line 1960 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3175 "dhcp6_parser.cc"
    break;

  case 580:
#line 1969 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3183 "dhcp6_parser.cc"
    break;

  case 581:
#line 1971 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3193 "dhcp6_parser.cc"
    break;

  case 582:
#line 1980 "dhcp6_parser.yy"
                               {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3204 "dhcp6_parser.cc"
    break;

  case 583:
#line 1985 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3213 "dhcp6_parser.cc"
    break;

  case 586:
#line 1994 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3223 "dhcp6_parser.cc"
    break;

  case 587:
#line 1998 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3233 "dhcp6_parser.cc"
    break;

  case 600:
#line 2023 "dhcp6_parser.yy"
                        {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3241 "dhcp6_parser.cc"
    break;

  case 601:
#line 2025 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3251 "dhcp6_parser.cc"
    break;

  case 602:
#line 2031 "dhcp6_parser.yy"
                                                 {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3260 "dhcp6_parser.cc"
    break;

  case 603:
#line 2039 "dhcp6_parser.yy"
                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3271 "dhcp6_parser.cc"
    break;

  case 604:
#line 2044 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3282 "dhcp6_parser.cc"
    break;

  case 616:
#line 2066 "dhcp6_parser.yy"
                     {
    ctx.enter(ctx.DUID_TYPE);
}
#line 3290 "dhcp6_parser.cc"
    break;

  case 617:
#line 2068 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3299 "dhcp6_parser.cc"
    break;

  case 618:
#line 2073 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3305 "dhcp6_parser.cc"
    break;

  case 619:
#line 2074 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3311 "dhcp6_parser.cc"
    break;

  case 620:
#line 2075 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3317 "dhcp6_parser.cc"
    break;

  case 621:
#line 2078 "dhcp6_parser.yy"
                           {
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3326 "dhcp6_parser.cc"
    break;

  case 622:
#line 2083 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3334 "dhcp6_parser.cc"
    break;

  case 623:
#line 2085 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3344 "dhcp6_parser.cc"
    break;

  case 624:
#line 2091 "dhcp6_parser.yy"
                         {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3353 "dhcp6_parser.cc"
    break;

  case 625:
#line 2096 "dhcp6_parser.yy"
                                           {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3362 "dhcp6_parser.cc"
    break;

  case 626:
#line 2103 "dhcp6_parser.yy"
                                         {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3371 "dhcp6_parser.cc"
    break;

  case 627:
#line 2110 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3382 "dhcp6_parser.cc"
    break;

  case 628:
#line 2115 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3391 "dhcp6_parser.cc"
    break;

  case 636:
#line 2131 "dhcp6_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3399 "dhcp6_parser.cc"
    break;

  case 637:
#line 2133 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3409 "dhcp6_parser.cc"
    break;

  case 638:
#line 2139 "dhcp6_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3417 "dhcp6_parser.cc"
    break;

  case 639:
#line 2141 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3427 "dhcp6_parser.cc"
    break;

  case 640:
#line 2149 "dhcp6_parser.yy"
                                       {
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3438 "dhcp6_parser.cc"
    break;

  case 641:
#line 2154 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3449 "dhcp6_parser.cc"
    break;

  case 650:
#line 2173 "dhcp6_parser.yy"
                                         {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3458 "dhcp6_parser.cc"
    break;

  case 651:
#line 2178 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3466 "dhcp6_parser.cc"
    break;

  case 652:
#line 2180 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3476 "dhcp6_parser.cc"
    break;

  case 653:
#line 2186 "dhcp6_parser.yy"
                                 {
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3485 "dhcp6_parser.cc"
    break;

  case 654:
#line 2191 "dhcp6_parser.yy"
                            {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3493 "dhcp6_parser.cc"
    break;

  case 655:
#line 2193 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3502 "dhcp6_parser.cc"
    break;

  case 656:
#line 2200 "dhcp6_parser.yy"
                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3513 "dhcp6_parser.cc"
    break;

  case 657:
#line 2205 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3524 "dhcp6_parser.cc"
    break;

  case 658:
#line 2212 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3534 "dhcp6_parser.cc"
    break;

  case 659:
#line 2216 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3544 "dhcp6_parser.cc"
    break;

  case 680:
#line 2246 "dhcp6_parser.yy"
                                             {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3553 "dhcp6_parser.cc"
    break;

  case 681:
#line 2251 "dhcp6_parser.yy"
                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3561 "dhcp6_parser.cc"
    break;

  case 682:
#line 2253 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3571 "dhcp6_parser.cc"
    break;

  case 683:
#line 2259 "dhcp6_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3579 "dhcp6_parser.cc"
    break;

  case 684:
#line 2261 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3589 "dhcp6_parser.cc"
    break;

  case 685:
#line 2267 "dhcp6_parser.yy"
                                       {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3598 "dhcp6_parser.cc"
    break;

  case 686:
#line 2272 "dhcp6_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3606 "dhcp6_parser.cc"
    break;

  case 687:
#line 2274 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3616 "dhcp6_parser.cc"
    break;

  case 688:
#line 2280 "dhcp6_parser.yy"
                                       {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3625 "dhcp6_parser.cc"
    break;

  case 689:
#line 2285 "dhcp6_parser.yy"
                                             {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3634 "dhcp6_parser.cc"
    break;

  case 690:
#line 2290 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3642 "dhcp6_parser.cc"
    break;

  case 691:
#line 2292 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3651 "dhcp6_parser.cc"
    break;

  case 692:
#line 2298 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3657 "dhcp6_parser.cc"
    break;

  case 693:
#line 2299 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3663 "dhcp6_parser.cc"
    break;

  case 694:
#line 2302 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3671 "dhcp6_parser.cc"
    break;

  case 695:
#line 2304 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3681 "dhcp6_parser.cc"
    break;

  case 696:
#line 2311 "dhcp6_parser.yy"
                                                         {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3690 "dhcp6_parser.cc"
    break;

  case 697:
#line 2317 "dhcp6_parser.yy"
                                                                 {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3699 "dhcp6_parser.cc"
    break;

  case 698:
#line 2323 "dhcp6_parser.yy"
                                             {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3707 "dhcp6_parser.cc"
    break;

  case 699:
#line 2325 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3716 "dhcp6_parser.cc"
    break;

  case 700:
#line 2331 "dhcp6_parser.yy"
                                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3724 "dhcp6_parser.cc"
    break;

  case 701:
#line 2333 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3734 "dhcp6_parser.cc"
    break;

  case 702:
#line 2340 "dhcp6_parser.yy"
                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3742 "dhcp6_parser.cc"
    break;

  case 703:
#line 2342 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3752 "dhcp6_parser.cc"
    break;

  case 704:
#line 2349 "dhcp6_parser.yy"
                                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3760 "dhcp6_parser.cc"
    break;

  case 705:
#line 2351 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3770 "dhcp6_parser.cc"
    break;

  case 706:
#line 2359 "dhcp6_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3778 "dhcp6_parser.cc"
    break;

  case 707:
#line 2361 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3787 "dhcp6_parser.cc"
    break;

  case 708:
#line 2366 "dhcp6_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3795 "dhcp6_parser.cc"
    break;

  case 709:
#line 2368 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3804 "dhcp6_parser.cc"
    break;

  case 710:
#line 2373 "dhcp6_parser.yy"
                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3812 "dhcp6_parser.cc"
    break;

  case 711:
#line 2375 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3821 "dhcp6_parser.cc"
    break;

  case 712:
#line 2382 "dhcp6_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3832 "dhcp6_parser.cc"
    break;

  case 713:
#line 2387 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3842 "dhcp6_parser.cc"
    break;

  case 714:
#line 2393 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3852 "dhcp6_parser.cc"
    break;

  case 715:
#line 2397 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 3861 "dhcp6_parser.cc"
    break;

  case 720:
#line 2412 "dhcp6_parser.yy"
                                   {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3872 "dhcp6_parser.cc"
    break;

  case 721:
#line 2417 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3881 "dhcp6_parser.cc"
    break;

  case 722:
#line 2422 "dhcp6_parser.yy"
                                                             {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3890 "dhcp6_parser.cc"
    break;

  case 723:
#line 2432 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3901 "dhcp6_parser.cc"
    break;

  case 724:
#line 2437 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3910 "dhcp6_parser.cc"
    break;

  case 725:
#line 2442 "dhcp6_parser.yy"
                            {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3920 "dhcp6_parser.cc"
    break;

  case 726:
#line 2446 "dhcp6_parser.yy"
                                {
    // parsing completed
}
#line 3928 "dhcp6_parser.cc"
    break;

  case 730:
#line 2462 "dhcp6_parser.yy"
                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3939 "dhcp6_parser.cc"
    break;

  case 731:
#line 2467 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3948 "dhcp6_parser.cc"
    break;

  case 734:
#line 2479 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3958 "dhcp6_parser.cc"
    break;

  case 735:
#line 2483 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 3966 "dhcp6_parser.cc"
    break;

  case 745:
#line 2500 "dhcp6_parser.yy"
                                     {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3975 "dhcp6_parser.cc"
    break;

  case 746:
#line 2505 "dhcp6_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3983 "dhcp6_parser.cc"
    break;

  case 747:
#line 2507 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3993 "dhcp6_parser.cc"
    break;

  case 748:
#line 2513 "dhcp6_parser.yy"
                                    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4004 "dhcp6_parser.cc"
    break;

  case 749:
#line 2518 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4013 "dhcp6_parser.cc"
    break;

  case 752:
#line 2527 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4023 "dhcp6_parser.cc"
    break;

  case 753:
#line 2531 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4031 "dhcp6_parser.cc"
    break;

  case 761:
#line 2546 "dhcp6_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4039 "dhcp6_parser.cc"
    break;

  case 762:
#line 2548 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4049 "dhcp6_parser.cc"
    break;

  case 763:
#line 2554 "dhcp6_parser.yy"
                           {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4058 "dhcp6_parser.cc"
    break;

  case 764:
#line 2559 "dhcp6_parser.yy"
                               {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4067 "dhcp6_parser.cc"
    break;

  case 765:
#line 2564 "dhcp6_parser.yy"
                             {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4076 "dhcp6_parser.cc"
    break;

  case 766:
#line 2569 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4084 "dhcp6_parser.cc"
    break;

  case 767:
#line 2571 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4094 "dhcp6_parser.cc"
    break;


#line 4098 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -937;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     446,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,    60,    31,    69,    73,
      95,   116,   148,   150,   184,   208,   225,   273,   282,   295,
     315,   318,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,    31,  -126,    29,   201,    41,   508,   227,   268,
      88,   114,    78,    -6,   -73,   614,     0,   175,  -937,   326,
     335,   336,   334,   341,  -937,  -937,  -937,  -937,  -937,   362,
    -937,   109,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,   378,   383,   385,   388,   389,   391,
     393,   394,   395,   397,   398,   399,  -937,   402,   403,   404,
    -937,  -937,  -937,   405,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
     406,  -937,  -937,  -937,  -937,  -937,  -937,  -937,   173,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
     407,  -937,   174,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,   409,   413,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,   199,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,   200,  -937,  -937,  -937,  -937,  -937,   414,  -937,   415,
     417,  -937,  -937,  -937,  -937,  -937,  -937,   206,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,   361,   420,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,   418,  -937,  -937,   421,  -937,
    -937,  -937,   423,  -937,  -937,   422,   426,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
     429,   430,  -937,  -937,  -937,  -937,   427,   433,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
     236,  -937,  -937,  -937,   436,  -937,  -937,   437,  -937,   439,
     445,  -937,  -937,   449,   450,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,   265,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,   275,
    -937,  -937,  -937,   460,   276,  -937,  -937,  -937,  -937,    31,
      31,  -937,   244,   464,   465,   466,   469,   470,  -937,    29,
    -937,   471,   472,   473,   475,   476,   480,   291,   292,   293,
     298,   305,   308,   309,   311,   304,   294,   316,   312,   497,
     319,   322,   324,   500,   510,   512,   327,   513,   515,   520,
     522,   523,   526,   527,   528,   530,   531,   533,   534,   535,
     536,   537,   538,   349,   540,   541,   542,   543,   544,   559,
     201,  -937,   560,   376,    41,  -937,   569,   571,   572,   573,
     574,   386,   387,   575,   577,   578,   508,  -937,   581,   227,
    -937,   583,   396,   584,   408,   410,   268,  -937,   585,   587,
     597,   601,   602,   604,   605,  -937,    88,  -937,   606,   608,
     419,   612,   613,   615,   424,  -937,    78,   617,   443,   448,
    -937,    -6,   638,   641,   100,  -937,   451,   644,   645,   456,
     647,   458,   459,   650,   651,   467,   468,   656,   657,   658,
     661,   614,  -937,     0,  -937,   662,   491,   175,  -937,  -937,
    -937,   663,   611,   679,    31,    31,    31,  -937,   477,   688,
     693,   695,   696,   664,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,   511,  -937,  -937,  -937,
      -1,   517,   518,  -937,   700,   707,   708,   709,   529,    -3,
     714,   718,   719,   720,   721,   722,   724,   725,   727,   728,
    -937,   730,   731,   732,   539,   547,   726,  -937,   736,  -937,
    -937,   737,   738,   552,   553,   554,  -937,  -937,   736,   555,
     742,  -937,   557,  -937,   558,  -937,   561,  -937,  -937,  -937,
     736,   736,   736,   562,   563,   579,   580,  -937,   582,   586,
    -937,   588,   589,   590,  -937,  -937,   591,  -937,  -937,  -937,
     592,    31,  -937,  -937,   593,   594,  -937,   595,  -937,  -937,
     223,   568,  -937,  -937,    -1,   596,   598,   599,  -937,  -937,
     747,  -937,  -937,    31,   201,     0,  -937,  -937,  -937,  -937,
     175,    41,   101,   101,   746,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,   763,   764,   767,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,   769,   -37,    31,   159,   689,
     773,   788,   789,   -16,   144,   -43,    30,   614,  -937,  -937,
     790,  -937,  -937,   791,   792,  -937,  -937,  -937,  -937,  -937,
     -56,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
     746,  -937,   279,   287,   306,   307,  -937,  -937,  -937,  -937,
     796,   797,   798,   799,   800,  -937,   801,   802,  -937,  -937,
    -937,   804,   805,   806,   807,  -937,   310,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,   313,  -937,
     808,   809,  -937,  -937,   810,   812,  -937,  -937,   811,   815,
    -937,  -937,   813,   817,  -937,  -937,   816,   818,  -937,  -937,
    -937,    43,  -937,  -937,  -937,   819,  -937,  -937,  -937,   118,
    -937,  -937,  -937,  -937,   320,  -937,  -937,  -937,   143,  -937,
    -937,   820,   821,  -937,  -937,   822,   824,  -937,   825,   826,
     827,   828,   829,   830,   321,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,   831,   832,   833,  -937,  -937,  -937,
    -937,   323,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,   338,  -937,  -937,  -937,   834,  -937,   835,
    -937,  -937,  -937,   351,  -937,  -937,  -937,  -937,  -937,   352,
    -937,   161,  -937,   620,  -937,   836,   837,  -937,  -937,   838,
     840,  -937,  -937,  -937,   839,  -937,   842,  -937,  -937,  -937,
    -937,   841,   845,   846,   847,   652,   659,   660,   665,   666,
     848,   668,   669,   849,   852,   853,   670,   671,   672,   673,
     101,  -937,  -937,   101,  -937,   746,   508,  -937,   763,    78,
    -937,   764,    -6,  -937,   767,   630,  -937,   769,   -37,  -937,
    -937,   159,  -937,   854,   689,  -937,   126,   773,  -937,    88,
    -937,   788,   -73,  -937,   789,   675,   676,   677,   678,   680,
     681,   -16,  -937,   855,   862,   682,   683,   684,   144,  -937,
     869,   875,   -43,  -937,   685,   876,   690,   879,    30,  -937,
    -937,   221,   790,  -937,  -937,   881,   886,   227,  -937,   791,
     268,  -937,   792,   891,  -937,  -937,   218,   648,   697,   704,
    -937,  -937,  -937,  -937,  -937,   713,  -937,  -937,   740,   741,
     749,  -937,  -937,  -937,  -937,  -937,   353,  -937,   354,  -937,
     892,  -937,   903,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,   355,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,   754,  -937,  -937,   908,  -937,  -937,  -937,  -937,
    -937,   905,   912,  -937,  -937,  -937,  -937,  -937,   909,  -937,
     365,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,   257,
     756,  -937,  -937,  -937,  -937,   765,   785,  -937,  -937,   794,
    -937,    31,  -937,  -937,   915,  -937,  -937,  -937,  -937,  -937,
     367,  -937,  -937,  -937,  -937,  -937,  -937,   814,   369,  -937,
     373,  -937,   823,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,   630,
    -937,  -937,   916,   760,  -937,   126,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,   977,   843,   979,
     221,  -937,  -937,  -937,  -937,  -937,  -937,   850,  -937,  -937,
     980,  -937,   851,  -937,  -937,   991,  -937,  -937,   172,  -937,
      12,   991,  -937,  -937,   995,   998,  1002,  -937,   375,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  1004,   844,   856,   857,
    1006,    12,  -937,   860,  -937,  -937,  -937,   861,  -937,  -937,
    -937
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   163,     9,
     312,    11,   490,    13,   515,    15,   545,    17,   415,    19,
     423,    21,   460,    23,   277,    25,   658,    27,   725,    29,
     714,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     547,     0,   425,   462,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   723,   706,   708,   710,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   126,   712,
     161,   175,   177,   179,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   159,     0,     0,     0,
     143,   150,   152,     0,   304,   413,   452,   503,   505,   362,
     370,   250,   267,   258,   243,   582,   537,   269,   288,   603,
       0,   627,   640,   656,   154,   156,   730,   125,     0,    74,
      76,    77,    78,    79,    80,    81,    82,    83,    84,   112,
     113,   114,    85,   118,   119,   120,   121,   122,   123,   116,
     117,   124,   110,    88,    89,    90,    91,   107,    92,    94,
      93,    98,    99,    86,   111,    87,    96,    97,   105,   106,
     108,    95,   100,   101,   102,   103,   104,   109,   115,   172,
       0,   171,     0,   165,   167,   168,   169,   170,   482,   507,
     352,   354,   356,     0,     0,   360,   358,   576,   351,   316,
     317,   318,   319,   320,   321,   322,   323,   339,   340,   341,
     344,   345,   346,   347,   348,   349,   342,   343,   350,     0,
     314,   327,   328,   329,   332,   333,   335,   330,   331,   324,
     325,   337,   338,   326,   334,   336,   501,   500,   496,   497,
     495,     0,   492,   494,   498,   499,   530,     0,   533,     0,
       0,   529,   523,   524,   522,   527,   528,     0,   517,   519,
     520,   525,   526,   521,   574,   562,   564,   566,   568,   570,
     572,   561,   558,   559,   560,     0,   548,   549,   553,   554,
     551,   555,   556,   557,   552,     0,   442,   223,     0,   446,
     444,   449,     0,   438,   439,     0,   426,   427,   429,   441,
     430,   431,   432,   448,   433,   434,   435,   436,   437,   476,
       0,     0,   474,   475,   478,   479,     0,   463,   464,   466,
     467,   468,   469,   470,   471,   472,   473,   284,   286,   281,
       0,   279,   282,   283,     0,   681,   683,     0,   686,     0,
       0,   690,   694,     0,     0,   698,   700,   702,   704,   679,
     677,   678,     0,   660,   662,   663,   664,   665,   666,   667,
     668,   669,   670,   671,   672,   673,   674,   675,   676,     0,
     727,   729,   720,     0,     0,   716,   718,   719,    48,     0,
       0,    41,     0,     0,     0,     0,     0,     0,    59,     0,
      61,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    73,     0,     0,     0,   164,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   313,     0,     0,
     491,     0,     0,     0,     0,     0,     0,   516,     0,     0,
       0,     0,     0,     0,     0,   546,     0,   416,     0,     0,
       0,     0,     0,     0,     0,   424,     0,     0,     0,     0,
     461,     0,     0,     0,     0,   278,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   659,     0,   726,     0,     0,     0,   715,    52,
      45,     0,     0,     0,     0,     0,     0,    63,     0,     0,
       0,     0,     0,     0,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,     0,   140,   141,   142,
       0,     0,     0,   158,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     626,     0,     0,     0,     0,     0,     0,    75,     0,   174,
     166,     0,     0,     0,     0,     0,   368,   369,     0,     0,
       0,   315,     0,   493,     0,   532,     0,   535,   536,   518,
       0,     0,     0,     0,     0,     0,     0,   550,     0,     0,
     440,     0,     0,     0,   451,   428,     0,   480,   481,   465,
       0,     0,   280,   680,     0,     0,   685,     0,   688,   689,
       0,     0,   696,   697,     0,     0,     0,     0,   661,   728,
       0,   722,   717,     0,     0,     0,   707,   709,   711,   127,
       0,     0,     0,     0,   181,   160,   145,   146,   147,   148,
     149,   144,   151,   153,   306,   417,   454,    42,   504,   506,
     364,   365,   366,   367,   363,   372,     0,    49,     0,     0,
       0,   539,   271,     0,     0,     0,     0,     0,   155,   157,
       0,    53,   173,   484,   509,   353,   355,   357,   361,   359,
       0,   502,   531,   534,   575,   563,   565,   567,   569,   571,
     573,   443,   224,   447,   445,   450,   477,   285,   287,   682,
     684,   687,   692,   693,   691,   695,   699,   701,   703,   705,
     181,    46,     0,     0,     0,     0,   210,   216,   218,   220,
       0,     0,     0,     0,     0,   234,     0,     0,   237,   239,
     241,     0,     0,     0,     0,   209,     0,   187,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   201,   208,
     202,   203,   204,   199,   200,   205,   206,   207,     0,   185,
       0,   182,   183,   310,     0,   307,   308,   421,     0,   418,
     419,   458,     0,   455,   456,   376,     0,   373,   374,   256,
     257,     0,   252,   254,   255,     0,   265,   266,   262,     0,
     260,   263,   264,   248,     0,   245,   247,   586,     0,   584,
     543,     0,   540,   541,   275,     0,   272,   273,     0,     0,
       0,     0,     0,     0,     0,   290,   292,   293,   294,   295,
     296,   297,   616,   622,     0,     0,     0,   615,   612,   613,
     614,     0,   605,   607,   610,   608,   609,   611,   636,   638,
     635,   633,   634,     0,   629,   631,   632,     0,   651,     0,
     654,   647,   648,     0,   642,   644,   645,   646,   649,     0,
     734,     0,   732,    55,   488,     0,   485,   486,   513,     0,
     510,   511,   580,   579,     0,   578,     0,    71,   724,   713,
     162,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   176,   178,     0,   180,     0,     0,   305,     0,   425,
     414,     0,   462,   453,     0,     0,   371,     0,     0,   251,
     268,     0,   259,     0,     0,   244,   588,     0,   583,   547,
     538,     0,     0,   270,     0,     0,     0,     0,     0,     0,
       0,     0,   289,     0,     0,     0,     0,     0,     0,   604,
       0,     0,     0,   628,     0,     0,     0,     0,     0,   641,
     657,     0,     0,   731,    57,     0,    56,     0,   483,     0,
       0,   508,     0,     0,   577,   721,     0,     0,     0,     0,
     222,   225,   226,   227,   228,     0,   236,   229,     0,     0,
       0,   231,   232,   233,   230,   188,     0,   184,     0,   309,
       0,   420,     0,   457,   412,   391,   392,   393,   395,   396,
     397,   384,   385,   400,   401,   402,   405,   406,   407,   408,
     409,   410,   403,   404,   411,   380,   381,   382,   383,   389,
     390,   388,   394,     0,   378,   386,   398,   399,   387,   375,
     253,   261,     0,   246,   600,     0,   598,   599,   595,   596,
     597,     0,   589,   590,   592,   593,   594,   585,     0,   542,
       0,   274,   298,   299,   300,   301,   302,   303,   291,     0,
       0,   621,   624,   625,   606,     0,     0,   630,   650,     0,
     653,     0,   643,   748,     0,   746,   744,   738,   742,   743,
       0,   736,   740,   741,   739,   733,    54,     0,     0,   487,
       0,   512,     0,   212,   213,   214,   215,   211,   217,   219,
     221,   235,   238,   240,   242,   186,   311,   422,   459,     0,
     377,   249,     0,     0,   587,     0,   544,   276,   618,   619,
     620,   617,   623,   637,   639,   652,   655,     0,     0,     0,
       0,   735,    58,   489,   514,   581,   379,     0,   602,   591,
       0,   745,     0,   737,   601,     0,   747,   752,     0,   750,
       0,     0,   749,   761,     0,     0,     0,   766,     0,   754,
     756,   757,   758,   759,   760,   751,     0,     0,     0,     0,
       0,     0,   753,     0,   763,   764,   765,     0,   755,   762,
     767
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,    -5,  -937,   428,
    -937,  -937,  -937,  -937,  -937,  -937,   277,  -937,  -535,  -937,
    -937,  -937,   -74,  -937,  -937,  -937,   600,  -937,  -937,  -937,
    -937,   337,   548,  -937,  -937,   -62,   -42,   -40,   -34,   -30,
     -29,   -27,   -26,     4,     5,     7,  -937,     8,     9,    10,
      11,  -937,   350,    21,  -937,    23,  -937,    24,  -937,    26,
    -937,    36,  -937,  -937,  -937,  -937,  -937,  -937,   332,   546,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,   261,
    -937,    62,  -937,  -657,    72,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,   -66,  -937,  -691,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,    49,  -937,
    -937,  -937,  -937,  -937,    56,  -680,  -937,  -937,  -937,  -937,
      54,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,    42,
    -937,  -937,  -937,    45,   504,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,    38,  -937,  -937,  -937,  -937,  -937,  -937,  -936,
    -937,  -937,  -937,    74,  -937,  -937,  -937,    75,   549,  -937,
    -937,  -934,  -937,  -933,  -937,    32,  -937,    40,  -937,    39,
    -937,  -937,  -937,  -932,  -937,  -937,  -937,  -937,    63,  -937,
    -937,  -136,   953,  -937,  -937,  -937,  -937,  -937,    77,  -937,
    -937,  -937,    80,  -937,   525,  -937,   -76,  -937,  -937,  -937,
    -937,  -937,   -70,  -937,  -937,  -937,  -937,  -937,   -24,  -937,
    -937,  -937,    81,  -937,  -937,  -937,    84,  -937,   521,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
      17,  -937,  -937,  -937,    44,   566,  -937,  -937,   -58,  -937,
      -8,  -937,  -937,  -937,  -937,  -937,    25,  -937,  -937,  -937,
      28,   567,  -937,  -937,  -937,  -937,  -937,  -937,  -937,   -47,
    -937,  -937,  -937,    83,  -937,  -937,  -937,    79,  -937,   550,
     329,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -931,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,    85,  -937,  -937,  -937,  -110,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,    68,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,    65,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,    61,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,   356,   545,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,  -937,   390,   524,  -937,  -937,  -937,  -937,  -937,
    -937,  -937,   400,   551,   -72,  -937,  -937,    64,  -937,  -937,
    -122,  -937,  -937,  -937,  -937,  -937,  -937,  -139,  -937,  -937,
    -157,  -937,  -937,  -937,  -937,  -937,  -937,  -937
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   698,    92,    93,    43,    72,    89,    90,   722,   913,
    1015,  1016,   785,    45,    74,   101,   102,   103,   413,    47,
      75,   158,   159,   160,   421,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   443,   691,   177,   444,   178,   445,   179,   467,   180,
     468,   181,   182,   439,   183,   423,    49,    76,   212,   213,
     214,   472,   215,   184,   424,   185,   425,   186,   426,   810,
     811,   812,   953,   786,   787,   788,   931,  1157,   789,   932,
     790,   933,   791,   934,   792,   793,   509,   794,   795,   796,
     797,   798,   799,   800,   801,   802,   803,   940,   804,   805,
     943,   806,   944,   807,   945,   187,   457,   844,   845,   846,
     973,   188,   454,   831,   832,   833,   834,   189,   456,   839,
     840,   841,   842,   190,   455,   191,   460,   855,   856,   857,
     982,    65,    84,   360,   361,   362,   522,   363,   523,   192,
     461,   864,   865,   866,   867,   868,   869,   870,   871,   193,
     447,   814,   815,   816,   956,    51,    77,   249,   250,   251,
     478,   252,   479,   253,   480,   254,   484,   255,   483,   194,
     452,   704,   257,   258,   195,   453,   826,   827,   828,   965,
    1083,  1084,   196,   448,    59,    81,   818,   819,   820,   959,
      61,    82,   325,   326,   327,   328,   329,   330,   331,   508,
     332,   512,   333,   511,   334,   335,   513,   336,   197,   449,
     822,   823,   824,   962,    63,    83,   346,   347,   348,   349,
     350,   517,   351,   352,   353,   354,   260,   476,   915,   916,
     917,  1017,    53,    78,   271,   272,   273,   488,   198,   450,
     199,   451,   263,   477,   919,   920,   921,  1020,    55,    79,
     287,   288,   289,   491,   290,   291,   493,   292,   293,   200,
     459,   851,   852,   853,   979,    57,    80,   305,   306,   307,
     308,   499,   309,   500,   310,   501,   311,   502,   312,   503,
     313,   504,   314,   498,   265,   485,   924,   925,  1023,   201,
     458,   848,   849,   976,  1101,  1102,  1103,  1104,  1105,  1172,
    1106,   202,   462,   881,   882,   883,   993,  1181,   884,   885,
     994,   886,   887,   203,   204,   464,   893,   894,   895,  1000,
     896,  1001,   205,   465,   903,   904,   905,   906,  1005,   907,
     908,  1007,   206,   466,    67,    85,   382,   383,   384,   385,
     527,   386,   528,   387,   388,   530,   389,   390,   391,   533,
     754,   392,   534,   393,   394,   395,   537,   396,   538,   397,
     539,   398,   540,   104,   415,   105,   416,   106,   417,   207,
     422,    71,    87,   404,   405,   406,   545,   407,   107,   414,
      69,    86,   399,   400,   208,   469,   911,   912,  1011,  1140,
    1141,  1142,  1143,  1189,  1144,  1187,  1208,  1209,  1210,  1218,
    1219,  1220,  1226,  1221,  1222,  1223,  1224,  1230
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     100,   157,   211,   228,   267,   281,   301,   344,   323,   342,
     359,   379,    40,   345,   401,   229,   324,   343,   216,   261,
     274,   285,   303,   878,   337,   355,   808,   380,   838,  1076,
     264,  1077,  1078,  1082,  1088,   230,    33,   231,    34,    94,
      35,   137,   138,   232,   357,   358,   968,   233,   234,   969,
     235,   236,   295,   259,   270,   284,   302,   209,   210,   922,
      32,   317,   339,   318,   319,   340,   341,    91,   217,   262,
     275,   286,   304,   829,   338,   356,    44,   381,   137,   138,
      46,   237,   238,   728,   239,   240,   241,   242,   243,   700,
     701,   702,   703,   888,   889,   734,   735,   736,   244,   316,
     245,   246,    48,   247,   858,   859,   860,   861,   862,   863,
     268,   282,   419,   248,   137,   138,   256,   420,   269,   283,
      99,   971,   766,    50,   972,   137,   138,   767,   768,   769,
     770,   771,   772,   773,   774,   775,   776,   777,   778,   779,
     780,   781,   782,   783,   784,   317,   977,   318,   319,   978,
      99,   320,   321,   322,   136,    52,   830,    54,   686,   687,
     688,   689,   137,   138,  1012,   872,   156,  1013,   317,   897,
     898,   899,   137,   138,   771,  1211,   470,   474,  1212,   135,
    1213,   471,   475,  1214,  1215,  1216,  1217,    99,   402,   403,
     294,    56,   136,   317,    95,   690,   295,   296,   297,   298,
     299,   300,   486,   489,    96,    97,    98,   487,   490,   496,
     137,   138,   108,   109,   497,    58,   110,   357,   358,   111,
     112,   113,    99,   900,    36,    37,    38,    39,   137,   138,
    1094,  1095,    60,  1076,    99,  1077,  1078,  1082,  1088,   524,
    1153,  1154,  1155,  1156,   525,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   541,   829,
     836,    99,   837,   542,   873,   874,   875,   876,   543,   547,
      62,    99,   470,   544,   548,   137,   138,   927,   317,    64,
     543,   838,   139,   136,    99,   928,  1046,   140,   141,   142,
     143,   144,    66,   145,   266,   137,   138,   878,   146,   547,
     474,   137,   138,   950,   929,   930,   950,   147,   951,    99,
     148,   952,    68,   974,   991,    70,   998,   149,   975,   992,
     225,   999,   408,   226,   136,   150,   151,    99,   409,   152,
     410,  1002,   411,   153,   412,   100,  1003,   276,   277,   278,
     279,   280,   137,   138,  1008,   541,   950,   486,  1169,  1009,
    1010,  1165,  1166,  1170,   154,   155,   418,   156,   524,   505,
    1190,   225,   489,  1177,   226,  1191,   496,  1193,  1231,   752,
     753,  1194,   427,  1232,  1178,  1179,  1180,   428,  1133,   429,
    1134,  1135,   430,   431,    99,   432,   157,   433,   434,   435,
     211,   436,   437,   438,   549,   550,   440,   441,   442,   446,
     463,   473,   228,   481,    99,   267,   216,   482,   492,   494,
      99,   495,   281,   506,   229,   510,   507,   514,   261,   516,
     515,   274,   301,   518,   519,   520,   521,   551,   285,   264,
     526,   529,   323,   531,   230,   344,   231,   342,   303,   532,
     324,   345,   232,   535,   536,   343,   233,   234,   337,   235,
     236,    99,   259,   355,   546,   270,   217,   379,   552,   553,
     554,   401,   284,   555,   556,   558,   559,   560,   262,   561,
     562,   275,   302,   380,   563,   564,   565,   566,   286,   573,
     237,   238,   567,   239,   240,   241,   242,   243,   304,   568,
     572,   576,   569,   570,   580,   571,   575,   244,   338,   245,
     246,   574,   247,   356,   581,   577,   582,   584,   578,   585,
     579,   268,   248,   583,   586,   256,   587,   588,   282,   269,
     589,   590,   591,   381,   592,   593,   283,   594,   595,   596,
     597,   598,   599,   600,   601,   602,   603,   604,   605,   676,
     677,   678,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   606,   608,   127,   128,   129,   130,   131,
     132,   133,   609,   611,   136,   612,   613,   614,   615,   618,
     616,   619,   620,   617,   218,   622,   219,   624,   626,   630,
     625,   631,   137,   138,   220,   221,   222,   223,   224,   139,
     157,   632,   627,   401,   628,   633,   634,   211,   635,   636,
     638,   225,   639,   640,   226,   146,   641,   642,   674,   643,
     644,   646,   227,   216,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,   647,
     877,   890,   650,   379,   648,   651,   748,   653,   654,   655,
     656,   657,   658,   659,   660,   661,   879,   891,   901,   380,
     664,   665,   666,   662,   663,   667,   670,   673,   761,   684,
     679,   154,   155,   217,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   671,   675,   127,   128,   129,
     130,   131,   132,   133,   134,   680,   136,   317,   137,   138,
     681,    99,   682,   683,   685,   694,   880,   892,   902,   381,
     692,   693,   695,   696,   137,   138,    34,   221,   222,   705,
     224,   139,   699,   706,   707,   708,   755,   710,   709,   711,
     712,   720,   718,   225,   713,   714,   226,   715,   716,   717,
     719,   721,   723,   724,   227,   725,   726,   727,   729,   730,
     731,   732,   760,   809,   733,   737,   738,   364,   365,   366,
     367,   368,   369,   370,   371,   372,   373,   374,   375,   376,
     813,   817,   739,   740,   821,   741,   825,   377,   378,   742,
     847,   743,   744,   745,   746,   747,   749,   750,   751,   757,
     843,   758,   759,   154,   155,   850,   854,   910,   914,   918,
     935,   936,   937,   938,   939,   941,   942,    99,   946,   947,
     948,   949,   955,  1014,   954,   958,   957,   960,   961,   963,
     964,   967,   966,    99,   981,   970,   980,   984,   983,   985,
     986,   987,   988,   989,   990,   995,   996,   997,  1004,  1006,
    1019,  1158,  1018,  1022,  1021,  1026,  1030,  1024,  1025,  1027,
    1028,  1029,  1035,  1038,  1032,  1031,  1039,  1040,  1092,  1119,
    1034,  1033,  1036,  1037,  1041,  1042,  1120,  1044,  1043,  1112,
    1113,  1114,  1115,  1125,  1116,  1117,  1121,  1122,  1123,  1126,
    1129,  1128,   228,  1131,  1130,   323,   344,  1146,   342,  1147,
    1159,  1054,   345,   324,   229,  1152,   343,  1160,   261,  1075,
    1167,   337,  1096,  1055,   355,   301,  1161,  1086,   359,   264,
    1097,  1168,  1173,  1174,   230,  1175,   231,  1176,  1099,  1188,
    1197,   303,   232,  1056,   877,  1057,   233,   234,   890,   235,
     236,  1058,   259,  1162,  1163,  1059,  1060,  1136,  1061,  1062,
     879,  1085,  1164,   267,   891,  1137,   281,  1171,   262,  1182,
     901,   338,  1098,  1138,   356,   302,  1198,  1087,  1183,   274,
     237,   238,   285,   239,   240,   241,   242,   243,  1100,  1063,
    1064,   304,  1065,  1066,  1067,  1068,  1069,   244,  1184,   245,
     246,  1200,   247,  1202,   835,  1205,  1070,  1185,  1071,  1072,
     880,  1073,   248,   270,   892,   256,   284,  1079,  1207,  1227,
     902,  1074,  1228,  1139,  1081,  1080,  1229,  1192,  1233,   275,
    1237,   762,   286,   765,   756,   697,  1195,  1047,   607,   557,
     610,   926,  1045,  1093,  1090,  1091,  1111,  1110,   652,  1118,
    1089,  1048,  1049,  1196,   315,   621,  1149,  1201,  1051,  1050,
    1234,   645,   649,  1204,  1206,  1053,  1052,  1151,  1150,   268,
    1235,  1236,   282,  1239,  1240,   623,   637,   269,  1108,   923,
     283,  1148,  1107,   629,  1109,  1199,  1124,  1127,  1203,  1132,
     764,   672,  1225,   909,  1238,   763,  1145,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   668,     0,     0,     0,
       0,     0,     0,     0,   669,  1054,     0,     0,     0,     0,
       0,  1096,     0,  1075,     0,     0,     0,  1055,     0,  1097,
       0,  1086,     0,     0,     0,     0,  1136,  1099,     0,     0,
       0,     0,     0,     0,  1137,     0,  1186,  1056,     0,  1057,
       0,     0,  1138,     0,     0,  1058,     0,     0,     0,  1059,
    1060,     0,  1061,  1062,     0,  1085,     0,     0,     0,     0,
       0,  1098,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1087,     0,     0,     0,     0,     0,  1100,     0,     0,
       0,     0,     0,  1063,  1064,     0,  1065,  1066,  1067,  1068,
    1069,     0,  1139,     0,     0,     0,     0,     0,     0,     0,
    1070,     0,  1071,  1072,     0,  1073,     0,     0,     0,     0,
       0,  1079,     0,     0,     0,  1074,     0,     0,  1081,  1080
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    83,    82,    83,
      84,    85,    17,    83,    86,    77,    82,    83,    76,    77,
      78,    79,    80,   714,    82,    83,   683,    85,   708,   965,
      77,   965,   965,   965,   965,    77,     5,    77,     7,    10,
       9,    84,    85,    77,   117,   118,     3,    77,    77,     6,
      77,    77,   108,    77,    78,    79,    80,    16,    17,   115,
       0,    67,    68,    69,    70,    71,    72,   193,    76,    77,
      78,    79,    80,   110,    82,    83,     7,    85,    84,    85,
       7,    77,    77,   618,    77,    77,    77,    77,    77,    92,
      93,    94,    95,   136,   137,   630,   631,   632,    77,    21,
      77,    77,     7,    77,   120,   121,   122,   123,   124,   125,
      78,    79,     3,    77,    84,    85,    77,     8,    78,    79,
     193,     3,    21,     7,     6,    84,    85,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    67,     3,    69,    70,     6,
     193,    73,    74,    75,    66,     7,   193,     7,   159,   160,
     161,   162,    84,    85,     3,    21,   166,     6,    67,   139,
     140,   141,    84,    85,    30,     3,     3,     3,     6,    65,
     168,     8,     8,   171,   172,   173,   174,   193,    13,    14,
     102,     7,    66,    67,   165,   196,   108,   109,   110,   111,
     112,   113,     3,     3,   175,   176,   177,     8,     8,     3,
      84,    85,    11,    12,     8,     7,    15,   117,   118,    18,
      19,    20,   193,   193,   193,   194,   195,   196,    84,    85,
     104,   105,     7,  1169,   193,  1169,  1169,  1169,  1169,     3,
      22,    23,    24,    25,     8,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,     3,   110,
     111,   193,   113,     8,   130,   131,   132,   133,     3,     3,
       7,   193,     3,     8,     8,    84,    85,     8,    67,     7,
       3,   971,    91,    66,   193,     8,   953,    96,    97,    98,
      99,   100,     7,   102,    77,    84,    85,   998,   107,     3,
       3,    84,    85,     3,     8,     8,     3,   116,     8,   193,
     119,     8,     7,     3,     3,     7,     3,   126,     8,     8,
     103,     8,     6,   106,    66,   134,   135,   193,     3,   138,
       4,     3,     8,   142,     3,   419,     8,    79,    80,    81,
      82,    83,    84,    85,     3,     3,     3,     3,     3,     8,
       8,     8,     8,     8,   163,   164,     4,   166,     3,     8,
       3,   103,     3,     8,   106,     8,     3,     8,     3,   156,
     157,     8,     4,     8,   127,   128,   129,     4,   167,     4,
     169,   170,     4,     4,   193,     4,   470,     4,     4,     4,
     474,     4,     4,     4,   409,   410,     4,     4,     4,     4,
       4,     4,   486,     4,   193,   489,   474,     4,     4,     4,
     193,     4,   496,     3,   486,     4,     8,     4,   486,     3,
       8,   489,   506,     4,     4,     8,     3,   193,   496,   486,
       4,     4,   516,     4,   486,   521,   486,   521,   506,     4,
     516,   521,   486,     4,     4,   521,   486,   486,   516,   486,
     486,   193,   486,   521,     4,   489,   474,   541,     4,     4,
       4,   543,   496,     4,     4,     4,     4,     4,   486,     4,
       4,   489,   506,   541,     4,   194,   194,   194,   496,   195,
     486,   486,   194,   486,   486,   486,   486,   486,   506,   194,
     196,     4,   194,   194,     4,   194,   194,   486,   516,   486,
     486,   195,   486,   521,     4,   196,     4,     4,   196,     4,
     196,   489,   486,   196,     4,   486,     4,     4,   496,   489,
       4,     4,     4,   541,     4,     4,   496,     4,     4,     4,
       4,     4,     4,   194,     4,     4,     4,     4,     4,   554,
     555,   556,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,     4,     4,    57,    58,    59,    60,    61,
      62,    63,   196,     4,    66,     4,     4,     4,     4,     4,
     194,     4,     4,   196,    76,     4,    78,     4,     4,     4,
     194,     4,    84,    85,    86,    87,    88,    89,    90,    91,
     674,     4,   194,   675,   194,     4,     4,   681,     4,     4,
       4,   103,     4,   194,   106,   107,     4,     4,     7,     4,
     196,     4,   114,   681,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   196,
     714,   715,     4,   717,   196,     4,   651,   196,     4,     4,
     194,     4,   194,   194,     4,     4,   714,   715,   716,   717,
       4,     4,     4,   196,   196,     4,     4,     4,   673,     5,
     193,   163,   164,   681,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,   194,     7,    57,    58,    59,
      60,    61,    62,    63,    64,     7,    66,    67,    84,    85,
       7,   193,     7,     7,   193,     5,   714,   715,   716,   717,
     193,   193,     5,     5,    84,    85,     7,    87,    88,     5,
      90,    91,   193,     5,     5,     5,   158,     5,     7,     5,
       5,     5,   193,   103,     7,     7,   106,     7,     7,     7,
     193,     5,     5,     5,   114,   193,   193,   193,   193,     7,
     193,   193,     5,     7,   193,   193,   193,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
       7,     7,   193,   193,     7,   193,     7,   163,   164,   193,
       7,   193,   193,   193,   193,   193,   193,   193,   193,   193,
     101,   193,   193,   163,   164,     7,     7,     7,     7,     7,
       4,     4,     4,     4,     4,     4,     4,   193,     4,     4,
       4,     4,     3,   193,     6,     3,     6,     6,     3,     6,
       3,     3,     6,   193,     3,     6,     6,     3,     6,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       3,   193,     6,     3,     6,     4,   194,     8,     6,     4,
       4,     4,     4,     4,   194,   196,     4,     4,     4,     4,
     194,   196,   194,   194,   194,   194,     4,   194,   196,   194,
     194,   194,   194,     4,   194,   194,   194,   194,   194,     4,
       4,   196,   956,     4,   194,   959,   962,     6,   962,     3,
     193,   965,   962,   959,   956,     4,   962,   193,   956,   965,
       8,   959,   976,   965,   962,   979,   193,   965,   982,   956,
     976,     8,     4,     8,   956,     3,   956,     8,   976,     4,
       4,   979,   956,   965,   998,   965,   956,   956,  1002,   956,
     956,   965,   956,   193,   193,   965,   965,  1011,   965,   965,
     998,   965,   193,  1017,  1002,  1011,  1020,   193,   956,   193,
    1008,   959,   976,  1011,   962,   979,   196,   965,   193,  1017,
     956,   956,  1020,   956,   956,   956,   956,   956,   976,   965,
     965,   979,   965,   965,   965,   965,   965,   956,   193,   956,
     956,     4,   956,     4,   707,     5,   965,   193,   965,   965,
     998,   965,   956,  1017,  1002,   956,  1020,   965,     7,     4,
    1008,   965,     4,  1011,   965,   965,     4,   193,     4,  1017,
       4,   674,  1020,   681,   664,   587,   193,   955,   470,   419,
     474,   760,   950,   974,   968,   971,   984,   982,   524,   991,
     967,   956,   958,  1169,    81,   486,  1019,   194,   961,   959,
     196,   516,   521,   193,   193,   964,   962,  1022,  1020,  1017,
     194,   194,  1020,   193,   193,   489,   506,  1017,   979,   730,
    1020,  1017,   977,   496,   981,  1175,   998,  1002,  1190,  1008,
     680,   547,  1211,   717,  1231,   675,  1012,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   541,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   543,  1169,    -1,    -1,    -1,    -1,
      -1,  1175,    -1,  1169,    -1,    -1,    -1,  1169,    -1,  1175,
      -1,  1169,    -1,    -1,    -1,    -1,  1190,  1175,    -1,    -1,
      -1,    -1,    -1,    -1,  1190,    -1,  1131,  1169,    -1,  1169,
      -1,    -1,  1190,    -1,    -1,  1169,    -1,    -1,    -1,  1169,
    1169,    -1,  1169,  1169,    -1,  1169,    -1,    -1,    -1,    -1,
      -1,  1175,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1169,    -1,    -1,    -1,    -1,    -1,  1175,    -1,    -1,
      -1,    -1,    -1,  1169,  1169,    -1,  1169,  1169,  1169,  1169,
    1169,    -1,  1190,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1169,    -1,  1169,  1169,    -1,  1169,    -1,    -1,    -1,    -1,
      -1,  1169,    -1,    -1,    -1,  1169,    -1,    -1,  1169,  1169
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,     0,     5,     7,     9,   193,   194,   195,   196,
     214,   215,   216,   221,     7,   230,     7,   236,     7,   273,
       7,   372,     7,   449,     7,   465,     7,   482,     7,   401,
       7,   407,     7,   431,     7,   348,     7,   551,     7,   597,
       7,   588,   222,   217,   231,   237,   274,   373,   450,   466,
     483,   402,   408,   432,   349,   552,   598,   589,   214,   223,
     224,   193,   219,   220,    10,   165,   175,   176,   177,   193,
     229,   232,   233,   234,   580,   582,   584,   595,    11,    12,
      15,    18,    19,    20,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    84,    85,    91,
      96,    97,    98,    99,   100,   102,   107,   116,   119,   126,
     134,   135,   138,   142,   163,   164,   166,   229,   238,   239,
     240,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   260,   262,   264,
     266,   268,   269,   271,   280,   282,   284,   322,   328,   334,
     340,   342,   356,   366,   386,   391,   399,   425,   455,   457,
     476,   506,   518,   530,   531,   539,   549,   586,   601,    16,
      17,   229,   275,   276,   277,   279,   455,   457,    76,    78,
      86,    87,    88,    89,    90,   103,   106,   114,   229,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     254,   255,   256,   257,   260,   262,   264,   266,   268,   374,
     375,   376,   378,   380,   382,   384,   386,   389,   390,   425,
     443,   455,   457,   459,   476,   501,    77,   229,   382,   384,
     425,   451,   452,   453,   455,   457,    79,    80,    81,    82,
      83,   229,   382,   384,   425,   455,   457,   467,   468,   469,
     471,   472,   474,   475,   102,   108,   109,   110,   111,   112,
     113,   229,   425,   455,   457,   484,   485,   486,   487,   489,
     491,   493,   495,   497,   499,   399,    21,    67,    69,    70,
      73,    74,    75,   229,   302,   409,   410,   411,   412,   413,
     414,   415,   417,   419,   421,   422,   424,   455,   457,    68,
      71,    72,   229,   302,   413,   419,   433,   434,   435,   436,
     437,   439,   440,   441,   442,   455,   457,   117,   118,   229,
     350,   351,   352,   354,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   163,   164,   229,
     455,   457,   553,   554,   555,   556,   558,   560,   561,   563,
     564,   565,   568,   570,   571,   572,   574,   576,   578,   599,
     600,   601,    13,    14,   590,   591,   592,   594,     6,     3,
       4,     8,     3,   235,   596,   581,   583,   585,     4,     3,
       8,   241,   587,   272,   281,   283,   285,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   270,
       4,     4,     4,   258,   261,   263,     4,   367,   400,   426,
     456,   458,   387,   392,   329,   341,   335,   323,   507,   477,
     343,   357,   519,     4,   532,   540,   550,   265,   267,   602,
       3,     8,   278,     4,     3,     8,   444,   460,   377,   379,
     381,     4,     4,   385,   383,   502,     3,     8,   454,     3,
       8,   470,     4,   473,     4,     4,     3,     8,   500,   488,
     490,   492,   494,   496,   498,     8,     3,     8,   416,   303,
       4,   420,   418,   423,     4,     8,     3,   438,     4,     4,
       8,     3,   353,   355,     3,     8,     4,   557,   559,     4,
     562,     4,     4,   566,   569,     4,     4,   573,   575,   577,
     579,     3,     8,     3,     8,   593,     4,     3,     8,   214,
     214,   193,     4,     4,     4,     4,     4,   233,     4,     4,
       4,     4,     4,     4,   194,   194,   194,   194,   194,   194,
     194,   194,   196,   195,   195,   194,     4,   196,   196,   196,
       4,     4,     4,   196,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     194,     4,     4,     4,     4,     4,     4,   239,     4,   196,
     276,     4,     4,     4,     4,     4,   194,   196,     4,     4,
       4,   375,     4,   452,     4,   194,     4,   194,   194,   468,
       4,     4,     4,     4,     4,     4,     4,   486,     4,     4,
     194,     4,     4,     4,   196,   411,     4,   196,   196,   435,
       4,     4,   351,   196,     4,     4,   194,     4,   194,   194,
       4,     4,   196,   196,     4,     4,     4,     4,   554,   600,
       4,   194,   591,     4,     7,     7,   214,   214,   214,   193,
       7,     7,     7,     7,     5,   193,   159,   160,   161,   162,
     196,   259,   193,   193,     5,     5,     5,   216,   218,   193,
      92,    93,    94,    95,   388,     5,     5,     5,     5,     7,
       5,     5,     5,     7,     7,     7,     7,     7,   193,   193,
       5,     5,   225,     5,     5,   193,   193,   193,   225,   193,
       7,   193,   193,   193,   225,   225,   225,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   214,   193,
     193,   193,   156,   157,   567,   158,   259,   193,   193,   193,
       5,   214,   238,   599,   590,   275,    21,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,   229,   290,   291,   292,   295,
     297,   299,   301,   302,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   315,   316,   318,   320,   290,     7,
     286,   287,   288,     7,   368,   369,   370,     7,   403,   404,
     405,     7,   427,   428,   429,     7,   393,   394,   395,   110,
     193,   330,   331,   332,   333,   223,   111,   113,   332,   336,
     337,   338,   339,   101,   324,   325,   326,     7,   508,   509,
       7,   478,   479,   480,     7,   344,   345,   346,   120,   121,
     122,   123,   124,   125,   358,   359,   360,   361,   362,   363,
     364,   365,    21,   130,   131,   132,   133,   229,   304,   455,
     457,   520,   521,   522,   525,   526,   528,   529,   136,   137,
     229,   455,   457,   533,   534,   535,   537,   139,   140,   141,
     193,   455,   457,   541,   542,   543,   544,   546,   547,   553,
       7,   603,   604,   226,     7,   445,   446,   447,     7,   461,
     462,   463,   115,   487,   503,   504,   286,     8,     8,     8,
       8,   293,   296,   298,   300,     4,     4,     4,     4,     4,
     314,     4,     4,   317,   319,   321,     4,     4,     4,     4,
       3,     8,     8,   289,     6,     3,   371,     6,     3,   406,
       6,     3,   430,     6,     3,   396,     6,     3,     3,     6,
       6,     3,     6,   327,     3,     8,   510,     3,     6,   481,
       6,     3,   347,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   523,   527,     4,     4,     4,     3,     8,
     536,   538,     3,     8,     4,   545,     4,   548,     3,     8,
       8,   605,     3,     6,   193,   227,   228,   448,     6,     3,
     464,     6,     3,   505,     8,     6,     4,     4,     4,     4,
     194,   196,   194,   196,   194,     4,   194,   194,     4,     4,
       4,   194,   194,   196,   194,   291,   290,   288,   374,   370,
     409,   405,   433,   429,   229,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   254,   255,   256,   257,
     260,   262,   264,   266,   268,   302,   366,   378,   380,   382,
     384,   386,   390,   397,   398,   425,   455,   457,   501,   395,
     331,   337,     4,   325,   104,   105,   229,   302,   425,   455,
     457,   511,   512,   513,   514,   515,   517,   509,   484,   480,
     350,   346,   194,   194,   194,   194,   194,   194,   359,     4,
       4,   194,   194,   194,   521,     4,     4,   534,   196,     4,
     194,     4,   542,   167,   169,   170,   229,   302,   455,   457,
     606,   607,   608,   609,   611,   604,     6,     3,   451,   447,
     467,   463,     4,    22,    23,    24,    25,   294,   193,   193,
     193,   193,   193,   193,   193,     8,     8,     8,     8,     3,
       8,   193,   516,     4,     8,     3,     8,     8,   127,   128,
     129,   524,   193,   193,   193,   193,   214,   612,     4,   610,
       3,     8,   193,     8,     8,   193,   398,     4,   196,   513,
       4,   194,     4,   607,   193,     5,   193,     7,   613,   614,
     615,     3,     6,   168,   171,   172,   173,   174,   616,   617,
     618,   620,   621,   622,   623,   614,   619,     4,     4,     4,
     624,     3,     8,     4,   196,   194,   194,     4,   617,   193,
     193
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   197,   199,   198,   200,   198,   201,   198,   202,   198,
     203,   198,   204,   198,   205,   198,   206,   198,   207,   198,
     208,   198,   209,   198,   210,   198,   211,   198,   212,   198,
     213,   198,   214,   214,   214,   214,   214,   214,   214,   215,
     217,   216,   218,   219,   219,   220,   220,   222,   221,   223,
     223,   224,   224,   226,   225,   227,   227,   228,   228,   229,
     231,   230,   232,   232,   233,   233,   233,   233,   233,   233,
     235,   234,   237,   236,   238,   238,   239,   239,   239,   239,
     239,   239,   239,   239,   239,   239,   239,   239,   239,   239,
     239,   239,   239,   239,   239,   239,   239,   239,   239,   239,
     239,   239,   239,   239,   239,   239,   239,   239,   239,   239,
     239,   239,   239,   239,   239,   239,   239,   239,   239,   239,
     239,   239,   239,   239,   239,   239,   241,   240,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   258,   257,   259,   259,   259,   259,   259,
     261,   260,   263,   262,   265,   264,   267,   266,   268,   270,
     269,   272,   271,   274,   273,   275,   275,   276,   276,   276,
     276,   276,   278,   277,   279,   281,   280,   283,   282,   285,
     284,   286,   286,   287,   287,   289,   288,   290,   290,   291,
     291,   291,   291,   291,   291,   291,   291,   291,   291,   291,
     291,   291,   291,   291,   291,   291,   291,   291,   291,   291,
     293,   292,   294,   294,   294,   294,   296,   295,   298,   297,
     300,   299,   301,   303,   302,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   314,   313,   315,   317,   316,   319,
     318,   321,   320,   323,   322,   324,   324,   325,   327,   326,
     329,   328,   330,   330,   331,   331,   332,   333,   335,   334,
     336,   336,   337,   337,   337,   338,   339,   341,   340,   343,
     342,   344,   344,   345,   345,   347,   346,   349,   348,   350,
     350,   350,   351,   351,   353,   352,   355,   354,   357,   356,
     358,   358,   359,   359,   359,   359,   359,   359,   360,   361,
     362,   363,   364,   365,   367,   366,   368,   368,   369,   369,
     371,   370,   373,   372,   374,   374,   375,   375,   375,   375,
     375,   375,   375,   375,   375,   375,   375,   375,   375,   375,
     375,   375,   375,   375,   375,   375,   375,   375,   375,   375,
     375,   375,   375,   375,   375,   375,   375,   375,   375,   375,
     375,   375,   377,   376,   379,   378,   381,   380,   383,   382,
     385,   384,   387,   386,   388,   388,   388,   388,   389,   390,
     392,   391,   393,   393,   394,   394,   396,   395,   397,   397,
     398,   398,   398,   398,   398,   398,   398,   398,   398,   398,
     398,   398,   398,   398,   398,   398,   398,   398,   398,   398,
     398,   398,   398,   398,   398,   398,   398,   398,   398,   398,
     398,   398,   398,   400,   399,   402,   401,   403,   403,   404,
     404,   406,   405,   408,   407,   409,   409,   410,   410,   411,
     411,   411,   411,   411,   411,   411,   411,   411,   411,   412,
     413,   414,   416,   415,   418,   417,   420,   419,   421,   423,
     422,   424,   426,   425,   427,   427,   428,   428,   430,   429,
     432,   431,   433,   433,   434,   434,   435,   435,   435,   435,
     435,   435,   435,   435,   435,   436,   438,   437,   439,   440,
     441,   442,   444,   443,   445,   445,   446,   446,   448,   447,
     450,   449,   451,   451,   452,   452,   452,   452,   452,   452,
     452,   454,   453,   456,   455,   458,   457,   460,   459,   461,
     461,   462,   462,   464,   463,   466,   465,   467,   467,   468,
     468,   468,   468,   468,   468,   468,   468,   468,   468,   468,
     470,   469,   471,   473,   472,   474,   475,   477,   476,   478,
     478,   479,   479,   481,   480,   483,   482,   484,   484,   485,
     485,   486,   486,   486,   486,   486,   486,   486,   486,   486,
     486,   486,   488,   487,   490,   489,   492,   491,   494,   493,
     496,   495,   498,   497,   500,   499,   502,   501,   503,   503,
     505,   504,   507,   506,   508,   508,   510,   509,   511,   511,
     512,   512,   513,   513,   513,   513,   513,   513,   513,   514,
     516,   515,   517,   519,   518,   520,   520,   521,   521,   521,
     521,   521,   521,   521,   521,   521,   523,   522,   524,   524,
     524,   525,   527,   526,   528,   529,   530,   532,   531,   533,
     533,   534,   534,   534,   534,   534,   536,   535,   538,   537,
     540,   539,   541,   541,   542,   542,   542,   542,   542,   542,
     543,   545,   544,   546,   548,   547,   550,   549,   552,   551,
     553,   553,   554,   554,   554,   554,   554,   554,   554,   554,
     554,   554,   554,   554,   554,   554,   554,   554,   554,   554,
     555,   557,   556,   559,   558,   560,   562,   561,   563,   564,
     566,   565,   567,   567,   569,   568,   570,   571,   573,   572,
     575,   574,   577,   576,   579,   578,   581,   580,   583,   582,
     585,   584,   587,   586,   589,   588,   590,   590,   591,   591,
     593,   592,   594,   596,   595,   598,   597,   599,   599,   600,
     602,   601,   603,   603,   605,   604,   606,   606,   607,   607,
     607,   607,   607,   607,   607,   608,   610,   609,   612,   611,
     613,   613,   615,   614,   616,   616,   617,   617,   617,   617,
     617,   619,   618,   620,   621,   622,   624,   623
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
       1,     1,     1,     1,     1,     1,     0,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     0,     4,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     3,     0,
       4,     0,     6,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     3,     0,     6,     0,     6,     0,
       6,     0,     1,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     3,     0,     4,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     0,     6,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     1,     1,     1,     1,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     1,     3,
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
  "\"tcp-nodelay\"", "\"max-row-errors\"", "\"preferred-lifetime\"",
  "\"min-preferred-lifetime\"", "\"max-preferred-lifetime\"",
  "\"valid-lifetime\"", "\"min-valid-lifetime\"", "\"max-valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"calculate-tee-times\"",
  "\"t1-percent\"", "\"t2-percent\"", "\"decline-probation-period\"",
  "\"server-tag\"", "\"ddns-send-updates\"", "\"ddns-override-no-update\"",
  "\"ddns-override-client-update\"", "\"ddns-replace-client-name\"",
  "\"ddns-generated-prefix\"", "\"ddns-qualifying-suffix\"",
  "\"store-extended-info\"", "\"subnet6\"", "\"option-def\"",
  "\"option-data\"", "\"name\"", "\"data\"", "\"code\"", "\"space\"",
  "\"csv-format\"", "\"always-send\"", "\"record-types\"",
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
  "store_extended_info", "server_tag", "$@28", "interfaces_config", "$@29",
  "sub_interfaces6", "$@30", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@31", "re_detect",
  "lease_database", "$@32", "hosts_database", "$@33", "hosts_databases",
  "$@34", "database_list", "not_empty_database_list", "database", "$@35",
  "database_map_params", "database_map_param", "database_type", "$@36",
  "db_type", "user", "$@37", "password", "$@38", "host", "$@39", "port",
  "name", "$@40", "persist", "lfc_interval", "readonly", "connect_timeout",
  "reconnect_wait_time", "max_row_errors", "request_timeout",
  "tcp_keepalive", "tcp_nodelay", "contact_points", "$@41",
  "max_reconnect_tries", "keyspace", "$@42", "consistency", "$@43",
  "serial_consistency", "$@44", "sanity_checks", "$@45",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@46",
  "mac_sources", "$@47", "mac_sources_list", "mac_sources_value",
  "duid_id", "string_id", "host_reservation_identifiers", "$@48",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@49",
  "hooks_libraries", "$@50", "hooks_libraries_list",
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
  "$@62", "require_client_classes", "$@63", "reservation_mode", "$@64",
  "hr_mode", "id", "rapid_commit", "shared_networks", "$@65",
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
  "dhcp_ddns_param", "enable_updates", "qualifying_suffix", "$@116",
  "server_ip", "$@117", "server_port", "sender_ip", "$@118", "sender_port",
  "max_queue_size", "ncr_protocol", "$@119", "ncr_protocol_value",
  "ncr_format", "$@120", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@121",
  "dep_generated_prefix", "$@122", "dep_hostname_char_set", "$@123",
  "dep_hostname_char_replacement", "$@124", "dhcp4_json_object", "$@125",
  "dhcpddns_json_object", "$@126", "control_agent_json_object", "$@127",
  "config_control", "$@128", "sub_config_control", "$@129",
  "config_control_params", "config_control_param", "config_databases",
  "$@130", "config_fetch_wait_time", "logging_object", "$@131",
  "sub_logging", "$@132", "logging_params", "logging_param", "loggers",
  "$@133", "loggers_entries", "logger_entry", "$@134", "logger_params",
  "logger_param", "debuglevel", "severity", "$@135", "output_options_list",
  "$@136", "output_options_list_content", "output_entry", "$@137",
  "output_params_list", "output_params", "output", "$@138", "flush",
  "maxsize", "maxver", "pattern", "$@139", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const short
  Dhcp6Parser::yyrline_[] =
  {
       0,   281,   281,   281,   282,   282,   283,   283,   284,   284,
     285,   285,   286,   286,   287,   287,   288,   288,   289,   289,
     290,   290,   291,   291,   292,   292,   293,   293,   294,   294,
     295,   295,   303,   304,   305,   306,   307,   308,   309,   312,
     317,   317,   328,   331,   332,   335,   339,   346,   346,   353,
     354,   357,   361,   368,   368,   375,   376,   379,   383,   394,
     404,   404,   419,   420,   424,   425,   426,   427,   428,   429,
     432,   432,   447,   447,   456,   457,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   479,   480,   481,   482,   483,   484,   485,
     486,   487,   488,   489,   490,   491,   492,   493,   494,   495,
     496,   497,   498,   499,   500,   501,   502,   503,   504,   505,
     506,   507,   508,   509,   510,   511,   514,   514,   522,   527,
     532,   537,   542,   547,   552,   557,   562,   567,   572,   577,
     582,   587,   592,   597,   597,   605,   608,   611,   614,   617,
     623,   623,   631,   631,   639,   639,   647,   647,   655,   660,
     660,   668,   668,   679,   679,   688,   689,   692,   693,   694,
     695,   696,   699,   699,   709,   715,   715,   727,   727,   739,
     739,   749,   750,   753,   754,   757,   757,   767,   768,   771,
     772,   773,   774,   775,   776,   777,   778,   779,   780,   781,
     782,   783,   784,   785,   786,   787,   788,   789,   790,   791,
     794,   794,   801,   802,   803,   804,   807,   807,   815,   815,
     823,   823,   831,   836,   836,   844,   849,   854,   859,   864,
     869,   874,   879,   884,   889,   889,   897,   902,   902,   910,
     910,   918,   918,   926,   926,   936,   937,   939,   941,   941,
     959,   959,   969,   970,   973,   974,   977,   982,   987,   987,
     997,   998,  1001,  1002,  1003,  1006,  1011,  1018,  1018,  1028,
    1028,  1038,  1039,  1042,  1043,  1046,  1046,  1056,  1056,  1066,
    1067,  1068,  1071,  1072,  1075,  1075,  1083,  1083,  1091,  1091,
    1102,  1103,  1106,  1107,  1108,  1109,  1110,  1111,  1114,  1119,
    1124,  1129,  1134,  1139,  1147,  1147,  1160,  1161,  1164,  1165,
    1172,  1172,  1198,  1198,  1209,  1210,  1214,  1215,  1216,  1217,
    1218,  1219,  1220,  1221,  1222,  1223,  1224,  1225,  1226,  1227,
    1228,  1229,  1230,  1231,  1232,  1233,  1234,  1235,  1236,  1237,
    1238,  1239,  1240,  1241,  1242,  1243,  1244,  1245,  1246,  1247,
    1248,  1249,  1252,  1252,  1260,  1260,  1268,  1268,  1276,  1276,
    1284,  1284,  1294,  1294,  1301,  1302,  1303,  1304,  1307,  1312,
    1320,  1320,  1331,  1332,  1336,  1337,  1340,  1340,  1348,  1349,
    1352,  1353,  1354,  1355,  1356,  1357,  1358,  1359,  1360,  1361,
    1362,  1363,  1364,  1365,  1366,  1367,  1368,  1369,  1370,  1371,
    1372,  1373,  1374,  1375,  1376,  1377,  1378,  1379,  1380,  1381,
    1382,  1383,  1384,  1391,  1391,  1404,  1404,  1413,  1414,  1417,
    1418,  1423,  1423,  1438,  1438,  1452,  1453,  1456,  1457,  1460,
    1461,  1462,  1463,  1464,  1465,  1466,  1467,  1468,  1469,  1472,
    1474,  1479,  1481,  1481,  1489,  1489,  1497,  1497,  1505,  1507,
    1507,  1515,  1524,  1524,  1536,  1537,  1542,  1543,  1548,  1548,
    1560,  1560,  1572,  1573,  1578,  1579,  1584,  1585,  1586,  1587,
    1588,  1589,  1590,  1591,  1592,  1595,  1597,  1597,  1605,  1607,
    1609,  1614,  1622,  1622,  1634,  1635,  1638,  1639,  1642,  1642,
    1652,  1652,  1661,  1662,  1665,  1666,  1667,  1668,  1669,  1670,
    1671,  1674,  1674,  1682,  1682,  1707,  1707,  1737,  1737,  1749,
    1750,  1753,  1754,  1757,  1757,  1769,  1769,  1781,  1782,  1785,
    1786,  1787,  1788,  1789,  1790,  1791,  1792,  1793,  1794,  1795,
    1798,  1798,  1806,  1811,  1811,  1819,  1824,  1832,  1832,  1842,
    1843,  1846,  1847,  1850,  1850,  1859,  1859,  1868,  1869,  1872,
    1873,  1877,  1878,  1879,  1880,  1881,  1882,  1883,  1884,  1885,
    1886,  1887,  1890,  1890,  1900,  1900,  1910,  1910,  1918,  1918,
    1926,  1926,  1934,  1934,  1942,  1942,  1955,  1955,  1965,  1966,
    1969,  1969,  1980,  1980,  1990,  1991,  1994,  1994,  2004,  2005,
    2008,  2009,  2012,  2013,  2014,  2015,  2016,  2017,  2018,  2021,
    2023,  2023,  2031,  2039,  2039,  2051,  2052,  2055,  2056,  2057,
    2058,  2059,  2060,  2061,  2062,  2063,  2066,  2066,  2073,  2074,
    2075,  2078,  2083,  2083,  2091,  2096,  2103,  2110,  2110,  2120,
    2121,  2124,  2125,  2126,  2127,  2128,  2131,  2131,  2139,  2139,
    2149,  2149,  2161,  2162,  2165,  2166,  2167,  2168,  2169,  2170,
    2173,  2178,  2178,  2186,  2191,  2191,  2200,  2200,  2212,  2212,
    2222,  2223,  2226,  2227,  2228,  2229,  2230,  2231,  2232,  2233,
    2234,  2235,  2236,  2237,  2238,  2239,  2240,  2241,  2242,  2243,
    2246,  2251,  2251,  2259,  2259,  2267,  2272,  2272,  2280,  2285,
    2290,  2290,  2298,  2299,  2302,  2302,  2311,  2317,  2323,  2323,
    2331,  2331,  2340,  2340,  2349,  2349,  2359,  2359,  2366,  2366,
    2373,  2373,  2382,  2382,  2393,  2393,  2403,  2404,  2408,  2409,
    2412,  2412,  2422,  2432,  2432,  2442,  2442,  2453,  2454,  2458,
    2462,  2462,  2474,  2475,  2479,  2479,  2487,  2488,  2491,  2492,
    2493,  2494,  2495,  2496,  2497,  2500,  2505,  2505,  2513,  2513,
    2523,  2524,  2527,  2527,  2535,  2536,  2539,  2540,  2541,  2542,
    2543,  2546,  2546,  2554,  2559,  2564,  2569,  2569
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
#line 5560 "dhcp6_parser.cc"

#line 2577 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
