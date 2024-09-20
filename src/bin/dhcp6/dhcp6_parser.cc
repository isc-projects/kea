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
#line 316 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 413 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 316 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 419 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 316 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 425 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 316 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 431 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 316 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 437 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 316 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 443 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 316 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 449 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 316 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 455 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 316 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 461 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 316 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 467 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
#line 316 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 473 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 316 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 479 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 316 "dhcp6_parser.yy"
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
#line 325 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 766 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 326 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 772 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 327 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 778 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 328 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 784 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 329 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 790 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 330 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 796 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 331 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 802 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 332 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 808 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 333 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 814 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 334 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 820 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 335 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 826 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 336 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 832 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 337 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 838 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 338 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 844 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 346 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 850 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 347 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 856 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 348 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 862 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 349 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 868 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 350 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 874 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 351 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 880 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 352 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 886 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 355 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 895 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 360 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 906 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 365 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 916 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 371 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 922 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 378 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 932 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 383 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 943 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 389 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 951 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 394 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 960 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 397 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 968 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 405 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 977 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 409 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 986 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 413 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 994 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 419 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 1002 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 421 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1011 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 430 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1020 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 434 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1029 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 438 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1037 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 448 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1048 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 457 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1059 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 462 "dhcp6_parser.yy"
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
#line 472 "dhcp6_parser.yy"
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
#line 481 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1097 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 489 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1105 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 495 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1115 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 499 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1124 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 506 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1132 "dhcp6_parser.cc"
    break;

  case 141: // $@21: %empty
#line 584 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1141 "dhcp6_parser.cc"
    break;

  case 142: // data_directory: "data-directory" $@21 ":" "constant string"
#line 587 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1151 "dhcp6_parser.cc"
    break;

  case 143: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 593 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1161 "dhcp6_parser.cc"
    break;

  case 144: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 599 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1171 "dhcp6_parser.cc"
    break;

  case 145: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 605 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1181 "dhcp6_parser.cc"
    break;

  case 146: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 611 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1191 "dhcp6_parser.cc"
    break;

  case 147: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 617 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1201 "dhcp6_parser.cc"
    break;

  case 148: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 623 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1211 "dhcp6_parser.cc"
    break;

  case 149: // renew_timer: "renew-timer" ":" "integer"
#line 629 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1221 "dhcp6_parser.cc"
    break;

  case 150: // rebind_timer: "rebind-timer" ":" "integer"
#line 635 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1231 "dhcp6_parser.cc"
    break;

  case 151: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 641 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1241 "dhcp6_parser.cc"
    break;

  case 152: // t1_percent: "t1-percent" ":" "floating point"
#line 647 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1251 "dhcp6_parser.cc"
    break;

  case 153: // t2_percent: "t2-percent" ":" "floating point"
#line 653 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1261 "dhcp6_parser.cc"
    break;

  case 154: // cache_threshold: "cache-threshold" ":" "floating point"
#line 659 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1271 "dhcp6_parser.cc"
    break;

  case 155: // cache_max_age: "cache-max-age" ":" "integer"
#line 665 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1281 "dhcp6_parser.cc"
    break;

  case 156: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 671 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1291 "dhcp6_parser.cc"
    break;

  case 157: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 677 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1301 "dhcp6_parser.cc"
    break;

  case 158: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 683 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1311 "dhcp6_parser.cc"
    break;

  case 159: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 689 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1321 "dhcp6_parser.cc"
    break;

  case 160: // $@22: %empty
#line 695 "dhcp6_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1330 "dhcp6_parser.cc"
    break;

  case 161: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 698 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1339 "dhcp6_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "when-present"
#line 704 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1347 "dhcp6_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "never"
#line 707 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1355 "dhcp6_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "always"
#line 710 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1363 "dhcp6_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "when-not-present"
#line 713 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1371 "dhcp6_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "boolean"
#line 716 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1380 "dhcp6_parser.cc"
    break;

  case 167: // $@23: %empty
#line 722 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1389 "dhcp6_parser.cc"
    break;

  case 168: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 725 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1399 "dhcp6_parser.cc"
    break;

  case 169: // $@24: %empty
#line 731 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1408 "dhcp6_parser.cc"
    break;

  case 170: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 734 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1418 "dhcp6_parser.cc"
    break;

  case 171: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 740 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1428 "dhcp6_parser.cc"
    break;

  case 172: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 749 "dhcp6_parser.yy"
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
#line 759 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1451 "dhcp6_parser.cc"
    break;

  case 174: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 762 "dhcp6_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 175: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 768 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1468 "dhcp6_parser.cc"
    break;

  case 176: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 771 "dhcp6_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1476 "dhcp6_parser.cc"
    break;

  case 177: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 774 "dhcp6_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1484 "dhcp6_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 777 "dhcp6_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1492 "dhcp6_parser.cc"
    break;

  case 179: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 782 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1502 "dhcp6_parser.cc"
    break;

  case 180: // $@26: %empty
#line 788 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1511 "dhcp6_parser.cc"
    break;

  case 181: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 791 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1521 "dhcp6_parser.cc"
    break;

  case 182: // $@27: %empty
#line 797 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1530 "dhcp6_parser.cc"
    break;

  case 183: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 800 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1540 "dhcp6_parser.cc"
    break;

  case 184: // store_extended_info: "store-extended-info" ":" "boolean"
#line 806 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1550 "dhcp6_parser.cc"
    break;

  case 185: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 812 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1560 "dhcp6_parser.cc"
    break;

  case 186: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 818 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1570 "dhcp6_parser.cc"
    break;

  case 187: // $@28: %empty
#line 824 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1579 "dhcp6_parser.cc"
    break;

  case 188: // server_tag: "server-tag" $@28 ":" "constant string"
#line 827 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1589 "dhcp6_parser.cc"
    break;

  case 189: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 833 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1599 "dhcp6_parser.cc"
    break;

  case 190: // $@29: %empty
#line 839 "dhcp6_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1608 "dhcp6_parser.cc"
    break;

  case 191: // allocator: "allocator" $@29 ":" "constant string"
#line 842 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1618 "dhcp6_parser.cc"
    break;

  case 192: // $@30: %empty
#line 848 "dhcp6_parser.yy"
                           {
    ctx.unique("pd-allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1627 "dhcp6_parser.cc"
    break;

  case 193: // pd_allocator: "pd-allocator" $@30 ":" "constant string"
#line 851 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-allocator", al);
    ctx.leave();
}
#line 1637 "dhcp6_parser.cc"
    break;

  case 194: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 857 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1647 "dhcp6_parser.cc"
    break;

  case 195: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 863 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1657 "dhcp6_parser.cc"
    break;

  case 196: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 869 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1667 "dhcp6_parser.cc"
    break;

  case 197: // $@31: %empty
#line 875 "dhcp6_parser.yy"
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
#line 881 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1689 "dhcp6_parser.cc"
    break;

  case 199: // $@32: %empty
#line 887 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1699 "dhcp6_parser.cc"
    break;

  case 200: // sub_interfaces6: "{" $@32 interfaces_config_params "}"
#line 891 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1708 "dhcp6_parser.cc"
    break;

  case 203: // interfaces_config_params: interfaces_config_params ","
#line 898 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1716 "dhcp6_parser.cc"
    break;

  case 212: // $@33: %empty
#line 913 "dhcp6_parser.yy"
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
#line 919 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1737 "dhcp6_parser.cc"
    break;

  case 214: // re_detect: "re-detect" ":" "boolean"
#line 924 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1747 "dhcp6_parser.cc"
    break;

  case 215: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 930 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1757 "dhcp6_parser.cc"
    break;

  case 216: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 936 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1767 "dhcp6_parser.cc"
    break;

  case 217: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 942 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1777 "dhcp6_parser.cc"
    break;

  case 218: // $@34: %empty
#line 948 "dhcp6_parser.yy"
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
#line 954 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1800 "dhcp6_parser.cc"
    break;

  case 220: // $@35: %empty
#line 961 "dhcp6_parser.yy"
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
#line 967 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1823 "dhcp6_parser.cc"
    break;

  case 222: // $@36: %empty
#line 974 "dhcp6_parser.yy"
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
#line 980 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1844 "dhcp6_parser.cc"
    break;

  case 228: // not_empty_database_list: not_empty_database_list ","
#line 991 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1852 "dhcp6_parser.cc"
    break;

  case 229: // $@37: %empty
#line 996 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1862 "dhcp6_parser.cc"
    break;

  case 230: // database: "{" $@37 database_map_params "}"
#line 1000 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1872 "dhcp6_parser.cc"
    break;

  case 233: // database_map_params: database_map_params ","
#line 1008 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1880 "dhcp6_parser.cc"
    break;

  case 257: // $@38: %empty
#line 1038 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1889 "dhcp6_parser.cc"
    break;

  case 258: // database_type: "type" $@38 ":" "constant string"
#line 1041 "dhcp6_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 1899 "dhcp6_parser.cc"
    break;

  case 259: // $@39: %empty
#line 1047 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1908 "dhcp6_parser.cc"
    break;

  case 260: // user: "user" $@39 ":" "constant string"
#line 1050 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1918 "dhcp6_parser.cc"
    break;

  case 261: // $@40: %empty
#line 1056 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1927 "dhcp6_parser.cc"
    break;

  case 262: // password: "password" $@40 ":" "constant string"
#line 1059 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1937 "dhcp6_parser.cc"
    break;

  case 263: // $@41: %empty
#line 1065 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1946 "dhcp6_parser.cc"
    break;

  case 264: // host: "host" $@41 ":" "constant string"
#line 1068 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1956 "dhcp6_parser.cc"
    break;

  case 265: // port: "port" ":" "integer"
#line 1074 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1966 "dhcp6_parser.cc"
    break;

  case 266: // $@42: %empty
#line 1080 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1975 "dhcp6_parser.cc"
    break;

  case 267: // name: "name" $@42 ":" "constant string"
#line 1083 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1985 "dhcp6_parser.cc"
    break;

  case 268: // persist: "persist" ":" "boolean"
#line 1089 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1995 "dhcp6_parser.cc"
    break;

  case 269: // lfc_interval: "lfc-interval" ":" "integer"
#line 1095 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2005 "dhcp6_parser.cc"
    break;

  case 270: // readonly: "readonly" ":" "boolean"
#line 1101 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2015 "dhcp6_parser.cc"
    break;

  case 271: // connect_timeout: "connect-timeout" ":" "integer"
#line 1107 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2025 "dhcp6_parser.cc"
    break;

  case 272: // read_timeout: "read-timeout" ":" "integer"
#line 1113 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2035 "dhcp6_parser.cc"
    break;

  case 273: // write_timeout: "write-timeout" ":" "integer"
#line 1119 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2045 "dhcp6_parser.cc"
    break;

  case 274: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1125 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2055 "dhcp6_parser.cc"
    break;

  case 275: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1132 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2065 "dhcp6_parser.cc"
    break;

  case 276: // $@43: %empty
#line 1138 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2074 "dhcp6_parser.cc"
    break;

  case 277: // on_fail: "on-fail" $@43 ":" on_fail_mode
#line 1141 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2083 "dhcp6_parser.cc"
    break;

  case 278: // on_fail_mode: "stop-retry-exit"
#line 1146 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2089 "dhcp6_parser.cc"
    break;

  case 279: // on_fail_mode: "serve-retry-exit"
#line 1147 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2095 "dhcp6_parser.cc"
    break;

  case 280: // on_fail_mode: "serve-retry-continue"
#line 1148 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2101 "dhcp6_parser.cc"
    break;

  case 281: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1151 "dhcp6_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2111 "dhcp6_parser.cc"
    break;

  case 282: // max_row_errors: "max-row-errors" ":" "integer"
#line 1157 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2121 "dhcp6_parser.cc"
    break;

  case 283: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1163 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2131 "dhcp6_parser.cc"
    break;

  case 284: // $@44: %empty
#line 1169 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2140 "dhcp6_parser.cc"
    break;

  case 285: // trust_anchor: "trust-anchor" $@44 ":" "constant string"
#line 1172 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2150 "dhcp6_parser.cc"
    break;

  case 286: // $@45: %empty
#line 1178 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2159 "dhcp6_parser.cc"
    break;

  case 287: // cert_file: "cert-file" $@45 ":" "constant string"
#line 1181 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2169 "dhcp6_parser.cc"
    break;

  case 288: // $@46: %empty
#line 1187 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2178 "dhcp6_parser.cc"
    break;

  case 289: // key_file: "key-file" $@46 ":" "constant string"
#line 1190 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2188 "dhcp6_parser.cc"
    break;

  case 290: // $@47: %empty
#line 1196 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2197 "dhcp6_parser.cc"
    break;

  case 291: // cipher_list: "cipher-list" $@47 ":" "constant string"
#line 1199 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2207 "dhcp6_parser.cc"
    break;

  case 292: // $@48: %empty
#line 1205 "dhcp6_parser.yy"
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
#line 1211 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2228 "dhcp6_parser.cc"
    break;

  case 296: // sanity_checks_params: sanity_checks_params ","
#line 1218 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2236 "dhcp6_parser.cc"
    break;

  case 299: // $@49: %empty
#line 1227 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2245 "dhcp6_parser.cc"
    break;

  case 300: // lease_checks: "lease-checks" $@49 ":" "constant string"
#line 1230 "dhcp6_parser.yy"
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
#line 1246 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2274 "dhcp6_parser.cc"
    break;

  case 302: // extended_info_checks: "extended-info-checks" $@50 ":" "constant string"
#line 1249 "dhcp6_parser.yy"
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
#line 1264 "dhcp6_parser.yy"
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
#line 1270 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2314 "dhcp6_parser.cc"
    break;

  case 307: // mac_sources_list: mac_sources_list ","
#line 1277 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2322 "dhcp6_parser.cc"
    break;

  case 310: // duid_id: "duid"
#line 1286 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2331 "dhcp6_parser.cc"
    break;

  case 311: // string_id: "constant string"
#line 1291 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2340 "dhcp6_parser.cc"
    break;

  case 312: // $@52: %empty
#line 1296 "dhcp6_parser.yy"
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
#line 1302 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2361 "dhcp6_parser.cc"
    break;

  case 316: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1309 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2369 "dhcp6_parser.cc"
    break;

  case 320: // hw_address_id: "hw-address"
#line 1319 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2378 "dhcp6_parser.cc"
    break;

  case 321: // flex_id: "flex-id"
#line 1324 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2387 "dhcp6_parser.cc"
    break;

  case 322: // $@53: %empty
#line 1331 "dhcp6_parser.yy"
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
#line 1337 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2408 "dhcp6_parser.cc"
    break;

  case 324: // $@54: %empty
#line 1344 "dhcp6_parser.yy"
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
#line 1350 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2431 "dhcp6_parser.cc"
    break;

  case 328: // multi_threading_params: multi_threading_params ","
#line 1359 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2439 "dhcp6_parser.cc"
    break;

  case 335: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1372 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2449 "dhcp6_parser.cc"
    break;

  case 336: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1378 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2459 "dhcp6_parser.cc"
    break;

  case 337: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1384 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2469 "dhcp6_parser.cc"
    break;

  case 338: // $@55: %empty
#line 1390 "dhcp6_parser.yy"
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
#line 1396 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2490 "dhcp6_parser.cc"
    break;

  case 344: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1407 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2498 "dhcp6_parser.cc"
    break;

  case 345: // $@56: %empty
#line 1412 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2508 "dhcp6_parser.cc"
    break;

  case 346: // hooks_library: "{" $@56 hooks_params "}"
#line 1416 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2518 "dhcp6_parser.cc"
    break;

  case 347: // $@57: %empty
#line 1422 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2528 "dhcp6_parser.cc"
    break;

  case 348: // sub_hooks_library: "{" $@57 hooks_params "}"
#line 1426 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2538 "dhcp6_parser.cc"
    break;

  case 351: // hooks_params: hooks_params ","
#line 1434 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2546 "dhcp6_parser.cc"
    break;

  case 355: // $@58: %empty
#line 1444 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2555 "dhcp6_parser.cc"
    break;

  case 356: // library: "library" $@58 ":" "constant string"
#line 1447 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2565 "dhcp6_parser.cc"
    break;

  case 357: // $@59: %empty
#line 1453 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2574 "dhcp6_parser.cc"
    break;

  case 358: // parameters: "parameters" $@59 ":" map_value
#line 1456 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2583 "dhcp6_parser.cc"
    break;

  case 359: // $@60: %empty
#line 1462 "dhcp6_parser.yy"
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
#line 1468 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2605 "dhcp6_parser.cc"
    break;

  case 363: // expired_leases_params: expired_leases_params ","
#line 1476 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2613 "dhcp6_parser.cc"
    break;

  case 370: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1489 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2623 "dhcp6_parser.cc"
    break;

  case 371: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1495 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2633 "dhcp6_parser.cc"
    break;

  case 372: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1501 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2643 "dhcp6_parser.cc"
    break;

  case 373: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1507 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2653 "dhcp6_parser.cc"
    break;

  case 374: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1513 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2663 "dhcp6_parser.cc"
    break;

  case 375: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1519 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2673 "dhcp6_parser.cc"
    break;

  case 376: // $@61: %empty
#line 1528 "dhcp6_parser.yy"
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
#line 1534 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2694 "dhcp6_parser.cc"
    break;

  case 382: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1548 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2702 "dhcp6_parser.cc"
    break;

  case 383: // $@62: %empty
#line 1557 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2712 "dhcp6_parser.cc"
    break;

  case 384: // subnet6: "{" $@62 subnet6_params "}"
#line 1561 "dhcp6_parser.yy"
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
#line 1583 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2748 "dhcp6_parser.cc"
    break;

  case 386: // sub_subnet6: "{" $@63 subnet6_params "}"
#line 1587 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2758 "dhcp6_parser.cc"
    break;

  case 389: // subnet6_params: subnet6_params ","
#line 1596 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2766 "dhcp6_parser.cc"
    break;

  case 436: // $@64: %empty
#line 1650 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2775 "dhcp6_parser.cc"
    break;

  case 437: // subnet: "subnet" $@64 ":" "constant string"
#line 1653 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2785 "dhcp6_parser.cc"
    break;

  case 438: // $@65: %empty
#line 1659 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2794 "dhcp6_parser.cc"
    break;

  case 439: // interface: "interface" $@65 ":" "constant string"
#line 1662 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2804 "dhcp6_parser.cc"
    break;

  case 440: // $@66: %empty
#line 1668 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2813 "dhcp6_parser.cc"
    break;

  case 441: // interface_id: "interface-id" $@66 ":" "constant string"
#line 1671 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2823 "dhcp6_parser.cc"
    break;

  case 442: // $@67: %empty
#line 1677 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2832 "dhcp6_parser.cc"
    break;

  case 443: // client_class: "client-class" $@67 ":" "constant string"
#line 1680 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2842 "dhcp6_parser.cc"
    break;

  case 444: // $@68: %empty
#line 1686 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2854 "dhcp6_parser.cc"
    break;

  case 445: // require_client_classes: "require-client-classes" $@68 ":" list_strings
#line 1692 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2863 "dhcp6_parser.cc"
    break;

  case 446: // reservations_global: "reservations-global" ":" "boolean"
#line 1697 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2873 "dhcp6_parser.cc"
    break;

  case 447: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1703 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2883 "dhcp6_parser.cc"
    break;

  case 448: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1709 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2893 "dhcp6_parser.cc"
    break;

  case 449: // id: "id" ":" "integer"
#line 1715 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2903 "dhcp6_parser.cc"
    break;

  case 450: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1721 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2913 "dhcp6_parser.cc"
    break;

  case 451: // $@69: %empty
#line 1729 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2925 "dhcp6_parser.cc"
    break;

  case 452: // shared_networks: "shared-networks" $@69 ":" "[" shared_networks_content "]"
#line 1735 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2934 "dhcp6_parser.cc"
    break;

  case 457: // shared_networks_list: shared_networks_list ","
#line 1748 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2942 "dhcp6_parser.cc"
    break;

  case 458: // $@70: %empty
#line 1753 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2952 "dhcp6_parser.cc"
    break;

  case 459: // shared_network: "{" $@70 shared_network_params "}"
#line 1757 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2960 "dhcp6_parser.cc"
    break;

  case 462: // shared_network_params: shared_network_params ","
#line 1763 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2968 "dhcp6_parser.cc"
    break;

  case 506: // $@71: %empty
#line 1817 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2980 "dhcp6_parser.cc"
    break;

  case 507: // option_def_list: "option-def" $@71 ":" "[" option_def_list_content "]"
#line 1823 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2989 "dhcp6_parser.cc"
    break;

  case 508: // $@72: %empty
#line 1831 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2998 "dhcp6_parser.cc"
    break;

  case 509: // sub_option_def_list: "{" $@72 option_def_list "}"
#line 1834 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 3006 "dhcp6_parser.cc"
    break;

  case 514: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1846 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3014 "dhcp6_parser.cc"
    break;

  case 515: // $@73: %empty
#line 1853 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3024 "dhcp6_parser.cc"
    break;

  case 516: // option_def_entry: "{" $@73 option_def_params "}"
#line 1857 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3036 "dhcp6_parser.cc"
    break;

  case 517: // $@74: %empty
#line 1868 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3046 "dhcp6_parser.cc"
    break;

  case 518: // sub_option_def: "{" $@74 option_def_params "}"
#line 1872 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3058 "dhcp6_parser.cc"
    break;

  case 523: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1888 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3066 "dhcp6_parser.cc"
    break;

  case 535: // code: "code" ":" "integer"
#line 1907 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3076 "dhcp6_parser.cc"
    break;

  case 537: // $@75: %empty
#line 1915 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3085 "dhcp6_parser.cc"
    break;

  case 538: // option_def_type: "type" $@75 ":" "constant string"
#line 1918 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3095 "dhcp6_parser.cc"
    break;

  case 539: // $@76: %empty
#line 1924 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3104 "dhcp6_parser.cc"
    break;

  case 540: // option_def_record_types: "record-types" $@76 ":" "constant string"
#line 1927 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3114 "dhcp6_parser.cc"
    break;

  case 541: // $@77: %empty
#line 1933 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3123 "dhcp6_parser.cc"
    break;

  case 542: // space: "space" $@77 ":" "constant string"
#line 1936 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3133 "dhcp6_parser.cc"
    break;

  case 544: // $@78: %empty
#line 1944 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3142 "dhcp6_parser.cc"
    break;

  case 545: // option_def_encapsulate: "encapsulate" $@78 ":" "constant string"
#line 1947 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3152 "dhcp6_parser.cc"
    break;

  case 546: // option_def_array: "array" ":" "boolean"
#line 1953 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3162 "dhcp6_parser.cc"
    break;

  case 547: // $@79: %empty
#line 1963 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3174 "dhcp6_parser.cc"
    break;

  case 548: // option_data_list: "option-data" $@79 ":" "[" option_data_list_content "]"
#line 1969 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3183 "dhcp6_parser.cc"
    break;

  case 553: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1984 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3191 "dhcp6_parser.cc"
    break;

  case 554: // $@80: %empty
#line 1991 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3201 "dhcp6_parser.cc"
    break;

  case 555: // option_data_entry: "{" $@80 option_data_params "}"
#line 1995 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3210 "dhcp6_parser.cc"
    break;

  case 556: // $@81: %empty
#line 2003 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3220 "dhcp6_parser.cc"
    break;

  case 557: // sub_option_data: "{" $@81 option_data_params "}"
#line 2007 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3229 "dhcp6_parser.cc"
    break;

  case 562: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2023 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3237 "dhcp6_parser.cc"
    break;

  case 574: // $@82: %empty
#line 2044 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3246 "dhcp6_parser.cc"
    break;

  case 575: // option_data_data: "data" $@82 ":" "constant string"
#line 2047 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3256 "dhcp6_parser.cc"
    break;

  case 578: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2057 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3266 "dhcp6_parser.cc"
    break;

  case 579: // option_data_always_send: "always-send" ":" "boolean"
#line 2063 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3276 "dhcp6_parser.cc"
    break;

  case 580: // option_data_never_send: "never-send" ":" "boolean"
#line 2069 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3286 "dhcp6_parser.cc"
    break;

  case 581: // $@83: %empty
#line 2078 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3298 "dhcp6_parser.cc"
    break;

  case 582: // pools_list: "pools" $@83 ":" "[" pools_list_content "]"
#line 2084 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3307 "dhcp6_parser.cc"
    break;

  case 587: // not_empty_pools_list: not_empty_pools_list ","
#line 2097 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3315 "dhcp6_parser.cc"
    break;

  case 588: // $@84: %empty
#line 2102 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3325 "dhcp6_parser.cc"
    break;

  case 589: // pool_list_entry: "{" $@84 pool_params "}"
#line 2106 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3335 "dhcp6_parser.cc"
    break;

  case 590: // $@85: %empty
#line 2112 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3345 "dhcp6_parser.cc"
    break;

  case 591: // sub_pool6: "{" $@85 pool_params "}"
#line 2116 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3355 "dhcp6_parser.cc"
    break;

  case 594: // pool_params: pool_params ","
#line 2124 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3363 "dhcp6_parser.cc"
    break;

  case 603: // $@86: %empty
#line 2139 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3372 "dhcp6_parser.cc"
    break;

  case 604: // pool_entry: "pool" $@86 ":" "constant string"
#line 2142 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3382 "dhcp6_parser.cc"
    break;

  case 605: // pool_id: "pool-id" ":" "integer"
#line 2148 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3392 "dhcp6_parser.cc"
    break;

  case 606: // $@87: %empty
#line 2154 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3400 "dhcp6_parser.cc"
    break;

  case 607: // user_context: "user-context" $@87 ":" map_value
#line 2156 "dhcp6_parser.yy"
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
#line 3427 "dhcp6_parser.cc"
    break;

  case 608: // $@88: %empty
#line 2179 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3435 "dhcp6_parser.cc"
    break;

  case 609: // comment: "comment" $@88 ":" "constant string"
#line 2181 "dhcp6_parser.yy"
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
#line 3464 "dhcp6_parser.cc"
    break;

  case 610: // $@89: %empty
#line 2209 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3476 "dhcp6_parser.cc"
    break;

  case 611: // pd_pools_list: "pd-pools" $@89 ":" "[" pd_pools_list_content "]"
#line 2215 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3485 "dhcp6_parser.cc"
    break;

  case 616: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2228 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3493 "dhcp6_parser.cc"
    break;

  case 617: // $@90: %empty
#line 2233 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3503 "dhcp6_parser.cc"
    break;

  case 618: // pd_pool_entry: "{" $@90 pd_pool_params "}"
#line 2237 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3515 "dhcp6_parser.cc"
    break;

  case 619: // $@91: %empty
#line 2245 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3525 "dhcp6_parser.cc"
    break;

  case 620: // sub_pd_pool: "{" $@91 pd_pool_params "}"
#line 2249 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3537 "dhcp6_parser.cc"
    break;

  case 623: // pd_pool_params: pd_pool_params ","
#line 2259 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3545 "dhcp6_parser.cc"
    break;

  case 636: // $@92: %empty
#line 2278 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3554 "dhcp6_parser.cc"
    break;

  case 637: // pd_prefix: "prefix" $@92 ":" "constant string"
#line 2281 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3564 "dhcp6_parser.cc"
    break;

  case 638: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2287 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3574 "dhcp6_parser.cc"
    break;

  case 639: // $@93: %empty
#line 2293 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3583 "dhcp6_parser.cc"
    break;

  case 640: // excluded_prefix: "excluded-prefix" $@93 ":" "constant string"
#line 2296 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3593 "dhcp6_parser.cc"
    break;

  case 641: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2302 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3603 "dhcp6_parser.cc"
    break;

  case 642: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2308 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3613 "dhcp6_parser.cc"
    break;

  case 643: // $@94: %empty
#line 2317 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3625 "dhcp6_parser.cc"
    break;

  case 644: // reservations: "reservations" $@94 ":" "[" reservations_list "]"
#line 2323 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3634 "dhcp6_parser.cc"
    break;

  case 649: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2334 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3642 "dhcp6_parser.cc"
    break;

  case 650: // $@95: %empty
#line 2339 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3652 "dhcp6_parser.cc"
    break;

  case 651: // reservation: "{" $@95 reservation_params "}"
#line 2343 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3661 "dhcp6_parser.cc"
    break;

  case 652: // $@96: %empty
#line 2348 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3671 "dhcp6_parser.cc"
    break;

  case 653: // sub_reservation: "{" $@96 reservation_params "}"
#line 2352 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3680 "dhcp6_parser.cc"
    break;

  case 658: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2363 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3688 "dhcp6_parser.cc"
    break;

  case 671: // $@97: %empty
#line 2383 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3700 "dhcp6_parser.cc"
    break;

  case 672: // ip_addresses: "ip-addresses" $@97 ":" list_strings
#line 2389 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3709 "dhcp6_parser.cc"
    break;

  case 673: // $@98: %empty
#line 2394 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3721 "dhcp6_parser.cc"
    break;

  case 674: // prefixes: "prefixes" $@98 ":" list_strings
#line 2400 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3730 "dhcp6_parser.cc"
    break;

  case 675: // $@99: %empty
#line 2405 "dhcp6_parser.yy"
                                     {
    ctx.unique("excluded-prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3742 "dhcp6_parser.cc"
    break;

  case 676: // excluded_prefixes: "excluded-prefixes" $@99 ":" list_strings
#line 2411 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3751 "dhcp6_parser.cc"
    break;

  case 677: // $@100: %empty
#line 2416 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3760 "dhcp6_parser.cc"
    break;

  case 678: // duid: "duid" $@100 ":" "constant string"
#line 2419 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3770 "dhcp6_parser.cc"
    break;

  case 679: // $@101: %empty
#line 2425 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3779 "dhcp6_parser.cc"
    break;

  case 680: // hw_address: "hw-address" $@101 ":" "constant string"
#line 2428 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3789 "dhcp6_parser.cc"
    break;

  case 681: // $@102: %empty
#line 2434 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3798 "dhcp6_parser.cc"
    break;

  case 682: // hostname: "hostname" $@102 ":" "constant string"
#line 2437 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3808 "dhcp6_parser.cc"
    break;

  case 683: // $@103: %empty
#line 2443 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3817 "dhcp6_parser.cc"
    break;

  case 684: // flex_id_value: "flex-id" $@103 ":" "constant string"
#line 2446 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3827 "dhcp6_parser.cc"
    break;

  case 685: // $@104: %empty
#line 2452 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3839 "dhcp6_parser.cc"
    break;

  case 686: // reservation_client_classes: "client-classes" $@104 ":" list_strings
#line 2458 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3848 "dhcp6_parser.cc"
    break;

  case 687: // $@105: %empty
#line 2466 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3860 "dhcp6_parser.cc"
    break;

  case 688: // relay: "relay" $@105 ":" "{" relay_map "}"
#line 2472 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3869 "dhcp6_parser.cc"
    break;

  case 690: // $@106: %empty
#line 2483 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3881 "dhcp6_parser.cc"
    break;

  case 691: // client_classes: "client-classes" $@106 ":" "[" client_classes_list "]"
#line 2489 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3890 "dhcp6_parser.cc"
    break;

  case 694: // client_classes_list: client_classes_list ","
#line 2496 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3898 "dhcp6_parser.cc"
    break;

  case 695: // $@107: %empty
#line 2501 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3908 "dhcp6_parser.cc"
    break;

  case 696: // client_class_entry: "{" $@107 client_class_params "}"
#line 2505 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3918 "dhcp6_parser.cc"
    break;

  case 701: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2517 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3926 "dhcp6_parser.cc"
    break;

  case 717: // $@108: %empty
#line 2540 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3935 "dhcp6_parser.cc"
    break;

  case 718: // client_class_test: "test" $@108 ":" "constant string"
#line 2543 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3945 "dhcp6_parser.cc"
    break;

  case 719: // $@109: %empty
#line 2549 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3954 "dhcp6_parser.cc"
    break;

  case 720: // client_class_template_test: "template-test" $@109 ":" "constant string"
#line 2552 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3964 "dhcp6_parser.cc"
    break;

  case 721: // only_if_required: "only-if-required" ":" "boolean"
#line 2558 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3974 "dhcp6_parser.cc"
    break;

  case 722: // $@110: %empty
#line 2567 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3986 "dhcp6_parser.cc"
    break;

  case 723: // server_id: "server-id" $@110 ":" "{" server_id_params "}"
#line 2573 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3997 "dhcp6_parser.cc"
    break;

  case 726: // server_id_params: server_id_params ","
#line 2582 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4005 "dhcp6_parser.cc"
    break;

  case 736: // $@111: %empty
#line 2598 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 4014 "dhcp6_parser.cc"
    break;

  case 737: // server_id_type: "type" $@111 ":" duid_type
#line 2601 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4023 "dhcp6_parser.cc"
    break;

  case 738: // duid_type: "LLT"
#line 2606 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4029 "dhcp6_parser.cc"
    break;

  case 739: // duid_type: "EN"
#line 2607 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4035 "dhcp6_parser.cc"
    break;

  case 740: // duid_type: "LL"
#line 2608 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4041 "dhcp6_parser.cc"
    break;

  case 741: // htype: "htype" ":" "integer"
#line 2611 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4051 "dhcp6_parser.cc"
    break;

  case 742: // $@112: %empty
#line 2617 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4060 "dhcp6_parser.cc"
    break;

  case 743: // identifier: "identifier" $@112 ":" "constant string"
#line 2620 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4070 "dhcp6_parser.cc"
    break;

  case 744: // time: "time" ":" "integer"
#line 2626 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4080 "dhcp6_parser.cc"
    break;

  case 745: // enterprise_id: "enterprise-id" ":" "integer"
#line 2632 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4090 "dhcp6_parser.cc"
    break;

  case 746: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2640 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4100 "dhcp6_parser.cc"
    break;

  case 747: // $@113: %empty
#line 2648 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4113 "dhcp6_parser.cc"
    break;

  case 748: // control_socket: "control-socket" $@113 ":" "{" control_socket_params "}"
#line 2655 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4122 "dhcp6_parser.cc"
    break;

  case 749: // $@114: %empty
#line 2660 "dhcp6_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4135 "dhcp6_parser.cc"
    break;

  case 750: // control_sockets: "control-sockets" $@114 ":" "[" control_socket_list "]"
#line 2667 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4144 "dhcp6_parser.cc"
    break;

  case 755: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2678 "dhcp6_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4152 "dhcp6_parser.cc"
    break;

  case 756: // $@115: %empty
#line 2683 "dhcp6_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4162 "dhcp6_parser.cc"
    break;

  case 757: // control_socket_entry: "{" $@115 control_socket_params "}"
#line 2687 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4170 "dhcp6_parser.cc"
    break;

  case 760: // control_socket_params: control_socket_params ","
#line 2693 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4178 "dhcp6_parser.cc"
    break;

  case 773: // $@116: %empty
#line 2712 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4187 "dhcp6_parser.cc"
    break;

  case 774: // control_socket_type: "socket-type" $@116 ":" control_socket_type_value
#line 2715 "dhcp6_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4196 "dhcp6_parser.cc"
    break;

  case 775: // control_socket_type_value: "unix"
#line 2721 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4202 "dhcp6_parser.cc"
    break;

  case 776: // control_socket_type_value: "http"
#line 2722 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4208 "dhcp6_parser.cc"
    break;

  case 777: // control_socket_type_value: "https"
#line 2723 "dhcp6_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4214 "dhcp6_parser.cc"
    break;

  case 778: // $@117: %empty
#line 2726 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4224 "dhcp6_parser.cc"
    break;

  case 779: // control_socket_name: "socket-name" $@117 ":" "constant string"
#line 2730 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4234 "dhcp6_parser.cc"
    break;

  case 780: // $@118: %empty
#line 2736 "dhcp6_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4244 "dhcp6_parser.cc"
    break;

  case 781: // control_socket_address: "socket-address" $@118 ":" "constant string"
#line 2740 "dhcp6_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4254 "dhcp6_parser.cc"
    break;

  case 782: // control_socket_port: "socket-port" ":" "integer"
#line 2746 "dhcp6_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4264 "dhcp6_parser.cc"
    break;

  case 783: // cert_required: "cert-required" ":" "boolean"
#line 2752 "dhcp6_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4274 "dhcp6_parser.cc"
    break;

  case 784: // $@119: %empty
#line 2760 "dhcp6_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4286 "dhcp6_parser.cc"
    break;

  case 785: // authentication: "authentication" $@119 ":" "{" auth_params "}"
#line 2766 "dhcp6_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4297 "dhcp6_parser.cc"
    break;

  case 788: // auth_params: auth_params ","
#line 2775 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4305 "dhcp6_parser.cc"
    break;

  case 796: // $@120: %empty
#line 2789 "dhcp6_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4314 "dhcp6_parser.cc"
    break;

  case 797: // auth_type: "type" $@120 ":" auth_type_value
#line 2792 "dhcp6_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4323 "dhcp6_parser.cc"
    break;

  case 798: // auth_type_value: "basic"
#line 2797 "dhcp6_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4329 "dhcp6_parser.cc"
    break;

  case 799: // $@121: %empty
#line 2800 "dhcp6_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4338 "dhcp6_parser.cc"
    break;

  case 800: // realm: "realm" $@121 ":" "constant string"
#line 2803 "dhcp6_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4348 "dhcp6_parser.cc"
    break;

  case 801: // $@122: %empty
#line 2809 "dhcp6_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4357 "dhcp6_parser.cc"
    break;

  case 802: // directory: "directory" $@122 ":" "constant string"
#line 2812 "dhcp6_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4367 "dhcp6_parser.cc"
    break;

  case 803: // $@123: %empty
#line 2818 "dhcp6_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4379 "dhcp6_parser.cc"
    break;

  case 804: // clients: "clients" $@123 ":" "[" clients_list "]"
#line 2824 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4388 "dhcp6_parser.cc"
    break;

  case 809: // not_empty_clients_list: not_empty_clients_list ","
#line 2835 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4396 "dhcp6_parser.cc"
    break;

  case 810: // $@124: %empty
#line 2840 "dhcp6_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4406 "dhcp6_parser.cc"
    break;

  case 811: // basic_auth: "{" $@124 clients_params "}"
#line 2844 "dhcp6_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4414 "dhcp6_parser.cc"
    break;

  case 814: // clients_params: clients_params ","
#line 2850 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4422 "dhcp6_parser.cc"
    break;

  case 822: // $@125: %empty
#line 2864 "dhcp6_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4431 "dhcp6_parser.cc"
    break;

  case 823: // user_file: "user-file" $@125 ":" "constant string"
#line 2867 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4441 "dhcp6_parser.cc"
    break;

  case 824: // $@126: %empty
#line 2873 "dhcp6_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4450 "dhcp6_parser.cc"
    break;

  case 825: // password_file: "password-file" $@126 ":" "constant string"
#line 2876 "dhcp6_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4460 "dhcp6_parser.cc"
    break;

  case 826: // $@127: %empty
#line 2884 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4472 "dhcp6_parser.cc"
    break;

  case 827: // dhcp_queue_control: "dhcp-queue-control" $@127 ":" "{" queue_control_params "}"
#line 2890 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4483 "dhcp6_parser.cc"
    break;

  case 830: // queue_control_params: queue_control_params ","
#line 2899 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4491 "dhcp6_parser.cc"
    break;

  case 837: // enable_queue: "enable-queue" ":" "boolean"
#line 2912 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4501 "dhcp6_parser.cc"
    break;

  case 838: // $@128: %empty
#line 2918 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4510 "dhcp6_parser.cc"
    break;

  case 839: // queue_type: "queue-type" $@128 ":" "constant string"
#line 2921 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4520 "dhcp6_parser.cc"
    break;

  case 840: // capacity: "capacity" ":" "integer"
#line 2927 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4530 "dhcp6_parser.cc"
    break;

  case 841: // $@129: %empty
#line 2933 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4539 "dhcp6_parser.cc"
    break;

  case 842: // arbitrary_map_entry: "constant string" $@129 ":" value
#line 2936 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4548 "dhcp6_parser.cc"
    break;

  case 843: // $@130: %empty
#line 2943 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4560 "dhcp6_parser.cc"
    break;

  case 844: // dhcp_ddns: "dhcp-ddns" $@130 ":" "{" dhcp_ddns_params "}"
#line 2949 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4571 "dhcp6_parser.cc"
    break;

  case 845: // $@131: %empty
#line 2956 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4581 "dhcp6_parser.cc"
    break;

  case 846: // sub_dhcp_ddns: "{" $@131 dhcp_ddns_params "}"
#line 2960 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4591 "dhcp6_parser.cc"
    break;

  case 849: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2968 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4599 "dhcp6_parser.cc"
    break;

  case 861: // enable_updates: "enable-updates" ":" "boolean"
#line 2986 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4609 "dhcp6_parser.cc"
    break;

  case 862: // $@132: %empty
#line 2992 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4618 "dhcp6_parser.cc"
    break;

  case 863: // server_ip: "server-ip" $@132 ":" "constant string"
#line 2995 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4628 "dhcp6_parser.cc"
    break;

  case 864: // server_port: "server-port" ":" "integer"
#line 3001 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4638 "dhcp6_parser.cc"
    break;

  case 865: // $@133: %empty
#line 3007 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4647 "dhcp6_parser.cc"
    break;

  case 866: // sender_ip: "sender-ip" $@133 ":" "constant string"
#line 3010 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4657 "dhcp6_parser.cc"
    break;

  case 867: // sender_port: "sender-port" ":" "integer"
#line 3016 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4667 "dhcp6_parser.cc"
    break;

  case 868: // max_queue_size: "max-queue-size" ":" "integer"
#line 3022 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4677 "dhcp6_parser.cc"
    break;

  case 869: // $@134: %empty
#line 3028 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4686 "dhcp6_parser.cc"
    break;

  case 870: // ncr_protocol: "ncr-protocol" $@134 ":" ncr_protocol_value
#line 3031 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4695 "dhcp6_parser.cc"
    break;

  case 871: // ncr_protocol_value: "UDP"
#line 3037 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4701 "dhcp6_parser.cc"
    break;

  case 872: // ncr_protocol_value: "TCP"
#line 3038 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4707 "dhcp6_parser.cc"
    break;

  case 873: // $@135: %empty
#line 3041 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4716 "dhcp6_parser.cc"
    break;

  case 874: // ncr_format: "ncr-format" $@135 ":" "JSON"
#line 3044 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4726 "dhcp6_parser.cc"
    break;

  case 875: // $@136: %empty
#line 3052 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4738 "dhcp6_parser.cc"
    break;

  case 876: // config_control: "config-control" $@136 ":" "{" config_control_params "}"
#line 3058 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4748 "dhcp6_parser.cc"
    break;

  case 877: // $@137: %empty
#line 3064 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4758 "dhcp6_parser.cc"
    break;

  case 878: // sub_config_control: "{" $@137 config_control_params "}"
#line 3068 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4767 "dhcp6_parser.cc"
    break;

  case 881: // config_control_params: config_control_params ","
#line 3076 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4775 "dhcp6_parser.cc"
    break;

  case 884: // $@138: %empty
#line 3086 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4787 "dhcp6_parser.cc"
    break;

  case 885: // config_databases: "config-databases" $@138 ":" "[" database_list "]"
#line 3092 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4796 "dhcp6_parser.cc"
    break;

  case 886: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3097 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4806 "dhcp6_parser.cc"
    break;

  case 887: // $@139: %empty
#line 3105 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4818 "dhcp6_parser.cc"
    break;

  case 888: // loggers: "loggers" $@139 ":" "[" loggers_entries "]"
#line 3111 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4827 "dhcp6_parser.cc"
    break;

  case 891: // loggers_entries: loggers_entries ","
#line 3120 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4835 "dhcp6_parser.cc"
    break;

  case 892: // $@140: %empty
#line 3126 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4845 "dhcp6_parser.cc"
    break;

  case 893: // logger_entry: "{" $@140 logger_params "}"
#line 3130 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4853 "dhcp6_parser.cc"
    break;

  case 896: // logger_params: logger_params ","
#line 3136 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4861 "dhcp6_parser.cc"
    break;

  case 904: // debuglevel: "debuglevel" ":" "integer"
#line 3150 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4871 "dhcp6_parser.cc"
    break;

  case 905: // $@141: %empty
#line 3156 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4880 "dhcp6_parser.cc"
    break;

  case 906: // severity: "severity" $@141 ":" "constant string"
#line 3159 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4890 "dhcp6_parser.cc"
    break;

  case 907: // $@142: %empty
#line 3165 "dhcp6_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4902 "dhcp6_parser.cc"
    break;

  case 908: // output_options_list: "output-options" $@142 ":" "[" output_options_list_content "]"
#line 3171 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4911 "dhcp6_parser.cc"
    break;

  case 911: // output_options_list_content: output_options_list_content ","
#line 3178 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4919 "dhcp6_parser.cc"
    break;

  case 912: // $@143: %empty
#line 3183 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4929 "dhcp6_parser.cc"
    break;

  case 913: // output_entry: "{" $@143 output_params_list "}"
#line 3187 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4937 "dhcp6_parser.cc"
    break;

  case 916: // output_params_list: output_params_list ","
#line 3193 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4945 "dhcp6_parser.cc"
    break;

  case 922: // $@144: %empty
#line 3205 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4954 "dhcp6_parser.cc"
    break;

  case 923: // output: "output" $@144 ":" "constant string"
#line 3208 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4964 "dhcp6_parser.cc"
    break;

  case 924: // flush: "flush" ":" "boolean"
#line 3214 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4974 "dhcp6_parser.cc"
    break;

  case 925: // maxsize: "maxsize" ":" "integer"
#line 3220 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4984 "dhcp6_parser.cc"
    break;

  case 926: // maxver: "maxver" ":" "integer"
#line 3226 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4994 "dhcp6_parser.cc"
    break;

  case 927: // $@145: %empty
#line 3232 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5003 "dhcp6_parser.cc"
    break;

  case 928: // pattern: "pattern" $@145 ":" "constant string"
#line 3235 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5013 "dhcp6_parser.cc"
    break;

  case 929: // $@146: %empty
#line 3241 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5025 "dhcp6_parser.cc"
    break;

  case 930: // compatibility: "compatibility" $@146 ":" "{" compatibility_params "}"
#line 3247 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5034 "dhcp6_parser.cc"
    break;

  case 933: // compatibility_params: compatibility_params ","
#line 3254 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5042 "dhcp6_parser.cc"
    break;

  case 936: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3263 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5052 "dhcp6_parser.cc"
    break;


#line 5056 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1344;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     509, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344,    70,    38,    90,   118,   120,
     138,   142,   146,   152,   185,   191,   257,   264,   270,   300,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,    38,  -143,
     101,   184,    36,   690,   282,   315,   556,    27,   198,   375,
     -79,   482,   376, -1344,   113,   126,   208,   216,   259, -1344,
      92, -1344, -1344, -1344, -1344, -1344, -1344, -1344,   318,   322,
     346,   356,   406,   410,   418,   419,   420,   424,   434,   435,
     436,   443, -1344,   444,   445,   447,   448,   456, -1344, -1344,
   -1344,   457,   459,   460,   461, -1344, -1344, -1344,   464, -1344,
   -1344, -1344, -1344, -1344, -1344,   470,   472,   474, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344,   481, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344,   487,   489,   491, -1344, -1344,
     493, -1344,    93, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344,   500,   501,   503,   506, -1344,    96, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344,   508,   511, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344,   104, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344,   512, -1344, -1344, -1344,
   -1344,   106, -1344, -1344, -1344, -1344, -1344, -1344,   515, -1344,
     516,   520, -1344, -1344, -1344, -1344, -1344, -1344, -1344,   114,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,   334,   361,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,   478,
   -1344, -1344,   521, -1344, -1344, -1344,   523, -1344, -1344,   524,
     528, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344,   530,   533,   534, -1344, -1344, -1344,
   -1344,   531,   540, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344,   125, -1344, -1344, -1344,
     541, -1344,   542, -1344,   543,   545, -1344, -1344, -1344, -1344,
   -1344,   127, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344,   546,   128, -1344, -1344, -1344, -1344,    38,    38,
   -1344,   325,   551, -1344, -1344,   552,   555,   557,   559,   560,
     563,   332,   341,   343,   347,   351,   357,   362,   365,   344,
     366,   367,   369,   371,   373,   573,   377,   378,   379,   381,
     383,   585,   599,   604,   386,   387,   390,   391,   616,   618,
     627,   404,   630,   631,   632,   633,   634,   636,   411,   412,
     417,   644,   645,   646,   647,   648,   650,   651,   653,   654,
     432,   659,   668,   669,   670,   671,   674,   675,   450,   451,
     452,   679,   680, -1344,   184, -1344,   688,   463,   467,   473,
     479,    36, -1344,   694,   696,   698,   701,   702,   480,   484,
     706,   713,   714,   690, -1344,   715,   492,   282, -1344,   732,
     525,   747,   526,   537,   315, -1344,   748,   762,   764,   765,
     766,   767,   771,   774, -1344,   556, -1344,   778,   780,   558,
     781,   784,   786,   561, -1344,   198,   788,   564,   575,   576,
   -1344,   375,   789,   803,   255, -1344,   578,   805,   582,   807,
     586,   587,   809,   813,   482, -1344,   815,   592,   376, -1344,
   -1344, -1344,   817,   816,   595,   818,   820,   821,   822,   819,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344,   603, -1344, -1344, -1344, -1344, -1344,
    -128,   605,   606, -1344, -1344, -1344, -1344,   826,   829,   830,
   -1344,   609,   610,   308,   833,   832,   613, -1344, -1344, -1344,
     836,   837,   838,   839,   840,   842,   843,   844,   845, -1344,
     846,   847,   850,   849,   851,   617,   622, -1344, -1344, -1344,
     852,   853, -1344,   854, -1344, -1344, -1344, -1344, -1344,   856,
     857,   623,   637,   638, -1344, -1344,   854,   639,   860, -1344,
     641, -1344, -1344,   642, -1344,   643, -1344, -1344, -1344,   854,
     854,   854,   854,   649,   652,   655,   656, -1344,   657,   658,
   -1344,   662,   663,   664, -1344, -1344,   665, -1344, -1344, -1344,
   -1344,   666,   832, -1344, -1344,   667, -1344,   672, -1344, -1344,
    -140,   681, -1344,   858, -1344, -1344,    38,   184, -1344,   376,
      36,   139,   139,   864, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344,   865,   867,   868, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344,   870, -1344, -1344, -1344,   -88,    38,   297,
     293,   871,   873,   874,   483,   164,   330,   477,   879,   291,
     482, -1344, -1344,   888,  -135, -1344, -1344,   889,   890, -1344,
   -1344, -1344, -1344, -1344,   769, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
     864, -1344,   135,   148,   154, -1344, -1344, -1344, -1344,   896,
     897,   898,   899,   900,   901,   902,   903,   904,   905, -1344,
     906,   907, -1344, -1344, -1344, -1344, -1344,   201, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344,   205, -1344,   908,   909, -1344, -1344,   910,   912, -1344,
   -1344,   913,   915, -1344, -1344,   914,   918, -1344, -1344,   916,
     920, -1344, -1344, -1344,    72, -1344, -1344, -1344,   919, -1344,
   -1344, -1344,   112, -1344, -1344, -1344, -1344, -1344,   207, -1344,
   -1344, -1344, -1344,   188, -1344, -1344,   921,   923, -1344, -1344,
     922,   926, -1344,   927,   928,   929,   930,   931,   932,   211,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,   933,
     934,   935, -1344, -1344, -1344, -1344,   213, -1344, -1344, -1344,
   -1344, -1344, -1344,   936,   937,   938, -1344,   215, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344,   939, -1344,   940,
   -1344, -1344, -1344, -1344, -1344, -1344,   217, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344,   924,   942, -1344,   943, -1344,
     944, -1344, -1344, -1344,   223, -1344, -1344, -1344, -1344, -1344,
     278, -1344,   327, -1344,   945, -1344,   303, -1344, -1344,   686,
   -1344,   946,   947, -1344, -1344,   948,   950, -1344, -1344,   949,
     952, -1344, -1344, -1344,   951,   955,   956,   957,   718,   721,
     728,   733,   734,   736,   737,   738,   739,   740,   965,   741,
     744,   970,   971,   973,   974,   139, -1344, -1344,   139, -1344,
     864,   690, -1344,   865,   198, -1344,   867,   375, -1344,   868,
    1097, -1344,   870,   -88, -1344, -1344,   297, -1344,   977,   982,
     293, -1344,   321,   871, -1344,   556, -1344,   873,   -79, -1344,
     874,   760,   770,   775,   777,   794,   795,   483, -1344,   991,
     995,   797,   801,   806,   164, -1344,   772,   808,   812,   330,
   -1344,  1008,  1029,  1037,   828,  1045,   869,   477, -1344,   477,
   -1344,   879,   911,  1056,   835,  1064,   291, -1344, -1344,   -16,
     888, -1344,   953,  -135, -1344, -1344,  1080,  1092,   282, -1344,
     889,   315, -1344,   890, -1344, -1344,   697,   892,   917,   954,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
     336, -1344, -1344,   958,   962,   963,   964, -1344,   305, -1344,
     311, -1344,  1122, -1344,  1125, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344,   317, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344,   966,   967, -1344, -1344, -1344,  1130,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344,  1129,  1135, -1344, -1344, -1344, -1344, -1344, -1344,  1131,
   -1344,   320, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
      30,   968, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
     242,   969,   972, -1344,  1133, -1344, -1344,   326, -1344, -1344,
     985, -1344,    38, -1344, -1344,  1138, -1344, -1344, -1344, -1344,
   -1344,   329, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
     986,   338, -1344,   340, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344,  1097, -1344, -1344, -1344,  1139,  1154,   984, -1344,   321,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344,   122, -1344, -1344, -1344,  1155,   987,  1156,
     -16, -1344, -1344, -1344, -1344, -1344,   989,   990, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344,   349, -1344, -1344,
   -1344, -1344, -1344,  1168, -1344,   993, -1344, -1344, -1344,  1157,
    1172,  1173,  1174,   122, -1344,  1175, -1344,  1009,   994,   997,
    1179, -1344, -1344,   348, -1344, -1344, -1344, -1344, -1344,  1185,
      -7,  1175, -1344, -1344,  1191,  1177, -1344, -1344,  1194,  1196,
    1197, -1344,   359, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
     204, -1344,  1185,  1214,   992,   998,   999,  1221,    -7, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344,   360, -1344, -1344,
   -1344, -1344,  1001, -1344, -1344, -1344,  1002, -1344,  1227,  1228,
     204, -1344, -1344, -1344,  1007,  1010, -1344, -1344, -1344
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   199,     9,   385,    11,
     590,    13,   619,    15,   652,    17,   508,    19,   517,    21,
     556,    23,   347,    25,   845,    27,   877,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   654,     0,   519,   558,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   141,   875,   197,   218,   220,   222,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   187,     0,     0,     0,     0,     0,   160,   167,
     169,     0,     0,     0,     0,   376,   506,   547,     0,   190,
     192,   173,   451,   606,   608,     0,     0,     0,   303,   322,
     312,   292,   690,   643,   338,   359,   722,     0,   324,   747,
     749,   826,   843,   180,   182,     0,     0,     0,   887,   929,
       0,   140,     0,    69,    72,    73,    74,    75,    76,    77,
      78,    79,    80,   111,   112,   113,   114,   115,    81,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   117,
     118,   129,   130,   131,   107,   137,   138,   139,   133,   134,
     135,    84,    85,    86,    87,   104,    88,    90,    89,   132,
      94,    95,    82,   108,   109,   110,    83,    92,    93,   102,
     103,   105,    91,    96,    97,    98,    99,   100,   101,   106,
     116,   136,   212,     0,     0,     0,     0,   211,     0,   201,
     204,   205,   206,   207,   208,   209,   210,   581,   610,   436,
     438,   440,     0,     0,   444,   442,   687,   435,   390,   391,
     392,   393,   394,   395,   396,   397,   415,   416,   417,   418,
     419,   422,   423,   424,   425,   426,   427,   428,   429,   430,
     431,   420,   421,   432,   433,   434,     0,   387,   401,   402,
     403,   406,   407,   409,   410,   411,   404,   405,   398,   399,
     413,   414,   400,   408,   412,   603,     0,   602,   598,   599,
     597,     0,   592,   595,   596,   600,   601,   636,     0,   639,
       0,     0,   635,   629,   630,   628,   627,   633,   634,     0,
     621,   624,   625,   631,   632,   626,   685,   671,   673,   675,
     677,   679,   681,   683,   670,   667,   668,   669,     0,   655,
     656,   661,   662,   663,   659,   664,   665,   666,   660,     0,
     537,   266,     0,   541,   539,   544,     0,   533,   534,     0,
     520,   521,   524,   536,   525,   526,   527,   543,   528,   529,
     530,   531,   532,   574,     0,     0,     0,   572,   573,   576,
     577,     0,   559,   560,   563,   564,   565,   566,   567,   568,
     569,   570,   571,   355,   357,   352,     0,   349,   353,   354,
       0,   862,     0,   865,     0,     0,   869,   873,   860,   858,
     859,     0,   847,   850,   851,   852,   853,   854,   855,   856,
     857,   884,     0,     0,   879,   882,   883,    47,    52,     0,
      39,    45,     0,    66,    62,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    60,    71,    68,     0,     0,     0,     0,
       0,   203,   200,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   389,   386,     0,     0,   594,   591,     0,
       0,     0,     0,     0,   623,   620,     0,     0,     0,     0,
       0,     0,     0,     0,   653,   658,   509,     0,     0,     0,
       0,     0,     0,     0,   518,   523,     0,     0,     0,     0,
     557,   562,     0,     0,   351,   348,     0,     0,     0,     0,
       0,     0,     0,     0,   849,   846,     0,     0,   881,   878,
      51,    43,     0,     0,     0,     0,     0,     0,     0,     0,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,     0,   185,   186,   157,   158,   159,
       0,     0,     0,   171,   172,   179,   184,     0,     0,     0,
     189,     0,     0,     0,     0,     0,     0,   446,   447,   448,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   746,
       0,     0,     0,     0,     0,     0,     0,   194,   195,   196,
       0,     0,    70,     0,   214,   215,   216,   217,   202,     0,
       0,     0,     0,     0,   449,   450,     0,     0,     0,   388,
       0,   605,   593,     0,   638,     0,   641,   642,   622,     0,
       0,     0,     0,     0,     0,     0,     0,   657,     0,     0,
     535,     0,     0,     0,   546,   522,     0,   578,   579,   580,
     561,     0,     0,   350,   861,     0,   864,     0,   867,   868,
       0,     0,   848,     0,   886,   880,     0,     0,   142,     0,
       0,     0,     0,   224,   188,   162,   163,   164,   165,   166,
     161,   168,   170,   378,   510,   549,   191,   193,   175,   176,
     177,   178,   174,   453,    40,   607,   609,     0,    48,     0,
       0,     0,   645,   340,     0,     0,     0,     0,   751,     0,
       0,   181,   183,     0,     0,    53,   213,   583,   612,   437,
     439,   441,   445,   443,     0,   604,   637,   640,   686,   672,
     674,   676,   678,   680,   682,   684,   538,   267,   542,   540,
     545,   575,   356,   358,   863,   866,   871,   872,   870,   874,
     224,    44,     0,     0,     0,   257,   259,   261,   263,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   276,
       0,     0,   284,   286,   288,   290,   256,     0,   231,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   248,   249,   250,   251,   247,   252,   253,   254,
     255,     0,   229,     0,   225,   226,   383,     0,   379,   380,
     515,     0,   511,   512,   554,     0,   550,   551,   458,     0,
     454,   455,   310,   311,     0,   305,   308,   309,     0,   320,
     321,   317,     0,   314,   318,   319,   299,   301,     0,   294,
     297,   298,   695,     0,   692,   650,     0,   646,   647,   345,
       0,   341,   342,     0,     0,     0,     0,     0,     0,     0,
     361,   364,   365,   366,   367,   368,   369,   736,   742,     0,
       0,     0,   735,   732,   733,   734,     0,   724,   727,   730,
     728,   729,   731,     0,     0,     0,   334,     0,   326,   329,
     330,   331,   332,   333,   773,   778,   780,     0,   784,     0,
     772,   766,   767,   768,   770,   771,     0,   758,   761,   762,
     763,   764,   769,   765,   756,     0,   752,   753,     0,   838,
       0,   841,   834,   835,     0,   828,   831,   832,   833,   836,
       0,   892,     0,   889,     0,   935,     0,   931,   934,    55,
     588,     0,   584,   585,   617,     0,   613,   614,   689,     0,
       0,    64,   876,   198,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   233,   219,   221,     0,   223,
     228,     0,   377,   382,   519,   507,   514,   558,   548,   553,
       0,   452,   457,   307,   304,   323,   316,   313,     0,     0,
     296,   293,   697,   694,   691,   654,   644,   649,     0,   339,
     344,     0,     0,     0,     0,     0,     0,   363,   360,     0,
       0,     0,     0,     0,   726,   723,     0,     0,     0,   328,
     325,     0,     0,     0,     0,     0,     0,   760,   748,     0,
     750,   755,     0,     0,     0,     0,   830,   827,   844,     0,
     891,   888,     0,   933,   930,    57,     0,    56,     0,   582,
     587,     0,   611,   616,   688,   885,     0,     0,     0,     0,
     265,   268,   269,   270,   271,   272,   273,   274,   283,   275,
       0,   281,   282,     0,     0,     0,     0,   232,     0,   227,
       0,   381,     0,   513,     0,   552,   505,   476,   477,   478,
     480,   481,   482,   467,   468,   485,   486,   487,   488,   489,
     492,   493,   494,   495,   496,   497,   498,   499,   500,   501,
     490,   491,   502,   503,   504,   463,   464,   465,   466,   474,
     475,   471,   472,   473,   479,     0,   460,   469,   483,   484,
     470,   456,   306,   315,     0,     0,   295,   717,   719,     0,
     715,   709,   710,   711,   712,   713,   714,   716,   706,   707,
     708,     0,   698,   699,   702,   703,   704,   705,   693,     0,
     648,     0,   343,   370,   371,   372,   373,   374,   375,   362,
       0,     0,   741,   744,   745,   725,   335,   336,   337,   327,
       0,     0,     0,   782,     0,   783,   759,     0,   754,   837,
       0,   840,     0,   829,   907,     0,   905,   903,   897,   901,
     902,     0,   894,   899,   900,   898,   890,   936,   932,    54,
      59,     0,   586,     0,   615,   258,   260,   262,   264,   278,
     279,   280,   277,   285,   287,   289,   291,   230,   384,   516,
     555,   462,   459,   300,   302,     0,     0,     0,   696,   701,
     651,   346,   738,   739,   740,   737,   743,   775,   776,   777,
     774,   779,   781,     0,   757,   839,   842,     0,     0,     0,
     896,   893,    58,   589,   618,   461,     0,     0,   721,   700,
     796,   799,   801,   803,   795,   794,   793,     0,   786,   789,
     790,   791,   792,     0,   904,     0,   895,   718,   720,     0,
       0,     0,     0,   788,   785,     0,   906,     0,     0,     0,
       0,   787,   912,     0,   909,   798,   797,   800,   802,   805,
       0,   911,   908,   810,     0,   806,   807,   922,     0,     0,
       0,   927,     0,   914,   917,   918,   919,   920,   921,   910,
       0,   804,   809,     0,     0,     0,     0,     0,   916,   913,
     822,   824,   821,   815,   817,   819,   820,     0,   812,   816,
     818,   808,     0,   924,   925,   926,     0,   915,     0,     0,
     814,   811,   923,   928,     0,     0,   813,   823,   825
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344,    -5, -1344,  -589, -1344,
     527, -1344, -1344, -1344, -1344,   486, -1344,  -618, -1344, -1344,
   -1344,   -71, -1344, -1344, -1344, -1344, -1344, -1344, -1344,   514,
     722, -1344, -1344,   -61,   -58,   -35,   -31,    -4,     3,   -34,
      20,    21,    25,    32,    33,    35, -1344,    37,    40,    43,
      47, -1344, -1344,    48, -1344,    51, -1344,    53,    59,    61,
   -1344, -1344,    64,    67, -1344,    71, -1344,    74, -1344, -1344,
   -1344, -1344, -1344,    77, -1344,    79, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344,   505,   724, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,   439, -1344,
     202, -1344,  -703,   218, -1344, -1344, -1343, -1344, -1339, -1344,
   -1344, -1344, -1344,   -30, -1344,  -737, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,  -761,
   -1344,  -744, -1344,  -741, -1344, -1344, -1344, -1344, -1344, -1344,
     186, -1344, -1344, -1344, -1344, -1344, -1344, -1344,   197,  -729,
   -1344, -1344, -1344, -1344,   200, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344,   165, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
     192, -1344, -1344, -1344,   190,   687, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344,   187, -1344, -1344, -1344, -1344, -1344, -1344,
   -1019, -1344, -1344, -1344,   220, -1344, -1344, -1344,   224,   742,
   -1344, -1344, -1014, -1344, -1013, -1344,   -11, -1344,    86, -1344,
      81,    82,    85, -1344, -1010, -1344, -1344, -1344, -1344,   221,
   -1344, -1344,   -29,  1200, -1344, -1344, -1344, -1344, -1344,   234,
   -1344, -1344, -1344,   237, -1344,   717, -1344,   -65, -1344, -1344,
   -1344, -1344, -1344,   -63, -1344, -1344, -1344, -1344, -1344,   -41,
   -1344, -1344, -1344,   235, -1344, -1344, -1344,   236, -1344,   716,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344,   166, -1344, -1344, -1344,   167,   751, -1344, -1344,
     -62,   -54, -1344,     7, -1344, -1344, -1344, -1344, -1344,   168,
   -1344, -1344, -1344,   172,   745, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344,   -56, -1344, -1344, -1344,   229, -1344, -1344, -1344,
     233, -1344,   746,   518, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1009,
   -1344, -1344, -1344, -1344, -1344,   240, -1344, -1344, -1344,   -10,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,   222,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344,   206, -1344,   212,   226, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344,   -53, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344,   -89, -1344, -1344,  -116, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344,   209, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344,   547,   735, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344,   589,   743, -1344, -1344, -1344, -1344,
   -1344, -1344,   210, -1344, -1344,    -3, -1344, -1344, -1344, -1344,
   -1344, -1344,   -49, -1344, -1344,   -83, -1344, -1344, -1344, -1344,
   -1344, -1344, -1344, -1344, -1344, -1344,   227, -1344
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     755,    87,    88,    41,    68,    84,    85,   776,   999,  1116,
    1117,   836,    43,    70,    90,   442,    91,    45,    71,   162,
     163,   164,   445,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   471,   740,   183,   472,   184,   473,   185,   186,   187,
     484,   752,   188,   189,   506,   190,   507,   191,   192,   193,
     194,   465,   195,   196,   482,   197,   483,   198,   199,   200,
     201,   447,    47,    72,   238,   239,   240,   516,   241,   242,
     243,   244,   202,   448,   203,   449,   204,   450,   863,   864,
     865,  1038,   837,   838,   839,  1014,   840,  1015,   841,  1016,
     842,  1017,   843,   844,   558,   845,   846,   847,   848,   849,
     850,   851,   852,   853,  1028,  1292,   854,   855,   856,   857,
    1031,   858,  1032,   859,  1033,   860,  1034,   205,   494,   898,
     899,   900,  1058,   901,  1059,   206,   491,   884,   885,   886,
     887,   207,   493,   892,   893,   894,   895,   208,   492,   209,
     501,   947,   948,   949,   950,   951,   210,   497,   910,   911,
     912,  1068,    63,    80,   406,   407,   408,   572,   409,   573,
     211,   498,   919,   920,   921,   922,   923,   924,   925,   926,
     212,   478,   867,   868,   869,  1041,    49,    73,   286,   287,
     288,   525,   289,   526,   290,   527,   291,   531,   292,   530,
     213,   214,   215,   296,   297,   216,   485,   879,   880,   881,
    1050,  1195,  1196,   217,   479,    57,    77,   871,   872,   873,
    1044,    59,    78,   369,   370,   371,   372,   373,   374,   375,
     557,   376,   561,   377,   560,   378,   379,   562,   380,   218,
     480,   875,   876,   877,  1047,    61,    79,   391,   392,   393,
     394,   395,   566,   396,   397,   398,   399,   400,   299,   523,
    1001,  1002,  1003,  1118,    51,    74,   311,   312,   313,   535,
     314,   219,   486,   220,   487,   302,   524,  1005,  1006,  1007,
    1121,    53,    75,   329,   330,   331,   539,   332,   333,   541,
     334,   335,   221,   496,   906,   907,   908,  1065,    55,    76,
     348,   349,   350,   351,   547,   352,   548,   353,   549,   354,
     550,   355,   551,   356,   552,   357,   553,   358,   546,   304,
     532,  1009,   222,   495,   903,   904,  1062,  1221,  1222,  1223,
    1224,  1225,  1305,  1226,  1306,  1227,   223,   499,   936,   937,
     938,  1079,  1315,   939,   940,  1080,   941,   942,   224,   225,
     502,   226,   503,   975,   976,   977,  1099,   966,   967,   968,
    1091,  1320,   969,  1092,   970,  1093,   971,   972,   973,  1095,
    1347,  1348,  1349,  1359,  1376,  1350,  1360,  1351,  1361,  1352,
    1362,  1384,  1385,  1386,  1400,  1417,  1418,  1419,  1428,  1420,
    1429,   227,   504,   984,   985,   986,   987,  1103,   988,   989,
    1105,   228,   505,    65,    81,   421,   422,   423,   424,   577,
     425,   426,   579,   427,   428,   429,   582,   808,   430,   583,
     229,   446,    67,    82,   433,   434,   435,   586,   436,   230,
     511,   992,   993,  1109,  1271,  1272,  1273,  1274,  1329,  1275,
    1327,  1373,  1374,  1380,  1392,  1393,  1394,  1403,  1395,  1396,
    1397,  1398,  1407,   231,   512,   996,   997,   998
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     161,   237,   257,   307,   322,   344,   961,   367,   387,   405,
     418,    38,   258,   326,   389,   259,   390,   303,   245,   300,
     315,   327,   346,   962,   381,   401,   963,   419,   933,   861,
     891,  1186,   298,   310,   325,   345,  1187,  1188,   260,   264,
    1194,  1200,   261,    31,   882,    32,   754,    33,   368,   388,
     806,   807,   232,   233,   234,   235,   236,  1413,   782,   403,
     404,  1414,   361,   308,   323,   735,   736,   737,   738,   262,
      30,   788,   789,   790,   791,  1053,   263,   994,  1054,   246,
     301,   316,   328,   347,    86,   382,   402,  1413,   420,   133,
     134,  1414,   160,   265,   266,   443,   514,    42,   267,   521,
     444,   515,   739,   126,   522,   268,   269,   533,   270,   537,
     271,    89,   534,   272,   538,  1056,   273,   544,  1057,   437,
     274,   275,   545,   754,   276,    44,   277,    46,   574,   438,
     584,   588,   278,   575,   279,   585,   589,   280,   514,   883,
     281,   133,   134,  1011,   282,    48,  1340,   283,   160,    50,
     284,   588,   285,    52,   293,   294,  1012,   521,   295,    54,
     309,   324,  1013,   815,   816,   817,   818,   819,   820,   821,
     822,   823,   824,   825,   826,   827,   828,   829,  1312,  1313,
    1314,   830,   831,   832,   833,   834,   835,  1264,   927,  1265,
    1266,  1063,    56,   820,  1064,    92,    93,  1387,    58,    94,
    1388,  1389,  1390,  1391,  1035,    95,    96,    97,  1035,  1036,
    1060,   160,   439,  1037,  1077,  1061,  1084,   361,  1089,  1078,
    1097,  1085,   360,  1090,   440,  1098,  1106,   133,   134,   816,
     817,  1107,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   441,   160,    60,    34,    35,    36,    37,   133,
     134,    62,   128,   129,   130,   131,   361,    64,   362,   363,
     132,   584,  1186,   364,   365,   366,  1108,  1187,  1188,   133,
     134,  1194,  1200,  1341,  1342,  1343,   135,   136,   137,   138,
     139,   140,   141,   133,   134,   142,  1113,    66,  1035,   133,
     134,  1114,   143,  1297,   533,   928,   929,   930,   931,  1298,
    1301,   144,   451,   574,   145,  1302,   452,   891,  1311,  1097,
    1110,   146,  1330,  1111,  1324,  1148,   961,  1331,   961,   147,
     148,   537,   554,   544,   149,   150,  1333,   933,  1334,   160,
     453,  1381,  1363,   962,  1382,   962,   963,  1364,   963,   127,
     454,   151,  1408,  1430,   555,   152,   160,  1409,  1431,    98,
      99,   100,   101,   102,   103,  1289,  1290,  1291,  1410,  1411,
     305,   153,   154,   155,   156,   157,   158,   133,   134,   431,
     432,   160,   127,   403,   404,   159,   133,   134,   127,   361,
     748,   749,   750,   751,   254,  1317,  1318,  1319,   255,   306,
     455,   160,   896,   897,   456,   317,   318,   319,   320,   321,
     133,   134,   457,   458,   459,   160,   133,   134,   460,   882,
     889,   160,   890,   590,   591,   133,   134,   254,   461,   462,
     463,   255,   306,   161,  1207,  1208,  1209,   464,   466,   467,
     237,   468,   469,   361,   383,   362,   363,   384,   385,   386,
     470,   474,   257,   475,   476,   477,   307,   245,   481,   978,
     979,   980,   258,   322,   488,   259,   489,   303,   490,   300,
     133,   134,   326,   315,   344,   500,   556,   943,   944,   945,
     327,   508,   298,   509,   367,   510,   310,   513,   260,   264,
     387,   346,   261,   325,   517,   518,   389,   519,   390,   160,
     520,   381,   528,   418,   345,   529,   536,   401,   981,   540,
     542,   832,   833,   834,   543,   559,   308,   563,   246,   262,
     419,   565,   564,   323,   567,   368,   263,   568,   569,   570,
     301,   388,   160,   571,   316,   576,   578,   580,   160,   581,
     587,   328,   592,   265,   266,   593,   594,   160,   267,   595,
     600,   596,   347,   597,   598,   268,   269,   599,   270,   601,
     271,   602,   382,   272,   608,   603,   273,   614,   402,   604,
     274,   275,   133,   134,   276,   605,   277,   133,   134,   620,
     606,   420,   278,   607,   279,   609,   610,   280,   611,   612,
     281,   613,   160,   621,   282,   615,   616,   283,   622,   617,
     284,   618,   285,   619,   293,   294,   623,   624,   295,   625,
     627,   626,   628,   309,   913,   914,   915,   916,   917,   918,
     324,   629,   630,   127,   631,   632,   633,   634,   635,   954,
     636,   637,   638,   955,   956,   957,   958,   639,   640,   641,
     642,   643,   644,   959,   645,   646,   161,   647,   648,   237,
     649,   133,   134,   650,   410,   411,   412,   413,   414,   415,
     416,   417,   651,   652,   653,   654,   245,   336,   655,   656,
     657,   658,   659,   660,   661,   337,   338,   339,   340,   341,
     342,   343,   663,   664,   932,   946,   960,   665,   669,   418,
     670,   666,   671,   995,   160,   672,   673,   667,   674,   160,
     676,   934,   952,   964,   675,   982,   419,   677,   678,   680,
     681,   811,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,   683,   246,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   685,   689,   684,   686,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   687,   690,   127,   691,   692,
     693,   694,   935,   953,   965,   695,   983,   420,   696,   129,
     130,   131,   698,   160,   699,   701,   700,   247,   702,   248,
     703,   704,   706,   711,   707,   133,   134,   249,   250,   251,
     252,   253,   135,   136,   137,   708,   709,   712,   714,   715,
     716,   717,   254,   720,   718,   719,   255,   721,   143,   723,
     724,   726,   728,   727,   733,   729,   256,   730,   731,   732,
     734,   743,   741,   742,   744,   745,   746,   747,   753,    32,
     756,   757,   758,   759,   771,   761,   760,   762,   763,   772,
     779,   764,   765,   766,   767,   768,   769,   773,   770,   775,
     774,   777,   778,   810,   780,   781,   783,   784,   785,   786,
     787,   862,   866,   809,   870,   874,   792,   878,   902,   793,
     905,   909,   794,   795,   796,   797,   974,   153,   154,   798,
     799,   800,   801,   802,   804,   991,  1000,  1004,   337,   805,
    1018,  1019,  1020,  1021,  1022,  1023,  1024,  1025,  1026,  1027,
    1029,  1030,  1040,  1115,  1039,  1043,  1042,   160,  1046,  1045,
    1048,  1049,  1051,  1052,  1285,  1055,  1067,  1066,  1069,  1070,
    1100,  1071,  1072,  1073,  1074,  1075,  1076,  1081,  1082,  1083,
    1086,  1087,  1088,  1094,  1096,  1101,  1130,  1102,  1104,  1112,
    1120,  1131,  1119,  1123,  1122,  1126,  1132,  1124,  1125,  1127,
    1128,  1129,  1134,  1133,  1135,  1136,  1137,  1138,  1139,  1140,
     257,  1141,  1142,   367,  1143,  1144,   387,  1145,  1146,  1156,
     258,  1204,   389,   259,   390,   303,  1205,   300,  1233,  1157,
     381,  1210,  1158,   401,   344,  1240,  1198,   405,  1234,  1241,
     298,  1211,  1246,  1235,  1212,  1236,   260,   264,  1219,  1197,
     261,   346,  1250,   932,   368,  1159,  1163,   388,   946,  1160,
    1185,  1218,  1237,  1238,   345,  1242,   960,  1213,   960,  1243,
     934,  1214,  1217,  1251,  1244,   952,  1247,   262,  1267,  1189,
    1248,  1252,   995,   964,   263,   964,  1161,   307,   301,  1254,
     322,   382,   982,  1162,   402,  1269,  1253,  1199,  1215,   326,
    1260,   265,   266,  1261,   315,  1216,   267,   327,  1262,  1220,
    1164,  1165,   347,   268,   269,  1166,   270,   310,   271,  1268,
     325,   272,  1167,  1168,   273,  1169,  1279,  1170,   274,   275,
    1171,   935,   276,  1172,   277,  1280,   953,  1173,  1174,  1255,
     278,  1175,   279,  1176,   965,   280,   965,   308,   281,  1177,
     323,  1178,   282,   983,  1179,   283,  1270,  1180,   284,  1286,
     285,  1181,   293,   294,  1182,   316,   295,  1183,   328,  1184,
    1299,  1191,  1192,  1300,  1307,  1193,  1190,  1308,  1309,  1310,
    1323,  1259,  1328,  1336,  1287,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,  1337,  1353,
    1355,  1367,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,  1365,   127,   361,  1368,  1369,  1370,  1375,
    1402,  1288,  1372,  1277,  1379,  1293,   129,   130,   131,  1294,
    1295,  1296,  1383,  1303,  1304,  1316,  1321,  1401,  1404,  1322,
    1405,  1406,   133,   134,   309,   250,   251,   324,   253,   135,
     136,   137,  1325,  1332,  1338,  1354,  1357,  1358,  1422,   254,
    1366,  1377,  1423,   255,  1378,  1426,  1424,  1425,  1432,  1433,
    1156,  1434,  1435,   256,  1437,   814,   662,  1438,  1210,   803,
    1157,   812,  1149,  1158,   888,   668,  1206,  1198,  1211,  1010,
    1202,  1212,  1344,  1147,  1249,  1219,  1203,  1326,  1231,  1267,
    1197,   713,  1232,  1151,  1239,  1150,  1159,  1163,  1218,  1345,
    1160,  1185,  1335,  1201,  1213,   679,  1269,   359,  1214,  1217,
    1153,  1152,   705,  1154,  1155,  1281,  1282,   710,   682,   688,
    1189,  1284,  1344,  1283,   153,   154,  1230,  1161,  1229,  1339,
    1268,   697,  1008,  1228,  1162,  1215,  1245,  1258,  1199,  1345,
    1371,  1257,  1216,  1421,  1436,  1263,  1220,   990,   813,   722,
    1276,  1164,  1165,  1256,   160,  1427,  1166,  1356,     0,  1412,
    1346,   725,  1399,  1167,  1168,     0,  1169,  1270,  1170,     0,
    1278,  1171,     0,     0,  1172,     0,  1415,     0,  1173,  1174,
       0,     0,  1175,     0,  1176,     0,     0,     0,     0,  1412,
    1177,     0,  1178,     0,     0,  1179,     0,     0,  1180,     0,
    1346,     0,  1181,     0,     0,  1182,  1415,     0,  1183,     0,
    1184,     0,  1191,  1192,     0,     0,  1193,  1190,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1416,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1416
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,   767,    78,    79,    80,
      81,    16,    73,    75,    79,    73,    79,    73,    72,    73,
      74,    75,    76,   767,    78,    79,   767,    81,   765,   732,
     759,  1050,    73,    74,    75,    76,  1050,  1050,    73,    73,
    1050,  1050,    73,     5,   132,     7,   635,     9,    78,    79,
     190,   191,    16,    17,    18,    19,    20,  1400,   676,   138,
     139,  1400,    78,    74,    75,   193,   194,   195,   196,    73,
       0,   689,   690,   691,   692,     3,    73,   212,     6,    72,
      73,    74,    75,    76,   227,    78,    79,  1430,    81,   105,
     106,  1430,   227,    73,    73,     3,     3,     7,    73,     3,
       8,     8,   230,    76,     8,    73,    73,     3,    73,     3,
      73,    10,     8,    73,     8,     3,    73,     3,     6,     6,
      73,    73,     8,   712,    73,     7,    73,     7,     3,     3,
       3,     3,    73,     8,    73,     8,     8,    73,     3,   227,
      73,   105,   106,     8,    73,     7,    24,    73,   227,     7,
      73,     3,    73,     7,    73,    73,     8,     3,    73,     7,
      74,    75,     8,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,   148,   149,
     150,    42,    43,    44,    45,    46,    47,   203,    24,   205,
     206,     3,     7,    29,     6,    11,    12,   204,     7,    15,
     207,   208,   209,   210,     3,    21,    22,    23,     3,     8,
       3,   227,     4,     8,     3,     8,     3,    78,     3,     8,
       3,     8,    24,     8,     8,     8,     3,   105,   106,    25,
      26,     8,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,     3,   227,     7,   227,   228,   229,   230,   105,
     106,     7,    88,    89,    90,    91,    78,     7,    80,    81,
      96,     3,  1301,    85,    86,    87,     8,  1301,  1301,   105,
     106,  1301,  1301,   171,   172,   173,   112,   113,   114,   115,
     116,   117,   118,   105,   106,   121,     3,     7,     3,   105,
     106,     8,   128,     8,     3,   151,   152,   153,   154,     8,
       3,   137,     4,     3,   140,     8,     4,  1056,     8,     3,
       3,   147,     3,     6,     8,  1038,  1097,     8,  1099,   155,
     156,     3,     8,     3,   160,   161,     8,  1084,     8,   227,
       4,     3,     3,  1097,     6,  1099,  1097,     8,  1099,    77,
       4,   177,     3,     3,     3,   181,   227,     8,     8,    48,
      49,    50,    51,    52,    53,    39,    40,    41,   174,   175,
      98,   197,   198,   199,   200,   201,   202,   105,   106,    13,
      14,   227,    77,   138,   139,   211,   105,   106,    77,    78,
      92,    93,    94,    95,   122,   163,   164,   165,   126,   127,
       4,   227,   119,   120,     4,   100,   101,   102,   103,   104,
     105,   106,     4,     4,     4,   227,   105,   106,     4,   132,
     133,   227,   135,   438,   439,   105,   106,   122,     4,     4,
       4,   126,   127,   514,   123,   124,   125,     4,     4,     4,
     521,     4,     4,    78,    79,    80,    81,    82,    83,    84,
       4,     4,   533,     4,     4,     4,   537,   521,     4,   178,
     179,   180,   533,   544,     4,   533,     4,   533,     4,   533,
     105,   106,   544,   537,   555,     4,     8,   157,   158,   159,
     544,     4,   533,     4,   565,     4,   537,     4,   533,   533,
     571,   555,   533,   544,     4,     4,   571,     4,   571,   227,
       4,   565,     4,   584,   555,     4,     4,   571,   227,     4,
       4,    44,    45,    46,     4,     4,   537,     4,   521,   533,
     584,     3,     8,   544,     4,   565,   533,     4,     4,     8,
     533,   571,   227,     3,   537,     4,     4,     4,   227,     4,
       4,   544,   227,   533,   533,     4,     4,   227,   533,     4,
     228,     4,   555,     4,     4,   533,   533,     4,   533,   228,
     533,   228,   565,   533,   230,   228,   533,     4,   571,   228,
     533,   533,   105,   106,   533,   228,   533,   105,   106,     4,
     228,   584,   533,   228,   533,   229,   229,   533,   229,   228,
     533,   228,   227,     4,   533,   228,   228,   533,     4,   230,
     533,   230,   533,   230,   533,   533,   230,   230,   533,   229,
       4,   230,     4,   537,   141,   142,   143,   144,   145,   146,
     544,     4,   228,    77,     4,     4,     4,     4,     4,   162,
       4,   230,   230,   166,   167,   168,   169,   230,     4,     4,
       4,     4,     4,   176,     4,     4,   727,     4,     4,   730,
     228,   105,   106,     4,   182,   183,   184,   185,   186,   187,
     188,   189,     4,     4,     4,     4,   730,   121,     4,     4,
     230,   230,   230,     4,     4,   129,   130,   131,   132,   133,
     134,   135,     4,   230,   765,   766,   767,   230,     4,   770,
       4,   228,     4,   774,   227,     4,     4,   228,   228,   227,
       4,   765,   766,   767,   230,   769,   770,     4,     4,     4,
     228,   726,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,     4,   730,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,     4,     4,   228,   228,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,   228,     4,    77,     4,     4,
       4,     4,   765,   766,   767,     4,   769,   770,     4,    89,
      90,    91,     4,   227,     4,     4,   228,    97,     4,    99,
       4,   230,     4,     4,   230,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   230,   230,     4,   230,     4,
     228,     4,   122,     4,   228,   228,   126,     4,   128,     4,
     228,     4,   227,     7,     5,     7,   136,     7,     7,     7,
     227,     5,   227,   227,     5,     5,   227,   227,     5,     7,
     227,     5,     5,     5,   227,     5,     7,     5,     5,   227,
     227,     7,     7,     7,     7,     5,     7,     5,     7,     5,
       7,     5,     5,     5,   227,   227,   227,     7,   227,   227,
     227,     7,     7,   192,     7,     7,   227,     7,     7,   227,
       7,     7,   227,   227,   227,   227,     7,   197,   198,   227,
     227,   227,   227,   227,   227,     7,     7,     7,   129,   227,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     3,   227,     6,     3,     6,   227,     3,     6,
       6,     3,     6,     3,   227,     6,     3,     6,     6,     3,
       6,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     3,   228,     4,     4,     4,
       3,   230,     6,     3,     6,     4,   228,     8,     6,     4,
       4,     4,   228,   230,   228,   228,   228,   228,   228,     4,
    1041,   230,   228,  1044,     4,     4,  1047,     4,     4,  1050,
    1041,     4,  1047,  1041,  1047,  1041,     4,  1041,   228,  1050,
    1044,  1062,  1050,  1047,  1065,     4,  1050,  1068,   228,     4,
    1041,  1062,   230,   228,  1062,   228,  1041,  1041,  1062,  1050,
    1041,  1065,     4,  1084,  1044,  1050,  1050,  1047,  1089,  1050,
    1050,  1062,   228,   228,  1065,   228,  1097,  1062,  1099,   228,
    1084,  1062,  1062,     4,   228,  1089,   228,  1041,  1109,  1050,
     228,     4,  1113,  1097,  1041,  1099,  1050,  1118,  1041,     4,
    1121,  1044,  1106,  1050,  1047,  1109,   228,  1050,  1062,  1121,
       4,  1041,  1041,   228,  1118,  1062,  1041,  1121,     4,  1062,
    1050,  1050,  1065,  1041,  1041,  1050,  1041,  1118,  1041,  1109,
    1121,  1041,  1050,  1050,  1041,  1050,     6,  1050,  1041,  1041,
    1050,  1084,  1041,  1050,  1041,     3,  1089,  1050,  1050,   230,
    1041,  1050,  1041,  1050,  1097,  1041,  1099,  1118,  1041,  1050,
    1121,  1050,  1041,  1106,  1050,  1041,  1109,  1050,  1041,   227,
    1041,  1050,  1041,  1041,  1050,  1118,  1041,  1050,  1121,  1050,
       8,  1050,  1050,     8,     4,  1050,  1050,     8,     3,     8,
       7,   230,     4,     4,   227,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,     4,     4,
       4,     4,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,     5,    77,    78,     4,     4,     4,   170,
       3,   227,     7,   230,     5,   227,    89,    90,    91,   227,
     227,   227,     7,   227,   227,   227,   227,     6,     4,   227,
       4,     4,   105,   106,  1118,   108,   109,  1121,   111,   112,
     113,   114,   227,   227,   230,   228,   227,   227,     4,   122,
     227,   227,   230,   126,   227,     4,   228,   228,   227,   227,
    1301,     4,     4,   136,   227,   730,   514,   227,  1309,   712,
    1301,   727,  1040,  1301,   758,   521,  1060,  1301,  1309,   810,
    1053,  1309,  1323,  1035,  1089,  1309,  1056,  1262,  1068,  1330,
    1301,   574,  1070,  1043,  1077,  1041,  1301,  1301,  1309,  1323,
    1301,  1301,  1301,  1052,  1309,   533,  1330,    77,  1309,  1309,
    1046,  1044,   565,  1047,  1049,  1118,  1120,   571,   537,   544,
    1301,  1123,  1363,  1121,   197,   198,  1067,  1301,  1065,  1309,
    1330,   555,   784,  1063,  1301,  1309,  1084,  1101,  1301,  1363,
    1363,  1099,  1309,  1402,  1430,  1106,  1309,   770,   729,   584,
    1110,  1301,  1301,  1097,   227,  1408,  1301,  1330,    -1,  1400,
    1323,   588,  1381,  1301,  1301,    -1,  1301,  1330,  1301,    -1,
    1113,  1301,    -1,    -1,  1301,    -1,  1400,    -1,  1301,  1301,
      -1,    -1,  1301,    -1,  1301,    -1,    -1,    -1,    -1,  1430,
    1301,    -1,  1301,    -1,    -1,  1301,    -1,    -1,  1301,    -1,
    1363,    -1,  1301,    -1,    -1,  1301,  1430,    -1,  1301,    -1,
    1301,    -1,  1301,  1301,    -1,    -1,  1301,  1301,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1400,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1430
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
       0,     5,     7,     9,   227,   228,   229,   230,   247,   248,
     249,   254,     7,   263,     7,   268,     7,   323,     7,   437,
       7,   515,     7,   532,     7,   549,     7,   466,     7,   472,
       7,   496,     7,   413,     7,   654,     7,   673,   255,   250,
     264,   269,   324,   438,   516,   533,   550,   467,   473,   497,
     414,   655,   674,   247,   256,   257,   227,   252,   253,    10,
     265,   267,    11,    12,    15,    21,    22,    23,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    88,    89,
      90,    91,    96,   105,   106,   112,   113,   114,   115,   116,
     117,   118,   121,   128,   137,   140,   147,   155,   156,   160,
     161,   177,   181,   197,   198,   199,   200,   201,   202,   211,
     227,   262,   270,   271,   272,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   294,   296,   298,   299,   300,   303,   304,
     306,   308,   309,   310,   311,   313,   314,   316,   318,   319,
     320,   321,   333,   335,   337,   378,   386,   392,   398,   400,
     407,   421,   431,   451,   452,   453,   456,   464,   490,   522,
     524,   543,   573,   587,   599,   600,   602,   642,   652,   671,
     680,   704,    16,    17,    18,    19,    20,   262,   325,   326,
     327,   329,   330,   331,   332,   522,   524,    97,    99,   107,
     108,   109,   110,   111,   122,   126,   136,   262,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   288,   289,   290,   291,   294,   296,   298,   299,   300,
     303,   304,   306,   308,   314,   316,   439,   440,   441,   443,
     445,   447,   449,   451,   452,   453,   454,   455,   490,   509,
     522,   524,   526,   543,   570,    98,   127,   262,   447,   449,
     490,   517,   518,   519,   521,   522,   524,   100,   101,   102,
     103,   104,   262,   447,   449,   490,   521,   522,   524,   534,
     535,   536,   538,   539,   541,   542,   121,   129,   130,   131,
     132,   133,   134,   135,   262,   490,   522,   524,   551,   552,
     553,   554,   556,   558,   560,   562,   564,   566,   568,   464,
      24,    78,    80,    81,    85,    86,    87,   262,   354,   474,
     475,   476,   477,   478,   479,   480,   482,   484,   486,   487,
     489,   522,   524,    79,    82,    83,    84,   262,   354,   478,
     484,   498,   499,   500,   501,   502,   504,   505,   506,   507,
     508,   522,   524,   138,   139,   262,   415,   416,   417,   419,
     182,   183,   184,   185,   186,   187,   188,   189,   262,   522,
     524,   656,   657,   658,   659,   661,   662,   664,   665,   666,
     669,    13,    14,   675,   676,   677,   679,     6,     3,     4,
       8,     3,   266,     3,     8,   273,   672,   322,   334,   336,
     338,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   312,     4,     4,     4,     4,
       4,   292,   295,   297,     4,     4,     4,     4,   432,   465,
     491,     4,   315,   317,   301,   457,   523,   525,     4,     4,
       4,   387,   399,   393,   379,   574,   544,   408,   422,   588,
       4,   401,   601,   603,   643,   653,   305,   307,     4,     4,
       4,   681,   705,     4,     3,     8,   328,     4,     4,     4,
       4,     3,     8,   510,   527,   442,   444,   446,     4,     4,
     450,   448,   571,     3,     8,   520,     4,     3,     8,   537,
       4,   540,     4,     4,     3,     8,   569,   555,   557,   559,
     561,   563,   565,   567,     8,     3,     8,   481,   355,     4,
     485,   483,   488,     4,     8,     3,   503,     4,     4,     4,
       8,     3,   418,   420,     3,     8,     4,   660,     4,   663,
       4,     4,   667,   670,     3,     8,   678,     4,     3,     8,
     247,   247,   227,     4,     4,     4,     4,     4,     4,     4,
     228,   228,   228,   228,   228,   228,   228,   228,   230,   229,
     229,   229,   228,   228,     4,   228,   228,   230,   230,   230,
       4,     4,     4,   230,   230,   229,   230,     4,     4,     4,
     228,     4,     4,     4,     4,     4,     4,   230,   230,   230,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   228,
       4,     4,     4,     4,     4,     4,     4,   230,   230,   230,
       4,     4,   271,     4,   230,   230,   228,   228,   326,     4,
       4,     4,     4,     4,   228,   230,     4,     4,     4,   440,
       4,   228,   518,     4,   228,     4,   228,   228,   535,     4,
       4,     4,     4,     4,     4,     4,     4,   553,     4,     4,
     228,     4,     4,     4,   230,   476,     4,   230,   230,   230,
     500,     4,     4,   416,   230,     4,   228,     4,   228,   228,
       4,     4,   657,     4,   228,   676,     4,     7,   227,     7,
       7,     7,     7,     5,   227,   193,   194,   195,   196,   230,
     293,   227,   227,     5,     5,     5,   227,   227,    92,    93,
      94,    95,   302,     5,   249,   251,   227,     5,     5,     5,
       7,     5,     5,     5,     7,     7,     7,     7,     5,     7,
       7,   227,   227,     5,     7,     5,   258,     5,     5,   227,
     227,   227,   258,   227,     7,   227,   227,   227,   258,   258,
     258,   258,   227,   227,   227,   227,   227,   227,   227,   227,
     227,   227,   227,   251,   227,   227,   190,   191,   668,   192,
       5,   247,   270,   675,   325,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      42,    43,    44,    45,    46,    47,   262,   343,   344,   345,
     347,   349,   351,   353,   354,   356,   357,   358,   359,   360,
     361,   362,   363,   364,   367,   368,   369,   370,   372,   374,
     376,   343,     7,   339,   340,   341,     7,   433,   434,   435,
       7,   468,   469,   470,     7,   492,   493,   494,     7,   458,
     459,   460,   132,   227,   388,   389,   390,   391,   256,   133,
     135,   390,   394,   395,   396,   397,   119,   120,   380,   381,
     382,   384,     7,   575,   576,     7,   545,   546,   547,     7,
     409,   410,   411,   141,   142,   143,   144,   145,   146,   423,
     424,   425,   426,   427,   428,   429,   430,    24,   151,   152,
     153,   154,   262,   356,   522,   524,   589,   590,   591,   594,
     595,   597,   598,   157,   158,   159,   262,   402,   403,   404,
     405,   406,   522,   524,   162,   166,   167,   168,   169,   176,
     262,   370,   372,   374,   522,   524,   608,   609,   610,   613,
     615,   617,   618,   619,     7,   604,   605,   606,   178,   179,
     180,   227,   522,   524,   644,   645,   646,   647,   649,   650,
     656,     7,   682,   683,   212,   262,   706,   707,   708,   259,
       7,   511,   512,   513,     7,   528,   529,   530,   554,   572,
     339,     8,     8,     8,   346,   348,   350,   352,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   365,     4,
       4,   371,   373,   375,   377,     3,     8,     8,   342,     6,
       3,   436,     6,     3,   471,     6,     3,   495,     6,     3,
     461,     6,     3,     3,     6,     6,     3,     6,   383,   385,
       3,     8,   577,     3,     6,   548,     6,     3,   412,     6,
       3,     4,     4,     4,     4,     4,     4,     3,     8,   592,
     596,     4,     4,     4,     3,     8,     4,     4,     4,     3,
       8,   611,   614,   616,     4,   620,     4,     3,     8,   607,
       6,     3,     4,   648,     4,   651,     3,     8,     8,   684,
       3,     6,     4,     3,     8,   227,   260,   261,   514,     6,
       3,   531,     6,     3,     8,     6,     4,     4,     4,     4,
     228,   230,   228,   230,   228,   228,   228,   228,   228,   228,
       4,   230,   228,     4,     4,     4,     4,   344,   343,   341,
     439,   435,   474,   470,   498,   494,   262,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     288,   289,   290,   291,   294,   296,   298,   299,   300,   303,
     304,   306,   308,   314,   316,   354,   431,   443,   445,   447,
     449,   451,   452,   453,   455,   462,   463,   490,   522,   524,
     570,   460,   389,   395,     4,     4,   381,   123,   124,   125,
     262,   274,   275,   276,   277,   278,   279,   354,   490,   522,
     524,   578,   579,   580,   581,   582,   584,   586,   576,   551,
     547,   415,   411,   228,   228,   228,   228,   228,   228,   424,
       4,     4,   228,   228,   228,   590,   230,   228,   228,   403,
       4,     4,     4,   228,     4,   230,   609,   608,   606,   230,
       4,   228,     4,   645,   203,   205,   206,   262,   354,   522,
     524,   685,   686,   687,   688,   690,   683,   230,   707,     6,
       3,   517,   513,   534,   530,   227,   227,   227,   227,    39,
      40,    41,   366,   227,   227,   227,   227,     8,     8,     8,
       8,     3,     8,   227,   227,   583,   585,     4,     8,     3,
       8,     8,   148,   149,   150,   593,   227,   163,   164,   165,
     612,   227,   227,     7,     8,   227,   247,   691,     4,   689,
       3,     8,   227,     8,     8,   463,     4,     4,   230,   580,
      24,   171,   172,   173,   262,   522,   524,   621,   622,   623,
     626,   628,   630,     4,   228,     4,   686,   227,   227,   624,
     627,   629,   631,     3,     8,     5,   227,     4,     4,     4,
       4,   622,     7,   692,   693,   170,   625,   227,   227,     5,
     694,     3,     6,     7,   632,   633,   634,   204,   207,   208,
     209,   210,   695,   696,   697,   699,   700,   701,   702,   693,
     635,     6,     3,   698,     4,     4,     4,   703,     3,     8,
     174,   175,   262,   347,   349,   522,   524,   636,   637,   638,
     640,   634,     4,   230,   228,   228,     4,   696,   639,   641,
       3,     8,   227,   227,     4,     4,   637,   227,   227
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   231,   233,   232,   234,   232,   235,   232,   236,   232,
     237,   232,   238,   232,   239,   232,   240,   232,   241,   232,
     242,   232,   243,   232,   244,   232,   245,   232,   246,   232,
     247,   247,   247,   247,   247,   247,   247,   248,   250,   249,
     251,   252,   252,   253,   253,   253,   255,   254,   256,   256,
     257,   257,   257,   259,   258,   260,   260,   261,   261,   261,
     262,   264,   263,   266,   265,   265,   267,   269,   268,   270,
     270,   270,   271,   271,   271,   271,   271,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   271,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   271,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   271,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   271,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   271,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   271,   271,   271,   271,
     271,   273,   272,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     292,   291,   293,   293,   293,   293,   293,   295,   294,   297,
     296,   298,   299,   301,   300,   302,   302,   302,   302,   303,
     305,   304,   307,   306,   308,   309,   310,   312,   311,   313,
     315,   314,   317,   316,   318,   319,   320,   322,   321,   324,
     323,   325,   325,   325,   326,   326,   326,   326,   326,   326,
     326,   326,   328,   327,   329,   330,   331,   332,   334,   333,
     336,   335,   338,   337,   339,   339,   340,   340,   340,   342,
     341,   343,   343,   343,   344,   344,   344,   344,   344,   344,
     344,   344,   344,   344,   344,   344,   344,   344,   344,   344,
     344,   344,   344,   344,   344,   344,   344,   346,   345,   348,
     347,   350,   349,   352,   351,   353,   355,   354,   356,   357,
     358,   359,   360,   361,   362,   363,   365,   364,   366,   366,
     366,   367,   368,   369,   371,   370,   373,   372,   375,   374,
     377,   376,   379,   378,   380,   380,   380,   381,   381,   383,
     382,   385,   384,   387,   386,   388,   388,   388,   389,   389,
     390,   391,   393,   392,   394,   394,   394,   395,   395,   395,
     396,   397,   399,   398,   401,   400,   402,   402,   402,   403,
     403,   403,   403,   403,   403,   404,   405,   406,   408,   407,
     409,   409,   410,   410,   410,   412,   411,   414,   413,   415,
     415,   415,   415,   416,   416,   418,   417,   420,   419,   422,
     421,   423,   423,   423,   424,   424,   424,   424,   424,   424,
     425,   426,   427,   428,   429,   430,   432,   431,   433,   433,
     434,   434,   434,   436,   435,   438,   437,   439,   439,   439,
     440,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     440,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     440,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     440,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     440,   440,   440,   440,   440,   440,   442,   441,   444,   443,
     446,   445,   448,   447,   450,   449,   451,   452,   453,   454,
     455,   457,   456,   458,   458,   459,   459,   459,   461,   460,
     462,   462,   462,   463,   463,   463,   463,   463,   463,   463,
     463,   463,   463,   463,   463,   463,   463,   463,   463,   463,
     463,   463,   463,   463,   463,   463,   463,   463,   463,   463,
     463,   463,   463,   463,   463,   463,   463,   463,   463,   463,
     463,   463,   463,   463,   463,   463,   465,   464,   467,   466,
     468,   468,   469,   469,   469,   471,   470,   473,   472,   474,
     474,   475,   475,   475,   476,   476,   476,   476,   476,   476,
     476,   476,   476,   476,   477,   478,   479,   481,   480,   483,
     482,   485,   484,   486,   488,   487,   489,   491,   490,   492,
     492,   493,   493,   493,   495,   494,   497,   496,   498,   498,
     499,   499,   499,   500,   500,   500,   500,   500,   500,   500,
     500,   500,   500,   501,   503,   502,   504,   505,   506,   507,
     508,   510,   509,   511,   511,   512,   512,   512,   514,   513,
     516,   515,   517,   517,   517,   518,   518,   518,   518,   518,
     518,   518,   518,   520,   519,   521,   523,   522,   525,   524,
     527,   526,   528,   528,   529,   529,   529,   531,   530,   533,
     532,   534,   534,   534,   535,   535,   535,   535,   535,   535,
     535,   535,   535,   535,   535,   535,   537,   536,   538,   540,
     539,   541,   542,   544,   543,   545,   545,   546,   546,   546,
     548,   547,   550,   549,   551,   551,   552,   552,   552,   553,
     553,   553,   553,   553,   553,   553,   553,   553,   553,   553,
     553,   555,   554,   557,   556,   559,   558,   561,   560,   563,
     562,   565,   564,   567,   566,   569,   568,   571,   570,   572,
     574,   573,   575,   575,   575,   577,   576,   578,   578,   579,
     579,   579,   580,   580,   580,   580,   580,   580,   580,   580,
     580,   580,   580,   580,   580,   580,   581,   583,   582,   585,
     584,   586,   588,   587,   589,   589,   589,   590,   590,   590,
     590,   590,   590,   590,   590,   590,   592,   591,   593,   593,
     593,   594,   596,   595,   597,   598,   599,   601,   600,   603,
     602,   604,   604,   605,   605,   605,   607,   606,   608,   608,
     608,   609,   609,   609,   609,   609,   609,   609,   609,   609,
     609,   609,   609,   611,   610,   612,   612,   612,   614,   613,
     616,   615,   617,   618,   620,   619,   621,   621,   621,   622,
     622,   622,   622,   622,   622,   622,   624,   623,   625,   627,
     626,   629,   628,   631,   630,   632,   632,   633,   633,   633,
     635,   634,   636,   636,   636,   637,   637,   637,   637,   637,
     637,   637,   639,   638,   641,   640,   643,   642,   644,   644,
     644,   645,   645,   645,   645,   645,   645,   646,   648,   647,
     649,   651,   650,   653,   652,   655,   654,   656,   656,   656,
     657,   657,   657,   657,   657,   657,   657,   657,   657,   657,
     657,   658,   660,   659,   661,   663,   662,   664,   665,   667,
     666,   668,   668,   670,   669,   672,   671,   674,   673,   675,
     675,   675,   676,   676,   678,   677,   679,   681,   680,   682,
     682,   682,   684,   683,   685,   685,   685,   686,   686,   686,
     686,   686,   686,   686,   687,   689,   688,   691,   690,   692,
     692,   692,   694,   693,   695,   695,   695,   696,   696,   696,
     696,   696,   698,   697,   699,   700,   701,   703,   702,   705,
     704,   706,   706,   706,   707,   707,   708
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
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     3,     3,     3,     3,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     6,     0,     4,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     0,
       1,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     0,     4,     0,
       4,     0,     4,     1,     0,     4,     3,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     0,     1,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     3,     3,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     0,     4,     0,     4,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       4,     3,     3,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     0,     1,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     1,
       0,     6,     1,     3,     2,     0,     4,     0,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     3,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     3,     0,     4,     3,     3,     3,     0,     6,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     0,     4,
       0,     4,     3,     3,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       3,     0,     4,     0,     6,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     3,     0,     4,     3,     3,     0,
       4,     1,     1,     0,     4,     0,     6,     0,     4,     1,
       3,     2,     1,     1,     0,     6,     3,     0,     6,     1,
       3,     2,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     6,     1,
       3,     2,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     0,     4,     3,     3,     3,     0,     4,     0,
       6,     1,     3,     2,     1,     1,     3
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
  "\"client-classes\"", "\"require-client-classes\"", "\"test\"",
  "\"template-test\"", "\"only-if-required\"", "\"client-class\"",
  "\"pool-id\"", "\"reservations\"", "\"ip-addresses\"", "\"prefixes\"",
  "\"excluded-prefixes\"", "\"duid\"", "\"hw-address\"", "\"hostname\"",
  "\"flex-id\"", "\"relay\"", "\"hooks-libraries\"", "\"library\"",
  "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"", "\"server-id\"",
  "\"LLT\"", "\"EN\"", "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"",
  "\"enterprise-id\"", "\"dhcp4o6-port\"", "\"multi-threading\"",
  "\"enable-multi-threading\"", "\"thread-pool-size\"",
  "\"packet-queue-size\"", "\"control-socket\"", "\"control-sockets\"",
  "\"socket-type\"", "\"unix\"", "\"http\"", "\"https\"",
  "\"socket-name\"", "\"socket-address\"", "\"socket-port\"",
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
  "reservation_param", "ip_addresses", "$@97", "prefixes", "$@98",
  "excluded_prefixes", "$@99", "duid", "$@100", "hw_address", "$@101",
  "hostname", "$@102", "flex_id_value", "$@103",
  "reservation_client_classes", "$@104", "relay", "$@105", "relay_map",
  "client_classes", "$@106", "client_classes_list", "client_class_entry",
  "$@107", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@108",
  "client_class_template_test", "$@109", "only_if_required", "server_id",
  "$@110", "server_id_params", "server_id_param", "server_id_type",
  "$@111", "duid_type", "htype", "identifier", "$@112", "time",
  "enterprise_id", "dhcp4o6_port", "control_socket", "$@113",
  "control_sockets", "$@114", "control_socket_list",
  "not_empty_control_socket_list", "control_socket_entry", "$@115",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@116", "control_socket_type_value", "control_socket_name", "$@117",
  "control_socket_address", "$@118", "control_socket_port",
  "cert_required", "authentication", "$@119", "auth_params", "auth_param",
  "auth_type", "$@120", "auth_type_value", "realm", "$@121", "directory",
  "$@122", "clients", "$@123", "clients_list", "not_empty_clients_list",
  "basic_auth", "$@124", "clients_params", "clients_param", "user_file",
  "$@125", "password_file", "$@126", "dhcp_queue_control", "$@127",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@128", "capacity", "arbitrary_map_entry", "$@129",
  "dhcp_ddns", "$@130", "sub_dhcp_ddns", "$@131", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@132", "server_port",
  "sender_ip", "$@133", "sender_port", "max_queue_size", "ncr_protocol",
  "$@134", "ncr_protocol_value", "ncr_format", "$@135", "config_control",
  "$@136", "sub_config_control", "$@137", "config_control_params",
  "config_control_param", "config_databases", "$@138",
  "config_fetch_wait_time", "loggers", "$@139", "loggers_entries",
  "logger_entry", "$@140", "logger_params", "logger_param", "debuglevel",
  "severity", "$@141", "output_options_list", "$@142",
  "output_options_list_content", "output_entry", "$@143",
  "output_params_list", "output_params", "output", "$@144", "flush",
  "maxsize", "maxver", "pattern", "$@145", "compatibility", "$@146",
  "compatibility_params", "compatibility_param", "lenient_option_parsing", YY_NULLPTR
  };
#endif


#if PARSER6_DEBUG
  const short
  Dhcp6Parser::yyrline_[] =
  {
       0,   325,   325,   325,   326,   326,   327,   327,   328,   328,
     329,   329,   330,   330,   331,   331,   332,   332,   333,   333,
     334,   334,   335,   335,   336,   336,   337,   337,   338,   338,
     346,   347,   348,   349,   350,   351,   352,   355,   360,   360,
     371,   374,   375,   378,   383,   389,   394,   394,   401,   402,
     405,   409,   413,   419,   419,   426,   427,   430,   434,   438,
     448,   457,   457,   472,   472,   486,   489,   495,   495,   504,
     505,   506,   513,   514,   515,   516,   517,   518,   519,   520,
     521,   522,   523,   524,   525,   526,   527,   528,   529,   530,
     531,   532,   533,   534,   535,   536,   537,   538,   539,   540,
     541,   542,   543,   544,   545,   546,   547,   548,   549,   550,
     551,   552,   553,   554,   555,   556,   557,   558,   559,   560,
     561,   562,   563,   564,   565,   566,   567,   568,   569,   570,
     571,   572,   573,   574,   575,   576,   577,   578,   579,   580,
     581,   584,   584,   593,   599,   605,   611,   617,   623,   629,
     635,   641,   647,   653,   659,   665,   671,   677,   683,   689,
     695,   695,   704,   707,   710,   713,   716,   722,   722,   731,
     731,   740,   749,   759,   759,   768,   771,   774,   777,   782,
     788,   788,   797,   797,   806,   812,   818,   824,   824,   833,
     839,   839,   848,   848,   857,   863,   869,   875,   875,   887,
     887,   896,   897,   898,   903,   904,   905,   906,   907,   908,
     909,   910,   913,   913,   924,   930,   936,   942,   948,   948,
     961,   961,   974,   974,   985,   986,   989,   990,   991,   996,
     996,  1006,  1007,  1008,  1013,  1014,  1015,  1016,  1017,  1018,
    1019,  1020,  1021,  1022,  1023,  1024,  1025,  1026,  1027,  1028,
    1029,  1030,  1031,  1032,  1033,  1034,  1035,  1038,  1038,  1047,
    1047,  1056,  1056,  1065,  1065,  1074,  1080,  1080,  1089,  1095,
    1101,  1107,  1113,  1119,  1125,  1132,  1138,  1138,  1146,  1147,
    1148,  1151,  1157,  1163,  1169,  1169,  1178,  1178,  1187,  1187,
    1196,  1196,  1205,  1205,  1216,  1217,  1218,  1223,  1224,  1227,
    1227,  1246,  1246,  1264,  1264,  1275,  1276,  1277,  1282,  1283,
    1286,  1291,  1296,  1296,  1307,  1308,  1309,  1314,  1315,  1316,
    1319,  1324,  1331,  1331,  1344,  1344,  1357,  1358,  1359,  1364,
    1365,  1366,  1367,  1368,  1369,  1372,  1378,  1384,  1390,  1390,
    1401,  1402,  1405,  1406,  1407,  1412,  1412,  1422,  1422,  1432,
    1433,  1434,  1437,  1440,  1441,  1444,  1444,  1453,  1453,  1462,
    1462,  1474,  1475,  1476,  1481,  1482,  1483,  1484,  1485,  1486,
    1489,  1495,  1501,  1507,  1513,  1519,  1528,  1528,  1542,  1543,
    1546,  1547,  1548,  1557,  1557,  1583,  1583,  1594,  1595,  1596,
    1602,  1603,  1604,  1605,  1606,  1607,  1608,  1609,  1610,  1611,
    1612,  1613,  1614,  1615,  1616,  1617,  1618,  1619,  1620,  1621,
    1622,  1623,  1624,  1625,  1626,  1627,  1628,  1629,  1630,  1631,
    1632,  1633,  1634,  1635,  1636,  1637,  1638,  1639,  1640,  1641,
    1642,  1643,  1644,  1645,  1646,  1647,  1650,  1650,  1659,  1659,
    1668,  1668,  1677,  1677,  1686,  1686,  1697,  1703,  1709,  1715,
    1721,  1729,  1729,  1741,  1742,  1746,  1747,  1748,  1753,  1753,
    1761,  1762,  1763,  1768,  1769,  1770,  1771,  1772,  1773,  1774,
    1775,  1776,  1777,  1778,  1779,  1780,  1781,  1782,  1783,  1784,
    1785,  1786,  1787,  1788,  1789,  1790,  1791,  1792,  1793,  1794,
    1795,  1796,  1797,  1798,  1799,  1800,  1801,  1802,  1803,  1804,
    1805,  1806,  1807,  1808,  1809,  1810,  1817,  1817,  1831,  1831,
    1840,  1841,  1844,  1845,  1846,  1853,  1853,  1868,  1868,  1882,
    1883,  1886,  1887,  1888,  1893,  1894,  1895,  1896,  1897,  1898,
    1899,  1900,  1901,  1902,  1905,  1907,  1913,  1915,  1915,  1924,
    1924,  1933,  1933,  1942,  1944,  1944,  1953,  1963,  1963,  1976,
    1977,  1982,  1983,  1984,  1991,  1991,  2003,  2003,  2015,  2016,
    2021,  2022,  2023,  2030,  2031,  2032,  2033,  2034,  2035,  2036,
    2037,  2038,  2039,  2042,  2044,  2044,  2053,  2055,  2057,  2063,
    2069,  2078,  2078,  2091,  2092,  2095,  2096,  2097,  2102,  2102,
    2112,  2112,  2122,  2123,  2124,  2129,  2130,  2131,  2132,  2133,
    2134,  2135,  2136,  2139,  2139,  2148,  2154,  2154,  2179,  2179,
    2209,  2209,  2222,  2223,  2226,  2227,  2228,  2233,  2233,  2245,
    2245,  2257,  2258,  2259,  2264,  2265,  2266,  2267,  2268,  2269,
    2270,  2271,  2272,  2273,  2274,  2275,  2278,  2278,  2287,  2293,
    2293,  2302,  2308,  2317,  2317,  2328,  2329,  2332,  2333,  2334,
    2339,  2339,  2348,  2348,  2357,  2358,  2361,  2362,  2363,  2369,
    2370,  2371,  2372,  2373,  2374,  2375,  2376,  2377,  2378,  2379,
    2380,  2383,  2383,  2394,  2394,  2405,  2405,  2416,  2416,  2425,
    2425,  2434,  2434,  2443,  2443,  2452,  2452,  2466,  2466,  2477,
    2483,  2483,  2494,  2495,  2496,  2501,  2501,  2511,  2512,  2515,
    2516,  2517,  2522,  2523,  2524,  2525,  2526,  2527,  2528,  2529,
    2530,  2531,  2532,  2533,  2534,  2535,  2538,  2540,  2540,  2549,
    2549,  2558,  2567,  2567,  2580,  2581,  2582,  2587,  2588,  2589,
    2590,  2591,  2592,  2593,  2594,  2595,  2598,  2598,  2606,  2607,
    2608,  2611,  2617,  2617,  2626,  2632,  2640,  2648,  2648,  2660,
    2660,  2672,  2673,  2676,  2677,  2678,  2683,  2683,  2691,  2692,
    2693,  2698,  2699,  2700,  2701,  2702,  2703,  2704,  2705,  2706,
    2707,  2708,  2709,  2712,  2712,  2721,  2722,  2723,  2726,  2726,
    2736,  2736,  2746,  2752,  2760,  2760,  2773,  2774,  2775,  2780,
    2781,  2782,  2783,  2784,  2785,  2786,  2789,  2789,  2797,  2800,
    2800,  2809,  2809,  2818,  2818,  2829,  2830,  2833,  2834,  2835,
    2840,  2840,  2848,  2849,  2850,  2855,  2856,  2857,  2858,  2859,
    2860,  2861,  2864,  2864,  2873,  2873,  2884,  2884,  2897,  2898,
    2899,  2904,  2905,  2906,  2907,  2908,  2909,  2912,  2918,  2918,
    2927,  2933,  2933,  2943,  2943,  2956,  2956,  2966,  2967,  2968,
    2973,  2974,  2975,  2976,  2977,  2978,  2979,  2980,  2981,  2982,
    2983,  2986,  2992,  2992,  3001,  3007,  3007,  3016,  3022,  3028,
    3028,  3037,  3038,  3041,  3041,  3052,  3052,  3064,  3064,  3074,
    3075,  3076,  3082,  3083,  3086,  3086,  3097,  3105,  3105,  3118,
    3119,  3120,  3126,  3126,  3134,  3135,  3136,  3141,  3142,  3143,
    3144,  3145,  3146,  3147,  3150,  3156,  3156,  3165,  3165,  3176,
    3177,  3178,  3183,  3183,  3191,  3192,  3193,  3198,  3199,  3200,
    3201,  3202,  3205,  3205,  3214,  3220,  3226,  3232,  3232,  3241,
    3241,  3252,  3253,  3254,  3259,  3260,  3263
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
#line 6796 "dhcp6_parser.cc"

#line 3269 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
