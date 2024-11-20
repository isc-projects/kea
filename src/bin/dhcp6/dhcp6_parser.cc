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
#line 323 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 413 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 323 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 419 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 323 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 425 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 323 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 431 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 323 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 437 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 323 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 443 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 323 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 449 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 323 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 455 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 323 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 461 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 323 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 467 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
#line 323 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 473 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 323 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 479 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 323 "dhcp6_parser.yy"
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
#line 332 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 766 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 333 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 772 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 334 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 778 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 335 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 784 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 336 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 790 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 337 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 796 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 338 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 802 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 339 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 808 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 340 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 814 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 341 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 820 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 342 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 826 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 343 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 832 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 344 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 838 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 345 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 844 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 353 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 850 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 354 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 856 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 355 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 862 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 356 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 868 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 357 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 874 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 358 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 880 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 359 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 886 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 362 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 895 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 367 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 906 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 372 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 916 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 378 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 922 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 385 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 932 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 390 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 943 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 396 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 951 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 401 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 960 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 404 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 968 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 412 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 977 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 416 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 986 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 420 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 994 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 426 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 1002 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 428 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1011 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 437 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1020 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 441 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1029 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 445 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1037 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 455 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1048 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 464 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1059 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 469 "dhcp6_parser.yy"
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
#line 479 "dhcp6_parser.yy"
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
#line 488 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1097 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 496 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1105 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 502 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1115 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 506 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1124 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 513 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1132 "dhcp6_parser.cc"
    break;

  case 144: // $@21: %empty
#line 594 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1141 "dhcp6_parser.cc"
    break;

  case 145: // data_directory: "data-directory" $@21 ":" "constant string"
#line 597 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1151 "dhcp6_parser.cc"
    break;

  case 146: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 603 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1161 "dhcp6_parser.cc"
    break;

  case 147: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 609 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1171 "dhcp6_parser.cc"
    break;

  case 148: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 615 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1181 "dhcp6_parser.cc"
    break;

  case 149: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 621 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1191 "dhcp6_parser.cc"
    break;

  case 150: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 627 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1201 "dhcp6_parser.cc"
    break;

  case 151: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 633 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1211 "dhcp6_parser.cc"
    break;

  case 152: // renew_timer: "renew-timer" ":" "integer"
#line 639 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1221 "dhcp6_parser.cc"
    break;

  case 153: // rebind_timer: "rebind-timer" ":" "integer"
#line 645 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1231 "dhcp6_parser.cc"
    break;

  case 154: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 651 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1241 "dhcp6_parser.cc"
    break;

  case 155: // t1_percent: "t1-percent" ":" "floating point"
#line 657 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1251 "dhcp6_parser.cc"
    break;

  case 156: // t2_percent: "t2-percent" ":" "floating point"
#line 663 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1261 "dhcp6_parser.cc"
    break;

  case 157: // cache_threshold: "cache-threshold" ":" "floating point"
#line 669 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1271 "dhcp6_parser.cc"
    break;

  case 158: // cache_max_age: "cache-max-age" ":" "integer"
#line 675 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1281 "dhcp6_parser.cc"
    break;

  case 159: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 681 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1291 "dhcp6_parser.cc"
    break;

  case 160: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 687 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1301 "dhcp6_parser.cc"
    break;

  case 161: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 693 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1311 "dhcp6_parser.cc"
    break;

  case 162: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 699 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1321 "dhcp6_parser.cc"
    break;

  case 163: // $@22: %empty
#line 705 "dhcp6_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1330 "dhcp6_parser.cc"
    break;

  case 164: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 708 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1339 "dhcp6_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "when-present"
#line 714 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1347 "dhcp6_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "never"
#line 717 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1355 "dhcp6_parser.cc"
    break;

  case 167: // ddns_replace_client_name_value: "always"
#line 720 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1363 "dhcp6_parser.cc"
    break;

  case 168: // ddns_replace_client_name_value: "when-not-present"
#line 723 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1371 "dhcp6_parser.cc"
    break;

  case 169: // ddns_replace_client_name_value: "boolean"
#line 726 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1380 "dhcp6_parser.cc"
    break;

  case 170: // $@23: %empty
#line 732 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1389 "dhcp6_parser.cc"
    break;

  case 171: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 735 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1399 "dhcp6_parser.cc"
    break;

  case 172: // $@24: %empty
#line 741 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1408 "dhcp6_parser.cc"
    break;

  case 173: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 744 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1418 "dhcp6_parser.cc"
    break;

  case 174: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 750 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1428 "dhcp6_parser.cc"
    break;

  case 175: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 759 "dhcp6_parser.yy"
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

  case 176: // $@25: %empty
#line 769 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1451 "dhcp6_parser.cc"
    break;

  case 177: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 772 "dhcp6_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 778 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1468 "dhcp6_parser.cc"
    break;

  case 179: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 781 "dhcp6_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1476 "dhcp6_parser.cc"
    break;

  case 180: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 784 "dhcp6_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1484 "dhcp6_parser.cc"
    break;

  case 181: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 787 "dhcp6_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1492 "dhcp6_parser.cc"
    break;

  case 182: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 792 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1502 "dhcp6_parser.cc"
    break;

  case 183: // ddns_ttl: "ddns-ttl" ":" "integer"
#line 798 "dhcp6_parser.yy"
                                 {
    ctx.unique("ddns-ttl", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl", ttl);
}
#line 1512 "dhcp6_parser.cc"
    break;

  case 184: // ddns_ttl_min: "ddns-ttl-min" ":" "integer"
#line 804 "dhcp6_parser.yy"
                                         {
    ctx.unique("ddns-ttl-min", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-min", ttl);
}
#line 1522 "dhcp6_parser.cc"
    break;

  case 185: // ddns_ttl_max: "ddns-ttl-mix" ":" "integer"
#line 810 "dhcp6_parser.yy"
                                         {
    ctx.unique("ddns-ttl-max", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-max", ttl);
}
#line 1532 "dhcp6_parser.cc"
    break;

  case 186: // $@26: %empty
#line 816 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1541 "dhcp6_parser.cc"
    break;

  case 187: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 819 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1551 "dhcp6_parser.cc"
    break;

  case 188: // $@27: %empty
#line 825 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1560 "dhcp6_parser.cc"
    break;

  case 189: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 828 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1570 "dhcp6_parser.cc"
    break;

  case 190: // store_extended_info: "store-extended-info" ":" "boolean"
#line 834 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1580 "dhcp6_parser.cc"
    break;

  case 191: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 840 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1590 "dhcp6_parser.cc"
    break;

  case 192: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 846 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1600 "dhcp6_parser.cc"
    break;

  case 193: // $@28: %empty
#line 852 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1609 "dhcp6_parser.cc"
    break;

  case 194: // server_tag: "server-tag" $@28 ":" "constant string"
#line 855 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1619 "dhcp6_parser.cc"
    break;

  case 195: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 861 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1629 "dhcp6_parser.cc"
    break;

  case 196: // $@29: %empty
#line 867 "dhcp6_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1638 "dhcp6_parser.cc"
    break;

  case 197: // allocator: "allocator" $@29 ":" "constant string"
#line 870 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1648 "dhcp6_parser.cc"
    break;

  case 198: // $@30: %empty
#line 876 "dhcp6_parser.yy"
                           {
    ctx.unique("pd-allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1657 "dhcp6_parser.cc"
    break;

  case 199: // pd_allocator: "pd-allocator" $@30 ":" "constant string"
#line 879 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-allocator", al);
    ctx.leave();
}
#line 1667 "dhcp6_parser.cc"
    break;

  case 200: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 885 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1677 "dhcp6_parser.cc"
    break;

  case 201: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 891 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1687 "dhcp6_parser.cc"
    break;

  case 202: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 897 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1697 "dhcp6_parser.cc"
    break;

  case 203: // $@31: %empty
#line 903 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1709 "dhcp6_parser.cc"
    break;

  case 204: // interfaces_config: "interfaces-config" $@31 ":" "{" interfaces_config_params "}"
#line 909 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1719 "dhcp6_parser.cc"
    break;

  case 205: // $@32: %empty
#line 915 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1729 "dhcp6_parser.cc"
    break;

  case 206: // sub_interfaces6: "{" $@32 interfaces_config_params "}"
#line 919 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1738 "dhcp6_parser.cc"
    break;

  case 209: // interfaces_config_params: interfaces_config_params ","
#line 926 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1746 "dhcp6_parser.cc"
    break;

  case 218: // $@33: %empty
#line 941 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1758 "dhcp6_parser.cc"
    break;

  case 219: // interfaces_list: "interfaces" $@33 ":" list_strings
#line 947 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1767 "dhcp6_parser.cc"
    break;

  case 220: // re_detect: "re-detect" ":" "boolean"
#line 952 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1777 "dhcp6_parser.cc"
    break;

  case 221: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 958 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1787 "dhcp6_parser.cc"
    break;

  case 222: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 964 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1797 "dhcp6_parser.cc"
    break;

  case 223: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 970 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1807 "dhcp6_parser.cc"
    break;

  case 224: // $@34: %empty
#line 976 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1819 "dhcp6_parser.cc"
    break;

  case 225: // lease_database: "lease-database" $@34 ":" "{" database_map_params "}"
#line 982 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1830 "dhcp6_parser.cc"
    break;

  case 226: // $@35: %empty
#line 989 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1842 "dhcp6_parser.cc"
    break;

  case 227: // hosts_database: "hosts-database" $@35 ":" "{" database_map_params "}"
#line 995 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1853 "dhcp6_parser.cc"
    break;

  case 228: // $@36: %empty
#line 1002 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1865 "dhcp6_parser.cc"
    break;

  case 229: // hosts_databases: "hosts-databases" $@36 ":" "[" database_list "]"
#line 1008 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1874 "dhcp6_parser.cc"
    break;

  case 234: // not_empty_database_list: not_empty_database_list ","
#line 1019 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1882 "dhcp6_parser.cc"
    break;

  case 235: // $@37: %empty
#line 1024 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1892 "dhcp6_parser.cc"
    break;

  case 236: // database: "{" $@37 database_map_params "}"
#line 1028 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1902 "dhcp6_parser.cc"
    break;

  case 239: // database_map_params: database_map_params ","
#line 1036 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1910 "dhcp6_parser.cc"
    break;

  case 263: // $@38: %empty
#line 1066 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1919 "dhcp6_parser.cc"
    break;

  case 264: // database_type: "type" $@38 ":" "constant string"
#line 1069 "dhcp6_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 1929 "dhcp6_parser.cc"
    break;

  case 265: // $@39: %empty
#line 1075 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1938 "dhcp6_parser.cc"
    break;

  case 266: // user: "user" $@39 ":" "constant string"
#line 1078 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1948 "dhcp6_parser.cc"
    break;

  case 267: // $@40: %empty
#line 1084 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1957 "dhcp6_parser.cc"
    break;

  case 268: // password: "password" $@40 ":" "constant string"
#line 1087 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1967 "dhcp6_parser.cc"
    break;

  case 269: // $@41: %empty
#line 1093 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1976 "dhcp6_parser.cc"
    break;

  case 270: // host: "host" $@41 ":" "constant string"
#line 1096 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1986 "dhcp6_parser.cc"
    break;

  case 271: // port: "port" ":" "integer"
#line 1102 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1996 "dhcp6_parser.cc"
    break;

  case 272: // $@42: %empty
#line 1108 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2005 "dhcp6_parser.cc"
    break;

  case 273: // name: "name" $@42 ":" "constant string"
#line 1111 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2015 "dhcp6_parser.cc"
    break;

  case 274: // persist: "persist" ":" "boolean"
#line 1117 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2025 "dhcp6_parser.cc"
    break;

  case 275: // lfc_interval: "lfc-interval" ":" "integer"
#line 1123 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2035 "dhcp6_parser.cc"
    break;

  case 276: // readonly: "readonly" ":" "boolean"
#line 1129 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2045 "dhcp6_parser.cc"
    break;

  case 277: // connect_timeout: "connect-timeout" ":" "integer"
#line 1135 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2055 "dhcp6_parser.cc"
    break;

  case 278: // read_timeout: "read-timeout" ":" "integer"
#line 1141 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2065 "dhcp6_parser.cc"
    break;

  case 279: // write_timeout: "write-timeout" ":" "integer"
#line 1147 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2075 "dhcp6_parser.cc"
    break;

  case 280: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1153 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2085 "dhcp6_parser.cc"
    break;

  case 281: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1159 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2095 "dhcp6_parser.cc"
    break;

  case 282: // $@43: %empty
#line 1165 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2104 "dhcp6_parser.cc"
    break;

  case 283: // on_fail: "on-fail" $@43 ":" on_fail_mode
#line 1168 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2113 "dhcp6_parser.cc"
    break;

  case 284: // on_fail_mode: "stop-retry-exit"
#line 1173 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2119 "dhcp6_parser.cc"
    break;

  case 285: // on_fail_mode: "serve-retry-exit"
#line 1174 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2125 "dhcp6_parser.cc"
    break;

  case 286: // on_fail_mode: "serve-retry-continue"
#line 1175 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2131 "dhcp6_parser.cc"
    break;

  case 287: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1178 "dhcp6_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2141 "dhcp6_parser.cc"
    break;

  case 288: // max_row_errors: "max-row-errors" ":" "integer"
#line 1184 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2151 "dhcp6_parser.cc"
    break;

  case 289: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1190 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2161 "dhcp6_parser.cc"
    break;

  case 290: // $@44: %empty
#line 1196 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2170 "dhcp6_parser.cc"
    break;

  case 291: // trust_anchor: "trust-anchor" $@44 ":" "constant string"
#line 1199 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2180 "dhcp6_parser.cc"
    break;

  case 292: // $@45: %empty
#line 1205 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2189 "dhcp6_parser.cc"
    break;

  case 293: // cert_file: "cert-file" $@45 ":" "constant string"
#line 1208 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2199 "dhcp6_parser.cc"
    break;

  case 294: // $@46: %empty
#line 1214 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2208 "dhcp6_parser.cc"
    break;

  case 295: // key_file: "key-file" $@46 ":" "constant string"
#line 1217 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2218 "dhcp6_parser.cc"
    break;

  case 296: // $@47: %empty
#line 1223 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2227 "dhcp6_parser.cc"
    break;

  case 297: // cipher_list: "cipher-list" $@47 ":" "constant string"
#line 1226 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2237 "dhcp6_parser.cc"
    break;

  case 298: // $@48: %empty
#line 1232 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2249 "dhcp6_parser.cc"
    break;

  case 299: // sanity_checks: "sanity-checks" $@48 ":" "{" sanity_checks_params "}"
#line 1238 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2258 "dhcp6_parser.cc"
    break;

  case 302: // sanity_checks_params: sanity_checks_params ","
#line 1245 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2266 "dhcp6_parser.cc"
    break;

  case 305: // $@49: %empty
#line 1254 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2275 "dhcp6_parser.cc"
    break;

  case 306: // lease_checks: "lease-checks" $@49 ":" "constant string"
#line 1257 "dhcp6_parser.yy"
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
#line 2295 "dhcp6_parser.cc"
    break;

  case 307: // $@50: %empty
#line 1273 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2304 "dhcp6_parser.cc"
    break;

  case 308: // extended_info_checks: "extended-info-checks" $@50 ":" "constant string"
#line 1276 "dhcp6_parser.yy"
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
#line 2323 "dhcp6_parser.cc"
    break;

  case 309: // $@51: %empty
#line 1291 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2335 "dhcp6_parser.cc"
    break;

  case 310: // mac_sources: "mac-sources" $@51 ":" "[" mac_sources_list "]"
#line 1297 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2344 "dhcp6_parser.cc"
    break;

  case 313: // mac_sources_list: mac_sources_list ","
#line 1304 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2352 "dhcp6_parser.cc"
    break;

  case 316: // duid_id: "duid"
#line 1313 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2361 "dhcp6_parser.cc"
    break;

  case 317: // string_id: "constant string"
#line 1318 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2370 "dhcp6_parser.cc"
    break;

  case 318: // $@52: %empty
#line 1323 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2382 "dhcp6_parser.cc"
    break;

  case 319: // host_reservation_identifiers: "host-reservation-identifiers" $@52 ":" "[" host_reservation_identifiers_list "]"
#line 1329 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2391 "dhcp6_parser.cc"
    break;

  case 322: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1336 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2399 "dhcp6_parser.cc"
    break;

  case 326: // hw_address_id: "hw-address"
#line 1346 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2408 "dhcp6_parser.cc"
    break;

  case 327: // flex_id: "flex-id"
#line 1351 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2417 "dhcp6_parser.cc"
    break;

  case 328: // $@53: %empty
#line 1358 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2429 "dhcp6_parser.cc"
    break;

  case 329: // relay_supplied_options: "relay-supplied-options" $@53 ":" "[" list_content "]"
#line 1364 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2438 "dhcp6_parser.cc"
    break;

  case 330: // $@54: %empty
#line 1371 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2450 "dhcp6_parser.cc"
    break;

  case 331: // dhcp_multi_threading: "multi-threading" $@54 ":" "{" multi_threading_params "}"
#line 1377 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2461 "dhcp6_parser.cc"
    break;

  case 334: // multi_threading_params: multi_threading_params ","
#line 1386 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2469 "dhcp6_parser.cc"
    break;

  case 341: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1399 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2479 "dhcp6_parser.cc"
    break;

  case 342: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1405 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2489 "dhcp6_parser.cc"
    break;

  case 343: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1411 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2499 "dhcp6_parser.cc"
    break;

  case 344: // $@55: %empty
#line 1417 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2511 "dhcp6_parser.cc"
    break;

  case 345: // hooks_libraries: "hooks-libraries" $@55 ":" "[" hooks_libraries_list "]"
#line 1423 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2520 "dhcp6_parser.cc"
    break;

  case 350: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1434 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2528 "dhcp6_parser.cc"
    break;

  case 351: // $@56: %empty
#line 1439 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2538 "dhcp6_parser.cc"
    break;

  case 352: // hooks_library: "{" $@56 hooks_params "}"
#line 1443 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2548 "dhcp6_parser.cc"
    break;

  case 353: // $@57: %empty
#line 1449 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2558 "dhcp6_parser.cc"
    break;

  case 354: // sub_hooks_library: "{" $@57 hooks_params "}"
#line 1453 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2568 "dhcp6_parser.cc"
    break;

  case 357: // hooks_params: hooks_params ","
#line 1461 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2576 "dhcp6_parser.cc"
    break;

  case 361: // $@58: %empty
#line 1471 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2585 "dhcp6_parser.cc"
    break;

  case 362: // library: "library" $@58 ":" "constant string"
#line 1474 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2595 "dhcp6_parser.cc"
    break;

  case 363: // $@59: %empty
#line 1480 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2604 "dhcp6_parser.cc"
    break;

  case 364: // parameters: "parameters" $@59 ":" map_value
#line 1483 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2613 "dhcp6_parser.cc"
    break;

  case 365: // $@60: %empty
#line 1489 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2625 "dhcp6_parser.cc"
    break;

  case 366: // expired_leases_processing: "expired-leases-processing" $@60 ":" "{" expired_leases_params "}"
#line 1495 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2635 "dhcp6_parser.cc"
    break;

  case 369: // expired_leases_params: expired_leases_params ","
#line 1503 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2643 "dhcp6_parser.cc"
    break;

  case 376: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1516 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2653 "dhcp6_parser.cc"
    break;

  case 377: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1522 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2663 "dhcp6_parser.cc"
    break;

  case 378: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1528 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2673 "dhcp6_parser.cc"
    break;

  case 379: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1534 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2683 "dhcp6_parser.cc"
    break;

  case 380: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1540 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2693 "dhcp6_parser.cc"
    break;

  case 381: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1546 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2703 "dhcp6_parser.cc"
    break;

  case 382: // $@61: %empty
#line 1555 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2715 "dhcp6_parser.cc"
    break;

  case 383: // subnet6_list: "subnet6" $@61 ":" "[" subnet6_list_content "]"
#line 1561 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2724 "dhcp6_parser.cc"
    break;

  case 388: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1575 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2732 "dhcp6_parser.cc"
    break;

  case 389: // $@62: %empty
#line 1584 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2742 "dhcp6_parser.cc"
    break;

  case 390: // subnet6: "{" $@62 subnet6_params "}"
#line 1588 "dhcp6_parser.yy"
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
#line 2768 "dhcp6_parser.cc"
    break;

  case 391: // $@63: %empty
#line 1610 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2778 "dhcp6_parser.cc"
    break;

  case 392: // sub_subnet6: "{" $@63 subnet6_params "}"
#line 1614 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2788 "dhcp6_parser.cc"
    break;

  case 395: // subnet6_params: subnet6_params ","
#line 1623 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2796 "dhcp6_parser.cc"
    break;

  case 447: // $@64: %empty
#line 1682 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2805 "dhcp6_parser.cc"
    break;

  case 448: // subnet: "subnet" $@64 ":" "constant string"
#line 1685 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2815 "dhcp6_parser.cc"
    break;

  case 449: // $@65: %empty
#line 1691 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2824 "dhcp6_parser.cc"
    break;

  case 450: // interface: "interface" $@65 ":" "constant string"
#line 1694 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2834 "dhcp6_parser.cc"
    break;

  case 451: // $@66: %empty
#line 1700 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2843 "dhcp6_parser.cc"
    break;

  case 452: // interface_id: "interface-id" $@66 ":" "constant string"
#line 1703 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2853 "dhcp6_parser.cc"
    break;

  case 453: // $@67: %empty
#line 1709 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2862 "dhcp6_parser.cc"
    break;

  case 454: // client_class: "client-class" $@67 ":" "constant string"
#line 1712 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2872 "dhcp6_parser.cc"
    break;

  case 455: // $@68: %empty
#line 1719 "dhcp6_parser.yy"
                                       {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2884 "dhcp6_parser.cc"
    break;

  case 456: // network_client_classes: "client-classes" $@68 ":" list_strings
#line 1725 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2893 "dhcp6_parser.cc"
    break;

  case 457: // $@69: %empty
#line 1731 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2905 "dhcp6_parser.cc"
    break;

  case 458: // require_client_classes: "require-client-classes" $@69 ":" list_strings
#line 1737 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2914 "dhcp6_parser.cc"
    break;

  case 459: // $@70: %empty
#line 1742 "dhcp6_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2926 "dhcp6_parser.cc"
    break;

  case 460: // evaluate_additional_classes: "evaluate-additional-classes" $@70 ":" list_strings
#line 1748 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2935 "dhcp6_parser.cc"
    break;

  case 461: // reservations_global: "reservations-global" ":" "boolean"
#line 1753 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2945 "dhcp6_parser.cc"
    break;

  case 462: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1759 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2955 "dhcp6_parser.cc"
    break;

  case 463: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1765 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2965 "dhcp6_parser.cc"
    break;

  case 464: // id: "id" ":" "integer"
#line 1771 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2975 "dhcp6_parser.cc"
    break;

  case 465: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1777 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2985 "dhcp6_parser.cc"
    break;

  case 466: // $@71: %empty
#line 1785 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2997 "dhcp6_parser.cc"
    break;

  case 467: // shared_networks: "shared-networks" $@71 ":" "[" shared_networks_content "]"
#line 1791 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3006 "dhcp6_parser.cc"
    break;

  case 472: // shared_networks_list: shared_networks_list ","
#line 1804 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3014 "dhcp6_parser.cc"
    break;

  case 473: // $@72: %empty
#line 1809 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3024 "dhcp6_parser.cc"
    break;

  case 474: // shared_network: "{" $@72 shared_network_params "}"
#line 1813 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3032 "dhcp6_parser.cc"
    break;

  case 477: // shared_network_params: shared_network_params ","
#line 1819 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3040 "dhcp6_parser.cc"
    break;

  case 526: // $@73: %empty
#line 1878 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3052 "dhcp6_parser.cc"
    break;

  case 527: // option_def_list: "option-def" $@73 ":" "[" option_def_list_content "]"
#line 1884 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3061 "dhcp6_parser.cc"
    break;

  case 528: // $@74: %empty
#line 1892 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3070 "dhcp6_parser.cc"
    break;

  case 529: // sub_option_def_list: "{" $@74 option_def_list "}"
#line 1895 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 3078 "dhcp6_parser.cc"
    break;

  case 534: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1907 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3086 "dhcp6_parser.cc"
    break;

  case 535: // $@75: %empty
#line 1914 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3096 "dhcp6_parser.cc"
    break;

  case 536: // option_def_entry: "{" $@75 option_def_params "}"
#line 1918 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3108 "dhcp6_parser.cc"
    break;

  case 537: // $@76: %empty
#line 1929 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3118 "dhcp6_parser.cc"
    break;

  case 538: // sub_option_def: "{" $@76 option_def_params "}"
#line 1933 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3130 "dhcp6_parser.cc"
    break;

  case 543: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1949 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3138 "dhcp6_parser.cc"
    break;

  case 555: // code: "code" ":" "integer"
#line 1968 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3148 "dhcp6_parser.cc"
    break;

  case 557: // $@77: %empty
#line 1976 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3157 "dhcp6_parser.cc"
    break;

  case 558: // option_def_type: "type" $@77 ":" "constant string"
#line 1979 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3167 "dhcp6_parser.cc"
    break;

  case 559: // $@78: %empty
#line 1985 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3176 "dhcp6_parser.cc"
    break;

  case 560: // option_def_record_types: "record-types" $@78 ":" "constant string"
#line 1988 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3186 "dhcp6_parser.cc"
    break;

  case 561: // $@79: %empty
#line 1994 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3195 "dhcp6_parser.cc"
    break;

  case 562: // space: "space" $@79 ":" "constant string"
#line 1997 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3205 "dhcp6_parser.cc"
    break;

  case 564: // $@80: %empty
#line 2005 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3214 "dhcp6_parser.cc"
    break;

  case 565: // option_def_encapsulate: "encapsulate" $@80 ":" "constant string"
#line 2008 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3224 "dhcp6_parser.cc"
    break;

  case 566: // option_def_array: "array" ":" "boolean"
#line 2014 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3234 "dhcp6_parser.cc"
    break;

  case 567: // $@81: %empty
#line 2024 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3246 "dhcp6_parser.cc"
    break;

  case 568: // option_data_list: "option-data" $@81 ":" "[" option_data_list_content "]"
#line 2030 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3255 "dhcp6_parser.cc"
    break;

  case 573: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2045 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3263 "dhcp6_parser.cc"
    break;

  case 574: // $@82: %empty
#line 2052 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3273 "dhcp6_parser.cc"
    break;

  case 575: // option_data_entry: "{" $@82 option_data_params "}"
#line 2056 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3282 "dhcp6_parser.cc"
    break;

  case 576: // $@83: %empty
#line 2064 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3292 "dhcp6_parser.cc"
    break;

  case 577: // sub_option_data: "{" $@83 option_data_params "}"
#line 2068 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3301 "dhcp6_parser.cc"
    break;

  case 582: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2084 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3309 "dhcp6_parser.cc"
    break;

  case 595: // $@84: %empty
#line 2106 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3318 "dhcp6_parser.cc"
    break;

  case 596: // option_data_data: "data" $@84 ":" "constant string"
#line 2109 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3328 "dhcp6_parser.cc"
    break;

  case 599: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2119 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3338 "dhcp6_parser.cc"
    break;

  case 600: // option_data_always_send: "always-send" ":" "boolean"
#line 2125 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3348 "dhcp6_parser.cc"
    break;

  case 601: // option_data_never_send: "never-send" ":" "boolean"
#line 2131 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3358 "dhcp6_parser.cc"
    break;

  case 602: // $@85: %empty
#line 2137 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3370 "dhcp6_parser.cc"
    break;

  case 603: // option_data_client_classes: "client-classes" $@85 ":" list_strings
#line 2143 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3379 "dhcp6_parser.cc"
    break;

  case 604: // $@86: %empty
#line 2151 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3391 "dhcp6_parser.cc"
    break;

  case 605: // pools_list: "pools" $@86 ":" "[" pools_list_content "]"
#line 2157 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3400 "dhcp6_parser.cc"
    break;

  case 610: // not_empty_pools_list: not_empty_pools_list ","
#line 2170 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3408 "dhcp6_parser.cc"
    break;

  case 611: // $@87: %empty
#line 2175 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3418 "dhcp6_parser.cc"
    break;

  case 612: // pool_list_entry: "{" $@87 pool_params "}"
#line 2179 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3428 "dhcp6_parser.cc"
    break;

  case 613: // $@88: %empty
#line 2185 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3438 "dhcp6_parser.cc"
    break;

  case 614: // sub_pool6: "{" $@88 pool_params "}"
#line 2189 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3448 "dhcp6_parser.cc"
    break;

  case 617: // pool_params: pool_params ","
#line 2197 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3456 "dhcp6_parser.cc"
    break;

  case 628: // $@89: %empty
#line 2214 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3465 "dhcp6_parser.cc"
    break;

  case 629: // pool_entry: "pool" $@89 ":" "constant string"
#line 2217 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3475 "dhcp6_parser.cc"
    break;

  case 630: // pool_id: "pool-id" ":" "integer"
#line 2223 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3485 "dhcp6_parser.cc"
    break;

  case 631: // $@90: %empty
#line 2229 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3493 "dhcp6_parser.cc"
    break;

  case 632: // user_context: "user-context" $@90 ":" map_value
#line 2231 "dhcp6_parser.yy"
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
#line 3520 "dhcp6_parser.cc"
    break;

  case 633: // $@91: %empty
#line 2254 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3528 "dhcp6_parser.cc"
    break;

  case 634: // comment: "comment" $@91 ":" "constant string"
#line 2256 "dhcp6_parser.yy"
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
#line 3557 "dhcp6_parser.cc"
    break;

  case 635: // $@92: %empty
#line 2284 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3569 "dhcp6_parser.cc"
    break;

  case 636: // pd_pools_list: "pd-pools" $@92 ":" "[" pd_pools_list_content "]"
#line 2290 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3578 "dhcp6_parser.cc"
    break;

  case 641: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2303 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3586 "dhcp6_parser.cc"
    break;

  case 642: // $@93: %empty
#line 2308 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3596 "dhcp6_parser.cc"
    break;

  case 643: // pd_pool_entry: "{" $@93 pd_pool_params "}"
#line 2312 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3608 "dhcp6_parser.cc"
    break;

  case 644: // $@94: %empty
#line 2320 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3618 "dhcp6_parser.cc"
    break;

  case 645: // sub_pd_pool: "{" $@94 pd_pool_params "}"
#line 2324 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3630 "dhcp6_parser.cc"
    break;

  case 648: // pd_pool_params: pd_pool_params ","
#line 2334 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3638 "dhcp6_parser.cc"
    break;

  case 663: // $@95: %empty
#line 2355 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3647 "dhcp6_parser.cc"
    break;

  case 664: // pd_prefix: "prefix" $@95 ":" "constant string"
#line 2358 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3657 "dhcp6_parser.cc"
    break;

  case 665: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2364 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3667 "dhcp6_parser.cc"
    break;

  case 666: // $@96: %empty
#line 2370 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3676 "dhcp6_parser.cc"
    break;

  case 667: // excluded_prefix: "excluded-prefix" $@96 ":" "constant string"
#line 2373 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3686 "dhcp6_parser.cc"
    break;

  case 668: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2379 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3696 "dhcp6_parser.cc"
    break;

  case 669: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2385 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3706 "dhcp6_parser.cc"
    break;

  case 670: // $@97: %empty
#line 2394 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3718 "dhcp6_parser.cc"
    break;

  case 671: // reservations: "reservations" $@97 ":" "[" reservations_list "]"
#line 2400 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3727 "dhcp6_parser.cc"
    break;

  case 676: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2411 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3735 "dhcp6_parser.cc"
    break;

  case 677: // $@98: %empty
#line 2416 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3745 "dhcp6_parser.cc"
    break;

  case 678: // reservation: "{" $@98 reservation_params "}"
#line 2420 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3754 "dhcp6_parser.cc"
    break;

  case 679: // $@99: %empty
#line 2425 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3764 "dhcp6_parser.cc"
    break;

  case 680: // sub_reservation: "{" $@99 reservation_params "}"
#line 2429 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3773 "dhcp6_parser.cc"
    break;

  case 685: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2440 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3781 "dhcp6_parser.cc"
    break;

  case 698: // $@100: %empty
#line 2460 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3793 "dhcp6_parser.cc"
    break;

  case 699: // ip_addresses: "ip-addresses" $@100 ":" list_strings
#line 2466 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3802 "dhcp6_parser.cc"
    break;

  case 700: // $@101: %empty
#line 2471 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3814 "dhcp6_parser.cc"
    break;

  case 701: // prefixes: "prefixes" $@101 ":" list_strings
#line 2477 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3823 "dhcp6_parser.cc"
    break;

  case 702: // $@102: %empty
#line 2482 "dhcp6_parser.yy"
                                     {
    ctx.unique("excluded-prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3835 "dhcp6_parser.cc"
    break;

  case 703: // excluded_prefixes: "excluded-prefixes" $@102 ":" list_strings
#line 2488 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3844 "dhcp6_parser.cc"
    break;

  case 704: // $@103: %empty
#line 2493 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3853 "dhcp6_parser.cc"
    break;

  case 705: // duid: "duid" $@103 ":" "constant string"
#line 2496 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3863 "dhcp6_parser.cc"
    break;

  case 706: // $@104: %empty
#line 2502 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3872 "dhcp6_parser.cc"
    break;

  case 707: // hw_address: "hw-address" $@104 ":" "constant string"
#line 2505 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3882 "dhcp6_parser.cc"
    break;

  case 708: // $@105: %empty
#line 2511 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3891 "dhcp6_parser.cc"
    break;

  case 709: // hostname: "hostname" $@105 ":" "constant string"
#line 2514 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3901 "dhcp6_parser.cc"
    break;

  case 710: // $@106: %empty
#line 2520 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3910 "dhcp6_parser.cc"
    break;

  case 711: // flex_id_value: "flex-id" $@106 ":" "constant string"
#line 2523 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3920 "dhcp6_parser.cc"
    break;

  case 712: // $@107: %empty
#line 2529 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3932 "dhcp6_parser.cc"
    break;

  case 713: // reservation_client_classes: "client-classes" $@107 ":" list_strings
#line 2535 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3941 "dhcp6_parser.cc"
    break;

  case 714: // $@108: %empty
#line 2543 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3953 "dhcp6_parser.cc"
    break;

  case 715: // relay: "relay" $@108 ":" "{" relay_map "}"
#line 2549 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3962 "dhcp6_parser.cc"
    break;

  case 717: // $@109: %empty
#line 2560 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3974 "dhcp6_parser.cc"
    break;

  case 718: // client_classes: "client-classes" $@109 ":" "[" client_classes_list "]"
#line 2566 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3983 "dhcp6_parser.cc"
    break;

  case 721: // client_classes_list: client_classes_list ","
#line 2573 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3991 "dhcp6_parser.cc"
    break;

  case 722: // $@110: %empty
#line 2578 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4001 "dhcp6_parser.cc"
    break;

  case 723: // client_class_entry: "{" $@110 client_class_params "}"
#line 2582 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 4011 "dhcp6_parser.cc"
    break;

  case 728: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2594 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 4019 "dhcp6_parser.cc"
    break;

  case 745: // $@111: %empty
#line 2618 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4028 "dhcp6_parser.cc"
    break;

  case 746: // client_class_test: "test" $@111 ":" "constant string"
#line 2621 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4038 "dhcp6_parser.cc"
    break;

  case 747: // $@112: %empty
#line 2627 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4047 "dhcp6_parser.cc"
    break;

  case 748: // client_class_template_test: "template-test" $@112 ":" "constant string"
#line 2630 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4057 "dhcp6_parser.cc"
    break;

  case 749: // only_if_required: "only-if-required" ":" "boolean"
#line 2637 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4067 "dhcp6_parser.cc"
    break;

  case 750: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2643 "dhcp6_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4077 "dhcp6_parser.cc"
    break;

  case 751: // $@113: %empty
#line 2652 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 4089 "dhcp6_parser.cc"
    break;

  case 752: // server_id: "server-id" $@113 ":" "{" server_id_params "}"
#line 2658 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4100 "dhcp6_parser.cc"
    break;

  case 755: // server_id_params: server_id_params ","
#line 2667 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4108 "dhcp6_parser.cc"
    break;

  case 765: // $@114: %empty
#line 2683 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 4117 "dhcp6_parser.cc"
    break;

  case 766: // server_id_type: "type" $@114 ":" duid_type
#line 2686 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4126 "dhcp6_parser.cc"
    break;

  case 767: // duid_type: "LLT"
#line 2691 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4132 "dhcp6_parser.cc"
    break;

  case 768: // duid_type: "EN"
#line 2692 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4138 "dhcp6_parser.cc"
    break;

  case 769: // duid_type: "LL"
#line 2693 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4144 "dhcp6_parser.cc"
    break;

  case 770: // htype: "htype" ":" "integer"
#line 2696 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4154 "dhcp6_parser.cc"
    break;

  case 771: // $@115: %empty
#line 2702 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4163 "dhcp6_parser.cc"
    break;

  case 772: // identifier: "identifier" $@115 ":" "constant string"
#line 2705 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4173 "dhcp6_parser.cc"
    break;

  case 773: // time: "time" ":" "integer"
#line 2711 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4183 "dhcp6_parser.cc"
    break;

  case 774: // enterprise_id: "enterprise-id" ":" "integer"
#line 2717 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4193 "dhcp6_parser.cc"
    break;

  case 775: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2725 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4203 "dhcp6_parser.cc"
    break;

  case 776: // $@116: %empty
#line 2733 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4216 "dhcp6_parser.cc"
    break;

  case 777: // control_socket: "control-socket" $@116 ":" "{" control_socket_params "}"
#line 2740 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4225 "dhcp6_parser.cc"
    break;

  case 778: // $@117: %empty
#line 2745 "dhcp6_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4238 "dhcp6_parser.cc"
    break;

  case 779: // control_sockets: "control-sockets" $@117 ":" "[" control_socket_list "]"
#line 2752 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4247 "dhcp6_parser.cc"
    break;

  case 784: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2763 "dhcp6_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4255 "dhcp6_parser.cc"
    break;

  case 785: // $@118: %empty
#line 2768 "dhcp6_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4265 "dhcp6_parser.cc"
    break;

  case 786: // control_socket_entry: "{" $@118 control_socket_params "}"
#line 2772 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4273 "dhcp6_parser.cc"
    break;

  case 789: // control_socket_params: control_socket_params ","
#line 2778 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4281 "dhcp6_parser.cc"
    break;

  case 803: // $@119: %empty
#line 2798 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4290 "dhcp6_parser.cc"
    break;

  case 804: // control_socket_type: "socket-type" $@119 ":" control_socket_type_value
#line 2801 "dhcp6_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4299 "dhcp6_parser.cc"
    break;

  case 805: // control_socket_type_value: "unix"
#line 2807 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4305 "dhcp6_parser.cc"
    break;

  case 806: // control_socket_type_value: "http"
#line 2808 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4311 "dhcp6_parser.cc"
    break;

  case 807: // control_socket_type_value: "https"
#line 2809 "dhcp6_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4317 "dhcp6_parser.cc"
    break;

  case 808: // $@120: %empty
#line 2812 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4327 "dhcp6_parser.cc"
    break;

  case 809: // control_socket_name: "socket-name" $@120 ":" "constant string"
#line 2816 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4337 "dhcp6_parser.cc"
    break;

  case 810: // $@121: %empty
#line 2822 "dhcp6_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4347 "dhcp6_parser.cc"
    break;

  case 811: // control_socket_address: "socket-address" $@121 ":" "constant string"
#line 2826 "dhcp6_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4357 "dhcp6_parser.cc"
    break;

  case 812: // control_socket_port: "socket-port" ":" "integer"
#line 2832 "dhcp6_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4367 "dhcp6_parser.cc"
    break;

  case 813: // cert_required: "cert-required" ":" "boolean"
#line 2838 "dhcp6_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4377 "dhcp6_parser.cc"
    break;

  case 814: // $@122: %empty
#line 2844 "dhcp6_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4389 "dhcp6_parser.cc"
    break;

  case 815: // http_headers: "http-headers" $@122 ":" "[" http_header_list "]"
#line 2850 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4398 "dhcp6_parser.cc"
    break;

  case 820: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2861 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4406 "dhcp6_parser.cc"
    break;

  case 821: // $@123: %empty
#line 2866 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4416 "dhcp6_parser.cc"
    break;

  case 822: // http_header: "{" $@123 http_header_params "}"
#line 2870 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4424 "dhcp6_parser.cc"
    break;

  case 825: // http_header_params: http_header_params ","
#line 2876 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4432 "dhcp6_parser.cc"
    break;

  case 831: // $@124: %empty
#line 2888 "dhcp6_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4441 "dhcp6_parser.cc"
    break;

  case 832: // header_value: "value" $@124 ":" "constant string"
#line 2891 "dhcp6_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4451 "dhcp6_parser.cc"
    break;

  case 833: // $@125: %empty
#line 2899 "dhcp6_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4463 "dhcp6_parser.cc"
    break;

  case 834: // authentication: "authentication" $@125 ":" "{" auth_params "}"
#line 2905 "dhcp6_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4474 "dhcp6_parser.cc"
    break;

  case 837: // auth_params: auth_params ","
#line 2914 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4482 "dhcp6_parser.cc"
    break;

  case 845: // $@126: %empty
#line 2928 "dhcp6_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4491 "dhcp6_parser.cc"
    break;

  case 846: // auth_type: "type" $@126 ":" auth_type_value
#line 2931 "dhcp6_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4500 "dhcp6_parser.cc"
    break;

  case 847: // auth_type_value: "basic"
#line 2936 "dhcp6_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4506 "dhcp6_parser.cc"
    break;

  case 848: // $@127: %empty
#line 2939 "dhcp6_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4515 "dhcp6_parser.cc"
    break;

  case 849: // realm: "realm" $@127 ":" "constant string"
#line 2942 "dhcp6_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4525 "dhcp6_parser.cc"
    break;

  case 850: // $@128: %empty
#line 2948 "dhcp6_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4534 "dhcp6_parser.cc"
    break;

  case 851: // directory: "directory" $@128 ":" "constant string"
#line 2951 "dhcp6_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4544 "dhcp6_parser.cc"
    break;

  case 852: // $@129: %empty
#line 2957 "dhcp6_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4556 "dhcp6_parser.cc"
    break;

  case 853: // clients: "clients" $@129 ":" "[" clients_list "]"
#line 2963 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4565 "dhcp6_parser.cc"
    break;

  case 858: // not_empty_clients_list: not_empty_clients_list ","
#line 2974 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4573 "dhcp6_parser.cc"
    break;

  case 859: // $@130: %empty
#line 2979 "dhcp6_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4583 "dhcp6_parser.cc"
    break;

  case 860: // basic_auth: "{" $@130 clients_params "}"
#line 2983 "dhcp6_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4591 "dhcp6_parser.cc"
    break;

  case 863: // clients_params: clients_params ","
#line 2989 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4599 "dhcp6_parser.cc"
    break;

  case 871: // $@131: %empty
#line 3003 "dhcp6_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4608 "dhcp6_parser.cc"
    break;

  case 872: // user_file: "user-file" $@131 ":" "constant string"
#line 3006 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4618 "dhcp6_parser.cc"
    break;

  case 873: // $@132: %empty
#line 3012 "dhcp6_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4627 "dhcp6_parser.cc"
    break;

  case 874: // password_file: "password-file" $@132 ":" "constant string"
#line 3015 "dhcp6_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4637 "dhcp6_parser.cc"
    break;

  case 875: // $@133: %empty
#line 3023 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4649 "dhcp6_parser.cc"
    break;

  case 876: // dhcp_queue_control: "dhcp-queue-control" $@133 ":" "{" queue_control_params "}"
#line 3029 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4660 "dhcp6_parser.cc"
    break;

  case 879: // queue_control_params: queue_control_params ","
#line 3038 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4668 "dhcp6_parser.cc"
    break;

  case 886: // enable_queue: "enable-queue" ":" "boolean"
#line 3051 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4678 "dhcp6_parser.cc"
    break;

  case 887: // $@134: %empty
#line 3057 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4687 "dhcp6_parser.cc"
    break;

  case 888: // queue_type: "queue-type" $@134 ":" "constant string"
#line 3060 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4697 "dhcp6_parser.cc"
    break;

  case 889: // capacity: "capacity" ":" "integer"
#line 3066 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4707 "dhcp6_parser.cc"
    break;

  case 890: // $@135: %empty
#line 3072 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4716 "dhcp6_parser.cc"
    break;

  case 891: // arbitrary_map_entry: "constant string" $@135 ":" value
#line 3075 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4725 "dhcp6_parser.cc"
    break;

  case 892: // $@136: %empty
#line 3082 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4737 "dhcp6_parser.cc"
    break;

  case 893: // dhcp_ddns: "dhcp-ddns" $@136 ":" "{" dhcp_ddns_params "}"
#line 3088 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4748 "dhcp6_parser.cc"
    break;

  case 894: // $@137: %empty
#line 3095 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4758 "dhcp6_parser.cc"
    break;

  case 895: // sub_dhcp_ddns: "{" $@137 dhcp_ddns_params "}"
#line 3099 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4768 "dhcp6_parser.cc"
    break;

  case 898: // dhcp_ddns_params: dhcp_ddns_params ","
#line 3107 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4776 "dhcp6_parser.cc"
    break;

  case 910: // enable_updates: "enable-updates" ":" "boolean"
#line 3125 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4786 "dhcp6_parser.cc"
    break;

  case 911: // $@138: %empty
#line 3131 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4795 "dhcp6_parser.cc"
    break;

  case 912: // server_ip: "server-ip" $@138 ":" "constant string"
#line 3134 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4805 "dhcp6_parser.cc"
    break;

  case 913: // server_port: "server-port" ":" "integer"
#line 3140 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4815 "dhcp6_parser.cc"
    break;

  case 914: // $@139: %empty
#line 3146 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4824 "dhcp6_parser.cc"
    break;

  case 915: // sender_ip: "sender-ip" $@139 ":" "constant string"
#line 3149 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4834 "dhcp6_parser.cc"
    break;

  case 916: // sender_port: "sender-port" ":" "integer"
#line 3155 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4844 "dhcp6_parser.cc"
    break;

  case 917: // max_queue_size: "max-queue-size" ":" "integer"
#line 3161 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4854 "dhcp6_parser.cc"
    break;

  case 918: // $@140: %empty
#line 3167 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4863 "dhcp6_parser.cc"
    break;

  case 919: // ncr_protocol: "ncr-protocol" $@140 ":" ncr_protocol_value
#line 3170 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4872 "dhcp6_parser.cc"
    break;

  case 920: // ncr_protocol_value: "UDP"
#line 3176 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4878 "dhcp6_parser.cc"
    break;

  case 921: // ncr_protocol_value: "TCP"
#line 3177 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4884 "dhcp6_parser.cc"
    break;

  case 922: // $@141: %empty
#line 3180 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4893 "dhcp6_parser.cc"
    break;

  case 923: // ncr_format: "ncr-format" $@141 ":" "JSON"
#line 3183 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4903 "dhcp6_parser.cc"
    break;

  case 924: // $@142: %empty
#line 3191 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4915 "dhcp6_parser.cc"
    break;

  case 925: // config_control: "config-control" $@142 ":" "{" config_control_params "}"
#line 3197 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4925 "dhcp6_parser.cc"
    break;

  case 926: // $@143: %empty
#line 3203 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4935 "dhcp6_parser.cc"
    break;

  case 927: // sub_config_control: "{" $@143 config_control_params "}"
#line 3207 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4944 "dhcp6_parser.cc"
    break;

  case 930: // config_control_params: config_control_params ","
#line 3215 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4952 "dhcp6_parser.cc"
    break;

  case 933: // $@144: %empty
#line 3225 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4964 "dhcp6_parser.cc"
    break;

  case 934: // config_databases: "config-databases" $@144 ":" "[" database_list "]"
#line 3231 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4973 "dhcp6_parser.cc"
    break;

  case 935: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3236 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4983 "dhcp6_parser.cc"
    break;

  case 936: // $@145: %empty
#line 3244 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4995 "dhcp6_parser.cc"
    break;

  case 937: // loggers: "loggers" $@145 ":" "[" loggers_entries "]"
#line 3250 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5004 "dhcp6_parser.cc"
    break;

  case 940: // loggers_entries: loggers_entries ","
#line 3259 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 5012 "dhcp6_parser.cc"
    break;

  case 941: // $@146: %empty
#line 3265 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 5022 "dhcp6_parser.cc"
    break;

  case 942: // logger_entry: "{" $@146 logger_params "}"
#line 3269 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 5030 "dhcp6_parser.cc"
    break;

  case 945: // logger_params: logger_params ","
#line 3275 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 5038 "dhcp6_parser.cc"
    break;

  case 953: // debuglevel: "debuglevel" ":" "integer"
#line 3289 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 5048 "dhcp6_parser.cc"
    break;

  case 954: // $@147: %empty
#line 3295 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5057 "dhcp6_parser.cc"
    break;

  case 955: // severity: "severity" $@147 ":" "constant string"
#line 3298 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 5067 "dhcp6_parser.cc"
    break;

  case 956: // $@148: %empty
#line 3304 "dhcp6_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 5079 "dhcp6_parser.cc"
    break;

  case 957: // output_options_list: "output-options" $@148 ":" "[" output_options_list_content "]"
#line 3310 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5088 "dhcp6_parser.cc"
    break;

  case 960: // output_options_list_content: output_options_list_content ","
#line 3317 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 5096 "dhcp6_parser.cc"
    break;

  case 961: // $@149: %empty
#line 3322 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 5106 "dhcp6_parser.cc"
    break;

  case 962: // output_entry: "{" $@149 output_params_list "}"
#line 3326 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 5114 "dhcp6_parser.cc"
    break;

  case 965: // output_params_list: output_params_list ","
#line 3332 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 5122 "dhcp6_parser.cc"
    break;

  case 971: // $@150: %empty
#line 3344 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5131 "dhcp6_parser.cc"
    break;

  case 972: // output: "output" $@150 ":" "constant string"
#line 3347 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5141 "dhcp6_parser.cc"
    break;

  case 973: // flush: "flush" ":" "boolean"
#line 3353 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5151 "dhcp6_parser.cc"
    break;

  case 974: // maxsize: "maxsize" ":" "integer"
#line 3359 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5161 "dhcp6_parser.cc"
    break;

  case 975: // maxver: "maxver" ":" "integer"
#line 3365 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5171 "dhcp6_parser.cc"
    break;

  case 976: // $@151: %empty
#line 3371 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5180 "dhcp6_parser.cc"
    break;

  case 977: // pattern: "pattern" $@151 ":" "constant string"
#line 3374 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5190 "dhcp6_parser.cc"
    break;

  case 978: // $@152: %empty
#line 3380 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5202 "dhcp6_parser.cc"
    break;

  case 979: // compatibility: "compatibility" $@152 ":" "{" compatibility_params "}"
#line 3386 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5211 "dhcp6_parser.cc"
    break;

  case 982: // compatibility_params: compatibility_params ","
#line 3393 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5219 "dhcp6_parser.cc"
    break;

  case 985: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3402 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5229 "dhcp6_parser.cc"
    break;


#line 5233 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1421;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     764, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421,    69,    43,    36,    87,    94,
     123,   184,   186,   195,   205,   253,   254,   266,   275,   335,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,    43,  -167,
      93,   175,    70,   741,   483,   353,   604,     2,   111,   590,
    -103,   511,   128, -1421,   110,   168,   119,   255,   330, -1421,
      75, -1421, -1421, -1421, -1421, -1421, -1421, -1421,   346,   350,
     366,   367,   373,   374,   385,   406,   407,   414,   421,   422,
     440,   441, -1421,   445,   446,   459,   466,   467, -1421, -1421,
   -1421,   472,   476,   477,   478,   479,   484,   485, -1421, -1421,
   -1421,   488, -1421, -1421, -1421, -1421, -1421, -1421,   489,   490,
     491, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
     492, -1421, -1421, -1421, -1421, -1421, -1421, -1421,   494,   498,
     500, -1421, -1421,   502, -1421,    76, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,   503,
     505,   506,   507, -1421,   109, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,   508,   509,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421,   116, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,   510,
   -1421, -1421, -1421, -1421, -1421, -1421,   117, -1421, -1421, -1421,
   -1421, -1421, -1421,   512, -1421,   513,   516, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421,   135, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421,   336,   518, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421,   380, -1421, -1421,   519,
   -1421, -1421, -1421,   520, -1421, -1421,   521,   524, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421,   529,   532,   536, -1421, -1421, -1421, -1421, -1421,   535,
     542, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421,   145, -1421, -1421, -1421,   545,
   -1421,   547, -1421,   548,   549, -1421, -1421, -1421, -1421, -1421,
     146, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421,   552,   206, -1421, -1421, -1421, -1421,    43,    43, -1421,
     312,   553, -1421, -1421,   554,   555,   556,   558,   560,   561,
     252,   333,   337,   338,   339,   347,   354,   355,   334,   342,
     345,   352,   359,   362,   566,   368,   375,   348,   363,   369,
     571,   597,   607,   376,   379,   386,   390,   391,   392,   395,
     617,   629,   633,   403,   635,   636,   639,   640,   641,   646,
     417,   418,   420,   647,   652,   654,   656,   658,   660,   661,
     663,   665,   443,   675,   676,   677,   678,   679,   681,   682,
     451,   452,   460,   704,   705, -1421,   175, -1421,   706,   474,
     481,   480,   486,    70, -1421,   712,   716,   718,   725,   727,
     497,   496,   731,   732,   733,   742,   745,   741, -1421,   746,
     522,   483, -1421,   749,   525,   757,   527,   528,   353, -1421,
     760,   761,   762,   763,   765,   770,   771,   772, -1421,   604,
   -1421,   773,   774,   533,   775,   776,   777,   565, -1421,   111,
     778,   567,   568,   582,   782, -1421,   590,   799,   816,   -87,
   -1421,   585,   819,   591,   821,   592,   593,   825,   826,   511,
   -1421,   827,   601,   128, -1421, -1421, -1421,   828,   830,   605,
     833,   835,   837,   838,   841, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,   613,
   -1421, -1421, -1421, -1421, -1421,  -128,   614,   625, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421,   855,   856,   857, -1421,   630,
     634,   371,   858,   862,   637, -1421, -1421, -1421,   865,   868,
     870,   869,   873,   874,   875,   876,   877, -1421,   878,   879,
     882,   881,   896,   655,   670, -1421, -1421, -1421,   900,   899,
   -1421,   916, -1421, -1421, -1421, -1421, -1421,   919,   920,   692,
     693,   694, -1421, -1421,   916,   916,   916,   695,   923, -1421,
     697, -1421, -1421,   698, -1421,   699, -1421, -1421, -1421,   916,
     916,   916,   916,   703,   707,   708,   709, -1421,   710,   713,
   -1421,   714,   715,   721, -1421, -1421,   726, -1421, -1421, -1421,
     916, -1421,   728,   862, -1421, -1421,   729, -1421,   730, -1421,
   -1421,  -100,   739, -1421,   934, -1421, -1421,    43,   175, -1421,
     128,    70,   370,   370,   933, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421,   945,   954,   958, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421,   962, -1421, -1421, -1421,  -102,    43,
     -11,    99,   963,   964,   965,    34,    47,   198,   257,   967,
     189,   511, -1421, -1421,   969,  -164, -1421, -1421,   970,   971,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421,   747, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421,   933, -1421,   207,   208,   210, -1421,
   -1421, -1421, -1421,   975,   976,   977,   978,   994,   995,   996,
     997,   998,   999, -1421,  1000,  1001, -1421, -1421, -1421, -1421,
   -1421,   256, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421,   262, -1421,  1002,  1004, -1421,
   -1421,  1005,  1007, -1421, -1421,  1008,  1010, -1421, -1421,  1011,
    1013, -1421, -1421,  1015,  1021, -1421, -1421, -1421,   107, -1421,
   -1421, -1421,  1020, -1421, -1421, -1421,   164, -1421, -1421, -1421,
   -1421, -1421,   268, -1421, -1421, -1421, -1421,   269, -1421, -1421,
    1028,  1033, -1421, -1421,  1031,  1036, -1421,  1041,  1046,  1048,
    1049,  1051,  1054,   297, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421,  1056,  1057,  1062, -1421, -1421, -1421, -1421,
     307, -1421, -1421, -1421, -1421, -1421, -1421,  1064,  1070,  1073,
   -1421,   310, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421,  1076, -1421,  1078, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421,   313, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421,  1034,  1083, -1421,  1089, -1421,  1092, -1421, -1421, -1421,
     320, -1421, -1421, -1421, -1421, -1421,   322, -1421,   306, -1421,
    1099, -1421,   323, -1421, -1421,   871, -1421,  1108,  1114, -1421,
   -1421,  1129,  1171, -1421, -1421,  1177,  1173, -1421, -1421, -1421,
    1183,  1185,  1186,  1187,   957,   956,   959,   960,   961,   966,
     968,   972,   973,   974,  1191,   979,   980,  1194,  1195,  1196,
    1198,   370, -1421, -1421,   370, -1421,   933,   741, -1421,   945,
     111, -1421,   954,   590, -1421,   958,   842, -1421,   962,  -102,
   -1421, -1421,   -11, -1421,  1200,  1201,    99, -1421,   643,   963,
   -1421,   604, -1421,   964,  -103, -1421,   965,   982,   983,   984,
     985,   986,   987,    34, -1421,  1202,  1206,   988,   989,   990,
      47, -1421,   991,   992,  1003,   198, -1421,  1207,  1208,  1209,
    1006,  1210,   993,  1222,   257, -1421,   257, -1421,   967,  1009,
    1225,  1012,  1227,   189, -1421, -1421,   230,   969, -1421,  1014,
    -164, -1421, -1421,  1226,  1230,   483, -1421,   970,   353, -1421,
     971, -1421, -1421,  1016,  1018,  1025,  1027, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421,   120, -1421, -1421,
    1029,  1030,  1032,  1035, -1421,   326, -1421,   340, -1421,  1228,
   -1421,  1229, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421,   343, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421,  1037,  1038, -1421, -1421,
   -1421,  1231,  1235, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421,  1232,  1239, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421,  1236, -1421,   349, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421,   299,  1039, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421,   305,  1040,  1042, -1421,  1238, -1421,
    1243, -1421,   361, -1421, -1421,  1043, -1421,    43, -1421, -1421,
    1245, -1421, -1421, -1421, -1421, -1421,   364, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421,  1044,   365, -1421,   382, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421,   842, -1421, -1421, -1421,
    1250,  1258,  1045,  1050, -1421,   643, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,    80,
    1260, -1421, -1421, -1421,  1261,  1053,  1264,   230, -1421, -1421,
   -1421, -1421, -1421,  1047,  1052, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421,   383, -1421, -1421, -1421, -1421,
   -1421, -1421,  1237,  1267, -1421,  1274, -1421,  1059, -1421, -1421,
   -1421,  1276,  1279,  1281,  1286,    80, -1421,   -17, -1421,  1260,
    1287, -1421,  1120,  1065,  1067,  1291, -1421, -1421, -1421, -1421,
   -1421, -1421,   384, -1421, -1421, -1421, -1421,   316, -1421, -1421,
   -1421, -1421, -1421,  1295,  1299,   -17, -1421,  -109,  1287, -1421,
   -1421,  1301,  1302, -1421,  1074, -1421, -1421,  1305,  1306,  1308,
   -1421,   419, -1421, -1421, -1421, -1421, -1421, -1421, -1421,    28,
   -1421,  1295, -1421,  1310,  1079,  1080,  1084,  1314,  -109, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421,   438, -1421, -1421,
   -1421, -1421,  1086, -1421, -1421, -1421,  1087, -1421,  1319,  1320,
      28, -1421, -1421, -1421,  1091,  1094, -1421, -1421, -1421
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   205,     9,   391,    11,
     613,    13,   644,    15,   679,    17,   528,    19,   537,    21,
     576,    23,   353,    25,   894,    27,   926,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   681,     0,   539,   578,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   144,   924,   203,   224,   226,   228,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   193,     0,     0,     0,     0,     0,   163,   170,
     172,     0,     0,     0,     0,     0,     0,     0,   382,   526,
     567,     0,   196,   198,   176,   466,   631,   633,     0,     0,
       0,   309,   328,   318,   298,   717,   670,   344,   365,   751,
       0,   330,   776,   778,   875,   892,   186,   188,     0,     0,
       0,   936,   978,     0,   143,     0,    69,    72,    73,    74,
      75,    76,    77,    78,    79,    80,   111,   112,   113,   114,
     115,    81,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   117,   118,   132,   133,   134,
     107,   140,   141,   142,   136,   137,   138,    84,    85,    86,
      87,   104,    88,    90,    89,   135,    94,    95,    82,   108,
     109,   110,    83,    92,    93,   102,   103,   105,    91,    96,
      97,    98,    99,   100,   101,   106,   116,   139,   218,     0,
       0,     0,     0,   217,     0,   207,   210,   211,   212,   213,
     214,   215,   216,   604,   635,   447,   449,   451,     0,     0,
     455,   457,   459,   453,   714,   446,   396,   397,   398,   399,
     400,   401,   402,   403,   423,   424,   425,   426,   427,   430,
     431,   432,   433,   434,   435,   436,   437,   438,   439,   440,
     441,   442,   428,   429,   443,   444,   445,     0,   393,   407,
     408,   409,   412,   413,   414,   415,   417,   418,   419,   410,
     411,   404,   405,   421,   422,   406,   416,   420,   628,     0,
     627,   621,   622,   623,   624,   620,     0,   615,   618,   619,
     625,   626,   663,     0,   666,     0,     0,   662,   654,   655,
     656,   657,   653,   652,   660,   661,     0,   646,   649,   650,
     658,   659,   651,   712,   698,   700,   702,   704,   706,   708,
     710,   697,   694,   695,   696,     0,   682,   683,   688,   689,
     690,   686,   691,   692,   693,   687,     0,   557,   272,     0,
     561,   559,   564,     0,   553,   554,     0,   540,   541,   544,
     556,   545,   546,   547,   563,   548,   549,   550,   551,   552,
     595,     0,     0,     0,   602,   593,   594,   597,   598,     0,
     579,   580,   583,   584,   585,   586,   587,   588,   589,   592,
     590,   591,   361,   363,   358,     0,   355,   359,   360,     0,
     911,     0,   914,     0,     0,   918,   922,   909,   907,   908,
       0,   896,   899,   900,   901,   902,   903,   904,   905,   906,
     933,     0,     0,   928,   931,   932,    47,    52,     0,    39,
      45,     0,    66,    62,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    60,    71,    68,     0,     0,
       0,     0,     0,   209,   206,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   395,   392,     0,
       0,   617,   614,     0,     0,     0,     0,     0,   648,   645,
       0,     0,     0,     0,     0,     0,     0,     0,   680,   685,
     529,     0,     0,     0,     0,     0,     0,     0,   538,   543,
       0,     0,     0,     0,     0,   577,   582,     0,     0,   357,
     354,     0,     0,     0,     0,     0,     0,     0,     0,   898,
     895,     0,     0,   930,   927,    51,    43,     0,     0,     0,
       0,     0,     0,     0,     0,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,     0,
     191,   192,   160,   161,   162,     0,     0,     0,   174,   175,
     182,   183,   184,   185,   190,     0,     0,     0,   195,     0,
       0,     0,     0,     0,     0,   461,   462,   463,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   775,     0,     0,
       0,     0,     0,     0,     0,   200,   201,   202,     0,     0,
      70,     0,   220,   221,   222,   223,   208,     0,     0,     0,
       0,     0,   464,   465,     0,     0,     0,     0,     0,   394,
       0,   630,   616,     0,   665,     0,   668,   669,   647,     0,
       0,     0,     0,     0,     0,     0,     0,   684,     0,     0,
     555,     0,     0,     0,   566,   542,     0,   599,   600,   601,
       0,   581,     0,     0,   356,   910,     0,   913,     0,   916,
     917,     0,     0,   897,     0,   935,   929,     0,     0,   145,
       0,     0,     0,     0,   230,   194,   165,   166,   167,   168,
     169,   164,   171,   173,   384,   530,   569,   197,   199,   178,
     179,   180,   181,   177,   468,    40,   632,   634,     0,    48,
       0,     0,     0,   672,   346,     0,     0,     0,     0,   780,
       0,     0,   187,   189,     0,     0,    53,   219,   606,   637,
     448,   450,   452,   456,   458,   460,   454,     0,   629,   664,
     667,   713,   699,   701,   703,   705,   707,   709,   711,   558,
     273,   562,   560,   565,   596,   603,   362,   364,   912,   915,
     920,   921,   919,   923,   230,    44,     0,     0,     0,   263,
     265,   267,   269,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   282,     0,     0,   290,   292,   294,   296,
     262,     0,   237,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   254,   255,   256,   257,
     253,   258,   259,   260,   261,     0,   235,     0,   231,   232,
     389,     0,   385,   386,   535,     0,   531,   532,   574,     0,
     570,   571,   473,     0,   469,   470,   316,   317,     0,   311,
     314,   315,     0,   326,   327,   323,     0,   320,   324,   325,
     305,   307,     0,   300,   303,   304,   722,     0,   719,   677,
       0,   673,   674,   351,     0,   347,   348,     0,     0,     0,
       0,     0,     0,     0,   367,   370,   371,   372,   373,   374,
     375,   765,   771,     0,     0,     0,   764,   761,   762,   763,
       0,   753,   756,   759,   757,   758,   760,     0,     0,     0,
     340,     0,   332,   335,   336,   337,   338,   339,   803,   808,
     810,     0,   833,     0,   814,   802,   795,   796,   797,   800,
     801,     0,   787,   790,   791,   792,   793,   798,   799,   794,
     785,     0,   781,   782,     0,   887,     0,   890,   883,   884,
       0,   877,   880,   881,   882,   885,     0,   941,     0,   938,
       0,   984,     0,   980,   983,    55,   611,     0,   607,   608,
     642,     0,   638,   639,   716,     0,     0,    64,   925,   204,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   239,   225,   227,     0,   229,   234,     0,   383,   388,
     539,   527,   534,   578,   568,   573,     0,   467,   472,   313,
     310,   329,   322,   319,     0,     0,   302,   299,   724,   721,
     718,   681,   671,   676,     0,   345,   350,     0,     0,     0,
       0,     0,     0,   369,   366,     0,     0,     0,     0,     0,
     755,   752,     0,     0,     0,   334,   331,     0,     0,     0,
       0,     0,     0,     0,   789,   777,     0,   779,   784,     0,
       0,     0,     0,   879,   876,   893,     0,   940,   937,     0,
     982,   979,    57,     0,    56,     0,   605,   610,     0,   636,
     641,   715,   934,     0,     0,     0,     0,   271,   274,   275,
     276,   277,   278,   279,   280,   289,   281,     0,   287,   288,
       0,     0,     0,     0,   238,     0,   233,     0,   387,     0,
     533,     0,   572,   525,   493,   494,   495,   497,   498,   499,
     482,   483,   502,   503,   504,   505,   506,   509,   510,   511,
     512,   513,   514,   515,   516,   517,   518,   519,   520,   521,
     507,   508,   522,   523,   524,   478,   479,   480,   481,   489,
     490,   491,   492,   486,   487,   488,   496,     0,   475,   484,
     500,   501,   485,   471,   312,   321,     0,     0,   301,   745,
     747,     0,     0,   743,   737,   738,   739,   740,   741,   742,
     744,   734,   735,   736,     0,   725,   726,   729,   730,   731,
     732,   733,   720,     0,   675,     0,   349,   376,   377,   378,
     379,   380,   381,   368,     0,     0,   770,   773,   774,   754,
     341,   342,   343,   333,     0,     0,     0,   812,     0,   813,
       0,   788,     0,   783,   886,     0,   889,     0,   878,   956,
       0,   954,   952,   946,   950,   951,     0,   943,   948,   949,
     947,   939,   985,   981,    54,    59,     0,   609,     0,   640,
     264,   266,   268,   270,   284,   285,   286,   283,   291,   293,
     295,   297,   236,   390,   536,   575,   477,   474,   306,   308,
       0,     0,     0,     0,   723,   728,   678,   352,   767,   768,
     769,   766,   772,   805,   806,   807,   804,   809,   811,     0,
     816,   786,   888,   891,     0,     0,     0,   945,   942,    58,
     612,   643,   476,     0,     0,   749,   750,   727,   845,   848,
     850,   852,   844,   843,   842,     0,   835,   838,   839,   840,
     841,   821,     0,   817,   818,     0,   953,     0,   944,   746,
     748,     0,     0,     0,     0,   837,   834,     0,   815,   820,
       0,   955,     0,     0,     0,     0,   836,   831,   830,   826,
     828,   829,     0,   823,   827,   819,   961,     0,   958,   847,
     846,   849,   851,   854,     0,   825,   822,     0,   960,   957,
     859,     0,   855,   856,     0,   824,   971,     0,     0,     0,
     976,     0,   963,   966,   967,   968,   969,   970,   959,     0,
     853,   858,   832,     0,     0,     0,     0,     0,   965,   962,
     871,   873,   870,   864,   866,   868,   869,     0,   861,   865,
     867,   857,     0,   973,   974,   975,     0,   964,     0,     0,
     863,   860,   972,   977,     0,     0,   862,   872,   874
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421,   -10, -1421,  -621, -1421,
     586, -1421, -1421, -1421, -1421,   541, -1421,  -285, -1421, -1421,
   -1421,   -71, -1421, -1421, -1421, -1421, -1421, -1421, -1421,   574,
     798, -1421, -1421,     4,    12,    22,    38,    41,    42,   -57,
     -54,   -35,   -15,    20,    23,    45, -1421,    48,    55,    60,
      61, -1421, -1421,    66, -1421,    67, -1421,    71,    72,    73,
   -1421, -1421,    74,    77,    78,    79,    84, -1421,    85, -1421,
      89, -1421, -1421, -1421, -1421, -1421,    90, -1421,    91, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421,   473,   793, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421,   493, -1421,   263, -1421,  -742,   267, -1421, -1421, -1420,
   -1421, -1418, -1421, -1421, -1421, -1421,   -55, -1421,  -783, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421,  -787, -1421,  -781, -1421,  -778, -1421, -1421, -1421,
   -1421, -1421, -1421,   244, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421,   258,  -768, -1421, -1421, -1421, -1421,   249, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421,   218, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421,   239, -1421, -1421, -1421,   245,   752, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421,   235, -1421, -1421, -1421,
   -1421, -1421, -1421, -1061, -1421, -1421, -1421,   273, -1421, -1421,
   -1421,   276,   797, -1421, -1421, -1060, -1421, -1059, -1421,    25,
   -1421,    98, -1421,   100, -1421,   102, -1421,    92,    95,    96,
   -1421, -1058, -1421, -1421, -1421, -1421,   272, -1421, -1421,     9,
    1280, -1421, -1421, -1421, -1421, -1421,   279, -1421, -1421, -1421,
     283, -1421,   781, -1421,   -65, -1421, -1421, -1421, -1421, -1421,
     -61, -1421, -1421, -1421, -1421, -1421,   -29, -1421, -1421, -1421,
     280, -1421, -1421, -1421,   289, -1421,   780, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421,   221, -1421, -1421, -1421,   224,   820, -1421, -1421,   -63,
     -42, -1421,   -13, -1421, -1421, -1421, -1421, -1421,   220, -1421,
   -1421, -1421,   225,   814, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421,   -58, -1421, -1421, -1421,   282, -1421, -1421, -1421,   285,
   -1421,   810,   575, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1057, -1421,
   -1421, -1421, -1421, -1421,   296, -1421, -1421, -1421,    44, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,   288,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421,   271, -1421,   264,   277, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421,   -14, -1421, -1421,   -31, -1421, -1421, -1421, -1421,
   -1421,    -5, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421,   -56, -1421, -1421,   -84, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421,   278, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421,   621,   817, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421,   668,   832, -1421, -1421, -1421, -1421,
   -1421, -1421,   286, -1421, -1421,    57, -1421, -1421, -1421, -1421,
   -1421, -1421,    -9, -1421, -1421,   -38, -1421, -1421, -1421, -1421,
   -1421, -1421, -1421, -1421, -1421, -1421,   293, -1421
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     786,    87,    88,    41,    68,    84,    85,   807,  1035,  1153,
    1154,   870,    43,    70,    90,   461,    91,    45,    71,   165,
     166,   167,   464,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   490,   771,   186,   491,   187,   492,   188,   189,   190,
     506,   783,   191,   192,   193,   194,   195,   528,   196,   529,
     197,   198,   199,   200,   484,   201,   202,   504,   203,   505,
     204,   205,   206,   207,   466,    47,    72,   244,   245,   246,
     538,   247,   248,   249,   250,   208,   467,   209,   468,   210,
     469,   897,   898,   899,  1074,   871,   872,   873,  1050,   874,
    1051,   875,  1052,   876,  1053,   877,   878,   582,   879,   880,
     881,   882,   883,   884,   885,   886,   887,  1064,  1337,   888,
     889,   890,   891,  1067,   892,  1068,   893,  1069,   894,  1070,
     211,   516,   932,   933,   934,  1094,   935,  1095,   212,   513,
     918,   919,   920,   921,   213,   515,   926,   927,   928,   929,
     214,   514,   215,   523,   981,   982,   983,   984,   985,   216,
     519,   944,   945,   946,  1104,    63,    80,   425,   426,   427,
     597,   428,   598,   217,   520,   953,   954,   955,   956,   957,
     958,   959,   960,   218,   500,   901,   902,   903,  1077,    49,
      73,   297,   298,   299,   547,   300,   548,   301,   549,   302,
     555,   303,   552,   304,   553,   305,   554,   219,   220,   221,
     309,   310,   222,   507,   913,   914,   915,  1086,  1237,  1238,
     223,   501,    57,    77,   905,   906,   907,  1080,    59,    78,
     386,   387,   388,   389,   390,   391,   392,   581,   393,   585,
     394,   584,   395,   396,   586,   397,   224,   502,   909,   910,
     911,  1083,    61,    79,   409,   410,   411,   412,   413,   590,
     414,   415,   416,   417,   418,   419,   594,   312,   545,  1037,
    1038,  1039,  1155,    51,    74,   326,   327,   328,   559,   329,
     225,   508,   226,   509,   315,   546,  1041,  1042,  1043,  1158,
      53,    75,   346,   347,   348,   563,   349,   350,   565,   351,
     352,   227,   518,   940,   941,   942,  1101,    55,    76,   365,
     366,   367,   368,   571,   369,   572,   370,   573,   371,   574,
     372,   575,   373,   576,   374,   577,   375,   570,   317,   556,
    1045,   228,   517,   937,   938,  1098,  1264,  1265,  1266,  1267,
    1268,  1350,  1269,  1351,  1270,  1271,   229,   521,   970,   971,
     972,  1115,  1361,   973,   974,  1116,   975,   976,   230,   231,
     524,   232,   525,  1011,  1012,  1013,  1136,  1001,  1002,  1003,
    1127,  1366,  1004,  1128,  1005,  1129,  1006,  1007,  1008,  1133,
    1402,  1403,  1404,  1417,  1432,  1433,  1434,  1444,  1009,  1131,
    1395,  1396,  1397,  1411,  1440,  1398,  1412,  1399,  1413,  1400,
    1414,  1451,  1452,  1453,  1469,  1487,  1488,  1489,  1498,  1490,
    1499,   233,   526,  1020,  1021,  1022,  1023,  1140,  1024,  1025,
    1142,   234,   527,    65,    81,   440,   441,   442,   443,   602,
     444,   445,   604,   446,   447,   448,   607,   842,   449,   608,
     235,   465,    67,    82,   452,   453,   454,   611,   455,   236,
     533,  1028,  1029,  1146,  1316,  1317,  1318,  1319,  1376,  1320,
    1374,  1437,  1438,  1447,  1461,  1462,  1463,  1473,  1464,  1465,
    1466,  1467,  1477,   237,   534,  1032,  1033,  1034
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     164,   243,   265,   320,   337,   361,    38,   384,   405,   424,
     437,   996,   343,   967,   407,   316,   272,   997,   408,   273,
     998,   895,   925,   385,   406,  1226,  1227,  1228,  1236,  1242,
     251,   313,   330,   344,   363,   916,   398,   420,   274,   438,
     422,   423,   785,    42,   311,   325,   342,   362,    31,  1483,
      32,  1484,    33,   850,   851,  1030,   422,   423,   275,   252,
     314,   331,   345,   364,   378,   399,   421,    86,   439,    30,
     163,   961,   766,   767,   768,   769,   854,   266,   462,   536,
    1483,   129,  1484,   463,   537,   267,   238,   239,   240,   241,
     242,   136,   137,   276,    44,   268,   277,   840,   841,   321,
     338,    46,  1456,    89,  1388,  1457,  1458,  1459,  1460,   770,
    1089,   269,   543,  1090,   270,   271,   456,   544,   278,   557,
     561,   279,   785,   458,   558,   562,   916,   923,   280,   924,
      48,   163,   917,   281,   282,   377,   136,   137,   568,   283,
     284,   450,   451,   569,   285,   286,   287,   288,   599,   609,
     289,   290,   291,   600,   610,   136,   137,   292,   293,  1334,
    1335,  1336,   294,   295,   296,   306,  1427,  1092,   307,   308,
    1093,   457,   322,   339,   323,   340,   324,   341,   136,   137,
     947,   948,   949,   950,   951,   952,    92,    93,   136,   137,
      94,    50,   378,    52,   379,   380,    95,    96,    97,   381,
     382,   383,    54,   962,   963,   964,   965,  1480,  1481,   613,
     536,   613,    56,   543,   614,  1047,  1048,   163,  1049,   136,
     137,   930,   931,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,  1389,  1390,  1391,  1071,
      58,    60,   163,   459,  1072,  1071,   131,   132,   133,   134,
    1073,  1096,  1099,    62,   135,  1100,  1097,    34,    35,    36,
      37,   163,    64,   136,   137,  1226,  1227,  1228,  1236,  1242,
     138,   139,   140,   141,   142,   143,   144,   136,   137,   145,
    1113,   866,   867,   868,   163,  1114,   136,   137,   146,  1147,
    1120,   378,  1148,  1125,   163,  1121,  1134,   147,  1126,  1448,
     148,  1135,  1449,  1143,   925,   609,  1150,   149,  1144,  1071,
    1145,  1151,  1185,   460,  1342,   150,   151,   967,   136,   137,
     152,   153,    66,   557,   578,   163,  1346,   996,  1343,   996,
     470,  1347,   599,   997,   471,   997,   998,  1357,   998,   154,
     977,   978,   979,   155,  1134,   136,   137,  1377,   561,  1371,
     472,   473,  1378,  1380,  1014,  1015,  1016,   474,   475,   156,
     157,   158,   159,   160,   161,   568,  1415,  1445,   580,   476,
    1381,  1416,  1446,   162,   849,   850,   851,   852,   853,   854,
     855,   856,   857,   858,   859,   860,   861,   862,   863,   163,
     477,   478,   864,   865,   866,   867,   868,   869,   479,   813,
     814,   815,  1478,  1017,   988,   480,   481,  1479,   989,   990,
     991,   992,   163,   130,   821,   822,   823,   824,   993,   994,
    1309,  1500,  1310,  1311,   482,   483,  1501,   615,   616,   485,
     486,   378,  1358,  1359,  1360,   835,   332,   333,   334,   335,
     336,   136,   137,   487,   163,   164,   779,   780,   781,   782,
     488,   489,   243,  1363,  1364,  1365,   493,   260,   261,   262,
     494,   495,   496,   497,   263,   319,   265,   625,   498,   499,
     320,   163,   503,   510,   511,   512,   522,   337,   530,   316,
     272,   251,   531,   273,   532,   343,   535,   539,   361,   540,
     541,   542,   550,   551,   560,   313,   564,   566,   384,   330,
     567,   579,   274,   583,   587,   405,   344,   589,   311,   588,
     252,   407,   325,   591,   385,   408,   592,   363,   437,   342,
     593,   406,   275,   595,   314,   596,   617,   398,   331,   601,
     362,   603,   605,   606,   420,   345,   612,   618,   619,   620,
     621,   266,   622,   130,   623,   624,   364,   438,   626,   267,
     639,   633,   627,   628,   629,   645,   399,   276,   634,   268,
     277,   635,   630,   421,   318,   642,   321,   163,   636,   631,
     632,   136,   137,   338,   637,   269,   439,   638,   270,   271,
     643,   646,   278,   640,   163,   279,   644,   260,   261,   262,
     641,   647,   280,   648,   263,   319,   649,   281,   282,   136,
     137,   655,   650,   283,   284,   651,   652,   653,   285,   286,
     287,   288,   654,   656,   289,   290,   291,   657,   658,   659,
     660,   292,   293,   661,   662,   663,   294,   295,   296,   306,
     664,   668,   307,   308,   665,   666,   669,   667,   670,   322,
     671,   323,   672,   324,   673,   674,   339,   675,   340,   676,
     341,   378,   400,   379,   380,   401,   402,   403,   677,   678,
     679,   680,   681,   682,   130,   683,   684,   164,   685,   686,
     243,    98,    99,   100,   101,   102,   103,   687,   136,   137,
     429,   430,   431,   432,   433,   434,   435,   436,   688,   689,
     691,   692,   136,   137,   404,   694,   697,   163,   693,   251,
     698,   695,   699,   130,   378,   966,   980,   995,   353,   700,
     437,   701,   702,   703,  1031,   704,   705,   706,   354,   355,
     356,   357,   358,   359,   360,   163,   707,   845,   252,   708,
     710,   136,   137,   713,   968,   986,   999,   711,  1018,   438,
     714,   715,   716,   717,   719,   720,   721,   722,   730,   723,
    1249,  1250,  1251,  1252,   724,   725,   726,   728,   729,   731,
     732,   733,   736,   969,   987,  1000,   740,  1019,   439,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   734,   742,   737,   738,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   739,
     743,   130,   745,   746,   163,   748,   747,   749,   750,   751,
     752,   754,   757,   132,   133,   134,   755,   758,   163,   759,
     760,   253,   761,   254,   762,   763,   764,   765,   772,   136,
     137,   255,   256,   257,   258,   259,   138,   139,   140,   773,
     774,   775,   776,   784,   777,   260,   261,   262,   778,    32,
     788,   787,   263,   789,   146,   790,   791,   163,   792,   793,
     794,   354,   264,   795,   796,   797,   798,   799,   800,   802,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   801,   803,   804,   805,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   806,   130,   378,   808,   809,   810,   811,   812,   816,
     817,   818,   819,   820,   132,   133,   134,   825,   843,   844,
     896,   826,   827,   828,   829,   156,   157,   830,   831,   832,
     136,   137,   900,   256,   257,   833,   259,   138,   139,   140,
     834,   904,   836,   838,   839,   908,   260,   261,   262,   912,
     936,   939,   943,   263,  1010,   163,  1027,  1036,  1040,  1054,
    1055,  1056,  1057,   264,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,  1058,  1059,
    1060,  1061,  1062,  1063,  1065,  1066,   265,  1076,  1075,   384,
    1079,  1078,   405,  1082,  1081,  1193,  1085,  1084,   407,   316,
     272,  1087,   408,   273,  1088,   385,  1091,  1253,   406,  1200,
     361,  1225,  1201,   424,  1102,   313,  1103,  1105,   398,  1106,
    1137,   420,   274,  1260,  1240,  1107,   156,   157,   311,   966,
    1108,  1202,  1109,  1110,   980,  1111,  1262,  1239,  1112,   363,
    1117,  1118,   275,   995,   314,   995,  1119,   399,  1122,  1261,
     421,  1203,   362,  1241,  1123,  1312,   163,  1124,   968,  1031,
    1130,   266,  1132,   986,   320,  1263,  1138,   337,   364,   267,
    1194,  1313,   999,  1139,   999,   343,  1141,   276,  1195,   268,
     277,  1018,  1254,  1149,  1314,  1152,  1204,   969,  1196,  1205,
    1255,  1229,   987,   330,  1156,   269,   344,  1157,   270,   271,
    1256,  1000,   278,  1000,  1197,   279,   325,  1198,  1199,   342,
    1019,  1206,   280,  1315,  1207,  1159,  1257,   281,   282,  1258,
    1259,  1208,   331,   283,   284,   345,  1209,  1210,   285,   286,
     287,   288,  1211,  1212,   289,   290,   291,  1213,  1214,  1215,
    1216,   292,   293,  1217,  1218,  1219,   294,   295,   296,   306,
    1220,  1221,   307,   308,  1160,  1222,  1223,  1224,  1233,  1162,
     321,  1234,  1235,   338,  1230,  1161,  1231,  1163,  1232,  1164,
    1165,  1166,  1167,  1168,  1169,  1177,  1171,  1170,  1180,  1181,
    1182,  1172,  1183,  1173,  1246,  1247,  1284,  1174,  1175,  1176,
    1285,  1294,  1295,  1296,  1298,  1179,  1178,  1277,  1278,  1279,
    1280,  1281,  1282,  1286,  1287,  1288,  1300,  1291,  1290,  1305,
    1299,  1307,  1324,  1325,   848,  1352,  1344,  1345,  1292,  1353,
    1354,  1297,  1355,  1418,  1356,  1369,  1304,  1306,  1370,  1375,
    1330,  1322,  1331,   322,  1383,   323,   339,   324,   340,  1332,
     341,  1333,  1384,  1338,  1339,  1405,  1340,  1401,  1407,  1341,
    1419,  1348,  1349,  1362,  1367,  1193,  1368,  1372,  1379,  1420,
    1422,  1409,  1385,  1423,  1253,  1424,  1410,  1386,  1406,  1200,
    1425,  1225,  1201,  1421,  1436,  1439,  1443,  1373,  1392,  1441,
    1260,  1442,  1450,  1454,  1240,  1471,  1312,  1470,  1472,  1474,
    1475,  1202,  1476,  1262,  1492,  1494,  1493,  1239,  1496,  1495,
    1502,  1503,  1313,  1504,  1505,  1507,  1261,  1393,  1508,   837,
     922,  1203,   846,  1241,   690,  1314,   696,  1046,  1184,  1186,
    1248,  1245,  1263,  1293,  1392,  1276,  1428,  1244,  1283,  1275,
    1194,   744,  1188,  1187,   709,  1382,  1394,   376,  1195,  1254,
    1243,  1190,  1429,  1189,  1315,  1192,  1204,  1255,  1196,  1205,
     735,  1229,  1191,  1393,  1428,  1430,   741,  1256,  1327,  1326,
    1329,   712,   718,  1328,  1197,  1274,  1273,  1198,  1199,   727,
    1429,  1206,  1044,  1257,  1207,  1272,  1258,  1259,  1482,  1387,
    1302,  1208,  1394,  1430,  1431,  1435,  1209,  1210,  1289,  1303,
    1426,  1301,  1211,  1212,  1455,  1491,  1506,  1213,  1214,  1215,
    1216,  1308,  1026,  1217,  1218,  1219,   753,  1485,   847,  1482,
    1220,  1221,  1431,  1321,  1408,  1222,  1223,  1224,  1233,  1468,
    1497,  1234,  1235,  1323,  1230,   756,  1231,     0,  1232,     0,
       0,     0,     0,     0,     0,     0,  1486,     0,  1485,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1486
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   798,    75,   796,    79,    73,    73,   798,    79,    73,
     798,   763,   790,    78,    79,  1086,  1086,  1086,  1086,  1086,
      72,    73,    74,    75,    76,   137,    78,    79,    73,    81,
     143,   144,   663,     7,    73,    74,    75,    76,     5,  1469,
       7,  1469,     9,    25,    26,   219,   143,   144,    73,    72,
      73,    74,    75,    76,    81,    78,    79,   234,    81,     0,
     234,    24,   200,   201,   202,   203,    29,    73,     3,     3,
    1500,    79,  1500,     8,     8,    73,    16,    17,    18,    19,
      20,   108,   109,    73,     7,    73,    73,   197,   198,    74,
      75,     7,   211,    10,    24,   214,   215,   216,   217,   237,
       3,    73,     3,     6,    73,    73,     6,     8,    73,     3,
       3,    73,   743,     4,     8,     8,   137,   138,    73,   140,
       7,   234,   234,    73,    73,    24,   108,   109,     3,    73,
      73,    13,    14,     8,    73,    73,    73,    73,     3,     3,
      73,    73,    73,     8,     8,   108,   109,    73,    73,    39,
      40,    41,    73,    73,    73,    73,   183,     3,    73,    73,
       6,     3,    74,    75,    74,    75,    74,    75,   108,   109,
     146,   147,   148,   149,   150,   151,    11,    12,   108,   109,
      15,     7,    81,     7,    83,    84,    21,    22,    23,    88,
      89,    90,     7,   156,   157,   158,   159,   179,   180,     3,
       3,     3,     7,     3,     8,     8,     8,   234,     8,   108,
     109,   122,   123,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,   176,   177,   178,     3,
       7,     7,   234,     8,     8,     3,    91,    92,    93,    94,
       8,     3,     3,     7,    99,     6,     8,   234,   235,   236,
     237,   234,     7,   108,   109,  1346,  1346,  1346,  1346,  1346,
     115,   116,   117,   118,   119,   120,   121,   108,   109,   124,
       3,    44,    45,    46,   234,     8,   108,   109,   133,     3,
       3,    81,     6,     3,   234,     8,     3,   142,     8,     3,
     145,     8,     6,     3,  1092,     3,     3,   152,     8,     3,
       8,     8,  1074,     3,     8,   160,   161,  1120,   108,   109,
     165,   166,     7,     3,     8,   234,     3,  1134,     8,  1136,
       4,     8,     3,  1134,     4,  1136,  1134,     8,  1136,   184,
     162,   163,   164,   188,     3,   108,   109,     3,     3,     8,
       4,     4,     8,     8,   185,   186,   187,     4,     4,   204,
     205,   206,   207,   208,   209,     3,     3,     3,     8,     4,
       8,     8,     8,   218,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,   234,
       4,     4,    42,    43,    44,    45,    46,    47,     4,   704,
     705,   706,     3,   234,   167,     4,     4,     8,   171,   172,
     173,   174,   234,    80,   719,   720,   721,   722,   181,   182,
     210,     3,   212,   213,     4,     4,     8,   457,   458,     4,
       4,    81,   153,   154,   155,   740,   103,   104,   105,   106,
     107,   108,   109,     4,   234,   536,    95,    96,    97,    98,
       4,     4,   543,   168,   169,   170,     4,   124,   125,   126,
       4,     4,     4,     4,   131,   132,   557,   235,     4,     4,
     561,   234,     4,     4,     4,     4,     4,   568,     4,   557,
     557,   543,     4,   557,     4,   568,     4,     4,   579,     4,
       4,     4,     4,     4,     4,   557,     4,     4,   589,   561,
       4,     3,   557,     4,     4,   596,   568,     3,   557,     8,
     543,   596,   561,     4,   589,   596,     4,   579,   609,   568,
       4,   596,   557,     8,   557,     3,   234,   589,   561,     4,
     579,     4,     4,     4,   596,   568,     4,     4,     4,     4,
       4,   557,     4,    80,     4,     4,   579,   609,   235,   557,
       4,   237,   235,   235,   235,     4,   589,   557,   236,   557,
     557,   236,   235,   596,   101,   237,   561,   234,   236,   235,
     235,   108,   109,   568,   235,   557,   609,   235,   557,   557,
     237,     4,   557,   235,   234,   557,   237,   124,   125,   126,
     235,     4,   557,   237,   131,   132,   237,   557,   557,   108,
     109,     4,   236,   557,   557,   235,   235,   235,   557,   557,
     557,   557,   237,     4,   557,   557,   557,     4,   235,     4,
       4,   557,   557,     4,     4,     4,   557,   557,   557,   557,
       4,     4,   557,   557,   237,   237,     4,   237,     4,   561,
       4,   561,     4,   561,     4,     4,   568,     4,   568,     4,
     568,    81,    82,    83,    84,    85,    86,    87,   235,     4,
       4,     4,     4,     4,    80,     4,     4,   758,   237,   237,
     761,    48,    49,    50,    51,    52,    53,   237,   108,   109,
     189,   190,   191,   192,   193,   194,   195,   196,     4,     4,
       4,   237,   108,   109,   124,   235,     4,   234,   237,   761,
       4,   235,     4,    80,    81,   796,   797,   798,   124,     4,
     801,     4,   235,   237,   805,     4,     4,     4,   134,   135,
     136,   137,   138,   139,   140,   234,     4,   757,   761,     4,
       4,   108,   109,     4,   796,   797,   798,   235,   800,   801,
     235,     4,   235,   235,     4,     4,     4,     4,   235,     4,
     127,   128,   129,   130,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   796,   797,   798,     4,   800,   801,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,   237,     4,   237,   237,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,   237,
       4,    80,   237,     4,   234,     4,   235,   235,   235,     4,
       4,     4,     4,    92,    93,    94,   235,     7,   234,   234,
       7,   100,     7,   102,     7,     7,     5,   234,   234,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   234,
       5,     5,     5,     5,   234,   124,   125,   126,   234,     7,
       5,   234,   131,     5,   133,     5,     7,   234,     5,     5,
       5,   134,   141,     7,     7,     7,     7,     5,     7,   234,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,     7,   234,     5,     7,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,     5,    80,    81,     5,     5,   234,   234,   234,   234,
       7,   234,   234,   234,    92,    93,    94,   234,   199,     5,
       7,   234,   234,   234,   234,   204,   205,   234,   234,   234,
     108,   109,     7,   111,   112,   234,   114,   115,   116,   117,
     234,     7,   234,   234,   234,     7,   124,   125,   126,     7,
       7,     7,     7,   131,     7,   234,     7,     7,     7,     4,
       4,     4,     4,   141,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,     4,     4,
       4,     4,     4,     4,     4,     4,  1077,     3,     6,  1080,
       3,     6,  1083,     3,     6,  1086,     3,     6,  1083,  1077,
    1077,     6,  1083,  1077,     3,  1080,     6,  1098,  1083,  1086,
    1101,  1086,  1086,  1104,     6,  1077,     3,     6,  1080,     3,
       6,  1083,  1077,  1098,  1086,     4,   204,   205,  1077,  1120,
       4,  1086,     4,     4,  1125,     4,  1098,  1086,     4,  1101,
       4,     4,  1077,  1134,  1077,  1136,     4,  1080,     4,  1098,
    1083,  1086,  1101,  1086,     4,  1146,   234,     4,  1120,  1150,
       4,  1077,     4,  1125,  1155,  1098,     3,  1158,  1101,  1077,
    1086,  1146,  1134,     4,  1136,  1158,     4,  1077,  1086,  1077,
    1077,  1143,  1098,     4,  1146,   234,  1086,  1120,  1086,  1086,
    1098,  1086,  1125,  1155,     6,  1077,  1158,     3,  1077,  1077,
    1098,  1134,  1077,  1136,  1086,  1077,  1155,  1086,  1086,  1158,
    1143,  1086,  1077,  1146,  1086,     6,  1098,  1077,  1077,  1098,
    1098,  1086,  1155,  1077,  1077,  1158,  1086,  1086,  1077,  1077,
    1077,  1077,  1086,  1086,  1077,  1077,  1077,  1086,  1086,  1086,
    1086,  1077,  1077,  1086,  1086,  1086,  1077,  1077,  1077,  1077,
    1086,  1086,  1077,  1077,     3,  1086,  1086,  1086,  1086,     6,
    1155,  1086,  1086,  1158,  1086,     8,  1086,     4,  1086,     4,
       4,     4,   235,   237,   235,     4,   235,   237,     4,     4,
       4,   235,     4,   235,     4,     4,     4,   235,   235,   235,
       4,     4,     4,     4,     4,   235,   237,   235,   235,   235,
     235,   235,   235,   235,   235,   235,     4,   235,   237,     4,
     237,     4,     6,     3,   761,     4,     8,     8,   235,     4,
       8,   235,     3,     6,     8,     7,   237,   235,     5,     4,
     234,   237,   234,  1155,     4,  1155,  1158,  1155,  1158,   234,
    1158,   234,     4,   234,   234,     4,   234,     7,     4,   234,
       3,   234,   234,   234,   234,  1346,   234,   234,   234,     5,
       4,   234,   237,     4,  1355,     4,   234,   237,   235,  1346,
       4,  1346,  1346,   234,     7,   175,     5,  1307,  1369,   234,
    1355,   234,     7,     4,  1346,     3,  1377,     6,   234,     4,
       4,  1346,     4,  1355,     4,   235,   237,  1346,     4,   235,
     234,   234,  1377,     4,     4,   234,  1355,  1369,   234,   743,
     789,  1346,   758,  1346,   536,  1377,   543,   844,  1071,  1076,
    1096,  1092,  1355,  1125,  1415,  1106,  1417,  1089,  1113,  1104,
    1346,   599,  1079,  1077,   557,  1346,  1369,    77,  1346,  1355,
    1088,  1082,  1417,  1080,  1377,  1085,  1346,  1355,  1346,  1346,
     589,  1346,  1083,  1415,  1445,  1417,   596,  1355,  1157,  1155,
    1160,   561,   568,  1158,  1346,  1103,  1101,  1346,  1346,   579,
    1445,  1346,   817,  1355,  1346,  1099,  1355,  1355,  1469,  1355,
    1136,  1346,  1415,  1445,  1417,  1419,  1346,  1346,  1120,  1138,
    1415,  1134,  1346,  1346,  1445,  1471,  1500,  1346,  1346,  1346,
    1346,  1143,   801,  1346,  1346,  1346,   609,  1469,   760,  1500,
    1346,  1346,  1445,  1147,  1377,  1346,  1346,  1346,  1346,  1448,
    1478,  1346,  1346,  1150,  1346,   613,  1346,    -1,  1346,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1469,    -1,  1500,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1500
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
       0,     5,     7,     9,   234,   235,   236,   237,   254,   255,
     256,   261,     7,   270,     7,   275,     7,   333,     7,   447,
       7,   531,     7,   548,     7,   565,     7,   480,     7,   486,
       7,   510,     7,   423,     7,   681,     7,   700,   262,   257,
     271,   276,   334,   448,   532,   549,   566,   481,   487,   511,
     424,   682,   701,   254,   263,   264,   234,   259,   260,    10,
     272,   274,    11,    12,    15,    21,    22,    23,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    91,    92,    93,    94,    99,   108,   109,   115,   116,
     117,   118,   119,   120,   121,   124,   133,   142,   145,   152,
     160,   161,   165,   166,   184,   188,   204,   205,   206,   207,
     208,   209,   218,   234,   269,   277,   278,   279,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   301,   303,   305,   306,
     307,   310,   311,   312,   313,   314,   316,   318,   319,   320,
     321,   323,   324,   326,   328,   329,   330,   331,   343,   345,
     347,   388,   396,   402,   408,   410,   417,   431,   441,   465,
     466,   467,   470,   478,   504,   538,   540,   559,   589,   604,
     616,   617,   619,   669,   679,   698,   707,   731,    16,    17,
      18,    19,    20,   269,   335,   336,   337,   339,   340,   341,
     342,   538,   540,   100,   102,   110,   111,   112,   113,   114,
     124,   125,   126,   131,   141,   269,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   295,
     296,   297,   298,   301,   303,   305,   306,   307,   310,   311,
     312,   313,   314,   316,   318,   324,   326,   449,   450,   451,
     453,   455,   457,   459,   461,   463,   465,   466,   467,   468,
     469,   504,   525,   538,   540,   542,   559,   586,   101,   132,
     269,   457,   459,   461,   463,   504,   533,   534,   535,   537,
     538,   540,   103,   104,   105,   106,   107,   269,   457,   459,
     461,   463,   504,   537,   538,   540,   550,   551,   552,   554,
     555,   557,   558,   124,   134,   135,   136,   137,   138,   139,
     140,   269,   504,   538,   540,   567,   568,   569,   570,   572,
     574,   576,   578,   580,   582,   584,   478,    24,    81,    83,
      84,    88,    89,    90,   269,   364,   488,   489,   490,   491,
     492,   493,   494,   496,   498,   500,   501,   503,   538,   540,
      82,    85,    86,    87,   124,   269,   364,   492,   498,   512,
     513,   514,   515,   516,   518,   519,   520,   521,   522,   523,
     538,   540,   143,   144,   269,   425,   426,   427,   429,   189,
     190,   191,   192,   193,   194,   195,   196,   269,   538,   540,
     683,   684,   685,   686,   688,   689,   691,   692,   693,   696,
      13,    14,   702,   703,   704,   706,     6,     3,     4,     8,
       3,   273,     3,     8,   280,   699,   332,   344,   346,   348,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   322,     4,     4,     4,     4,     4,
     299,   302,   304,     4,     4,     4,     4,     4,     4,     4,
     442,   479,   505,     4,   325,   327,   308,   471,   539,   541,
       4,     4,     4,   397,   409,   403,   389,   590,   560,   418,
     432,   605,     4,   411,   618,   620,   670,   680,   315,   317,
       4,     4,     4,   708,   732,     4,     3,     8,   338,     4,
       4,     4,     4,     3,     8,   526,   543,   452,   454,   456,
       4,     4,   460,   462,   464,   458,   587,     3,     8,   536,
       4,     3,     8,   553,     4,   556,     4,     4,     3,     8,
     585,   571,   573,   575,   577,   579,   581,   583,     8,     3,
       8,   495,   365,     4,   499,   497,   502,     4,     8,     3,
     517,     4,     4,     4,   524,     8,     3,   428,   430,     3,
       8,     4,   687,     4,   690,     4,     4,   694,   697,     3,
       8,   705,     4,     3,     8,   254,   254,   234,     4,     4,
       4,     4,     4,     4,     4,   235,   235,   235,   235,   235,
     235,   235,   235,   237,   236,   236,   236,   235,   235,     4,
     235,   235,   237,   237,   237,     4,     4,     4,   237,   237,
     236,   235,   235,   235,   237,     4,     4,     4,   235,     4,
       4,     4,     4,     4,     4,   237,   237,   237,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   235,     4,     4,
       4,     4,     4,     4,     4,   237,   237,   237,     4,     4,
     278,     4,   237,   237,   235,   235,   336,     4,     4,     4,
       4,     4,   235,   237,     4,     4,     4,     4,     4,   450,
       4,   235,   534,     4,   235,     4,   235,   235,   551,     4,
       4,     4,     4,     4,     4,     4,     4,   569,     4,     4,
     235,     4,     4,     4,   237,   490,     4,   237,   237,   237,
       4,   514,     4,     4,   426,   237,     4,   235,     4,   235,
     235,     4,     4,   684,     4,   235,   703,     4,     7,   234,
       7,     7,     7,     7,     5,   234,   200,   201,   202,   203,
     237,   300,   234,   234,     5,     5,     5,   234,   234,    95,
      96,    97,    98,   309,     5,   256,   258,   234,     5,     5,
       5,     7,     5,     5,     5,     7,     7,     7,     7,     5,
       7,     7,   234,   234,     5,     7,     5,   265,     5,     5,
     234,   234,   234,   265,   265,   265,   234,     7,   234,   234,
     234,   265,   265,   265,   265,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   265,   234,   258,   234,   234,
     197,   198,   695,   199,     5,   254,   277,   702,   335,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    42,    43,    44,    45,    46,    47,
     269,   353,   354,   355,   357,   359,   361,   363,   364,   366,
     367,   368,   369,   370,   371,   372,   373,   374,   377,   378,
     379,   380,   382,   384,   386,   353,     7,   349,   350,   351,
       7,   443,   444,   445,     7,   482,   483,   484,     7,   506,
     507,   508,     7,   472,   473,   474,   137,   234,   398,   399,
     400,   401,   263,   138,   140,   400,   404,   405,   406,   407,
     122,   123,   390,   391,   392,   394,     7,   591,   592,     7,
     561,   562,   563,     7,   419,   420,   421,   146,   147,   148,
     149,   150,   151,   433,   434,   435,   436,   437,   438,   439,
     440,    24,   156,   157,   158,   159,   269,   366,   538,   540,
     606,   607,   608,   611,   612,   614,   615,   162,   163,   164,
     269,   412,   413,   414,   415,   416,   538,   540,   167,   171,
     172,   173,   174,   181,   182,   269,   380,   382,   384,   538,
     540,   625,   626,   627,   630,   632,   634,   635,   636,   646,
       7,   621,   622,   623,   185,   186,   187,   234,   538,   540,
     671,   672,   673,   674,   676,   677,   683,     7,   709,   710,
     219,   269,   733,   734,   735,   266,     7,   527,   528,   529,
       7,   544,   545,   546,   570,   588,   349,     8,     8,     8,
     356,   358,   360,   362,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   375,     4,     4,   381,   383,   385,
     387,     3,     8,     8,   352,     6,     3,   446,     6,     3,
     485,     6,     3,   509,     6,     3,   475,     6,     3,     3,
       6,     6,     3,     6,   393,   395,     3,     8,   593,     3,
       6,   564,     6,     3,   422,     6,     3,     4,     4,     4,
       4,     4,     4,     3,     8,   609,   613,     4,     4,     4,
       3,     8,     4,     4,     4,     3,     8,   628,   631,   633,
       4,   647,     4,   637,     3,     8,   624,     6,     3,     4,
     675,     4,   678,     3,     8,     8,   711,     3,     6,     4,
       3,     8,   234,   267,   268,   530,     6,     3,   547,     6,
       3,     8,     6,     4,     4,     4,     4,   235,   237,   235,
     237,   235,   235,   235,   235,   235,   235,     4,   237,   235,
       4,     4,     4,     4,   354,   353,   351,   449,   445,   488,
     484,   512,   508,   269,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   295,   296,   297,
     298,   301,   303,   305,   306,   307,   310,   311,   312,   313,
     314,   316,   318,   324,   326,   364,   441,   453,   455,   457,
     459,   461,   463,   465,   466,   467,   469,   476,   477,   504,
     538,   540,   586,   474,   399,   405,     4,     4,   391,   127,
     128,   129,   130,   269,   281,   282,   283,   284,   285,   286,
     364,   504,   538,   540,   594,   595,   596,   597,   598,   600,
     602,   603,   592,   567,   563,   425,   421,   235,   235,   235,
     235,   235,   235,   434,     4,     4,   235,   235,   235,   607,
     237,   235,   235,   413,     4,     4,     4,   235,     4,   237,
       4,   626,   625,   623,   237,     4,   235,     4,   672,   210,
     212,   213,   269,   364,   538,   540,   712,   713,   714,   715,
     717,   710,   237,   734,     6,     3,   533,   529,   550,   546,
     234,   234,   234,   234,    39,    40,    41,   376,   234,   234,
     234,   234,     8,     8,     8,     8,     3,     8,   234,   234,
     599,   601,     4,     4,     8,     3,     8,     8,   153,   154,
     155,   610,   234,   168,   169,   170,   629,   234,   234,     7,
       5,     8,   234,   254,   718,     4,   716,     3,     8,   234,
       8,     8,   477,     4,     4,   237,   237,   596,    24,   176,
     177,   178,   269,   538,   540,   648,   649,   650,   653,   655,
     657,     7,   638,   639,   640,     4,   235,     4,   713,   234,
     234,   651,   654,   656,   658,     3,     8,   641,     6,     3,
       5,   234,     4,     4,     4,     4,   649,   183,   269,   364,
     538,   540,   642,   643,   644,   640,     7,   719,   720,   175,
     652,   234,   234,     5,   645,     3,     8,   721,     3,     6,
       7,   659,   660,   661,     4,   643,   211,   214,   215,   216,
     217,   722,   723,   724,   726,   727,   728,   729,   720,   662,
       6,     3,   234,   725,     4,     4,     4,   730,     3,     8,
     179,   180,   269,   357,   359,   538,   540,   663,   664,   665,
     667,   661,     4,   237,   235,   235,     4,   723,   666,   668,
       3,     8,   234,   234,     4,     4,   664,   234,   234
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   238,   240,   239,   241,   239,   242,   239,   243,   239,
     244,   239,   245,   239,   246,   239,   247,   239,   248,   239,
     249,   239,   250,   239,   251,   239,   252,   239,   253,   239,
     254,   254,   254,   254,   254,   254,   254,   255,   257,   256,
     258,   259,   259,   260,   260,   260,   262,   261,   263,   263,
     264,   264,   264,   266,   265,   267,   267,   268,   268,   268,
     269,   271,   270,   273,   272,   272,   274,   276,   275,   277,
     277,   277,   278,   278,   278,   278,   278,   278,   278,   278,
     278,   278,   278,   278,   278,   278,   278,   278,   278,   278,
     278,   278,   278,   278,   278,   278,   278,   278,   278,   278,
     278,   278,   278,   278,   278,   278,   278,   278,   278,   278,
     278,   278,   278,   278,   278,   278,   278,   278,   278,   278,
     278,   278,   278,   278,   278,   278,   278,   278,   278,   278,
     278,   278,   278,   278,   278,   278,   278,   278,   278,   278,
     278,   278,   278,   278,   280,   279,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   299,   298,   300,   300,   300,   300,   300,
     302,   301,   304,   303,   305,   306,   308,   307,   309,   309,
     309,   309,   310,   311,   312,   313,   315,   314,   317,   316,
     318,   319,   320,   322,   321,   323,   325,   324,   327,   326,
     328,   329,   330,   332,   331,   334,   333,   335,   335,   335,
     336,   336,   336,   336,   336,   336,   336,   336,   338,   337,
     339,   340,   341,   342,   344,   343,   346,   345,   348,   347,
     349,   349,   350,   350,   350,   352,   351,   353,   353,   353,
     354,   354,   354,   354,   354,   354,   354,   354,   354,   354,
     354,   354,   354,   354,   354,   354,   354,   354,   354,   354,
     354,   354,   354,   356,   355,   358,   357,   360,   359,   362,
     361,   363,   365,   364,   366,   367,   368,   369,   370,   371,
     372,   373,   375,   374,   376,   376,   376,   377,   378,   379,
     381,   380,   383,   382,   385,   384,   387,   386,   389,   388,
     390,   390,   390,   391,   391,   393,   392,   395,   394,   397,
     396,   398,   398,   398,   399,   399,   400,   401,   403,   402,
     404,   404,   404,   405,   405,   405,   406,   407,   409,   408,
     411,   410,   412,   412,   412,   413,   413,   413,   413,   413,
     413,   414,   415,   416,   418,   417,   419,   419,   420,   420,
     420,   422,   421,   424,   423,   425,   425,   425,   425,   426,
     426,   428,   427,   430,   429,   432,   431,   433,   433,   433,
     434,   434,   434,   434,   434,   434,   435,   436,   437,   438,
     439,   440,   442,   441,   443,   443,   444,   444,   444,   446,
     445,   448,   447,   449,   449,   449,   450,   450,   450,   450,
     450,   450,   450,   450,   450,   450,   450,   450,   450,   450,
     450,   450,   450,   450,   450,   450,   450,   450,   450,   450,
     450,   450,   450,   450,   450,   450,   450,   450,   450,   450,
     450,   450,   450,   450,   450,   450,   450,   450,   450,   450,
     450,   450,   450,   450,   450,   450,   450,   452,   451,   454,
     453,   456,   455,   458,   457,   460,   459,   462,   461,   464,
     463,   465,   466,   467,   468,   469,   471,   470,   472,   472,
     473,   473,   473,   475,   474,   476,   476,   476,   477,   477,
     477,   477,   477,   477,   477,   477,   477,   477,   477,   477,
     477,   477,   477,   477,   477,   477,   477,   477,   477,   477,
     477,   477,   477,   477,   477,   477,   477,   477,   477,   477,
     477,   477,   477,   477,   477,   477,   477,   477,   477,   477,
     477,   477,   477,   477,   477,   477,   479,   478,   481,   480,
     482,   482,   483,   483,   483,   485,   484,   487,   486,   488,
     488,   489,   489,   489,   490,   490,   490,   490,   490,   490,
     490,   490,   490,   490,   491,   492,   493,   495,   494,   497,
     496,   499,   498,   500,   502,   501,   503,   505,   504,   506,
     506,   507,   507,   507,   509,   508,   511,   510,   512,   512,
     513,   513,   513,   514,   514,   514,   514,   514,   514,   514,
     514,   514,   514,   514,   515,   517,   516,   518,   519,   520,
     521,   522,   524,   523,   526,   525,   527,   527,   528,   528,
     528,   530,   529,   532,   531,   533,   533,   533,   534,   534,
     534,   534,   534,   534,   534,   534,   534,   534,   536,   535,
     537,   539,   538,   541,   540,   543,   542,   544,   544,   545,
     545,   545,   547,   546,   549,   548,   550,   550,   550,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   553,   552,   554,   556,   555,   557,   558,
     560,   559,   561,   561,   562,   562,   562,   564,   563,   566,
     565,   567,   567,   568,   568,   568,   569,   569,   569,   569,
     569,   569,   569,   569,   569,   569,   569,   569,   571,   570,
     573,   572,   575,   574,   577,   576,   579,   578,   581,   580,
     583,   582,   585,   584,   587,   586,   588,   590,   589,   591,
     591,   591,   593,   592,   594,   594,   595,   595,   595,   596,
     596,   596,   596,   596,   596,   596,   596,   596,   596,   596,
     596,   596,   596,   596,   597,   599,   598,   601,   600,   602,
     603,   605,   604,   606,   606,   606,   607,   607,   607,   607,
     607,   607,   607,   607,   607,   609,   608,   610,   610,   610,
     611,   613,   612,   614,   615,   616,   618,   617,   620,   619,
     621,   621,   622,   622,   622,   624,   623,   625,   625,   625,
     626,   626,   626,   626,   626,   626,   626,   626,   626,   626,
     626,   626,   626,   628,   627,   629,   629,   629,   631,   630,
     633,   632,   634,   635,   637,   636,   638,   638,   639,   639,
     639,   641,   640,   642,   642,   642,   643,   643,   643,   643,
     643,   645,   644,   647,   646,   648,   648,   648,   649,   649,
     649,   649,   649,   649,   649,   651,   650,   652,   654,   653,
     656,   655,   658,   657,   659,   659,   660,   660,   660,   662,
     661,   663,   663,   663,   664,   664,   664,   664,   664,   664,
     664,   666,   665,   668,   667,   670,   669,   671,   671,   671,
     672,   672,   672,   672,   672,   672,   673,   675,   674,   676,
     678,   677,   680,   679,   682,   681,   683,   683,   683,   684,
     684,   684,   684,   684,   684,   684,   684,   684,   684,   684,
     685,   687,   686,   688,   690,   689,   691,   692,   694,   693,
     695,   695,   697,   696,   699,   698,   701,   700,   702,   702,
     702,   703,   703,   705,   704,   706,   708,   707,   709,   709,
     709,   711,   710,   712,   712,   712,   713,   713,   713,   713,
     713,   713,   713,   714,   716,   715,   718,   717,   719,   719,
     719,   721,   720,   722,   722,   722,   723,   723,   723,   723,
     723,   725,   724,   726,   727,   728,   730,   729,   732,   731,
     733,   733,   733,   734,   734,   735
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
       1,     1,     1,     1,     0,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     0,     4,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     3,     3,     0,     4,     1,     1,
       1,     1,     3,     3,     3,     3,     0,     4,     0,     4,
       3,     3,     3,     0,     4,     3,     0,     4,     0,     4,
       3,     3,     3,     0,     6,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     3,     3,     3,     0,     6,     0,     6,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     3,     3,     3,     3,
       3,     3,     0,     4,     1,     1,     1,     3,     3,     3,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     3,     2,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     1,     0,     6,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     1,     3,     2,     1,     1,
       1,     0,     4,     0,     4,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     3,     3,     3,     3,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     4,     0,     4,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     0,     4,     3,     3,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     0,     1,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     1,     0,     6,     1,
       3,     2,     0,     4,     0,     1,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     3,
       3,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       3,     0,     4,     3,     3,     3,     0,     6,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     0,     4,
       0,     4,     3,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     0,     4,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     0,     4,
       0,     4,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     3,
       0,     4,     0,     6,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     3,     0,     4,     3,     3,     0,     4,
       1,     1,     0,     4,     0,     6,     0,     4,     1,     3,
       2,     1,     1,     0,     6,     3,     0,     6,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     3,     0,     4,     0,     6,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     0,     4,     3,     3,     3,     0,     4,     0,     6,
       1,     3,     2,     1,     1,     3
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
  "\"ddns-ttl-percent\"", "\"ddns-ttl\"", "\"ddns-ttl-min\"",
  "\"ddns-ttl-mix\"", "\"store-extended-info\"", "\"subnet6\"",
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
  "\"http-headers\"", "\"value\"", "\"dhcp-queue-control\"",
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
  "ddns_conflict_resolution_mode_value", "ddns_ttl_percent", "ddns_ttl",
  "ddns_ttl_min", "ddns_ttl_max", "hostname_char_set", "$@26",
  "hostname_char_replacement", "$@27", "store_extended_info",
  "statistic_default_sample_count", "statistic_default_sample_age",
  "server_tag", "$@28", "parked_packet_limit", "allocator", "$@29",
  "pd_allocator", "$@30", "early_global_reservations_lookup",
  "ip_reservations_unique", "reservations_lookup_first",
  "interfaces_config", "$@31", "sub_interfaces6", "$@32",
  "interfaces_config_params", "interfaces_config_param", "interfaces_list",
  "$@33", "re_detect", "service_sockets_require_all",
  "service_sockets_retry_wait_time", "service_sockets_max_retries",
  "lease_database", "$@34", "hosts_database", "$@35", "hosts_databases",
  "$@36", "database_list", "not_empty_database_list", "database", "$@37",
  "database_map_params", "database_map_param", "database_type", "$@38",
  "user", "$@39", "password", "$@40", "host", "$@41", "port", "name",
  "$@42", "persist", "lfc_interval", "readonly", "connect_timeout",
  "read_timeout", "write_timeout", "tcp_user_timeout",
  "reconnect_wait_time", "on_fail", "$@43", "on_fail_mode",
  "retry_on_startup", "max_row_errors", "max_reconnect_tries",
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
  "$@67", "network_client_classes", "$@68", "require_client_classes",
  "$@69", "evaluate_additional_classes", "$@70", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "id",
  "rapid_commit", "shared_networks", "$@71", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@72",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@73", "sub_option_def_list", "$@74", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@75",
  "sub_option_def", "$@76", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@77",
  "option_def_record_types", "$@78", "space", "$@79", "option_def_space",
  "option_def_encapsulate", "$@80", "option_def_array", "option_data_list",
  "$@81", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@82", "sub_option_data", "$@83",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@84",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "option_data_never_send",
  "option_data_client_classes", "$@85", "pools_list", "$@86",
  "pools_list_content", "not_empty_pools_list", "pool_list_entry", "$@87",
  "sub_pool6", "$@88", "pool_params", "pool_param", "pool_entry", "$@89",
  "pool_id", "user_context", "$@90", "comment", "$@91", "pd_pools_list",
  "$@92", "pd_pools_list_content", "not_empty_pd_pools_list",
  "pd_pool_entry", "$@93", "sub_pd_pool", "$@94", "pd_pool_params",
  "pd_pool_param", "pd_prefix", "$@95", "pd_prefix_len", "excluded_prefix",
  "$@96", "excluded_prefix_len", "pd_delegated_len", "reservations",
  "$@97", "reservations_list", "not_empty_reservations_list",
  "reservation", "$@98", "sub_reservation", "$@99", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@100", "prefixes", "$@101", "excluded_prefixes", "$@102", "duid",
  "$@103", "hw_address", "$@104", "hostname", "$@105", "flex_id_value",
  "$@106", "reservation_client_classes", "$@107", "relay", "$@108",
  "relay_map", "client_classes", "$@109", "client_classes_list",
  "client_class_entry", "$@110", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@111",
  "client_class_template_test", "$@112", "only_if_required",
  "only_in_additional_list", "server_id", "$@113", "server_id_params",
  "server_id_param", "server_id_type", "$@114", "duid_type", "htype",
  "identifier", "$@115", "time", "enterprise_id", "dhcp4o6_port",
  "control_socket", "$@116", "control_sockets", "$@117",
  "control_socket_list", "not_empty_control_socket_list",
  "control_socket_entry", "$@118", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@119",
  "control_socket_type_value", "control_socket_name", "$@120",
  "control_socket_address", "$@121", "control_socket_port",
  "cert_required", "http_headers", "$@122", "http_header_list",
  "not_empty_http_header_list", "http_header", "$@123",
  "http_header_params", "http_header_param", "header_value", "$@124",
  "authentication", "$@125", "auth_params", "auth_param", "auth_type",
  "$@126", "auth_type_value", "realm", "$@127", "directory", "$@128",
  "clients", "$@129", "clients_list", "not_empty_clients_list",
  "basic_auth", "$@130", "clients_params", "clients_param", "user_file",
  "$@131", "password_file", "$@132", "dhcp_queue_control", "$@133",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@134", "capacity", "arbitrary_map_entry", "$@135",
  "dhcp_ddns", "$@136", "sub_dhcp_ddns", "$@137", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@138", "server_port",
  "sender_ip", "$@139", "sender_port", "max_queue_size", "ncr_protocol",
  "$@140", "ncr_protocol_value", "ncr_format", "$@141", "config_control",
  "$@142", "sub_config_control", "$@143", "config_control_params",
  "config_control_param", "config_databases", "$@144",
  "config_fetch_wait_time", "loggers", "$@145", "loggers_entries",
  "logger_entry", "$@146", "logger_params", "logger_param", "debuglevel",
  "severity", "$@147", "output_options_list", "$@148",
  "output_options_list_content", "output_entry", "$@149",
  "output_params_list", "output_params", "output", "$@150", "flush",
  "maxsize", "maxver", "pattern", "$@151", "compatibility", "$@152",
  "compatibility_params", "compatibility_param", "lenient_option_parsing", YY_NULLPTR
  };
#endif


#if PARSER6_DEBUG
  const short
  Dhcp6Parser::yyrline_[] =
  {
       0,   332,   332,   332,   333,   333,   334,   334,   335,   335,
     336,   336,   337,   337,   338,   338,   339,   339,   340,   340,
     341,   341,   342,   342,   343,   343,   344,   344,   345,   345,
     353,   354,   355,   356,   357,   358,   359,   362,   367,   367,
     378,   381,   382,   385,   390,   396,   401,   401,   408,   409,
     412,   416,   420,   426,   426,   433,   434,   437,   441,   445,
     455,   464,   464,   479,   479,   493,   496,   502,   502,   511,
     512,   513,   520,   521,   522,   523,   524,   525,   526,   527,
     528,   529,   530,   531,   532,   533,   534,   535,   536,   537,
     538,   539,   540,   541,   542,   543,   544,   545,   546,   547,
     548,   549,   550,   551,   552,   553,   554,   555,   556,   557,
     558,   559,   560,   561,   562,   563,   564,   565,   566,   567,
     568,   569,   570,   571,   572,   573,   574,   575,   576,   577,
     578,   579,   580,   581,   582,   583,   584,   585,   586,   587,
     588,   589,   590,   591,   594,   594,   603,   609,   615,   621,
     627,   633,   639,   645,   651,   657,   663,   669,   675,   681,
     687,   693,   699,   705,   705,   714,   717,   720,   723,   726,
     732,   732,   741,   741,   750,   759,   769,   769,   778,   781,
     784,   787,   792,   798,   804,   810,   816,   816,   825,   825,
     834,   840,   846,   852,   852,   861,   867,   867,   876,   876,
     885,   891,   897,   903,   903,   915,   915,   924,   925,   926,
     931,   932,   933,   934,   935,   936,   937,   938,   941,   941,
     952,   958,   964,   970,   976,   976,   989,   989,  1002,  1002,
    1013,  1014,  1017,  1018,  1019,  1024,  1024,  1034,  1035,  1036,
    1041,  1042,  1043,  1044,  1045,  1046,  1047,  1048,  1049,  1050,
    1051,  1052,  1053,  1054,  1055,  1056,  1057,  1058,  1059,  1060,
    1061,  1062,  1063,  1066,  1066,  1075,  1075,  1084,  1084,  1093,
    1093,  1102,  1108,  1108,  1117,  1123,  1129,  1135,  1141,  1147,
    1153,  1159,  1165,  1165,  1173,  1174,  1175,  1178,  1184,  1190,
    1196,  1196,  1205,  1205,  1214,  1214,  1223,  1223,  1232,  1232,
    1243,  1244,  1245,  1250,  1251,  1254,  1254,  1273,  1273,  1291,
    1291,  1302,  1303,  1304,  1309,  1310,  1313,  1318,  1323,  1323,
    1334,  1335,  1336,  1341,  1342,  1343,  1346,  1351,  1358,  1358,
    1371,  1371,  1384,  1385,  1386,  1391,  1392,  1393,  1394,  1395,
    1396,  1399,  1405,  1411,  1417,  1417,  1428,  1429,  1432,  1433,
    1434,  1439,  1439,  1449,  1449,  1459,  1460,  1461,  1464,  1467,
    1468,  1471,  1471,  1480,  1480,  1489,  1489,  1501,  1502,  1503,
    1508,  1509,  1510,  1511,  1512,  1513,  1516,  1522,  1528,  1534,
    1540,  1546,  1555,  1555,  1569,  1570,  1573,  1574,  1575,  1584,
    1584,  1610,  1610,  1621,  1622,  1623,  1629,  1630,  1631,  1632,
    1633,  1634,  1635,  1636,  1637,  1638,  1639,  1640,  1641,  1642,
    1643,  1644,  1645,  1646,  1647,  1648,  1649,  1650,  1651,  1652,
    1653,  1654,  1655,  1656,  1657,  1658,  1659,  1660,  1661,  1662,
    1663,  1664,  1665,  1666,  1667,  1668,  1669,  1670,  1671,  1672,
    1673,  1674,  1675,  1676,  1677,  1678,  1679,  1682,  1682,  1691,
    1691,  1700,  1700,  1709,  1709,  1719,  1719,  1731,  1731,  1742,
    1742,  1753,  1759,  1765,  1771,  1777,  1785,  1785,  1797,  1798,
    1802,  1803,  1804,  1809,  1809,  1817,  1818,  1819,  1824,  1825,
    1826,  1827,  1828,  1829,  1830,  1831,  1832,  1833,  1834,  1835,
    1836,  1837,  1838,  1839,  1840,  1841,  1842,  1843,  1844,  1845,
    1846,  1847,  1848,  1849,  1850,  1851,  1852,  1853,  1854,  1855,
    1856,  1857,  1858,  1859,  1860,  1861,  1862,  1863,  1864,  1865,
    1866,  1867,  1868,  1869,  1870,  1871,  1878,  1878,  1892,  1892,
    1901,  1902,  1905,  1906,  1907,  1914,  1914,  1929,  1929,  1943,
    1944,  1947,  1948,  1949,  1954,  1955,  1956,  1957,  1958,  1959,
    1960,  1961,  1962,  1963,  1966,  1968,  1974,  1976,  1976,  1985,
    1985,  1994,  1994,  2003,  2005,  2005,  2014,  2024,  2024,  2037,
    2038,  2043,  2044,  2045,  2052,  2052,  2064,  2064,  2076,  2077,
    2082,  2083,  2084,  2091,  2092,  2093,  2094,  2095,  2096,  2097,
    2098,  2099,  2100,  2101,  2104,  2106,  2106,  2115,  2117,  2119,
    2125,  2131,  2137,  2137,  2151,  2151,  2164,  2165,  2168,  2169,
    2170,  2175,  2175,  2185,  2185,  2195,  2196,  2197,  2202,  2203,
    2204,  2205,  2206,  2207,  2208,  2209,  2210,  2211,  2214,  2214,
    2223,  2229,  2229,  2254,  2254,  2284,  2284,  2297,  2298,  2301,
    2302,  2303,  2308,  2308,  2320,  2320,  2332,  2333,  2334,  2339,
    2340,  2341,  2342,  2343,  2344,  2345,  2346,  2347,  2348,  2349,
    2350,  2351,  2352,  2355,  2355,  2364,  2370,  2370,  2379,  2385,
    2394,  2394,  2405,  2406,  2409,  2410,  2411,  2416,  2416,  2425,
    2425,  2434,  2435,  2438,  2439,  2440,  2446,  2447,  2448,  2449,
    2450,  2451,  2452,  2453,  2454,  2455,  2456,  2457,  2460,  2460,
    2471,  2471,  2482,  2482,  2493,  2493,  2502,  2502,  2511,  2511,
    2520,  2520,  2529,  2529,  2543,  2543,  2554,  2560,  2560,  2571,
    2572,  2573,  2578,  2578,  2588,  2589,  2592,  2593,  2594,  2599,
    2600,  2601,  2602,  2603,  2604,  2605,  2606,  2607,  2608,  2609,
    2610,  2611,  2612,  2613,  2616,  2618,  2618,  2627,  2627,  2637,
    2643,  2652,  2652,  2665,  2666,  2667,  2672,  2673,  2674,  2675,
    2676,  2677,  2678,  2679,  2680,  2683,  2683,  2691,  2692,  2693,
    2696,  2702,  2702,  2711,  2717,  2725,  2733,  2733,  2745,  2745,
    2757,  2758,  2761,  2762,  2763,  2768,  2768,  2776,  2777,  2778,
    2783,  2784,  2785,  2786,  2787,  2788,  2789,  2790,  2791,  2792,
    2793,  2794,  2795,  2798,  2798,  2807,  2808,  2809,  2812,  2812,
    2822,  2822,  2832,  2838,  2844,  2844,  2855,  2856,  2859,  2860,
    2861,  2866,  2866,  2874,  2875,  2876,  2881,  2882,  2883,  2884,
    2885,  2888,  2888,  2899,  2899,  2912,  2913,  2914,  2919,  2920,
    2921,  2922,  2923,  2924,  2925,  2928,  2928,  2936,  2939,  2939,
    2948,  2948,  2957,  2957,  2968,  2969,  2972,  2973,  2974,  2979,
    2979,  2987,  2988,  2989,  2994,  2995,  2996,  2997,  2998,  2999,
    3000,  3003,  3003,  3012,  3012,  3023,  3023,  3036,  3037,  3038,
    3043,  3044,  3045,  3046,  3047,  3048,  3051,  3057,  3057,  3066,
    3072,  3072,  3082,  3082,  3095,  3095,  3105,  3106,  3107,  3112,
    3113,  3114,  3115,  3116,  3117,  3118,  3119,  3120,  3121,  3122,
    3125,  3131,  3131,  3140,  3146,  3146,  3155,  3161,  3167,  3167,
    3176,  3177,  3180,  3180,  3191,  3191,  3203,  3203,  3213,  3214,
    3215,  3221,  3222,  3225,  3225,  3236,  3244,  3244,  3257,  3258,
    3259,  3265,  3265,  3273,  3274,  3275,  3280,  3281,  3282,  3283,
    3284,  3285,  3286,  3289,  3295,  3295,  3304,  3304,  3315,  3316,
    3317,  3322,  3322,  3330,  3331,  3332,  3337,  3338,  3339,  3340,
    3341,  3344,  3344,  3353,  3359,  3365,  3371,  3371,  3380,  3380,
    3391,  3392,  3393,  3398,  3399,  3402
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
#line 7032 "dhcp6_parser.cc"

#line 3408 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
