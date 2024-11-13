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
#line 320 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 413 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 320 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 419 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 320 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 425 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 320 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 431 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 320 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 437 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 320 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 443 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 320 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 449 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 320 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 455 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 320 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 461 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 320 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 467 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
#line 320 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 473 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 320 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 479 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 320 "dhcp6_parser.yy"
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
#line 329 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 766 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 330 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 772 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 331 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 778 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 332 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 784 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 333 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 790 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 334 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 796 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 335 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 802 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 336 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 808 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 337 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 814 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 338 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 820 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 339 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 826 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 340 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 832 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 341 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 838 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 342 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 844 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 350 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 850 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 351 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 856 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 352 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 862 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 353 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 868 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 354 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 874 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 355 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 880 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 356 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 886 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 359 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 895 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 364 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 906 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 369 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 916 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 375 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 922 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 382 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 932 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 387 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 943 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 393 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 951 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 398 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 960 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 401 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 968 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 409 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 977 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 413 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 986 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 417 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 994 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 423 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 1002 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 425 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1011 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 434 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1020 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 438 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1029 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 442 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1037 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 452 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1048 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 461 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1059 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 466 "dhcp6_parser.yy"
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
#line 476 "dhcp6_parser.yy"
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
#line 485 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1097 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 493 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1105 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 499 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1115 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 503 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1124 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 510 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1132 "dhcp6_parser.cc"
    break;

  case 141: // $@21: %empty
#line 588 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1141 "dhcp6_parser.cc"
    break;

  case 142: // data_directory: "data-directory" $@21 ":" "constant string"
#line 591 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1151 "dhcp6_parser.cc"
    break;

  case 143: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 597 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1161 "dhcp6_parser.cc"
    break;

  case 144: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 603 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1171 "dhcp6_parser.cc"
    break;

  case 145: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 609 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1181 "dhcp6_parser.cc"
    break;

  case 146: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 615 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1191 "dhcp6_parser.cc"
    break;

  case 147: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 621 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1201 "dhcp6_parser.cc"
    break;

  case 148: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 627 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1211 "dhcp6_parser.cc"
    break;

  case 149: // renew_timer: "renew-timer" ":" "integer"
#line 633 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1221 "dhcp6_parser.cc"
    break;

  case 150: // rebind_timer: "rebind-timer" ":" "integer"
#line 639 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1231 "dhcp6_parser.cc"
    break;

  case 151: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 645 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1241 "dhcp6_parser.cc"
    break;

  case 152: // t1_percent: "t1-percent" ":" "floating point"
#line 651 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1251 "dhcp6_parser.cc"
    break;

  case 153: // t2_percent: "t2-percent" ":" "floating point"
#line 657 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1261 "dhcp6_parser.cc"
    break;

  case 154: // cache_threshold: "cache-threshold" ":" "floating point"
#line 663 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1271 "dhcp6_parser.cc"
    break;

  case 155: // cache_max_age: "cache-max-age" ":" "integer"
#line 669 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1281 "dhcp6_parser.cc"
    break;

  case 156: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 675 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1291 "dhcp6_parser.cc"
    break;

  case 157: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 681 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1301 "dhcp6_parser.cc"
    break;

  case 158: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 687 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1311 "dhcp6_parser.cc"
    break;

  case 159: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 693 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1321 "dhcp6_parser.cc"
    break;

  case 160: // $@22: %empty
#line 699 "dhcp6_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1330 "dhcp6_parser.cc"
    break;

  case 161: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 702 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1339 "dhcp6_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "when-present"
#line 708 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1347 "dhcp6_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "never"
#line 711 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1355 "dhcp6_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "always"
#line 714 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1363 "dhcp6_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "when-not-present"
#line 717 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1371 "dhcp6_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "boolean"
#line 720 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1380 "dhcp6_parser.cc"
    break;

  case 167: // $@23: %empty
#line 726 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1389 "dhcp6_parser.cc"
    break;

  case 168: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 729 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1399 "dhcp6_parser.cc"
    break;

  case 169: // $@24: %empty
#line 735 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1408 "dhcp6_parser.cc"
    break;

  case 170: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 738 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1418 "dhcp6_parser.cc"
    break;

  case 171: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 744 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1428 "dhcp6_parser.cc"
    break;

  case 172: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 753 "dhcp6_parser.yy"
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
#line 763 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1451 "dhcp6_parser.cc"
    break;

  case 174: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 766 "dhcp6_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 175: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 772 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1468 "dhcp6_parser.cc"
    break;

  case 176: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 775 "dhcp6_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1476 "dhcp6_parser.cc"
    break;

  case 177: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 778 "dhcp6_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1484 "dhcp6_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 781 "dhcp6_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1492 "dhcp6_parser.cc"
    break;

  case 179: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 786 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1502 "dhcp6_parser.cc"
    break;

  case 180: // $@26: %empty
#line 792 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1511 "dhcp6_parser.cc"
    break;

  case 181: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 795 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1521 "dhcp6_parser.cc"
    break;

  case 182: // $@27: %empty
#line 801 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1530 "dhcp6_parser.cc"
    break;

  case 183: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 804 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1540 "dhcp6_parser.cc"
    break;

  case 184: // store_extended_info: "store-extended-info" ":" "boolean"
#line 810 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1550 "dhcp6_parser.cc"
    break;

  case 185: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 816 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1560 "dhcp6_parser.cc"
    break;

  case 186: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 822 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1570 "dhcp6_parser.cc"
    break;

  case 187: // $@28: %empty
#line 828 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1579 "dhcp6_parser.cc"
    break;

  case 188: // server_tag: "server-tag" $@28 ":" "constant string"
#line 831 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1589 "dhcp6_parser.cc"
    break;

  case 189: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 837 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1599 "dhcp6_parser.cc"
    break;

  case 190: // $@29: %empty
#line 843 "dhcp6_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1608 "dhcp6_parser.cc"
    break;

  case 191: // allocator: "allocator" $@29 ":" "constant string"
#line 846 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1618 "dhcp6_parser.cc"
    break;

  case 192: // $@30: %empty
#line 852 "dhcp6_parser.yy"
                           {
    ctx.unique("pd-allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1627 "dhcp6_parser.cc"
    break;

  case 193: // pd_allocator: "pd-allocator" $@30 ":" "constant string"
#line 855 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-allocator", al);
    ctx.leave();
}
#line 1637 "dhcp6_parser.cc"
    break;

  case 194: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 861 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1647 "dhcp6_parser.cc"
    break;

  case 195: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 867 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1657 "dhcp6_parser.cc"
    break;

  case 196: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 873 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1667 "dhcp6_parser.cc"
    break;

  case 197: // $@31: %empty
#line 879 "dhcp6_parser.yy"
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
#line 885 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1689 "dhcp6_parser.cc"
    break;

  case 199: // $@32: %empty
#line 891 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1699 "dhcp6_parser.cc"
    break;

  case 200: // sub_interfaces6: "{" $@32 interfaces_config_params "}"
#line 895 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1708 "dhcp6_parser.cc"
    break;

  case 203: // interfaces_config_params: interfaces_config_params ","
#line 902 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1716 "dhcp6_parser.cc"
    break;

  case 212: // $@33: %empty
#line 917 "dhcp6_parser.yy"
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
#line 923 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1737 "dhcp6_parser.cc"
    break;

  case 214: // re_detect: "re-detect" ":" "boolean"
#line 928 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1747 "dhcp6_parser.cc"
    break;

  case 215: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 934 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1757 "dhcp6_parser.cc"
    break;

  case 216: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 940 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1767 "dhcp6_parser.cc"
    break;

  case 217: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 946 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1777 "dhcp6_parser.cc"
    break;

  case 218: // $@34: %empty
#line 952 "dhcp6_parser.yy"
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
#line 958 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1800 "dhcp6_parser.cc"
    break;

  case 220: // $@35: %empty
#line 965 "dhcp6_parser.yy"
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
#line 971 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1823 "dhcp6_parser.cc"
    break;

  case 222: // $@36: %empty
#line 978 "dhcp6_parser.yy"
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
#line 984 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1844 "dhcp6_parser.cc"
    break;

  case 228: // not_empty_database_list: not_empty_database_list ","
#line 995 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1852 "dhcp6_parser.cc"
    break;

  case 229: // $@37: %empty
#line 1000 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1862 "dhcp6_parser.cc"
    break;

  case 230: // database: "{" $@37 database_map_params "}"
#line 1004 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1872 "dhcp6_parser.cc"
    break;

  case 233: // database_map_params: database_map_params ","
#line 1012 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1880 "dhcp6_parser.cc"
    break;

  case 257: // $@38: %empty
#line 1042 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1889 "dhcp6_parser.cc"
    break;

  case 258: // database_type: "type" $@38 ":" "constant string"
#line 1045 "dhcp6_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 1899 "dhcp6_parser.cc"
    break;

  case 259: // $@39: %empty
#line 1051 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1908 "dhcp6_parser.cc"
    break;

  case 260: // user: "user" $@39 ":" "constant string"
#line 1054 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1918 "dhcp6_parser.cc"
    break;

  case 261: // $@40: %empty
#line 1060 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1927 "dhcp6_parser.cc"
    break;

  case 262: // password: "password" $@40 ":" "constant string"
#line 1063 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1937 "dhcp6_parser.cc"
    break;

  case 263: // $@41: %empty
#line 1069 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1946 "dhcp6_parser.cc"
    break;

  case 264: // host: "host" $@41 ":" "constant string"
#line 1072 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1956 "dhcp6_parser.cc"
    break;

  case 265: // port: "port" ":" "integer"
#line 1078 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1966 "dhcp6_parser.cc"
    break;

  case 266: // $@42: %empty
#line 1084 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1975 "dhcp6_parser.cc"
    break;

  case 267: // name: "name" $@42 ":" "constant string"
#line 1087 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1985 "dhcp6_parser.cc"
    break;

  case 268: // persist: "persist" ":" "boolean"
#line 1093 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1995 "dhcp6_parser.cc"
    break;

  case 269: // lfc_interval: "lfc-interval" ":" "integer"
#line 1099 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2005 "dhcp6_parser.cc"
    break;

  case 270: // readonly: "readonly" ":" "boolean"
#line 1105 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2015 "dhcp6_parser.cc"
    break;

  case 271: // connect_timeout: "connect-timeout" ":" "integer"
#line 1111 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2025 "dhcp6_parser.cc"
    break;

  case 272: // read_timeout: "read-timeout" ":" "integer"
#line 1117 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2035 "dhcp6_parser.cc"
    break;

  case 273: // write_timeout: "write-timeout" ":" "integer"
#line 1123 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2045 "dhcp6_parser.cc"
    break;

  case 274: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1129 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2055 "dhcp6_parser.cc"
    break;

  case 275: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1135 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2065 "dhcp6_parser.cc"
    break;

  case 276: // $@43: %empty
#line 1141 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2074 "dhcp6_parser.cc"
    break;

  case 277: // on_fail: "on-fail" $@43 ":" on_fail_mode
#line 1144 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2083 "dhcp6_parser.cc"
    break;

  case 278: // on_fail_mode: "stop-retry-exit"
#line 1149 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2089 "dhcp6_parser.cc"
    break;

  case 279: // on_fail_mode: "serve-retry-exit"
#line 1150 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2095 "dhcp6_parser.cc"
    break;

  case 280: // on_fail_mode: "serve-retry-continue"
#line 1151 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2101 "dhcp6_parser.cc"
    break;

  case 281: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1154 "dhcp6_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2111 "dhcp6_parser.cc"
    break;

  case 282: // max_row_errors: "max-row-errors" ":" "integer"
#line 1160 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2121 "dhcp6_parser.cc"
    break;

  case 283: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1166 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2131 "dhcp6_parser.cc"
    break;

  case 284: // $@44: %empty
#line 1172 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2140 "dhcp6_parser.cc"
    break;

  case 285: // trust_anchor: "trust-anchor" $@44 ":" "constant string"
#line 1175 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2150 "dhcp6_parser.cc"
    break;

  case 286: // $@45: %empty
#line 1181 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2159 "dhcp6_parser.cc"
    break;

  case 287: // cert_file: "cert-file" $@45 ":" "constant string"
#line 1184 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2169 "dhcp6_parser.cc"
    break;

  case 288: // $@46: %empty
#line 1190 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2178 "dhcp6_parser.cc"
    break;

  case 289: // key_file: "key-file" $@46 ":" "constant string"
#line 1193 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2188 "dhcp6_parser.cc"
    break;

  case 290: // $@47: %empty
#line 1199 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2197 "dhcp6_parser.cc"
    break;

  case 291: // cipher_list: "cipher-list" $@47 ":" "constant string"
#line 1202 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2207 "dhcp6_parser.cc"
    break;

  case 292: // $@48: %empty
#line 1208 "dhcp6_parser.yy"
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
#line 1214 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2228 "dhcp6_parser.cc"
    break;

  case 296: // sanity_checks_params: sanity_checks_params ","
#line 1221 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2236 "dhcp6_parser.cc"
    break;

  case 299: // $@49: %empty
#line 1230 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2245 "dhcp6_parser.cc"
    break;

  case 300: // lease_checks: "lease-checks" $@49 ":" "constant string"
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
#line 2265 "dhcp6_parser.cc"
    break;

  case 301: // $@50: %empty
#line 1249 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2274 "dhcp6_parser.cc"
    break;

  case 302: // extended_info_checks: "extended-info-checks" $@50 ":" "constant string"
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
#line 2293 "dhcp6_parser.cc"
    break;

  case 303: // $@51: %empty
#line 1267 "dhcp6_parser.yy"
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
#line 1273 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2314 "dhcp6_parser.cc"
    break;

  case 307: // mac_sources_list: mac_sources_list ","
#line 1280 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2322 "dhcp6_parser.cc"
    break;

  case 310: // duid_id: "duid"
#line 1289 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2331 "dhcp6_parser.cc"
    break;

  case 311: // string_id: "constant string"
#line 1294 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2340 "dhcp6_parser.cc"
    break;

  case 312: // $@52: %empty
#line 1299 "dhcp6_parser.yy"
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
#line 1305 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2361 "dhcp6_parser.cc"
    break;

  case 316: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1312 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2369 "dhcp6_parser.cc"
    break;

  case 320: // hw_address_id: "hw-address"
#line 1322 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2378 "dhcp6_parser.cc"
    break;

  case 321: // flex_id: "flex-id"
#line 1327 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2387 "dhcp6_parser.cc"
    break;

  case 322: // $@53: %empty
#line 1334 "dhcp6_parser.yy"
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
#line 1340 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2408 "dhcp6_parser.cc"
    break;

  case 324: // $@54: %empty
#line 1347 "dhcp6_parser.yy"
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
#line 1353 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2431 "dhcp6_parser.cc"
    break;

  case 328: // multi_threading_params: multi_threading_params ","
#line 1362 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2439 "dhcp6_parser.cc"
    break;

  case 335: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1375 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2449 "dhcp6_parser.cc"
    break;

  case 336: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1381 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2459 "dhcp6_parser.cc"
    break;

  case 337: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1387 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2469 "dhcp6_parser.cc"
    break;

  case 338: // $@55: %empty
#line 1393 "dhcp6_parser.yy"
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
#line 1399 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2490 "dhcp6_parser.cc"
    break;

  case 344: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1410 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2498 "dhcp6_parser.cc"
    break;

  case 345: // $@56: %empty
#line 1415 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2508 "dhcp6_parser.cc"
    break;

  case 346: // hooks_library: "{" $@56 hooks_params "}"
#line 1419 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2518 "dhcp6_parser.cc"
    break;

  case 347: // $@57: %empty
#line 1425 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2528 "dhcp6_parser.cc"
    break;

  case 348: // sub_hooks_library: "{" $@57 hooks_params "}"
#line 1429 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2538 "dhcp6_parser.cc"
    break;

  case 351: // hooks_params: hooks_params ","
#line 1437 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2546 "dhcp6_parser.cc"
    break;

  case 355: // $@58: %empty
#line 1447 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2555 "dhcp6_parser.cc"
    break;

  case 356: // library: "library" $@58 ":" "constant string"
#line 1450 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2565 "dhcp6_parser.cc"
    break;

  case 357: // $@59: %empty
#line 1456 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2574 "dhcp6_parser.cc"
    break;

  case 358: // parameters: "parameters" $@59 ":" map_value
#line 1459 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2583 "dhcp6_parser.cc"
    break;

  case 359: // $@60: %empty
#line 1465 "dhcp6_parser.yy"
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
#line 1471 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2605 "dhcp6_parser.cc"
    break;

  case 363: // expired_leases_params: expired_leases_params ","
#line 1479 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2613 "dhcp6_parser.cc"
    break;

  case 370: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1492 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2623 "dhcp6_parser.cc"
    break;

  case 371: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1498 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2633 "dhcp6_parser.cc"
    break;

  case 372: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1504 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2643 "dhcp6_parser.cc"
    break;

  case 373: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1510 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2653 "dhcp6_parser.cc"
    break;

  case 374: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1516 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2663 "dhcp6_parser.cc"
    break;

  case 375: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1522 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2673 "dhcp6_parser.cc"
    break;

  case 376: // $@61: %empty
#line 1531 "dhcp6_parser.yy"
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
#line 1537 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2694 "dhcp6_parser.cc"
    break;

  case 382: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1551 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2702 "dhcp6_parser.cc"
    break;

  case 383: // $@62: %empty
#line 1560 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2712 "dhcp6_parser.cc"
    break;

  case 384: // subnet6: "{" $@62 subnet6_params "}"
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
#line 2738 "dhcp6_parser.cc"
    break;

  case 385: // $@63: %empty
#line 1586 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2748 "dhcp6_parser.cc"
    break;

  case 386: // sub_subnet6: "{" $@63 subnet6_params "}"
#line 1590 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2758 "dhcp6_parser.cc"
    break;

  case 389: // subnet6_params: subnet6_params ","
#line 1599 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2766 "dhcp6_parser.cc"
    break;

  case 437: // $@64: %empty
#line 1654 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2775 "dhcp6_parser.cc"
    break;

  case 438: // subnet: "subnet" $@64 ":" "constant string"
#line 1657 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2785 "dhcp6_parser.cc"
    break;

  case 439: // $@65: %empty
#line 1663 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2794 "dhcp6_parser.cc"
    break;

  case 440: // interface: "interface" $@65 ":" "constant string"
#line 1666 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2804 "dhcp6_parser.cc"
    break;

  case 441: // $@66: %empty
#line 1672 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2813 "dhcp6_parser.cc"
    break;

  case 442: // interface_id: "interface-id" $@66 ":" "constant string"
#line 1675 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2823 "dhcp6_parser.cc"
    break;

  case 443: // $@67: %empty
#line 1681 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2832 "dhcp6_parser.cc"
    break;

  case 444: // client_class: "client-class" $@67 ":" "constant string"
#line 1684 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2842 "dhcp6_parser.cc"
    break;

  case 445: // $@68: %empty
#line 1691 "dhcp6_parser.yy"
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
#line 1697 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2863 "dhcp6_parser.cc"
    break;

  case 447: // $@69: %empty
#line 1702 "dhcp6_parser.yy"
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
#line 1708 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2884 "dhcp6_parser.cc"
    break;

  case 449: // reservations_global: "reservations-global" ":" "boolean"
#line 1713 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2894 "dhcp6_parser.cc"
    break;

  case 450: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1719 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2904 "dhcp6_parser.cc"
    break;

  case 451: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1725 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2914 "dhcp6_parser.cc"
    break;

  case 452: // id: "id" ":" "integer"
#line 1731 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2924 "dhcp6_parser.cc"
    break;

  case 453: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1737 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2934 "dhcp6_parser.cc"
    break;

  case 454: // $@70: %empty
#line 1745 "dhcp6_parser.yy"
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
#line 1751 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2955 "dhcp6_parser.cc"
    break;

  case 460: // shared_networks_list: shared_networks_list ","
#line 1764 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2963 "dhcp6_parser.cc"
    break;

  case 461: // $@71: %empty
#line 1769 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2973 "dhcp6_parser.cc"
    break;

  case 462: // shared_network: "{" $@71 shared_network_params "}"
#line 1773 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2981 "dhcp6_parser.cc"
    break;

  case 465: // shared_network_params: shared_network_params ","
#line 1779 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2989 "dhcp6_parser.cc"
    break;

  case 510: // $@72: %empty
#line 1834 "dhcp6_parser.yy"
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
#line 1840 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3010 "dhcp6_parser.cc"
    break;

  case 512: // $@73: %empty
#line 1848 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3019 "dhcp6_parser.cc"
    break;

  case 513: // sub_option_def_list: "{" $@73 option_def_list "}"
#line 1851 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 3027 "dhcp6_parser.cc"
    break;

  case 518: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1863 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3035 "dhcp6_parser.cc"
    break;

  case 519: // $@74: %empty
#line 1870 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3045 "dhcp6_parser.cc"
    break;

  case 520: // option_def_entry: "{" $@74 option_def_params "}"
#line 1874 "dhcp6_parser.yy"
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
#line 1885 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3067 "dhcp6_parser.cc"
    break;

  case 522: // sub_option_def: "{" $@75 option_def_params "}"
#line 1889 "dhcp6_parser.yy"
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
#line 1905 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3087 "dhcp6_parser.cc"
    break;

  case 539: // code: "code" ":" "integer"
#line 1924 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3097 "dhcp6_parser.cc"
    break;

  case 541: // $@76: %empty
#line 1932 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3106 "dhcp6_parser.cc"
    break;

  case 542: // option_def_type: "type" $@76 ":" "constant string"
#line 1935 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3116 "dhcp6_parser.cc"
    break;

  case 543: // $@77: %empty
#line 1941 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3125 "dhcp6_parser.cc"
    break;

  case 544: // option_def_record_types: "record-types" $@77 ":" "constant string"
#line 1944 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3135 "dhcp6_parser.cc"
    break;

  case 545: // $@78: %empty
#line 1950 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3144 "dhcp6_parser.cc"
    break;

  case 546: // space: "space" $@78 ":" "constant string"
#line 1953 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3154 "dhcp6_parser.cc"
    break;

  case 548: // $@79: %empty
#line 1961 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3163 "dhcp6_parser.cc"
    break;

  case 549: // option_def_encapsulate: "encapsulate" $@79 ":" "constant string"
#line 1964 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3173 "dhcp6_parser.cc"
    break;

  case 550: // option_def_array: "array" ":" "boolean"
#line 1970 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3183 "dhcp6_parser.cc"
    break;

  case 551: // $@80: %empty
#line 1980 "dhcp6_parser.yy"
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
#line 1986 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3204 "dhcp6_parser.cc"
    break;

  case 557: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2001 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3212 "dhcp6_parser.cc"
    break;

  case 558: // $@81: %empty
#line 2008 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3222 "dhcp6_parser.cc"
    break;

  case 559: // option_data_entry: "{" $@81 option_data_params "}"
#line 2012 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3231 "dhcp6_parser.cc"
    break;

  case 560: // $@82: %empty
#line 2020 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3241 "dhcp6_parser.cc"
    break;

  case 561: // sub_option_data: "{" $@82 option_data_params "}"
#line 2024 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3250 "dhcp6_parser.cc"
    break;

  case 566: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2040 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3258 "dhcp6_parser.cc"
    break;

  case 579: // $@83: %empty
#line 2062 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3267 "dhcp6_parser.cc"
    break;

  case 580: // option_data_data: "data" $@83 ":" "constant string"
#line 2065 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3277 "dhcp6_parser.cc"
    break;

  case 583: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2075 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3287 "dhcp6_parser.cc"
    break;

  case 584: // option_data_always_send: "always-send" ":" "boolean"
#line 2081 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3297 "dhcp6_parser.cc"
    break;

  case 585: // option_data_never_send: "never-send" ":" "boolean"
#line 2087 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3307 "dhcp6_parser.cc"
    break;

  case 586: // $@84: %empty
#line 2093 "dhcp6_parser.yy"
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
#line 2099 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3328 "dhcp6_parser.cc"
    break;

  case 588: // $@85: %empty
#line 2107 "dhcp6_parser.yy"
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
#line 2113 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3349 "dhcp6_parser.cc"
    break;

  case 594: // not_empty_pools_list: not_empty_pools_list ","
#line 2126 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3357 "dhcp6_parser.cc"
    break;

  case 595: // $@86: %empty
#line 2131 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3367 "dhcp6_parser.cc"
    break;

  case 596: // pool_list_entry: "{" $@86 pool_params "}"
#line 2135 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3377 "dhcp6_parser.cc"
    break;

  case 597: // $@87: %empty
#line 2141 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3387 "dhcp6_parser.cc"
    break;

  case 598: // sub_pool6: "{" $@87 pool_params "}"
#line 2145 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3397 "dhcp6_parser.cc"
    break;

  case 601: // pool_params: pool_params ","
#line 2153 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3405 "dhcp6_parser.cc"
    break;

  case 611: // $@88: %empty
#line 2169 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3414 "dhcp6_parser.cc"
    break;

  case 612: // pool_entry: "pool" $@88 ":" "constant string"
#line 2172 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3424 "dhcp6_parser.cc"
    break;

  case 613: // pool_id: "pool-id" ":" "integer"
#line 2178 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3434 "dhcp6_parser.cc"
    break;

  case 614: // $@89: %empty
#line 2184 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3442 "dhcp6_parser.cc"
    break;

  case 615: // user_context: "user-context" $@89 ":" map_value
#line 2186 "dhcp6_parser.yy"
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
#line 2209 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3477 "dhcp6_parser.cc"
    break;

  case 617: // comment: "comment" $@90 ":" "constant string"
#line 2211 "dhcp6_parser.yy"
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
#line 2239 "dhcp6_parser.yy"
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
#line 2245 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3527 "dhcp6_parser.cc"
    break;

  case 624: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2258 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3535 "dhcp6_parser.cc"
    break;

  case 625: // $@92: %empty
#line 2263 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3545 "dhcp6_parser.cc"
    break;

  case 626: // pd_pool_entry: "{" $@92 pd_pool_params "}"
#line 2267 "dhcp6_parser.yy"
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
#line 2275 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3567 "dhcp6_parser.cc"
    break;

  case 628: // sub_pd_pool: "{" $@93 pd_pool_params "}"
#line 2279 "dhcp6_parser.yy"
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
#line 2289 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3587 "dhcp6_parser.cc"
    break;

  case 645: // $@94: %empty
#line 2309 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3596 "dhcp6_parser.cc"
    break;

  case 646: // pd_prefix: "prefix" $@94 ":" "constant string"
#line 2312 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3606 "dhcp6_parser.cc"
    break;

  case 647: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2318 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3616 "dhcp6_parser.cc"
    break;

  case 648: // $@95: %empty
#line 2324 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3625 "dhcp6_parser.cc"
    break;

  case 649: // excluded_prefix: "excluded-prefix" $@95 ":" "constant string"
#line 2327 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3635 "dhcp6_parser.cc"
    break;

  case 650: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2333 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3645 "dhcp6_parser.cc"
    break;

  case 651: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2339 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3655 "dhcp6_parser.cc"
    break;

  case 652: // $@96: %empty
#line 2348 "dhcp6_parser.yy"
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
#line 2354 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3676 "dhcp6_parser.cc"
    break;

  case 658: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2365 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3684 "dhcp6_parser.cc"
    break;

  case 659: // $@97: %empty
#line 2370 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3694 "dhcp6_parser.cc"
    break;

  case 660: // reservation: "{" $@97 reservation_params "}"
#line 2374 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3703 "dhcp6_parser.cc"
    break;

  case 661: // $@98: %empty
#line 2379 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3713 "dhcp6_parser.cc"
    break;

  case 662: // sub_reservation: "{" $@98 reservation_params "}"
#line 2383 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3722 "dhcp6_parser.cc"
    break;

  case 667: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2394 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3730 "dhcp6_parser.cc"
    break;

  case 680: // $@99: %empty
#line 2414 "dhcp6_parser.yy"
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
#line 2420 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3751 "dhcp6_parser.cc"
    break;

  case 682: // $@100: %empty
#line 2425 "dhcp6_parser.yy"
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
#line 2431 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3772 "dhcp6_parser.cc"
    break;

  case 684: // $@101: %empty
#line 2436 "dhcp6_parser.yy"
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
#line 2442 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3793 "dhcp6_parser.cc"
    break;

  case 686: // $@102: %empty
#line 2447 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3802 "dhcp6_parser.cc"
    break;

  case 687: // duid: "duid" $@102 ":" "constant string"
#line 2450 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3812 "dhcp6_parser.cc"
    break;

  case 688: // $@103: %empty
#line 2456 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3821 "dhcp6_parser.cc"
    break;

  case 689: // hw_address: "hw-address" $@103 ":" "constant string"
#line 2459 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3831 "dhcp6_parser.cc"
    break;

  case 690: // $@104: %empty
#line 2465 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3840 "dhcp6_parser.cc"
    break;

  case 691: // hostname: "hostname" $@104 ":" "constant string"
#line 2468 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3850 "dhcp6_parser.cc"
    break;

  case 692: // $@105: %empty
#line 2474 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3859 "dhcp6_parser.cc"
    break;

  case 693: // flex_id_value: "flex-id" $@105 ":" "constant string"
#line 2477 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3869 "dhcp6_parser.cc"
    break;

  case 694: // $@106: %empty
#line 2483 "dhcp6_parser.yy"
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
#line 2489 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3890 "dhcp6_parser.cc"
    break;

  case 696: // $@107: %empty
#line 2497 "dhcp6_parser.yy"
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
#line 2503 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3911 "dhcp6_parser.cc"
    break;

  case 699: // $@108: %empty
#line 2514 "dhcp6_parser.yy"
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
#line 2520 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3932 "dhcp6_parser.cc"
    break;

  case 703: // client_classes_list: client_classes_list ","
#line 2527 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3940 "dhcp6_parser.cc"
    break;

  case 704: // $@109: %empty
#line 2532 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3950 "dhcp6_parser.cc"
    break;

  case 705: // client_class_entry: "{" $@109 client_class_params "}"
#line 2536 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3960 "dhcp6_parser.cc"
    break;

  case 710: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2548 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3968 "dhcp6_parser.cc"
    break;

  case 727: // $@110: %empty
#line 2572 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3977 "dhcp6_parser.cc"
    break;

  case 728: // client_class_test: "test" $@110 ":" "constant string"
#line 2575 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3987 "dhcp6_parser.cc"
    break;

  case 729: // $@111: %empty
#line 2581 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3996 "dhcp6_parser.cc"
    break;

  case 730: // client_class_template_test: "template-test" $@111 ":" "constant string"
#line 2584 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4006 "dhcp6_parser.cc"
    break;

  case 731: // only_if_required: "only-if-required" ":" "boolean"
#line 2591 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4016 "dhcp6_parser.cc"
    break;

  case 732: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2597 "dhcp6_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4026 "dhcp6_parser.cc"
    break;

  case 733: // $@112: %empty
#line 2606 "dhcp6_parser.yy"
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
#line 2612 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4049 "dhcp6_parser.cc"
    break;

  case 737: // server_id_params: server_id_params ","
#line 2621 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4057 "dhcp6_parser.cc"
    break;

  case 747: // $@113: %empty
#line 2637 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 4066 "dhcp6_parser.cc"
    break;

  case 748: // server_id_type: "type" $@113 ":" duid_type
#line 2640 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4075 "dhcp6_parser.cc"
    break;

  case 749: // duid_type: "LLT"
#line 2645 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4081 "dhcp6_parser.cc"
    break;

  case 750: // duid_type: "EN"
#line 2646 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4087 "dhcp6_parser.cc"
    break;

  case 751: // duid_type: "LL"
#line 2647 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4093 "dhcp6_parser.cc"
    break;

  case 752: // htype: "htype" ":" "integer"
#line 2650 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4103 "dhcp6_parser.cc"
    break;

  case 753: // $@114: %empty
#line 2656 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4112 "dhcp6_parser.cc"
    break;

  case 754: // identifier: "identifier" $@114 ":" "constant string"
#line 2659 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4122 "dhcp6_parser.cc"
    break;

  case 755: // time: "time" ":" "integer"
#line 2665 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4132 "dhcp6_parser.cc"
    break;

  case 756: // enterprise_id: "enterprise-id" ":" "integer"
#line 2671 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4142 "dhcp6_parser.cc"
    break;

  case 757: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2679 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4152 "dhcp6_parser.cc"
    break;

  case 758: // $@115: %empty
#line 2687 "dhcp6_parser.yy"
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
#line 2694 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4174 "dhcp6_parser.cc"
    break;

  case 760: // $@116: %empty
#line 2699 "dhcp6_parser.yy"
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
#line 2706 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4196 "dhcp6_parser.cc"
    break;

  case 766: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2717 "dhcp6_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4204 "dhcp6_parser.cc"
    break;

  case 767: // $@117: %empty
#line 2722 "dhcp6_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4214 "dhcp6_parser.cc"
    break;

  case 768: // control_socket_entry: "{" $@117 control_socket_params "}"
#line 2726 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4222 "dhcp6_parser.cc"
    break;

  case 771: // control_socket_params: control_socket_params ","
#line 2732 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4230 "dhcp6_parser.cc"
    break;

  case 785: // $@118: %empty
#line 2752 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4239 "dhcp6_parser.cc"
    break;

  case 786: // control_socket_type: "socket-type" $@118 ":" control_socket_type_value
#line 2755 "dhcp6_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4248 "dhcp6_parser.cc"
    break;

  case 787: // control_socket_type_value: "unix"
#line 2761 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4254 "dhcp6_parser.cc"
    break;

  case 788: // control_socket_type_value: "http"
#line 2762 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4260 "dhcp6_parser.cc"
    break;

  case 789: // control_socket_type_value: "https"
#line 2763 "dhcp6_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4266 "dhcp6_parser.cc"
    break;

  case 790: // $@119: %empty
#line 2766 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4276 "dhcp6_parser.cc"
    break;

  case 791: // control_socket_name: "socket-name" $@119 ":" "constant string"
#line 2770 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4286 "dhcp6_parser.cc"
    break;

  case 792: // $@120: %empty
#line 2776 "dhcp6_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4296 "dhcp6_parser.cc"
    break;

  case 793: // control_socket_address: "socket-address" $@120 ":" "constant string"
#line 2780 "dhcp6_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4306 "dhcp6_parser.cc"
    break;

  case 794: // control_socket_port: "socket-port" ":" "integer"
#line 2786 "dhcp6_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4316 "dhcp6_parser.cc"
    break;

  case 795: // cert_required: "cert-required" ":" "boolean"
#line 2792 "dhcp6_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4326 "dhcp6_parser.cc"
    break;

  case 796: // $@121: %empty
#line 2798 "dhcp6_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4337 "dhcp6_parser.cc"
    break;

  case 797: // http_headers: "http-headers" $@121 ":" "[" http_header_list "]"
#line 2803 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4346 "dhcp6_parser.cc"
    break;

  case 802: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2814 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4354 "dhcp6_parser.cc"
    break;

  case 803: // $@122: %empty
#line 2819 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4364 "dhcp6_parser.cc"
    break;

  case 804: // http_header: "{" $@122 http_header_params "}"
#line 2823 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4372 "dhcp6_parser.cc"
    break;

  case 807: // http_header_params: http_header_params ","
#line 2829 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4380 "dhcp6_parser.cc"
    break;

  case 813: // $@123: %empty
#line 2841 "dhcp6_parser.yy"
             {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4389 "dhcp6_parser.cc"
    break;

  case 814: // value: "value" $@123 ":" "constant string"
#line 2844 "dhcp6_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4399 "dhcp6_parser.cc"
    break;

  case 815: // $@124: %empty
#line 2852 "dhcp6_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4411 "dhcp6_parser.cc"
    break;

  case 816: // authentication: "authentication" $@124 ":" "{" auth_params "}"
#line 2858 "dhcp6_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4422 "dhcp6_parser.cc"
    break;

  case 819: // auth_params: auth_params ","
#line 2867 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4430 "dhcp6_parser.cc"
    break;

  case 827: // $@125: %empty
#line 2881 "dhcp6_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4439 "dhcp6_parser.cc"
    break;

  case 828: // auth_type: "type" $@125 ":" auth_type_value
#line 2884 "dhcp6_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4448 "dhcp6_parser.cc"
    break;

  case 829: // auth_type_value: "basic"
#line 2889 "dhcp6_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4454 "dhcp6_parser.cc"
    break;

  case 830: // $@126: %empty
#line 2892 "dhcp6_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4463 "dhcp6_parser.cc"
    break;

  case 831: // realm: "realm" $@126 ":" "constant string"
#line 2895 "dhcp6_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4473 "dhcp6_parser.cc"
    break;

  case 832: // $@127: %empty
#line 2901 "dhcp6_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4482 "dhcp6_parser.cc"
    break;

  case 833: // directory: "directory" $@127 ":" "constant string"
#line 2904 "dhcp6_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4492 "dhcp6_parser.cc"
    break;

  case 834: // $@128: %empty
#line 2910 "dhcp6_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4504 "dhcp6_parser.cc"
    break;

  case 835: // clients: "clients" $@128 ":" "[" clients_list "]"
#line 2916 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4513 "dhcp6_parser.cc"
    break;

  case 840: // not_empty_clients_list: not_empty_clients_list ","
#line 2927 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4521 "dhcp6_parser.cc"
    break;

  case 841: // $@129: %empty
#line 2932 "dhcp6_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4531 "dhcp6_parser.cc"
    break;

  case 842: // basic_auth: "{" $@129 clients_params "}"
#line 2936 "dhcp6_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4539 "dhcp6_parser.cc"
    break;

  case 845: // clients_params: clients_params ","
#line 2942 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4547 "dhcp6_parser.cc"
    break;

  case 853: // $@130: %empty
#line 2956 "dhcp6_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4556 "dhcp6_parser.cc"
    break;

  case 854: // user_file: "user-file" $@130 ":" "constant string"
#line 2959 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4566 "dhcp6_parser.cc"
    break;

  case 855: // $@131: %empty
#line 2965 "dhcp6_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4575 "dhcp6_parser.cc"
    break;

  case 856: // password_file: "password-file" $@131 ":" "constant string"
#line 2968 "dhcp6_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4585 "dhcp6_parser.cc"
    break;

  case 857: // $@132: %empty
#line 2976 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4597 "dhcp6_parser.cc"
    break;

  case 858: // dhcp_queue_control: "dhcp-queue-control" $@132 ":" "{" queue_control_params "}"
#line 2982 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4608 "dhcp6_parser.cc"
    break;

  case 861: // queue_control_params: queue_control_params ","
#line 2991 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4616 "dhcp6_parser.cc"
    break;

  case 868: // enable_queue: "enable-queue" ":" "boolean"
#line 3004 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4626 "dhcp6_parser.cc"
    break;

  case 869: // $@133: %empty
#line 3010 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4635 "dhcp6_parser.cc"
    break;

  case 870: // queue_type: "queue-type" $@133 ":" "constant string"
#line 3013 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4645 "dhcp6_parser.cc"
    break;

  case 871: // capacity: "capacity" ":" "integer"
#line 3019 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4655 "dhcp6_parser.cc"
    break;

  case 872: // $@134: %empty
#line 3025 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4664 "dhcp6_parser.cc"
    break;

  case 873: // arbitrary_map_entry: "constant string" $@134 ":" value
#line 3028 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4673 "dhcp6_parser.cc"
    break;

  case 874: // $@135: %empty
#line 3035 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4685 "dhcp6_parser.cc"
    break;

  case 875: // dhcp_ddns: "dhcp-ddns" $@135 ":" "{" dhcp_ddns_params "}"
#line 3041 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4696 "dhcp6_parser.cc"
    break;

  case 876: // $@136: %empty
#line 3048 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4706 "dhcp6_parser.cc"
    break;

  case 877: // sub_dhcp_ddns: "{" $@136 dhcp_ddns_params "}"
#line 3052 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4716 "dhcp6_parser.cc"
    break;

  case 880: // dhcp_ddns_params: dhcp_ddns_params ","
#line 3060 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4724 "dhcp6_parser.cc"
    break;

  case 892: // enable_updates: "enable-updates" ":" "boolean"
#line 3078 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4734 "dhcp6_parser.cc"
    break;

  case 893: // $@137: %empty
#line 3084 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4743 "dhcp6_parser.cc"
    break;

  case 894: // server_ip: "server-ip" $@137 ":" "constant string"
#line 3087 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4753 "dhcp6_parser.cc"
    break;

  case 895: // server_port: "server-port" ":" "integer"
#line 3093 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4763 "dhcp6_parser.cc"
    break;

  case 896: // $@138: %empty
#line 3099 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4772 "dhcp6_parser.cc"
    break;

  case 897: // sender_ip: "sender-ip" $@138 ":" "constant string"
#line 3102 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4782 "dhcp6_parser.cc"
    break;

  case 898: // sender_port: "sender-port" ":" "integer"
#line 3108 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4792 "dhcp6_parser.cc"
    break;

  case 899: // max_queue_size: "max-queue-size" ":" "integer"
#line 3114 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4802 "dhcp6_parser.cc"
    break;

  case 900: // $@139: %empty
#line 3120 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4811 "dhcp6_parser.cc"
    break;

  case 901: // ncr_protocol: "ncr-protocol" $@139 ":" ncr_protocol_value
#line 3123 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4820 "dhcp6_parser.cc"
    break;

  case 902: // ncr_protocol_value: "UDP"
#line 3129 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4826 "dhcp6_parser.cc"
    break;

  case 903: // ncr_protocol_value: "TCP"
#line 3130 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4832 "dhcp6_parser.cc"
    break;

  case 904: // $@140: %empty
#line 3133 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4841 "dhcp6_parser.cc"
    break;

  case 905: // ncr_format: "ncr-format" $@140 ":" "JSON"
#line 3136 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4851 "dhcp6_parser.cc"
    break;

  case 906: // $@141: %empty
#line 3144 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4863 "dhcp6_parser.cc"
    break;

  case 907: // config_control: "config-control" $@141 ":" "{" config_control_params "}"
#line 3150 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4873 "dhcp6_parser.cc"
    break;

  case 908: // $@142: %empty
#line 3156 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4883 "dhcp6_parser.cc"
    break;

  case 909: // sub_config_control: "{" $@142 config_control_params "}"
#line 3160 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4892 "dhcp6_parser.cc"
    break;

  case 912: // config_control_params: config_control_params ","
#line 3168 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4900 "dhcp6_parser.cc"
    break;

  case 915: // $@143: %empty
#line 3178 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4912 "dhcp6_parser.cc"
    break;

  case 916: // config_databases: "config-databases" $@143 ":" "[" database_list "]"
#line 3184 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4921 "dhcp6_parser.cc"
    break;

  case 917: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3189 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4931 "dhcp6_parser.cc"
    break;

  case 918: // $@144: %empty
#line 3197 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4943 "dhcp6_parser.cc"
    break;

  case 919: // loggers: "loggers" $@144 ":" "[" loggers_entries "]"
#line 3203 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4952 "dhcp6_parser.cc"
    break;

  case 922: // loggers_entries: loggers_entries ","
#line 3212 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4960 "dhcp6_parser.cc"
    break;

  case 923: // $@145: %empty
#line 3218 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4970 "dhcp6_parser.cc"
    break;

  case 924: // logger_entry: "{" $@145 logger_params "}"
#line 3222 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4978 "dhcp6_parser.cc"
    break;

  case 927: // logger_params: logger_params ","
#line 3228 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4986 "dhcp6_parser.cc"
    break;

  case 935: // debuglevel: "debuglevel" ":" "integer"
#line 3242 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4996 "dhcp6_parser.cc"
    break;

  case 936: // $@146: %empty
#line 3248 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5005 "dhcp6_parser.cc"
    break;

  case 937: // severity: "severity" $@146 ":" "constant string"
#line 3251 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 5015 "dhcp6_parser.cc"
    break;

  case 938: // $@147: %empty
#line 3257 "dhcp6_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 5027 "dhcp6_parser.cc"
    break;

  case 939: // output_options_list: "output-options" $@147 ":" "[" output_options_list_content "]"
#line 3263 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5036 "dhcp6_parser.cc"
    break;

  case 942: // output_options_list_content: output_options_list_content ","
#line 3270 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 5044 "dhcp6_parser.cc"
    break;

  case 943: // $@148: %empty
#line 3275 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 5054 "dhcp6_parser.cc"
    break;

  case 944: // output_entry: "{" $@148 output_params_list "}"
#line 3279 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 5062 "dhcp6_parser.cc"
    break;

  case 947: // output_params_list: output_params_list ","
#line 3285 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 5070 "dhcp6_parser.cc"
    break;

  case 953: // $@149: %empty
#line 3297 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5079 "dhcp6_parser.cc"
    break;

  case 954: // output: "output" $@149 ":" "constant string"
#line 3300 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5089 "dhcp6_parser.cc"
    break;

  case 955: // flush: "flush" ":" "boolean"
#line 3306 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5099 "dhcp6_parser.cc"
    break;

  case 956: // maxsize: "maxsize" ":" "integer"
#line 3312 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5109 "dhcp6_parser.cc"
    break;

  case 957: // maxver: "maxver" ":" "integer"
#line 3318 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5119 "dhcp6_parser.cc"
    break;

  case 958: // $@150: %empty
#line 3324 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5128 "dhcp6_parser.cc"
    break;

  case 959: // pattern: "pattern" $@150 ":" "constant string"
#line 3327 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5138 "dhcp6_parser.cc"
    break;

  case 960: // $@151: %empty
#line 3333 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5150 "dhcp6_parser.cc"
    break;

  case 961: // compatibility: "compatibility" $@151 ":" "{" compatibility_params "}"
#line 3339 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5159 "dhcp6_parser.cc"
    break;

  case 964: // compatibility_params: compatibility_params ","
#line 3346 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5167 "dhcp6_parser.cc"
    break;

  case 967: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3355 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5177 "dhcp6_parser.cc"
    break;


#line 5181 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1402;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     523, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402,    40,    66,    47,    74,    85,
     102,   115,   121,   129,   178,   180,   187,   226,   238,   276,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,    66,
    -164,   149,   199,   716,    43,  1418,   109,   577,   455,   167,
     117,   189,   -98,   473,   130, -1402,   283,   290,   307,   295,
     302,    89, -1402,    76, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402,   331,   341,   343,   345,   349,   355,   357,   366,   417,
     441,   451,   452,   463,   464, -1402,   465,   466,   467,   470,
     471, -1402, -1402, -1402,   474,   475,   476,   477, -1402, -1402,
   -1402,   478, -1402, -1402, -1402, -1402, -1402, -1402,   480,   482,
     483, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
     489, -1402, -1402, -1402, -1402, -1402, -1402, -1402,   491,   493,
     495, -1402, -1402,   503, -1402,    79, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402,   504,   506,   508,   509,
   -1402,    95, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402,   511,   514, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
     112, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402,   517, -1402, -1402, -1402, -1402, -1402,   113, -1402, -1402,
   -1402, -1402, -1402, -1402,   521, -1402,   522,   524, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402,   116, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402,   329,   336, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402,   364, -1402, -1402,   525,
   -1402, -1402, -1402,   527, -1402, -1402,   407,   531, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402,   536,   538,   539, -1402, -1402, -1402, -1402, -1402,   469,
     541, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402,   122, -1402, -1402, -1402,   542,
   -1402,   543, -1402,   544,   549, -1402, -1402, -1402, -1402, -1402,
     123, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402,   550,   143, -1402, -1402, -1402, -1402,    66,    66, -1402,
     296, -1402,   552, -1402, -1402,   553,   558,   560,   561,   564,
     565,   313,   338,   352,   361,   362,   365,   367,   373,   339,
     342,   374,   377,   379,   380,   568,   381,   385,   372,   384,
     386,   596,   618,   619,   391,   392,   395,   396,   625,   627,
     629,   403,   632,   633,   634,   638,   639,   640,   412,   416,
     418,   641,   644,   645,   647,   649,   651,   652,   653,   654,
     435,   664,   666,   667,   669,   670,   671,   672,   450,   453,
     454,   681,   685, -1402,   716, -1402,   686,   457,   458,   461,
     462,    43, -1402,   691,   692,   693,   694,   697,   479,   468,
     699,   706,   709,   710,  1418, -1402,   711,   485,   109, -1402,
     714,   488,   717,   490,   494,   577, -1402,   719,   721,   725,
     726,   728,   729,   730,   731, -1402,   455, -1402,   732,   753,
     528,   757,   758,   790,   562, -1402,   117,   791,   563,   567,
     575,   806, -1402,   189,   807,   809,   -94, -1402,   580,   811,
     584,   813,   586,   587,   816,   819,   473, -1402,   820,   593,
     130, -1402, -1402, -1402,   822,   828,   605,   831,   832,   833,
     834,   837, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402,   612, -1402, -1402, -1402,
   -1402, -1402,    20,   613,   614, -1402, -1402, -1402, -1402,   842,
     843,   844, -1402,   620,   621,   287,   845,   846,   623, -1402,
   -1402, -1402,   851,   852,   854,   853,   856,   857,   858,   859,
     860, -1402,   861,   862,   865,   864,   868,   646,   650, -1402,
   -1402, -1402,   867,   869, -1402,   875, -1402, -1402, -1402, -1402,
   -1402,   877,   878,   655,   656,   657, -1402, -1402,   875,   875,
     658,   883, -1402,   660, -1402, -1402,   661, -1402,   662, -1402,
   -1402, -1402,   875,   875,   875,   875,   663,   665,   668,   673,
   -1402,   674,   675, -1402,   676,   677,   678, -1402, -1402,   679,
   -1402, -1402, -1402,   875, -1402,   680,   846, -1402, -1402,   682,
   -1402,   683, -1402, -1402,   -30,   631, -1402,   879, -1402, -1402,
      66,   716, -1402,   130,    43,   146,   146,   888, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402,   891,   893,   895,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402,   896, -1402, -1402,
   -1402,   -89,    66,   -46,   279,   905,   908,   909,   171,    94,
     120,   196,   916,   124,   473, -1402, -1402,   917,  -159, -1402,
   -1402,   918,   919, -1402, -1402, -1402, -1402, -1402, -1402,   733,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402,   888, -1402,   151,   193,
     202, -1402, -1402, -1402, -1402,   881,   923,   924,   925,   926,
     928,   929,   930,   931,   932, -1402,   933,   934, -1402, -1402,
   -1402, -1402, -1402,   203, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402,   205, -1402,   935,
     936, -1402, -1402,   937,   939, -1402, -1402,   938,   942, -1402,
   -1402,   940,   945, -1402, -1402,   943,   947, -1402, -1402, -1402,
      62, -1402, -1402, -1402,   946, -1402, -1402, -1402,   340, -1402,
   -1402, -1402, -1402, -1402,   213, -1402, -1402, -1402, -1402,   433,
   -1402, -1402,   948,   950, -1402, -1402,   949,   953, -1402,   954,
     955,   956,   957,   958,   959,   236, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402,   960,   961,   962, -1402, -1402,
   -1402, -1402,   301, -1402, -1402, -1402, -1402, -1402, -1402,   963,
     964,   965, -1402,   318, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402,   966, -1402,   967, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402,   319, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402,   951,   969, -1402,   970, -1402,   971, -1402,
   -1402, -1402,   320, -1402, -1402, -1402, -1402, -1402,   321, -1402,
     447, -1402,   972, -1402,   333, -1402, -1402,   720, -1402,   973,
     974, -1402, -1402,   975,   977, -1402, -1402,   976,   979, -1402,
   -1402, -1402,   978,   982,   984,   985,   708,   739,   746,   749,
     759,   760,   762,   765,   773,   778,  1014,   785,   793,  1018,
    1019,  1028,  1029,   146, -1402, -1402,   146, -1402,   888,  1418,
   -1402,   891,   117, -1402,   893,   189, -1402,   895,   335, -1402,
     896,   -89, -1402, -1402,   -46, -1402,  1032,  1035,   279, -1402,
     207,   905, -1402,   455, -1402,   908,   -98, -1402,   909,   810,
     815,   817,   840,   848,   876,   171, -1402,  1041,  1047,   882,
     885,   898,    94, -1402,   818,   914,   921,   120, -1402,  1062,
    1065,  1082,   941,  1085,   907,  1086,   196, -1402,   196, -1402,
     916,   915,  1090,   944,  1105,   124, -1402, -1402,   291,   917,
   -1402,   927,  -159, -1402, -1402,  1104,  1147,   109, -1402,   918,
     577, -1402,   919, -1402, -1402,   952,   968,   980,   981, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,   212,
   -1402, -1402,   983,   986,   987,   988, -1402,   354, -1402,   360,
   -1402,  1149, -1402,  1150, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402,   368, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402,   989,   991, -1402, -1402, -1402,  1151,
    1158, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402,  1155,  1161, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402,  1157, -1402,   370, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402,   310,   994, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402,   299,   996,   997, -1402,  1159, -1402,  1162, -1402,
     408, -1402, -1402,   999, -1402,    66, -1402, -1402,  1164, -1402,
   -1402, -1402, -1402, -1402,   411, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402,  1000,   414, -1402,   415, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402,   335, -1402, -1402, -1402,  1165,  1166,
    1001,  1002, -1402,   207, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402,    61,  1167, -1402,
   -1402, -1402,  1168,  1005,  1171,   291, -1402, -1402, -1402, -1402,
   -1402,  1003,  1007, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402,   425, -1402, -1402, -1402, -1402, -1402, -1402,
    1172,  1174, -1402,  1175, -1402,  1008, -1402, -1402, -1402,  1177,
    1178,  1180,  1181,    61, -1402,    32, -1402,  1167,  1179, -1402,
    1015,  1009,  1010,  1183, -1402,   503, -1402, -1402, -1402, -1402,
   -1402,   426, -1402, -1402, -1402,   448, -1402, -1402, -1402, -1402,
   -1402,  1182,    32, -1402,  -107,  1179, -1402, -1402,  1173,  1187,
   -1402, -1402, -1402,  1188,  1189,  1190, -1402,   427, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402,    51, -1402,  1182,  1191,  1011,
    1012,  1016,  1192,  -107, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402,   434, -1402, -1402, -1402, -1402,  1020, -1402, -1402,
   -1402,  1022, -1402,  1193,  1194,    51, -1402, -1402, -1402,  1023,
    1024, -1402, -1402, -1402
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,   813,    33,    30,    31,    32,    37,
       3,    35,    36,    61,     5,    67,     7,   199,     9,   385,
      11,   597,    13,   627,    15,   661,    17,   512,    19,   521,
      21,   560,    23,   347,    25,   876,    27,   908,    29,    48,
      41,     0,     0,     0,     0,     0,     0,     0,   663,     0,
     523,   562,     0,     0,     0,    50,     0,    49,     0,     0,
      42,     0,    63,     0,    65,   141,   906,   197,   218,   220,
     222,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   187,     0,     0,     0,     0,
       0,   160,   167,   169,     0,     0,     0,     0,   376,   510,
     551,     0,   190,   192,   173,   454,   614,   616,     0,     0,
       0,   303,   322,   312,   292,   699,   652,   338,   359,   733,
       0,   324,   758,   760,   857,   874,   180,   182,     0,     0,
       0,   918,   960,     0,   140,     0,    69,    72,    73,    74,
      75,    76,    77,    78,    79,    80,   111,   112,   113,   114,
     115,    81,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   117,   118,   129,   130,   131,   107,   137,   138,
     139,   133,   134,   135,    84,    85,    86,    87,   104,    88,
      90,    89,   132,    94,    95,    82,   108,   109,   110,    83,
      92,    93,   102,   103,   105,    91,    96,    97,    98,    99,
     100,   101,   106,   116,   136,   212,     0,     0,     0,     0,
     211,     0,   201,   204,   205,   206,   207,   208,   209,   210,
     588,   618,   437,   439,   441,     0,     0,   445,   447,   443,
     696,   436,   390,   391,   392,   393,   394,   395,   396,   397,
     416,   417,   418,   419,   420,   423,   424,   425,   426,   427,
     428,   429,   430,   431,   432,   421,   422,   433,   434,   435,
       0,   387,   401,   402,   403,   406,   407,   408,   410,   411,
     412,   404,   405,   398,   399,   414,   415,   400,   409,   413,
     611,     0,   610,   605,   606,   607,   604,     0,   599,   602,
     603,   608,   609,   645,     0,   648,     0,     0,   644,   637,
     638,   639,   636,   635,   642,   643,     0,   629,   632,   633,
     640,   641,   634,   694,   680,   682,   684,   686,   688,   690,
     692,   679,   676,   677,   678,     0,   664,   665,   670,   671,
     672,   668,   673,   674,   675,   669,     0,   541,   266,     0,
     545,   543,   548,     0,   537,   538,     0,   524,   525,   528,
     540,   529,   530,   531,   547,   532,   533,   534,   535,   536,
     579,     0,     0,     0,   586,   577,   578,   581,   582,     0,
     563,   564,   567,   568,   569,   570,   571,   572,   573,   576,
     574,   575,   355,   357,   352,     0,   349,   353,   354,     0,
     893,     0,   896,     0,     0,   900,   904,   891,   889,   890,
       0,   878,   881,   882,   883,   884,   885,   886,   887,   888,
     915,     0,     0,   910,   913,   914,    47,    52,     0,    39,
      45,   814,     0,    66,    62,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    60,    71,    68,     0,     0,     0,     0,
       0,   203,   200,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   389,   386,     0,     0,   601,   598,
       0,     0,     0,     0,     0,   631,   628,     0,     0,     0,
       0,     0,     0,     0,     0,   662,   667,   513,     0,     0,
       0,     0,     0,     0,     0,   522,   527,     0,     0,     0,
       0,     0,   561,   566,     0,     0,   351,   348,     0,     0,
       0,     0,     0,     0,     0,     0,   880,   877,     0,     0,
     912,   909,    51,    43,     0,     0,     0,     0,     0,     0,
       0,     0,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,     0,   185,   186,   157,
     158,   159,     0,     0,     0,   171,   172,   179,   184,     0,
       0,     0,   189,     0,     0,     0,     0,     0,     0,   449,
     450,   451,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   757,     0,     0,     0,     0,     0,     0,     0,   194,
     195,   196,     0,     0,    70,     0,   214,   215,   216,   217,
     202,     0,     0,     0,     0,     0,   452,   453,     0,     0,
       0,     0,   388,     0,   613,   600,     0,   647,     0,   650,
     651,   630,     0,     0,     0,     0,     0,     0,     0,     0,
     666,     0,     0,   539,     0,     0,     0,   550,   526,     0,
     583,   584,   585,     0,   565,     0,     0,   350,   892,     0,
     895,     0,   898,   899,     0,     0,   879,     0,   917,   911,
       0,     0,   142,     0,     0,     0,     0,   224,   188,   162,
     163,   164,   165,   166,   161,   168,   170,   378,   514,   553,
     191,   193,   175,   176,   177,   178,   174,   456,    40,   615,
     617,     0,    48,     0,     0,     0,   654,   340,     0,     0,
       0,     0,   762,     0,     0,   181,   183,     0,     0,    53,
     213,   590,   620,   438,   440,   442,   446,   448,   444,     0,
     612,   646,   649,   695,   681,   683,   685,   687,   689,   691,
     693,   542,   267,   546,   544,   549,   580,   587,   356,   358,
     894,   897,   902,   903,   901,   905,   224,    44,     0,     0,
       0,   257,   259,   261,   263,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   276,     0,     0,   284,   286,
     288,   290,   256,     0,   231,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   248,   249,
     250,   251,   247,   252,   253,   254,   255,     0,   229,     0,
     225,   226,   383,     0,   379,   380,   519,     0,   515,   516,
     558,     0,   554,   555,   461,     0,   457,   458,   310,   311,
       0,   305,   308,   309,     0,   320,   321,   317,     0,   314,
     318,   319,   299,   301,     0,   294,   297,   298,   704,     0,
     701,   659,     0,   655,   656,   345,     0,   341,   342,     0,
       0,     0,     0,     0,     0,     0,   361,   364,   365,   366,
     367,   368,   369,   747,   753,     0,     0,     0,   746,   743,
     744,   745,     0,   735,   738,   741,   739,   740,   742,     0,
       0,     0,   334,     0,   326,   329,   330,   331,   332,   333,
     785,   790,   792,     0,   815,     0,   796,   784,   777,   778,
     779,   782,   783,     0,   769,   772,   773,   774,   775,   780,
     781,   776,   767,     0,   763,   764,     0,   869,     0,   872,
     865,   866,     0,   859,   862,   863,   864,   867,     0,   923,
       0,   920,     0,   966,     0,   962,   965,    55,   595,     0,
     591,   592,   625,     0,   621,   622,   698,     0,     0,    64,
     907,   198,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   233,   219,   221,     0,   223,   228,     0,
     377,   382,   523,   511,   518,   562,   552,   557,     0,   455,
     460,   307,   304,   323,   316,   313,     0,     0,   296,   293,
     706,   703,   700,   663,   653,   658,     0,   339,   344,     0,
       0,     0,     0,     0,     0,   363,   360,     0,     0,     0,
       0,     0,   737,   734,     0,     0,     0,   328,   325,     0,
       0,     0,     0,     0,     0,     0,   771,   759,     0,   761,
     766,     0,     0,     0,     0,   861,   858,   875,     0,   922,
     919,     0,   964,   961,    57,     0,    56,     0,   589,   594,
       0,   619,   624,   697,   916,     0,     0,     0,     0,   265,
     268,   269,   270,   271,   272,   273,   274,   283,   275,     0,
     281,   282,     0,     0,     0,     0,   232,     0,   227,     0,
     381,     0,   517,     0,   556,   509,   480,   481,   482,   484,
     485,   486,   470,   471,   489,   490,   491,   492,   493,   496,
     497,   498,   499,   500,   501,   502,   503,   504,   505,   494,
     495,   506,   507,   508,   466,   467,   468,   469,   477,   478,
     479,   474,   475,   476,   483,     0,   463,   472,   487,   488,
     473,   459,   306,   315,     0,     0,   295,   727,   729,     0,
       0,   725,   719,   720,   721,   722,   723,   724,   726,   716,
     717,   718,     0,   707,   708,   711,   712,   713,   714,   715,
     702,     0,   657,     0,   343,   370,   371,   372,   373,   374,
     375,   362,     0,     0,   752,   755,   756,   736,   335,   336,
     337,   327,     0,     0,     0,   794,     0,   795,     0,   770,
       0,   765,   868,     0,   871,     0,   860,   938,     0,   936,
     934,   928,   932,   933,     0,   925,   930,   931,   929,   921,
     967,   963,    54,    59,     0,   593,     0,   623,   258,   260,
     262,   264,   278,   279,   280,   277,   285,   287,   289,   291,
     230,   384,   520,   559,   465,   462,   300,   302,     0,     0,
       0,     0,   705,   710,   660,   346,   749,   750,   751,   748,
     754,   787,   788,   789,   786,   791,   793,     0,   798,   768,
     870,   873,     0,     0,     0,   927,   924,    58,   596,   626,
     464,     0,     0,   731,   732,   709,   827,   830,   832,   834,
     826,   825,   824,     0,   817,   820,   821,   822,   823,   803,
       0,   799,   800,     0,   935,     0,   926,   728,   730,     0,
       0,     0,     0,   819,   816,     0,   797,   802,     0,   937,
       0,     0,     0,     0,   818,    33,   809,   812,   808,   810,
     811,     0,   805,   801,   943,     0,   940,   829,   828,   831,
     833,   836,   807,   804,     0,   942,   939,   841,     0,   837,
     838,   806,   953,     0,     0,     0,   958,     0,   945,   948,
     949,   950,   951,   952,   941,     0,   835,   840,     0,     0,
       0,     0,     0,   947,   944,   853,   855,   852,   846,   848,
     850,   851,     0,   843,   847,   849,   839,     0,   955,   956,
     957,     0,   946,     0,     0,   845,   842,   954,   959,     0,
       0,   844,   854,   856
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402,   -16, -1402,  -609, -1402,
     445, -1402, -1402, -1402, -1402,   419, -1402,  -427, -1402, -1402,
   -1402,   -72, -1402, -1402, -1402, -1402, -1402, -1402, -1402,   459,
     684, -1402, -1402,   -59,   -56,   -53,   -42,   -39,    -9,   -11,
      -6,    -5,     5,     8,    11,    15, -1402,    33,    36,    37,
      38, -1402, -1402,    39, -1402,    52, -1402,    54,    57,    59,
   -1402, -1402,    60,    64, -1402,    65, -1402,    70, -1402, -1402,
   -1402, -1402, -1402,    72, -1402,    75, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402,   460,   702, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,   375, -1402,
     144, -1402,  -718,   150, -1402, -1402, -1401, -1402, -1397, -1402,
   -1402, -1402, -1402,   -67, -1402,  -752, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,  -774,
   -1402,  -764, -1402,  -760, -1402, -1402, -1402, -1402, -1402, -1402,
     127, -1402, -1402, -1402, -1402, -1402, -1402, -1402,   135,  -744,
   -1402, -1402, -1402, -1402,   133, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402,   103, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
     125, -1402, -1402, -1402,   156,   630, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402,   114, -1402, -1402, -1402, -1402, -1402, -1402,
   -1038, -1402, -1402, -1402,   154, -1402, -1402, -1402,   184,   703,
   -1402, -1402, -1037, -1402, -1036, -1402,    84, -1402,    86, -1402,
      92, -1402,    77,    80,    83, -1402, -1034, -1402, -1402, -1402,
   -1402,   176, -1402, -1402,   -75,  1184, -1402, -1402, -1402, -1402,
   -1402,   186, -1402, -1402, -1402,   194, -1402,   688, -1402,   -66,
   -1402, -1402, -1402, -1402, -1402,   -63, -1402, -1402, -1402, -1402,
   -1402,   -52, -1402, -1402, -1402,   191, -1402, -1402, -1402,   195,
   -1402,   687, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402,   128, -1402, -1402, -1402,
     136,   736, -1402, -1402,   -65,   -25, -1402,    19, -1402, -1402,
   -1402, -1402, -1402,   134, -1402, -1402, -1402,   119,   707, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402,   -55, -1402, -1402, -1402,
     201, -1402, -1402, -1402,   204, -1402,   712,   496, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1033, -1402, -1402, -1402, -1402, -1402,   198,
   -1402, -1402, -1402,   -44, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402,   188, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
     172, -1402,   175,   181, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402,  -101, -1402, -1402,
    -124, -1402, -1402, -1402, -1402,   -93, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402,  -146, -1402, -1402,
    -173, -1402, -1402, -1402, -1402, -1402, -1402, -1402,   179, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,   519,
     713, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,   569,   705,
   -1402, -1402, -1402, -1402, -1402, -1402,   177, -1402, -1402,   -48,
   -1402, -1402, -1402, -1402, -1402, -1402,  -115, -1402, -1402,  -142,
   -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402, -1402,
     182, -1402
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    85,    40,    41,    70,
     769,    89,    90,    42,    69,    86,    87,   790,  1017,  1135,
    1136,   852,    44,    72,    93,   452,    94,    46,    73,   165,
     166,   167,   455,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   481,   754,   186,   482,   187,   483,   188,   189,   190,
     494,   766,   191,   192,   516,   193,   517,   194,   195,   196,
     197,   475,   198,   199,   492,   200,   493,   201,   202,   203,
     204,   457,    48,    74,   241,   242,   243,   526,   244,   245,
     246,   247,   205,   458,   206,   459,   207,   460,   879,   880,
     881,  1056,   853,   854,   855,  1032,   856,  1033,   857,  1034,
     858,  1035,   859,   860,   569,   861,   862,   863,   864,   865,
     866,   867,   868,   869,  1046,  1315,   870,   871,   872,   873,
    1049,   874,  1050,   875,  1051,   876,  1052,   208,   504,   914,
     915,   916,  1076,   917,  1077,   209,   501,   900,   901,   902,
     903,   210,   503,   908,   909,   910,   911,   211,   502,   212,
     511,   963,   964,   965,   966,   967,   213,   507,   926,   927,
     928,  1086,    64,    82,   415,   416,   417,   584,   418,   585,
     214,   508,   935,   936,   937,   938,   939,   940,   941,   942,
     215,   488,   883,   884,   885,  1059,    50,    75,   290,   291,
     292,   535,   293,   536,   294,   537,   295,   542,   296,   540,
     297,   541,   216,   217,   218,   301,   302,   219,   495,   895,
     896,   897,  1068,  1215,  1216,   220,   489,    58,    79,   887,
     888,   889,  1062,    60,    80,   376,   377,   378,   379,   380,
     381,   382,   568,   383,   572,   384,   571,   385,   386,   573,
     387,   221,   490,   891,   892,   893,  1065,    62,    81,   399,
     400,   401,   402,   403,   577,   404,   405,   406,   407,   408,
     409,   581,   304,   533,  1019,  1020,  1021,  1137,    52,    76,
     317,   318,   319,   546,   320,   222,   496,   223,   497,   307,
     534,  1023,  1024,  1025,  1140,    54,    77,   336,   337,   338,
     550,   339,   340,   552,   341,   342,   224,   506,   922,   923,
     924,  1083,    56,    78,   355,   356,   357,   358,   558,   359,
     559,   360,   560,   361,   561,   362,   562,   363,   563,   364,
     564,   365,   557,   309,   543,  1027,   225,   505,   919,   920,
    1080,  1242,  1243,  1244,  1245,  1246,  1328,  1247,  1329,  1248,
    1249,   226,   509,   952,   953,   954,  1097,  1339,   955,   956,
    1098,   957,   958,   227,   228,   512,   229,   513,   993,   994,
     995,  1118,   983,   984,   985,  1109,  1344,   986,  1110,   987,
    1111,   988,   989,   990,  1115,  1380,  1381,  1382,  1395,  1411,
    1412,    71,   991,  1113,  1373,  1374,  1375,  1389,  1418,  1376,
    1390,  1377,  1391,  1378,  1392,  1428,  1429,  1430,  1445,  1462,
    1463,  1464,  1473,  1465,  1474,   230,   514,  1002,  1003,  1004,
    1005,  1122,  1006,  1007,  1124,   231,   515,    66,    83,   430,
     431,   432,   433,   589,   434,   435,   591,   436,   437,   438,
     594,   824,   439,   595,   232,   456,    68,    84,   442,   443,
     444,   598,   445,   233,   521,  1010,  1011,  1128,  1294,  1295,
    1296,  1297,  1354,  1298,  1352,  1415,  1416,  1424,  1437,  1438,
    1439,  1448,  1440,  1441,  1442,  1443,  1452,   234,   522,  1014,
    1015,  1016
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
      39,   164,   240,   261,   312,   328,   351,   978,   374,   395,
     414,   427,   333,   375,   396,   397,   262,   979,   398,   263,
     308,   980,   264,   303,   316,   332,   352,   949,   877,   907,
    1205,  1206,  1207,   265,  1214,  1220,   266,    31,   768,    32,
      30,    33,   412,   413,  1458,   898,   412,   413,  1459,   248,
     305,   321,   334,   353,    43,   388,   410,  1012,   428,   235,
     236,   237,   238,   239,   268,  1071,   267,    88,  1072,   269,
     270,    31,   163,    32,  1458,    33,   832,   833,  1459,   453,
     271,    45,   524,   272,   454,  1366,   273,   525,   898,   905,
     274,   906,    47,   249,   306,   322,   335,   354,   531,   389,
     411,  1432,   429,   532,  1433,  1434,  1435,  1436,   275,    49,
     368,   276,   277,   278,   279,   544,   548,   768,   943,   555,
     545,   549,    51,   836,   556,   586,   596,   280,    53,   281,
     587,   597,   282,   163,   283,   284,    55,   136,   137,   285,
     286,   367,   899,   440,   441,   287,   600,   288,   136,   137,
     289,   601,   298,    91,   524,   299,   136,   137,   300,  1029,
     313,   329,   314,   330,   822,   823,   136,   137,   315,   331,
     831,   832,   833,   834,   835,   836,   837,   838,   839,   840,
     841,   842,   843,   844,   845,    57,   130,    59,   846,   847,
     848,   849,   850,   851,    61,   368,   600,   369,   370,   136,
     137,  1030,   371,   372,   373,   531,  1053,   310,  1053,    92,
    1031,  1054,    34,  1055,   136,   137,  1078,   749,   750,   751,
     752,  1079,   136,   137,   368,   136,   137,  1455,  1456,   136,
     137,   257,   258,    63,  1367,  1368,  1369,   259,   311,  1095,
     848,   849,   850,   129,  1096,    65,    34,   944,   945,   946,
     947,  1312,  1313,  1314,   753,   101,   102,   103,   104,   105,
     106,   796,   797,  1405,    36,    37,    38,   368,   390,   369,
     370,   391,   392,   393,   163,   803,   804,   805,   806,   959,
     960,   961,   163,    67,   130,   368,  1205,  1206,  1207,   446,
    1214,  1220,   163,   447,   136,   137,   817,    35,    36,    37,
      38,   136,   137,   449,  1102,   450,   996,   997,   998,  1103,
     394,   448,   136,   137,   929,   930,   931,   932,   933,   934,
     451,  1107,  1116,  1125,   596,   163,  1108,  1117,  1126,  1127,
     907,  1227,  1228,  1229,  1230,   461,  1132,   565,  1167,   566,
     163,  1133,   978,  1074,   978,   462,  1075,   463,   163,   464,
     949,   163,   979,   465,   979,   999,   980,  1053,   980,   466,
     970,   467,  1320,   544,   971,   972,   973,   974,  1321,   368,
     468,  1324,   567,   586,   975,   976,  1325,   163,  1335,   762,
     763,   764,   765,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   136,   137,   912,   913,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,  1116,   130,   368,  1355,   575,  1349,   548,   555,  1356,
     163,   469,  1358,  1359,   132,   133,   134,   163,  1393,  1422,
    1453,   602,   603,  1394,  1423,  1454,  1081,  1475,   163,  1082,
     136,   137,  1476,   253,   254,   470,   256,   138,   139,   140,
    1129,  1425,   164,  1130,  1426,   471,   472,   257,   258,   240,
    1336,  1337,  1338,   259,  1341,  1342,  1343,   473,   474,   476,
     477,   478,   261,   260,   479,   480,   312,   582,   484,   485,
     486,   487,   491,   328,   498,   262,   499,   500,   263,   308,
     333,   264,   303,   510,   351,   518,   316,   519,  1287,   520,
    1288,  1289,   265,   332,   374,   266,   248,   523,   527,   375,
     528,   395,   529,   530,   352,   538,   396,   397,   539,   305,
     398,   547,   163,   321,   427,   551,   553,   604,   554,   570,
     334,   574,   130,   268,   576,   267,   156,   157,   269,   270,
     578,   353,   579,   580,   583,   612,   588,   590,   592,   271,
     249,   388,   272,   593,   599,   273,   605,   606,   410,   274,
     136,   137,   607,   306,   608,   609,   163,   322,   610,   611,
     613,   428,   626,   620,   335,   621,   343,   275,   136,   137,
     276,   277,   278,   279,   614,   354,   344,   345,   346,   347,
     348,   349,   350,   615,   616,   389,   280,   617,   281,   618,
     632,   282,   411,   283,   284,   619,   629,   622,   285,   286,
     623,   624,   625,   627,   287,   429,   288,   628,   630,   289,
     631,   298,   633,   634,   299,   635,   636,   300,   637,   639,
     638,   640,   313,   641,   314,   642,   643,   644,   645,   329,
     315,   330,   646,   647,   648,   652,   649,   331,   653,   654,
     650,   655,   651,   656,   130,   657,   658,   659,   660,   419,
     420,   421,   422,   423,   424,   425,   426,   661,   662,   164,
     663,   664,   240,   665,   666,   667,   668,   323,   324,   325,
     326,   327,   136,   137,   669,   672,   163,   670,   671,   673,
     675,   676,   677,   678,   679,   681,   682,   683,   684,   257,
     258,   685,   687,   688,   163,   259,   311,   948,   962,   977,
     689,   686,   427,   690,   691,   693,  1013,   694,   696,   248,
     697,   698,   699,   702,   827,   703,   700,    95,    96,   704,
     705,    97,   706,   707,   708,   709,   711,    98,    99,   100,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,   950,   968,   981,   712,  1000,   428,
     713,   714,   715,   249,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   716,   719,   717,   720,   951,   969,
     982,   721,  1001,   429,   131,   132,   133,   134,   163,   722,
     723,   725,   135,   726,   728,   729,   730,   731,   732,   733,
     734,   136,   137,   735,   737,   738,   740,   825,   138,   139,
     140,   141,   142,   143,   144,   741,   742,   145,   743,   744,
     745,   746,   747,   748,   755,   756,   146,   757,   758,   759,
     767,   760,   761,    32,   770,   147,   771,   772,   148,   773,
     774,   775,   776,   777,   344,   149,   778,   779,   780,   781,
     782,   783,   787,   150,   151,   784,   788,   785,   152,   153,
     789,   786,   791,   792,   826,  1036,   793,   794,   795,   798,
     799,   800,   801,   802,   807,   878,   808,   154,   882,   809,
     886,   155,   890,   894,   810,   811,   812,   813,   814,   815,
     816,   818,   918,   820,   821,   921,   925,   156,   157,   158,
     159,   160,   161,   992,  1009,  1018,  1022,  1037,  1038,  1039,
    1040,   162,  1041,  1042,  1043,  1044,  1045,  1047,  1048,  1058,
    1149,  1057,  1061,  1060,  1063,  1064,  1066,   163,  1067,  1069,
    1070,  1134,  1073,  1085,  1084,  1087,  1088,  1119,  1089,  1090,
    1091,  1092,  1093,  1094,  1099,  1100,  1101,  1104,  1105,  1106,
    1112,  1114,  1120,  1150,  1121,  1123,  1131,  1139,  1151,  1138,
    1142,  1141,  1145,  1152,  1143,  1144,  1146,   261,  1147,  1148,
     374,  1153,  1154,   395,  1155,   375,  1175,  1156,   396,   397,
     262,  1204,   398,   263,   308,  1157,   264,   303,  1231,  1176,
    1158,   351,  1177,  1238,   414,  1178,  1217,   265,  1159,  1160,
     266,  1232,  1162,  1163,  1233,  1161,  1179,  1234,  1239,  1180,
     948,   352,  1164,  1165,   305,   962,  1224,   388,  1235,  1225,
     410,  1236,  1255,  1218,   977,  1262,   977,  1256,   268,  1257,
     267,  1263,  1268,   269,   270,  1240,  1290,  1182,   353,  1181,
    1013,  1291,  1183,  1184,   271,   312,  1272,   272,   328,  1273,
     273,  1237,  1258,  1185,   274,   333,  1186,   950,   306,  1187,
    1259,   389,   968,  1188,   411,   316,  1274,  1219,   332,  1276,
    1278,   981,   275,   981,  1283,   276,   277,   278,   279,  1241,
    1000,  1189,   354,  1292,  1190,  1191,  1192,  1193,  1260,  1285,
    1302,   280,   321,   281,  1264,   334,   282,  1265,   283,   284,
    1194,   951,  1195,   285,   286,  1196,   969,  1197,  1198,   287,
    1266,   288,  1199,  1200,   289,   982,   298,   982,  1201,   299,
    1202,  1277,   300,  1203,  1001,  1211,  1269,  1293,  1212,  1282,
    1303,  1213,  1208,  1270,  1209,  1330,   322,  1322,  1323,   335,
    1210,  1300,  1331,  1332,  1333,  1334,  1347,  1348,  1353,  1361,
    1362,   819,  1383,  1275,  1379,  1385,  1284,  1397,  1396,  1446,
    1398,  1400,  1401,  1308,  1402,  1403,  1414,  1417,  1421,  1427,
    1447,   904,  1449,  1450,  1451,  1467,  1471,  1479,  1480,  1309,
     828,  1028,  1168,  1166,   830,  1226,  1222,  1223,   674,  1261,
    1271,  1310,  1311,  1254,  1316,  1170,   727,  1317,  1318,  1319,
    1326,   313,  1327,   314,   329,  1340,   330,  1345,  1346,   315,
    1350,  1357,   331,   680,  1387,  1363,  1364,  1384,  1388,  1399,
    1419,  1420,  1253,  1169,  1469,  1468,  1221,   692,  1470,  1360,
    1172,  1477,  1175,  1478,  1482,  1483,  1171,  1204,  1174,  1306,
    1173,  1231,   701,   366,   718,  1176,  1238,  1305,  1177,  1351,
     724,  1178,  1217,  1304,  1232,  1370,  1307,  1233,   710,  1250,
    1234,  1239,  1179,  1290,   695,  1180,  1252,  1251,  1291,  1365,
    1267,  1235,  1281,  1280,  1236,  1026,  1413,  1279,  1431,  1218,
    1404,  1466,  1481,  1008,  1286,   739,  1299,  1386,  1240,   736,
    1444,  1472,   829,  1182,  1301,  1181,     0,     0,  1183,  1184,
       0,  1370,  1371,  1407,  1237,     0,     0,     0,  1408,  1185,
    1292,     0,  1186,     0,     0,  1187,     0,     0,     0,  1188,
       0,     0,     0,  1219,     0,     0,     0,     0,     0,     0,
    1407,     0,  1241,     0,     0,  1408,     0,  1189,     0,     0,
    1190,  1191,  1192,  1193,     0,     0,  1372,     0,  1371,     0,
    1409,     0,     0,  1457,  1293,     0,  1194,     0,  1195,  1406,
       0,  1196,     0,  1197,  1198,     0,     0,     0,  1199,  1200,
       0,     0,     0,     0,  1201,     0,  1202,  1409,     0,  1203,
       0,  1211,     0,  1457,  1212,     0,  1406,  1213,  1208,     0,
    1209,     0,  1372,     0,  1410,     0,  1210,     0,     0,     0,
    1460,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1410,     0,     0,     0,     0,     0,     0,     0,     0,
    1460,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1461,     0,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,     0,
       0,     0,     0,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,     0,  1461,   130,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   132,   133,   134,
       0,     0,     0,     0,     0,   250,     0,   251,     0,     0,
       0,     0,     0,   136,   137,   252,   253,   254,   255,   256,
     138,   139,   140,     0,     0,     0,     0,     0,     0,     0,
     257,   258,     0,     0,     0,     0,   259,     0,   146,     0,
       0,     0,     0,     0,     0,     0,   260,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   156,
     157,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   163
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      16,    73,    74,    75,    76,    77,    78,   781,    80,    81,
      82,    83,    77,    80,    81,    81,    75,   781,    81,    75,
      75,   781,    75,    75,    76,    77,    78,   779,   746,   773,
    1068,  1068,  1068,    75,  1068,  1068,    75,     5,   647,     7,
       0,     9,   140,   141,  1445,   134,   140,   141,  1445,    74,
      75,    76,    77,    78,     7,    80,    81,   216,    83,    16,
      17,    18,    19,    20,    75,     3,    75,   231,     6,    75,
      75,     5,   231,     7,  1475,     9,    25,    26,  1475,     3,
      75,     7,     3,    75,     8,    24,    75,     8,   134,   135,
      75,   137,     7,    74,    75,    76,    77,    78,     3,    80,
      81,   208,    83,     8,   211,   212,   213,   214,    75,     7,
      78,    75,    75,    75,    75,     3,     3,   726,    24,     3,
       8,     8,     7,    29,     8,     3,     3,    75,     7,    75,
       8,     8,    75,   231,    75,    75,     7,   105,   106,    75,
      75,    24,   231,    13,    14,    75,     3,    75,   105,   106,
      75,     8,    75,     4,     3,    75,   105,   106,    75,     8,
      76,    77,    76,    77,   194,   195,   105,   106,    76,    77,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,     7,    77,     7,    42,    43,
      44,    45,    46,    47,     7,    78,     3,    80,    81,   105,
     106,     8,    85,    86,    87,     3,     3,    98,     3,    10,
       8,     8,   180,     8,   105,   106,     3,   197,   198,   199,
     200,     8,   105,   106,    78,   105,   106,   176,   177,   105,
     106,   122,   123,     7,   173,   174,   175,   128,   129,     3,
      44,    45,    46,    76,     8,     7,   180,   153,   154,   155,
     156,    39,    40,    41,   234,    48,    49,    50,    51,    52,
      53,   688,   689,   231,   232,   233,   234,    78,    79,    80,
      81,    82,    83,    84,   231,   702,   703,   704,   705,   159,
     160,   161,   231,     7,    77,    78,  1324,  1324,  1324,     6,
    1324,  1324,   231,     3,   105,   106,   723,   231,   232,   233,
     234,   105,   106,     8,     3,     3,   182,   183,   184,     8,
     121,     4,   105,   106,   143,   144,   145,   146,   147,   148,
     231,     3,     3,     3,     3,   231,     8,     8,     8,     8,
    1074,   124,   125,   126,   127,     4,     3,     8,  1056,     3,
     231,     8,  1116,     3,  1118,     4,     6,     4,   231,     4,
    1102,   231,  1116,     4,  1118,   231,  1116,     3,  1118,     4,
     164,     4,     8,     3,   168,   169,   170,   171,     8,    78,
       4,     3,     8,     3,   178,   179,     8,   231,     8,    92,
      93,    94,    95,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,   105,   106,   119,   120,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,     3,    77,    78,     3,     8,     8,     3,     3,     8,
     231,     4,     8,     8,    89,    90,    91,   231,     3,     3,
       3,   447,   448,     8,     8,     8,     3,     3,   231,     6,
     105,   106,     8,   108,   109,     4,   111,   112,   113,   114,
       3,     3,   524,     6,     6,     4,     4,   122,   123,   531,
     150,   151,   152,   128,   165,   166,   167,     4,     4,     4,
       4,     4,   544,   138,     4,     4,   548,     8,     4,     4,
       4,     4,     4,   555,     4,   544,     4,     4,   544,   544,
     555,   544,   544,     4,   566,     4,   548,     4,   207,     4,
     209,   210,   544,   555,   576,   544,   531,     4,     4,   576,
       4,   583,     4,     4,   566,     4,   583,   583,     4,   544,
     583,     4,   231,   548,   596,     4,     4,   231,     4,     4,
     555,     4,    77,   544,     3,   544,   201,   202,   544,   544,
       4,   566,     4,     4,     3,   232,     4,     4,     4,   544,
     531,   576,   544,     4,     4,   544,     4,     4,   583,   544,
     105,   106,     4,   544,     4,     4,   231,   548,     4,     4,
     232,   596,     4,   234,   555,   233,   121,   544,   105,   106,
     544,   544,   544,   544,   232,   566,   131,   132,   133,   134,
     135,   136,   137,   232,   232,   576,   544,   232,   544,   232,
       4,   544,   583,   544,   544,   232,   234,   233,   544,   544,
     233,   232,   232,   232,   544,   596,   544,   232,   234,   544,
     234,   544,     4,     4,   544,   234,   234,   544,   233,     4,
     234,     4,   548,     4,   548,   232,     4,     4,     4,   555,
     548,   555,     4,     4,     4,     4,   234,   555,     4,     4,
     234,     4,   234,     4,    77,     4,     4,     4,     4,   186,
     187,   188,   189,   190,   191,   192,   193,   232,     4,   741,
       4,     4,   744,     4,     4,     4,     4,   100,   101,   102,
     103,   104,   105,   106,   234,     4,   231,   234,   234,     4,
       4,   234,   234,   232,   232,     4,     4,     4,     4,   122,
     123,     4,   234,     4,   231,   128,   129,   779,   780,   781,
       4,   232,   784,     4,     4,     4,   788,   232,     4,   744,
     232,     4,   232,     4,   740,     4,   232,    11,    12,     4,
       4,    15,     4,     4,     4,     4,     4,    21,    22,    23,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   779,   780,   781,     4,   783,   784,
     232,     4,     4,   744,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,     4,     4,   234,   234,   779,   780,
     781,   234,   783,   784,    88,    89,    90,    91,   231,   234,
       4,     4,    96,     4,   234,     4,   232,     4,   232,   232,
       4,   105,   106,     4,     4,   232,     4,   196,   112,   113,
     114,   115,   116,   117,   118,     7,   231,   121,     7,     7,
       7,     7,     5,   231,   231,   231,   130,     5,     5,     5,
       5,   231,   231,     7,   231,   139,     5,     5,   142,     5,
       7,     5,     5,     5,   131,   149,     7,     7,     7,     7,
       5,     7,     5,   157,   158,     7,     7,   231,   162,   163,
       5,   231,     5,     5,     5,     4,   231,   231,   231,   231,
       7,   231,   231,   231,   231,     7,   231,   181,     7,   231,
       7,   185,     7,     7,   231,   231,   231,   231,   231,   231,
     231,   231,     7,   231,   231,     7,     7,   201,   202,   203,
     204,   205,   206,     7,     7,     7,     7,     4,     4,     4,
       4,   215,     4,     4,     4,     4,     4,     4,     4,     3,
     232,     6,     3,     6,     6,     3,     6,   231,     3,     6,
       3,   231,     6,     3,     6,     6,     3,     6,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     3,   234,     4,     4,     4,     3,   232,     6,
       3,     6,     4,   234,     8,     6,     4,  1059,     4,     4,
    1062,   232,   232,  1065,   232,  1062,  1068,   232,  1065,  1065,
    1059,  1068,  1065,  1059,  1059,   232,  1059,  1059,  1080,  1068,
     232,  1083,  1068,  1080,  1086,  1068,  1068,  1059,     4,   234,
    1059,  1080,     4,     4,  1080,   232,  1068,  1080,  1080,  1068,
    1102,  1083,     4,     4,  1059,  1107,     4,  1062,  1080,     4,
    1065,  1080,   232,  1068,  1116,     4,  1118,   232,  1059,   232,
    1059,     4,   234,  1059,  1059,  1080,  1128,  1068,  1083,  1068,
    1132,  1128,  1068,  1068,  1059,  1137,     4,  1059,  1140,     4,
    1059,  1080,   232,  1068,  1059,  1140,  1068,  1102,  1059,  1068,
     232,  1062,  1107,  1068,  1065,  1137,     4,  1068,  1140,     4,
       4,  1116,  1059,  1118,     4,  1059,  1059,  1059,  1059,  1080,
    1125,  1068,  1083,  1128,  1068,  1068,  1068,  1068,   232,     4,
       6,  1059,  1137,  1059,   232,  1140,  1059,   232,  1059,  1059,
    1068,  1102,  1068,  1059,  1059,  1068,  1107,  1068,  1068,  1059,
     232,  1059,  1068,  1068,  1059,  1116,  1059,  1118,  1068,  1059,
    1068,   234,  1059,  1068,  1125,  1068,   232,  1128,  1068,   234,
       3,  1068,  1068,   232,  1068,     4,  1137,     8,     8,  1140,
    1068,   234,     4,     8,     3,     8,     7,     5,     4,     4,
       4,   726,     4,   232,     7,     4,   232,     3,     6,     6,
       5,     4,     4,   231,     4,     4,     7,   172,     5,     7,
       3,   772,     4,     4,     4,     4,     4,     4,     4,   231,
     741,   826,  1058,  1053,   744,  1078,  1071,  1074,   524,  1095,
    1107,   231,   231,  1088,   231,  1061,   586,   231,   231,   231,
     231,  1137,   231,  1137,  1140,   231,  1140,   231,   231,  1137,
     231,   231,  1140,   531,   231,   234,   234,   232,   231,   231,
     231,   231,  1086,  1059,   232,   234,  1070,   544,   232,  1324,
    1064,   231,  1324,   231,   231,   231,  1062,  1324,  1067,  1140,
    1065,  1333,   555,    79,   576,  1324,  1333,  1139,  1324,  1285,
     583,  1324,  1324,  1137,  1333,  1347,  1142,  1333,   566,  1081,
    1333,  1333,  1324,  1355,   548,  1324,  1085,  1083,  1355,  1333,
    1102,  1333,  1120,  1118,  1333,   799,  1397,  1116,  1422,  1324,
    1393,  1447,  1475,   784,  1125,   600,  1129,  1355,  1333,   596,
    1425,  1453,   743,  1324,  1132,  1324,    -1,    -1,  1324,  1324,
      -1,  1393,  1347,  1395,  1333,    -1,    -1,    -1,  1395,  1324,
    1355,    -1,  1324,    -1,    -1,  1324,    -1,    -1,    -1,  1324,
      -1,    -1,    -1,  1324,    -1,    -1,    -1,    -1,    -1,    -1,
    1422,    -1,  1333,    -1,    -1,  1422,    -1,  1324,    -1,    -1,
    1324,  1324,  1324,  1324,    -1,    -1,  1347,    -1,  1393,    -1,
    1395,    -1,    -1,  1445,  1355,    -1,  1324,    -1,  1324,  1395,
      -1,  1324,    -1,  1324,  1324,    -1,    -1,    -1,  1324,  1324,
      -1,    -1,    -1,    -1,  1324,    -1,  1324,  1422,    -1,  1324,
      -1,  1324,    -1,  1475,  1324,    -1,  1422,  1324,  1324,    -1,
    1324,    -1,  1393,    -1,  1395,    -1,  1324,    -1,    -1,    -1,
    1445,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1422,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1475,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1445,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    -1,  1475,    77,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    91,
      -1,    -1,    -1,    -1,    -1,    97,    -1,    99,    -1,    -1,
      -1,    -1,    -1,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     122,   123,    -1,    -1,    -1,    -1,   128,    -1,   130,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   138,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   201,
     202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   231
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
       0,     5,     7,     9,   180,   231,   232,   233,   234,   251,
     252,   253,   258,     7,   267,     7,   272,     7,   327,     7,
     441,     7,   523,     7,   540,     7,   557,     7,   472,     7,
     478,     7,   502,     7,   417,     7,   672,     7,   691,   259,
     254,   636,   268,   273,   328,   442,   524,   541,   558,   473,
     479,   503,   418,   673,   692,   251,   260,   261,   231,   256,
     257,     4,    10,   269,   271,    11,    12,    15,    21,    22,
      23,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    88,    89,    90,    91,    96,   105,   106,   112,   113,
     114,   115,   116,   117,   118,   121,   130,   139,   142,   149,
     157,   158,   162,   163,   181,   185,   201,   202,   203,   204,
     205,   206,   215,   231,   266,   274,   275,   276,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   298,   300,   302,   303,
     304,   307,   308,   310,   312,   313,   314,   315,   317,   318,
     320,   322,   323,   324,   325,   337,   339,   341,   382,   390,
     396,   402,   404,   411,   425,   435,   457,   458,   459,   462,
     470,   496,   530,   532,   551,   581,   596,   608,   609,   611,
     660,   670,   689,   698,   722,    16,    17,    18,    19,    20,
     266,   329,   330,   331,   333,   334,   335,   336,   530,   532,
      97,    99,   107,   108,   109,   110,   111,   122,   123,   128,
     138,   266,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   292,   293,   294,   295,   298,
     300,   302,   303,   304,   307,   308,   310,   312,   318,   320,
     443,   444,   445,   447,   449,   451,   453,   455,   457,   458,
     459,   460,   461,   496,   517,   530,   532,   534,   551,   578,
      98,   129,   266,   451,   453,   455,   496,   525,   526,   527,
     529,   530,   532,   100,   101,   102,   103,   104,   266,   451,
     453,   455,   496,   529,   530,   532,   542,   543,   544,   546,
     547,   549,   550,   121,   131,   132,   133,   134,   135,   136,
     137,   266,   496,   530,   532,   559,   560,   561,   562,   564,
     566,   568,   570,   572,   574,   576,   470,    24,    78,    80,
      81,    85,    86,    87,   266,   358,   480,   481,   482,   483,
     484,   485,   486,   488,   490,   492,   493,   495,   530,   532,
      79,    82,    83,    84,   121,   266,   358,   484,   490,   504,
     505,   506,   507,   508,   510,   511,   512,   513,   514,   515,
     530,   532,   140,   141,   266,   419,   420,   421,   423,   186,
     187,   188,   189,   190,   191,   192,   193,   266,   530,   532,
     674,   675,   676,   677,   679,   680,   682,   683,   684,   687,
      13,    14,   693,   694,   695,   697,     6,     3,     4,     8,
       3,   231,   270,     3,     8,   277,   690,   326,   338,   340,
     342,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   316,     4,     4,     4,     4,
       4,   296,   299,   301,     4,     4,     4,     4,   436,   471,
     497,     4,   319,   321,   305,   463,   531,   533,     4,     4,
       4,   391,   403,   397,   383,   582,   552,   412,   426,   597,
       4,   405,   610,   612,   661,   671,   309,   311,     4,     4,
       4,   699,   723,     4,     3,     8,   332,     4,     4,     4,
       4,     3,     8,   518,   535,   446,   448,   450,     4,     4,
     454,   456,   452,   579,     3,     8,   528,     4,     3,     8,
     545,     4,   548,     4,     4,     3,     8,   577,   563,   565,
     567,   569,   571,   573,   575,     8,     3,     8,   487,   359,
       4,   491,   489,   494,     4,     8,     3,   509,     4,     4,
       4,   516,     8,     3,   422,   424,     3,     8,     4,   678,
       4,   681,     4,     4,   685,   688,     3,     8,   696,     4,
       3,     8,   251,   251,   231,     4,     4,     4,     4,     4,
       4,     4,   232,   232,   232,   232,   232,   232,   232,   232,
     234,   233,   233,   233,   232,   232,     4,   232,   232,   234,
     234,   234,     4,     4,     4,   234,   234,   233,   234,     4,
       4,     4,   232,     4,     4,     4,     4,     4,     4,   234,
     234,   234,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   232,     4,     4,     4,     4,     4,     4,     4,   234,
     234,   234,     4,     4,   275,     4,   234,   234,   232,   232,
     330,     4,     4,     4,     4,     4,   232,   234,     4,     4,
       4,     4,   444,     4,   232,   526,     4,   232,     4,   232,
     232,   543,     4,     4,     4,     4,     4,     4,     4,     4,
     561,     4,     4,   232,     4,     4,     4,   234,   482,     4,
     234,   234,   234,     4,   506,     4,     4,   420,   234,     4,
     232,     4,   232,   232,     4,     4,   675,     4,   232,   694,
       4,     7,   231,     7,     7,     7,     7,     5,   231,   197,
     198,   199,   200,   234,   297,   231,   231,     5,     5,     5,
     231,   231,    92,    93,    94,    95,   306,     5,   253,   255,
     231,     5,     5,     5,     7,     5,     5,     5,     7,     7,
       7,     7,     5,     7,     7,   231,   231,     5,     7,     5,
     262,     5,     5,   231,   231,   231,   262,   262,   231,     7,
     231,   231,   231,   262,   262,   262,   262,   231,   231,   231,
     231,   231,   231,   231,   231,   231,   231,   262,   231,   255,
     231,   231,   194,   195,   686,   196,     5,   251,   274,   693,
     329,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    42,    43,    44,    45,
      46,    47,   266,   347,   348,   349,   351,   353,   355,   357,
     358,   360,   361,   362,   363,   364,   365,   366,   367,   368,
     371,   372,   373,   374,   376,   378,   380,   347,     7,   343,
     344,   345,     7,   437,   438,   439,     7,   474,   475,   476,
       7,   498,   499,   500,     7,   464,   465,   466,   134,   231,
     392,   393,   394,   395,   260,   135,   137,   394,   398,   399,
     400,   401,   119,   120,   384,   385,   386,   388,     7,   583,
     584,     7,   553,   554,   555,     7,   413,   414,   415,   143,
     144,   145,   146,   147,   148,   427,   428,   429,   430,   431,
     432,   433,   434,    24,   153,   154,   155,   156,   266,   360,
     530,   532,   598,   599,   600,   603,   604,   606,   607,   159,
     160,   161,   266,   406,   407,   408,   409,   410,   530,   532,
     164,   168,   169,   170,   171,   178,   179,   266,   374,   376,
     378,   530,   532,   617,   618,   619,   622,   624,   626,   627,
     628,   637,     7,   613,   614,   615,   182,   183,   184,   231,
     530,   532,   662,   663,   664,   665,   667,   668,   674,     7,
     700,   701,   216,   266,   724,   725,   726,   263,     7,   519,
     520,   521,     7,   536,   537,   538,   562,   580,   343,     8,
       8,     8,   350,   352,   354,   356,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   369,     4,     4,   375,
     377,   379,   381,     3,     8,     8,   346,     6,     3,   440,
       6,     3,   477,     6,     3,   501,     6,     3,   467,     6,
       3,     3,     6,     6,     3,     6,   387,   389,     3,     8,
     585,     3,     6,   556,     6,     3,   416,     6,     3,     4,
       4,     4,     4,     4,     4,     3,     8,   601,   605,     4,
       4,     4,     3,     8,     4,     4,     4,     3,     8,   620,
     623,   625,     4,   638,     4,   629,     3,     8,   616,     6,
       3,     4,   666,     4,   669,     3,     8,     8,   702,     3,
       6,     4,     3,     8,   231,   264,   265,   522,     6,     3,
     539,     6,     3,     8,     6,     4,     4,     4,     4,   232,
     234,   232,   234,   232,   232,   232,   232,   232,   232,     4,
     234,   232,     4,     4,     4,     4,   348,   347,   345,   443,
     439,   480,   476,   504,   500,   266,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   292,
     293,   294,   295,   298,   300,   302,   303,   304,   307,   308,
     310,   312,   318,   320,   358,   435,   447,   449,   451,   453,
     455,   457,   458,   459,   461,   468,   469,   496,   530,   532,
     578,   466,   393,   399,     4,     4,   385,   124,   125,   126,
     127,   266,   278,   279,   280,   281,   282,   283,   358,   496,
     530,   532,   586,   587,   588,   589,   590,   592,   594,   595,
     584,   559,   555,   419,   415,   232,   232,   232,   232,   232,
     232,   428,     4,     4,   232,   232,   232,   599,   234,   232,
     232,   407,     4,     4,     4,   232,     4,   234,     4,   618,
     617,   615,   234,     4,   232,     4,   663,   207,   209,   210,
     266,   358,   530,   532,   703,   704,   705,   706,   708,   701,
     234,   725,     6,     3,   525,   521,   542,   538,   231,   231,
     231,   231,    39,    40,    41,   370,   231,   231,   231,   231,
       8,     8,     8,     8,     3,     8,   231,   231,   591,   593,
       4,     4,     8,     3,     8,     8,   150,   151,   152,   602,
     231,   165,   166,   167,   621,   231,   231,     7,     5,     8,
     231,   251,   709,     4,   707,     3,     8,   231,     8,     8,
     469,     4,     4,   234,   234,   588,    24,   173,   174,   175,
     266,   530,   532,   639,   640,   641,   644,   646,   648,     7,
     630,   631,   632,     4,   232,     4,   704,   231,   231,   642,
     645,   647,   649,     3,     8,   633,     6,     3,     5,   231,
       4,     4,     4,     4,   640,   231,   251,   266,   358,   530,
     532,   634,   635,   632,     7,   710,   711,   172,   643,   231,
     231,     5,     3,     8,   712,     3,     6,     7,   650,   651,
     652,   635,   208,   211,   212,   213,   214,   713,   714,   715,
     717,   718,   719,   720,   711,   653,     6,     3,   716,     4,
       4,     4,   721,     3,     8,   176,   177,   266,   351,   353,
     530,   532,   654,   655,   656,   658,   652,     4,   234,   232,
     232,     4,   714,   657,   659,     3,     8,   231,   231,     4,
       4,   655,   231,   231
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   235,   237,   236,   238,   236,   239,   236,   240,   236,
     241,   236,   242,   236,   243,   236,   244,   236,   245,   236,
     246,   236,   247,   236,   248,   236,   249,   236,   250,   236,
     251,   251,   251,   251,   251,   251,   251,   252,   254,   253,
     255,   256,   256,   257,   257,   257,   259,   258,   260,   260,
     261,   261,   261,   263,   262,   264,   264,   265,   265,   265,
     266,   268,   267,   270,   269,   269,   271,   273,   272,   274,
     274,   274,   275,   275,   275,   275,   275,   275,   275,   275,
     275,   275,   275,   275,   275,   275,   275,   275,   275,   275,
     275,   275,   275,   275,   275,   275,   275,   275,   275,   275,
     275,   275,   275,   275,   275,   275,   275,   275,   275,   275,
     275,   275,   275,   275,   275,   275,   275,   275,   275,   275,
     275,   275,   275,   275,   275,   275,   275,   275,   275,   275,
     275,   275,   275,   275,   275,   275,   275,   275,   275,   275,
     275,   277,   276,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     296,   295,   297,   297,   297,   297,   297,   299,   298,   301,
     300,   302,   303,   305,   304,   306,   306,   306,   306,   307,
     309,   308,   311,   310,   312,   313,   314,   316,   315,   317,
     319,   318,   321,   320,   322,   323,   324,   326,   325,   328,
     327,   329,   329,   329,   330,   330,   330,   330,   330,   330,
     330,   330,   332,   331,   333,   334,   335,   336,   338,   337,
     340,   339,   342,   341,   343,   343,   344,   344,   344,   346,
     345,   347,   347,   347,   348,   348,   348,   348,   348,   348,
     348,   348,   348,   348,   348,   348,   348,   348,   348,   348,
     348,   348,   348,   348,   348,   348,   348,   350,   349,   352,
     351,   354,   353,   356,   355,   357,   359,   358,   360,   361,
     362,   363,   364,   365,   366,   367,   369,   368,   370,   370,
     370,   371,   372,   373,   375,   374,   377,   376,   379,   378,
     381,   380,   383,   382,   384,   384,   384,   385,   385,   387,
     386,   389,   388,   391,   390,   392,   392,   392,   393,   393,
     394,   395,   397,   396,   398,   398,   398,   399,   399,   399,
     400,   401,   403,   402,   405,   404,   406,   406,   406,   407,
     407,   407,   407,   407,   407,   408,   409,   410,   412,   411,
     413,   413,   414,   414,   414,   416,   415,   418,   417,   419,
     419,   419,   419,   420,   420,   422,   421,   424,   423,   426,
     425,   427,   427,   427,   428,   428,   428,   428,   428,   428,
     429,   430,   431,   432,   433,   434,   436,   435,   437,   437,
     438,   438,   438,   440,   439,   442,   441,   443,   443,   443,
     444,   444,   444,   444,   444,   444,   444,   444,   444,   444,
     444,   444,   444,   444,   444,   444,   444,   444,   444,   444,
     444,   444,   444,   444,   444,   444,   444,   444,   444,   444,
     444,   444,   444,   444,   444,   444,   444,   444,   444,   444,
     444,   444,   444,   444,   444,   444,   444,   446,   445,   448,
     447,   450,   449,   452,   451,   454,   453,   456,   455,   457,
     458,   459,   460,   461,   463,   462,   464,   464,   465,   465,
     465,   467,   466,   468,   468,   468,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     471,   470,   473,   472,   474,   474,   475,   475,   475,   477,
     476,   479,   478,   480,   480,   481,   481,   481,   482,   482,
     482,   482,   482,   482,   482,   482,   482,   482,   483,   484,
     485,   487,   486,   489,   488,   491,   490,   492,   494,   493,
     495,   497,   496,   498,   498,   499,   499,   499,   501,   500,
     503,   502,   504,   504,   505,   505,   505,   506,   506,   506,
     506,   506,   506,   506,   506,   506,   506,   506,   507,   509,
     508,   510,   511,   512,   513,   514,   516,   515,   518,   517,
     519,   519,   520,   520,   520,   522,   521,   524,   523,   525,
     525,   525,   526,   526,   526,   526,   526,   526,   526,   526,
     526,   528,   527,   529,   531,   530,   533,   532,   535,   534,
     536,   536,   537,   537,   537,   539,   538,   541,   540,   542,
     542,   542,   543,   543,   543,   543,   543,   543,   543,   543,
     543,   543,   543,   543,   543,   545,   544,   546,   548,   547,
     549,   550,   552,   551,   553,   553,   554,   554,   554,   556,
     555,   558,   557,   559,   559,   560,   560,   560,   561,   561,
     561,   561,   561,   561,   561,   561,   561,   561,   561,   561,
     563,   562,   565,   564,   567,   566,   569,   568,   571,   570,
     573,   572,   575,   574,   577,   576,   579,   578,   580,   582,
     581,   583,   583,   583,   585,   584,   586,   586,   587,   587,
     587,   588,   588,   588,   588,   588,   588,   588,   588,   588,
     588,   588,   588,   588,   588,   588,   589,   591,   590,   593,
     592,   594,   595,   597,   596,   598,   598,   598,   599,   599,
     599,   599,   599,   599,   599,   599,   599,   601,   600,   602,
     602,   602,   603,   605,   604,   606,   607,   608,   610,   609,
     612,   611,   613,   613,   614,   614,   614,   616,   615,   617,
     617,   617,   618,   618,   618,   618,   618,   618,   618,   618,
     618,   618,   618,   618,   618,   620,   619,   621,   621,   621,
     623,   622,   625,   624,   626,   627,   629,   628,   630,   630,
     631,   631,   631,   633,   632,   634,   634,   634,   635,   635,
     635,   635,   635,   636,   251,   638,   637,   639,   639,   639,
     640,   640,   640,   640,   640,   640,   640,   642,   641,   643,
     645,   644,   647,   646,   649,   648,   650,   650,   651,   651,
     651,   653,   652,   654,   654,   654,   655,   655,   655,   655,
     655,   655,   655,   657,   656,   659,   658,   661,   660,   662,
     662,   662,   663,   663,   663,   663,   663,   663,   664,   666,
     665,   667,   669,   668,   671,   670,   673,   672,   674,   674,
     674,   675,   675,   675,   675,   675,   675,   675,   675,   675,
     675,   675,   676,   678,   677,   679,   681,   680,   682,   683,
     685,   684,   686,   686,   688,   687,   690,   689,   692,   691,
     693,   693,   693,   694,   694,   696,   695,   697,   699,   698,
     700,   700,   700,   702,   701,   703,   703,   703,   704,   704,
     704,   704,   704,   704,   704,   705,   707,   706,   709,   708,
     710,   710,   710,   712,   711,   713,   713,   713,   714,   714,
     714,   714,   714,   716,   715,   717,   718,   719,   721,   720,
     723,   722,   724,   724,   724,   725,   725,   726
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
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       0,     4,     0,     4,     3,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     0,     4,     0,     6,     1,     3,     2,
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
  "cert_required", "http_headers", "$@121", "http_header_list",
  "not_empty_http_header_list", "http_header", "$@122",
  "http_header_params", "http_header_param", "$@123", "authentication",
  "$@124", "auth_params", "auth_param", "auth_type", "$@125",
  "auth_type_value", "realm", "$@126", "directory", "$@127", "clients",
  "$@128", "clients_list", "not_empty_clients_list", "basic_auth", "$@129",
  "clients_params", "clients_param", "user_file", "$@130", "password_file",
  "$@131", "dhcp_queue_control", "$@132", "queue_control_params",
  "queue_control_param", "enable_queue", "queue_type", "$@133", "capacity",
  "arbitrary_map_entry", "$@134", "dhcp_ddns", "$@135", "sub_dhcp_ddns",
  "$@136", "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "server_ip", "$@137", "server_port", "sender_ip", "$@138", "sender_port",
  "max_queue_size", "ncr_protocol", "$@139", "ncr_protocol_value",
  "ncr_format", "$@140", "config_control", "$@141", "sub_config_control",
  "$@142", "config_control_params", "config_control_param",
  "config_databases", "$@143", "config_fetch_wait_time", "loggers",
  "$@144", "loggers_entries", "logger_entry", "$@145", "logger_params",
  "logger_param", "debuglevel", "severity", "$@146", "output_options_list",
  "$@147", "output_options_list_content", "output_entry", "$@148",
  "output_params_list", "output_params", "output", "$@149", "flush",
  "maxsize", "maxver", "pattern", "$@150", "compatibility", "$@151",
  "compatibility_params", "compatibility_param", "lenient_option_parsing", YY_NULLPTR
  };
#endif


#if PARSER6_DEBUG
  const short
  Dhcp6Parser::yyrline_[] =
  {
       0,   329,   329,   329,   330,   330,   331,   331,   332,   332,
     333,   333,   334,   334,   335,   335,   336,   336,   337,   337,
     338,   338,   339,   339,   340,   340,   341,   341,   342,   342,
     350,   351,   352,   353,   354,   355,   356,   359,   364,   364,
     375,   378,   379,   382,   387,   393,   398,   398,   405,   406,
     409,   413,   417,   423,   423,   430,   431,   434,   438,   442,
     452,   461,   461,   476,   476,   490,   493,   499,   499,   508,
     509,   510,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     555,   556,   557,   558,   559,   560,   561,   562,   563,   564,
     565,   566,   567,   568,   569,   570,   571,   572,   573,   574,
     575,   576,   577,   578,   579,   580,   581,   582,   583,   584,
     585,   588,   588,   597,   603,   609,   615,   621,   627,   633,
     639,   645,   651,   657,   663,   669,   675,   681,   687,   693,
     699,   699,   708,   711,   714,   717,   720,   726,   726,   735,
     735,   744,   753,   763,   763,   772,   775,   778,   781,   786,
     792,   792,   801,   801,   810,   816,   822,   828,   828,   837,
     843,   843,   852,   852,   861,   867,   873,   879,   879,   891,
     891,   900,   901,   902,   907,   908,   909,   910,   911,   912,
     913,   914,   917,   917,   928,   934,   940,   946,   952,   952,
     965,   965,   978,   978,   989,   990,   993,   994,   995,  1000,
    1000,  1010,  1011,  1012,  1017,  1018,  1019,  1020,  1021,  1022,
    1023,  1024,  1025,  1026,  1027,  1028,  1029,  1030,  1031,  1032,
    1033,  1034,  1035,  1036,  1037,  1038,  1039,  1042,  1042,  1051,
    1051,  1060,  1060,  1069,  1069,  1078,  1084,  1084,  1093,  1099,
    1105,  1111,  1117,  1123,  1129,  1135,  1141,  1141,  1149,  1150,
    1151,  1154,  1160,  1166,  1172,  1172,  1181,  1181,  1190,  1190,
    1199,  1199,  1208,  1208,  1219,  1220,  1221,  1226,  1227,  1230,
    1230,  1249,  1249,  1267,  1267,  1278,  1279,  1280,  1285,  1286,
    1289,  1294,  1299,  1299,  1310,  1311,  1312,  1317,  1318,  1319,
    1322,  1327,  1334,  1334,  1347,  1347,  1360,  1361,  1362,  1367,
    1368,  1369,  1370,  1371,  1372,  1375,  1381,  1387,  1393,  1393,
    1404,  1405,  1408,  1409,  1410,  1415,  1415,  1425,  1425,  1435,
    1436,  1437,  1440,  1443,  1444,  1447,  1447,  1456,  1456,  1465,
    1465,  1477,  1478,  1479,  1484,  1485,  1486,  1487,  1488,  1489,
    1492,  1498,  1504,  1510,  1516,  1522,  1531,  1531,  1545,  1546,
    1549,  1550,  1551,  1560,  1560,  1586,  1586,  1597,  1598,  1599,
    1605,  1606,  1607,  1608,  1609,  1610,  1611,  1612,  1613,  1614,
    1615,  1616,  1617,  1618,  1619,  1620,  1621,  1622,  1623,  1624,
    1625,  1626,  1627,  1628,  1629,  1630,  1631,  1632,  1633,  1634,
    1635,  1636,  1637,  1638,  1639,  1640,  1641,  1642,  1643,  1644,
    1645,  1646,  1647,  1648,  1649,  1650,  1651,  1654,  1654,  1663,
    1663,  1672,  1672,  1681,  1681,  1691,  1691,  1702,  1702,  1713,
    1719,  1725,  1731,  1737,  1745,  1745,  1757,  1758,  1762,  1763,
    1764,  1769,  1769,  1777,  1778,  1779,  1784,  1785,  1786,  1787,
    1788,  1789,  1790,  1791,  1792,  1793,  1794,  1795,  1796,  1797,
    1798,  1799,  1800,  1801,  1802,  1803,  1804,  1805,  1806,  1807,
    1808,  1809,  1810,  1811,  1812,  1813,  1814,  1815,  1816,  1817,
    1818,  1819,  1820,  1821,  1822,  1823,  1824,  1825,  1826,  1827,
    1834,  1834,  1848,  1848,  1857,  1858,  1861,  1862,  1863,  1870,
    1870,  1885,  1885,  1899,  1900,  1903,  1904,  1905,  1910,  1911,
    1912,  1913,  1914,  1915,  1916,  1917,  1918,  1919,  1922,  1924,
    1930,  1932,  1932,  1941,  1941,  1950,  1950,  1959,  1961,  1961,
    1970,  1980,  1980,  1993,  1994,  1999,  2000,  2001,  2008,  2008,
    2020,  2020,  2032,  2033,  2038,  2039,  2040,  2047,  2048,  2049,
    2050,  2051,  2052,  2053,  2054,  2055,  2056,  2057,  2060,  2062,
    2062,  2071,  2073,  2075,  2081,  2087,  2093,  2093,  2107,  2107,
    2120,  2121,  2124,  2125,  2126,  2131,  2131,  2141,  2141,  2151,
    2152,  2153,  2158,  2159,  2160,  2161,  2162,  2163,  2164,  2165,
    2166,  2169,  2169,  2178,  2184,  2184,  2209,  2209,  2239,  2239,
    2252,  2253,  2256,  2257,  2258,  2263,  2263,  2275,  2275,  2287,
    2288,  2289,  2294,  2295,  2296,  2297,  2298,  2299,  2300,  2301,
    2302,  2303,  2304,  2305,  2306,  2309,  2309,  2318,  2324,  2324,
    2333,  2339,  2348,  2348,  2359,  2360,  2363,  2364,  2365,  2370,
    2370,  2379,  2379,  2388,  2389,  2392,  2393,  2394,  2400,  2401,
    2402,  2403,  2404,  2405,  2406,  2407,  2408,  2409,  2410,  2411,
    2414,  2414,  2425,  2425,  2436,  2436,  2447,  2447,  2456,  2456,
    2465,  2465,  2474,  2474,  2483,  2483,  2497,  2497,  2508,  2514,
    2514,  2525,  2526,  2527,  2532,  2532,  2542,  2543,  2546,  2547,
    2548,  2553,  2554,  2555,  2556,  2557,  2558,  2559,  2560,  2561,
    2562,  2563,  2564,  2565,  2566,  2567,  2570,  2572,  2572,  2581,
    2581,  2591,  2597,  2606,  2606,  2619,  2620,  2621,  2626,  2627,
    2628,  2629,  2630,  2631,  2632,  2633,  2634,  2637,  2637,  2645,
    2646,  2647,  2650,  2656,  2656,  2665,  2671,  2679,  2687,  2687,
    2699,  2699,  2711,  2712,  2715,  2716,  2717,  2722,  2722,  2730,
    2731,  2732,  2737,  2738,  2739,  2740,  2741,  2742,  2743,  2744,
    2745,  2746,  2747,  2748,  2749,  2752,  2752,  2761,  2762,  2763,
    2766,  2766,  2776,  2776,  2786,  2792,  2798,  2798,  2808,  2809,
    2812,  2813,  2814,  2819,  2819,  2827,  2828,  2829,  2834,  2835,
    2836,  2837,  2838,  2841,  2841,  2852,  2852,  2865,  2866,  2867,
    2872,  2873,  2874,  2875,  2876,  2877,  2878,  2881,  2881,  2889,
    2892,  2892,  2901,  2901,  2910,  2910,  2921,  2922,  2925,  2926,
    2927,  2932,  2932,  2940,  2941,  2942,  2947,  2948,  2949,  2950,
    2951,  2952,  2953,  2956,  2956,  2965,  2965,  2976,  2976,  2989,
    2990,  2991,  2996,  2997,  2998,  2999,  3000,  3001,  3004,  3010,
    3010,  3019,  3025,  3025,  3035,  3035,  3048,  3048,  3058,  3059,
    3060,  3065,  3066,  3067,  3068,  3069,  3070,  3071,  3072,  3073,
    3074,  3075,  3078,  3084,  3084,  3093,  3099,  3099,  3108,  3114,
    3120,  3120,  3129,  3130,  3133,  3133,  3144,  3144,  3156,  3156,
    3166,  3167,  3168,  3174,  3175,  3178,  3178,  3189,  3197,  3197,
    3210,  3211,  3212,  3218,  3218,  3226,  3227,  3228,  3233,  3234,
    3235,  3236,  3237,  3238,  3239,  3242,  3248,  3248,  3257,  3257,
    3268,  3269,  3270,  3275,  3275,  3283,  3284,  3285,  3290,  3291,
    3292,  3293,  3294,  3297,  3297,  3306,  3312,  3318,  3324,  3324,
    3333,  3333,  3344,  3345,  3346,  3351,  3352,  3355
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
#line 6997 "dhcp6_parser.cc"

#line 3361 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
