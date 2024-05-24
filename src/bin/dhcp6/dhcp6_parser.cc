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
#line 303 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 409 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 303 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 415 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 303 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 421 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 303 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 427 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 303 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 433 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 303 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 439 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 303 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 445 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 303 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 451 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 303 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 457 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 303 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 463 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 303 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 469 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 303 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 475 "dhcp6_parser.cc"
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
#line 312 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 755 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 313 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 761 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 314 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 767 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 315 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 773 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 316 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 779 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 317 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 785 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 318 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 791 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 319 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 797 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 320 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 803 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 321 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 809 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 322 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 815 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 323 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 821 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 324 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 827 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 325 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 833 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 333 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 839 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 334 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 845 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 335 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 851 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 336 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 857 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 337 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 863 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 338 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 869 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 339 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 875 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 342 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 884 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 347 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 895 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 352 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 905 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 358 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 911 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 365 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 921 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 370 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 932 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 376 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 940 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 381 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 949 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 384 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 957 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 392 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 966 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 396 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 975 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 400 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 983 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 406 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 991 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 408 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1000 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 417 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1009 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 421 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1018 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 425 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1026 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 435 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1037 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 444 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1048 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 449 "dhcp6_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1061 "dhcp6_parser.cc"
    break;

  case 63: // $@19: %empty
#line 459 "dhcp6_parser.yy"
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
#line 1076 "dhcp6_parser.cc"
    break;

  case 64: // global_object: "Dhcp6" $@19 ":" "{" global_params "}"
#line 468 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1086 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 476 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1094 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 482 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1104 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 486 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1113 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 493 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1121 "dhcp6_parser.cc"
    break;

  case 140: // $@21: %empty
#line 570 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1130 "dhcp6_parser.cc"
    break;

  case 141: // data_directory: "data-directory" $@21 ":" "constant string"
#line 573 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1140 "dhcp6_parser.cc"
    break;

  case 142: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 579 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1150 "dhcp6_parser.cc"
    break;

  case 143: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 585 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1160 "dhcp6_parser.cc"
    break;

  case 144: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 591 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1170 "dhcp6_parser.cc"
    break;

  case 145: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 597 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1180 "dhcp6_parser.cc"
    break;

  case 146: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 603 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1190 "dhcp6_parser.cc"
    break;

  case 147: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 609 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1200 "dhcp6_parser.cc"
    break;

  case 148: // renew_timer: "renew-timer" ":" "integer"
#line 615 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1210 "dhcp6_parser.cc"
    break;

  case 149: // rebind_timer: "rebind-timer" ":" "integer"
#line 621 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1220 "dhcp6_parser.cc"
    break;

  case 150: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 627 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1230 "dhcp6_parser.cc"
    break;

  case 151: // t1_percent: "t1-percent" ":" "floating point"
#line 633 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1240 "dhcp6_parser.cc"
    break;

  case 152: // t2_percent: "t2-percent" ":" "floating point"
#line 639 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1250 "dhcp6_parser.cc"
    break;

  case 153: // cache_threshold: "cache-threshold" ":" "floating point"
#line 645 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1260 "dhcp6_parser.cc"
    break;

  case 154: // cache_max_age: "cache-max-age" ":" "integer"
#line 651 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1270 "dhcp6_parser.cc"
    break;

  case 155: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 657 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1280 "dhcp6_parser.cc"
    break;

  case 156: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 663 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1290 "dhcp6_parser.cc"
    break;

  case 157: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 669 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1300 "dhcp6_parser.cc"
    break;

  case 158: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 675 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1310 "dhcp6_parser.cc"
    break;

  case 159: // $@22: %empty
#line 681 "dhcp6_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1319 "dhcp6_parser.cc"
    break;

  case 160: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 684 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1328 "dhcp6_parser.cc"
    break;

  case 161: // ddns_replace_client_name_value: "when-present"
#line 690 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1336 "dhcp6_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "never"
#line 693 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1344 "dhcp6_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "always"
#line 696 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1352 "dhcp6_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "when-not-present"
#line 699 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1360 "dhcp6_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "boolean"
#line 702 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1369 "dhcp6_parser.cc"
    break;

  case 166: // $@23: %empty
#line 708 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1378 "dhcp6_parser.cc"
    break;

  case 167: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 711 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1388 "dhcp6_parser.cc"
    break;

  case 168: // $@24: %empty
#line 717 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1397 "dhcp6_parser.cc"
    break;

  case 169: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 720 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1407 "dhcp6_parser.cc"
    break;

  case 170: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 726 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1417 "dhcp6_parser.cc"
    break;

  case 171: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 735 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.warning(yystack_[1].location, "ddns-use-conflict-resolution is deprecated. "
             "Substituting ddns-conflict-resolution-mode");
    ElementPtr mode(new StringElement(b->boolValue() ? "check-with-dhcid"
                                      : "no-check-with-dhcid"));
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", mode);
}
#line 1431 "dhcp6_parser.cc"
    break;

  case 172: // $@25: %empty
#line 745 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1440 "dhcp6_parser.cc"
    break;

  case 173: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 748 "dhcp6_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1449 "dhcp6_parser.cc"
    break;

  case 174: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 754 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1457 "dhcp6_parser.cc"
    break;

  case 175: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 757 "dhcp6_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1465 "dhcp6_parser.cc"
    break;

  case 176: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 760 "dhcp6_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1473 "dhcp6_parser.cc"
    break;

  case 177: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 763 "dhcp6_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1481 "dhcp6_parser.cc"
    break;

  case 178: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 768 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1491 "dhcp6_parser.cc"
    break;

  case 179: // $@26: %empty
#line 774 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1500 "dhcp6_parser.cc"
    break;

  case 180: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 777 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1510 "dhcp6_parser.cc"
    break;

  case 181: // $@27: %empty
#line 783 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1519 "dhcp6_parser.cc"
    break;

  case 182: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 786 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1529 "dhcp6_parser.cc"
    break;

  case 183: // store_extended_info: "store-extended-info" ":" "boolean"
#line 792 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1539 "dhcp6_parser.cc"
    break;

  case 184: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 798 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1549 "dhcp6_parser.cc"
    break;

  case 185: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 804 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1559 "dhcp6_parser.cc"
    break;

  case 186: // $@28: %empty
#line 810 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1568 "dhcp6_parser.cc"
    break;

  case 187: // server_tag: "server-tag" $@28 ":" "constant string"
#line 813 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1578 "dhcp6_parser.cc"
    break;

  case 188: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 819 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1588 "dhcp6_parser.cc"
    break;

  case 189: // $@29: %empty
#line 825 "dhcp6_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1597 "dhcp6_parser.cc"
    break;

  case 190: // allocator: "allocator" $@29 ":" "constant string"
#line 828 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1607 "dhcp6_parser.cc"
    break;

  case 191: // $@30: %empty
#line 834 "dhcp6_parser.yy"
                           {
    ctx.unique("pd-allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1616 "dhcp6_parser.cc"
    break;

  case 192: // pd_allocator: "pd-allocator" $@30 ":" "constant string"
#line 837 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-allocator", al);
    ctx.leave();
}
#line 1626 "dhcp6_parser.cc"
    break;

  case 193: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 843 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1636 "dhcp6_parser.cc"
    break;

  case 194: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 849 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1646 "dhcp6_parser.cc"
    break;

  case 195: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 855 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1656 "dhcp6_parser.cc"
    break;

  case 196: // $@31: %empty
#line 861 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1668 "dhcp6_parser.cc"
    break;

  case 197: // interfaces_config: "interfaces-config" $@31 ":" "{" interfaces_config_params "}"
#line 867 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1678 "dhcp6_parser.cc"
    break;

  case 198: // $@32: %empty
#line 873 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1688 "dhcp6_parser.cc"
    break;

  case 199: // sub_interfaces6: "{" $@32 interfaces_config_params "}"
#line 877 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1697 "dhcp6_parser.cc"
    break;

  case 202: // interfaces_config_params: interfaces_config_params ","
#line 884 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1705 "dhcp6_parser.cc"
    break;

  case 211: // $@33: %empty
#line 899 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1717 "dhcp6_parser.cc"
    break;

  case 212: // interfaces_list: "interfaces" $@33 ":" list_strings
#line 905 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1726 "dhcp6_parser.cc"
    break;

  case 213: // re_detect: "re-detect" ":" "boolean"
#line 910 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1736 "dhcp6_parser.cc"
    break;

  case 214: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 916 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1746 "dhcp6_parser.cc"
    break;

  case 215: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 922 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1756 "dhcp6_parser.cc"
    break;

  case 216: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 928 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1766 "dhcp6_parser.cc"
    break;

  case 217: // $@34: %empty
#line 934 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1778 "dhcp6_parser.cc"
    break;

  case 218: // lease_database: "lease-database" $@34 ":" "{" database_map_params "}"
#line 940 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1789 "dhcp6_parser.cc"
    break;

  case 219: // $@35: %empty
#line 947 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1801 "dhcp6_parser.cc"
    break;

  case 220: // hosts_database: "hosts-database" $@35 ":" "{" database_map_params "}"
#line 953 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1812 "dhcp6_parser.cc"
    break;

  case 221: // $@36: %empty
#line 960 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1824 "dhcp6_parser.cc"
    break;

  case 222: // hosts_databases: "hosts-databases" $@36 ":" "[" database_list "]"
#line 966 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1833 "dhcp6_parser.cc"
    break;

  case 227: // not_empty_database_list: not_empty_database_list ","
#line 977 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1841 "dhcp6_parser.cc"
    break;

  case 228: // $@37: %empty
#line 982 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1851 "dhcp6_parser.cc"
    break;

  case 229: // database: "{" $@37 database_map_params "}"
#line 986 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1861 "dhcp6_parser.cc"
    break;

  case 232: // database_map_params: database_map_params ","
#line 994 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1869 "dhcp6_parser.cc"
    break;

  case 256: // $@38: %empty
#line 1024 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1878 "dhcp6_parser.cc"
    break;

  case 257: // database_type: "type" $@38 ":" db_type
#line 1027 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1887 "dhcp6_parser.cc"
    break;

  case 258: // db_type: "memfile"
#line 1032 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1893 "dhcp6_parser.cc"
    break;

  case 259: // db_type: "mysql"
#line 1033 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1899 "dhcp6_parser.cc"
    break;

  case 260: // db_type: "postgresql"
#line 1034 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1905 "dhcp6_parser.cc"
    break;

  case 261: // $@39: %empty
#line 1037 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1914 "dhcp6_parser.cc"
    break;

  case 262: // user: "user" $@39 ":" "constant string"
#line 1040 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1924 "dhcp6_parser.cc"
    break;

  case 263: // $@40: %empty
#line 1046 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1933 "dhcp6_parser.cc"
    break;

  case 264: // password: "password" $@40 ":" "constant string"
#line 1049 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1943 "dhcp6_parser.cc"
    break;

  case 265: // $@41: %empty
#line 1055 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1952 "dhcp6_parser.cc"
    break;

  case 266: // host: "host" $@41 ":" "constant string"
#line 1058 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1962 "dhcp6_parser.cc"
    break;

  case 267: // port: "port" ":" "integer"
#line 1064 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1972 "dhcp6_parser.cc"
    break;

  case 268: // $@42: %empty
#line 1070 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1981 "dhcp6_parser.cc"
    break;

  case 269: // name: "name" $@42 ":" "constant string"
#line 1073 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1991 "dhcp6_parser.cc"
    break;

  case 270: // persist: "persist" ":" "boolean"
#line 1079 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2001 "dhcp6_parser.cc"
    break;

  case 271: // lfc_interval: "lfc-interval" ":" "integer"
#line 1085 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2011 "dhcp6_parser.cc"
    break;

  case 272: // readonly: "readonly" ":" "boolean"
#line 1091 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2021 "dhcp6_parser.cc"
    break;

  case 273: // connect_timeout: "connect-timeout" ":" "integer"
#line 1097 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2031 "dhcp6_parser.cc"
    break;

  case 274: // read_timeout: "read-timeout" ":" "integer"
#line 1103 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2041 "dhcp6_parser.cc"
    break;

  case 275: // write_timeout: "write-timeout" ":" "integer"
#line 1109 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2051 "dhcp6_parser.cc"
    break;

  case 276: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1115 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2061 "dhcp6_parser.cc"
    break;

  case 277: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1122 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2071 "dhcp6_parser.cc"
    break;

  case 278: // $@43: %empty
#line 1128 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2080 "dhcp6_parser.cc"
    break;

  case 279: // on_fail: "on-fail" $@43 ":" on_fail_mode
#line 1131 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2089 "dhcp6_parser.cc"
    break;

  case 280: // on_fail_mode: "stop-retry-exit"
#line 1136 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2095 "dhcp6_parser.cc"
    break;

  case 281: // on_fail_mode: "serve-retry-exit"
#line 1137 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2101 "dhcp6_parser.cc"
    break;

  case 282: // on_fail_mode: "serve-retry-continue"
#line 1138 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2107 "dhcp6_parser.cc"
    break;

  case 283: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1141 "dhcp6_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2117 "dhcp6_parser.cc"
    break;

  case 284: // max_row_errors: "max-row-errors" ":" "integer"
#line 1147 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2127 "dhcp6_parser.cc"
    break;

  case 285: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1153 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2137 "dhcp6_parser.cc"
    break;

  case 286: // $@44: %empty
#line 1159 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2146 "dhcp6_parser.cc"
    break;

  case 287: // trust_anchor: "trust-anchor" $@44 ":" "constant string"
#line 1162 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2156 "dhcp6_parser.cc"
    break;

  case 288: // $@45: %empty
#line 1168 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2165 "dhcp6_parser.cc"
    break;

  case 289: // cert_file: "cert-file" $@45 ":" "constant string"
#line 1171 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2175 "dhcp6_parser.cc"
    break;

  case 290: // $@46: %empty
#line 1177 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2184 "dhcp6_parser.cc"
    break;

  case 291: // key_file: "key-file" $@46 ":" "constant string"
#line 1180 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2194 "dhcp6_parser.cc"
    break;

  case 292: // $@47: %empty
#line 1186 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2203 "dhcp6_parser.cc"
    break;

  case 293: // cipher_list: "cipher-list" $@47 ":" "constant string"
#line 1189 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2213 "dhcp6_parser.cc"
    break;

  case 294: // $@48: %empty
#line 1195 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2225 "dhcp6_parser.cc"
    break;

  case 295: // sanity_checks: "sanity-checks" $@48 ":" "{" sanity_checks_params "}"
#line 1201 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2234 "dhcp6_parser.cc"
    break;

  case 298: // sanity_checks_params: sanity_checks_params ","
#line 1208 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2242 "dhcp6_parser.cc"
    break;

  case 301: // $@49: %empty
#line 1217 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2251 "dhcp6_parser.cc"
    break;

  case 302: // lease_checks: "lease-checks" $@49 ":" "constant string"
#line 1220 "dhcp6_parser.yy"
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
#line 2271 "dhcp6_parser.cc"
    break;

  case 303: // $@50: %empty
#line 1236 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2280 "dhcp6_parser.cc"
    break;

  case 304: // extended_info_checks: "extended-info-checks" $@50 ":" "constant string"
#line 1239 "dhcp6_parser.yy"
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
#line 2299 "dhcp6_parser.cc"
    break;

  case 305: // $@51: %empty
#line 1254 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2311 "dhcp6_parser.cc"
    break;

  case 306: // mac_sources: "mac-sources" $@51 ":" "[" mac_sources_list "]"
#line 1260 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2320 "dhcp6_parser.cc"
    break;

  case 309: // mac_sources_list: mac_sources_list ","
#line 1267 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2328 "dhcp6_parser.cc"
    break;

  case 312: // duid_id: "duid"
#line 1276 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2337 "dhcp6_parser.cc"
    break;

  case 313: // string_id: "constant string"
#line 1281 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2346 "dhcp6_parser.cc"
    break;

  case 314: // $@52: %empty
#line 1286 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2358 "dhcp6_parser.cc"
    break;

  case 315: // host_reservation_identifiers: "host-reservation-identifiers" $@52 ":" "[" host_reservation_identifiers_list "]"
#line 1292 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2367 "dhcp6_parser.cc"
    break;

  case 318: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1299 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2375 "dhcp6_parser.cc"
    break;

  case 322: // hw_address_id: "hw-address"
#line 1309 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2384 "dhcp6_parser.cc"
    break;

  case 323: // flex_id: "flex-id"
#line 1314 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2393 "dhcp6_parser.cc"
    break;

  case 324: // $@53: %empty
#line 1321 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2405 "dhcp6_parser.cc"
    break;

  case 325: // relay_supplied_options: "relay-supplied-options" $@53 ":" "[" list_content "]"
#line 1327 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2414 "dhcp6_parser.cc"
    break;

  case 326: // $@54: %empty
#line 1334 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2426 "dhcp6_parser.cc"
    break;

  case 327: // dhcp_multi_threading: "multi-threading" $@54 ":" "{" multi_threading_params "}"
#line 1340 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2437 "dhcp6_parser.cc"
    break;

  case 330: // multi_threading_params: multi_threading_params ","
#line 1349 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2445 "dhcp6_parser.cc"
    break;

  case 337: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1362 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2455 "dhcp6_parser.cc"
    break;

  case 338: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1368 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2465 "dhcp6_parser.cc"
    break;

  case 339: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1374 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2475 "dhcp6_parser.cc"
    break;

  case 340: // $@55: %empty
#line 1380 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2487 "dhcp6_parser.cc"
    break;

  case 341: // hooks_libraries: "hooks-libraries" $@55 ":" "[" hooks_libraries_list "]"
#line 1386 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2496 "dhcp6_parser.cc"
    break;

  case 346: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1397 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2504 "dhcp6_parser.cc"
    break;

  case 347: // $@56: %empty
#line 1402 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2514 "dhcp6_parser.cc"
    break;

  case 348: // hooks_library: "{" $@56 hooks_params "}"
#line 1406 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2524 "dhcp6_parser.cc"
    break;

  case 349: // $@57: %empty
#line 1412 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2534 "dhcp6_parser.cc"
    break;

  case 350: // sub_hooks_library: "{" $@57 hooks_params "}"
#line 1416 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2544 "dhcp6_parser.cc"
    break;

  case 353: // hooks_params: hooks_params ","
#line 1424 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2552 "dhcp6_parser.cc"
    break;

  case 357: // $@58: %empty
#line 1434 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2561 "dhcp6_parser.cc"
    break;

  case 358: // library: "library" $@58 ":" "constant string"
#line 1437 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2571 "dhcp6_parser.cc"
    break;

  case 359: // $@59: %empty
#line 1443 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2580 "dhcp6_parser.cc"
    break;

  case 360: // parameters: "parameters" $@59 ":" map_value
#line 1446 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2589 "dhcp6_parser.cc"
    break;

  case 361: // $@60: %empty
#line 1452 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2601 "dhcp6_parser.cc"
    break;

  case 362: // expired_leases_processing: "expired-leases-processing" $@60 ":" "{" expired_leases_params "}"
#line 1458 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2611 "dhcp6_parser.cc"
    break;

  case 365: // expired_leases_params: expired_leases_params ","
#line 1466 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2619 "dhcp6_parser.cc"
    break;

  case 372: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1479 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2629 "dhcp6_parser.cc"
    break;

  case 373: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1485 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2639 "dhcp6_parser.cc"
    break;

  case 374: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1491 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2649 "dhcp6_parser.cc"
    break;

  case 375: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1497 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2659 "dhcp6_parser.cc"
    break;

  case 376: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1503 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2669 "dhcp6_parser.cc"
    break;

  case 377: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1509 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2679 "dhcp6_parser.cc"
    break;

  case 378: // $@61: %empty
#line 1518 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2691 "dhcp6_parser.cc"
    break;

  case 379: // subnet6_list: "subnet6" $@61 ":" "[" subnet6_list_content "]"
#line 1524 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2700 "dhcp6_parser.cc"
    break;

  case 384: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1538 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2708 "dhcp6_parser.cc"
    break;

  case 385: // $@62: %empty
#line 1547 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2718 "dhcp6_parser.cc"
    break;

  case 386: // subnet6: "{" $@62 subnet6_params "}"
#line 1551 "dhcp6_parser.yy"
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
#line 2744 "dhcp6_parser.cc"
    break;

  case 387: // $@63: %empty
#line 1573 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2754 "dhcp6_parser.cc"
    break;

  case 388: // sub_subnet6: "{" $@63 subnet6_params "}"
#line 1577 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2764 "dhcp6_parser.cc"
    break;

  case 391: // subnet6_params: subnet6_params ","
#line 1586 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2772 "dhcp6_parser.cc"
    break;

  case 438: // $@64: %empty
#line 1640 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2781 "dhcp6_parser.cc"
    break;

  case 439: // subnet: "subnet" $@64 ":" "constant string"
#line 1643 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2791 "dhcp6_parser.cc"
    break;

  case 440: // $@65: %empty
#line 1649 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2800 "dhcp6_parser.cc"
    break;

  case 441: // interface: "interface" $@65 ":" "constant string"
#line 1652 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2810 "dhcp6_parser.cc"
    break;

  case 442: // $@66: %empty
#line 1658 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2819 "dhcp6_parser.cc"
    break;

  case 443: // interface_id: "interface-id" $@66 ":" "constant string"
#line 1661 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2829 "dhcp6_parser.cc"
    break;

  case 444: // $@67: %empty
#line 1667 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2838 "dhcp6_parser.cc"
    break;

  case 445: // client_class: "client-class" $@67 ":" "constant string"
#line 1670 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2848 "dhcp6_parser.cc"
    break;

  case 446: // $@68: %empty
#line 1676 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2860 "dhcp6_parser.cc"
    break;

  case 447: // require_client_classes: "require-client-classes" $@68 ":" list_strings
#line 1682 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2869 "dhcp6_parser.cc"
    break;

  case 448: // reservations_global: "reservations-global" ":" "boolean"
#line 1687 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2879 "dhcp6_parser.cc"
    break;

  case 449: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1693 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2889 "dhcp6_parser.cc"
    break;

  case 450: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1699 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2899 "dhcp6_parser.cc"
    break;

  case 451: // id: "id" ":" "integer"
#line 1705 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2909 "dhcp6_parser.cc"
    break;

  case 452: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1711 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2919 "dhcp6_parser.cc"
    break;

  case 453: // $@69: %empty
#line 1719 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2931 "dhcp6_parser.cc"
    break;

  case 454: // shared_networks: "shared-networks" $@69 ":" "[" shared_networks_content "]"
#line 1725 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2940 "dhcp6_parser.cc"
    break;

  case 459: // shared_networks_list: shared_networks_list ","
#line 1738 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2948 "dhcp6_parser.cc"
    break;

  case 460: // $@70: %empty
#line 1743 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2958 "dhcp6_parser.cc"
    break;

  case 461: // shared_network: "{" $@70 shared_network_params "}"
#line 1747 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2966 "dhcp6_parser.cc"
    break;

  case 464: // shared_network_params: shared_network_params ","
#line 1753 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2974 "dhcp6_parser.cc"
    break;

  case 508: // $@71: %empty
#line 1807 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2986 "dhcp6_parser.cc"
    break;

  case 509: // option_def_list: "option-def" $@71 ":" "[" option_def_list_content "]"
#line 1813 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2995 "dhcp6_parser.cc"
    break;

  case 510: // $@72: %empty
#line 1821 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3004 "dhcp6_parser.cc"
    break;

  case 511: // sub_option_def_list: "{" $@72 option_def_list "}"
#line 1824 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 3012 "dhcp6_parser.cc"
    break;

  case 516: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1836 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3020 "dhcp6_parser.cc"
    break;

  case 517: // $@73: %empty
#line 1843 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3030 "dhcp6_parser.cc"
    break;

  case 518: // option_def_entry: "{" $@73 option_def_params "}"
#line 1847 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3042 "dhcp6_parser.cc"
    break;

  case 519: // $@74: %empty
#line 1858 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3052 "dhcp6_parser.cc"
    break;

  case 520: // sub_option_def: "{" $@74 option_def_params "}"
#line 1862 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3064 "dhcp6_parser.cc"
    break;

  case 525: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1878 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3072 "dhcp6_parser.cc"
    break;

  case 537: // code: "code" ":" "integer"
#line 1897 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3082 "dhcp6_parser.cc"
    break;

  case 539: // $@75: %empty
#line 1905 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3091 "dhcp6_parser.cc"
    break;

  case 540: // option_def_type: "type" $@75 ":" "constant string"
#line 1908 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3101 "dhcp6_parser.cc"
    break;

  case 541: // $@76: %empty
#line 1914 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3110 "dhcp6_parser.cc"
    break;

  case 542: // option_def_record_types: "record-types" $@76 ":" "constant string"
#line 1917 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3120 "dhcp6_parser.cc"
    break;

  case 543: // $@77: %empty
#line 1923 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3129 "dhcp6_parser.cc"
    break;

  case 544: // space: "space" $@77 ":" "constant string"
#line 1926 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3139 "dhcp6_parser.cc"
    break;

  case 546: // $@78: %empty
#line 1934 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3148 "dhcp6_parser.cc"
    break;

  case 547: // option_def_encapsulate: "encapsulate" $@78 ":" "constant string"
#line 1937 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3158 "dhcp6_parser.cc"
    break;

  case 548: // option_def_array: "array" ":" "boolean"
#line 1943 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3168 "dhcp6_parser.cc"
    break;

  case 549: // $@79: %empty
#line 1953 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3180 "dhcp6_parser.cc"
    break;

  case 550: // option_data_list: "option-data" $@79 ":" "[" option_data_list_content "]"
#line 1959 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3189 "dhcp6_parser.cc"
    break;

  case 555: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1974 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3197 "dhcp6_parser.cc"
    break;

  case 556: // $@80: %empty
#line 1981 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3207 "dhcp6_parser.cc"
    break;

  case 557: // option_data_entry: "{" $@80 option_data_params "}"
#line 1985 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3216 "dhcp6_parser.cc"
    break;

  case 558: // $@81: %empty
#line 1993 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3226 "dhcp6_parser.cc"
    break;

  case 559: // sub_option_data: "{" $@81 option_data_params "}"
#line 1997 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3235 "dhcp6_parser.cc"
    break;

  case 564: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2013 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3243 "dhcp6_parser.cc"
    break;

  case 576: // $@82: %empty
#line 2034 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3252 "dhcp6_parser.cc"
    break;

  case 577: // option_data_data: "data" $@82 ":" "constant string"
#line 2037 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3262 "dhcp6_parser.cc"
    break;

  case 580: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2047 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3272 "dhcp6_parser.cc"
    break;

  case 581: // option_data_always_send: "always-send" ":" "boolean"
#line 2053 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3282 "dhcp6_parser.cc"
    break;

  case 582: // option_data_never_send: "never-send" ":" "boolean"
#line 2059 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3292 "dhcp6_parser.cc"
    break;

  case 583: // $@83: %empty
#line 2068 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3304 "dhcp6_parser.cc"
    break;

  case 584: // pools_list: "pools" $@83 ":" "[" pools_list_content "]"
#line 2074 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3313 "dhcp6_parser.cc"
    break;

  case 589: // not_empty_pools_list: not_empty_pools_list ","
#line 2087 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3321 "dhcp6_parser.cc"
    break;

  case 590: // $@84: %empty
#line 2092 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3331 "dhcp6_parser.cc"
    break;

  case 591: // pool_list_entry: "{" $@84 pool_params "}"
#line 2096 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3341 "dhcp6_parser.cc"
    break;

  case 592: // $@85: %empty
#line 2102 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3351 "dhcp6_parser.cc"
    break;

  case 593: // sub_pool6: "{" $@85 pool_params "}"
#line 2106 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3361 "dhcp6_parser.cc"
    break;

  case 596: // pool_params: pool_params ","
#line 2114 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3369 "dhcp6_parser.cc"
    break;

  case 605: // $@86: %empty
#line 2129 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3378 "dhcp6_parser.cc"
    break;

  case 606: // pool_entry: "pool" $@86 ":" "constant string"
#line 2132 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3388 "dhcp6_parser.cc"
    break;

  case 607: // pool_id: "pool-id" ":" "integer"
#line 2138 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3398 "dhcp6_parser.cc"
    break;

  case 608: // $@87: %empty
#line 2144 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3406 "dhcp6_parser.cc"
    break;

  case 609: // user_context: "user-context" $@87 ":" map_value
#line 2146 "dhcp6_parser.yy"
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
#line 3433 "dhcp6_parser.cc"
    break;

  case 610: // $@88: %empty
#line 2169 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3441 "dhcp6_parser.cc"
    break;

  case 611: // comment: "comment" $@88 ":" "constant string"
#line 2171 "dhcp6_parser.yy"
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
#line 3470 "dhcp6_parser.cc"
    break;

  case 612: // $@89: %empty
#line 2199 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3482 "dhcp6_parser.cc"
    break;

  case 613: // pd_pools_list: "pd-pools" $@89 ":" "[" pd_pools_list_content "]"
#line 2205 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3491 "dhcp6_parser.cc"
    break;

  case 618: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2218 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3499 "dhcp6_parser.cc"
    break;

  case 619: // $@90: %empty
#line 2223 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3509 "dhcp6_parser.cc"
    break;

  case 620: // pd_pool_entry: "{" $@90 pd_pool_params "}"
#line 2227 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3521 "dhcp6_parser.cc"
    break;

  case 621: // $@91: %empty
#line 2235 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3531 "dhcp6_parser.cc"
    break;

  case 622: // sub_pd_pool: "{" $@91 pd_pool_params "}"
#line 2239 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3543 "dhcp6_parser.cc"
    break;

  case 625: // pd_pool_params: pd_pool_params ","
#line 2249 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3551 "dhcp6_parser.cc"
    break;

  case 638: // $@92: %empty
#line 2268 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3560 "dhcp6_parser.cc"
    break;

  case 639: // pd_prefix: "prefix" $@92 ":" "constant string"
#line 2271 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3570 "dhcp6_parser.cc"
    break;

  case 640: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2277 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3580 "dhcp6_parser.cc"
    break;

  case 641: // $@93: %empty
#line 2283 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3589 "dhcp6_parser.cc"
    break;

  case 642: // excluded_prefix: "excluded-prefix" $@93 ":" "constant string"
#line 2286 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3599 "dhcp6_parser.cc"
    break;

  case 643: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2292 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3609 "dhcp6_parser.cc"
    break;

  case 644: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2298 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3619 "dhcp6_parser.cc"
    break;

  case 645: // $@94: %empty
#line 2307 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3631 "dhcp6_parser.cc"
    break;

  case 646: // reservations: "reservations" $@94 ":" "[" reservations_list "]"
#line 2313 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3640 "dhcp6_parser.cc"
    break;

  case 651: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2324 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3648 "dhcp6_parser.cc"
    break;

  case 652: // $@95: %empty
#line 2329 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3658 "dhcp6_parser.cc"
    break;

  case 653: // reservation: "{" $@95 reservation_params "}"
#line 2333 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3667 "dhcp6_parser.cc"
    break;

  case 654: // $@96: %empty
#line 2338 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3677 "dhcp6_parser.cc"
    break;

  case 655: // sub_reservation: "{" $@96 reservation_params "}"
#line 2342 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3686 "dhcp6_parser.cc"
    break;

  case 660: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2353 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3694 "dhcp6_parser.cc"
    break;

  case 672: // $@97: %empty
#line 2372 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3706 "dhcp6_parser.cc"
    break;

  case 673: // ip_addresses: "ip-addresses" $@97 ":" list_strings
#line 2378 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3715 "dhcp6_parser.cc"
    break;

  case 674: // $@98: %empty
#line 2383 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3727 "dhcp6_parser.cc"
    break;

  case 675: // prefixes: "prefixes" $@98 ":" list_strings
#line 2389 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3736 "dhcp6_parser.cc"
    break;

  case 676: // $@99: %empty
#line 2394 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3745 "dhcp6_parser.cc"
    break;

  case 677: // duid: "duid" $@99 ":" "constant string"
#line 2397 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3755 "dhcp6_parser.cc"
    break;

  case 678: // $@100: %empty
#line 2403 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3764 "dhcp6_parser.cc"
    break;

  case 679: // hw_address: "hw-address" $@100 ":" "constant string"
#line 2406 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3774 "dhcp6_parser.cc"
    break;

  case 680: // $@101: %empty
#line 2412 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3783 "dhcp6_parser.cc"
    break;

  case 681: // hostname: "hostname" $@101 ":" "constant string"
#line 2415 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3793 "dhcp6_parser.cc"
    break;

  case 682: // $@102: %empty
#line 2421 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3802 "dhcp6_parser.cc"
    break;

  case 683: // flex_id_value: "flex-id" $@102 ":" "constant string"
#line 2424 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3812 "dhcp6_parser.cc"
    break;

  case 684: // $@103: %empty
#line 2430 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3824 "dhcp6_parser.cc"
    break;

  case 685: // reservation_client_classes: "client-classes" $@103 ":" list_strings
#line 2436 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3833 "dhcp6_parser.cc"
    break;

  case 686: // $@104: %empty
#line 2444 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3845 "dhcp6_parser.cc"
    break;

  case 687: // relay: "relay" $@104 ":" "{" relay_map "}"
#line 2450 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3854 "dhcp6_parser.cc"
    break;

  case 689: // $@105: %empty
#line 2461 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3866 "dhcp6_parser.cc"
    break;

  case 690: // client_classes: "client-classes" $@105 ":" "[" client_classes_list "]"
#line 2467 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3875 "dhcp6_parser.cc"
    break;

  case 693: // client_classes_list: client_classes_list ","
#line 2474 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3883 "dhcp6_parser.cc"
    break;

  case 694: // $@106: %empty
#line 2479 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3893 "dhcp6_parser.cc"
    break;

  case 695: // client_class_entry: "{" $@106 client_class_params "}"
#line 2483 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3903 "dhcp6_parser.cc"
    break;

  case 700: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2495 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3911 "dhcp6_parser.cc"
    break;

  case 716: // $@107: %empty
#line 2518 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3920 "dhcp6_parser.cc"
    break;

  case 717: // client_class_test: "test" $@107 ":" "constant string"
#line 2521 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3930 "dhcp6_parser.cc"
    break;

  case 718: // $@108: %empty
#line 2527 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3939 "dhcp6_parser.cc"
    break;

  case 719: // client_class_template_test: "template-test" $@108 ":" "constant string"
#line 2530 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3949 "dhcp6_parser.cc"
    break;

  case 720: // only_if_required: "only-if-required" ":" "boolean"
#line 2536 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3959 "dhcp6_parser.cc"
    break;

  case 721: // $@109: %empty
#line 2545 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3971 "dhcp6_parser.cc"
    break;

  case 722: // server_id: "server-id" $@109 ":" "{" server_id_params "}"
#line 2551 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3982 "dhcp6_parser.cc"
    break;

  case 725: // server_id_params: server_id_params ","
#line 2560 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 3990 "dhcp6_parser.cc"
    break;

  case 735: // $@110: %empty
#line 2576 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3999 "dhcp6_parser.cc"
    break;

  case 736: // server_id_type: "type" $@110 ":" duid_type
#line 2579 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4008 "dhcp6_parser.cc"
    break;

  case 737: // duid_type: "LLT"
#line 2584 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4014 "dhcp6_parser.cc"
    break;

  case 738: // duid_type: "EN"
#line 2585 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4020 "dhcp6_parser.cc"
    break;

  case 739: // duid_type: "LL"
#line 2586 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4026 "dhcp6_parser.cc"
    break;

  case 740: // htype: "htype" ":" "integer"
#line 2589 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4036 "dhcp6_parser.cc"
    break;

  case 741: // $@111: %empty
#line 2595 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4045 "dhcp6_parser.cc"
    break;

  case 742: // identifier: "identifier" $@111 ":" "constant string"
#line 2598 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4055 "dhcp6_parser.cc"
    break;

  case 743: // time: "time" ":" "integer"
#line 2604 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4065 "dhcp6_parser.cc"
    break;

  case 744: // enterprise_id: "enterprise-id" ":" "integer"
#line 2610 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4075 "dhcp6_parser.cc"
    break;

  case 745: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2618 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4085 "dhcp6_parser.cc"
    break;

  case 746: // $@112: %empty
#line 2626 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4097 "dhcp6_parser.cc"
    break;

  case 747: // control_socket: "control-socket" $@112 ":" "{" control_socket_params "}"
#line 2632 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4106 "dhcp6_parser.cc"
    break;

  case 750: // control_socket_params: control_socket_params ","
#line 2639 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4114 "dhcp6_parser.cc"
    break;

  case 756: // $@113: %empty
#line 2651 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4123 "dhcp6_parser.cc"
    break;

  case 757: // socket_type: "socket-type" $@113 ":" "constant string"
#line 2654 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 4133 "dhcp6_parser.cc"
    break;

  case 758: // $@114: %empty
#line 2660 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4142 "dhcp6_parser.cc"
    break;

  case 759: // socket_name: "socket-name" $@114 ":" "constant string"
#line 2663 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4152 "dhcp6_parser.cc"
    break;

  case 760: // $@115: %empty
#line 2672 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4164 "dhcp6_parser.cc"
    break;

  case 761: // dhcp_queue_control: "dhcp-queue-control" $@115 ":" "{" queue_control_params "}"
#line 2678 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4175 "dhcp6_parser.cc"
    break;

  case 764: // queue_control_params: queue_control_params ","
#line 2687 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4183 "dhcp6_parser.cc"
    break;

  case 771: // enable_queue: "enable-queue" ":" "boolean"
#line 2700 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4193 "dhcp6_parser.cc"
    break;

  case 772: // $@116: %empty
#line 2706 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4202 "dhcp6_parser.cc"
    break;

  case 773: // queue_type: "queue-type" $@116 ":" "constant string"
#line 2709 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4212 "dhcp6_parser.cc"
    break;

  case 774: // capacity: "capacity" ":" "integer"
#line 2715 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4222 "dhcp6_parser.cc"
    break;

  case 775: // $@117: %empty
#line 2721 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4231 "dhcp6_parser.cc"
    break;

  case 776: // arbitrary_map_entry: "constant string" $@117 ":" value
#line 2724 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4240 "dhcp6_parser.cc"
    break;

  case 777: // $@118: %empty
#line 2731 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4252 "dhcp6_parser.cc"
    break;

  case 778: // dhcp_ddns: "dhcp-ddns" $@118 ":" "{" dhcp_ddns_params "}"
#line 2737 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4263 "dhcp6_parser.cc"
    break;

  case 779: // $@119: %empty
#line 2744 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4273 "dhcp6_parser.cc"
    break;

  case 780: // sub_dhcp_ddns: "{" $@119 dhcp_ddns_params "}"
#line 2748 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4283 "dhcp6_parser.cc"
    break;

  case 783: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2756 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4291 "dhcp6_parser.cc"
    break;

  case 795: // enable_updates: "enable-updates" ":" "boolean"
#line 2774 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4301 "dhcp6_parser.cc"
    break;

  case 796: // $@120: %empty
#line 2780 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4310 "dhcp6_parser.cc"
    break;

  case 797: // server_ip: "server-ip" $@120 ":" "constant string"
#line 2783 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4320 "dhcp6_parser.cc"
    break;

  case 798: // server_port: "server-port" ":" "integer"
#line 2789 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4330 "dhcp6_parser.cc"
    break;

  case 799: // $@121: %empty
#line 2795 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4339 "dhcp6_parser.cc"
    break;

  case 800: // sender_ip: "sender-ip" $@121 ":" "constant string"
#line 2798 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4349 "dhcp6_parser.cc"
    break;

  case 801: // sender_port: "sender-port" ":" "integer"
#line 2804 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4359 "dhcp6_parser.cc"
    break;

  case 802: // max_queue_size: "max-queue-size" ":" "integer"
#line 2810 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4369 "dhcp6_parser.cc"
    break;

  case 803: // $@122: %empty
#line 2816 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4378 "dhcp6_parser.cc"
    break;

  case 804: // ncr_protocol: "ncr-protocol" $@122 ":" ncr_protocol_value
#line 2819 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4387 "dhcp6_parser.cc"
    break;

  case 805: // ncr_protocol_value: "UDP"
#line 2825 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4393 "dhcp6_parser.cc"
    break;

  case 806: // ncr_protocol_value: "TCP"
#line 2826 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4399 "dhcp6_parser.cc"
    break;

  case 807: // $@123: %empty
#line 2829 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4408 "dhcp6_parser.cc"
    break;

  case 808: // ncr_format: "ncr-format" $@123 ":" "JSON"
#line 2832 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4418 "dhcp6_parser.cc"
    break;

  case 809: // $@124: %empty
#line 2840 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4430 "dhcp6_parser.cc"
    break;

  case 810: // config_control: "config-control" $@124 ":" "{" config_control_params "}"
#line 2846 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4440 "dhcp6_parser.cc"
    break;

  case 811: // $@125: %empty
#line 2852 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4450 "dhcp6_parser.cc"
    break;

  case 812: // sub_config_control: "{" $@125 config_control_params "}"
#line 2856 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4459 "dhcp6_parser.cc"
    break;

  case 815: // config_control_params: config_control_params ","
#line 2864 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4467 "dhcp6_parser.cc"
    break;

  case 818: // $@126: %empty
#line 2874 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4479 "dhcp6_parser.cc"
    break;

  case 819: // config_databases: "config-databases" $@126 ":" "[" database_list "]"
#line 2880 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4488 "dhcp6_parser.cc"
    break;

  case 820: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2885 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4498 "dhcp6_parser.cc"
    break;

  case 821: // $@127: %empty
#line 2893 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4510 "dhcp6_parser.cc"
    break;

  case 822: // loggers: "loggers" $@127 ":" "[" loggers_entries "]"
#line 2899 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4519 "dhcp6_parser.cc"
    break;

  case 825: // loggers_entries: loggers_entries ","
#line 2908 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4527 "dhcp6_parser.cc"
    break;

  case 826: // $@128: %empty
#line 2914 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4537 "dhcp6_parser.cc"
    break;

  case 827: // logger_entry: "{" $@128 logger_params "}"
#line 2918 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4545 "dhcp6_parser.cc"
    break;

  case 830: // logger_params: logger_params ","
#line 2924 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4553 "dhcp6_parser.cc"
    break;

  case 838: // debuglevel: "debuglevel" ":" "integer"
#line 2938 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4563 "dhcp6_parser.cc"
    break;

  case 839: // $@129: %empty
#line 2944 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4572 "dhcp6_parser.cc"
    break;

  case 840: // severity: "severity" $@129 ":" "constant string"
#line 2947 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4582 "dhcp6_parser.cc"
    break;

  case 841: // $@130: %empty
#line 2953 "dhcp6_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4594 "dhcp6_parser.cc"
    break;

  case 842: // output_options_list: "output-options" $@130 ":" "[" output_options_list_content "]"
#line 2959 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4603 "dhcp6_parser.cc"
    break;

  case 845: // output_options_list_content: output_options_list_content ","
#line 2966 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4611 "dhcp6_parser.cc"
    break;

  case 846: // $@131: %empty
#line 2971 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4621 "dhcp6_parser.cc"
    break;

  case 847: // output_entry: "{" $@131 output_params_list "}"
#line 2975 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4629 "dhcp6_parser.cc"
    break;

  case 850: // output_params_list: output_params_list ","
#line 2981 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4637 "dhcp6_parser.cc"
    break;

  case 856: // $@132: %empty
#line 2993 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4646 "dhcp6_parser.cc"
    break;

  case 857: // output: "output" $@132 ":" "constant string"
#line 2996 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4656 "dhcp6_parser.cc"
    break;

  case 858: // flush: "flush" ":" "boolean"
#line 3002 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4666 "dhcp6_parser.cc"
    break;

  case 859: // maxsize: "maxsize" ":" "integer"
#line 3008 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4676 "dhcp6_parser.cc"
    break;

  case 860: // maxver: "maxver" ":" "integer"
#line 3014 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4686 "dhcp6_parser.cc"
    break;

  case 861: // $@133: %empty
#line 3020 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4695 "dhcp6_parser.cc"
    break;

  case 862: // pattern: "pattern" $@133 ":" "constant string"
#line 3023 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4705 "dhcp6_parser.cc"
    break;

  case 863: // $@134: %empty
#line 3029 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4717 "dhcp6_parser.cc"
    break;

  case 864: // compatibility: "compatibility" $@134 ":" "{" compatibility_params "}"
#line 3035 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4726 "dhcp6_parser.cc"
    break;

  case 867: // compatibility_params: compatibility_params ","
#line 3042 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4734 "dhcp6_parser.cc"
    break;

  case 870: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3051 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4744 "dhcp6_parser.cc"
    break;


#line 4748 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1000;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     432, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000,    35,    34,    70,    82,    89,
     115,   121,   123,   131,   133,   139,   141,   147,   156,   163,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,    34,  -175,
      99,   167,    75,   669,   322,   214,   282,   -35,    77,   313,
     -94,   455,    54, -1000,    55,   174,   183,   185,   188, -1000,
      96, -1000, -1000, -1000, -1000, -1000, -1000, -1000,   196,   211,
     267,   285,   289,   303,   307,   330,   336,   337,   347,   354,
     377,   379, -1000,   388,   389,   397,   403,   409, -1000, -1000,
   -1000,   422,   436,   442,   449, -1000, -1000, -1000,   450, -1000,
   -1000, -1000, -1000, -1000, -1000,   452,   456,   462, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000,   465, -1000, -1000,
   -1000, -1000, -1000, -1000,   466,   472,   480, -1000, -1000,   482,
   -1000,   154, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000,   483,   486,   487,   489, -1000,   161, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
     491,   492, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000,   172, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000,   494, -1000, -1000, -1000, -1000,   173,
   -1000, -1000, -1000, -1000, -1000, -1000,   495, -1000,   497,   499,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000,   191, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000,   255,   301, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000,   323, -1000, -1000,   501, -1000,
   -1000, -1000,   505, -1000, -1000,   353,   335, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
     506,   510,   511, -1000, -1000, -1000, -1000,   396,   425, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000,   198, -1000, -1000, -1000,   515, -1000,   516, -1000,
     518,   522, -1000, -1000, -1000, -1000, -1000,   199, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,   523,   209,
   -1000, -1000, -1000, -1000,    34,    34, -1000,   220,   530, -1000,
   -1000,   531,   535,   536,   537,   540,   543,   242,   332,   333,
     343,   350,   351,   352,   358,   355,   338,   359,   363,   365,
     366,   546,   369,   370,   371,   375,   381,   547,   548,   565,
     382,   383,   378,   385,   579,   583,   584,   390,   594,   601,
     605,   606,   607,   608,   398,   399,   401,   610,   611,   614,
     617,   618,   619,   620,   643,   645,   437,   646,   648,   650,
     651,   652,   653,   443,   444,   445,   654,   655, -1000,   167,
   -1000,   656,   446,   448,   451,   453,    75, -1000,   664,   667,
     668,   670,   671,   457,   458,   673,   674,   675,   669, -1000,
     676,   467,   322, -1000,   677,   468,   678,   469,   473,   214,
   -1000,   687,   688,   689,   691,   692,   693,   694, -1000,   282,
   -1000,   695,   701,   490,   703,   705,   706,   493, -1000,    77,
     708,   496,   498,   500, -1000,   313,   709,   711,   137, -1000,
     517,   713,   520,   729,   532,   534,   730,   743,   455, -1000,
     747,   544,    54, -1000, -1000, -1000,   748,   746,   549,   752,
     758,   759,   760,   763, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,   555, -1000,
   -1000, -1000, -1000, -1000,   -50,   557,   558, -1000, -1000, -1000,
   -1000,   769,   770,   771, -1000,   572,   573,   367,   784,   783,
     576, -1000, -1000, -1000,   787,   788,   790,   789,   792,   794,
     796,   795,   797, -1000,   798,   799,   801,   802,   588,   595,
   -1000, -1000, -1000,   806,   805, -1000,   808, -1000, -1000, -1000,
   -1000, -1000,   809,   823,   615,   616,   628, -1000, -1000,   808,
     631,   822, -1000,   632, -1000, -1000,   633, -1000,   634, -1000,
   -1000, -1000,   808,   808,   808,   635,   636,   637,   638, -1000,
     644,   647, -1000,   649,   659,   662, -1000, -1000,   672, -1000,
   -1000, -1000, -1000,   679,   783, -1000, -1000,   680, -1000,   681,
   -1000, -1000,   102,   683, -1000,   855, -1000, -1000,    34,   167,
   -1000,    54,    75,   339,   339,   854, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000,   858,   859,   860, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000,   861, -1000, -1000, -1000,  -101,
      34,   -53,   192,   862,   863,   864,   202,    42,    95,   -44,
     -23,   455, -1000, -1000,   875,  -152, -1000, -1000,   876,   878,
   -1000, -1000, -1000, -1000, -1000,   754, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
     854, -1000,   245,   261,   271, -1000, -1000, -1000, -1000,   884,
     886,   887,   888,   893,   894,   895,   896,   897,   899, -1000,
     900,   901, -1000, -1000, -1000, -1000, -1000,   292, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000,   293, -1000,   902,   903, -1000, -1000,   904,   906, -1000,
   -1000,   905,   909, -1000, -1000,   907,   911, -1000, -1000,   910,
     912, -1000, -1000, -1000,    39, -1000, -1000, -1000,   913, -1000,
   -1000, -1000,    94, -1000, -1000, -1000, -1000, -1000,   294, -1000,
   -1000, -1000, -1000,   112, -1000, -1000,   914,   915, -1000, -1000,
     916,   918, -1000,   919,   920,   921,   922,   923,   924,   300,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,   925,
     926,   927, -1000, -1000, -1000, -1000,   325, -1000, -1000, -1000,
   -1000, -1000, -1000,   928,   929,   930, -1000,   327, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,   334,
   -1000, -1000, -1000,   931, -1000,   932, -1000, -1000, -1000,   356,
   -1000, -1000, -1000, -1000, -1000,   357, -1000,   210, -1000,   933,
   -1000,   400, -1000, -1000,   702, -1000,   934,   935, -1000, -1000,
     936,   938, -1000, -1000,   939,   937, -1000, -1000, -1000,   940,
     942,   948,   949,   723,   738,   742,   749,   744,   745,   773,
     774,   775,   779,   966,   756,   807,   971,   981,   983,   999,
     339, -1000, -1000,   339, -1000,   854,   669, -1000,   858,    77,
   -1000,   859,   313, -1000,   860,   764, -1000,   861,  -101, -1000,
   -1000,   -53, -1000,  1000,  1008,   192, -1000,    -1,   862, -1000,
     282, -1000,   863,   -94, -1000,   864,   812,   827,   828,   848,
     881,   882,   202, -1000,  1021,  1034,   891,   892,   898,    42,
   -1000,   885,   917,   941,    95, -1000,  1073,  1096,   -44, -1000,
     908,  1098,   943,  1105,   -23, -1000, -1000,   218,   875, -1000,
     944,  -152, -1000, -1000,  1104,  1108,   322, -1000,   876,   214,
   -1000,   878, -1000, -1000,   454,   945,   946,   950, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,   430, -1000,
   -1000,   951,   953,   954,   956, -1000,   402, -1000,   424, -1000,
    1107, -1000,  1109, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000,   431, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000,   957,   958, -1000, -1000, -1000,  1112, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,  1110,
    1116, -1000, -1000, -1000, -1000, -1000, -1000,  1113, -1000,   433,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,   380,   959,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,   960,   961,
   -1000, -1000,   962, -1000,    34, -1000, -1000,  1118, -1000, -1000,
   -1000, -1000, -1000,   434, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000,   963,   440, -1000,   441, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000,   764, -1000, -1000, -1000,
    1119,  1121,   964, -1000,    -1, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000,  1124,   947,  1125,   218,
   -1000, -1000, -1000, -1000, -1000,   965,   968, -1000, -1000,  1115,
   -1000,   969, -1000, -1000, -1000,  1106, -1000, -1000,   259, -1000,
      13,  1106, -1000, -1000,  1126,  1127,  1128, -1000,   447, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000,  1130,   967,   970,   972,
    1131,    13, -1000,   974, -1000, -1000, -1000,   975, -1000, -1000,
   -1000
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   198,     9,   387,    11,
     592,    13,   621,    15,   654,    17,   510,    19,   519,    21,
     558,    23,   349,    25,   779,    27,   811,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   656,     0,   521,   560,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   140,   809,   196,   217,   219,   221,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   186,     0,     0,     0,     0,     0,   159,   166,
     168,     0,     0,     0,     0,   378,   508,   549,     0,   189,
     191,   172,   453,   608,   610,     0,     0,     0,   305,   324,
     314,   294,   689,   645,   340,   361,   721,     0,   326,   746,
     760,   777,   179,   181,     0,     0,     0,   821,   863,     0,
     139,     0,    69,    72,    73,    74,    75,    76,    77,    78,
      79,    80,   110,   111,   112,   113,   114,    81,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   116,   117,
     128,   129,   130,   106,   136,   137,   138,   132,   133,   134,
      84,    85,    86,    87,   103,    88,    90,    89,   131,    94,
      95,    82,   107,   108,   109,    83,    92,    93,   101,   102,
     104,    91,    96,    97,    98,    99,   100,   105,   115,   135,
     211,     0,     0,     0,     0,   210,     0,   200,   203,   204,
     205,   206,   207,   208,   209,   583,   612,   438,   440,   442,
       0,     0,   446,   444,   686,   437,   392,   393,   394,   395,
     396,   397,   398,   399,   417,   418,   419,   420,   421,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   422,
     423,   434,   435,   436,     0,   389,   403,   404,   405,   408,
     409,   411,   412,   413,   406,   407,   400,   401,   415,   416,
     402,   410,   414,   605,     0,   604,   600,   601,   599,     0,
     594,   597,   598,   602,   603,   638,     0,   641,     0,     0,
     637,   631,   632,   630,   629,   635,   636,     0,   623,   626,
     627,   633,   634,   628,   684,   672,   674,   676,   678,   680,
     682,   671,   668,   669,   670,     0,   657,   658,   663,   664,
     661,   665,   666,   667,   662,     0,   539,   268,     0,   543,
     541,   546,     0,   535,   536,     0,   522,   523,   526,   538,
     527,   528,   529,   545,   530,   531,   532,   533,   534,   576,
       0,     0,     0,   574,   575,   578,   579,     0,   561,   562,
     565,   566,   567,   568,   569,   570,   571,   572,   573,   357,
     359,   354,     0,   351,   355,   356,     0,   796,     0,   799,
       0,     0,   803,   807,   794,   792,   793,     0,   781,   784,
     785,   786,   787,   788,   789,   790,   791,   818,     0,     0,
     813,   816,   817,    47,    52,     0,    39,    45,     0,    66,
      62,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    60,    71,
      68,     0,     0,     0,     0,     0,   202,   199,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   391,   388,
       0,     0,   596,   593,     0,     0,     0,     0,     0,   625,
     622,     0,     0,     0,     0,     0,     0,     0,   655,   660,
     511,     0,     0,     0,     0,     0,     0,     0,   520,   525,
       0,     0,     0,     0,   559,   564,     0,     0,   353,   350,
       0,     0,     0,     0,     0,     0,     0,     0,   783,   780,
       0,     0,   815,   812,    51,    43,     0,     0,     0,     0,
       0,     0,     0,     0,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,     0,   184,
     185,   156,   157,   158,     0,     0,     0,   170,   171,   178,
     183,     0,     0,     0,   188,     0,     0,     0,     0,     0,
       0,   448,   449,   450,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   745,     0,     0,     0,     0,     0,     0,
     193,   194,   195,     0,     0,    70,     0,   213,   214,   215,
     216,   201,     0,     0,     0,     0,     0,   451,   452,     0,
       0,     0,   390,     0,   607,   595,     0,   640,     0,   643,
     644,   624,     0,     0,     0,     0,     0,     0,     0,   659,
       0,     0,   537,     0,     0,     0,   548,   524,     0,   580,
     581,   582,   563,     0,     0,   352,   795,     0,   798,     0,
     801,   802,     0,     0,   782,     0,   820,   814,     0,     0,
     141,     0,     0,     0,     0,   223,   187,   161,   162,   163,
     164,   165,   160,   167,   169,   380,   512,   551,   190,   192,
     174,   175,   176,   177,   173,   455,    40,   609,   611,     0,
      48,     0,     0,     0,   647,   342,     0,     0,     0,     0,
       0,     0,   180,   182,     0,     0,    53,   212,   585,   614,
     439,   441,   443,   447,   445,     0,   606,   639,   642,   685,
     673,   675,   677,   679,   681,   683,   540,   269,   544,   542,
     547,   577,   358,   360,   797,   800,   805,   806,   804,   808,
     223,    44,     0,     0,     0,   256,   261,   263,   265,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   278,
       0,     0,   286,   288,   290,   292,   255,     0,   230,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   247,   248,   249,   250,   246,   251,   252,   253,
     254,     0,   228,     0,   224,   225,   385,     0,   381,   382,
     517,     0,   513,   514,   556,     0,   552,   553,   460,     0,
     456,   457,   312,   313,     0,   307,   310,   311,     0,   322,
     323,   319,     0,   316,   320,   321,   301,   303,     0,   296,
     299,   300,   694,     0,   691,   652,     0,   648,   649,   347,
       0,   343,   344,     0,     0,     0,     0,     0,     0,     0,
     363,   366,   367,   368,   369,   370,   371,   735,   741,     0,
       0,     0,   734,   731,   732,   733,     0,   723,   726,   729,
     727,   728,   730,     0,     0,     0,   336,     0,   328,   331,
     332,   333,   334,   335,   756,   758,   755,   753,   754,     0,
     748,   751,   752,     0,   772,     0,   775,   768,   769,     0,
     762,   765,   766,   767,   770,     0,   826,     0,   823,     0,
     869,     0,   865,   868,    55,   590,     0,   586,   587,   619,
       0,   615,   616,   688,     0,     0,    64,   810,   197,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     232,   218,   220,     0,   222,   227,     0,   379,   384,   521,
     509,   516,   560,   550,   555,     0,   454,   459,   309,   306,
     325,   318,   315,     0,     0,   298,   295,   696,   693,   690,
     656,   646,   651,     0,   341,   346,     0,     0,     0,     0,
       0,     0,   365,   362,     0,     0,     0,     0,     0,   725,
     722,     0,     0,     0,   330,   327,     0,     0,   750,   747,
       0,     0,     0,     0,   764,   761,   778,     0,   825,   822,
       0,   867,   864,    57,     0,    56,     0,   584,   589,     0,
     613,   618,   687,   819,     0,     0,     0,     0,   267,   270,
     271,   272,   273,   274,   275,   276,   285,   277,     0,   283,
     284,     0,     0,     0,     0,   231,     0,   226,     0,   383,
       0,   515,     0,   554,   507,   478,   479,   480,   482,   483,
     484,   469,   470,   487,   488,   489,   490,   491,   494,   495,
     496,   497,   498,   499,   500,   501,   502,   503,   492,   493,
     504,   505,   506,   465,   466,   467,   468,   476,   477,   473,
     474,   475,   481,     0,   462,   471,   485,   486,   472,   458,
     308,   317,     0,     0,   297,   716,   718,     0,   714,   708,
     709,   710,   711,   712,   713,   715,   705,   706,   707,     0,
     697,   698,   701,   702,   703,   704,   692,     0,   650,     0,
     345,   372,   373,   374,   375,   376,   377,   364,     0,     0,
     740,   743,   744,   724,   337,   338,   339,   329,     0,     0,
     749,   771,     0,   774,     0,   763,   841,     0,   839,   837,
     831,   835,   836,     0,   828,   833,   834,   832,   824,   870,
     866,    54,    59,     0,   588,     0,   617,   258,   259,   260,
     257,   262,   264,   266,   280,   281,   282,   279,   287,   289,
     291,   293,   229,   386,   518,   557,   464,   461,   302,   304,
       0,     0,     0,   695,   700,   653,   348,   737,   738,   739,
     736,   742,   757,   759,   773,   776,     0,     0,     0,   830,
     827,    58,   591,   620,   463,     0,     0,   720,   699,     0,
     838,     0,   829,   717,   719,     0,   840,   846,     0,   843,
       0,   845,   842,   856,     0,     0,     0,   861,     0,   848,
     851,   852,   853,   854,   855,   844,     0,     0,     0,     0,
       0,   850,   847,     0,   858,   859,   860,     0,   849,   857,
     862
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000,   -10, -1000,  -593, -1000,
     203, -1000, -1000, -1000, -1000,   362, -1000,  -510, -1000, -1000,
   -1000,   -71, -1000, -1000, -1000, -1000, -1000, -1000, -1000,   417,
     629, -1000, -1000,   -61,   -43,   -39,    10,    14,    15,   -24,
     -17,   -11,    17,    25,    29,    30, -1000,    32,    33,    37,
      43, -1000, -1000,    44, -1000,    50, -1000,    51,    56,    62,
   -1000, -1000,    63,    64, -1000,    66, -1000,    68, -1000, -1000,
   -1000, -1000, -1000,    69, -1000,    74, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000,   415,   623, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,   340, -1000,
     126, -1000,  -701,   132, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000,   -41, -1000,  -746, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000,   108, -1000, -1000, -1000, -1000, -1000, -1000, -1000,   116,
    -726, -1000, -1000, -1000, -1000,   114, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000,    83, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000,   101, -1000, -1000, -1000,   105,   581, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000,    98, -1000, -1000, -1000, -1000, -1000,
   -1000,  -999, -1000, -1000, -1000,   134, -1000, -1000, -1000,   135,
     625, -1000, -1000,  -998, -1000,  -996, -1000,    38, -1000,    81,
   -1000,    76,    79,    80, -1000,  -994, -1000, -1000, -1000, -1000,
     127, -1000, -1000,  -111,  1079, -1000, -1000, -1000, -1000, -1000,
     143, -1000, -1000, -1000,   160, -1000,   599, -1000,   -65, -1000,
   -1000, -1000, -1000, -1000,   -59, -1000, -1000, -1000, -1000, -1000,
     -16, -1000, -1000, -1000,   157, -1000, -1000, -1000,   165, -1000,
     626, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000,   104, -1000, -1000, -1000,   107,   665, -1000,
   -1000,   -62,   -57, -1000,    -3, -1000, -1000, -1000, -1000, -1000,
     103, -1000, -1000, -1000,   109,   657, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000,   -45, -1000, -1000, -1000,   158, -1000, -1000,
   -1000,   159, -1000,   658,   426, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,  -993, -1000,
   -1000, -1000, -1000, -1000,   164, -1000, -1000, -1000,   -70, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,   149, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000,   138, -1000, -1000, -1000, -1000, -1000, -1000, -1000,   136,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
     459,   641, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,   503,
     630, -1000, -1000, -1000, -1000, -1000, -1000,   144, -1000, -1000,
     -78, -1000, -1000, -1000, -1000, -1000, -1000,   -96, -1000, -1000,
    -115, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
   -1000,   140, -1000
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     747,    87,    88,    41,    68,    84,    85,   767,   974,  1084,
    1085,   826,    43,    70,    90,   438,    91,    45,    71,   161,
     162,   163,   441,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   467,   732,   182,   468,   183,   469,   184,   185,   186,
     480,   744,   187,   188,   501,   189,   502,   190,   191,   192,
     193,   461,   194,   195,   478,   196,   479,   197,   198,   199,
     200,   443,    47,    72,   236,   237,   238,   511,   239,   240,
     241,   242,   201,   444,   202,   445,   203,   446,   853,   854,
     855,  1013,   827,   828,   829,   989,  1250,   830,   990,   831,
     991,   832,   992,   833,   834,   552,   835,   836,   837,   838,
     839,   840,   841,   842,   843,  1003,  1257,   844,   845,   846,
     847,  1006,   848,  1007,   849,  1008,   850,  1009,   204,   490,
     888,   889,   890,  1033,   891,  1034,   205,   487,   874,   875,
     876,   877,   206,   489,   882,   883,   884,   885,   207,   488,
     208,   497,   937,   938,   939,   940,   941,   209,   493,   900,
     901,   902,  1043,    63,    80,   402,   403,   404,   566,   405,
     567,   210,   494,   909,   910,   911,   912,   913,   914,   915,
     916,   211,   474,   857,   858,   859,  1016,    49,    73,   284,
     285,   286,   520,   287,   521,   288,   522,   289,   526,   290,
     525,   212,   213,   214,   294,   295,   215,   481,   869,   870,
     871,  1025,  1163,  1164,   216,   475,    57,    77,   861,   862,
     863,  1019,    59,    78,   365,   366,   367,   368,   369,   370,
     371,   551,   372,   555,   373,   554,   374,   375,   556,   376,
     217,   476,   865,   866,   867,  1022,    61,    79,   387,   388,
     389,   390,   391,   560,   392,   393,   394,   395,   396,   297,
     518,   976,   977,   978,  1086,    51,    74,   309,   310,   311,
     530,   312,   218,   482,   219,   483,   300,   519,   980,   981,
     982,  1089,    53,    75,   327,   328,   329,   534,   330,   331,
     536,   332,   333,   220,   492,   896,   897,   898,  1040,    55,
      76,   345,   346,   347,   348,   542,   349,   543,   350,   544,
     351,   545,   352,   546,   353,   547,   354,   541,   302,   527,
     984,   221,   491,   893,   894,  1037,  1189,  1190,  1191,  1192,
    1193,  1270,  1194,  1271,  1195,   222,   495,   926,   927,   928,
    1054,  1280,   929,   930,  1055,   931,   932,   223,   224,   498,
     949,   950,   951,  1066,   952,  1067,   225,   499,   959,   960,
     961,   962,  1071,   963,   964,  1073,   226,   500,    65,    81,
     417,   418,   419,   420,   571,   421,   422,   573,   423,   424,
     425,   576,   798,   426,   577,   227,   442,    67,    82,   429,
     430,   431,   580,   432,   228,   506,   967,   968,  1077,  1233,
    1234,  1235,  1236,  1288,  1237,  1286,  1308,  1309,  1310,  1318,
    1319,  1320,  1326,  1321,  1322,  1323,  1324,  1330,   229,   507,
     971,   972,   973
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     160,   235,   255,   305,   320,   341,    38,   363,   383,   401,
     414,   923,   256,   324,   385,   243,   298,   313,   325,   343,
     386,   377,   397,   851,   415,   881,  1154,  1155,   301,  1156,
     257,  1162,  1168,   872,   258,    30,   746,   364,   384,    31,
      86,    32,  1028,    33,   126,  1029,   399,   400,   969,   262,
      98,    99,   100,   101,   102,   103,   263,   296,   308,   323,
     342,   433,   264,   159,   133,   134,   917,   427,   428,   244,
     299,   314,   326,   344,   810,   378,   398,    42,   416,   127,
     357,   872,   879,   259,   880,   133,   134,   260,   261,    44,
     265,   230,   231,   232,   233,   234,    46,  1031,   266,   439,
    1032,   356,   267,   268,   440,   269,   270,   133,   134,    89,
     271,   746,   306,   321,   873,  1038,   272,   273,  1039,   944,
     945,   159,    48,   274,   275,  1175,  1176,  1177,    50,   276,
      52,   727,   728,   729,   730,   277,   278,   279,    54,   280,
      56,   281,   282,   953,   954,   955,    58,   283,    60,   291,
     133,   134,   292,   293,    62,   307,   322,   509,   357,   773,
     358,   359,   510,    64,   516,   360,   361,   362,   731,   517,
      66,   159,   779,   780,   781,   528,   532,   434,    92,    93,
     529,   533,    94,   133,   134,   133,   134,   435,    95,    96,
      97,   437,   956,   436,   539,   918,   919,   920,   921,   540,
     447,   568,   578,   133,   134,  1313,   569,   579,  1314,  1315,
    1316,  1317,   582,  1078,   159,   448,  1079,   583,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   509,    34,
      35,    36,    37,   986,   933,   934,   935,   159,   128,   129,
     130,   131,  1311,   548,   582,  1312,   132,  1154,  1155,   987,
    1156,   449,  1162,  1168,   516,   133,   134,   399,   400,   988,
     796,   797,   135,   136,   137,   138,   139,   140,   141,   450,
     159,   142,   159,   451,   127,  1010,  1010,  1035,   143,   357,
    1011,  1012,  1036,  1052,   549,   881,   144,   452,  1053,   145,
     159,   453,  1116,   923,   886,   887,   146,   315,   316,   317,
     318,   319,   133,   134,   147,   148,   133,   134,  1059,   149,
    1064,   550,   150,  1060,   454,  1065,   151,  1068,   559,   252,
     455,   456,  1069,   253,   304,   903,   904,   905,   906,   907,
     908,   457,   152,   153,   154,   155,   156,   157,   458,  1074,
     578,   558,   127,   805,  1075,  1076,   158,   806,   807,   808,
     809,   810,   811,   812,   813,   814,   815,   816,   817,   818,
     819,   459,   159,   460,   820,   821,   822,   823,   824,   825,
     133,   134,   462,   463,   357,   379,   358,   359,   380,   381,
     382,   464,   127,  1081,   564,  1010,   334,   465,  1082,  1226,
    1262,  1227,  1228,   466,   335,   336,   337,   338,   339,   340,
     357,   133,   134,   303,   584,   585,   470,   528,   565,   159,
     133,   134,  1263,   159,  1266,   586,   568,  1289,   160,  1267,
     471,  1276,  1290,   532,   539,   235,   472,   252,  1292,  1293,
    1331,   253,   304,   473,   477,  1332,   484,   255,   594,   243,
     485,   305,   740,   741,   742,   743,   486,   256,   320,   496,
     503,   298,  1254,  1255,  1256,   313,   504,   324,   341,  1247,
    1248,  1249,   325,   301,   505,   257,   508,   512,   363,   258,
     513,   514,   343,   515,   383,   523,   524,   159,   531,   535,
     385,   537,   377,   538,   262,   553,   386,   414,   397,   557,
     561,   263,   296,   244,   562,   563,   308,   264,   364,   570,
     572,   415,   574,   323,   384,   299,   575,   581,   159,   314,
    1277,  1278,  1279,   342,   587,   588,   326,   159,   259,   589,
     590,   591,   260,   261,   592,   265,   344,   593,   595,   596,
     608,   614,   615,   266,   159,   603,   378,   267,   268,   597,
     269,   270,   398,   133,   134,   271,   598,   599,   600,   616,
     306,   272,   273,   602,   601,   416,   604,   321,   274,   275,
     605,   606,   607,   621,   276,   609,   610,   622,   623,   611,
     277,   278,   279,   612,   280,   619,   281,   282,   625,   613,
     617,   618,   283,   620,   291,   626,   624,   292,   293,   627,
     628,   629,   630,   307,   634,   635,   631,   632,   636,   633,
     322,   637,   638,   639,   640,   406,   407,   408,   409,   410,
     411,   412,   413,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,   641,   160,   642,
     644,   235,   645,   643,   646,   647,   648,   649,   653,   654,
     656,   650,   651,   652,   657,   243,   658,   659,   662,   660,
     159,   663,   664,   667,   665,   666,   668,   669,   670,   671,
     673,   676,   678,   674,   677,   679,   922,   936,   946,   680,
     414,   682,   683,   684,   970,   685,   686,   687,   688,   690,
     924,   942,   947,   957,   415,   691,   692,   693,   801,   694,
     695,   696,   698,   703,   699,   704,   700,   707,   701,   244,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   709,   712,   706,   708,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   713,   710,   127,
     711,   715,   718,   719,   925,   943,   948,   958,   416,   721,
     716,   129,   130,   131,   720,   722,   723,   724,   725,   245,
     726,   246,   733,   734,   735,   736,   737,   133,   134,   247,
     248,   249,   250,   251,   135,   136,   137,   738,   739,   745,
      32,   748,   749,   750,   252,   751,   752,   753,   253,   754,
     143,   755,   756,   762,   757,   758,   759,   254,   760,   761,
     763,   764,   765,   766,   768,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   769,   775,
     770,   771,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   772,   127,   357,   774,   776,   777,   778,
     782,   783,   784,   785,   152,   153,   129,   130,   131,   786,
     800,   852,   787,   799,   788,   856,   860,   864,   868,   892,
     895,   899,   133,   134,   789,   248,   249,   790,   251,   135,
     136,   137,   966,   975,   159,   979,   335,   791,   993,   252,
     994,   995,   996,   253,   792,   794,   795,   997,   998,   999,
    1000,  1001,   254,  1002,  1004,  1005,  1015,   793,  1014,  1018,
    1017,  1020,  1021,  1023,  1024,  1027,  1026,  1083,  1042,  1030,
    1041,  1045,  1044,  1046,  1047,  1048,  1049,  1050,  1051,  1056,
    1057,  1058,  1061,  1062,  1063,  1070,  1072,  1080,  1088,  1098,
    1087,  1091,  1090,  1093,  1094,   255,  1095,  1092,   363,   152,
     153,   383,  1096,  1097,  1124,   256,  1099,   385,  1100,   298,
    1102,  1103,   377,   386,  1125,   397,  1178,  1101,  1166,   341,
    1108,   301,   401,   257,  1109,  1111,  1179,   258,   364,   159,
    1187,   384,  1126,   343,  1153,  1112,  1127,  1113,   922,  1104,
    1105,  1106,   262,   936,  1180,  1107,  1185,   946,  1181,   263,
     296,  1131,   924,  1114,  1172,   264,  1229,   942,  1132,  1165,
     970,   947,  1173,   299,  1133,   305,   378,   957,   320,   398,
    1231,  1186,  1167,  1110,   342,  1208,   259,   324,  1201,   313,
     260,   261,   325,   265,  1188,  1128,  1230,   344,  1209,  1129,
    1130,   266,  1134,  1202,  1203,   267,   268,  1182,   269,   270,
    1135,  1183,  1184,   271,  1136,  1137,   925,  1138,  1139,   272,
     273,   943,  1140,  1157,  1204,   948,   274,   275,  1141,  1142,
     308,   958,   276,   323,  1232,  1143,  1144,  1218,   277,   278,
     279,  1145,   280,   314,   281,   282,   326,  1146,  1147,  1148,
     283,  1149,   291,  1150,  1151,   292,   293,  1205,  1206,  1152,
    1219,  1159,  1222,  1214,  1160,  1161,  1158,  1210,  1211,  1224,
    1241,  1242,   878,  1307,  1212,  1264,  1272,  1265,  1273,  1274,
    1305,  1275,  1287,  1295,   306,  1296,  1221,   321,  1299,  1301,
    1327,  1328,  1329,  1215,  1333,  1337,   802,   804,   655,   661,
     985,  1117,  1115,  1174,  1170,  1171,  1200,  1217,  1199,   705,
    1207,  1118,  1119,   672,  1169,  1294,   355,  1216,   697,  1223,
    1251,  1252,  1239,  1300,  1121,  1253,  1258,   307,  1259,  1260,
     322,  1261,  1268,  1269,  1281,  1282,  1283,  1284,  1291,  1120,
    1303,  1123,  1297,  1304,  1306,  1334,  1335,  1122,  1336,  1339,
    1340,   702,  1244,  1243,  1246,  1124,   681,   675,  1245,  1197,
    1198,   983,  1196,  1178,  1298,  1125,  1220,   689,  1213,  1166,
    1225,  1302,   717,  1179,  1285,  1325,  1338,  1187,  1229,   714,
     965,  1240,  1238,  1126,   803,  1153,     0,  1127,     0,     0,
       0,  1180,  1231,  1185,     0,  1181,     0,     0,     0,     0,
       0,     0,  1131,     0,     0,     0,     0,     0,  1230,  1132,
    1165,     0,     0,     0,     0,  1133,     0,     0,  1186,     0,
       0,     0,     0,  1167,     0,     0,     0,     0,     0,     0,
       0,  1188,     0,     0,     0,     0,  1128,     0,     0,     0,
    1129,  1130,     0,  1134,  1182,     0,  1232,     0,  1183,  1184,
       0,  1135,     0,     0,     0,  1136,  1137,     0,  1138,  1139,
       0,     0,     0,  1140,  1157,     0,     0,     0,     0,  1141,
    1142,     0,     0,     0,     0,     0,  1143,  1144,     0,     0,
       0,     0,  1145,     0,     0,     0,     0,     0,  1146,  1147,
    1148,     0,  1149,     0,  1150,  1151,     0,     0,     0,     0,
    1152,     0,  1159,     0,     0,  1160,  1161,  1158
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   757,    73,    75,    79,    72,    73,    74,    75,    76,
      79,    78,    79,   724,    81,   751,  1025,  1025,    73,  1025,
      73,  1025,  1025,   134,    73,     0,   629,    78,    79,     5,
     215,     7,     3,     9,    79,     6,   140,   141,   200,    73,
      51,    52,    53,    54,    55,    56,    73,    73,    74,    75,
      76,     6,    73,   215,   108,   109,    24,    13,    14,    72,
      73,    74,    75,    76,    32,    78,    79,     7,    81,    80,
      81,   134,   135,    73,   137,   108,   109,    73,    73,     7,
      73,    16,    17,    18,    19,    20,     7,     3,    73,     3,
       6,    24,    73,    73,     8,    73,    73,   108,   109,    10,
      73,   704,    74,    75,   215,     3,    73,    73,     6,   163,
     164,   215,     7,    73,    73,   126,   127,   128,     7,    73,
       7,   181,   182,   183,   184,    73,    73,    73,     7,    73,
       7,    73,    73,   166,   167,   168,     7,    73,     7,    73,
     108,   109,    73,    73,     7,    74,    75,     3,    81,   669,
      83,    84,     8,     7,     3,    88,    89,    90,   218,     8,
       7,   215,   682,   683,   684,     3,     3,     3,    11,    12,
       8,     8,    15,   108,   109,   108,   109,     4,    21,    22,
      23,     3,   215,     8,     3,   153,   154,   155,   156,     8,
       4,     3,     3,   108,   109,   192,     8,     8,   195,   196,
     197,   198,     3,     3,   215,     4,     6,     8,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,     3,   215,
     216,   217,   218,     8,   159,   160,   161,   215,    91,    92,
      93,    94,     3,     8,     3,     6,    99,  1266,  1266,     8,
    1266,     4,  1266,  1266,     3,   108,   109,   140,   141,     8,
     178,   179,   115,   116,   117,   118,   119,   120,   121,     4,
     215,   124,   215,     4,    80,     3,     3,     3,   131,    81,
       8,     8,     8,     3,     3,  1031,   139,     4,     8,   142,
     215,     4,  1013,  1059,   122,   123,   149,   103,   104,   105,
     106,   107,   108,   109,   157,   158,   108,   109,     3,   162,
       3,     8,   165,     8,     4,     8,   169,     3,     3,   125,
       4,     4,     8,   129,   130,   143,   144,   145,   146,   147,
     148,     4,   185,   186,   187,   188,   189,   190,     4,     3,
       3,     8,    80,    24,     8,     8,   199,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,     4,   215,     4,    45,    46,    47,    48,    49,    50,
     108,   109,     4,     4,    81,    82,    83,    84,    85,    86,
      87,     4,    80,     3,     8,     3,   124,     4,     8,   191,
       8,   193,   194,     4,   132,   133,   134,   135,   136,   137,
      81,   108,   109,   101,   434,   435,     4,     3,     3,   215,
     108,   109,     8,   215,     3,   215,     3,     3,   509,     8,
       4,     8,     8,     3,     3,   516,     4,   125,     8,     8,
       3,   129,   130,     4,     4,     8,     4,   528,   216,   516,
       4,   532,    95,    96,    97,    98,     4,   528,   539,     4,
       4,   528,    42,    43,    44,   532,     4,   539,   549,    25,
      26,    27,   539,   528,     4,   528,     4,     4,   559,   528,
       4,     4,   549,     4,   565,     4,     4,   215,     4,     4,
     565,     4,   559,     4,   528,     4,   565,   578,   565,     4,
       4,   528,   528,   516,     4,     4,   532,   528,   559,     4,
       4,   578,     4,   539,   565,   528,     4,     4,   215,   532,
     150,   151,   152,   549,     4,     4,   539,   215,   528,     4,
       4,     4,   528,   528,     4,   528,   549,     4,   216,   216,
       4,     4,     4,   528,   215,   217,   559,   528,   528,   216,
     528,   528,   565,   108,   109,   528,   216,   216,   216,     4,
     532,   528,   528,   218,   216,   578,   217,   539,   528,   528,
     217,   216,   216,     4,   528,   216,   216,     4,     4,   218,
     528,   528,   528,   218,   528,   217,   528,   528,     4,   218,
     218,   218,   528,   218,   528,     4,   216,   528,   528,     4,
       4,     4,     4,   532,     4,     4,   218,   218,     4,   218,
     539,     4,     4,     4,     4,   170,   171,   172,   173,   174,
     175,   176,   177,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,     4,   719,     4,
       4,   722,     4,   216,     4,     4,     4,     4,     4,     4,
       4,   218,   218,   218,   218,   722,   218,   216,     4,   216,
     215,     4,     4,   216,     4,     4,   218,     4,     4,     4,
       4,     4,     4,   216,   216,   216,   757,   758,   759,   216,
     761,     4,     4,     4,   765,     4,     4,     4,     4,     4,
     757,   758,   759,   760,   761,     4,   216,     4,   718,     4,
       4,   218,     4,     4,   218,     4,   218,     4,   218,   722,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,     4,     4,   218,   216,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,     4,   216,    80,
     216,     4,     4,     7,   757,   758,   759,   760,   761,     7,
     216,    92,    93,    94,   215,     7,     7,     7,     5,   100,
     215,   102,   215,   215,     5,     5,     5,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   215,   215,     5,
       7,   215,     5,     5,   125,     5,     7,     5,   129,     5,
     131,     5,     7,   215,     7,     7,     7,   138,     7,     7,
     215,     5,     7,     5,     5,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,     5,     7,
     215,   215,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,   215,    80,    81,   215,   215,   215,   215,
     215,   215,   215,   215,   185,   186,    92,    93,    94,   215,
       5,     7,   215,   180,   215,     7,     7,     7,     7,     7,
       7,     7,   108,   109,   215,   111,   112,   215,   114,   115,
     116,   117,     7,     7,   215,     7,   132,   215,     4,   125,
       4,     4,     4,   129,   215,   215,   215,     4,     4,     4,
       4,     4,   138,     4,     4,     4,     3,   704,     6,     3,
       6,     6,     3,     6,     3,     3,     6,   215,     3,     6,
       6,     3,     6,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,   216,
       6,     3,     6,     6,     4,  1016,     4,     8,  1019,   185,
     186,  1022,     4,     4,  1025,  1016,   218,  1022,   216,  1016,
     216,   216,  1019,  1022,  1025,  1022,  1037,   218,  1025,  1040,
       4,  1016,  1043,  1016,   218,     4,  1037,  1016,  1019,   215,
    1037,  1022,  1025,  1040,  1025,     4,  1025,     4,  1059,   216,
     216,   216,  1016,  1064,  1037,   216,  1037,  1068,  1037,  1016,
    1016,  1025,  1059,     4,     4,  1016,  1077,  1064,  1025,  1025,
    1081,  1068,     4,  1016,  1025,  1086,  1019,  1074,  1089,  1022,
    1077,  1037,  1025,   216,  1040,     4,  1016,  1089,   216,  1086,
    1016,  1016,  1089,  1016,  1037,  1025,  1077,  1040,     4,  1025,
    1025,  1016,  1025,   216,   216,  1016,  1016,  1037,  1016,  1016,
    1025,  1037,  1037,  1016,  1025,  1025,  1059,  1025,  1025,  1016,
    1016,  1064,  1025,  1025,   216,  1068,  1016,  1016,  1025,  1025,
    1086,  1074,  1016,  1089,  1077,  1025,  1025,     4,  1016,  1016,
    1016,  1025,  1016,  1086,  1016,  1016,  1089,  1025,  1025,  1025,
    1016,  1025,  1016,  1025,  1025,  1016,  1016,   216,   216,  1025,
       4,  1025,     4,   218,  1025,  1025,  1025,   216,   216,     4,
       6,     3,   750,     7,   216,     8,     4,     8,     8,     3,
       5,     8,     4,     4,  1086,     4,   218,  1089,     4,     4,
       4,     4,     4,   216,     4,     4,   719,   722,   509,   516,
     800,  1015,  1010,  1035,  1028,  1031,  1045,  1064,  1043,   568,
    1052,  1016,  1018,   528,  1027,  1266,    77,   216,   559,   216,
     215,   215,   218,   216,  1021,   215,   215,  1086,   215,   215,
    1089,   215,   215,   215,   215,   215,   215,   215,   215,  1019,
     215,  1024,   218,   215,   215,   218,   216,  1022,   216,   215,
     215,   565,  1088,  1086,  1091,  1266,   539,   532,  1089,  1040,
    1042,   775,  1038,  1274,  1274,  1266,  1068,   549,  1059,  1266,
    1074,  1289,   582,  1274,  1224,  1311,  1331,  1274,  1289,   578,
     761,  1081,  1078,  1266,   721,  1266,    -1,  1266,    -1,    -1,
      -1,  1274,  1289,  1274,    -1,  1274,    -1,    -1,    -1,    -1,
      -1,    -1,  1266,    -1,    -1,    -1,    -1,    -1,  1289,  1266,
    1266,    -1,    -1,    -1,    -1,  1266,    -1,    -1,  1274,    -1,
      -1,    -1,    -1,  1266,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1274,    -1,    -1,    -1,    -1,  1266,    -1,    -1,    -1,
    1266,  1266,    -1,  1266,  1274,    -1,  1289,    -1,  1274,  1274,
      -1,  1266,    -1,    -1,    -1,  1266,  1266,    -1,  1266,  1266,
      -1,    -1,    -1,  1266,  1266,    -1,    -1,    -1,    -1,  1266,
    1266,    -1,    -1,    -1,    -1,    -1,  1266,  1266,    -1,    -1,
      -1,    -1,  1266,    -1,    -1,    -1,    -1,    -1,  1266,  1266,
    1266,    -1,  1266,    -1,  1266,  1266,    -1,    -1,    -1,    -1,
    1266,    -1,  1266,    -1,    -1,  1266,  1266,  1266
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
       0,     5,     7,     9,   215,   216,   217,   218,   235,   236,
     237,   242,     7,   251,     7,   256,     7,   311,     7,   426,
       7,   504,     7,   521,     7,   538,     7,   455,     7,   461,
       7,   485,     7,   402,     7,   607,     7,   626,   243,   238,
     252,   257,   312,   427,   505,   522,   539,   456,   462,   486,
     403,   608,   627,   235,   244,   245,   215,   240,   241,    10,
     253,   255,    11,    12,    15,    21,    22,    23,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    91,    92,
      93,    94,    99,   108,   109,   115,   116,   117,   118,   119,
     120,   121,   124,   131,   139,   142,   149,   157,   158,   162,
     165,   169,   185,   186,   187,   188,   189,   190,   199,   215,
     250,   258,   259,   260,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   282,   284,   286,   287,   288,   291,   292,   294,
     296,   297,   298,   299,   301,   302,   304,   306,   307,   308,
     309,   321,   323,   325,   367,   375,   381,   387,   389,   396,
     410,   420,   440,   441,   442,   445,   453,   479,   511,   513,
     532,   560,   574,   586,   587,   595,   605,   624,   633,   657,
      16,    17,    18,    19,    20,   250,   313,   314,   315,   317,
     318,   319,   320,   511,   513,   100,   102,   110,   111,   112,
     113,   114,   125,   129,   138,   250,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   276,
     277,   278,   279,   282,   284,   286,   287,   288,   291,   292,
     294,   296,   302,   304,   428,   429,   430,   432,   434,   436,
     438,   440,   441,   442,   443,   444,   479,   498,   511,   513,
     515,   532,   557,   101,   130,   250,   436,   438,   479,   506,
     507,   508,   510,   511,   513,   103,   104,   105,   106,   107,
     250,   436,   438,   479,   510,   511,   513,   523,   524,   525,
     527,   528,   530,   531,   124,   132,   133,   134,   135,   136,
     137,   250,   479,   511,   513,   540,   541,   542,   543,   545,
     547,   549,   551,   553,   555,   453,    24,    81,    83,    84,
      88,    89,    90,   250,   343,   463,   464,   465,   466,   467,
     468,   469,   471,   473,   475,   476,   478,   511,   513,    82,
      85,    86,    87,   250,   343,   467,   473,   487,   488,   489,
     490,   491,   493,   494,   495,   496,   497,   511,   513,   140,
     141,   250,   404,   405,   406,   408,   170,   171,   172,   173,
     174,   175,   176,   177,   250,   511,   513,   609,   610,   611,
     612,   614,   615,   617,   618,   619,   622,    13,    14,   628,
     629,   630,   632,     6,     3,     4,     8,     3,   254,     3,
       8,   261,   625,   310,   322,   324,   326,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   300,     4,     4,     4,     4,     4,   280,   283,   285,
       4,     4,     4,     4,   421,   454,   480,     4,   303,   305,
     289,   446,   512,   514,     4,     4,     4,   376,   388,   382,
     368,   561,   533,   397,   411,   575,     4,   390,   588,   596,
     606,   293,   295,     4,     4,     4,   634,   658,     4,     3,
       8,   316,     4,     4,     4,     4,     3,     8,   499,   516,
     431,   433,   435,     4,     4,   439,   437,   558,     3,     8,
     509,     4,     3,     8,   526,     4,   529,     4,     4,     3,
       8,   556,   544,   546,   548,   550,   552,   554,     8,     3,
       8,   470,   344,     4,   474,   472,   477,     4,     8,     3,
     492,     4,     4,     4,     8,     3,   407,   409,     3,     8,
       4,   613,     4,   616,     4,     4,   620,   623,     3,     8,
     631,     4,     3,     8,   235,   235,   215,     4,     4,     4,
       4,     4,     4,     4,   216,   216,   216,   216,   216,   216,
     216,   216,   218,   217,   217,   217,   216,   216,     4,   216,
     216,   218,   218,   218,     4,     4,     4,   218,   218,   217,
     218,     4,     4,     4,   216,     4,     4,     4,     4,     4,
       4,   218,   218,   218,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   216,     4,     4,     4,     4,     4,     4,
     218,   218,   218,     4,     4,   259,     4,   218,   218,   216,
     216,   314,     4,     4,     4,     4,     4,   216,   218,     4,
       4,     4,   429,     4,   216,   507,     4,   216,     4,   216,
     216,   524,     4,     4,     4,     4,     4,     4,     4,   542,
       4,     4,   216,     4,     4,     4,   218,   465,     4,   218,
     218,   218,   489,     4,     4,   405,   218,     4,   216,     4,
     216,   216,     4,     4,   610,     4,   216,   629,     4,     7,
     215,     7,     7,     7,     7,     5,   215,   181,   182,   183,
     184,   218,   281,   215,   215,     5,     5,     5,   215,   215,
      95,    96,    97,    98,   290,     5,   237,   239,   215,     5,
       5,     5,     7,     5,     5,     5,     7,     7,     7,     7,
       7,     7,   215,   215,     5,     7,     5,   246,     5,     5,
     215,   215,   215,   246,   215,     7,   215,   215,   215,   246,
     246,   246,   215,   215,   215,   215,   215,   215,   215,   215,
     215,   215,   215,   239,   215,   215,   178,   179,   621,   180,
       5,   235,   258,   628,   313,    24,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      45,    46,    47,    48,    49,    50,   250,   331,   332,   333,
     336,   338,   340,   342,   343,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   356,   357,   358,   359,   361,   363,
     365,   331,     7,   327,   328,   329,     7,   422,   423,   424,
       7,   457,   458,   459,     7,   481,   482,   483,     7,   447,
     448,   449,   134,   215,   377,   378,   379,   380,   244,   135,
     137,   379,   383,   384,   385,   386,   122,   123,   369,   370,
     371,   373,     7,   562,   563,     7,   534,   535,   536,     7,
     398,   399,   400,   143,   144,   145,   146,   147,   148,   412,
     413,   414,   415,   416,   417,   418,   419,    24,   153,   154,
     155,   156,   250,   345,   511,   513,   576,   577,   578,   581,
     582,   584,   585,   159,   160,   161,   250,   391,   392,   393,
     394,   395,   511,   513,   163,   164,   250,   511,   513,   589,
     590,   591,   593,   166,   167,   168,   215,   511,   513,   597,
     598,   599,   600,   602,   603,   609,     7,   635,   636,   200,
     250,   659,   660,   661,   247,     7,   500,   501,   502,     7,
     517,   518,   519,   543,   559,   327,     8,     8,     8,   334,
     337,   339,   341,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   354,     4,     4,   360,   362,   364,   366,
       3,     8,     8,   330,     6,     3,   425,     6,     3,   460,
       6,     3,   484,     6,     3,   450,     6,     3,     3,     6,
       6,     3,     6,   372,   374,     3,     8,   564,     3,     6,
     537,     6,     3,   401,     6,     3,     4,     4,     4,     4,
       4,     4,     3,     8,   579,   583,     4,     4,     4,     3,
       8,     4,     4,     4,     3,     8,   592,   594,     3,     8,
       4,   601,     4,   604,     3,     8,     8,   637,     3,     6,
       4,     3,     8,   215,   248,   249,   503,     6,     3,   520,
       6,     3,     8,     6,     4,     4,     4,     4,   216,   218,
     216,   218,   216,   216,   216,   216,   216,   216,     4,   218,
     216,     4,     4,     4,     4,   332,   331,   329,   428,   424,
     463,   459,   487,   483,   250,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   276,   277,
     278,   279,   282,   284,   286,   287,   288,   291,   292,   294,
     296,   302,   304,   343,   420,   432,   434,   436,   438,   440,
     441,   442,   444,   451,   452,   479,   511,   513,   557,   449,
     378,   384,     4,     4,   370,   126,   127,   128,   250,   262,
     263,   264,   265,   266,   267,   343,   479,   511,   513,   565,
     566,   567,   568,   569,   571,   573,   563,   540,   536,   404,
     400,   216,   216,   216,   216,   216,   216,   413,     4,     4,
     216,   216,   216,   577,   218,   216,   216,   392,     4,     4,
     590,   218,     4,   216,     4,   598,   191,   193,   194,   250,
     343,   511,   513,   638,   639,   640,   641,   643,   636,   218,
     660,     6,     3,   506,   502,   523,   519,    25,    26,    27,
     335,   215,   215,   215,    42,    43,    44,   355,   215,   215,
     215,   215,     8,     8,     8,     8,     3,     8,   215,   215,
     570,   572,     4,     8,     3,     8,     8,   150,   151,   152,
     580,   215,   215,   215,   215,   235,   644,     4,   642,     3,
       8,   215,     8,     8,   452,     4,     4,   218,   567,     4,
     216,     4,   639,   215,   215,     5,   215,     7,   645,   646,
     647,     3,     6,   192,   195,   196,   197,   198,   648,   649,
     650,   652,   653,   654,   655,   646,   651,     4,     4,     4,
     656,     3,     8,     4,   218,   216,   216,     4,   649,   215,
     215
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   219,   221,   220,   222,   220,   223,   220,   224,   220,
     225,   220,   226,   220,   227,   220,   228,   220,   229,   220,
     230,   220,   231,   220,   232,   220,   233,   220,   234,   220,
     235,   235,   235,   235,   235,   235,   235,   236,   238,   237,
     239,   240,   240,   241,   241,   241,   243,   242,   244,   244,
     245,   245,   245,   247,   246,   248,   248,   249,   249,   249,
     250,   252,   251,   254,   253,   253,   255,   257,   256,   258,
     258,   258,   259,   259,   259,   259,   259,   259,   259,   259,
     259,   259,   259,   259,   259,   259,   259,   259,   259,   259,
     259,   259,   259,   259,   259,   259,   259,   259,   259,   259,
     259,   259,   259,   259,   259,   259,   259,   259,   259,   259,
     259,   259,   259,   259,   259,   259,   259,   259,   259,   259,
     259,   259,   259,   259,   259,   259,   259,   259,   259,   259,
     259,   259,   259,   259,   259,   259,   259,   259,   259,   259,
     261,   260,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   280,
     279,   281,   281,   281,   281,   281,   283,   282,   285,   284,
     286,   287,   289,   288,   290,   290,   290,   290,   291,   293,
     292,   295,   294,   296,   297,   298,   300,   299,   301,   303,
     302,   305,   304,   306,   307,   308,   310,   309,   312,   311,
     313,   313,   313,   314,   314,   314,   314,   314,   314,   314,
     314,   316,   315,   317,   318,   319,   320,   322,   321,   324,
     323,   326,   325,   327,   327,   328,   328,   328,   330,   329,
     331,   331,   331,   332,   332,   332,   332,   332,   332,   332,
     332,   332,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   332,   332,   332,   332,   332,   334,   333,   335,   335,
     335,   337,   336,   339,   338,   341,   340,   342,   344,   343,
     345,   346,   347,   348,   349,   350,   351,   352,   354,   353,
     355,   355,   355,   356,   357,   358,   360,   359,   362,   361,
     364,   363,   366,   365,   368,   367,   369,   369,   369,   370,
     370,   372,   371,   374,   373,   376,   375,   377,   377,   377,
     378,   378,   379,   380,   382,   381,   383,   383,   383,   384,
     384,   384,   385,   386,   388,   387,   390,   389,   391,   391,
     391,   392,   392,   392,   392,   392,   392,   393,   394,   395,
     397,   396,   398,   398,   399,   399,   399,   401,   400,   403,
     402,   404,   404,   404,   404,   405,   405,   407,   406,   409,
     408,   411,   410,   412,   412,   412,   413,   413,   413,   413,
     413,   413,   414,   415,   416,   417,   418,   419,   421,   420,
     422,   422,   423,   423,   423,   425,   424,   427,   426,   428,
     428,   428,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   429,   429,   431,   430,
     433,   432,   435,   434,   437,   436,   439,   438,   440,   441,
     442,   443,   444,   446,   445,   447,   447,   448,   448,   448,
     450,   449,   451,   451,   451,   452,   452,   452,   452,   452,
     452,   452,   452,   452,   452,   452,   452,   452,   452,   452,
     452,   452,   452,   452,   452,   452,   452,   452,   452,   452,
     452,   452,   452,   452,   452,   452,   452,   452,   452,   452,
     452,   452,   452,   452,   452,   452,   452,   452,   454,   453,
     456,   455,   457,   457,   458,   458,   458,   460,   459,   462,
     461,   463,   463,   464,   464,   464,   465,   465,   465,   465,
     465,   465,   465,   465,   465,   465,   466,   467,   468,   470,
     469,   472,   471,   474,   473,   475,   477,   476,   478,   480,
     479,   481,   481,   482,   482,   482,   484,   483,   486,   485,
     487,   487,   488,   488,   488,   489,   489,   489,   489,   489,
     489,   489,   489,   489,   489,   490,   492,   491,   493,   494,
     495,   496,   497,   499,   498,   500,   500,   501,   501,   501,
     503,   502,   505,   504,   506,   506,   506,   507,   507,   507,
     507,   507,   507,   507,   507,   509,   508,   510,   512,   511,
     514,   513,   516,   515,   517,   517,   518,   518,   518,   520,
     519,   522,   521,   523,   523,   523,   524,   524,   524,   524,
     524,   524,   524,   524,   524,   524,   524,   524,   526,   525,
     527,   529,   528,   530,   531,   533,   532,   534,   534,   535,
     535,   535,   537,   536,   539,   538,   540,   540,   541,   541,
     541,   542,   542,   542,   542,   542,   542,   542,   542,   542,
     542,   542,   544,   543,   546,   545,   548,   547,   550,   549,
     552,   551,   554,   553,   556,   555,   558,   557,   559,   561,
     560,   562,   562,   562,   564,   563,   565,   565,   566,   566,
     566,   567,   567,   567,   567,   567,   567,   567,   567,   567,
     567,   567,   567,   567,   567,   568,   570,   569,   572,   571,
     573,   575,   574,   576,   576,   576,   577,   577,   577,   577,
     577,   577,   577,   577,   577,   579,   578,   580,   580,   580,
     581,   583,   582,   584,   585,   586,   588,   587,   589,   589,
     589,   590,   590,   590,   590,   590,   592,   591,   594,   593,
     596,   595,   597,   597,   597,   598,   598,   598,   598,   598,
     598,   599,   601,   600,   602,   604,   603,   606,   605,   608,
     607,   609,   609,   609,   610,   610,   610,   610,   610,   610,
     610,   610,   610,   610,   610,   611,   613,   612,   614,   616,
     615,   617,   618,   620,   619,   621,   621,   623,   622,   625,
     624,   627,   626,   628,   628,   628,   629,   629,   631,   630,
     632,   634,   633,   635,   635,   635,   637,   636,   638,   638,
     638,   639,   639,   639,   639,   639,   639,   639,   640,   642,
     641,   644,   643,   645,   645,   645,   647,   646,   648,   648,
     648,   649,   649,   649,   649,   649,   651,   650,   652,   653,
     654,   656,   655,   658,   657,   659,   659,   659,   660,   660,
     661
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
       0,     4,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     0,
       4,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       3,     3,     0,     4,     1,     1,     1,     1,     3,     0,
       4,     0,     4,     3,     3,     3,     0,     4,     3,     0,
       4,     0,     4,     3,     3,     3,     0,     6,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     3,     3,     3,     0,     6,     0,
       6,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     3,     3,     3,     3,     3,     3,     0,     4,
       1,     1,     1,     3,     3,     3,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     1,     3,     2,     1,
       1,     0,     4,     0,     4,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     0,     6,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     1,     3,     2,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     3,     3,
       3,     3,     3,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     6,
       0,     4,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     0,     1,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     0,
       4,     0,     4,     0,     4,     1,     0,     4,     3,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     0,     4,
       0,     1,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       3,     3,     3,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     4,
       0,     4,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     4,     3,     3,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     0,     1,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     1,     0,
       6,     1,     3,     2,     0,     4,     0,     1,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       3,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       3,     0,     4,     3,     3,     3,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     3,     0,     4,     0,     6,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     3,     0,
       4,     3,     3,     0,     4,     1,     1,     0,     4,     0,
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
  "\"interface-id\"", "\"id\"", "\"rapid-commit\"",
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
  "reservations_in_subnet", "reservations_out_of_pool", "id",
  "rapid_commit", "shared_networks", "$@69", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@70",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@71", "sub_option_def_list", "$@72", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@73",
  "sub_option_def", "$@74", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@75",
  "option_def_record_types", "$@76", "space", "$@77", "option_def_space",
  "option_def_encapsulate", "$@78", "option_def_array", "option_data_list",
  "$@79", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@80", "sub_option_data", "$@81",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@82",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "option_data_never_send", "pools_list",
  "$@83", "pools_list_content", "not_empty_pools_list", "pool_list_entry",
  "$@84", "sub_pool6", "$@85", "pool_params", "pool_param", "pool_entry",
  "$@86", "pool_id", "user_context", "$@87", "comment", "$@88",
  "pd_pools_list", "$@89", "pd_pools_list_content",
  "not_empty_pd_pools_list", "pd_pool_entry", "$@90", "sub_pd_pool",
  "$@91", "pd_pool_params", "pd_pool_param", "pd_prefix", "$@92",
  "pd_prefix_len", "excluded_prefix", "$@93", "excluded_prefix_len",
  "pd_delegated_len", "reservations", "$@94", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@95", "sub_reservation",
  "$@96", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "ip_addresses", "$@97", "prefixes", "$@98", "duid",
  "$@99", "hw_address", "$@100", "hostname", "$@101", "flex_id_value",
  "$@102", "reservation_client_classes", "$@103", "relay", "$@104",
  "relay_map", "client_classes", "$@105", "client_classes_list",
  "client_class_entry", "$@106", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@107",
  "client_class_template_test", "$@108", "only_if_required", "server_id",
  "$@109", "server_id_params", "server_id_param", "server_id_type",
  "$@110", "duid_type", "htype", "identifier", "$@111", "time",
  "enterprise_id", "dhcp4o6_port", "control_socket", "$@112",
  "control_socket_params", "control_socket_param", "socket_type", "$@113",
  "socket_name", "$@114", "dhcp_queue_control", "$@115",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@116", "capacity", "arbitrary_map_entry", "$@117",
  "dhcp_ddns", "$@118", "sub_dhcp_ddns", "$@119", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@120", "server_port",
  "sender_ip", "$@121", "sender_port", "max_queue_size", "ncr_protocol",
  "$@122", "ncr_protocol_value", "ncr_format", "$@123", "config_control",
  "$@124", "sub_config_control", "$@125", "config_control_params",
  "config_control_param", "config_databases", "$@126",
  "config_fetch_wait_time", "loggers", "$@127", "loggers_entries",
  "logger_entry", "$@128", "logger_params", "logger_param", "debuglevel",
  "severity", "$@129", "output_options_list", "$@130",
  "output_options_list_content", "output_entry", "$@131",
  "output_params_list", "output_params", "output", "$@132", "flush",
  "maxsize", "maxver", "pattern", "$@133", "compatibility", "$@134",
  "compatibility_params", "compatibility_param", "lenient_option_parsing", YY_NULLPTR
  };
#endif


#if PARSER6_DEBUG
  const short
  Dhcp6Parser::yyrline_[] =
  {
       0,   312,   312,   312,   313,   313,   314,   314,   315,   315,
     316,   316,   317,   317,   318,   318,   319,   319,   320,   320,
     321,   321,   322,   322,   323,   323,   324,   324,   325,   325,
     333,   334,   335,   336,   337,   338,   339,   342,   347,   347,
     358,   361,   362,   365,   370,   376,   381,   381,   388,   389,
     392,   396,   400,   406,   406,   413,   414,   417,   421,   425,
     435,   444,   444,   459,   459,   473,   476,   482,   482,   491,
     492,   493,   500,   501,   502,   503,   504,   505,   506,   507,
     508,   509,   510,   511,   512,   513,   514,   515,   516,   517,
     518,   519,   520,   521,   522,   523,   524,   525,   526,   527,
     528,   529,   530,   531,   532,   533,   534,   535,   536,   537,
     538,   539,   540,   541,   542,   543,   544,   545,   546,   547,
     548,   549,   550,   551,   552,   553,   554,   555,   556,   557,
     558,   559,   560,   561,   562,   563,   564,   565,   566,   567,
     570,   570,   579,   585,   591,   597,   603,   609,   615,   621,
     627,   633,   639,   645,   651,   657,   663,   669,   675,   681,
     681,   690,   693,   696,   699,   702,   708,   708,   717,   717,
     726,   735,   745,   745,   754,   757,   760,   763,   768,   774,
     774,   783,   783,   792,   798,   804,   810,   810,   819,   825,
     825,   834,   834,   843,   849,   855,   861,   861,   873,   873,
     882,   883,   884,   889,   890,   891,   892,   893,   894,   895,
     896,   899,   899,   910,   916,   922,   928,   934,   934,   947,
     947,   960,   960,   971,   972,   975,   976,   977,   982,   982,
     992,   993,   994,   999,  1000,  1001,  1002,  1003,  1004,  1005,
    1006,  1007,  1008,  1009,  1010,  1011,  1012,  1013,  1014,  1015,
    1016,  1017,  1018,  1019,  1020,  1021,  1024,  1024,  1032,  1033,
    1034,  1037,  1037,  1046,  1046,  1055,  1055,  1064,  1070,  1070,
    1079,  1085,  1091,  1097,  1103,  1109,  1115,  1122,  1128,  1128,
    1136,  1137,  1138,  1141,  1147,  1153,  1159,  1159,  1168,  1168,
    1177,  1177,  1186,  1186,  1195,  1195,  1206,  1207,  1208,  1213,
    1214,  1217,  1217,  1236,  1236,  1254,  1254,  1265,  1266,  1267,
    1272,  1273,  1276,  1281,  1286,  1286,  1297,  1298,  1299,  1304,
    1305,  1306,  1309,  1314,  1321,  1321,  1334,  1334,  1347,  1348,
    1349,  1354,  1355,  1356,  1357,  1358,  1359,  1362,  1368,  1374,
    1380,  1380,  1391,  1392,  1395,  1396,  1397,  1402,  1402,  1412,
    1412,  1422,  1423,  1424,  1427,  1430,  1431,  1434,  1434,  1443,
    1443,  1452,  1452,  1464,  1465,  1466,  1471,  1472,  1473,  1474,
    1475,  1476,  1479,  1485,  1491,  1497,  1503,  1509,  1518,  1518,
    1532,  1533,  1536,  1537,  1538,  1547,  1547,  1573,  1573,  1584,
    1585,  1586,  1592,  1593,  1594,  1595,  1596,  1597,  1598,  1599,
    1600,  1601,  1602,  1603,  1604,  1605,  1606,  1607,  1608,  1609,
    1610,  1611,  1612,  1613,  1614,  1615,  1616,  1617,  1618,  1619,
    1620,  1621,  1622,  1623,  1624,  1625,  1626,  1627,  1628,  1629,
    1630,  1631,  1632,  1633,  1634,  1635,  1636,  1637,  1640,  1640,
    1649,  1649,  1658,  1658,  1667,  1667,  1676,  1676,  1687,  1693,
    1699,  1705,  1711,  1719,  1719,  1731,  1732,  1736,  1737,  1738,
    1743,  1743,  1751,  1752,  1753,  1758,  1759,  1760,  1761,  1762,
    1763,  1764,  1765,  1766,  1767,  1768,  1769,  1770,  1771,  1772,
    1773,  1774,  1775,  1776,  1777,  1778,  1779,  1780,  1781,  1782,
    1783,  1784,  1785,  1786,  1787,  1788,  1789,  1790,  1791,  1792,
    1793,  1794,  1795,  1796,  1797,  1798,  1799,  1800,  1807,  1807,
    1821,  1821,  1830,  1831,  1834,  1835,  1836,  1843,  1843,  1858,
    1858,  1872,  1873,  1876,  1877,  1878,  1883,  1884,  1885,  1886,
    1887,  1888,  1889,  1890,  1891,  1892,  1895,  1897,  1903,  1905,
    1905,  1914,  1914,  1923,  1923,  1932,  1934,  1934,  1943,  1953,
    1953,  1966,  1967,  1972,  1973,  1974,  1981,  1981,  1993,  1993,
    2005,  2006,  2011,  2012,  2013,  2020,  2021,  2022,  2023,  2024,
    2025,  2026,  2027,  2028,  2029,  2032,  2034,  2034,  2043,  2045,
    2047,  2053,  2059,  2068,  2068,  2081,  2082,  2085,  2086,  2087,
    2092,  2092,  2102,  2102,  2112,  2113,  2114,  2119,  2120,  2121,
    2122,  2123,  2124,  2125,  2126,  2129,  2129,  2138,  2144,  2144,
    2169,  2169,  2199,  2199,  2212,  2213,  2216,  2217,  2218,  2223,
    2223,  2235,  2235,  2247,  2248,  2249,  2254,  2255,  2256,  2257,
    2258,  2259,  2260,  2261,  2262,  2263,  2264,  2265,  2268,  2268,
    2277,  2283,  2283,  2292,  2298,  2307,  2307,  2318,  2319,  2322,
    2323,  2324,  2329,  2329,  2338,  2338,  2347,  2348,  2351,  2352,
    2353,  2359,  2360,  2361,  2362,  2363,  2364,  2365,  2366,  2367,
    2368,  2369,  2372,  2372,  2383,  2383,  2394,  2394,  2403,  2403,
    2412,  2412,  2421,  2421,  2430,  2430,  2444,  2444,  2455,  2461,
    2461,  2472,  2473,  2474,  2479,  2479,  2489,  2490,  2493,  2494,
    2495,  2500,  2501,  2502,  2503,  2504,  2505,  2506,  2507,  2508,
    2509,  2510,  2511,  2512,  2513,  2516,  2518,  2518,  2527,  2527,
    2536,  2545,  2545,  2558,  2559,  2560,  2565,  2566,  2567,  2568,
    2569,  2570,  2571,  2572,  2573,  2576,  2576,  2584,  2585,  2586,
    2589,  2595,  2595,  2604,  2610,  2618,  2626,  2626,  2637,  2638,
    2639,  2644,  2645,  2646,  2647,  2648,  2651,  2651,  2660,  2660,
    2672,  2672,  2685,  2686,  2687,  2692,  2693,  2694,  2695,  2696,
    2697,  2700,  2706,  2706,  2715,  2721,  2721,  2731,  2731,  2744,
    2744,  2754,  2755,  2756,  2761,  2762,  2763,  2764,  2765,  2766,
    2767,  2768,  2769,  2770,  2771,  2774,  2780,  2780,  2789,  2795,
    2795,  2804,  2810,  2816,  2816,  2825,  2826,  2829,  2829,  2840,
    2840,  2852,  2852,  2862,  2863,  2864,  2870,  2871,  2874,  2874,
    2885,  2893,  2893,  2906,  2907,  2908,  2914,  2914,  2922,  2923,
    2924,  2929,  2930,  2931,  2932,  2933,  2934,  2935,  2938,  2944,
    2944,  2953,  2953,  2964,  2965,  2966,  2971,  2971,  2979,  2980,
    2981,  2986,  2987,  2988,  2989,  2990,  2993,  2993,  3002,  3008,
    3014,  3020,  3020,  3029,  3029,  3040,  3041,  3042,  3047,  3048,
    3051
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
#line 6408 "dhcp6_parser.cc"

#line 3057 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
