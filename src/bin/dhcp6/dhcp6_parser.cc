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
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
      case symbol_kind::S_auth_type_value: // auth_type_value
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
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
      case symbol_kind::S_auth_type_value: // auth_type_value
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
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
      case symbol_kind::S_auth_type_value: // auth_type_value
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
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
      case symbol_kind::S_auth_type_value: // auth_type_value
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
#line 318 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 413 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 318 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 419 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 318 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 425 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 318 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 431 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 318 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 437 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 318 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 443 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 318 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 449 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 318 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 455 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 318 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 461 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 318 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 467 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
#line 318 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 473 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 318 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 479 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 318 "dhcp6_parser.yy"
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
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
      case symbol_kind::S_auth_type_value: // auth_type_value
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
#line 327 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 766 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 328 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 772 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 329 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 778 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 330 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 784 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 331 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 790 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 332 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 796 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 333 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 802 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 334 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 808 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 335 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 814 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 336 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 820 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 337 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 826 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 338 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 832 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 339 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 838 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 340 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 844 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 348 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 850 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 349 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 856 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 350 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 862 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 351 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 868 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 352 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 874 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 353 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 880 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 354 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 886 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 357 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 895 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 362 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 906 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 367 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 916 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 373 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 922 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 380 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 932 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 385 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 943 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 391 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 951 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 396 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 960 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 399 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 968 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 407 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 977 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 411 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 986 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 415 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 994 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 421 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 1002 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 423 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1011 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 432 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1020 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 436 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1029 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 440 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1037 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 450 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1048 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 459 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1059 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 464 "dhcp6_parser.yy"
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
#line 474 "dhcp6_parser.yy"
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
#line 483 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1097 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 491 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1105 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 497 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1115 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 501 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1124 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 508 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1132 "dhcp6_parser.cc"
    break;

  case 141: // $@21: %empty
#line 586 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1141 "dhcp6_parser.cc"
    break;

  case 142: // data_directory: "data-directory" $@21 ":" "constant string"
#line 589 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1151 "dhcp6_parser.cc"
    break;

  case 143: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 595 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1161 "dhcp6_parser.cc"
    break;

  case 144: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 601 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1171 "dhcp6_parser.cc"
    break;

  case 145: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 607 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1181 "dhcp6_parser.cc"
    break;

  case 146: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 613 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1191 "dhcp6_parser.cc"
    break;

  case 147: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 619 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1201 "dhcp6_parser.cc"
    break;

  case 148: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 625 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1211 "dhcp6_parser.cc"
    break;

  case 149: // renew_timer: "renew-timer" ":" "integer"
#line 631 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1221 "dhcp6_parser.cc"
    break;

  case 150: // rebind_timer: "rebind-timer" ":" "integer"
#line 637 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1231 "dhcp6_parser.cc"
    break;

  case 151: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 643 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1241 "dhcp6_parser.cc"
    break;

  case 152: // t1_percent: "t1-percent" ":" "floating point"
#line 649 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1251 "dhcp6_parser.cc"
    break;

  case 153: // t2_percent: "t2-percent" ":" "floating point"
#line 655 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1261 "dhcp6_parser.cc"
    break;

  case 154: // cache_threshold: "cache-threshold" ":" "floating point"
#line 661 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1271 "dhcp6_parser.cc"
    break;

  case 155: // cache_max_age: "cache-max-age" ":" "integer"
#line 667 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1281 "dhcp6_parser.cc"
    break;

  case 156: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 673 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1291 "dhcp6_parser.cc"
    break;

  case 157: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 679 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1301 "dhcp6_parser.cc"
    break;

  case 158: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 685 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1311 "dhcp6_parser.cc"
    break;

  case 159: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 691 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1321 "dhcp6_parser.cc"
    break;

  case 160: // $@22: %empty
#line 697 "dhcp6_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1330 "dhcp6_parser.cc"
    break;

  case 161: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 700 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1339 "dhcp6_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "when-present"
#line 706 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1347 "dhcp6_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "never"
#line 709 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1355 "dhcp6_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "always"
#line 712 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1363 "dhcp6_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "when-not-present"
#line 715 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1371 "dhcp6_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "boolean"
#line 718 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1380 "dhcp6_parser.cc"
    break;

  case 167: // $@23: %empty
#line 724 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1389 "dhcp6_parser.cc"
    break;

  case 168: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 727 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1399 "dhcp6_parser.cc"
    break;

  case 169: // $@24: %empty
#line 733 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1408 "dhcp6_parser.cc"
    break;

  case 170: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 736 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1418 "dhcp6_parser.cc"
    break;

  case 171: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 742 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1428 "dhcp6_parser.cc"
    break;

  case 172: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 751 "dhcp6_parser.yy"
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
#line 761 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1451 "dhcp6_parser.cc"
    break;

  case 174: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 764 "dhcp6_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 175: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 770 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1468 "dhcp6_parser.cc"
    break;

  case 176: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 773 "dhcp6_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1476 "dhcp6_parser.cc"
    break;

  case 177: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 776 "dhcp6_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1484 "dhcp6_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 779 "dhcp6_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1492 "dhcp6_parser.cc"
    break;

  case 179: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 784 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1502 "dhcp6_parser.cc"
    break;

  case 180: // $@26: %empty
#line 790 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1511 "dhcp6_parser.cc"
    break;

  case 181: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 793 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1521 "dhcp6_parser.cc"
    break;

  case 182: // $@27: %empty
#line 799 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1530 "dhcp6_parser.cc"
    break;

  case 183: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 802 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1540 "dhcp6_parser.cc"
    break;

  case 184: // store_extended_info: "store-extended-info" ":" "boolean"
#line 808 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1550 "dhcp6_parser.cc"
    break;

  case 185: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 814 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1560 "dhcp6_parser.cc"
    break;

  case 186: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 820 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1570 "dhcp6_parser.cc"
    break;

  case 187: // $@28: %empty
#line 826 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1579 "dhcp6_parser.cc"
    break;

  case 188: // server_tag: "server-tag" $@28 ":" "constant string"
#line 829 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1589 "dhcp6_parser.cc"
    break;

  case 189: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 835 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1599 "dhcp6_parser.cc"
    break;

  case 190: // $@29: %empty
#line 841 "dhcp6_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1608 "dhcp6_parser.cc"
    break;

  case 191: // allocator: "allocator" $@29 ":" "constant string"
#line 844 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1618 "dhcp6_parser.cc"
    break;

  case 192: // $@30: %empty
#line 850 "dhcp6_parser.yy"
                           {
    ctx.unique("pd-allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1627 "dhcp6_parser.cc"
    break;

  case 193: // pd_allocator: "pd-allocator" $@30 ":" "constant string"
#line 853 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-allocator", al);
    ctx.leave();
}
#line 1637 "dhcp6_parser.cc"
    break;

  case 194: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 859 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1647 "dhcp6_parser.cc"
    break;

  case 195: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 865 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1657 "dhcp6_parser.cc"
    break;

  case 196: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 871 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1667 "dhcp6_parser.cc"
    break;

  case 197: // $@31: %empty
#line 877 "dhcp6_parser.yy"
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
#line 883 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1689 "dhcp6_parser.cc"
    break;

  case 199: // $@32: %empty
#line 889 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1699 "dhcp6_parser.cc"
    break;

  case 200: // sub_interfaces6: "{" $@32 interfaces_config_params "}"
#line 893 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1708 "dhcp6_parser.cc"
    break;

  case 203: // interfaces_config_params: interfaces_config_params ","
#line 900 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1716 "dhcp6_parser.cc"
    break;

  case 212: // $@33: %empty
#line 915 "dhcp6_parser.yy"
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
#line 921 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1737 "dhcp6_parser.cc"
    break;

  case 214: // re_detect: "re-detect" ":" "boolean"
#line 926 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1747 "dhcp6_parser.cc"
    break;

  case 215: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 932 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1757 "dhcp6_parser.cc"
    break;

  case 216: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 938 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1767 "dhcp6_parser.cc"
    break;

  case 217: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 944 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1777 "dhcp6_parser.cc"
    break;

  case 218: // $@34: %empty
#line 950 "dhcp6_parser.yy"
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
#line 956 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1800 "dhcp6_parser.cc"
    break;

  case 220: // $@35: %empty
#line 963 "dhcp6_parser.yy"
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
#line 969 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1823 "dhcp6_parser.cc"
    break;

  case 222: // $@36: %empty
#line 976 "dhcp6_parser.yy"
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
#line 982 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1844 "dhcp6_parser.cc"
    break;

  case 228: // not_empty_database_list: not_empty_database_list ","
#line 993 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1852 "dhcp6_parser.cc"
    break;

  case 229: // $@37: %empty
#line 998 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1862 "dhcp6_parser.cc"
    break;

  case 230: // database: "{" $@37 database_map_params "}"
#line 1002 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1872 "dhcp6_parser.cc"
    break;

  case 233: // database_map_params: database_map_params ","
#line 1010 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1880 "dhcp6_parser.cc"
    break;

  case 257: // $@38: %empty
#line 1040 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1889 "dhcp6_parser.cc"
    break;

  case 258: // database_type: "type" $@38 ":" "constant string"
#line 1043 "dhcp6_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 1899 "dhcp6_parser.cc"
    break;

  case 259: // $@39: %empty
#line 1049 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1908 "dhcp6_parser.cc"
    break;

  case 260: // user: "user" $@39 ":" "constant string"
#line 1052 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1918 "dhcp6_parser.cc"
    break;

  case 261: // $@40: %empty
#line 1058 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1927 "dhcp6_parser.cc"
    break;

  case 262: // password: "password" $@40 ":" "constant string"
#line 1061 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1937 "dhcp6_parser.cc"
    break;

  case 263: // $@41: %empty
#line 1067 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1946 "dhcp6_parser.cc"
    break;

  case 264: // host: "host" $@41 ":" "constant string"
#line 1070 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1956 "dhcp6_parser.cc"
    break;

  case 265: // port: "port" ":" "integer"
#line 1076 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1966 "dhcp6_parser.cc"
    break;

  case 266: // $@42: %empty
#line 1082 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1975 "dhcp6_parser.cc"
    break;

  case 267: // name: "name" $@42 ":" "constant string"
#line 1085 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1985 "dhcp6_parser.cc"
    break;

  case 268: // persist: "persist" ":" "boolean"
#line 1091 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1995 "dhcp6_parser.cc"
    break;

  case 269: // lfc_interval: "lfc-interval" ":" "integer"
#line 1097 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2005 "dhcp6_parser.cc"
    break;

  case 270: // readonly: "readonly" ":" "boolean"
#line 1103 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2015 "dhcp6_parser.cc"
    break;

  case 271: // connect_timeout: "connect-timeout" ":" "integer"
#line 1109 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2025 "dhcp6_parser.cc"
    break;

  case 272: // read_timeout: "read-timeout" ":" "integer"
#line 1115 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2035 "dhcp6_parser.cc"
    break;

  case 273: // write_timeout: "write-timeout" ":" "integer"
#line 1121 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2045 "dhcp6_parser.cc"
    break;

  case 274: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1127 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2055 "dhcp6_parser.cc"
    break;

  case 275: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1133 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2065 "dhcp6_parser.cc"
    break;

  case 276: // $@43: %empty
#line 1139 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2074 "dhcp6_parser.cc"
    break;

  case 277: // on_fail: "on-fail" $@43 ":" on_fail_mode
#line 1142 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2083 "dhcp6_parser.cc"
    break;

  case 278: // on_fail_mode: "stop-retry-exit"
#line 1147 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2089 "dhcp6_parser.cc"
    break;

  case 279: // on_fail_mode: "serve-retry-exit"
#line 1148 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2095 "dhcp6_parser.cc"
    break;

  case 280: // on_fail_mode: "serve-retry-continue"
#line 1149 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2101 "dhcp6_parser.cc"
    break;

  case 281: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1152 "dhcp6_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2111 "dhcp6_parser.cc"
    break;

  case 282: // max_row_errors: "max-row-errors" ":" "integer"
#line 1158 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2121 "dhcp6_parser.cc"
    break;

  case 283: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1164 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2131 "dhcp6_parser.cc"
    break;

  case 284: // $@44: %empty
#line 1170 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2140 "dhcp6_parser.cc"
    break;

  case 285: // trust_anchor: "trust-anchor" $@44 ":" "constant string"
#line 1173 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2150 "dhcp6_parser.cc"
    break;

  case 286: // $@45: %empty
#line 1179 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2159 "dhcp6_parser.cc"
    break;

  case 287: // cert_file: "cert-file" $@45 ":" "constant string"
#line 1182 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2169 "dhcp6_parser.cc"
    break;

  case 288: // $@46: %empty
#line 1188 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2178 "dhcp6_parser.cc"
    break;

  case 289: // key_file: "key-file" $@46 ":" "constant string"
#line 1191 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2188 "dhcp6_parser.cc"
    break;

  case 290: // $@47: %empty
#line 1197 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2197 "dhcp6_parser.cc"
    break;

  case 291: // cipher_list: "cipher-list" $@47 ":" "constant string"
#line 1200 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2207 "dhcp6_parser.cc"
    break;

  case 292: // $@48: %empty
#line 1206 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2219 "dhcp6_parser.cc"
    break;

  case 293: // sanity_checks: "sanity-checks" $@48 ":" "{" sanity_checks_params "}"
#line 1212 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2228 "dhcp6_parser.cc"
    break;

  case 296: // sanity_checks_params: sanity_checks_params ","
#line 1219 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2236 "dhcp6_parser.cc"
    break;

  case 299: // $@49: %empty
#line 1228 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2245 "dhcp6_parser.cc"
    break;

  case 300: // lease_checks: "lease-checks" $@49 ":" "constant string"
#line 1231 "dhcp6_parser.yy"
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
#line 2265 "dhcp6_parser.cc"
    break;

  case 301: // $@50: %empty
#line 1247 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2274 "dhcp6_parser.cc"
    break;

  case 302: // extended_info_checks: "extended-info-checks" $@50 ":" "constant string"
#line 1250 "dhcp6_parser.yy"
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
#line 2293 "dhcp6_parser.cc"
    break;

  case 303: // $@51: %empty
#line 1265 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2305 "dhcp6_parser.cc"
    break;

  case 304: // mac_sources: "mac-sources" $@51 ":" "[" mac_sources_list "]"
#line 1271 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2314 "dhcp6_parser.cc"
    break;

  case 307: // mac_sources_list: mac_sources_list ","
#line 1278 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2322 "dhcp6_parser.cc"
    break;

  case 310: // duid_id: "duid"
#line 1287 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2331 "dhcp6_parser.cc"
    break;

  case 311: // string_id: "constant string"
#line 1292 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2340 "dhcp6_parser.cc"
    break;

  case 312: // $@52: %empty
#line 1297 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2352 "dhcp6_parser.cc"
    break;

  case 313: // host_reservation_identifiers: "host-reservation-identifiers" $@52 ":" "[" host_reservation_identifiers_list "]"
#line 1303 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2361 "dhcp6_parser.cc"
    break;

  case 316: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1310 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2369 "dhcp6_parser.cc"
    break;

  case 320: // hw_address_id: "hw-address"
#line 1320 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2378 "dhcp6_parser.cc"
    break;

  case 321: // flex_id: "flex-id"
#line 1325 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2387 "dhcp6_parser.cc"
    break;

  case 322: // $@53: %empty
#line 1332 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2399 "dhcp6_parser.cc"
    break;

  case 323: // relay_supplied_options: "relay-supplied-options" $@53 ":" "[" list_content "]"
#line 1338 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2408 "dhcp6_parser.cc"
    break;

  case 324: // $@54: %empty
#line 1345 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2420 "dhcp6_parser.cc"
    break;

  case 325: // dhcp_multi_threading: "multi-threading" $@54 ":" "{" multi_threading_params "}"
#line 1351 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2431 "dhcp6_parser.cc"
    break;

  case 328: // multi_threading_params: multi_threading_params ","
#line 1360 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2439 "dhcp6_parser.cc"
    break;

  case 335: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1373 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2449 "dhcp6_parser.cc"
    break;

  case 336: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1379 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2459 "dhcp6_parser.cc"
    break;

  case 337: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1385 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2469 "dhcp6_parser.cc"
    break;

  case 338: // $@55: %empty
#line 1391 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2481 "dhcp6_parser.cc"
    break;

  case 339: // hooks_libraries: "hooks-libraries" $@55 ":" "[" hooks_libraries_list "]"
#line 1397 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2490 "dhcp6_parser.cc"
    break;

  case 344: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1408 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2498 "dhcp6_parser.cc"
    break;

  case 345: // $@56: %empty
#line 1413 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2508 "dhcp6_parser.cc"
    break;

  case 346: // hooks_library: "{" $@56 hooks_params "}"
#line 1417 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2518 "dhcp6_parser.cc"
    break;

  case 347: // $@57: %empty
#line 1423 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2528 "dhcp6_parser.cc"
    break;

  case 348: // sub_hooks_library: "{" $@57 hooks_params "}"
#line 1427 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2538 "dhcp6_parser.cc"
    break;

  case 351: // hooks_params: hooks_params ","
#line 1435 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2546 "dhcp6_parser.cc"
    break;

  case 355: // $@58: %empty
#line 1445 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2555 "dhcp6_parser.cc"
    break;

  case 356: // library: "library" $@58 ":" "constant string"
#line 1448 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2565 "dhcp6_parser.cc"
    break;

  case 357: // $@59: %empty
#line 1454 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2574 "dhcp6_parser.cc"
    break;

  case 358: // parameters: "parameters" $@59 ":" map_value
#line 1457 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2583 "dhcp6_parser.cc"
    break;

  case 359: // $@60: %empty
#line 1463 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2595 "dhcp6_parser.cc"
    break;

  case 360: // expired_leases_processing: "expired-leases-processing" $@60 ":" "{" expired_leases_params "}"
#line 1469 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2605 "dhcp6_parser.cc"
    break;

  case 363: // expired_leases_params: expired_leases_params ","
#line 1477 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2613 "dhcp6_parser.cc"
    break;

  case 370: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1490 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2623 "dhcp6_parser.cc"
    break;

  case 371: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1496 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2633 "dhcp6_parser.cc"
    break;

  case 372: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1502 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2643 "dhcp6_parser.cc"
    break;

  case 373: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1508 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2653 "dhcp6_parser.cc"
    break;

  case 374: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1514 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2663 "dhcp6_parser.cc"
    break;

  case 375: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1520 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2673 "dhcp6_parser.cc"
    break;

  case 376: // $@61: %empty
#line 1529 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2685 "dhcp6_parser.cc"
    break;

  case 377: // subnet6_list: "subnet6" $@61 ":" "[" subnet6_list_content "]"
#line 1535 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2694 "dhcp6_parser.cc"
    break;

  case 382: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1549 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2702 "dhcp6_parser.cc"
    break;

  case 383: // $@62: %empty
#line 1558 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2712 "dhcp6_parser.cc"
    break;

  case 384: // subnet6: "{" $@62 subnet6_params "}"
#line 1562 "dhcp6_parser.yy"
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
#line 2738 "dhcp6_parser.cc"
    break;

  case 385: // $@63: %empty
#line 1584 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2748 "dhcp6_parser.cc"
    break;

  case 386: // sub_subnet6: "{" $@63 subnet6_params "}"
#line 1588 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2758 "dhcp6_parser.cc"
    break;

  case 389: // subnet6_params: subnet6_params ","
#line 1597 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2766 "dhcp6_parser.cc"
    break;

  case 437: // $@64: %empty
#line 1652 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2775 "dhcp6_parser.cc"
    break;

  case 438: // subnet: "subnet" $@64 ":" "constant string"
#line 1655 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2785 "dhcp6_parser.cc"
    break;

  case 439: // $@65: %empty
#line 1661 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2794 "dhcp6_parser.cc"
    break;

  case 440: // interface: "interface" $@65 ":" "constant string"
#line 1664 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2804 "dhcp6_parser.cc"
    break;

  case 441: // $@66: %empty
#line 1670 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2813 "dhcp6_parser.cc"
    break;

  case 442: // interface_id: "interface-id" $@66 ":" "constant string"
#line 1673 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2823 "dhcp6_parser.cc"
    break;

  case 443: // $@67: %empty
#line 1679 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2832 "dhcp6_parser.cc"
    break;

  case 444: // client_class: "client-class" $@67 ":" "constant string"
#line 1682 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2842 "dhcp6_parser.cc"
    break;

  case 445: // $@68: %empty
#line 1689 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2854 "dhcp6_parser.cc"
    break;

  case 446: // require_client_classes: "require-client-classes" $@68 ":" list_strings
#line 1695 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2863 "dhcp6_parser.cc"
    break;

  case 447: // $@69: %empty
#line 1700 "dhcp6_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2875 "dhcp6_parser.cc"
    break;

  case 448: // evaluate_additional_classes: "evaluate-additional-classes" $@69 ":" list_strings
#line 1706 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2884 "dhcp6_parser.cc"
    break;

  case 449: // reservations_global: "reservations-global" ":" "boolean"
#line 1711 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2894 "dhcp6_parser.cc"
    break;

  case 450: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1717 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2904 "dhcp6_parser.cc"
    break;

  case 451: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1723 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2914 "dhcp6_parser.cc"
    break;

  case 452: // id: "id" ":" "integer"
#line 1729 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2924 "dhcp6_parser.cc"
    break;

  case 453: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1735 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2934 "dhcp6_parser.cc"
    break;

  case 454: // $@70: %empty
#line 1743 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2946 "dhcp6_parser.cc"
    break;

  case 455: // shared_networks: "shared-networks" $@70 ":" "[" shared_networks_content "]"
#line 1749 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2955 "dhcp6_parser.cc"
    break;

  case 460: // shared_networks_list: shared_networks_list ","
#line 1762 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2963 "dhcp6_parser.cc"
    break;

  case 461: // $@71: %empty
#line 1767 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2973 "dhcp6_parser.cc"
    break;

  case 462: // shared_network: "{" $@71 shared_network_params "}"
#line 1771 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2981 "dhcp6_parser.cc"
    break;

  case 465: // shared_network_params: shared_network_params ","
#line 1777 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2989 "dhcp6_parser.cc"
    break;

  case 510: // $@72: %empty
#line 1832 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3001 "dhcp6_parser.cc"
    break;

  case 511: // option_def_list: "option-def" $@72 ":" "[" option_def_list_content "]"
#line 1838 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3010 "dhcp6_parser.cc"
    break;

  case 512: // $@73: %empty
#line 1846 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3019 "dhcp6_parser.cc"
    break;

  case 513: // sub_option_def_list: "{" $@73 option_def_list "}"
#line 1849 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 3027 "dhcp6_parser.cc"
    break;

  case 518: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1861 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3035 "dhcp6_parser.cc"
    break;

  case 519: // $@74: %empty
#line 1868 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3045 "dhcp6_parser.cc"
    break;

  case 520: // option_def_entry: "{" $@74 option_def_params "}"
#line 1872 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3057 "dhcp6_parser.cc"
    break;

  case 521: // $@75: %empty
#line 1883 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3067 "dhcp6_parser.cc"
    break;

  case 522: // sub_option_def: "{" $@75 option_def_params "}"
#line 1887 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3079 "dhcp6_parser.cc"
    break;

  case 527: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1903 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3087 "dhcp6_parser.cc"
    break;

  case 539: // code: "code" ":" "integer"
#line 1922 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3097 "dhcp6_parser.cc"
    break;

  case 541: // $@76: %empty
#line 1930 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3106 "dhcp6_parser.cc"
    break;

  case 542: // option_def_type: "type" $@76 ":" "constant string"
#line 1933 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3116 "dhcp6_parser.cc"
    break;

  case 543: // $@77: %empty
#line 1939 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3125 "dhcp6_parser.cc"
    break;

  case 544: // option_def_record_types: "record-types" $@77 ":" "constant string"
#line 1942 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3135 "dhcp6_parser.cc"
    break;

  case 545: // $@78: %empty
#line 1948 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3144 "dhcp6_parser.cc"
    break;

  case 546: // space: "space" $@78 ":" "constant string"
#line 1951 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3154 "dhcp6_parser.cc"
    break;

  case 548: // $@79: %empty
#line 1959 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3163 "dhcp6_parser.cc"
    break;

  case 549: // option_def_encapsulate: "encapsulate" $@79 ":" "constant string"
#line 1962 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3173 "dhcp6_parser.cc"
    break;

  case 550: // option_def_array: "array" ":" "boolean"
#line 1968 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3183 "dhcp6_parser.cc"
    break;

  case 551: // $@80: %empty
#line 1978 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3195 "dhcp6_parser.cc"
    break;

  case 552: // option_data_list: "option-data" $@80 ":" "[" option_data_list_content "]"
#line 1984 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3204 "dhcp6_parser.cc"
    break;

  case 557: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1999 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3212 "dhcp6_parser.cc"
    break;

  case 558: // $@81: %empty
#line 2006 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3222 "dhcp6_parser.cc"
    break;

  case 559: // option_data_entry: "{" $@81 option_data_params "}"
#line 2010 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3231 "dhcp6_parser.cc"
    break;

  case 560: // $@82: %empty
#line 2018 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3241 "dhcp6_parser.cc"
    break;

  case 561: // sub_option_data: "{" $@82 option_data_params "}"
#line 2022 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3250 "dhcp6_parser.cc"
    break;

  case 566: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2038 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3258 "dhcp6_parser.cc"
    break;

  case 579: // $@83: %empty
#line 2060 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3267 "dhcp6_parser.cc"
    break;

  case 580: // option_data_data: "data" $@83 ":" "constant string"
#line 2063 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3277 "dhcp6_parser.cc"
    break;

  case 583: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2073 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3287 "dhcp6_parser.cc"
    break;

  case 584: // option_data_always_send: "always-send" ":" "boolean"
#line 2079 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3297 "dhcp6_parser.cc"
    break;

  case 585: // option_data_never_send: "never-send" ":" "boolean"
#line 2085 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3307 "dhcp6_parser.cc"
    break;

  case 586: // $@84: %empty
#line 2091 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3319 "dhcp6_parser.cc"
    break;

  case 587: // option_data_client_classes: "client-classes" $@84 ":" list_strings
#line 2097 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3328 "dhcp6_parser.cc"
    break;

  case 588: // $@85: %empty
#line 2105 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3340 "dhcp6_parser.cc"
    break;

  case 589: // pools_list: "pools" $@85 ":" "[" pools_list_content "]"
#line 2111 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3349 "dhcp6_parser.cc"
    break;

  case 594: // not_empty_pools_list: not_empty_pools_list ","
#line 2124 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3357 "dhcp6_parser.cc"
    break;

  case 595: // $@86: %empty
#line 2129 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3367 "dhcp6_parser.cc"
    break;

  case 596: // pool_list_entry: "{" $@86 pool_params "}"
#line 2133 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3377 "dhcp6_parser.cc"
    break;

  case 597: // $@87: %empty
#line 2139 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3387 "dhcp6_parser.cc"
    break;

  case 598: // sub_pool6: "{" $@87 pool_params "}"
#line 2143 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3397 "dhcp6_parser.cc"
    break;

  case 601: // pool_params: pool_params ","
#line 2151 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3405 "dhcp6_parser.cc"
    break;

  case 611: // $@88: %empty
#line 2167 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3414 "dhcp6_parser.cc"
    break;

  case 612: // pool_entry: "pool" $@88 ":" "constant string"
#line 2170 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3424 "dhcp6_parser.cc"
    break;

  case 613: // pool_id: "pool-id" ":" "integer"
#line 2176 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3434 "dhcp6_parser.cc"
    break;

  case 614: // $@89: %empty
#line 2182 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3442 "dhcp6_parser.cc"
    break;

  case 615: // user_context: "user-context" $@89 ":" map_value
#line 2184 "dhcp6_parser.yy"
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
#line 3469 "dhcp6_parser.cc"
    break;

  case 616: // $@90: %empty
#line 2207 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3477 "dhcp6_parser.cc"
    break;

  case 617: // comment: "comment" $@90 ":" "constant string"
#line 2209 "dhcp6_parser.yy"
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
#line 3506 "dhcp6_parser.cc"
    break;

  case 618: // $@91: %empty
#line 2237 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3518 "dhcp6_parser.cc"
    break;

  case 619: // pd_pools_list: "pd-pools" $@91 ":" "[" pd_pools_list_content "]"
#line 2243 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3527 "dhcp6_parser.cc"
    break;

  case 624: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2256 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3535 "dhcp6_parser.cc"
    break;

  case 625: // $@92: %empty
#line 2261 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3545 "dhcp6_parser.cc"
    break;

  case 626: // pd_pool_entry: "{" $@92 pd_pool_params "}"
#line 2265 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3557 "dhcp6_parser.cc"
    break;

  case 627: // $@93: %empty
#line 2273 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3567 "dhcp6_parser.cc"
    break;

  case 628: // sub_pd_pool: "{" $@93 pd_pool_params "}"
#line 2277 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3579 "dhcp6_parser.cc"
    break;

  case 631: // pd_pool_params: pd_pool_params ","
#line 2287 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3587 "dhcp6_parser.cc"
    break;

  case 645: // $@94: %empty
#line 2307 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3596 "dhcp6_parser.cc"
    break;

  case 646: // pd_prefix: "prefix" $@94 ":" "constant string"
#line 2310 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3606 "dhcp6_parser.cc"
    break;

  case 647: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2316 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3616 "dhcp6_parser.cc"
    break;

  case 648: // $@95: %empty
#line 2322 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3625 "dhcp6_parser.cc"
    break;

  case 649: // excluded_prefix: "excluded-prefix" $@95 ":" "constant string"
#line 2325 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3635 "dhcp6_parser.cc"
    break;

  case 650: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2331 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3645 "dhcp6_parser.cc"
    break;

  case 651: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2337 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3655 "dhcp6_parser.cc"
    break;

  case 652: // $@96: %empty
#line 2346 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3667 "dhcp6_parser.cc"
    break;

  case 653: // reservations: "reservations" $@96 ":" "[" reservations_list "]"
#line 2352 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3676 "dhcp6_parser.cc"
    break;

  case 658: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2363 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3684 "dhcp6_parser.cc"
    break;

  case 659: // $@97: %empty
#line 2368 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3694 "dhcp6_parser.cc"
    break;

  case 660: // reservation: "{" $@97 reservation_params "}"
#line 2372 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3703 "dhcp6_parser.cc"
    break;

  case 661: // $@98: %empty
#line 2377 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3713 "dhcp6_parser.cc"
    break;

  case 662: // sub_reservation: "{" $@98 reservation_params "}"
#line 2381 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3722 "dhcp6_parser.cc"
    break;

  case 667: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2392 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3730 "dhcp6_parser.cc"
    break;

  case 680: // $@99: %empty
#line 2412 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3742 "dhcp6_parser.cc"
    break;

  case 681: // ip_addresses: "ip-addresses" $@99 ":" list_strings
#line 2418 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3751 "dhcp6_parser.cc"
    break;

  case 682: // $@100: %empty
#line 2423 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3763 "dhcp6_parser.cc"
    break;

  case 683: // prefixes: "prefixes" $@100 ":" list_strings
#line 2429 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3772 "dhcp6_parser.cc"
    break;

  case 684: // $@101: %empty
#line 2434 "dhcp6_parser.yy"
                                     {
    ctx.unique("excluded-prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3784 "dhcp6_parser.cc"
    break;

  case 685: // excluded_prefixes: "excluded-prefixes" $@101 ":" list_strings
#line 2440 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3793 "dhcp6_parser.cc"
    break;

  case 686: // $@102: %empty
#line 2445 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3802 "dhcp6_parser.cc"
    break;

  case 687: // duid: "duid" $@102 ":" "constant string"
#line 2448 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3812 "dhcp6_parser.cc"
    break;

  case 688: // $@103: %empty
#line 2454 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3821 "dhcp6_parser.cc"
    break;

  case 689: // hw_address: "hw-address" $@103 ":" "constant string"
#line 2457 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3831 "dhcp6_parser.cc"
    break;

  case 690: // $@104: %empty
#line 2463 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3840 "dhcp6_parser.cc"
    break;

  case 691: // hostname: "hostname" $@104 ":" "constant string"
#line 2466 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3850 "dhcp6_parser.cc"
    break;

  case 692: // $@105: %empty
#line 2472 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3859 "dhcp6_parser.cc"
    break;

  case 693: // flex_id_value: "flex-id" $@105 ":" "constant string"
#line 2475 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3869 "dhcp6_parser.cc"
    break;

  case 694: // $@106: %empty
#line 2481 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3881 "dhcp6_parser.cc"
    break;

  case 695: // reservation_client_classes: "client-classes" $@106 ":" list_strings
#line 2487 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3890 "dhcp6_parser.cc"
    break;

  case 696: // $@107: %empty
#line 2495 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3902 "dhcp6_parser.cc"
    break;

  case 697: // relay: "relay" $@107 ":" "{" relay_map "}"
#line 2501 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3911 "dhcp6_parser.cc"
    break;

  case 699: // $@108: %empty
#line 2512 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3923 "dhcp6_parser.cc"
    break;

  case 700: // client_classes: "client-classes" $@108 ":" "[" client_classes_list "]"
#line 2518 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3932 "dhcp6_parser.cc"
    break;

  case 703: // client_classes_list: client_classes_list ","
#line 2525 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3940 "dhcp6_parser.cc"
    break;

  case 704: // $@109: %empty
#line 2530 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3950 "dhcp6_parser.cc"
    break;

  case 705: // client_class_entry: "{" $@109 client_class_params "}"
#line 2534 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3960 "dhcp6_parser.cc"
    break;

  case 710: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2546 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3968 "dhcp6_parser.cc"
    break;

  case 727: // $@110: %empty
#line 2570 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3977 "dhcp6_parser.cc"
    break;

  case 728: // client_class_test: "test" $@110 ":" "constant string"
#line 2573 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3987 "dhcp6_parser.cc"
    break;

  case 729: // $@111: %empty
#line 2579 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3996 "dhcp6_parser.cc"
    break;

  case 730: // client_class_template_test: "template-test" $@111 ":" "constant string"
#line 2582 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4006 "dhcp6_parser.cc"
    break;

  case 731: // only_if_required: "only-if-required" ":" "boolean"
#line 2589 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4016 "dhcp6_parser.cc"
    break;

  case 732: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2595 "dhcp6_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4026 "dhcp6_parser.cc"
    break;

  case 733: // $@112: %empty
#line 2604 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 4038 "dhcp6_parser.cc"
    break;

  case 734: // server_id: "server-id" $@112 ":" "{" server_id_params "}"
#line 2610 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4049 "dhcp6_parser.cc"
    break;

  case 737: // server_id_params: server_id_params ","
#line 2619 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4057 "dhcp6_parser.cc"
    break;

  case 747: // $@113: %empty
#line 2635 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 4066 "dhcp6_parser.cc"
    break;

  case 748: // server_id_type: "type" $@113 ":" duid_type
#line 2638 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4075 "dhcp6_parser.cc"
    break;

  case 749: // duid_type: "LLT"
#line 2643 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4081 "dhcp6_parser.cc"
    break;

  case 750: // duid_type: "EN"
#line 2644 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4087 "dhcp6_parser.cc"
    break;

  case 751: // duid_type: "LL"
#line 2645 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4093 "dhcp6_parser.cc"
    break;

  case 752: // htype: "htype" ":" "integer"
#line 2648 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4103 "dhcp6_parser.cc"
    break;

  case 753: // $@114: %empty
#line 2654 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4112 "dhcp6_parser.cc"
    break;

  case 754: // identifier: "identifier" $@114 ":" "constant string"
#line 2657 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4122 "dhcp6_parser.cc"
    break;

  case 755: // time: "time" ":" "integer"
#line 2663 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4132 "dhcp6_parser.cc"
    break;

  case 756: // enterprise_id: "enterprise-id" ":" "integer"
#line 2669 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4142 "dhcp6_parser.cc"
    break;

  case 757: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2677 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4152 "dhcp6_parser.cc"
    break;

  case 758: // $@115: %empty
#line 2685 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4165 "dhcp6_parser.cc"
    break;

  case 759: // control_socket: "control-socket" $@115 ":" "{" control_socket_params "}"
#line 2692 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4174 "dhcp6_parser.cc"
    break;

  case 760: // $@116: %empty
#line 2697 "dhcp6_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4187 "dhcp6_parser.cc"
    break;

  case 761: // control_sockets: "control-sockets" $@116 ":" "[" control_socket_list "]"
#line 2704 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4196 "dhcp6_parser.cc"
    break;

  case 766: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2715 "dhcp6_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4204 "dhcp6_parser.cc"
    break;

  case 767: // $@117: %empty
#line 2720 "dhcp6_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4214 "dhcp6_parser.cc"
    break;

  case 768: // control_socket_entry: "{" $@117 control_socket_params "}"
#line 2724 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4222 "dhcp6_parser.cc"
    break;

  case 771: // control_socket_params: control_socket_params ","
#line 2730 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4230 "dhcp6_parser.cc"
    break;

  case 784: // $@118: %empty
#line 2749 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4239 "dhcp6_parser.cc"
    break;

  case 785: // control_socket_type: "socket-type" $@118 ":" control_socket_type_value
#line 2752 "dhcp6_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4248 "dhcp6_parser.cc"
    break;

  case 786: // control_socket_type_value: "unix"
#line 2758 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4254 "dhcp6_parser.cc"
    break;

  case 787: // control_socket_type_value: "http"
#line 2759 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4260 "dhcp6_parser.cc"
    break;

  case 788: // control_socket_type_value: "https"
#line 2760 "dhcp6_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4266 "dhcp6_parser.cc"
    break;

  case 789: // $@119: %empty
#line 2763 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4276 "dhcp6_parser.cc"
    break;

  case 790: // control_socket_name: "socket-name" $@119 ":" "constant string"
#line 2767 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4286 "dhcp6_parser.cc"
    break;

  case 791: // $@120: %empty
#line 2773 "dhcp6_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4296 "dhcp6_parser.cc"
    break;

  case 792: // control_socket_address: "socket-address" $@120 ":" "constant string"
#line 2777 "dhcp6_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4306 "dhcp6_parser.cc"
    break;

  case 793: // control_socket_port: "socket-port" ":" "integer"
#line 2783 "dhcp6_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4316 "dhcp6_parser.cc"
    break;

  case 794: // cert_required: "cert-required" ":" "boolean"
#line 2789 "dhcp6_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4326 "dhcp6_parser.cc"
    break;

  case 795: // $@121: %empty
#line 2797 "dhcp6_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4338 "dhcp6_parser.cc"
    break;

  case 796: // authentication: "authentication" $@121 ":" "{" auth_params "}"
#line 2803 "dhcp6_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4349 "dhcp6_parser.cc"
    break;

  case 799: // auth_params: auth_params ","
#line 2812 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4357 "dhcp6_parser.cc"
    break;

  case 807: // $@122: %empty
#line 2826 "dhcp6_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4366 "dhcp6_parser.cc"
    break;

  case 808: // auth_type: "type" $@122 ":" auth_type_value
#line 2829 "dhcp6_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4375 "dhcp6_parser.cc"
    break;

  case 809: // auth_type_value: "basic"
#line 2834 "dhcp6_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4381 "dhcp6_parser.cc"
    break;

  case 810: // $@123: %empty
#line 2837 "dhcp6_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4390 "dhcp6_parser.cc"
    break;

  case 811: // realm: "realm" $@123 ":" "constant string"
#line 2840 "dhcp6_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4400 "dhcp6_parser.cc"
    break;

  case 812: // $@124: %empty
#line 2846 "dhcp6_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4409 "dhcp6_parser.cc"
    break;

  case 813: // directory: "directory" $@124 ":" "constant string"
#line 2849 "dhcp6_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4419 "dhcp6_parser.cc"
    break;

  case 814: // $@125: %empty
#line 2855 "dhcp6_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4431 "dhcp6_parser.cc"
    break;

  case 815: // clients: "clients" $@125 ":" "[" clients_list "]"
#line 2861 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4440 "dhcp6_parser.cc"
    break;

  case 820: // not_empty_clients_list: not_empty_clients_list ","
#line 2872 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4448 "dhcp6_parser.cc"
    break;

  case 821: // $@126: %empty
#line 2877 "dhcp6_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4458 "dhcp6_parser.cc"
    break;

  case 822: // basic_auth: "{" $@126 clients_params "}"
#line 2881 "dhcp6_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4466 "dhcp6_parser.cc"
    break;

  case 825: // clients_params: clients_params ","
#line 2887 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4474 "dhcp6_parser.cc"
    break;

  case 833: // $@127: %empty
#line 2901 "dhcp6_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4483 "dhcp6_parser.cc"
    break;

  case 834: // user_file: "user-file" $@127 ":" "constant string"
#line 2904 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4493 "dhcp6_parser.cc"
    break;

  case 835: // $@128: %empty
#line 2910 "dhcp6_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4502 "dhcp6_parser.cc"
    break;

  case 836: // password_file: "password-file" $@128 ":" "constant string"
#line 2913 "dhcp6_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4512 "dhcp6_parser.cc"
    break;

  case 837: // $@129: %empty
#line 2921 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4524 "dhcp6_parser.cc"
    break;

  case 838: // dhcp_queue_control: "dhcp-queue-control" $@129 ":" "{" queue_control_params "}"
#line 2927 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4535 "dhcp6_parser.cc"
    break;

  case 841: // queue_control_params: queue_control_params ","
#line 2936 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4543 "dhcp6_parser.cc"
    break;

  case 848: // enable_queue: "enable-queue" ":" "boolean"
#line 2949 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4553 "dhcp6_parser.cc"
    break;

  case 849: // $@130: %empty
#line 2955 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4562 "dhcp6_parser.cc"
    break;

  case 850: // queue_type: "queue-type" $@130 ":" "constant string"
#line 2958 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4572 "dhcp6_parser.cc"
    break;

  case 851: // capacity: "capacity" ":" "integer"
#line 2964 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4582 "dhcp6_parser.cc"
    break;

  case 852: // $@131: %empty
#line 2970 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4591 "dhcp6_parser.cc"
    break;

  case 853: // arbitrary_map_entry: "constant string" $@131 ":" value
#line 2973 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4600 "dhcp6_parser.cc"
    break;

  case 854: // $@132: %empty
#line 2980 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4612 "dhcp6_parser.cc"
    break;

  case 855: // dhcp_ddns: "dhcp-ddns" $@132 ":" "{" dhcp_ddns_params "}"
#line 2986 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4623 "dhcp6_parser.cc"
    break;

  case 856: // $@133: %empty
#line 2993 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4633 "dhcp6_parser.cc"
    break;

  case 857: // sub_dhcp_ddns: "{" $@133 dhcp_ddns_params "}"
#line 2997 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4643 "dhcp6_parser.cc"
    break;

  case 860: // dhcp_ddns_params: dhcp_ddns_params ","
#line 3005 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4651 "dhcp6_parser.cc"
    break;

  case 872: // enable_updates: "enable-updates" ":" "boolean"
#line 3023 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4661 "dhcp6_parser.cc"
    break;

  case 873: // $@134: %empty
#line 3029 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4670 "dhcp6_parser.cc"
    break;

  case 874: // server_ip: "server-ip" $@134 ":" "constant string"
#line 3032 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4680 "dhcp6_parser.cc"
    break;

  case 875: // server_port: "server-port" ":" "integer"
#line 3038 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4690 "dhcp6_parser.cc"
    break;

  case 876: // $@135: %empty
#line 3044 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4699 "dhcp6_parser.cc"
    break;

  case 877: // sender_ip: "sender-ip" $@135 ":" "constant string"
#line 3047 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4709 "dhcp6_parser.cc"
    break;

  case 878: // sender_port: "sender-port" ":" "integer"
#line 3053 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4719 "dhcp6_parser.cc"
    break;

  case 879: // max_queue_size: "max-queue-size" ":" "integer"
#line 3059 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4729 "dhcp6_parser.cc"
    break;

  case 880: // $@136: %empty
#line 3065 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4738 "dhcp6_parser.cc"
    break;

  case 881: // ncr_protocol: "ncr-protocol" $@136 ":" ncr_protocol_value
#line 3068 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4747 "dhcp6_parser.cc"
    break;

  case 882: // ncr_protocol_value: "UDP"
#line 3074 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4753 "dhcp6_parser.cc"
    break;

  case 883: // ncr_protocol_value: "TCP"
#line 3075 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4759 "dhcp6_parser.cc"
    break;

  case 884: // $@137: %empty
#line 3078 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4768 "dhcp6_parser.cc"
    break;

  case 885: // ncr_format: "ncr-format" $@137 ":" "JSON"
#line 3081 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4778 "dhcp6_parser.cc"
    break;

  case 886: // $@138: %empty
#line 3089 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4790 "dhcp6_parser.cc"
    break;

  case 887: // config_control: "config-control" $@138 ":" "{" config_control_params "}"
#line 3095 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4800 "dhcp6_parser.cc"
    break;

  case 888: // $@139: %empty
#line 3101 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4810 "dhcp6_parser.cc"
    break;

  case 889: // sub_config_control: "{" $@139 config_control_params "}"
#line 3105 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4819 "dhcp6_parser.cc"
    break;

  case 892: // config_control_params: config_control_params ","
#line 3113 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4827 "dhcp6_parser.cc"
    break;

  case 895: // $@140: %empty
#line 3123 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4839 "dhcp6_parser.cc"
    break;

  case 896: // config_databases: "config-databases" $@140 ":" "[" database_list "]"
#line 3129 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4848 "dhcp6_parser.cc"
    break;

  case 897: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3134 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4858 "dhcp6_parser.cc"
    break;

  case 898: // $@141: %empty
#line 3142 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4870 "dhcp6_parser.cc"
    break;

  case 899: // loggers: "loggers" $@141 ":" "[" loggers_entries "]"
#line 3148 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4879 "dhcp6_parser.cc"
    break;

  case 902: // loggers_entries: loggers_entries ","
#line 3157 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4887 "dhcp6_parser.cc"
    break;

  case 903: // $@142: %empty
#line 3163 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4897 "dhcp6_parser.cc"
    break;

  case 904: // logger_entry: "{" $@142 logger_params "}"
#line 3167 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4905 "dhcp6_parser.cc"
    break;

  case 907: // logger_params: logger_params ","
#line 3173 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4913 "dhcp6_parser.cc"
    break;

  case 915: // debuglevel: "debuglevel" ":" "integer"
#line 3187 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4923 "dhcp6_parser.cc"
    break;

  case 916: // $@143: %empty
#line 3193 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4932 "dhcp6_parser.cc"
    break;

  case 917: // severity: "severity" $@143 ":" "constant string"
#line 3196 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4942 "dhcp6_parser.cc"
    break;

  case 918: // $@144: %empty
#line 3202 "dhcp6_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4954 "dhcp6_parser.cc"
    break;

  case 919: // output_options_list: "output-options" $@144 ":" "[" output_options_list_content "]"
#line 3208 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4963 "dhcp6_parser.cc"
    break;

  case 922: // output_options_list_content: output_options_list_content ","
#line 3215 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4971 "dhcp6_parser.cc"
    break;

  case 923: // $@145: %empty
#line 3220 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4981 "dhcp6_parser.cc"
    break;

  case 924: // output_entry: "{" $@145 output_params_list "}"
#line 3224 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4989 "dhcp6_parser.cc"
    break;

  case 927: // output_params_list: output_params_list ","
#line 3230 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4997 "dhcp6_parser.cc"
    break;

  case 933: // $@146: %empty
#line 3242 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5006 "dhcp6_parser.cc"
    break;

  case 934: // output: "output" $@146 ":" "constant string"
#line 3245 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5016 "dhcp6_parser.cc"
    break;

  case 935: // flush: "flush" ":" "boolean"
#line 3251 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5026 "dhcp6_parser.cc"
    break;

  case 936: // maxsize: "maxsize" ":" "integer"
#line 3257 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5036 "dhcp6_parser.cc"
    break;

  case 937: // maxver: "maxver" ":" "integer"
#line 3263 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5046 "dhcp6_parser.cc"
    break;

  case 938: // $@147: %empty
#line 3269 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5055 "dhcp6_parser.cc"
    break;

  case 939: // pattern: "pattern" $@147 ":" "constant string"
#line 3272 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5065 "dhcp6_parser.cc"
    break;

  case 940: // $@148: %empty
#line 3278 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5077 "dhcp6_parser.cc"
    break;

  case 941: // compatibility: "compatibility" $@148 ":" "{" compatibility_params "}"
#line 3284 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5086 "dhcp6_parser.cc"
    break;

  case 944: // compatibility_params: compatibility_params ","
#line 3291 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5094 "dhcp6_parser.cc"
    break;

  case 947: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3300 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5104 "dhcp6_parser.cc"
    break;


#line 5108 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1371;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     433, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371,    43,    35,    83,    98,   110,
     114,   126,   128,   130,   132,   134,   142,   158,   160,   190,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,    35,  -175,
      46,   725,    54,  1369,   179,   140,   182,    -7,   127,   280,
     -95,   245,    62, -1371,   121,   144,   185,   196,   203, -1371,
      49, -1371, -1371, -1371, -1371, -1371, -1371, -1371,   223,   268,
     321,   327,   333,   351,   353,   363,   364,   372,   424,   449,
     450,   451, -1371,   453,   454,   455,   456,   457, -1371, -1371,
   -1371,   458,   459,   460,   461, -1371, -1371, -1371,   462, -1371,
   -1371, -1371, -1371, -1371, -1371,   463,   464,   466, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371,   467, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371,   468,   471,   472, -1371, -1371,
     473, -1371,    60, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371,   474,   477,   482,   484, -1371,    81, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371,   485,   486, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371,    99, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,   488, -1371,
   -1371, -1371, -1371, -1371,   100, -1371, -1371, -1371, -1371, -1371,
   -1371,   489, -1371,   490,   492, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371,   101, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371,   241,   228, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371,   243, -1371, -1371,   493, -1371, -1371, -1371,
     494, -1371, -1371,   282,   307, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,   496,   499,
     500, -1371, -1371, -1371, -1371, -1371,   316,   403, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371,   116, -1371, -1371, -1371,   501, -1371,   503, -1371,
     506,   507, -1371, -1371, -1371, -1371, -1371,   154, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,   508,   193,
   -1371, -1371, -1371, -1371,    35,    35, -1371,   186,   512, -1371,
   -1371,   514,   516,   519,   520,   521,   524,   187,   207,   209,
     299,   301,   303,   305,   308,   304,   309,   310,   311,   313,
     314,   542,   319,   323,   318,   322,   325,   547,   551,   555,
     328,   329,   335,   337,   560,   563,   564,   340,   567,   568,
     569,   571,   572,   578,   352,   354,   356,   579,   581,   585,
     586,   587,   590,   592,   593,   594,   370,   597,   598,   599,
     600,   602,   604,   610,   386,   389,   391,   612,   615, -1371,
     725, -1371,   616,   392,   400,   396,   397,    54, -1371,   630,
     631,   632,   633,   635,   412,   409,   639,   640,   642,   658,
    1369, -1371,   659,   434,   179, -1371,   661,   438,   663,   440,
     441,   140, -1371,   668,   669,   670,   671,   672,   673,   674,
     675, -1371,   182, -1371,   676,   677,   452,   679,   680,   681,
     465, -1371,   127,   682,   469,   470,   475,   683, -1371,   280,
     684,   685,   120, -1371,   476,   686,   480,   687,   481,   487,
     688,   689,   245, -1371,   690,   491,    62, -1371, -1371, -1371,
     692,   691,   483,   693,   696,   707,   708,   694, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371,   495, -1371, -1371, -1371, -1371, -1371,  -116,   498,
     509, -1371, -1371, -1371, -1371,   711,   713,   714, -1371,   510,
     513,   332,   715,   716,   515, -1371, -1371, -1371,   717,   720,
     723,   722,   736,   738,   740,   742,   743, -1371,   744,   745,
     748,   747,   749,   526,   528, -1371, -1371, -1371,   753,   752,
   -1371,   755, -1371, -1371, -1371, -1371, -1371,   759,   762,   539,
     540,   541, -1371, -1371,   755,   755,   543,   764, -1371,   574,
   -1371, -1371,   575, -1371,   576, -1371, -1371, -1371,   755,   755,
     755,   755,   577,   580,   582,   583, -1371,   588,   589, -1371,
     591,   595,   596, -1371, -1371,   603, -1371, -1371, -1371,   755,
   -1371,   605,   716, -1371, -1371,   606, -1371,   607, -1371, -1371,
      23,   613, -1371,   803, -1371, -1371,    35,   725, -1371,    62,
      54,   148,   148,   812, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371,   815,   816,   819, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371,   820, -1371, -1371, -1371,   -93,    35,   -43,
     162,   821,   822,   826,   227,    82,    -5,   165,   837,   124,
     245, -1371, -1371,   838,  -163, -1371, -1371,   840,   841, -1371,
   -1371, -1371, -1371, -1371, -1371,   718, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371,   812, -1371,   231,   247,   249, -1371, -1371, -1371,
   -1371,   806,   846,   847,   848,   849,   850,   852,   853,   854,
     855, -1371,   856,   857, -1371, -1371, -1371, -1371, -1371,   250,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371,   320, -1371,   859,   860, -1371, -1371,   862,
     863, -1371, -1371,   864,   866, -1371, -1371,   865,   869, -1371,
   -1371,   867,   872, -1371, -1371, -1371,   112, -1371, -1371, -1371,
     870, -1371, -1371, -1371,   222, -1371, -1371, -1371, -1371, -1371,
     324, -1371, -1371, -1371, -1371,   286, -1371, -1371,   871,   875,
   -1371, -1371,   873,   877, -1371,   858,   880,   881,   882,   885,
     886,   336, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371,   887,   888,   889, -1371, -1371, -1371, -1371,   338, -1371,
   -1371, -1371, -1371, -1371, -1371,   890,   891,   892, -1371,   375,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,   893,
   -1371,   894, -1371, -1371, -1371, -1371, -1371, -1371,   381, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371,   895,   878, -1371,
     896, -1371,   898, -1371, -1371, -1371,   384, -1371, -1371, -1371,
   -1371, -1371,   385, -1371,   306, -1371,   899, -1371,   387, -1371,
   -1371,   678, -1371,   900,   902, -1371, -1371,   903,   907, -1371,
   -1371,   904,   905, -1371, -1371, -1371,   909,   910,   911,   912,
     700,   667,   701,   702,   703,   705,   706,   709,   710,   712,
     913,   719,   726,   914,   915,   916,   917,   148, -1371, -1371,
     148, -1371,   812,  1369, -1371,   815,   127, -1371,   816,   280,
   -1371,   819,  1465, -1371,   820,   -93, -1371, -1371,   -43, -1371,
     918,   919,   162, -1371,   170,   821, -1371,   182, -1371,   822,
     -95, -1371,   826,   727,   728,   729,   730,   731,   732,   227,
   -1371,   928,   933,   733,   734,   735,    82, -1371,   721,   737,
     739,    -5, -1371,   937,   939,   940,   741,   941,   746,   165,
   -1371,   165, -1371,   837,   751,   942,   750,   943,   124, -1371,
   -1371,   215,   838, -1371,   754,  -163, -1371, -1371,   944,   945,
     179, -1371,   840,   140, -1371,   841, -1371, -1371,   758,   760,
     761,   766, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371,   259, -1371, -1371,   771,   773,   775,   781, -1371,
     388, -1371,   394, -1371,   947, -1371,   958, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,   395, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371,   783,   789, -1371,
   -1371, -1371,   948,   964, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371,   962,   946, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371,   965, -1371,   401, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371,   296,   791, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371,   285,   792,   794, -1371,   967,
   -1371, -1371,   402, -1371, -1371,   797, -1371,    35, -1371, -1371,
     968, -1371, -1371, -1371, -1371, -1371,   404, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371,   798,   410, -1371,   411, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371,  1465, -1371, -1371, -1371,
     971,   972,   799,   801, -1371,   170, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,    25,
   -1371, -1371, -1371,   973,   763,   975,   215, -1371, -1371, -1371,
   -1371, -1371,   814,   817, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371,   413, -1371, -1371, -1371, -1371, -1371,
     976, -1371,   818, -1371, -1371, -1371,   980,  1037,  1048,  1049,
      25, -1371,  1050, -1371,   883,   832,   839,  1065, -1371, -1371,
     342, -1371, -1371, -1371, -1371, -1371,  1064,  -113,  1050, -1371,
   -1371,  1066,  1074, -1371, -1371,  1076,  1079,  1087, -1371,   435,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371,    97, -1371,  1064,
    1094,   922,   906,   921,  1106,  -113, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371,   437, -1371, -1371, -1371, -1371,   884,
   -1371, -1371, -1371,   920, -1371,  1144,  1153,    97, -1371, -1371,
   -1371,   930,   931, -1371, -1371, -1371
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   199,     9,   385,    11,
     597,    13,   627,    15,   661,    17,   512,    19,   521,    21,
     560,    23,   347,    25,   856,    27,   888,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   663,     0,   523,   562,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   141,   886,   197,   218,   220,   222,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   187,     0,     0,     0,     0,     0,   160,   167,
     169,     0,     0,     0,     0,   376,   510,   551,     0,   190,
     192,   173,   454,   614,   616,     0,     0,     0,   303,   322,
     312,   292,   699,   652,   338,   359,   733,     0,   324,   758,
     760,   837,   854,   180,   182,     0,     0,     0,   898,   940,
       0,   140,     0,    69,    72,    73,    74,    75,    76,    77,
      78,    79,    80,   111,   112,   113,   114,   115,    81,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   117,
     118,   129,   130,   131,   107,   137,   138,   139,   133,   134,
     135,    84,    85,    86,    87,   104,    88,    90,    89,   132,
      94,    95,    82,   108,   109,   110,    83,    92,    93,   102,
     103,   105,    91,    96,    97,    98,    99,   100,   101,   106,
     116,   136,   212,     0,     0,     0,     0,   211,     0,   201,
     204,   205,   206,   207,   208,   209,   210,   588,   618,   437,
     439,   441,     0,     0,   445,   447,   443,   696,   436,   390,
     391,   392,   393,   394,   395,   396,   397,   416,   417,   418,
     419,   420,   423,   424,   425,   426,   427,   428,   429,   430,
     431,   432,   421,   422,   433,   434,   435,     0,   387,   401,
     402,   403,   406,   407,   408,   410,   411,   412,   404,   405,
     398,   399,   414,   415,   400,   409,   413,   611,     0,   610,
     605,   606,   607,   604,     0,   599,   602,   603,   608,   609,
     645,     0,   648,     0,     0,   644,   637,   638,   639,   636,
     635,   642,   643,     0,   629,   632,   633,   640,   641,   634,
     694,   680,   682,   684,   686,   688,   690,   692,   679,   676,
     677,   678,     0,   664,   665,   670,   671,   672,   668,   673,
     674,   675,   669,     0,   541,   266,     0,   545,   543,   548,
       0,   537,   538,     0,   524,   525,   528,   540,   529,   530,
     531,   547,   532,   533,   534,   535,   536,   579,     0,     0,
       0,   586,   577,   578,   581,   582,     0,   563,   564,   567,
     568,   569,   570,   571,   572,   573,   576,   574,   575,   355,
     357,   352,     0,   349,   353,   354,     0,   873,     0,   876,
       0,     0,   880,   884,   871,   869,   870,     0,   858,   861,
     862,   863,   864,   865,   866,   867,   868,   895,     0,     0,
     890,   893,   894,    47,    52,     0,    39,    45,     0,    66,
      62,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
      71,    68,     0,     0,     0,     0,     0,   203,   200,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     389,   386,     0,     0,   601,   598,     0,     0,     0,     0,
       0,   631,   628,     0,     0,     0,     0,     0,     0,     0,
       0,   662,   667,   513,     0,     0,     0,     0,     0,     0,
       0,   522,   527,     0,     0,     0,     0,     0,   561,   566,
       0,     0,   351,   348,     0,     0,     0,     0,     0,     0,
       0,     0,   860,   857,     0,     0,   892,   889,    51,    43,
       0,     0,     0,     0,     0,     0,     0,     0,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,     0,   185,   186,   157,   158,   159,     0,     0,
       0,   171,   172,   179,   184,     0,     0,     0,   189,     0,
       0,     0,     0,     0,     0,   449,   450,   451,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   757,     0,     0,
       0,     0,     0,     0,     0,   194,   195,   196,     0,     0,
      70,     0,   214,   215,   216,   217,   202,     0,     0,     0,
       0,     0,   452,   453,     0,     0,     0,     0,   388,     0,
     613,   600,     0,   647,     0,   650,   651,   630,     0,     0,
       0,     0,     0,     0,     0,     0,   666,     0,     0,   539,
       0,     0,     0,   550,   526,     0,   583,   584,   585,     0,
     565,     0,     0,   350,   872,     0,   875,     0,   878,   879,
       0,     0,   859,     0,   897,   891,     0,     0,   142,     0,
       0,     0,     0,   224,   188,   162,   163,   164,   165,   166,
     161,   168,   170,   378,   514,   553,   191,   193,   175,   176,
     177,   178,   174,   456,    40,   615,   617,     0,    48,     0,
       0,     0,   654,   340,     0,     0,     0,     0,   762,     0,
       0,   181,   183,     0,     0,    53,   213,   590,   620,   438,
     440,   442,   446,   448,   444,     0,   612,   646,   649,   695,
     681,   683,   685,   687,   689,   691,   693,   542,   267,   546,
     544,   549,   580,   587,   356,   358,   874,   877,   882,   883,
     881,   885,   224,    44,     0,     0,     0,   257,   259,   261,
     263,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   276,     0,     0,   284,   286,   288,   290,   256,     0,
     231,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   248,   249,   250,   251,   247,   252,
     253,   254,   255,     0,   229,     0,   225,   226,   383,     0,
     379,   380,   519,     0,   515,   516,   558,     0,   554,   555,
     461,     0,   457,   458,   310,   311,     0,   305,   308,   309,
       0,   320,   321,   317,     0,   314,   318,   319,   299,   301,
       0,   294,   297,   298,   704,     0,   701,   659,     0,   655,
     656,   345,     0,   341,   342,     0,     0,     0,     0,     0,
       0,     0,   361,   364,   365,   366,   367,   368,   369,   747,
     753,     0,     0,     0,   746,   743,   744,   745,     0,   735,
     738,   741,   739,   740,   742,     0,     0,     0,   334,     0,
     326,   329,   330,   331,   332,   333,   784,   789,   791,     0,
     795,     0,   783,   777,   778,   779,   781,   782,     0,   769,
     772,   773,   774,   775,   780,   776,   767,     0,   763,   764,
       0,   849,     0,   852,   845,   846,     0,   839,   842,   843,
     844,   847,     0,   903,     0,   900,     0,   946,     0,   942,
     945,    55,   595,     0,   591,   592,   625,     0,   621,   622,
     698,     0,     0,    64,   887,   198,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   233,   219,   221,
       0,   223,   228,     0,   377,   382,   523,   511,   518,   562,
     552,   557,     0,   455,   460,   307,   304,   323,   316,   313,
       0,     0,   296,   293,   706,   703,   700,   663,   653,   658,
       0,   339,   344,     0,     0,     0,     0,     0,     0,   363,
     360,     0,     0,     0,     0,     0,   737,   734,     0,     0,
       0,   328,   325,     0,     0,     0,     0,     0,     0,   771,
     759,     0,   761,   766,     0,     0,     0,     0,   841,   838,
     855,     0,   902,   899,     0,   944,   941,    57,     0,    56,
       0,   589,   594,     0,   619,   624,   697,   896,     0,     0,
       0,     0,   265,   268,   269,   270,   271,   272,   273,   274,
     283,   275,     0,   281,   282,     0,     0,     0,     0,   232,
       0,   227,     0,   381,     0,   517,     0,   556,   509,   480,
     481,   482,   484,   485,   486,   470,   471,   489,   490,   491,
     492,   493,   496,   497,   498,   499,   500,   501,   502,   503,
     504,   505,   494,   495,   506,   507,   508,   466,   467,   468,
     469,   477,   478,   479,   474,   475,   476,   483,     0,   463,
     472,   487,   488,   473,   459,   306,   315,     0,     0,   295,
     727,   729,     0,     0,   725,   719,   720,   721,   722,   723,
     724,   726,   716,   717,   718,     0,   707,   708,   711,   712,
     713,   714,   715,   702,     0,   657,     0,   343,   370,   371,
     372,   373,   374,   375,   362,     0,     0,   752,   755,   756,
     736,   335,   336,   337,   327,     0,     0,     0,   793,     0,
     794,   770,     0,   765,   848,     0,   851,     0,   840,   918,
       0,   916,   914,   908,   912,   913,     0,   905,   910,   911,
     909,   901,   947,   943,    54,    59,     0,   593,     0,   623,
     258,   260,   262,   264,   278,   279,   280,   277,   285,   287,
     289,   291,   230,   384,   520,   559,   465,   462,   300,   302,
       0,     0,     0,     0,   705,   710,   660,   346,   749,   750,
     751,   748,   754,   786,   787,   788,   785,   790,   792,     0,
     768,   850,   853,     0,     0,     0,   907,   904,    58,   596,
     626,   464,     0,     0,   731,   732,   709,   807,   810,   812,
     814,   806,   805,   804,     0,   797,   800,   801,   802,   803,
       0,   915,     0,   906,   728,   730,     0,     0,     0,     0,
     799,   796,     0,   917,     0,     0,     0,     0,   798,   923,
       0,   920,   809,   808,   811,   813,   816,     0,   922,   919,
     821,     0,   817,   818,   933,     0,     0,     0,   938,     0,
     925,   928,   929,   930,   931,   932,   921,     0,   815,   820,
       0,     0,     0,     0,     0,   927,   924,   833,   835,   832,
     826,   828,   830,   831,     0,   823,   827,   829,   819,     0,
     935,   936,   937,     0,   926,     0,     0,   825,   822,   934,
     939,     0,     0,   824,   834,   836
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371,    -3, -1371,  -593, -1371,
     439, -1371, -1371, -1371, -1371,   398, -1371,  -319, -1371, -1371,
   -1371,   -71, -1371, -1371, -1371, -1371, -1371, -1371, -1371,   341,
     643, -1371, -1371,   -61,   -38,   -25,     5,    22,    37,   -57,
     -55,   -18,    39,    40,    41,    47, -1371,    52,    53,    55,
      59, -1371, -1371,    65, -1371,    67, -1371,    69,    70,    71,
   -1371, -1371,    72,    73, -1371,    75, -1371,    77, -1371, -1371,
   -1371, -1371, -1371,    85, -1371,    88, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371,   422,   637, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,   343, -1371,
     115, -1371,  -720,   122, -1371, -1371, -1370, -1371, -1364, -1371,
   -1371, -1371, -1371,   -40, -1371,  -754, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,  -771,
   -1371,  -762, -1371,  -757, -1371, -1371, -1371, -1371, -1371, -1371,
     102, -1371, -1371, -1371, -1371, -1371, -1371, -1371,   103,  -746,
   -1371, -1371, -1371, -1371,   104, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371,    74, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
      89, -1371, -1371, -1371,   105,   601, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371,    84, -1371, -1371, -1371, -1371, -1371, -1371,
   -1038, -1371, -1371, -1371,   123, -1371, -1371, -1371,   117,   636,
   -1371, -1371, -1037, -1371, -1036, -1371,    78, -1371,    94, -1371,
      96, -1371,    90,    91,    93, -1371, -1030, -1371, -1371, -1371,
   -1371,   113, -1371, -1371,  -137,  1103, -1371, -1371, -1371, -1371,
   -1371,   129, -1371, -1371, -1371,   125, -1371,   614, -1371,   -65,
   -1371, -1371, -1371, -1371, -1371,   -60, -1371, -1371, -1371, -1371,
   -1371,    12, -1371, -1371, -1371,   131, -1371, -1371, -1371,   135,
   -1371,   609, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371,    50, -1371, -1371, -1371,
      61,   645, -1371, -1371,   -64,   -45, -1371,   -14, -1371, -1371,
   -1371, -1371, -1371,    58, -1371, -1371, -1371,    51,   644, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371,   -56, -1371, -1371, -1371,
     111, -1371, -1371, -1371,   119, -1371,   638,   406, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1025, -1371, -1371, -1371, -1371, -1371,   137,
   -1371, -1371, -1371,  -128, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371,   106, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
      86, -1371,    87,    95, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371,  -177, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,  -214, -1371,
   -1371,  -241, -1371, -1371, -1371, -1371, -1371, -1371, -1371,    92,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
     427,   617, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,   478,
     618, -1371, -1371, -1371, -1371, -1371, -1371,   108, -1371, -1371,
    -133, -1371, -1371, -1371, -1371, -1371, -1371,  -183, -1371, -1371,
    -209, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371, -1371,
   -1371,   107, -1371
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     765,    87,    88,    41,    68,    84,    85,   786,  1011,  1128,
    1129,   848,    43,    70,    90,   448,    91,    45,    71,   162,
     163,   164,   451,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   477,   750,   183,   478,   184,   479,   185,   186,   187,
     490,   762,   188,   189,   512,   190,   513,   191,   192,   193,
     194,   471,   195,   196,   488,   197,   489,   198,   199,   200,
     201,   453,    47,    72,   238,   239,   240,   522,   241,   242,
     243,   244,   202,   454,   203,   455,   204,   456,   875,   876,
     877,  1050,   849,   850,   851,  1026,   852,  1027,   853,  1028,
     854,  1029,   855,   856,   565,   857,   858,   859,   860,   861,
     862,   863,   864,   865,  1040,  1307,   866,   867,   868,   869,
    1043,   870,  1044,   871,  1045,   872,  1046,   205,   500,   910,
     911,   912,  1070,   913,  1071,   206,   497,   896,   897,   898,
     899,   207,   499,   904,   905,   906,   907,   208,   498,   209,
     507,   959,   960,   961,   962,   963,   210,   503,   922,   923,
     924,  1080,    63,    80,   412,   413,   414,   580,   415,   581,
     211,   504,   931,   932,   933,   934,   935,   936,   937,   938,
     212,   484,   879,   880,   881,  1053,    49,    73,   287,   288,
     289,   531,   290,   532,   291,   533,   292,   538,   293,   536,
     294,   537,   213,   214,   215,   298,   299,   216,   491,   891,
     892,   893,  1062,  1208,  1209,   217,   485,    57,    77,   883,
     884,   885,  1056,    59,    78,   373,   374,   375,   376,   377,
     378,   379,   564,   380,   568,   381,   567,   382,   383,   569,
     384,   218,   486,   887,   888,   889,  1059,    61,    79,   396,
     397,   398,   399,   400,   573,   401,   402,   403,   404,   405,
     406,   577,   301,   529,  1013,  1014,  1015,  1130,    51,    74,
     314,   315,   316,   542,   317,   219,   492,   220,   493,   304,
     530,  1017,  1018,  1019,  1133,    53,    75,   333,   334,   335,
     546,   336,   337,   548,   338,   339,   221,   502,   918,   919,
     920,  1077,    55,    76,   352,   353,   354,   355,   554,   356,
     555,   357,   556,   358,   557,   359,   558,   360,   559,   361,
     560,   362,   553,   306,   539,  1021,   222,   501,   915,   916,
    1074,  1235,  1236,  1237,  1238,  1239,  1320,  1240,  1321,  1241,
    1242,   223,   505,   948,   949,   950,  1091,  1331,   951,   952,
    1092,   953,   954,   224,   225,   508,   226,   509,   987,   988,
     989,  1111,   978,   979,   980,  1103,  1336,   981,  1104,   982,
    1105,   983,   984,   985,  1107,  1364,  1365,  1366,  1376,  1393,
    1367,  1377,  1368,  1378,  1369,  1379,  1401,  1402,  1403,  1417,
    1434,  1435,  1436,  1445,  1437,  1446,   227,   510,   996,   997,
     998,   999,  1115,  1000,  1001,  1117,   228,   511,    65,    81,
     427,   428,   429,   430,   585,   431,   432,   587,   433,   434,
     435,   590,   820,   436,   591,   229,   452,    67,    82,   439,
     440,   441,   594,   442,   230,   517,  1004,  1005,  1121,  1286,
    1287,  1288,  1289,  1345,  1290,  1343,  1390,  1391,  1397,  1409,
    1410,  1411,  1420,  1412,  1413,  1414,  1415,  1424,   231,   518,
    1008,  1009,  1010
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     161,   237,   258,   309,   325,   348,   973,   371,   392,   411,
     424,   330,   259,    38,   394,   974,   265,   305,   266,   395,
     975,   945,   873,   903,  1198,  1199,  1200,   245,   302,   318,
     331,   350,  1207,   385,   407,   260,   425,  1213,   372,   393,
      31,   894,    32,    30,    33,   409,   410,  1430,   261,  1357,
     764,  1006,   449,  1431,    86,   267,    89,   450,   246,   303,
     319,   332,   351,   520,   386,   408,   160,   426,   521,   126,
     232,   233,   234,   235,   236,   437,   438,  1430,   262,   745,
     746,   747,   748,  1431,   527,   300,   313,   329,   349,   528,
      42,   894,   901,  1404,   902,   263,  1405,  1406,  1407,  1408,
     133,   134,   540,   544,   551,    44,   939,   541,   545,   552,
     264,   832,   268,   269,   270,  1065,   749,    46,  1066,   582,
     271,    48,   828,   829,   583,   272,   273,   443,   274,   764,
     133,   134,   275,    50,   160,    52,   895,    54,   276,    56,
     277,    58,   278,   279,   280,   281,   282,   444,   283,    60,
     284,   364,   310,   326,   955,   956,   957,   592,   285,   133,
     134,   286,   593,   295,   296,    62,   297,    64,   311,   327,
     312,   328,   827,   828,   829,   830,   831,   832,   833,   834,
     835,   836,   837,   838,   839,   840,   841,   133,   134,   445,
     842,   843,   844,   845,   846,   847,   596,    66,  1358,  1359,
    1360,   597,   133,   134,   446,   365,   447,   366,   367,   844,
     845,   846,   368,   369,   370,   818,   819,   127,    98,    99,
     100,   101,   102,   103,   160,  1068,   365,   457,  1069,   133,
     134,   562,   133,   134,   520,   940,   941,   942,   943,  1023,
     320,   321,   322,   323,   324,   133,   134,   127,   365,   561,
     596,   563,   527,  1047,   160,  1024,   127,  1025,  1048,   127,
     409,   410,   254,   255,    34,    35,    36,    37,   256,   308,
     133,   134,   458,  1427,  1428,   133,   134,   307,  1198,  1199,
    1200,   908,   909,   160,   133,   134,  1207,   133,   134,  1075,
     571,  1213,  1076,   365,  1220,  1221,  1222,  1223,  1304,  1305,
    1306,   254,   255,   340,   990,   991,   992,   256,   308,  1122,
     572,   160,  1123,   341,   342,   343,   344,   345,   346,   347,
     133,   134,   903,  1047,   578,   459,   160,  1072,  1049,   966,
    1160,   460,  1073,   967,   968,   969,   970,   461,   973,  1089,
     973,  1096,   945,   971,  1090,  1398,  1097,   974,  1399,   974,
     133,   134,   975,   993,   975,   462,   160,   463,   365,   387,
     366,   367,   388,   389,   390,   792,   793,   464,   465,   160,
     925,   926,   927,   928,   929,   930,   466,   160,  1101,   799,
     800,   801,   802,  1102,  1109,   133,   134,  1118,   592,  1110,
    1125,  1047,  1119,  1120,   160,  1126,  1312,   540,  1316,   160,
     813,   391,  1313,  1317,   582,  1109,   579,  1346,   160,  1327,
    1340,   160,  1347,   544,   551,   600,  1380,   608,  1349,  1350,
    1279,  1381,  1280,  1281,   758,   759,   760,   761,   467,   416,
     417,   418,   419,   420,   421,   422,   423,   609,  1425,   610,
    1447,   598,   599,  1426,   160,  1448,  1328,  1329,  1330,   161,
    1333,  1334,  1335,   468,   469,   470,   237,   472,   473,   474,
     475,   476,   480,   481,   482,   483,   487,   494,   495,   258,
     496,   506,   514,   309,   160,   515,   516,   519,   523,   259,
     325,   524,   245,   265,   305,   266,   525,   330,   526,   534,
     535,   348,   543,   547,   549,   302,   550,   566,   570,   318,
     574,   371,   260,   575,   576,   584,   331,   586,   392,   160,
     588,   589,   595,   246,   394,   261,   601,   350,   602,   395,
     603,   424,   267,   604,   605,   606,   303,   385,   607,   611,
     319,   612,   372,   613,   407,   614,   616,   332,   615,   393,
     617,   618,   619,   620,   621,   262,   622,   425,   351,   623,
     625,   628,   300,   624,   626,   629,   313,   627,   386,   630,
     631,   632,   263,   329,   635,   408,   633,   636,   637,   634,
     638,   639,   640,   641,   349,   642,   643,   264,   426,   268,
     269,   270,   644,   648,   645,   649,   646,   271,   647,   650,
     651,   652,   272,   273,   653,   274,   654,   655,   656,   275,
     657,   658,   659,   660,   661,   276,   662,   277,   663,   278,
     279,   280,   281,   282,   664,   283,   668,   284,   665,   669,
     671,   666,   310,   667,   672,   285,   674,   675,   286,   326,
     295,   296,   673,   297,   677,   678,   679,   680,   311,   681,
     312,   683,   682,   684,   685,   327,   686,   328,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,   687,   689,   690,   692,   161,   694,   693,   237,
     695,   696,   698,   699,   700,   701,   702,   703,   704,   705,
     707,   708,   709,   710,   711,   712,   715,   719,   721,   722,
     725,   727,   730,   731,   733,   245,   736,   713,   737,   743,
     739,   716,   717,   740,   944,   958,   972,   718,   724,   424,
     726,   728,   738,  1007,   741,   742,   753,   729,   754,   755,
     763,   734,   767,    32,   744,   768,   246,   751,   769,   770,
     946,   964,   976,   823,   994,   425,    92,    93,   752,   756,
      94,   771,   757,   772,   766,   773,    95,    96,    97,   774,
     775,   776,   777,   778,   779,   781,   780,   782,   783,   784,
     785,   947,   965,   977,   787,   995,   426,   788,   789,   790,
     791,   795,   794,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   796,   797,   798,   803,   821,   822,   804,
    1030,   805,   806,   128,   129,   130,   131,   807,   808,   874,
     809,   132,   878,   882,   810,   811,   886,   890,   914,   917,
     133,   134,   812,   921,   814,   816,   817,   135,   136,   137,
     138,   139,   140,   141,   986,  1003,   142,  1012,  1016,   341,
    1031,  1032,  1033,  1034,  1035,   143,  1036,  1037,  1038,  1039,
    1041,  1042,  1083,  1052,   144,  1051,  1055,   145,  1054,  1058,
    1057,  1060,  1061,  1063,   146,  1064,  1067,  1078,  1079,  1081,
    1082,  1113,   147,   148,  1084,  1085,  1086,   149,   150,  1087,
    1088,  1093,  1094,  1095,  1098,  1099,  1100,  1106,  1108,  1143,
    1114,  1112,  1116,  1124,   151,  1132,  1131,  1127,   152,  1134,
    1135,  1137,  1136,  1138,  1139,  1140,  1141,  1152,  1155,  1156,
    1157,  1158,  1217,  1218,   153,   154,   155,   156,   157,   158,
    1142,  1144,  1255,  1146,  1145,  1147,  1148,  1256,   159,  1149,
    1150,  1265,  1151,  1266,  1267,  1269,  1275,  1277,  1295,  1325,
    1294,  1153,  1322,  1261,   160,  1314,  1154,  1248,  1249,  1250,
    1251,  1252,  1253,  1257,  1258,  1259,  1315,  1262,  1323,  1263,
    1324,  1268,  1344,  1326,  1339,  1352,  1353,  1370,  1270,  1372,
    1276,  1382,   258,  1274,  1384,   371,  1292,  1300,   392,  1301,
    1302,  1168,   259,  1371,   394,  1303,   265,   305,   266,   395,
    1308,  1169,  1309,  1224,  1310,  1175,   348,  1176,   302,   411,
    1311,   385,  1318,  1225,   407,   260,   372,  1211,  1319,   393,
    1332,  1337,  1197,  1338,  1170,   944,  1341,  1348,   261,  1233,
     958,  1354,   350,  1355,  1231,   267,  1226,  1171,   972,   303,
     972,  1385,   386,  1374,  1177,   408,  1375,  1383,  1212,  1227,
    1282,   946,  1386,  1387,  1007,  1392,   964,  1389,   262,   309,
    1234,  1394,   325,   351,   976,   300,   976,  1172,  1395,   330,
    1396,  1400,  1418,   994,  1210,   263,  1284,  1419,   824,  1228,
    1421,  1283,   947,  1422,  1173,   318,  1232,   965,   331,   349,
     264,  1423,   268,   269,   270,   977,  1229,   977,  1439,  1174,
     271,  1178,  1179,  1180,   995,   272,   273,  1285,   274,  1181,
    1443,  1230,   275,  1449,  1182,  1183,   319,  1184,   276,   332,
     277,  1185,   278,   279,   280,   281,   282,  1186,   283,  1187,
     284,  1188,  1189,  1190,  1191,  1192,  1441,  1193,   285,  1194,
    1201,   286,   313,   295,   296,   329,   297,  1195,  1451,  1450,
    1196,  1442,  1204,  1205,  1440,  1206,  1202,  1452,  1203,  1454,
    1455,   815,   826,   670,   676,  1022,   900,  1161,  1215,  1159,
    1162,  1247,  1216,  1254,  1219,  1264,   688,  1214,  1163,  1351,
     363,  1164,  1297,   723,  1298,  1246,   714,  1165,   720,   691,
    1245,  1296,  1167,  1299,  1166,   697,  1244,  1356,  1272,  1273,
     706,  1020,  1260,  1388,  1271,  1438,  1453,  1002,   310,   732,
    1278,   326,  1243,  1373,   735,  1416,  1444,   825,     0,     0,
       0,     0,     0,     0,   311,     0,   312,   327,     0,   328,
    1291,     0,  1293,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1168,     0,     0,     0,     0,
       0,     0,     0,     0,  1224,  1169,     0,     0,     0,  1175,
       0,  1176,     0,     0,  1225,     0,     0,     0,  1361,     0,
       0,  1211,     0,     0,  1342,  1282,  1197,     0,  1170,     0,
    1233,     0,     0,     0,     0,  1231,     0,  1226,     0,     0,
       0,  1171,     0,     0,  1362,     0,     0,     0,  1177,     0,
    1227,  1284,  1212,     0,     0,     0,  1283,     0,     0,  1361,
       0,  1234,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1172,     0,     0,     0,  1363,     0,     0,  1210,     0,
    1228,     0,  1285,     0,     0,  1362,     0,  1232,  1173,     0,
       0,     0,     0,     0,     0,     0,  1429,  1229,     0,     0,
       0,     0,     0,  1174,     0,  1178,  1179,  1180,     0,     0,
       0,     0,  1230,  1181,     0,     0,  1363,     0,  1182,  1183,
       0,  1184,  1432,     0,     0,  1185,  1429,     0,     0,     0,
       0,  1186,     0,  1187,     0,  1188,  1189,  1190,  1191,  1192,
       0,  1193,     0,  1194,  1201,     0,     0,     0,     0,     0,
       0,  1195,  1432,  1433,  1196,     0,  1204,  1205,     0,  1206,
    1202,     0,  1203,     0,     0,     0,     0,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
       0,     0,     0,  1433,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,     0,     0,   127,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   129,   130,
     131,     0,     0,     0,     0,     0,   247,     0,   248,     0,
       0,     0,     0,     0,   133,   134,   249,   250,   251,   252,
     253,   135,   136,   137,     0,     0,     0,     0,     0,     0,
       0,   254,   255,     0,     0,     0,     0,   256,     0,   143,
       0,     0,     0,     0,     0,     0,     0,   257,     0,     0,
       0,     0,     0,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,     0,     0,     0,     0,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,     0,   127,   365,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   129,   130,   131,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   153,   154,
     133,   134,     0,   250,   251,     0,   253,   135,   136,   137,
       0,     0,     0,     0,     0,     0,     0,   254,   255,     0,
       0,     0,     0,   256,     0,     0,     0,     0,   160,     0,
       0,     0,     0,   257,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   153,   154,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   160
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,   777,    78,    79,    80,
      81,    75,    73,    16,    79,   777,    73,    73,    73,    79,
     777,   775,   742,   769,  1062,  1062,  1062,    72,    73,    74,
      75,    76,  1062,    78,    79,    73,    81,  1062,    78,    79,
       5,   134,     7,     0,     9,   140,   141,  1417,    73,    24,
     643,   214,     3,  1417,   229,    73,    10,     8,    72,    73,
      74,    75,    76,     3,    78,    79,   229,    81,     8,    76,
      16,    17,    18,    19,    20,    13,    14,  1447,    73,   195,
     196,   197,   198,  1447,     3,    73,    74,    75,    76,     8,
       7,   134,   135,   206,   137,    73,   209,   210,   211,   212,
     105,   106,     3,     3,     3,     7,    24,     8,     8,     8,
      73,    29,    73,    73,    73,     3,   232,     7,     6,     3,
      73,     7,    25,    26,     8,    73,    73,     6,    73,   722,
     105,   106,    73,     7,   229,     7,   229,     7,    73,     7,
      73,     7,    73,    73,    73,    73,    73,     3,    73,     7,
      73,    24,    74,    75,   159,   160,   161,     3,    73,   105,
     106,    73,     8,    73,    73,     7,    73,     7,    74,    75,
      74,    75,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,   105,   106,     4,
      42,    43,    44,    45,    46,    47,     3,     7,   173,   174,
     175,     8,   105,   106,     8,    78,     3,    80,    81,    44,
      45,    46,    85,    86,    87,   192,   193,    77,    48,    49,
      50,    51,    52,    53,   229,     3,    78,     4,     6,   105,
     106,     3,   105,   106,     3,   153,   154,   155,   156,     8,
     100,   101,   102,   103,   104,   105,   106,    77,    78,     8,
       3,     8,     3,     3,   229,     8,    77,     8,     8,    77,
     140,   141,   122,   123,   229,   230,   231,   232,   128,   129,
     105,   106,     4,   176,   177,   105,   106,    98,  1316,  1316,
    1316,   119,   120,   229,   105,   106,  1316,   105,   106,     3,
       8,  1316,     6,    78,   124,   125,   126,   127,    39,    40,
      41,   122,   123,   121,   180,   181,   182,   128,   129,     3,
       3,   229,     6,   131,   132,   133,   134,   135,   136,   137,
     105,   106,  1068,     3,     8,     4,   229,     3,     8,   164,
    1050,     4,     8,   168,   169,   170,   171,     4,  1109,     3,
    1111,     3,  1096,   178,     8,     3,     8,  1109,     6,  1111,
     105,   106,  1109,   229,  1111,     4,   229,     4,    78,    79,
      80,    81,    82,    83,    84,   684,   685,     4,     4,   229,
     143,   144,   145,   146,   147,   148,     4,   229,     3,   698,
     699,   700,   701,     8,     3,   105,   106,     3,     3,     8,
       3,     3,     8,     8,   229,     8,     8,     3,     3,   229,
     719,   121,     8,     8,     3,     3,     3,     3,   229,     8,
       8,   229,     8,     3,     3,   229,     3,   230,     8,     8,
     205,     8,   207,   208,    92,    93,    94,    95,     4,   184,
     185,   186,   187,   188,   189,   190,   191,   230,     3,   230,
       3,   444,   445,     8,   229,     8,   150,   151,   152,   520,
     165,   166,   167,     4,     4,     4,   527,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   540,
       4,     4,     4,   544,   229,     4,     4,     4,     4,   540,
     551,     4,   527,   540,   540,   540,     4,   551,     4,     4,
       4,   562,     4,     4,     4,   540,     4,     4,     4,   544,
       4,   572,   540,     4,     4,     4,   551,     4,   579,   229,
       4,     4,     4,   527,   579,   540,     4,   562,     4,   579,
       4,   592,   540,     4,     4,     4,   540,   572,     4,   230,
     544,   230,   572,   230,   579,   230,   232,   551,   230,   579,
     231,   231,   231,   230,   230,   540,     4,   592,   562,   230,
     232,     4,   540,   230,   232,     4,   544,   232,   572,     4,
     232,   232,   540,   551,     4,   579,   231,     4,     4,   232,
     230,     4,     4,     4,   562,     4,     4,   540,   592,   540,
     540,   540,     4,     4,   232,     4,   232,   540,   232,     4,
       4,     4,   540,   540,     4,   540,     4,     4,     4,   540,
     230,     4,     4,     4,     4,   540,     4,   540,     4,   540,
     540,   540,   540,   540,     4,   540,     4,   540,   232,     4,
       4,   232,   544,   232,   232,   540,   230,   230,   540,   551,
     540,   540,   232,   540,     4,     4,     4,     4,   544,     4,
     544,   232,   230,     4,     4,   551,     4,   551,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,     4,     4,   230,     4,   737,     4,   230,   740,
     230,   230,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   230,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   740,     4,   232,     7,     5,
       7,   232,   232,     7,   775,   776,   777,   232,   232,   780,
     230,   230,   229,   784,     7,     7,     5,   230,     5,     5,
       5,   230,     5,     7,   229,     5,   740,   229,     5,     7,
     775,   776,   777,   736,   779,   780,    11,    12,   229,   229,
      15,     5,   229,     5,   229,     5,    21,    22,    23,     7,
       7,     7,     7,     5,     7,   229,     7,   229,     5,     7,
       5,   775,   776,   777,     5,   779,   780,     5,   229,   229,
     229,     7,   229,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,   229,   229,   229,   229,   194,     5,   229,
       4,   229,   229,    88,    89,    90,    91,   229,   229,     7,
     229,    96,     7,     7,   229,   229,     7,     7,     7,     7,
     105,   106,   229,     7,   229,   229,   229,   112,   113,   114,
     115,   116,   117,   118,     7,     7,   121,     7,     7,   131,
       4,     4,     4,     4,     4,   130,     4,     4,     4,     4,
       4,     4,     4,     3,   139,     6,     3,   142,     6,     3,
       6,     6,     3,     6,   149,     3,     6,     6,     3,     6,
       3,     3,   157,   158,     4,     4,     4,   162,   163,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   232,
       4,     6,     4,     4,   179,     3,     6,   229,   183,     6,
       3,     6,     8,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   199,   200,   201,   202,   203,   204,
     230,   230,     4,   230,   232,   230,   230,     4,   213,   230,
     230,     4,   230,     4,     4,     4,     4,     4,     3,     3,
       6,   232,     4,   232,   229,     8,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,     8,   230,     4,   230,
       8,   230,     4,     8,     7,     4,     4,     4,   232,     4,
     230,     5,  1053,   232,     4,  1056,   232,   229,  1059,   229,
     229,  1062,  1053,   230,  1059,   229,  1053,  1053,  1053,  1059,
     229,  1062,   229,  1074,   229,  1062,  1077,  1062,  1053,  1080,
     229,  1056,   229,  1074,  1059,  1053,  1056,  1062,   229,  1059,
     229,   229,  1062,   229,  1062,  1096,   229,   229,  1053,  1074,
    1101,   232,  1077,   232,  1074,  1053,  1074,  1062,  1109,  1053,
    1111,     4,  1056,   229,  1062,  1059,   229,   229,  1062,  1074,
    1121,  1096,     4,     4,  1125,   172,  1101,     7,  1053,  1130,
    1074,   229,  1133,  1077,  1109,  1053,  1111,  1062,   229,  1133,
       5,     7,     6,  1118,  1062,  1053,  1121,     3,   737,  1074,
       4,  1121,  1096,     4,  1062,  1130,  1074,  1101,  1133,  1077,
    1053,     4,  1053,  1053,  1053,  1109,  1074,  1111,     4,  1062,
    1053,  1062,  1062,  1062,  1118,  1053,  1053,  1121,  1053,  1062,
       4,  1074,  1053,   229,  1062,  1062,  1130,  1062,  1053,  1133,
    1053,  1062,  1053,  1053,  1053,  1053,  1053,  1062,  1053,  1062,
    1053,  1062,  1062,  1062,  1062,  1062,   230,  1062,  1053,  1062,
    1062,  1053,  1130,  1053,  1053,  1133,  1053,  1062,     4,   229,
    1062,   230,  1062,  1062,   232,  1062,  1062,     4,  1062,   229,
     229,   722,   740,   520,   527,   822,   768,  1052,  1065,  1047,
    1053,  1082,  1068,  1089,  1072,  1101,   540,  1064,  1055,  1316,
      77,  1056,  1132,   582,  1133,  1080,   572,  1058,   579,   544,
    1079,  1130,  1061,  1135,  1059,   551,  1077,  1325,  1111,  1113,
     562,   795,  1096,  1380,  1109,  1419,  1447,   780,  1130,   592,
    1118,  1133,  1075,  1346,   596,  1398,  1425,   739,    -1,    -1,
      -1,    -1,    -1,    -1,  1130,    -1,  1130,  1133,    -1,  1133,
    1122,    -1,  1125,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1316,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1325,  1316,    -1,    -1,    -1,  1316,
      -1,  1316,    -1,    -1,  1325,    -1,    -1,    -1,  1339,    -1,
      -1,  1316,    -1,    -1,  1277,  1346,  1316,    -1,  1316,    -1,
    1325,    -1,    -1,    -1,    -1,  1325,    -1,  1325,    -1,    -1,
      -1,  1316,    -1,    -1,  1339,    -1,    -1,    -1,  1316,    -1,
    1325,  1346,  1316,    -1,    -1,    -1,  1346,    -1,    -1,  1380,
      -1,  1325,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1316,    -1,    -1,    -1,  1339,    -1,    -1,  1316,    -1,
    1325,    -1,  1346,    -1,    -1,  1380,    -1,  1325,  1316,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1417,  1325,    -1,    -1,
      -1,    -1,    -1,  1316,    -1,  1316,  1316,  1316,    -1,    -1,
      -1,    -1,  1325,  1316,    -1,    -1,  1380,    -1,  1316,  1316,
      -1,  1316,  1417,    -1,    -1,  1316,  1447,    -1,    -1,    -1,
      -1,  1316,    -1,  1316,    -1,  1316,  1316,  1316,  1316,  1316,
      -1,  1316,    -1,  1316,  1316,    -1,    -1,    -1,    -1,    -1,
      -1,  1316,  1447,  1417,  1316,    -1,  1316,  1316,    -1,  1316,
    1316,    -1,  1316,    -1,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    -1,    -1,  1447,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    -1,    -1,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,
      91,    -1,    -1,    -1,    -1,    -1,    97,    -1,    99,    -1,
      -1,    -1,    -1,    -1,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   122,   123,    -1,    -1,    -1,    -1,   128,    -1,   130,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   138,    -1,    -1,
      -1,    -1,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    -1,    77,    78,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    90,    91,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   199,   200,
     105,   106,    -1,   108,   109,    -1,   111,   112,   113,   114,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   122,   123,    -1,
      -1,    -1,    -1,   128,    -1,    -1,    -1,    -1,   229,    -1,
      -1,    -1,    -1,   138,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   199,   200,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   229
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
       0,     5,     7,     9,   229,   230,   231,   232,   249,   250,
     251,   256,     7,   265,     7,   270,     7,   325,     7,   439,
       7,   521,     7,   538,     7,   555,     7,   470,     7,   476,
       7,   500,     7,   415,     7,   661,     7,   680,   257,   252,
     266,   271,   326,   440,   522,   539,   556,   471,   477,   501,
     416,   662,   681,   249,   258,   259,   229,   254,   255,    10,
     267,   269,    11,    12,    15,    21,    22,    23,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    88,    89,
      90,    91,    96,   105,   106,   112,   113,   114,   115,   116,
     117,   118,   121,   130,   139,   142,   149,   157,   158,   162,
     163,   179,   183,   199,   200,   201,   202,   203,   204,   213,
     229,   264,   272,   273,   274,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   296,   298,   300,   301,   302,   305,   306,
     308,   310,   311,   312,   313,   315,   316,   318,   320,   321,
     322,   323,   335,   337,   339,   380,   388,   394,   400,   402,
     409,   423,   433,   455,   456,   457,   460,   468,   494,   528,
     530,   549,   579,   594,   606,   607,   609,   649,   659,   678,
     687,   711,    16,    17,    18,    19,    20,   264,   327,   328,
     329,   331,   332,   333,   334,   528,   530,    97,    99,   107,
     108,   109,   110,   111,   122,   123,   128,   138,   264,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   290,   291,   292,   293,   296,   298,   300,   301,
     302,   305,   306,   308,   310,   316,   318,   441,   442,   443,
     445,   447,   449,   451,   453,   455,   456,   457,   458,   459,
     494,   515,   528,   530,   532,   549,   576,    98,   129,   264,
     449,   451,   453,   494,   523,   524,   525,   527,   528,   530,
     100,   101,   102,   103,   104,   264,   449,   451,   453,   494,
     527,   528,   530,   540,   541,   542,   544,   545,   547,   548,
     121,   131,   132,   133,   134,   135,   136,   137,   264,   494,
     528,   530,   557,   558,   559,   560,   562,   564,   566,   568,
     570,   572,   574,   468,    24,    78,    80,    81,    85,    86,
      87,   264,   356,   478,   479,   480,   481,   482,   483,   484,
     486,   488,   490,   491,   493,   528,   530,    79,    82,    83,
      84,   121,   264,   356,   482,   488,   502,   503,   504,   505,
     506,   508,   509,   510,   511,   512,   513,   528,   530,   140,
     141,   264,   417,   418,   419,   421,   184,   185,   186,   187,
     188,   189,   190,   191,   264,   528,   530,   663,   664,   665,
     666,   668,   669,   671,   672,   673,   676,    13,    14,   682,
     683,   684,   686,     6,     3,     4,     8,     3,   268,     3,
       8,   275,   679,   324,   336,   338,   340,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   314,     4,     4,     4,     4,     4,   294,   297,   299,
       4,     4,     4,     4,   434,   469,   495,     4,   317,   319,
     303,   461,   529,   531,     4,     4,     4,   389,   401,   395,
     381,   580,   550,   410,   424,   595,     4,   403,   608,   610,
     650,   660,   307,   309,     4,     4,     4,   688,   712,     4,
       3,     8,   330,     4,     4,     4,     4,     3,     8,   516,
     533,   444,   446,   448,     4,     4,   452,   454,   450,   577,
       3,     8,   526,     4,     3,     8,   543,     4,   546,     4,
       4,     3,     8,   575,   561,   563,   565,   567,   569,   571,
     573,     8,     3,     8,   485,   357,     4,   489,   487,   492,
       4,     8,     3,   507,     4,     4,     4,   514,     8,     3,
     420,   422,     3,     8,     4,   667,     4,   670,     4,     4,
     674,   677,     3,     8,   685,     4,     3,     8,   249,   249,
     229,     4,     4,     4,     4,     4,     4,     4,   230,   230,
     230,   230,   230,   230,   230,   230,   232,   231,   231,   231,
     230,   230,     4,   230,   230,   232,   232,   232,     4,     4,
       4,   232,   232,   231,   232,     4,     4,     4,   230,     4,
       4,     4,     4,     4,     4,   232,   232,   232,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   230,     4,     4,
       4,     4,     4,     4,     4,   232,   232,   232,     4,     4,
     273,     4,   232,   232,   230,   230,   328,     4,     4,     4,
       4,     4,   230,   232,     4,     4,     4,     4,   442,     4,
     230,   524,     4,   230,     4,   230,   230,   541,     4,     4,
       4,     4,     4,     4,     4,     4,   559,     4,     4,   230,
       4,     4,     4,   232,   480,     4,   232,   232,   232,     4,
     504,     4,     4,   418,   232,     4,   230,     4,   230,   230,
       4,     4,   664,     4,   230,   683,     4,     7,   229,     7,
       7,     7,     7,     5,   229,   195,   196,   197,   198,   232,
     295,   229,   229,     5,     5,     5,   229,   229,    92,    93,
      94,    95,   304,     5,   251,   253,   229,     5,     5,     5,
       7,     5,     5,     5,     7,     7,     7,     7,     5,     7,
       7,   229,   229,     5,     7,     5,   260,     5,     5,   229,
     229,   229,   260,   260,   229,     7,   229,   229,   229,   260,
     260,   260,   260,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   260,   229,   253,   229,   229,   192,   193,
     675,   194,     5,   249,   272,   682,   327,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    42,    43,    44,    45,    46,    47,   264,   345,
     346,   347,   349,   351,   353,   355,   356,   358,   359,   360,
     361,   362,   363,   364,   365,   366,   369,   370,   371,   372,
     374,   376,   378,   345,     7,   341,   342,   343,     7,   435,
     436,   437,     7,   472,   473,   474,     7,   496,   497,   498,
       7,   462,   463,   464,   134,   229,   390,   391,   392,   393,
     258,   135,   137,   392,   396,   397,   398,   399,   119,   120,
     382,   383,   384,   386,     7,   581,   582,     7,   551,   552,
     553,     7,   411,   412,   413,   143,   144,   145,   146,   147,
     148,   425,   426,   427,   428,   429,   430,   431,   432,    24,
     153,   154,   155,   156,   264,   358,   528,   530,   596,   597,
     598,   601,   602,   604,   605,   159,   160,   161,   264,   404,
     405,   406,   407,   408,   528,   530,   164,   168,   169,   170,
     171,   178,   264,   372,   374,   376,   528,   530,   615,   616,
     617,   620,   622,   624,   625,   626,     7,   611,   612,   613,
     180,   181,   182,   229,   528,   530,   651,   652,   653,   654,
     656,   657,   663,     7,   689,   690,   214,   264,   713,   714,
     715,   261,     7,   517,   518,   519,     7,   534,   535,   536,
     560,   578,   341,     8,     8,     8,   348,   350,   352,   354,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     367,     4,     4,   373,   375,   377,   379,     3,     8,     8,
     344,     6,     3,   438,     6,     3,   475,     6,     3,   499,
       6,     3,   465,     6,     3,     3,     6,     6,     3,     6,
     385,   387,     3,     8,   583,     3,     6,   554,     6,     3,
     414,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,   599,   603,     4,     4,     4,     3,     8,     4,     4,
       4,     3,     8,   618,   621,   623,     4,   627,     4,     3,
       8,   614,     6,     3,     4,   655,     4,   658,     3,     8,
       8,   691,     3,     6,     4,     3,     8,   229,   262,   263,
     520,     6,     3,   537,     6,     3,     8,     6,     4,     4,
       4,     4,   230,   232,   230,   232,   230,   230,   230,   230,
     230,   230,     4,   232,   230,     4,     4,     4,     4,   346,
     345,   343,   441,   437,   478,   474,   502,   498,   264,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   290,   291,   292,   293,   296,   298,   300,   301,
     302,   305,   306,   308,   310,   316,   318,   356,   433,   445,
     447,   449,   451,   453,   455,   456,   457,   459,   466,   467,
     494,   528,   530,   576,   464,   391,   397,     4,     4,   383,
     124,   125,   126,   127,   264,   276,   277,   278,   279,   280,
     281,   356,   494,   528,   530,   584,   585,   586,   587,   588,
     590,   592,   593,   582,   557,   553,   417,   413,   230,   230,
     230,   230,   230,   230,   426,     4,     4,   230,   230,   230,
     597,   232,   230,   230,   405,     4,     4,     4,   230,     4,
     232,   616,   615,   613,   232,     4,   230,     4,   652,   205,
     207,   208,   264,   356,   528,   530,   692,   693,   694,   695,
     697,   690,   232,   714,     6,     3,   523,   519,   540,   536,
     229,   229,   229,   229,    39,    40,    41,   368,   229,   229,
     229,   229,     8,     8,     8,     8,     3,     8,   229,   229,
     589,   591,     4,     4,     8,     3,     8,     8,   150,   151,
     152,   600,   229,   165,   166,   167,   619,   229,   229,     7,
       8,   229,   249,   698,     4,   696,     3,     8,   229,     8,
       8,   467,     4,     4,   232,   232,   586,    24,   173,   174,
     175,   264,   528,   530,   628,   629,   630,   633,   635,   637,
       4,   230,     4,   693,   229,   229,   631,   634,   636,   638,
       3,     8,     5,   229,     4,     4,     4,     4,   629,     7,
     699,   700,   172,   632,   229,   229,     5,   701,     3,     6,
       7,   639,   640,   641,   206,   209,   210,   211,   212,   702,
     703,   704,   706,   707,   708,   709,   700,   642,     6,     3,
     705,     4,     4,     4,   710,     3,     8,   176,   177,   264,
     349,   351,   528,   530,   643,   644,   645,   647,   641,     4,
     232,   230,   230,     4,   703,   646,   648,     3,     8,   229,
     229,     4,     4,   644,   229,   229
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   233,   235,   234,   236,   234,   237,   234,   238,   234,
     239,   234,   240,   234,   241,   234,   242,   234,   243,   234,
     244,   234,   245,   234,   246,   234,   247,   234,   248,   234,
     249,   249,   249,   249,   249,   249,   249,   250,   252,   251,
     253,   254,   254,   255,   255,   255,   257,   256,   258,   258,
     259,   259,   259,   261,   260,   262,   262,   263,   263,   263,
     264,   266,   265,   268,   267,   267,   269,   271,   270,   272,
     272,   272,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   275,   274,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     294,   293,   295,   295,   295,   295,   295,   297,   296,   299,
     298,   300,   301,   303,   302,   304,   304,   304,   304,   305,
     307,   306,   309,   308,   310,   311,   312,   314,   313,   315,
     317,   316,   319,   318,   320,   321,   322,   324,   323,   326,
     325,   327,   327,   327,   328,   328,   328,   328,   328,   328,
     328,   328,   330,   329,   331,   332,   333,   334,   336,   335,
     338,   337,   340,   339,   341,   341,   342,   342,   342,   344,
     343,   345,   345,   345,   346,   346,   346,   346,   346,   346,
     346,   346,   346,   346,   346,   346,   346,   346,   346,   346,
     346,   346,   346,   346,   346,   346,   346,   348,   347,   350,
     349,   352,   351,   354,   353,   355,   357,   356,   358,   359,
     360,   361,   362,   363,   364,   365,   367,   366,   368,   368,
     368,   369,   370,   371,   373,   372,   375,   374,   377,   376,
     379,   378,   381,   380,   382,   382,   382,   383,   383,   385,
     384,   387,   386,   389,   388,   390,   390,   390,   391,   391,
     392,   393,   395,   394,   396,   396,   396,   397,   397,   397,
     398,   399,   401,   400,   403,   402,   404,   404,   404,   405,
     405,   405,   405,   405,   405,   406,   407,   408,   410,   409,
     411,   411,   412,   412,   412,   414,   413,   416,   415,   417,
     417,   417,   417,   418,   418,   420,   419,   422,   421,   424,
     423,   425,   425,   425,   426,   426,   426,   426,   426,   426,
     427,   428,   429,   430,   431,   432,   434,   433,   435,   435,
     436,   436,   436,   438,   437,   440,   439,   441,   441,   441,
     442,   442,   442,   442,   442,   442,   442,   442,   442,   442,
     442,   442,   442,   442,   442,   442,   442,   442,   442,   442,
     442,   442,   442,   442,   442,   442,   442,   442,   442,   442,
     442,   442,   442,   442,   442,   442,   442,   442,   442,   442,
     442,   442,   442,   442,   442,   442,   442,   444,   443,   446,
     445,   448,   447,   450,   449,   452,   451,   454,   453,   455,
     456,   457,   458,   459,   461,   460,   462,   462,   463,   463,
     463,   465,   464,   466,   466,   466,   467,   467,   467,   467,
     467,   467,   467,   467,   467,   467,   467,   467,   467,   467,
     467,   467,   467,   467,   467,   467,   467,   467,   467,   467,
     467,   467,   467,   467,   467,   467,   467,   467,   467,   467,
     467,   467,   467,   467,   467,   467,   467,   467,   467,   467,
     469,   468,   471,   470,   472,   472,   473,   473,   473,   475,
     474,   477,   476,   478,   478,   479,   479,   479,   480,   480,
     480,   480,   480,   480,   480,   480,   480,   480,   481,   482,
     483,   485,   484,   487,   486,   489,   488,   490,   492,   491,
     493,   495,   494,   496,   496,   497,   497,   497,   499,   498,
     501,   500,   502,   502,   503,   503,   503,   504,   504,   504,
     504,   504,   504,   504,   504,   504,   504,   504,   505,   507,
     506,   508,   509,   510,   511,   512,   514,   513,   516,   515,
     517,   517,   518,   518,   518,   520,   519,   522,   521,   523,
     523,   523,   524,   524,   524,   524,   524,   524,   524,   524,
     524,   526,   525,   527,   529,   528,   531,   530,   533,   532,
     534,   534,   535,   535,   535,   537,   536,   539,   538,   540,
     540,   540,   541,   541,   541,   541,   541,   541,   541,   541,
     541,   541,   541,   541,   541,   543,   542,   544,   546,   545,
     547,   548,   550,   549,   551,   551,   552,   552,   552,   554,
     553,   556,   555,   557,   557,   558,   558,   558,   559,   559,
     559,   559,   559,   559,   559,   559,   559,   559,   559,   559,
     561,   560,   563,   562,   565,   564,   567,   566,   569,   568,
     571,   570,   573,   572,   575,   574,   577,   576,   578,   580,
     579,   581,   581,   581,   583,   582,   584,   584,   585,   585,
     585,   586,   586,   586,   586,   586,   586,   586,   586,   586,
     586,   586,   586,   586,   586,   586,   587,   589,   588,   591,
     590,   592,   593,   595,   594,   596,   596,   596,   597,   597,
     597,   597,   597,   597,   597,   597,   597,   599,   598,   600,
     600,   600,   601,   603,   602,   604,   605,   606,   608,   607,
     610,   609,   611,   611,   612,   612,   612,   614,   613,   615,
     615,   615,   616,   616,   616,   616,   616,   616,   616,   616,
     616,   616,   616,   616,   618,   617,   619,   619,   619,   621,
     620,   623,   622,   624,   625,   627,   626,   628,   628,   628,
     629,   629,   629,   629,   629,   629,   629,   631,   630,   632,
     634,   633,   636,   635,   638,   637,   639,   639,   640,   640,
     640,   642,   641,   643,   643,   643,   644,   644,   644,   644,
     644,   644,   644,   646,   645,   648,   647,   650,   649,   651,
     651,   651,   652,   652,   652,   652,   652,   652,   653,   655,
     654,   656,   658,   657,   660,   659,   662,   661,   663,   663,
     663,   664,   664,   664,   664,   664,   664,   664,   664,   664,
     664,   664,   665,   667,   666,   668,   670,   669,   671,   672,
     674,   673,   675,   675,   677,   676,   679,   678,   681,   680,
     682,   682,   682,   683,   683,   685,   684,   686,   688,   687,
     689,   689,   689,   691,   690,   692,   692,   692,   693,   693,
     693,   693,   693,   693,   693,   694,   696,   695,   698,   697,
     699,   699,   699,   701,   700,   702,   702,   702,   703,   703,
     703,   703,   703,   705,   704,   706,   707,   708,   710,   709,
     712,   711,   713,   713,   713,   714,   714,   715
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
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     1,     1,
       1,     3,     3,     3,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     1,     3,     2,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     0,     6,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     1,
       3,     2,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     3,
       3,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     6,     0,     4,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     0,     1,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     0,     4,     0,     4,     0,     4,     1,     0,     4,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     0,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     3,     3,     3,     0,     4,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     4,
       3,     3,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     0,     1,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     1,     0,
       6,     1,     3,     2,     0,     4,     0,     1,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     3,     3,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     3,     0,     4,     3,     3,     3,     0,     6,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     0,
       4,     0,     4,     3,     3,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       0,     4,     0,     4,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     3,     0,     4,     0,     6,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     3,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     0,     6,     0,     4,
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
  "\"type\"", "\"user\"", "\"password\"", "\"host\"", "\"port\"",
  "\"persist\"", "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
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
  "\"client-classes\"", "\"require-client-classes\"",
  "\"evaluate-additional-classes\"", "\"test\"", "\"template-test\"",
  "\"only-if-required\"", "\"only-in-additional-list\"",
  "\"client-class\"", "\"pool-id\"", "\"reservations\"",
  "\"ip-addresses\"", "\"prefixes\"", "\"excluded-prefixes\"", "\"duid\"",
  "\"hw-address\"", "\"hostname\"", "\"flex-id\"", "\"relay\"",
  "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
  "\"expired-leases-processing\"", "\"reclaim-timer-wait-time\"",
  "\"flush-reclaimed-timer-wait-time\"", "\"hold-reclaimed-time\"",
  "\"max-reclaim-leases\"", "\"max-reclaim-time\"",
  "\"unwarned-reclaim-cycles\"", "\"server-id\"", "\"LLT\"", "\"EN\"",
  "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"", "\"enterprise-id\"",
  "\"dhcp4o6-port\"", "\"multi-threading\"", "\"enable-multi-threading\"",
  "\"thread-pool-size\"", "\"packet-queue-size\"", "\"control-socket\"",
  "\"control-sockets\"", "\"socket-type\"", "\"unix\"", "\"http\"",
  "\"https\"", "\"socket-name\"", "\"socket-address\"", "\"socket-port\"",
  "\"authentication\"", "\"basic\"", "\"realm\"", "\"directory\"",
  "\"clients\"", "\"user-file\"", "\"password-file\"", "\"cert-required\"",
  "\"dhcp-queue-control\"", "\"enable-queue\"", "\"queue-type\"",
  "\"capacity\"", "\"dhcp-ddns\"", "\"enable-updates\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"", "\"UDP\"",
  "\"TCP\"", "\"JSON\"", "\"when-present\"", "\"never\"", "\"always\"",
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
  "database_map_param", "database_type", "$@38", "user", "$@39",
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
  "$@67", "require_client_classes", "$@68", "evaluate_additional_classes",
  "$@69", "reservations_global", "reservations_in_subnet",
  "reservations_out_of_pool", "id", "rapid_commit", "shared_networks",
  "$@70", "shared_networks_content", "shared_networks_list",
  "shared_network", "$@71", "shared_network_params",
  "shared_network_param", "option_def_list", "$@72", "sub_option_def_list",
  "$@73", "option_def_list_content", "not_empty_option_def_list",
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
  "option_data_always_send", "option_data_never_send",
  "option_data_client_classes", "$@84", "pools_list", "$@85",
  "pools_list_content", "not_empty_pools_list", "pool_list_entry", "$@86",
  "sub_pool6", "$@87", "pool_params", "pool_param", "pool_entry", "$@88",
  "pool_id", "user_context", "$@89", "comment", "$@90", "pd_pools_list",
  "$@91", "pd_pools_list_content", "not_empty_pd_pools_list",
  "pd_pool_entry", "$@92", "sub_pd_pool", "$@93", "pd_pool_params",
  "pd_pool_param", "pd_prefix", "$@94", "pd_prefix_len", "excluded_prefix",
  "$@95", "excluded_prefix_len", "pd_delegated_len", "reservations",
  "$@96", "reservations_list", "not_empty_reservations_list",
  "reservation", "$@97", "sub_reservation", "$@98", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@99", "prefixes", "$@100", "excluded_prefixes", "$@101", "duid",
  "$@102", "hw_address", "$@103", "hostname", "$@104", "flex_id_value",
  "$@105", "reservation_client_classes", "$@106", "relay", "$@107",
  "relay_map", "client_classes", "$@108", "client_classes_list",
  "client_class_entry", "$@109", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@110",
  "client_class_template_test", "$@111", "only_if_required",
  "only_in_additional_list", "server_id", "$@112", "server_id_params",
  "server_id_param", "server_id_type", "$@113", "duid_type", "htype",
  "identifier", "$@114", "time", "enterprise_id", "dhcp4o6_port",
  "control_socket", "$@115", "control_sockets", "$@116",
  "control_socket_list", "not_empty_control_socket_list",
  "control_socket_entry", "$@117", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@118",
  "control_socket_type_value", "control_socket_name", "$@119",
  "control_socket_address", "$@120", "control_socket_port",
  "cert_required", "authentication", "$@121", "auth_params", "auth_param",
  "auth_type", "$@122", "auth_type_value", "realm", "$@123", "directory",
  "$@124", "clients", "$@125", "clients_list", "not_empty_clients_list",
  "basic_auth", "$@126", "clients_params", "clients_param", "user_file",
  "$@127", "password_file", "$@128", "dhcp_queue_control", "$@129",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@130", "capacity", "arbitrary_map_entry", "$@131",
  "dhcp_ddns", "$@132", "sub_dhcp_ddns", "$@133", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@134", "server_port",
  "sender_ip", "$@135", "sender_port", "max_queue_size", "ncr_protocol",
  "$@136", "ncr_protocol_value", "ncr_format", "$@137", "config_control",
  "$@138", "sub_config_control", "$@139", "config_control_params",
  "config_control_param", "config_databases", "$@140",
  "config_fetch_wait_time", "loggers", "$@141", "loggers_entries",
  "logger_entry", "$@142", "logger_params", "logger_param", "debuglevel",
  "severity", "$@143", "output_options_list", "$@144",
  "output_options_list_content", "output_entry", "$@145",
  "output_params_list", "output_params", "output", "$@146", "flush",
  "maxsize", "maxver", "pattern", "$@147", "compatibility", "$@148",
  "compatibility_params", "compatibility_param", "lenient_option_parsing", YY_NULLPTR
  };
#endif


#if PARSER6_DEBUG
  const short
  Dhcp6Parser::yyrline_[] =
  {
       0,   327,   327,   327,   328,   328,   329,   329,   330,   330,
     331,   331,   332,   332,   333,   333,   334,   334,   335,   335,
     336,   336,   337,   337,   338,   338,   339,   339,   340,   340,
     348,   349,   350,   351,   352,   353,   354,   357,   362,   362,
     373,   376,   377,   380,   385,   391,   396,   396,   403,   404,
     407,   411,   415,   421,   421,   428,   429,   432,   436,   440,
     450,   459,   459,   474,   474,   488,   491,   497,   497,   506,
     507,   508,   515,   516,   517,   518,   519,   520,   521,   522,
     523,   524,   525,   526,   527,   528,   529,   530,   531,   532,
     533,   534,   535,   536,   537,   538,   539,   540,   541,   542,
     543,   544,   545,   546,   547,   548,   549,   550,   551,   552,
     553,   554,   555,   556,   557,   558,   559,   560,   561,   562,
     563,   564,   565,   566,   567,   568,   569,   570,   571,   572,
     573,   574,   575,   576,   577,   578,   579,   580,   581,   582,
     583,   586,   586,   595,   601,   607,   613,   619,   625,   631,
     637,   643,   649,   655,   661,   667,   673,   679,   685,   691,
     697,   697,   706,   709,   712,   715,   718,   724,   724,   733,
     733,   742,   751,   761,   761,   770,   773,   776,   779,   784,
     790,   790,   799,   799,   808,   814,   820,   826,   826,   835,
     841,   841,   850,   850,   859,   865,   871,   877,   877,   889,
     889,   898,   899,   900,   905,   906,   907,   908,   909,   910,
     911,   912,   915,   915,   926,   932,   938,   944,   950,   950,
     963,   963,   976,   976,   987,   988,   991,   992,   993,   998,
     998,  1008,  1009,  1010,  1015,  1016,  1017,  1018,  1019,  1020,
    1021,  1022,  1023,  1024,  1025,  1026,  1027,  1028,  1029,  1030,
    1031,  1032,  1033,  1034,  1035,  1036,  1037,  1040,  1040,  1049,
    1049,  1058,  1058,  1067,  1067,  1076,  1082,  1082,  1091,  1097,
    1103,  1109,  1115,  1121,  1127,  1133,  1139,  1139,  1147,  1148,
    1149,  1152,  1158,  1164,  1170,  1170,  1179,  1179,  1188,  1188,
    1197,  1197,  1206,  1206,  1217,  1218,  1219,  1224,  1225,  1228,
    1228,  1247,  1247,  1265,  1265,  1276,  1277,  1278,  1283,  1284,
    1287,  1292,  1297,  1297,  1308,  1309,  1310,  1315,  1316,  1317,
    1320,  1325,  1332,  1332,  1345,  1345,  1358,  1359,  1360,  1365,
    1366,  1367,  1368,  1369,  1370,  1373,  1379,  1385,  1391,  1391,
    1402,  1403,  1406,  1407,  1408,  1413,  1413,  1423,  1423,  1433,
    1434,  1435,  1438,  1441,  1442,  1445,  1445,  1454,  1454,  1463,
    1463,  1475,  1476,  1477,  1482,  1483,  1484,  1485,  1486,  1487,
    1490,  1496,  1502,  1508,  1514,  1520,  1529,  1529,  1543,  1544,
    1547,  1548,  1549,  1558,  1558,  1584,  1584,  1595,  1596,  1597,
    1603,  1604,  1605,  1606,  1607,  1608,  1609,  1610,  1611,  1612,
    1613,  1614,  1615,  1616,  1617,  1618,  1619,  1620,  1621,  1622,
    1623,  1624,  1625,  1626,  1627,  1628,  1629,  1630,  1631,  1632,
    1633,  1634,  1635,  1636,  1637,  1638,  1639,  1640,  1641,  1642,
    1643,  1644,  1645,  1646,  1647,  1648,  1649,  1652,  1652,  1661,
    1661,  1670,  1670,  1679,  1679,  1689,  1689,  1700,  1700,  1711,
    1717,  1723,  1729,  1735,  1743,  1743,  1755,  1756,  1760,  1761,
    1762,  1767,  1767,  1775,  1776,  1777,  1782,  1783,  1784,  1785,
    1786,  1787,  1788,  1789,  1790,  1791,  1792,  1793,  1794,  1795,
    1796,  1797,  1798,  1799,  1800,  1801,  1802,  1803,  1804,  1805,
    1806,  1807,  1808,  1809,  1810,  1811,  1812,  1813,  1814,  1815,
    1816,  1817,  1818,  1819,  1820,  1821,  1822,  1823,  1824,  1825,
    1832,  1832,  1846,  1846,  1855,  1856,  1859,  1860,  1861,  1868,
    1868,  1883,  1883,  1897,  1898,  1901,  1902,  1903,  1908,  1909,
    1910,  1911,  1912,  1913,  1914,  1915,  1916,  1917,  1920,  1922,
    1928,  1930,  1930,  1939,  1939,  1948,  1948,  1957,  1959,  1959,
    1968,  1978,  1978,  1991,  1992,  1997,  1998,  1999,  2006,  2006,
    2018,  2018,  2030,  2031,  2036,  2037,  2038,  2045,  2046,  2047,
    2048,  2049,  2050,  2051,  2052,  2053,  2054,  2055,  2058,  2060,
    2060,  2069,  2071,  2073,  2079,  2085,  2091,  2091,  2105,  2105,
    2118,  2119,  2122,  2123,  2124,  2129,  2129,  2139,  2139,  2149,
    2150,  2151,  2156,  2157,  2158,  2159,  2160,  2161,  2162,  2163,
    2164,  2167,  2167,  2176,  2182,  2182,  2207,  2207,  2237,  2237,
    2250,  2251,  2254,  2255,  2256,  2261,  2261,  2273,  2273,  2285,
    2286,  2287,  2292,  2293,  2294,  2295,  2296,  2297,  2298,  2299,
    2300,  2301,  2302,  2303,  2304,  2307,  2307,  2316,  2322,  2322,
    2331,  2337,  2346,  2346,  2357,  2358,  2361,  2362,  2363,  2368,
    2368,  2377,  2377,  2386,  2387,  2390,  2391,  2392,  2398,  2399,
    2400,  2401,  2402,  2403,  2404,  2405,  2406,  2407,  2408,  2409,
    2412,  2412,  2423,  2423,  2434,  2434,  2445,  2445,  2454,  2454,
    2463,  2463,  2472,  2472,  2481,  2481,  2495,  2495,  2506,  2512,
    2512,  2523,  2524,  2525,  2530,  2530,  2540,  2541,  2544,  2545,
    2546,  2551,  2552,  2553,  2554,  2555,  2556,  2557,  2558,  2559,
    2560,  2561,  2562,  2563,  2564,  2565,  2568,  2570,  2570,  2579,
    2579,  2589,  2595,  2604,  2604,  2617,  2618,  2619,  2624,  2625,
    2626,  2627,  2628,  2629,  2630,  2631,  2632,  2635,  2635,  2643,
    2644,  2645,  2648,  2654,  2654,  2663,  2669,  2677,  2685,  2685,
    2697,  2697,  2709,  2710,  2713,  2714,  2715,  2720,  2720,  2728,
    2729,  2730,  2735,  2736,  2737,  2738,  2739,  2740,  2741,  2742,
    2743,  2744,  2745,  2746,  2749,  2749,  2758,  2759,  2760,  2763,
    2763,  2773,  2773,  2783,  2789,  2797,  2797,  2810,  2811,  2812,
    2817,  2818,  2819,  2820,  2821,  2822,  2823,  2826,  2826,  2834,
    2837,  2837,  2846,  2846,  2855,  2855,  2866,  2867,  2870,  2871,
    2872,  2877,  2877,  2885,  2886,  2887,  2892,  2893,  2894,  2895,
    2896,  2897,  2898,  2901,  2901,  2910,  2910,  2921,  2921,  2934,
    2935,  2936,  2941,  2942,  2943,  2944,  2945,  2946,  2949,  2955,
    2955,  2964,  2970,  2970,  2980,  2980,  2993,  2993,  3003,  3004,
    3005,  3010,  3011,  3012,  3013,  3014,  3015,  3016,  3017,  3018,
    3019,  3020,  3023,  3029,  3029,  3038,  3044,  3044,  3053,  3059,
    3065,  3065,  3074,  3075,  3078,  3078,  3089,  3089,  3101,  3101,
    3111,  3112,  3113,  3119,  3120,  3123,  3123,  3134,  3142,  3142,
    3155,  3156,  3157,  3163,  3163,  3171,  3172,  3173,  3178,  3179,
    3180,  3181,  3182,  3183,  3184,  3187,  3193,  3193,  3202,  3202,
    3213,  3214,  3215,  3220,  3220,  3228,  3229,  3230,  3235,  3236,
    3237,  3238,  3239,  3242,  3242,  3251,  3257,  3263,  3269,  3269,
    3278,  3278,  3289,  3290,  3291,  3296,  3297,  3300
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
#line 6914 "dhcp6_parser.cc"

#line 3306 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
