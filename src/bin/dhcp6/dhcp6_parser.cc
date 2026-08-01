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

  case 187: // ddns_ttl_max: "ddns-ttl-max" ":" "integer"
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

  case 205: // allow_address_registration: "allow-address-registration" ":" "boolean"
#line 919 "dhcp6_parser.yy"
                                                                     {
    ctx.unique("allow-address-registration", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allow-address-registration", first);
}
#line 1729 "dhcp6_parser.cc"
    break;

  case 206: // $@31: %empty
#line 925 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1741 "dhcp6_parser.cc"
    break;

  case 207: // interfaces_config: "interfaces-config" $@31 ":" "{" interfaces_config_params "}"
#line 931 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1751 "dhcp6_parser.cc"
    break;

  case 208: // $@32: %empty
#line 937 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1761 "dhcp6_parser.cc"
    break;

  case 209: // sub_interfaces6: "{" $@32 interfaces_config_params "}"
#line 941 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1770 "dhcp6_parser.cc"
    break;

  case 212: // interfaces_config_params: interfaces_config_params ","
#line 948 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1778 "dhcp6_parser.cc"
    break;

  case 221: // $@33: %empty
#line 963 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1790 "dhcp6_parser.cc"
    break;

  case 222: // interfaces_list: "interfaces" $@33 ":" list_strings
#line 969 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1799 "dhcp6_parser.cc"
    break;

  case 223: // re_detect: "re-detect" ":" "boolean"
#line 974 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1809 "dhcp6_parser.cc"
    break;

  case 224: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 980 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1819 "dhcp6_parser.cc"
    break;

  case 225: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 986 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1829 "dhcp6_parser.cc"
    break;

  case 226: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 992 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1839 "dhcp6_parser.cc"
    break;

  case 227: // $@34: %empty
#line 998 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1851 "dhcp6_parser.cc"
    break;

  case 228: // lease_database: "lease-database" $@34 ":" "{" database_map_params "}"
#line 1004 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1862 "dhcp6_parser.cc"
    break;

  case 229: // $@35: %empty
#line 1011 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1874 "dhcp6_parser.cc"
    break;

  case 230: // hosts_database: "hosts-database" $@35 ":" "{" database_map_params "}"
#line 1017 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1885 "dhcp6_parser.cc"
    break;

  case 231: // $@36: %empty
#line 1024 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1897 "dhcp6_parser.cc"
    break;

  case 232: // hosts_databases: "hosts-databases" $@36 ":" "[" database_list "]"
#line 1030 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1906 "dhcp6_parser.cc"
    break;

  case 237: // not_empty_database_list: not_empty_database_list ","
#line 1041 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1914 "dhcp6_parser.cc"
    break;

  case 238: // $@37: %empty
#line 1046 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1924 "dhcp6_parser.cc"
    break;

  case 239: // database: "{" $@37 database_map_params "}"
#line 1050 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1934 "dhcp6_parser.cc"
    break;

  case 242: // database_map_params: database_map_params ","
#line 1058 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1942 "dhcp6_parser.cc"
    break;

  case 267: // $@38: %empty
#line 1089 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1951 "dhcp6_parser.cc"
    break;

  case 268: // database_type: "type" $@38 ":" "constant string"
#line 1092 "dhcp6_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 1961 "dhcp6_parser.cc"
    break;

  case 269: // $@39: %empty
#line 1098 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1970 "dhcp6_parser.cc"
    break;

  case 270: // user: "user" $@39 ":" "constant string"
#line 1101 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1980 "dhcp6_parser.cc"
    break;

  case 271: // $@40: %empty
#line 1107 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1989 "dhcp6_parser.cc"
    break;

  case 272: // password: "password" $@40 ":" "constant string"
#line 1110 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1999 "dhcp6_parser.cc"
    break;

  case 273: // $@41: %empty
#line 1116 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2008 "dhcp6_parser.cc"
    break;

  case 274: // host: "host" $@41 ":" "constant string"
#line 1119 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2018 "dhcp6_parser.cc"
    break;

  case 275: // port: "port" ":" "integer"
#line 1125 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2028 "dhcp6_parser.cc"
    break;

  case 276: // $@42: %empty
#line 1131 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2037 "dhcp6_parser.cc"
    break;

  case 277: // name: "name" $@42 ":" "constant string"
#line 1134 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2047 "dhcp6_parser.cc"
    break;

  case 278: // persist: "persist" ":" "boolean"
#line 1140 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2057 "dhcp6_parser.cc"
    break;

  case 279: // lfc_interval: "lfc-interval" ":" "integer"
#line 1146 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2067 "dhcp6_parser.cc"
    break;

  case 280: // readonly: "readonly" ":" "boolean"
#line 1152 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2077 "dhcp6_parser.cc"
    break;

  case 281: // connect_timeout: "connect-timeout" ":" "integer"
#line 1158 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2087 "dhcp6_parser.cc"
    break;

  case 282: // read_timeout: "read-timeout" ":" "integer"
#line 1164 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2097 "dhcp6_parser.cc"
    break;

  case 283: // write_timeout: "write-timeout" ":" "integer"
#line 1170 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2107 "dhcp6_parser.cc"
    break;

  case 284: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1176 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2117 "dhcp6_parser.cc"
    break;

  case 285: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1182 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2127 "dhcp6_parser.cc"
    break;

  case 286: // $@43: %empty
#line 1188 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2136 "dhcp6_parser.cc"
    break;

  case 287: // on_fail: "on-fail" $@43 ":" on_fail_mode
#line 1191 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2145 "dhcp6_parser.cc"
    break;

  case 288: // on_fail_mode: "stop-retry-exit"
#line 1196 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2151 "dhcp6_parser.cc"
    break;

  case 289: // on_fail_mode: "serve-retry-exit"
#line 1197 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2157 "dhcp6_parser.cc"
    break;

  case 290: // on_fail_mode: "serve-retry-continue"
#line 1198 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2163 "dhcp6_parser.cc"
    break;

  case 291: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1201 "dhcp6_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2173 "dhcp6_parser.cc"
    break;

  case 292: // max_row_errors: "max-row-errors" ":" "integer"
#line 1207 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2183 "dhcp6_parser.cc"
    break;

  case 293: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1213 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2193 "dhcp6_parser.cc"
    break;

  case 294: // $@44: %empty
#line 1219 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2202 "dhcp6_parser.cc"
    break;

  case 295: // trust_anchor: "trust-anchor" $@44 ":" "constant string"
#line 1222 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2212 "dhcp6_parser.cc"
    break;

  case 296: // $@45: %empty
#line 1228 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2221 "dhcp6_parser.cc"
    break;

  case 297: // cert_file: "cert-file" $@45 ":" "constant string"
#line 1231 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2231 "dhcp6_parser.cc"
    break;

  case 298: // $@46: %empty
#line 1237 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2240 "dhcp6_parser.cc"
    break;

  case 299: // key_file: "key-file" $@46 ":" "constant string"
#line 1240 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2250 "dhcp6_parser.cc"
    break;

  case 300: // $@47: %empty
#line 1246 "dhcp6_parser.yy"
                   {
    ctx.unique("ssl-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SSL_MODE);
}
#line 2259 "dhcp6_parser.cc"
    break;

  case 301: // ssl_mode: "ssl-mode" $@47 ":" ssl_mode
#line 1249 "dhcp6_parser.yy"
                 {
    ctx.stack_.back()->set("ssl-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2268 "dhcp6_parser.cc"
    break;

  case 302: // ssl_mode: "disable"
#line 1254 "dhcp6_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disable", ctx.loc2pos(yystack_[0].location)));
            }
#line 2276 "dhcp6_parser.cc"
    break;

  case 303: // ssl_mode: "prefer"
#line 1257 "dhcp6_parser.yy"
                 {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("prefer", ctx.loc2pos(yystack_[0].location)));
            }
#line 2284 "dhcp6_parser.cc"
    break;

  case 304: // ssl_mode: "require"
#line 1260 "dhcp6_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("require", ctx.loc2pos(yystack_[0].location)));
            }
#line 2292 "dhcp6_parser.cc"
    break;

  case 305: // ssl_mode: "verify-ca"
#line 1263 "dhcp6_parser.yy"
                    {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-ca", ctx.loc2pos(yystack_[0].location)));
            }
#line 2300 "dhcp6_parser.cc"
    break;

  case 306: // ssl_mode: "verify-full"
#line 1266 "dhcp6_parser.yy"
                      {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-full", ctx.loc2pos(yystack_[0].location)));
            }
#line 2308 "dhcp6_parser.cc"
    break;

  case 307: // $@48: %empty
#line 1271 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2317 "dhcp6_parser.cc"
    break;

  case 308: // cipher_list: "cipher-list" $@48 ":" "constant string"
#line 1274 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2327 "dhcp6_parser.cc"
    break;

  case 309: // $@49: %empty
#line 1280 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2339 "dhcp6_parser.cc"
    break;

  case 310: // sanity_checks: "sanity-checks" $@49 ":" "{" sanity_checks_params "}"
#line 1286 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2348 "dhcp6_parser.cc"
    break;

  case 313: // sanity_checks_params: sanity_checks_params ","
#line 1293 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2356 "dhcp6_parser.cc"
    break;

  case 316: // $@50: %empty
#line 1302 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2365 "dhcp6_parser.cc"
    break;

  case 317: // lease_checks: "lease-checks" $@50 ":" "constant string"
#line 1305 "dhcp6_parser.yy"
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
#line 2385 "dhcp6_parser.cc"
    break;

  case 318: // $@51: %empty
#line 1321 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2394 "dhcp6_parser.cc"
    break;

  case 319: // extended_info_checks: "extended-info-checks" $@51 ":" "constant string"
#line 1324 "dhcp6_parser.yy"
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
#line 2413 "dhcp6_parser.cc"
    break;

  case 320: // $@52: %empty
#line 1339 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2425 "dhcp6_parser.cc"
    break;

  case 321: // mac_sources: "mac-sources" $@52 ":" "[" mac_sources_list "]"
#line 1345 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2434 "dhcp6_parser.cc"
    break;

  case 324: // mac_sources_list: mac_sources_list ","
#line 1352 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2442 "dhcp6_parser.cc"
    break;

  case 327: // duid_id: "duid"
#line 1361 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2451 "dhcp6_parser.cc"
    break;

  case 328: // string_id: "constant string"
#line 1366 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2460 "dhcp6_parser.cc"
    break;

  case 329: // $@53: %empty
#line 1371 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2472 "dhcp6_parser.cc"
    break;

  case 330: // host_reservation_identifiers: "host-reservation-identifiers" $@53 ":" "[" host_reservation_identifiers_list "]"
#line 1377 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2481 "dhcp6_parser.cc"
    break;

  case 333: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1384 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2489 "dhcp6_parser.cc"
    break;

  case 337: // hw_address_id: "hw-address"
#line 1394 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2498 "dhcp6_parser.cc"
    break;

  case 338: // flex_id: "flex-id"
#line 1399 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2507 "dhcp6_parser.cc"
    break;

  case 339: // $@54: %empty
#line 1406 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2519 "dhcp6_parser.cc"
    break;

  case 340: // relay_supplied_options: "relay-supplied-options" $@54 ":" "[" list_content "]"
#line 1412 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2528 "dhcp6_parser.cc"
    break;

  case 341: // $@55: %empty
#line 1419 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2540 "dhcp6_parser.cc"
    break;

  case 342: // dhcp_multi_threading: "multi-threading" $@55 ":" "{" multi_threading_params "}"
#line 1425 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2551 "dhcp6_parser.cc"
    break;

  case 345: // multi_threading_params: multi_threading_params ","
#line 1434 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2559 "dhcp6_parser.cc"
    break;

  case 352: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1447 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2569 "dhcp6_parser.cc"
    break;

  case 353: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1453 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2579 "dhcp6_parser.cc"
    break;

  case 354: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1459 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2589 "dhcp6_parser.cc"
    break;

  case 355: // $@56: %empty
#line 1465 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2601 "dhcp6_parser.cc"
    break;

  case 356: // hooks_libraries: "hooks-libraries" $@56 ":" "[" hooks_libraries_list "]"
#line 1471 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2610 "dhcp6_parser.cc"
    break;

  case 361: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1482 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2618 "dhcp6_parser.cc"
    break;

  case 362: // $@57: %empty
#line 1487 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2628 "dhcp6_parser.cc"
    break;

  case 363: // hooks_library: "{" $@57 hooks_params "}"
#line 1491 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2638 "dhcp6_parser.cc"
    break;

  case 364: // $@58: %empty
#line 1497 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2648 "dhcp6_parser.cc"
    break;

  case 365: // sub_hooks_library: "{" $@58 hooks_params "}"
#line 1501 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2658 "dhcp6_parser.cc"
    break;

  case 368: // hooks_params: hooks_params ","
#line 1509 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2666 "dhcp6_parser.cc"
    break;

  case 372: // $@59: %empty
#line 1519 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2675 "dhcp6_parser.cc"
    break;

  case 373: // library: "library" $@59 ":" "constant string"
#line 1522 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2685 "dhcp6_parser.cc"
    break;

  case 374: // $@60: %empty
#line 1528 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2694 "dhcp6_parser.cc"
    break;

  case 375: // parameters: "parameters" $@60 ":" map_value
#line 1531 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2703 "dhcp6_parser.cc"
    break;

  case 376: // $@61: %empty
#line 1537 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2715 "dhcp6_parser.cc"
    break;

  case 377: // expired_leases_processing: "expired-leases-processing" $@61 ":" "{" expired_leases_params "}"
#line 1543 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2725 "dhcp6_parser.cc"
    break;

  case 380: // expired_leases_params: expired_leases_params ","
#line 1551 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2733 "dhcp6_parser.cc"
    break;

  case 387: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1564 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2743 "dhcp6_parser.cc"
    break;

  case 388: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1570 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2753 "dhcp6_parser.cc"
    break;

  case 389: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1576 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2763 "dhcp6_parser.cc"
    break;

  case 390: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1582 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2773 "dhcp6_parser.cc"
    break;

  case 391: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1588 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2783 "dhcp6_parser.cc"
    break;

  case 392: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1594 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2793 "dhcp6_parser.cc"
    break;

  case 393: // $@62: %empty
#line 1603 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2805 "dhcp6_parser.cc"
    break;

  case 394: // subnet6_list: "subnet6" $@62 ":" "[" subnet6_list_content "]"
#line 1609 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2814 "dhcp6_parser.cc"
    break;

  case 399: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1623 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2822 "dhcp6_parser.cc"
    break;

  case 400: // $@63: %empty
#line 1632 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2832 "dhcp6_parser.cc"
    break;

  case 401: // subnet6: "{" $@63 subnet6_params "}"
#line 1636 "dhcp6_parser.yy"
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
#line 2858 "dhcp6_parser.cc"
    break;

  case 402: // $@64: %empty
#line 1658 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2868 "dhcp6_parser.cc"
    break;

  case 403: // sub_subnet6: "{" $@64 subnet6_params "}"
#line 1662 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2878 "dhcp6_parser.cc"
    break;

  case 406: // subnet6_params: subnet6_params ","
#line 1671 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2886 "dhcp6_parser.cc"
    break;

  case 459: // $@65: %empty
#line 1731 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2895 "dhcp6_parser.cc"
    break;

  case 460: // subnet: "subnet" $@65 ":" "constant string"
#line 1734 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2905 "dhcp6_parser.cc"
    break;

  case 461: // $@66: %empty
#line 1740 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2914 "dhcp6_parser.cc"
    break;

  case 462: // interface: "interface" $@66 ":" "constant string"
#line 1743 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2924 "dhcp6_parser.cc"
    break;

  case 463: // $@67: %empty
#line 1749 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2933 "dhcp6_parser.cc"
    break;

  case 464: // interface_id: "interface-id" $@67 ":" "constant string"
#line 1752 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2943 "dhcp6_parser.cc"
    break;

  case 465: // $@68: %empty
#line 1758 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2952 "dhcp6_parser.cc"
    break;

  case 466: // client_class: "client-class" $@68 ":" "constant string"
#line 1761 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2962 "dhcp6_parser.cc"
    break;

  case 467: // $@69: %empty
#line 1768 "dhcp6_parser.yy"
                                       {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2974 "dhcp6_parser.cc"
    break;

  case 468: // network_client_classes: "client-classes" $@69 ":" list_strings
#line 1774 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2983 "dhcp6_parser.cc"
    break;

  case 469: // $@70: %empty
#line 1780 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2995 "dhcp6_parser.cc"
    break;

  case 470: // require_client_classes: "require-client-classes" $@70 ":" list_strings
#line 1786 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3004 "dhcp6_parser.cc"
    break;

  case 471: // $@71: %empty
#line 1791 "dhcp6_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3016 "dhcp6_parser.cc"
    break;

  case 472: // evaluate_additional_classes: "evaluate-additional-classes" $@71 ":" list_strings
#line 1797 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3025 "dhcp6_parser.cc"
    break;

  case 473: // reservations_global: "reservations-global" ":" "boolean"
#line 1802 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 3035 "dhcp6_parser.cc"
    break;

  case 474: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1808 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 3045 "dhcp6_parser.cc"
    break;

  case 475: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1814 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 3055 "dhcp6_parser.cc"
    break;

  case 476: // id: "id" ":" "integer"
#line 1820 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 3065 "dhcp6_parser.cc"
    break;

  case 477: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1826 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 3075 "dhcp6_parser.cc"
    break;

  case 478: // $@72: %empty
#line 1834 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3087 "dhcp6_parser.cc"
    break;

  case 479: // shared_networks: "shared-networks" $@72 ":" "[" shared_networks_content "]"
#line 1840 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3096 "dhcp6_parser.cc"
    break;

  case 484: // shared_networks_list: shared_networks_list ","
#line 1853 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3104 "dhcp6_parser.cc"
    break;

  case 485: // $@73: %empty
#line 1858 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3114 "dhcp6_parser.cc"
    break;

  case 486: // shared_network: "{" $@73 shared_network_params "}"
#line 1862 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3122 "dhcp6_parser.cc"
    break;

  case 489: // shared_network_params: shared_network_params ","
#line 1868 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3130 "dhcp6_parser.cc"
    break;

  case 539: // $@74: %empty
#line 1928 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3142 "dhcp6_parser.cc"
    break;

  case 540: // option_def_list: "option-def" $@74 ":" "[" option_def_list_content "]"
#line 1934 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3151 "dhcp6_parser.cc"
    break;

  case 541: // $@75: %empty
#line 1942 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3160 "dhcp6_parser.cc"
    break;

  case 542: // sub_option_def_list: "{" $@75 option_def_list "}"
#line 1945 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 3168 "dhcp6_parser.cc"
    break;

  case 547: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1957 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3176 "dhcp6_parser.cc"
    break;

  case 548: // $@76: %empty
#line 1964 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3186 "dhcp6_parser.cc"
    break;

  case 549: // option_def_entry: "{" $@76 option_def_params "}"
#line 1968 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3198 "dhcp6_parser.cc"
    break;

  case 550: // $@77: %empty
#line 1979 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3208 "dhcp6_parser.cc"
    break;

  case 551: // sub_option_def: "{" $@77 option_def_params "}"
#line 1983 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3220 "dhcp6_parser.cc"
    break;

  case 556: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1999 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3228 "dhcp6_parser.cc"
    break;

  case 568: // code: "code" ":" "integer"
#line 2018 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3238 "dhcp6_parser.cc"
    break;

  case 570: // $@78: %empty
#line 2026 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3247 "dhcp6_parser.cc"
    break;

  case 571: // option_def_type: "type" $@78 ":" "constant string"
#line 2029 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3257 "dhcp6_parser.cc"
    break;

  case 572: // $@79: %empty
#line 2035 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3266 "dhcp6_parser.cc"
    break;

  case 573: // option_def_record_types: "record-types" $@79 ":" "constant string"
#line 2038 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3276 "dhcp6_parser.cc"
    break;

  case 574: // $@80: %empty
#line 2044 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3285 "dhcp6_parser.cc"
    break;

  case 575: // space: "space" $@80 ":" "constant string"
#line 2047 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3295 "dhcp6_parser.cc"
    break;

  case 577: // $@81: %empty
#line 2055 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3304 "dhcp6_parser.cc"
    break;

  case 578: // option_def_encapsulate: "encapsulate" $@81 ":" "constant string"
#line 2058 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3314 "dhcp6_parser.cc"
    break;

  case 579: // option_def_array: "array" ":" "boolean"
#line 2064 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3324 "dhcp6_parser.cc"
    break;

  case 580: // $@82: %empty
#line 2074 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3336 "dhcp6_parser.cc"
    break;

  case 581: // option_data_list: "option-data" $@82 ":" "[" option_data_list_content "]"
#line 2080 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3345 "dhcp6_parser.cc"
    break;

  case 586: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2095 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3353 "dhcp6_parser.cc"
    break;

  case 587: // $@83: %empty
#line 2102 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3363 "dhcp6_parser.cc"
    break;

  case 588: // option_data_entry: "{" $@83 option_data_params "}"
#line 2106 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3372 "dhcp6_parser.cc"
    break;

  case 589: // $@84: %empty
#line 2114 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3382 "dhcp6_parser.cc"
    break;

  case 590: // sub_option_data: "{" $@84 option_data_params "}"
#line 2118 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3391 "dhcp6_parser.cc"
    break;

  case 595: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2134 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3399 "dhcp6_parser.cc"
    break;

  case 608: // $@85: %empty
#line 2156 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3408 "dhcp6_parser.cc"
    break;

  case 609: // option_data_data: "data" $@85 ":" "constant string"
#line 2159 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3418 "dhcp6_parser.cc"
    break;

  case 612: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2169 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3428 "dhcp6_parser.cc"
    break;

  case 613: // option_data_always_send: "always-send" ":" "boolean"
#line 2175 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3438 "dhcp6_parser.cc"
    break;

  case 614: // option_data_never_send: "never-send" ":" "boolean"
#line 2181 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3448 "dhcp6_parser.cc"
    break;

  case 615: // $@86: %empty
#line 2187 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3460 "dhcp6_parser.cc"
    break;

  case 616: // option_data_client_classes: "client-classes" $@86 ":" list_strings
#line 2193 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3469 "dhcp6_parser.cc"
    break;

  case 617: // $@87: %empty
#line 2201 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3481 "dhcp6_parser.cc"
    break;

  case 618: // pools_list: "pools" $@87 ":" "[" pools_list_content "]"
#line 2207 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3490 "dhcp6_parser.cc"
    break;

  case 623: // not_empty_pools_list: not_empty_pools_list ","
#line 2220 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3498 "dhcp6_parser.cc"
    break;

  case 624: // $@88: %empty
#line 2225 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3508 "dhcp6_parser.cc"
    break;

  case 625: // pool_list_entry: "{" $@88 pool_params "}"
#line 2229 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3518 "dhcp6_parser.cc"
    break;

  case 626: // $@89: %empty
#line 2235 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3528 "dhcp6_parser.cc"
    break;

  case 627: // sub_pool6: "{" $@89 pool_params "}"
#line 2239 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3538 "dhcp6_parser.cc"
    break;

  case 630: // pool_params: pool_params ","
#line 2247 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3546 "dhcp6_parser.cc"
    break;

  case 655: // $@90: %empty
#line 2278 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3555 "dhcp6_parser.cc"
    break;

  case 656: // pool_entry: "pool" $@90 ":" "constant string"
#line 2281 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3565 "dhcp6_parser.cc"
    break;

  case 657: // pool_id: "pool-id" ":" "integer"
#line 2287 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3575 "dhcp6_parser.cc"
    break;

  case 658: // $@91: %empty
#line 2293 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3583 "dhcp6_parser.cc"
    break;

  case 659: // user_context: "user-context" $@91 ":" map_value
#line 2295 "dhcp6_parser.yy"
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
#line 3610 "dhcp6_parser.cc"
    break;

  case 660: // $@92: %empty
#line 2318 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3618 "dhcp6_parser.cc"
    break;

  case 661: // comment: "comment" $@92 ":" "constant string"
#line 2320 "dhcp6_parser.yy"
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
#line 3647 "dhcp6_parser.cc"
    break;

  case 662: // $@93: %empty
#line 2348 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3659 "dhcp6_parser.cc"
    break;

  case 663: // pd_pools_list: "pd-pools" $@93 ":" "[" pd_pools_list_content "]"
#line 2354 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3668 "dhcp6_parser.cc"
    break;

  case 668: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2367 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3676 "dhcp6_parser.cc"
    break;

  case 669: // $@94: %empty
#line 2372 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3686 "dhcp6_parser.cc"
    break;

  case 670: // pd_pool_entry: "{" $@94 pd_pool_params "}"
#line 2376 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3698 "dhcp6_parser.cc"
    break;

  case 671: // $@95: %empty
#line 2384 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3708 "dhcp6_parser.cc"
    break;

  case 672: // sub_pd_pool: "{" $@95 pd_pool_params "}"
#line 2388 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3720 "dhcp6_parser.cc"
    break;

  case 675: // pd_pool_params: pd_pool_params ","
#line 2398 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3728 "dhcp6_parser.cc"
    break;

  case 690: // $@96: %empty
#line 2419 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3737 "dhcp6_parser.cc"
    break;

  case 691: // pd_prefix: "prefix" $@96 ":" "constant string"
#line 2422 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3747 "dhcp6_parser.cc"
    break;

  case 692: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2428 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3757 "dhcp6_parser.cc"
    break;

  case 693: // $@97: %empty
#line 2434 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3766 "dhcp6_parser.cc"
    break;

  case 694: // excluded_prefix: "excluded-prefix" $@97 ":" "constant string"
#line 2437 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3776 "dhcp6_parser.cc"
    break;

  case 695: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2443 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3786 "dhcp6_parser.cc"
    break;

  case 696: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2449 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3796 "dhcp6_parser.cc"
    break;

  case 697: // $@98: %empty
#line 2458 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3808 "dhcp6_parser.cc"
    break;

  case 698: // reservations: "reservations" $@98 ":" "[" reservations_list "]"
#line 2464 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3817 "dhcp6_parser.cc"
    break;

  case 703: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2475 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3825 "dhcp6_parser.cc"
    break;

  case 704: // $@99: %empty
#line 2480 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3835 "dhcp6_parser.cc"
    break;

  case 705: // reservation: "{" $@99 reservation_params "}"
#line 2484 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3844 "dhcp6_parser.cc"
    break;

  case 706: // $@100: %empty
#line 2489 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3854 "dhcp6_parser.cc"
    break;

  case 707: // sub_reservation: "{" $@100 reservation_params "}"
#line 2493 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3863 "dhcp6_parser.cc"
    break;

  case 712: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2504 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3871 "dhcp6_parser.cc"
    break;

  case 725: // $@101: %empty
#line 2524 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3883 "dhcp6_parser.cc"
    break;

  case 726: // ip_addresses: "ip-addresses" $@101 ":" list_strings
#line 2530 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3892 "dhcp6_parser.cc"
    break;

  case 727: // $@102: %empty
#line 2535 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3904 "dhcp6_parser.cc"
    break;

  case 728: // prefixes: "prefixes" $@102 ":" list_strings
#line 2541 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3913 "dhcp6_parser.cc"
    break;

  case 729: // $@103: %empty
#line 2546 "dhcp6_parser.yy"
                                     {
    ctx.unique("excluded-prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3925 "dhcp6_parser.cc"
    break;

  case 730: // excluded_prefixes: "excluded-prefixes" $@103 ":" list_strings
#line 2552 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3934 "dhcp6_parser.cc"
    break;

  case 731: // $@104: %empty
#line 2557 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3943 "dhcp6_parser.cc"
    break;

  case 732: // duid: "duid" $@104 ":" "constant string"
#line 2560 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3953 "dhcp6_parser.cc"
    break;

  case 733: // $@105: %empty
#line 2566 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3962 "dhcp6_parser.cc"
    break;

  case 734: // hw_address: "hw-address" $@105 ":" "constant string"
#line 2569 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3972 "dhcp6_parser.cc"
    break;

  case 735: // $@106: %empty
#line 2575 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3981 "dhcp6_parser.cc"
    break;

  case 736: // hostname: "hostname" $@106 ":" "constant string"
#line 2578 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3991 "dhcp6_parser.cc"
    break;

  case 737: // $@107: %empty
#line 2584 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4000 "dhcp6_parser.cc"
    break;

  case 738: // flex_id_value: "flex-id" $@107 ":" "constant string"
#line 2587 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 4010 "dhcp6_parser.cc"
    break;

  case 739: // $@108: %empty
#line 2593 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4022 "dhcp6_parser.cc"
    break;

  case 740: // reservation_client_classes: "client-classes" $@108 ":" list_strings
#line 2599 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4031 "dhcp6_parser.cc"
    break;

  case 741: // $@109: %empty
#line 2607 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 4043 "dhcp6_parser.cc"
    break;

  case 742: // relay: "relay" $@109 ":" "{" relay_map "}"
#line 2613 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4052 "dhcp6_parser.cc"
    break;

  case 744: // $@110: %empty
#line 2624 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 4064 "dhcp6_parser.cc"
    break;

  case 745: // client_classes: "client-classes" $@110 ":" "[" client_classes_list "]"
#line 2630 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4073 "dhcp6_parser.cc"
    break;

  case 750: // not_empty_classes_list: not_empty_classes_list ","
#line 2641 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4081 "dhcp6_parser.cc"
    break;

  case 751: // $@111: %empty
#line 2646 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4091 "dhcp6_parser.cc"
    break;

  case 752: // client_class_entry: "{" $@111 client_class_params "}"
#line 2650 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 4101 "dhcp6_parser.cc"
    break;

  case 757: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2662 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 4109 "dhcp6_parser.cc"
    break;

  case 774: // $@112: %empty
#line 2686 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4118 "dhcp6_parser.cc"
    break;

  case 775: // client_class_test: "test" $@112 ":" "constant string"
#line 2689 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4128 "dhcp6_parser.cc"
    break;

  case 776: // $@113: %empty
#line 2695 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4137 "dhcp6_parser.cc"
    break;

  case 777: // client_class_template_test: "template-test" $@113 ":" "constant string"
#line 2698 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4147 "dhcp6_parser.cc"
    break;

  case 778: // only_if_required: "only-if-required" ":" "boolean"
#line 2705 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4157 "dhcp6_parser.cc"
    break;

  case 779: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2711 "dhcp6_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4167 "dhcp6_parser.cc"
    break;

  case 780: // $@114: %empty
#line 2720 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 4179 "dhcp6_parser.cc"
    break;

  case 781: // server_id: "server-id" $@114 ":" "{" server_id_params "}"
#line 2726 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4190 "dhcp6_parser.cc"
    break;

  case 784: // server_id_params: server_id_params ","
#line 2735 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4198 "dhcp6_parser.cc"
    break;

  case 794: // $@115: %empty
#line 2751 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 4207 "dhcp6_parser.cc"
    break;

  case 795: // server_id_type: "type" $@115 ":" duid_type
#line 2754 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4216 "dhcp6_parser.cc"
    break;

  case 796: // duid_type: "LLT"
#line 2759 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4222 "dhcp6_parser.cc"
    break;

  case 797: // duid_type: "EN"
#line 2760 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4228 "dhcp6_parser.cc"
    break;

  case 798: // duid_type: "LL"
#line 2761 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4234 "dhcp6_parser.cc"
    break;

  case 799: // htype: "htype" ":" "integer"
#line 2764 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4244 "dhcp6_parser.cc"
    break;

  case 800: // $@116: %empty
#line 2770 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4253 "dhcp6_parser.cc"
    break;

  case 801: // identifier: "identifier" $@116 ":" "constant string"
#line 2773 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4263 "dhcp6_parser.cc"
    break;

  case 802: // time: "time" ":" "integer"
#line 2779 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4273 "dhcp6_parser.cc"
    break;

  case 803: // enterprise_id: "enterprise-id" ":" "integer"
#line 2785 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4283 "dhcp6_parser.cc"
    break;

  case 804: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2793 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4293 "dhcp6_parser.cc"
    break;

  case 805: // $@117: %empty
#line 2801 "dhcp6_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKETS);
}
#line 4305 "dhcp6_parser.cc"
    break;

  case 806: // control_sockets: "control-sockets" $@117 ":" "[" control_socket_list "]"
#line 2807 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4314 "dhcp6_parser.cc"
    break;

  case 811: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2818 "dhcp6_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4322 "dhcp6_parser.cc"
    break;

  case 812: // $@118: %empty
#line 2823 "dhcp6_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4332 "dhcp6_parser.cc"
    break;

  case 813: // control_socket_entry: "{" $@118 control_socket_params "}"
#line 2827 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4340 "dhcp6_parser.cc"
    break;

  case 816: // control_socket_params: control_socket_params ","
#line 2833 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4348 "dhcp6_parser.cc"
    break;

  case 830: // $@119: %empty
#line 2853 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4357 "dhcp6_parser.cc"
    break;

  case 831: // control_socket_type: "socket-type" $@119 ":" control_socket_type_value
#line 2856 "dhcp6_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4366 "dhcp6_parser.cc"
    break;

  case 832: // control_socket_type_value: "unix"
#line 2862 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4372 "dhcp6_parser.cc"
    break;

  case 833: // control_socket_type_value: "http"
#line 2863 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4378 "dhcp6_parser.cc"
    break;

  case 834: // control_socket_type_value: "https"
#line 2864 "dhcp6_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4384 "dhcp6_parser.cc"
    break;

  case 835: // $@120: %empty
#line 2867 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4393 "dhcp6_parser.cc"
    break;

  case 836: // control_socket_name: "socket-name" $@120 ":" "constant string"
#line 2870 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4403 "dhcp6_parser.cc"
    break;

  case 837: // $@121: %empty
#line 2876 "dhcp6_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4412 "dhcp6_parser.cc"
    break;

  case 838: // control_socket_address: "socket-address" $@121 ":" "constant string"
#line 2879 "dhcp6_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4422 "dhcp6_parser.cc"
    break;

  case 839: // control_socket_port: "socket-port" ":" "integer"
#line 2885 "dhcp6_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4432 "dhcp6_parser.cc"
    break;

  case 840: // cert_required: "cert-required" ":" "boolean"
#line 2891 "dhcp6_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4442 "dhcp6_parser.cc"
    break;

  case 841: // $@122: %empty
#line 2897 "dhcp6_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4454 "dhcp6_parser.cc"
    break;

  case 842: // http_headers: "http-headers" $@122 ":" "[" http_header_list "]"
#line 2903 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4463 "dhcp6_parser.cc"
    break;

  case 847: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2914 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4471 "dhcp6_parser.cc"
    break;

  case 848: // $@123: %empty
#line 2919 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4481 "dhcp6_parser.cc"
    break;

  case 849: // http_header: "{" $@123 http_header_params "}"
#line 2923 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4489 "dhcp6_parser.cc"
    break;

  case 852: // http_header_params: http_header_params ","
#line 2929 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4497 "dhcp6_parser.cc"
    break;

  case 858: // $@124: %empty
#line 2941 "dhcp6_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4506 "dhcp6_parser.cc"
    break;

  case 859: // header_value: "value" $@124 ":" "constant string"
#line 2944 "dhcp6_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4516 "dhcp6_parser.cc"
    break;

  case 860: // $@125: %empty
#line 2952 "dhcp6_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4528 "dhcp6_parser.cc"
    break;

  case 861: // authentication: "authentication" $@125 ":" "{" auth_params "}"
#line 2958 "dhcp6_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4539 "dhcp6_parser.cc"
    break;

  case 864: // auth_params: auth_params ","
#line 2967 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4547 "dhcp6_parser.cc"
    break;

  case 872: // $@126: %empty
#line 2981 "dhcp6_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4556 "dhcp6_parser.cc"
    break;

  case 873: // auth_type: "type" $@126 ":" auth_type_value
#line 2984 "dhcp6_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4565 "dhcp6_parser.cc"
    break;

  case 874: // auth_type_value: "basic"
#line 2989 "dhcp6_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4571 "dhcp6_parser.cc"
    break;

  case 875: // $@127: %empty
#line 2992 "dhcp6_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4580 "dhcp6_parser.cc"
    break;

  case 876: // realm: "realm" $@127 ":" "constant string"
#line 2995 "dhcp6_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4590 "dhcp6_parser.cc"
    break;

  case 877: // $@128: %empty
#line 3001 "dhcp6_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4599 "dhcp6_parser.cc"
    break;

  case 878: // directory: "directory" $@128 ":" "constant string"
#line 3004 "dhcp6_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4609 "dhcp6_parser.cc"
    break;

  case 879: // $@129: %empty
#line 3010 "dhcp6_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4621 "dhcp6_parser.cc"
    break;

  case 880: // clients: "clients" $@129 ":" "[" clients_list "]"
#line 3016 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4630 "dhcp6_parser.cc"
    break;

  case 885: // not_empty_clients_list: not_empty_clients_list ","
#line 3027 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4638 "dhcp6_parser.cc"
    break;

  case 886: // $@130: %empty
#line 3032 "dhcp6_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4648 "dhcp6_parser.cc"
    break;

  case 887: // basic_auth: "{" $@130 clients_params "}"
#line 3036 "dhcp6_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4656 "dhcp6_parser.cc"
    break;

  case 890: // clients_params: clients_params ","
#line 3042 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4664 "dhcp6_parser.cc"
    break;

  case 898: // $@131: %empty
#line 3056 "dhcp6_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4673 "dhcp6_parser.cc"
    break;

  case 899: // user_file: "user-file" $@131 ":" "constant string"
#line 3059 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4683 "dhcp6_parser.cc"
    break;

  case 900: // $@132: %empty
#line 3065 "dhcp6_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4692 "dhcp6_parser.cc"
    break;

  case 901: // password_file: "password-file" $@132 ":" "constant string"
#line 3068 "dhcp6_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4702 "dhcp6_parser.cc"
    break;

  case 902: // $@133: %empty
#line 3076 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4714 "dhcp6_parser.cc"
    break;

  case 903: // dhcp_queue_control: "dhcp-queue-control" $@133 ":" "{" queue_control_params "}"
#line 3082 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4725 "dhcp6_parser.cc"
    break;

  case 906: // queue_control_params: queue_control_params ","
#line 3091 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4733 "dhcp6_parser.cc"
    break;

  case 913: // enable_queue: "enable-queue" ":" "boolean"
#line 3104 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4743 "dhcp6_parser.cc"
    break;

  case 914: // $@134: %empty
#line 3110 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4752 "dhcp6_parser.cc"
    break;

  case 915: // queue_type: "queue-type" $@134 ":" "constant string"
#line 3113 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4762 "dhcp6_parser.cc"
    break;

  case 916: // capacity: "capacity" ":" "integer"
#line 3119 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4772 "dhcp6_parser.cc"
    break;

  case 917: // $@135: %empty
#line 3125 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4781 "dhcp6_parser.cc"
    break;

  case 918: // arbitrary_map_entry: "constant string" $@135 ":" value
#line 3128 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4790 "dhcp6_parser.cc"
    break;

  case 919: // $@136: %empty
#line 3135 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4802 "dhcp6_parser.cc"
    break;

  case 920: // dhcp_ddns: "dhcp-ddns" $@136 ":" "{" dhcp_ddns_params "}"
#line 3141 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4813 "dhcp6_parser.cc"
    break;

  case 921: // $@137: %empty
#line 3148 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4823 "dhcp6_parser.cc"
    break;

  case 922: // sub_dhcp_ddns: "{" $@137 dhcp_ddns_params "}"
#line 3152 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4833 "dhcp6_parser.cc"
    break;

  case 925: // dhcp_ddns_params: dhcp_ddns_params ","
#line 3160 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4841 "dhcp6_parser.cc"
    break;

  case 937: // enable_updates: "enable-updates" ":" "boolean"
#line 3178 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4851 "dhcp6_parser.cc"
    break;

  case 938: // $@138: %empty
#line 3184 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4860 "dhcp6_parser.cc"
    break;

  case 939: // server_ip: "server-ip" $@138 ":" "constant string"
#line 3187 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4870 "dhcp6_parser.cc"
    break;

  case 940: // server_port: "server-port" ":" "integer"
#line 3193 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4880 "dhcp6_parser.cc"
    break;

  case 941: // $@139: %empty
#line 3199 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4889 "dhcp6_parser.cc"
    break;

  case 942: // sender_ip: "sender-ip" $@139 ":" "constant string"
#line 3202 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4899 "dhcp6_parser.cc"
    break;

  case 943: // sender_port: "sender-port" ":" "integer"
#line 3208 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4909 "dhcp6_parser.cc"
    break;

  case 944: // max_queue_size: "max-queue-size" ":" "integer"
#line 3214 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4919 "dhcp6_parser.cc"
    break;

  case 945: // $@140: %empty
#line 3220 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4928 "dhcp6_parser.cc"
    break;

  case 946: // ncr_protocol: "ncr-protocol" $@140 ":" ncr_protocol_value
#line 3223 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4937 "dhcp6_parser.cc"
    break;

  case 947: // ncr_protocol_value: "UDP"
#line 3229 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4943 "dhcp6_parser.cc"
    break;

  case 948: // ncr_protocol_value: "TCP"
#line 3230 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4949 "dhcp6_parser.cc"
    break;

  case 949: // $@141: %empty
#line 3233 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4958 "dhcp6_parser.cc"
    break;

  case 950: // ncr_format: "ncr-format" $@141 ":" "JSON"
#line 3236 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4968 "dhcp6_parser.cc"
    break;

  case 951: // $@142: %empty
#line 3244 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4980 "dhcp6_parser.cc"
    break;

  case 952: // config_control: "config-control" $@142 ":" "{" config_control_params "}"
#line 3250 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4990 "dhcp6_parser.cc"
    break;

  case 953: // $@143: %empty
#line 3256 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 5000 "dhcp6_parser.cc"
    break;

  case 954: // sub_config_control: "{" $@143 config_control_params "}"
#line 3260 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 5009 "dhcp6_parser.cc"
    break;

  case 957: // config_control_params: config_control_params ","
#line 3268 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 5017 "dhcp6_parser.cc"
    break;

  case 960: // $@144: %empty
#line 3278 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 5029 "dhcp6_parser.cc"
    break;

  case 961: // config_databases: "config-databases" $@144 ":" "[" database_list "]"
#line 3284 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5038 "dhcp6_parser.cc"
    break;

  case 962: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3289 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 5048 "dhcp6_parser.cc"
    break;

  case 963: // $@145: %empty
#line 3297 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 5060 "dhcp6_parser.cc"
    break;

  case 964: // loggers: "loggers" $@145 ":" "[" loggers_entries "]"
#line 3303 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5069 "dhcp6_parser.cc"
    break;

  case 967: // loggers_entries: loggers_entries ","
#line 3312 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 5077 "dhcp6_parser.cc"
    break;

  case 968: // $@146: %empty
#line 3318 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 5087 "dhcp6_parser.cc"
    break;

  case 969: // logger_entry: "{" $@146 logger_params "}"
#line 3322 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 5095 "dhcp6_parser.cc"
    break;

  case 972: // logger_params: logger_params ","
#line 3328 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 5103 "dhcp6_parser.cc"
    break;

  case 980: // debuglevel: "debuglevel" ":" "integer"
#line 3342 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 5113 "dhcp6_parser.cc"
    break;

  case 981: // $@147: %empty
#line 3348 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5122 "dhcp6_parser.cc"
    break;

  case 982: // severity: "severity" $@147 ":" "constant string"
#line 3351 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 5132 "dhcp6_parser.cc"
    break;

  case 983: // $@148: %empty
#line 3357 "dhcp6_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 5144 "dhcp6_parser.cc"
    break;

  case 984: // output_options_list: "output-options" $@148 ":" "[" output_options_list_content "]"
#line 3363 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5153 "dhcp6_parser.cc"
    break;

  case 987: // output_options_list_content: output_options_list_content ","
#line 3370 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 5161 "dhcp6_parser.cc"
    break;

  case 988: // $@149: %empty
#line 3375 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 5171 "dhcp6_parser.cc"
    break;

  case 989: // output_entry: "{" $@149 output_params_list "}"
#line 3379 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 5179 "dhcp6_parser.cc"
    break;

  case 992: // output_params_list: output_params_list ","
#line 3385 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 5187 "dhcp6_parser.cc"
    break;

  case 998: // $@150: %empty
#line 3397 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5196 "dhcp6_parser.cc"
    break;

  case 999: // output: "output" $@150 ":" "constant string"
#line 3400 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5206 "dhcp6_parser.cc"
    break;

  case 1000: // flush: "flush" ":" "boolean"
#line 3406 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5216 "dhcp6_parser.cc"
    break;

  case 1001: // maxsize: "maxsize" ":" "integer"
#line 3412 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5226 "dhcp6_parser.cc"
    break;

  case 1002: // maxver: "maxver" ":" "integer"
#line 3418 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5236 "dhcp6_parser.cc"
    break;

  case 1003: // $@151: %empty
#line 3424 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5245 "dhcp6_parser.cc"
    break;

  case 1004: // pattern: "pattern" $@151 ":" "constant string"
#line 3427 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5255 "dhcp6_parser.cc"
    break;

  case 1005: // $@152: %empty
#line 3433 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5267 "dhcp6_parser.cc"
    break;

  case 1006: // compatibility: "compatibility" $@152 ":" "{" compatibility_params "}"
#line 3439 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5276 "dhcp6_parser.cc"
    break;

  case 1009: // compatibility_params: compatibility_params ","
#line 3446 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5284 "dhcp6_parser.cc"
    break;

  case 1012: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3455 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5294 "dhcp6_parser.cc"
    break;


#line 5298 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1467;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     571, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467,    54,    82,    77,    83,   141,
     145,   210,   224,   241,   252,   273,   288,   331,   362,   364,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,    82,  -184,
      95,   774,   166,   336,  1515,   229,   583,   -23,   131,   -21,
     -91,   231,   118, -1467,    72,   157,    88,    93,   175, -1467,
      58, -1467, -1467, -1467, -1467, -1467, -1467, -1467,   105,   200,
     369,   382,   384,   401,   402,   421,   444,   446,   459,   467,
     471,   473,   475, -1467,   481,   495,   507,   515,   518, -1467,
   -1467, -1467,   519,   521,   524,   525,   526,   529,   531, -1467,
   -1467, -1467,   533, -1467, -1467, -1467, -1467, -1467, -1467,   537,
     538,   541, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467,   544, -1467, -1467, -1467, -1467, -1467, -1467,   547,   549,
     554,   558, -1467, -1467,   559, -1467,    94, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467,   561,   563,   565,   566, -1467,   112, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
     569,   570, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
     153, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467,   572, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467,   160, -1467, -1467, -1467, -1467, -1467, -1467,
     574, -1467,   576,   577, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467,   167, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467,   454,   500, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467,   502, -1467, -1467,   579, -1467, -1467, -1467,
     580, -1467, -1467,   536,   582, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,   590,   592,
     593, -1467, -1467, -1467, -1467, -1467,   567,   596, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467,   171, -1467, -1467, -1467,   599, -1467,   602, -1467,
     603,   606, -1467, -1467, -1467, -1467, -1467,   215, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,   607,   232,
   -1467, -1467, -1467, -1467,    82,    82, -1467,   372,   612, -1467,
   -1467,   613,   619,   621,   623,   625,   629,   395,   397,   405,
     408,   409,   410,   412,   413,   400,   414,   419,   420,   426,
     429,   427,   652,   432,   433,   434,   435,   436,   669,   672,
     678,   442,   443,   440,   447,   448,   449,   450,   689,   691,
     692,   455,   696,   697,   698,   699,   700,   701,   463,   464,
     466,   707,   708,   709,   711,   712,   713,   714,   715,   716,
     479,   718,   719,   727,   729,   730,   731,   492,   493,   494,
     496,   735,   737, -1467,   774, -1467,   738,   503,   505,   501,
     504,   166, -1467,   746,   747,   749,   750,   751,   514,   513,
     754,   755,   756,   757,   758,   336, -1467,   759,   522,  1515,
   -1467,   761,   527,   768,   532,   534,   229, -1467,   769,   771,
     773,   775,   776,   777,   778,   779, -1467,   583, -1467,   780,
     784,   548,   787,   788,   789,   550, -1467,   131,   808,   573,
     575,   618,   809, -1467,   -21,   810,   811,    16, -1467,   620,
     812,   578,   814,   585,   624,   817,   859,   231, -1467,   861,
     626,   118, -1467, -1467, -1467,   863,   862,   630,   869,   870,
     871,   872,   865, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,   640, -1467,
   -1467, -1467, -1467, -1467,  -132,   641,   642, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467,   879,   880,   881, -1467,   646,   647,
     174,   886,   885,   653, -1467, -1467, -1467,   888,   890,   898,
     897,   901,   902,   903,   904,   905, -1467,   906,   910,   909,
     911,   668,   676, -1467, -1467, -1467, -1467,   914,   913, -1467,
     916, -1467, -1467, -1467, -1467, -1467,   917,   919,   684,   686,
     687, -1467, -1467,   916,   916,   916,   688,   923, -1467,   690,
   -1467, -1467,   693, -1467,   694, -1467, -1467, -1467,   916,   916,
     916,   916,   695,   702,   703,   704, -1467,   706,   710, -1467,
     717,   720,   721, -1467, -1467,   722, -1467, -1467, -1467,   916,
   -1467,   724,   885, -1467, -1467,   725, -1467,   726, -1467, -1467,
      34,   705, -1467,   927, -1467, -1467,    82,   774, -1467,   118,
     166,   163,   163,   930, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467,   931,   932,   933, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467,   941, -1467, -1467, -1467,   -92,    82,   277,
     159,   942,   943,   945,   225,   109,   114,   946,   -70,   231,
   -1467, -1467,   947,  -179, -1467, -1467,   948,   949, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467,   637, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467,   930, -1467,   236,   242,   257, -1467, -1467, -1467,
   -1467,   953,   955,   956,   965,   966,   967,   968,   969,   970,
     971, -1467,   972,   973, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467,   301, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
     314, -1467,   974,   975, -1467, -1467,   976,   978, -1467, -1467,
     977,   988, -1467, -1467,   986,   990, -1467, -1467,   989,   991,
   -1467, -1467, -1467,    50, -1467, -1467, -1467,   992, -1467, -1467,
   -1467,   246, -1467, -1467, -1467, -1467, -1467,   324, -1467, -1467,
   -1467, -1467,   994,   993, -1467, -1467,   995,   999, -1467, -1467,
     997,  1001, -1467,  1002,  1003,  1004,  1005,  1006,  1008,   345,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,  1009,
    1012,  1014, -1467, -1467, -1467, -1467,   346, -1467, -1467, -1467,
   -1467, -1467, -1467,  1015,  1018,  1019, -1467,   348, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467,  1022,  1028, -1467,  1021, -1467,
    1035, -1467, -1467, -1467,   349, -1467, -1467, -1467, -1467, -1467,
     356, -1467,   302, -1467,  1040, -1467,   431, -1467, -1467,   764,
   -1467,  1043,  1048, -1467, -1467,  1046,  1050, -1467, -1467,  1055,
    1059, -1467, -1467, -1467,  1065,  1066,  1068,  1070,   837,   753,
     843,   842,   845,   855,   877,   878,   899,   921,  1097,   860,
     937,  1136,  1147,  1168,  1181,  1182,   163, -1467, -1467,   163,
   -1467,   930,   336, -1467,   931,   131, -1467,   932,   -21, -1467,
     933,  1446, -1467,   941,   -92, -1467, -1467,   277, -1467,  1184,
    1186,   159, -1467,   199, -1467,   942,   583, -1467,   943,   -91,
   -1467,   945,   950,   957,   958,   959,   961,   963,   225, -1467,
    1191,  1194,   964,   979,   980,   109, -1467,   981,   982,   984,
     114, -1467,   197, -1467,   946,   983,  1204,   987,  1205,   -70,
   -1467, -1467,   146,   947, -1467,   996,  -179, -1467, -1467,  1207,
    1208,  1515, -1467,   948,   229, -1467,   949, -1467, -1467,   998,
    1000,  1007,  1010, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467,   227, -1467, -1467,  1013,  1017,  1020,   540,
    1023, -1467,   438, -1467,   439, -1467,  1202, -1467,  1210, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467,   441, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467,  1024,  1025, -1467, -1467, -1467,  1211,
    1212, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467,  1215,  1216, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467,  1220, -1467,   458, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467,   158,  1026, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467,  1227, -1467,  1228, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467,   470, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467,  1027, -1467,    82, -1467,
   -1467,  1230, -1467, -1467, -1467, -1467, -1467,   483, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467,  1029,   484, -1467,   485,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,  1446, -1467,
   -1467, -1467,  1231,  1232,  1011,  1030, -1467,   199, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467,  1233,  1234,  1238,  1031,  1239,
    1032,  1240,   197, -1467, -1467, -1467,  1241,  1033,  1242,   146,
   -1467, -1467, -1467, -1467, -1467,  1036,  1037, -1467, -1467, -1467,
     155,  1038,  1039, -1467,  1213, -1467,  1245, -1467,  1254, -1467,
    1041, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
      87,  1255,  1256, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467,   486, -1467, -1467, -1467, -1467, -1467, -1467,  1263,  1244,
   -1467, -1467,   506, -1467,  1267,  1268,  1277,  1279,    87, -1467,
     148, -1467,  1255,    76,  1256, -1467,   798,  1044,  1045,  1283,
   -1467, -1467, -1467, -1467, -1467, -1467,   497, -1467, -1467, -1467,
   -1467,  1280,  1285,  1286, -1467,   498, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467,  1284,  1288,   148,
   -1467,  1289,  1051,  1052,  1056,  1295,    76, -1467, -1467,  1296,
    1298, -1467,  1063, -1467,  1064, -1467, -1467, -1467,  1071, -1467,
     117, -1467,  1284, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467,   499, -1467, -1467, -1467, -1467,  1302,  1303,
     117, -1467,  1072,  1073, -1467, -1467, -1467
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   208,     9,   402,    11,
     626,    13,   671,    15,   706,    17,   541,    19,   550,    21,
     589,    23,   364,    25,   921,    27,   953,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   708,     0,   552,   591,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   145,   951,   206,   227,   229,   231,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   195,     0,     0,     0,     0,     0,   165,
     172,   174,     0,     0,     0,     0,     0,     0,     0,   393,
     539,   580,     0,   198,   200,   178,   478,   658,   660,     0,
       0,     0,   320,   339,   329,   309,   744,   697,   355,   376,
     780,     0,   341,   805,   902,   919,   188,   190,     0,     0,
       0,     0,   963,  1005,     0,   144,     0,    69,    72,    73,
      74,    75,    76,    77,    78,    79,    80,   110,   111,   112,
     113,   114,   115,    81,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   117,   118,   132,
     133,   134,   106,   141,   142,   143,   136,   137,   138,   139,
      84,    85,    86,    87,   103,    88,    90,    89,   135,    94,
      95,    82,   107,   108,   109,    83,    92,    93,   101,   102,
     104,    91,    96,    97,    98,    99,   100,   105,   116,   140,
     221,     0,     0,     0,     0,   220,     0,   210,   213,   214,
     215,   216,   217,   218,   219,   617,   662,   459,   461,   463,
       0,     0,   467,   469,   471,   465,   741,   458,   407,   408,
     409,   410,   411,   412,   413,   414,   434,   435,   436,   437,
     438,   439,   442,   443,   444,   445,   446,   447,   448,   449,
     450,   451,   452,   453,   454,   440,   441,   455,   456,   457,
       0,   404,   418,   419,   420,   423,   424,   425,   426,   428,
     429,   430,   421,   422,   415,   416,   432,   433,   417,   427,
     431,   655,     0,   654,   638,   639,   640,   641,   642,   643,
     644,   645,   646,   647,   648,   649,   650,   651,   634,   635,
     636,   637,   633,     0,   628,   631,   632,   652,   653,   690,
       0,   693,     0,     0,   689,   681,   682,   683,   684,   680,
     679,   687,   688,     0,   673,   676,   677,   685,   686,   678,
     739,   725,   727,   729,   731,   733,   735,   737,   724,   721,
     722,   723,     0,   709,   710,   715,   716,   717,   713,   718,
     719,   720,   714,     0,   570,   276,     0,   574,   572,   577,
       0,   566,   567,     0,   553,   554,   557,   569,   558,   559,
     560,   576,   561,   562,   563,   564,   565,   608,     0,     0,
       0,   615,   606,   607,   610,   611,     0,   592,   593,   596,
     597,   598,   599,   600,   601,   602,   605,   603,   604,   372,
     374,   369,     0,   366,   370,   371,     0,   938,     0,   941,
       0,     0,   945,   949,   936,   934,   935,     0,   923,   926,
     927,   928,   929,   930,   931,   932,   933,   960,     0,     0,
     955,   958,   959,    47,    52,     0,    39,    45,     0,    66,
      62,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    60,    71,    68,     0,     0,     0,     0,
       0,   212,   209,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   406,   403,     0,     0,   630,
     627,     0,     0,     0,     0,     0,   675,   672,     0,     0,
       0,     0,     0,     0,     0,     0,   707,   712,   542,     0,
       0,     0,     0,     0,     0,     0,   551,   556,     0,     0,
       0,     0,     0,   590,   595,     0,     0,   368,   365,     0,
       0,     0,     0,     0,     0,     0,     0,   925,   922,     0,
       0,   957,   954,    51,    43,     0,     0,     0,     0,     0,
       0,     0,     0,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,     0,   193,
     194,   162,   163,   164,     0,     0,     0,   176,   177,   184,
     185,   186,   187,   192,     0,     0,     0,   197,     0,     0,
       0,     0,     0,     0,   473,   474,   475,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   804,     0,     0,     0,
       0,     0,     0,   202,   203,   204,   205,     0,     0,    70,
       0,   223,   224,   225,   226,   211,     0,     0,     0,     0,
       0,   476,   477,     0,     0,     0,     0,     0,   405,     0,
     657,   629,     0,   692,     0,   695,   696,   674,     0,     0,
       0,     0,     0,     0,     0,     0,   711,     0,     0,   568,
       0,     0,     0,   579,   555,     0,   612,   613,   614,     0,
     594,     0,     0,   367,   937,     0,   940,     0,   943,   944,
       0,     0,   924,     0,   962,   956,     0,     0,   146,     0,
       0,     0,     0,   233,   196,   167,   168,   169,   170,   171,
     166,   173,   175,   395,   543,   582,   199,   201,   180,   181,
     182,   183,   179,   480,    40,   659,   661,     0,    48,     0,
       0,   746,   699,   357,     0,     0,     0,   807,     0,     0,
     189,   191,     0,     0,    53,   222,   619,   664,   460,   462,
     464,   468,   470,   472,   466,     0,   656,   691,   694,   740,
     726,   728,   730,   732,   734,   736,   738,   571,   277,   575,
     573,   578,   609,   616,   373,   375,   939,   942,   947,   948,
     946,   950,   233,    44,     0,     0,     0,   267,   269,   271,
     273,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   286,     0,     0,   294,   296,   298,   300,   302,   303,
     304,   305,   306,   307,   266,     0,   240,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     257,   258,   259,   260,   256,   261,   262,   263,   264,   265,
       0,   238,     0,   234,   235,   400,     0,   396,   397,   548,
       0,   544,   545,   587,     0,   583,   584,   485,     0,   481,
     482,   327,   328,     0,   322,   325,   326,     0,   337,   338,
     334,     0,   331,   335,   336,   316,   318,     0,   311,   314,
     315,   751,     0,   747,   748,   704,     0,   700,   701,   362,
       0,   358,   359,     0,     0,     0,     0,     0,     0,     0,
     378,   381,   382,   383,   384,   385,   386,   794,   800,     0,
       0,     0,   793,   790,   791,   792,     0,   782,   785,   788,
     786,   787,   789,     0,     0,     0,   351,     0,   343,   346,
     347,   348,   349,   350,   812,     0,   808,   809,     0,   914,
       0,   917,   910,   911,     0,   904,   907,   908,   909,   912,
       0,   968,     0,   965,     0,  1011,     0,  1007,  1010,    55,
     624,     0,   620,   621,   669,     0,   665,   666,   743,     0,
       0,    64,   952,   207,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   242,   228,   230,     0,
     232,   237,     0,   394,   399,   552,   540,   547,   591,   581,
     586,     0,   479,   484,   324,   321,   340,   333,   330,     0,
       0,   313,   310,   753,   745,   750,   708,   698,   703,     0,
     356,   361,     0,     0,     0,     0,     0,     0,   380,   377,
       0,     0,     0,     0,     0,   784,   781,     0,     0,     0,
     345,   342,     0,   806,   811,     0,     0,     0,     0,   906,
     903,   920,     0,   967,   964,     0,  1009,  1006,    57,     0,
      56,     0,   618,   623,     0,   663,   668,   742,   961,     0,
       0,     0,     0,   275,   278,   279,   280,   281,   282,   283,
     284,   293,   285,     0,   291,   292,     0,     0,     0,     0,
       0,   241,     0,   236,     0,   398,     0,   546,     0,   585,
     538,   505,   506,   507,   509,   510,   511,   494,   495,   514,
     515,   516,   517,   518,   519,   522,   523,   524,   525,   526,
     527,   528,   529,   530,   531,   532,   533,   534,   520,   521,
     535,   536,   537,   490,   491,   492,   493,   501,   502,   503,
     504,   498,   499,   500,   508,     0,   487,   496,   512,   513,
     497,   483,   323,   332,     0,     0,   312,   774,   776,     0,
       0,   772,   766,   767,   768,   769,   770,   771,   773,   763,
     764,   765,     0,   754,   755,   758,   759,   760,   761,   762,
     749,     0,   702,     0,   360,   387,   388,   389,   390,   391,
     392,   379,     0,     0,   799,   802,   803,   783,   352,   353,
     354,   344,   830,   835,   837,     0,   860,     0,   841,   829,
     822,   823,   824,   827,   828,     0,   814,   817,   818,   819,
     820,   825,   826,   821,   810,   913,     0,   916,     0,   905,
     983,     0,   981,   979,   973,   977,   978,     0,   970,   975,
     976,   974,   966,  1012,  1008,    54,    59,     0,   622,     0,
     667,   268,   270,   272,   274,   288,   289,   290,   287,   295,
     297,   299,   301,   308,   239,   401,   549,   588,   489,   486,
     317,   319,     0,     0,     0,     0,   752,   757,   705,   363,
     796,   797,   798,   795,   801,     0,     0,     0,     0,     0,
       0,     0,   816,   813,   915,   918,     0,     0,     0,   972,
     969,    58,   625,   670,   488,     0,     0,   778,   779,   756,
       0,     0,     0,   839,     0,   840,     0,   815,     0,   980,
       0,   971,   775,   777,   832,   833,   834,   831,   836,   838,
       0,   843,     0,   982,   872,   875,   877,   879,   871,   870,
     869,     0,   862,   865,   866,   867,   868,   848,     0,   844,
     845,   988,     0,   985,     0,     0,     0,     0,   864,   861,
       0,   842,   847,     0,   987,   984,     0,     0,     0,     0,
     863,   858,   857,   853,   855,   856,     0,   850,   854,   846,
     998,     0,     0,     0,  1003,     0,   990,   993,   994,   995,
     996,   997,   986,   874,   873,   876,   878,   881,     0,   852,
     849,     0,     0,     0,     0,     0,   992,   989,   886,     0,
     882,   883,     0,   851,     0,  1000,  1001,  1002,     0,   991,
       0,   880,   885,   859,   999,  1004,   898,   900,   897,   891,
     893,   895,   896,     0,   888,   892,   894,   884,     0,     0,
     890,   887,     0,     0,   889,   899,   901
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467,   -10, -1467,  -617, -1467,
     560, -1467, -1467, -1467, -1467,   508, -1467,  -243, -1467, -1467,
   -1467,   -71, -1467, -1467, -1467, -1467, -1467, -1467, -1467,   543,
     767, -1467, -1467,   -41,   -35,   -15,    20,    25,    27,   -18,
      23,    26,    68,    71,    73,    74,    78, -1467,   -61,   -58,
     -55,    30, -1467, -1467,    33, -1467,    40, -1467,    43,    84,
      45, -1467, -1467,    51,    53,    56,    61,    63, -1467,    66,
   -1467,    85, -1467, -1467, -1467, -1467, -1467,    86, -1467,    89,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,   545,
     748, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467,   465, -1467,   247, -1467,  -768,   253, -1467,
   -1467, -1466, -1467, -1402, -1467, -1467, -1467, -1467,   -43, -1467,
    -804, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1091, -1467, -1090, -1467, -1089, -1467,
     151, -1467, -1467, -1467, -1467, -1467, -1467,   230, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467,   243,  -787, -1467, -1467, -1467,
   -1467,   238, -1467, -1467, -1467, -1467, -1467, -1467, -1467,   206,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467,   228, -1467, -1467,
   -1467,   235,   728, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
     220, -1467, -1467, -1467, -1467, -1467, -1467, -1068, -1467, -1467,
   -1467,   263, -1467, -1467, -1467,   266,   781, -1467, -1467, -1062,
   -1467, -1057, -1467,    79, -1467,    98, -1467,   102, -1467,   106,
   -1467,    91,    92,    96, -1467, -1052, -1467, -1467, -1467, -1467,
     258, -1467, -1467,    -8,  1276, -1467, -1467, -1467, -1467, -1467,
     267, -1467, -1467, -1467,   270, -1467,   752, -1467,   -62, -1467,
   -1467, -1467, -1467, -1467,   -59, -1467, -1467, -1467, -1467, -1467,
     -25, -1467, -1467, -1467,   268, -1467, -1467, -1467,   269, -1467,
     762, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467,   207, -1467, -1467, -1467,   211,
     782, -1467, -1467,   -54,   -48, -1467,     7, -1467, -1467, -1467,
   -1467, -1467,   208, -1467, -1467, -1467,   209,   783, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467,   -36, -1467, -1467, -1467,   259,
   -1467, -1467, -1467,   260, -1467,   785,   535, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1051, -1467, -1467, -1467, -1467, -1467, -1467,   275,
   -1467, -1467, -1467,     1, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467,   248, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,   237, -1467,
   -1467,    -7, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467,   -66, -1467, -1467,   -99, -1467,
   -1467, -1467, -1467, -1467,   -53, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467,  -119, -1467, -1467,  -133,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467,   265, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,   586,   772,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467,   627,   786, -1467,
   -1467, -1467, -1467, -1467, -1467,   272, -1467, -1467,    19, -1467,
   -1467, -1467, -1467, -1467, -1467,   -44, -1467, -1467,   -84, -1467,
   -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467, -1467,   274,
   -1467
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     805,    87,    88,    41,    68,    84,    85,   825,  1039,  1149,
    1150,   894,    43,    70,    90,   478,    91,    45,    71,   166,
     167,   168,   481,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   508,   790,   188,   509,   189,   510,   190,   191,
     192,   524,   802,   193,   194,   195,   196,   197,   545,   198,
     546,   199,   200,   201,   202,   502,   203,   204,   522,   205,
     523,   206,   207,   208,   209,   210,   483,    47,    72,   246,
     247,   248,   556,   249,   250,   251,   252,   211,   484,   212,
     485,   213,   486,   922,   923,   924,  1079,   895,   896,   897,
    1054,   898,  1055,   899,  1056,   900,  1057,   901,   902,   600,
     903,   904,   905,   906,   907,   908,   909,   910,   911,  1068,
    1348,   912,   913,   914,   915,  1071,   916,  1072,   917,  1073,
     918,  1074,   919,  1075,   214,   534,   957,   958,   959,  1099,
     960,  1100,   215,   531,   943,   944,   945,   946,   216,   533,
     951,   952,   953,   954,   217,   532,   218,   541,  1007,  1008,
    1009,  1010,  1011,   219,   537,   970,   971,   972,  1109,    63,
      80,   442,   443,   444,   615,   445,   616,   220,   538,   979,
     980,   981,   982,   983,   984,   985,   986,   221,   518,   926,
     927,   928,  1082,    49,    73,   300,   301,   302,   565,   303,
     566,   304,   567,   305,   573,   306,   570,   307,   571,   308,
     572,   222,   223,   224,   312,   313,   225,   525,   938,   939,
     940,  1091,  1235,  1236,   226,   519,    57,    77,   930,   931,
     932,  1085,    59,    78,   403,   404,   405,   406,   407,   408,
     409,   599,   410,   603,   411,   602,   412,   413,   604,   414,
     227,   520,   934,   935,   936,  1088,    61,    79,   426,   427,
     428,   429,   430,   608,   431,   432,   433,   434,   435,   436,
     612,   315,   563,  1041,  1042,  1043,  1151,    51,    74,   343,
     344,   345,   577,   346,   228,   526,   229,   527,   318,   564,
    1045,  1046,  1047,  1154,    53,    75,   363,   364,   365,   581,
     366,   367,   583,   368,   369,   230,   536,   966,   967,   968,
    1106,    55,    76,   382,   383,   384,   385,   589,   386,   590,
     387,   591,   388,   592,   389,   593,   390,   594,   391,   595,
     392,   588,   320,   574,  1049,   231,   535,   962,   963,   964,
    1103,  1262,  1263,  1264,  1265,  1266,  1362,  1267,  1363,  1268,
    1269,   232,   539,   996,   997,   998,  1120,  1373,   999,  1000,
    1121,  1001,  1002,   233,   234,   542,  1015,  1016,  1017,  1132,
    1305,  1306,  1307,  1375,  1417,  1308,  1376,  1309,  1377,  1310,
    1311,  1312,  1381,  1438,  1439,  1440,  1450,  1466,  1467,  1468,
    1488,  1313,  1379,  1431,  1432,  1433,  1444,  1484,  1434,  1445,
    1435,  1446,  1436,  1447,  1499,  1500,  1501,  1510,  1523,  1524,
    1525,  1528,  1526,  1529,   235,   543,  1024,  1025,  1026,  1027,
    1136,  1028,  1029,  1138,   236,   544,    65,    81,   457,   458,
     459,   460,   620,   461,   462,   622,   463,   464,   465,   625,
     860,   466,   626,   237,   482,    67,    82,   469,   470,   471,
     629,   472,   238,   551,  1032,  1033,  1142,  1327,  1328,  1329,
    1330,  1388,  1331,  1386,  1442,  1443,  1453,  1475,  1476,  1477,
    1491,  1478,  1479,  1480,  1481,  1495,   239,   552,  1036,  1037,
    1038
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     165,   245,   267,   323,   354,   378,    38,   401,   422,   441,
     454,   993,   282,   324,   920,   283,   325,   424,   284,   326,
     425,   360,   950,  1224,   253,   316,   347,   361,   380,  1225,
     415,   437,   268,   455,  1226,   402,   423,   319,   269,  1234,
    1240,  1300,  1301,  1302,  1519,   137,   138,  1034,   314,   342,
     359,   379,   941,  1094,    30,   274,  1095,    86,   270,   439,
     440,   479,   164,   130,  1519,   804,   480,   395,   417,   396,
     397,   418,   419,   420,   785,   786,   787,   788,   473,   254,
     317,   348,   362,   381,    42,   416,   438,    31,   456,    32,
      44,    33,   475,   271,   137,   138,   275,   554,   272,   276,
     273,   476,   555,   285,   327,    89,   286,   328,  1520,   487,
     421,  1424,   789,   287,   329,   561,   288,   330,   290,   331,
     562,  1018,  1019,  1020,   291,   332,   292,   333,  1520,   293,
     334,   467,   468,   987,   294,   335,   295,   336,   872,   296,
     337,   277,   868,   869,   278,   804,   279,   280,    46,   942,
     164,   281,    48,   338,   355,   394,   575,   289,   297,   298,
     474,   576,   299,   579,   309,   310,   439,   440,   580,   311,
     586,  1021,   339,   356,   617,   587,   340,   357,   477,   618,
     341,   358,   240,   241,   242,   243,   244,   867,   868,   869,
     870,   871,   872,   873,   874,   875,   876,   877,   878,   879,
     880,   881,   137,   138,   488,   882,   883,   884,   885,   886,
     887,   888,   889,   890,   891,   892,   893,    50,   627,   395,
     164,   396,   397,   628,   137,   138,   398,   399,   400,   137,
     138,    52,   137,   138,   395,   631,   395,   858,   859,   554,
     632,   884,   885,   886,  1051,   631,   137,   138,    54,  1097,
    1052,   395,  1098,    98,    99,   100,   101,   102,   103,    56,
     561,   137,   138,   137,   138,  1053,  1345,  1346,  1347,  1425,
    1426,  1427,   988,   989,   990,   991,   798,   799,   800,   801,
      58,   137,   138,  1003,  1004,  1005,   131,   395,   955,   956,
    1224,  1300,  1301,  1302,  1470,    60,  1225,  1471,  1472,  1473,
    1474,  1226,  1516,  1517,  1076,  1143,  1234,  1240,  1144,  1077,
     950,  1182,   137,   138,   137,   138,   131,  1076,  1370,  1371,
    1372,   993,  1078,    34,    35,    36,    37,  1101,   164,  1414,
    1415,  1416,  1102,  1247,  1248,  1249,  1250,  1461,    62,   349,
     350,   351,   352,   353,   137,   138,   137,   138,  1118,  1125,
     164,  1130,  1139,  1119,  1126,   164,  1131,  1140,   164,   627,
     262,   263,   264,  1320,  1141,  1321,  1322,   265,   322,    64,
    1292,    66,   164,   489,  1293,  1294,  1295,  1296,   973,   974,
     975,   976,   977,   978,  1297,  1298,   490,   164,   491,   164,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   164,   492,   493,   164,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   941,   948,   131,   949,   494,   446,   447,   448,   449,
     450,   451,   452,   453,  1146,   133,   134,   135,   164,  1147,
     164,  1076,   575,   255,  1358,   256,  1354,  1355,   495,  1359,
     496,   137,   138,   257,   258,   259,   260,   261,   139,   140,
     141,   617,   596,   497,   633,   634,  1369,   262,   263,   264,
     164,   498,   164,  1382,   265,   499,   147,   500,  1383,   501,
     831,   832,   833,   165,   266,   503,  1389,   579,   586,  1448,
     245,  1390,  1392,  1393,  1449,   839,   840,   841,   842,   504,
    1489,  1496,  1530,   597,   267,  1490,  1497,  1531,   323,  1454,
     598,   505,  1455,   253,   282,   354,   853,   283,   324,   506,
     284,   325,   507,   511,   326,   512,   378,   316,   513,   514,
     515,   347,   360,   516,   268,   517,   401,   521,   361,   319,
     269,   528,   529,   422,   606,   530,   156,   157,   540,   380,
     314,   547,   424,   548,   342,   425,   454,   274,   549,   415,
     270,   359,   550,   553,   402,   557,   437,   558,   254,   559,
     560,   423,   379,   568,   569,   613,   578,   164,   582,   455,
     584,   585,   317,   601,   605,   607,   348,   887,   888,   889,
     890,   891,   892,   362,   609,   271,   610,   611,   275,   614,
     272,   276,   273,   619,   381,   285,   621,   623,   286,   327,
     624,   630,   328,   635,   416,   287,   636,   637,   288,   329,
     290,   438,   330,   638,   331,   639,   291,   640,   292,   641,
     332,   293,   333,   642,   456,   334,   294,   643,   295,   644,
     335,   296,   336,   277,   651,   337,   278,   645,   279,   280,
     646,   647,   648,   281,   649,   650,   658,   652,   338,   289,
     297,   298,   653,   654,   299,   355,   309,   310,   655,   657,
     131,   311,   656,   664,   659,   660,   665,   339,   661,   662,
     663,   340,   666,   669,   356,   341,   667,   668,   357,   670,
     671,   672,   358,   674,   673,   675,   676,   677,   137,   138,
     678,   679,   680,   681,   682,   683,   165,   684,   685,   245,
     686,   687,   688,   689,   370,   690,   691,   692,   693,   694,
     695,   696,   697,   698,   371,   372,   373,   374,   375,   376,
     377,   699,   253,   700,   701,   702,   703,   704,   705,   707,
     706,   708,   710,   713,   992,  1006,   714,   711,   454,   712,
     716,   717,  1035,   718,   719,   720,   721,   722,   723,   724,
     725,   726,   727,   729,   730,   732,   863,   994,  1012,   733,
    1022,   455,   734,   738,   735,   739,   736,   740,   371,   741,
     742,   743,   744,   745,   747,    92,    93,   254,   748,    94,
     749,   750,   751,   752,   753,    95,    96,    97,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,   755,   759,   761,   762,   765,   756,   767,   757,
     766,   770,   995,  1013,   164,  1023,   456,   768,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   758,   771,   764,   773,   769,   776,   774,   777,
     783,   778,   132,   133,   134,   135,   779,   780,   781,   782,
     136,   784,   791,   792,   793,   794,   795,   796,   797,   137,
     138,   803,    32,   807,   806,   808,   139,   140,   141,   142,
     143,   144,   145,   809,   810,   146,   811,   812,   813,   820,
     861,   814,   815,   816,   147,   817,   818,   821,   819,   822,
     823,   824,   826,   148,   827,   828,   149,   829,   830,   834,
     835,   836,   862,   150,   837,   838,   843,   921,   925,   929,
     933,   151,   152,   844,   845,   846,   153,   847,   937,   961,
     965,   848,   969,  1014,  1031,  1040,  1044,  1058,   849,  1059,
    1060,   850,   851,   852,   154,   854,   856,   857,   155,  1061,
    1062,  1063,  1064,  1065,  1066,  1067,  1069,  1070,  1081,  1483,
    1080,  1084,  1083,  1086,   156,   157,   158,   159,   160,   161,
     162,  1087,  1089,  1090,  1093,  1092,  1105,  1164,  1096,   163,
    1104,  1107,  1108,  1110,  1111,  1148,  1112,  1113,  1114,  1115,
    1116,   267,  1117,  1122,   401,   164,  1123,   422,  1124,  1127,
    1190,   282,  1128,  1129,   283,  1135,   424,   284,  1133,   425,
    1205,  1134,  1251,  1206,   316,   378,  1207,   415,   441,  1137,
     437,   268,   402,  1238,  1145,   423,   319,   269,  1223,  1152,
    1191,  1153,  1155,  1156,   992,  1260,  1192,   314,   380,  1006,
    1258,  1299,  1252,  1157,   274,  1158,  1237,   270,  1253,  1159,
    1160,  1323,  1161,  1197,  1162,  1035,  1193,   994,  1259,  1163,
     323,   379,  1012,   354,  1303,  1165,  1166,  1167,  1254,   317,
     324,  1022,   416,   325,  1325,   438,   326,  1168,  1239,  1324,
     360,  1173,   271,   347,  1174,   275,   361,   272,   276,   273,
    1261,  1194,   285,   381,  1198,   286,  1195,  1199,  1196,  1169,
    1170,  1208,   287,  1255,  1209,   288,   342,   290,  1256,   359,
    1257,  1210,   995,   291,  1211,   292,  1213,  1013,   293,  1304,
    1176,  1171,  1214,   294,  1215,   295,  1023,  1216,   296,  1326,
     277,  1177,  1217,   278,  1218,   279,   280,  1219,   348,  1200,
     281,   362,  1201,  1172,  1202,  1203,   289,   297,   298,  1204,
    1227,   299,  1178,   309,   310,  1212,  1220,  1221,   311,  1175,
    1222,   327,  1231,  1232,   328,  1179,  1180,  1233,  1244,  1228,
    1245,   329,  1275,  1229,   330,  1282,   331,  1230,  1283,  1276,
    1277,  1278,   332,  1279,   333,  1280,  1284,   334,  1316,  1318,
    1356,  1336,   335,  1335,   336,  1364,  1365,   337,  1357,  1367,
    1420,  1285,  1286,  1366,  1289,  1288,  1290,  1315,  1368,  1317,
     338,  1378,  1380,   355,  1387,  1395,  1396,  1400,  1401,  1341,
    1333,  1342,  1402,  1404,  1406,  1408,  1410,  1452,  1343,   339,
    1421,  1344,   356,   340,  1349,  1397,   357,   341,  1350,  1422,
     358,  1351,  1437,  1441,  1353,  1360,  1361,  1374,  1384,  1451,
    1391,  1456,  1457,  1403,  1398,  1409,  1405,  1412,  1413,  1418,
    1419,  1458,  1423,  1459,  1492,  1485,  1486,  1190,  1487,  1493,
    1494,  1498,  1502,  1504,  1506,  1505,  1251,  1205,  1507,  1508,
    1206,  1512,  1511,  1207,  1513,  1514,  1532,  1533,  1385,   715,
    1238,  1299,  1515,  1535,  1536,  1223,   947,  1191,  1323,  1260,
     864,   709,   855,  1192,  1258,   866,  1252,  1050,  1183,  1181,
    1352,  1246,  1253,  1237,  1303,  1243,  1291,  1242,  1281,  1274,
    1197,  1325,  1259,  1193,  1273,   763,  1324,  1185,  1184,  1428,
    1394,  1241,  1254,   393,  1187,  1186,   728,  1188,  1189,   754,
    1338,   731,  1337,  1339,  1340,  1239,  1271,  1272,  1399,   737,
    1048,  1314,  1429,  1287,  1261,  1407,   760,  1428,  1194,  1462,
    1270,  1198,   746,  1195,  1199,  1196,  1469,  1255,  1208,  1304,
    1503,  1209,  1256,  1527,  1257,  1460,  1326,  1534,  1210,   772,
    1429,  1211,  1464,  1213,  1319,  1030,   865,  1463,  1411,  1214,
    1482,  1215,  1509,     0,  1216,  1332,     0,   775,  1462,  1217,
    1334,  1218,     0,     0,  1219,     0,  1200,  1430,     0,  1201,
       0,  1202,  1203,     0,     0,     0,  1204,  1227,     0,  1518,
       0,  1464,  1212,  1220,  1221,     0,  1463,  1222,     0,  1231,
    1232,     0,     0,     0,  1233,  1430,  1228,  1465,     0,  1518,
    1229,     0,  1521,     0,  1230,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1521,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1465,     0,     0,     0,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,     0,     0,     0,  1522,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,     0,   131,   395,     0,     0,  1522,     0,     0,
       0,     0,     0,     0,     0,   133,   134,   135,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   137,   138,     0,   258,   259,     0,   261,   139,   140,
     141,     0,     0,     0,     0,     0,     0,   262,   263,   264,
       0,     0,     0,     0,   265,     0,     0,   116,   117,   118,
     119,   120,   121,   122,   266,   124,   125,   126,   127,     0,
       0,     0,   131,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   135,     0,     0,     0,
       0,     0,     0,   321,     0,     0,     0,     0,     0,     0,
     137,   138,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   262,   263,   264,     0,
       0,     0,     0,   265,   322,     0,   156,   157,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   164,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   156,   157,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   164
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   815,    73,    74,   782,    73,    74,    79,    73,    74,
      79,    75,   809,  1091,    72,    73,    74,    75,    76,  1091,
      78,    79,    73,    81,  1091,    78,    79,    73,    73,  1091,
    1091,  1132,  1132,  1132,  1510,   115,   116,   226,    73,    74,
      75,    76,   144,     3,     0,    73,     6,   241,    73,   150,
     151,     3,   241,    86,  1530,   682,     8,    88,    89,    90,
      91,    92,    93,    94,   206,   207,   208,   209,     6,    72,
      73,    74,    75,    76,     7,    78,    79,     5,    81,     7,
       7,     9,     4,    73,   115,   116,    73,     3,    73,    73,
      73,     8,     8,    73,    74,    10,    73,    74,  1510,     4,
     131,    24,   244,    73,    74,     3,    73,    74,    73,    74,
       8,   191,   192,   193,    73,    74,    73,    74,  1530,    73,
      74,    13,    14,    24,    73,    74,    73,    74,    29,    73,
      74,    73,    25,    26,    73,   762,    73,    73,     7,   241,
     241,    73,     7,    74,    75,    24,     3,    73,    73,    73,
       3,     8,    73,     3,    73,    73,   150,   151,     8,    73,
       3,   241,    74,    75,     3,     8,    74,    75,     3,     8,
      74,    75,    16,    17,    18,    19,    20,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,   115,   116,     4,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,     7,     3,    88,
     241,    90,    91,     8,   115,   116,    95,    96,    97,   115,
     116,     7,   115,   116,    88,     3,    88,   203,   204,     3,
       8,    44,    45,    46,     8,     3,   115,   116,     7,     3,
       8,    88,     6,    54,    55,    56,    57,    58,    59,     7,
       3,   115,   116,   115,   116,     8,    39,    40,    41,   182,
     183,   184,   163,   164,   165,   166,   102,   103,   104,   105,
       7,   115,   116,   169,   170,   171,    87,    88,   129,   130,
    1358,  1382,  1382,  1382,   218,     7,  1358,   221,   222,   223,
     224,  1358,   185,   186,     3,     3,  1358,  1358,     6,     8,
    1097,  1079,   115,   116,   115,   116,    87,     3,   160,   161,
     162,  1125,     8,   241,   242,   243,   244,     3,   241,   174,
     175,   176,     8,   134,   135,   136,   137,   189,     7,   110,
     111,   112,   113,   114,   115,   116,   115,   116,     3,     3,
     241,     3,     3,     8,     8,   241,     8,     8,   241,     3,
     131,   132,   133,   217,     8,   219,   220,   138,   139,     7,
     173,     7,   241,     4,   177,   178,   179,   180,   153,   154,
     155,   156,   157,   158,   187,   188,     4,   241,     4,   241,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,   241,     4,     4,   241,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,   144,   145,    87,   147,     4,   195,   196,   197,   198,
     199,   200,   201,   202,     3,    99,   100,   101,   241,     8,
     241,     3,     3,   107,     3,   109,     8,     8,     4,     8,
       4,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,     3,     8,     4,   474,   475,     8,   131,   132,   133,
     241,     4,   241,     3,   138,     4,   140,     4,     8,     4,
     723,   724,   725,   554,   148,     4,     3,     3,     3,     3,
     561,     8,     8,     8,     8,   738,   739,   740,   741,     4,
       3,     3,     3,     3,   575,     8,     8,     8,   579,     3,
       8,     4,     6,   561,   575,   586,   759,   575,   579,     4,
     575,   579,     4,     4,   579,     4,   597,   575,     4,     4,
       4,   579,   586,     4,   575,     4,   607,     4,   586,   575,
     575,     4,     4,   614,     8,     4,   210,   211,     4,   597,
     575,     4,   614,     4,   579,   614,   627,   575,     4,   607,
     575,   586,     4,     4,   607,     4,   614,     4,   561,     4,
       4,   614,   597,     4,     4,     8,     4,   241,     4,   627,
       4,     4,   575,     4,     4,     3,   579,    47,    48,    49,
      50,    51,    52,   586,     4,   575,     4,     4,   575,     3,
     575,   575,   575,     4,   597,   575,     4,     4,   575,   579,
       4,     4,   579,   241,   607,   575,     4,     4,   575,   579,
     575,   614,   579,     4,   579,     4,   575,     4,   575,     4,
     579,   575,   579,     4,   627,   579,   575,   242,   575,   242,
     579,   575,   579,   575,   244,   579,   575,   242,   575,   575,
     242,   242,   242,   575,   242,   242,     4,   243,   579,   575,
     575,   575,   243,   243,   575,   586,   575,   575,   242,   242,
      87,   575,   243,     4,   242,   242,     4,   579,   244,   244,
     244,   579,     4,   243,   586,   579,   244,   244,   586,   242,
     242,   242,   586,     4,   244,     4,     4,   242,   115,   116,
       4,     4,     4,     4,     4,     4,   777,   244,   244,   780,
     244,     4,     4,     4,   131,     4,     4,     4,     4,     4,
       4,   242,     4,     4,   141,   142,   143,   144,   145,   146,
     147,     4,   780,     4,     4,     4,   244,   244,   244,     4,
     244,     4,     4,   242,   815,   816,   242,   244,   819,   244,
       4,     4,   823,     4,     4,     4,   242,   244,     4,     4,
       4,     4,     4,     4,   242,     4,   776,   815,   816,   242,
     818,   819,     4,     4,   242,     4,   242,     4,   141,     4,
       4,     4,     4,     4,     4,    11,    12,   780,     4,    15,
     242,     4,     4,     4,   244,    21,    22,    23,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,     4,     4,     4,     4,     4,   244,     4,   244,
     242,     4,   815,   816,   241,   818,   819,   242,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,   244,     4,   244,     4,   242,     4,   242,     7,
       5,   241,    98,    99,   100,   101,     7,     7,     7,     7,
     106,   241,   241,   241,     5,     5,     5,   241,   241,   115,
     116,     5,     7,     5,   241,     5,   122,   123,   124,   125,
     126,   127,   128,     5,     7,   131,     5,     5,     5,   241,
     205,     7,     7,     7,   140,     5,     7,   241,     7,     5,
       7,     5,     5,   149,     5,   241,   152,   241,   241,   241,
       7,   241,     5,   159,   241,   241,   241,     7,     7,     7,
       7,   167,   168,   241,   241,   241,   172,   241,     7,     7,
       7,   241,     7,     7,     7,     7,     7,     4,   241,     4,
       4,   241,   241,   241,   190,   241,   241,   241,   194,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,   181,
       6,     3,     6,     6,   210,   211,   212,   213,   214,   215,
     216,     3,     6,     3,     3,     6,     3,   244,     6,   225,
       6,     6,     3,     6,     3,   241,     4,     4,     4,     4,
       4,  1082,     4,     4,  1085,   241,     4,  1088,     4,     4,
    1091,  1082,     4,     4,  1082,     4,  1088,  1082,     6,  1088,
    1091,     3,  1103,  1091,  1082,  1106,  1091,  1085,  1109,     4,
    1088,  1082,  1085,  1091,     4,  1088,  1082,  1082,  1091,     6,
    1091,     3,     6,     3,  1125,  1103,  1091,  1082,  1106,  1130,
    1103,  1132,  1103,     8,  1082,     6,  1091,  1082,  1103,     4,
       4,  1142,     4,  1091,     4,  1146,  1091,  1125,  1103,   242,
    1151,  1106,  1130,  1154,  1132,   242,   244,   242,  1103,  1082,
    1151,  1139,  1085,  1151,  1142,  1088,  1151,   242,  1091,  1142,
    1154,     4,  1082,  1151,   244,  1082,  1154,  1082,  1082,  1082,
    1103,  1091,  1082,  1106,  1091,  1082,  1091,  1091,  1091,   242,
     242,  1091,  1082,  1103,  1091,  1082,  1151,  1082,  1103,  1154,
    1103,  1091,  1125,  1082,  1091,  1082,  1091,  1130,  1082,  1132,
       4,   242,  1091,  1082,  1091,  1082,  1139,  1091,  1082,  1142,
    1082,     4,  1091,  1082,  1091,  1082,  1082,  1091,  1151,  1091,
    1082,  1154,  1091,   242,  1091,  1091,  1082,  1082,  1082,  1091,
    1091,  1082,     4,  1082,  1082,  1091,  1091,  1091,  1082,   242,
    1091,  1151,  1091,  1091,  1151,     4,     4,  1091,     4,  1091,
       4,  1151,   242,  1091,  1151,     4,  1151,  1091,     4,   242,
     242,   242,  1151,   242,  1151,   242,   242,  1151,     4,     4,
       8,     3,  1151,     6,  1151,     4,     4,  1151,     8,     3,
       7,   242,   242,     8,   242,   244,   242,   244,     8,   242,
    1151,     4,     4,  1154,     4,     4,     4,     4,     4,   241,
     244,   241,     4,     4,     4,     4,     4,     3,   241,  1151,
       5,   241,  1154,  1151,   241,   244,  1154,  1151,   241,     5,
    1154,   241,     7,     7,   241,   241,   241,   241,   241,     6,
     241,     4,     4,   242,   244,   242,   244,   241,   241,   241,
     241,     4,   241,     4,     4,   241,   241,  1358,     5,     4,
       4,     7,     4,     4,   242,   244,  1367,  1358,   242,     4,
    1358,     3,     6,  1358,   241,   241,     4,     4,  1318,   561,
    1358,  1382,   241,   241,   241,  1358,   808,  1358,  1389,  1367,
     777,   554,   762,  1358,  1367,   780,  1367,   862,  1081,  1076,
    1179,  1101,  1367,  1358,  1382,  1097,  1130,  1094,  1118,  1111,
    1358,  1389,  1367,  1358,  1109,   617,  1389,  1084,  1082,  1420,
    1358,  1093,  1367,    77,  1087,  1085,   575,  1088,  1090,   607,
    1153,   579,  1151,  1154,  1156,  1358,  1106,  1108,  1367,   586,
     835,  1134,  1420,  1125,  1367,  1382,   614,  1448,  1358,  1450,
    1105,  1358,   597,  1358,  1358,  1358,  1452,  1367,  1358,  1382,
    1489,  1358,  1367,  1512,  1367,  1448,  1389,  1530,  1358,   627,
    1448,  1358,  1450,  1358,  1139,   819,   779,  1450,  1389,  1358,
    1454,  1358,  1496,    -1,  1358,  1143,    -1,   631,  1489,  1358,
    1146,  1358,    -1,    -1,  1358,    -1,  1358,  1420,    -1,  1358,
      -1,  1358,  1358,    -1,    -1,    -1,  1358,  1358,    -1,  1510,
      -1,  1489,  1358,  1358,  1358,    -1,  1489,  1358,    -1,  1358,
    1358,    -1,    -1,    -1,  1358,  1448,  1358,  1450,    -1,  1530,
    1358,    -1,  1510,    -1,  1358,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1530,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1489,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    -1,    -1,    -1,  1510,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    -1,    87,    88,    -1,    -1,  1530,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    99,   100,   101,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   115,   116,    -1,   118,   119,    -1,   121,   122,   123,
     124,    -1,    -1,    -1,    -1,    -1,    -1,   131,   132,   133,
      -1,    -1,    -1,    -1,   138,    -1,    -1,    72,    73,    74,
      75,    76,    77,    78,   148,    80,    81,    82,    83,    -1,
      -1,    -1,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,
      -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,    -1,    -1,
     115,   116,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   131,   132,   133,    -1,
      -1,    -1,    -1,   138,   139,    -1,   210,   211,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   241,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   210,   211,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   241
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
       0,     5,     7,     9,   241,   242,   243,   244,   261,   262,
     263,   268,     7,   277,     7,   282,     7,   342,     7,   458,
       7,   542,     7,   559,     7,   576,     7,   491,     7,   497,
       7,   521,     7,   434,     7,   691,     7,   710,   269,   264,
     278,   283,   343,   459,   543,   560,   577,   492,   498,   522,
     435,   692,   711,   261,   270,   271,   241,   266,   267,    10,
     279,   281,    11,    12,    15,    21,    22,    23,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    98,    99,   100,   101,   106,   115,   116,   122,
     123,   124,   125,   126,   127,   128,   131,   140,   149,   152,
     159,   167,   168,   172,   190,   194,   210,   211,   212,   213,
     214,   215,   216,   225,   241,   276,   284,   285,   286,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   309,   311,
     313,   314,   315,   318,   319,   320,   321,   322,   324,   326,
     327,   328,   329,   331,   332,   334,   336,   337,   338,   339,
     340,   352,   354,   356,   399,   407,   413,   419,   421,   428,
     442,   452,   476,   477,   478,   481,   489,   515,   549,   551,
     570,   600,   616,   628,   629,   679,   689,   708,   717,   741,
      16,    17,    18,    19,    20,   276,   344,   345,   346,   348,
     349,   350,   351,   549,   551,   107,   109,   117,   118,   119,
     120,   121,   131,   132,   133,   138,   148,   276,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   303,   304,   305,   306,   309,   311,   313,   314,
     315,   318,   319,   320,   321,   322,   324,   326,   332,   334,
     460,   461,   462,   464,   466,   468,   470,   472,   474,   476,
     477,   478,   479,   480,   515,   536,   549,   551,   553,   570,
     597,   108,   139,   276,   303,   304,   305,   306,   309,   311,
     313,   315,   318,   319,   320,   321,   322,   324,   468,   470,
     472,   474,   515,   544,   545,   546,   548,   549,   551,   110,
     111,   112,   113,   114,   276,   468,   470,   472,   474,   515,
     548,   549,   551,   561,   562,   563,   565,   566,   568,   569,
     131,   141,   142,   143,   144,   145,   146,   147,   276,   515,
     549,   551,   578,   579,   580,   581,   583,   585,   587,   589,
     591,   593,   595,   489,    24,    88,    90,    91,    95,    96,
      97,   276,   373,   499,   500,   501,   502,   503,   504,   505,
     507,   509,   511,   512,   514,   549,   551,    89,    92,    93,
      94,   131,   276,   373,   503,   509,   523,   524,   525,   526,
     527,   529,   530,   531,   532,   533,   534,   549,   551,   150,
     151,   276,   436,   437,   438,   440,   195,   196,   197,   198,
     199,   200,   201,   202,   276,   549,   551,   693,   694,   695,
     696,   698,   699,   701,   702,   703,   706,    13,    14,   712,
     713,   714,   716,     6,     3,     4,     8,     3,   280,     3,
       8,   287,   709,   341,   353,   355,   357,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   330,     4,     4,     4,     4,     4,   307,   310,
     312,     4,     4,     4,     4,     4,     4,     4,   453,   490,
     516,     4,   333,   335,   316,   482,   550,   552,     4,     4,
       4,   408,   420,   414,   400,   601,   571,   429,   443,   617,
       4,   422,   630,   680,   690,   323,   325,     4,     4,     4,
       4,   718,   742,     4,     3,     8,   347,     4,     4,     4,
       4,     3,     8,   537,   554,   463,   465,   467,     4,     4,
     471,   473,   475,   469,   598,     3,     8,   547,     4,     3,
       8,   564,     4,   567,     4,     4,     3,     8,   596,   582,
     584,   586,   588,   590,   592,   594,     8,     3,     8,   506,
     374,     4,   510,   508,   513,     4,     8,     3,   528,     4,
       4,     4,   535,     8,     3,   439,   441,     3,     8,     4,
     697,     4,   700,     4,     4,   704,   707,     3,     8,   715,
       4,     3,     8,   261,   261,   241,     4,     4,     4,     4,
       4,     4,     4,   242,   242,   242,   242,   242,   242,   242,
     242,   244,   243,   243,   243,   242,   243,   242,     4,   242,
     242,   244,   244,   244,     4,     4,     4,   244,   244,   243,
     242,   242,   242,   244,     4,     4,     4,   242,     4,     4,
       4,     4,     4,     4,   244,   244,   244,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   242,     4,     4,     4,
       4,     4,     4,   244,   244,   244,   244,     4,     4,   285,
       4,   244,   244,   242,   242,   345,     4,     4,     4,     4,
       4,   242,   244,     4,     4,     4,     4,     4,   461,     4,
     242,   545,     4,   242,     4,   242,   242,   562,     4,     4,
       4,     4,     4,     4,     4,     4,   580,     4,     4,   242,
       4,     4,     4,   244,   501,     4,   244,   244,   244,     4,
     525,     4,     4,   437,   244,     4,   242,     4,   242,   242,
       4,     4,   694,     4,   242,   713,     4,     7,   241,     7,
       7,     7,     7,     5,   241,   206,   207,   208,   209,   244,
     308,   241,   241,     5,     5,     5,   241,   241,   102,   103,
     104,   105,   317,     5,   263,   265,   241,     5,     5,     5,
       7,     5,     5,     5,     7,     7,     7,     5,     7,     7,
     241,   241,     5,     7,     5,   272,     5,     5,   241,   241,
     241,   272,   272,   272,   241,     7,   241,   241,   241,   272,
     272,   272,   272,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   272,   241,   265,   241,   241,   203,   204,
     705,   205,     5,   261,   284,   712,   344,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,   276,   362,   363,   364,   366,   368,
     370,   372,   373,   375,   376,   377,   378,   379,   380,   381,
     382,   383,   386,   387,   388,   389,   391,   393,   395,   397,
     362,     7,   358,   359,   360,     7,   454,   455,   456,     7,
     493,   494,   495,     7,   517,   518,   519,     7,   483,   484,
     485,   144,   241,   409,   410,   411,   412,   270,   145,   147,
     411,   415,   416,   417,   418,   129,   130,   401,   402,   403,
     405,     7,   602,   603,   604,     7,   572,   573,   574,     7,
     430,   431,   432,   153,   154,   155,   156,   157,   158,   444,
     445,   446,   447,   448,   449,   450,   451,    24,   163,   164,
     165,   166,   276,   375,   549,   551,   618,   619,   620,   623,
     624,   626,   627,   169,   170,   171,   276,   423,   424,   425,
     426,   427,   549,   551,     7,   631,   632,   633,   191,   192,
     193,   241,   549,   551,   681,   682,   683,   684,   686,   687,
     693,     7,   719,   720,   226,   276,   743,   744,   745,   273,
       7,   538,   539,   540,     7,   555,   556,   557,   581,   599,
     358,     8,     8,     8,   365,   367,   369,   371,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   384,     4,
       4,   390,   392,   394,   396,   398,     3,     8,     8,   361,
       6,     3,   457,     6,     3,   496,     6,     3,   520,     6,
       3,   486,     6,     3,     3,     6,     6,     3,     6,   404,
     406,     3,     8,   605,     6,     3,   575,     6,     3,   433,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
     621,   625,     4,     4,     4,     3,     8,     4,     4,     4,
       3,     8,   634,     6,     3,     4,   685,     4,   688,     3,
       8,     8,   721,     3,     6,     4,     3,     8,   241,   274,
     275,   541,     6,     3,   558,     6,     3,     8,     6,     4,
       4,     4,     4,   242,   244,   242,   244,   242,   242,   242,
     242,   242,   242,     4,   244,   242,     4,     4,     4,     4,
       4,   363,   362,   360,   460,   456,   499,   495,   523,   519,
     276,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   303,   304,   305,   306,   309,
     311,   313,   314,   315,   318,   319,   320,   321,   322,   324,
     326,   332,   334,   373,   452,   464,   466,   468,   470,   472,
     474,   476,   477,   478,   480,   487,   488,   515,   549,   551,
     597,   485,   410,   416,     4,     4,   402,   134,   135,   136,
     137,   276,   288,   289,   290,   291,   292,   293,   373,   515,
     549,   551,   606,   607,   608,   609,   610,   612,   614,   615,
     604,   578,   574,   436,   432,   242,   242,   242,   242,   242,
     242,   445,     4,     4,   242,   242,   242,   619,   244,   242,
     242,   424,   173,   177,   178,   179,   180,   187,   188,   276,
     389,   391,   393,   549,   551,   635,   636,   637,   640,   642,
     644,   645,   646,   656,   633,   244,     4,   242,     4,   682,
     217,   219,   220,   276,   373,   549,   551,   722,   723,   724,
     725,   727,   720,   244,   744,     6,     3,   544,   540,   561,
     557,   241,   241,   241,   241,    39,    40,    41,   385,   241,
     241,   241,   395,   241,     8,     8,     8,     8,     3,     8,
     241,   241,   611,   613,     4,     4,     8,     3,     8,     8,
     160,   161,   162,   622,   241,   638,   641,   643,     4,   657,
       4,   647,     3,     8,   241,   261,   728,     4,   726,     3,
       8,   241,     8,     8,   488,     4,     4,   244,   244,   608,
       4,     4,     4,   242,     4,   244,     4,   636,     4,   242,
       4,   723,   241,   241,   174,   175,   176,   639,   241,   241,
       7,     5,     5,   241,    24,   182,   183,   184,   276,   549,
     551,   658,   659,   660,   663,   665,   667,     7,   648,   649,
     650,     7,   729,   730,   661,   664,   666,   668,     3,     8,
     651,     6,     3,   731,     3,     6,     4,     4,     4,     4,
     659,   189,   276,   373,   549,   551,   652,   653,   654,   650,
     218,   221,   222,   223,   224,   732,   733,   734,   736,   737,
     738,   739,   730,   181,   662,   241,   241,     5,   655,     3,
       8,   735,     4,     4,     4,   740,     3,     8,     7,   669,
     670,   671,     4,   653,     4,   244,   242,   242,     4,   733,
     672,     6,     3,   241,   241,   241,   185,   186,   276,   366,
     368,   549,   551,   673,   674,   675,   677,   671,   676,   678,
       3,     8,     4,     4,   674,   241,   241
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
     335,   334,   336,   337,   338,   339,   341,   340,   343,   342,
     344,   344,   344,   345,   345,   345,   345,   345,   345,   345,
     345,   347,   346,   348,   349,   350,   351,   353,   352,   355,
     354,   357,   356,   358,   358,   359,   359,   359,   361,   360,
     362,   362,   362,   363,   363,   363,   363,   363,   363,   363,
     363,   363,   363,   363,   363,   363,   363,   363,   363,   363,
     363,   363,   363,   363,   363,   363,   363,   365,   364,   367,
     366,   369,   368,   371,   370,   372,   374,   373,   375,   376,
     377,   378,   379,   380,   381,   382,   384,   383,   385,   385,
     385,   386,   387,   388,   390,   389,   392,   391,   394,   393,
     396,   395,   395,   395,   395,   395,   395,   398,   397,   400,
     399,   401,   401,   401,   402,   402,   404,   403,   406,   405,
     408,   407,   409,   409,   409,   410,   410,   411,   412,   414,
     413,   415,   415,   415,   416,   416,   416,   417,   418,   420,
     419,   422,   421,   423,   423,   423,   424,   424,   424,   424,
     424,   424,   425,   426,   427,   429,   428,   430,   430,   431,
     431,   431,   433,   432,   435,   434,   436,   436,   436,   436,
     437,   437,   439,   438,   441,   440,   443,   442,   444,   444,
     444,   445,   445,   445,   445,   445,   445,   446,   447,   448,
     449,   450,   451,   453,   452,   454,   454,   455,   455,   455,
     457,   456,   459,   458,   460,   460,   460,   461,   461,   461,
     461,   461,   461,   461,   461,   461,   461,   461,   461,   461,
     461,   461,   461,   461,   461,   461,   461,   461,   461,   461,
     461,   461,   461,   461,   461,   461,   461,   461,   461,   461,
     461,   461,   461,   461,   461,   461,   461,   461,   461,   461,
     461,   461,   461,   461,   461,   461,   461,   461,   461,   463,
     462,   465,   464,   467,   466,   469,   468,   471,   470,   473,
     472,   475,   474,   476,   477,   478,   479,   480,   482,   481,
     483,   483,   484,   484,   484,   486,   485,   487,   487,   487,
     488,   488,   488,   488,   488,   488,   488,   488,   488,   488,
     488,   488,   488,   488,   488,   488,   488,   488,   488,   488,
     488,   488,   488,   488,   488,   488,   488,   488,   488,   488,
     488,   488,   488,   488,   488,   488,   488,   488,   488,   488,
     488,   488,   488,   488,   488,   488,   488,   488,   488,   490,
     489,   492,   491,   493,   493,   494,   494,   494,   496,   495,
     498,   497,   499,   499,   500,   500,   500,   501,   501,   501,
     501,   501,   501,   501,   501,   501,   501,   502,   503,   504,
     506,   505,   508,   507,   510,   509,   511,   513,   512,   514,
     516,   515,   517,   517,   518,   518,   518,   520,   519,   522,
     521,   523,   523,   524,   524,   524,   525,   525,   525,   525,
     525,   525,   525,   525,   525,   525,   525,   526,   528,   527,
     529,   530,   531,   532,   533,   535,   534,   537,   536,   538,
     538,   539,   539,   539,   541,   540,   543,   542,   544,   544,
     544,   545,   545,   545,   545,   545,   545,   545,   545,   545,
     545,   545,   545,   545,   545,   545,   545,   545,   545,   545,
     545,   545,   545,   545,   545,   547,   546,   548,   550,   549,
     552,   551,   554,   553,   555,   555,   556,   556,   556,   558,
     557,   560,   559,   561,   561,   561,   562,   562,   562,   562,
     562,   562,   562,   562,   562,   562,   562,   562,   562,   562,
     564,   563,   565,   567,   566,   568,   569,   571,   570,   572,
     572,   573,   573,   573,   575,   574,   577,   576,   578,   578,
     579,   579,   579,   580,   580,   580,   580,   580,   580,   580,
     580,   580,   580,   580,   580,   582,   581,   584,   583,   586,
     585,   588,   587,   590,   589,   592,   591,   594,   593,   596,
     595,   598,   597,   599,   601,   600,   602,   602,   603,   603,
     603,   605,   604,   606,   606,   607,   607,   607,   608,   608,
     608,   608,   608,   608,   608,   608,   608,   608,   608,   608,
     608,   608,   608,   609,   611,   610,   613,   612,   614,   615,
     617,   616,   618,   618,   618,   619,   619,   619,   619,   619,
     619,   619,   619,   619,   621,   620,   622,   622,   622,   623,
     625,   624,   626,   627,   628,   630,   629,   631,   631,   632,
     632,   632,   634,   633,   635,   635,   635,   636,   636,   636,
     636,   636,   636,   636,   636,   636,   636,   636,   636,   636,
     638,   637,   639,   639,   639,   641,   640,   643,   642,   644,
     645,   647,   646,   648,   648,   649,   649,   649,   651,   650,
     652,   652,   652,   653,   653,   653,   653,   653,   655,   654,
     657,   656,   658,   658,   658,   659,   659,   659,   659,   659,
     659,   659,   661,   660,   662,   664,   663,   666,   665,   668,
     667,   669,   669,   670,   670,   670,   672,   671,   673,   673,
     673,   674,   674,   674,   674,   674,   674,   674,   676,   675,
     678,   677,   680,   679,   681,   681,   681,   682,   682,   682,
     682,   682,   682,   683,   685,   684,   686,   688,   687,   690,
     689,   692,   691,   693,   693,   693,   694,   694,   694,   694,
     694,   694,   694,   694,   694,   694,   694,   695,   697,   696,
     698,   700,   699,   701,   702,   704,   703,   705,   705,   707,
     706,   709,   708,   711,   710,   712,   712,   712,   713,   713,
     715,   714,   716,   718,   717,   719,   719,   719,   721,   720,
     722,   722,   722,   723,   723,   723,   723,   723,   723,   723,
     724,   726,   725,   728,   727,   729,   729,   729,   731,   730,
     732,   732,   732,   733,   733,   733,   733,   733,   735,   734,
     736,   737,   738,   740,   739,   742,   741,   743,   743,   743,
     744,   744,   745
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
       0,     4,     3,     3,     3,     3,     0,     6,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     3,     3,     3,     0,     6,     0,
       6,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     1,     1,
       1,     3,     3,     3,     0,     4,     0,     4,     0,     4,
       0,     4,     1,     1,     1,     1,     1,     0,     4,     0,
       6,     1,     3,     2,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     0,
       6,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     1,     3,     2,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     3,     3,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
       4,     0,     6,     1,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     1,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     3,     3,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     3,
       0,     4,     3,     3,     3,     0,     6,     0,     1,     1,
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
  "\"ddns-ttl-max\"", "\"store-extended-info\"", "\"subnet6\"",
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
  "\"thread-pool-size\"", "\"packet-queue-size\"", "\"control-sockets\"",
  "\"socket-type\"", "\"unix\"", "\"http\"", "\"https\"",
  "\"socket-name\"", "\"socket-address\"", "\"socket-port\"",
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
  "ddns_update_on_renew", "ddns_use_conflict_resolution",
  "ddns_conflict_resolution_mode", "$@25",
  "ddns_conflict_resolution_mode_value", "ddns_ttl_percent", "ddns_ttl",
  "ddns_ttl_min", "ddns_ttl_max", "hostname_char_set", "$@26",
  "hostname_char_replacement", "$@27", "store_extended_info",
  "statistic_default_sample_count", "statistic_default_sample_age",
  "server_tag", "$@28", "parked_packet_limit", "allocator", "$@29",
  "pd_allocator", "$@30", "early_global_reservations_lookup",
  "ip_reservations_unique", "reservations_lookup_first",
  "allow_address_registration", "interfaces_config", "$@31",
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
  "key_file", "$@46", "ssl_mode", "$@47", "cipher_list", "$@48",
  "sanity_checks", "$@49", "sanity_checks_params", "sanity_checks_param",
  "lease_checks", "$@50", "extended_info_checks", "$@51", "mac_sources",
  "$@52", "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
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
  "not_empty_classes_list", "client_class_entry", "$@111",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@112",
  "client_class_template_test", "$@113", "only_if_required",
  "only_in_additional_list", "server_id", "$@114", "server_id_params",
  "server_id_param", "server_id_type", "$@115", "duid_type", "htype",
  "identifier", "$@116", "time", "enterprise_id", "dhcp4o6_port",
  "control_sockets", "$@117", "control_socket_list",
  "not_empty_control_socket_list", "control_socket_entry", "$@118",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@119", "control_socket_type_value", "control_socket_name", "$@120",
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
     892,   892,   901,   907,   913,   919,   925,   925,   937,   937,
     946,   947,   948,   953,   954,   955,   956,   957,   958,   959,
     960,   963,   963,   974,   980,   986,   992,   998,   998,  1011,
    1011,  1024,  1024,  1035,  1036,  1039,  1040,  1041,  1046,  1046,
    1056,  1057,  1058,  1063,  1064,  1065,  1066,  1067,  1068,  1069,
    1070,  1071,  1072,  1073,  1074,  1075,  1076,  1077,  1078,  1079,
    1080,  1081,  1082,  1083,  1084,  1085,  1086,  1089,  1089,  1098,
    1098,  1107,  1107,  1116,  1116,  1125,  1131,  1131,  1140,  1146,
    1152,  1158,  1164,  1170,  1176,  1182,  1188,  1188,  1196,  1197,
    1198,  1201,  1207,  1213,  1219,  1219,  1228,  1228,  1237,  1237,
    1246,  1246,  1254,  1257,  1260,  1263,  1266,  1271,  1271,  1280,
    1280,  1291,  1292,  1293,  1298,  1299,  1302,  1302,  1321,  1321,
    1339,  1339,  1350,  1351,  1352,  1357,  1358,  1361,  1366,  1371,
    1371,  1382,  1383,  1384,  1389,  1390,  1391,  1394,  1399,  1406,
    1406,  1419,  1419,  1432,  1433,  1434,  1439,  1440,  1441,  1442,
    1443,  1444,  1447,  1453,  1459,  1465,  1465,  1476,  1477,  1480,
    1481,  1482,  1487,  1487,  1497,  1497,  1507,  1508,  1509,  1512,
    1515,  1516,  1519,  1519,  1528,  1528,  1537,  1537,  1549,  1550,
    1551,  1556,  1557,  1558,  1559,  1560,  1561,  1564,  1570,  1576,
    1582,  1588,  1594,  1603,  1603,  1617,  1618,  1621,  1622,  1623,
    1632,  1632,  1658,  1658,  1669,  1670,  1671,  1677,  1678,  1679,
    1680,  1681,  1682,  1683,  1684,  1685,  1686,  1687,  1688,  1689,
    1690,  1691,  1692,  1693,  1694,  1695,  1696,  1697,  1698,  1699,
    1700,  1701,  1702,  1703,  1704,  1705,  1706,  1707,  1708,  1709,
    1710,  1711,  1712,  1713,  1714,  1715,  1716,  1717,  1718,  1719,
    1720,  1721,  1722,  1723,  1724,  1725,  1726,  1727,  1728,  1731,
    1731,  1740,  1740,  1749,  1749,  1758,  1758,  1768,  1768,  1780,
    1780,  1791,  1791,  1802,  1808,  1814,  1820,  1826,  1834,  1834,
    1846,  1847,  1851,  1852,  1853,  1858,  1858,  1866,  1867,  1868,
    1873,  1874,  1875,  1876,  1877,  1878,  1879,  1880,  1881,  1882,
    1883,  1884,  1885,  1886,  1887,  1888,  1889,  1890,  1891,  1892,
    1893,  1894,  1895,  1896,  1897,  1898,  1899,  1900,  1901,  1902,
    1903,  1904,  1905,  1906,  1907,  1908,  1909,  1910,  1911,  1912,
    1913,  1914,  1915,  1916,  1917,  1918,  1919,  1920,  1921,  1928,
    1928,  1942,  1942,  1951,  1952,  1955,  1956,  1957,  1964,  1964,
    1979,  1979,  1993,  1994,  1997,  1998,  1999,  2004,  2005,  2006,
    2007,  2008,  2009,  2010,  2011,  2012,  2013,  2016,  2018,  2024,
    2026,  2026,  2035,  2035,  2044,  2044,  2053,  2055,  2055,  2064,
    2074,  2074,  2087,  2088,  2093,  2094,  2095,  2102,  2102,  2114,
    2114,  2126,  2127,  2132,  2133,  2134,  2141,  2142,  2143,  2144,
    2145,  2146,  2147,  2148,  2149,  2150,  2151,  2154,  2156,  2156,
    2165,  2167,  2169,  2175,  2181,  2187,  2187,  2201,  2201,  2214,
    2215,  2218,  2219,  2220,  2225,  2225,  2235,  2235,  2245,  2246,
    2247,  2252,  2253,  2254,  2255,  2256,  2257,  2258,  2259,  2260,
    2261,  2262,  2263,  2264,  2265,  2266,  2267,  2268,  2269,  2270,
    2271,  2272,  2273,  2274,  2275,  2278,  2278,  2287,  2293,  2293,
    2318,  2318,  2348,  2348,  2361,  2362,  2365,  2366,  2367,  2372,
    2372,  2384,  2384,  2396,  2397,  2398,  2403,  2404,  2405,  2406,
    2407,  2408,  2409,  2410,  2411,  2412,  2413,  2414,  2415,  2416,
    2419,  2419,  2428,  2434,  2434,  2443,  2449,  2458,  2458,  2469,
    2470,  2473,  2474,  2475,  2480,  2480,  2489,  2489,  2498,  2499,
    2502,  2503,  2504,  2510,  2511,  2512,  2513,  2514,  2515,  2516,
    2517,  2518,  2519,  2520,  2521,  2524,  2524,  2535,  2535,  2546,
    2546,  2557,  2557,  2566,  2566,  2575,  2575,  2584,  2584,  2593,
    2593,  2607,  2607,  2618,  2624,  2624,  2635,  2636,  2639,  2640,
    2641,  2646,  2646,  2656,  2657,  2660,  2661,  2662,  2667,  2668,
    2669,  2670,  2671,  2672,  2673,  2674,  2675,  2676,  2677,  2678,
    2679,  2680,  2681,  2684,  2686,  2686,  2695,  2695,  2705,  2711,
    2720,  2720,  2733,  2734,  2735,  2740,  2741,  2742,  2743,  2744,
    2745,  2746,  2747,  2748,  2751,  2751,  2759,  2760,  2761,  2764,
    2770,  2770,  2779,  2785,  2793,  2801,  2801,  2812,  2813,  2816,
    2817,  2818,  2823,  2823,  2831,  2832,  2833,  2838,  2839,  2840,
    2841,  2842,  2843,  2844,  2845,  2846,  2847,  2848,  2849,  2850,
    2853,  2853,  2862,  2863,  2864,  2867,  2867,  2876,  2876,  2885,
    2891,  2897,  2897,  2908,  2909,  2912,  2913,  2914,  2919,  2919,
    2927,  2928,  2929,  2934,  2935,  2936,  2937,  2938,  2941,  2941,
    2952,  2952,  2965,  2966,  2967,  2972,  2973,  2974,  2975,  2976,
    2977,  2978,  2981,  2981,  2989,  2992,  2992,  3001,  3001,  3010,
    3010,  3021,  3022,  3025,  3026,  3027,  3032,  3032,  3040,  3041,
    3042,  3047,  3048,  3049,  3050,  3051,  3052,  3053,  3056,  3056,
    3065,  3065,  3076,  3076,  3089,  3090,  3091,  3096,  3097,  3098,
    3099,  3100,  3101,  3104,  3110,  3110,  3119,  3125,  3125,  3135,
    3135,  3148,  3148,  3158,  3159,  3160,  3165,  3166,  3167,  3168,
    3169,  3170,  3171,  3172,  3173,  3174,  3175,  3178,  3184,  3184,
    3193,  3199,  3199,  3208,  3214,  3220,  3220,  3229,  3230,  3233,
    3233,  3244,  3244,  3256,  3256,  3266,  3267,  3268,  3274,  3275,
    3278,  3278,  3289,  3297,  3297,  3310,  3311,  3312,  3318,  3318,
    3326,  3327,  3328,  3333,  3334,  3335,  3336,  3337,  3338,  3339,
    3342,  3348,  3348,  3357,  3357,  3368,  3369,  3370,  3375,  3375,
    3383,  3384,  3385,  3390,  3391,  3392,  3393,  3394,  3397,  3397,
    3406,  3412,  3418,  3424,  3424,  3433,  3433,  3444,  3445,  3446,
    3451,  3452,  3455
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
#line 7174 "dhcp6_parser.cc"

#line 3461 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
