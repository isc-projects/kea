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
#line 315 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 413 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 315 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 419 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 315 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 425 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 315 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 431 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 315 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 437 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 315 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 443 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 315 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 449 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 315 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 455 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 315 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 461 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 315 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 467 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 315 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 473 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 315 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 479 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 315 "dhcp6_parser.yy"
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
#line 324 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 766 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 325 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 772 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 326 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 778 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 327 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 784 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 328 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 790 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 329 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 796 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 330 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 802 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 331 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 808 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 332 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 814 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 333 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 820 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 334 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 826 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 335 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 832 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 336 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 838 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 337 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 844 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 345 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 850 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 346 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 856 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 347 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 862 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 348 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 868 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 349 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 874 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 350 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 880 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 351 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 886 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 354 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 895 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 359 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 906 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 364 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 916 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 370 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 922 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 377 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 932 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 382 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 943 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 388 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 951 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 393 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 960 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 396 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 968 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 404 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 977 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 408 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 986 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 412 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 994 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 418 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 1002 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 420 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1011 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 429 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1020 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 433 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1029 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 437 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1037 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 447 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1048 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 456 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1059 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 461 "dhcp6_parser.yy"
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
#line 471 "dhcp6_parser.yy"
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
#line 480 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1097 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 488 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1105 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 494 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1115 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 498 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1124 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 505 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1132 "dhcp6_parser.cc"
    break;

  case 141: // $@21: %empty
#line 583 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1141 "dhcp6_parser.cc"
    break;

  case 142: // data_directory: "data-directory" $@21 ":" "constant string"
#line 586 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1151 "dhcp6_parser.cc"
    break;

  case 143: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 592 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1161 "dhcp6_parser.cc"
    break;

  case 144: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 598 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1171 "dhcp6_parser.cc"
    break;

  case 145: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 604 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1181 "dhcp6_parser.cc"
    break;

  case 146: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 610 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1191 "dhcp6_parser.cc"
    break;

  case 147: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 616 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1201 "dhcp6_parser.cc"
    break;

  case 148: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 622 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1211 "dhcp6_parser.cc"
    break;

  case 149: // renew_timer: "renew-timer" ":" "integer"
#line 628 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1221 "dhcp6_parser.cc"
    break;

  case 150: // rebind_timer: "rebind-timer" ":" "integer"
#line 634 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1231 "dhcp6_parser.cc"
    break;

  case 151: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 640 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1241 "dhcp6_parser.cc"
    break;

  case 152: // t1_percent: "t1-percent" ":" "floating point"
#line 646 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1251 "dhcp6_parser.cc"
    break;

  case 153: // t2_percent: "t2-percent" ":" "floating point"
#line 652 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1261 "dhcp6_parser.cc"
    break;

  case 154: // cache_threshold: "cache-threshold" ":" "floating point"
#line 658 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1271 "dhcp6_parser.cc"
    break;

  case 155: // cache_max_age: "cache-max-age" ":" "integer"
#line 664 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1281 "dhcp6_parser.cc"
    break;

  case 156: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 670 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1291 "dhcp6_parser.cc"
    break;

  case 157: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 676 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1301 "dhcp6_parser.cc"
    break;

  case 158: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 682 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1311 "dhcp6_parser.cc"
    break;

  case 159: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 688 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1321 "dhcp6_parser.cc"
    break;

  case 160: // $@22: %empty
#line 694 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1330 "dhcp6_parser.cc"
    break;

  case 161: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 697 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1339 "dhcp6_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "when-present"
#line 703 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1347 "dhcp6_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "never"
#line 706 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1355 "dhcp6_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "always"
#line 709 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1363 "dhcp6_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "when-not-present"
#line 712 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1371 "dhcp6_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "boolean"
#line 715 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1380 "dhcp6_parser.cc"
    break;

  case 167: // $@23: %empty
#line 721 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1389 "dhcp6_parser.cc"
    break;

  case 168: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 724 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1399 "dhcp6_parser.cc"
    break;

  case 169: // $@24: %empty
#line 730 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1408 "dhcp6_parser.cc"
    break;

  case 170: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 733 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1418 "dhcp6_parser.cc"
    break;

  case 171: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 739 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1428 "dhcp6_parser.cc"
    break;

  case 172: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 748 "dhcp6_parser.yy"
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
#line 758 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1451 "dhcp6_parser.cc"
    break;

  case 174: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 761 "dhcp6_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 175: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 767 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1468 "dhcp6_parser.cc"
    break;

  case 176: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 770 "dhcp6_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1476 "dhcp6_parser.cc"
    break;

  case 177: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 773 "dhcp6_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1484 "dhcp6_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 776 "dhcp6_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1492 "dhcp6_parser.cc"
    break;

  case 179: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 781 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1502 "dhcp6_parser.cc"
    break;

  case 180: // $@26: %empty
#line 787 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1511 "dhcp6_parser.cc"
    break;

  case 181: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 790 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1521 "dhcp6_parser.cc"
    break;

  case 182: // $@27: %empty
#line 796 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1530 "dhcp6_parser.cc"
    break;

  case 183: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 799 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1540 "dhcp6_parser.cc"
    break;

  case 184: // store_extended_info: "store-extended-info" ":" "boolean"
#line 805 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1550 "dhcp6_parser.cc"
    break;

  case 185: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 811 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1560 "dhcp6_parser.cc"
    break;

  case 186: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 817 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1570 "dhcp6_parser.cc"
    break;

  case 187: // $@28: %empty
#line 823 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1579 "dhcp6_parser.cc"
    break;

  case 188: // server_tag: "server-tag" $@28 ":" "constant string"
#line 826 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1589 "dhcp6_parser.cc"
    break;

  case 189: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 832 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1599 "dhcp6_parser.cc"
    break;

  case 190: // $@29: %empty
#line 838 "dhcp6_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1608 "dhcp6_parser.cc"
    break;

  case 191: // allocator: "allocator" $@29 ":" "constant string"
#line 841 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1618 "dhcp6_parser.cc"
    break;

  case 192: // $@30: %empty
#line 847 "dhcp6_parser.yy"
                           {
    ctx.unique("pd-allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1627 "dhcp6_parser.cc"
    break;

  case 193: // pd_allocator: "pd-allocator" $@30 ":" "constant string"
#line 850 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-allocator", al);
    ctx.leave();
}
#line 1637 "dhcp6_parser.cc"
    break;

  case 194: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 856 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1647 "dhcp6_parser.cc"
    break;

  case 195: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 862 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1657 "dhcp6_parser.cc"
    break;

  case 196: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 868 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1667 "dhcp6_parser.cc"
    break;

  case 197: // $@31: %empty
#line 874 "dhcp6_parser.yy"
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
#line 880 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1689 "dhcp6_parser.cc"
    break;

  case 199: // $@32: %empty
#line 886 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1699 "dhcp6_parser.cc"
    break;

  case 200: // sub_interfaces6: "{" $@32 interfaces_config_params "}"
#line 890 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1708 "dhcp6_parser.cc"
    break;

  case 203: // interfaces_config_params: interfaces_config_params ","
#line 897 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1716 "dhcp6_parser.cc"
    break;

  case 212: // $@33: %empty
#line 912 "dhcp6_parser.yy"
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
#line 918 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1737 "dhcp6_parser.cc"
    break;

  case 214: // re_detect: "re-detect" ":" "boolean"
#line 923 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1747 "dhcp6_parser.cc"
    break;

  case 215: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 929 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1757 "dhcp6_parser.cc"
    break;

  case 216: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 935 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1767 "dhcp6_parser.cc"
    break;

  case 217: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 941 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1777 "dhcp6_parser.cc"
    break;

  case 218: // $@34: %empty
#line 947 "dhcp6_parser.yy"
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
#line 953 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1800 "dhcp6_parser.cc"
    break;

  case 220: // $@35: %empty
#line 960 "dhcp6_parser.yy"
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
#line 966 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1823 "dhcp6_parser.cc"
    break;

  case 222: // $@36: %empty
#line 973 "dhcp6_parser.yy"
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
#line 979 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1844 "dhcp6_parser.cc"
    break;

  case 228: // not_empty_database_list: not_empty_database_list ","
#line 990 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1852 "dhcp6_parser.cc"
    break;

  case 229: // $@37: %empty
#line 995 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1862 "dhcp6_parser.cc"
    break;

  case 230: // database: "{" $@37 database_map_params "}"
#line 999 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1872 "dhcp6_parser.cc"
    break;

  case 233: // database_map_params: database_map_params ","
#line 1007 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1880 "dhcp6_parser.cc"
    break;

  case 257: // $@38: %empty
#line 1037 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1889 "dhcp6_parser.cc"
    break;

  case 258: // database_type: "type" $@38 ":" db_type
#line 1040 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1898 "dhcp6_parser.cc"
    break;

  case 259: // db_type: "memfile"
#line 1045 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1904 "dhcp6_parser.cc"
    break;

  case 260: // db_type: "mysql"
#line 1046 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1910 "dhcp6_parser.cc"
    break;

  case 261: // db_type: "postgresql"
#line 1047 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1916 "dhcp6_parser.cc"
    break;

  case 262: // $@39: %empty
#line 1050 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1925 "dhcp6_parser.cc"
    break;

  case 263: // user: "user" $@39 ":" "constant string"
#line 1053 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1935 "dhcp6_parser.cc"
    break;

  case 264: // $@40: %empty
#line 1059 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1944 "dhcp6_parser.cc"
    break;

  case 265: // password: "password" $@40 ":" "constant string"
#line 1062 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1954 "dhcp6_parser.cc"
    break;

  case 266: // $@41: %empty
#line 1068 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1963 "dhcp6_parser.cc"
    break;

  case 267: // host: "host" $@41 ":" "constant string"
#line 1071 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1973 "dhcp6_parser.cc"
    break;

  case 268: // port: "port" ":" "integer"
#line 1077 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1983 "dhcp6_parser.cc"
    break;

  case 269: // $@42: %empty
#line 1083 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1992 "dhcp6_parser.cc"
    break;

  case 270: // name: "name" $@42 ":" "constant string"
#line 1086 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2002 "dhcp6_parser.cc"
    break;

  case 271: // persist: "persist" ":" "boolean"
#line 1092 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2012 "dhcp6_parser.cc"
    break;

  case 272: // lfc_interval: "lfc-interval" ":" "integer"
#line 1098 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2022 "dhcp6_parser.cc"
    break;

  case 273: // readonly: "readonly" ":" "boolean"
#line 1104 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2032 "dhcp6_parser.cc"
    break;

  case 274: // connect_timeout: "connect-timeout" ":" "integer"
#line 1110 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2042 "dhcp6_parser.cc"
    break;

  case 275: // read_timeout: "read-timeout" ":" "integer"
#line 1116 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2052 "dhcp6_parser.cc"
    break;

  case 276: // write_timeout: "write-timeout" ":" "integer"
#line 1122 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2062 "dhcp6_parser.cc"
    break;

  case 277: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1128 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2072 "dhcp6_parser.cc"
    break;

  case 278: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1135 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2082 "dhcp6_parser.cc"
    break;

  case 279: // $@43: %empty
#line 1141 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2091 "dhcp6_parser.cc"
    break;

  case 280: // on_fail: "on-fail" $@43 ":" on_fail_mode
#line 1144 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2100 "dhcp6_parser.cc"
    break;

  case 281: // on_fail_mode: "stop-retry-exit"
#line 1149 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2106 "dhcp6_parser.cc"
    break;

  case 282: // on_fail_mode: "serve-retry-exit"
#line 1150 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2112 "dhcp6_parser.cc"
    break;

  case 283: // on_fail_mode: "serve-retry-continue"
#line 1151 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2118 "dhcp6_parser.cc"
    break;

  case 284: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1154 "dhcp6_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2128 "dhcp6_parser.cc"
    break;

  case 285: // max_row_errors: "max-row-errors" ":" "integer"
#line 1160 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2138 "dhcp6_parser.cc"
    break;

  case 286: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1166 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2148 "dhcp6_parser.cc"
    break;

  case 287: // $@44: %empty
#line 1172 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2157 "dhcp6_parser.cc"
    break;

  case 288: // trust_anchor: "trust-anchor" $@44 ":" "constant string"
#line 1175 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2167 "dhcp6_parser.cc"
    break;

  case 289: // $@45: %empty
#line 1181 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2176 "dhcp6_parser.cc"
    break;

  case 290: // cert_file: "cert-file" $@45 ":" "constant string"
#line 1184 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2186 "dhcp6_parser.cc"
    break;

  case 291: // $@46: %empty
#line 1190 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2195 "dhcp6_parser.cc"
    break;

  case 292: // key_file: "key-file" $@46 ":" "constant string"
#line 1193 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2205 "dhcp6_parser.cc"
    break;

  case 293: // $@47: %empty
#line 1199 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2214 "dhcp6_parser.cc"
    break;

  case 294: // cipher_list: "cipher-list" $@47 ":" "constant string"
#line 1202 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2224 "dhcp6_parser.cc"
    break;

  case 295: // $@48: %empty
#line 1208 "dhcp6_parser.yy"
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
#line 1214 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2245 "dhcp6_parser.cc"
    break;

  case 299: // sanity_checks_params: sanity_checks_params ","
#line 1221 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2253 "dhcp6_parser.cc"
    break;

  case 302: // $@49: %empty
#line 1230 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2262 "dhcp6_parser.cc"
    break;

  case 303: // lease_checks: "lease-checks" $@49 ":" "constant string"
#line 1233 "dhcp6_parser.yy"
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
#line 1249 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2291 "dhcp6_parser.cc"
    break;

  case 305: // extended_info_checks: "extended-info-checks" $@50 ":" "constant string"
#line 1252 "dhcp6_parser.yy"
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
#line 1267 "dhcp6_parser.yy"
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
#line 1273 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2331 "dhcp6_parser.cc"
    break;

  case 310: // mac_sources_list: mac_sources_list ","
#line 1280 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2339 "dhcp6_parser.cc"
    break;

  case 313: // duid_id: "duid"
#line 1289 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2348 "dhcp6_parser.cc"
    break;

  case 314: // string_id: "constant string"
#line 1294 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2357 "dhcp6_parser.cc"
    break;

  case 315: // $@52: %empty
#line 1299 "dhcp6_parser.yy"
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
#line 1305 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2378 "dhcp6_parser.cc"
    break;

  case 319: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1312 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2386 "dhcp6_parser.cc"
    break;

  case 323: // hw_address_id: "hw-address"
#line 1322 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2395 "dhcp6_parser.cc"
    break;

  case 324: // flex_id: "flex-id"
#line 1327 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2404 "dhcp6_parser.cc"
    break;

  case 325: // $@53: %empty
#line 1334 "dhcp6_parser.yy"
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
#line 1340 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2425 "dhcp6_parser.cc"
    break;

  case 327: // $@54: %empty
#line 1347 "dhcp6_parser.yy"
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
#line 1353 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2448 "dhcp6_parser.cc"
    break;

  case 331: // multi_threading_params: multi_threading_params ","
#line 1362 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2456 "dhcp6_parser.cc"
    break;

  case 338: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1375 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2466 "dhcp6_parser.cc"
    break;

  case 339: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1381 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2476 "dhcp6_parser.cc"
    break;

  case 340: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1387 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2486 "dhcp6_parser.cc"
    break;

  case 341: // $@55: %empty
#line 1393 "dhcp6_parser.yy"
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
#line 1399 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2507 "dhcp6_parser.cc"
    break;

  case 347: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1410 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2515 "dhcp6_parser.cc"
    break;

  case 348: // $@56: %empty
#line 1415 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2525 "dhcp6_parser.cc"
    break;

  case 349: // hooks_library: "{" $@56 hooks_params "}"
#line 1419 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2535 "dhcp6_parser.cc"
    break;

  case 350: // $@57: %empty
#line 1425 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2545 "dhcp6_parser.cc"
    break;

  case 351: // sub_hooks_library: "{" $@57 hooks_params "}"
#line 1429 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2555 "dhcp6_parser.cc"
    break;

  case 354: // hooks_params: hooks_params ","
#line 1437 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2563 "dhcp6_parser.cc"
    break;

  case 358: // $@58: %empty
#line 1447 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2572 "dhcp6_parser.cc"
    break;

  case 359: // library: "library" $@58 ":" "constant string"
#line 1450 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2582 "dhcp6_parser.cc"
    break;

  case 360: // $@59: %empty
#line 1456 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2591 "dhcp6_parser.cc"
    break;

  case 361: // parameters: "parameters" $@59 ":" map_value
#line 1459 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2600 "dhcp6_parser.cc"
    break;

  case 362: // $@60: %empty
#line 1465 "dhcp6_parser.yy"
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
#line 1471 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2622 "dhcp6_parser.cc"
    break;

  case 366: // expired_leases_params: expired_leases_params ","
#line 1479 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2630 "dhcp6_parser.cc"
    break;

  case 373: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1492 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2640 "dhcp6_parser.cc"
    break;

  case 374: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1498 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2650 "dhcp6_parser.cc"
    break;

  case 375: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1504 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2660 "dhcp6_parser.cc"
    break;

  case 376: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1510 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2670 "dhcp6_parser.cc"
    break;

  case 377: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1516 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2680 "dhcp6_parser.cc"
    break;

  case 378: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1522 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2690 "dhcp6_parser.cc"
    break;

  case 379: // $@61: %empty
#line 1531 "dhcp6_parser.yy"
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
#line 1537 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2711 "dhcp6_parser.cc"
    break;

  case 385: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1551 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2719 "dhcp6_parser.cc"
    break;

  case 386: // $@62: %empty
#line 1560 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2729 "dhcp6_parser.cc"
    break;

  case 387: // subnet6: "{" $@62 subnet6_params "}"
#line 1564 "dhcp6_parser.yy"
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
#line 1586 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2765 "dhcp6_parser.cc"
    break;

  case 389: // sub_subnet6: "{" $@63 subnet6_params "}"
#line 1590 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2775 "dhcp6_parser.cc"
    break;

  case 392: // subnet6_params: subnet6_params ","
#line 1599 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2783 "dhcp6_parser.cc"
    break;

  case 440: // $@64: %empty
#line 1654 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2792 "dhcp6_parser.cc"
    break;

  case 441: // subnet: "subnet" $@64 ":" "constant string"
#line 1657 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2802 "dhcp6_parser.cc"
    break;

  case 442: // $@65: %empty
#line 1663 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2811 "dhcp6_parser.cc"
    break;

  case 443: // interface: "interface" $@65 ":" "constant string"
#line 1666 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2821 "dhcp6_parser.cc"
    break;

  case 444: // $@66: %empty
#line 1672 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2830 "dhcp6_parser.cc"
    break;

  case 445: // interface_id: "interface-id" $@66 ":" "constant string"
#line 1675 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2840 "dhcp6_parser.cc"
    break;

  case 446: // $@67: %empty
#line 1681 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2849 "dhcp6_parser.cc"
    break;

  case 447: // client_class: "client-class" $@67 ":" "constant string"
#line 1684 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2859 "dhcp6_parser.cc"
    break;

  case 448: // $@68: %empty
#line 1690 "dhcp6_parser.yy"
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
#line 1696 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2880 "dhcp6_parser.cc"
    break;

  case 450: // reservations_global: "reservations-global" ":" "boolean"
#line 1701 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2890 "dhcp6_parser.cc"
    break;

  case 451: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1707 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2900 "dhcp6_parser.cc"
    break;

  case 452: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1713 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2910 "dhcp6_parser.cc"
    break;

  case 453: // $@69: %empty
#line 1719 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2919 "dhcp6_parser.cc"
    break;

  case 454: // reservation_mode: "reservation-mode" $@69 ":" hr_mode
#line 1722 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2928 "dhcp6_parser.cc"
    break;

  case 455: // hr_mode: "disabled"
#line 1727 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2934 "dhcp6_parser.cc"
    break;

  case 456: // hr_mode: "out-of-pool"
#line 1728 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2940 "dhcp6_parser.cc"
    break;

  case 457: // hr_mode: "global"
#line 1729 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2946 "dhcp6_parser.cc"
    break;

  case 458: // hr_mode: "all"
#line 1730 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2952 "dhcp6_parser.cc"
    break;

  case 459: // id: "id" ":" "integer"
#line 1733 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2962 "dhcp6_parser.cc"
    break;

  case 460: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1739 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2972 "dhcp6_parser.cc"
    break;

  case 461: // $@70: %empty
#line 1747 "dhcp6_parser.yy"
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
#line 1753 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2993 "dhcp6_parser.cc"
    break;

  case 467: // shared_networks_list: shared_networks_list ","
#line 1766 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3001 "dhcp6_parser.cc"
    break;

  case 468: // $@71: %empty
#line 1771 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3011 "dhcp6_parser.cc"
    break;

  case 469: // shared_network: "{" $@71 shared_network_params "}"
#line 1775 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3019 "dhcp6_parser.cc"
    break;

  case 472: // shared_network_params: shared_network_params ","
#line 1781 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3027 "dhcp6_parser.cc"
    break;

  case 517: // $@72: %empty
#line 1836 "dhcp6_parser.yy"
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
#line 1842 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3048 "dhcp6_parser.cc"
    break;

  case 519: // $@73: %empty
#line 1850 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3057 "dhcp6_parser.cc"
    break;

  case 520: // sub_option_def_list: "{" $@73 option_def_list "}"
#line 1853 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 3065 "dhcp6_parser.cc"
    break;

  case 525: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1865 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3073 "dhcp6_parser.cc"
    break;

  case 526: // $@74: %empty
#line 1872 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3083 "dhcp6_parser.cc"
    break;

  case 527: // option_def_entry: "{" $@74 option_def_params "}"
#line 1876 "dhcp6_parser.yy"
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
#line 1887 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3105 "dhcp6_parser.cc"
    break;

  case 529: // sub_option_def: "{" $@75 option_def_params "}"
#line 1891 "dhcp6_parser.yy"
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
#line 1907 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3125 "dhcp6_parser.cc"
    break;

  case 546: // code: "code" ":" "integer"
#line 1926 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3135 "dhcp6_parser.cc"
    break;

  case 548: // $@76: %empty
#line 1934 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3144 "dhcp6_parser.cc"
    break;

  case 549: // option_def_type: "type" $@76 ":" "constant string"
#line 1937 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3154 "dhcp6_parser.cc"
    break;

  case 550: // $@77: %empty
#line 1943 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3163 "dhcp6_parser.cc"
    break;

  case 551: // option_def_record_types: "record-types" $@77 ":" "constant string"
#line 1946 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3173 "dhcp6_parser.cc"
    break;

  case 552: // $@78: %empty
#line 1952 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3182 "dhcp6_parser.cc"
    break;

  case 553: // space: "space" $@78 ":" "constant string"
#line 1955 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3192 "dhcp6_parser.cc"
    break;

  case 555: // $@79: %empty
#line 1963 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3201 "dhcp6_parser.cc"
    break;

  case 556: // option_def_encapsulate: "encapsulate" $@79 ":" "constant string"
#line 1966 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3211 "dhcp6_parser.cc"
    break;

  case 557: // option_def_array: "array" ":" "boolean"
#line 1972 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3221 "dhcp6_parser.cc"
    break;

  case 558: // $@80: %empty
#line 1982 "dhcp6_parser.yy"
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
#line 1988 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3242 "dhcp6_parser.cc"
    break;

  case 564: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2003 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3250 "dhcp6_parser.cc"
    break;

  case 565: // $@81: %empty
#line 2010 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3260 "dhcp6_parser.cc"
    break;

  case 566: // option_data_entry: "{" $@81 option_data_params "}"
#line 2014 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3269 "dhcp6_parser.cc"
    break;

  case 567: // $@82: %empty
#line 2022 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3279 "dhcp6_parser.cc"
    break;

  case 568: // sub_option_data: "{" $@82 option_data_params "}"
#line 2026 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3288 "dhcp6_parser.cc"
    break;

  case 573: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2042 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3296 "dhcp6_parser.cc"
    break;

  case 585: // $@83: %empty
#line 2063 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3305 "dhcp6_parser.cc"
    break;

  case 586: // option_data_data: "data" $@83 ":" "constant string"
#line 2066 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3315 "dhcp6_parser.cc"
    break;

  case 589: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2076 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3325 "dhcp6_parser.cc"
    break;

  case 590: // option_data_always_send: "always-send" ":" "boolean"
#line 2082 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3335 "dhcp6_parser.cc"
    break;

  case 591: // option_data_never_send: "never-send" ":" "boolean"
#line 2088 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3345 "dhcp6_parser.cc"
    break;

  case 592: // $@84: %empty
#line 2097 "dhcp6_parser.yy"
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
#line 2103 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3366 "dhcp6_parser.cc"
    break;

  case 598: // not_empty_pools_list: not_empty_pools_list ","
#line 2116 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3374 "dhcp6_parser.cc"
    break;

  case 599: // $@85: %empty
#line 2121 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3384 "dhcp6_parser.cc"
    break;

  case 600: // pool_list_entry: "{" $@85 pool_params "}"
#line 2125 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3394 "dhcp6_parser.cc"
    break;

  case 601: // $@86: %empty
#line 2131 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3404 "dhcp6_parser.cc"
    break;

  case 602: // sub_pool6: "{" $@86 pool_params "}"
#line 2135 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3414 "dhcp6_parser.cc"
    break;

  case 605: // pool_params: pool_params ","
#line 2143 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3422 "dhcp6_parser.cc"
    break;

  case 614: // $@87: %empty
#line 2158 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3431 "dhcp6_parser.cc"
    break;

  case 615: // pool_entry: "pool" $@87 ":" "constant string"
#line 2161 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3441 "dhcp6_parser.cc"
    break;

  case 616: // pool_id: "pool-id" ":" "integer"
#line 2167 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3451 "dhcp6_parser.cc"
    break;

  case 617: // $@88: %empty
#line 2173 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3459 "dhcp6_parser.cc"
    break;

  case 618: // user_context: "user-context" $@88 ":" map_value
#line 2175 "dhcp6_parser.yy"
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
#line 2198 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3494 "dhcp6_parser.cc"
    break;

  case 620: // comment: "comment" $@89 ":" "constant string"
#line 2200 "dhcp6_parser.yy"
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
#line 2228 "dhcp6_parser.yy"
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
#line 2234 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3544 "dhcp6_parser.cc"
    break;

  case 627: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2247 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3552 "dhcp6_parser.cc"
    break;

  case 628: // $@91: %empty
#line 2252 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3562 "dhcp6_parser.cc"
    break;

  case 629: // pd_pool_entry: "{" $@91 pd_pool_params "}"
#line 2256 "dhcp6_parser.yy"
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
#line 2264 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3584 "dhcp6_parser.cc"
    break;

  case 631: // sub_pd_pool: "{" $@92 pd_pool_params "}"
#line 2268 "dhcp6_parser.yy"
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
#line 2278 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3604 "dhcp6_parser.cc"
    break;

  case 646: // $@93: %empty
#line 2296 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3613 "dhcp6_parser.cc"
    break;

  case 647: // pd_prefix: "prefix" $@93 ":" "constant string"
#line 2299 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3623 "dhcp6_parser.cc"
    break;

  case 648: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2305 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3633 "dhcp6_parser.cc"
    break;

  case 649: // $@94: %empty
#line 2311 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3642 "dhcp6_parser.cc"
    break;

  case 650: // excluded_prefix: "excluded-prefix" $@94 ":" "constant string"
#line 2314 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3652 "dhcp6_parser.cc"
    break;

  case 651: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2320 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3662 "dhcp6_parser.cc"
    break;

  case 652: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2326 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3672 "dhcp6_parser.cc"
    break;

  case 653: // $@95: %empty
#line 2335 "dhcp6_parser.yy"
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
#line 2341 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3693 "dhcp6_parser.cc"
    break;

  case 659: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2352 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3701 "dhcp6_parser.cc"
    break;

  case 660: // $@96: %empty
#line 2357 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3711 "dhcp6_parser.cc"
    break;

  case 661: // reservation: "{" $@96 reservation_params "}"
#line 2361 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3720 "dhcp6_parser.cc"
    break;

  case 662: // $@97: %empty
#line 2366 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3730 "dhcp6_parser.cc"
    break;

  case 663: // sub_reservation: "{" $@97 reservation_params "}"
#line 2370 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3739 "dhcp6_parser.cc"
    break;

  case 668: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2381 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3747 "dhcp6_parser.cc"
    break;

  case 680: // $@98: %empty
#line 2400 "dhcp6_parser.yy"
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
#line 2406 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3768 "dhcp6_parser.cc"
    break;

  case 682: // $@99: %empty
#line 2411 "dhcp6_parser.yy"
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
#line 2417 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3789 "dhcp6_parser.cc"
    break;

  case 684: // $@100: %empty
#line 2422 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3798 "dhcp6_parser.cc"
    break;

  case 685: // duid: "duid" $@100 ":" "constant string"
#line 2425 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3808 "dhcp6_parser.cc"
    break;

  case 686: // $@101: %empty
#line 2431 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3817 "dhcp6_parser.cc"
    break;

  case 687: // hw_address: "hw-address" $@101 ":" "constant string"
#line 2434 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3827 "dhcp6_parser.cc"
    break;

  case 688: // $@102: %empty
#line 2440 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3836 "dhcp6_parser.cc"
    break;

  case 689: // hostname: "hostname" $@102 ":" "constant string"
#line 2443 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3846 "dhcp6_parser.cc"
    break;

  case 690: // $@103: %empty
#line 2449 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3855 "dhcp6_parser.cc"
    break;

  case 691: // flex_id_value: "flex-id" $@103 ":" "constant string"
#line 2452 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3865 "dhcp6_parser.cc"
    break;

  case 692: // $@104: %empty
#line 2458 "dhcp6_parser.yy"
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
#line 2464 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3886 "dhcp6_parser.cc"
    break;

  case 694: // $@105: %empty
#line 2472 "dhcp6_parser.yy"
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
#line 2478 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3907 "dhcp6_parser.cc"
    break;

  case 698: // $@106: %empty
#line 2487 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3916 "dhcp6_parser.cc"
    break;

  case 699: // ip_address: "ip-address" $@106 ":" "constant string"
#line 2490 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3926 "dhcp6_parser.cc"
    break;

  case 700: // $@107: %empty
#line 2499 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3938 "dhcp6_parser.cc"
    break;

  case 701: // client_classes: "client-classes" $@107 ":" "[" client_classes_list "]"
#line 2505 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3947 "dhcp6_parser.cc"
    break;

  case 704: // client_classes_list: client_classes_list ","
#line 2512 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3955 "dhcp6_parser.cc"
    break;

  case 705: // $@108: %empty
#line 2517 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3965 "dhcp6_parser.cc"
    break;

  case 706: // client_class_entry: "{" $@108 client_class_params "}"
#line 2521 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3975 "dhcp6_parser.cc"
    break;

  case 711: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2533 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3983 "dhcp6_parser.cc"
    break;

  case 727: // $@109: %empty
#line 2556 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3992 "dhcp6_parser.cc"
    break;

  case 728: // client_class_test: "test" $@109 ":" "constant string"
#line 2559 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4002 "dhcp6_parser.cc"
    break;

  case 729: // $@110: %empty
#line 2565 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4011 "dhcp6_parser.cc"
    break;

  case 730: // client_class_template_test: "template-test" $@110 ":" "constant string"
#line 2568 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4021 "dhcp6_parser.cc"
    break;

  case 731: // only_if_required: "only-if-required" ":" "boolean"
#line 2574 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4031 "dhcp6_parser.cc"
    break;

  case 732: // $@111: %empty
#line 2583 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 4043 "dhcp6_parser.cc"
    break;

  case 733: // server_id: "server-id" $@111 ":" "{" server_id_params "}"
#line 2589 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4054 "dhcp6_parser.cc"
    break;

  case 736: // server_id_params: server_id_params ","
#line 2598 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4062 "dhcp6_parser.cc"
    break;

  case 746: // $@112: %empty
#line 2614 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 4071 "dhcp6_parser.cc"
    break;

  case 747: // server_id_type: "type" $@112 ":" duid_type
#line 2617 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4080 "dhcp6_parser.cc"
    break;

  case 748: // duid_type: "LLT"
#line 2622 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4086 "dhcp6_parser.cc"
    break;

  case 749: // duid_type: "EN"
#line 2623 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4092 "dhcp6_parser.cc"
    break;

  case 750: // duid_type: "LL"
#line 2624 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4098 "dhcp6_parser.cc"
    break;

  case 751: // htype: "htype" ":" "integer"
#line 2627 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4108 "dhcp6_parser.cc"
    break;

  case 752: // $@113: %empty
#line 2633 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4117 "dhcp6_parser.cc"
    break;

  case 753: // identifier: "identifier" $@113 ":" "constant string"
#line 2636 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4127 "dhcp6_parser.cc"
    break;

  case 754: // time: "time" ":" "integer"
#line 2642 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4137 "dhcp6_parser.cc"
    break;

  case 755: // enterprise_id: "enterprise-id" ":" "integer"
#line 2648 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4147 "dhcp6_parser.cc"
    break;

  case 756: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2656 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4157 "dhcp6_parser.cc"
    break;

  case 757: // $@114: %empty
#line 2664 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4169 "dhcp6_parser.cc"
    break;

  case 758: // control_socket: "control-socket" $@114 ":" "{" control_socket_params "}"
#line 2670 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4178 "dhcp6_parser.cc"
    break;

  case 761: // control_socket_params: control_socket_params ","
#line 2677 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4186 "dhcp6_parser.cc"
    break;

  case 767: // $@115: %empty
#line 2689 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4195 "dhcp6_parser.cc"
    break;

  case 768: // socket_type: "socket-type" $@115 ":" "constant string"
#line 2692 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 4205 "dhcp6_parser.cc"
    break;

  case 769: // $@116: %empty
#line 2698 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4214 "dhcp6_parser.cc"
    break;

  case 770: // socket_name: "socket-name" $@116 ":" "constant string"
#line 2701 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4224 "dhcp6_parser.cc"
    break;

  case 771: // $@117: %empty
#line 2710 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4236 "dhcp6_parser.cc"
    break;

  case 772: // dhcp_queue_control: "dhcp-queue-control" $@117 ":" "{" queue_control_params "}"
#line 2716 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4247 "dhcp6_parser.cc"
    break;

  case 775: // queue_control_params: queue_control_params ","
#line 2725 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4255 "dhcp6_parser.cc"
    break;

  case 782: // enable_queue: "enable-queue" ":" "boolean"
#line 2738 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4265 "dhcp6_parser.cc"
    break;

  case 783: // $@118: %empty
#line 2744 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4274 "dhcp6_parser.cc"
    break;

  case 784: // queue_type: "queue-type" $@118 ":" "constant string"
#line 2747 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4284 "dhcp6_parser.cc"
    break;

  case 785: // capacity: "capacity" ":" "integer"
#line 2753 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4294 "dhcp6_parser.cc"
    break;

  case 786: // $@119: %empty
#line 2759 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4303 "dhcp6_parser.cc"
    break;

  case 787: // arbitrary_map_entry: "constant string" $@119 ":" value
#line 2762 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4312 "dhcp6_parser.cc"
    break;

  case 788: // $@120: %empty
#line 2769 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4324 "dhcp6_parser.cc"
    break;

  case 789: // dhcp_ddns: "dhcp-ddns" $@120 ":" "{" dhcp_ddns_params "}"
#line 2775 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4335 "dhcp6_parser.cc"
    break;

  case 790: // $@121: %empty
#line 2782 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4345 "dhcp6_parser.cc"
    break;

  case 791: // sub_dhcp_ddns: "{" $@121 dhcp_ddns_params "}"
#line 2786 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4355 "dhcp6_parser.cc"
    break;

  case 794: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2794 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4363 "dhcp6_parser.cc"
    break;

  case 813: // enable_updates: "enable-updates" ":" "boolean"
#line 2819 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4373 "dhcp6_parser.cc"
    break;

  case 814: // $@122: %empty
#line 2826 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4382 "dhcp6_parser.cc"
    break;

  case 815: // dep_qualifying_suffix: "qualifying-suffix" $@122 ":" "constant string"
#line 2829 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4392 "dhcp6_parser.cc"
    break;

  case 816: // $@123: %empty
#line 2835 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4401 "dhcp6_parser.cc"
    break;

  case 817: // server_ip: "server-ip" $@123 ":" "constant string"
#line 2838 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4411 "dhcp6_parser.cc"
    break;

  case 818: // server_port: "server-port" ":" "integer"
#line 2844 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4421 "dhcp6_parser.cc"
    break;

  case 819: // $@124: %empty
#line 2850 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4430 "dhcp6_parser.cc"
    break;

  case 820: // sender_ip: "sender-ip" $@124 ":" "constant string"
#line 2853 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4440 "dhcp6_parser.cc"
    break;

  case 821: // sender_port: "sender-port" ":" "integer"
#line 2859 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4450 "dhcp6_parser.cc"
    break;

  case 822: // max_queue_size: "max-queue-size" ":" "integer"
#line 2865 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4460 "dhcp6_parser.cc"
    break;

  case 823: // $@125: %empty
#line 2871 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4469 "dhcp6_parser.cc"
    break;

  case 824: // ncr_protocol: "ncr-protocol" $@125 ":" ncr_protocol_value
#line 2874 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4478 "dhcp6_parser.cc"
    break;

  case 825: // ncr_protocol_value: "UDP"
#line 2880 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4484 "dhcp6_parser.cc"
    break;

  case 826: // ncr_protocol_value: "TCP"
#line 2881 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4490 "dhcp6_parser.cc"
    break;

  case 827: // $@126: %empty
#line 2884 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4499 "dhcp6_parser.cc"
    break;

  case 828: // ncr_format: "ncr-format" $@126 ":" "JSON"
#line 2887 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4509 "dhcp6_parser.cc"
    break;

  case 829: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2894 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4519 "dhcp6_parser.cc"
    break;

  case 830: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2901 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4529 "dhcp6_parser.cc"
    break;

  case 831: // $@127: %empty
#line 2908 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4538 "dhcp6_parser.cc"
    break;

  case 832: // dep_replace_client_name: "replace-client-name" $@127 ":" ddns_replace_client_name_value
#line 2911 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4547 "dhcp6_parser.cc"
    break;

  case 833: // $@128: %empty
#line 2917 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4556 "dhcp6_parser.cc"
    break;

  case 834: // dep_generated_prefix: "generated-prefix" $@128 ":" "constant string"
#line 2920 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4566 "dhcp6_parser.cc"
    break;

  case 835: // $@129: %empty
#line 2927 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4575 "dhcp6_parser.cc"
    break;

  case 836: // dep_hostname_char_set: "hostname-char-set" $@129 ":" "constant string"
#line 2930 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4585 "dhcp6_parser.cc"
    break;

  case 837: // $@130: %empty
#line 2937 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4594 "dhcp6_parser.cc"
    break;

  case 838: // dep_hostname_char_replacement: "hostname-char-replacement" $@130 ":" "constant string"
#line 2940 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4604 "dhcp6_parser.cc"
    break;

  case 839: // $@131: %empty
#line 2949 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4616 "dhcp6_parser.cc"
    break;

  case 840: // config_control: "config-control" $@131 ":" "{" config_control_params "}"
#line 2955 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4626 "dhcp6_parser.cc"
    break;

  case 841: // $@132: %empty
#line 2961 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4636 "dhcp6_parser.cc"
    break;

  case 842: // sub_config_control: "{" $@132 config_control_params "}"
#line 2965 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4645 "dhcp6_parser.cc"
    break;

  case 845: // config_control_params: config_control_params ","
#line 2973 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4653 "dhcp6_parser.cc"
    break;

  case 848: // $@133: %empty
#line 2983 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4665 "dhcp6_parser.cc"
    break;

  case 849: // config_databases: "config-databases" $@133 ":" "[" database_list "]"
#line 2989 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4674 "dhcp6_parser.cc"
    break;

  case 850: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2994 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4684 "dhcp6_parser.cc"
    break;

  case 851: // $@134: %empty
#line 3002 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4696 "dhcp6_parser.cc"
    break;

  case 852: // loggers: "loggers" $@134 ":" "[" loggers_entries "]"
#line 3008 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4705 "dhcp6_parser.cc"
    break;

  case 855: // loggers_entries: loggers_entries ","
#line 3017 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4713 "dhcp6_parser.cc"
    break;

  case 856: // $@135: %empty
#line 3023 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4723 "dhcp6_parser.cc"
    break;

  case 857: // logger_entry: "{" $@135 logger_params "}"
#line 3027 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4731 "dhcp6_parser.cc"
    break;

  case 860: // logger_params: logger_params ","
#line 3033 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4739 "dhcp6_parser.cc"
    break;

  case 868: // debuglevel: "debuglevel" ":" "integer"
#line 3047 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4749 "dhcp6_parser.cc"
    break;

  case 869: // $@136: %empty
#line 3053 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4758 "dhcp6_parser.cc"
    break;

  case 870: // severity: "severity" $@136 ":" "constant string"
#line 3056 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4768 "dhcp6_parser.cc"
    break;

  case 871: // $@137: %empty
#line 3062 "dhcp6_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4780 "dhcp6_parser.cc"
    break;

  case 872: // output_options_list: "output-options" $@137 ":" "[" output_options_list_content "]"
#line 3068 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4789 "dhcp6_parser.cc"
    break;

  case 875: // output_options_list_content: output_options_list_content ","
#line 3075 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4797 "dhcp6_parser.cc"
    break;

  case 876: // $@138: %empty
#line 3080 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4807 "dhcp6_parser.cc"
    break;

  case 877: // output_entry: "{" $@138 output_params_list "}"
#line 3084 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4815 "dhcp6_parser.cc"
    break;

  case 880: // output_params_list: output_params_list ","
#line 3090 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4823 "dhcp6_parser.cc"
    break;

  case 886: // $@139: %empty
#line 3102 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4832 "dhcp6_parser.cc"
    break;

  case 887: // output: "output" $@139 ":" "constant string"
#line 3105 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4842 "dhcp6_parser.cc"
    break;

  case 888: // flush: "flush" ":" "boolean"
#line 3111 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4852 "dhcp6_parser.cc"
    break;

  case 889: // maxsize: "maxsize" ":" "integer"
#line 3117 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4862 "dhcp6_parser.cc"
    break;

  case 890: // maxver: "maxver" ":" "integer"
#line 3123 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4872 "dhcp6_parser.cc"
    break;

  case 891: // $@140: %empty
#line 3129 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4881 "dhcp6_parser.cc"
    break;

  case 892: // pattern: "pattern" $@140 ":" "constant string"
#line 3132 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4891 "dhcp6_parser.cc"
    break;

  case 893: // $@141: %empty
#line 3138 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4903 "dhcp6_parser.cc"
    break;

  case 894: // compatibility: "compatibility" $@141 ":" "{" compatibility_params "}"
#line 3144 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4912 "dhcp6_parser.cc"
    break;

  case 897: // compatibility_params: compatibility_params ","
#line 3151 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4920 "dhcp6_parser.cc"
    break;

  case 900: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3160 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4930 "dhcp6_parser.cc"
    break;


#line 4934 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1047;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     637, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047,    53,    26,    29,    48,    70,
      72,    93,   108,   114,   123,   133,   160,   175,   186,   208,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,    26,  -182,
      74,   166,    23,   592,   197,   -12,   214,   169,   102,    87,
    -101,   692,    94, -1047,   266,   275,    85,   272,   290, -1047,
      77, -1047, -1047, -1047, -1047, -1047, -1047, -1047,    98,   292,
     293,   295,   296,   316,   320,   322,   357,   371,   373,   389,
     390,   401, -1047,   403,   404,   431,   449,   450, -1047, -1047,
   -1047,   457,   460,   461,   464, -1047, -1047, -1047,   465, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047,   466,   467,   468, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,   469, -1047,
   -1047, -1047, -1047, -1047, -1047,   471,   473,   475, -1047, -1047,
     476, -1047,    78, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047,   477,   478,   479,   480, -1047,    96, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047,   482,   483, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047,   106, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047,   489, -1047, -1047,
   -1047, -1047,   125, -1047, -1047, -1047, -1047, -1047, -1047,   490,
   -1047,   492,   493, -1047, -1047, -1047, -1047, -1047, -1047,   126,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047,   328,   415, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047,   418, -1047, -1047,
     494, -1047, -1047, -1047,   497, -1047, -1047,   444,   500, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047,   503,   504,   506, -1047, -1047, -1047, -1047,   496,
     509, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047,   140, -1047, -1047, -1047,   510, -1047,
   -1047,   511, -1047,   514,   516, -1047, -1047,   518,   519, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047,   154, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047,   522,   176, -1047, -1047, -1047, -1047,
      26,    26, -1047,   287,   523, -1047, -1047,   528,   532,   533,
     534,   535,   539,   317,   321,   324,   325,   327,   329,   331,
     334,   318,   337,   338,   340,   342,   343,   545,   344,   345,
     335,   351,   352,   553,   563,   570,   354,   356,   359,   361,
     582,   587,   589,   367,   593,   594,   596,   597,   598,   599,
     600,   376,   377,   383,   611,   612,   613,   614,   615,   616,
     618,   619,   625,   405,   626,   627,   630,   632,   633,   634,
     410,   427,   428,   654,   655, -1047,   166, -1047,   666,   445,
     446,   451,   452,    23, -1047,   667,   669,   672,   673,   677,
     455,   458,   684,   685,   686,   592, -1047,   687,   472,   197,
   -1047,   689,   481,   691,   484,   488,   -12, -1047,   694,   706,
     712,   713,   714,   715,   716, -1047,   214, -1047,   717,   725,
     505,   726,   729,   730,   507, -1047,   102,   738,   515,   520,
     521, -1047,    87,   739,   741,     0, -1047,   524,   743,   744,
     525,   750,   542,   543,   751,   767,   555,   558,   768,   786,
     792,   798,   692, -1047,   799,   577,    94, -1047, -1047, -1047,
     801,   702,   470,   800,   802,   803,   804,   636, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047,   580, -1047, -1047, -1047, -1047, -1047,    90,   586,
     595, -1047, -1047, -1047, -1047,   810,   817,   818, -1047,   602,
     603,   262,   819,   823,   605,   341, -1047, -1047, -1047,   827,
     828,   829,   830,   831,   833,   835,   834,   836, -1047,   837,
     838,   839,   840,   638,   639, -1047, -1047, -1047,   858,   859,
   -1047,   862, -1047, -1047, -1047, -1047, -1047,   876,   877,   657,
     658,   659, -1047, -1047,   862,   660,   880, -1047,   664, -1047,
   -1047,   665, -1047,   668, -1047, -1047, -1047,   862,   862,   862,
     670,   671,   674,   678, -1047,   679,   680, -1047,   681,   682,
     683, -1047, -1047,   688, -1047, -1047, -1047, -1047,   690,   823,
   -1047, -1047,   693,   695, -1047,   696, -1047, -1047,   -14,   617,
   -1047, -1047,    90,   697,   698,   699, -1047,   887, -1047, -1047,
      26,   166, -1047,    94,    23,   350,   350,   886, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047,   888,   891,   892,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047,   896, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047,  -107,    26,    24,   136,
     903,   904,   905,   219,    42,   237,    36,   -61,   692, -1047,
   -1047,   906,  -144, -1047, -1047,   908,   910, -1047, -1047, -1047,
   -1047, -1047,   -83, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047,   886, -1047,   248,   258,   330, -1047, -1047, -1047,
   -1047,   916,   922,   923,   924,   925,   926,   928,   929,   930,
     931, -1047,   932,   933, -1047, -1047, -1047, -1047, -1047,   332,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047,   336, -1047,   934,   935, -1047, -1047,   936,
     938, -1047, -1047,   937,   941, -1047, -1047,   939,   943, -1047,
   -1047,   942,   944, -1047, -1047, -1047,    95, -1047, -1047, -1047,
     945, -1047, -1047, -1047,   206, -1047, -1047, -1047, -1047, -1047,
     339, -1047, -1047, -1047, -1047,   210, -1047, -1047,   946,   947,
   -1047, -1047,   948,   950, -1047,   951,   952,   953,   954,   955,
     956,   398, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047,   957,   958,   959, -1047, -1047, -1047, -1047,   412, -1047,
   -1047, -1047, -1047, -1047, -1047,   960,   961,   962, -1047,   413,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047,   414, -1047, -1047, -1047,   963, -1047,   964, -1047, -1047,
   -1047,   416, -1047, -1047, -1047, -1047, -1047,   422, -1047,   244,
   -1047,   965, -1047,   424, -1047, -1047,   723, -1047,   966,   967,
   -1047, -1047,   968,   970, -1047, -1047, -1047,   969, -1047,   972,
   -1047, -1047, -1047,   971,   975,   976,   977,   749,   710,   755,
     742,   756,   757,   758,   759,   760,   761,   986,   762,   766,
     990,   992,   993,   995,   350, -1047, -1047,   350, -1047,   886,
     592, -1047,   888,   102, -1047,   891,    87, -1047,   892,   705,
   -1047,   896,  -107, -1047, -1047,    24, -1047,   998,  1000,   136,
   -1047,   358,   903, -1047,   214, -1047,   904,  -101, -1047,   905,
     778,   780,   781,   784,   787,   791,   219, -1047,  1015,  1016,
     796,   806,   807,    42, -1047,   842,   808,   820,   237, -1047,
    1025,  1027,    36, -1047,   843,  1052,   855,  1063,   -61, -1047,
   -1047,    99,   906, -1047,   856,  -144, -1047, -1047,  1081,  1066,
     197, -1047,   908,   -12, -1047,   910,  1084, -1047, -1047,   283,
     863,   868,   882, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047,   274, -1047, -1047,   895,   918,   920,   921,
   -1047,   425, -1047,   426, -1047,  1146, -1047,  1148, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,   433,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,   940,   949,
   -1047, -1047, -1047,  1153, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047,  1150,  1156, -1047, -1047, -1047,
   -1047, -1047, -1047,  1152, -1047,   434, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047,   192,   973, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047,   974,   978, -1047, -1047,   979, -1047,
      26, -1047, -1047,  1157, -1047, -1047, -1047, -1047, -1047,   440,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,   980,   441,
   -1047,   442, -1047,   981, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047,   705, -1047, -1047, -1047,  1158,  1159,   982,
   -1047,   358, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047,  1160,   983,  1161,    99, -1047, -1047, -1047,
   -1047, -1047, -1047,   987,   989, -1047, -1047,  1162, -1047,   994,
   -1047, -1047, -1047,  1163, -1047, -1047,   273, -1047,    -9,  1163,
   -1047, -1047,  1164,  1165,  1167, -1047,   448, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047,  1168,   996,   985,   991,  1169,    -9,
   -1047,   997, -1047, -1047, -1047,  1001, -1047, -1047, -1047
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
     567,    23,   350,    25,   790,    27,   841,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   664,     0,   530,   569,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   141,   839,   197,   218,   220,   222,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   187,     0,     0,     0,     0,     0,   160,   167,
     169,     0,     0,     0,     0,   379,   517,   558,     0,   190,
     192,   173,   461,   617,   619,   453,     0,     0,     0,   306,
     325,   315,   295,   700,   653,   341,   362,   732,     0,   327,
     757,   771,   788,   180,   182,     0,     0,     0,   851,   893,
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
     582,   358,   360,   355,     0,   352,   356,   357,     0,   814,
     816,     0,   819,     0,     0,   823,   827,     0,     0,   831,
     833,   835,   837,   812,   810,   811,     0,   792,   795,   807,
     796,   797,   798,   799,   800,   801,   802,   803,   804,   805,
     806,   808,   809,   848,     0,     0,   843,   846,   847,    47,
      52,     0,    39,    45,     0,    66,    62,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    60,    71,    68,     0,     0,
       0,     0,     0,   203,   200,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   392,   389,     0,     0,   605,
     602,     0,     0,     0,     0,     0,   634,   631,     0,     0,
       0,     0,     0,     0,     0,   663,   668,   520,     0,     0,
       0,     0,     0,     0,     0,   529,   534,     0,     0,     0,
       0,   568,   573,     0,     0,   354,   351,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   794,   791,     0,     0,   845,   842,    51,    43,
       0,     0,     0,     0,     0,     0,     0,     0,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,     0,   185,   186,   157,   158,   159,     0,     0,
       0,   171,   172,   179,   184,     0,     0,     0,   189,     0,
       0,     0,     0,     0,     0,     0,   450,   451,   452,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   756,     0,
       0,     0,     0,     0,     0,   194,   195,   196,     0,     0,
      70,     0,   214,   215,   216,   217,   202,     0,     0,     0,
       0,     0,   459,   460,     0,     0,     0,   391,     0,   616,
     604,     0,   648,     0,   651,   652,   633,     0,     0,     0,
       0,     0,     0,     0,   667,     0,     0,   546,     0,     0,
       0,   557,   533,     0,   589,   590,   591,   572,     0,     0,
     353,   813,     0,     0,   818,     0,   821,   822,     0,     0,
     829,   830,     0,     0,     0,     0,   793,     0,   850,   844,
       0,     0,   142,     0,     0,     0,     0,   224,   188,   162,
     163,   164,   165,   166,   161,   168,   170,   381,   521,   560,
     191,   193,   175,   176,   177,   178,   174,   463,    40,   618,
     620,   455,   456,   457,   458,   454,     0,    48,     0,     0,
       0,   655,   343,     0,     0,     0,     0,     0,     0,   181,
     183,     0,     0,    53,   213,   594,   623,   441,   443,   445,
     449,   447,     0,   615,   647,   650,   693,   681,   683,   685,
     687,   689,   691,   549,   270,   553,   551,   556,   586,   359,
     361,   815,   817,   820,   825,   826,   824,   828,   832,   834,
     836,   838,   224,    44,     0,     0,     0,   257,   262,   264,
     266,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   279,     0,     0,   287,   289,   291,   293,   256,     0,
     231,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   248,   249,   250,   251,   247,   252,
     253,   254,   255,     0,   229,     0,   225,   226,   386,     0,
     382,   383,   526,     0,   522,   523,   565,     0,   561,   562,
     468,     0,   464,   465,   313,   314,     0,   308,   311,   312,
       0,   323,   324,   320,     0,   317,   321,   322,   302,   304,
       0,   297,   300,   301,   705,     0,   702,   660,     0,   656,
     657,   348,     0,   344,   345,     0,     0,     0,     0,     0,
       0,     0,   364,   367,   368,   369,   370,   371,   372,   746,
     752,     0,     0,     0,   745,   742,   743,   744,     0,   734,
     737,   740,   738,   739,   741,     0,     0,     0,   337,     0,
     329,   332,   333,   334,   335,   336,   767,   769,   766,   764,
     765,     0,   759,   762,   763,     0,   783,     0,   786,   779,
     780,     0,   773,   776,   777,   778,   781,     0,   856,     0,
     853,     0,   899,     0,   895,   898,    55,   599,     0,   595,
     596,   628,     0,   624,   625,   698,   697,     0,   696,     0,
      64,   840,   198,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   233,   219,   221,     0,   223,   228,
       0,   380,   385,   530,   518,   525,   569,   559,   564,     0,
     462,   467,   310,   307,   326,   319,   316,     0,     0,   299,
     296,   707,   704,   701,   664,   654,   659,     0,   342,   347,
       0,     0,     0,     0,     0,     0,   366,   363,     0,     0,
       0,     0,     0,   736,   733,     0,     0,     0,   331,   328,
       0,     0,   761,   758,     0,     0,     0,     0,   775,   772,
     789,     0,   855,   852,     0,   897,   894,    57,     0,    56,
       0,   593,   598,     0,   622,   627,     0,   695,   849,     0,
       0,     0,     0,   268,   271,   272,   273,   274,   275,   276,
     277,   286,   278,     0,   284,   285,     0,     0,     0,     0,
     232,     0,   227,     0,   384,     0,   524,     0,   563,   516,
     487,   488,   489,   491,   492,   493,   477,   478,   496,   497,
     498,   499,   500,   503,   504,   505,   506,   507,   508,   509,
     510,   511,   512,   501,   502,   513,   514,   515,   473,   474,
     475,   476,   485,   486,   482,   483,   484,   481,   490,     0,
     470,   479,   494,   495,   480,   466,   309,   318,     0,     0,
     298,   727,   729,     0,   725,   719,   720,   721,   722,   723,
     724,   726,   716,   717,   718,     0,   708,   709,   712,   713,
     714,   715,   703,     0,   658,     0,   346,   373,   374,   375,
     376,   377,   378,   365,     0,     0,   751,   754,   755,   735,
     338,   339,   340,   330,     0,     0,   760,   782,     0,   785,
       0,   774,   871,     0,   869,   867,   861,   865,   866,     0,
     858,   863,   864,   862,   854,   900,   896,    54,    59,     0,
     597,     0,   626,     0,   259,   260,   261,   258,   263,   265,
     267,   281,   282,   283,   280,   288,   290,   292,   294,   230,
     387,   527,   566,   472,   469,   303,   305,     0,     0,     0,
     706,   711,   661,   349,   748,   749,   750,   747,   753,   768,
     770,   784,   787,     0,     0,     0,   860,   857,    58,   600,
     629,   699,   471,     0,     0,   731,   710,     0,   868,     0,
     859,   728,   730,     0,   870,   876,     0,   873,     0,   875,
     872,   886,     0,     0,     0,   891,     0,   878,   881,   882,
     883,   884,   885,   874,     0,     0,     0,     0,     0,   880,
     877,     0,   888,   889,   890,     0,   879,   887,   892
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047,    -4, -1047,  -602, -1047,
     113, -1047, -1047, -1047, -1047,   387, -1047,  -644, -1047, -1047,
   -1047,   -71, -1047, -1047, -1047, -1047, -1047, -1047, -1047,   429,
     650, -1047, -1047,   -43,   -39,    10,    14,    15,    17,   -24,
     -21,   -17,   -11,    30,    32,    33, -1047,    37,    43,    44,
      47, -1047,   435,    50, -1047,    51, -1047,    62,    63,    64,
   -1047, -1047,    65,    66, -1047,    68, -1047,    69, -1047, -1047,
   -1047, -1047, -1047,    76, -1047,    79, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047,   430,   645, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,   346, -1047,
     120, -1047,  -745,   127, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047,   -41, -1047,  -788, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047,   103, -1047, -1047, -1047, -1047, -1047, -1047, -1047,   111,
    -768, -1047, -1047, -1047, -1047,   110, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047,    88, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047,    97, -1047, -1047, -1047,   100,   604, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047,   101, -1047, -1047, -1047, -1047, -1047,
   -1047, -1046, -1047, -1047, -1047,   128, -1047, -1047, -1047,   131,
     647, -1047, -1047, -1044, -1047, -1043, -1047,    84, -1047,    86,
   -1047,    80,    81,    82,    83, -1047, -1047, -1047, -1042, -1047,
   -1047, -1047, -1047,   122, -1047, -1047,  -119,  1118, -1047, -1047,
   -1047, -1047, -1047,   137, -1047, -1047, -1047,   135, -1047,   646,
   -1047,   -66, -1047, -1047, -1047, -1047, -1047,   -65, -1047, -1047,
   -1047, -1047, -1047,   -16, -1047, -1047, -1047,   141, -1047, -1047,
   -1047,   142, -1047,   621, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047,    89, -1047, -1047, -1047,
      71,   675, -1047, -1047, -1047,   -57, -1047,    -3, -1047, -1047,
   -1047, -1047, -1047,    91, -1047, -1047, -1047,   104,   676, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047,   -45, -1047, -1047, -1047,
     143, -1047, -1047, -1047,   144, -1047,   701,   419, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1040, -1047, -1047, -1047, -1047, -1047, -1047, -1047,   148,
   -1047, -1047, -1047,   -88, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047,   132, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047,   124, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047,   116, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047,   443,   641, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047,   485,   640, -1047, -1047,
   -1047, -1047, -1047, -1047,   117, -1047, -1047,   -96, -1047, -1047,
   -1047, -1047, -1047, -1047,  -115, -1047, -1047,  -134, -1047, -1047,
   -1047, -1047, -1047, -1047, -1047, -1047, -1047, -1047,   129, -1047
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     779,    87,    88,    41,    68,    84,    85,   804,  1016,  1128,
    1129,   868,    43,    70,    90,   454,    91,    45,    71,   162,
     163,   164,   457,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   483,   764,   183,   484,   184,   485,   185,   186,   187,
     496,   776,   188,   189,   518,   190,   519,   191,   192,   193,
     194,   477,   195,   196,   494,   197,   495,   198,   199,   200,
     201,   459,    47,    72,   238,   239,   240,   528,   241,   242,
     243,   244,   202,   460,   203,   461,   204,   462,   895,   896,
     897,  1057,   869,   870,   871,  1033,  1297,   872,  1034,   873,
    1035,   874,  1036,   875,   876,   569,   877,   878,   879,   880,
     881,   882,   883,   884,   885,  1047,  1304,   886,   887,   888,
     889,  1050,   890,  1051,   891,  1052,   892,  1053,   205,   507,
     930,   931,   932,  1077,   933,  1078,   206,   504,   916,   917,
     918,   919,   207,   506,   924,   925,   926,   927,   208,   505,
     209,   514,   979,   980,   981,   982,   983,   210,   510,   942,
     943,   944,  1087,    63,    80,   404,   405,   406,   583,   407,
     584,   211,   511,   951,   952,   953,   954,   955,   956,   957,
     958,   212,   490,   899,   900,   901,  1060,    49,    73,   286,
     287,   288,   537,   289,   538,   290,   539,   291,   543,   292,
     542,   213,   214,   215,   216,   500,   785,   297,   298,   217,
     497,   911,   912,   913,  1069,  1209,  1210,   218,   491,    57,
      77,   903,   904,   905,  1063,    59,    78,   367,   368,   369,
     370,   371,   372,   373,   568,   374,   572,   375,   571,   376,
     377,   573,   378,   219,   492,   907,   908,   909,  1066,    61,
      79,   389,   390,   391,   392,   393,   577,   394,   395,   396,
     397,   398,   300,   535,  1018,  1019,  1020,  1130,    51,    74,
     312,   313,   314,   547,   315,   220,   498,   221,   499,   303,
     536,  1022,  1023,  1024,  1133,    53,    75,   329,   330,   331,
     551,   332,   333,   553,   334,   335,   222,   509,   938,   939,
     940,  1084,    55,    76,   347,   348,   349,   350,   559,   351,
     560,   352,   561,   353,   562,   354,   563,   355,   564,   356,
     558,   305,   544,  1027,  1028,  1136,   223,   508,   935,   936,
    1081,  1235,  1236,  1237,  1238,  1239,  1317,  1240,  1318,  1241,
     224,   512,   968,   969,   970,  1098,  1327,   971,   972,  1099,
     973,   974,   225,   226,   515,   991,   992,   993,  1110,   994,
    1111,   227,   516,  1001,  1002,  1003,  1004,  1115,  1005,  1006,
    1117,   228,   517,    65,    81,   426,   427,   428,   429,   588,
     430,   589,   431,   432,   591,   433,   434,   435,   594,   836,
     436,   595,   437,   438,   439,   598,   440,   599,   441,   600,
     442,   601,   229,   458,    67,    82,   445,   446,   447,   604,
     448,   230,   523,  1009,  1010,  1121,  1279,  1280,  1281,  1282,
    1335,  1283,  1333,  1356,  1357,  1358,  1366,  1367,  1368,  1374,
    1369,  1370,  1371,  1372,  1378,   231,   524,  1013,  1014,  1015
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     161,   237,   257,   308,   323,   343,   965,   365,   385,   403,
     423,   893,    38,   387,   388,   245,   301,   316,   327,   345,
     923,   379,   399,  1199,   424,  1200,  1201,  1208,   304,  1214,
     258,    31,   914,    32,   259,    33,    42,   366,   386,   232,
     233,   234,   235,   236,    86,   401,   402,   133,   134,   264,
     810,   778,   265,    30,   337,    44,   266,   299,   311,   326,
     344,  1025,   267,   816,   817,   818,   959,  1011,   127,   246,
     302,   317,   328,   346,   852,   380,   400,    46,   425,    48,
     455,   526,   160,   260,    89,   456,   527,   261,   262,   451,
     263,   318,   319,   320,   321,   322,   133,   134,  1072,   533,
      50,  1073,   463,   268,   534,   269,   270,   443,   444,   545,
     271,   995,   996,   997,   546,    52,   272,   273,   254,   915,
     274,    54,   255,   275,   276,   160,   358,   778,   549,   556,
      56,   133,   134,   550,   557,   277,   278,   279,   280,   281,
      58,   282,   283,   585,   133,   134,   401,   402,   586,   284,
     133,   134,   285,   293,   294,   295,   296,   602,   309,   324,
     310,   325,   603,   914,   921,   998,   922,    60,   359,   381,
     360,   361,   382,   383,   384,   834,   835,    92,    93,   606,
     359,    94,    62,   359,   607,   360,   361,    95,    96,    97,
     362,   363,   364,    64,  1361,   133,   134,  1362,  1363,  1364,
    1365,   960,   961,   962,   963,   986,   987,   133,   134,  1075,
     133,   134,  1076,  1082,   160,    66,  1083,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,  1122,   126,   160,
    1123,   526,    34,    35,    36,    37,  1030,   128,   129,   130,
     131,   606,   160,   928,   929,   132,  1031,  1199,   160,  1200,
    1201,  1208,   449,  1214,   133,   134,  1359,   127,   450,  1360,
     452,   135,   759,   760,   761,   762,   136,   137,   138,   139,
     140,   141,   142,   453,   127,   143,   464,   465,   306,   466,
     467,  1272,   144,  1273,  1274,   133,   134,   923,  1294,  1295,
    1296,   145,  1161,   160,   146,   965,  1301,  1302,  1303,   763,
     468,   147,   133,   134,   469,   160,   470,   254,   160,   148,
     149,   255,   307,   533,   150,  1054,   565,   151,  1032,  1054,
    1055,   152,  1079,   336,  1056,   133,   134,  1080,  1324,  1325,
    1326,   337,   338,   339,   340,   341,   342,   772,   773,   774,
     775,   471,   153,   154,   155,   156,   157,   158,   945,   946,
     947,   948,   949,   950,   847,   472,   159,   473,   848,   849,
     850,   851,   852,   853,   854,   855,   856,   857,   858,   859,
     860,   861,   160,   474,   475,   862,   863,   864,   865,   866,
     867,  1096,   975,   976,   977,   476,  1097,   478,   479,    98,
      99,   100,   101,   102,   103,  1103,  1108,  1112,   566,  1118,
    1104,  1109,  1113,   160,  1119,   602,   567,  1125,  1054,   545,
    1120,   359,  1126,  1309,  1310,   480,  1313,   585,   127,   359,
     160,  1314,  1323,  1336,   549,   556,   608,   609,  1337,  1339,
    1340,  1379,   575,   481,   482,   161,  1380,   781,   782,   783,
     784,   486,   237,   160,   487,   488,   133,   134,   489,   493,
     501,   502,   503,   513,   257,   520,   245,   521,   308,   522,
     525,   529,   530,   531,   532,   323,   540,   541,   301,  1221,
    1222,  1223,   316,   548,   552,   343,   554,   555,   570,   327,
     304,   574,   258,   576,   581,   365,   259,   578,   579,   345,
     580,   385,   582,   610,   587,   590,   387,   388,   592,   379,
     593,   264,   596,   597,   265,   399,   605,   611,   266,   299,
     246,   423,   612,   311,   267,   366,   613,   614,   615,   616,
     326,   386,   302,   617,   618,   424,   317,   626,   619,   632,
     344,   620,   621,   328,   622,   260,   623,   638,   624,   261,
     262,   625,   263,   346,   635,   627,   628,   639,   629,   630,
     631,   633,   634,   380,   640,   268,   160,   269,   270,   400,
     636,   637,   271,   641,   160,   642,   645,   643,   272,   273,
     644,   646,   274,   647,   648,   275,   276,   649,   650,   425,
     651,   652,   653,   654,   655,   656,   657,   277,   278,   279,
     280,   281,   658,   282,   283,   659,   660,   661,   662,   663,
     664,   284,   665,   666,   285,   293,   294,   295,   296,   667,
     669,   670,   668,   309,   671,   310,   672,   673,   674,   675,
     324,   757,   325,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   676,   677,   678,   679,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     681,   687,   127,   688,   682,   683,   689,   690,   684,   685,
     161,   691,   692,   237,   129,   130,   131,   693,   694,   695,
     696,   698,   247,   701,   248,   703,   752,   245,   707,   699,
     133,   134,   249,   250,   251,   252,   253,   135,   702,   751,
     708,   704,   136,   137,   138,   705,   709,   710,   711,   712,
     713,   715,   254,   964,   978,   988,   255,   423,   144,   716,
     718,  1012,   717,   719,   720,   256,   721,   966,   984,   989,
     999,   424,   723,   728,   724,   729,   843,   732,   733,   725,
     726,   246,   734,   731,   735,   738,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   736,
     737,   739,   742,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   740,   127,   359,   741,   153,   154,
     743,   967,   985,   990,  1000,   425,   744,   129,   130,   131,
     133,   134,   745,   747,   748,   750,   758,   753,   837,   754,
     755,   756,   765,   133,   134,   767,   250,   251,   160,   253,
     135,   766,   768,   769,   777,   136,   137,   138,   770,   771,
      32,   780,   786,   787,   788,   254,   790,   789,   791,   255,
     792,   793,   830,   794,   795,   796,   797,   798,   256,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,   801,   799,   800,   802,   803,   408,   409,
     410,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     420,   805,   806,   807,   808,   809,   811,   812,   421,   422,
     813,   814,   842,   894,   815,   898,   819,   820,   902,   906,
     821,   153,   154,   910,   822,   823,   824,   825,   826,   827,
     934,   937,   941,  1008,   828,  1017,   829,  1021,   160,   831,
    1037,   832,   833,   839,   840,   841,  1038,  1039,  1040,  1041,
    1042,   160,  1043,  1044,  1045,  1046,  1048,  1049,  1059,  1144,
    1058,  1062,  1061,  1064,  1065,  1067,  1068,  1071,  1070,  1127,
    1086,  1074,  1085,  1089,  1088,  1090,  1091,  1092,  1093,  1094,
    1095,  1100,  1101,  1102,  1105,  1106,  1107,  1114,  1116,  1124,
    1132,  1146,  1131,  1135,  1134,  1139,  1143,  1137,  1138,  1140,
    1141,  1142,  1145,  1147,  1148,  1149,  1150,  1151,  1152,   257,
    1153,  1154,   365,  1155,  1156,   385,  1157,  1158,  1169,  1159,
     387,   388,  1218,   301,  1219,  1247,   379,  1248,  1249,   399,
    1224,  1250,  1212,   343,  1251,   304,   403,   258,  1252,  1254,
    1255,   259,   366,  1256,  1233,   386,  1170,   345,  1198,  1264,
    1171,  1265,   964,  1257,  1258,  1261,   264,   978,  1225,   265,
    1231,   988,  1226,   266,   299,  1176,   966,  1262,  1177,   267,
    1275,   984,  1178,  1211,  1012,   989,  1268,   302,  1179,   308,
     380,   999,   323,   400,  1277,  1232,  1213,  1270,   344,  1288,
     260,  1260,  1267,   316,   261,   262,   327,   263,  1234,  1172,
    1276,   346,  1269,  1173,  1174,  1285,  1175,  1287,  1293,  1298,
     268,  1227,   269,   270,  1299,  1228,  1229,   271,  1230,  1180,
     967,  1181,  1182,   272,   273,   985,  1183,   274,  1300,   990,
     275,   276,  1184,  1185,   311,  1000,  1186,   326,  1278,  1187,
    1188,  1305,   277,   278,   279,   280,   281,   317,   282,   283,
     328,  1189,  1190,  1191,  1192,  1193,   284,  1194,  1195,   285,
     293,   294,   295,   296,  1306,  1196,  1307,  1308,  1197,  1204,
    1205,  1206,  1207,  1202,  1311,  1203,  1312,  1319,  1320,  1321,
    1322,  1334,  1343,  1344,  1347,  1349,  1315,  1353,  1375,  1376,
    1355,  1377,  1381,  1385,   920,  1316,   680,   838,   686,  1162,
     844,  1160,  1220,  1216,   846,  1217,  1246,  1245,  1029,   730,
    1164,  1163,   697,  1215,  1342,   357,  1263,  1253,  1165,  1328,
    1329,  1289,  1166,   727,  1330,  1331,  1338,  1341,  1167,  1168,
    1348,  1345,  1383,  1351,   309,  1352,   310,   324,  1384,   325,
    1354,  1290,   722,  1387,   700,  1382,  1292,  1388,  1243,  1244,
    1242,  1026,   706,  1346,  1271,  1259,  1266,  1291,   845,  1284,
    1350,  1007,  1169,   746,  1373,  1386,   749,     0,     0,     0,
    1224,     0,     0,     0,  1286,     0,  1212,     0,     0,     0,
       0,     0,     0,     0,  1233,  1275,  1332,   714,     0,     0,
    1170,     0,  1198,     0,  1171,     0,     0,     0,  1225,  1277,
    1231,     0,  1226,     0,     0,     0,     0,     0,     0,  1176,
       0,     0,  1177,     0,     0,  1276,  1178,  1211,     0,     0,
       0,     0,  1179,     0,     0,  1232,     0,     0,     0,     0,
    1213,     0,     0,     0,     0,     0,     0,     0,  1234,     0,
       0,     0,     0,  1172,     0,     0,     0,  1173,  1174,     0,
    1175,  1227,     0,  1278,     0,  1228,  1229,     0,  1230,     0,
       0,     0,     0,  1180,     0,  1181,  1182,     0,     0,     0,
    1183,     0,     0,     0,     0,     0,  1184,  1185,     0,     0,
    1186,     0,     0,  1187,  1188,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1189,  1190,  1191,  1192,  1193,
       0,  1194,  1195,     0,     0,     0,     0,     0,     0,  1196,
       0,     0,  1197,  1204,  1205,  1206,  1207,  1202,     0,  1203
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,   794,    78,    79,    80,
      81,   756,    16,    79,    79,    72,    73,    74,    75,    76,
     788,    78,    79,  1069,    81,  1069,  1069,  1069,    73,  1069,
      73,     5,   139,     7,    73,     9,     7,    78,    79,    16,
      17,    18,    19,    20,   226,   146,   147,   108,   109,    73,
     694,   653,    73,     0,   137,     7,    73,    73,    74,    75,
      76,   144,    73,   707,   708,   709,    24,   211,    80,    72,
      73,    74,    75,    76,    32,    78,    79,     7,    81,     7,
       3,     3,   226,    73,    10,     8,     8,    73,    73,     4,
      73,   103,   104,   105,   106,   107,   108,   109,     3,     3,
       7,     6,     4,    73,     8,    73,    73,    13,    14,     3,
      73,   172,   173,   174,     8,     7,    73,    73,   130,   226,
      73,     7,   134,    73,    73,   226,    24,   729,     3,     3,
       7,   108,   109,     8,     8,    73,    73,    73,    73,    73,
       7,    73,    73,     3,   108,   109,   146,   147,     8,    73,
     108,   109,    73,    73,    73,    73,    73,     3,    74,    75,
      74,    75,     8,   139,   140,   226,   142,     7,    81,    82,
      83,    84,    85,    86,    87,   189,   190,    11,    12,     3,
      81,    15,     7,    81,     8,    83,    84,    21,    22,    23,
      88,    89,    90,     7,   203,   108,   109,   206,   207,   208,
     209,   159,   160,   161,   162,   169,   170,   108,   109,     3,
     108,   109,     6,     3,   226,     7,     6,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     3,    79,   226,
       6,     3,   226,   227,   228,   229,     8,    91,    92,    93,
      94,     3,   226,   127,   128,    99,     8,  1313,   226,  1313,
    1313,  1313,     6,  1313,   108,   109,     3,    80,     3,     6,
       8,   115,   192,   193,   194,   195,   120,   121,   122,   123,
     124,   125,   126,     3,    80,   129,     4,     4,   101,     4,
       4,   202,   136,   204,   205,   108,   109,  1075,    25,    26,
      27,   145,  1057,   226,   148,  1103,    42,    43,    44,   229,
       4,   155,   108,   109,     4,   226,     4,   130,   226,   163,
     164,   134,   135,     3,   168,     3,     8,   171,     8,     3,
       8,   175,     3,   129,     8,   108,   109,     8,   156,   157,
     158,   137,   138,   139,   140,   141,   142,    95,    96,    97,
      98,     4,   196,   197,   198,   199,   200,   201,   149,   150,
     151,   152,   153,   154,    24,     4,   210,     4,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,   226,     4,     4,    45,    46,    47,    48,    49,
      50,     3,   165,   166,   167,     4,     8,     4,     4,    51,
      52,    53,    54,    55,    56,     3,     3,     3,     3,     3,
       8,     8,     8,   226,     8,     3,     8,     3,     3,     3,
       8,    81,     8,     8,     8,     4,     3,     3,    80,    81,
     226,     8,     8,     3,     3,     3,   450,   451,     8,     8,
       8,     3,     8,     4,     4,   526,     8,   116,   117,   118,
     119,     4,   533,   226,     4,     4,   108,   109,     4,     4,
       4,     4,     4,     4,   545,     4,   533,     4,   549,     4,
       4,     4,     4,     4,     4,   556,     4,     4,   545,   131,
     132,   133,   549,     4,     4,   566,     4,     4,     4,   556,
     545,     4,   545,     3,     8,   576,   545,     4,     4,   566,
       4,   582,     3,   226,     4,     4,   582,   582,     4,   576,
       4,   545,     4,     4,   545,   582,     4,     4,   545,   545,
     533,   602,     4,   549,   545,   576,     4,     4,     4,     4,
     556,   582,   545,     4,   227,   602,   549,   229,   227,     4,
     566,   227,   227,   556,   227,   545,   227,     4,   227,   545,
     545,   227,   545,   566,   229,   228,   228,     4,   228,   227,
     227,   227,   227,   576,     4,   545,   226,   545,   545,   582,
     229,   229,   545,   229,   226,   229,     4,   228,   545,   545,
     229,     4,   545,     4,   227,   545,   545,     4,     4,   602,
       4,     4,     4,     4,     4,   229,   229,   545,   545,   545,
     545,   545,   229,   545,   545,     4,     4,     4,     4,     4,
       4,   545,     4,     4,   545,   545,   545,   545,   545,     4,
       4,     4,   227,   549,     4,   549,     4,     4,     4,   229,
     556,     5,   556,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,   229,   229,     4,     4,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
       4,     4,    80,     4,   229,   229,     4,     4,   227,   227,
     751,     4,   227,   754,    92,    93,    94,   229,     4,     4,
       4,     4,   100,     4,   102,     4,   226,   754,     4,   227,
     108,   109,   110,   111,   112,   113,   114,   115,   227,     7,
       4,   227,   120,   121,   122,   227,     4,     4,     4,     4,
       4,     4,   130,   794,   795,   796,   134,   798,   136,     4,
       4,   802,   227,     4,     4,   143,   229,   794,   795,   796,
     797,   798,     4,     4,   229,     4,   750,     4,     4,   229,
     229,   754,   227,   229,     4,     4,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,   227,
     227,     4,     4,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,   229,    80,    81,   229,   196,   197,
       4,   794,   795,   796,   797,   798,     4,    92,    93,    94,
     108,   109,     4,     4,   227,     4,   226,     7,   191,     7,
       7,     7,   226,   108,   109,     5,   111,   112,   226,   114,
     115,   226,     5,     5,     5,   120,   121,   122,   226,   226,
       7,   226,     5,     5,     5,   130,     5,     7,     5,   134,
       5,     7,   729,     7,     7,     7,     7,     7,   143,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,     5,   226,   226,     7,     5,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,     5,     5,   226,   226,   226,   226,     7,   196,   197,
     226,   226,     5,     7,   226,     7,   226,   226,     7,     7,
     226,   196,   197,     7,   226,   226,   226,   226,   226,   226,
       7,     7,     7,     7,   226,     7,   226,     7,   226,   226,
       4,   226,   226,   226,   226,   226,     4,     4,     4,     4,
       4,   226,     4,     4,     4,     4,     4,     4,     3,   229,
       6,     3,     6,     6,     3,     6,     3,     3,     6,   226,
       3,     6,     6,     3,     6,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       3,   229,     6,     3,     6,     4,   227,     8,     6,     4,
       4,     4,   227,   227,   227,   227,   227,   227,   227,  1060,
       4,   229,  1063,   227,     4,  1066,     4,     4,  1069,     4,
    1066,  1066,     4,  1060,     4,   227,  1063,   227,   227,  1066,
    1081,   227,  1069,  1084,   227,  1060,  1087,  1060,   227,     4,
       4,  1060,  1063,   227,  1081,  1066,  1069,  1084,  1069,     4,
    1069,     4,  1103,   227,   227,   227,  1060,  1108,  1081,  1060,
    1081,  1112,  1081,  1060,  1060,  1069,  1103,   227,  1069,  1060,
    1121,  1108,  1069,  1069,  1125,  1112,     4,  1060,  1069,  1130,
    1063,  1118,  1133,  1066,  1121,  1081,  1069,     4,  1084,     3,
    1060,   229,   229,  1130,  1060,  1060,  1133,  1060,  1081,  1069,
    1121,  1084,   227,  1069,  1069,   229,  1069,     6,     4,   226,
    1060,  1081,  1060,  1060,   226,  1081,  1081,  1060,  1081,  1069,
    1103,  1069,  1069,  1060,  1060,  1108,  1069,  1060,   226,  1112,
    1060,  1060,  1069,  1069,  1130,  1118,  1069,  1133,  1121,  1069,
    1069,   226,  1060,  1060,  1060,  1060,  1060,  1130,  1060,  1060,
    1133,  1069,  1069,  1069,  1069,  1069,  1060,  1069,  1069,  1060,
    1060,  1060,  1060,  1060,   226,  1069,   226,   226,  1069,  1069,
    1069,  1069,  1069,  1069,     8,  1069,     8,     4,     8,     3,
       8,     4,     4,     4,     4,     4,   226,     5,     4,     4,
       7,     4,     4,     4,   787,   226,   526,   742,   533,  1059,
     751,  1054,  1079,  1072,   754,  1075,  1089,  1087,   842,   585,
    1062,  1060,   545,  1071,  1313,    77,  1108,  1096,  1063,   226,
     226,  1130,  1065,   582,   226,   226,   226,   226,  1066,  1068,
     227,   229,   227,   226,  1130,   226,  1130,  1133,   227,  1133,
     226,  1132,   576,   226,   549,   229,  1135,   226,  1084,  1086,
    1082,   812,   556,  1321,  1118,  1103,  1112,  1133,   753,  1122,
    1336,   798,  1313,   602,  1359,  1379,   606,    -1,    -1,    -1,
    1321,    -1,    -1,    -1,  1125,    -1,  1313,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1321,  1336,  1270,   566,    -1,    -1,
    1313,    -1,  1313,    -1,  1313,    -1,    -1,    -1,  1321,  1336,
    1321,    -1,  1321,    -1,    -1,    -1,    -1,    -1,    -1,  1313,
      -1,    -1,  1313,    -1,    -1,  1336,  1313,  1313,    -1,    -1,
      -1,    -1,  1313,    -1,    -1,  1321,    -1,    -1,    -1,    -1,
    1313,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1321,    -1,
      -1,    -1,    -1,  1313,    -1,    -1,    -1,  1313,  1313,    -1,
    1313,  1321,    -1,  1336,    -1,  1321,  1321,    -1,  1321,    -1,
      -1,    -1,    -1,  1313,    -1,  1313,  1313,    -1,    -1,    -1,
    1313,    -1,    -1,    -1,    -1,    -1,  1313,  1313,    -1,    -1,
    1313,    -1,    -1,  1313,  1313,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1313,  1313,  1313,  1313,  1313,
      -1,  1313,  1313,    -1,    -1,    -1,    -1,    -1,    -1,  1313,
      -1,    -1,  1313,  1313,  1313,  1313,  1313,  1313,    -1,  1313
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
       0,     5,     7,     9,   226,   227,   228,   229,   246,   247,
     248,   253,     7,   262,     7,   267,     7,   322,     7,   437,
       7,   518,     7,   535,     7,   552,     7,   469,     7,   475,
       7,   499,     7,   413,     7,   623,     7,   654,   254,   249,
     263,   268,   323,   438,   519,   536,   553,   470,   476,   500,
     414,   624,   655,   246,   255,   256,   226,   251,   252,    10,
     264,   266,    11,    12,    15,    21,    22,    23,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    91,    92,
      93,    94,    99,   108,   109,   115,   120,   121,   122,   123,
     124,   125,   126,   129,   136,   145,   148,   155,   163,   164,
     168,   171,   175,   196,   197,   198,   199,   200,   201,   210,
     226,   261,   269,   270,   271,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   293,   295,   297,   298,   299,   302,   303,
     305,   307,   308,   309,   310,   312,   313,   315,   317,   318,
     319,   320,   332,   334,   336,   378,   386,   392,   398,   400,
     407,   421,   431,   451,   452,   453,   454,   459,   467,   493,
     525,   527,   546,   576,   590,   602,   603,   611,   621,   652,
     661,   685,    16,    17,    18,    19,    20,   261,   324,   325,
     326,   328,   329,   330,   331,   525,   527,   100,   102,   110,
     111,   112,   113,   114,   130,   134,   143,   261,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   287,   288,   289,   290,   293,   295,   297,   298,   299,
     302,   303,   305,   307,   313,   315,   439,   440,   441,   443,
     445,   447,   449,   451,   452,   453,   454,   457,   458,   493,
     512,   525,   527,   529,   546,   571,   101,   135,   261,   447,
     449,   493,   520,   521,   522,   524,   525,   527,   103,   104,
     105,   106,   107,   261,   447,   449,   493,   525,   527,   537,
     538,   539,   541,   542,   544,   545,   129,   137,   138,   139,
     140,   141,   142,   261,   493,   525,   527,   554,   555,   556,
     557,   559,   561,   563,   565,   567,   569,   467,    24,    81,
      83,    84,    88,    89,    90,   261,   354,   477,   478,   479,
     480,   481,   482,   483,   485,   487,   489,   490,   492,   525,
     527,    82,    85,    86,    87,   261,   354,   481,   487,   501,
     502,   503,   504,   505,   507,   508,   509,   510,   511,   525,
     527,   146,   147,   261,   415,   416,   417,   419,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   196,   197,   261,   525,   527,   625,   626,   627,   628,
     630,   632,   633,   635,   636,   637,   640,   642,   643,   644,
     646,   648,   650,    13,    14,   656,   657,   658,   660,     6,
       3,     4,     8,     3,   265,     3,     8,   272,   653,   321,
     333,   335,   337,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   311,     4,     4,
       4,     4,     4,   291,   294,   296,     4,     4,     4,     4,
     432,   468,   494,     4,   314,   316,   300,   460,   526,   528,
     455,     4,     4,     4,   387,   399,   393,   379,   577,   547,
     408,   422,   591,     4,   401,   604,   612,   622,   304,   306,
       4,     4,     4,   662,   686,     4,     3,     8,   327,     4,
       4,     4,     4,     3,     8,   513,   530,   442,   444,   446,
       4,     4,   450,   448,   572,     3,     8,   523,     4,     3,
       8,   540,     4,   543,     4,     4,     3,     8,   570,   558,
     560,   562,   564,   566,   568,     8,     3,     8,   484,   355,
       4,   488,   486,   491,     4,     8,     3,   506,     4,     4,
       4,     8,     3,   418,   420,     3,     8,     4,   629,   631,
       4,   634,     4,     4,   638,   641,     4,     4,   645,   647,
     649,   651,     3,     8,   659,     4,     3,     8,   246,   246,
     226,     4,     4,     4,     4,     4,     4,     4,   227,   227,
     227,   227,   227,   227,   227,   227,   229,   228,   228,   228,
     227,   227,     4,   227,   227,   229,   229,   229,     4,     4,
       4,   229,   229,   228,   229,     4,     4,     4,   227,     4,
       4,     4,     4,     4,     4,     4,   229,   229,   229,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   227,     4,
       4,     4,     4,     4,     4,   229,   229,   229,     4,     4,
     270,     4,   229,   229,   227,   227,   325,     4,     4,     4,
       4,     4,   227,   229,     4,     4,     4,   440,     4,   227,
     521,     4,   227,     4,   227,   227,   538,     4,     4,     4,
       4,     4,     4,     4,   556,     4,     4,   227,     4,     4,
       4,   229,   479,     4,   229,   229,   229,   503,     4,     4,
     416,   229,     4,     4,   227,     4,   227,   227,     4,     4,
     229,   229,     4,     4,     4,     4,   626,     4,   227,   657,
       4,     7,   226,     7,     7,     7,     7,     5,   226,   192,
     193,   194,   195,   229,   292,   226,   226,     5,     5,     5,
     226,   226,    95,    96,    97,    98,   301,     5,   248,   250,
     226,   116,   117,   118,   119,   456,     5,     5,     5,     7,
       5,     5,     5,     7,     7,     7,     7,     7,     7,   226,
     226,     5,     7,     5,   257,     5,     5,   226,   226,   226,
     257,   226,     7,   226,   226,   226,   257,   257,   257,   226,
     226,   226,   226,   226,   226,   226,   226,   226,   226,   226,
     250,   226,   226,   226,   189,   190,   639,   191,   292,   226,
     226,   226,     5,   246,   269,   656,   324,    24,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    45,    46,    47,    48,    49,    50,   261,   342,
     343,   344,   347,   349,   351,   353,   354,   356,   357,   358,
     359,   360,   361,   362,   363,   364,   367,   368,   369,   370,
     372,   374,   376,   342,     7,   338,   339,   340,     7,   433,
     434,   435,     7,   471,   472,   473,     7,   495,   496,   497,
       7,   461,   462,   463,   139,   226,   388,   389,   390,   391,
     255,   140,   142,   390,   394,   395,   396,   397,   127,   128,
     380,   381,   382,   384,     7,   578,   579,     7,   548,   549,
     550,     7,   409,   410,   411,   149,   150,   151,   152,   153,
     154,   423,   424,   425,   426,   427,   428,   429,   430,    24,
     159,   160,   161,   162,   261,   356,   525,   527,   592,   593,
     594,   597,   598,   600,   601,   165,   166,   167,   261,   402,
     403,   404,   405,   406,   525,   527,   169,   170,   261,   525,
     527,   605,   606,   607,   609,   172,   173,   174,   226,   525,
     527,   613,   614,   615,   616,   618,   619,   625,     7,   663,
     664,   211,   261,   687,   688,   689,   258,     7,   514,   515,
     516,     7,   531,   532,   533,   144,   557,   573,   574,   338,
       8,     8,     8,   345,   348,   350,   352,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   365,     4,     4,
     371,   373,   375,   377,     3,     8,     8,   341,     6,     3,
     436,     6,     3,   474,     6,     3,   498,     6,     3,   464,
       6,     3,     3,     6,     6,     3,     6,   383,   385,     3,
       8,   580,     3,     6,   551,     6,     3,   412,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,   595,   599,
       4,     4,     4,     3,     8,     4,     4,     4,     3,     8,
     608,   610,     3,     8,     4,   617,     4,   620,     3,     8,
       8,   665,     3,     6,     4,     3,     8,   226,   259,   260,
     517,     6,     3,   534,     6,     3,   575,     8,     6,     4,
       4,     4,     4,   227,   229,   227,   229,   227,   227,   227,
     227,   227,   227,     4,   229,   227,     4,     4,     4,     4,
     343,   342,   340,   439,   435,   477,   473,   501,   497,   261,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   287,   288,   289,   290,   293,   295,   297,
     298,   299,   302,   303,   305,   307,   313,   315,   354,   431,
     443,   445,   447,   449,   451,   452,   453,   454,   458,   465,
     466,   493,   525,   527,   571,   463,   389,   395,     4,     4,
     381,   131,   132,   133,   261,   273,   274,   275,   276,   277,
     278,   354,   493,   525,   527,   581,   582,   583,   584,   585,
     587,   589,   579,   554,   550,   415,   411,   227,   227,   227,
     227,   227,   227,   424,     4,     4,   227,   227,   227,   593,
     229,   227,   227,   403,     4,     4,   606,   229,     4,   227,
       4,   614,   202,   204,   205,   261,   354,   525,   527,   666,
     667,   668,   669,   671,   664,   229,   688,     6,     3,   520,
     516,   537,   533,     4,    25,    26,    27,   346,   226,   226,
     226,    42,    43,    44,   366,   226,   226,   226,   226,     8,
       8,     8,     8,     3,     8,   226,   226,   586,   588,     4,
       8,     3,     8,     8,   156,   157,   158,   596,   226,   226,
     226,   226,   246,   672,     4,   670,     3,     8,   226,     8,
       8,   226,   466,     4,     4,   229,   583,     4,   227,     4,
     667,   226,   226,     5,   226,     7,   673,   674,   675,     3,
       6,   203,   206,   207,   208,   209,   676,   677,   678,   680,
     681,   682,   683,   674,   679,     4,     4,     4,   684,     3,
       8,     4,   229,   227,   227,     4,   677,   226,   226
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   230,   232,   231,   233,   231,   234,   231,   235,   231,
     236,   231,   237,   231,   238,   231,   239,   231,   240,   231,
     241,   231,   242,   231,   243,   231,   244,   231,   245,   231,
     246,   246,   246,   246,   246,   246,   246,   247,   249,   248,
     250,   251,   251,   252,   252,   252,   254,   253,   255,   255,
     256,   256,   256,   258,   257,   259,   259,   260,   260,   260,
     261,   263,   262,   265,   264,   264,   266,   268,   267,   269,
     269,   269,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   272,   271,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     291,   290,   292,   292,   292,   292,   292,   294,   293,   296,
     295,   297,   298,   300,   299,   301,   301,   301,   301,   302,
     304,   303,   306,   305,   307,   308,   309,   311,   310,   312,
     314,   313,   316,   315,   317,   318,   319,   321,   320,   323,
     322,   324,   324,   324,   325,   325,   325,   325,   325,   325,
     325,   325,   327,   326,   328,   329,   330,   331,   333,   332,
     335,   334,   337,   336,   338,   338,   339,   339,   339,   341,
     340,   342,   342,   342,   343,   343,   343,   343,   343,   343,
     343,   343,   343,   343,   343,   343,   343,   343,   343,   343,
     343,   343,   343,   343,   343,   343,   343,   345,   344,   346,
     346,   346,   348,   347,   350,   349,   352,   351,   353,   355,
     354,   356,   357,   358,   359,   360,   361,   362,   363,   365,
     364,   366,   366,   366,   367,   368,   369,   371,   370,   373,
     372,   375,   374,   377,   376,   379,   378,   380,   380,   380,
     381,   381,   383,   382,   385,   384,   387,   386,   388,   388,
     388,   389,   389,   390,   391,   393,   392,   394,   394,   394,
     395,   395,   395,   396,   397,   399,   398,   401,   400,   402,
     402,   402,   403,   403,   403,   403,   403,   403,   404,   405,
     406,   408,   407,   409,   409,   410,   410,   410,   412,   411,
     414,   413,   415,   415,   415,   415,   416,   416,   418,   417,
     420,   419,   422,   421,   423,   423,   423,   424,   424,   424,
     424,   424,   424,   425,   426,   427,   428,   429,   430,   432,
     431,   433,   433,   434,   434,   434,   436,   435,   438,   437,
     439,   439,   439,   440,   440,   440,   440,   440,   440,   440,
     440,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     440,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     440,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     440,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     442,   441,   444,   443,   446,   445,   448,   447,   450,   449,
     451,   452,   453,   455,   454,   456,   456,   456,   456,   457,
     458,   460,   459,   461,   461,   462,   462,   462,   464,   463,
     465,   465,   465,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   468,   467,   470,
     469,   471,   471,   472,   472,   472,   474,   473,   476,   475,
     477,   477,   478,   478,   478,   479,   479,   479,   479,   479,
     479,   479,   479,   479,   479,   480,   481,   482,   484,   483,
     486,   485,   488,   487,   489,   491,   490,   492,   494,   493,
     495,   495,   496,   496,   496,   498,   497,   500,   499,   501,
     501,   502,   502,   502,   503,   503,   503,   503,   503,   503,
     503,   503,   503,   503,   504,   506,   505,   507,   508,   509,
     510,   511,   513,   512,   514,   514,   515,   515,   515,   517,
     516,   519,   518,   520,   520,   520,   521,   521,   521,   521,
     521,   521,   521,   521,   523,   522,   524,   526,   525,   528,
     527,   530,   529,   531,   531,   532,   532,   532,   534,   533,
     536,   535,   537,   537,   537,   538,   538,   538,   538,   538,
     538,   538,   538,   538,   538,   538,   540,   539,   541,   543,
     542,   544,   545,   547,   546,   548,   548,   549,   549,   549,
     551,   550,   553,   552,   554,   554,   555,   555,   555,   556,
     556,   556,   556,   556,   556,   556,   556,   556,   556,   556,
     558,   557,   560,   559,   562,   561,   564,   563,   566,   565,
     568,   567,   570,   569,   572,   571,   573,   573,   575,   574,
     577,   576,   578,   578,   578,   580,   579,   581,   581,   582,
     582,   582,   583,   583,   583,   583,   583,   583,   583,   583,
     583,   583,   583,   583,   583,   583,   584,   586,   585,   588,
     587,   589,   591,   590,   592,   592,   592,   593,   593,   593,
     593,   593,   593,   593,   593,   593,   595,   594,   596,   596,
     596,   597,   599,   598,   600,   601,   602,   604,   603,   605,
     605,   605,   606,   606,   606,   606,   606,   608,   607,   610,
     609,   612,   611,   613,   613,   613,   614,   614,   614,   614,
     614,   614,   615,   617,   616,   618,   620,   619,   622,   621,
     624,   623,   625,   625,   625,   626,   626,   626,   626,   626,
     626,   626,   626,   626,   626,   626,   626,   626,   626,   626,
     626,   626,   626,   627,   629,   628,   631,   630,   632,   634,
     633,   635,   636,   638,   637,   639,   639,   641,   640,   642,
     643,   645,   644,   647,   646,   649,   648,   651,   650,   653,
     652,   655,   654,   656,   656,   656,   657,   657,   659,   658,
     660,   662,   661,   663,   663,   663,   665,   664,   666,   666,
     666,   667,   667,   667,   667,   667,   667,   667,   668,   670,
     669,   672,   671,   673,   673,   673,   675,   674,   676,   676,
     676,   677,   677,   677,   677,   677,   679,   678,   680,   681,
     682,   684,   683,   686,   685,   687,   687,   687,   688,   688,
     689
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
       0,     4,     0,     4,     0,     6,     1,     1,     0,     4,
       0,     6,     1,     3,     2,     0,     4,     0,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     3,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     3,     0,     4,     3,     3,     3,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     3,     0,     4,     0,     6,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     0,     4,     1,     1,     0,     4,     3,
       3,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     1,     3,     2,     1,     1,     0,     6,
       3,     0,     6,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     6,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     0,     4,     3,     3,
       3,     0,     4,     0,     6,     1,     3,     2,     1,     1,
       3
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
  "\"loggers\"", "\"output-options\"", "\"output\"", "\"debuglevel\"",
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
  "relay_map", "ip_address", "$@106", "client_classes", "$@107",
  "client_classes_list", "client_class_entry", "$@108",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@109",
  "client_class_template_test", "$@110", "only_if_required", "server_id",
  "$@111", "server_id_params", "server_id_param", "server_id_type",
  "$@112", "duid_type", "htype", "identifier", "$@113", "time",
  "enterprise_id", "dhcp4o6_port", "control_socket", "$@114",
  "control_socket_params", "control_socket_param", "socket_type", "$@115",
  "socket_name", "$@116", "dhcp_queue_control", "$@117",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@118", "capacity", "arbitrary_map_entry", "$@119",
  "dhcp_ddns", "$@120", "sub_dhcp_ddns", "$@121", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "dep_qualifying_suffix", "$@122",
  "server_ip", "$@123", "server_port", "sender_ip", "$@124", "sender_port",
  "max_queue_size", "ncr_protocol", "$@125", "ncr_protocol_value",
  "ncr_format", "$@126", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@127",
  "dep_generated_prefix", "$@128", "dep_hostname_char_set", "$@129",
  "dep_hostname_char_replacement", "$@130", "config_control", "$@131",
  "sub_config_control", "$@132", "config_control_params",
  "config_control_param", "config_databases", "$@133",
  "config_fetch_wait_time", "loggers", "$@134", "loggers_entries",
  "logger_entry", "$@135", "logger_params", "logger_param", "debuglevel",
  "severity", "$@136", "output_options_list", "$@137",
  "output_options_list_content", "output_entry", "$@138",
  "output_params_list", "output_params", "output", "$@139", "flush",
  "maxsize", "maxver", "pattern", "$@140", "compatibility", "$@141",
  "compatibility_params", "compatibility_param", "lenient_option_parsing", YY_NULLPTR
  };
#endif


#if PARSER6_DEBUG
  const short
  Dhcp6Parser::yyrline_[] =
  {
       0,   324,   324,   324,   325,   325,   326,   326,   327,   327,
     328,   328,   329,   329,   330,   330,   331,   331,   332,   332,
     333,   333,   334,   334,   335,   335,   336,   336,   337,   337,
     345,   346,   347,   348,   349,   350,   351,   354,   359,   359,
     370,   373,   374,   377,   382,   388,   393,   393,   400,   401,
     404,   408,   412,   418,   418,   425,   426,   429,   433,   437,
     447,   456,   456,   471,   471,   485,   488,   494,   494,   503,
     504,   505,   512,   513,   514,   515,   516,   517,   518,   519,
     520,   521,   522,   523,   524,   525,   526,   527,   528,   529,
     530,   531,   532,   533,   534,   535,   536,   537,   538,   539,
     540,   541,   542,   543,   544,   545,   546,   547,   548,   549,
     550,   551,   552,   553,   554,   555,   556,   557,   558,   559,
     560,   561,   562,   563,   564,   565,   566,   567,   568,   569,
     570,   571,   572,   573,   574,   575,   576,   577,   578,   579,
     580,   583,   583,   592,   598,   604,   610,   616,   622,   628,
     634,   640,   646,   652,   658,   664,   670,   676,   682,   688,
     694,   694,   703,   706,   709,   712,   715,   721,   721,   730,
     730,   739,   748,   758,   758,   767,   770,   773,   776,   781,
     787,   787,   796,   796,   805,   811,   817,   823,   823,   832,
     838,   838,   847,   847,   856,   862,   868,   874,   874,   886,
     886,   895,   896,   897,   902,   903,   904,   905,   906,   907,
     908,   909,   912,   912,   923,   929,   935,   941,   947,   947,
     960,   960,   973,   973,   984,   985,   988,   989,   990,   995,
     995,  1005,  1006,  1007,  1012,  1013,  1014,  1015,  1016,  1017,
    1018,  1019,  1020,  1021,  1022,  1023,  1024,  1025,  1026,  1027,
    1028,  1029,  1030,  1031,  1032,  1033,  1034,  1037,  1037,  1045,
    1046,  1047,  1050,  1050,  1059,  1059,  1068,  1068,  1077,  1083,
    1083,  1092,  1098,  1104,  1110,  1116,  1122,  1128,  1135,  1141,
    1141,  1149,  1150,  1151,  1154,  1160,  1166,  1172,  1172,  1181,
    1181,  1190,  1190,  1199,  1199,  1208,  1208,  1219,  1220,  1221,
    1226,  1227,  1230,  1230,  1249,  1249,  1267,  1267,  1278,  1279,
    1280,  1285,  1286,  1289,  1294,  1299,  1299,  1310,  1311,  1312,
    1317,  1318,  1319,  1322,  1327,  1334,  1334,  1347,  1347,  1360,
    1361,  1362,  1367,  1368,  1369,  1370,  1371,  1372,  1375,  1381,
    1387,  1393,  1393,  1404,  1405,  1408,  1409,  1410,  1415,  1415,
    1425,  1425,  1435,  1436,  1437,  1440,  1443,  1444,  1447,  1447,
    1456,  1456,  1465,  1465,  1477,  1478,  1479,  1484,  1485,  1486,
    1487,  1488,  1489,  1492,  1498,  1504,  1510,  1516,  1522,  1531,
    1531,  1545,  1546,  1549,  1550,  1551,  1560,  1560,  1586,  1586,
    1597,  1598,  1599,  1605,  1606,  1607,  1608,  1609,  1610,  1611,
    1612,  1613,  1614,  1615,  1616,  1617,  1618,  1619,  1620,  1621,
    1622,  1623,  1624,  1625,  1626,  1627,  1628,  1629,  1630,  1631,
    1632,  1633,  1634,  1635,  1636,  1637,  1638,  1639,  1640,  1641,
    1642,  1643,  1644,  1645,  1646,  1647,  1648,  1649,  1650,  1651,
    1654,  1654,  1663,  1663,  1672,  1672,  1681,  1681,  1690,  1690,
    1701,  1707,  1713,  1719,  1719,  1727,  1728,  1729,  1730,  1733,
    1739,  1747,  1747,  1759,  1760,  1764,  1765,  1766,  1771,  1771,
    1779,  1780,  1781,  1786,  1787,  1788,  1789,  1790,  1791,  1792,
    1793,  1794,  1795,  1796,  1797,  1798,  1799,  1800,  1801,  1802,
    1803,  1804,  1805,  1806,  1807,  1808,  1809,  1810,  1811,  1812,
    1813,  1814,  1815,  1816,  1817,  1818,  1819,  1820,  1821,  1822,
    1823,  1824,  1825,  1826,  1827,  1828,  1829,  1836,  1836,  1850,
    1850,  1859,  1860,  1863,  1864,  1865,  1872,  1872,  1887,  1887,
    1901,  1902,  1905,  1906,  1907,  1912,  1913,  1914,  1915,  1916,
    1917,  1918,  1919,  1920,  1921,  1924,  1926,  1932,  1934,  1934,
    1943,  1943,  1952,  1952,  1961,  1963,  1963,  1972,  1982,  1982,
    1995,  1996,  2001,  2002,  2003,  2010,  2010,  2022,  2022,  2034,
    2035,  2040,  2041,  2042,  2049,  2050,  2051,  2052,  2053,  2054,
    2055,  2056,  2057,  2058,  2061,  2063,  2063,  2072,  2074,  2076,
    2082,  2088,  2097,  2097,  2110,  2111,  2114,  2115,  2116,  2121,
    2121,  2131,  2131,  2141,  2142,  2143,  2148,  2149,  2150,  2151,
    2152,  2153,  2154,  2155,  2158,  2158,  2167,  2173,  2173,  2198,
    2198,  2228,  2228,  2241,  2242,  2245,  2246,  2247,  2252,  2252,
    2264,  2264,  2276,  2277,  2278,  2283,  2284,  2285,  2286,  2287,
    2288,  2289,  2290,  2291,  2292,  2293,  2296,  2296,  2305,  2311,
    2311,  2320,  2326,  2335,  2335,  2346,  2347,  2350,  2351,  2352,
    2357,  2357,  2366,  2366,  2375,  2376,  2379,  2380,  2381,  2387,
    2388,  2389,  2390,  2391,  2392,  2393,  2394,  2395,  2396,  2397,
    2400,  2400,  2411,  2411,  2422,  2422,  2431,  2431,  2440,  2440,
    2449,  2449,  2458,  2458,  2472,  2472,  2483,  2484,  2487,  2487,
    2499,  2499,  2510,  2511,  2512,  2517,  2517,  2527,  2528,  2531,
    2532,  2533,  2538,  2539,  2540,  2541,  2542,  2543,  2544,  2545,
    2546,  2547,  2548,  2549,  2550,  2551,  2554,  2556,  2556,  2565,
    2565,  2574,  2583,  2583,  2596,  2597,  2598,  2603,  2604,  2605,
    2606,  2607,  2608,  2609,  2610,  2611,  2614,  2614,  2622,  2623,
    2624,  2627,  2633,  2633,  2642,  2648,  2656,  2664,  2664,  2675,
    2676,  2677,  2682,  2683,  2684,  2685,  2686,  2689,  2689,  2698,
    2698,  2710,  2710,  2723,  2724,  2725,  2730,  2731,  2732,  2733,
    2734,  2735,  2738,  2744,  2744,  2753,  2759,  2759,  2769,  2769,
    2782,  2782,  2792,  2793,  2794,  2799,  2800,  2801,  2802,  2803,
    2804,  2805,  2806,  2807,  2808,  2809,  2810,  2811,  2812,  2813,
    2814,  2815,  2816,  2819,  2826,  2826,  2835,  2835,  2844,  2850,
    2850,  2859,  2865,  2871,  2871,  2880,  2881,  2884,  2884,  2894,
    2901,  2908,  2908,  2917,  2917,  2927,  2927,  2937,  2937,  2949,
    2949,  2961,  2961,  2971,  2972,  2973,  2979,  2980,  2983,  2983,
    2994,  3002,  3002,  3015,  3016,  3017,  3023,  3023,  3031,  3032,
    3033,  3038,  3039,  3040,  3041,  3042,  3043,  3044,  3047,  3053,
    3053,  3062,  3062,  3073,  3074,  3075,  3080,  3080,  3088,  3089,
    3090,  3095,  3096,  3097,  3098,  3099,  3102,  3102,  3111,  3117,
    3123,  3129,  3129,  3138,  3138,  3149,  3150,  3151,  3156,  3157,
    3160
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
#line 6634 "dhcp6_parser.cc"

#line 3166 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
