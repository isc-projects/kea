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

  case 256: // $@38: %empty
#line 1035 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1889 "dhcp6_parser.cc"
    break;

  case 257: // database_type: "type" $@38 ":" db_type
#line 1038 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1898 "dhcp6_parser.cc"
    break;

  case 258: // db_type: "memfile"
#line 1043 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1904 "dhcp6_parser.cc"
    break;

  case 259: // db_type: "mysql"
#line 1044 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1910 "dhcp6_parser.cc"
    break;

  case 260: // db_type: "postgresql"
#line 1045 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1916 "dhcp6_parser.cc"
    break;

  case 261: // $@39: %empty
#line 1048 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1925 "dhcp6_parser.cc"
    break;

  case 262: // user: "user" $@39 ":" "constant string"
#line 1051 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1935 "dhcp6_parser.cc"
    break;

  case 263: // $@40: %empty
#line 1057 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1944 "dhcp6_parser.cc"
    break;

  case 264: // password: "password" $@40 ":" "constant string"
#line 1060 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1954 "dhcp6_parser.cc"
    break;

  case 265: // $@41: %empty
#line 1066 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1963 "dhcp6_parser.cc"
    break;

  case 266: // host: "host" $@41 ":" "constant string"
#line 1069 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1973 "dhcp6_parser.cc"
    break;

  case 267: // port: "port" ":" "integer"
#line 1075 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1983 "dhcp6_parser.cc"
    break;

  case 268: // $@42: %empty
#line 1081 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1992 "dhcp6_parser.cc"
    break;

  case 269: // name: "name" $@42 ":" "constant string"
#line 1084 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2002 "dhcp6_parser.cc"
    break;

  case 270: // persist: "persist" ":" "boolean"
#line 1090 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2012 "dhcp6_parser.cc"
    break;

  case 271: // lfc_interval: "lfc-interval" ":" "integer"
#line 1096 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2022 "dhcp6_parser.cc"
    break;

  case 272: // readonly: "readonly" ":" "boolean"
#line 1102 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2032 "dhcp6_parser.cc"
    break;

  case 273: // connect_timeout: "connect-timeout" ":" "integer"
#line 1108 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2042 "dhcp6_parser.cc"
    break;

  case 274: // read_timeout: "read-timeout" ":" "integer"
#line 1114 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2052 "dhcp6_parser.cc"
    break;

  case 275: // write_timeout: "write-timeout" ":" "integer"
#line 1120 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2062 "dhcp6_parser.cc"
    break;

  case 276: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1126 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2072 "dhcp6_parser.cc"
    break;

  case 277: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1133 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2082 "dhcp6_parser.cc"
    break;

  case 278: // $@43: %empty
#line 1139 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2091 "dhcp6_parser.cc"
    break;

  case 279: // on_fail: "on-fail" $@43 ":" on_fail_mode
#line 1142 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2100 "dhcp6_parser.cc"
    break;

  case 280: // on_fail_mode: "stop-retry-exit"
#line 1147 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2106 "dhcp6_parser.cc"
    break;

  case 281: // on_fail_mode: "serve-retry-exit"
#line 1148 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2112 "dhcp6_parser.cc"
    break;

  case 282: // on_fail_mode: "serve-retry-continue"
#line 1149 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2118 "dhcp6_parser.cc"
    break;

  case 283: // max_row_errors: "max-row-errors" ":" "integer"
#line 1152 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2128 "dhcp6_parser.cc"
    break;

  case 284: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1158 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2138 "dhcp6_parser.cc"
    break;

  case 285: // $@44: %empty
#line 1164 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2147 "dhcp6_parser.cc"
    break;

  case 286: // trust_anchor: "trust-anchor" $@44 ":" "constant string"
#line 1167 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2157 "dhcp6_parser.cc"
    break;

  case 287: // $@45: %empty
#line 1173 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2166 "dhcp6_parser.cc"
    break;

  case 288: // cert_file: "cert-file" $@45 ":" "constant string"
#line 1176 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2176 "dhcp6_parser.cc"
    break;

  case 289: // $@46: %empty
#line 1182 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2185 "dhcp6_parser.cc"
    break;

  case 290: // key_file: "key-file" $@46 ":" "constant string"
#line 1185 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2195 "dhcp6_parser.cc"
    break;

  case 291: // $@47: %empty
#line 1191 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2204 "dhcp6_parser.cc"
    break;

  case 292: // cipher_list: "cipher-list" $@47 ":" "constant string"
#line 1194 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2214 "dhcp6_parser.cc"
    break;

  case 293: // $@48: %empty
#line 1200 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2226 "dhcp6_parser.cc"
    break;

  case 294: // sanity_checks: "sanity-checks" $@48 ":" "{" sanity_checks_params "}"
#line 1206 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2235 "dhcp6_parser.cc"
    break;

  case 297: // sanity_checks_params: sanity_checks_params ","
#line 1213 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2243 "dhcp6_parser.cc"
    break;

  case 300: // $@49: %empty
#line 1222 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2252 "dhcp6_parser.cc"
    break;

  case 301: // lease_checks: "lease-checks" $@49 ":" "constant string"
#line 1225 "dhcp6_parser.yy"
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
#line 2272 "dhcp6_parser.cc"
    break;

  case 302: // $@50: %empty
#line 1241 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2281 "dhcp6_parser.cc"
    break;

  case 303: // extended_info_checks: "extended-info-checks" $@50 ":" "constant string"
#line 1244 "dhcp6_parser.yy"
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
#line 2300 "dhcp6_parser.cc"
    break;

  case 304: // $@51: %empty
#line 1259 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2312 "dhcp6_parser.cc"
    break;

  case 305: // mac_sources: "mac-sources" $@51 ":" "[" mac_sources_list "]"
#line 1265 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2321 "dhcp6_parser.cc"
    break;

  case 308: // mac_sources_list: mac_sources_list ","
#line 1272 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2329 "dhcp6_parser.cc"
    break;

  case 311: // duid_id: "duid"
#line 1281 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2338 "dhcp6_parser.cc"
    break;

  case 312: // string_id: "constant string"
#line 1286 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2347 "dhcp6_parser.cc"
    break;

  case 313: // $@52: %empty
#line 1291 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2359 "dhcp6_parser.cc"
    break;

  case 314: // host_reservation_identifiers: "host-reservation-identifiers" $@52 ":" "[" host_reservation_identifiers_list "]"
#line 1297 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2368 "dhcp6_parser.cc"
    break;

  case 317: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1304 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2376 "dhcp6_parser.cc"
    break;

  case 321: // hw_address_id: "hw-address"
#line 1314 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2385 "dhcp6_parser.cc"
    break;

  case 322: // flex_id: "flex-id"
#line 1319 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2394 "dhcp6_parser.cc"
    break;

  case 323: // $@53: %empty
#line 1326 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2406 "dhcp6_parser.cc"
    break;

  case 324: // relay_supplied_options: "relay-supplied-options" $@53 ":" "[" list_content "]"
#line 1332 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2415 "dhcp6_parser.cc"
    break;

  case 325: // $@54: %empty
#line 1339 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2427 "dhcp6_parser.cc"
    break;

  case 326: // dhcp_multi_threading: "multi-threading" $@54 ":" "{" multi_threading_params "}"
#line 1345 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2438 "dhcp6_parser.cc"
    break;

  case 329: // multi_threading_params: multi_threading_params ","
#line 1354 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2446 "dhcp6_parser.cc"
    break;

  case 336: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1367 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2456 "dhcp6_parser.cc"
    break;

  case 337: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1373 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2466 "dhcp6_parser.cc"
    break;

  case 338: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1379 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2476 "dhcp6_parser.cc"
    break;

  case 339: // $@55: %empty
#line 1385 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2488 "dhcp6_parser.cc"
    break;

  case 340: // hooks_libraries: "hooks-libraries" $@55 ":" "[" hooks_libraries_list "]"
#line 1391 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2497 "dhcp6_parser.cc"
    break;

  case 345: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1402 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2505 "dhcp6_parser.cc"
    break;

  case 346: // $@56: %empty
#line 1407 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2515 "dhcp6_parser.cc"
    break;

  case 347: // hooks_library: "{" $@56 hooks_params "}"
#line 1411 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2525 "dhcp6_parser.cc"
    break;

  case 348: // $@57: %empty
#line 1417 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2535 "dhcp6_parser.cc"
    break;

  case 349: // sub_hooks_library: "{" $@57 hooks_params "}"
#line 1421 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2545 "dhcp6_parser.cc"
    break;

  case 352: // hooks_params: hooks_params ","
#line 1429 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2553 "dhcp6_parser.cc"
    break;

  case 356: // $@58: %empty
#line 1439 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2562 "dhcp6_parser.cc"
    break;

  case 357: // library: "library" $@58 ":" "constant string"
#line 1442 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2572 "dhcp6_parser.cc"
    break;

  case 358: // $@59: %empty
#line 1448 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2581 "dhcp6_parser.cc"
    break;

  case 359: // parameters: "parameters" $@59 ":" map_value
#line 1451 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2590 "dhcp6_parser.cc"
    break;

  case 360: // $@60: %empty
#line 1457 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2602 "dhcp6_parser.cc"
    break;

  case 361: // expired_leases_processing: "expired-leases-processing" $@60 ":" "{" expired_leases_params "}"
#line 1463 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2612 "dhcp6_parser.cc"
    break;

  case 364: // expired_leases_params: expired_leases_params ","
#line 1471 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2620 "dhcp6_parser.cc"
    break;

  case 371: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1484 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2630 "dhcp6_parser.cc"
    break;

  case 372: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1490 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2640 "dhcp6_parser.cc"
    break;

  case 373: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1496 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2650 "dhcp6_parser.cc"
    break;

  case 374: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1502 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2660 "dhcp6_parser.cc"
    break;

  case 375: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1508 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2670 "dhcp6_parser.cc"
    break;

  case 376: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1514 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2680 "dhcp6_parser.cc"
    break;

  case 377: // $@61: %empty
#line 1523 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2692 "dhcp6_parser.cc"
    break;

  case 378: // subnet6_list: "subnet6" $@61 ":" "[" subnet6_list_content "]"
#line 1529 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2701 "dhcp6_parser.cc"
    break;

  case 383: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1543 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2709 "dhcp6_parser.cc"
    break;

  case 384: // $@62: %empty
#line 1552 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2719 "dhcp6_parser.cc"
    break;

  case 385: // subnet6: "{" $@62 subnet6_params "}"
#line 1556 "dhcp6_parser.yy"
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
#line 2745 "dhcp6_parser.cc"
    break;

  case 386: // $@63: %empty
#line 1578 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2755 "dhcp6_parser.cc"
    break;

  case 387: // sub_subnet6: "{" $@63 subnet6_params "}"
#line 1582 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2765 "dhcp6_parser.cc"
    break;

  case 390: // subnet6_params: subnet6_params ","
#line 1591 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2773 "dhcp6_parser.cc"
    break;

  case 438: // $@64: %empty
#line 1646 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2782 "dhcp6_parser.cc"
    break;

  case 439: // subnet: "subnet" $@64 ":" "constant string"
#line 1649 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2792 "dhcp6_parser.cc"
    break;

  case 440: // $@65: %empty
#line 1655 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2801 "dhcp6_parser.cc"
    break;

  case 441: // interface: "interface" $@65 ":" "constant string"
#line 1658 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2811 "dhcp6_parser.cc"
    break;

  case 442: // $@66: %empty
#line 1664 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2820 "dhcp6_parser.cc"
    break;

  case 443: // interface_id: "interface-id" $@66 ":" "constant string"
#line 1667 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2830 "dhcp6_parser.cc"
    break;

  case 444: // $@67: %empty
#line 1673 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2839 "dhcp6_parser.cc"
    break;

  case 445: // client_class: "client-class" $@67 ":" "constant string"
#line 1676 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2849 "dhcp6_parser.cc"
    break;

  case 446: // $@68: %empty
#line 1682 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2861 "dhcp6_parser.cc"
    break;

  case 447: // require_client_classes: "require-client-classes" $@68 ":" list_strings
#line 1688 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2870 "dhcp6_parser.cc"
    break;

  case 448: // reservations_global: "reservations-global" ":" "boolean"
#line 1693 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2880 "dhcp6_parser.cc"
    break;

  case 449: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1699 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2890 "dhcp6_parser.cc"
    break;

  case 450: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1705 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2900 "dhcp6_parser.cc"
    break;

  case 451: // $@69: %empty
#line 1711 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2909 "dhcp6_parser.cc"
    break;

  case 452: // reservation_mode: "reservation-mode" $@69 ":" hr_mode
#line 1714 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2918 "dhcp6_parser.cc"
    break;

  case 453: // hr_mode: "disabled"
#line 1719 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2924 "dhcp6_parser.cc"
    break;

  case 454: // hr_mode: "out-of-pool"
#line 1720 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2930 "dhcp6_parser.cc"
    break;

  case 455: // hr_mode: "global"
#line 1721 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2936 "dhcp6_parser.cc"
    break;

  case 456: // hr_mode: "all"
#line 1722 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2942 "dhcp6_parser.cc"
    break;

  case 457: // id: "id" ":" "integer"
#line 1725 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2952 "dhcp6_parser.cc"
    break;

  case 458: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1731 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2962 "dhcp6_parser.cc"
    break;

  case 459: // $@70: %empty
#line 1739 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2974 "dhcp6_parser.cc"
    break;

  case 460: // shared_networks: "shared-networks" $@70 ":" "[" shared_networks_content "]"
#line 1745 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2983 "dhcp6_parser.cc"
    break;

  case 465: // shared_networks_list: shared_networks_list ","
#line 1758 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2991 "dhcp6_parser.cc"
    break;

  case 466: // $@71: %empty
#line 1763 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3001 "dhcp6_parser.cc"
    break;

  case 467: // shared_network: "{" $@71 shared_network_params "}"
#line 1767 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3009 "dhcp6_parser.cc"
    break;

  case 470: // shared_network_params: shared_network_params ","
#line 1773 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3017 "dhcp6_parser.cc"
    break;

  case 515: // $@72: %empty
#line 1828 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3029 "dhcp6_parser.cc"
    break;

  case 516: // option_def_list: "option-def" $@72 ":" "[" option_def_list_content "]"
#line 1834 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3038 "dhcp6_parser.cc"
    break;

  case 517: // $@73: %empty
#line 1842 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3047 "dhcp6_parser.cc"
    break;

  case 518: // sub_option_def_list: "{" $@73 option_def_list "}"
#line 1845 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 3055 "dhcp6_parser.cc"
    break;

  case 523: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1857 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3063 "dhcp6_parser.cc"
    break;

  case 524: // $@74: %empty
#line 1864 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3073 "dhcp6_parser.cc"
    break;

  case 525: // option_def_entry: "{" $@74 option_def_params "}"
#line 1868 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3085 "dhcp6_parser.cc"
    break;

  case 526: // $@75: %empty
#line 1879 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3095 "dhcp6_parser.cc"
    break;

  case 527: // sub_option_def: "{" $@75 option_def_params "}"
#line 1883 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3107 "dhcp6_parser.cc"
    break;

  case 532: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1899 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3115 "dhcp6_parser.cc"
    break;

  case 544: // code: "code" ":" "integer"
#line 1918 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3125 "dhcp6_parser.cc"
    break;

  case 546: // $@76: %empty
#line 1926 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3134 "dhcp6_parser.cc"
    break;

  case 547: // option_def_type: "type" $@76 ":" "constant string"
#line 1929 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3144 "dhcp6_parser.cc"
    break;

  case 548: // $@77: %empty
#line 1935 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3153 "dhcp6_parser.cc"
    break;

  case 549: // option_def_record_types: "record-types" $@77 ":" "constant string"
#line 1938 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3163 "dhcp6_parser.cc"
    break;

  case 550: // $@78: %empty
#line 1944 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3172 "dhcp6_parser.cc"
    break;

  case 551: // space: "space" $@78 ":" "constant string"
#line 1947 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3182 "dhcp6_parser.cc"
    break;

  case 553: // $@79: %empty
#line 1955 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3191 "dhcp6_parser.cc"
    break;

  case 554: // option_def_encapsulate: "encapsulate" $@79 ":" "constant string"
#line 1958 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3201 "dhcp6_parser.cc"
    break;

  case 555: // option_def_array: "array" ":" "boolean"
#line 1964 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3211 "dhcp6_parser.cc"
    break;

  case 556: // $@80: %empty
#line 1974 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3223 "dhcp6_parser.cc"
    break;

  case 557: // option_data_list: "option-data" $@80 ":" "[" option_data_list_content "]"
#line 1980 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3232 "dhcp6_parser.cc"
    break;

  case 562: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1995 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3240 "dhcp6_parser.cc"
    break;

  case 563: // $@81: %empty
#line 2002 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3250 "dhcp6_parser.cc"
    break;

  case 564: // option_data_entry: "{" $@81 option_data_params "}"
#line 2006 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3259 "dhcp6_parser.cc"
    break;

  case 565: // $@82: %empty
#line 2014 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3269 "dhcp6_parser.cc"
    break;

  case 566: // sub_option_data: "{" $@82 option_data_params "}"
#line 2018 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3278 "dhcp6_parser.cc"
    break;

  case 571: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2034 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3286 "dhcp6_parser.cc"
    break;

  case 583: // $@83: %empty
#line 2055 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3295 "dhcp6_parser.cc"
    break;

  case 584: // option_data_data: "data" $@83 ":" "constant string"
#line 2058 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3305 "dhcp6_parser.cc"
    break;

  case 587: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2068 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3315 "dhcp6_parser.cc"
    break;

  case 588: // option_data_always_send: "always-send" ":" "boolean"
#line 2074 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3325 "dhcp6_parser.cc"
    break;

  case 589: // option_data_never_send: "never-send" ":" "boolean"
#line 2080 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3335 "dhcp6_parser.cc"
    break;

  case 590: // $@84: %empty
#line 2089 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3347 "dhcp6_parser.cc"
    break;

  case 591: // pools_list: "pools" $@84 ":" "[" pools_list_content "]"
#line 2095 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3356 "dhcp6_parser.cc"
    break;

  case 596: // not_empty_pools_list: not_empty_pools_list ","
#line 2108 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3364 "dhcp6_parser.cc"
    break;

  case 597: // $@85: %empty
#line 2113 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3374 "dhcp6_parser.cc"
    break;

  case 598: // pool_list_entry: "{" $@85 pool_params "}"
#line 2117 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3384 "dhcp6_parser.cc"
    break;

  case 599: // $@86: %empty
#line 2123 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3394 "dhcp6_parser.cc"
    break;

  case 600: // sub_pool6: "{" $@86 pool_params "}"
#line 2127 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3404 "dhcp6_parser.cc"
    break;

  case 603: // pool_params: pool_params ","
#line 2135 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3412 "dhcp6_parser.cc"
    break;

  case 612: // $@87: %empty
#line 2150 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3421 "dhcp6_parser.cc"
    break;

  case 613: // pool_entry: "pool" $@87 ":" "constant string"
#line 2153 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3431 "dhcp6_parser.cc"
    break;

  case 614: // pool_id: "pool-id" ":" "integer"
#line 2159 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3441 "dhcp6_parser.cc"
    break;

  case 615: // $@88: %empty
#line 2165 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3449 "dhcp6_parser.cc"
    break;

  case 616: // user_context: "user-context" $@88 ":" map_value
#line 2167 "dhcp6_parser.yy"
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
#line 3476 "dhcp6_parser.cc"
    break;

  case 617: // $@89: %empty
#line 2190 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3484 "dhcp6_parser.cc"
    break;

  case 618: // comment: "comment" $@89 ":" "constant string"
#line 2192 "dhcp6_parser.yy"
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
#line 3513 "dhcp6_parser.cc"
    break;

  case 619: // $@90: %empty
#line 2220 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3525 "dhcp6_parser.cc"
    break;

  case 620: // pd_pools_list: "pd-pools" $@90 ":" "[" pd_pools_list_content "]"
#line 2226 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3534 "dhcp6_parser.cc"
    break;

  case 625: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2239 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3542 "dhcp6_parser.cc"
    break;

  case 626: // $@91: %empty
#line 2244 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3552 "dhcp6_parser.cc"
    break;

  case 627: // pd_pool_entry: "{" $@91 pd_pool_params "}"
#line 2248 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3564 "dhcp6_parser.cc"
    break;

  case 628: // $@92: %empty
#line 2256 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3574 "dhcp6_parser.cc"
    break;

  case 629: // sub_pd_pool: "{" $@92 pd_pool_params "}"
#line 2260 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3586 "dhcp6_parser.cc"
    break;

  case 632: // pd_pool_params: pd_pool_params ","
#line 2270 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3594 "dhcp6_parser.cc"
    break;

  case 644: // $@93: %empty
#line 2288 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3603 "dhcp6_parser.cc"
    break;

  case 645: // pd_prefix: "prefix" $@93 ":" "constant string"
#line 2291 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3613 "dhcp6_parser.cc"
    break;

  case 646: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2297 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3623 "dhcp6_parser.cc"
    break;

  case 647: // $@94: %empty
#line 2303 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3632 "dhcp6_parser.cc"
    break;

  case 648: // excluded_prefix: "excluded-prefix" $@94 ":" "constant string"
#line 2306 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3642 "dhcp6_parser.cc"
    break;

  case 649: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2312 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3652 "dhcp6_parser.cc"
    break;

  case 650: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2318 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3662 "dhcp6_parser.cc"
    break;

  case 651: // $@95: %empty
#line 2327 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3674 "dhcp6_parser.cc"
    break;

  case 652: // reservations: "reservations" $@95 ":" "[" reservations_list "]"
#line 2333 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3683 "dhcp6_parser.cc"
    break;

  case 657: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2344 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3691 "dhcp6_parser.cc"
    break;

  case 658: // $@96: %empty
#line 2349 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3701 "dhcp6_parser.cc"
    break;

  case 659: // reservation: "{" $@96 reservation_params "}"
#line 2353 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3710 "dhcp6_parser.cc"
    break;

  case 660: // $@97: %empty
#line 2358 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3720 "dhcp6_parser.cc"
    break;

  case 661: // sub_reservation: "{" $@97 reservation_params "}"
#line 2362 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3729 "dhcp6_parser.cc"
    break;

  case 666: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2373 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3737 "dhcp6_parser.cc"
    break;

  case 678: // $@98: %empty
#line 2392 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3749 "dhcp6_parser.cc"
    break;

  case 679: // ip_addresses: "ip-addresses" $@98 ":" list_strings
#line 2398 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3758 "dhcp6_parser.cc"
    break;

  case 680: // $@99: %empty
#line 2403 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3770 "dhcp6_parser.cc"
    break;

  case 681: // prefixes: "prefixes" $@99 ":" list_strings
#line 2409 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3779 "dhcp6_parser.cc"
    break;

  case 682: // $@100: %empty
#line 2414 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3788 "dhcp6_parser.cc"
    break;

  case 683: // duid: "duid" $@100 ":" "constant string"
#line 2417 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3798 "dhcp6_parser.cc"
    break;

  case 684: // $@101: %empty
#line 2423 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3807 "dhcp6_parser.cc"
    break;

  case 685: // hw_address: "hw-address" $@101 ":" "constant string"
#line 2426 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3817 "dhcp6_parser.cc"
    break;

  case 686: // $@102: %empty
#line 2432 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3826 "dhcp6_parser.cc"
    break;

  case 687: // hostname: "hostname" $@102 ":" "constant string"
#line 2435 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3836 "dhcp6_parser.cc"
    break;

  case 688: // $@103: %empty
#line 2441 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3845 "dhcp6_parser.cc"
    break;

  case 689: // flex_id_value: "flex-id" $@103 ":" "constant string"
#line 2444 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3855 "dhcp6_parser.cc"
    break;

  case 690: // $@104: %empty
#line 2450 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3867 "dhcp6_parser.cc"
    break;

  case 691: // reservation_client_classes: "client-classes" $@104 ":" list_strings
#line 2456 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3876 "dhcp6_parser.cc"
    break;

  case 692: // $@105: %empty
#line 2464 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3888 "dhcp6_parser.cc"
    break;

  case 693: // relay: "relay" $@105 ":" "{" relay_map "}"
#line 2470 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3897 "dhcp6_parser.cc"
    break;

  case 696: // $@106: %empty
#line 2479 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3906 "dhcp6_parser.cc"
    break;

  case 697: // ip_address: "ip-address" $@106 ":" "constant string"
#line 2482 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3916 "dhcp6_parser.cc"
    break;

  case 698: // $@107: %empty
#line 2491 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3928 "dhcp6_parser.cc"
    break;

  case 699: // client_classes: "client-classes" $@107 ":" "[" client_classes_list "]"
#line 2497 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3937 "dhcp6_parser.cc"
    break;

  case 702: // client_classes_list: client_classes_list ","
#line 2504 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3945 "dhcp6_parser.cc"
    break;

  case 703: // $@108: %empty
#line 2509 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3955 "dhcp6_parser.cc"
    break;

  case 704: // client_class_entry: "{" $@108 client_class_params "}"
#line 2513 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3965 "dhcp6_parser.cc"
    break;

  case 709: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2525 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3973 "dhcp6_parser.cc"
    break;

  case 725: // $@109: %empty
#line 2548 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3982 "dhcp6_parser.cc"
    break;

  case 726: // client_class_test: "test" $@109 ":" "constant string"
#line 2551 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3992 "dhcp6_parser.cc"
    break;

  case 727: // $@110: %empty
#line 2557 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4001 "dhcp6_parser.cc"
    break;

  case 728: // client_class_template_test: "template-test" $@110 ":" "constant string"
#line 2560 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4011 "dhcp6_parser.cc"
    break;

  case 729: // only_if_required: "only-if-required" ":" "boolean"
#line 2566 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4021 "dhcp6_parser.cc"
    break;

  case 730: // $@111: %empty
#line 2575 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 4033 "dhcp6_parser.cc"
    break;

  case 731: // server_id: "server-id" $@111 ":" "{" server_id_params "}"
#line 2581 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4044 "dhcp6_parser.cc"
    break;

  case 734: // server_id_params: server_id_params ","
#line 2590 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4052 "dhcp6_parser.cc"
    break;

  case 744: // $@112: %empty
#line 2606 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 4061 "dhcp6_parser.cc"
    break;

  case 745: // server_id_type: "type" $@112 ":" duid_type
#line 2609 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4070 "dhcp6_parser.cc"
    break;

  case 746: // duid_type: "LLT"
#line 2614 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4076 "dhcp6_parser.cc"
    break;

  case 747: // duid_type: "EN"
#line 2615 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4082 "dhcp6_parser.cc"
    break;

  case 748: // duid_type: "LL"
#line 2616 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4088 "dhcp6_parser.cc"
    break;

  case 749: // htype: "htype" ":" "integer"
#line 2619 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4098 "dhcp6_parser.cc"
    break;

  case 750: // $@113: %empty
#line 2625 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4107 "dhcp6_parser.cc"
    break;

  case 751: // identifier: "identifier" $@113 ":" "constant string"
#line 2628 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4117 "dhcp6_parser.cc"
    break;

  case 752: // time: "time" ":" "integer"
#line 2634 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4127 "dhcp6_parser.cc"
    break;

  case 753: // enterprise_id: "enterprise-id" ":" "integer"
#line 2640 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4137 "dhcp6_parser.cc"
    break;

  case 754: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2648 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4147 "dhcp6_parser.cc"
    break;

  case 755: // $@114: %empty
#line 2656 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4159 "dhcp6_parser.cc"
    break;

  case 756: // control_socket: "control-socket" $@114 ":" "{" control_socket_params "}"
#line 2662 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4168 "dhcp6_parser.cc"
    break;

  case 759: // control_socket_params: control_socket_params ","
#line 2669 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4176 "dhcp6_parser.cc"
    break;

  case 765: // $@115: %empty
#line 2681 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4185 "dhcp6_parser.cc"
    break;

  case 766: // socket_type: "socket-type" $@115 ":" "constant string"
#line 2684 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 4195 "dhcp6_parser.cc"
    break;

  case 767: // $@116: %empty
#line 2690 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4204 "dhcp6_parser.cc"
    break;

  case 768: // socket_name: "socket-name" $@116 ":" "constant string"
#line 2693 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4214 "dhcp6_parser.cc"
    break;

  case 769: // $@117: %empty
#line 2702 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4226 "dhcp6_parser.cc"
    break;

  case 770: // dhcp_queue_control: "dhcp-queue-control" $@117 ":" "{" queue_control_params "}"
#line 2708 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4237 "dhcp6_parser.cc"
    break;

  case 773: // queue_control_params: queue_control_params ","
#line 2717 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4245 "dhcp6_parser.cc"
    break;

  case 780: // enable_queue: "enable-queue" ":" "boolean"
#line 2730 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4255 "dhcp6_parser.cc"
    break;

  case 781: // $@118: %empty
#line 2736 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4264 "dhcp6_parser.cc"
    break;

  case 782: // queue_type: "queue-type" $@118 ":" "constant string"
#line 2739 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4274 "dhcp6_parser.cc"
    break;

  case 783: // capacity: "capacity" ":" "integer"
#line 2745 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4284 "dhcp6_parser.cc"
    break;

  case 784: // $@119: %empty
#line 2751 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4293 "dhcp6_parser.cc"
    break;

  case 785: // arbitrary_map_entry: "constant string" $@119 ":" value
#line 2754 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4302 "dhcp6_parser.cc"
    break;

  case 786: // $@120: %empty
#line 2761 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4314 "dhcp6_parser.cc"
    break;

  case 787: // dhcp_ddns: "dhcp-ddns" $@120 ":" "{" dhcp_ddns_params "}"
#line 2767 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4325 "dhcp6_parser.cc"
    break;

  case 788: // $@121: %empty
#line 2774 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4335 "dhcp6_parser.cc"
    break;

  case 789: // sub_dhcp_ddns: "{" $@121 dhcp_ddns_params "}"
#line 2778 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4345 "dhcp6_parser.cc"
    break;

  case 792: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2786 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4353 "dhcp6_parser.cc"
    break;

  case 811: // enable_updates: "enable-updates" ":" "boolean"
#line 2811 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4363 "dhcp6_parser.cc"
    break;

  case 812: // $@122: %empty
#line 2818 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4372 "dhcp6_parser.cc"
    break;

  case 813: // dep_qualifying_suffix: "qualifying-suffix" $@122 ":" "constant string"
#line 2821 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4382 "dhcp6_parser.cc"
    break;

  case 814: // $@123: %empty
#line 2827 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4391 "dhcp6_parser.cc"
    break;

  case 815: // server_ip: "server-ip" $@123 ":" "constant string"
#line 2830 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4401 "dhcp6_parser.cc"
    break;

  case 816: // server_port: "server-port" ":" "integer"
#line 2836 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4411 "dhcp6_parser.cc"
    break;

  case 817: // $@124: %empty
#line 2842 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4420 "dhcp6_parser.cc"
    break;

  case 818: // sender_ip: "sender-ip" $@124 ":" "constant string"
#line 2845 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4430 "dhcp6_parser.cc"
    break;

  case 819: // sender_port: "sender-port" ":" "integer"
#line 2851 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4440 "dhcp6_parser.cc"
    break;

  case 820: // max_queue_size: "max-queue-size" ":" "integer"
#line 2857 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4450 "dhcp6_parser.cc"
    break;

  case 821: // $@125: %empty
#line 2863 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4459 "dhcp6_parser.cc"
    break;

  case 822: // ncr_protocol: "ncr-protocol" $@125 ":" ncr_protocol_value
#line 2866 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4468 "dhcp6_parser.cc"
    break;

  case 823: // ncr_protocol_value: "UDP"
#line 2872 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4474 "dhcp6_parser.cc"
    break;

  case 824: // ncr_protocol_value: "TCP"
#line 2873 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4480 "dhcp6_parser.cc"
    break;

  case 825: // $@126: %empty
#line 2876 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4489 "dhcp6_parser.cc"
    break;

  case 826: // ncr_format: "ncr-format" $@126 ":" "JSON"
#line 2879 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4499 "dhcp6_parser.cc"
    break;

  case 827: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2886 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4509 "dhcp6_parser.cc"
    break;

  case 828: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2893 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4519 "dhcp6_parser.cc"
    break;

  case 829: // $@127: %empty
#line 2900 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4528 "dhcp6_parser.cc"
    break;

  case 830: // dep_replace_client_name: "replace-client-name" $@127 ":" ddns_replace_client_name_value
#line 2903 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4537 "dhcp6_parser.cc"
    break;

  case 831: // $@128: %empty
#line 2909 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4546 "dhcp6_parser.cc"
    break;

  case 832: // dep_generated_prefix: "generated-prefix" $@128 ":" "constant string"
#line 2912 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4556 "dhcp6_parser.cc"
    break;

  case 833: // $@129: %empty
#line 2919 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4565 "dhcp6_parser.cc"
    break;

  case 834: // dep_hostname_char_set: "hostname-char-set" $@129 ":" "constant string"
#line 2922 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4575 "dhcp6_parser.cc"
    break;

  case 835: // $@130: %empty
#line 2929 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4584 "dhcp6_parser.cc"
    break;

  case 836: // dep_hostname_char_replacement: "hostname-char-replacement" $@130 ":" "constant string"
#line 2932 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4594 "dhcp6_parser.cc"
    break;

  case 837: // $@131: %empty
#line 2941 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4606 "dhcp6_parser.cc"
    break;

  case 838: // config_control: "config-control" $@131 ":" "{" config_control_params "}"
#line 2947 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4616 "dhcp6_parser.cc"
    break;

  case 839: // $@132: %empty
#line 2953 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4626 "dhcp6_parser.cc"
    break;

  case 840: // sub_config_control: "{" $@132 config_control_params "}"
#line 2957 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4635 "dhcp6_parser.cc"
    break;

  case 843: // config_control_params: config_control_params ","
#line 2965 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4643 "dhcp6_parser.cc"
    break;

  case 846: // $@133: %empty
#line 2975 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4655 "dhcp6_parser.cc"
    break;

  case 847: // config_databases: "config-databases" $@133 ":" "[" database_list "]"
#line 2981 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4664 "dhcp6_parser.cc"
    break;

  case 848: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2986 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4674 "dhcp6_parser.cc"
    break;

  case 849: // $@134: %empty
#line 2994 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4686 "dhcp6_parser.cc"
    break;

  case 850: // loggers: "loggers" $@134 ":" "[" loggers_entries "]"
#line 3000 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4695 "dhcp6_parser.cc"
    break;

  case 853: // loggers_entries: loggers_entries ","
#line 3009 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4703 "dhcp6_parser.cc"
    break;

  case 854: // $@135: %empty
#line 3015 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4713 "dhcp6_parser.cc"
    break;

  case 855: // logger_entry: "{" $@135 logger_params "}"
#line 3019 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4721 "dhcp6_parser.cc"
    break;

  case 858: // logger_params: logger_params ","
#line 3025 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4729 "dhcp6_parser.cc"
    break;

  case 866: // debuglevel: "debuglevel" ":" "integer"
#line 3039 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4739 "dhcp6_parser.cc"
    break;

  case 867: // $@136: %empty
#line 3045 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4748 "dhcp6_parser.cc"
    break;

  case 868: // severity: "severity" $@136 ":" "constant string"
#line 3048 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4758 "dhcp6_parser.cc"
    break;

  case 869: // $@137: %empty
#line 3054 "dhcp6_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4770 "dhcp6_parser.cc"
    break;

  case 870: // output_options_list: "output-options" $@137 ":" "[" output_options_list_content "]"
#line 3060 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4779 "dhcp6_parser.cc"
    break;

  case 873: // output_options_list_content: output_options_list_content ","
#line 3067 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4787 "dhcp6_parser.cc"
    break;

  case 874: // $@138: %empty
#line 3072 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4797 "dhcp6_parser.cc"
    break;

  case 875: // output_entry: "{" $@138 output_params_list "}"
#line 3076 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4805 "dhcp6_parser.cc"
    break;

  case 878: // output_params_list: output_params_list ","
#line 3082 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4813 "dhcp6_parser.cc"
    break;

  case 884: // $@139: %empty
#line 3094 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4822 "dhcp6_parser.cc"
    break;

  case 885: // output: "output" $@139 ":" "constant string"
#line 3097 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4832 "dhcp6_parser.cc"
    break;

  case 886: // flush: "flush" ":" "boolean"
#line 3103 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4842 "dhcp6_parser.cc"
    break;

  case 887: // maxsize: "maxsize" ":" "integer"
#line 3109 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4852 "dhcp6_parser.cc"
    break;

  case 888: // maxver: "maxver" ":" "integer"
#line 3115 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4862 "dhcp6_parser.cc"
    break;

  case 889: // $@140: %empty
#line 3121 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4871 "dhcp6_parser.cc"
    break;

  case 890: // pattern: "pattern" $@140 ":" "constant string"
#line 3124 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4881 "dhcp6_parser.cc"
    break;

  case 891: // $@141: %empty
#line 3130 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4893 "dhcp6_parser.cc"
    break;

  case 892: // compatibility: "compatibility" $@141 ":" "{" compatibility_params "}"
#line 3136 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4902 "dhcp6_parser.cc"
    break;

  case 895: // compatibility_params: compatibility_params ","
#line 3143 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4910 "dhcp6_parser.cc"
    break;

  case 898: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3152 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4920 "dhcp6_parser.cc"
    break;


#line 4924 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1044;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     638, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044,    46,    26,    48,    56,    70,
      77,    94,   108,   114,   159,   175,   179,   190,   204,   248,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,    26,  -181,
      40,   166,    23,   593,   -15,    67,   219,     8,   236,   341,
     -92,   693,   115, -1044,   207,   258,    85,   255,   278, -1044,
      71, -1044, -1044, -1044, -1044, -1044, -1044, -1044,   289,   291,
     292,   298,   299,   307,   310,   311,   334,   348,   364,   388,
     389,   395, -1044,   430,   441,   449,   450,   455, -1044, -1044,
   -1044,   456,   459,   460,   461, -1044, -1044, -1044,   465, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044,   466,   467,   468, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,   469, -1044,
   -1044, -1044, -1044, -1044, -1044,   471,   473,   475, -1044, -1044,
     476, -1044,    88, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044,   477,   478,   479,   480, -1044,    99, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044,   482,   483, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044,   101, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044,   489, -1044, -1044,
   -1044, -1044,   137, -1044, -1044, -1044, -1044, -1044, -1044,   490,
   -1044,   492,   493, -1044, -1044, -1044, -1044, -1044, -1044,   140,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044,   297,   328, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044,   337, -1044, -1044,
     494, -1044, -1044, -1044,   497, -1044, -1044,   362,   339, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044,   499,   500,   503, -1044, -1044, -1044, -1044,   502,
     369, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044,   154, -1044, -1044, -1044,   504, -1044,
   -1044,   508, -1044,   509,   510, -1044, -1044,   511,   514, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044,   160, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044,   516,   176, -1044, -1044, -1044, -1044,
      26,    26, -1044,   302,   518, -1044, -1044,   519,   522,   528,
     532,   533,   534,   313,   317,   318,   321,   323,   326,   330,
     332,   320,   324,   340,   342,   335,   344,   550,   350,   354,
     336,   343,   353,   553,   561,   564,   355,   357,   360,   358,
     568,   586,   587,   367,   590,   594,   596,   597,   598,   599,
     600,   377,   378,   384,   611,   612,   613,   614,   615,   616,
     618,   619,   625,   371,   626,   627,   628,   630,   632,   633,
     410,   411,   413,   652,   653, -1044,   166, -1044,   654,   431,
     442,   445,   447,    23, -1044,   670,   671,   672,   673,   674,
     453,   454,   677,   683,   684,   593, -1044,   685,   464,   -15,
   -1044,   687,   470,   689,   472,   484,    67, -1044,   691,   695,
     704,   705,   707,   711,   712, -1044,   219, -1044,   713,   714,
     495,   715,   716,   725,   505, -1044,   236,   726,   506,   515,
     517, -1044,   341,   728,   732,   -51, -1044,   520,   738,   740,
     521,   745,   524,   526,   749,   750,   527,   541,   766,   767,
     768,   780,   693, -1044,   783,   570,   115, -1044, -1044, -1044,
     786,   795,   578,   797,   798,   799,   800,   803, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044,   584, -1044, -1044, -1044, -1044, -1044,   -94,   585,
     603, -1044, -1044, -1044, -1044,   806,   807,   810, -1044,   604,
     605,   322,   816,   815,   606,   325, -1044, -1044, -1044,   818,
     819,   827,   826,   829,   831,   832,   833,   834, -1044,   835,
     836,   837,   838,   621,   622, -1044, -1044, -1044,   858,   857,
   -1044,   860, -1044, -1044, -1044, -1044, -1044,   861,   862,   656,
     657,   658, -1044, -1044,   860,   659,   878, -1044,   661, -1044,
   -1044,   662, -1044,   665, -1044, -1044, -1044,   860,   860,   860,
     666,   667,   668,   669, -1044,   675,   678, -1044,   679,   680,
     681, -1044, -1044,   682, -1044, -1044, -1044, -1044,   686,   815,
   -1044, -1044,   688,   690, -1044,   692, -1044, -1044,   -38,   648,
   -1044, -1044,   -94,   694,   696,   697, -1044,   890, -1044, -1044,
      26,   166, -1044,   115,    23,   349,   349,   889, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044,   891,   892,   901,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044,   902, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044,   -93,    26,    60,   120,
     903,   905,   907,    42,   243,   142,   -42,   -60,   693, -1044,
   -1044,   909,  -174, -1044, -1044,   913,   916, -1044, -1044, -1044,
   -1044, -1044,   -75, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044,   889, -1044,   177,   206,   268, -1044, -1044, -1044,
   -1044,   893,   920,   921,   922,   923,   924,   925,   926,   928,
     929, -1044,   930, -1044, -1044, -1044, -1044, -1044,   274, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044,   275, -1044,   931,   932, -1044, -1044,   933,   935, -1044,
   -1044,   934,   938, -1044, -1044,   936,   940, -1044, -1044,   939,
     941, -1044, -1044, -1044,   119, -1044, -1044, -1044,   942, -1044,
   -1044, -1044,   141, -1044, -1044, -1044, -1044, -1044,   276, -1044,
   -1044, -1044, -1044,   161, -1044, -1044,   943,   944, -1044, -1044,
     945,   947, -1044,   948,   949,   950,   951,   952,   953,   314,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,   954,
     955,   956, -1044, -1044, -1044, -1044,   327, -1044, -1044, -1044,
   -1044, -1044, -1044,   957,   958,   959, -1044,   329, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,   331,
   -1044, -1044, -1044,   960, -1044,   961, -1044, -1044, -1044,   338,
   -1044, -1044, -1044, -1044, -1044,   345, -1044,   209, -1044,   962,
   -1044,   346, -1044, -1044,   721, -1044,   963,   964, -1044, -1044,
     965,   967, -1044, -1044, -1044,   966, -1044,   969, -1044, -1044,
   -1044,   968,   972,   973,   974,   710,   751,   742,   752,   747,
     755,   756,   757,   758,   759,   983,   762,   986,   987,   989,
     990,   349, -1044, -1044,   349, -1044,   889,   593, -1044,   891,
     236, -1044,   892,   341, -1044,   901,   706, -1044,   902,   -93,
   -1044, -1044,    60, -1044,   992,   995,   120, -1044,   359,   903,
   -1044,   219, -1044,   905,   -92, -1044,   907,   775,   776,   778,
     779,   782,   785,    42, -1044,  1011,  1012,   791,   794,   802,
     243, -1044,   804,   805,   840,   142, -1044,  1022,  1026,   -42,
   -1044,   825,  1040,   842,  1060,   -60, -1044, -1044,    96,   909,
   -1044,   841,  -174, -1044, -1044,  1073,  1079,   -15, -1044,   913,
      67, -1044,   916,  1080, -1044, -1044,   381,   866,   880,   918,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
     408, -1044,   919,   937,   946,   970, -1044,   366, -1044,   368,
   -1044,  1077, -1044,  1078, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044,   397, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044,   971,   975, -1044, -1044, -1044,  1114,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044,  1133,  1148, -1044, -1044, -1044, -1044, -1044, -1044,  1145,
   -1044,   412, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
     301,   976, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
     977,   978, -1044, -1044,   979, -1044,    26, -1044, -1044,  1150,
   -1044, -1044, -1044, -1044, -1044,   425, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044,   980,   427, -1044,   428, -1044,   981,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,   706,
   -1044, -1044, -1044,  1151,  1152,   982, -1044,   359, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,  1153,
     991,  1154,    96, -1044, -1044, -1044, -1044, -1044, -1044,   984,
     993, -1044, -1044,  1155, -1044,   994, -1044, -1044, -1044,  1156,
   -1044, -1044,   259, -1044,     0,  1156, -1044, -1044,  1157,  1160,
    1161, -1044,   429, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
    1162,   996,   997,   999,  1163,     0, -1044,  1001, -1044, -1044,
   -1044,  1002, -1044, -1044, -1044
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   199,     9,   386,    11,
     599,    13,   628,    15,   660,    17,   517,    19,   526,    21,
     565,    23,   348,    25,   788,    27,   839,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   662,     0,   528,   567,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   141,   837,   197,   218,   220,   222,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   187,     0,     0,     0,     0,     0,   160,   167,
     169,     0,     0,     0,     0,   377,   515,   556,     0,   190,
     192,   173,   459,   615,   617,   451,     0,     0,     0,   304,
     323,   313,   293,   698,   651,   339,   360,   730,     0,   325,
     755,   769,   786,   180,   182,     0,     0,     0,   849,   891,
       0,   140,     0,    69,    72,    73,    74,    75,    76,    77,
      78,    79,    80,   111,   112,   113,   114,   115,    81,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   117,
     118,   129,   130,   131,   106,   137,   138,   139,   133,   134,
     135,    84,    85,    86,    87,   103,    88,    90,    89,   132,
      94,    95,    82,   108,   109,   110,   107,    83,    92,    93,
     101,   102,   104,    91,    96,    97,    98,    99,   100,   105,
     116,   136,   212,     0,     0,     0,     0,   211,     0,   201,
     204,   205,   206,   207,   208,   209,   210,   590,   619,   438,
     440,   442,     0,     0,   446,   444,   692,   437,   391,   392,
     393,   394,   395,   396,   397,   398,   417,   418,   419,   420,
     421,   424,   425,   426,   427,   428,   429,   430,   431,   432,
     433,   422,   423,   434,   435,   436,     0,   388,   402,   403,
     404,   407,   408,   411,   412,   413,   410,   405,   406,   399,
     400,   415,   416,   401,   409,   414,   612,     0,   611,   607,
     608,   606,     0,   601,   604,   605,   609,   610,   644,     0,
     647,     0,     0,   643,   637,   638,   636,   641,   642,     0,
     630,   633,   634,   639,   640,   635,   690,   678,   680,   682,
     684,   686,   688,   677,   674,   675,   676,     0,   663,   664,
     669,   670,   667,   671,   672,   673,   668,     0,   546,   268,
       0,   550,   548,   553,     0,   542,   543,     0,   529,   530,
     533,   545,   534,   535,   536,   552,   537,   538,   539,   540,
     541,   583,     0,     0,     0,   581,   582,   585,   586,     0,
     568,   569,   572,   573,   574,   575,   576,   577,   578,   579,
     580,   356,   358,   353,     0,   350,   354,   355,     0,   812,
     814,     0,   817,     0,     0,   821,   825,     0,     0,   829,
     831,   833,   835,   810,   808,   809,     0,   790,   793,   805,
     794,   795,   796,   797,   798,   799,   800,   801,   802,   803,
     804,   806,   807,   846,     0,     0,   841,   844,   845,    47,
      52,     0,    39,    45,     0,    66,    62,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    60,    71,    68,     0,     0,
       0,     0,     0,   203,   200,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   390,   387,     0,     0,   603,
     600,     0,     0,     0,     0,     0,   632,   629,     0,     0,
       0,     0,     0,     0,     0,   661,   666,   518,     0,     0,
       0,     0,     0,     0,     0,   527,   532,     0,     0,     0,
       0,   566,   571,     0,     0,   352,   349,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   792,   789,     0,     0,   843,   840,    51,    43,
       0,     0,     0,     0,     0,     0,     0,     0,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,     0,   185,   186,   157,   158,   159,     0,     0,
       0,   171,   172,   179,   184,     0,     0,     0,   189,     0,
       0,     0,     0,     0,     0,     0,   448,   449,   450,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   754,     0,
       0,     0,     0,     0,     0,   194,   195,   196,     0,     0,
      70,     0,   214,   215,   216,   217,   202,     0,     0,     0,
       0,     0,   457,   458,     0,     0,     0,   389,     0,   614,
     602,     0,   646,     0,   649,   650,   631,     0,     0,     0,
       0,     0,     0,     0,   665,     0,     0,   544,     0,     0,
       0,   555,   531,     0,   587,   588,   589,   570,     0,     0,
     351,   811,     0,     0,   816,     0,   819,   820,     0,     0,
     827,   828,     0,     0,     0,     0,   791,     0,   848,   842,
       0,     0,   142,     0,     0,     0,     0,   224,   188,   162,
     163,   164,   165,   166,   161,   168,   170,   379,   519,   558,
     191,   193,   175,   176,   177,   178,   174,   461,    40,   616,
     618,   453,   454,   455,   456,   452,     0,    48,     0,     0,
       0,   653,   341,     0,     0,     0,     0,     0,     0,   181,
     183,     0,     0,    53,   213,   592,   621,   439,   441,   443,
     447,   445,     0,   613,   645,   648,   691,   679,   681,   683,
     685,   687,   689,   547,   269,   551,   549,   554,   584,   357,
     359,   813,   815,   818,   823,   824,   822,   826,   830,   832,
     834,   836,   224,    44,     0,     0,     0,   256,   261,   263,
     265,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   278,     0,   285,   287,   289,   291,   255,     0,   231,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   248,   249,   250,   247,   251,   252,   253,
     254,     0,   229,     0,   225,   226,   384,     0,   380,   381,
     524,     0,   520,   521,   563,     0,   559,   560,   466,     0,
     462,   463,   311,   312,     0,   306,   309,   310,     0,   321,
     322,   318,     0,   315,   319,   320,   300,   302,     0,   295,
     298,   299,   703,     0,   700,   658,     0,   654,   655,   346,
       0,   342,   343,     0,     0,     0,     0,     0,     0,     0,
     362,   365,   366,   367,   368,   369,   370,   744,   750,     0,
       0,     0,   743,   740,   741,   742,     0,   732,   735,   738,
     736,   737,   739,     0,     0,     0,   335,     0,   327,   330,
     331,   332,   333,   334,   765,   767,   764,   762,   763,     0,
     757,   760,   761,     0,   781,     0,   784,   777,   778,     0,
     771,   774,   775,   776,   779,     0,   854,     0,   851,     0,
     897,     0,   893,   896,    55,   597,     0,   593,   594,   626,
       0,   622,   623,   696,   695,     0,   694,     0,    64,   838,
     198,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   233,   219,   221,     0,   223,   228,     0,   378,   383,
     528,   516,   523,   567,   557,   562,     0,   460,   465,   308,
     305,   324,   317,   314,     0,     0,   297,   294,   705,   702,
     699,   662,   652,   657,     0,   340,   345,     0,     0,     0,
       0,     0,     0,   364,   361,     0,     0,     0,     0,     0,
     734,   731,     0,     0,     0,   329,   326,     0,     0,   759,
     756,     0,     0,     0,     0,   773,   770,   787,     0,   853,
     850,     0,   895,   892,    57,     0,    56,     0,   591,   596,
       0,   620,   625,     0,   693,   847,     0,     0,     0,     0,
     267,   270,   271,   272,   273,   274,   275,   276,   284,   277,
       0,   283,     0,     0,     0,     0,   232,     0,   227,     0,
     382,     0,   522,     0,   561,   514,   485,   486,   487,   489,
     490,   491,   475,   476,   494,   495,   496,   497,   498,   501,
     502,   503,   504,   505,   506,   507,   508,   509,   510,   499,
     500,   511,   512,   513,   471,   472,   473,   474,   483,   484,
     480,   481,   482,   479,   488,     0,   468,   477,   492,   493,
     478,   464,   307,   316,     0,     0,   296,   725,   727,     0,
     723,   717,   718,   719,   720,   721,   722,   724,   714,   715,
     716,     0,   706,   707,   710,   711,   712,   713,   701,     0,
     656,     0,   344,   371,   372,   373,   374,   375,   376,   363,
       0,     0,   749,   752,   753,   733,   336,   337,   338,   328,
       0,     0,   758,   780,     0,   783,     0,   772,   869,     0,
     867,   865,   859,   863,   864,     0,   856,   861,   862,   860,
     852,   898,   894,    54,    59,     0,   595,     0,   624,     0,
     258,   259,   260,   257,   262,   264,   266,   280,   281,   282,
     279,   286,   288,   290,   292,   230,   385,   525,   564,   470,
     467,   301,   303,     0,     0,     0,   704,   709,   659,   347,
     746,   747,   748,   745,   751,   766,   768,   782,   785,     0,
       0,     0,   858,   855,    58,   598,   627,   697,   469,     0,
       0,   729,   708,     0,   866,     0,   857,   726,   728,     0,
     868,   874,     0,   871,     0,   873,   870,   884,     0,     0,
       0,   889,     0,   876,   879,   880,   881,   882,   883,   872,
       0,     0,     0,     0,     0,   878,   875,     0,   886,   887,
     888,     0,   877,   885,   890
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044,    -4, -1044,  -621, -1044,
     439, -1044, -1044, -1044, -1044,   372, -1044,  -627, -1044, -1044,
   -1044,   -71, -1044, -1044, -1044, -1044, -1044, -1044, -1044,   418,
     644, -1044, -1044,   -43,   -39,    10,    14,    15,    17,   -24,
     -21,   -17,   -11,    30,    32,    33, -1044,    37,    43,    44,
      47, -1044,   432,    50, -1044,    51, -1044,    62,    63,    64,
   -1044, -1044,    65,    66, -1044,    68, -1044,    69, -1044, -1044,
   -1044, -1044, -1044,    76, -1044,    79, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044,   419,   639, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,   333, -1044,
     121, -1044,  -745,   125, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044,   -41, -1044,  -788, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
     102, -1044, -1044, -1044, -1044, -1044, -1044, -1044,   110,  -768,
   -1044, -1044, -1044, -1044,   109, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044,    75, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
      97, -1044, -1044, -1044,    98,   601, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044,    91, -1044, -1044, -1044, -1044, -1044, -1044,
   -1043, -1044, -1044, -1044,   126, -1044, -1044, -1044,   130,   643,
   -1044, -1044, -1041, -1044, -1040, -1044,    84, -1044,    86, -1044,
      80,    81,    82,    83, -1044, -1044, -1044, -1039, -1044, -1044,
   -1044, -1044,   122, -1044, -1044,  -120,  1115, -1044, -1044, -1044,
   -1044, -1044,   129, -1044, -1044, -1044,   133, -1044,   623, -1044,
     -66, -1044, -1044, -1044, -1044, -1044,   -65, -1044, -1044, -1044,
   -1044, -1044,   -16, -1044, -1044, -1044,   132, -1044, -1044, -1044,
     131, -1044,   640, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044,    78, -1044, -1044, -1044,    93,
     649, -1044, -1044, -1044,   -57, -1044,    -3, -1044, -1044, -1044,
   -1044, -1044,    89, -1044, -1044, -1044,   100,   676, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044,   -45, -1044, -1044, -1044,   145,
   -1044, -1044, -1044,   127, -1044,   646,   403, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1037, -1044, -1044, -1044, -1044, -1044, -1044, -1044,   150, -1044,
   -1044, -1044,   -86, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044,   134, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044,   124, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044,   128, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044,   437,   634, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044,   486,   631, -1044, -1044, -1044,
   -1044, -1044, -1044,   123, -1044, -1044,   -91, -1044, -1044, -1044,
   -1044, -1044, -1044,  -115, -1044, -1044,  -131, -1044, -1044, -1044,
   -1044, -1044, -1044, -1044, -1044, -1044, -1044,   135, -1044
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     779,    87,    88,    41,    68,    84,    85,   804,  1014,  1125,
    1126,   867,    43,    70,    90,   454,    91,    45,    71,   162,
     163,   164,   457,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   483,   764,   183,   484,   184,   485,   185,   186,   187,
     496,   776,   188,   189,   518,   190,   519,   191,   192,   193,
     194,   477,   195,   196,   494,   197,   495,   198,   199,   200,
     201,   459,    47,    72,   238,   239,   240,   528,   241,   242,
     243,   244,   202,   460,   203,   461,   204,   462,   893,   894,
     895,  1054,   868,   869,   870,  1031,  1293,   871,  1032,   872,
    1033,   873,  1034,   874,   875,   569,   876,   877,   878,   879,
     880,   881,   882,   883,   884,  1045,  1300,   885,   886,   887,
    1047,   888,  1048,   889,  1049,   890,  1050,   205,   507,   928,
     929,   930,  1074,   931,  1075,   206,   504,   914,   915,   916,
     917,   207,   506,   922,   923,   924,   925,   208,   505,   209,
     514,   977,   978,   979,   980,   981,   210,   510,   940,   941,
     942,  1084,    63,    80,   404,   405,   406,   583,   407,   584,
     211,   511,   949,   950,   951,   952,   953,   954,   955,   956,
     212,   490,   897,   898,   899,  1057,    49,    73,   286,   287,
     288,   537,   289,   538,   290,   539,   291,   543,   292,   542,
     213,   214,   215,   216,   500,   785,   297,   298,   217,   497,
     909,   910,   911,  1066,  1205,  1206,   218,   491,    57,    77,
     901,   902,   903,  1060,    59,    78,   367,   368,   369,   370,
     371,   372,   373,   568,   374,   572,   375,   571,   376,   377,
     573,   378,   219,   492,   905,   906,   907,  1063,    61,    79,
     389,   390,   391,   392,   393,   577,   394,   395,   396,   397,
     398,   300,   535,  1016,  1017,  1018,  1127,    51,    74,   312,
     313,   314,   547,   315,   220,   498,   221,   499,   303,   536,
    1020,  1021,  1022,  1130,    53,    75,   329,   330,   331,   551,
     332,   333,   553,   334,   335,   222,   509,   936,   937,   938,
    1081,    55,    76,   347,   348,   349,   350,   559,   351,   560,
     352,   561,   353,   562,   354,   563,   355,   564,   356,   558,
     305,   544,  1025,  1026,  1133,   223,   508,   933,   934,  1078,
    1231,  1232,  1233,  1234,  1235,  1313,  1236,  1314,  1237,   224,
     512,   966,   967,   968,  1095,  1323,   969,   970,  1096,   971,
     972,   225,   226,   515,   989,   990,   991,  1107,   992,  1108,
     227,   516,   999,  1000,  1001,  1002,  1112,  1003,  1004,  1114,
     228,   517,    65,    81,   426,   427,   428,   429,   588,   430,
     589,   431,   432,   591,   433,   434,   435,   594,   836,   436,
     595,   437,   438,   439,   598,   440,   599,   441,   600,   442,
     601,   229,   458,    67,    82,   445,   446,   447,   604,   448,
     230,   523,  1007,  1008,  1118,  1275,  1276,  1277,  1278,  1331,
    1279,  1329,  1352,  1353,  1354,  1362,  1363,  1364,  1370,  1365,
    1366,  1367,  1368,  1374,   231,   524,  1011,  1012,  1013
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     161,   237,   257,   308,   323,   343,   963,   365,   385,   403,
     423,   891,    38,   387,   388,   245,   301,   316,   327,   345,
     921,   379,   399,  1195,   424,  1196,  1197,  1204,   304,  1210,
     258,    31,   778,    32,   259,    33,  1009,   366,   386,   232,
     233,   234,   235,   236,    86,   912,    30,   133,   134,   264,
      89,   160,   265,   401,   402,    42,   266,   299,   311,   326,
     344,   337,   267,    44,   127,   133,   134,   810,  1023,   246,
     302,   317,   328,   346,   455,   380,   400,    46,   425,   456,
     816,   817,   818,   260,    48,   306,   126,   261,   262,   451,
     263,   526,   133,   134,   401,   402,   527,   759,   760,   761,
     762,    50,   533,   268,   545,   269,   270,   534,   778,   546,
     271,   993,   994,   995,   254,    52,   272,   273,   255,   307,
     274,    54,  1069,   275,   276,  1070,   984,   985,   443,   444,
     133,   134,   913,   160,   763,   277,   278,   279,   280,   281,
     549,   282,   283,   556,  1072,   550,   127,  1073,   557,   284,
     834,   835,   285,   293,   294,   295,   296,   585,   309,   324,
     310,   325,   586,   602,  1079,   996,    56,  1080,   603,   318,
     319,   320,   321,   322,   133,   134,   359,    92,    93,   606,
     526,    94,    58,   160,   607,  1028,    60,    95,    96,    97,
     943,   944,   945,   946,   947,   948,   254,    62,   912,   919,
     255,   920,  1357,   133,   134,  1358,  1359,  1360,  1361,   606,
     160,    64,  1119,   449,  1029,  1120,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   926,   927,   160,   133,
     134,    34,    35,    36,    37,    66,   128,   129,   130,   131,
     358,   450,  1355,   452,   132,  1356,  1195,   957,  1196,  1197,
    1204,   533,  1210,   133,   134,   852,  1030,  1051,  1051,  1076,
     135,   453,  1052,  1053,  1077,   136,   137,   138,   139,   140,
     141,   142,   160,   463,   143,   464,   465,  1268,   127,  1269,
    1270,   144,   466,   467,   921,   565,   973,   974,   975,  1157,
     145,   468,   963,   146,   469,   470,   359,  1093,   360,   361,
     147,   160,  1094,   362,   363,   364,   133,   134,   148,   149,
    1100,   566,  1105,   150,  1109,  1101,   151,  1106,   471,  1110,
     152,  1115,   576,   133,   134,   567,  1116,   336,   602,  1122,
     133,   134,   472,  1117,  1123,   337,   338,   339,   340,   341,
     342,   153,   154,   155,   156,   157,   158,   160,   473,  1051,
     575,   545,   582,   847,  1305,   159,  1306,   848,   849,   850,
     851,   852,   853,   854,   855,   856,   857,   858,   859,   860,
     861,   160,   474,   475,   862,   863,   864,   865,   866,   476,
    1309,   958,   959,   960,   961,  1310,  1290,  1291,  1292,    98,
      99,   100,   101,   102,   103,   585,   772,   773,   774,   775,
    1319,   359,   381,   360,   361,   382,   383,   384,  1332,   359,
     549,   556,  1375,  1333,   478,  1335,  1336,  1376,   127,   359,
     781,   782,   783,   784,   160,   479,   608,   609,   133,   134,
    1297,  1298,  1299,   480,   481,   161,  1320,  1321,  1322,   482,
     486,   160,   237,   487,   488,   489,   133,   134,   160,   493,
     501,   502,   503,   513,   257,   520,   245,   521,   308,   522,
     525,   529,   530,   531,   532,   323,   540,   541,   301,  1217,
    1218,  1219,   316,   548,   552,   343,   554,   555,   570,   327,
     304,   574,   258,   578,   579,   365,   259,   580,   587,   345,
     581,   385,   590,   592,   593,   596,   387,   388,   597,   379,
     605,   264,   611,   612,   265,   399,   613,   610,   266,   299,
     246,   423,   614,   311,   267,   366,   615,   616,   617,   618,
     326,   386,   302,   619,   620,   424,   317,   621,   626,   622,
     344,   627,   623,   328,   632,   260,   624,   638,   625,   261,
     262,   630,   263,   346,   635,   639,   160,   628,   640,   629,
     631,   636,   645,   380,   160,   268,   633,   269,   270,   400,
     634,   637,   271,   641,   160,   642,   644,   643,   272,   273,
     646,   647,   274,   648,   649,   275,   276,   668,   650,   425,
     651,   652,   653,   654,   655,   656,   657,   277,   278,   279,
     280,   281,   658,   282,   283,   659,   660,   661,   662,   663,
     664,   284,   665,   666,   285,   293,   294,   295,   296,   667,
     669,   670,   671,   309,   672,   310,   673,   674,   675,   676,
     324,   677,   325,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   678,   679,   681,   682,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     683,   684,   127,   685,   687,   688,   689,   690,   691,   692,
     161,   694,   693,   237,   129,   130,   131,   695,   696,   698,
     699,   701,   247,   703,   248,   707,   702,   245,   704,   708,
     133,   134,   249,   250,   251,   252,   253,   135,   709,   710,
     705,   711,   136,   137,   138,   712,   713,   715,   716,   718,
     719,   717,   254,   962,   976,   986,   255,   423,   144,   720,
     723,  1010,   728,   721,   724,   256,   729,   964,   982,   987,
     997,   424,   732,   725,   733,   726,   843,   734,   731,   735,
     736,   246,   737,   738,   739,   740,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   741,
     742,   743,   744,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   745,   127,   359,   747,   153,   154,
     750,   965,   983,   988,   998,   425,   748,   129,   130,   131,
     133,   134,   751,   752,   753,   754,   755,   756,   757,   758,
     765,   767,   768,   133,   134,   769,   250,   251,   160,   253,
     135,   777,    32,   786,   787,   136,   137,   138,   766,   770,
     771,   780,   788,   789,   790,   254,   791,   792,   837,   255,
     793,   794,   795,   796,   797,   798,   799,   800,   256,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,   801,   802,   803,   805,   806,   408,   409,
     410,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     420,   807,   808,   809,   811,   812,   813,   814,   421,   422,
     815,   819,   820,   821,   822,   842,   892,  1035,   896,   900,
     823,   153,   154,   824,   825,   826,   827,   828,   904,   908,
     932,   829,   935,   831,   939,   832,  1006,   833,   160,   839,
    1015,   840,   841,  1019,  1036,  1037,  1038,  1039,  1040,  1041,
    1042,   160,  1043,  1044,  1046,  1056,  1140,  1055,  1059,  1058,
    1061,  1062,  1064,  1065,  1068,  1067,  1124,  1083,  1071,  1082,
    1086,  1085,  1087,  1088,  1089,  1090,  1091,  1092,  1097,  1098,
    1099,  1102,  1103,  1104,  1111,  1113,  1121,  1129,  1142,  1128,
    1132,  1131,  1136,  1144,  1134,  1135,  1137,  1138,  1139,  1141,
    1143,  1145,  1146,  1147,  1148,  1149,   257,  1150,  1151,   365,
    1152,  1153,   385,  1154,  1155,  1165,  1214,   387,   388,  1215,
     301,  1243,  1244,   379,  1245,  1246,   399,  1220,  1247,  1208,
     343,  1248,   304,   403,   258,  1250,  1251,  1252,   259,   366,
    1253,  1229,   386,  1166,   345,  1194,  1260,  1167,  1254,   962,
    1261,  1257,  1256,   264,   976,  1221,   265,  1227,   986,  1222,
     266,   299,  1172,   964,  1264,  1173,   267,  1271,   982,  1174,
    1207,  1010,   987,  1263,   302,  1175,   308,   380,   997,   323,
     400,  1273,  1228,  1209,  1266,   344,  1258,   260,  1265,  1281,
     316,   261,   262,   327,   263,  1230,  1168,  1272,   346,  1283,
    1169,  1170,  1284,  1171,  1289,  1307,  1308,   268,  1223,   269,
     270,  1294,  1224,  1225,   271,  1226,  1176,   965,  1177,  1178,
     272,   273,   983,  1179,   274,  1295,   988,   275,   276,  1180,
    1181,   311,   998,  1182,   326,  1274,  1183,  1184,  1315,   277,
     278,   279,   280,   281,   317,   282,   283,   328,  1185,  1186,
    1187,  1188,  1189,   284,  1190,  1191,   285,   293,   294,   295,
     296,  1316,  1192,  1296,  1301,  1193,  1200,  1201,  1202,  1203,
    1198,  1317,  1199,  1318,  1330,  1339,  1340,  1343,  1345,   918,
    1349,  1371,  1302,  1351,  1372,  1373,  1377,  1381,   830,   844,
     680,  1303,   686,   846,   838,  1027,  1156,  1158,  1216,  1212,
    1259,  1213,  1241,  1242,  1249,  1160,   730,  1159,   697,  1338,
    1211,  1162,   357,  1161,  1163,  1304,  1311,  1164,   700,   722,
    1312,  1324,  1325,  1326,  1327,  1334,  1337,  1286,  1239,  1347,
    1341,   309,   714,   310,   324,  1024,   325,  1344,  1348,  1350,
    1285,  1288,   727,  1379,  1378,  1380,  1383,  1384,  1240,  1238,
    1287,  1342,   706,  1262,  1255,  1005,   746,   749,  1165,   845,
    1369,  1346,  1280,  1267,  1382,     0,  1220,     0,     0,     0,
       0,     0,  1208,     0,     0,     0,     0,  1282,     0,     0,
    1229,  1271,  1328,     0,     0,     0,  1166,     0,  1194,     0,
    1167,     0,     0,     0,  1221,  1273,  1227,     0,  1222,     0,
       0,     0,     0,     0,     0,  1172,     0,     0,  1173,     0,
       0,  1272,  1174,  1207,     0,     0,     0,     0,  1175,     0,
       0,  1228,     0,     0,     0,     0,  1209,     0,     0,     0,
       0,     0,     0,     0,  1230,     0,     0,     0,     0,  1168,
       0,     0,     0,  1169,  1170,     0,  1171,  1223,     0,  1274,
       0,  1224,  1225,     0,  1226,     0,     0,     0,     0,  1176,
       0,  1177,  1178,     0,     0,     0,  1179,     0,     0,     0,
       0,     0,  1180,  1181,     0,     0,  1182,     0,     0,  1183,
    1184,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1185,  1186,  1187,  1188,  1189,     0,  1190,  1191,     0,
       0,     0,     0,     0,     0,  1192,     0,     0,  1193,  1200,
    1201,  1202,  1203,  1198,     0,  1199
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,   794,    78,    79,    80,
      81,   756,    16,    79,    79,    72,    73,    74,    75,    76,
     788,    78,    79,  1066,    81,  1066,  1066,  1066,    73,  1066,
      73,     5,   653,     7,    73,     9,   210,    78,    79,    16,
      17,    18,    19,    20,   225,   138,     0,   107,   108,    73,
      10,   225,    73,   145,   146,     7,    73,    73,    74,    75,
      76,   136,    73,     7,    79,   107,   108,   694,   143,    72,
      73,    74,    75,    76,     3,    78,    79,     7,    81,     8,
     707,   708,   709,    73,     7,   100,    78,    73,    73,     4,
      73,     3,   107,   108,   145,   146,     8,   191,   192,   193,
     194,     7,     3,    73,     3,    73,    73,     8,   729,     8,
      73,   171,   172,   173,   129,     7,    73,    73,   133,   134,
      73,     7,     3,    73,    73,     6,   168,   169,    13,    14,
     107,   108,   225,   225,   228,    73,    73,    73,    73,    73,
       3,    73,    73,     3,     3,     8,    79,     6,     8,    73,
     188,   189,    73,    73,    73,    73,    73,     3,    74,    75,
      74,    75,     8,     3,     3,   225,     7,     6,     8,   102,
     103,   104,   105,   106,   107,   108,    80,    11,    12,     3,
       3,    15,     7,   225,     8,     8,     7,    21,    22,    23,
     148,   149,   150,   151,   152,   153,   129,     7,   138,   139,
     133,   141,   202,   107,   108,   205,   206,   207,   208,     3,
     225,     7,     3,     6,     8,     6,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,   126,   127,   225,   107,
     108,   225,   226,   227,   228,     7,    90,    91,    92,    93,
      24,     3,     3,     8,    98,     6,  1309,    24,  1309,  1309,
    1309,     3,  1309,   107,   108,    32,     8,     3,     3,     3,
     114,     3,     8,     8,     8,   119,   120,   121,   122,   123,
     124,   125,   225,     4,   128,     4,     4,   201,    79,   203,
     204,   135,     4,     4,  1072,     8,   164,   165,   166,  1054,
     144,     4,  1100,   147,     4,     4,    80,     3,    82,    83,
     154,   225,     8,    87,    88,    89,   107,   108,   162,   163,
       3,     3,     3,   167,     3,     8,   170,     8,     4,     8,
     174,     3,     3,   107,   108,     8,     8,   128,     3,     3,
     107,   108,     4,     8,     8,   136,   137,   138,   139,   140,
     141,   195,   196,   197,   198,   199,   200,   225,     4,     3,
       8,     3,     3,    24,     8,   209,     8,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,   225,     4,     4,    45,    46,    47,    48,    49,     4,
       3,   158,   159,   160,   161,     8,    25,    26,    27,    50,
      51,    52,    53,    54,    55,     3,    94,    95,    96,    97,
       8,    80,    81,    82,    83,    84,    85,    86,     3,    80,
       3,     3,     3,     8,     4,     8,     8,     8,    79,    80,
     115,   116,   117,   118,   225,     4,   450,   451,   107,   108,
      42,    43,    44,     4,     4,   526,   155,   156,   157,     4,
       4,   225,   533,     4,     4,     4,   107,   108,   225,     4,
       4,     4,     4,     4,   545,     4,   533,     4,   549,     4,
       4,     4,     4,     4,     4,   556,     4,     4,   545,   130,
     131,   132,   549,     4,     4,   566,     4,     4,     4,   556,
     545,     4,   545,     4,     4,   576,   545,     4,     4,   566,
       8,   582,     4,     4,     4,     4,   582,   582,     4,   576,
       4,   545,     4,     4,   545,   582,     4,   225,   545,   545,
     533,   602,     4,   549,   545,   576,     4,     4,     4,   226,
     556,   582,   545,   226,   226,   602,   549,   226,   228,   226,
     566,   227,   226,   556,     4,   545,   226,     4,   226,   545,
     545,   226,   545,   566,   228,     4,   225,   227,     4,   227,
     226,   228,     4,   576,   225,   545,   226,   545,   545,   582,
     226,   228,   545,   228,   225,   228,   228,   227,   545,   545,
       4,     4,   545,   226,     4,   545,   545,   226,     4,   602,
       4,     4,     4,     4,     4,   228,   228,   545,   545,   545,
     545,   545,   228,   545,   545,     4,     4,     4,     4,     4,
       4,   545,     4,     4,   545,   545,   545,   545,   545,     4,
       4,     4,     4,   549,     4,   549,     4,     4,   228,   228,
     556,   228,   556,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,     4,     4,     4,   228,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
     228,   226,    79,   226,     4,     4,     4,     4,     4,   226,
     751,     4,   228,   754,    91,    92,    93,     4,     4,     4,
     226,     4,    99,     4,   101,     4,   226,   754,   226,     4,
     107,   108,   109,   110,   111,   112,   113,   114,     4,     4,
     226,     4,   119,   120,   121,     4,     4,     4,     4,     4,
       4,   226,   129,   794,   795,   796,   133,   798,   135,     4,
       4,   802,     4,   228,   228,   142,     4,   794,   795,   796,
     797,   798,     4,   228,     4,   228,   750,   226,   228,     4,
     226,   754,   226,     4,     4,   228,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,   228,
       4,     4,     4,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,     4,    79,    80,     4,   195,   196,
       4,   794,   795,   796,   797,   798,   226,    91,    92,    93,
     107,   108,     7,   225,     7,     7,     7,     7,     5,   225,
     225,     5,     5,   107,   108,     5,   110,   111,   225,   113,
     114,     5,     7,     5,     5,   119,   120,   121,   225,   225,
     225,   225,     5,     7,     5,   129,     5,     5,   190,   133,
       7,     7,     7,     7,     7,     7,   225,   225,   142,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,     5,     7,     5,     5,     5,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   225,   225,   225,   225,     7,   225,   225,   195,   196,
     225,   225,   225,   225,   225,     5,     7,     4,     7,     7,
     225,   195,   196,   225,   225,   225,   225,   225,     7,     7,
       7,   225,     7,   225,     7,   225,     7,   225,   225,   225,
       7,   225,   225,     7,     4,     4,     4,     4,     4,     4,
       4,   225,     4,     4,     4,     3,   226,     6,     3,     6,
       6,     3,     6,     3,     3,     6,   225,     3,     6,     6,
       3,     6,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     3,   226,     6,
       3,     6,     4,   226,     8,     6,     4,     4,     4,   228,
     228,   226,   226,   226,   226,   226,  1057,     4,   226,  1060,
       4,     4,  1063,     4,     4,  1066,     4,  1063,  1063,     4,
    1057,   226,   226,  1060,   226,   226,  1063,  1078,   226,  1066,
    1081,   226,  1057,  1084,  1057,     4,     4,   226,  1057,  1060,
     226,  1078,  1063,  1066,  1081,  1066,     4,  1066,   226,  1100,
       4,   226,   228,  1057,  1105,  1078,  1057,  1078,  1109,  1078,
    1057,  1057,  1066,  1100,     4,  1066,  1057,  1118,  1105,  1066,
    1066,  1122,  1109,   228,  1057,  1066,  1127,  1060,  1115,  1130,
    1063,  1118,  1078,  1066,     4,  1081,   226,  1057,   226,   228,
    1127,  1057,  1057,  1130,  1057,  1078,  1066,  1118,  1081,     6,
    1066,  1066,     3,  1066,     4,     8,     8,  1057,  1078,  1057,
    1057,   225,  1078,  1078,  1057,  1078,  1066,  1100,  1066,  1066,
    1057,  1057,  1105,  1066,  1057,   225,  1109,  1057,  1057,  1066,
    1066,  1127,  1115,  1066,  1130,  1118,  1066,  1066,     4,  1057,
    1057,  1057,  1057,  1057,  1127,  1057,  1057,  1130,  1066,  1066,
    1066,  1066,  1066,  1057,  1066,  1066,  1057,  1057,  1057,  1057,
    1057,     8,  1066,   225,   225,  1066,  1066,  1066,  1066,  1066,
    1066,     3,  1066,     8,     4,     4,     4,     4,     4,   787,
       5,     4,   225,     7,     4,     4,     4,     4,   729,   751,
     526,   225,   533,   754,   742,   842,  1051,  1056,  1076,  1069,
    1105,  1072,  1084,  1086,  1093,  1059,   585,  1057,   545,  1309,
    1068,  1062,    77,  1060,  1063,   225,   225,  1065,   549,   576,
     225,   225,   225,   225,   225,   225,   225,  1129,  1081,   225,
     228,  1127,   566,  1127,  1130,   812,  1130,   226,   225,   225,
    1127,  1132,   582,   226,   228,   226,   225,   225,  1083,  1079,
    1130,  1317,   556,  1109,  1100,   798,   602,   606,  1309,   753,
    1355,  1332,  1119,  1115,  1375,    -1,  1317,    -1,    -1,    -1,
      -1,    -1,  1309,    -1,    -1,    -1,    -1,  1122,    -1,    -1,
    1317,  1332,  1266,    -1,    -1,    -1,  1309,    -1,  1309,    -1,
    1309,    -1,    -1,    -1,  1317,  1332,  1317,    -1,  1317,    -1,
      -1,    -1,    -1,    -1,    -1,  1309,    -1,    -1,  1309,    -1,
      -1,  1332,  1309,  1309,    -1,    -1,    -1,    -1,  1309,    -1,
      -1,  1317,    -1,    -1,    -1,    -1,  1309,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1317,    -1,    -1,    -1,    -1,  1309,
      -1,    -1,    -1,  1309,  1309,    -1,  1309,  1317,    -1,  1332,
      -1,  1317,  1317,    -1,  1317,    -1,    -1,    -1,    -1,  1309,
      -1,  1309,  1309,    -1,    -1,    -1,  1309,    -1,    -1,    -1,
      -1,    -1,  1309,  1309,    -1,    -1,  1309,    -1,    -1,  1309,
    1309,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1309,  1309,  1309,  1309,  1309,    -1,  1309,  1309,    -1,
      -1,    -1,    -1,    -1,    -1,  1309,    -1,    -1,  1309,  1309,
    1309,  1309,  1309,  1309,    -1,  1309
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
       0,     5,     7,     9,   225,   226,   227,   228,   245,   246,
     247,   252,     7,   261,     7,   266,     7,   321,     7,   435,
       7,   516,     7,   533,     7,   550,     7,   467,     7,   473,
       7,   497,     7,   411,     7,   621,     7,   652,   253,   248,
     262,   267,   322,   436,   517,   534,   551,   468,   474,   498,
     412,   622,   653,   245,   254,   255,   225,   250,   251,    10,
     263,   265,    11,    12,    15,    21,    22,    23,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    90,    91,
      92,    93,    98,   107,   108,   114,   119,   120,   121,   122,
     123,   124,   125,   128,   135,   144,   147,   154,   162,   163,
     167,   170,   174,   195,   196,   197,   198,   199,   200,   209,
     225,   260,   268,   269,   270,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   292,   294,   296,   297,   298,   301,   302,
     304,   306,   307,   308,   309,   311,   312,   314,   316,   317,
     318,   319,   331,   333,   335,   376,   384,   390,   396,   398,
     405,   419,   429,   449,   450,   451,   452,   457,   465,   491,
     523,   525,   544,   574,   588,   600,   601,   609,   619,   650,
     659,   683,    16,    17,    18,    19,    20,   260,   323,   324,
     325,   327,   328,   329,   330,   523,   525,    99,   101,   109,
     110,   111,   112,   113,   129,   133,   142,   260,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   286,   287,   288,   289,   292,   294,   296,   297,   298,
     301,   302,   304,   306,   312,   314,   437,   438,   439,   441,
     443,   445,   447,   449,   450,   451,   452,   455,   456,   491,
     510,   523,   525,   527,   544,   569,   100,   134,   260,   445,
     447,   491,   518,   519,   520,   522,   523,   525,   102,   103,
     104,   105,   106,   260,   445,   447,   491,   523,   525,   535,
     536,   537,   539,   540,   542,   543,   128,   136,   137,   138,
     139,   140,   141,   260,   491,   523,   525,   552,   553,   554,
     555,   557,   559,   561,   563,   565,   567,   465,    24,    80,
      82,    83,    87,    88,    89,   260,   353,   475,   476,   477,
     478,   479,   480,   481,   483,   485,   487,   488,   490,   523,
     525,    81,    84,    85,    86,   260,   353,   479,   485,   499,
     500,   501,   502,   503,   505,   506,   507,   508,   509,   523,
     525,   145,   146,   260,   413,   414,   415,   417,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   195,   196,   260,   523,   525,   623,   624,   625,   626,
     628,   630,   631,   633,   634,   635,   638,   640,   641,   642,
     644,   646,   648,    13,    14,   654,   655,   656,   658,     6,
       3,     4,     8,     3,   264,     3,     8,   271,   651,   320,
     332,   334,   336,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   310,     4,     4,
       4,     4,     4,   290,   293,   295,     4,     4,     4,     4,
     430,   466,   492,     4,   313,   315,   299,   458,   524,   526,
     453,     4,     4,     4,   385,   397,   391,   377,   575,   545,
     406,   420,   589,     4,   399,   602,   610,   620,   303,   305,
       4,     4,     4,   660,   684,     4,     3,     8,   326,     4,
       4,     4,     4,     3,     8,   511,   528,   440,   442,   444,
       4,     4,   448,   446,   570,     3,     8,   521,     4,     3,
       8,   538,     4,   541,     4,     4,     3,     8,   568,   556,
     558,   560,   562,   564,   566,     8,     3,     8,   482,   354,
       4,   486,   484,   489,     4,     8,     3,   504,     4,     4,
       4,     8,     3,   416,   418,     3,     8,     4,   627,   629,
       4,   632,     4,     4,   636,   639,     4,     4,   643,   645,
     647,   649,     3,     8,   657,     4,     3,     8,   245,   245,
     225,     4,     4,     4,     4,     4,     4,     4,   226,   226,
     226,   226,   226,   226,   226,   226,   228,   227,   227,   227,
     226,   226,     4,   226,   226,   228,   228,   228,     4,     4,
       4,   228,   228,   227,   228,     4,     4,     4,   226,     4,
       4,     4,     4,     4,     4,     4,   228,   228,   228,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   226,     4,
       4,     4,     4,     4,     4,   228,   228,   228,     4,     4,
     269,     4,   228,   228,   226,   226,   324,     4,     4,     4,
       4,     4,   226,   228,     4,     4,     4,   438,     4,   226,
     519,     4,   226,     4,   226,   226,   536,     4,     4,     4,
       4,     4,     4,     4,   554,     4,     4,   226,     4,     4,
       4,   228,   477,     4,   228,   228,   228,   501,     4,     4,
     414,   228,     4,     4,   226,     4,   226,   226,     4,     4,
     228,   228,     4,     4,     4,     4,   624,     4,   226,   655,
       4,     7,   225,     7,     7,     7,     7,     5,   225,   191,
     192,   193,   194,   228,   291,   225,   225,     5,     5,     5,
     225,   225,    94,    95,    96,    97,   300,     5,   247,   249,
     225,   115,   116,   117,   118,   454,     5,     5,     5,     7,
       5,     5,     5,     7,     7,     7,     7,     7,     7,   225,
     225,     5,     7,     5,   256,     5,     5,   225,   225,   225,
     256,   225,     7,   225,   225,   225,   256,   256,   256,   225,
     225,   225,   225,   225,   225,   225,   225,   225,   225,   225,
     249,   225,   225,   225,   188,   189,   637,   190,   291,   225,
     225,   225,     5,   245,   268,   654,   323,    24,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    45,    46,    47,    48,    49,   260,   341,   342,
     343,   346,   348,   350,   352,   353,   355,   356,   357,   358,
     359,   360,   361,   362,   363,   366,   367,   368,   370,   372,
     374,   341,     7,   337,   338,   339,     7,   431,   432,   433,
       7,   469,   470,   471,     7,   493,   494,   495,     7,   459,
     460,   461,   138,   225,   386,   387,   388,   389,   254,   139,
     141,   388,   392,   393,   394,   395,   126,   127,   378,   379,
     380,   382,     7,   576,   577,     7,   546,   547,   548,     7,
     407,   408,   409,   148,   149,   150,   151,   152,   153,   421,
     422,   423,   424,   425,   426,   427,   428,    24,   158,   159,
     160,   161,   260,   355,   523,   525,   590,   591,   592,   595,
     596,   598,   599,   164,   165,   166,   260,   400,   401,   402,
     403,   404,   523,   525,   168,   169,   260,   523,   525,   603,
     604,   605,   607,   171,   172,   173,   225,   523,   525,   611,
     612,   613,   614,   616,   617,   623,     7,   661,   662,   210,
     260,   685,   686,   687,   257,     7,   512,   513,   514,     7,
     529,   530,   531,   143,   555,   571,   572,   337,     8,     8,
       8,   344,   347,   349,   351,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   364,     4,   369,   371,   373,
     375,     3,     8,     8,   340,     6,     3,   434,     6,     3,
     472,     6,     3,   496,     6,     3,   462,     6,     3,     3,
       6,     6,     3,     6,   381,   383,     3,     8,   578,     3,
       6,   549,     6,     3,   410,     6,     3,     4,     4,     4,
       4,     4,     4,     3,     8,   593,   597,     4,     4,     4,
       3,     8,     4,     4,     4,     3,     8,   606,   608,     3,
       8,     4,   615,     4,   618,     3,     8,     8,   663,     3,
       6,     4,     3,     8,   225,   258,   259,   515,     6,     3,
     532,     6,     3,   573,     8,     6,     4,     4,     4,     4,
     226,   228,   226,   228,   226,   226,   226,   226,   226,   226,
       4,   226,     4,     4,     4,     4,   342,   341,   339,   437,
     433,   475,   471,   499,   495,   260,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   286,
     287,   288,   289,   292,   294,   296,   297,   298,   301,   302,
     304,   306,   312,   314,   353,   429,   441,   443,   445,   447,
     449,   450,   451,   452,   456,   463,   464,   491,   523,   525,
     569,   461,   387,   393,     4,     4,   379,   130,   131,   132,
     260,   272,   273,   274,   275,   276,   277,   353,   491,   523,
     525,   579,   580,   581,   582,   583,   585,   587,   577,   552,
     548,   413,   409,   226,   226,   226,   226,   226,   226,   422,
       4,     4,   226,   226,   226,   591,   228,   226,   226,   401,
       4,     4,   604,   228,     4,   226,     4,   612,   201,   203,
     204,   260,   353,   523,   525,   664,   665,   666,   667,   669,
     662,   228,   686,     6,     3,   518,   514,   535,   531,     4,
      25,    26,    27,   345,   225,   225,   225,    42,    43,    44,
     365,   225,   225,   225,   225,     8,     8,     8,     8,     3,
       8,   225,   225,   584,   586,     4,     8,     3,     8,     8,
     155,   156,   157,   594,   225,   225,   225,   225,   245,   670,
       4,   668,     3,     8,   225,     8,     8,   225,   464,     4,
       4,   228,   581,     4,   226,     4,   665,   225,   225,     5,
     225,     7,   671,   672,   673,     3,     6,   202,   205,   206,
     207,   208,   674,   675,   676,   678,   679,   680,   681,   672,
     677,     4,     4,     4,   682,     3,     8,     4,   228,   226,
     226,     4,   675,   225,   225
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
     342,   342,   342,   342,   342,   342,   344,   343,   345,   345,
     345,   347,   346,   349,   348,   351,   350,   352,   354,   353,
     355,   356,   357,   358,   359,   360,   361,   362,   364,   363,
     365,   365,   365,   366,   367,   369,   368,   371,   370,   373,
     372,   375,   374,   377,   376,   378,   378,   378,   379,   379,
     381,   380,   383,   382,   385,   384,   386,   386,   386,   387,
     387,   388,   389,   391,   390,   392,   392,   392,   393,   393,
     393,   394,   395,   397,   396,   399,   398,   400,   400,   400,
     401,   401,   401,   401,   401,   401,   402,   403,   404,   406,
     405,   407,   407,   408,   408,   408,   410,   409,   412,   411,
     413,   413,   413,   413,   414,   414,   416,   415,   418,   417,
     420,   419,   421,   421,   421,   422,   422,   422,   422,   422,
     422,   423,   424,   425,   426,   427,   428,   430,   429,   431,
     431,   432,   432,   432,   434,   433,   436,   435,   437,   437,
     437,   438,   438,   438,   438,   438,   438,   438,   438,   438,
     438,   438,   438,   438,   438,   438,   438,   438,   438,   438,
     438,   438,   438,   438,   438,   438,   438,   438,   438,   438,
     438,   438,   438,   438,   438,   438,   438,   438,   438,   438,
     438,   438,   438,   438,   438,   438,   438,   438,   440,   439,
     442,   441,   444,   443,   446,   445,   448,   447,   449,   450,
     451,   453,   452,   454,   454,   454,   454,   455,   456,   458,
     457,   459,   459,   460,   460,   460,   462,   461,   463,   463,
     463,   464,   464,   464,   464,   464,   464,   464,   464,   464,
     464,   464,   464,   464,   464,   464,   464,   464,   464,   464,
     464,   464,   464,   464,   464,   464,   464,   464,   464,   464,
     464,   464,   464,   464,   464,   464,   464,   464,   464,   464,
     464,   464,   464,   464,   464,   466,   465,   468,   467,   469,
     469,   470,   470,   470,   472,   471,   474,   473,   475,   475,
     476,   476,   476,   477,   477,   477,   477,   477,   477,   477,
     477,   477,   477,   478,   479,   480,   482,   481,   484,   483,
     486,   485,   487,   489,   488,   490,   492,   491,   493,   493,
     494,   494,   494,   496,   495,   498,   497,   499,   499,   500,
     500,   500,   501,   501,   501,   501,   501,   501,   501,   501,
     501,   501,   502,   504,   503,   505,   506,   507,   508,   509,
     511,   510,   512,   512,   513,   513,   513,   515,   514,   517,
     516,   518,   518,   518,   519,   519,   519,   519,   519,   519,
     519,   519,   521,   520,   522,   524,   523,   526,   525,   528,
     527,   529,   529,   530,   530,   530,   532,   531,   534,   533,
     535,   535,   535,   536,   536,   536,   536,   536,   536,   536,
     536,   536,   536,   536,   538,   537,   539,   541,   540,   542,
     543,   545,   544,   546,   546,   547,   547,   547,   549,   548,
     551,   550,   552,   552,   553,   553,   553,   554,   554,   554,
     554,   554,   554,   554,   554,   554,   554,   554,   556,   555,
     558,   557,   560,   559,   562,   561,   564,   563,   566,   565,
     568,   567,   570,   569,   571,   571,   573,   572,   575,   574,
     576,   576,   576,   578,   577,   579,   579,   580,   580,   580,
     581,   581,   581,   581,   581,   581,   581,   581,   581,   581,
     581,   581,   581,   581,   582,   584,   583,   586,   585,   587,
     589,   588,   590,   590,   590,   591,   591,   591,   591,   591,
     591,   591,   591,   591,   593,   592,   594,   594,   594,   595,
     597,   596,   598,   599,   600,   602,   601,   603,   603,   603,
     604,   604,   604,   604,   604,   606,   605,   608,   607,   610,
     609,   611,   611,   611,   612,   612,   612,   612,   612,   612,
     613,   615,   614,   616,   618,   617,   620,   619,   622,   621,
     623,   623,   623,   624,   624,   624,   624,   624,   624,   624,
     624,   624,   624,   624,   624,   624,   624,   624,   624,   624,
     624,   625,   627,   626,   629,   628,   630,   632,   631,   633,
     634,   636,   635,   637,   637,   639,   638,   640,   641,   643,
     642,   645,   644,   647,   646,   649,   648,   651,   650,   653,
     652,   654,   654,   654,   655,   655,   657,   656,   658,   660,
     659,   661,   661,   661,   663,   662,   664,   664,   664,   665,
     665,   665,   665,   665,   665,   665,   666,   668,   667,   670,
     669,   671,   671,   671,   673,   672,   674,   674,   674,   675,
     675,   675,   675,   675,   677,   676,   678,   679,   680,   682,
     681,   684,   683,   685,   685,   685,   686,   686,   687
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
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     3,     3,     3,     3,     3,     3,     0,     4,
       1,     1,     1,     3,     3,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     1,     3,     2,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     0,     6,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     0,     4,
       1,     3,     2,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     3,     3,
       3,     0,     4,     1,     1,     1,     1,     3,     3,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     6,     0,     4,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     0,     1,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     0,     4,     0,     4,
       0,     4,     1,     0,     4,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     0,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     3,     3,     3,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     0,     4,     0,     4,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     4,     3,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     0,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     1,     1,     0,     4,     0,     6,
       1,     3,     2,     0,     4,     0,     1,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     3,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     3,
       0,     4,     3,     3,     3,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     3,     0,     4,     0,     6,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     0,     4,     1,     1,     0,     4,     3,     3,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     0,
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
  "$@43", "on_fail_mode", "max_row_errors", "max_reconnect_tries",
  "trust_anchor", "$@44", "cert_file", "$@45", "key_file", "$@46",
  "cipher_list", "$@47", "sanity_checks", "$@48", "sanity_checks_params",
  "sanity_checks_param", "lease_checks", "$@49", "extended_info_checks",
  "$@50", "mac_sources", "$@51", "mac_sources_list", "mac_sources_value",
  "duid_id", "string_id", "host_reservation_identifiers", "$@52",
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
    1027,  1028,  1029,  1030,  1031,  1032,  1035,  1035,  1043,  1044,
    1045,  1048,  1048,  1057,  1057,  1066,  1066,  1075,  1081,  1081,
    1090,  1096,  1102,  1108,  1114,  1120,  1126,  1133,  1139,  1139,
    1147,  1148,  1149,  1152,  1158,  1164,  1164,  1173,  1173,  1182,
    1182,  1191,  1191,  1200,  1200,  1211,  1212,  1213,  1218,  1219,
    1222,  1222,  1241,  1241,  1259,  1259,  1270,  1271,  1272,  1277,
    1278,  1281,  1286,  1291,  1291,  1302,  1303,  1304,  1309,  1310,
    1311,  1314,  1319,  1326,  1326,  1339,  1339,  1352,  1353,  1354,
    1359,  1360,  1361,  1362,  1363,  1364,  1367,  1373,  1379,  1385,
    1385,  1396,  1397,  1400,  1401,  1402,  1407,  1407,  1417,  1417,
    1427,  1428,  1429,  1432,  1435,  1436,  1439,  1439,  1448,  1448,
    1457,  1457,  1469,  1470,  1471,  1476,  1477,  1478,  1479,  1480,
    1481,  1484,  1490,  1496,  1502,  1508,  1514,  1523,  1523,  1537,
    1538,  1541,  1542,  1543,  1552,  1552,  1578,  1578,  1589,  1590,
    1591,  1597,  1598,  1599,  1600,  1601,  1602,  1603,  1604,  1605,
    1606,  1607,  1608,  1609,  1610,  1611,  1612,  1613,  1614,  1615,
    1616,  1617,  1618,  1619,  1620,  1621,  1622,  1623,  1624,  1625,
    1626,  1627,  1628,  1629,  1630,  1631,  1632,  1633,  1634,  1635,
    1636,  1637,  1638,  1639,  1640,  1641,  1642,  1643,  1646,  1646,
    1655,  1655,  1664,  1664,  1673,  1673,  1682,  1682,  1693,  1699,
    1705,  1711,  1711,  1719,  1720,  1721,  1722,  1725,  1731,  1739,
    1739,  1751,  1752,  1756,  1757,  1758,  1763,  1763,  1771,  1772,
    1773,  1778,  1779,  1780,  1781,  1782,  1783,  1784,  1785,  1786,
    1787,  1788,  1789,  1790,  1791,  1792,  1793,  1794,  1795,  1796,
    1797,  1798,  1799,  1800,  1801,  1802,  1803,  1804,  1805,  1806,
    1807,  1808,  1809,  1810,  1811,  1812,  1813,  1814,  1815,  1816,
    1817,  1818,  1819,  1820,  1821,  1828,  1828,  1842,  1842,  1851,
    1852,  1855,  1856,  1857,  1864,  1864,  1879,  1879,  1893,  1894,
    1897,  1898,  1899,  1904,  1905,  1906,  1907,  1908,  1909,  1910,
    1911,  1912,  1913,  1916,  1918,  1924,  1926,  1926,  1935,  1935,
    1944,  1944,  1953,  1955,  1955,  1964,  1974,  1974,  1987,  1988,
    1993,  1994,  1995,  2002,  2002,  2014,  2014,  2026,  2027,  2032,
    2033,  2034,  2041,  2042,  2043,  2044,  2045,  2046,  2047,  2048,
    2049,  2050,  2053,  2055,  2055,  2064,  2066,  2068,  2074,  2080,
    2089,  2089,  2102,  2103,  2106,  2107,  2108,  2113,  2113,  2123,
    2123,  2133,  2134,  2135,  2140,  2141,  2142,  2143,  2144,  2145,
    2146,  2147,  2150,  2150,  2159,  2165,  2165,  2190,  2190,  2220,
    2220,  2233,  2234,  2237,  2238,  2239,  2244,  2244,  2256,  2256,
    2268,  2269,  2270,  2275,  2276,  2277,  2278,  2279,  2280,  2281,
    2282,  2283,  2284,  2285,  2288,  2288,  2297,  2303,  2303,  2312,
    2318,  2327,  2327,  2338,  2339,  2342,  2343,  2344,  2349,  2349,
    2358,  2358,  2367,  2368,  2371,  2372,  2373,  2379,  2380,  2381,
    2382,  2383,  2384,  2385,  2386,  2387,  2388,  2389,  2392,  2392,
    2403,  2403,  2414,  2414,  2423,  2423,  2432,  2432,  2441,  2441,
    2450,  2450,  2464,  2464,  2475,  2476,  2479,  2479,  2491,  2491,
    2502,  2503,  2504,  2509,  2509,  2519,  2520,  2523,  2524,  2525,
    2530,  2531,  2532,  2533,  2534,  2535,  2536,  2537,  2538,  2539,
    2540,  2541,  2542,  2543,  2546,  2548,  2548,  2557,  2557,  2566,
    2575,  2575,  2588,  2589,  2590,  2595,  2596,  2597,  2598,  2599,
    2600,  2601,  2602,  2603,  2606,  2606,  2614,  2615,  2616,  2619,
    2625,  2625,  2634,  2640,  2648,  2656,  2656,  2667,  2668,  2669,
    2674,  2675,  2676,  2677,  2678,  2681,  2681,  2690,  2690,  2702,
    2702,  2715,  2716,  2717,  2722,  2723,  2724,  2725,  2726,  2727,
    2730,  2736,  2736,  2745,  2751,  2751,  2761,  2761,  2774,  2774,
    2784,  2785,  2786,  2791,  2792,  2793,  2794,  2795,  2796,  2797,
    2798,  2799,  2800,  2801,  2802,  2803,  2804,  2805,  2806,  2807,
    2808,  2811,  2818,  2818,  2827,  2827,  2836,  2842,  2842,  2851,
    2857,  2863,  2863,  2872,  2873,  2876,  2876,  2886,  2893,  2900,
    2900,  2909,  2909,  2919,  2919,  2929,  2929,  2941,  2941,  2953,
    2953,  2963,  2964,  2965,  2971,  2972,  2975,  2975,  2986,  2994,
    2994,  3007,  3008,  3009,  3015,  3015,  3023,  3024,  3025,  3030,
    3031,  3032,  3033,  3034,  3035,  3036,  3039,  3045,  3045,  3054,
    3054,  3065,  3066,  3067,  3072,  3072,  3080,  3081,  3082,  3087,
    3088,  3089,  3090,  3091,  3094,  3094,  3103,  3109,  3115,  3121,
    3121,  3130,  3130,  3141,  3142,  3143,  3148,  3149,  3152
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
#line 6620 "dhcp6_parser.cc"

#line 3158 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
