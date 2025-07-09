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
#line 330 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 417 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 330 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 423 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 330 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 429 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 330 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 435 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 330 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 441 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 330 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 447 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 330 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 453 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 330 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 459 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 330 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 465 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ssl_mode: // ssl_mode
#line 330 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 471 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 330 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 477 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
#line 330 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 483 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 330 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 489 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 330 "dhcp6_parser.yy"
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
#line 339 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 777 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 340 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 783 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 341 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 789 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 342 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 795 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 343 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 801 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 344 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 807 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 345 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 813 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 346 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 819 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 347 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 825 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 348 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 831 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 349 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 837 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 350 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 843 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 351 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 849 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 352 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 855 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 360 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 861 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 361 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 867 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 362 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 873 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 363 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 879 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 364 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 885 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 365 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 891 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 366 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 897 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 369 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 906 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 374 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 917 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 379 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 927 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 385 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 933 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 392 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 943 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 397 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 954 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 403 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 962 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 408 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 971 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 411 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 979 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 419 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 988 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 423 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 997 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 427 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 1005 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 433 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 1013 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 435 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1022 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 444 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1031 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 448 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1040 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 452 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1048 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 462 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1059 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 471 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1070 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 476 "dhcp6_parser.yy"
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
#line 486 "dhcp6_parser.yy"
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
#line 495 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1108 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 503 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1116 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 509 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1126 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 513 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1135 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 520 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1143 "dhcp6_parser.cc"
    break;

  case 144: // $@21: %empty
#line 601 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1152 "dhcp6_parser.cc"
    break;

  case 145: // data_directory: "data-directory" $@21 ":" "constant string"
#line 604 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.warning(yystack_[2].location, "data-directory is deprecated and will be ignored");
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1163 "dhcp6_parser.cc"
    break;

  case 146: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 611 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1173 "dhcp6_parser.cc"
    break;

  case 147: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 617 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1183 "dhcp6_parser.cc"
    break;

  case 148: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 623 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1193 "dhcp6_parser.cc"
    break;

  case 149: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 629 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1203 "dhcp6_parser.cc"
    break;

  case 150: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 635 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1213 "dhcp6_parser.cc"
    break;

  case 151: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 641 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1223 "dhcp6_parser.cc"
    break;

  case 152: // renew_timer: "renew-timer" ":" "integer"
#line 647 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1233 "dhcp6_parser.cc"
    break;

  case 153: // rebind_timer: "rebind-timer" ":" "integer"
#line 653 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1243 "dhcp6_parser.cc"
    break;

  case 154: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 659 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1253 "dhcp6_parser.cc"
    break;

  case 155: // t1_percent: "t1-percent" ":" "floating point"
#line 665 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1263 "dhcp6_parser.cc"
    break;

  case 156: // t2_percent: "t2-percent" ":" "floating point"
#line 671 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1273 "dhcp6_parser.cc"
    break;

  case 157: // cache_threshold: "cache-threshold" ":" "floating point"
#line 677 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1283 "dhcp6_parser.cc"
    break;

  case 158: // cache_max_age: "cache-max-age" ":" "integer"
#line 683 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1293 "dhcp6_parser.cc"
    break;

  case 159: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 689 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1303 "dhcp6_parser.cc"
    break;

  case 160: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 695 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1313 "dhcp6_parser.cc"
    break;

  case 161: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 701 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1323 "dhcp6_parser.cc"
    break;

  case 162: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 707 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1333 "dhcp6_parser.cc"
    break;

  case 163: // $@22: %empty
#line 713 "dhcp6_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1342 "dhcp6_parser.cc"
    break;

  case 164: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 716 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1351 "dhcp6_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "when-present"
#line 722 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1359 "dhcp6_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "never"
#line 725 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1367 "dhcp6_parser.cc"
    break;

  case 167: // ddns_replace_client_name_value: "always"
#line 728 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1375 "dhcp6_parser.cc"
    break;

  case 168: // ddns_replace_client_name_value: "when-not-present"
#line 731 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1383 "dhcp6_parser.cc"
    break;

  case 169: // ddns_replace_client_name_value: "boolean"
#line 734 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1392 "dhcp6_parser.cc"
    break;

  case 170: // $@23: %empty
#line 740 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1401 "dhcp6_parser.cc"
    break;

  case 171: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 743 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1411 "dhcp6_parser.cc"
    break;

  case 172: // $@24: %empty
#line 749 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1420 "dhcp6_parser.cc"
    break;

  case 173: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 752 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1430 "dhcp6_parser.cc"
    break;

  case 174: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 758 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1440 "dhcp6_parser.cc"
    break;

  case 175: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 767 "dhcp6_parser.yy"
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
#line 777 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1463 "dhcp6_parser.cc"
    break;

  case 177: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 780 "dhcp6_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1472 "dhcp6_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 786 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1480 "dhcp6_parser.cc"
    break;

  case 179: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 789 "dhcp6_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1488 "dhcp6_parser.cc"
    break;

  case 180: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 792 "dhcp6_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1496 "dhcp6_parser.cc"
    break;

  case 181: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 795 "dhcp6_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1504 "dhcp6_parser.cc"
    break;

  case 182: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 800 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1514 "dhcp6_parser.cc"
    break;

  case 183: // ddns_ttl: "ddns-ttl" ":" "integer"
#line 806 "dhcp6_parser.yy"
                                 {
    ctx.unique("ddns-ttl", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl", ttl);
}
#line 1524 "dhcp6_parser.cc"
    break;

  case 184: // ddns_ttl_min: "ddns-ttl-min" ":" "integer"
#line 812 "dhcp6_parser.yy"
                                         {
    ctx.unique("ddns-ttl-min", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-min", ttl);
}
#line 1534 "dhcp6_parser.cc"
    break;

  case 185: // ddns_ttl_max: "ddns-ttl-mix" ":" "integer"
#line 818 "dhcp6_parser.yy"
                                         {
    ctx.unique("ddns-ttl-max", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-max", ttl);
}
#line 1544 "dhcp6_parser.cc"
    break;

  case 186: // $@26: %empty
#line 824 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1553 "dhcp6_parser.cc"
    break;

  case 187: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 827 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1563 "dhcp6_parser.cc"
    break;

  case 188: // $@27: %empty
#line 833 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1572 "dhcp6_parser.cc"
    break;

  case 189: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 836 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1582 "dhcp6_parser.cc"
    break;

  case 190: // store_extended_info: "store-extended-info" ":" "boolean"
#line 842 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1592 "dhcp6_parser.cc"
    break;

  case 191: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 848 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1602 "dhcp6_parser.cc"
    break;

  case 192: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 854 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1612 "dhcp6_parser.cc"
    break;

  case 193: // $@28: %empty
#line 860 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1621 "dhcp6_parser.cc"
    break;

  case 194: // server_tag: "server-tag" $@28 ":" "constant string"
#line 863 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1631 "dhcp6_parser.cc"
    break;

  case 195: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 869 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1641 "dhcp6_parser.cc"
    break;

  case 196: // $@29: %empty
#line 875 "dhcp6_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1650 "dhcp6_parser.cc"
    break;

  case 197: // allocator: "allocator" $@29 ":" "constant string"
#line 878 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1660 "dhcp6_parser.cc"
    break;

  case 198: // $@30: %empty
#line 884 "dhcp6_parser.yy"
                           {
    ctx.unique("pd-allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1669 "dhcp6_parser.cc"
    break;

  case 199: // pd_allocator: "pd-allocator" $@30 ":" "constant string"
#line 887 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-allocator", al);
    ctx.leave();
}
#line 1679 "dhcp6_parser.cc"
    break;

  case 200: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 893 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1689 "dhcp6_parser.cc"
    break;

  case 201: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 899 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1699 "dhcp6_parser.cc"
    break;

  case 202: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 905 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1709 "dhcp6_parser.cc"
    break;

  case 203: // $@31: %empty
#line 911 "dhcp6_parser.yy"
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
#line 917 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1731 "dhcp6_parser.cc"
    break;

  case 205: // $@32: %empty
#line 923 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1741 "dhcp6_parser.cc"
    break;

  case 206: // sub_interfaces6: "{" $@32 interfaces_config_params "}"
#line 927 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1750 "dhcp6_parser.cc"
    break;

  case 209: // interfaces_config_params: interfaces_config_params ","
#line 934 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1758 "dhcp6_parser.cc"
    break;

  case 218: // $@33: %empty
#line 949 "dhcp6_parser.yy"
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
#line 955 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1779 "dhcp6_parser.cc"
    break;

  case 220: // re_detect: "re-detect" ":" "boolean"
#line 960 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1789 "dhcp6_parser.cc"
    break;

  case 221: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 966 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1799 "dhcp6_parser.cc"
    break;

  case 222: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 972 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1809 "dhcp6_parser.cc"
    break;

  case 223: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 978 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1819 "dhcp6_parser.cc"
    break;

  case 224: // $@34: %empty
#line 984 "dhcp6_parser.yy"
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
#line 990 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1842 "dhcp6_parser.cc"
    break;

  case 226: // $@35: %empty
#line 997 "dhcp6_parser.yy"
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
#line 1003 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1865 "dhcp6_parser.cc"
    break;

  case 228: // $@36: %empty
#line 1010 "dhcp6_parser.yy"
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
#line 1016 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1886 "dhcp6_parser.cc"
    break;

  case 234: // not_empty_database_list: not_empty_database_list ","
#line 1027 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1894 "dhcp6_parser.cc"
    break;

  case 235: // $@37: %empty
#line 1032 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1904 "dhcp6_parser.cc"
    break;

  case 236: // database: "{" $@37 database_map_params "}"
#line 1036 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1914 "dhcp6_parser.cc"
    break;

  case 239: // database_map_params: database_map_params ","
#line 1044 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1922 "dhcp6_parser.cc"
    break;

  case 264: // $@38: %empty
#line 1075 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1931 "dhcp6_parser.cc"
    break;

  case 265: // database_type: "type" $@38 ":" "constant string"
#line 1078 "dhcp6_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 1941 "dhcp6_parser.cc"
    break;

  case 266: // $@39: %empty
#line 1084 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1950 "dhcp6_parser.cc"
    break;

  case 267: // user: "user" $@39 ":" "constant string"
#line 1087 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1960 "dhcp6_parser.cc"
    break;

  case 268: // $@40: %empty
#line 1093 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1969 "dhcp6_parser.cc"
    break;

  case 269: // password: "password" $@40 ":" "constant string"
#line 1096 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1979 "dhcp6_parser.cc"
    break;

  case 270: // $@41: %empty
#line 1102 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1988 "dhcp6_parser.cc"
    break;

  case 271: // host: "host" $@41 ":" "constant string"
#line 1105 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1998 "dhcp6_parser.cc"
    break;

  case 272: // port: "port" ":" "integer"
#line 1111 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2008 "dhcp6_parser.cc"
    break;

  case 273: // $@42: %empty
#line 1117 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2017 "dhcp6_parser.cc"
    break;

  case 274: // name: "name" $@42 ":" "constant string"
#line 1120 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2027 "dhcp6_parser.cc"
    break;

  case 275: // persist: "persist" ":" "boolean"
#line 1126 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2037 "dhcp6_parser.cc"
    break;

  case 276: // lfc_interval: "lfc-interval" ":" "integer"
#line 1132 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2047 "dhcp6_parser.cc"
    break;

  case 277: // readonly: "readonly" ":" "boolean"
#line 1138 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2057 "dhcp6_parser.cc"
    break;

  case 278: // connect_timeout: "connect-timeout" ":" "integer"
#line 1144 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2067 "dhcp6_parser.cc"
    break;

  case 279: // read_timeout: "read-timeout" ":" "integer"
#line 1150 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2077 "dhcp6_parser.cc"
    break;

  case 280: // write_timeout: "write-timeout" ":" "integer"
#line 1156 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2087 "dhcp6_parser.cc"
    break;

  case 281: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1162 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2097 "dhcp6_parser.cc"
    break;

  case 282: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1168 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2107 "dhcp6_parser.cc"
    break;

  case 283: // $@43: %empty
#line 1174 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2116 "dhcp6_parser.cc"
    break;

  case 284: // on_fail: "on-fail" $@43 ":" on_fail_mode
#line 1177 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2125 "dhcp6_parser.cc"
    break;

  case 285: // on_fail_mode: "stop-retry-exit"
#line 1182 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2131 "dhcp6_parser.cc"
    break;

  case 286: // on_fail_mode: "serve-retry-exit"
#line 1183 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2137 "dhcp6_parser.cc"
    break;

  case 287: // on_fail_mode: "serve-retry-continue"
#line 1184 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2143 "dhcp6_parser.cc"
    break;

  case 288: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1187 "dhcp6_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2153 "dhcp6_parser.cc"
    break;

  case 289: // max_row_errors: "max-row-errors" ":" "integer"
#line 1193 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2163 "dhcp6_parser.cc"
    break;

  case 290: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1199 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2173 "dhcp6_parser.cc"
    break;

  case 291: // $@44: %empty
#line 1205 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2182 "dhcp6_parser.cc"
    break;

  case 292: // trust_anchor: "trust-anchor" $@44 ":" "constant string"
#line 1208 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2192 "dhcp6_parser.cc"
    break;

  case 293: // $@45: %empty
#line 1214 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2201 "dhcp6_parser.cc"
    break;

  case 294: // cert_file: "cert-file" $@45 ":" "constant string"
#line 1217 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2211 "dhcp6_parser.cc"
    break;

  case 295: // $@46: %empty
#line 1223 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2220 "dhcp6_parser.cc"
    break;

  case 296: // key_file: "key-file" $@46 ":" "constant string"
#line 1226 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2230 "dhcp6_parser.cc"
    break;

  case 297: // $@47: %empty
#line 1232 "dhcp6_parser.yy"
                   {
    ctx.unique("ssl-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SSL_MODE);
}
#line 2239 "dhcp6_parser.cc"
    break;

  case 298: // ssl_mode: "ssl-mode" $@47 ":" ssl_mode
#line 1235 "dhcp6_parser.yy"
                 {
    ctx.stack_.back()->set("ssl-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2248 "dhcp6_parser.cc"
    break;

  case 299: // ssl_mode: "disable"
#line 1240 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disable", ctx.loc2pos(yystack_[0].location))); }
#line 2254 "dhcp6_parser.cc"
    break;

  case 300: // ssl_mode: "prefer"
#line 1241 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("prefer", ctx.loc2pos(yystack_[0].location))); }
#line 2260 "dhcp6_parser.cc"
    break;

  case 301: // ssl_mode: "require"
#line 1242 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("require", ctx.loc2pos(yystack_[0].location))); }
#line 2266 "dhcp6_parser.cc"
    break;

  case 302: // ssl_mode: "verify-ca"
#line 1243 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-ca", ctx.loc2pos(yystack_[0].location))); }
#line 2272 "dhcp6_parser.cc"
    break;

  case 303: // ssl_mode: "verify-full"
#line 1244 "dhcp6_parser.yy"
                      { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-full", ctx.loc2pos(yystack_[0].location))); }
#line 2278 "dhcp6_parser.cc"
    break;

  case 304: // $@48: %empty
#line 1247 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2287 "dhcp6_parser.cc"
    break;

  case 305: // cipher_list: "cipher-list" $@48 ":" "constant string"
#line 1250 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2297 "dhcp6_parser.cc"
    break;

  case 306: // $@49: %empty
#line 1256 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2309 "dhcp6_parser.cc"
    break;

  case 307: // sanity_checks: "sanity-checks" $@49 ":" "{" sanity_checks_params "}"
#line 1262 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2318 "dhcp6_parser.cc"
    break;

  case 310: // sanity_checks_params: sanity_checks_params ","
#line 1269 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2326 "dhcp6_parser.cc"
    break;

  case 313: // $@50: %empty
#line 1278 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2335 "dhcp6_parser.cc"
    break;

  case 314: // lease_checks: "lease-checks" $@50 ":" "constant string"
#line 1281 "dhcp6_parser.yy"
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
#line 2355 "dhcp6_parser.cc"
    break;

  case 315: // $@51: %empty
#line 1297 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2364 "dhcp6_parser.cc"
    break;

  case 316: // extended_info_checks: "extended-info-checks" $@51 ":" "constant string"
#line 1300 "dhcp6_parser.yy"
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
#line 2383 "dhcp6_parser.cc"
    break;

  case 317: // $@52: %empty
#line 1315 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2395 "dhcp6_parser.cc"
    break;

  case 318: // mac_sources: "mac-sources" $@52 ":" "[" mac_sources_list "]"
#line 1321 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2404 "dhcp6_parser.cc"
    break;

  case 321: // mac_sources_list: mac_sources_list ","
#line 1328 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2412 "dhcp6_parser.cc"
    break;

  case 324: // duid_id: "duid"
#line 1337 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2421 "dhcp6_parser.cc"
    break;

  case 325: // string_id: "constant string"
#line 1342 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2430 "dhcp6_parser.cc"
    break;

  case 326: // $@53: %empty
#line 1347 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2442 "dhcp6_parser.cc"
    break;

  case 327: // host_reservation_identifiers: "host-reservation-identifiers" $@53 ":" "[" host_reservation_identifiers_list "]"
#line 1353 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2451 "dhcp6_parser.cc"
    break;

  case 330: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1360 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2459 "dhcp6_parser.cc"
    break;

  case 334: // hw_address_id: "hw-address"
#line 1370 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2468 "dhcp6_parser.cc"
    break;

  case 335: // flex_id: "flex-id"
#line 1375 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2477 "dhcp6_parser.cc"
    break;

  case 336: // $@54: %empty
#line 1382 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2489 "dhcp6_parser.cc"
    break;

  case 337: // relay_supplied_options: "relay-supplied-options" $@54 ":" "[" list_content "]"
#line 1388 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2498 "dhcp6_parser.cc"
    break;

  case 338: // $@55: %empty
#line 1395 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2510 "dhcp6_parser.cc"
    break;

  case 339: // dhcp_multi_threading: "multi-threading" $@55 ":" "{" multi_threading_params "}"
#line 1401 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2521 "dhcp6_parser.cc"
    break;

  case 342: // multi_threading_params: multi_threading_params ","
#line 1410 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2529 "dhcp6_parser.cc"
    break;

  case 349: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1423 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2539 "dhcp6_parser.cc"
    break;

  case 350: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1429 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2549 "dhcp6_parser.cc"
    break;

  case 351: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1435 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2559 "dhcp6_parser.cc"
    break;

  case 352: // $@56: %empty
#line 1441 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2571 "dhcp6_parser.cc"
    break;

  case 353: // hooks_libraries: "hooks-libraries" $@56 ":" "[" hooks_libraries_list "]"
#line 1447 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2580 "dhcp6_parser.cc"
    break;

  case 358: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1458 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2588 "dhcp6_parser.cc"
    break;

  case 359: // $@57: %empty
#line 1463 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2598 "dhcp6_parser.cc"
    break;

  case 360: // hooks_library: "{" $@57 hooks_params "}"
#line 1467 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2608 "dhcp6_parser.cc"
    break;

  case 361: // $@58: %empty
#line 1473 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2618 "dhcp6_parser.cc"
    break;

  case 362: // sub_hooks_library: "{" $@58 hooks_params "}"
#line 1477 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2628 "dhcp6_parser.cc"
    break;

  case 365: // hooks_params: hooks_params ","
#line 1485 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2636 "dhcp6_parser.cc"
    break;

  case 369: // $@59: %empty
#line 1495 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2645 "dhcp6_parser.cc"
    break;

  case 370: // library: "library" $@59 ":" "constant string"
#line 1498 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2655 "dhcp6_parser.cc"
    break;

  case 371: // $@60: %empty
#line 1504 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2664 "dhcp6_parser.cc"
    break;

  case 372: // parameters: "parameters" $@60 ":" map_value
#line 1507 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2673 "dhcp6_parser.cc"
    break;

  case 373: // $@61: %empty
#line 1513 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2685 "dhcp6_parser.cc"
    break;

  case 374: // expired_leases_processing: "expired-leases-processing" $@61 ":" "{" expired_leases_params "}"
#line 1519 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2695 "dhcp6_parser.cc"
    break;

  case 377: // expired_leases_params: expired_leases_params ","
#line 1527 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2703 "dhcp6_parser.cc"
    break;

  case 384: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1540 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2713 "dhcp6_parser.cc"
    break;

  case 385: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1546 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2723 "dhcp6_parser.cc"
    break;

  case 386: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1552 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2733 "dhcp6_parser.cc"
    break;

  case 387: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1558 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2743 "dhcp6_parser.cc"
    break;

  case 388: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1564 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2753 "dhcp6_parser.cc"
    break;

  case 389: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1570 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2763 "dhcp6_parser.cc"
    break;

  case 390: // $@62: %empty
#line 1579 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2775 "dhcp6_parser.cc"
    break;

  case 391: // subnet6_list: "subnet6" $@62 ":" "[" subnet6_list_content "]"
#line 1585 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2784 "dhcp6_parser.cc"
    break;

  case 396: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1599 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2792 "dhcp6_parser.cc"
    break;

  case 397: // $@63: %empty
#line 1608 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2802 "dhcp6_parser.cc"
    break;

  case 398: // subnet6: "{" $@63 subnet6_params "}"
#line 1612 "dhcp6_parser.yy"
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
#line 2828 "dhcp6_parser.cc"
    break;

  case 399: // $@64: %empty
#line 1634 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2838 "dhcp6_parser.cc"
    break;

  case 400: // sub_subnet6: "{" $@64 subnet6_params "}"
#line 1638 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2848 "dhcp6_parser.cc"
    break;

  case 403: // subnet6_params: subnet6_params ","
#line 1647 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2856 "dhcp6_parser.cc"
    break;

  case 455: // $@65: %empty
#line 1706 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2865 "dhcp6_parser.cc"
    break;

  case 456: // subnet: "subnet" $@65 ":" "constant string"
#line 1709 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2875 "dhcp6_parser.cc"
    break;

  case 457: // $@66: %empty
#line 1715 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2884 "dhcp6_parser.cc"
    break;

  case 458: // interface: "interface" $@66 ":" "constant string"
#line 1718 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2894 "dhcp6_parser.cc"
    break;

  case 459: // $@67: %empty
#line 1724 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2903 "dhcp6_parser.cc"
    break;

  case 460: // interface_id: "interface-id" $@67 ":" "constant string"
#line 1727 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2913 "dhcp6_parser.cc"
    break;

  case 461: // $@68: %empty
#line 1733 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2922 "dhcp6_parser.cc"
    break;

  case 462: // client_class: "client-class" $@68 ":" "constant string"
#line 1736 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2932 "dhcp6_parser.cc"
    break;

  case 463: // $@69: %empty
#line 1743 "dhcp6_parser.yy"
                                       {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2944 "dhcp6_parser.cc"
    break;

  case 464: // network_client_classes: "client-classes" $@69 ":" list_strings
#line 1749 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2953 "dhcp6_parser.cc"
    break;

  case 465: // $@70: %empty
#line 1755 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2965 "dhcp6_parser.cc"
    break;

  case 466: // require_client_classes: "require-client-classes" $@70 ":" list_strings
#line 1761 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2974 "dhcp6_parser.cc"
    break;

  case 467: // $@71: %empty
#line 1766 "dhcp6_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2986 "dhcp6_parser.cc"
    break;

  case 468: // evaluate_additional_classes: "evaluate-additional-classes" $@71 ":" list_strings
#line 1772 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2995 "dhcp6_parser.cc"
    break;

  case 469: // reservations_global: "reservations-global" ":" "boolean"
#line 1777 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 3005 "dhcp6_parser.cc"
    break;

  case 470: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1783 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 3015 "dhcp6_parser.cc"
    break;

  case 471: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1789 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 3025 "dhcp6_parser.cc"
    break;

  case 472: // id: "id" ":" "integer"
#line 1795 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 3035 "dhcp6_parser.cc"
    break;

  case 473: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1801 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 3045 "dhcp6_parser.cc"
    break;

  case 474: // $@72: %empty
#line 1809 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3057 "dhcp6_parser.cc"
    break;

  case 475: // shared_networks: "shared-networks" $@72 ":" "[" shared_networks_content "]"
#line 1815 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3066 "dhcp6_parser.cc"
    break;

  case 480: // shared_networks_list: shared_networks_list ","
#line 1828 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3074 "dhcp6_parser.cc"
    break;

  case 481: // $@73: %empty
#line 1833 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3084 "dhcp6_parser.cc"
    break;

  case 482: // shared_network: "{" $@73 shared_network_params "}"
#line 1837 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3092 "dhcp6_parser.cc"
    break;

  case 485: // shared_network_params: shared_network_params ","
#line 1843 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3100 "dhcp6_parser.cc"
    break;

  case 534: // $@74: %empty
#line 1902 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3112 "dhcp6_parser.cc"
    break;

  case 535: // option_def_list: "option-def" $@74 ":" "[" option_def_list_content "]"
#line 1908 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3121 "dhcp6_parser.cc"
    break;

  case 536: // $@75: %empty
#line 1916 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3130 "dhcp6_parser.cc"
    break;

  case 537: // sub_option_def_list: "{" $@75 option_def_list "}"
#line 1919 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 3138 "dhcp6_parser.cc"
    break;

  case 542: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1931 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3146 "dhcp6_parser.cc"
    break;

  case 543: // $@76: %empty
#line 1938 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3156 "dhcp6_parser.cc"
    break;

  case 544: // option_def_entry: "{" $@76 option_def_params "}"
#line 1942 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3168 "dhcp6_parser.cc"
    break;

  case 545: // $@77: %empty
#line 1953 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3178 "dhcp6_parser.cc"
    break;

  case 546: // sub_option_def: "{" $@77 option_def_params "}"
#line 1957 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3190 "dhcp6_parser.cc"
    break;

  case 551: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1973 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3198 "dhcp6_parser.cc"
    break;

  case 563: // code: "code" ":" "integer"
#line 1992 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3208 "dhcp6_parser.cc"
    break;

  case 565: // $@78: %empty
#line 2000 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3217 "dhcp6_parser.cc"
    break;

  case 566: // option_def_type: "type" $@78 ":" "constant string"
#line 2003 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3227 "dhcp6_parser.cc"
    break;

  case 567: // $@79: %empty
#line 2009 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3236 "dhcp6_parser.cc"
    break;

  case 568: // option_def_record_types: "record-types" $@79 ":" "constant string"
#line 2012 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3246 "dhcp6_parser.cc"
    break;

  case 569: // $@80: %empty
#line 2018 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3255 "dhcp6_parser.cc"
    break;

  case 570: // space: "space" $@80 ":" "constant string"
#line 2021 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3265 "dhcp6_parser.cc"
    break;

  case 572: // $@81: %empty
#line 2029 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3274 "dhcp6_parser.cc"
    break;

  case 573: // option_def_encapsulate: "encapsulate" $@81 ":" "constant string"
#line 2032 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3284 "dhcp6_parser.cc"
    break;

  case 574: // option_def_array: "array" ":" "boolean"
#line 2038 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3294 "dhcp6_parser.cc"
    break;

  case 575: // $@82: %empty
#line 2048 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3306 "dhcp6_parser.cc"
    break;

  case 576: // option_data_list: "option-data" $@82 ":" "[" option_data_list_content "]"
#line 2054 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3315 "dhcp6_parser.cc"
    break;

  case 581: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2069 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3323 "dhcp6_parser.cc"
    break;

  case 582: // $@83: %empty
#line 2076 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3333 "dhcp6_parser.cc"
    break;

  case 583: // option_data_entry: "{" $@83 option_data_params "}"
#line 2080 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3342 "dhcp6_parser.cc"
    break;

  case 584: // $@84: %empty
#line 2088 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3352 "dhcp6_parser.cc"
    break;

  case 585: // sub_option_data: "{" $@84 option_data_params "}"
#line 2092 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3361 "dhcp6_parser.cc"
    break;

  case 590: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2108 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3369 "dhcp6_parser.cc"
    break;

  case 603: // $@85: %empty
#line 2130 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3378 "dhcp6_parser.cc"
    break;

  case 604: // option_data_data: "data" $@85 ":" "constant string"
#line 2133 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3388 "dhcp6_parser.cc"
    break;

  case 607: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2143 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3398 "dhcp6_parser.cc"
    break;

  case 608: // option_data_always_send: "always-send" ":" "boolean"
#line 2149 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3408 "dhcp6_parser.cc"
    break;

  case 609: // option_data_never_send: "never-send" ":" "boolean"
#line 2155 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3418 "dhcp6_parser.cc"
    break;

  case 610: // $@86: %empty
#line 2161 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3430 "dhcp6_parser.cc"
    break;

  case 611: // option_data_client_classes: "client-classes" $@86 ":" list_strings
#line 2167 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3439 "dhcp6_parser.cc"
    break;

  case 612: // $@87: %empty
#line 2175 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3451 "dhcp6_parser.cc"
    break;

  case 613: // pools_list: "pools" $@87 ":" "[" pools_list_content "]"
#line 2181 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3460 "dhcp6_parser.cc"
    break;

  case 618: // not_empty_pools_list: not_empty_pools_list ","
#line 2194 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3468 "dhcp6_parser.cc"
    break;

  case 619: // $@88: %empty
#line 2199 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3478 "dhcp6_parser.cc"
    break;

  case 620: // pool_list_entry: "{" $@88 pool_params "}"
#line 2203 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3488 "dhcp6_parser.cc"
    break;

  case 621: // $@89: %empty
#line 2209 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3498 "dhcp6_parser.cc"
    break;

  case 622: // sub_pool6: "{" $@89 pool_params "}"
#line 2213 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3508 "dhcp6_parser.cc"
    break;

  case 625: // pool_params: pool_params ","
#line 2221 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3516 "dhcp6_parser.cc"
    break;

  case 650: // $@90: %empty
#line 2252 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3525 "dhcp6_parser.cc"
    break;

  case 651: // pool_entry: "pool" $@90 ":" "constant string"
#line 2255 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3535 "dhcp6_parser.cc"
    break;

  case 652: // pool_id: "pool-id" ":" "integer"
#line 2261 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3545 "dhcp6_parser.cc"
    break;

  case 653: // $@91: %empty
#line 2267 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3553 "dhcp6_parser.cc"
    break;

  case 654: // user_context: "user-context" $@91 ":" map_value
#line 2269 "dhcp6_parser.yy"
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
#line 3580 "dhcp6_parser.cc"
    break;

  case 655: // $@92: %empty
#line 2292 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3588 "dhcp6_parser.cc"
    break;

  case 656: // comment: "comment" $@92 ":" "constant string"
#line 2294 "dhcp6_parser.yy"
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
#line 3617 "dhcp6_parser.cc"
    break;

  case 657: // $@93: %empty
#line 2322 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3629 "dhcp6_parser.cc"
    break;

  case 658: // pd_pools_list: "pd-pools" $@93 ":" "[" pd_pools_list_content "]"
#line 2328 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3638 "dhcp6_parser.cc"
    break;

  case 663: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2341 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3646 "dhcp6_parser.cc"
    break;

  case 664: // $@94: %empty
#line 2346 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3656 "dhcp6_parser.cc"
    break;

  case 665: // pd_pool_entry: "{" $@94 pd_pool_params "}"
#line 2350 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3668 "dhcp6_parser.cc"
    break;

  case 666: // $@95: %empty
#line 2358 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3678 "dhcp6_parser.cc"
    break;

  case 667: // sub_pd_pool: "{" $@95 pd_pool_params "}"
#line 2362 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3690 "dhcp6_parser.cc"
    break;

  case 670: // pd_pool_params: pd_pool_params ","
#line 2372 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3698 "dhcp6_parser.cc"
    break;

  case 685: // $@96: %empty
#line 2393 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3707 "dhcp6_parser.cc"
    break;

  case 686: // pd_prefix: "prefix" $@96 ":" "constant string"
#line 2396 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3717 "dhcp6_parser.cc"
    break;

  case 687: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2402 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3727 "dhcp6_parser.cc"
    break;

  case 688: // $@97: %empty
#line 2408 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3736 "dhcp6_parser.cc"
    break;

  case 689: // excluded_prefix: "excluded-prefix" $@97 ":" "constant string"
#line 2411 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3746 "dhcp6_parser.cc"
    break;

  case 690: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2417 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3756 "dhcp6_parser.cc"
    break;

  case 691: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2423 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3766 "dhcp6_parser.cc"
    break;

  case 692: // $@98: %empty
#line 2432 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3778 "dhcp6_parser.cc"
    break;

  case 693: // reservations: "reservations" $@98 ":" "[" reservations_list "]"
#line 2438 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3787 "dhcp6_parser.cc"
    break;

  case 698: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2449 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3795 "dhcp6_parser.cc"
    break;

  case 699: // $@99: %empty
#line 2454 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3805 "dhcp6_parser.cc"
    break;

  case 700: // reservation: "{" $@99 reservation_params "}"
#line 2458 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3814 "dhcp6_parser.cc"
    break;

  case 701: // $@100: %empty
#line 2463 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3824 "dhcp6_parser.cc"
    break;

  case 702: // sub_reservation: "{" $@100 reservation_params "}"
#line 2467 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3833 "dhcp6_parser.cc"
    break;

  case 707: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2478 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3841 "dhcp6_parser.cc"
    break;

  case 720: // $@101: %empty
#line 2498 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3853 "dhcp6_parser.cc"
    break;

  case 721: // ip_addresses: "ip-addresses" $@101 ":" list_strings
#line 2504 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3862 "dhcp6_parser.cc"
    break;

  case 722: // $@102: %empty
#line 2509 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3874 "dhcp6_parser.cc"
    break;

  case 723: // prefixes: "prefixes" $@102 ":" list_strings
#line 2515 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3883 "dhcp6_parser.cc"
    break;

  case 724: // $@103: %empty
#line 2520 "dhcp6_parser.yy"
                                     {
    ctx.unique("excluded-prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3895 "dhcp6_parser.cc"
    break;

  case 725: // excluded_prefixes: "excluded-prefixes" $@103 ":" list_strings
#line 2526 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3904 "dhcp6_parser.cc"
    break;

  case 726: // $@104: %empty
#line 2531 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3913 "dhcp6_parser.cc"
    break;

  case 727: // duid: "duid" $@104 ":" "constant string"
#line 2534 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3923 "dhcp6_parser.cc"
    break;

  case 728: // $@105: %empty
#line 2540 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3932 "dhcp6_parser.cc"
    break;

  case 729: // hw_address: "hw-address" $@105 ":" "constant string"
#line 2543 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3942 "dhcp6_parser.cc"
    break;

  case 730: // $@106: %empty
#line 2549 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3951 "dhcp6_parser.cc"
    break;

  case 731: // hostname: "hostname" $@106 ":" "constant string"
#line 2552 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3961 "dhcp6_parser.cc"
    break;

  case 732: // $@107: %empty
#line 2558 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3970 "dhcp6_parser.cc"
    break;

  case 733: // flex_id_value: "flex-id" $@107 ":" "constant string"
#line 2561 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3980 "dhcp6_parser.cc"
    break;

  case 734: // $@108: %empty
#line 2567 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3992 "dhcp6_parser.cc"
    break;

  case 735: // reservation_client_classes: "client-classes" $@108 ":" list_strings
#line 2573 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4001 "dhcp6_parser.cc"
    break;

  case 736: // $@109: %empty
#line 2581 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 4013 "dhcp6_parser.cc"
    break;

  case 737: // relay: "relay" $@109 ":" "{" relay_map "}"
#line 2587 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4022 "dhcp6_parser.cc"
    break;

  case 739: // $@110: %empty
#line 2598 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 4034 "dhcp6_parser.cc"
    break;

  case 740: // client_classes: "client-classes" $@110 ":" "[" client_classes_list "]"
#line 2604 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4043 "dhcp6_parser.cc"
    break;

  case 743: // client_classes_list: client_classes_list ","
#line 2611 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 4051 "dhcp6_parser.cc"
    break;

  case 744: // $@111: %empty
#line 2616 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4061 "dhcp6_parser.cc"
    break;

  case 745: // client_class_entry: "{" $@111 client_class_params "}"
#line 2620 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 4071 "dhcp6_parser.cc"
    break;

  case 750: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2632 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 4079 "dhcp6_parser.cc"
    break;

  case 767: // $@112: %empty
#line 2656 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4088 "dhcp6_parser.cc"
    break;

  case 768: // client_class_test: "test" $@112 ":" "constant string"
#line 2659 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4098 "dhcp6_parser.cc"
    break;

  case 769: // $@113: %empty
#line 2665 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4107 "dhcp6_parser.cc"
    break;

  case 770: // client_class_template_test: "template-test" $@113 ":" "constant string"
#line 2668 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4117 "dhcp6_parser.cc"
    break;

  case 771: // only_if_required: "only-if-required" ":" "boolean"
#line 2675 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4127 "dhcp6_parser.cc"
    break;

  case 772: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2681 "dhcp6_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4137 "dhcp6_parser.cc"
    break;

  case 773: // $@114: %empty
#line 2690 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 4149 "dhcp6_parser.cc"
    break;

  case 774: // server_id: "server-id" $@114 ":" "{" server_id_params "}"
#line 2696 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4160 "dhcp6_parser.cc"
    break;

  case 777: // server_id_params: server_id_params ","
#line 2705 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4168 "dhcp6_parser.cc"
    break;

  case 787: // $@115: %empty
#line 2721 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 4177 "dhcp6_parser.cc"
    break;

  case 788: // server_id_type: "type" $@115 ":" duid_type
#line 2724 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4186 "dhcp6_parser.cc"
    break;

  case 789: // duid_type: "LLT"
#line 2729 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4192 "dhcp6_parser.cc"
    break;

  case 790: // duid_type: "EN"
#line 2730 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4198 "dhcp6_parser.cc"
    break;

  case 791: // duid_type: "LL"
#line 2731 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4204 "dhcp6_parser.cc"
    break;

  case 792: // htype: "htype" ":" "integer"
#line 2734 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4214 "dhcp6_parser.cc"
    break;

  case 793: // $@116: %empty
#line 2740 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4223 "dhcp6_parser.cc"
    break;

  case 794: // identifier: "identifier" $@116 ":" "constant string"
#line 2743 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4233 "dhcp6_parser.cc"
    break;

  case 795: // time: "time" ":" "integer"
#line 2749 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4243 "dhcp6_parser.cc"
    break;

  case 796: // enterprise_id: "enterprise-id" ":" "integer"
#line 2755 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4253 "dhcp6_parser.cc"
    break;

  case 797: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2763 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4263 "dhcp6_parser.cc"
    break;

  case 798: // $@117: %empty
#line 2771 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4276 "dhcp6_parser.cc"
    break;

  case 799: // control_socket: "control-socket" $@117 ":" "{" control_socket_params "}"
#line 2778 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4285 "dhcp6_parser.cc"
    break;

  case 800: // $@118: %empty
#line 2783 "dhcp6_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4298 "dhcp6_parser.cc"
    break;

  case 801: // control_sockets: "control-sockets" $@118 ":" "[" control_socket_list "]"
#line 2790 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4307 "dhcp6_parser.cc"
    break;

  case 806: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2801 "dhcp6_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4315 "dhcp6_parser.cc"
    break;

  case 807: // $@119: %empty
#line 2806 "dhcp6_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4325 "dhcp6_parser.cc"
    break;

  case 808: // control_socket_entry: "{" $@119 control_socket_params "}"
#line 2810 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4333 "dhcp6_parser.cc"
    break;

  case 811: // control_socket_params: control_socket_params ","
#line 2816 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4341 "dhcp6_parser.cc"
    break;

  case 825: // $@120: %empty
#line 2836 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4350 "dhcp6_parser.cc"
    break;

  case 826: // control_socket_type: "socket-type" $@120 ":" control_socket_type_value
#line 2839 "dhcp6_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4359 "dhcp6_parser.cc"
    break;

  case 827: // control_socket_type_value: "unix"
#line 2845 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4365 "dhcp6_parser.cc"
    break;

  case 828: // control_socket_type_value: "http"
#line 2846 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4371 "dhcp6_parser.cc"
    break;

  case 829: // control_socket_type_value: "https"
#line 2847 "dhcp6_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4377 "dhcp6_parser.cc"
    break;

  case 830: // $@121: %empty
#line 2850 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4387 "dhcp6_parser.cc"
    break;

  case 831: // control_socket_name: "socket-name" $@121 ":" "constant string"
#line 2854 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4397 "dhcp6_parser.cc"
    break;

  case 832: // $@122: %empty
#line 2860 "dhcp6_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4407 "dhcp6_parser.cc"
    break;

  case 833: // control_socket_address: "socket-address" $@122 ":" "constant string"
#line 2864 "dhcp6_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4417 "dhcp6_parser.cc"
    break;

  case 834: // control_socket_port: "socket-port" ":" "integer"
#line 2870 "dhcp6_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4427 "dhcp6_parser.cc"
    break;

  case 835: // cert_required: "cert-required" ":" "boolean"
#line 2876 "dhcp6_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4437 "dhcp6_parser.cc"
    break;

  case 836: // $@123: %empty
#line 2882 "dhcp6_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4449 "dhcp6_parser.cc"
    break;

  case 837: // http_headers: "http-headers" $@123 ":" "[" http_header_list "]"
#line 2888 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4458 "dhcp6_parser.cc"
    break;

  case 842: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2899 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4466 "dhcp6_parser.cc"
    break;

  case 843: // $@124: %empty
#line 2904 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4476 "dhcp6_parser.cc"
    break;

  case 844: // http_header: "{" $@124 http_header_params "}"
#line 2908 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4484 "dhcp6_parser.cc"
    break;

  case 847: // http_header_params: http_header_params ","
#line 2914 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4492 "dhcp6_parser.cc"
    break;

  case 853: // $@125: %empty
#line 2926 "dhcp6_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4501 "dhcp6_parser.cc"
    break;

  case 854: // header_value: "value" $@125 ":" "constant string"
#line 2929 "dhcp6_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4511 "dhcp6_parser.cc"
    break;

  case 855: // $@126: %empty
#line 2937 "dhcp6_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4523 "dhcp6_parser.cc"
    break;

  case 856: // authentication: "authentication" $@126 ":" "{" auth_params "}"
#line 2943 "dhcp6_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4534 "dhcp6_parser.cc"
    break;

  case 859: // auth_params: auth_params ","
#line 2952 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4542 "dhcp6_parser.cc"
    break;

  case 867: // $@127: %empty
#line 2966 "dhcp6_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4551 "dhcp6_parser.cc"
    break;

  case 868: // auth_type: "type" $@127 ":" auth_type_value
#line 2969 "dhcp6_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4560 "dhcp6_parser.cc"
    break;

  case 869: // auth_type_value: "basic"
#line 2974 "dhcp6_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4566 "dhcp6_parser.cc"
    break;

  case 870: // $@128: %empty
#line 2977 "dhcp6_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4575 "dhcp6_parser.cc"
    break;

  case 871: // realm: "realm" $@128 ":" "constant string"
#line 2980 "dhcp6_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4585 "dhcp6_parser.cc"
    break;

  case 872: // $@129: %empty
#line 2986 "dhcp6_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4594 "dhcp6_parser.cc"
    break;

  case 873: // directory: "directory" $@129 ":" "constant string"
#line 2989 "dhcp6_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4604 "dhcp6_parser.cc"
    break;

  case 874: // $@130: %empty
#line 2995 "dhcp6_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4616 "dhcp6_parser.cc"
    break;

  case 875: // clients: "clients" $@130 ":" "[" clients_list "]"
#line 3001 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4625 "dhcp6_parser.cc"
    break;

  case 880: // not_empty_clients_list: not_empty_clients_list ","
#line 3012 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4633 "dhcp6_parser.cc"
    break;

  case 881: // $@131: %empty
#line 3017 "dhcp6_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4643 "dhcp6_parser.cc"
    break;

  case 882: // basic_auth: "{" $@131 clients_params "}"
#line 3021 "dhcp6_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4651 "dhcp6_parser.cc"
    break;

  case 885: // clients_params: clients_params ","
#line 3027 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4659 "dhcp6_parser.cc"
    break;

  case 893: // $@132: %empty
#line 3041 "dhcp6_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4668 "dhcp6_parser.cc"
    break;

  case 894: // user_file: "user-file" $@132 ":" "constant string"
#line 3044 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4678 "dhcp6_parser.cc"
    break;

  case 895: // $@133: %empty
#line 3050 "dhcp6_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4687 "dhcp6_parser.cc"
    break;

  case 896: // password_file: "password-file" $@133 ":" "constant string"
#line 3053 "dhcp6_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4697 "dhcp6_parser.cc"
    break;

  case 897: // $@134: %empty
#line 3061 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4709 "dhcp6_parser.cc"
    break;

  case 898: // dhcp_queue_control: "dhcp-queue-control" $@134 ":" "{" queue_control_params "}"
#line 3067 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4720 "dhcp6_parser.cc"
    break;

  case 901: // queue_control_params: queue_control_params ","
#line 3076 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4728 "dhcp6_parser.cc"
    break;

  case 908: // enable_queue: "enable-queue" ":" "boolean"
#line 3089 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4738 "dhcp6_parser.cc"
    break;

  case 909: // $@135: %empty
#line 3095 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4747 "dhcp6_parser.cc"
    break;

  case 910: // queue_type: "queue-type" $@135 ":" "constant string"
#line 3098 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4757 "dhcp6_parser.cc"
    break;

  case 911: // capacity: "capacity" ":" "integer"
#line 3104 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4767 "dhcp6_parser.cc"
    break;

  case 912: // $@136: %empty
#line 3110 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4776 "dhcp6_parser.cc"
    break;

  case 913: // arbitrary_map_entry: "constant string" $@136 ":" value
#line 3113 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4785 "dhcp6_parser.cc"
    break;

  case 914: // $@137: %empty
#line 3120 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4797 "dhcp6_parser.cc"
    break;

  case 915: // dhcp_ddns: "dhcp-ddns" $@137 ":" "{" dhcp_ddns_params "}"
#line 3126 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4808 "dhcp6_parser.cc"
    break;

  case 916: // $@138: %empty
#line 3133 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4818 "dhcp6_parser.cc"
    break;

  case 917: // sub_dhcp_ddns: "{" $@138 dhcp_ddns_params "}"
#line 3137 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4828 "dhcp6_parser.cc"
    break;

  case 920: // dhcp_ddns_params: dhcp_ddns_params ","
#line 3145 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4836 "dhcp6_parser.cc"
    break;

  case 932: // enable_updates: "enable-updates" ":" "boolean"
#line 3163 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4846 "dhcp6_parser.cc"
    break;

  case 933: // $@139: %empty
#line 3169 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4855 "dhcp6_parser.cc"
    break;

  case 934: // server_ip: "server-ip" $@139 ":" "constant string"
#line 3172 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4865 "dhcp6_parser.cc"
    break;

  case 935: // server_port: "server-port" ":" "integer"
#line 3178 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4875 "dhcp6_parser.cc"
    break;

  case 936: // $@140: %empty
#line 3184 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4884 "dhcp6_parser.cc"
    break;

  case 937: // sender_ip: "sender-ip" $@140 ":" "constant string"
#line 3187 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4894 "dhcp6_parser.cc"
    break;

  case 938: // sender_port: "sender-port" ":" "integer"
#line 3193 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4904 "dhcp6_parser.cc"
    break;

  case 939: // max_queue_size: "max-queue-size" ":" "integer"
#line 3199 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4914 "dhcp6_parser.cc"
    break;

  case 940: // $@141: %empty
#line 3205 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4923 "dhcp6_parser.cc"
    break;

  case 941: // ncr_protocol: "ncr-protocol" $@141 ":" ncr_protocol_value
#line 3208 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4932 "dhcp6_parser.cc"
    break;

  case 942: // ncr_protocol_value: "UDP"
#line 3214 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4938 "dhcp6_parser.cc"
    break;

  case 943: // ncr_protocol_value: "TCP"
#line 3215 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4944 "dhcp6_parser.cc"
    break;

  case 944: // $@142: %empty
#line 3218 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4953 "dhcp6_parser.cc"
    break;

  case 945: // ncr_format: "ncr-format" $@142 ":" "JSON"
#line 3221 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4963 "dhcp6_parser.cc"
    break;

  case 946: // $@143: %empty
#line 3229 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4975 "dhcp6_parser.cc"
    break;

  case 947: // config_control: "config-control" $@143 ":" "{" config_control_params "}"
#line 3235 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4985 "dhcp6_parser.cc"
    break;

  case 948: // $@144: %empty
#line 3241 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4995 "dhcp6_parser.cc"
    break;

  case 949: // sub_config_control: "{" $@144 config_control_params "}"
#line 3245 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 5004 "dhcp6_parser.cc"
    break;

  case 952: // config_control_params: config_control_params ","
#line 3253 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 5012 "dhcp6_parser.cc"
    break;

  case 955: // $@145: %empty
#line 3263 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 5024 "dhcp6_parser.cc"
    break;

  case 956: // config_databases: "config-databases" $@145 ":" "[" database_list "]"
#line 3269 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5033 "dhcp6_parser.cc"
    break;

  case 957: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3274 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 5043 "dhcp6_parser.cc"
    break;

  case 958: // $@146: %empty
#line 3282 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 5055 "dhcp6_parser.cc"
    break;

  case 959: // loggers: "loggers" $@146 ":" "[" loggers_entries "]"
#line 3288 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5064 "dhcp6_parser.cc"
    break;

  case 962: // loggers_entries: loggers_entries ","
#line 3297 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 5072 "dhcp6_parser.cc"
    break;

  case 963: // $@147: %empty
#line 3303 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 5082 "dhcp6_parser.cc"
    break;

  case 964: // logger_entry: "{" $@147 logger_params "}"
#line 3307 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 5090 "dhcp6_parser.cc"
    break;

  case 967: // logger_params: logger_params ","
#line 3313 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 5098 "dhcp6_parser.cc"
    break;

  case 975: // debuglevel: "debuglevel" ":" "integer"
#line 3327 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 5108 "dhcp6_parser.cc"
    break;

  case 976: // $@148: %empty
#line 3333 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5117 "dhcp6_parser.cc"
    break;

  case 977: // severity: "severity" $@148 ":" "constant string"
#line 3336 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 5127 "dhcp6_parser.cc"
    break;

  case 978: // $@149: %empty
#line 3342 "dhcp6_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 5139 "dhcp6_parser.cc"
    break;

  case 979: // output_options_list: "output-options" $@149 ":" "[" output_options_list_content "]"
#line 3348 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5148 "dhcp6_parser.cc"
    break;

  case 982: // output_options_list_content: output_options_list_content ","
#line 3355 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 5156 "dhcp6_parser.cc"
    break;

  case 983: // $@150: %empty
#line 3360 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 5166 "dhcp6_parser.cc"
    break;

  case 984: // output_entry: "{" $@150 output_params_list "}"
#line 3364 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 5174 "dhcp6_parser.cc"
    break;

  case 987: // output_params_list: output_params_list ","
#line 3370 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 5182 "dhcp6_parser.cc"
    break;

  case 993: // $@151: %empty
#line 3382 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5191 "dhcp6_parser.cc"
    break;

  case 994: // output: "output" $@151 ":" "constant string"
#line 3385 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5201 "dhcp6_parser.cc"
    break;

  case 995: // flush: "flush" ":" "boolean"
#line 3391 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5211 "dhcp6_parser.cc"
    break;

  case 996: // maxsize: "maxsize" ":" "integer"
#line 3397 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5221 "dhcp6_parser.cc"
    break;

  case 997: // maxver: "maxver" ":" "integer"
#line 3403 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5231 "dhcp6_parser.cc"
    break;

  case 998: // $@152: %empty
#line 3409 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5240 "dhcp6_parser.cc"
    break;

  case 999: // pattern: "pattern" $@152 ":" "constant string"
#line 3412 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5250 "dhcp6_parser.cc"
    break;

  case 1000: // $@153: %empty
#line 3418 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5262 "dhcp6_parser.cc"
    break;

  case 1001: // compatibility: "compatibility" $@153 ":" "{" compatibility_params "}"
#line 3424 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5271 "dhcp6_parser.cc"
    break;

  case 1004: // compatibility_params: compatibility_params ","
#line 3431 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5279 "dhcp6_parser.cc"
    break;

  case 1007: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3440 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5289 "dhcp6_parser.cc"
    break;


#line 5293 "dhcp6_parser.cc"

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
     490, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445,    51,    43,    62,    67,    74,
     117,   176,   209,   210,   211,   224,   225,   234,   238,   247,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,    43,  -148,
     245,   763,    70,  1442,   320,   164,   228,    35,    11,   382,
    -108,   513,    89, -1445,   259,   278,   307,   274,   310, -1445,
     109, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   322,   340,
     346,   349,   372,   373,   381,   383,   401,   412,   414,   415,
     426,   443, -1445,   444,   459,   480,   491,   494, -1445, -1445,
   -1445,   495,   497,   498,   499,   501,   502,   503, -1445, -1445,
   -1445,   504, -1445, -1445, -1445, -1445, -1445, -1445,   505,   506,
     512, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
     514, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   516,   517,
     519, -1445, -1445,   520, -1445,   135, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   521,
     522,   523,   524, -1445,   145, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   530,   531,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445,   153, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   533,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
     171, -1445, -1445, -1445, -1445, -1445, -1445,   534, -1445,   537,
     539, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
     174, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   326,
     334, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
     344, -1445, -1445,   543, -1445, -1445, -1445,   546, -1445, -1445,
     376,   551, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445,   553,   555,   559, -1445, -1445,
   -1445, -1445, -1445,   421,   562, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   184,
   -1445, -1445, -1445,   563, -1445,   566, -1445,   567,   568, -1445,
   -1445, -1445, -1445, -1445,   190, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445,   569,   241, -1445, -1445, -1445,
   -1445,    43,    43, -1445,   336,   570, -1445, -1445,   573,   574,
     575,   578,   580,   581,   253,   325,   345,   347,   355,   358,
     360,   361,   362,   350,   364,   365,   363,   367,   583,   370,
     377,   371,   378,   389,   585,   596,   599,   390,   391,   375,
     384,   388,   397,   396,   611,   620,   636,   404,   646,   648,
     650,   652,   653,   654,   419,   420,   432,   660,   665,   668,
     673,   676,   677,   678,   679,   681,   447,   683,   686,   687,
     688,   689,   690,   692,   454,   455,   460,   695,   701, -1445,
     763, -1445,   702,   487,   488,   493,   496,    70, -1445,   728,
     731,   732,   734,   738,   508,   500,   741,   742,   743,   746,
     747,  1442, -1445,   748,   515,   320, -1445,   750,   518,   751,
     525,   526,   164, -1445,   753,   754,   756,   759,   760,   761,
     767,   772, -1445,   228, -1445,   773,   775,   540,   776,   778,
     779,   544, -1445,    11,   784,   547,   548,   549,   785, -1445,
     382,   789,   790,   -19, -1445,   552,   792,   564,   796,   565,
     571,   799,   800,   513, -1445,   803,   572,    89, -1445, -1445,
   -1445,   804,   802,   576,   807,   808,   843,   844,   805, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445,   612, -1445, -1445, -1445, -1445, -1445,  -152,
     613,   614, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   806,
     850,   851, -1445,   617,   618,   386,   854,   857,   625, -1445,
   -1445, -1445,   861,   862,   864,   863,   866,   867,   868,   869,
     872, -1445,   873,   874,   870,   875,   876,   634,   651, -1445,
   -1445, -1445,   887,   888, -1445,   889, -1445, -1445, -1445, -1445,
   -1445,   891,   892,   658,   659,   661, -1445, -1445,   889,   889,
     889,   663,   893, -1445,   664, -1445, -1445,   666, -1445,   667,
   -1445, -1445, -1445,   889,   889,   889,   889,   669,   670,   672,
     675, -1445,   680,   682, -1445,   684,   685,   691, -1445, -1445,
     693, -1445, -1445, -1445,   889, -1445,   696,   857, -1445, -1445,
     697, -1445,   698, -1445, -1445,   -62,   700, -1445,   903, -1445,
   -1445,    43,   763, -1445,    89,    70,   177,   177,   906, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   909,   910,
     911, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   912, -1445,
   -1445, -1445,  -103,    43,   179,    68,   916,   919,   920,   258,
      75,   138,   202,   921,   216,   513, -1445, -1445,   925,  -161,
   -1445, -1445,   932,   933, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445,   801, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   906, -1445,
     254,   290,   321, -1445, -1445, -1445, -1445,   938,   939,   940,
     941,   942,   943,   944,   945,   946,   947, -1445,   948,   950,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445,   330, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445,   333, -1445,   949,   953,
   -1445, -1445,   952,   956, -1445, -1445,   954,   958, -1445, -1445,
     957,   959, -1445, -1445,   960,   961, -1445, -1445, -1445,    72,
   -1445, -1445, -1445,   962, -1445, -1445, -1445,   110, -1445, -1445,
   -1445, -1445, -1445,   348, -1445, -1445, -1445, -1445,   159, -1445,
   -1445,   963,   964, -1445, -1445,   965,   967, -1445,   968,   975,
     976,   977,   978,   979,   351, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445,   980,   981,   982, -1445, -1445, -1445,
   -1445,   357, -1445, -1445, -1445, -1445, -1445, -1445,   984,   985,
     986, -1445,   359, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445,   987, -1445,   988, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445,   380, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445,   989,   990, -1445,   992, -1445,   993, -1445, -1445,
   -1445,   395, -1445, -1445, -1445, -1445, -1445,   425, -1445,   260,
   -1445,   994, -1445,   428, -1445, -1445,   725, -1445,   995,   991,
   -1445, -1445,   996,   997, -1445, -1445,   998,   999, -1445, -1445,
   -1445,  1000,  1003,  1004,  1005,   758,   768,   769,   770,   771,
     774,   777,   780,   781,   782,  1010,   783,   786,  1012,  1013,
    1015,  1016,  1020,   177, -1445, -1445,   177, -1445,   906,  1442,
   -1445,   909,    11, -1445,   910,   382, -1445,   911,  1540, -1445,
     912,  -103, -1445, -1445,   179, -1445,  1021,  1025,    68, -1445,
     213,   916, -1445,   228, -1445,   919,  -108, -1445,   920,   791,
     794,   795,   797,   798,   815,   258, -1445,  1026,  1029,   817,
     818,   820,    75, -1445,   819,   826,   827,   138, -1445,  1039,
    1042,  1044,   828,  1068,   831,  1071,   202, -1445,   202, -1445,
     921,   834,  1076,   841,  1079,   216, -1445, -1445,    40,   925,
   -1445,   845,  -161, -1445, -1445,  1084,  1093,   320, -1445,   932,
     164, -1445,   933, -1445, -1445,   858,   859,   878,   885, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,    69,
   -1445, -1445,   896,   899,   917,   374,   926, -1445,   429, -1445,
     435, -1445,  1094, -1445,  1096, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
     436, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   931,
     936, -1445, -1445, -1445,  1104,  1111, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445,  1119,  1130, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445,  1152, -1445,   437, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445,   332,   951, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445,   291,   955,   969,
   -1445,  1166, -1445,  1173, -1445,   438, -1445, -1445,  1002, -1445,
      43, -1445, -1445,  1176, -1445, -1445, -1445, -1445, -1445,   446,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,  1006,   452,
   -1445,   456, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
    1540, -1445, -1445, -1445,  1178,  1181,  1001,  1008, -1445,   213,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445,    52,  1180, -1445, -1445, -1445,  1184,   983,
    1186,    40, -1445, -1445, -1445, -1445, -1445,  1007,  1009, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   473,
   -1445, -1445, -1445, -1445, -1445, -1445,  1212,  1216, -1445,  1215,
   -1445,  1014, -1445, -1445, -1445,  1223,  1225,  1226,  1227,    52,
   -1445,   146, -1445,  1180,  1228, -1445,  1053,  1017,  1018,  1231,
   -1445, -1445, -1445, -1445, -1445, -1445,   474, -1445, -1445, -1445,
   -1445,   306, -1445, -1445, -1445, -1445, -1445,  1232,  1236,   146,
   -1445,  -150,  1228, -1445, -1445,  1239,  1249, -1445,  1019, -1445,
   -1445,  1252,  1256,  1259, -1445,   475, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445,    57, -1445,  1232, -1445,  1260,  1023,  1027,
    1028,  1266,  -150, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445,   477, -1445, -1445, -1445, -1445,  1031, -1445, -1445, -1445,
    1033, -1445,  1270,  1271,    57, -1445, -1445, -1445,  1036,  1037,
   -1445, -1445, -1445
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   205,     9,   399,    11,
     621,    13,   666,    15,   701,    17,   536,    19,   545,    21,
     584,    23,   361,    25,   916,    27,   948,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   703,     0,   547,   586,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   144,   946,   203,   224,   226,   228,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   193,     0,     0,     0,     0,     0,   163,   170,
     172,     0,     0,     0,     0,     0,     0,     0,   390,   534,
     575,     0,   196,   198,   176,   474,   653,   655,     0,     0,
       0,   317,   336,   326,   306,   739,   692,   352,   373,   773,
       0,   338,   798,   800,   897,   914,   186,   188,     0,     0,
       0,   958,  1000,     0,   143,     0,    69,    72,    73,    74,
      75,    76,    77,    78,    79,    80,   111,   112,   113,   114,
     115,    81,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   117,   118,   132,   133,   134,
     107,   140,   141,   142,   136,   137,   138,    84,    85,    86,
      87,   104,    88,    90,    89,   135,    94,    95,    82,   108,
     109,   110,    83,    92,    93,   102,   103,   105,    91,    96,
      97,    98,    99,   100,   101,   106,   116,   139,   218,     0,
       0,     0,     0,   217,     0,   207,   210,   211,   212,   213,
     214,   215,   216,   612,   657,   455,   457,   459,     0,     0,
     463,   465,   467,   461,   736,   454,   404,   405,   406,   407,
     408,   409,   410,   411,   431,   432,   433,   434,   435,   438,
     439,   440,   441,   442,   443,   444,   445,   446,   447,   448,
     449,   450,   436,   437,   451,   452,   453,     0,   401,   415,
     416,   417,   420,   421,   422,   423,   425,   426,   427,   418,
     419,   412,   413,   429,   430,   414,   424,   428,   650,     0,
     649,   633,   634,   635,   636,   637,   638,   639,   640,   641,
     642,   643,   644,   645,   646,   629,   630,   631,   632,   628,
       0,   623,   626,   627,   647,   648,   685,     0,   688,     0,
       0,   684,   676,   677,   678,   679,   675,   674,   682,   683,
       0,   668,   671,   672,   680,   681,   673,   734,   720,   722,
     724,   726,   728,   730,   732,   719,   716,   717,   718,     0,
     704,   705,   710,   711,   712,   708,   713,   714,   715,   709,
       0,   565,   273,     0,   569,   567,   572,     0,   561,   562,
       0,   548,   549,   552,   564,   553,   554,   555,   571,   556,
     557,   558,   559,   560,   603,     0,     0,     0,   610,   601,
     602,   605,   606,     0,   587,   588,   591,   592,   593,   594,
     595,   596,   597,   600,   598,   599,   369,   371,   366,     0,
     363,   367,   368,     0,   933,     0,   936,     0,     0,   940,
     944,   931,   929,   930,     0,   918,   921,   922,   923,   924,
     925,   926,   927,   928,   955,     0,     0,   950,   953,   954,
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
       0,   403,   400,     0,     0,   625,   622,     0,     0,     0,
       0,     0,   670,   667,     0,     0,     0,     0,     0,     0,
       0,     0,   702,   707,   537,     0,     0,     0,     0,     0,
       0,     0,   546,   551,     0,     0,     0,     0,     0,   585,
     590,     0,     0,   365,   362,     0,     0,     0,     0,     0,
       0,     0,     0,   920,   917,     0,     0,   952,   949,    51,
      43,     0,     0,     0,     0,     0,     0,     0,     0,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,     0,   191,   192,   160,   161,   162,     0,
       0,     0,   174,   175,   182,   183,   184,   185,   190,     0,
       0,     0,   195,     0,     0,     0,     0,     0,     0,   469,
     470,   471,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   797,     0,     0,     0,     0,     0,     0,     0,   200,
     201,   202,     0,     0,    70,     0,   220,   221,   222,   223,
     208,     0,     0,     0,     0,     0,   472,   473,     0,     0,
       0,     0,     0,   402,     0,   652,   624,     0,   687,     0,
     690,   691,   669,     0,     0,     0,     0,     0,     0,     0,
       0,   706,     0,     0,   563,     0,     0,     0,   574,   550,
       0,   607,   608,   609,     0,   589,     0,     0,   364,   932,
       0,   935,     0,   938,   939,     0,     0,   919,     0,   957,
     951,     0,     0,   145,     0,     0,     0,     0,   230,   194,
     165,   166,   167,   168,   169,   164,   171,   173,   392,   538,
     577,   197,   199,   178,   179,   180,   181,   177,   476,    40,
     654,   656,     0,    48,     0,     0,     0,   694,   354,     0,
       0,     0,     0,   802,     0,     0,   187,   189,     0,     0,
      53,   219,   614,   659,   456,   458,   460,   464,   466,   468,
     462,     0,   651,   686,   689,   735,   721,   723,   725,   727,
     729,   731,   733,   566,   274,   570,   568,   573,   604,   611,
     370,   372,   934,   937,   942,   943,   941,   945,   230,    44,
       0,     0,     0,   264,   266,   268,   270,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   283,     0,     0,
     291,   293,   295,   297,   299,   300,   301,   302,   303,   304,
     263,     0,   237,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   254,   255,   256,   257,
     253,   258,   259,   260,   261,   262,     0,   235,     0,   231,
     232,   397,     0,   393,   394,   543,     0,   539,   540,   582,
       0,   578,   579,   481,     0,   477,   478,   324,   325,     0,
     319,   322,   323,     0,   334,   335,   331,     0,   328,   332,
     333,   313,   315,     0,   308,   311,   312,   744,     0,   741,
     699,     0,   695,   696,   359,     0,   355,   356,     0,     0,
       0,     0,     0,     0,     0,   375,   378,   379,   380,   381,
     382,   383,   787,   793,     0,     0,     0,   786,   783,   784,
     785,     0,   775,   778,   781,   779,   780,   782,     0,     0,
       0,   348,     0,   340,   343,   344,   345,   346,   347,   825,
     830,   832,     0,   855,     0,   836,   824,   817,   818,   819,
     822,   823,     0,   809,   812,   813,   814,   815,   820,   821,
     816,   807,     0,   803,   804,     0,   909,     0,   912,   905,
     906,     0,   899,   902,   903,   904,   907,     0,   963,     0,
     960,     0,  1006,     0,  1002,  1005,    55,   619,     0,   615,
     616,   664,     0,   660,   661,   738,     0,     0,    64,   947,
     204,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   239,   225,   227,     0,   229,   234,     0,
     391,   396,   547,   535,   542,   586,   576,   581,     0,   475,
     480,   321,   318,   337,   330,   327,     0,     0,   310,   307,
     746,   743,   740,   703,   693,   698,     0,   353,   358,     0,
       0,     0,     0,     0,     0,   377,   374,     0,     0,     0,
       0,     0,   777,   774,     0,     0,     0,   342,   339,     0,
       0,     0,     0,     0,     0,     0,   811,   799,     0,   801,
     806,     0,     0,     0,     0,   901,   898,   915,     0,   962,
     959,     0,  1004,  1001,    57,     0,    56,     0,   613,   618,
       0,   658,   663,   737,   956,     0,     0,     0,     0,   272,
     275,   276,   277,   278,   279,   280,   281,   290,   282,     0,
     288,   289,     0,     0,     0,     0,     0,   238,     0,   233,
       0,   395,     0,   541,     0,   580,   533,   501,   502,   503,
     505,   506,   507,   490,   491,   510,   511,   512,   513,   514,
     517,   518,   519,   520,   521,   522,   523,   524,   525,   526,
     527,   528,   529,   515,   516,   530,   531,   532,   486,   487,
     488,   489,   497,   498,   499,   500,   494,   495,   496,   504,
       0,   483,   492,   508,   509,   493,   479,   320,   329,     0,
       0,   309,   767,   769,     0,     0,   765,   759,   760,   761,
     762,   763,   764,   766,   756,   757,   758,     0,   747,   748,
     751,   752,   753,   754,   755,   742,     0,   697,     0,   357,
     384,   385,   386,   387,   388,   389,   376,     0,     0,   792,
     795,   796,   776,   349,   350,   351,   341,     0,     0,     0,
     834,     0,   835,     0,   810,     0,   805,   908,     0,   911,
       0,   900,   978,     0,   976,   974,   968,   972,   973,     0,
     965,   970,   971,   969,   961,  1007,  1003,    54,    59,     0,
     617,     0,   662,   265,   267,   269,   271,   285,   286,   287,
     284,   292,   294,   296,   298,   305,   236,   398,   544,   583,
     485,   482,   314,   316,     0,     0,     0,     0,   745,   750,
     700,   360,   789,   790,   791,   788,   794,   827,   828,   829,
     826,   831,   833,     0,   838,   808,   910,   913,     0,     0,
       0,   967,   964,    58,   620,   665,   484,     0,     0,   771,
     772,   749,   867,   870,   872,   874,   866,   865,   864,     0,
     857,   860,   861,   862,   863,   843,     0,   839,   840,     0,
     975,     0,   966,   768,   770,     0,     0,     0,     0,   859,
     856,     0,   837,   842,     0,   977,     0,     0,     0,     0,
     858,   853,   852,   848,   850,   851,     0,   845,   849,   841,
     983,     0,   980,   869,   868,   871,   873,   876,     0,   847,
     844,     0,   982,   979,   881,     0,   877,   878,     0,   846,
     993,     0,     0,     0,   998,     0,   985,   988,   989,   990,
     991,   992,   981,     0,   875,   880,   854,     0,     0,     0,
       0,     0,   987,   984,   893,   895,   892,   886,   888,   890,
     891,     0,   883,   887,   889,   879,     0,   995,   996,   997,
       0,   986,     0,     0,   885,   882,   994,   999,     0,     0,
     884,   894,   896
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445,   -10, -1445,  -634, -1445,
     527, -1445, -1445, -1445, -1445,   476, -1445,  -415, -1445, -1445,
   -1445,   -71, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   509,
     730, -1445, -1445,     4,    12,    22,    38,    41,    42,   -57,
     -54,   -35,   -15,    97,   100,   102, -1445,    20,    23,    45,
      48, -1445, -1445,    55, -1445,    60, -1445,    66,   103,    71,
   -1445, -1445,    73,    76,    78,    84,    90, -1445,    95, -1445,
     105, -1445, -1445, -1445, -1445, -1445,   107, -1445,   108, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445,   507,   721, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445,   427, -1445,   185, -1445,  -756,   193, -1445, -1445, -1444,
   -1445, -1440, -1445, -1445, -1445, -1445,   -55, -1445,  -797, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445,  -801, -1445,  -795, -1445,  -792, -1445,    82, -1445,
   -1445, -1445, -1445, -1445, -1445,   170, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445,   178,  -782, -1445, -1445, -1445, -1445,   180,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445,   143, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445,   163, -1445, -1445, -1445,   166,
     694, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   158, -1445,
   -1445, -1445, -1445, -1445, -1445, -1083, -1445, -1445, -1445,   194,
   -1445, -1445, -1445,   197,   727, -1445, -1445, -1082, -1445, -1081,
   -1445,    61, -1445,    85, -1445,   120, -1445,   125, -1445,   113,
     115,   118, -1445, -1080, -1445, -1445, -1445, -1445,   191, -1445,
   -1445,   -67,  1229, -1445, -1445, -1445, -1445, -1445,   200, -1445,
   -1445, -1445,   207, -1445,   707, -1445,   -65, -1445, -1445, -1445,
   -1445, -1445,   -61, -1445, -1445, -1445, -1445, -1445,   -29, -1445,
   -1445, -1445,   204, -1445, -1445, -1445,   212, -1445,   704, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445,   133, -1445, -1445, -1445,   141,   744, -1445,
   -1445,   -63,   -42, -1445,   -13, -1445, -1445, -1445, -1445, -1445,
     139, -1445, -1445, -1445,   147,   749, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445,   -58, -1445, -1445, -1445,   198, -1445, -1445,
   -1445,   203, -1445,   736,   511, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1079, -1445, -1445, -1445, -1445, -1445,   215, -1445, -1445, -1445,
     -47, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445,   183, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445,   173, -1445,   181,
     182, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445,  -109, -1445, -1445,  -129, -1445, -1445,
   -1445, -1445, -1445,   -96, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445,  -151, -1445, -1445,  -179, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445,   187, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445,   532,   726, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445,   579,   729, -1445, -1445,
   -1445, -1445, -1445, -1445,   189, -1445, -1445,   -53, -1445, -1445,
   -1445, -1445, -1445, -1445,  -118, -1445, -1445,  -142, -1445, -1445,
   -1445, -1445, -1445, -1445, -1445, -1445, -1445, -1445,   192, -1445
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     800,    87,    88,    41,    68,    84,    85,   821,  1056,  1175,
    1176,   890,    43,    70,    90,   475,    91,    45,    71,   165,
     166,   167,   478,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   504,   785,   186,   505,   187,   506,   188,   189,   190,
     520,   797,   191,   192,   193,   194,   195,   542,   196,   543,
     197,   198,   199,   200,   498,   201,   202,   518,   203,   519,
     204,   205,   206,   207,   480,    47,    72,   244,   245,   246,
     552,   247,   248,   249,   250,   208,   481,   209,   482,   210,
     483,   918,   919,   920,  1096,   891,   892,   893,  1071,   894,
    1072,   895,  1073,   896,  1074,   897,   898,   596,   899,   900,
     901,   902,   903,   904,   905,   906,   907,  1085,  1360,   908,
     909,   910,   911,  1088,   912,  1089,   913,  1090,   914,  1091,
     915,  1092,   211,   530,   953,   954,   955,  1116,   956,  1117,
     212,   527,   939,   940,   941,   942,   213,   529,   947,   948,
     949,   950,   214,   528,   215,   537,  1002,  1003,  1004,  1005,
    1006,   216,   533,   965,   966,   967,  1126,    63,    80,   439,
     440,   441,   611,   442,   612,   217,   534,   974,   975,   976,
     977,   978,   979,   980,   981,   218,   514,   922,   923,   924,
    1099,    49,    73,   297,   298,   299,   561,   300,   562,   301,
     563,   302,   569,   303,   566,   304,   567,   305,   568,   219,
     220,   221,   309,   310,   222,   521,   934,   935,   936,  1108,
    1260,  1261,   223,   515,    57,    77,   926,   927,   928,  1102,
      59,    78,   400,   401,   402,   403,   404,   405,   406,   595,
     407,   599,   408,   598,   409,   410,   600,   411,   224,   516,
     930,   931,   932,  1105,    61,    79,   423,   424,   425,   426,
     427,   604,   428,   429,   430,   431,   432,   433,   608,   312,
     559,  1058,  1059,  1060,  1177,    51,    74,   340,   341,   342,
     573,   343,   225,   522,   226,   523,   315,   560,  1062,  1063,
    1064,  1180,    53,    75,   360,   361,   362,   577,   363,   364,
     579,   365,   366,   227,   532,   961,   962,   963,  1123,    55,
      76,   379,   380,   381,   382,   585,   383,   586,   384,   587,
     385,   588,   386,   589,   387,   590,   388,   591,   389,   584,
     317,   570,  1066,   228,   531,   958,   959,  1120,  1287,  1288,
    1289,  1290,  1291,  1374,  1292,  1375,  1293,  1294,   229,   535,
     991,   992,   993,  1137,  1385,   994,   995,  1138,   996,   997,
     230,   231,   538,   232,   539,  1032,  1033,  1034,  1158,  1022,
    1023,  1024,  1149,  1390,  1025,  1150,  1026,  1151,  1027,  1028,
    1029,  1155,  1426,  1427,  1428,  1441,  1456,  1457,  1458,  1468,
    1030,  1153,  1419,  1420,  1421,  1435,  1464,  1422,  1436,  1423,
    1437,  1424,  1438,  1475,  1476,  1477,  1493,  1511,  1512,  1513,
    1522,  1514,  1523,   233,   540,  1041,  1042,  1043,  1044,  1162,
    1045,  1046,  1164,   234,   541,    65,    81,   454,   455,   456,
     457,   616,   458,   459,   618,   460,   461,   462,   621,   856,
     463,   622,   235,   479,    67,    82,   466,   467,   468,   625,
     469,   236,   547,  1049,  1050,  1168,  1339,  1340,  1341,  1342,
    1400,  1343,  1398,  1461,  1462,  1471,  1485,  1486,  1487,  1497,
    1488,  1489,  1490,  1491,  1501,   237,   548,  1053,  1054,  1055
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     164,   243,   265,   320,   351,   375,    38,   398,   419,   438,
     451,  1017,   357,   988,   421,   316,   272,  1018,   422,   273,
    1019,   916,   946,   399,   420,  1249,  1250,  1251,  1259,  1265,
     251,   313,   344,   358,   377,   391,   412,   434,   274,   452,
     937,   436,   437,   799,   311,   339,   356,   376,    31,  1507,
      32,    30,    33,  1508,   780,   781,   782,   783,   275,   252,
     314,   345,   359,   378,  1051,   413,   435,  1480,   453,    42,
    1481,  1482,  1483,  1484,    44,  1111,  1412,   266,  1112,   163,
    1507,    46,   864,   865,  1508,   267,   238,   239,   240,   241,
     242,   784,    86,   279,   321,   268,   280,   322,   392,   982,
     393,   394,   464,   465,   868,   395,   396,   397,  1357,  1358,
    1359,   269,   476,  1114,   270,   271,  1115,   477,   281,   323,
     129,   282,   324,   799,    48,   136,   137,   392,   283,   325,
     436,   437,   163,   284,   326,   335,   352,   938,   550,   285,
     327,   854,   855,   551,   287,   328,   288,   329,   557,   289,
     330,   290,   331,   558,   136,   137,   571,   291,   332,   336,
     353,   572,  1121,   292,   333,  1122,   136,   137,   293,   334,
     276,   136,   137,   277,   575,   278,   286,   582,   294,   576,
     295,   296,   583,    50,   136,   137,   306,   613,   307,   136,
     137,   308,   614,   623,   337,   354,   951,   952,   624,   338,
     355,   863,   864,   865,   866,   867,   868,   869,   870,   871,
     872,   873,   874,   875,   876,   877,    52,    54,    56,   878,
     879,   880,   881,   882,   883,   884,   885,   886,   887,   888,
     889,    58,    60,   392,  1413,  1414,  1415,   983,   984,   985,
     986,    62,  1504,  1505,   627,    64,   880,   881,   882,   628,
     130,   163,   136,   137,    66,    89,  1332,   550,  1333,  1334,
     136,   137,  1068,  1169,   392,   470,  1170,    98,    99,   100,
     101,   102,   103,   346,   347,   348,   349,   350,   136,   137,
     163,   471,   473,    34,    35,    36,    37,  1249,  1250,  1251,
    1259,  1265,   163,   627,   260,   261,   262,   163,  1069,   130,
     392,   263,   319,   827,   828,   829,   998,   999,  1000,  1472,
     163,   472,  1473,   474,   130,   163,   136,   137,   835,   836,
     837,   838,   937,   944,   557,   945,   484,   136,   137,  1070,
     136,   137,   946,  1093,   592,  1451,  1093,   593,  1094,   849,
    1208,  1095,   136,   137,   485,   988,  1272,  1273,  1274,  1275,
     486,  1118,   594,   487,  1135,  1017,  1119,  1017,   367,  1136,
    1142,  1018,  1147,  1018,  1019,  1143,  1019,  1148,   368,   369,
     370,   371,   372,   373,   374,  1009,   488,   489,   163,  1010,
    1011,  1012,  1013,  1156,   602,   490,   163,   491,  1157,  1014,
    1015,   115,   116,   117,   118,   119,   120,   121,  1165,   123,
     124,   125,   126,  1166,   163,   492,   130,  1035,  1036,  1037,
     968,   969,   970,   971,   972,   973,   493,   163,   494,   495,
     134,   883,   884,   885,   886,   887,   888,   318,   623,   609,
     496,  1172,  1093,  1167,   136,   137,  1173,  1366,   571,  1370,
     613,  1156,   163,  1367,  1371,  1381,  1395,   497,   499,  1401,
     260,   261,   262,   163,  1402,   575,  1038,   263,   319,   582,
    1404,   629,   630,   500,  1405,  1387,  1388,  1389,   163,   392,
     414,   393,   394,   415,   416,   417,  1439,  1469,  1502,   164,
    1524,  1440,  1470,  1503,   501,  1525,   243,   793,   794,   795,
     796,  1382,  1383,  1384,   639,   502,   136,   137,   503,   507,
     265,   508,   509,   510,   320,   511,   512,   513,   517,   524,
     525,   351,   418,   316,   272,   251,   526,   273,   536,   357,
     544,   545,   375,   546,   549,   553,   554,   555,   556,   313,
     156,   157,   398,   344,   564,   565,   274,   574,   578,   419,
     358,   580,   311,   581,   252,   421,   339,   597,   399,   422,
     601,   377,   451,   356,   603,   420,   275,   605,   314,   606,
     163,   412,   345,   607,   376,   610,   640,   615,   434,   359,
     617,   619,   620,   626,   632,   266,   631,   633,   634,   635,
     378,   452,   636,   267,   637,   638,   641,   653,   642,   659,
     413,   279,   648,   268,   280,   321,   643,   435,   322,   644,
     660,   645,   646,   661,   651,   647,   649,   650,   652,   269,
     453,   654,   270,   271,   656,   669,   281,   664,   655,   282,
     323,   657,   163,   324,   670,   665,   283,   136,   137,   666,
     325,   284,   658,   662,   663,   326,   335,   285,   667,   668,
     671,   327,   287,   352,   288,   672,   328,   289,   329,   290,
     673,   330,   674,   331,   675,   291,   676,   677,   678,   332,
     336,   292,   679,   680,   682,   333,   293,   353,   276,   683,
     334,   277,   684,   278,   286,   681,   294,   685,   295,   296,
     686,   687,   688,   689,   306,   690,   307,   692,   691,   308,
     693,   694,   695,   696,   697,   337,   698,   699,   700,   702,
     338,   164,   354,   701,   243,   703,   705,   355,   443,   444,
     445,   446,   447,   448,   449,   450,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
     706,   707,   711,   251,   708,   712,   713,   709,   714,   987,
    1001,  1016,   715,   717,   451,   718,   719,   720,  1052,   716,
     721,   722,   724,   163,   727,   729,   725,   733,   734,   728,
     735,   859,   252,   736,   737,   738,   730,   731,   989,  1007,
    1020,   739,  1039,   452,    92,    93,   740,   742,    94,   743,
     745,   744,   746,   747,    95,    96,    97,   748,   750,   754,
     751,   752,   753,   756,   757,   759,   760,   990,  1008,  1021,
     762,  1040,   453,   765,   766,   761,   763,   768,   771,   772,
     778,   788,   764,   769,   774,   775,   773,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     776,   777,   779,   786,   787,   789,   790,   791,   792,   798,
     131,   132,   133,   134,    32,   801,   802,   803,   135,   804,
     805,   806,   807,   808,   816,   813,   809,   136,   137,   810,
     811,   812,   814,   815,   138,   139,   140,   141,   142,   143,
     144,   817,   818,   145,   820,   819,   822,   823,   824,   825,
     831,   826,   146,   830,   832,   857,   833,   834,   858,   839,
     840,   147,   841,   917,   148,   842,   921,   925,   929,   933,
     843,   149,   844,   957,   845,   846,   960,   964,  1031,   150,
     151,   847,  1048,   848,   152,   153,   850,   852,   853,  1057,
    1061,   368,  1075,  1076,  1077,  1078,  1079,  1080,  1081,  1082,
    1083,  1084,  1086,   154,  1087,  1097,  1098,   155,  1100,  1101,
    1103,  1104,  1107,  1106,  1110,  1174,  1109,  1125,  1113,  1124,
    1128,  1127,  1129,   156,   157,   158,   159,   160,   161,  1130,
    1131,  1132,  1133,  1134,  1139,  1140,  1141,   162,  1144,  1145,
    1146,  1152,  1154,  1160,  1179,  1159,  1161,  1163,  1171,  1189,
    1182,  1178,  1181,   163,  1185,  1184,  1183,  1186,  1187,  1188,
    1191,  1190,  1193,  1192,  1199,  1194,  1202,  1203,  1195,  1204,
    1205,  1196,  1197,  1198,  1206,  1269,  1200,  1201,   265,  1270,
    1307,   398,  1300,  1308,   419,  1301,  1302,  1216,  1303,  1304,
     421,   316,   272,  1317,   422,   273,  1318,   399,  1319,  1276,
     420,  1223,   375,  1248,  1224,   438,  1305,   313,  1309,  1310,
     412,  1311,  1313,   434,   274,  1283,  1263,  1314,  1315,  1320,
     311,   987,  1321,  1225,  1322,  1323,  1001,  1327,  1285,  1262,
    1328,   377,  1329,  1330,   275,  1016,   314,  1016,  1345,   413,
    1347,  1284,   435,  1226,   376,  1264,  1348,  1335,  1353,  1354,
     989,  1052,  1368,   266,  1369,  1007,   320,  1286,  1376,   351,
     378,   267,  1217,  1336,  1020,  1377,  1020,   357,  1355,   279,
    1218,   268,   280,  1039,  1277,  1356,  1337,  1378,  1230,   990,
    1219,  1231,  1278,  1379,  1008,   344,  1361,   269,   358,  1362,
     270,   271,  1279,  1021,   281,  1021,  1220,   282,   339,  1221,
    1222,   356,  1040,  1232,   283,  1338,  1233,  1363,  1280,   284,
    1380,  1281,  1282,  1234,   345,   285,  1365,   359,  1235,  1252,
     287,  1372,   288,  1393,  1236,   289,  1373,   290,  1394,  1238,
    1399,  1239,  1407,   291,  1240,  1408,  1241,  1425,  1429,   292,
    1431,  1386,  1242,  1253,   293,  1391,   276,   321,  1243,   277,
     322,   278,   286,  1244,   294,  1227,   295,   296,  1228,  1392,
    1229,  1237,   306,  1245,   307,  1246,  1247,   308,  1442,  1443,
    1444,  1256,   323,  1257,  1430,   324,  1258,  1446,  1254,  1447,
    1448,  1449,   325,  1255,  1463,  1460,  1467,   326,   335,  1474,
    1478,   352,  1396,   327,  1409,  1494,  1403,  1433,   328,  1434,
     329,  1410,  1495,   330,  1445,   331,  1498,  1465,  1466,  1496,
    1499,   332,   336,  1500,  1516,   353,  1517,   333,  1518,  1519,
    1520,  1526,   334,  1527,  1528,  1529,  1531,  1532,   710,   943,
     704,   860,   862,  1209,   851,  1067,  1207,  1364,  1271,  1267,
    1316,  1299,  1298,  1306,  1268,  1211,  1210,   337,   723,  1216,
     354,  1266,   338,  1406,  1213,   355,   390,   758,  1276,  1212,
     749,  1215,  1350,  1223,   755,  1248,  1224,  1214,  1349,   726,
    1397,  1352,  1416,  1297,  1283,  1312,  1296,  1351,  1263,   741,
    1335,   732,  1411,  1326,  1459,  1225,  1295,  1285,  1324,  1325,
    1479,  1262,  1065,  1450,  1515,  1530,  1336,  1047,  1432,   767,
    1284,  1417,  1331,   861,  1492,  1226,   770,  1264,  1344,  1337,
    1521,     0,     0,     0,  1346,     0,  1286,     0,  1416,     0,
    1452,     0,     0,     0,  1217,     0,     0,     0,     0,     0,
    1418,     0,  1218,  1277,     0,     0,  1453,     0,  1338,     0,
    1230,  1278,  1219,  1231,     0,     0,     0,  1417,  1452,  1454,
       0,  1279,     0,     0,     0,     0,     0,     0,  1220,     0,
       0,  1221,  1222,     0,  1453,  1232,     0,  1280,  1233,     0,
    1281,  1282,  1506,     0,     0,  1234,  1418,  1454,  1455,     0,
    1235,  1252,     0,     0,     0,     0,  1236,     0,     0,     0,
       0,  1238,     0,  1239,     0,     0,  1240,     0,  1241,     0,
       0,  1509,     0,  1506,  1242,  1253,  1455,     0,     0,     0,
    1243,     0,     0,     0,     0,  1244,     0,  1227,     0,     0,
    1228,     0,  1229,  1237,     0,  1245,     0,  1246,  1247,     0,
    1510,     0,  1509,  1256,     0,  1257,     0,     0,  1258,     0,
    1254,     0,     0,     0,     0,  1255,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,     0,
       0,  1510,     0,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,     0,     0,   130,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     132,   133,   134,     0,     0,     0,     0,     0,   253,     0,
     254,     0,     0,     0,     0,     0,   136,   137,   255,   256,
     257,   258,   259,   138,   139,   140,     0,     0,     0,     0,
       0,     0,   260,   261,   262,     0,     0,     0,     0,   263,
       0,   146,     0,     0,     0,     0,     0,     0,     0,   264,
       0,     0,     0,     0,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,     0,     0,     0,
       0,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,     0,   130,   392,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   132,   133,
     134,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   156,   157,   136,   137,     0,   256,   257,     0,
     259,   138,   139,   140,     0,     0,     0,     0,     0,     0,
     260,   261,   262,     0,     0,     0,     0,   263,     0,     0,
       0,     0,   163,     0,     0,     0,     0,   264,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     156,   157,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     163
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   812,    75,   810,    79,    73,    73,   812,    79,    73,
     812,   777,   804,    78,    79,  1108,  1108,  1108,  1108,  1108,
      72,    73,    74,    75,    76,    24,    78,    79,    73,    81,
     143,   149,   150,   677,    73,    74,    75,    76,     5,  1493,
       7,     0,     9,  1493,   206,   207,   208,   209,    73,    72,
      73,    74,    75,    76,   225,    78,    79,   217,    81,     7,
     220,   221,   222,   223,     7,     3,    24,    73,     6,   240,
    1524,     7,    25,    26,  1524,    73,    16,    17,    18,    19,
      20,   243,   240,    73,    74,    73,    73,    74,    87,    24,
      89,    90,    13,    14,    29,    94,    95,    96,    39,    40,
      41,    73,     3,     3,    73,    73,     6,     8,    73,    74,
      85,    73,    74,   757,     7,   114,   115,    87,    73,    74,
     149,   150,   240,    73,    74,    74,    75,   240,     3,    73,
      74,   203,   204,     8,    73,    74,    73,    74,     3,    73,
      74,    73,    74,     8,   114,   115,     3,    73,    74,    74,
      75,     8,     3,    73,    74,     6,   114,   115,    73,    74,
      73,   114,   115,    73,     3,    73,    73,     3,    73,     8,
      73,    73,     8,     7,   114,   115,    73,     3,    73,   114,
     115,    73,     8,     3,    74,    75,   128,   129,     8,    74,
      75,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,     7,     7,     7,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,     7,     7,    87,   182,   183,   184,   162,   163,   164,
     165,     7,   185,   186,     3,     7,    44,    45,    46,     8,
      86,   240,   114,   115,     7,    10,   216,     3,   218,   219,
     114,   115,     8,     3,    87,     6,     6,    54,    55,    56,
      57,    58,    59,   109,   110,   111,   112,   113,   114,   115,
     240,     3,     8,   240,   241,   242,   243,  1370,  1370,  1370,
    1370,  1370,   240,     3,   130,   131,   132,   240,     8,    86,
      87,   137,   138,   718,   719,   720,   168,   169,   170,     3,
     240,     4,     6,     3,    86,   240,   114,   115,   733,   734,
     735,   736,   143,   144,     3,   146,     4,   114,   115,     8,
     114,   115,  1114,     3,     8,   189,     3,     3,     8,   754,
    1096,     8,   114,   115,     4,  1142,   133,   134,   135,   136,
       4,     3,     8,     4,     3,  1156,     8,  1158,   130,     8,
       3,  1156,     3,  1158,  1156,     8,  1158,     8,   140,   141,
     142,   143,   144,   145,   146,   173,     4,     4,   240,   177,
     178,   179,   180,     3,     8,     4,   240,     4,     8,   187,
     188,    71,    72,    73,    74,    75,    76,    77,     3,    79,
      80,    81,    82,     8,   240,     4,    86,   191,   192,   193,
     152,   153,   154,   155,   156,   157,     4,   240,     4,     4,
     100,    47,    48,    49,    50,    51,    52,   107,     3,     8,
       4,     3,     3,     8,   114,   115,     8,     8,     3,     3,
       3,     3,   240,     8,     8,     8,     8,     4,     4,     3,
     130,   131,   132,   240,     8,     3,   240,   137,   138,     3,
       8,   471,   472,     4,     8,   174,   175,   176,   240,    87,
      88,    89,    90,    91,    92,    93,     3,     3,     3,   550,
       3,     8,     8,     8,     4,     8,   557,   101,   102,   103,
     104,   159,   160,   161,   241,     4,   114,   115,     4,     4,
     571,     4,     4,     4,   575,     4,     4,     4,     4,     4,
       4,   582,   130,   571,   571,   557,     4,   571,     4,   582,
       4,     4,   593,     4,     4,     4,     4,     4,     4,   571,
     210,   211,   603,   575,     4,     4,   571,     4,     4,   610,
     582,     4,   571,     4,   557,   610,   575,     4,   603,   610,
       4,   593,   623,   582,     3,   610,   571,     4,   571,     4,
     240,   603,   575,     4,   593,     3,   241,     4,   610,   582,
       4,     4,     4,     4,     4,   571,   240,     4,     4,     4,
     593,   623,     4,   571,     4,     4,   241,     4,   241,     4,
     603,   571,   242,   571,   571,   575,   241,   610,   575,   241,
       4,   241,   241,     4,   241,   243,   242,   242,   241,   571,
     623,   241,   571,   571,   243,     4,   571,   242,   241,   571,
     575,   243,   240,   575,     4,   241,   571,   114,   115,   241,
     575,   571,   243,   243,   243,   575,   575,   571,   241,   243,
       4,   575,   571,   582,   571,   241,   575,   571,   575,   571,
       4,   575,     4,   575,     4,   571,     4,     4,     4,   575,
     575,   571,   243,   243,     4,   575,   571,   582,   571,     4,
     575,   571,     4,   571,   571,   243,   571,     4,   571,   571,
       4,     4,     4,     4,   571,     4,   571,     4,   241,   571,
       4,     4,     4,     4,     4,   575,     4,   243,   243,     4,
     575,   772,   582,   243,   775,     4,     4,   582,   195,   196,
     197,   198,   199,   200,   201,   202,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     243,   243,     4,   775,   241,     4,     4,   241,     4,   810,
     811,   812,     4,   243,   815,     4,     4,     4,   819,   241,
       4,     4,     4,   240,     4,     4,   241,     4,     4,   241,
       4,   771,   775,     4,     4,     4,   241,   241,   810,   811,
     812,     4,   814,   815,    11,    12,     4,     4,    15,     4,
       4,   241,     4,     4,    21,    22,    23,   243,     4,     4,
     243,   243,   243,     4,     4,   243,     4,   810,   811,   812,
       4,   814,   815,     4,     4,   241,   241,     4,     4,     7,
       5,     5,   241,   241,     7,     7,   240,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
       7,     7,   240,   240,   240,     5,     5,   240,   240,     5,
      97,    98,    99,   100,     7,   240,     5,     5,   105,     5,
       7,     5,     5,     5,   240,     5,     7,   114,   115,     7,
       7,     7,     7,     7,   121,   122,   123,   124,   125,   126,
     127,   240,     5,   130,     5,     7,     5,     5,   240,   240,
       7,   240,   139,   240,   240,   205,   240,   240,     5,   240,
     240,   148,   240,     7,   151,   240,     7,     7,     7,     7,
     240,   158,   240,     7,   240,   240,     7,     7,     7,   166,
     167,   240,     7,   240,   171,   172,   240,   240,   240,     7,
       7,   140,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   190,     4,     6,     3,   194,     6,     3,
       6,     3,     3,     6,     3,   240,     6,     3,     6,     6,
       3,     6,     4,   210,   211,   212,   213,   214,   215,     4,
       4,     4,     4,     4,     4,     4,     4,   224,     4,     4,
       4,     4,     4,     3,     3,     6,     4,     4,     4,   241,
       3,     6,     6,   240,     4,     6,     8,     4,     4,     4,
     241,   243,   241,   243,     4,   241,     4,     4,   241,     4,
       4,   241,   241,   241,     4,     4,   243,   241,  1099,     4,
       4,  1102,   241,     4,  1105,   241,   241,  1108,   241,   241,
    1105,  1099,  1099,     4,  1105,  1099,     4,  1102,     4,  1120,
    1105,  1108,  1123,  1108,  1108,  1126,   241,  1099,   241,   241,
    1102,   241,   243,  1105,  1099,  1120,  1108,   241,   241,   241,
    1099,  1142,     4,  1108,   243,     4,  1147,   243,  1120,  1108,
       4,  1123,   241,     4,  1099,  1156,  1099,  1158,   243,  1102,
       6,  1120,  1105,  1108,  1123,  1108,     3,  1168,   240,   240,
    1142,  1172,     8,  1099,     8,  1147,  1177,  1120,     4,  1180,
    1123,  1099,  1108,  1168,  1156,     4,  1158,  1180,   240,  1099,
    1108,  1099,  1099,  1165,  1120,   240,  1168,     8,  1108,  1142,
    1108,  1108,  1120,     3,  1147,  1177,   240,  1099,  1180,   240,
    1099,  1099,  1120,  1156,  1099,  1158,  1108,  1099,  1177,  1108,
    1108,  1180,  1165,  1108,  1099,  1168,  1108,   240,  1120,  1099,
       8,  1120,  1120,  1108,  1177,  1099,   240,  1180,  1108,  1108,
    1099,   240,  1099,     7,  1108,  1099,   240,  1099,     5,  1108,
       4,  1108,     4,  1099,  1108,     4,  1108,     7,     4,  1099,
       4,   240,  1108,  1108,  1099,   240,  1099,  1177,  1108,  1099,
    1177,  1099,  1099,  1108,  1099,  1108,  1099,  1099,  1108,   240,
    1108,  1108,  1099,  1108,  1099,  1108,  1108,  1099,     6,     3,
       5,  1108,  1177,  1108,   241,  1177,  1108,     4,  1108,     4,
       4,     4,  1177,  1108,   181,     7,     5,  1177,  1177,     7,
       4,  1180,   240,  1177,   243,     6,   240,   240,  1177,   240,
    1177,   243,     3,  1177,   240,  1177,     4,   240,   240,   240,
       4,  1177,  1177,     4,     4,  1180,   243,  1177,   241,   241,
       4,   240,  1177,   240,     4,     4,   240,   240,   557,   803,
     550,   772,   775,  1098,   757,   858,  1093,  1205,  1118,  1111,
    1147,  1128,  1126,  1135,  1114,  1101,  1099,  1177,   571,  1370,
    1180,  1110,  1177,  1370,  1104,  1180,    77,   613,  1379,  1102,
     603,  1107,  1179,  1370,   610,  1370,  1370,  1105,  1177,   575,
    1330,  1182,  1393,  1125,  1379,  1142,  1123,  1180,  1370,   593,
    1401,   582,  1379,  1160,  1443,  1370,  1121,  1379,  1156,  1158,
    1469,  1370,   831,  1439,  1495,  1524,  1401,   815,  1401,   623,
    1379,  1393,  1165,   774,  1472,  1370,   627,  1370,  1169,  1401,
    1502,    -1,    -1,    -1,  1172,    -1,  1379,    -1,  1439,    -1,
    1441,    -1,    -1,    -1,  1370,    -1,    -1,    -1,    -1,    -1,
    1393,    -1,  1370,  1379,    -1,    -1,  1441,    -1,  1401,    -1,
    1370,  1379,  1370,  1370,    -1,    -1,    -1,  1439,  1469,  1441,
      -1,  1379,    -1,    -1,    -1,    -1,    -1,    -1,  1370,    -1,
      -1,  1370,  1370,    -1,  1469,  1370,    -1,  1379,  1370,    -1,
    1379,  1379,  1493,    -1,    -1,  1370,  1439,  1469,  1441,    -1,
    1370,  1370,    -1,    -1,    -1,    -1,  1370,    -1,    -1,    -1,
      -1,  1370,    -1,  1370,    -1,    -1,  1370,    -1,  1370,    -1,
      -1,  1493,    -1,  1524,  1370,  1370,  1469,    -1,    -1,    -1,
    1370,    -1,    -1,    -1,    -1,  1370,    -1,  1370,    -1,    -1,
    1370,    -1,  1370,  1370,    -1,  1370,    -1,  1370,  1370,    -1,
    1493,    -1,  1524,  1370,    -1,  1370,    -1,    -1,  1370,    -1,
    1370,    -1,    -1,    -1,    -1,  1370,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    -1,
      -1,  1524,    -1,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    -1,    -1,    86,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      98,    99,   100,    -1,    -1,    -1,    -1,    -1,   106,    -1,
     108,    -1,    -1,    -1,    -1,    -1,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,    -1,    -1,    -1,    -1,
      -1,    -1,   130,   131,   132,    -1,    -1,    -1,    -1,   137,
      -1,   139,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   147,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    -1,    -1,    -1,
      -1,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    -1,    86,    87,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    99,
     100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   210,   211,   114,   115,    -1,   117,   118,    -1,
     120,   121,   122,   123,    -1,    -1,    -1,    -1,    -1,    -1,
     130,   131,   132,    -1,    -1,    -1,    -1,   137,    -1,    -1,
      -1,    -1,   240,    -1,    -1,    -1,    -1,   147,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     210,   211,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     240
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
       0,     5,     7,     9,   240,   241,   242,   243,   260,   261,
     262,   267,     7,   276,     7,   281,     7,   339,     7,   455,
       7,   539,     7,   556,     7,   573,     7,   488,     7,   494,
       7,   518,     7,   431,     7,   689,     7,   708,   268,   263,
     277,   282,   340,   456,   540,   557,   574,   489,   495,   519,
     432,   690,   709,   260,   269,   270,   240,   265,   266,    10,
     278,   280,    11,    12,    15,    21,    22,    23,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    97,    98,    99,   100,   105,   114,   115,   121,   122,
     123,   124,   125,   126,   127,   130,   139,   148,   151,   158,
     166,   167,   171,   172,   190,   194,   210,   211,   212,   213,
     214,   215,   224,   240,   275,   283,   284,   285,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   307,   309,   311,   312,
     313,   316,   317,   318,   319,   320,   322,   324,   325,   326,
     327,   329,   330,   332,   334,   335,   336,   337,   349,   351,
     353,   396,   404,   410,   416,   418,   425,   439,   449,   473,
     474,   475,   478,   486,   512,   546,   548,   567,   597,   612,
     624,   625,   627,   677,   687,   706,   715,   739,    16,    17,
      18,    19,    20,   275,   341,   342,   343,   345,   346,   347,
     348,   546,   548,   106,   108,   116,   117,   118,   119,   120,
     130,   131,   132,   137,   147,   275,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   301,
     302,   303,   304,   307,   309,   311,   312,   313,   316,   317,
     318,   319,   320,   322,   324,   330,   332,   457,   458,   459,
     461,   463,   465,   467,   469,   471,   473,   474,   475,   476,
     477,   512,   533,   546,   548,   550,   567,   594,   107,   138,
     275,   301,   302,   303,   304,   307,   309,   311,   313,   316,
     317,   318,   319,   320,   322,   465,   467,   469,   471,   512,
     541,   542,   543,   545,   546,   548,   109,   110,   111,   112,
     113,   275,   465,   467,   469,   471,   512,   545,   546,   548,
     558,   559,   560,   562,   563,   565,   566,   130,   140,   141,
     142,   143,   144,   145,   146,   275,   512,   546,   548,   575,
     576,   577,   578,   580,   582,   584,   586,   588,   590,   592,
     486,    24,    87,    89,    90,    94,    95,    96,   275,   370,
     496,   497,   498,   499,   500,   501,   502,   504,   506,   508,
     509,   511,   546,   548,    88,    91,    92,    93,   130,   275,
     370,   500,   506,   520,   521,   522,   523,   524,   526,   527,
     528,   529,   530,   531,   546,   548,   149,   150,   275,   433,
     434,   435,   437,   195,   196,   197,   198,   199,   200,   201,
     202,   275,   546,   548,   691,   692,   693,   694,   696,   697,
     699,   700,   701,   704,    13,    14,   710,   711,   712,   714,
       6,     3,     4,     8,     3,   279,     3,     8,   286,   707,
     338,   350,   352,   354,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   328,     4,
       4,     4,     4,     4,   305,   308,   310,     4,     4,     4,
       4,     4,     4,     4,   450,   487,   513,     4,   331,   333,
     314,   479,   547,   549,     4,     4,     4,   405,   417,   411,
     397,   598,   568,   426,   440,   613,     4,   419,   626,   628,
     678,   688,   321,   323,     4,     4,     4,   716,   740,     4,
       3,     8,   344,     4,     4,     4,     4,     3,     8,   534,
     551,   460,   462,   464,     4,     4,   468,   470,   472,   466,
     595,     3,     8,   544,     4,     3,     8,   561,     4,   564,
       4,     4,     3,     8,   593,   579,   581,   583,   585,   587,
     589,   591,     8,     3,     8,   503,   371,     4,   507,   505,
     510,     4,     8,     3,   525,     4,     4,     4,   532,     8,
       3,   436,   438,     3,     8,     4,   695,     4,   698,     4,
       4,   702,   705,     3,     8,   713,     4,     3,     8,   260,
     260,   240,     4,     4,     4,     4,     4,     4,     4,   241,
     241,   241,   241,   241,   241,   241,   241,   243,   242,   242,
     242,   241,   241,     4,   241,   241,   243,   243,   243,     4,
       4,     4,   243,   243,   242,   241,   241,   241,   243,     4,
       4,     4,   241,     4,     4,     4,     4,     4,     4,   243,
     243,   243,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   241,     4,     4,     4,     4,     4,     4,     4,   243,
     243,   243,     4,     4,   284,     4,   243,   243,   241,   241,
     342,     4,     4,     4,     4,     4,   241,   243,     4,     4,
       4,     4,     4,   458,     4,   241,   542,     4,   241,     4,
     241,   241,   559,     4,     4,     4,     4,     4,     4,     4,
       4,   577,     4,     4,   241,     4,     4,     4,   243,   498,
       4,   243,   243,   243,     4,   522,     4,     4,   434,   243,
       4,   241,     4,   241,   241,     4,     4,   692,     4,   241,
     711,     4,     7,   240,     7,     7,     7,     7,     5,   240,
     206,   207,   208,   209,   243,   306,   240,   240,     5,     5,
       5,   240,   240,   101,   102,   103,   104,   315,     5,   262,
     264,   240,     5,     5,     5,     7,     5,     5,     5,     7,
       7,     7,     7,     5,     7,     7,   240,   240,     5,     7,
       5,   271,     5,     5,   240,   240,   240,   271,   271,   271,
     240,     7,   240,   240,   240,   271,   271,   271,   271,   240,
     240,   240,   240,   240,   240,   240,   240,   240,   240,   271,
     240,   264,   240,   240,   203,   204,   703,   205,     5,   260,
     283,   710,   341,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
     275,   359,   360,   361,   363,   365,   367,   369,   370,   372,
     373,   374,   375,   376,   377,   378,   379,   380,   383,   384,
     385,   386,   388,   390,   392,   394,   359,     7,   355,   356,
     357,     7,   451,   452,   453,     7,   490,   491,   492,     7,
     514,   515,   516,     7,   480,   481,   482,   143,   240,   406,
     407,   408,   409,   269,   144,   146,   408,   412,   413,   414,
     415,   128,   129,   398,   399,   400,   402,     7,   599,   600,
       7,   569,   570,   571,     7,   427,   428,   429,   152,   153,
     154,   155,   156,   157,   441,   442,   443,   444,   445,   446,
     447,   448,    24,   162,   163,   164,   165,   275,   372,   546,
     548,   614,   615,   616,   619,   620,   622,   623,   168,   169,
     170,   275,   420,   421,   422,   423,   424,   546,   548,   173,
     177,   178,   179,   180,   187,   188,   275,   386,   388,   390,
     546,   548,   633,   634,   635,   638,   640,   642,   643,   644,
     654,     7,   629,   630,   631,   191,   192,   193,   240,   546,
     548,   679,   680,   681,   682,   684,   685,   691,     7,   717,
     718,   225,   275,   741,   742,   743,   272,     7,   535,   536,
     537,     7,   552,   553,   554,   578,   596,   355,     8,     8,
       8,   362,   364,   366,   368,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   381,     4,     4,   387,   389,
     391,   393,   395,     3,     8,     8,   358,     6,     3,   454,
       6,     3,   493,     6,     3,   517,     6,     3,   483,     6,
       3,     3,     6,     6,     3,     6,   401,   403,     3,     8,
     601,     3,     6,   572,     6,     3,   430,     6,     3,     4,
       4,     4,     4,     4,     4,     3,     8,   617,   621,     4,
       4,     4,     3,     8,     4,     4,     4,     3,     8,   636,
     639,   641,     4,   655,     4,   645,     3,     8,   632,     6,
       3,     4,   683,     4,   686,     3,     8,     8,   719,     3,
       6,     4,     3,     8,   240,   273,   274,   538,     6,     3,
     555,     6,     3,     8,     6,     4,     4,     4,     4,   241,
     243,   241,   243,   241,   241,   241,   241,   241,   241,     4,
     243,   241,     4,     4,     4,     4,     4,   360,   359,   357,
     457,   453,   496,   492,   520,   516,   275,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     301,   302,   303,   304,   307,   309,   311,   312,   313,   316,
     317,   318,   319,   320,   322,   324,   330,   332,   370,   449,
     461,   463,   465,   467,   469,   471,   473,   474,   475,   477,
     484,   485,   512,   546,   548,   594,   482,   407,   413,     4,
       4,   399,   133,   134,   135,   136,   275,   287,   288,   289,
     290,   291,   292,   370,   512,   546,   548,   602,   603,   604,
     605,   606,   608,   610,   611,   600,   575,   571,   433,   429,
     241,   241,   241,   241,   241,   241,   442,     4,     4,   241,
     241,   241,   615,   243,   241,   241,   421,     4,     4,     4,
     241,     4,   243,     4,   634,   633,   631,   243,     4,   241,
       4,   680,   216,   218,   219,   275,   370,   546,   548,   720,
     721,   722,   723,   725,   718,   243,   742,     6,     3,   541,
     537,   558,   554,   240,   240,   240,   240,    39,    40,    41,
     382,   240,   240,   240,   392,   240,     8,     8,     8,     8,
       3,     8,   240,   240,   607,   609,     4,     4,     8,     3,
       8,     8,   159,   160,   161,   618,   240,   174,   175,   176,
     637,   240,   240,     7,     5,     8,   240,   260,   726,     4,
     724,     3,     8,   240,     8,     8,   485,     4,     4,   243,
     243,   604,    24,   182,   183,   184,   275,   546,   548,   656,
     657,   658,   661,   663,   665,     7,   646,   647,   648,     4,
     241,     4,   721,   240,   240,   659,   662,   664,   666,     3,
       8,   649,     6,     3,     5,   240,     4,     4,     4,     4,
     657,   189,   275,   370,   546,   548,   650,   651,   652,   648,
       7,   727,   728,   181,   660,   240,   240,     5,   653,     3,
       8,   729,     3,     6,     7,   667,   668,   669,     4,   651,
     217,   220,   221,   222,   223,   730,   731,   732,   734,   735,
     736,   737,   728,   670,     6,     3,   240,   733,     4,     4,
       4,   738,     3,     8,   185,   186,   275,   363,   365,   546,
     548,   671,   672,   673,   675,   669,     4,   243,   241,   241,
       4,   731,   674,   676,     3,     8,   240,   240,     4,     4,
     672,   240,   240
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   244,   246,   245,   247,   245,   248,   245,   249,   245,
     250,   245,   251,   245,   252,   245,   253,   245,   254,   245,
     255,   245,   256,   245,   257,   245,   258,   245,   259,   245,
     260,   260,   260,   260,   260,   260,   260,   261,   263,   262,
     264,   265,   265,   266,   266,   266,   268,   267,   269,   269,
     270,   270,   270,   272,   271,   273,   273,   274,   274,   274,
     275,   277,   276,   279,   278,   278,   280,   282,   281,   283,
     283,   283,   284,   284,   284,   284,   284,   284,   284,   284,
     284,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     284,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     284,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     284,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     284,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     284,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     284,   284,   284,   284,   286,   285,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   305,   304,   306,   306,   306,   306,   306,
     308,   307,   310,   309,   311,   312,   314,   313,   315,   315,
     315,   315,   316,   317,   318,   319,   321,   320,   323,   322,
     324,   325,   326,   328,   327,   329,   331,   330,   333,   332,
     334,   335,   336,   338,   337,   340,   339,   341,   341,   341,
     342,   342,   342,   342,   342,   342,   342,   342,   344,   343,
     345,   346,   347,   348,   350,   349,   352,   351,   354,   353,
     355,   355,   356,   356,   356,   358,   357,   359,   359,   359,
     360,   360,   360,   360,   360,   360,   360,   360,   360,   360,
     360,   360,   360,   360,   360,   360,   360,   360,   360,   360,
     360,   360,   360,   360,   362,   361,   364,   363,   366,   365,
     368,   367,   369,   371,   370,   372,   373,   374,   375,   376,
     377,   378,   379,   381,   380,   382,   382,   382,   383,   384,
     385,   387,   386,   389,   388,   391,   390,   393,   392,   392,
     392,   392,   392,   392,   395,   394,   397,   396,   398,   398,
     398,   399,   399,   401,   400,   403,   402,   405,   404,   406,
     406,   406,   407,   407,   408,   409,   411,   410,   412,   412,
     412,   413,   413,   413,   414,   415,   417,   416,   419,   418,
     420,   420,   420,   421,   421,   421,   421,   421,   421,   422,
     423,   424,   426,   425,   427,   427,   428,   428,   428,   430,
     429,   432,   431,   433,   433,   433,   433,   434,   434,   436,
     435,   438,   437,   440,   439,   441,   441,   441,   442,   442,
     442,   442,   442,   442,   443,   444,   445,   446,   447,   448,
     450,   449,   451,   451,   452,   452,   452,   454,   453,   456,
     455,   457,   457,   457,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   458,   460,   459,   462,   461,   464,
     463,   466,   465,   468,   467,   470,   469,   472,   471,   473,
     474,   475,   476,   477,   479,   478,   480,   480,   481,   481,
     481,   483,   482,   484,   484,   484,   485,   485,   485,   485,
     485,   485,   485,   485,   485,   485,   485,   485,   485,   485,
     485,   485,   485,   485,   485,   485,   485,   485,   485,   485,
     485,   485,   485,   485,   485,   485,   485,   485,   485,   485,
     485,   485,   485,   485,   485,   485,   485,   485,   485,   485,
     485,   485,   485,   485,   487,   486,   489,   488,   490,   490,
     491,   491,   491,   493,   492,   495,   494,   496,   496,   497,
     497,   497,   498,   498,   498,   498,   498,   498,   498,   498,
     498,   498,   499,   500,   501,   503,   502,   505,   504,   507,
     506,   508,   510,   509,   511,   513,   512,   514,   514,   515,
     515,   515,   517,   516,   519,   518,   520,   520,   521,   521,
     521,   522,   522,   522,   522,   522,   522,   522,   522,   522,
     522,   522,   523,   525,   524,   526,   527,   528,   529,   530,
     532,   531,   534,   533,   535,   535,   536,   536,   536,   538,
     537,   540,   539,   541,   541,   541,   542,   542,   542,   542,
     542,   542,   542,   542,   542,   542,   542,   542,   542,   542,
     542,   542,   542,   542,   542,   542,   542,   542,   542,   542,
     544,   543,   545,   547,   546,   549,   548,   551,   550,   552,
     552,   553,   553,   553,   555,   554,   557,   556,   558,   558,
     558,   559,   559,   559,   559,   559,   559,   559,   559,   559,
     559,   559,   559,   559,   559,   561,   560,   562,   564,   563,
     565,   566,   568,   567,   569,   569,   570,   570,   570,   572,
     571,   574,   573,   575,   575,   576,   576,   576,   577,   577,
     577,   577,   577,   577,   577,   577,   577,   577,   577,   577,
     579,   578,   581,   580,   583,   582,   585,   584,   587,   586,
     589,   588,   591,   590,   593,   592,   595,   594,   596,   598,
     597,   599,   599,   599,   601,   600,   602,   602,   603,   603,
     603,   604,   604,   604,   604,   604,   604,   604,   604,   604,
     604,   604,   604,   604,   604,   604,   605,   607,   606,   609,
     608,   610,   611,   613,   612,   614,   614,   614,   615,   615,
     615,   615,   615,   615,   615,   615,   615,   617,   616,   618,
     618,   618,   619,   621,   620,   622,   623,   624,   626,   625,
     628,   627,   629,   629,   630,   630,   630,   632,   631,   633,
     633,   633,   634,   634,   634,   634,   634,   634,   634,   634,
     634,   634,   634,   634,   634,   636,   635,   637,   637,   637,
     639,   638,   641,   640,   642,   643,   645,   644,   646,   646,
     647,   647,   647,   649,   648,   650,   650,   650,   651,   651,
     651,   651,   651,   653,   652,   655,   654,   656,   656,   656,
     657,   657,   657,   657,   657,   657,   657,   659,   658,   660,
     662,   661,   664,   663,   666,   665,   667,   667,   668,   668,
     668,   670,   669,   671,   671,   671,   672,   672,   672,   672,
     672,   672,   672,   674,   673,   676,   675,   678,   677,   679,
     679,   679,   680,   680,   680,   680,   680,   680,   681,   683,
     682,   684,   686,   685,   688,   687,   690,   689,   691,   691,
     691,   692,   692,   692,   692,   692,   692,   692,   692,   692,
     692,   692,   693,   695,   694,   696,   698,   697,   699,   700,
     702,   701,   703,   703,   705,   704,   707,   706,   709,   708,
     710,   710,   710,   711,   711,   713,   712,   714,   716,   715,
     717,   717,   717,   719,   718,   720,   720,   720,   721,   721,
     721,   721,   721,   721,   721,   722,   724,   723,   726,   725,
     727,   727,   727,   729,   728,   730,   730,   730,   731,   731,
     731,   731,   731,   733,   732,   734,   735,   736,   738,   737,
     740,   739,   741,   741,   741,   742,   742,   743
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
       3,     0,     4,     0,     4,     0,     4,     0,     4,     1,
       1,     1,     1,     1,     0,     4,     0,     6,     1,     3,
       2,     1,     1,     0,     4,     0,     4,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     1,     0,     6,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     1,     3,     2,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     3,
       3,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     4,     0,     4,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
  "\"trust-anchor\"", "\"cert-file\"", "\"key-file\"", "\"ssl-mode\"",
  "\"disable\"", "\"prefer\"", "\"require\"", "\"verify-ca\"",
  "\"verify-full\"", "\"cipher-list\"", "\"preferred-lifetime\"",
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
       0,   339,   339,   339,   340,   340,   341,   341,   342,   342,
     343,   343,   344,   344,   345,   345,   346,   346,   347,   347,
     348,   348,   349,   349,   350,   350,   351,   351,   352,   352,
     360,   361,   362,   363,   364,   365,   366,   369,   374,   374,
     385,   388,   389,   392,   397,   403,   408,   408,   415,   416,
     419,   423,   427,   433,   433,   440,   441,   444,   448,   452,
     462,   471,   471,   486,   486,   500,   503,   509,   509,   518,
     519,   520,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     555,   556,   557,   558,   559,   560,   561,   562,   563,   564,
     565,   566,   567,   568,   569,   570,   571,   572,   573,   574,
     575,   576,   577,   578,   579,   580,   581,   582,   583,   584,
     585,   586,   587,   588,   589,   590,   591,   592,   593,   594,
     595,   596,   597,   598,   601,   601,   611,   617,   623,   629,
     635,   641,   647,   653,   659,   665,   671,   677,   683,   689,
     695,   701,   707,   713,   713,   722,   725,   728,   731,   734,
     740,   740,   749,   749,   758,   767,   777,   777,   786,   789,
     792,   795,   800,   806,   812,   818,   824,   824,   833,   833,
     842,   848,   854,   860,   860,   869,   875,   875,   884,   884,
     893,   899,   905,   911,   911,   923,   923,   932,   933,   934,
     939,   940,   941,   942,   943,   944,   945,   946,   949,   949,
     960,   966,   972,   978,   984,   984,   997,   997,  1010,  1010,
    1021,  1022,  1025,  1026,  1027,  1032,  1032,  1042,  1043,  1044,
    1049,  1050,  1051,  1052,  1053,  1054,  1055,  1056,  1057,  1058,
    1059,  1060,  1061,  1062,  1063,  1064,  1065,  1066,  1067,  1068,
    1069,  1070,  1071,  1072,  1075,  1075,  1084,  1084,  1093,  1093,
    1102,  1102,  1111,  1117,  1117,  1126,  1132,  1138,  1144,  1150,
    1156,  1162,  1168,  1174,  1174,  1182,  1183,  1184,  1187,  1193,
    1199,  1205,  1205,  1214,  1214,  1223,  1223,  1232,  1232,  1240,
    1241,  1242,  1243,  1244,  1247,  1247,  1256,  1256,  1267,  1268,
    1269,  1274,  1275,  1278,  1278,  1297,  1297,  1315,  1315,  1326,
    1327,  1328,  1333,  1334,  1337,  1342,  1347,  1347,  1358,  1359,
    1360,  1365,  1366,  1367,  1370,  1375,  1382,  1382,  1395,  1395,
    1408,  1409,  1410,  1415,  1416,  1417,  1418,  1419,  1420,  1423,
    1429,  1435,  1441,  1441,  1452,  1453,  1456,  1457,  1458,  1463,
    1463,  1473,  1473,  1483,  1484,  1485,  1488,  1491,  1492,  1495,
    1495,  1504,  1504,  1513,  1513,  1525,  1526,  1527,  1532,  1533,
    1534,  1535,  1536,  1537,  1540,  1546,  1552,  1558,  1564,  1570,
    1579,  1579,  1593,  1594,  1597,  1598,  1599,  1608,  1608,  1634,
    1634,  1645,  1646,  1647,  1653,  1654,  1655,  1656,  1657,  1658,
    1659,  1660,  1661,  1662,  1663,  1664,  1665,  1666,  1667,  1668,
    1669,  1670,  1671,  1672,  1673,  1674,  1675,  1676,  1677,  1678,
    1679,  1680,  1681,  1682,  1683,  1684,  1685,  1686,  1687,  1688,
    1689,  1690,  1691,  1692,  1693,  1694,  1695,  1696,  1697,  1698,
    1699,  1700,  1701,  1702,  1703,  1706,  1706,  1715,  1715,  1724,
    1724,  1733,  1733,  1743,  1743,  1755,  1755,  1766,  1766,  1777,
    1783,  1789,  1795,  1801,  1809,  1809,  1821,  1822,  1826,  1827,
    1828,  1833,  1833,  1841,  1842,  1843,  1848,  1849,  1850,  1851,
    1852,  1853,  1854,  1855,  1856,  1857,  1858,  1859,  1860,  1861,
    1862,  1863,  1864,  1865,  1866,  1867,  1868,  1869,  1870,  1871,
    1872,  1873,  1874,  1875,  1876,  1877,  1878,  1879,  1880,  1881,
    1882,  1883,  1884,  1885,  1886,  1887,  1888,  1889,  1890,  1891,
    1892,  1893,  1894,  1895,  1902,  1902,  1916,  1916,  1925,  1926,
    1929,  1930,  1931,  1938,  1938,  1953,  1953,  1967,  1968,  1971,
    1972,  1973,  1978,  1979,  1980,  1981,  1982,  1983,  1984,  1985,
    1986,  1987,  1990,  1992,  1998,  2000,  2000,  2009,  2009,  2018,
    2018,  2027,  2029,  2029,  2038,  2048,  2048,  2061,  2062,  2067,
    2068,  2069,  2076,  2076,  2088,  2088,  2100,  2101,  2106,  2107,
    2108,  2115,  2116,  2117,  2118,  2119,  2120,  2121,  2122,  2123,
    2124,  2125,  2128,  2130,  2130,  2139,  2141,  2143,  2149,  2155,
    2161,  2161,  2175,  2175,  2188,  2189,  2192,  2193,  2194,  2199,
    2199,  2209,  2209,  2219,  2220,  2221,  2226,  2227,  2228,  2229,
    2230,  2231,  2232,  2233,  2234,  2235,  2236,  2237,  2238,  2239,
    2240,  2241,  2242,  2243,  2244,  2245,  2246,  2247,  2248,  2249,
    2252,  2252,  2261,  2267,  2267,  2292,  2292,  2322,  2322,  2335,
    2336,  2339,  2340,  2341,  2346,  2346,  2358,  2358,  2370,  2371,
    2372,  2377,  2378,  2379,  2380,  2381,  2382,  2383,  2384,  2385,
    2386,  2387,  2388,  2389,  2390,  2393,  2393,  2402,  2408,  2408,
    2417,  2423,  2432,  2432,  2443,  2444,  2447,  2448,  2449,  2454,
    2454,  2463,  2463,  2472,  2473,  2476,  2477,  2478,  2484,  2485,
    2486,  2487,  2488,  2489,  2490,  2491,  2492,  2493,  2494,  2495,
    2498,  2498,  2509,  2509,  2520,  2520,  2531,  2531,  2540,  2540,
    2549,  2549,  2558,  2558,  2567,  2567,  2581,  2581,  2592,  2598,
    2598,  2609,  2610,  2611,  2616,  2616,  2626,  2627,  2630,  2631,
    2632,  2637,  2638,  2639,  2640,  2641,  2642,  2643,  2644,  2645,
    2646,  2647,  2648,  2649,  2650,  2651,  2654,  2656,  2656,  2665,
    2665,  2675,  2681,  2690,  2690,  2703,  2704,  2705,  2710,  2711,
    2712,  2713,  2714,  2715,  2716,  2717,  2718,  2721,  2721,  2729,
    2730,  2731,  2734,  2740,  2740,  2749,  2755,  2763,  2771,  2771,
    2783,  2783,  2795,  2796,  2799,  2800,  2801,  2806,  2806,  2814,
    2815,  2816,  2821,  2822,  2823,  2824,  2825,  2826,  2827,  2828,
    2829,  2830,  2831,  2832,  2833,  2836,  2836,  2845,  2846,  2847,
    2850,  2850,  2860,  2860,  2870,  2876,  2882,  2882,  2893,  2894,
    2897,  2898,  2899,  2904,  2904,  2912,  2913,  2914,  2919,  2920,
    2921,  2922,  2923,  2926,  2926,  2937,  2937,  2950,  2951,  2952,
    2957,  2958,  2959,  2960,  2961,  2962,  2963,  2966,  2966,  2974,
    2977,  2977,  2986,  2986,  2995,  2995,  3006,  3007,  3010,  3011,
    3012,  3017,  3017,  3025,  3026,  3027,  3032,  3033,  3034,  3035,
    3036,  3037,  3038,  3041,  3041,  3050,  3050,  3061,  3061,  3074,
    3075,  3076,  3081,  3082,  3083,  3084,  3085,  3086,  3089,  3095,
    3095,  3104,  3110,  3110,  3120,  3120,  3133,  3133,  3143,  3144,
    3145,  3150,  3151,  3152,  3153,  3154,  3155,  3156,  3157,  3158,
    3159,  3160,  3163,  3169,  3169,  3178,  3184,  3184,  3193,  3199,
    3205,  3205,  3214,  3215,  3218,  3218,  3229,  3229,  3241,  3241,
    3251,  3252,  3253,  3259,  3260,  3263,  3263,  3274,  3282,  3282,
    3295,  3296,  3297,  3303,  3303,  3311,  3312,  3313,  3318,  3319,
    3320,  3321,  3322,  3323,  3324,  3327,  3333,  3333,  3342,  3342,
    3353,  3354,  3355,  3360,  3360,  3368,  3369,  3370,  3375,  3376,
    3377,  3378,  3379,  3382,  3382,  3391,  3397,  3403,  3409,  3409,
    3418,  3418,  3429,  3430,  3431,  3436,  3437,  3440
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
#line 7169 "dhcp6_parser.cc"

#line 3446 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
