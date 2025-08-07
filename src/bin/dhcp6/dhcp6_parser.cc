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
#line 331 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 417 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 331 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 423 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 331 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 429 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 331 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 435 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 331 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 441 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 331 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 447 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 331 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 453 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 331 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 459 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 331 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 465 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ssl_mode: // ssl_mode
#line 331 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 471 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 331 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 477 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
#line 331 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 483 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 331 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 489 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 331 "dhcp6_parser.yy"
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
#line 340 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 777 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 341 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 783 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 342 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 789 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 343 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 795 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 344 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 801 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 345 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 807 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 346 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 813 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 347 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 819 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 348 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 825 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 349 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 831 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 350 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 837 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 351 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 843 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 352 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 849 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 353 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 855 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 361 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 861 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 362 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 867 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 363 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 873 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 364 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 879 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 365 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 885 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 366 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 891 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 367 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 897 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 370 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 906 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 375 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 917 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 380 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 927 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 386 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 933 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 393 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 943 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 398 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 954 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 404 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 962 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 409 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 971 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 412 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 979 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 420 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 988 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 424 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 997 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 428 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 1005 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 434 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 1013 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 436 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1022 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 445 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1031 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 449 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1040 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 453 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1048 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 463 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1059 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 472 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1070 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 477 "dhcp6_parser.yy"
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
#line 487 "dhcp6_parser.yy"
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
#line 496 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1108 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 504 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1116 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 510 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1126 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 514 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1135 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 521 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1143 "dhcp6_parser.cc"
    break;

  case 145: // $@21: %empty
#line 603 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1152 "dhcp6_parser.cc"
    break;

  case 146: // data_directory: "data-directory" $@21 ":" "constant string"
#line 606 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.warning(yystack_[2].location, "data-directory is deprecated and will be ignored");
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1163 "dhcp6_parser.cc"
    break;

  case 147: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 613 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1173 "dhcp6_parser.cc"
    break;

  case 148: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 619 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1183 "dhcp6_parser.cc"
    break;

  case 149: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 625 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1193 "dhcp6_parser.cc"
    break;

  case 150: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 631 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1203 "dhcp6_parser.cc"
    break;

  case 151: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 637 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1213 "dhcp6_parser.cc"
    break;

  case 152: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 643 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1223 "dhcp6_parser.cc"
    break;

  case 153: // renew_timer: "renew-timer" ":" "integer"
#line 649 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1233 "dhcp6_parser.cc"
    break;

  case 154: // rebind_timer: "rebind-timer" ":" "integer"
#line 655 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1243 "dhcp6_parser.cc"
    break;

  case 155: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 661 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1253 "dhcp6_parser.cc"
    break;

  case 156: // t1_percent: "t1-percent" ":" "floating point"
#line 667 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1263 "dhcp6_parser.cc"
    break;

  case 157: // t2_percent: "t2-percent" ":" "floating point"
#line 673 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1273 "dhcp6_parser.cc"
    break;

  case 158: // cache_threshold: "cache-threshold" ":" "floating point"
#line 679 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1283 "dhcp6_parser.cc"
    break;

  case 159: // cache_max_age: "cache-max-age" ":" "integer"
#line 685 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1293 "dhcp6_parser.cc"
    break;

  case 160: // adaptive_lease_time_threshold: "adaptive-lease-time-threshold" ":" "floating point"
#line 691 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("adaptive-lease-time-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr altt(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("adaptive-lease-time-threshold", altt);
}
#line 1303 "dhcp6_parser.cc"
    break;

  case 161: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 697 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1313 "dhcp6_parser.cc"
    break;

  case 162: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 703 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1323 "dhcp6_parser.cc"
    break;

  case 163: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 709 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1333 "dhcp6_parser.cc"
    break;

  case 164: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 715 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1343 "dhcp6_parser.cc"
    break;

  case 165: // $@22: %empty
#line 721 "dhcp6_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1352 "dhcp6_parser.cc"
    break;

  case 166: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 724 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1361 "dhcp6_parser.cc"
    break;

  case 167: // ddns_replace_client_name_value: "when-present"
#line 730 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1369 "dhcp6_parser.cc"
    break;

  case 168: // ddns_replace_client_name_value: "never"
#line 733 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1377 "dhcp6_parser.cc"
    break;

  case 169: // ddns_replace_client_name_value: "always"
#line 736 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1385 "dhcp6_parser.cc"
    break;

  case 170: // ddns_replace_client_name_value: "when-not-present"
#line 739 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1393 "dhcp6_parser.cc"
    break;

  case 171: // ddns_replace_client_name_value: "boolean"
#line 742 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1402 "dhcp6_parser.cc"
    break;

  case 172: // $@23: %empty
#line 748 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1411 "dhcp6_parser.cc"
    break;

  case 173: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 751 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1421 "dhcp6_parser.cc"
    break;

  case 174: // $@24: %empty
#line 757 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1430 "dhcp6_parser.cc"
    break;

  case 175: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 760 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1440 "dhcp6_parser.cc"
    break;

  case 176: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 766 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1450 "dhcp6_parser.cc"
    break;

  case 177: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 775 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.warning(yystack_[1].location, "ddns-use-conflict-resolution is deprecated. "
             "Substituting ddns-conflict-resolution-mode");
    ElementPtr mode(new StringElement(b->boolValue() ? "check-with-dhcid"
                                      : "no-check-with-dhcid"));
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", mode);
}
#line 1464 "dhcp6_parser.cc"
    break;

  case 178: // $@25: %empty
#line 785 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1473 "dhcp6_parser.cc"
    break;

  case 179: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 788 "dhcp6_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1482 "dhcp6_parser.cc"
    break;

  case 180: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 794 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1490 "dhcp6_parser.cc"
    break;

  case 181: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 797 "dhcp6_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1498 "dhcp6_parser.cc"
    break;

  case 182: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 800 "dhcp6_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1506 "dhcp6_parser.cc"
    break;

  case 183: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 803 "dhcp6_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1514 "dhcp6_parser.cc"
    break;

  case 184: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 808 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1524 "dhcp6_parser.cc"
    break;

  case 185: // ddns_ttl: "ddns-ttl" ":" "integer"
#line 814 "dhcp6_parser.yy"
                                 {
    ctx.unique("ddns-ttl", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl", ttl);
}
#line 1534 "dhcp6_parser.cc"
    break;

  case 186: // ddns_ttl_min: "ddns-ttl-min" ":" "integer"
#line 820 "dhcp6_parser.yy"
                                         {
    ctx.unique("ddns-ttl-min", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-min", ttl);
}
#line 1544 "dhcp6_parser.cc"
    break;

  case 187: // ddns_ttl_max: "ddns-ttl-mix" ":" "integer"
#line 826 "dhcp6_parser.yy"
                                         {
    ctx.unique("ddns-ttl-max", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-max", ttl);
}
#line 1554 "dhcp6_parser.cc"
    break;

  case 188: // $@26: %empty
#line 832 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1563 "dhcp6_parser.cc"
    break;

  case 189: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 835 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1573 "dhcp6_parser.cc"
    break;

  case 190: // $@27: %empty
#line 841 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1582 "dhcp6_parser.cc"
    break;

  case 191: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 844 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1592 "dhcp6_parser.cc"
    break;

  case 192: // store_extended_info: "store-extended-info" ":" "boolean"
#line 850 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1602 "dhcp6_parser.cc"
    break;

  case 193: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 856 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1612 "dhcp6_parser.cc"
    break;

  case 194: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 862 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1622 "dhcp6_parser.cc"
    break;

  case 195: // $@28: %empty
#line 868 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1631 "dhcp6_parser.cc"
    break;

  case 196: // server_tag: "server-tag" $@28 ":" "constant string"
#line 871 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1641 "dhcp6_parser.cc"
    break;

  case 197: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 877 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1651 "dhcp6_parser.cc"
    break;

  case 198: // $@29: %empty
#line 883 "dhcp6_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1660 "dhcp6_parser.cc"
    break;

  case 199: // allocator: "allocator" $@29 ":" "constant string"
#line 886 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1670 "dhcp6_parser.cc"
    break;

  case 200: // $@30: %empty
#line 892 "dhcp6_parser.yy"
                           {
    ctx.unique("pd-allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1679 "dhcp6_parser.cc"
    break;

  case 201: // pd_allocator: "pd-allocator" $@30 ":" "constant string"
#line 895 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-allocator", al);
    ctx.leave();
}
#line 1689 "dhcp6_parser.cc"
    break;

  case 202: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 901 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1699 "dhcp6_parser.cc"
    break;

  case 203: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 907 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1709 "dhcp6_parser.cc"
    break;

  case 204: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 913 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1719 "dhcp6_parser.cc"
    break;

  case 205: // $@31: %empty
#line 919 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1731 "dhcp6_parser.cc"
    break;

  case 206: // interfaces_config: "interfaces-config" $@31 ":" "{" interfaces_config_params "}"
#line 925 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1741 "dhcp6_parser.cc"
    break;

  case 207: // $@32: %empty
#line 931 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1751 "dhcp6_parser.cc"
    break;

  case 208: // sub_interfaces6: "{" $@32 interfaces_config_params "}"
#line 935 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1760 "dhcp6_parser.cc"
    break;

  case 211: // interfaces_config_params: interfaces_config_params ","
#line 942 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1768 "dhcp6_parser.cc"
    break;

  case 220: // $@33: %empty
#line 957 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1780 "dhcp6_parser.cc"
    break;

  case 221: // interfaces_list: "interfaces" $@33 ":" list_strings
#line 963 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1789 "dhcp6_parser.cc"
    break;

  case 222: // re_detect: "re-detect" ":" "boolean"
#line 968 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1799 "dhcp6_parser.cc"
    break;

  case 223: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 974 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1809 "dhcp6_parser.cc"
    break;

  case 224: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 980 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1819 "dhcp6_parser.cc"
    break;

  case 225: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 986 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1829 "dhcp6_parser.cc"
    break;

  case 226: // $@34: %empty
#line 992 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1841 "dhcp6_parser.cc"
    break;

  case 227: // lease_database: "lease-database" $@34 ":" "{" database_map_params "}"
#line 998 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1852 "dhcp6_parser.cc"
    break;

  case 228: // $@35: %empty
#line 1005 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1864 "dhcp6_parser.cc"
    break;

  case 229: // hosts_database: "hosts-database" $@35 ":" "{" database_map_params "}"
#line 1011 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1875 "dhcp6_parser.cc"
    break;

  case 230: // $@36: %empty
#line 1018 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1887 "dhcp6_parser.cc"
    break;

  case 231: // hosts_databases: "hosts-databases" $@36 ":" "[" database_list "]"
#line 1024 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1896 "dhcp6_parser.cc"
    break;

  case 236: // not_empty_database_list: not_empty_database_list ","
#line 1035 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1904 "dhcp6_parser.cc"
    break;

  case 237: // $@37: %empty
#line 1040 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1914 "dhcp6_parser.cc"
    break;

  case 238: // database: "{" $@37 database_map_params "}"
#line 1044 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1924 "dhcp6_parser.cc"
    break;

  case 241: // database_map_params: database_map_params ","
#line 1052 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1932 "dhcp6_parser.cc"
    break;

  case 266: // $@38: %empty
#line 1083 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1941 "dhcp6_parser.cc"
    break;

  case 267: // database_type: "type" $@38 ":" "constant string"
#line 1086 "dhcp6_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 1951 "dhcp6_parser.cc"
    break;

  case 268: // $@39: %empty
#line 1092 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1960 "dhcp6_parser.cc"
    break;

  case 269: // user: "user" $@39 ":" "constant string"
#line 1095 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1970 "dhcp6_parser.cc"
    break;

  case 270: // $@40: %empty
#line 1101 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1979 "dhcp6_parser.cc"
    break;

  case 271: // password: "password" $@40 ":" "constant string"
#line 1104 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1989 "dhcp6_parser.cc"
    break;

  case 272: // $@41: %empty
#line 1110 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1998 "dhcp6_parser.cc"
    break;

  case 273: // host: "host" $@41 ":" "constant string"
#line 1113 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2008 "dhcp6_parser.cc"
    break;

  case 274: // port: "port" ":" "integer"
#line 1119 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2018 "dhcp6_parser.cc"
    break;

  case 275: // $@42: %empty
#line 1125 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2027 "dhcp6_parser.cc"
    break;

  case 276: // name: "name" $@42 ":" "constant string"
#line 1128 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2037 "dhcp6_parser.cc"
    break;

  case 277: // persist: "persist" ":" "boolean"
#line 1134 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2047 "dhcp6_parser.cc"
    break;

  case 278: // lfc_interval: "lfc-interval" ":" "integer"
#line 1140 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2057 "dhcp6_parser.cc"
    break;

  case 279: // readonly: "readonly" ":" "boolean"
#line 1146 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2067 "dhcp6_parser.cc"
    break;

  case 280: // connect_timeout: "connect-timeout" ":" "integer"
#line 1152 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2077 "dhcp6_parser.cc"
    break;

  case 281: // read_timeout: "read-timeout" ":" "integer"
#line 1158 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2087 "dhcp6_parser.cc"
    break;

  case 282: // write_timeout: "write-timeout" ":" "integer"
#line 1164 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2097 "dhcp6_parser.cc"
    break;

  case 283: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1170 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2107 "dhcp6_parser.cc"
    break;

  case 284: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1176 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2117 "dhcp6_parser.cc"
    break;

  case 285: // $@43: %empty
#line 1182 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2126 "dhcp6_parser.cc"
    break;

  case 286: // on_fail: "on-fail" $@43 ":" on_fail_mode
#line 1185 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2135 "dhcp6_parser.cc"
    break;

  case 287: // on_fail_mode: "stop-retry-exit"
#line 1190 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2141 "dhcp6_parser.cc"
    break;

  case 288: // on_fail_mode: "serve-retry-exit"
#line 1191 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2147 "dhcp6_parser.cc"
    break;

  case 289: // on_fail_mode: "serve-retry-continue"
#line 1192 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2153 "dhcp6_parser.cc"
    break;

  case 290: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1195 "dhcp6_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2163 "dhcp6_parser.cc"
    break;

  case 291: // max_row_errors: "max-row-errors" ":" "integer"
#line 1201 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2173 "dhcp6_parser.cc"
    break;

  case 292: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1207 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2183 "dhcp6_parser.cc"
    break;

  case 293: // $@44: %empty
#line 1213 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2192 "dhcp6_parser.cc"
    break;

  case 294: // trust_anchor: "trust-anchor" $@44 ":" "constant string"
#line 1216 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2202 "dhcp6_parser.cc"
    break;

  case 295: // $@45: %empty
#line 1222 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2211 "dhcp6_parser.cc"
    break;

  case 296: // cert_file: "cert-file" $@45 ":" "constant string"
#line 1225 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2221 "dhcp6_parser.cc"
    break;

  case 297: // $@46: %empty
#line 1231 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2230 "dhcp6_parser.cc"
    break;

  case 298: // key_file: "key-file" $@46 ":" "constant string"
#line 1234 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2240 "dhcp6_parser.cc"
    break;

  case 299: // $@47: %empty
#line 1240 "dhcp6_parser.yy"
                   {
    ctx.unique("ssl-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SSL_MODE);
}
#line 2249 "dhcp6_parser.cc"
    break;

  case 300: // ssl_mode: "ssl-mode" $@47 ":" ssl_mode
#line 1243 "dhcp6_parser.yy"
                 {
    ctx.stack_.back()->set("ssl-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2258 "dhcp6_parser.cc"
    break;

  case 301: // ssl_mode: "disable"
#line 1248 "dhcp6_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disable", ctx.loc2pos(yystack_[0].location)));
            }
#line 2266 "dhcp6_parser.cc"
    break;

  case 302: // ssl_mode: "prefer"
#line 1251 "dhcp6_parser.yy"
                 {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("prefer", ctx.loc2pos(yystack_[0].location)));
            }
#line 2274 "dhcp6_parser.cc"
    break;

  case 303: // ssl_mode: "require"
#line 1254 "dhcp6_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("require", ctx.loc2pos(yystack_[0].location)));
            }
#line 2282 "dhcp6_parser.cc"
    break;

  case 304: // ssl_mode: "verify-ca"
#line 1257 "dhcp6_parser.yy"
                    {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-ca", ctx.loc2pos(yystack_[0].location)));
            }
#line 2290 "dhcp6_parser.cc"
    break;

  case 305: // ssl_mode: "verify-full"
#line 1260 "dhcp6_parser.yy"
                      {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-full", ctx.loc2pos(yystack_[0].location)));
            }
#line 2298 "dhcp6_parser.cc"
    break;

  case 306: // $@48: %empty
#line 1265 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2307 "dhcp6_parser.cc"
    break;

  case 307: // cipher_list: "cipher-list" $@48 ":" "constant string"
#line 1268 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2317 "dhcp6_parser.cc"
    break;

  case 308: // $@49: %empty
#line 1274 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2329 "dhcp6_parser.cc"
    break;

  case 309: // sanity_checks: "sanity-checks" $@49 ":" "{" sanity_checks_params "}"
#line 1280 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2338 "dhcp6_parser.cc"
    break;

  case 312: // sanity_checks_params: sanity_checks_params ","
#line 1287 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2346 "dhcp6_parser.cc"
    break;

  case 315: // $@50: %empty
#line 1296 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2355 "dhcp6_parser.cc"
    break;

  case 316: // lease_checks: "lease-checks" $@50 ":" "constant string"
#line 1299 "dhcp6_parser.yy"
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
#line 2375 "dhcp6_parser.cc"
    break;

  case 317: // $@51: %empty
#line 1315 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2384 "dhcp6_parser.cc"
    break;

  case 318: // extended_info_checks: "extended-info-checks" $@51 ":" "constant string"
#line 1318 "dhcp6_parser.yy"
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
#line 2403 "dhcp6_parser.cc"
    break;

  case 319: // $@52: %empty
#line 1333 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2415 "dhcp6_parser.cc"
    break;

  case 320: // mac_sources: "mac-sources" $@52 ":" "[" mac_sources_list "]"
#line 1339 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2424 "dhcp6_parser.cc"
    break;

  case 323: // mac_sources_list: mac_sources_list ","
#line 1346 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2432 "dhcp6_parser.cc"
    break;

  case 326: // duid_id: "duid"
#line 1355 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2441 "dhcp6_parser.cc"
    break;

  case 327: // string_id: "constant string"
#line 1360 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2450 "dhcp6_parser.cc"
    break;

  case 328: // $@53: %empty
#line 1365 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2462 "dhcp6_parser.cc"
    break;

  case 329: // host_reservation_identifiers: "host-reservation-identifiers" $@53 ":" "[" host_reservation_identifiers_list "]"
#line 1371 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2471 "dhcp6_parser.cc"
    break;

  case 332: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1378 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2479 "dhcp6_parser.cc"
    break;

  case 336: // hw_address_id: "hw-address"
#line 1388 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2488 "dhcp6_parser.cc"
    break;

  case 337: // flex_id: "flex-id"
#line 1393 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2497 "dhcp6_parser.cc"
    break;

  case 338: // $@54: %empty
#line 1400 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2509 "dhcp6_parser.cc"
    break;

  case 339: // relay_supplied_options: "relay-supplied-options" $@54 ":" "[" list_content "]"
#line 1406 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2518 "dhcp6_parser.cc"
    break;

  case 340: // $@55: %empty
#line 1413 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2530 "dhcp6_parser.cc"
    break;

  case 341: // dhcp_multi_threading: "multi-threading" $@55 ":" "{" multi_threading_params "}"
#line 1419 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2541 "dhcp6_parser.cc"
    break;

  case 344: // multi_threading_params: multi_threading_params ","
#line 1428 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2549 "dhcp6_parser.cc"
    break;

  case 351: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1441 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2559 "dhcp6_parser.cc"
    break;

  case 352: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1447 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2569 "dhcp6_parser.cc"
    break;

  case 353: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1453 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2579 "dhcp6_parser.cc"
    break;

  case 354: // $@56: %empty
#line 1459 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2591 "dhcp6_parser.cc"
    break;

  case 355: // hooks_libraries: "hooks-libraries" $@56 ":" "[" hooks_libraries_list "]"
#line 1465 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2600 "dhcp6_parser.cc"
    break;

  case 360: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1476 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2608 "dhcp6_parser.cc"
    break;

  case 361: // $@57: %empty
#line 1481 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2618 "dhcp6_parser.cc"
    break;

  case 362: // hooks_library: "{" $@57 hooks_params "}"
#line 1485 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2628 "dhcp6_parser.cc"
    break;

  case 363: // $@58: %empty
#line 1491 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2638 "dhcp6_parser.cc"
    break;

  case 364: // sub_hooks_library: "{" $@58 hooks_params "}"
#line 1495 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2648 "dhcp6_parser.cc"
    break;

  case 367: // hooks_params: hooks_params ","
#line 1503 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2656 "dhcp6_parser.cc"
    break;

  case 371: // $@59: %empty
#line 1513 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2665 "dhcp6_parser.cc"
    break;

  case 372: // library: "library" $@59 ":" "constant string"
#line 1516 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2675 "dhcp6_parser.cc"
    break;

  case 373: // $@60: %empty
#line 1522 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2684 "dhcp6_parser.cc"
    break;

  case 374: // parameters: "parameters" $@60 ":" map_value
#line 1525 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2693 "dhcp6_parser.cc"
    break;

  case 375: // $@61: %empty
#line 1531 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2705 "dhcp6_parser.cc"
    break;

  case 376: // expired_leases_processing: "expired-leases-processing" $@61 ":" "{" expired_leases_params "}"
#line 1537 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2715 "dhcp6_parser.cc"
    break;

  case 379: // expired_leases_params: expired_leases_params ","
#line 1545 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2723 "dhcp6_parser.cc"
    break;

  case 386: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1558 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2733 "dhcp6_parser.cc"
    break;

  case 387: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1564 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2743 "dhcp6_parser.cc"
    break;

  case 388: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1570 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2753 "dhcp6_parser.cc"
    break;

  case 389: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1576 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2763 "dhcp6_parser.cc"
    break;

  case 390: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1582 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2773 "dhcp6_parser.cc"
    break;

  case 391: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1588 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2783 "dhcp6_parser.cc"
    break;

  case 392: // $@62: %empty
#line 1597 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2795 "dhcp6_parser.cc"
    break;

  case 393: // subnet6_list: "subnet6" $@62 ":" "[" subnet6_list_content "]"
#line 1603 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2804 "dhcp6_parser.cc"
    break;

  case 398: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1617 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2812 "dhcp6_parser.cc"
    break;

  case 399: // $@63: %empty
#line 1626 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2822 "dhcp6_parser.cc"
    break;

  case 400: // subnet6: "{" $@63 subnet6_params "}"
#line 1630 "dhcp6_parser.yy"
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
#line 2848 "dhcp6_parser.cc"
    break;

  case 401: // $@64: %empty
#line 1652 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2858 "dhcp6_parser.cc"
    break;

  case 402: // sub_subnet6: "{" $@64 subnet6_params "}"
#line 1656 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2868 "dhcp6_parser.cc"
    break;

  case 405: // subnet6_params: subnet6_params ","
#line 1665 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2876 "dhcp6_parser.cc"
    break;

  case 458: // $@65: %empty
#line 1725 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2885 "dhcp6_parser.cc"
    break;

  case 459: // subnet: "subnet" $@65 ":" "constant string"
#line 1728 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2895 "dhcp6_parser.cc"
    break;

  case 460: // $@66: %empty
#line 1734 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2904 "dhcp6_parser.cc"
    break;

  case 461: // interface: "interface" $@66 ":" "constant string"
#line 1737 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2914 "dhcp6_parser.cc"
    break;

  case 462: // $@67: %empty
#line 1743 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2923 "dhcp6_parser.cc"
    break;

  case 463: // interface_id: "interface-id" $@67 ":" "constant string"
#line 1746 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2933 "dhcp6_parser.cc"
    break;

  case 464: // $@68: %empty
#line 1752 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2942 "dhcp6_parser.cc"
    break;

  case 465: // client_class: "client-class" $@68 ":" "constant string"
#line 1755 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2952 "dhcp6_parser.cc"
    break;

  case 466: // $@69: %empty
#line 1762 "dhcp6_parser.yy"
                                       {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2964 "dhcp6_parser.cc"
    break;

  case 467: // network_client_classes: "client-classes" $@69 ":" list_strings
#line 1768 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2973 "dhcp6_parser.cc"
    break;

  case 468: // $@70: %empty
#line 1774 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2985 "dhcp6_parser.cc"
    break;

  case 469: // require_client_classes: "require-client-classes" $@70 ":" list_strings
#line 1780 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2994 "dhcp6_parser.cc"
    break;

  case 470: // $@71: %empty
#line 1785 "dhcp6_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3006 "dhcp6_parser.cc"
    break;

  case 471: // evaluate_additional_classes: "evaluate-additional-classes" $@71 ":" list_strings
#line 1791 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3015 "dhcp6_parser.cc"
    break;

  case 472: // reservations_global: "reservations-global" ":" "boolean"
#line 1796 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 3025 "dhcp6_parser.cc"
    break;

  case 473: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1802 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 3035 "dhcp6_parser.cc"
    break;

  case 474: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1808 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 3045 "dhcp6_parser.cc"
    break;

  case 475: // id: "id" ":" "integer"
#line 1814 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 3055 "dhcp6_parser.cc"
    break;

  case 476: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1820 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 3065 "dhcp6_parser.cc"
    break;

  case 477: // $@72: %empty
#line 1828 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3077 "dhcp6_parser.cc"
    break;

  case 478: // shared_networks: "shared-networks" $@72 ":" "[" shared_networks_content "]"
#line 1834 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3086 "dhcp6_parser.cc"
    break;

  case 483: // shared_networks_list: shared_networks_list ","
#line 1847 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3094 "dhcp6_parser.cc"
    break;

  case 484: // $@73: %empty
#line 1852 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3104 "dhcp6_parser.cc"
    break;

  case 485: // shared_network: "{" $@73 shared_network_params "}"
#line 1856 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3112 "dhcp6_parser.cc"
    break;

  case 488: // shared_network_params: shared_network_params ","
#line 1862 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3120 "dhcp6_parser.cc"
    break;

  case 538: // $@74: %empty
#line 1922 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3132 "dhcp6_parser.cc"
    break;

  case 539: // option_def_list: "option-def" $@74 ":" "[" option_def_list_content "]"
#line 1928 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3141 "dhcp6_parser.cc"
    break;

  case 540: // $@75: %empty
#line 1936 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3150 "dhcp6_parser.cc"
    break;

  case 541: // sub_option_def_list: "{" $@75 option_def_list "}"
#line 1939 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 3158 "dhcp6_parser.cc"
    break;

  case 546: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1951 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3166 "dhcp6_parser.cc"
    break;

  case 547: // $@76: %empty
#line 1958 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3176 "dhcp6_parser.cc"
    break;

  case 548: // option_def_entry: "{" $@76 option_def_params "}"
#line 1962 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3188 "dhcp6_parser.cc"
    break;

  case 549: // $@77: %empty
#line 1973 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3198 "dhcp6_parser.cc"
    break;

  case 550: // sub_option_def: "{" $@77 option_def_params "}"
#line 1977 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3210 "dhcp6_parser.cc"
    break;

  case 555: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1993 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3218 "dhcp6_parser.cc"
    break;

  case 567: // code: "code" ":" "integer"
#line 2012 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3228 "dhcp6_parser.cc"
    break;

  case 569: // $@78: %empty
#line 2020 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3237 "dhcp6_parser.cc"
    break;

  case 570: // option_def_type: "type" $@78 ":" "constant string"
#line 2023 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3247 "dhcp6_parser.cc"
    break;

  case 571: // $@79: %empty
#line 2029 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3256 "dhcp6_parser.cc"
    break;

  case 572: // option_def_record_types: "record-types" $@79 ":" "constant string"
#line 2032 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3266 "dhcp6_parser.cc"
    break;

  case 573: // $@80: %empty
#line 2038 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3275 "dhcp6_parser.cc"
    break;

  case 574: // space: "space" $@80 ":" "constant string"
#line 2041 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3285 "dhcp6_parser.cc"
    break;

  case 576: // $@81: %empty
#line 2049 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3294 "dhcp6_parser.cc"
    break;

  case 577: // option_def_encapsulate: "encapsulate" $@81 ":" "constant string"
#line 2052 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3304 "dhcp6_parser.cc"
    break;

  case 578: // option_def_array: "array" ":" "boolean"
#line 2058 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3314 "dhcp6_parser.cc"
    break;

  case 579: // $@82: %empty
#line 2068 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3326 "dhcp6_parser.cc"
    break;

  case 580: // option_data_list: "option-data" $@82 ":" "[" option_data_list_content "]"
#line 2074 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3335 "dhcp6_parser.cc"
    break;

  case 585: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2089 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3343 "dhcp6_parser.cc"
    break;

  case 586: // $@83: %empty
#line 2096 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3353 "dhcp6_parser.cc"
    break;

  case 587: // option_data_entry: "{" $@83 option_data_params "}"
#line 2100 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3362 "dhcp6_parser.cc"
    break;

  case 588: // $@84: %empty
#line 2108 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3372 "dhcp6_parser.cc"
    break;

  case 589: // sub_option_data: "{" $@84 option_data_params "}"
#line 2112 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3381 "dhcp6_parser.cc"
    break;

  case 594: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2128 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3389 "dhcp6_parser.cc"
    break;

  case 607: // $@85: %empty
#line 2150 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3398 "dhcp6_parser.cc"
    break;

  case 608: // option_data_data: "data" $@85 ":" "constant string"
#line 2153 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3408 "dhcp6_parser.cc"
    break;

  case 611: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2163 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3418 "dhcp6_parser.cc"
    break;

  case 612: // option_data_always_send: "always-send" ":" "boolean"
#line 2169 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3428 "dhcp6_parser.cc"
    break;

  case 613: // option_data_never_send: "never-send" ":" "boolean"
#line 2175 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3438 "dhcp6_parser.cc"
    break;

  case 614: // $@86: %empty
#line 2181 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3450 "dhcp6_parser.cc"
    break;

  case 615: // option_data_client_classes: "client-classes" $@86 ":" list_strings
#line 2187 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3459 "dhcp6_parser.cc"
    break;

  case 616: // $@87: %empty
#line 2195 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3471 "dhcp6_parser.cc"
    break;

  case 617: // pools_list: "pools" $@87 ":" "[" pools_list_content "]"
#line 2201 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3480 "dhcp6_parser.cc"
    break;

  case 622: // not_empty_pools_list: not_empty_pools_list ","
#line 2214 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3488 "dhcp6_parser.cc"
    break;

  case 623: // $@88: %empty
#line 2219 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3498 "dhcp6_parser.cc"
    break;

  case 624: // pool_list_entry: "{" $@88 pool_params "}"
#line 2223 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3508 "dhcp6_parser.cc"
    break;

  case 625: // $@89: %empty
#line 2229 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3518 "dhcp6_parser.cc"
    break;

  case 626: // sub_pool6: "{" $@89 pool_params "}"
#line 2233 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3528 "dhcp6_parser.cc"
    break;

  case 629: // pool_params: pool_params ","
#line 2241 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3536 "dhcp6_parser.cc"
    break;

  case 654: // $@90: %empty
#line 2272 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3545 "dhcp6_parser.cc"
    break;

  case 655: // pool_entry: "pool" $@90 ":" "constant string"
#line 2275 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3555 "dhcp6_parser.cc"
    break;

  case 656: // pool_id: "pool-id" ":" "integer"
#line 2281 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3565 "dhcp6_parser.cc"
    break;

  case 657: // $@91: %empty
#line 2287 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3573 "dhcp6_parser.cc"
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
#line 3600 "dhcp6_parser.cc"
    break;

  case 659: // $@92: %empty
#line 2312 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3608 "dhcp6_parser.cc"
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
#line 3637 "dhcp6_parser.cc"
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
#line 3649 "dhcp6_parser.cc"
    break;

  case 662: // pd_pools_list: "pd-pools" $@93 ":" "[" pd_pools_list_content "]"
#line 2348 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3658 "dhcp6_parser.cc"
    break;

  case 667: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2361 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3666 "dhcp6_parser.cc"
    break;

  case 668: // $@94: %empty
#line 2366 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3676 "dhcp6_parser.cc"
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
#line 3688 "dhcp6_parser.cc"
    break;

  case 670: // $@95: %empty
#line 2378 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3698 "dhcp6_parser.cc"
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
#line 3710 "dhcp6_parser.cc"
    break;

  case 674: // pd_pool_params: pd_pool_params ","
#line 2392 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3718 "dhcp6_parser.cc"
    break;

  case 689: // $@96: %empty
#line 2413 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3727 "dhcp6_parser.cc"
    break;

  case 690: // pd_prefix: "prefix" $@96 ":" "constant string"
#line 2416 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3737 "dhcp6_parser.cc"
    break;

  case 691: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2422 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3747 "dhcp6_parser.cc"
    break;

  case 692: // $@97: %empty
#line 2428 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3756 "dhcp6_parser.cc"
    break;

  case 693: // excluded_prefix: "excluded-prefix" $@97 ":" "constant string"
#line 2431 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3766 "dhcp6_parser.cc"
    break;

  case 694: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2437 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3776 "dhcp6_parser.cc"
    break;

  case 695: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2443 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3786 "dhcp6_parser.cc"
    break;

  case 696: // $@98: %empty
#line 2452 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3798 "dhcp6_parser.cc"
    break;

  case 697: // reservations: "reservations" $@98 ":" "[" reservations_list "]"
#line 2458 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3807 "dhcp6_parser.cc"
    break;

  case 702: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2469 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3815 "dhcp6_parser.cc"
    break;

  case 703: // $@99: %empty
#line 2474 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3825 "dhcp6_parser.cc"
    break;

  case 704: // reservation: "{" $@99 reservation_params "}"
#line 2478 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3834 "dhcp6_parser.cc"
    break;

  case 705: // $@100: %empty
#line 2483 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3844 "dhcp6_parser.cc"
    break;

  case 706: // sub_reservation: "{" $@100 reservation_params "}"
#line 2487 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3853 "dhcp6_parser.cc"
    break;

  case 711: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2498 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3861 "dhcp6_parser.cc"
    break;

  case 724: // $@101: %empty
#line 2518 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3873 "dhcp6_parser.cc"
    break;

  case 725: // ip_addresses: "ip-addresses" $@101 ":" list_strings
#line 2524 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3882 "dhcp6_parser.cc"
    break;

  case 726: // $@102: %empty
#line 2529 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3894 "dhcp6_parser.cc"
    break;

  case 727: // prefixes: "prefixes" $@102 ":" list_strings
#line 2535 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3903 "dhcp6_parser.cc"
    break;

  case 728: // $@103: %empty
#line 2540 "dhcp6_parser.yy"
                                     {
    ctx.unique("excluded-prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3915 "dhcp6_parser.cc"
    break;

  case 729: // excluded_prefixes: "excluded-prefixes" $@103 ":" list_strings
#line 2546 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3924 "dhcp6_parser.cc"
    break;

  case 730: // $@104: %empty
#line 2551 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3933 "dhcp6_parser.cc"
    break;

  case 731: // duid: "duid" $@104 ":" "constant string"
#line 2554 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3943 "dhcp6_parser.cc"
    break;

  case 732: // $@105: %empty
#line 2560 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3952 "dhcp6_parser.cc"
    break;

  case 733: // hw_address: "hw-address" $@105 ":" "constant string"
#line 2563 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3962 "dhcp6_parser.cc"
    break;

  case 734: // $@106: %empty
#line 2569 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3971 "dhcp6_parser.cc"
    break;

  case 735: // hostname: "hostname" $@106 ":" "constant string"
#line 2572 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3981 "dhcp6_parser.cc"
    break;

  case 736: // $@107: %empty
#line 2578 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3990 "dhcp6_parser.cc"
    break;

  case 737: // flex_id_value: "flex-id" $@107 ":" "constant string"
#line 2581 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 4000 "dhcp6_parser.cc"
    break;

  case 738: // $@108: %empty
#line 2587 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4012 "dhcp6_parser.cc"
    break;

  case 739: // reservation_client_classes: "client-classes" $@108 ":" list_strings
#line 2593 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4021 "dhcp6_parser.cc"
    break;

  case 740: // $@109: %empty
#line 2601 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 4033 "dhcp6_parser.cc"
    break;

  case 741: // relay: "relay" $@109 ":" "{" relay_map "}"
#line 2607 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4042 "dhcp6_parser.cc"
    break;

  case 743: // $@110: %empty
#line 2618 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 4054 "dhcp6_parser.cc"
    break;

  case 744: // client_classes: "client-classes" $@110 ":" "[" client_classes_list "]"
#line 2624 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4063 "dhcp6_parser.cc"
    break;

  case 747: // client_classes_list: client_classes_list ","
#line 2631 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 4071 "dhcp6_parser.cc"
    break;

  case 748: // $@111: %empty
#line 2636 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4081 "dhcp6_parser.cc"
    break;

  case 749: // client_class_entry: "{" $@111 client_class_params "}"
#line 2640 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 4091 "dhcp6_parser.cc"
    break;

  case 754: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2652 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 4099 "dhcp6_parser.cc"
    break;

  case 771: // $@112: %empty
#line 2676 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4108 "dhcp6_parser.cc"
    break;

  case 772: // client_class_test: "test" $@112 ":" "constant string"
#line 2679 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4118 "dhcp6_parser.cc"
    break;

  case 773: // $@113: %empty
#line 2685 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4127 "dhcp6_parser.cc"
    break;

  case 774: // client_class_template_test: "template-test" $@113 ":" "constant string"
#line 2688 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4137 "dhcp6_parser.cc"
    break;

  case 775: // only_if_required: "only-if-required" ":" "boolean"
#line 2695 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4147 "dhcp6_parser.cc"
    break;

  case 776: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2701 "dhcp6_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4157 "dhcp6_parser.cc"
    break;

  case 777: // $@114: %empty
#line 2710 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 4169 "dhcp6_parser.cc"
    break;

  case 778: // server_id: "server-id" $@114 ":" "{" server_id_params "}"
#line 2716 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4180 "dhcp6_parser.cc"
    break;

  case 781: // server_id_params: server_id_params ","
#line 2725 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4188 "dhcp6_parser.cc"
    break;

  case 791: // $@115: %empty
#line 2741 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 4197 "dhcp6_parser.cc"
    break;

  case 792: // server_id_type: "type" $@115 ":" duid_type
#line 2744 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4206 "dhcp6_parser.cc"
    break;

  case 793: // duid_type: "LLT"
#line 2749 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4212 "dhcp6_parser.cc"
    break;

  case 794: // duid_type: "EN"
#line 2750 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4218 "dhcp6_parser.cc"
    break;

  case 795: // duid_type: "LL"
#line 2751 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4224 "dhcp6_parser.cc"
    break;

  case 796: // htype: "htype" ":" "integer"
#line 2754 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4234 "dhcp6_parser.cc"
    break;

  case 797: // $@116: %empty
#line 2760 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4243 "dhcp6_parser.cc"
    break;

  case 798: // identifier: "identifier" $@116 ":" "constant string"
#line 2763 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4253 "dhcp6_parser.cc"
    break;

  case 799: // time: "time" ":" "integer"
#line 2769 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4263 "dhcp6_parser.cc"
    break;

  case 800: // enterprise_id: "enterprise-id" ":" "integer"
#line 2775 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4273 "dhcp6_parser.cc"
    break;

  case 801: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2783 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4283 "dhcp6_parser.cc"
    break;

  case 802: // $@117: %empty
#line 2791 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4296 "dhcp6_parser.cc"
    break;

  case 803: // control_socket: "control-socket" $@117 ":" "{" control_socket_params "}"
#line 2798 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4305 "dhcp6_parser.cc"
    break;

  case 804: // $@118: %empty
#line 2803 "dhcp6_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4318 "dhcp6_parser.cc"
    break;

  case 805: // control_sockets: "control-sockets" $@118 ":" "[" control_socket_list "]"
#line 2810 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4327 "dhcp6_parser.cc"
    break;

  case 810: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2821 "dhcp6_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4335 "dhcp6_parser.cc"
    break;

  case 811: // $@119: %empty
#line 2826 "dhcp6_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4345 "dhcp6_parser.cc"
    break;

  case 812: // control_socket_entry: "{" $@119 control_socket_params "}"
#line 2830 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4353 "dhcp6_parser.cc"
    break;

  case 815: // control_socket_params: control_socket_params ","
#line 2836 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4361 "dhcp6_parser.cc"
    break;

  case 829: // $@120: %empty
#line 2856 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4370 "dhcp6_parser.cc"
    break;

  case 830: // control_socket_type: "socket-type" $@120 ":" control_socket_type_value
#line 2859 "dhcp6_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4379 "dhcp6_parser.cc"
    break;

  case 831: // control_socket_type_value: "unix"
#line 2865 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4385 "dhcp6_parser.cc"
    break;

  case 832: // control_socket_type_value: "http"
#line 2866 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4391 "dhcp6_parser.cc"
    break;

  case 833: // control_socket_type_value: "https"
#line 2867 "dhcp6_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4397 "dhcp6_parser.cc"
    break;

  case 834: // $@121: %empty
#line 2870 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4407 "dhcp6_parser.cc"
    break;

  case 835: // control_socket_name: "socket-name" $@121 ":" "constant string"
#line 2874 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4417 "dhcp6_parser.cc"
    break;

  case 836: // $@122: %empty
#line 2880 "dhcp6_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4427 "dhcp6_parser.cc"
    break;

  case 837: // control_socket_address: "socket-address" $@122 ":" "constant string"
#line 2884 "dhcp6_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4437 "dhcp6_parser.cc"
    break;

  case 838: // control_socket_port: "socket-port" ":" "integer"
#line 2890 "dhcp6_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4447 "dhcp6_parser.cc"
    break;

  case 839: // cert_required: "cert-required" ":" "boolean"
#line 2896 "dhcp6_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4457 "dhcp6_parser.cc"
    break;

  case 840: // $@123: %empty
#line 2902 "dhcp6_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4469 "dhcp6_parser.cc"
    break;

  case 841: // http_headers: "http-headers" $@123 ":" "[" http_header_list "]"
#line 2908 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4478 "dhcp6_parser.cc"
    break;

  case 846: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2919 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4486 "dhcp6_parser.cc"
    break;

  case 847: // $@124: %empty
#line 2924 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4496 "dhcp6_parser.cc"
    break;

  case 848: // http_header: "{" $@124 http_header_params "}"
#line 2928 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4504 "dhcp6_parser.cc"
    break;

  case 851: // http_header_params: http_header_params ","
#line 2934 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4512 "dhcp6_parser.cc"
    break;

  case 857: // $@125: %empty
#line 2946 "dhcp6_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4521 "dhcp6_parser.cc"
    break;

  case 858: // header_value: "value" $@125 ":" "constant string"
#line 2949 "dhcp6_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4531 "dhcp6_parser.cc"
    break;

  case 859: // $@126: %empty
#line 2957 "dhcp6_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4543 "dhcp6_parser.cc"
    break;

  case 860: // authentication: "authentication" $@126 ":" "{" auth_params "}"
#line 2963 "dhcp6_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4554 "dhcp6_parser.cc"
    break;

  case 863: // auth_params: auth_params ","
#line 2972 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4562 "dhcp6_parser.cc"
    break;

  case 871: // $@127: %empty
#line 2986 "dhcp6_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4571 "dhcp6_parser.cc"
    break;

  case 872: // auth_type: "type" $@127 ":" auth_type_value
#line 2989 "dhcp6_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4580 "dhcp6_parser.cc"
    break;

  case 873: // auth_type_value: "basic"
#line 2994 "dhcp6_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4586 "dhcp6_parser.cc"
    break;

  case 874: // $@128: %empty
#line 2997 "dhcp6_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4595 "dhcp6_parser.cc"
    break;

  case 875: // realm: "realm" $@128 ":" "constant string"
#line 3000 "dhcp6_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4605 "dhcp6_parser.cc"
    break;

  case 876: // $@129: %empty
#line 3006 "dhcp6_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4614 "dhcp6_parser.cc"
    break;

  case 877: // directory: "directory" $@129 ":" "constant string"
#line 3009 "dhcp6_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4624 "dhcp6_parser.cc"
    break;

  case 878: // $@130: %empty
#line 3015 "dhcp6_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4636 "dhcp6_parser.cc"
    break;

  case 879: // clients: "clients" $@130 ":" "[" clients_list "]"
#line 3021 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4645 "dhcp6_parser.cc"
    break;

  case 884: // not_empty_clients_list: not_empty_clients_list ","
#line 3032 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4653 "dhcp6_parser.cc"
    break;

  case 885: // $@131: %empty
#line 3037 "dhcp6_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4663 "dhcp6_parser.cc"
    break;

  case 886: // basic_auth: "{" $@131 clients_params "}"
#line 3041 "dhcp6_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4671 "dhcp6_parser.cc"
    break;

  case 889: // clients_params: clients_params ","
#line 3047 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4679 "dhcp6_parser.cc"
    break;

  case 897: // $@132: %empty
#line 3061 "dhcp6_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4688 "dhcp6_parser.cc"
    break;

  case 898: // user_file: "user-file" $@132 ":" "constant string"
#line 3064 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4698 "dhcp6_parser.cc"
    break;

  case 899: // $@133: %empty
#line 3070 "dhcp6_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4707 "dhcp6_parser.cc"
    break;

  case 900: // password_file: "password-file" $@133 ":" "constant string"
#line 3073 "dhcp6_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4717 "dhcp6_parser.cc"
    break;

  case 901: // $@134: %empty
#line 3081 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4729 "dhcp6_parser.cc"
    break;

  case 902: // dhcp_queue_control: "dhcp-queue-control" $@134 ":" "{" queue_control_params "}"
#line 3087 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4740 "dhcp6_parser.cc"
    break;

  case 905: // queue_control_params: queue_control_params ","
#line 3096 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4748 "dhcp6_parser.cc"
    break;

  case 912: // enable_queue: "enable-queue" ":" "boolean"
#line 3109 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4758 "dhcp6_parser.cc"
    break;

  case 913: // $@135: %empty
#line 3115 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4767 "dhcp6_parser.cc"
    break;

  case 914: // queue_type: "queue-type" $@135 ":" "constant string"
#line 3118 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4777 "dhcp6_parser.cc"
    break;

  case 915: // capacity: "capacity" ":" "integer"
#line 3124 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4787 "dhcp6_parser.cc"
    break;

  case 916: // $@136: %empty
#line 3130 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4796 "dhcp6_parser.cc"
    break;

  case 917: // arbitrary_map_entry: "constant string" $@136 ":" value
#line 3133 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4805 "dhcp6_parser.cc"
    break;

  case 918: // $@137: %empty
#line 3140 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4817 "dhcp6_parser.cc"
    break;

  case 919: // dhcp_ddns: "dhcp-ddns" $@137 ":" "{" dhcp_ddns_params "}"
#line 3146 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4828 "dhcp6_parser.cc"
    break;

  case 920: // $@138: %empty
#line 3153 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4838 "dhcp6_parser.cc"
    break;

  case 921: // sub_dhcp_ddns: "{" $@138 dhcp_ddns_params "}"
#line 3157 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4848 "dhcp6_parser.cc"
    break;

  case 924: // dhcp_ddns_params: dhcp_ddns_params ","
#line 3165 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4856 "dhcp6_parser.cc"
    break;

  case 936: // enable_updates: "enable-updates" ":" "boolean"
#line 3183 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4866 "dhcp6_parser.cc"
    break;

  case 937: // $@139: %empty
#line 3189 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4875 "dhcp6_parser.cc"
    break;

  case 938: // server_ip: "server-ip" $@139 ":" "constant string"
#line 3192 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4885 "dhcp6_parser.cc"
    break;

  case 939: // server_port: "server-port" ":" "integer"
#line 3198 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4895 "dhcp6_parser.cc"
    break;

  case 940: // $@140: %empty
#line 3204 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4904 "dhcp6_parser.cc"
    break;

  case 941: // sender_ip: "sender-ip" $@140 ":" "constant string"
#line 3207 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4914 "dhcp6_parser.cc"
    break;

  case 942: // sender_port: "sender-port" ":" "integer"
#line 3213 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4924 "dhcp6_parser.cc"
    break;

  case 943: // max_queue_size: "max-queue-size" ":" "integer"
#line 3219 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4934 "dhcp6_parser.cc"
    break;

  case 944: // $@141: %empty
#line 3225 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4943 "dhcp6_parser.cc"
    break;

  case 945: // ncr_protocol: "ncr-protocol" $@141 ":" ncr_protocol_value
#line 3228 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4952 "dhcp6_parser.cc"
    break;

  case 946: // ncr_protocol_value: "UDP"
#line 3234 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4958 "dhcp6_parser.cc"
    break;

  case 947: // ncr_protocol_value: "TCP"
#line 3235 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4964 "dhcp6_parser.cc"
    break;

  case 948: // $@142: %empty
#line 3238 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4973 "dhcp6_parser.cc"
    break;

  case 949: // ncr_format: "ncr-format" $@142 ":" "JSON"
#line 3241 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4983 "dhcp6_parser.cc"
    break;

  case 950: // $@143: %empty
#line 3249 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4995 "dhcp6_parser.cc"
    break;

  case 951: // config_control: "config-control" $@143 ":" "{" config_control_params "}"
#line 3255 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5005 "dhcp6_parser.cc"
    break;

  case 952: // $@144: %empty
#line 3261 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 5015 "dhcp6_parser.cc"
    break;

  case 953: // sub_config_control: "{" $@144 config_control_params "}"
#line 3265 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 5024 "dhcp6_parser.cc"
    break;

  case 956: // config_control_params: config_control_params ","
#line 3273 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 5032 "dhcp6_parser.cc"
    break;

  case 959: // $@145: %empty
#line 3283 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 5044 "dhcp6_parser.cc"
    break;

  case 960: // config_databases: "config-databases" $@145 ":" "[" database_list "]"
#line 3289 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5053 "dhcp6_parser.cc"
    break;

  case 961: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3294 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 5063 "dhcp6_parser.cc"
    break;

  case 962: // $@146: %empty
#line 3302 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 5075 "dhcp6_parser.cc"
    break;

  case 963: // loggers: "loggers" $@146 ":" "[" loggers_entries "]"
#line 3308 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5084 "dhcp6_parser.cc"
    break;

  case 966: // loggers_entries: loggers_entries ","
#line 3317 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 5092 "dhcp6_parser.cc"
    break;

  case 967: // $@147: %empty
#line 3323 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 5102 "dhcp6_parser.cc"
    break;

  case 968: // logger_entry: "{" $@147 logger_params "}"
#line 3327 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 5110 "dhcp6_parser.cc"
    break;

  case 971: // logger_params: logger_params ","
#line 3333 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 5118 "dhcp6_parser.cc"
    break;

  case 979: // debuglevel: "debuglevel" ":" "integer"
#line 3347 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 5128 "dhcp6_parser.cc"
    break;

  case 980: // $@148: %empty
#line 3353 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5137 "dhcp6_parser.cc"
    break;

  case 981: // severity: "severity" $@148 ":" "constant string"
#line 3356 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 5147 "dhcp6_parser.cc"
    break;

  case 982: // $@149: %empty
#line 3362 "dhcp6_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 5159 "dhcp6_parser.cc"
    break;

  case 983: // output_options_list: "output-options" $@149 ":" "[" output_options_list_content "]"
#line 3368 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5168 "dhcp6_parser.cc"
    break;

  case 986: // output_options_list_content: output_options_list_content ","
#line 3375 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 5176 "dhcp6_parser.cc"
    break;

  case 987: // $@150: %empty
#line 3380 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 5186 "dhcp6_parser.cc"
    break;

  case 988: // output_entry: "{" $@150 output_params_list "}"
#line 3384 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 5194 "dhcp6_parser.cc"
    break;

  case 991: // output_params_list: output_params_list ","
#line 3390 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 5202 "dhcp6_parser.cc"
    break;

  case 997: // $@151: %empty
#line 3402 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5211 "dhcp6_parser.cc"
    break;

  case 998: // output: "output" $@151 ":" "constant string"
#line 3405 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5221 "dhcp6_parser.cc"
    break;

  case 999: // flush: "flush" ":" "boolean"
#line 3411 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5231 "dhcp6_parser.cc"
    break;

  case 1000: // maxsize: "maxsize" ":" "integer"
#line 3417 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5241 "dhcp6_parser.cc"
    break;

  case 1001: // maxver: "maxver" ":" "integer"
#line 3423 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5251 "dhcp6_parser.cc"
    break;

  case 1002: // $@152: %empty
#line 3429 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5260 "dhcp6_parser.cc"
    break;

  case 1003: // pattern: "pattern" $@152 ":" "constant string"
#line 3432 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5270 "dhcp6_parser.cc"
    break;

  case 1004: // $@153: %empty
#line 3438 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5282 "dhcp6_parser.cc"
    break;

  case 1005: // compatibility: "compatibility" $@153 ":" "{" compatibility_params "}"
#line 3444 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5291 "dhcp6_parser.cc"
    break;

  case 1008: // compatibility_params: compatibility_params ","
#line 3451 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5299 "dhcp6_parser.cc"
    break;

  case 1011: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3460 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5309 "dhcp6_parser.cc"
    break;


#line 5313 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1445;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     485, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445,    49,    43,    34,    44,    62,
      83,    93,    98,   106,   147,   158,   167,   176,   209,   211,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,    43,  -174,
     110,   768,    56,  1448,   195,   281,   301,     2,    11,   335,
     -80,   258,   111, -1445,   136,   238,   243,   241,   261, -1445,
      75, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   300,   314,
     325,   327,   331,   334,   365,   394,   417,   418,   430,   433,
     445,   448,   449, -1445,   469,   478,   484,   491,   503, -1445,
   -1445, -1445,   512,   516,   520,   521,   523,   527,   528, -1445,
   -1445, -1445,   530, -1445, -1445, -1445, -1445, -1445, -1445,   531,
     534,   535, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445,   537, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   541,
     543,   547, -1445, -1445,   550, -1445,    81, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445,   554,   557,   559,   560, -1445,   101, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
     563,   565, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
     109, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445,   566, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445,   135, -1445, -1445, -1445, -1445, -1445, -1445,
     567, -1445,   570,   571, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445,   145, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445,   273,   292, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445,   298, -1445, -1445,   573, -1445, -1445, -1445,
     574, -1445, -1445,   403,   428, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   576,   577,
     578, -1445, -1445, -1445, -1445, -1445,   425,   471, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445,   159, -1445, -1445, -1445,   579, -1445,   582, -1445,
     584,   585, -1445, -1445, -1445, -1445, -1445,   174, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   586,   190,
   -1445, -1445, -1445, -1445,    43,    43, -1445,  -131,   587, -1445,
   -1445,   588,   589,   592,   596,   599,   600,   363,   364,   366,
     368,   369,   370,   373,   376,   375,   378,   379,   383,   386,
     388,   387,   603,   390,   391,   392,   393,   399,   605,   621,
     634,   400,   405,   411,   414,   416,   419,   422,   638,   656,
     658,   426,   663,   669,   672,   675,   677,   680,   441,   442,
     443,   685,   687,   688,   691,   692,   693,   694,   695,   697,
     461,   698,   701,   704,   706,   722,   723,   724,   487,   492,
     493,   725,   726, -1445,   768, -1445,   728,   495,   496,   499,
     500,    56, -1445,   729,   730,   731,   739,   743,   506,   507,
     746,   748,   750,   751,   752,  1448, -1445,   753,   517,   195,
   -1445,   754,   518,   757,   522,   526,   281, -1445,   758,   759,
     761,   765,   766,   767,   772,   777, -1445,   301, -1445,   778,
     780,   544,   781,   783,   784,   548, -1445,    11,   789,   551,
     552,   553,   790, -1445,   335,   794,   795,   232, -1445,   556,
     797,   568,   801,   569,   572,   804,   805,   258, -1445,   808,
     575,   111, -1445, -1445, -1445,   809,   811,   580,   812,   813,
     849,   850,   810, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   617, -1445,
   -1445, -1445, -1445, -1445,  -128,   618,   619, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445,   856,   857,   858, -1445,   623,   624,
     398,   865,   864,   631, -1445, -1445, -1445,   868,   870,   871,
     872,   873,   875,   876,   878,   879, -1445,   880,   881,   877,
     882,   890,   636,   657, -1445, -1445, -1445,   895,   894, -1445,
     897, -1445, -1445, -1445, -1445, -1445,   898,   899,   664,   665,
     666, -1445, -1445,   897,   897,   897,   668,   903, -1445,   670,
   -1445, -1445,   671, -1445,   673, -1445, -1445, -1445,   897,   897,
     897,   897,   674,   678,   681,   682, -1445,   683,   684, -1445,
     689,   690,   696, -1445, -1445,   702, -1445, -1445, -1445,   897,
   -1445,   703,   864, -1445, -1445,   705, -1445,   707, -1445, -1445,
      30,   610, -1445,   908, -1445, -1445,    43,   768, -1445,   111,
      56,   177,   177,   909, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445,   911,   914,   919, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445,   921, -1445, -1445, -1445,  -104,    43,    40,
     279,   922,   925,   926,   104,    74,   234,   198,   927,   -62,
     258, -1445, -1445,   931,  -184, -1445, -1445,   932,   935, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445,   806, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445,   909, -1445,   228,   271,   290, -1445, -1445,
   -1445, -1445,   941,   945,   946,   947,   948,   949,   950,   951,
     952,   953, -1445,   954,   956, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445,   291, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445,   304, -1445,   955,   769, -1445, -1445,   958,   959, -1445,
   -1445,   960,   962, -1445, -1445,   961,   965, -1445, -1445,   963,
     967, -1445, -1445, -1445,   191, -1445, -1445, -1445,   966, -1445,
   -1445, -1445,   245, -1445, -1445, -1445, -1445, -1445,   322, -1445,
   -1445, -1445, -1445,   260, -1445, -1445,   968,   970, -1445, -1445,
     969,   973, -1445,   974,   981,   982,   983,   984,   985,   336,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   986,
     987,   988, -1445, -1445, -1445, -1445,   338, -1445, -1445, -1445,
   -1445, -1445, -1445,   990,   991,   992, -1445,   339, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445,   993, -1445,   994,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445,   340, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445,   971,   996, -1445,
     997, -1445,   998, -1445, -1445, -1445,   348, -1445, -1445, -1445,
   -1445, -1445,   351, -1445,   277, -1445,   999, -1445,   357, -1445,
   -1445,   763, -1445,  1000,  1002, -1445, -1445,  1001,  1005, -1445,
   -1445,  1003,  1004, -1445, -1445, -1445,  1008,  1009,  1010,  1011,
     774,   727,   775,   756,   776,   779,   782,   785,   786,   787,
    1015,   788,   792,  1016,  1018,  1019,  1021,  1022,   177, -1445,
   -1445,   177, -1445,   909,  1448, -1445,   911,    11, -1445,   914,
     335, -1445,   919,  1546, -1445,   921,  -104, -1445, -1445,    40,
   -1445,  1026,  1027,   279, -1445,   265,   922, -1445,   301, -1445,
     925,   -80, -1445,   926,   793,   796,   798,   799,   802,   819,
     104, -1445,  1033,  1039,   821,   822,   824,    74, -1445,   807,
     825,   830,   234, -1445,  1044,  1049,  1069,   832,  1073,   835,
    1076,   198, -1445,   198, -1445,   927,   838,  1081,   845,  1084,
     -62, -1445, -1445,   221,   931, -1445,   851,  -184, -1445, -1445,
    1087,  1098,   195, -1445,   932,   281, -1445,   935, -1445, -1445,
     862,   863,   866,   889, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445,   470, -1445, -1445,   891,   900,   924,
     429,   930, -1445,   359, -1445,   367, -1445,  1101, -1445,  1105,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445,   381, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445,   937,   940, -1445, -1445, -1445,
    1116,  1119, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445,  1130,  1141, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445,  1154, -1445,   382, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445,   352,   942, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445,   353,   944,   995, -1445,  1169, -1445,  1182,
   -1445,   407, -1445, -1445,  1006, -1445,    43, -1445, -1445,  1186,
   -1445, -1445, -1445, -1445, -1445,   427, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445,  1013,   460, -1445,   464, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445,  1546, -1445, -1445, -1445,
    1188,  1189,   980,   989, -1445,   265, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   117,
    1193, -1445, -1445, -1445,  1191,   972,  1192,   221, -1445, -1445,
   -1445, -1445, -1445,  1020,  1023, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445,   486, -1445, -1445, -1445, -1445,
   -1445, -1445,  1219,  1226, -1445,  1230, -1445,  1024, -1445, -1445,
   -1445,  1235,  1236,  1237,  1240,   117, -1445,   -24, -1445,  1193,
    1238, -1445,  1067,  1028,  1030,  1245, -1445, -1445, -1445, -1445,
   -1445, -1445,   488, -1445, -1445, -1445, -1445,   302, -1445, -1445,
   -1445, -1445, -1445,  1244,  1248,   -24, -1445,    32,  1238, -1445,
   -1445,  1250,  1254, -1445,  1032, -1445, -1445,  1255,  1258,  1259,
   -1445,   489, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   130,
   -1445,  1244, -1445,  1264,  1031,  1034,  1036,  1270,    32, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445,   490, -1445, -1445,
   -1445, -1445,  1038, -1445, -1445, -1445,  1040, -1445,  1276,  1278,
     130, -1445, -1445, -1445,  1042,  1043, -1445, -1445, -1445
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   207,     9,   401,    11,
     625,    13,   670,    15,   705,    17,   540,    19,   549,    21,
     588,    23,   363,    25,   920,    27,   952,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   707,     0,   551,   590,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   145,   950,   205,   226,   228,   230,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   195,     0,     0,     0,     0,     0,   165,
     172,   174,     0,     0,     0,     0,     0,     0,     0,   392,
     538,   579,     0,   198,   200,   178,   477,   657,   659,     0,
       0,     0,   319,   338,   328,   308,   743,   696,   354,   375,
     777,     0,   340,   802,   804,   901,   918,   188,   190,     0,
       0,     0,   962,  1004,     0,   144,     0,    69,    72,    73,
      74,    75,    76,    77,    78,    79,    80,   111,   112,   113,
     114,   115,   116,    81,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   118,   119,   133,
     134,   135,   107,   141,   142,   143,   137,   138,   139,    84,
      85,    86,    87,   104,    88,    90,    89,   136,    94,    95,
      82,   108,   109,   110,    83,    92,    93,   102,   103,   105,
      91,    96,    97,    98,    99,   100,   101,   106,   117,   140,
     220,     0,     0,     0,     0,   219,     0,   209,   212,   213,
     214,   215,   216,   217,   218,   616,   661,   458,   460,   462,
       0,     0,   466,   468,   470,   464,   740,   457,   406,   407,
     408,   409,   410,   411,   412,   413,   433,   434,   435,   436,
     437,   438,   441,   442,   443,   444,   445,   446,   447,   448,
     449,   450,   451,   452,   453,   439,   440,   454,   455,   456,
       0,   403,   417,   418,   419,   422,   423,   424,   425,   427,
     428,   429,   420,   421,   414,   415,   431,   432,   416,   426,
     430,   654,     0,   653,   637,   638,   639,   640,   641,   642,
     643,   644,   645,   646,   647,   648,   649,   650,   633,   634,
     635,   636,   632,     0,   627,   630,   631,   651,   652,   689,
       0,   692,     0,     0,   688,   680,   681,   682,   683,   679,
     678,   686,   687,     0,   672,   675,   676,   684,   685,   677,
     738,   724,   726,   728,   730,   732,   734,   736,   723,   720,
     721,   722,     0,   708,   709,   714,   715,   716,   712,   717,
     718,   719,   713,     0,   569,   275,     0,   573,   571,   576,
       0,   565,   566,     0,   552,   553,   556,   568,   557,   558,
     559,   575,   560,   561,   562,   563,   564,   607,     0,     0,
       0,   614,   605,   606,   609,   610,     0,   591,   592,   595,
     596,   597,   598,   599,   600,   601,   604,   602,   603,   371,
     373,   368,     0,   365,   369,   370,     0,   937,     0,   940,
       0,     0,   944,   948,   935,   933,   934,     0,   922,   925,
     926,   927,   928,   929,   930,   931,   932,   959,     0,     0,
     954,   957,   958,    47,    52,     0,    39,    45,     0,    66,
      62,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    60,    71,    68,     0,     0,     0,     0,
       0,   211,   208,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   405,   402,     0,     0,   629,
     626,     0,     0,     0,     0,     0,   674,   671,     0,     0,
       0,     0,     0,     0,     0,     0,   706,   711,   541,     0,
       0,     0,     0,     0,     0,     0,   550,   555,     0,     0,
       0,     0,     0,   589,   594,     0,     0,   367,   364,     0,
       0,     0,     0,     0,     0,     0,     0,   924,   921,     0,
       0,   956,   953,    51,    43,     0,     0,     0,     0,     0,
       0,     0,     0,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,     0,   193,
     194,   162,   163,   164,     0,     0,     0,   176,   177,   184,
     185,   186,   187,   192,     0,     0,     0,   197,     0,     0,
       0,     0,     0,     0,   472,   473,   474,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   801,     0,     0,     0,
       0,     0,     0,     0,   202,   203,   204,     0,     0,    70,
       0,   222,   223,   224,   225,   210,     0,     0,     0,     0,
       0,   475,   476,     0,     0,     0,     0,     0,   404,     0,
     656,   628,     0,   691,     0,   694,   695,   673,     0,     0,
       0,     0,     0,     0,     0,     0,   710,     0,     0,   567,
       0,     0,     0,   578,   554,     0,   611,   612,   613,     0,
     593,     0,     0,   366,   936,     0,   939,     0,   942,   943,
       0,     0,   923,     0,   961,   955,     0,     0,   146,     0,
       0,     0,     0,   232,   196,   167,   168,   169,   170,   171,
     166,   173,   175,   394,   542,   581,   199,   201,   180,   181,
     182,   183,   179,   479,    40,   658,   660,     0,    48,     0,
       0,     0,   698,   356,     0,     0,     0,     0,   806,     0,
       0,   189,   191,     0,     0,    53,   221,   618,   663,   459,
     461,   463,   467,   469,   471,   465,     0,   655,   690,   693,
     739,   725,   727,   729,   731,   733,   735,   737,   570,   276,
     574,   572,   577,   608,   615,   372,   374,   938,   941,   946,
     947,   945,   949,   232,    44,     0,     0,     0,   266,   268,
     270,   272,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   285,     0,     0,   293,   295,   297,   299,   301,
     302,   303,   304,   305,   306,   265,     0,   239,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   256,   257,   258,   259,   255,   260,   261,   262,   263,
     264,     0,   237,     0,   233,   234,   399,     0,   395,   396,
     547,     0,   543,   544,   586,     0,   582,   583,   484,     0,
     480,   481,   326,   327,     0,   321,   324,   325,     0,   336,
     337,   333,     0,   330,   334,   335,   315,   317,     0,   310,
     313,   314,   748,     0,   745,   703,     0,   699,   700,   361,
       0,   357,   358,     0,     0,     0,     0,     0,     0,     0,
     377,   380,   381,   382,   383,   384,   385,   791,   797,     0,
       0,     0,   790,   787,   788,   789,     0,   779,   782,   785,
     783,   784,   786,     0,     0,     0,   350,     0,   342,   345,
     346,   347,   348,   349,   829,   834,   836,     0,   859,     0,
     840,   828,   821,   822,   823,   826,   827,     0,   813,   816,
     817,   818,   819,   824,   825,   820,   811,     0,   807,   808,
       0,   913,     0,   916,   909,   910,     0,   903,   906,   907,
     908,   911,     0,   967,     0,   964,     0,  1010,     0,  1006,
    1009,    55,   623,     0,   619,   620,   668,     0,   664,   665,
     742,     0,     0,    64,   951,   206,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   241,   227,
     229,     0,   231,   236,     0,   393,   398,   551,   539,   546,
     590,   580,   585,     0,   478,   483,   323,   320,   339,   332,
     329,     0,     0,   312,   309,   750,   747,   744,   707,   697,
     702,     0,   355,   360,     0,     0,     0,     0,     0,     0,
     379,   376,     0,     0,     0,     0,     0,   781,   778,     0,
       0,     0,   344,   341,     0,     0,     0,     0,     0,     0,
       0,   815,   803,     0,   805,   810,     0,     0,     0,     0,
     905,   902,   919,     0,   966,   963,     0,  1008,  1005,    57,
       0,    56,     0,   617,   622,     0,   662,   667,   741,   960,
       0,     0,     0,     0,   274,   277,   278,   279,   280,   281,
     282,   283,   292,   284,     0,   290,   291,     0,     0,     0,
       0,     0,   240,     0,   235,     0,   397,     0,   545,     0,
     584,   537,   504,   505,   506,   508,   509,   510,   493,   494,
     513,   514,   515,   516,   517,   518,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   531,   532,   533,   519,
     520,   534,   535,   536,   489,   490,   491,   492,   500,   501,
     502,   503,   497,   498,   499,   507,     0,   486,   495,   511,
     512,   496,   482,   322,   331,     0,     0,   311,   771,   773,
       0,     0,   769,   763,   764,   765,   766,   767,   768,   770,
     760,   761,   762,     0,   751,   752,   755,   756,   757,   758,
     759,   746,     0,   701,     0,   359,   386,   387,   388,   389,
     390,   391,   378,     0,     0,   796,   799,   800,   780,   351,
     352,   353,   343,     0,     0,     0,   838,     0,   839,     0,
     814,     0,   809,   912,     0,   915,     0,   904,   982,     0,
     980,   978,   972,   976,   977,     0,   969,   974,   975,   973,
     965,  1011,  1007,    54,    59,     0,   621,     0,   666,   267,
     269,   271,   273,   287,   288,   289,   286,   294,   296,   298,
     300,   307,   238,   400,   548,   587,   488,   485,   316,   318,
       0,     0,     0,     0,   749,   754,   704,   362,   793,   794,
     795,   792,   798,   831,   832,   833,   830,   835,   837,     0,
     842,   812,   914,   917,     0,     0,     0,   971,   968,    58,
     624,   669,   487,     0,     0,   775,   776,   753,   871,   874,
     876,   878,   870,   869,   868,     0,   861,   864,   865,   866,
     867,   847,     0,   843,   844,     0,   979,     0,   970,   772,
     774,     0,     0,     0,     0,   863,   860,     0,   841,   846,
       0,   981,     0,     0,     0,     0,   862,   857,   856,   852,
     854,   855,     0,   849,   853,   845,   987,     0,   984,   873,
     872,   875,   877,   880,     0,   851,   848,     0,   986,   983,
     885,     0,   881,   882,     0,   850,   997,     0,     0,     0,
    1002,     0,   989,   992,   993,   994,   995,   996,   985,     0,
     879,   884,   858,     0,     0,     0,     0,     0,   991,   988,
     897,   899,   896,   890,   892,   894,   895,     0,   887,   891,
     893,   883,     0,   999,  1000,  1001,     0,   990,     0,     0,
     889,   886,   998,  1003,     0,     0,   888,   898,   900
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445,   -10, -1445,  -639, -1445,
     524, -1445, -1445, -1445, -1445,   477, -1445,  -254, -1445, -1445,
   -1445,   -71, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   510,
     734, -1445, -1445,     4,    12,    22,    38,    41,    42,   -57,
     -54,   -35,   -15,    97,   100,   102,   103, -1445,    20,    23,
      45,    48, -1445, -1445,    55, -1445,    60, -1445,    66,   105,
      71, -1445, -1445,    73,    76,    78,    84,    90, -1445,    95,
   -1445,   107, -1445, -1445, -1445, -1445, -1445,   108, -1445,   113,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   509,   732,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445,   431, -1445,   187, -1445,  -761,   193, -1445, -1445,
   -1444, -1445, -1443, -1445, -1445, -1445, -1445,   -55, -1445,  -802,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445,  -806, -1445,  -800, -1445,  -797, -1445,    82,
   -1445, -1445, -1445, -1445, -1445, -1445,   172, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445,   180,  -787, -1445, -1445, -1445, -1445,
     178, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   146, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445,   166, -1445, -1445, -1445,
     169,   699, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   161,
   -1445, -1445, -1445, -1445, -1445, -1445, -1088, -1445, -1445, -1445,
     196, -1445, -1445, -1445,   200,   733, -1445, -1445, -1087, -1445,
   -1086, -1445,    61, -1445,    85, -1445,   121, -1445,   125, -1445,
     115,   118,   119, -1445, -1085, -1445, -1445, -1445, -1445,   194,
   -1445, -1445,   -64,  1234, -1445, -1445, -1445, -1445, -1445,   204,
   -1445, -1445, -1445,   208, -1445,   710, -1445,   -65, -1445, -1445,
   -1445, -1445, -1445,   -61, -1445, -1445, -1445, -1445, -1445,   -29,
   -1445, -1445, -1445,   206, -1445, -1445, -1445,   210, -1445,   709,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445,   140, -1445, -1445, -1445,   143,   760,
   -1445, -1445,   -63,   -42, -1445,   -13, -1445, -1445, -1445, -1445,
   -1445,   142, -1445, -1445, -1445,   148,   741, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445,   -58, -1445, -1445, -1445,   201, -1445,
   -1445, -1445,   207, -1445,   735,   501, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1084, -1445, -1445, -1445, -1445, -1445,   212, -1445, -1445,
   -1445,   -45, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445,   197, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   181, -1445,
     179,   184, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445,  -101, -1445, -1445,  -126, -1445,
   -1445, -1445, -1445, -1445,   -95, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445,  -150, -1445, -1445,  -177,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445,   185, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   538,   737,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445,   581,   736, -1445,
   -1445, -1445, -1445, -1445, -1445,   188, -1445, -1445,   -53, -1445,
   -1445, -1445, -1445, -1445, -1445,  -119, -1445, -1445,  -142, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   192,
   -1445
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     805,    87,    88,    41,    68,    84,    85,   826,  1061,  1180,
    1181,   895,    43,    70,    90,   478,    91,    45,    71,   166,
     167,   168,   481,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   508,   790,   188,   509,   189,   510,   190,   191,
     192,   524,   802,   193,   194,   195,   196,   197,   546,   198,
     547,   199,   200,   201,   202,   502,   203,   204,   522,   205,
     523,   206,   207,   208,   209,   483,    47,    72,   246,   247,
     248,   556,   249,   250,   251,   252,   210,   484,   211,   485,
     212,   486,   923,   924,   925,  1101,   896,   897,   898,  1076,
     899,  1077,   900,  1078,   901,  1079,   902,   903,   600,   904,
     905,   906,   907,   908,   909,   910,   911,   912,  1090,  1366,
     913,   914,   915,   916,  1093,   917,  1094,   918,  1095,   919,
    1096,   920,  1097,   213,   534,   958,   959,   960,  1121,   961,
    1122,   214,   531,   944,   945,   946,   947,   215,   533,   952,
     953,   954,   955,   216,   532,   217,   541,  1007,  1008,  1009,
    1010,  1011,   218,   537,   970,   971,   972,  1131,    63,    80,
     442,   443,   444,   615,   445,   616,   219,   538,   979,   980,
     981,   982,   983,   984,   985,   986,   220,   518,   927,   928,
     929,  1104,    49,    73,   300,   301,   302,   565,   303,   566,
     304,   567,   305,   573,   306,   570,   307,   571,   308,   572,
     221,   222,   223,   312,   313,   224,   525,   939,   940,   941,
    1113,  1266,  1267,   225,   519,    57,    77,   931,   932,   933,
    1107,    59,    78,   403,   404,   405,   406,   407,   408,   409,
     599,   410,   603,   411,   602,   412,   413,   604,   414,   226,
     520,   935,   936,   937,  1110,    61,    79,   426,   427,   428,
     429,   430,   608,   431,   432,   433,   434,   435,   436,   612,
     315,   563,  1063,  1064,  1065,  1182,    51,    74,   343,   344,
     345,   577,   346,   227,   526,   228,   527,   318,   564,  1067,
    1068,  1069,  1185,    53,    75,   363,   364,   365,   581,   366,
     367,   583,   368,   369,   229,   536,   966,   967,   968,  1128,
      55,    76,   382,   383,   384,   385,   589,   386,   590,   387,
     591,   388,   592,   389,   593,   390,   594,   391,   595,   392,
     588,   320,   574,  1071,   230,   535,   963,   964,  1125,  1293,
    1294,  1295,  1296,  1297,  1380,  1298,  1381,  1299,  1300,   231,
     539,   996,   997,   998,  1142,  1391,   999,  1000,  1143,  1001,
    1002,   232,   233,   542,   234,   543,  1037,  1038,  1039,  1163,
    1027,  1028,  1029,  1154,  1396,  1030,  1155,  1031,  1156,  1032,
    1033,  1034,  1160,  1432,  1433,  1434,  1447,  1462,  1463,  1464,
    1474,  1035,  1158,  1425,  1426,  1427,  1441,  1470,  1428,  1442,
    1429,  1443,  1430,  1444,  1481,  1482,  1483,  1499,  1517,  1518,
    1519,  1528,  1520,  1529,   235,   544,  1046,  1047,  1048,  1049,
    1167,  1050,  1051,  1169,   236,   545,    65,    81,   457,   458,
     459,   460,   620,   461,   462,   622,   463,   464,   465,   625,
     861,   466,   626,   237,   482,    67,    82,   469,   470,   471,
     629,   472,   238,   551,  1054,  1055,  1173,  1345,  1346,  1347,
    1348,  1406,  1349,  1404,  1467,  1468,  1477,  1491,  1492,  1493,
    1503,  1494,  1495,  1496,  1497,  1507,   239,   552,  1058,  1059,
    1060
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     165,   245,   267,   323,   354,   378,    38,   401,   422,   441,
     454,  1022,   360,   993,   424,   319,   274,  1023,   425,   275,
    1024,   921,   951,   402,   423,  1255,  1256,  1257,  1265,  1271,
     253,   316,   347,   361,   380,   394,   415,   437,   276,   455,
     942,    42,  1056,   804,   314,   342,   359,   379,    31,    30,
      32,    44,    33,   137,   138,  1513,  1514,   164,   277,   254,
     317,   348,   362,   381,   395,   416,   438,    86,   456,    46,
     439,   440,   240,   241,   242,   243,   244,   268,   479,   785,
     786,   787,   788,   480,   554,   269,  1513,  1514,   130,   555,
      48,   137,   138,   282,   324,   270,   283,   325,   987,   395,
      50,   396,   397,   873,   561,    52,   398,   399,   400,   562,
     635,   271,   575,    54,   272,   273,   789,   576,   284,   326,
      89,   285,   327,   804,   467,   468,   137,   138,   286,   328,
    1040,  1041,  1042,   287,   329,   338,   355,   943,   579,   288,
     330,  1418,   473,   580,   290,   331,   291,   332,   586,   292,
     333,   293,   334,   587,    56,   869,   870,   294,   335,   339,
     356,   164,   617,   295,   336,    58,  1457,   618,   296,   337,
     278,   137,   138,   279,    60,   280,   281,   627,   289,  1043,
     297,   298,   628,    62,   942,   949,   299,   950,   309,   137,
     138,   310,   311,   631,  1116,   340,   357,  1117,   632,   341,
     358,   868,   869,   870,   871,   872,   873,   874,   875,   876,
     877,   878,   879,   880,   881,   882,    64,   164,    66,   883,
     884,   885,   886,   887,   888,   889,   890,   891,   892,   893,
     894,   554,   137,   138,   859,   860,  1073,   988,   989,   990,
     991,   474,   885,   886,   887,   137,   138,   475,  1119,   476,
    1486,  1120,   164,  1487,  1488,  1489,  1490,   973,   974,   975,
     976,   977,   978,  1126,   477,   395,  1127,   116,   117,   118,
     119,   120,   121,   122,   631,   124,   125,   126,   127,  1074,
    1174,   596,   131,  1175,    34,    35,    36,    37,  1255,  1256,
    1257,  1265,  1271,   561,  1098,   597,   135,   164,  1075,  1099,
    1419,  1420,  1421,   321,   487,  1478,   598,  1098,  1479,   395,
     137,   138,  1100,   137,   138,   164,  1510,  1511,   488,    98,
      99,   100,   101,   102,   103,  1123,   262,   263,   264,   489,
    1124,   490,   951,   265,   322,   491,   137,   138,   492,  1140,
    1213,  1147,  1152,  1161,  1141,   993,  1148,  1153,  1162,   137,
     138,  1170,   131,   395,   627,  1022,  1171,  1022,   164,  1172,
    1177,  1023,  1098,  1023,  1024,  1178,  1024,  1372,   131,   493,
     575,   164,  1014,   137,   138,  1373,  1015,  1016,  1017,  1018,
     137,   138,   439,   440,  1376,   617,  1019,  1020,   131,  1377,
    1387,   349,   350,   351,   352,   353,   137,   138,   494,  1278,
    1279,  1280,  1281,  1003,  1004,  1005,   157,   158,   956,   957,
    1161,   606,   262,   263,   264,  1401,   137,   138,   164,   265,
     322,   495,   496,   395,   417,   396,   397,   418,   419,   420,
    1407,   607,   370,   613,   497,  1408,   164,   498,  1338,   164,
    1339,  1340,   371,   372,   373,   374,   375,   376,   377,   499,
     137,   138,   500,   501,   446,   447,   448,   449,   450,   451,
     452,   453,   164,   579,   633,   634,   421,   586,  1410,   832,
     833,   834,  1411,   503,   614,   164,   888,   889,   890,   891,
     892,   893,   504,   165,   840,   841,   842,   843,   505,  1445,
     245,  1475,  1508,  1530,  1446,   506,  1476,  1509,  1531,   164,
     798,   799,   800,   801,   267,   854,   164,   507,   323,  1363,
    1364,  1365,  1388,  1389,  1390,   354,   511,   319,   274,   253,
     512,   275,   164,   360,   513,   514,   378,   515,  1393,  1394,
    1395,   516,   517,   316,   521,   528,   401,   347,   529,   530,
     276,   540,   164,   422,   361,   548,   314,   549,   254,   424,
     342,   550,   402,   425,   553,   380,   454,   359,   557,   423,
     277,   558,   317,   559,   560,   415,   348,   568,   379,   569,
     578,   582,   437,   362,   584,   585,   164,   601,   605,   268,
     609,   610,   611,   619,   381,   455,   621,   269,   623,   624,
     630,   636,   637,   638,   416,   282,   639,   270,   283,   324,
     640,   438,   325,   641,   642,   643,   644,   658,   645,   664,
     646,   647,   648,   271,   456,   649,   272,   273,   650,   651,
     284,   652,   653,   285,   326,   665,   654,   327,   655,   657,
     286,   656,   659,   660,   328,   287,   661,   662,   666,   329,
     338,   288,   674,   663,   667,   330,   290,   355,   291,   668,
     331,   292,   332,   293,   669,   333,   670,   334,   671,   294,
     675,   672,   676,   335,   339,   295,   673,   678,   677,   336,
     296,   356,   278,   679,   337,   279,   680,   280,   281,   681,
     289,   682,   297,   298,   683,   684,   685,   686,   299,   687,
     309,   688,   689,   310,   311,   690,   691,   692,   693,   694,
     340,   695,   697,   696,   341,   698,   165,   357,   699,   245,
     700,   358,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,   701,   702,   703,   707,
     708,   704,   710,   716,   717,   718,   705,   706,   253,   711,
     712,   713,   714,   719,   992,  1006,  1021,   720,   721,   454,
     723,   722,   724,  1057,   725,   726,   727,   729,   732,   730,
     733,   734,   738,   739,   735,   740,   864,   254,   736,   741,
     742,   743,  1103,   994,  1012,  1025,   744,  1044,   455,    92,
      93,   745,   747,    94,   748,   750,   749,   751,   752,    95,
      96,    97,   753,   755,   759,   756,   757,   758,   761,   762,
     764,   765,   995,  1013,  1026,   767,  1045,   456,   770,   771,
     766,   768,   773,   776,   769,   783,   862,   774,   777,   779,
     780,   778,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   781,   782,   784,   791,
     792,   793,   794,   795,   796,   797,   132,   133,   134,   135,
     803,    32,   806,   807,   136,   808,   809,   821,   811,   810,
     812,   813,   818,   137,   138,   814,   815,   816,   817,   819,
     139,   140,   141,   142,   143,   144,   145,   820,   822,   146,
     823,   824,   825,   827,   828,   829,   830,   831,   147,   835,
     836,   837,   838,   863,   839,   844,   922,   148,   926,   845,
     149,   930,   846,   847,   848,   849,   934,   150,   938,   962,
     850,   851,   965,   969,  1036,   151,   152,   852,  1053,  1062,
     153,   154,  1066,   853,   855,  1080,   857,   371,   858,  1081,
    1082,  1083,  1084,  1085,  1086,  1087,  1088,  1089,  1091,   155,
    1092,  1102,  1106,   156,  1105,  1109,  1108,  1111,  1112,  1114,
    1115,  1195,  1118,  1130,  1129,  1132,  1133,  1164,  1134,   157,
     158,   159,   160,   161,   162,  1135,  1136,  1137,  1138,  1139,
    1144,  1145,  1146,   163,  1149,  1150,  1151,  1157,  1159,  1165,
    1197,  1166,  1168,  1176,  1179,  1184,  1183,  1186,  1187,   164,
    1189,  1188,  1190,  1191,  1192,  1193,  1194,  1196,  1198,  1204,
    1207,  1199,  1208,  1209,  1200,  1210,  1211,  1201,  1202,  1203,
    1275,  1276,  1205,   267,  1206,  1306,   401,  1313,  1307,   422,
    1308,  1309,  1221,  1314,  1310,   424,   319,   274,  1323,   425,
     275,  1319,   402,  1324,  1282,   423,  1228,   378,  1254,  1229,
     441,  1311,   316,  1315,  1316,   415,  1317,  1320,   437,   276,
    1289,  1269,  1321,  1325,  1326,   314,   992,  1327,  1230,  1328,
    1329,  1006,  1333,  1291,  1268,  1334,   380,  1335,  1336,   277,
    1021,   317,  1021,  1353,   416,  1351,  1290,   438,  1231,   379,
    1270,  1354,  1341,  1359,  1360,   994,  1057,  1361,   268,  1374,
    1012,   323,  1292,  1375,   354,   381,   269,  1222,  1342,  1025,
    1382,  1025,   360,  1383,   282,  1223,   270,   283,  1044,  1283,
    1362,  1343,  1367,  1236,   995,  1224,  1237,  1284,  1384,  1013,
     347,  1368,   271,   361,  1385,   272,   273,  1285,  1026,   284,
    1026,  1225,   285,   342,  1226,  1227,   359,  1045,  1238,   286,
    1344,  1239,  1386,  1286,   287,  1369,  1287,  1288,  1240,   348,
     288,  1371,   362,  1241,  1258,   290,  1399,   291,  1378,  1242,
     292,  1379,   293,  1392,  1244,  1397,  1245,  1400,   294,  1246,
    1405,  1247,  1413,  1414,   295,  1435,  1437,  1248,  1259,   296,
    1431,   278,   324,  1249,   279,   325,   280,   281,  1250,   289,
    1232,   297,   298,  1233,  1436,  1234,  1235,   299,  1243,   309,
    1251,  1252,   310,   311,  1415,  1448,  1253,   326,  1262,  1449,
     327,  1263,  1264,  1416,  1260,  1450,  1398,   328,  1261,  1452,
    1453,  1454,   329,   338,  1455,  1466,   355,  1402,   330,  1469,
    1473,  1480,  1484,   331,  1409,   332,  1500,  1501,   333,  1504,
     334,  1439,  1505,  1506,  1440,  1451,   335,   339,  1522,  1471,
     356,  1472,   336,  1502,  1526,  1523,  1524,   337,  1525,  1532,
    1534,  1533,  1535,  1537,  1538,   948,   856,   865,   709,   867,
    1214,  1212,  1370,   715,  1072,  1277,  1273,  1274,  1322,  1305,
    1304,  1312,  1216,   340,  1215,  1221,   357,   341,   728,  1272,
     358,   393,  1412,  1218,  1282,  1217,   763,   754,  1220,  1228,
    1219,  1254,  1229,   760,  1356,  1355,  1403,   737,  1422,  1358,
    1289,  1303,   746,  1357,  1269,  1302,  1341,  1070,  1301,   731,
    1417,  1230,  1331,  1291,  1318,  1330,  1332,  1268,  1465,  1485,
    1456,  1521,  1342,  1536,  1438,  1337,  1290,  1423,  1052,  1498,
     866,  1231,  1350,  1270,   772,  1343,  1527,   775,     0,  1352,
       0,     0,  1292,     0,  1422,     0,  1458,     0,     0,     0,
    1222,     0,     0,     0,     0,     0,  1424,     0,  1223,  1283,
       0,     0,  1459,     0,  1344,     0,  1236,  1284,  1224,  1237,
       0,     0,     0,  1423,  1458,  1460,     0,  1285,     0,     0,
       0,     0,     0,     0,  1225,     0,     0,  1226,  1227,     0,
    1459,  1238,     0,  1286,  1239,     0,  1287,  1288,  1512,     0,
       0,  1240,  1424,  1460,  1461,     0,  1241,  1258,     0,     0,
       0,     0,  1242,     0,     0,     0,     0,  1244,     0,  1245,
       0,     0,  1246,     0,  1247,     0,     0,  1515,     0,  1512,
    1248,  1259,  1461,     0,     0,     0,  1249,     0,     0,     0,
       0,  1250,     0,  1232,     0,     0,  1233,     0,  1234,  1235,
       0,  1243,     0,  1251,  1252,     0,  1516,     0,  1515,  1253,
       0,  1262,     0,     0,  1263,  1264,     0,  1260,     0,     0,
       0,  1261,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,     0,  1516,     0,     0,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,     0,     0,   131,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   133,   134,   135,
       0,     0,     0,     0,     0,   255,     0,   256,     0,     0,
       0,     0,     0,   137,   138,   257,   258,   259,   260,   261,
     139,   140,   141,     0,     0,     0,     0,     0,     0,   262,
     263,   264,     0,     0,     0,     0,   265,     0,   147,     0,
       0,     0,     0,     0,     0,     0,   266,     0,     0,     0,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,     0,     0,     0,     0,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,     0,   131,   395,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   133,   134,   135,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   157,
     158,   137,   138,     0,   258,   259,     0,   261,   139,   140,
     141,     0,     0,     0,     0,     0,     0,   262,   263,   264,
       0,     0,     0,     0,   265,     0,     0,     0,     0,   164,
       0,     0,     0,     0,   266,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   157,   158,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   164
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   817,    75,   815,    79,    73,    73,   817,    79,    73,
     817,   782,   809,    78,    79,  1113,  1113,  1113,  1113,  1113,
      72,    73,    74,    75,    76,    24,    78,    79,    73,    81,
     144,     7,   226,   682,    73,    74,    75,    76,     5,     0,
       7,     7,     9,   115,   116,  1499,  1499,   241,    73,    72,
      73,    74,    75,    76,    88,    78,    79,   241,    81,     7,
     150,   151,    16,    17,    18,    19,    20,    73,     3,   207,
     208,   209,   210,     8,     3,    73,  1530,  1530,    86,     8,
       7,   115,   116,    73,    74,    73,    73,    74,    24,    88,
       7,    90,    91,    29,     3,     7,    95,    96,    97,     8,
     241,    73,     3,     7,    73,    73,   244,     8,    73,    74,
      10,    73,    74,   762,    13,    14,   115,   116,    73,    74,
     192,   193,   194,    73,    74,    74,    75,   241,     3,    73,
      74,    24,     6,     8,    73,    74,    73,    74,     3,    73,
      74,    73,    74,     8,     7,    25,    26,    73,    74,    74,
      75,   241,     3,    73,    74,     7,   190,     8,    73,    74,
      73,   115,   116,    73,     7,    73,    73,     3,    73,   241,
      73,    73,     8,     7,   144,   145,    73,   147,    73,   115,
     116,    73,    73,     3,     3,    74,    75,     6,     8,    74,
      75,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,     7,   241,     7,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,     3,   115,   116,   204,   205,     8,   163,   164,   165,
     166,     3,    44,    45,    46,   115,   116,     4,     3,     8,
     218,     6,   241,   221,   222,   223,   224,   153,   154,   155,
     156,   157,   158,     3,     3,    88,     6,    72,    73,    74,
      75,    76,    77,    78,     3,    80,    81,    82,    83,     8,
       3,     8,    87,     6,   241,   242,   243,   244,  1376,  1376,
    1376,  1376,  1376,     3,     3,     3,   101,   241,     8,     8,
     183,   184,   185,   108,     4,     3,     8,     3,     6,    88,
     115,   116,     8,   115,   116,   241,   186,   187,     4,    54,
      55,    56,    57,    58,    59,     3,   131,   132,   133,     4,
       8,     4,  1119,   138,   139,     4,   115,   116,     4,     3,
    1101,     3,     3,     3,     8,  1147,     8,     8,     8,   115,
     116,     3,    87,    88,     3,  1161,     8,  1163,   241,     8,
       3,  1161,     3,  1163,  1161,     8,  1163,     8,    87,     4,
       3,   241,   174,   115,   116,     8,   178,   179,   180,   181,
     115,   116,   150,   151,     3,     3,   188,   189,    87,     8,
       8,   110,   111,   112,   113,   114,   115,   116,     4,   134,
     135,   136,   137,   169,   170,   171,   211,   212,   129,   130,
       3,     8,   131,   132,   133,     8,   115,   116,   241,   138,
     139,     4,     4,    88,    89,    90,    91,    92,    93,    94,
       3,     3,   131,     8,     4,     8,   241,     4,   217,   241,
     219,   220,   141,   142,   143,   144,   145,   146,   147,     4,
     115,   116,     4,     4,   196,   197,   198,   199,   200,   201,
     202,   203,   241,     3,   474,   475,   131,     3,     8,   723,
     724,   725,     8,     4,     3,   241,    47,    48,    49,    50,
      51,    52,     4,   554,   738,   739,   740,   741,     4,     3,
     561,     3,     3,     3,     8,     4,     8,     8,     8,   241,
     102,   103,   104,   105,   575,   759,   241,     4,   579,    39,
      40,    41,   160,   161,   162,   586,     4,   575,   575,   561,
       4,   575,   241,   586,     4,     4,   597,     4,   175,   176,
     177,     4,     4,   575,     4,     4,   607,   579,     4,     4,
     575,     4,   241,   614,   586,     4,   575,     4,   561,   614,
     579,     4,   607,   614,     4,   597,   627,   586,     4,   614,
     575,     4,   575,     4,     4,   607,   579,     4,   597,     4,
       4,     4,   614,   586,     4,     4,   241,     4,     4,   575,
       4,     4,     4,     4,   597,   627,     4,   575,     4,     4,
       4,     4,     4,     4,   607,   575,     4,   575,   575,   579,
       4,   614,   579,     4,     4,   242,   242,     4,   242,     4,
     242,   242,   242,   575,   627,   242,   575,   575,   242,   244,
     575,   243,   243,   575,   579,     4,   243,   579,   242,   242,
     575,   243,   242,   242,   579,   575,   244,   244,     4,   579,
     579,   575,     4,   244,   244,   579,   575,   586,   575,   244,
     579,   575,   579,   575,   243,   579,   242,   579,   242,   575,
       4,   242,     4,   579,   579,   575,   244,     4,   242,   579,
     575,   586,   575,     4,   579,   575,     4,   575,   575,     4,
     575,     4,   575,   575,     4,   244,   244,   244,   575,     4,
     575,     4,     4,   575,   575,     4,     4,     4,     4,     4,
     579,     4,     4,   242,   579,     4,   777,   586,     4,   780,
       4,   586,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,     4,     4,     4,     4,
       4,   244,     4,     4,     4,     4,   244,   244,   780,   244,
     244,   242,   242,     4,   815,   816,   817,     4,   242,   820,
       4,   244,     4,   824,     4,     4,     4,     4,     4,   242,
     242,     4,     4,     4,   242,     4,   776,   780,   242,     4,
       4,     4,     3,   815,   816,   817,     4,   819,   820,    11,
      12,     4,     4,    15,     4,     4,   242,     4,     4,    21,
      22,    23,   244,     4,     4,   244,   244,   244,     4,     4,
     244,     4,   815,   816,   817,     4,   819,   820,     4,     4,
     242,   242,     4,     4,   242,     5,   206,   242,     7,     7,
       7,   241,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,     7,     7,   241,   241,
     241,     5,     5,     5,   241,   241,    98,    99,   100,   101,
       5,     7,   241,     5,   106,     5,     5,   241,     5,     7,
       5,     5,     5,   115,   116,     7,     7,     7,     7,     7,
     122,   123,   124,   125,   126,   127,   128,     7,   241,   131,
       5,     7,     5,     5,     5,   241,   241,   241,   140,   241,
       7,   241,   241,     5,   241,   241,     7,   149,     7,   241,
     152,     7,   241,   241,   241,   241,     7,   159,     7,     7,
     241,   241,     7,     7,     7,   167,   168,   241,     7,     7,
     172,   173,     7,   241,   241,     4,   241,   141,   241,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   191,
       4,     6,     3,   195,     6,     3,     6,     6,     3,     6,
       3,   244,     6,     3,     6,     6,     3,     6,     4,   211,
     212,   213,   214,   215,   216,     4,     4,     4,     4,     4,
       4,     4,     4,   225,     4,     4,     4,     4,     4,     3,
     244,     4,     4,     4,   241,     3,     6,     6,     3,   241,
       6,     8,     4,     4,     4,     4,   242,   242,   242,     4,
       4,   242,     4,     4,   242,     4,     4,   242,   242,   242,
       4,     4,   244,  1104,   242,   242,  1107,     4,   242,  1110,
     242,   242,  1113,     4,   242,  1110,  1104,  1104,     4,  1110,
    1104,   244,  1107,     4,  1125,  1110,  1113,  1128,  1113,  1113,
    1131,   242,  1104,   242,   242,  1107,   242,   242,  1110,  1104,
    1125,  1113,   242,     4,   242,  1104,  1147,     4,  1113,   244,
       4,  1152,   244,  1125,  1113,     4,  1128,   242,     4,  1104,
    1161,  1104,  1163,     6,  1107,   244,  1125,  1110,  1113,  1128,
    1113,     3,  1173,   241,   241,  1147,  1177,   241,  1104,     8,
    1152,  1182,  1125,     8,  1185,  1128,  1104,  1113,  1173,  1161,
       4,  1163,  1185,     4,  1104,  1113,  1104,  1104,  1170,  1125,
     241,  1173,   241,  1113,  1147,  1113,  1113,  1125,     8,  1152,
    1182,   241,  1104,  1185,     3,  1104,  1104,  1125,  1161,  1104,
    1163,  1113,  1104,  1182,  1113,  1113,  1185,  1170,  1113,  1104,
    1173,  1113,     8,  1125,  1104,   241,  1125,  1125,  1113,  1182,
    1104,   241,  1185,  1113,  1113,  1104,     7,  1104,   241,  1113,
    1104,   241,  1104,   241,  1113,   241,  1113,     5,  1104,  1113,
       4,  1113,     4,     4,  1104,     4,     4,  1113,  1113,  1104,
       7,  1104,  1182,  1113,  1104,  1182,  1104,  1104,  1113,  1104,
    1113,  1104,  1104,  1113,   242,  1113,  1113,  1104,  1113,  1104,
    1113,  1113,  1104,  1104,   244,     6,  1113,  1182,  1113,     3,
    1182,  1113,  1113,   244,  1113,     5,   241,  1182,  1113,     4,
       4,     4,  1182,  1182,     4,     7,  1185,   241,  1182,   182,
       5,     7,     4,  1182,   241,  1182,     6,     3,  1182,     4,
    1182,   241,     4,     4,   241,   241,  1182,  1182,     4,   241,
    1185,   241,  1182,   241,     4,   244,   242,  1182,   242,   241,
       4,   241,     4,   241,   241,   808,   762,   777,   554,   780,
    1103,  1098,  1210,   561,   863,  1123,  1116,  1119,  1152,  1133,
    1131,  1140,  1106,  1182,  1104,  1376,  1185,  1182,   575,  1115,
    1185,    77,  1376,  1109,  1385,  1107,   617,   607,  1112,  1376,
    1110,  1376,  1376,   614,  1184,  1182,  1336,   586,  1399,  1187,
    1385,  1130,   597,  1185,  1376,  1128,  1407,   836,  1126,   579,
    1385,  1376,  1163,  1385,  1147,  1161,  1165,  1376,  1449,  1475,
    1445,  1501,  1407,  1530,  1407,  1170,  1385,  1399,   820,  1478,
     779,  1376,  1174,  1376,   627,  1407,  1508,   631,    -1,  1177,
      -1,    -1,  1385,    -1,  1445,    -1,  1447,    -1,    -1,    -1,
    1376,    -1,    -1,    -1,    -1,    -1,  1399,    -1,  1376,  1385,
      -1,    -1,  1447,    -1,  1407,    -1,  1376,  1385,  1376,  1376,
      -1,    -1,    -1,  1445,  1475,  1447,    -1,  1385,    -1,    -1,
      -1,    -1,    -1,    -1,  1376,    -1,    -1,  1376,  1376,    -1,
    1475,  1376,    -1,  1385,  1376,    -1,  1385,  1385,  1499,    -1,
      -1,  1376,  1445,  1475,  1447,    -1,  1376,  1376,    -1,    -1,
      -1,    -1,  1376,    -1,    -1,    -1,    -1,  1376,    -1,  1376,
      -1,    -1,  1376,    -1,  1376,    -1,    -1,  1499,    -1,  1530,
    1376,  1376,  1475,    -1,    -1,    -1,  1376,    -1,    -1,    -1,
      -1,  1376,    -1,  1376,    -1,    -1,  1376,    -1,  1376,  1376,
      -1,  1376,    -1,  1376,  1376,    -1,  1499,    -1,  1530,  1376,
      -1,  1376,    -1,    -1,  1376,  1376,    -1,  1376,    -1,    -1,
      -1,  1376,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    -1,  1530,    -1,    -1,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    -1,    -1,    87,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    99,   100,   101,
      -1,    -1,    -1,    -1,    -1,   107,    -1,   109,    -1,    -1,
      -1,    -1,    -1,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,    -1,    -1,    -1,    -1,    -1,    -1,   131,
     132,   133,    -1,    -1,    -1,    -1,   138,    -1,   140,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   148,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    -1,    -1,    -1,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    -1,    87,    88,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    99,   100,   101,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   211,
     212,   115,   116,    -1,   118,   119,    -1,   121,   122,   123,
     124,    -1,    -1,    -1,    -1,    -1,    -1,   131,   132,   133,
      -1,    -1,    -1,    -1,   138,    -1,    -1,    -1,    -1,   241,
      -1,    -1,    -1,    -1,   148,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   211,   212,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   241
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
       0,     5,     7,     9,   241,   242,   243,   244,   261,   262,
     263,   268,     7,   277,     7,   282,     7,   341,     7,   457,
       7,   541,     7,   558,     7,   575,     7,   490,     7,   496,
       7,   520,     7,   433,     7,   691,     7,   710,   269,   264,
     278,   283,   342,   458,   542,   559,   576,   491,   497,   521,
     434,   692,   711,   261,   270,   271,   241,   266,   267,    10,
     279,   281,    11,    12,    15,    21,    22,    23,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    98,    99,   100,   101,   106,   115,   116,   122,
     123,   124,   125,   126,   127,   128,   131,   140,   149,   152,
     159,   167,   168,   172,   173,   191,   195,   211,   212,   213,
     214,   215,   216,   225,   241,   276,   284,   285,   286,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   309,   311,
     313,   314,   315,   318,   319,   320,   321,   322,   324,   326,
     327,   328,   329,   331,   332,   334,   336,   337,   338,   339,
     351,   353,   355,   398,   406,   412,   418,   420,   427,   441,
     451,   475,   476,   477,   480,   488,   514,   548,   550,   569,
     599,   614,   626,   627,   629,   679,   689,   708,   717,   741,
      16,    17,    18,    19,    20,   276,   343,   344,   345,   347,
     348,   349,   350,   548,   550,   107,   109,   117,   118,   119,
     120,   121,   131,   132,   133,   138,   148,   276,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   303,   304,   305,   306,   309,   311,   313,   314,
     315,   318,   319,   320,   321,   322,   324,   326,   332,   334,
     459,   460,   461,   463,   465,   467,   469,   471,   473,   475,
     476,   477,   478,   479,   514,   535,   548,   550,   552,   569,
     596,   108,   139,   276,   303,   304,   305,   306,   309,   311,
     313,   315,   318,   319,   320,   321,   322,   324,   467,   469,
     471,   473,   514,   543,   544,   545,   547,   548,   550,   110,
     111,   112,   113,   114,   276,   467,   469,   471,   473,   514,
     547,   548,   550,   560,   561,   562,   564,   565,   567,   568,
     131,   141,   142,   143,   144,   145,   146,   147,   276,   514,
     548,   550,   577,   578,   579,   580,   582,   584,   586,   588,
     590,   592,   594,   488,    24,    88,    90,    91,    95,    96,
      97,   276,   372,   498,   499,   500,   501,   502,   503,   504,
     506,   508,   510,   511,   513,   548,   550,    89,    92,    93,
      94,   131,   276,   372,   502,   508,   522,   523,   524,   525,
     526,   528,   529,   530,   531,   532,   533,   548,   550,   150,
     151,   276,   435,   436,   437,   439,   196,   197,   198,   199,
     200,   201,   202,   203,   276,   548,   550,   693,   694,   695,
     696,   698,   699,   701,   702,   703,   706,    13,    14,   712,
     713,   714,   716,     6,     3,     4,     8,     3,   280,     3,
       8,   287,   709,   340,   352,   354,   356,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   330,     4,     4,     4,     4,     4,   307,   310,
     312,     4,     4,     4,     4,     4,     4,     4,   452,   489,
     515,     4,   333,   335,   316,   481,   549,   551,     4,     4,
       4,   407,   419,   413,   399,   600,   570,   428,   442,   615,
       4,   421,   628,   630,   680,   690,   323,   325,     4,     4,
       4,   718,   742,     4,     3,     8,   346,     4,     4,     4,
       4,     3,     8,   536,   553,   462,   464,   466,     4,     4,
     470,   472,   474,   468,   597,     3,     8,   546,     4,     3,
       8,   563,     4,   566,     4,     4,     3,     8,   595,   581,
     583,   585,   587,   589,   591,   593,     8,     3,     8,   505,
     373,     4,   509,   507,   512,     4,     8,     3,   527,     4,
       4,     4,   534,     8,     3,   438,   440,     3,     8,     4,
     697,     4,   700,     4,     4,   704,   707,     3,     8,   715,
       4,     3,     8,   261,   261,   241,     4,     4,     4,     4,
       4,     4,     4,   242,   242,   242,   242,   242,   242,   242,
     242,   244,   243,   243,   243,   242,   243,   242,     4,   242,
     242,   244,   244,   244,     4,     4,     4,   244,   244,   243,
     242,   242,   242,   244,     4,     4,     4,   242,     4,     4,
       4,     4,     4,     4,   244,   244,   244,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   242,     4,     4,     4,
       4,     4,     4,     4,   244,   244,   244,     4,     4,   285,
       4,   244,   244,   242,   242,   344,     4,     4,     4,     4,
       4,   242,   244,     4,     4,     4,     4,     4,   460,     4,
     242,   544,     4,   242,     4,   242,   242,   561,     4,     4,
       4,     4,     4,     4,     4,     4,   579,     4,     4,   242,
       4,     4,     4,   244,   500,     4,   244,   244,   244,     4,
     524,     4,     4,   436,   244,     4,   242,     4,   242,   242,
       4,     4,   694,     4,   242,   713,     4,     7,   241,     7,
       7,     7,     7,     5,   241,   207,   208,   209,   210,   244,
     308,   241,   241,     5,     5,     5,   241,   241,   102,   103,
     104,   105,   317,     5,   263,   265,   241,     5,     5,     5,
       7,     5,     5,     5,     7,     7,     7,     7,     5,     7,
       7,   241,   241,     5,     7,     5,   272,     5,     5,   241,
     241,   241,   272,   272,   272,   241,     7,   241,   241,   241,
     272,   272,   272,   272,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   241,   272,   241,   265,   241,   241,   204,
     205,   705,   206,     5,   261,   284,   712,   343,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,   276,   361,   362,   363,   365,
     367,   369,   371,   372,   374,   375,   376,   377,   378,   379,
     380,   381,   382,   385,   386,   387,   388,   390,   392,   394,
     396,   361,     7,   357,   358,   359,     7,   453,   454,   455,
       7,   492,   493,   494,     7,   516,   517,   518,     7,   482,
     483,   484,   144,   241,   408,   409,   410,   411,   270,   145,
     147,   410,   414,   415,   416,   417,   129,   130,   400,   401,
     402,   404,     7,   601,   602,     7,   571,   572,   573,     7,
     429,   430,   431,   153,   154,   155,   156,   157,   158,   443,
     444,   445,   446,   447,   448,   449,   450,    24,   163,   164,
     165,   166,   276,   374,   548,   550,   616,   617,   618,   621,
     622,   624,   625,   169,   170,   171,   276,   422,   423,   424,
     425,   426,   548,   550,   174,   178,   179,   180,   181,   188,
     189,   276,   388,   390,   392,   548,   550,   635,   636,   637,
     640,   642,   644,   645,   646,   656,     7,   631,   632,   633,
     192,   193,   194,   241,   548,   550,   681,   682,   683,   684,
     686,   687,   693,     7,   719,   720,   226,   276,   743,   744,
     745,   273,     7,   537,   538,   539,     7,   554,   555,   556,
     580,   598,   357,     8,     8,     8,   364,   366,   368,   370,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     383,     4,     4,   389,   391,   393,   395,   397,     3,     8,
       8,   360,     6,     3,   456,     6,     3,   495,     6,     3,
     519,     6,     3,   485,     6,     3,     3,     6,     6,     3,
       6,   403,   405,     3,     8,   603,     3,     6,   574,     6,
       3,   432,     6,     3,     4,     4,     4,     4,     4,     4,
       3,     8,   619,   623,     4,     4,     4,     3,     8,     4,
       4,     4,     3,     8,   638,   641,   643,     4,   657,     4,
     647,     3,     8,   634,     6,     3,     4,   685,     4,   688,
       3,     8,     8,   721,     3,     6,     4,     3,     8,   241,
     274,   275,   540,     6,     3,   557,     6,     3,     8,     6,
       4,     4,     4,     4,   242,   244,   242,   244,   242,   242,
     242,   242,   242,   242,     4,   244,   242,     4,     4,     4,
       4,     4,   362,   361,   359,   459,   455,   498,   494,   522,
     518,   276,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   303,   304,   305,   306,
     309,   311,   313,   314,   315,   318,   319,   320,   321,   322,
     324,   326,   332,   334,   372,   451,   463,   465,   467,   469,
     471,   473,   475,   476,   477,   479,   486,   487,   514,   548,
     550,   596,   484,   409,   415,     4,     4,   401,   134,   135,
     136,   137,   276,   288,   289,   290,   291,   292,   293,   372,
     514,   548,   550,   604,   605,   606,   607,   608,   610,   612,
     613,   602,   577,   573,   435,   431,   242,   242,   242,   242,
     242,   242,   444,     4,     4,   242,   242,   242,   617,   244,
     242,   242,   423,     4,     4,     4,   242,     4,   244,     4,
     636,   635,   633,   244,     4,   242,     4,   682,   217,   219,
     220,   276,   372,   548,   550,   722,   723,   724,   725,   727,
     720,   244,   744,     6,     3,   543,   539,   560,   556,   241,
     241,   241,   241,    39,    40,    41,   384,   241,   241,   241,
     394,   241,     8,     8,     8,     8,     3,     8,   241,   241,
     609,   611,     4,     4,     8,     3,     8,     8,   160,   161,
     162,   620,   241,   175,   176,   177,   639,   241,   241,     7,
       5,     8,   241,   261,   728,     4,   726,     3,     8,   241,
       8,     8,   487,     4,     4,   244,   244,   606,    24,   183,
     184,   185,   276,   548,   550,   658,   659,   660,   663,   665,
     667,     7,   648,   649,   650,     4,   242,     4,   723,   241,
     241,   661,   664,   666,   668,     3,     8,   651,     6,     3,
       5,   241,     4,     4,     4,     4,   659,   190,   276,   372,
     548,   550,   652,   653,   654,   650,     7,   729,   730,   182,
     662,   241,   241,     5,   655,     3,     8,   731,     3,     6,
       7,   669,   670,   671,     4,   653,   218,   221,   222,   223,
     224,   732,   733,   734,   736,   737,   738,   739,   730,   672,
       6,     3,   241,   735,     4,     4,     4,   740,     3,     8,
     186,   187,   276,   365,   367,   548,   550,   673,   674,   675,
     677,   671,     4,   244,   242,   242,     4,   733,   676,   678,
       3,     8,   241,   241,     4,     4,   674,   241,   241
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   245,   247,   246,   248,   246,   249,   246,   250,   246,
     251,   246,   252,   246,   253,   246,   254,   246,   255,   246,
     256,   246,   257,   246,   258,   246,   259,   246,   260,   246,
     261,   261,   261,   261,   261,   261,   261,   262,   264,   263,
     265,   266,   266,   267,   267,   267,   269,   268,   270,   270,
     271,   271,   271,   273,   272,   274,   274,   275,   275,   275,
     276,   278,   277,   280,   279,   279,   281,   283,   282,   284,
     284,   284,   285,   285,   285,   285,   285,   285,   285,   285,
     285,   285,   285,   285,   285,   285,   285,   285,   285,   285,
     285,   285,   285,   285,   285,   285,   285,   285,   285,   285,
     285,   285,   285,   285,   285,   285,   285,   285,   285,   285,
     285,   285,   285,   285,   285,   285,   285,   285,   285,   285,
     285,   285,   285,   285,   285,   285,   285,   285,   285,   285,
     285,   285,   285,   285,   285,   285,   285,   285,   285,   285,
     285,   285,   285,   285,   285,   287,   286,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   307,   306,   308,   308,   308,
     308,   308,   310,   309,   312,   311,   313,   314,   316,   315,
     317,   317,   317,   317,   318,   319,   320,   321,   323,   322,
     325,   324,   326,   327,   328,   330,   329,   331,   333,   332,
     335,   334,   336,   337,   338,   340,   339,   342,   341,   343,
     343,   343,   344,   344,   344,   344,   344,   344,   344,   344,
     346,   345,   347,   348,   349,   350,   352,   351,   354,   353,
     356,   355,   357,   357,   358,   358,   358,   360,   359,   361,
     361,   361,   362,   362,   362,   362,   362,   362,   362,   362,
     362,   362,   362,   362,   362,   362,   362,   362,   362,   362,
     362,   362,   362,   362,   362,   362,   364,   363,   366,   365,
     368,   367,   370,   369,   371,   373,   372,   374,   375,   376,
     377,   378,   379,   380,   381,   383,   382,   384,   384,   384,
     385,   386,   387,   389,   388,   391,   390,   393,   392,   395,
     394,   394,   394,   394,   394,   394,   397,   396,   399,   398,
     400,   400,   400,   401,   401,   403,   402,   405,   404,   407,
     406,   408,   408,   408,   409,   409,   410,   411,   413,   412,
     414,   414,   414,   415,   415,   415,   416,   417,   419,   418,
     421,   420,   422,   422,   422,   423,   423,   423,   423,   423,
     423,   424,   425,   426,   428,   427,   429,   429,   430,   430,
     430,   432,   431,   434,   433,   435,   435,   435,   435,   436,
     436,   438,   437,   440,   439,   442,   441,   443,   443,   443,
     444,   444,   444,   444,   444,   444,   445,   446,   447,   448,
     449,   450,   452,   451,   453,   453,   454,   454,   454,   456,
     455,   458,   457,   459,   459,   459,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   460,   462,   461,
     464,   463,   466,   465,   468,   467,   470,   469,   472,   471,
     474,   473,   475,   476,   477,   478,   479,   481,   480,   482,
     482,   483,   483,   483,   485,   484,   486,   486,   486,   487,
     487,   487,   487,   487,   487,   487,   487,   487,   487,   487,
     487,   487,   487,   487,   487,   487,   487,   487,   487,   487,
     487,   487,   487,   487,   487,   487,   487,   487,   487,   487,
     487,   487,   487,   487,   487,   487,   487,   487,   487,   487,
     487,   487,   487,   487,   487,   487,   487,   487,   489,   488,
     491,   490,   492,   492,   493,   493,   493,   495,   494,   497,
     496,   498,   498,   499,   499,   499,   500,   500,   500,   500,
     500,   500,   500,   500,   500,   500,   501,   502,   503,   505,
     504,   507,   506,   509,   508,   510,   512,   511,   513,   515,
     514,   516,   516,   517,   517,   517,   519,   518,   521,   520,
     522,   522,   523,   523,   523,   524,   524,   524,   524,   524,
     524,   524,   524,   524,   524,   524,   525,   527,   526,   528,
     529,   530,   531,   532,   534,   533,   536,   535,   537,   537,
     538,   538,   538,   540,   539,   542,   541,   543,   543,   543,
     544,   544,   544,   544,   544,   544,   544,   544,   544,   544,
     544,   544,   544,   544,   544,   544,   544,   544,   544,   544,
     544,   544,   544,   544,   546,   545,   547,   549,   548,   551,
     550,   553,   552,   554,   554,   555,   555,   555,   557,   556,
     559,   558,   560,   560,   560,   561,   561,   561,   561,   561,
     561,   561,   561,   561,   561,   561,   561,   561,   561,   563,
     562,   564,   566,   565,   567,   568,   570,   569,   571,   571,
     572,   572,   572,   574,   573,   576,   575,   577,   577,   578,
     578,   578,   579,   579,   579,   579,   579,   579,   579,   579,
     579,   579,   579,   579,   581,   580,   583,   582,   585,   584,
     587,   586,   589,   588,   591,   590,   593,   592,   595,   594,
     597,   596,   598,   600,   599,   601,   601,   601,   603,   602,
     604,   604,   605,   605,   605,   606,   606,   606,   606,   606,
     606,   606,   606,   606,   606,   606,   606,   606,   606,   606,
     607,   609,   608,   611,   610,   612,   613,   615,   614,   616,
     616,   616,   617,   617,   617,   617,   617,   617,   617,   617,
     617,   619,   618,   620,   620,   620,   621,   623,   622,   624,
     625,   626,   628,   627,   630,   629,   631,   631,   632,   632,
     632,   634,   633,   635,   635,   635,   636,   636,   636,   636,
     636,   636,   636,   636,   636,   636,   636,   636,   636,   638,
     637,   639,   639,   639,   641,   640,   643,   642,   644,   645,
     647,   646,   648,   648,   649,   649,   649,   651,   650,   652,
     652,   652,   653,   653,   653,   653,   653,   655,   654,   657,
     656,   658,   658,   658,   659,   659,   659,   659,   659,   659,
     659,   661,   660,   662,   664,   663,   666,   665,   668,   667,
     669,   669,   670,   670,   670,   672,   671,   673,   673,   673,
     674,   674,   674,   674,   674,   674,   674,   676,   675,   678,
     677,   680,   679,   681,   681,   681,   682,   682,   682,   682,
     682,   682,   683,   685,   684,   686,   688,   687,   690,   689,
     692,   691,   693,   693,   693,   694,   694,   694,   694,   694,
     694,   694,   694,   694,   694,   694,   695,   697,   696,   698,
     700,   699,   701,   702,   704,   703,   705,   705,   707,   706,
     709,   708,   711,   710,   712,   712,   712,   713,   713,   715,
     714,   716,   718,   717,   719,   719,   719,   721,   720,   722,
     722,   722,   723,   723,   723,   723,   723,   723,   723,   724,
     726,   725,   728,   727,   729,   729,   729,   731,   730,   732,
     732,   732,   733,   733,   733,   733,   733,   735,   734,   736,
     737,   738,   740,   739,   742,   741,   743,   743,   743,   744,
     744,   745
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
       1,     1,     1,     1,     1,     0,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     3,     3,     0,     4,
       1,     1,     1,     1,     3,     3,     3,     3,     0,     4,
       0,     4,     3,     3,     3,     0,     4,     3,     0,     4,
       0,     4,     3,     3,     3,     0,     6,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     3,     3,     3,     0,     6,     0,     6,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     1,     1,     1,
       3,     3,     3,     0,     4,     0,     4,     0,     4,     0,
       4,     1,     1,     1,     1,     1,     0,     4,     0,     6,
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
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     3,     3,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     3,     3,     3,     0,     4,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     4,     0,
       4,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     4,     3,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     0,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     1,     0,     6,     1,     3,     2,     0,     4,
       0,     1,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     3,     3,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     3,     0,     4,     3,
       3,     3,     0,     6,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     0,     4,     0,     4,     3,     3,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     0,     4,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     3,     0,     4,     0,     6,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     3,
       0,     4,     3,     3,     0,     4,     1,     1,     0,     4,
       0,     6,     0,     4,     1,     3,     2,     1,     1,     0,
       6,     3,     0,     6,     1,     3,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     6,     1,     3,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     3,     0,     4,     0,     6,     1,     3,     2,     1,
       1,     3
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
  "adaptive_lease_time_threshold", "decline_probation_period",
  "ddns_send_updates", "ddns_override_no_update",
  "ddns_override_client_update", "ddns_replace_client_name", "$@22",
  "ddns_replace_client_name_value", "ddns_generated_prefix", "$@23",
  "ddns_qualifying_suffix", "$@24", "ddns_update_on_renew",
  "ddns_use_conflict_resolution", "ddns_conflict_resolution_mode", "$@25",
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
  "ssl_mode", "$@47", "cipher_list", "$@48", "sanity_checks", "$@49",
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
       0,   340,   340,   340,   341,   341,   342,   342,   343,   343,
     344,   344,   345,   345,   346,   346,   347,   347,   348,   348,
     349,   349,   350,   350,   351,   351,   352,   352,   353,   353,
     361,   362,   363,   364,   365,   366,   367,   370,   375,   375,
     386,   389,   390,   393,   398,   404,   409,   409,   416,   417,
     420,   424,   428,   434,   434,   441,   442,   445,   449,   453,
     463,   472,   472,   487,   487,   501,   504,   510,   510,   519,
     520,   521,   528,   529,   530,   531,   532,   533,   534,   535,
     536,   537,   538,   539,   540,   541,   542,   543,   544,   545,
     546,   547,   548,   549,   550,   551,   552,   553,   554,   555,
     556,   557,   558,   559,   560,   561,   562,   563,   564,   565,
     566,   567,   568,   569,   570,   571,   572,   573,   574,   575,
     576,   577,   578,   579,   580,   581,   582,   583,   584,   585,
     586,   587,   588,   589,   590,   591,   592,   593,   594,   595,
     596,   597,   598,   599,   600,   603,   603,   613,   619,   625,
     631,   637,   643,   649,   655,   661,   667,   673,   679,   685,
     691,   697,   703,   709,   715,   721,   721,   730,   733,   736,
     739,   742,   748,   748,   757,   757,   766,   775,   785,   785,
     794,   797,   800,   803,   808,   814,   820,   826,   832,   832,
     841,   841,   850,   856,   862,   868,   868,   877,   883,   883,
     892,   892,   901,   907,   913,   919,   919,   931,   931,   940,
     941,   942,   947,   948,   949,   950,   951,   952,   953,   954,
     957,   957,   968,   974,   980,   986,   992,   992,  1005,  1005,
    1018,  1018,  1029,  1030,  1033,  1034,  1035,  1040,  1040,  1050,
    1051,  1052,  1057,  1058,  1059,  1060,  1061,  1062,  1063,  1064,
    1065,  1066,  1067,  1068,  1069,  1070,  1071,  1072,  1073,  1074,
    1075,  1076,  1077,  1078,  1079,  1080,  1083,  1083,  1092,  1092,
    1101,  1101,  1110,  1110,  1119,  1125,  1125,  1134,  1140,  1146,
    1152,  1158,  1164,  1170,  1176,  1182,  1182,  1190,  1191,  1192,
    1195,  1201,  1207,  1213,  1213,  1222,  1222,  1231,  1231,  1240,
    1240,  1248,  1251,  1254,  1257,  1260,  1265,  1265,  1274,  1274,
    1285,  1286,  1287,  1292,  1293,  1296,  1296,  1315,  1315,  1333,
    1333,  1344,  1345,  1346,  1351,  1352,  1355,  1360,  1365,  1365,
    1376,  1377,  1378,  1383,  1384,  1385,  1388,  1393,  1400,  1400,
    1413,  1413,  1426,  1427,  1428,  1433,  1434,  1435,  1436,  1437,
    1438,  1441,  1447,  1453,  1459,  1459,  1470,  1471,  1474,  1475,
    1476,  1481,  1481,  1491,  1491,  1501,  1502,  1503,  1506,  1509,
    1510,  1513,  1513,  1522,  1522,  1531,  1531,  1543,  1544,  1545,
    1550,  1551,  1552,  1553,  1554,  1555,  1558,  1564,  1570,  1576,
    1582,  1588,  1597,  1597,  1611,  1612,  1615,  1616,  1617,  1626,
    1626,  1652,  1652,  1663,  1664,  1665,  1671,  1672,  1673,  1674,
    1675,  1676,  1677,  1678,  1679,  1680,  1681,  1682,  1683,  1684,
    1685,  1686,  1687,  1688,  1689,  1690,  1691,  1692,  1693,  1694,
    1695,  1696,  1697,  1698,  1699,  1700,  1701,  1702,  1703,  1704,
    1705,  1706,  1707,  1708,  1709,  1710,  1711,  1712,  1713,  1714,
    1715,  1716,  1717,  1718,  1719,  1720,  1721,  1722,  1725,  1725,
    1734,  1734,  1743,  1743,  1752,  1752,  1762,  1762,  1774,  1774,
    1785,  1785,  1796,  1802,  1808,  1814,  1820,  1828,  1828,  1840,
    1841,  1845,  1846,  1847,  1852,  1852,  1860,  1861,  1862,  1867,
    1868,  1869,  1870,  1871,  1872,  1873,  1874,  1875,  1876,  1877,
    1878,  1879,  1880,  1881,  1882,  1883,  1884,  1885,  1886,  1887,
    1888,  1889,  1890,  1891,  1892,  1893,  1894,  1895,  1896,  1897,
    1898,  1899,  1900,  1901,  1902,  1903,  1904,  1905,  1906,  1907,
    1908,  1909,  1910,  1911,  1912,  1913,  1914,  1915,  1922,  1922,
    1936,  1936,  1945,  1946,  1949,  1950,  1951,  1958,  1958,  1973,
    1973,  1987,  1988,  1991,  1992,  1993,  1998,  1999,  2000,  2001,
    2002,  2003,  2004,  2005,  2006,  2007,  2010,  2012,  2018,  2020,
    2020,  2029,  2029,  2038,  2038,  2047,  2049,  2049,  2058,  2068,
    2068,  2081,  2082,  2087,  2088,  2089,  2096,  2096,  2108,  2108,
    2120,  2121,  2126,  2127,  2128,  2135,  2136,  2137,  2138,  2139,
    2140,  2141,  2142,  2143,  2144,  2145,  2148,  2150,  2150,  2159,
    2161,  2163,  2169,  2175,  2181,  2181,  2195,  2195,  2208,  2209,
    2212,  2213,  2214,  2219,  2219,  2229,  2229,  2239,  2240,  2241,
    2246,  2247,  2248,  2249,  2250,  2251,  2252,  2253,  2254,  2255,
    2256,  2257,  2258,  2259,  2260,  2261,  2262,  2263,  2264,  2265,
    2266,  2267,  2268,  2269,  2272,  2272,  2281,  2287,  2287,  2312,
    2312,  2342,  2342,  2355,  2356,  2359,  2360,  2361,  2366,  2366,
    2378,  2378,  2390,  2391,  2392,  2397,  2398,  2399,  2400,  2401,
    2402,  2403,  2404,  2405,  2406,  2407,  2408,  2409,  2410,  2413,
    2413,  2422,  2428,  2428,  2437,  2443,  2452,  2452,  2463,  2464,
    2467,  2468,  2469,  2474,  2474,  2483,  2483,  2492,  2493,  2496,
    2497,  2498,  2504,  2505,  2506,  2507,  2508,  2509,  2510,  2511,
    2512,  2513,  2514,  2515,  2518,  2518,  2529,  2529,  2540,  2540,
    2551,  2551,  2560,  2560,  2569,  2569,  2578,  2578,  2587,  2587,
    2601,  2601,  2612,  2618,  2618,  2629,  2630,  2631,  2636,  2636,
    2646,  2647,  2650,  2651,  2652,  2657,  2658,  2659,  2660,  2661,
    2662,  2663,  2664,  2665,  2666,  2667,  2668,  2669,  2670,  2671,
    2674,  2676,  2676,  2685,  2685,  2695,  2701,  2710,  2710,  2723,
    2724,  2725,  2730,  2731,  2732,  2733,  2734,  2735,  2736,  2737,
    2738,  2741,  2741,  2749,  2750,  2751,  2754,  2760,  2760,  2769,
    2775,  2783,  2791,  2791,  2803,  2803,  2815,  2816,  2819,  2820,
    2821,  2826,  2826,  2834,  2835,  2836,  2841,  2842,  2843,  2844,
    2845,  2846,  2847,  2848,  2849,  2850,  2851,  2852,  2853,  2856,
    2856,  2865,  2866,  2867,  2870,  2870,  2880,  2880,  2890,  2896,
    2902,  2902,  2913,  2914,  2917,  2918,  2919,  2924,  2924,  2932,
    2933,  2934,  2939,  2940,  2941,  2942,  2943,  2946,  2946,  2957,
    2957,  2970,  2971,  2972,  2977,  2978,  2979,  2980,  2981,  2982,
    2983,  2986,  2986,  2994,  2997,  2997,  3006,  3006,  3015,  3015,
    3026,  3027,  3030,  3031,  3032,  3037,  3037,  3045,  3046,  3047,
    3052,  3053,  3054,  3055,  3056,  3057,  3058,  3061,  3061,  3070,
    3070,  3081,  3081,  3094,  3095,  3096,  3101,  3102,  3103,  3104,
    3105,  3106,  3109,  3115,  3115,  3124,  3130,  3130,  3140,  3140,
    3153,  3153,  3163,  3164,  3165,  3170,  3171,  3172,  3173,  3174,
    3175,  3176,  3177,  3178,  3179,  3180,  3183,  3189,  3189,  3198,
    3204,  3204,  3213,  3219,  3225,  3225,  3234,  3235,  3238,  3238,
    3249,  3249,  3261,  3261,  3271,  3272,  3273,  3279,  3280,  3283,
    3283,  3294,  3302,  3302,  3315,  3316,  3317,  3323,  3323,  3331,
    3332,  3333,  3338,  3339,  3340,  3341,  3342,  3343,  3344,  3347,
    3353,  3353,  3362,  3362,  3373,  3374,  3375,  3380,  3380,  3388,
    3389,  3390,  3395,  3396,  3397,  3398,  3399,  3402,  3402,  3411,
    3417,  3423,  3429,  3429,  3438,  3438,  3449,  3450,  3451,  3456,
    3457,  3460
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
#line 7195 "dhcp6_parser.cc"

#line 3466 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
