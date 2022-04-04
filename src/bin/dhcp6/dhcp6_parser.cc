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
      case 230: // value
      case 234: // map_value
      case 276: // ddns_replace_client_name_value
      case 322: // db_type
      case 339: // on_fail_mode
      case 426: // hr_mode
      case 562: // duid_type
      case 605: // ncr_protocol_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 213: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 212: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 211: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 210: // "constant string"
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
      case 230: // value
      case 234: // map_value
      case 276: // ddns_replace_client_name_value
      case 322: // db_type
      case 339: // on_fail_mode
      case 426: // hr_mode
      case 562: // duid_type
      case 605: // ncr_protocol_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 213: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 212: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 211: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 210: // "constant string"
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
      case 230: // value
      case 234: // map_value
      case 276: // ddns_replace_client_name_value
      case 322: // db_type
      case 339: // on_fail_mode
      case 426: // hr_mode
      case 562: // duid_type
      case 605: // ncr_protocol_value
        value.copy< ElementPtr > (that.value);
        break;

      case 213: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 212: // "floating point"
        value.copy< double > (that.value);
        break;

      case 211: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 210: // "constant string"
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
      case 230: // value
      case 234: // map_value
      case 276: // ddns_replace_client_name_value
      case 322: // db_type
      case 339: // on_fail_mode
      case 426: // hr_mode
      case 562: // duid_type
      case 605: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 213: // "boolean"
        value.move< bool > (that.value);
        break;

      case 212: // "floating point"
        value.move< double > (that.value);
        break;

      case 211: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 210: // "constant string"
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
      case 210: // "constant string"
#line 293 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 447 "dhcp6_parser.cc"
        break;

      case 211: // "integer"
#line 293 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 453 "dhcp6_parser.cc"
        break;

      case 212: // "floating point"
#line 293 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 459 "dhcp6_parser.cc"
        break;

      case 213: // "boolean"
#line 293 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 465 "dhcp6_parser.cc"
        break;

      case 230: // value
#line 293 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 471 "dhcp6_parser.cc"
        break;

      case 234: // map_value
#line 293 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 477 "dhcp6_parser.cc"
        break;

      case 276: // ddns_replace_client_name_value
#line 293 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 483 "dhcp6_parser.cc"
        break;

      case 322: // db_type
#line 293 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 489 "dhcp6_parser.cc"
        break;

      case 339: // on_fail_mode
#line 293 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 495 "dhcp6_parser.cc"
        break;

      case 426: // hr_mode
#line 293 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 501 "dhcp6_parser.cc"
        break;

      case 562: // duid_type
#line 293 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 507 "dhcp6_parser.cc"
        break;

      case 605: // ncr_protocol_value
#line 293 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 513 "dhcp6_parser.cc"
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
      case 230: // value
      case 234: // map_value
      case 276: // ddns_replace_client_name_value
      case 322: // db_type
      case 339: // on_fail_mode
      case 426: // hr_mode
      case 562: // duid_type
      case 605: // ncr_protocol_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 213: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 212: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 211: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 210: // "constant string"
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
#line 302 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 781 "dhcp6_parser.cc"
    break;

  case 4:
#line 303 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 787 "dhcp6_parser.cc"
    break;

  case 6:
#line 304 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 793 "dhcp6_parser.cc"
    break;

  case 8:
#line 305 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 799 "dhcp6_parser.cc"
    break;

  case 10:
#line 306 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 805 "dhcp6_parser.cc"
    break;

  case 12:
#line 307 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 811 "dhcp6_parser.cc"
    break;

  case 14:
#line 308 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 817 "dhcp6_parser.cc"
    break;

  case 16:
#line 309 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 823 "dhcp6_parser.cc"
    break;

  case 18:
#line 310 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 829 "dhcp6_parser.cc"
    break;

  case 20:
#line 311 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 835 "dhcp6_parser.cc"
    break;

  case 22:
#line 312 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 841 "dhcp6_parser.cc"
    break;

  case 24:
#line 313 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 847 "dhcp6_parser.cc"
    break;

  case 26:
#line 314 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 853 "dhcp6_parser.cc"
    break;

  case 28:
#line 315 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 859 "dhcp6_parser.cc"
    break;

  case 30:
#line 323 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 865 "dhcp6_parser.cc"
    break;

  case 31:
#line 324 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 871 "dhcp6_parser.cc"
    break;

  case 32:
#line 325 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 877 "dhcp6_parser.cc"
    break;

  case 33:
#line 326 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 883 "dhcp6_parser.cc"
    break;

  case 34:
#line 327 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 889 "dhcp6_parser.cc"
    break;

  case 35:
#line 328 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 895 "dhcp6_parser.cc"
    break;

  case 36:
#line 329 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 901 "dhcp6_parser.cc"
    break;

  case 37:
#line 332 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 910 "dhcp6_parser.cc"
    break;

  case 38:
#line 337 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 921 "dhcp6_parser.cc"
    break;

  case 39:
#line 342 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 931 "dhcp6_parser.cc"
    break;

  case 40:
#line 348 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 937 "dhcp6_parser.cc"
    break;

  case 43:
#line 355 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 947 "dhcp6_parser.cc"
    break;

  case 44:
#line 360 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 958 "dhcp6_parser.cc"
    break;

  case 45:
#line 366 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 966 "dhcp6_parser.cc"
    break;

  case 46:
#line 371 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 975 "dhcp6_parser.cc"
    break;

  case 47:
#line 374 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 983 "dhcp6_parser.cc"
    break;

  case 50:
#line 382 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 992 "dhcp6_parser.cc"
    break;

  case 51:
#line 386 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 1001 "dhcp6_parser.cc"
    break;

  case 52:
#line 390 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 1009 "dhcp6_parser.cc"
    break;

  case 53:
#line 396 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 1017 "dhcp6_parser.cc"
    break;

  case 54:
#line 398 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1026 "dhcp6_parser.cc"
    break;

  case 57:
#line 407 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1035 "dhcp6_parser.cc"
    break;

  case 58:
#line 411 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1044 "dhcp6_parser.cc"
    break;

  case 59:
#line 415 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1052 "dhcp6_parser.cc"
    break;

  case 60:
#line 425 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1063 "dhcp6_parser.cc"
    break;

  case 61:
#line 434 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1074 "dhcp6_parser.cc"
    break;

  case 62:
#line 439 "dhcp6_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1087 "dhcp6_parser.cc"
    break;

  case 63:
#line 449 "dhcp6_parser.yy"
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
#line 1102 "dhcp6_parser.cc"
    break;

  case 64:
#line 458 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1112 "dhcp6_parser.cc"
    break;

  case 66:
#line 466 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1120 "dhcp6_parser.cc"
    break;

  case 67:
#line 472 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1130 "dhcp6_parser.cc"
    break;

  case 68:
#line 476 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1139 "dhcp6_parser.cc"
    break;

  case 71:
#line 483 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1147 "dhcp6_parser.cc"
    break;

  case 137:
#line 557 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1156 "dhcp6_parser.cc"
    break;

  case 138:
#line 560 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1166 "dhcp6_parser.cc"
    break;

  case 139:
#line 566 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1176 "dhcp6_parser.cc"
    break;

  case 140:
#line 572 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1186 "dhcp6_parser.cc"
    break;

  case 141:
#line 578 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1196 "dhcp6_parser.cc"
    break;

  case 142:
#line 584 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1206 "dhcp6_parser.cc"
    break;

  case 143:
#line 590 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1216 "dhcp6_parser.cc"
    break;

  case 144:
#line 596 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1226 "dhcp6_parser.cc"
    break;

  case 145:
#line 602 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1236 "dhcp6_parser.cc"
    break;

  case 146:
#line 608 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1246 "dhcp6_parser.cc"
    break;

  case 147:
#line 614 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1256 "dhcp6_parser.cc"
    break;

  case 148:
#line 620 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1266 "dhcp6_parser.cc"
    break;

  case 149:
#line 626 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1276 "dhcp6_parser.cc"
    break;

  case 150:
#line 632 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1286 "dhcp6_parser.cc"
    break;

  case 151:
#line 638 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1296 "dhcp6_parser.cc"
    break;

  case 152:
#line 644 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1306 "dhcp6_parser.cc"
    break;

  case 153:
#line 650 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1316 "dhcp6_parser.cc"
    break;

  case 154:
#line 656 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1326 "dhcp6_parser.cc"
    break;

  case 155:
#line 662 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1336 "dhcp6_parser.cc"
    break;

  case 156:
#line 668 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1345 "dhcp6_parser.cc"
    break;

  case 157:
#line 671 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1354 "dhcp6_parser.cc"
    break;

  case 158:
#line 677 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1362 "dhcp6_parser.cc"
    break;

  case 159:
#line 680 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1370 "dhcp6_parser.cc"
    break;

  case 160:
#line 683 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1378 "dhcp6_parser.cc"
    break;

  case 161:
#line 686 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1386 "dhcp6_parser.cc"
    break;

  case 162:
#line 689 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1395 "dhcp6_parser.cc"
    break;

  case 163:
#line 695 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1404 "dhcp6_parser.cc"
    break;

  case 164:
#line 698 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1414 "dhcp6_parser.cc"
    break;

  case 165:
#line 704 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1423 "dhcp6_parser.cc"
    break;

  case 166:
#line 707 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1433 "dhcp6_parser.cc"
    break;

  case 167:
#line 713 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1443 "dhcp6_parser.cc"
    break;

  case 168:
#line 719 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1453 "dhcp6_parser.cc"
    break;

  case 169:
#line 725 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1462 "dhcp6_parser.cc"
    break;

  case 170:
#line 728 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1472 "dhcp6_parser.cc"
    break;

  case 171:
#line 734 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1481 "dhcp6_parser.cc"
    break;

  case 172:
#line 737 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1491 "dhcp6_parser.cc"
    break;

  case 173:
#line 743 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1501 "dhcp6_parser.cc"
    break;

  case 174:
#line 749 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1511 "dhcp6_parser.cc"
    break;

  case 175:
#line 755 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1521 "dhcp6_parser.cc"
    break;

  case 176:
#line 761 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1530 "dhcp6_parser.cc"
    break;

  case 177:
#line 764 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1540 "dhcp6_parser.cc"
    break;

  case 178:
#line 770 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1550 "dhcp6_parser.cc"
    break;

  case 179:
#line 776 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1560 "dhcp6_parser.cc"
    break;

  case 180:
#line 782 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1570 "dhcp6_parser.cc"
    break;

  case 181:
#line 788 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1580 "dhcp6_parser.cc"
    break;

  case 182:
#line 794 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1592 "dhcp6_parser.cc"
    break;

  case 183:
#line 800 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1602 "dhcp6_parser.cc"
    break;

  case 184:
#line 806 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1612 "dhcp6_parser.cc"
    break;

  case 185:
#line 810 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1621 "dhcp6_parser.cc"
    break;

  case 188:
#line 817 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1629 "dhcp6_parser.cc"
    break;

  case 197:
#line 832 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1641 "dhcp6_parser.cc"
    break;

  case 198:
#line 838 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1650 "dhcp6_parser.cc"
    break;

  case 199:
#line 843 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1660 "dhcp6_parser.cc"
    break;

  case 200:
#line 849 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1670 "dhcp6_parser.cc"
    break;

  case 201:
#line 855 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1680 "dhcp6_parser.cc"
    break;

  case 202:
#line 861 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1690 "dhcp6_parser.cc"
    break;

  case 203:
#line 867 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1702 "dhcp6_parser.cc"
    break;

  case 204:
#line 873 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1713 "dhcp6_parser.cc"
    break;

  case 205:
#line 880 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1725 "dhcp6_parser.cc"
    break;

  case 206:
#line 886 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1736 "dhcp6_parser.cc"
    break;

  case 207:
#line 893 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1748 "dhcp6_parser.cc"
    break;

  case 208:
#line 899 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1757 "dhcp6_parser.cc"
    break;

  case 213:
#line 910 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1765 "dhcp6_parser.cc"
    break;

  case 214:
#line 915 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1775 "dhcp6_parser.cc"
    break;

  case 215:
#line 919 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1785 "dhcp6_parser.cc"
    break;

  case 218:
#line 927 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1793 "dhcp6_parser.cc"
    break;

  case 238:
#line 953 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1802 "dhcp6_parser.cc"
    break;

  case 239:
#line 956 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1811 "dhcp6_parser.cc"
    break;

  case 240:
#line 961 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1817 "dhcp6_parser.cc"
    break;

  case 241:
#line 962 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1823 "dhcp6_parser.cc"
    break;

  case 242:
#line 963 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1829 "dhcp6_parser.cc"
    break;

  case 243:
#line 966 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1838 "dhcp6_parser.cc"
    break;

  case 244:
#line 969 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1848 "dhcp6_parser.cc"
    break;

  case 245:
#line 975 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1857 "dhcp6_parser.cc"
    break;

  case 246:
#line 978 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1867 "dhcp6_parser.cc"
    break;

  case 247:
#line 984 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1876 "dhcp6_parser.cc"
    break;

  case 248:
#line 987 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1886 "dhcp6_parser.cc"
    break;

  case 249:
#line 993 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1896 "dhcp6_parser.cc"
    break;

  case 250:
#line 999 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1905 "dhcp6_parser.cc"
    break;

  case 251:
#line 1002 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1915 "dhcp6_parser.cc"
    break;

  case 252:
#line 1008 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1925 "dhcp6_parser.cc"
    break;

  case 253:
#line 1014 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1935 "dhcp6_parser.cc"
    break;

  case 254:
#line 1020 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1945 "dhcp6_parser.cc"
    break;

  case 255:
#line 1026 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1955 "dhcp6_parser.cc"
    break;

  case 256:
#line 1032 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1965 "dhcp6_parser.cc"
    break;

  case 257:
#line 1038 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 1974 "dhcp6_parser.cc"
    break;

  case 258:
#line 1041 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1983 "dhcp6_parser.cc"
    break;

  case 259:
#line 1046 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 1989 "dhcp6_parser.cc"
    break;

  case 260:
#line 1047 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 1995 "dhcp6_parser.cc"
    break;

  case 261:
#line 1048 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2001 "dhcp6_parser.cc"
    break;

  case 262:
#line 1051 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2011 "dhcp6_parser.cc"
    break;

  case 263:
#line 1057 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2021 "dhcp6_parser.cc"
    break;

  case 264:
#line 1063 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2030 "dhcp6_parser.cc"
    break;

  case 265:
#line 1066 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2040 "dhcp6_parser.cc"
    break;

  case 266:
#line 1072 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2049 "dhcp6_parser.cc"
    break;

  case 267:
#line 1075 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2059 "dhcp6_parser.cc"
    break;

  case 268:
#line 1081 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2068 "dhcp6_parser.cc"
    break;

  case 269:
#line 1084 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2078 "dhcp6_parser.cc"
    break;

  case 270:
#line 1090 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2087 "dhcp6_parser.cc"
    break;

  case 271:
#line 1093 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2097 "dhcp6_parser.cc"
    break;

  case 272:
#line 1099 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2109 "dhcp6_parser.cc"
    break;

  case 273:
#line 1105 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2118 "dhcp6_parser.cc"
    break;

  case 276:
#line 1112 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2126 "dhcp6_parser.cc"
    break;

  case 278:
#line 1119 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2135 "dhcp6_parser.cc"
    break;

  case 279:
#line 1122 "dhcp6_parser.yy"
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
#line 2155 "dhcp6_parser.cc"
    break;

  case 280:
#line 1138 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2167 "dhcp6_parser.cc"
    break;

  case 281:
#line 1144 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2176 "dhcp6_parser.cc"
    break;

  case 284:
#line 1151 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2184 "dhcp6_parser.cc"
    break;

  case 287:
#line 1160 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2193 "dhcp6_parser.cc"
    break;

  case 288:
#line 1165 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2202 "dhcp6_parser.cc"
    break;

  case 289:
#line 1170 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2214 "dhcp6_parser.cc"
    break;

  case 290:
#line 1176 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2223 "dhcp6_parser.cc"
    break;

  case 293:
#line 1183 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2231 "dhcp6_parser.cc"
    break;

  case 297:
#line 1193 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2240 "dhcp6_parser.cc"
    break;

  case 298:
#line 1198 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2249 "dhcp6_parser.cc"
    break;

  case 299:
#line 1205 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2261 "dhcp6_parser.cc"
    break;

  case 300:
#line 1211 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2270 "dhcp6_parser.cc"
    break;

  case 301:
#line 1218 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2282 "dhcp6_parser.cc"
    break;

  case 302:
#line 1224 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2293 "dhcp6_parser.cc"
    break;

  case 305:
#line 1233 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2301 "dhcp6_parser.cc"
    break;

  case 312:
#line 1246 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2311 "dhcp6_parser.cc"
    break;

  case 313:
#line 1252 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2321 "dhcp6_parser.cc"
    break;

  case 314:
#line 1258 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2331 "dhcp6_parser.cc"
    break;

  case 315:
#line 1264 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2343 "dhcp6_parser.cc"
    break;

  case 316:
#line 1270 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2352 "dhcp6_parser.cc"
    break;

  case 321:
#line 1281 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2360 "dhcp6_parser.cc"
    break;

  case 322:
#line 1286 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2370 "dhcp6_parser.cc"
    break;

  case 323:
#line 1290 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2380 "dhcp6_parser.cc"
    break;

  case 324:
#line 1296 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2390 "dhcp6_parser.cc"
    break;

  case 325:
#line 1300 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2400 "dhcp6_parser.cc"
    break;

  case 328:
#line 1308 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2408 "dhcp6_parser.cc"
    break;

  case 332:
#line 1318 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2417 "dhcp6_parser.cc"
    break;

  case 333:
#line 1321 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2427 "dhcp6_parser.cc"
    break;

  case 334:
#line 1327 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2436 "dhcp6_parser.cc"
    break;

  case 335:
#line 1330 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2445 "dhcp6_parser.cc"
    break;

  case 336:
#line 1336 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2457 "dhcp6_parser.cc"
    break;

  case 337:
#line 1342 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2467 "dhcp6_parser.cc"
    break;

  case 340:
#line 1350 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2475 "dhcp6_parser.cc"
    break;

  case 347:
#line 1363 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2485 "dhcp6_parser.cc"
    break;

  case 348:
#line 1369 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2495 "dhcp6_parser.cc"
    break;

  case 349:
#line 1375 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2505 "dhcp6_parser.cc"
    break;

  case 350:
#line 1381 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2515 "dhcp6_parser.cc"
    break;

  case 351:
#line 1387 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2525 "dhcp6_parser.cc"
    break;

  case 352:
#line 1393 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2535 "dhcp6_parser.cc"
    break;

  case 353:
#line 1402 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2547 "dhcp6_parser.cc"
    break;

  case 354:
#line 1408 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2556 "dhcp6_parser.cc"
    break;

  case 359:
#line 1422 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2564 "dhcp6_parser.cc"
    break;

  case 360:
#line 1431 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2574 "dhcp6_parser.cc"
    break;

  case 361:
#line 1435 "dhcp6_parser.yy"
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
#line 2600 "dhcp6_parser.cc"
    break;

  case 362:
#line 1457 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2610 "dhcp6_parser.cc"
    break;

  case 363:
#line 1461 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2620 "dhcp6_parser.cc"
    break;

  case 366:
#line 1470 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2628 "dhcp6_parser.cc"
    break;

  case 410:
#line 1521 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2637 "dhcp6_parser.cc"
    break;

  case 411:
#line 1524 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2647 "dhcp6_parser.cc"
    break;

  case 412:
#line 1530 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2656 "dhcp6_parser.cc"
    break;

  case 413:
#line 1533 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2666 "dhcp6_parser.cc"
    break;

  case 414:
#line 1539 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2675 "dhcp6_parser.cc"
    break;

  case 415:
#line 1542 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2685 "dhcp6_parser.cc"
    break;

  case 416:
#line 1548 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2694 "dhcp6_parser.cc"
    break;

  case 417:
#line 1551 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2704 "dhcp6_parser.cc"
    break;

  case 418:
#line 1557 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2716 "dhcp6_parser.cc"
    break;

  case 419:
#line 1563 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2725 "dhcp6_parser.cc"
    break;

  case 420:
#line 1568 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2735 "dhcp6_parser.cc"
    break;

  case 421:
#line 1574 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2745 "dhcp6_parser.cc"
    break;

  case 422:
#line 1580 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2755 "dhcp6_parser.cc"
    break;

  case 423:
#line 1586 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2764 "dhcp6_parser.cc"
    break;

  case 424:
#line 1589 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2773 "dhcp6_parser.cc"
    break;

  case 425:
#line 1594 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2779 "dhcp6_parser.cc"
    break;

  case 426:
#line 1595 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2785 "dhcp6_parser.cc"
    break;

  case 427:
#line 1596 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2791 "dhcp6_parser.cc"
    break;

  case 428:
#line 1597 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2797 "dhcp6_parser.cc"
    break;

  case 429:
#line 1600 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2807 "dhcp6_parser.cc"
    break;

  case 430:
#line 1606 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2817 "dhcp6_parser.cc"
    break;

  case 431:
#line 1614 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2829 "dhcp6_parser.cc"
    break;

  case 432:
#line 1620 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2838 "dhcp6_parser.cc"
    break;

  case 437:
#line 1633 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2846 "dhcp6_parser.cc"
    break;

  case 438:
#line 1638 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2856 "dhcp6_parser.cc"
    break;

  case 439:
#line 1642 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2864 "dhcp6_parser.cc"
    break;

  case 442:
#line 1648 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2872 "dhcp6_parser.cc"
    break;

  case 483:
#line 1699 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2884 "dhcp6_parser.cc"
    break;

  case 484:
#line 1705 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2893 "dhcp6_parser.cc"
    break;

  case 485:
#line 1713 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2902 "dhcp6_parser.cc"
    break;

  case 486:
#line 1716 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2910 "dhcp6_parser.cc"
    break;

  case 491:
#line 1728 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 2918 "dhcp6_parser.cc"
    break;

  case 492:
#line 1735 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2928 "dhcp6_parser.cc"
    break;

  case 493:
#line 1739 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2940 "dhcp6_parser.cc"
    break;

  case 494:
#line 1750 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2950 "dhcp6_parser.cc"
    break;

  case 495:
#line 1754 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2962 "dhcp6_parser.cc"
    break;

  case 500:
#line 1770 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 2970 "dhcp6_parser.cc"
    break;

  case 512:
#line 1789 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2980 "dhcp6_parser.cc"
    break;

  case 514:
#line 1797 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2989 "dhcp6_parser.cc"
    break;

  case 515:
#line 1800 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2999 "dhcp6_parser.cc"
    break;

  case 516:
#line 1806 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3008 "dhcp6_parser.cc"
    break;

  case 517:
#line 1809 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3018 "dhcp6_parser.cc"
    break;

  case 518:
#line 1815 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3027 "dhcp6_parser.cc"
    break;

  case 519:
#line 1818 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3037 "dhcp6_parser.cc"
    break;

  case 521:
#line 1826 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3046 "dhcp6_parser.cc"
    break;

  case 522:
#line 1829 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3056 "dhcp6_parser.cc"
    break;

  case 523:
#line 1835 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3066 "dhcp6_parser.cc"
    break;

  case 524:
#line 1845 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3078 "dhcp6_parser.cc"
    break;

  case 525:
#line 1851 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3087 "dhcp6_parser.cc"
    break;

  case 530:
#line 1866 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3095 "dhcp6_parser.cc"
    break;

  case 531:
#line 1873 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3105 "dhcp6_parser.cc"
    break;

  case 532:
#line 1877 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3114 "dhcp6_parser.cc"
    break;

  case 533:
#line 1885 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3124 "dhcp6_parser.cc"
    break;

  case 534:
#line 1889 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3133 "dhcp6_parser.cc"
    break;

  case 539:
#line 1905 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3141 "dhcp6_parser.cc"
    break;

  case 550:
#line 1925 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3150 "dhcp6_parser.cc"
    break;

  case 551:
#line 1928 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3160 "dhcp6_parser.cc"
    break;

  case 554:
#line 1938 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 3170 "dhcp6_parser.cc"
    break;

  case 555:
#line 1944 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3180 "dhcp6_parser.cc"
    break;

  case 556:
#line 1953 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3192 "dhcp6_parser.cc"
    break;

  case 557:
#line 1959 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3201 "dhcp6_parser.cc"
    break;

  case 562:
#line 1972 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3209 "dhcp6_parser.cc"
    break;

  case 563:
#line 1977 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3219 "dhcp6_parser.cc"
    break;

  case 564:
#line 1981 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3229 "dhcp6_parser.cc"
    break;

  case 565:
#line 1987 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3239 "dhcp6_parser.cc"
    break;

  case 566:
#line 1991 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3249 "dhcp6_parser.cc"
    break;

  case 569:
#line 1999 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3257 "dhcp6_parser.cc"
    break;

  case 577:
#line 2013 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3266 "dhcp6_parser.cc"
    break;

  case 578:
#line 2016 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3276 "dhcp6_parser.cc"
    break;

  case 579:
#line 2022 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3284 "dhcp6_parser.cc"
    break;

  case 580:
#line 2024 "dhcp6_parser.yy"
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
#line 3311 "dhcp6_parser.cc"
    break;

  case 581:
#line 2047 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3319 "dhcp6_parser.cc"
    break;

  case 582:
#line 2049 "dhcp6_parser.yy"
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
#line 3348 "dhcp6_parser.cc"
    break;

  case 583:
#line 2077 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3360 "dhcp6_parser.cc"
    break;

  case 584:
#line 2083 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3369 "dhcp6_parser.cc"
    break;

  case 589:
#line 2096 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3377 "dhcp6_parser.cc"
    break;

  case 590:
#line 2101 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3387 "dhcp6_parser.cc"
    break;

  case 591:
#line 2105 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3399 "dhcp6_parser.cc"
    break;

  case 592:
#line 2113 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3409 "dhcp6_parser.cc"
    break;

  case 593:
#line 2117 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3421 "dhcp6_parser.cc"
    break;

  case 596:
#line 2127 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3429 "dhcp6_parser.cc"
    break;

  case 608:
#line 2145 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3438 "dhcp6_parser.cc"
    break;

  case 609:
#line 2148 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3448 "dhcp6_parser.cc"
    break;

  case 610:
#line 2154 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3458 "dhcp6_parser.cc"
    break;

  case 611:
#line 2160 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3467 "dhcp6_parser.cc"
    break;

  case 612:
#line 2163 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3477 "dhcp6_parser.cc"
    break;

  case 613:
#line 2169 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3487 "dhcp6_parser.cc"
    break;

  case 614:
#line 2175 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3497 "dhcp6_parser.cc"
    break;

  case 615:
#line 2184 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3509 "dhcp6_parser.cc"
    break;

  case 616:
#line 2190 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3518 "dhcp6_parser.cc"
    break;

  case 621:
#line 2201 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3526 "dhcp6_parser.cc"
    break;

  case 622:
#line 2206 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3536 "dhcp6_parser.cc"
    break;

  case 623:
#line 2210 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3545 "dhcp6_parser.cc"
    break;

  case 624:
#line 2215 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3555 "dhcp6_parser.cc"
    break;

  case 625:
#line 2219 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3564 "dhcp6_parser.cc"
    break;

  case 630:
#line 2230 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3572 "dhcp6_parser.cc"
    break;

  case 642:
#line 2249 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3584 "dhcp6_parser.cc"
    break;

  case 643:
#line 2255 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3593 "dhcp6_parser.cc"
    break;

  case 644:
#line 2260 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3605 "dhcp6_parser.cc"
    break;

  case 645:
#line 2266 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3614 "dhcp6_parser.cc"
    break;

  case 646:
#line 2271 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3623 "dhcp6_parser.cc"
    break;

  case 647:
#line 2274 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3633 "dhcp6_parser.cc"
    break;

  case 648:
#line 2280 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3642 "dhcp6_parser.cc"
    break;

  case 649:
#line 2283 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3652 "dhcp6_parser.cc"
    break;

  case 650:
#line 2289 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3661 "dhcp6_parser.cc"
    break;

  case 651:
#line 2292 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3671 "dhcp6_parser.cc"
    break;

  case 652:
#line 2298 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3680 "dhcp6_parser.cc"
    break;

  case 653:
#line 2301 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3690 "dhcp6_parser.cc"
    break;

  case 654:
#line 2307 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3702 "dhcp6_parser.cc"
    break;

  case 655:
#line 2313 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3711 "dhcp6_parser.cc"
    break;

  case 656:
#line 2321 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3723 "dhcp6_parser.cc"
    break;

  case 657:
#line 2327 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3732 "dhcp6_parser.cc"
    break;

  case 660:
#line 2336 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3741 "dhcp6_parser.cc"
    break;

  case 661:
#line 2339 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3751 "dhcp6_parser.cc"
    break;

  case 662:
#line 2348 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3763 "dhcp6_parser.cc"
    break;

  case 663:
#line 2354 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3772 "dhcp6_parser.cc"
    break;

  case 666:
#line 2361 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3780 "dhcp6_parser.cc"
    break;

  case 667:
#line 2366 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3790 "dhcp6_parser.cc"
    break;

  case 668:
#line 2370 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3800 "dhcp6_parser.cc"
    break;

  case 673:
#line 2382 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3808 "dhcp6_parser.cc"
    break;

  case 688:
#line 2404 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3817 "dhcp6_parser.cc"
    break;

  case 689:
#line 2407 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3827 "dhcp6_parser.cc"
    break;

  case 690:
#line 2413 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3837 "dhcp6_parser.cc"
    break;

  case 691:
#line 2422 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3849 "dhcp6_parser.cc"
    break;

  case 692:
#line 2428 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3860 "dhcp6_parser.cc"
    break;

  case 695:
#line 2437 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 3868 "dhcp6_parser.cc"
    break;

  case 705:
#line 2453 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3877 "dhcp6_parser.cc"
    break;

  case 706:
#line 2456 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3886 "dhcp6_parser.cc"
    break;

  case 707:
#line 2461 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3892 "dhcp6_parser.cc"
    break;

  case 708:
#line 2462 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3898 "dhcp6_parser.cc"
    break;

  case 709:
#line 2463 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3904 "dhcp6_parser.cc"
    break;

  case 710:
#line 2466 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3914 "dhcp6_parser.cc"
    break;

  case 711:
#line 2472 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3923 "dhcp6_parser.cc"
    break;

  case 712:
#line 2475 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3933 "dhcp6_parser.cc"
    break;

  case 713:
#line 2481 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3943 "dhcp6_parser.cc"
    break;

  case 714:
#line 2487 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3953 "dhcp6_parser.cc"
    break;

  case 715:
#line 2495 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3963 "dhcp6_parser.cc"
    break;

  case 716:
#line 2503 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3975 "dhcp6_parser.cc"
    break;

  case 717:
#line 2509 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3984 "dhcp6_parser.cc"
    break;

  case 720:
#line 2516 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3992 "dhcp6_parser.cc"
    break;

  case 726:
#line 2528 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4001 "dhcp6_parser.cc"
    break;

  case 727:
#line 2531 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 4011 "dhcp6_parser.cc"
    break;

  case 728:
#line 2537 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4020 "dhcp6_parser.cc"
    break;

  case 729:
#line 2540 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4030 "dhcp6_parser.cc"
    break;

  case 730:
#line 2549 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4042 "dhcp6_parser.cc"
    break;

  case 731:
#line 2555 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4053 "dhcp6_parser.cc"
    break;

  case 734:
#line 2564 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4061 "dhcp6_parser.cc"
    break;

  case 741:
#line 2577 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4071 "dhcp6_parser.cc"
    break;

  case 742:
#line 2583 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4080 "dhcp6_parser.cc"
    break;

  case 743:
#line 2586 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4090 "dhcp6_parser.cc"
    break;

  case 744:
#line 2592 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4100 "dhcp6_parser.cc"
    break;

  case 745:
#line 2598 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4109 "dhcp6_parser.cc"
    break;

  case 746:
#line 2601 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4118 "dhcp6_parser.cc"
    break;

  case 747:
#line 2608 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4130 "dhcp6_parser.cc"
    break;

  case 748:
#line 2614 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4141 "dhcp6_parser.cc"
    break;

  case 749:
#line 2621 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4151 "dhcp6_parser.cc"
    break;

  case 750:
#line 2625 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4161 "dhcp6_parser.cc"
    break;

  case 753:
#line 2633 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4169 "dhcp6_parser.cc"
    break;

  case 772:
#line 2658 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4179 "dhcp6_parser.cc"
    break;

  case 773:
#line 2665 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4188 "dhcp6_parser.cc"
    break;

  case 774:
#line 2668 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4198 "dhcp6_parser.cc"
    break;

  case 775:
#line 2674 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4207 "dhcp6_parser.cc"
    break;

  case 776:
#line 2677 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4217 "dhcp6_parser.cc"
    break;

  case 777:
#line 2683 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4227 "dhcp6_parser.cc"
    break;

  case 778:
#line 2689 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4236 "dhcp6_parser.cc"
    break;

  case 779:
#line 2692 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4246 "dhcp6_parser.cc"
    break;

  case 780:
#line 2698 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4256 "dhcp6_parser.cc"
    break;

  case 781:
#line 2704 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4266 "dhcp6_parser.cc"
    break;

  case 782:
#line 2710 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4275 "dhcp6_parser.cc"
    break;

  case 783:
#line 2713 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4284 "dhcp6_parser.cc"
    break;

  case 784:
#line 2719 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4290 "dhcp6_parser.cc"
    break;

  case 785:
#line 2720 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4296 "dhcp6_parser.cc"
    break;

  case 786:
#line 2723 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4305 "dhcp6_parser.cc"
    break;

  case 787:
#line 2726 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4315 "dhcp6_parser.cc"
    break;

  case 788:
#line 2733 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4325 "dhcp6_parser.cc"
    break;

  case 789:
#line 2740 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4335 "dhcp6_parser.cc"
    break;

  case 790:
#line 2747 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4344 "dhcp6_parser.cc"
    break;

  case 791:
#line 2750 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4353 "dhcp6_parser.cc"
    break;

  case 792:
#line 2756 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4362 "dhcp6_parser.cc"
    break;

  case 793:
#line 2759 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4372 "dhcp6_parser.cc"
    break;

  case 794:
#line 2766 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4381 "dhcp6_parser.cc"
    break;

  case 795:
#line 2769 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4391 "dhcp6_parser.cc"
    break;

  case 796:
#line 2776 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4400 "dhcp6_parser.cc"
    break;

  case 797:
#line 2779 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4410 "dhcp6_parser.cc"
    break;

  case 798:
#line 2788 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4422 "dhcp6_parser.cc"
    break;

  case 799:
#line 2794 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4432 "dhcp6_parser.cc"
    break;

  case 800:
#line 2800 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4442 "dhcp6_parser.cc"
    break;

  case 801:
#line 2804 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4451 "dhcp6_parser.cc"
    break;

  case 804:
#line 2812 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4459 "dhcp6_parser.cc"
    break;

  case 807:
#line 2822 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4471 "dhcp6_parser.cc"
    break;

  case 808:
#line 2828 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4480 "dhcp6_parser.cc"
    break;

  case 809:
#line 2833 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4490 "dhcp6_parser.cc"
    break;

  case 810:
#line 2841 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4502 "dhcp6_parser.cc"
    break;

  case 811:
#line 2847 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4511 "dhcp6_parser.cc"
    break;

  case 814:
#line 2856 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4519 "dhcp6_parser.cc"
    break;

  case 815:
#line 2862 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4529 "dhcp6_parser.cc"
    break;

  case 816:
#line 2866 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4537 "dhcp6_parser.cc"
    break;

  case 819:
#line 2872 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4545 "dhcp6_parser.cc"
    break;

  case 827:
#line 2886 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4555 "dhcp6_parser.cc"
    break;

  case 828:
#line 2892 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4564 "dhcp6_parser.cc"
    break;

  case 829:
#line 2895 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4574 "dhcp6_parser.cc"
    break;

  case 830:
#line 2901 "dhcp6_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4586 "dhcp6_parser.cc"
    break;

  case 831:
#line 2907 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4595 "dhcp6_parser.cc"
    break;

  case 834:
#line 2914 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4603 "dhcp6_parser.cc"
    break;

  case 835:
#line 2919 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4613 "dhcp6_parser.cc"
    break;

  case 836:
#line 2923 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4621 "dhcp6_parser.cc"
    break;

  case 839:
#line 2929 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4629 "dhcp6_parser.cc"
    break;

  case 845:
#line 2941 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4638 "dhcp6_parser.cc"
    break;

  case 846:
#line 2944 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4648 "dhcp6_parser.cc"
    break;

  case 847:
#line 2950 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4658 "dhcp6_parser.cc"
    break;

  case 848:
#line 2956 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4668 "dhcp6_parser.cc"
    break;

  case 849:
#line 2962 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4678 "dhcp6_parser.cc"
    break;

  case 850:
#line 2968 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4687 "dhcp6_parser.cc"
    break;

  case 851:
#line 2971 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4697 "dhcp6_parser.cc"
    break;

  case 852:
#line 2977 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4709 "dhcp6_parser.cc"
    break;

  case 853:
#line 2983 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4718 "dhcp6_parser.cc"
    break;

  case 856:
#line 2990 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4726 "dhcp6_parser.cc"
    break;

  case 859:
#line 2999 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4736 "dhcp6_parser.cc"
    break;


#line 4740 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -996;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     437,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,    36,    30,    93,    94,   106,
     108,   137,   155,   171,   173,   180,   182,   192,   193,   199,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,    30,  -166,
     130,   160,    78,   668,    42,   296,    71,    -2,    81,   -25,
     -90,   451,    35,  -996,   244,   248,   260,   257,   297,  -996,
      65,  -996,  -996,  -996,  -996,  -996,  -996,  -996,   306,   328,
     329,   335,   349,   359,   362,   369,   370,   377,   379,   389,
     397,   398,  -996,   399,   416,   434,   436,   439,  -996,  -996,
    -996,   440,   441,   442,  -996,  -996,  -996,   443,  -996,  -996,
    -996,  -996,   444,   445,   446,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,   447,  -996,  -996,  -996,  -996,  -996,
    -996,   448,   449,   452,  -996,  -996,   455,  -996,    96,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,   456,   457,   459,   463,  -996,
     100,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,   464,   465,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,   113,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,   123,
    -996,  -996,  -996,  -996,  -996,   467,  -996,   468,   471,  -996,
    -996,  -996,  -996,  -996,  -996,   133,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,   323,   438,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,   357,  -996,  -996,   472,  -996,  -996,  -996,
     473,  -996,  -996,   470,   476,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,   477,   479,
    -996,  -996,  -996,  -996,   478,   482,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,   176,  -996,
    -996,  -996,   483,  -996,  -996,   484,  -996,   487,   488,  -996,
    -996,   499,   500,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
     236,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,   503,   246,
    -996,  -996,  -996,  -996,    30,    30,  -996,   245,   504,  -996,
    -996,   508,   510,   513,   514,   516,   517,   315,   316,   317,
     319,   320,   324,   325,   331,   321,   312,   326,   338,   340,
     341,   518,   342,   344,   348,   351,   352,   536,   550,   552,
     354,   356,   358,   553,   556,   566,   365,   568,   569,   571,
     574,   373,   375,   376,   578,   579,   581,   586,   588,   589,
     592,   594,   595,   393,   596,   598,   601,   602,   603,   605,
     412,   415,   417,   620,   622,  -996,   160,  -996,   623,   435,
     450,   418,   453,    78,  -996,   643,   645,   646,   647,   649,
     454,   460,   650,   652,   653,   668,  -996,   654,    42,  -996,
     655,   458,   656,   461,   466,   296,  -996,   658,   662,   663,
     664,   666,   670,   671,  -996,    71,  -996,   672,   674,   469,
     675,   677,   678,   474,  -996,    81,   679,   480,   481,  -996,
     -25,   680,   681,   -73,  -996,   485,   682,   687,   486,   691,
     489,   490,   695,   698,   496,   497,   699,   707,   709,   724,
     451,  -996,   725,   519,    35,  -996,  -996,  -996,   727,   734,
     532,   737,   738,   739,   745,   748,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
     544,  -996,  -996,  -996,  -996,  -996,   -95,   546,   548,  -996,
    -996,  -996,   754,   755,   756,  -996,   766,   765,   563,   327,
    -996,  -996,  -996,   769,   773,   774,   775,   776,   778,   780,
     779,   782,  -996,   783,   784,   785,   786,   570,   584,  -996,
    -996,  -996,   791,   790,  -996,   793,  -996,  -996,  -996,  -996,
    -996,   794,   795,   591,   593,   607,  -996,  -996,   793,   608,
     812,  -996,   610,  -996,   621,  -996,   624,  -996,  -996,  -996,
     793,   793,   793,   625,   626,   627,   628,  -996,   629,   630,
    -996,   631,   632,   633,  -996,  -996,   634,  -996,  -996,  -996,
     635,   765,  -996,  -996,   636,   637,  -996,   640,  -996,  -996,
     -50,   587,  -996,  -996,   -95,   641,   644,   651,  -996,   797,
    -996,  -996,    30,   160,  -996,    35,    78,   292,   292,   850,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,   853,
     855,   856,   860,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,   -91,    30,   313,   758,   861,   862,   863,   273,   252,
     152,   -20,    -5,   451,  -996,  -996,   864,  -145,  -996,  -996,
     867,   868,  -996,  -996,  -996,  -996,  -996,   -19,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,   850,  -996,   250,
     271,   274,  -996,  -996,  -996,  -996,   873,   875,   876,   877,
     878,   879,   881,  -996,   882,  -996,  -996,  -996,  -996,  -996,
     275,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
     290,  -996,   883,   884,  -996,  -996,   885,   887,  -996,  -996,
     886,   890,  -996,  -996,   888,   892,  -996,  -996,   891,   893,
    -996,  -996,  -996,   185,  -996,  -996,  -996,   894,  -996,  -996,
    -996,   284,  -996,  -996,  -996,  -996,   301,  -996,  -996,  -996,
     291,  -996,  -996,   895,   896,  -996,  -996,   897,   899,  -996,
     900,   901,   902,   903,   904,   905,   303,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,   906,   907,   908,  -996,
    -996,  -996,  -996,   310,  -996,  -996,  -996,  -996,  -996,  -996,
     909,   910,   911,  -996,   343,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,   347,  -996,  -996,  -996,
     912,  -996,   913,  -996,  -996,  -996,   361,  -996,  -996,  -996,
    -996,  -996,   364,  -996,   311,  -996,   914,  -996,   372,  -996,
    -996,   688,  -996,   915,   916,  -996,  -996,   917,   919,  -996,
    -996,  -996,   880,  -996,   918,  -996,  -996,  -996,   921,   922,
     923,   924,   718,   717,   720,   719,   722,   723,   728,   931,
     730,   932,   938,   940,   941,   292,  -996,  -996,   292,  -996,
     850,   668,  -996,   853,    81,  -996,   855,   -25,  -996,   856,
     757,  -996,   860,   -91,  -996,  -996,   313,  -996,   943,   758,
    -996,   309,   861,  -996,    71,  -996,   862,   -90,  -996,   863,
     743,   744,   746,   747,   753,   759,   273,  -996,   944,   967,
     762,   763,   767,   252,  -996,   788,   799,   800,   152,  -996,
     991,   992,   -20,  -996,   801,  1014,   809,  1017,    -5,  -996,
    -996,   190,   864,  -996,   816,  -145,  -996,  -996,  1027,  1031,
      42,  -996,   867,   296,  -996,   868,  1033,  -996,  -996,   129,
     710,   832,   845,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
     197,  -996,   852,   889,   898,   920,  -996,   374,  -996,   391,
    -996,  1070,  -996,  1077,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,   410,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
     925,  -996,  -996,  1084,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  1083,  1091,  -996,  -996,  -996,
    -996,  -996,  1088,  -996,   411,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,    28,   926,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,   927,   928,  -996,  -996,   929,  -996,    30,
    -996,  -996,  1093,  -996,  -996,  -996,  -996,  -996,   413,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,   930,   414,  -996,
     420,  -996,   933,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,   757,  -996,  -996,  1094,   934,  -996,   309,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    1096,   935,  1097,   190,  -996,  -996,  -996,  -996,  -996,  -996,
     939,  -996,  -996,  1098,  -996,   942,  -996,  -996,  1095,  -996,
    -996,   346,  -996,    11,  1095,  -996,  -996,  1100,  1101,  1102,
    -996,   426,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  1103,
     937,   946,   948,  1105,    11,  -996,   950,  -996,  -996,  -996,
     951,  -996,  -996,  -996
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   184,     9,   362,    11,
     565,    13,   592,    15,   624,    17,   485,    19,   494,    21,
     533,    23,   324,    25,   749,    27,   800,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   626,     0,   496,   535,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   137,   798,   182,   203,   205,   207,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   176,     0,     0,     0,     0,     0,   156,   163,
     165,     0,     0,     0,   353,   483,   524,     0,   431,   579,
     581,   423,     0,     0,     0,   280,   299,   289,   272,   662,
     615,   315,   336,   691,     0,   301,   716,   730,   747,   169,
     171,     0,     0,     0,   810,   852,     0,   136,     0,    69,
      72,    73,    74,    75,    76,    77,    78,    79,    80,   111,
     112,   113,   114,   115,    81,   119,   120,   121,   122,   123,
     124,   125,   126,   117,   118,   127,   128,   129,   106,   135,
     131,   132,   133,    84,    85,    86,    87,   103,    88,    90,
      89,   130,    94,    95,    82,   108,   109,   110,   107,    83,
      92,    93,   101,   102,   104,    91,    96,    97,    98,    99,
     100,   105,   116,   134,   197,     0,     0,     0,     0,   196,
       0,   186,   189,   190,   191,   192,   193,   194,   195,   556,
     583,   410,   412,   414,     0,     0,   418,   416,   656,   409,
     367,   368,   369,   370,   371,   372,   373,   374,   393,   394,
     395,   396,   397,   400,   401,   402,   403,   404,   405,   406,
     407,   398,   399,   408,     0,   364,   378,   379,   380,   383,
     384,   387,   388,   389,   386,   381,   382,   375,   376,   391,
     392,   377,   385,   390,   577,   576,   572,   573,   571,     0,
     567,   570,   574,   575,   608,     0,   611,     0,     0,   607,
     601,   602,   600,   605,   606,     0,   594,   597,   598,   603,
     604,   599,   654,   642,   644,   646,   648,   650,   652,   641,
     638,   639,   640,     0,   627,   628,   633,   634,   631,   635,
     636,   637,   632,     0,   514,   250,     0,   518,   516,   521,
       0,   510,   511,     0,   497,   498,   501,   513,   502,   503,
     504,   520,   505,   506,   507,   508,   509,   550,     0,     0,
     548,   549,   552,   553,     0,   536,   537,   540,   541,   542,
     543,   544,   545,   546,   547,   332,   334,   329,     0,   326,
     330,   331,     0,   773,   775,     0,   778,     0,     0,   782,
     786,     0,     0,   790,   792,   794,   796,   771,   769,   770,
       0,   751,   754,   766,   755,   756,   757,   758,   759,   760,
     761,   762,   763,   764,   765,   767,   768,   807,     0,     0,
     802,   805,   806,    47,    52,     0,    39,    45,     0,    66,
      62,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    60,    71,    68,     0,     0,
       0,     0,     0,   188,   185,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   366,   363,     0,   569,   566,
       0,     0,     0,     0,     0,   596,   593,     0,     0,     0,
       0,     0,     0,     0,   625,   630,   486,     0,     0,     0,
       0,     0,     0,     0,   495,   500,     0,     0,     0,   534,
     539,     0,     0,   328,   325,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     753,   750,     0,     0,   804,   801,    51,    43,     0,     0,
       0,     0,     0,     0,     0,     0,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
       0,   174,   175,   153,   154,   155,     0,     0,     0,   167,
     168,   173,     0,     0,     0,   178,     0,     0,     0,     0,
     420,   421,   422,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   715,     0,     0,     0,     0,     0,     0,   179,
     180,   181,     0,     0,    70,     0,   199,   200,   201,   202,
     187,     0,     0,     0,     0,     0,   429,   430,     0,     0,
       0,   365,     0,   568,     0,   610,     0,   613,   614,   595,
       0,     0,     0,     0,     0,     0,     0,   629,     0,     0,
     512,     0,     0,     0,   523,   499,     0,   554,   555,   538,
       0,     0,   327,   772,     0,     0,   777,     0,   780,   781,
       0,     0,   788,   789,     0,     0,     0,     0,   752,     0,
     809,   803,     0,     0,   138,     0,     0,     0,     0,   209,
     177,   158,   159,   160,   161,   162,   157,   164,   166,   355,
     487,   526,   433,    40,   580,   582,   425,   426,   427,   428,
     424,     0,    48,     0,     0,     0,   617,   317,     0,     0,
       0,     0,     0,     0,   170,   172,     0,     0,    53,   198,
     558,   585,   411,   413,   415,   419,   417,     0,   578,   609,
     612,   655,   643,   645,   647,   649,   651,   653,   515,   251,
     519,   517,   522,   551,   333,   335,   774,   776,   779,   784,
     785,   783,   787,   791,   793,   795,   797,   209,    44,     0,
       0,     0,   238,   243,   245,   247,     0,     0,     0,     0,
       0,     0,     0,   257,     0,   264,   266,   268,   270,   237,
       0,   216,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   230,   231,   232,   229,   233,   234,   235,   236,
       0,   214,     0,   210,   211,   360,     0,   356,   357,   492,
       0,   488,   489,   531,     0,   527,   528,   438,     0,   434,
     435,   287,   288,     0,   282,   285,   286,     0,   297,   298,
     294,     0,   291,   295,   296,   278,     0,   274,   277,   667,
       0,   664,   622,     0,   618,   619,   322,     0,   318,   319,
       0,     0,     0,     0,     0,     0,     0,   338,   341,   342,
     343,   344,   345,   346,   705,   711,     0,     0,     0,   704,
     701,   702,   703,     0,   693,   696,   699,   697,   698,   700,
       0,     0,     0,   311,     0,   303,   306,   307,   308,   309,
     310,   726,   728,   725,   723,   724,     0,   718,   721,   722,
       0,   742,     0,   745,   738,   739,     0,   732,   735,   736,
     737,   740,     0,   815,     0,   812,     0,   858,     0,   854,
     857,    55,   563,     0,   559,   560,   590,     0,   586,   587,
     660,   659,     0,   658,     0,    64,   799,   183,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   218,   204,   206,     0,   208,
     213,     0,   354,   359,   496,   484,   491,   535,   525,   530,
       0,   432,   437,   284,   281,   300,   293,   290,     0,   276,
     273,   669,   666,   663,   626,   616,   621,     0,   316,   321,
       0,     0,     0,     0,     0,     0,   340,   337,     0,     0,
       0,     0,     0,   695,   692,     0,     0,     0,   305,   302,
       0,     0,   720,   717,     0,     0,     0,     0,   734,   731,
     748,     0,   814,   811,     0,   856,   853,    57,     0,    56,
       0,   557,   562,     0,   584,   589,     0,   657,   808,     0,
       0,     0,     0,   249,   252,   253,   254,   255,   263,   256,
       0,   262,     0,     0,     0,     0,   217,     0,   212,     0,
     358,     0,   490,     0,   529,   482,   457,   458,   459,   461,
     462,   463,   447,   448,   466,   467,   468,   469,   470,   473,
     474,   475,   476,   477,   478,   479,   480,   471,   472,   481,
     443,   444,   445,   446,   455,   456,   452,   453,   454,   451,
     460,     0,   440,   449,   464,   465,   450,   436,   283,   292,
       0,   275,   688,     0,   686,   680,   681,   682,   683,   684,
     685,   687,   677,   678,   679,     0,   670,   671,   674,   675,
     676,   665,     0,   620,     0,   320,   347,   348,   349,   350,
     351,   352,   339,     0,     0,   710,   713,   714,   694,   312,
     313,   314,   304,     0,     0,   719,   741,     0,   744,     0,
     733,   830,     0,   828,   826,   820,   824,   825,     0,   817,
     822,   823,   821,   813,   859,   855,    54,    59,     0,   561,
       0,   588,     0,   240,   241,   242,   239,   244,   246,   248,
     259,   260,   261,   258,   265,   267,   269,   271,   215,   361,
     493,   532,   442,   439,   279,     0,     0,   668,   673,   623,
     323,   707,   708,   709,   706,   712,   727,   729,   743,   746,
       0,     0,     0,   819,   816,    58,   564,   591,   661,   441,
       0,   690,   672,     0,   827,     0,   818,   689,     0,   829,
     835,     0,   832,     0,   834,   831,   845,     0,     0,     0,
     850,     0,   837,   840,   841,   842,   843,   844,   833,     0,
       0,     0,     0,     0,   839,   836,     0,   847,   848,   849,
       0,   838,   846,   851
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,   -10,  -996,  -589,  -996,
     409,  -996,  -996,  -996,  -996,   360,  -996,  -594,  -996,  -996,
    -996,   -71,  -996,  -996,  -996,  -996,  -996,  -996,  -996,   388,
     609,  -996,  -996,   -43,   -14,    12,    16,    20,    33,   -59,
     -31,   -30,   -28,   -27,   -26,    19,  -996,    34,    37,    38,
      41,  -996,   400,    49,  -996,    52,  -996,    54,    55,    56,
    -996,    59,  -996,    62,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,   387,   604,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
     314,  -996,   109,  -996,  -712,   111,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,   -45,  -996,  -748,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,    89,
    -996,  -996,  -996,  -996,  -996,    97,  -731,  -996,  -996,  -996,
    -996,    98,  -996,  -996,  -996,  -996,  -996,  -996,  -996,    64,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,    84,  -996,  -996,
    -996,    88,   564,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
      80,  -996,  -996,  -996,  -996,  -996,  -996,  -995,  -996,  -996,
    -996,   115,  -996,  -996,  -996,   118,   606,  -996,  -996,  -993,
    -996,  -992,  -996,    73,  -996,    75,  -996,    66,    69,    70,
      72,  -996,  -996,  -996,  -991,  -996,  -996,  -996,  -996,   110,
    -996,  -996,  -119,  1057,  -996,  -996,  -996,  -996,  -996,   125,
    -996,  -996,  -996,   128,  -996,   590,  -996,   -67,  -996,  -996,
    -996,  -996,  -996,   -64,  -996,  -996,  -996,  -996,  -996,     4,
    -996,  -996,  -996,   132,  -996,  -996,  -996,   127,  -996,   611,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,    82,  -996,  -996,  -996,    68,   638,  -996,  -996,   -55,
    -996,   -12,  -996,  -996,  -996,  -996,  -996,    77,  -996,  -996,
    -996,    85,   619,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
     -60,  -996,  -996,  -996,   131,  -996,  -996,  -996,   135,  -996,
     618,   395,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -989,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,   138,  -996,  -996,  -996,   -93,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,   120,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,   112,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,   107,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,   419,   597,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,   475,   599,
    -996,  -996,  -996,  -996,  -996,  -996,   104,  -996,  -996,   -94,
    -996,  -996,  -996,  -996,  -996,  -996,  -116,  -996,  -996,  -134,
    -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,  -996,
     114,  -996
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     744,    87,    88,    41,    68,    84,    85,   769,   971,  1078,
    1079,   829,    43,    70,    90,   438,    91,    45,    71,   158,
     159,   160,   441,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   467,   736,   179,   468,   180,   469,   181,   182,   183,
     498,   184,   499,   185,   186,   187,   188,   461,   189,   190,
     191,   192,   193,   443,    47,    72,   230,   231,   232,   508,
     233,   234,   235,   236,   194,   444,   195,   445,   196,   446,
     852,   853,   854,  1008,   830,   831,   832,   988,  1236,   833,
     989,   834,   990,   835,   991,   836,   837,   548,   838,   839,
     840,   841,   842,   843,   999,  1243,   844,   845,   846,  1001,
     847,  1002,   848,  1003,   849,  1004,   197,   487,   886,   887,
     888,  1028,   198,   484,   873,   874,   875,   876,   199,   486,
     881,   882,   883,   884,   200,   485,   201,   494,   934,   935,
     936,   937,   938,   202,   490,   897,   898,   899,  1037,    63,
      80,   388,   389,   390,   561,   391,   562,   203,   491,   906,
     907,   908,   909,   910,   911,   912,   913,   204,   473,   856,
     857,   858,  1011,    49,    73,   274,   275,   276,   517,   277,
     518,   278,   519,   279,   523,   280,   522,   205,   206,   207,
     208,   480,   750,   285,   286,   209,   477,   868,   869,   870,
    1020,  1151,  1152,   210,   474,    57,    77,   860,   861,   862,
    1014,    59,    78,   353,   354,   355,   356,   357,   358,   359,
     547,   360,   551,   361,   550,   362,   363,   552,   364,   211,
     475,   864,   865,   866,  1017,    61,    79,   374,   375,   376,
     377,   378,   556,   379,   380,   381,   382,   288,   515,   973,
     974,   975,  1080,    51,    74,   299,   300,   301,   527,   212,
     478,   213,   479,   291,   516,   977,   978,   979,  1083,    53,
      75,   315,   316,   317,   530,   318,   319,   532,   320,   321,
     214,   489,   893,   894,   895,  1034,    55,    76,   333,   334,
     335,   336,   538,   337,   539,   338,   540,   339,   541,   340,
     542,   341,   543,   342,   537,   293,   524,   982,   983,  1086,
     215,   488,   890,   891,  1031,  1175,  1176,  1177,  1178,  1179,
    1255,  1180,   216,   492,   923,   924,   925,  1048,  1264,   926,
     927,  1049,   928,   929,   217,   218,   495,   946,   947,   948,
    1060,   949,  1061,   219,   496,   956,   957,   958,   959,  1065,
     960,   961,  1067,   220,   497,    65,    81,   410,   411,   412,
     413,   566,   414,   567,   415,   416,   569,   417,   418,   419,
     572,   801,   420,   573,   421,   422,   423,   576,   424,   577,
     425,   578,   426,   579,   221,   442,    67,    82,   429,   430,
     431,   582,   432,   222,   503,   964,   965,  1071,  1218,  1219,
    1220,  1221,  1272,  1222,  1270,  1291,  1292,  1293,  1301,  1302,
    1303,  1309,  1304,  1305,  1306,  1307,  1313,   223,   504,   968,
     969,   970
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     157,   229,   249,   295,   309,   329,    38,   351,   370,   387,
     407,   920,   372,   292,   256,   373,   850,   237,   289,   302,
     313,   331,   880,   365,   383,  1141,   408,  1142,  1143,  1150,
     250,  1156,   871,   352,   371,    31,    30,    32,   743,    33,
     385,   386,   257,   258,    86,   259,   260,   261,   427,   428,
     966,   345,   367,   346,   347,   368,   369,   385,   386,   251,
     238,   290,   303,   314,   332,   156,   366,   384,   439,   409,
     129,   130,   125,   440,   775,   129,   130,   287,   298,   312,
     330,   731,   732,   733,   734,   252,   781,   782,   783,   253,
     129,   130,   262,   254,   224,   225,   226,   227,   228,   506,
      42,    44,   323,   513,   507,   344,   255,   263,   514,   980,
     264,   265,   743,    46,   266,    48,   525,   126,   735,   872,
     156,   526,   267,   799,   800,   268,   528,   269,   270,   271,
     294,   529,   272,   941,   942,   273,   535,   129,   130,   281,
      89,   536,   282,   283,    50,   284,   126,   296,   310,   297,
     311,   950,   951,   952,  1233,  1234,  1235,   345,   246,   346,
     347,   247,    52,   348,   349,   350,   129,   130,  1261,  1262,
    1263,    92,    93,   129,   130,    94,   129,   130,    54,   563,
      56,    95,    96,    97,   564,   156,   322,    58,  1023,    60,
     156,  1024,   323,   324,   325,   326,   327,   328,  1296,    62,
      64,  1297,  1298,  1299,  1300,   953,    66,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,  1240,  1241,  1242,   580,
      34,    35,    36,    37,   581,   127,   128,   129,   130,   584,
     433,   434,   156,   506,   585,   129,   130,  1141,   985,  1142,
    1143,  1150,   131,  1156,   435,   436,   345,   132,   133,   134,
     135,   136,   137,   138,   584,   139,   914,   513,  1005,   986,
     140,   156,   987,  1006,   817,   129,   130,  1026,   156,   141,
    1027,   156,   142,  1005,  1032,   880,  1107,  1033,  1007,   143,
     437,   930,   931,   932,  1029,   920,  1046,   144,   145,  1030,
     447,  1047,   146,  1053,  1072,   147,   812,  1073,  1054,   148,
     813,   814,   815,   816,   817,   818,   819,   820,   821,   822,
     823,   544,   448,   449,   824,   825,   826,   827,   828,   450,
     149,   150,   151,   152,   153,   154,  1058,   129,   130,  1294,
    1062,  1059,  1295,   451,   155,  1063,    98,    99,   100,   101,
     102,   103,   156,   452,  1068,   546,   453,   580,   345,  1069,
     156,   126,  1070,   454,   455,  1075,  1211,  1005,  1212,  1213,
    1076,   456,  1248,   457,   126,   345,   304,   305,   306,   307,
     308,   129,   130,   458,   525,   915,   916,   917,   918,  1249,
     156,   459,   460,   462,   129,   130,   900,   901,   902,   903,
     904,   905,   246,  1252,   563,   247,  1273,   528,  1253,  1260,
     463,  1274,  1276,   535,   586,   587,  1162,  1163,  1277,  1314,
     746,   747,   748,   749,  1315,   157,   871,   878,   464,   879,
     465,   545,   229,   466,   470,   471,   472,   476,   481,   482,
     483,   493,   500,   501,   249,   588,   502,   295,   237,   505,
     509,   510,   156,   511,   309,   292,   256,   512,   520,   521,
     289,   531,   533,   302,   329,   534,   549,   553,   554,   555,
     313,   557,   250,   558,   351,   560,   559,   565,   568,   370,
     331,   570,   571,   372,   257,   258,   373,   259,   260,   261,
     365,   238,   156,   574,   575,   383,   156,   583,   589,   407,
     352,   251,   590,   290,   591,   371,   303,   592,   593,   156,
     594,   595,   610,   314,   605,   408,   596,   597,   598,   287,
     599,   600,   298,   332,   604,   601,   602,   252,   606,   312,
     616,   253,   603,   366,   262,   254,   129,   130,   384,   330,
     607,   608,   609,   611,   617,   612,   618,   622,   255,   263,
     623,   613,   264,   265,   614,   615,   266,   619,   409,   620,
     624,   621,   626,   627,   267,   628,   625,   268,   629,   269,
     270,   271,   633,   634,   272,   635,   630,   273,   631,   632,
     636,   281,   637,   638,   282,   283,   639,   284,   640,   641,
     643,   296,   644,   297,   642,   645,   646,   647,   310,   648,
     311,   392,   393,   394,   395,   396,   397,   398,   399,   400,
     401,   402,   403,   404,   652,   649,   653,   655,   650,   658,
     651,   405,   406,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,   661,   656,   662,
     663,   664,   157,   665,   668,   229,   669,   670,   672,   674,
     676,   156,   680,   657,   659,   666,   681,   682,   683,   675,
     684,   237,   677,   667,   685,   686,   688,   678,   689,   691,
     690,   692,   693,   696,   700,   701,   704,   694,   919,   933,
     943,   705,   407,   697,   698,   707,   967,   706,   703,   710,
     708,   709,   711,   714,   921,   939,   944,   954,   408,   712,
     713,   715,   808,   716,   238,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   717,   719,
     720,   722,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   723,   724,   126,   725,   726,   727,   922,   940,   945,
     955,   409,   728,   729,   730,   239,   737,   240,   738,   739,
     740,   741,   802,   129,   130,   241,   242,   243,   244,   245,
     131,   742,    32,   745,   751,   132,   133,   134,   752,   753,
     764,   755,   754,   756,   246,   757,   758,   247,   140,   759,
     760,   761,   762,   763,   765,   248,   766,   767,   768,   770,
     771,   772,   807,   773,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   774,   776,   777,
     778,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   779,   126,   345,   780,   784,   785,   786,   787,   788,
     789,   790,   791,   792,   793,   794,   796,   797,   149,   150,
     798,   804,   129,   130,   805,   242,   243,   851,   245,   131,
     855,   806,   859,   863,   132,   133,   134,   867,   889,   892,
     896,   963,   885,   246,   972,   976,   247,   992,   156,   993,
     994,   995,   996,   997,   248,   998,  1000,  1010,  1087,  1009,
    1013,  1012,  1015,  1016,  1018,  1019,  1022,  1021,  1077,  1036,
    1025,  1035,  1039,  1038,  1040,  1041,  1042,  1043,  1044,  1045,
    1050,  1051,  1052,  1055,  1056,  1057,  1064,  1066,  1074,  1082,
    1237,  1081,  1085,  1084,  1088,  1089,  1090,  1091,  1092,  1093,
    1094,  1095,  1096,  1097,  1098,  1100,  1102,   149,   150,  1099,
     249,  1101,  1103,   351,  1104,  1105,   370,  1160,  1193,  1115,
     372,   292,   256,   373,  1186,  1187,   289,  1188,  1189,   365,
    1164,  1122,   383,   329,  1190,  1154,   387,   156,   250,   352,
    1191,  1194,   371,  1195,  1196,  1140,  1173,  1116,  1197,   331,
     257,   258,   919,   259,   260,   261,  1171,   933,  1165,  1123,
    1124,   943,  1125,  1126,  1127,  1203,  1204,   251,   921,   290,
    1214,  1199,   366,   939,   967,   384,  1117,   944,  1155,   295,
    1200,  1201,   309,   954,  1206,   287,  1216,  1166,  1207,  1174,
    1208,  1209,   332,   252,  1153,   302,  1215,   253,   313,  1224,
     262,   254,  1118,  1226,  1227,  1172,  1119,  1232,   330,  1128,
    1120,   922,  1238,  1167,   255,   263,   940,  1168,   264,   265,
     945,  1169,   266,  1121,  1129,  1239,   955,  1130,  1131,  1217,
     267,  1132,  1244,   268,  1170,   269,   270,   271,   303,  1133,
     272,   314,  1134,   273,  1135,  1136,  1137,   281,  1250,  1138,
     282,   283,  1139,   284,   298,  1251,  1146,   312,  1256,  1147,
    1148,  1257,  1149,  1144,  1258,  1145,  1259,  1271,  1280,  1245,
    1283,  1285,  1290,  1288,  1310,  1311,  1312,  1316,  1246,  1320,
     795,   809,   877,   811,   803,   654,  1106,   660,  1161,  1108,
    1158,   984,  1202,  1185,  1159,  1184,  1192,   702,  1110,  1109,
    1247,   671,  1157,  1279,   343,  1254,  1265,  1266,  1267,  1268,
    1275,  1112,  1111,  1278,  1113,   695,  1284,  1281,  1228,  1287,
    1317,  1114,  1289,   296,   679,   297,   310,  1318,   311,  1319,
    1322,  1323,  1231,   687,  1229,  1282,   673,  1183,  1230,  1182,
    1181,   699,   981,  1198,  1205,  1210,  1223,   718,  1308,  1286,
    1321,  1115,   962,   721,     0,     0,     0,  1164,     0,  1225,
       0,     0,     0,  1122,     0,     0,     0,  1154,     0,  1269,
     810,     0,  1214,  1173,     0,     0,     0,  1140,     0,  1116,
       0,     0,     0,  1171,     0,  1165,     0,     0,  1216,     0,
       0,  1123,  1124,     0,  1125,  1126,  1127,     0,  1215,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1117,     0,
    1155,     0,     0,     0,  1166,     0,  1174,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1153,     0,     0,     0,
       0,  1217,  1172,     0,  1118,     0,     0,     0,  1119,     0,
    1167,  1128,  1120,     0,  1168,     0,     0,     0,  1169,     0,
       0,     0,     0,     0,     0,  1121,  1129,     0,     0,  1130,
    1131,  1170,     0,  1132,     0,     0,     0,     0,     0,     0,
       0,  1133,     0,     0,  1134,     0,  1135,  1136,  1137,     0,
       0,  1138,     0,     0,  1139,     0,     0,     0,  1146,     0,
       0,  1147,  1148,     0,  1149,  1144,     0,  1145
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   759,    79,    73,    73,    79,   728,    72,    73,    74,
      75,    76,   753,    78,    79,  1020,    81,  1020,  1020,  1020,
      73,  1020,   123,    78,    79,     5,     0,     7,   627,     9,
     130,   131,    73,    73,   210,    73,    73,    73,    13,    14,
     195,    76,    77,    78,    79,    80,    81,   130,   131,    73,
      72,    73,    74,    75,    76,   210,    78,    79,     3,    81,
      95,    96,    74,     8,   668,    95,    96,    73,    74,    75,
      76,   176,   177,   178,   179,    73,   680,   681,   682,    73,
      95,    96,    73,    73,    16,    17,    18,    19,    20,     3,
       7,     7,   121,     3,     8,    24,    73,    73,     8,   128,
      73,    73,   701,     7,    73,     7,     3,    75,   213,   210,
     210,     8,    73,   173,   174,    73,     3,    73,    73,    73,
      88,     8,    73,   153,   154,    73,     3,    95,    96,    73,
      10,     8,    73,    73,     7,    73,    75,    74,    75,    74,
      75,   156,   157,   158,    25,    26,    27,    76,   116,    78,
      79,   119,     7,    82,    83,    84,    95,    96,   140,   141,
     142,    11,    12,    95,    96,    15,    95,    96,     7,     3,
       7,    21,    22,    23,     8,   210,   115,     7,     3,     7,
     210,     6,   121,   122,   123,   124,   125,   126,   187,     7,
       7,   190,   191,   192,   193,   210,     7,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    39,    40,    41,     3,
     210,   211,   212,   213,     8,    85,    86,    95,    96,     3,
       6,     3,   210,     3,     8,    95,    96,  1252,     8,  1252,
    1252,  1252,   102,  1252,     4,     8,    76,   107,   108,   109,
     110,   111,   112,   113,     3,   115,    24,     3,     3,     8,
     120,   210,     8,     8,    32,    95,    96,     3,   210,   129,
       6,   210,   132,     3,     3,  1026,  1008,     6,     8,   139,
       3,   149,   150,   151,     3,  1053,     3,   147,   148,     8,
       4,     8,   152,     3,     3,   155,    24,     6,     8,   159,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,     8,     4,     4,    42,    43,    44,    45,    46,     4,
     180,   181,   182,   183,   184,   185,     3,    95,    96,     3,
       3,     8,     6,     4,   194,     8,    47,    48,    49,    50,
      51,    52,   210,     4,     3,     8,     4,     3,    76,     8,
     210,    75,     8,     4,     4,     3,   186,     3,   188,   189,
       8,     4,     8,     4,    75,    76,    90,    91,    92,    93,
      94,    95,    96,     4,     3,   143,   144,   145,   146,     8,
     210,     4,     4,     4,    95,    96,   133,   134,   135,   136,
     137,   138,   116,     3,     3,   119,     3,     3,     8,     8,
       4,     8,     8,     3,   434,   435,   117,   118,     8,     3,
     103,   104,   105,   106,     8,   506,   123,   124,     4,   126,
       4,     3,   513,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   525,   210,     4,   528,   513,     4,
       4,     4,   210,     4,   535,   525,   525,     4,     4,     4,
     525,     4,     4,   528,   545,     4,     4,     4,     8,     3,
     535,     4,   525,     4,   555,     3,     8,     4,     4,   560,
     545,     4,     4,   560,   525,   525,   560,   525,   525,   525,
     555,   513,   210,     4,     4,   560,   210,     4,     4,   580,
     555,   525,     4,   525,     4,   560,   528,     4,     4,   210,
       4,     4,     4,   535,   212,   580,   211,   211,   211,   525,
     211,   211,   528,   545,   213,   211,   211,   525,   212,   535,
       4,   525,   211,   555,   525,   525,    95,    96,   560,   545,
     212,   211,   211,   211,     4,   211,     4,     4,   525,   525,
       4,   213,   525,   525,   213,   213,   525,   213,   580,   213,
       4,   213,     4,     4,   525,     4,   211,   525,     4,   525,
     525,   525,     4,     4,   525,     4,   213,   525,   213,   213,
       4,   525,     4,     4,   525,   525,     4,   525,     4,     4,
       4,   528,     4,   528,   211,     4,     4,     4,   535,     4,
     535,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,     4,   213,     4,     4,   213,   211,
     213,   180,   181,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,     4,   213,     4,
       4,     4,   723,     4,     4,   726,     4,     4,     4,     4,
       4,   210,     4,   213,   211,   211,     4,     4,     4,   211,
       4,   726,   211,   213,     4,     4,     4,   211,     4,     4,
     211,     4,     4,     4,     4,     4,     4,   213,   759,   760,
     761,     4,   763,   213,   213,     4,   767,   211,   213,     4,
     211,   211,     4,     4,   759,   760,   761,   762,   763,   213,
     213,     4,   722,     4,   726,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,     4,     4,
     211,     4,    64,    65,    66,    67,    68,    69,    70,    71,
      72,     7,   210,    75,     7,     7,     7,   759,   760,   761,
     762,   763,     7,     5,   210,    87,   210,    89,   210,     5,
       5,     5,   175,    95,    96,    97,    98,    99,   100,   101,
     102,     5,     7,   210,     5,   107,   108,   109,     5,     5,
     210,     5,     7,     5,   116,     5,     7,   119,   120,     7,
       7,     7,     7,     7,   210,   127,     5,     7,     5,     5,
       5,   210,     5,   210,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,   210,   210,     7,
     210,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,   210,    75,    76,   210,   210,   210,   210,   210,   210,
     210,   210,   210,   210,   210,   210,   210,   210,   180,   181,
     210,   210,    95,    96,   210,    98,    99,     7,   101,   102,
       7,   210,     7,     7,   107,   108,   109,     7,     7,     7,
       7,     7,   114,   116,     7,     7,   119,     4,   210,     4,
       4,     4,     4,     4,   127,     4,     4,     3,     8,     6,
       3,     6,     6,     3,     6,     3,     3,     6,   210,     3,
       6,     6,     3,     6,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     3,
     210,     6,     3,     6,     6,     4,     4,     4,     4,   211,
     213,   211,   213,   211,   211,     4,     4,   180,   181,   211,
    1011,   211,     4,  1014,     4,     4,  1017,     4,     4,  1020,
    1017,  1011,  1011,  1017,   211,   211,  1011,   211,   211,  1014,
    1031,  1020,  1017,  1034,   211,  1020,  1037,   210,  1011,  1014,
     211,     4,  1017,   211,   211,  1020,  1031,  1020,   211,  1034,
    1011,  1011,  1053,  1011,  1011,  1011,  1031,  1058,  1031,  1020,
    1020,  1062,  1020,  1020,  1020,     4,     4,  1011,  1053,  1011,
    1071,   213,  1014,  1058,  1075,  1017,  1020,  1062,  1020,  1080,
     211,   211,  1083,  1068,   213,  1011,  1071,  1031,     4,  1031,
     211,     4,  1034,  1011,  1020,  1080,  1071,  1011,  1083,   213,
    1011,  1011,  1020,     6,     3,  1031,  1020,     4,  1034,  1020,
    1020,  1053,   210,  1031,  1011,  1011,  1058,  1031,  1011,  1011,
    1062,  1031,  1011,  1020,  1020,   210,  1068,  1020,  1020,  1071,
    1011,  1020,   210,  1011,  1031,  1011,  1011,  1011,  1080,  1020,
    1011,  1083,  1020,  1011,  1020,  1020,  1020,  1011,     8,  1020,
    1011,  1011,  1020,  1011,  1080,     8,  1020,  1083,     4,  1020,
    1020,     8,  1020,  1020,     3,  1020,     8,     4,     4,   210,
       4,     4,     7,     5,     4,     4,     4,     4,   210,     4,
     701,   723,   752,   726,   714,   506,  1005,   513,  1029,  1010,
    1023,   807,  1058,  1039,  1026,  1037,  1046,   563,  1013,  1011,
     210,   525,  1022,  1252,    77,   210,   210,   210,   210,   210,
     210,  1016,  1014,   210,  1017,   555,   211,   213,  1080,   210,
     213,  1019,   210,  1080,   535,  1080,  1083,   211,  1083,   211,
     210,   210,  1085,   545,  1082,  1258,   528,  1036,  1083,  1034,
    1032,   560,   777,  1053,  1062,  1068,  1072,   580,  1294,  1273,
    1314,  1252,   763,   584,    -1,    -1,    -1,  1258,    -1,  1075,
      -1,    -1,    -1,  1252,    -1,    -1,    -1,  1252,    -1,  1209,
     725,    -1,  1273,  1258,    -1,    -1,    -1,  1252,    -1,  1252,
      -1,    -1,    -1,  1258,    -1,  1258,    -1,    -1,  1273,    -1,
      -1,  1252,  1252,    -1,  1252,  1252,  1252,    -1,  1273,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1252,    -1,
    1252,    -1,    -1,    -1,  1258,    -1,  1258,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1252,    -1,    -1,    -1,
      -1,  1273,  1258,    -1,  1252,    -1,    -1,    -1,  1252,    -1,
    1258,  1252,  1252,    -1,  1258,    -1,    -1,    -1,  1258,    -1,
      -1,    -1,    -1,    -1,    -1,  1252,  1252,    -1,    -1,  1252,
    1252,  1258,    -1,  1252,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1252,    -1,    -1,  1252,    -1,  1252,  1252,  1252,    -1,
      -1,  1252,    -1,    -1,  1252,    -1,    -1,    -1,  1252,    -1,
      -1,  1252,  1252,    -1,  1252,  1252,    -1,  1252
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
       0,     5,     7,     9,   210,   211,   212,   213,   230,   231,
     232,   237,     7,   246,     7,   251,     7,   298,     7,   407,
       7,   487,     7,   503,     7,   520,     7,   439,     7,   445,
       7,   469,     7,   383,     7,   589,     7,   620,   238,   233,
     247,   252,   299,   408,   488,   504,   521,   440,   446,   470,
     384,   590,   621,   230,   239,   240,   210,   235,   236,    10,
     248,   250,    11,    12,    15,    21,    22,    23,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    85,    86,    95,
      96,   102,   107,   108,   109,   110,   111,   112,   113,   115,
     120,   129,   132,   139,   147,   148,   152,   155,   159,   180,
     181,   182,   183,   184,   185,   194,   210,   245,   253,   254,
     255,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   277,
     279,   281,   282,   283,   285,   287,   288,   289,   290,   292,
     293,   294,   295,   296,   308,   310,   312,   350,   356,   362,
     368,   370,   377,   391,   401,   421,   422,   423,   424,   429,
     437,   463,   493,   495,   514,   544,   556,   568,   569,   577,
     587,   618,   627,   651,    16,    17,    18,    19,    20,   245,
     300,   301,   302,   304,   305,   306,   307,   493,   495,    87,
      89,    97,    98,    99,   100,   101,   116,   119,   127,   245,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   271,   272,   273,   274,   277,   279,   281,
     282,   283,   285,   287,   409,   410,   411,   413,   415,   417,
     419,   421,   422,   423,   424,   427,   428,   463,   481,   493,
     495,   497,   514,   539,    88,   245,   417,   419,   463,   489,
     490,   491,   493,   495,    90,    91,    92,    93,    94,   245,
     417,   419,   463,   493,   495,   505,   506,   507,   509,   510,
     512,   513,   115,   121,   122,   123,   124,   125,   126,   245,
     463,   493,   495,   522,   523,   524,   525,   527,   529,   531,
     533,   535,   537,   437,    24,    76,    78,    79,    82,    83,
      84,   245,   330,   447,   448,   449,   450,   451,   452,   453,
     455,   457,   459,   460,   462,   493,   495,    77,    80,    81,
     245,   330,   451,   457,   471,   472,   473,   474,   475,   477,
     478,   479,   480,   493,   495,   130,   131,   245,   385,   386,
     387,   389,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   180,   181,   245,   493,   495,
     591,   592,   593,   594,   596,   598,   599,   601,   602,   603,
     606,   608,   609,   610,   612,   614,   616,    13,    14,   622,
     623,   624,   626,     6,     3,     4,     8,     3,   249,     3,
       8,   256,   619,   297,   309,   311,   313,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   291,     4,     4,     4,     4,     4,   275,   278,   280,
       4,     4,     4,   402,   438,   464,     4,   430,   494,   496,
     425,     4,     4,     4,   357,   369,   363,   351,   545,   515,
     378,   392,   557,     4,   371,   570,   578,   588,   284,   286,
       4,     4,     4,   628,   652,     4,     3,     8,   303,     4,
       4,     4,     4,     3,     8,   482,   498,   412,   414,   416,
       4,     4,   420,   418,   540,     3,     8,   492,     3,     8,
     508,     4,   511,     4,     4,     3,     8,   538,   526,   528,
     530,   532,   534,   536,     8,     3,     8,   454,   331,     4,
     458,   456,   461,     4,     8,     3,   476,     4,     4,     8,
       3,   388,   390,     3,     8,     4,   595,   597,     4,   600,
       4,     4,   604,   607,     4,     4,   611,   613,   615,   617,
       3,     8,   625,     4,     3,     8,   230,   230,   210,     4,
       4,     4,     4,     4,     4,     4,   211,   211,   211,   211,
     211,   211,   211,   211,   213,   212,   212,   212,   211,   211,
       4,   211,   211,   213,   213,   213,     4,     4,     4,   213,
     213,   213,     4,     4,     4,   211,     4,     4,     4,     4,
     213,   213,   213,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   211,     4,     4,     4,     4,     4,     4,   213,
     213,   213,     4,     4,   254,     4,   213,   213,   211,   211,
     301,     4,     4,     4,     4,     4,   211,   213,     4,     4,
       4,   410,     4,   490,     4,   211,     4,   211,   211,   506,
       4,     4,     4,     4,     4,     4,     4,   524,     4,     4,
     211,     4,     4,     4,   213,   449,     4,   213,   213,   473,
       4,     4,   386,   213,     4,     4,   211,     4,   211,   211,
       4,     4,   213,   213,     4,     4,     4,     4,   592,     4,
     211,   623,     4,     7,   210,     7,     7,     7,     7,     5,
     210,   176,   177,   178,   179,   213,   276,   210,   210,     5,
       5,     5,     5,   232,   234,   210,   103,   104,   105,   106,
     426,     5,     5,     5,     7,     5,     5,     5,     7,     7,
       7,     7,     7,     7,   210,   210,     5,     7,     5,   241,
       5,     5,   210,   210,   210,   241,   210,     7,   210,   210,
     210,   241,   241,   241,   210,   210,   210,   210,   210,   210,
     210,   210,   210,   210,   210,   234,   210,   210,   210,   173,
     174,   605,   175,   276,   210,   210,   210,     5,   230,   253,
     622,   300,    24,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    42,    43,    44,    45,    46,   245,
     318,   319,   320,   323,   325,   327,   329,   330,   332,   333,
     334,   335,   336,   337,   340,   341,   342,   344,   346,   348,
     318,     7,   314,   315,   316,     7,   403,   404,   405,     7,
     441,   442,   443,     7,   465,   466,   467,     7,   431,   432,
     433,   123,   210,   358,   359,   360,   361,   239,   124,   126,
     360,   364,   365,   366,   367,   114,   352,   353,   354,     7,
     546,   547,     7,   516,   517,   518,     7,   379,   380,   381,
     133,   134,   135,   136,   137,   138,   393,   394,   395,   396,
     397,   398,   399,   400,    24,   143,   144,   145,   146,   245,
     332,   493,   495,   558,   559,   560,   563,   564,   566,   567,
     149,   150,   151,   245,   372,   373,   374,   375,   376,   493,
     495,   153,   154,   245,   493,   495,   571,   572,   573,   575,
     156,   157,   158,   210,   493,   495,   579,   580,   581,   582,
     584,   585,   591,     7,   629,   630,   195,   245,   653,   654,
     655,   242,     7,   483,   484,   485,     7,   499,   500,   501,
     128,   525,   541,   542,   314,     8,     8,     8,   321,   324,
     326,   328,     4,     4,     4,     4,     4,     4,     4,   338,
       4,   343,   345,   347,   349,     3,     8,     8,   317,     6,
       3,   406,     6,     3,   444,     6,     3,   468,     6,     3,
     434,     6,     3,     3,     6,     6,     3,     6,   355,     3,
       8,   548,     3,     6,   519,     6,     3,   382,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,   561,   565,
       4,     4,     4,     3,     8,     4,     4,     4,     3,     8,
     574,   576,     3,     8,     4,   583,     4,   586,     3,     8,
       8,   631,     3,     6,     4,     3,     8,   210,   243,   244,
     486,     6,     3,   502,     6,     3,   543,     8,     6,     4,
       4,     4,     4,   211,   213,   211,   213,   211,   211,   211,
       4,   211,     4,     4,     4,     4,   319,   318,   316,   409,
     405,   447,   443,   471,   467,   245,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   271,
     272,   273,   274,   277,   279,   281,   282,   283,   285,   287,
     330,   401,   413,   415,   417,   419,   421,   422,   423,   424,
     428,   435,   436,   463,   493,   495,   539,   433,   359,   365,
       4,   353,   117,   118,   245,   257,   258,   259,   260,   261,
     262,   330,   463,   493,   495,   549,   550,   551,   552,   553,
     555,   547,   522,   518,   385,   381,   211,   211,   211,   211,
     211,   211,   394,     4,     4,   211,   211,   211,   559,   213,
     211,   211,   373,     4,     4,   572,   213,     4,   211,     4,
     580,   186,   188,   189,   245,   330,   493,   495,   632,   633,
     634,   635,   637,   630,   213,   654,     6,     3,   489,   485,
     505,   501,     4,    25,    26,    27,   322,   210,   210,   210,
      39,    40,    41,   339,   210,   210,   210,   210,     8,     8,
       8,     8,     3,     8,   210,   554,     4,     8,     3,     8,
       8,   140,   141,   142,   562,   210,   210,   210,   210,   230,
     638,     4,   636,     3,     8,   210,     8,     8,   210,   436,
       4,   213,   551,     4,   211,     4,   633,   210,     5,   210,
       7,   639,   640,   641,     3,     6,   187,   190,   191,   192,
     193,   642,   643,   644,   646,   647,   648,   649,   640,   645,
       4,     4,     4,   650,     3,     8,     4,   213,   211,   211,
       4,   643,   210,   210
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   214,   216,   215,   217,   215,   218,   215,   219,   215,
     220,   215,   221,   215,   222,   215,   223,   215,   224,   215,
     225,   215,   226,   215,   227,   215,   228,   215,   229,   215,
     230,   230,   230,   230,   230,   230,   230,   231,   233,   232,
     234,   235,   235,   236,   236,   236,   238,   237,   239,   239,
     240,   240,   240,   242,   241,   243,   243,   244,   244,   244,
     245,   247,   246,   249,   248,   248,   250,   252,   251,   253,
     253,   253,   254,   254,   254,   254,   254,   254,   254,   254,
     254,   254,   254,   254,   254,   254,   254,   254,   254,   254,
     254,   254,   254,   254,   254,   254,   254,   254,   254,   254,
     254,   254,   254,   254,   254,   254,   254,   254,   254,   254,
     254,   254,   254,   254,   254,   254,   254,   254,   254,   254,
     254,   254,   254,   254,   254,   254,   254,   254,   254,   254,
     254,   254,   254,   254,   254,   254,   254,   256,   255,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   275,   274,   276,   276,
     276,   276,   276,   278,   277,   280,   279,   281,   282,   284,
     283,   286,   285,   287,   288,   289,   291,   290,   292,   293,
     294,   295,   297,   296,   299,   298,   300,   300,   300,   301,
     301,   301,   301,   301,   301,   301,   301,   303,   302,   304,
     305,   306,   307,   309,   308,   311,   310,   313,   312,   314,
     314,   315,   315,   315,   317,   316,   318,   318,   318,   319,
     319,   319,   319,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   319,   321,   320,
     322,   322,   322,   324,   323,   326,   325,   328,   327,   329,
     331,   330,   332,   333,   334,   335,   336,   338,   337,   339,
     339,   339,   340,   341,   343,   342,   345,   344,   347,   346,
     349,   348,   351,   350,   352,   352,   352,   353,   355,   354,
     357,   356,   358,   358,   358,   359,   359,   360,   361,   363,
     362,   364,   364,   364,   365,   365,   365,   366,   367,   369,
     368,   371,   370,   372,   372,   372,   373,   373,   373,   373,
     373,   373,   374,   375,   376,   378,   377,   379,   379,   380,
     380,   380,   382,   381,   384,   383,   385,   385,   385,   385,
     386,   386,   388,   387,   390,   389,   392,   391,   393,   393,
     393,   394,   394,   394,   394,   394,   394,   395,   396,   397,
     398,   399,   400,   402,   401,   403,   403,   404,   404,   404,
     406,   405,   408,   407,   409,   409,   409,   410,   410,   410,
     410,   410,   410,   410,   410,   410,   410,   410,   410,   410,
     410,   410,   410,   410,   410,   410,   410,   410,   410,   410,
     410,   410,   410,   410,   410,   410,   410,   410,   410,   410,
     410,   410,   410,   410,   410,   410,   410,   410,   410,   410,
     412,   411,   414,   413,   416,   415,   418,   417,   420,   419,
     421,   422,   423,   425,   424,   426,   426,   426,   426,   427,
     428,   430,   429,   431,   431,   432,   432,   432,   434,   433,
     435,   435,   435,   436,   436,   436,   436,   436,   436,   436,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   436,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   436,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   436,
     436,   436,   436,   438,   437,   440,   439,   441,   441,   442,
     442,   442,   444,   443,   446,   445,   447,   447,   448,   448,
     448,   449,   449,   449,   449,   449,   449,   449,   449,   449,
     449,   450,   451,   452,   454,   453,   456,   455,   458,   457,
     459,   461,   460,   462,   464,   463,   465,   465,   466,   466,
     466,   468,   467,   470,   469,   471,   471,   472,   472,   472,
     473,   473,   473,   473,   473,   473,   473,   473,   473,   474,
     476,   475,   477,   478,   479,   480,   482,   481,   483,   483,
     484,   484,   484,   486,   485,   488,   487,   489,   489,   489,
     490,   490,   490,   490,   490,   490,   490,   492,   491,   494,
     493,   496,   495,   498,   497,   499,   499,   500,   500,   500,
     502,   501,   504,   503,   505,   505,   505,   506,   506,   506,
     506,   506,   506,   506,   506,   506,   506,   506,   508,   507,
     509,   511,   510,   512,   513,   515,   514,   516,   516,   517,
     517,   517,   519,   518,   521,   520,   522,   522,   523,   523,
     523,   524,   524,   524,   524,   524,   524,   524,   524,   524,
     524,   524,   526,   525,   528,   527,   530,   529,   532,   531,
     534,   533,   536,   535,   538,   537,   540,   539,   541,   541,
     543,   542,   545,   544,   546,   546,   546,   548,   547,   549,
     549,   550,   550,   550,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   552,   554,   553,
     555,   557,   556,   558,   558,   558,   559,   559,   559,   559,
     559,   559,   559,   559,   559,   561,   560,   562,   562,   562,
     563,   565,   564,   566,   567,   568,   570,   569,   571,   571,
     571,   572,   572,   572,   572,   572,   574,   573,   576,   575,
     578,   577,   579,   579,   579,   580,   580,   580,   580,   580,
     580,   581,   583,   582,   584,   586,   585,   588,   587,   590,
     589,   591,   591,   591,   592,   592,   592,   592,   592,   592,
     592,   592,   592,   592,   592,   592,   592,   592,   592,   592,
     592,   592,   593,   595,   594,   597,   596,   598,   600,   599,
     601,   602,   604,   603,   605,   605,   607,   606,   608,   609,
     611,   610,   613,   612,   615,   614,   617,   616,   619,   618,
     621,   620,   622,   622,   622,   623,   623,   625,   624,   626,
     628,   627,   629,   629,   629,   631,   630,   632,   632,   632,
     633,   633,   633,   633,   633,   633,   633,   634,   636,   635,
     638,   637,   639,   639,   639,   641,   640,   642,   642,   642,
     643,   643,   643,   643,   643,   645,   644,   646,   647,   648,
     650,   649,   652,   651,   653,   653,   653,   654,   654,   655
  };

  const signed char
  Dhcp6Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     2,     0,     4,     0,     1,
       1,     3,     2,     0,     4,     0,     1,     1,     3,     2,
       2,     0,     4,     0,     6,     1,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     3,     3,     0,
       4,     0,     4,     3,     3,     3,     0,     4,     3,     3,
       3,     3,     0,     6,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     3,     3,     0,     6,     0,     6,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     3,     3,     3,     0,     4,     1,
       1,     1,     3,     3,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     1,     3,     2,     1,     0,     4,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     0,
       6,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     1,     3,     2,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       3,     3,     3,     0,     4,     1,     1,     1,     1,     3,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     6,     0,     4,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     0,     1,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     0,     4,     0,     4,     0,     4,
       1,     0,     4,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     0,     1,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     3,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     4,     3,     3,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     0,     1,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     1,     1,
       0,     4,     0,     6,     1,     3,     2,     0,     4,     0,
       1,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       3,     0,     4,     3,     3,     3,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     3,     0,     4,     0,     6,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     0,     4,     1,     1,     0,     4,     3,     3,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     1,     3,     2,     1,     1,     0,     6,     3,
       0,     6,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     6,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     0,     4,     3,     3,     3,
       0,     4,     0,     6,     1,     3,     2,     1,     1,     3
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
  "\"re-detect\"", "\"service-sockets-require-all\"",
  "\"service-sockets-retry-wait-time\"", "\"service-sockets-max-retries\"",
  "\"lease-database\"", "\"hosts-database\"", "\"hosts-databases\"",
  "\"type\"", "\"memfile\"", "\"mysql\"", "\"postgresql\"", "\"user\"",
  "\"password\"", "\"host\"", "\"port\"", "\"persist\"",
  "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
  "\"max-reconnect-tries\"", "\"reconnect-wait-time\"", "\"on-fail\"",
  "\"stop-retry-exit\"", "\"serve-retry-exit\"",
  "\"serve-retry-continue\"", "\"max-row-errors\"", "\"trust-anchor\"",
  "\"cert-file\"", "\"key-file\"", "\"cipher-list\"",
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
  "\"encapsulate\"", "\"array\"", "\"parked-packet-limit\"",
  "\"shared-networks\"", "\"pools\"", "\"pool\"", "\"pd-pools\"",
  "\"prefix\"", "\"prefix-len\"", "\"excluded-prefix\"",
  "\"excluded-prefix-len\"", "\"delegated-len\"", "\"user-context\"",
  "\"comment\"", "\"subnet\"", "\"interface\"", "\"interface-id\"",
  "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"global\"", "\"all\"", "\"reservations-global\"",
  "\"reservations-in-subnet\"", "\"reservations-out-of-pool\"",
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
  "\"hostname-char-replacement\"", "\"early-global-reservations-lookup\"",
  "\"ip-reservations-unique\"", "\"reservations-lookup-first\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"",
  "\"compatibility\"", "\"lenient-option-parsing\"", "TOPLEVEL_JSON",
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
  "syntax_map", "$@18", "global_object", "$@19", "global_object_comma",
  "sub_dhcp6", "$@20", "global_params", "global_param", "data_directory",
  "$@21", "preferred_lifetime", "min_preferred_lifetime",
  "max_preferred_lifetime", "valid_lifetime", "min_valid_lifetime",
  "max_valid_lifetime", "renew_timer", "rebind_timer",
  "calculate_tee_times", "t1_percent", "t2_percent", "cache_threshold",
  "cache_max_age", "decline_probation_period", "ddns_send_updates",
  "ddns_override_no_update", "ddns_override_client_update",
  "ddns_replace_client_name", "$@22", "ddns_replace_client_name_value",
  "ddns_generated_prefix", "$@23", "ddns_qualifying_suffix", "$@24",
  "ddns_update_on_renew", "ddns_use_conflict_resolution",
  "hostname_char_set", "$@25", "hostname_char_replacement", "$@26",
  "store_extended_info", "statistic_default_sample_count",
  "statistic_default_sample_age", "server_tag", "$@27",
  "parked_packet_limit", "early_global_reservations_lookup",
  "ip_reservations_unique", "reservations_lookup_first",
  "interfaces_config", "$@28", "sub_interfaces6", "$@29",
  "interfaces_config_params", "interfaces_config_param", "interfaces_list",
  "$@30", "re_detect", "service_sockets_require_all",
  "service_sockets_retry_wait_time", "service_sockets_max_retries",
  "lease_database", "$@31", "hosts_database", "$@32", "hosts_databases",
  "$@33", "database_list", "not_empty_database_list", "database", "$@34",
  "database_map_params", "database_map_param", "database_type", "$@35",
  "db_type", "user", "$@36", "password", "$@37", "host", "$@38", "port",
  "name", "$@39", "persist", "lfc_interval", "readonly", "connect_timeout",
  "reconnect_wait_time", "on_fail", "$@40", "on_fail_mode",
  "max_row_errors", "max_reconnect_tries", "trust_anchor", "$@41",
  "cert_file", "$@42", "key_file", "$@43", "cipher_list", "$@44",
  "sanity_checks", "$@45", "sanity_checks_params", "sanity_checks_param",
  "lease_checks", "$@46", "mac_sources", "$@47", "mac_sources_list",
  "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@48",
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
  "$@63", "require_client_classes", "$@64", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "reservation_mode",
  "$@65", "hr_mode", "id", "rapid_commit", "shared_networks", "$@66",
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
  "dhcp_ddns_param", "enable_updates", "dep_qualifying_suffix", "$@117",
  "server_ip", "$@118", "server_port", "sender_ip", "$@119", "sender_port",
  "max_queue_size", "ncr_protocol", "$@120", "ncr_protocol_value",
  "ncr_format", "$@121", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@122",
  "dep_generated_prefix", "$@123", "dep_hostname_char_set", "$@124",
  "dep_hostname_char_replacement", "$@125", "config_control", "$@126",
  "sub_config_control", "$@127", "config_control_params",
  "config_control_param", "config_databases", "$@128",
  "config_fetch_wait_time", "loggers", "$@129", "loggers_entries",
  "logger_entry", "$@130", "logger_params", "logger_param", "debuglevel",
  "severity", "$@131", "output_options_list", "$@132",
  "output_options_list_content", "output_entry", "$@133",
  "output_params_list", "output_params", "output", "$@134", "flush",
  "maxsize", "maxver", "pattern", "$@135", "compatibility", "$@136",
  "compatibility_params", "compatibility_param", "lenient_option_parsing", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const short
  Dhcp6Parser::yyrline_[] =
  {
       0,   302,   302,   302,   303,   303,   304,   304,   305,   305,
     306,   306,   307,   307,   308,   308,   309,   309,   310,   310,
     311,   311,   312,   312,   313,   313,   314,   314,   315,   315,
     323,   324,   325,   326,   327,   328,   329,   332,   337,   337,
     348,   351,   352,   355,   360,   366,   371,   371,   378,   379,
     382,   386,   390,   396,   396,   403,   404,   407,   411,   415,
     425,   434,   434,   449,   449,   463,   466,   472,   472,   481,
     482,   483,   490,   491,   492,   493,   494,   495,   496,   497,
     498,   499,   500,   501,   502,   503,   504,   505,   506,   507,
     508,   509,   510,   511,   512,   513,   514,   515,   516,   517,
     518,   519,   520,   521,   522,   523,   524,   525,   526,   527,
     528,   529,   530,   531,   532,   533,   534,   535,   536,   537,
     538,   539,   540,   541,   542,   543,   544,   545,   546,   547,
     548,   549,   550,   551,   552,   553,   554,   557,   557,   566,
     572,   578,   584,   590,   596,   602,   608,   614,   620,   626,
     632,   638,   644,   650,   656,   662,   668,   668,   677,   680,
     683,   686,   689,   695,   695,   704,   704,   713,   719,   725,
     725,   734,   734,   743,   749,   755,   761,   761,   770,   776,
     782,   788,   794,   794,   806,   806,   815,   816,   817,   822,
     823,   824,   825,   826,   827,   828,   829,   832,   832,   843,
     849,   855,   861,   867,   867,   880,   880,   893,   893,   904,
     905,   908,   909,   910,   915,   915,   925,   926,   927,   932,
     933,   934,   935,   936,   937,   938,   939,   940,   941,   942,
     943,   944,   945,   946,   947,   948,   949,   950,   953,   953,
     961,   962,   963,   966,   966,   975,   975,   984,   984,   993,
     999,   999,  1008,  1014,  1020,  1026,  1032,  1038,  1038,  1046,
    1047,  1048,  1051,  1057,  1063,  1063,  1072,  1072,  1081,  1081,
    1090,  1090,  1099,  1099,  1110,  1111,  1112,  1117,  1119,  1119,
    1138,  1138,  1149,  1150,  1151,  1156,  1157,  1160,  1165,  1170,
    1170,  1181,  1182,  1183,  1188,  1189,  1190,  1193,  1198,  1205,
    1205,  1218,  1218,  1231,  1232,  1233,  1238,  1239,  1240,  1241,
    1242,  1243,  1246,  1252,  1258,  1264,  1264,  1275,  1276,  1279,
    1280,  1281,  1286,  1286,  1296,  1296,  1306,  1307,  1308,  1311,
    1314,  1315,  1318,  1318,  1327,  1327,  1336,  1336,  1348,  1349,
    1350,  1355,  1356,  1357,  1358,  1359,  1360,  1363,  1369,  1375,
    1381,  1387,  1393,  1402,  1402,  1416,  1417,  1420,  1421,  1422,
    1431,  1431,  1457,  1457,  1468,  1469,  1470,  1476,  1477,  1478,
    1479,  1480,  1481,  1482,  1483,  1484,  1485,  1486,  1487,  1488,
    1489,  1490,  1491,  1492,  1493,  1494,  1495,  1496,  1497,  1498,
    1499,  1500,  1501,  1502,  1503,  1504,  1505,  1506,  1507,  1508,
    1509,  1510,  1511,  1512,  1513,  1514,  1515,  1516,  1517,  1518,
    1521,  1521,  1530,  1530,  1539,  1539,  1548,  1548,  1557,  1557,
    1568,  1574,  1580,  1586,  1586,  1594,  1595,  1596,  1597,  1600,
    1606,  1614,  1614,  1626,  1627,  1631,  1632,  1633,  1638,  1638,
    1646,  1647,  1648,  1653,  1654,  1655,  1656,  1657,  1658,  1659,
    1660,  1661,  1662,  1663,  1664,  1665,  1666,  1667,  1668,  1669,
    1670,  1671,  1672,  1673,  1674,  1675,  1676,  1677,  1678,  1679,
    1680,  1681,  1682,  1683,  1684,  1685,  1686,  1687,  1688,  1689,
    1690,  1691,  1692,  1699,  1699,  1713,  1713,  1722,  1723,  1726,
    1727,  1728,  1735,  1735,  1750,  1750,  1764,  1765,  1768,  1769,
    1770,  1775,  1776,  1777,  1778,  1779,  1780,  1781,  1782,  1783,
    1784,  1787,  1789,  1795,  1797,  1797,  1806,  1806,  1815,  1815,
    1824,  1826,  1826,  1835,  1845,  1845,  1858,  1859,  1864,  1865,
    1866,  1873,  1873,  1885,  1885,  1897,  1898,  1903,  1904,  1905,
    1912,  1913,  1914,  1915,  1916,  1917,  1918,  1919,  1920,  1923,
    1925,  1925,  1934,  1936,  1938,  1944,  1953,  1953,  1966,  1967,
    1970,  1971,  1972,  1977,  1977,  1987,  1987,  1997,  1998,  1999,
    2004,  2005,  2006,  2007,  2008,  2009,  2010,  2013,  2013,  2022,
    2022,  2047,  2047,  2077,  2077,  2090,  2091,  2094,  2095,  2096,
    2101,  2101,  2113,  2113,  2125,  2126,  2127,  2132,  2133,  2134,
    2135,  2136,  2137,  2138,  2139,  2140,  2141,  2142,  2145,  2145,
    2154,  2160,  2160,  2169,  2175,  2184,  2184,  2195,  2196,  2199,
    2200,  2201,  2206,  2206,  2215,  2215,  2224,  2225,  2228,  2229,
    2230,  2236,  2237,  2238,  2239,  2240,  2241,  2242,  2243,  2244,
    2245,  2246,  2249,  2249,  2260,  2260,  2271,  2271,  2280,  2280,
    2289,  2289,  2298,  2298,  2307,  2307,  2321,  2321,  2332,  2333,
    2336,  2336,  2348,  2348,  2359,  2360,  2361,  2366,  2366,  2376,
    2377,  2380,  2381,  2382,  2387,  2388,  2389,  2390,  2391,  2392,
    2393,  2394,  2395,  2396,  2397,  2398,  2399,  2402,  2404,  2404,
    2413,  2422,  2422,  2435,  2436,  2437,  2442,  2443,  2444,  2445,
    2446,  2447,  2448,  2449,  2450,  2453,  2453,  2461,  2462,  2463,
    2466,  2472,  2472,  2481,  2487,  2495,  2503,  2503,  2514,  2515,
    2516,  2521,  2522,  2523,  2524,  2525,  2528,  2528,  2537,  2537,
    2549,  2549,  2562,  2563,  2564,  2569,  2570,  2571,  2572,  2573,
    2574,  2577,  2583,  2583,  2592,  2598,  2598,  2608,  2608,  2621,
    2621,  2631,  2632,  2633,  2638,  2639,  2640,  2641,  2642,  2643,
    2644,  2645,  2646,  2647,  2648,  2649,  2650,  2651,  2652,  2653,
    2654,  2655,  2658,  2665,  2665,  2674,  2674,  2683,  2689,  2689,
    2698,  2704,  2710,  2710,  2719,  2720,  2723,  2723,  2733,  2740,
    2747,  2747,  2756,  2756,  2766,  2766,  2776,  2776,  2788,  2788,
    2800,  2800,  2810,  2811,  2812,  2818,  2819,  2822,  2822,  2833,
    2841,  2841,  2854,  2855,  2856,  2862,  2862,  2870,  2871,  2872,
    2877,  2878,  2879,  2880,  2881,  2882,  2883,  2886,  2892,  2892,
    2901,  2901,  2912,  2913,  2914,  2919,  2919,  2927,  2928,  2929,
    2934,  2935,  2936,  2937,  2938,  2941,  2941,  2950,  2956,  2962,
    2968,  2968,  2977,  2977,  2988,  2989,  2990,  2995,  2996,  2999
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
#line 6300 "dhcp6_parser.cc"

#line 3005 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
