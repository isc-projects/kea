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

  case 268: // $@38: %empty
#line 1090 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1951 "dhcp6_parser.cc"
    break;

  case 269: // database_type: "type" $@38 ":" "constant string"
#line 1093 "dhcp6_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 1961 "dhcp6_parser.cc"
    break;

  case 270: // $@39: %empty
#line 1099 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1970 "dhcp6_parser.cc"
    break;

  case 271: // user: "user" $@39 ":" "constant string"
#line 1102 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1980 "dhcp6_parser.cc"
    break;

  case 272: // $@40: %empty
#line 1108 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1989 "dhcp6_parser.cc"
    break;

  case 273: // password: "password" $@40 ":" "constant string"
#line 1111 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1999 "dhcp6_parser.cc"
    break;

  case 274: // $@41: %empty
#line 1117 "dhcp6_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2008 "dhcp6_parser.cc"
    break;

  case 275: // password_file: "password-file" $@41 ":" "constant string"
#line 1120 "dhcp6_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 2018 "dhcp6_parser.cc"
    break;

  case 276: // $@42: %empty
#line 1126 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2027 "dhcp6_parser.cc"
    break;

  case 277: // host: "host" $@42 ":" "constant string"
#line 1129 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2037 "dhcp6_parser.cc"
    break;

  case 278: // port: "port" ":" "integer"
#line 1135 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2047 "dhcp6_parser.cc"
    break;

  case 279: // $@43: %empty
#line 1141 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2056 "dhcp6_parser.cc"
    break;

  case 280: // name: "name" $@43 ":" "constant string"
#line 1144 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2066 "dhcp6_parser.cc"
    break;

  case 281: // persist: "persist" ":" "boolean"
#line 1150 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2076 "dhcp6_parser.cc"
    break;

  case 282: // lfc_interval: "lfc-interval" ":" "integer"
#line 1156 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2086 "dhcp6_parser.cc"
    break;

  case 283: // readonly: "readonly" ":" "boolean"
#line 1162 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2096 "dhcp6_parser.cc"
    break;

  case 284: // connect_timeout: "connect-timeout" ":" "integer"
#line 1168 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2106 "dhcp6_parser.cc"
    break;

  case 285: // read_timeout: "read-timeout" ":" "integer"
#line 1174 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2116 "dhcp6_parser.cc"
    break;

  case 286: // write_timeout: "write-timeout" ":" "integer"
#line 1180 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2126 "dhcp6_parser.cc"
    break;

  case 287: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1186 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2136 "dhcp6_parser.cc"
    break;

  case 288: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1192 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2146 "dhcp6_parser.cc"
    break;

  case 289: // $@44: %empty
#line 1198 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2155 "dhcp6_parser.cc"
    break;

  case 290: // on_fail: "on-fail" $@44 ":" on_fail_mode
#line 1201 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2164 "dhcp6_parser.cc"
    break;

  case 291: // on_fail_mode: "stop-retry-exit"
#line 1206 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2170 "dhcp6_parser.cc"
    break;

  case 292: // on_fail_mode: "serve-retry-exit"
#line 1207 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2176 "dhcp6_parser.cc"
    break;

  case 293: // on_fail_mode: "serve-retry-continue"
#line 1208 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2182 "dhcp6_parser.cc"
    break;

  case 294: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1211 "dhcp6_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2192 "dhcp6_parser.cc"
    break;

  case 295: // max_row_errors: "max-row-errors" ":" "integer"
#line 1217 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2202 "dhcp6_parser.cc"
    break;

  case 296: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1223 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2212 "dhcp6_parser.cc"
    break;

  case 297: // $@45: %empty
#line 1229 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2221 "dhcp6_parser.cc"
    break;

  case 298: // trust_anchor: "trust-anchor" $@45 ":" "constant string"
#line 1232 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2231 "dhcp6_parser.cc"
    break;

  case 299: // $@46: %empty
#line 1238 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2240 "dhcp6_parser.cc"
    break;

  case 300: // cert_file: "cert-file" $@46 ":" "constant string"
#line 1241 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2250 "dhcp6_parser.cc"
    break;

  case 301: // $@47: %empty
#line 1247 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2259 "dhcp6_parser.cc"
    break;

  case 302: // key_file: "key-file" $@47 ":" "constant string"
#line 1250 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2269 "dhcp6_parser.cc"
    break;

  case 303: // $@48: %empty
#line 1256 "dhcp6_parser.yy"
                   {
    ctx.unique("ssl-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SSL_MODE);
}
#line 2278 "dhcp6_parser.cc"
    break;

  case 304: // ssl_mode: "ssl-mode" $@48 ":" ssl_mode
#line 1259 "dhcp6_parser.yy"
                 {
    ctx.stack_.back()->set("ssl-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2287 "dhcp6_parser.cc"
    break;

  case 305: // ssl_mode: "disable"
#line 1264 "dhcp6_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disable", ctx.loc2pos(yystack_[0].location)));
            }
#line 2295 "dhcp6_parser.cc"
    break;

  case 306: // ssl_mode: "prefer"
#line 1267 "dhcp6_parser.yy"
                 {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("prefer", ctx.loc2pos(yystack_[0].location)));
            }
#line 2303 "dhcp6_parser.cc"
    break;

  case 307: // ssl_mode: "require"
#line 1270 "dhcp6_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("require", ctx.loc2pos(yystack_[0].location)));
            }
#line 2311 "dhcp6_parser.cc"
    break;

  case 308: // ssl_mode: "verify-ca"
#line 1273 "dhcp6_parser.yy"
                    {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-ca", ctx.loc2pos(yystack_[0].location)));
            }
#line 2319 "dhcp6_parser.cc"
    break;

  case 309: // ssl_mode: "verify-full"
#line 1276 "dhcp6_parser.yy"
                      {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-full", ctx.loc2pos(yystack_[0].location)));
            }
#line 2327 "dhcp6_parser.cc"
    break;

  case 310: // $@49: %empty
#line 1281 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2336 "dhcp6_parser.cc"
    break;

  case 311: // cipher_list: "cipher-list" $@49 ":" "constant string"
#line 1284 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2346 "dhcp6_parser.cc"
    break;

  case 312: // $@50: %empty
#line 1290 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2358 "dhcp6_parser.cc"
    break;

  case 313: // sanity_checks: "sanity-checks" $@50 ":" "{" sanity_checks_params "}"
#line 1296 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2367 "dhcp6_parser.cc"
    break;

  case 316: // sanity_checks_params: sanity_checks_params ","
#line 1303 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2375 "dhcp6_parser.cc"
    break;

  case 319: // $@51: %empty
#line 1312 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2384 "dhcp6_parser.cc"
    break;

  case 320: // lease_checks: "lease-checks" $@51 ":" "constant string"
#line 1315 "dhcp6_parser.yy"
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
#line 2404 "dhcp6_parser.cc"
    break;

  case 321: // $@52: %empty
#line 1331 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2413 "dhcp6_parser.cc"
    break;

  case 322: // extended_info_checks: "extended-info-checks" $@52 ":" "constant string"
#line 1334 "dhcp6_parser.yy"
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
#line 2432 "dhcp6_parser.cc"
    break;

  case 323: // $@53: %empty
#line 1349 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2444 "dhcp6_parser.cc"
    break;

  case 324: // mac_sources: "mac-sources" $@53 ":" "[" mac_sources_list "]"
#line 1355 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2453 "dhcp6_parser.cc"
    break;

  case 327: // mac_sources_list: mac_sources_list ","
#line 1362 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2461 "dhcp6_parser.cc"
    break;

  case 330: // duid_id: "duid"
#line 1371 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2470 "dhcp6_parser.cc"
    break;

  case 331: // string_id: "constant string"
#line 1376 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2479 "dhcp6_parser.cc"
    break;

  case 332: // $@54: %empty
#line 1381 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2491 "dhcp6_parser.cc"
    break;

  case 333: // host_reservation_identifiers: "host-reservation-identifiers" $@54 ":" "[" host_reservation_identifiers_list "]"
#line 1387 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2500 "dhcp6_parser.cc"
    break;

  case 336: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1394 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2508 "dhcp6_parser.cc"
    break;

  case 340: // hw_address_id: "hw-address"
#line 1404 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2517 "dhcp6_parser.cc"
    break;

  case 341: // flex_id: "flex-id"
#line 1409 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2526 "dhcp6_parser.cc"
    break;

  case 342: // $@55: %empty
#line 1416 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2538 "dhcp6_parser.cc"
    break;

  case 343: // relay_supplied_options: "relay-supplied-options" $@55 ":" "[" list_content "]"
#line 1422 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2547 "dhcp6_parser.cc"
    break;

  case 344: // $@56: %empty
#line 1429 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2559 "dhcp6_parser.cc"
    break;

  case 345: // dhcp_multi_threading: "multi-threading" $@56 ":" "{" multi_threading_params "}"
#line 1435 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2570 "dhcp6_parser.cc"
    break;

  case 348: // multi_threading_params: multi_threading_params ","
#line 1444 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2578 "dhcp6_parser.cc"
    break;

  case 355: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1457 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2588 "dhcp6_parser.cc"
    break;

  case 356: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1463 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2598 "dhcp6_parser.cc"
    break;

  case 357: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1469 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2608 "dhcp6_parser.cc"
    break;

  case 358: // $@57: %empty
#line 1475 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2620 "dhcp6_parser.cc"
    break;

  case 359: // hooks_libraries: "hooks-libraries" $@57 ":" "[" hooks_libraries_list "]"
#line 1481 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2629 "dhcp6_parser.cc"
    break;

  case 364: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1492 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2637 "dhcp6_parser.cc"
    break;

  case 365: // $@58: %empty
#line 1497 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2647 "dhcp6_parser.cc"
    break;

  case 366: // hooks_library: "{" $@58 hooks_params "}"
#line 1501 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2657 "dhcp6_parser.cc"
    break;

  case 367: // $@59: %empty
#line 1507 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2667 "dhcp6_parser.cc"
    break;

  case 368: // sub_hooks_library: "{" $@59 hooks_params "}"
#line 1511 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2677 "dhcp6_parser.cc"
    break;

  case 371: // hooks_params: hooks_params ","
#line 1519 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2685 "dhcp6_parser.cc"
    break;

  case 375: // $@60: %empty
#line 1529 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2694 "dhcp6_parser.cc"
    break;

  case 376: // library: "library" $@60 ":" "constant string"
#line 1532 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2704 "dhcp6_parser.cc"
    break;

  case 377: // $@61: %empty
#line 1538 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2713 "dhcp6_parser.cc"
    break;

  case 378: // parameters: "parameters" $@61 ":" map_value
#line 1541 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2722 "dhcp6_parser.cc"
    break;

  case 379: // $@62: %empty
#line 1547 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2734 "dhcp6_parser.cc"
    break;

  case 380: // expired_leases_processing: "expired-leases-processing" $@62 ":" "{" expired_leases_params "}"
#line 1553 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2744 "dhcp6_parser.cc"
    break;

  case 383: // expired_leases_params: expired_leases_params ","
#line 1561 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2752 "dhcp6_parser.cc"
    break;

  case 390: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1574 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2762 "dhcp6_parser.cc"
    break;

  case 391: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1580 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2772 "dhcp6_parser.cc"
    break;

  case 392: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1586 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2782 "dhcp6_parser.cc"
    break;

  case 393: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1592 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2792 "dhcp6_parser.cc"
    break;

  case 394: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1598 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2802 "dhcp6_parser.cc"
    break;

  case 395: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1604 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2812 "dhcp6_parser.cc"
    break;

  case 396: // $@63: %empty
#line 1613 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2824 "dhcp6_parser.cc"
    break;

  case 397: // subnet6_list: "subnet6" $@63 ":" "[" subnet6_list_content "]"
#line 1619 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2833 "dhcp6_parser.cc"
    break;

  case 402: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1633 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2841 "dhcp6_parser.cc"
    break;

  case 403: // $@64: %empty
#line 1642 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2851 "dhcp6_parser.cc"
    break;

  case 404: // subnet6: "{" $@64 subnet6_params "}"
#line 1646 "dhcp6_parser.yy"
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
#line 2877 "dhcp6_parser.cc"
    break;

  case 405: // $@65: %empty
#line 1668 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2887 "dhcp6_parser.cc"
    break;

  case 406: // sub_subnet6: "{" $@65 subnet6_params "}"
#line 1672 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2897 "dhcp6_parser.cc"
    break;

  case 409: // subnet6_params: subnet6_params ","
#line 1681 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2905 "dhcp6_parser.cc"
    break;

  case 462: // $@66: %empty
#line 1741 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2914 "dhcp6_parser.cc"
    break;

  case 463: // subnet: "subnet" $@66 ":" "constant string"
#line 1744 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2924 "dhcp6_parser.cc"
    break;

  case 464: // $@67: %empty
#line 1750 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2933 "dhcp6_parser.cc"
    break;

  case 465: // interface: "interface" $@67 ":" "constant string"
#line 1753 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2943 "dhcp6_parser.cc"
    break;

  case 466: // $@68: %empty
#line 1759 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2952 "dhcp6_parser.cc"
    break;

  case 467: // interface_id: "interface-id" $@68 ":" "constant string"
#line 1762 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2962 "dhcp6_parser.cc"
    break;

  case 468: // $@69: %empty
#line 1768 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2971 "dhcp6_parser.cc"
    break;

  case 469: // client_class: "client-class" $@69 ":" "constant string"
#line 1771 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2981 "dhcp6_parser.cc"
    break;

  case 470: // $@70: %empty
#line 1778 "dhcp6_parser.yy"
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
#line 1784 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3002 "dhcp6_parser.cc"
    break;

  case 472: // $@71: %empty
#line 1790 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3014 "dhcp6_parser.cc"
    break;

  case 473: // require_client_classes: "require-client-classes" $@71 ":" list_strings
#line 1796 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3023 "dhcp6_parser.cc"
    break;

  case 474: // $@72: %empty
#line 1801 "dhcp6_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3035 "dhcp6_parser.cc"
    break;

  case 475: // evaluate_additional_classes: "evaluate-additional-classes" $@72 ":" list_strings
#line 1807 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3044 "dhcp6_parser.cc"
    break;

  case 476: // reservations_global: "reservations-global" ":" "boolean"
#line 1812 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 3054 "dhcp6_parser.cc"
    break;

  case 477: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1818 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 3064 "dhcp6_parser.cc"
    break;

  case 478: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1824 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 3074 "dhcp6_parser.cc"
    break;

  case 479: // id: "id" ":" "integer"
#line 1830 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 3084 "dhcp6_parser.cc"
    break;

  case 480: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1836 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 3094 "dhcp6_parser.cc"
    break;

  case 481: // $@73: %empty
#line 1844 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3106 "dhcp6_parser.cc"
    break;

  case 482: // shared_networks: "shared-networks" $@73 ":" "[" shared_networks_content "]"
#line 1850 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3115 "dhcp6_parser.cc"
    break;

  case 487: // shared_networks_list: shared_networks_list ","
#line 1863 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3123 "dhcp6_parser.cc"
    break;

  case 488: // $@74: %empty
#line 1868 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3133 "dhcp6_parser.cc"
    break;

  case 489: // shared_network: "{" $@74 shared_network_params "}"
#line 1872 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3141 "dhcp6_parser.cc"
    break;

  case 492: // shared_network_params: shared_network_params ","
#line 1878 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3149 "dhcp6_parser.cc"
    break;

  case 542: // $@75: %empty
#line 1938 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3161 "dhcp6_parser.cc"
    break;

  case 543: // option_def_list: "option-def" $@75 ":" "[" option_def_list_content "]"
#line 1944 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3170 "dhcp6_parser.cc"
    break;

  case 544: // $@76: %empty
#line 1952 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3179 "dhcp6_parser.cc"
    break;

  case 545: // sub_option_def_list: "{" $@76 option_def_list "}"
#line 1955 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 3187 "dhcp6_parser.cc"
    break;

  case 550: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1967 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3195 "dhcp6_parser.cc"
    break;

  case 551: // $@77: %empty
#line 1974 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3205 "dhcp6_parser.cc"
    break;

  case 552: // option_def_entry: "{" $@77 option_def_params "}"
#line 1978 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3217 "dhcp6_parser.cc"
    break;

  case 553: // $@78: %empty
#line 1989 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3227 "dhcp6_parser.cc"
    break;

  case 554: // sub_option_def: "{" $@78 option_def_params "}"
#line 1993 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3239 "dhcp6_parser.cc"
    break;

  case 559: // not_empty_option_def_params: not_empty_option_def_params ","
#line 2009 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3247 "dhcp6_parser.cc"
    break;

  case 571: // code: "code" ":" "integer"
#line 2028 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3257 "dhcp6_parser.cc"
    break;

  case 573: // $@79: %empty
#line 2036 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3266 "dhcp6_parser.cc"
    break;

  case 574: // option_def_type: "type" $@79 ":" "constant string"
#line 2039 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3276 "dhcp6_parser.cc"
    break;

  case 575: // $@80: %empty
#line 2045 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3285 "dhcp6_parser.cc"
    break;

  case 576: // option_def_record_types: "record-types" $@80 ":" "constant string"
#line 2048 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3295 "dhcp6_parser.cc"
    break;

  case 577: // $@81: %empty
#line 2054 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3304 "dhcp6_parser.cc"
    break;

  case 578: // space: "space" $@81 ":" "constant string"
#line 2057 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3314 "dhcp6_parser.cc"
    break;

  case 580: // $@82: %empty
#line 2065 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3323 "dhcp6_parser.cc"
    break;

  case 581: // option_def_encapsulate: "encapsulate" $@82 ":" "constant string"
#line 2068 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3333 "dhcp6_parser.cc"
    break;

  case 582: // option_def_array: "array" ":" "boolean"
#line 2074 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3343 "dhcp6_parser.cc"
    break;

  case 583: // $@83: %empty
#line 2084 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3355 "dhcp6_parser.cc"
    break;

  case 584: // option_data_list: "option-data" $@83 ":" "[" option_data_list_content "]"
#line 2090 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3364 "dhcp6_parser.cc"
    break;

  case 589: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2105 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3372 "dhcp6_parser.cc"
    break;

  case 590: // $@84: %empty
#line 2112 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3382 "dhcp6_parser.cc"
    break;

  case 591: // option_data_entry: "{" $@84 option_data_params "}"
#line 2116 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3391 "dhcp6_parser.cc"
    break;

  case 592: // $@85: %empty
#line 2124 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3401 "dhcp6_parser.cc"
    break;

  case 593: // sub_option_data: "{" $@85 option_data_params "}"
#line 2128 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3410 "dhcp6_parser.cc"
    break;

  case 598: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2144 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3418 "dhcp6_parser.cc"
    break;

  case 611: // $@86: %empty
#line 2166 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3427 "dhcp6_parser.cc"
    break;

  case 612: // option_data_data: "data" $@86 ":" "constant string"
#line 2169 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3437 "dhcp6_parser.cc"
    break;

  case 615: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2179 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3447 "dhcp6_parser.cc"
    break;

  case 616: // option_data_always_send: "always-send" ":" "boolean"
#line 2185 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3457 "dhcp6_parser.cc"
    break;

  case 617: // option_data_never_send: "never-send" ":" "boolean"
#line 2191 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3467 "dhcp6_parser.cc"
    break;

  case 618: // $@87: %empty
#line 2197 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3479 "dhcp6_parser.cc"
    break;

  case 619: // option_data_client_classes: "client-classes" $@87 ":" list_strings
#line 2203 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3488 "dhcp6_parser.cc"
    break;

  case 620: // $@88: %empty
#line 2211 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3500 "dhcp6_parser.cc"
    break;

  case 621: // pools_list: "pools" $@88 ":" "[" pools_list_content "]"
#line 2217 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3509 "dhcp6_parser.cc"
    break;

  case 626: // not_empty_pools_list: not_empty_pools_list ","
#line 2230 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3517 "dhcp6_parser.cc"
    break;

  case 627: // $@89: %empty
#line 2235 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3527 "dhcp6_parser.cc"
    break;

  case 628: // pool_list_entry: "{" $@89 pool_params "}"
#line 2239 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3537 "dhcp6_parser.cc"
    break;

  case 629: // $@90: %empty
#line 2245 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3547 "dhcp6_parser.cc"
    break;

  case 630: // sub_pool6: "{" $@90 pool_params "}"
#line 2249 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3557 "dhcp6_parser.cc"
    break;

  case 633: // pool_params: pool_params ","
#line 2257 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3565 "dhcp6_parser.cc"
    break;

  case 658: // $@91: %empty
#line 2288 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3574 "dhcp6_parser.cc"
    break;

  case 659: // pool_entry: "pool" $@91 ":" "constant string"
#line 2291 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3584 "dhcp6_parser.cc"
    break;

  case 660: // pool_id: "pool-id" ":" "integer"
#line 2297 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3594 "dhcp6_parser.cc"
    break;

  case 661: // $@92: %empty
#line 2303 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3602 "dhcp6_parser.cc"
    break;

  case 662: // user_context: "user-context" $@92 ":" map_value
#line 2305 "dhcp6_parser.yy"
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
#line 3629 "dhcp6_parser.cc"
    break;

  case 663: // $@93: %empty
#line 2328 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3637 "dhcp6_parser.cc"
    break;

  case 664: // comment: "comment" $@93 ":" "constant string"
#line 2330 "dhcp6_parser.yy"
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
#line 3666 "dhcp6_parser.cc"
    break;

  case 665: // $@94: %empty
#line 2358 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3678 "dhcp6_parser.cc"
    break;

  case 666: // pd_pools_list: "pd-pools" $@94 ":" "[" pd_pools_list_content "]"
#line 2364 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3687 "dhcp6_parser.cc"
    break;

  case 671: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2377 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3695 "dhcp6_parser.cc"
    break;

  case 672: // $@95: %empty
#line 2382 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3705 "dhcp6_parser.cc"
    break;

  case 673: // pd_pool_entry: "{" $@95 pd_pool_params "}"
#line 2386 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3717 "dhcp6_parser.cc"
    break;

  case 674: // $@96: %empty
#line 2394 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3727 "dhcp6_parser.cc"
    break;

  case 675: // sub_pd_pool: "{" $@96 pd_pool_params "}"
#line 2398 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3739 "dhcp6_parser.cc"
    break;

  case 678: // pd_pool_params: pd_pool_params ","
#line 2408 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3747 "dhcp6_parser.cc"
    break;

  case 693: // $@97: %empty
#line 2429 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3756 "dhcp6_parser.cc"
    break;

  case 694: // pd_prefix: "prefix" $@97 ":" "constant string"
#line 2432 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3766 "dhcp6_parser.cc"
    break;

  case 695: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2438 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3776 "dhcp6_parser.cc"
    break;

  case 696: // $@98: %empty
#line 2444 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3785 "dhcp6_parser.cc"
    break;

  case 697: // excluded_prefix: "excluded-prefix" $@98 ":" "constant string"
#line 2447 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3795 "dhcp6_parser.cc"
    break;

  case 698: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2453 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3805 "dhcp6_parser.cc"
    break;

  case 699: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2459 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3815 "dhcp6_parser.cc"
    break;

  case 700: // $@99: %empty
#line 2468 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3827 "dhcp6_parser.cc"
    break;

  case 701: // reservations: "reservations" $@99 ":" "[" reservations_list "]"
#line 2474 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3836 "dhcp6_parser.cc"
    break;

  case 706: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2485 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3844 "dhcp6_parser.cc"
    break;

  case 707: // $@100: %empty
#line 2490 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3854 "dhcp6_parser.cc"
    break;

  case 708: // reservation: "{" $@100 reservation_params "}"
#line 2494 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3863 "dhcp6_parser.cc"
    break;

  case 709: // $@101: %empty
#line 2499 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3873 "dhcp6_parser.cc"
    break;

  case 710: // sub_reservation: "{" $@101 reservation_params "}"
#line 2503 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3882 "dhcp6_parser.cc"
    break;

  case 715: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2514 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3890 "dhcp6_parser.cc"
    break;

  case 728: // $@102: %empty
#line 2534 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3902 "dhcp6_parser.cc"
    break;

  case 729: // ip_addresses: "ip-addresses" $@102 ":" list_strings
#line 2540 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3911 "dhcp6_parser.cc"
    break;

  case 730: // $@103: %empty
#line 2545 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3923 "dhcp6_parser.cc"
    break;

  case 731: // prefixes: "prefixes" $@103 ":" list_strings
#line 2551 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3932 "dhcp6_parser.cc"
    break;

  case 732: // $@104: %empty
#line 2556 "dhcp6_parser.yy"
                                     {
    ctx.unique("excluded-prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3944 "dhcp6_parser.cc"
    break;

  case 733: // excluded_prefixes: "excluded-prefixes" $@104 ":" list_strings
#line 2562 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3953 "dhcp6_parser.cc"
    break;

  case 734: // $@105: %empty
#line 2567 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3962 "dhcp6_parser.cc"
    break;

  case 735: // duid: "duid" $@105 ":" "constant string"
#line 2570 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3972 "dhcp6_parser.cc"
    break;

  case 736: // $@106: %empty
#line 2576 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3981 "dhcp6_parser.cc"
    break;

  case 737: // hw_address: "hw-address" $@106 ":" "constant string"
#line 2579 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3991 "dhcp6_parser.cc"
    break;

  case 738: // $@107: %empty
#line 2585 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4000 "dhcp6_parser.cc"
    break;

  case 739: // hostname: "hostname" $@107 ":" "constant string"
#line 2588 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 4010 "dhcp6_parser.cc"
    break;

  case 740: // $@108: %empty
#line 2594 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4019 "dhcp6_parser.cc"
    break;

  case 741: // flex_id_value: "flex-id" $@108 ":" "constant string"
#line 2597 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 4029 "dhcp6_parser.cc"
    break;

  case 742: // $@109: %empty
#line 2603 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4041 "dhcp6_parser.cc"
    break;

  case 743: // reservation_client_classes: "client-classes" $@109 ":" list_strings
#line 2609 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4050 "dhcp6_parser.cc"
    break;

  case 744: // $@110: %empty
#line 2617 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 4062 "dhcp6_parser.cc"
    break;

  case 745: // relay: "relay" $@110 ":" "{" relay_map "}"
#line 2623 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4071 "dhcp6_parser.cc"
    break;

  case 747: // $@111: %empty
#line 2634 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 4083 "dhcp6_parser.cc"
    break;

  case 748: // client_classes: "client-classes" $@111 ":" "[" client_classes_list "]"
#line 2640 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4092 "dhcp6_parser.cc"
    break;

  case 753: // not_empty_classes_list: not_empty_classes_list ","
#line 2651 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4100 "dhcp6_parser.cc"
    break;

  case 754: // $@112: %empty
#line 2656 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4110 "dhcp6_parser.cc"
    break;

  case 755: // client_class_entry: "{" $@112 client_class_params "}"
#line 2660 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 4120 "dhcp6_parser.cc"
    break;

  case 760: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2672 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 4128 "dhcp6_parser.cc"
    break;

  case 777: // $@113: %empty
#line 2696 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4137 "dhcp6_parser.cc"
    break;

  case 778: // client_class_test: "test" $@113 ":" "constant string"
#line 2699 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4147 "dhcp6_parser.cc"
    break;

  case 779: // $@114: %empty
#line 2705 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4156 "dhcp6_parser.cc"
    break;

  case 780: // client_class_template_test: "template-test" $@114 ":" "constant string"
#line 2708 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4166 "dhcp6_parser.cc"
    break;

  case 781: // only_if_required: "only-if-required" ":" "boolean"
#line 2715 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4176 "dhcp6_parser.cc"
    break;

  case 782: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2721 "dhcp6_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4186 "dhcp6_parser.cc"
    break;

  case 783: // $@115: %empty
#line 2730 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 4198 "dhcp6_parser.cc"
    break;

  case 784: // server_id: "server-id" $@115 ":" "{" server_id_params "}"
#line 2736 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4209 "dhcp6_parser.cc"
    break;

  case 787: // server_id_params: server_id_params ","
#line 2745 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4217 "dhcp6_parser.cc"
    break;

  case 797: // $@116: %empty
#line 2761 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 4226 "dhcp6_parser.cc"
    break;

  case 798: // server_id_type: "type" $@116 ":" duid_type
#line 2764 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4235 "dhcp6_parser.cc"
    break;

  case 799: // duid_type: "LLT"
#line 2769 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4241 "dhcp6_parser.cc"
    break;

  case 800: // duid_type: "EN"
#line 2770 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4247 "dhcp6_parser.cc"
    break;

  case 801: // duid_type: "LL"
#line 2771 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4253 "dhcp6_parser.cc"
    break;

  case 802: // htype: "htype" ":" "integer"
#line 2774 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4263 "dhcp6_parser.cc"
    break;

  case 803: // $@117: %empty
#line 2780 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4272 "dhcp6_parser.cc"
    break;

  case 804: // identifier: "identifier" $@117 ":" "constant string"
#line 2783 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4282 "dhcp6_parser.cc"
    break;

  case 805: // time: "time" ":" "integer"
#line 2789 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4292 "dhcp6_parser.cc"
    break;

  case 806: // enterprise_id: "enterprise-id" ":" "integer"
#line 2795 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4302 "dhcp6_parser.cc"
    break;

  case 807: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2803 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4312 "dhcp6_parser.cc"
    break;

  case 808: // $@118: %empty
#line 2811 "dhcp6_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKETS);
}
#line 4324 "dhcp6_parser.cc"
    break;

  case 809: // control_sockets: "control-sockets" $@118 ":" "[" control_socket_list "]"
#line 2817 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4333 "dhcp6_parser.cc"
    break;

  case 814: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2828 "dhcp6_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4341 "dhcp6_parser.cc"
    break;

  case 815: // $@119: %empty
#line 2833 "dhcp6_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4351 "dhcp6_parser.cc"
    break;

  case 816: // control_socket_entry: "{" $@119 control_socket_params "}"
#line 2837 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4359 "dhcp6_parser.cc"
    break;

  case 819: // control_socket_params: control_socket_params ","
#line 2843 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4367 "dhcp6_parser.cc"
    break;

  case 833: // $@120: %empty
#line 2863 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4376 "dhcp6_parser.cc"
    break;

  case 834: // control_socket_type: "socket-type" $@120 ":" control_socket_type_value
#line 2866 "dhcp6_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4385 "dhcp6_parser.cc"
    break;

  case 835: // control_socket_type_value: "unix"
#line 2872 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4391 "dhcp6_parser.cc"
    break;

  case 836: // control_socket_type_value: "http"
#line 2873 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4397 "dhcp6_parser.cc"
    break;

  case 837: // control_socket_type_value: "https"
#line 2874 "dhcp6_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4403 "dhcp6_parser.cc"
    break;

  case 838: // $@121: %empty
#line 2877 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4412 "dhcp6_parser.cc"
    break;

  case 839: // control_socket_name: "socket-name" $@121 ":" "constant string"
#line 2880 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4422 "dhcp6_parser.cc"
    break;

  case 840: // $@122: %empty
#line 2886 "dhcp6_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4431 "dhcp6_parser.cc"
    break;

  case 841: // control_socket_address: "socket-address" $@122 ":" "constant string"
#line 2889 "dhcp6_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4441 "dhcp6_parser.cc"
    break;

  case 842: // control_socket_port: "socket-port" ":" "integer"
#line 2895 "dhcp6_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4451 "dhcp6_parser.cc"
    break;

  case 843: // cert_required: "cert-required" ":" "boolean"
#line 2901 "dhcp6_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4461 "dhcp6_parser.cc"
    break;

  case 844: // $@123: %empty
#line 2907 "dhcp6_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4473 "dhcp6_parser.cc"
    break;

  case 845: // http_headers: "http-headers" $@123 ":" "[" http_header_list "]"
#line 2913 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4482 "dhcp6_parser.cc"
    break;

  case 850: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2924 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4490 "dhcp6_parser.cc"
    break;

  case 851: // $@124: %empty
#line 2929 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4500 "dhcp6_parser.cc"
    break;

  case 852: // http_header: "{" $@124 http_header_params "}"
#line 2933 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4508 "dhcp6_parser.cc"
    break;

  case 855: // http_header_params: http_header_params ","
#line 2939 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4516 "dhcp6_parser.cc"
    break;

  case 861: // $@125: %empty
#line 2951 "dhcp6_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4525 "dhcp6_parser.cc"
    break;

  case 862: // header_value: "value" $@125 ":" "constant string"
#line 2954 "dhcp6_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4535 "dhcp6_parser.cc"
    break;

  case 863: // $@126: %empty
#line 2962 "dhcp6_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4547 "dhcp6_parser.cc"
    break;

  case 864: // authentication: "authentication" $@126 ":" "{" auth_params "}"
#line 2968 "dhcp6_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4558 "dhcp6_parser.cc"
    break;

  case 867: // auth_params: auth_params ","
#line 2977 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4566 "dhcp6_parser.cc"
    break;

  case 875: // $@127: %empty
#line 2991 "dhcp6_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4575 "dhcp6_parser.cc"
    break;

  case 876: // auth_type: "type" $@127 ":" auth_type_value
#line 2994 "dhcp6_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4584 "dhcp6_parser.cc"
    break;

  case 877: // auth_type_value: "basic"
#line 2999 "dhcp6_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4590 "dhcp6_parser.cc"
    break;

  case 878: // $@128: %empty
#line 3002 "dhcp6_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4599 "dhcp6_parser.cc"
    break;

  case 879: // realm: "realm" $@128 ":" "constant string"
#line 3005 "dhcp6_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4609 "dhcp6_parser.cc"
    break;

  case 880: // $@129: %empty
#line 3011 "dhcp6_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4618 "dhcp6_parser.cc"
    break;

  case 881: // directory: "directory" $@129 ":" "constant string"
#line 3014 "dhcp6_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4628 "dhcp6_parser.cc"
    break;

  case 882: // $@130: %empty
#line 3020 "dhcp6_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4640 "dhcp6_parser.cc"
    break;

  case 883: // clients: "clients" $@130 ":" "[" clients_list "]"
#line 3026 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4649 "dhcp6_parser.cc"
    break;

  case 888: // not_empty_clients_list: not_empty_clients_list ","
#line 3037 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4657 "dhcp6_parser.cc"
    break;

  case 889: // $@131: %empty
#line 3042 "dhcp6_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4667 "dhcp6_parser.cc"
    break;

  case 890: // basic_auth: "{" $@131 clients_params "}"
#line 3046 "dhcp6_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4675 "dhcp6_parser.cc"
    break;

  case 893: // clients_params: clients_params ","
#line 3052 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4683 "dhcp6_parser.cc"
    break;

  case 901: // $@132: %empty
#line 3066 "dhcp6_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4692 "dhcp6_parser.cc"
    break;

  case 902: // user_file: "user-file" $@132 ":" "constant string"
#line 3069 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4702 "dhcp6_parser.cc"
    break;

  case 903: // $@133: %empty
#line 3077 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4714 "dhcp6_parser.cc"
    break;

  case 904: // dhcp_queue_control: "dhcp-queue-control" $@133 ":" "{" queue_control_params "}"
#line 3083 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4725 "dhcp6_parser.cc"
    break;

  case 907: // queue_control_params: queue_control_params ","
#line 3092 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4733 "dhcp6_parser.cc"
    break;

  case 914: // enable_queue: "enable-queue" ":" "boolean"
#line 3105 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4743 "dhcp6_parser.cc"
    break;

  case 915: // $@134: %empty
#line 3111 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4752 "dhcp6_parser.cc"
    break;

  case 916: // queue_type: "queue-type" $@134 ":" "constant string"
#line 3114 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4762 "dhcp6_parser.cc"
    break;

  case 917: // capacity: "capacity" ":" "integer"
#line 3120 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4772 "dhcp6_parser.cc"
    break;

  case 918: // $@135: %empty
#line 3126 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4781 "dhcp6_parser.cc"
    break;

  case 919: // arbitrary_map_entry: "constant string" $@135 ":" value
#line 3129 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4790 "dhcp6_parser.cc"
    break;

  case 920: // $@136: %empty
#line 3136 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4802 "dhcp6_parser.cc"
    break;

  case 921: // dhcp_ddns: "dhcp-ddns" $@136 ":" "{" dhcp_ddns_params "}"
#line 3142 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4813 "dhcp6_parser.cc"
    break;

  case 922: // $@137: %empty
#line 3149 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4823 "dhcp6_parser.cc"
    break;

  case 923: // sub_dhcp_ddns: "{" $@137 dhcp_ddns_params "}"
#line 3153 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4833 "dhcp6_parser.cc"
    break;

  case 926: // dhcp_ddns_params: dhcp_ddns_params ","
#line 3161 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4841 "dhcp6_parser.cc"
    break;

  case 938: // enable_updates: "enable-updates" ":" "boolean"
#line 3179 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4851 "dhcp6_parser.cc"
    break;

  case 939: // $@138: %empty
#line 3185 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4860 "dhcp6_parser.cc"
    break;

  case 940: // server_ip: "server-ip" $@138 ":" "constant string"
#line 3188 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4870 "dhcp6_parser.cc"
    break;

  case 941: // server_port: "server-port" ":" "integer"
#line 3194 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4880 "dhcp6_parser.cc"
    break;

  case 942: // $@139: %empty
#line 3200 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4889 "dhcp6_parser.cc"
    break;

  case 943: // sender_ip: "sender-ip" $@139 ":" "constant string"
#line 3203 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4899 "dhcp6_parser.cc"
    break;

  case 944: // sender_port: "sender-port" ":" "integer"
#line 3209 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4909 "dhcp6_parser.cc"
    break;

  case 945: // max_queue_size: "max-queue-size" ":" "integer"
#line 3215 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4919 "dhcp6_parser.cc"
    break;

  case 946: // $@140: %empty
#line 3221 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4928 "dhcp6_parser.cc"
    break;

  case 947: // ncr_protocol: "ncr-protocol" $@140 ":" ncr_protocol_value
#line 3224 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4937 "dhcp6_parser.cc"
    break;

  case 948: // ncr_protocol_value: "UDP"
#line 3230 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4943 "dhcp6_parser.cc"
    break;

  case 949: // ncr_protocol_value: "TCP"
#line 3231 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4949 "dhcp6_parser.cc"
    break;

  case 950: // $@141: %empty
#line 3234 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4958 "dhcp6_parser.cc"
    break;

  case 951: // ncr_format: "ncr-format" $@141 ":" "JSON"
#line 3237 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4968 "dhcp6_parser.cc"
    break;

  case 952: // $@142: %empty
#line 3245 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4980 "dhcp6_parser.cc"
    break;

  case 953: // config_control: "config-control" $@142 ":" "{" config_control_params "}"
#line 3251 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4990 "dhcp6_parser.cc"
    break;

  case 954: // $@143: %empty
#line 3257 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 5000 "dhcp6_parser.cc"
    break;

  case 955: // sub_config_control: "{" $@143 config_control_params "}"
#line 3261 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 5009 "dhcp6_parser.cc"
    break;

  case 958: // config_control_params: config_control_params ","
#line 3269 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 5017 "dhcp6_parser.cc"
    break;

  case 961: // $@144: %empty
#line 3279 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 5029 "dhcp6_parser.cc"
    break;

  case 962: // config_databases: "config-databases" $@144 ":" "[" database_list "]"
#line 3285 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5038 "dhcp6_parser.cc"
    break;

  case 963: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3290 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 5048 "dhcp6_parser.cc"
    break;

  case 964: // $@145: %empty
#line 3298 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 5060 "dhcp6_parser.cc"
    break;

  case 965: // loggers: "loggers" $@145 ":" "[" loggers_entries "]"
#line 3304 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5069 "dhcp6_parser.cc"
    break;

  case 968: // loggers_entries: loggers_entries ","
#line 3313 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 5077 "dhcp6_parser.cc"
    break;

  case 969: // $@146: %empty
#line 3319 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 5087 "dhcp6_parser.cc"
    break;

  case 970: // logger_entry: "{" $@146 logger_params "}"
#line 3323 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 5095 "dhcp6_parser.cc"
    break;

  case 973: // logger_params: logger_params ","
#line 3329 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 5103 "dhcp6_parser.cc"
    break;

  case 981: // debuglevel: "debuglevel" ":" "integer"
#line 3343 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 5113 "dhcp6_parser.cc"
    break;

  case 982: // $@147: %empty
#line 3349 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5122 "dhcp6_parser.cc"
    break;

  case 983: // severity: "severity" $@147 ":" "constant string"
#line 3352 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 5132 "dhcp6_parser.cc"
    break;

  case 984: // $@148: %empty
#line 3358 "dhcp6_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 5144 "dhcp6_parser.cc"
    break;

  case 985: // output_options_list: "output-options" $@148 ":" "[" output_options_list_content "]"
#line 3364 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5153 "dhcp6_parser.cc"
    break;

  case 988: // output_options_list_content: output_options_list_content ","
#line 3371 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 5161 "dhcp6_parser.cc"
    break;

  case 989: // $@149: %empty
#line 3376 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 5171 "dhcp6_parser.cc"
    break;

  case 990: // output_entry: "{" $@149 output_params_list "}"
#line 3380 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 5179 "dhcp6_parser.cc"
    break;

  case 993: // output_params_list: output_params_list ","
#line 3386 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 5187 "dhcp6_parser.cc"
    break;

  case 999: // $@150: %empty
#line 3398 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5196 "dhcp6_parser.cc"
    break;

  case 1000: // output: "output" $@150 ":" "constant string"
#line 3401 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5206 "dhcp6_parser.cc"
    break;

  case 1001: // flush: "flush" ":" "boolean"
#line 3407 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5216 "dhcp6_parser.cc"
    break;

  case 1002: // maxsize: "maxsize" ":" "integer"
#line 3413 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5226 "dhcp6_parser.cc"
    break;

  case 1003: // maxver: "maxver" ":" "integer"
#line 3419 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5236 "dhcp6_parser.cc"
    break;

  case 1004: // $@151: %empty
#line 3425 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5245 "dhcp6_parser.cc"
    break;

  case 1005: // pattern: "pattern" $@151 ":" "constant string"
#line 3428 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5255 "dhcp6_parser.cc"
    break;

  case 1006: // $@152: %empty
#line 3434 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5267 "dhcp6_parser.cc"
    break;

  case 1007: // compatibility: "compatibility" $@152 ":" "{" compatibility_params "}"
#line 3440 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5276 "dhcp6_parser.cc"
    break;

  case 1010: // compatibility_params: compatibility_params ","
#line 3447 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5284 "dhcp6_parser.cc"
    break;

  case 1013: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3456 "dhcp6_parser.yy"
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


  const short Dhcp6Parser::yypact_ninf_ = -1471;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     663, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471,   127,    35,    57,   147,   166,
     184,   190,   191,   193,   200,   220,   247,   260,   264,   309,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,    35,  -125,
     134,   284,    90,   735,  1188,   306,   631,    98,   153,   648,
    -104,   716,    37, -1471,   181,   298,   308,   314,   311, -1471,
      82, -1471, -1471, -1471, -1471, -1471, -1471, -1471,   332,   369,
     385,   391,   394,   397,   398,   401,   409,   410,   428,   437,
     438,   446,   449, -1471,   451,   453,   458,   459,   462, -1471,
   -1471, -1471,   463,   469,   478,   480,   485,   497,   498, -1471,
   -1471, -1471,   499, -1471, -1471, -1471, -1471, -1471, -1471,   501,
     503,   514, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471,   515, -1471, -1471, -1471, -1471, -1471, -1471,   517,   519,
     524,   526, -1471, -1471,   528, -1471,    96, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471,   529,   531,   535,   537, -1471,   110, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
     538,   540, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
     163, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471,   541, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471,   164, -1471, -1471, -1471, -1471, -1471, -1471,
     542, -1471,   544,   546, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471,   171, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471,   321,   374, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471,   380, -1471, -1471,   548, -1471, -1471, -1471,
     549, -1471, -1471,   547,   555, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,   557,   558,
     561, -1471, -1471, -1471, -1471, -1471,   560,   567, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471,   177, -1471, -1471, -1471,   568, -1471,   570, -1471,
     571,   572, -1471, -1471, -1471, -1471, -1471,   180, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,   574,   187,
   -1471, -1471, -1471, -1471,    35,    35, -1471,   -47,   577, -1471,
   -1471,   581,   582,   584,   586,   587,   588,   351,   353,   354,
     356,   357,   358,   361,   362,   363,   328,   366,   367,   370,
     368,   376,   610,   379,   381,   382,   388,   389,   620,   621,
     624,   392,   395,   386,   396,   400,   403,   402,   636,   651,
     652,   415,   656,   658,   662,   664,   665,   666,   408,   427,
     429,   670,   671,   672,   675,   677,   678,   681,   682,   683,
     447,   686,   688,   689,   692,   693,   695,   456,   460,   461,
     464,   698,   699, -1471,   284, -1471,   706,   467,   468,   471,
     473,    90, -1471,   712,   713,   715,   717,   718,   487,   476,
     726,   727,   729,   730,   731,   735, -1471,   739,   507,  1188,
   -1471,   746,   509,   749,   512,   513,   306, -1471,   754,   755,
     756,   757,   761,   765,   776,   777, -1471,   631, -1471,   778,
     779,   545,   782,   816,   817,   585, -1471,   153,   821,   589,
     593,   594,   824, -1471,   648,   826,   835,   -20, -1471,   596,
     837,   601,   841,   604,   605,   844,   845,   716, -1471,   865,
     628,    37, -1471, -1471, -1471,   867,   869,   633,   870,   871,
     872,   873,   876, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,   641, -1471,
   -1471, -1471, -1471, -1471,    56,   643,   644, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471,   881,   882,   883, -1471,   667,   668,
     344,   899,   898,   679, -1471, -1471, -1471,   901,   902,   914,
     915,   916,   918,   919,   920,   921, -1471,   922,   925,   924,
     926,   684,   685, -1471, -1471, -1471, -1471,   927,   928, -1471,
     929, -1471, -1471, -1471, -1471, -1471,   931,   932,   697,   700,
     701, -1471, -1471,   929,   929,   929,   702,   933, -1471,   703,
   -1471, -1471,   707, -1471,   708, -1471, -1471, -1471,   929,   929,
     929,   929,   709,   710,   711,   714, -1471,   719,   720, -1471,
     721,   722,   723, -1471, -1471,   724, -1471, -1471, -1471,   929,
   -1471,   725,   898, -1471, -1471,   728, -1471,   732, -1471, -1471,
     -53,   734, -1471,   942, -1471, -1471,    35,   284, -1471,    37,
      90,   186,   186,   946, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471,   947,   949,   951, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471,   952, -1471, -1471, -1471,  -101,    35,   -42,
      34,   960,   961,   963,   129,    93,   -37,   964,   288,   716,
   -1471, -1471,   965,  -170, -1471, -1471,   967,   968, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471,   836, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471,   946, -1471,   237,   239,   243, -1471, -1471, -1471,
   -1471,   974,   975,   976,   977,   978,   979,   980,   981,   982,
     983, -1471,   984,   985, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471,   252, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471,   258, -1471,   986,   987, -1471, -1471,   988,   990,
   -1471, -1471,   989,   993, -1471, -1471,   991,   995, -1471, -1471,
     994,   996, -1471, -1471, -1471,    54, -1471, -1471, -1471,   997,
   -1471, -1471, -1471,    71, -1471, -1471, -1471, -1471, -1471,   272,
   -1471, -1471, -1471, -1471,   998,   999, -1471, -1471,  1000,  1002,
   -1471, -1471,  1001,  1005, -1471,  1006,  1007,  1008,  1009,  1011,
    1012,   294, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471,  1014,  1015,  1017, -1471, -1471, -1471, -1471,   301, -1471,
   -1471, -1471, -1471, -1471, -1471,  1018,  1021,  1025, -1471,   305,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471,  1003,  1029, -1471,
    1030, -1471,  1038, -1471, -1471, -1471,   307, -1471, -1471, -1471,
   -1471, -1471,   315, -1471,   117, -1471,  1045, -1471,   325, -1471,
   -1471,   750, -1471,  1046,  1051, -1471, -1471,  1049,  1057, -1471,
   -1471,  1064,  1069, -1471, -1471, -1471,  1073,  1080,  1085,  1086,
     759,   847,   856,   857,   858,   861,   862,   863,   866,   868,
    1107,   874,   877,  1109,  1111,  1118,  1120,  1121,  1123,   186,
   -1471, -1471,   186, -1471,   946,   735, -1471,   947,   153, -1471,
     949,   648, -1471,   951,  1452, -1471,   952,  -101, -1471, -1471,
     -42, -1471,  1125,  1126,    34, -1471,   669, -1471,   960,   631,
   -1471,   961,  -104, -1471,   963,   891,   892,   896,   903,   930,
     943,   129, -1471,  1140,  1156,   958,   970,   973,    93, -1471,
     917,   992,  1004,   -37, -1471,   281, -1471,   964,   923,  1166,
    1010,  1171,   288, -1471, -1471,    53,   965, -1471,   940,  -170,
   -1471, -1471,  1183,  1216,  1188, -1471,   967,   306, -1471,   968,
   -1471, -1471,  1013,  1016,  1026,  1031, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471,   436, -1471, -1471,  1032,
    1033,  1035,   813,  1036,  1037, -1471,   327, -1471,   329, -1471,
    1217, -1471,  1219, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,   371,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,  1039,  1040,
   -1471, -1471, -1471,  1220,  1225, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471,  1222,  1228, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471,  1224, -1471,   372, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471,   331,  1042, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,  1231,
   -1471,  1232, -1471, -1471, -1471, -1471, -1471, -1471, -1471,   373,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
    1043, -1471,    35, -1471, -1471,  1233, -1471, -1471, -1471, -1471,
   -1471,   383, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
    1047,   384, -1471,   420, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471,  1452, -1471, -1471, -1471,  1235,  1237,  1050,
    1053, -1471,   669, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
    1238,  1239,  1240,  1044,  1241,  1054,  1243,   281, -1471, -1471,
   -1471,  1244,  1048,  1245,    53, -1471, -1471, -1471, -1471, -1471,
    1052,  1058, -1471, -1471, -1471,   336,  1059,  1065, -1471,  1246,
   -1471,  1250, -1471,  1251, -1471,  1066, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471,   137,  1252,  1272, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471,   422, -1471, -1471, -1471,
   -1471, -1471, -1471,  1281,  1247, -1471, -1471,   118, -1471,  1254,
    1287,  1291,  1305,   137, -1471,   -40, -1471,  1252,  -130,  1272,
   -1471,  1070,  1072,  1077,  1324, -1471, -1471, -1471, -1471, -1471,
   -1471,   423, -1471, -1471, -1471, -1471,  1306,  1326,  1328, -1471,
     426, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471,  1329,  1331,   -40, -1471,  1336,  1089,  1099,  1100,
    1339,  -130, -1471, -1471,  1338,  1346, -1471,  1112, -1471,  1114,
   -1471, -1471, -1471,  1115, -1471,    40, -1471,  1329, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,   432, -1471,
   -1471, -1471,  1348,    40, -1471,  1117, -1471, -1471
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   208,     9,   405,    11,
     629,    13,   674,    15,   709,    17,   544,    19,   553,    21,
     592,    23,   367,    25,   922,    27,   954,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   711,     0,   555,   594,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   145,   952,   206,   227,   229,   231,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   195,     0,     0,     0,     0,     0,   165,
     172,   174,     0,     0,     0,     0,     0,     0,     0,   396,
     542,   583,     0,   198,   200,   178,   481,   661,   663,     0,
       0,     0,   323,   342,   332,   312,   747,   700,   358,   379,
     783,     0,   344,   808,   903,   920,   188,   190,     0,     0,
       0,     0,   964,  1006,     0,   144,     0,    69,    72,    73,
      74,    75,    76,    77,    78,    79,    80,   110,   111,   112,
     113,   114,   115,    81,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   117,   118,   132,
     133,   134,   106,   141,   142,   143,   136,   137,   138,   139,
      84,    85,    86,    87,   103,    88,    90,    89,   135,    94,
      95,    82,   107,   108,   109,    83,    92,    93,   101,   102,
     104,    91,    96,    97,    98,    99,   100,   105,   116,   140,
     221,     0,     0,     0,     0,   220,     0,   210,   213,   214,
     215,   216,   217,   218,   219,   620,   665,   462,   464,   466,
       0,     0,   470,   472,   474,   468,   744,   461,   410,   411,
     412,   413,   414,   415,   416,   417,   437,   438,   439,   440,
     441,   442,   445,   446,   447,   448,   449,   450,   451,   452,
     453,   454,   455,   456,   457,   443,   444,   458,   459,   460,
       0,   407,   421,   422,   423,   426,   427,   428,   429,   431,
     432,   433,   424,   425,   418,   419,   435,   436,   420,   430,
     434,   658,     0,   657,   641,   642,   643,   644,   645,   646,
     647,   648,   649,   650,   651,   652,   653,   654,   637,   638,
     639,   640,   636,     0,   631,   634,   635,   655,   656,   693,
       0,   696,     0,     0,   692,   684,   685,   686,   687,   683,
     682,   690,   691,     0,   676,   679,   680,   688,   689,   681,
     742,   728,   730,   732,   734,   736,   738,   740,   727,   724,
     725,   726,     0,   712,   713,   718,   719,   720,   716,   721,
     722,   723,   717,     0,   573,   279,     0,   577,   575,   580,
       0,   569,   570,     0,   556,   557,   560,   572,   561,   562,
     563,   579,   564,   565,   566,   567,   568,   611,     0,     0,
       0,   618,   609,   610,   613,   614,     0,   595,   596,   599,
     600,   601,   602,   603,   604,   605,   608,   606,   607,   375,
     377,   372,     0,   369,   373,   374,     0,   939,     0,   942,
       0,     0,   946,   950,   937,   935,   936,     0,   924,   927,
     928,   929,   930,   931,   932,   933,   934,   961,     0,     0,
     956,   959,   960,    47,    52,     0,    39,    45,     0,    66,
      62,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    60,    71,    68,     0,     0,     0,     0,
       0,   212,   209,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   409,   406,     0,     0,   633,
     630,     0,     0,     0,     0,     0,   678,   675,     0,     0,
       0,     0,     0,     0,     0,     0,   710,   715,   545,     0,
       0,     0,     0,     0,     0,     0,   554,   559,     0,     0,
       0,     0,     0,   593,   598,     0,     0,   371,   368,     0,
       0,     0,     0,     0,     0,     0,     0,   926,   923,     0,
       0,   958,   955,    51,    43,     0,     0,     0,     0,     0,
       0,     0,     0,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,     0,   193,
     194,   162,   163,   164,     0,     0,     0,   176,   177,   184,
     185,   186,   187,   192,     0,     0,     0,   197,     0,     0,
       0,     0,     0,     0,   476,   477,   478,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   807,     0,     0,     0,
       0,     0,     0,   202,   203,   204,   205,     0,     0,    70,
       0,   223,   224,   225,   226,   211,     0,     0,     0,     0,
       0,   479,   480,     0,     0,     0,     0,     0,   408,     0,
     660,   632,     0,   695,     0,   698,   699,   677,     0,     0,
       0,     0,     0,     0,     0,     0,   714,     0,     0,   571,
       0,     0,     0,   582,   558,     0,   615,   616,   617,     0,
     597,     0,     0,   370,   938,     0,   941,     0,   944,   945,
       0,     0,   925,     0,   963,   957,     0,     0,   146,     0,
       0,     0,     0,   233,   196,   167,   168,   169,   170,   171,
     166,   173,   175,   398,   546,   585,   199,   201,   180,   181,
     182,   183,   179,   483,    40,   662,   664,     0,    48,     0,
       0,   749,   702,   360,     0,     0,     0,   810,     0,     0,
     189,   191,     0,     0,    53,   222,   622,   667,   463,   465,
     467,   471,   473,   475,   469,     0,   659,   694,   697,   743,
     729,   731,   733,   735,   737,   739,   741,   574,   280,   578,
     576,   581,   612,   619,   376,   378,   940,   943,   948,   949,
     947,   951,   233,    44,     0,     0,     0,   268,   270,   272,
     276,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   289,     0,     0,   297,   299,   301,   303,   305,   306,
     307,   308,   309,   310,   274,   267,     0,   240,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   258,   259,   260,   261,   257,   262,   263,   264,
     265,   266,     0,   238,     0,   234,   235,   403,     0,   399,
     400,   551,     0,   547,   548,   590,     0,   586,   587,   488,
       0,   484,   485,   330,   331,     0,   325,   328,   329,     0,
     340,   341,   337,     0,   334,   338,   339,   319,   321,     0,
     314,   317,   318,   754,     0,   750,   751,   707,     0,   703,
     704,   365,     0,   361,   362,     0,     0,     0,     0,     0,
       0,     0,   381,   384,   385,   386,   387,   388,   389,   797,
     803,     0,     0,     0,   796,   793,   794,   795,     0,   785,
     788,   791,   789,   790,   792,     0,     0,     0,   354,     0,
     346,   349,   350,   351,   352,   353,   815,     0,   811,   812,
       0,   915,     0,   918,   911,   912,     0,   905,   908,   909,
     910,   913,     0,   969,     0,   966,     0,  1012,     0,  1008,
    1011,    55,   627,     0,   623,   624,   672,     0,   668,   669,
     746,     0,     0,    64,   953,   207,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   242,
     228,   230,     0,   232,   237,     0,   397,   402,   555,   543,
     550,   594,   584,   589,     0,   482,   487,   327,   324,   343,
     336,   333,     0,     0,   316,   313,   756,   748,   753,   711,
     701,   706,     0,   359,   364,     0,     0,     0,     0,     0,
       0,   383,   380,     0,     0,     0,     0,     0,   787,   784,
       0,     0,     0,   348,   345,     0,   809,   814,     0,     0,
       0,     0,   907,   904,   921,     0,   968,   965,     0,  1010,
    1007,    57,     0,    56,     0,   621,   626,     0,   666,   671,
     745,   962,     0,     0,     0,     0,   278,   281,   282,   283,
     284,   285,   286,   287,   296,   288,     0,   294,   295,     0,
       0,     0,     0,     0,     0,   241,     0,   236,     0,   401,
       0,   549,     0,   588,   541,   508,   509,   510,   512,   513,
     514,   497,   498,   517,   518,   519,   520,   521,   522,   525,
     526,   527,   528,   529,   530,   531,   532,   533,   534,   535,
     536,   537,   523,   524,   538,   539,   540,   493,   494,   495,
     496,   504,   505,   506,   507,   501,   502,   503,   511,     0,
     490,   499,   515,   516,   500,   486,   326,   335,     0,     0,
     315,   777,   779,     0,     0,   775,   769,   770,   771,   772,
     773,   774,   776,   766,   767,   768,     0,   757,   758,   761,
     762,   763,   764,   765,   752,     0,   705,     0,   363,   390,
     391,   392,   393,   394,   395,   382,     0,     0,   802,   805,
     806,   786,   355,   356,   357,   347,   833,   838,   840,     0,
     863,     0,   844,   832,   825,   826,   827,   830,   831,     0,
     817,   820,   821,   822,   823,   828,   829,   824,   813,   914,
       0,   917,     0,   906,   984,     0,   982,   980,   974,   978,
     979,     0,   971,   976,   977,   975,   967,  1013,  1009,    54,
      59,     0,   625,     0,   670,   269,   271,   273,   277,   291,
     292,   293,   290,   298,   300,   302,   304,   311,   275,   239,
     404,   552,   591,   492,   489,   320,   322,     0,     0,     0,
       0,   755,   760,   708,   366,   799,   800,   801,   798,   804,
       0,     0,     0,     0,     0,     0,     0,   819,   816,   916,
     919,     0,     0,     0,   973,   970,    58,   628,   673,   491,
       0,     0,   781,   782,   759,     0,     0,     0,   842,     0,
     843,     0,   818,     0,   981,     0,   972,   778,   780,   835,
     836,   837,   834,   839,   841,     0,   846,     0,   983,   875,
     878,   880,   882,   874,   873,   872,     0,   865,   868,   869,
     870,   871,   851,     0,   847,   848,   989,     0,   986,     0,
       0,     0,     0,   867,   864,     0,   845,   850,     0,   988,
     985,     0,     0,     0,     0,   866,   861,   860,   856,   858,
     859,     0,   853,   857,   849,   999,     0,     0,     0,  1004,
       0,   991,   994,   995,   996,   997,   998,   987,   877,   876,
     879,   881,   884,     0,   855,   852,     0,     0,     0,     0,
       0,   993,   990,   889,     0,   885,   886,     0,   854,     0,
    1001,  1002,  1003,     0,   992,     0,   883,   888,   862,  1000,
    1005,   901,   900,   894,   896,   897,   898,   899,     0,   891,
     895,   887,     0,   893,   890,     0,   892,   902
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471,   -10, -1471,  -643, -1471,
     597, -1471, -1471, -1471, -1471,   552, -1471,  -253, -1471, -1471,
   -1471,   -71, -1471, -1471, -1471, -1471, -1471, -1471, -1471,   573,
     808, -1471, -1471,   -61,   -58,   -55,   -41,   -38,   -35,   -18,
      89,    92,    97,   102,   103,   105,   108, -1471,   -15,   -12,
      27,    38, -1471, -1471,    41, -1471,    52, -1471,    55,   109,
      62, -1471, -1471,    69,    72,    74,    79,    84, -1471,    86,
   -1471,   113, -1471, -1471, -1471, -1471, -1471,   116, -1471,   119,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,   583,
     803, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471,   504, -1471,   283, -1471,  -765,   286, -1471,
   -1471, -1470, -1471, -1466, -1471, -1463, -1471, -1471, -1471, -1471,
     -25, -1471,  -804, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1099, -1471, -1098, -1471,
   -1094, -1471,   188, -1471, -1471, -1471, -1471, -1471, -1471,   268,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471,   271,  -789, -1471,
   -1471, -1471, -1471,   273, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471,   241, -1471, -1471, -1471, -1471, -1471, -1471, -1471,   261,
   -1471, -1471, -1471,   266,   762, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471,   255, -1471, -1471, -1471, -1471, -1471, -1471, -1073,
   -1471, -1471, -1471,   296, -1471, -1471, -1471,   302,   806, -1471,
   -1471, -1072, -1471, -1071, -1471,    -6, -1471,    -2, -1471,    64,
   -1471,   128, -1471,   120,   123,   126, -1471, -1065, -1471, -1471,
   -1471, -1471,   290, -1471, -1471,    25,  1312, -1471, -1471, -1471,
   -1471, -1471,   303, -1471, -1471, -1471,   304, -1471,   784, -1471,
     -63, -1471, -1471, -1471, -1471, -1471,   -60, -1471, -1471, -1471,
   -1471, -1471,    22, -1471, -1471, -1471,   310, -1471, -1471, -1471,
     317, -1471,   783, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471,   240, -1471, -1471,
   -1471,   246,   827, -1471, -1471,   -62,   -48, -1471,     8, -1471,
   -1471, -1471, -1471, -1471,   250, -1471, -1471, -1471,   253,   825,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471,   -59, -1471, -1471,
   -1471,   313, -1471, -1471, -1471,   312, -1471,   815,   578, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1060, -1471, -1471, -1471, -1471, -1471,
   -1471,   318, -1471, -1471, -1471,    42, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471,   289, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
     279, -1471, -1471,    32, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471,   -29, -1471, -1471,
     -74, -1471, -1471, -1471, -1471, -1471,   -31, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,   -86, -1471,
   -1471,   -99, -1471, -1471, -1471, -1471, -1471,   297, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,   617,   811,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471,   661,   810, -1471,
   -1471, -1471, -1471, -1471, -1471,   299, -1471, -1471,    49, -1471,
   -1471, -1471, -1471, -1471, -1471,   -11, -1471, -1471,   -51, -1471,
   -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471, -1471,   324,
   -1471
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     805,    87,    88,    41,    68,    84,    85,   825,  1041,  1152,
    1153,   895,    43,    70,    90,   478,    91,    45,    71,   166,
     167,   168,   481,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   508,   790,   188,   509,   189,   510,   190,   191,
     192,   524,   802,   193,   194,   195,   196,   197,   545,   198,
     546,   199,   200,   201,   202,   502,   203,   204,   522,   205,
     523,   206,   207,   208,   209,   210,   483,    47,    72,   246,
     247,   248,   556,   249,   250,   251,   252,   211,   484,   212,
     485,   213,   486,   924,   925,   926,  1082,   896,   897,   898,
    1056,   899,  1057,   900,  1058,   901,  1078,   902,  1059,   903,
     904,   600,   905,   906,   907,   908,   909,   910,   911,   912,
     913,  1070,  1352,   914,   915,   916,   917,  1073,   918,  1074,
     919,  1075,   920,  1076,   921,  1077,   214,   534,   959,   960,
     961,  1102,   962,  1103,   215,   531,   945,   946,   947,   948,
     216,   533,   953,   954,   955,   956,   217,   532,   218,   541,
    1009,  1010,  1011,  1012,  1013,   219,   537,   972,   973,   974,
    1112,    63,    80,   442,   443,   444,   615,   445,   616,   220,
     538,   981,   982,   983,   984,   985,   986,   987,   988,   221,
     518,   928,   929,   930,  1085,    49,    73,   300,   301,   302,
     565,   303,   566,   304,   567,   305,   573,   306,   570,   307,
     571,   308,   572,   222,   223,   224,   312,   313,   225,   525,
     940,   941,   942,  1094,  1239,  1240,   226,   519,    57,    77,
     932,   933,   934,  1088,    59,    78,   403,   404,   405,   406,
     407,   408,   409,   599,   410,   603,   411,   602,   412,   413,
     604,   414,   227,   520,   936,   937,   938,  1091,    61,    79,
     426,   427,   428,   429,   430,   608,   431,   432,   433,   434,
     435,   436,   612,   315,   563,  1043,  1044,  1045,  1154,    51,
      74,   343,   344,   345,   577,   346,   228,   526,   229,   527,
     318,   564,  1047,  1048,  1049,  1157,    53,    75,   363,   364,
     365,   581,   366,   367,   583,   368,   369,   230,   536,   968,
     969,   970,  1109,    55,    76,   382,   383,   384,   385,   589,
     386,   590,   387,   591,   388,   592,   389,   593,   390,   594,
     391,   595,   392,   588,   320,   574,  1051,   231,   535,   964,
     965,   966,  1106,  1266,  1267,  1268,  1269,  1270,  1367,  1271,
    1368,  1272,  1273,   232,   539,   998,   999,  1000,  1123,  1378,
    1001,  1002,  1124,  1003,  1004,   233,   234,   542,  1017,  1018,
    1019,  1135,  1309,  1310,  1311,  1380,  1422,  1312,  1381,  1313,
    1382,  1314,  1315,  1316,  1386,  1443,  1444,  1445,  1455,  1471,
    1472,  1473,  1493,  1317,  1384,  1436,  1437,  1438,  1449,  1489,
    1439,  1450,  1440,  1451,  1441,  1452,  1504,  1505,  1506,  1515,
    1528,  1529,  1530,  1532,   235,   543,  1026,  1027,  1028,  1029,
    1139,  1030,  1031,  1141,   236,   544,    65,    81,   457,   458,
     459,   460,   620,   461,   462,   622,   463,   464,   465,   625,
     860,   466,   626,   237,   482,    67,    82,   469,   470,   471,
     629,   472,   238,   551,  1034,  1035,  1145,  1331,  1332,  1333,
    1334,  1393,  1335,  1391,  1447,  1448,  1458,  1480,  1481,  1482,
    1496,  1483,  1484,  1485,  1486,  1500,   239,   552,  1038,  1039,
    1040
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     165,   245,   267,   323,   354,   378,    38,   401,   422,   441,
     454,   995,   268,   360,   319,   269,   424,   922,   270,   425,
     952,  1228,  1229,  1230,   253,   316,   347,   361,   380,  1238,
     415,   437,   271,   455,  1244,   272,  1304,  1305,   273,   804,
      31,  1306,    32,   943,    33,  1523,   439,   440,   395,  1524,
     467,   468,  1525,   402,   423,   274,  1036,  1097,   282,   324,
    1098,   283,   325,  1523,    42,   868,   869,  1524,   338,   355,
    1525,   164,   339,   356,  1100,   137,   138,  1101,   137,   138,
     254,   317,   348,   362,   381,   479,   416,   438,  1475,   456,
     480,  1476,  1477,  1478,  1479,   314,   342,   359,   379,   554,
     284,   326,   943,   950,   555,   951,   240,   241,   242,   243,
     244,   285,   327,   561,   286,   328,    86,   989,   562,   804,
    1146,  1459,   872,  1147,  1460,   287,   329,    30,   288,   330,
     439,   440,  1005,  1006,  1007,   290,   331,   164,   340,   357,
     944,   395,   291,   332,    89,   292,   333,   293,   334,  1466,
     858,   859,   294,   335,    44,   137,   138,   295,   336,   296,
     337,  1429,   275,   957,   958,   276,   575,   579,   137,   138,
     277,   576,   580,    46,   586,   278,   279,   394,   280,   587,
     617,   281,   289,   627,   130,   618,   297,   473,   628,   298,
     631,    48,   299,   309,   635,   632,   310,    50,    52,   311,
      54,   164,   341,   358,   164,   137,   138,    56,   137,   138,
     867,   868,   869,   870,   871,   872,   873,   874,   875,   876,
     877,   878,   879,   880,   881,  1521,   894,    58,   882,   883,
     884,   885,   886,   887,   888,   889,   890,   891,   892,   893,
     554,   395,   631,   396,   397,  1053,   561,  1054,   398,   399,
     400,  1055,   137,   138,    60,  1079,   990,   991,   992,   993,
    1080,  1079,   785,   786,   787,   788,  1081,    62,   137,   138,
    1324,    64,  1325,  1326,   395,  1104,    34,    35,    36,    37,
    1105,   164,   975,   976,   977,   978,   979,   980,  1304,  1305,
    1228,  1229,  1230,  1306,   164,    92,    93,  1121,  1238,    94,
     789,   474,  1122,  1244,  1128,    95,    96,    97,  1133,  1129,
    1142,   952,   475,  1134,   477,  1143,    66,  1186,   627,  1430,
    1431,  1432,   476,  1144,   995,   884,   885,   886,  1149,   596,
    1079,   164,   575,  1150,   164,  1359,   487,  1360,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   894,   488,  1363,   617,  1387,   597,   164,  1364,
    1374,  1388,   132,   133,   134,   135,  1394,   579,   598,   489,
     136,  1395,  1397,   131,   164,   490,   137,   138,   491,   137,
     138,   492,   493,   137,   138,   494,   139,   140,   141,   142,
     143,   144,   145,   495,   496,   146,   349,   350,   351,   352,
     353,   137,   138,   586,   147,  1453,  1494,   164,  1398,  1501,
    1454,  1495,   497,   148,  1502,  1533,   149,   262,   263,   264,
    1534,   498,   499,   150,   265,   322,   798,   799,   800,   801,
     500,   151,   152,   501,  1296,   503,   153,   504,  1297,  1298,
    1299,  1300,   505,   506,   633,   634,   507,   511,  1301,  1302,
     831,   832,   833,   512,   154,  1349,  1350,  1351,   155,  1020,
    1021,  1022,   513,   165,   514,   839,   840,   841,   842,   515,
     245,  1375,  1376,  1377,   156,   157,   158,   159,   160,   161,
     162,   516,   517,   521,   267,   528,   853,   529,   323,   163,
    1419,  1420,  1421,   253,   268,   354,   319,   269,   530,   540,
     270,   547,   164,   548,   360,   164,   378,   316,   549,  1023,
     550,   347,   553,   557,   271,   558,   401,   272,   361,   559,
     273,   560,   568,   422,   569,   578,   582,   164,   584,   380,
     585,   424,   601,   605,   425,   606,   454,   274,   607,   415,
     282,   609,   610,   283,   324,   611,   437,   325,   613,   254,
     614,   652,   619,   338,   621,   623,   624,   339,   630,   455,
     355,   636,   402,   317,   356,   637,   638,   348,   639,   423,
     640,   641,   642,   643,   362,   644,   645,   314,   646,   647,
     648,   342,   284,   649,   650,   381,   326,   651,   359,   653,
     654,   656,   655,   285,   658,   416,   286,   327,   657,   379,
     328,   659,   438,   660,   664,   665,   661,   287,   666,   669,
     288,   329,   662,   663,   330,   456,   667,   290,   670,   668,
     674,   331,   671,   340,   291,   672,   673,   292,   332,   293,
     357,   333,   684,   334,   294,   675,   676,   677,   335,   295,
     678,   296,   679,   336,   275,   337,   680,   276,   681,   682,
     683,   685,   277,   686,   687,   688,   689,   278,   279,   690,
     280,   691,   692,   281,   289,   693,   694,   695,   297,   696,
     697,   298,   698,   699,   299,   309,   700,   701,   310,   702,
     703,   311,   707,   708,   704,   705,   165,   341,   706,   245,
     710,   711,   712,   713,   358,   714,   716,   717,   131,   718,
     722,   719,   720,    98,    99,   100,   101,   102,   103,   721,
     723,   724,   253,   725,   726,   727,   395,   417,   396,   397,
     418,   419,   420,   729,   994,  1008,   137,   138,   454,   730,
     732,   733,  1037,   734,   735,   736,   131,   395,   738,   739,
     740,   741,   370,   137,   138,   742,   863,   996,  1014,   743,
    1024,   455,   371,   372,   373,   374,   375,   376,   377,   421,
     744,   745,   747,   748,   137,   138,   750,   749,   254,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,  1251,  1252,  1253,  1254,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     751,   752,   131,   997,  1015,   755,  1025,   456,   759,   753,
     761,   137,   138,   756,   133,   134,   135,   757,   758,   762,
     764,   765,   255,   766,   256,   767,   768,   769,   770,   771,
     137,   138,   257,   258,   259,   260,   261,   139,   140,   141,
     887,   888,   889,   890,   891,   892,   262,   263,   264,   773,
     774,   776,   164,   265,   778,   147,   777,   779,   780,   781,
     782,   783,   784,   266,   791,   792,   793,   794,   795,   164,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,   803,    32,   807,   808,   796,   797,
     164,   446,   447,   448,   449,   450,   451,   452,   453,   809,
     806,   811,   810,   812,   813,   820,   821,   814,   815,   816,
     817,   818,   822,   819,   824,   823,   826,   827,   828,   861,
     835,   829,   830,   834,   836,   156,   157,   862,   837,   838,
     843,   844,   845,   923,   927,   846,   931,   164,   935,   939,
     847,   848,   849,   850,   851,   852,   854,   963,   967,   856,
     971,  1016,  1033,   857,  1042,  1046,   164,   371,  1060,  1061,
    1062,  1063,  1064,  1065,  1066,  1067,  1068,  1069,  1071,  1072,
    1084,  1151,  1083,  1087,  1086,  1089,  1090,  1092,  1093,  1096,
    1095,  1166,  1108,  1099,  1107,  1111,  1110,  1113,  1114,  1136,
    1115,  1116,  1117,  1118,   267,  1119,  1120,   401,  1125,  1126,
     422,  1127,  1130,  1194,   268,  1131,   319,   269,   424,  1132,
     270,   425,  1137,  1195,  1138,  1255,  1196,   316,   378,  1197,
     415,   441,  1140,   437,   271,  1256,  1242,   272,  1257,  1148,
     273,  1258,  1155,  1198,  1156,  1158,  1199,   994,  1264,  1200,
    1159,   380,  1008,   402,  1303,  1259,   423,   274,  1260,  1227,
     282,  1261,  1160,   283,  1327,  1161,  1201,  1162,  1037,  1209,
     996,  1262,  1210,   323,  1163,  1014,   354,  1307,  1231,  1164,
    1165,  1167,  1232,   317,  1024,   360,   416,  1329,  1168,   438,
    1170,  1169,  1243,  1171,  1172,  1173,   347,   314,  1174,   361,
    1175,  1176,   284,  1179,  1265,  1180,  1241,   381,  1177,  1178,
    1328,  1211,  1181,   285,  1182,  1183,   286,  1184,  1263,  1248,
    1249,   379,  1212,  1279,  1280,  1213,   997,   287,  1281,   324,
     288,  1015,   325,  1308,  1286,  1282,  1214,   290,   338,  1215,
    1025,   355,   339,  1330,   291,   356,  1217,   292,  1233,   293,
    1287,  1292,   348,  1218,   294,   362,  1219,  1319,  1220,   295,
    1320,   296,  1283,  1221,   275,  1322,   342,   276,  1222,   359,
    1223,   326,   277,  1202,  1337,  1284,  1203,   278,   279,  1339,
     280,  1204,   327,   281,   289,   328,  1205,  1206,   297,  1207,
    1288,   298,  1208,  1216,   299,   309,   329,  1224,   310,   330,
    1225,   311,  1289,  1226,  1235,  1290,   331,  1236,   340,  1340,
    1237,   357,  1234,   332,  1369,  1361,   333,  1362,   334,  1370,
    1371,  1372,  1373,   335,  1293,  1383,  1385,  1392,   336,  1400,
     337,  1401,  1405,  1406,  1407,  1409,  1294,  1411,  1413,  1415,
    1457,  1488,  1321,  1425,  1345,  1426,  1427,  1346,  1461,  1442,
     116,   117,   118,   119,   120,   121,   122,  1347,   124,   125,
     126,   127,  1348,  1353,  1354,   131,  1355,  1357,  1358,  1446,
    1365,  1366,   341,  1379,  1389,   358,  1408,  1456,  1396,   135,
    1414,  1462,  1194,  1417,  1402,  1463,   321,  1403,  1410,  1418,
    1423,  1255,  1195,   137,   138,  1196,  1424,  1428,  1197,  1464,
    1497,  1256,  1390,  1490,  1257,  1242,  1303,  1258,  1491,   262,
     263,   264,  1198,  1327,  1264,  1199,   265,   322,  1200,  1492,
    1498,  1259,  1499,  1510,  1260,  1507,  1503,  1261,  1227,  1307,
    1509,  1511,  1512,  1513,  1516,  1201,  1329,  1262,  1209,  1517,
     864,  1210,  1535,  1518,  1433,  1519,  1520,  1231,  1537,   855,
     949,  1232,   709,   866,   715,  1185,  1052,  1187,  1246,  1328,
    1356,  1243,  1250,  1247,  1295,  1278,  1285,  1434,  1277,   763,
    1265,   728,  1433,  1189,  1467,  1241,  1245,  1188,  1399,   393,
    1211,   754,  1190,  1191,  1263,  1308,  1342,   760,   156,   157,
    1341,  1212,  1330,  1193,  1213,  1434,   731,  1469,  1192,  1344,
    1343,   737,   746,  1050,  1404,  1214,  1318,  1291,  1215,  1412,
    1508,  1275,  1465,  1467,  1276,  1217,  1274,  1233,  1474,   164,
    1468,  1531,  1218,  1435,  1536,  1219,  1032,  1220,   772,  1323,
     865,   775,  1221,  1416,  1522,  1336,  1469,  1222,  1487,  1223,
    1514,     0,  1202,     0,     0,  1203,     0,     0,     0,     0,
    1204,  1435,  1522,  1470,     0,  1205,  1206,  1526,  1207,  1468,
       0,  1208,  1216,  1338,     0,     0,  1224,     0,     0,  1225,
       0,     0,  1226,  1235,     0,  1526,  1236,     0,     0,  1237,
       0,  1234,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1470,     0,     0,     0,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
       0,     0,     0,  1527,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,     0,   131,
     395,  1527,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   133,   134,   135,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   137,   138,     0,
     258,   259,     0,   261,   139,   140,   141,     0,     0,     0,
       0,     0,     0,   262,   263,   264,     0,     0,     0,     0,
     265,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     266,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   156,   157,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   164
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   815,    73,    75,    73,    73,    79,   782,    73,    79,
     809,  1094,  1094,  1094,    72,    73,    74,    75,    76,  1094,
      78,    79,    73,    81,  1094,    73,  1135,  1135,    73,   682,
       5,  1135,     7,   144,     9,  1515,   150,   151,    88,  1515,
      13,    14,  1515,    78,    79,    73,   226,     3,    73,    74,
       6,    73,    74,  1533,     7,    25,    26,  1533,    74,    75,
    1533,   241,    74,    75,     3,   115,   116,     6,   115,   116,
      72,    73,    74,    75,    76,     3,    78,    79,   218,    81,
       8,   221,   222,   223,   224,    73,    74,    75,    76,     3,
      73,    74,   144,   145,     8,   147,    16,    17,    18,    19,
      20,    73,    74,     3,    73,    74,   241,    24,     8,   762,
       3,     3,    29,     6,     6,    73,    74,     0,    73,    74,
     150,   151,   169,   170,   171,    73,    74,   241,    74,    75,
     241,    88,    73,    74,    10,    73,    74,    73,    74,   189,
     203,   204,    73,    74,     7,   115,   116,    73,    74,    73,
      74,    24,    73,   129,   130,    73,     3,     3,   115,   116,
      73,     8,     8,     7,     3,    73,    73,    24,    73,     8,
       3,    73,    73,     3,    86,     8,    73,     6,     8,    73,
       3,     7,    73,    73,   241,     8,    73,     7,     7,    73,
       7,   241,    74,    75,   241,   115,   116,     7,   115,   116,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,   185,   186,     7,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
       3,    88,     3,    90,    91,     8,     3,     8,    95,    96,
      97,     8,   115,   116,     7,     3,   163,   164,   165,   166,
       8,     3,   206,   207,   208,   209,     8,     7,   115,   116,
     217,     7,   219,   220,    88,     3,   241,   242,   243,   244,
       8,   241,   153,   154,   155,   156,   157,   158,  1387,  1387,
    1363,  1363,  1363,  1387,   241,    11,    12,     3,  1363,    15,
     244,     3,     8,  1363,     3,    21,    22,    23,     3,     8,
       3,  1100,     4,     8,     3,     8,     7,  1082,     3,   182,
     183,   184,     8,     8,  1128,    44,    45,    46,     3,     8,
       3,   241,     3,     8,   241,     8,     4,     8,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,   186,     4,     3,     3,     3,     3,   241,     8,
       8,     8,    98,    99,   100,   101,     3,     3,     8,     4,
     106,     8,     8,    87,   241,     4,   115,   116,     4,   115,
     116,     4,     4,   115,   116,     4,   122,   123,   124,   125,
     126,   127,   128,     4,     4,   131,   110,   111,   112,   113,
     114,   115,   116,     3,   140,     3,     3,   241,     8,     3,
       8,     8,     4,   149,     8,     3,   152,   131,   132,   133,
       8,     4,     4,   159,   138,   139,   102,   103,   104,   105,
       4,   167,   168,     4,   173,     4,   172,     4,   177,   178,
     179,   180,     4,     4,   474,   475,     4,     4,   187,   188,
     723,   724,   725,     4,   190,    39,    40,    41,   194,   191,
     192,   193,     4,   554,     4,   738,   739,   740,   741,     4,
     561,   160,   161,   162,   210,   211,   212,   213,   214,   215,
     216,     4,     4,     4,   575,     4,   759,     4,   579,   225,
     174,   175,   176,   561,   575,   586,   575,   575,     4,     4,
     575,     4,   241,     4,   586,   241,   597,   575,     4,   241,
       4,   579,     4,     4,   575,     4,   607,   575,   586,     4,
     575,     4,     4,   614,     4,     4,     4,   241,     4,   597,
       4,   614,     4,     4,   614,     8,   627,   575,     3,   607,
     575,     4,     4,   575,   579,     4,   614,   579,     8,   561,
       3,   243,     4,   579,     4,     4,     4,   579,     4,   627,
     586,     4,   607,   575,   586,     4,     4,   579,     4,   614,
       4,     4,     4,   242,   586,   242,   242,   575,   242,   242,
     242,   579,   575,   242,   242,   597,   579,   244,   586,   243,
     243,   243,   242,   575,     4,   607,   575,   579,   242,   597,
     579,   242,   614,   242,     4,     4,   244,   575,     4,   243,
     575,   579,   244,   244,   579,   627,   244,   575,   242,   244,
       4,   579,   242,   579,   575,   242,   244,   575,   579,   575,
     586,   579,   244,   579,   575,     4,     4,   242,   579,   575,
       4,   575,     4,   579,   575,   579,     4,   575,     4,     4,
       4,   244,   575,   244,     4,     4,     4,   575,   575,     4,
     575,     4,     4,   575,   575,     4,     4,     4,   575,   242,
       4,   575,     4,     4,   575,   575,     4,     4,   575,     4,
     244,   575,     4,     4,   244,   244,   777,   579,   244,   780,
       4,   244,   244,   242,   586,   242,     4,     4,    87,     4,
     244,     4,     4,    54,    55,    56,    57,    58,    59,   242,
       4,     4,   780,     4,     4,     4,    88,    89,    90,    91,
      92,    93,    94,     4,   815,   816,   115,   116,   819,   242,
       4,   242,   823,     4,   242,   242,    87,    88,     4,     4,
       4,     4,   131,   115,   116,     4,   776,   815,   816,     4,
     818,   819,   141,   142,   143,   144,   145,   146,   147,   131,
       4,     4,     4,     4,   115,   116,     4,   242,   780,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,   134,   135,   136,   137,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
       4,     4,    87,   815,   816,     4,   818,   819,     4,   244,
       4,   115,   116,   244,    99,   100,   101,   244,   244,     4,
     244,     4,   107,   242,   109,     4,   242,   242,     4,     4,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
      47,    48,    49,    50,    51,    52,   131,   132,   133,     4,
     242,     4,   241,   138,   241,   140,     7,     7,     7,     7,
       7,     5,   241,   148,   241,   241,     5,     5,     5,   241,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,     5,     7,     5,     5,   241,   241,
     241,   195,   196,   197,   198,   199,   200,   201,   202,     5,
     241,     5,     7,     5,     5,   241,   241,     7,     7,     7,
       5,     7,     5,     7,     5,     7,     5,     5,   241,   205,
       7,   241,   241,   241,   241,   210,   211,     5,   241,   241,
     241,   241,   241,     7,     7,   241,     7,   241,     7,     7,
     241,   241,   241,   241,   241,   241,   241,     7,     7,   241,
       7,     7,     7,   241,     7,     7,   241,   141,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       3,   241,     6,     3,     6,     6,     3,     6,     3,     3,
       6,   242,     3,     6,     6,     3,     6,     6,     3,     6,
       4,     4,     4,     4,  1085,     4,     4,  1088,     4,     4,
    1091,     4,     4,  1094,  1085,     4,  1085,  1085,  1091,     4,
    1085,  1091,     3,  1094,     4,  1106,  1094,  1085,  1109,  1094,
    1088,  1112,     4,  1091,  1085,  1106,  1094,  1085,  1106,     4,
    1085,  1106,     6,  1094,     3,     6,  1094,  1128,  1106,  1094,
       3,  1109,  1133,  1088,  1135,  1106,  1091,  1085,  1106,  1094,
    1085,  1106,     8,  1085,  1145,     6,  1094,     4,  1149,  1094,
    1128,  1106,  1094,  1154,     4,  1133,  1157,  1135,  1094,     4,
       4,   244,  1094,  1085,  1142,  1157,  1088,  1145,   242,  1091,
     242,   244,  1094,   242,   242,   242,  1154,  1085,   242,  1157,
     242,     4,  1085,     4,  1106,     4,  1094,  1109,   244,   242,
    1145,  1094,     4,  1085,     4,     4,  1085,     4,  1106,     4,
       4,  1109,  1094,   242,   242,  1094,  1128,  1085,   242,  1154,
    1085,  1133,  1154,  1135,     4,   242,  1094,  1085,  1154,  1094,
    1142,  1157,  1154,  1145,  1085,  1157,  1094,  1085,  1094,  1085,
       4,   244,  1154,  1094,  1085,  1157,  1094,   244,  1094,  1085,
       4,  1085,   242,  1094,  1085,     4,  1154,  1085,  1094,  1157,
    1094,  1154,  1085,  1094,   244,   242,  1094,  1085,  1085,     6,
    1085,  1094,  1154,  1085,  1085,  1154,  1094,  1094,  1085,  1094,
     242,  1085,  1094,  1094,  1085,  1085,  1154,  1094,  1085,  1154,
    1094,  1085,   242,  1094,  1094,   242,  1154,  1094,  1154,     3,
    1094,  1157,  1094,  1154,     4,     8,  1154,     8,  1154,     4,
       8,     3,     8,  1154,   242,     4,     4,     4,  1154,     4,
    1154,     4,     4,     4,     4,     4,   242,     4,     4,     4,
       3,   181,   242,     7,   241,     5,     5,   241,     4,     7,
      72,    73,    74,    75,    76,    77,    78,   241,    80,    81,
      82,    83,   241,   241,   241,    87,   241,   241,   241,     7,
     241,   241,  1154,   241,   241,  1157,   242,     6,   241,   101,
     242,     4,  1363,   241,   244,     4,   108,   244,   244,   241,
     241,  1372,  1363,   115,   116,  1363,   241,   241,  1363,     4,
       4,  1372,  1322,   241,  1372,  1363,  1387,  1372,   241,   131,
     132,   133,  1363,  1394,  1372,  1363,   138,   139,  1363,     5,
       4,  1372,     4,   244,  1372,     4,     7,  1372,  1363,  1387,
       4,   242,   242,     4,     6,  1363,  1394,  1372,  1363,     3,
     777,  1363,     4,   241,  1425,   241,   241,  1363,   241,   762,
     808,  1363,   554,   780,   561,  1079,   862,  1084,  1097,  1394,
    1182,  1363,  1104,  1100,  1133,  1114,  1121,  1425,  1112,   617,
    1372,   575,  1453,  1087,  1455,  1363,  1096,  1085,  1363,    77,
    1363,   607,  1088,  1090,  1372,  1387,  1156,   614,   210,   211,
    1154,  1363,  1394,  1093,  1363,  1453,   579,  1455,  1091,  1159,
    1157,   586,   597,   835,  1372,  1363,  1137,  1128,  1363,  1387,
    1494,  1109,  1453,  1494,  1111,  1363,  1108,  1363,  1457,   241,
    1455,  1517,  1363,  1425,  1533,  1363,   819,  1363,   627,  1142,
     779,   631,  1363,  1394,  1515,  1146,  1494,  1363,  1459,  1363,
    1501,    -1,  1363,    -1,    -1,  1363,    -1,    -1,    -1,    -1,
    1363,  1453,  1533,  1455,    -1,  1363,  1363,  1515,  1363,  1494,
      -1,  1363,  1363,  1149,    -1,    -1,  1363,    -1,    -1,  1363,
      -1,    -1,  1363,  1363,    -1,  1533,  1363,    -1,    -1,  1363,
      -1,  1363,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1494,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      -1,    -1,    -1,  1515,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    -1,    87,
      88,  1533,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    99,   100,   101,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   115,   116,    -1,
     118,   119,    -1,   121,   122,   123,   124,    -1,    -1,    -1,
      -1,    -1,    -1,   131,   132,   133,    -1,    -1,    -1,    -1,
     138,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   210,   211,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   241
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
       0,     5,     7,     9,   241,   242,   243,   244,   261,   262,
     263,   268,     7,   277,     7,   282,     7,   342,     7,   460,
       7,   544,     7,   561,     7,   578,     7,   493,     7,   499,
       7,   523,     7,   436,     7,   691,     7,   710,   269,   264,
     278,   283,   343,   461,   545,   562,   579,   494,   500,   524,
     437,   692,   711,   261,   270,   271,   241,   266,   267,    10,
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
     340,   352,   354,   356,   401,   409,   415,   421,   423,   430,
     444,   454,   478,   479,   480,   483,   491,   517,   551,   553,
     572,   602,   618,   630,   631,   679,   689,   708,   717,   741,
      16,    17,    18,    19,    20,   276,   344,   345,   346,   348,
     349,   350,   351,   551,   553,   107,   109,   117,   118,   119,
     120,   121,   131,   132,   133,   138,   148,   276,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   303,   304,   305,   306,   309,   311,   313,   314,
     315,   318,   319,   320,   321,   322,   324,   326,   332,   334,
     462,   463,   464,   466,   468,   470,   472,   474,   476,   478,
     479,   480,   481,   482,   517,   538,   551,   553,   555,   572,
     599,   108,   139,   276,   303,   304,   305,   306,   309,   311,
     313,   315,   318,   319,   320,   321,   322,   324,   470,   472,
     474,   476,   517,   546,   547,   548,   550,   551,   553,   110,
     111,   112,   113,   114,   276,   470,   472,   474,   476,   517,
     550,   551,   553,   563,   564,   565,   567,   568,   570,   571,
     131,   141,   142,   143,   144,   145,   146,   147,   276,   517,
     551,   553,   580,   581,   582,   583,   585,   587,   589,   591,
     593,   595,   597,   491,    24,    88,    90,    91,    95,    96,
      97,   276,   375,   501,   502,   503,   504,   505,   506,   507,
     509,   511,   513,   514,   516,   551,   553,    89,    92,    93,
      94,   131,   276,   375,   505,   511,   525,   526,   527,   528,
     529,   531,   532,   533,   534,   535,   536,   551,   553,   150,
     151,   276,   438,   439,   440,   442,   195,   196,   197,   198,
     199,   200,   201,   202,   276,   551,   553,   693,   694,   695,
     696,   698,   699,   701,   702,   703,   706,    13,    14,   712,
     713,   714,   716,     6,     3,     4,     8,     3,   280,     3,
       8,   287,   709,   341,   353,   355,   357,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   330,     4,     4,     4,     4,     4,   307,   310,
     312,     4,     4,     4,     4,     4,     4,     4,   455,   492,
     518,     4,   333,   335,   316,   484,   552,   554,     4,     4,
       4,   410,   422,   416,   402,   603,   573,   431,   445,   619,
       4,   424,   632,   680,   690,   323,   325,     4,     4,     4,
       4,   718,   742,     4,     3,     8,   347,     4,     4,     4,
       4,     3,     8,   539,   556,   465,   467,   469,     4,     4,
     473,   475,   477,   471,   600,     3,     8,   549,     4,     3,
       8,   566,     4,   569,     4,     4,     3,     8,   598,   584,
     586,   588,   590,   592,   594,   596,     8,     3,     8,   508,
     376,     4,   512,   510,   515,     4,     8,     3,   530,     4,
       4,     4,   537,     8,     3,   441,   443,     3,     8,     4,
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
       4,   242,   244,     4,     4,     4,     4,     4,   463,     4,
     242,   547,     4,   242,     4,   242,   242,   564,     4,     4,
       4,     4,     4,     4,     4,     4,   582,     4,     4,   242,
       4,     4,     4,   244,   503,     4,   244,   244,   244,     4,
     527,     4,     4,   439,   244,     4,   242,     4,   242,   242,
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
      50,    51,    52,    53,   186,   276,   362,   363,   364,   366,
     368,   370,   372,   374,   375,   377,   378,   379,   380,   381,
     382,   383,   384,   385,   388,   389,   390,   391,   393,   395,
     397,   399,   362,     7,   358,   359,   360,     7,   456,   457,
     458,     7,   495,   496,   497,     7,   519,   520,   521,     7,
     485,   486,   487,   144,   241,   411,   412,   413,   414,   270,
     145,   147,   413,   417,   418,   419,   420,   129,   130,   403,
     404,   405,   407,     7,   604,   605,   606,     7,   574,   575,
     576,     7,   432,   433,   434,   153,   154,   155,   156,   157,
     158,   446,   447,   448,   449,   450,   451,   452,   453,    24,
     163,   164,   165,   166,   276,   377,   551,   553,   620,   621,
     622,   625,   626,   628,   629,   169,   170,   171,   276,   425,
     426,   427,   428,   429,   551,   553,     7,   633,   634,   635,
     191,   192,   193,   241,   551,   553,   681,   682,   683,   684,
     686,   687,   693,     7,   719,   720,   226,   276,   743,   744,
     745,   273,     7,   540,   541,   542,     7,   557,   558,   559,
     583,   601,   358,     8,     8,     8,   365,   367,   369,   373,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     386,     4,     4,   392,   394,   396,   398,   400,   371,     3,
       8,     8,   361,     6,     3,   459,     6,     3,   498,     6,
       3,   522,     6,     3,   488,     6,     3,     3,     6,     6,
       3,     6,   406,   408,     3,     8,   607,     6,     3,   577,
       6,     3,   435,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   623,   627,     4,     4,     4,     3,     8,
       4,     4,     4,     3,     8,   636,     6,     3,     4,   685,
       4,   688,     3,     8,     8,   721,     3,     6,     4,     3,
       8,   241,   274,   275,   543,     6,     3,   560,     6,     3,
       8,     6,     4,     4,     4,     4,   242,   244,   242,   244,
     242,   242,   242,   242,   242,   242,     4,   244,   242,     4,
       4,     4,     4,     4,     4,   363,   362,   360,   462,   458,
     501,   497,   525,   521,   276,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   303,
     304,   305,   306,   309,   311,   313,   314,   315,   318,   319,
     320,   321,   322,   324,   326,   332,   334,   375,   454,   466,
     468,   470,   472,   474,   476,   478,   479,   480,   482,   489,
     490,   517,   551,   553,   599,   487,   412,   418,     4,     4,
     404,   134,   135,   136,   137,   276,   288,   289,   290,   291,
     292,   293,   375,   517,   551,   553,   608,   609,   610,   611,
     612,   614,   616,   617,   606,   580,   576,   438,   434,   242,
     242,   242,   242,   242,   242,   447,     4,     4,   242,   242,
     242,   621,   244,   242,   242,   426,   173,   177,   178,   179,
     180,   187,   188,   276,   391,   393,   395,   551,   553,   637,
     638,   639,   642,   644,   646,   647,   648,   658,   635,   244,
       4,   242,     4,   682,   217,   219,   220,   276,   375,   551,
     553,   722,   723,   724,   725,   727,   720,   244,   744,     6,
       3,   546,   542,   563,   559,   241,   241,   241,   241,    39,
      40,    41,   387,   241,   241,   241,   397,   241,   241,     8,
       8,     8,     8,     3,     8,   241,   241,   613,   615,     4,
       4,     8,     3,     8,     8,   160,   161,   162,   624,   241,
     640,   643,   645,     4,   659,     4,   649,     3,     8,   241,
     261,   728,     4,   726,     3,     8,   241,     8,     8,   490,
       4,     4,   244,   244,   610,     4,     4,     4,   242,     4,
     244,     4,   638,     4,   242,     4,   723,   241,   241,   174,
     175,   176,   641,   241,   241,     7,     5,     5,   241,    24,
     182,   183,   184,   276,   551,   553,   660,   661,   662,   665,
     667,   669,     7,   650,   651,   652,     7,   729,   730,   663,
     666,   668,   670,     3,     8,   653,     6,     3,   731,     3,
       6,     4,     4,     4,     4,   661,   189,   276,   375,   551,
     553,   654,   655,   656,   652,   218,   221,   222,   223,   224,
     732,   733,   734,   736,   737,   738,   739,   730,   181,   664,
     241,   241,     5,   657,     3,     8,   735,     4,     4,     4,
     740,     3,     8,     7,   671,   672,   673,     4,   655,     4,
     244,   242,   242,     4,   733,   674,     6,     3,   241,   241,
     241,   185,   276,   366,   368,   370,   551,   553,   675,   676,
     677,   673,   678,     3,     8,     4,   676,   241
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
     363,   363,   363,   363,   363,   363,   363,   363,   365,   364,
     367,   366,   369,   368,   371,   370,   373,   372,   374,   376,
     375,   377,   378,   379,   380,   381,   382,   383,   384,   386,
     385,   387,   387,   387,   388,   389,   390,   392,   391,   394,
     393,   396,   395,   398,   397,   397,   397,   397,   397,   397,
     400,   399,   402,   401,   403,   403,   403,   404,   404,   406,
     405,   408,   407,   410,   409,   411,   411,   411,   412,   412,
     413,   414,   416,   415,   417,   417,   417,   418,   418,   418,
     419,   420,   422,   421,   424,   423,   425,   425,   425,   426,
     426,   426,   426,   426,   426,   427,   428,   429,   431,   430,
     432,   432,   433,   433,   433,   435,   434,   437,   436,   438,
     438,   438,   438,   439,   439,   441,   440,   443,   442,   445,
     444,   446,   446,   446,   447,   447,   447,   447,   447,   447,
     448,   449,   450,   451,   452,   453,   455,   454,   456,   456,
     457,   457,   457,   459,   458,   461,   460,   462,   462,   462,
     463,   463,   463,   463,   463,   463,   463,   463,   463,   463,
     463,   463,   463,   463,   463,   463,   463,   463,   463,   463,
     463,   463,   463,   463,   463,   463,   463,   463,   463,   463,
     463,   463,   463,   463,   463,   463,   463,   463,   463,   463,
     463,   463,   463,   463,   463,   463,   463,   463,   463,   463,
     463,   463,   465,   464,   467,   466,   469,   468,   471,   470,
     473,   472,   475,   474,   477,   476,   478,   479,   480,   481,
     482,   484,   483,   485,   485,   486,   486,   486,   488,   487,
     489,   489,   489,   490,   490,   490,   490,   490,   490,   490,
     490,   490,   490,   490,   490,   490,   490,   490,   490,   490,
     490,   490,   490,   490,   490,   490,   490,   490,   490,   490,
     490,   490,   490,   490,   490,   490,   490,   490,   490,   490,
     490,   490,   490,   490,   490,   490,   490,   490,   490,   490,
     490,   490,   492,   491,   494,   493,   495,   495,   496,   496,
     496,   498,   497,   500,   499,   501,   501,   502,   502,   502,
     503,   503,   503,   503,   503,   503,   503,   503,   503,   503,
     504,   505,   506,   508,   507,   510,   509,   512,   511,   513,
     515,   514,   516,   518,   517,   519,   519,   520,   520,   520,
     522,   521,   524,   523,   525,   525,   526,   526,   526,   527,
     527,   527,   527,   527,   527,   527,   527,   527,   527,   527,
     528,   530,   529,   531,   532,   533,   534,   535,   537,   536,
     539,   538,   540,   540,   541,   541,   541,   543,   542,   545,
     544,   546,   546,   546,   547,   547,   547,   547,   547,   547,
     547,   547,   547,   547,   547,   547,   547,   547,   547,   547,
     547,   547,   547,   547,   547,   547,   547,   547,   549,   548,
     550,   552,   551,   554,   553,   556,   555,   557,   557,   558,
     558,   558,   560,   559,   562,   561,   563,   563,   563,   564,
     564,   564,   564,   564,   564,   564,   564,   564,   564,   564,
     564,   564,   564,   566,   565,   567,   569,   568,   570,   571,
     573,   572,   574,   574,   575,   575,   575,   577,   576,   579,
     578,   580,   580,   581,   581,   581,   582,   582,   582,   582,
     582,   582,   582,   582,   582,   582,   582,   582,   584,   583,
     586,   585,   588,   587,   590,   589,   592,   591,   594,   593,
     596,   595,   598,   597,   600,   599,   601,   603,   602,   604,
     604,   605,   605,   605,   607,   606,   608,   608,   609,   609,
     609,   610,   610,   610,   610,   610,   610,   610,   610,   610,
     610,   610,   610,   610,   610,   610,   611,   613,   612,   615,
     614,   616,   617,   619,   618,   620,   620,   620,   621,   621,
     621,   621,   621,   621,   621,   621,   621,   623,   622,   624,
     624,   624,   625,   627,   626,   628,   629,   630,   632,   631,
     633,   633,   634,   634,   634,   636,   635,   637,   637,   637,
     638,   638,   638,   638,   638,   638,   638,   638,   638,   638,
     638,   638,   638,   640,   639,   641,   641,   641,   643,   642,
     645,   644,   646,   647,   649,   648,   650,   650,   651,   651,
     651,   653,   652,   654,   654,   654,   655,   655,   655,   655,
     655,   657,   656,   659,   658,   660,   660,   660,   661,   661,
     661,   661,   661,   661,   661,   663,   662,   664,   666,   665,
     668,   667,   670,   669,   671,   671,   672,   672,   672,   674,
     673,   675,   675,   675,   676,   676,   676,   676,   676,   676,
     676,   678,   677,   680,   679,   681,   681,   681,   682,   682,
     682,   682,   682,   682,   683,   685,   684,   686,   688,   687,
     690,   689,   692,   691,   693,   693,   693,   694,   694,   694,
     694,   694,   694,   694,   694,   694,   694,   694,   695,   697,
     696,   698,   700,   699,   701,   702,   704,   703,   705,   705,
     707,   706,   709,   708,   711,   710,   712,   712,   712,   713,
     713,   715,   714,   716,   718,   717,   719,   719,   719,   721,
     720,   722,   722,   722,   723,   723,   723,   723,   723,   723,
     723,   724,   726,   725,   728,   727,   729,   729,   729,   731,
     730,   732,   732,   732,   733,   733,   733,   733,   733,   735,
     734,   736,   737,   738,   740,   739,   742,   741,   743,   743,
     743,   744,   744,   745
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
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     0,
       4,     1,     1,     1,     3,     3,     3,     0,     4,     0,
       4,     0,     4,     0,     4,     1,     1,     1,     1,     1,
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     3,     3,     3,     3,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     6,     0,     4,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     0,     1,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     0,     4,     0,     4,     0,     4,     1,
       0,     4,     3,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     0,     1,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     3,     3,     3,     0,     4,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     4,     0,     4,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     0,     4,     3,     3,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     0,     1,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     1,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     0,     1,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     3,     3,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     3,     0,     4,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     0,     4,
       0,     4,     3,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     0,     4,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     0,     4,
       0,     4,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     6,     1,     3,     2,     1,     1,
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
  "password", "$@40", "password_file", "$@41", "host", "$@42", "port",
  "name", "$@43", "persist", "lfc_interval", "readonly", "connect_timeout",
  "read_timeout", "write_timeout", "tcp_user_timeout",
  "reconnect_wait_time", "on_fail", "$@44", "on_fail_mode",
  "retry_on_startup", "max_row_errors", "max_reconnect_tries",
  "trust_anchor", "$@45", "cert_file", "$@46", "key_file", "$@47",
  "ssl_mode", "$@48", "cipher_list", "$@49", "sanity_checks", "$@50",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@51",
  "extended_info_checks", "$@52", "mac_sources", "$@53",
  "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
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
  "not_empty_classes_list", "client_class_entry", "$@112",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@113",
  "client_class_template_test", "$@114", "only_if_required",
  "only_in_additional_list", "server_id", "$@115", "server_id_params",
  "server_id_param", "server_id_type", "$@116", "duid_type", "htype",
  "identifier", "$@117", "time", "enterprise_id", "dhcp4o6_port",
  "control_sockets", "$@118", "control_socket_list",
  "not_empty_control_socket_list", "control_socket_entry", "$@119",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@120", "control_socket_type_value", "control_socket_name", "$@121",
  "control_socket_address", "$@122", "control_socket_port",
  "cert_required", "http_headers", "$@123", "http_header_list",
  "not_empty_http_header_list", "http_header", "$@124",
  "http_header_params", "http_header_param", "header_value", "$@125",
  "authentication", "$@126", "auth_params", "auth_param", "auth_type",
  "$@127", "auth_type_value", "realm", "$@128", "directory", "$@129",
  "clients", "$@130", "clients_list", "not_empty_clients_list",
  "basic_auth", "$@131", "clients_params", "clients_param", "user_file",
  "$@132", "dhcp_queue_control", "$@133", "queue_control_params",
  "queue_control_param", "enable_queue", "queue_type", "$@134", "capacity",
  "arbitrary_map_entry", "$@135", "dhcp_ddns", "$@136", "sub_dhcp_ddns",
  "$@137", "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "server_ip", "$@138", "server_port", "sender_ip", "$@139", "sender_port",
  "max_queue_size", "ncr_protocol", "$@140", "ncr_protocol_value",
  "ncr_format", "$@141", "config_control", "$@142", "sub_config_control",
  "$@143", "config_control_params", "config_control_param",
  "config_databases", "$@144", "config_fetch_wait_time", "loggers",
  "$@145", "loggers_entries", "logger_entry", "$@146", "logger_params",
  "logger_param", "debuglevel", "severity", "$@147", "output_options_list",
  "$@148", "output_options_list_content", "output_entry", "$@149",
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
    1080,  1081,  1082,  1083,  1084,  1085,  1086,  1087,  1090,  1090,
    1099,  1099,  1108,  1108,  1117,  1117,  1126,  1126,  1135,  1141,
    1141,  1150,  1156,  1162,  1168,  1174,  1180,  1186,  1192,  1198,
    1198,  1206,  1207,  1208,  1211,  1217,  1223,  1229,  1229,  1238,
    1238,  1247,  1247,  1256,  1256,  1264,  1267,  1270,  1273,  1276,
    1281,  1281,  1290,  1290,  1301,  1302,  1303,  1308,  1309,  1312,
    1312,  1331,  1331,  1349,  1349,  1360,  1361,  1362,  1367,  1368,
    1371,  1376,  1381,  1381,  1392,  1393,  1394,  1399,  1400,  1401,
    1404,  1409,  1416,  1416,  1429,  1429,  1442,  1443,  1444,  1449,
    1450,  1451,  1452,  1453,  1454,  1457,  1463,  1469,  1475,  1475,
    1486,  1487,  1490,  1491,  1492,  1497,  1497,  1507,  1507,  1517,
    1518,  1519,  1522,  1525,  1526,  1529,  1529,  1538,  1538,  1547,
    1547,  1559,  1560,  1561,  1566,  1567,  1568,  1569,  1570,  1571,
    1574,  1580,  1586,  1592,  1598,  1604,  1613,  1613,  1627,  1628,
    1631,  1632,  1633,  1642,  1642,  1668,  1668,  1679,  1680,  1681,
    1687,  1688,  1689,  1690,  1691,  1692,  1693,  1694,  1695,  1696,
    1697,  1698,  1699,  1700,  1701,  1702,  1703,  1704,  1705,  1706,
    1707,  1708,  1709,  1710,  1711,  1712,  1713,  1714,  1715,  1716,
    1717,  1718,  1719,  1720,  1721,  1722,  1723,  1724,  1725,  1726,
    1727,  1728,  1729,  1730,  1731,  1732,  1733,  1734,  1735,  1736,
    1737,  1738,  1741,  1741,  1750,  1750,  1759,  1759,  1768,  1768,
    1778,  1778,  1790,  1790,  1801,  1801,  1812,  1818,  1824,  1830,
    1836,  1844,  1844,  1856,  1857,  1861,  1862,  1863,  1868,  1868,
    1876,  1877,  1878,  1883,  1884,  1885,  1886,  1887,  1888,  1889,
    1890,  1891,  1892,  1893,  1894,  1895,  1896,  1897,  1898,  1899,
    1900,  1901,  1902,  1903,  1904,  1905,  1906,  1907,  1908,  1909,
    1910,  1911,  1912,  1913,  1914,  1915,  1916,  1917,  1918,  1919,
    1920,  1921,  1922,  1923,  1924,  1925,  1926,  1927,  1928,  1929,
    1930,  1931,  1938,  1938,  1952,  1952,  1961,  1962,  1965,  1966,
    1967,  1974,  1974,  1989,  1989,  2003,  2004,  2007,  2008,  2009,
    2014,  2015,  2016,  2017,  2018,  2019,  2020,  2021,  2022,  2023,
    2026,  2028,  2034,  2036,  2036,  2045,  2045,  2054,  2054,  2063,
    2065,  2065,  2074,  2084,  2084,  2097,  2098,  2103,  2104,  2105,
    2112,  2112,  2124,  2124,  2136,  2137,  2142,  2143,  2144,  2151,
    2152,  2153,  2154,  2155,  2156,  2157,  2158,  2159,  2160,  2161,
    2164,  2166,  2166,  2175,  2177,  2179,  2185,  2191,  2197,  2197,
    2211,  2211,  2224,  2225,  2228,  2229,  2230,  2235,  2235,  2245,
    2245,  2255,  2256,  2257,  2262,  2263,  2264,  2265,  2266,  2267,
    2268,  2269,  2270,  2271,  2272,  2273,  2274,  2275,  2276,  2277,
    2278,  2279,  2280,  2281,  2282,  2283,  2284,  2285,  2288,  2288,
    2297,  2303,  2303,  2328,  2328,  2358,  2358,  2371,  2372,  2375,
    2376,  2377,  2382,  2382,  2394,  2394,  2406,  2407,  2408,  2413,
    2414,  2415,  2416,  2417,  2418,  2419,  2420,  2421,  2422,  2423,
    2424,  2425,  2426,  2429,  2429,  2438,  2444,  2444,  2453,  2459,
    2468,  2468,  2479,  2480,  2483,  2484,  2485,  2490,  2490,  2499,
    2499,  2508,  2509,  2512,  2513,  2514,  2520,  2521,  2522,  2523,
    2524,  2525,  2526,  2527,  2528,  2529,  2530,  2531,  2534,  2534,
    2545,  2545,  2556,  2556,  2567,  2567,  2576,  2576,  2585,  2585,
    2594,  2594,  2603,  2603,  2617,  2617,  2628,  2634,  2634,  2645,
    2646,  2649,  2650,  2651,  2656,  2656,  2666,  2667,  2670,  2671,
    2672,  2677,  2678,  2679,  2680,  2681,  2682,  2683,  2684,  2685,
    2686,  2687,  2688,  2689,  2690,  2691,  2694,  2696,  2696,  2705,
    2705,  2715,  2721,  2730,  2730,  2743,  2744,  2745,  2750,  2751,
    2752,  2753,  2754,  2755,  2756,  2757,  2758,  2761,  2761,  2769,
    2770,  2771,  2774,  2780,  2780,  2789,  2795,  2803,  2811,  2811,
    2822,  2823,  2826,  2827,  2828,  2833,  2833,  2841,  2842,  2843,
    2848,  2849,  2850,  2851,  2852,  2853,  2854,  2855,  2856,  2857,
    2858,  2859,  2860,  2863,  2863,  2872,  2873,  2874,  2877,  2877,
    2886,  2886,  2895,  2901,  2907,  2907,  2918,  2919,  2922,  2923,
    2924,  2929,  2929,  2937,  2938,  2939,  2944,  2945,  2946,  2947,
    2948,  2951,  2951,  2962,  2962,  2975,  2976,  2977,  2982,  2983,
    2984,  2985,  2986,  2987,  2988,  2991,  2991,  2999,  3002,  3002,
    3011,  3011,  3020,  3020,  3031,  3032,  3035,  3036,  3037,  3042,
    3042,  3050,  3051,  3052,  3057,  3058,  3059,  3060,  3061,  3062,
    3063,  3066,  3066,  3077,  3077,  3090,  3091,  3092,  3097,  3098,
    3099,  3100,  3101,  3102,  3105,  3111,  3111,  3120,  3126,  3126,
    3136,  3136,  3149,  3149,  3159,  3160,  3161,  3166,  3167,  3168,
    3169,  3170,  3171,  3172,  3173,  3174,  3175,  3176,  3179,  3185,
    3185,  3194,  3200,  3200,  3209,  3215,  3221,  3221,  3230,  3231,
    3234,  3234,  3245,  3245,  3257,  3257,  3267,  3268,  3269,  3275,
    3276,  3279,  3279,  3290,  3298,  3298,  3311,  3312,  3313,  3319,
    3319,  3327,  3328,  3329,  3334,  3335,  3336,  3337,  3338,  3339,
    3340,  3343,  3349,  3349,  3358,  3358,  3369,  3370,  3371,  3376,
    3376,  3384,  3385,  3386,  3391,  3392,  3393,  3394,  3395,  3398,
    3398,  3407,  3413,  3419,  3425,  3425,  3434,  3434,  3445,  3446,
    3447,  3452,  3453,  3456
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
#line 7162 "dhcp6_parser.cc"

#line 3462 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
