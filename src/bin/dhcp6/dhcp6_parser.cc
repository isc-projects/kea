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

  case 159: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 690 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1303 "dhcp6_parser.cc"
    break;

  case 160: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 696 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1313 "dhcp6_parser.cc"
    break;

  case 161: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 702 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1323 "dhcp6_parser.cc"
    break;

  case 162: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 708 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1333 "dhcp6_parser.cc"
    break;

  case 163: // $@22: %empty
#line 714 "dhcp6_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1342 "dhcp6_parser.cc"
    break;

  case 164: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 717 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1351 "dhcp6_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "when-present"
#line 723 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1359 "dhcp6_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "never"
#line 726 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1367 "dhcp6_parser.cc"
    break;

  case 167: // ddns_replace_client_name_value: "always"
#line 729 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1375 "dhcp6_parser.cc"
    break;

  case 168: // ddns_replace_client_name_value: "when-not-present"
#line 732 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1383 "dhcp6_parser.cc"
    break;

  case 169: // ddns_replace_client_name_value: "boolean"
#line 735 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1392 "dhcp6_parser.cc"
    break;

  case 170: // $@23: %empty
#line 741 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1401 "dhcp6_parser.cc"
    break;

  case 171: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 744 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1411 "dhcp6_parser.cc"
    break;

  case 172: // $@24: %empty
#line 750 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1420 "dhcp6_parser.cc"
    break;

  case 173: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 753 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1430 "dhcp6_parser.cc"
    break;

  case 174: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 759 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1440 "dhcp6_parser.cc"
    break;

  case 175: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 768 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.warning(yystack_[1].location, "ddns-use-conflict-resolution is deprecated. "
             "Substituting ddns-conflict-resolution-mode");
    ElementPtr mode(new StringElement(b->boolValue() ? "check-with-dhcid"
                                      : "no-check-with-dhcid"));
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", mode);
}
#line 1454 "dhcp6_parser.cc"
    break;

  case 176: // $@25: %empty
#line 778 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1463 "dhcp6_parser.cc"
    break;

  case 177: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 781 "dhcp6_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1472 "dhcp6_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 787 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1480 "dhcp6_parser.cc"
    break;

  case 179: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 790 "dhcp6_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1488 "dhcp6_parser.cc"
    break;

  case 180: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 793 "dhcp6_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1496 "dhcp6_parser.cc"
    break;

  case 181: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 796 "dhcp6_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1504 "dhcp6_parser.cc"
    break;

  case 182: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 801 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1514 "dhcp6_parser.cc"
    break;

  case 183: // ddns_ttl: "ddns-ttl" ":" "integer"
#line 807 "dhcp6_parser.yy"
                                 {
    ctx.unique("ddns-ttl", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl", ttl);
}
#line 1524 "dhcp6_parser.cc"
    break;

  case 184: // ddns_ttl_min: "ddns-ttl-min" ":" "integer"
#line 813 "dhcp6_parser.yy"
                                         {
    ctx.unique("ddns-ttl-min", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-min", ttl);
}
#line 1534 "dhcp6_parser.cc"
    break;

  case 185: // ddns_ttl_max: "ddns-ttl-mix" ":" "integer"
#line 819 "dhcp6_parser.yy"
                                         {
    ctx.unique("ddns-ttl-max", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-max", ttl);
}
#line 1544 "dhcp6_parser.cc"
    break;

  case 186: // $@26: %empty
#line 825 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1553 "dhcp6_parser.cc"
    break;

  case 187: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 828 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1563 "dhcp6_parser.cc"
    break;

  case 188: // $@27: %empty
#line 834 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1572 "dhcp6_parser.cc"
    break;

  case 189: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 837 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1582 "dhcp6_parser.cc"
    break;

  case 190: // store_extended_info: "store-extended-info" ":" "boolean"
#line 843 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1592 "dhcp6_parser.cc"
    break;

  case 191: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 849 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1602 "dhcp6_parser.cc"
    break;

  case 192: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 855 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1612 "dhcp6_parser.cc"
    break;

  case 193: // $@28: %empty
#line 861 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1621 "dhcp6_parser.cc"
    break;

  case 194: // server_tag: "server-tag" $@28 ":" "constant string"
#line 864 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1631 "dhcp6_parser.cc"
    break;

  case 195: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 870 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1641 "dhcp6_parser.cc"
    break;

  case 196: // $@29: %empty
#line 876 "dhcp6_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1650 "dhcp6_parser.cc"
    break;

  case 197: // allocator: "allocator" $@29 ":" "constant string"
#line 879 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1660 "dhcp6_parser.cc"
    break;

  case 198: // $@30: %empty
#line 885 "dhcp6_parser.yy"
                           {
    ctx.unique("pd-allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1669 "dhcp6_parser.cc"
    break;

  case 199: // pd_allocator: "pd-allocator" $@30 ":" "constant string"
#line 888 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-allocator", al);
    ctx.leave();
}
#line 1679 "dhcp6_parser.cc"
    break;

  case 200: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 894 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1689 "dhcp6_parser.cc"
    break;

  case 201: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 900 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1699 "dhcp6_parser.cc"
    break;

  case 202: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 906 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1709 "dhcp6_parser.cc"
    break;

  case 203: // $@31: %empty
#line 912 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1721 "dhcp6_parser.cc"
    break;

  case 204: // interfaces_config: "interfaces-config" $@31 ":" "{" interfaces_config_params "}"
#line 918 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1731 "dhcp6_parser.cc"
    break;

  case 205: // $@32: %empty
#line 924 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1741 "dhcp6_parser.cc"
    break;

  case 206: // sub_interfaces6: "{" $@32 interfaces_config_params "}"
#line 928 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1750 "dhcp6_parser.cc"
    break;

  case 209: // interfaces_config_params: interfaces_config_params ","
#line 935 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1758 "dhcp6_parser.cc"
    break;

  case 218: // $@33: %empty
#line 950 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1770 "dhcp6_parser.cc"
    break;

  case 219: // interfaces_list: "interfaces" $@33 ":" list_strings
#line 956 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1779 "dhcp6_parser.cc"
    break;

  case 220: // re_detect: "re-detect" ":" "boolean"
#line 961 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1789 "dhcp6_parser.cc"
    break;

  case 221: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 967 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1799 "dhcp6_parser.cc"
    break;

  case 222: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 973 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1809 "dhcp6_parser.cc"
    break;

  case 223: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 979 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1819 "dhcp6_parser.cc"
    break;

  case 224: // $@34: %empty
#line 985 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1831 "dhcp6_parser.cc"
    break;

  case 225: // lease_database: "lease-database" $@34 ":" "{" database_map_params "}"
#line 991 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1842 "dhcp6_parser.cc"
    break;

  case 226: // $@35: %empty
#line 998 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1854 "dhcp6_parser.cc"
    break;

  case 227: // hosts_database: "hosts-database" $@35 ":" "{" database_map_params "}"
#line 1004 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1865 "dhcp6_parser.cc"
    break;

  case 228: // $@36: %empty
#line 1011 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1877 "dhcp6_parser.cc"
    break;

  case 229: // hosts_databases: "hosts-databases" $@36 ":" "[" database_list "]"
#line 1017 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1886 "dhcp6_parser.cc"
    break;

  case 234: // not_empty_database_list: not_empty_database_list ","
#line 1028 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1894 "dhcp6_parser.cc"
    break;

  case 235: // $@37: %empty
#line 1033 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1904 "dhcp6_parser.cc"
    break;

  case 236: // database: "{" $@37 database_map_params "}"
#line 1037 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1914 "dhcp6_parser.cc"
    break;

  case 239: // database_map_params: database_map_params ","
#line 1045 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1922 "dhcp6_parser.cc"
    break;

  case 265: // $@38: %empty
#line 1077 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1931 "dhcp6_parser.cc"
    break;

  case 266: // database_type: "type" $@38 ":" "constant string"
#line 1080 "dhcp6_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 1941 "dhcp6_parser.cc"
    break;

  case 267: // $@39: %empty
#line 1086 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1950 "dhcp6_parser.cc"
    break;

  case 268: // user: "user" $@39 ":" "constant string"
#line 1089 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1960 "dhcp6_parser.cc"
    break;

  case 269: // $@40: %empty
#line 1095 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1969 "dhcp6_parser.cc"
    break;

  case 270: // password: "password" $@40 ":" "constant string"
#line 1098 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1979 "dhcp6_parser.cc"
    break;

  case 271: // $@41: %empty
#line 1104 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1988 "dhcp6_parser.cc"
    break;

  case 272: // host: "host" $@41 ":" "constant string"
#line 1107 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1998 "dhcp6_parser.cc"
    break;

  case 273: // port: "port" ":" "integer"
#line 1113 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2008 "dhcp6_parser.cc"
    break;

  case 274: // $@42: %empty
#line 1119 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2017 "dhcp6_parser.cc"
    break;

  case 275: // name: "name" $@42 ":" "constant string"
#line 1122 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2027 "dhcp6_parser.cc"
    break;

  case 276: // persist: "persist" ":" "boolean"
#line 1128 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2037 "dhcp6_parser.cc"
    break;

  case 277: // lfc_interval: "lfc-interval" ":" "integer"
#line 1134 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2047 "dhcp6_parser.cc"
    break;

  case 278: // readonly: "readonly" ":" "boolean"
#line 1140 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2057 "dhcp6_parser.cc"
    break;

  case 279: // connect_timeout: "connect-timeout" ":" "integer"
#line 1146 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2067 "dhcp6_parser.cc"
    break;

  case 280: // read_timeout: "read-timeout" ":" "integer"
#line 1152 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2077 "dhcp6_parser.cc"
    break;

  case 281: // write_timeout: "write-timeout" ":" "integer"
#line 1158 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2087 "dhcp6_parser.cc"
    break;

  case 282: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1164 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2097 "dhcp6_parser.cc"
    break;

  case 283: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1170 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2107 "dhcp6_parser.cc"
    break;

  case 284: // $@43: %empty
#line 1176 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2116 "dhcp6_parser.cc"
    break;

  case 285: // on_fail: "on-fail" $@43 ":" on_fail_mode
#line 1179 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2125 "dhcp6_parser.cc"
    break;

  case 286: // on_fail_mode: "stop-retry-exit"
#line 1184 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2131 "dhcp6_parser.cc"
    break;

  case 287: // on_fail_mode: "serve-retry-exit"
#line 1185 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2137 "dhcp6_parser.cc"
    break;

  case 288: // on_fail_mode: "serve-retry-continue"
#line 1186 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2143 "dhcp6_parser.cc"
    break;

  case 289: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1189 "dhcp6_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2153 "dhcp6_parser.cc"
    break;

  case 290: // max_row_errors: "max-row-errors" ":" "integer"
#line 1195 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2163 "dhcp6_parser.cc"
    break;

  case 291: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1201 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2173 "dhcp6_parser.cc"
    break;

  case 292: // $@44: %empty
#line 1207 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2182 "dhcp6_parser.cc"
    break;

  case 293: // trust_anchor: "trust-anchor" $@44 ":" "constant string"
#line 1210 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2192 "dhcp6_parser.cc"
    break;

  case 294: // $@45: %empty
#line 1216 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2201 "dhcp6_parser.cc"
    break;

  case 295: // cert_file: "cert-file" $@45 ":" "constant string"
#line 1219 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2211 "dhcp6_parser.cc"
    break;

  case 296: // $@46: %empty
#line 1225 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2220 "dhcp6_parser.cc"
    break;

  case 297: // key_file: "key-file" $@46 ":" "constant string"
#line 1228 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2230 "dhcp6_parser.cc"
    break;

  case 298: // $@47: %empty
#line 1234 "dhcp6_parser.yy"
                           {
    ctx.unique("key-password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2239 "dhcp6_parser.cc"
    break;

  case 299: // key_password: "key-password" $@47 ":" "constant string"
#line 1237 "dhcp6_parser.yy"
               {
    ElementPtr key_pass(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-password", key_pass);
    ctx.leave();
}
#line 2249 "dhcp6_parser.cc"
    break;

  case 300: // $@48: %empty
#line 1243 "dhcp6_parser.yy"
                   {
    ctx.unique("ssl-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SSL_MODE);
}
#line 2258 "dhcp6_parser.cc"
    break;

  case 301: // ssl_mode: "ssl-mode" $@48 ":" ssl_mode
#line 1246 "dhcp6_parser.yy"
                 {
    ctx.stack_.back()->set("ssl-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2267 "dhcp6_parser.cc"
    break;

  case 302: // ssl_mode: "disable"
#line 1251 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disable", ctx.loc2pos(yystack_[0].location))); }
#line 2273 "dhcp6_parser.cc"
    break;

  case 303: // ssl_mode: "prefer"
#line 1252 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("prefer", ctx.loc2pos(yystack_[0].location))); }
#line 2279 "dhcp6_parser.cc"
    break;

  case 304: // ssl_mode: "require"
#line 1253 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("require", ctx.loc2pos(yystack_[0].location))); }
#line 2285 "dhcp6_parser.cc"
    break;

  case 305: // ssl_mode: "verify-ca"
#line 1254 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-ca", ctx.loc2pos(yystack_[0].location))); }
#line 2291 "dhcp6_parser.cc"
    break;

  case 306: // ssl_mode: "verify-full"
#line 1255 "dhcp6_parser.yy"
                      { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-full", ctx.loc2pos(yystack_[0].location))); }
#line 2297 "dhcp6_parser.cc"
    break;

  case 307: // $@49: %empty
#line 1258 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2306 "dhcp6_parser.cc"
    break;

  case 308: // cipher_list: "cipher-list" $@49 ":" "constant string"
#line 1261 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2316 "dhcp6_parser.cc"
    break;

  case 309: // $@50: %empty
#line 1267 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2328 "dhcp6_parser.cc"
    break;

  case 310: // sanity_checks: "sanity-checks" $@50 ":" "{" sanity_checks_params "}"
#line 1273 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2337 "dhcp6_parser.cc"
    break;

  case 313: // sanity_checks_params: sanity_checks_params ","
#line 1280 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2345 "dhcp6_parser.cc"
    break;

  case 316: // $@51: %empty
#line 1289 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2354 "dhcp6_parser.cc"
    break;

  case 317: // lease_checks: "lease-checks" $@51 ":" "constant string"
#line 1292 "dhcp6_parser.yy"
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
#line 2374 "dhcp6_parser.cc"
    break;

  case 318: // $@52: %empty
#line 1308 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2383 "dhcp6_parser.cc"
    break;

  case 319: // extended_info_checks: "extended-info-checks" $@52 ":" "constant string"
#line 1311 "dhcp6_parser.yy"
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
#line 2402 "dhcp6_parser.cc"
    break;

  case 320: // $@53: %empty
#line 1326 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2414 "dhcp6_parser.cc"
    break;

  case 321: // mac_sources: "mac-sources" $@53 ":" "[" mac_sources_list "]"
#line 1332 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2423 "dhcp6_parser.cc"
    break;

  case 324: // mac_sources_list: mac_sources_list ","
#line 1339 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2431 "dhcp6_parser.cc"
    break;

  case 327: // duid_id: "duid"
#line 1348 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2440 "dhcp6_parser.cc"
    break;

  case 328: // string_id: "constant string"
#line 1353 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2449 "dhcp6_parser.cc"
    break;

  case 329: // $@54: %empty
#line 1358 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2461 "dhcp6_parser.cc"
    break;

  case 330: // host_reservation_identifiers: "host-reservation-identifiers" $@54 ":" "[" host_reservation_identifiers_list "]"
#line 1364 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2470 "dhcp6_parser.cc"
    break;

  case 333: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1371 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2478 "dhcp6_parser.cc"
    break;

  case 337: // hw_address_id: "hw-address"
#line 1381 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2487 "dhcp6_parser.cc"
    break;

  case 338: // flex_id: "flex-id"
#line 1386 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2496 "dhcp6_parser.cc"
    break;

  case 339: // $@55: %empty
#line 1393 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2508 "dhcp6_parser.cc"
    break;

  case 340: // relay_supplied_options: "relay-supplied-options" $@55 ":" "[" list_content "]"
#line 1399 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2517 "dhcp6_parser.cc"
    break;

  case 341: // $@56: %empty
#line 1406 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2529 "dhcp6_parser.cc"
    break;

  case 342: // dhcp_multi_threading: "multi-threading" $@56 ":" "{" multi_threading_params "}"
#line 1412 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2540 "dhcp6_parser.cc"
    break;

  case 345: // multi_threading_params: multi_threading_params ","
#line 1421 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2548 "dhcp6_parser.cc"
    break;

  case 352: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1434 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2558 "dhcp6_parser.cc"
    break;

  case 353: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1440 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2568 "dhcp6_parser.cc"
    break;

  case 354: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1446 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2578 "dhcp6_parser.cc"
    break;

  case 355: // $@57: %empty
#line 1452 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2590 "dhcp6_parser.cc"
    break;

  case 356: // hooks_libraries: "hooks-libraries" $@57 ":" "[" hooks_libraries_list "]"
#line 1458 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2599 "dhcp6_parser.cc"
    break;

  case 361: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1469 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2607 "dhcp6_parser.cc"
    break;

  case 362: // $@58: %empty
#line 1474 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2617 "dhcp6_parser.cc"
    break;

  case 363: // hooks_library: "{" $@58 hooks_params "}"
#line 1478 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2627 "dhcp6_parser.cc"
    break;

  case 364: // $@59: %empty
#line 1484 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2637 "dhcp6_parser.cc"
    break;

  case 365: // sub_hooks_library: "{" $@59 hooks_params "}"
#line 1488 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2647 "dhcp6_parser.cc"
    break;

  case 368: // hooks_params: hooks_params ","
#line 1496 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2655 "dhcp6_parser.cc"
    break;

  case 372: // $@60: %empty
#line 1506 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2664 "dhcp6_parser.cc"
    break;

  case 373: // library: "library" $@60 ":" "constant string"
#line 1509 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2674 "dhcp6_parser.cc"
    break;

  case 374: // $@61: %empty
#line 1515 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2683 "dhcp6_parser.cc"
    break;

  case 375: // parameters: "parameters" $@61 ":" map_value
#line 1518 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2692 "dhcp6_parser.cc"
    break;

  case 376: // $@62: %empty
#line 1524 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2704 "dhcp6_parser.cc"
    break;

  case 377: // expired_leases_processing: "expired-leases-processing" $@62 ":" "{" expired_leases_params "}"
#line 1530 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2714 "dhcp6_parser.cc"
    break;

  case 380: // expired_leases_params: expired_leases_params ","
#line 1538 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2722 "dhcp6_parser.cc"
    break;

  case 387: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1551 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2732 "dhcp6_parser.cc"
    break;

  case 388: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1557 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2742 "dhcp6_parser.cc"
    break;

  case 389: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1563 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2752 "dhcp6_parser.cc"
    break;

  case 390: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1569 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2762 "dhcp6_parser.cc"
    break;

  case 391: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1575 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2772 "dhcp6_parser.cc"
    break;

  case 392: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1581 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2782 "dhcp6_parser.cc"
    break;

  case 393: // $@63: %empty
#line 1590 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2794 "dhcp6_parser.cc"
    break;

  case 394: // subnet6_list: "subnet6" $@63 ":" "[" subnet6_list_content "]"
#line 1596 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2803 "dhcp6_parser.cc"
    break;

  case 399: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1610 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2811 "dhcp6_parser.cc"
    break;

  case 400: // $@64: %empty
#line 1619 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2821 "dhcp6_parser.cc"
    break;

  case 401: // subnet6: "{" $@64 subnet6_params "}"
#line 1623 "dhcp6_parser.yy"
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
#line 2847 "dhcp6_parser.cc"
    break;

  case 402: // $@65: %empty
#line 1645 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2857 "dhcp6_parser.cc"
    break;

  case 403: // sub_subnet6: "{" $@65 subnet6_params "}"
#line 1649 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2867 "dhcp6_parser.cc"
    break;

  case 406: // subnet6_params: subnet6_params ","
#line 1658 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2875 "dhcp6_parser.cc"
    break;

  case 458: // $@66: %empty
#line 1717 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2884 "dhcp6_parser.cc"
    break;

  case 459: // subnet: "subnet" $@66 ":" "constant string"
#line 1720 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2894 "dhcp6_parser.cc"
    break;

  case 460: // $@67: %empty
#line 1726 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2903 "dhcp6_parser.cc"
    break;

  case 461: // interface: "interface" $@67 ":" "constant string"
#line 1729 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2913 "dhcp6_parser.cc"
    break;

  case 462: // $@68: %empty
#line 1735 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2922 "dhcp6_parser.cc"
    break;

  case 463: // interface_id: "interface-id" $@68 ":" "constant string"
#line 1738 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2932 "dhcp6_parser.cc"
    break;

  case 464: // $@69: %empty
#line 1744 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2941 "dhcp6_parser.cc"
    break;

  case 465: // client_class: "client-class" $@69 ":" "constant string"
#line 1747 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2951 "dhcp6_parser.cc"
    break;

  case 466: // $@70: %empty
#line 1754 "dhcp6_parser.yy"
                                       {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2963 "dhcp6_parser.cc"
    break;

  case 467: // network_client_classes: "client-classes" $@70 ":" list_strings
#line 1760 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2972 "dhcp6_parser.cc"
    break;

  case 468: // $@71: %empty
#line 1766 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2984 "dhcp6_parser.cc"
    break;

  case 469: // require_client_classes: "require-client-classes" $@71 ":" list_strings
#line 1772 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2993 "dhcp6_parser.cc"
    break;

  case 470: // $@72: %empty
#line 1777 "dhcp6_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3005 "dhcp6_parser.cc"
    break;

  case 471: // evaluate_additional_classes: "evaluate-additional-classes" $@72 ":" list_strings
#line 1783 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3014 "dhcp6_parser.cc"
    break;

  case 472: // reservations_global: "reservations-global" ":" "boolean"
#line 1788 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 3024 "dhcp6_parser.cc"
    break;

  case 473: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1794 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 3034 "dhcp6_parser.cc"
    break;

  case 474: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1800 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 3044 "dhcp6_parser.cc"
    break;

  case 475: // id: "id" ":" "integer"
#line 1806 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 3054 "dhcp6_parser.cc"
    break;

  case 476: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1812 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 3064 "dhcp6_parser.cc"
    break;

  case 477: // $@73: %empty
#line 1820 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3076 "dhcp6_parser.cc"
    break;

  case 478: // shared_networks: "shared-networks" $@73 ":" "[" shared_networks_content "]"
#line 1826 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3085 "dhcp6_parser.cc"
    break;

  case 483: // shared_networks_list: shared_networks_list ","
#line 1839 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3093 "dhcp6_parser.cc"
    break;

  case 484: // $@74: %empty
#line 1844 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3103 "dhcp6_parser.cc"
    break;

  case 485: // shared_network: "{" $@74 shared_network_params "}"
#line 1848 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3111 "dhcp6_parser.cc"
    break;

  case 488: // shared_network_params: shared_network_params ","
#line 1854 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3119 "dhcp6_parser.cc"
    break;

  case 537: // $@75: %empty
#line 1913 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3131 "dhcp6_parser.cc"
    break;

  case 538: // option_def_list: "option-def" $@75 ":" "[" option_def_list_content "]"
#line 1919 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3140 "dhcp6_parser.cc"
    break;

  case 539: // $@76: %empty
#line 1927 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3149 "dhcp6_parser.cc"
    break;

  case 540: // sub_option_def_list: "{" $@76 option_def_list "}"
#line 1930 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 3157 "dhcp6_parser.cc"
    break;

  case 545: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1942 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3165 "dhcp6_parser.cc"
    break;

  case 546: // $@77: %empty
#line 1949 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3175 "dhcp6_parser.cc"
    break;

  case 547: // option_def_entry: "{" $@77 option_def_params "}"
#line 1953 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3187 "dhcp6_parser.cc"
    break;

  case 548: // $@78: %empty
#line 1964 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3197 "dhcp6_parser.cc"
    break;

  case 549: // sub_option_def: "{" $@78 option_def_params "}"
#line 1968 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3209 "dhcp6_parser.cc"
    break;

  case 554: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1984 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3217 "dhcp6_parser.cc"
    break;

  case 566: // code: "code" ":" "integer"
#line 2003 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3227 "dhcp6_parser.cc"
    break;

  case 568: // $@79: %empty
#line 2011 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3236 "dhcp6_parser.cc"
    break;

  case 569: // option_def_type: "type" $@79 ":" "constant string"
#line 2014 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3246 "dhcp6_parser.cc"
    break;

  case 570: // $@80: %empty
#line 2020 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3255 "dhcp6_parser.cc"
    break;

  case 571: // option_def_record_types: "record-types" $@80 ":" "constant string"
#line 2023 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3265 "dhcp6_parser.cc"
    break;

  case 572: // $@81: %empty
#line 2029 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3274 "dhcp6_parser.cc"
    break;

  case 573: // space: "space" $@81 ":" "constant string"
#line 2032 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3284 "dhcp6_parser.cc"
    break;

  case 575: // $@82: %empty
#line 2040 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3293 "dhcp6_parser.cc"
    break;

  case 576: // option_def_encapsulate: "encapsulate" $@82 ":" "constant string"
#line 2043 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3303 "dhcp6_parser.cc"
    break;

  case 577: // option_def_array: "array" ":" "boolean"
#line 2049 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3313 "dhcp6_parser.cc"
    break;

  case 578: // $@83: %empty
#line 2059 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3325 "dhcp6_parser.cc"
    break;

  case 579: // option_data_list: "option-data" $@83 ":" "[" option_data_list_content "]"
#line 2065 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3334 "dhcp6_parser.cc"
    break;

  case 584: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2080 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3342 "dhcp6_parser.cc"
    break;

  case 585: // $@84: %empty
#line 2087 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3352 "dhcp6_parser.cc"
    break;

  case 586: // option_data_entry: "{" $@84 option_data_params "}"
#line 2091 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3361 "dhcp6_parser.cc"
    break;

  case 587: // $@85: %empty
#line 2099 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3371 "dhcp6_parser.cc"
    break;

  case 588: // sub_option_data: "{" $@85 option_data_params "}"
#line 2103 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3380 "dhcp6_parser.cc"
    break;

  case 593: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2119 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3388 "dhcp6_parser.cc"
    break;

  case 606: // $@86: %empty
#line 2141 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3397 "dhcp6_parser.cc"
    break;

  case 607: // option_data_data: "data" $@86 ":" "constant string"
#line 2144 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3407 "dhcp6_parser.cc"
    break;

  case 610: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2154 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3417 "dhcp6_parser.cc"
    break;

  case 611: // option_data_always_send: "always-send" ":" "boolean"
#line 2160 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3427 "dhcp6_parser.cc"
    break;

  case 612: // option_data_never_send: "never-send" ":" "boolean"
#line 2166 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3437 "dhcp6_parser.cc"
    break;

  case 613: // $@87: %empty
#line 2172 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3449 "dhcp6_parser.cc"
    break;

  case 614: // option_data_client_classes: "client-classes" $@87 ":" list_strings
#line 2178 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3458 "dhcp6_parser.cc"
    break;

  case 615: // $@88: %empty
#line 2186 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3470 "dhcp6_parser.cc"
    break;

  case 616: // pools_list: "pools" $@88 ":" "[" pools_list_content "]"
#line 2192 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3479 "dhcp6_parser.cc"
    break;

  case 621: // not_empty_pools_list: not_empty_pools_list ","
#line 2205 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3487 "dhcp6_parser.cc"
    break;

  case 622: // $@89: %empty
#line 2210 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3497 "dhcp6_parser.cc"
    break;

  case 623: // pool_list_entry: "{" $@89 pool_params "}"
#line 2214 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3507 "dhcp6_parser.cc"
    break;

  case 624: // $@90: %empty
#line 2220 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3517 "dhcp6_parser.cc"
    break;

  case 625: // sub_pool6: "{" $@90 pool_params "}"
#line 2224 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3527 "dhcp6_parser.cc"
    break;

  case 628: // pool_params: pool_params ","
#line 2232 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3535 "dhcp6_parser.cc"
    break;

  case 653: // $@91: %empty
#line 2263 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3544 "dhcp6_parser.cc"
    break;

  case 654: // pool_entry: "pool" $@91 ":" "constant string"
#line 2266 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3554 "dhcp6_parser.cc"
    break;

  case 655: // pool_id: "pool-id" ":" "integer"
#line 2272 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3564 "dhcp6_parser.cc"
    break;

  case 656: // $@92: %empty
#line 2278 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3572 "dhcp6_parser.cc"
    break;

  case 657: // user_context: "user-context" $@92 ":" map_value
#line 2280 "dhcp6_parser.yy"
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
#line 3599 "dhcp6_parser.cc"
    break;

  case 658: // $@93: %empty
#line 2303 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3607 "dhcp6_parser.cc"
    break;

  case 659: // comment: "comment" $@93 ":" "constant string"
#line 2305 "dhcp6_parser.yy"
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
#line 3636 "dhcp6_parser.cc"
    break;

  case 660: // $@94: %empty
#line 2333 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3648 "dhcp6_parser.cc"
    break;

  case 661: // pd_pools_list: "pd-pools" $@94 ":" "[" pd_pools_list_content "]"
#line 2339 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3657 "dhcp6_parser.cc"
    break;

  case 666: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2352 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3665 "dhcp6_parser.cc"
    break;

  case 667: // $@95: %empty
#line 2357 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3675 "dhcp6_parser.cc"
    break;

  case 668: // pd_pool_entry: "{" $@95 pd_pool_params "}"
#line 2361 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3687 "dhcp6_parser.cc"
    break;

  case 669: // $@96: %empty
#line 2369 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3697 "dhcp6_parser.cc"
    break;

  case 670: // sub_pd_pool: "{" $@96 pd_pool_params "}"
#line 2373 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3709 "dhcp6_parser.cc"
    break;

  case 673: // pd_pool_params: pd_pool_params ","
#line 2383 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3717 "dhcp6_parser.cc"
    break;

  case 688: // $@97: %empty
#line 2404 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3726 "dhcp6_parser.cc"
    break;

  case 689: // pd_prefix: "prefix" $@97 ":" "constant string"
#line 2407 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3736 "dhcp6_parser.cc"
    break;

  case 690: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2413 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3746 "dhcp6_parser.cc"
    break;

  case 691: // $@98: %empty
#line 2419 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3755 "dhcp6_parser.cc"
    break;

  case 692: // excluded_prefix: "excluded-prefix" $@98 ":" "constant string"
#line 2422 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3765 "dhcp6_parser.cc"
    break;

  case 693: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2428 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3775 "dhcp6_parser.cc"
    break;

  case 694: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2434 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3785 "dhcp6_parser.cc"
    break;

  case 695: // $@99: %empty
#line 2443 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3797 "dhcp6_parser.cc"
    break;

  case 696: // reservations: "reservations" $@99 ":" "[" reservations_list "]"
#line 2449 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3806 "dhcp6_parser.cc"
    break;

  case 701: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2460 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3814 "dhcp6_parser.cc"
    break;

  case 702: // $@100: %empty
#line 2465 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3824 "dhcp6_parser.cc"
    break;

  case 703: // reservation: "{" $@100 reservation_params "}"
#line 2469 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3833 "dhcp6_parser.cc"
    break;

  case 704: // $@101: %empty
#line 2474 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3843 "dhcp6_parser.cc"
    break;

  case 705: // sub_reservation: "{" $@101 reservation_params "}"
#line 2478 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3852 "dhcp6_parser.cc"
    break;

  case 710: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2489 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3860 "dhcp6_parser.cc"
    break;

  case 723: // $@102: %empty
#line 2509 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3872 "dhcp6_parser.cc"
    break;

  case 724: // ip_addresses: "ip-addresses" $@102 ":" list_strings
#line 2515 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3881 "dhcp6_parser.cc"
    break;

  case 725: // $@103: %empty
#line 2520 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3893 "dhcp6_parser.cc"
    break;

  case 726: // prefixes: "prefixes" $@103 ":" list_strings
#line 2526 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3902 "dhcp6_parser.cc"
    break;

  case 727: // $@104: %empty
#line 2531 "dhcp6_parser.yy"
                                     {
    ctx.unique("excluded-prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3914 "dhcp6_parser.cc"
    break;

  case 728: // excluded_prefixes: "excluded-prefixes" $@104 ":" list_strings
#line 2537 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3923 "dhcp6_parser.cc"
    break;

  case 729: // $@105: %empty
#line 2542 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3932 "dhcp6_parser.cc"
    break;

  case 730: // duid: "duid" $@105 ":" "constant string"
#line 2545 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3942 "dhcp6_parser.cc"
    break;

  case 731: // $@106: %empty
#line 2551 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3951 "dhcp6_parser.cc"
    break;

  case 732: // hw_address: "hw-address" $@106 ":" "constant string"
#line 2554 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3961 "dhcp6_parser.cc"
    break;

  case 733: // $@107: %empty
#line 2560 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3970 "dhcp6_parser.cc"
    break;

  case 734: // hostname: "hostname" $@107 ":" "constant string"
#line 2563 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3980 "dhcp6_parser.cc"
    break;

  case 735: // $@108: %empty
#line 2569 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3989 "dhcp6_parser.cc"
    break;

  case 736: // flex_id_value: "flex-id" $@108 ":" "constant string"
#line 2572 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3999 "dhcp6_parser.cc"
    break;

  case 737: // $@109: %empty
#line 2578 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4011 "dhcp6_parser.cc"
    break;

  case 738: // reservation_client_classes: "client-classes" $@109 ":" list_strings
#line 2584 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4020 "dhcp6_parser.cc"
    break;

  case 739: // $@110: %empty
#line 2592 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 4032 "dhcp6_parser.cc"
    break;

  case 740: // relay: "relay" $@110 ":" "{" relay_map "}"
#line 2598 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4041 "dhcp6_parser.cc"
    break;

  case 742: // $@111: %empty
#line 2609 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 4053 "dhcp6_parser.cc"
    break;

  case 743: // client_classes: "client-classes" $@111 ":" "[" client_classes_list "]"
#line 2615 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4062 "dhcp6_parser.cc"
    break;

  case 746: // client_classes_list: client_classes_list ","
#line 2622 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 4070 "dhcp6_parser.cc"
    break;

  case 747: // $@112: %empty
#line 2627 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4080 "dhcp6_parser.cc"
    break;

  case 748: // client_class_entry: "{" $@112 client_class_params "}"
#line 2631 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 4090 "dhcp6_parser.cc"
    break;

  case 753: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2643 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 4098 "dhcp6_parser.cc"
    break;

  case 770: // $@113: %empty
#line 2667 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4107 "dhcp6_parser.cc"
    break;

  case 771: // client_class_test: "test" $@113 ":" "constant string"
#line 2670 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4117 "dhcp6_parser.cc"
    break;

  case 772: // $@114: %empty
#line 2676 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4126 "dhcp6_parser.cc"
    break;

  case 773: // client_class_template_test: "template-test" $@114 ":" "constant string"
#line 2679 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4136 "dhcp6_parser.cc"
    break;

  case 774: // only_if_required: "only-if-required" ":" "boolean"
#line 2686 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4146 "dhcp6_parser.cc"
    break;

  case 775: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2692 "dhcp6_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4156 "dhcp6_parser.cc"
    break;

  case 776: // $@115: %empty
#line 2701 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 4168 "dhcp6_parser.cc"
    break;

  case 777: // server_id: "server-id" $@115 ":" "{" server_id_params "}"
#line 2707 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4179 "dhcp6_parser.cc"
    break;

  case 780: // server_id_params: server_id_params ","
#line 2716 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4187 "dhcp6_parser.cc"
    break;

  case 790: // $@116: %empty
#line 2732 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 4196 "dhcp6_parser.cc"
    break;

  case 791: // server_id_type: "type" $@116 ":" duid_type
#line 2735 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4205 "dhcp6_parser.cc"
    break;

  case 792: // duid_type: "LLT"
#line 2740 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4211 "dhcp6_parser.cc"
    break;

  case 793: // duid_type: "EN"
#line 2741 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4217 "dhcp6_parser.cc"
    break;

  case 794: // duid_type: "LL"
#line 2742 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4223 "dhcp6_parser.cc"
    break;

  case 795: // htype: "htype" ":" "integer"
#line 2745 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4233 "dhcp6_parser.cc"
    break;

  case 796: // $@117: %empty
#line 2751 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4242 "dhcp6_parser.cc"
    break;

  case 797: // identifier: "identifier" $@117 ":" "constant string"
#line 2754 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4252 "dhcp6_parser.cc"
    break;

  case 798: // time: "time" ":" "integer"
#line 2760 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4262 "dhcp6_parser.cc"
    break;

  case 799: // enterprise_id: "enterprise-id" ":" "integer"
#line 2766 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4272 "dhcp6_parser.cc"
    break;

  case 800: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2774 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4282 "dhcp6_parser.cc"
    break;

  case 801: // $@118: %empty
#line 2782 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4295 "dhcp6_parser.cc"
    break;

  case 802: // control_socket: "control-socket" $@118 ":" "{" control_socket_params "}"
#line 2789 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4304 "dhcp6_parser.cc"
    break;

  case 803: // $@119: %empty
#line 2794 "dhcp6_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4317 "dhcp6_parser.cc"
    break;

  case 804: // control_sockets: "control-sockets" $@119 ":" "[" control_socket_list "]"
#line 2801 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4326 "dhcp6_parser.cc"
    break;

  case 809: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2812 "dhcp6_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4334 "dhcp6_parser.cc"
    break;

  case 810: // $@120: %empty
#line 2817 "dhcp6_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4344 "dhcp6_parser.cc"
    break;

  case 811: // control_socket_entry: "{" $@120 control_socket_params "}"
#line 2821 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4352 "dhcp6_parser.cc"
    break;

  case 814: // control_socket_params: control_socket_params ","
#line 2827 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4360 "dhcp6_parser.cc"
    break;

  case 828: // $@121: %empty
#line 2847 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4369 "dhcp6_parser.cc"
    break;

  case 829: // control_socket_type: "socket-type" $@121 ":" control_socket_type_value
#line 2850 "dhcp6_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4378 "dhcp6_parser.cc"
    break;

  case 830: // control_socket_type_value: "unix"
#line 2856 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4384 "dhcp6_parser.cc"
    break;

  case 831: // control_socket_type_value: "http"
#line 2857 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4390 "dhcp6_parser.cc"
    break;

  case 832: // control_socket_type_value: "https"
#line 2858 "dhcp6_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4396 "dhcp6_parser.cc"
    break;

  case 833: // $@122: %empty
#line 2861 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4406 "dhcp6_parser.cc"
    break;

  case 834: // control_socket_name: "socket-name" $@122 ":" "constant string"
#line 2865 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4416 "dhcp6_parser.cc"
    break;

  case 835: // $@123: %empty
#line 2871 "dhcp6_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4426 "dhcp6_parser.cc"
    break;

  case 836: // control_socket_address: "socket-address" $@123 ":" "constant string"
#line 2875 "dhcp6_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4436 "dhcp6_parser.cc"
    break;

  case 837: // control_socket_port: "socket-port" ":" "integer"
#line 2881 "dhcp6_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4446 "dhcp6_parser.cc"
    break;

  case 838: // cert_required: "cert-required" ":" "boolean"
#line 2887 "dhcp6_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4456 "dhcp6_parser.cc"
    break;

  case 839: // $@124: %empty
#line 2893 "dhcp6_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4468 "dhcp6_parser.cc"
    break;

  case 840: // http_headers: "http-headers" $@124 ":" "[" http_header_list "]"
#line 2899 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4477 "dhcp6_parser.cc"
    break;

  case 845: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2910 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4485 "dhcp6_parser.cc"
    break;

  case 846: // $@125: %empty
#line 2915 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4495 "dhcp6_parser.cc"
    break;

  case 847: // http_header: "{" $@125 http_header_params "}"
#line 2919 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4503 "dhcp6_parser.cc"
    break;

  case 850: // http_header_params: http_header_params ","
#line 2925 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4511 "dhcp6_parser.cc"
    break;

  case 856: // $@126: %empty
#line 2937 "dhcp6_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4520 "dhcp6_parser.cc"
    break;

  case 857: // header_value: "value" $@126 ":" "constant string"
#line 2940 "dhcp6_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4530 "dhcp6_parser.cc"
    break;

  case 858: // $@127: %empty
#line 2948 "dhcp6_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4542 "dhcp6_parser.cc"
    break;

  case 859: // authentication: "authentication" $@127 ":" "{" auth_params "}"
#line 2954 "dhcp6_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4553 "dhcp6_parser.cc"
    break;

  case 862: // auth_params: auth_params ","
#line 2963 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4561 "dhcp6_parser.cc"
    break;

  case 870: // $@128: %empty
#line 2977 "dhcp6_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4570 "dhcp6_parser.cc"
    break;

  case 871: // auth_type: "type" $@128 ":" auth_type_value
#line 2980 "dhcp6_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4579 "dhcp6_parser.cc"
    break;

  case 872: // auth_type_value: "basic"
#line 2985 "dhcp6_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4585 "dhcp6_parser.cc"
    break;

  case 873: // $@129: %empty
#line 2988 "dhcp6_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4594 "dhcp6_parser.cc"
    break;

  case 874: // realm: "realm" $@129 ":" "constant string"
#line 2991 "dhcp6_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4604 "dhcp6_parser.cc"
    break;

  case 875: // $@130: %empty
#line 2997 "dhcp6_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4613 "dhcp6_parser.cc"
    break;

  case 876: // directory: "directory" $@130 ":" "constant string"
#line 3000 "dhcp6_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4623 "dhcp6_parser.cc"
    break;

  case 877: // $@131: %empty
#line 3006 "dhcp6_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4635 "dhcp6_parser.cc"
    break;

  case 878: // clients: "clients" $@131 ":" "[" clients_list "]"
#line 3012 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4644 "dhcp6_parser.cc"
    break;

  case 883: // not_empty_clients_list: not_empty_clients_list ","
#line 3023 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4652 "dhcp6_parser.cc"
    break;

  case 884: // $@132: %empty
#line 3028 "dhcp6_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4662 "dhcp6_parser.cc"
    break;

  case 885: // basic_auth: "{" $@132 clients_params "}"
#line 3032 "dhcp6_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4670 "dhcp6_parser.cc"
    break;

  case 888: // clients_params: clients_params ","
#line 3038 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4678 "dhcp6_parser.cc"
    break;

  case 896: // $@133: %empty
#line 3052 "dhcp6_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4687 "dhcp6_parser.cc"
    break;

  case 897: // user_file: "user-file" $@133 ":" "constant string"
#line 3055 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4697 "dhcp6_parser.cc"
    break;

  case 898: // $@134: %empty
#line 3061 "dhcp6_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4706 "dhcp6_parser.cc"
    break;

  case 899: // password_file: "password-file" $@134 ":" "constant string"
#line 3064 "dhcp6_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4716 "dhcp6_parser.cc"
    break;

  case 900: // $@135: %empty
#line 3072 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4728 "dhcp6_parser.cc"
    break;

  case 901: // dhcp_queue_control: "dhcp-queue-control" $@135 ":" "{" queue_control_params "}"
#line 3078 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4739 "dhcp6_parser.cc"
    break;

  case 904: // queue_control_params: queue_control_params ","
#line 3087 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4747 "dhcp6_parser.cc"
    break;

  case 911: // enable_queue: "enable-queue" ":" "boolean"
#line 3100 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4757 "dhcp6_parser.cc"
    break;

  case 912: // $@136: %empty
#line 3106 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4766 "dhcp6_parser.cc"
    break;

  case 913: // queue_type: "queue-type" $@136 ":" "constant string"
#line 3109 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4776 "dhcp6_parser.cc"
    break;

  case 914: // capacity: "capacity" ":" "integer"
#line 3115 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4786 "dhcp6_parser.cc"
    break;

  case 915: // $@137: %empty
#line 3121 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4795 "dhcp6_parser.cc"
    break;

  case 916: // arbitrary_map_entry: "constant string" $@137 ":" value
#line 3124 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4804 "dhcp6_parser.cc"
    break;

  case 917: // $@138: %empty
#line 3131 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4816 "dhcp6_parser.cc"
    break;

  case 918: // dhcp_ddns: "dhcp-ddns" $@138 ":" "{" dhcp_ddns_params "}"
#line 3137 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4827 "dhcp6_parser.cc"
    break;

  case 919: // $@139: %empty
#line 3144 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4837 "dhcp6_parser.cc"
    break;

  case 920: // sub_dhcp_ddns: "{" $@139 dhcp_ddns_params "}"
#line 3148 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4847 "dhcp6_parser.cc"
    break;

  case 923: // dhcp_ddns_params: dhcp_ddns_params ","
#line 3156 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4855 "dhcp6_parser.cc"
    break;

  case 935: // enable_updates: "enable-updates" ":" "boolean"
#line 3174 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4865 "dhcp6_parser.cc"
    break;

  case 936: // $@140: %empty
#line 3180 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4874 "dhcp6_parser.cc"
    break;

  case 937: // server_ip: "server-ip" $@140 ":" "constant string"
#line 3183 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4884 "dhcp6_parser.cc"
    break;

  case 938: // server_port: "server-port" ":" "integer"
#line 3189 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4894 "dhcp6_parser.cc"
    break;

  case 939: // $@141: %empty
#line 3195 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4903 "dhcp6_parser.cc"
    break;

  case 940: // sender_ip: "sender-ip" $@141 ":" "constant string"
#line 3198 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4913 "dhcp6_parser.cc"
    break;

  case 941: // sender_port: "sender-port" ":" "integer"
#line 3204 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4923 "dhcp6_parser.cc"
    break;

  case 942: // max_queue_size: "max-queue-size" ":" "integer"
#line 3210 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4933 "dhcp6_parser.cc"
    break;

  case 943: // $@142: %empty
#line 3216 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4942 "dhcp6_parser.cc"
    break;

  case 944: // ncr_protocol: "ncr-protocol" $@142 ":" ncr_protocol_value
#line 3219 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4951 "dhcp6_parser.cc"
    break;

  case 945: // ncr_protocol_value: "UDP"
#line 3225 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4957 "dhcp6_parser.cc"
    break;

  case 946: // ncr_protocol_value: "TCP"
#line 3226 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4963 "dhcp6_parser.cc"
    break;

  case 947: // $@143: %empty
#line 3229 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4972 "dhcp6_parser.cc"
    break;

  case 948: // ncr_format: "ncr-format" $@143 ":" "JSON"
#line 3232 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4982 "dhcp6_parser.cc"
    break;

  case 949: // $@144: %empty
#line 3240 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4994 "dhcp6_parser.cc"
    break;

  case 950: // config_control: "config-control" $@144 ":" "{" config_control_params "}"
#line 3246 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5004 "dhcp6_parser.cc"
    break;

  case 951: // $@145: %empty
#line 3252 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 5014 "dhcp6_parser.cc"
    break;

  case 952: // sub_config_control: "{" $@145 config_control_params "}"
#line 3256 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 5023 "dhcp6_parser.cc"
    break;

  case 955: // config_control_params: config_control_params ","
#line 3264 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 5031 "dhcp6_parser.cc"
    break;

  case 958: // $@146: %empty
#line 3274 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 5043 "dhcp6_parser.cc"
    break;

  case 959: // config_databases: "config-databases" $@146 ":" "[" database_list "]"
#line 3280 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5052 "dhcp6_parser.cc"
    break;

  case 960: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3285 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 5062 "dhcp6_parser.cc"
    break;

  case 961: // $@147: %empty
#line 3293 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 5074 "dhcp6_parser.cc"
    break;

  case 962: // loggers: "loggers" $@147 ":" "[" loggers_entries "]"
#line 3299 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5083 "dhcp6_parser.cc"
    break;

  case 965: // loggers_entries: loggers_entries ","
#line 3308 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 5091 "dhcp6_parser.cc"
    break;

  case 966: // $@148: %empty
#line 3314 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 5101 "dhcp6_parser.cc"
    break;

  case 967: // logger_entry: "{" $@148 logger_params "}"
#line 3318 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 5109 "dhcp6_parser.cc"
    break;

  case 970: // logger_params: logger_params ","
#line 3324 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 5117 "dhcp6_parser.cc"
    break;

  case 978: // debuglevel: "debuglevel" ":" "integer"
#line 3338 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 5127 "dhcp6_parser.cc"
    break;

  case 979: // $@149: %empty
#line 3344 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5136 "dhcp6_parser.cc"
    break;

  case 980: // severity: "severity" $@149 ":" "constant string"
#line 3347 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 5146 "dhcp6_parser.cc"
    break;

  case 981: // $@150: %empty
#line 3353 "dhcp6_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 5158 "dhcp6_parser.cc"
    break;

  case 982: // output_options_list: "output-options" $@150 ":" "[" output_options_list_content "]"
#line 3359 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5167 "dhcp6_parser.cc"
    break;

  case 985: // output_options_list_content: output_options_list_content ","
#line 3366 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 5175 "dhcp6_parser.cc"
    break;

  case 986: // $@151: %empty
#line 3371 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 5185 "dhcp6_parser.cc"
    break;

  case 987: // output_entry: "{" $@151 output_params_list "}"
#line 3375 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 5193 "dhcp6_parser.cc"
    break;

  case 990: // output_params_list: output_params_list ","
#line 3381 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 5201 "dhcp6_parser.cc"
    break;

  case 996: // $@152: %empty
#line 3393 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5210 "dhcp6_parser.cc"
    break;

  case 997: // output: "output" $@152 ":" "constant string"
#line 3396 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5220 "dhcp6_parser.cc"
    break;

  case 998: // flush: "flush" ":" "boolean"
#line 3402 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5230 "dhcp6_parser.cc"
    break;

  case 999: // maxsize: "maxsize" ":" "integer"
#line 3408 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5240 "dhcp6_parser.cc"
    break;

  case 1000: // maxver: "maxver" ":" "integer"
#line 3414 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5250 "dhcp6_parser.cc"
    break;

  case 1001: // $@153: %empty
#line 3420 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5259 "dhcp6_parser.cc"
    break;

  case 1002: // pattern: "pattern" $@153 ":" "constant string"
#line 3423 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5269 "dhcp6_parser.cc"
    break;

  case 1003: // $@154: %empty
#line 3429 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5281 "dhcp6_parser.cc"
    break;

  case 1004: // compatibility: "compatibility" $@154 ":" "{" compatibility_params "}"
#line 3435 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5290 "dhcp6_parser.cc"
    break;

  case 1007: // compatibility_params: compatibility_params ","
#line 3442 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5298 "dhcp6_parser.cc"
    break;

  case 1010: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3451 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5308 "dhcp6_parser.cc"
    break;


#line 5312 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1450;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     710, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450,    64,    43,    34,    62,    77,
      93,    98,   123,   141,   186,   209,   225,   236,   259,   260,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,    43,  -174,
     114,   763,    56,  1446,   326,   336,   164,   192,    11,   627,
     -80,   610,    96, -1450,   292,   297,   300,   310,   331, -1450,
     109, -1450, -1450, -1450, -1450, -1450, -1450, -1450,   340,   341,
     355,   357,   361,   369,   373,   375,   384,   420,   439,   440,
     449,   450, -1450,   459,   468,   472,   473,   474, -1450, -1450,
   -1450,   484,   485,   486,   487,   488,   489,   490, -1450, -1450,
   -1450,   491, -1450, -1450, -1450, -1450, -1450, -1450,   492,   493,
     494, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
     495, -1450, -1450, -1450, -1450, -1450, -1450, -1450,   497,   498,
     499, -1450, -1450,   501, -1450,   117, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,   502,
     503,   504,   505, -1450,   159, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,   506,   508,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450,   171, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,   512,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
     174, -1450, -1450, -1450, -1450, -1450, -1450,   514, -1450,   516,
     517, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
     184, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,   321,
     419, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
     382, -1450, -1450,   519, -1450, -1450, -1450,   520, -1450, -1450,
     477,   522, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450,   523,   524,   526, -1450, -1450,
   -1450, -1450, -1450,   518,   528, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,   250,
   -1450, -1450, -1450,   530, -1450,   531, -1450,   537,   539, -1450,
   -1450, -1450, -1450, -1450,   251, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450,   543,   261, -1450, -1450, -1450,
   -1450,    43,    43, -1450,   309,   550, -1450, -1450,   553,   555,
     556,   559,   561,   562,   328,   330,   332,   334,   337,   342,
     343,   344,   327,   335,   345,   346,   350,   358,   569,   359,
     362,   352,   363,   364,   578,   583,   595,   367,   370,   374,
     376,   379,   380,   371,   598,   599,   601,   385,   602,   620,
     621,   624,   625,   628,   389,   390,   394,   635,   636,   641,
     646,   648,   650,   652,   653,   654,   421,   658,   660,   665,
     668,   671,   673,   676,   437,   438,   441,   679,   683, -1450,
     763, -1450,   684,   446,   447,   451,   454,    56, -1450,   688,
     690,   693,   694,   695,   461,   462,   701,   704,   705,   706,
     707,  1446, -1450,   708,   471,   326, -1450,   718,   482,   719,
     496,   507,   336, -1450,   723,   724,   725,   726,   727,   728,
     730,   731, -1450,   164, -1450,   732,   733,   509,   741,   742,
     743,   470, -1450,    11,   746,   510,   511,   513,   748, -1450,
     627,   749,   752,   -59, -1450,   515,   756,   521,   760,   525,
     529,   761,   762,   610, -1450,   772,   535,    96, -1450, -1450,
   -1450,   775,   773,   540,   776,   780,   781,   782,   777, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450,   549, -1450, -1450, -1450, -1450, -1450,  -154,
     551,   552, -1450, -1450, -1450, -1450, -1450, -1450, -1450,   786,
     789,   790, -1450,   563,   564,   378,   791,   793,   573, -1450,
   -1450, -1450,   798,   810,   811,   845,   812,   848,   849,   850,
     851, -1450,   852,   853,   860,   859,   863,   614,   615, -1450,
   -1450, -1450,   862,   864, -1450,   867, -1450, -1450, -1450, -1450,
   -1450,   868,   869,   634,   639,   640, -1450, -1450,   867,   867,
     867,   642,   870, -1450,   643, -1450, -1450,   651, -1450,   655,
   -1450, -1450, -1450,   867,   867,   867,   867,   656,   657,   659,
     661, -1450,   663,   664, -1450,   666,   667,   669, -1450, -1450,
     670, -1450, -1450, -1450,   867, -1450,   672,   793, -1450, -1450,
     675, -1450,   677, -1450, -1450,    13,   687, -1450,   871, -1450,
   -1450,    43,   763, -1450,    96,    56,   177,   177,   875, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,   888,   892,
     894, -1450, -1450, -1450, -1450, -1450, -1450, -1450,   899, -1450,
   -1450, -1450,  -104,    43,   -66,   112,   902,   907,   910,   275,
      74,    27,   204,   912,   131,   610, -1450, -1450,   913,  -184,
   -1450, -1450,   914,   916, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450,   783, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,   875, -1450,
     273,   274,   280, -1450, -1450, -1450, -1450,   921,   922,   923,
     924,   925,   928,   929,   930,   947,   948, -1450,   949,   951,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450,   291, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,   293, -1450,
     950,   954, -1450, -1450,   953,   957, -1450, -1450,   955,   959,
   -1450, -1450,   958,   960, -1450, -1450,   961,   962, -1450, -1450,
   -1450,   110, -1450, -1450, -1450,   963, -1450, -1450, -1450,   135,
   -1450, -1450, -1450, -1450, -1450,   313, -1450, -1450, -1450, -1450,
     257, -1450, -1450,   964,   965, -1450, -1450,   966,   968, -1450,
     969,   976,   977,   978,   979,   980,   314, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450,   981,   982,   983, -1450,
   -1450, -1450, -1450,   325, -1450, -1450, -1450, -1450, -1450, -1450,
     985,   986,   987, -1450,   329, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450,   988, -1450,   989, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450,   338, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450,   990,   991, -1450,   993, -1450,   994,
   -1450, -1450, -1450,   339, -1450, -1450, -1450, -1450, -1450,   354,
   -1450,   467, -1450,   995, -1450,   360, -1450, -1450,   754, -1450,
     996,   997, -1450, -1450,   999,   998, -1450, -1450,  1000,  1001,
   -1450, -1450, -1450,  1002,  1005,  1006,  1007,   770,   722,   771,
     759,   774,   778,   779,   784,   785,   787,  1010,   788,   794,
    1011,  1013,  1014,  1015,  1018,  1019,   177, -1450, -1450,   177,
   -1450,   875,  1446, -1450,   888,    11, -1450,   892,   627, -1450,
     894,  1544, -1450,   899,  -104, -1450, -1450,   -66, -1450,  1020,
    1021,   112, -1450,   215,   902, -1450,   164, -1450,   907,   -80,
   -1450,   910,   796,   797,   799,   800,   804,   807,   275, -1450,
    1024,  1026,   809,   817,   819,    74, -1450,   818,   822,   823,
      27, -1450,  1029,  1031,  1066,   829,  1068,   831,  1073,   204,
   -1450,   204, -1450,   912,   834,  1076,   841,  1081,   131, -1450,
   -1450,    16,   913, -1450,   842,  -184, -1450, -1450,  1085,  1090,
     326, -1450,   914,   336, -1450,   916, -1450, -1450,   858,   861,
     866,   877, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450,   144, -1450, -1450,   880,   887,   889,   895,   387,
     898, -1450,   368, -1450,   372, -1450,  1093, -1450,  1097, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450,   383, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450,   901,   919, -1450, -1450, -1450,  1107,  1159,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450,  1161,  1171, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
    1168, -1450,   386, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450,    -6,   938, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450,   220,   940,   942, -1450,  1178, -1450,  1183, -1450,   407,
   -1450, -1450,   952, -1450,    43, -1450, -1450,  1186, -1450, -1450,
   -1450, -1450, -1450,   408, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450,   971,   409, -1450,   411, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450,  1544, -1450, -1450, -1450,  1187,
    1190,  1003,  1004, -1450,   215, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,   129,  1191,
   -1450, -1450, -1450,  1217,   992,  1218,    16, -1450, -1450, -1450,
   -1450, -1450,  1008,  1009, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450,   417, -1450, -1450, -1450, -1450, -1450,
   -1450,  1221,  1220, -1450,  1225, -1450,  1016, -1450, -1450, -1450,
    1228,  1229,  1233,  1234,   129, -1450,   146, -1450,  1191,  1232,
   -1450,  1060,  1022,  1025,  1238, -1450, -1450, -1450, -1450, -1450,
   -1450,   418, -1450, -1450, -1450, -1450,   481, -1450, -1450, -1450,
   -1450, -1450,  1245,  1241,   146, -1450,  -135,  1232, -1450, -1450,
    1248,  1252, -1450,  1028, -1450, -1450,  1255,  1256,  1257, -1450,
     452, -1450, -1450, -1450, -1450, -1450, -1450, -1450,   140, -1450,
    1245, -1450,  1258,  1023,  1030,  1032,  1267,  -135, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450,   463, -1450, -1450, -1450,
   -1450,  1035, -1450, -1450, -1450,  1036, -1450,  1269,  1274,   140,
   -1450, -1450, -1450,  1038,  1039, -1450, -1450, -1450
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   205,     9,   402,    11,
     624,    13,   669,    15,   704,    17,   539,    19,   548,    21,
     587,    23,   364,    25,   919,    27,   951,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   706,     0,   550,   589,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   144,   949,   203,   224,   226,   228,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   193,     0,     0,     0,     0,     0,   163,   170,
     172,     0,     0,     0,     0,     0,     0,     0,   393,   537,
     578,     0,   196,   198,   176,   477,   656,   658,     0,     0,
       0,   320,   339,   329,   309,   742,   695,   355,   376,   776,
       0,   341,   801,   803,   900,   917,   186,   188,     0,     0,
       0,   961,  1003,     0,   143,     0,    69,    72,    73,    74,
      75,    76,    77,    78,    79,    80,   111,   112,   113,   114,
     115,    81,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   117,   118,   132,   133,   134,
     107,   140,   141,   142,   136,   137,   138,    84,    85,    86,
      87,   104,    88,    90,    89,   135,    94,    95,    82,   108,
     109,   110,    83,    92,    93,   102,   103,   105,    91,    96,
      97,    98,    99,   100,   101,   106,   116,   139,   218,     0,
       0,     0,     0,   217,     0,   207,   210,   211,   212,   213,
     214,   215,   216,   615,   660,   458,   460,   462,     0,     0,
     466,   468,   470,   464,   739,   457,   407,   408,   409,   410,
     411,   412,   413,   414,   434,   435,   436,   437,   438,   441,
     442,   443,   444,   445,   446,   447,   448,   449,   450,   451,
     452,   453,   439,   440,   454,   455,   456,     0,   404,   418,
     419,   420,   423,   424,   425,   426,   428,   429,   430,   421,
     422,   415,   416,   432,   433,   417,   427,   431,   653,     0,
     652,   636,   637,   638,   639,   640,   641,   642,   643,   644,
     645,   646,   647,   648,   649,   632,   633,   634,   635,   631,
       0,   626,   629,   630,   650,   651,   688,     0,   691,     0,
       0,   687,   679,   680,   681,   682,   678,   677,   685,   686,
       0,   671,   674,   675,   683,   684,   676,   737,   723,   725,
     727,   729,   731,   733,   735,   722,   719,   720,   721,     0,
     707,   708,   713,   714,   715,   711,   716,   717,   718,   712,
       0,   568,   274,     0,   572,   570,   575,     0,   564,   565,
       0,   551,   552,   555,   567,   556,   557,   558,   574,   559,
     560,   561,   562,   563,   606,     0,     0,     0,   613,   604,
     605,   608,   609,     0,   590,   591,   594,   595,   596,   597,
     598,   599,   600,   603,   601,   602,   372,   374,   369,     0,
     366,   370,   371,     0,   936,     0,   939,     0,     0,   943,
     947,   934,   932,   933,     0,   921,   924,   925,   926,   927,
     928,   929,   930,   931,   958,     0,     0,   953,   956,   957,
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
       0,   406,   403,     0,     0,   628,   625,     0,     0,     0,
       0,     0,   673,   670,     0,     0,     0,     0,     0,     0,
       0,     0,   705,   710,   540,     0,     0,     0,     0,     0,
       0,     0,   549,   554,     0,     0,     0,     0,     0,   588,
     593,     0,     0,   368,   365,     0,     0,     0,     0,     0,
       0,     0,     0,   923,   920,     0,     0,   955,   952,    51,
      43,     0,     0,     0,     0,     0,     0,     0,     0,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,     0,   191,   192,   160,   161,   162,     0,
       0,     0,   174,   175,   182,   183,   184,   185,   190,     0,
       0,     0,   195,     0,     0,     0,     0,     0,     0,   472,
     473,   474,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   800,     0,     0,     0,     0,     0,     0,     0,   200,
     201,   202,     0,     0,    70,     0,   220,   221,   222,   223,
     208,     0,     0,     0,     0,     0,   475,   476,     0,     0,
       0,     0,     0,   405,     0,   655,   627,     0,   690,     0,
     693,   694,   672,     0,     0,     0,     0,     0,     0,     0,
       0,   709,     0,     0,   566,     0,     0,     0,   577,   553,
       0,   610,   611,   612,     0,   592,     0,     0,   367,   935,
       0,   938,     0,   941,   942,     0,     0,   922,     0,   960,
     954,     0,     0,   145,     0,     0,     0,     0,   230,   194,
     165,   166,   167,   168,   169,   164,   171,   173,   395,   541,
     580,   197,   199,   178,   179,   180,   181,   177,   479,    40,
     657,   659,     0,    48,     0,     0,     0,   697,   357,     0,
       0,     0,     0,   805,     0,     0,   187,   189,     0,     0,
      53,   219,   617,   662,   459,   461,   463,   467,   469,   471,
     465,     0,   654,   689,   692,   738,   724,   726,   728,   730,
     732,   734,   736,   569,   275,   573,   571,   576,   607,   614,
     373,   375,   937,   940,   945,   946,   944,   948,   230,    44,
       0,     0,     0,   265,   267,   269,   271,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   284,     0,     0,
     292,   294,   296,   298,   300,   302,   303,   304,   305,   306,
     307,   264,     0,   237,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   254,   255,   256,
     257,   253,   258,   259,   260,   261,   262,   263,     0,   235,
       0,   231,   232,   400,     0,   396,   397,   546,     0,   542,
     543,   585,     0,   581,   582,   484,     0,   480,   481,   327,
     328,     0,   322,   325,   326,     0,   337,   338,   334,     0,
     331,   335,   336,   316,   318,     0,   311,   314,   315,   747,
       0,   744,   702,     0,   698,   699,   362,     0,   358,   359,
       0,     0,     0,     0,     0,     0,     0,   378,   381,   382,
     383,   384,   385,   386,   790,   796,     0,     0,     0,   789,
     786,   787,   788,     0,   778,   781,   784,   782,   783,   785,
       0,     0,     0,   351,     0,   343,   346,   347,   348,   349,
     350,   828,   833,   835,     0,   858,     0,   839,   827,   820,
     821,   822,   825,   826,     0,   812,   815,   816,   817,   818,
     823,   824,   819,   810,     0,   806,   807,     0,   912,     0,
     915,   908,   909,     0,   902,   905,   906,   907,   910,     0,
     966,     0,   963,     0,  1009,     0,  1005,  1008,    55,   622,
       0,   618,   619,   667,     0,   663,   664,   741,     0,     0,
      64,   950,   204,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   239,   225,   227,     0,
     229,   234,     0,   394,   399,   550,   538,   545,   589,   579,
     584,     0,   478,   483,   324,   321,   340,   333,   330,     0,
       0,   313,   310,   749,   746,   743,   706,   696,   701,     0,
     356,   361,     0,     0,     0,     0,     0,     0,   380,   377,
       0,     0,     0,     0,     0,   780,   777,     0,     0,     0,
     345,   342,     0,     0,     0,     0,     0,     0,     0,   814,
     802,     0,   804,   809,     0,     0,     0,     0,   904,   901,
     918,     0,   965,   962,     0,  1007,  1004,    57,     0,    56,
       0,   616,   621,     0,   661,   666,   740,   959,     0,     0,
       0,     0,   273,   276,   277,   278,   279,   280,   281,   282,
     291,   283,     0,   289,   290,     0,     0,     0,     0,     0,
       0,   238,     0,   233,     0,   398,     0,   544,     0,   583,
     536,   504,   505,   506,   508,   509,   510,   493,   494,   513,
     514,   515,   516,   517,   520,   521,   522,   523,   524,   525,
     526,   527,   528,   529,   530,   531,   532,   518,   519,   533,
     534,   535,   489,   490,   491,   492,   500,   501,   502,   503,
     497,   498,   499,   507,     0,   486,   495,   511,   512,   496,
     482,   323,   332,     0,     0,   312,   770,   772,     0,     0,
     768,   762,   763,   764,   765,   766,   767,   769,   759,   760,
     761,     0,   750,   751,   754,   755,   756,   757,   758,   745,
       0,   700,     0,   360,   387,   388,   389,   390,   391,   392,
     379,     0,     0,   795,   798,   799,   779,   352,   353,   354,
     344,     0,     0,     0,   837,     0,   838,     0,   813,     0,
     808,   911,     0,   914,     0,   903,   981,     0,   979,   977,
     971,   975,   976,     0,   968,   973,   974,   972,   964,  1010,
    1006,    54,    59,     0,   620,     0,   665,   266,   268,   270,
     272,   286,   287,   288,   285,   293,   295,   297,   299,   301,
     308,   236,   401,   547,   586,   488,   485,   317,   319,     0,
       0,     0,     0,   748,   753,   703,   363,   792,   793,   794,
     791,   797,   830,   831,   832,   829,   834,   836,     0,   841,
     811,   913,   916,     0,     0,     0,   970,   967,    58,   623,
     668,   487,     0,     0,   774,   775,   752,   870,   873,   875,
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
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450,   -10, -1450,  -634, -1450,
     527, -1450, -1450, -1450, -1450,   478, -1450,  -380, -1450, -1450,
   -1450,   -71, -1450, -1450, -1450, -1450, -1450, -1450, -1450,   534,
     735, -1450, -1450,     4,    12,    22,    38,    41,    42,   -57,
     -54,   -35,   -15,    97,   100,   102, -1450,    20,    23,    45,
      48, -1450, -1450,    55, -1450,    60, -1450,    66,   103,    71,
   -1450, -1450,    73,    76,    78,    84,    90, -1450,    95, -1450,
     105, -1450, -1450, -1450, -1450, -1450,   107, -1450,   108, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450,   532,   729, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450,   424, -1450,   182, -1450,  -756,   191, -1450, -1450, -1449,
   -1450, -1447, -1450, -1450, -1450, -1450,   -55, -1450,  -797, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450,  -801, -1450,  -795, -1450,  -792, -1450, -1450, -1450,
      79, -1450, -1450, -1450, -1450, -1450, -1450,   168, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450,   176,  -782, -1450, -1450, -1450,
   -1450,   175, -1450, -1450, -1450, -1450, -1450, -1450, -1450,   143,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450,   160, -1450, -1450,
   -1450,   165,   682, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
     158, -1450, -1450, -1450, -1450, -1450, -1450, -1086, -1450, -1450,
   -1450,   193, -1450, -1450, -1450,   196,   738, -1450, -1450, -1085,
   -1450, -1084, -1450,    61, -1450,    85, -1450,   120, -1450,   125,
   -1450,   113,   115,   118, -1450, -1083, -1450, -1450, -1450, -1450,
     188, -1450, -1450,   -76,  1235, -1450, -1450, -1450, -1450, -1450,
     195, -1450, -1450, -1450,   205, -1450,   711, -1450,   -65, -1450,
   -1450, -1450, -1450, -1450,   -61, -1450, -1450, -1450, -1450, -1450,
     -29, -1450, -1450, -1450,   201, -1450, -1450, -1450,   207, -1450,
     709, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450,   134, -1450, -1450, -1450,   137,
     747, -1450, -1450,   -63,   -42, -1450,   -13, -1450, -1450, -1450,
   -1450, -1450,   138, -1450, -1450, -1450,   142,   744, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450,   -58, -1450, -1450, -1450,   200,
   -1450, -1450, -1450,   206, -1450,   737,   500, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1082, -1450, -1450, -1450, -1450, -1450,   210, -1450,
   -1450, -1450,   -48, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450,   194, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,   178,
   -1450,   183,   179, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450,  -111, -1450, -1450,  -131,
   -1450, -1450, -1450, -1450, -1450,   -99, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450,  -153, -1450, -1450,
    -181, -1450, -1450, -1450, -1450, -1450, -1450, -1450,   181, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,   538,
     734, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,   576,   736,
   -1450, -1450, -1450, -1450, -1450, -1450,   180, -1450, -1450,   -52,
   -1450, -1450, -1450, -1450, -1450, -1450,  -119, -1450, -1450,  -148,
   -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450, -1450,
     190, -1450
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     800,    87,    88,    41,    68,    84,    85,   821,  1058,  1178,
    1179,   891,    43,    70,    90,   475,    91,    45,    71,   165,
     166,   167,   478,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   504,   785,   186,   505,   187,   506,   188,   189,   190,
     520,   797,   191,   192,   193,   194,   195,   542,   196,   543,
     197,   198,   199,   200,   498,   201,   202,   518,   203,   519,
     204,   205,   206,   207,   480,    47,    72,   244,   245,   246,
     552,   247,   248,   249,   250,   208,   481,   209,   482,   210,
     483,   920,   921,   922,  1099,   892,   893,   894,  1073,   895,
    1074,   896,  1075,   897,  1076,   898,   899,   596,   900,   901,
     902,   903,   904,   905,   906,   907,   908,  1087,  1364,   909,
     910,   911,   912,  1090,   913,  1091,   914,  1092,   915,  1093,
     916,  1094,   917,  1095,   211,   530,   955,   956,   957,  1119,
     958,  1120,   212,   527,   941,   942,   943,   944,   213,   529,
     949,   950,   951,   952,   214,   528,   215,   537,  1004,  1005,
    1006,  1007,  1008,   216,   533,   967,   968,   969,  1129,    63,
      80,   439,   440,   441,   611,   442,   612,   217,   534,   976,
     977,   978,   979,   980,   981,   982,   983,   218,   514,   924,
     925,   926,  1102,    49,    73,   297,   298,   299,   561,   300,
     562,   301,   563,   302,   569,   303,   566,   304,   567,   305,
     568,   219,   220,   221,   309,   310,   222,   521,   936,   937,
     938,  1111,  1264,  1265,   223,   515,    57,    77,   928,   929,
     930,  1105,    59,    78,   400,   401,   402,   403,   404,   405,
     406,   595,   407,   599,   408,   598,   409,   410,   600,   411,
     224,   516,   932,   933,   934,  1108,    61,    79,   423,   424,
     425,   426,   427,   604,   428,   429,   430,   431,   432,   433,
     608,   312,   559,  1060,  1061,  1062,  1180,    51,    74,   340,
     341,   342,   573,   343,   225,   522,   226,   523,   315,   560,
    1064,  1065,  1066,  1183,    53,    75,   360,   361,   362,   577,
     363,   364,   579,   365,   366,   227,   532,   963,   964,   965,
    1126,    55,    76,   379,   380,   381,   382,   585,   383,   586,
     384,   587,   385,   588,   386,   589,   387,   590,   388,   591,
     389,   584,   317,   570,  1068,   228,   531,   960,   961,  1123,
    1291,  1292,  1293,  1294,  1295,  1379,  1296,  1380,  1297,  1298,
     229,   535,   993,   994,   995,  1140,  1390,   996,   997,  1141,
     998,   999,   230,   231,   538,   232,   539,  1034,  1035,  1036,
    1161,  1024,  1025,  1026,  1152,  1395,  1027,  1153,  1028,  1154,
    1029,  1030,  1031,  1158,  1431,  1432,  1433,  1446,  1461,  1462,
    1463,  1473,  1032,  1156,  1424,  1425,  1426,  1440,  1469,  1427,
    1441,  1428,  1442,  1429,  1443,  1480,  1481,  1482,  1498,  1516,
    1517,  1518,  1527,  1519,  1528,   233,   540,  1043,  1044,  1045,
    1046,  1165,  1047,  1048,  1167,   234,   541,    65,    81,   454,
     455,   456,   457,   616,   458,   459,   618,   460,   461,   462,
     621,   856,   463,   622,   235,   479,    67,    82,   466,   467,
     468,   625,   469,   236,   547,  1051,  1052,  1171,  1343,  1344,
    1345,  1346,  1405,  1347,  1403,  1466,  1467,  1476,  1490,  1491,
    1492,  1502,  1493,  1494,  1495,  1496,  1506,   237,   548,  1055,
    1056,  1057
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     164,   243,   265,   320,   351,   375,    38,   398,   419,   438,
     451,  1019,   357,   990,   421,   316,   272,  1020,   422,   273,
    1021,   918,   948,   399,   420,  1253,  1254,  1255,  1263,  1269,
     251,   313,   344,   358,   377,   391,   412,   434,   274,   452,
     939,    42,  1053,   799,   311,   339,   356,   376,    31,  1512,
      32,  1513,    33,   780,   781,   782,   783,   163,   275,   252,
     314,   345,   359,   378,    30,   413,   435,    86,   453,    44,
     436,   437,   238,   239,   240,   241,   242,   266,   939,   946,
    1512,   947,  1513,  1485,    46,   267,  1486,  1487,  1488,  1489,
     784,   436,   437,   279,   321,   268,   280,   322,   984,   392,
      48,   393,   394,   868,   392,    50,   395,   396,   397,   464,
     465,   269,   476,  1114,   270,   271,  1115,   477,   281,   323,
     550,   282,   324,   799,    89,   551,   136,   137,   283,   325,
      52,   136,   137,   284,   326,   335,   352,   940,  1117,   285,
     327,  1118,   136,   137,   287,   328,   288,   329,    54,   289,
     330,   290,   331,  1417,  1387,  1388,  1389,   291,   332,   336,
     353,   163,   557,   292,   333,   864,   865,   558,   293,   334,
     276,   136,   137,   277,   571,   278,   286,   575,   294,   572,
     295,   296,   576,  1361,  1362,  1363,   306,   582,   307,   136,
     137,   308,   583,    56,   337,   354,  1000,  1001,  1002,   338,
     355,   863,   864,   865,   866,   867,   868,   869,   870,   871,
     872,   873,   874,   875,   876,   877,    58,   854,   855,   878,
     879,   880,   881,   882,   883,   884,   885,   886,   887,   888,
     889,   890,    60,  1336,   392,  1337,  1338,   985,   986,   987,
     988,   953,   954,    62,   136,   137,   136,   137,   880,   881,
     882,   130,   163,   613,   623,   136,   137,   163,   614,   624,
    1124,   136,   137,  1125,   627,   392,    64,    66,   163,   628,
      98,    99,   100,   101,   102,   103,   550,   627,   129,   136,
     137,  1070,  1071,   557,    34,    35,    36,    37,  1072,  1253,
    1254,  1255,  1263,  1269,  1096,   367,  1096,   163,   470,  1097,
     471,  1098,   130,   392,   472,   368,   369,   370,   371,   372,
     373,   374,  1418,  1419,  1420,   163,  1121,  1138,   473,   136,
     137,  1122,  1139,  1037,  1038,  1039,  1509,  1510,  1145,   592,
     136,   137,  1150,  1146,   474,   948,  1456,  1151,   827,   828,
     829,  1159,  1168,  1212,   484,   485,  1160,  1169,   990,  1276,
    1277,  1278,  1279,   835,   836,   837,   838,   623,  1019,   486,
    1019,   487,  1170,  1175,  1020,   488,  1020,  1021,  1176,  1021,
     163,  1096,  1040,   489,   849,   571,  1371,   490,  1011,   491,
    1372,   163,  1012,  1013,  1014,  1015,  1375,   163,   492,   613,
     594,  1376,  1016,  1017,  1386,  1392,  1393,  1394,   115,   116,
     117,   118,   119,   120,   121,   163,   123,   124,   125,   126,
    1159,  1406,   575,   130,   582,  1400,  1407,  1409,   163,  1410,
    1444,  1474,   593,   130,   493,  1445,  1475,   134,   970,   971,
     972,   973,   974,   975,   318,   884,   885,   886,   887,   888,
     889,   136,   137,   494,   495,   163,   346,   347,   348,   349,
     350,   136,   137,   496,   497,  1507,   163,   260,   261,   262,
    1508,   629,   630,   499,   263,   319,  1529,   260,   261,   262,
    1172,  1530,   500,  1173,   263,   319,   501,   502,   503,   164,
     793,   794,   795,   796,  1477,   602,   243,  1478,   507,   508,
     509,   510,   511,   512,   513,   517,   524,   525,   526,   536,
     265,   544,   545,   546,   320,   549,   553,   554,   555,   556,
     564,   351,   565,   316,   272,   251,   574,   273,   578,   357,
     580,   581,   375,   597,   601,   603,   609,   605,   606,   313,
     607,   610,   398,   344,   615,   617,   274,   156,   157,   419,
     358,   619,   311,   620,   252,   421,   339,   626,   399,   422,
     631,   377,   451,   356,   632,   420,   275,   633,   314,   634,
     635,   412,   345,   636,   376,   637,   638,   163,   434,   359,
     639,   647,   640,   653,   641,   266,   642,   163,   648,   643,
     378,   452,   659,   267,   644,   645,   646,   660,   649,   650,
     413,   279,   651,   268,   280,   321,   656,   435,   322,   661,
     652,   654,   669,   670,   655,   671,   673,   657,   658,   269,
     453,   662,   270,   271,   663,   668,   281,   664,   665,   282,
     323,   666,   667,   324,   674,   675,   283,   672,   676,   677,
     325,   284,   678,   679,   680,   326,   335,   285,   681,   682,
     683,   327,   287,   352,   288,   684,   328,   289,   329,   290,
     685,   330,   686,   331,   687,   291,   688,   689,   690,   332,
     336,   292,   692,   691,   693,   333,   293,   353,   276,   694,
     334,   277,   695,   278,   286,   696,   294,   697,   295,   296,
     698,   699,   700,   702,   306,   701,   307,   703,   705,   308,
     706,   707,   711,   708,   712,   337,   709,   713,   714,   715,
     338,   164,   354,   716,   243,   718,   717,   355,   719,   720,
     721,   722,   724,   725,   748,   392,   414,   393,   394,   415,
     416,   417,   727,   729,   728,   136,   137,   733,   734,   735,
     736,   737,   738,   251,   739,   740,   742,   743,   730,   989,
    1003,  1018,   136,   137,   451,   745,   746,   747,  1054,   731,
     750,   744,   754,   756,   751,   752,   757,   753,   418,   759,
     760,   859,   252,   761,   762,   765,   766,   763,   991,  1009,
    1022,   764,  1041,   452,    92,    93,   768,   769,    94,   771,
     772,   773,   778,   774,    95,    96,    97,   775,   776,   777,
     779,   788,   786,   787,   789,   790,   798,   992,  1010,  1023,
      32,  1042,   453,   802,   791,   792,   443,   444,   445,   446,
     447,   448,   449,   450,   801,   803,   804,   806,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   163,   805,   807,   808,   816,   817,   809,   810,   811,
     812,   131,   132,   133,   134,   813,   814,   818,   163,   135,
     815,   819,   820,   822,   823,   824,   858,   831,   136,   137,
     825,   826,   919,   830,   832,   138,   139,   140,   141,   142,
     143,   144,   833,   857,   145,   923,   834,   839,   840,   927,
     841,   931,   842,   146,   843,   844,   935,   845,   846,   959,
     847,   848,   147,   850,   962,   148,   852,   966,   853,  1033,
    1050,  1059,   149,  1063,   368,  1077,  1078,  1079,  1080,  1081,
     150,   151,  1082,  1083,  1084,   152,   153,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,  1085,  1086,  1088,   154,  1089,  1100,  1101,   155,  1103,
    1104,  1106,  1107,  1110,  1109,  1113,  1193,  1112,  1128,  1116,
    1127,  1131,  1130,  1132,   156,   157,   158,   159,   160,   161,
    1133,  1134,  1135,  1136,  1137,  1142,  1143,  1144,   162,  1147,
    1148,  1149,  1155,  1157,  1163,  1177,  1162,  1164,  1166,  1174,
    1182,  1185,  1181,  1195,   163,  1184,  1188,  1187,  1186,  1189,
    1190,  1191,  1192,  1194,  1202,  1205,  1196,  1206,  1207,  1208,
    1197,  1198,  1209,  1210,  1273,  1274,  1199,  1200,  1311,  1201,
    1312,   265,  1203,  1321,   398,  1322,  1204,   419,  1304,  1305,
    1220,  1306,  1307,   421,   316,   272,  1308,   422,   273,  1309,
     399,  1313,  1280,   420,  1227,   375,  1252,  1228,   438,  1314,
     313,  1315,  1317,   412,  1318,  1319,   434,   274,  1287,  1267,
    1323,  1324,  1325,   311,   989,  1326,  1229,  1327,  1331,  1003,
    1332,  1289,  1266,  1333,   377,  1334,  1349,   275,  1018,   314,
    1018,  1351,   413,  1352,  1288,   435,  1230,   376,  1268,  1357,
    1339,  1373,  1358,   991,  1054,  1374,   266,  1359,  1009,   320,
    1290,  1381,   351,   378,   267,  1221,  1340,  1022,  1360,  1022,
     357,  1365,   279,  1222,   268,   280,  1041,  1281,  1366,  1341,
    1367,  1234,   992,  1223,  1235,  1282,  1368,  1010,   344,  1370,
     269,   358,  1377,   270,   271,  1283,  1023,   281,  1023,  1224,
     282,   339,  1225,  1226,   356,  1042,  1236,   283,  1342,  1237,
    1378,  1284,   284,  1382,  1285,  1286,  1238,   345,   285,  1383,
     359,  1239,  1256,   287,  1384,   288,  1385,  1240,   289,  1391,
     290,  1396,  1242,  1397,  1243,  1398,   291,  1244,  1399,  1245,
    1404,  1412,   292,  1401,  1413,  1246,  1257,   293,  1430,   276,
     321,  1247,   277,   322,   278,   286,  1248,   294,  1231,   295,
     296,  1232,  1408,  1233,  1241,   306,  1249,   307,  1250,  1251,
     308,  1434,  1436,  1448,  1260,   323,  1261,  1447,   324,  1262,
    1449,  1258,  1451,  1452,  1435,   325,  1259,  1453,  1454,  1465,
     326,   335,  1468,  1472,   352,  1483,   327,  1414,  1415,  1438,
    1439,   328,  1479,   329,  1499,  1500,   330,  1450,   331,  1503,
    1504,  1505,  1521,  1470,   332,   336,  1471,  1522,   353,  1501,
     333,  1525,  1523,  1533,  1524,   334,  1531,  1532,  1534,  1536,
    1537,   945,  1069,  1213,   851,   704,   710,  1211,  1369,  1275,
    1271,  1303,  1272,  1320,  1302,   758,  1310,  1215,  1214,  1411,
     337,  1270,  1217,   354,  1220,   338,   860,   862,   355,   723,
    1216,  1219,   390,  1280,   749,  1218,  1354,  1353,  1227,   755,
    1252,  1228,   726,  1356,  1402,  1355,   732,  1421,  1301,  1287,
     741,  1067,  1300,  1267,  1299,  1339,  1416,  1464,  1328,  1316,
    1229,  1330,  1289,  1484,  1329,  1455,  1266,  1520,  1535,  1335,
     861,  1340,  1348,  1049,  1437,  1288,  1422,   767,  1497,  1526,
    1230,     0,  1268,   770,  1341,  1350,     0,     0,     0,     0,
       0,  1290,     0,  1421,     0,  1457,     0,     0,     0,  1221,
       0,     0,     0,     0,     0,  1423,     0,  1222,  1281,     0,
       0,  1458,     0,  1342,     0,  1234,  1282,  1223,  1235,     0,
       0,     0,  1422,  1457,  1459,     0,  1283,     0,     0,     0,
       0,     0,     0,  1224,     0,     0,  1225,  1226,     0,  1458,
    1236,     0,  1284,  1237,     0,  1285,  1286,  1511,     0,     0,
    1238,  1423,  1459,  1460,     0,  1239,  1256,     0,     0,     0,
       0,  1240,     0,     0,     0,     0,  1242,     0,  1243,     0,
       0,  1244,     0,  1245,     0,     0,  1514,     0,  1511,  1246,
    1257,  1460,     0,     0,     0,  1247,     0,     0,     0,     0,
    1248,     0,  1231,     0,     0,  1232,     0,  1233,  1241,     0,
    1249,     0,  1250,  1251,     0,  1515,     0,  1514,  1260,     0,
    1261,     0,     0,  1262,     0,  1258,     0,     0,     0,     0,
    1259,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,     0,     0,  1515,     0,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,     0,     0,   130,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   132,   133,   134,     0,     0,
       0,     0,     0,   253,     0,   254,     0,     0,     0,     0,
       0,   136,   137,   255,   256,   257,   258,   259,   138,   139,
     140,     0,     0,     0,     0,     0,     0,   260,   261,   262,
       0,     0,     0,     0,   263,     0,   146,     0,     0,     0,
       0,     0,     0,     0,   264,     0,     0,     0,     0,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,     0,     0,     0,     0,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
       0,   130,   392,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   132,   133,   134,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   156,   157,   136,
     137,     0,   256,   257,     0,   259,   138,   139,   140,     0,
       0,     0,     0,     0,     0,   260,   261,   262,     0,     0,
       0,     0,   263,     0,     0,     0,     0,   163,     0,     0,
       0,     0,   264,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   156,   157,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   163
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   812,    75,   810,    79,    73,    73,   812,    79,    73,
     812,   777,   804,    78,    79,  1111,  1111,  1111,  1111,  1111,
      72,    73,    74,    75,    76,    24,    78,    79,    73,    81,
     144,     7,   226,   677,    73,    74,    75,    76,     5,  1498,
       7,  1498,     9,   207,   208,   209,   210,   241,    73,    72,
      73,    74,    75,    76,     0,    78,    79,   241,    81,     7,
     150,   151,    16,    17,    18,    19,    20,    73,   144,   145,
    1529,   147,  1529,   218,     7,    73,   221,   222,   223,   224,
     244,   150,   151,    73,    74,    73,    73,    74,    24,    88,
       7,    90,    91,    29,    88,     7,    95,    96,    97,    13,
      14,    73,     3,     3,    73,    73,     6,     8,    73,    74,
       3,    73,    74,   757,    10,     8,   115,   116,    73,    74,
       7,   115,   116,    73,    74,    74,    75,   241,     3,    73,
      74,     6,   115,   116,    73,    74,    73,    74,     7,    73,
      74,    73,    74,    24,   160,   161,   162,    73,    74,    74,
      75,   241,     3,    73,    74,    25,    26,     8,    73,    74,
      73,   115,   116,    73,     3,    73,    73,     3,    73,     8,
      73,    73,     8,    39,    40,    41,    73,     3,    73,   115,
     116,    73,     8,     7,    74,    75,   169,   170,   171,    74,
      75,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,     7,   204,   205,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,     7,   217,    88,   219,   220,   163,   164,   165,
     166,   129,   130,     7,   115,   116,   115,   116,    44,    45,
      46,    87,   241,     3,     3,   115,   116,   241,     8,     8,
       3,   115,   116,     6,     3,    88,     7,     7,   241,     8,
      55,    56,    57,    58,    59,    60,     3,     3,    86,   115,
     116,     8,     8,     3,   241,   242,   243,   244,     8,  1375,
    1375,  1375,  1375,  1375,     3,   131,     3,   241,     6,     8,
       3,     8,    87,    88,     4,   141,   142,   143,   144,   145,
     146,   147,   183,   184,   185,   241,     3,     3,     8,   115,
     116,     8,     8,   192,   193,   194,   186,   187,     3,     8,
     115,   116,     3,     8,     3,  1117,   190,     8,   718,   719,
     720,     3,     3,  1099,     4,     4,     8,     8,  1145,   134,
     135,   136,   137,   733,   734,   735,   736,     3,  1159,     4,
    1161,     4,     8,     3,  1159,     4,  1161,  1159,     8,  1161,
     241,     3,   241,     4,   754,     3,     8,     4,   174,     4,
       8,   241,   178,   179,   180,   181,     3,   241,     4,     3,
       8,     8,   188,   189,     8,   175,   176,   177,    72,    73,
      74,    75,    76,    77,    78,   241,    80,    81,    82,    83,
       3,     3,     3,    87,     3,     8,     8,     8,   241,     8,
       3,     3,     3,    87,     4,     8,     8,   101,   153,   154,
     155,   156,   157,   158,   108,    48,    49,    50,    51,    52,
      53,   115,   116,     4,     4,   241,   110,   111,   112,   113,
     114,   115,   116,     4,     4,     3,   241,   131,   132,   133,
       8,   471,   472,     4,   138,   139,     3,   131,   132,   133,
       3,     8,     4,     6,   138,   139,     4,     4,     4,   550,
     102,   103,   104,   105,     3,     8,   557,     6,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     571,     4,     4,     4,   575,     4,     4,     4,     4,     4,
       4,   582,     4,   571,   571,   557,     4,   571,     4,   582,
       4,     4,   593,     4,     4,     3,     8,     4,     4,   571,
       4,     3,   603,   575,     4,     4,   571,   211,   212,   610,
     582,     4,   571,     4,   557,   610,   575,     4,   603,   610,
     241,   593,   623,   582,     4,   610,   571,     4,   571,     4,
       4,   603,   575,     4,   593,     4,     4,   241,   610,   582,
     242,   244,   242,     4,   242,   571,   242,   241,   243,   242,
     593,   623,     4,   571,   242,   242,   242,     4,   243,   243,
     603,   571,   242,   571,   571,   575,   244,   610,   575,     4,
     242,   242,     4,     4,   242,     4,     4,   244,   244,   571,
     623,   244,   571,   571,   244,   244,   571,   243,   242,   571,
     575,   242,   242,   575,     4,     4,   571,   242,     4,     4,
     575,   571,     4,   244,   244,   575,   575,   571,   244,     4,
       4,   575,   571,   582,   571,     4,   575,   571,   575,   571,
       4,   575,     4,   575,     4,   571,     4,     4,     4,   575,
     575,   571,     4,   242,     4,   575,   571,   582,   571,     4,
     575,   571,     4,   571,   571,     4,   571,     4,   571,   571,
       4,   244,   244,     4,   571,   244,   571,     4,     4,   571,
     244,   244,     4,   242,     4,   575,   242,     4,     4,     4,
     575,   772,   582,   242,   775,     4,   244,   582,     4,     4,
       4,     4,     4,   242,   244,    88,    89,    90,    91,    92,
      93,    94,     4,     4,   242,   115,   116,     4,     4,     4,
       4,     4,     4,   775,     4,     4,     4,     4,   242,   810,
     811,   812,   115,   116,   815,     4,     4,     4,   819,   242,
       4,   242,     4,     4,   244,   244,     4,   244,   131,   244,
       4,   771,   775,   242,     4,     4,     4,   242,   810,   811,
     812,   242,   814,   815,    11,    12,     4,   242,    15,     4,
       7,   241,     5,     7,    21,    22,    23,     7,     7,     7,
     241,     5,   241,   241,     5,     5,     5,   810,   811,   812,
       7,   814,   815,     5,   241,   241,   196,   197,   198,   199,
     200,   201,   202,   203,   241,     5,     5,     5,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,   241,     7,     5,     5,   241,   241,     7,     7,     7,
       7,    98,    99,   100,   101,     5,     7,     5,   241,   106,
       7,     7,     5,     5,     5,   241,     5,     7,   115,   116,
     241,   241,     7,   241,   241,   122,   123,   124,   125,   126,
     127,   128,   241,   206,   131,     7,   241,   241,   241,     7,
     241,     7,   241,   140,   241,   241,     7,   241,   241,     7,
     241,   241,   149,   241,     7,   152,   241,     7,   241,     7,
       7,     7,   159,     7,   141,     4,     4,     4,     4,     4,
     167,   168,     4,     4,     4,   172,   173,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,     4,     4,     4,   191,     4,     6,     3,   195,     6,
       3,     6,     3,     3,     6,     3,   244,     6,     3,     6,
       6,     3,     6,     4,   211,   212,   213,   214,   215,   216,
       4,     4,     4,     4,     4,     4,     4,     4,   225,     4,
       4,     4,     4,     4,     3,   241,     6,     4,     4,     4,
       3,     3,     6,   244,   241,     6,     4,     6,     8,     4,
       4,     4,   242,   242,     4,     4,   242,     4,     4,     4,
     242,   242,     4,     4,     4,     4,   242,   242,     4,   242,
       4,  1102,   244,     4,  1105,     4,   242,  1108,   242,   242,
    1111,   242,   242,  1108,  1102,  1102,   242,  1108,  1102,   242,
    1105,   242,  1123,  1108,  1111,  1126,  1111,  1111,  1129,   242,
    1102,   242,   244,  1105,   242,   242,  1108,  1102,  1123,  1111,
       4,   242,     4,  1102,  1145,   244,  1111,     4,   244,  1150,
       4,  1123,  1111,   242,  1126,     4,   244,  1102,  1159,  1102,
    1161,     6,  1105,     3,  1123,  1108,  1111,  1126,  1111,   241,
    1171,     8,   241,  1145,  1175,     8,  1102,   241,  1150,  1180,
    1123,     4,  1183,  1126,  1102,  1111,  1171,  1159,   241,  1161,
    1183,   241,  1102,  1111,  1102,  1102,  1168,  1123,   241,  1171,
     241,  1111,  1145,  1111,  1111,  1123,   241,  1150,  1180,   241,
    1102,  1183,   241,  1102,  1102,  1123,  1159,  1102,  1161,  1111,
    1102,  1180,  1111,  1111,  1183,  1168,  1111,  1102,  1171,  1111,
     241,  1123,  1102,     4,  1123,  1123,  1111,  1180,  1102,     8,
    1183,  1111,  1111,  1102,     3,  1102,     8,  1111,  1102,   241,
    1102,   241,  1111,   241,  1111,     7,  1102,  1111,     5,  1111,
       4,     4,  1102,   241,     4,  1111,  1111,  1102,     7,  1102,
    1180,  1111,  1102,  1180,  1102,  1102,  1111,  1102,  1111,  1102,
    1102,  1111,   241,  1111,  1111,  1102,  1111,  1102,  1111,  1111,
    1102,     4,     4,     3,  1111,  1180,  1111,     6,  1180,  1111,
       5,  1111,     4,     4,   242,  1180,  1111,     4,     4,     7,
    1180,  1180,   182,     5,  1183,     4,  1180,   244,   244,   241,
     241,  1180,     7,  1180,     6,     3,  1180,   241,  1180,     4,
       4,     4,     4,   241,  1180,  1180,   241,   244,  1183,   241,
    1180,     4,   242,     4,   242,  1180,   241,   241,     4,   241,
     241,   803,   858,  1101,   757,   550,   557,  1096,  1209,  1121,
    1114,  1131,  1117,  1150,  1129,   613,  1138,  1104,  1102,  1375,
    1180,  1113,  1107,  1183,  1375,  1180,   772,   775,  1183,   571,
    1105,  1110,    77,  1384,   603,  1108,  1182,  1180,  1375,   610,
    1375,  1375,   575,  1185,  1334,  1183,   582,  1398,  1128,  1384,
     593,   831,  1126,  1375,  1124,  1406,  1384,  1448,  1159,  1145,
    1375,  1163,  1384,  1474,  1161,  1444,  1375,  1500,  1529,  1168,
     774,  1406,  1172,   815,  1406,  1384,  1398,   623,  1477,  1507,
    1375,    -1,  1375,   627,  1406,  1175,    -1,    -1,    -1,    -1,
      -1,  1384,    -1,  1444,    -1,  1446,    -1,    -1,    -1,  1375,
      -1,    -1,    -1,    -1,    -1,  1398,    -1,  1375,  1384,    -1,
      -1,  1446,    -1,  1406,    -1,  1375,  1384,  1375,  1375,    -1,
      -1,    -1,  1444,  1474,  1446,    -1,  1384,    -1,    -1,    -1,
      -1,    -1,    -1,  1375,    -1,    -1,  1375,  1375,    -1,  1474,
    1375,    -1,  1384,  1375,    -1,  1384,  1384,  1498,    -1,    -1,
    1375,  1444,  1474,  1446,    -1,  1375,  1375,    -1,    -1,    -1,
      -1,  1375,    -1,    -1,    -1,    -1,  1375,    -1,  1375,    -1,
      -1,  1375,    -1,  1375,    -1,    -1,  1498,    -1,  1529,  1375,
    1375,  1474,    -1,    -1,    -1,  1375,    -1,    -1,    -1,    -1,
    1375,    -1,  1375,    -1,    -1,  1375,    -1,  1375,  1375,    -1,
    1375,    -1,  1375,  1375,    -1,  1498,    -1,  1529,  1375,    -1,
    1375,    -1,    -1,  1375,    -1,  1375,    -1,    -1,    -1,    -1,
    1375,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    -1,    -1,  1529,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    -1,    -1,    87,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    99,   100,   101,    -1,    -1,
      -1,    -1,    -1,   107,    -1,   109,    -1,    -1,    -1,    -1,
      -1,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,    -1,    -1,    -1,    -1,    -1,    -1,   131,   132,   133,
      -1,    -1,    -1,    -1,   138,    -1,   140,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   148,    -1,    -1,    -1,    -1,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    -1,    -1,    -1,    -1,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      -1,    87,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    99,   100,   101,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   211,   212,   115,
     116,    -1,   118,   119,    -1,   121,   122,   123,   124,    -1,
      -1,    -1,    -1,    -1,    -1,   131,   132,   133,    -1,    -1,
      -1,    -1,   138,    -1,    -1,    -1,    -1,   241,    -1,    -1,
      -1,    -1,   148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   211,   212,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   241
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
       0,     5,     7,     9,   241,   242,   243,   244,   261,   262,
     263,   268,     7,   277,     7,   282,     7,   340,     7,   458,
       7,   542,     7,   559,     7,   576,     7,   491,     7,   497,
       7,   521,     7,   434,     7,   692,     7,   711,   269,   264,
     278,   283,   341,   459,   543,   560,   577,   492,   498,   522,
     435,   693,   712,   261,   270,   271,   241,   266,   267,    10,
     279,   281,    11,    12,    15,    21,    22,    23,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    98,    99,   100,   101,   106,   115,   116,   122,   123,
     124,   125,   126,   127,   128,   131,   140,   149,   152,   159,
     167,   168,   172,   173,   191,   195,   211,   212,   213,   214,
     215,   216,   225,   241,   276,   284,   285,   286,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   308,   310,   312,   313,
     314,   317,   318,   319,   320,   321,   323,   325,   326,   327,
     328,   330,   331,   333,   335,   336,   337,   338,   350,   352,
     354,   399,   407,   413,   419,   421,   428,   442,   452,   476,
     477,   478,   481,   489,   515,   549,   551,   570,   600,   615,
     627,   628,   630,   680,   690,   709,   718,   742,    16,    17,
      18,    19,    20,   276,   342,   343,   344,   346,   347,   348,
     349,   549,   551,   107,   109,   117,   118,   119,   120,   121,
     131,   132,   133,   138,   148,   276,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   302,
     303,   304,   305,   308,   310,   312,   313,   314,   317,   318,
     319,   320,   321,   323,   325,   331,   333,   460,   461,   462,
     464,   466,   468,   470,   472,   474,   476,   477,   478,   479,
     480,   515,   536,   549,   551,   553,   570,   597,   108,   139,
     276,   302,   303,   304,   305,   308,   310,   312,   314,   317,
     318,   319,   320,   321,   323,   468,   470,   472,   474,   515,
     544,   545,   546,   548,   549,   551,   110,   111,   112,   113,
     114,   276,   468,   470,   472,   474,   515,   548,   549,   551,
     561,   562,   563,   565,   566,   568,   569,   131,   141,   142,
     143,   144,   145,   146,   147,   276,   515,   549,   551,   578,
     579,   580,   581,   583,   585,   587,   589,   591,   593,   595,
     489,    24,    88,    90,    91,    95,    96,    97,   276,   371,
     499,   500,   501,   502,   503,   504,   505,   507,   509,   511,
     512,   514,   549,   551,    89,    92,    93,    94,   131,   276,
     371,   503,   509,   523,   524,   525,   526,   527,   529,   530,
     531,   532,   533,   534,   549,   551,   150,   151,   276,   436,
     437,   438,   440,   196,   197,   198,   199,   200,   201,   202,
     203,   276,   549,   551,   694,   695,   696,   697,   699,   700,
     702,   703,   704,   707,    13,    14,   713,   714,   715,   717,
       6,     3,     4,     8,     3,   280,     3,     8,   287,   710,
     339,   351,   353,   355,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   329,     4,
       4,     4,     4,     4,   306,   309,   311,     4,     4,     4,
       4,     4,     4,     4,   453,   490,   516,     4,   332,   334,
     315,   482,   550,   552,     4,     4,     4,   408,   420,   414,
     400,   601,   571,   429,   443,   616,     4,   422,   629,   631,
     681,   691,   322,   324,     4,     4,     4,   719,   743,     4,
       3,     8,   345,     4,     4,     4,     4,     3,     8,   537,
     554,   463,   465,   467,     4,     4,   471,   473,   475,   469,
     598,     3,     8,   547,     4,     3,     8,   564,     4,   567,
       4,     4,     3,     8,   596,   582,   584,   586,   588,   590,
     592,   594,     8,     3,     8,   506,   372,     4,   510,   508,
     513,     4,     8,     3,   528,     4,     4,     4,   535,     8,
       3,   439,   441,     3,     8,     4,   698,     4,   701,     4,
       4,   705,   708,     3,     8,   716,     4,     3,     8,   261,
     261,   241,     4,     4,     4,     4,     4,     4,     4,   242,
     242,   242,   242,   242,   242,   242,   242,   244,   243,   243,
     243,   242,   242,     4,   242,   242,   244,   244,   244,     4,
       4,     4,   244,   244,   243,   242,   242,   242,   244,     4,
       4,     4,   242,     4,     4,     4,     4,     4,     4,   244,
     244,   244,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   242,     4,     4,     4,     4,     4,     4,     4,   244,
     244,   244,     4,     4,   285,     4,   244,   244,   242,   242,
     343,     4,     4,     4,     4,     4,   242,   244,     4,     4,
       4,     4,     4,   461,     4,   242,   545,     4,   242,     4,
     242,   242,   562,     4,     4,     4,     4,     4,     4,     4,
       4,   580,     4,     4,   242,     4,     4,     4,   244,   501,
       4,   244,   244,   244,     4,   525,     4,     4,   437,   244,
       4,   242,     4,   242,   242,     4,     4,   695,     4,   242,
     714,     4,     7,   241,     7,     7,     7,     7,     5,   241,
     207,   208,   209,   210,   244,   307,   241,   241,     5,     5,
       5,   241,   241,   102,   103,   104,   105,   316,     5,   263,
     265,   241,     5,     5,     5,     7,     5,     5,     5,     7,
       7,     7,     7,     5,     7,     7,   241,   241,     5,     7,
       5,   272,     5,     5,   241,   241,   241,   272,   272,   272,
     241,     7,   241,   241,   241,   272,   272,   272,   272,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   272,
     241,   265,   241,   241,   204,   205,   706,   206,     5,   261,
     284,   713,   342,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,   276,   360,   361,   362,   364,   366,   368,   370,   371,
     373,   374,   375,   376,   377,   378,   379,   380,   381,   384,
     385,   386,   387,   389,   391,   393,   395,   397,   360,     7,
     356,   357,   358,     7,   454,   455,   456,     7,   493,   494,
     495,     7,   517,   518,   519,     7,   483,   484,   485,   144,
     241,   409,   410,   411,   412,   270,   145,   147,   411,   415,
     416,   417,   418,   129,   130,   401,   402,   403,   405,     7,
     602,   603,     7,   572,   573,   574,     7,   430,   431,   432,
     153,   154,   155,   156,   157,   158,   444,   445,   446,   447,
     448,   449,   450,   451,    24,   163,   164,   165,   166,   276,
     373,   549,   551,   617,   618,   619,   622,   623,   625,   626,
     169,   170,   171,   276,   423,   424,   425,   426,   427,   549,
     551,   174,   178,   179,   180,   181,   188,   189,   276,   387,
     389,   391,   549,   551,   636,   637,   638,   641,   643,   645,
     646,   647,   657,     7,   632,   633,   634,   192,   193,   194,
     241,   549,   551,   682,   683,   684,   685,   687,   688,   694,
       7,   720,   721,   226,   276,   744,   745,   746,   273,     7,
     538,   539,   540,     7,   555,   556,   557,   581,   599,   356,
       8,     8,     8,   363,   365,   367,   369,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   382,     4,     4,
     388,   390,   392,   394,   396,   398,     3,     8,     8,   359,
       6,     3,   457,     6,     3,   496,     6,     3,   520,     6,
       3,   486,     6,     3,     3,     6,     6,     3,     6,   404,
     406,     3,     8,   604,     3,     6,   575,     6,     3,   433,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
     620,   624,     4,     4,     4,     3,     8,     4,     4,     4,
       3,     8,   639,   642,   644,     4,   658,     4,   648,     3,
       8,   635,     6,     3,     4,   686,     4,   689,     3,     8,
       8,   722,     3,     6,     4,     3,     8,   241,   274,   275,
     541,     6,     3,   558,     6,     3,     8,     6,     4,     4,
       4,     4,   242,   244,   242,   244,   242,   242,   242,   242,
     242,   242,     4,   244,   242,     4,     4,     4,     4,     4,
       4,   361,   360,   358,   460,   456,   499,   495,   523,   519,
     276,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   302,   303,   304,   305,   308,   310,
     312,   313,   314,   317,   318,   319,   320,   321,   323,   325,
     331,   333,   371,   452,   464,   466,   468,   470,   472,   474,
     476,   477,   478,   480,   487,   488,   515,   549,   551,   597,
     485,   410,   416,     4,     4,   402,   134,   135,   136,   137,
     276,   288,   289,   290,   291,   292,   293,   371,   515,   549,
     551,   605,   606,   607,   608,   609,   611,   613,   614,   603,
     578,   574,   436,   432,   242,   242,   242,   242,   242,   242,
     445,     4,     4,   242,   242,   242,   618,   244,   242,   242,
     424,     4,     4,     4,   242,     4,   244,     4,   637,   636,
     634,   244,     4,   242,     4,   683,   217,   219,   220,   276,
     371,   549,   551,   723,   724,   725,   726,   728,   721,   244,
     745,     6,     3,   544,   540,   561,   557,   241,   241,   241,
     241,    39,    40,    41,   383,   241,   241,   241,   241,   395,
     241,     8,     8,     8,     8,     3,     8,   241,   241,   610,
     612,     4,     4,     8,     3,     8,     8,   160,   161,   162,
     621,   241,   175,   176,   177,   640,   241,   241,     7,     5,
       8,   241,   261,   729,     4,   727,     3,     8,   241,     8,
       8,   488,     4,     4,   244,   244,   607,    24,   183,   184,
     185,   276,   549,   551,   659,   660,   661,   664,   666,   668,
       7,   649,   650,   651,     4,   242,     4,   724,   241,   241,
     662,   665,   667,   669,     3,     8,   652,     6,     3,     5,
     241,     4,     4,     4,     4,   660,   190,   276,   371,   549,
     551,   653,   654,   655,   651,     7,   730,   731,   182,   663,
     241,   241,     5,   656,     3,     8,   732,     3,     6,     7,
     670,   671,   672,     4,   654,   218,   221,   222,   223,   224,
     733,   734,   735,   737,   738,   739,   740,   731,   673,     6,
       3,   241,   736,     4,     4,     4,   741,     3,     8,   186,
     187,   276,   364,   366,   549,   551,   674,   675,   676,   678,
     672,     4,   244,   242,   242,     4,   734,   677,   679,     3,
       8,   241,   241,     4,     4,   675,   241,   241
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
     302,   303,   304,   306,   305,   307,   307,   307,   307,   307,
     309,   308,   311,   310,   312,   313,   315,   314,   316,   316,
     316,   316,   317,   318,   319,   320,   322,   321,   324,   323,
     325,   326,   327,   329,   328,   330,   332,   331,   334,   333,
     335,   336,   337,   339,   338,   341,   340,   342,   342,   342,
     343,   343,   343,   343,   343,   343,   343,   343,   345,   344,
     346,   347,   348,   349,   351,   350,   353,   352,   355,   354,
     356,   356,   357,   357,   357,   359,   358,   360,   360,   360,
     361,   361,   361,   361,   361,   361,   361,   361,   361,   361,
     361,   361,   361,   361,   361,   361,   361,   361,   361,   361,
     361,   361,   361,   361,   361,   363,   362,   365,   364,   367,
     366,   369,   368,   370,   372,   371,   373,   374,   375,   376,
     377,   378,   379,   380,   382,   381,   383,   383,   383,   384,
     385,   386,   388,   387,   390,   389,   392,   391,   394,   393,
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
     461,   461,   461,   461,   461,   461,   461,   461,   463,   462,
     465,   464,   467,   466,   469,   468,   471,   470,   473,   472,
     475,   474,   476,   477,   478,   479,   480,   482,   481,   483,
     483,   484,   484,   484,   486,   485,   487,   487,   487,   488,
     488,   488,   488,   488,   488,   488,   488,   488,   488,   488,
     488,   488,   488,   488,   488,   488,   488,   488,   488,   488,
     488,   488,   488,   488,   488,   488,   488,   488,   488,   488,
     488,   488,   488,   488,   488,   488,   488,   488,   488,   488,
     488,   488,   488,   488,   488,   488,   488,   490,   489,   492,
     491,   493,   493,   494,   494,   494,   496,   495,   498,   497,
     499,   499,   500,   500,   500,   501,   501,   501,   501,   501,
     501,   501,   501,   501,   501,   502,   503,   504,   506,   505,
     508,   507,   510,   509,   511,   513,   512,   514,   516,   515,
     517,   517,   518,   518,   518,   520,   519,   522,   521,   523,
     523,   524,   524,   524,   525,   525,   525,   525,   525,   525,
     525,   525,   525,   525,   525,   526,   528,   527,   529,   530,
     531,   532,   533,   535,   534,   537,   536,   538,   538,   539,
     539,   539,   541,   540,   543,   542,   544,   544,   544,   545,
     545,   545,   545,   545,   545,   545,   545,   545,   545,   545,
     545,   545,   545,   545,   545,   545,   545,   545,   545,   545,
     545,   545,   545,   547,   546,   548,   550,   549,   552,   551,
     554,   553,   555,   555,   556,   556,   556,   558,   557,   560,
     559,   561,   561,   561,   562,   562,   562,   562,   562,   562,
     562,   562,   562,   562,   562,   562,   562,   562,   564,   563,
     565,   567,   566,   568,   569,   571,   570,   572,   572,   573,
     573,   573,   575,   574,   577,   576,   578,   578,   579,   579,
     579,   580,   580,   580,   580,   580,   580,   580,   580,   580,
     580,   580,   580,   582,   581,   584,   583,   586,   585,   588,
     587,   590,   589,   592,   591,   594,   593,   596,   595,   598,
     597,   599,   601,   600,   602,   602,   602,   604,   603,   605,
     605,   606,   606,   606,   607,   607,   607,   607,   607,   607,
     607,   607,   607,   607,   607,   607,   607,   607,   607,   608,
     610,   609,   612,   611,   613,   614,   616,   615,   617,   617,
     617,   618,   618,   618,   618,   618,   618,   618,   618,   618,
     620,   619,   621,   621,   621,   622,   624,   623,   625,   626,
     627,   629,   628,   631,   630,   632,   632,   633,   633,   633,
     635,   634,   636,   636,   636,   637,   637,   637,   637,   637,
     637,   637,   637,   637,   637,   637,   637,   637,   639,   638,
     640,   640,   640,   642,   641,   644,   643,   645,   646,   648,
     647,   649,   649,   650,   650,   650,   652,   651,   653,   653,
     653,   654,   654,   654,   654,   654,   656,   655,   658,   657,
     659,   659,   659,   660,   660,   660,   660,   660,   660,   660,
     662,   661,   663,   665,   664,   667,   666,   669,   668,   670,
     670,   671,   671,   671,   673,   672,   674,   674,   674,   675,
     675,   675,   675,   675,   675,   675,   677,   676,   679,   678,
     681,   680,   682,   682,   682,   683,   683,   683,   683,   683,
     683,   684,   686,   685,   687,   689,   688,   691,   690,   693,
     692,   694,   694,   694,   695,   695,   695,   695,   695,   695,
     695,   695,   695,   695,   695,   696,   698,   697,   699,   701,
     700,   702,   703,   705,   704,   706,   706,   708,   707,   710,
     709,   712,   711,   713,   713,   713,   714,   714,   716,   715,
     717,   719,   718,   720,   720,   720,   722,   721,   723,   723,
     723,   724,   724,   724,   724,   724,   724,   724,   725,   727,
     726,   729,   728,   730,   730,   730,   732,   731,   733,   733,
     733,   734,   734,   734,   734,   734,   736,   735,   737,   738,
     739,   741,   740,   743,   742,   744,   744,   744,   745,   745,
     746
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
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     1,     1,     1,     3,
       3,     3,     0,     4,     0,     4,     0,     4,     0,     4,
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
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     3,     3,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     1,     3,     2,     1,
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
  "\"trust-anchor\"", "\"cert-file\"", "\"key-file\"", "\"key-password\"",
  "\"ssl-mode\"", "\"disable\"", "\"prefer\"", "\"require\"",
  "\"verify-ca\"", "\"verify-full\"", "\"cipher-list\"",
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
  "key_password", "$@47", "ssl_mode", "$@48", "cipher_list", "$@49",
  "sanity_checks", "$@50", "sanity_checks_params", "sanity_checks_param",
  "lease_checks", "$@51", "extended_info_checks", "$@52", "mac_sources",
  "$@53", "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@54",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@55",
  "dhcp_multi_threading", "$@56", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@57", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@58",
  "sub_hooks_library", "$@59", "hooks_params", "hooks_param", "library",
  "$@60", "parameters", "$@61", "expired_leases_processing", "$@62",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@63",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@64",
  "sub_subnet6", "$@65", "subnet6_params", "subnet6_param", "subnet",
  "$@66", "interface", "$@67", "interface_id", "$@68", "client_class",
  "$@69", "network_client_classes", "$@70", "require_client_classes",
  "$@71", "evaluate_additional_classes", "$@72", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "id",
  "rapid_commit", "shared_networks", "$@73", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@74",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@75", "sub_option_def_list", "$@76", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@77",
  "sub_option_def", "$@78", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@79",
  "option_def_record_types", "$@80", "space", "$@81", "option_def_space",
  "option_def_encapsulate", "$@82", "option_def_array", "option_data_list",
  "$@83", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@84", "sub_option_data", "$@85",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@86",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "option_data_never_send",
  "option_data_client_classes", "$@87", "pools_list", "$@88",
  "pools_list_content", "not_empty_pools_list", "pool_list_entry", "$@89",
  "sub_pool6", "$@90", "pool_params", "pool_param", "pool_entry", "$@91",
  "pool_id", "user_context", "$@92", "comment", "$@93", "pd_pools_list",
  "$@94", "pd_pools_list_content", "not_empty_pd_pools_list",
  "pd_pool_entry", "$@95", "sub_pd_pool", "$@96", "pd_pool_params",
  "pd_pool_param", "pd_prefix", "$@97", "pd_prefix_len", "excluded_prefix",
  "$@98", "excluded_prefix_len", "pd_delegated_len", "reservations",
  "$@99", "reservations_list", "not_empty_reservations_list",
  "reservation", "$@100", "sub_reservation", "$@101", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@102", "prefixes", "$@103", "excluded_prefixes", "$@104", "duid",
  "$@105", "hw_address", "$@106", "hostname", "$@107", "flex_id_value",
  "$@108", "reservation_client_classes", "$@109", "relay", "$@110",
  "relay_map", "client_classes", "$@111", "client_classes_list",
  "client_class_entry", "$@112", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@113",
  "client_class_template_test", "$@114", "only_if_required",
  "only_in_additional_list", "server_id", "$@115", "server_id_params",
  "server_id_param", "server_id_type", "$@116", "duid_type", "htype",
  "identifier", "$@117", "time", "enterprise_id", "dhcp4o6_port",
  "control_socket", "$@118", "control_sockets", "$@119",
  "control_socket_list", "not_empty_control_socket_list",
  "control_socket_entry", "$@120", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@121",
  "control_socket_type_value", "control_socket_name", "$@122",
  "control_socket_address", "$@123", "control_socket_port",
  "cert_required", "http_headers", "$@124", "http_header_list",
  "not_empty_http_header_list", "http_header", "$@125",
  "http_header_params", "http_header_param", "header_value", "$@126",
  "authentication", "$@127", "auth_params", "auth_param", "auth_type",
  "$@128", "auth_type_value", "realm", "$@129", "directory", "$@130",
  "clients", "$@131", "clients_list", "not_empty_clients_list",
  "basic_auth", "$@132", "clients_params", "clients_param", "user_file",
  "$@133", "password_file", "$@134", "dhcp_queue_control", "$@135",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@136", "capacity", "arbitrary_map_entry", "$@137",
  "dhcp_ddns", "$@138", "sub_dhcp_ddns", "$@139", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@140", "server_port",
  "sender_ip", "$@141", "sender_port", "max_queue_size", "ncr_protocol",
  "$@142", "ncr_protocol_value", "ncr_format", "$@143", "config_control",
  "$@144", "sub_config_control", "$@145", "config_control_params",
  "config_control_param", "config_databases", "$@146",
  "config_fetch_wait_time", "loggers", "$@147", "loggers_entries",
  "logger_entry", "$@148", "logger_params", "logger_param", "debuglevel",
  "severity", "$@149", "output_options_list", "$@150",
  "output_options_list_content", "output_entry", "$@151",
  "output_params_list", "output_params", "output", "$@152", "flush",
  "maxsize", "maxver", "pattern", "$@153", "compatibility", "$@154",
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
     696,   702,   708,   714,   714,   723,   726,   729,   732,   735,
     741,   741,   750,   750,   759,   768,   778,   778,   787,   790,
     793,   796,   801,   807,   813,   819,   825,   825,   834,   834,
     843,   849,   855,   861,   861,   870,   876,   876,   885,   885,
     894,   900,   906,   912,   912,   924,   924,   933,   934,   935,
     940,   941,   942,   943,   944,   945,   946,   947,   950,   950,
     961,   967,   973,   979,   985,   985,   998,   998,  1011,  1011,
    1022,  1023,  1026,  1027,  1028,  1033,  1033,  1043,  1044,  1045,
    1050,  1051,  1052,  1053,  1054,  1055,  1056,  1057,  1058,  1059,
    1060,  1061,  1062,  1063,  1064,  1065,  1066,  1067,  1068,  1069,
    1070,  1071,  1072,  1073,  1074,  1077,  1077,  1086,  1086,  1095,
    1095,  1104,  1104,  1113,  1119,  1119,  1128,  1134,  1140,  1146,
    1152,  1158,  1164,  1170,  1176,  1176,  1184,  1185,  1186,  1189,
    1195,  1201,  1207,  1207,  1216,  1216,  1225,  1225,  1234,  1234,
    1243,  1243,  1251,  1252,  1253,  1254,  1255,  1258,  1258,  1267,
    1267,  1278,  1279,  1280,  1285,  1286,  1289,  1289,  1308,  1308,
    1326,  1326,  1337,  1338,  1339,  1344,  1345,  1348,  1353,  1358,
    1358,  1369,  1370,  1371,  1376,  1377,  1378,  1381,  1386,  1393,
    1393,  1406,  1406,  1419,  1420,  1421,  1426,  1427,  1428,  1429,
    1430,  1431,  1434,  1440,  1446,  1452,  1452,  1463,  1464,  1467,
    1468,  1469,  1474,  1474,  1484,  1484,  1494,  1495,  1496,  1499,
    1502,  1503,  1506,  1506,  1515,  1515,  1524,  1524,  1536,  1537,
    1538,  1543,  1544,  1545,  1546,  1547,  1548,  1551,  1557,  1563,
    1569,  1575,  1581,  1590,  1590,  1604,  1605,  1608,  1609,  1610,
    1619,  1619,  1645,  1645,  1656,  1657,  1658,  1664,  1665,  1666,
    1667,  1668,  1669,  1670,  1671,  1672,  1673,  1674,  1675,  1676,
    1677,  1678,  1679,  1680,  1681,  1682,  1683,  1684,  1685,  1686,
    1687,  1688,  1689,  1690,  1691,  1692,  1693,  1694,  1695,  1696,
    1697,  1698,  1699,  1700,  1701,  1702,  1703,  1704,  1705,  1706,
    1707,  1708,  1709,  1710,  1711,  1712,  1713,  1714,  1717,  1717,
    1726,  1726,  1735,  1735,  1744,  1744,  1754,  1754,  1766,  1766,
    1777,  1777,  1788,  1794,  1800,  1806,  1812,  1820,  1820,  1832,
    1833,  1837,  1838,  1839,  1844,  1844,  1852,  1853,  1854,  1859,
    1860,  1861,  1862,  1863,  1864,  1865,  1866,  1867,  1868,  1869,
    1870,  1871,  1872,  1873,  1874,  1875,  1876,  1877,  1878,  1879,
    1880,  1881,  1882,  1883,  1884,  1885,  1886,  1887,  1888,  1889,
    1890,  1891,  1892,  1893,  1894,  1895,  1896,  1897,  1898,  1899,
    1900,  1901,  1902,  1903,  1904,  1905,  1906,  1913,  1913,  1927,
    1927,  1936,  1937,  1940,  1941,  1942,  1949,  1949,  1964,  1964,
    1978,  1979,  1982,  1983,  1984,  1989,  1990,  1991,  1992,  1993,
    1994,  1995,  1996,  1997,  1998,  2001,  2003,  2009,  2011,  2011,
    2020,  2020,  2029,  2029,  2038,  2040,  2040,  2049,  2059,  2059,
    2072,  2073,  2078,  2079,  2080,  2087,  2087,  2099,  2099,  2111,
    2112,  2117,  2118,  2119,  2126,  2127,  2128,  2129,  2130,  2131,
    2132,  2133,  2134,  2135,  2136,  2139,  2141,  2141,  2150,  2152,
    2154,  2160,  2166,  2172,  2172,  2186,  2186,  2199,  2200,  2203,
    2204,  2205,  2210,  2210,  2220,  2220,  2230,  2231,  2232,  2237,
    2238,  2239,  2240,  2241,  2242,  2243,  2244,  2245,  2246,  2247,
    2248,  2249,  2250,  2251,  2252,  2253,  2254,  2255,  2256,  2257,
    2258,  2259,  2260,  2263,  2263,  2272,  2278,  2278,  2303,  2303,
    2333,  2333,  2346,  2347,  2350,  2351,  2352,  2357,  2357,  2369,
    2369,  2381,  2382,  2383,  2388,  2389,  2390,  2391,  2392,  2393,
    2394,  2395,  2396,  2397,  2398,  2399,  2400,  2401,  2404,  2404,
    2413,  2419,  2419,  2428,  2434,  2443,  2443,  2454,  2455,  2458,
    2459,  2460,  2465,  2465,  2474,  2474,  2483,  2484,  2487,  2488,
    2489,  2495,  2496,  2497,  2498,  2499,  2500,  2501,  2502,  2503,
    2504,  2505,  2506,  2509,  2509,  2520,  2520,  2531,  2531,  2542,
    2542,  2551,  2551,  2560,  2560,  2569,  2569,  2578,  2578,  2592,
    2592,  2603,  2609,  2609,  2620,  2621,  2622,  2627,  2627,  2637,
    2638,  2641,  2642,  2643,  2648,  2649,  2650,  2651,  2652,  2653,
    2654,  2655,  2656,  2657,  2658,  2659,  2660,  2661,  2662,  2665,
    2667,  2667,  2676,  2676,  2686,  2692,  2701,  2701,  2714,  2715,
    2716,  2721,  2722,  2723,  2724,  2725,  2726,  2727,  2728,  2729,
    2732,  2732,  2740,  2741,  2742,  2745,  2751,  2751,  2760,  2766,
    2774,  2782,  2782,  2794,  2794,  2806,  2807,  2810,  2811,  2812,
    2817,  2817,  2825,  2826,  2827,  2832,  2833,  2834,  2835,  2836,
    2837,  2838,  2839,  2840,  2841,  2842,  2843,  2844,  2847,  2847,
    2856,  2857,  2858,  2861,  2861,  2871,  2871,  2881,  2887,  2893,
    2893,  2904,  2905,  2908,  2909,  2910,  2915,  2915,  2923,  2924,
    2925,  2930,  2931,  2932,  2933,  2934,  2937,  2937,  2948,  2948,
    2961,  2962,  2963,  2968,  2969,  2970,  2971,  2972,  2973,  2974,
    2977,  2977,  2985,  2988,  2988,  2997,  2997,  3006,  3006,  3017,
    3018,  3021,  3022,  3023,  3028,  3028,  3036,  3037,  3038,  3043,
    3044,  3045,  3046,  3047,  3048,  3049,  3052,  3052,  3061,  3061,
    3072,  3072,  3085,  3086,  3087,  3092,  3093,  3094,  3095,  3096,
    3097,  3100,  3106,  3106,  3115,  3121,  3121,  3131,  3131,  3144,
    3144,  3154,  3155,  3156,  3161,  3162,  3163,  3164,  3165,  3166,
    3167,  3168,  3169,  3170,  3171,  3174,  3180,  3180,  3189,  3195,
    3195,  3204,  3210,  3216,  3216,  3225,  3226,  3229,  3229,  3240,
    3240,  3252,  3252,  3262,  3263,  3264,  3270,  3271,  3274,  3274,
    3285,  3293,  3293,  3306,  3307,  3308,  3314,  3314,  3322,  3323,
    3324,  3329,  3330,  3331,  3332,  3333,  3334,  3335,  3338,  3344,
    3344,  3353,  3353,  3364,  3365,  3366,  3371,  3371,  3379,  3380,
    3381,  3386,  3387,  3388,  3389,  3390,  3393,  3393,  3402,  3408,
    3414,  3420,  3420,  3429,  3429,  3440,  3441,  3442,  3447,  3448,
    3451
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
#line 7194 "dhcp6_parser.cc"

#line 3457 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
