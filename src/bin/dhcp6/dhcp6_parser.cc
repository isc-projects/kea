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
#line 324 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 413 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 324 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 419 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 324 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 425 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 324 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 431 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 324 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 437 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 324 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 443 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 324 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 449 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 324 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 455 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 324 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 461 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 324 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 467 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
#line 324 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 473 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 324 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 479 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 324 "dhcp6_parser.yy"
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
#line 333 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 766 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 334 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 772 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 335 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 778 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 336 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 784 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 337 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 790 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 338 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 796 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 339 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 802 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 340 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 808 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 341 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 814 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 342 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 820 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 343 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 826 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 344 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 832 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 345 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 838 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 346 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 844 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 354 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 850 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 355 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 856 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 356 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 862 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 357 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 868 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 358 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 874 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 359 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 880 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 360 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 886 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 363 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 895 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 368 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 906 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 373 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 916 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 379 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 922 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 386 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 932 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 391 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 943 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 397 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 951 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 402 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 960 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 405 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 968 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 413 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 977 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 417 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 986 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 421 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 994 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 427 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 1002 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 429 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1011 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 438 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1020 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 442 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1029 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 446 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1037 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 456 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1048 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 465 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1059 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 470 "dhcp6_parser.yy"
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
#line 480 "dhcp6_parser.yy"
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
#line 489 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1097 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 497 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1105 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 503 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1115 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 507 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1124 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 514 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1132 "dhcp6_parser.cc"
    break;

  case 144: // $@21: %empty
#line 595 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1141 "dhcp6_parser.cc"
    break;

  case 145: // data_directory: "data-directory" $@21 ":" "constant string"
#line 598 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.warning(yystack_[2].location, "data-directory is deprecated and will be ignored");
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1152 "dhcp6_parser.cc"
    break;

  case 146: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 605 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1162 "dhcp6_parser.cc"
    break;

  case 147: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 611 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1172 "dhcp6_parser.cc"
    break;

  case 148: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 617 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1182 "dhcp6_parser.cc"
    break;

  case 149: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 623 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1192 "dhcp6_parser.cc"
    break;

  case 150: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 629 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1202 "dhcp6_parser.cc"
    break;

  case 151: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 635 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1212 "dhcp6_parser.cc"
    break;

  case 152: // renew_timer: "renew-timer" ":" "integer"
#line 641 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1222 "dhcp6_parser.cc"
    break;

  case 153: // rebind_timer: "rebind-timer" ":" "integer"
#line 647 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1232 "dhcp6_parser.cc"
    break;

  case 154: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 653 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1242 "dhcp6_parser.cc"
    break;

  case 155: // t1_percent: "t1-percent" ":" "floating point"
#line 659 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1252 "dhcp6_parser.cc"
    break;

  case 156: // t2_percent: "t2-percent" ":" "floating point"
#line 665 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1262 "dhcp6_parser.cc"
    break;

  case 157: // cache_threshold: "cache-threshold" ":" "floating point"
#line 671 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1272 "dhcp6_parser.cc"
    break;

  case 158: // cache_max_age: "cache-max-age" ":" "integer"
#line 677 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1282 "dhcp6_parser.cc"
    break;

  case 159: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 683 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1292 "dhcp6_parser.cc"
    break;

  case 160: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 689 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1302 "dhcp6_parser.cc"
    break;

  case 161: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 695 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1312 "dhcp6_parser.cc"
    break;

  case 162: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 701 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1322 "dhcp6_parser.cc"
    break;

  case 163: // $@22: %empty
#line 707 "dhcp6_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1331 "dhcp6_parser.cc"
    break;

  case 164: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 710 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1340 "dhcp6_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "when-present"
#line 716 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1348 "dhcp6_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "never"
#line 719 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1356 "dhcp6_parser.cc"
    break;

  case 167: // ddns_replace_client_name_value: "always"
#line 722 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1364 "dhcp6_parser.cc"
    break;

  case 168: // ddns_replace_client_name_value: "when-not-present"
#line 725 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1372 "dhcp6_parser.cc"
    break;

  case 169: // ddns_replace_client_name_value: "boolean"
#line 728 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1381 "dhcp6_parser.cc"
    break;

  case 170: // $@23: %empty
#line 734 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1390 "dhcp6_parser.cc"
    break;

  case 171: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 737 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1400 "dhcp6_parser.cc"
    break;

  case 172: // $@24: %empty
#line 743 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1409 "dhcp6_parser.cc"
    break;

  case 173: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 746 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1419 "dhcp6_parser.cc"
    break;

  case 174: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 752 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1429 "dhcp6_parser.cc"
    break;

  case 175: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 761 "dhcp6_parser.yy"
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
#line 771 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1452 "dhcp6_parser.cc"
    break;

  case 177: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 774 "dhcp6_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1461 "dhcp6_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 780 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1469 "dhcp6_parser.cc"
    break;

  case 179: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 783 "dhcp6_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1477 "dhcp6_parser.cc"
    break;

  case 180: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 786 "dhcp6_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1485 "dhcp6_parser.cc"
    break;

  case 181: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 789 "dhcp6_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1493 "dhcp6_parser.cc"
    break;

  case 182: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 794 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1503 "dhcp6_parser.cc"
    break;

  case 183: // ddns_ttl: "ddns-ttl" ":" "integer"
#line 800 "dhcp6_parser.yy"
                                 {
    ctx.unique("ddns-ttl", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl", ttl);
}
#line 1513 "dhcp6_parser.cc"
    break;

  case 184: // ddns_ttl_min: "ddns-ttl-min" ":" "integer"
#line 806 "dhcp6_parser.yy"
                                         {
    ctx.unique("ddns-ttl-min", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-min", ttl);
}
#line 1523 "dhcp6_parser.cc"
    break;

  case 185: // ddns_ttl_max: "ddns-ttl-mix" ":" "integer"
#line 812 "dhcp6_parser.yy"
                                         {
    ctx.unique("ddns-ttl-max", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-max", ttl);
}
#line 1533 "dhcp6_parser.cc"
    break;

  case 186: // $@26: %empty
#line 818 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1542 "dhcp6_parser.cc"
    break;

  case 187: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 821 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1552 "dhcp6_parser.cc"
    break;

  case 188: // $@27: %empty
#line 827 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1561 "dhcp6_parser.cc"
    break;

  case 189: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 830 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1571 "dhcp6_parser.cc"
    break;

  case 190: // store_extended_info: "store-extended-info" ":" "boolean"
#line 836 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1581 "dhcp6_parser.cc"
    break;

  case 191: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 842 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1591 "dhcp6_parser.cc"
    break;

  case 192: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 848 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1601 "dhcp6_parser.cc"
    break;

  case 193: // $@28: %empty
#line 854 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1610 "dhcp6_parser.cc"
    break;

  case 194: // server_tag: "server-tag" $@28 ":" "constant string"
#line 857 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1620 "dhcp6_parser.cc"
    break;

  case 195: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 863 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1630 "dhcp6_parser.cc"
    break;

  case 196: // $@29: %empty
#line 869 "dhcp6_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1639 "dhcp6_parser.cc"
    break;

  case 197: // allocator: "allocator" $@29 ":" "constant string"
#line 872 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1649 "dhcp6_parser.cc"
    break;

  case 198: // $@30: %empty
#line 878 "dhcp6_parser.yy"
                           {
    ctx.unique("pd-allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1658 "dhcp6_parser.cc"
    break;

  case 199: // pd_allocator: "pd-allocator" $@30 ":" "constant string"
#line 881 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-allocator", al);
    ctx.leave();
}
#line 1668 "dhcp6_parser.cc"
    break;

  case 200: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 887 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1678 "dhcp6_parser.cc"
    break;

  case 201: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 893 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1688 "dhcp6_parser.cc"
    break;

  case 202: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 899 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1698 "dhcp6_parser.cc"
    break;

  case 203: // $@31: %empty
#line 905 "dhcp6_parser.yy"
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
#line 911 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1720 "dhcp6_parser.cc"
    break;

  case 205: // $@32: %empty
#line 917 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1730 "dhcp6_parser.cc"
    break;

  case 206: // sub_interfaces6: "{" $@32 interfaces_config_params "}"
#line 921 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1739 "dhcp6_parser.cc"
    break;

  case 209: // interfaces_config_params: interfaces_config_params ","
#line 928 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1747 "dhcp6_parser.cc"
    break;

  case 218: // $@33: %empty
#line 943 "dhcp6_parser.yy"
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
#line 949 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1768 "dhcp6_parser.cc"
    break;

  case 220: // re_detect: "re-detect" ":" "boolean"
#line 954 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1778 "dhcp6_parser.cc"
    break;

  case 221: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 960 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1788 "dhcp6_parser.cc"
    break;

  case 222: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 966 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1798 "dhcp6_parser.cc"
    break;

  case 223: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 972 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1808 "dhcp6_parser.cc"
    break;

  case 224: // $@34: %empty
#line 978 "dhcp6_parser.yy"
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
#line 984 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1831 "dhcp6_parser.cc"
    break;

  case 226: // $@35: %empty
#line 991 "dhcp6_parser.yy"
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
#line 997 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1854 "dhcp6_parser.cc"
    break;

  case 228: // $@36: %empty
#line 1004 "dhcp6_parser.yy"
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
#line 1010 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1875 "dhcp6_parser.cc"
    break;

  case 234: // not_empty_database_list: not_empty_database_list ","
#line 1021 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1883 "dhcp6_parser.cc"
    break;

  case 235: // $@37: %empty
#line 1026 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1893 "dhcp6_parser.cc"
    break;

  case 236: // database: "{" $@37 database_map_params "}"
#line 1030 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1903 "dhcp6_parser.cc"
    break;

  case 239: // database_map_params: database_map_params ","
#line 1038 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1911 "dhcp6_parser.cc"
    break;

  case 264: // $@38: %empty
#line 1069 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1920 "dhcp6_parser.cc"
    break;

  case 265: // database_type: "type" $@38 ":" "constant string"
#line 1072 "dhcp6_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 1930 "dhcp6_parser.cc"
    break;

  case 266: // $@39: %empty
#line 1078 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1939 "dhcp6_parser.cc"
    break;

  case 267: // user: "user" $@39 ":" "constant string"
#line 1081 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1949 "dhcp6_parser.cc"
    break;

  case 268: // $@40: %empty
#line 1087 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1958 "dhcp6_parser.cc"
    break;

  case 269: // password: "password" $@40 ":" "constant string"
#line 1090 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1968 "dhcp6_parser.cc"
    break;

  case 270: // $@41: %empty
#line 1096 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1977 "dhcp6_parser.cc"
    break;

  case 271: // host: "host" $@41 ":" "constant string"
#line 1099 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1987 "dhcp6_parser.cc"
    break;

  case 272: // port: "port" ":" "integer"
#line 1105 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1997 "dhcp6_parser.cc"
    break;

  case 273: // $@42: %empty
#line 1111 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2006 "dhcp6_parser.cc"
    break;

  case 274: // name: "name" $@42 ":" "constant string"
#line 1114 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2016 "dhcp6_parser.cc"
    break;

  case 275: // persist: "persist" ":" "boolean"
#line 1120 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2026 "dhcp6_parser.cc"
    break;

  case 276: // lfc_interval: "lfc-interval" ":" "integer"
#line 1126 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2036 "dhcp6_parser.cc"
    break;

  case 277: // readonly: "readonly" ":" "boolean"
#line 1132 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2046 "dhcp6_parser.cc"
    break;

  case 278: // connect_timeout: "connect-timeout" ":" "integer"
#line 1138 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2056 "dhcp6_parser.cc"
    break;

  case 279: // read_timeout: "read-timeout" ":" "integer"
#line 1144 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2066 "dhcp6_parser.cc"
    break;

  case 280: // write_timeout: "write-timeout" ":" "integer"
#line 1150 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2076 "dhcp6_parser.cc"
    break;

  case 281: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1156 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2086 "dhcp6_parser.cc"
    break;

  case 282: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1162 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2096 "dhcp6_parser.cc"
    break;

  case 283: // $@43: %empty
#line 1168 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2105 "dhcp6_parser.cc"
    break;

  case 284: // on_fail: "on-fail" $@43 ":" on_fail_mode
#line 1171 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2114 "dhcp6_parser.cc"
    break;

  case 285: // on_fail_mode: "stop-retry-exit"
#line 1176 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2120 "dhcp6_parser.cc"
    break;

  case 286: // on_fail_mode: "serve-retry-exit"
#line 1177 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2126 "dhcp6_parser.cc"
    break;

  case 287: // on_fail_mode: "serve-retry-continue"
#line 1178 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2132 "dhcp6_parser.cc"
    break;

  case 288: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1181 "dhcp6_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2142 "dhcp6_parser.cc"
    break;

  case 289: // max_row_errors: "max-row-errors" ":" "integer"
#line 1187 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2152 "dhcp6_parser.cc"
    break;

  case 290: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1193 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2162 "dhcp6_parser.cc"
    break;

  case 291: // $@44: %empty
#line 1199 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2171 "dhcp6_parser.cc"
    break;

  case 292: // trust_anchor: "trust-anchor" $@44 ":" "constant string"
#line 1202 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2181 "dhcp6_parser.cc"
    break;

  case 293: // $@45: %empty
#line 1208 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2190 "dhcp6_parser.cc"
    break;

  case 294: // cert_file: "cert-file" $@45 ":" "constant string"
#line 1211 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2200 "dhcp6_parser.cc"
    break;

  case 295: // $@46: %empty
#line 1217 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2209 "dhcp6_parser.cc"
    break;

  case 296: // key_file: "key-file" $@46 ":" "constant string"
#line 1220 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2219 "dhcp6_parser.cc"
    break;

  case 297: // $@47: %empty
#line 1226 "dhcp6_parser.yy"
                           {
    ctx.unique("key-password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2228 "dhcp6_parser.cc"
    break;

  case 298: // key_password: "key-password" $@47 ":" "constant string"
#line 1229 "dhcp6_parser.yy"
               {
    ElementPtr key_pass(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-password", key_pass);
    ctx.leave();
}
#line 2238 "dhcp6_parser.cc"
    break;

  case 299: // $@48: %empty
#line 1235 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2247 "dhcp6_parser.cc"
    break;

  case 300: // cipher_list: "cipher-list" $@48 ":" "constant string"
#line 1238 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2257 "dhcp6_parser.cc"
    break;

  case 301: // $@49: %empty
#line 1244 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2269 "dhcp6_parser.cc"
    break;

  case 302: // sanity_checks: "sanity-checks" $@49 ":" "{" sanity_checks_params "}"
#line 1250 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2278 "dhcp6_parser.cc"
    break;

  case 305: // sanity_checks_params: sanity_checks_params ","
#line 1257 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2286 "dhcp6_parser.cc"
    break;

  case 308: // $@50: %empty
#line 1266 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2295 "dhcp6_parser.cc"
    break;

  case 309: // lease_checks: "lease-checks" $@50 ":" "constant string"
#line 1269 "dhcp6_parser.yy"
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
#line 2315 "dhcp6_parser.cc"
    break;

  case 310: // $@51: %empty
#line 1285 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2324 "dhcp6_parser.cc"
    break;

  case 311: // extended_info_checks: "extended-info-checks" $@51 ":" "constant string"
#line 1288 "dhcp6_parser.yy"
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
#line 2343 "dhcp6_parser.cc"
    break;

  case 312: // $@52: %empty
#line 1303 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2355 "dhcp6_parser.cc"
    break;

  case 313: // mac_sources: "mac-sources" $@52 ":" "[" mac_sources_list "]"
#line 1309 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2364 "dhcp6_parser.cc"
    break;

  case 316: // mac_sources_list: mac_sources_list ","
#line 1316 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2372 "dhcp6_parser.cc"
    break;

  case 319: // duid_id: "duid"
#line 1325 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2381 "dhcp6_parser.cc"
    break;

  case 320: // string_id: "constant string"
#line 1330 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2390 "dhcp6_parser.cc"
    break;

  case 321: // $@53: %empty
#line 1335 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2402 "dhcp6_parser.cc"
    break;

  case 322: // host_reservation_identifiers: "host-reservation-identifiers" $@53 ":" "[" host_reservation_identifiers_list "]"
#line 1341 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2411 "dhcp6_parser.cc"
    break;

  case 325: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1348 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2419 "dhcp6_parser.cc"
    break;

  case 329: // hw_address_id: "hw-address"
#line 1358 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2428 "dhcp6_parser.cc"
    break;

  case 330: // flex_id: "flex-id"
#line 1363 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2437 "dhcp6_parser.cc"
    break;

  case 331: // $@54: %empty
#line 1370 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2449 "dhcp6_parser.cc"
    break;

  case 332: // relay_supplied_options: "relay-supplied-options" $@54 ":" "[" list_content "]"
#line 1376 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2458 "dhcp6_parser.cc"
    break;

  case 333: // $@55: %empty
#line 1383 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2470 "dhcp6_parser.cc"
    break;

  case 334: // dhcp_multi_threading: "multi-threading" $@55 ":" "{" multi_threading_params "}"
#line 1389 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2481 "dhcp6_parser.cc"
    break;

  case 337: // multi_threading_params: multi_threading_params ","
#line 1398 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2489 "dhcp6_parser.cc"
    break;

  case 344: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1411 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2499 "dhcp6_parser.cc"
    break;

  case 345: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1417 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2509 "dhcp6_parser.cc"
    break;

  case 346: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1423 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2519 "dhcp6_parser.cc"
    break;

  case 347: // $@56: %empty
#line 1429 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2531 "dhcp6_parser.cc"
    break;

  case 348: // hooks_libraries: "hooks-libraries" $@56 ":" "[" hooks_libraries_list "]"
#line 1435 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2540 "dhcp6_parser.cc"
    break;

  case 353: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1446 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2548 "dhcp6_parser.cc"
    break;

  case 354: // $@57: %empty
#line 1451 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2558 "dhcp6_parser.cc"
    break;

  case 355: // hooks_library: "{" $@57 hooks_params "}"
#line 1455 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2568 "dhcp6_parser.cc"
    break;

  case 356: // $@58: %empty
#line 1461 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2578 "dhcp6_parser.cc"
    break;

  case 357: // sub_hooks_library: "{" $@58 hooks_params "}"
#line 1465 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2588 "dhcp6_parser.cc"
    break;

  case 360: // hooks_params: hooks_params ","
#line 1473 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2596 "dhcp6_parser.cc"
    break;

  case 364: // $@59: %empty
#line 1483 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2605 "dhcp6_parser.cc"
    break;

  case 365: // library: "library" $@59 ":" "constant string"
#line 1486 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2615 "dhcp6_parser.cc"
    break;

  case 366: // $@60: %empty
#line 1492 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2624 "dhcp6_parser.cc"
    break;

  case 367: // parameters: "parameters" $@60 ":" map_value
#line 1495 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2633 "dhcp6_parser.cc"
    break;

  case 368: // $@61: %empty
#line 1501 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2645 "dhcp6_parser.cc"
    break;

  case 369: // expired_leases_processing: "expired-leases-processing" $@61 ":" "{" expired_leases_params "}"
#line 1507 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2655 "dhcp6_parser.cc"
    break;

  case 372: // expired_leases_params: expired_leases_params ","
#line 1515 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2663 "dhcp6_parser.cc"
    break;

  case 379: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1528 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2673 "dhcp6_parser.cc"
    break;

  case 380: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1534 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2683 "dhcp6_parser.cc"
    break;

  case 381: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1540 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2693 "dhcp6_parser.cc"
    break;

  case 382: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1546 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2703 "dhcp6_parser.cc"
    break;

  case 383: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1552 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2713 "dhcp6_parser.cc"
    break;

  case 384: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1558 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2723 "dhcp6_parser.cc"
    break;

  case 385: // $@62: %empty
#line 1567 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2735 "dhcp6_parser.cc"
    break;

  case 386: // subnet6_list: "subnet6" $@62 ":" "[" subnet6_list_content "]"
#line 1573 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2744 "dhcp6_parser.cc"
    break;

  case 391: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1587 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2752 "dhcp6_parser.cc"
    break;

  case 392: // $@63: %empty
#line 1596 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2762 "dhcp6_parser.cc"
    break;

  case 393: // subnet6: "{" $@63 subnet6_params "}"
#line 1600 "dhcp6_parser.yy"
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
#line 2788 "dhcp6_parser.cc"
    break;

  case 394: // $@64: %empty
#line 1622 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2798 "dhcp6_parser.cc"
    break;

  case 395: // sub_subnet6: "{" $@64 subnet6_params "}"
#line 1626 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2808 "dhcp6_parser.cc"
    break;

  case 398: // subnet6_params: subnet6_params ","
#line 1635 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2816 "dhcp6_parser.cc"
    break;

  case 450: // $@65: %empty
#line 1694 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2825 "dhcp6_parser.cc"
    break;

  case 451: // subnet: "subnet" $@65 ":" "constant string"
#line 1697 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2835 "dhcp6_parser.cc"
    break;

  case 452: // $@66: %empty
#line 1703 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2844 "dhcp6_parser.cc"
    break;

  case 453: // interface: "interface" $@66 ":" "constant string"
#line 1706 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2854 "dhcp6_parser.cc"
    break;

  case 454: // $@67: %empty
#line 1712 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2863 "dhcp6_parser.cc"
    break;

  case 455: // interface_id: "interface-id" $@67 ":" "constant string"
#line 1715 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2873 "dhcp6_parser.cc"
    break;

  case 456: // $@68: %empty
#line 1721 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2882 "dhcp6_parser.cc"
    break;

  case 457: // client_class: "client-class" $@68 ":" "constant string"
#line 1724 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2892 "dhcp6_parser.cc"
    break;

  case 458: // $@69: %empty
#line 1731 "dhcp6_parser.yy"
                                       {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2904 "dhcp6_parser.cc"
    break;

  case 459: // network_client_classes: "client-classes" $@69 ":" list_strings
#line 1737 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2913 "dhcp6_parser.cc"
    break;

  case 460: // $@70: %empty
#line 1743 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2925 "dhcp6_parser.cc"
    break;

  case 461: // require_client_classes: "require-client-classes" $@70 ":" list_strings
#line 1749 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2934 "dhcp6_parser.cc"
    break;

  case 462: // $@71: %empty
#line 1754 "dhcp6_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2946 "dhcp6_parser.cc"
    break;

  case 463: // evaluate_additional_classes: "evaluate-additional-classes" $@71 ":" list_strings
#line 1760 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2955 "dhcp6_parser.cc"
    break;

  case 464: // reservations_global: "reservations-global" ":" "boolean"
#line 1765 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2965 "dhcp6_parser.cc"
    break;

  case 465: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1771 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2975 "dhcp6_parser.cc"
    break;

  case 466: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1777 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2985 "dhcp6_parser.cc"
    break;

  case 467: // id: "id" ":" "integer"
#line 1783 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2995 "dhcp6_parser.cc"
    break;

  case 468: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1789 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 3005 "dhcp6_parser.cc"
    break;

  case 469: // $@72: %empty
#line 1797 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3017 "dhcp6_parser.cc"
    break;

  case 470: // shared_networks: "shared-networks" $@72 ":" "[" shared_networks_content "]"
#line 1803 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3026 "dhcp6_parser.cc"
    break;

  case 475: // shared_networks_list: shared_networks_list ","
#line 1816 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3034 "dhcp6_parser.cc"
    break;

  case 476: // $@73: %empty
#line 1821 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3044 "dhcp6_parser.cc"
    break;

  case 477: // shared_network: "{" $@73 shared_network_params "}"
#line 1825 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3052 "dhcp6_parser.cc"
    break;

  case 480: // shared_network_params: shared_network_params ","
#line 1831 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3060 "dhcp6_parser.cc"
    break;

  case 529: // $@74: %empty
#line 1890 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3072 "dhcp6_parser.cc"
    break;

  case 530: // option_def_list: "option-def" $@74 ":" "[" option_def_list_content "]"
#line 1896 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3081 "dhcp6_parser.cc"
    break;

  case 531: // $@75: %empty
#line 1904 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3090 "dhcp6_parser.cc"
    break;

  case 532: // sub_option_def_list: "{" $@75 option_def_list "}"
#line 1907 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 3098 "dhcp6_parser.cc"
    break;

  case 537: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1919 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3106 "dhcp6_parser.cc"
    break;

  case 538: // $@76: %empty
#line 1926 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3116 "dhcp6_parser.cc"
    break;

  case 539: // option_def_entry: "{" $@76 option_def_params "}"
#line 1930 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3128 "dhcp6_parser.cc"
    break;

  case 540: // $@77: %empty
#line 1941 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3138 "dhcp6_parser.cc"
    break;

  case 541: // sub_option_def: "{" $@77 option_def_params "}"
#line 1945 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3150 "dhcp6_parser.cc"
    break;

  case 546: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1961 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3158 "dhcp6_parser.cc"
    break;

  case 558: // code: "code" ":" "integer"
#line 1980 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3168 "dhcp6_parser.cc"
    break;

  case 560: // $@78: %empty
#line 1988 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3177 "dhcp6_parser.cc"
    break;

  case 561: // option_def_type: "type" $@78 ":" "constant string"
#line 1991 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3187 "dhcp6_parser.cc"
    break;

  case 562: // $@79: %empty
#line 1997 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3196 "dhcp6_parser.cc"
    break;

  case 563: // option_def_record_types: "record-types" $@79 ":" "constant string"
#line 2000 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3206 "dhcp6_parser.cc"
    break;

  case 564: // $@80: %empty
#line 2006 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3215 "dhcp6_parser.cc"
    break;

  case 565: // space: "space" $@80 ":" "constant string"
#line 2009 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3225 "dhcp6_parser.cc"
    break;

  case 567: // $@81: %empty
#line 2017 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3234 "dhcp6_parser.cc"
    break;

  case 568: // option_def_encapsulate: "encapsulate" $@81 ":" "constant string"
#line 2020 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3244 "dhcp6_parser.cc"
    break;

  case 569: // option_def_array: "array" ":" "boolean"
#line 2026 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3254 "dhcp6_parser.cc"
    break;

  case 570: // $@82: %empty
#line 2036 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3266 "dhcp6_parser.cc"
    break;

  case 571: // option_data_list: "option-data" $@82 ":" "[" option_data_list_content "]"
#line 2042 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3275 "dhcp6_parser.cc"
    break;

  case 576: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2057 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3283 "dhcp6_parser.cc"
    break;

  case 577: // $@83: %empty
#line 2064 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3293 "dhcp6_parser.cc"
    break;

  case 578: // option_data_entry: "{" $@83 option_data_params "}"
#line 2068 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3302 "dhcp6_parser.cc"
    break;

  case 579: // $@84: %empty
#line 2076 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3312 "dhcp6_parser.cc"
    break;

  case 580: // sub_option_data: "{" $@84 option_data_params "}"
#line 2080 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3321 "dhcp6_parser.cc"
    break;

  case 585: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2096 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3329 "dhcp6_parser.cc"
    break;

  case 598: // $@85: %empty
#line 2118 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3338 "dhcp6_parser.cc"
    break;

  case 599: // option_data_data: "data" $@85 ":" "constant string"
#line 2121 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3348 "dhcp6_parser.cc"
    break;

  case 602: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2131 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3358 "dhcp6_parser.cc"
    break;

  case 603: // option_data_always_send: "always-send" ":" "boolean"
#line 2137 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3368 "dhcp6_parser.cc"
    break;

  case 604: // option_data_never_send: "never-send" ":" "boolean"
#line 2143 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3378 "dhcp6_parser.cc"
    break;

  case 605: // $@86: %empty
#line 2149 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3390 "dhcp6_parser.cc"
    break;

  case 606: // option_data_client_classes: "client-classes" $@86 ":" list_strings
#line 2155 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3399 "dhcp6_parser.cc"
    break;

  case 607: // $@87: %empty
#line 2163 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3411 "dhcp6_parser.cc"
    break;

  case 608: // pools_list: "pools" $@87 ":" "[" pools_list_content "]"
#line 2169 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3420 "dhcp6_parser.cc"
    break;

  case 613: // not_empty_pools_list: not_empty_pools_list ","
#line 2182 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3428 "dhcp6_parser.cc"
    break;

  case 614: // $@88: %empty
#line 2187 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3438 "dhcp6_parser.cc"
    break;

  case 615: // pool_list_entry: "{" $@88 pool_params "}"
#line 2191 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3448 "dhcp6_parser.cc"
    break;

  case 616: // $@89: %empty
#line 2197 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3458 "dhcp6_parser.cc"
    break;

  case 617: // sub_pool6: "{" $@89 pool_params "}"
#line 2201 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3468 "dhcp6_parser.cc"
    break;

  case 620: // pool_params: pool_params ","
#line 2209 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3476 "dhcp6_parser.cc"
    break;

  case 645: // $@90: %empty
#line 2240 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3485 "dhcp6_parser.cc"
    break;

  case 646: // pool_entry: "pool" $@90 ":" "constant string"
#line 2243 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3495 "dhcp6_parser.cc"
    break;

  case 647: // pool_id: "pool-id" ":" "integer"
#line 2249 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3505 "dhcp6_parser.cc"
    break;

  case 648: // $@91: %empty
#line 2255 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3513 "dhcp6_parser.cc"
    break;

  case 649: // user_context: "user-context" $@91 ":" map_value
#line 2257 "dhcp6_parser.yy"
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
#line 3540 "dhcp6_parser.cc"
    break;

  case 650: // $@92: %empty
#line 2280 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3548 "dhcp6_parser.cc"
    break;

  case 651: // comment: "comment" $@92 ":" "constant string"
#line 2282 "dhcp6_parser.yy"
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
#line 3577 "dhcp6_parser.cc"
    break;

  case 652: // $@93: %empty
#line 2310 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3589 "dhcp6_parser.cc"
    break;

  case 653: // pd_pools_list: "pd-pools" $@93 ":" "[" pd_pools_list_content "]"
#line 2316 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3598 "dhcp6_parser.cc"
    break;

  case 658: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2329 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3606 "dhcp6_parser.cc"
    break;

  case 659: // $@94: %empty
#line 2334 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3616 "dhcp6_parser.cc"
    break;

  case 660: // pd_pool_entry: "{" $@94 pd_pool_params "}"
#line 2338 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3628 "dhcp6_parser.cc"
    break;

  case 661: // $@95: %empty
#line 2346 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3638 "dhcp6_parser.cc"
    break;

  case 662: // sub_pd_pool: "{" $@95 pd_pool_params "}"
#line 2350 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3650 "dhcp6_parser.cc"
    break;

  case 665: // pd_pool_params: pd_pool_params ","
#line 2360 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3658 "dhcp6_parser.cc"
    break;

  case 680: // $@96: %empty
#line 2381 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3667 "dhcp6_parser.cc"
    break;

  case 681: // pd_prefix: "prefix" $@96 ":" "constant string"
#line 2384 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3677 "dhcp6_parser.cc"
    break;

  case 682: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2390 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3687 "dhcp6_parser.cc"
    break;

  case 683: // $@97: %empty
#line 2396 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3696 "dhcp6_parser.cc"
    break;

  case 684: // excluded_prefix: "excluded-prefix" $@97 ":" "constant string"
#line 2399 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3706 "dhcp6_parser.cc"
    break;

  case 685: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2405 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3716 "dhcp6_parser.cc"
    break;

  case 686: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2411 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3726 "dhcp6_parser.cc"
    break;

  case 687: // $@98: %empty
#line 2420 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3738 "dhcp6_parser.cc"
    break;

  case 688: // reservations: "reservations" $@98 ":" "[" reservations_list "]"
#line 2426 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3747 "dhcp6_parser.cc"
    break;

  case 693: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2437 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3755 "dhcp6_parser.cc"
    break;

  case 694: // $@99: %empty
#line 2442 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3765 "dhcp6_parser.cc"
    break;

  case 695: // reservation: "{" $@99 reservation_params "}"
#line 2446 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3774 "dhcp6_parser.cc"
    break;

  case 696: // $@100: %empty
#line 2451 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3784 "dhcp6_parser.cc"
    break;

  case 697: // sub_reservation: "{" $@100 reservation_params "}"
#line 2455 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3793 "dhcp6_parser.cc"
    break;

  case 702: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2466 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3801 "dhcp6_parser.cc"
    break;

  case 715: // $@101: %empty
#line 2486 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3813 "dhcp6_parser.cc"
    break;

  case 716: // ip_addresses: "ip-addresses" $@101 ":" list_strings
#line 2492 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3822 "dhcp6_parser.cc"
    break;

  case 717: // $@102: %empty
#line 2497 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3834 "dhcp6_parser.cc"
    break;

  case 718: // prefixes: "prefixes" $@102 ":" list_strings
#line 2503 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3843 "dhcp6_parser.cc"
    break;

  case 719: // $@103: %empty
#line 2508 "dhcp6_parser.yy"
                                     {
    ctx.unique("excluded-prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3855 "dhcp6_parser.cc"
    break;

  case 720: // excluded_prefixes: "excluded-prefixes" $@103 ":" list_strings
#line 2514 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3864 "dhcp6_parser.cc"
    break;

  case 721: // $@104: %empty
#line 2519 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3873 "dhcp6_parser.cc"
    break;

  case 722: // duid: "duid" $@104 ":" "constant string"
#line 2522 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3883 "dhcp6_parser.cc"
    break;

  case 723: // $@105: %empty
#line 2528 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3892 "dhcp6_parser.cc"
    break;

  case 724: // hw_address: "hw-address" $@105 ":" "constant string"
#line 2531 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3902 "dhcp6_parser.cc"
    break;

  case 725: // $@106: %empty
#line 2537 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3911 "dhcp6_parser.cc"
    break;

  case 726: // hostname: "hostname" $@106 ":" "constant string"
#line 2540 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3921 "dhcp6_parser.cc"
    break;

  case 727: // $@107: %empty
#line 2546 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3930 "dhcp6_parser.cc"
    break;

  case 728: // flex_id_value: "flex-id" $@107 ":" "constant string"
#line 2549 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3940 "dhcp6_parser.cc"
    break;

  case 729: // $@108: %empty
#line 2555 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3952 "dhcp6_parser.cc"
    break;

  case 730: // reservation_client_classes: "client-classes" $@108 ":" list_strings
#line 2561 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3961 "dhcp6_parser.cc"
    break;

  case 731: // $@109: %empty
#line 2569 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3973 "dhcp6_parser.cc"
    break;

  case 732: // relay: "relay" $@109 ":" "{" relay_map "}"
#line 2575 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3982 "dhcp6_parser.cc"
    break;

  case 734: // $@110: %empty
#line 2586 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3994 "dhcp6_parser.cc"
    break;

  case 735: // client_classes: "client-classes" $@110 ":" "[" client_classes_list "]"
#line 2592 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4003 "dhcp6_parser.cc"
    break;

  case 738: // client_classes_list: client_classes_list ","
#line 2599 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 4011 "dhcp6_parser.cc"
    break;

  case 739: // $@111: %empty
#line 2604 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4021 "dhcp6_parser.cc"
    break;

  case 740: // client_class_entry: "{" $@111 client_class_params "}"
#line 2608 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 4031 "dhcp6_parser.cc"
    break;

  case 745: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2620 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 4039 "dhcp6_parser.cc"
    break;

  case 762: // $@112: %empty
#line 2644 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4048 "dhcp6_parser.cc"
    break;

  case 763: // client_class_test: "test" $@112 ":" "constant string"
#line 2647 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4058 "dhcp6_parser.cc"
    break;

  case 764: // $@113: %empty
#line 2653 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4067 "dhcp6_parser.cc"
    break;

  case 765: // client_class_template_test: "template-test" $@113 ":" "constant string"
#line 2656 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4077 "dhcp6_parser.cc"
    break;

  case 766: // only_if_required: "only-if-required" ":" "boolean"
#line 2663 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4087 "dhcp6_parser.cc"
    break;

  case 767: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2669 "dhcp6_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4097 "dhcp6_parser.cc"
    break;

  case 768: // $@114: %empty
#line 2678 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 4109 "dhcp6_parser.cc"
    break;

  case 769: // server_id: "server-id" $@114 ":" "{" server_id_params "}"
#line 2684 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4120 "dhcp6_parser.cc"
    break;

  case 772: // server_id_params: server_id_params ","
#line 2693 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4128 "dhcp6_parser.cc"
    break;

  case 782: // $@115: %empty
#line 2709 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 4137 "dhcp6_parser.cc"
    break;

  case 783: // server_id_type: "type" $@115 ":" duid_type
#line 2712 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4146 "dhcp6_parser.cc"
    break;

  case 784: // duid_type: "LLT"
#line 2717 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4152 "dhcp6_parser.cc"
    break;

  case 785: // duid_type: "EN"
#line 2718 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4158 "dhcp6_parser.cc"
    break;

  case 786: // duid_type: "LL"
#line 2719 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4164 "dhcp6_parser.cc"
    break;

  case 787: // htype: "htype" ":" "integer"
#line 2722 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4174 "dhcp6_parser.cc"
    break;

  case 788: // $@116: %empty
#line 2728 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4183 "dhcp6_parser.cc"
    break;

  case 789: // identifier: "identifier" $@116 ":" "constant string"
#line 2731 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4193 "dhcp6_parser.cc"
    break;

  case 790: // time: "time" ":" "integer"
#line 2737 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4203 "dhcp6_parser.cc"
    break;

  case 791: // enterprise_id: "enterprise-id" ":" "integer"
#line 2743 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4213 "dhcp6_parser.cc"
    break;

  case 792: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2751 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4223 "dhcp6_parser.cc"
    break;

  case 793: // $@117: %empty
#line 2759 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4236 "dhcp6_parser.cc"
    break;

  case 794: // control_socket: "control-socket" $@117 ":" "{" control_socket_params "}"
#line 2766 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4245 "dhcp6_parser.cc"
    break;

  case 795: // $@118: %empty
#line 2771 "dhcp6_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4258 "dhcp6_parser.cc"
    break;

  case 796: // control_sockets: "control-sockets" $@118 ":" "[" control_socket_list "]"
#line 2778 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4267 "dhcp6_parser.cc"
    break;

  case 801: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2789 "dhcp6_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4275 "dhcp6_parser.cc"
    break;

  case 802: // $@119: %empty
#line 2794 "dhcp6_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4285 "dhcp6_parser.cc"
    break;

  case 803: // control_socket_entry: "{" $@119 control_socket_params "}"
#line 2798 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4293 "dhcp6_parser.cc"
    break;

  case 806: // control_socket_params: control_socket_params ","
#line 2804 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4301 "dhcp6_parser.cc"
    break;

  case 820: // $@120: %empty
#line 2824 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4310 "dhcp6_parser.cc"
    break;

  case 821: // control_socket_type: "socket-type" $@120 ":" control_socket_type_value
#line 2827 "dhcp6_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4319 "dhcp6_parser.cc"
    break;

  case 822: // control_socket_type_value: "unix"
#line 2833 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4325 "dhcp6_parser.cc"
    break;

  case 823: // control_socket_type_value: "http"
#line 2834 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4331 "dhcp6_parser.cc"
    break;

  case 824: // control_socket_type_value: "https"
#line 2835 "dhcp6_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4337 "dhcp6_parser.cc"
    break;

  case 825: // $@121: %empty
#line 2838 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4347 "dhcp6_parser.cc"
    break;

  case 826: // control_socket_name: "socket-name" $@121 ":" "constant string"
#line 2842 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4357 "dhcp6_parser.cc"
    break;

  case 827: // $@122: %empty
#line 2848 "dhcp6_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4367 "dhcp6_parser.cc"
    break;

  case 828: // control_socket_address: "socket-address" $@122 ":" "constant string"
#line 2852 "dhcp6_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4377 "dhcp6_parser.cc"
    break;

  case 829: // control_socket_port: "socket-port" ":" "integer"
#line 2858 "dhcp6_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4387 "dhcp6_parser.cc"
    break;

  case 830: // cert_required: "cert-required" ":" "boolean"
#line 2864 "dhcp6_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4397 "dhcp6_parser.cc"
    break;

  case 831: // $@123: %empty
#line 2870 "dhcp6_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4409 "dhcp6_parser.cc"
    break;

  case 832: // http_headers: "http-headers" $@123 ":" "[" http_header_list "]"
#line 2876 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4418 "dhcp6_parser.cc"
    break;

  case 837: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2887 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4426 "dhcp6_parser.cc"
    break;

  case 838: // $@124: %empty
#line 2892 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4436 "dhcp6_parser.cc"
    break;

  case 839: // http_header: "{" $@124 http_header_params "}"
#line 2896 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4444 "dhcp6_parser.cc"
    break;

  case 842: // http_header_params: http_header_params ","
#line 2902 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4452 "dhcp6_parser.cc"
    break;

  case 848: // $@125: %empty
#line 2914 "dhcp6_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4461 "dhcp6_parser.cc"
    break;

  case 849: // header_value: "value" $@125 ":" "constant string"
#line 2917 "dhcp6_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4471 "dhcp6_parser.cc"
    break;

  case 850: // $@126: %empty
#line 2925 "dhcp6_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4483 "dhcp6_parser.cc"
    break;

  case 851: // authentication: "authentication" $@126 ":" "{" auth_params "}"
#line 2931 "dhcp6_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4494 "dhcp6_parser.cc"
    break;

  case 854: // auth_params: auth_params ","
#line 2940 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4502 "dhcp6_parser.cc"
    break;

  case 862: // $@127: %empty
#line 2954 "dhcp6_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4511 "dhcp6_parser.cc"
    break;

  case 863: // auth_type: "type" $@127 ":" auth_type_value
#line 2957 "dhcp6_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4520 "dhcp6_parser.cc"
    break;

  case 864: // auth_type_value: "basic"
#line 2962 "dhcp6_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4526 "dhcp6_parser.cc"
    break;

  case 865: // $@128: %empty
#line 2965 "dhcp6_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4535 "dhcp6_parser.cc"
    break;

  case 866: // realm: "realm" $@128 ":" "constant string"
#line 2968 "dhcp6_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4545 "dhcp6_parser.cc"
    break;

  case 867: // $@129: %empty
#line 2974 "dhcp6_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4554 "dhcp6_parser.cc"
    break;

  case 868: // directory: "directory" $@129 ":" "constant string"
#line 2977 "dhcp6_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4564 "dhcp6_parser.cc"
    break;

  case 869: // $@130: %empty
#line 2983 "dhcp6_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4576 "dhcp6_parser.cc"
    break;

  case 870: // clients: "clients" $@130 ":" "[" clients_list "]"
#line 2989 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4585 "dhcp6_parser.cc"
    break;

  case 875: // not_empty_clients_list: not_empty_clients_list ","
#line 3000 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4593 "dhcp6_parser.cc"
    break;

  case 876: // $@131: %empty
#line 3005 "dhcp6_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4603 "dhcp6_parser.cc"
    break;

  case 877: // basic_auth: "{" $@131 clients_params "}"
#line 3009 "dhcp6_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4611 "dhcp6_parser.cc"
    break;

  case 880: // clients_params: clients_params ","
#line 3015 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4619 "dhcp6_parser.cc"
    break;

  case 888: // $@132: %empty
#line 3029 "dhcp6_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4628 "dhcp6_parser.cc"
    break;

  case 889: // user_file: "user-file" $@132 ":" "constant string"
#line 3032 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4638 "dhcp6_parser.cc"
    break;

  case 890: // $@133: %empty
#line 3038 "dhcp6_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4647 "dhcp6_parser.cc"
    break;

  case 891: // password_file: "password-file" $@133 ":" "constant string"
#line 3041 "dhcp6_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4657 "dhcp6_parser.cc"
    break;

  case 892: // $@134: %empty
#line 3049 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4669 "dhcp6_parser.cc"
    break;

  case 893: // dhcp_queue_control: "dhcp-queue-control" $@134 ":" "{" queue_control_params "}"
#line 3055 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4680 "dhcp6_parser.cc"
    break;

  case 896: // queue_control_params: queue_control_params ","
#line 3064 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4688 "dhcp6_parser.cc"
    break;

  case 903: // enable_queue: "enable-queue" ":" "boolean"
#line 3077 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4698 "dhcp6_parser.cc"
    break;

  case 904: // $@135: %empty
#line 3083 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4707 "dhcp6_parser.cc"
    break;

  case 905: // queue_type: "queue-type" $@135 ":" "constant string"
#line 3086 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4717 "dhcp6_parser.cc"
    break;

  case 906: // capacity: "capacity" ":" "integer"
#line 3092 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4727 "dhcp6_parser.cc"
    break;

  case 907: // $@136: %empty
#line 3098 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4736 "dhcp6_parser.cc"
    break;

  case 908: // arbitrary_map_entry: "constant string" $@136 ":" value
#line 3101 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4745 "dhcp6_parser.cc"
    break;

  case 909: // $@137: %empty
#line 3108 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4757 "dhcp6_parser.cc"
    break;

  case 910: // dhcp_ddns: "dhcp-ddns" $@137 ":" "{" dhcp_ddns_params "}"
#line 3114 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4768 "dhcp6_parser.cc"
    break;

  case 911: // $@138: %empty
#line 3121 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4778 "dhcp6_parser.cc"
    break;

  case 912: // sub_dhcp_ddns: "{" $@138 dhcp_ddns_params "}"
#line 3125 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4788 "dhcp6_parser.cc"
    break;

  case 915: // dhcp_ddns_params: dhcp_ddns_params ","
#line 3133 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4796 "dhcp6_parser.cc"
    break;

  case 927: // enable_updates: "enable-updates" ":" "boolean"
#line 3151 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4806 "dhcp6_parser.cc"
    break;

  case 928: // $@139: %empty
#line 3157 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4815 "dhcp6_parser.cc"
    break;

  case 929: // server_ip: "server-ip" $@139 ":" "constant string"
#line 3160 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4825 "dhcp6_parser.cc"
    break;

  case 930: // server_port: "server-port" ":" "integer"
#line 3166 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4835 "dhcp6_parser.cc"
    break;

  case 931: // $@140: %empty
#line 3172 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4844 "dhcp6_parser.cc"
    break;

  case 932: // sender_ip: "sender-ip" $@140 ":" "constant string"
#line 3175 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4854 "dhcp6_parser.cc"
    break;

  case 933: // sender_port: "sender-port" ":" "integer"
#line 3181 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4864 "dhcp6_parser.cc"
    break;

  case 934: // max_queue_size: "max-queue-size" ":" "integer"
#line 3187 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4874 "dhcp6_parser.cc"
    break;

  case 935: // $@141: %empty
#line 3193 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4883 "dhcp6_parser.cc"
    break;

  case 936: // ncr_protocol: "ncr-protocol" $@141 ":" ncr_protocol_value
#line 3196 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4892 "dhcp6_parser.cc"
    break;

  case 937: // ncr_protocol_value: "UDP"
#line 3202 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4898 "dhcp6_parser.cc"
    break;

  case 938: // ncr_protocol_value: "TCP"
#line 3203 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4904 "dhcp6_parser.cc"
    break;

  case 939: // $@142: %empty
#line 3206 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4913 "dhcp6_parser.cc"
    break;

  case 940: // ncr_format: "ncr-format" $@142 ":" "JSON"
#line 3209 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4923 "dhcp6_parser.cc"
    break;

  case 941: // $@143: %empty
#line 3217 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4935 "dhcp6_parser.cc"
    break;

  case 942: // config_control: "config-control" $@143 ":" "{" config_control_params "}"
#line 3223 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4945 "dhcp6_parser.cc"
    break;

  case 943: // $@144: %empty
#line 3229 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4955 "dhcp6_parser.cc"
    break;

  case 944: // sub_config_control: "{" $@144 config_control_params "}"
#line 3233 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4964 "dhcp6_parser.cc"
    break;

  case 947: // config_control_params: config_control_params ","
#line 3241 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4972 "dhcp6_parser.cc"
    break;

  case 950: // $@145: %empty
#line 3251 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4984 "dhcp6_parser.cc"
    break;

  case 951: // config_databases: "config-databases" $@145 ":" "[" database_list "]"
#line 3257 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4993 "dhcp6_parser.cc"
    break;

  case 952: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3262 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 5003 "dhcp6_parser.cc"
    break;

  case 953: // $@146: %empty
#line 3270 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 5015 "dhcp6_parser.cc"
    break;

  case 954: // loggers: "loggers" $@146 ":" "[" loggers_entries "]"
#line 3276 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5024 "dhcp6_parser.cc"
    break;

  case 957: // loggers_entries: loggers_entries ","
#line 3285 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 5032 "dhcp6_parser.cc"
    break;

  case 958: // $@147: %empty
#line 3291 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 5042 "dhcp6_parser.cc"
    break;

  case 959: // logger_entry: "{" $@147 logger_params "}"
#line 3295 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 5050 "dhcp6_parser.cc"
    break;

  case 962: // logger_params: logger_params ","
#line 3301 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 5058 "dhcp6_parser.cc"
    break;

  case 970: // debuglevel: "debuglevel" ":" "integer"
#line 3315 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 5068 "dhcp6_parser.cc"
    break;

  case 971: // $@148: %empty
#line 3321 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5077 "dhcp6_parser.cc"
    break;

  case 972: // severity: "severity" $@148 ":" "constant string"
#line 3324 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 5087 "dhcp6_parser.cc"
    break;

  case 973: // $@149: %empty
#line 3330 "dhcp6_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 5099 "dhcp6_parser.cc"
    break;

  case 974: // output_options_list: "output-options" $@149 ":" "[" output_options_list_content "]"
#line 3336 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5108 "dhcp6_parser.cc"
    break;

  case 977: // output_options_list_content: output_options_list_content ","
#line 3343 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 5116 "dhcp6_parser.cc"
    break;

  case 978: // $@150: %empty
#line 3348 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 5126 "dhcp6_parser.cc"
    break;

  case 979: // output_entry: "{" $@150 output_params_list "}"
#line 3352 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 5134 "dhcp6_parser.cc"
    break;

  case 982: // output_params_list: output_params_list ","
#line 3358 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 5142 "dhcp6_parser.cc"
    break;

  case 988: // $@151: %empty
#line 3370 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5151 "dhcp6_parser.cc"
    break;

  case 989: // output: "output" $@151 ":" "constant string"
#line 3373 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5161 "dhcp6_parser.cc"
    break;

  case 990: // flush: "flush" ":" "boolean"
#line 3379 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5171 "dhcp6_parser.cc"
    break;

  case 991: // maxsize: "maxsize" ":" "integer"
#line 3385 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5181 "dhcp6_parser.cc"
    break;

  case 992: // maxver: "maxver" ":" "integer"
#line 3391 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5191 "dhcp6_parser.cc"
    break;

  case 993: // $@152: %empty
#line 3397 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5200 "dhcp6_parser.cc"
    break;

  case 994: // pattern: "pattern" $@152 ":" "constant string"
#line 3400 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5210 "dhcp6_parser.cc"
    break;

  case 995: // $@153: %empty
#line 3406 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5222 "dhcp6_parser.cc"
    break;

  case 996: // compatibility: "compatibility" $@153 ":" "{" compatibility_params "}"
#line 3412 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5231 "dhcp6_parser.cc"
    break;

  case 999: // compatibility_params: compatibility_params ","
#line 3419 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5239 "dhcp6_parser.cc"
    break;

  case 1002: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3428 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5249 "dhcp6_parser.cc"
    break;


#line 5253 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1434;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     710, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434,    35,    43,    44,   117,   158,
     176,   182,   189,   209,   211,   239,   245,   255,   265,   279,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,    43,  -186,
      59,   763,    62,  1442,   173,   610,   260,    10,    16,   640,
     -74,   273,    89, -1434,   135,   124,   170,   286,   304, -1434,
      64, -1434, -1434, -1434, -1434, -1434, -1434, -1434,   307,   324,
     349,   351,   373,   380,   383,   386,   399,   409,   451,   483,
     490,   492, -1434,   495,   505,   506,   508,   512, -1434, -1434,
   -1434,   514,   516,   517,   519,   523,   524,   526, -1434, -1434,
   -1434,   527, -1434, -1434, -1434, -1434, -1434, -1434,   530,   531,
     533, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
     534, -1434, -1434, -1434, -1434, -1434, -1434, -1434,   537,   539,
     543, -1434, -1434,   546, -1434,    80, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,   550,
     553,   555,   556, -1434,    81, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,   559,   561,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434,   134, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,   562,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
     140, -1434, -1434, -1434, -1434, -1434, -1434,   563, -1434,   568,
     569, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
     159, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,   314,
     402, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
     477, -1434, -1434,   570, -1434, -1434, -1434,   572, -1434, -1434,
     571,   404, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434,   573,   574,   578, -1434, -1434,
   -1434, -1434, -1434,   576,   582, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,   174,
   -1434, -1434, -1434,   585, -1434,   588, -1434,   592,   595, -1434,
   -1434, -1434, -1434, -1434,   250, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434,   601,   252, -1434, -1434, -1434,
   -1434,    43,    43, -1434,   371,   603, -1434, -1434,   604,   607,
     611,   613,   614,   617,   378,   388,   391,   392,   393,   396,
     397,   398,   387,   408,   413,   415,   418,   420,   634,   421,
     422,   424,   425,   426,   635,   636,   665,   434,   437,   440,
     444,   447,   452,   443,   678,   681,   683,   454,   688,   689,
     690,   692,   693,   694,   461,   465,   467,   702,   704,   705,
     706,   707,   708,   709,   717,   725,   494,   727,   728,   730,
     734,   741,   742,   743,   513,   515,   518,   748,   750, -1434,
     763, -1434,   751,   520,   521,   528,   535,    62, -1434,   753,
     756,   759,   762,   772,   541,   529,   775,   776,   777,   778,
     779,  1442, -1434,   783,   552,   173, -1434,   785,   554,   787,
     557,   558,   610, -1434,   788,   791,   792,   796,   799,   800,
     801,   802, -1434,   260, -1434,   803,   804,   575,   805,   806,
     842,   609, -1434,    16,   844,   612,   615,   616,   845, -1434,
     640,   847,   848,   236, -1434,   621,   856,   625,   858,   628,
     629,   862,   863,   273, -1434,   864,   633,    89, -1434, -1434,
   -1434,   866,   867,   641,   870,   871,   879,   880,   884, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434,   655, -1434, -1434, -1434, -1434, -1434,  -128,
     656,   657, -1434, -1434, -1434, -1434, -1434, -1434, -1434,   888,
     889,   890, -1434,   661,   663,    57,   894,   893,   666, -1434,
   -1434, -1434,   897,   898,   899,   900,   903,   905,   906,   907,
     908, -1434,   910,   911,   914,   913,   915,   670,   677, -1434,
   -1434, -1434,   916,   919, -1434,   918, -1434, -1434, -1434, -1434,
   -1434,   922,   923,   711,   712,   714, -1434, -1434,   918,   918,
     918,   715,   938, -1434,   716, -1434, -1434,   718, -1434,   719,
   -1434, -1434, -1434,   918,   918,   918,   918,   720,   721,   722,
     723, -1434,   724,   726, -1434,   729,   731,   732, -1434, -1434,
     739, -1434, -1434, -1434,   918, -1434,   740,   893, -1434, -1434,
     744, -1434,   745, -1434, -1434,   274,   671, -1434,   955, -1434,
   -1434,    43,   763, -1434,    89,    62,   177,   177,   956, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,   958,   969,
     970, -1434, -1434, -1434, -1434, -1434, -1434, -1434,   971, -1434,
   -1434, -1434,   -97,    43,   132,   382,   974,   976,   977,    79,
      75,   167,   192,   978,   -56,   273, -1434, -1434,   979,  -178,
   -1434, -1434,   980,   981, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434,   827, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,   956, -1434,
     253,   266,   300, -1434, -1434, -1434, -1434,   909,   985,   986,
     987,   988,   989,   990,   991,   992,   993, -1434,   995,   996,
   -1434, -1434, -1434, -1434, -1434, -1434,   301, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434,   316, -1434,   997,   998, -1434, -1434,   999,  1001, -1434,
   -1434,  1000,  1004, -1434, -1434,  1002,  1006, -1434, -1434,  1005,
    1007, -1434, -1434, -1434,   110, -1434, -1434, -1434,  1008, -1434,
   -1434, -1434,   114, -1434, -1434, -1434, -1434, -1434,   317, -1434,
   -1434, -1434, -1434,   184, -1434, -1434,  1009,  1010, -1434, -1434,
    1011,  1013, -1434,  1014,  1015,  1016,  1017,  1018,  1020,   318,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,  1021,
    1023,  1024, -1434, -1434, -1434, -1434,   326, -1434, -1434, -1434,
   -1434, -1434, -1434,  1026,  1027,  1029, -1434,   339, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434,  1030, -1434,  1034,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434,   340, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434,  1035,  1040, -1434,
    1047, -1434,  1049, -1434, -1434, -1434,   343, -1434, -1434, -1434,
   -1434, -1434,   346, -1434,   289, -1434,  1050, -1434,   354, -1434,
   -1434,   767, -1434,  1051,  1053, -1434, -1434,  1056,  1060, -1434,
   -1434,  1059,  1058, -1434, -1434, -1434,  1065,  1066,  1068,  1071,
     841,   774,   849,   840,   855,   857,   861,   874,   877,   886,
    1079,   865,   892,  1090,  1095,  1116,  1127,  1130,   177, -1434,
   -1434,   177, -1434,   956,  1442, -1434,   958,    16, -1434,   969,
     640, -1434,   970,   365, -1434,   971,   -97, -1434, -1434,   132,
   -1434,  1148,  1151,   382, -1434,   263,   974, -1434,   260, -1434,
     976,   -74, -1434,   977,   925,   930,   932,   935,   937,   939,
      79, -1434,  1173,  1176,   946,   947,   949,    75, -1434,   948,
     954,   968,   167, -1434,  1209,  1210,  1211,   983,  1218,  1003,
    1220,   192, -1434,   192, -1434,   978,  1025,  1221,   994,  1222,
     -56, -1434, -1434,   175,   979, -1434,  1028,  -178, -1434, -1434,
    1223,  1228,   173, -1434,   980,   610, -1434,   981, -1434, -1434,
    1012,  1019,  1033,  1036, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434,   389, -1434, -1434,  1037,  1038,  1039,
    1041,  1042, -1434,   360, -1434,   368, -1434,  1226, -1434,  1227,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434,   401, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434,  1043,  1044, -1434, -1434, -1434,  1233,
    1235, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434,  1232,  1239, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434,  1236, -1434,   403, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434,   347,  1045, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434,   355,  1046,  1048, -1434,  1242, -1434,  1241, -1434,
     442, -1434, -1434,  1052, -1434,    43, -1434, -1434,  1247, -1434,
   -1434, -1434, -1434, -1434,   445, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434,  1054,   446, -1434,   448, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434,   365, -1434, -1434, -1434,  1248,
    1249,  1031,  1032, -1434,   263, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,    88,  1251,
   -1434, -1434, -1434,  1255,  1055,  1257,   175, -1434, -1434, -1434,
   -1434, -1434,  1061,  1063, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434,   449, -1434, -1434, -1434, -1434, -1434,
   -1434,  1258,  1252, -1434,  1260, -1434,  1064, -1434, -1434, -1434,
    1271,  1278,  1280,  1281,    88, -1434,   -18, -1434,  1251,  1279,
   -1434,  1112,  1067,  1069,  1285, -1434, -1434, -1434, -1434, -1434,
   -1434,   468, -1434, -1434, -1434, -1434,   290, -1434, -1434, -1434,
   -1434, -1434,  1286,  1297,   -18, -1434,   121,  1279, -1434, -1434,
    1299,  1303, -1434,  1072, -1434, -1434,  1305,  1308,  1309, -1434,
     481, -1434, -1434, -1434, -1434, -1434, -1434, -1434,    83, -1434,
    1286, -1434,  1310,  1078,  1082,  1084,  1317,   121, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434,   485, -1434, -1434, -1434,
   -1434,  1087, -1434, -1434, -1434,  1089, -1434,  1322,  1323,    83,
   -1434, -1434, -1434,  1093,  1094, -1434, -1434, -1434
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   205,     9,   394,    11,
     616,    13,   661,    15,   696,    17,   531,    19,   540,    21,
     579,    23,   356,    25,   911,    27,   943,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   698,     0,   542,   581,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   144,   941,   203,   224,   226,   228,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   193,     0,     0,     0,     0,     0,   163,   170,
     172,     0,     0,     0,     0,     0,     0,     0,   385,   529,
     570,     0,   196,   198,   176,   469,   648,   650,     0,     0,
       0,   312,   331,   321,   301,   734,   687,   347,   368,   768,
       0,   333,   793,   795,   892,   909,   186,   188,     0,     0,
       0,   953,   995,     0,   143,     0,    69,    72,    73,    74,
      75,    76,    77,    78,    79,    80,   111,   112,   113,   114,
     115,    81,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   117,   118,   132,   133,   134,
     107,   140,   141,   142,   136,   137,   138,    84,    85,    86,
      87,   104,    88,    90,    89,   135,    94,    95,    82,   108,
     109,   110,    83,    92,    93,   102,   103,   105,    91,    96,
      97,    98,    99,   100,   101,   106,   116,   139,   218,     0,
       0,     0,     0,   217,     0,   207,   210,   211,   212,   213,
     214,   215,   216,   607,   652,   450,   452,   454,     0,     0,
     458,   460,   462,   456,   731,   449,   399,   400,   401,   402,
     403,   404,   405,   406,   426,   427,   428,   429,   430,   433,
     434,   435,   436,   437,   438,   439,   440,   441,   442,   443,
     444,   445,   431,   432,   446,   447,   448,     0,   396,   410,
     411,   412,   415,   416,   417,   418,   420,   421,   422,   413,
     414,   407,   408,   424,   425,   409,   419,   423,   645,     0,
     644,   628,   629,   630,   631,   632,   633,   634,   635,   636,
     637,   638,   639,   640,   641,   624,   625,   626,   627,   623,
       0,   618,   621,   622,   642,   643,   680,     0,   683,     0,
       0,   679,   671,   672,   673,   674,   670,   669,   677,   678,
       0,   663,   666,   667,   675,   676,   668,   729,   715,   717,
     719,   721,   723,   725,   727,   714,   711,   712,   713,     0,
     699,   700,   705,   706,   707,   703,   708,   709,   710,   704,
       0,   560,   273,     0,   564,   562,   567,     0,   556,   557,
       0,   543,   544,   547,   559,   548,   549,   550,   566,   551,
     552,   553,   554,   555,   598,     0,     0,     0,   605,   596,
     597,   600,   601,     0,   582,   583,   586,   587,   588,   589,
     590,   591,   592,   595,   593,   594,   364,   366,   361,     0,
     358,   362,   363,     0,   928,     0,   931,     0,     0,   935,
     939,   926,   924,   925,     0,   913,   916,   917,   918,   919,
     920,   921,   922,   923,   950,     0,     0,   945,   948,   949,
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
       0,   398,   395,     0,     0,   620,   617,     0,     0,     0,
       0,     0,   665,   662,     0,     0,     0,     0,     0,     0,
       0,     0,   697,   702,   532,     0,     0,     0,     0,     0,
       0,     0,   541,   546,     0,     0,     0,     0,     0,   580,
     585,     0,     0,   360,   357,     0,     0,     0,     0,     0,
       0,     0,     0,   915,   912,     0,     0,   947,   944,    51,
      43,     0,     0,     0,     0,     0,     0,     0,     0,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,     0,   191,   192,   160,   161,   162,     0,
       0,     0,   174,   175,   182,   183,   184,   185,   190,     0,
       0,     0,   195,     0,     0,     0,     0,     0,     0,   464,
     465,   466,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   792,     0,     0,     0,     0,     0,     0,     0,   200,
     201,   202,     0,     0,    70,     0,   220,   221,   222,   223,
     208,     0,     0,     0,     0,     0,   467,   468,     0,     0,
       0,     0,     0,   397,     0,   647,   619,     0,   682,     0,
     685,   686,   664,     0,     0,     0,     0,     0,     0,     0,
       0,   701,     0,     0,   558,     0,     0,     0,   569,   545,
       0,   602,   603,   604,     0,   584,     0,     0,   359,   927,
       0,   930,     0,   933,   934,     0,     0,   914,     0,   952,
     946,     0,     0,   145,     0,     0,     0,     0,   230,   194,
     165,   166,   167,   168,   169,   164,   171,   173,   387,   533,
     572,   197,   199,   178,   179,   180,   181,   177,   471,    40,
     649,   651,     0,    48,     0,     0,     0,   689,   349,     0,
       0,     0,     0,   797,     0,     0,   187,   189,     0,     0,
      53,   219,   609,   654,   451,   453,   455,   459,   461,   463,
     457,     0,   646,   681,   684,   730,   716,   718,   720,   722,
     724,   726,   728,   561,   274,   565,   563,   568,   599,   606,
     365,   367,   929,   932,   937,   938,   936,   940,   230,    44,
       0,     0,     0,   264,   266,   268,   270,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   283,     0,     0,
     291,   293,   295,   297,   299,   263,     0,   237,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   254,   255,   256,   257,   253,   258,   259,   260,   261,
     262,     0,   235,     0,   231,   232,   392,     0,   388,   389,
     538,     0,   534,   535,   577,     0,   573,   574,   476,     0,
     472,   473,   319,   320,     0,   314,   317,   318,     0,   329,
     330,   326,     0,   323,   327,   328,   308,   310,     0,   303,
     306,   307,   739,     0,   736,   694,     0,   690,   691,   354,
       0,   350,   351,     0,     0,     0,     0,     0,     0,     0,
     370,   373,   374,   375,   376,   377,   378,   782,   788,     0,
       0,     0,   781,   778,   779,   780,     0,   770,   773,   776,
     774,   775,   777,     0,     0,     0,   343,     0,   335,   338,
     339,   340,   341,   342,   820,   825,   827,     0,   850,     0,
     831,   819,   812,   813,   814,   817,   818,     0,   804,   807,
     808,   809,   810,   815,   816,   811,   802,     0,   798,   799,
       0,   904,     0,   907,   900,   901,     0,   894,   897,   898,
     899,   902,     0,   958,     0,   955,     0,  1001,     0,   997,
    1000,    55,   614,     0,   610,   611,   659,     0,   655,   656,
     733,     0,     0,    64,   942,   204,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   239,   225,
     227,     0,   229,   234,     0,   386,   391,   542,   530,   537,
     581,   571,   576,     0,   470,   475,   316,   313,   332,   325,
     322,     0,     0,   305,   302,   741,   738,   735,   698,   688,
     693,     0,   348,   353,     0,     0,     0,     0,     0,     0,
     372,   369,     0,     0,     0,     0,     0,   772,   769,     0,
       0,     0,   337,   334,     0,     0,     0,     0,     0,     0,
       0,   806,   794,     0,   796,   801,     0,     0,     0,     0,
     896,   893,   910,     0,   957,   954,     0,   999,   996,    57,
       0,    56,     0,   608,   613,     0,   653,   658,   732,   951,
       0,     0,     0,     0,   272,   275,   276,   277,   278,   279,
     280,   281,   290,   282,     0,   288,   289,     0,     0,     0,
       0,     0,   238,     0,   233,     0,   390,     0,   536,     0,
     575,   528,   496,   497,   498,   500,   501,   502,   485,   486,
     505,   506,   507,   508,   509,   512,   513,   514,   515,   516,
     517,   518,   519,   520,   521,   522,   523,   524,   510,   511,
     525,   526,   527,   481,   482,   483,   484,   492,   493,   494,
     495,   489,   490,   491,   499,     0,   478,   487,   503,   504,
     488,   474,   315,   324,     0,     0,   304,   762,   764,     0,
       0,   760,   754,   755,   756,   757,   758,   759,   761,   751,
     752,   753,     0,   742,   743,   746,   747,   748,   749,   750,
     737,     0,   692,     0,   352,   379,   380,   381,   382,   383,
     384,   371,     0,     0,   787,   790,   791,   771,   344,   345,
     346,   336,     0,     0,     0,   829,     0,   830,     0,   805,
       0,   800,   903,     0,   906,     0,   895,   973,     0,   971,
     969,   963,   967,   968,     0,   960,   965,   966,   964,   956,
    1002,   998,    54,    59,     0,   612,     0,   657,   265,   267,
     269,   271,   285,   286,   287,   284,   292,   294,   296,   298,
     300,   236,   393,   539,   578,   480,   477,   309,   311,     0,
       0,     0,     0,   740,   745,   695,   355,   784,   785,   786,
     783,   789,   822,   823,   824,   821,   826,   828,     0,   833,
     803,   905,   908,     0,     0,     0,   962,   959,    58,   615,
     660,   479,     0,     0,   766,   767,   744,   862,   865,   867,
     869,   861,   860,   859,     0,   852,   855,   856,   857,   858,
     838,     0,   834,   835,     0,   970,     0,   961,   763,   765,
       0,     0,     0,     0,   854,   851,     0,   832,   837,     0,
     972,     0,     0,     0,     0,   853,   848,   847,   843,   845,
     846,     0,   840,   844,   836,   978,     0,   975,   864,   863,
     866,   868,   871,     0,   842,   839,     0,   977,   974,   876,
       0,   872,   873,     0,   841,   988,     0,     0,     0,   993,
       0,   980,   983,   984,   985,   986,   987,   976,     0,   870,
     875,   849,     0,     0,     0,     0,     0,   982,   979,   888,
     890,   887,   881,   883,   885,   886,     0,   878,   882,   884,
     874,     0,   990,   991,   992,     0,   981,     0,     0,   880,
     877,   989,   994,     0,     0,   879,   889,   891
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434,   -10, -1434,  -634, -1434,
     577, -1434, -1434, -1434, -1434,   532, -1434,  -132, -1434, -1434,
   -1434,   -71, -1434, -1434, -1434, -1434, -1434, -1434, -1434,   565,
     781, -1434, -1434,     4,    12,    22,    38,    41,    42,   -57,
     -54,   -35,   -15,    97,   100,   102, -1434,    20,    23,    45,
      48, -1434, -1434,    55, -1434,    60, -1434,    66,   103,    71,
   -1434, -1434,    73,    76,    78,    84,    90, -1434,    95, -1434,
     105, -1434, -1434, -1434, -1434, -1434,   107, -1434,   108, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434,   564,   786, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434,   475, -1434,   247, -1434,  -756,   254, -1434, -1434, -1433,
   -1434, -1432, -1434, -1434, -1434, -1434,   -55, -1434,  -797, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434,  -801, -1434,  -795, -1434,  -792, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434,   225, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434,   238,  -782, -1434, -1434, -1434, -1434,   240,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434,   205, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434,   228, -1434, -1434, -1434,   227,
     746, -1434, -1434, -1434, -1434, -1434, -1434, -1434,   223, -1434,
   -1434, -1434, -1434, -1434, -1434, -1078, -1434, -1434, -1434,   259,
   -1434, -1434, -1434,   262,   789, -1434, -1434, -1077, -1434, -1076,
   -1434,    61, -1434,    85, -1434,   120, -1434,   125, -1434,   113,
     115,   118, -1434, -1075, -1434, -1434, -1434, -1434,   257, -1434,
   -1434,    -8,  1287, -1434, -1434, -1434, -1434, -1434,   267, -1434,
   -1434, -1434,   261, -1434,   764, -1434,   -65, -1434, -1434, -1434,
   -1434, -1434,   -61, -1434, -1434, -1434, -1434, -1434,   -29, -1434,
   -1434, -1434,   268, -1434, -1434, -1434,   271, -1434,   758, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434,   198, -1434, -1434, -1434,   201,   807, -1434,
   -1434,   -63,   -42, -1434,   -13, -1434, -1434, -1434, -1434, -1434,
     197, -1434, -1434, -1434,   204,   794, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434,   -58, -1434, -1434, -1434,   264, -1434, -1434,
   -1434,   272, -1434,   798,   549, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1074, -1434, -1434, -1434, -1434, -1434,   281, -1434, -1434, -1434,
      15, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434,   258, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434,   243, -1434,   246,
     249, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434,   -37, -1434, -1434,   -62, -1434, -1434,
   -1434, -1434, -1434,   -30, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434,   -85, -1434, -1434,  -111, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434,   251, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434,   599,   795, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434,   645,   797, -1434, -1434,
   -1434, -1434, -1434, -1434,   269, -1434, -1434,    31, -1434, -1434,
   -1434, -1434, -1434, -1434,   -39, -1434, -1434,   -68, -1434, -1434,
   -1434, -1434, -1434, -1434, -1434, -1434, -1434, -1434,   270, -1434
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     800,    87,    88,    41,    68,    84,    85,   821,  1051,  1170,
    1171,   885,    43,    70,    90,   475,    91,    45,    71,   165,
     166,   167,   478,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   504,   785,   186,   505,   187,   506,   188,   189,   190,
     520,   797,   191,   192,   193,   194,   195,   542,   196,   543,
     197,   198,   199,   200,   498,   201,   202,   518,   203,   519,
     204,   205,   206,   207,   480,    47,    72,   244,   245,   246,
     552,   247,   248,   249,   250,   208,   481,   209,   482,   210,
     483,   913,   914,   915,  1091,   886,   887,   888,  1066,   889,
    1067,   890,  1068,   891,  1069,   892,   893,   596,   894,   895,
     896,   897,   898,   899,   900,   901,   902,  1080,  1355,   903,
     904,   905,   906,  1083,   907,  1084,   908,  1085,   909,  1086,
     910,  1087,   211,   530,   948,   949,   950,  1111,   951,  1112,
     212,   527,   934,   935,   936,   937,   213,   529,   942,   943,
     944,   945,   214,   528,   215,   537,   997,   998,   999,  1000,
    1001,   216,   533,   960,   961,   962,  1121,    63,    80,   439,
     440,   441,   611,   442,   612,   217,   534,   969,   970,   971,
     972,   973,   974,   975,   976,   218,   514,   917,   918,   919,
    1094,    49,    73,   297,   298,   299,   561,   300,   562,   301,
     563,   302,   569,   303,   566,   304,   567,   305,   568,   219,
     220,   221,   309,   310,   222,   521,   929,   930,   931,  1103,
    1255,  1256,   223,   515,    57,    77,   921,   922,   923,  1097,
      59,    78,   400,   401,   402,   403,   404,   405,   406,   595,
     407,   599,   408,   598,   409,   410,   600,   411,   224,   516,
     925,   926,   927,  1100,    61,    79,   423,   424,   425,   426,
     427,   604,   428,   429,   430,   431,   432,   433,   608,   312,
     559,  1053,  1054,  1055,  1172,    51,    74,   340,   341,   342,
     573,   343,   225,   522,   226,   523,   315,   560,  1057,  1058,
    1059,  1175,    53,    75,   360,   361,   362,   577,   363,   364,
     579,   365,   366,   227,   532,   956,   957,   958,  1118,    55,
      76,   379,   380,   381,   382,   585,   383,   586,   384,   587,
     385,   588,   386,   589,   387,   590,   388,   591,   389,   584,
     317,   570,  1061,   228,   531,   953,   954,  1115,  1282,  1283,
    1284,  1285,  1286,  1369,  1287,  1370,  1288,  1289,   229,   535,
     986,   987,   988,  1132,  1380,   989,   990,  1133,   991,   992,
     230,   231,   538,   232,   539,  1027,  1028,  1029,  1153,  1017,
    1018,  1019,  1144,  1385,  1020,  1145,  1021,  1146,  1022,  1023,
    1024,  1150,  1421,  1422,  1423,  1436,  1451,  1452,  1453,  1463,
    1025,  1148,  1414,  1415,  1416,  1430,  1459,  1417,  1431,  1418,
    1432,  1419,  1433,  1470,  1471,  1472,  1488,  1506,  1507,  1508,
    1517,  1509,  1518,   233,   540,  1036,  1037,  1038,  1039,  1157,
    1040,  1041,  1159,   234,   541,    65,    81,   454,   455,   456,
     457,   616,   458,   459,   618,   460,   461,   462,   621,   856,
     463,   622,   235,   479,    67,    82,   466,   467,   468,   625,
     469,   236,   547,  1044,  1045,  1163,  1334,  1335,  1336,  1337,
    1395,  1338,  1393,  1456,  1457,  1466,  1480,  1481,  1482,  1492,
    1483,  1484,  1485,  1486,  1496,   237,   548,  1048,  1049,  1050
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     164,   243,   265,   320,   351,   375,    38,   398,   419,   438,
     451,  1012,   357,   983,   421,   316,   272,  1013,   422,   273,
    1014,   911,   941,   399,   420,  1244,  1245,  1246,  1254,  1260,
     251,   313,   344,   358,   377,    30,   412,   434,   274,   452,
     391,   932,  1046,   799,   311,   339,   356,   376,    31,    86,
      32,    42,    33,   136,   137,  1502,  1503,   163,   275,   252,
     314,   345,   359,   378,   392,   413,   435,   476,   453,    89,
     436,   437,   477,   780,   781,   782,   783,   266,   238,   239,
     240,   241,   242,   550,   557,   267,  1502,  1503,   551,   558,
     129,   136,   137,   279,   321,   268,   280,   322,   392,   977,
     393,   394,   464,   465,   868,   395,   396,   397,   864,   865,
     784,   269,  1407,  1106,   270,   271,  1107,  1109,   281,   323,
    1110,   282,   324,   799,    44,   136,   137,   471,   283,   325,
    1030,  1031,  1032,   284,   326,   335,   352,   571,   933,   285,
     327,   470,   572,   575,   287,   328,   288,   329,   576,   289,
     330,   290,   331,   793,   794,   795,   796,   291,   332,   336,
     353,   163,   582,   292,   333,    46,  1446,   583,   293,   334,
     276,   136,   137,   277,   472,   278,   286,   613,   294,  1033,
     295,   296,   614,    48,   136,   137,   306,  1116,   307,    50,
    1117,   308,   136,   137,   337,   354,    52,   136,   137,   338,
     355,   863,   864,   865,   866,   867,   868,   869,   870,   871,
     872,   873,   874,   875,   876,   877,    54,   163,    56,   878,
     879,   880,   881,   882,   883,   884,   963,   964,   965,   966,
     967,   968,   978,   979,   980,   981,   880,   881,   882,   115,
     116,   117,   118,   119,   120,   121,    58,   123,   124,   125,
     126,   163,    60,   623,   130,   627,   550,   392,   624,   392,
     628,  1063,    62,  1499,  1500,  1408,  1409,  1410,   134,   627,
     932,   939,    64,   940,  1064,   318,   136,   137,    34,    35,
      36,    37,   136,   137,   136,   137,    66,  1244,  1245,  1246,
    1254,  1260,  1164,  1467,   473,  1165,  1468,   163,   260,   261,
     262,   136,   137,   557,  1088,   263,   319,   474,  1065,  1089,
     163,   484,    98,    99,   100,   101,   102,   103,   163,  1088,
    1113,  1130,   592,   163,  1090,  1114,  1131,   941,   485,  1137,
     993,   994,   995,  1475,  1138,  1203,  1476,  1477,  1478,  1479,
     983,   130,  1142,  1151,   130,   392,  1160,  1143,  1152,   623,
    1012,  1161,  1012,   486,  1162,   487,  1013,  1167,  1013,  1014,
    1004,  1014,  1168,  1088,  1005,  1006,  1007,  1008,  1361,   136,
     137,   571,   136,   137,  1009,  1010,  1362,   488,   156,   157,
     436,   437,   136,   137,   489,   367,  1327,   490,  1328,  1329,
     491,  1267,  1268,  1269,  1270,   368,   369,   370,   371,   372,
     373,   374,   163,   492,  1365,   593,   613,   603,   163,  1366,
     163,  1376,   163,   493,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   163,  1352,  1353,
    1354,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,  1151,   130,   392,  1396,   575,
    1390,   582,  1434,  1397,  1399,   494,  1400,  1435,   132,   133,
     134,   629,   630,   443,   444,   445,   446,   447,   448,   449,
     450,  1464,   854,   855,   136,   137,  1465,   256,   257,   164,
     259,   138,   139,   140,  1497,   594,   243,   495,  1519,  1498,
     260,   261,   262,  1520,   496,   163,   497,   263,   163,   499,
     265,  1377,  1378,  1379,   320,   946,   947,   264,   163,   500,
     501,   351,   502,   316,   272,   251,   503,   273,   507,   357,
     508,   509,   375,   510,  1382,  1383,  1384,   511,   512,   313,
     513,   517,   398,   344,   524,   525,   274,   526,   536,   419,
     358,   544,   311,   545,   252,   421,   339,   546,   399,   422,
     549,   377,   451,   356,   553,   420,   275,   554,   314,   555,
     556,   412,   345,   564,   376,   565,   574,   578,   434,   359,
     156,   157,   580,   581,   597,   266,   601,   605,   606,   602,
     378,   452,   607,   267,   609,   610,   827,   828,   829,   615,
     413,   279,   617,   268,   280,   321,   619,   435,   322,   620,
     163,   835,   836,   837,   838,   626,   631,   632,   633,   269,
     453,   634,   270,   271,   639,   635,   281,   636,   637,   282,
     323,   638,   849,   324,   640,   647,   283,   641,   642,   643,
     325,   284,   644,   645,   646,   326,   335,   285,   653,   659,
     660,   327,   287,   352,   288,   648,   328,   289,   329,   290,
     649,   330,   650,   331,   651,   291,   652,   654,   655,   332,
     336,   292,   656,   657,   658,   333,   293,   353,   276,   661,
     334,   277,   662,   278,   286,   663,   294,   664,   295,   296,
     665,   668,   669,   666,   306,   670,   307,   671,   667,   308,
     672,   130,   673,   674,   675,   337,   676,   677,   678,   679,
     338,   164,   354,   680,   243,   681,   682,   355,   683,   684,
     685,   686,   687,   688,   346,   347,   348,   349,   350,   136,
     137,   689,   392,   414,   393,   394,   415,   416,   417,   690,
     691,   692,   693,   251,   694,   260,   261,   262,   695,   982,
     996,  1011,   263,   319,   451,   696,   697,   698,  1047,   136,
     137,   699,   702,   700,   703,   705,   701,   711,   706,   707,
     712,   859,   252,   713,   708,   418,   714,   717,   984,  1002,
    1015,   709,  1034,   452,    92,    93,   715,   716,    94,   718,
     719,   720,   721,   722,    95,    96,    97,   724,   725,   727,
     728,   729,   733,   730,   731,   734,   735,   985,  1003,  1016,
     736,  1035,   453,   737,   738,   739,   740,   742,   743,   745,
     746,   744,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   163,   747,   748,   750,   754,
     751,   756,   757,   752,   753,   131,   132,   133,   134,   759,
     760,   761,   762,   135,   763,   764,   765,   766,   768,   769,
     771,   857,   136,   137,   772,   163,   773,   774,   775,   138,
     139,   140,   141,   142,   143,   144,   776,   777,   145,   778,
     779,   786,   787,   788,   789,   790,   791,   146,   792,   798,
      32,   801,   802,   803,   804,   816,   147,   805,   806,   148,
     807,   808,   817,  1070,   809,   810,   149,   811,   812,   813,
     814,   818,   815,   820,   150,   151,   819,   822,   823,   152,
     153,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,   831,   824,   825,   154,   826,
     830,   832,   155,   833,   834,   839,   840,   841,   842,   843,
     858,   844,   368,   912,   845,   916,   846,   847,   156,   157,
     158,   159,   160,   161,   848,   850,   920,   924,   928,   852,
     853,   952,   162,   955,   959,  1026,  1043,  1052,  1056,  1071,
    1072,  1073,  1074,  1075,  1076,  1077,  1078,  1079,   163,  1081,
    1082,  1093,  1169,  1092,  1096,  1095,  1098,  1099,  1101,  1102,
    1105,  1104,  1185,  1120,  1108,  1119,  1123,  1122,  1124,  1125,
    1126,  1127,  1128,   265,  1129,  1134,   398,  1135,  1136,   419,
    1139,  1140,  1211,  1141,  1147,   421,   316,   272,  1149,   422,
     273,  1154,   399,  1155,  1271,   420,  1218,   375,  1243,  1219,
     438,  1156,   313,  1158,  1166,   412,  1174,  1173,   434,   274,
    1278,  1258,  1176,  1177,  1179,   311,   982,  1178,  1220,  1180,
    1181,   996,  1182,  1280,  1257,  1183,   377,  1184,  1187,   275,
    1011,   314,  1011,  1194,   413,  1186,  1279,   435,  1221,   376,
    1259,  1188,  1330,  1189,  1197,   984,  1047,  1190,   266,  1198,
    1002,   320,  1281,  1195,   351,   378,   267,  1212,  1331,  1015,
    1191,  1015,   357,  1192,   279,  1213,   268,   280,  1034,  1272,
    1199,  1332,  1193,  1225,   985,  1214,  1226,  1273,  1196,  1003,
     344,  1200,   269,   358,  1201,   270,   271,  1274,  1016,   281,
    1016,  1215,   282,   339,  1216,  1217,   356,  1035,  1227,   283,
    1333,  1228,  1264,  1275,   284,  1265,  1276,  1277,  1229,   345,
     285,  1295,   359,  1230,  1247,   287,  1296,   288,  1297,  1231,
     289,  1298,   290,  1299,  1233,  1300,  1234,  1302,   291,  1235,
    1303,  1236,  1304,  1305,   292,  1306,  1308,  1237,  1248,   293,
    1309,   276,   321,  1238,   277,   322,   278,   286,  1239,   294,
    1222,   295,   296,  1223,  1310,  1224,  1232,   306,  1240,   307,
    1241,  1242,   308,  1312,  1313,  1314,  1251,   323,  1252,  1315,
     324,  1253,  1316,  1249,  1318,  1323,  1325,   325,  1250,  1342,
    1324,  1343,   326,   335,  1363,  1364,   352,  1371,   327,  1372,
    1373,  1317,  1374,   328,  1375,   329,  1389,  1348,   330,  1388,
     331,  1394,  1402,  1403,  1349,  1438,   332,   336,  1420,  1424,
     353,  1426,   333,  1322,  1437,  1439,  1340,   334,  1350,  1404,
    1405,  1351,  1356,  1357,  1358,  1441,  1359,  1360,  1367,  1368,
    1381,  1386,  1442,  1387,  1443,  1444,  1455,  1391,  1458,  1398,
    1462,  1425,   337,  1469,  1211,   354,  1428,   338,  1429,  1440,
     355,  1473,  1460,  1271,  1461,  1489,  1490,  1491,  1218,  1493,
    1243,  1219,  1494,  1495,  1511,  1392,  1512,  1411,  1513,  1278,
    1514,  1515,  1521,  1258,  1522,  1330,  1523,  1524,  1526,  1527,
    1220,   704,  1280,  1062,   851,   938,  1257,   860,  1266,   862,
    1204,  1331,  1202,   710,  1262,  1279,  1412,  1311,  1293,  1263,
    1221,  1294,  1259,  1301,  1332,  1206,  1205,  1401,  1207,   758,
     723,  1281,  1261,  1411,   390,  1447,  1208,   749,   755,  1212,
    1210,  1209,  1345,  1344,  1347,  1413,   732,  1213,  1272,  1346,
    1060,  1448,   726,  1333,  1292,  1225,  1273,  1214,  1226,  1406,
    1291,   741,  1412,  1447,  1449,  1307,  1274,  1290,  1321,  1320,
    1319,  1454,  1474,  1215,  1445,  1510,  1216,  1217,  1525,  1448,
    1227,  1326,  1275,  1228,  1042,  1276,  1277,  1501,   767,   861,
    1229,  1413,  1449,  1450,   770,  1230,  1247,  1427,  1487,  1516,
       0,  1231,     0,  1339,     0,     0,  1233,  1341,  1234,     0,
       0,  1235,     0,  1236,     0,     0,  1504,     0,  1501,  1237,
    1248,  1450,     0,     0,     0,  1238,     0,     0,     0,     0,
    1239,     0,  1222,     0,     0,  1223,     0,  1224,  1232,     0,
    1240,     0,  1241,  1242,     0,  1505,     0,  1504,  1251,     0,
    1252,     0,     0,  1253,     0,  1249,     0,     0,     0,     0,
    1250,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,     0,     0,  1505,     0,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,     0,     0,   130,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   132,   133,   134,     0,     0,
       0,     0,     0,   253,     0,   254,     0,     0,     0,     0,
       0,   136,   137,   255,   256,   257,   258,   259,   138,   139,
     140,     0,     0,     0,     0,     0,     0,   260,   261,   262,
       0,     0,     0,     0,   263,     0,   146,     0,     0,     0,
       0,     0,     0,     0,   264,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   156,   157,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   163
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   812,    75,   810,    79,    73,    73,   812,    79,    73,
     812,   777,   804,    78,    79,  1103,  1103,  1103,  1103,  1103,
      72,    73,    74,    75,    76,     0,    78,    79,    73,    81,
      24,   138,   220,   677,    73,    74,    75,    76,     5,   235,
       7,     7,     9,   109,   110,  1488,  1488,   235,    73,    72,
      73,    74,    75,    76,    82,    78,    79,     3,    81,    10,
     144,   145,     8,   201,   202,   203,   204,    73,    16,    17,
      18,    19,    20,     3,     3,    73,  1519,  1519,     8,     8,
      80,   109,   110,    73,    74,    73,    73,    74,    82,    24,
      84,    85,    13,    14,    29,    89,    90,    91,    25,    26,
     238,    73,    24,     3,    73,    73,     6,     3,    73,    74,
       6,    73,    74,   757,     7,   109,   110,     3,    73,    74,
     186,   187,   188,    73,    74,    74,    75,     3,   235,    73,
      74,     6,     8,     3,    73,    74,    73,    74,     8,    73,
      74,    73,    74,    96,    97,    98,    99,    73,    74,    74,
      75,   235,     3,    73,    74,     7,   184,     8,    73,    74,
      73,   109,   110,    73,     4,    73,    73,     3,    73,   235,
      73,    73,     8,     7,   109,   110,    73,     3,    73,     7,
       6,    73,   109,   110,    74,    75,     7,   109,   110,    74,
      75,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,     7,   235,     7,    42,
      43,    44,    45,    46,    47,    48,   147,   148,   149,   150,
     151,   152,   157,   158,   159,   160,    44,    45,    46,    66,
      67,    68,    69,    70,    71,    72,     7,    74,    75,    76,
      77,   235,     7,     3,    81,     3,     3,    82,     8,    82,
       8,     8,     7,   180,   181,   177,   178,   179,    95,     3,
     138,   139,     7,   141,     8,   102,   109,   110,   235,   236,
     237,   238,   109,   110,   109,   110,     7,  1365,  1365,  1365,
    1365,  1365,     3,     3,     8,     6,     6,   235,   125,   126,
     127,   109,   110,     3,     3,   132,   133,     3,     8,     8,
     235,     4,    49,    50,    51,    52,    53,    54,   235,     3,
       3,     3,     8,   235,     8,     8,     8,  1109,     4,     3,
     163,   164,   165,   212,     8,  1091,   215,   216,   217,   218,
    1137,    81,     3,     3,    81,    82,     3,     8,     8,     3,
    1151,     8,  1153,     4,     8,     4,  1151,     3,  1153,  1151,
     168,  1153,     8,     3,   172,   173,   174,   175,     8,   109,
     110,     3,   109,   110,   182,   183,     8,     4,   205,   206,
     144,   145,   109,   110,     4,   125,   211,     4,   213,   214,
       4,   128,   129,   130,   131,   135,   136,   137,   138,   139,
     140,   141,   235,     4,     3,     3,     3,     3,   235,     8,
     235,     8,   235,     4,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,   235,    39,    40,
      41,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,     3,    81,    82,     3,     3,
       8,     3,     3,     8,     8,     4,     8,     8,    93,    94,
      95,   471,   472,   190,   191,   192,   193,   194,   195,   196,
     197,     3,   198,   199,   109,   110,     8,   112,   113,   550,
     115,   116,   117,   118,     3,     8,   557,     4,     3,     8,
     125,   126,   127,     8,     4,   235,     4,   132,   235,     4,
     571,   154,   155,   156,   575,   123,   124,   142,   235,     4,
       4,   582,     4,   571,   571,   557,     4,   571,     4,   582,
       4,     4,   593,     4,   169,   170,   171,     4,     4,   571,
       4,     4,   603,   575,     4,     4,   571,     4,     4,   610,
     582,     4,   571,     4,   557,   610,   575,     4,   603,   610,
       4,   593,   623,   582,     4,   610,   571,     4,   571,     4,
       4,   603,   575,     4,   593,     4,     4,     4,   610,   582,
     205,   206,     4,     4,     4,   571,     4,     4,     4,     8,
     593,   623,     4,   571,     8,     3,   718,   719,   720,     4,
     603,   571,     4,   571,   571,   575,     4,   610,   575,     4,
     235,   733,   734,   735,   736,     4,   235,     4,     4,   571,
     623,     4,   571,   571,   236,     4,   571,     4,     4,   571,
     575,     4,   754,   575,   236,   238,   571,   236,   236,   236,
     575,   571,   236,   236,   236,   575,   575,   571,     4,     4,
       4,   575,   571,   582,   571,   237,   575,   571,   575,   571,
     237,   575,   237,   575,   236,   571,   236,   236,   236,   575,
     575,   571,   238,   238,   238,   575,   571,   582,   571,     4,
     575,   571,   238,   571,   571,   238,   571,   237,   571,   571,
     236,   238,     4,   236,   571,     4,   571,     4,   236,   571,
     236,    81,     4,     4,     4,   575,     4,     4,     4,   238,
     575,   772,   582,   238,   775,   238,     4,   582,     4,     4,
       4,     4,     4,     4,   104,   105,   106,   107,   108,   109,
     110,     4,    82,    83,    84,    85,    86,    87,    88,     4,
     236,     4,     4,   775,     4,   125,   126,   127,     4,   810,
     811,   812,   132,   133,   815,     4,     4,     4,   819,   109,
     110,   238,     4,   238,     4,     4,   238,     4,   238,   238,
       4,   771,   775,     4,   236,   125,     4,   238,   810,   811,
     812,   236,   814,   815,    11,    12,     4,   236,    15,     4,
       4,     4,     4,     4,    21,    22,    23,     4,   236,     4,
     236,     4,     4,   236,   236,     4,     4,   810,   811,   812,
       4,   814,   815,     4,     4,     4,     4,     4,     4,     4,
       4,   236,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,   235,     4,   238,     4,     4,
     238,     4,     4,   238,   238,    92,    93,    94,    95,   238,
       4,   236,     4,   100,   236,   236,     4,     4,     4,   236,
       4,   200,   109,   110,     7,   235,   235,     7,     7,   116,
     117,   118,   119,   120,   121,   122,     7,     7,   125,     5,
     235,   235,   235,     5,     5,     5,   235,   134,   235,     5,
       7,   235,     5,     5,     5,   235,   143,     7,     5,   146,
       5,     5,   235,     4,     7,     7,   153,     7,     7,     5,
       7,     5,     7,     5,   161,   162,     7,     5,     5,   166,
     167,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,     7,   235,   235,   185,   235,
     235,   235,   189,   235,   235,   235,   235,   235,   235,   235,
       5,   235,   135,     7,   235,     7,   235,   235,   205,   206,
     207,   208,   209,   210,   235,   235,     7,     7,     7,   235,
     235,     7,   219,     7,     7,     7,     7,     7,     7,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   235,     4,
       4,     3,   235,     6,     3,     6,     6,     3,     6,     3,
       3,     6,   238,     3,     6,     6,     3,     6,     4,     4,
       4,     4,     4,  1094,     4,     4,  1097,     4,     4,  1100,
       4,     4,  1103,     4,     4,  1100,  1094,  1094,     4,  1100,
    1094,     6,  1097,     3,  1115,  1100,  1103,  1118,  1103,  1103,
    1121,     4,  1094,     4,     4,  1097,     3,     6,  1100,  1094,
    1115,  1103,     6,     3,     6,  1094,  1137,     8,  1103,     4,
       4,  1142,     4,  1115,  1103,     4,  1118,   236,   238,  1094,
    1151,  1094,  1153,     4,  1097,   236,  1115,  1100,  1103,  1118,
    1103,   236,  1163,   236,     4,  1137,  1167,   236,  1094,     4,
    1142,  1172,  1115,   238,  1175,  1118,  1094,  1103,  1163,  1151,
     236,  1153,  1175,   236,  1094,  1103,  1094,  1094,  1160,  1115,
       4,  1163,   236,  1103,  1137,  1103,  1103,  1115,   236,  1142,
    1172,     4,  1094,  1175,     4,  1094,  1094,  1115,  1151,  1094,
    1153,  1103,  1094,  1172,  1103,  1103,  1175,  1160,  1103,  1094,
    1163,  1103,     4,  1115,  1094,     4,  1115,  1115,  1103,  1172,
    1094,   236,  1175,  1103,  1103,  1094,   236,  1094,   236,  1103,
    1094,   236,  1094,   236,  1103,   236,  1103,     4,  1094,  1103,
       4,  1103,   236,   236,  1094,   236,   238,  1103,  1103,  1094,
     236,  1094,  1172,  1103,  1094,  1172,  1094,  1094,  1103,  1094,
    1103,  1094,  1094,  1103,   236,  1103,  1103,  1094,  1103,  1094,
    1103,  1103,  1094,     4,     4,     4,  1103,  1172,  1103,   236,
    1172,  1103,     4,  1103,     4,     4,     4,  1172,  1103,     6,
     236,     3,  1172,  1172,     8,     8,  1175,     4,  1172,     4,
       8,   238,     3,  1172,     8,  1172,     5,   235,  1172,     7,
    1172,     4,     4,     4,   235,     3,  1172,  1172,     7,     4,
    1175,     4,  1172,   238,     6,     5,   238,  1172,   235,   238,
     238,   235,   235,   235,   235,     4,   235,   235,   235,   235,
     235,   235,     4,   235,     4,     4,     7,   235,   176,   235,
       5,   236,  1172,     7,  1365,  1175,   235,  1172,   235,   235,
    1175,     4,   235,  1374,   235,     6,     3,   235,  1365,     4,
    1365,  1365,     4,     4,     4,  1325,   238,  1388,   236,  1374,
     236,     4,   235,  1365,   235,  1396,     4,     4,   235,   235,
    1365,   550,  1374,   858,   757,   803,  1365,   772,  1113,   775,
    1093,  1396,  1088,   557,  1106,  1374,  1388,  1142,  1121,  1109,
    1365,  1123,  1365,  1130,  1396,  1096,  1094,  1365,  1097,   613,
     571,  1374,  1105,  1434,    77,  1436,  1099,   603,   610,  1365,
    1102,  1100,  1174,  1172,  1177,  1388,   582,  1365,  1374,  1175,
     831,  1436,   575,  1396,  1120,  1365,  1374,  1365,  1365,  1374,
    1118,   593,  1434,  1464,  1436,  1137,  1374,  1116,  1155,  1153,
    1151,  1438,  1464,  1365,  1434,  1490,  1365,  1365,  1519,  1464,
    1365,  1160,  1374,  1365,   815,  1374,  1374,  1488,   623,   774,
    1365,  1434,  1464,  1436,   627,  1365,  1365,  1396,  1467,  1497,
      -1,  1365,    -1,  1164,    -1,    -1,  1365,  1167,  1365,    -1,
      -1,  1365,    -1,  1365,    -1,    -1,  1488,    -1,  1519,  1365,
    1365,  1464,    -1,    -1,    -1,  1365,    -1,    -1,    -1,    -1,
    1365,    -1,  1365,    -1,    -1,  1365,    -1,  1365,  1365,    -1,
    1365,    -1,  1365,  1365,    -1,  1488,    -1,  1519,  1365,    -1,
    1365,    -1,    -1,  1365,    -1,  1365,    -1,    -1,    -1,    -1,
    1365,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,  1519,    -1,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    -1,    -1,    81,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    93,    94,    95,    -1,    -1,
      -1,    -1,    -1,   101,    -1,   103,    -1,    -1,    -1,    -1,
      -1,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,    -1,    -1,    -1,    -1,    -1,    -1,   125,   126,   127,
      -1,    -1,    -1,    -1,   132,    -1,   134,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   142,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   205,   206,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   235
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
       0,     5,     7,     9,   235,   236,   237,   238,   255,   256,
     257,   262,     7,   271,     7,   276,     7,   334,     7,   450,
       7,   534,     7,   551,     7,   568,     7,   483,     7,   489,
       7,   513,     7,   426,     7,   684,     7,   703,   263,   258,
     272,   277,   335,   451,   535,   552,   569,   484,   490,   514,
     427,   685,   704,   255,   264,   265,   235,   260,   261,    10,
     273,   275,    11,    12,    15,    21,    22,    23,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    92,    93,    94,    95,   100,   109,   110,   116,   117,
     118,   119,   120,   121,   122,   125,   134,   143,   146,   153,
     161,   162,   166,   167,   185,   189,   205,   206,   207,   208,
     209,   210,   219,   235,   270,   278,   279,   280,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   302,   304,   306,   307,
     308,   311,   312,   313,   314,   315,   317,   319,   320,   321,
     322,   324,   325,   327,   329,   330,   331,   332,   344,   346,
     348,   391,   399,   405,   411,   413,   420,   434,   444,   468,
     469,   470,   473,   481,   507,   541,   543,   562,   592,   607,
     619,   620,   622,   672,   682,   701,   710,   734,    16,    17,
      18,    19,    20,   270,   336,   337,   338,   340,   341,   342,
     343,   541,   543,   101,   103,   111,   112,   113,   114,   115,
     125,   126,   127,   132,   142,   270,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   296,
     297,   298,   299,   302,   304,   306,   307,   308,   311,   312,
     313,   314,   315,   317,   319,   325,   327,   452,   453,   454,
     456,   458,   460,   462,   464,   466,   468,   469,   470,   471,
     472,   507,   528,   541,   543,   545,   562,   589,   102,   133,
     270,   296,   297,   298,   299,   302,   304,   306,   308,   311,
     312,   313,   314,   315,   317,   460,   462,   464,   466,   507,
     536,   537,   538,   540,   541,   543,   104,   105,   106,   107,
     108,   270,   460,   462,   464,   466,   507,   540,   541,   543,
     553,   554,   555,   557,   558,   560,   561,   125,   135,   136,
     137,   138,   139,   140,   141,   270,   507,   541,   543,   570,
     571,   572,   573,   575,   577,   579,   581,   583,   585,   587,
     481,    24,    82,    84,    85,    89,    90,    91,   270,   365,
     491,   492,   493,   494,   495,   496,   497,   499,   501,   503,
     504,   506,   541,   543,    83,    86,    87,    88,   125,   270,
     365,   495,   501,   515,   516,   517,   518,   519,   521,   522,
     523,   524,   525,   526,   541,   543,   144,   145,   270,   428,
     429,   430,   432,   190,   191,   192,   193,   194,   195,   196,
     197,   270,   541,   543,   686,   687,   688,   689,   691,   692,
     694,   695,   696,   699,    13,    14,   705,   706,   707,   709,
       6,     3,     4,     8,     3,   274,     3,     8,   281,   702,
     333,   345,   347,   349,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   323,     4,
       4,     4,     4,     4,   300,   303,   305,     4,     4,     4,
       4,     4,     4,     4,   445,   482,   508,     4,   326,   328,
     309,   474,   542,   544,     4,     4,     4,   400,   412,   406,
     392,   593,   563,   421,   435,   608,     4,   414,   621,   623,
     673,   683,   316,   318,     4,     4,     4,   711,   735,     4,
       3,     8,   339,     4,     4,     4,     4,     3,     8,   529,
     546,   455,   457,   459,     4,     4,   463,   465,   467,   461,
     590,     3,     8,   539,     4,     3,     8,   556,     4,   559,
       4,     4,     3,     8,   588,   574,   576,   578,   580,   582,
     584,   586,     8,     3,     8,   498,   366,     4,   502,   500,
     505,     4,     8,     3,   520,     4,     4,     4,   527,     8,
       3,   431,   433,     3,     8,     4,   690,     4,   693,     4,
       4,   697,   700,     3,     8,   708,     4,     3,     8,   255,
     255,   235,     4,     4,     4,     4,     4,     4,     4,   236,
     236,   236,   236,   236,   236,   236,   236,   238,   237,   237,
     237,   236,   236,     4,   236,   236,   238,   238,   238,     4,
       4,     4,   238,   238,   237,   236,   236,   236,   238,     4,
       4,     4,   236,     4,     4,     4,     4,     4,     4,   238,
     238,   238,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   236,     4,     4,     4,     4,     4,     4,     4,   238,
     238,   238,     4,     4,   279,     4,   238,   238,   236,   236,
     337,     4,     4,     4,     4,     4,   236,   238,     4,     4,
       4,     4,     4,   453,     4,   236,   537,     4,   236,     4,
     236,   236,   554,     4,     4,     4,     4,     4,     4,     4,
       4,   572,     4,     4,   236,     4,     4,     4,   238,   493,
       4,   238,   238,   238,     4,   517,     4,     4,   429,   238,
       4,   236,     4,   236,   236,     4,     4,   687,     4,   236,
     706,     4,     7,   235,     7,     7,     7,     7,     5,   235,
     201,   202,   203,   204,   238,   301,   235,   235,     5,     5,
       5,   235,   235,    96,    97,    98,    99,   310,     5,   257,
     259,   235,     5,     5,     5,     7,     5,     5,     5,     7,
       7,     7,     7,     5,     7,     7,   235,   235,     5,     7,
       5,   266,     5,     5,   235,   235,   235,   266,   266,   266,
     235,     7,   235,   235,   235,   266,   266,   266,   266,   235,
     235,   235,   235,   235,   235,   235,   235,   235,   235,   266,
     235,   259,   235,   235,   198,   199,   698,   200,     5,   255,
     278,   705,   336,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    42,    43,
      44,    45,    46,    47,    48,   270,   354,   355,   356,   358,
     360,   362,   364,   365,   367,   368,   369,   370,   371,   372,
     373,   374,   375,   378,   379,   380,   381,   383,   385,   387,
     389,   354,     7,   350,   351,   352,     7,   446,   447,   448,
       7,   485,   486,   487,     7,   509,   510,   511,     7,   475,
     476,   477,   138,   235,   401,   402,   403,   404,   264,   139,
     141,   403,   407,   408,   409,   410,   123,   124,   393,   394,
     395,   397,     7,   594,   595,     7,   564,   565,   566,     7,
     422,   423,   424,   147,   148,   149,   150,   151,   152,   436,
     437,   438,   439,   440,   441,   442,   443,    24,   157,   158,
     159,   160,   270,   367,   541,   543,   609,   610,   611,   614,
     615,   617,   618,   163,   164,   165,   270,   415,   416,   417,
     418,   419,   541,   543,   168,   172,   173,   174,   175,   182,
     183,   270,   381,   383,   385,   541,   543,   628,   629,   630,
     633,   635,   637,   638,   639,   649,     7,   624,   625,   626,
     186,   187,   188,   235,   541,   543,   674,   675,   676,   677,
     679,   680,   686,     7,   712,   713,   220,   270,   736,   737,
     738,   267,     7,   530,   531,   532,     7,   547,   548,   549,
     573,   591,   350,     8,     8,     8,   357,   359,   361,   363,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     376,     4,     4,   382,   384,   386,   388,   390,     3,     8,
       8,   353,     6,     3,   449,     6,     3,   488,     6,     3,
     512,     6,     3,   478,     6,     3,     3,     6,     6,     3,
       6,   396,   398,     3,     8,   596,     3,     6,   567,     6,
       3,   425,     6,     3,     4,     4,     4,     4,     4,     4,
       3,     8,   612,   616,     4,     4,     4,     3,     8,     4,
       4,     4,     3,     8,   631,   634,   636,     4,   650,     4,
     640,     3,     8,   627,     6,     3,     4,   678,     4,   681,
       3,     8,     8,   714,     3,     6,     4,     3,     8,   235,
     268,   269,   533,     6,     3,   550,     6,     3,     8,     6,
       4,     4,     4,     4,   236,   238,   236,   238,   236,   236,
     236,   236,   236,   236,     4,   238,   236,     4,     4,     4,
       4,     4,   355,   354,   352,   452,   448,   491,   487,   515,
     511,   270,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   296,   297,   298,   299,   302,
     304,   306,   307,   308,   311,   312,   313,   314,   315,   317,
     319,   325,   327,   365,   444,   456,   458,   460,   462,   464,
     466,   468,   469,   470,   472,   479,   480,   507,   541,   543,
     589,   477,   402,   408,     4,     4,   394,   128,   129,   130,
     131,   270,   282,   283,   284,   285,   286,   287,   365,   507,
     541,   543,   597,   598,   599,   600,   601,   603,   605,   606,
     595,   570,   566,   428,   424,   236,   236,   236,   236,   236,
     236,   437,     4,     4,   236,   236,   236,   610,   238,   236,
     236,   416,     4,     4,     4,   236,     4,   238,     4,   629,
     628,   626,   238,     4,   236,     4,   675,   211,   213,   214,
     270,   365,   541,   543,   715,   716,   717,   718,   720,   713,
     238,   737,     6,     3,   536,   532,   553,   549,   235,   235,
     235,   235,    39,    40,    41,   377,   235,   235,   235,   235,
     235,     8,     8,     8,     8,     3,     8,   235,   235,   602,
     604,     4,     4,     8,     3,     8,     8,   154,   155,   156,
     613,   235,   169,   170,   171,   632,   235,   235,     7,     5,
       8,   235,   255,   721,     4,   719,     3,     8,   235,     8,
       8,   480,     4,     4,   238,   238,   599,    24,   177,   178,
     179,   270,   541,   543,   651,   652,   653,   656,   658,   660,
       7,   641,   642,   643,     4,   236,     4,   716,   235,   235,
     654,   657,   659,   661,     3,     8,   644,     6,     3,     5,
     235,     4,     4,     4,     4,   652,   184,   270,   365,   541,
     543,   645,   646,   647,   643,     7,   722,   723,   176,   655,
     235,   235,     5,   648,     3,     8,   724,     3,     6,     7,
     662,   663,   664,     4,   646,   212,   215,   216,   217,   218,
     725,   726,   727,   729,   730,   731,   732,   723,   665,     6,
       3,   235,   728,     4,     4,     4,   733,     3,     8,   180,
     181,   270,   358,   360,   541,   543,   666,   667,   668,   670,
     664,     4,   238,   236,   236,     4,   726,   669,   671,     3,
       8,   235,   235,     4,     4,   667,   235,   235
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   239,   241,   240,   242,   240,   243,   240,   244,   240,
     245,   240,   246,   240,   247,   240,   248,   240,   249,   240,
     250,   240,   251,   240,   252,   240,   253,   240,   254,   240,
     255,   255,   255,   255,   255,   255,   255,   256,   258,   257,
     259,   260,   260,   261,   261,   261,   263,   262,   264,   264,
     265,   265,   265,   267,   266,   268,   268,   269,   269,   269,
     270,   272,   271,   274,   273,   273,   275,   277,   276,   278,
     278,   278,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   281,   280,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   300,   299,   301,   301,   301,   301,   301,
     303,   302,   305,   304,   306,   307,   309,   308,   310,   310,
     310,   310,   311,   312,   313,   314,   316,   315,   318,   317,
     319,   320,   321,   323,   322,   324,   326,   325,   328,   327,
     329,   330,   331,   333,   332,   335,   334,   336,   336,   336,
     337,   337,   337,   337,   337,   337,   337,   337,   339,   338,
     340,   341,   342,   343,   345,   344,   347,   346,   349,   348,
     350,   350,   351,   351,   351,   353,   352,   354,   354,   354,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   357,   356,   359,   358,   361,   360,
     363,   362,   364,   366,   365,   367,   368,   369,   370,   371,
     372,   373,   374,   376,   375,   377,   377,   377,   378,   379,
     380,   382,   381,   384,   383,   386,   385,   388,   387,   390,
     389,   392,   391,   393,   393,   393,   394,   394,   396,   395,
     398,   397,   400,   399,   401,   401,   401,   402,   402,   403,
     404,   406,   405,   407,   407,   407,   408,   408,   408,   409,
     410,   412,   411,   414,   413,   415,   415,   415,   416,   416,
     416,   416,   416,   416,   417,   418,   419,   421,   420,   422,
     422,   423,   423,   423,   425,   424,   427,   426,   428,   428,
     428,   428,   429,   429,   431,   430,   433,   432,   435,   434,
     436,   436,   436,   437,   437,   437,   437,   437,   437,   438,
     439,   440,   441,   442,   443,   445,   444,   446,   446,   447,
     447,   447,   449,   448,   451,   450,   452,   452,   452,   453,
     453,   453,   453,   453,   453,   453,   453,   453,   453,   453,
     453,   453,   453,   453,   453,   453,   453,   453,   453,   453,
     453,   453,   453,   453,   453,   453,   453,   453,   453,   453,
     453,   453,   453,   453,   453,   453,   453,   453,   453,   453,
     453,   453,   453,   453,   453,   453,   453,   453,   453,   453,
     455,   454,   457,   456,   459,   458,   461,   460,   463,   462,
     465,   464,   467,   466,   468,   469,   470,   471,   472,   474,
     473,   475,   475,   476,   476,   476,   478,   477,   479,   479,
     479,   480,   480,   480,   480,   480,   480,   480,   480,   480,
     480,   480,   480,   480,   480,   480,   480,   480,   480,   480,
     480,   480,   480,   480,   480,   480,   480,   480,   480,   480,
     480,   480,   480,   480,   480,   480,   480,   480,   480,   480,
     480,   480,   480,   480,   480,   480,   480,   480,   480,   482,
     481,   484,   483,   485,   485,   486,   486,   486,   488,   487,
     490,   489,   491,   491,   492,   492,   492,   493,   493,   493,
     493,   493,   493,   493,   493,   493,   493,   494,   495,   496,
     498,   497,   500,   499,   502,   501,   503,   505,   504,   506,
     508,   507,   509,   509,   510,   510,   510,   512,   511,   514,
     513,   515,   515,   516,   516,   516,   517,   517,   517,   517,
     517,   517,   517,   517,   517,   517,   517,   518,   520,   519,
     521,   522,   523,   524,   525,   527,   526,   529,   528,   530,
     530,   531,   531,   531,   533,   532,   535,   534,   536,   536,
     536,   537,   537,   537,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   537,   539,   538,   540,   542,   541,
     544,   543,   546,   545,   547,   547,   548,   548,   548,   550,
     549,   552,   551,   553,   553,   553,   554,   554,   554,   554,
     554,   554,   554,   554,   554,   554,   554,   554,   554,   554,
     556,   555,   557,   559,   558,   560,   561,   563,   562,   564,
     564,   565,   565,   565,   567,   566,   569,   568,   570,   570,
     571,   571,   571,   572,   572,   572,   572,   572,   572,   572,
     572,   572,   572,   572,   572,   574,   573,   576,   575,   578,
     577,   580,   579,   582,   581,   584,   583,   586,   585,   588,
     587,   590,   589,   591,   593,   592,   594,   594,   594,   596,
     595,   597,   597,   598,   598,   598,   599,   599,   599,   599,
     599,   599,   599,   599,   599,   599,   599,   599,   599,   599,
     599,   600,   602,   601,   604,   603,   605,   606,   608,   607,
     609,   609,   609,   610,   610,   610,   610,   610,   610,   610,
     610,   610,   612,   611,   613,   613,   613,   614,   616,   615,
     617,   618,   619,   621,   620,   623,   622,   624,   624,   625,
     625,   625,   627,   626,   628,   628,   628,   629,   629,   629,
     629,   629,   629,   629,   629,   629,   629,   629,   629,   629,
     631,   630,   632,   632,   632,   634,   633,   636,   635,   637,
     638,   640,   639,   641,   641,   642,   642,   642,   644,   643,
     645,   645,   645,   646,   646,   646,   646,   646,   648,   647,
     650,   649,   651,   651,   651,   652,   652,   652,   652,   652,
     652,   652,   654,   653,   655,   657,   656,   659,   658,   661,
     660,   662,   662,   663,   663,   663,   665,   664,   666,   666,
     666,   667,   667,   667,   667,   667,   667,   667,   669,   668,
     671,   670,   673,   672,   674,   674,   674,   675,   675,   675,
     675,   675,   675,   676,   678,   677,   679,   681,   680,   683,
     682,   685,   684,   686,   686,   686,   687,   687,   687,   687,
     687,   687,   687,   687,   687,   687,   687,   688,   690,   689,
     691,   693,   692,   694,   695,   697,   696,   698,   698,   700,
     699,   702,   701,   704,   703,   705,   705,   705,   706,   706,
     708,   707,   709,   711,   710,   712,   712,   712,   714,   713,
     715,   715,   715,   716,   716,   716,   716,   716,   716,   716,
     717,   719,   718,   721,   720,   722,   722,   722,   724,   723,
     725,   725,   725,   726,   726,   726,   726,   726,   728,   727,
     729,   730,   731,   733,   732,   735,   734,   736,   736,   736,
     737,   737,   738
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
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     0,     4,     1,     1,     1,     3,     3,
       3,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     3,     2,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     0,     6,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     1,     3,
       2,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     3,     3,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       6,     0,     4,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     0,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       0,     4,     0,     4,     0,     4,     1,     0,     4,     3,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     0,     1,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     3,     3,     3,     0,     4,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     4,
       0,     4,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     4,     3,     3,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     0,     1,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     0,     6,     1,     3,     2,     0,
       4,     0,     1,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     3,     3,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     3,     0,     4,
       3,     3,     3,     0,     6,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     0,     4,     0,     4,     3,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     0,     4,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     0,     4,     0,     4,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     3,     0,     4,     3,     0,     4,     0,
       6,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       3,     0,     4,     3,     3,     0,     4,     1,     1,     0,
       4,     0,     6,     0,     4,     1,     3,     2,     1,     1,
       0,     6,     3,     0,     6,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     6,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     0,     4,
       3,     3,     3,     0,     4,     0,     6,     1,     3,     2,
       1,     1,     3
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
  "\"trust-anchor\"", "\"cert-file\"", "\"key-file\"", "\"key-password\"",
  "\"cipher-list\"", "\"preferred-lifetime\"",
  "\"min-preferred-lifetime\"", "\"max-preferred-lifetime\"",
  "\"valid-lifetime\"", "\"min-valid-lifetime\"", "\"max-valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"calculate-tee-times\"",
  "\"t1-percent\"", "\"t2-percent\"", "\"cache-threshold\"",
  "\"cache-max-age\"", "\"decline-probation-period\"", "\"server-tag\"",
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
  "key_password", "$@47", "cipher_list", "$@48", "sanity_checks", "$@49",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@50",
  "extended_info_checks", "$@51", "mac_sources", "$@52",
  "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@53",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@54",
  "dhcp_multi_threading", "$@55", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@56", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@57",
  "sub_hooks_library", "$@58", "hooks_params", "hooks_param", "library",
  "$@59", "parameters", "$@60", "expired_leases_processing", "$@61",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@62",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@63",
  "sub_subnet6", "$@64", "subnet6_params", "subnet6_param", "subnet",
  "$@65", "interface", "$@66", "interface_id", "$@67", "client_class",
  "$@68", "network_client_classes", "$@69", "require_client_classes",
  "$@70", "evaluate_additional_classes", "$@71", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "id",
  "rapid_commit", "shared_networks", "$@72", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@73",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@74", "sub_option_def_list", "$@75", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@76",
  "sub_option_def", "$@77", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@78",
  "option_def_record_types", "$@79", "space", "$@80", "option_def_space",
  "option_def_encapsulate", "$@81", "option_def_array", "option_data_list",
  "$@82", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@83", "sub_option_data", "$@84",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@85",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "option_data_never_send",
  "option_data_client_classes", "$@86", "pools_list", "$@87",
  "pools_list_content", "not_empty_pools_list", "pool_list_entry", "$@88",
  "sub_pool6", "$@89", "pool_params", "pool_param", "pool_entry", "$@90",
  "pool_id", "user_context", "$@91", "comment", "$@92", "pd_pools_list",
  "$@93", "pd_pools_list_content", "not_empty_pd_pools_list",
  "pd_pool_entry", "$@94", "sub_pd_pool", "$@95", "pd_pool_params",
  "pd_pool_param", "pd_prefix", "$@96", "pd_prefix_len", "excluded_prefix",
  "$@97", "excluded_prefix_len", "pd_delegated_len", "reservations",
  "$@98", "reservations_list", "not_empty_reservations_list",
  "reservation", "$@99", "sub_reservation", "$@100", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@101", "prefixes", "$@102", "excluded_prefixes", "$@103", "duid",
  "$@104", "hw_address", "$@105", "hostname", "$@106", "flex_id_value",
  "$@107", "reservation_client_classes", "$@108", "relay", "$@109",
  "relay_map", "client_classes", "$@110", "client_classes_list",
  "client_class_entry", "$@111", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@112",
  "client_class_template_test", "$@113", "only_if_required",
  "only_in_additional_list", "server_id", "$@114", "server_id_params",
  "server_id_param", "server_id_type", "$@115", "duid_type", "htype",
  "identifier", "$@116", "time", "enterprise_id", "dhcp4o6_port",
  "control_socket", "$@117", "control_sockets", "$@118",
  "control_socket_list", "not_empty_control_socket_list",
  "control_socket_entry", "$@119", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@120",
  "control_socket_type_value", "control_socket_name", "$@121",
  "control_socket_address", "$@122", "control_socket_port",
  "cert_required", "http_headers", "$@123", "http_header_list",
  "not_empty_http_header_list", "http_header", "$@124",
  "http_header_params", "http_header_param", "header_value", "$@125",
  "authentication", "$@126", "auth_params", "auth_param", "auth_type",
  "$@127", "auth_type_value", "realm", "$@128", "directory", "$@129",
  "clients", "$@130", "clients_list", "not_empty_clients_list",
  "basic_auth", "$@131", "clients_params", "clients_param", "user_file",
  "$@132", "password_file", "$@133", "dhcp_queue_control", "$@134",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@135", "capacity", "arbitrary_map_entry", "$@136",
  "dhcp_ddns", "$@137", "sub_dhcp_ddns", "$@138", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@139", "server_port",
  "sender_ip", "$@140", "sender_port", "max_queue_size", "ncr_protocol",
  "$@141", "ncr_protocol_value", "ncr_format", "$@142", "config_control",
  "$@143", "sub_config_control", "$@144", "config_control_params",
  "config_control_param", "config_databases", "$@145",
  "config_fetch_wait_time", "loggers", "$@146", "loggers_entries",
  "logger_entry", "$@147", "logger_params", "logger_param", "debuglevel",
  "severity", "$@148", "output_options_list", "$@149",
  "output_options_list_content", "output_entry", "$@150",
  "output_params_list", "output_params", "output", "$@151", "flush",
  "maxsize", "maxver", "pattern", "$@152", "compatibility", "$@153",
  "compatibility_params", "compatibility_param", "lenient_option_parsing", YY_NULLPTR
  };
#endif


#if PARSER6_DEBUG
  const short
  Dhcp6Parser::yyrline_[] =
  {
       0,   333,   333,   333,   334,   334,   335,   335,   336,   336,
     337,   337,   338,   338,   339,   339,   340,   340,   341,   341,
     342,   342,   343,   343,   344,   344,   345,   345,   346,   346,
     354,   355,   356,   357,   358,   359,   360,   363,   368,   368,
     379,   382,   383,   386,   391,   397,   402,   402,   409,   410,
     413,   417,   421,   427,   427,   434,   435,   438,   442,   446,
     456,   465,   465,   480,   480,   494,   497,   503,   503,   512,
     513,   514,   521,   522,   523,   524,   525,   526,   527,   528,
     529,   530,   531,   532,   533,   534,   535,   536,   537,   538,
     539,   540,   541,   542,   543,   544,   545,   546,   547,   548,
     549,   550,   551,   552,   553,   554,   555,   556,   557,   558,
     559,   560,   561,   562,   563,   564,   565,   566,   567,   568,
     569,   570,   571,   572,   573,   574,   575,   576,   577,   578,
     579,   580,   581,   582,   583,   584,   585,   586,   587,   588,
     589,   590,   591,   592,   595,   595,   605,   611,   617,   623,
     629,   635,   641,   647,   653,   659,   665,   671,   677,   683,
     689,   695,   701,   707,   707,   716,   719,   722,   725,   728,
     734,   734,   743,   743,   752,   761,   771,   771,   780,   783,
     786,   789,   794,   800,   806,   812,   818,   818,   827,   827,
     836,   842,   848,   854,   854,   863,   869,   869,   878,   878,
     887,   893,   899,   905,   905,   917,   917,   926,   927,   928,
     933,   934,   935,   936,   937,   938,   939,   940,   943,   943,
     954,   960,   966,   972,   978,   978,   991,   991,  1004,  1004,
    1015,  1016,  1019,  1020,  1021,  1026,  1026,  1036,  1037,  1038,
    1043,  1044,  1045,  1046,  1047,  1048,  1049,  1050,  1051,  1052,
    1053,  1054,  1055,  1056,  1057,  1058,  1059,  1060,  1061,  1062,
    1063,  1064,  1065,  1066,  1069,  1069,  1078,  1078,  1087,  1087,
    1096,  1096,  1105,  1111,  1111,  1120,  1126,  1132,  1138,  1144,
    1150,  1156,  1162,  1168,  1168,  1176,  1177,  1178,  1181,  1187,
    1193,  1199,  1199,  1208,  1208,  1217,  1217,  1226,  1226,  1235,
    1235,  1244,  1244,  1255,  1256,  1257,  1262,  1263,  1266,  1266,
    1285,  1285,  1303,  1303,  1314,  1315,  1316,  1321,  1322,  1325,
    1330,  1335,  1335,  1346,  1347,  1348,  1353,  1354,  1355,  1358,
    1363,  1370,  1370,  1383,  1383,  1396,  1397,  1398,  1403,  1404,
    1405,  1406,  1407,  1408,  1411,  1417,  1423,  1429,  1429,  1440,
    1441,  1444,  1445,  1446,  1451,  1451,  1461,  1461,  1471,  1472,
    1473,  1476,  1479,  1480,  1483,  1483,  1492,  1492,  1501,  1501,
    1513,  1514,  1515,  1520,  1521,  1522,  1523,  1524,  1525,  1528,
    1534,  1540,  1546,  1552,  1558,  1567,  1567,  1581,  1582,  1585,
    1586,  1587,  1596,  1596,  1622,  1622,  1633,  1634,  1635,  1641,
    1642,  1643,  1644,  1645,  1646,  1647,  1648,  1649,  1650,  1651,
    1652,  1653,  1654,  1655,  1656,  1657,  1658,  1659,  1660,  1661,
    1662,  1663,  1664,  1665,  1666,  1667,  1668,  1669,  1670,  1671,
    1672,  1673,  1674,  1675,  1676,  1677,  1678,  1679,  1680,  1681,
    1682,  1683,  1684,  1685,  1686,  1687,  1688,  1689,  1690,  1691,
    1694,  1694,  1703,  1703,  1712,  1712,  1721,  1721,  1731,  1731,
    1743,  1743,  1754,  1754,  1765,  1771,  1777,  1783,  1789,  1797,
    1797,  1809,  1810,  1814,  1815,  1816,  1821,  1821,  1829,  1830,
    1831,  1836,  1837,  1838,  1839,  1840,  1841,  1842,  1843,  1844,
    1845,  1846,  1847,  1848,  1849,  1850,  1851,  1852,  1853,  1854,
    1855,  1856,  1857,  1858,  1859,  1860,  1861,  1862,  1863,  1864,
    1865,  1866,  1867,  1868,  1869,  1870,  1871,  1872,  1873,  1874,
    1875,  1876,  1877,  1878,  1879,  1880,  1881,  1882,  1883,  1890,
    1890,  1904,  1904,  1913,  1914,  1917,  1918,  1919,  1926,  1926,
    1941,  1941,  1955,  1956,  1959,  1960,  1961,  1966,  1967,  1968,
    1969,  1970,  1971,  1972,  1973,  1974,  1975,  1978,  1980,  1986,
    1988,  1988,  1997,  1997,  2006,  2006,  2015,  2017,  2017,  2026,
    2036,  2036,  2049,  2050,  2055,  2056,  2057,  2064,  2064,  2076,
    2076,  2088,  2089,  2094,  2095,  2096,  2103,  2104,  2105,  2106,
    2107,  2108,  2109,  2110,  2111,  2112,  2113,  2116,  2118,  2118,
    2127,  2129,  2131,  2137,  2143,  2149,  2149,  2163,  2163,  2176,
    2177,  2180,  2181,  2182,  2187,  2187,  2197,  2197,  2207,  2208,
    2209,  2214,  2215,  2216,  2217,  2218,  2219,  2220,  2221,  2222,
    2223,  2224,  2225,  2226,  2227,  2228,  2229,  2230,  2231,  2232,
    2233,  2234,  2235,  2236,  2237,  2240,  2240,  2249,  2255,  2255,
    2280,  2280,  2310,  2310,  2323,  2324,  2327,  2328,  2329,  2334,
    2334,  2346,  2346,  2358,  2359,  2360,  2365,  2366,  2367,  2368,
    2369,  2370,  2371,  2372,  2373,  2374,  2375,  2376,  2377,  2378,
    2381,  2381,  2390,  2396,  2396,  2405,  2411,  2420,  2420,  2431,
    2432,  2435,  2436,  2437,  2442,  2442,  2451,  2451,  2460,  2461,
    2464,  2465,  2466,  2472,  2473,  2474,  2475,  2476,  2477,  2478,
    2479,  2480,  2481,  2482,  2483,  2486,  2486,  2497,  2497,  2508,
    2508,  2519,  2519,  2528,  2528,  2537,  2537,  2546,  2546,  2555,
    2555,  2569,  2569,  2580,  2586,  2586,  2597,  2598,  2599,  2604,
    2604,  2614,  2615,  2618,  2619,  2620,  2625,  2626,  2627,  2628,
    2629,  2630,  2631,  2632,  2633,  2634,  2635,  2636,  2637,  2638,
    2639,  2642,  2644,  2644,  2653,  2653,  2663,  2669,  2678,  2678,
    2691,  2692,  2693,  2698,  2699,  2700,  2701,  2702,  2703,  2704,
    2705,  2706,  2709,  2709,  2717,  2718,  2719,  2722,  2728,  2728,
    2737,  2743,  2751,  2759,  2759,  2771,  2771,  2783,  2784,  2787,
    2788,  2789,  2794,  2794,  2802,  2803,  2804,  2809,  2810,  2811,
    2812,  2813,  2814,  2815,  2816,  2817,  2818,  2819,  2820,  2821,
    2824,  2824,  2833,  2834,  2835,  2838,  2838,  2848,  2848,  2858,
    2864,  2870,  2870,  2881,  2882,  2885,  2886,  2887,  2892,  2892,
    2900,  2901,  2902,  2907,  2908,  2909,  2910,  2911,  2914,  2914,
    2925,  2925,  2938,  2939,  2940,  2945,  2946,  2947,  2948,  2949,
    2950,  2951,  2954,  2954,  2962,  2965,  2965,  2974,  2974,  2983,
    2983,  2994,  2995,  2998,  2999,  3000,  3005,  3005,  3013,  3014,
    3015,  3020,  3021,  3022,  3023,  3024,  3025,  3026,  3029,  3029,
    3038,  3038,  3049,  3049,  3062,  3063,  3064,  3069,  3070,  3071,
    3072,  3073,  3074,  3077,  3083,  3083,  3092,  3098,  3098,  3108,
    3108,  3121,  3121,  3131,  3132,  3133,  3138,  3139,  3140,  3141,
    3142,  3143,  3144,  3145,  3146,  3147,  3148,  3151,  3157,  3157,
    3166,  3172,  3172,  3181,  3187,  3193,  3193,  3202,  3203,  3206,
    3206,  3217,  3217,  3229,  3229,  3239,  3240,  3241,  3247,  3248,
    3251,  3251,  3262,  3270,  3270,  3283,  3284,  3285,  3291,  3291,
    3299,  3300,  3301,  3306,  3307,  3308,  3309,  3310,  3311,  3312,
    3315,  3321,  3321,  3330,  3330,  3341,  3342,  3343,  3348,  3348,
    3356,  3357,  3358,  3363,  3364,  3365,  3366,  3367,  3370,  3370,
    3379,  3385,  3391,  3397,  3397,  3406,  3406,  3417,  3418,  3419,
    3424,  3425,  3428
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
#line 7103 "dhcp6_parser.cc"

#line 3434 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
