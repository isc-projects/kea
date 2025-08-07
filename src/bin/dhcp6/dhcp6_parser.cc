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

  case 144: // $@21: %empty
#line 602 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1152 "dhcp6_parser.cc"
    break;

  case 145: // data_directory: "data-directory" $@21 ":" "constant string"
#line 605 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.warning(yystack_[2].location, "data-directory is deprecated and will be ignored");
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1163 "dhcp6_parser.cc"
    break;

  case 146: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 612 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1173 "dhcp6_parser.cc"
    break;

  case 147: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 618 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1183 "dhcp6_parser.cc"
    break;

  case 148: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 624 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1193 "dhcp6_parser.cc"
    break;

  case 149: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 630 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1203 "dhcp6_parser.cc"
    break;

  case 150: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 636 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1213 "dhcp6_parser.cc"
    break;

  case 151: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 642 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1223 "dhcp6_parser.cc"
    break;

  case 152: // renew_timer: "renew-timer" ":" "integer"
#line 648 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1233 "dhcp6_parser.cc"
    break;

  case 153: // rebind_timer: "rebind-timer" ":" "integer"
#line 654 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1243 "dhcp6_parser.cc"
    break;

  case 154: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 660 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1253 "dhcp6_parser.cc"
    break;

  case 155: // t1_percent: "t1-percent" ":" "floating point"
#line 666 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1263 "dhcp6_parser.cc"
    break;

  case 156: // t2_percent: "t2-percent" ":" "floating point"
#line 672 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1273 "dhcp6_parser.cc"
    break;

  case 157: // cache_threshold: "cache-threshold" ":" "floating point"
#line 678 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1283 "dhcp6_parser.cc"
    break;

  case 158: // cache_max_age: "cache-max-age" ":" "integer"
#line 684 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1293 "dhcp6_parser.cc"
    break;

  case 159: // adaptive_lease_time_threshold: "adaptive-lease-time-threshold" ":" "floating point"
#line 690 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("adaptive-lease-time-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr altt(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("adaptive-lease-time-threshold", altt);
}
#line 1303 "dhcp6_parser.cc"
    break;

  case 160: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 696 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1313 "dhcp6_parser.cc"
    break;

  case 161: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 702 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1323 "dhcp6_parser.cc"
    break;

  case 162: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 708 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1333 "dhcp6_parser.cc"
    break;

  case 163: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 714 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1343 "dhcp6_parser.cc"
    break;

  case 164: // $@22: %empty
#line 720 "dhcp6_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1352 "dhcp6_parser.cc"
    break;

  case 165: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 723 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1361 "dhcp6_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "when-present"
#line 729 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1369 "dhcp6_parser.cc"
    break;

  case 167: // ddns_replace_client_name_value: "never"
#line 732 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1377 "dhcp6_parser.cc"
    break;

  case 168: // ddns_replace_client_name_value: "always"
#line 735 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1385 "dhcp6_parser.cc"
    break;

  case 169: // ddns_replace_client_name_value: "when-not-present"
#line 738 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1393 "dhcp6_parser.cc"
    break;

  case 170: // ddns_replace_client_name_value: "boolean"
#line 741 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1402 "dhcp6_parser.cc"
    break;

  case 171: // $@23: %empty
#line 747 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1411 "dhcp6_parser.cc"
    break;

  case 172: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 750 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1421 "dhcp6_parser.cc"
    break;

  case 173: // $@24: %empty
#line 756 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1430 "dhcp6_parser.cc"
    break;

  case 174: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 759 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1440 "dhcp6_parser.cc"
    break;

  case 175: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 765 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1450 "dhcp6_parser.cc"
    break;

  case 176: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 774 "dhcp6_parser.yy"
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

  case 177: // $@25: %empty
#line 784 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1473 "dhcp6_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 787 "dhcp6_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1482 "dhcp6_parser.cc"
    break;

  case 179: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 793 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1490 "dhcp6_parser.cc"
    break;

  case 180: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 796 "dhcp6_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1498 "dhcp6_parser.cc"
    break;

  case 181: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 799 "dhcp6_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1506 "dhcp6_parser.cc"
    break;

  case 182: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 802 "dhcp6_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1514 "dhcp6_parser.cc"
    break;

  case 183: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 807 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1524 "dhcp6_parser.cc"
    break;

  case 184: // ddns_ttl: "ddns-ttl" ":" "integer"
#line 813 "dhcp6_parser.yy"
                                 {
    ctx.unique("ddns-ttl", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl", ttl);
}
#line 1534 "dhcp6_parser.cc"
    break;

  case 185: // ddns_ttl_min: "ddns-ttl-min" ":" "integer"
#line 819 "dhcp6_parser.yy"
                                         {
    ctx.unique("ddns-ttl-min", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-min", ttl);
}
#line 1544 "dhcp6_parser.cc"
    break;

  case 186: // ddns_ttl_max: "ddns-ttl-mix" ":" "integer"
#line 825 "dhcp6_parser.yy"
                                         {
    ctx.unique("ddns-ttl-max", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-max", ttl);
}
#line 1554 "dhcp6_parser.cc"
    break;

  case 187: // $@26: %empty
#line 831 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1563 "dhcp6_parser.cc"
    break;

  case 188: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 834 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1573 "dhcp6_parser.cc"
    break;

  case 189: // $@27: %empty
#line 840 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1582 "dhcp6_parser.cc"
    break;

  case 190: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 843 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1592 "dhcp6_parser.cc"
    break;

  case 191: // store_extended_info: "store-extended-info" ":" "boolean"
#line 849 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1602 "dhcp6_parser.cc"
    break;

  case 192: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 855 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1612 "dhcp6_parser.cc"
    break;

  case 193: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 861 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1622 "dhcp6_parser.cc"
    break;

  case 194: // $@28: %empty
#line 867 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1631 "dhcp6_parser.cc"
    break;

  case 195: // server_tag: "server-tag" $@28 ":" "constant string"
#line 870 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1641 "dhcp6_parser.cc"
    break;

  case 196: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 876 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1651 "dhcp6_parser.cc"
    break;

  case 197: // $@29: %empty
#line 882 "dhcp6_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1660 "dhcp6_parser.cc"
    break;

  case 198: // allocator: "allocator" $@29 ":" "constant string"
#line 885 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1670 "dhcp6_parser.cc"
    break;

  case 199: // $@30: %empty
#line 891 "dhcp6_parser.yy"
                           {
    ctx.unique("pd-allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1679 "dhcp6_parser.cc"
    break;

  case 200: // pd_allocator: "pd-allocator" $@30 ":" "constant string"
#line 894 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-allocator", al);
    ctx.leave();
}
#line 1689 "dhcp6_parser.cc"
    break;

  case 201: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 900 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1699 "dhcp6_parser.cc"
    break;

  case 202: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 906 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1709 "dhcp6_parser.cc"
    break;

  case 203: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 912 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1719 "dhcp6_parser.cc"
    break;

  case 204: // $@31: %empty
#line 918 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1731 "dhcp6_parser.cc"
    break;

  case 205: // interfaces_config: "interfaces-config" $@31 ":" "{" interfaces_config_params "}"
#line 924 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1741 "dhcp6_parser.cc"
    break;

  case 206: // $@32: %empty
#line 930 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1751 "dhcp6_parser.cc"
    break;

  case 207: // sub_interfaces6: "{" $@32 interfaces_config_params "}"
#line 934 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1760 "dhcp6_parser.cc"
    break;

  case 210: // interfaces_config_params: interfaces_config_params ","
#line 941 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1768 "dhcp6_parser.cc"
    break;

  case 219: // $@33: %empty
#line 956 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1780 "dhcp6_parser.cc"
    break;

  case 220: // interfaces_list: "interfaces" $@33 ":" list_strings
#line 962 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1789 "dhcp6_parser.cc"
    break;

  case 221: // re_detect: "re-detect" ":" "boolean"
#line 967 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1799 "dhcp6_parser.cc"
    break;

  case 222: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 973 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1809 "dhcp6_parser.cc"
    break;

  case 223: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 979 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1819 "dhcp6_parser.cc"
    break;

  case 224: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 985 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1829 "dhcp6_parser.cc"
    break;

  case 225: // $@34: %empty
#line 991 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1841 "dhcp6_parser.cc"
    break;

  case 226: // lease_database: "lease-database" $@34 ":" "{" database_map_params "}"
#line 997 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1852 "dhcp6_parser.cc"
    break;

  case 227: // $@35: %empty
#line 1004 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1864 "dhcp6_parser.cc"
    break;

  case 228: // hosts_database: "hosts-database" $@35 ":" "{" database_map_params "}"
#line 1010 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1875 "dhcp6_parser.cc"
    break;

  case 229: // $@36: %empty
#line 1017 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1887 "dhcp6_parser.cc"
    break;

  case 230: // hosts_databases: "hosts-databases" $@36 ":" "[" database_list "]"
#line 1023 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1896 "dhcp6_parser.cc"
    break;

  case 235: // not_empty_database_list: not_empty_database_list ","
#line 1034 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1904 "dhcp6_parser.cc"
    break;

  case 236: // $@37: %empty
#line 1039 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1914 "dhcp6_parser.cc"
    break;

  case 237: // database: "{" $@37 database_map_params "}"
#line 1043 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1924 "dhcp6_parser.cc"
    break;

  case 240: // database_map_params: database_map_params ","
#line 1051 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1932 "dhcp6_parser.cc"
    break;

  case 265: // $@38: %empty
#line 1082 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1941 "dhcp6_parser.cc"
    break;

  case 266: // database_type: "type" $@38 ":" "constant string"
#line 1085 "dhcp6_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 1951 "dhcp6_parser.cc"
    break;

  case 267: // $@39: %empty
#line 1091 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1960 "dhcp6_parser.cc"
    break;

  case 268: // user: "user" $@39 ":" "constant string"
#line 1094 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1970 "dhcp6_parser.cc"
    break;

  case 269: // $@40: %empty
#line 1100 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1979 "dhcp6_parser.cc"
    break;

  case 270: // password: "password" $@40 ":" "constant string"
#line 1103 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1989 "dhcp6_parser.cc"
    break;

  case 271: // $@41: %empty
#line 1109 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1998 "dhcp6_parser.cc"
    break;

  case 272: // host: "host" $@41 ":" "constant string"
#line 1112 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2008 "dhcp6_parser.cc"
    break;

  case 273: // port: "port" ":" "integer"
#line 1118 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2018 "dhcp6_parser.cc"
    break;

  case 274: // $@42: %empty
#line 1124 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2027 "dhcp6_parser.cc"
    break;

  case 275: // name: "name" $@42 ":" "constant string"
#line 1127 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2037 "dhcp6_parser.cc"
    break;

  case 276: // persist: "persist" ":" "boolean"
#line 1133 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2047 "dhcp6_parser.cc"
    break;

  case 277: // lfc_interval: "lfc-interval" ":" "integer"
#line 1139 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2057 "dhcp6_parser.cc"
    break;

  case 278: // readonly: "readonly" ":" "boolean"
#line 1145 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2067 "dhcp6_parser.cc"
    break;

  case 279: // connect_timeout: "connect-timeout" ":" "integer"
#line 1151 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2077 "dhcp6_parser.cc"
    break;

  case 280: // read_timeout: "read-timeout" ":" "integer"
#line 1157 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2087 "dhcp6_parser.cc"
    break;

  case 281: // write_timeout: "write-timeout" ":" "integer"
#line 1163 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2097 "dhcp6_parser.cc"
    break;

  case 282: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1169 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2107 "dhcp6_parser.cc"
    break;

  case 283: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1175 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2117 "dhcp6_parser.cc"
    break;

  case 284: // $@43: %empty
#line 1181 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2126 "dhcp6_parser.cc"
    break;

  case 285: // on_fail: "on-fail" $@43 ":" on_fail_mode
#line 1184 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2135 "dhcp6_parser.cc"
    break;

  case 286: // on_fail_mode: "stop-retry-exit"
#line 1189 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2141 "dhcp6_parser.cc"
    break;

  case 287: // on_fail_mode: "serve-retry-exit"
#line 1190 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2147 "dhcp6_parser.cc"
    break;

  case 288: // on_fail_mode: "serve-retry-continue"
#line 1191 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2153 "dhcp6_parser.cc"
    break;

  case 289: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1194 "dhcp6_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2163 "dhcp6_parser.cc"
    break;

  case 290: // max_row_errors: "max-row-errors" ":" "integer"
#line 1200 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2173 "dhcp6_parser.cc"
    break;

  case 291: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1206 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2183 "dhcp6_parser.cc"
    break;

  case 292: // $@44: %empty
#line 1212 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2192 "dhcp6_parser.cc"
    break;

  case 293: // trust_anchor: "trust-anchor" $@44 ":" "constant string"
#line 1215 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2202 "dhcp6_parser.cc"
    break;

  case 294: // $@45: %empty
#line 1221 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2211 "dhcp6_parser.cc"
    break;

  case 295: // cert_file: "cert-file" $@45 ":" "constant string"
#line 1224 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2221 "dhcp6_parser.cc"
    break;

  case 296: // $@46: %empty
#line 1230 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2230 "dhcp6_parser.cc"
    break;

  case 297: // key_file: "key-file" $@46 ":" "constant string"
#line 1233 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2240 "dhcp6_parser.cc"
    break;

  case 298: // $@47: %empty
#line 1239 "dhcp6_parser.yy"
                   {
    ctx.unique("ssl-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SSL_MODE);
}
#line 2249 "dhcp6_parser.cc"
    break;

  case 299: // ssl_mode: "ssl-mode" $@47 ":" ssl_mode
#line 1242 "dhcp6_parser.yy"
                 {
    ctx.stack_.back()->set("ssl-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2258 "dhcp6_parser.cc"
    break;

  case 300: // ssl_mode: "disable"
#line 1247 "dhcp6_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disable", ctx.loc2pos(yystack_[0].location)));
            }
#line 2266 "dhcp6_parser.cc"
    break;

  case 301: // ssl_mode: "prefer"
#line 1250 "dhcp6_parser.yy"
                 {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("prefer", ctx.loc2pos(yystack_[0].location)));
            }
#line 2274 "dhcp6_parser.cc"
    break;

  case 302: // ssl_mode: "require"
#line 1253 "dhcp6_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("require", ctx.loc2pos(yystack_[0].location)));
            }
#line 2282 "dhcp6_parser.cc"
    break;

  case 303: // ssl_mode: "verify-ca"
#line 1256 "dhcp6_parser.yy"
                    {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-ca", ctx.loc2pos(yystack_[0].location)));
            }
#line 2290 "dhcp6_parser.cc"
    break;

  case 304: // ssl_mode: "verify-full"
#line 1259 "dhcp6_parser.yy"
                      {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-full", ctx.loc2pos(yystack_[0].location)));
            }
#line 2298 "dhcp6_parser.cc"
    break;

  case 305: // $@48: %empty
#line 1264 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2307 "dhcp6_parser.cc"
    break;

  case 306: // cipher_list: "cipher-list" $@48 ":" "constant string"
#line 1267 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2317 "dhcp6_parser.cc"
    break;

  case 307: // $@49: %empty
#line 1273 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2329 "dhcp6_parser.cc"
    break;

  case 308: // sanity_checks: "sanity-checks" $@49 ":" "{" sanity_checks_params "}"
#line 1279 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2338 "dhcp6_parser.cc"
    break;

  case 311: // sanity_checks_params: sanity_checks_params ","
#line 1286 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2346 "dhcp6_parser.cc"
    break;

  case 314: // $@50: %empty
#line 1295 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2355 "dhcp6_parser.cc"
    break;

  case 315: // lease_checks: "lease-checks" $@50 ":" "constant string"
#line 1298 "dhcp6_parser.yy"
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

  case 316: // $@51: %empty
#line 1314 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2384 "dhcp6_parser.cc"
    break;

  case 317: // extended_info_checks: "extended-info-checks" $@51 ":" "constant string"
#line 1317 "dhcp6_parser.yy"
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

  case 318: // $@52: %empty
#line 1332 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2415 "dhcp6_parser.cc"
    break;

  case 319: // mac_sources: "mac-sources" $@52 ":" "[" mac_sources_list "]"
#line 1338 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2424 "dhcp6_parser.cc"
    break;

  case 322: // mac_sources_list: mac_sources_list ","
#line 1345 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2432 "dhcp6_parser.cc"
    break;

  case 325: // duid_id: "duid"
#line 1354 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2441 "dhcp6_parser.cc"
    break;

  case 326: // string_id: "constant string"
#line 1359 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2450 "dhcp6_parser.cc"
    break;

  case 327: // $@53: %empty
#line 1364 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2462 "dhcp6_parser.cc"
    break;

  case 328: // host_reservation_identifiers: "host-reservation-identifiers" $@53 ":" "[" host_reservation_identifiers_list "]"
#line 1370 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2471 "dhcp6_parser.cc"
    break;

  case 331: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1377 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2479 "dhcp6_parser.cc"
    break;

  case 335: // hw_address_id: "hw-address"
#line 1387 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2488 "dhcp6_parser.cc"
    break;

  case 336: // flex_id: "flex-id"
#line 1392 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2497 "dhcp6_parser.cc"
    break;

  case 337: // $@54: %empty
#line 1399 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2509 "dhcp6_parser.cc"
    break;

  case 338: // relay_supplied_options: "relay-supplied-options" $@54 ":" "[" list_content "]"
#line 1405 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2518 "dhcp6_parser.cc"
    break;

  case 339: // $@55: %empty
#line 1412 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2530 "dhcp6_parser.cc"
    break;

  case 340: // dhcp_multi_threading: "multi-threading" $@55 ":" "{" multi_threading_params "}"
#line 1418 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2541 "dhcp6_parser.cc"
    break;

  case 343: // multi_threading_params: multi_threading_params ","
#line 1427 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2549 "dhcp6_parser.cc"
    break;

  case 350: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1440 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2559 "dhcp6_parser.cc"
    break;

  case 351: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1446 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2569 "dhcp6_parser.cc"
    break;

  case 352: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1452 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2579 "dhcp6_parser.cc"
    break;

  case 353: // $@56: %empty
#line 1458 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2591 "dhcp6_parser.cc"
    break;

  case 354: // hooks_libraries: "hooks-libraries" $@56 ":" "[" hooks_libraries_list "]"
#line 1464 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2600 "dhcp6_parser.cc"
    break;

  case 359: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1475 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2608 "dhcp6_parser.cc"
    break;

  case 360: // $@57: %empty
#line 1480 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2618 "dhcp6_parser.cc"
    break;

  case 361: // hooks_library: "{" $@57 hooks_params "}"
#line 1484 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2628 "dhcp6_parser.cc"
    break;

  case 362: // $@58: %empty
#line 1490 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2638 "dhcp6_parser.cc"
    break;

  case 363: // sub_hooks_library: "{" $@58 hooks_params "}"
#line 1494 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2648 "dhcp6_parser.cc"
    break;

  case 366: // hooks_params: hooks_params ","
#line 1502 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2656 "dhcp6_parser.cc"
    break;

  case 370: // $@59: %empty
#line 1512 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2665 "dhcp6_parser.cc"
    break;

  case 371: // library: "library" $@59 ":" "constant string"
#line 1515 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2675 "dhcp6_parser.cc"
    break;

  case 372: // $@60: %empty
#line 1521 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2684 "dhcp6_parser.cc"
    break;

  case 373: // parameters: "parameters" $@60 ":" map_value
#line 1524 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2693 "dhcp6_parser.cc"
    break;

  case 374: // $@61: %empty
#line 1530 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2705 "dhcp6_parser.cc"
    break;

  case 375: // expired_leases_processing: "expired-leases-processing" $@61 ":" "{" expired_leases_params "}"
#line 1536 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2715 "dhcp6_parser.cc"
    break;

  case 378: // expired_leases_params: expired_leases_params ","
#line 1544 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2723 "dhcp6_parser.cc"
    break;

  case 385: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1557 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2733 "dhcp6_parser.cc"
    break;

  case 386: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1563 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2743 "dhcp6_parser.cc"
    break;

  case 387: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1569 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2753 "dhcp6_parser.cc"
    break;

  case 388: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1575 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2763 "dhcp6_parser.cc"
    break;

  case 389: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1581 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2773 "dhcp6_parser.cc"
    break;

  case 390: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1587 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2783 "dhcp6_parser.cc"
    break;

  case 391: // $@62: %empty
#line 1596 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2795 "dhcp6_parser.cc"
    break;

  case 392: // subnet6_list: "subnet6" $@62 ":" "[" subnet6_list_content "]"
#line 1602 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2804 "dhcp6_parser.cc"
    break;

  case 397: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1616 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2812 "dhcp6_parser.cc"
    break;

  case 398: // $@63: %empty
#line 1625 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2822 "dhcp6_parser.cc"
    break;

  case 399: // subnet6: "{" $@63 subnet6_params "}"
#line 1629 "dhcp6_parser.yy"
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

  case 400: // $@64: %empty
#line 1651 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2858 "dhcp6_parser.cc"
    break;

  case 401: // sub_subnet6: "{" $@64 subnet6_params "}"
#line 1655 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2868 "dhcp6_parser.cc"
    break;

  case 404: // subnet6_params: subnet6_params ","
#line 1664 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2876 "dhcp6_parser.cc"
    break;

  case 457: // $@65: %empty
#line 1724 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2885 "dhcp6_parser.cc"
    break;

  case 458: // subnet: "subnet" $@65 ":" "constant string"
#line 1727 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2895 "dhcp6_parser.cc"
    break;

  case 459: // $@66: %empty
#line 1733 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2904 "dhcp6_parser.cc"
    break;

  case 460: // interface: "interface" $@66 ":" "constant string"
#line 1736 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2914 "dhcp6_parser.cc"
    break;

  case 461: // $@67: %empty
#line 1742 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2923 "dhcp6_parser.cc"
    break;

  case 462: // interface_id: "interface-id" $@67 ":" "constant string"
#line 1745 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2933 "dhcp6_parser.cc"
    break;

  case 463: // $@68: %empty
#line 1751 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2942 "dhcp6_parser.cc"
    break;

  case 464: // client_class: "client-class" $@68 ":" "constant string"
#line 1754 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2952 "dhcp6_parser.cc"
    break;

  case 465: // $@69: %empty
#line 1761 "dhcp6_parser.yy"
                                       {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2964 "dhcp6_parser.cc"
    break;

  case 466: // network_client_classes: "client-classes" $@69 ":" list_strings
#line 1767 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2973 "dhcp6_parser.cc"
    break;

  case 467: // $@70: %empty
#line 1773 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2985 "dhcp6_parser.cc"
    break;

  case 468: // require_client_classes: "require-client-classes" $@70 ":" list_strings
#line 1779 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2994 "dhcp6_parser.cc"
    break;

  case 469: // $@71: %empty
#line 1784 "dhcp6_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3006 "dhcp6_parser.cc"
    break;

  case 470: // evaluate_additional_classes: "evaluate-additional-classes" $@71 ":" list_strings
#line 1790 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3015 "dhcp6_parser.cc"
    break;

  case 471: // reservations_global: "reservations-global" ":" "boolean"
#line 1795 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 3025 "dhcp6_parser.cc"
    break;

  case 472: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1801 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 3035 "dhcp6_parser.cc"
    break;

  case 473: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1807 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 3045 "dhcp6_parser.cc"
    break;

  case 474: // id: "id" ":" "integer"
#line 1813 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 3055 "dhcp6_parser.cc"
    break;

  case 475: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1819 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 3065 "dhcp6_parser.cc"
    break;

  case 476: // $@72: %empty
#line 1827 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3077 "dhcp6_parser.cc"
    break;

  case 477: // shared_networks: "shared-networks" $@72 ":" "[" shared_networks_content "]"
#line 1833 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3086 "dhcp6_parser.cc"
    break;

  case 482: // shared_networks_list: shared_networks_list ","
#line 1846 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3094 "dhcp6_parser.cc"
    break;

  case 483: // $@73: %empty
#line 1851 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3104 "dhcp6_parser.cc"
    break;

  case 484: // shared_network: "{" $@73 shared_network_params "}"
#line 1855 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3112 "dhcp6_parser.cc"
    break;

  case 487: // shared_network_params: shared_network_params ","
#line 1861 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3120 "dhcp6_parser.cc"
    break;

  case 537: // $@74: %empty
#line 1921 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3132 "dhcp6_parser.cc"
    break;

  case 538: // option_def_list: "option-def" $@74 ":" "[" option_def_list_content "]"
#line 1927 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3141 "dhcp6_parser.cc"
    break;

  case 539: // $@75: %empty
#line 1935 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3150 "dhcp6_parser.cc"
    break;

  case 540: // sub_option_def_list: "{" $@75 option_def_list "}"
#line 1938 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 3158 "dhcp6_parser.cc"
    break;

  case 545: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1950 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3166 "dhcp6_parser.cc"
    break;

  case 546: // $@76: %empty
#line 1957 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3176 "dhcp6_parser.cc"
    break;

  case 547: // option_def_entry: "{" $@76 option_def_params "}"
#line 1961 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3188 "dhcp6_parser.cc"
    break;

  case 548: // $@77: %empty
#line 1972 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3198 "dhcp6_parser.cc"
    break;

  case 549: // sub_option_def: "{" $@77 option_def_params "}"
#line 1976 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3210 "dhcp6_parser.cc"
    break;

  case 554: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1992 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3218 "dhcp6_parser.cc"
    break;

  case 566: // code: "code" ":" "integer"
#line 2011 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3228 "dhcp6_parser.cc"
    break;

  case 568: // $@78: %empty
#line 2019 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3237 "dhcp6_parser.cc"
    break;

  case 569: // option_def_type: "type" $@78 ":" "constant string"
#line 2022 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3247 "dhcp6_parser.cc"
    break;

  case 570: // $@79: %empty
#line 2028 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3256 "dhcp6_parser.cc"
    break;

  case 571: // option_def_record_types: "record-types" $@79 ":" "constant string"
#line 2031 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3266 "dhcp6_parser.cc"
    break;

  case 572: // $@80: %empty
#line 2037 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3275 "dhcp6_parser.cc"
    break;

  case 573: // space: "space" $@80 ":" "constant string"
#line 2040 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3285 "dhcp6_parser.cc"
    break;

  case 575: // $@81: %empty
#line 2048 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3294 "dhcp6_parser.cc"
    break;

  case 576: // option_def_encapsulate: "encapsulate" $@81 ":" "constant string"
#line 2051 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3304 "dhcp6_parser.cc"
    break;

  case 577: // option_def_array: "array" ":" "boolean"
#line 2057 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3314 "dhcp6_parser.cc"
    break;

  case 578: // $@82: %empty
#line 2067 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3326 "dhcp6_parser.cc"
    break;

  case 579: // option_data_list: "option-data" $@82 ":" "[" option_data_list_content "]"
#line 2073 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3335 "dhcp6_parser.cc"
    break;

  case 584: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2088 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3343 "dhcp6_parser.cc"
    break;

  case 585: // $@83: %empty
#line 2095 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3353 "dhcp6_parser.cc"
    break;

  case 586: // option_data_entry: "{" $@83 option_data_params "}"
#line 2099 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3362 "dhcp6_parser.cc"
    break;

  case 587: // $@84: %empty
#line 2107 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3372 "dhcp6_parser.cc"
    break;

  case 588: // sub_option_data: "{" $@84 option_data_params "}"
#line 2111 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3381 "dhcp6_parser.cc"
    break;

  case 593: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2127 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3389 "dhcp6_parser.cc"
    break;

  case 606: // $@85: %empty
#line 2149 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3398 "dhcp6_parser.cc"
    break;

  case 607: // option_data_data: "data" $@85 ":" "constant string"
#line 2152 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3408 "dhcp6_parser.cc"
    break;

  case 610: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2162 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3418 "dhcp6_parser.cc"
    break;

  case 611: // option_data_always_send: "always-send" ":" "boolean"
#line 2168 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3428 "dhcp6_parser.cc"
    break;

  case 612: // option_data_never_send: "never-send" ":" "boolean"
#line 2174 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3438 "dhcp6_parser.cc"
    break;

  case 613: // $@86: %empty
#line 2180 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3450 "dhcp6_parser.cc"
    break;

  case 614: // option_data_client_classes: "client-classes" $@86 ":" list_strings
#line 2186 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3459 "dhcp6_parser.cc"
    break;

  case 615: // $@87: %empty
#line 2194 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3471 "dhcp6_parser.cc"
    break;

  case 616: // pools_list: "pools" $@87 ":" "[" pools_list_content "]"
#line 2200 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3480 "dhcp6_parser.cc"
    break;

  case 621: // not_empty_pools_list: not_empty_pools_list ","
#line 2213 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3488 "dhcp6_parser.cc"
    break;

  case 622: // $@88: %empty
#line 2218 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3498 "dhcp6_parser.cc"
    break;

  case 623: // pool_list_entry: "{" $@88 pool_params "}"
#line 2222 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3508 "dhcp6_parser.cc"
    break;

  case 624: // $@89: %empty
#line 2228 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3518 "dhcp6_parser.cc"
    break;

  case 625: // sub_pool6: "{" $@89 pool_params "}"
#line 2232 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3528 "dhcp6_parser.cc"
    break;

  case 628: // pool_params: pool_params ","
#line 2240 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3536 "dhcp6_parser.cc"
    break;

  case 653: // $@90: %empty
#line 2271 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3545 "dhcp6_parser.cc"
    break;

  case 654: // pool_entry: "pool" $@90 ":" "constant string"
#line 2274 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3555 "dhcp6_parser.cc"
    break;

  case 655: // pool_id: "pool-id" ":" "integer"
#line 2280 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3565 "dhcp6_parser.cc"
    break;

  case 656: // $@91: %empty
#line 2286 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3573 "dhcp6_parser.cc"
    break;

  case 657: // user_context: "user-context" $@91 ":" map_value
#line 2288 "dhcp6_parser.yy"
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

  case 658: // $@92: %empty
#line 2311 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3608 "dhcp6_parser.cc"
    break;

  case 659: // comment: "comment" $@92 ":" "constant string"
#line 2313 "dhcp6_parser.yy"
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

  case 660: // $@93: %empty
#line 2341 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3649 "dhcp6_parser.cc"
    break;

  case 661: // pd_pools_list: "pd-pools" $@93 ":" "[" pd_pools_list_content "]"
#line 2347 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3658 "dhcp6_parser.cc"
    break;

  case 666: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2360 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3666 "dhcp6_parser.cc"
    break;

  case 667: // $@94: %empty
#line 2365 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3676 "dhcp6_parser.cc"
    break;

  case 668: // pd_pool_entry: "{" $@94 pd_pool_params "}"
#line 2369 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3688 "dhcp6_parser.cc"
    break;

  case 669: // $@95: %empty
#line 2377 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3698 "dhcp6_parser.cc"
    break;

  case 670: // sub_pd_pool: "{" $@95 pd_pool_params "}"
#line 2381 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3710 "dhcp6_parser.cc"
    break;

  case 673: // pd_pool_params: pd_pool_params ","
#line 2391 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3718 "dhcp6_parser.cc"
    break;

  case 688: // $@96: %empty
#line 2412 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3727 "dhcp6_parser.cc"
    break;

  case 689: // pd_prefix: "prefix" $@96 ":" "constant string"
#line 2415 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3737 "dhcp6_parser.cc"
    break;

  case 690: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2421 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3747 "dhcp6_parser.cc"
    break;

  case 691: // $@97: %empty
#line 2427 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3756 "dhcp6_parser.cc"
    break;

  case 692: // excluded_prefix: "excluded-prefix" $@97 ":" "constant string"
#line 2430 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3766 "dhcp6_parser.cc"
    break;

  case 693: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2436 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3776 "dhcp6_parser.cc"
    break;

  case 694: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2442 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3786 "dhcp6_parser.cc"
    break;

  case 695: // $@98: %empty
#line 2451 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3798 "dhcp6_parser.cc"
    break;

  case 696: // reservations: "reservations" $@98 ":" "[" reservations_list "]"
#line 2457 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3807 "dhcp6_parser.cc"
    break;

  case 701: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2468 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3815 "dhcp6_parser.cc"
    break;

  case 702: // $@99: %empty
#line 2473 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3825 "dhcp6_parser.cc"
    break;

  case 703: // reservation: "{" $@99 reservation_params "}"
#line 2477 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3834 "dhcp6_parser.cc"
    break;

  case 704: // $@100: %empty
#line 2482 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3844 "dhcp6_parser.cc"
    break;

  case 705: // sub_reservation: "{" $@100 reservation_params "}"
#line 2486 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3853 "dhcp6_parser.cc"
    break;

  case 710: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2497 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3861 "dhcp6_parser.cc"
    break;

  case 723: // $@101: %empty
#line 2517 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3873 "dhcp6_parser.cc"
    break;

  case 724: // ip_addresses: "ip-addresses" $@101 ":" list_strings
#line 2523 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3882 "dhcp6_parser.cc"
    break;

  case 725: // $@102: %empty
#line 2528 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3894 "dhcp6_parser.cc"
    break;

  case 726: // prefixes: "prefixes" $@102 ":" list_strings
#line 2534 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3903 "dhcp6_parser.cc"
    break;

  case 727: // $@103: %empty
#line 2539 "dhcp6_parser.yy"
                                     {
    ctx.unique("excluded-prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3915 "dhcp6_parser.cc"
    break;

  case 728: // excluded_prefixes: "excluded-prefixes" $@103 ":" list_strings
#line 2545 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3924 "dhcp6_parser.cc"
    break;

  case 729: // $@104: %empty
#line 2550 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3933 "dhcp6_parser.cc"
    break;

  case 730: // duid: "duid" $@104 ":" "constant string"
#line 2553 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3943 "dhcp6_parser.cc"
    break;

  case 731: // $@105: %empty
#line 2559 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3952 "dhcp6_parser.cc"
    break;

  case 732: // hw_address: "hw-address" $@105 ":" "constant string"
#line 2562 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3962 "dhcp6_parser.cc"
    break;

  case 733: // $@106: %empty
#line 2568 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3971 "dhcp6_parser.cc"
    break;

  case 734: // hostname: "hostname" $@106 ":" "constant string"
#line 2571 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3981 "dhcp6_parser.cc"
    break;

  case 735: // $@107: %empty
#line 2577 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3990 "dhcp6_parser.cc"
    break;

  case 736: // flex_id_value: "flex-id" $@107 ":" "constant string"
#line 2580 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 4000 "dhcp6_parser.cc"
    break;

  case 737: // $@108: %empty
#line 2586 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4012 "dhcp6_parser.cc"
    break;

  case 738: // reservation_client_classes: "client-classes" $@108 ":" list_strings
#line 2592 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4021 "dhcp6_parser.cc"
    break;

  case 739: // $@109: %empty
#line 2600 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 4033 "dhcp6_parser.cc"
    break;

  case 740: // relay: "relay" $@109 ":" "{" relay_map "}"
#line 2606 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4042 "dhcp6_parser.cc"
    break;

  case 742: // $@110: %empty
#line 2617 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 4054 "dhcp6_parser.cc"
    break;

  case 743: // client_classes: "client-classes" $@110 ":" "[" client_classes_list "]"
#line 2623 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4063 "dhcp6_parser.cc"
    break;

  case 746: // client_classes_list: client_classes_list ","
#line 2630 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 4071 "dhcp6_parser.cc"
    break;

  case 747: // $@111: %empty
#line 2635 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4081 "dhcp6_parser.cc"
    break;

  case 748: // client_class_entry: "{" $@111 client_class_params "}"
#line 2639 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 4091 "dhcp6_parser.cc"
    break;

  case 753: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2651 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 4099 "dhcp6_parser.cc"
    break;

  case 770: // $@112: %empty
#line 2675 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4108 "dhcp6_parser.cc"
    break;

  case 771: // client_class_test: "test" $@112 ":" "constant string"
#line 2678 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4118 "dhcp6_parser.cc"
    break;

  case 772: // $@113: %empty
#line 2684 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4127 "dhcp6_parser.cc"
    break;

  case 773: // client_class_template_test: "template-test" $@113 ":" "constant string"
#line 2687 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4137 "dhcp6_parser.cc"
    break;

  case 774: // only_if_required: "only-if-required" ":" "boolean"
#line 2694 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4147 "dhcp6_parser.cc"
    break;

  case 775: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2700 "dhcp6_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4157 "dhcp6_parser.cc"
    break;

  case 776: // $@114: %empty
#line 2709 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 4169 "dhcp6_parser.cc"
    break;

  case 777: // server_id: "server-id" $@114 ":" "{" server_id_params "}"
#line 2715 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4180 "dhcp6_parser.cc"
    break;

  case 780: // server_id_params: server_id_params ","
#line 2724 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4188 "dhcp6_parser.cc"
    break;

  case 790: // $@115: %empty
#line 2740 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 4197 "dhcp6_parser.cc"
    break;

  case 791: // server_id_type: "type" $@115 ":" duid_type
#line 2743 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4206 "dhcp6_parser.cc"
    break;

  case 792: // duid_type: "LLT"
#line 2748 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4212 "dhcp6_parser.cc"
    break;

  case 793: // duid_type: "EN"
#line 2749 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4218 "dhcp6_parser.cc"
    break;

  case 794: // duid_type: "LL"
#line 2750 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4224 "dhcp6_parser.cc"
    break;

  case 795: // htype: "htype" ":" "integer"
#line 2753 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4234 "dhcp6_parser.cc"
    break;

  case 796: // $@116: %empty
#line 2759 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4243 "dhcp6_parser.cc"
    break;

  case 797: // identifier: "identifier" $@116 ":" "constant string"
#line 2762 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4253 "dhcp6_parser.cc"
    break;

  case 798: // time: "time" ":" "integer"
#line 2768 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4263 "dhcp6_parser.cc"
    break;

  case 799: // enterprise_id: "enterprise-id" ":" "integer"
#line 2774 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4273 "dhcp6_parser.cc"
    break;

  case 800: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2782 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4283 "dhcp6_parser.cc"
    break;

  case 801: // $@117: %empty
#line 2790 "dhcp6_parser.yy"
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

  case 802: // control_socket: "control-socket" $@117 ":" "{" control_socket_params "}"
#line 2797 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4305 "dhcp6_parser.cc"
    break;

  case 803: // $@118: %empty
#line 2802 "dhcp6_parser.yy"
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

  case 804: // control_sockets: "control-sockets" $@118 ":" "[" control_socket_list "]"
#line 2809 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4327 "dhcp6_parser.cc"
    break;

  case 809: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2820 "dhcp6_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4335 "dhcp6_parser.cc"
    break;

  case 810: // $@119: %empty
#line 2825 "dhcp6_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4345 "dhcp6_parser.cc"
    break;

  case 811: // control_socket_entry: "{" $@119 control_socket_params "}"
#line 2829 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4353 "dhcp6_parser.cc"
    break;

  case 814: // control_socket_params: control_socket_params ","
#line 2835 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4361 "dhcp6_parser.cc"
    break;

  case 828: // $@120: %empty
#line 2855 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4370 "dhcp6_parser.cc"
    break;

  case 829: // control_socket_type: "socket-type" $@120 ":" control_socket_type_value
#line 2858 "dhcp6_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4379 "dhcp6_parser.cc"
    break;

  case 830: // control_socket_type_value: "unix"
#line 2864 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4385 "dhcp6_parser.cc"
    break;

  case 831: // control_socket_type_value: "http"
#line 2865 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4391 "dhcp6_parser.cc"
    break;

  case 832: // control_socket_type_value: "https"
#line 2866 "dhcp6_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4397 "dhcp6_parser.cc"
    break;

  case 833: // $@121: %empty
#line 2869 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4407 "dhcp6_parser.cc"
    break;

  case 834: // control_socket_name: "socket-name" $@121 ":" "constant string"
#line 2873 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4417 "dhcp6_parser.cc"
    break;

  case 835: // $@122: %empty
#line 2879 "dhcp6_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4427 "dhcp6_parser.cc"
    break;

  case 836: // control_socket_address: "socket-address" $@122 ":" "constant string"
#line 2883 "dhcp6_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4437 "dhcp6_parser.cc"
    break;

  case 837: // control_socket_port: "socket-port" ":" "integer"
#line 2889 "dhcp6_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4447 "dhcp6_parser.cc"
    break;

  case 838: // cert_required: "cert-required" ":" "boolean"
#line 2895 "dhcp6_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4457 "dhcp6_parser.cc"
    break;

  case 839: // $@123: %empty
#line 2901 "dhcp6_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4469 "dhcp6_parser.cc"
    break;

  case 840: // http_headers: "http-headers" $@123 ":" "[" http_header_list "]"
#line 2907 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4478 "dhcp6_parser.cc"
    break;

  case 845: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2918 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4486 "dhcp6_parser.cc"
    break;

  case 846: // $@124: %empty
#line 2923 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4496 "dhcp6_parser.cc"
    break;

  case 847: // http_header: "{" $@124 http_header_params "}"
#line 2927 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4504 "dhcp6_parser.cc"
    break;

  case 850: // http_header_params: http_header_params ","
#line 2933 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4512 "dhcp6_parser.cc"
    break;

  case 856: // $@125: %empty
#line 2945 "dhcp6_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4521 "dhcp6_parser.cc"
    break;

  case 857: // header_value: "value" $@125 ":" "constant string"
#line 2948 "dhcp6_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4531 "dhcp6_parser.cc"
    break;

  case 858: // $@126: %empty
#line 2956 "dhcp6_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4543 "dhcp6_parser.cc"
    break;

  case 859: // authentication: "authentication" $@126 ":" "{" auth_params "}"
#line 2962 "dhcp6_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4554 "dhcp6_parser.cc"
    break;

  case 862: // auth_params: auth_params ","
#line 2971 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4562 "dhcp6_parser.cc"
    break;

  case 870: // $@127: %empty
#line 2985 "dhcp6_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4571 "dhcp6_parser.cc"
    break;

  case 871: // auth_type: "type" $@127 ":" auth_type_value
#line 2988 "dhcp6_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4580 "dhcp6_parser.cc"
    break;

  case 872: // auth_type_value: "basic"
#line 2993 "dhcp6_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4586 "dhcp6_parser.cc"
    break;

  case 873: // $@128: %empty
#line 2996 "dhcp6_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4595 "dhcp6_parser.cc"
    break;

  case 874: // realm: "realm" $@128 ":" "constant string"
#line 2999 "dhcp6_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4605 "dhcp6_parser.cc"
    break;

  case 875: // $@129: %empty
#line 3005 "dhcp6_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4614 "dhcp6_parser.cc"
    break;

  case 876: // directory: "directory" $@129 ":" "constant string"
#line 3008 "dhcp6_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4624 "dhcp6_parser.cc"
    break;

  case 877: // $@130: %empty
#line 3014 "dhcp6_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4636 "dhcp6_parser.cc"
    break;

  case 878: // clients: "clients" $@130 ":" "[" clients_list "]"
#line 3020 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4645 "dhcp6_parser.cc"
    break;

  case 883: // not_empty_clients_list: not_empty_clients_list ","
#line 3031 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4653 "dhcp6_parser.cc"
    break;

  case 884: // $@131: %empty
#line 3036 "dhcp6_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4663 "dhcp6_parser.cc"
    break;

  case 885: // basic_auth: "{" $@131 clients_params "}"
#line 3040 "dhcp6_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4671 "dhcp6_parser.cc"
    break;

  case 888: // clients_params: clients_params ","
#line 3046 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4679 "dhcp6_parser.cc"
    break;

  case 896: // $@132: %empty
#line 3060 "dhcp6_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4688 "dhcp6_parser.cc"
    break;

  case 897: // user_file: "user-file" $@132 ":" "constant string"
#line 3063 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4698 "dhcp6_parser.cc"
    break;

  case 898: // $@133: %empty
#line 3069 "dhcp6_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4707 "dhcp6_parser.cc"
    break;

  case 899: // password_file: "password-file" $@133 ":" "constant string"
#line 3072 "dhcp6_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4717 "dhcp6_parser.cc"
    break;

  case 900: // $@134: %empty
#line 3080 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4729 "dhcp6_parser.cc"
    break;

  case 901: // dhcp_queue_control: "dhcp-queue-control" $@134 ":" "{" queue_control_params "}"
#line 3086 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4740 "dhcp6_parser.cc"
    break;

  case 904: // queue_control_params: queue_control_params ","
#line 3095 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4748 "dhcp6_parser.cc"
    break;

  case 911: // enable_queue: "enable-queue" ":" "boolean"
#line 3108 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4758 "dhcp6_parser.cc"
    break;

  case 912: // $@135: %empty
#line 3114 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4767 "dhcp6_parser.cc"
    break;

  case 913: // queue_type: "queue-type" $@135 ":" "constant string"
#line 3117 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4777 "dhcp6_parser.cc"
    break;

  case 914: // capacity: "capacity" ":" "integer"
#line 3123 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4787 "dhcp6_parser.cc"
    break;

  case 915: // $@136: %empty
#line 3129 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4796 "dhcp6_parser.cc"
    break;

  case 916: // arbitrary_map_entry: "constant string" $@136 ":" value
#line 3132 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4805 "dhcp6_parser.cc"
    break;

  case 917: // $@137: %empty
#line 3139 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4817 "dhcp6_parser.cc"
    break;

  case 918: // dhcp_ddns: "dhcp-ddns" $@137 ":" "{" dhcp_ddns_params "}"
#line 3145 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4828 "dhcp6_parser.cc"
    break;

  case 919: // $@138: %empty
#line 3152 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4838 "dhcp6_parser.cc"
    break;

  case 920: // sub_dhcp_ddns: "{" $@138 dhcp_ddns_params "}"
#line 3156 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4848 "dhcp6_parser.cc"
    break;

  case 923: // dhcp_ddns_params: dhcp_ddns_params ","
#line 3164 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4856 "dhcp6_parser.cc"
    break;

  case 935: // enable_updates: "enable-updates" ":" "boolean"
#line 3182 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4866 "dhcp6_parser.cc"
    break;

  case 936: // $@139: %empty
#line 3188 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4875 "dhcp6_parser.cc"
    break;

  case 937: // server_ip: "server-ip" $@139 ":" "constant string"
#line 3191 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4885 "dhcp6_parser.cc"
    break;

  case 938: // server_port: "server-port" ":" "integer"
#line 3197 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4895 "dhcp6_parser.cc"
    break;

  case 939: // $@140: %empty
#line 3203 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4904 "dhcp6_parser.cc"
    break;

  case 940: // sender_ip: "sender-ip" $@140 ":" "constant string"
#line 3206 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4914 "dhcp6_parser.cc"
    break;

  case 941: // sender_port: "sender-port" ":" "integer"
#line 3212 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4924 "dhcp6_parser.cc"
    break;

  case 942: // max_queue_size: "max-queue-size" ":" "integer"
#line 3218 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4934 "dhcp6_parser.cc"
    break;

  case 943: // $@141: %empty
#line 3224 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4943 "dhcp6_parser.cc"
    break;

  case 944: // ncr_protocol: "ncr-protocol" $@141 ":" ncr_protocol_value
#line 3227 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4952 "dhcp6_parser.cc"
    break;

  case 945: // ncr_protocol_value: "UDP"
#line 3233 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4958 "dhcp6_parser.cc"
    break;

  case 946: // ncr_protocol_value: "TCP"
#line 3234 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4964 "dhcp6_parser.cc"
    break;

  case 947: // $@142: %empty
#line 3237 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4973 "dhcp6_parser.cc"
    break;

  case 948: // ncr_format: "ncr-format" $@142 ":" "JSON"
#line 3240 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4983 "dhcp6_parser.cc"
    break;

  case 949: // $@143: %empty
#line 3248 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4995 "dhcp6_parser.cc"
    break;

  case 950: // config_control: "config-control" $@143 ":" "{" config_control_params "}"
#line 3254 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5005 "dhcp6_parser.cc"
    break;

  case 951: // $@144: %empty
#line 3260 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 5015 "dhcp6_parser.cc"
    break;

  case 952: // sub_config_control: "{" $@144 config_control_params "}"
#line 3264 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 5024 "dhcp6_parser.cc"
    break;

  case 955: // config_control_params: config_control_params ","
#line 3272 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 5032 "dhcp6_parser.cc"
    break;

  case 958: // $@145: %empty
#line 3282 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 5044 "dhcp6_parser.cc"
    break;

  case 959: // config_databases: "config-databases" $@145 ":" "[" database_list "]"
#line 3288 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5053 "dhcp6_parser.cc"
    break;

  case 960: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3293 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 5063 "dhcp6_parser.cc"
    break;

  case 961: // $@146: %empty
#line 3301 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 5075 "dhcp6_parser.cc"
    break;

  case 962: // loggers: "loggers" $@146 ":" "[" loggers_entries "]"
#line 3307 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5084 "dhcp6_parser.cc"
    break;

  case 965: // loggers_entries: loggers_entries ","
#line 3316 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 5092 "dhcp6_parser.cc"
    break;

  case 966: // $@147: %empty
#line 3322 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 5102 "dhcp6_parser.cc"
    break;

  case 967: // logger_entry: "{" $@147 logger_params "}"
#line 3326 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 5110 "dhcp6_parser.cc"
    break;

  case 970: // logger_params: logger_params ","
#line 3332 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 5118 "dhcp6_parser.cc"
    break;

  case 978: // debuglevel: "debuglevel" ":" "integer"
#line 3346 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 5128 "dhcp6_parser.cc"
    break;

  case 979: // $@148: %empty
#line 3352 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5137 "dhcp6_parser.cc"
    break;

  case 980: // severity: "severity" $@148 ":" "constant string"
#line 3355 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 5147 "dhcp6_parser.cc"
    break;

  case 981: // $@149: %empty
#line 3361 "dhcp6_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 5159 "dhcp6_parser.cc"
    break;

  case 982: // output_options_list: "output-options" $@149 ":" "[" output_options_list_content "]"
#line 3367 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5168 "dhcp6_parser.cc"
    break;

  case 985: // output_options_list_content: output_options_list_content ","
#line 3374 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 5176 "dhcp6_parser.cc"
    break;

  case 986: // $@150: %empty
#line 3379 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 5186 "dhcp6_parser.cc"
    break;

  case 987: // output_entry: "{" $@150 output_params_list "}"
#line 3383 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 5194 "dhcp6_parser.cc"
    break;

  case 990: // output_params_list: output_params_list ","
#line 3389 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 5202 "dhcp6_parser.cc"
    break;

  case 996: // $@151: %empty
#line 3401 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5211 "dhcp6_parser.cc"
    break;

  case 997: // output: "output" $@151 ":" "constant string"
#line 3404 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5221 "dhcp6_parser.cc"
    break;

  case 998: // flush: "flush" ":" "boolean"
#line 3410 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5231 "dhcp6_parser.cc"
    break;

  case 999: // maxsize: "maxsize" ":" "integer"
#line 3416 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5241 "dhcp6_parser.cc"
    break;

  case 1000: // maxver: "maxver" ":" "integer"
#line 3422 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5251 "dhcp6_parser.cc"
    break;

  case 1001: // $@152: %empty
#line 3428 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5260 "dhcp6_parser.cc"
    break;

  case 1002: // pattern: "pattern" $@152 ":" "constant string"
#line 3431 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5270 "dhcp6_parser.cc"
    break;

  case 1003: // $@153: %empty
#line 3437 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5282 "dhcp6_parser.cc"
    break;

  case 1004: // compatibility: "compatibility" $@153 ":" "{" compatibility_params "}"
#line 3443 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5291 "dhcp6_parser.cc"
    break;

  case 1007: // compatibility_params: compatibility_params ","
#line 3450 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5299 "dhcp6_parser.cc"
    break;

  case 1010: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3459 "dhcp6_parser.yy"
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


  const short Dhcp6Parser::yypact_ninf_ = -1446;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     482, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446,   120,    45,    49,    57,   227,
     247,   255,   266,   267,   289,   293,   295,   310,   313,   314,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,    45,  -183,
      93,   767,    56,  1445,   346,   -20,   256,   -15,   134,   217,
    -108,   214,   103, -1446,   312,   324,   327,   320,   331, -1446,
      43, -1446, -1446, -1446, -1446, -1446, -1446, -1446,   334,   345,
     348,   350,   352,   362,   372,   388,   391,   392,   402,   403,
     427,   438, -1446,   442,   449,   452,   453,   455, -1446, -1446,
   -1446,   456,   465,   476,   488,   498,   506,   508, -1446, -1446,
   -1446,   524, -1446, -1446, -1446, -1446, -1446, -1446,   525,   527,
     529, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
     530, -1446, -1446, -1446, -1446, -1446, -1446, -1446,   533,   535,
     537, -1446, -1446,   540, -1446,    75, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,   547,
     548,   555,   556, -1446,    98, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446,   558, -1446, -1446, -1446, -1446, -1446,   559,
     562, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,   143,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446,   563, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446,   153, -1446, -1446, -1446, -1446, -1446, -1446,   564,
   -1446,   565,   566, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446,   156, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446,   397,   332, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446,   475, -1446, -1446,   569, -1446, -1446, -1446,   570,
   -1446, -1446,   567,   573, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446,   575,   576,   577,
   -1446, -1446, -1446, -1446, -1446,   574,   582, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446,   174, -1446, -1446, -1446,   584, -1446,   585, -1446,   586,
     587, -1446, -1446, -1446, -1446, -1446,   258, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446,   588,   282, -1446,
   -1446, -1446, -1446,    45,    45, -1446,   336,   590, -1446, -1446,
     591,   592,   593,   594,   595,   597,   360,   361,   364,   365,
     368,   369,   375,   376,   370,   373,   377,   378,   381,   382,
     600,   385,   389,   386,   390,   393,   629,   632,   637,   407,
     411,   416,   404,   418,   420,   421,   663,   666,   668,   431,
     670,   671,   673,   674,   676,   679,   440,   441,   444,   682,
     686,   688,   691,   693,   695,   697,   698,   699,   462,   702,
     703,   719,   720,   721,   722,   723,   484,   485,   486,   727,
     728, -1446,   767, -1446,   729,   492,   494,   499,   500,    56,
   -1446,   496,   730,   731,   736,   742,   743,   507,   509,   746,
     747,   750,   751,   752,  1445, -1446,   753,   517,   346, -1446,
     754,   519,   756,   520,   521,   -20, -1446,   760,   763,   764,
     765,   766,   771,   776,   777, -1446,   256, -1446,   779,   780,
     543,   782,   783,   787,   549, -1446,   134,   788,   550,   551,
     552,   793, -1446,   217,   794,   795,   -53, -1446,   560,   796,
     568,   803,   571,   572,   804,   805,   214, -1446,   807,   578,
     103, -1446, -1446, -1446,   808,   809,   614,   810,   811,   812,
     827,   851, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446,   616, -1446, -1446, -1446,
   -1446, -1446,  -121,   617,   618, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446,   855,   856,   857, -1446,   622,   623,    27,   864,
     863,   630, -1446, -1446, -1446,   867,   869,   870,   871,   872,
     874,   875,   877,   878, -1446,   879,   880,   876,   881,   889,
     635,   656, -1446, -1446, -1446,   894,   893, -1446,   896, -1446,
   -1446, -1446, -1446, -1446, -1446,   897,   898,   664,   665,   667,
   -1446, -1446,   896,   896,   896,   669,   902, -1446,   672, -1446,
   -1446,   677, -1446,   680, -1446, -1446, -1446,   896,   896,   896,
     896,   681,   683,   684,   687, -1446,   689,   690, -1446,   692,
     696,   700, -1446, -1446,   701, -1446, -1446, -1446,   896, -1446,
     704,   863, -1446, -1446,   705, -1446,   706, -1446, -1446,   -95,
     609, -1446,   899, -1446, -1446,    45,   767, -1446,   103,    56,
     167,   167,   904, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446,   905,   907,   908, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446,   910, -1446, -1446, -1446,   -87,    45,    91,   122,
     913,   916,   920,   114,   112,   124,   200,   922,   132,   214,
   -1446, -1446,   925,  -171, -1446, -1446,   929,   931, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446,   802, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446,   904, -1446,   311,   339,   342, -1446, -1446, -1446,
   -1446,   940,   944,   945,   946,   947,   948,   949,   950,   951,
     952, -1446,   953,   955, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446,   343, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
     374, -1446,   954,   768, -1446, -1446,   957,   958, -1446, -1446,
     959,   961, -1446, -1446,   960,   964, -1446, -1446,   962,   966,
   -1446, -1446, -1446,    96, -1446, -1446, -1446,   965, -1446, -1446,
   -1446,   163, -1446, -1446, -1446, -1446, -1446,   383, -1446, -1446,
   -1446, -1446,   173, -1446, -1446,   967,   969, -1446, -1446,   968,
     972, -1446,   973,   980,   981,   982,   983,   984,   401, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,   985,   986,
     987, -1446, -1446, -1446, -1446,   422, -1446, -1446, -1446, -1446,
   -1446, -1446,   989,   990,   991, -1446,   429, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446,   992, -1446,   993, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446,   435, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446,   970,   995, -1446,   996,
   -1446,   997, -1446, -1446, -1446,   436, -1446, -1446, -1446, -1446,
   -1446,   437, -1446,   220, -1446,   998, -1446,   479, -1446, -1446,
     758, -1446,   999,  1000, -1446, -1446,  1001,  1003, -1446, -1446,
    1002,  1005, -1446, -1446, -1446,  1008,  1009,  1010,  1011,   762,
     726,   774,   773,   778,   781,   784,   785,   786,   789,  1014,
     775,   791,  1017,  1018,  1020,  1021,  1025,   167, -1446, -1446,
     167, -1446,   904,  1445, -1446,   905,   134, -1446,   907,   217,
   -1446,   908,  1543, -1446,   910,   -87, -1446, -1446,    91, -1446,
    1026,  1030,   122, -1446,   225,   913, -1446,   256, -1446,   916,
    -108, -1446,   920,   797,   800,   806,   813,   815,   820,   114,
   -1446,  1032,  1033,   821,   823,   826,   112, -1446,   829,   834,
     839,   124, -1446,  1043,  1046,  1067,   842,  1088,   850,  1093,
     200, -1446,   200, -1446,   922,   858,  1099,   866,  1108,   132,
   -1446, -1446,   248,   925, -1446,   873,  -171, -1446, -1446,  1113,
    1006,   346, -1446,   929,   -20, -1446,   931, -1446, -1446,   884,
     890,   891,   900, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446,    40, -1446, -1446,   909,   911,   914,   424,
     917, -1446,   483, -1446,   487, -1446,  1114, -1446,  1127, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446,   490, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446,   921,   924, -1446, -1446, -1446,  1117,
    1136, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446,  1137,  1145, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446,  1153, -1446,   491, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446,    46,   934, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446,   208,   939,   943, -1446,  1163, -1446,  1184, -1446,
     493, -1446, -1446,   975, -1446,    45, -1446, -1446,  1199, -1446,
   -1446, -1446, -1446, -1446,   497, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446,   977,   501, -1446,   503, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446,  1543, -1446, -1446, -1446,  1209,
    1220,   994,  1004, -1446,   225, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,    58,  1219,
   -1446, -1446, -1446,  1224,   988,  1227,   248, -1446, -1446, -1446,
   -1446, -1446,  1012,  1013, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446,   505, -1446, -1446, -1446, -1446, -1446,
   -1446,  1228,  1230, -1446,  1231, -1446,  1015, -1446, -1446, -1446,
    1233,  1235,  1236,  1237,    58, -1446,   149, -1446,  1219,  1239,
   -1446,  1061,  1022,  1023,  1244, -1446, -1446, -1446, -1446, -1446,
   -1446,   515, -1446, -1446, -1446, -1446,   257, -1446, -1446, -1446,
   -1446, -1446,  1251,  1240,   149, -1446,    35,  1239, -1446, -1446,
    1245,  1256, -1446,  1024, -1446, -1446,  1257,  1258,  1262, -1446,
     516, -1446, -1446, -1446, -1446, -1446, -1446, -1446,   207, -1446,
    1251, -1446,  1263,  1027,  1028,  1031,  1264,    35, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446,   518, -1446, -1446, -1446,
   -1446,  1034, -1446, -1446, -1446,  1035, -1446,  1265,  1268,   207,
   -1446, -1446, -1446,  1036,  1037, -1446, -1446, -1446
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   206,     9,   400,    11,
     624,    13,   669,    15,   704,    17,   539,    19,   548,    21,
     587,    23,   362,    25,   919,    27,   951,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   706,     0,   550,   589,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   144,   949,   204,   225,   227,   229,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   194,     0,     0,     0,     0,     0,   164,   171,
     173,     0,     0,     0,     0,     0,     0,     0,   391,   537,
     578,     0,   197,   199,   177,   476,   656,   658,     0,     0,
       0,   318,   337,   327,   307,   742,   695,   353,   374,   776,
       0,   339,   801,   803,   900,   917,   187,   189,     0,     0,
       0,   961,  1003,     0,   143,     0,    69,    72,    73,    74,
      75,    76,    77,    78,    79,    80,   111,   112,   113,   114,
     115,    81,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   117,   118,   132,   133,   134,
     107,   140,   141,   142,   136,   137,   138,    84,    85,    86,
      87,   104,    88,    90,    89,   135,    94,    95,    82,   108,
     109,   110,    83,    92,    93,   102,   103,   105,    91,    96,
      97,    98,    99,   100,   101,   106,   116,   139,   219,     0,
       0,     0,     0,   218,     0,   208,   211,   212,   213,   214,
     215,   216,   217,     0,   615,   660,   457,   459,   461,     0,
       0,   465,   467,   469,   463,   739,   456,   405,   406,   407,
     408,   409,   410,   411,   412,   432,   433,   434,   435,   436,
     437,   440,   441,   442,   443,   444,   445,   446,   447,   448,
     449,   450,   451,   452,   438,   439,   453,   454,   455,     0,
     402,   416,   417,   418,   421,   422,   423,   424,   426,   427,
     428,   419,   420,   413,   414,   430,   431,   415,   425,   429,
     653,     0,   652,   636,   637,   638,   639,   640,   641,   642,
     643,   644,   645,   646,   647,   648,   649,   632,   633,   634,
     635,   631,     0,   626,   629,   630,   650,   651,   688,     0,
     691,     0,     0,   687,   679,   680,   681,   682,   678,   677,
     685,   686,     0,   671,   674,   675,   683,   684,   676,   737,
     723,   725,   727,   729,   731,   733,   735,   722,   719,   720,
     721,     0,   707,   708,   713,   714,   715,   711,   716,   717,
     718,   712,     0,   568,   274,     0,   572,   570,   575,     0,
     564,   565,     0,   551,   552,   555,   567,   556,   557,   558,
     574,   559,   560,   561,   562,   563,   606,     0,     0,     0,
     613,   604,   605,   608,   609,     0,   590,   591,   594,   595,
     596,   597,   598,   599,   600,   603,   601,   602,   370,   372,
     367,     0,   364,   368,   369,     0,   936,     0,   939,     0,
       0,   943,   947,   934,   932,   933,     0,   921,   924,   925,
     926,   927,   928,   929,   930,   931,   958,     0,     0,   953,
     956,   957,    47,    52,     0,    39,    45,     0,    66,    62,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    60,    71,    68,     0,     0,     0,     0,     0,   210,
     207,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   404,   401,     0,     0,   628,   625,
       0,     0,     0,     0,     0,   673,   670,     0,     0,     0,
       0,     0,     0,     0,     0,   705,   710,   540,     0,     0,
       0,     0,     0,     0,     0,   549,   554,     0,     0,     0,
       0,     0,   588,   593,     0,     0,   366,   363,     0,     0,
       0,     0,     0,     0,     0,     0,   923,   920,     0,     0,
     955,   952,    51,    43,     0,     0,     0,     0,     0,     0,
       0,     0,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   160,     0,   192,   193,   161,
     162,   163,     0,     0,     0,   175,   176,   183,   184,   185,
     186,   191,     0,     0,     0,   196,     0,     0,     0,     0,
       0,     0,   471,   472,   473,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   800,     0,     0,     0,     0,     0,
       0,     0,   201,   202,   203,     0,     0,    70,     0,   221,
     222,   223,   224,   209,   159,     0,     0,     0,     0,     0,
     474,   475,     0,     0,     0,     0,     0,   403,     0,   655,
     627,     0,   690,     0,   693,   694,   672,     0,     0,     0,
       0,     0,     0,     0,     0,   709,     0,     0,   566,     0,
       0,     0,   577,   553,     0,   610,   611,   612,     0,   592,
       0,     0,   365,   935,     0,   938,     0,   941,   942,     0,
       0,   922,     0,   960,   954,     0,     0,   145,     0,     0,
       0,     0,   231,   195,   166,   167,   168,   169,   170,   165,
     172,   174,   393,   541,   580,   198,   200,   179,   180,   181,
     182,   178,   478,    40,   657,   659,     0,    48,     0,     0,
       0,   697,   355,     0,     0,     0,     0,   805,     0,     0,
     188,   190,     0,     0,    53,   220,   617,   662,   458,   460,
     462,   466,   468,   470,   464,     0,   654,   689,   692,   738,
     724,   726,   728,   730,   732,   734,   736,   569,   275,   573,
     571,   576,   607,   614,   371,   373,   937,   940,   945,   946,
     944,   948,   231,    44,     0,     0,     0,   265,   267,   269,
     271,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   284,     0,     0,   292,   294,   296,   298,   300,   301,
     302,   303,   304,   305,   264,     0,   238,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     255,   256,   257,   258,   254,   259,   260,   261,   262,   263,
       0,   236,     0,   232,   233,   398,     0,   394,   395,   546,
       0,   542,   543,   585,     0,   581,   582,   483,     0,   479,
     480,   325,   326,     0,   320,   323,   324,     0,   335,   336,
     332,     0,   329,   333,   334,   314,   316,     0,   309,   312,
     313,   747,     0,   744,   702,     0,   698,   699,   360,     0,
     356,   357,     0,     0,     0,     0,     0,     0,     0,   376,
     379,   380,   381,   382,   383,   384,   790,   796,     0,     0,
       0,   789,   786,   787,   788,     0,   778,   781,   784,   782,
     783,   785,     0,     0,     0,   349,     0,   341,   344,   345,
     346,   347,   348,   828,   833,   835,     0,   858,     0,   839,
     827,   820,   821,   822,   825,   826,     0,   812,   815,   816,
     817,   818,   823,   824,   819,   810,     0,   806,   807,     0,
     912,     0,   915,   908,   909,     0,   902,   905,   906,   907,
     910,     0,   966,     0,   963,     0,  1009,     0,  1005,  1008,
      55,   622,     0,   618,   619,   667,     0,   663,   664,   741,
       0,     0,    64,   950,   205,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   240,   226,   228,
       0,   230,   235,     0,   392,   397,   550,   538,   545,   589,
     579,   584,     0,   477,   482,   322,   319,   338,   331,   328,
       0,     0,   311,   308,   749,   746,   743,   706,   696,   701,
       0,   354,   359,     0,     0,     0,     0,     0,     0,   378,
     375,     0,     0,     0,     0,     0,   780,   777,     0,     0,
       0,   343,   340,     0,     0,     0,     0,     0,     0,     0,
     814,   802,     0,   804,   809,     0,     0,     0,     0,   904,
     901,   918,     0,   965,   962,     0,  1007,  1004,    57,     0,
      56,     0,   616,   621,     0,   661,   666,   740,   959,     0,
       0,     0,     0,   273,   276,   277,   278,   279,   280,   281,
     282,   291,   283,     0,   289,   290,     0,     0,     0,     0,
       0,   239,     0,   234,     0,   396,     0,   544,     0,   583,
     536,   503,   504,   505,   507,   508,   509,   492,   493,   512,
     513,   514,   515,   516,   517,   520,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   531,   532,   518,   519,
     533,   534,   535,   488,   489,   490,   491,   499,   500,   501,
     502,   496,   497,   498,   506,     0,   485,   494,   510,   511,
     495,   481,   321,   330,     0,     0,   310,   770,   772,     0,
       0,   768,   762,   763,   764,   765,   766,   767,   769,   759,
     760,   761,     0,   750,   751,   754,   755,   756,   757,   758,
     745,     0,   700,     0,   358,   385,   386,   387,   388,   389,
     390,   377,     0,     0,   795,   798,   799,   779,   350,   351,
     352,   342,     0,     0,     0,   837,     0,   838,     0,   813,
       0,   808,   911,     0,   914,     0,   903,   981,     0,   979,
     977,   971,   975,   976,     0,   968,   973,   974,   972,   964,
    1010,  1006,    54,    59,     0,   620,     0,   665,   266,   268,
     270,   272,   286,   287,   288,   285,   293,   295,   297,   299,
     306,   237,   399,   547,   586,   487,   484,   315,   317,     0,
       0,     0,     0,   748,   753,   703,   361,   792,   793,   794,
     791,   797,   830,   831,   832,   829,   834,   836,     0,   841,
     811,   913,   916,     0,     0,     0,   970,   967,    58,   623,
     668,   486,     0,     0,   774,   775,   752,   870,   873,   875,
     877,   869,   868,   867,     0,   860,   863,   864,   865,   866,
     846,     0,   842,   843,     0,   978,     0,   969,   771,   773,
       0,     0,     0,     0,   862,   859,     0,   840,   845,     0,
     980,     0,     0,     0,     0,   861,   856,   855,   851,   853,
     854,     0,   848,   852,   844,   986,     0,   983,   872,   871,
     874,   876,   879,     0,   850,   847,     0,   985,   982,   884,
       0,   880,   881,     0,   849,   996,     0,     0,     0,  1001,
       0,   988,   991,   992,   993,   994,   995,   984,     0,   878,
     883,   857,     0,     0,     0,     0,     0,   990,   987,   896,
     898,   895,   889,   891,   893,   894,     0,   886,   890,   892,
     882,     0,   998,   999,  1000,     0,   989,     0,     0,   888,
     885,   997,  1002,     0,     0,   887,   897,   899
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446,   -10, -1446,  -635, -1446,
     513, -1446, -1446, -1446, -1446,   472, -1446,  -288, -1446, -1446,
   -1446,   -71, -1446, -1446, -1446, -1446, -1446, -1446, -1446,   504,
     732, -1446, -1446,   -52,   -29,   -26,   -24,     4,    12,   -25,
      82,    84,    87,    89,    90,    92, -1084, -1446,    31,    34,
      41,    48, -1446, -1446,    51, -1446,    54, -1446,    61,    94,
      64, -1446, -1446,    66,    69,    71,    74,    76, -1446,    79,
   -1446,    95, -1446, -1446, -1446, -1446, -1446,    97, -1446,   102,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,   502,   724,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446,   423, -1446,   180, -1446,  -756,   189, -1446, -1446,
   -1445, -1446, -1429, -1446, -1446, -1446, -1446,   -66, -1446,  -788,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446,  -805, -1446,  -793, -1446,  -792, -1446,    78,
   -1446, -1446, -1446, -1446, -1446, -1446,   166, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446,   176,  -781, -1446, -1446, -1446, -1446,
     171, -1446, -1446, -1446, -1446, -1446, -1446, -1446,   147, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446,   168, -1446, -1446, -1446,
     172,   685, -1446, -1446, -1446, -1446, -1446, -1446, -1446,   164,
   -1446, -1446, -1446, -1446, -1446, -1446, -1083, -1446, -1446, -1446,
     201, -1446, -1446, -1446,   202,   733, -1446, -1446, -1077, -1446,
   -1074, -1446,   109, -1446,   111, -1446,   113, -1446,   115, -1446,
     105,   107,   108, -1446, -1072, -1446, -1446, -1446, -1446,   194,
   -1446, -1446,   -65,  1234, -1446, -1446, -1446, -1446, -1446,   204,
   -1446, -1446, -1446,   209, -1446,   708, -1446,   -60, -1446, -1446,
   -1446, -1446, -1446,   -57, -1446, -1446, -1446, -1446, -1446,   -58,
   -1446, -1446, -1446,   205, -1446, -1446, -1446,   210, -1446,   707,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446,   138, -1446, -1446, -1446,   141,   759,
   -1446, -1446,   -55,   -42, -1446,   -13, -1446, -1446, -1446, -1446,
   -1446,   142, -1446, -1446, -1446,   140,   744, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446,   -59, -1446, -1446, -1446,   212, -1446,
   -1446, -1446,   203, -1446,   735,   510, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1071, -1446, -1446, -1446, -1446, -1446,   211, -1446, -1446,
   -1446,   -50, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446,   192, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,   175, -1446,
     181,   184, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446,  -101, -1446, -1446,  -126, -1446,
   -1446, -1446, -1446, -1446,   -92, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446,  -147, -1446, -1446,  -175,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446,   188, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,   542,   737,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446,   581,   738, -1446,
   -1446, -1446, -1446, -1446, -1446,   193, -1446, -1446,   -41, -1446,
   -1446, -1446, -1446, -1446, -1446,  -110, -1446, -1446,  -138, -1446,
   -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446, -1446,   196,
   -1446
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     804,    87,    88,    41,    68,    84,    85,   825,  1060,  1179,
    1180,   894,    43,    70,    90,   477,    91,    45,    71,   165,
     166,   167,   480,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   280,   181,   182,   183,
     184,   185,   506,   789,   186,   507,   187,   508,   188,   189,
     190,   522,   801,   191,   192,   193,   194,   195,   544,   196,
     545,   197,   198,   199,   200,   500,   201,   202,   520,   203,
     521,   204,   205,   206,   207,   482,    47,    72,   244,   245,
     246,   554,   247,   248,   249,   250,   208,   483,   209,   484,
     210,   485,   922,   923,   924,  1100,   895,   896,   897,  1075,
     898,  1076,   899,  1077,   900,  1078,   901,   902,   599,   903,
     904,   905,   906,   907,   908,   909,   910,   911,  1089,  1365,
     912,   913,   914,   915,  1092,   916,  1093,   917,  1094,   918,
    1095,   919,  1096,   211,   532,   957,   958,   959,  1120,   960,
    1121,   212,   529,   943,   944,   945,   946,   213,   531,   951,
     952,   953,   954,   214,   530,   215,   539,  1006,  1007,  1008,
    1009,  1010,   216,   535,   969,   970,   971,  1130,    63,    80,
     441,   442,   443,   614,   444,   615,   217,   536,   978,   979,
     980,   981,   982,   983,   984,   985,   218,   516,   926,   927,
     928,  1103,    49,    73,   299,   300,   301,   564,   302,   565,
     303,   566,   304,   572,   305,   569,   306,   570,   307,   571,
     219,   220,   221,   311,   312,   222,   523,   938,   939,   940,
    1112,  1265,  1266,   223,   517,    57,    77,   930,   931,   932,
    1106,    59,    78,   402,   403,   404,   405,   406,   407,   408,
     598,   409,   602,   410,   601,   411,   412,   603,   413,   224,
     518,   934,   935,   936,  1109,    61,    79,   425,   426,   427,
     428,   429,   607,   430,   431,   432,   433,   434,   435,   611,
     314,   562,  1062,  1063,  1064,  1181,    51,    74,   342,   343,
     344,   576,   345,   225,   524,   226,   525,   317,   563,  1066,
    1067,  1068,  1184,    53,    75,   362,   363,   364,   580,   365,
     366,   582,   367,   368,   227,   534,   965,   966,   967,  1127,
      55,    76,   381,   382,   383,   384,   588,   385,   589,   386,
     590,   387,   591,   388,   592,   389,   593,   390,   594,   391,
     587,   319,   573,  1070,   228,   533,   962,   963,  1124,  1292,
    1293,  1294,  1295,  1296,  1379,  1297,  1380,  1298,  1299,   229,
     537,   995,   996,   997,  1141,  1390,   998,   999,  1142,  1000,
    1001,   230,   231,   540,   232,   541,  1036,  1037,  1038,  1162,
    1026,  1027,  1028,  1153,  1395,  1029,  1154,  1030,  1155,  1031,
    1032,  1033,  1159,  1431,  1432,  1433,  1446,  1461,  1462,  1463,
    1473,  1034,  1157,  1424,  1425,  1426,  1440,  1469,  1427,  1441,
    1428,  1442,  1429,  1443,  1480,  1481,  1482,  1498,  1516,  1517,
    1518,  1527,  1519,  1528,   233,   542,  1045,  1046,  1047,  1048,
    1166,  1049,  1050,  1168,   234,   543,    65,    81,   456,   457,
     458,   459,   619,   460,   461,   621,   462,   463,   464,   624,
     860,   465,   625,   235,   481,    67,    82,   468,   469,   470,
     628,   471,   236,   549,  1053,  1054,  1172,  1344,  1345,  1346,
    1347,  1405,  1348,  1403,  1466,  1467,  1476,  1490,  1491,  1492,
    1502,  1493,  1494,  1495,  1496,  1506,   237,   550,  1057,  1058,
    1059
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     164,   243,   266,   322,   353,   377,    38,   400,   421,   440,
     453,  1021,   401,   422,   318,   313,   341,   358,   378,   423,
     359,   267,   424,  1022,  1023,   920,   992,   950,  1234,  1254,
     251,   315,   346,   360,   379,  1255,   414,   436,  1256,   454,
    1264,  1270,   438,   439,   268,   803,   478,   269,   273,   270,
      31,   479,    32,  1512,    33,  1055,    42,   941,    86,   252,
     316,   347,   361,   380,    44,   415,   437,   130,   455,  1513,
     163,   129,   238,   239,   240,   241,   242,   271,   552,  1362,
    1363,  1364,  1417,   553,  1512,   272,   784,   785,   786,   787,
     348,   349,   350,   351,   352,   136,   137,   438,   439,  1115,
    1513,   559,  1116,    89,   281,   323,   560,   282,   324,   858,
     859,   261,   262,   263,   283,   325,   466,   467,   264,   321,
      30,   284,   326,   788,   285,   327,   803,   286,   328,   797,
     798,   799,   800,   163,   287,   329,   986,   289,   330,   290,
     331,   872,   291,   332,   292,   333,   574,   293,   334,   294,
     335,   575,   295,   336,   942,   274,   578,   275,   393,   585,
     276,   579,   277,   278,   586,   279,  1118,   288,   296,  1119,
     297,   136,   137,   136,   137,   298,  1125,   616,   308,  1126,
     309,   310,   617,   337,   354,   338,   355,   339,   356,   340,
     357,   867,   868,   869,   870,   871,   872,   873,   874,   875,
     876,   877,   878,   879,   880,   881,  1387,  1388,  1389,   882,
     883,   884,   885,   886,   887,   888,   889,   890,   891,   892,
     893,   163,   394,  1173,   395,   396,  1174,   136,   137,   397,
     398,   399,   868,   869,    46,   941,   948,   394,   949,   136,
     137,  1418,  1419,  1420,   884,   885,   886,   136,   137,   136,
     137,   955,   956,  1485,    48,   394,  1486,  1487,  1488,  1489,
    1477,   626,    50,  1478,   136,   137,   627,   972,   973,   974,
     975,   976,   977,    52,    54,   987,   988,   989,   990,    98,
      99,   100,   101,   102,   103,   630,    34,    35,    36,    37,
     631,  1234,  1254,  1002,  1003,  1004,    56,   163,  1255,   163,
      58,  1256,    60,  1264,  1270,   394,   416,   395,   396,   417,
     418,   419,   130,   394,   552,   136,   137,    62,   472,  1072,
      64,    66,   136,   137,  1039,  1040,  1041,   473,   475,   136,
     137,   474,   136,   137,   476,   596,   394,   950,   486,  1456,
     136,   137,   630,   130,  1212,   559,  1097,  1073,   420,   487,
    1074,  1098,   488,   163,   489,  1021,   490,  1021,   992,  1277,
    1278,  1279,  1280,   136,   137,   163,   491,  1022,  1023,  1022,
    1023,   136,   137,  1042,  1013,   163,   492,  1097,  1014,  1015,
    1016,  1017,  1099,  1392,  1393,  1394,  1122,   369,  1018,  1019,
     163,  1123,   493,  1509,  1510,   494,   495,   370,   371,   372,
     373,   374,   375,   376,  1139,   595,   496,   497,   163,  1140,
     445,   446,   447,   448,   449,   450,   451,   452,   115,   116,
     117,   118,   119,   120,   121,  1146,   123,   124,   125,   126,
    1147,   498,  1151,   130,   831,   832,   833,  1152,  1160,  1169,
     626,   163,   499,  1161,  1170,  1171,   501,   134,   163,   839,
     840,   841,   842,   502,   320,   163,   503,   504,   163,   505,
     509,   136,   137,   632,   633,  1337,   163,  1338,  1339,   510,
     853,   887,   888,   889,   890,   891,   892,   261,   262,   263,
     511,   164,  1176,   597,   264,   321,  1097,  1177,   243,   163,
     574,  1371,   512,  1375,   616,  1372,  1160,   163,  1376,  1386,
    1406,  1400,   513,   266,   578,  1407,   585,   322,  1444,  1409,
     514,  1410,   515,  1445,   353,   318,   313,   251,  1474,  1507,
     341,  1529,   267,  1475,  1508,   377,  1530,   358,   519,   526,
     359,   527,   315,   528,   538,   400,   346,   546,   378,   547,
     401,   548,   421,   360,   551,   268,   252,   422,   269,   273,
     270,   555,   556,   423,   379,   453,   424,   156,   157,   557,
     558,   316,   561,   567,   414,   347,   568,   577,   581,   583,
     584,   436,   361,   600,   604,   605,   606,   634,   271,   608,
     609,   610,   612,   380,   454,   613,   272,   163,   618,   620,
     622,   623,   629,   415,   635,   636,   637,   638,   639,   640,
     437,   641,   642,   643,   656,   281,   644,   645,   282,   323,
     646,   647,   324,   455,   650,   283,   651,   648,   649,   325,
     652,   653,   284,   654,   655,   285,   326,   657,   286,   327,
     659,   658,   328,   662,   660,   287,   663,   661,   289,   329,
     290,   664,   330,   291,   331,   292,   668,   332,   293,   333,
     294,   665,   334,   295,   335,   666,   274,   336,   275,   667,
     669,   276,   670,   277,   278,   671,   279,   672,   288,   296,
     673,   297,   674,   675,   676,   677,   298,   678,   679,   308,
     680,   309,   310,   681,   682,   683,   685,   337,   684,   338,
     686,   339,   687,   340,   354,   688,   355,   689,   356,   690,
     357,   691,   692,   693,   694,   164,   695,   696,   243,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,   697,   698,   699,   700,   701,   702,   703,
     704,   705,   706,   708,   715,   716,   709,   251,   710,   714,
     717,   711,   712,   991,  1005,  1020,   718,   719,   453,   720,
     722,   723,  1056,   721,   724,   725,   726,   728,   731,   729,
     733,   732,   734,   735,   737,   863,   252,   738,   739,   740,
     741,  1102,   993,  1011,  1024,   742,  1043,   454,    92,    93,
     743,   744,    94,   746,   747,   748,   749,   750,    95,    96,
      97,   751,   754,   752,   755,   756,   757,   758,   760,   761,
     764,   994,  1012,  1025,   763,  1044,   455,   766,   769,   770,
     765,   772,   775,   767,   768,   861,   776,   778,   779,   780,
     773,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   781,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   777,   782,   783,   790,   791,
     792,   793,   794,   795,   796,   131,   132,   133,   134,   802,
      32,   805,   806,   135,   807,   808,   820,   810,   809,   811,
     812,   817,   136,   137,   813,   814,   815,   816,   818,   138,
     139,   140,   141,   142,   143,   144,   819,   821,   145,   822,
     823,   824,   826,   827,   862,   828,   829,   146,   830,   835,
     834,   921,   925,   836,   929,   933,   147,   937,   837,   148,
     961,   838,   843,   964,   844,   845,   149,   968,   846,  1035,
     847,   848,  1052,   849,   150,   151,  1061,   850,  1065,   152,
     153,   851,   852,   370,  1079,   854,   856,   857,  1080,  1081,
    1082,  1083,  1084,  1085,  1086,  1087,  1088,  1090,   154,  1091,
    1101,  1105,   155,  1104,  1108,  1107,  1110,  1111,  1113,  1114,
    1194,  1117,  1129,  1128,  1131,  1132,  1163,  1133,   156,   157,
     158,   159,   160,   161,  1134,  1135,  1136,  1137,  1138,  1143,
    1144,  1145,   162,  1148,  1149,  1150,  1156,  1158,  1164,  1178,
    1165,  1167,  1175,  1183,  1193,  1182,  1186,  1185,   163,  1353,
    1187,  1188,  1189,  1190,  1191,  1192,  1195,  1196,  1203,  1204,
    1197,  1206,  1207,  1198,  1208,  1209,  1199,  1200,  1201,  1210,
    1274,  1202,   266,  1205,  1275,   400,  1312,  1313,   421,  1305,
     401,  1220,  1306,   422,   318,   313,  1253,  1322,  1307,   423,
    1323,   267,   424,  1281,  1267,  1308,   377,  1309,  1288,   440,
    1221,   315,  1310,  1314,   414,  1315,  1289,   436,  1316,   378,
    1268,  1324,  1282,  1318,   268,   991,  1319,   269,   273,   270,
    1005,  1320,  1290,  1222,  1325,   379,  1223,  1227,  1224,  1020,
     316,  1020,  1326,   415,  1327,  1283,   437,  1328,  1284,  1269,
    1285,  1340,  1332,  1333,   993,  1056,  1341,   271,  1334,  1011,
     322,  1291,  1335,   353,   380,   272,  1225,  1350,  1024,  1352,
    1024,  1381,  1373,   341,  1226,  1358,   358,  1043,  1286,   359,
    1342,  1359,  1360,   994,   281,  1374,  1287,   282,  1012,   346,
    1382,  1361,   360,  1235,   283,  1383,  1236,  1025,  1384,  1025,
    1366,   284,  1367,  1237,   285,  1368,  1044,   286,  1370,  1343,
    1238,  1385,  1377,  1239,   287,  1378,  1240,   289,   347,   290,
    1398,   361,   291,  1241,   292,  1391,  1243,   293,  1244,   294,
    1396,  1245,   295,  1246,  1397,   274,  1247,   275,  1248,  1399,
     276,  1249,   277,   278,  1228,   279,  1229,   288,   296,  1230,
     297,  1231,  1232,  1404,  1233,   298,  1242,  1250,   308,  1251,
     309,   310,   323,  1412,  1252,   324,  1401,  1261,  1408,  1262,
    1263,  1257,   325,  1258,  1413,  1259,  1430,  1260,  1434,   326,
    1435,  1436,   327,  1448,  1447,   328,  1449,  1451,  1414,  1452,
    1453,  1454,   329,  1468,  1483,   330,  1465,   331,  1415,  1472,
     332,  1499,   333,  1438,  1439,   334,  1450,   335,  1479,  1500,
     336,  1503,  1504,  1470,  1471,  1501,  1505,  1521,  1525,  1533,
    1523,  1522,  1534,  1524,   855,  1531,  1532,  1536,  1537,   947,
     864,   866,  1213,   713,   707,  1071,  1211,  1369,  1276,  1273,
     337,  1272,   338,   354,   339,   355,   340,   356,  1321,   357,
    1304,   762,  1303,  1311,  1220,  1214,  1215,   727,  1271,  1253,
    1411,   392,  1217,  1281,   753,  1216,  1219,  1267,  1288,  1218,
     759,  1355,  1354,  1221,  1356,  1402,  1289,  1421,  1357,   736,
    1301,   745,  1282,  1268,  1416,  1340,  1300,   730,  1317,  1331,
    1341,  1302,  1290,  1330,  1329,  1069,  1222,  1464,  1484,  1223,
    1227,  1224,  1455,  1520,  1535,  1283,  1422,  1336,  1284,   865,
    1285,  1051,  1269,   771,  1342,  1437,  1349,  1497,   774,  1526,
       0,  1291,  1351,  1421,     0,  1457,     0,     0,     0,  1225,
    1458,     0,     0,     0,     0,  1423,     0,  1226,  1286,     0,
       0,     0,     0,  1343,     0,     0,  1287,     0,     0,     0,
       0,     0,  1422,  1457,  1459,     0,  1235,     0,  1458,  1236,
       0,     0,     0,     0,     0,     0,  1237,     0,     0,     0,
       0,     0,     0,  1238,     0,     0,  1239,  1511,     0,  1240,
       0,  1423,  1459,  1460,     0,     0,  1241,     0,     0,  1243,
       0,  1244,     0,     0,  1245,     0,  1246,     0,     0,  1247,
       0,  1248,     0,     0,  1249,     0,  1514,  1228,  1511,  1229,
       0,  1460,  1230,     0,  1231,  1232,     0,  1233,     0,  1242,
    1250,     0,  1251,     0,     0,     0,     0,  1252,     0,     0,
    1261,     0,  1262,  1263,  1257,  1515,  1258,  1514,  1259,     0,
    1260,     0,     0,     0,     0,     0,     0,     0,     0,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   253,     0,     0,     0,  1515,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
       0,     0,   130,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   132,   133,   134,     0,     0,     0,
       0,     0,   254,     0,   255,     0,     0,     0,     0,     0,
     136,   137,   256,   257,   258,   259,   260,   138,   139,   140,
       0,     0,     0,     0,     0,     0,   261,   262,   263,     0,
       0,     0,     0,   264,     0,   146,     0,     0,     0,     0,
       0,     0,     0,   265,     0,     0,     0,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     253,     0,     0,     0,     0,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,     0,
     130,   394,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   132,   133,   134,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   156,   157,   136,   137,
       0,   257,   258,     0,   260,   138,   139,   140,     0,     0,
       0,     0,     0,     0,   261,   262,   263,     0,     0,     0,
       0,   264,     0,     0,     0,     0,   163,     0,     0,     0,
       0,   265,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   156,   157,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   163
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   816,    78,    79,    73,    73,    74,    75,    76,    79,
      75,    73,    79,   816,   816,   781,   814,   808,  1112,  1112,
      72,    73,    74,    75,    76,  1112,    78,    79,  1112,    81,
    1112,  1112,   150,   151,    73,   680,     3,    73,    73,    73,
       5,     8,     7,  1498,     9,   226,     7,   144,   241,    72,
      73,    74,    75,    76,     7,    78,    79,    87,    81,  1498,
     241,    86,    16,    17,    18,    19,    20,    73,     3,    39,
      40,    41,    24,     8,  1529,    73,   207,   208,   209,   210,
     110,   111,   112,   113,   114,   115,   116,   150,   151,     3,
    1529,     3,     6,    10,    73,    74,     8,    73,    74,   204,
     205,   131,   132,   133,    73,    74,    13,    14,   138,   139,
       0,    73,    74,   244,    73,    74,   761,    73,    74,   102,
     103,   104,   105,   241,    73,    74,    24,    73,    74,    73,
      74,    29,    73,    74,    73,    74,     3,    73,    74,    73,
      74,     8,    73,    74,   241,    73,     3,    73,    24,     3,
      73,     8,    73,    73,     8,    73,     3,    73,    73,     6,
      73,   115,   116,   115,   116,    73,     3,     3,    73,     6,
      73,    73,     8,    74,    75,    74,    75,    74,    75,    74,
      75,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,   160,   161,   162,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,   241,    88,     3,    90,    91,     6,   115,   116,    95,
      96,    97,    25,    26,     7,   144,   145,    88,   147,   115,
     116,   183,   184,   185,    44,    45,    46,   115,   116,   115,
     116,   129,   130,   218,     7,    88,   221,   222,   223,   224,
       3,     3,     7,     6,   115,   116,     8,   153,   154,   155,
     156,   157,   158,     7,     7,   163,   164,   165,   166,    54,
      55,    56,    57,    58,    59,     3,   241,   242,   243,   244,
       8,  1375,  1375,   169,   170,   171,     7,   241,  1375,   241,
       7,  1375,     7,  1375,  1375,    88,    89,    90,    91,    92,
      93,    94,    87,    88,     3,   115,   116,     7,     6,     8,
       7,     7,   115,   116,   192,   193,   194,     3,     8,   115,
     116,     4,   115,   116,     3,     3,    88,  1118,     4,   190,
     115,   116,     3,    87,  1100,     3,     3,     8,   131,     4,
       8,     8,     4,   241,     4,  1160,     4,  1162,  1146,   134,
     135,   136,   137,   115,   116,   241,     4,  1160,  1160,  1162,
    1162,   115,   116,   241,   174,   241,     4,     3,   178,   179,
     180,   181,     8,   175,   176,   177,     3,   131,   188,   189,
     241,     8,     4,   186,   187,     4,     4,   141,   142,   143,
     144,   145,   146,   147,     3,     8,     4,     4,   241,     8,
     196,   197,   198,   199,   200,   201,   202,   203,    72,    73,
      74,    75,    76,    77,    78,     3,    80,    81,    82,    83,
       8,     4,     3,    87,   722,   723,   724,     8,     3,     3,
       3,   241,     4,     8,     8,     8,     4,   101,   241,   737,
     738,   739,   740,     4,   108,   241,     4,     4,   241,     4,
       4,   115,   116,   473,   474,   217,   241,   219,   220,     4,
     758,    47,    48,    49,    50,    51,    52,   131,   132,   133,
       4,   552,     3,     8,   138,   139,     3,     8,   559,   241,
       3,     8,     4,     3,     3,     8,     3,   241,     8,     8,
       3,     8,     4,   574,     3,     8,     3,   578,     3,     8,
       4,     8,     4,     8,   585,   574,   574,   559,     3,     3,
     578,     3,   574,     8,     8,   596,     8,   585,     4,     4,
     585,     4,   574,     4,     4,   606,   578,     4,   596,     4,
     606,     4,   613,   585,     4,   574,   559,   613,   574,   574,
     574,     4,     4,   613,   596,   626,   613,   211,   212,     4,
       4,   574,     4,     4,   606,   578,     4,     4,     4,     4,
       4,   613,   585,     4,     4,     8,     3,   241,   574,     4,
       4,     4,     8,   596,   626,     3,   574,   241,     4,     4,
       4,     4,     4,   606,     4,     4,     4,     4,     4,     4,
     613,     4,   242,   242,     4,   574,   242,   242,   574,   578,
     242,   242,   578,   626,   244,   574,   243,   242,   242,   578,
     243,   243,   574,   242,   242,   574,   578,   242,   574,   578,
     244,   242,   578,     4,   244,   574,     4,   244,   574,   578,
     574,     4,   578,   574,   578,   574,   242,   578,   574,   578,
     574,   244,   578,   574,   578,   244,   574,   578,   574,   243,
     242,   574,   242,   574,   574,   244,   574,     4,   574,   574,
       4,   574,     4,   242,     4,     4,   574,     4,     4,   574,
       4,   574,   574,     4,   244,   244,     4,   578,   244,   578,
       4,   578,     4,   578,   585,     4,   585,     4,   585,     4,
     585,     4,     4,     4,   242,   776,     4,     4,   779,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,     4,     4,     4,     4,     4,   244,   244,
     244,     4,     4,     4,     4,     4,   244,   779,   244,   243,
       4,   242,   242,   814,   815,   816,     4,     4,   819,   242,
       4,     4,   823,   244,     4,     4,     4,     4,     4,   242,
       4,   242,   242,   242,     4,   775,   779,     4,     4,     4,
       4,     3,   814,   815,   816,     4,   818,   819,    11,    12,
       4,     4,    15,     4,     4,   242,     4,     4,    21,    22,
      23,     4,     4,   244,   244,   244,   244,     4,     4,     4,
       4,   814,   815,   816,   244,   818,   819,     4,     4,     4,
     242,     4,     4,   242,   242,   206,     7,     7,     7,     7,
     242,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,     7,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,   241,     5,   241,   241,   241,
       5,     5,     5,   241,   241,    98,    99,   100,   101,     5,
       7,   241,     5,   106,     5,     5,   241,     5,     7,     5,
       5,     5,   115,   116,     7,     7,     7,     7,     7,   122,
     123,   124,   125,   126,   127,   128,     7,   241,   131,     5,
       7,     5,     5,     5,     5,   241,   241,   140,   241,     7,
     241,     7,     7,   241,     7,     7,   149,     7,   241,   152,
       7,   241,   241,     7,   241,   241,   159,     7,   241,     7,
     241,   241,     7,   241,   167,   168,     7,   241,     7,   172,
     173,   241,   241,   141,     4,   241,   241,   241,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   191,     4,
       6,     3,   195,     6,     3,     6,     6,     3,     6,     3,
     244,     6,     3,     6,     6,     3,     6,     4,   211,   212,
     213,   214,   215,   216,     4,     4,     4,     4,     4,     4,
       4,     4,   225,     4,     4,     4,     4,     4,     3,   241,
       4,     4,     4,     3,   242,     6,     3,     6,   241,     3,
       8,     6,     4,     4,     4,     4,   242,   244,     4,   244,
     242,     4,     4,   242,     4,     4,   242,   242,   242,     4,
       4,   242,  1103,   242,     4,  1106,     4,     4,  1109,   242,
    1106,  1112,   242,  1109,  1103,  1103,  1112,     4,   242,  1109,
       4,  1103,  1109,  1124,  1112,   242,  1127,   242,  1124,  1130,
    1112,  1103,   242,   242,  1106,   242,  1124,  1109,   242,  1127,
    1112,     4,  1124,   244,  1103,  1146,   242,  1103,  1103,  1103,
    1151,   242,  1124,  1112,   242,  1127,  1112,  1112,  1112,  1160,
    1103,  1162,     4,  1106,   244,  1124,  1109,     4,  1124,  1112,
    1124,  1172,   244,     4,  1146,  1176,  1172,  1103,   242,  1151,
    1181,  1124,     4,  1184,  1127,  1103,  1112,   244,  1160,     6,
    1162,     4,     8,  1181,  1112,   241,  1184,  1169,  1124,  1184,
    1172,   241,   241,  1146,  1103,     8,  1124,  1103,  1151,  1181,
       4,   241,  1184,  1112,  1103,     8,  1112,  1160,     3,  1162,
     241,  1103,   241,  1112,  1103,   241,  1169,  1103,   241,  1172,
    1112,     8,   241,  1112,  1103,   241,  1112,  1103,  1181,  1103,
       7,  1184,  1103,  1112,  1103,   241,  1112,  1103,  1112,  1103,
     241,  1112,  1103,  1112,   241,  1103,  1112,  1103,  1112,     5,
    1103,  1112,  1103,  1103,  1112,  1103,  1112,  1103,  1103,  1112,
    1103,  1112,  1112,     4,  1112,  1103,  1112,  1112,  1103,  1112,
    1103,  1103,  1181,     4,  1112,  1181,   241,  1112,   241,  1112,
    1112,  1112,  1181,  1112,     4,  1112,     7,  1112,     4,  1181,
     242,     4,  1181,     3,     6,  1181,     5,     4,   244,     4,
       4,     4,  1181,   182,     4,  1181,     7,  1181,   244,     5,
    1181,     6,  1181,   241,   241,  1181,   241,  1181,     7,     3,
    1181,     4,     4,   241,   241,   241,     4,     4,     4,     4,
     242,   244,     4,   242,   761,   241,   241,   241,   241,   807,
     776,   779,  1102,   559,   552,   862,  1097,  1209,  1122,  1118,
    1181,  1115,  1181,  1184,  1181,  1184,  1181,  1184,  1151,  1184,
    1132,   616,  1130,  1139,  1375,  1103,  1105,   574,  1114,  1375,
    1375,    77,  1108,  1384,   606,  1106,  1111,  1375,  1384,  1109,
     613,  1183,  1181,  1375,  1184,  1335,  1384,  1398,  1186,   585,
    1127,   596,  1384,  1375,  1384,  1406,  1125,   578,  1146,  1164,
    1406,  1129,  1384,  1162,  1160,   835,  1375,  1448,  1474,  1375,
    1375,  1375,  1444,  1500,  1529,  1384,  1398,  1169,  1384,   778,
    1384,   819,  1375,   626,  1406,  1406,  1173,  1477,   630,  1507,
      -1,  1384,  1176,  1444,    -1,  1446,    -1,    -1,    -1,  1375,
    1446,    -1,    -1,    -1,    -1,  1398,    -1,  1375,  1384,    -1,
      -1,    -1,    -1,  1406,    -1,    -1,  1384,    -1,    -1,    -1,
      -1,    -1,  1444,  1474,  1446,    -1,  1375,    -1,  1474,  1375,
      -1,    -1,    -1,    -1,    -1,    -1,  1375,    -1,    -1,    -1,
      -1,    -1,    -1,  1375,    -1,    -1,  1375,  1498,    -1,  1375,
      -1,  1444,  1474,  1446,    -1,    -1,  1375,    -1,    -1,  1375,
      -1,  1375,    -1,    -1,  1375,    -1,  1375,    -1,    -1,  1375,
      -1,  1375,    -1,    -1,  1375,    -1,  1498,  1375,  1529,  1375,
      -1,  1474,  1375,    -1,  1375,  1375,    -1,  1375,    -1,  1375,
    1375,    -1,  1375,    -1,    -1,    -1,    -1,  1375,    -1,    -1,
    1375,    -1,  1375,  1375,  1375,  1498,  1375,  1529,  1375,    -1,
    1375,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    -1,    -1,    -1,  1529,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      -1,    -1,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    99,   100,   101,    -1,    -1,    -1,
      -1,    -1,   107,    -1,   109,    -1,    -1,    -1,    -1,    -1,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
      -1,    -1,    -1,    -1,    -1,    -1,   131,   132,   133,    -1,
      -1,    -1,    -1,   138,    -1,   140,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   148,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    -1,
      87,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    99,   100,   101,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   211,   212,   115,   116,
      -1,   118,   119,    -1,   121,   122,   123,   124,    -1,    -1,
      -1,    -1,    -1,    -1,   131,   132,   133,    -1,    -1,    -1,
      -1,   138,    -1,    -1,    -1,    -1,   241,    -1,    -1,    -1,
      -1,   148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   211,   212,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   241
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
      66,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    98,    99,   100,   101,   106,   115,   116,   122,   123,
     124,   125,   126,   127,   128,   131,   140,   149,   152,   159,
     167,   168,   172,   173,   191,   195,   211,   212,   213,   214,
     215,   216,   225,   241,   276,   284,   285,   286,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   302,   303,   304,   305,   306,   309,   311,   313,   314,
     315,   318,   319,   320,   321,   322,   324,   326,   327,   328,
     329,   331,   332,   334,   336,   337,   338,   339,   351,   353,
     355,   398,   406,   412,   418,   420,   427,   441,   451,   475,
     476,   477,   480,   488,   514,   548,   550,   569,   599,   614,
     626,   627,   629,   679,   689,   708,   717,   741,    16,    17,
      18,    19,    20,   276,   343,   344,   345,   347,   348,   349,
     350,   548,   550,    67,   107,   109,   117,   118,   119,   120,
     121,   131,   132,   133,   138,   148,   276,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   303,   304,   305,   306,   309,   311,   313,   314,   315,
     318,   319,   320,   321,   322,   324,   326,   332,   334,   459,
     460,   461,   463,   465,   467,   469,   471,   473,   475,   476,
     477,   478,   479,   514,   535,   548,   550,   552,   569,   596,
     108,   139,   276,   303,   304,   305,   306,   309,   311,   313,
     315,   318,   319,   320,   321,   322,   324,   467,   469,   471,
     473,   514,   543,   544,   545,   547,   548,   550,   110,   111,
     112,   113,   114,   276,   467,   469,   471,   473,   514,   547,
     548,   550,   560,   561,   562,   564,   565,   567,   568,   131,
     141,   142,   143,   144,   145,   146,   147,   276,   514,   548,
     550,   577,   578,   579,   580,   582,   584,   586,   588,   590,
     592,   594,   488,    24,    88,    90,    91,    95,    96,    97,
     276,   372,   498,   499,   500,   501,   502,   503,   504,   506,
     508,   510,   511,   513,   548,   550,    89,    92,    93,    94,
     131,   276,   372,   502,   508,   522,   523,   524,   525,   526,
     528,   529,   530,   531,   532,   533,   548,   550,   150,   151,
     276,   435,   436,   437,   439,   196,   197,   198,   199,   200,
     201,   202,   203,   276,   548,   550,   693,   694,   695,   696,
     698,   699,   701,   702,   703,   706,    13,    14,   712,   713,
     714,   716,     6,     3,     4,     8,     3,   280,     3,     8,
     287,   709,   340,   352,   354,   356,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     330,     4,     4,     4,     4,     4,   307,   310,   312,     4,
       4,     4,     4,     4,     4,     4,   452,   489,   515,     4,
     333,   335,   316,   481,   549,   551,     4,     4,     4,   407,
     419,   413,   399,   600,   570,   428,   442,   615,     4,   421,
     628,   630,   680,   690,   323,   325,     4,     4,     4,   718,
     742,     4,     3,     8,   346,     4,     4,     4,     4,     3,
       8,     4,   536,   553,   462,   464,   466,     4,     4,   470,
     472,   474,   468,   597,     3,     8,   546,     4,     3,     8,
     563,     4,   566,     4,     4,     3,     8,   595,   581,   583,
     585,   587,   589,   591,   593,     8,     3,     8,   505,   373,
       4,   509,   507,   512,     4,     8,     3,   527,     4,     4,
       4,   534,     8,     3,   438,   440,     3,     8,     4,   697,
       4,   700,     4,     4,   704,   707,     3,     8,   715,     4,
       3,     8,   261,   261,   241,     4,     4,     4,     4,     4,
       4,     4,   242,   242,   242,   242,   242,   242,   242,   242,
     244,   243,   243,   243,   242,   242,     4,   242,   242,   244,
     244,   244,     4,     4,     4,   244,   244,   243,   242,   242,
     242,   244,     4,     4,     4,   242,     4,     4,     4,     4,
       4,     4,   244,   244,   244,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   242,     4,     4,     4,     4,     4,
       4,     4,   244,   244,   244,     4,     4,   285,     4,   244,
     244,   242,   242,   344,   243,     4,     4,     4,     4,     4,
     242,   244,     4,     4,     4,     4,     4,   460,     4,   242,
     544,     4,   242,     4,   242,   242,   561,     4,     4,     4,
       4,     4,     4,     4,     4,   579,     4,     4,   242,     4,
       4,     4,   244,   500,     4,   244,   244,   244,     4,   524,
       4,     4,   436,   244,     4,   242,     4,   242,   242,     4,
       4,   694,     4,   242,   713,     4,     7,   241,     7,     7,
       7,     7,     5,   241,   207,   208,   209,   210,   244,   308,
     241,   241,     5,     5,     5,   241,   241,   102,   103,   104,
     105,   317,     5,   263,   265,   241,     5,     5,     5,     7,
       5,     5,     5,     7,     7,     7,     7,     5,     7,     7,
     241,   241,     5,     7,     5,   272,     5,     5,   241,   241,
     241,   272,   272,   272,   241,     7,   241,   241,   241,   272,
     272,   272,   272,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   272,   241,   265,   241,   241,   204,   205,
     705,   206,     5,   261,   284,   712,   343,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,   276,   361,   362,   363,   365,   367,
     369,   371,   372,   374,   375,   376,   377,   378,   379,   380,
     381,   382,   385,   386,   387,   388,   390,   392,   394,   396,
     361,     7,   357,   358,   359,     7,   453,   454,   455,     7,
     492,   493,   494,     7,   516,   517,   518,     7,   482,   483,
     484,   144,   241,   408,   409,   410,   411,   270,   145,   147,
     410,   414,   415,   416,   417,   129,   130,   400,   401,   402,
     404,     7,   601,   602,     7,   571,   572,   573,     7,   429,
     430,   431,   153,   154,   155,   156,   157,   158,   443,   444,
     445,   446,   447,   448,   449,   450,    24,   163,   164,   165,
     166,   276,   374,   548,   550,   616,   617,   618,   621,   622,
     624,   625,   169,   170,   171,   276,   422,   423,   424,   425,
     426,   548,   550,   174,   178,   179,   180,   181,   188,   189,
     276,   388,   390,   392,   548,   550,   635,   636,   637,   640,
     642,   644,   645,   646,   656,     7,   631,   632,   633,   192,
     193,   194,   241,   548,   550,   681,   682,   683,   684,   686,
     687,   693,     7,   719,   720,   226,   276,   743,   744,   745,
     273,     7,   537,   538,   539,     7,   554,   555,   556,   580,
     598,   357,     8,     8,     8,   364,   366,   368,   370,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   383,
       4,     4,   389,   391,   393,   395,   397,     3,     8,     8,
     360,     6,     3,   456,     6,     3,   495,     6,     3,   519,
       6,     3,   485,     6,     3,     3,     6,     6,     3,     6,
     403,   405,     3,     8,   603,     3,     6,   574,     6,     3,
     432,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,   619,   623,     4,     4,     4,     3,     8,     4,     4,
       4,     3,     8,   638,   641,   643,     4,   657,     4,   647,
       3,     8,   634,     6,     3,     4,   685,     4,   688,     3,
       8,     8,   721,     3,     6,     4,     3,     8,   241,   274,
     275,   540,     6,     3,   557,     6,     3,     8,     6,     4,
       4,     4,     4,   242,   244,   242,   244,   242,   242,   242,
     242,   242,   242,     4,   244,   242,     4,     4,     4,     4,
       4,   362,   361,   359,   459,   455,   498,   494,   522,   518,
     276,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   303,   304,   305,   306,   309,
     311,   313,   314,   315,   318,   319,   320,   321,   322,   324,
     326,   332,   334,   372,   451,   463,   465,   467,   469,   471,
     473,   475,   476,   477,   479,   486,   487,   514,   548,   550,
     596,   484,   409,   415,     4,     4,   401,   134,   135,   136,
     137,   276,   288,   289,   290,   291,   292,   293,   372,   514,
     548,   550,   604,   605,   606,   607,   608,   610,   612,   613,
     602,   577,   573,   435,   431,   242,   242,   242,   242,   242,
     242,   444,     4,     4,   242,   242,   242,   617,   244,   242,
     242,   423,     4,     4,     4,   242,     4,   244,     4,   636,
     635,   633,   244,     4,   242,     4,   682,   217,   219,   220,
     276,   372,   548,   550,   722,   723,   724,   725,   727,   720,
     244,   744,     6,     3,   543,   539,   560,   556,   241,   241,
     241,   241,    39,    40,    41,   384,   241,   241,   241,   394,
     241,     8,     8,     8,     8,     3,     8,   241,   241,   609,
     611,     4,     4,     8,     3,     8,     8,   160,   161,   162,
     620,   241,   175,   176,   177,   639,   241,   241,     7,     5,
       8,   241,   261,   728,     4,   726,     3,     8,   241,     8,
       8,   487,     4,     4,   244,   244,   606,    24,   183,   184,
     185,   276,   548,   550,   658,   659,   660,   663,   665,   667,
       7,   648,   649,   650,     4,   242,     4,   723,   241,   241,
     661,   664,   666,   668,     3,     8,   651,     6,     3,     5,
     241,     4,     4,     4,     4,   659,   190,   276,   372,   548,
     550,   652,   653,   654,   650,     7,   729,   730,   182,   662,
     241,   241,     5,   655,     3,     8,   731,     3,     6,     7,
     669,   670,   671,     4,   653,   218,   221,   222,   223,   224,
     732,   733,   734,   736,   737,   738,   739,   730,   672,     6,
       3,   241,   735,     4,     4,     4,   740,     3,     8,   186,
     187,   276,   365,   367,   548,   550,   673,   674,   675,   677,
     671,     4,   244,   242,   242,     4,   733,   676,   678,     3,
       8,   241,   241,     4,     4,   674,   241,   241
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
     285,   285,   285,   285,   287,   286,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   307,   306,   308,   308,   308,   308,
     308,   310,   309,   312,   311,   313,   314,   316,   315,   317,
     317,   317,   317,   318,   319,   320,   321,   323,   322,   325,
     324,   326,   327,   328,   330,   329,   331,   333,   332,   335,
     334,   336,   337,   338,   340,   339,   342,   341,   343,   343,
     343,   344,   344,   344,   344,   344,   344,   344,   344,   346,
     345,   347,   348,   349,   350,   352,   351,   354,   353,   356,
     355,   357,   357,   358,   358,   358,   360,   359,   361,   361,
     361,   362,   362,   362,   362,   362,   362,   362,   362,   362,
     362,   362,   362,   362,   362,   362,   362,   362,   362,   362,
     362,   362,   362,   362,   362,   364,   363,   366,   365,   368,
     367,   370,   369,   371,   373,   372,   374,   375,   376,   377,
     378,   379,   380,   381,   383,   382,   384,   384,   384,   385,
     386,   387,   389,   388,   391,   390,   393,   392,   395,   394,
     394,   394,   394,   394,   394,   397,   396,   399,   398,   400,
     400,   400,   401,   401,   403,   402,   405,   404,   407,   406,
     408,   408,   408,   409,   409,   410,   411,   413,   412,   414,
     414,   414,   415,   415,   415,   416,   417,   419,   418,   421,
     420,   422,   422,   422,   423,   423,   423,   423,   423,   423,
     424,   425,   426,   428,   427,   429,   429,   430,   430,   430,
     432,   431,   434,   433,   435,   435,   435,   435,   436,   436,
     438,   437,   440,   439,   442,   441,   443,   443,   443,   444,
     444,   444,   444,   444,   444,   445,   446,   447,   448,   449,
     450,   452,   451,   453,   453,   454,   454,   454,   456,   455,
     458,   457,   459,   459,   459,   460,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   462,   461,   464,
     463,   466,   465,   468,   467,   470,   469,   472,   471,   474,
     473,   475,   476,   477,   478,   479,   481,   480,   482,   482,
     483,   483,   483,   485,   484,   486,   486,   486,   487,   487,
     487,   487,   487,   487,   487,   487,   487,   487,   487,   487,
     487,   487,   487,   487,   487,   487,   487,   487,   487,   487,
     487,   487,   487,   487,   487,   487,   487,   487,   487,   487,
     487,   487,   487,   487,   487,   487,   487,   487,   487,   487,
     487,   487,   487,   487,   487,   487,   487,   489,   488,   491,
     490,   492,   492,   493,   493,   493,   495,   494,   497,   496,
     498,   498,   499,   499,   499,   500,   500,   500,   500,   500,
     500,   500,   500,   500,   500,   501,   502,   503,   505,   504,
     507,   506,   509,   508,   510,   512,   511,   513,   515,   514,
     516,   516,   517,   517,   517,   519,   518,   521,   520,   522,
     522,   523,   523,   523,   524,   524,   524,   524,   524,   524,
     524,   524,   524,   524,   524,   525,   527,   526,   528,   529,
     530,   531,   532,   534,   533,   536,   535,   537,   537,   538,
     538,   538,   540,   539,   542,   541,   543,   543,   543,   544,
     544,   544,   544,   544,   544,   544,   544,   544,   544,   544,
     544,   544,   544,   544,   544,   544,   544,   544,   544,   544,
     544,   544,   544,   546,   545,   547,   549,   548,   551,   550,
     553,   552,   554,   554,   555,   555,   555,   557,   556,   559,
     558,   560,   560,   560,   561,   561,   561,   561,   561,   561,
     561,   561,   561,   561,   561,   561,   561,   561,   563,   562,
     564,   566,   565,   567,   568,   570,   569,   571,   571,   572,
     572,   572,   574,   573,   576,   575,   577,   577,   578,   578,
     578,   579,   579,   579,   579,   579,   579,   579,   579,   579,
     579,   579,   579,   581,   580,   583,   582,   585,   584,   587,
     586,   589,   588,   591,   590,   593,   592,   595,   594,   597,
     596,   598,   600,   599,   601,   601,   601,   603,   602,   604,
     604,   605,   605,   605,   606,   606,   606,   606,   606,   606,
     606,   606,   606,   606,   606,   606,   606,   606,   606,   607,
     609,   608,   611,   610,   612,   613,   615,   614,   616,   616,
     616,   617,   617,   617,   617,   617,   617,   617,   617,   617,
     619,   618,   620,   620,   620,   621,   623,   622,   624,   625,
     626,   628,   627,   630,   629,   631,   631,   632,   632,   632,
     634,   633,   635,   635,   635,   636,   636,   636,   636,   636,
     636,   636,   636,   636,   636,   636,   636,   636,   638,   637,
     639,   639,   639,   641,   640,   643,   642,   644,   645,   647,
     646,   648,   648,   649,   649,   649,   651,   650,   652,   652,
     652,   653,   653,   653,   653,   653,   655,   654,   657,   656,
     658,   658,   658,   659,   659,   659,   659,   659,   659,   659,
     661,   660,   662,   664,   663,   666,   665,   668,   667,   669,
     669,   670,   670,   670,   672,   671,   673,   673,   673,   674,
     674,   674,   674,   674,   674,   674,   676,   675,   678,   677,
     680,   679,   681,   681,   681,   682,   682,   682,   682,   682,
     682,   683,   685,   684,   686,   688,   687,   690,   689,   692,
     691,   693,   693,   693,   694,   694,   694,   694,   694,   694,
     694,   694,   694,   694,   694,   695,   697,   696,   698,   700,
     699,   701,   702,   704,   703,   705,   705,   707,   706,   709,
     708,   711,   710,   712,   712,   712,   713,   713,   715,   714,
     716,   718,   717,   719,   719,   719,   721,   720,   722,   722,
     722,   723,   723,   723,   723,   723,   723,   723,   724,   726,
     725,   728,   727,   729,   729,   729,   731,   730,   732,   732,
     732,   733,   733,   733,   733,   733,   735,   734,   736,   737,
     738,   740,   739,   742,   741,   743,   743,   743,   744,   744,
     745
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
       3,     3,     3,     3,     0,     4,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     3,     3,     0,     4,     1,
       1,     1,     1,     3,     3,     3,     3,     0,     4,     0,
       4,     3,     3,     3,     0,     4,     3,     0,     4,     0,
       4,     3,     3,     3,     0,     6,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     3,     3,     3,     0,     6,     0,     6,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     1,     1,     1,     3,
       3,     3,     0,     4,     0,     4,     0,     4,     0,     4,
       1,     1,     1,     1,     1,     0,     4,     0,     6,     1,
       3,     2,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     0,     6,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     1,     3,     2,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
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
       1,     1,     1,     1,     1,     1,     1,     0,     6,     0,
       4,     0,     1,     1,     3,     2,     0,     4,     0,     4,
       0,     1,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     0,     4,
       0,     4,     0,     4,     1,     0,     4,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     0,
       1,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       3,     3,     3,     0,     4,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     0,     4,     0,     4,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     4,     3,     3,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     0,     1,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     0,     6,     1,     3,     2,     0,     4,     0,
       1,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     3,     3,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     3,     0,     4,     3,     3,
       3,     0,     6,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     0,     4,     0,     4,     3,     3,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     0,     4,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     0,     4,     0,     4,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     3,     0,     4,     0,     6,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     3,     0,
       4,     3,     3,     0,     4,     1,     1,     0,     4,     0,
       6,     0,     4,     1,     3,     2,     1,     1,     0,     6,
       3,     0,     6,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     6,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     0,     4,     3,     3,
       3,     0,     4,     0,     6,     1,     3,     2,     1,     1,
       3
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
     596,   597,   598,   599,   602,   602,   612,   618,   624,   630,
     636,   642,   648,   654,   660,   666,   672,   678,   684,   690,
     696,   702,   708,   714,   720,   720,   729,   732,   735,   738,
     741,   747,   747,   756,   756,   765,   774,   784,   784,   793,
     796,   799,   802,   807,   813,   819,   825,   831,   831,   840,
     840,   849,   855,   861,   867,   867,   876,   882,   882,   891,
     891,   900,   906,   912,   918,   918,   930,   930,   939,   940,
     941,   946,   947,   948,   949,   950,   951,   952,   953,   956,
     956,   967,   973,   979,   985,   991,   991,  1004,  1004,  1017,
    1017,  1028,  1029,  1032,  1033,  1034,  1039,  1039,  1049,  1050,
    1051,  1056,  1057,  1058,  1059,  1060,  1061,  1062,  1063,  1064,
    1065,  1066,  1067,  1068,  1069,  1070,  1071,  1072,  1073,  1074,
    1075,  1076,  1077,  1078,  1079,  1082,  1082,  1091,  1091,  1100,
    1100,  1109,  1109,  1118,  1124,  1124,  1133,  1139,  1145,  1151,
    1157,  1163,  1169,  1175,  1181,  1181,  1189,  1190,  1191,  1194,
    1200,  1206,  1212,  1212,  1221,  1221,  1230,  1230,  1239,  1239,
    1247,  1250,  1253,  1256,  1259,  1264,  1264,  1273,  1273,  1284,
    1285,  1286,  1291,  1292,  1295,  1295,  1314,  1314,  1332,  1332,
    1343,  1344,  1345,  1350,  1351,  1354,  1359,  1364,  1364,  1375,
    1376,  1377,  1382,  1383,  1384,  1387,  1392,  1399,  1399,  1412,
    1412,  1425,  1426,  1427,  1432,  1433,  1434,  1435,  1436,  1437,
    1440,  1446,  1452,  1458,  1458,  1469,  1470,  1473,  1474,  1475,
    1480,  1480,  1490,  1490,  1500,  1501,  1502,  1505,  1508,  1509,
    1512,  1512,  1521,  1521,  1530,  1530,  1542,  1543,  1544,  1549,
    1550,  1551,  1552,  1553,  1554,  1557,  1563,  1569,  1575,  1581,
    1587,  1596,  1596,  1610,  1611,  1614,  1615,  1616,  1625,  1625,
    1651,  1651,  1662,  1663,  1664,  1670,  1671,  1672,  1673,  1674,
    1675,  1676,  1677,  1678,  1679,  1680,  1681,  1682,  1683,  1684,
    1685,  1686,  1687,  1688,  1689,  1690,  1691,  1692,  1693,  1694,
    1695,  1696,  1697,  1698,  1699,  1700,  1701,  1702,  1703,  1704,
    1705,  1706,  1707,  1708,  1709,  1710,  1711,  1712,  1713,  1714,
    1715,  1716,  1717,  1718,  1719,  1720,  1721,  1724,  1724,  1733,
    1733,  1742,  1742,  1751,  1751,  1761,  1761,  1773,  1773,  1784,
    1784,  1795,  1801,  1807,  1813,  1819,  1827,  1827,  1839,  1840,
    1844,  1845,  1846,  1851,  1851,  1859,  1860,  1861,  1866,  1867,
    1868,  1869,  1870,  1871,  1872,  1873,  1874,  1875,  1876,  1877,
    1878,  1879,  1880,  1881,  1882,  1883,  1884,  1885,  1886,  1887,
    1888,  1889,  1890,  1891,  1892,  1893,  1894,  1895,  1896,  1897,
    1898,  1899,  1900,  1901,  1902,  1903,  1904,  1905,  1906,  1907,
    1908,  1909,  1910,  1911,  1912,  1913,  1914,  1921,  1921,  1935,
    1935,  1944,  1945,  1948,  1949,  1950,  1957,  1957,  1972,  1972,
    1986,  1987,  1990,  1991,  1992,  1997,  1998,  1999,  2000,  2001,
    2002,  2003,  2004,  2005,  2006,  2009,  2011,  2017,  2019,  2019,
    2028,  2028,  2037,  2037,  2046,  2048,  2048,  2057,  2067,  2067,
    2080,  2081,  2086,  2087,  2088,  2095,  2095,  2107,  2107,  2119,
    2120,  2125,  2126,  2127,  2134,  2135,  2136,  2137,  2138,  2139,
    2140,  2141,  2142,  2143,  2144,  2147,  2149,  2149,  2158,  2160,
    2162,  2168,  2174,  2180,  2180,  2194,  2194,  2207,  2208,  2211,
    2212,  2213,  2218,  2218,  2228,  2228,  2238,  2239,  2240,  2245,
    2246,  2247,  2248,  2249,  2250,  2251,  2252,  2253,  2254,  2255,
    2256,  2257,  2258,  2259,  2260,  2261,  2262,  2263,  2264,  2265,
    2266,  2267,  2268,  2271,  2271,  2280,  2286,  2286,  2311,  2311,
    2341,  2341,  2354,  2355,  2358,  2359,  2360,  2365,  2365,  2377,
    2377,  2389,  2390,  2391,  2396,  2397,  2398,  2399,  2400,  2401,
    2402,  2403,  2404,  2405,  2406,  2407,  2408,  2409,  2412,  2412,
    2421,  2427,  2427,  2436,  2442,  2451,  2451,  2462,  2463,  2466,
    2467,  2468,  2473,  2473,  2482,  2482,  2491,  2492,  2495,  2496,
    2497,  2503,  2504,  2505,  2506,  2507,  2508,  2509,  2510,  2511,
    2512,  2513,  2514,  2517,  2517,  2528,  2528,  2539,  2539,  2550,
    2550,  2559,  2559,  2568,  2568,  2577,  2577,  2586,  2586,  2600,
    2600,  2611,  2617,  2617,  2628,  2629,  2630,  2635,  2635,  2645,
    2646,  2649,  2650,  2651,  2656,  2657,  2658,  2659,  2660,  2661,
    2662,  2663,  2664,  2665,  2666,  2667,  2668,  2669,  2670,  2673,
    2675,  2675,  2684,  2684,  2694,  2700,  2709,  2709,  2722,  2723,
    2724,  2729,  2730,  2731,  2732,  2733,  2734,  2735,  2736,  2737,
    2740,  2740,  2748,  2749,  2750,  2753,  2759,  2759,  2768,  2774,
    2782,  2790,  2790,  2802,  2802,  2814,  2815,  2818,  2819,  2820,
    2825,  2825,  2833,  2834,  2835,  2840,  2841,  2842,  2843,  2844,
    2845,  2846,  2847,  2848,  2849,  2850,  2851,  2852,  2855,  2855,
    2864,  2865,  2866,  2869,  2869,  2879,  2879,  2889,  2895,  2901,
    2901,  2912,  2913,  2916,  2917,  2918,  2923,  2923,  2931,  2932,
    2933,  2938,  2939,  2940,  2941,  2942,  2945,  2945,  2956,  2956,
    2969,  2970,  2971,  2976,  2977,  2978,  2979,  2980,  2981,  2982,
    2985,  2985,  2993,  2996,  2996,  3005,  3005,  3014,  3014,  3025,
    3026,  3029,  3030,  3031,  3036,  3036,  3044,  3045,  3046,  3051,
    3052,  3053,  3054,  3055,  3056,  3057,  3060,  3060,  3069,  3069,
    3080,  3080,  3093,  3094,  3095,  3100,  3101,  3102,  3103,  3104,
    3105,  3108,  3114,  3114,  3123,  3129,  3129,  3139,  3139,  3152,
    3152,  3162,  3163,  3164,  3169,  3170,  3171,  3172,  3173,  3174,
    3175,  3176,  3177,  3178,  3179,  3182,  3188,  3188,  3197,  3203,
    3203,  3212,  3218,  3224,  3224,  3233,  3234,  3237,  3237,  3248,
    3248,  3260,  3260,  3270,  3271,  3272,  3278,  3279,  3282,  3282,
    3293,  3301,  3301,  3314,  3315,  3316,  3322,  3322,  3330,  3331,
    3332,  3337,  3338,  3339,  3340,  3341,  3342,  3343,  3346,  3352,
    3352,  3361,  3361,  3372,  3373,  3374,  3379,  3379,  3387,  3388,
    3389,  3394,  3395,  3396,  3397,  3398,  3401,  3401,  3410,  3416,
    3422,  3428,  3428,  3437,  3437,  3448,  3449,  3450,  3455,  3456,
    3459
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

#line 3465 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
