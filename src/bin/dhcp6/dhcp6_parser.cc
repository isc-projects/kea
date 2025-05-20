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
    ctx.warning(yystack_[2].location, "data-directory is deprecated and will be ignored");
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1152 "dhcp6_parser.cc"
    break;

  case 146: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 604 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1162 "dhcp6_parser.cc"
    break;

  case 147: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 610 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1172 "dhcp6_parser.cc"
    break;

  case 148: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 616 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1182 "dhcp6_parser.cc"
    break;

  case 149: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 622 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1192 "dhcp6_parser.cc"
    break;

  case 150: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 628 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1202 "dhcp6_parser.cc"
    break;

  case 151: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 634 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1212 "dhcp6_parser.cc"
    break;

  case 152: // renew_timer: "renew-timer" ":" "integer"
#line 640 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1222 "dhcp6_parser.cc"
    break;

  case 153: // rebind_timer: "rebind-timer" ":" "integer"
#line 646 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1232 "dhcp6_parser.cc"
    break;

  case 154: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 652 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1242 "dhcp6_parser.cc"
    break;

  case 155: // t1_percent: "t1-percent" ":" "floating point"
#line 658 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1252 "dhcp6_parser.cc"
    break;

  case 156: // t2_percent: "t2-percent" ":" "floating point"
#line 664 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1262 "dhcp6_parser.cc"
    break;

  case 157: // cache_threshold: "cache-threshold" ":" "floating point"
#line 670 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1272 "dhcp6_parser.cc"
    break;

  case 158: // cache_max_age: "cache-max-age" ":" "integer"
#line 676 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1282 "dhcp6_parser.cc"
    break;

  case 159: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 682 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1292 "dhcp6_parser.cc"
    break;

  case 160: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 688 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1302 "dhcp6_parser.cc"
    break;

  case 161: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 694 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1312 "dhcp6_parser.cc"
    break;

  case 162: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 700 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1322 "dhcp6_parser.cc"
    break;

  case 163: // $@22: %empty
#line 706 "dhcp6_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1331 "dhcp6_parser.cc"
    break;

  case 164: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 709 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1340 "dhcp6_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "when-present"
#line 715 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1348 "dhcp6_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "never"
#line 718 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1356 "dhcp6_parser.cc"
    break;

  case 167: // ddns_replace_client_name_value: "always"
#line 721 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1364 "dhcp6_parser.cc"
    break;

  case 168: // ddns_replace_client_name_value: "when-not-present"
#line 724 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1372 "dhcp6_parser.cc"
    break;

  case 169: // ddns_replace_client_name_value: "boolean"
#line 727 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1381 "dhcp6_parser.cc"
    break;

  case 170: // $@23: %empty
#line 733 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1390 "dhcp6_parser.cc"
    break;

  case 171: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 736 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1400 "dhcp6_parser.cc"
    break;

  case 172: // $@24: %empty
#line 742 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1409 "dhcp6_parser.cc"
    break;

  case 173: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 745 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1419 "dhcp6_parser.cc"
    break;

  case 174: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 751 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1429 "dhcp6_parser.cc"
    break;

  case 175: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 760 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.warning(yystack_[1].location, "ddns-use-conflict-resolution is deprecated. "
             "Substituting ddns-conflict-resolution-mode");
    ElementPtr mode(new StringElement(b->boolValue() ? "check-with-dhcid"
                                      : "no-check-with-dhcid"));
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", mode);
}
#line 1443 "dhcp6_parser.cc"
    break;

  case 176: // $@25: %empty
#line 770 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1452 "dhcp6_parser.cc"
    break;

  case 177: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 773 "dhcp6_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1461 "dhcp6_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 779 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1469 "dhcp6_parser.cc"
    break;

  case 179: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 782 "dhcp6_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1477 "dhcp6_parser.cc"
    break;

  case 180: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 785 "dhcp6_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1485 "dhcp6_parser.cc"
    break;

  case 181: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 788 "dhcp6_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1493 "dhcp6_parser.cc"
    break;

  case 182: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 793 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1503 "dhcp6_parser.cc"
    break;

  case 183: // ddns_ttl: "ddns-ttl" ":" "integer"
#line 799 "dhcp6_parser.yy"
                                 {
    ctx.unique("ddns-ttl", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl", ttl);
}
#line 1513 "dhcp6_parser.cc"
    break;

  case 184: // ddns_ttl_min: "ddns-ttl-min" ":" "integer"
#line 805 "dhcp6_parser.yy"
                                         {
    ctx.unique("ddns-ttl-min", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-min", ttl);
}
#line 1523 "dhcp6_parser.cc"
    break;

  case 185: // ddns_ttl_max: "ddns-ttl-mix" ":" "integer"
#line 811 "dhcp6_parser.yy"
                                         {
    ctx.unique("ddns-ttl-max", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-max", ttl);
}
#line 1533 "dhcp6_parser.cc"
    break;

  case 186: // $@26: %empty
#line 817 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1542 "dhcp6_parser.cc"
    break;

  case 187: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 820 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1552 "dhcp6_parser.cc"
    break;

  case 188: // $@27: %empty
#line 826 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1561 "dhcp6_parser.cc"
    break;

  case 189: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 829 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1571 "dhcp6_parser.cc"
    break;

  case 190: // store_extended_info: "store-extended-info" ":" "boolean"
#line 835 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1581 "dhcp6_parser.cc"
    break;

  case 191: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 841 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1591 "dhcp6_parser.cc"
    break;

  case 192: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 847 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1601 "dhcp6_parser.cc"
    break;

  case 193: // $@28: %empty
#line 853 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1610 "dhcp6_parser.cc"
    break;

  case 194: // server_tag: "server-tag" $@28 ":" "constant string"
#line 856 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1620 "dhcp6_parser.cc"
    break;

  case 195: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 862 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1630 "dhcp6_parser.cc"
    break;

  case 196: // $@29: %empty
#line 868 "dhcp6_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1639 "dhcp6_parser.cc"
    break;

  case 197: // allocator: "allocator" $@29 ":" "constant string"
#line 871 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1649 "dhcp6_parser.cc"
    break;

  case 198: // $@30: %empty
#line 877 "dhcp6_parser.yy"
                           {
    ctx.unique("pd-allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1658 "dhcp6_parser.cc"
    break;

  case 199: // pd_allocator: "pd-allocator" $@30 ":" "constant string"
#line 880 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-allocator", al);
    ctx.leave();
}
#line 1668 "dhcp6_parser.cc"
    break;

  case 200: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 886 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1678 "dhcp6_parser.cc"
    break;

  case 201: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 892 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1688 "dhcp6_parser.cc"
    break;

  case 202: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 898 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1698 "dhcp6_parser.cc"
    break;

  case 203: // $@31: %empty
#line 904 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1710 "dhcp6_parser.cc"
    break;

  case 204: // interfaces_config: "interfaces-config" $@31 ":" "{" interfaces_config_params "}"
#line 910 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1720 "dhcp6_parser.cc"
    break;

  case 205: // $@32: %empty
#line 916 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1730 "dhcp6_parser.cc"
    break;

  case 206: // sub_interfaces6: "{" $@32 interfaces_config_params "}"
#line 920 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1739 "dhcp6_parser.cc"
    break;

  case 209: // interfaces_config_params: interfaces_config_params ","
#line 927 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1747 "dhcp6_parser.cc"
    break;

  case 218: // $@33: %empty
#line 942 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1759 "dhcp6_parser.cc"
    break;

  case 219: // interfaces_list: "interfaces" $@33 ":" list_strings
#line 948 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1768 "dhcp6_parser.cc"
    break;

  case 220: // re_detect: "re-detect" ":" "boolean"
#line 953 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1778 "dhcp6_parser.cc"
    break;

  case 221: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 959 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1788 "dhcp6_parser.cc"
    break;

  case 222: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 965 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1798 "dhcp6_parser.cc"
    break;

  case 223: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 971 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1808 "dhcp6_parser.cc"
    break;

  case 224: // $@34: %empty
#line 977 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1820 "dhcp6_parser.cc"
    break;

  case 225: // lease_database: "lease-database" $@34 ":" "{" database_map_params "}"
#line 983 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1831 "dhcp6_parser.cc"
    break;

  case 226: // $@35: %empty
#line 990 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1843 "dhcp6_parser.cc"
    break;

  case 227: // hosts_database: "hosts-database" $@35 ":" "{" database_map_params "}"
#line 996 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1854 "dhcp6_parser.cc"
    break;

  case 228: // $@36: %empty
#line 1003 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1866 "dhcp6_parser.cc"
    break;

  case 229: // hosts_databases: "hosts-databases" $@36 ":" "[" database_list "]"
#line 1009 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1875 "dhcp6_parser.cc"
    break;

  case 234: // not_empty_database_list: not_empty_database_list ","
#line 1020 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1883 "dhcp6_parser.cc"
    break;

  case 235: // $@37: %empty
#line 1025 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1893 "dhcp6_parser.cc"
    break;

  case 236: // database: "{" $@37 database_map_params "}"
#line 1029 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1903 "dhcp6_parser.cc"
    break;

  case 239: // database_map_params: database_map_params ","
#line 1037 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1911 "dhcp6_parser.cc"
    break;

  case 263: // $@38: %empty
#line 1067 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1920 "dhcp6_parser.cc"
    break;

  case 264: // database_type: "type" $@38 ":" "constant string"
#line 1070 "dhcp6_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 1930 "dhcp6_parser.cc"
    break;

  case 265: // $@39: %empty
#line 1076 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1939 "dhcp6_parser.cc"
    break;

  case 266: // user: "user" $@39 ":" "constant string"
#line 1079 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1949 "dhcp6_parser.cc"
    break;

  case 267: // $@40: %empty
#line 1085 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1958 "dhcp6_parser.cc"
    break;

  case 268: // password: "password" $@40 ":" "constant string"
#line 1088 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1968 "dhcp6_parser.cc"
    break;

  case 269: // $@41: %empty
#line 1094 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1977 "dhcp6_parser.cc"
    break;

  case 270: // host: "host" $@41 ":" "constant string"
#line 1097 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1987 "dhcp6_parser.cc"
    break;

  case 271: // port: "port" ":" "integer"
#line 1103 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1997 "dhcp6_parser.cc"
    break;

  case 272: // $@42: %empty
#line 1109 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2006 "dhcp6_parser.cc"
    break;

  case 273: // name: "name" $@42 ":" "constant string"
#line 1112 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2016 "dhcp6_parser.cc"
    break;

  case 274: // persist: "persist" ":" "boolean"
#line 1118 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2026 "dhcp6_parser.cc"
    break;

  case 275: // lfc_interval: "lfc-interval" ":" "integer"
#line 1124 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2036 "dhcp6_parser.cc"
    break;

  case 276: // readonly: "readonly" ":" "boolean"
#line 1130 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2046 "dhcp6_parser.cc"
    break;

  case 277: // connect_timeout: "connect-timeout" ":" "integer"
#line 1136 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2056 "dhcp6_parser.cc"
    break;

  case 278: // read_timeout: "read-timeout" ":" "integer"
#line 1142 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2066 "dhcp6_parser.cc"
    break;

  case 279: // write_timeout: "write-timeout" ":" "integer"
#line 1148 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2076 "dhcp6_parser.cc"
    break;

  case 280: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1154 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2086 "dhcp6_parser.cc"
    break;

  case 281: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1160 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2096 "dhcp6_parser.cc"
    break;

  case 282: // $@43: %empty
#line 1166 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2105 "dhcp6_parser.cc"
    break;

  case 283: // on_fail: "on-fail" $@43 ":" on_fail_mode
#line 1169 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2114 "dhcp6_parser.cc"
    break;

  case 284: // on_fail_mode: "stop-retry-exit"
#line 1174 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2120 "dhcp6_parser.cc"
    break;

  case 285: // on_fail_mode: "serve-retry-exit"
#line 1175 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2126 "dhcp6_parser.cc"
    break;

  case 286: // on_fail_mode: "serve-retry-continue"
#line 1176 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2132 "dhcp6_parser.cc"
    break;

  case 287: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1179 "dhcp6_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2142 "dhcp6_parser.cc"
    break;

  case 288: // max_row_errors: "max-row-errors" ":" "integer"
#line 1185 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2152 "dhcp6_parser.cc"
    break;

  case 289: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1191 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2162 "dhcp6_parser.cc"
    break;

  case 290: // $@44: %empty
#line 1197 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2171 "dhcp6_parser.cc"
    break;

  case 291: // trust_anchor: "trust-anchor" $@44 ":" "constant string"
#line 1200 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2181 "dhcp6_parser.cc"
    break;

  case 292: // $@45: %empty
#line 1206 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2190 "dhcp6_parser.cc"
    break;

  case 293: // cert_file: "cert-file" $@45 ":" "constant string"
#line 1209 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2200 "dhcp6_parser.cc"
    break;

  case 294: // $@46: %empty
#line 1215 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2209 "dhcp6_parser.cc"
    break;

  case 295: // key_file: "key-file" $@46 ":" "constant string"
#line 1218 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2219 "dhcp6_parser.cc"
    break;

  case 296: // $@47: %empty
#line 1224 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2228 "dhcp6_parser.cc"
    break;

  case 297: // cipher_list: "cipher-list" $@47 ":" "constant string"
#line 1227 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2238 "dhcp6_parser.cc"
    break;

  case 298: // $@48: %empty
#line 1233 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2250 "dhcp6_parser.cc"
    break;

  case 299: // sanity_checks: "sanity-checks" $@48 ":" "{" sanity_checks_params "}"
#line 1239 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2259 "dhcp6_parser.cc"
    break;

  case 302: // sanity_checks_params: sanity_checks_params ","
#line 1246 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2267 "dhcp6_parser.cc"
    break;

  case 305: // $@49: %empty
#line 1255 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2276 "dhcp6_parser.cc"
    break;

  case 306: // lease_checks: "lease-checks" $@49 ":" "constant string"
#line 1258 "dhcp6_parser.yy"
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
#line 2296 "dhcp6_parser.cc"
    break;

  case 307: // $@50: %empty
#line 1274 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2305 "dhcp6_parser.cc"
    break;

  case 308: // extended_info_checks: "extended-info-checks" $@50 ":" "constant string"
#line 1277 "dhcp6_parser.yy"
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
#line 2324 "dhcp6_parser.cc"
    break;

  case 309: // $@51: %empty
#line 1292 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2336 "dhcp6_parser.cc"
    break;

  case 310: // mac_sources: "mac-sources" $@51 ":" "[" mac_sources_list "]"
#line 1298 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2345 "dhcp6_parser.cc"
    break;

  case 313: // mac_sources_list: mac_sources_list ","
#line 1305 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2353 "dhcp6_parser.cc"
    break;

  case 316: // duid_id: "duid"
#line 1314 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2362 "dhcp6_parser.cc"
    break;

  case 317: // string_id: "constant string"
#line 1319 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2371 "dhcp6_parser.cc"
    break;

  case 318: // $@52: %empty
#line 1324 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2383 "dhcp6_parser.cc"
    break;

  case 319: // host_reservation_identifiers: "host-reservation-identifiers" $@52 ":" "[" host_reservation_identifiers_list "]"
#line 1330 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2392 "dhcp6_parser.cc"
    break;

  case 322: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1337 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2400 "dhcp6_parser.cc"
    break;

  case 326: // hw_address_id: "hw-address"
#line 1347 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2409 "dhcp6_parser.cc"
    break;

  case 327: // flex_id: "flex-id"
#line 1352 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2418 "dhcp6_parser.cc"
    break;

  case 328: // $@53: %empty
#line 1359 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2430 "dhcp6_parser.cc"
    break;

  case 329: // relay_supplied_options: "relay-supplied-options" $@53 ":" "[" list_content "]"
#line 1365 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2439 "dhcp6_parser.cc"
    break;

  case 330: // $@54: %empty
#line 1372 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2451 "dhcp6_parser.cc"
    break;

  case 331: // dhcp_multi_threading: "multi-threading" $@54 ":" "{" multi_threading_params "}"
#line 1378 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2462 "dhcp6_parser.cc"
    break;

  case 334: // multi_threading_params: multi_threading_params ","
#line 1387 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2470 "dhcp6_parser.cc"
    break;

  case 341: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1400 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2480 "dhcp6_parser.cc"
    break;

  case 342: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1406 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2490 "dhcp6_parser.cc"
    break;

  case 343: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1412 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2500 "dhcp6_parser.cc"
    break;

  case 344: // $@55: %empty
#line 1418 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2512 "dhcp6_parser.cc"
    break;

  case 345: // hooks_libraries: "hooks-libraries" $@55 ":" "[" hooks_libraries_list "]"
#line 1424 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2521 "dhcp6_parser.cc"
    break;

  case 350: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1435 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2529 "dhcp6_parser.cc"
    break;

  case 351: // $@56: %empty
#line 1440 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2539 "dhcp6_parser.cc"
    break;

  case 352: // hooks_library: "{" $@56 hooks_params "}"
#line 1444 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2549 "dhcp6_parser.cc"
    break;

  case 353: // $@57: %empty
#line 1450 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2559 "dhcp6_parser.cc"
    break;

  case 354: // sub_hooks_library: "{" $@57 hooks_params "}"
#line 1454 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2569 "dhcp6_parser.cc"
    break;

  case 357: // hooks_params: hooks_params ","
#line 1462 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2577 "dhcp6_parser.cc"
    break;

  case 361: // $@58: %empty
#line 1472 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2586 "dhcp6_parser.cc"
    break;

  case 362: // library: "library" $@58 ":" "constant string"
#line 1475 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2596 "dhcp6_parser.cc"
    break;

  case 363: // $@59: %empty
#line 1481 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2605 "dhcp6_parser.cc"
    break;

  case 364: // parameters: "parameters" $@59 ":" map_value
#line 1484 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2614 "dhcp6_parser.cc"
    break;

  case 365: // $@60: %empty
#line 1490 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2626 "dhcp6_parser.cc"
    break;

  case 366: // expired_leases_processing: "expired-leases-processing" $@60 ":" "{" expired_leases_params "}"
#line 1496 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2636 "dhcp6_parser.cc"
    break;

  case 369: // expired_leases_params: expired_leases_params ","
#line 1504 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2644 "dhcp6_parser.cc"
    break;

  case 376: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1517 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2654 "dhcp6_parser.cc"
    break;

  case 377: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1523 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2664 "dhcp6_parser.cc"
    break;

  case 378: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1529 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2674 "dhcp6_parser.cc"
    break;

  case 379: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1535 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2684 "dhcp6_parser.cc"
    break;

  case 380: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1541 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2694 "dhcp6_parser.cc"
    break;

  case 381: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1547 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2704 "dhcp6_parser.cc"
    break;

  case 382: // $@61: %empty
#line 1556 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2716 "dhcp6_parser.cc"
    break;

  case 383: // subnet6_list: "subnet6" $@61 ":" "[" subnet6_list_content "]"
#line 1562 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2725 "dhcp6_parser.cc"
    break;

  case 388: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1576 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2733 "dhcp6_parser.cc"
    break;

  case 389: // $@62: %empty
#line 1585 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2743 "dhcp6_parser.cc"
    break;

  case 390: // subnet6: "{" $@62 subnet6_params "}"
#line 1589 "dhcp6_parser.yy"
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
#line 2769 "dhcp6_parser.cc"
    break;

  case 391: // $@63: %empty
#line 1611 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2779 "dhcp6_parser.cc"
    break;

  case 392: // sub_subnet6: "{" $@63 subnet6_params "}"
#line 1615 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2789 "dhcp6_parser.cc"
    break;

  case 395: // subnet6_params: subnet6_params ","
#line 1624 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2797 "dhcp6_parser.cc"
    break;

  case 447: // $@64: %empty
#line 1683 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2806 "dhcp6_parser.cc"
    break;

  case 448: // subnet: "subnet" $@64 ":" "constant string"
#line 1686 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2816 "dhcp6_parser.cc"
    break;

  case 449: // $@65: %empty
#line 1692 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2825 "dhcp6_parser.cc"
    break;

  case 450: // interface: "interface" $@65 ":" "constant string"
#line 1695 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2835 "dhcp6_parser.cc"
    break;

  case 451: // $@66: %empty
#line 1701 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2844 "dhcp6_parser.cc"
    break;

  case 452: // interface_id: "interface-id" $@66 ":" "constant string"
#line 1704 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2854 "dhcp6_parser.cc"
    break;

  case 453: // $@67: %empty
#line 1710 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2863 "dhcp6_parser.cc"
    break;

  case 454: // client_class: "client-class" $@67 ":" "constant string"
#line 1713 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2873 "dhcp6_parser.cc"
    break;

  case 455: // $@68: %empty
#line 1720 "dhcp6_parser.yy"
                                       {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2885 "dhcp6_parser.cc"
    break;

  case 456: // network_client_classes: "client-classes" $@68 ":" list_strings
#line 1726 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2894 "dhcp6_parser.cc"
    break;

  case 457: // $@69: %empty
#line 1732 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2906 "dhcp6_parser.cc"
    break;

  case 458: // require_client_classes: "require-client-classes" $@69 ":" list_strings
#line 1738 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2915 "dhcp6_parser.cc"
    break;

  case 459: // $@70: %empty
#line 1743 "dhcp6_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2927 "dhcp6_parser.cc"
    break;

  case 460: // evaluate_additional_classes: "evaluate-additional-classes" $@70 ":" list_strings
#line 1749 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2936 "dhcp6_parser.cc"
    break;

  case 461: // reservations_global: "reservations-global" ":" "boolean"
#line 1754 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2946 "dhcp6_parser.cc"
    break;

  case 462: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1760 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2956 "dhcp6_parser.cc"
    break;

  case 463: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1766 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2966 "dhcp6_parser.cc"
    break;

  case 464: // id: "id" ":" "integer"
#line 1772 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2976 "dhcp6_parser.cc"
    break;

  case 465: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1778 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2986 "dhcp6_parser.cc"
    break;

  case 466: // $@71: %empty
#line 1786 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2998 "dhcp6_parser.cc"
    break;

  case 467: // shared_networks: "shared-networks" $@71 ":" "[" shared_networks_content "]"
#line 1792 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3007 "dhcp6_parser.cc"
    break;

  case 472: // shared_networks_list: shared_networks_list ","
#line 1805 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3015 "dhcp6_parser.cc"
    break;

  case 473: // $@72: %empty
#line 1810 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3025 "dhcp6_parser.cc"
    break;

  case 474: // shared_network: "{" $@72 shared_network_params "}"
#line 1814 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3033 "dhcp6_parser.cc"
    break;

  case 477: // shared_network_params: shared_network_params ","
#line 1820 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3041 "dhcp6_parser.cc"
    break;

  case 526: // $@73: %empty
#line 1879 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3053 "dhcp6_parser.cc"
    break;

  case 527: // option_def_list: "option-def" $@73 ":" "[" option_def_list_content "]"
#line 1885 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3062 "dhcp6_parser.cc"
    break;

  case 528: // $@74: %empty
#line 1893 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3071 "dhcp6_parser.cc"
    break;

  case 529: // sub_option_def_list: "{" $@74 option_def_list "}"
#line 1896 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 3079 "dhcp6_parser.cc"
    break;

  case 534: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1908 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3087 "dhcp6_parser.cc"
    break;

  case 535: // $@75: %empty
#line 1915 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3097 "dhcp6_parser.cc"
    break;

  case 536: // option_def_entry: "{" $@75 option_def_params "}"
#line 1919 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3109 "dhcp6_parser.cc"
    break;

  case 537: // $@76: %empty
#line 1930 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3119 "dhcp6_parser.cc"
    break;

  case 538: // sub_option_def: "{" $@76 option_def_params "}"
#line 1934 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3131 "dhcp6_parser.cc"
    break;

  case 543: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1950 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3139 "dhcp6_parser.cc"
    break;

  case 555: // code: "code" ":" "integer"
#line 1969 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3149 "dhcp6_parser.cc"
    break;

  case 557: // $@77: %empty
#line 1977 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3158 "dhcp6_parser.cc"
    break;

  case 558: // option_def_type: "type" $@77 ":" "constant string"
#line 1980 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3168 "dhcp6_parser.cc"
    break;

  case 559: // $@78: %empty
#line 1986 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3177 "dhcp6_parser.cc"
    break;

  case 560: // option_def_record_types: "record-types" $@78 ":" "constant string"
#line 1989 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3187 "dhcp6_parser.cc"
    break;

  case 561: // $@79: %empty
#line 1995 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3196 "dhcp6_parser.cc"
    break;

  case 562: // space: "space" $@79 ":" "constant string"
#line 1998 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3206 "dhcp6_parser.cc"
    break;

  case 564: // $@80: %empty
#line 2006 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3215 "dhcp6_parser.cc"
    break;

  case 565: // option_def_encapsulate: "encapsulate" $@80 ":" "constant string"
#line 2009 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3225 "dhcp6_parser.cc"
    break;

  case 566: // option_def_array: "array" ":" "boolean"
#line 2015 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3235 "dhcp6_parser.cc"
    break;

  case 567: // $@81: %empty
#line 2025 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3247 "dhcp6_parser.cc"
    break;

  case 568: // option_data_list: "option-data" $@81 ":" "[" option_data_list_content "]"
#line 2031 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3256 "dhcp6_parser.cc"
    break;

  case 573: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2046 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3264 "dhcp6_parser.cc"
    break;

  case 574: // $@82: %empty
#line 2053 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3274 "dhcp6_parser.cc"
    break;

  case 575: // option_data_entry: "{" $@82 option_data_params "}"
#line 2057 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3283 "dhcp6_parser.cc"
    break;

  case 576: // $@83: %empty
#line 2065 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3293 "dhcp6_parser.cc"
    break;

  case 577: // sub_option_data: "{" $@83 option_data_params "}"
#line 2069 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3302 "dhcp6_parser.cc"
    break;

  case 582: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2085 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3310 "dhcp6_parser.cc"
    break;

  case 595: // $@84: %empty
#line 2107 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3319 "dhcp6_parser.cc"
    break;

  case 596: // option_data_data: "data" $@84 ":" "constant string"
#line 2110 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3329 "dhcp6_parser.cc"
    break;

  case 599: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2120 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3339 "dhcp6_parser.cc"
    break;

  case 600: // option_data_always_send: "always-send" ":" "boolean"
#line 2126 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3349 "dhcp6_parser.cc"
    break;

  case 601: // option_data_never_send: "never-send" ":" "boolean"
#line 2132 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3359 "dhcp6_parser.cc"
    break;

  case 602: // $@85: %empty
#line 2138 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3371 "dhcp6_parser.cc"
    break;

  case 603: // option_data_client_classes: "client-classes" $@85 ":" list_strings
#line 2144 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3380 "dhcp6_parser.cc"
    break;

  case 604: // $@86: %empty
#line 2152 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3392 "dhcp6_parser.cc"
    break;

  case 605: // pools_list: "pools" $@86 ":" "[" pools_list_content "]"
#line 2158 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3401 "dhcp6_parser.cc"
    break;

  case 610: // not_empty_pools_list: not_empty_pools_list ","
#line 2171 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3409 "dhcp6_parser.cc"
    break;

  case 611: // $@87: %empty
#line 2176 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3419 "dhcp6_parser.cc"
    break;

  case 612: // pool_list_entry: "{" $@87 pool_params "}"
#line 2180 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3429 "dhcp6_parser.cc"
    break;

  case 613: // $@88: %empty
#line 2186 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3439 "dhcp6_parser.cc"
    break;

  case 614: // sub_pool6: "{" $@88 pool_params "}"
#line 2190 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3449 "dhcp6_parser.cc"
    break;

  case 617: // pool_params: pool_params ","
#line 2198 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3457 "dhcp6_parser.cc"
    break;

  case 642: // $@89: %empty
#line 2229 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3466 "dhcp6_parser.cc"
    break;

  case 643: // pool_entry: "pool" $@89 ":" "constant string"
#line 2232 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3476 "dhcp6_parser.cc"
    break;

  case 644: // pool_id: "pool-id" ":" "integer"
#line 2238 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3486 "dhcp6_parser.cc"
    break;

  case 645: // $@90: %empty
#line 2244 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3494 "dhcp6_parser.cc"
    break;

  case 646: // user_context: "user-context" $@90 ":" map_value
#line 2246 "dhcp6_parser.yy"
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
#line 3521 "dhcp6_parser.cc"
    break;

  case 647: // $@91: %empty
#line 2269 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3529 "dhcp6_parser.cc"
    break;

  case 648: // comment: "comment" $@91 ":" "constant string"
#line 2271 "dhcp6_parser.yy"
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
#line 3558 "dhcp6_parser.cc"
    break;

  case 649: // $@92: %empty
#line 2299 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3570 "dhcp6_parser.cc"
    break;

  case 650: // pd_pools_list: "pd-pools" $@92 ":" "[" pd_pools_list_content "]"
#line 2305 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3579 "dhcp6_parser.cc"
    break;

  case 655: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2318 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3587 "dhcp6_parser.cc"
    break;

  case 656: // $@93: %empty
#line 2323 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3597 "dhcp6_parser.cc"
    break;

  case 657: // pd_pool_entry: "{" $@93 pd_pool_params "}"
#line 2327 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3609 "dhcp6_parser.cc"
    break;

  case 658: // $@94: %empty
#line 2335 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3619 "dhcp6_parser.cc"
    break;

  case 659: // sub_pd_pool: "{" $@94 pd_pool_params "}"
#line 2339 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3631 "dhcp6_parser.cc"
    break;

  case 662: // pd_pool_params: pd_pool_params ","
#line 2349 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3639 "dhcp6_parser.cc"
    break;

  case 677: // $@95: %empty
#line 2370 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3648 "dhcp6_parser.cc"
    break;

  case 678: // pd_prefix: "prefix" $@95 ":" "constant string"
#line 2373 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3658 "dhcp6_parser.cc"
    break;

  case 679: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2379 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3668 "dhcp6_parser.cc"
    break;

  case 680: // $@96: %empty
#line 2385 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3677 "dhcp6_parser.cc"
    break;

  case 681: // excluded_prefix: "excluded-prefix" $@96 ":" "constant string"
#line 2388 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3687 "dhcp6_parser.cc"
    break;

  case 682: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2394 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3697 "dhcp6_parser.cc"
    break;

  case 683: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2400 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3707 "dhcp6_parser.cc"
    break;

  case 684: // $@97: %empty
#line 2409 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3719 "dhcp6_parser.cc"
    break;

  case 685: // reservations: "reservations" $@97 ":" "[" reservations_list "]"
#line 2415 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3728 "dhcp6_parser.cc"
    break;

  case 690: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2426 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3736 "dhcp6_parser.cc"
    break;

  case 691: // $@98: %empty
#line 2431 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3746 "dhcp6_parser.cc"
    break;

  case 692: // reservation: "{" $@98 reservation_params "}"
#line 2435 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3755 "dhcp6_parser.cc"
    break;

  case 693: // $@99: %empty
#line 2440 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3765 "dhcp6_parser.cc"
    break;

  case 694: // sub_reservation: "{" $@99 reservation_params "}"
#line 2444 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3774 "dhcp6_parser.cc"
    break;

  case 699: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2455 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3782 "dhcp6_parser.cc"
    break;

  case 712: // $@100: %empty
#line 2475 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3794 "dhcp6_parser.cc"
    break;

  case 713: // ip_addresses: "ip-addresses" $@100 ":" list_strings
#line 2481 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3803 "dhcp6_parser.cc"
    break;

  case 714: // $@101: %empty
#line 2486 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3815 "dhcp6_parser.cc"
    break;

  case 715: // prefixes: "prefixes" $@101 ":" list_strings
#line 2492 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3824 "dhcp6_parser.cc"
    break;

  case 716: // $@102: %empty
#line 2497 "dhcp6_parser.yy"
                                     {
    ctx.unique("excluded-prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3836 "dhcp6_parser.cc"
    break;

  case 717: // excluded_prefixes: "excluded-prefixes" $@102 ":" list_strings
#line 2503 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3845 "dhcp6_parser.cc"
    break;

  case 718: // $@103: %empty
#line 2508 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3854 "dhcp6_parser.cc"
    break;

  case 719: // duid: "duid" $@103 ":" "constant string"
#line 2511 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3864 "dhcp6_parser.cc"
    break;

  case 720: // $@104: %empty
#line 2517 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3873 "dhcp6_parser.cc"
    break;

  case 721: // hw_address: "hw-address" $@104 ":" "constant string"
#line 2520 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3883 "dhcp6_parser.cc"
    break;

  case 722: // $@105: %empty
#line 2526 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3892 "dhcp6_parser.cc"
    break;

  case 723: // hostname: "hostname" $@105 ":" "constant string"
#line 2529 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3902 "dhcp6_parser.cc"
    break;

  case 724: // $@106: %empty
#line 2535 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3911 "dhcp6_parser.cc"
    break;

  case 725: // flex_id_value: "flex-id" $@106 ":" "constant string"
#line 2538 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3921 "dhcp6_parser.cc"
    break;

  case 726: // $@107: %empty
#line 2544 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3933 "dhcp6_parser.cc"
    break;

  case 727: // reservation_client_classes: "client-classes" $@107 ":" list_strings
#line 2550 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3942 "dhcp6_parser.cc"
    break;

  case 728: // $@108: %empty
#line 2558 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3954 "dhcp6_parser.cc"
    break;

  case 729: // relay: "relay" $@108 ":" "{" relay_map "}"
#line 2564 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3963 "dhcp6_parser.cc"
    break;

  case 731: // $@109: %empty
#line 2575 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3975 "dhcp6_parser.cc"
    break;

  case 732: // client_classes: "client-classes" $@109 ":" "[" client_classes_list "]"
#line 2581 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3984 "dhcp6_parser.cc"
    break;

  case 735: // client_classes_list: client_classes_list ","
#line 2588 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3992 "dhcp6_parser.cc"
    break;

  case 736: // $@110: %empty
#line 2593 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4002 "dhcp6_parser.cc"
    break;

  case 737: // client_class_entry: "{" $@110 client_class_params "}"
#line 2597 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 4012 "dhcp6_parser.cc"
    break;

  case 742: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2609 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 4020 "dhcp6_parser.cc"
    break;

  case 759: // $@111: %empty
#line 2633 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4029 "dhcp6_parser.cc"
    break;

  case 760: // client_class_test: "test" $@111 ":" "constant string"
#line 2636 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4039 "dhcp6_parser.cc"
    break;

  case 761: // $@112: %empty
#line 2642 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4048 "dhcp6_parser.cc"
    break;

  case 762: // client_class_template_test: "template-test" $@112 ":" "constant string"
#line 2645 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4058 "dhcp6_parser.cc"
    break;

  case 763: // only_if_required: "only-if-required" ":" "boolean"
#line 2652 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4068 "dhcp6_parser.cc"
    break;

  case 764: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2658 "dhcp6_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4078 "dhcp6_parser.cc"
    break;

  case 765: // $@113: %empty
#line 2667 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 4090 "dhcp6_parser.cc"
    break;

  case 766: // server_id: "server-id" $@113 ":" "{" server_id_params "}"
#line 2673 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4101 "dhcp6_parser.cc"
    break;

  case 769: // server_id_params: server_id_params ","
#line 2682 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4109 "dhcp6_parser.cc"
    break;

  case 779: // $@114: %empty
#line 2698 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 4118 "dhcp6_parser.cc"
    break;

  case 780: // server_id_type: "type" $@114 ":" duid_type
#line 2701 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4127 "dhcp6_parser.cc"
    break;

  case 781: // duid_type: "LLT"
#line 2706 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4133 "dhcp6_parser.cc"
    break;

  case 782: // duid_type: "EN"
#line 2707 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4139 "dhcp6_parser.cc"
    break;

  case 783: // duid_type: "LL"
#line 2708 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4145 "dhcp6_parser.cc"
    break;

  case 784: // htype: "htype" ":" "integer"
#line 2711 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4155 "dhcp6_parser.cc"
    break;

  case 785: // $@115: %empty
#line 2717 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4164 "dhcp6_parser.cc"
    break;

  case 786: // identifier: "identifier" $@115 ":" "constant string"
#line 2720 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4174 "dhcp6_parser.cc"
    break;

  case 787: // time: "time" ":" "integer"
#line 2726 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4184 "dhcp6_parser.cc"
    break;

  case 788: // enterprise_id: "enterprise-id" ":" "integer"
#line 2732 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4194 "dhcp6_parser.cc"
    break;

  case 789: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2740 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4204 "dhcp6_parser.cc"
    break;

  case 790: // $@116: %empty
#line 2748 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4217 "dhcp6_parser.cc"
    break;

  case 791: // control_socket: "control-socket" $@116 ":" "{" control_socket_params "}"
#line 2755 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4226 "dhcp6_parser.cc"
    break;

  case 792: // $@117: %empty
#line 2760 "dhcp6_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4239 "dhcp6_parser.cc"
    break;

  case 793: // control_sockets: "control-sockets" $@117 ":" "[" control_socket_list "]"
#line 2767 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4248 "dhcp6_parser.cc"
    break;

  case 798: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2778 "dhcp6_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4256 "dhcp6_parser.cc"
    break;

  case 799: // $@118: %empty
#line 2783 "dhcp6_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4266 "dhcp6_parser.cc"
    break;

  case 800: // control_socket_entry: "{" $@118 control_socket_params "}"
#line 2787 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4274 "dhcp6_parser.cc"
    break;

  case 803: // control_socket_params: control_socket_params ","
#line 2793 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4282 "dhcp6_parser.cc"
    break;

  case 817: // $@119: %empty
#line 2813 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4291 "dhcp6_parser.cc"
    break;

  case 818: // control_socket_type: "socket-type" $@119 ":" control_socket_type_value
#line 2816 "dhcp6_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4300 "dhcp6_parser.cc"
    break;

  case 819: // control_socket_type_value: "unix"
#line 2822 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4306 "dhcp6_parser.cc"
    break;

  case 820: // control_socket_type_value: "http"
#line 2823 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4312 "dhcp6_parser.cc"
    break;

  case 821: // control_socket_type_value: "https"
#line 2824 "dhcp6_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4318 "dhcp6_parser.cc"
    break;

  case 822: // $@120: %empty
#line 2827 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4328 "dhcp6_parser.cc"
    break;

  case 823: // control_socket_name: "socket-name" $@120 ":" "constant string"
#line 2831 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4338 "dhcp6_parser.cc"
    break;

  case 824: // $@121: %empty
#line 2837 "dhcp6_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4348 "dhcp6_parser.cc"
    break;

  case 825: // control_socket_address: "socket-address" $@121 ":" "constant string"
#line 2841 "dhcp6_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4358 "dhcp6_parser.cc"
    break;

  case 826: // control_socket_port: "socket-port" ":" "integer"
#line 2847 "dhcp6_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4368 "dhcp6_parser.cc"
    break;

  case 827: // cert_required: "cert-required" ":" "boolean"
#line 2853 "dhcp6_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4378 "dhcp6_parser.cc"
    break;

  case 828: // $@122: %empty
#line 2859 "dhcp6_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4390 "dhcp6_parser.cc"
    break;

  case 829: // http_headers: "http-headers" $@122 ":" "[" http_header_list "]"
#line 2865 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4399 "dhcp6_parser.cc"
    break;

  case 834: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2876 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4407 "dhcp6_parser.cc"
    break;

  case 835: // $@123: %empty
#line 2881 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4417 "dhcp6_parser.cc"
    break;

  case 836: // http_header: "{" $@123 http_header_params "}"
#line 2885 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4425 "dhcp6_parser.cc"
    break;

  case 839: // http_header_params: http_header_params ","
#line 2891 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4433 "dhcp6_parser.cc"
    break;

  case 845: // $@124: %empty
#line 2903 "dhcp6_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4442 "dhcp6_parser.cc"
    break;

  case 846: // header_value: "value" $@124 ":" "constant string"
#line 2906 "dhcp6_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4452 "dhcp6_parser.cc"
    break;

  case 847: // $@125: %empty
#line 2914 "dhcp6_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4464 "dhcp6_parser.cc"
    break;

  case 848: // authentication: "authentication" $@125 ":" "{" auth_params "}"
#line 2920 "dhcp6_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4475 "dhcp6_parser.cc"
    break;

  case 851: // auth_params: auth_params ","
#line 2929 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4483 "dhcp6_parser.cc"
    break;

  case 859: // $@126: %empty
#line 2943 "dhcp6_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4492 "dhcp6_parser.cc"
    break;

  case 860: // auth_type: "type" $@126 ":" auth_type_value
#line 2946 "dhcp6_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4501 "dhcp6_parser.cc"
    break;

  case 861: // auth_type_value: "basic"
#line 2951 "dhcp6_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4507 "dhcp6_parser.cc"
    break;

  case 862: // $@127: %empty
#line 2954 "dhcp6_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4516 "dhcp6_parser.cc"
    break;

  case 863: // realm: "realm" $@127 ":" "constant string"
#line 2957 "dhcp6_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4526 "dhcp6_parser.cc"
    break;

  case 864: // $@128: %empty
#line 2963 "dhcp6_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4535 "dhcp6_parser.cc"
    break;

  case 865: // directory: "directory" $@128 ":" "constant string"
#line 2966 "dhcp6_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4545 "dhcp6_parser.cc"
    break;

  case 866: // $@129: %empty
#line 2972 "dhcp6_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4557 "dhcp6_parser.cc"
    break;

  case 867: // clients: "clients" $@129 ":" "[" clients_list "]"
#line 2978 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4566 "dhcp6_parser.cc"
    break;

  case 872: // not_empty_clients_list: not_empty_clients_list ","
#line 2989 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4574 "dhcp6_parser.cc"
    break;

  case 873: // $@130: %empty
#line 2994 "dhcp6_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4584 "dhcp6_parser.cc"
    break;

  case 874: // basic_auth: "{" $@130 clients_params "}"
#line 2998 "dhcp6_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4592 "dhcp6_parser.cc"
    break;

  case 877: // clients_params: clients_params ","
#line 3004 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4600 "dhcp6_parser.cc"
    break;

  case 885: // $@131: %empty
#line 3018 "dhcp6_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4609 "dhcp6_parser.cc"
    break;

  case 886: // user_file: "user-file" $@131 ":" "constant string"
#line 3021 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4619 "dhcp6_parser.cc"
    break;

  case 887: // $@132: %empty
#line 3027 "dhcp6_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4628 "dhcp6_parser.cc"
    break;

  case 888: // password_file: "password-file" $@132 ":" "constant string"
#line 3030 "dhcp6_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4638 "dhcp6_parser.cc"
    break;

  case 889: // $@133: %empty
#line 3038 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4650 "dhcp6_parser.cc"
    break;

  case 890: // dhcp_queue_control: "dhcp-queue-control" $@133 ":" "{" queue_control_params "}"
#line 3044 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4661 "dhcp6_parser.cc"
    break;

  case 893: // queue_control_params: queue_control_params ","
#line 3053 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4669 "dhcp6_parser.cc"
    break;

  case 900: // enable_queue: "enable-queue" ":" "boolean"
#line 3066 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4679 "dhcp6_parser.cc"
    break;

  case 901: // $@134: %empty
#line 3072 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4688 "dhcp6_parser.cc"
    break;

  case 902: // queue_type: "queue-type" $@134 ":" "constant string"
#line 3075 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4698 "dhcp6_parser.cc"
    break;

  case 903: // capacity: "capacity" ":" "integer"
#line 3081 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4708 "dhcp6_parser.cc"
    break;

  case 904: // $@135: %empty
#line 3087 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4717 "dhcp6_parser.cc"
    break;

  case 905: // arbitrary_map_entry: "constant string" $@135 ":" value
#line 3090 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4726 "dhcp6_parser.cc"
    break;

  case 906: // $@136: %empty
#line 3097 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4738 "dhcp6_parser.cc"
    break;

  case 907: // dhcp_ddns: "dhcp-ddns" $@136 ":" "{" dhcp_ddns_params "}"
#line 3103 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4749 "dhcp6_parser.cc"
    break;

  case 908: // $@137: %empty
#line 3110 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4759 "dhcp6_parser.cc"
    break;

  case 909: // sub_dhcp_ddns: "{" $@137 dhcp_ddns_params "}"
#line 3114 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4769 "dhcp6_parser.cc"
    break;

  case 912: // dhcp_ddns_params: dhcp_ddns_params ","
#line 3122 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4777 "dhcp6_parser.cc"
    break;

  case 924: // enable_updates: "enable-updates" ":" "boolean"
#line 3140 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4787 "dhcp6_parser.cc"
    break;

  case 925: // $@138: %empty
#line 3146 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4796 "dhcp6_parser.cc"
    break;

  case 926: // server_ip: "server-ip" $@138 ":" "constant string"
#line 3149 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4806 "dhcp6_parser.cc"
    break;

  case 927: // server_port: "server-port" ":" "integer"
#line 3155 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4816 "dhcp6_parser.cc"
    break;

  case 928: // $@139: %empty
#line 3161 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4825 "dhcp6_parser.cc"
    break;

  case 929: // sender_ip: "sender-ip" $@139 ":" "constant string"
#line 3164 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4835 "dhcp6_parser.cc"
    break;

  case 930: // sender_port: "sender-port" ":" "integer"
#line 3170 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4845 "dhcp6_parser.cc"
    break;

  case 931: // max_queue_size: "max-queue-size" ":" "integer"
#line 3176 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4855 "dhcp6_parser.cc"
    break;

  case 932: // $@140: %empty
#line 3182 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4864 "dhcp6_parser.cc"
    break;

  case 933: // ncr_protocol: "ncr-protocol" $@140 ":" ncr_protocol_value
#line 3185 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4873 "dhcp6_parser.cc"
    break;

  case 934: // ncr_protocol_value: "UDP"
#line 3191 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4879 "dhcp6_parser.cc"
    break;

  case 935: // ncr_protocol_value: "TCP"
#line 3192 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4885 "dhcp6_parser.cc"
    break;

  case 936: // $@141: %empty
#line 3195 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4894 "dhcp6_parser.cc"
    break;

  case 937: // ncr_format: "ncr-format" $@141 ":" "JSON"
#line 3198 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4904 "dhcp6_parser.cc"
    break;

  case 938: // $@142: %empty
#line 3206 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4916 "dhcp6_parser.cc"
    break;

  case 939: // config_control: "config-control" $@142 ":" "{" config_control_params "}"
#line 3212 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4926 "dhcp6_parser.cc"
    break;

  case 940: // $@143: %empty
#line 3218 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4936 "dhcp6_parser.cc"
    break;

  case 941: // sub_config_control: "{" $@143 config_control_params "}"
#line 3222 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4945 "dhcp6_parser.cc"
    break;

  case 944: // config_control_params: config_control_params ","
#line 3230 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4953 "dhcp6_parser.cc"
    break;

  case 947: // $@144: %empty
#line 3240 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4965 "dhcp6_parser.cc"
    break;

  case 948: // config_databases: "config-databases" $@144 ":" "[" database_list "]"
#line 3246 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4974 "dhcp6_parser.cc"
    break;

  case 949: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3251 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4984 "dhcp6_parser.cc"
    break;

  case 950: // $@145: %empty
#line 3259 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4996 "dhcp6_parser.cc"
    break;

  case 951: // loggers: "loggers" $@145 ":" "[" loggers_entries "]"
#line 3265 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5005 "dhcp6_parser.cc"
    break;

  case 954: // loggers_entries: loggers_entries ","
#line 3274 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 5013 "dhcp6_parser.cc"
    break;

  case 955: // $@146: %empty
#line 3280 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 5023 "dhcp6_parser.cc"
    break;

  case 956: // logger_entry: "{" $@146 logger_params "}"
#line 3284 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 5031 "dhcp6_parser.cc"
    break;

  case 959: // logger_params: logger_params ","
#line 3290 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 5039 "dhcp6_parser.cc"
    break;

  case 967: // debuglevel: "debuglevel" ":" "integer"
#line 3304 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 5049 "dhcp6_parser.cc"
    break;

  case 968: // $@147: %empty
#line 3310 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5058 "dhcp6_parser.cc"
    break;

  case 969: // severity: "severity" $@147 ":" "constant string"
#line 3313 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 5068 "dhcp6_parser.cc"
    break;

  case 970: // $@148: %empty
#line 3319 "dhcp6_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 5080 "dhcp6_parser.cc"
    break;

  case 971: // output_options_list: "output-options" $@148 ":" "[" output_options_list_content "]"
#line 3325 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5089 "dhcp6_parser.cc"
    break;

  case 974: // output_options_list_content: output_options_list_content ","
#line 3332 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 5097 "dhcp6_parser.cc"
    break;

  case 975: // $@149: %empty
#line 3337 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 5107 "dhcp6_parser.cc"
    break;

  case 976: // output_entry: "{" $@149 output_params_list "}"
#line 3341 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 5115 "dhcp6_parser.cc"
    break;

  case 979: // output_params_list: output_params_list ","
#line 3347 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 5123 "dhcp6_parser.cc"
    break;

  case 985: // $@150: %empty
#line 3359 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5132 "dhcp6_parser.cc"
    break;

  case 986: // output: "output" $@150 ":" "constant string"
#line 3362 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5142 "dhcp6_parser.cc"
    break;

  case 987: // flush: "flush" ":" "boolean"
#line 3368 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5152 "dhcp6_parser.cc"
    break;

  case 988: // maxsize: "maxsize" ":" "integer"
#line 3374 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5162 "dhcp6_parser.cc"
    break;

  case 989: // maxver: "maxver" ":" "integer"
#line 3380 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5172 "dhcp6_parser.cc"
    break;

  case 990: // $@151: %empty
#line 3386 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5181 "dhcp6_parser.cc"
    break;

  case 991: // pattern: "pattern" $@151 ":" "constant string"
#line 3389 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5191 "dhcp6_parser.cc"
    break;

  case 992: // $@152: %empty
#line 3395 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5203 "dhcp6_parser.cc"
    break;

  case 993: // compatibility: "compatibility" $@152 ":" "{" compatibility_params "}"
#line 3401 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5212 "dhcp6_parser.cc"
    break;

  case 996: // compatibility_params: compatibility_params ","
#line 3408 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5220 "dhcp6_parser.cc"
    break;

  case 999: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3417 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5230 "dhcp6_parser.cc"
    break;


#line 5234 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1442;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     486, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442,    51,    43,    50,    79,   141,
     243,   251,   286,   297,   314,   322,   335,   337,   378,   388,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,    43,  -158,
      68,   763,    63,  1437,   656,   274,   826,    52,    17,   160,
     -52,   261,    56, -1442,   187,   138,   290,   395,   319, -1442,
      64, -1442, -1442, -1442, -1442, -1442, -1442, -1442,   400,   408,
     423,   425,   426,   444,   445,   469,   472,   483,   484,   489,
     490,   492, -1442,   494,   495,   501,   502,   505, -1442, -1442,
   -1442,   506,   508,   512,   514,   516,   517,   519, -1442, -1442,
   -1442,   520, -1442, -1442, -1442, -1442, -1442, -1442,   521,   522,
     523, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
     524, -1442, -1442, -1442, -1442, -1442, -1442, -1442,   526,   527,
     530, -1442, -1442,   531, -1442,   109, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,   533,
     534,   537,   539, -1442,   134, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,   543,   546,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442,   135, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,   550,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
     171, -1442, -1442, -1442, -1442, -1442, -1442,   553, -1442,   555,
     556, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
     182, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,   403,
     482, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
     557, -1442, -1442,   559, -1442, -1442, -1442,   562, -1442, -1442,
     564,   570, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442,   563,   572,   573, -1442, -1442,
   -1442, -1442, -1442,   566,   575, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,   184,
   -1442, -1442, -1442,   578, -1442,   580, -1442,   581,   582, -1442,
   -1442, -1442, -1442, -1442,   186, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442,   583,   227, -1442, -1442, -1442,
   -1442,    43,    43, -1442,   345,   584, -1442, -1442,   585,   588,
     592,   595,   597,   598,   368,   369,   370,   371,   372,   373,
     376,   379,   380,   382,   385,   386,   389,   390,   611,   392,
     394,   391,   396,   397,   628,   634,   635,   413,   415,   404,
     410,   419,   421,   420,   654,   658,   659,   429,   665,   668,
     671,   673,   676,   677,   446,   448,   450,   678,   684,   686,
     687,   688,   689,   690,   691,   693,   465,   695,   698,   716,
     724,   730,   731,   733,   509,   510,   515,   734,   738, -1442,
     763, -1442,   739,   518,   529,   525,   528,    63, -1442,   741,
     745,   747,   749,   750,   532,   540,   752,   754,   755,   767,
     772,  1437, -1442,   775,   548,   656, -1442,   785,   558,   786,
     560,   561,   274, -1442,   787,   788,   790,   796,   799,   800,
     801,   802, -1442,   826, -1442,   803,   804,   574,   806,   840,
     841,   609, -1442,    17,   843,   612,   613,   614,   844, -1442,
     160,   848,   849,    18, -1442,   621,   855,   629,   859,   630,
     631,   863,   864,   261, -1442,   865,   638,    56, -1442, -1442,
   -1442,   866,   867,   641,   869,   870,   878,   879,   883, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442,   655, -1442, -1442, -1442, -1442, -1442,  -147,
     657,   660, -1442, -1442, -1442, -1442, -1442, -1442, -1442,   887,
     888,   890, -1442,   663,   664,   276,   894,   893,   667, -1442,
   -1442, -1442,   897,   898,   899,   900,   904,   905,   906,   907,
     909, -1442,   910,   911,   908,   912,   913,   692,   696, -1442,
   -1442, -1442,   916,   915, -1442,   920, -1442, -1442, -1442, -1442,
   -1442,   922,   926,   699,   702,   703, -1442, -1442,   920,   920,
     920,   704,   925, -1442,   705, -1442, -1442,   706, -1442,   707,
   -1442, -1442, -1442,   920,   920,   920,   920,   708,   709,   710,
     711, -1442,   712,   714, -1442,   715,   718,   719, -1442, -1442,
     720, -1442, -1442, -1442,   920, -1442,   721,   893, -1442, -1442,
     722, -1442,   723, -1442, -1442,   -74,   713, -1442,   953, -1442,
   -1442,    43,   763, -1442,    56,    63,   175,   175,   952, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,   966,   967,
     968, -1442, -1442, -1442, -1442, -1442, -1442, -1442,   969, -1442,
   -1442, -1442,  -102,    43,    89,    93,   970,   971,   972,   242,
      75,   163,   194,   973,   -20,   261, -1442, -1442,   975,  -170,
   -1442, -1442,   976,   977, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442,   851, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,   952, -1442,
     245,   246,   249, -1442, -1442, -1442, -1442,   982,   983,   984,
     985,   986,   987,   988,   989,   990,   991, -1442,   992,   994,
   -1442, -1442, -1442, -1442, -1442,   287, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,   293,
   -1442,   993,   997, -1442, -1442,   995,   999, -1442, -1442,   998,
    1000, -1442, -1442,  1001,  1002, -1442, -1442,  1003,  1005, -1442,
   -1442, -1442,    81, -1442, -1442, -1442,  1004, -1442, -1442, -1442,
     110, -1442, -1442, -1442, -1442, -1442,   302, -1442, -1442, -1442,
   -1442,   124, -1442, -1442,  1006,  1008, -1442, -1442,  1007,  1011,
   -1442,  1012,  1013,  1014,  1015,  1017,  1018,   303, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442,  1020,  1021,  1023,
   -1442, -1442, -1442, -1442,   309, -1442, -1442, -1442, -1442, -1442,
   -1442,  1024,  1026,  1027, -1442,   315, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442,  1031, -1442,  1034, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442,   325, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442,  1009,  1037, -1442,  1044, -1442,
    1046, -1442, -1442, -1442,   327, -1442, -1442, -1442, -1442, -1442,
     328, -1442,   357, -1442,  1047, -1442,   340, -1442, -1442,   819,
   -1442,  1048,  1056, -1442, -1442,  1055,  1061, -1442, -1442,  1058,
    1063, -1442, -1442, -1442,  1068,  1070,  1071,  1076,   771,   830,
     847,   853,   856,   861,   872,   875,   882,   884,  1084,   857,
     896,  1096,  1121,  1124,  1145,   175, -1442, -1442,   175, -1442,
     952,  1437, -1442,   966,    17, -1442,   967,   160, -1442,   968,
     366, -1442,   969,  -102, -1442, -1442,    89, -1442,  1148,  1154,
      93, -1442,   211,   970, -1442,   826, -1442,   971,   -52, -1442,
     972,   928,   930,   933,   935,   937,   939,   242, -1442,  1173,
    1175,   945,   947,   948,    75, -1442,   950,   981,   996,   163,
   -1442,  1197,  1206,  1207,  1016,  1208,  1019,  1215,   194, -1442,
     194, -1442,   973,  1025,  1216,  1028,  1218,   -20, -1442, -1442,
     174,   975, -1442,  1029,  -170, -1442, -1442,  1219,  1223,   656,
   -1442,   976,   274, -1442,   977, -1442, -1442,  1010,  1033,  1035,
    1036, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442,    69, -1442, -1442,  1038,  1039,  1040,  1041, -1442,   342,
   -1442,   343, -1442,  1220, -1442,  1224, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442,   349, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
    1042,  1043, -1442, -1442, -1442,  1230,  1232, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,  1229,  1235,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442,  1231, -1442,   356,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,   112,  1045,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,   333,  1049,
    1050, -1442,  1234, -1442,  1222, -1442,   393, -1442, -1442,  1051,
   -1442,    43, -1442, -1442,  1239, -1442, -1442, -1442, -1442, -1442,
     399, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,  1052,
     460, -1442,   461, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
     366, -1442, -1442, -1442,  1242,  1244,  1054,  1057, -1442,   211,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442,    47,  1243, -1442, -1442, -1442,  1245,  1030,
    1248,   174, -1442, -1442, -1442, -1442, -1442,  1053,  1062, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,   462,
   -1442, -1442, -1442, -1442, -1442, -1442,  1249,  1255, -1442,  1256,
   -1442,  1065, -1442, -1442, -1442,  1264,  1267,  1274,  1276,    47,
   -1442,    -6, -1442,  1243,  1253, -1442,  1106,  1066,  1067,  1277,
   -1442, -1442, -1442, -1442, -1442, -1442,   463, -1442, -1442, -1442,
   -1442,   407, -1442, -1442, -1442, -1442, -1442,  1281,  1293,    -6,
   -1442,    59,  1253, -1442, -1442,  1296,  1301, -1442,  1073, -1442,
   -1442,  1304,  1305,  1306, -1442,   464, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442,   128, -1442,  1281, -1442,  1309,  1078,  1081,
    1082,  1315,    59, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442,   481, -1442, -1442, -1442, -1442,  1087, -1442, -1442, -1442,
    1088, -1442,  1319,  1320,   128, -1442, -1442, -1442,  1092,  1094,
   -1442, -1442, -1442
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   205,     9,   391,    11,
     613,    13,   658,    15,   693,    17,   528,    19,   537,    21,
     576,    23,   353,    25,   908,    27,   940,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   695,     0,   539,   578,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   144,   938,   203,   224,   226,   228,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   193,     0,     0,     0,     0,     0,   163,   170,
     172,     0,     0,     0,     0,     0,     0,     0,   382,   526,
     567,     0,   196,   198,   176,   466,   645,   647,     0,     0,
       0,   309,   328,   318,   298,   731,   684,   344,   365,   765,
       0,   330,   790,   792,   889,   906,   186,   188,     0,     0,
       0,   950,   992,     0,   143,     0,    69,    72,    73,    74,
      75,    76,    77,    78,    79,    80,   111,   112,   113,   114,
     115,    81,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   117,   118,   132,   133,   134,
     107,   140,   141,   142,   136,   137,   138,    84,    85,    86,
      87,   104,    88,    90,    89,   135,    94,    95,    82,   108,
     109,   110,    83,    92,    93,   102,   103,   105,    91,    96,
      97,    98,    99,   100,   101,   106,   116,   139,   218,     0,
       0,     0,     0,   217,     0,   207,   210,   211,   212,   213,
     214,   215,   216,   604,   649,   447,   449,   451,     0,     0,
     455,   457,   459,   453,   728,   446,   396,   397,   398,   399,
     400,   401,   402,   403,   423,   424,   425,   426,   427,   430,
     431,   432,   433,   434,   435,   436,   437,   438,   439,   440,
     441,   442,   428,   429,   443,   444,   445,     0,   393,   407,
     408,   409,   412,   413,   414,   415,   417,   418,   419,   410,
     411,   404,   405,   421,   422,   406,   416,   420,   642,     0,
     641,   625,   626,   627,   628,   629,   630,   631,   632,   633,
     634,   635,   636,   637,   638,   621,   622,   623,   624,   620,
       0,   615,   618,   619,   639,   640,   677,     0,   680,     0,
       0,   676,   668,   669,   670,   671,   667,   666,   674,   675,
       0,   660,   663,   664,   672,   673,   665,   726,   712,   714,
     716,   718,   720,   722,   724,   711,   708,   709,   710,     0,
     696,   697,   702,   703,   704,   700,   705,   706,   707,   701,
       0,   557,   272,     0,   561,   559,   564,     0,   553,   554,
       0,   540,   541,   544,   556,   545,   546,   547,   563,   548,
     549,   550,   551,   552,   595,     0,     0,     0,   602,   593,
     594,   597,   598,     0,   579,   580,   583,   584,   585,   586,
     587,   588,   589,   592,   590,   591,   361,   363,   358,     0,
     355,   359,   360,     0,   925,     0,   928,     0,     0,   932,
     936,   923,   921,   922,     0,   910,   913,   914,   915,   916,
     917,   918,   919,   920,   947,     0,     0,   942,   945,   946,
      47,    52,     0,    39,    45,     0,    66,    62,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
      71,    68,     0,     0,     0,     0,     0,   209,   206,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   395,   392,     0,     0,   617,   614,     0,     0,     0,
       0,     0,   662,   659,     0,     0,     0,     0,     0,     0,
       0,     0,   694,   699,   529,     0,     0,     0,     0,     0,
       0,     0,   538,   543,     0,     0,     0,     0,     0,   577,
     582,     0,     0,   357,   354,     0,     0,     0,     0,     0,
       0,     0,     0,   912,   909,     0,     0,   944,   941,    51,
      43,     0,     0,     0,     0,     0,     0,     0,     0,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,     0,   191,   192,   160,   161,   162,     0,
       0,     0,   174,   175,   182,   183,   184,   185,   190,     0,
       0,     0,   195,     0,     0,     0,     0,     0,     0,   461,
     462,   463,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   789,     0,     0,     0,     0,     0,     0,     0,   200,
     201,   202,     0,     0,    70,     0,   220,   221,   222,   223,
     208,     0,     0,     0,     0,     0,   464,   465,     0,     0,
       0,     0,     0,   394,     0,   644,   616,     0,   679,     0,
     682,   683,   661,     0,     0,     0,     0,     0,     0,     0,
       0,   698,     0,     0,   555,     0,     0,     0,   566,   542,
       0,   599,   600,   601,     0,   581,     0,     0,   356,   924,
       0,   927,     0,   930,   931,     0,     0,   911,     0,   949,
     943,     0,     0,   145,     0,     0,     0,     0,   230,   194,
     165,   166,   167,   168,   169,   164,   171,   173,   384,   530,
     569,   197,   199,   178,   179,   180,   181,   177,   468,    40,
     646,   648,     0,    48,     0,     0,     0,   686,   346,     0,
       0,     0,     0,   794,     0,     0,   187,   189,     0,     0,
      53,   219,   606,   651,   448,   450,   452,   456,   458,   460,
     454,     0,   643,   678,   681,   727,   713,   715,   717,   719,
     721,   723,   725,   558,   273,   562,   560,   565,   596,   603,
     362,   364,   926,   929,   934,   935,   933,   937,   230,    44,
       0,     0,     0,   263,   265,   267,   269,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   282,     0,     0,
     290,   292,   294,   296,   262,     0,   237,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     254,   255,   256,   257,   253,   258,   259,   260,   261,     0,
     235,     0,   231,   232,   389,     0,   385,   386,   535,     0,
     531,   532,   574,     0,   570,   571,   473,     0,   469,   470,
     316,   317,     0,   311,   314,   315,     0,   326,   327,   323,
       0,   320,   324,   325,   305,   307,     0,   300,   303,   304,
     736,     0,   733,   691,     0,   687,   688,   351,     0,   347,
     348,     0,     0,     0,     0,     0,     0,     0,   367,   370,
     371,   372,   373,   374,   375,   779,   785,     0,     0,     0,
     778,   775,   776,   777,     0,   767,   770,   773,   771,   772,
     774,     0,     0,     0,   340,     0,   332,   335,   336,   337,
     338,   339,   817,   822,   824,     0,   847,     0,   828,   816,
     809,   810,   811,   814,   815,     0,   801,   804,   805,   806,
     807,   812,   813,   808,   799,     0,   795,   796,     0,   901,
       0,   904,   897,   898,     0,   891,   894,   895,   896,   899,
       0,   955,     0,   952,     0,   998,     0,   994,   997,    55,
     611,     0,   607,   608,   656,     0,   652,   653,   730,     0,
       0,    64,   939,   204,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   239,   225,   227,     0,   229,
     234,     0,   383,   388,   539,   527,   534,   578,   568,   573,
       0,   467,   472,   313,   310,   329,   322,   319,     0,     0,
     302,   299,   738,   735,   732,   695,   685,   690,     0,   345,
     350,     0,     0,     0,     0,     0,     0,   369,   366,     0,
       0,     0,     0,     0,   769,   766,     0,     0,     0,   334,
     331,     0,     0,     0,     0,     0,     0,     0,   803,   791,
       0,   793,   798,     0,     0,     0,     0,   893,   890,   907,
       0,   954,   951,     0,   996,   993,    57,     0,    56,     0,
     605,   610,     0,   650,   655,   729,   948,     0,     0,     0,
       0,   271,   274,   275,   276,   277,   278,   279,   280,   289,
     281,     0,   287,   288,     0,     0,     0,     0,   238,     0,
     233,     0,   387,     0,   533,     0,   572,   525,   493,   494,
     495,   497,   498,   499,   482,   483,   502,   503,   504,   505,
     506,   509,   510,   511,   512,   513,   514,   515,   516,   517,
     518,   519,   520,   521,   507,   508,   522,   523,   524,   478,
     479,   480,   481,   489,   490,   491,   492,   486,   487,   488,
     496,     0,   475,   484,   500,   501,   485,   471,   312,   321,
       0,     0,   301,   759,   761,     0,     0,   757,   751,   752,
     753,   754,   755,   756,   758,   748,   749,   750,     0,   739,
     740,   743,   744,   745,   746,   747,   734,     0,   689,     0,
     349,   376,   377,   378,   379,   380,   381,   368,     0,     0,
     784,   787,   788,   768,   341,   342,   343,   333,     0,     0,
       0,   826,     0,   827,     0,   802,     0,   797,   900,     0,
     903,     0,   892,   970,     0,   968,   966,   960,   964,   965,
       0,   957,   962,   963,   961,   953,   999,   995,    54,    59,
       0,   609,     0,   654,   264,   266,   268,   270,   284,   285,
     286,   283,   291,   293,   295,   297,   236,   390,   536,   575,
     477,   474,   306,   308,     0,     0,     0,     0,   737,   742,
     692,   352,   781,   782,   783,   780,   786,   819,   820,   821,
     818,   823,   825,     0,   830,   800,   902,   905,     0,     0,
       0,   959,   956,    58,   612,   657,   476,     0,     0,   763,
     764,   741,   859,   862,   864,   866,   858,   857,   856,     0,
     849,   852,   853,   854,   855,   835,     0,   831,   832,     0,
     967,     0,   958,   760,   762,     0,     0,     0,     0,   851,
     848,     0,   829,   834,     0,   969,     0,     0,     0,     0,
     850,   845,   844,   840,   842,   843,     0,   837,   841,   833,
     975,     0,   972,   861,   860,   863,   865,   868,     0,   839,
     836,     0,   974,   971,   873,     0,   869,   870,     0,   838,
     985,     0,     0,     0,   990,     0,   977,   980,   981,   982,
     983,   984,   973,     0,   867,   872,   846,     0,     0,     0,
       0,     0,   979,   976,   885,   887,   884,   878,   880,   882,
     883,     0,   875,   879,   881,   871,     0,   987,   988,   989,
       0,   978,     0,     0,   877,   874,   986,   991,     0,     0,
     876,   886,   888
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442,   -10, -1442,  -637, -1442,
     576, -1442, -1442, -1442, -1442,   535, -1442,  -420, -1442, -1442,
   -1442,   -71, -1442, -1442, -1442, -1442, -1442, -1442, -1442,   565,
     779, -1442, -1442,     4,    12,    22,    38,    41,    42,   -57,
     -54,   -35,   -15,    97,   100,   102, -1442,    20,    23,    45,
      48, -1442, -1442,    55, -1442,    60, -1442,    66,   103,    71,
   -1442, -1442,    73,    76,    78,    84,    90, -1442,    95, -1442,
     105, -1442, -1442, -1442, -1442, -1442,   107, -1442,   108, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442,   567,   773, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442,   474, -1442,   244, -1442,  -756,   250, -1442, -1442, -1441,
   -1442, -1440, -1442, -1442, -1442, -1442,   -55, -1442,  -797, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442,  -801, -1442,  -795, -1442,  -792, -1442, -1442, -1442,
   -1442, -1442, -1442,   229, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442,   240,  -782, -1442, -1442, -1442, -1442,   238, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442,   207, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442,   228, -1442, -1442, -1442,   232,   740, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442,   224, -1442, -1442, -1442,
   -1442, -1442, -1442, -1075, -1442, -1442, -1442,   259, -1442, -1442,
   -1442,   263,   784, -1442, -1442, -1074, -1442, -1073, -1442,    61,
   -1442,    85, -1442,   121, -1442,   123, -1442,   113,   115,   118,
   -1442, -1072, -1442, -1442, -1442, -1442,   255, -1442, -1442,    -1,
    1284, -1442, -1442, -1442, -1442, -1442,   266, -1442, -1442, -1442,
     269, -1442,   762, -1442,   -65, -1442, -1442, -1442, -1442, -1442,
     -61, -1442, -1442, -1442, -1442, -1442,   -29, -1442, -1442, -1442,
     267, -1442, -1442, -1442,   270, -1442,   758, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442,   198, -1442, -1442, -1442,   202,   809, -1442, -1442,   -63,
     -42, -1442,   -13, -1442, -1442, -1442, -1442, -1442,   200, -1442,
   -1442, -1442,   203,   795, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442,   -58, -1442, -1442, -1442,   262, -1442, -1442, -1442,   271,
   -1442,   792,   568, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1071, -1442,
   -1442, -1442, -1442, -1442,   277, -1442, -1442, -1442,    24, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,   258,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442,   248, -1442,   247,   265, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442,   -39, -1442, -1442,   -64, -1442, -1442, -1442, -1442,
   -1442,   -33, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442,   -82, -1442, -1442,  -108, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442,   252, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442,   599,   805, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442,   645,   797, -1442, -1442, -1442, -1442,
   -1442, -1442,   264, -1442, -1442,    31, -1442, -1442, -1442, -1442,
   -1442, -1442,   -32, -1442, -1442,   -69, -1442, -1442, -1442, -1442,
   -1442, -1442, -1442, -1442, -1442, -1442,   268, -1442
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     800,    87,    88,    41,    68,    84,    85,   821,  1049,  1167,
    1168,   884,    43,    70,    90,   475,    91,    45,    71,   165,
     166,   167,   478,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   504,   785,   186,   505,   187,   506,   188,   189,   190,
     520,   797,   191,   192,   193,   194,   195,   542,   196,   543,
     197,   198,   199,   200,   498,   201,   202,   518,   203,   519,
     204,   205,   206,   207,   480,    47,    72,   244,   245,   246,
     552,   247,   248,   249,   250,   208,   481,   209,   482,   210,
     483,   911,   912,   913,  1088,   885,   886,   887,  1064,   888,
    1065,   889,  1066,   890,  1067,   891,   892,   596,   893,   894,
     895,   896,   897,   898,   899,   900,   901,  1078,  1351,   902,
     903,   904,   905,  1081,   906,  1082,   907,  1083,   908,  1084,
     211,   530,   946,   947,   948,  1108,   949,  1109,   212,   527,
     932,   933,   934,   935,   213,   529,   940,   941,   942,   943,
     214,   528,   215,   537,   995,   996,   997,   998,   999,   216,
     533,   958,   959,   960,  1118,    63,    80,   439,   440,   441,
     611,   442,   612,   217,   534,   967,   968,   969,   970,   971,
     972,   973,   974,   218,   514,   915,   916,   917,  1091,    49,
      73,   297,   298,   299,   561,   300,   562,   301,   563,   302,
     569,   303,   566,   304,   567,   305,   568,   219,   220,   221,
     309,   310,   222,   521,   927,   928,   929,  1100,  1251,  1252,
     223,   515,    57,    77,   919,   920,   921,  1094,    59,    78,
     400,   401,   402,   403,   404,   405,   406,   595,   407,   599,
     408,   598,   409,   410,   600,   411,   224,   516,   923,   924,
     925,  1097,    61,    79,   423,   424,   425,   426,   427,   604,
     428,   429,   430,   431,   432,   433,   608,   312,   559,  1051,
    1052,  1053,  1169,    51,    74,   340,   341,   342,   573,   343,
     225,   522,   226,   523,   315,   560,  1055,  1056,  1057,  1172,
      53,    75,   360,   361,   362,   577,   363,   364,   579,   365,
     366,   227,   532,   954,   955,   956,  1115,    55,    76,   379,
     380,   381,   382,   585,   383,   586,   384,   587,   385,   588,
     386,   589,   387,   590,   388,   591,   389,   584,   317,   570,
    1059,   228,   531,   951,   952,  1112,  1278,  1279,  1280,  1281,
    1282,  1364,  1283,  1365,  1284,  1285,   229,   535,   984,   985,
     986,  1129,  1375,   987,   988,  1130,   989,   990,   230,   231,
     538,   232,   539,  1025,  1026,  1027,  1150,  1015,  1016,  1017,
    1141,  1380,  1018,  1142,  1019,  1143,  1020,  1021,  1022,  1147,
    1416,  1417,  1418,  1431,  1446,  1447,  1448,  1458,  1023,  1145,
    1409,  1410,  1411,  1425,  1454,  1412,  1426,  1413,  1427,  1414,
    1428,  1465,  1466,  1467,  1483,  1501,  1502,  1503,  1512,  1504,
    1513,   233,   540,  1034,  1035,  1036,  1037,  1154,  1038,  1039,
    1156,   234,   541,    65,    81,   454,   455,   456,   457,   616,
     458,   459,   618,   460,   461,   462,   621,   856,   463,   622,
     235,   479,    67,    82,   466,   467,   468,   625,   469,   236,
     547,  1042,  1043,  1160,  1330,  1331,  1332,  1333,  1390,  1334,
    1388,  1451,  1452,  1461,  1475,  1476,  1477,  1487,  1478,  1479,
    1480,  1481,  1491,   237,   548,  1046,  1047,  1048
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     164,   243,   265,   320,   351,   375,    38,   398,   419,   438,
     451,  1010,   357,   981,   421,   316,   272,  1011,   422,   273,
    1012,   909,   939,   399,   420,  1240,  1241,  1242,  1250,  1256,
     251,   313,   344,   358,   377,   930,   412,   434,   274,   452,
     799,   391,  1497,  1498,   311,   339,   356,   376,    31,  1044,
      32,    30,    33,   780,   781,   782,   783,    42,   275,   252,
     314,   345,   359,   378,   163,   413,   435,   476,   453,   464,
     465,  1402,   477,  1497,  1498,   392,    86,   266,    89,   238,
     239,   240,   241,   242,  1103,   267,    44,  1104,   136,   137,
     784,   436,   437,   279,   321,   268,   280,   322,   392,   975,
     393,   394,   136,   137,   868,   395,   396,   397,  1348,  1349,
    1350,   269,   550,  1106,   270,   271,  1107,   551,   281,   323,
     799,   282,   324,   854,   855,   136,   137,  1113,   283,   325,
    1114,   129,   931,   284,   326,   335,   352,   557,   571,   285,
     327,   471,   558,   572,   287,   328,   288,   329,    46,   289,
     330,   290,   331,   864,   865,   136,   137,   291,   332,   336,
     353,   436,   437,   292,   333,  1028,  1029,  1030,   293,   334,
     276,   136,   137,   277,   575,   278,   286,  1441,   294,   576,
     295,   296,   163,   136,   137,   582,   306,   613,   307,   623,
     583,   308,   614,   470,   624,   337,   354,   338,   355,   863,
     864,   865,   866,   867,   868,   869,   870,   871,   872,   873,
     874,   875,   876,   877,  1031,   944,   945,   878,   879,   880,
     881,   882,   883,  1403,  1404,  1405,   930,   937,   163,   938,
     627,   976,   977,   978,   979,   628,   136,   137,   880,   881,
     882,   392,   414,   393,   394,   415,   416,   417,   550,   627,
      48,   163,   557,  1061,  1062,   392,   392,  1063,    50,    98,
      99,   100,   101,   102,   103,  1372,  1373,  1374,   136,   137,
    1470,   136,   137,  1471,  1472,  1473,  1474,    34,    35,    36,
      37,   163,   136,   137,   418,  1240,  1241,  1242,  1250,  1256,
    1085,   130,   392,    52,   472,  1086,  1085,   163,   827,   828,
     829,  1087,   136,   137,    54,  1110,  1127,  1494,  1495,   163,
    1111,  1128,  1134,   835,   836,   837,   838,  1135,  1139,   136,
     137,    56,   474,  1140,   939,   991,   992,   993,  1148,    58,
    1157,   623,  1199,  1149,   849,  1158,  1159,   981,  1263,  1264,
    1265,  1266,    60,  1164,    62,  1085,   571,  1010,  1165,  1010,
    1356,  1357,  1360,  1011,   130,  1011,  1012,  1361,  1012,   613,
    1161,  1002,   163,  1162,  1371,  1003,  1004,  1005,  1006,   136,
     137,   793,   794,   795,   796,  1007,  1008,   346,   347,   348,
     349,   350,   136,   137,  1323,    64,  1324,  1325,   961,   962,
     963,   964,   965,   966,   163,    66,  1148,   163,   260,   261,
     262,  1385,  1391,   473,   484,   263,   319,  1392,   163,   163,
    1462,   592,   485,  1463,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   486,   163,   487,
     488,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   163,   130,   392,   489,   490,
     443,   444,   445,   446,   447,   448,   449,   450,   132,   133,
     134,   629,   630,   575,   582,  1429,  1459,  1492,  1394,  1395,
    1430,  1460,  1493,   491,   136,   137,   492,   256,   257,   164,
     259,   138,   139,   140,  1514,   593,   243,   493,   494,  1515,
     260,   261,   262,   495,   496,   163,   497,   263,   499,   500,
     265,  1377,  1378,  1379,   320,   501,   502,   264,   163,   503,
     507,   351,   508,   316,   272,   251,   509,   273,   510,   357,
     511,   512,   375,   513,   517,   524,   525,   526,   536,   313,
     544,   545,   398,   344,   546,   549,   274,   553,   554,   419,
     358,   555,   311,   556,   252,   421,   339,   564,   399,   422,
     565,   377,   451,   356,   574,   420,   275,   578,   314,   580,
     581,   412,   345,   597,   376,   594,   601,   605,   434,   359,
     156,   157,   602,   603,   609,   266,   606,   607,   610,   631,
     378,   452,   615,   267,   617,   619,   620,   626,   632,   633,
     413,   279,   634,   268,   280,   321,   635,   435,   322,   636,
     163,   637,   638,   639,   640,   641,   642,   643,   644,   269,
     453,   645,   270,   271,   646,   653,   281,   647,   648,   282,
     323,   649,   650,   324,   651,   652,   283,   654,   656,   655,
     325,   284,   659,   657,   658,   326,   335,   285,   660,   661,
     664,   327,   287,   352,   288,   665,   328,   289,   329,   290,
     662,   330,   663,   331,   666,   291,   667,   668,   669,   332,
     336,   292,   670,   671,   672,   333,   293,   353,   276,   673,
     334,   277,   674,   278,   286,   675,   294,   676,   295,   296,
     677,   678,   682,   679,   306,   680,   307,   681,   683,   308,
     684,   685,   686,   687,   688,   689,   337,   690,   338,   692,
     691,   164,   693,   354,   243,   355,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
     694,   115,   116,   117,   118,   119,   120,   121,   695,   123,
     124,   125,   126,   251,   696,   697,   130,   698,   702,   980,
     994,  1009,   703,   705,   451,   711,   699,   700,  1045,   712,
     134,   713,   701,   714,   715,   706,   718,   318,   719,   720,
     708,   859,   252,   709,   136,   137,   707,   716,   982,  1000,
    1013,   721,  1032,   452,    92,    93,   722,   717,    94,   724,
     260,   261,   262,   725,    95,    96,    97,   263,   319,   727,
     729,   733,   734,   728,   735,   730,   731,   983,  1001,  1014,
     736,  1033,   453,   737,   738,   739,   740,   742,   743,   744,
     745,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   746,   747,   748,   750,   754,   751,
     752,   753,   756,   757,   131,   132,   133,   134,   759,   760,
     156,   157,   135,   762,   761,   763,   764,   765,   766,   768,
     771,   136,   137,   769,   772,   773,   774,   775,   138,   139,
     140,   141,   142,   143,   144,   776,   777,   145,   778,   779,
     163,   786,   788,   789,   787,   790,   146,   791,   792,   798,
      32,   801,   802,   803,   804,   147,   130,   805,   148,   806,
     807,   808,   857,   813,   809,   149,   810,   811,   812,   814,
     815,   818,   819,   150,   151,   820,   816,   822,   152,   153,
     817,   823,   831,   824,   136,   137,   825,   826,   830,   832,
     833,   834,   839,   840,   841,   842,   843,   154,   844,   845,
     367,   155,   846,   847,   848,   850,   852,   853,   858,   910,
     368,   369,   370,   371,   372,   373,   374,   156,   157,   158,
     159,   160,   161,   914,   918,   922,   926,   950,   953,   957,
    1024,   162,  1041,  1050,  1054,   368,  1068,  1069,  1070,  1071,
    1072,  1073,  1074,  1075,  1076,  1077,  1079,   163,  1080,  1089,
    1090,  1092,  1093,  1096,  1095,  1099,  1181,  1098,  1102,  1101,
    1105,  1117,  1116,  1119,  1120,  1151,  1121,  1122,  1123,  1124,
     265,  1125,  1126,   398,  1131,  1132,   419,  1133,  1136,  1207,
    1137,  1138,   421,   316,   272,  1144,   422,   273,  1146,   399,
    1152,  1267,   420,  1214,   375,  1239,  1215,   438,  1153,   313,
    1155,  1163,   412,  1166,  1170,   434,   274,  1274,  1254,  1171,
     163,  1173,   311,   980,  1174,  1216,  1175,  1182,   994,  1176,
    1276,  1253,  1177,   377,  1178,  1179,   275,  1009,   314,  1009,
    1180,   413,  1183,  1275,   435,  1217,   376,  1255,  1191,  1326,
    1184,  1185,   982,  1045,  1192,   266,  1186,  1000,   320,  1277,
    1194,   351,   378,   267,  1208,  1327,  1013,  1187,  1013,   357,
    1188,   279,  1209,   268,   280,  1032,  1268,  1189,  1328,  1190,
    1221,   983,  1210,  1222,  1269,  1195,  1001,   344,  1196,   269,
     358,  1193,   270,   271,  1270,  1014,   281,  1014,  1211,   282,
     339,  1212,  1213,   356,  1033,  1223,   283,  1329,  1224,  1197,
    1271,   284,  1260,  1272,  1273,  1225,   345,   285,  1261,   359,
    1226,  1243,   287,  1291,   288,  1292,  1227,   289,  1293,   290,
    1294,  1229,  1295,  1230,  1296,   291,  1231,  1298,  1232,  1299,
    1300,   292,  1301,  1302,  1233,  1244,   293,  1304,   276,   321,
    1234,   277,   322,   278,   286,  1235,   294,  1218,   295,   296,
    1219,  1308,  1220,  1228,   306,  1236,   307,  1237,  1238,   308,
    1309,  1310,  1312,  1247,   323,  1248,  1305,   324,  1249,  1314,
    1319,  1245,  1321,  1246,   325,  1338,  1339,  1384,  1358,   326,
     335,  1306,  1359,   352,  1366,   327,  1367,  1368,  1369,  1370,
     328,  1383,   329,  1389,  1344,   330,  1397,   331,  1398,  1419,
    1415,  1311,  1421,   332,   336,  1432,  1313,   353,  1433,   333,
    1450,  1434,  1318,  1320,   334,  1420,  1336,  1345,  1436,  1346,
    1347,  1437,  1352,  1353,  1354,  1355,  1362,  1363,  1438,  1376,
    1439,  1453,  1457,  1381,  1382,  1386,  1393,  1423,  1464,  1207,
     337,  1399,   338,   354,  1400,   355,  1424,  1468,  1267,  1435,
    1455,  1456,  1484,  1214,  1485,  1239,  1215,  1486,  1488,  1489,
    1490,  1387,  1406,  1506,  1274,  1507,  1508,  1509,  1254,  1510,
    1326,  1516,  1517,  1518,  1519,  1216,  1521,  1276,  1522,   704,
     710,  1253,  1060,   851,  1200,  1198,  1327,   860,   936,  1262,
    1275,  1407,   862,  1258,  1259,  1217,  1307,  1255,  1290,  1328,
    1289,  1297,  1202,   758,  1201,   723,  1277,  1257,  1406,  1396,
    1442,   390,  1204,  1203,  1208,   749,  1206,  1205,   755,  1341,
    1408,  1340,  1209,  1268,  1343,  1342,  1443,   732,  1329,  1288,
    1221,  1269,  1210,  1222,   726,   741,  1287,  1407,  1442,  1444,
    1286,  1270,  1303,  1401,  1449,  1469,  1440,  1316,  1211,  1058,
    1317,  1212,  1213,  1505,  1443,  1223,  1520,  1271,  1224,  1322,
    1272,  1273,  1496,  1315,  1040,  1225,  1408,  1444,  1445,   861,
    1226,  1243,  1422,  1511,   770,  1335,  1227,     0,   767,     0,
    1482,  1229,  1337,  1230,     0,     0,  1231,     0,  1232,     0,
       0,  1499,     0,  1496,  1233,  1244,  1445,     0,     0,     0,
    1234,     0,     0,     0,     0,  1235,     0,  1218,     0,     0,
    1219,     0,  1220,  1228,     0,  1236,     0,  1237,  1238,     0,
    1500,     0,  1499,  1247,     0,  1248,     0,     0,  1249,     0,
       0,  1245,     0,  1246,     0,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,     0,     0,
       0,  1500,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,     0,     0,   130,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   132,
     133,   134,     0,     0,     0,     0,     0,   253,     0,   254,
       0,     0,     0,     0,     0,   136,   137,   255,   256,   257,
     258,   259,   138,   139,   140,     0,     0,     0,     0,     0,
       0,   260,   261,   262,     0,     0,     0,     0,   263,     0,
     146,     0,     0,     0,     0,     0,     0,     0,   264,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   156,   157,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   163
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   812,    75,   810,    79,    73,    73,   812,    79,    73,
     812,   777,   804,    78,    79,  1100,  1100,  1100,  1100,  1100,
      72,    73,    74,    75,    76,   137,    78,    79,    73,    81,
     677,    24,  1483,  1483,    73,    74,    75,    76,     5,   219,
       7,     0,     9,   200,   201,   202,   203,     7,    73,    72,
      73,    74,    75,    76,   234,    78,    79,     3,    81,    13,
      14,    24,     8,  1514,  1514,    81,   234,    73,    10,    16,
      17,    18,    19,    20,     3,    73,     7,     6,   108,   109,
     237,   143,   144,    73,    74,    73,    73,    74,    81,    24,
      83,    84,   108,   109,    29,    88,    89,    90,    39,    40,
      41,    73,     3,     3,    73,    73,     6,     8,    73,    74,
     757,    73,    74,   197,   198,   108,   109,     3,    73,    74,
       6,    79,   234,    73,    74,    74,    75,     3,     3,    73,
      74,     3,     8,     8,    73,    74,    73,    74,     7,    73,
      74,    73,    74,    25,    26,   108,   109,    73,    74,    74,
      75,   143,   144,    73,    74,   185,   186,   187,    73,    74,
      73,   108,   109,    73,     3,    73,    73,   183,    73,     8,
      73,    73,   234,   108,   109,     3,    73,     3,    73,     3,
       8,    73,     8,     6,     8,    74,    75,    74,    75,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,   234,   122,   123,    42,    43,    44,
      45,    46,    47,   176,   177,   178,   137,   138,   234,   140,
       3,   156,   157,   158,   159,     8,   108,   109,    44,    45,
      46,    81,    82,    83,    84,    85,    86,    87,     3,     3,
       7,   234,     3,     8,     8,    81,    81,     8,     7,    48,
      49,    50,    51,    52,    53,   153,   154,   155,   108,   109,
     211,   108,   109,   214,   215,   216,   217,   234,   235,   236,
     237,   234,   108,   109,   124,  1360,  1360,  1360,  1360,  1360,
       3,    80,    81,     7,     4,     8,     3,   234,   718,   719,
     720,     8,   108,   109,     7,     3,     3,   179,   180,   234,
       8,     8,     3,   733,   734,   735,   736,     8,     3,   108,
     109,     7,     3,     8,  1106,   162,   163,   164,     3,     7,
       3,     3,  1088,     8,   754,     8,     8,  1134,   127,   128,
     129,   130,     7,     3,     7,     3,     3,  1148,     8,  1150,
       8,     8,     3,  1148,    80,  1150,  1148,     8,  1150,     3,
       3,   167,   234,     6,     8,   171,   172,   173,   174,   108,
     109,    95,    96,    97,    98,   181,   182,   103,   104,   105,
     106,   107,   108,   109,   210,     7,   212,   213,   146,   147,
     148,   149,   150,   151,   234,     7,     3,   234,   124,   125,
     126,     8,     3,     8,     4,   131,   132,     8,   234,   234,
       3,     8,     4,     6,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,     4,   234,     4,
       4,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,   234,    80,    81,     4,     4,
     189,   190,   191,   192,   193,   194,   195,   196,    92,    93,
      94,   471,   472,     3,     3,     3,     3,     3,     8,     8,
       8,     8,     8,     4,   108,   109,     4,   111,   112,   550,
     114,   115,   116,   117,     3,     3,   557,     4,     4,     8,
     124,   125,   126,     4,     4,   234,     4,   131,     4,     4,
     571,   168,   169,   170,   575,     4,     4,   141,   234,     4,
       4,   582,     4,   571,   571,   557,     4,   571,     4,   582,
       4,     4,   593,     4,     4,     4,     4,     4,     4,   571,
       4,     4,   603,   575,     4,     4,   571,     4,     4,   610,
     582,     4,   571,     4,   557,   610,   575,     4,   603,   610,
       4,   593,   623,   582,     4,   610,   571,     4,   571,     4,
       4,   603,   575,     4,   593,     8,     4,     4,   610,   582,
     204,   205,     8,     3,     8,   571,     4,     4,     3,   234,
     593,   623,     4,   571,     4,     4,     4,     4,     4,     4,
     603,   571,     4,   571,   571,   575,     4,   610,   575,     4,
     234,     4,     4,   235,   235,   235,   235,   235,   235,   571,
     623,   235,   571,   571,   235,     4,   571,   237,   236,   571,
     575,   236,   236,   575,   235,   235,   571,   235,   237,   235,
     575,   571,     4,   237,   237,   575,   575,   571,     4,     4,
     236,   575,   571,   582,   571,   235,   575,   571,   575,   571,
     237,   575,   237,   575,   235,   571,   235,   237,     4,   575,
     575,   571,     4,     4,   235,   575,   571,   582,   571,     4,
     575,   571,     4,   571,   571,     4,   571,     4,   571,   571,
       4,     4,     4,   237,   571,   237,   571,   237,     4,   571,
       4,     4,     4,     4,     4,     4,   575,     4,   575,     4,
     235,   772,     4,   582,   775,   582,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
       4,    65,    66,    67,    68,    69,    70,    71,     4,    73,
      74,    75,    76,   775,     4,     4,    80,     4,     4,   810,
     811,   812,     4,     4,   815,     4,   237,   237,   819,     4,
      94,     4,   237,     4,     4,   237,     4,   101,     4,     4,
     235,   771,   775,   235,   108,   109,   237,   235,   810,   811,
     812,     4,   814,   815,    11,    12,     4,   237,    15,     4,
     124,   125,   126,   235,    21,    22,    23,   131,   132,     4,
       4,     4,     4,   235,     4,   235,   235,   810,   811,   812,
       4,   814,   815,     4,     4,     4,     4,     4,     4,   235,
       4,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,     4,     4,   237,     4,     4,   237,
     237,   237,     4,     4,    91,    92,    93,    94,   237,     4,
     204,   205,    99,     4,   235,   235,   235,     4,     4,     4,
       4,   108,   109,   235,     7,   234,     7,     7,   115,   116,
     117,   118,   119,   120,   121,     7,     7,   124,     5,   234,
     234,   234,     5,     5,   234,     5,   133,   234,   234,     5,
       7,   234,     5,     5,     5,   142,    80,     7,   145,     5,
       5,     5,   199,     5,     7,   152,     7,     7,     7,     7,
       7,     5,     7,   160,   161,     5,   234,     5,   165,   166,
     234,     5,     7,   234,   108,   109,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   184,   234,   234,
     124,   188,   234,   234,   234,   234,   234,   234,     5,     7,
     134,   135,   136,   137,   138,   139,   140,   204,   205,   206,
     207,   208,   209,     7,     7,     7,     7,     7,     7,     7,
       7,   218,     7,     7,     7,   134,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   234,     4,     6,
       3,     6,     3,     3,     6,     3,   235,     6,     3,     6,
       6,     3,     6,     6,     3,     6,     4,     4,     4,     4,
    1091,     4,     4,  1094,     4,     4,  1097,     4,     4,  1100,
       4,     4,  1097,  1091,  1091,     4,  1097,  1091,     4,  1094,
       3,  1112,  1097,  1100,  1115,  1100,  1100,  1118,     4,  1091,
       4,     4,  1094,   234,     6,  1097,  1091,  1112,  1100,     3,
     234,     6,  1091,  1134,     3,  1100,     8,   237,  1139,     6,
    1112,  1100,     4,  1115,     4,     4,  1091,  1148,  1091,  1150,
       4,  1094,   235,  1112,  1097,  1100,  1115,  1100,     4,  1160,
     237,   235,  1134,  1164,   237,  1091,   235,  1139,  1169,  1112,
       4,  1172,  1115,  1091,  1100,  1160,  1148,   235,  1150,  1172,
     235,  1091,  1100,  1091,  1091,  1157,  1112,   235,  1160,   235,
    1100,  1134,  1100,  1100,  1112,     4,  1139,  1169,     4,  1091,
    1172,   235,  1091,  1091,  1112,  1148,  1091,  1150,  1100,  1091,
    1169,  1100,  1100,  1172,  1157,  1100,  1091,  1160,  1100,     4,
    1112,  1091,     4,  1112,  1112,  1100,  1169,  1091,     4,  1172,
    1100,  1100,  1091,   235,  1091,   235,  1100,  1091,   235,  1091,
     235,  1100,   235,  1100,   235,  1091,  1100,     4,  1100,     4,
     235,  1091,   235,   235,  1100,  1100,  1091,   237,  1091,  1169,
    1100,  1091,  1169,  1091,  1091,  1100,  1091,  1100,  1091,  1091,
    1100,     4,  1100,  1100,  1091,  1100,  1091,  1100,  1100,  1091,
       4,     4,     4,  1100,  1169,  1100,   235,  1169,  1100,     4,
       4,  1100,     4,  1100,  1169,     6,     3,     5,     8,  1169,
    1169,   235,     8,  1172,     4,  1169,     4,     8,     3,     8,
    1169,     7,  1169,     4,   234,  1169,     4,  1169,     4,     4,
       7,   235,     4,  1169,  1169,     6,   237,  1172,     3,  1169,
       7,     5,   237,   235,  1169,   235,   237,   234,     4,   234,
     234,     4,   234,   234,   234,   234,   234,   234,     4,   234,
       4,   175,     5,   234,   234,   234,   234,   234,     7,  1360,
    1169,   237,  1169,  1172,   237,  1172,   234,     4,  1369,   234,
     234,   234,     6,  1360,     3,  1360,  1360,   234,     4,     4,
       4,  1321,  1383,     4,  1369,   237,   235,   235,  1360,     4,
    1391,   234,   234,     4,     4,  1360,   234,  1369,   234,   550,
     557,  1360,   858,   757,  1090,  1085,  1391,   772,   803,  1110,
    1369,  1383,   775,  1103,  1106,  1360,  1139,  1360,  1120,  1391,
    1118,  1127,  1093,   613,  1091,   571,  1369,  1102,  1429,  1360,
    1431,    77,  1096,  1094,  1360,   603,  1099,  1097,   610,  1171,
    1383,  1169,  1360,  1369,  1174,  1172,  1431,   582,  1391,  1117,
    1360,  1369,  1360,  1360,   575,   593,  1115,  1429,  1459,  1431,
    1113,  1369,  1134,  1369,  1433,  1459,  1429,  1150,  1360,   831,
    1152,  1360,  1360,  1485,  1459,  1360,  1514,  1369,  1360,  1157,
    1369,  1369,  1483,  1148,   815,  1360,  1429,  1459,  1431,   774,
    1360,  1360,  1391,  1492,   627,  1161,  1360,    -1,   623,    -1,
    1462,  1360,  1164,  1360,    -1,    -1,  1360,    -1,  1360,    -1,
      -1,  1483,    -1,  1514,  1360,  1360,  1459,    -1,    -1,    -1,
    1360,    -1,    -1,    -1,    -1,  1360,    -1,  1360,    -1,    -1,
    1360,    -1,  1360,  1360,    -1,  1360,    -1,  1360,  1360,    -1,
    1483,    -1,  1514,  1360,    -1,  1360,    -1,    -1,  1360,    -1,
      -1,  1360,    -1,  1360,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    -1,
      -1,  1514,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    -1,    -1,    80,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    92,
      93,    94,    -1,    -1,    -1,    -1,    -1,   100,    -1,   102,
      -1,    -1,    -1,    -1,    -1,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,    -1,    -1,    -1,    -1,    -1,
      -1,   124,   125,   126,    -1,    -1,    -1,    -1,   131,    -1,
     133,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   234
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
     269,   295,   296,   297,   298,   301,   303,   305,   307,   310,
     311,   312,   313,   314,   316,   457,   459,   461,   463,   504,
     533,   534,   535,   537,   538,   540,   103,   104,   105,   106,
     107,   269,   457,   459,   461,   463,   504,   537,   538,   540,
     550,   551,   552,   554,   555,   557,   558,   124,   134,   135,
     136,   137,   138,   139,   140,   269,   504,   538,   540,   567,
     568,   569,   570,   572,   574,   576,   578,   580,   582,   584,
     478,    24,    81,    83,    84,    88,    89,    90,   269,   364,
     488,   489,   490,   491,   492,   493,   494,   496,   498,   500,
     501,   503,   538,   540,    82,    85,    86,    87,   124,   269,
     364,   492,   498,   512,   513,   514,   515,   516,   518,   519,
     520,   521,   522,   523,   538,   540,   143,   144,   269,   425,
     426,   427,   429,   189,   190,   191,   192,   193,   194,   195,
     196,   269,   538,   540,   683,   684,   685,   686,   688,   689,
     691,   692,   693,   696,    13,    14,   702,   703,   704,   706,
       6,     3,     4,     8,     3,   273,     3,     8,   280,   699,
     332,   344,   346,   348,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   322,     4,
       4,     4,     4,     4,   299,   302,   304,     4,     4,     4,
       4,     4,     4,     4,   442,   479,   505,     4,   325,   327,
     308,   471,   539,   541,     4,     4,     4,   397,   409,   403,
     389,   590,   560,   418,   432,   605,     4,   411,   618,   620,
     670,   680,   315,   317,     4,     4,     4,   708,   732,     4,
       3,     8,   338,     4,     4,     4,     4,     3,     8,   526,
     543,   452,   454,   456,     4,     4,   460,   462,   464,   458,
     587,     3,     8,   536,     4,     3,     8,   553,     4,   556,
       4,     4,     3,     8,   585,   571,   573,   575,   577,   579,
     581,   583,     8,     3,     8,   495,   365,     4,   499,   497,
     502,     4,     8,     3,   517,     4,     4,     4,   524,     8,
       3,   428,   430,     3,     8,     4,   687,     4,   690,     4,
       4,   694,   697,     3,     8,   705,     4,     3,     8,   254,
     254,   234,     4,     4,     4,     4,     4,     4,     4,   235,
     235,   235,   235,   235,   235,   235,   235,   237,   236,   236,
     236,   235,   235,     4,   235,   235,   237,   237,   237,     4,
       4,     4,   237,   237,   236,   235,   235,   235,   237,     4,
       4,     4,   235,     4,     4,     4,     4,     4,     4,   237,
     237,   237,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   235,     4,     4,     4,     4,     4,     4,     4,   237,
     237,   237,     4,     4,   278,     4,   237,   237,   235,   235,
     336,     4,     4,     4,     4,     4,   235,   237,     4,     4,
       4,     4,     4,   450,     4,   235,   534,     4,   235,     4,
     235,   235,   551,     4,     4,     4,     4,     4,     4,     4,
       4,   569,     4,     4,   235,     4,     4,     4,   237,   490,
       4,   237,   237,   237,     4,   514,     4,     4,   426,   237,
       4,   235,     4,   235,   235,     4,     4,   684,     4,   235,
     703,     4,     7,   234,     7,     7,     7,     7,     5,   234,
     200,   201,   202,   203,   237,   300,   234,   234,     5,     5,
       5,   234,   234,    95,    96,    97,    98,   309,     5,   256,
     258,   234,     5,     5,     5,     7,     5,     5,     5,     7,
       7,     7,     7,     5,     7,     7,   234,   234,     5,     7,
       5,   265,     5,     5,   234,   234,   234,   265,   265,   265,
     234,     7,   234,   234,   234,   265,   265,   265,   265,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   265,
     234,   258,   234,   234,   197,   198,   695,   199,     5,   254,
     277,   702,   335,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    42,    43,
      44,    45,    46,    47,   269,   353,   354,   355,   357,   359,
     361,   363,   364,   366,   367,   368,   369,   370,   371,   372,
     373,   374,   377,   378,   379,   380,   382,   384,   386,   353,
       7,   349,   350,   351,     7,   443,   444,   445,     7,   482,
     483,   484,     7,   506,   507,   508,     7,   472,   473,   474,
     137,   234,   398,   399,   400,   401,   263,   138,   140,   400,
     404,   405,   406,   407,   122,   123,   390,   391,   392,   394,
       7,   591,   592,     7,   561,   562,   563,     7,   419,   420,
     421,   146,   147,   148,   149,   150,   151,   433,   434,   435,
     436,   437,   438,   439,   440,    24,   156,   157,   158,   159,
     269,   366,   538,   540,   606,   607,   608,   611,   612,   614,
     615,   162,   163,   164,   269,   412,   413,   414,   415,   416,
     538,   540,   167,   171,   172,   173,   174,   181,   182,   269,
     380,   382,   384,   538,   540,   625,   626,   627,   630,   632,
     634,   635,   636,   646,     7,   621,   622,   623,   185,   186,
     187,   234,   538,   540,   671,   672,   673,   674,   676,   677,
     683,     7,   709,   710,   219,   269,   733,   734,   735,   266,
       7,   527,   528,   529,     7,   544,   545,   546,   570,   588,
     349,     8,     8,     8,   356,   358,   360,   362,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   375,     4,
       4,   381,   383,   385,   387,     3,     8,     8,   352,     6,
       3,   446,     6,     3,   485,     6,     3,   509,     6,     3,
     475,     6,     3,     3,     6,     6,     3,     6,   393,   395,
       3,     8,   593,     3,     6,   564,     6,     3,   422,     6,
       3,     4,     4,     4,     4,     4,     4,     3,     8,   609,
     613,     4,     4,     4,     3,     8,     4,     4,     4,     3,
       8,   628,   631,   633,     4,   647,     4,   637,     3,     8,
     624,     6,     3,     4,   675,     4,   678,     3,     8,     8,
     711,     3,     6,     4,     3,     8,   234,   267,   268,   530,
       6,     3,   547,     6,     3,     8,     6,     4,     4,     4,
       4,   235,   237,   235,   237,   235,   235,   235,   235,   235,
     235,     4,   237,   235,     4,     4,     4,     4,   354,   353,
     351,   449,   445,   488,   484,   512,   508,   269,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   295,   296,   297,   298,   301,   303,   305,   306,   307,
     310,   311,   312,   313,   314,   316,   318,   324,   326,   364,
     441,   453,   455,   457,   459,   461,   463,   465,   466,   467,
     469,   476,   477,   504,   538,   540,   586,   474,   399,   405,
       4,     4,   391,   127,   128,   129,   130,   269,   281,   282,
     283,   284,   285,   286,   364,   504,   538,   540,   594,   595,
     596,   597,   598,   600,   602,   603,   592,   567,   563,   425,
     421,   235,   235,   235,   235,   235,   235,   434,     4,     4,
     235,   235,   235,   607,   237,   235,   235,   413,     4,     4,
       4,   235,     4,   237,     4,   626,   625,   623,   237,     4,
     235,     4,   672,   210,   212,   213,   269,   364,   538,   540,
     712,   713,   714,   715,   717,   710,   237,   734,     6,     3,
     533,   529,   550,   546,   234,   234,   234,   234,    39,    40,
      41,   376,   234,   234,   234,   234,     8,     8,     8,     8,
       3,     8,   234,   234,   599,   601,     4,     4,     8,     3,
       8,     8,   153,   154,   155,   610,   234,   168,   169,   170,
     629,   234,   234,     7,     5,     8,   234,   254,   718,     4,
     716,     3,     8,   234,     8,     8,   477,     4,     4,   237,
     237,   596,    24,   176,   177,   178,   269,   538,   540,   648,
     649,   650,   653,   655,   657,     7,   638,   639,   640,     4,
     235,     4,   713,   234,   234,   651,   654,   656,   658,     3,
       8,   641,     6,     3,     5,   234,     4,     4,     4,     4,
     649,   183,   269,   364,   538,   540,   642,   643,   644,   640,
       7,   719,   720,   175,   652,   234,   234,     5,   645,     3,
       8,   721,     3,     6,     7,   659,   660,   661,     4,   643,
     211,   214,   215,   216,   217,   722,   723,   724,   726,   727,
     728,   729,   720,   662,     6,     3,   234,   725,     4,     4,
       4,   730,     3,     8,   179,   180,   269,   357,   359,   538,
     540,   663,   664,   665,   667,   661,     4,   237,   235,   235,
       4,   723,   666,   668,     3,     8,   234,   234,     4,     4,
     664,   234,   234
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
     534,   534,   534,   534,   534,   534,   534,   534,   534,   534,
     534,   534,   534,   534,   534,   534,   534,   534,   534,   534,
     534,   534,   536,   535,   537,   539,   538,   541,   540,   543,
     542,   544,   544,   545,   545,   545,   547,   546,   549,   548,
     550,   550,   550,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   553,   552,   554,
     556,   555,   557,   558,   560,   559,   561,   561,   562,   562,
     562,   564,   563,   566,   565,   567,   567,   568,   568,   568,
     569,   569,   569,   569,   569,   569,   569,   569,   569,   569,
     569,   569,   571,   570,   573,   572,   575,   574,   577,   576,
     579,   578,   581,   580,   583,   582,   585,   584,   587,   586,
     588,   590,   589,   591,   591,   591,   593,   592,   594,   594,
     595,   595,   595,   596,   596,   596,   596,   596,   596,   596,
     596,   596,   596,   596,   596,   596,   596,   596,   597,   599,
     598,   601,   600,   602,   603,   605,   604,   606,   606,   606,
     607,   607,   607,   607,   607,   607,   607,   607,   607,   609,
     608,   610,   610,   610,   611,   613,   612,   614,   615,   616,
     618,   617,   620,   619,   621,   621,   622,   622,   622,   624,
     623,   625,   625,   625,   626,   626,   626,   626,   626,   626,
     626,   626,   626,   626,   626,   626,   626,   628,   627,   629,
     629,   629,   631,   630,   633,   632,   634,   635,   637,   636,
     638,   638,   639,   639,   639,   641,   640,   642,   642,   642,
     643,   643,   643,   643,   643,   645,   644,   647,   646,   648,
     648,   648,   649,   649,   649,   649,   649,   649,   649,   651,
     650,   652,   654,   653,   656,   655,   658,   657,   659,   659,
     660,   660,   660,   662,   661,   663,   663,   663,   664,   664,
     664,   664,   664,   664,   664,   666,   665,   668,   667,   670,
     669,   671,   671,   671,   672,   672,   672,   672,   672,   672,
     673,   675,   674,   676,   678,   677,   680,   679,   682,   681,
     683,   683,   683,   684,   684,   684,   684,   684,   684,   684,
     684,   684,   684,   684,   685,   687,   686,   688,   690,   689,
     691,   692,   694,   693,   695,   695,   697,   696,   699,   698,
     701,   700,   702,   702,   702,   703,   703,   705,   704,   706,
     708,   707,   709,   709,   709,   711,   710,   712,   712,   712,
     713,   713,   713,   713,   713,   713,   713,   714,   716,   715,
     718,   717,   719,   719,   719,   721,   720,   722,   722,   722,
     723,   723,   723,   723,   723,   725,   724,   726,   727,   728,
     730,   729,   732,   731,   733,   733,   733,   734,   734,   735
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     0,     4,     0,     4,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       0,     4,     3,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     0,     1,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     0,     6,     1,     3,     2,     0,     4,     0,     1,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     3,     3,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     3,     0,     4,     3,     3,     3,
       0,     6,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     0,     4,     0,     4,     3,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     0,     4,     0,     6,     1,
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
     588,   589,   590,   591,   594,   594,   604,   610,   616,   622,
     628,   634,   640,   646,   652,   658,   664,   670,   676,   682,
     688,   694,   700,   706,   706,   715,   718,   721,   724,   727,
     733,   733,   742,   742,   751,   760,   770,   770,   779,   782,
     785,   788,   793,   799,   805,   811,   817,   817,   826,   826,
     835,   841,   847,   853,   853,   862,   868,   868,   877,   877,
     886,   892,   898,   904,   904,   916,   916,   925,   926,   927,
     932,   933,   934,   935,   936,   937,   938,   939,   942,   942,
     953,   959,   965,   971,   977,   977,   990,   990,  1003,  1003,
    1014,  1015,  1018,  1019,  1020,  1025,  1025,  1035,  1036,  1037,
    1042,  1043,  1044,  1045,  1046,  1047,  1048,  1049,  1050,  1051,
    1052,  1053,  1054,  1055,  1056,  1057,  1058,  1059,  1060,  1061,
    1062,  1063,  1064,  1067,  1067,  1076,  1076,  1085,  1085,  1094,
    1094,  1103,  1109,  1109,  1118,  1124,  1130,  1136,  1142,  1148,
    1154,  1160,  1166,  1166,  1174,  1175,  1176,  1179,  1185,  1191,
    1197,  1197,  1206,  1206,  1215,  1215,  1224,  1224,  1233,  1233,
    1244,  1245,  1246,  1251,  1252,  1255,  1255,  1274,  1274,  1292,
    1292,  1303,  1304,  1305,  1310,  1311,  1314,  1319,  1324,  1324,
    1335,  1336,  1337,  1342,  1343,  1344,  1347,  1352,  1359,  1359,
    1372,  1372,  1385,  1386,  1387,  1392,  1393,  1394,  1395,  1396,
    1397,  1400,  1406,  1412,  1418,  1418,  1429,  1430,  1433,  1434,
    1435,  1440,  1440,  1450,  1450,  1460,  1461,  1462,  1465,  1468,
    1469,  1472,  1472,  1481,  1481,  1490,  1490,  1502,  1503,  1504,
    1509,  1510,  1511,  1512,  1513,  1514,  1517,  1523,  1529,  1535,
    1541,  1547,  1556,  1556,  1570,  1571,  1574,  1575,  1576,  1585,
    1585,  1611,  1611,  1622,  1623,  1624,  1630,  1631,  1632,  1633,
    1634,  1635,  1636,  1637,  1638,  1639,  1640,  1641,  1642,  1643,
    1644,  1645,  1646,  1647,  1648,  1649,  1650,  1651,  1652,  1653,
    1654,  1655,  1656,  1657,  1658,  1659,  1660,  1661,  1662,  1663,
    1664,  1665,  1666,  1667,  1668,  1669,  1670,  1671,  1672,  1673,
    1674,  1675,  1676,  1677,  1678,  1679,  1680,  1683,  1683,  1692,
    1692,  1701,  1701,  1710,  1710,  1720,  1720,  1732,  1732,  1743,
    1743,  1754,  1760,  1766,  1772,  1778,  1786,  1786,  1798,  1799,
    1803,  1804,  1805,  1810,  1810,  1818,  1819,  1820,  1825,  1826,
    1827,  1828,  1829,  1830,  1831,  1832,  1833,  1834,  1835,  1836,
    1837,  1838,  1839,  1840,  1841,  1842,  1843,  1844,  1845,  1846,
    1847,  1848,  1849,  1850,  1851,  1852,  1853,  1854,  1855,  1856,
    1857,  1858,  1859,  1860,  1861,  1862,  1863,  1864,  1865,  1866,
    1867,  1868,  1869,  1870,  1871,  1872,  1879,  1879,  1893,  1893,
    1902,  1903,  1906,  1907,  1908,  1915,  1915,  1930,  1930,  1944,
    1945,  1948,  1949,  1950,  1955,  1956,  1957,  1958,  1959,  1960,
    1961,  1962,  1963,  1964,  1967,  1969,  1975,  1977,  1977,  1986,
    1986,  1995,  1995,  2004,  2006,  2006,  2015,  2025,  2025,  2038,
    2039,  2044,  2045,  2046,  2053,  2053,  2065,  2065,  2077,  2078,
    2083,  2084,  2085,  2092,  2093,  2094,  2095,  2096,  2097,  2098,
    2099,  2100,  2101,  2102,  2105,  2107,  2107,  2116,  2118,  2120,
    2126,  2132,  2138,  2138,  2152,  2152,  2165,  2166,  2169,  2170,
    2171,  2176,  2176,  2186,  2186,  2196,  2197,  2198,  2203,  2204,
    2205,  2206,  2207,  2208,  2209,  2210,  2211,  2212,  2213,  2214,
    2215,  2216,  2217,  2218,  2219,  2220,  2221,  2222,  2223,  2224,
    2225,  2226,  2229,  2229,  2238,  2244,  2244,  2269,  2269,  2299,
    2299,  2312,  2313,  2316,  2317,  2318,  2323,  2323,  2335,  2335,
    2347,  2348,  2349,  2354,  2355,  2356,  2357,  2358,  2359,  2360,
    2361,  2362,  2363,  2364,  2365,  2366,  2367,  2370,  2370,  2379,
    2385,  2385,  2394,  2400,  2409,  2409,  2420,  2421,  2424,  2425,
    2426,  2431,  2431,  2440,  2440,  2449,  2450,  2453,  2454,  2455,
    2461,  2462,  2463,  2464,  2465,  2466,  2467,  2468,  2469,  2470,
    2471,  2472,  2475,  2475,  2486,  2486,  2497,  2497,  2508,  2508,
    2517,  2517,  2526,  2526,  2535,  2535,  2544,  2544,  2558,  2558,
    2569,  2575,  2575,  2586,  2587,  2588,  2593,  2593,  2603,  2604,
    2607,  2608,  2609,  2614,  2615,  2616,  2617,  2618,  2619,  2620,
    2621,  2622,  2623,  2624,  2625,  2626,  2627,  2628,  2631,  2633,
    2633,  2642,  2642,  2652,  2658,  2667,  2667,  2680,  2681,  2682,
    2687,  2688,  2689,  2690,  2691,  2692,  2693,  2694,  2695,  2698,
    2698,  2706,  2707,  2708,  2711,  2717,  2717,  2726,  2732,  2740,
    2748,  2748,  2760,  2760,  2772,  2773,  2776,  2777,  2778,  2783,
    2783,  2791,  2792,  2793,  2798,  2799,  2800,  2801,  2802,  2803,
    2804,  2805,  2806,  2807,  2808,  2809,  2810,  2813,  2813,  2822,
    2823,  2824,  2827,  2827,  2837,  2837,  2847,  2853,  2859,  2859,
    2870,  2871,  2874,  2875,  2876,  2881,  2881,  2889,  2890,  2891,
    2896,  2897,  2898,  2899,  2900,  2903,  2903,  2914,  2914,  2927,
    2928,  2929,  2934,  2935,  2936,  2937,  2938,  2939,  2940,  2943,
    2943,  2951,  2954,  2954,  2963,  2963,  2972,  2972,  2983,  2984,
    2987,  2988,  2989,  2994,  2994,  3002,  3003,  3004,  3009,  3010,
    3011,  3012,  3013,  3014,  3015,  3018,  3018,  3027,  3027,  3038,
    3038,  3051,  3052,  3053,  3058,  3059,  3060,  3061,  3062,  3063,
    3066,  3072,  3072,  3081,  3087,  3087,  3097,  3097,  3110,  3110,
    3120,  3121,  3122,  3127,  3128,  3129,  3130,  3131,  3132,  3133,
    3134,  3135,  3136,  3137,  3140,  3146,  3146,  3155,  3161,  3161,
    3170,  3176,  3182,  3182,  3191,  3192,  3195,  3195,  3206,  3206,
    3218,  3218,  3228,  3229,  3230,  3236,  3237,  3240,  3240,  3251,
    3259,  3259,  3272,  3273,  3274,  3280,  3280,  3288,  3289,  3290,
    3295,  3296,  3297,  3298,  3299,  3300,  3301,  3304,  3310,  3310,
    3319,  3319,  3330,  3331,  3332,  3337,  3337,  3345,  3346,  3347,
    3352,  3353,  3354,  3355,  3356,  3359,  3359,  3368,  3374,  3380,
    3386,  3386,  3395,  3395,  3406,  3407,  3408,  3413,  3414,  3417
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
#line 7080 "dhcp6_parser.cc"

#line 3423 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
