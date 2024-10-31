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

  case 438: // $@64: %empty
#line 1655 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2775 "dhcp6_parser.cc"
    break;

  case 439: // subnet: "subnet" $@64 ":" "constant string"
#line 1658 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2785 "dhcp6_parser.cc"
    break;

  case 440: // $@65: %empty
#line 1664 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2794 "dhcp6_parser.cc"
    break;

  case 441: // interface: "interface" $@65 ":" "constant string"
#line 1667 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2804 "dhcp6_parser.cc"
    break;

  case 442: // $@66: %empty
#line 1673 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2813 "dhcp6_parser.cc"
    break;

  case 443: // interface_id: "interface-id" $@66 ":" "constant string"
#line 1676 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2823 "dhcp6_parser.cc"
    break;

  case 444: // $@67: %empty
#line 1682 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2832 "dhcp6_parser.cc"
    break;

  case 445: // client_class: "client-class" $@67 ":" "constant string"
#line 1685 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2842 "dhcp6_parser.cc"
    break;

  case 446: // $@68: %empty
#line 1692 "dhcp6_parser.yy"
                                       {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2854 "dhcp6_parser.cc"
    break;

  case 447: // network_client_classes: "client-classes" $@68 ":" list_strings
#line 1698 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2863 "dhcp6_parser.cc"
    break;

  case 448: // $@69: %empty
#line 1704 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2875 "dhcp6_parser.cc"
    break;

  case 449: // require_client_classes: "require-client-classes" $@69 ":" list_strings
#line 1710 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2884 "dhcp6_parser.cc"
    break;

  case 450: // $@70: %empty
#line 1715 "dhcp6_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2896 "dhcp6_parser.cc"
    break;

  case 451: // evaluate_additional_classes: "evaluate-additional-classes" $@70 ":" list_strings
#line 1721 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2905 "dhcp6_parser.cc"
    break;

  case 452: // reservations_global: "reservations-global" ":" "boolean"
#line 1726 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2915 "dhcp6_parser.cc"
    break;

  case 453: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1732 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2925 "dhcp6_parser.cc"
    break;

  case 454: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1738 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2935 "dhcp6_parser.cc"
    break;

  case 455: // id: "id" ":" "integer"
#line 1744 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2945 "dhcp6_parser.cc"
    break;

  case 456: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1750 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2955 "dhcp6_parser.cc"
    break;

  case 457: // $@71: %empty
#line 1758 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2967 "dhcp6_parser.cc"
    break;

  case 458: // shared_networks: "shared-networks" $@71 ":" "[" shared_networks_content "]"
#line 1764 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2976 "dhcp6_parser.cc"
    break;

  case 463: // shared_networks_list: shared_networks_list ","
#line 1777 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2984 "dhcp6_parser.cc"
    break;

  case 464: // $@72: %empty
#line 1782 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2994 "dhcp6_parser.cc"
    break;

  case 465: // shared_network: "{" $@72 shared_network_params "}"
#line 1786 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3002 "dhcp6_parser.cc"
    break;

  case 468: // shared_network_params: shared_network_params ","
#line 1792 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3010 "dhcp6_parser.cc"
    break;

  case 514: // $@73: %empty
#line 1848 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3022 "dhcp6_parser.cc"
    break;

  case 515: // option_def_list: "option-def" $@73 ":" "[" option_def_list_content "]"
#line 1854 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3031 "dhcp6_parser.cc"
    break;

  case 516: // $@74: %empty
#line 1862 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3040 "dhcp6_parser.cc"
    break;

  case 517: // sub_option_def_list: "{" $@74 option_def_list "}"
#line 1865 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 3048 "dhcp6_parser.cc"
    break;

  case 522: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1877 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3056 "dhcp6_parser.cc"
    break;

  case 523: // $@75: %empty
#line 1884 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3066 "dhcp6_parser.cc"
    break;

  case 524: // option_def_entry: "{" $@75 option_def_params "}"
#line 1888 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3078 "dhcp6_parser.cc"
    break;

  case 525: // $@76: %empty
#line 1899 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3088 "dhcp6_parser.cc"
    break;

  case 526: // sub_option_def: "{" $@76 option_def_params "}"
#line 1903 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3100 "dhcp6_parser.cc"
    break;

  case 531: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1919 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3108 "dhcp6_parser.cc"
    break;

  case 543: // code: "code" ":" "integer"
#line 1938 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3118 "dhcp6_parser.cc"
    break;

  case 545: // $@77: %empty
#line 1946 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3127 "dhcp6_parser.cc"
    break;

  case 546: // option_def_type: "type" $@77 ":" "constant string"
#line 1949 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3137 "dhcp6_parser.cc"
    break;

  case 547: // $@78: %empty
#line 1955 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3146 "dhcp6_parser.cc"
    break;

  case 548: // option_def_record_types: "record-types" $@78 ":" "constant string"
#line 1958 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3156 "dhcp6_parser.cc"
    break;

  case 549: // $@79: %empty
#line 1964 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3165 "dhcp6_parser.cc"
    break;

  case 550: // space: "space" $@79 ":" "constant string"
#line 1967 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3175 "dhcp6_parser.cc"
    break;

  case 552: // $@80: %empty
#line 1975 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3184 "dhcp6_parser.cc"
    break;

  case 553: // option_def_encapsulate: "encapsulate" $@80 ":" "constant string"
#line 1978 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3194 "dhcp6_parser.cc"
    break;

  case 554: // option_def_array: "array" ":" "boolean"
#line 1984 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3204 "dhcp6_parser.cc"
    break;

  case 555: // $@81: %empty
#line 1994 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3216 "dhcp6_parser.cc"
    break;

  case 556: // option_data_list: "option-data" $@81 ":" "[" option_data_list_content "]"
#line 2000 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3225 "dhcp6_parser.cc"
    break;

  case 561: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2015 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3233 "dhcp6_parser.cc"
    break;

  case 562: // $@82: %empty
#line 2022 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3243 "dhcp6_parser.cc"
    break;

  case 563: // option_data_entry: "{" $@82 option_data_params "}"
#line 2026 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3252 "dhcp6_parser.cc"
    break;

  case 564: // $@83: %empty
#line 2034 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3262 "dhcp6_parser.cc"
    break;

  case 565: // sub_option_data: "{" $@83 option_data_params "}"
#line 2038 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3271 "dhcp6_parser.cc"
    break;

  case 570: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2054 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3279 "dhcp6_parser.cc"
    break;

  case 583: // $@84: %empty
#line 2076 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3288 "dhcp6_parser.cc"
    break;

  case 584: // option_data_data: "data" $@84 ":" "constant string"
#line 2079 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3298 "dhcp6_parser.cc"
    break;

  case 587: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2089 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3308 "dhcp6_parser.cc"
    break;

  case 588: // option_data_always_send: "always-send" ":" "boolean"
#line 2095 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3318 "dhcp6_parser.cc"
    break;

  case 589: // option_data_never_send: "never-send" ":" "boolean"
#line 2101 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3328 "dhcp6_parser.cc"
    break;

  case 590: // $@85: %empty
#line 2107 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3340 "dhcp6_parser.cc"
    break;

  case 591: // option_data_client_classes: "client-classes" $@85 ":" list_strings
#line 2113 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3349 "dhcp6_parser.cc"
    break;

  case 592: // $@86: %empty
#line 2121 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3361 "dhcp6_parser.cc"
    break;

  case 593: // pools_list: "pools" $@86 ":" "[" pools_list_content "]"
#line 2127 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3370 "dhcp6_parser.cc"
    break;

  case 598: // not_empty_pools_list: not_empty_pools_list ","
#line 2140 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3378 "dhcp6_parser.cc"
    break;

  case 599: // $@87: %empty
#line 2145 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3388 "dhcp6_parser.cc"
    break;

  case 600: // pool_list_entry: "{" $@87 pool_params "}"
#line 2149 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3398 "dhcp6_parser.cc"
    break;

  case 601: // $@88: %empty
#line 2155 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3408 "dhcp6_parser.cc"
    break;

  case 602: // sub_pool6: "{" $@88 pool_params "}"
#line 2159 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3418 "dhcp6_parser.cc"
    break;

  case 605: // pool_params: pool_params ","
#line 2167 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3426 "dhcp6_parser.cc"
    break;

  case 616: // $@89: %empty
#line 2184 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3435 "dhcp6_parser.cc"
    break;

  case 617: // pool_entry: "pool" $@89 ":" "constant string"
#line 2187 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3445 "dhcp6_parser.cc"
    break;

  case 618: // pool_id: "pool-id" ":" "integer"
#line 2193 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3455 "dhcp6_parser.cc"
    break;

  case 619: // $@90: %empty
#line 2199 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3463 "dhcp6_parser.cc"
    break;

  case 620: // user_context: "user-context" $@90 ":" map_value
#line 2201 "dhcp6_parser.yy"
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
#line 3490 "dhcp6_parser.cc"
    break;

  case 621: // $@91: %empty
#line 2224 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3498 "dhcp6_parser.cc"
    break;

  case 622: // comment: "comment" $@91 ":" "constant string"
#line 2226 "dhcp6_parser.yy"
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
#line 3527 "dhcp6_parser.cc"
    break;

  case 623: // $@92: %empty
#line 2254 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3539 "dhcp6_parser.cc"
    break;

  case 624: // pd_pools_list: "pd-pools" $@92 ":" "[" pd_pools_list_content "]"
#line 2260 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3548 "dhcp6_parser.cc"
    break;

  case 629: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2273 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3556 "dhcp6_parser.cc"
    break;

  case 630: // $@93: %empty
#line 2278 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3566 "dhcp6_parser.cc"
    break;

  case 631: // pd_pool_entry: "{" $@93 pd_pool_params "}"
#line 2282 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3578 "dhcp6_parser.cc"
    break;

  case 632: // $@94: %empty
#line 2290 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3588 "dhcp6_parser.cc"
    break;

  case 633: // sub_pd_pool: "{" $@94 pd_pool_params "}"
#line 2294 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3600 "dhcp6_parser.cc"
    break;

  case 636: // pd_pool_params: pd_pool_params ","
#line 2304 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3608 "dhcp6_parser.cc"
    break;

  case 651: // $@95: %empty
#line 2325 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3617 "dhcp6_parser.cc"
    break;

  case 652: // pd_prefix: "prefix" $@95 ":" "constant string"
#line 2328 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3627 "dhcp6_parser.cc"
    break;

  case 653: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2334 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3637 "dhcp6_parser.cc"
    break;

  case 654: // $@96: %empty
#line 2340 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3646 "dhcp6_parser.cc"
    break;

  case 655: // excluded_prefix: "excluded-prefix" $@96 ":" "constant string"
#line 2343 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3656 "dhcp6_parser.cc"
    break;

  case 656: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2349 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3666 "dhcp6_parser.cc"
    break;

  case 657: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2355 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3676 "dhcp6_parser.cc"
    break;

  case 658: // $@97: %empty
#line 2364 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3688 "dhcp6_parser.cc"
    break;

  case 659: // reservations: "reservations" $@97 ":" "[" reservations_list "]"
#line 2370 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3697 "dhcp6_parser.cc"
    break;

  case 664: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2381 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3705 "dhcp6_parser.cc"
    break;

  case 665: // $@98: %empty
#line 2386 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3715 "dhcp6_parser.cc"
    break;

  case 666: // reservation: "{" $@98 reservation_params "}"
#line 2390 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3724 "dhcp6_parser.cc"
    break;

  case 667: // $@99: %empty
#line 2395 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3734 "dhcp6_parser.cc"
    break;

  case 668: // sub_reservation: "{" $@99 reservation_params "}"
#line 2399 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3743 "dhcp6_parser.cc"
    break;

  case 673: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2410 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3751 "dhcp6_parser.cc"
    break;

  case 686: // $@100: %empty
#line 2430 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3763 "dhcp6_parser.cc"
    break;

  case 687: // ip_addresses: "ip-addresses" $@100 ":" list_strings
#line 2436 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3772 "dhcp6_parser.cc"
    break;

  case 688: // $@101: %empty
#line 2441 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3784 "dhcp6_parser.cc"
    break;

  case 689: // prefixes: "prefixes" $@101 ":" list_strings
#line 2447 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3793 "dhcp6_parser.cc"
    break;

  case 690: // $@102: %empty
#line 2452 "dhcp6_parser.yy"
                                     {
    ctx.unique("excluded-prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3805 "dhcp6_parser.cc"
    break;

  case 691: // excluded_prefixes: "excluded-prefixes" $@102 ":" list_strings
#line 2458 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3814 "dhcp6_parser.cc"
    break;

  case 692: // $@103: %empty
#line 2463 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3823 "dhcp6_parser.cc"
    break;

  case 693: // duid: "duid" $@103 ":" "constant string"
#line 2466 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3833 "dhcp6_parser.cc"
    break;

  case 694: // $@104: %empty
#line 2472 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3842 "dhcp6_parser.cc"
    break;

  case 695: // hw_address: "hw-address" $@104 ":" "constant string"
#line 2475 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3852 "dhcp6_parser.cc"
    break;

  case 696: // $@105: %empty
#line 2481 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3861 "dhcp6_parser.cc"
    break;

  case 697: // hostname: "hostname" $@105 ":" "constant string"
#line 2484 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3871 "dhcp6_parser.cc"
    break;

  case 698: // $@106: %empty
#line 2490 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3880 "dhcp6_parser.cc"
    break;

  case 699: // flex_id_value: "flex-id" $@106 ":" "constant string"
#line 2493 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3890 "dhcp6_parser.cc"
    break;

  case 700: // $@107: %empty
#line 2499 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3902 "dhcp6_parser.cc"
    break;

  case 701: // reservation_client_classes: "client-classes" $@107 ":" list_strings
#line 2505 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3911 "dhcp6_parser.cc"
    break;

  case 702: // $@108: %empty
#line 2513 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3923 "dhcp6_parser.cc"
    break;

  case 703: // relay: "relay" $@108 ":" "{" relay_map "}"
#line 2519 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3932 "dhcp6_parser.cc"
    break;

  case 705: // $@109: %empty
#line 2530 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3944 "dhcp6_parser.cc"
    break;

  case 706: // client_classes: "client-classes" $@109 ":" "[" client_classes_list "]"
#line 2536 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3953 "dhcp6_parser.cc"
    break;

  case 709: // client_classes_list: client_classes_list ","
#line 2543 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3961 "dhcp6_parser.cc"
    break;

  case 710: // $@110: %empty
#line 2548 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3971 "dhcp6_parser.cc"
    break;

  case 711: // client_class_entry: "{" $@110 client_class_params "}"
#line 2552 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3981 "dhcp6_parser.cc"
    break;

  case 716: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2564 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3989 "dhcp6_parser.cc"
    break;

  case 733: // $@111: %empty
#line 2588 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3998 "dhcp6_parser.cc"
    break;

  case 734: // client_class_test: "test" $@111 ":" "constant string"
#line 2591 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4008 "dhcp6_parser.cc"
    break;

  case 735: // $@112: %empty
#line 2597 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4017 "dhcp6_parser.cc"
    break;

  case 736: // client_class_template_test: "template-test" $@112 ":" "constant string"
#line 2600 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4027 "dhcp6_parser.cc"
    break;

  case 737: // only_if_required: "only-if-required" ":" "boolean"
#line 2607 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4037 "dhcp6_parser.cc"
    break;

  case 738: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2613 "dhcp6_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4047 "dhcp6_parser.cc"
    break;

  case 739: // $@113: %empty
#line 2622 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 4059 "dhcp6_parser.cc"
    break;

  case 740: // server_id: "server-id" $@113 ":" "{" server_id_params "}"
#line 2628 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4070 "dhcp6_parser.cc"
    break;

  case 743: // server_id_params: server_id_params ","
#line 2637 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4078 "dhcp6_parser.cc"
    break;

  case 753: // $@114: %empty
#line 2653 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 4087 "dhcp6_parser.cc"
    break;

  case 754: // server_id_type: "type" $@114 ":" duid_type
#line 2656 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4096 "dhcp6_parser.cc"
    break;

  case 755: // duid_type: "LLT"
#line 2661 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4102 "dhcp6_parser.cc"
    break;

  case 756: // duid_type: "EN"
#line 2662 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4108 "dhcp6_parser.cc"
    break;

  case 757: // duid_type: "LL"
#line 2663 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4114 "dhcp6_parser.cc"
    break;

  case 758: // htype: "htype" ":" "integer"
#line 2666 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4124 "dhcp6_parser.cc"
    break;

  case 759: // $@115: %empty
#line 2672 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4133 "dhcp6_parser.cc"
    break;

  case 760: // identifier: "identifier" $@115 ":" "constant string"
#line 2675 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4143 "dhcp6_parser.cc"
    break;

  case 761: // time: "time" ":" "integer"
#line 2681 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4153 "dhcp6_parser.cc"
    break;

  case 762: // enterprise_id: "enterprise-id" ":" "integer"
#line 2687 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4163 "dhcp6_parser.cc"
    break;

  case 763: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2695 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4173 "dhcp6_parser.cc"
    break;

  case 764: // $@116: %empty
#line 2703 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4186 "dhcp6_parser.cc"
    break;

  case 765: // control_socket: "control-socket" $@116 ":" "{" control_socket_params "}"
#line 2710 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4195 "dhcp6_parser.cc"
    break;

  case 766: // $@117: %empty
#line 2715 "dhcp6_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4208 "dhcp6_parser.cc"
    break;

  case 767: // control_sockets: "control-sockets" $@117 ":" "[" control_socket_list "]"
#line 2722 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4217 "dhcp6_parser.cc"
    break;

  case 772: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2733 "dhcp6_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4225 "dhcp6_parser.cc"
    break;

  case 773: // $@118: %empty
#line 2738 "dhcp6_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4235 "dhcp6_parser.cc"
    break;

  case 774: // control_socket_entry: "{" $@118 control_socket_params "}"
#line 2742 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4243 "dhcp6_parser.cc"
    break;

  case 777: // control_socket_params: control_socket_params ","
#line 2748 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4251 "dhcp6_parser.cc"
    break;

  case 791: // $@119: %empty
#line 2768 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4260 "dhcp6_parser.cc"
    break;

  case 792: // control_socket_type: "socket-type" $@119 ":" control_socket_type_value
#line 2771 "dhcp6_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4269 "dhcp6_parser.cc"
    break;

  case 793: // control_socket_type_value: "unix"
#line 2777 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4275 "dhcp6_parser.cc"
    break;

  case 794: // control_socket_type_value: "http"
#line 2778 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4281 "dhcp6_parser.cc"
    break;

  case 795: // control_socket_type_value: "https"
#line 2779 "dhcp6_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4287 "dhcp6_parser.cc"
    break;

  case 796: // $@120: %empty
#line 2782 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4297 "dhcp6_parser.cc"
    break;

  case 797: // control_socket_name: "socket-name" $@120 ":" "constant string"
#line 2786 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4307 "dhcp6_parser.cc"
    break;

  case 798: // $@121: %empty
#line 2792 "dhcp6_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4317 "dhcp6_parser.cc"
    break;

  case 799: // control_socket_address: "socket-address" $@121 ":" "constant string"
#line 2796 "dhcp6_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4327 "dhcp6_parser.cc"
    break;

  case 800: // control_socket_port: "socket-port" ":" "integer"
#line 2802 "dhcp6_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4337 "dhcp6_parser.cc"
    break;

  case 801: // cert_required: "cert-required" ":" "boolean"
#line 2808 "dhcp6_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4347 "dhcp6_parser.cc"
    break;

  case 802: // $@122: %empty
#line 2814 "dhcp6_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4359 "dhcp6_parser.cc"
    break;

  case 803: // http_headers: "http-headers" $@122 ":" "[" http_header_list "]"
#line 2820 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4368 "dhcp6_parser.cc"
    break;

  case 808: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2831 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4376 "dhcp6_parser.cc"
    break;

  case 809: // $@123: %empty
#line 2836 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4386 "dhcp6_parser.cc"
    break;

  case 810: // http_header: "{" $@123 http_header_params "}"
#line 2840 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4394 "dhcp6_parser.cc"
    break;

  case 813: // http_header_params: http_header_params ","
#line 2846 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4402 "dhcp6_parser.cc"
    break;

  case 819: // $@124: %empty
#line 2858 "dhcp6_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4411 "dhcp6_parser.cc"
    break;

  case 820: // header_value: "value" $@124 ":" "constant string"
#line 2861 "dhcp6_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4421 "dhcp6_parser.cc"
    break;

  case 821: // $@125: %empty
#line 2869 "dhcp6_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4433 "dhcp6_parser.cc"
    break;

  case 822: // authentication: "authentication" $@125 ":" "{" auth_params "}"
#line 2875 "dhcp6_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4444 "dhcp6_parser.cc"
    break;

  case 825: // auth_params: auth_params ","
#line 2884 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4452 "dhcp6_parser.cc"
    break;

  case 833: // $@126: %empty
#line 2898 "dhcp6_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4461 "dhcp6_parser.cc"
    break;

  case 834: // auth_type: "type" $@126 ":" auth_type_value
#line 2901 "dhcp6_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4470 "dhcp6_parser.cc"
    break;

  case 835: // auth_type_value: "basic"
#line 2906 "dhcp6_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4476 "dhcp6_parser.cc"
    break;

  case 836: // $@127: %empty
#line 2909 "dhcp6_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4485 "dhcp6_parser.cc"
    break;

  case 837: // realm: "realm" $@127 ":" "constant string"
#line 2912 "dhcp6_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4495 "dhcp6_parser.cc"
    break;

  case 838: // $@128: %empty
#line 2918 "dhcp6_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4504 "dhcp6_parser.cc"
    break;

  case 839: // directory: "directory" $@128 ":" "constant string"
#line 2921 "dhcp6_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4514 "dhcp6_parser.cc"
    break;

  case 840: // $@129: %empty
#line 2927 "dhcp6_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4526 "dhcp6_parser.cc"
    break;

  case 841: // clients: "clients" $@129 ":" "[" clients_list "]"
#line 2933 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4535 "dhcp6_parser.cc"
    break;

  case 846: // not_empty_clients_list: not_empty_clients_list ","
#line 2944 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4543 "dhcp6_parser.cc"
    break;

  case 847: // $@130: %empty
#line 2949 "dhcp6_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4553 "dhcp6_parser.cc"
    break;

  case 848: // basic_auth: "{" $@130 clients_params "}"
#line 2953 "dhcp6_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4561 "dhcp6_parser.cc"
    break;

  case 851: // clients_params: clients_params ","
#line 2959 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4569 "dhcp6_parser.cc"
    break;

  case 859: // $@131: %empty
#line 2973 "dhcp6_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4578 "dhcp6_parser.cc"
    break;

  case 860: // user_file: "user-file" $@131 ":" "constant string"
#line 2976 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4588 "dhcp6_parser.cc"
    break;

  case 861: // $@132: %empty
#line 2982 "dhcp6_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4597 "dhcp6_parser.cc"
    break;

  case 862: // password_file: "password-file" $@132 ":" "constant string"
#line 2985 "dhcp6_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4607 "dhcp6_parser.cc"
    break;

  case 863: // $@133: %empty
#line 2993 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4619 "dhcp6_parser.cc"
    break;

  case 864: // dhcp_queue_control: "dhcp-queue-control" $@133 ":" "{" queue_control_params "}"
#line 2999 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4630 "dhcp6_parser.cc"
    break;

  case 867: // queue_control_params: queue_control_params ","
#line 3008 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4638 "dhcp6_parser.cc"
    break;

  case 874: // enable_queue: "enable-queue" ":" "boolean"
#line 3021 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4648 "dhcp6_parser.cc"
    break;

  case 875: // $@134: %empty
#line 3027 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4657 "dhcp6_parser.cc"
    break;

  case 876: // queue_type: "queue-type" $@134 ":" "constant string"
#line 3030 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4667 "dhcp6_parser.cc"
    break;

  case 877: // capacity: "capacity" ":" "integer"
#line 3036 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4677 "dhcp6_parser.cc"
    break;

  case 878: // $@135: %empty
#line 3042 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4686 "dhcp6_parser.cc"
    break;

  case 879: // arbitrary_map_entry: "constant string" $@135 ":" value
#line 3045 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4695 "dhcp6_parser.cc"
    break;

  case 880: // $@136: %empty
#line 3052 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4707 "dhcp6_parser.cc"
    break;

  case 881: // dhcp_ddns: "dhcp-ddns" $@136 ":" "{" dhcp_ddns_params "}"
#line 3058 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4718 "dhcp6_parser.cc"
    break;

  case 882: // $@137: %empty
#line 3065 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4728 "dhcp6_parser.cc"
    break;

  case 883: // sub_dhcp_ddns: "{" $@137 dhcp_ddns_params "}"
#line 3069 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4738 "dhcp6_parser.cc"
    break;

  case 886: // dhcp_ddns_params: dhcp_ddns_params ","
#line 3077 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4746 "dhcp6_parser.cc"
    break;

  case 898: // enable_updates: "enable-updates" ":" "boolean"
#line 3095 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4756 "dhcp6_parser.cc"
    break;

  case 899: // $@138: %empty
#line 3101 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4765 "dhcp6_parser.cc"
    break;

  case 900: // server_ip: "server-ip" $@138 ":" "constant string"
#line 3104 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4775 "dhcp6_parser.cc"
    break;

  case 901: // server_port: "server-port" ":" "integer"
#line 3110 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4785 "dhcp6_parser.cc"
    break;

  case 902: // $@139: %empty
#line 3116 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4794 "dhcp6_parser.cc"
    break;

  case 903: // sender_ip: "sender-ip" $@139 ":" "constant string"
#line 3119 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4804 "dhcp6_parser.cc"
    break;

  case 904: // sender_port: "sender-port" ":" "integer"
#line 3125 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4814 "dhcp6_parser.cc"
    break;

  case 905: // max_queue_size: "max-queue-size" ":" "integer"
#line 3131 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4824 "dhcp6_parser.cc"
    break;

  case 906: // $@140: %empty
#line 3137 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4833 "dhcp6_parser.cc"
    break;

  case 907: // ncr_protocol: "ncr-protocol" $@140 ":" ncr_protocol_value
#line 3140 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4842 "dhcp6_parser.cc"
    break;

  case 908: // ncr_protocol_value: "UDP"
#line 3146 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4848 "dhcp6_parser.cc"
    break;

  case 909: // ncr_protocol_value: "TCP"
#line 3147 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4854 "dhcp6_parser.cc"
    break;

  case 910: // $@141: %empty
#line 3150 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4863 "dhcp6_parser.cc"
    break;

  case 911: // ncr_format: "ncr-format" $@141 ":" "JSON"
#line 3153 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4873 "dhcp6_parser.cc"
    break;

  case 912: // $@142: %empty
#line 3161 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4885 "dhcp6_parser.cc"
    break;

  case 913: // config_control: "config-control" $@142 ":" "{" config_control_params "}"
#line 3167 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4895 "dhcp6_parser.cc"
    break;

  case 914: // $@143: %empty
#line 3173 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4905 "dhcp6_parser.cc"
    break;

  case 915: // sub_config_control: "{" $@143 config_control_params "}"
#line 3177 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4914 "dhcp6_parser.cc"
    break;

  case 918: // config_control_params: config_control_params ","
#line 3185 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4922 "dhcp6_parser.cc"
    break;

  case 921: // $@144: %empty
#line 3195 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4934 "dhcp6_parser.cc"
    break;

  case 922: // config_databases: "config-databases" $@144 ":" "[" database_list "]"
#line 3201 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4943 "dhcp6_parser.cc"
    break;

  case 923: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3206 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4953 "dhcp6_parser.cc"
    break;

  case 924: // $@145: %empty
#line 3214 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4965 "dhcp6_parser.cc"
    break;

  case 925: // loggers: "loggers" $@145 ":" "[" loggers_entries "]"
#line 3220 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4974 "dhcp6_parser.cc"
    break;

  case 928: // loggers_entries: loggers_entries ","
#line 3229 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4982 "dhcp6_parser.cc"
    break;

  case 929: // $@146: %empty
#line 3235 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4992 "dhcp6_parser.cc"
    break;

  case 930: // logger_entry: "{" $@146 logger_params "}"
#line 3239 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 5000 "dhcp6_parser.cc"
    break;

  case 933: // logger_params: logger_params ","
#line 3245 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 5008 "dhcp6_parser.cc"
    break;

  case 941: // debuglevel: "debuglevel" ":" "integer"
#line 3259 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 5018 "dhcp6_parser.cc"
    break;

  case 942: // $@147: %empty
#line 3265 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5027 "dhcp6_parser.cc"
    break;

  case 943: // severity: "severity" $@147 ":" "constant string"
#line 3268 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 5037 "dhcp6_parser.cc"
    break;

  case 944: // $@148: %empty
#line 3274 "dhcp6_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 5049 "dhcp6_parser.cc"
    break;

  case 945: // output_options_list: "output-options" $@148 ":" "[" output_options_list_content "]"
#line 3280 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5058 "dhcp6_parser.cc"
    break;

  case 948: // output_options_list_content: output_options_list_content ","
#line 3287 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 5066 "dhcp6_parser.cc"
    break;

  case 949: // $@149: %empty
#line 3292 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 5076 "dhcp6_parser.cc"
    break;

  case 950: // output_entry: "{" $@149 output_params_list "}"
#line 3296 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 5084 "dhcp6_parser.cc"
    break;

  case 953: // output_params_list: output_params_list ","
#line 3302 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 5092 "dhcp6_parser.cc"
    break;

  case 959: // $@150: %empty
#line 3314 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5101 "dhcp6_parser.cc"
    break;

  case 960: // output: "output" $@150 ":" "constant string"
#line 3317 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5111 "dhcp6_parser.cc"
    break;

  case 961: // flush: "flush" ":" "boolean"
#line 3323 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5121 "dhcp6_parser.cc"
    break;

  case 962: // maxsize: "maxsize" ":" "integer"
#line 3329 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5131 "dhcp6_parser.cc"
    break;

  case 963: // maxver: "maxver" ":" "integer"
#line 3335 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5141 "dhcp6_parser.cc"
    break;

  case 964: // $@151: %empty
#line 3341 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5150 "dhcp6_parser.cc"
    break;

  case 965: // pattern: "pattern" $@151 ":" "constant string"
#line 3344 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5160 "dhcp6_parser.cc"
    break;

  case 966: // $@152: %empty
#line 3350 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5172 "dhcp6_parser.cc"
    break;

  case 967: // compatibility: "compatibility" $@152 ":" "{" compatibility_params "}"
#line 3356 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5181 "dhcp6_parser.cc"
    break;

  case 970: // compatibility_params: compatibility_params ","
#line 3363 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5189 "dhcp6_parser.cc"
    break;

  case 973: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3372 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5199 "dhcp6_parser.cc"
    break;


#line 5203 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1411;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     438, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411,    40,    43,    44,    81,    87,
     102,   120,   128,   134,   210,   224,   252,   265,   266,   289,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,    43,  -164,
      59,   734,    37,  1393,   183,     2,   121,     8,   129,   140,
     -70,   204,    62, -1411,    80,   113,    93,   261,   126, -1411,
     109, -1411, -1411, -1411, -1411, -1411, -1411, -1411,   295,   303,
     319,   325,   327,   338,   350,   357,   411,   417,   437,   450,
     452,   458, -1411,   459,   460,   461,   462,   463, -1411, -1411,
   -1411,   464,   465,   466,   467, -1411, -1411, -1411,   468, -1411,
   -1411, -1411, -1411, -1411, -1411,   469,   471,   472, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411,   473, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411,   475,   476,   477, -1411, -1411,
     478, -1411,   157, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411,   479,   480,   482,   486, -1411,   198, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411,   488,   490, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,   222, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
     491, -1411, -1411, -1411, -1411, -1411, -1411,   240, -1411, -1411,
   -1411, -1411, -1411, -1411,   493, -1411,   494,   495, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411,   287, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411,   336,   430, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411,   492, -1411, -1411,
     497, -1411, -1411, -1411,   498, -1411, -1411,   496,   502, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411,   504,   505,   507, -1411, -1411, -1411, -1411, -1411,
     509,   512, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411,   290, -1411, -1411, -1411,
     508, -1411,   517, -1411,   520,   524, -1411, -1411, -1411, -1411,
   -1411,   294, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411,   527,   300, -1411, -1411, -1411, -1411,    43,    43,
   -1411,   302,   530, -1411, -1411,   533,   535,   536,   537,   540,
     541,   315,   316,   318,   320,   321,   326,   328,   329,   312,
     323,   330,   333,   337,   341,   547,   344,   345,   346,   348,
     351,   555,   558,   566,   355,   358,   339,   360,   571,   574,
     575,   356,   587,   591,   592,   593,   594,   595,   367,   368,
     369,   600,   603,   604,   605,   606,   609,   610,   611,   616,
     389,   621,   622,   623,   624,   627,   628,   629,   403,   404,
     405,   636,   638, -1411,   734, -1411,   639,   412,   415,   418,
     421,    37, -1411,   640,   647,   665,   666,   667,   442,   444,
     669,   672,   673,   675,   676,  1393, -1411,   677,   451,   183,
   -1411,   678,   453,   680,   454,   455,     2, -1411,   684,   685,
     686,   687,   688,   689,   690,   691, -1411,   121, -1411,   692,
     693,   470,   694,   695,   696,   474, -1411,   129,   697,   483,
     484,   487,   699, -1411,   140,   701,   702,   -60, -1411,   489,
     703,   481,   705,   499,   503,   710,   712,   204, -1411,   716,
     506,    62, -1411, -1411, -1411,   718,   717,   511,   719,   720,
     721,   722,   725, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411,   516, -1411, -1411,
   -1411, -1411, -1411,  -108,   519,   521, -1411, -1411, -1411, -1411,
     729,   731,   732, -1411,   522,   523,   284,   743,   744,   528,
   -1411, -1411, -1411,   753,   755,   756,   757,   758,   760,   761,
     764,   767, -1411,   768,   769,   762,   770,   771,   531,   548,
   -1411, -1411, -1411,   775,   774, -1411,   807, -1411, -1411, -1411,
   -1411, -1411,   808,   809,   584,   585,   586, -1411, -1411,   807,
     807,   807,   588,   811, -1411,   589, -1411, -1411,   590, -1411,
     596, -1411, -1411, -1411,   807,   807,   807,   807,   597,   598,
     601,   602, -1411,   607,   612, -1411,   613,   614,   625, -1411,
   -1411,   626, -1411, -1411, -1411,   807, -1411,   630,   744, -1411,
   -1411,   631, -1411,   632, -1411, -1411,   -46,   529, -1411,   821,
   -1411, -1411,    43,   734, -1411,    62,    37,   150,   150,   824,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,   827,
     828,   829, -1411, -1411, -1411, -1411, -1411, -1411, -1411,   830,
   -1411, -1411, -1411,   -99,    43,   324,   268,   834,   835,   846,
     262,    49,   -23,   195,   847,   144,   204, -1411, -1411,   851,
    -167, -1411, -1411,   852,   853, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411,   735, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,   824,
   -1411,   310,   313,   314, -1411, -1411, -1411, -1411,   861,   863,
     864,   865,   866,   867,   868,   870,   871,   873, -1411,   874,
     875, -1411, -1411, -1411, -1411, -1411,   340, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
     342, -1411,   876,   877, -1411, -1411,   878,   882, -1411, -1411,
     880,   884, -1411, -1411,   883,   885, -1411, -1411,   887,   891,
   -1411, -1411, -1411,    95, -1411, -1411, -1411,   889, -1411, -1411,
   -1411,   107, -1411, -1411, -1411, -1411, -1411,   343, -1411, -1411,
   -1411, -1411,   153, -1411, -1411,   892,   896, -1411, -1411,   894,
     898, -1411,   886,   899,   900,   901,   902,   903,   354, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,   904,   905,
     906, -1411, -1411, -1411, -1411,   364, -1411, -1411, -1411, -1411,
   -1411, -1411,   907,   908,   909, -1411,   395, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411,   910, -1411,   912, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411,   408, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411,   911,   915, -1411,   916,
   -1411,   917, -1411, -1411, -1411,   409, -1411, -1411, -1411, -1411,
   -1411,   410, -1411,   226, -1411,   918, -1411,   416, -1411, -1411,
     650, -1411,   919,   920, -1411, -1411,   921,   923, -1411, -1411,
     922,   925, -1411, -1411, -1411,   924,   928,   929,   930,   670,
     707,   711,   708,   713,   714,   715,   723,   724,   726,   940,
     727,   728,   944,   946,   947,   948,   150, -1411, -1411,   150,
   -1411,   824,  1393, -1411,   827,   129, -1411,   828,   140, -1411,
     829,  1491, -1411,   830,   -99, -1411, -1411,   324, -1411,   949,
     950,   268, -1411,   214,   834, -1411,   121, -1411,   835,   -70,
   -1411,   846,   730,   736,   737,   738,   739,   740,   262, -1411,
     953,   955,   741,   742,   745,    49, -1411,   733,   746,   747,
     -23, -1411,   959,   960,   962,   748,   971,   749,   972,   195,
   -1411,   195, -1411,   847,   750,   977,   754,   978,   144, -1411,
   -1411,   173,   851, -1411,   751,  -167, -1411, -1411,   981,   926,
     183, -1411,   852,     2, -1411,   853, -1411, -1411,   759,   765,
     778,   780, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411,   172, -1411, -1411,   788,   790,   791,   793, -1411,
     419, -1411,   420, -1411,   980, -1411,   984, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,   422,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,   794,   799,
   -1411, -1411, -1411,   985,   989, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411,   987,   995, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411,   991, -1411,   426, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411,    39,   800, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411,   203,   801,   804, -1411,
     994, -1411,   997, -1411,   428, -1411, -1411,   806, -1411,    43,
   -1411, -1411,  1002, -1411, -1411, -1411, -1411, -1411,   429, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411,   812,   439, -1411,
     440, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,  1491, -1411,
   -1411, -1411,  1034,  1036,   817,   819, -1411,   214, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411,    63,  1038, -1411, -1411, -1411,  1042,   833,  1055,   173,
   -1411, -1411, -1411, -1411, -1411,   831,   836, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411,   441, -1411, -1411,
   -1411, -1411, -1411, -1411,  1065,  1058, -1411,  1073, -1411,   850,
   -1411, -1411, -1411,  1084,  1086,  1095,  1098,    63, -1411,   209,
   -1411,  1038,  1113, -1411,   752,   927,   933,  1149, -1411, -1411,
   -1411, -1411, -1411, -1411,   443, -1411, -1411, -1411, -1411,   241,
   -1411, -1411, -1411, -1411, -1411,  1150,  1155,   209, -1411,   122,
    1113, -1411, -1411,  1160,  1167, -1411,   941, -1411, -1411,  1169,
    1170,  1171, -1411,   447, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411,    94, -1411,  1150, -1411,  1172,   937,   945,   951,  1174,
     122, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,   449,
   -1411, -1411, -1411, -1411,   954, -1411, -1411, -1411,   956, -1411,
    1175,  1176,    94, -1411, -1411, -1411,   957,   958, -1411, -1411,
   -1411
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   199,     9,   385,    11,
     601,    13,   632,    15,   667,    17,   516,    19,   525,    21,
     564,    23,   347,    25,   882,    27,   914,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   669,     0,   527,   566,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   141,   912,   197,   218,   220,   222,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   187,     0,     0,     0,     0,     0,   160,   167,
     169,     0,     0,     0,     0,   376,   514,   555,     0,   190,
     192,   173,   457,   619,   621,     0,     0,     0,   303,   322,
     312,   292,   705,   658,   338,   359,   739,     0,   324,   764,
     766,   863,   880,   180,   182,     0,     0,     0,   924,   966,
       0,   140,     0,    69,    72,    73,    74,    75,    76,    77,
      78,    79,    80,   111,   112,   113,   114,   115,    81,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   117,
     118,   129,   130,   131,   107,   137,   138,   139,   133,   134,
     135,    84,    85,    86,    87,   104,    88,    90,    89,   132,
      94,    95,    82,   108,   109,   110,    83,    92,    93,   102,
     103,   105,    91,    96,    97,    98,    99,   100,   101,   106,
     116,   136,   212,     0,     0,     0,     0,   211,     0,   201,
     204,   205,   206,   207,   208,   209,   210,   592,   623,   438,
     440,   442,     0,     0,   446,   448,   450,   444,   702,   437,
     390,   391,   392,   393,   394,   395,   396,   397,   417,   418,
     419,   420,   421,   424,   425,   426,   427,   428,   429,   430,
     431,   432,   433,   422,   423,   434,   435,   436,     0,   387,
     401,   402,   403,   406,   407,   408,   409,   411,   412,   413,
     404,   405,   398,   399,   415,   416,   400,   410,   414,   616,
       0,   615,   609,   610,   611,   612,   608,     0,   603,   606,
     607,   613,   614,   651,     0,   654,     0,     0,   650,   642,
     643,   644,   645,   641,   640,   648,   649,     0,   634,   637,
     638,   646,   647,   639,   700,   686,   688,   690,   692,   694,
     696,   698,   685,   682,   683,   684,     0,   670,   671,   676,
     677,   678,   674,   679,   680,   681,   675,     0,   545,   266,
       0,   549,   547,   552,     0,   541,   542,     0,   528,   529,
     532,   544,   533,   534,   535,   551,   536,   537,   538,   539,
     540,   583,     0,     0,     0,   590,   581,   582,   585,   586,
       0,   567,   568,   571,   572,   573,   574,   575,   576,   577,
     580,   578,   579,   355,   357,   352,     0,   349,   353,   354,
       0,   899,     0,   902,     0,     0,   906,   910,   897,   895,
     896,     0,   884,   887,   888,   889,   890,   891,   892,   893,
     894,   921,     0,     0,   916,   919,   920,    47,    52,     0,
      39,    45,     0,    66,    62,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    60,    71,    68,     0,     0,     0,     0,
       0,   203,   200,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   389,   386,     0,     0,   605,
     602,     0,     0,     0,     0,     0,   636,   633,     0,     0,
       0,     0,     0,     0,     0,     0,   668,   673,   517,     0,
       0,     0,     0,     0,     0,     0,   526,   531,     0,     0,
       0,     0,     0,   565,   570,     0,     0,   351,   348,     0,
       0,     0,     0,     0,     0,     0,     0,   886,   883,     0,
       0,   918,   915,    51,    43,     0,     0,     0,     0,     0,
       0,     0,     0,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,     0,   185,   186,
     157,   158,   159,     0,     0,     0,   171,   172,   179,   184,
       0,     0,     0,   189,     0,     0,     0,     0,     0,     0,
     452,   453,   454,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   763,     0,     0,     0,     0,     0,     0,     0,
     194,   195,   196,     0,     0,    70,     0,   214,   215,   216,
     217,   202,     0,     0,     0,     0,     0,   455,   456,     0,
       0,     0,     0,     0,   388,     0,   618,   604,     0,   653,
       0,   656,   657,   635,     0,     0,     0,     0,     0,     0,
       0,     0,   672,     0,     0,   543,     0,     0,     0,   554,
     530,     0,   587,   588,   589,     0,   569,     0,     0,   350,
     898,     0,   901,     0,   904,   905,     0,     0,   885,     0,
     923,   917,     0,     0,   142,     0,     0,     0,     0,   224,
     188,   162,   163,   164,   165,   166,   161,   168,   170,   378,
     518,   557,   191,   193,   175,   176,   177,   178,   174,   459,
      40,   620,   622,     0,    48,     0,     0,     0,   660,   340,
       0,     0,     0,     0,   768,     0,     0,   181,   183,     0,
       0,    53,   213,   594,   625,   439,   441,   443,   447,   449,
     451,   445,     0,   617,   652,   655,   701,   687,   689,   691,
     693,   695,   697,   699,   546,   267,   550,   548,   553,   584,
     591,   356,   358,   900,   903,   908,   909,   907,   911,   224,
      44,     0,     0,     0,   257,   259,   261,   263,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   276,     0,
       0,   284,   286,   288,   290,   256,     0,   231,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   248,   249,   250,   251,   247,   252,   253,   254,   255,
       0,   229,     0,   225,   226,   383,     0,   379,   380,   523,
       0,   519,   520,   562,     0,   558,   559,   464,     0,   460,
     461,   310,   311,     0,   305,   308,   309,     0,   320,   321,
     317,     0,   314,   318,   319,   299,   301,     0,   294,   297,
     298,   710,     0,   707,   665,     0,   661,   662,   345,     0,
     341,   342,     0,     0,     0,     0,     0,     0,     0,   361,
     364,   365,   366,   367,   368,   369,   753,   759,     0,     0,
       0,   752,   749,   750,   751,     0,   741,   744,   747,   745,
     746,   748,     0,     0,     0,   334,     0,   326,   329,   330,
     331,   332,   333,   791,   796,   798,     0,   821,     0,   802,
     790,   783,   784,   785,   788,   789,     0,   775,   778,   779,
     780,   781,   786,   787,   782,   773,     0,   769,   770,     0,
     875,     0,   878,   871,   872,     0,   865,   868,   869,   870,
     873,     0,   929,     0,   926,     0,   972,     0,   968,   971,
      55,   599,     0,   595,   596,   630,     0,   626,   627,   704,
       0,     0,    64,   913,   198,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   233,   219,   221,     0,
     223,   228,     0,   377,   382,   527,   515,   522,   566,   556,
     561,     0,   458,   463,   307,   304,   323,   316,   313,     0,
       0,   296,   293,   712,   709,   706,   669,   659,   664,     0,
     339,   344,     0,     0,     0,     0,     0,     0,   363,   360,
       0,     0,     0,     0,     0,   743,   740,     0,     0,     0,
     328,   325,     0,     0,     0,     0,     0,     0,     0,   777,
     765,     0,   767,   772,     0,     0,     0,     0,   867,   864,
     881,     0,   928,   925,     0,   970,   967,    57,     0,    56,
       0,   593,   598,     0,   624,   629,   703,   922,     0,     0,
       0,     0,   265,   268,   269,   270,   271,   272,   273,   274,
     283,   275,     0,   281,   282,     0,     0,     0,     0,   232,
       0,   227,     0,   381,     0,   521,     0,   560,   513,   484,
     485,   486,   488,   489,   490,   473,   474,   493,   494,   495,
     496,   497,   500,   501,   502,   503,   504,   505,   506,   507,
     508,   509,   498,   499,   510,   511,   512,   469,   470,   471,
     472,   480,   481,   482,   483,   477,   478,   479,   487,     0,
     466,   475,   491,   492,   476,   462,   306,   315,     0,     0,
     295,   733,   735,     0,     0,   731,   725,   726,   727,   728,
     729,   730,   732,   722,   723,   724,     0,   713,   714,   717,
     718,   719,   720,   721,   708,     0,   663,     0,   343,   370,
     371,   372,   373,   374,   375,   362,     0,     0,   758,   761,
     762,   742,   335,   336,   337,   327,     0,     0,     0,   800,
       0,   801,     0,   776,     0,   771,   874,     0,   877,     0,
     866,   944,     0,   942,   940,   934,   938,   939,     0,   931,
     936,   937,   935,   927,   973,   969,    54,    59,     0,   597,
       0,   628,   258,   260,   262,   264,   278,   279,   280,   277,
     285,   287,   289,   291,   230,   384,   524,   563,   468,   465,
     300,   302,     0,     0,     0,     0,   711,   716,   666,   346,
     755,   756,   757,   754,   760,   793,   794,   795,   792,   797,
     799,     0,   804,   774,   876,   879,     0,     0,     0,   933,
     930,    58,   600,   631,   467,     0,     0,   737,   738,   715,
     833,   836,   838,   840,   832,   831,   830,     0,   823,   826,
     827,   828,   829,   809,     0,   805,   806,     0,   941,     0,
     932,   734,   736,     0,     0,     0,     0,   825,   822,     0,
     803,   808,     0,   943,     0,     0,     0,     0,   824,   819,
     818,   814,   816,   817,     0,   811,   815,   807,   949,     0,
     946,   835,   834,   837,   839,   842,     0,   813,   810,     0,
     948,   945,   847,     0,   843,   844,     0,   812,   959,     0,
       0,     0,   964,     0,   951,   954,   955,   956,   957,   958,
     947,     0,   841,   846,   820,     0,     0,     0,     0,     0,
     953,   950,   859,   861,   858,   852,   854,   856,   857,     0,
     849,   853,   855,   845,     0,   961,   962,   963,     0,   952,
       0,     0,   851,   848,   960,   965,     0,     0,   850,   860,
     862
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411,   -10, -1411,  -606, -1411,
     456, -1411, -1411, -1411, -1411,   407, -1411,  -305, -1411, -1411,
   -1411,   -71, -1411, -1411, -1411, -1411, -1411, -1411, -1411,   448,
     658, -1411, -1411,     4,    12,    22,    38,    41,    42,   -57,
     -54,   -35,   -15,    20,    23,    45, -1411,    48,    55,    60,
      61, -1411, -1411,    66, -1411,    67, -1411,    71,    72,    73,
   -1411, -1411,    74,    77, -1411,    78, -1411,    79, -1411, -1411,
   -1411, -1411, -1411,    84, -1411,    85, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411,   446,   655, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,   361, -1411,
     132, -1411,  -727,   138, -1411, -1411, -1410, -1411, -1408, -1411,
   -1411, -1411, -1411,   -55, -1411,  -768, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,  -772,
   -1411,  -766, -1411,  -763, -1411, -1411, -1411, -1411, -1411, -1411,
     114, -1411, -1411, -1411, -1411, -1411, -1411, -1411,   123,  -753,
   -1411, -1411, -1411, -1411,   119, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411,    88, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
     108, -1411, -1411, -1411,   111,   615, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411,   103, -1411, -1411, -1411, -1411, -1411, -1411,
   -1046, -1411, -1411, -1411,   139, -1411, -1411, -1411,   142,   660,
   -1411, -1411, -1045, -1411, -1044, -1411,    25, -1411,    92, -1411,
      96, -1411,    98, -1411,    89,    90,    91, -1411, -1043, -1411,
   -1411, -1411, -1411,   133, -1411, -1411,  -121,  1131, -1411, -1411,
   -1411, -1411, -1411,   143, -1411, -1411, -1411,   146, -1411,   635,
   -1411,   -65, -1411, -1411, -1411, -1411, -1411,   -61, -1411, -1411,
   -1411, -1411, -1411,   -29, -1411, -1411, -1411,   145, -1411, -1411,
   -1411,   141, -1411,   633, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,    76, -1411,
   -1411, -1411,    82,   664, -1411, -1411,   -63,   -42, -1411,   -13,
   -1411, -1411, -1411, -1411, -1411,    69, -1411, -1411, -1411,    83,
     663, -1411, -1411, -1411, -1411, -1411, -1411, -1411,   -58, -1411,
   -1411, -1411,   135, -1411, -1411, -1411,   130, -1411,   653,   423,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1042, -1411, -1411, -1411, -1411,
   -1411,   137, -1411, -1411, -1411,  -113, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411,   124, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411,   104, -1411,   110,   115, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,  -173,
   -1411, -1411,  -197, -1411, -1411, -1411, -1411, -1411,  -160, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
    -220, -1411, -1411,  -242, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411,   116, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411,   457,   645, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411,   500,   646, -1411, -1411, -1411, -1411, -1411, -1411,   117,
   -1411, -1411,  -111, -1411, -1411, -1411, -1411, -1411, -1411,  -184,
   -1411, -1411,  -210, -1411, -1411, -1411, -1411, -1411, -1411, -1411,
   -1411, -1411, -1411,   118, -1411
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     771,    87,    88,    41,    68,    84,    85,   792,  1020,  1138,
    1139,   855,    43,    70,    90,   452,    91,    45,    71,   162,
     163,   164,   455,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   481,   756,   183,   482,   184,   483,   185,   186,   187,
     494,   768,   188,   189,   516,   190,   517,   191,   192,   193,
     194,   475,   195,   196,   492,   197,   493,   198,   199,   200,
     201,   457,    47,    72,   238,   239,   240,   526,   241,   242,
     243,   244,   202,   458,   203,   459,   204,   460,   882,   883,
     884,  1059,   856,   857,   858,  1035,   859,  1036,   860,  1037,
     861,  1038,   862,   863,   570,   864,   865,   866,   867,   868,
     869,   870,   871,   872,  1049,  1319,   873,   874,   875,   876,
    1052,   877,  1053,   878,  1054,   879,  1055,   205,   504,   917,
     918,   919,  1079,   920,  1080,   206,   501,   903,   904,   905,
     906,   207,   503,   911,   912,   913,   914,   208,   502,   209,
     511,   966,   967,   968,   969,   970,   210,   507,   929,   930,
     931,  1089,    63,    80,   416,   417,   418,   585,   419,   586,
     211,   508,   938,   939,   940,   941,   942,   943,   944,   945,
     212,   488,   886,   887,   888,  1062,    49,    73,   288,   289,
     290,   535,   291,   536,   292,   537,   293,   543,   294,   540,
     295,   541,   296,   542,   213,   214,   215,   300,   301,   216,
     495,   898,   899,   900,  1071,  1219,  1220,   217,   489,    57,
      77,   890,   891,   892,  1065,    59,    78,   377,   378,   379,
     380,   381,   382,   383,   569,   384,   573,   385,   572,   386,
     387,   574,   388,   218,   490,   894,   895,   896,  1068,    61,
      79,   400,   401,   402,   403,   404,   578,   405,   406,   407,
     408,   409,   410,   582,   303,   533,  1022,  1023,  1024,  1140,
      51,    74,   317,   318,   319,   547,   320,   219,   496,   220,
     497,   306,   534,  1026,  1027,  1028,  1143,    53,    75,   337,
     338,   339,   551,   340,   341,   553,   342,   343,   221,   506,
     925,   926,   927,  1086,    55,    76,   356,   357,   358,   359,
     559,   360,   560,   361,   561,   362,   562,   363,   563,   364,
     564,   365,   565,   366,   558,   308,   544,  1030,   222,   505,
     922,   923,  1083,  1246,  1247,  1248,  1249,  1250,  1332,  1251,
    1333,  1252,  1253,   223,   509,   955,   956,   957,  1100,  1343,
     958,   959,  1101,   960,   961,   224,   225,   512,   226,   513,
     996,   997,   998,  1121,   986,   987,   988,  1112,  1348,   989,
    1113,   990,  1114,   991,   992,   993,  1118,  1384,  1385,  1386,
    1399,  1414,  1415,  1416,  1426,   994,  1116,  1377,  1378,  1379,
    1393,  1422,  1380,  1394,  1381,  1395,  1382,  1396,  1433,  1434,
    1435,  1451,  1469,  1470,  1471,  1480,  1472,  1481,   227,   514,
    1005,  1006,  1007,  1008,  1125,  1009,  1010,  1127,   228,   515,
      65,    81,   431,   432,   433,   434,   590,   435,   436,   592,
     437,   438,   439,   595,   827,   440,   596,   229,   456,    67,
      82,   443,   444,   445,   599,   446,   230,   521,  1013,  1014,
    1131,  1298,  1299,  1300,  1301,  1358,  1302,  1356,  1419,  1420,
    1429,  1443,  1444,  1445,  1455,  1446,  1447,  1448,  1449,  1459,
     231,   522,  1017,  1018,  1019
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     161,   237,   259,   311,   328,   352,    38,   375,   396,   415,
     428,   981,   334,   952,   398,   307,   266,   982,   399,   267,
     983,   880,   910,   376,   397,  1208,  1209,  1210,  1218,  1224,
     245,   304,   321,   335,   354,   901,   389,   411,   268,   429,
      30,  1465,   770,  1466,   302,   316,   333,   353,    31,  1015,
      32,    42,    33,   232,   233,   234,   235,   236,   269,   246,
     305,   322,   336,   355,   160,   390,   412,    86,   430,    89,
     413,   414,  1465,   946,  1466,   441,   442,   260,   839,   127,
     413,   414,   133,   134,   126,   261,   447,  1370,    44,   751,
     752,   753,   754,   270,    46,   262,   271,   449,  1074,   312,
     329,  1075,   323,   324,   325,   326,   327,   133,   134,    48,
    1077,   263,   453,  1078,   264,   265,   448,   454,   272,   835,
     836,   273,   770,   254,   255,   256,   755,    50,   274,   451,
     257,   310,   902,   275,   276,    52,   962,   963,   964,   277,
     278,    54,   133,   134,   279,   280,   281,   282,   825,   826,
     283,   284,   285,   368,   133,   134,  1084,   286,   287,  1085,
     524,   160,   297,   298,   299,   525,   313,   330,   133,   134,
     314,   331,   315,   332,   834,   835,   836,   837,   838,   839,
     840,   841,   842,   843,   844,   845,   846,   847,   848,  1340,
    1341,  1342,   849,   850,   851,   852,   853,   854,   127,   133,
     134,   531,   947,   948,   949,   950,   532,   369,   160,   370,
     371,  1316,  1317,  1318,   372,   373,   374,    56,   369,   391,
     370,   371,   392,   393,   394,   545,   133,   134,   369,  1132,
     546,    58,  1133,   160,   133,   134,  1371,  1372,  1373,   851,
     852,   853,   344,   549,  1430,   133,   134,  1431,   550,   133,
     134,   369,   345,   346,   347,   348,   349,   350,   351,    60,
     127,   395,    98,    99,   100,   101,   102,   103,   160,   450,
    1462,  1463,    62,    64,    34,    35,    36,    37,   133,   134,
     160,   309,  1208,  1209,  1210,  1218,  1224,   369,   133,   134,
     556,   127,   369,   587,   160,   557,    66,   597,   588,   461,
     133,   134,   598,   601,   254,   255,   256,   462,   602,   133,
     134,   257,   310,   524,   133,   134,   601,   531,  1032,   133,
     134,  1033,  1034,   463,   910,   160,   999,  1000,  1001,   464,
    1438,   465,  1170,  1439,  1440,  1441,  1442,   952,  1231,  1232,
    1233,  1234,   466,  1056,   566,  1056,  1081,   981,  1057,   981,
    1058,  1082,   160,   982,   467,   982,   983,  1098,   983,   973,
     160,   468,  1099,   974,   975,   976,   977,  1105,  1345,  1346,
    1347,   160,  1106,   978,   979,  1002,   764,   765,   766,   767,
    1291,   160,  1292,  1293,   798,   799,   800,   915,   916,  1409,
     420,   421,   422,   423,   424,   425,   426,   427,  1110,   806,
     807,   808,   809,  1111,   160,   932,   933,   934,   935,   936,
     937,  1119,  1128,   597,   160,   469,  1120,  1129,  1130,  1135,
     820,   470,  1056,   545,  1136,  1328,   160,  1324,  1325,   587,
    1329,  1119,  1359,   567,  1339,   160,  1353,  1360,   603,   604,
     160,   471,   549,   556,  1397,   160,  1427,  1362,  1363,  1398,
    1460,  1428,  1482,   161,   472,  1461,   473,  1483,   901,   908,
     237,   909,   474,   476,   477,   478,   479,   480,   484,   485,
     486,   487,   491,   498,   259,   499,   500,   510,   311,   518,
     519,   520,   523,   527,   528,   328,   529,   307,   266,   245,
     530,   267,   538,   334,   539,   548,   352,   552,   554,   555,
     568,   571,   575,   304,   576,   577,   375,   321,   579,   580,
     268,   581,   589,   396,   335,   584,   302,   583,   246,   398,
     316,   591,   376,   399,   593,   354,   428,   333,   594,   397,
     269,   600,   305,   605,   606,   389,   322,   607,   353,   608,
     609,   610,   411,   336,   611,   612,   621,   613,   614,   260,
     615,   627,   616,   617,   355,   429,   622,   261,   618,   633,
     619,   620,   634,   623,   390,   270,   624,   262,   271,   625,
     635,   412,   638,   626,   312,   640,   628,   629,   641,   642,
     630,   329,   631,   263,   430,   632,   264,   265,   643,   636,
     272,   644,   637,   273,   639,   645,   646,   647,   648,   649,
     274,   650,   651,   652,   653,   275,   276,   654,   655,   656,
     657,   277,   278,   658,   659,   660,   279,   280,   281,   282,
     661,   662,   283,   284,   285,   663,   664,   665,   666,   286,
     287,   667,   668,   669,   297,   298,   299,   670,   671,   672,
     673,   313,   674,   676,   682,   314,   677,   315,   330,   678,
     679,   683,   331,   680,   332,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,   684,
     685,   686,   161,   689,   687,   237,   690,   691,   688,   692,
     693,   695,   698,   696,   700,   699,   701,   702,   704,   705,
     706,   707,   708,   709,   710,   711,   713,   714,   716,   717,
     718,   721,   715,   725,   245,   727,   728,   731,   719,   733,
     951,   965,   980,   732,   736,   428,   737,   722,   723,  1016,
     739,   724,   742,   730,   743,   828,   745,   746,   747,   748,
     749,   734,   830,   246,   759,   735,   760,   761,   740,   953,
     971,   984,   744,  1003,   429,    92,    93,   750,   769,    94,
     757,    32,   758,   762,   763,    95,    96,    97,   773,   772,
     774,   775,   787,   777,   776,   778,   779,   784,   954,   972,
     985,   780,  1004,   430,   781,   782,   783,   785,   786,   788,
     789,   790,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   791,   793,   794,   795,   796,   797,   802,   801,
     803,   804,   128,   129,   130,   131,   829,   805,   810,   811,
     132,   881,   812,   813,   885,   889,   893,   897,   814,   133,
     134,   921,   924,   815,   816,   817,   135,   136,   137,   138,
     139,   140,   141,   928,   995,   142,   818,   819,  1012,  1021,
    1025,   821,   823,   824,   143,  1039,   345,  1040,  1041,  1042,
    1043,  1044,  1045,   144,  1046,  1047,   145,  1048,  1050,  1051,
    1061,  1137,  1060,   146,  1063,  1064,  1066,  1067,  1070,  1069,
    1092,   147,   148,  1072,  1073,  1076,   149,   150,  1087,  1088,
    1090,  1091,  1152,  1093,  1094,  1095,  1096,  1097,  1102,  1103,
    1104,  1107,  1108,  1109,  1115,   151,  1117,  1122,  1123,   152,
    1124,  1126,  1134,  1142,  1421,  1141,  1145,  1144,  1148,  1307,
    1146,  1147,  1149,  1150,  1151,   153,   154,   155,   156,   157,
     158,  1153,  1155,  1154,  1162,  1156,  1157,  1158,  1165,   159,
    1166,  1167,  1168,  1228,  1229,  1159,  1160,  1266,  1161,  1267,
    1164,  1163,  1259,  1276,  1277,   160,  1278,  1272,  1260,  1261,
    1262,  1263,  1264,  1268,  1269,  1280,  1282,  1270,  1273,  1274,
    1279,  1287,  1289,  1281,  1286,  1304,  1288,  1306,  1326,  1334,
    1312,   259,  1327,  1335,   375,  1336,  1313,   396,  1337,  1338,
    1178,  1351,  1352,   398,   307,   266,  1357,   399,   267,  1314,
     376,  1315,  1235,   397,  1185,   352,  1207,  1186,   415,  1320,
     304,  1321,  1322,   389,  1323,  1330,   411,   268,  1242,  1222,
    1331,  1344,  1349,   302,   951,  1350,  1187,  1354,  1365,   965,
    1366,  1244,  1221,  1361,   354,  1383,  1387,   269,   980,   305,
     980,  1367,   390,  1368,  1243,   412,  1188,   353,  1223,  1389,
    1294,  1401,  1391,   953,  1016,  1388,   260,  1392,   971,   311,
    1245,  1400,   328,   355,   261,  1179,  1295,   984,  1402,   984,
     334,  1403,   270,  1180,   262,   271,  1003,  1236,  1404,  1296,
    1405,  1189,   954,  1181,  1190,  1237,  1211,   972,   321,  1406,
     263,   335,  1407,   264,   265,  1238,   985,   272,   985,  1182,
     273,   316,  1183,  1184,   333,  1004,  1191,   274,  1297,  1192,
    1418,  1239,   275,   276,  1240,  1241,  1193,   322,   277,   278,
     336,  1194,  1195,   279,   280,   281,   282,  1196,  1197,   283,
     284,   285,  1198,  1199,  1200,  1201,   286,   287,  1202,  1203,
    1204,   297,   298,   299,  1425,  1205,  1206,  1432,  1423,  1436,
    1215,  1216,  1217,  1212,  1424,   312,  1452,  1213,   329,  1214,
    1453,  1475,  1454,  1456,  1457,  1458,  1474,  1476,  1478,  1486,
    1487,   907,   675,  1477,   822,  1484,   681,  1485,  1489,  1490,
    1031,   831,   833,  1171,  1169,  1230,  1227,  1226,  1275,  1258,
    1257,  1265,   729,  1173,  1172,   694,  1225,  1364,   367,  1176,
    1175,  1174,   720,   697,  1311,  1177,  1255,   726,  1309,   703,
     712,  1254,  1308,  1256,  1369,  1029,  1310,  1285,  1417,  1271,
    1437,  1284,   313,  1473,  1283,   330,   314,  1408,   315,   331,
    1488,   332,   738,  1011,  1290,   832,  1450,   741,  1390,  1303,
    1479,     0,     0,  1305,     0,     0,     0,  1178,     0,     0,
       0,     0,     0,     0,     0,     0,  1235,     0,     0,     0,
       0,  1185,     0,  1207,  1186,     0,     0,     0,     0,  1355,
    1374,     0,  1242,     0,     0,     0,  1222,     0,  1294,     0,
       0,     0,     0,  1187,     0,  1244,     0,     0,     0,  1221,
       0,     0,     0,     0,  1295,     0,     0,     0,  1243,  1375,
       0,     0,     0,  1188,     0,  1223,     0,  1296,     0,     0,
       0,     0,     0,     0,  1245,     0,  1374,     0,  1410,     0,
       0,     0,  1179,     0,     0,     0,     0,     0,  1376,     0,
    1180,  1236,     0,     0,  1411,     0,  1297,     0,  1189,  1237,
    1181,  1190,     0,  1211,     0,  1375,  1410,  1412,     0,  1238,
       0,     0,     0,     0,     0,     0,  1182,     0,     0,  1183,
    1184,     0,  1411,  1191,     0,  1239,  1192,     0,  1240,  1241,
    1464,     0,     0,  1193,  1376,  1412,  1413,     0,  1194,  1195,
       0,     0,     0,     0,  1196,  1197,     0,     0,     0,  1198,
    1199,  1200,  1201,     0,     0,  1202,  1203,  1204,     0,  1467,
       0,  1464,  1205,  1206,  1413,     0,     0,  1215,  1216,  1217,
    1212,     0,     0,     0,  1213,     0,  1214,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1468,     0,
    1467,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,     0,     0,     0,     0,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,     0,  1468,
     127,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   129,   130,   131,     0,     0,     0,     0,     0,
     247,     0,   248,     0,     0,     0,     0,     0,   133,   134,
     249,   250,   251,   252,   253,   135,   136,   137,     0,     0,
       0,     0,     0,     0,   254,   255,   256,     0,     0,     0,
       0,   257,     0,   143,     0,     0,     0,     0,     0,     0,
       0,   258,     0,     0,     0,     0,     0,     0,     0,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,     0,     0,     0,     0,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,     0,   127,   369,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     129,   130,   131,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   153,   154,   133,   134,     0,   250,
     251,     0,   253,   135,   136,   137,     0,     0,     0,     0,
       0,     0,   254,   255,   256,     0,     0,     0,     0,   257,
       0,     0,     0,     0,   160,     0,     0,     0,     0,   258,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   153,   154,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   160
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   783,    75,   781,    79,    73,    73,   783,    79,    73,
     783,   748,   775,    78,    79,  1071,  1071,  1071,  1071,  1071,
      72,    73,    74,    75,    76,   134,    78,    79,    73,    81,
       0,  1451,   648,  1451,    73,    74,    75,    76,     5,   216,
       7,     7,     9,    16,    17,    18,    19,    20,    73,    72,
      73,    74,    75,    76,   231,    78,    79,   231,    81,    10,
     140,   141,  1482,    24,  1482,    13,    14,    73,    29,    77,
     140,   141,   105,   106,    76,    73,     6,    24,     7,   197,
     198,   199,   200,    73,     7,    73,    73,     4,     3,    74,
      75,     6,   100,   101,   102,   103,   104,   105,   106,     7,
       3,    73,     3,     6,    73,    73,     3,     8,    73,    25,
      26,    73,   728,   121,   122,   123,   234,     7,    73,     3,
     128,   129,   231,    73,    73,     7,   159,   160,   161,    73,
      73,     7,   105,   106,    73,    73,    73,    73,   194,   195,
      73,    73,    73,    24,   105,   106,     3,    73,    73,     6,
       3,   231,    73,    73,    73,     8,    74,    75,   105,   106,
      74,    75,    74,    75,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,   150,
     151,   152,    42,    43,    44,    45,    46,    47,    77,   105,
     106,     3,   153,   154,   155,   156,     8,    78,   231,    80,
      81,    39,    40,    41,    85,    86,    87,     7,    78,    79,
      80,    81,    82,    83,    84,     3,   105,   106,    78,     3,
       8,     7,     6,   231,   105,   106,   173,   174,   175,    44,
      45,    46,   121,     3,     3,   105,   106,     6,     8,   105,
     106,    78,   131,   132,   133,   134,   135,   136,   137,     7,
      77,   121,    48,    49,    50,    51,    52,    53,   231,     8,
     176,   177,     7,     7,   231,   232,   233,   234,   105,   106,
     231,    98,  1328,  1328,  1328,  1328,  1328,    78,   105,   106,
       3,    77,    78,     3,   231,     8,     7,     3,     8,     4,
     105,   106,     8,     3,   121,   122,   123,     4,     8,   105,
     106,   128,   129,     3,   105,   106,     3,     3,     8,   105,
     106,     8,     8,     4,  1077,   231,   182,   183,   184,     4,
     208,     4,  1059,   211,   212,   213,   214,  1105,   124,   125,
     126,   127,     4,     3,     8,     3,     3,  1119,     8,  1121,
       8,     8,   231,  1119,     4,  1121,  1119,     3,  1121,   164,
     231,     4,     8,   168,   169,   170,   171,     3,   165,   166,
     167,   231,     8,   178,   179,   231,    92,    93,    94,    95,
     207,   231,   209,   210,   689,   690,   691,   119,   120,   180,
     186,   187,   188,   189,   190,   191,   192,   193,     3,   704,
     705,   706,   707,     8,   231,   143,   144,   145,   146,   147,
     148,     3,     3,     3,   231,     4,     8,     8,     8,     3,
     725,     4,     3,     3,     8,     3,   231,     8,     8,     3,
       8,     3,     3,     3,     8,   231,     8,     8,   448,   449,
     231,     4,     3,     3,     3,   231,     3,     8,     8,     8,
       3,     8,     3,   524,     4,     8,     4,     8,   134,   135,
     531,   137,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   545,     4,     4,     4,   549,     4,
       4,     4,     4,     4,     4,   556,     4,   545,   545,   531,
       4,   545,     4,   556,     4,     4,   567,     4,     4,     4,
       8,     4,     4,   545,     8,     3,   577,   549,     4,     4,
     545,     4,     4,   584,   556,     3,   545,     8,   531,   584,
     549,     4,   577,   584,     4,   567,   597,   556,     4,   584,
     545,     4,   545,   231,     4,   577,   549,     4,   567,     4,
       4,     4,   584,   556,     4,     4,   234,   232,   232,   545,
     232,     4,   232,   232,   567,   597,   233,   545,   232,     4,
     232,   232,     4,   233,   577,   545,   233,   545,   545,   232,
       4,   584,   233,   232,   549,     4,   232,   232,     4,     4,
     234,   556,   234,   545,   597,   234,   545,   545,   232,   234,
     545,     4,   234,   545,   234,     4,     4,     4,     4,     4,
     545,   234,   234,   234,     4,   545,   545,     4,     4,     4,
       4,   545,   545,     4,     4,     4,   545,   545,   545,   545,
       4,   232,   545,   545,   545,     4,     4,     4,     4,   545,
     545,     4,     4,     4,   545,   545,   545,   234,   234,   234,
       4,   549,     4,     4,     4,   549,   234,   549,   556,   234,
     232,     4,   556,   232,   556,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,     4,
       4,     4,   743,     4,   232,   746,     4,     4,   234,     4,
       4,     4,     4,   232,     4,   232,   232,   232,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   232,     4,   746,     4,     4,     4,   234,     4,
     781,   782,   783,   232,     4,   786,     4,   234,   234,   790,
       4,   234,     4,   234,     7,   196,     7,     7,     7,     7,
       5,   232,   742,   746,     5,   232,     5,     5,   232,   781,
     782,   783,   231,   785,   786,    11,    12,   231,     5,    15,
     231,     7,   231,   231,   231,    21,    22,    23,     5,   231,
       5,     5,   231,     5,     7,     5,     5,     5,   781,   782,
     783,     7,   785,   786,     7,     7,     7,     7,     7,   231,
       5,     7,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,     5,     5,     5,   231,   231,   231,     7,   231,
     231,   231,    88,    89,    90,    91,     5,   231,   231,   231,
      96,     7,   231,   231,     7,     7,     7,     7,   231,   105,
     106,     7,     7,   231,   231,   231,   112,   113,   114,   115,
     116,   117,   118,     7,     7,   121,   231,   231,     7,     7,
       7,   231,   231,   231,   130,     4,   131,     4,     4,     4,
       4,     4,     4,   139,     4,     4,   142,     4,     4,     4,
       3,   231,     6,   149,     6,     3,     6,     3,     3,     6,
       4,   157,   158,     6,     3,     6,   162,   163,     6,     3,
       6,     3,   232,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   181,     4,     6,     3,   185,
       4,     4,     4,     3,   172,     6,     3,     6,     4,     3,
       8,     6,     4,     4,     4,   201,   202,   203,   204,   205,
     206,   234,   234,   232,     4,   232,   232,   232,     4,   215,
       4,     4,     4,     4,     4,   232,   232,     4,   232,     4,
     232,   234,   232,     4,     4,   231,     4,   234,   232,   232,
     232,   232,   232,   232,   232,     4,     4,   232,   232,   232,
     232,     4,     4,   234,   234,   234,   232,     6,     8,     4,
     231,  1062,     8,     4,  1065,     8,   231,  1068,     3,     8,
    1071,     7,     5,  1068,  1062,  1062,     4,  1068,  1062,   231,
    1065,   231,  1083,  1068,  1071,  1086,  1071,  1071,  1089,   231,
    1062,   231,   231,  1065,   231,   231,  1068,  1062,  1083,  1071,
     231,   231,   231,  1062,  1105,   231,  1071,   231,     4,  1110,
       4,  1083,  1071,   231,  1086,     7,     4,  1062,  1119,  1062,
    1121,   234,  1065,   234,  1083,  1068,  1071,  1086,  1071,     4,
    1131,     3,   231,  1105,  1135,   232,  1062,   231,  1110,  1140,
    1083,     6,  1143,  1086,  1062,  1071,  1131,  1119,     5,  1121,
    1143,   231,  1062,  1071,  1062,  1062,  1128,  1083,     4,  1131,
       4,  1071,  1105,  1071,  1071,  1083,  1071,  1110,  1140,     4,
    1062,  1143,     4,  1062,  1062,  1083,  1119,  1062,  1121,  1071,
    1062,  1140,  1071,  1071,  1143,  1128,  1071,  1062,  1131,  1071,
       7,  1083,  1062,  1062,  1083,  1083,  1071,  1140,  1062,  1062,
    1143,  1071,  1071,  1062,  1062,  1062,  1062,  1071,  1071,  1062,
    1062,  1062,  1071,  1071,  1071,  1071,  1062,  1062,  1071,  1071,
    1071,  1062,  1062,  1062,     5,  1071,  1071,     7,   231,     4,
    1071,  1071,  1071,  1071,   231,  1140,     6,  1071,  1143,  1071,
       3,   234,   231,     4,     4,     4,     4,   232,     4,     4,
       4,   774,   524,   232,   728,   231,   531,   231,   231,   231,
     829,   743,   746,  1061,  1056,  1081,  1077,  1074,  1110,  1091,
    1089,  1098,   587,  1064,  1062,   545,  1073,  1328,    77,  1068,
    1067,  1065,   577,   549,  1145,  1070,  1086,   584,  1142,   556,
     567,  1084,  1140,  1088,  1337,   802,  1143,  1123,  1401,  1105,
    1427,  1121,  1140,  1453,  1119,  1143,  1140,  1397,  1140,  1143,
    1482,  1143,   597,   786,  1128,   745,  1430,   601,  1359,  1132,
    1460,    -1,    -1,  1135,    -1,    -1,    -1,  1328,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1337,    -1,    -1,    -1,
      -1,  1328,    -1,  1328,  1328,    -1,    -1,    -1,    -1,  1289,
    1351,    -1,  1337,    -1,    -1,    -1,  1328,    -1,  1359,    -1,
      -1,    -1,    -1,  1328,    -1,  1337,    -1,    -1,    -1,  1328,
      -1,    -1,    -1,    -1,  1359,    -1,    -1,    -1,  1337,  1351,
      -1,    -1,    -1,  1328,    -1,  1328,    -1,  1359,    -1,    -1,
      -1,    -1,    -1,    -1,  1337,    -1,  1397,    -1,  1399,    -1,
      -1,    -1,  1328,    -1,    -1,    -1,    -1,    -1,  1351,    -1,
    1328,  1337,    -1,    -1,  1399,    -1,  1359,    -1,  1328,  1337,
    1328,  1328,    -1,  1328,    -1,  1397,  1427,  1399,    -1,  1337,
      -1,    -1,    -1,    -1,    -1,    -1,  1328,    -1,    -1,  1328,
    1328,    -1,  1427,  1328,    -1,  1337,  1328,    -1,  1337,  1337,
    1451,    -1,    -1,  1328,  1397,  1427,  1399,    -1,  1328,  1328,
      -1,    -1,    -1,    -1,  1328,  1328,    -1,    -1,    -1,  1328,
    1328,  1328,  1328,    -1,    -1,  1328,  1328,  1328,    -1,  1451,
      -1,  1482,  1328,  1328,  1427,    -1,    -1,  1328,  1328,  1328,
    1328,    -1,    -1,    -1,  1328,    -1,  1328,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1451,    -1,
    1482,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    -1,  1482,
      77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    90,    91,    -1,    -1,    -1,    -1,    -1,
      97,    -1,    99,    -1,    -1,    -1,    -1,    -1,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,    -1,    -1,
      -1,    -1,    -1,    -1,   121,   122,   123,    -1,    -1,    -1,
      -1,   128,    -1,   130,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   138,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    -1,    77,    78,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    90,    91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   201,   202,   105,   106,    -1,   108,
     109,    -1,   111,   112,   113,   114,    -1,    -1,    -1,    -1,
      -1,    -1,   121,   122,   123,    -1,    -1,    -1,    -1,   128,
      -1,    -1,    -1,    -1,   231,    -1,    -1,    -1,    -1,   138,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   201,   202,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   231
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
       0,     5,     7,     9,   231,   232,   233,   234,   251,   252,
     253,   258,     7,   267,     7,   272,     7,   327,     7,   441,
       7,   525,     7,   542,     7,   559,     7,   474,     7,   480,
       7,   504,     7,   417,     7,   675,     7,   694,   259,   254,
     268,   273,   328,   442,   526,   543,   560,   475,   481,   505,
     418,   676,   695,   251,   260,   261,   231,   256,   257,    10,
     269,   271,    11,    12,    15,    21,    22,    23,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    88,    89,
      90,    91,    96,   105,   106,   112,   113,   114,   115,   116,
     117,   118,   121,   130,   139,   142,   149,   157,   158,   162,
     163,   181,   185,   201,   202,   203,   204,   205,   206,   215,
     231,   266,   274,   275,   276,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   298,   300,   302,   303,   304,   307,   308,
     310,   312,   313,   314,   315,   317,   318,   320,   322,   323,
     324,   325,   337,   339,   341,   382,   390,   396,   402,   404,
     411,   425,   435,   459,   460,   461,   464,   472,   498,   532,
     534,   553,   583,   598,   610,   611,   613,   663,   673,   692,
     701,   725,    16,    17,    18,    19,    20,   266,   329,   330,
     331,   333,   334,   335,   336,   532,   534,    97,    99,   107,
     108,   109,   110,   111,   121,   122,   123,   128,   138,   266,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   292,   293,   294,   295,   298,   300,   302,
     303,   304,   307,   308,   310,   312,   318,   320,   443,   444,
     445,   447,   449,   451,   453,   455,   457,   459,   460,   461,
     462,   463,   498,   519,   532,   534,   536,   553,   580,    98,
     129,   266,   451,   453,   455,   457,   498,   527,   528,   529,
     531,   532,   534,   100,   101,   102,   103,   104,   266,   451,
     453,   455,   457,   498,   531,   532,   534,   544,   545,   546,
     548,   549,   551,   552,   121,   131,   132,   133,   134,   135,
     136,   137,   266,   498,   532,   534,   561,   562,   563,   564,
     566,   568,   570,   572,   574,   576,   578,   472,    24,    78,
      80,    81,    85,    86,    87,   266,   358,   482,   483,   484,
     485,   486,   487,   488,   490,   492,   494,   495,   497,   532,
     534,    79,    82,    83,    84,   121,   266,   358,   486,   492,
     506,   507,   508,   509,   510,   512,   513,   514,   515,   516,
     517,   532,   534,   140,   141,   266,   419,   420,   421,   423,
     186,   187,   188,   189,   190,   191,   192,   193,   266,   532,
     534,   677,   678,   679,   680,   682,   683,   685,   686,   687,
     690,    13,    14,   696,   697,   698,   700,     6,     3,     4,
       8,     3,   270,     3,     8,   277,   693,   326,   338,   340,
     342,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   316,     4,     4,     4,     4,
       4,   296,   299,   301,     4,     4,     4,     4,   436,   473,
     499,     4,   319,   321,   305,   465,   533,   535,     4,     4,
       4,   391,   403,   397,   383,   584,   554,   412,   426,   599,
       4,   405,   612,   614,   664,   674,   309,   311,     4,     4,
       4,   702,   726,     4,     3,     8,   332,     4,     4,     4,
       4,     3,     8,   520,   537,   446,   448,   450,     4,     4,
     454,   456,   458,   452,   581,     3,     8,   530,     4,     3,
       8,   547,     4,   550,     4,     4,     3,     8,   579,   565,
     567,   569,   571,   573,   575,   577,     8,     3,     8,   489,
     359,     4,   493,   491,   496,     4,     8,     3,   511,     4,
       4,     4,   518,     8,     3,   422,   424,     3,     8,     4,
     681,     4,   684,     4,     4,   688,   691,     3,     8,   699,
       4,     3,     8,   251,   251,   231,     4,     4,     4,     4,
       4,     4,     4,   232,   232,   232,   232,   232,   232,   232,
     232,   234,   233,   233,   233,   232,   232,     4,   232,   232,
     234,   234,   234,     4,     4,     4,   234,   234,   233,   234,
       4,     4,     4,   232,     4,     4,     4,     4,     4,     4,
     234,   234,   234,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   232,     4,     4,     4,     4,     4,     4,     4,
     234,   234,   234,     4,     4,   275,     4,   234,   234,   232,
     232,   330,     4,     4,     4,     4,     4,   232,   234,     4,
       4,     4,     4,     4,   444,     4,   232,   528,     4,   232,
       4,   232,   232,   545,     4,     4,     4,     4,     4,     4,
       4,     4,   563,     4,     4,   232,     4,     4,     4,   234,
     484,     4,   234,   234,   234,     4,   508,     4,     4,   420,
     234,     4,   232,     4,   232,   232,     4,     4,   678,     4,
     232,   697,     4,     7,   231,     7,     7,     7,     7,     5,
     231,   197,   198,   199,   200,   234,   297,   231,   231,     5,
       5,     5,   231,   231,    92,    93,    94,    95,   306,     5,
     253,   255,   231,     5,     5,     5,     7,     5,     5,     5,
       7,     7,     7,     7,     5,     7,     7,   231,   231,     5,
       7,     5,   262,     5,     5,   231,   231,   231,   262,   262,
     262,   231,     7,   231,   231,   231,   262,   262,   262,   262,
     231,   231,   231,   231,   231,   231,   231,   231,   231,   231,
     262,   231,   255,   231,   231,   194,   195,   689,   196,     5,
     251,   274,   696,   329,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    42,
      43,    44,    45,    46,    47,   266,   347,   348,   349,   351,
     353,   355,   357,   358,   360,   361,   362,   363,   364,   365,
     366,   367,   368,   371,   372,   373,   374,   376,   378,   380,
     347,     7,   343,   344,   345,     7,   437,   438,   439,     7,
     476,   477,   478,     7,   500,   501,   502,     7,   466,   467,
     468,   134,   231,   392,   393,   394,   395,   260,   135,   137,
     394,   398,   399,   400,   401,   119,   120,   384,   385,   386,
     388,     7,   585,   586,     7,   555,   556,   557,     7,   413,
     414,   415,   143,   144,   145,   146,   147,   148,   427,   428,
     429,   430,   431,   432,   433,   434,    24,   153,   154,   155,
     156,   266,   360,   532,   534,   600,   601,   602,   605,   606,
     608,   609,   159,   160,   161,   266,   406,   407,   408,   409,
     410,   532,   534,   164,   168,   169,   170,   171,   178,   179,
     266,   374,   376,   378,   532,   534,   619,   620,   621,   624,
     626,   628,   629,   630,   640,     7,   615,   616,   617,   182,
     183,   184,   231,   532,   534,   665,   666,   667,   668,   670,
     671,   677,     7,   703,   704,   216,   266,   727,   728,   729,
     263,     7,   521,   522,   523,     7,   538,   539,   540,   564,
     582,   343,     8,     8,     8,   350,   352,   354,   356,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   369,
       4,     4,   375,   377,   379,   381,     3,     8,     8,   346,
       6,     3,   440,     6,     3,   479,     6,     3,   503,     6,
       3,   469,     6,     3,     3,     6,     6,     3,     6,   387,
     389,     3,     8,   587,     3,     6,   558,     6,     3,   416,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
     603,   607,     4,     4,     4,     3,     8,     4,     4,     4,
       3,     8,   622,   625,   627,     4,   641,     4,   631,     3,
       8,   618,     6,     3,     4,   669,     4,   672,     3,     8,
       8,   705,     3,     6,     4,     3,     8,   231,   264,   265,
     524,     6,     3,   541,     6,     3,     8,     6,     4,     4,
       4,     4,   232,   234,   232,   234,   232,   232,   232,   232,
     232,   232,     4,   234,   232,     4,     4,     4,     4,   348,
     347,   345,   443,   439,   482,   478,   506,   502,   266,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   292,   293,   294,   295,   298,   300,   302,   303,
     304,   307,   308,   310,   312,   318,   320,   358,   435,   447,
     449,   451,   453,   455,   457,   459,   460,   461,   463,   470,
     471,   498,   532,   534,   580,   468,   393,   399,     4,     4,
     385,   124,   125,   126,   127,   266,   278,   279,   280,   281,
     282,   283,   358,   498,   532,   534,   588,   589,   590,   591,
     592,   594,   596,   597,   586,   561,   557,   419,   415,   232,
     232,   232,   232,   232,   232,   428,     4,     4,   232,   232,
     232,   601,   234,   232,   232,   407,     4,     4,     4,   232,
       4,   234,     4,   620,   619,   617,   234,     4,   232,     4,
     666,   207,   209,   210,   266,   358,   532,   534,   706,   707,
     708,   709,   711,   704,   234,   728,     6,     3,   527,   523,
     544,   540,   231,   231,   231,   231,    39,    40,    41,   370,
     231,   231,   231,   231,     8,     8,     8,     8,     3,     8,
     231,   231,   593,   595,     4,     4,     8,     3,     8,     8,
     150,   151,   152,   604,   231,   165,   166,   167,   623,   231,
     231,     7,     5,     8,   231,   251,   712,     4,   710,     3,
       8,   231,     8,     8,   471,     4,     4,   234,   234,   590,
      24,   173,   174,   175,   266,   532,   534,   642,   643,   644,
     647,   649,   651,     7,   632,   633,   634,     4,   232,     4,
     707,   231,   231,   645,   648,   650,   652,     3,     8,   635,
       6,     3,     5,   231,     4,     4,     4,     4,   643,   180,
     266,   358,   532,   534,   636,   637,   638,   634,     7,   713,
     714,   172,   646,   231,   231,     5,   639,     3,     8,   715,
       3,     6,     7,   653,   654,   655,     4,   637,   208,   211,
     212,   213,   214,   716,   717,   718,   720,   721,   722,   723,
     714,   656,     6,     3,   231,   719,     4,     4,     4,   724,
       3,     8,   176,   177,   266,   351,   353,   532,   534,   657,
     658,   659,   661,   655,     4,   234,   232,   232,     4,   717,
     660,   662,     3,     8,   231,   231,     4,     4,   658,   231,
     231
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
     444,   444,   444,   444,   444,   444,   444,   444,   446,   445,
     448,   447,   450,   449,   452,   451,   454,   453,   456,   455,
     458,   457,   459,   460,   461,   462,   463,   465,   464,   466,
     466,   467,   467,   467,   469,   468,   470,   470,   470,   471,
     471,   471,   471,   471,   471,   471,   471,   471,   471,   471,
     471,   471,   471,   471,   471,   471,   471,   471,   471,   471,
     471,   471,   471,   471,   471,   471,   471,   471,   471,   471,
     471,   471,   471,   471,   471,   471,   471,   471,   471,   471,
     471,   471,   471,   471,   473,   472,   475,   474,   476,   476,
     477,   477,   477,   479,   478,   481,   480,   482,   482,   483,
     483,   483,   484,   484,   484,   484,   484,   484,   484,   484,
     484,   484,   485,   486,   487,   489,   488,   491,   490,   493,
     492,   494,   496,   495,   497,   499,   498,   500,   500,   501,
     501,   501,   503,   502,   505,   504,   506,   506,   507,   507,
     507,   508,   508,   508,   508,   508,   508,   508,   508,   508,
     508,   508,   509,   511,   510,   512,   513,   514,   515,   516,
     518,   517,   520,   519,   521,   521,   522,   522,   522,   524,
     523,   526,   525,   527,   527,   527,   528,   528,   528,   528,
     528,   528,   528,   528,   528,   528,   530,   529,   531,   533,
     532,   535,   534,   537,   536,   538,   538,   539,   539,   539,
     541,   540,   543,   542,   544,   544,   544,   545,   545,   545,
     545,   545,   545,   545,   545,   545,   545,   545,   545,   545,
     545,   547,   546,   548,   550,   549,   551,   552,   554,   553,
     555,   555,   556,   556,   556,   558,   557,   560,   559,   561,
     561,   562,   562,   562,   563,   563,   563,   563,   563,   563,
     563,   563,   563,   563,   563,   563,   565,   564,   567,   566,
     569,   568,   571,   570,   573,   572,   575,   574,   577,   576,
     579,   578,   581,   580,   582,   584,   583,   585,   585,   585,
     587,   586,   588,   588,   589,   589,   589,   590,   590,   590,
     590,   590,   590,   590,   590,   590,   590,   590,   590,   590,
     590,   590,   591,   593,   592,   595,   594,   596,   597,   599,
     598,   600,   600,   600,   601,   601,   601,   601,   601,   601,
     601,   601,   601,   603,   602,   604,   604,   604,   605,   607,
     606,   608,   609,   610,   612,   611,   614,   613,   615,   615,
     616,   616,   616,   618,   617,   619,   619,   619,   620,   620,
     620,   620,   620,   620,   620,   620,   620,   620,   620,   620,
     620,   622,   621,   623,   623,   623,   625,   624,   627,   626,
     628,   629,   631,   630,   632,   632,   633,   633,   633,   635,
     634,   636,   636,   636,   637,   637,   637,   637,   637,   639,
     638,   641,   640,   642,   642,   642,   643,   643,   643,   643,
     643,   643,   643,   645,   644,   646,   648,   647,   650,   649,
     652,   651,   653,   653,   654,   654,   654,   656,   655,   657,
     657,   657,   658,   658,   658,   658,   658,   658,   658,   660,
     659,   662,   661,   664,   663,   665,   665,   665,   666,   666,
     666,   666,   666,   666,   667,   669,   668,   670,   672,   671,
     674,   673,   676,   675,   677,   677,   677,   678,   678,   678,
     678,   678,   678,   678,   678,   678,   678,   678,   679,   681,
     680,   682,   684,   683,   685,   686,   688,   687,   689,   689,
     691,   690,   693,   692,   695,   694,   696,   696,   696,   697,
     697,   699,   698,   700,   702,   701,   703,   703,   703,   705,
     704,   706,   706,   706,   707,   707,   707,   707,   707,   707,
     707,   708,   710,   709,   712,   711,   713,   713,   713,   715,
     714,   716,   716,   716,   717,   717,   717,   717,   717,   719,
     718,   720,   721,   722,   724,   723,   726,   725,   727,   727,
     727,   728,   728,   729
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
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     3,     3,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     0,     4,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     0,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     0,     4,     0,     4,     0,
       4,     1,     0,     4,     3,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     0,     1,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     3,     3,     3,
       0,     4,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     4,     3,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     0,
       1,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     1,     0,     6,     1,     3,     2,
       0,     4,     0,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     3,     3,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     3,     0,
       4,     3,     3,     3,     0,     6,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     0,     4,     0,     4,
       3,     3,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     0,
       4,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     0,     4,     0,     4,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     3,     0,     4,
       0,     6,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     3,     0,     4,     3,     3,     0,     4,     1,     1,
       0,     4,     0,     6,     0,     4,     1,     3,     2,     1,
       1,     0,     6,     3,     0,     6,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     6,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     0,
       4,     3,     3,     3,     0,     4,     0,     6,     1,     3,
       2,     1,     1,     3
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
    1645,  1646,  1647,  1648,  1649,  1650,  1651,  1652,  1655,  1655,
    1664,  1664,  1673,  1673,  1682,  1682,  1692,  1692,  1704,  1704,
    1715,  1715,  1726,  1732,  1738,  1744,  1750,  1758,  1758,  1770,
    1771,  1775,  1776,  1777,  1782,  1782,  1790,  1791,  1792,  1797,
    1798,  1799,  1800,  1801,  1802,  1803,  1804,  1805,  1806,  1807,
    1808,  1809,  1810,  1811,  1812,  1813,  1814,  1815,  1816,  1817,
    1818,  1819,  1820,  1821,  1822,  1823,  1824,  1825,  1826,  1827,
    1828,  1829,  1830,  1831,  1832,  1833,  1834,  1835,  1836,  1837,
    1838,  1839,  1840,  1841,  1848,  1848,  1862,  1862,  1871,  1872,
    1875,  1876,  1877,  1884,  1884,  1899,  1899,  1913,  1914,  1917,
    1918,  1919,  1924,  1925,  1926,  1927,  1928,  1929,  1930,  1931,
    1932,  1933,  1936,  1938,  1944,  1946,  1946,  1955,  1955,  1964,
    1964,  1973,  1975,  1975,  1984,  1994,  1994,  2007,  2008,  2013,
    2014,  2015,  2022,  2022,  2034,  2034,  2046,  2047,  2052,  2053,
    2054,  2061,  2062,  2063,  2064,  2065,  2066,  2067,  2068,  2069,
    2070,  2071,  2074,  2076,  2076,  2085,  2087,  2089,  2095,  2101,
    2107,  2107,  2121,  2121,  2134,  2135,  2138,  2139,  2140,  2145,
    2145,  2155,  2155,  2165,  2166,  2167,  2172,  2173,  2174,  2175,
    2176,  2177,  2178,  2179,  2180,  2181,  2184,  2184,  2193,  2199,
    2199,  2224,  2224,  2254,  2254,  2267,  2268,  2271,  2272,  2273,
    2278,  2278,  2290,  2290,  2302,  2303,  2304,  2309,  2310,  2311,
    2312,  2313,  2314,  2315,  2316,  2317,  2318,  2319,  2320,  2321,
    2322,  2325,  2325,  2334,  2340,  2340,  2349,  2355,  2364,  2364,
    2375,  2376,  2379,  2380,  2381,  2386,  2386,  2395,  2395,  2404,
    2405,  2408,  2409,  2410,  2416,  2417,  2418,  2419,  2420,  2421,
    2422,  2423,  2424,  2425,  2426,  2427,  2430,  2430,  2441,  2441,
    2452,  2452,  2463,  2463,  2472,  2472,  2481,  2481,  2490,  2490,
    2499,  2499,  2513,  2513,  2524,  2530,  2530,  2541,  2542,  2543,
    2548,  2548,  2558,  2559,  2562,  2563,  2564,  2569,  2570,  2571,
    2572,  2573,  2574,  2575,  2576,  2577,  2578,  2579,  2580,  2581,
    2582,  2583,  2586,  2588,  2588,  2597,  2597,  2607,  2613,  2622,
    2622,  2635,  2636,  2637,  2642,  2643,  2644,  2645,  2646,  2647,
    2648,  2649,  2650,  2653,  2653,  2661,  2662,  2663,  2666,  2672,
    2672,  2681,  2687,  2695,  2703,  2703,  2715,  2715,  2727,  2728,
    2731,  2732,  2733,  2738,  2738,  2746,  2747,  2748,  2753,  2754,
    2755,  2756,  2757,  2758,  2759,  2760,  2761,  2762,  2763,  2764,
    2765,  2768,  2768,  2777,  2778,  2779,  2782,  2782,  2792,  2792,
    2802,  2808,  2814,  2814,  2825,  2826,  2829,  2830,  2831,  2836,
    2836,  2844,  2845,  2846,  2851,  2852,  2853,  2854,  2855,  2858,
    2858,  2869,  2869,  2882,  2883,  2884,  2889,  2890,  2891,  2892,
    2893,  2894,  2895,  2898,  2898,  2906,  2909,  2909,  2918,  2918,
    2927,  2927,  2938,  2939,  2942,  2943,  2944,  2949,  2949,  2957,
    2958,  2959,  2964,  2965,  2966,  2967,  2968,  2969,  2970,  2973,
    2973,  2982,  2982,  2993,  2993,  3006,  3007,  3008,  3013,  3014,
    3015,  3016,  3017,  3018,  3021,  3027,  3027,  3036,  3042,  3042,
    3052,  3052,  3065,  3065,  3075,  3076,  3077,  3082,  3083,  3084,
    3085,  3086,  3087,  3088,  3089,  3090,  3091,  3092,  3095,  3101,
    3101,  3110,  3116,  3116,  3125,  3131,  3137,  3137,  3146,  3147,
    3150,  3150,  3161,  3161,  3173,  3173,  3183,  3184,  3185,  3191,
    3192,  3195,  3195,  3206,  3214,  3214,  3227,  3228,  3229,  3235,
    3235,  3243,  3244,  3245,  3250,  3251,  3252,  3253,  3254,  3255,
    3256,  3259,  3265,  3265,  3274,  3274,  3285,  3286,  3287,  3292,
    3292,  3300,  3301,  3302,  3307,  3308,  3309,  3310,  3311,  3314,
    3314,  3323,  3329,  3335,  3341,  3341,  3350,  3350,  3361,  3362,
    3363,  3368,  3369,  3372
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
#line 7043 "dhcp6_parser.cc"

#line 3378 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
