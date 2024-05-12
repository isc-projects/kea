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
#line 314 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 413 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 314 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 419 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 314 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 425 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 314 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 431 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 314 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 437 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 314 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 443 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 314 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 449 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 314 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 455 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 314 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 461 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 314 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 467 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 314 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 473 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 314 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 479 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 314 "dhcp6_parser.yy"
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
#line 323 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 766 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 324 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 772 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 325 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 778 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 326 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 784 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 327 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 790 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 328 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 796 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 329 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 802 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 330 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 808 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 331 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 814 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 332 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 820 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 333 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 826 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 334 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 832 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 335 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 838 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 336 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 844 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 344 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 850 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 345 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 856 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 346 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 862 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 347 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 868 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 348 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 874 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 349 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 880 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 350 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 886 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 353 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 895 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 358 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 906 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 363 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 916 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 369 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 922 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 376 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 932 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 381 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 943 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 387 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 951 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 392 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 960 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 395 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 968 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 403 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 977 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 407 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 986 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 411 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 994 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 417 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 1002 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 419 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1011 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 428 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1020 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 432 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1029 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 436 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1037 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 446 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1048 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 455 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1059 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 460 "dhcp6_parser.yy"
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
#line 470 "dhcp6_parser.yy"
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
#line 479 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1097 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 487 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1105 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 493 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1115 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 497 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1124 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 504 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1132 "dhcp6_parser.cc"
    break;

  case 141: // $@21: %empty
#line 582 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1141 "dhcp6_parser.cc"
    break;

  case 142: // data_directory: "data-directory" $@21 ":" "constant string"
#line 585 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1151 "dhcp6_parser.cc"
    break;

  case 143: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 591 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1161 "dhcp6_parser.cc"
    break;

  case 144: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 597 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1171 "dhcp6_parser.cc"
    break;

  case 145: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 603 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1181 "dhcp6_parser.cc"
    break;

  case 146: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 609 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1191 "dhcp6_parser.cc"
    break;

  case 147: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 615 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1201 "dhcp6_parser.cc"
    break;

  case 148: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 621 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1211 "dhcp6_parser.cc"
    break;

  case 149: // renew_timer: "renew-timer" ":" "integer"
#line 627 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1221 "dhcp6_parser.cc"
    break;

  case 150: // rebind_timer: "rebind-timer" ":" "integer"
#line 633 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1231 "dhcp6_parser.cc"
    break;

  case 151: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 639 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1241 "dhcp6_parser.cc"
    break;

  case 152: // t1_percent: "t1-percent" ":" "floating point"
#line 645 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1251 "dhcp6_parser.cc"
    break;

  case 153: // t2_percent: "t2-percent" ":" "floating point"
#line 651 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1261 "dhcp6_parser.cc"
    break;

  case 154: // cache_threshold: "cache-threshold" ":" "floating point"
#line 657 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1271 "dhcp6_parser.cc"
    break;

  case 155: // cache_max_age: "cache-max-age" ":" "integer"
#line 663 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1281 "dhcp6_parser.cc"
    break;

  case 156: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 669 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1291 "dhcp6_parser.cc"
    break;

  case 157: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 675 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1301 "dhcp6_parser.cc"
    break;

  case 158: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 681 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1311 "dhcp6_parser.cc"
    break;

  case 159: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 687 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1321 "dhcp6_parser.cc"
    break;

  case 160: // $@22: %empty
#line 693 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1330 "dhcp6_parser.cc"
    break;

  case 161: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 696 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1339 "dhcp6_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "when-present"
#line 702 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1347 "dhcp6_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "never"
#line 705 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1355 "dhcp6_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "always"
#line 708 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1363 "dhcp6_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "when-not-present"
#line 711 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1371 "dhcp6_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "boolean"
#line 714 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1380 "dhcp6_parser.cc"
    break;

  case 167: // $@23: %empty
#line 720 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1389 "dhcp6_parser.cc"
    break;

  case 168: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 723 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1399 "dhcp6_parser.cc"
    break;

  case 169: // $@24: %empty
#line 729 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1408 "dhcp6_parser.cc"
    break;

  case 170: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 732 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1418 "dhcp6_parser.cc"
    break;

  case 171: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 738 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1428 "dhcp6_parser.cc"
    break;

  case 172: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 747 "dhcp6_parser.yy"
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
#line 757 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1451 "dhcp6_parser.cc"
    break;

  case 174: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 760 "dhcp6_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 175: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 766 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1468 "dhcp6_parser.cc"
    break;

  case 176: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 769 "dhcp6_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1476 "dhcp6_parser.cc"
    break;

  case 177: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 772 "dhcp6_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1484 "dhcp6_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 775 "dhcp6_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1492 "dhcp6_parser.cc"
    break;

  case 179: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 780 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1502 "dhcp6_parser.cc"
    break;

  case 180: // $@26: %empty
#line 786 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1511 "dhcp6_parser.cc"
    break;

  case 181: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 789 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1521 "dhcp6_parser.cc"
    break;

  case 182: // $@27: %empty
#line 795 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1530 "dhcp6_parser.cc"
    break;

  case 183: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 798 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1540 "dhcp6_parser.cc"
    break;

  case 184: // store_extended_info: "store-extended-info" ":" "boolean"
#line 804 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1550 "dhcp6_parser.cc"
    break;

  case 185: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 810 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1560 "dhcp6_parser.cc"
    break;

  case 186: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 816 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1570 "dhcp6_parser.cc"
    break;

  case 187: // $@28: %empty
#line 822 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1579 "dhcp6_parser.cc"
    break;

  case 188: // server_tag: "server-tag" $@28 ":" "constant string"
#line 825 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1589 "dhcp6_parser.cc"
    break;

  case 189: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 831 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1599 "dhcp6_parser.cc"
    break;

  case 190: // $@29: %empty
#line 837 "dhcp6_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1608 "dhcp6_parser.cc"
    break;

  case 191: // allocator: "allocator" $@29 ":" "constant string"
#line 840 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1618 "dhcp6_parser.cc"
    break;

  case 192: // $@30: %empty
#line 846 "dhcp6_parser.yy"
                           {
    ctx.unique("pd-allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1627 "dhcp6_parser.cc"
    break;

  case 193: // pd_allocator: "pd-allocator" $@30 ":" "constant string"
#line 849 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-allocator", al);
    ctx.leave();
}
#line 1637 "dhcp6_parser.cc"
    break;

  case 194: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 855 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1647 "dhcp6_parser.cc"
    break;

  case 195: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 861 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1657 "dhcp6_parser.cc"
    break;

  case 196: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 867 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1667 "dhcp6_parser.cc"
    break;

  case 197: // $@31: %empty
#line 873 "dhcp6_parser.yy"
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
#line 879 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1689 "dhcp6_parser.cc"
    break;

  case 199: // $@32: %empty
#line 885 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1699 "dhcp6_parser.cc"
    break;

  case 200: // sub_interfaces6: "{" $@32 interfaces_config_params "}"
#line 889 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1708 "dhcp6_parser.cc"
    break;

  case 203: // interfaces_config_params: interfaces_config_params ","
#line 896 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1716 "dhcp6_parser.cc"
    break;

  case 212: // $@33: %empty
#line 911 "dhcp6_parser.yy"
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
#line 917 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1737 "dhcp6_parser.cc"
    break;

  case 214: // re_detect: "re-detect" ":" "boolean"
#line 922 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1747 "dhcp6_parser.cc"
    break;

  case 215: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 928 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1757 "dhcp6_parser.cc"
    break;

  case 216: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 934 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1767 "dhcp6_parser.cc"
    break;

  case 217: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 940 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1777 "dhcp6_parser.cc"
    break;

  case 218: // $@34: %empty
#line 946 "dhcp6_parser.yy"
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
#line 952 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1800 "dhcp6_parser.cc"
    break;

  case 220: // $@35: %empty
#line 959 "dhcp6_parser.yy"
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
#line 965 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1823 "dhcp6_parser.cc"
    break;

  case 222: // $@36: %empty
#line 972 "dhcp6_parser.yy"
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
#line 978 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1844 "dhcp6_parser.cc"
    break;

  case 228: // not_empty_database_list: not_empty_database_list ","
#line 989 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1852 "dhcp6_parser.cc"
    break;

  case 229: // $@37: %empty
#line 994 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1862 "dhcp6_parser.cc"
    break;

  case 230: // database: "{" $@37 database_map_params "}"
#line 998 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1872 "dhcp6_parser.cc"
    break;

  case 233: // database_map_params: database_map_params ","
#line 1006 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1880 "dhcp6_parser.cc"
    break;

  case 257: // $@38: %empty
#line 1036 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1889 "dhcp6_parser.cc"
    break;

  case 258: // database_type: "type" $@38 ":" db_type
#line 1039 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1898 "dhcp6_parser.cc"
    break;

  case 259: // db_type: "memfile"
#line 1044 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1904 "dhcp6_parser.cc"
    break;

  case 260: // db_type: "mysql"
#line 1045 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1910 "dhcp6_parser.cc"
    break;

  case 261: // db_type: "postgresql"
#line 1046 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1916 "dhcp6_parser.cc"
    break;

  case 262: // $@39: %empty
#line 1049 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1925 "dhcp6_parser.cc"
    break;

  case 263: // user: "user" $@39 ":" "constant string"
#line 1052 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1935 "dhcp6_parser.cc"
    break;

  case 264: // $@40: %empty
#line 1058 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1944 "dhcp6_parser.cc"
    break;

  case 265: // password: "password" $@40 ":" "constant string"
#line 1061 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1954 "dhcp6_parser.cc"
    break;

  case 266: // $@41: %empty
#line 1067 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1963 "dhcp6_parser.cc"
    break;

  case 267: // host: "host" $@41 ":" "constant string"
#line 1070 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1973 "dhcp6_parser.cc"
    break;

  case 268: // port: "port" ":" "integer"
#line 1076 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1983 "dhcp6_parser.cc"
    break;

  case 269: // $@42: %empty
#line 1082 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1992 "dhcp6_parser.cc"
    break;

  case 270: // name: "name" $@42 ":" "constant string"
#line 1085 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2002 "dhcp6_parser.cc"
    break;

  case 271: // persist: "persist" ":" "boolean"
#line 1091 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2012 "dhcp6_parser.cc"
    break;

  case 272: // lfc_interval: "lfc-interval" ":" "integer"
#line 1097 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2022 "dhcp6_parser.cc"
    break;

  case 273: // readonly: "readonly" ":" "boolean"
#line 1103 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2032 "dhcp6_parser.cc"
    break;

  case 274: // connect_timeout: "connect-timeout" ":" "integer"
#line 1109 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2042 "dhcp6_parser.cc"
    break;

  case 275: // read_timeout: "read-timeout" ":" "integer"
#line 1115 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2052 "dhcp6_parser.cc"
    break;

  case 276: // write_timeout: "write-timeout" ":" "integer"
#line 1121 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2062 "dhcp6_parser.cc"
    break;

  case 277: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1127 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2072 "dhcp6_parser.cc"
    break;

  case 278: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1134 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2082 "dhcp6_parser.cc"
    break;

  case 279: // $@43: %empty
#line 1140 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2091 "dhcp6_parser.cc"
    break;

  case 280: // on_fail: "on-fail" $@43 ":" on_fail_mode
#line 1143 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2100 "dhcp6_parser.cc"
    break;

  case 281: // on_fail_mode: "stop-retry-exit"
#line 1148 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2106 "dhcp6_parser.cc"
    break;

  case 282: // on_fail_mode: "serve-retry-exit"
#line 1149 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2112 "dhcp6_parser.cc"
    break;

  case 283: // on_fail_mode: "serve-retry-continue"
#line 1150 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2118 "dhcp6_parser.cc"
    break;

  case 284: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1153 "dhcp6_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2128 "dhcp6_parser.cc"
    break;

  case 285: // max_row_errors: "max-row-errors" ":" "integer"
#line 1159 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2138 "dhcp6_parser.cc"
    break;

  case 286: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1165 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2148 "dhcp6_parser.cc"
    break;

  case 287: // $@44: %empty
#line 1171 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2157 "dhcp6_parser.cc"
    break;

  case 288: // trust_anchor: "trust-anchor" $@44 ":" "constant string"
#line 1174 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2167 "dhcp6_parser.cc"
    break;

  case 289: // $@45: %empty
#line 1180 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2176 "dhcp6_parser.cc"
    break;

  case 290: // cert_file: "cert-file" $@45 ":" "constant string"
#line 1183 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2186 "dhcp6_parser.cc"
    break;

  case 291: // $@46: %empty
#line 1189 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2195 "dhcp6_parser.cc"
    break;

  case 292: // key_file: "key-file" $@46 ":" "constant string"
#line 1192 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2205 "dhcp6_parser.cc"
    break;

  case 293: // $@47: %empty
#line 1198 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2214 "dhcp6_parser.cc"
    break;

  case 294: // cipher_list: "cipher-list" $@47 ":" "constant string"
#line 1201 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2224 "dhcp6_parser.cc"
    break;

  case 295: // $@48: %empty
#line 1207 "dhcp6_parser.yy"
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
#line 1213 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2245 "dhcp6_parser.cc"
    break;

  case 299: // sanity_checks_params: sanity_checks_params ","
#line 1220 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2253 "dhcp6_parser.cc"
    break;

  case 302: // $@49: %empty
#line 1229 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2262 "dhcp6_parser.cc"
    break;

  case 303: // lease_checks: "lease-checks" $@49 ":" "constant string"
#line 1232 "dhcp6_parser.yy"
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
#line 1248 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2291 "dhcp6_parser.cc"
    break;

  case 305: // extended_info_checks: "extended-info-checks" $@50 ":" "constant string"
#line 1251 "dhcp6_parser.yy"
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
#line 1266 "dhcp6_parser.yy"
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
#line 1272 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2331 "dhcp6_parser.cc"
    break;

  case 310: // mac_sources_list: mac_sources_list ","
#line 1279 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2339 "dhcp6_parser.cc"
    break;

  case 313: // duid_id: "duid"
#line 1288 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2348 "dhcp6_parser.cc"
    break;

  case 314: // string_id: "constant string"
#line 1293 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2357 "dhcp6_parser.cc"
    break;

  case 315: // $@52: %empty
#line 1298 "dhcp6_parser.yy"
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
#line 1304 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2378 "dhcp6_parser.cc"
    break;

  case 319: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1311 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2386 "dhcp6_parser.cc"
    break;

  case 323: // hw_address_id: "hw-address"
#line 1321 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2395 "dhcp6_parser.cc"
    break;

  case 324: // flex_id: "flex-id"
#line 1326 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2404 "dhcp6_parser.cc"
    break;

  case 325: // $@53: %empty
#line 1333 "dhcp6_parser.yy"
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
#line 1339 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2425 "dhcp6_parser.cc"
    break;

  case 327: // $@54: %empty
#line 1346 "dhcp6_parser.yy"
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
#line 1352 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2448 "dhcp6_parser.cc"
    break;

  case 331: // multi_threading_params: multi_threading_params ","
#line 1361 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2456 "dhcp6_parser.cc"
    break;

  case 338: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1374 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2466 "dhcp6_parser.cc"
    break;

  case 339: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1380 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2476 "dhcp6_parser.cc"
    break;

  case 340: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1386 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2486 "dhcp6_parser.cc"
    break;

  case 341: // $@55: %empty
#line 1392 "dhcp6_parser.yy"
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
#line 1398 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2507 "dhcp6_parser.cc"
    break;

  case 347: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1409 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2515 "dhcp6_parser.cc"
    break;

  case 348: // $@56: %empty
#line 1414 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2525 "dhcp6_parser.cc"
    break;

  case 349: // hooks_library: "{" $@56 hooks_params "}"
#line 1418 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2535 "dhcp6_parser.cc"
    break;

  case 350: // $@57: %empty
#line 1424 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2545 "dhcp6_parser.cc"
    break;

  case 351: // sub_hooks_library: "{" $@57 hooks_params "}"
#line 1428 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2555 "dhcp6_parser.cc"
    break;

  case 354: // hooks_params: hooks_params ","
#line 1436 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2563 "dhcp6_parser.cc"
    break;

  case 358: // $@58: %empty
#line 1446 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2572 "dhcp6_parser.cc"
    break;

  case 359: // library: "library" $@58 ":" "constant string"
#line 1449 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2582 "dhcp6_parser.cc"
    break;

  case 360: // $@59: %empty
#line 1455 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2591 "dhcp6_parser.cc"
    break;

  case 361: // parameters: "parameters" $@59 ":" map_value
#line 1458 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2600 "dhcp6_parser.cc"
    break;

  case 362: // $@60: %empty
#line 1464 "dhcp6_parser.yy"
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
#line 1470 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2622 "dhcp6_parser.cc"
    break;

  case 366: // expired_leases_params: expired_leases_params ","
#line 1478 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2630 "dhcp6_parser.cc"
    break;

  case 373: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1491 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2640 "dhcp6_parser.cc"
    break;

  case 374: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1497 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2650 "dhcp6_parser.cc"
    break;

  case 375: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1503 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2660 "dhcp6_parser.cc"
    break;

  case 376: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1509 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2670 "dhcp6_parser.cc"
    break;

  case 377: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1515 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2680 "dhcp6_parser.cc"
    break;

  case 378: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1521 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2690 "dhcp6_parser.cc"
    break;

  case 379: // $@61: %empty
#line 1530 "dhcp6_parser.yy"
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
#line 1536 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2711 "dhcp6_parser.cc"
    break;

  case 385: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1550 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2719 "dhcp6_parser.cc"
    break;

  case 386: // $@62: %empty
#line 1559 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2729 "dhcp6_parser.cc"
    break;

  case 387: // subnet6: "{" $@62 subnet6_params "}"
#line 1563 "dhcp6_parser.yy"
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
#line 1585 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2765 "dhcp6_parser.cc"
    break;

  case 389: // sub_subnet6: "{" $@63 subnet6_params "}"
#line 1589 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2775 "dhcp6_parser.cc"
    break;

  case 392: // subnet6_params: subnet6_params ","
#line 1598 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2783 "dhcp6_parser.cc"
    break;

  case 440: // $@64: %empty
#line 1653 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2792 "dhcp6_parser.cc"
    break;

  case 441: // subnet: "subnet" $@64 ":" "constant string"
#line 1656 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2802 "dhcp6_parser.cc"
    break;

  case 442: // $@65: %empty
#line 1662 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2811 "dhcp6_parser.cc"
    break;

  case 443: // interface: "interface" $@65 ":" "constant string"
#line 1665 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2821 "dhcp6_parser.cc"
    break;

  case 444: // $@66: %empty
#line 1671 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2830 "dhcp6_parser.cc"
    break;

  case 445: // interface_id: "interface-id" $@66 ":" "constant string"
#line 1674 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2840 "dhcp6_parser.cc"
    break;

  case 446: // $@67: %empty
#line 1680 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2849 "dhcp6_parser.cc"
    break;

  case 447: // client_class: "client-class" $@67 ":" "constant string"
#line 1683 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2859 "dhcp6_parser.cc"
    break;

  case 448: // $@68: %empty
#line 1689 "dhcp6_parser.yy"
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
#line 1695 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2880 "dhcp6_parser.cc"
    break;

  case 450: // reservations_global: "reservations-global" ":" "boolean"
#line 1700 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2890 "dhcp6_parser.cc"
    break;

  case 451: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1706 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2900 "dhcp6_parser.cc"
    break;

  case 452: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1712 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2910 "dhcp6_parser.cc"
    break;

  case 453: // $@69: %empty
#line 1718 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2919 "dhcp6_parser.cc"
    break;

  case 454: // reservation_mode: "reservation-mode" $@69 ":" hr_mode
#line 1721 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2928 "dhcp6_parser.cc"
    break;

  case 455: // hr_mode: "disabled"
#line 1726 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2934 "dhcp6_parser.cc"
    break;

  case 456: // hr_mode: "out-of-pool"
#line 1727 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2940 "dhcp6_parser.cc"
    break;

  case 457: // hr_mode: "global"
#line 1728 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2946 "dhcp6_parser.cc"
    break;

  case 458: // hr_mode: "all"
#line 1729 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2952 "dhcp6_parser.cc"
    break;

  case 459: // id: "id" ":" "integer"
#line 1732 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2962 "dhcp6_parser.cc"
    break;

  case 460: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1738 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2972 "dhcp6_parser.cc"
    break;

  case 461: // $@70: %empty
#line 1746 "dhcp6_parser.yy"
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
#line 1752 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2993 "dhcp6_parser.cc"
    break;

  case 467: // shared_networks_list: shared_networks_list ","
#line 1765 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3001 "dhcp6_parser.cc"
    break;

  case 468: // $@71: %empty
#line 1770 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3011 "dhcp6_parser.cc"
    break;

  case 469: // shared_network: "{" $@71 shared_network_params "}"
#line 1774 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3019 "dhcp6_parser.cc"
    break;

  case 472: // shared_network_params: shared_network_params ","
#line 1780 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3027 "dhcp6_parser.cc"
    break;

  case 517: // $@72: %empty
#line 1835 "dhcp6_parser.yy"
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
#line 1841 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3048 "dhcp6_parser.cc"
    break;

  case 519: // $@73: %empty
#line 1849 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3057 "dhcp6_parser.cc"
    break;

  case 520: // sub_option_def_list: "{" $@73 option_def_list "}"
#line 1852 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 3065 "dhcp6_parser.cc"
    break;

  case 525: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1864 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3073 "dhcp6_parser.cc"
    break;

  case 526: // $@74: %empty
#line 1871 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3083 "dhcp6_parser.cc"
    break;

  case 527: // option_def_entry: "{" $@74 option_def_params "}"
#line 1875 "dhcp6_parser.yy"
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
#line 1886 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3105 "dhcp6_parser.cc"
    break;

  case 529: // sub_option_def: "{" $@75 option_def_params "}"
#line 1890 "dhcp6_parser.yy"
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
#line 1906 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3125 "dhcp6_parser.cc"
    break;

  case 546: // code: "code" ":" "integer"
#line 1925 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3135 "dhcp6_parser.cc"
    break;

  case 548: // $@76: %empty
#line 1933 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3144 "dhcp6_parser.cc"
    break;

  case 549: // option_def_type: "type" $@76 ":" "constant string"
#line 1936 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3154 "dhcp6_parser.cc"
    break;

  case 550: // $@77: %empty
#line 1942 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3163 "dhcp6_parser.cc"
    break;

  case 551: // option_def_record_types: "record-types" $@77 ":" "constant string"
#line 1945 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3173 "dhcp6_parser.cc"
    break;

  case 552: // $@78: %empty
#line 1951 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3182 "dhcp6_parser.cc"
    break;

  case 553: // space: "space" $@78 ":" "constant string"
#line 1954 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3192 "dhcp6_parser.cc"
    break;

  case 555: // $@79: %empty
#line 1962 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3201 "dhcp6_parser.cc"
    break;

  case 556: // option_def_encapsulate: "encapsulate" $@79 ":" "constant string"
#line 1965 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3211 "dhcp6_parser.cc"
    break;

  case 557: // option_def_array: "array" ":" "boolean"
#line 1971 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3221 "dhcp6_parser.cc"
    break;

  case 558: // $@80: %empty
#line 1981 "dhcp6_parser.yy"
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
#line 1987 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3242 "dhcp6_parser.cc"
    break;

  case 564: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2002 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3250 "dhcp6_parser.cc"
    break;

  case 565: // $@81: %empty
#line 2009 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3260 "dhcp6_parser.cc"
    break;

  case 566: // option_data_entry: "{" $@81 option_data_params "}"
#line 2013 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3269 "dhcp6_parser.cc"
    break;

  case 567: // $@82: %empty
#line 2021 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3279 "dhcp6_parser.cc"
    break;

  case 568: // sub_option_data: "{" $@82 option_data_params "}"
#line 2025 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3288 "dhcp6_parser.cc"
    break;

  case 573: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2041 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3296 "dhcp6_parser.cc"
    break;

  case 585: // $@83: %empty
#line 2062 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3305 "dhcp6_parser.cc"
    break;

  case 586: // option_data_data: "data" $@83 ":" "constant string"
#line 2065 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3315 "dhcp6_parser.cc"
    break;

  case 589: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2075 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3325 "dhcp6_parser.cc"
    break;

  case 590: // option_data_always_send: "always-send" ":" "boolean"
#line 2081 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3335 "dhcp6_parser.cc"
    break;

  case 591: // option_data_never_send: "never-send" ":" "boolean"
#line 2087 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3345 "dhcp6_parser.cc"
    break;

  case 592: // $@84: %empty
#line 2096 "dhcp6_parser.yy"
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
#line 2102 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3366 "dhcp6_parser.cc"
    break;

  case 598: // not_empty_pools_list: not_empty_pools_list ","
#line 2115 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3374 "dhcp6_parser.cc"
    break;

  case 599: // $@85: %empty
#line 2120 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3384 "dhcp6_parser.cc"
    break;

  case 600: // pool_list_entry: "{" $@85 pool_params "}"
#line 2124 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3394 "dhcp6_parser.cc"
    break;

  case 601: // $@86: %empty
#line 2130 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3404 "dhcp6_parser.cc"
    break;

  case 602: // sub_pool6: "{" $@86 pool_params "}"
#line 2134 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3414 "dhcp6_parser.cc"
    break;

  case 605: // pool_params: pool_params ","
#line 2142 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3422 "dhcp6_parser.cc"
    break;

  case 614: // $@87: %empty
#line 2157 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3431 "dhcp6_parser.cc"
    break;

  case 615: // pool_entry: "pool" $@87 ":" "constant string"
#line 2160 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3441 "dhcp6_parser.cc"
    break;

  case 616: // pool_id: "pool-id" ":" "integer"
#line 2166 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3451 "dhcp6_parser.cc"
    break;

  case 617: // $@88: %empty
#line 2172 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3459 "dhcp6_parser.cc"
    break;

  case 618: // user_context: "user-context" $@88 ":" map_value
#line 2174 "dhcp6_parser.yy"
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
#line 2197 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3494 "dhcp6_parser.cc"
    break;

  case 620: // comment: "comment" $@89 ":" "constant string"
#line 2199 "dhcp6_parser.yy"
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
#line 2227 "dhcp6_parser.yy"
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
#line 2233 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3544 "dhcp6_parser.cc"
    break;

  case 627: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2246 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3552 "dhcp6_parser.cc"
    break;

  case 628: // $@91: %empty
#line 2251 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3562 "dhcp6_parser.cc"
    break;

  case 629: // pd_pool_entry: "{" $@91 pd_pool_params "}"
#line 2255 "dhcp6_parser.yy"
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
#line 2263 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3584 "dhcp6_parser.cc"
    break;

  case 631: // sub_pd_pool: "{" $@92 pd_pool_params "}"
#line 2267 "dhcp6_parser.yy"
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
#line 2277 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3604 "dhcp6_parser.cc"
    break;

  case 646: // $@93: %empty
#line 2295 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3613 "dhcp6_parser.cc"
    break;

  case 647: // pd_prefix: "prefix" $@93 ":" "constant string"
#line 2298 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3623 "dhcp6_parser.cc"
    break;

  case 648: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2304 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3633 "dhcp6_parser.cc"
    break;

  case 649: // $@94: %empty
#line 2310 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3642 "dhcp6_parser.cc"
    break;

  case 650: // excluded_prefix: "excluded-prefix" $@94 ":" "constant string"
#line 2313 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3652 "dhcp6_parser.cc"
    break;

  case 651: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2319 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3662 "dhcp6_parser.cc"
    break;

  case 652: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2325 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3672 "dhcp6_parser.cc"
    break;

  case 653: // $@95: %empty
#line 2334 "dhcp6_parser.yy"
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
#line 2340 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3693 "dhcp6_parser.cc"
    break;

  case 659: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2351 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3701 "dhcp6_parser.cc"
    break;

  case 660: // $@96: %empty
#line 2356 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3711 "dhcp6_parser.cc"
    break;

  case 661: // reservation: "{" $@96 reservation_params "}"
#line 2360 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3720 "dhcp6_parser.cc"
    break;

  case 662: // $@97: %empty
#line 2365 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3730 "dhcp6_parser.cc"
    break;

  case 663: // sub_reservation: "{" $@97 reservation_params "}"
#line 2369 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3739 "dhcp6_parser.cc"
    break;

  case 668: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2380 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3747 "dhcp6_parser.cc"
    break;

  case 680: // $@98: %empty
#line 2399 "dhcp6_parser.yy"
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
#line 2405 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3768 "dhcp6_parser.cc"
    break;

  case 682: // $@99: %empty
#line 2410 "dhcp6_parser.yy"
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
#line 2416 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3789 "dhcp6_parser.cc"
    break;

  case 684: // $@100: %empty
#line 2421 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3798 "dhcp6_parser.cc"
    break;

  case 685: // duid: "duid" $@100 ":" "constant string"
#line 2424 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3808 "dhcp6_parser.cc"
    break;

  case 686: // $@101: %empty
#line 2430 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3817 "dhcp6_parser.cc"
    break;

  case 687: // hw_address: "hw-address" $@101 ":" "constant string"
#line 2433 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3827 "dhcp6_parser.cc"
    break;

  case 688: // $@102: %empty
#line 2439 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3836 "dhcp6_parser.cc"
    break;

  case 689: // hostname: "hostname" $@102 ":" "constant string"
#line 2442 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3846 "dhcp6_parser.cc"
    break;

  case 690: // $@103: %empty
#line 2448 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3855 "dhcp6_parser.cc"
    break;

  case 691: // flex_id_value: "flex-id" $@103 ":" "constant string"
#line 2451 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3865 "dhcp6_parser.cc"
    break;

  case 692: // $@104: %empty
#line 2457 "dhcp6_parser.yy"
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
#line 2463 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3886 "dhcp6_parser.cc"
    break;

  case 694: // $@105: %empty
#line 2471 "dhcp6_parser.yy"
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
#line 2477 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3907 "dhcp6_parser.cc"
    break;

  case 697: // $@106: %empty
#line 2488 "dhcp6_parser.yy"
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
#line 2494 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3928 "dhcp6_parser.cc"
    break;

  case 701: // client_classes_list: client_classes_list ","
#line 2501 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3936 "dhcp6_parser.cc"
    break;

  case 702: // $@107: %empty
#line 2506 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3946 "dhcp6_parser.cc"
    break;

  case 703: // client_class_entry: "{" $@107 client_class_params "}"
#line 2510 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3956 "dhcp6_parser.cc"
    break;

  case 708: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2522 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3964 "dhcp6_parser.cc"
    break;

  case 724: // $@108: %empty
#line 2545 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3973 "dhcp6_parser.cc"
    break;

  case 725: // client_class_test: "test" $@108 ":" "constant string"
#line 2548 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3983 "dhcp6_parser.cc"
    break;

  case 726: // $@109: %empty
#line 2554 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3992 "dhcp6_parser.cc"
    break;

  case 727: // client_class_template_test: "template-test" $@109 ":" "constant string"
#line 2557 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4002 "dhcp6_parser.cc"
    break;

  case 728: // only_if_required: "only-if-required" ":" "boolean"
#line 2563 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4012 "dhcp6_parser.cc"
    break;

  case 729: // $@110: %empty
#line 2572 "dhcp6_parser.yy"
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
#line 2578 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4035 "dhcp6_parser.cc"
    break;

  case 733: // server_id_params: server_id_params ","
#line 2587 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4043 "dhcp6_parser.cc"
    break;

  case 743: // $@111: %empty
#line 2603 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 4052 "dhcp6_parser.cc"
    break;

  case 744: // server_id_type: "type" $@111 ":" duid_type
#line 2606 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4061 "dhcp6_parser.cc"
    break;

  case 745: // duid_type: "LLT"
#line 2611 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4067 "dhcp6_parser.cc"
    break;

  case 746: // duid_type: "EN"
#line 2612 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4073 "dhcp6_parser.cc"
    break;

  case 747: // duid_type: "LL"
#line 2613 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4079 "dhcp6_parser.cc"
    break;

  case 748: // htype: "htype" ":" "integer"
#line 2616 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4089 "dhcp6_parser.cc"
    break;

  case 749: // $@112: %empty
#line 2622 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4098 "dhcp6_parser.cc"
    break;

  case 750: // identifier: "identifier" $@112 ":" "constant string"
#line 2625 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4108 "dhcp6_parser.cc"
    break;

  case 751: // time: "time" ":" "integer"
#line 2631 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4118 "dhcp6_parser.cc"
    break;

  case 752: // enterprise_id: "enterprise-id" ":" "integer"
#line 2637 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4128 "dhcp6_parser.cc"
    break;

  case 753: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2645 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4138 "dhcp6_parser.cc"
    break;

  case 754: // $@113: %empty
#line 2653 "dhcp6_parser.yy"
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
#line 2659 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4159 "dhcp6_parser.cc"
    break;

  case 758: // control_socket_params: control_socket_params ","
#line 2666 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4167 "dhcp6_parser.cc"
    break;

  case 764: // $@114: %empty
#line 2678 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4176 "dhcp6_parser.cc"
    break;

  case 765: // socket_type: "socket-type" $@114 ":" "constant string"
#line 2681 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 4186 "dhcp6_parser.cc"
    break;

  case 766: // $@115: %empty
#line 2687 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4195 "dhcp6_parser.cc"
    break;

  case 767: // socket_name: "socket-name" $@115 ":" "constant string"
#line 2690 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4205 "dhcp6_parser.cc"
    break;

  case 768: // $@116: %empty
#line 2699 "dhcp6_parser.yy"
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
#line 2705 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4228 "dhcp6_parser.cc"
    break;

  case 772: // queue_control_params: queue_control_params ","
#line 2714 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4236 "dhcp6_parser.cc"
    break;

  case 779: // enable_queue: "enable-queue" ":" "boolean"
#line 2727 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4246 "dhcp6_parser.cc"
    break;

  case 780: // $@117: %empty
#line 2733 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4255 "dhcp6_parser.cc"
    break;

  case 781: // queue_type: "queue-type" $@117 ":" "constant string"
#line 2736 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4265 "dhcp6_parser.cc"
    break;

  case 782: // capacity: "capacity" ":" "integer"
#line 2742 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4275 "dhcp6_parser.cc"
    break;

  case 783: // $@118: %empty
#line 2748 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4284 "dhcp6_parser.cc"
    break;

  case 784: // arbitrary_map_entry: "constant string" $@118 ":" value
#line 2751 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4293 "dhcp6_parser.cc"
    break;

  case 785: // $@119: %empty
#line 2758 "dhcp6_parser.yy"
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
#line 2764 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4316 "dhcp6_parser.cc"
    break;

  case 787: // $@120: %empty
#line 2771 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4326 "dhcp6_parser.cc"
    break;

  case 788: // sub_dhcp_ddns: "{" $@120 dhcp_ddns_params "}"
#line 2775 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4336 "dhcp6_parser.cc"
    break;

  case 791: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2783 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4344 "dhcp6_parser.cc"
    break;

  case 810: // enable_updates: "enable-updates" ":" "boolean"
#line 2808 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4354 "dhcp6_parser.cc"
    break;

  case 811: // $@121: %empty
#line 2815 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4363 "dhcp6_parser.cc"
    break;

  case 812: // dep_qualifying_suffix: "qualifying-suffix" $@121 ":" "constant string"
#line 2818 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4373 "dhcp6_parser.cc"
    break;

  case 813: // $@122: %empty
#line 2824 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4382 "dhcp6_parser.cc"
    break;

  case 814: // server_ip: "server-ip" $@122 ":" "constant string"
#line 2827 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4392 "dhcp6_parser.cc"
    break;

  case 815: // server_port: "server-port" ":" "integer"
#line 2833 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4402 "dhcp6_parser.cc"
    break;

  case 816: // $@123: %empty
#line 2839 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4411 "dhcp6_parser.cc"
    break;

  case 817: // sender_ip: "sender-ip" $@123 ":" "constant string"
#line 2842 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4421 "dhcp6_parser.cc"
    break;

  case 818: // sender_port: "sender-port" ":" "integer"
#line 2848 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4431 "dhcp6_parser.cc"
    break;

  case 819: // max_queue_size: "max-queue-size" ":" "integer"
#line 2854 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4441 "dhcp6_parser.cc"
    break;

  case 820: // $@124: %empty
#line 2860 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4450 "dhcp6_parser.cc"
    break;

  case 821: // ncr_protocol: "ncr-protocol" $@124 ":" ncr_protocol_value
#line 2863 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4459 "dhcp6_parser.cc"
    break;

  case 822: // ncr_protocol_value: "UDP"
#line 2869 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4465 "dhcp6_parser.cc"
    break;

  case 823: // ncr_protocol_value: "TCP"
#line 2870 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4471 "dhcp6_parser.cc"
    break;

  case 824: // $@125: %empty
#line 2873 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4480 "dhcp6_parser.cc"
    break;

  case 825: // ncr_format: "ncr-format" $@125 ":" "JSON"
#line 2876 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4490 "dhcp6_parser.cc"
    break;

  case 826: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2883 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4500 "dhcp6_parser.cc"
    break;

  case 827: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2890 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4510 "dhcp6_parser.cc"
    break;

  case 828: // $@126: %empty
#line 2897 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4519 "dhcp6_parser.cc"
    break;

  case 829: // dep_replace_client_name: "replace-client-name" $@126 ":" ddns_replace_client_name_value
#line 2900 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4528 "dhcp6_parser.cc"
    break;

  case 830: // $@127: %empty
#line 2906 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4537 "dhcp6_parser.cc"
    break;

  case 831: // dep_generated_prefix: "generated-prefix" $@127 ":" "constant string"
#line 2909 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4547 "dhcp6_parser.cc"
    break;

  case 832: // $@128: %empty
#line 2916 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4556 "dhcp6_parser.cc"
    break;

  case 833: // dep_hostname_char_set: "hostname-char-set" $@128 ":" "constant string"
#line 2919 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4566 "dhcp6_parser.cc"
    break;

  case 834: // $@129: %empty
#line 2926 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4575 "dhcp6_parser.cc"
    break;

  case 835: // dep_hostname_char_replacement: "hostname-char-replacement" $@129 ":" "constant string"
#line 2929 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4585 "dhcp6_parser.cc"
    break;

  case 836: // $@130: %empty
#line 2938 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4597 "dhcp6_parser.cc"
    break;

  case 837: // config_control: "config-control" $@130 ":" "{" config_control_params "}"
#line 2944 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4607 "dhcp6_parser.cc"
    break;

  case 838: // $@131: %empty
#line 2950 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4617 "dhcp6_parser.cc"
    break;

  case 839: // sub_config_control: "{" $@131 config_control_params "}"
#line 2954 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4626 "dhcp6_parser.cc"
    break;

  case 842: // config_control_params: config_control_params ","
#line 2962 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4634 "dhcp6_parser.cc"
    break;

  case 845: // $@132: %empty
#line 2972 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4646 "dhcp6_parser.cc"
    break;

  case 846: // config_databases: "config-databases" $@132 ":" "[" database_list "]"
#line 2978 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4655 "dhcp6_parser.cc"
    break;

  case 847: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2983 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4665 "dhcp6_parser.cc"
    break;

  case 848: // $@133: %empty
#line 2991 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4677 "dhcp6_parser.cc"
    break;

  case 849: // loggers: "loggers" $@133 ":" "[" loggers_entries "]"
#line 2997 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4686 "dhcp6_parser.cc"
    break;

  case 852: // loggers_entries: loggers_entries ","
#line 3006 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4694 "dhcp6_parser.cc"
    break;

  case 853: // $@134: %empty
#line 3012 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4704 "dhcp6_parser.cc"
    break;

  case 854: // logger_entry: "{" $@134 logger_params "}"
#line 3016 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4712 "dhcp6_parser.cc"
    break;

  case 857: // logger_params: logger_params ","
#line 3022 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4720 "dhcp6_parser.cc"
    break;

  case 865: // debuglevel: "debuglevel" ":" "integer"
#line 3036 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4730 "dhcp6_parser.cc"
    break;

  case 866: // $@135: %empty
#line 3042 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4739 "dhcp6_parser.cc"
    break;

  case 867: // severity: "severity" $@135 ":" "constant string"
#line 3045 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4749 "dhcp6_parser.cc"
    break;

  case 868: // $@136: %empty
#line 3051 "dhcp6_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4761 "dhcp6_parser.cc"
    break;

  case 869: // output_options_list: "output-options" $@136 ":" "[" output_options_list_content "]"
#line 3057 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4770 "dhcp6_parser.cc"
    break;

  case 872: // output_options_list_content: output_options_list_content ","
#line 3064 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4778 "dhcp6_parser.cc"
    break;

  case 873: // $@137: %empty
#line 3069 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4788 "dhcp6_parser.cc"
    break;

  case 874: // output_entry: "{" $@137 output_params_list "}"
#line 3073 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4796 "dhcp6_parser.cc"
    break;

  case 877: // output_params_list: output_params_list ","
#line 3079 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4804 "dhcp6_parser.cc"
    break;

  case 883: // $@138: %empty
#line 3091 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4813 "dhcp6_parser.cc"
    break;

  case 884: // output: "output" $@138 ":" "constant string"
#line 3094 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4823 "dhcp6_parser.cc"
    break;

  case 885: // flush: "flush" ":" "boolean"
#line 3100 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4833 "dhcp6_parser.cc"
    break;

  case 886: // maxsize: "maxsize" ":" "integer"
#line 3106 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4843 "dhcp6_parser.cc"
    break;

  case 887: // maxver: "maxver" ":" "integer"
#line 3112 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4853 "dhcp6_parser.cc"
    break;

  case 888: // $@139: %empty
#line 3118 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4862 "dhcp6_parser.cc"
    break;

  case 889: // pattern: "pattern" $@139 ":" "constant string"
#line 3121 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4872 "dhcp6_parser.cc"
    break;

  case 890: // $@140: %empty
#line 3127 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4884 "dhcp6_parser.cc"
    break;

  case 891: // compatibility: "compatibility" $@140 ":" "{" compatibility_params "}"
#line 3133 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4893 "dhcp6_parser.cc"
    break;

  case 894: // compatibility_params: compatibility_params ","
#line 3140 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4901 "dhcp6_parser.cc"
    break;

  case 897: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3149 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4911 "dhcp6_parser.cc"
    break;


#line 4915 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1043;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     -26, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043,    36,    34,    35,    82,    90,
     114,   118,   122,   143,   144,   164,   166,   175,   196,   244,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,    34,  -164,
      70,   155,    75,   592,   298,   318,   231,   126,    91,   250,
     -99,   681,    54, -1043,   138,   262,   268,   258,   279, -1043,
      71, -1043, -1043, -1043, -1043, -1043, -1043, -1043,   288,   297,
     316,   317,   322,   326,   334,   343,   344,   358,   359,   370,
     371,   393, -1043,   404,   405,   437,   443,   453, -1043, -1043,
   -1043,   466,   467,   473,   478, -1043, -1043, -1043,   479, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043,   482,   483,   489, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,   490, -1043,
   -1043, -1043, -1043, -1043, -1043,   492,   493,   494, -1043, -1043,
     497, -1043,    74, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043,   499,   500,   503,   504, -1043,    93, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043,   506,   511, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043,    96, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043,   514, -1043, -1043,
   -1043, -1043,   111, -1043, -1043, -1043, -1043, -1043, -1043,   516,
   -1043,   518,   522, -1043, -1043, -1043, -1043, -1043, -1043,   119,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043,   275,   342, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043,   296, -1043, -1043,
     523, -1043, -1043, -1043,   528, -1043, -1043,   423,   448, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043,   532,   533,   534, -1043, -1043, -1043, -1043,   432,
     536, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043,   151, -1043, -1043, -1043,   540, -1043,
   -1043,   543, -1043,   544,   545, -1043, -1043,   547,   548, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043,   161, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043,   550,   290, -1043, -1043, -1043, -1043,
      34,    34, -1043,   225,   552, -1043, -1043,   553,   554,   557,
     560,   561,   562,   345,   346,   350,   360,   361,   364,   365,
     367,   339,   354,   356,   375,   368,   372,   564,   377,   378,
     369,   384,   387,   565,   580,   581,   388,   389,   379,   390,
     596,   597,   601,   394,   615,   619,   622,   623,   624,   627,
     628,   406,   410,   411,   629,   631,   632,   636,   637,   638,
     652,   653,   654,   433,   666,   667,   669,   670,   671,   672,
     449,   451,   459,   674,   677, -1043,   155, -1043,   678,   462,
     463,   469,   470,    75, -1043,   684,   685,   689,   694,   695,
     484,   480,   705,   707,   711,   592, -1043,   712,   491,   298,
   -1043,   714,   495,   715,   507,   508,   318, -1043,   716,   725,
     726,   728,   732,   738,   739, -1043,   231, -1043,   740,   742,
     521,   744,   745,   746,   524, -1043,    91,   749,   526,   541,
     542, -1043,   250,   764,   767,   -95, -1043,   555,   782,   795,
     574,   797,   576,   577,   800,   801,   578,   579,   804,   805,
     806,   807,   681, -1043,   810,   594,    54, -1043, -1043, -1043,
     817,   815,   598,   820,   821,   822,   823,   826, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043,   607, -1043, -1043, -1043, -1043, -1043,  -128,   608,
     610, -1043, -1043, -1043, -1043,   831,   832,   834, -1043,   616,
     617,   160,   835,   836,   620,   301, -1043, -1043, -1043,   839,
     841,   843,   842,   845,   846,   847,   848,   862, -1043,   863,
     864,   865,   866,   649,   650, -1043, -1043, -1043,   849,   871,
   -1043,   874, -1043, -1043, -1043, -1043, -1043,   875,   876,   657,
     658,   659, -1043, -1043,   874,   660,   879, -1043,   662, -1043,
   -1043,   663, -1043,   664, -1043, -1043, -1043,   874,   874,   874,
     665,   668,   673,   676, -1043,   679,   680, -1043,   682,   683,
     686, -1043, -1043,   687, -1043, -1043, -1043, -1043,   688,   836,
   -1043, -1043,   690,   691, -1043,   692, -1043, -1043,   -76,   701,
   -1043, -1043,  -128,   693,   696,   697, -1043,   887, -1043, -1043,
      34,   155, -1043,    54,    75,   355,   355,   888, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043,   889,   890,   895,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043,   896, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043,  -107,    34,    23,   115,
     902,   903,   907,    88,   136,   248,   -23,   -64,   681, -1043,
   -1043,   912,  -177, -1043, -1043,   913,   916, -1043, -1043, -1043,
   -1043, -1043,   757, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043,   888, -1043,   302,   304,   320, -1043, -1043, -1043,
   -1043,   920,   921,   922,   923,   924,   926,   927,   928,   929,
     930, -1043,   931,   932, -1043, -1043, -1043, -1043, -1043,   338,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043,   341, -1043,   933,   850, -1043, -1043,   934,
     935, -1043, -1043,   936,   938, -1043, -1043,   937,   941, -1043,
   -1043,   939,   943, -1043, -1043, -1043,    78, -1043, -1043, -1043,
     942, -1043, -1043, -1043,   137, -1043, -1043, -1043, -1043, -1043,
     373, -1043, -1043, -1043, -1043,   198, -1043, -1043,   944,   946,
   -1043, -1043,   945,   949, -1043,   950,   951,   952,   953,   954,
     955,   374, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043,   956,   957,   958, -1043, -1043, -1043, -1043,   407, -1043,
   -1043, -1043, -1043, -1043, -1043,   959,   960,   961, -1043,   408,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043,   426, -1043, -1043, -1043,   962, -1043,   963, -1043, -1043,
   -1043,   427, -1043, -1043, -1043, -1043, -1043,   434, -1043,   300,
   -1043,   964, -1043,   435, -1043, -1043,   722, -1043,   947,   966,
   -1043, -1043,   965,   967, -1043, -1043,   968,   969, -1043, -1043,
   -1043,   970,   973,   974,   975,   747,   709,   754,   753,   756,
     758,   759,   760,   762,   763,   979,   766,   765,   988,   991,
     996,   998,   355, -1043, -1043,   355, -1043,   888,   592, -1043,
     889,    91, -1043,   890,   250, -1043,   895,   704, -1043,   896,
    -107, -1043, -1043,    23, -1043,   999,  1001,   115, -1043,   234,
     902, -1043,   231, -1043,   903,   -99, -1043,   907,   783,   786,
     790,   791,   803,   819,    88, -1043,  1017,  1023,   828,   844,
     854,   136, -1043,   837,   859,   860,   248, -1043,  1027,  1028,
     -23, -1043,   878,  1029,   893,  1063,   -64, -1043, -1043,    49,
     912, -1043,   911,  -177, -1043, -1043,  1135,  1066,   298, -1043,
     913,   318, -1043,   916, -1043, -1043,   454,   917,   919,   925,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
     447, -1043, -1043,   940,   948,   971,   972, -1043,   436, -1043,
     446, -1043,  1137, -1043,  1141, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043,   450, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043,   977,   978, -1043, -1043, -1043,
    1147, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043,  1144,  1150, -1043, -1043, -1043, -1043, -1043, -1043,
    1146, -1043,   457, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043,   357,   980, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043,   981,   982, -1043, -1043,   983, -1043,    34, -1043, -1043,
    1151, -1043, -1043, -1043, -1043, -1043,   458, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043,   985,   460, -1043,   461, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,   704,
   -1043, -1043, -1043,  1152,  1153,   986, -1043,   234, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,  1154,
     987,  1155,    49, -1043, -1043, -1043, -1043, -1043,   990,   992,
   -1043, -1043,  1156, -1043,   993, -1043, -1043, -1043,  1157, -1043,
   -1043,   321, -1043,   -74,  1157, -1043, -1043,  1158,  1159,  1162,
   -1043,   464, -1043, -1043, -1043, -1043, -1043, -1043, -1043,  1163,
     994,   995,   997,  1164,   -74, -1043,  1000, -1043, -1043, -1043,
    1002, -1043, -1043, -1043
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
     567,    23,   350,    25,   787,    27,   838,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   664,     0,   530,   569,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   141,   836,   197,   218,   220,   222,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   187,     0,     0,     0,     0,     0,   160,   167,
     169,     0,     0,     0,     0,   379,   517,   558,     0,   190,
     192,   173,   461,   617,   619,   453,     0,     0,     0,   306,
     325,   315,   295,   697,   653,   341,   362,   729,     0,   327,
     754,   768,   785,   180,   182,     0,     0,     0,   848,   890,
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
     582,   358,   360,   355,     0,   352,   356,   357,     0,   811,
     813,     0,   816,     0,     0,   820,   824,     0,     0,   828,
     830,   832,   834,   809,   807,   808,     0,   789,   792,   804,
     793,   794,   795,   796,   797,   798,   799,   800,   801,   802,
     803,   805,   806,   845,     0,     0,   840,   843,   844,    47,
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
       0,     0,   791,   788,     0,     0,   842,   839,    51,    43,
       0,     0,     0,     0,     0,     0,     0,     0,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,     0,   185,   186,   157,   158,   159,     0,     0,
       0,   171,   172,   179,   184,     0,     0,     0,   189,     0,
       0,     0,     0,     0,     0,     0,   450,   451,   452,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   753,     0,
       0,     0,     0,     0,     0,   194,   195,   196,     0,     0,
      70,     0,   214,   215,   216,   217,   202,     0,     0,     0,
       0,     0,   459,   460,     0,     0,     0,   391,     0,   616,
     604,     0,   648,     0,   651,   652,   633,     0,     0,     0,
       0,     0,     0,     0,   667,     0,     0,   546,     0,     0,
       0,   557,   533,     0,   589,   590,   591,   572,     0,     0,
     353,   810,     0,     0,   815,     0,   818,   819,     0,     0,
     826,   827,     0,     0,     0,     0,   790,     0,   847,   841,
       0,     0,   142,     0,     0,     0,     0,   224,   188,   162,
     163,   164,   165,   166,   161,   168,   170,   381,   521,   560,
     191,   193,   175,   176,   177,   178,   174,   463,    40,   618,
     620,   455,   456,   457,   458,   454,     0,    48,     0,     0,
       0,   655,   343,     0,     0,     0,     0,     0,     0,   181,
     183,     0,     0,    53,   213,   594,   623,   441,   443,   445,
     449,   447,     0,   615,   647,   650,   693,   681,   683,   685,
     687,   689,   691,   549,   270,   553,   551,   556,   586,   359,
     361,   812,   814,   817,   822,   823,   821,   825,   829,   831,
     833,   835,   224,    44,     0,     0,     0,   257,   262,   264,
     266,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   279,     0,     0,   287,   289,   291,   293,   256,     0,
     231,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   248,   249,   250,   251,   247,   252,
     253,   254,   255,     0,   229,     0,   225,   226,   386,     0,
     382,   383,   526,     0,   522,   523,   565,     0,   561,   562,
     468,     0,   464,   465,   313,   314,     0,   308,   311,   312,
       0,   323,   324,   320,     0,   317,   321,   322,   302,   304,
       0,   297,   300,   301,   702,     0,   699,   660,     0,   656,
     657,   348,     0,   344,   345,     0,     0,     0,     0,     0,
       0,     0,   364,   367,   368,   369,   370,   371,   372,   743,
     749,     0,     0,     0,   742,   739,   740,   741,     0,   731,
     734,   737,   735,   736,   738,     0,     0,     0,   337,     0,
     329,   332,   333,   334,   335,   336,   764,   766,   763,   761,
     762,     0,   756,   759,   760,     0,   780,     0,   783,   776,
     777,     0,   770,   773,   774,   775,   778,     0,   853,     0,
     850,     0,   896,     0,   892,   895,    55,   599,     0,   595,
     596,   628,     0,   624,   625,   696,     0,     0,    64,   837,
     198,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   233,   219,   221,     0,   223,   228,     0,   380,
     385,   530,   518,   525,   569,   559,   564,     0,   462,   467,
     310,   307,   326,   319,   316,     0,     0,   299,   296,   704,
     701,   698,   664,   654,   659,     0,   342,   347,     0,     0,
       0,     0,     0,     0,   366,   363,     0,     0,     0,     0,
       0,   733,   730,     0,     0,     0,   331,   328,     0,     0,
     758,   755,     0,     0,     0,     0,   772,   769,   786,     0,
     852,   849,     0,   894,   891,    57,     0,    56,     0,   593,
     598,     0,   622,   627,   695,   846,     0,     0,     0,     0,
     268,   271,   272,   273,   274,   275,   276,   277,   286,   278,
       0,   284,   285,     0,     0,     0,     0,   232,     0,   227,
       0,   384,     0,   524,     0,   563,   516,   487,   488,   489,
     491,   492,   493,   477,   478,   496,   497,   498,   499,   500,
     503,   504,   505,   506,   507,   508,   509,   510,   511,   512,
     501,   502,   513,   514,   515,   473,   474,   475,   476,   485,
     486,   482,   483,   484,   481,   490,     0,   470,   479,   494,
     495,   480,   466,   309,   318,     0,     0,   298,   724,   726,
       0,   722,   716,   717,   718,   719,   720,   721,   723,   713,
     714,   715,     0,   705,   706,   709,   710,   711,   712,   700,
       0,   658,     0,   346,   373,   374,   375,   376,   377,   378,
     365,     0,     0,   748,   751,   752,   732,   338,   339,   340,
     330,     0,     0,   757,   779,     0,   782,     0,   771,   868,
       0,   866,   864,   858,   862,   863,     0,   855,   860,   861,
     859,   851,   897,   893,    54,    59,     0,   597,     0,   626,
     259,   260,   261,   258,   263,   265,   267,   281,   282,   283,
     280,   288,   290,   292,   294,   230,   387,   527,   566,   472,
     469,   303,   305,     0,     0,     0,   703,   708,   661,   349,
     745,   746,   747,   744,   750,   765,   767,   781,   784,     0,
       0,     0,   857,   854,    58,   600,   629,   471,     0,     0,
     728,   707,     0,   865,     0,   856,   725,   727,     0,   867,
     873,     0,   870,     0,   872,   869,   883,     0,     0,     0,
     888,     0,   875,   878,   879,   880,   881,   882,   871,     0,
       0,     0,     0,     0,   877,   874,     0,   885,   886,   887,
       0,   876,   884,   889
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043,    -5, -1043,  -618, -1043,
     243, -1043, -1043, -1043, -1043,   382, -1043,  -654, -1043, -1043,
   -1043,   -71, -1043, -1043, -1043, -1043, -1043, -1043, -1043,   409,
     644, -1043, -1043,   -61,   -43,   -39,    10,    14,    15,   -24,
     -21,   -17,   -11,    17,    25,    29, -1043,    30,    32,    33,
      37, -1043,   429,    43, -1043,    44, -1043,    47,    50,    51,
   -1043, -1043,    62,    63, -1043,    64, -1043,    65, -1043, -1043,
   -1043, -1043, -1043,    66, -1043,    68, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043,   418,   641, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,   333, -1043,
     120, -1043,  -736,   124, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043,   -41, -1043,  -788, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043,   101, -1043, -1043, -1043, -1043, -1043, -1043, -1043,   109,
    -765, -1043, -1043, -1043, -1043,   107, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043,    77, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043,    94, -1043, -1043, -1043,    97,   599, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043,    92, -1043, -1043, -1043, -1043, -1043,
   -1043, -1042, -1043, -1043, -1043,   125, -1043, -1043, -1043,   129,
     643, -1043, -1043, -1041, -1043, -1040, -1043,    73, -1043,    81,
   -1043,    69,    76,    79,    80, -1043, -1043, -1043, -1038, -1043,
   -1043, -1043, -1043,   121, -1043, -1043,  -120,  1114, -1043, -1043,
   -1043, -1043, -1043,   130, -1043, -1043, -1043,   131, -1043,   618,
   -1043,   -66, -1043, -1043, -1043, -1043, -1043,   -65, -1043, -1043,
   -1043, -1043, -1043,   -16, -1043, -1043, -1043,   132, -1043, -1043,
   -1043,   135, -1043,   613, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043,    86, -1043, -1043, -1043,
      72,   675, -1043, -1043, -1043,   -57, -1043,    -3, -1043, -1043,
   -1043, -1043, -1043,    87, -1043, -1043, -1043,    95,   655, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043,   -45, -1043, -1043, -1043,
     145, -1043, -1043, -1043,   146, -1043,   698,   419, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1036, -1043, -1043, -1043, -1043, -1043,   139, -1043, -1043,
   -1043,   -87, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043,   133, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043,   123, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043,   116, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043,   438,   633, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043,   486,   634, -1043, -1043, -1043, -1043,
   -1043, -1043,   117, -1043, -1043,   -91, -1043, -1043, -1043, -1043,
   -1043, -1043,  -112, -1043, -1043,  -131, -1043, -1043, -1043, -1043,
   -1043, -1043, -1043, -1043, -1043, -1043,   127, -1043
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     779,    87,    88,    41,    68,    84,    85,   804,  1016,  1126,
    1127,   868,    43,    70,    90,   454,    91,    45,    71,   162,
     163,   164,   457,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   483,   764,   183,   484,   184,   485,   185,   186,   187,
     496,   776,   188,   189,   518,   190,   519,   191,   192,   193,
     194,   477,   195,   196,   494,   197,   495,   198,   199,   200,
     201,   459,    47,    72,   238,   239,   240,   528,   241,   242,
     243,   244,   202,   460,   203,   461,   204,   462,   895,   896,
     897,  1055,   869,   870,   871,  1031,  1293,   872,  1032,   873,
    1033,   874,  1034,   875,   876,   569,   877,   878,   879,   880,
     881,   882,   883,   884,   885,  1045,  1300,   886,   887,   888,
     889,  1048,   890,  1049,   891,  1050,   892,  1051,   205,   507,
     930,   931,   932,  1075,   933,  1076,   206,   504,   916,   917,
     918,   919,   207,   506,   924,   925,   926,   927,   208,   505,
     209,   514,   979,   980,   981,   982,   983,   210,   510,   942,
     943,   944,  1085,    63,    80,   404,   405,   406,   583,   407,
     584,   211,   511,   951,   952,   953,   954,   955,   956,   957,
     958,   212,   490,   899,   900,   901,  1058,    49,    73,   286,
     287,   288,   537,   289,   538,   290,   539,   291,   543,   292,
     542,   213,   214,   215,   216,   500,   785,   297,   298,   217,
     497,   911,   912,   913,  1067,  1206,  1207,   218,   491,    57,
      77,   903,   904,   905,  1061,    59,    78,   367,   368,   369,
     370,   371,   372,   373,   568,   374,   572,   375,   571,   376,
     377,   573,   378,   219,   492,   907,   908,   909,  1064,    61,
      79,   389,   390,   391,   392,   393,   577,   394,   395,   396,
     397,   398,   300,   535,  1018,  1019,  1020,  1128,    51,    74,
     312,   313,   314,   547,   315,   220,   498,   221,   499,   303,
     536,  1022,  1023,  1024,  1131,    53,    75,   329,   330,   331,
     551,   332,   333,   553,   334,   335,   222,   509,   938,   939,
     940,  1082,    55,    76,   347,   348,   349,   350,   559,   351,
     560,   352,   561,   353,   562,   354,   563,   355,   564,   356,
     558,   305,   544,  1026,   223,   508,   935,   936,  1079,  1232,
    1233,  1234,  1235,  1236,  1313,  1237,  1314,  1238,   224,   512,
     968,   969,   970,  1096,  1323,   971,   972,  1097,   973,   974,
     225,   226,   515,   991,   992,   993,  1108,   994,  1109,   227,
     516,  1001,  1002,  1003,  1004,  1113,  1005,  1006,  1115,   228,
     517,    65,    81,   426,   427,   428,   429,   588,   430,   589,
     431,   432,   591,   433,   434,   435,   594,   836,   436,   595,
     437,   438,   439,   598,   440,   599,   441,   600,   442,   601,
     229,   458,    67,    82,   445,   446,   447,   604,   448,   230,
     523,  1009,  1010,  1119,  1276,  1277,  1278,  1279,  1331,  1280,
    1329,  1351,  1352,  1353,  1361,  1362,  1363,  1369,  1364,  1365,
    1366,  1367,  1373,   231,   524,  1013,  1014,  1015
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     161,   237,   257,   308,   323,   343,   965,   365,   385,   403,
     423,    38,   258,   387,   388,   245,   301,   316,   327,   345,
     893,   379,   399,   923,   424,  1196,  1197,  1198,   304,  1205,
     259,  1211,   914,  1011,   260,   778,    30,   366,   386,    31,
     810,    32,    42,    33,   133,   134,   401,   402,   160,   264,
     401,   402,   265,   816,   817,   818,   266,   299,   311,   326,
     344,    86,   267,   759,   760,   761,   762,   443,   444,   246,
     302,   317,   328,   346,   455,   380,   400,   526,   425,   456,
      89,  1070,   527,   261,  1071,   133,   134,   262,   263,    44,
     268,   232,   233,   234,   235,   236,   533,    46,   269,   545,
     763,   534,   270,   271,   546,   272,   273,   995,   996,   997,
     274,   778,   834,   835,   549,   358,   275,   276,   915,   550,
     277,    48,   556,   278,   279,    50,   160,   557,  1356,    52,
     359,  1357,  1358,  1359,  1360,   280,   281,   282,   283,   284,
    1073,   285,   293,  1074,   449,   986,   987,   309,   324,   294,
      54,    56,   295,   296,   585,   310,   325,   133,   134,   586,
     959,   998,   914,   921,   602,   922,    92,    93,   852,   603,
      94,    58,   359,    60,   360,   361,    95,    96,    97,   362,
     363,   364,    62,   133,   134,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,   133,
     134,  1080,   160,    64,  1081,   126,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   945,   946,   947,   948,
     949,   950,   928,   929,   133,   134,   128,   129,   130,   131,
    1269,    66,  1270,  1271,   132,   772,   773,   774,   775,    34,
      35,    36,    37,   133,   134,   450,   452,  1196,  1197,  1198,
     135,  1205,   451,  1211,   160,   136,   137,   138,   139,   140,
     141,   142,   453,   565,   143,    98,    99,   100,   101,   102,
     103,   144,   463,   606,   960,   961,   962,   963,   607,   145,
     160,   464,   146,  1120,   567,   526,  1121,   606,   923,   147,
    1028,   127,  1029,   965,   127,   359,   160,   148,   149,  1158,
     465,   466,   150,   533,  1354,   151,   467,  1355,  1030,   152,
     468,   359,   381,   360,   361,   382,   383,   384,   469,   133,
     134,  1052,   133,   134,  1052,   566,  1053,   470,   471,  1054,
     153,   154,   155,   156,   157,   158,   133,   134,   133,   134,
     336,   160,   472,   473,   159,  1218,  1219,  1220,   337,   338,
     339,   340,   341,   342,   474,   475,  1077,  1094,   127,   847,
     160,  1078,  1095,   848,   849,   850,   851,   852,   853,   854,
     855,   856,   857,   858,   859,   860,   861,   476,   127,   306,
     862,   863,   864,   865,   866,   867,   133,   134,   478,   479,
    1101,  1106,   975,   976,   977,  1102,  1107,   781,   782,   783,
     784,   318,   319,   320,   321,   322,   133,   134,   254,  1110,
    1116,   575,   255,   307,  1111,  1117,   359,   602,  1123,  1052,
     581,   480,  1118,  1124,  1305,   608,   609,   481,   254,   545,
     610,   576,   255,  1309,  1306,   161,   160,   482,  1310,   160,
     585,  1332,   237,   549,   556,  1319,  1333,  1374,  1335,  1336,
     486,   487,  1375,   160,   257,   160,   245,   488,   308,  1290,
    1291,  1292,   489,   493,   258,   323,   501,   502,   301,  1297,
    1298,  1299,   316,   503,   513,   343,   520,   521,   522,   327,
     304,   525,   259,   529,   530,   365,   260,   531,   532,   345,
     540,   385,  1320,  1321,  1322,   541,   387,   388,   548,   379,
     552,   264,   554,   160,   265,   399,   555,   570,   266,   299,
     246,   423,   574,   311,   267,   366,   578,   579,   580,   582,
     326,   386,   302,   160,   587,   424,   317,   590,   592,   593,
     344,   596,   597,   328,   605,   261,   611,   612,   613,   262,
     263,   614,   268,   346,   615,   616,   617,   626,   632,   638,
     269,   618,   619,   380,   270,   271,   620,   272,   273,   400,
     160,   627,   274,   628,   639,   640,   621,   622,   275,   276,
     623,   624,   277,   625,   630,   278,   279,   635,   631,   425,
     645,   646,   629,   633,   634,   647,   643,   280,   281,   282,
     283,   284,   636,   285,   293,   637,   641,   642,   644,   649,
     648,   294,   309,   650,   295,   296,   651,   652,   653,   324,
     310,   654,   655,   659,   656,   660,   661,   325,   657,   658,
     662,   663,   664,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   665,   666,   667,   668,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     669,   670,   127,   671,   672,   673,   674,   675,   678,   676,
     161,   679,   681,   237,   129,   130,   131,   677,   687,   688,
     682,   683,   247,   689,   248,   684,   685,   245,   690,   691,
     133,   134,   249,   250,   251,   252,   253,   135,   693,   694,
     692,   695,   136,   137,   138,   696,   698,   699,   701,   703,
     707,   702,   254,   964,   978,   988,   255,   423,   144,   708,
     709,  1012,   710,   704,   705,   256,   711,   966,   984,   989,
     999,   424,   712,   713,   715,   843,   716,   717,   718,   719,
     720,   246,   721,   723,   724,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   728,   725,
     726,   729,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   731,   127,   359,   732,   153,   154,   133,
     134,   967,   985,   990,  1000,   425,   129,   130,   131,   733,
     734,   735,   736,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   133,   134,   747,   250,   251,   160,   253,   135,
     748,   750,   751,   752,   136,   137,   138,   753,   754,   755,
     756,   757,   758,   765,   254,   766,   767,   768,   255,   769,
     777,   770,   771,    32,   786,   780,   787,   256,   788,   789,
     790,   791,   792,  1057,   801,   793,   408,   409,   410,   411,
     412,   413,   414,   415,   416,   417,   418,   419,   420,   794,
     795,   796,   797,   798,   799,   800,   421,   422,   802,   803,
     805,   806,   807,   808,   809,   811,   812,   813,   814,   815,
     819,   837,   842,   820,   337,   894,   898,   902,   821,   153,
     154,   822,   906,   910,   823,   824,   160,   825,   826,   934,
     937,   827,   828,   829,   941,   831,   832,   833,   839,  1008,
    1017,   840,   841,  1021,  1035,  1036,  1037,  1038,  1039,   160,
    1040,  1041,  1042,  1043,  1044,  1046,  1047,  1141,  1060,  1056,
    1059,  1063,  1062,  1065,  1066,  1068,  1069,  1125,  1072,  1084,
    1083,  1086,  1087,  1129,  1088,  1089,  1090,  1091,  1092,  1093,
    1098,  1099,  1100,  1103,  1104,  1105,  1112,  1114,  1122,  1130,
    1133,  1132,   830,  1140,  1136,  1135,  1134,  1137,  1138,  1139,
    1142,  1143,  1144,  1150,  1145,  1146,  1147,   257,  1148,  1149,
     365,  1152,  1153,   385,  1151,  1154,  1166,   258,   387,   388,
    1155,   301,  1156,  1215,   379,  1216,  1167,   399,  1221,  1244,
    1209,   343,  1245,   304,   403,   259,  1246,  1247,  1222,   260,
     366,  1251,  1230,   386,  1168,   345,  1195,  1252,  1169,  1248,
     964,  1261,  1262,  1265,   264,   978,  1223,   265,  1228,   988,
    1224,   266,   299,  1173,   966,  1249,  1174,   267,  1272,   984,
    1175,  1208,  1012,   989,  1253,   302,  1176,   308,   380,   999,
     323,   400,  1274,  1229,  1210,  1257,   344,  1267,   261,  1285,
    1254,   316,   262,   263,   327,   268,  1231,  1170,  1273,   346,
    1255,  1171,  1172,   269,  1177,  1258,  1259,   270,   271,  1225,
     272,   273,  1178,  1226,  1227,   274,  1179,  1180,   967,  1181,
    1182,   275,   276,   985,  1183,   277,  1264,   990,   278,   279,
    1184,  1185,   311,  1000,  1186,   326,  1275,  1187,  1188,  1266,
     280,   281,   282,   283,   284,   317,   285,   293,   328,  1189,
    1190,  1191,  1192,  1193,   294,  1194,  1201,   295,   296,  1282,
    1199,  1284,  1294,  1202,  1295,  1307,  1203,  1204,  1200,  1308,
    1296,  1315,  1316,  1317,  1318,  1330,  1338,  1339,  1342,  1344,
     844,  1348,  1370,  1371,  1350,  1301,  1372,  1376,  1380,   920,
     680,   838,   846,  1302,   686,  1027,  1157,  1159,  1217,  1213,
    1214,  1243,  1242,  1260,   730,  1161,  1250,  1160,   697,  1337,
    1212,   357,  1162,  1163,   722,   727,  1303,  1304,  1165,  1164,
    1286,   309,  1311,  1312,   324,  1324,  1325,  1326,  1327,   310,
    1334,   706,   325,  1343,  1340,  1346,  1287,  1347,  1349,  1239,
    1289,  1378,  1377,  1379,   700,  1382,  1288,  1383,  1240,  1241,
    1341,  1025,  1268,  1263,  1256,   746,  1007,  1281,  1166,   845,
     749,  1345,  1368,  1381,     0,     0,  1221,     0,  1167,     0,
    1283,     0,  1209,     0,     0,     0,  1222,     0,     0,     0,
    1230,  1272,  1328,     0,   714,     0,  1168,     0,  1195,     0,
    1169,     0,     0,     0,  1223,  1274,  1228,     0,  1224,     0,
       0,     0,     0,     0,     0,  1173,     0,     0,  1174,     0,
       0,  1273,  1175,  1208,     0,     0,     0,     0,  1176,     0,
       0,  1229,     0,     0,     0,     0,  1210,     0,     0,     0,
       0,     0,     0,     0,  1231,     0,     0,     0,     0,  1170,
       0,     0,     0,  1171,  1172,     0,  1177,  1225,     0,  1275,
       0,  1226,  1227,     0,  1178,     0,     0,     0,  1179,  1180,
       0,  1181,  1182,     0,     0,     0,  1183,     0,     0,     0,
       0,     0,  1184,  1185,     0,     0,  1186,     0,     0,  1187,
    1188,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1189,  1190,  1191,  1192,  1193,     0,  1194,  1201,     0,
       0,     0,  1199,     0,     0,  1202,     0,     0,  1203,  1204,
    1200
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,   794,    78,    79,    80,
      81,    16,    73,    79,    79,    72,    73,    74,    75,    76,
     756,    78,    79,   788,    81,  1067,  1067,  1067,    73,  1067,
      73,  1067,   139,   210,    73,   653,     0,    78,    79,     5,
     694,     7,     7,     9,   108,   109,   145,   146,   225,    73,
     145,   146,    73,   707,   708,   709,    73,    73,    74,    75,
      76,   225,    73,   191,   192,   193,   194,    13,    14,    72,
      73,    74,    75,    76,     3,    78,    79,     3,    81,     8,
      10,     3,     8,    73,     6,   108,   109,    73,    73,     7,
      73,    16,    17,    18,    19,    20,     3,     7,    73,     3,
     228,     8,    73,    73,     8,    73,    73,   171,   172,   173,
      73,   729,   188,   189,     3,    24,    73,    73,   225,     8,
      73,     7,     3,    73,    73,     7,   225,     8,   202,     7,
      81,   205,   206,   207,   208,    73,    73,    73,    73,    73,
       3,    73,    73,     6,     6,   168,   169,    74,    75,    73,
       7,     7,    73,    73,     3,    74,    75,   108,   109,     8,
      24,   225,   139,   140,     3,   142,    11,    12,    32,     8,
      15,     7,    81,     7,    83,    84,    21,    22,    23,    88,
      89,    90,     7,   108,   109,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   108,
     109,     3,   225,     7,     6,    79,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,   148,   149,   150,   151,
     152,   153,   127,   128,   108,   109,    91,    92,    93,    94,
     201,     7,   203,   204,    99,    95,    96,    97,    98,   225,
     226,   227,   228,   108,   109,     3,     8,  1309,  1309,  1309,
     115,  1309,     4,  1309,   225,   120,   121,   122,   123,   124,
     125,   126,     3,     8,   129,    51,    52,    53,    54,    55,
      56,   136,     4,     3,   158,   159,   160,   161,     8,   144,
     225,     4,   147,     3,     8,     3,     6,     3,  1073,   154,
       8,    80,     8,  1101,    80,    81,   225,   162,   163,  1055,
       4,     4,   167,     3,     3,   170,     4,     6,     8,   174,
       4,    81,    82,    83,    84,    85,    86,    87,     4,   108,
     109,     3,   108,   109,     3,     3,     8,     4,     4,     8,
     195,   196,   197,   198,   199,   200,   108,   109,   108,   109,
     129,   225,     4,     4,   209,   131,   132,   133,   137,   138,
     139,   140,   141,   142,     4,     4,     3,     3,    80,    24,
     225,     8,     8,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,     4,    80,   101,
      45,    46,    47,    48,    49,    50,   108,   109,     4,     4,
       3,     3,   164,   165,   166,     8,     8,   116,   117,   118,
     119,   103,   104,   105,   106,   107,   108,   109,   130,     3,
       3,     8,   134,   135,     8,     8,    81,     3,     3,     3,
       8,     4,     8,     8,     8,   450,   451,     4,   130,     3,
     225,     3,   134,     3,     8,   526,   225,     4,     8,   225,
       3,     3,   533,     3,     3,     8,     8,     3,     8,     8,
       4,     4,     8,   225,   545,   225,   533,     4,   549,    25,
      26,    27,     4,     4,   545,   556,     4,     4,   545,    42,
      43,    44,   549,     4,     4,   566,     4,     4,     4,   556,
     545,     4,   545,     4,     4,   576,   545,     4,     4,   566,
       4,   582,   155,   156,   157,     4,   582,   582,     4,   576,
       4,   545,     4,   225,   545,   582,     4,     4,   545,   545,
     533,   602,     4,   549,   545,   576,     4,     4,     4,     3,
     556,   582,   545,   225,     4,   602,   549,     4,     4,     4,
     566,     4,     4,   556,     4,   545,     4,     4,     4,   545,
     545,     4,   545,   566,     4,     4,     4,   228,     4,     4,
     545,   226,   226,   576,   545,   545,   226,   545,   545,   582,
     225,   227,   545,   227,     4,     4,   226,   226,   545,   545,
     226,   226,   545,   226,   226,   545,   545,   228,   226,   602,
       4,     4,   227,   226,   226,     4,   227,   545,   545,   545,
     545,   545,   228,   545,   545,   228,   228,   228,   228,     4,
     226,   545,   549,     4,   545,   545,     4,     4,     4,   556,
     549,     4,     4,     4,   228,     4,     4,   556,   228,   228,
       4,     4,     4,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,     4,     4,     4,   226,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
       4,     4,    80,     4,     4,     4,     4,   228,     4,   228,
     751,     4,     4,   754,    92,    93,    94,   228,     4,     4,
     228,   228,   100,     4,   102,   226,   226,   754,     4,     4,
     108,   109,   110,   111,   112,   113,   114,   115,   228,     4,
     226,     4,   120,   121,   122,     4,     4,   226,     4,     4,
       4,   226,   130,   794,   795,   796,   134,   798,   136,     4,
       4,   802,     4,   226,   226,   143,     4,   794,   795,   796,
     797,   798,     4,     4,     4,   750,     4,   226,     4,     4,
       4,   754,   228,     4,   228,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,     4,   228,
     228,     4,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,   228,    80,    81,     4,   195,   196,   108,
     109,   794,   795,   796,   797,   798,    92,    93,    94,     4,
     226,     4,   226,   226,     4,     4,   228,   228,     4,     4,
       4,     4,   108,   109,     4,   111,   112,   225,   114,   115,
     226,     4,     7,   225,   120,   121,   122,     7,     7,     7,
       7,     5,   225,   225,   130,   225,     5,     5,   134,     5,
       5,   225,   225,     7,     5,   225,     5,   143,     5,     7,
       5,     5,     5,     3,     5,     7,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,     7,
       7,     7,     7,     7,   225,   225,   195,   196,     7,     5,
       5,     5,   225,   225,   225,   225,     7,   225,   225,   225,
     225,   190,     5,   225,   137,     7,     7,     7,   225,   195,
     196,   225,     7,     7,   225,   225,   225,   225,   225,     7,
       7,   225,   225,   225,     7,   225,   225,   225,   225,     7,
       7,   225,   225,     7,     4,     4,     4,     4,     4,   225,
       4,     4,     4,     4,     4,     4,     4,   228,     3,     6,
       6,     3,     6,     6,     3,     6,     3,   225,     6,     3,
       6,     6,     3,     6,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     3,
       3,     6,   729,   226,     4,     6,     8,     4,     4,     4,
     226,   228,   226,     4,   226,   226,   226,  1058,   226,   226,
    1061,   226,     4,  1064,   228,     4,  1067,  1058,  1064,  1064,
       4,  1058,     4,     4,  1061,     4,  1067,  1064,  1079,   226,
    1067,  1082,   226,  1058,  1085,  1058,   226,   226,  1079,  1058,
    1061,     4,  1079,  1064,  1067,  1082,  1067,     4,  1067,   226,
    1101,     4,     4,     4,  1058,  1106,  1079,  1058,  1079,  1110,
    1079,  1058,  1058,  1067,  1101,   226,  1067,  1058,  1119,  1106,
    1067,  1067,  1123,  1110,   226,  1058,  1067,  1128,  1061,  1116,
    1131,  1064,  1119,  1079,  1067,   228,  1082,     4,  1058,     3,
     226,  1128,  1058,  1058,  1131,  1058,  1079,  1067,  1119,  1082,
     226,  1067,  1067,  1058,  1067,   226,   226,  1058,  1058,  1079,
    1058,  1058,  1067,  1079,  1079,  1058,  1067,  1067,  1101,  1067,
    1067,  1058,  1058,  1106,  1067,  1058,   228,  1110,  1058,  1058,
    1067,  1067,  1128,  1116,  1067,  1131,  1119,  1067,  1067,   226,
    1058,  1058,  1058,  1058,  1058,  1128,  1058,  1058,  1131,  1067,
    1067,  1067,  1067,  1067,  1058,  1067,  1067,  1058,  1058,   228,
    1067,     6,   225,  1067,   225,     8,  1067,  1067,  1067,     8,
     225,     4,     8,     3,     8,     4,     4,     4,     4,     4,
     751,     5,     4,     4,     7,   225,     4,     4,     4,   787,
     526,   742,   754,   225,   533,   842,  1052,  1057,  1077,  1070,
    1073,  1087,  1085,  1106,   585,  1060,  1094,  1058,   545,  1309,
    1069,    77,  1061,  1063,   576,   582,   225,   225,  1066,  1064,
    1128,  1128,   225,   225,  1131,   225,   225,   225,   225,  1128,
     225,   556,  1131,   226,   228,   225,  1130,   225,   225,  1080,
    1133,   226,   228,   226,   549,   225,  1131,   225,  1082,  1084,
    1317,   812,  1116,  1110,  1101,   602,   798,  1120,  1309,   753,
     606,  1332,  1354,  1374,    -1,    -1,  1317,    -1,  1309,    -1,
    1123,    -1,  1309,    -1,    -1,    -1,  1317,    -1,    -1,    -1,
    1317,  1332,  1267,    -1,   566,    -1,  1309,    -1,  1309,    -1,
    1309,    -1,    -1,    -1,  1317,  1332,  1317,    -1,  1317,    -1,
      -1,    -1,    -1,    -1,    -1,  1309,    -1,    -1,  1309,    -1,
      -1,  1332,  1309,  1309,    -1,    -1,    -1,    -1,  1309,    -1,
      -1,  1317,    -1,    -1,    -1,    -1,  1309,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1317,    -1,    -1,    -1,    -1,  1309,
      -1,    -1,    -1,  1309,  1309,    -1,  1309,  1317,    -1,  1332,
      -1,  1317,  1317,    -1,  1309,    -1,    -1,    -1,  1309,  1309,
      -1,  1309,  1309,    -1,    -1,    -1,  1309,    -1,    -1,    -1,
      -1,    -1,  1309,  1309,    -1,    -1,  1309,    -1,    -1,  1309,
    1309,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1309,  1309,  1309,  1309,  1309,    -1,  1309,  1309,    -1,
      -1,    -1,  1309,    -1,    -1,  1309,    -1,    -1,  1309,  1309,
    1309
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
       0,     5,     7,     9,   225,   226,   227,   228,   245,   246,
     247,   252,     7,   261,     7,   266,     7,   321,     7,   436,
       7,   517,     7,   534,     7,   551,     7,   468,     7,   474,
       7,   498,     7,   412,     7,   620,     7,   651,   253,   248,
     262,   267,   322,   437,   518,   535,   552,   469,   475,   499,
     413,   621,   652,   245,   254,   255,   225,   250,   251,    10,
     263,   265,    11,    12,    15,    21,    22,    23,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    91,    92,
      93,    94,    99,   108,   109,   115,   120,   121,   122,   123,
     124,   125,   126,   129,   136,   144,   147,   154,   162,   163,
     167,   170,   174,   195,   196,   197,   198,   199,   200,   209,
     225,   260,   268,   269,   270,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   292,   294,   296,   297,   298,   301,   302,
     304,   306,   307,   308,   309,   311,   312,   314,   316,   317,
     318,   319,   331,   333,   335,   377,   385,   391,   397,   399,
     406,   420,   430,   450,   451,   452,   453,   458,   466,   492,
     524,   526,   545,   573,   587,   599,   600,   608,   618,   649,
     658,   682,    16,    17,    18,    19,    20,   260,   323,   324,
     325,   327,   328,   329,   330,   524,   526,   100,   102,   110,
     111,   112,   113,   114,   130,   134,   143,   260,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   286,   287,   288,   289,   292,   294,   296,   297,   298,
     301,   302,   304,   306,   312,   314,   438,   439,   440,   442,
     444,   446,   448,   450,   451,   452,   453,   456,   457,   492,
     511,   524,   526,   528,   545,   570,   101,   135,   260,   446,
     448,   492,   519,   520,   521,   523,   524,   526,   103,   104,
     105,   106,   107,   260,   446,   448,   492,   524,   526,   536,
     537,   538,   540,   541,   543,   544,   129,   137,   138,   139,
     140,   141,   142,   260,   492,   524,   526,   553,   554,   555,
     556,   558,   560,   562,   564,   566,   568,   466,    24,    81,
      83,    84,    88,    89,    90,   260,   353,   476,   477,   478,
     479,   480,   481,   482,   484,   486,   488,   489,   491,   524,
     526,    82,    85,    86,    87,   260,   353,   480,   486,   500,
     501,   502,   503,   504,   506,   507,   508,   509,   510,   524,
     526,   145,   146,   260,   414,   415,   416,   418,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   195,   196,   260,   524,   526,   622,   623,   624,   625,
     627,   629,   630,   632,   633,   634,   637,   639,   640,   641,
     643,   645,   647,    13,    14,   653,   654,   655,   657,     6,
       3,     4,     8,     3,   264,     3,     8,   271,   650,   320,
     332,   334,   336,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   310,     4,     4,
       4,     4,     4,   290,   293,   295,     4,     4,     4,     4,
     431,   467,   493,     4,   313,   315,   299,   459,   525,   527,
     454,     4,     4,     4,   386,   398,   392,   378,   574,   546,
     407,   421,   588,     4,   400,   601,   609,   619,   303,   305,
       4,     4,     4,   659,   683,     4,     3,     8,   326,     4,
       4,     4,     4,     3,     8,   512,   529,   441,   443,   445,
       4,     4,   449,   447,   571,     3,     8,   522,     4,     3,
       8,   539,     4,   542,     4,     4,     3,     8,   569,   557,
     559,   561,   563,   565,   567,     8,     3,     8,   483,   354,
       4,   487,   485,   490,     4,     8,     3,   505,     4,     4,
       4,     8,     3,   417,   419,     3,     8,     4,   626,   628,
       4,   631,     4,     4,   635,   638,     4,     4,   642,   644,
     646,   648,     3,     8,   656,     4,     3,     8,   245,   245,
     225,     4,     4,     4,     4,     4,     4,     4,   226,   226,
     226,   226,   226,   226,   226,   226,   228,   227,   227,   227,
     226,   226,     4,   226,   226,   228,   228,   228,     4,     4,
       4,   228,   228,   227,   228,     4,     4,     4,   226,     4,
       4,     4,     4,     4,     4,     4,   228,   228,   228,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   226,     4,
       4,     4,     4,     4,     4,   228,   228,   228,     4,     4,
     269,     4,   228,   228,   226,   226,   324,     4,     4,     4,
       4,     4,   226,   228,     4,     4,     4,   439,     4,   226,
     520,     4,   226,     4,   226,   226,   537,     4,     4,     4,
       4,     4,     4,     4,   555,     4,     4,   226,     4,     4,
       4,   228,   478,     4,   228,   228,   228,   502,     4,     4,
     415,   228,     4,     4,   226,     4,   226,   226,     4,     4,
     228,   228,     4,     4,     4,     4,   623,     4,   226,   654,
       4,     7,   225,     7,     7,     7,     7,     5,   225,   191,
     192,   193,   194,   228,   291,   225,   225,     5,     5,     5,
     225,   225,    95,    96,    97,    98,   300,     5,   247,   249,
     225,   116,   117,   118,   119,   455,     5,     5,     5,     7,
       5,     5,     5,     7,     7,     7,     7,     7,     7,   225,
     225,     5,     7,     5,   256,     5,     5,   225,   225,   225,
     256,   225,     7,   225,   225,   225,   256,   256,   256,   225,
     225,   225,   225,   225,   225,   225,   225,   225,   225,   225,
     249,   225,   225,   225,   188,   189,   636,   190,   291,   225,
     225,   225,     5,   245,   268,   653,   323,    24,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    45,    46,    47,    48,    49,    50,   260,   341,
     342,   343,   346,   348,   350,   352,   353,   355,   356,   357,
     358,   359,   360,   361,   362,   363,   366,   367,   368,   369,
     371,   373,   375,   341,     7,   337,   338,   339,     7,   432,
     433,   434,     7,   470,   471,   472,     7,   494,   495,   496,
       7,   460,   461,   462,   139,   225,   387,   388,   389,   390,
     254,   140,   142,   389,   393,   394,   395,   396,   127,   128,
     379,   380,   381,   383,     7,   575,   576,     7,   547,   548,
     549,     7,   408,   409,   410,   148,   149,   150,   151,   152,
     153,   422,   423,   424,   425,   426,   427,   428,   429,    24,
     158,   159,   160,   161,   260,   355,   524,   526,   589,   590,
     591,   594,   595,   597,   598,   164,   165,   166,   260,   401,
     402,   403,   404,   405,   524,   526,   168,   169,   260,   524,
     526,   602,   603,   604,   606,   171,   172,   173,   225,   524,
     526,   610,   611,   612,   613,   615,   616,   622,     7,   660,
     661,   210,   260,   684,   685,   686,   257,     7,   513,   514,
     515,     7,   530,   531,   532,   556,   572,   337,     8,     8,
       8,   344,   347,   349,   351,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   364,     4,     4,   370,   372,
     374,   376,     3,     8,     8,   340,     6,     3,   435,     6,
       3,   473,     6,     3,   497,     6,     3,   463,     6,     3,
       3,     6,     6,     3,     6,   382,   384,     3,     8,   577,
       3,     6,   550,     6,     3,   411,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,   592,   596,     4,     4,
       4,     3,     8,     4,     4,     4,     3,     8,   605,   607,
       3,     8,     4,   614,     4,   617,     3,     8,     8,   662,
       3,     6,     4,     3,     8,   225,   258,   259,   516,     6,
       3,   533,     6,     3,     8,     6,     4,     4,     4,     4,
     226,   228,   226,   228,   226,   226,   226,   226,   226,   226,
       4,   228,   226,     4,     4,     4,     4,   342,   341,   339,
     438,   434,   476,   472,   500,   496,   260,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     286,   287,   288,   289,   292,   294,   296,   297,   298,   301,
     302,   304,   306,   312,   314,   353,   430,   442,   444,   446,
     448,   450,   451,   452,   453,   457,   464,   465,   492,   524,
     526,   570,   462,   388,   394,     4,     4,   380,   131,   132,
     133,   260,   272,   273,   274,   275,   276,   277,   353,   492,
     524,   526,   578,   579,   580,   581,   582,   584,   586,   576,
     553,   549,   414,   410,   226,   226,   226,   226,   226,   226,
     423,     4,     4,   226,   226,   226,   590,   228,   226,   226,
     402,     4,     4,   603,   228,     4,   226,     4,   611,   201,
     203,   204,   260,   353,   524,   526,   663,   664,   665,   666,
     668,   661,   228,   685,     6,     3,   519,   515,   536,   532,
      25,    26,    27,   345,   225,   225,   225,    42,    43,    44,
     365,   225,   225,   225,   225,     8,     8,     8,     8,     3,
       8,   225,   225,   583,   585,     4,     8,     3,     8,     8,
     155,   156,   157,   593,   225,   225,   225,   225,   245,   669,
       4,   667,     3,     8,   225,     8,     8,   465,     4,     4,
     228,   580,     4,   226,     4,   664,   225,   225,     5,   225,
       7,   670,   671,   672,     3,     6,   202,   205,   206,   207,
     208,   673,   674,   675,   677,   678,   679,   680,   671,   676,
       4,     4,     4,   681,     3,     8,     4,   228,   226,   226,
       4,   674,   225,   225
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   229,   231,   230,   232,   230,   233,   230,   234,   230,
     235,   230,   236,   230,   237,   230,   238,   230,   239,   230,
     240,   230,   241,   230,   242,   230,   243,   230,   244,   230,
     245,   245,   245,   245,   245,   245,   245,   246,   248,   247,
     249,   250,   250,   251,   251,   251,   253,   252,   254,   254,
     255,   255,   255,   257,   256,   258,   258,   259,   259,   259,
     260,   262,   261,   264,   263,   263,   265,   267,   266,   268,
     268,   268,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   271,   270,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     290,   289,   291,   291,   291,   291,   291,   293,   292,   295,
     294,   296,   297,   299,   298,   300,   300,   300,   300,   301,
     303,   302,   305,   304,   306,   307,   308,   310,   309,   311,
     313,   312,   315,   314,   316,   317,   318,   320,   319,   322,
     321,   323,   323,   323,   324,   324,   324,   324,   324,   324,
     324,   324,   326,   325,   327,   328,   329,   330,   332,   331,
     334,   333,   336,   335,   337,   337,   338,   338,   338,   340,
     339,   341,   341,   341,   342,   342,   342,   342,   342,   342,
     342,   342,   342,   342,   342,   342,   342,   342,   342,   342,
     342,   342,   342,   342,   342,   342,   342,   344,   343,   345,
     345,   345,   347,   346,   349,   348,   351,   350,   352,   354,
     353,   355,   356,   357,   358,   359,   360,   361,   362,   364,
     363,   365,   365,   365,   366,   367,   368,   370,   369,   372,
     371,   374,   373,   376,   375,   378,   377,   379,   379,   379,
     380,   380,   382,   381,   384,   383,   386,   385,   387,   387,
     387,   388,   388,   389,   390,   392,   391,   393,   393,   393,
     394,   394,   394,   395,   396,   398,   397,   400,   399,   401,
     401,   401,   402,   402,   402,   402,   402,   402,   403,   404,
     405,   407,   406,   408,   408,   409,   409,   409,   411,   410,
     413,   412,   414,   414,   414,   414,   415,   415,   417,   416,
     419,   418,   421,   420,   422,   422,   422,   423,   423,   423,
     423,   423,   423,   424,   425,   426,   427,   428,   429,   431,
     430,   432,   432,   433,   433,   433,   435,   434,   437,   436,
     438,   438,   438,   439,   439,   439,   439,   439,   439,   439,
     439,   439,   439,   439,   439,   439,   439,   439,   439,   439,
     439,   439,   439,   439,   439,   439,   439,   439,   439,   439,
     439,   439,   439,   439,   439,   439,   439,   439,   439,   439,
     439,   439,   439,   439,   439,   439,   439,   439,   439,   439,
     441,   440,   443,   442,   445,   444,   447,   446,   449,   448,
     450,   451,   452,   454,   453,   455,   455,   455,   455,   456,
     457,   459,   458,   460,   460,   461,   461,   461,   463,   462,
     464,   464,   464,   465,   465,   465,   465,   465,   465,   465,
     465,   465,   465,   465,   465,   465,   465,   465,   465,   465,
     465,   465,   465,   465,   465,   465,   465,   465,   465,   465,
     465,   465,   465,   465,   465,   465,   465,   465,   465,   465,
     465,   465,   465,   465,   465,   465,   465,   467,   466,   469,
     468,   470,   470,   471,   471,   471,   473,   472,   475,   474,
     476,   476,   477,   477,   477,   478,   478,   478,   478,   478,
     478,   478,   478,   478,   478,   479,   480,   481,   483,   482,
     485,   484,   487,   486,   488,   490,   489,   491,   493,   492,
     494,   494,   495,   495,   495,   497,   496,   499,   498,   500,
     500,   501,   501,   501,   502,   502,   502,   502,   502,   502,
     502,   502,   502,   502,   503,   505,   504,   506,   507,   508,
     509,   510,   512,   511,   513,   513,   514,   514,   514,   516,
     515,   518,   517,   519,   519,   519,   520,   520,   520,   520,
     520,   520,   520,   520,   522,   521,   523,   525,   524,   527,
     526,   529,   528,   530,   530,   531,   531,   531,   533,   532,
     535,   534,   536,   536,   536,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   537,   537,   539,   538,   540,   542,
     541,   543,   544,   546,   545,   547,   547,   548,   548,   548,
     550,   549,   552,   551,   553,   553,   554,   554,   554,   555,
     555,   555,   555,   555,   555,   555,   555,   555,   555,   555,
     557,   556,   559,   558,   561,   560,   563,   562,   565,   564,
     567,   566,   569,   568,   571,   570,   572,   574,   573,   575,
     575,   575,   577,   576,   578,   578,   579,   579,   579,   580,
     580,   580,   580,   580,   580,   580,   580,   580,   580,   580,
     580,   580,   580,   581,   583,   582,   585,   584,   586,   588,
     587,   589,   589,   589,   590,   590,   590,   590,   590,   590,
     590,   590,   590,   592,   591,   593,   593,   593,   594,   596,
     595,   597,   598,   599,   601,   600,   602,   602,   602,   603,
     603,   603,   603,   603,   605,   604,   607,   606,   609,   608,
     610,   610,   610,   611,   611,   611,   611,   611,   611,   612,
     614,   613,   615,   617,   616,   619,   618,   621,   620,   622,
     622,   622,   623,   623,   623,   623,   623,   623,   623,   623,
     623,   623,   623,   623,   623,   623,   623,   623,   623,   623,
     624,   626,   625,   628,   627,   629,   631,   630,   632,   633,
     635,   634,   636,   636,   638,   637,   639,   640,   642,   641,
     644,   643,   646,   645,   648,   647,   650,   649,   652,   651,
     653,   653,   653,   654,   654,   656,   655,   657,   659,   658,
     660,   660,   660,   662,   661,   663,   663,   663,   664,   664,
     664,   664,   664,   664,   664,   665,   667,   666,   669,   668,
     670,   670,   670,   672,   671,   673,   673,   673,   674,   674,
     674,   674,   674,   676,   675,   677,   678,   679,   681,   680,
     683,   682,   684,   684,   684,   685,   685,   686
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     3,     3,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     2,     1,     1,     0,     6,     3,     0,     6,
       1,     3,     2,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     0,     6,
       1,     3,     2,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     0,     4,     3,     3,     3,     0,     4,
       0,     6,     1,     3,     2,     1,     1,     3
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
  "dhcp_ddns_param", "enable_updates", "dep_qualifying_suffix", "$@121",
  "server_ip", "$@122", "server_port", "sender_ip", "$@123", "sender_port",
  "max_queue_size", "ncr_protocol", "$@124", "ncr_protocol_value",
  "ncr_format", "$@125", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@126",
  "dep_generated_prefix", "$@127", "dep_hostname_char_set", "$@128",
  "dep_hostname_char_replacement", "$@129", "config_control", "$@130",
  "sub_config_control", "$@131", "config_control_params",
  "config_control_param", "config_databases", "$@132",
  "config_fetch_wait_time", "loggers", "$@133", "loggers_entries",
  "logger_entry", "$@134", "logger_params", "logger_param", "debuglevel",
  "severity", "$@135", "output_options_list", "$@136",
  "output_options_list_content", "output_entry", "$@137",
  "output_params_list", "output_params", "output", "$@138", "flush",
  "maxsize", "maxver", "pattern", "$@139", "compatibility", "$@140",
  "compatibility_params", "compatibility_param", "lenient_option_parsing", YY_NULLPTR
  };
#endif


#if PARSER6_DEBUG
  const short
  Dhcp6Parser::yyrline_[] =
  {
       0,   323,   323,   323,   324,   324,   325,   325,   326,   326,
     327,   327,   328,   328,   329,   329,   330,   330,   331,   331,
     332,   332,   333,   333,   334,   334,   335,   335,   336,   336,
     344,   345,   346,   347,   348,   349,   350,   353,   358,   358,
     369,   372,   373,   376,   381,   387,   392,   392,   399,   400,
     403,   407,   411,   417,   417,   424,   425,   428,   432,   436,
     446,   455,   455,   470,   470,   484,   487,   493,   493,   502,
     503,   504,   511,   512,   513,   514,   515,   516,   517,   518,
     519,   520,   521,   522,   523,   524,   525,   526,   527,   528,
     529,   530,   531,   532,   533,   534,   535,   536,   537,   538,
     539,   540,   541,   542,   543,   544,   545,   546,   547,   548,
     549,   550,   551,   552,   553,   554,   555,   556,   557,   558,
     559,   560,   561,   562,   563,   564,   565,   566,   567,   568,
     569,   570,   571,   572,   573,   574,   575,   576,   577,   578,
     579,   582,   582,   591,   597,   603,   609,   615,   621,   627,
     633,   639,   645,   651,   657,   663,   669,   675,   681,   687,
     693,   693,   702,   705,   708,   711,   714,   720,   720,   729,
     729,   738,   747,   757,   757,   766,   769,   772,   775,   780,
     786,   786,   795,   795,   804,   810,   816,   822,   822,   831,
     837,   837,   846,   846,   855,   861,   867,   873,   873,   885,
     885,   894,   895,   896,   901,   902,   903,   904,   905,   906,
     907,   908,   911,   911,   922,   928,   934,   940,   946,   946,
     959,   959,   972,   972,   983,   984,   987,   988,   989,   994,
     994,  1004,  1005,  1006,  1011,  1012,  1013,  1014,  1015,  1016,
    1017,  1018,  1019,  1020,  1021,  1022,  1023,  1024,  1025,  1026,
    1027,  1028,  1029,  1030,  1031,  1032,  1033,  1036,  1036,  1044,
    1045,  1046,  1049,  1049,  1058,  1058,  1067,  1067,  1076,  1082,
    1082,  1091,  1097,  1103,  1109,  1115,  1121,  1127,  1134,  1140,
    1140,  1148,  1149,  1150,  1153,  1159,  1165,  1171,  1171,  1180,
    1180,  1189,  1189,  1198,  1198,  1207,  1207,  1218,  1219,  1220,
    1225,  1226,  1229,  1229,  1248,  1248,  1266,  1266,  1277,  1278,
    1279,  1284,  1285,  1288,  1293,  1298,  1298,  1309,  1310,  1311,
    1316,  1317,  1318,  1321,  1326,  1333,  1333,  1346,  1346,  1359,
    1360,  1361,  1366,  1367,  1368,  1369,  1370,  1371,  1374,  1380,
    1386,  1392,  1392,  1403,  1404,  1407,  1408,  1409,  1414,  1414,
    1424,  1424,  1434,  1435,  1436,  1439,  1442,  1443,  1446,  1446,
    1455,  1455,  1464,  1464,  1476,  1477,  1478,  1483,  1484,  1485,
    1486,  1487,  1488,  1491,  1497,  1503,  1509,  1515,  1521,  1530,
    1530,  1544,  1545,  1548,  1549,  1550,  1559,  1559,  1585,  1585,
    1596,  1597,  1598,  1604,  1605,  1606,  1607,  1608,  1609,  1610,
    1611,  1612,  1613,  1614,  1615,  1616,  1617,  1618,  1619,  1620,
    1621,  1622,  1623,  1624,  1625,  1626,  1627,  1628,  1629,  1630,
    1631,  1632,  1633,  1634,  1635,  1636,  1637,  1638,  1639,  1640,
    1641,  1642,  1643,  1644,  1645,  1646,  1647,  1648,  1649,  1650,
    1653,  1653,  1662,  1662,  1671,  1671,  1680,  1680,  1689,  1689,
    1700,  1706,  1712,  1718,  1718,  1726,  1727,  1728,  1729,  1732,
    1738,  1746,  1746,  1758,  1759,  1763,  1764,  1765,  1770,  1770,
    1778,  1779,  1780,  1785,  1786,  1787,  1788,  1789,  1790,  1791,
    1792,  1793,  1794,  1795,  1796,  1797,  1798,  1799,  1800,  1801,
    1802,  1803,  1804,  1805,  1806,  1807,  1808,  1809,  1810,  1811,
    1812,  1813,  1814,  1815,  1816,  1817,  1818,  1819,  1820,  1821,
    1822,  1823,  1824,  1825,  1826,  1827,  1828,  1835,  1835,  1849,
    1849,  1858,  1859,  1862,  1863,  1864,  1871,  1871,  1886,  1886,
    1900,  1901,  1904,  1905,  1906,  1911,  1912,  1913,  1914,  1915,
    1916,  1917,  1918,  1919,  1920,  1923,  1925,  1931,  1933,  1933,
    1942,  1942,  1951,  1951,  1960,  1962,  1962,  1971,  1981,  1981,
    1994,  1995,  2000,  2001,  2002,  2009,  2009,  2021,  2021,  2033,
    2034,  2039,  2040,  2041,  2048,  2049,  2050,  2051,  2052,  2053,
    2054,  2055,  2056,  2057,  2060,  2062,  2062,  2071,  2073,  2075,
    2081,  2087,  2096,  2096,  2109,  2110,  2113,  2114,  2115,  2120,
    2120,  2130,  2130,  2140,  2141,  2142,  2147,  2148,  2149,  2150,
    2151,  2152,  2153,  2154,  2157,  2157,  2166,  2172,  2172,  2197,
    2197,  2227,  2227,  2240,  2241,  2244,  2245,  2246,  2251,  2251,
    2263,  2263,  2275,  2276,  2277,  2282,  2283,  2284,  2285,  2286,
    2287,  2288,  2289,  2290,  2291,  2292,  2295,  2295,  2304,  2310,
    2310,  2319,  2325,  2334,  2334,  2345,  2346,  2349,  2350,  2351,
    2356,  2356,  2365,  2365,  2374,  2375,  2378,  2379,  2380,  2386,
    2387,  2388,  2389,  2390,  2391,  2392,  2393,  2394,  2395,  2396,
    2399,  2399,  2410,  2410,  2421,  2421,  2430,  2430,  2439,  2439,
    2448,  2448,  2457,  2457,  2471,  2471,  2482,  2488,  2488,  2499,
    2500,  2501,  2506,  2506,  2516,  2517,  2520,  2521,  2522,  2527,
    2528,  2529,  2530,  2531,  2532,  2533,  2534,  2535,  2536,  2537,
    2538,  2539,  2540,  2543,  2545,  2545,  2554,  2554,  2563,  2572,
    2572,  2585,  2586,  2587,  2592,  2593,  2594,  2595,  2596,  2597,
    2598,  2599,  2600,  2603,  2603,  2611,  2612,  2613,  2616,  2622,
    2622,  2631,  2637,  2645,  2653,  2653,  2664,  2665,  2666,  2671,
    2672,  2673,  2674,  2675,  2678,  2678,  2687,  2687,  2699,  2699,
    2712,  2713,  2714,  2719,  2720,  2721,  2722,  2723,  2724,  2727,
    2733,  2733,  2742,  2748,  2748,  2758,  2758,  2771,  2771,  2781,
    2782,  2783,  2788,  2789,  2790,  2791,  2792,  2793,  2794,  2795,
    2796,  2797,  2798,  2799,  2800,  2801,  2802,  2803,  2804,  2805,
    2808,  2815,  2815,  2824,  2824,  2833,  2839,  2839,  2848,  2854,
    2860,  2860,  2869,  2870,  2873,  2873,  2883,  2890,  2897,  2897,
    2906,  2906,  2916,  2916,  2926,  2926,  2938,  2938,  2950,  2950,
    2960,  2961,  2962,  2968,  2969,  2972,  2972,  2983,  2991,  2991,
    3004,  3005,  3006,  3012,  3012,  3020,  3021,  3022,  3027,  3028,
    3029,  3030,  3031,  3032,  3033,  3036,  3042,  3042,  3051,  3051,
    3062,  3063,  3064,  3069,  3069,  3077,  3078,  3079,  3084,  3085,
    3086,  3087,  3088,  3091,  3091,  3100,  3106,  3112,  3118,  3118,
    3127,  3127,  3138,  3139,  3140,  3145,  3146,  3149
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
#line 6612 "dhcp6_parser.cc"

#line 3155 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
