// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.


// Take the name prefix into account.
#define yylex   parser6_lex



#include "dhcp6_parser.h"


// Unqualified %code blocks.
#line 34 "dhcp6_parser.yy"

#include <dhcp6/parser_context.h>

// Avoid warnings with the error counter.
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#line 57 "dhcp6_parser.cc"


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
      yy_stack_print_ ();                \
  } while (false)

#else // !PARSER6_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
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
#line 150 "dhcp6_parser.cc"

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

  /*---------.
  | symbol.  |
  `---------*/



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

  Dhcp6Parser::symbol_kind_type
  Dhcp6Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Dhcp6Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Dhcp6Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_hr_mode: // hr_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOAT: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTEGER: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING: // "constant string"
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
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_hr_mode: // hr_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOAT: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTEGER: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING: // "constant string"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Dhcp6Parser::stack_symbol_type&
  Dhcp6Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_hr_mode: // hr_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
        value.copy< ElementPtr > (that.value);
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.copy< bool > (that.value);
        break;

      case symbol_kind::S_FLOAT: // "floating point"
        value.copy< double > (that.value);
        break;

      case symbol_kind::S_INTEGER: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case symbol_kind::S_STRING: // "constant string"
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
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_hr_mode: // hr_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.move< bool > (that.value);
        break;

      case symbol_kind::S_FLOAT: // "floating point"
        value.move< double > (that.value);
        break;

      case symbol_kind::S_INTEGER: // "integer"
        value.move< int64_t > (that.value);
        break;

      case symbol_kind::S_STRING: // "constant string"
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
  Dhcp6Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        switch (yykind)
    {
      case symbol_kind::S_STRING: // "constant string"
#line 309 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 413 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 309 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 419 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 309 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 425 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 309 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 431 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 309 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 437 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 309 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 443 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 309 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 449 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 309 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 455 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 309 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 461 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 309 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 467 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 309 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 473 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 309 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 479 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 309 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 485 "dhcp6_parser.cc"
        break;

      default:
        break;
    }
        yyo << ')';
      }
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
  Dhcp6Parser::yypop_ (int n) YY_NOEXCEPT
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
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Dhcp6Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Dhcp6Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
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
    YY_STACK_PRINT ();

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
        YYCDEBUG << "Reading a token\n";
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

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
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
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_hr_mode: // hr_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case symbol_kind::S_FLOAT: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case symbol_kind::S_INTEGER: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case symbol_kind::S_STRING: // "constant string"
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
  case 2: // $@1: %empty
#line 318 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 766 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 319 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 772 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 320 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 778 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 321 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 784 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 322 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 790 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 323 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 796 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 324 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 802 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 325 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 808 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 326 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 814 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 327 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 820 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 328 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 826 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 329 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 832 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 330 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 838 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 331 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 844 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 339 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 850 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 340 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 856 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 341 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 862 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 342 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 868 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 343 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 874 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 344 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 880 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 345 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 886 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 348 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 895 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 353 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 906 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 358 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 916 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 364 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 922 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 371 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 932 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 376 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 943 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 382 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 951 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 387 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 960 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 390 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 968 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 398 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 977 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 402 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 986 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 406 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 994 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 412 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 1002 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 414 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1011 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 423 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1020 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 427 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1029 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 431 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1037 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 441 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1048 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 450 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1059 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 455 "dhcp6_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1072 "dhcp6_parser.cc"
    break;

  case 63: // $@19: %empty
#line 465 "dhcp6_parser.yy"
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
#line 1087 "dhcp6_parser.cc"
    break;

  case 64: // global_object: "Dhcp6" $@19 ":" "{" global_params "}"
#line 474 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1097 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 482 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1105 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 488 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1115 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 492 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1124 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 499 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1132 "dhcp6_parser.cc"
    break;

  case 141: // $@21: %empty
#line 577 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1141 "dhcp6_parser.cc"
    break;

  case 142: // data_directory: "data-directory" $@21 ":" "constant string"
#line 580 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1151 "dhcp6_parser.cc"
    break;

  case 143: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 586 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1161 "dhcp6_parser.cc"
    break;

  case 144: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 592 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1171 "dhcp6_parser.cc"
    break;

  case 145: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 598 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1181 "dhcp6_parser.cc"
    break;

  case 146: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 604 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1191 "dhcp6_parser.cc"
    break;

  case 147: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 610 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1201 "dhcp6_parser.cc"
    break;

  case 148: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 616 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1211 "dhcp6_parser.cc"
    break;

  case 149: // renew_timer: "renew-timer" ":" "integer"
#line 622 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1221 "dhcp6_parser.cc"
    break;

  case 150: // rebind_timer: "rebind-timer" ":" "integer"
#line 628 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1231 "dhcp6_parser.cc"
    break;

  case 151: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 634 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1241 "dhcp6_parser.cc"
    break;

  case 152: // t1_percent: "t1-percent" ":" "floating point"
#line 640 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1251 "dhcp6_parser.cc"
    break;

  case 153: // t2_percent: "t2-percent" ":" "floating point"
#line 646 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1261 "dhcp6_parser.cc"
    break;

  case 154: // cache_threshold: "cache-threshold" ":" "floating point"
#line 652 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1271 "dhcp6_parser.cc"
    break;

  case 155: // cache_max_age: "cache-max-age" ":" "integer"
#line 658 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1281 "dhcp6_parser.cc"
    break;

  case 156: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 664 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1291 "dhcp6_parser.cc"
    break;

  case 157: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 670 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1301 "dhcp6_parser.cc"
    break;

  case 158: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 676 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1311 "dhcp6_parser.cc"
    break;

  case 159: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 682 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1321 "dhcp6_parser.cc"
    break;

  case 160: // $@22: %empty
#line 688 "dhcp6_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1330 "dhcp6_parser.cc"
    break;

  case 161: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 691 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1339 "dhcp6_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "when-present"
#line 697 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1347 "dhcp6_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "never"
#line 700 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1355 "dhcp6_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "always"
#line 703 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1363 "dhcp6_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "when-not-present"
#line 706 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1371 "dhcp6_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "boolean"
#line 709 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1380 "dhcp6_parser.cc"
    break;

  case 167: // $@23: %empty
#line 715 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1389 "dhcp6_parser.cc"
    break;

  case 168: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 718 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1399 "dhcp6_parser.cc"
    break;

  case 169: // $@24: %empty
#line 724 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1408 "dhcp6_parser.cc"
    break;

  case 170: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 727 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1418 "dhcp6_parser.cc"
    break;

  case 171: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 733 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1428 "dhcp6_parser.cc"
    break;

  case 172: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 742 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.warning(yystack_[1].location, "ddns-use-conflict-resolution is deprecated. "
             "Substituting ddns-conflict-resolution-mode");
    ElementPtr mode(new StringElement(b->boolValue() ? "check-with-dhcid"
                                      : "no-check-with-dhcid"));
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", mode);
}
#line 1442 "dhcp6_parser.cc"
    break;

  case 173: // $@25: %empty
#line 752 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1451 "dhcp6_parser.cc"
    break;

  case 174: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 755 "dhcp6_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 175: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 761 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1468 "dhcp6_parser.cc"
    break;

  case 176: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 764 "dhcp6_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1476 "dhcp6_parser.cc"
    break;

  case 177: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 767 "dhcp6_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1484 "dhcp6_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 770 "dhcp6_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1492 "dhcp6_parser.cc"
    break;

  case 179: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 775 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1502 "dhcp6_parser.cc"
    break;

  case 180: // $@26: %empty
#line 781 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1511 "dhcp6_parser.cc"
    break;

  case 181: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 784 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1521 "dhcp6_parser.cc"
    break;

  case 182: // $@27: %empty
#line 790 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1530 "dhcp6_parser.cc"
    break;

  case 183: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 793 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1540 "dhcp6_parser.cc"
    break;

  case 184: // store_extended_info: "store-extended-info" ":" "boolean"
#line 799 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1550 "dhcp6_parser.cc"
    break;

  case 185: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 805 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1560 "dhcp6_parser.cc"
    break;

  case 186: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 811 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1570 "dhcp6_parser.cc"
    break;

  case 187: // $@28: %empty
#line 817 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1579 "dhcp6_parser.cc"
    break;

  case 188: // server_tag: "server-tag" $@28 ":" "constant string"
#line 820 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1589 "dhcp6_parser.cc"
    break;

  case 189: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 826 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1599 "dhcp6_parser.cc"
    break;

  case 190: // $@29: %empty
#line 832 "dhcp6_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1608 "dhcp6_parser.cc"
    break;

  case 191: // allocator: "allocator" $@29 ":" "constant string"
#line 835 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1618 "dhcp6_parser.cc"
    break;

  case 192: // $@30: %empty
#line 841 "dhcp6_parser.yy"
                           {
    ctx.unique("pd-allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1627 "dhcp6_parser.cc"
    break;

  case 193: // pd_allocator: "pd-allocator" $@30 ":" "constant string"
#line 844 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-allocator", al);
    ctx.leave();
}
#line 1637 "dhcp6_parser.cc"
    break;

  case 194: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 850 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1647 "dhcp6_parser.cc"
    break;

  case 195: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 856 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1657 "dhcp6_parser.cc"
    break;

  case 196: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 862 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1667 "dhcp6_parser.cc"
    break;

  case 197: // $@31: %empty
#line 868 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1679 "dhcp6_parser.cc"
    break;

  case 198: // interfaces_config: "interfaces-config" $@31 ":" "{" interfaces_config_params "}"
#line 874 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1689 "dhcp6_parser.cc"
    break;

  case 199: // $@32: %empty
#line 880 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1699 "dhcp6_parser.cc"
    break;

  case 200: // sub_interfaces6: "{" $@32 interfaces_config_params "}"
#line 884 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1708 "dhcp6_parser.cc"
    break;

  case 203: // interfaces_config_params: interfaces_config_params ","
#line 891 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1716 "dhcp6_parser.cc"
    break;

  case 212: // $@33: %empty
#line 906 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1728 "dhcp6_parser.cc"
    break;

  case 213: // interfaces_list: "interfaces" $@33 ":" list_strings
#line 912 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1737 "dhcp6_parser.cc"
    break;

  case 214: // re_detect: "re-detect" ":" "boolean"
#line 917 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1747 "dhcp6_parser.cc"
    break;

  case 215: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 923 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1757 "dhcp6_parser.cc"
    break;

  case 216: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 929 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1767 "dhcp6_parser.cc"
    break;

  case 217: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 935 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1777 "dhcp6_parser.cc"
    break;

  case 218: // $@34: %empty
#line 941 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1789 "dhcp6_parser.cc"
    break;

  case 219: // lease_database: "lease-database" $@34 ":" "{" database_map_params "}"
#line 947 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1800 "dhcp6_parser.cc"
    break;

  case 220: // $@35: %empty
#line 954 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1812 "dhcp6_parser.cc"
    break;

  case 221: // hosts_database: "hosts-database" $@35 ":" "{" database_map_params "}"
#line 960 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1823 "dhcp6_parser.cc"
    break;

  case 222: // $@36: %empty
#line 967 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1835 "dhcp6_parser.cc"
    break;

  case 223: // hosts_databases: "hosts-databases" $@36 ":" "[" database_list "]"
#line 973 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1844 "dhcp6_parser.cc"
    break;

  case 228: // not_empty_database_list: not_empty_database_list ","
#line 984 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1852 "dhcp6_parser.cc"
    break;

  case 229: // $@37: %empty
#line 989 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1862 "dhcp6_parser.cc"
    break;

  case 230: // database: "{" $@37 database_map_params "}"
#line 993 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1872 "dhcp6_parser.cc"
    break;

  case 233: // database_map_params: database_map_params ","
#line 1001 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1880 "dhcp6_parser.cc"
    break;

  case 257: // $@38: %empty
#line 1031 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1889 "dhcp6_parser.cc"
    break;

  case 258: // database_type: "type" $@38 ":" db_type
#line 1034 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1898 "dhcp6_parser.cc"
    break;

  case 259: // db_type: "memfile"
#line 1039 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1904 "dhcp6_parser.cc"
    break;

  case 260: // db_type: "mysql"
#line 1040 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1910 "dhcp6_parser.cc"
    break;

  case 261: // db_type: "postgresql"
#line 1041 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1916 "dhcp6_parser.cc"
    break;

  case 262: // $@39: %empty
#line 1044 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1925 "dhcp6_parser.cc"
    break;

  case 263: // user: "user" $@39 ":" "constant string"
#line 1047 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1935 "dhcp6_parser.cc"
    break;

  case 264: // $@40: %empty
#line 1053 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1944 "dhcp6_parser.cc"
    break;

  case 265: // password: "password" $@40 ":" "constant string"
#line 1056 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1954 "dhcp6_parser.cc"
    break;

  case 266: // $@41: %empty
#line 1062 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1963 "dhcp6_parser.cc"
    break;

  case 267: // host: "host" $@41 ":" "constant string"
#line 1065 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1973 "dhcp6_parser.cc"
    break;

  case 268: // port: "port" ":" "integer"
#line 1071 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1983 "dhcp6_parser.cc"
    break;

  case 269: // $@42: %empty
#line 1077 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1992 "dhcp6_parser.cc"
    break;

  case 270: // name: "name" $@42 ":" "constant string"
#line 1080 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2002 "dhcp6_parser.cc"
    break;

  case 271: // persist: "persist" ":" "boolean"
#line 1086 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2012 "dhcp6_parser.cc"
    break;

  case 272: // lfc_interval: "lfc-interval" ":" "integer"
#line 1092 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2022 "dhcp6_parser.cc"
    break;

  case 273: // readonly: "readonly" ":" "boolean"
#line 1098 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2032 "dhcp6_parser.cc"
    break;

  case 274: // connect_timeout: "connect-timeout" ":" "integer"
#line 1104 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2042 "dhcp6_parser.cc"
    break;

  case 275: // read_timeout: "read-timeout" ":" "integer"
#line 1110 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2052 "dhcp6_parser.cc"
    break;

  case 276: // write_timeout: "write-timeout" ":" "integer"
#line 1116 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2062 "dhcp6_parser.cc"
    break;

  case 277: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1122 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2072 "dhcp6_parser.cc"
    break;

  case 278: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1129 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2082 "dhcp6_parser.cc"
    break;

  case 279: // $@43: %empty
#line 1135 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2091 "dhcp6_parser.cc"
    break;

  case 280: // on_fail: "on-fail" $@43 ":" on_fail_mode
#line 1138 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2100 "dhcp6_parser.cc"
    break;

  case 281: // on_fail_mode: "stop-retry-exit"
#line 1143 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2106 "dhcp6_parser.cc"
    break;

  case 282: // on_fail_mode: "serve-retry-exit"
#line 1144 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2112 "dhcp6_parser.cc"
    break;

  case 283: // on_fail_mode: "serve-retry-continue"
#line 1145 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2118 "dhcp6_parser.cc"
    break;

  case 284: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1148 "dhcp6_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2128 "dhcp6_parser.cc"
    break;

  case 285: // max_row_errors: "max-row-errors" ":" "integer"
#line 1154 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2138 "dhcp6_parser.cc"
    break;

  case 286: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1160 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2148 "dhcp6_parser.cc"
    break;

  case 287: // $@44: %empty
#line 1166 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2157 "dhcp6_parser.cc"
    break;

  case 288: // trust_anchor: "trust-anchor" $@44 ":" "constant string"
#line 1169 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2167 "dhcp6_parser.cc"
    break;

  case 289: // $@45: %empty
#line 1175 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2176 "dhcp6_parser.cc"
    break;

  case 290: // cert_file: "cert-file" $@45 ":" "constant string"
#line 1178 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2186 "dhcp6_parser.cc"
    break;

  case 291: // $@46: %empty
#line 1184 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2195 "dhcp6_parser.cc"
    break;

  case 292: // key_file: "key-file" $@46 ":" "constant string"
#line 1187 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2205 "dhcp6_parser.cc"
    break;

  case 293: // $@47: %empty
#line 1193 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2214 "dhcp6_parser.cc"
    break;

  case 294: // cipher_list: "cipher-list" $@47 ":" "constant string"
#line 1196 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2224 "dhcp6_parser.cc"
    break;

  case 295: // $@48: %empty
#line 1202 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2236 "dhcp6_parser.cc"
    break;

  case 296: // sanity_checks: "sanity-checks" $@48 ":" "{" sanity_checks_params "}"
#line 1208 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2245 "dhcp6_parser.cc"
    break;

  case 299: // sanity_checks_params: sanity_checks_params ","
#line 1215 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2253 "dhcp6_parser.cc"
    break;

  case 302: // $@49: %empty
#line 1224 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2262 "dhcp6_parser.cc"
    break;

  case 303: // lease_checks: "lease-checks" $@49 ":" "constant string"
#line 1227 "dhcp6_parser.yy"
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
#line 2282 "dhcp6_parser.cc"
    break;

  case 304: // $@50: %empty
#line 1243 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2291 "dhcp6_parser.cc"
    break;

  case 305: // extended_info_checks: "extended-info-checks" $@50 ":" "constant string"
#line 1246 "dhcp6_parser.yy"
               {

    if ( (string(yystack_[0].value.as < std::string > ()) == "none") ||
         (string(yystack_[0].value.as < std::string > ()) == "fix") ||
         (string(yystack_[0].value.as < std::string > ()) == "strict") ||
         (string(yystack_[0].value.as < std::string > ()) == "pedantic")) {
        ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
        ctx.stack_.back()->set("extended-info-checks", user);
        ctx.leave();
    } else {
        error(yystack_[0].location, "Unsupported 'extended-info-checks value: " + string(yystack_[0].value.as < std::string > ()) +
              ", supported values are: none, fix, strict, pedantic");
    }
}
#line 2310 "dhcp6_parser.cc"
    break;

  case 306: // $@51: %empty
#line 1261 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2322 "dhcp6_parser.cc"
    break;

  case 307: // mac_sources: "mac-sources" $@51 ":" "[" mac_sources_list "]"
#line 1267 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2331 "dhcp6_parser.cc"
    break;

  case 310: // mac_sources_list: mac_sources_list ","
#line 1274 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2339 "dhcp6_parser.cc"
    break;

  case 313: // duid_id: "duid"
#line 1283 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2348 "dhcp6_parser.cc"
    break;

  case 314: // string_id: "constant string"
#line 1288 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2357 "dhcp6_parser.cc"
    break;

  case 315: // $@52: %empty
#line 1293 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2369 "dhcp6_parser.cc"
    break;

  case 316: // host_reservation_identifiers: "host-reservation-identifiers" $@52 ":" "[" host_reservation_identifiers_list "]"
#line 1299 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2378 "dhcp6_parser.cc"
    break;

  case 319: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1306 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2386 "dhcp6_parser.cc"
    break;

  case 323: // hw_address_id: "hw-address"
#line 1316 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2395 "dhcp6_parser.cc"
    break;

  case 324: // flex_id: "flex-id"
#line 1321 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2404 "dhcp6_parser.cc"
    break;

  case 325: // $@53: %empty
#line 1328 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2416 "dhcp6_parser.cc"
    break;

  case 326: // relay_supplied_options: "relay-supplied-options" $@53 ":" "[" list_content "]"
#line 1334 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2425 "dhcp6_parser.cc"
    break;

  case 327: // $@54: %empty
#line 1341 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2437 "dhcp6_parser.cc"
    break;

  case 328: // dhcp_multi_threading: "multi-threading" $@54 ":" "{" multi_threading_params "}"
#line 1347 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2448 "dhcp6_parser.cc"
    break;

  case 331: // multi_threading_params: multi_threading_params ","
#line 1356 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2456 "dhcp6_parser.cc"
    break;

  case 338: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1369 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2466 "dhcp6_parser.cc"
    break;

  case 339: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1375 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2476 "dhcp6_parser.cc"
    break;

  case 340: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1381 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2486 "dhcp6_parser.cc"
    break;

  case 341: // $@55: %empty
#line 1387 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2498 "dhcp6_parser.cc"
    break;

  case 342: // hooks_libraries: "hooks-libraries" $@55 ":" "[" hooks_libraries_list "]"
#line 1393 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2507 "dhcp6_parser.cc"
    break;

  case 347: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1404 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2515 "dhcp6_parser.cc"
    break;

  case 348: // $@56: %empty
#line 1409 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2525 "dhcp6_parser.cc"
    break;

  case 349: // hooks_library: "{" $@56 hooks_params "}"
#line 1413 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2535 "dhcp6_parser.cc"
    break;

  case 350: // $@57: %empty
#line 1419 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2545 "dhcp6_parser.cc"
    break;

  case 351: // sub_hooks_library: "{" $@57 hooks_params "}"
#line 1423 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2555 "dhcp6_parser.cc"
    break;

  case 354: // hooks_params: hooks_params ","
#line 1431 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2563 "dhcp6_parser.cc"
    break;

  case 358: // $@58: %empty
#line 1441 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2572 "dhcp6_parser.cc"
    break;

  case 359: // library: "library" $@58 ":" "constant string"
#line 1444 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2582 "dhcp6_parser.cc"
    break;

  case 360: // $@59: %empty
#line 1450 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2591 "dhcp6_parser.cc"
    break;

  case 361: // parameters: "parameters" $@59 ":" map_value
#line 1453 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2600 "dhcp6_parser.cc"
    break;

  case 362: // $@60: %empty
#line 1459 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2612 "dhcp6_parser.cc"
    break;

  case 363: // expired_leases_processing: "expired-leases-processing" $@60 ":" "{" expired_leases_params "}"
#line 1465 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2622 "dhcp6_parser.cc"
    break;

  case 366: // expired_leases_params: expired_leases_params ","
#line 1473 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2630 "dhcp6_parser.cc"
    break;

  case 373: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1486 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2640 "dhcp6_parser.cc"
    break;

  case 374: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1492 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2650 "dhcp6_parser.cc"
    break;

  case 375: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1498 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2660 "dhcp6_parser.cc"
    break;

  case 376: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1504 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2670 "dhcp6_parser.cc"
    break;

  case 377: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1510 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2680 "dhcp6_parser.cc"
    break;

  case 378: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1516 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2690 "dhcp6_parser.cc"
    break;

  case 379: // $@61: %empty
#line 1525 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2702 "dhcp6_parser.cc"
    break;

  case 380: // subnet6_list: "subnet6" $@61 ":" "[" subnet6_list_content "]"
#line 1531 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2711 "dhcp6_parser.cc"
    break;

  case 385: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1545 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2719 "dhcp6_parser.cc"
    break;

  case 386: // $@62: %empty
#line 1554 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2729 "dhcp6_parser.cc"
    break;

  case 387: // subnet6: "{" $@62 subnet6_params "}"
#line 1558 "dhcp6_parser.yy"
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
#line 2755 "dhcp6_parser.cc"
    break;

  case 388: // $@63: %empty
#line 1580 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2765 "dhcp6_parser.cc"
    break;

  case 389: // sub_subnet6: "{" $@63 subnet6_params "}"
#line 1584 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2775 "dhcp6_parser.cc"
    break;

  case 392: // subnet6_params: subnet6_params ","
#line 1593 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2783 "dhcp6_parser.cc"
    break;

  case 440: // $@64: %empty
#line 1648 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2792 "dhcp6_parser.cc"
    break;

  case 441: // subnet: "subnet" $@64 ":" "constant string"
#line 1651 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2802 "dhcp6_parser.cc"
    break;

  case 442: // $@65: %empty
#line 1657 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2811 "dhcp6_parser.cc"
    break;

  case 443: // interface: "interface" $@65 ":" "constant string"
#line 1660 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2821 "dhcp6_parser.cc"
    break;

  case 444: // $@66: %empty
#line 1666 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2830 "dhcp6_parser.cc"
    break;

  case 445: // interface_id: "interface-id" $@66 ":" "constant string"
#line 1669 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2840 "dhcp6_parser.cc"
    break;

  case 446: // $@67: %empty
#line 1675 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2849 "dhcp6_parser.cc"
    break;

  case 447: // client_class: "client-class" $@67 ":" "constant string"
#line 1678 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2859 "dhcp6_parser.cc"
    break;

  case 448: // $@68: %empty
#line 1684 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2871 "dhcp6_parser.cc"
    break;

  case 449: // require_client_classes: "require-client-classes" $@68 ":" list_strings
#line 1690 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2880 "dhcp6_parser.cc"
    break;

  case 450: // reservations_global: "reservations-global" ":" "boolean"
#line 1695 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2890 "dhcp6_parser.cc"
    break;

  case 451: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1701 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2900 "dhcp6_parser.cc"
    break;

  case 452: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1707 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2910 "dhcp6_parser.cc"
    break;

  case 453: // $@69: %empty
#line 1713 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2919 "dhcp6_parser.cc"
    break;

  case 454: // reservation_mode: "reservation-mode" $@69 ":" hr_mode
#line 1716 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2928 "dhcp6_parser.cc"
    break;

  case 455: // hr_mode: "disabled"
#line 1721 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2934 "dhcp6_parser.cc"
    break;

  case 456: // hr_mode: "out-of-pool"
#line 1722 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2940 "dhcp6_parser.cc"
    break;

  case 457: // hr_mode: "global"
#line 1723 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2946 "dhcp6_parser.cc"
    break;

  case 458: // hr_mode: "all"
#line 1724 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2952 "dhcp6_parser.cc"
    break;

  case 459: // id: "id" ":" "integer"
#line 1727 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2962 "dhcp6_parser.cc"
    break;

  case 460: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1733 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2972 "dhcp6_parser.cc"
    break;

  case 461: // $@70: %empty
#line 1741 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2984 "dhcp6_parser.cc"
    break;

  case 462: // shared_networks: "shared-networks" $@70 ":" "[" shared_networks_content "]"
#line 1747 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2993 "dhcp6_parser.cc"
    break;

  case 467: // shared_networks_list: shared_networks_list ","
#line 1760 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3001 "dhcp6_parser.cc"
    break;

  case 468: // $@71: %empty
#line 1765 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3011 "dhcp6_parser.cc"
    break;

  case 469: // shared_network: "{" $@71 shared_network_params "}"
#line 1769 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3019 "dhcp6_parser.cc"
    break;

  case 472: // shared_network_params: shared_network_params ","
#line 1775 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3027 "dhcp6_parser.cc"
    break;

  case 517: // $@72: %empty
#line 1830 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3039 "dhcp6_parser.cc"
    break;

  case 518: // option_def_list: "option-def" $@72 ":" "[" option_def_list_content "]"
#line 1836 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3048 "dhcp6_parser.cc"
    break;

  case 519: // $@73: %empty
#line 1844 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3057 "dhcp6_parser.cc"
    break;

  case 520: // sub_option_def_list: "{" $@73 option_def_list "}"
#line 1847 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 3065 "dhcp6_parser.cc"
    break;

  case 525: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1859 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3073 "dhcp6_parser.cc"
    break;

  case 526: // $@74: %empty
#line 1866 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3083 "dhcp6_parser.cc"
    break;

  case 527: // option_def_entry: "{" $@74 option_def_params "}"
#line 1870 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3095 "dhcp6_parser.cc"
    break;

  case 528: // $@75: %empty
#line 1881 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3105 "dhcp6_parser.cc"
    break;

  case 529: // sub_option_def: "{" $@75 option_def_params "}"
#line 1885 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3117 "dhcp6_parser.cc"
    break;

  case 534: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1901 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3125 "dhcp6_parser.cc"
    break;

  case 546: // code: "code" ":" "integer"
#line 1920 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3135 "dhcp6_parser.cc"
    break;

  case 548: // $@76: %empty
#line 1928 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3144 "dhcp6_parser.cc"
    break;

  case 549: // option_def_type: "type" $@76 ":" "constant string"
#line 1931 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3154 "dhcp6_parser.cc"
    break;

  case 550: // $@77: %empty
#line 1937 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3163 "dhcp6_parser.cc"
    break;

  case 551: // option_def_record_types: "record-types" $@77 ":" "constant string"
#line 1940 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3173 "dhcp6_parser.cc"
    break;

  case 552: // $@78: %empty
#line 1946 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3182 "dhcp6_parser.cc"
    break;

  case 553: // space: "space" $@78 ":" "constant string"
#line 1949 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3192 "dhcp6_parser.cc"
    break;

  case 555: // $@79: %empty
#line 1957 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3201 "dhcp6_parser.cc"
    break;

  case 556: // option_def_encapsulate: "encapsulate" $@79 ":" "constant string"
#line 1960 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3211 "dhcp6_parser.cc"
    break;

  case 557: // option_def_array: "array" ":" "boolean"
#line 1966 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3221 "dhcp6_parser.cc"
    break;

  case 558: // $@80: %empty
#line 1976 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3233 "dhcp6_parser.cc"
    break;

  case 559: // option_data_list: "option-data" $@80 ":" "[" option_data_list_content "]"
#line 1982 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3242 "dhcp6_parser.cc"
    break;

  case 564: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1997 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3250 "dhcp6_parser.cc"
    break;

  case 565: // $@81: %empty
#line 2004 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3260 "dhcp6_parser.cc"
    break;

  case 566: // option_data_entry: "{" $@81 option_data_params "}"
#line 2008 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3269 "dhcp6_parser.cc"
    break;

  case 567: // $@82: %empty
#line 2016 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3279 "dhcp6_parser.cc"
    break;

  case 568: // sub_option_data: "{" $@82 option_data_params "}"
#line 2020 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3288 "dhcp6_parser.cc"
    break;

  case 573: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2036 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3296 "dhcp6_parser.cc"
    break;

  case 585: // $@83: %empty
#line 2057 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3305 "dhcp6_parser.cc"
    break;

  case 586: // option_data_data: "data" $@83 ":" "constant string"
#line 2060 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3315 "dhcp6_parser.cc"
    break;

  case 589: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2070 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3325 "dhcp6_parser.cc"
    break;

  case 590: // option_data_always_send: "always-send" ":" "boolean"
#line 2076 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3335 "dhcp6_parser.cc"
    break;

  case 591: // option_data_never_send: "never-send" ":" "boolean"
#line 2082 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3345 "dhcp6_parser.cc"
    break;

  case 592: // $@84: %empty
#line 2091 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3357 "dhcp6_parser.cc"
    break;

  case 593: // pools_list: "pools" $@84 ":" "[" pools_list_content "]"
#line 2097 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3366 "dhcp6_parser.cc"
    break;

  case 598: // not_empty_pools_list: not_empty_pools_list ","
#line 2110 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3374 "dhcp6_parser.cc"
    break;

  case 599: // $@85: %empty
#line 2115 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3384 "dhcp6_parser.cc"
    break;

  case 600: // pool_list_entry: "{" $@85 pool_params "}"
#line 2119 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3394 "dhcp6_parser.cc"
    break;

  case 601: // $@86: %empty
#line 2125 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3404 "dhcp6_parser.cc"
    break;

  case 602: // sub_pool6: "{" $@86 pool_params "}"
#line 2129 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3414 "dhcp6_parser.cc"
    break;

  case 605: // pool_params: pool_params ","
#line 2137 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3422 "dhcp6_parser.cc"
    break;

  case 614: // $@87: %empty
#line 2152 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3431 "dhcp6_parser.cc"
    break;

  case 615: // pool_entry: "pool" $@87 ":" "constant string"
#line 2155 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3441 "dhcp6_parser.cc"
    break;

  case 616: // pool_id: "pool-id" ":" "integer"
#line 2161 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3451 "dhcp6_parser.cc"
    break;

  case 617: // $@88: %empty
#line 2167 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3459 "dhcp6_parser.cc"
    break;

  case 618: // user_context: "user-context" $@88 ":" map_value
#line 2169 "dhcp6_parser.yy"
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
#line 3486 "dhcp6_parser.cc"
    break;

  case 619: // $@89: %empty
#line 2192 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3494 "dhcp6_parser.cc"
    break;

  case 620: // comment: "comment" $@89 ":" "constant string"
#line 2194 "dhcp6_parser.yy"
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
#line 3523 "dhcp6_parser.cc"
    break;

  case 621: // $@90: %empty
#line 2222 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3535 "dhcp6_parser.cc"
    break;

  case 622: // pd_pools_list: "pd-pools" $@90 ":" "[" pd_pools_list_content "]"
#line 2228 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3544 "dhcp6_parser.cc"
    break;

  case 627: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2241 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3552 "dhcp6_parser.cc"
    break;

  case 628: // $@91: %empty
#line 2246 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3562 "dhcp6_parser.cc"
    break;

  case 629: // pd_pool_entry: "{" $@91 pd_pool_params "}"
#line 2250 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3574 "dhcp6_parser.cc"
    break;

  case 630: // $@92: %empty
#line 2258 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3584 "dhcp6_parser.cc"
    break;

  case 631: // sub_pd_pool: "{" $@92 pd_pool_params "}"
#line 2262 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3596 "dhcp6_parser.cc"
    break;

  case 634: // pd_pool_params: pd_pool_params ","
#line 2272 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3604 "dhcp6_parser.cc"
    break;

  case 646: // $@93: %empty
#line 2290 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3613 "dhcp6_parser.cc"
    break;

  case 647: // pd_prefix: "prefix" $@93 ":" "constant string"
#line 2293 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3623 "dhcp6_parser.cc"
    break;

  case 648: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2299 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3633 "dhcp6_parser.cc"
    break;

  case 649: // $@94: %empty
#line 2305 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3642 "dhcp6_parser.cc"
    break;

  case 650: // excluded_prefix: "excluded-prefix" $@94 ":" "constant string"
#line 2308 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3652 "dhcp6_parser.cc"
    break;

  case 651: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2314 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3662 "dhcp6_parser.cc"
    break;

  case 652: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2320 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3672 "dhcp6_parser.cc"
    break;

  case 653: // $@95: %empty
#line 2329 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3684 "dhcp6_parser.cc"
    break;

  case 654: // reservations: "reservations" $@95 ":" "[" reservations_list "]"
#line 2335 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3693 "dhcp6_parser.cc"
    break;

  case 659: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2346 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3701 "dhcp6_parser.cc"
    break;

  case 660: // $@96: %empty
#line 2351 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3711 "dhcp6_parser.cc"
    break;

  case 661: // reservation: "{" $@96 reservation_params "}"
#line 2355 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3720 "dhcp6_parser.cc"
    break;

  case 662: // $@97: %empty
#line 2360 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3730 "dhcp6_parser.cc"
    break;

  case 663: // sub_reservation: "{" $@97 reservation_params "}"
#line 2364 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3739 "dhcp6_parser.cc"
    break;

  case 668: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2375 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3747 "dhcp6_parser.cc"
    break;

  case 680: // $@98: %empty
#line 2394 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3759 "dhcp6_parser.cc"
    break;

  case 681: // ip_addresses: "ip-addresses" $@98 ":" list_strings
#line 2400 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3768 "dhcp6_parser.cc"
    break;

  case 682: // $@99: %empty
#line 2405 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3780 "dhcp6_parser.cc"
    break;

  case 683: // prefixes: "prefixes" $@99 ":" list_strings
#line 2411 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3789 "dhcp6_parser.cc"
    break;

  case 684: // $@100: %empty
#line 2416 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3798 "dhcp6_parser.cc"
    break;

  case 685: // duid: "duid" $@100 ":" "constant string"
#line 2419 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3808 "dhcp6_parser.cc"
    break;

  case 686: // $@101: %empty
#line 2425 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3817 "dhcp6_parser.cc"
    break;

  case 687: // hw_address: "hw-address" $@101 ":" "constant string"
#line 2428 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3827 "dhcp6_parser.cc"
    break;

  case 688: // $@102: %empty
#line 2434 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3836 "dhcp6_parser.cc"
    break;

  case 689: // hostname: "hostname" $@102 ":" "constant string"
#line 2437 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3846 "dhcp6_parser.cc"
    break;

  case 690: // $@103: %empty
#line 2443 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3855 "dhcp6_parser.cc"
    break;

  case 691: // flex_id_value: "flex-id" $@103 ":" "constant string"
#line 2446 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3865 "dhcp6_parser.cc"
    break;

  case 692: // $@104: %empty
#line 2452 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3877 "dhcp6_parser.cc"
    break;

  case 693: // reservation_client_classes: "client-classes" $@104 ":" list_strings
#line 2458 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3886 "dhcp6_parser.cc"
    break;

  case 694: // $@105: %empty
#line 2466 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3898 "dhcp6_parser.cc"
    break;

  case 695: // relay: "relay" $@105 ":" "{" relay_map "}"
#line 2472 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3907 "dhcp6_parser.cc"
    break;

  case 697: // $@106: %empty
#line 2483 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3919 "dhcp6_parser.cc"
    break;

  case 698: // client_classes: "client-classes" $@106 ":" "[" client_classes_list "]"
#line 2489 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3928 "dhcp6_parser.cc"
    break;

  case 701: // client_classes_list: client_classes_list ","
#line 2496 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3936 "dhcp6_parser.cc"
    break;

  case 702: // $@107: %empty
#line 2501 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3946 "dhcp6_parser.cc"
    break;

  case 703: // client_class_entry: "{" $@107 client_class_params "}"
#line 2505 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3956 "dhcp6_parser.cc"
    break;

  case 708: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2517 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3964 "dhcp6_parser.cc"
    break;

  case 724: // $@108: %empty
#line 2540 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3973 "dhcp6_parser.cc"
    break;

  case 725: // client_class_test: "test" $@108 ":" "constant string"
#line 2543 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3983 "dhcp6_parser.cc"
    break;

  case 726: // $@109: %empty
#line 2549 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3992 "dhcp6_parser.cc"
    break;

  case 727: // client_class_template_test: "template-test" $@109 ":" "constant string"
#line 2552 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4002 "dhcp6_parser.cc"
    break;

  case 728: // only_if_required: "only-if-required" ":" "boolean"
#line 2558 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4012 "dhcp6_parser.cc"
    break;

  case 729: // $@110: %empty
#line 2567 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 4024 "dhcp6_parser.cc"
    break;

  case 730: // server_id: "server-id" $@110 ":" "{" server_id_params "}"
#line 2573 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4035 "dhcp6_parser.cc"
    break;

  case 733: // server_id_params: server_id_params ","
#line 2582 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4043 "dhcp6_parser.cc"
    break;

  case 743: // $@111: %empty
#line 2598 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 4052 "dhcp6_parser.cc"
    break;

  case 744: // server_id_type: "type" $@111 ":" duid_type
#line 2601 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4061 "dhcp6_parser.cc"
    break;

  case 745: // duid_type: "LLT"
#line 2606 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4067 "dhcp6_parser.cc"
    break;

  case 746: // duid_type: "EN"
#line 2607 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4073 "dhcp6_parser.cc"
    break;

  case 747: // duid_type: "LL"
#line 2608 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4079 "dhcp6_parser.cc"
    break;

  case 748: // htype: "htype" ":" "integer"
#line 2611 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4089 "dhcp6_parser.cc"
    break;

  case 749: // $@112: %empty
#line 2617 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4098 "dhcp6_parser.cc"
    break;

  case 750: // identifier: "identifier" $@112 ":" "constant string"
#line 2620 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4108 "dhcp6_parser.cc"
    break;

  case 751: // time: "time" ":" "integer"
#line 2626 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4118 "dhcp6_parser.cc"
    break;

  case 752: // enterprise_id: "enterprise-id" ":" "integer"
#line 2632 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4128 "dhcp6_parser.cc"
    break;

  case 753: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2640 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4138 "dhcp6_parser.cc"
    break;

  case 754: // $@113: %empty
#line 2648 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4150 "dhcp6_parser.cc"
    break;

  case 755: // control_socket: "control-socket" $@113 ":" "{" control_socket_params "}"
#line 2654 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4159 "dhcp6_parser.cc"
    break;

  case 758: // control_socket_params: control_socket_params ","
#line 2661 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4167 "dhcp6_parser.cc"
    break;

  case 764: // $@114: %empty
#line 2673 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4176 "dhcp6_parser.cc"
    break;

  case 765: // socket_type: "socket-type" $@114 ":" "constant string"
#line 2676 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 4186 "dhcp6_parser.cc"
    break;

  case 766: // $@115: %empty
#line 2682 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4195 "dhcp6_parser.cc"
    break;

  case 767: // socket_name: "socket-name" $@115 ":" "constant string"
#line 2685 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4205 "dhcp6_parser.cc"
    break;

  case 768: // $@116: %empty
#line 2694 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4217 "dhcp6_parser.cc"
    break;

  case 769: // dhcp_queue_control: "dhcp-queue-control" $@116 ":" "{" queue_control_params "}"
#line 2700 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4228 "dhcp6_parser.cc"
    break;

  case 772: // queue_control_params: queue_control_params ","
#line 2709 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4236 "dhcp6_parser.cc"
    break;

  case 779: // enable_queue: "enable-queue" ":" "boolean"
#line 2722 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4246 "dhcp6_parser.cc"
    break;

  case 780: // $@117: %empty
#line 2728 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4255 "dhcp6_parser.cc"
    break;

  case 781: // queue_type: "queue-type" $@117 ":" "constant string"
#line 2731 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4265 "dhcp6_parser.cc"
    break;

  case 782: // capacity: "capacity" ":" "integer"
#line 2737 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4275 "dhcp6_parser.cc"
    break;

  case 783: // $@118: %empty
#line 2743 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4284 "dhcp6_parser.cc"
    break;

  case 784: // arbitrary_map_entry: "constant string" $@118 ":" value
#line 2746 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4293 "dhcp6_parser.cc"
    break;

  case 785: // $@119: %empty
#line 2753 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4305 "dhcp6_parser.cc"
    break;

  case 786: // dhcp_ddns: "dhcp-ddns" $@119 ":" "{" dhcp_ddns_params "}"
#line 2759 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4316 "dhcp6_parser.cc"
    break;

  case 787: // $@120: %empty
#line 2766 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4326 "dhcp6_parser.cc"
    break;

  case 788: // sub_dhcp_ddns: "{" $@120 dhcp_ddns_params "}"
#line 2770 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4336 "dhcp6_parser.cc"
    break;

  case 791: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2778 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4344 "dhcp6_parser.cc"
    break;

  case 803: // enable_updates: "enable-updates" ":" "boolean"
#line 2796 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4354 "dhcp6_parser.cc"
    break;

  case 804: // $@121: %empty
#line 2802 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4363 "dhcp6_parser.cc"
    break;

  case 805: // server_ip: "server-ip" $@121 ":" "constant string"
#line 2805 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4373 "dhcp6_parser.cc"
    break;

  case 806: // server_port: "server-port" ":" "integer"
#line 2811 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4383 "dhcp6_parser.cc"
    break;

  case 807: // $@122: %empty
#line 2817 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4392 "dhcp6_parser.cc"
    break;

  case 808: // sender_ip: "sender-ip" $@122 ":" "constant string"
#line 2820 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4402 "dhcp6_parser.cc"
    break;

  case 809: // sender_port: "sender-port" ":" "integer"
#line 2826 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4412 "dhcp6_parser.cc"
    break;

  case 810: // max_queue_size: "max-queue-size" ":" "integer"
#line 2832 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4422 "dhcp6_parser.cc"
    break;

  case 811: // $@123: %empty
#line 2838 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4431 "dhcp6_parser.cc"
    break;

  case 812: // ncr_protocol: "ncr-protocol" $@123 ":" ncr_protocol_value
#line 2841 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4440 "dhcp6_parser.cc"
    break;

  case 813: // ncr_protocol_value: "UDP"
#line 2847 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4446 "dhcp6_parser.cc"
    break;

  case 814: // ncr_protocol_value: "TCP"
#line 2848 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4452 "dhcp6_parser.cc"
    break;

  case 815: // $@124: %empty
#line 2851 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4461 "dhcp6_parser.cc"
    break;

  case 816: // ncr_format: "ncr-format" $@124 ":" "JSON"
#line 2854 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4471 "dhcp6_parser.cc"
    break;

  case 817: // $@125: %empty
#line 2862 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4483 "dhcp6_parser.cc"
    break;

  case 818: // config_control: "config-control" $@125 ":" "{" config_control_params "}"
#line 2868 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4493 "dhcp6_parser.cc"
    break;

  case 819: // $@126: %empty
#line 2874 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4503 "dhcp6_parser.cc"
    break;

  case 820: // sub_config_control: "{" $@126 config_control_params "}"
#line 2878 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4512 "dhcp6_parser.cc"
    break;

  case 823: // config_control_params: config_control_params ","
#line 2886 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4520 "dhcp6_parser.cc"
    break;

  case 826: // $@127: %empty
#line 2896 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4532 "dhcp6_parser.cc"
    break;

  case 827: // config_databases: "config-databases" $@127 ":" "[" database_list "]"
#line 2902 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4541 "dhcp6_parser.cc"
    break;

  case 828: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2907 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4551 "dhcp6_parser.cc"
    break;

  case 829: // $@128: %empty
#line 2915 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4563 "dhcp6_parser.cc"
    break;

  case 830: // loggers: "loggers" $@128 ":" "[" loggers_entries "]"
#line 2921 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4572 "dhcp6_parser.cc"
    break;

  case 833: // loggers_entries: loggers_entries ","
#line 2930 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4580 "dhcp6_parser.cc"
    break;

  case 834: // $@129: %empty
#line 2936 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4590 "dhcp6_parser.cc"
    break;

  case 835: // logger_entry: "{" $@129 logger_params "}"
#line 2940 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4598 "dhcp6_parser.cc"
    break;

  case 838: // logger_params: logger_params ","
#line 2946 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4606 "dhcp6_parser.cc"
    break;

  case 846: // debuglevel: "debuglevel" ":" "integer"
#line 2960 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4616 "dhcp6_parser.cc"
    break;

  case 847: // $@130: %empty
#line 2966 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4625 "dhcp6_parser.cc"
    break;

  case 848: // severity: "severity" $@130 ":" "constant string"
#line 2969 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4635 "dhcp6_parser.cc"
    break;

  case 849: // $@131: %empty
#line 2975 "dhcp6_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4647 "dhcp6_parser.cc"
    break;

  case 850: // output_options_list: "output-options" $@131 ":" "[" output_options_list_content "]"
#line 2981 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4656 "dhcp6_parser.cc"
    break;

  case 853: // output_options_list_content: output_options_list_content ","
#line 2988 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4664 "dhcp6_parser.cc"
    break;

  case 854: // $@132: %empty
#line 2993 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4674 "dhcp6_parser.cc"
    break;

  case 855: // output_entry: "{" $@132 output_params_list "}"
#line 2997 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4682 "dhcp6_parser.cc"
    break;

  case 858: // output_params_list: output_params_list ","
#line 3003 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4690 "dhcp6_parser.cc"
    break;

  case 864: // $@133: %empty
#line 3015 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4699 "dhcp6_parser.cc"
    break;

  case 865: // output: "output" $@133 ":" "constant string"
#line 3018 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4709 "dhcp6_parser.cc"
    break;

  case 866: // flush: "flush" ":" "boolean"
#line 3024 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4719 "dhcp6_parser.cc"
    break;

  case 867: // maxsize: "maxsize" ":" "integer"
#line 3030 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4729 "dhcp6_parser.cc"
    break;

  case 868: // maxver: "maxver" ":" "integer"
#line 3036 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4739 "dhcp6_parser.cc"
    break;

  case 869: // $@134: %empty
#line 3042 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4748 "dhcp6_parser.cc"
    break;

  case 870: // pattern: "pattern" $@134 ":" "constant string"
#line 3045 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4758 "dhcp6_parser.cc"
    break;

  case 871: // $@135: %empty
#line 3051 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4770 "dhcp6_parser.cc"
    break;

  case 872: // compatibility: "compatibility" $@135 ":" "{" compatibility_params "}"
#line 3057 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4779 "dhcp6_parser.cc"
    break;

  case 875: // compatibility_params: compatibility_params ","
#line 3064 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4787 "dhcp6_parser.cc"
    break;

  case 878: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3073 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4797 "dhcp6_parser.cc"
    break;


#line 4801 "dhcp6_parser.cc"

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
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
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
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
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
    {
      stack_symbol_type error_token;

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
    YY_STACK_PRINT ();
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

  std::string
  Dhcp6Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Dhcp6Parser::context.
  Dhcp6Parser::context::context (const Dhcp6Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Dhcp6Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  Dhcp6Parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
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

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  Dhcp6Parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

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
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short Dhcp6Parser::yypact_ninf_ = -1010;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     473, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010,    36,    34,    35,    70,   108,
     123,   127,   141,   151,   178,   180,   200,   245,   246,   254,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,    34,  -136,
     140,   171,   102,   676,   201,   293,   239,   142,   107,   331,
     -94,   458,    87, -1010,   278,   285,   294,   297,   317, -1010,
      58, -1010, -1010, -1010, -1010, -1010, -1010, -1010,   342,   355,
     356,   367,   386,   401,   405,   420,   421,   426,   442,   443,
     451,   453, -1010,   454,   457,   459,   461,   462, -1010, -1010,
   -1010,   463,   464,   465,   468, -1010, -1010, -1010,   469, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010,   471,   472,   475, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,   476, -1010,
   -1010, -1010, -1010, -1010, -1010,   478,   479,   480, -1010, -1010,
     483, -1010,    60, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010,   485,   486,   489,   490, -1010,    71, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010,   492,   494, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010,    77, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010,   495, -1010, -1010,
   -1010, -1010,    78, -1010, -1010, -1010, -1010, -1010, -1010,   496,
   -1010,   497,   500, -1010, -1010, -1010, -1010, -1010, -1010,    86,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010,   332,   417, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010,   362, -1010, -1010,
     502, -1010, -1010, -1010,   504, -1010, -1010,   501,   474, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010,   508,   513,   514, -1010, -1010, -1010, -1010,   515,
     522, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010,    96, -1010, -1010, -1010,   525, -1010,
     526, -1010,   527,   529, -1010, -1010, -1010, -1010, -1010,   106,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
     530,   124, -1010, -1010, -1010, -1010,    34,    34, -1010,   315,
     533, -1010, -1010,   534,   536,   538,   539,   540,   543,   334,
     337,   341,   348,   349,   350,   351,   358,   327,   330,   335,
     354,   363,   365,   549,   368,   369,   360,   373,   375,   550,
     573,   581,   378,   379,   370,   380,   584,   587,   600,   385,
     604,   605,   609,   610,   611,   612,   614,   396,   397,   398,
     618,   619,   621,   622,   623,   624,   625,   626,   627,   411,
     637,   638,   639,   640,   641,   642,   424,   425,   427,   645,
     647, -1010,   171, -1010,   649,   431,   433,   436,   437,   102,
   -1010,   655,   656,   657,   658,   659,   444,   441,   662,   663,
     664,   676, -1010,   666,   452,   201, -1010,   667,   455,   668,
     456,   477,   293, -1010,   670,   671,   689,   690,   696,   697,
     698, -1010,   239, -1010,   700,   701,   487,   702,   703,   710,
     493, -1010,   107,   711,   498,   499,   503, -1010,   331,   714,
     715,   -38, -1010,   517,   716,   520,   720,   521,   537,   721,
     739,   458, -1010,   750,   541,    87, -1010, -1010, -1010,   751,
     752,   551,   753,   754,   765,   766,   769, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010,   555, -1010, -1010, -1010, -1010, -1010,  -141,   557,   559,
   -1010, -1010, -1010, -1010,   775,   776,   777, -1010,   563,   572,
     347,   788,   787,   575,   333, -1010, -1010, -1010,   794,   795,
     796,   797,   798,   800,   802,   801,   804, -1010,   806,   807,
     808,   809,   582,   589, -1010, -1010, -1010,   812,   811, -1010,
     815, -1010, -1010, -1010, -1010, -1010,   816,   817,   603,   606,
     607, -1010, -1010,   815,   608,   818, -1010,   643, -1010, -1010,
     644, -1010,   648, -1010, -1010, -1010,   815,   815,   815,   650,
     654,   660,   661, -1010,   665,   669, -1010,   672,   675,   677,
   -1010, -1010,   678, -1010, -1010, -1010, -1010,   682,   787, -1010,
   -1010,   683, -1010,   684, -1010, -1010,    22,   673, -1010,   819,
   -1010, -1010,    34,   171, -1010,    87,   102,   131,   131,   822,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,   836,
     837,   838, -1010, -1010, -1010, -1010, -1010, -1010, -1010,   839,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,   -95,    34,
     210,   185,   854,   855,   858,   236,   234,   110,    91,   -76,
     458, -1010, -1010,   862,  -155, -1010, -1010,   868,   869, -1010,
   -1010, -1010, -1010, -1010,   620, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,   822,
   -1010,   125,   135,   137, -1010, -1010, -1010, -1010,   873,   874,
     875,   878,   879,   880,   882,   901,   902,   903, -1010,   904,
     906, -1010, -1010, -1010, -1010, -1010,   143, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
     181, -1010,   905,   909, -1010, -1010,   908,   912, -1010, -1010,
     910,   914, -1010, -1010,   913,   915, -1010, -1010,   917,   918,
   -1010, -1010, -1010,    61, -1010, -1010, -1010,   919, -1010, -1010,
   -1010,   214, -1010, -1010, -1010, -1010, -1010,   205, -1010, -1010,
   -1010, -1010,   416, -1010, -1010,   920,   921, -1010, -1010,   922,
     924, -1010,   916,   925,   926,   927,   928,   929,   206, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,   930,   931,
     932, -1010, -1010, -1010, -1010,   269, -1010, -1010, -1010, -1010,
   -1010, -1010,   933,   934,   935, -1010,   275, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,   279, -1010,
   -1010, -1010,   936, -1010,   937, -1010, -1010, -1010,   282, -1010,
   -1010, -1010, -1010, -1010,   296, -1010,   423, -1010,   938, -1010,
     298, -1010, -1010,   723, -1010,   939,   941, -1010, -1010,   940,
     944, -1010, -1010,   942,   943, -1010, -1010, -1010,   947,   948,
     949,   951,   727,   733,   737,   736,   740,   741,   746,   755,
     758,   762,   968,   761,   767,   990,   992,   994,   996,   131,
   -1010, -1010,   131, -1010,   822,   676, -1010,   836,   107, -1010,
     837,   331, -1010,   838,   779, -1010,   839,   -95, -1010, -1010,
     210, -1010,  1000,  1008,   185, -1010,   302,   854, -1010,   239,
   -1010,   855,   -94, -1010,   858,   792,   813,   826,   831,   832,
     852,   236, -1010,  1017,  1028,   865,   886,   888,   234, -1010,
     814,   890,   891,   110, -1010,  1032,  1113,    91, -1010,   895,
    1115,   899,  1117,   -76, -1010, -1010,   208,   862, -1010,   900,
    -155, -1010, -1010,  1116,  1121,   201, -1010,   868,   293, -1010,
     869, -1010, -1010,   148,   907,   911,   923, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010,    49, -1010, -1010,
     945,   946,   950,   952, -1010,   318, -1010,   320, -1010,  1118,
   -1010,  1120, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010,   321, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010,   953,   954, -1010, -1010, -1010,  1125, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,  1122,
    1129, -1010, -1010, -1010, -1010, -1010, -1010,  1126, -1010,   329,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,   281,   955,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,   956,   958,
   -1010, -1010,   959, -1010,    34, -1010, -1010,  1131, -1010, -1010,
   -1010, -1010, -1010,   336, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010,   961,   364, -1010,   366, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010,   779, -1010, -1010, -1010,
    1133,  1134,   960, -1010,   302, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010,  1135,   963,  1136,   208,
   -1010, -1010, -1010, -1010, -1010,   962,   965, -1010, -1010,  1137,
   -1010,   966, -1010, -1010, -1010,  1138, -1010, -1010,   450, -1010,
       1,  1138, -1010, -1010,  1140,  1142,  1143, -1010,   400, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010,  1144,   964,   967,   969,
    1145,     1, -1010,   971, -1010, -1010, -1010,   972, -1010, -1010,
   -1010
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   199,     9,   388,    11,
     601,    13,   630,    15,   662,    17,   519,    19,   528,    21,
     567,    23,   350,    25,   787,    27,   819,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   664,     0,   530,   569,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   141,   817,   197,   218,   220,   222,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   187,     0,     0,     0,     0,     0,   160,   167,
     169,     0,     0,     0,     0,   379,   517,   558,     0,   190,
     192,   173,   461,   617,   619,   453,     0,     0,     0,   306,
     325,   315,   295,   697,   653,   341,   362,   729,     0,   327,
     754,   768,   785,   180,   182,     0,     0,     0,   829,   871,
       0,   140,     0,    69,    72,    73,    74,    75,    76,    77,
      78,    79,    80,   111,   112,   113,   114,   115,    81,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   117,
     118,   129,   130,   131,   106,   137,   138,   139,   133,   134,
     135,    84,    85,    86,    87,   103,    88,    90,    89,   132,
      94,    95,    82,   108,   109,   110,   107,    83,    92,    93,
     101,   102,   104,    91,    96,    97,    98,    99,   100,   105,
     116,   136,   212,     0,     0,     0,     0,   211,     0,   201,
     204,   205,   206,   207,   208,   209,   210,   592,   621,   440,
     442,   444,     0,     0,   448,   446,   694,   439,   393,   394,
     395,   396,   397,   398,   399,   400,   419,   420,   421,   422,
     423,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   424,   425,   436,   437,   438,     0,   390,   404,   405,
     406,   409,   410,   413,   414,   415,   412,   407,   408,   401,
     402,   417,   418,   403,   411,   416,   614,     0,   613,   609,
     610,   608,     0,   603,   606,   607,   611,   612,   646,     0,
     649,     0,     0,   645,   639,   640,   638,   643,   644,     0,
     632,   635,   636,   641,   642,   637,   692,   680,   682,   684,
     686,   688,   690,   679,   676,   677,   678,     0,   665,   666,
     671,   672,   669,   673,   674,   675,   670,     0,   548,   269,
       0,   552,   550,   555,     0,   544,   545,     0,   531,   532,
     535,   547,   536,   537,   538,   554,   539,   540,   541,   542,
     543,   585,     0,     0,     0,   583,   584,   587,   588,     0,
     570,   571,   574,   575,   576,   577,   578,   579,   580,   581,
     582,   358,   360,   355,     0,   352,   356,   357,     0,   804,
       0,   807,     0,     0,   811,   815,   802,   800,   801,     0,
     789,   792,   793,   794,   795,   796,   797,   798,   799,   826,
       0,     0,   821,   824,   825,    47,    52,     0,    39,    45,
       0,    66,    62,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    60,    71,    68,     0,     0,     0,     0,     0,   203,
     200,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   392,   389,     0,     0,   605,   602,     0,     0,     0,
       0,     0,   634,   631,     0,     0,     0,     0,     0,     0,
       0,   663,   668,   520,     0,     0,     0,     0,     0,     0,
       0,   529,   534,     0,     0,     0,     0,   568,   573,     0,
       0,   354,   351,     0,     0,     0,     0,     0,     0,     0,
       0,   791,   788,     0,     0,   823,   820,    51,    43,     0,
       0,     0,     0,     0,     0,     0,     0,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,     0,   185,   186,   157,   158,   159,     0,     0,     0,
     171,   172,   179,   184,     0,     0,     0,   189,     0,     0,
       0,     0,     0,     0,     0,   450,   451,   452,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   753,     0,     0,
       0,     0,     0,     0,   194,   195,   196,     0,     0,    70,
       0,   214,   215,   216,   217,   202,     0,     0,     0,     0,
       0,   459,   460,     0,     0,     0,   391,     0,   616,   604,
       0,   648,     0,   651,   652,   633,     0,     0,     0,     0,
       0,     0,     0,   667,     0,     0,   546,     0,     0,     0,
     557,   533,     0,   589,   590,   591,   572,     0,     0,   353,
     803,     0,   806,     0,   809,   810,     0,     0,   790,     0,
     828,   822,     0,     0,   142,     0,     0,     0,     0,   224,
     188,   162,   163,   164,   165,   166,   161,   168,   170,   381,
     521,   560,   191,   193,   175,   176,   177,   178,   174,   463,
      40,   618,   620,   455,   456,   457,   458,   454,     0,    48,
       0,     0,     0,   655,   343,     0,     0,     0,     0,     0,
       0,   181,   183,     0,     0,    53,   213,   594,   623,   441,
     443,   445,   449,   447,     0,   615,   647,   650,   693,   681,
     683,   685,   687,   689,   691,   549,   270,   553,   551,   556,
     586,   359,   361,   805,   808,   813,   814,   812,   816,   224,
      44,     0,     0,     0,   257,   262,   264,   266,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   279,     0,
       0,   287,   289,   291,   293,   256,     0,   231,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   248,   249,   250,   251,   247,   252,   253,   254,   255,
       0,   229,     0,   225,   226,   386,     0,   382,   383,   526,
       0,   522,   523,   565,     0,   561,   562,   468,     0,   464,
     465,   313,   314,     0,   308,   311,   312,     0,   323,   324,
     320,     0,   317,   321,   322,   302,   304,     0,   297,   300,
     301,   702,     0,   699,   660,     0,   656,   657,   348,     0,
     344,   345,     0,     0,     0,     0,     0,     0,     0,   364,
     367,   368,   369,   370,   371,   372,   743,   749,     0,     0,
       0,   742,   739,   740,   741,     0,   731,   734,   737,   735,
     736,   738,     0,     0,     0,   337,     0,   329,   332,   333,
     334,   335,   336,   764,   766,   763,   761,   762,     0,   756,
     759,   760,     0,   780,     0,   783,   776,   777,     0,   770,
     773,   774,   775,   778,     0,   834,     0,   831,     0,   877,
       0,   873,   876,    55,   599,     0,   595,   596,   628,     0,
     624,   625,   696,     0,     0,    64,   818,   198,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   233,
     219,   221,     0,   223,   228,     0,   380,   385,   530,   518,
     525,   569,   559,   564,     0,   462,   467,   310,   307,   326,
     319,   316,     0,     0,   299,   296,   704,   701,   698,   664,
     654,   659,     0,   342,   347,     0,     0,     0,     0,     0,
       0,   366,   363,     0,     0,     0,     0,     0,   733,   730,
       0,     0,     0,   331,   328,     0,     0,   758,   755,     0,
       0,     0,     0,   772,   769,   786,     0,   833,   830,     0,
     875,   872,    57,     0,    56,     0,   593,   598,     0,   622,
     627,   695,   827,     0,     0,     0,     0,   268,   271,   272,
     273,   274,   275,   276,   277,   286,   278,     0,   284,   285,
       0,     0,     0,     0,   232,     0,   227,     0,   384,     0,
     524,     0,   563,   516,   487,   488,   489,   491,   492,   493,
     477,   478,   496,   497,   498,   499,   500,   503,   504,   505,
     506,   507,   508,   509,   510,   511,   512,   501,   502,   513,
     514,   515,   473,   474,   475,   476,   485,   486,   482,   483,
     484,   481,   490,     0,   470,   479,   494,   495,   480,   466,
     309,   318,     0,     0,   298,   724,   726,     0,   722,   716,
     717,   718,   719,   720,   721,   723,   713,   714,   715,     0,
     705,   706,   709,   710,   711,   712,   700,     0,   658,     0,
     346,   373,   374,   375,   376,   377,   378,   365,     0,     0,
     748,   751,   752,   732,   338,   339,   340,   330,     0,     0,
     757,   779,     0,   782,     0,   771,   849,     0,   847,   845,
     839,   843,   844,     0,   836,   841,   842,   840,   832,   878,
     874,    54,    59,     0,   597,     0,   626,   259,   260,   261,
     258,   263,   265,   267,   281,   282,   283,   280,   288,   290,
     292,   294,   230,   387,   527,   566,   472,   469,   303,   305,
       0,     0,     0,   703,   708,   661,   349,   745,   746,   747,
     744,   750,   765,   767,   781,   784,     0,     0,     0,   838,
     835,    58,   600,   629,   471,     0,     0,   728,   707,     0,
     846,     0,   837,   725,   727,     0,   848,   854,     0,   851,
       0,   853,   850,   864,     0,     0,     0,   869,     0,   856,
     859,   860,   861,   862,   863,   852,     0,     0,     0,     0,
       0,   858,   855,     0,   866,   867,   868,     0,   857,   865,
     870
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010,    -5, -1010,  -597, -1010,
     445, -1010, -1010, -1010, -1010,   382, -1010,  -633, -1010, -1010,
   -1010,   -71, -1010, -1010, -1010, -1010, -1010, -1010, -1010,   402,
     646, -1010, -1010,   -61,   -43,   -39,    10,    14,    15,   -24,
     -17,   -11,    17,    25,    29,    30, -1010,    32,    33,    37,
      43, -1010, -1010,    44, -1010,    50, -1010,    51,    56,    62,
   -1010, -1010,    63,    64, -1010,    66, -1010,    68, -1010, -1010,
   -1010, -1010, -1010,    69, -1010,    74, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010,   428,   631, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,   343, -1010,
     132, -1010,  -708,   136, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010,   -41, -1010,  -760, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010,   113, -1010, -1010, -1010, -1010, -1010, -1010, -1010,   114,
    -737, -1010, -1010, -1010, -1010,   119, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010,    88, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010,   109, -1010, -1010, -1010,   112,   591, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010,    99, -1010, -1010, -1010, -1010, -1010,
   -1010, -1009, -1010, -1010, -1010,   144, -1010, -1010, -1010,   164,
     636, -1010, -1010, -1008, -1010, -1007, -1010,    38, -1010,    82,
   -1010,    76,    79,    80,    81, -1010, -1010, -1010, -1005, -1010,
   -1010, -1010, -1010,   133, -1010, -1010,  -108,  1119, -1010, -1010,
   -1010, -1010, -1010,   163, -1010, -1010, -1010,   166, -1010,   633,
   -1010,   -66, -1010, -1010, -1010, -1010, -1010,   -65, -1010, -1010,
   -1010, -1010, -1010,   -16, -1010, -1010, -1010,   165, -1010, -1010,
   -1010,   168, -1010,   629, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010,   103, -1010, -1010, -1010,
     111,   674, -1010, -1010, -1010,   -57, -1010,    -3, -1010, -1010,
   -1010, -1010, -1010,   101, -1010, -1010, -1010,   104,   679, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010,   -45, -1010, -1010, -1010,
     152, -1010, -1010, -1010,   155, -1010,   680,   430, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1003, -1010, -1010, -1010, -1010, -1010,   160, -1010, -1010,
   -1010,   -74, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010,   149, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010,   134, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010,   129, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010,   438,   635, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010,   505,   651, -1010, -1010, -1010, -1010, -1010, -1010,
     138, -1010, -1010,   -81, -1010, -1010, -1010, -1010, -1010, -1010,
    -101, -1010, -1010,  -119, -1010, -1010, -1010, -1010, -1010, -1010,
   -1010, -1010, -1010, -1010,   150, -1010
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     751,    87,    88,    41,    68,    84,    85,   776,   983,  1093,
    1094,   835,    43,    70,    90,   440,    91,    45,    71,   162,
     163,   164,   443,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   469,   736,   183,   470,   184,   471,   185,   186,   187,
     482,   748,   188,   189,   504,   190,   505,   191,   192,   193,
     194,   463,   195,   196,   480,   197,   481,   198,   199,   200,
     201,   445,    47,    72,   238,   239,   240,   514,   241,   242,
     243,   244,   202,   446,   203,   447,   204,   448,   862,   863,
     864,  1022,   836,   837,   838,   998,  1260,   839,   999,   840,
    1000,   841,  1001,   842,   843,   555,   844,   845,   846,   847,
     848,   849,   850,   851,   852,  1012,  1267,   853,   854,   855,
     856,  1015,   857,  1016,   858,  1017,   859,  1018,   205,   493,
     897,   898,   899,  1042,   900,  1043,   206,   490,   883,   884,
     885,   886,   207,   492,   891,   892,   893,   894,   208,   491,
     209,   500,   946,   947,   948,   949,   950,   210,   496,   909,
     910,   911,  1052,    63,    80,   404,   405,   406,   569,   407,
     570,   211,   497,   918,   919,   920,   921,   922,   923,   924,
     925,   212,   476,   866,   867,   868,  1025,    49,    73,   286,
     287,   288,   523,   289,   524,   290,   525,   291,   529,   292,
     528,   213,   214,   215,   216,   486,   757,   297,   298,   217,
     483,   878,   879,   880,  1034,  1173,  1174,   218,   477,    57,
      77,   870,   871,   872,  1028,    59,    78,   367,   368,   369,
     370,   371,   372,   373,   554,   374,   558,   375,   557,   376,
     377,   559,   378,   219,   478,   874,   875,   876,  1031,    61,
      79,   389,   390,   391,   392,   393,   563,   394,   395,   396,
     397,   398,   300,   521,   985,   986,   987,  1095,    51,    74,
     312,   313,   314,   533,   315,   220,   484,   221,   485,   303,
     522,   989,   990,   991,  1098,    53,    75,   329,   330,   331,
     537,   332,   333,   539,   334,   335,   222,   495,   905,   906,
     907,  1049,    55,    76,   347,   348,   349,   350,   545,   351,
     546,   352,   547,   353,   548,   354,   549,   355,   550,   356,
     544,   305,   530,   993,   223,   494,   902,   903,  1046,  1199,
    1200,  1201,  1202,  1203,  1280,  1204,  1281,  1205,   224,   498,
     935,   936,   937,  1063,  1290,   938,   939,  1064,   940,   941,
     225,   226,   501,   958,   959,   960,  1075,   961,  1076,   227,
     502,   968,   969,   970,   971,  1080,   972,   973,  1082,   228,
     503,    65,    81,   419,   420,   421,   422,   574,   423,   424,
     576,   425,   426,   427,   579,   807,   428,   580,   229,   444,
      67,    82,   431,   432,   433,   583,   434,   230,   509,   976,
     977,  1086,  1243,  1244,  1245,  1246,  1298,  1247,  1296,  1318,
    1319,  1320,  1328,  1329,  1330,  1336,  1331,  1332,  1333,  1334,
    1340,   231,   510,   980,   981,   982
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     161,   237,   257,   308,   323,   343,   932,   365,   385,   403,
     416,    38,   258,   387,   388,   245,   301,   316,   327,   345,
     860,   379,   399,   890,   417,  1163,  1164,  1165,   304,  1172,
     259,  1178,   133,   134,   260,   750,    30,   366,   386,    31,
     782,    32,    42,    33,   881,   731,   732,   733,   734,   264,
     978,   401,   402,   788,   789,   790,   265,   299,   311,   326,
     344,   441,   266,   512,  1037,   160,   442,  1038,   513,   246,
     302,   317,   328,   346,   519,   380,   400,    44,   418,   520,
     531,   535,   735,   261,    86,   532,   536,   262,   263,   542,
     267,  1264,  1265,  1266,   543,   962,   963,   964,   268,   571,
     429,   430,   269,   270,   572,   271,   272,   401,   402,   581,
     273,   750,   309,   324,   582,    46,   274,   275,   232,   233,
     234,   235,   236,   276,   277,   882,   160,   585,   512,   278,
      48,   358,   586,   995,    50,   279,   280,   281,   585,   282,
     519,   283,   284,   996,   965,   997,  1019,   285,    52,   293,
      89,  1020,   294,   295,   296,   814,   310,   325,    54,   815,
     816,   817,   818,   819,   820,   821,   822,   823,   824,   825,
     826,   827,   828,  1257,  1258,  1259,   829,   830,   831,   832,
     833,   834,    92,    93,  1019,    56,    94,    58,   359,  1021,
     360,   361,    95,    96,    97,   362,   363,   364,  1323,   133,
     134,  1324,  1325,  1326,  1327,   805,   806,    60,  1044,  1061,
     133,   134,   359,  1045,  1062,   133,   134,  1040,   133,   134,
    1041,   126,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,    62,    64,    34,    35,    36,    37,   926,   953,
     954,    66,   128,   129,   130,   131,   819,  1163,  1164,  1165,
     132,  1172,  1068,  1178,   942,   943,   944,  1069,  1073,   133,
     134,   127,  1077,  1074,   435,  1083,   135,  1078,   436,   359,
    1084,   136,   137,   138,   139,   140,   141,   142,   437,   581,
     143,  1090,   306,   890,  1085,   438,  1091,   144,   932,   133,
     134,   160,   895,   896,  1125,   145,   133,   134,   146,   127,
     439,  1019,   160,   531,  1276,   147,  1272,   160,  1273,  1277,
     160,   254,   571,   148,   149,   255,   307,  1286,   150,  1299,
     551,   151,   133,   134,  1300,   152,   449,   133,   134,   881,
     888,   160,   889,    98,    99,   100,   101,   102,   103,   450,
     451,   153,   154,   155,   156,   157,   158,   535,   336,   542,
     553,   452,  1302,   127,  1303,   159,   337,   338,   339,   340,
     341,   342,   127,   359,   912,   913,   914,   915,   916,   917,
     453,   160,   927,   928,   929,   930,   318,   319,   320,   321,
     322,   133,   134,  1341,  1236,   454,  1237,  1238,  1342,   455,
     133,   134,   359,   381,   360,   361,   382,   383,   384,  1047,
     552,   160,  1048,   254,   456,   457,  1087,   255,   160,  1088,
     458,   587,   588,  1185,  1186,  1187,  1287,  1288,  1289,   133,
     134,   161,   744,   745,   746,   747,   459,   460,   237,   753,
     754,   755,   756,  1321,   160,   461,  1322,   462,   464,   160,
     257,   465,   245,   466,   308,   467,   468,   472,   473,   474,
     258,   323,   475,   479,   301,   487,   488,   562,   316,   489,
     499,   343,   506,   507,   508,   327,   304,   511,   259,   515,
     516,   365,   260,   517,   518,   345,   526,   385,   527,   534,
     538,   540,   387,   388,   541,   379,   556,   264,   560,   561,
     416,   399,   564,   160,   265,   299,   246,   565,   566,   311,
     266,   366,   160,   567,   417,   568,   326,   386,   302,   573,
     575,   577,   317,   578,   584,   589,   344,   590,   591,   328,
     592,   261,   593,   594,   595,   262,   263,   596,   267,   346,
     605,   160,   606,   611,   617,   597,   268,   607,   598,   380,
     269,   270,   599,   271,   272,   400,   133,   134,   273,   600,
     601,   602,   603,   309,   274,   275,   608,   618,   418,   604,
     324,   276,   277,   614,   609,   619,   610,   278,   624,   612,
     613,   625,   622,   279,   280,   281,   615,   282,   616,   283,
     284,   620,   621,   623,   626,   285,   627,   293,   628,   629,
     294,   295,   296,   630,   631,   632,   633,   310,   634,   635,
     636,   637,   638,   639,   325,   640,   641,   642,   643,   644,
     645,   646,   647,   408,   409,   410,   411,   412,   413,   414,
     415,   648,   649,   650,   651,   652,   653,   654,   655,   657,
     656,   658,   161,   660,   661,   237,   662,   663,   664,   666,
     667,   668,   669,   670,   672,   671,   673,   674,   675,   245,
     677,   680,   682,   678,   686,   687,   681,   683,   160,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,   688,   689,   931,   945,   955,   684,   416,
     690,   691,   692,   979,   694,   695,   697,   698,   696,   933,
     951,   956,   966,   417,   699,   702,   700,   810,   707,   708,
     711,   703,   704,   246,   713,   716,   705,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     710,   712,   714,   717,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   719,   722,   127,   337,   715,   723,
     725,   726,   720,   934,   952,   957,   967,   418,   129,   130,
     131,   724,   727,   728,   729,   730,   247,   737,   248,   738,
     739,   740,   741,   742,   133,   134,   249,   250,   251,   252,
     253,   135,   743,   749,    32,   752,   136,   137,   138,   758,
     759,   760,   771,   762,   761,   763,   254,   764,   765,   772,
     255,   766,   144,   767,   768,   769,   770,   773,   774,   256,
     775,   777,   778,   779,   809,   784,   780,   781,   783,   861,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   865,   869,   873,   877,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   808,   127,
     359,   901,   904,   785,   786,   908,   153,   154,   787,   975,
     791,   129,   130,   131,   792,   984,   988,  1002,  1003,  1004,
     793,   794,  1005,  1006,  1007,   795,  1008,   133,   134,   796,
     250,   251,   797,   253,   135,   798,   160,   799,   800,   136,
     137,   138,   801,   803,   804,  1009,  1010,  1011,  1013,   254,
    1014,  1023,  1024,   255,  1026,  1027,  1029,  1030,  1033,  1032,
    1055,  1036,   256,  1035,  1051,  1039,  1050,  1054,  1053,  1056,
    1057,  1058,  1059,  1060,  1065,  1066,  1067,  1070,  1071,  1072,
    1079,  1081,  1089,  1092,  1097,  1096,  1099,  1100,  1107,  1102,
    1101,  1103,  1104,  1105,   257,  1106,  1108,   365,  1109,  1110,
     385,  1111,  1112,  1133,   258,   387,   388,  1113,   301,   153,
     154,   379,  1117,  1134,   399,  1188,  1114,  1176,   343,  1115,
     304,   403,   259,  1116,  1118,  1189,   260,   366,  1119,  1197,
     386,  1135,   345,  1162,  1120,  1136,  1121,   931,  1122,   160,
    1123,   264,   945,  1190,  1182,  1195,   955,  1191,   265,   299,
    1140,   933,  1183,  1211,   266,  1239,   951,  1141,  1175,   979,
     956,  1218,   302,  1142,   308,   380,   966,   323,   400,  1241,
    1196,  1177,  1219,   344,  1212,   261,  1228,  1224,   316,   262,
     263,   327,   267,  1198,  1137,  1240,   346,  1213,  1138,  1139,
     268,  1143,  1214,  1215,   269,   270,  1192,   271,   272,  1144,
    1193,  1194,   273,  1145,  1146,   934,  1147,  1148,   274,   275,
     952,  1149,  1166,  1216,   957,   276,   277,  1150,  1151,   311,
     967,   278,   326,  1242,  1152,  1153,  1220,   279,   280,   281,
    1154,   282,   317,   283,   284,   328,  1155,  1156,  1157,   285,
    1158,   293,  1159,  1160,   294,   295,   296,  1221,  1161,  1222,
    1168,  1225,  1226,  1169,  1170,  1171,  1167,  1229,  1231,  1232,
    1233,  1234,  1251,  1249,  1252,   811,  1274,  1261,  1275,  1282,
    1283,  1262,  1284,   309,  1285,  1297,   324,  1305,  1306,  1309,
    1311,   887,  1315,  1263,  1337,  1317,  1338,  1339,  1343,  1347,
     665,  1180,   994,   802,   813,  1124,  1126,  1184,   659,  1181,
    1217,  1227,   709,  1210,  1209,  1268,  1269,   676,  1304,  1179,
    1270,  1128,  1271,  1278,  1279,  1291,  1292,   310,  1293,  1294,
     325,  1301,  1313,  1307,  1310,  1314,  1316,  1344,  1345,  1127,
    1346,  1349,  1350,  1130,  1129,   701,   357,   706,  1132,  1131,
    1254,  1256,  1255,  1208,  1207,  1133,  1253,  1206,   974,   679,
    1308,  1230,  1235,  1188,   992,  1134,   718,  1223,  1312,  1176,
    1335,   685,  1348,  1189,     0,  1248,     0,  1197,  1239,  1295,
     812,     0,   693,  1135,     0,  1162,   721,  1136,     0,     0,
    1250,  1190,  1241,  1195,     0,  1191,     0,     0,     0,     0,
       0,     0,  1140,     0,     0,     0,     0,     0,  1240,  1141,
    1175,     0,     0,     0,     0,  1142,     0,     0,  1196,     0,
       0,     0,     0,  1177,     0,     0,     0,     0,     0,     0,
       0,  1198,     0,     0,     0,     0,  1137,     0,     0,     0,
    1138,  1139,     0,  1143,  1192,     0,  1242,     0,  1193,  1194,
       0,  1144,     0,     0,     0,  1145,  1146,     0,  1147,  1148,
       0,     0,     0,  1149,  1166,     0,     0,     0,     0,  1150,
    1151,     0,     0,     0,     0,     0,  1152,  1153,     0,     0,
       0,     0,  1154,     0,     0,     0,     0,     0,  1155,  1156,
    1157,     0,  1158,     0,  1159,  1160,     0,     0,     0,     0,
    1161,     0,  1168,     0,     0,  1169,  1170,  1171,  1167
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,   766,    78,    79,    80,
      81,    16,    73,    79,    79,    72,    73,    74,    75,    76,
     728,    78,    79,   760,    81,  1034,  1034,  1034,    73,  1034,
      73,  1034,   108,   109,    73,   632,     0,    78,    79,     5,
     673,     7,     7,     9,   139,   186,   187,   188,   189,    73,
     205,   145,   146,   686,   687,   688,    73,    73,    74,    75,
      76,     3,    73,     3,     3,   220,     8,     6,     8,    72,
      73,    74,    75,    76,     3,    78,    79,     7,    81,     8,
       3,     3,   223,    73,   220,     8,     8,    73,    73,     3,
      73,    42,    43,    44,     8,   171,   172,   173,    73,     3,
      13,    14,    73,    73,     8,    73,    73,   145,   146,     3,
      73,   708,    74,    75,     8,     7,    73,    73,    16,    17,
      18,    19,    20,    73,    73,   220,   220,     3,     3,    73,
       7,    24,     8,     8,     7,    73,    73,    73,     3,    73,
       3,    73,    73,     8,   220,     8,     3,    73,     7,    73,
      10,     8,    73,    73,    73,    24,    74,    75,     7,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    25,    26,    27,    45,    46,    47,    48,
      49,    50,    11,    12,     3,     7,    15,     7,    81,     8,
      83,    84,    21,    22,    23,    88,    89,    90,   197,   108,
     109,   200,   201,   202,   203,   183,   184,     7,     3,     3,
     108,   109,    81,     8,     8,   108,   109,     3,   108,   109,
       6,    79,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,     7,     7,   220,   221,   222,   223,    24,   168,
     169,     7,    91,    92,    93,    94,    32,  1276,  1276,  1276,
      99,  1276,     3,  1276,   164,   165,   166,     8,     3,   108,
     109,    80,     3,     8,     6,     3,   115,     8,     3,    81,
       8,   120,   121,   122,   123,   124,   125,   126,     4,     3,
     129,     3,   101,  1040,     8,     8,     8,   136,  1068,   108,
     109,   220,   127,   128,  1022,   144,   108,   109,   147,    80,
       3,     3,   220,     3,     3,   154,     8,   220,     8,     8,
     220,   130,     3,   162,   163,   134,   135,     8,   167,     3,
       8,   170,   108,   109,     8,   174,     4,   108,   109,   139,
     140,   220,   142,    51,    52,    53,    54,    55,    56,     4,
       4,   190,   191,   192,   193,   194,   195,     3,   129,     3,
       8,     4,     8,    80,     8,   204,   137,   138,   139,   140,
     141,   142,    80,    81,   148,   149,   150,   151,   152,   153,
       4,   220,   158,   159,   160,   161,   103,   104,   105,   106,
     107,   108,   109,     3,   196,     4,   198,   199,     8,     4,
     108,   109,    81,    82,    83,    84,    85,    86,    87,     3,
       3,   220,     6,   130,     4,     4,     3,   134,   220,     6,
       4,   436,   437,   131,   132,   133,   155,   156,   157,   108,
     109,   512,    95,    96,    97,    98,     4,     4,   519,   116,
     117,   118,   119,     3,   220,     4,     6,     4,     4,   220,
     531,     4,   519,     4,   535,     4,     4,     4,     4,     4,
     531,   542,     4,     4,   531,     4,     4,     3,   535,     4,
       4,   552,     4,     4,     4,   542,   531,     4,   531,     4,
       4,   562,   531,     4,     4,   552,     4,   568,     4,     4,
       4,     4,   568,   568,     4,   562,     4,   531,     4,     8,
     581,   568,     4,   220,   531,   531,   519,     4,     4,   535,
     531,   562,   220,     8,   581,     3,   542,   568,   531,     4,
       4,     4,   535,     4,     4,   220,   552,     4,     4,   542,
       4,   531,     4,     4,     4,   531,   531,     4,   531,   552,
     223,   220,   222,     4,     4,   221,   531,   222,   221,   562,
     531,   531,   221,   531,   531,   568,   108,   109,   531,   221,
     221,   221,   221,   535,   531,   531,   222,     4,   581,   221,
     542,   531,   531,   223,   221,     4,   221,   531,     4,   221,
     221,     4,   222,   531,   531,   531,   223,   531,   223,   531,
     531,   223,   223,   223,     4,   531,   221,   531,     4,     4,
     531,   531,   531,     4,     4,     4,     4,   535,     4,   223,
     223,   223,     4,     4,   542,     4,     4,     4,     4,     4,
       4,     4,   221,   175,   176,   177,   178,   179,   180,   181,
     182,     4,     4,     4,     4,     4,     4,   223,   223,     4,
     223,     4,   723,     4,   223,   726,   223,   221,   221,     4,
       4,     4,     4,     4,   223,   221,     4,     4,     4,   726,
       4,     4,     4,   221,     4,     4,   221,   221,   220,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,     4,     4,   766,   767,   768,   221,   770,
       4,     4,     4,   774,     4,     4,     4,     4,   221,   766,
     767,   768,   769,   770,     4,     4,   223,   722,     4,     4,
       4,   223,   223,   726,     4,     4,   223,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
     223,   221,   221,     4,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,     4,     4,    80,   137,   221,     7,
       7,     7,   221,   766,   767,   768,   769,   770,    92,    93,
      94,   220,     7,     7,     5,   220,   100,   220,   102,   220,
       5,     5,     5,   220,   108,   109,   110,   111,   112,   113,
     114,   115,   220,     5,     7,   220,   120,   121,   122,     5,
       5,     5,   220,     5,     7,     5,   130,     5,     7,   220,
     134,     7,   136,     7,     7,     7,     7,     5,     7,   143,
       5,     5,     5,   220,     5,     7,   220,   220,   220,     7,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,     7,     7,     7,     7,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,   185,    80,
      81,     7,     7,   220,   220,     7,   190,   191,   220,     7,
     220,    92,    93,    94,   220,     7,     7,     4,     4,     4,
     220,   220,     4,     4,     4,   220,     4,   108,   109,   220,
     111,   112,   220,   114,   115,   220,   220,   220,   220,   120,
     121,   122,   220,   220,   220,     4,     4,     4,     4,   130,
       4,     6,     3,   134,     6,     3,     6,     3,     3,     6,
       4,     3,   143,     6,     3,     6,     6,     3,     6,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   220,     3,     6,     6,     3,   221,     6,
       8,     4,     4,     4,  1025,     4,   223,  1028,   221,   223,
    1031,   221,   221,  1034,  1025,  1031,  1031,   221,  1025,   190,
     191,  1028,     4,  1034,  1031,  1046,   221,  1034,  1049,   221,
    1025,  1052,  1025,   221,   223,  1046,  1025,  1028,   221,  1046,
    1031,  1034,  1049,  1034,     4,  1034,     4,  1068,     4,   220,
       4,  1025,  1073,  1046,     4,  1046,  1077,  1046,  1025,  1025,
    1034,  1068,     4,   221,  1025,  1086,  1073,  1034,  1034,  1090,
    1077,     4,  1025,  1034,  1095,  1028,  1083,  1098,  1031,  1086,
    1046,  1034,     4,  1049,   221,  1025,     4,   223,  1095,  1025,
    1025,  1098,  1025,  1046,  1034,  1086,  1049,   221,  1034,  1034,
    1025,  1034,   221,   221,  1025,  1025,  1046,  1025,  1025,  1034,
    1046,  1046,  1025,  1034,  1034,  1068,  1034,  1034,  1025,  1025,
    1073,  1034,  1034,   221,  1077,  1025,  1025,  1034,  1034,  1095,
    1083,  1025,  1098,  1086,  1034,  1034,   221,  1025,  1025,  1025,
    1034,  1025,  1095,  1025,  1025,  1098,  1034,  1034,  1034,  1025,
    1034,  1025,  1034,  1034,  1025,  1025,  1025,   221,  1034,   221,
    1034,   221,   221,  1034,  1034,  1034,  1034,     4,   223,     4,
     221,     4,     6,   223,     3,   723,     8,   220,     8,     4,
       8,   220,     3,  1095,     8,     4,  1098,     4,     4,     4,
       4,   759,     5,   220,     4,     7,     4,     4,     4,     4,
     519,  1037,   809,   708,   726,  1019,  1024,  1044,   512,  1040,
    1061,  1073,   571,  1054,  1052,   220,   220,   531,  1276,  1036,
     220,  1027,   220,   220,   220,   220,   220,  1095,   220,   220,
    1098,   220,   220,   223,   221,   220,   220,   223,   221,  1025,
     221,   220,   220,  1030,  1028,   562,    77,   568,  1033,  1031,
    1097,  1100,  1098,  1051,  1049,  1276,  1095,  1047,   770,   535,
    1284,  1077,  1083,  1284,   784,  1276,   581,  1068,  1299,  1276,
    1321,   542,  1341,  1284,    -1,  1087,    -1,  1284,  1299,  1234,
     725,    -1,   552,  1276,    -1,  1276,   585,  1276,    -1,    -1,
    1090,  1284,  1299,  1284,    -1,  1284,    -1,    -1,    -1,    -1,
      -1,    -1,  1276,    -1,    -1,    -1,    -1,    -1,  1299,  1276,
    1276,    -1,    -1,    -1,    -1,  1276,    -1,    -1,  1284,    -1,
      -1,    -1,    -1,  1276,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1284,    -1,    -1,    -1,    -1,  1276,    -1,    -1,    -1,
    1276,  1276,    -1,  1276,  1284,    -1,  1299,    -1,  1284,  1284,
      -1,  1276,    -1,    -1,    -1,  1276,  1276,    -1,  1276,  1276,
      -1,    -1,    -1,  1276,  1276,    -1,    -1,    -1,    -1,  1276,
    1276,    -1,    -1,    -1,    -1,    -1,  1276,  1276,    -1,    -1,
      -1,    -1,  1276,    -1,    -1,    -1,    -1,    -1,  1276,  1276,
    1276,    -1,  1276,    -1,  1276,  1276,    -1,    -1,    -1,    -1,
    1276,    -1,  1276,    -1,    -1,  1276,  1276,  1276,  1276
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
       0,     5,     7,     9,   220,   221,   222,   223,   240,   241,
     242,   247,     7,   256,     7,   261,     7,   316,     7,   431,
       7,   512,     7,   529,     7,   546,     7,   463,     7,   469,
       7,   493,     7,   407,     7,   615,     7,   634,   248,   243,
     257,   262,   317,   432,   513,   530,   547,   464,   470,   494,
     408,   616,   635,   240,   249,   250,   220,   245,   246,    10,
     258,   260,    11,    12,    15,    21,    22,    23,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    91,    92,
      93,    94,    99,   108,   109,   115,   120,   121,   122,   123,
     124,   125,   126,   129,   136,   144,   147,   154,   162,   163,
     167,   170,   174,   190,   191,   192,   193,   194,   195,   204,
     220,   255,   263,   264,   265,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   287,   289,   291,   292,   293,   296,   297,
     299,   301,   302,   303,   304,   306,   307,   309,   311,   312,
     313,   314,   326,   328,   330,   372,   380,   386,   392,   394,
     401,   415,   425,   445,   446,   447,   448,   453,   461,   487,
     519,   521,   540,   568,   582,   594,   595,   603,   613,   632,
     641,   665,    16,    17,    18,    19,    20,   255,   318,   319,
     320,   322,   323,   324,   325,   519,   521,   100,   102,   110,
     111,   112,   113,   114,   130,   134,   143,   255,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   281,   282,   283,   284,   287,   289,   291,   292,   293,
     296,   297,   299,   301,   307,   309,   433,   434,   435,   437,
     439,   441,   443,   445,   446,   447,   448,   451,   452,   487,
     506,   519,   521,   523,   540,   565,   101,   135,   255,   441,
     443,   487,   514,   515,   516,   518,   519,   521,   103,   104,
     105,   106,   107,   255,   441,   443,   487,   519,   521,   531,
     532,   533,   535,   536,   538,   539,   129,   137,   138,   139,
     140,   141,   142,   255,   487,   519,   521,   548,   549,   550,
     551,   553,   555,   557,   559,   561,   563,   461,    24,    81,
      83,    84,    88,    89,    90,   255,   348,   471,   472,   473,
     474,   475,   476,   477,   479,   481,   483,   484,   486,   519,
     521,    82,    85,    86,    87,   255,   348,   475,   481,   495,
     496,   497,   498,   499,   501,   502,   503,   504,   505,   519,
     521,   145,   146,   255,   409,   410,   411,   413,   175,   176,
     177,   178,   179,   180,   181,   182,   255,   519,   521,   617,
     618,   619,   620,   622,   623,   625,   626,   627,   630,    13,
      14,   636,   637,   638,   640,     6,     3,     4,     8,     3,
     259,     3,     8,   266,   633,   315,   327,   329,   331,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   305,     4,     4,     4,     4,     4,   285,
     288,   290,     4,     4,     4,     4,   426,   462,   488,     4,
     308,   310,   294,   454,   520,   522,   449,     4,     4,     4,
     381,   393,   387,   373,   569,   541,   402,   416,   583,     4,
     395,   596,   604,   614,   298,   300,     4,     4,     4,   642,
     666,     4,     3,     8,   321,     4,     4,     4,     4,     3,
       8,   507,   524,   436,   438,   440,     4,     4,   444,   442,
     566,     3,     8,   517,     4,     3,     8,   534,     4,   537,
       4,     4,     3,     8,   564,   552,   554,   556,   558,   560,
     562,     8,     3,     8,   478,   349,     4,   482,   480,   485,
       4,     8,     3,   500,     4,     4,     4,     8,     3,   412,
     414,     3,     8,     4,   621,     4,   624,     4,     4,   628,
     631,     3,     8,   639,     4,     3,     8,   240,   240,   220,
       4,     4,     4,     4,     4,     4,     4,   221,   221,   221,
     221,   221,   221,   221,   221,   223,   222,   222,   222,   221,
     221,     4,   221,   221,   223,   223,   223,     4,     4,     4,
     223,   223,   222,   223,     4,     4,     4,   221,     4,     4,
       4,     4,     4,     4,     4,   223,   223,   223,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   221,     4,     4,
       4,     4,     4,     4,   223,   223,   223,     4,     4,   264,
       4,   223,   223,   221,   221,   319,     4,     4,     4,     4,
       4,   221,   223,     4,     4,     4,   434,     4,   221,   515,
       4,   221,     4,   221,   221,   532,     4,     4,     4,     4,
       4,     4,     4,   550,     4,     4,   221,     4,     4,     4,
     223,   473,     4,   223,   223,   223,   497,     4,     4,   410,
     223,     4,   221,     4,   221,   221,     4,     4,   618,     4,
     221,   637,     4,     7,   220,     7,     7,     7,     7,     5,
     220,   186,   187,   188,   189,   223,   286,   220,   220,     5,
       5,     5,   220,   220,    95,    96,    97,    98,   295,     5,
     242,   244,   220,   116,   117,   118,   119,   450,     5,     5,
       5,     7,     5,     5,     5,     7,     7,     7,     7,     7,
       7,   220,   220,     5,     7,     5,   251,     5,     5,   220,
     220,   220,   251,   220,     7,   220,   220,   220,   251,   251,
     251,   220,   220,   220,   220,   220,   220,   220,   220,   220,
     220,   220,   244,   220,   220,   183,   184,   629,   185,     5,
     240,   263,   636,   318,    24,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    45,
      46,    47,    48,    49,    50,   255,   336,   337,   338,   341,
     343,   345,   347,   348,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   361,   362,   363,   364,   366,   368,   370,
     336,     7,   332,   333,   334,     7,   427,   428,   429,     7,
     465,   466,   467,     7,   489,   490,   491,     7,   455,   456,
     457,   139,   220,   382,   383,   384,   385,   249,   140,   142,
     384,   388,   389,   390,   391,   127,   128,   374,   375,   376,
     378,     7,   570,   571,     7,   542,   543,   544,     7,   403,
     404,   405,   148,   149,   150,   151,   152,   153,   417,   418,
     419,   420,   421,   422,   423,   424,    24,   158,   159,   160,
     161,   255,   350,   519,   521,   584,   585,   586,   589,   590,
     592,   593,   164,   165,   166,   255,   396,   397,   398,   399,
     400,   519,   521,   168,   169,   255,   519,   521,   597,   598,
     599,   601,   171,   172,   173,   220,   519,   521,   605,   606,
     607,   608,   610,   611,   617,     7,   643,   644,   205,   255,
     667,   668,   669,   252,     7,   508,   509,   510,     7,   525,
     526,   527,   551,   567,   332,     8,     8,     8,   339,   342,
     344,   346,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   359,     4,     4,   365,   367,   369,   371,     3,
       8,     8,   335,     6,     3,   430,     6,     3,   468,     6,
       3,   492,     6,     3,   458,     6,     3,     3,     6,     6,
       3,     6,   377,   379,     3,     8,   572,     3,     6,   545,
       6,     3,   406,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   587,   591,     4,     4,     4,     3,     8,
       4,     4,     4,     3,     8,   600,   602,     3,     8,     4,
     609,     4,   612,     3,     8,     8,   645,     3,     6,     4,
       3,     8,   220,   253,   254,   511,     6,     3,   528,     6,
       3,     8,     6,     4,     4,     4,     4,   221,   223,   221,
     223,   221,   221,   221,   221,   221,   221,     4,   223,   221,
       4,     4,     4,     4,   337,   336,   334,   433,   429,   471,
     467,   495,   491,   255,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   281,   282,   283,
     284,   287,   289,   291,   292,   293,   296,   297,   299,   301,
     307,   309,   348,   425,   437,   439,   441,   443,   445,   446,
     447,   448,   452,   459,   460,   487,   519,   521,   565,   457,
     383,   389,     4,     4,   375,   131,   132,   133,   255,   267,
     268,   269,   270,   271,   272,   348,   487,   519,   521,   573,
     574,   575,   576,   577,   579,   581,   571,   548,   544,   409,
     405,   221,   221,   221,   221,   221,   221,   418,     4,     4,
     221,   221,   221,   585,   223,   221,   221,   397,     4,     4,
     598,   223,     4,   221,     4,   606,   196,   198,   199,   255,
     348,   519,   521,   646,   647,   648,   649,   651,   644,   223,
     668,     6,     3,   514,   510,   531,   527,    25,    26,    27,
     340,   220,   220,   220,    42,    43,    44,   360,   220,   220,
     220,   220,     8,     8,     8,     8,     3,     8,   220,   220,
     578,   580,     4,     8,     3,     8,     8,   155,   156,   157,
     588,   220,   220,   220,   220,   240,   652,     4,   650,     3,
       8,   220,     8,     8,   460,     4,     4,   223,   575,     4,
     221,     4,   647,   220,   220,     5,   220,     7,   653,   654,
     655,     3,     6,   197,   200,   201,   202,   203,   656,   657,
     658,   660,   661,   662,   663,   654,   659,     4,     4,     4,
     664,     3,     8,     4,   223,   221,   221,     4,   657,   220,
     220
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   224,   226,   225,   227,   225,   228,   225,   229,   225,
     230,   225,   231,   225,   232,   225,   233,   225,   234,   225,
     235,   225,   236,   225,   237,   225,   238,   225,   239,   225,
     240,   240,   240,   240,   240,   240,   240,   241,   243,   242,
     244,   245,   245,   246,   246,   246,   248,   247,   249,   249,
     250,   250,   250,   252,   251,   253,   253,   254,   254,   254,
     255,   257,   256,   259,   258,   258,   260,   262,   261,   263,
     263,   263,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   266,   265,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     285,   284,   286,   286,   286,   286,   286,   288,   287,   290,
     289,   291,   292,   294,   293,   295,   295,   295,   295,   296,
     298,   297,   300,   299,   301,   302,   303,   305,   304,   306,
     308,   307,   310,   309,   311,   312,   313,   315,   314,   317,
     316,   318,   318,   318,   319,   319,   319,   319,   319,   319,
     319,   319,   321,   320,   322,   323,   324,   325,   327,   326,
     329,   328,   331,   330,   332,   332,   333,   333,   333,   335,
     334,   336,   336,   336,   337,   337,   337,   337,   337,   337,
     337,   337,   337,   337,   337,   337,   337,   337,   337,   337,
     337,   337,   337,   337,   337,   337,   337,   339,   338,   340,
     340,   340,   342,   341,   344,   343,   346,   345,   347,   349,
     348,   350,   351,   352,   353,   354,   355,   356,   357,   359,
     358,   360,   360,   360,   361,   362,   363,   365,   364,   367,
     366,   369,   368,   371,   370,   373,   372,   374,   374,   374,
     375,   375,   377,   376,   379,   378,   381,   380,   382,   382,
     382,   383,   383,   384,   385,   387,   386,   388,   388,   388,
     389,   389,   389,   390,   391,   393,   392,   395,   394,   396,
     396,   396,   397,   397,   397,   397,   397,   397,   398,   399,
     400,   402,   401,   403,   403,   404,   404,   404,   406,   405,
     408,   407,   409,   409,   409,   409,   410,   410,   412,   411,
     414,   413,   416,   415,   417,   417,   417,   418,   418,   418,
     418,   418,   418,   419,   420,   421,   422,   423,   424,   426,
     425,   427,   427,   428,   428,   428,   430,   429,   432,   431,
     433,   433,   433,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     436,   435,   438,   437,   440,   439,   442,   441,   444,   443,
     445,   446,   447,   449,   448,   450,   450,   450,   450,   451,
     452,   454,   453,   455,   455,   456,   456,   456,   458,   457,
     459,   459,   459,   460,   460,   460,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   462,   461,   464,
     463,   465,   465,   466,   466,   466,   468,   467,   470,   469,
     471,   471,   472,   472,   472,   473,   473,   473,   473,   473,
     473,   473,   473,   473,   473,   474,   475,   476,   478,   477,
     480,   479,   482,   481,   483,   485,   484,   486,   488,   487,
     489,   489,   490,   490,   490,   492,   491,   494,   493,   495,
     495,   496,   496,   496,   497,   497,   497,   497,   497,   497,
     497,   497,   497,   497,   498,   500,   499,   501,   502,   503,
     504,   505,   507,   506,   508,   508,   509,   509,   509,   511,
     510,   513,   512,   514,   514,   514,   515,   515,   515,   515,
     515,   515,   515,   515,   517,   516,   518,   520,   519,   522,
     521,   524,   523,   525,   525,   526,   526,   526,   528,   527,
     530,   529,   531,   531,   531,   532,   532,   532,   532,   532,
     532,   532,   532,   532,   532,   532,   534,   533,   535,   537,
     536,   538,   539,   541,   540,   542,   542,   543,   543,   543,
     545,   544,   547,   546,   548,   548,   549,   549,   549,   550,
     550,   550,   550,   550,   550,   550,   550,   550,   550,   550,
     552,   551,   554,   553,   556,   555,   558,   557,   560,   559,
     562,   561,   564,   563,   566,   565,   567,   569,   568,   570,
     570,   570,   572,   571,   573,   573,   574,   574,   574,   575,
     575,   575,   575,   575,   575,   575,   575,   575,   575,   575,
     575,   575,   575,   576,   578,   577,   580,   579,   581,   583,
     582,   584,   584,   584,   585,   585,   585,   585,   585,   585,
     585,   585,   585,   587,   586,   588,   588,   588,   589,   591,
     590,   592,   593,   594,   596,   595,   597,   597,   597,   598,
     598,   598,   598,   598,   600,   599,   602,   601,   604,   603,
     605,   605,   605,   606,   606,   606,   606,   606,   606,   607,
     609,   608,   610,   612,   611,   614,   613,   616,   615,   617,
     617,   617,   618,   618,   618,   618,   618,   618,   618,   618,
     618,   618,   618,   619,   621,   620,   622,   624,   623,   625,
     626,   628,   627,   629,   629,   631,   630,   633,   632,   635,
     634,   636,   636,   636,   637,   637,   639,   638,   640,   642,
     641,   643,   643,   643,   645,   644,   646,   646,   646,   647,
     647,   647,   647,   647,   647,   647,   648,   650,   649,   652,
     651,   653,   653,   653,   655,   654,   656,   656,   656,   657,
     657,   657,   657,   657,   659,   658,   660,   661,   662,   664,
     663,   666,   665,   667,   667,   667,   668,   668,   669
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       0,     4,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     3,     3,     0,     4,     1,     1,     1,     1,     3,
       0,     4,     0,     4,     3,     3,     3,     0,     4,     3,
       0,     4,     0,     4,     3,     3,     3,     0,     6,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     3,     3,     3,     0,     6,
       0,     6,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     0,
       4,     1,     1,     1,     3,     3,     3,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     1,     3,     2,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     0,     6,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     1,     3,     2,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
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
       1,     1,     1,     1,     1,     1,     1,     0,     6,     0,
       4,     0,     1,     1,     3,     2,     0,     4,     0,     4,
       0,     1,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     0,     4,
       0,     4,     0,     4,     1,     0,     4,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     0,
       1,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     4,     0,
       4,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       4,     3,     3,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     0,     1,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     1,     0,     6,     1,
       3,     2,     0,     4,     0,     1,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     3,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     3,     0,
       4,     3,     3,     3,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     3,     0,     4,     0,     6,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     0,     4,     3,     0,     4,     3,
       3,     0,     4,     1,     1,     0,     4,     0,     6,     0,
       4,     1,     3,     2,     1,     1,     0,     6,     3,     0,
       6,     1,     3,     2,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       6,     1,     3,     2,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     0,     4,     3,     3,     3,     0,
       4,     0,     6,     1,     3,     2,     1,     1,     3
  };


#if PARSER6_DEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Dhcp6Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\",\"", "\":\"",
  "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"",
  "\"data-directory\"", "\"config-control\"", "\"config-databases\"",
  "\"config-fetch-wait-time\"", "\"interfaces-config\"", "\"interfaces\"",
  "\"re-detect\"", "\"service-sockets-require-all\"",
  "\"service-sockets-retry-wait-time\"", "\"service-sockets-max-retries\"",
  "\"lease-database\"", "\"hosts-database\"", "\"hosts-databases\"",
  "\"type\"", "\"memfile\"", "\"mysql\"", "\"postgresql\"", "\"user\"",
  "\"password\"", "\"host\"", "\"port\"", "\"persist\"",
  "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
  "\"read-timeout\"", "\"write-timeout\"", "\"tcp-user-timeout\"",
  "\"max-reconnect-tries\"", "\"reconnect-wait-time\"", "\"on-fail\"",
  "\"stop-retry-exit\"", "\"serve-retry-exit\"",
  "\"serve-retry-continue\"", "\"retry-on-startup\"", "\"max-row-errors\"",
  "\"trust-anchor\"", "\"cert-file\"", "\"key-file\"", "\"cipher-list\"",
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
  "\"ddns-ttl-percent\"", "\"store-extended-info\"", "\"subnet6\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"always-send\"", "\"never-send\"",
  "\"record-types\"", "\"encapsulate\"", "\"array\"",
  "\"parked-packet-limit\"", "\"allocator\"", "\"pd-allocator\"",
  "\"ddns-conflict-resolution-mode\"", "\"check-with-dhcid\"",
  "\"no-check-with-dhcid\"", "\"check-exists-with-dhcid\"",
  "\"no-check-without-dhcid\"", "\"shared-networks\"", "\"pools\"",
  "\"pool\"", "\"pd-pools\"", "\"prefix\"", "\"prefix-len\"",
  "\"excluded-prefix\"", "\"excluded-prefix-len\"", "\"delegated-len\"",
  "\"user-context\"", "\"comment\"", "\"subnet\"", "\"interface\"",
  "\"interface-id\"", "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"",
  "\"disabled\"", "\"out-of-pool\"", "\"global\"", "\"all\"",
  "\"reservations-global\"", "\"reservations-in-subnet\"",
  "\"reservations-out-of-pool\"", "\"mac-sources\"",
  "\"relay-supplied-options\"", "\"host-reservation-identifiers\"",
  "\"sanity-checks\"", "\"lease-checks\"", "\"extended-info-checks\"",
  "\"client-classes\"", "\"require-client-classes\"", "\"test\"",
  "\"template-test\"", "\"only-if-required\"", "\"client-class\"",
  "\"pool-id\"", "\"reservations\"", "\"ip-addresses\"", "\"prefixes\"",
  "\"duid\"", "\"hw-address\"", "\"hostname\"", "\"flex-id\"", "\"relay\"",
  "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
  "\"expired-leases-processing\"", "\"reclaim-timer-wait-time\"",
  "\"flush-reclaimed-timer-wait-time\"", "\"hold-reclaimed-time\"",
  "\"max-reclaim-leases\"", "\"max-reclaim-time\"",
  "\"unwarned-reclaim-cycles\"", "\"server-id\"", "\"LLT\"", "\"EN\"",
  "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"", "\"enterprise-id\"",
  "\"dhcp4o6-port\"", "\"multi-threading\"", "\"enable-multi-threading\"",
  "\"thread-pool-size\"", "\"packet-queue-size\"", "\"control-socket\"",
  "\"socket-type\"", "\"socket-name\"", "\"dhcp-queue-control\"",
  "\"enable-queue\"", "\"queue-type\"", "\"capacity\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"server-ip\"", "\"server-port\"",
  "\"sender-ip\"", "\"sender-port\"", "\"max-queue-size\"",
  "\"ncr-protocol\"", "\"ncr-format\"", "\"UDP\"", "\"TCP\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"hostname-char-set\"", "\"hostname-char-replacement\"",
  "\"early-global-reservations-lookup\"", "\"ip-reservations-unique\"",
  "\"reservations-lookup-first\"", "\"loggers\"", "\"output-options\"",
  "\"output\"", "\"debuglevel\"", "\"severity\"", "\"flush\"",
  "\"maxsize\"", "\"maxver\"", "\"pattern\"", "\"compatibility\"",
  "\"lenient-option-parsing\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP6",
  "SUB_DHCP6", "SUB_INTERFACES6", "SUB_SUBNET6", "SUB_POOL6",
  "SUB_PD_POOL", "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS",
  "SUB_CONFIG_CONTROL", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "$@14", "value", "sub_json", "map2", "$@15", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@16", "list_content",
  "not_empty_list", "list_strings", "$@17", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@18",
  "global_object", "$@19", "global_object_comma", "sub_dhcp6", "$@20",
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
  "ddns_conflict_resolution_mode", "$@25",
  "ddns_conflict_resolution_mode_value", "ddns_ttl_percent",
  "hostname_char_set", "$@26", "hostname_char_replacement", "$@27",
  "store_extended_info", "statistic_default_sample_count",
  "statistic_default_sample_age", "server_tag", "$@28",
  "parked_packet_limit", "allocator", "$@29", "pd_allocator", "$@30",
  "early_global_reservations_lookup", "ip_reservations_unique",
  "reservations_lookup_first", "interfaces_config", "$@31",
  "sub_interfaces6", "$@32", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@33", "re_detect",
  "service_sockets_require_all", "service_sockets_retry_wait_time",
  "service_sockets_max_retries", "lease_database", "$@34",
  "hosts_database", "$@35", "hosts_databases", "$@36", "database_list",
  "not_empty_database_list", "database", "$@37", "database_map_params",
  "database_map_param", "database_type", "$@38", "db_type", "user", "$@39",
  "password", "$@40", "host", "$@41", "port", "name", "$@42", "persist",
  "lfc_interval", "readonly", "connect_timeout", "read_timeout",
  "write_timeout", "tcp_user_timeout", "reconnect_wait_time", "on_fail",
  "$@43", "on_fail_mode", "retry_on_startup", "max_row_errors",
  "max_reconnect_tries", "trust_anchor", "$@44", "cert_file", "$@45",
  "key_file", "$@46", "cipher_list", "$@47", "sanity_checks", "$@48",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@49",
  "extended_info_checks", "$@50", "mac_sources", "$@51",
  "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@52",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@53",
  "dhcp_multi_threading", "$@54", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@55", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@56",
  "sub_hooks_library", "$@57", "hooks_params", "hooks_param", "library",
  "$@58", "parameters", "$@59", "expired_leases_processing", "$@60",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@61",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@62",
  "sub_subnet6", "$@63", "subnet6_params", "subnet6_param", "subnet",
  "$@64", "interface", "$@65", "interface_id", "$@66", "client_class",
  "$@67", "require_client_classes", "$@68", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "reservation_mode",
  "$@69", "hr_mode", "id", "rapid_commit", "shared_networks", "$@70",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@71", "shared_network_params", "shared_network_param",
  "option_def_list", "$@72", "sub_option_def_list", "$@73",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@74", "sub_option_def", "$@75",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@76",
  "option_def_record_types", "$@77", "space", "$@78", "option_def_space",
  "option_def_encapsulate", "$@79", "option_def_array", "option_data_list",
  "$@80", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@81", "sub_option_data", "$@82",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@83",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "option_data_never_send", "pools_list",
  "$@84", "pools_list_content", "not_empty_pools_list", "pool_list_entry",
  "$@85", "sub_pool6", "$@86", "pool_params", "pool_param", "pool_entry",
  "$@87", "pool_id", "user_context", "$@88", "comment", "$@89",
  "pd_pools_list", "$@90", "pd_pools_list_content",
  "not_empty_pd_pools_list", "pd_pool_entry", "$@91", "sub_pd_pool",
  "$@92", "pd_pool_params", "pd_pool_param", "pd_prefix", "$@93",
  "pd_prefix_len", "excluded_prefix", "$@94", "excluded_prefix_len",
  "pd_delegated_len", "reservations", "$@95", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@96", "sub_reservation",
  "$@97", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "ip_addresses", "$@98", "prefixes", "$@99", "duid",
  "$@100", "hw_address", "$@101", "hostname", "$@102", "flex_id_value",
  "$@103", "reservation_client_classes", "$@104", "relay", "$@105",
  "relay_map", "client_classes", "$@106", "client_classes_list",
  "client_class_entry", "$@107", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@108",
  "client_class_template_test", "$@109", "only_if_required", "server_id",
  "$@110", "server_id_params", "server_id_param", "server_id_type",
  "$@111", "duid_type", "htype", "identifier", "$@112", "time",
  "enterprise_id", "dhcp4o6_port", "control_socket", "$@113",
  "control_socket_params", "control_socket_param", "socket_type", "$@114",
  "socket_name", "$@115", "dhcp_queue_control", "$@116",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@117", "capacity", "arbitrary_map_entry", "$@118",
  "dhcp_ddns", "$@119", "sub_dhcp_ddns", "$@120", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@121", "server_port",
  "sender_ip", "$@122", "sender_port", "max_queue_size", "ncr_protocol",
  "$@123", "ncr_protocol_value", "ncr_format", "$@124", "config_control",
  "$@125", "sub_config_control", "$@126", "config_control_params",
  "config_control_param", "config_databases", "$@127",
  "config_fetch_wait_time", "loggers", "$@128", "loggers_entries",
  "logger_entry", "$@129", "logger_params", "logger_param", "debuglevel",
  "severity", "$@130", "output_options_list", "$@131",
  "output_options_list_content", "output_entry", "$@132",
  "output_params_list", "output_params", "output", "$@133", "flush",
  "maxsize", "maxver", "pattern", "$@134", "compatibility", "$@135",
  "compatibility_params", "compatibility_param", "lenient_option_parsing", YY_NULLPTR
  };
#endif


#if PARSER6_DEBUG
  const short
  Dhcp6Parser::yyrline_[] =
  {
       0,   318,   318,   318,   319,   319,   320,   320,   321,   321,
     322,   322,   323,   323,   324,   324,   325,   325,   326,   326,
     327,   327,   328,   328,   329,   329,   330,   330,   331,   331,
     339,   340,   341,   342,   343,   344,   345,   348,   353,   353,
     364,   367,   368,   371,   376,   382,   387,   387,   394,   395,
     398,   402,   406,   412,   412,   419,   420,   423,   427,   431,
     441,   450,   450,   465,   465,   479,   482,   488,   488,   497,
     498,   499,   506,   507,   508,   509,   510,   511,   512,   513,
     514,   515,   516,   517,   518,   519,   520,   521,   522,   523,
     524,   525,   526,   527,   528,   529,   530,   531,   532,   533,
     534,   535,   536,   537,   538,   539,   540,   541,   542,   543,
     544,   545,   546,   547,   548,   549,   550,   551,   552,   553,
     554,   555,   556,   557,   558,   559,   560,   561,   562,   563,
     564,   565,   566,   567,   568,   569,   570,   571,   572,   573,
     574,   577,   577,   586,   592,   598,   604,   610,   616,   622,
     628,   634,   640,   646,   652,   658,   664,   670,   676,   682,
     688,   688,   697,   700,   703,   706,   709,   715,   715,   724,
     724,   733,   742,   752,   752,   761,   764,   767,   770,   775,
     781,   781,   790,   790,   799,   805,   811,   817,   817,   826,
     832,   832,   841,   841,   850,   856,   862,   868,   868,   880,
     880,   889,   890,   891,   896,   897,   898,   899,   900,   901,
     902,   903,   906,   906,   917,   923,   929,   935,   941,   941,
     954,   954,   967,   967,   978,   979,   982,   983,   984,   989,
     989,   999,  1000,  1001,  1006,  1007,  1008,  1009,  1010,  1011,
    1012,  1013,  1014,  1015,  1016,  1017,  1018,  1019,  1020,  1021,
    1022,  1023,  1024,  1025,  1026,  1027,  1028,  1031,  1031,  1039,
    1040,  1041,  1044,  1044,  1053,  1053,  1062,  1062,  1071,  1077,
    1077,  1086,  1092,  1098,  1104,  1110,  1116,  1122,  1129,  1135,
    1135,  1143,  1144,  1145,  1148,  1154,  1160,  1166,  1166,  1175,
    1175,  1184,  1184,  1193,  1193,  1202,  1202,  1213,  1214,  1215,
    1220,  1221,  1224,  1224,  1243,  1243,  1261,  1261,  1272,  1273,
    1274,  1279,  1280,  1283,  1288,  1293,  1293,  1304,  1305,  1306,
    1311,  1312,  1313,  1316,  1321,  1328,  1328,  1341,  1341,  1354,
    1355,  1356,  1361,  1362,  1363,  1364,  1365,  1366,  1369,  1375,
    1381,  1387,  1387,  1398,  1399,  1402,  1403,  1404,  1409,  1409,
    1419,  1419,  1429,  1430,  1431,  1434,  1437,  1438,  1441,  1441,
    1450,  1450,  1459,  1459,  1471,  1472,  1473,  1478,  1479,  1480,
    1481,  1482,  1483,  1486,  1492,  1498,  1504,  1510,  1516,  1525,
    1525,  1539,  1540,  1543,  1544,  1545,  1554,  1554,  1580,  1580,
    1591,  1592,  1593,  1599,  1600,  1601,  1602,  1603,  1604,  1605,
    1606,  1607,  1608,  1609,  1610,  1611,  1612,  1613,  1614,  1615,
    1616,  1617,  1618,  1619,  1620,  1621,  1622,  1623,  1624,  1625,
    1626,  1627,  1628,  1629,  1630,  1631,  1632,  1633,  1634,  1635,
    1636,  1637,  1638,  1639,  1640,  1641,  1642,  1643,  1644,  1645,
    1648,  1648,  1657,  1657,  1666,  1666,  1675,  1675,  1684,  1684,
    1695,  1701,  1707,  1713,  1713,  1721,  1722,  1723,  1724,  1727,
    1733,  1741,  1741,  1753,  1754,  1758,  1759,  1760,  1765,  1765,
    1773,  1774,  1775,  1780,  1781,  1782,  1783,  1784,  1785,  1786,
    1787,  1788,  1789,  1790,  1791,  1792,  1793,  1794,  1795,  1796,
    1797,  1798,  1799,  1800,  1801,  1802,  1803,  1804,  1805,  1806,
    1807,  1808,  1809,  1810,  1811,  1812,  1813,  1814,  1815,  1816,
    1817,  1818,  1819,  1820,  1821,  1822,  1823,  1830,  1830,  1844,
    1844,  1853,  1854,  1857,  1858,  1859,  1866,  1866,  1881,  1881,
    1895,  1896,  1899,  1900,  1901,  1906,  1907,  1908,  1909,  1910,
    1911,  1912,  1913,  1914,  1915,  1918,  1920,  1926,  1928,  1928,
    1937,  1937,  1946,  1946,  1955,  1957,  1957,  1966,  1976,  1976,
    1989,  1990,  1995,  1996,  1997,  2004,  2004,  2016,  2016,  2028,
    2029,  2034,  2035,  2036,  2043,  2044,  2045,  2046,  2047,  2048,
    2049,  2050,  2051,  2052,  2055,  2057,  2057,  2066,  2068,  2070,
    2076,  2082,  2091,  2091,  2104,  2105,  2108,  2109,  2110,  2115,
    2115,  2125,  2125,  2135,  2136,  2137,  2142,  2143,  2144,  2145,
    2146,  2147,  2148,  2149,  2152,  2152,  2161,  2167,  2167,  2192,
    2192,  2222,  2222,  2235,  2236,  2239,  2240,  2241,  2246,  2246,
    2258,  2258,  2270,  2271,  2272,  2277,  2278,  2279,  2280,  2281,
    2282,  2283,  2284,  2285,  2286,  2287,  2290,  2290,  2299,  2305,
    2305,  2314,  2320,  2329,  2329,  2340,  2341,  2344,  2345,  2346,
    2351,  2351,  2360,  2360,  2369,  2370,  2373,  2374,  2375,  2381,
    2382,  2383,  2384,  2385,  2386,  2387,  2388,  2389,  2390,  2391,
    2394,  2394,  2405,  2405,  2416,  2416,  2425,  2425,  2434,  2434,
    2443,  2443,  2452,  2452,  2466,  2466,  2477,  2483,  2483,  2494,
    2495,  2496,  2501,  2501,  2511,  2512,  2515,  2516,  2517,  2522,
    2523,  2524,  2525,  2526,  2527,  2528,  2529,  2530,  2531,  2532,
    2533,  2534,  2535,  2538,  2540,  2540,  2549,  2549,  2558,  2567,
    2567,  2580,  2581,  2582,  2587,  2588,  2589,  2590,  2591,  2592,
    2593,  2594,  2595,  2598,  2598,  2606,  2607,  2608,  2611,  2617,
    2617,  2626,  2632,  2640,  2648,  2648,  2659,  2660,  2661,  2666,
    2667,  2668,  2669,  2670,  2673,  2673,  2682,  2682,  2694,  2694,
    2707,  2708,  2709,  2714,  2715,  2716,  2717,  2718,  2719,  2722,
    2728,  2728,  2737,  2743,  2743,  2753,  2753,  2766,  2766,  2776,
    2777,  2778,  2783,  2784,  2785,  2786,  2787,  2788,  2789,  2790,
    2791,  2792,  2793,  2796,  2802,  2802,  2811,  2817,  2817,  2826,
    2832,  2838,  2838,  2847,  2848,  2851,  2851,  2862,  2862,  2874,
    2874,  2884,  2885,  2886,  2892,  2893,  2896,  2896,  2907,  2915,
    2915,  2928,  2929,  2930,  2936,  2936,  2944,  2945,  2946,  2951,
    2952,  2953,  2954,  2955,  2956,  2957,  2960,  2966,  2966,  2975,
    2975,  2986,  2987,  2988,  2993,  2993,  3001,  3002,  3003,  3008,
    3009,  3010,  3011,  3012,  3015,  3015,  3024,  3030,  3036,  3042,
    3042,  3051,  3051,  3062,  3063,  3064,  3069,  3070,  3073
  };

  void
  Dhcp6Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Dhcp6Parser::yy_reduce_print_ (int yyrule) const
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
#line 6467 "dhcp6_parser.cc"

#line 3079 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
