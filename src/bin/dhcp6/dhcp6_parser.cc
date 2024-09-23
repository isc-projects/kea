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

  case 575: // $@82: %empty
#line 2045 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3246 "dhcp6_parser.cc"
    break;

  case 576: // option_data_data: "data" $@82 ":" "constant string"
#line 2048 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3256 "dhcp6_parser.cc"
    break;

  case 579: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2058 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3266 "dhcp6_parser.cc"
    break;

  case 580: // option_data_always_send: "always-send" ":" "boolean"
#line 2064 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3276 "dhcp6_parser.cc"
    break;

  case 581: // option_data_never_send: "never-send" ":" "boolean"
#line 2070 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3286 "dhcp6_parser.cc"
    break;

  case 582: // $@83: %empty
#line 2076 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3298 "dhcp6_parser.cc"
    break;

  case 583: // option_data_client_classes: "client-classes" $@83 ":" list_strings
#line 2082 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3307 "dhcp6_parser.cc"
    break;

  case 584: // $@84: %empty
#line 2090 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3319 "dhcp6_parser.cc"
    break;

  case 585: // pools_list: "pools" $@84 ":" "[" pools_list_content "]"
#line 2096 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3328 "dhcp6_parser.cc"
    break;

  case 590: // not_empty_pools_list: not_empty_pools_list ","
#line 2109 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3336 "dhcp6_parser.cc"
    break;

  case 591: // $@85: %empty
#line 2114 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3346 "dhcp6_parser.cc"
    break;

  case 592: // pool_list_entry: "{" $@85 pool_params "}"
#line 2118 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3356 "dhcp6_parser.cc"
    break;

  case 593: // $@86: %empty
#line 2124 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3366 "dhcp6_parser.cc"
    break;

  case 594: // sub_pool6: "{" $@86 pool_params "}"
#line 2128 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3376 "dhcp6_parser.cc"
    break;

  case 597: // pool_params: pool_params ","
#line 2136 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3384 "dhcp6_parser.cc"
    break;

  case 606: // $@87: %empty
#line 2151 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3393 "dhcp6_parser.cc"
    break;

  case 607: // pool_entry: "pool" $@87 ":" "constant string"
#line 2154 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3403 "dhcp6_parser.cc"
    break;

  case 608: // pool_id: "pool-id" ":" "integer"
#line 2160 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3413 "dhcp6_parser.cc"
    break;

  case 609: // $@88: %empty
#line 2166 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3421 "dhcp6_parser.cc"
    break;

  case 610: // user_context: "user-context" $@88 ":" map_value
#line 2168 "dhcp6_parser.yy"
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
#line 3448 "dhcp6_parser.cc"
    break;

  case 611: // $@89: %empty
#line 2191 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3456 "dhcp6_parser.cc"
    break;

  case 612: // comment: "comment" $@89 ":" "constant string"
#line 2193 "dhcp6_parser.yy"
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
#line 3485 "dhcp6_parser.cc"
    break;

  case 613: // $@90: %empty
#line 2221 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3497 "dhcp6_parser.cc"
    break;

  case 614: // pd_pools_list: "pd-pools" $@90 ":" "[" pd_pools_list_content "]"
#line 2227 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3506 "dhcp6_parser.cc"
    break;

  case 619: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2240 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3514 "dhcp6_parser.cc"
    break;

  case 620: // $@91: %empty
#line 2245 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3524 "dhcp6_parser.cc"
    break;

  case 621: // pd_pool_entry: "{" $@91 pd_pool_params "}"
#line 2249 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3536 "dhcp6_parser.cc"
    break;

  case 622: // $@92: %empty
#line 2257 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3546 "dhcp6_parser.cc"
    break;

  case 623: // sub_pd_pool: "{" $@92 pd_pool_params "}"
#line 2261 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3558 "dhcp6_parser.cc"
    break;

  case 626: // pd_pool_params: pd_pool_params ","
#line 2271 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3566 "dhcp6_parser.cc"
    break;

  case 639: // $@93: %empty
#line 2290 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3575 "dhcp6_parser.cc"
    break;

  case 640: // pd_prefix: "prefix" $@93 ":" "constant string"
#line 2293 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3585 "dhcp6_parser.cc"
    break;

  case 641: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2299 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3595 "dhcp6_parser.cc"
    break;

  case 642: // $@94: %empty
#line 2305 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3604 "dhcp6_parser.cc"
    break;

  case 643: // excluded_prefix: "excluded-prefix" $@94 ":" "constant string"
#line 2308 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3614 "dhcp6_parser.cc"
    break;

  case 644: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2314 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3624 "dhcp6_parser.cc"
    break;

  case 645: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2320 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3634 "dhcp6_parser.cc"
    break;

  case 646: // $@95: %empty
#line 2329 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3646 "dhcp6_parser.cc"
    break;

  case 647: // reservations: "reservations" $@95 ":" "[" reservations_list "]"
#line 2335 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3655 "dhcp6_parser.cc"
    break;

  case 652: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2346 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3663 "dhcp6_parser.cc"
    break;

  case 653: // $@96: %empty
#line 2351 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3673 "dhcp6_parser.cc"
    break;

  case 654: // reservation: "{" $@96 reservation_params "}"
#line 2355 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3682 "dhcp6_parser.cc"
    break;

  case 655: // $@97: %empty
#line 2360 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3692 "dhcp6_parser.cc"
    break;

  case 656: // sub_reservation: "{" $@97 reservation_params "}"
#line 2364 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3701 "dhcp6_parser.cc"
    break;

  case 661: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2375 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3709 "dhcp6_parser.cc"
    break;

  case 674: // $@98: %empty
#line 2395 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3721 "dhcp6_parser.cc"
    break;

  case 675: // ip_addresses: "ip-addresses" $@98 ":" list_strings
#line 2401 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3730 "dhcp6_parser.cc"
    break;

  case 676: // $@99: %empty
#line 2406 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3742 "dhcp6_parser.cc"
    break;

  case 677: // prefixes: "prefixes" $@99 ":" list_strings
#line 2412 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3751 "dhcp6_parser.cc"
    break;

  case 678: // $@100: %empty
#line 2417 "dhcp6_parser.yy"
                                     {
    ctx.unique("excluded-prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3763 "dhcp6_parser.cc"
    break;

  case 679: // excluded_prefixes: "excluded-prefixes" $@100 ":" list_strings
#line 2423 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3772 "dhcp6_parser.cc"
    break;

  case 680: // $@101: %empty
#line 2428 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3781 "dhcp6_parser.cc"
    break;

  case 681: // duid: "duid" $@101 ":" "constant string"
#line 2431 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3791 "dhcp6_parser.cc"
    break;

  case 682: // $@102: %empty
#line 2437 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3800 "dhcp6_parser.cc"
    break;

  case 683: // hw_address: "hw-address" $@102 ":" "constant string"
#line 2440 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3810 "dhcp6_parser.cc"
    break;

  case 684: // $@103: %empty
#line 2446 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3819 "dhcp6_parser.cc"
    break;

  case 685: // hostname: "hostname" $@103 ":" "constant string"
#line 2449 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3829 "dhcp6_parser.cc"
    break;

  case 686: // $@104: %empty
#line 2455 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3838 "dhcp6_parser.cc"
    break;

  case 687: // flex_id_value: "flex-id" $@104 ":" "constant string"
#line 2458 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3848 "dhcp6_parser.cc"
    break;

  case 688: // $@105: %empty
#line 2464 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3860 "dhcp6_parser.cc"
    break;

  case 689: // reservation_client_classes: "client-classes" $@105 ":" list_strings
#line 2470 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3869 "dhcp6_parser.cc"
    break;

  case 690: // $@106: %empty
#line 2478 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3881 "dhcp6_parser.cc"
    break;

  case 691: // relay: "relay" $@106 ":" "{" relay_map "}"
#line 2484 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3890 "dhcp6_parser.cc"
    break;

  case 693: // $@107: %empty
#line 2495 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3902 "dhcp6_parser.cc"
    break;

  case 694: // client_classes: "client-classes" $@107 ":" "[" client_classes_list "]"
#line 2501 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3911 "dhcp6_parser.cc"
    break;

  case 697: // client_classes_list: client_classes_list ","
#line 2508 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3919 "dhcp6_parser.cc"
    break;

  case 698: // $@108: %empty
#line 2513 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3929 "dhcp6_parser.cc"
    break;

  case 699: // client_class_entry: "{" $@108 client_class_params "}"
#line 2517 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3939 "dhcp6_parser.cc"
    break;

  case 704: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2529 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3947 "dhcp6_parser.cc"
    break;

  case 720: // $@109: %empty
#line 2552 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3956 "dhcp6_parser.cc"
    break;

  case 721: // client_class_test: "test" $@109 ":" "constant string"
#line 2555 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3966 "dhcp6_parser.cc"
    break;

  case 722: // $@110: %empty
#line 2561 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3975 "dhcp6_parser.cc"
    break;

  case 723: // client_class_template_test: "template-test" $@110 ":" "constant string"
#line 2564 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3985 "dhcp6_parser.cc"
    break;

  case 724: // only_if_required: "only-if-required" ":" "boolean"
#line 2570 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3995 "dhcp6_parser.cc"
    break;

  case 725: // $@111: %empty
#line 2579 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 4007 "dhcp6_parser.cc"
    break;

  case 726: // server_id: "server-id" $@111 ":" "{" server_id_params "}"
#line 2585 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4018 "dhcp6_parser.cc"
    break;

  case 729: // server_id_params: server_id_params ","
#line 2594 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4026 "dhcp6_parser.cc"
    break;

  case 739: // $@112: %empty
#line 2610 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 4035 "dhcp6_parser.cc"
    break;

  case 740: // server_id_type: "type" $@112 ":" duid_type
#line 2613 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4044 "dhcp6_parser.cc"
    break;

  case 741: // duid_type: "LLT"
#line 2618 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4050 "dhcp6_parser.cc"
    break;

  case 742: // duid_type: "EN"
#line 2619 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4056 "dhcp6_parser.cc"
    break;

  case 743: // duid_type: "LL"
#line 2620 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4062 "dhcp6_parser.cc"
    break;

  case 744: // htype: "htype" ":" "integer"
#line 2623 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4072 "dhcp6_parser.cc"
    break;

  case 745: // $@113: %empty
#line 2629 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4081 "dhcp6_parser.cc"
    break;

  case 746: // identifier: "identifier" $@113 ":" "constant string"
#line 2632 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4091 "dhcp6_parser.cc"
    break;

  case 747: // time: "time" ":" "integer"
#line 2638 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4101 "dhcp6_parser.cc"
    break;

  case 748: // enterprise_id: "enterprise-id" ":" "integer"
#line 2644 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4111 "dhcp6_parser.cc"
    break;

  case 749: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2652 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4121 "dhcp6_parser.cc"
    break;

  case 750: // $@114: %empty
#line 2660 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4134 "dhcp6_parser.cc"
    break;

  case 751: // control_socket: "control-socket" $@114 ":" "{" control_socket_params "}"
#line 2667 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4143 "dhcp6_parser.cc"
    break;

  case 752: // $@115: %empty
#line 2672 "dhcp6_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4156 "dhcp6_parser.cc"
    break;

  case 753: // control_sockets: "control-sockets" $@115 ":" "[" control_socket_list "]"
#line 2679 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4165 "dhcp6_parser.cc"
    break;

  case 758: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2690 "dhcp6_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4173 "dhcp6_parser.cc"
    break;

  case 759: // $@116: %empty
#line 2695 "dhcp6_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4183 "dhcp6_parser.cc"
    break;

  case 760: // control_socket_entry: "{" $@116 control_socket_params "}"
#line 2699 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4191 "dhcp6_parser.cc"
    break;

  case 763: // control_socket_params: control_socket_params ","
#line 2705 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4199 "dhcp6_parser.cc"
    break;

  case 776: // $@117: %empty
#line 2724 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4208 "dhcp6_parser.cc"
    break;

  case 777: // control_socket_type: "socket-type" $@117 ":" control_socket_type_value
#line 2727 "dhcp6_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4217 "dhcp6_parser.cc"
    break;

  case 778: // control_socket_type_value: "unix"
#line 2733 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4223 "dhcp6_parser.cc"
    break;

  case 779: // control_socket_type_value: "http"
#line 2734 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4229 "dhcp6_parser.cc"
    break;

  case 780: // control_socket_type_value: "https"
#line 2735 "dhcp6_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4235 "dhcp6_parser.cc"
    break;

  case 781: // $@118: %empty
#line 2738 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4245 "dhcp6_parser.cc"
    break;

  case 782: // control_socket_name: "socket-name" $@118 ":" "constant string"
#line 2742 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4255 "dhcp6_parser.cc"
    break;

  case 783: // $@119: %empty
#line 2748 "dhcp6_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4265 "dhcp6_parser.cc"
    break;

  case 784: // control_socket_address: "socket-address" $@119 ":" "constant string"
#line 2752 "dhcp6_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4275 "dhcp6_parser.cc"
    break;

  case 785: // control_socket_port: "socket-port" ":" "integer"
#line 2758 "dhcp6_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4285 "dhcp6_parser.cc"
    break;

  case 786: // cert_required: "cert-required" ":" "boolean"
#line 2764 "dhcp6_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4295 "dhcp6_parser.cc"
    break;

  case 787: // $@120: %empty
#line 2772 "dhcp6_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4307 "dhcp6_parser.cc"
    break;

  case 788: // authentication: "authentication" $@120 ":" "{" auth_params "}"
#line 2778 "dhcp6_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4318 "dhcp6_parser.cc"
    break;

  case 791: // auth_params: auth_params ","
#line 2787 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4326 "dhcp6_parser.cc"
    break;

  case 799: // $@121: %empty
#line 2801 "dhcp6_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4335 "dhcp6_parser.cc"
    break;

  case 800: // auth_type: "type" $@121 ":" auth_type_value
#line 2804 "dhcp6_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4344 "dhcp6_parser.cc"
    break;

  case 801: // auth_type_value: "basic"
#line 2809 "dhcp6_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4350 "dhcp6_parser.cc"
    break;

  case 802: // $@122: %empty
#line 2812 "dhcp6_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4359 "dhcp6_parser.cc"
    break;

  case 803: // realm: "realm" $@122 ":" "constant string"
#line 2815 "dhcp6_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4369 "dhcp6_parser.cc"
    break;

  case 804: // $@123: %empty
#line 2821 "dhcp6_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4378 "dhcp6_parser.cc"
    break;

  case 805: // directory: "directory" $@123 ":" "constant string"
#line 2824 "dhcp6_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4388 "dhcp6_parser.cc"
    break;

  case 806: // $@124: %empty
#line 2830 "dhcp6_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4400 "dhcp6_parser.cc"
    break;

  case 807: // clients: "clients" $@124 ":" "[" clients_list "]"
#line 2836 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4409 "dhcp6_parser.cc"
    break;

  case 812: // not_empty_clients_list: not_empty_clients_list ","
#line 2847 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4417 "dhcp6_parser.cc"
    break;

  case 813: // $@125: %empty
#line 2852 "dhcp6_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4427 "dhcp6_parser.cc"
    break;

  case 814: // basic_auth: "{" $@125 clients_params "}"
#line 2856 "dhcp6_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4435 "dhcp6_parser.cc"
    break;

  case 817: // clients_params: clients_params ","
#line 2862 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4443 "dhcp6_parser.cc"
    break;

  case 825: // $@126: %empty
#line 2876 "dhcp6_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4452 "dhcp6_parser.cc"
    break;

  case 826: // user_file: "user-file" $@126 ":" "constant string"
#line 2879 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4462 "dhcp6_parser.cc"
    break;

  case 827: // $@127: %empty
#line 2885 "dhcp6_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4471 "dhcp6_parser.cc"
    break;

  case 828: // password_file: "password-file" $@127 ":" "constant string"
#line 2888 "dhcp6_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4481 "dhcp6_parser.cc"
    break;

  case 829: // $@128: %empty
#line 2896 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4493 "dhcp6_parser.cc"
    break;

  case 830: // dhcp_queue_control: "dhcp-queue-control" $@128 ":" "{" queue_control_params "}"
#line 2902 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4504 "dhcp6_parser.cc"
    break;

  case 833: // queue_control_params: queue_control_params ","
#line 2911 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4512 "dhcp6_parser.cc"
    break;

  case 840: // enable_queue: "enable-queue" ":" "boolean"
#line 2924 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4522 "dhcp6_parser.cc"
    break;

  case 841: // $@129: %empty
#line 2930 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4531 "dhcp6_parser.cc"
    break;

  case 842: // queue_type: "queue-type" $@129 ":" "constant string"
#line 2933 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4541 "dhcp6_parser.cc"
    break;

  case 843: // capacity: "capacity" ":" "integer"
#line 2939 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4551 "dhcp6_parser.cc"
    break;

  case 844: // $@130: %empty
#line 2945 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4560 "dhcp6_parser.cc"
    break;

  case 845: // arbitrary_map_entry: "constant string" $@130 ":" value
#line 2948 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4569 "dhcp6_parser.cc"
    break;

  case 846: // $@131: %empty
#line 2955 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4581 "dhcp6_parser.cc"
    break;

  case 847: // dhcp_ddns: "dhcp-ddns" $@131 ":" "{" dhcp_ddns_params "}"
#line 2961 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4592 "dhcp6_parser.cc"
    break;

  case 848: // $@132: %empty
#line 2968 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4602 "dhcp6_parser.cc"
    break;

  case 849: // sub_dhcp_ddns: "{" $@132 dhcp_ddns_params "}"
#line 2972 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4612 "dhcp6_parser.cc"
    break;

  case 852: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2980 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4620 "dhcp6_parser.cc"
    break;

  case 864: // enable_updates: "enable-updates" ":" "boolean"
#line 2998 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4630 "dhcp6_parser.cc"
    break;

  case 865: // $@133: %empty
#line 3004 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4639 "dhcp6_parser.cc"
    break;

  case 866: // server_ip: "server-ip" $@133 ":" "constant string"
#line 3007 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4649 "dhcp6_parser.cc"
    break;

  case 867: // server_port: "server-port" ":" "integer"
#line 3013 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4659 "dhcp6_parser.cc"
    break;

  case 868: // $@134: %empty
#line 3019 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4668 "dhcp6_parser.cc"
    break;

  case 869: // sender_ip: "sender-ip" $@134 ":" "constant string"
#line 3022 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4678 "dhcp6_parser.cc"
    break;

  case 870: // sender_port: "sender-port" ":" "integer"
#line 3028 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4688 "dhcp6_parser.cc"
    break;

  case 871: // max_queue_size: "max-queue-size" ":" "integer"
#line 3034 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4698 "dhcp6_parser.cc"
    break;

  case 872: // $@135: %empty
#line 3040 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4707 "dhcp6_parser.cc"
    break;

  case 873: // ncr_protocol: "ncr-protocol" $@135 ":" ncr_protocol_value
#line 3043 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4716 "dhcp6_parser.cc"
    break;

  case 874: // ncr_protocol_value: "UDP"
#line 3049 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4722 "dhcp6_parser.cc"
    break;

  case 875: // ncr_protocol_value: "TCP"
#line 3050 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4728 "dhcp6_parser.cc"
    break;

  case 876: // $@136: %empty
#line 3053 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4737 "dhcp6_parser.cc"
    break;

  case 877: // ncr_format: "ncr-format" $@136 ":" "JSON"
#line 3056 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4747 "dhcp6_parser.cc"
    break;

  case 878: // $@137: %empty
#line 3064 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4759 "dhcp6_parser.cc"
    break;

  case 879: // config_control: "config-control" $@137 ":" "{" config_control_params "}"
#line 3070 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4769 "dhcp6_parser.cc"
    break;

  case 880: // $@138: %empty
#line 3076 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4779 "dhcp6_parser.cc"
    break;

  case 881: // sub_config_control: "{" $@138 config_control_params "}"
#line 3080 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4788 "dhcp6_parser.cc"
    break;

  case 884: // config_control_params: config_control_params ","
#line 3088 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4796 "dhcp6_parser.cc"
    break;

  case 887: // $@139: %empty
#line 3098 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4808 "dhcp6_parser.cc"
    break;

  case 888: // config_databases: "config-databases" $@139 ":" "[" database_list "]"
#line 3104 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4817 "dhcp6_parser.cc"
    break;

  case 889: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3109 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4827 "dhcp6_parser.cc"
    break;

  case 890: // $@140: %empty
#line 3117 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4839 "dhcp6_parser.cc"
    break;

  case 891: // loggers: "loggers" $@140 ":" "[" loggers_entries "]"
#line 3123 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4848 "dhcp6_parser.cc"
    break;

  case 894: // loggers_entries: loggers_entries ","
#line 3132 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4856 "dhcp6_parser.cc"
    break;

  case 895: // $@141: %empty
#line 3138 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4866 "dhcp6_parser.cc"
    break;

  case 896: // logger_entry: "{" $@141 logger_params "}"
#line 3142 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4874 "dhcp6_parser.cc"
    break;

  case 899: // logger_params: logger_params ","
#line 3148 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4882 "dhcp6_parser.cc"
    break;

  case 907: // debuglevel: "debuglevel" ":" "integer"
#line 3162 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4892 "dhcp6_parser.cc"
    break;

  case 908: // $@142: %empty
#line 3168 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4901 "dhcp6_parser.cc"
    break;

  case 909: // severity: "severity" $@142 ":" "constant string"
#line 3171 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4911 "dhcp6_parser.cc"
    break;

  case 910: // $@143: %empty
#line 3177 "dhcp6_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4923 "dhcp6_parser.cc"
    break;

  case 911: // output_options_list: "output-options" $@143 ":" "[" output_options_list_content "]"
#line 3183 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4932 "dhcp6_parser.cc"
    break;

  case 914: // output_options_list_content: output_options_list_content ","
#line 3190 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4940 "dhcp6_parser.cc"
    break;

  case 915: // $@144: %empty
#line 3195 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4950 "dhcp6_parser.cc"
    break;

  case 916: // output_entry: "{" $@144 output_params_list "}"
#line 3199 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4958 "dhcp6_parser.cc"
    break;

  case 919: // output_params_list: output_params_list ","
#line 3205 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4966 "dhcp6_parser.cc"
    break;

  case 925: // $@145: %empty
#line 3217 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4975 "dhcp6_parser.cc"
    break;

  case 926: // output: "output" $@145 ":" "constant string"
#line 3220 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4985 "dhcp6_parser.cc"
    break;

  case 927: // flush: "flush" ":" "boolean"
#line 3226 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4995 "dhcp6_parser.cc"
    break;

  case 928: // maxsize: "maxsize" ":" "integer"
#line 3232 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5005 "dhcp6_parser.cc"
    break;

  case 929: // maxver: "maxver" ":" "integer"
#line 3238 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5015 "dhcp6_parser.cc"
    break;

  case 930: // $@146: %empty
#line 3244 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5024 "dhcp6_parser.cc"
    break;

  case 931: // pattern: "pattern" $@146 ":" "constant string"
#line 3247 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5034 "dhcp6_parser.cc"
    break;

  case 932: // $@147: %empty
#line 3253 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5046 "dhcp6_parser.cc"
    break;

  case 933: // compatibility: "compatibility" $@147 ":" "{" compatibility_params "}"
#line 3259 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5055 "dhcp6_parser.cc"
    break;

  case 936: // compatibility_params: compatibility_params ","
#line 3266 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5063 "dhcp6_parser.cc"
    break;

  case 939: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3275 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5073 "dhcp6_parser.cc"
    break;


#line 5077 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1354;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     525, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354,    44,    38,    56,    90,   104,
     114,   116,   118,   120,   136,   160,   169,   170,   196,   232,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,    38,   -78,
     147,   157,    57,   713,   453,   547,   510,   165,   220,   613,
     -88,   230,   174, -1354,   281,   286,   298,   302,   326, -1354,
      87, -1354, -1354, -1354, -1354, -1354, -1354, -1354,   345,   369,
     370,   401,   422,   432,   440,   442,   446,   447,   449,   450,
     451,   452, -1354,   454,   457,   458,   459,   461, -1354, -1354,
   -1354,   462,   463,   465,   475, -1354, -1354, -1354,   477, -1354,
   -1354, -1354, -1354, -1354, -1354,   479,   481,   485, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354,   488, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354,   489,   491,   493, -1354, -1354,
     494, -1354,   109, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354,   495,   496,   500,   507, -1354,   121, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354,   509,   511, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354,   133, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354,   514, -1354, -1354, -1354,
   -1354,   139, -1354, -1354, -1354, -1354, -1354, -1354,   515, -1354,
     519,   520, -1354, -1354, -1354, -1354, -1354, -1354, -1354,   150,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,   322,   338,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,   355,
   -1354, -1354,   523, -1354, -1354, -1354,   527, -1354, -1354,   363,
     380, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354,   531,   532,   533, -1354, -1354, -1354,
   -1354, -1354,   373,   436, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,   156, -1354,
   -1354, -1354,   534, -1354,   535, -1354,   536,   537, -1354, -1354,
   -1354, -1354, -1354,   162, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354,   540,   163, -1354, -1354, -1354, -1354,
      38,    38, -1354,   287,   541, -1354, -1354,   546,   548,   551,
     552,   553,   557,   334,   335,   336,   340,   341,   346,   349,
     353,   356,   354,   360,   368,   365,   371,   563,   375,   376,
     362,   381,   387,   581,   594,   597,   390,   391,   393,   397,
     601,   619,   624,   402,   625,   629,   630,   631,   632,   633,
     408,   416,   424,   651,   652,   653,   654,   655,   657,   658,
     660,   661,   438,   663,   664,   666,   667,   668,   671,   672,
     448,   455,   456,   673,   675, -1354,   157, -1354,   677,   460,
     471,   474,   476,    57, -1354,   678,   679,   680,   683,   684,
     478,   480,   701,   704,   705,   713, -1354,   707,   484,   453,
   -1354,   709,   486,   711,   499,   503,   547, -1354,   712,   717,
     718,   719,   728,   729,   731,   732, -1354,   510, -1354,   748,
     749,   526,   754,   771,   772,   487, -1354,   220,   773,   558,
     559,   561,   788, -1354,   613,   789,   790,   141, -1354,   565,
     792,   569,   794,   571,   572,   797,   801,   230, -1354,   802,
     579,   174, -1354, -1354, -1354,   804,   806,   582,   807,   808,
     809,   810,   823, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354,   584, -1354, -1354,
   -1354, -1354, -1354,  -115,   602,   603, -1354, -1354, -1354, -1354,
     826,   827,   828, -1354,   607,   609,   378,   832,   831,   615,
   -1354, -1354, -1354,   838,   839,   840,   841,   842,   845,   846,
     847,   848, -1354,   849,   850,   853,   852,   854,   626,   635,
   -1354, -1354, -1354,   855,   856, -1354,   859, -1354, -1354, -1354,
   -1354, -1354,   860,   861,   640,   641,   642, -1354, -1354,   859,
     643,   864, -1354,   645, -1354, -1354,   646, -1354,   647, -1354,
   -1354, -1354,   859,   859,   859,   859,   648,   649,   650,   656,
   -1354,   659,   662, -1354,   665,   669,   670, -1354, -1354,   674,
   -1354, -1354, -1354,   859, -1354,   676,   831, -1354, -1354,   681,
   -1354,   682, -1354, -1354,   142,   686, -1354,   874, -1354, -1354,
      38,   157, -1354,   174,    57,   364,   364,   873, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354,   875,   877,   878,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354,   880, -1354, -1354,
   -1354,   -90,    38,    69,   284,   881,   883,   884,    40,    84,
     -52,   210,   886,    13,   230, -1354, -1354,   887,  -129, -1354,
   -1354,   888,   891, -1354, -1354, -1354, -1354, -1354,   723, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354,   873, -1354,   191,   192,   256,
   -1354, -1354, -1354, -1354,   895,   896,   898,   900,   901,   902,
     903,   908,   909,   910, -1354,   911,   912, -1354, -1354, -1354,
   -1354, -1354,   273, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354,   274, -1354,   913,   843,
   -1354, -1354,   914,   915, -1354, -1354,   916,   918, -1354, -1354,
     917,   921, -1354, -1354,   919,   923, -1354, -1354, -1354,    81,
   -1354, -1354, -1354,   922, -1354, -1354, -1354,    85, -1354, -1354,
   -1354, -1354, -1354,   285, -1354, -1354, -1354, -1354,   254, -1354,
   -1354,   924,   926, -1354, -1354,   925,   929, -1354,   930,   931,
     932,   933,   934,   935,   300, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354,   937,   938,   939, -1354, -1354, -1354,
   -1354,   306, -1354, -1354, -1354, -1354, -1354, -1354,   940,   941,
     942, -1354,   319, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354,   943, -1354,   944, -1354, -1354, -1354, -1354, -1354,
   -1354,   320, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
     927,   946, -1354,   947, -1354,   948, -1354, -1354, -1354,   337,
   -1354, -1354, -1354, -1354, -1354,   339, -1354,   255, -1354,   949,
   -1354,   357, -1354, -1354,   690, -1354,   950,   951, -1354, -1354,
     952,   954, -1354, -1354,   953,   956, -1354, -1354, -1354,   955,
     959,   960,   961,   699,   720,   727,   730,   738,   739,   740,
     741,   742,   743,   968,   744,   745,   972,   973,   975,   976,
     364, -1354, -1354,   364, -1354,   873,   713, -1354,   875,   220,
   -1354,   877,   613, -1354,   878,  1105, -1354,   880,   -90, -1354,
   -1354,    69, -1354,   978,   979,   284, -1354,   382,   881, -1354,
     510, -1354,   883,   -88, -1354,   884,   758,   761,   762,   764,
     765,   775,    40, -1354,  1001,  1009,   796,   799,   818,    84,
   -1354,   786,   822,   833,   -52, -1354,  1013,  1016,  1025,   835,
    1030,   821,   210, -1354,   210, -1354,   886,   834,  1032,   844,
    1033,    13, -1354, -1354,   343,   887, -1354,   906,  -129, -1354,
   -1354,  1064,  1081,   453, -1354,   888,   547, -1354,   891, -1354,
   -1354,   867,   876,   904,   920, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354,   280, -1354, -1354,   957,   958,
     962,   963, -1354,   358, -1354,   359, -1354,  1129, -1354,  1131,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
     361, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,   964,
     965, -1354, -1354, -1354,  1136, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354,  1134,  1140, -1354, -1354,
   -1354, -1354, -1354, -1354,  1137, -1354,   367, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354,   101,   966, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354,   188,   970,   971, -1354,  1139,
   -1354, -1354,   377, -1354, -1354,   974, -1354,    38, -1354, -1354,
    1144, -1354, -1354, -1354, -1354, -1354,   379, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354,   977,   417, -1354,   419, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354,  1105, -1354, -1354, -1354,
    1145,  1146,   936, -1354,   382, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,    25, -1354,
   -1354, -1354,  1147,   980,  1148,   343, -1354, -1354, -1354, -1354,
   -1354,   988,   993, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354,   420, -1354, -1354, -1354, -1354, -1354,  1162, -1354,
     994, -1354, -1354, -1354,  1164,  1165,  1177,  1182,    25, -1354,
    1180, -1354,  1018,   995,   996,  1194, -1354, -1354,   293, -1354,
   -1354, -1354, -1354, -1354,  1193,  -108,  1180, -1354, -1354,  1138,
    1199, -1354, -1354,  1201,  1203,  1220, -1354,   421, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354,    68, -1354,  1193,  1221,   998,
    1002,  1004,  1222,  -108, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354,   435, -1354, -1354, -1354, -1354,  1006, -1354, -1354,
   -1354,  1007, -1354,  1225,  1232,    68, -1354, -1354, -1354,  1010,
    1011, -1354, -1354, -1354
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   199,     9,   385,    11,
     593,    13,   622,    15,   655,    17,   508,    19,   517,    21,
     556,    23,   347,    25,   848,    27,   880,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   657,     0,   519,   558,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   141,   878,   197,   218,   220,   222,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   187,     0,     0,     0,     0,     0,   160,   167,
     169,     0,     0,     0,     0,   376,   506,   547,     0,   190,
     192,   173,   451,   609,   611,     0,     0,     0,   303,   322,
     312,   292,   693,   646,   338,   359,   725,     0,   324,   750,
     752,   829,   846,   180,   182,     0,     0,     0,   890,   932,
       0,   140,     0,    69,    72,    73,    74,    75,    76,    77,
      78,    79,    80,   111,   112,   113,   114,   115,    81,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   117,
     118,   129,   130,   131,   107,   137,   138,   139,   133,   134,
     135,    84,    85,    86,    87,   104,    88,    90,    89,   132,
      94,    95,    82,   108,   109,   110,    83,    92,    93,   102,
     103,   105,    91,    96,    97,    98,    99,   100,   101,   106,
     116,   136,   212,     0,     0,     0,     0,   211,     0,   201,
     204,   205,   206,   207,   208,   209,   210,   584,   613,   436,
     438,   440,     0,     0,   444,   442,   690,   435,   390,   391,
     392,   393,   394,   395,   396,   397,   415,   416,   417,   418,
     419,   422,   423,   424,   425,   426,   427,   428,   429,   430,
     431,   420,   421,   432,   433,   434,     0,   387,   401,   402,
     403,   406,   407,   409,   410,   411,   404,   405,   398,   399,
     413,   414,   400,   408,   412,   606,     0,   605,   601,   602,
     600,     0,   595,   598,   599,   603,   604,   639,     0,   642,
       0,     0,   638,   632,   633,   631,   630,   636,   637,     0,
     624,   627,   628,   634,   635,   629,   688,   674,   676,   678,
     680,   682,   684,   686,   673,   670,   671,   672,     0,   658,
     659,   664,   665,   666,   662,   667,   668,   669,   663,     0,
     537,   266,     0,   541,   539,   544,     0,   533,   534,     0,
     520,   521,   524,   536,   525,   526,   527,   543,   528,   529,
     530,   531,   532,   575,     0,     0,     0,   582,   573,   574,
     577,   578,     0,   559,   560,   563,   564,   565,   566,   567,
     568,   569,   572,   570,   571,   355,   357,   352,     0,   349,
     353,   354,     0,   865,     0,   868,     0,     0,   872,   876,
     863,   861,   862,     0,   850,   853,   854,   855,   856,   857,
     858,   859,   860,   887,     0,     0,   882,   885,   886,    47,
      52,     0,    39,    45,     0,    66,    62,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    60,    71,    68,     0,     0,
       0,     0,     0,   203,   200,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   389,   386,     0,     0,   597,
     594,     0,     0,     0,     0,     0,   626,   623,     0,     0,
       0,     0,     0,     0,     0,     0,   656,   661,   509,     0,
       0,     0,     0,     0,     0,     0,   518,   523,     0,     0,
       0,     0,     0,   557,   562,     0,     0,   351,   348,     0,
       0,     0,     0,     0,     0,     0,     0,   852,   849,     0,
       0,   884,   881,    51,    43,     0,     0,     0,     0,     0,
       0,     0,     0,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,     0,   185,   186,
     157,   158,   159,     0,     0,     0,   171,   172,   179,   184,
       0,     0,     0,   189,     0,     0,     0,     0,     0,     0,
     446,   447,   448,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   749,     0,     0,     0,     0,     0,     0,     0,
     194,   195,   196,     0,     0,    70,     0,   214,   215,   216,
     217,   202,     0,     0,     0,     0,     0,   449,   450,     0,
       0,     0,   388,     0,   608,   596,     0,   641,     0,   644,
     645,   625,     0,     0,     0,     0,     0,     0,     0,     0,
     660,     0,     0,   535,     0,     0,     0,   546,   522,     0,
     579,   580,   581,     0,   561,     0,     0,   350,   864,     0,
     867,     0,   870,   871,     0,     0,   851,     0,   889,   883,
       0,     0,   142,     0,     0,     0,     0,   224,   188,   162,
     163,   164,   165,   166,   161,   168,   170,   378,   510,   549,
     191,   193,   175,   176,   177,   178,   174,   453,    40,   610,
     612,     0,    48,     0,     0,     0,   648,   340,     0,     0,
       0,     0,   754,     0,     0,   181,   183,     0,     0,    53,
     213,   586,   615,   437,   439,   441,   445,   443,     0,   607,
     640,   643,   689,   675,   677,   679,   681,   683,   685,   687,
     538,   267,   542,   540,   545,   576,   583,   356,   358,   866,
     869,   874,   875,   873,   877,   224,    44,     0,     0,     0,
     257,   259,   261,   263,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   276,     0,     0,   284,   286,   288,
     290,   256,     0,   231,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   248,   249,   250,
     251,   247,   252,   253,   254,   255,     0,   229,     0,   225,
     226,   383,     0,   379,   380,   515,     0,   511,   512,   554,
       0,   550,   551,   458,     0,   454,   455,   310,   311,     0,
     305,   308,   309,     0,   320,   321,   317,     0,   314,   318,
     319,   299,   301,     0,   294,   297,   298,   698,     0,   695,
     653,     0,   649,   650,   345,     0,   341,   342,     0,     0,
       0,     0,     0,     0,     0,   361,   364,   365,   366,   367,
     368,   369,   739,   745,     0,     0,     0,   738,   735,   736,
     737,     0,   727,   730,   733,   731,   732,   734,     0,     0,
       0,   334,     0,   326,   329,   330,   331,   332,   333,   776,
     781,   783,     0,   787,     0,   775,   769,   770,   771,   773,
     774,     0,   761,   764,   765,   766,   767,   772,   768,   759,
       0,   755,   756,     0,   841,     0,   844,   837,   838,     0,
     831,   834,   835,   836,   839,     0,   895,     0,   892,     0,
     938,     0,   934,   937,    55,   591,     0,   587,   588,   620,
       0,   616,   617,   692,     0,     0,    64,   879,   198,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     233,   219,   221,     0,   223,   228,     0,   377,   382,   519,
     507,   514,   558,   548,   553,     0,   452,   457,   307,   304,
     323,   316,   313,     0,     0,   296,   293,   700,   697,   694,
     657,   647,   652,     0,   339,   344,     0,     0,     0,     0,
       0,     0,   363,   360,     0,     0,     0,     0,     0,   729,
     726,     0,     0,     0,   328,   325,     0,     0,     0,     0,
       0,     0,   763,   751,     0,   753,   758,     0,     0,     0,
       0,   833,   830,   847,     0,   894,   891,     0,   936,   933,
      57,     0,    56,     0,   585,   590,     0,   614,   619,   691,
     888,     0,     0,     0,     0,   265,   268,   269,   270,   271,
     272,   273,   274,   283,   275,     0,   281,   282,     0,     0,
       0,     0,   232,     0,   227,     0,   381,     0,   513,     0,
     552,   505,   476,   477,   478,   480,   481,   482,   467,   468,
     485,   486,   487,   488,   489,   492,   493,   494,   495,   496,
     497,   498,   499,   500,   501,   490,   491,   502,   503,   504,
     463,   464,   465,   466,   474,   475,   471,   472,   473,   479,
       0,   460,   469,   483,   484,   470,   456,   306,   315,     0,
       0,   295,   720,   722,     0,   718,   712,   713,   714,   715,
     716,   717,   719,   709,   710,   711,     0,   701,   702,   705,
     706,   707,   708,   696,     0,   651,     0,   343,   370,   371,
     372,   373,   374,   375,   362,     0,     0,   744,   747,   748,
     728,   335,   336,   337,   327,     0,     0,     0,   785,     0,
     786,   762,     0,   757,   840,     0,   843,     0,   832,   910,
       0,   908,   906,   900,   904,   905,     0,   897,   902,   903,
     901,   893,   939,   935,    54,    59,     0,   589,     0,   618,
     258,   260,   262,   264,   278,   279,   280,   277,   285,   287,
     289,   291,   230,   384,   516,   555,   462,   459,   300,   302,
       0,     0,     0,   699,   704,   654,   346,   741,   742,   743,
     740,   746,   778,   779,   780,   777,   782,   784,     0,   760,
     842,   845,     0,     0,     0,   899,   896,    58,   592,   621,
     461,     0,     0,   724,   703,   799,   802,   804,   806,   798,
     797,   796,     0,   789,   792,   793,   794,   795,     0,   907,
       0,   898,   721,   723,     0,     0,     0,     0,   791,   788,
       0,   909,     0,     0,     0,     0,   790,   915,     0,   912,
     801,   800,   803,   805,   808,     0,   914,   911,   813,     0,
     809,   810,   925,     0,     0,     0,   930,     0,   917,   920,
     921,   922,   923,   924,   913,     0,   807,   812,     0,     0,
       0,     0,     0,   919,   916,   825,   827,   824,   818,   820,
     822,   823,     0,   815,   819,   821,   811,     0,   927,   928,
     929,     0,   918,     0,     0,   817,   814,   926,   931,     0,
       0,   816,   826,   828
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354,     0, -1354,  -581, -1354,
     524, -1354, -1354, -1354, -1354,   119, -1354,  -624, -1354, -1354,
   -1354,   -71, -1354, -1354, -1354, -1354, -1354, -1354, -1354,   508,
     726, -1354, -1354,   -61,   -58,   -27,   -25,    -7,    12,    -1,
      19,    30,    31,    36,    37,    41, -1354,    43,    47,    49,
      53, -1354, -1354,    55, -1354,    59, -1354,    60,    61,    65,
   -1354, -1354,    67,    71, -1354,    72, -1354,    73, -1354, -1354,
   -1354, -1354, -1354,    75, -1354,    77, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354,   512,   721, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,   434, -1354,
     202, -1354,  -712,   212, -1354, -1354, -1353, -1354, -1349, -1354,
   -1354, -1354, -1354,   -41, -1354,  -746, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,  -765,
   -1354,  -758, -1354,  -754, -1354, -1354, -1354, -1354, -1354, -1354,
     185, -1354, -1354, -1354, -1354, -1354, -1354, -1354,   197,  -737,
   -1354, -1354, -1354, -1354,   193, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354,   164, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
     187, -1354, -1354, -1354,   190,   689, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354,   178, -1354, -1354, -1354, -1354, -1354, -1354,
   -1023, -1354, -1354, -1354,   222, -1354, -1354, -1354,   225,   733,
   -1354, -1354, -1020, -1354, -1016, -1354,    80, -1354,    86, -1354,
      78,    79,    83, -1354, -1015, -1354, -1354, -1354, -1354,   215,
   -1354, -1354,   -32,  1198, -1354, -1354, -1354, -1354, -1354,   226,
   -1354, -1354, -1354,   227, -1354,   715, -1354,   -57, -1354, -1354,
   -1354, -1354, -1354,   -54, -1354, -1354, -1354, -1354, -1354,   -55,
   -1354, -1354, -1354,   224, -1354, -1354, -1354,   228, -1354,   710,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354,   161, -1354, -1354, -1354,   168,   746,
   -1354, -1354,   -64,   -45, -1354,   -14, -1354, -1354, -1354, -1354,
   -1354,   167, -1354, -1354, -1354,   172,   747, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354,   -59, -1354, -1354, -1354,   216, -1354,
   -1354, -1354,   231, -1354,   751,   516, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1014, -1354, -1354, -1354, -1354, -1354,   238, -1354, -1354,
   -1354,   -18, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354,   221, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354,   203, -1354,   207,
     211, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354,   -56, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354,   -92, -1354, -1354,  -119, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354,   206, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354,   545,   735, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354,   587,   736, -1354, -1354,
   -1354, -1354, -1354, -1354,   209, -1354, -1354,    -6, -1354, -1354,
   -1354, -1354, -1354, -1354,   -53, -1354, -1354,   -85, -1354, -1354,
   -1354, -1354, -1354, -1354, -1354, -1354, -1354, -1354,   213, -1354
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     759,    87,    88,    41,    68,    84,    85,   780,  1004,  1121,
    1122,   841,    43,    70,    90,   444,    91,    45,    71,   162,
     163,   164,   447,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   473,   744,   183,   474,   184,   475,   185,   186,   187,
     486,   756,   188,   189,   508,   190,   509,   191,   192,   193,
     194,   467,   195,   196,   484,   197,   485,   198,   199,   200,
     201,   449,    47,    72,   238,   239,   240,   518,   241,   242,
     243,   244,   202,   450,   203,   451,   204,   452,   868,   869,
     870,  1043,   842,   843,   844,  1019,   845,  1020,   846,  1021,
     847,  1022,   848,   849,   560,   850,   851,   852,   853,   854,
     855,   856,   857,   858,  1033,  1297,   859,   860,   861,   862,
    1036,   863,  1037,   864,  1038,   865,  1039,   205,   496,   903,
     904,   905,  1063,   906,  1064,   206,   493,   889,   890,   891,
     892,   207,   495,   897,   898,   899,   900,   208,   494,   209,
     503,   952,   953,   954,   955,   956,   210,   499,   915,   916,
     917,  1073,    63,    80,   408,   409,   410,   575,   411,   576,
     211,   500,   924,   925,   926,   927,   928,   929,   930,   931,
     212,   480,   872,   873,   874,  1046,    49,    73,   286,   287,
     288,   527,   289,   528,   290,   529,   291,   533,   292,   532,
     213,   214,   215,   296,   297,   216,   487,   884,   885,   886,
    1055,  1200,  1201,   217,   481,    57,    77,   876,   877,   878,
    1049,    59,    78,   369,   370,   371,   372,   373,   374,   375,
     559,   376,   563,   377,   562,   378,   379,   564,   380,   218,
     482,   880,   881,   882,  1052,    61,    79,   392,   393,   394,
     395,   396,   568,   397,   398,   399,   400,   401,   402,   572,
     299,   525,  1006,  1007,  1008,  1123,    51,    74,   311,   312,
     313,   537,   314,   219,   488,   220,   489,   302,   526,  1010,
    1011,  1012,  1126,    53,    75,   329,   330,   331,   541,   332,
     333,   543,   334,   335,   221,   498,   911,   912,   913,  1070,
      55,    76,   348,   349,   350,   351,   549,   352,   550,   353,
     551,   354,   552,   355,   553,   356,   554,   357,   555,   358,
     548,   304,   534,  1014,   222,   497,   908,   909,  1067,  1226,
    1227,  1228,  1229,  1230,  1310,  1231,  1311,  1232,   223,   501,
     941,   942,   943,  1084,  1320,   944,   945,  1085,   946,   947,
     224,   225,   504,   226,   505,   980,   981,   982,  1104,   971,
     972,   973,  1096,  1325,   974,  1097,   975,  1098,   976,   977,
     978,  1100,  1352,  1353,  1354,  1364,  1381,  1355,  1365,  1356,
    1366,  1357,  1367,  1389,  1390,  1391,  1405,  1422,  1423,  1424,
    1433,  1425,  1434,   227,   506,   989,   990,   991,   992,  1108,
     993,   994,  1110,   228,   507,    65,    81,   423,   424,   425,
     426,   580,   427,   428,   582,   429,   430,   431,   585,   813,
     432,   586,   229,   448,    67,    82,   435,   436,   437,   589,
     438,   230,   513,   997,   998,  1114,  1276,  1277,  1278,  1279,
    1334,  1280,  1332,  1378,  1379,  1385,  1397,  1398,  1399,  1408,
    1400,  1401,  1402,  1403,  1412,   231,   514,  1001,  1002,  1003
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     161,   237,   257,   307,   322,   344,   966,   367,   388,   407,
     420,   326,   258,   967,   303,   259,    38,   968,   298,   310,
     325,   345,   390,   938,   866,   391,   896,   245,   300,   315,
     327,   346,  1191,   381,   403,  1192,   421,   368,   389,  1193,
    1199,  1205,   887,    31,    30,    32,   260,    33,   261,  1345,
     405,   406,  1418,   133,   134,   786,  1419,   758,   246,   301,
     316,   328,   347,    42,   382,   404,   262,   422,   792,   793,
     794,   795,   264,   232,   233,   234,   235,   236,   739,   740,
     741,   742,  1418,   999,  1058,   263,  1419,  1059,  1061,   806,
     445,  1062,   265,   821,   822,   446,  1392,    44,   160,  1393,
    1394,  1395,  1396,   266,   267,   948,   949,   950,   932,   268,
     269,    46,   516,   825,   270,   743,   271,   517,   133,   134,
     272,    48,   273,    50,   523,    52,   274,    54,   275,   524,
     133,   134,   276,   277,   278,   758,   535,   888,   279,   160,
     280,   536,   539,    56,   281,   282,   283,   540,   284,    86,
     285,   293,   294,   546,   308,   323,   295,    89,   547,   577,
     309,   324,   133,   134,   578,   587,   591,    58,    92,    93,
     588,   592,    94,   133,   134,   160,    60,    62,    95,    96,
      97,   918,   919,   920,   921,   922,   923,   433,   434,   133,
     134,   983,   984,   985,   516,   591,  1346,  1347,  1348,  1016,
    1017,   887,   894,    64,   895,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   933,   934,   935,   936,    66,
     986,   126,  1415,  1416,   360,   128,   129,   130,   131,  1317,
    1318,  1319,   160,   132,   837,   838,   839,  1068,  1115,   523,
    1069,  1116,   133,   134,  1018,    34,    35,    36,    37,   135,
     136,   137,   138,   139,   140,   141,  1040,  1040,   142,   405,
     406,  1041,  1042,  1191,   160,   143,  1192,   439,  1065,   440,
    1193,  1199,  1205,  1066,   144,   160,  1386,   145,   361,  1387,
     362,   363,   441,  1082,   146,   364,   365,   366,  1083,  1089,
     442,   160,   147,   148,  1090,   133,   134,   149,   150,  1294,
    1295,  1296,  1094,  1102,   896,   133,   134,  1095,  1103,   443,
     556,  1153,   811,   812,   151,   133,   134,   966,   152,   966,
    1111,   557,   587,   938,   967,  1112,   967,  1113,   968,   453,
     968,  1322,  1323,  1324,   153,   154,   155,   156,   157,   158,
    1118,  1040,   535,   558,  1306,  1119,  1302,  1303,   159,  1307,
     577,   566,   959,   454,   455,  1316,   960,   961,   962,   963,
    1102,   573,  1335,   567,   160,  1329,   964,  1336,   820,   821,
     822,   823,   824,   825,   826,   827,   828,   829,   830,   831,
     832,   833,   834,   901,   902,   456,   835,   836,   837,   838,
     839,   840,   412,   413,   414,   415,   416,   417,   418,   419,
     539,   361,   546,  1368,  1413,  1338,   457,  1339,  1369,  1414,
      98,    99,   100,   101,   102,   103,   458,   160,  1435,   574,
     593,   594,   361,  1436,   459,   161,   460,   160,   133,   134,
     461,   462,   237,   463,   464,   465,   466,   160,   468,   127,
     361,   469,   470,   471,   257,   472,   476,   477,   307,   478,
     752,   753,   754,   755,   258,   322,   303,   259,   245,   479,
     298,   483,   326,   490,   310,   491,   344,   133,   134,   492,
     300,   325,   502,   510,   315,   511,   367,   512,   515,   519,
     520,   327,   345,   388,   521,  1212,  1213,  1214,   260,   246,
     261,   522,   346,   530,   595,   531,   420,   390,   538,   542,
     391,   301,   381,   544,   545,   316,   368,   561,   262,   403,
     127,   565,   328,   389,   264,   569,   570,   571,   579,   581,
     583,   584,   421,   347,   590,   596,  1269,   263,  1270,  1271,
     597,   305,   598,   382,   265,   599,   600,   601,   133,   134,
     404,   602,   603,   604,   605,   266,   267,   617,   606,   607,
     160,   268,   269,   422,   608,   254,   270,   609,   271,   255,
     306,   610,   272,   612,   273,   623,   611,   127,   274,   613,
     275,   160,   620,   615,   276,   277,   278,   614,   624,   616,
     279,   625,   280,   618,   619,   630,   281,   282,   283,   160,
     284,   621,   285,   293,   294,   133,   134,   622,   295,   308,
     626,   627,   628,   631,   127,   309,   323,   629,   632,   634,
     633,   336,   324,   635,   636,   637,   638,   639,   640,   337,
     338,   339,   340,   341,   342,   343,   641,   317,   318,   319,
     320,   321,   133,   134,   642,   643,   644,   645,   646,   647,
     161,   648,   649,   237,   650,   651,   652,   653,   654,   254,
     655,   656,   657,   255,   306,   658,   659,   663,   660,   664,
     160,   666,   672,   673,   674,   661,   662,   675,   676,   245,
     667,   361,   383,   362,   363,   384,   385,   386,   937,   951,
     965,   668,   669,   420,   670,   679,   677,  1000,   680,   681,
     678,   683,   684,   686,   687,   688,   692,   707,   133,   134,
     246,   693,   694,   695,   939,   957,   969,   689,   987,   421,
     816,   690,   696,   697,   387,   698,   699,   160,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,   701,   702,   703,   940,   958,   970,   704,   988,
     422,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   160,   705,   706,   709,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   710,   711,
     127,   712,   713,   715,   716,   718,   719,   720,   721,   722,
     723,   724,   129,   130,   131,   725,   727,   728,   730,   732,
     247,   738,   248,   731,   733,   734,   735,   736,   133,   134,
     249,   250,   251,   252,   253,   135,   136,   137,   737,   745,
     746,   747,   748,   749,   750,   254,   751,   757,    32,   255,
     160,   143,   760,   761,   762,   763,  1045,   765,   764,   256,
     766,   767,   337,   775,   768,   769,   770,   771,   772,   773,
     777,   774,   776,   778,   779,   781,   782,   783,   784,   785,
     787,   788,   789,   790,   791,   796,   797,   798,   814,   815,
     867,   893,   871,   799,   875,   879,   800,   883,   907,   801,
     910,   914,   802,   979,   996,  1005,   803,   804,  1009,  1023,
    1024,   805,  1025,   807,  1026,  1027,  1028,  1029,   809,   810,
     153,   154,  1030,  1031,  1032,  1034,  1035,  1120,  1048,  1044,
    1047,  1051,  1050,  1053,  1054,  1056,  1057,  1135,  1060,  1072,
    1071,  1074,  1075,  1105,  1076,  1077,  1078,  1079,  1080,  1081,
     160,  1086,  1087,  1088,  1091,  1092,  1093,  1099,  1101,  1106,
    1136,  1107,  1109,  1117,  1125,  1137,  1124,  1128,  1127,  1131,
    1138,  1129,  1130,  1132,  1133,  1134,  1139,  1140,  1141,  1142,
    1143,  1144,  1145,  1147,  1146,   257,  1148,  1149,   367,  1150,
    1151,   388,  1209,  1210,  1161,   258,  1238,   303,   259,  1239,
    1240,   298,  1241,  1242,  1162,   390,  1215,  1163,   391,   344,
    1202,   300,   407,  1243,   381,  1245,  1216,   403,   368,  1217,
    1203,   389,  1223,  1246,  1190,   345,  1251,  1255,   937,   260,
    1256,   261,  1224,   951,  1247,   346,  1222,  1248,  1164,  1257,
    1165,   965,   301,   965,  1259,   382,  1265,  1267,   404,   262,
    1218,  1204,  1219,  1272,   939,   264,  1249,  1000,  1166,   957,
    1252,  1260,   307,  1225,  1168,   322,   347,   969,   263,   969,
    1220,  1253,   326,  1258,  1264,   265,   987,  1167,   310,  1274,
    1284,   325,  1266,  1273,  1169,   940,   266,   267,   315,  1221,
     958,   327,   268,   269,  1285,  1170,  1171,   270,   970,   271,
     970,  1172,  1173,   272,  1290,   273,  1174,   988,  1175,   274,
    1275,   275,  1176,  1291,  1177,   276,   277,   278,  1178,   316,
    1179,   279,   328,   280,  1180,  1181,  1182,   281,   282,   283,
    1183,   284,  1184,   285,   293,   294,  1185,  1186,  1187,   295,
    1188,  1292,  1189,  1196,  1197,  1194,  1282,  1304,  1198,  1305,
    1312,  1195,  1313,  1314,  1406,  1315,  1328,  1293,  1333,  1341,
    1342,  1358,  1360,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,  1343,  1370,  1372,  1373,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,  1374,   127,   361,  1298,  1299,  1375,  1377,  1380,  1300,
    1301,  1308,  1309,  1321,   129,   130,   131,  1326,  1327,  1384,
    1388,  1330,  1407,   308,  1337,  1409,   323,  1410,  1359,   309,
     133,   134,   324,   250,   251,  1362,   253,   135,   136,   137,
    1363,  1371,  1382,  1383,  1411,  1427,  1431,   254,  1428,  1439,
    1429,   255,  1430,  1437,  1438,  1161,  1440,  1442,  1443,   817,
     808,   256,   665,  1215,   671,  1162,   819,  1154,  1163,  1015,
    1211,  1202,  1152,  1216,  1208,  1207,  1217,  1349,  1254,  1223,
    1244,  1203,  1237,  1236,  1272,  1190,   717,  1331,   682,  1224,
    1156,  1155,  1206,  1222,  1340,   359,  1157,  1158,  1160,  1164,
    1159,  1165,   708,  1350,   714,   685,  1287,  1218,  1235,  1219,
    1274,  1286,  1204,   691,  1273,  1289,  1344,  1349,  1288,  1166,
    1225,  1234,   153,   154,  1013,  1168,  1233,  1220,   700,  1263,
    1250,  1262,  1376,  1261,  1351,  1426,  1441,  1268,  1167,   995,
     818,  1275,   726,  1350,  1281,  1169,  1221,   729,  1432,  1361,
       0,  1283,   160,  1404,  1417,     0,  1170,  1171,     0,     0,
       0,     0,  1172,  1173,     0,     0,     0,  1174,     0,  1175,
       0,     0,     0,  1176,  1351,  1177,     0,     0,     0,  1178,
    1420,  1179,     0,     0,  1417,  1180,  1181,  1182,     0,     0,
       0,  1183,     0,  1184,     0,     0,     0,  1185,  1186,  1187,
       0,  1188,     0,  1189,  1196,  1197,  1194,     0,     0,  1198,
    1420,  1421,  1195,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1421
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,   771,    78,    79,    80,
      81,    75,    73,   771,    73,    73,    16,   771,    73,    74,
      75,    76,    79,   769,   736,    79,   763,    72,    73,    74,
      75,    76,  1055,    78,    79,  1055,    81,    78,    79,  1055,
    1055,  1055,   132,     5,     0,     7,    73,     9,    73,    24,
     138,   139,  1405,   105,   106,   679,  1405,   638,    72,    73,
      74,    75,    76,     7,    78,    79,    73,    81,   692,   693,
     694,   695,    73,    16,    17,    18,    19,    20,   193,   194,
     195,   196,  1435,   212,     3,    73,  1435,     6,     3,   713,
       3,     6,    73,    25,    26,     8,   204,     7,   227,   207,
     208,   209,   210,    73,    73,   157,   158,   159,    24,    73,
      73,     7,     3,    29,    73,   230,    73,     8,   105,   106,
      73,     7,    73,     7,     3,     7,    73,     7,    73,     8,
     105,   106,    73,    73,    73,   716,     3,   227,    73,   227,
      73,     8,     3,     7,    73,    73,    73,     8,    73,   227,
      73,    73,    73,     3,    74,    75,    73,    10,     8,     3,
      74,    75,   105,   106,     8,     3,     3,     7,    11,    12,
       8,     8,    15,   105,   106,   227,     7,     7,    21,    22,
      23,   141,   142,   143,   144,   145,   146,    13,    14,   105,
     106,   178,   179,   180,     3,     3,   171,   172,   173,     8,
       8,   132,   133,     7,   135,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,   151,   152,   153,   154,     7,
     227,    76,   174,   175,    24,    88,    89,    90,    91,   148,
     149,   150,   227,    96,    44,    45,    46,     3,     3,     3,
       6,     6,   105,   106,     8,   227,   228,   229,   230,   112,
     113,   114,   115,   116,   117,   118,     3,     3,   121,   138,
     139,     8,     8,  1306,   227,   128,  1306,     6,     3,     3,
    1306,  1306,  1306,     8,   137,   227,     3,   140,    78,     6,
      80,    81,     4,     3,   147,    85,    86,    87,     8,     3,
       8,   227,   155,   156,     8,   105,   106,   160,   161,    39,
      40,    41,     3,     3,  1061,   105,   106,     8,     8,     3,
       8,  1043,   190,   191,   177,   105,   106,  1102,   181,  1104,
       3,     3,     3,  1089,  1102,     8,  1104,     8,  1102,     4,
    1104,   163,   164,   165,   197,   198,   199,   200,   201,   202,
       3,     3,     3,     8,     3,     8,     8,     8,   211,     8,
       3,     8,   162,     4,     4,     8,   166,   167,   168,   169,
       3,     8,     3,     3,   227,     8,   176,     8,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,   119,   120,     4,    42,    43,    44,    45,
      46,    47,   182,   183,   184,   185,   186,   187,   188,   189,
       3,    78,     3,     3,     3,     8,     4,     8,     8,     8,
      48,    49,    50,    51,    52,    53,     4,   227,     3,     3,
     440,   441,    78,     8,     4,   516,     4,   227,   105,   106,
       4,     4,   523,     4,     4,     4,     4,   227,     4,    77,
      78,     4,     4,     4,   535,     4,     4,     4,   539,     4,
      92,    93,    94,    95,   535,   546,   535,   535,   523,     4,
     535,     4,   546,     4,   539,     4,   557,   105,   106,     4,
     535,   546,     4,     4,   539,     4,   567,     4,     4,     4,
       4,   546,   557,   574,     4,   123,   124,   125,   535,   523,
     535,     4,   557,     4,   227,     4,   587,   574,     4,     4,
     574,   535,   567,     4,     4,   539,   567,     4,   535,   574,
      77,     4,   546,   574,   535,     4,     4,     4,     4,     4,
       4,     4,   587,   557,     4,     4,   203,   535,   205,   206,
       4,    98,     4,   567,   535,     4,     4,     4,   105,   106,
     574,     4,   228,   228,   228,   535,   535,     4,   228,   228,
     227,   535,   535,   587,   228,   122,   535,   228,   535,   126,
     127,   228,   535,   229,   535,     4,   230,    77,   535,   229,
     535,   227,   230,   228,   535,   535,   535,   229,     4,   228,
     535,     4,   535,   228,   228,     4,   535,   535,   535,   227,
     535,   230,   535,   535,   535,   105,   106,   230,   535,   539,
     230,   230,   229,     4,    77,   539,   546,   230,     4,     4,
     228,   121,   546,     4,     4,     4,     4,     4,   230,   129,
     130,   131,   132,   133,   134,   135,   230,   100,   101,   102,
     103,   104,   105,   106,   230,     4,     4,     4,     4,     4,
     731,     4,     4,   734,     4,     4,   228,     4,     4,   122,
       4,     4,     4,   126,   127,     4,     4,     4,   230,     4,
     227,     4,     4,     4,     4,   230,   230,     4,     4,   734,
     230,    78,    79,    80,    81,    82,    83,    84,   769,   770,
     771,   230,   228,   774,   228,     4,   228,   778,     4,     4,
     230,     4,   228,     4,   228,     4,     4,   230,   105,   106,
     734,     4,     4,     4,   769,   770,   771,   228,   773,   774,
     730,   228,     4,     4,   121,     4,     4,   227,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,     4,     4,   228,   769,   770,   771,     4,   773,
     774,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,   227,     4,     4,     4,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,   230,   230,
      77,   230,     4,     4,     4,   230,     4,   228,     4,   228,
     228,     4,    89,    90,    91,     4,     4,   228,     4,   227,
      97,   227,    99,     7,     7,     7,     7,     7,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,     5,   227,
     227,     5,     5,     5,   227,   122,   227,     5,     7,   126,
     227,   128,   227,     5,     5,     5,     3,     5,     7,   136,
       5,     5,   129,   227,     7,     7,     7,     7,     5,     7,
       5,     7,   227,     7,     5,     5,     5,   227,   227,   227,
     227,     7,   227,   227,   227,   227,   227,   227,   192,     5,
       7,   762,     7,   227,     7,     7,   227,     7,     7,   227,
       7,     7,   227,     7,     7,     7,   227,   227,     7,     4,
       4,   227,     4,   227,     4,     4,     4,     4,   227,   227,
     197,   198,     4,     4,     4,     4,     4,   227,     3,     6,
       6,     3,     6,     6,     3,     6,     3,   228,     6,     3,
       6,     6,     3,     6,     4,     4,     4,     4,     4,     4,
     227,     4,     4,     4,     4,     4,     4,     4,     4,     3,
     230,     4,     4,     4,     3,   228,     6,     3,     6,     4,
     230,     8,     6,     4,     4,     4,   228,   228,   228,   228,
     228,   228,     4,   228,   230,  1046,     4,     4,  1049,     4,
       4,  1052,     4,     4,  1055,  1046,   228,  1046,  1046,   228,
     228,  1046,   228,   228,  1055,  1052,  1067,  1055,  1052,  1070,
    1055,  1046,  1073,   228,  1049,     4,  1067,  1052,  1049,  1067,
    1055,  1052,  1067,     4,  1055,  1070,   230,     4,  1089,  1046,
       4,  1046,  1067,  1094,   228,  1070,  1067,   228,  1055,     4,
    1055,  1102,  1046,  1104,     4,  1049,     4,     4,  1052,  1046,
    1067,  1055,  1067,  1114,  1089,  1046,   228,  1118,  1055,  1094,
     228,   230,  1123,  1067,  1055,  1126,  1070,  1102,  1046,  1104,
    1067,   228,  1126,   228,   230,  1046,  1111,  1055,  1123,  1114,
       6,  1126,   228,  1114,  1055,  1089,  1046,  1046,  1123,  1067,
    1094,  1126,  1046,  1046,     3,  1055,  1055,  1046,  1102,  1046,
    1104,  1055,  1055,  1046,   227,  1046,  1055,  1111,  1055,  1046,
    1114,  1046,  1055,   227,  1055,  1046,  1046,  1046,  1055,  1123,
    1055,  1046,  1126,  1046,  1055,  1055,  1055,  1046,  1046,  1046,
    1055,  1046,  1055,  1046,  1046,  1046,  1055,  1055,  1055,  1046,
    1055,   227,  1055,  1055,  1055,  1055,   230,     8,  1055,     8,
       4,  1055,     8,     3,     6,     8,     7,   227,     4,     4,
       4,     4,     4,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,   230,     5,     4,     4,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,     4,    77,    78,   227,   227,     4,     7,   170,   227,
     227,   227,   227,   227,    89,    90,    91,   227,   227,     5,
       7,   227,     3,  1123,   227,     4,  1126,     4,   228,  1123,
     105,   106,  1126,   108,   109,   227,   111,   112,   113,   114,
     227,   227,   227,   227,     4,     4,     4,   122,   230,     4,
     228,   126,   228,   227,   227,  1306,     4,   227,   227,   731,
     716,   136,   516,  1314,   523,  1306,   734,  1045,  1306,   815,
    1065,  1306,  1040,  1314,  1061,  1058,  1314,  1328,  1094,  1314,
    1082,  1306,  1075,  1073,  1335,  1306,   577,  1267,   535,  1314,
    1048,  1046,  1057,  1314,  1306,    77,  1049,  1051,  1054,  1306,
    1052,  1306,   567,  1328,   574,   539,  1125,  1314,  1072,  1314,
    1335,  1123,  1306,   546,  1335,  1128,  1314,  1368,  1126,  1306,
    1314,  1070,   197,   198,   788,  1306,  1068,  1314,   557,  1106,
    1089,  1104,  1368,  1102,  1328,  1407,  1435,  1111,  1306,   774,
     733,  1335,   587,  1368,  1115,  1306,  1314,   591,  1413,  1335,
      -1,  1118,   227,  1386,  1405,    -1,  1306,  1306,    -1,    -1,
      -1,    -1,  1306,  1306,    -1,    -1,    -1,  1306,    -1,  1306,
      -1,    -1,    -1,  1306,  1368,  1306,    -1,    -1,    -1,  1306,
    1405,  1306,    -1,    -1,  1435,  1306,  1306,  1306,    -1,    -1,
      -1,  1306,    -1,  1306,    -1,    -1,    -1,  1306,  1306,  1306,
      -1,  1306,    -1,  1306,  1306,  1306,  1306,    -1,    -1,  1306,
    1435,  1405,  1306,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1435
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
       0,     5,     7,     9,   227,   228,   229,   230,   247,   248,
     249,   254,     7,   263,     7,   268,     7,   323,     7,   437,
       7,   517,     7,   534,     7,   551,     7,   466,     7,   472,
       7,   496,     7,   413,     7,   656,     7,   675,   255,   250,
     264,   269,   324,   438,   518,   535,   552,   467,   473,   497,
     414,   657,   676,   247,   256,   257,   227,   252,   253,    10,
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
     407,   421,   431,   451,   452,   453,   456,   464,   490,   524,
     526,   545,   575,   589,   601,   602,   604,   644,   654,   673,
     682,   706,    16,    17,    18,    19,    20,   262,   325,   326,
     327,   329,   330,   331,   332,   524,   526,    97,    99,   107,
     108,   109,   110,   111,   122,   126,   136,   262,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   288,   289,   290,   291,   294,   296,   298,   299,   300,
     303,   304,   306,   308,   314,   316,   439,   440,   441,   443,
     445,   447,   449,   451,   452,   453,   454,   455,   490,   511,
     524,   526,   528,   545,   572,    98,   127,   262,   447,   449,
     490,   519,   520,   521,   523,   524,   526,   100,   101,   102,
     103,   104,   262,   447,   449,   490,   523,   524,   526,   536,
     537,   538,   540,   541,   543,   544,   121,   129,   130,   131,
     132,   133,   134,   135,   262,   490,   524,   526,   553,   554,
     555,   556,   558,   560,   562,   564,   566,   568,   570,   464,
      24,    78,    80,    81,    85,    86,    87,   262,   354,   474,
     475,   476,   477,   478,   479,   480,   482,   484,   486,   487,
     489,   524,   526,    79,    82,    83,    84,   121,   262,   354,
     478,   484,   498,   499,   500,   501,   502,   504,   505,   506,
     507,   508,   509,   524,   526,   138,   139,   262,   415,   416,
     417,   419,   182,   183,   184,   185,   186,   187,   188,   189,
     262,   524,   526,   658,   659,   660,   661,   663,   664,   666,
     667,   668,   671,    13,    14,   677,   678,   679,   681,     6,
       3,     4,     8,     3,   266,     3,     8,   273,   674,   322,
     334,   336,   338,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   312,     4,     4,
       4,     4,     4,   292,   295,   297,     4,     4,     4,     4,
     432,   465,   491,     4,   315,   317,   301,   457,   525,   527,
       4,     4,     4,   387,   399,   393,   379,   576,   546,   408,
     422,   590,     4,   401,   603,   605,   645,   655,   305,   307,
       4,     4,     4,   683,   707,     4,     3,     8,   328,     4,
       4,     4,     4,     3,     8,   512,   529,   442,   444,   446,
       4,     4,   450,   448,   573,     3,     8,   522,     4,     3,
       8,   539,     4,   542,     4,     4,     3,     8,   571,   557,
     559,   561,   563,   565,   567,   569,     8,     3,     8,   481,
     355,     4,   485,   483,   488,     4,     8,     3,   503,     4,
       4,     4,   510,     8,     3,   418,   420,     3,     8,     4,
     662,     4,   665,     4,     4,   669,   672,     3,     8,   680,
       4,     3,     8,   247,   247,   227,     4,     4,     4,     4,
       4,     4,     4,   228,   228,   228,   228,   228,   228,   228,
     228,   230,   229,   229,   229,   228,   228,     4,   228,   228,
     230,   230,   230,     4,     4,     4,   230,   230,   229,   230,
       4,     4,     4,   228,     4,     4,     4,     4,     4,     4,
     230,   230,   230,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   228,     4,     4,     4,     4,     4,     4,     4,
     230,   230,   230,     4,     4,   271,     4,   230,   230,   228,
     228,   326,     4,     4,     4,     4,     4,   228,   230,     4,
       4,     4,   440,     4,   228,   520,     4,   228,     4,   228,
     228,   537,     4,     4,     4,     4,     4,     4,     4,     4,
     555,     4,     4,   228,     4,     4,     4,   230,   476,     4,
     230,   230,   230,     4,   500,     4,     4,   416,   230,     4,
     228,     4,   228,   228,     4,     4,   659,     4,   228,   678,
       4,     7,   227,     7,     7,     7,     7,     5,   227,   193,
     194,   195,   196,   230,   293,   227,   227,     5,     5,     5,
     227,   227,    92,    93,    94,    95,   302,     5,   249,   251,
     227,     5,     5,     5,     7,     5,     5,     5,     7,     7,
       7,     7,     5,     7,     7,   227,   227,     5,     7,     5,
     258,     5,     5,   227,   227,   227,   258,   227,     7,   227,
     227,   227,   258,   258,   258,   258,   227,   227,   227,   227,
     227,   227,   227,   227,   227,   227,   258,   227,   251,   227,
     227,   190,   191,   670,   192,     5,   247,   270,   677,   325,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    42,    43,    44,    45,    46,
      47,   262,   343,   344,   345,   347,   349,   351,   353,   354,
     356,   357,   358,   359,   360,   361,   362,   363,   364,   367,
     368,   369,   370,   372,   374,   376,   343,     7,   339,   340,
     341,     7,   433,   434,   435,     7,   468,   469,   470,     7,
     492,   493,   494,     7,   458,   459,   460,   132,   227,   388,
     389,   390,   391,   256,   133,   135,   390,   394,   395,   396,
     397,   119,   120,   380,   381,   382,   384,     7,   577,   578,
       7,   547,   548,   549,     7,   409,   410,   411,   141,   142,
     143,   144,   145,   146,   423,   424,   425,   426,   427,   428,
     429,   430,    24,   151,   152,   153,   154,   262,   356,   524,
     526,   591,   592,   593,   596,   597,   599,   600,   157,   158,
     159,   262,   402,   403,   404,   405,   406,   524,   526,   162,
     166,   167,   168,   169,   176,   262,   370,   372,   374,   524,
     526,   610,   611,   612,   615,   617,   619,   620,   621,     7,
     606,   607,   608,   178,   179,   180,   227,   524,   526,   646,
     647,   648,   649,   651,   652,   658,     7,   684,   685,   212,
     262,   708,   709,   710,   259,     7,   513,   514,   515,     7,
     530,   531,   532,   556,   574,   339,     8,     8,     8,   346,
     348,   350,   352,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   365,     4,     4,   371,   373,   375,   377,
       3,     8,     8,   342,     6,     3,   436,     6,     3,   471,
       6,     3,   495,     6,     3,   461,     6,     3,     3,     6,
       6,     3,     6,   383,   385,     3,     8,   579,     3,     6,
     550,     6,     3,   412,     6,     3,     4,     4,     4,     4,
       4,     4,     3,     8,   594,   598,     4,     4,     4,     3,
       8,     4,     4,     4,     3,     8,   613,   616,   618,     4,
     622,     4,     3,     8,   609,     6,     3,     4,   650,     4,
     653,     3,     8,     8,   686,     3,     6,     4,     3,     8,
     227,   260,   261,   516,     6,     3,   533,     6,     3,     8,
       6,     4,     4,     4,     4,   228,   230,   228,   230,   228,
     228,   228,   228,   228,   228,     4,   230,   228,     4,     4,
       4,     4,   344,   343,   341,   439,   435,   474,   470,   498,
     494,   262,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   288,   289,   290,   291,   294,
     296,   298,   299,   300,   303,   304,   306,   308,   314,   316,
     354,   431,   443,   445,   447,   449,   451,   452,   453,   455,
     462,   463,   490,   524,   526,   572,   460,   389,   395,     4,
       4,   381,   123,   124,   125,   262,   274,   275,   276,   277,
     278,   279,   354,   490,   524,   526,   580,   581,   582,   583,
     584,   586,   588,   578,   553,   549,   415,   411,   228,   228,
     228,   228,   228,   228,   424,     4,     4,   228,   228,   228,
     592,   230,   228,   228,   403,     4,     4,     4,   228,     4,
     230,   611,   610,   608,   230,     4,   228,     4,   647,   203,
     205,   206,   262,   354,   524,   526,   687,   688,   689,   690,
     692,   685,   230,   709,     6,     3,   519,   515,   536,   532,
     227,   227,   227,   227,    39,    40,    41,   366,   227,   227,
     227,   227,     8,     8,     8,     8,     3,     8,   227,   227,
     585,   587,     4,     8,     3,     8,     8,   148,   149,   150,
     595,   227,   163,   164,   165,   614,   227,   227,     7,     8,
     227,   247,   693,     4,   691,     3,     8,   227,     8,     8,
     463,     4,     4,   230,   582,    24,   171,   172,   173,   262,
     524,   526,   623,   624,   625,   628,   630,   632,     4,   228,
       4,   688,   227,   227,   626,   629,   631,   633,     3,     8,
       5,   227,     4,     4,     4,     4,   624,     7,   694,   695,
     170,   627,   227,   227,     5,   696,     3,     6,     7,   634,
     635,   636,   204,   207,   208,   209,   210,   697,   698,   699,
     701,   702,   703,   704,   695,   637,     6,     3,   700,     4,
       4,     4,   705,     3,     8,   174,   175,   262,   347,   349,
     524,   526,   638,   639,   640,   642,   636,     4,   230,   228,
     228,     4,   698,   641,   643,     3,     8,   227,   227,     4,
       4,   639,   227,   227
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
     500,   500,   500,   500,   501,   503,   502,   504,   505,   506,
     507,   508,   510,   509,   512,   511,   513,   513,   514,   514,
     514,   516,   515,   518,   517,   519,   519,   519,   520,   520,
     520,   520,   520,   520,   520,   520,   522,   521,   523,   525,
     524,   527,   526,   529,   528,   530,   530,   531,   531,   531,
     533,   532,   535,   534,   536,   536,   536,   537,   537,   537,
     537,   537,   537,   537,   537,   537,   537,   537,   537,   539,
     538,   540,   542,   541,   543,   544,   546,   545,   547,   547,
     548,   548,   548,   550,   549,   552,   551,   553,   553,   554,
     554,   554,   555,   555,   555,   555,   555,   555,   555,   555,
     555,   555,   555,   555,   557,   556,   559,   558,   561,   560,
     563,   562,   565,   564,   567,   566,   569,   568,   571,   570,
     573,   572,   574,   576,   575,   577,   577,   577,   579,   578,
     580,   580,   581,   581,   581,   582,   582,   582,   582,   582,
     582,   582,   582,   582,   582,   582,   582,   582,   582,   583,
     585,   584,   587,   586,   588,   590,   589,   591,   591,   591,
     592,   592,   592,   592,   592,   592,   592,   592,   592,   594,
     593,   595,   595,   595,   596,   598,   597,   599,   600,   601,
     603,   602,   605,   604,   606,   606,   607,   607,   607,   609,
     608,   610,   610,   610,   611,   611,   611,   611,   611,   611,
     611,   611,   611,   611,   611,   611,   613,   612,   614,   614,
     614,   616,   615,   618,   617,   619,   620,   622,   621,   623,
     623,   623,   624,   624,   624,   624,   624,   624,   624,   626,
     625,   627,   629,   628,   631,   630,   633,   632,   634,   634,
     635,   635,   635,   637,   636,   638,   638,   638,   639,   639,
     639,   639,   639,   639,   639,   641,   640,   643,   642,   645,
     644,   646,   646,   646,   647,   647,   647,   647,   647,   647,
     648,   650,   649,   651,   653,   652,   655,   654,   657,   656,
     658,   658,   658,   659,   659,   659,   659,   659,   659,   659,
     659,   659,   659,   659,   660,   662,   661,   663,   665,   664,
     666,   667,   669,   668,   670,   670,   672,   671,   674,   673,
     676,   675,   677,   677,   677,   678,   678,   680,   679,   681,
     683,   682,   684,   684,   684,   686,   685,   687,   687,   687,
     688,   688,   688,   688,   688,   688,   688,   689,   691,   690,
     693,   692,   694,   694,   694,   696,   695,   697,   697,   697,
     698,   698,   698,   698,   698,   700,   699,   701,   702,   703,
     705,   704,   707,   706,   708,   708,   708,   709,   709,   710
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
       1,     1,     1,     1,     1,     0,     4,     1,     1,     3,
       3,     3,     0,     4,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     4,     3,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     0,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     1,     0,     6,     1,     3,     2,     0,     4,
       0,     1,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     3,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     3,     0,     4,     3,     3,     3,
       0,     6,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     0,     4,     0,     4,     3,     3,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     0,     4,     0,     4,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     3,     0,     4,     0,     6,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     3,     0,     4,
       3,     3,     0,     4,     1,     1,     0,     4,     0,     6,
       0,     4,     1,     3,     2,     1,     1,     0,     6,     3,
       0,     6,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     6,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     0,     4,     3,     3,     3,
       0,     4,     0,     6,     1,     3,     2,     1,     1,     3
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
  "option_data_always_send", "option_data_never_send",
  "option_data_client_classes", "$@83", "pools_list", "$@84",
  "pools_list_content", "not_empty_pools_list", "pool_list_entry", "$@85",
  "sub_pool6", "$@86", "pool_params", "pool_param", "pool_entry", "$@87",
  "pool_id", "user_context", "$@88", "comment", "$@89", "pd_pools_list",
  "$@90", "pd_pools_list_content", "not_empty_pd_pools_list",
  "pd_pool_entry", "$@91", "sub_pd_pool", "$@92", "pd_pool_params",
  "pd_pool_param", "pd_prefix", "$@93", "pd_prefix_len", "excluded_prefix",
  "$@94", "excluded_prefix_len", "pd_delegated_len", "reservations",
  "$@95", "reservations_list", "not_empty_reservations_list",
  "reservation", "$@96", "sub_reservation", "$@97", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@98", "prefixes", "$@99", "excluded_prefixes", "$@100", "duid",
  "$@101", "hw_address", "$@102", "hostname", "$@103", "flex_id_value",
  "$@104", "reservation_client_classes", "$@105", "relay", "$@106",
  "relay_map", "client_classes", "$@107", "client_classes_list",
  "client_class_entry", "$@108", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@109",
  "client_class_template_test", "$@110", "only_if_required", "server_id",
  "$@111", "server_id_params", "server_id_param", "server_id_type",
  "$@112", "duid_type", "htype", "identifier", "$@113", "time",
  "enterprise_id", "dhcp4o6_port", "control_socket", "$@114",
  "control_sockets", "$@115", "control_socket_list",
  "not_empty_control_socket_list", "control_socket_entry", "$@116",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@117", "control_socket_type_value", "control_socket_name", "$@118",
  "control_socket_address", "$@119", "control_socket_port",
  "cert_required", "authentication", "$@120", "auth_params", "auth_param",
  "auth_type", "$@121", "auth_type_value", "realm", "$@122", "directory",
  "$@123", "clients", "$@124", "clients_list", "not_empty_clients_list",
  "basic_auth", "$@125", "clients_params", "clients_param", "user_file",
  "$@126", "password_file", "$@127", "dhcp_queue_control", "$@128",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@129", "capacity", "arbitrary_map_entry", "$@130",
  "dhcp_ddns", "$@131", "sub_dhcp_ddns", "$@132", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@133", "server_port",
  "sender_ip", "$@134", "sender_port", "max_queue_size", "ncr_protocol",
  "$@135", "ncr_protocol_value", "ncr_format", "$@136", "config_control",
  "$@137", "sub_config_control", "$@138", "config_control_params",
  "config_control_param", "config_databases", "$@139",
  "config_fetch_wait_time", "loggers", "$@140", "loggers_entries",
  "logger_entry", "$@141", "logger_params", "logger_param", "debuglevel",
  "severity", "$@142", "output_options_list", "$@143",
  "output_options_list_content", "output_entry", "$@144",
  "output_params_list", "output_params", "output", "$@145", "flush",
  "maxsize", "maxver", "pattern", "$@146", "compatibility", "$@147",
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
    2037,  2038,  2039,  2040,  2043,  2045,  2045,  2054,  2056,  2058,
    2064,  2070,  2076,  2076,  2090,  2090,  2103,  2104,  2107,  2108,
    2109,  2114,  2114,  2124,  2124,  2134,  2135,  2136,  2141,  2142,
    2143,  2144,  2145,  2146,  2147,  2148,  2151,  2151,  2160,  2166,
    2166,  2191,  2191,  2221,  2221,  2234,  2235,  2238,  2239,  2240,
    2245,  2245,  2257,  2257,  2269,  2270,  2271,  2276,  2277,  2278,
    2279,  2280,  2281,  2282,  2283,  2284,  2285,  2286,  2287,  2290,
    2290,  2299,  2305,  2305,  2314,  2320,  2329,  2329,  2340,  2341,
    2344,  2345,  2346,  2351,  2351,  2360,  2360,  2369,  2370,  2373,
    2374,  2375,  2381,  2382,  2383,  2384,  2385,  2386,  2387,  2388,
    2389,  2390,  2391,  2392,  2395,  2395,  2406,  2406,  2417,  2417,
    2428,  2428,  2437,  2437,  2446,  2446,  2455,  2455,  2464,  2464,
    2478,  2478,  2489,  2495,  2495,  2506,  2507,  2508,  2513,  2513,
    2523,  2524,  2527,  2528,  2529,  2534,  2535,  2536,  2537,  2538,
    2539,  2540,  2541,  2542,  2543,  2544,  2545,  2546,  2547,  2550,
    2552,  2552,  2561,  2561,  2570,  2579,  2579,  2592,  2593,  2594,
    2599,  2600,  2601,  2602,  2603,  2604,  2605,  2606,  2607,  2610,
    2610,  2618,  2619,  2620,  2623,  2629,  2629,  2638,  2644,  2652,
    2660,  2660,  2672,  2672,  2684,  2685,  2688,  2689,  2690,  2695,
    2695,  2703,  2704,  2705,  2710,  2711,  2712,  2713,  2714,  2715,
    2716,  2717,  2718,  2719,  2720,  2721,  2724,  2724,  2733,  2734,
    2735,  2738,  2738,  2748,  2748,  2758,  2764,  2772,  2772,  2785,
    2786,  2787,  2792,  2793,  2794,  2795,  2796,  2797,  2798,  2801,
    2801,  2809,  2812,  2812,  2821,  2821,  2830,  2830,  2841,  2842,
    2845,  2846,  2847,  2852,  2852,  2860,  2861,  2862,  2867,  2868,
    2869,  2870,  2871,  2872,  2873,  2876,  2876,  2885,  2885,  2896,
    2896,  2909,  2910,  2911,  2916,  2917,  2918,  2919,  2920,  2921,
    2924,  2930,  2930,  2939,  2945,  2945,  2955,  2955,  2968,  2968,
    2978,  2979,  2980,  2985,  2986,  2987,  2988,  2989,  2990,  2991,
    2992,  2993,  2994,  2995,  2998,  3004,  3004,  3013,  3019,  3019,
    3028,  3034,  3040,  3040,  3049,  3050,  3053,  3053,  3064,  3064,
    3076,  3076,  3086,  3087,  3088,  3094,  3095,  3098,  3098,  3109,
    3117,  3117,  3130,  3131,  3132,  3138,  3138,  3146,  3147,  3148,
    3153,  3154,  3155,  3156,  3157,  3158,  3159,  3162,  3168,  3168,
    3177,  3177,  3188,  3189,  3190,  3195,  3195,  3203,  3204,  3205,
    3210,  3211,  3212,  3213,  3214,  3217,  3217,  3226,  3232,  3238,
    3244,  3244,  3253,  3253,  3264,  3265,  3266,  3271,  3272,  3275
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
#line 6819 "dhcp6_parser.cc"

#line 3281 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
