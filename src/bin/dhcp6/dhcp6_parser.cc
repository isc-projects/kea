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
      case symbol_kind::S_ssl_mode: // ssl_mode
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
      case symbol_kind::S_ssl_mode: // ssl_mode
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
      case symbol_kind::S_ssl_mode: // ssl_mode
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
      case symbol_kind::S_ssl_mode: // ssl_mode
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
#line 329 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 417 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 329 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 423 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 329 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 429 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 329 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 435 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 329 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 441 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 329 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 447 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 329 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 453 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 329 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 459 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 329 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 465 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ssl_mode: // ssl_mode
#line 329 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 471 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 329 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 477 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
#line 329 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 483 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 329 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 489 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 329 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 495 "dhcp6_parser.cc"
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
      case symbol_kind::S_ssl_mode: // ssl_mode
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
#line 338 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 777 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 339 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 783 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 340 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 789 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 341 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 795 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 342 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 801 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 343 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 807 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 344 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 813 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 345 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 819 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 346 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 825 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 347 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 831 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 348 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 837 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 349 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 843 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 350 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 849 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 351 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 855 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 359 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 861 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 360 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 867 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 361 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 873 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 362 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 879 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 363 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 885 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 364 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 891 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 365 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 897 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 368 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 906 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 373 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 917 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 378 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 927 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 384 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 933 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 391 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 943 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 396 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 954 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 402 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 962 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 407 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 971 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 410 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 979 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 418 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 988 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 422 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 997 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 426 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 1005 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 432 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 1013 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 434 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1022 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 443 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1031 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 447 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1040 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 451 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1048 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 461 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1059 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 470 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1070 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 475 "dhcp6_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1083 "dhcp6_parser.cc"
    break;

  case 63: // $@19: %empty
#line 485 "dhcp6_parser.yy"
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
#line 1098 "dhcp6_parser.cc"
    break;

  case 64: // global_object: "Dhcp6" $@19 ":" "{" global_params "}"
#line 494 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1108 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 502 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1116 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 508 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1126 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 512 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1135 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 519 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1143 "dhcp6_parser.cc"
    break;

  case 146: // $@21: %empty
#line 602 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1152 "dhcp6_parser.cc"
    break;

  case 147: // data_directory: "data-directory" $@21 ":" "constant string"
#line 605 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.warning(yystack_[2].location, "data-directory is deprecated and will be ignored");
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1163 "dhcp6_parser.cc"
    break;

  case 148: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 612 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1173 "dhcp6_parser.cc"
    break;

  case 149: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 618 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1183 "dhcp6_parser.cc"
    break;

  case 150: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 624 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1193 "dhcp6_parser.cc"
    break;

  case 151: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 630 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1203 "dhcp6_parser.cc"
    break;

  case 152: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 636 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1213 "dhcp6_parser.cc"
    break;

  case 153: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 642 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1223 "dhcp6_parser.cc"
    break;

  case 154: // renew_timer: "renew-timer" ":" "integer"
#line 648 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1233 "dhcp6_parser.cc"
    break;

  case 155: // rebind_timer: "rebind-timer" ":" "integer"
#line 654 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1243 "dhcp6_parser.cc"
    break;

  case 156: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 660 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1253 "dhcp6_parser.cc"
    break;

  case 157: // t1_percent: "t1-percent" ":" "floating point"
#line 666 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1263 "dhcp6_parser.cc"
    break;

  case 158: // t2_percent: "t2-percent" ":" "floating point"
#line 672 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1273 "dhcp6_parser.cc"
    break;

  case 159: // cache_threshold: "cache-threshold" ":" "floating point"
#line 678 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1283 "dhcp6_parser.cc"
    break;

  case 160: // cache_max_age: "cache-max-age" ":" "integer"
#line 684 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1293 "dhcp6_parser.cc"
    break;

  case 161: // adaptive_lease_time_threshold: "adaptive-lease-time-threshold" ":" "floating point"
#line 690 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("adaptive-lease-time-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr altt(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("adaptive-lease-time-threshold", altt);
}
#line 1303 "dhcp6_parser.cc"
    break;

  case 162: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 696 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1313 "dhcp6_parser.cc"
    break;

  case 163: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 702 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1323 "dhcp6_parser.cc"
    break;

  case 164: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 708 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1333 "dhcp6_parser.cc"
    break;

  case 165: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 714 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1343 "dhcp6_parser.cc"
    break;

  case 166: // $@22: %empty
#line 720 "dhcp6_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1352 "dhcp6_parser.cc"
    break;

  case 167: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 723 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1361 "dhcp6_parser.cc"
    break;

  case 168: // ddns_replace_client_name_value: "when-present"
#line 729 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1369 "dhcp6_parser.cc"
    break;

  case 169: // ddns_replace_client_name_value: "never"
#line 732 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1377 "dhcp6_parser.cc"
    break;

  case 170: // ddns_replace_client_name_value: "always"
#line 735 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1385 "dhcp6_parser.cc"
    break;

  case 171: // ddns_replace_client_name_value: "when-not-present"
#line 738 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1393 "dhcp6_parser.cc"
    break;

  case 172: // ddns_replace_client_name_value: "boolean"
#line 741 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1402 "dhcp6_parser.cc"
    break;

  case 173: // $@23: %empty
#line 747 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1411 "dhcp6_parser.cc"
    break;

  case 174: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 750 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1421 "dhcp6_parser.cc"
    break;

  case 175: // $@24: %empty
#line 756 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1430 "dhcp6_parser.cc"
    break;

  case 176: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 759 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1440 "dhcp6_parser.cc"
    break;

  case 177: // $@25: %empty
#line 765 "dhcp6_parser.yy"
                                     {
    ctx.unique("ddns-reverse-zone", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1449 "dhcp6_parser.cc"
    break;

  case 178: // ddns_reverse_zone: "ddns-reverse-zone" $@25 ":" "constant string"
#line 768 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-reverse-zone", s);
    ctx.leave();
}
#line 1459 "dhcp6_parser.cc"
    break;

  case 179: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 774 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1469 "dhcp6_parser.cc"
    break;

  case 180: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 783 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.warning(yystack_[1].location, "ddns-use-conflict-resolution is deprecated. "
             "Substituting ddns-conflict-resolution-mode");
    ElementPtr mode(new StringElement(b->boolValue() ? "check-with-dhcid"
                                      : "no-check-with-dhcid"));
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", mode);
}
#line 1483 "dhcp6_parser.cc"
    break;

  case 181: // $@26: %empty
#line 793 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1492 "dhcp6_parser.cc"
    break;

  case 182: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@26 ":" ddns_conflict_resolution_mode_value
#line 796 "dhcp6_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1501 "dhcp6_parser.cc"
    break;

  case 183: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 802 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1509 "dhcp6_parser.cc"
    break;

  case 184: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 805 "dhcp6_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1517 "dhcp6_parser.cc"
    break;

  case 185: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 808 "dhcp6_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1525 "dhcp6_parser.cc"
    break;

  case 186: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 811 "dhcp6_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1533 "dhcp6_parser.cc"
    break;

  case 187: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 816 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1543 "dhcp6_parser.cc"
    break;

  case 188: // ddns_ttl: "ddns-ttl" ":" "integer"
#line 822 "dhcp6_parser.yy"
                                 {
    ctx.unique("ddns-ttl", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl", ttl);
}
#line 1553 "dhcp6_parser.cc"
    break;

  case 189: // ddns_ttl_min: "ddns-ttl-min" ":" "integer"
#line 828 "dhcp6_parser.yy"
                                         {
    ctx.unique("ddns-ttl-min", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-min", ttl);
}
#line 1563 "dhcp6_parser.cc"
    break;

  case 190: // ddns_ttl_max: "ddns-ttl-max" ":" "integer"
#line 834 "dhcp6_parser.yy"
                                         {
    ctx.unique("ddns-ttl-max", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-max", ttl);
}
#line 1573 "dhcp6_parser.cc"
    break;

  case 191: // $@27: %empty
#line 840 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1582 "dhcp6_parser.cc"
    break;

  case 192: // hostname_char_set: "hostname-char-set" $@27 ":" "constant string"
#line 843 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1592 "dhcp6_parser.cc"
    break;

  case 193: // $@28: %empty
#line 849 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1601 "dhcp6_parser.cc"
    break;

  case 194: // hostname_char_replacement: "hostname-char-replacement" $@28 ":" "constant string"
#line 852 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1611 "dhcp6_parser.cc"
    break;

  case 195: // store_extended_info: "store-extended-info" ":" "boolean"
#line 858 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1621 "dhcp6_parser.cc"
    break;

  case 196: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 864 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1631 "dhcp6_parser.cc"
    break;

  case 197: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 870 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1641 "dhcp6_parser.cc"
    break;

  case 198: // $@29: %empty
#line 876 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1650 "dhcp6_parser.cc"
    break;

  case 199: // server_tag: "server-tag" $@29 ":" "constant string"
#line 879 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1660 "dhcp6_parser.cc"
    break;

  case 200: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 885 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1670 "dhcp6_parser.cc"
    break;

  case 201: // $@30: %empty
#line 891 "dhcp6_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1679 "dhcp6_parser.cc"
    break;

  case 202: // allocator: "allocator" $@30 ":" "constant string"
#line 894 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1689 "dhcp6_parser.cc"
    break;

  case 203: // $@31: %empty
#line 900 "dhcp6_parser.yy"
                           {
    ctx.unique("pd-allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1698 "dhcp6_parser.cc"
    break;

  case 204: // pd_allocator: "pd-allocator" $@31 ":" "constant string"
#line 903 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-allocator", al);
    ctx.leave();
}
#line 1708 "dhcp6_parser.cc"
    break;

  case 205: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 909 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1718 "dhcp6_parser.cc"
    break;

  case 206: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 915 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1728 "dhcp6_parser.cc"
    break;

  case 207: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 921 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1738 "dhcp6_parser.cc"
    break;

  case 208: // allow_address_registration: "allow-address-registration" ":" "boolean"
#line 927 "dhcp6_parser.yy"
                                                                     {
    ctx.unique("allow-address-registration", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allow-address-registration", first);
}
#line 1748 "dhcp6_parser.cc"
    break;

  case 209: // $@32: %empty
#line 933 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1760 "dhcp6_parser.cc"
    break;

  case 210: // interfaces_config: "interfaces-config" $@32 ":" "{" interfaces_config_params "}"
#line 939 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1770 "dhcp6_parser.cc"
    break;

  case 211: // $@33: %empty
#line 945 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1780 "dhcp6_parser.cc"
    break;

  case 212: // sub_interfaces6: "{" $@33 interfaces_config_params "}"
#line 949 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1789 "dhcp6_parser.cc"
    break;

  case 215: // interfaces_config_params: interfaces_config_params ","
#line 956 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1797 "dhcp6_parser.cc"
    break;

  case 224: // $@34: %empty
#line 971 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1809 "dhcp6_parser.cc"
    break;

  case 225: // interfaces_list: "interfaces" $@34 ":" list_strings
#line 977 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1818 "dhcp6_parser.cc"
    break;

  case 226: // re_detect: "re-detect" ":" "boolean"
#line 982 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1828 "dhcp6_parser.cc"
    break;

  case 227: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 988 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1838 "dhcp6_parser.cc"
    break;

  case 228: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 994 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1848 "dhcp6_parser.cc"
    break;

  case 229: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 1000 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1858 "dhcp6_parser.cc"
    break;

  case 230: // $@35: %empty
#line 1006 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1870 "dhcp6_parser.cc"
    break;

  case 231: // lease_database: "lease-database" $@35 ":" "{" database_map_params "}"
#line 1012 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1881 "dhcp6_parser.cc"
    break;

  case 232: // $@36: %empty
#line 1019 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1893 "dhcp6_parser.cc"
    break;

  case 233: // hosts_database: "hosts-database" $@36 ":" "{" database_map_params "}"
#line 1025 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1904 "dhcp6_parser.cc"
    break;

  case 234: // $@37: %empty
#line 1032 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1916 "dhcp6_parser.cc"
    break;

  case 235: // hosts_databases: "hosts-databases" $@37 ":" "[" database_list "]"
#line 1038 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1925 "dhcp6_parser.cc"
    break;

  case 240: // not_empty_database_list: not_empty_database_list ","
#line 1049 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1933 "dhcp6_parser.cc"
    break;

  case 241: // $@38: %empty
#line 1054 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1943 "dhcp6_parser.cc"
    break;

  case 242: // database: "{" $@38 database_map_params "}"
#line 1058 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1953 "dhcp6_parser.cc"
    break;

  case 245: // database_map_params: database_map_params ","
#line 1066 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1961 "dhcp6_parser.cc"
    break;

  case 271: // $@39: %empty
#line 1098 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1970 "dhcp6_parser.cc"
    break;

  case 272: // database_type: "type" $@39 ":" "constant string"
#line 1101 "dhcp6_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 1980 "dhcp6_parser.cc"
    break;

  case 273: // $@40: %empty
#line 1107 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1989 "dhcp6_parser.cc"
    break;

  case 274: // user: "user" $@40 ":" "constant string"
#line 1110 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1999 "dhcp6_parser.cc"
    break;

  case 275: // $@41: %empty
#line 1116 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2008 "dhcp6_parser.cc"
    break;

  case 276: // password: "password" $@41 ":" "constant string"
#line 1119 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2018 "dhcp6_parser.cc"
    break;

  case 277: // $@42: %empty
#line 1125 "dhcp6_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2027 "dhcp6_parser.cc"
    break;

  case 278: // password_file: "password-file" $@42 ":" "constant string"
#line 1128 "dhcp6_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 2037 "dhcp6_parser.cc"
    break;

  case 279: // $@43: %empty
#line 1134 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2046 "dhcp6_parser.cc"
    break;

  case 280: // host: "host" $@43 ":" "constant string"
#line 1137 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2056 "dhcp6_parser.cc"
    break;

  case 281: // port: "port" ":" "integer"
#line 1143 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2066 "dhcp6_parser.cc"
    break;

  case 282: // $@44: %empty
#line 1149 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2075 "dhcp6_parser.cc"
    break;

  case 283: // name: "name" $@44 ":" "constant string"
#line 1152 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2085 "dhcp6_parser.cc"
    break;

  case 284: // persist: "persist" ":" "boolean"
#line 1158 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2095 "dhcp6_parser.cc"
    break;

  case 285: // lfc_interval: "lfc-interval" ":" "integer"
#line 1164 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2105 "dhcp6_parser.cc"
    break;

  case 286: // readonly: "readonly" ":" "boolean"
#line 1170 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2115 "dhcp6_parser.cc"
    break;

  case 287: // connect_timeout: "connect-timeout" ":" "integer"
#line 1176 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2125 "dhcp6_parser.cc"
    break;

  case 288: // read_timeout: "read-timeout" ":" "integer"
#line 1182 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2135 "dhcp6_parser.cc"
    break;

  case 289: // write_timeout: "write-timeout" ":" "integer"
#line 1188 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2145 "dhcp6_parser.cc"
    break;

  case 290: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1194 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2155 "dhcp6_parser.cc"
    break;

  case 291: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1200 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2165 "dhcp6_parser.cc"
    break;

  case 292: // $@45: %empty
#line 1206 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2174 "dhcp6_parser.cc"
    break;

  case 293: // on_fail: "on-fail" $@45 ":" on_fail_mode
#line 1209 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2183 "dhcp6_parser.cc"
    break;

  case 294: // on_fail_mode: "stop-retry-exit"
#line 1214 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2189 "dhcp6_parser.cc"
    break;

  case 295: // on_fail_mode: "serve-retry-exit"
#line 1215 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2195 "dhcp6_parser.cc"
    break;

  case 296: // on_fail_mode: "serve-retry-continue"
#line 1216 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2201 "dhcp6_parser.cc"
    break;

  case 297: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1219 "dhcp6_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2211 "dhcp6_parser.cc"
    break;

  case 298: // max_row_errors: "max-row-errors" ":" "integer"
#line 1225 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2221 "dhcp6_parser.cc"
    break;

  case 299: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1231 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2231 "dhcp6_parser.cc"
    break;

  case 300: // $@46: %empty
#line 1237 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2240 "dhcp6_parser.cc"
    break;

  case 301: // trust_anchor: "trust-anchor" $@46 ":" "constant string"
#line 1240 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2250 "dhcp6_parser.cc"
    break;

  case 302: // $@47: %empty
#line 1246 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2259 "dhcp6_parser.cc"
    break;

  case 303: // cert_file: "cert-file" $@47 ":" "constant string"
#line 1249 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2269 "dhcp6_parser.cc"
    break;

  case 304: // $@48: %empty
#line 1255 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2278 "dhcp6_parser.cc"
    break;

  case 305: // key_file: "key-file" $@48 ":" "constant string"
#line 1258 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2288 "dhcp6_parser.cc"
    break;

  case 306: // $@49: %empty
#line 1264 "dhcp6_parser.yy"
                   {
    ctx.unique("ssl-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SSL_MODE);
}
#line 2297 "dhcp6_parser.cc"
    break;

  case 307: // ssl_mode: "ssl-mode" $@49 ":" ssl_mode
#line 1267 "dhcp6_parser.yy"
                 {
    ctx.stack_.back()->set("ssl-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2306 "dhcp6_parser.cc"
    break;

  case 308: // ssl_mode: "disable"
#line 1272 "dhcp6_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disable", ctx.loc2pos(yystack_[0].location)));
            }
#line 2314 "dhcp6_parser.cc"
    break;

  case 309: // ssl_mode: "prefer"
#line 1275 "dhcp6_parser.yy"
                 {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("prefer", ctx.loc2pos(yystack_[0].location)));
            }
#line 2322 "dhcp6_parser.cc"
    break;

  case 310: // ssl_mode: "require"
#line 1278 "dhcp6_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("require", ctx.loc2pos(yystack_[0].location)));
            }
#line 2330 "dhcp6_parser.cc"
    break;

  case 311: // ssl_mode: "verify-ca"
#line 1281 "dhcp6_parser.yy"
                    {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-ca", ctx.loc2pos(yystack_[0].location)));
            }
#line 2338 "dhcp6_parser.cc"
    break;

  case 312: // ssl_mode: "verify-full"
#line 1284 "dhcp6_parser.yy"
                      {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-full", ctx.loc2pos(yystack_[0].location)));
            }
#line 2346 "dhcp6_parser.cc"
    break;

  case 313: // $@50: %empty
#line 1289 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2355 "dhcp6_parser.cc"
    break;

  case 314: // cipher_list: "cipher-list" $@50 ":" "constant string"
#line 1292 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2365 "dhcp6_parser.cc"
    break;

  case 315: // $@51: %empty
#line 1298 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2377 "dhcp6_parser.cc"
    break;

  case 316: // sanity_checks: "sanity-checks" $@51 ":" "{" sanity_checks_params "}"
#line 1304 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2386 "dhcp6_parser.cc"
    break;

  case 319: // sanity_checks_params: sanity_checks_params ","
#line 1311 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2394 "dhcp6_parser.cc"
    break;

  case 322: // $@52: %empty
#line 1320 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2403 "dhcp6_parser.cc"
    break;

  case 323: // lease_checks: "lease-checks" $@52 ":" "constant string"
#line 1323 "dhcp6_parser.yy"
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
#line 2423 "dhcp6_parser.cc"
    break;

  case 324: // $@53: %empty
#line 1339 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2432 "dhcp6_parser.cc"
    break;

  case 325: // extended_info_checks: "extended-info-checks" $@53 ":" "constant string"
#line 1342 "dhcp6_parser.yy"
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
#line 2451 "dhcp6_parser.cc"
    break;

  case 326: // $@54: %empty
#line 1357 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2463 "dhcp6_parser.cc"
    break;

  case 327: // mac_sources: "mac-sources" $@54 ":" "[" mac_sources_list "]"
#line 1363 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2472 "dhcp6_parser.cc"
    break;

  case 330: // mac_sources_list: mac_sources_list ","
#line 1370 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2480 "dhcp6_parser.cc"
    break;

  case 333: // duid_id: "duid"
#line 1379 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2489 "dhcp6_parser.cc"
    break;

  case 334: // string_id: "constant string"
#line 1384 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2498 "dhcp6_parser.cc"
    break;

  case 335: // $@55: %empty
#line 1389 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2510 "dhcp6_parser.cc"
    break;

  case 336: // host_reservation_identifiers: "host-reservation-identifiers" $@55 ":" "[" host_reservation_identifiers_list "]"
#line 1395 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2519 "dhcp6_parser.cc"
    break;

  case 339: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1402 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2527 "dhcp6_parser.cc"
    break;

  case 343: // hw_address_id: "hw-address"
#line 1412 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2536 "dhcp6_parser.cc"
    break;

  case 344: // flex_id: "flex-id"
#line 1417 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2545 "dhcp6_parser.cc"
    break;

  case 345: // $@56: %empty
#line 1424 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2557 "dhcp6_parser.cc"
    break;

  case 346: // relay_supplied_options: "relay-supplied-options" $@56 ":" "[" list_content "]"
#line 1430 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2566 "dhcp6_parser.cc"
    break;

  case 347: // $@57: %empty
#line 1437 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2578 "dhcp6_parser.cc"
    break;

  case 348: // dhcp_multi_threading: "multi-threading" $@57 ":" "{" multi_threading_params "}"
#line 1443 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2589 "dhcp6_parser.cc"
    break;

  case 351: // multi_threading_params: multi_threading_params ","
#line 1452 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2597 "dhcp6_parser.cc"
    break;

  case 358: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1465 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2607 "dhcp6_parser.cc"
    break;

  case 359: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1471 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2617 "dhcp6_parser.cc"
    break;

  case 360: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1477 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2627 "dhcp6_parser.cc"
    break;

  case 361: // $@58: %empty
#line 1483 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2639 "dhcp6_parser.cc"
    break;

  case 362: // hooks_libraries: "hooks-libraries" $@58 ":" "[" hooks_libraries_list "]"
#line 1489 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2648 "dhcp6_parser.cc"
    break;

  case 367: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1500 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2656 "dhcp6_parser.cc"
    break;

  case 368: // $@59: %empty
#line 1505 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2666 "dhcp6_parser.cc"
    break;

  case 369: // hooks_library: "{" $@59 hooks_params "}"
#line 1509 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2676 "dhcp6_parser.cc"
    break;

  case 370: // $@60: %empty
#line 1515 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2686 "dhcp6_parser.cc"
    break;

  case 371: // sub_hooks_library: "{" $@60 hooks_params "}"
#line 1519 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2696 "dhcp6_parser.cc"
    break;

  case 374: // hooks_params: hooks_params ","
#line 1527 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2704 "dhcp6_parser.cc"
    break;

  case 378: // $@61: %empty
#line 1537 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2713 "dhcp6_parser.cc"
    break;

  case 379: // library: "library" $@61 ":" "constant string"
#line 1540 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2723 "dhcp6_parser.cc"
    break;

  case 380: // $@62: %empty
#line 1546 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2732 "dhcp6_parser.cc"
    break;

  case 381: // parameters: "parameters" $@62 ":" map_value
#line 1549 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2741 "dhcp6_parser.cc"
    break;

  case 382: // $@63: %empty
#line 1555 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2753 "dhcp6_parser.cc"
    break;

  case 383: // expired_leases_processing: "expired-leases-processing" $@63 ":" "{" expired_leases_params "}"
#line 1561 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2763 "dhcp6_parser.cc"
    break;

  case 386: // expired_leases_params: expired_leases_params ","
#line 1569 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2771 "dhcp6_parser.cc"
    break;

  case 393: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1582 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2781 "dhcp6_parser.cc"
    break;

  case 394: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1588 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2791 "dhcp6_parser.cc"
    break;

  case 395: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1594 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2801 "dhcp6_parser.cc"
    break;

  case 396: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1600 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2811 "dhcp6_parser.cc"
    break;

  case 397: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1606 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2821 "dhcp6_parser.cc"
    break;

  case 398: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1612 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2831 "dhcp6_parser.cc"
    break;

  case 399: // $@64: %empty
#line 1621 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2843 "dhcp6_parser.cc"
    break;

  case 400: // subnet6_list: "subnet6" $@64 ":" "[" subnet6_list_content "]"
#line 1627 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2852 "dhcp6_parser.cc"
    break;

  case 405: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1641 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2860 "dhcp6_parser.cc"
    break;

  case 406: // $@65: %empty
#line 1650 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2870 "dhcp6_parser.cc"
    break;

  case 407: // subnet6: "{" $@65 subnet6_params "}"
#line 1654 "dhcp6_parser.yy"
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
#line 2896 "dhcp6_parser.cc"
    break;

  case 408: // $@66: %empty
#line 1676 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2906 "dhcp6_parser.cc"
    break;

  case 409: // sub_subnet6: "{" $@66 subnet6_params "}"
#line 1680 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2916 "dhcp6_parser.cc"
    break;

  case 412: // subnet6_params: subnet6_params ","
#line 1689 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2924 "dhcp6_parser.cc"
    break;

  case 464: // $@67: %empty
#line 1748 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2933 "dhcp6_parser.cc"
    break;

  case 465: // subnet: "subnet" $@67 ":" "constant string"
#line 1751 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2943 "dhcp6_parser.cc"
    break;

  case 466: // $@68: %empty
#line 1757 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2952 "dhcp6_parser.cc"
    break;

  case 467: // interface: "interface" $@68 ":" "constant string"
#line 1760 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2962 "dhcp6_parser.cc"
    break;

  case 468: // $@69: %empty
#line 1766 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2971 "dhcp6_parser.cc"
    break;

  case 469: // interface_id: "interface-id" $@69 ":" "constant string"
#line 1769 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2981 "dhcp6_parser.cc"
    break;

  case 470: // $@70: %empty
#line 1776 "dhcp6_parser.yy"
                                       {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2993 "dhcp6_parser.cc"
    break;

  case 471: // network_client_classes: "client-classes" $@70 ":" list_strings
#line 1782 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3002 "dhcp6_parser.cc"
    break;

  case 472: // $@71: %empty
#line 1787 "dhcp6_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3014 "dhcp6_parser.cc"
    break;

  case 473: // evaluate_additional_classes: "evaluate-additional-classes" $@71 ":" list_strings
#line 1793 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3023 "dhcp6_parser.cc"
    break;

  case 474: // reservations_global: "reservations-global" ":" "boolean"
#line 1798 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 3033 "dhcp6_parser.cc"
    break;

  case 475: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1804 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 3043 "dhcp6_parser.cc"
    break;

  case 476: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1810 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 3053 "dhcp6_parser.cc"
    break;

  case 477: // id: "id" ":" "integer"
#line 1816 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 3063 "dhcp6_parser.cc"
    break;

  case 478: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1822 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 3073 "dhcp6_parser.cc"
    break;

  case 479: // $@72: %empty
#line 1830 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3085 "dhcp6_parser.cc"
    break;

  case 480: // shared_networks: "shared-networks" $@72 ":" "[" shared_networks_content "]"
#line 1836 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3094 "dhcp6_parser.cc"
    break;

  case 485: // shared_networks_list: shared_networks_list ","
#line 1849 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3102 "dhcp6_parser.cc"
    break;

  case 486: // $@73: %empty
#line 1854 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3112 "dhcp6_parser.cc"
    break;

  case 487: // shared_network: "{" $@73 shared_network_params "}"
#line 1858 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3120 "dhcp6_parser.cc"
    break;

  case 490: // shared_network_params: shared_network_params ","
#line 1864 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3128 "dhcp6_parser.cc"
    break;

  case 539: // $@74: %empty
#line 1923 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3140 "dhcp6_parser.cc"
    break;

  case 540: // option_def_list: "option-def" $@74 ":" "[" option_def_list_content "]"
#line 1929 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3149 "dhcp6_parser.cc"
    break;

  case 541: // $@75: %empty
#line 1937 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3158 "dhcp6_parser.cc"
    break;

  case 542: // sub_option_def_list: "{" $@75 option_def_list "}"
#line 1940 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 3166 "dhcp6_parser.cc"
    break;

  case 547: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1952 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3174 "dhcp6_parser.cc"
    break;

  case 548: // $@76: %empty
#line 1959 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3184 "dhcp6_parser.cc"
    break;

  case 549: // option_def_entry: "{" $@76 option_def_params "}"
#line 1963 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3196 "dhcp6_parser.cc"
    break;

  case 550: // $@77: %empty
#line 1974 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3206 "dhcp6_parser.cc"
    break;

  case 551: // sub_option_def: "{" $@77 option_def_params "}"
#line 1978 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3218 "dhcp6_parser.cc"
    break;

  case 556: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1994 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3226 "dhcp6_parser.cc"
    break;

  case 568: // code: "code" ":" "integer"
#line 2013 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3236 "dhcp6_parser.cc"
    break;

  case 570: // $@78: %empty
#line 2021 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3245 "dhcp6_parser.cc"
    break;

  case 571: // option_def_type: "type" $@78 ":" "constant string"
#line 2024 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3255 "dhcp6_parser.cc"
    break;

  case 572: // $@79: %empty
#line 2030 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3264 "dhcp6_parser.cc"
    break;

  case 573: // option_def_record_types: "record-types" $@79 ":" "constant string"
#line 2033 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3274 "dhcp6_parser.cc"
    break;

  case 574: // $@80: %empty
#line 2039 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3283 "dhcp6_parser.cc"
    break;

  case 575: // space: "space" $@80 ":" "constant string"
#line 2042 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3293 "dhcp6_parser.cc"
    break;

  case 577: // $@81: %empty
#line 2050 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3302 "dhcp6_parser.cc"
    break;

  case 578: // option_def_encapsulate: "encapsulate" $@81 ":" "constant string"
#line 2053 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3312 "dhcp6_parser.cc"
    break;

  case 579: // option_def_array: "array" ":" "boolean"
#line 2059 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3322 "dhcp6_parser.cc"
    break;

  case 580: // $@82: %empty
#line 2069 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3334 "dhcp6_parser.cc"
    break;

  case 581: // option_data_list: "option-data" $@82 ":" "[" option_data_list_content "]"
#line 2075 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3343 "dhcp6_parser.cc"
    break;

  case 586: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2090 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3351 "dhcp6_parser.cc"
    break;

  case 587: // $@83: %empty
#line 2097 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3361 "dhcp6_parser.cc"
    break;

  case 588: // option_data_entry: "{" $@83 option_data_params "}"
#line 2101 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3370 "dhcp6_parser.cc"
    break;

  case 589: // $@84: %empty
#line 2109 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3380 "dhcp6_parser.cc"
    break;

  case 590: // sub_option_data: "{" $@84 option_data_params "}"
#line 2113 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3389 "dhcp6_parser.cc"
    break;

  case 595: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2129 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3397 "dhcp6_parser.cc"
    break;

  case 608: // $@85: %empty
#line 2151 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3406 "dhcp6_parser.cc"
    break;

  case 609: // option_data_data: "data" $@85 ":" "constant string"
#line 2154 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3416 "dhcp6_parser.cc"
    break;

  case 612: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2164 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3426 "dhcp6_parser.cc"
    break;

  case 613: // option_data_always_send: "always-send" ":" "boolean"
#line 2170 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3436 "dhcp6_parser.cc"
    break;

  case 614: // option_data_never_send: "never-send" ":" "boolean"
#line 2176 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3446 "dhcp6_parser.cc"
    break;

  case 615: // $@86: %empty
#line 2182 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3458 "dhcp6_parser.cc"
    break;

  case 616: // option_data_client_classes: "client-classes" $@86 ":" list_strings
#line 2188 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3467 "dhcp6_parser.cc"
    break;

  case 617: // $@87: %empty
#line 2196 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3479 "dhcp6_parser.cc"
    break;

  case 618: // pools_list: "pools" $@87 ":" "[" pools_list_content "]"
#line 2202 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3488 "dhcp6_parser.cc"
    break;

  case 623: // not_empty_pools_list: not_empty_pools_list ","
#line 2215 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3496 "dhcp6_parser.cc"
    break;

  case 624: // $@88: %empty
#line 2220 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3506 "dhcp6_parser.cc"
    break;

  case 625: // pool_list_entry: "{" $@88 pool_params "}"
#line 2224 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3516 "dhcp6_parser.cc"
    break;

  case 626: // $@89: %empty
#line 2230 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3526 "dhcp6_parser.cc"
    break;

  case 627: // sub_pool6: "{" $@89 pool_params "}"
#line 2234 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3536 "dhcp6_parser.cc"
    break;

  case 630: // pool_params: pool_params ","
#line 2242 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3544 "dhcp6_parser.cc"
    break;

  case 654: // $@90: %empty
#line 2272 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3553 "dhcp6_parser.cc"
    break;

  case 655: // pool_entry: "pool" $@90 ":" "constant string"
#line 2275 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3563 "dhcp6_parser.cc"
    break;

  case 656: // pool_id: "pool-id" ":" "integer"
#line 2281 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3573 "dhcp6_parser.cc"
    break;

  case 657: // $@91: %empty
#line 2287 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3581 "dhcp6_parser.cc"
    break;

  case 658: // user_context: "user-context" $@91 ":" map_value
#line 2289 "dhcp6_parser.yy"
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
#line 3608 "dhcp6_parser.cc"
    break;

  case 659: // $@92: %empty
#line 2312 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3616 "dhcp6_parser.cc"
    break;

  case 660: // comment: "comment" $@92 ":" "constant string"
#line 2314 "dhcp6_parser.yy"
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
#line 3645 "dhcp6_parser.cc"
    break;

  case 661: // $@93: %empty
#line 2342 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3657 "dhcp6_parser.cc"
    break;

  case 662: // pd_pools_list: "pd-pools" $@93 ":" "[" pd_pools_list_content "]"
#line 2348 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3666 "dhcp6_parser.cc"
    break;

  case 667: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2361 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3674 "dhcp6_parser.cc"
    break;

  case 668: // $@94: %empty
#line 2366 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3684 "dhcp6_parser.cc"
    break;

  case 669: // pd_pool_entry: "{" $@94 pd_pool_params "}"
#line 2370 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3696 "dhcp6_parser.cc"
    break;

  case 670: // $@95: %empty
#line 2378 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3706 "dhcp6_parser.cc"
    break;

  case 671: // sub_pd_pool: "{" $@95 pd_pool_params "}"
#line 2382 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3718 "dhcp6_parser.cc"
    break;

  case 674: // pd_pool_params: pd_pool_params ","
#line 2392 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3726 "dhcp6_parser.cc"
    break;

  case 687: // $@96: %empty
#line 2411 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3735 "dhcp6_parser.cc"
    break;

  case 688: // pd_prefix: "prefix" $@96 ":" "constant string"
#line 2414 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3745 "dhcp6_parser.cc"
    break;

  case 689: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2420 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3755 "dhcp6_parser.cc"
    break;

  case 690: // $@97: %empty
#line 2426 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3764 "dhcp6_parser.cc"
    break;

  case 691: // excluded_prefix: "excluded-prefix" $@97 ":" "constant string"
#line 2429 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3774 "dhcp6_parser.cc"
    break;

  case 692: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2435 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3784 "dhcp6_parser.cc"
    break;

  case 693: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2441 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3794 "dhcp6_parser.cc"
    break;

  case 694: // $@98: %empty
#line 2450 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3806 "dhcp6_parser.cc"
    break;

  case 695: // reservations: "reservations" $@98 ":" "[" reservations_list "]"
#line 2456 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3815 "dhcp6_parser.cc"
    break;

  case 700: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2467 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3823 "dhcp6_parser.cc"
    break;

  case 701: // $@99: %empty
#line 2472 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3833 "dhcp6_parser.cc"
    break;

  case 702: // reservation: "{" $@99 reservation_params "}"
#line 2476 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3842 "dhcp6_parser.cc"
    break;

  case 703: // $@100: %empty
#line 2481 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3852 "dhcp6_parser.cc"
    break;

  case 704: // sub_reservation: "{" $@100 reservation_params "}"
#line 2485 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3861 "dhcp6_parser.cc"
    break;

  case 709: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2496 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3869 "dhcp6_parser.cc"
    break;

  case 722: // $@101: %empty
#line 2516 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3881 "dhcp6_parser.cc"
    break;

  case 723: // ip_addresses: "ip-addresses" $@101 ":" list_strings
#line 2522 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3890 "dhcp6_parser.cc"
    break;

  case 724: // $@102: %empty
#line 2527 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3902 "dhcp6_parser.cc"
    break;

  case 725: // prefixes: "prefixes" $@102 ":" list_strings
#line 2533 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3911 "dhcp6_parser.cc"
    break;

  case 726: // $@103: %empty
#line 2538 "dhcp6_parser.yy"
                                     {
    ctx.unique("excluded-prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3923 "dhcp6_parser.cc"
    break;

  case 727: // excluded_prefixes: "excluded-prefixes" $@103 ":" list_strings
#line 2544 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3932 "dhcp6_parser.cc"
    break;

  case 728: // $@104: %empty
#line 2549 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3941 "dhcp6_parser.cc"
    break;

  case 729: // duid: "duid" $@104 ":" "constant string"
#line 2552 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3951 "dhcp6_parser.cc"
    break;

  case 730: // $@105: %empty
#line 2558 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3960 "dhcp6_parser.cc"
    break;

  case 731: // hw_address: "hw-address" $@105 ":" "constant string"
#line 2561 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3970 "dhcp6_parser.cc"
    break;

  case 732: // $@106: %empty
#line 2567 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3979 "dhcp6_parser.cc"
    break;

  case 733: // hostname: "hostname" $@106 ":" "constant string"
#line 2570 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3989 "dhcp6_parser.cc"
    break;

  case 734: // $@107: %empty
#line 2576 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3998 "dhcp6_parser.cc"
    break;

  case 735: // flex_id_value: "flex-id" $@107 ":" "constant string"
#line 2579 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 4008 "dhcp6_parser.cc"
    break;

  case 736: // $@108: %empty
#line 2585 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4020 "dhcp6_parser.cc"
    break;

  case 737: // reservation_client_classes: "client-classes" $@108 ":" list_strings
#line 2591 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4029 "dhcp6_parser.cc"
    break;

  case 738: // $@109: %empty
#line 2599 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 4041 "dhcp6_parser.cc"
    break;

  case 739: // relay: "relay" $@109 ":" "{" relay_map "}"
#line 2605 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4050 "dhcp6_parser.cc"
    break;

  case 741: // $@110: %empty
#line 2616 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 4062 "dhcp6_parser.cc"
    break;

  case 742: // client_classes: "client-classes" $@110 ":" "[" client_classes_list "]"
#line 2622 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4071 "dhcp6_parser.cc"
    break;

  case 747: // not_empty_classes_list: not_empty_classes_list ","
#line 2633 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4079 "dhcp6_parser.cc"
    break;

  case 748: // $@111: %empty
#line 2638 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4089 "dhcp6_parser.cc"
    break;

  case 749: // client_class_entry: "{" $@111 client_class_params "}"
#line 2642 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 4099 "dhcp6_parser.cc"
    break;

  case 754: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2654 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 4107 "dhcp6_parser.cc"
    break;

  case 770: // $@112: %empty
#line 2677 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4116 "dhcp6_parser.cc"
    break;

  case 771: // client_class_test: "test" $@112 ":" "constant string"
#line 2680 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4126 "dhcp6_parser.cc"
    break;

  case 772: // $@113: %empty
#line 2686 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4135 "dhcp6_parser.cc"
    break;

  case 773: // client_class_template_test: "template-test" $@113 ":" "constant string"
#line 2689 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4145 "dhcp6_parser.cc"
    break;

  case 774: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2695 "dhcp6_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4155 "dhcp6_parser.cc"
    break;

  case 775: // $@114: %empty
#line 2704 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 4167 "dhcp6_parser.cc"
    break;

  case 776: // server_id: "server-id" $@114 ":" "{" server_id_params "}"
#line 2710 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4178 "dhcp6_parser.cc"
    break;

  case 779: // server_id_params: server_id_params ","
#line 2719 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4186 "dhcp6_parser.cc"
    break;

  case 789: // $@115: %empty
#line 2735 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 4195 "dhcp6_parser.cc"
    break;

  case 790: // server_id_type: "type" $@115 ":" duid_type
#line 2738 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4204 "dhcp6_parser.cc"
    break;

  case 791: // duid_type: "LLT"
#line 2743 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4210 "dhcp6_parser.cc"
    break;

  case 792: // duid_type: "EN"
#line 2744 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4216 "dhcp6_parser.cc"
    break;

  case 793: // duid_type: "LL"
#line 2745 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4222 "dhcp6_parser.cc"
    break;

  case 794: // htype: "htype" ":" "integer"
#line 2748 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4232 "dhcp6_parser.cc"
    break;

  case 795: // $@116: %empty
#line 2754 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4241 "dhcp6_parser.cc"
    break;

  case 796: // identifier: "identifier" $@116 ":" "constant string"
#line 2757 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4251 "dhcp6_parser.cc"
    break;

  case 797: // time: "time" ":" "integer"
#line 2763 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4261 "dhcp6_parser.cc"
    break;

  case 798: // enterprise_id: "enterprise-id" ":" "integer"
#line 2769 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4271 "dhcp6_parser.cc"
    break;

  case 799: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2777 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4281 "dhcp6_parser.cc"
    break;

  case 800: // $@117: %empty
#line 2785 "dhcp6_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKETS);
}
#line 4293 "dhcp6_parser.cc"
    break;

  case 801: // control_sockets: "control-sockets" $@117 ":" "[" control_socket_list "]"
#line 2791 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4302 "dhcp6_parser.cc"
    break;

  case 806: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2802 "dhcp6_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4310 "dhcp6_parser.cc"
    break;

  case 807: // $@118: %empty
#line 2807 "dhcp6_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4320 "dhcp6_parser.cc"
    break;

  case 808: // control_socket_entry: "{" $@118 control_socket_params "}"
#line 2811 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4328 "dhcp6_parser.cc"
    break;

  case 811: // control_socket_params: control_socket_params ","
#line 2817 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4336 "dhcp6_parser.cc"
    break;

  case 825: // $@119: %empty
#line 2837 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4345 "dhcp6_parser.cc"
    break;

  case 826: // control_socket_type: "socket-type" $@119 ":" control_socket_type_value
#line 2840 "dhcp6_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4354 "dhcp6_parser.cc"
    break;

  case 827: // control_socket_type_value: "unix"
#line 2846 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4360 "dhcp6_parser.cc"
    break;

  case 828: // control_socket_type_value: "http"
#line 2847 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4366 "dhcp6_parser.cc"
    break;

  case 829: // control_socket_type_value: "https"
#line 2848 "dhcp6_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4372 "dhcp6_parser.cc"
    break;

  case 830: // $@120: %empty
#line 2851 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4381 "dhcp6_parser.cc"
    break;

  case 831: // control_socket_name: "socket-name" $@120 ":" "constant string"
#line 2854 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4391 "dhcp6_parser.cc"
    break;

  case 832: // $@121: %empty
#line 2860 "dhcp6_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4400 "dhcp6_parser.cc"
    break;

  case 833: // control_socket_address: "socket-address" $@121 ":" "constant string"
#line 2863 "dhcp6_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4410 "dhcp6_parser.cc"
    break;

  case 834: // control_socket_port: "socket-port" ":" "integer"
#line 2869 "dhcp6_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4420 "dhcp6_parser.cc"
    break;

  case 835: // cert_required: "cert-required" ":" "boolean"
#line 2875 "dhcp6_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4430 "dhcp6_parser.cc"
    break;

  case 836: // $@122: %empty
#line 2881 "dhcp6_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4442 "dhcp6_parser.cc"
    break;

  case 837: // http_headers: "http-headers" $@122 ":" "[" http_header_list "]"
#line 2887 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4451 "dhcp6_parser.cc"
    break;

  case 842: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2898 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4459 "dhcp6_parser.cc"
    break;

  case 843: // $@123: %empty
#line 2903 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4469 "dhcp6_parser.cc"
    break;

  case 844: // http_header: "{" $@123 http_header_params "}"
#line 2907 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4477 "dhcp6_parser.cc"
    break;

  case 847: // http_header_params: http_header_params ","
#line 2913 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4485 "dhcp6_parser.cc"
    break;

  case 853: // $@124: %empty
#line 2925 "dhcp6_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4494 "dhcp6_parser.cc"
    break;

  case 854: // header_value: "value" $@124 ":" "constant string"
#line 2928 "dhcp6_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4504 "dhcp6_parser.cc"
    break;

  case 855: // $@125: %empty
#line 2936 "dhcp6_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4516 "dhcp6_parser.cc"
    break;

  case 856: // authentication: "authentication" $@125 ":" "{" auth_params "}"
#line 2942 "dhcp6_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4527 "dhcp6_parser.cc"
    break;

  case 859: // auth_params: auth_params ","
#line 2951 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4535 "dhcp6_parser.cc"
    break;

  case 867: // $@126: %empty
#line 2965 "dhcp6_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4544 "dhcp6_parser.cc"
    break;

  case 868: // auth_type: "type" $@126 ":" auth_type_value
#line 2968 "dhcp6_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4553 "dhcp6_parser.cc"
    break;

  case 869: // auth_type_value: "basic"
#line 2973 "dhcp6_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4559 "dhcp6_parser.cc"
    break;

  case 870: // $@127: %empty
#line 2976 "dhcp6_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4568 "dhcp6_parser.cc"
    break;

  case 871: // realm: "realm" $@127 ":" "constant string"
#line 2979 "dhcp6_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4578 "dhcp6_parser.cc"
    break;

  case 872: // $@128: %empty
#line 2985 "dhcp6_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4587 "dhcp6_parser.cc"
    break;

  case 873: // directory: "directory" $@128 ":" "constant string"
#line 2988 "dhcp6_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4597 "dhcp6_parser.cc"
    break;

  case 874: // $@129: %empty
#line 2994 "dhcp6_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4609 "dhcp6_parser.cc"
    break;

  case 875: // clients: "clients" $@129 ":" "[" clients_list "]"
#line 3000 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4618 "dhcp6_parser.cc"
    break;

  case 880: // not_empty_clients_list: not_empty_clients_list ","
#line 3011 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4626 "dhcp6_parser.cc"
    break;

  case 881: // $@130: %empty
#line 3016 "dhcp6_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4636 "dhcp6_parser.cc"
    break;

  case 882: // basic_auth: "{" $@130 clients_params "}"
#line 3020 "dhcp6_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4644 "dhcp6_parser.cc"
    break;

  case 885: // clients_params: clients_params ","
#line 3026 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4652 "dhcp6_parser.cc"
    break;

  case 893: // $@131: %empty
#line 3040 "dhcp6_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4661 "dhcp6_parser.cc"
    break;

  case 894: // user_file: "user-file" $@131 ":" "constant string"
#line 3043 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4671 "dhcp6_parser.cc"
    break;

  case 895: // $@132: %empty
#line 3051 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4683 "dhcp6_parser.cc"
    break;

  case 896: // dhcp_queue_control: "dhcp-queue-control" $@132 ":" "{" queue_control_params "}"
#line 3057 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4694 "dhcp6_parser.cc"
    break;

  case 899: // queue_control_params: queue_control_params ","
#line 3066 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4702 "dhcp6_parser.cc"
    break;

  case 906: // enable_queue: "enable-queue" ":" "boolean"
#line 3079 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4712 "dhcp6_parser.cc"
    break;

  case 907: // $@133: %empty
#line 3085 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4721 "dhcp6_parser.cc"
    break;

  case 908: // queue_type: "queue-type" $@133 ":" "constant string"
#line 3088 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4731 "dhcp6_parser.cc"
    break;

  case 909: // capacity: "capacity" ":" "integer"
#line 3094 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4741 "dhcp6_parser.cc"
    break;

  case 910: // $@134: %empty
#line 3100 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4750 "dhcp6_parser.cc"
    break;

  case 911: // arbitrary_map_entry: "constant string" $@134 ":" value
#line 3103 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4759 "dhcp6_parser.cc"
    break;

  case 912: // $@135: %empty
#line 3110 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4771 "dhcp6_parser.cc"
    break;

  case 913: // dhcp_ddns: "dhcp-ddns" $@135 ":" "{" dhcp_ddns_params "}"
#line 3116 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4782 "dhcp6_parser.cc"
    break;

  case 914: // $@136: %empty
#line 3123 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4792 "dhcp6_parser.cc"
    break;

  case 915: // sub_dhcp_ddns: "{" $@136 dhcp_ddns_params "}"
#line 3127 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4802 "dhcp6_parser.cc"
    break;

  case 918: // dhcp_ddns_params: dhcp_ddns_params ","
#line 3135 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4810 "dhcp6_parser.cc"
    break;

  case 930: // enable_updates: "enable-updates" ":" "boolean"
#line 3153 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4820 "dhcp6_parser.cc"
    break;

  case 931: // $@137: %empty
#line 3159 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4829 "dhcp6_parser.cc"
    break;

  case 932: // server_ip: "server-ip" $@137 ":" "constant string"
#line 3162 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4839 "dhcp6_parser.cc"
    break;

  case 933: // server_port: "server-port" ":" "integer"
#line 3168 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4849 "dhcp6_parser.cc"
    break;

  case 934: // $@138: %empty
#line 3174 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4858 "dhcp6_parser.cc"
    break;

  case 935: // sender_ip: "sender-ip" $@138 ":" "constant string"
#line 3177 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4868 "dhcp6_parser.cc"
    break;

  case 936: // sender_port: "sender-port" ":" "integer"
#line 3183 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4878 "dhcp6_parser.cc"
    break;

  case 937: // max_queue_size: "max-queue-size" ":" "integer"
#line 3189 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4888 "dhcp6_parser.cc"
    break;

  case 938: // $@139: %empty
#line 3195 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4897 "dhcp6_parser.cc"
    break;

  case 939: // ncr_protocol: "ncr-protocol" $@139 ":" ncr_protocol_value
#line 3198 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4906 "dhcp6_parser.cc"
    break;

  case 940: // ncr_protocol_value: "UDP"
#line 3204 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4912 "dhcp6_parser.cc"
    break;

  case 941: // ncr_protocol_value: "TCP"
#line 3205 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4918 "dhcp6_parser.cc"
    break;

  case 942: // $@140: %empty
#line 3208 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4927 "dhcp6_parser.cc"
    break;

  case 943: // ncr_format: "ncr-format" $@140 ":" "JSON"
#line 3211 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4937 "dhcp6_parser.cc"
    break;

  case 944: // $@141: %empty
#line 3219 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4949 "dhcp6_parser.cc"
    break;

  case 945: // config_control: "config-control" $@141 ":" "{" config_control_params "}"
#line 3225 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4959 "dhcp6_parser.cc"
    break;

  case 946: // $@142: %empty
#line 3231 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4969 "dhcp6_parser.cc"
    break;

  case 947: // sub_config_control: "{" $@142 config_control_params "}"
#line 3235 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4978 "dhcp6_parser.cc"
    break;

  case 950: // config_control_params: config_control_params ","
#line 3243 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4986 "dhcp6_parser.cc"
    break;

  case 953: // $@143: %empty
#line 3253 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4998 "dhcp6_parser.cc"
    break;

  case 954: // config_databases: "config-databases" $@143 ":" "[" database_list "]"
#line 3259 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5007 "dhcp6_parser.cc"
    break;

  case 955: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3264 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 5017 "dhcp6_parser.cc"
    break;

  case 956: // $@144: %empty
#line 3272 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 5029 "dhcp6_parser.cc"
    break;

  case 957: // loggers: "loggers" $@144 ":" "[" loggers_entries "]"
#line 3278 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5038 "dhcp6_parser.cc"
    break;

  case 960: // loggers_entries: loggers_entries ","
#line 3287 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 5046 "dhcp6_parser.cc"
    break;

  case 961: // $@145: %empty
#line 3293 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 5056 "dhcp6_parser.cc"
    break;

  case 962: // logger_entry: "{" $@145 logger_params "}"
#line 3297 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 5064 "dhcp6_parser.cc"
    break;

  case 965: // logger_params: logger_params ","
#line 3303 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 5072 "dhcp6_parser.cc"
    break;

  case 973: // debuglevel: "debuglevel" ":" "integer"
#line 3317 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 5082 "dhcp6_parser.cc"
    break;

  case 974: // $@146: %empty
#line 3323 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5091 "dhcp6_parser.cc"
    break;

  case 975: // severity: "severity" $@146 ":" "constant string"
#line 3326 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 5101 "dhcp6_parser.cc"
    break;

  case 976: // $@147: %empty
#line 3332 "dhcp6_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 5113 "dhcp6_parser.cc"
    break;

  case 977: // output_options_list: "output-options" $@147 ":" "[" output_options_list_content "]"
#line 3338 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5122 "dhcp6_parser.cc"
    break;

  case 980: // output_options_list_content: output_options_list_content ","
#line 3345 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 5130 "dhcp6_parser.cc"
    break;

  case 981: // $@148: %empty
#line 3350 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 5140 "dhcp6_parser.cc"
    break;

  case 982: // output_entry: "{" $@148 output_params_list "}"
#line 3354 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 5148 "dhcp6_parser.cc"
    break;

  case 985: // output_params_list: output_params_list ","
#line 3360 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 5156 "dhcp6_parser.cc"
    break;

  case 991: // $@149: %empty
#line 3372 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5165 "dhcp6_parser.cc"
    break;

  case 992: // output: "output" $@149 ":" "constant string"
#line 3375 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5175 "dhcp6_parser.cc"
    break;

  case 993: // flush: "flush" ":" "boolean"
#line 3381 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5185 "dhcp6_parser.cc"
    break;

  case 994: // maxsize: "maxsize" ":" "integer"
#line 3387 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5195 "dhcp6_parser.cc"
    break;

  case 995: // maxver: "maxver" ":" "integer"
#line 3393 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5205 "dhcp6_parser.cc"
    break;

  case 996: // $@150: %empty
#line 3399 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5214 "dhcp6_parser.cc"
    break;

  case 997: // pattern: "pattern" $@150 ":" "constant string"
#line 3402 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5224 "dhcp6_parser.cc"
    break;

  case 998: // $@151: %empty
#line 3408 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5236 "dhcp6_parser.cc"
    break;

  case 999: // compatibility: "compatibility" $@151 ":" "{" compatibility_params "}"
#line 3414 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5245 "dhcp6_parser.cc"
    break;

  case 1002: // compatibility_params: compatibility_params ","
#line 3421 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5253 "dhcp6_parser.cc"
    break;

  case 1005: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3430 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5263 "dhcp6_parser.cc"
    break;


#line 5267 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1448;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     551, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448,    48,    36,    55,    58,    83,
     139,   177,   184,   197,   241,   250,   252,   274,   276,   285,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,    36,  -168,
      78,   284,    35,   746,  1408,   331,   610,     7,   155,   286,
     -81,   536,   108, -1448,   106,    96,   158,   279,   291, -1448,
      79, -1448, -1448, -1448, -1448, -1448, -1448, -1448,   306,   317,
     333,   369,   385,   401,   402,   451,   455,   461,   462,   473,
     486,   498,   500, -1448,   502,   504,   507,   512,   513, -1448,
   -1448, -1448, -1448,   514,   522,   525,   526,   528,   529,   535,
   -1448, -1448, -1448,   544, -1448, -1448, -1448, -1448, -1448, -1448,
     546,   548,   549, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448,   550, -1448, -1448, -1448, -1448, -1448, -1448,   553,
     554,   556,   557, -1448, -1448,   558, -1448,   115, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448,   560,   561,   563,   564, -1448,   128, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448,   567,   568, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448,   173, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448,   570, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448,   182, -1448, -1448, -1448, -1448, -1448, -1448,   571, -1448,
     574,   575, -1448, -1448, -1448, -1448, -1448, -1448, -1448,   205,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,   444,   472,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,   493,
   -1448, -1448,   577, -1448, -1448, -1448,   578, -1448, -1448,   532,
     580, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448,   581,   584,   585, -1448, -1448, -1448,
   -1448, -1448,   582,   589, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,   242, -1448,
   -1448, -1448,   591, -1448,   592, -1448,   594,   596, -1448, -1448,
   -1448, -1448, -1448,   246, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448,   597,   255, -1448, -1448, -1448, -1448,
      36,    36, -1448,   354,   600, -1448, -1448,   601,   602,   604,
     605,   607,   608,   375,   378,   382,   384,   388,   392,   397,
     399,   377,   406,   408,   419,   403,   426,   423,   638,   428,
     430,   417,   429,   431,   661,   662,   670,   672,   436,   437,
     440,   442,   443,   445,   446,   680,   683,   685,   452,   686,
     687,   690,   691,   692,   693,   457,   460,   463,   697,   700,
     702,   703,   704,   705,   712,   713,   714,   479,   716,   717,
     718,   719,   720,   721,   495,   496,   499,   506,   742,   752,
   -1448,   284, -1448,   753,   516,   519,   523,   530,    35, -1448,
     758,   762,   765,   767,   770,   576,   552,   789,   793,   810,
     746, -1448,   811,   593,  1408, -1448,   813,   595,   828,   598,
     599,   331, -1448,   832,   833,   836,   837,   838,   839,   840,
     841, -1448,   610, -1448,   846,   847,   612,   849,   851,   853,
     616, -1448,   155,   855,   618,   619,   630,   869, -1448,   286,
     870,   871,    63, -1448,   634,   873,   640,   877,   642,   643,
     881,   882,   536, -1448,   883,   648,   108, -1448, -1448, -1448,
     885,   884,   651,   886,   887,   889,   890,   893, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448,   660, -1448, -1448, -1448, -1448, -1448,  -127,
     663,   664,   665, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
     895,   896,   900, -1448,   667,   668,     5,   903,   902,   688,
   -1448, -1448, -1448,   919,   920,   921,   936,   941,   942,   943,
     944,   945, -1448,   946,   954,   953,   955,   710,   711, -1448,
   -1448, -1448, -1448,   956,   957, -1448,   958, -1448, -1448, -1448,
   -1448, -1448,   960,   961,   728,   729,   730, -1448, -1448,   958,
     958,   963, -1448,   732, -1448, -1448,   735, -1448,   738, -1448,
   -1448, -1448,   958,   958,   958,   958,   743,   744,   745,   747,
   -1448,   748,   751, -1448,   754,   755,   756, -1448, -1448,   757,
   -1448, -1448, -1448,   958, -1448,   759,   902, -1448, -1448,   760,
   -1448,   761, -1448, -1448,   -28,   788, -1448,   987, -1448, -1448,
      36,   284, -1448,   108,    35,   190,   190,   990, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,   994,   996,
     997, -1448, -1448, -1448, -1448, -1448, -1448, -1448,   998, -1448,
   -1448, -1448,   -96,    36,   346,   199,   999,  1001,  1002,    47,
     153,    93,  1004,   280,   536, -1448, -1448,  1005,  -143, -1448,
   -1448,  1007,  1008, -1448, -1448, -1448, -1448, -1448,   879, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448,   990, -1448,   265,   277,   290,
   -1448, -1448, -1448, -1448,  1015,  1019,  1021,  1025,  1026,  1032,
    1033,  1036,  1039,  1042, -1448,  1043,  1044, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,   301,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448,   305, -1448,  1053,  1057, -1448,
   -1448,  1056,  1065, -1448, -1448,  1068,  1080, -1448, -1448,  1079,
    1096, -1448, -1448,  1094,  1105, -1448, -1448, -1448,    89, -1448,
   -1448, -1448,  1104, -1448, -1448, -1448,   150, -1448, -1448, -1448,
   -1448, -1448,   315, -1448, -1448, -1448, -1448,  1111,  1116, -1448,
   -1448,  1119,  1125, -1448, -1448,  1130,  1138, -1448,  1118,  1141,
    1143,  1146,  1151,  1152,   325, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448,  1163,  1178,  1180, -1448, -1448, -1448,
   -1448,   328, -1448, -1448, -1448, -1448, -1448, -1448,  1187,  1191,
    1192, -1448,   379, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
    1195,  1199, -1448,  1200, -1448,  1201, -1448, -1448, -1448,   387,
   -1448, -1448, -1448, -1448, -1448,   390, -1448,   160, -1448,  1203,
   -1448,   396, -1448, -1448,   970, -1448,  1204,  1209, -1448, -1448,
    1208,  1212, -1448, -1448,  1211,  1210, -1448, -1448, -1448,  1213,
    1216,  1218,  1220,   985,   984,   989,   988,   991,   992,   993,
     995,  1000,  1003,  1223,  1006,  1009,  1230,  1232,  1233,  1234,
    1235,  1237,   190, -1448, -1448,   190, -1448,   990,   746, -1448,
     994,   155, -1448,   996,   286, -1448,   997,   856, -1448,   998,
     -96, -1448, -1448,   346, -1448,  1238,  1240,   199, -1448,   656,
   -1448,   999,   610, -1448,  1001,   -81, -1448,  1002,  1010,  1011,
    1012,  1013,  1014,  1016,    47, -1448,  1241,  1242,  1017,  1018,
    1020,   153, -1448,  1022,  1023,  1027,    93, -1448,   149, -1448,
    1004,  1024,  1243,  1028,  1251,   280, -1448, -1448,   -47,  1005,
   -1448,  1029,  -143, -1448, -1448,  1255,  1262,  1408, -1448,  1007,
     331, -1448,  1008, -1448, -1448,  1030,  1031,  1034,  1035, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,   261,
   -1448, -1448,  1037,  1038,  1040,   434,  1041,  1045, -1448,   412,
   -1448,   418, -1448,  1264, -1448,  1267, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448,   422, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
    1046,  1047, -1448, -1448, -1448,  1274, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448,  1273,  1280, -1448,
   -1448, -1448, -1448, -1448, -1448,  1279, -1448,   424, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448,   355,  1049, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,  1285,
   -1448,  1287, -1448, -1448, -1448, -1448, -1448, -1448, -1448,   425,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
    1055, -1448,    36, -1448, -1448,  1291, -1448, -1448, -1448, -1448,
   -1448,   432, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
    1058,   448, -1448,   450, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448,   856, -1448, -1448, -1448,  1292,  1294,  1061,
   -1448,   656, -1448, -1448, -1448, -1448, -1448, -1448, -1448,  1296,
    1300,  1302,  1069,  1304,  1071,  1306,   149, -1448, -1448, -1448,
    1307,  1074,  1312,   -47, -1448, -1448, -1448, -1448, -1448,  1082,
    1083, -1448, -1448,    57,  1086,  1087, -1448,  1311, -1448,  1314,
   -1448,  1323, -1448,  1090, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448,    25,  1324,  1326, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448,   459, -1448, -1448, -1448, -1448, -1448,
   -1448,  1328,  1333, -1448, -1448,   411, -1448,  1335,  1336,  1337,
    1339,    25, -1448,    80, -1448,  1324,  -115,  1326, -1448,  1165,
    1106,  1108,  1343, -1448, -1448, -1448, -1448, -1448, -1448,   470,
   -1448, -1448, -1448, -1448,  1345,  1346,  1347, -1448,   471, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
    1348,  1349,    80, -1448,  1350,  1115,  1122,  1126,  1354,  -115,
   -1448, -1448,  1353,  1362, -1448,  1134, -1448,  1135, -1448, -1448,
   -1448,  1136, -1448,    72, -1448,  1348, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448,   497, -1448, -1448, -1448,
    1372,    72, -1448,  1139, -1448, -1448
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   211,     9,   408,    11,
     626,    13,   670,    15,   703,    17,   541,    19,   550,    21,
     589,    23,   370,    25,   914,    27,   946,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   705,     0,   552,   591,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   146,   944,   209,   230,   232,   234,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   198,     0,     0,     0,     0,     0,   166,
     173,   175,   177,     0,     0,     0,     0,     0,     0,     0,
     399,   539,   580,     0,   201,   203,   181,   479,   657,   659,
       0,     0,     0,   326,   345,   335,   315,   741,   694,   361,
     382,   775,     0,   347,   800,   895,   912,   191,   193,     0,
       0,     0,     0,   956,   998,     0,   145,     0,    69,    72,
      73,    74,    75,    76,    77,    78,    79,    80,   110,   111,
     112,   113,   114,   115,    81,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   117,
     118,   133,   134,   135,   106,   142,   143,   144,   137,   138,
     139,   140,    84,    85,    86,    87,   103,    88,    90,    89,
     136,    94,    95,    82,   107,   108,   109,    83,    92,    93,
     101,   102,   104,    91,    96,    97,    98,    99,   100,   105,
     116,   141,   224,     0,     0,     0,     0,   223,     0,   213,
     216,   217,   218,   219,   220,   221,   222,   617,   661,   464,
     466,   468,     0,     0,   470,   472,   738,   463,   413,   414,
     415,   416,   417,   418,   419,   420,   438,   439,   440,   441,
     442,   443,   446,   447,   448,   449,   450,   451,   452,   453,
     454,   455,   456,   457,   458,   459,   444,   445,   460,   461,
     462,     0,   410,   424,   425,   426,   429,   430,   432,   433,
     434,   427,   428,   421,   422,   436,   437,   423,   431,   435,
     654,     0,   653,   636,   637,   638,   639,   640,   641,   642,
     643,   644,   645,   646,   647,   648,   649,   650,   634,   635,
     633,     0,   628,   631,   632,   651,   652,   687,     0,   690,
       0,     0,   686,   680,   681,   679,   678,   684,   685,     0,
     672,   675,   676,   682,   683,   677,   736,   722,   724,   726,
     728,   730,   732,   734,   721,   718,   719,   720,     0,   706,
     707,   712,   713,   714,   710,   715,   716,   717,   711,     0,
     570,   282,     0,   574,   572,   577,     0,   566,   567,     0,
     553,   554,   557,   569,   558,   559,   560,   576,   561,   562,
     563,   564,   565,   608,     0,     0,     0,   615,   606,   607,
     610,   611,     0,   592,   593,   596,   597,   598,   599,   600,
     601,   602,   605,   603,   604,   378,   380,   375,     0,   372,
     376,   377,     0,   931,     0,   934,     0,     0,   938,   942,
     929,   927,   928,     0,   916,   919,   920,   921,   922,   923,
     924,   925,   926,   953,     0,     0,   948,   951,   952,    47,
      52,     0,    39,    45,     0,    66,    62,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      60,    71,    68,     0,     0,     0,     0,     0,   215,   212,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     412,   409,     0,     0,   630,   627,     0,     0,     0,     0,
       0,   674,   671,     0,     0,     0,     0,     0,     0,     0,
       0,   704,   709,   542,     0,     0,     0,     0,     0,     0,
       0,   551,   556,     0,     0,     0,     0,     0,   590,   595,
       0,     0,   374,   371,     0,     0,     0,     0,     0,     0,
       0,     0,   918,   915,     0,     0,   950,   947,    51,    43,
       0,     0,     0,     0,     0,     0,     0,     0,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,     0,   196,   197,   163,   164,   165,     0,
       0,     0,     0,   179,   180,   187,   188,   189,   190,   195,
       0,     0,     0,   200,     0,     0,     0,     0,     0,     0,
     474,   475,   476,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   799,     0,     0,     0,     0,     0,     0,   205,
     206,   207,   208,     0,     0,    70,     0,   226,   227,   228,
     229,   214,     0,     0,     0,     0,     0,   477,   478,     0,
       0,     0,   411,     0,   656,   629,     0,   689,     0,   692,
     693,   673,     0,     0,     0,     0,     0,     0,     0,     0,
     708,     0,     0,   568,     0,     0,     0,   579,   555,     0,
     612,   613,   614,     0,   594,     0,     0,   373,   930,     0,
     933,     0,   936,   937,     0,     0,   917,     0,   955,   949,
       0,     0,   147,     0,     0,     0,     0,   236,   199,   168,
     169,   170,   171,   172,   167,   174,   176,   178,   401,   543,
     582,   202,   204,   183,   184,   185,   186,   182,   481,    40,
     658,   660,     0,    48,     0,     0,   743,   696,   363,     0,
       0,     0,   802,     0,     0,   192,   194,     0,     0,    53,
     225,   619,   663,   465,   467,   469,   471,   473,     0,   655,
     688,   691,   737,   723,   725,   727,   729,   731,   733,   735,
     571,   283,   575,   573,   578,   609,   616,   379,   381,   932,
     935,   940,   941,   939,   943,   236,    44,     0,     0,     0,
     271,   273,   275,   279,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   292,     0,     0,   300,   302,   304,
     306,   308,   309,   310,   311,   312,   313,   277,   270,     0,
     243,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   261,   262,   263,   264,   260,
     265,   266,   267,   268,   269,     0,   241,     0,   237,   238,
     406,     0,   402,   403,   548,     0,   544,   545,   587,     0,
     583,   584,   486,     0,   482,   483,   333,   334,     0,   328,
     331,   332,     0,   343,   344,   340,     0,   337,   341,   342,
     322,   324,     0,   317,   320,   321,   748,     0,   744,   745,
     701,     0,   697,   698,   368,     0,   364,   365,     0,     0,
       0,     0,     0,     0,     0,   384,   387,   388,   389,   390,
     391,   392,   789,   795,     0,     0,     0,   788,   785,   786,
     787,     0,   777,   780,   783,   781,   782,   784,     0,     0,
       0,   357,     0,   349,   352,   353,   354,   355,   356,   807,
       0,   803,   804,     0,   907,     0,   910,   903,   904,     0,
     897,   900,   901,   902,   905,     0,   961,     0,   958,     0,
    1004,     0,  1000,  1003,    55,   624,     0,   620,   621,   668,
       0,   664,   665,   740,     0,     0,    64,   945,   210,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   245,   231,   233,     0,   235,   240,     0,   400,
     405,   552,   540,   547,   591,   581,   586,     0,   480,   485,
     330,   327,   346,   339,   336,     0,     0,   319,   316,   750,
     742,   747,   705,   695,   700,     0,   362,   367,     0,     0,
       0,     0,     0,     0,   386,   383,     0,     0,     0,     0,
       0,   779,   776,     0,     0,     0,   351,   348,     0,   801,
     806,     0,     0,     0,     0,   899,   896,   913,     0,   960,
     957,     0,  1002,   999,    57,     0,    56,     0,   618,   623,
       0,   662,   667,   739,   954,     0,     0,     0,     0,   281,
     284,   285,   286,   287,   288,   289,   290,   299,   291,     0,
     297,   298,     0,     0,     0,     0,     0,     0,   244,     0,
     239,     0,   404,     0,   546,     0,   585,   538,   504,   505,
     506,   508,   509,   510,   495,   496,   513,   514,   515,   516,
     517,   518,   521,   522,   523,   524,   525,   526,   527,   528,
     529,   530,   531,   532,   533,   534,   519,   520,   535,   536,
     537,   491,   492,   493,   494,   502,   503,   499,   500,   501,
     507,     0,   488,   497,   511,   512,   498,   484,   329,   338,
       0,     0,   318,   770,   772,     0,   768,   762,   763,   764,
     765,   766,   767,   769,   759,   760,   761,     0,   751,   752,
     755,   756,   757,   758,   746,     0,   699,     0,   366,   393,
     394,   395,   396,   397,   398,   385,     0,     0,   794,   797,
     798,   778,   358,   359,   360,   350,   825,   830,   832,     0,
     855,     0,   836,   824,   817,   818,   819,   822,   823,     0,
     809,   812,   813,   814,   815,   820,   821,   816,   805,   906,
       0,   909,     0,   898,   976,     0,   974,   972,   966,   970,
     971,     0,   963,   968,   969,   967,   959,  1005,  1001,    54,
      59,     0,   622,     0,   666,   272,   274,   276,   280,   294,
     295,   296,   293,   301,   303,   305,   307,   314,   278,   242,
     407,   549,   588,   490,   487,   323,   325,     0,     0,     0,
     749,   754,   702,   369,   791,   792,   793,   790,   796,     0,
       0,     0,     0,     0,     0,     0,   811,   808,   908,   911,
       0,     0,     0,   965,   962,    58,   625,   669,   489,     0,
       0,   774,   753,     0,     0,     0,   834,     0,   835,     0,
     810,     0,   973,     0,   964,   771,   773,   827,   828,   829,
     826,   831,   833,     0,   838,     0,   975,   867,   870,   872,
     874,   866,   865,   864,     0,   857,   860,   861,   862,   863,
     843,     0,   839,   840,   981,     0,   978,     0,     0,     0,
       0,   859,   856,     0,   837,   842,     0,   980,   977,     0,
       0,     0,     0,   858,   853,   852,   848,   850,   851,     0,
     845,   849,   841,   991,     0,     0,     0,   996,     0,   983,
     986,   987,   988,   989,   990,   979,   869,   868,   871,   873,
     876,     0,   847,   844,     0,     0,     0,     0,     0,   985,
     982,   881,     0,   877,   878,     0,   846,     0,   993,   994,
     995,     0,   984,     0,   875,   880,   854,   992,   997,   893,
     892,   886,   888,   889,   890,   891,     0,   883,   887,   879,
       0,   885,   882,     0,   884,   894
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448,   -10, -1448,  -628, -1448,
     623, -1448, -1448, -1448, -1448,   583, -1448,  -296, -1448, -1448,
   -1448,   -71, -1448, -1448, -1448, -1448, -1448, -1448, -1448,   613,
     830, -1448, -1448,   -29,   -26,    -1,     3,    16,    27,   -61,
     -36,   -33,    84,    86,    87,    88,    91, -1448,    29,    40,
      43,    46, -1448, -1448,    51, -1448,    53, -1448,    56, -1448,
      59,    92,    61, -1448, -1448,    64,    66,    71,    74,    76,
   -1448,    81, -1448,    94, -1448, -1448, -1448, -1448, -1448,    99,
   -1448,   102, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448,   611,   829, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448,   534, -1448,   313, -1448,  -763,
     319, -1448, -1448, -1447, -1448, -1430, -1448, -1428, -1448, -1448,
   -1448, -1448,   -60, -1448,  -799, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1094, -1448,
   -1092, -1448, -1090, -1448,   217, -1448, -1448, -1448, -1448, -1448,
   -1448,   297, -1448, -1448, -1448, -1448, -1448, -1448, -1448,   310,
    -790, -1448, -1448, -1448, -1448,   308, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448,   281, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448,   295, -1448, -1448, -1448,   298,   796, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448,   296, -1448, -1448, -1448, -1448, -1448,
   -1448, -1065, -1448, -1448, -1448,   335, -1448, -1448, -1448,   327,
     843, -1448, -1448, -1064, -1448, -1063, -1448,   -54, -1448,   112,
   -1448,   105,   107,   110, -1448, -1062, -1448, -1448, -1448, -1448,
     329, -1448, -1448,    67,  1344, -1448, -1448, -1448, -1448, -1448,
     340, -1448, -1448, -1448,   344, -1448,   814, -1448,   -64, -1448,
   -1448, -1448, -1448, -1448,   -62, -1448, -1448, -1448, -1448, -1448,
      10, -1448, -1448, -1448,   345, -1448, -1448, -1448,   349, -1448,
     821, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448,   289, -1448, -1448, -1448,   288,
     868, -1448, -1448,   -59,   -46, -1448,   -15, -1448, -1448, -1448,
   -1448, -1448,   294, -1448, -1448, -1448,   293,   867, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448,   -34, -1448, -1448, -1448,   347,
   -1448, -1448, -1448,   351, -1448,   857,   626, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1056, -1448, -1448, -1448, -1448, -1448, -1448,   358,
   -1448, -1448, -1448,    95, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448,   341, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448,   334, -1448, -1448,
      85, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448,    21, -1448, -1448,   -14, -1448, -1448,
   -1448, -1448, -1448,    28, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448,   -35, -1448, -1448,   -50, -1448,
   -1448, -1448, -1448, -1448,   337, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448,   659,   852, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448,   706,   850, -1448, -1448, -1448, -1448,
   -1448, -1448,   338, -1448, -1448,   111, -1448, -1448, -1448, -1448,
   -1448, -1448,    31, -1448, -1448,     4, -1448, -1448, -1448, -1448,
   -1448, -1448, -1448, -1448, -1448, -1448,   353, -1448
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     800,    87,    88,    41,    68,    84,    85,   820,  1034,  1145,
    1146,   888,    43,    70,    90,   474,    91,    45,    71,   167,
     168,   169,   477,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   504,   784,   189,   505,   190,   506,   191,   507,
     192,   193,   194,   521,   797,   195,   196,   197,   198,   199,
     542,   200,   543,   201,   202,   203,   204,   498,   205,   206,
     519,   207,   520,   208,   209,   210,   211,   212,   479,    47,
      72,   248,   249,   250,   553,   251,   252,   253,   254,   213,
     480,   214,   481,   215,   482,   917,   918,   919,  1075,   889,
     890,   891,  1049,   892,  1050,   893,  1051,   894,  1071,   895,
    1052,   896,   897,   595,   898,   899,   900,   901,   902,   903,
     904,   905,   906,  1063,  1342,   907,   908,   909,   910,  1066,
     911,  1067,   912,  1068,   913,  1069,   914,  1070,   216,   531,
     952,   953,   954,  1095,   955,  1096,   217,   528,   938,   939,
     940,   941,   218,   530,   946,   947,   948,   949,   219,   529,
     220,   538,  1002,  1003,  1004,  1005,  1006,   221,   534,   965,
     966,   967,  1105,    63,    80,   438,   439,   440,   610,   441,
     611,   222,   535,   974,   975,   976,   977,   978,   979,   980,
     981,   223,   515,   921,   922,   923,  1078,    49,    73,   301,
     302,   303,   562,   304,   563,   305,   564,   306,   567,   307,
     568,   224,   225,   226,   311,   312,   227,   522,   933,   934,
     935,  1087,  1231,  1232,   228,   516,    57,    77,   925,   926,
     927,  1081,    59,    78,   399,   400,   401,   402,   403,   404,
     405,   594,   406,   598,   407,   597,   408,   409,   599,   410,
     229,   517,   929,   930,   931,  1084,    61,    79,   422,   423,
     424,   425,   426,   603,   427,   428,   429,   430,   431,   432,
     607,   314,   560,  1036,  1037,  1038,  1147,    51,    74,   341,
     342,   343,   572,   344,   230,   523,   231,   524,   317,   561,
    1040,  1041,  1042,  1150,    53,    75,   359,   360,   361,   576,
     362,   363,   578,   364,   365,   232,   533,   961,   962,   963,
    1102,    55,    76,   378,   379,   380,   381,   584,   382,   585,
     383,   586,   384,   587,   385,   588,   386,   589,   387,   590,
     388,   583,   319,   569,  1044,   233,   532,   957,   958,   959,
    1099,  1257,  1258,  1259,  1260,  1261,  1357,  1262,  1358,  1263,
     234,   536,   991,   992,   993,  1116,  1367,   994,   995,  1117,
     996,   997,   235,   236,   539,  1010,  1011,  1012,  1128,  1299,
    1300,  1301,  1369,  1410,  1302,  1370,  1303,  1371,  1304,  1305,
    1306,  1375,  1431,  1432,  1433,  1443,  1459,  1460,  1461,  1481,
    1307,  1373,  1424,  1425,  1426,  1437,  1477,  1427,  1438,  1428,
    1439,  1429,  1440,  1492,  1493,  1494,  1503,  1516,  1517,  1518,
    1520,   237,   540,  1019,  1020,  1021,  1022,  1132,  1023,  1024,
    1134,   238,   541,    65,    81,   453,   454,   455,   456,   615,
     457,   458,   617,   459,   460,   461,   620,   853,   462,   621,
     239,   478,    67,    82,   465,   466,   467,   624,   468,   240,
     548,  1027,  1028,  1138,  1321,  1322,  1323,  1324,  1382,  1325,
    1380,  1435,  1436,  1446,  1468,  1469,  1470,  1484,  1471,  1472,
    1473,  1474,  1488,   241,   549,  1031,  1032,  1033
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     166,   247,   267,   322,   352,   374,    38,   397,   418,   437,
     450,   988,   274,   915,   945,   420,   356,   421,   398,   419,
     338,   353,  1222,  1223,  1224,  1230,   255,   315,   345,   357,
     376,  1236,   411,   433,  1294,   451,  1295,   275,  1296,   318,
     276,    31,   391,    32,   268,    33,   936,   269,    30,  1417,
     799,   242,   243,   244,   245,   246,  1511,   256,   316,   346,
     358,   377,    42,   412,   434,    44,   452,   435,   436,   138,
     139,    86,   270,  1512,  1511,  1513,   271,   779,   780,   781,
     782,  1029,   475,   313,   340,   355,   375,   476,    89,   272,
      46,  1512,  1090,  1513,   131,  1091,   165,   861,   862,   470,
     273,  1463,   282,   323,  1464,  1465,  1466,  1467,   793,   794,
     795,   796,   469,   283,   324,   783,   284,   325,   551,   285,
     326,   463,   464,   552,   286,   327,   287,   328,   799,   288,
     329,   558,   289,   330,   291,   331,   559,   292,   332,   293,
     333,   138,   139,   937,   294,   334,    48,   295,   335,   296,
     336,   138,   139,  1093,   297,   337,  1094,   277,   165,   278,
     279,   280,   471,  1139,   281,   290,  1140,   298,  1314,   391,
    1315,  1316,   299,   851,   852,   300,   570,   982,   308,   390,
     309,   571,   865,   310,    50,   574,   339,   354,   138,   139,
     575,    52,   165,   877,   878,   879,   138,   139,   968,   969,
     970,   971,   972,   973,    54,  1418,  1419,  1420,   581,   138,
     139,   435,   436,   582,   860,   861,   862,   863,   864,   865,
     866,   867,   868,   869,   870,   871,   872,   873,   874,  1407,
    1408,  1409,   875,   876,   877,   878,   879,   880,   881,   882,
     883,   884,   885,   886,   391,   612,   392,   393,    56,   622,
     613,   394,   395,   396,   623,  1509,   887,    58,   626,    60,
     998,   999,  1000,   627,   165,   138,   139,  1454,   551,   138,
     139,   138,   139,  1046,   165,    34,    35,    36,    37,   391,
     626,    62,  1294,    64,  1295,  1047,  1296,   472,  1222,  1223,
    1224,  1230,    66,   558,   473,    92,    93,  1236,  1048,    94,
    1339,  1340,  1341,   945,  1072,    95,    96,    97,  1072,  1073,
     483,   165,  1179,  1074,   983,   984,   985,   986,  1097,   165,
    1286,   484,   988,  1098,  1287,  1288,  1289,  1290,  1114,   950,
     951,  1121,   165,  1115,  1291,  1292,  1122,   485,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   486,   887,   391,   413,   392,   393,   414,
     415,   416,  1126,   133,   134,   135,   136,  1127,   165,   487,
    1135,   137,   165,   622,   165,  1136,   138,   139,  1137,  1142,
     138,   139,   138,   139,  1143,   488,   489,   140,   141,   142,
     143,   144,   145,   146,  1447,  1072,   147,  1448,   417,   132,
    1349,   570,   148,   826,   827,  1353,  1350,   612,  1376,   165,
    1354,   149,  1363,  1377,   150,  1383,   832,   833,   834,   835,
    1384,   151,   347,   348,   349,   350,   351,   138,   139,   152,
     153,   574,   591,   581,   154,   490,  1386,   846,  1387,   491,
     628,   629,  1441,   264,   265,   492,   493,  1442,   321,  1013,
    1014,  1015,   155,  1482,  1489,   592,   156,   494,  1483,  1490,
     166,   880,   881,   882,   883,   884,   885,   247,   936,   943,
     495,   944,   157,   158,   159,   160,   161,   162,   163,   267,
    1521,   593,   496,   322,   497,  1522,   499,   164,   500,   274,
     352,   501,   255,  1364,  1365,  1366,   502,   503,   508,  1016,
     338,   374,   356,   165,   315,   165,   509,   353,   345,   510,
     511,   397,   512,   513,   275,   357,   318,   276,   418,   514,
     601,   268,   398,   256,   269,   420,   376,   421,   518,   419,
     525,   450,   526,   527,   537,   316,   411,   544,   545,   346,
     546,   547,   550,   433,   554,   555,   358,   556,   557,   270,
     165,   565,   566,   271,   573,   577,   451,   377,   579,   580,
     313,   596,   600,   602,   340,   604,   272,   412,   605,   606,
     608,   355,   609,   630,   434,   614,   616,   273,   618,   282,
     619,   625,   375,   323,   631,   632,   633,   452,   634,   635,
     283,   636,   637,   284,   324,   638,   285,   325,   639,   646,
     326,   286,   640,   287,   641,   327,   288,   328,   642,   289,
     329,   291,   643,   330,   292,   331,   293,   644,   332,   645,
     333,   294,   653,   650,   295,   334,   296,   647,   335,   648,
     336,   297,   138,   139,   277,   337,   278,   279,   280,   656,
     649,   281,   290,   652,   298,   659,   660,   651,   654,   299,
     655,   657,   300,   658,   661,   308,   662,   309,   663,   664,
     310,   665,   666,   667,   670,   668,   339,   671,   669,   672,
     674,   675,   673,   354,   676,   677,   678,   679,   132,   680,
     166,   683,   681,   247,   684,   682,   685,   686,   687,   688,
      98,    99,   100,   101,   102,   103,   689,   690,   691,   692,
     693,   694,   695,   696,   697,   698,   138,   139,   255,   442,
     443,   444,   445,   446,   447,   448,   449,   699,   700,   987,
    1001,   701,   366,   450,   132,   391,   703,  1030,   702,   367,
     368,   369,   370,   371,   372,   373,   704,   706,   707,   256,
     856,   708,   712,   709,   989,  1007,   713,  1017,   451,   714,
     710,   715,   138,   139,   716,   165,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
    1243,  1244,  1245,   719,   718,   990,  1008,   720,  1018,   452,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   721,   723,   717,   726,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   728,   724,   132,   727,   732,   733,   729,   730,
     734,   735,   736,   737,   738,   739,   134,   135,   136,   165,
     741,   742,   743,   744,   257,   745,   258,   746,   747,   749,
     750,   751,   138,   139,   259,   260,   261,   262,   263,   140,
     141,   142,   752,   753,   755,   756,   758,   759,   264,   265,
     760,   761,   762,   763,   148,   764,   765,   767,   768,   770,
     772,   771,   266,   773,   774,   165,   775,   776,   777,   778,
     788,   789,   785,   786,   787,   790,   791,   792,   798,    32,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   802,   803,   804,   801,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   805,   132,   391,   806,   807,   808,   815,
     816,   809,   810,   811,   157,   158,   134,   135,   136,   812,
     813,   817,   814,   819,   818,   821,   822,   823,   824,   825,
     828,   829,   138,   139,   830,   260,   261,   831,   263,   140,
     141,   142,   836,   837,   838,   165,   839,   840,   264,   265,
     841,   854,   855,   842,   843,   844,   845,   916,   847,   849,
     850,   920,   266,   924,   928,   932,   956,   267,   960,   964,
     397,  1009,  1026,   418,  1035,  1039,  1187,   274,   367,  1053,
     420,   398,   421,  1054,   419,  1055,  1194,  1221,  1246,  1056,
    1057,   374,   315,  1225,   437,   411,  1058,  1059,   433,  1253,
    1060,  1234,   275,  1061,   318,   276,  1062,  1064,  1065,   268,
     987,  1195,   269,  1255,  1196,  1001,   376,  1293,  1188,  1076,
    1077,  1189,  1079,   316,   157,   158,   412,  1317,  1080,   434,
    1247,  1030,  1235,  1248,  1082,   989,   322,   270,  1318,   352,
    1007,   271,  1297,  1083,  1256,  1085,  1190,   377,   313,  1017,
    1191,   356,  1319,   338,   272,   165,   353,  1233,  1249,  1086,
    1088,   345,  1250,  1192,   357,   273,   990,   282,  1089,  1254,
    1092,  1008,   375,  1298,  1193,  1251,  1202,  1100,   283,  1101,
    1018,   284,  1108,  1320,   285,  1103,  1252,  1203,  1104,   286,
    1204,   287,   346,  1205,   288,   358,  1106,   289,  1206,   291,
    1207,  1107,   292,  1208,   293,  1109,  1209,  1110,  1211,   294,
    1111,  1212,   295,  1213,   296,  1112,  1113,   340,  1214,   297,
     355,  1215,   277,  1216,   278,   279,   280,  1118,  1217,   281,
     290,  1197,   298,  1198,  1199,  1200,   323,   299,  1201,  1210,
     300,  1218,  1119,   308,  1120,   309,  1219,   324,   310,  1220,
     325,  1123,  1227,   326,  1228,  1124,  1125,  1229,   327,  1226,
     328,  1129,  1130,   329,  1131,  1133,   330,  1141,   331,  1144,
    1148,   332,  1149,   333,  1151,  1152,  1154,  1155,   334,  1153,
    1156,   335,  1157,   336,  1158,  1159,  1160,  1169,   337,  1161,
    1162,  1163,  1164,  1165,  1172,  1166,  1173,  1174,  1175,  1176,
    1167,  1177,  1240,  1168,  1241,  1276,  1277,  1310,  1170,  1171,
    1269,  1270,  1271,  1272,  1273,  1312,  1274,  1278,  1279,   339,
    1280,  1329,   354,  1283,  1282,  1330,  1309,  1284,  1311,  1335,
    1336,  1327,  1351,  1337,  1338,  1352,  1343,  1344,  1359,  1345,
    1347,  1360,  1187,  1361,  1348,  1355,  1356,  1362,  1368,  1372,
    1246,  1374,  1194,  1221,  1378,  1381,  1389,  1385,  1390,  1225,
    1393,  1253,  1379,  1391,  1394,  1293,  1395,  1234,  1397,  1396,
    1399,  1401,  1317,  1398,  1402,  1255,  1403,  1195,  1413,  1414,
    1196,  1405,  1406,  1318,  1188,  1411,  1412,  1189,  1415,  1416,
    1297,  1430,  1247,  1434,  1444,  1248,  1445,  1319,  1235,  1449,
    1450,  1451,  1421,  1452,  1476,  1478,  1256,  1479,  1480,  1485,
    1486,  1487,  1190,  1495,  1497,  1491,  1191,  1498,  1501,  1504,
    1249,  1298,  1499,  1233,  1250,  1505,  1500,  1422,  1320,  1192,
    1421,  1254,  1455,  1506,  1507,  1508,  1523,  1251,  1525,   848,
    1193,   705,  1202,  1456,   857,   859,   942,   711,  1252,  1045,
    1180,  1178,  1346,  1203,  1242,  1422,  1204,  1457,  1423,  1205,
    1238,  1239,  1268,  1267,  1206,  1181,  1207,  1285,   757,  1208,
    1275,  1455,  1209,   722,  1211,  1182,   748,  1212,  1237,  1213,
    1388,   389,  1456,  1184,  1214,  1183,  1423,  1215,  1458,  1216,
     754,  1186,  1510,  1185,  1217,  1331,  1457,  1197,  1332,  1198,
    1199,  1200,   725,  1333,  1201,  1210,  1334,  1218,   731,   740,
    1510,  1266,  1219,  1265,  1043,  1220,  1392,  1514,  1227,  1264,
    1228,  1400,  1281,  1229,  1308,  1226,  1462,  1458,  1496,  1453,
    1519,  1524,  1313,  1025,   766,  1514,   769,  1326,  1475,   858,
     116,   117,   118,   119,   120,   121,   122,   123,  1515,   125,
     126,   127,   128,  1502,  1404,  1328,   132,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1515,     0,     0,     0,
     136,     0,     0,     0,     0,     0,     0,   320,     0,     0,
       0,     0,     0,     0,   138,   139,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     264,   265,     0,     0,     0,   321,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   157,   158,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   165
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   810,    73,   776,   804,    79,    75,    79,    78,    79,
      74,    75,  1087,  1087,  1087,  1087,    72,    73,    74,    75,
      76,  1087,    78,    79,  1128,    81,  1128,    73,  1128,    73,
      73,     5,    89,     7,    73,     9,   142,    73,     0,    24,
     678,    16,    17,    18,    19,    20,  1503,    72,    73,    74,
      75,    76,     7,    78,    79,     7,    81,   148,   149,   116,
     117,   239,    73,  1503,  1521,  1503,    73,   204,   205,   206,
     207,   224,     3,    73,    74,    75,    76,     8,    10,    73,
       7,  1521,     3,  1521,    87,     6,   239,    25,    26,     3,
      73,   216,    73,    74,   219,   220,   221,   222,   103,   104,
     105,   106,     6,    73,    74,   242,    73,    74,     3,    73,
      74,    13,    14,     8,    73,    74,    73,    74,   756,    73,
      74,     3,    73,    74,    73,    74,     8,    73,    74,    73,
      74,   116,   117,   239,    73,    74,     7,    73,    74,    73,
      74,   116,   117,     3,    73,    74,     6,    73,   239,    73,
      73,    73,     4,     3,    73,    73,     6,    73,   215,    89,
     217,   218,    73,   201,   202,    73,     3,    24,    73,    24,
      73,     8,    29,    73,     7,     3,    74,    75,   116,   117,
       8,     7,   239,    44,    45,    46,   116,   117,   151,   152,
     153,   154,   155,   156,     7,   180,   181,   182,     3,   116,
     117,   148,   149,     8,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,   172,
     173,   174,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    89,     3,    91,    92,     7,     3,
       8,    96,    97,    98,     8,   183,   184,     7,     3,     7,
     167,   168,   169,     8,   239,   116,   117,   187,     3,   116,
     117,   116,   117,     8,   239,   239,   240,   241,   242,    89,
       3,     7,  1376,     7,  1376,     8,  1376,     8,  1353,  1353,
    1353,  1353,     7,     3,     3,    11,    12,  1353,     8,    15,
      39,    40,    41,  1093,     3,    21,    22,    23,     3,     8,
       4,   239,  1075,     8,   161,   162,   163,   164,     3,   239,
     171,     4,  1121,     8,   175,   176,   177,   178,     3,   130,
     131,     3,   239,     8,   185,   186,     8,     4,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,     4,   184,    89,    90,    91,    92,    93,
      94,    95,     3,    99,   100,   101,   102,     8,   239,     4,
       3,   107,   239,     3,   239,     8,   116,   117,     8,     3,
     116,   117,   116,   117,     8,     4,     4,   123,   124,   125,
     126,   127,   128,   129,     3,     3,   132,     6,   132,    88,
       8,     3,   138,   719,   720,     3,     8,     3,     3,   239,
       8,   147,     8,     8,   150,     3,   732,   733,   734,   735,
       8,   157,   111,   112,   113,   114,   115,   116,   117,   165,
     166,     3,     8,     3,   170,     4,     8,   753,     8,     4,
     470,   471,     3,   132,   133,     4,     4,     8,   137,   189,
     190,   191,   188,     3,     3,     3,   192,     4,     8,     8,
     551,    47,    48,    49,    50,    51,    52,   558,   142,   143,
       4,   145,   208,   209,   210,   211,   212,   213,   214,   570,
       3,     8,     4,   574,     4,     8,     4,   223,     4,   570,
     581,     4,   558,   158,   159,   160,     4,     4,     4,   239,
     574,   592,   581,   239,   570,   239,     4,   581,   574,     4,
       4,   602,     4,     4,   570,   581,   570,   570,   609,     4,
       8,   570,   602,   558,   570,   609,   592,   609,     4,   609,
       4,   622,     4,     4,     4,   570,   602,     4,     4,   574,
       4,     4,     4,   609,     4,     4,   581,     4,     4,   570,
     239,     4,     4,   570,     4,     4,   622,   592,     4,     4,
     570,     4,     4,     3,   574,     4,   570,   602,     4,     4,
       8,   581,     3,   239,   609,     4,     4,   570,     4,   570,
       4,     4,   592,   574,     4,     4,     4,   622,     4,     4,
     570,     4,     4,   570,   574,   240,   570,   574,   240,   242,
     574,   570,   240,   570,   240,   574,   570,   574,   240,   570,
     574,   570,   240,   574,   570,   574,   570,   240,   574,   240,
     574,   570,     4,   240,   570,   574,   570,   241,   574,   241,
     574,   570,   116,   117,   570,   574,   570,   570,   570,   242,
     241,   570,   570,   240,   570,     4,     4,   241,   240,   570,
     240,   242,   570,   242,     4,   570,     4,   570,   242,   242,
     570,   241,   240,   240,     4,   240,   574,     4,   242,     4,
       4,     4,   240,   581,     4,     4,     4,     4,    88,   242,
     771,     4,   242,   774,     4,   242,     4,     4,     4,     4,
      54,    55,    56,    57,    58,    59,     4,     4,     4,   240,
       4,     4,     4,     4,     4,     4,   116,   117,   774,   193,
     194,   195,   196,   197,   198,   199,   200,   242,   242,   810,
     811,   242,   132,   814,    88,    89,     4,   818,   242,   139,
     140,   141,   142,   143,   144,   145,     4,     4,   242,   774,
     770,   242,     4,   240,   810,   811,     4,   813,   814,     4,
     240,     4,   116,   117,     4,   239,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     134,   135,   136,     4,   242,   810,   811,     4,   813,   814,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,     4,     4,   240,     4,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,     4,   240,    88,   240,     4,     4,   240,   240,
       4,     4,     4,     4,     4,     4,   100,   101,   102,   239,
       4,     4,   240,     4,   108,     4,   110,     4,   242,     4,
     242,   242,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   242,     4,     4,     4,   242,     4,   132,   133,
     240,     4,   240,   240,   138,     4,     4,     4,   240,     4,
     239,     7,   146,     7,     7,   239,     7,     7,     5,   239,
       5,     5,   239,   239,   239,     5,   239,   239,     5,     7,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,     5,     5,     5,   239,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,     7,    88,    89,     5,     5,     5,   239,
     239,     7,     7,     7,   208,   209,   100,   101,   102,     5,
       7,     5,     7,     5,     7,     5,     5,   239,   239,   239,
       7,   239,   116,   117,   239,   119,   120,   239,   122,   123,
     124,   125,   239,   239,   239,   239,   239,   239,   132,   133,
     239,   203,     5,   239,   239,   239,   239,     7,   239,   239,
     239,     7,   146,     7,     7,     7,     7,  1078,     7,     7,
    1081,     7,     7,  1084,     7,     7,  1087,  1078,   139,     4,
    1084,  1081,  1084,     4,  1084,     4,  1087,  1087,  1099,     4,
       4,  1102,  1078,  1087,  1105,  1081,     4,     4,  1084,  1099,
       4,  1087,  1078,     4,  1078,  1078,     4,     4,     4,  1078,
    1121,  1087,  1078,  1099,  1087,  1126,  1102,  1128,  1087,     6,
       3,  1087,     6,  1078,   208,   209,  1081,  1138,     3,  1084,
    1099,  1142,  1087,  1099,     6,  1121,  1147,  1078,  1138,  1150,
    1126,  1078,  1128,     3,  1099,     6,  1087,  1102,  1078,  1135,
    1087,  1150,  1138,  1147,  1078,   239,  1150,  1087,  1099,     3,
       6,  1147,  1099,  1087,  1150,  1078,  1121,  1078,     3,  1099,
       6,  1126,  1102,  1128,  1087,  1099,  1087,     6,  1078,     3,
    1135,  1078,     4,  1138,  1078,     6,  1099,  1087,     3,  1078,
    1087,  1078,  1147,  1087,  1078,  1150,     6,  1078,  1087,  1078,
    1087,     3,  1078,  1087,  1078,     4,  1087,     4,  1087,  1078,
       4,  1087,  1078,  1087,  1078,     4,     4,  1147,  1087,  1078,
    1150,  1087,  1078,  1087,  1078,  1078,  1078,     4,  1087,  1078,
    1078,  1087,  1078,  1087,  1087,  1087,  1147,  1078,  1087,  1087,
    1078,  1087,     4,  1078,     4,  1078,  1087,  1147,  1078,  1087,
    1147,     4,  1087,  1147,  1087,     4,     4,  1087,  1147,  1087,
    1147,     6,     3,  1147,     4,     4,  1147,     4,  1147,   239,
       6,  1147,     3,  1147,     6,     3,     6,     4,  1147,     8,
       4,  1147,     4,  1147,     4,   240,   242,     4,  1147,   240,
     242,   240,   240,   240,     4,   240,     4,     4,     4,     4,
     240,     4,     4,   240,     4,     4,     4,     4,   242,   240,
     240,   240,   240,   240,   240,     4,   240,   240,   240,  1147,
     240,     6,  1150,   240,   242,     3,   242,   240,   240,   239,
     239,   242,     8,   239,   239,     8,   239,   239,     4,   239,
     239,     8,  1353,     3,   239,   239,   239,     8,   239,     4,
    1361,     4,  1353,  1353,   239,     4,     4,   239,     4,  1353,
       4,  1361,  1312,   242,     4,  1376,     4,  1353,     4,   240,
       4,     4,  1383,   242,   240,  1361,     4,  1353,     7,     5,
    1353,   239,   239,  1383,  1353,   239,   239,  1353,     5,   239,
    1376,     7,  1361,     7,     6,  1361,     3,  1383,  1353,     4,
       4,     4,  1413,     4,   179,   239,  1361,   239,     5,     4,
       4,     4,  1353,     4,     4,     7,  1353,   242,     4,     6,
    1361,  1376,   240,  1353,  1361,     3,   240,  1413,  1383,  1353,
    1441,  1361,  1443,   239,   239,   239,     4,  1361,   239,   756,
    1353,   551,  1353,  1443,   771,   774,   803,   558,  1361,   855,
    1077,  1072,  1175,  1353,  1097,  1441,  1353,  1443,  1413,  1353,
    1090,  1093,  1107,  1105,  1353,  1078,  1353,  1126,   612,  1353,
    1114,  1482,  1353,   570,  1353,  1080,   602,  1353,  1089,  1353,
    1353,    77,  1482,  1083,  1353,  1081,  1441,  1353,  1443,  1353,
     609,  1086,  1503,  1084,  1353,  1147,  1482,  1353,  1149,  1353,
    1353,  1353,   574,  1150,  1353,  1353,  1152,  1353,   581,   592,
    1521,  1104,  1353,  1102,   828,  1353,  1361,  1503,  1353,  1101,
    1353,  1376,  1121,  1353,  1130,  1353,  1445,  1482,  1482,  1441,
    1505,  1521,  1135,   814,   622,  1521,   626,  1139,  1447,   773,
      72,    73,    74,    75,    76,    77,    78,    79,  1503,    81,
      82,    83,    84,  1489,  1383,  1142,    88,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1521,    -1,    -1,    -1,
     102,    -1,    -1,    -1,    -1,    -1,    -1,   109,    -1,    -1,
      -1,    -1,    -1,    -1,   116,   117,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     132,   133,    -1,    -1,    -1,   137,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   208,   209,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   239
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
       0,     5,     7,     9,   239,   240,   241,   242,   259,   260,
     261,   266,     7,   275,     7,   280,     7,   342,     7,   460,
       7,   540,     7,   557,     7,   574,     7,   489,     7,   495,
       7,   519,     7,   436,     7,   686,     7,   705,   267,   262,
     276,   281,   343,   461,   541,   558,   575,   490,   496,   520,
     437,   687,   706,   259,   268,   269,   239,   264,   265,    10,
     277,   279,    11,    12,    15,    21,    22,    23,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    99,   100,   101,   102,   107,   116,   117,
     123,   124,   125,   126,   127,   128,   129,   132,   138,   147,
     150,   157,   165,   166,   170,   188,   192,   208,   209,   210,
     211,   212,   213,   214,   223,   239,   274,   282,   283,   284,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   307,
     309,   311,   313,   314,   315,   318,   319,   320,   321,   322,
     324,   326,   327,   328,   329,   331,   332,   334,   336,   337,
     338,   339,   340,   352,   354,   356,   401,   409,   415,   421,
     423,   430,   444,   454,   474,   475,   476,   479,   487,   513,
     547,   549,   568,   598,   613,   625,   626,   674,   684,   703,
     712,   736,    16,    17,    18,    19,    20,   274,   344,   345,
     346,   348,   349,   350,   351,   547,   549,   108,   110,   118,
     119,   120,   121,   122,   132,   133,   146,   274,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   301,   302,   303,   304,   307,   309,   311,   313,
     314,   315,   318,   319,   320,   321,   322,   324,   326,   332,
     334,   462,   463,   464,   466,   468,   470,   472,   474,   475,
     476,   477,   478,   513,   534,   547,   549,   551,   568,   595,
     109,   137,   274,   301,   302,   303,   304,   307,   309,   311,
     313,   315,   318,   319,   320,   321,   322,   324,   470,   472,
     513,   542,   543,   544,   546,   547,   549,   111,   112,   113,
     114,   115,   274,   470,   472,   513,   546,   547,   549,   559,
     560,   561,   563,   564,   566,   567,   132,   139,   140,   141,
     142,   143,   144,   145,   274,   513,   547,   549,   576,   577,
     578,   579,   581,   583,   585,   587,   589,   591,   593,   487,
      24,    89,    91,    92,    96,    97,    98,   274,   375,   497,
     498,   499,   500,   501,   502,   503,   505,   507,   509,   510,
     512,   547,   549,    90,    93,    94,    95,   132,   274,   375,
     501,   507,   521,   522,   523,   524,   525,   527,   528,   529,
     530,   531,   532,   547,   549,   148,   149,   274,   438,   439,
     440,   442,   193,   194,   195,   196,   197,   198,   199,   200,
     274,   547,   549,   688,   689,   690,   691,   693,   694,   696,
     697,   698,   701,    13,    14,   707,   708,   709,   711,     6,
       3,     4,     8,     3,   278,     3,     8,   285,   704,   341,
     353,   355,   357,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   330,     4,
       4,     4,     4,     4,   305,   308,   310,   312,     4,     4,
       4,     4,     4,     4,     4,   455,   488,   514,     4,   333,
     335,   316,   480,   548,   550,     4,     4,     4,   410,   422,
     416,   402,   599,   569,   431,   445,   614,     4,   424,   627,
     675,   685,   323,   325,     4,     4,     4,     4,   713,   737,
       4,     3,     8,   347,     4,     4,     4,     4,     3,     8,
     535,   552,   465,   467,   469,     4,     4,   471,   473,   596,
       3,     8,   545,     4,     3,     8,   562,     4,   565,     4,
       4,     3,     8,   594,   580,   582,   584,   586,   588,   590,
     592,     8,     3,     8,   504,   376,     4,   508,   506,   511,
       4,     8,     3,   526,     4,     4,     4,   533,     8,     3,
     441,   443,     3,     8,     4,   692,     4,   695,     4,     4,
     699,   702,     3,     8,   710,     4,     3,     8,   259,   259,
     239,     4,     4,     4,     4,     4,     4,     4,   240,   240,
     240,   240,   240,   240,   240,   240,   242,   241,   241,   241,
     240,   241,   240,     4,   240,   240,   242,   242,   242,     4,
       4,     4,     4,   242,   242,   241,   240,   240,   240,   242,
       4,     4,     4,   240,     4,     4,     4,     4,     4,     4,
     242,   242,   242,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   240,     4,     4,     4,     4,     4,     4,   242,
     242,   242,   242,     4,     4,   283,     4,   242,   242,   240,
     240,   345,     4,     4,     4,     4,     4,   240,   242,     4,
       4,     4,   463,     4,   240,   543,     4,   240,     4,   240,
     240,   560,     4,     4,     4,     4,     4,     4,     4,     4,
     578,     4,     4,   240,     4,     4,     4,   242,   499,     4,
     242,   242,   242,     4,   523,     4,     4,   439,   242,     4,
     240,     4,   240,   240,     4,     4,   689,     4,   240,   708,
       4,     7,   239,     7,     7,     7,     7,     5,   239,   204,
     205,   206,   207,   242,   306,   239,   239,   239,     5,     5,
       5,   239,   239,   103,   104,   105,   106,   317,     5,   261,
     263,   239,     5,     5,     5,     7,     5,     5,     5,     7,
       7,     7,     5,     7,     7,   239,   239,     5,     7,     5,
     270,     5,     5,   239,   239,   239,   270,   270,     7,   239,
     239,   239,   270,   270,   270,   270,   239,   239,   239,   239,
     239,   239,   239,   239,   239,   239,   270,   239,   263,   239,
     239,   201,   202,   700,   203,     5,   259,   282,   707,   344,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,   184,   274,   362,
     363,   364,   366,   368,   370,   372,   374,   375,   377,   378,
     379,   380,   381,   382,   383,   384,   385,   388,   389,   390,
     391,   393,   395,   397,   399,   362,     7,   358,   359,   360,
       7,   456,   457,   458,     7,   491,   492,   493,     7,   515,
     516,   517,     7,   481,   482,   483,   142,   239,   411,   412,
     413,   414,   268,   143,   145,   413,   417,   418,   419,   420,
     130,   131,   403,   404,   405,   407,     7,   600,   601,   602,
       7,   570,   571,   572,     7,   432,   433,   434,   151,   152,
     153,   154,   155,   156,   446,   447,   448,   449,   450,   451,
     452,   453,    24,   161,   162,   163,   164,   274,   377,   547,
     549,   615,   616,   617,   620,   621,   623,   624,   167,   168,
     169,   274,   425,   426,   427,   428,   429,   547,   549,     7,
     628,   629,   630,   189,   190,   191,   239,   547,   549,   676,
     677,   678,   679,   681,   682,   688,     7,   714,   715,   224,
     274,   738,   739,   740,   271,     7,   536,   537,   538,     7,
     553,   554,   555,   579,   597,   358,     8,     8,     8,   365,
     367,   369,   373,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   386,     4,     4,   392,   394,   396,   398,
     400,   371,     3,     8,     8,   361,     6,     3,   459,     6,
       3,   494,     6,     3,   518,     6,     3,   484,     6,     3,
       3,     6,     6,     3,     6,   406,   408,     3,     8,   603,
       6,     3,   573,     6,     3,   435,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,   618,   622,     4,     4,
       4,     3,     8,     4,     4,     4,     3,     8,   631,     6,
       3,     4,   680,     4,   683,     3,     8,     8,   716,     3,
       6,     4,     3,     8,   239,   272,   273,   539,     6,     3,
     556,     6,     3,     8,     6,     4,     4,     4,     4,   240,
     242,   240,   242,   240,   240,   240,   240,   240,   240,     4,
     242,   240,     4,     4,     4,     4,     4,     4,   363,   362,
     360,   462,   458,   497,   493,   521,   517,   274,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   301,   302,   303,   304,   307,   309,   311,   313,
     314,   315,   318,   319,   320,   321,   322,   324,   326,   332,
     334,   375,   454,   466,   468,   470,   472,   474,   475,   476,
     478,   485,   486,   513,   547,   549,   595,   483,   412,   418,
       4,     4,   404,   134,   135,   136,   274,   286,   287,   288,
     289,   290,   291,   375,   513,   547,   549,   604,   605,   606,
     607,   608,   610,   612,   602,   576,   572,   438,   434,   240,
     240,   240,   240,   240,   240,   447,     4,     4,   240,   240,
     240,   616,   242,   240,   240,   426,   171,   175,   176,   177,
     178,   185,   186,   274,   391,   393,   395,   547,   549,   632,
     633,   634,   637,   639,   641,   642,   643,   653,   630,   242,
       4,   240,     4,   677,   215,   217,   218,   274,   375,   547,
     549,   717,   718,   719,   720,   722,   715,   242,   739,     6,
       3,   542,   538,   559,   555,   239,   239,   239,   239,    39,
      40,    41,   387,   239,   239,   239,   397,   239,   239,     8,
       8,     8,     8,     3,     8,   239,   239,   609,   611,     4,
       8,     3,     8,     8,   158,   159,   160,   619,   239,   635,
     638,   640,     4,   654,     4,   644,     3,     8,   239,   259,
     723,     4,   721,     3,     8,   239,     8,     8,   486,     4,
       4,   242,   606,     4,     4,     4,   240,     4,   242,     4,
     633,     4,   240,     4,   718,   239,   239,   172,   173,   174,
     636,   239,   239,     7,     5,     5,   239,    24,   180,   181,
     182,   274,   547,   549,   655,   656,   657,   660,   662,   664,
       7,   645,   646,   647,     7,   724,   725,   658,   661,   663,
     665,     3,     8,   648,     6,     3,   726,     3,     6,     4,
       4,     4,     4,   656,   187,   274,   375,   547,   549,   649,
     650,   651,   647,   216,   219,   220,   221,   222,   727,   728,
     729,   731,   732,   733,   734,   725,   179,   659,   239,   239,
       5,   652,     3,     8,   730,     4,     4,     4,   735,     3,
       8,     7,   666,   667,   668,     4,   650,     4,   242,   240,
     240,     4,   728,   669,     6,     3,   239,   239,   239,   183,
     274,   366,   368,   370,   547,   549,   670,   671,   672,   668,
     673,     3,     8,     4,   671,   239
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   243,   245,   244,   246,   244,   247,   244,   248,   244,
     249,   244,   250,   244,   251,   244,   252,   244,   253,   244,
     254,   244,   255,   244,   256,   244,   257,   244,   258,   244,
     259,   259,   259,   259,   259,   259,   259,   260,   262,   261,
     263,   264,   264,   265,   265,   265,   267,   266,   268,   268,
     269,   269,   269,   271,   270,   272,   272,   273,   273,   273,
     274,   276,   275,   278,   277,   277,   279,   281,   280,   282,
     282,   282,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   285,   284,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   305,   304,   306,   306,
     306,   306,   306,   308,   307,   310,   309,   312,   311,   313,
     314,   316,   315,   317,   317,   317,   317,   318,   319,   320,
     321,   323,   322,   325,   324,   326,   327,   328,   330,   329,
     331,   333,   332,   335,   334,   336,   337,   338,   339,   341,
     340,   343,   342,   344,   344,   344,   345,   345,   345,   345,
     345,   345,   345,   345,   347,   346,   348,   349,   350,   351,
     353,   352,   355,   354,   357,   356,   358,   358,   359,   359,
     359,   361,   360,   362,   362,   362,   363,   363,   363,   363,
     363,   363,   363,   363,   363,   363,   363,   363,   363,   363,
     363,   363,   363,   363,   363,   363,   363,   363,   363,   363,
     363,   365,   364,   367,   366,   369,   368,   371,   370,   373,
     372,   374,   376,   375,   377,   378,   379,   380,   381,   382,
     383,   384,   386,   385,   387,   387,   387,   388,   389,   390,
     392,   391,   394,   393,   396,   395,   398,   397,   397,   397,
     397,   397,   397,   400,   399,   402,   401,   403,   403,   403,
     404,   404,   406,   405,   408,   407,   410,   409,   411,   411,
     411,   412,   412,   413,   414,   416,   415,   417,   417,   417,
     418,   418,   418,   419,   420,   422,   421,   424,   423,   425,
     425,   425,   426,   426,   426,   426,   426,   426,   427,   428,
     429,   431,   430,   432,   432,   433,   433,   433,   435,   434,
     437,   436,   438,   438,   438,   438,   439,   439,   441,   440,
     443,   442,   445,   444,   446,   446,   446,   447,   447,   447,
     447,   447,   447,   448,   449,   450,   451,   452,   453,   455,
     454,   456,   456,   457,   457,   457,   459,   458,   461,   460,
     462,   462,   462,   463,   463,   463,   463,   463,   463,   463,
     463,   463,   463,   463,   463,   463,   463,   463,   463,   463,
     463,   463,   463,   463,   463,   463,   463,   463,   463,   463,
     463,   463,   463,   463,   463,   463,   463,   463,   463,   463,
     463,   463,   463,   463,   463,   463,   463,   463,   463,   463,
     463,   463,   463,   463,   465,   464,   467,   466,   469,   468,
     471,   470,   473,   472,   474,   475,   476,   477,   478,   480,
     479,   481,   481,   482,   482,   482,   484,   483,   485,   485,
     485,   486,   486,   486,   486,   486,   486,   486,   486,   486,
     486,   486,   486,   486,   486,   486,   486,   486,   486,   486,
     486,   486,   486,   486,   486,   486,   486,   486,   486,   486,
     486,   486,   486,   486,   486,   486,   486,   486,   486,   486,
     486,   486,   486,   486,   486,   486,   486,   486,   486,   488,
     487,   490,   489,   491,   491,   492,   492,   492,   494,   493,
     496,   495,   497,   497,   498,   498,   498,   499,   499,   499,
     499,   499,   499,   499,   499,   499,   499,   500,   501,   502,
     504,   503,   506,   505,   508,   507,   509,   511,   510,   512,
     514,   513,   515,   515,   516,   516,   516,   518,   517,   520,
     519,   521,   521,   522,   522,   522,   523,   523,   523,   523,
     523,   523,   523,   523,   523,   523,   523,   524,   526,   525,
     527,   528,   529,   530,   531,   533,   532,   535,   534,   536,
     536,   537,   537,   537,   539,   538,   541,   540,   542,   542,
     542,   543,   543,   543,   543,   543,   543,   543,   543,   543,
     543,   543,   543,   543,   543,   543,   543,   543,   543,   543,
     543,   543,   543,   543,   545,   544,   546,   548,   547,   550,
     549,   552,   551,   553,   553,   554,   554,   554,   556,   555,
     558,   557,   559,   559,   559,   560,   560,   560,   560,   560,
     560,   560,   560,   560,   560,   560,   560,   562,   561,   563,
     565,   564,   566,   567,   569,   568,   570,   570,   571,   571,
     571,   573,   572,   575,   574,   576,   576,   577,   577,   577,
     578,   578,   578,   578,   578,   578,   578,   578,   578,   578,
     578,   578,   580,   579,   582,   581,   584,   583,   586,   585,
     588,   587,   590,   589,   592,   591,   594,   593,   596,   595,
     597,   599,   598,   600,   600,   601,   601,   601,   603,   602,
     604,   604,   605,   605,   605,   606,   606,   606,   606,   606,
     606,   606,   606,   606,   606,   606,   606,   606,   606,   607,
     609,   608,   611,   610,   612,   614,   613,   615,   615,   615,
     616,   616,   616,   616,   616,   616,   616,   616,   616,   618,
     617,   619,   619,   619,   620,   622,   621,   623,   624,   625,
     627,   626,   628,   628,   629,   629,   629,   631,   630,   632,
     632,   632,   633,   633,   633,   633,   633,   633,   633,   633,
     633,   633,   633,   633,   633,   635,   634,   636,   636,   636,
     638,   637,   640,   639,   641,   642,   644,   643,   645,   645,
     646,   646,   646,   648,   647,   649,   649,   649,   650,   650,
     650,   650,   650,   652,   651,   654,   653,   655,   655,   655,
     656,   656,   656,   656,   656,   656,   656,   658,   657,   659,
     661,   660,   663,   662,   665,   664,   666,   666,   667,   667,
     667,   669,   668,   670,   670,   670,   671,   671,   671,   671,
     671,   671,   671,   673,   672,   675,   674,   676,   676,   676,
     677,   677,   677,   677,   677,   677,   678,   680,   679,   681,
     683,   682,   685,   684,   687,   686,   688,   688,   688,   689,
     689,   689,   689,   689,   689,   689,   689,   689,   689,   689,
     690,   692,   691,   693,   695,   694,   696,   697,   699,   698,
     700,   700,   702,   701,   704,   703,   706,   705,   707,   707,
     707,   708,   708,   710,   709,   711,   713,   712,   714,   714,
     714,   716,   715,   717,   717,   717,   718,   718,   718,   718,
     718,   718,   718,   719,   721,   720,   723,   722,   724,   724,
     724,   726,   725,   727,   727,   727,   728,   728,   728,   728,
     728,   730,   729,   731,   732,   733,   735,   734,   737,   736,
     738,   738,   738,   739,   739,   740
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
       1,     1,     1,     1,     1,     1,     0,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     3,
       3,     0,     4,     1,     1,     1,     1,     3,     3,     3,
       3,     0,     4,     0,     4,     3,     3,     3,     0,     4,
       3,     0,     4,     0,     4,     3,     3,     3,     3,     0,
       6,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     3,     3,     3,
       0,     6,     0,     6,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     3,     3,     3,     3,
       3,     3,     0,     4,     1,     1,     1,     3,     3,     3,
       0,     4,     0,     4,     0,     4,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     6,     1,     3,     2,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     0,     6,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     1,     3,     2,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
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
       1,     1,     1,     1,     0,     4,     3,     0,     4,     0,
       4,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       0,     4,     3,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     0,     1,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     1,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     3,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     3,     0,     4,     3,     3,     3,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       0,     4,     0,     4,     3,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     0,     4,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       0,     4,     0,     4,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     6,     1,     3,     2,
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
  "\"trust-anchor\"", "\"cert-file\"", "\"key-file\"", "\"ssl-mode\"",
  "\"disable\"", "\"prefer\"", "\"require\"", "\"verify-ca\"",
  "\"verify-full\"", "\"cipher-list\"", "\"preferred-lifetime\"",
  "\"min-preferred-lifetime\"", "\"max-preferred-lifetime\"",
  "\"valid-lifetime\"", "\"min-valid-lifetime\"", "\"max-valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"calculate-tee-times\"",
  "\"t1-percent\"", "\"t2-percent\"", "\"cache-threshold\"",
  "\"cache-max-age\"", "\"adaptive-lease-time-threshold\"",
  "\"decline-probation-period\"", "\"server-tag\"",
  "\"statistic-default-sample-count\"", "\"statistic-default-sample-age\"",
  "\"ddns-send-updates\"", "\"ddns-override-no-update\"",
  "\"ddns-override-client-update\"", "\"ddns-replace-client-name\"",
  "\"ddns-generated-prefix\"", "\"ddns-qualifying-suffix\"",
  "\"ddns-reverse-zone\"", "\"ddns-update-on-renew\"",
  "\"ddns-use-conflict-resolution\"", "\"ddns-ttl-percent\"",
  "\"ddns-ttl\"", "\"ddns-ttl-min\"", "\"ddns-ttl-max\"",
  "\"store-extended-info\"", "\"subnet6\"", "\"option-def\"",
  "\"option-data\"", "\"name\"", "\"data\"", "\"code\"", "\"space\"",
  "\"csv-format\"", "\"always-send\"", "\"never-send\"",
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
  "\"client-classes\"", "\"evaluate-additional-classes\"", "\"test\"",
  "\"template-test\"", "\"only-in-additional-list\"", "\"pool-id\"",
  "\"reservations\"", "\"ip-addresses\"", "\"prefixes\"",
  "\"excluded-prefixes\"", "\"duid\"", "\"hw-address\"", "\"hostname\"",
  "\"flex-id\"", "\"relay\"", "\"hooks-libraries\"", "\"library\"",
  "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"", "\"server-id\"",
  "\"LLT\"", "\"EN\"", "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"",
  "\"enterprise-id\"", "\"dhcp4o6-port\"", "\"multi-threading\"",
  "\"enable-multi-threading\"", "\"thread-pool-size\"",
  "\"packet-queue-size\"", "\"control-sockets\"", "\"socket-type\"",
  "\"unix\"", "\"http\"", "\"https\"", "\"socket-name\"",
  "\"socket-address\"", "\"socket-port\"", "\"authentication\"",
  "\"basic\"", "\"realm\"", "\"directory\"", "\"clients\"",
  "\"user-file\"", "\"password-file\"", "\"cert-required\"",
  "\"http-headers\"", "\"value\"", "\"dhcp-queue-control\"",
  "\"enable-queue\"", "\"queue-type\"", "\"capacity\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"server-ip\"", "\"server-port\"",
  "\"sender-ip\"", "\"sender-port\"", "\"max-queue-size\"",
  "\"ncr-protocol\"", "\"ncr-format\"", "\"UDP\"", "\"TCP\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"hostname-char-set\"", "\"hostname-char-replacement\"",
  "\"early-global-reservations-lookup\"", "\"ip-reservations-unique\"",
  "\"reservations-lookup-first\"", "\"allow-address-registration\"",
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
  "cache_max_age", "adaptive_lease_time_threshold",
  "decline_probation_period", "ddns_send_updates",
  "ddns_override_no_update", "ddns_override_client_update",
  "ddns_replace_client_name", "$@22", "ddns_replace_client_name_value",
  "ddns_generated_prefix", "$@23", "ddns_qualifying_suffix", "$@24",
  "ddns_reverse_zone", "$@25", "ddns_update_on_renew",
  "ddns_use_conflict_resolution", "ddns_conflict_resolution_mode", "$@26",
  "ddns_conflict_resolution_mode_value", "ddns_ttl_percent", "ddns_ttl",
  "ddns_ttl_min", "ddns_ttl_max", "hostname_char_set", "$@27",
  "hostname_char_replacement", "$@28", "store_extended_info",
  "statistic_default_sample_count", "statistic_default_sample_age",
  "server_tag", "$@29", "parked_packet_limit", "allocator", "$@30",
  "pd_allocator", "$@31", "early_global_reservations_lookup",
  "ip_reservations_unique", "reservations_lookup_first",
  "allow_address_registration", "interfaces_config", "$@32",
  "sub_interfaces6", "$@33", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@34", "re_detect",
  "service_sockets_require_all", "service_sockets_retry_wait_time",
  "service_sockets_max_retries", "lease_database", "$@35",
  "hosts_database", "$@36", "hosts_databases", "$@37", "database_list",
  "not_empty_database_list", "database", "$@38", "database_map_params",
  "database_map_param", "database_type", "$@39", "user", "$@40",
  "password", "$@41", "password_file", "$@42", "host", "$@43", "port",
  "name", "$@44", "persist", "lfc_interval", "readonly", "connect_timeout",
  "read_timeout", "write_timeout", "tcp_user_timeout",
  "reconnect_wait_time", "on_fail", "$@45", "on_fail_mode",
  "retry_on_startup", "max_row_errors", "max_reconnect_tries",
  "trust_anchor", "$@46", "cert_file", "$@47", "key_file", "$@48",
  "ssl_mode", "$@49", "cipher_list", "$@50", "sanity_checks", "$@51",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@52",
  "extended_info_checks", "$@53", "mac_sources", "$@54",
  "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@55",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@56",
  "dhcp_multi_threading", "$@57", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@58", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@59",
  "sub_hooks_library", "$@60", "hooks_params", "hooks_param", "library",
  "$@61", "parameters", "$@62", "expired_leases_processing", "$@63",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@64",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@65",
  "sub_subnet6", "$@66", "subnet6_params", "subnet6_param", "subnet",
  "$@67", "interface", "$@68", "interface_id", "$@69",
  "network_client_classes", "$@70", "evaluate_additional_classes", "$@71",
  "reservations_global", "reservations_in_subnet",
  "reservations_out_of_pool", "id", "rapid_commit", "shared_networks",
  "$@72", "shared_networks_content", "shared_networks_list",
  "shared_network", "$@73", "shared_network_params",
  "shared_network_param", "option_def_list", "$@74", "sub_option_def_list",
  "$@75", "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@76", "sub_option_def", "$@77",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@78",
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
  "not_empty_classes_list", "client_class_entry", "$@111",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@112",
  "client_class_template_test", "$@113", "only_in_additional_list",
  "server_id", "$@114", "server_id_params", "server_id_param",
  "server_id_type", "$@115", "duid_type", "htype", "identifier", "$@116",
  "time", "enterprise_id", "dhcp4o6_port", "control_sockets", "$@117",
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
       0,   338,   338,   338,   339,   339,   340,   340,   341,   341,
     342,   342,   343,   343,   344,   344,   345,   345,   346,   346,
     347,   347,   348,   348,   349,   349,   350,   350,   351,   351,
     359,   360,   361,   362,   363,   364,   365,   368,   373,   373,
     384,   387,   388,   391,   396,   402,   407,   407,   414,   415,
     418,   422,   426,   432,   432,   439,   440,   443,   447,   451,
     461,   470,   470,   485,   485,   499,   502,   508,   508,   517,
     518,   519,   526,   527,   528,   529,   530,   531,   532,   533,
     534,   535,   536,   537,   538,   539,   540,   541,   542,   543,
     544,   545,   546,   547,   548,   549,   550,   551,   552,   553,
     554,   555,   556,   557,   558,   559,   560,   561,   562,   563,
     564,   565,   566,   567,   568,   569,   570,   571,   572,   573,
     574,   575,   576,   577,   578,   579,   580,   581,   582,   583,
     584,   585,   586,   587,   588,   589,   590,   591,   592,   593,
     594,   595,   596,   597,   598,   599,   602,   602,   612,   618,
     624,   630,   636,   642,   648,   654,   660,   666,   672,   678,
     684,   690,   696,   702,   708,   714,   720,   720,   729,   732,
     735,   738,   741,   747,   747,   756,   756,   765,   765,   774,
     783,   793,   793,   802,   805,   808,   811,   816,   822,   828,
     834,   840,   840,   849,   849,   858,   864,   870,   876,   876,
     885,   891,   891,   900,   900,   909,   915,   921,   927,   933,
     933,   945,   945,   954,   955,   956,   961,   962,   963,   964,
     965,   966,   967,   968,   971,   971,   982,   988,   994,  1000,
    1006,  1006,  1019,  1019,  1032,  1032,  1043,  1044,  1047,  1048,
    1049,  1054,  1054,  1064,  1065,  1066,  1071,  1072,  1073,  1074,
    1075,  1076,  1077,  1078,  1079,  1080,  1081,  1082,  1083,  1084,
    1085,  1086,  1087,  1088,  1089,  1090,  1091,  1092,  1093,  1094,
    1095,  1098,  1098,  1107,  1107,  1116,  1116,  1125,  1125,  1134,
    1134,  1143,  1149,  1149,  1158,  1164,  1170,  1176,  1182,  1188,
    1194,  1200,  1206,  1206,  1214,  1215,  1216,  1219,  1225,  1231,
    1237,  1237,  1246,  1246,  1255,  1255,  1264,  1264,  1272,  1275,
    1278,  1281,  1284,  1289,  1289,  1298,  1298,  1309,  1310,  1311,
    1316,  1317,  1320,  1320,  1339,  1339,  1357,  1357,  1368,  1369,
    1370,  1375,  1376,  1379,  1384,  1389,  1389,  1400,  1401,  1402,
    1407,  1408,  1409,  1412,  1417,  1424,  1424,  1437,  1437,  1450,
    1451,  1452,  1457,  1458,  1459,  1460,  1461,  1462,  1465,  1471,
    1477,  1483,  1483,  1494,  1495,  1498,  1499,  1500,  1505,  1505,
    1515,  1515,  1525,  1526,  1527,  1530,  1533,  1534,  1537,  1537,
    1546,  1546,  1555,  1555,  1567,  1568,  1569,  1574,  1575,  1576,
    1577,  1578,  1579,  1582,  1588,  1594,  1600,  1606,  1612,  1621,
    1621,  1635,  1636,  1639,  1640,  1641,  1650,  1650,  1676,  1676,
    1687,  1688,  1689,  1695,  1696,  1697,  1698,  1699,  1700,  1701,
    1702,  1703,  1704,  1705,  1706,  1707,  1708,  1709,  1710,  1711,
    1712,  1713,  1714,  1715,  1716,  1717,  1718,  1719,  1720,  1721,
    1722,  1723,  1724,  1725,  1726,  1727,  1728,  1729,  1730,  1731,
    1732,  1733,  1734,  1735,  1736,  1737,  1738,  1739,  1740,  1741,
    1742,  1743,  1744,  1745,  1748,  1748,  1757,  1757,  1766,  1766,
    1776,  1776,  1787,  1787,  1798,  1804,  1810,  1816,  1822,  1830,
    1830,  1842,  1843,  1847,  1848,  1849,  1854,  1854,  1862,  1863,
    1864,  1869,  1870,  1871,  1872,  1873,  1874,  1875,  1876,  1877,
    1878,  1879,  1880,  1881,  1882,  1883,  1884,  1885,  1886,  1887,
    1888,  1889,  1890,  1891,  1892,  1893,  1894,  1895,  1896,  1897,
    1898,  1899,  1900,  1901,  1902,  1903,  1904,  1905,  1906,  1907,
    1908,  1909,  1910,  1911,  1912,  1913,  1914,  1915,  1916,  1923,
    1923,  1937,  1937,  1946,  1947,  1950,  1951,  1952,  1959,  1959,
    1974,  1974,  1988,  1989,  1992,  1993,  1994,  1999,  2000,  2001,
    2002,  2003,  2004,  2005,  2006,  2007,  2008,  2011,  2013,  2019,
    2021,  2021,  2030,  2030,  2039,  2039,  2048,  2050,  2050,  2059,
    2069,  2069,  2082,  2083,  2088,  2089,  2090,  2097,  2097,  2109,
    2109,  2121,  2122,  2127,  2128,  2129,  2136,  2137,  2138,  2139,
    2140,  2141,  2142,  2143,  2144,  2145,  2146,  2149,  2151,  2151,
    2160,  2162,  2164,  2170,  2176,  2182,  2182,  2196,  2196,  2209,
    2210,  2213,  2214,  2215,  2220,  2220,  2230,  2230,  2240,  2241,
    2242,  2247,  2248,  2249,  2250,  2251,  2252,  2253,  2254,  2255,
    2256,  2257,  2258,  2259,  2260,  2261,  2262,  2263,  2264,  2265,
    2266,  2267,  2268,  2269,  2272,  2272,  2281,  2287,  2287,  2312,
    2312,  2342,  2342,  2355,  2356,  2359,  2360,  2361,  2366,  2366,
    2378,  2378,  2390,  2391,  2392,  2397,  2398,  2399,  2400,  2401,
    2402,  2403,  2404,  2405,  2406,  2407,  2408,  2411,  2411,  2420,
    2426,  2426,  2435,  2441,  2450,  2450,  2461,  2462,  2465,  2466,
    2467,  2472,  2472,  2481,  2481,  2490,  2491,  2494,  2495,  2496,
    2502,  2503,  2504,  2505,  2506,  2507,  2508,  2509,  2510,  2511,
    2512,  2513,  2516,  2516,  2527,  2527,  2538,  2538,  2549,  2549,
    2558,  2558,  2567,  2567,  2576,  2576,  2585,  2585,  2599,  2599,
    2610,  2616,  2616,  2627,  2628,  2631,  2632,  2633,  2638,  2638,
    2648,  2649,  2652,  2653,  2654,  2659,  2660,  2661,  2662,  2663,
    2664,  2665,  2666,  2667,  2668,  2669,  2670,  2671,  2672,  2675,
    2677,  2677,  2686,  2686,  2695,  2704,  2704,  2717,  2718,  2719,
    2724,  2725,  2726,  2727,  2728,  2729,  2730,  2731,  2732,  2735,
    2735,  2743,  2744,  2745,  2748,  2754,  2754,  2763,  2769,  2777,
    2785,  2785,  2796,  2797,  2800,  2801,  2802,  2807,  2807,  2815,
    2816,  2817,  2822,  2823,  2824,  2825,  2826,  2827,  2828,  2829,
    2830,  2831,  2832,  2833,  2834,  2837,  2837,  2846,  2847,  2848,
    2851,  2851,  2860,  2860,  2869,  2875,  2881,  2881,  2892,  2893,
    2896,  2897,  2898,  2903,  2903,  2911,  2912,  2913,  2918,  2919,
    2920,  2921,  2922,  2925,  2925,  2936,  2936,  2949,  2950,  2951,
    2956,  2957,  2958,  2959,  2960,  2961,  2962,  2965,  2965,  2973,
    2976,  2976,  2985,  2985,  2994,  2994,  3005,  3006,  3009,  3010,
    3011,  3016,  3016,  3024,  3025,  3026,  3031,  3032,  3033,  3034,
    3035,  3036,  3037,  3040,  3040,  3051,  3051,  3064,  3065,  3066,
    3071,  3072,  3073,  3074,  3075,  3076,  3079,  3085,  3085,  3094,
    3100,  3100,  3110,  3110,  3123,  3123,  3133,  3134,  3135,  3140,
    3141,  3142,  3143,  3144,  3145,  3146,  3147,  3148,  3149,  3150,
    3153,  3159,  3159,  3168,  3174,  3174,  3183,  3189,  3195,  3195,
    3204,  3205,  3208,  3208,  3219,  3219,  3231,  3231,  3241,  3242,
    3243,  3249,  3250,  3253,  3253,  3264,  3272,  3272,  3285,  3286,
    3287,  3293,  3293,  3301,  3302,  3303,  3308,  3309,  3310,  3311,
    3312,  3313,  3314,  3317,  3323,  3323,  3332,  3332,  3343,  3344,
    3345,  3350,  3350,  3358,  3359,  3360,  3365,  3366,  3367,  3368,
    3369,  3372,  3372,  3381,  3387,  3393,  3399,  3399,  3408,  3408,
    3419,  3420,  3421,  3426,  3427,  3430
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
#line 7112 "dhcp6_parser.cc"

#line 3436 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
