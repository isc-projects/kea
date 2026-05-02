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
#line 332 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 417 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 332 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 423 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 332 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 429 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 332 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 435 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 332 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 441 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 332 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 447 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 332 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 453 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 332 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 459 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 332 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 465 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ssl_mode: // ssl_mode
#line 332 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 471 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 332 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 477 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
#line 332 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 483 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 332 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 489 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 332 "dhcp6_parser.yy"
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
#line 341 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 777 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 342 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 783 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 343 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 789 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 344 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 795 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 345 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 801 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 346 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 807 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 347 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 813 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 348 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 819 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 349 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 825 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 350 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 831 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 351 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 837 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 352 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 843 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 353 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 849 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 354 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 855 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 362 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 861 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 363 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 867 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 364 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 873 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 365 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 879 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 366 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 885 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 367 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 891 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 368 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 897 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 371 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 906 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 376 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 917 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 381 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 927 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 387 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 933 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 394 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 943 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 399 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 954 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 405 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 962 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 410 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 971 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 413 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 979 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 421 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 988 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 425 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 997 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 429 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 1005 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 435 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 1013 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 437 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1022 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 446 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1031 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 450 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1040 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 454 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1048 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 464 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1059 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 473 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1070 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 478 "dhcp6_parser.yy"
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
#line 488 "dhcp6_parser.yy"
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
#line 497 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1108 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 505 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1116 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 511 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1126 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 515 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1135 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 522 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1143 "dhcp6_parser.cc"
    break;

  case 146: // $@21: %empty
#line 605 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1152 "dhcp6_parser.cc"
    break;

  case 147: // data_directory: "data-directory" $@21 ":" "constant string"
#line 608 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.warning(yystack_[2].location, "data-directory is deprecated and will be ignored");
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1163 "dhcp6_parser.cc"
    break;

  case 148: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 615 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1173 "dhcp6_parser.cc"
    break;

  case 149: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 621 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1183 "dhcp6_parser.cc"
    break;

  case 150: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 627 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1193 "dhcp6_parser.cc"
    break;

  case 151: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 633 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1203 "dhcp6_parser.cc"
    break;

  case 152: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 639 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1213 "dhcp6_parser.cc"
    break;

  case 153: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 645 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1223 "dhcp6_parser.cc"
    break;

  case 154: // renew_timer: "renew-timer" ":" "integer"
#line 651 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1233 "dhcp6_parser.cc"
    break;

  case 155: // rebind_timer: "rebind-timer" ":" "integer"
#line 657 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1243 "dhcp6_parser.cc"
    break;

  case 156: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 663 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1253 "dhcp6_parser.cc"
    break;

  case 157: // t1_percent: "t1-percent" ":" "floating point"
#line 669 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1263 "dhcp6_parser.cc"
    break;

  case 158: // t2_percent: "t2-percent" ":" "floating point"
#line 675 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1273 "dhcp6_parser.cc"
    break;

  case 159: // cache_threshold: "cache-threshold" ":" "floating point"
#line 681 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1283 "dhcp6_parser.cc"
    break;

  case 160: // cache_max_age: "cache-max-age" ":" "integer"
#line 687 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1293 "dhcp6_parser.cc"
    break;

  case 161: // adaptive_lease_time_threshold: "adaptive-lease-time-threshold" ":" "floating point"
#line 693 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("adaptive-lease-time-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr altt(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("adaptive-lease-time-threshold", altt);
}
#line 1303 "dhcp6_parser.cc"
    break;

  case 162: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 699 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1313 "dhcp6_parser.cc"
    break;

  case 163: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 705 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1323 "dhcp6_parser.cc"
    break;

  case 164: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 711 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1333 "dhcp6_parser.cc"
    break;

  case 165: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 717 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1343 "dhcp6_parser.cc"
    break;

  case 166: // $@22: %empty
#line 723 "dhcp6_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1352 "dhcp6_parser.cc"
    break;

  case 167: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 726 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1361 "dhcp6_parser.cc"
    break;

  case 168: // ddns_replace_client_name_value: "when-present"
#line 732 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1369 "dhcp6_parser.cc"
    break;

  case 169: // ddns_replace_client_name_value: "never"
#line 735 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1377 "dhcp6_parser.cc"
    break;

  case 170: // ddns_replace_client_name_value: "always"
#line 738 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1385 "dhcp6_parser.cc"
    break;

  case 171: // ddns_replace_client_name_value: "when-not-present"
#line 741 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1393 "dhcp6_parser.cc"
    break;

  case 172: // ddns_replace_client_name_value: "boolean"
#line 744 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1402 "dhcp6_parser.cc"
    break;

  case 173: // $@23: %empty
#line 750 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1411 "dhcp6_parser.cc"
    break;

  case 174: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 753 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1421 "dhcp6_parser.cc"
    break;

  case 175: // $@24: %empty
#line 759 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1430 "dhcp6_parser.cc"
    break;

  case 176: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 762 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1440 "dhcp6_parser.cc"
    break;

  case 177: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 768 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1450 "dhcp6_parser.cc"
    break;

  case 178: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 777 "dhcp6_parser.yy"
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

  case 179: // $@25: %empty
#line 787 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1473 "dhcp6_parser.cc"
    break;

  case 180: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 790 "dhcp6_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1482 "dhcp6_parser.cc"
    break;

  case 181: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 796 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1490 "dhcp6_parser.cc"
    break;

  case 182: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 799 "dhcp6_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1498 "dhcp6_parser.cc"
    break;

  case 183: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 802 "dhcp6_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1506 "dhcp6_parser.cc"
    break;

  case 184: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 805 "dhcp6_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1514 "dhcp6_parser.cc"
    break;

  case 185: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 810 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1524 "dhcp6_parser.cc"
    break;

  case 186: // ddns_ttl: "ddns-ttl" ":" "integer"
#line 816 "dhcp6_parser.yy"
                                 {
    ctx.unique("ddns-ttl", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl", ttl);
}
#line 1534 "dhcp6_parser.cc"
    break;

  case 187: // ddns_ttl_min: "ddns-ttl-min" ":" "integer"
#line 822 "dhcp6_parser.yy"
                                         {
    ctx.unique("ddns-ttl-min", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-min", ttl);
}
#line 1544 "dhcp6_parser.cc"
    break;

  case 188: // ddns_ttl_max: "ddns-ttl-max" ":" "integer"
#line 828 "dhcp6_parser.yy"
                                         {
    ctx.unique("ddns-ttl-max", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-max", ttl);
}
#line 1554 "dhcp6_parser.cc"
    break;

  case 189: // $@26: %empty
#line 834 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1563 "dhcp6_parser.cc"
    break;

  case 190: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 837 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1573 "dhcp6_parser.cc"
    break;

  case 191: // $@27: %empty
#line 843 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1582 "dhcp6_parser.cc"
    break;

  case 192: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 846 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1592 "dhcp6_parser.cc"
    break;

  case 193: // store_extended_info: "store-extended-info" ":" "boolean"
#line 852 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1602 "dhcp6_parser.cc"
    break;

  case 194: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 858 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1612 "dhcp6_parser.cc"
    break;

  case 195: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 864 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1622 "dhcp6_parser.cc"
    break;

  case 196: // $@28: %empty
#line 870 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1631 "dhcp6_parser.cc"
    break;

  case 197: // server_tag: "server-tag" $@28 ":" "constant string"
#line 873 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1641 "dhcp6_parser.cc"
    break;

  case 198: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 879 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1651 "dhcp6_parser.cc"
    break;

  case 199: // $@29: %empty
#line 885 "dhcp6_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1660 "dhcp6_parser.cc"
    break;

  case 200: // allocator: "allocator" $@29 ":" "constant string"
#line 888 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1670 "dhcp6_parser.cc"
    break;

  case 201: // $@30: %empty
#line 894 "dhcp6_parser.yy"
                           {
    ctx.unique("pd-allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1679 "dhcp6_parser.cc"
    break;

  case 202: // pd_allocator: "pd-allocator" $@30 ":" "constant string"
#line 897 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-allocator", al);
    ctx.leave();
}
#line 1689 "dhcp6_parser.cc"
    break;

  case 203: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 903 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1699 "dhcp6_parser.cc"
    break;

  case 204: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 909 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1709 "dhcp6_parser.cc"
    break;

  case 205: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 915 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1719 "dhcp6_parser.cc"
    break;

  case 206: // allow_address_registration: "allow-address-registration" ":" "boolean"
#line 921 "dhcp6_parser.yy"
                                                                     {
    ctx.unique("allow-address-registration", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allow-address-registration", first);
}
#line 1729 "dhcp6_parser.cc"
    break;

  case 207: // $@31: %empty
#line 927 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1741 "dhcp6_parser.cc"
    break;

  case 208: // interfaces_config: "interfaces-config" $@31 ":" "{" interfaces_config_params "}"
#line 933 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1751 "dhcp6_parser.cc"
    break;

  case 209: // $@32: %empty
#line 939 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1761 "dhcp6_parser.cc"
    break;

  case 210: // sub_interfaces6: "{" $@32 interfaces_config_params "}"
#line 943 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1770 "dhcp6_parser.cc"
    break;

  case 213: // interfaces_config_params: interfaces_config_params ","
#line 950 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1778 "dhcp6_parser.cc"
    break;

  case 222: // $@33: %empty
#line 965 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1790 "dhcp6_parser.cc"
    break;

  case 223: // interfaces_list: "interfaces" $@33 ":" list_strings
#line 971 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1799 "dhcp6_parser.cc"
    break;

  case 224: // re_detect: "re-detect" ":" "boolean"
#line 976 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1809 "dhcp6_parser.cc"
    break;

  case 225: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 982 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1819 "dhcp6_parser.cc"
    break;

  case 226: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 988 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1829 "dhcp6_parser.cc"
    break;

  case 227: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 994 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1839 "dhcp6_parser.cc"
    break;

  case 228: // $@34: %empty
#line 1000 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1851 "dhcp6_parser.cc"
    break;

  case 229: // lease_database: "lease-database" $@34 ":" "{" database_map_params "}"
#line 1006 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1862 "dhcp6_parser.cc"
    break;

  case 230: // $@35: %empty
#line 1013 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1874 "dhcp6_parser.cc"
    break;

  case 231: // hosts_database: "hosts-database" $@35 ":" "{" database_map_params "}"
#line 1019 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1885 "dhcp6_parser.cc"
    break;

  case 232: // $@36: %empty
#line 1026 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1897 "dhcp6_parser.cc"
    break;

  case 233: // hosts_databases: "hosts-databases" $@36 ":" "[" database_list "]"
#line 1032 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1906 "dhcp6_parser.cc"
    break;

  case 238: // not_empty_database_list: not_empty_database_list ","
#line 1043 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1914 "dhcp6_parser.cc"
    break;

  case 239: // $@37: %empty
#line 1048 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1924 "dhcp6_parser.cc"
    break;

  case 240: // database: "{" $@37 database_map_params "}"
#line 1052 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1934 "dhcp6_parser.cc"
    break;

  case 243: // database_map_params: database_map_params ","
#line 1060 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1942 "dhcp6_parser.cc"
    break;

  case 268: // $@38: %empty
#line 1091 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1951 "dhcp6_parser.cc"
    break;

  case 269: // database_type: "type" $@38 ":" "constant string"
#line 1094 "dhcp6_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 1961 "dhcp6_parser.cc"
    break;

  case 270: // $@39: %empty
#line 1100 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1970 "dhcp6_parser.cc"
    break;

  case 271: // user: "user" $@39 ":" "constant string"
#line 1103 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1980 "dhcp6_parser.cc"
    break;

  case 272: // $@40: %empty
#line 1109 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1989 "dhcp6_parser.cc"
    break;

  case 273: // password: "password" $@40 ":" "constant string"
#line 1112 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1999 "dhcp6_parser.cc"
    break;

  case 274: // $@41: %empty
#line 1118 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2008 "dhcp6_parser.cc"
    break;

  case 275: // host: "host" $@41 ":" "constant string"
#line 1121 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2018 "dhcp6_parser.cc"
    break;

  case 276: // port: "port" ":" "integer"
#line 1127 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2028 "dhcp6_parser.cc"
    break;

  case 277: // $@42: %empty
#line 1133 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2037 "dhcp6_parser.cc"
    break;

  case 278: // name: "name" $@42 ":" "constant string"
#line 1136 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2047 "dhcp6_parser.cc"
    break;

  case 279: // persist: "persist" ":" "boolean"
#line 1142 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2057 "dhcp6_parser.cc"
    break;

  case 280: // lfc_interval: "lfc-interval" ":" "integer"
#line 1148 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2067 "dhcp6_parser.cc"
    break;

  case 281: // readonly: "readonly" ":" "boolean"
#line 1154 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2077 "dhcp6_parser.cc"
    break;

  case 282: // connect_timeout: "connect-timeout" ":" "integer"
#line 1160 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2087 "dhcp6_parser.cc"
    break;

  case 283: // read_timeout: "read-timeout" ":" "integer"
#line 1166 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2097 "dhcp6_parser.cc"
    break;

  case 284: // write_timeout: "write-timeout" ":" "integer"
#line 1172 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2107 "dhcp6_parser.cc"
    break;

  case 285: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1178 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2117 "dhcp6_parser.cc"
    break;

  case 286: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1184 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2127 "dhcp6_parser.cc"
    break;

  case 287: // $@43: %empty
#line 1190 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2136 "dhcp6_parser.cc"
    break;

  case 288: // on_fail: "on-fail" $@43 ":" on_fail_mode
#line 1193 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2145 "dhcp6_parser.cc"
    break;

  case 289: // on_fail_mode: "stop-retry-exit"
#line 1198 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2151 "dhcp6_parser.cc"
    break;

  case 290: // on_fail_mode: "serve-retry-exit"
#line 1199 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2157 "dhcp6_parser.cc"
    break;

  case 291: // on_fail_mode: "serve-retry-continue"
#line 1200 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2163 "dhcp6_parser.cc"
    break;

  case 292: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1203 "dhcp6_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2173 "dhcp6_parser.cc"
    break;

  case 293: // max_row_errors: "max-row-errors" ":" "integer"
#line 1209 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2183 "dhcp6_parser.cc"
    break;

  case 294: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1215 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2193 "dhcp6_parser.cc"
    break;

  case 295: // $@44: %empty
#line 1221 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2202 "dhcp6_parser.cc"
    break;

  case 296: // trust_anchor: "trust-anchor" $@44 ":" "constant string"
#line 1224 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2212 "dhcp6_parser.cc"
    break;

  case 297: // $@45: %empty
#line 1230 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2221 "dhcp6_parser.cc"
    break;

  case 298: // cert_file: "cert-file" $@45 ":" "constant string"
#line 1233 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2231 "dhcp6_parser.cc"
    break;

  case 299: // $@46: %empty
#line 1239 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2240 "dhcp6_parser.cc"
    break;

  case 300: // key_file: "key-file" $@46 ":" "constant string"
#line 1242 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2250 "dhcp6_parser.cc"
    break;

  case 301: // $@47: %empty
#line 1248 "dhcp6_parser.yy"
                   {
    ctx.unique("ssl-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SSL_MODE);
}
#line 2259 "dhcp6_parser.cc"
    break;

  case 302: // ssl_mode: "ssl-mode" $@47 ":" ssl_mode
#line 1251 "dhcp6_parser.yy"
                 {
    ctx.stack_.back()->set("ssl-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2268 "dhcp6_parser.cc"
    break;

  case 303: // ssl_mode: "disable"
#line 1256 "dhcp6_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disable", ctx.loc2pos(yystack_[0].location)));
            }
#line 2276 "dhcp6_parser.cc"
    break;

  case 304: // ssl_mode: "prefer"
#line 1259 "dhcp6_parser.yy"
                 {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("prefer", ctx.loc2pos(yystack_[0].location)));
            }
#line 2284 "dhcp6_parser.cc"
    break;

  case 305: // ssl_mode: "require"
#line 1262 "dhcp6_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("require", ctx.loc2pos(yystack_[0].location)));
            }
#line 2292 "dhcp6_parser.cc"
    break;

  case 306: // ssl_mode: "verify-ca"
#line 1265 "dhcp6_parser.yy"
                    {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-ca", ctx.loc2pos(yystack_[0].location)));
            }
#line 2300 "dhcp6_parser.cc"
    break;

  case 307: // ssl_mode: "verify-full"
#line 1268 "dhcp6_parser.yy"
                      {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-full", ctx.loc2pos(yystack_[0].location)));
            }
#line 2308 "dhcp6_parser.cc"
    break;

  case 308: // $@48: %empty
#line 1273 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2317 "dhcp6_parser.cc"
    break;

  case 309: // cipher_list: "cipher-list" $@48 ":" "constant string"
#line 1276 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2327 "dhcp6_parser.cc"
    break;

  case 310: // $@49: %empty
#line 1282 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2339 "dhcp6_parser.cc"
    break;

  case 311: // sanity_checks: "sanity-checks" $@49 ":" "{" sanity_checks_params "}"
#line 1288 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2348 "dhcp6_parser.cc"
    break;

  case 314: // sanity_checks_params: sanity_checks_params ","
#line 1295 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2356 "dhcp6_parser.cc"
    break;

  case 317: // $@50: %empty
#line 1304 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2365 "dhcp6_parser.cc"
    break;

  case 318: // lease_checks: "lease-checks" $@50 ":" "constant string"
#line 1307 "dhcp6_parser.yy"
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

  case 319: // $@51: %empty
#line 1323 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2394 "dhcp6_parser.cc"
    break;

  case 320: // extended_info_checks: "extended-info-checks" $@51 ":" "constant string"
#line 1326 "dhcp6_parser.yy"
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

  case 321: // $@52: %empty
#line 1341 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2425 "dhcp6_parser.cc"
    break;

  case 322: // mac_sources: "mac-sources" $@52 ":" "[" mac_sources_list "]"
#line 1347 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2434 "dhcp6_parser.cc"
    break;

  case 325: // mac_sources_list: mac_sources_list ","
#line 1354 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2442 "dhcp6_parser.cc"
    break;

  case 328: // duid_id: "duid"
#line 1363 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2451 "dhcp6_parser.cc"
    break;

  case 329: // string_id: "constant string"
#line 1368 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2460 "dhcp6_parser.cc"
    break;

  case 330: // $@53: %empty
#line 1373 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2472 "dhcp6_parser.cc"
    break;

  case 331: // host_reservation_identifiers: "host-reservation-identifiers" $@53 ":" "[" host_reservation_identifiers_list "]"
#line 1379 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2481 "dhcp6_parser.cc"
    break;

  case 334: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1386 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2489 "dhcp6_parser.cc"
    break;

  case 338: // hw_address_id: "hw-address"
#line 1396 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2498 "dhcp6_parser.cc"
    break;

  case 339: // flex_id: "flex-id"
#line 1401 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2507 "dhcp6_parser.cc"
    break;

  case 340: // $@54: %empty
#line 1408 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2519 "dhcp6_parser.cc"
    break;

  case 341: // relay_supplied_options: "relay-supplied-options" $@54 ":" "[" list_content "]"
#line 1414 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2528 "dhcp6_parser.cc"
    break;

  case 342: // $@55: %empty
#line 1421 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2540 "dhcp6_parser.cc"
    break;

  case 343: // dhcp_multi_threading: "multi-threading" $@55 ":" "{" multi_threading_params "}"
#line 1427 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2551 "dhcp6_parser.cc"
    break;

  case 346: // multi_threading_params: multi_threading_params ","
#line 1436 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2559 "dhcp6_parser.cc"
    break;

  case 353: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1449 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2569 "dhcp6_parser.cc"
    break;

  case 354: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1455 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2579 "dhcp6_parser.cc"
    break;

  case 355: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1461 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2589 "dhcp6_parser.cc"
    break;

  case 356: // $@56: %empty
#line 1467 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2601 "dhcp6_parser.cc"
    break;

  case 357: // hooks_libraries: "hooks-libraries" $@56 ":" "[" hooks_libraries_list "]"
#line 1473 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2610 "dhcp6_parser.cc"
    break;

  case 362: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1484 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2618 "dhcp6_parser.cc"
    break;

  case 363: // $@57: %empty
#line 1489 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2628 "dhcp6_parser.cc"
    break;

  case 364: // hooks_library: "{" $@57 hooks_params "}"
#line 1493 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2638 "dhcp6_parser.cc"
    break;

  case 365: // $@58: %empty
#line 1499 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2648 "dhcp6_parser.cc"
    break;

  case 366: // sub_hooks_library: "{" $@58 hooks_params "}"
#line 1503 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2658 "dhcp6_parser.cc"
    break;

  case 369: // hooks_params: hooks_params ","
#line 1511 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2666 "dhcp6_parser.cc"
    break;

  case 373: // $@59: %empty
#line 1521 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2675 "dhcp6_parser.cc"
    break;

  case 374: // library: "library" $@59 ":" "constant string"
#line 1524 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2685 "dhcp6_parser.cc"
    break;

  case 375: // $@60: %empty
#line 1530 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2694 "dhcp6_parser.cc"
    break;

  case 376: // parameters: "parameters" $@60 ":" map_value
#line 1533 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2703 "dhcp6_parser.cc"
    break;

  case 377: // $@61: %empty
#line 1539 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2715 "dhcp6_parser.cc"
    break;

  case 378: // expired_leases_processing: "expired-leases-processing" $@61 ":" "{" expired_leases_params "}"
#line 1545 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2725 "dhcp6_parser.cc"
    break;

  case 381: // expired_leases_params: expired_leases_params ","
#line 1553 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2733 "dhcp6_parser.cc"
    break;

  case 388: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1566 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2743 "dhcp6_parser.cc"
    break;

  case 389: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1572 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2753 "dhcp6_parser.cc"
    break;

  case 390: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1578 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2763 "dhcp6_parser.cc"
    break;

  case 391: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1584 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2773 "dhcp6_parser.cc"
    break;

  case 392: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1590 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2783 "dhcp6_parser.cc"
    break;

  case 393: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1596 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2793 "dhcp6_parser.cc"
    break;

  case 394: // $@62: %empty
#line 1605 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2805 "dhcp6_parser.cc"
    break;

  case 395: // subnet6_list: "subnet6" $@62 ":" "[" subnet6_list_content "]"
#line 1611 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2814 "dhcp6_parser.cc"
    break;

  case 400: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1625 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2822 "dhcp6_parser.cc"
    break;

  case 401: // $@63: %empty
#line 1634 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2832 "dhcp6_parser.cc"
    break;

  case 402: // subnet6: "{" $@63 subnet6_params "}"
#line 1638 "dhcp6_parser.yy"
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

  case 403: // $@64: %empty
#line 1660 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2868 "dhcp6_parser.cc"
    break;

  case 404: // sub_subnet6: "{" $@64 subnet6_params "}"
#line 1664 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2878 "dhcp6_parser.cc"
    break;

  case 407: // subnet6_params: subnet6_params ","
#line 1673 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2886 "dhcp6_parser.cc"
    break;

  case 460: // $@65: %empty
#line 1733 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2895 "dhcp6_parser.cc"
    break;

  case 461: // subnet: "subnet" $@65 ":" "constant string"
#line 1736 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2905 "dhcp6_parser.cc"
    break;

  case 462: // $@66: %empty
#line 1742 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2914 "dhcp6_parser.cc"
    break;

  case 463: // interface: "interface" $@66 ":" "constant string"
#line 1745 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2924 "dhcp6_parser.cc"
    break;

  case 464: // $@67: %empty
#line 1751 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2933 "dhcp6_parser.cc"
    break;

  case 465: // interface_id: "interface-id" $@67 ":" "constant string"
#line 1754 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2943 "dhcp6_parser.cc"
    break;

  case 466: // $@68: %empty
#line 1760 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2952 "dhcp6_parser.cc"
    break;

  case 467: // client_class: "client-class" $@68 ":" "constant string"
#line 1763 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2962 "dhcp6_parser.cc"
    break;

  case 468: // $@69: %empty
#line 1770 "dhcp6_parser.yy"
                                       {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2974 "dhcp6_parser.cc"
    break;

  case 469: // network_client_classes: "client-classes" $@69 ":" list_strings
#line 1776 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2983 "dhcp6_parser.cc"
    break;

  case 470: // $@70: %empty
#line 1782 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2995 "dhcp6_parser.cc"
    break;

  case 471: // require_client_classes: "require-client-classes" $@70 ":" list_strings
#line 1788 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3004 "dhcp6_parser.cc"
    break;

  case 472: // $@71: %empty
#line 1793 "dhcp6_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3016 "dhcp6_parser.cc"
    break;

  case 473: // evaluate_additional_classes: "evaluate-additional-classes" $@71 ":" list_strings
#line 1799 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3025 "dhcp6_parser.cc"
    break;

  case 474: // reservations_global: "reservations-global" ":" "boolean"
#line 1804 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 3035 "dhcp6_parser.cc"
    break;

  case 475: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1810 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 3045 "dhcp6_parser.cc"
    break;

  case 476: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1816 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 3055 "dhcp6_parser.cc"
    break;

  case 477: // id: "id" ":" "integer"
#line 1822 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 3065 "dhcp6_parser.cc"
    break;

  case 478: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1828 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 3075 "dhcp6_parser.cc"
    break;

  case 479: // $@72: %empty
#line 1836 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3087 "dhcp6_parser.cc"
    break;

  case 480: // shared_networks: "shared-networks" $@72 ":" "[" shared_networks_content "]"
#line 1842 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3096 "dhcp6_parser.cc"
    break;

  case 485: // shared_networks_list: shared_networks_list ","
#line 1855 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3104 "dhcp6_parser.cc"
    break;

  case 486: // $@73: %empty
#line 1860 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3114 "dhcp6_parser.cc"
    break;

  case 487: // shared_network: "{" $@73 shared_network_params "}"
#line 1864 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3122 "dhcp6_parser.cc"
    break;

  case 490: // shared_network_params: shared_network_params ","
#line 1870 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3130 "dhcp6_parser.cc"
    break;

  case 540: // $@74: %empty
#line 1930 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3142 "dhcp6_parser.cc"
    break;

  case 541: // option_def_list: "option-def" $@74 ":" "[" option_def_list_content "]"
#line 1936 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3151 "dhcp6_parser.cc"
    break;

  case 542: // $@75: %empty
#line 1944 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3160 "dhcp6_parser.cc"
    break;

  case 543: // sub_option_def_list: "{" $@75 option_def_list "}"
#line 1947 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 3168 "dhcp6_parser.cc"
    break;

  case 548: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1959 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3176 "dhcp6_parser.cc"
    break;

  case 549: // $@76: %empty
#line 1966 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3186 "dhcp6_parser.cc"
    break;

  case 550: // option_def_entry: "{" $@76 option_def_params "}"
#line 1970 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3198 "dhcp6_parser.cc"
    break;

  case 551: // $@77: %empty
#line 1981 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3208 "dhcp6_parser.cc"
    break;

  case 552: // sub_option_def: "{" $@77 option_def_params "}"
#line 1985 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3220 "dhcp6_parser.cc"
    break;

  case 557: // not_empty_option_def_params: not_empty_option_def_params ","
#line 2001 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3228 "dhcp6_parser.cc"
    break;

  case 569: // code: "code" ":" "integer"
#line 2020 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3238 "dhcp6_parser.cc"
    break;

  case 571: // $@78: %empty
#line 2028 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3247 "dhcp6_parser.cc"
    break;

  case 572: // option_def_type: "type" $@78 ":" "constant string"
#line 2031 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3257 "dhcp6_parser.cc"
    break;

  case 573: // $@79: %empty
#line 2037 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3266 "dhcp6_parser.cc"
    break;

  case 574: // option_def_record_types: "record-types" $@79 ":" "constant string"
#line 2040 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3276 "dhcp6_parser.cc"
    break;

  case 575: // $@80: %empty
#line 2046 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3285 "dhcp6_parser.cc"
    break;

  case 576: // space: "space" $@80 ":" "constant string"
#line 2049 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3295 "dhcp6_parser.cc"
    break;

  case 578: // $@81: %empty
#line 2057 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3304 "dhcp6_parser.cc"
    break;

  case 579: // option_def_encapsulate: "encapsulate" $@81 ":" "constant string"
#line 2060 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3314 "dhcp6_parser.cc"
    break;

  case 580: // option_def_array: "array" ":" "boolean"
#line 2066 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3324 "dhcp6_parser.cc"
    break;

  case 581: // $@82: %empty
#line 2076 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3336 "dhcp6_parser.cc"
    break;

  case 582: // option_data_list: "option-data" $@82 ":" "[" option_data_list_content "]"
#line 2082 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3345 "dhcp6_parser.cc"
    break;

  case 587: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2097 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3353 "dhcp6_parser.cc"
    break;

  case 588: // $@83: %empty
#line 2104 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3363 "dhcp6_parser.cc"
    break;

  case 589: // option_data_entry: "{" $@83 option_data_params "}"
#line 2108 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3372 "dhcp6_parser.cc"
    break;

  case 590: // $@84: %empty
#line 2116 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3382 "dhcp6_parser.cc"
    break;

  case 591: // sub_option_data: "{" $@84 option_data_params "}"
#line 2120 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3391 "dhcp6_parser.cc"
    break;

  case 596: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2136 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3399 "dhcp6_parser.cc"
    break;

  case 609: // $@85: %empty
#line 2158 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3408 "dhcp6_parser.cc"
    break;

  case 610: // option_data_data: "data" $@85 ":" "constant string"
#line 2161 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3418 "dhcp6_parser.cc"
    break;

  case 613: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2171 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3428 "dhcp6_parser.cc"
    break;

  case 614: // option_data_always_send: "always-send" ":" "boolean"
#line 2177 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3438 "dhcp6_parser.cc"
    break;

  case 615: // option_data_never_send: "never-send" ":" "boolean"
#line 2183 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3448 "dhcp6_parser.cc"
    break;

  case 616: // $@86: %empty
#line 2189 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3460 "dhcp6_parser.cc"
    break;

  case 617: // option_data_client_classes: "client-classes" $@86 ":" list_strings
#line 2195 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3469 "dhcp6_parser.cc"
    break;

  case 618: // $@87: %empty
#line 2203 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3481 "dhcp6_parser.cc"
    break;

  case 619: // pools_list: "pools" $@87 ":" "[" pools_list_content "]"
#line 2209 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3490 "dhcp6_parser.cc"
    break;

  case 624: // not_empty_pools_list: not_empty_pools_list ","
#line 2222 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3498 "dhcp6_parser.cc"
    break;

  case 625: // $@88: %empty
#line 2227 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3508 "dhcp6_parser.cc"
    break;

  case 626: // pool_list_entry: "{" $@88 pool_params "}"
#line 2231 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3518 "dhcp6_parser.cc"
    break;

  case 627: // $@89: %empty
#line 2237 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3528 "dhcp6_parser.cc"
    break;

  case 628: // sub_pool6: "{" $@89 pool_params "}"
#line 2241 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3538 "dhcp6_parser.cc"
    break;

  case 631: // pool_params: pool_params ","
#line 2249 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3546 "dhcp6_parser.cc"
    break;

  case 656: // $@90: %empty
#line 2280 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3555 "dhcp6_parser.cc"
    break;

  case 657: // pool_entry: "pool" $@90 ":" "constant string"
#line 2283 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3565 "dhcp6_parser.cc"
    break;

  case 658: // pool_id: "pool-id" ":" "integer"
#line 2289 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3575 "dhcp6_parser.cc"
    break;

  case 659: // $@91: %empty
#line 2295 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3583 "dhcp6_parser.cc"
    break;

  case 660: // user_context: "user-context" $@91 ":" map_value
#line 2297 "dhcp6_parser.yy"
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

  case 661: // $@92: %empty
#line 2320 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3618 "dhcp6_parser.cc"
    break;

  case 662: // comment: "comment" $@92 ":" "constant string"
#line 2322 "dhcp6_parser.yy"
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

  case 663: // $@93: %empty
#line 2350 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3659 "dhcp6_parser.cc"
    break;

  case 664: // pd_pools_list: "pd-pools" $@93 ":" "[" pd_pools_list_content "]"
#line 2356 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3668 "dhcp6_parser.cc"
    break;

  case 669: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2369 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3676 "dhcp6_parser.cc"
    break;

  case 670: // $@94: %empty
#line 2374 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3686 "dhcp6_parser.cc"
    break;

  case 671: // pd_pool_entry: "{" $@94 pd_pool_params "}"
#line 2378 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3698 "dhcp6_parser.cc"
    break;

  case 672: // $@95: %empty
#line 2386 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3708 "dhcp6_parser.cc"
    break;

  case 673: // sub_pd_pool: "{" $@95 pd_pool_params "}"
#line 2390 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3720 "dhcp6_parser.cc"
    break;

  case 676: // pd_pool_params: pd_pool_params ","
#line 2400 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3728 "dhcp6_parser.cc"
    break;

  case 691: // $@96: %empty
#line 2421 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3737 "dhcp6_parser.cc"
    break;

  case 692: // pd_prefix: "prefix" $@96 ":" "constant string"
#line 2424 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3747 "dhcp6_parser.cc"
    break;

  case 693: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2430 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3757 "dhcp6_parser.cc"
    break;

  case 694: // $@97: %empty
#line 2436 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3766 "dhcp6_parser.cc"
    break;

  case 695: // excluded_prefix: "excluded-prefix" $@97 ":" "constant string"
#line 2439 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3776 "dhcp6_parser.cc"
    break;

  case 696: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2445 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3786 "dhcp6_parser.cc"
    break;

  case 697: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2451 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3796 "dhcp6_parser.cc"
    break;

  case 698: // $@98: %empty
#line 2460 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3808 "dhcp6_parser.cc"
    break;

  case 699: // reservations: "reservations" $@98 ":" "[" reservations_list "]"
#line 2466 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3817 "dhcp6_parser.cc"
    break;

  case 704: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2477 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3825 "dhcp6_parser.cc"
    break;

  case 705: // $@99: %empty
#line 2482 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3835 "dhcp6_parser.cc"
    break;

  case 706: // reservation: "{" $@99 reservation_params "}"
#line 2486 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3844 "dhcp6_parser.cc"
    break;

  case 707: // $@100: %empty
#line 2491 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3854 "dhcp6_parser.cc"
    break;

  case 708: // sub_reservation: "{" $@100 reservation_params "}"
#line 2495 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3863 "dhcp6_parser.cc"
    break;

  case 713: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2506 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3871 "dhcp6_parser.cc"
    break;

  case 726: // $@101: %empty
#line 2526 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3883 "dhcp6_parser.cc"
    break;

  case 727: // ip_addresses: "ip-addresses" $@101 ":" list_strings
#line 2532 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3892 "dhcp6_parser.cc"
    break;

  case 728: // $@102: %empty
#line 2537 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3904 "dhcp6_parser.cc"
    break;

  case 729: // prefixes: "prefixes" $@102 ":" list_strings
#line 2543 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3913 "dhcp6_parser.cc"
    break;

  case 730: // $@103: %empty
#line 2548 "dhcp6_parser.yy"
                                     {
    ctx.unique("excluded-prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3925 "dhcp6_parser.cc"
    break;

  case 731: // excluded_prefixes: "excluded-prefixes" $@103 ":" list_strings
#line 2554 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3934 "dhcp6_parser.cc"
    break;

  case 732: // $@104: %empty
#line 2559 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3943 "dhcp6_parser.cc"
    break;

  case 733: // duid: "duid" $@104 ":" "constant string"
#line 2562 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3953 "dhcp6_parser.cc"
    break;

  case 734: // $@105: %empty
#line 2568 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3962 "dhcp6_parser.cc"
    break;

  case 735: // hw_address: "hw-address" $@105 ":" "constant string"
#line 2571 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3972 "dhcp6_parser.cc"
    break;

  case 736: // $@106: %empty
#line 2577 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3981 "dhcp6_parser.cc"
    break;

  case 737: // hostname: "hostname" $@106 ":" "constant string"
#line 2580 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3991 "dhcp6_parser.cc"
    break;

  case 738: // $@107: %empty
#line 2586 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4000 "dhcp6_parser.cc"
    break;

  case 739: // flex_id_value: "flex-id" $@107 ":" "constant string"
#line 2589 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 4010 "dhcp6_parser.cc"
    break;

  case 740: // $@108: %empty
#line 2595 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4022 "dhcp6_parser.cc"
    break;

  case 741: // reservation_client_classes: "client-classes" $@108 ":" list_strings
#line 2601 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4031 "dhcp6_parser.cc"
    break;

  case 742: // $@109: %empty
#line 2609 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 4043 "dhcp6_parser.cc"
    break;

  case 743: // relay: "relay" $@109 ":" "{" relay_map "}"
#line 2615 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4052 "dhcp6_parser.cc"
    break;

  case 745: // $@110: %empty
#line 2626 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 4064 "dhcp6_parser.cc"
    break;

  case 746: // client_classes: "client-classes" $@110 ":" "[" client_classes_list "]"
#line 2632 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4073 "dhcp6_parser.cc"
    break;

  case 751: // not_empty_classes_list: not_empty_classes_list ","
#line 2643 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4081 "dhcp6_parser.cc"
    break;

  case 752: // $@111: %empty
#line 2648 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4091 "dhcp6_parser.cc"
    break;

  case 753: // client_class_entry: "{" $@111 client_class_params "}"
#line 2652 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 4101 "dhcp6_parser.cc"
    break;

  case 758: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2664 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 4109 "dhcp6_parser.cc"
    break;

  case 775: // $@112: %empty
#line 2688 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4118 "dhcp6_parser.cc"
    break;

  case 776: // client_class_test: "test" $@112 ":" "constant string"
#line 2691 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4128 "dhcp6_parser.cc"
    break;

  case 777: // $@113: %empty
#line 2697 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4137 "dhcp6_parser.cc"
    break;

  case 778: // client_class_template_test: "template-test" $@113 ":" "constant string"
#line 2700 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4147 "dhcp6_parser.cc"
    break;

  case 779: // only_if_required: "only-if-required" ":" "boolean"
#line 2707 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4157 "dhcp6_parser.cc"
    break;

  case 780: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2713 "dhcp6_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4167 "dhcp6_parser.cc"
    break;

  case 781: // $@114: %empty
#line 2722 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 4179 "dhcp6_parser.cc"
    break;

  case 782: // server_id: "server-id" $@114 ":" "{" server_id_params "}"
#line 2728 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4190 "dhcp6_parser.cc"
    break;

  case 785: // server_id_params: server_id_params ","
#line 2737 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4198 "dhcp6_parser.cc"
    break;

  case 795: // $@115: %empty
#line 2753 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 4207 "dhcp6_parser.cc"
    break;

  case 796: // server_id_type: "type" $@115 ":" duid_type
#line 2756 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4216 "dhcp6_parser.cc"
    break;

  case 797: // duid_type: "LLT"
#line 2761 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4222 "dhcp6_parser.cc"
    break;

  case 798: // duid_type: "EN"
#line 2762 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4228 "dhcp6_parser.cc"
    break;

  case 799: // duid_type: "LL"
#line 2763 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4234 "dhcp6_parser.cc"
    break;

  case 800: // htype: "htype" ":" "integer"
#line 2766 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4244 "dhcp6_parser.cc"
    break;

  case 801: // $@116: %empty
#line 2772 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4253 "dhcp6_parser.cc"
    break;

  case 802: // identifier: "identifier" $@116 ":" "constant string"
#line 2775 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4263 "dhcp6_parser.cc"
    break;

  case 803: // time: "time" ":" "integer"
#line 2781 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4273 "dhcp6_parser.cc"
    break;

  case 804: // enterprise_id: "enterprise-id" ":" "integer"
#line 2787 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4283 "dhcp6_parser.cc"
    break;

  case 805: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2795 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4293 "dhcp6_parser.cc"
    break;

  case 806: // $@117: %empty
#line 2803 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4306 "dhcp6_parser.cc"
    break;

  case 807: // control_socket: "control-socket" $@117 ":" "{" control_socket_params "}"
#line 2810 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4315 "dhcp6_parser.cc"
    break;

  case 808: // $@118: %empty
#line 2815 "dhcp6_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4328 "dhcp6_parser.cc"
    break;

  case 809: // control_sockets: "control-sockets" $@118 ":" "[" control_socket_list "]"
#line 2822 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4337 "dhcp6_parser.cc"
    break;

  case 814: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2833 "dhcp6_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4345 "dhcp6_parser.cc"
    break;

  case 815: // $@119: %empty
#line 2838 "dhcp6_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4355 "dhcp6_parser.cc"
    break;

  case 816: // control_socket_entry: "{" $@119 control_socket_params "}"
#line 2842 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4363 "dhcp6_parser.cc"
    break;

  case 819: // control_socket_params: control_socket_params ","
#line 2848 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4371 "dhcp6_parser.cc"
    break;

  case 833: // $@120: %empty
#line 2868 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4380 "dhcp6_parser.cc"
    break;

  case 834: // control_socket_type: "socket-type" $@120 ":" control_socket_type_value
#line 2871 "dhcp6_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4389 "dhcp6_parser.cc"
    break;

  case 835: // control_socket_type_value: "unix"
#line 2877 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4395 "dhcp6_parser.cc"
    break;

  case 836: // control_socket_type_value: "http"
#line 2878 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4401 "dhcp6_parser.cc"
    break;

  case 837: // control_socket_type_value: "https"
#line 2879 "dhcp6_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4407 "dhcp6_parser.cc"
    break;

  case 838: // $@121: %empty
#line 2882 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4417 "dhcp6_parser.cc"
    break;

  case 839: // control_socket_name: "socket-name" $@121 ":" "constant string"
#line 2886 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4427 "dhcp6_parser.cc"
    break;

  case 840: // $@122: %empty
#line 2892 "dhcp6_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4437 "dhcp6_parser.cc"
    break;

  case 841: // control_socket_address: "socket-address" $@122 ":" "constant string"
#line 2896 "dhcp6_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4447 "dhcp6_parser.cc"
    break;

  case 842: // control_socket_port: "socket-port" ":" "integer"
#line 2902 "dhcp6_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4457 "dhcp6_parser.cc"
    break;

  case 843: // cert_required: "cert-required" ":" "boolean"
#line 2908 "dhcp6_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4467 "dhcp6_parser.cc"
    break;

  case 844: // $@123: %empty
#line 2914 "dhcp6_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4479 "dhcp6_parser.cc"
    break;

  case 845: // http_headers: "http-headers" $@123 ":" "[" http_header_list "]"
#line 2920 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4488 "dhcp6_parser.cc"
    break;

  case 850: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2931 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4496 "dhcp6_parser.cc"
    break;

  case 851: // $@124: %empty
#line 2936 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4506 "dhcp6_parser.cc"
    break;

  case 852: // http_header: "{" $@124 http_header_params "}"
#line 2940 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4514 "dhcp6_parser.cc"
    break;

  case 855: // http_header_params: http_header_params ","
#line 2946 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4522 "dhcp6_parser.cc"
    break;

  case 861: // $@125: %empty
#line 2958 "dhcp6_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4531 "dhcp6_parser.cc"
    break;

  case 862: // header_value: "value" $@125 ":" "constant string"
#line 2961 "dhcp6_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4541 "dhcp6_parser.cc"
    break;

  case 863: // $@126: %empty
#line 2969 "dhcp6_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4553 "dhcp6_parser.cc"
    break;

  case 864: // authentication: "authentication" $@126 ":" "{" auth_params "}"
#line 2975 "dhcp6_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4564 "dhcp6_parser.cc"
    break;

  case 867: // auth_params: auth_params ","
#line 2984 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4572 "dhcp6_parser.cc"
    break;

  case 875: // $@127: %empty
#line 2998 "dhcp6_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4581 "dhcp6_parser.cc"
    break;

  case 876: // auth_type: "type" $@127 ":" auth_type_value
#line 3001 "dhcp6_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4590 "dhcp6_parser.cc"
    break;

  case 877: // auth_type_value: "basic"
#line 3006 "dhcp6_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4596 "dhcp6_parser.cc"
    break;

  case 878: // $@128: %empty
#line 3009 "dhcp6_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4605 "dhcp6_parser.cc"
    break;

  case 879: // realm: "realm" $@128 ":" "constant string"
#line 3012 "dhcp6_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4615 "dhcp6_parser.cc"
    break;

  case 880: // $@129: %empty
#line 3018 "dhcp6_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4624 "dhcp6_parser.cc"
    break;

  case 881: // directory: "directory" $@129 ":" "constant string"
#line 3021 "dhcp6_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4634 "dhcp6_parser.cc"
    break;

  case 882: // $@130: %empty
#line 3027 "dhcp6_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4646 "dhcp6_parser.cc"
    break;

  case 883: // clients: "clients" $@130 ":" "[" clients_list "]"
#line 3033 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4655 "dhcp6_parser.cc"
    break;

  case 888: // not_empty_clients_list: not_empty_clients_list ","
#line 3044 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4663 "dhcp6_parser.cc"
    break;

  case 889: // $@131: %empty
#line 3049 "dhcp6_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4673 "dhcp6_parser.cc"
    break;

  case 890: // basic_auth: "{" $@131 clients_params "}"
#line 3053 "dhcp6_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4681 "dhcp6_parser.cc"
    break;

  case 893: // clients_params: clients_params ","
#line 3059 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4689 "dhcp6_parser.cc"
    break;

  case 901: // $@132: %empty
#line 3073 "dhcp6_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4698 "dhcp6_parser.cc"
    break;

  case 902: // user_file: "user-file" $@132 ":" "constant string"
#line 3076 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4708 "dhcp6_parser.cc"
    break;

  case 903: // $@133: %empty
#line 3082 "dhcp6_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4717 "dhcp6_parser.cc"
    break;

  case 904: // password_file: "password-file" $@133 ":" "constant string"
#line 3085 "dhcp6_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4727 "dhcp6_parser.cc"
    break;

  case 905: // $@134: %empty
#line 3093 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4739 "dhcp6_parser.cc"
    break;

  case 906: // dhcp_queue_control: "dhcp-queue-control" $@134 ":" "{" queue_control_params "}"
#line 3099 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4750 "dhcp6_parser.cc"
    break;

  case 909: // queue_control_params: queue_control_params ","
#line 3108 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4758 "dhcp6_parser.cc"
    break;

  case 916: // enable_queue: "enable-queue" ":" "boolean"
#line 3121 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4768 "dhcp6_parser.cc"
    break;

  case 917: // $@135: %empty
#line 3127 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4777 "dhcp6_parser.cc"
    break;

  case 918: // queue_type: "queue-type" $@135 ":" "constant string"
#line 3130 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4787 "dhcp6_parser.cc"
    break;

  case 919: // capacity: "capacity" ":" "integer"
#line 3136 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4797 "dhcp6_parser.cc"
    break;

  case 920: // $@136: %empty
#line 3142 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4806 "dhcp6_parser.cc"
    break;

  case 921: // arbitrary_map_entry: "constant string" $@136 ":" value
#line 3145 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4815 "dhcp6_parser.cc"
    break;

  case 922: // $@137: %empty
#line 3152 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4827 "dhcp6_parser.cc"
    break;

  case 923: // dhcp_ddns: "dhcp-ddns" $@137 ":" "{" dhcp_ddns_params "}"
#line 3158 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4838 "dhcp6_parser.cc"
    break;

  case 924: // $@138: %empty
#line 3165 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4848 "dhcp6_parser.cc"
    break;

  case 925: // sub_dhcp_ddns: "{" $@138 dhcp_ddns_params "}"
#line 3169 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4858 "dhcp6_parser.cc"
    break;

  case 928: // dhcp_ddns_params: dhcp_ddns_params ","
#line 3177 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4866 "dhcp6_parser.cc"
    break;

  case 940: // enable_updates: "enable-updates" ":" "boolean"
#line 3195 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4876 "dhcp6_parser.cc"
    break;

  case 941: // $@139: %empty
#line 3201 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4885 "dhcp6_parser.cc"
    break;

  case 942: // server_ip: "server-ip" $@139 ":" "constant string"
#line 3204 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4895 "dhcp6_parser.cc"
    break;

  case 943: // server_port: "server-port" ":" "integer"
#line 3210 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4905 "dhcp6_parser.cc"
    break;

  case 944: // $@140: %empty
#line 3216 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4914 "dhcp6_parser.cc"
    break;

  case 945: // sender_ip: "sender-ip" $@140 ":" "constant string"
#line 3219 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4924 "dhcp6_parser.cc"
    break;

  case 946: // sender_port: "sender-port" ":" "integer"
#line 3225 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4934 "dhcp6_parser.cc"
    break;

  case 947: // max_queue_size: "max-queue-size" ":" "integer"
#line 3231 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4944 "dhcp6_parser.cc"
    break;

  case 948: // $@141: %empty
#line 3237 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4953 "dhcp6_parser.cc"
    break;

  case 949: // ncr_protocol: "ncr-protocol" $@141 ":" ncr_protocol_value
#line 3240 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4962 "dhcp6_parser.cc"
    break;

  case 950: // ncr_protocol_value: "UDP"
#line 3246 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4968 "dhcp6_parser.cc"
    break;

  case 951: // ncr_protocol_value: "TCP"
#line 3247 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4974 "dhcp6_parser.cc"
    break;

  case 952: // $@142: %empty
#line 3250 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4983 "dhcp6_parser.cc"
    break;

  case 953: // ncr_format: "ncr-format" $@142 ":" "JSON"
#line 3253 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4993 "dhcp6_parser.cc"
    break;

  case 954: // $@143: %empty
#line 3261 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 5005 "dhcp6_parser.cc"
    break;

  case 955: // config_control: "config-control" $@143 ":" "{" config_control_params "}"
#line 3267 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5015 "dhcp6_parser.cc"
    break;

  case 956: // $@144: %empty
#line 3273 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 5025 "dhcp6_parser.cc"
    break;

  case 957: // sub_config_control: "{" $@144 config_control_params "}"
#line 3277 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 5034 "dhcp6_parser.cc"
    break;

  case 960: // config_control_params: config_control_params ","
#line 3285 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 5042 "dhcp6_parser.cc"
    break;

  case 963: // $@145: %empty
#line 3295 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 5054 "dhcp6_parser.cc"
    break;

  case 964: // config_databases: "config-databases" $@145 ":" "[" database_list "]"
#line 3301 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5063 "dhcp6_parser.cc"
    break;

  case 965: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3306 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 5073 "dhcp6_parser.cc"
    break;

  case 966: // $@146: %empty
#line 3314 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 5085 "dhcp6_parser.cc"
    break;

  case 967: // loggers: "loggers" $@146 ":" "[" loggers_entries "]"
#line 3320 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5094 "dhcp6_parser.cc"
    break;

  case 970: // loggers_entries: loggers_entries ","
#line 3329 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 5102 "dhcp6_parser.cc"
    break;

  case 971: // $@147: %empty
#line 3335 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 5112 "dhcp6_parser.cc"
    break;

  case 972: // logger_entry: "{" $@147 logger_params "}"
#line 3339 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 5120 "dhcp6_parser.cc"
    break;

  case 975: // logger_params: logger_params ","
#line 3345 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 5128 "dhcp6_parser.cc"
    break;

  case 983: // debuglevel: "debuglevel" ":" "integer"
#line 3359 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 5138 "dhcp6_parser.cc"
    break;

  case 984: // $@148: %empty
#line 3365 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5147 "dhcp6_parser.cc"
    break;

  case 985: // severity: "severity" $@148 ":" "constant string"
#line 3368 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 5157 "dhcp6_parser.cc"
    break;

  case 986: // $@149: %empty
#line 3374 "dhcp6_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 5169 "dhcp6_parser.cc"
    break;

  case 987: // output_options_list: "output-options" $@149 ":" "[" output_options_list_content "]"
#line 3380 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5178 "dhcp6_parser.cc"
    break;

  case 990: // output_options_list_content: output_options_list_content ","
#line 3387 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 5186 "dhcp6_parser.cc"
    break;

  case 991: // $@150: %empty
#line 3392 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 5196 "dhcp6_parser.cc"
    break;

  case 992: // output_entry: "{" $@150 output_params_list "}"
#line 3396 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 5204 "dhcp6_parser.cc"
    break;

  case 995: // output_params_list: output_params_list ","
#line 3402 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 5212 "dhcp6_parser.cc"
    break;

  case 1001: // $@151: %empty
#line 3414 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5221 "dhcp6_parser.cc"
    break;

  case 1002: // output: "output" $@151 ":" "constant string"
#line 3417 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5231 "dhcp6_parser.cc"
    break;

  case 1003: // flush: "flush" ":" "boolean"
#line 3423 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5241 "dhcp6_parser.cc"
    break;

  case 1004: // maxsize: "maxsize" ":" "integer"
#line 3429 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5251 "dhcp6_parser.cc"
    break;

  case 1005: // maxver: "maxver" ":" "integer"
#line 3435 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5261 "dhcp6_parser.cc"
    break;

  case 1006: // $@152: %empty
#line 3441 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5270 "dhcp6_parser.cc"
    break;

  case 1007: // pattern: "pattern" $@152 ":" "constant string"
#line 3444 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5280 "dhcp6_parser.cc"
    break;

  case 1008: // $@153: %empty
#line 3450 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5292 "dhcp6_parser.cc"
    break;

  case 1009: // compatibility: "compatibility" $@153 ":" "{" compatibility_params "}"
#line 3456 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5301 "dhcp6_parser.cc"
    break;

  case 1012: // compatibility_params: compatibility_params ","
#line 3463 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5309 "dhcp6_parser.cc"
    break;

  case 1015: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3472 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5319 "dhcp6_parser.cc"
    break;


#line 5323 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1457;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     488, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457,    43,    62,    50,    57,    63,
      83,    93,   135,   148,   170,   180,   191,   192,   211,   212,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,    62,  -154,
      82,   772,    56,   322,  1523,   364,   130,    99,    11,   166,
    -101,   216,    91, -1457,   228,   121,   237,   234,   246, -1457,
      75, -1457, -1457, -1457, -1457, -1457, -1457, -1457,   265,   266,
     282,   283,   306,   307,   314,   330,   349,   353,   365,   367,
     369,   371,   388, -1457,   403,   428,   445,   446,   461, -1457,
   -1457, -1457,   477,   478,   490,   504,   527,   531,   534, -1457,
   -1457, -1457,   537, -1457, -1457, -1457, -1457, -1457, -1457,   538,
     540,   541, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457,   544, -1457, -1457, -1457, -1457, -1457, -1457, -1457,   546,
     550,   553,   557, -1457, -1457,   562, -1457,   109, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457,   563,   566,   568,   569, -1457,   117, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457,   570,   577, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457,   129, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457,   579, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457,   140, -1457, -1457, -1457, -1457,
   -1457, -1457,   580, -1457,   581,   582, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457,   153, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457,   291,   323, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457,   328, -1457, -1457,   585, -1457,
   -1457, -1457,   587, -1457, -1457,   449,   466, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
     588,   589,   590, -1457, -1457, -1457, -1457, -1457,   498,   592,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457,   159, -1457, -1457, -1457,   595, -1457,
     599, -1457,   603,   604, -1457, -1457, -1457, -1457, -1457,   171,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
     605,   259, -1457, -1457, -1457, -1457,    62,    62, -1457,   354,
     606, -1457, -1457,   607,   608,   609,   610,   611,   614,   378,
     379,   381,   382,   385,   386,   389,   391,   390,   392,   396,
     397,   402,   408,   404,   627,   414,   416,   394,   401,   418,
     657,   660,   661,   424,   426,   432,   427,   436,   439,   442,
     680,   684,   685,   447,   688,   690,   691,   694,   695,   696,
     457,   458,   462,   697,   701,   702,   705,   708,   710,   726,
     727,   728,   491,   729,   737,   739,   740,   741,   742,   743,
     506,   507,   509,   510,   752,   754, -1457,   772, -1457,   755,
     515,   516,   519,   521,    56, -1457,   759,   761,   762,   763,
     768,   530,   529,   771,   776,   781,   782,   784,   322, -1457,
     785,   533,  1523, -1457,   786,   548,   788,   555,   556,   364,
   -1457,   796,   797,   798,   799,   800,   801,   805,   808, -1457,
     130, -1457,   809,   810,   576,   816,   817,   818,   578, -1457,
      11,   820,   615,   616,   617,   821, -1457,   166,   859,   860,
     -70, -1457,   620,   862,   624,   864,   626,   631,   871,   872,
     216, -1457,   873,   636,    91, -1457, -1457, -1457,   876,   874,
     640,   877,   878,   879,   882,   885, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457,   641, -1457, -1457, -1457, -1457, -1457,  -156,   649,   650,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457,   888,   896,   897,
   -1457,   662,   663,   475,   901,   900,   666, -1457, -1457, -1457,
     904,   905,   906,   907,   908,   910,   911,   912,   913, -1457,
     915,   918,   921,   920,   922,   675,   676, -1457, -1457, -1457,
   -1457,   923,   925, -1457,   928, -1457, -1457, -1457, -1457, -1457,
     929,   930,   699,   700,   704, -1457, -1457,   928,   928,   928,
     706,   931, -1457,   707, -1457, -1457,   709, -1457,   711, -1457,
   -1457, -1457,   928,   928,   928,   928,   712,   713,   714,   715,
   -1457,   716,   717, -1457,   718,   719,   720, -1457, -1457,   722,
   -1457, -1457, -1457,   928, -1457,   723,   900, -1457, -1457,   724,
   -1457,   730, -1457, -1457,   -74,   731, -1457,   938, -1457, -1457,
      62,   772, -1457,    91,    56,   178,   178,   940, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457,   943,   945,   961,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457,   962, -1457, -1457,
   -1457,  -104,    62,    88,    36,   963,   964,   966,   194,    74,
     132,   149,   967,   295,   216, -1457, -1457,   968,  -186, -1457,
   -1457,   969,   970, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
     789, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457,   940, -1457,   260,
     275,   276, -1457, -1457, -1457, -1457,   932,   974,   975,   976,
     977,   978,   986,   987,   988,   989, -1457,   990,   991, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
     277, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457,   292, -1457,   993,   994, -1457,
   -1457,   995,   997, -1457, -1457,   996,  1000, -1457, -1457,   998,
    1002, -1457, -1457,  1001,  1003, -1457, -1457, -1457,    81, -1457,
   -1457, -1457,  1004, -1457, -1457, -1457,   110, -1457, -1457, -1457,
   -1457, -1457,   305, -1457, -1457, -1457, -1457,  1005,  1006, -1457,
   -1457,  1007,  1009, -1457, -1457,  1010,  1012, -1457,   992,  1013,
    1014,  1015,  1016,  1017,   309, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457,  1018,  1019,  1020, -1457, -1457, -1457,
   -1457,   316, -1457, -1457, -1457, -1457, -1457, -1457,  1021,  1022,
    1023, -1457,   317, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457,  1024, -1457,  1025, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457,   332, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457,  1026,  1027, -1457,  1029, -1457,  1030, -1457, -1457,
   -1457,   351, -1457, -1457, -1457, -1457, -1457,   352, -1457,   290,
   -1457,  1031, -1457,   358, -1457, -1457,   766, -1457,  1033,  1028,
   -1457, -1457,  1034,  1039, -1457, -1457,  1035,  1040, -1457, -1457,
   -1457,  1032,  1041,  1044,  1045,   794,   811,   815,   823,   826,
     828,   829,   834,   835,   836,  1049,   837,   841,  1062,  1081,
    1083,  1086,  1088,   178, -1457, -1457,   178, -1457,   940,   322,
   -1457,   943,    11, -1457,   945,   166, -1457,   961,  1454, -1457,
     962,  -104, -1457, -1457,    88, -1457,  1089,  1094,    36, -1457,
     681, -1457,   963,   130, -1457,   964,  -101, -1457,   966,   857,
     863,   865,   866,   869,   875,   194, -1457,  1110,  1121,   892,
     894,   903,    74, -1457,   883,   924,   927,   132, -1457,  1139,
    1145,  1172,   947,  1177,   941,  1179,   149, -1457,   149, -1457,
     967,   950,  1184,   949,  1193,   295, -1457, -1457,   206,   968,
   -1457,   953,  -186, -1457, -1457,  1194,  1198,  1523, -1457,   969,
     364, -1457,   970, -1457, -1457,   999,  1008,  1036,  1037, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,   395,
   -1457, -1457,  1038,  1042,  1043,   465,  1046, -1457,   360, -1457,
     422, -1457,  1197, -1457,  1211, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457,   425, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
    1047,  1048, -1457, -1457, -1457,  1225,  1226, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,  1230,  1231,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457,  1235, -1457,   444,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,   311,  1050,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,   315,  1051,
    1052, -1457,  1232, -1457,  1240, -1457,   453, -1457, -1457,  1053,
   -1457,    62, -1457, -1457,  1242, -1457, -1457, -1457, -1457, -1457,
     456, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,  1054,
     460, -1457,   501, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457,  1454, -1457, -1457, -1457,  1245,  1248,  1011,  1055, -1457,
     681, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457,    67,  1247, -1457, -1457, -1457,  1251,
    1056,  1253,   206, -1457, -1457, -1457, -1457, -1457,  1059,  1060,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
     502, -1457, -1457, -1457, -1457, -1457, -1457,  1255,  1256, -1457,
    1257, -1457,  1061, -1457, -1457, -1457,  1260,  1262,  1263,  1264,
      67, -1457,    -6, -1457,  1247,  1266, -1457,  1087,  1063,  1064,
    1265, -1457, -1457, -1457, -1457, -1457, -1457,   520, -1457, -1457,
   -1457, -1457,   387, -1457, -1457, -1457, -1457, -1457,  1267,  1272,
      -6, -1457,   120,  1266, -1457, -1457,  1275,  1280, -1457,  1065,
   -1457, -1457,  1282,  1283,  1287, -1457,   522, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457,   128, -1457,  1267, -1457,  1293,  1066,
    1071,  1072,  1294,   120, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457,   524, -1457, -1457, -1457, -1457,  1075, -1457, -1457,
   -1457,  1076, -1457,  1300,  1304,   128, -1457, -1457, -1457,  1078,
    1079, -1457, -1457, -1457
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   209,     9,   403,    11,
     627,    13,   672,    15,   707,    17,   542,    19,   551,    21,
     590,    23,   365,    25,   924,    27,   956,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   709,     0,   553,   592,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   146,   954,   207,   228,   230,   232,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   196,     0,     0,     0,     0,     0,   166,
     173,   175,     0,     0,     0,     0,     0,     0,     0,   394,
     540,   581,     0,   199,   201,   179,   479,   659,   661,     0,
       0,     0,   321,   340,   330,   310,   745,   698,   356,   377,
     781,     0,   342,   806,   808,   905,   922,   189,   191,     0,
       0,     0,     0,   966,  1008,     0,   145,     0,    69,    72,
      73,    74,    75,    76,    77,    78,    79,    80,   111,   112,
     113,   114,   115,   116,    81,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   118,   119,
     133,   134,   135,   107,   142,   143,   144,   137,   138,   139,
     140,    84,    85,    86,    87,   104,    88,    90,    89,   136,
      94,    95,    82,   108,   109,   110,    83,    92,    93,   102,
     103,   105,    91,    96,    97,    98,    99,   100,   101,   106,
     117,   141,   222,     0,     0,     0,     0,   221,     0,   211,
     214,   215,   216,   217,   218,   219,   220,   618,   663,   460,
     462,   464,     0,     0,   468,   470,   472,   466,   742,   459,
     408,   409,   410,   411,   412,   413,   414,   415,   435,   436,
     437,   438,   439,   440,   443,   444,   445,   446,   447,   448,
     449,   450,   451,   452,   453,   454,   455,   441,   442,   456,
     457,   458,     0,   405,   419,   420,   421,   424,   425,   426,
     427,   429,   430,   431,   422,   423,   416,   417,   433,   434,
     418,   428,   432,   656,     0,   655,   639,   640,   641,   642,
     643,   644,   645,   646,   647,   648,   649,   650,   651,   652,
     635,   636,   637,   638,   634,     0,   629,   632,   633,   653,
     654,   691,     0,   694,     0,     0,   690,   682,   683,   684,
     685,   681,   680,   688,   689,     0,   674,   677,   678,   686,
     687,   679,   740,   726,   728,   730,   732,   734,   736,   738,
     725,   722,   723,   724,     0,   710,   711,   716,   717,   718,
     714,   719,   720,   721,   715,     0,   571,   277,     0,   575,
     573,   578,     0,   567,   568,     0,   554,   555,   558,   570,
     559,   560,   561,   577,   562,   563,   564,   565,   566,   609,
       0,     0,     0,   616,   607,   608,   611,   612,     0,   593,
     594,   597,   598,   599,   600,   601,   602,   603,   606,   604,
     605,   373,   375,   370,     0,   367,   371,   372,     0,   941,
       0,   944,     0,     0,   948,   952,   939,   937,   938,     0,
     926,   929,   930,   931,   932,   933,   934,   935,   936,   963,
       0,     0,   958,   961,   962,    47,    52,     0,    39,    45,
       0,    66,    62,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    60,    71,    68,     0,
       0,     0,     0,     0,   213,   210,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   407,   404,
       0,     0,   631,   628,     0,     0,     0,     0,     0,   676,
     673,     0,     0,     0,     0,     0,     0,     0,     0,   708,
     713,   543,     0,     0,     0,     0,     0,     0,     0,   552,
     557,     0,     0,     0,     0,     0,   591,   596,     0,     0,
     369,   366,     0,     0,     0,     0,     0,     0,     0,     0,
     928,   925,     0,     0,   960,   957,    51,    43,     0,     0,
       0,     0,     0,     0,     0,     0,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,     0,   194,   195,   163,   164,   165,     0,     0,     0,
     177,   178,   185,   186,   187,   188,   193,     0,     0,     0,
     198,     0,     0,     0,     0,     0,     0,   474,   475,   476,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   805,
       0,     0,     0,     0,     0,     0,     0,   203,   204,   205,
     206,     0,     0,    70,     0,   224,   225,   226,   227,   212,
       0,     0,     0,     0,     0,   477,   478,     0,     0,     0,
       0,     0,   406,     0,   658,   630,     0,   693,     0,   696,
     697,   675,     0,     0,     0,     0,     0,     0,     0,     0,
     712,     0,     0,   569,     0,     0,     0,   580,   556,     0,
     613,   614,   615,     0,   595,     0,     0,   368,   940,     0,
     943,     0,   946,   947,     0,     0,   927,     0,   965,   959,
       0,     0,   147,     0,     0,     0,     0,   234,   197,   168,
     169,   170,   171,   172,   167,   174,   176,   396,   544,   583,
     200,   202,   181,   182,   183,   184,   180,   481,    40,   660,
     662,     0,    48,     0,     0,   747,   700,   358,     0,     0,
       0,     0,   810,     0,     0,   190,   192,     0,     0,    53,
     223,   620,   665,   461,   463,   465,   469,   471,   473,   467,
       0,   657,   692,   695,   741,   727,   729,   731,   733,   735,
     737,   739,   572,   278,   576,   574,   579,   610,   617,   374,
     376,   942,   945,   950,   951,   949,   953,   234,    44,     0,
       0,     0,   268,   270,   272,   274,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   287,     0,     0,   295,
     297,   299,   301,   303,   304,   305,   306,   307,   308,   267,
       0,   241,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   258,   259,   260,   261,   257,
     262,   263,   264,   265,   266,     0,   239,     0,   235,   236,
     401,     0,   397,   398,   549,     0,   545,   546,   588,     0,
     584,   585,   486,     0,   482,   483,   328,   329,     0,   323,
     326,   327,     0,   338,   339,   335,     0,   332,   336,   337,
     317,   319,     0,   312,   315,   316,   752,     0,   748,   749,
     705,     0,   701,   702,   363,     0,   359,   360,     0,     0,
       0,     0,     0,     0,     0,   379,   382,   383,   384,   385,
     386,   387,   795,   801,     0,     0,     0,   794,   791,   792,
     793,     0,   783,   786,   789,   787,   788,   790,     0,     0,
       0,   352,     0,   344,   347,   348,   349,   350,   351,   833,
     838,   840,     0,   863,     0,   844,   832,   825,   826,   827,
     830,   831,     0,   817,   820,   821,   822,   823,   828,   829,
     824,   815,     0,   811,   812,     0,   917,     0,   920,   913,
     914,     0,   907,   910,   911,   912,   915,     0,   971,     0,
     968,     0,  1014,     0,  1010,  1013,    55,   625,     0,   621,
     622,   670,     0,   666,   667,   744,     0,     0,    64,   955,
     208,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   243,   229,   231,     0,   233,   238,     0,
     395,   400,   553,   541,   548,   592,   582,   587,     0,   480,
     485,   325,   322,   341,   334,   331,     0,     0,   314,   311,
     754,   746,   751,   709,   699,   704,     0,   357,   362,     0,
       0,     0,     0,     0,     0,   381,   378,     0,     0,     0,
       0,     0,   785,   782,     0,     0,     0,   346,   343,     0,
       0,     0,     0,     0,     0,     0,   819,   807,     0,   809,
     814,     0,     0,     0,     0,   909,   906,   923,     0,   970,
     967,     0,  1012,  1009,    57,     0,    56,     0,   619,   624,
       0,   664,   669,   743,   964,     0,     0,     0,     0,   276,
     279,   280,   281,   282,   283,   284,   285,   294,   286,     0,
     292,   293,     0,     0,     0,     0,     0,   242,     0,   237,
       0,   399,     0,   547,     0,   586,   539,   506,   507,   508,
     510,   511,   512,   495,   496,   515,   516,   517,   518,   519,
     520,   523,   524,   525,   526,   527,   528,   529,   530,   531,
     532,   533,   534,   535,   521,   522,   536,   537,   538,   491,
     492,   493,   494,   502,   503,   504,   505,   499,   500,   501,
     509,     0,   488,   497,   513,   514,   498,   484,   324,   333,
       0,     0,   313,   775,   777,     0,     0,   773,   767,   768,
     769,   770,   771,   772,   774,   764,   765,   766,     0,   755,
     756,   759,   760,   761,   762,   763,   750,     0,   703,     0,
     361,   388,   389,   390,   391,   392,   393,   380,     0,     0,
     800,   803,   804,   784,   353,   354,   355,   345,     0,     0,
       0,   842,     0,   843,     0,   818,     0,   813,   916,     0,
     919,     0,   908,   986,     0,   984,   982,   976,   980,   981,
       0,   973,   978,   979,   977,   969,  1015,  1011,    54,    59,
       0,   623,     0,   668,   269,   271,   273,   275,   289,   290,
     291,   288,   296,   298,   300,   302,   309,   240,   402,   550,
     589,   490,   487,   318,   320,     0,     0,     0,     0,   753,
     758,   706,   364,   797,   798,   799,   796,   802,   835,   836,
     837,   834,   839,   841,     0,   846,   816,   918,   921,     0,
       0,     0,   975,   972,    58,   626,   671,   489,     0,     0,
     779,   780,   757,   875,   878,   880,   882,   874,   873,   872,
       0,   865,   868,   869,   870,   871,   851,     0,   847,   848,
       0,   983,     0,   974,   776,   778,     0,     0,     0,     0,
     867,   864,     0,   845,   850,     0,   985,     0,     0,     0,
       0,   866,   861,   860,   856,   858,   859,     0,   853,   857,
     849,   991,     0,   988,   877,   876,   879,   881,   884,     0,
     855,   852,     0,   990,   987,   889,     0,   885,   886,     0,
     854,  1001,     0,     0,     0,  1006,     0,   993,   996,   997,
     998,   999,  1000,   989,     0,   883,   888,   862,     0,     0,
       0,     0,     0,   995,   992,   901,   903,   900,   894,   896,
     898,   899,     0,   891,   895,   897,   887,     0,  1003,  1004,
    1005,     0,   994,     0,     0,   893,   890,  1002,  1007,     0,
       0,   892,   902,   904
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457,   -10, -1457,  -643, -1457,
     559, -1457, -1457, -1457, -1457,   511, -1457,  -244, -1457, -1457,
   -1457,   -71, -1457, -1457, -1457, -1457, -1457, -1457, -1457,   547,
     765, -1457, -1457,     4,    12,    22,    38,    41,    42,   -57,
     -54,   -35,   -15,    97,   100,   102,   103, -1457,    20,    23,
      45,    48, -1457, -1457,    55, -1457,    60, -1457,    66,   105,
      71, -1457, -1457,    73,    76,    78,    84,    90, -1457,    95,
   -1457,   107, -1457, -1457, -1457, -1457, -1457,   108, -1457,   113,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,   545,
     770, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457,   463, -1457,   224, -1457,  -765,   233, -1457,
   -1457, -1456, -1457, -1449, -1457, -1457, -1457, -1457,   -55, -1457,
    -806, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457,  -810, -1457,  -804, -1457,  -801, -1457,
     123, -1457, -1457, -1457, -1457, -1457, -1457,   209, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457,   219,  -791, -1457, -1457, -1457,
   -1457,   218, -1457, -1457, -1457, -1457, -1457, -1457, -1457,   186,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457,   207, -1457, -1457,
   -1457,   208,   733, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
     202, -1457, -1457, -1457, -1457, -1457, -1457, -1093, -1457, -1457,
   -1457,   238, -1457, -1457, -1457,   241,   773, -1457, -1457, -1092,
   -1457, -1091, -1457,    61, -1457,    85, -1457,   122, -1457,   126,
   -1457,   115,   118,   119, -1457, -1090, -1457, -1457, -1457, -1457,
     235, -1457, -1457,   -27,  1279, -1457, -1457, -1457, -1457, -1457,
     244, -1457, -1457, -1457,   247, -1457,   750, -1457,   -65, -1457,
   -1457, -1457, -1457, -1457,   -61, -1457, -1457, -1457, -1457, -1457,
     -29, -1457, -1457, -1457,   248, -1457, -1457, -1457,   249, -1457,
     746, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457,   182, -1457, -1457, -1457,   185,
     787, -1457, -1457,   -63,   -42, -1457,   -13, -1457, -1457, -1457,
   -1457, -1457,   175, -1457, -1457, -1457,   183,   791, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457,   -58, -1457, -1457, -1457,   239,
   -1457, -1457, -1457,   242, -1457,   778,   536, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1089, -1457, -1457, -1457, -1457, -1457, -1457,   250,
   -1457, -1457, -1457,    -7, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457,   232, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
     217, -1457,   220,   223, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457,   -68, -1457, -1457,
     -90, -1457, -1457, -1457, -1457, -1457,   -52, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,  -114, -1457,
   -1457,  -140, -1457, -1457, -1457, -1457, -1457, -1457, -1457,   221,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
     583,   775, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,   623,
     777, -1457, -1457, -1457, -1457, -1457, -1457,   236, -1457, -1457,
     -12, -1457, -1457, -1457, -1457, -1457, -1457,   -69, -1457, -1457,
    -100, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457, -1457,
   -1457,   245, -1457
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     809,    87,    88,    41,    68,    84,    85,   830,  1066,  1185,
    1186,   899,    43,    70,    90,   480,    91,    45,    71,   167,
     168,   169,   483,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   510,   794,   189,   511,   190,   512,   191,   192,
     193,   526,   806,   194,   195,   196,   197,   198,   548,   199,
     549,   200,   201,   202,   203,   504,   204,   205,   524,   206,
     525,   207,   208,   209,   210,   211,   485,    47,    72,   248,
     249,   250,   559,   251,   252,   253,   254,   212,   486,   213,
     487,   214,   488,   927,   928,   929,  1106,   900,   901,   902,
    1081,   903,  1082,   904,  1083,   905,  1084,   906,   907,   603,
     908,   909,   910,   911,   912,   913,   914,   915,   916,  1095,
    1371,   917,   918,   919,   920,  1098,   921,  1099,   922,  1100,
     923,  1101,   924,  1102,   215,   536,   962,   963,   964,  1126,
     965,  1127,   216,   533,   948,   949,   950,   951,   217,   535,
     956,   957,   958,   959,   218,   534,   219,   543,  1012,  1013,
    1014,  1015,  1016,   220,   539,   975,   976,   977,  1136,    63,
      80,   444,   445,   446,   618,   447,   619,   221,   540,   984,
     985,   986,   987,   988,   989,   990,   991,   222,   520,   931,
     932,   933,  1109,    49,    73,   302,   303,   304,   568,   305,
     569,   306,   570,   307,   576,   308,   573,   309,   574,   310,
     575,   223,   224,   225,   314,   315,   226,   527,   943,   944,
     945,  1118,  1271,  1272,   227,   521,    57,    77,   935,   936,
     937,  1112,    59,    78,   405,   406,   407,   408,   409,   410,
     411,   602,   412,   606,   413,   605,   414,   415,   607,   416,
     228,   522,   939,   940,   941,  1115,    61,    79,   428,   429,
     430,   431,   432,   611,   433,   434,   435,   436,   437,   438,
     615,   317,   566,  1068,  1069,  1070,  1187,    51,    74,   345,
     346,   347,   580,   348,   229,   528,   230,   529,   320,   567,
    1072,  1073,  1074,  1190,    53,    75,   365,   366,   367,   584,
     368,   369,   586,   370,   371,   231,   538,   971,   972,   973,
    1133,    55,    76,   384,   385,   386,   387,   592,   388,   593,
     389,   594,   390,   595,   391,   596,   392,   597,   393,   598,
     394,   591,   322,   577,  1076,   232,   537,   967,   968,   969,
    1130,  1298,  1299,  1300,  1301,  1302,  1385,  1303,  1386,  1304,
    1305,   233,   541,  1001,  1002,  1003,  1147,  1396,  1004,  1005,
    1148,  1006,  1007,   234,   235,   544,   236,   545,  1042,  1043,
    1044,  1168,  1032,  1033,  1034,  1159,  1401,  1035,  1160,  1036,
    1161,  1037,  1038,  1039,  1165,  1437,  1438,  1439,  1452,  1467,
    1468,  1469,  1479,  1040,  1163,  1430,  1431,  1432,  1446,  1475,
    1433,  1447,  1434,  1448,  1435,  1449,  1486,  1487,  1488,  1504,
    1522,  1523,  1524,  1533,  1525,  1534,   237,   546,  1051,  1052,
    1053,  1054,  1172,  1055,  1056,  1174,   238,   547,    65,    81,
     459,   460,   461,   462,   623,   463,   464,   625,   465,   466,
     467,   628,   865,   468,   629,   239,   484,    67,    82,   471,
     472,   473,   632,   474,   240,   554,  1059,  1060,  1178,  1350,
    1351,  1352,  1353,  1411,  1354,  1409,  1472,  1473,  1482,  1496,
    1497,  1498,  1508,  1499,  1500,  1501,  1502,  1512,   241,   555,
    1063,  1064,  1065
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     166,   247,   269,   325,   356,   380,    38,   403,   424,   443,
     456,  1027,   362,   998,   426,   321,   276,  1028,   427,   277,
    1029,   925,   955,   404,   425,  1260,  1261,  1262,  1270,  1276,
     255,   318,   349,   363,   382,   396,   417,   439,   278,   457,
     946,  1061,   808,    30,   316,   344,   361,   381,  1518,   441,
     442,   789,   790,   791,   792,  1519,   165,    42,   279,   256,
     319,   350,   364,   383,    44,   418,   440,    31,   458,    32,
      46,    33,   242,   243,   244,   245,   246,   270,   481,  1518,
     441,   442,   397,   482,  1121,   271,  1519,  1122,    86,   793,
      48,  1423,    89,   284,   326,   272,   285,   327,   992,   397,
      50,   398,   399,   877,   469,   470,   400,   401,   402,   137,
     138,   273,   557,  1124,   274,   275,  1125,   558,   286,   328,
     564,   287,   329,   808,   476,   565,   137,   138,   288,   330,
     863,   864,   578,   289,   331,   340,   357,   579,   947,   290,
     332,   165,    52,   582,   292,   333,   293,   334,   583,   294,
     335,   295,   336,   873,   874,    54,   589,   296,   337,   341,
     358,   590,   620,   297,   338,   960,   961,   621,   298,   339,
     280,   137,   138,   281,   630,   282,   283,    56,   291,   631,
     299,   300,   137,   138,  1462,   130,   301,    58,   311,   137,
     138,   312,   313,   889,   890,   891,   342,   359,    60,    62,
     343,   360,   872,   873,   874,   875,   876,   877,   878,   879,
     880,   881,   882,   883,   884,   885,   886,   131,    64,    66,
     887,   888,   889,   890,   891,   892,   893,   894,   895,   896,
     897,   898,   946,   953,   475,   954,   165,   993,   994,   995,
     996,   477,   478,   137,   138,   137,   138,   137,   138,   479,
    1424,  1425,  1426,   165,   397,   419,   398,   399,   420,   421,
     422,   372,   634,   557,   137,   138,   397,   635,  1078,   489,
     490,   373,   374,   375,   376,   377,   378,   379,   634,   564,
    1103,   137,   138,  1079,  1080,  1104,   491,   492,  1260,  1261,
    1262,  1270,  1276,  1179,   397,  1103,  1180,   423,   165,   599,
    1105,  1008,  1009,  1010,    34,    35,    36,    37,  1128,   165,
     493,   494,  1145,  1129,  1515,  1516,   165,  1146,   495,  1152,
    1157,   137,   138,  1019,  1153,  1158,   600,  1020,  1021,  1022,
    1023,   137,   138,   955,   496,  1166,   601,  1024,  1025,  1491,
    1167,  1218,  1492,  1493,  1494,  1495,   998,   978,   979,   980,
     981,   982,   983,   497,  1175,   630,  1027,   498,  1027,  1176,
    1177,  1182,  1028,  1103,  1028,  1029,  1183,  1029,  1377,   499,
     165,   500,   165,   501,   165,   502,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
    1483,   165,   503,  1484,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   505,   165,   131,
     137,   138,   448,   449,   450,   451,   452,   453,   454,   455,
     165,   133,   134,   135,  1343,   578,  1344,  1345,  1381,   257,
    1378,   258,   506,  1382,  1368,  1369,  1370,   137,   138,   259,
     260,   261,   262,   263,   139,   140,   141,   620,   165,   507,
     508,   131,  1392,   264,   265,   266,  1166,   609,   165,  1412,
     267,  1406,   147,   582,  1413,   509,   636,   637,  1415,   610,
     268,  1393,  1394,  1395,   351,   352,   353,   354,   355,   137,
     138,   513,   514,   836,   837,   838,   166,  1045,  1046,  1047,
    1398,  1399,  1400,   247,   515,   264,   265,   266,   844,   845,
     846,   847,   267,   324,   589,  1450,   616,   269,   516,  1416,
    1451,   325,   892,   893,   894,   895,   896,   897,   356,   858,
     321,   276,   255,  1480,   277,  1513,   362,  1535,  1481,   380,
    1514,   517,  1536,   157,   158,   518,   318,  1048,   519,   403,
     349,   523,   530,   278,   531,   532,   424,   363,   542,   316,
     550,   256,   426,   344,   551,   404,   427,   552,   382,   456,
     361,   553,   425,   279,   165,   319,   556,   560,   417,   350,
     561,   381,   562,   563,   571,   439,   364,   802,   803,   804,
     805,   572,   270,   581,   585,   587,   588,   383,   457,   604,
     271,   608,   612,   613,   614,   617,   638,   418,   284,   622,
     272,   285,   326,   624,   440,   327,   165,   626,   627,   633,
     639,   640,   641,   642,   643,   644,   273,   458,   645,   274,
     275,   646,   647,   286,   648,   649,   287,   328,   650,   651,
     329,   661,   652,   288,   653,   654,   655,   330,   289,   664,
     656,   657,   331,   340,   290,   658,   665,   660,   332,   292,
     357,   293,   659,   333,   294,   334,   295,   662,   335,   663,
     336,   667,   296,   666,   668,   669,   337,   341,   297,   670,
     673,   671,   338,   298,   358,   280,   672,   339,   281,   674,
     282,   283,   675,   291,   677,   299,   300,   676,   678,   679,
     680,   301,   681,   311,   682,   683,   312,   313,   684,   685,
     686,   690,   687,   688,   342,   691,   692,   689,   343,   693,
     166,   359,   694,   247,   695,   360,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
     696,   697,   698,   700,   699,    98,    99,   100,   101,   102,
     103,   701,   255,   702,   703,   704,   705,   706,   997,  1011,
    1026,   707,   708,   456,   709,   710,   711,  1062,   712,   714,
     715,   716,   717,   720,   718,   721,   722,   723,   131,   397,
     868,   256,   724,   725,   726,   727,   734,   999,  1017,  1030,
     728,  1049,   457,    92,    93,   729,   730,    94,   731,   733,
     736,   737,   738,    95,    96,    97,   137,   138,   739,   740,
     742,   743,   744,   745,   746,   747,  1000,  1018,  1031,   748,
    1050,   458,   749,   751,   752,  1283,  1284,  1285,  1286,   753,
     754,   755,   756,   757,   759,   763,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     760,   761,   762,   765,   766,   768,   769,   770,   771,   772,
     132,   133,   134,   135,   773,   774,   775,   777,   136,   778,
     780,   781,   782,   788,   783,   784,   785,   137,   138,   786,
     787,   795,   796,   797,   139,   140,   141,   142,   143,   144,
     145,   798,   799,   146,   800,   801,   807,    32,   810,   811,
     812,   813,   147,   815,   814,   816,   817,   825,   826,   818,
     819,   148,   820,   165,   149,   821,   822,   823,   827,   824,
     373,   150,   828,   829,   831,   832,  1085,   866,   840,   151,
     152,   833,   834,   867,   153,   154,   835,   926,   839,   841,
     930,   842,   934,   843,   848,   849,   850,   851,   852,   853,
     854,   855,   856,   155,   857,   859,   861,   156,   938,   942,
     966,   970,   862,   974,  1041,  1058,  1067,  1071,  1086,  1087,
    1088,  1089,  1090,   157,   158,   159,   160,   161,   162,   163,
    1091,  1092,  1093,  1094,  1096,  1097,  1139,  1108,   164,  1107,
    1111,  1110,  1113,  1114,  1116,  1117,  1120,  1119,  1184,  1132,
    1123,  1131,  1135,  1134,   165,  1138,  1137,  1140,  1141,  1142,
    1143,  1144,  1149,  1150,  1151,  1154,  1155,  1156,  1162,  1164,
    1170,  1189,  1169,  1171,  1173,  1181,  1195,  1199,   269,  1188,
    1191,   403,  1192,  1193,   424,  1196,  1194,  1226,  1197,  1198,
     426,   321,   276,  1209,   427,   277,  1200,   404,  1201,  1287,
     425,  1233,   380,  1259,  1234,   443,  1212,   318,  1202,  1203,
     417,  1204,  1205,   439,   278,  1294,  1274,  1206,  1207,  1208,
     316,   997,  1210,  1235,  1211,  1213,  1011,  1214,  1296,  1273,
    1215,   382,  1216,  1280,   279,  1026,   319,  1026,  1281,   418,
    1311,  1295,   440,  1236,   381,  1275,  1312,  1346,  1313,  1314,
     999,  1062,  1315,   270,  1318,  1017,   325,  1297,  1316,   356,
     383,   271,  1227,  1347,  1030,  1319,  1030,   362,  1324,   284,
    1228,   272,   285,  1049,  1288,  1320,  1348,  1321,  1241,  1000,
    1229,  1242,  1289,  1328,  1018,   349,  1322,   273,   363,  1329,
     274,   275,  1290,  1031,   286,  1031,  1230,   287,   344,  1231,
    1232,   361,  1050,  1243,   288,  1349,  1244,  1325,  1291,   289,
    1326,  1292,  1293,  1245,   350,   290,  1330,   364,  1246,  1263,
     292,  1332,   293,  1334,  1247,   294,  1333,   295,  1339,  1249,
    1331,  1250,  1340,   296,  1251,  1338,  1252,  1341,  1356,   297,
    1358,  1359,  1253,  1264,   298,  1379,   280,   326,  1254,   281,
     327,   282,   283,  1255,   291,  1237,   299,   300,  1238,  1380,
    1239,  1240,   301,  1248,   311,  1256,  1257,   312,   313,  1387,
    1388,  1258,   328,  1267,  1390,   329,  1268,  1269,  1389,  1404,
    1265,  1364,   330,  1391,  1266,  1405,  1410,   331,   340,  1418,
    1365,   357,  1419,   332,  1436,  1440,  1420,  1442,   333,  1454,
     334,  1453,  1455,   335,  1457,   336,  1458,  1459,  1460,  1474,
    1478,   337,   341,  1471,  1485,   358,  1489,   338,  1366,  1367,
    1372,  1505,   339,  1506,  1373,  1374,  1509,  1510,  1376,  1383,
    1384,  1511,  1397,  1402,  1403,  1407,  1414,  1527,  1531,  1441,
    1421,  1444,  1445,  1456,  1539,  1476,  1477,  1507,  1540,   342,
    1226,  1528,   359,   343,  1529,  1530,   360,  1537,  1538,  1287,
    1542,  1543,   713,   952,  1233,   860,  1259,  1234,   869,   871,
    1077,  1408,  1219,  1427,   719,  1294,  1217,  1282,  1375,  1274,
    1278,  1346,  1279,  1327,  1309,  1310,  1235,  1317,  1296,  1221,
    1220,   732,  1273,   767,  1417,  1277,   395,  1347,  1223,  1222,
     758,  1295,  1428,   764,  1224,  1225,  1236,  1363,  1275,   735,
    1348,  1361,  1360,  1362,  1308,  1307,  1075,  1297,   750,  1427,
     741,  1463,  1306,  1422,  1323,  1227,  1470,  1337,  1336,  1335,
    1490,  1429,  1526,  1228,  1288,  1541,  1342,  1464,  1461,  1349,
    1443,  1241,  1289,  1229,  1242,   776,   870,  1057,  1428,  1463,
    1465,   779,  1290,  1532,  1503,  1355,     0,     0,     0,  1230,
       0,     0,  1231,  1232,     0,  1464,  1243,  1357,  1291,  1244,
       0,  1292,  1293,  1517,     0,     0,  1245,  1429,  1465,  1466,
       0,  1246,  1263,     0,     0,     0,     0,  1247,     0,     0,
       0,     0,  1249,     0,  1250,     0,     0,  1251,     0,  1252,
       0,     0,  1520,     0,  1517,  1253,  1264,  1466,     0,     0,
       0,  1254,     0,     0,     0,     0,  1255,     0,  1237,     0,
       0,  1238,     0,  1239,  1240,     0,  1248,     0,  1256,  1257,
       0,  1521,     0,  1520,  1258,     0,  1267,     0,     0,  1268,
    1269,     0,     0,  1265,     0,     0,     0,  1266,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,  1521,     0,     0,     0,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
       0,   131,   397,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   133,   134,   135,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   137,
     138,     0,   260,   261,     0,   263,   139,   140,   141,     0,
       0,     0,     0,     0,     0,   264,   265,   266,     0,     0,
       0,     0,   267,     0,     0,   116,   117,   118,   119,   120,
     121,   122,   268,   124,   125,   126,   127,     0,     0,     0,
     131,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   135,     0,     0,     0,     0,     0,
       0,   323,     0,     0,     0,     0,     0,     0,   137,   138,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   264,   265,   266,     0,     0,     0,
       0,   267,   324,     0,     0,   157,   158,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   165,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   157,   158,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   165
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   821,    75,   819,    79,    73,    73,   821,    79,    73,
     821,   786,   813,    78,    79,  1118,  1118,  1118,  1118,  1118,
      72,    73,    74,    75,    76,    24,    78,    79,    73,    81,
     144,   227,   685,     0,    73,    74,    75,    76,  1504,   150,
     151,   207,   208,   209,   210,  1504,   242,     7,    73,    72,
      73,    74,    75,    76,     7,    78,    79,     5,    81,     7,
       7,     9,    16,    17,    18,    19,    20,    73,     3,  1535,
     150,   151,    88,     8,     3,    73,  1535,     6,   242,   245,
       7,    24,    10,    73,    74,    73,    73,    74,    24,    88,
       7,    90,    91,    29,    13,    14,    95,    96,    97,   115,
     116,    73,     3,     3,    73,    73,     6,     8,    73,    74,
       3,    73,    74,   766,     3,     8,   115,   116,    73,    74,
     204,   205,     3,    73,    74,    74,    75,     8,   242,    73,
      74,   242,     7,     3,    73,    74,    73,    74,     8,    73,
      74,    73,    74,    25,    26,     7,     3,    73,    74,    74,
      75,     8,     3,    73,    74,   129,   130,     8,    73,    74,
      73,   115,   116,    73,     3,    73,    73,     7,    73,     8,
      73,    73,   115,   116,   190,    86,    73,     7,    73,   115,
     116,    73,    73,    44,    45,    46,    74,    75,     7,     7,
      74,    75,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    87,     7,     7,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,   144,   145,     6,   147,   242,   163,   164,   165,
     166,     4,     8,   115,   116,   115,   116,   115,   116,     3,
     183,   184,   185,   242,    88,    89,    90,    91,    92,    93,
      94,   131,     3,     3,   115,   116,    88,     8,     8,     4,
       4,   141,   142,   143,   144,   145,   146,   147,     3,     3,
       3,   115,   116,     8,     8,     8,     4,     4,  1381,  1381,
    1381,  1381,  1381,     3,    88,     3,     6,   131,   242,     8,
       8,   169,   170,   171,   242,   243,   244,   245,     3,   242,
       4,     4,     3,     8,   186,   187,   242,     8,     4,     3,
       3,   115,   116,   174,     8,     8,     3,   178,   179,   180,
     181,   115,   116,  1124,     4,     3,     8,   188,   189,   219,
       8,  1106,   222,   223,   224,   225,  1152,   153,   154,   155,
     156,   157,   158,     4,     3,     3,  1166,     4,  1168,     8,
       8,     3,  1166,     3,  1168,  1166,     8,  1168,     8,     4,
     242,     4,   242,     4,   242,     4,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
       3,   242,     4,     6,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,     4,   242,    87,
     115,   116,   196,   197,   198,   199,   200,   201,   202,   203,
     242,    99,   100,   101,   218,     3,   220,   221,     3,   107,
       8,   109,     4,     8,    39,    40,    41,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,     3,   242,     4,
       4,    87,     8,   131,   132,   133,     3,     8,   242,     3,
     138,     8,   140,     3,     8,     4,   476,   477,     8,     3,
     148,   160,   161,   162,   110,   111,   112,   113,   114,   115,
     116,     4,     4,   727,   728,   729,   557,   192,   193,   194,
     175,   176,   177,   564,     4,   131,   132,   133,   742,   743,
     744,   745,   138,   139,     3,     3,     8,   578,     4,     8,
       8,   582,    47,    48,    49,    50,    51,    52,   589,   763,
     578,   578,   564,     3,   578,     3,   589,     3,     8,   600,
       8,     4,     8,   211,   212,     4,   578,   242,     4,   610,
     582,     4,     4,   578,     4,     4,   617,   589,     4,   578,
       4,   564,   617,   582,     4,   610,   617,     4,   600,   630,
     589,     4,   617,   578,   242,   578,     4,     4,   610,   582,
       4,   600,     4,     4,     4,   617,   589,   102,   103,   104,
     105,     4,   578,     4,     4,     4,     4,   600,   630,     4,
     578,     4,     4,     4,     4,     3,   242,   610,   578,     4,
     578,   578,   582,     4,   617,   582,   242,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   578,   630,     4,   578,
     578,   243,   243,   578,   243,   243,   578,   582,   243,   243,
     582,     4,   243,   578,   243,   245,   244,   582,   578,   245,
     244,   244,   582,   582,   578,   243,   245,   243,   582,   578,
     589,   578,   244,   582,   578,   582,   578,   243,   582,   243,
     582,     4,   578,   245,     4,     4,   582,   582,   578,   245,
     243,   245,   582,   578,   589,   578,   244,   582,   578,   243,
     578,   578,   243,   578,     4,   578,   578,   245,     4,     4,
     243,   578,     4,   578,     4,     4,   578,   578,     4,     4,
       4,     4,   245,   245,   582,     4,     4,   245,   582,     4,
     781,   589,     4,   784,     4,   589,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
       4,     4,     4,     4,   243,    54,    55,    56,    57,    58,
      59,     4,   784,     4,     4,     4,     4,     4,   819,   820,
     821,   245,   245,   824,   245,   245,     4,   828,     4,     4,
     245,   245,   243,     4,   243,     4,     4,     4,    87,    88,
     780,   784,     4,   243,   245,     4,   243,   819,   820,   821,
       4,   823,   824,    11,    12,     4,     4,    15,     4,     4,
       4,   243,     4,    21,    22,    23,   115,   116,   243,   243,
       4,     4,     4,     4,     4,     4,   819,   820,   821,     4,
     823,   824,     4,     4,     4,   134,   135,   136,   137,   243,
       4,     4,     4,   245,     4,     4,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
     245,   245,   245,     4,     4,   245,     4,   243,     4,   243,
      98,    99,   100,   101,   243,     4,     4,     4,   106,   243,
       4,     7,   242,   242,     7,     7,     7,   115,   116,     7,
       5,   242,   242,     5,   122,   123,   124,   125,   126,   127,
     128,     5,     5,   131,   242,   242,     5,     7,   242,     5,
       5,     5,   140,     5,     7,     5,     5,   242,   242,     7,
       7,   149,     7,   242,   152,     7,     5,     7,     5,     7,
     141,   159,     7,     5,     5,     5,     4,   206,     7,   167,
     168,   242,   242,     5,   172,   173,   242,     7,   242,   242,
       7,   242,     7,   242,   242,   242,   242,   242,   242,   242,
     242,   242,   242,   191,   242,   242,   242,   195,     7,     7,
       7,     7,   242,     7,     7,     7,     7,     7,     4,     4,
       4,     4,     4,   211,   212,   213,   214,   215,   216,   217,
       4,     4,     4,     4,     4,     4,     4,     3,   226,     6,
       3,     6,     6,     3,     6,     3,     3,     6,   242,     3,
       6,     6,     3,     6,   242,     3,     6,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       3,     3,     6,     4,     4,     4,     4,   243,  1109,     6,
       6,  1112,     3,     8,  1115,     4,     6,  1118,     4,     4,
    1115,  1109,  1109,     4,  1115,  1109,   245,  1112,   243,  1130,
    1115,  1118,  1133,  1118,  1118,  1136,     4,  1109,   245,   243,
    1112,   243,   243,  1115,  1109,  1130,  1118,   243,   243,   243,
    1109,  1152,   245,  1118,   243,     4,  1157,     4,  1130,  1118,
       4,  1133,     4,     4,  1109,  1166,  1109,  1168,     4,  1112,
     243,  1130,  1115,  1118,  1133,  1118,   243,  1178,   243,   243,
    1152,  1182,   243,  1109,     4,  1157,  1187,  1130,   243,  1190,
    1133,  1109,  1118,  1178,  1166,     4,  1168,  1190,   245,  1109,
    1118,  1109,  1109,  1175,  1130,   243,  1178,   243,  1118,  1152,
    1118,  1118,  1130,     4,  1157,  1187,   243,  1109,  1190,     4,
    1109,  1109,  1130,  1166,  1109,  1168,  1118,  1109,  1187,  1118,
    1118,  1190,  1175,  1118,  1109,  1178,  1118,   243,  1130,  1109,
     243,  1130,  1130,  1118,  1187,  1109,     4,  1190,  1118,  1118,
    1109,     4,  1109,     4,  1118,  1109,   245,  1109,     4,  1118,
     243,  1118,   243,  1109,  1118,   245,  1118,     4,   245,  1109,
       6,     3,  1118,  1118,  1109,     8,  1109,  1187,  1118,  1109,
    1187,  1109,  1109,  1118,  1109,  1118,  1109,  1109,  1118,     8,
    1118,  1118,  1109,  1118,  1109,  1118,  1118,  1109,  1109,     4,
       4,  1118,  1187,  1118,     3,  1187,  1118,  1118,     8,     7,
    1118,   242,  1187,     8,  1118,     5,     4,  1187,  1187,     4,
     242,  1190,     4,  1187,     7,     4,   245,     4,  1187,     3,
    1187,     6,     5,  1187,     4,  1187,     4,     4,     4,   182,
       5,  1187,  1187,     7,     7,  1190,     4,  1187,   242,   242,
     242,     6,  1187,     3,   242,   242,     4,     4,   242,   242,
     242,     4,   242,   242,   242,   242,   242,     4,     4,   243,
     245,   242,   242,   242,     4,   242,   242,   242,     4,  1187,
    1381,   245,  1190,  1187,   243,   243,  1190,   242,   242,  1390,
     242,   242,   557,   812,  1381,   766,  1381,  1381,   781,   784,
     867,  1341,  1108,  1404,   564,  1390,  1103,  1128,  1215,  1381,
    1121,  1412,  1124,  1157,  1136,  1138,  1381,  1145,  1390,  1111,
    1109,   578,  1381,   620,  1381,  1120,    77,  1412,  1114,  1112,
     610,  1390,  1404,   617,  1115,  1117,  1381,  1192,  1381,   582,
    1412,  1189,  1187,  1190,  1135,  1133,   840,  1390,   600,  1450,
     589,  1452,  1132,  1390,  1152,  1381,  1454,  1170,  1168,  1166,
    1480,  1404,  1506,  1381,  1390,  1535,  1175,  1452,  1450,  1412,
    1412,  1381,  1390,  1381,  1381,   630,   783,   824,  1450,  1480,
    1452,   634,  1390,  1513,  1483,  1179,    -1,    -1,    -1,  1381,
      -1,    -1,  1381,  1381,    -1,  1480,  1381,  1182,  1390,  1381,
      -1,  1390,  1390,  1504,    -1,    -1,  1381,  1450,  1480,  1452,
      -1,  1381,  1381,    -1,    -1,    -1,    -1,  1381,    -1,    -1,
      -1,    -1,  1381,    -1,  1381,    -1,    -1,  1381,    -1,  1381,
      -1,    -1,  1504,    -1,  1535,  1381,  1381,  1480,    -1,    -1,
      -1,  1381,    -1,    -1,    -1,    -1,  1381,    -1,  1381,    -1,
      -1,  1381,    -1,  1381,  1381,    -1,  1381,    -1,  1381,  1381,
      -1,  1504,    -1,  1535,  1381,    -1,  1381,    -1,    -1,  1381,
    1381,    -1,    -1,  1381,    -1,    -1,    -1,  1381,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,  1535,    -1,    -1,    -1,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      -1,    87,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    99,   100,   101,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   115,
     116,    -1,   118,   119,    -1,   121,   122,   123,   124,    -1,
      -1,    -1,    -1,    -1,    -1,   131,   132,   133,    -1,    -1,
      -1,    -1,   138,    -1,    -1,    72,    73,    74,    75,    76,
      77,    78,   148,    80,    81,    82,    83,    -1,    -1,    -1,
      87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,    -1,
      -1,   108,    -1,    -1,    -1,    -1,    -1,    -1,   115,   116,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   131,   132,   133,    -1,    -1,    -1,
      -1,   138,   139,    -1,    -1,   211,   212,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   242,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   211,   212,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   242
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
       0,     5,     7,     9,   242,   243,   244,   245,   262,   263,
     264,   269,     7,   278,     7,   283,     7,   343,     7,   459,
       7,   543,     7,   560,     7,   577,     7,   492,     7,   498,
       7,   522,     7,   435,     7,   694,     7,   713,   270,   265,
     279,   284,   344,   460,   544,   561,   578,   493,   499,   523,
     436,   695,   714,   262,   271,   272,   242,   267,   268,    10,
     280,   282,    11,    12,    15,    21,    22,    23,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    98,    99,   100,   101,   106,   115,   116,   122,
     123,   124,   125,   126,   127,   128,   131,   140,   149,   152,
     159,   167,   168,   172,   173,   191,   195,   211,   212,   213,
     214,   215,   216,   217,   226,   242,   277,   285,   286,   287,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   310,
     312,   314,   315,   316,   319,   320,   321,   322,   323,   325,
     327,   328,   329,   330,   332,   333,   335,   337,   338,   339,
     340,   341,   353,   355,   357,   400,   408,   414,   420,   422,
     429,   443,   453,   477,   478,   479,   482,   490,   516,   550,
     552,   571,   601,   617,   629,   630,   632,   682,   692,   711,
     720,   744,    16,    17,    18,    19,    20,   277,   345,   346,
     347,   349,   350,   351,   352,   550,   552,   107,   109,   117,
     118,   119,   120,   121,   131,   132,   133,   138,   148,   277,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   304,   305,   306,   307,   310,   312,
     314,   315,   316,   319,   320,   321,   322,   323,   325,   327,
     333,   335,   461,   462,   463,   465,   467,   469,   471,   473,
     475,   477,   478,   479,   480,   481,   516,   537,   550,   552,
     554,   571,   598,   108,   139,   277,   304,   305,   306,   307,
     310,   312,   314,   316,   319,   320,   321,   322,   323,   325,
     469,   471,   473,   475,   516,   545,   546,   547,   549,   550,
     552,   110,   111,   112,   113,   114,   277,   469,   471,   473,
     475,   516,   549,   550,   552,   562,   563,   564,   566,   567,
     569,   570,   131,   141,   142,   143,   144,   145,   146,   147,
     277,   516,   550,   552,   579,   580,   581,   582,   584,   586,
     588,   590,   592,   594,   596,   490,    24,    88,    90,    91,
      95,    96,    97,   277,   374,   500,   501,   502,   503,   504,
     505,   506,   508,   510,   512,   513,   515,   550,   552,    89,
      92,    93,    94,   131,   277,   374,   504,   510,   524,   525,
     526,   527,   528,   530,   531,   532,   533,   534,   535,   550,
     552,   150,   151,   277,   437,   438,   439,   441,   196,   197,
     198,   199,   200,   201,   202,   203,   277,   550,   552,   696,
     697,   698,   699,   701,   702,   704,   705,   706,   709,    13,
      14,   715,   716,   717,   719,     6,     3,     4,     8,     3,
     281,     3,     8,   288,   712,   342,   354,   356,   358,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   331,     4,     4,     4,     4,     4,
     308,   311,   313,     4,     4,     4,     4,     4,     4,     4,
     454,   491,   517,     4,   334,   336,   317,   483,   551,   553,
       4,     4,     4,   409,   421,   415,   401,   602,   572,   430,
     444,   618,     4,   423,   631,   633,   683,   693,   324,   326,
       4,     4,     4,     4,   721,   745,     4,     3,     8,   348,
       4,     4,     4,     4,     3,     8,   538,   555,   464,   466,
     468,     4,     4,   472,   474,   476,   470,   599,     3,     8,
     548,     4,     3,     8,   565,     4,   568,     4,     4,     3,
       8,   597,   583,   585,   587,   589,   591,   593,   595,     8,
       3,     8,   507,   375,     4,   511,   509,   514,     4,     8,
       3,   529,     4,     4,     4,   536,     8,     3,   440,   442,
       3,     8,     4,   700,     4,   703,     4,     4,   707,   710,
       3,     8,   718,     4,     3,     8,   262,   262,   242,     4,
       4,     4,     4,     4,     4,     4,   243,   243,   243,   243,
     243,   243,   243,   243,   245,   244,   244,   244,   243,   244,
     243,     4,   243,   243,   245,   245,   245,     4,     4,     4,
     245,   245,   244,   243,   243,   243,   245,     4,     4,     4,
     243,     4,     4,     4,     4,     4,     4,   245,   245,   245,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   243,
       4,     4,     4,     4,     4,     4,     4,   245,   245,   245,
     245,     4,     4,   286,     4,   245,   245,   243,   243,   346,
       4,     4,     4,     4,     4,   243,   245,     4,     4,     4,
       4,     4,   462,     4,   243,   546,     4,   243,     4,   243,
     243,   563,     4,     4,     4,     4,     4,     4,     4,     4,
     581,     4,     4,   243,     4,     4,     4,   245,   502,     4,
     245,   245,   245,     4,   526,     4,     4,   438,   245,     4,
     243,     4,   243,   243,     4,     4,   697,     4,   243,   716,
       4,     7,   242,     7,     7,     7,     7,     5,   242,   207,
     208,   209,   210,   245,   309,   242,   242,     5,     5,     5,
     242,   242,   102,   103,   104,   105,   318,     5,   264,   266,
     242,     5,     5,     5,     7,     5,     5,     5,     7,     7,
       7,     7,     5,     7,     7,   242,   242,     5,     7,     5,
     273,     5,     5,   242,   242,   242,   273,   273,   273,   242,
       7,   242,   242,   242,   273,   273,   273,   273,   242,   242,
     242,   242,   242,   242,   242,   242,   242,   242,   273,   242,
     266,   242,   242,   204,   205,   708,   206,     5,   262,   285,
     715,   345,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,   277,
     363,   364,   365,   367,   369,   371,   373,   374,   376,   377,
     378,   379,   380,   381,   382,   383,   384,   387,   388,   389,
     390,   392,   394,   396,   398,   363,     7,   359,   360,   361,
       7,   455,   456,   457,     7,   494,   495,   496,     7,   518,
     519,   520,     7,   484,   485,   486,   144,   242,   410,   411,
     412,   413,   271,   145,   147,   412,   416,   417,   418,   419,
     129,   130,   402,   403,   404,   406,     7,   603,   604,   605,
       7,   573,   574,   575,     7,   431,   432,   433,   153,   154,
     155,   156,   157,   158,   445,   446,   447,   448,   449,   450,
     451,   452,    24,   163,   164,   165,   166,   277,   376,   550,
     552,   619,   620,   621,   624,   625,   627,   628,   169,   170,
     171,   277,   424,   425,   426,   427,   428,   550,   552,   174,
     178,   179,   180,   181,   188,   189,   277,   390,   392,   394,
     550,   552,   638,   639,   640,   643,   645,   647,   648,   649,
     659,     7,   634,   635,   636,   192,   193,   194,   242,   550,
     552,   684,   685,   686,   687,   689,   690,   696,     7,   722,
     723,   227,   277,   746,   747,   748,   274,     7,   539,   540,
     541,     7,   556,   557,   558,   582,   600,   359,     8,     8,
       8,   366,   368,   370,   372,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   385,     4,     4,   391,   393,
     395,   397,   399,     3,     8,     8,   362,     6,     3,   458,
       6,     3,   497,     6,     3,   521,     6,     3,   487,     6,
       3,     3,     6,     6,     3,     6,   405,   407,     3,     8,
     606,     6,     3,   576,     6,     3,   434,     6,     3,     4,
       4,     4,     4,     4,     4,     3,     8,   622,   626,     4,
       4,     4,     3,     8,     4,     4,     4,     3,     8,   641,
     644,   646,     4,   660,     4,   650,     3,     8,   637,     6,
       3,     4,   688,     4,   691,     3,     8,     8,   724,     3,
       6,     4,     3,     8,   242,   275,   276,   542,     6,     3,
     559,     6,     3,     8,     6,     4,     4,     4,     4,   243,
     245,   243,   245,   243,   243,   243,   243,   243,   243,     4,
     245,   243,     4,     4,     4,     4,     4,   364,   363,   361,
     461,   457,   500,   496,   524,   520,   277,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   304,   305,   306,   307,   310,   312,   314,   315,   316,
     319,   320,   321,   322,   323,   325,   327,   333,   335,   374,
     453,   465,   467,   469,   471,   473,   475,   477,   478,   479,
     481,   488,   489,   516,   550,   552,   598,   486,   411,   417,
       4,     4,   403,   134,   135,   136,   137,   277,   289,   290,
     291,   292,   293,   294,   374,   516,   550,   552,   607,   608,
     609,   610,   611,   613,   615,   616,   605,   579,   575,   437,
     433,   243,   243,   243,   243,   243,   243,   446,     4,     4,
     243,   243,   243,   620,   245,   243,   243,   425,     4,     4,
       4,   243,     4,   245,     4,   639,   638,   636,   245,     4,
     243,     4,   685,   218,   220,   221,   277,   374,   550,   552,
     725,   726,   727,   728,   730,   723,   245,   747,     6,     3,
     545,   541,   562,   558,   242,   242,   242,   242,    39,    40,
      41,   386,   242,   242,   242,   396,   242,     8,     8,     8,
       8,     3,     8,   242,   242,   612,   614,     4,     4,     8,
       3,     8,     8,   160,   161,   162,   623,   242,   175,   176,
     177,   642,   242,   242,     7,     5,     8,   242,   262,   731,
       4,   729,     3,     8,   242,     8,     8,   489,     4,     4,
     245,   245,   609,    24,   183,   184,   185,   277,   550,   552,
     661,   662,   663,   666,   668,   670,     7,   651,   652,   653,
       4,   243,     4,   726,   242,   242,   664,   667,   669,   671,
       3,     8,   654,     6,     3,     5,   242,     4,     4,     4,
       4,   662,   190,   277,   374,   550,   552,   655,   656,   657,
     653,     7,   732,   733,   182,   665,   242,   242,     5,   658,
       3,     8,   734,     3,     6,     7,   672,   673,   674,     4,
     656,   219,   222,   223,   224,   225,   735,   736,   737,   739,
     740,   741,   742,   733,   675,     6,     3,   242,   738,     4,
       4,     4,   743,     3,     8,   186,   187,   277,   367,   369,
     550,   552,   676,   677,   678,   680,   674,     4,   245,   243,
     243,     4,   736,   679,   681,     3,     8,   242,   242,     4,
       4,   677,   242,   242
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   246,   248,   247,   249,   247,   250,   247,   251,   247,
     252,   247,   253,   247,   254,   247,   255,   247,   256,   247,
     257,   247,   258,   247,   259,   247,   260,   247,   261,   247,
     262,   262,   262,   262,   262,   262,   262,   263,   265,   264,
     266,   267,   267,   268,   268,   268,   270,   269,   271,   271,
     272,   272,   272,   274,   273,   275,   275,   276,   276,   276,
     277,   279,   278,   281,   280,   280,   282,   284,   283,   285,
     285,   285,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   288,   287,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   308,   307,   309,   309,
     309,   309,   309,   311,   310,   313,   312,   314,   315,   317,
     316,   318,   318,   318,   318,   319,   320,   321,   322,   324,
     323,   326,   325,   327,   328,   329,   331,   330,   332,   334,
     333,   336,   335,   337,   338,   339,   340,   342,   341,   344,
     343,   345,   345,   345,   346,   346,   346,   346,   346,   346,
     346,   346,   348,   347,   349,   350,   351,   352,   354,   353,
     356,   355,   358,   357,   359,   359,   360,   360,   360,   362,
     361,   363,   363,   363,   364,   364,   364,   364,   364,   364,
     364,   364,   364,   364,   364,   364,   364,   364,   364,   364,
     364,   364,   364,   364,   364,   364,   364,   364,   366,   365,
     368,   367,   370,   369,   372,   371,   373,   375,   374,   376,
     377,   378,   379,   380,   381,   382,   383,   385,   384,   386,
     386,   386,   387,   388,   389,   391,   390,   393,   392,   395,
     394,   397,   396,   396,   396,   396,   396,   396,   399,   398,
     401,   400,   402,   402,   402,   403,   403,   405,   404,   407,
     406,   409,   408,   410,   410,   410,   411,   411,   412,   413,
     415,   414,   416,   416,   416,   417,   417,   417,   418,   419,
     421,   420,   423,   422,   424,   424,   424,   425,   425,   425,
     425,   425,   425,   426,   427,   428,   430,   429,   431,   431,
     432,   432,   432,   434,   433,   436,   435,   437,   437,   437,
     437,   438,   438,   440,   439,   442,   441,   444,   443,   445,
     445,   445,   446,   446,   446,   446,   446,   446,   447,   448,
     449,   450,   451,   452,   454,   453,   455,   455,   456,   456,
     456,   458,   457,   460,   459,   461,   461,   461,   462,   462,
     462,   462,   462,   462,   462,   462,   462,   462,   462,   462,
     462,   462,   462,   462,   462,   462,   462,   462,   462,   462,
     462,   462,   462,   462,   462,   462,   462,   462,   462,   462,
     462,   462,   462,   462,   462,   462,   462,   462,   462,   462,
     462,   462,   462,   462,   462,   462,   462,   462,   462,   462,
     464,   463,   466,   465,   468,   467,   470,   469,   472,   471,
     474,   473,   476,   475,   477,   478,   479,   480,   481,   483,
     482,   484,   484,   485,   485,   485,   487,   486,   488,   488,
     488,   489,   489,   489,   489,   489,   489,   489,   489,   489,
     489,   489,   489,   489,   489,   489,   489,   489,   489,   489,
     489,   489,   489,   489,   489,   489,   489,   489,   489,   489,
     489,   489,   489,   489,   489,   489,   489,   489,   489,   489,
     489,   489,   489,   489,   489,   489,   489,   489,   489,   489,
     491,   490,   493,   492,   494,   494,   495,   495,   495,   497,
     496,   499,   498,   500,   500,   501,   501,   501,   502,   502,
     502,   502,   502,   502,   502,   502,   502,   502,   503,   504,
     505,   507,   506,   509,   508,   511,   510,   512,   514,   513,
     515,   517,   516,   518,   518,   519,   519,   519,   521,   520,
     523,   522,   524,   524,   525,   525,   525,   526,   526,   526,
     526,   526,   526,   526,   526,   526,   526,   526,   527,   529,
     528,   530,   531,   532,   533,   534,   536,   535,   538,   537,
     539,   539,   540,   540,   540,   542,   541,   544,   543,   545,
     545,   545,   546,   546,   546,   546,   546,   546,   546,   546,
     546,   546,   546,   546,   546,   546,   546,   546,   546,   546,
     546,   546,   546,   546,   546,   546,   548,   547,   549,   551,
     550,   553,   552,   555,   554,   556,   556,   557,   557,   557,
     559,   558,   561,   560,   562,   562,   562,   563,   563,   563,
     563,   563,   563,   563,   563,   563,   563,   563,   563,   563,
     563,   565,   564,   566,   568,   567,   569,   570,   572,   571,
     573,   573,   574,   574,   574,   576,   575,   578,   577,   579,
     579,   580,   580,   580,   581,   581,   581,   581,   581,   581,
     581,   581,   581,   581,   581,   581,   583,   582,   585,   584,
     587,   586,   589,   588,   591,   590,   593,   592,   595,   594,
     597,   596,   599,   598,   600,   602,   601,   603,   603,   604,
     604,   604,   606,   605,   607,   607,   608,   608,   608,   609,
     609,   609,   609,   609,   609,   609,   609,   609,   609,   609,
     609,   609,   609,   609,   610,   612,   611,   614,   613,   615,
     616,   618,   617,   619,   619,   619,   620,   620,   620,   620,
     620,   620,   620,   620,   620,   622,   621,   623,   623,   623,
     624,   626,   625,   627,   628,   629,   631,   630,   633,   632,
     634,   634,   635,   635,   635,   637,   636,   638,   638,   638,
     639,   639,   639,   639,   639,   639,   639,   639,   639,   639,
     639,   639,   639,   641,   640,   642,   642,   642,   644,   643,
     646,   645,   647,   648,   650,   649,   651,   651,   652,   652,
     652,   654,   653,   655,   655,   655,   656,   656,   656,   656,
     656,   658,   657,   660,   659,   661,   661,   661,   662,   662,
     662,   662,   662,   662,   662,   664,   663,   665,   667,   666,
     669,   668,   671,   670,   672,   672,   673,   673,   673,   675,
     674,   676,   676,   676,   677,   677,   677,   677,   677,   677,
     677,   679,   678,   681,   680,   683,   682,   684,   684,   684,
     685,   685,   685,   685,   685,   685,   686,   688,   687,   689,
     691,   690,   693,   692,   695,   694,   696,   696,   696,   697,
     697,   697,   697,   697,   697,   697,   697,   697,   697,   697,
     698,   700,   699,   701,   703,   702,   704,   705,   707,   706,
     708,   708,   710,   709,   712,   711,   714,   713,   715,   715,
     715,   716,   716,   718,   717,   719,   721,   720,   722,   722,
     722,   724,   723,   725,   725,   725,   726,   726,   726,   726,
     726,   726,   726,   727,   729,   728,   731,   730,   732,   732,
     732,   734,   733,   735,   735,   735,   736,   736,   736,   736,
     736,   738,   737,   739,   740,   741,   743,   742,   745,   744,
     746,   746,   746,   747,   747,   748
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
       1,     1,     1,     0,     4,     0,     4,     3,     3,     0,
       4,     1,     1,     1,     1,     3,     3,     3,     3,     0,
       4,     0,     4,     3,     3,     3,     0,     4,     3,     0,
       4,     0,     4,     3,     3,     3,     3,     0,     6,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     3,     3,     3,     0,     6,
       0,     6,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     0,     4,     1,
       1,     1,     3,     3,     3,     0,     4,     0,     4,     0,
       4,     0,     4,     1,     1,     1,     1,     1,     0,     4,
       0,     6,     1,     3,     2,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       0,     6,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     1,     3,     2,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     1,     3,     2,     1,     1,
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     4,     3,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     0,
       1,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     1,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     0,     1,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     3,
       3,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       3,     0,     4,     3,     3,     3,     0,     6,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     0,     4,
       0,     4,     3,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     0,     4,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     0,     4,
       0,     4,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     6,     1,     3,     2,
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
       0,   341,   341,   341,   342,   342,   343,   343,   344,   344,
     345,   345,   346,   346,   347,   347,   348,   348,   349,   349,
     350,   350,   351,   351,   352,   352,   353,   353,   354,   354,
     362,   363,   364,   365,   366,   367,   368,   371,   376,   376,
     387,   390,   391,   394,   399,   405,   410,   410,   417,   418,
     421,   425,   429,   435,   435,   442,   443,   446,   450,   454,
     464,   473,   473,   488,   488,   502,   505,   511,   511,   520,
     521,   522,   529,   530,   531,   532,   533,   534,   535,   536,
     537,   538,   539,   540,   541,   542,   543,   544,   545,   546,
     547,   548,   549,   550,   551,   552,   553,   554,   555,   556,
     557,   558,   559,   560,   561,   562,   563,   564,   565,   566,
     567,   568,   569,   570,   571,   572,   573,   574,   575,   576,
     577,   578,   579,   580,   581,   582,   583,   584,   585,   586,
     587,   588,   589,   590,   591,   592,   593,   594,   595,   596,
     597,   598,   599,   600,   601,   602,   605,   605,   615,   621,
     627,   633,   639,   645,   651,   657,   663,   669,   675,   681,
     687,   693,   699,   705,   711,   717,   723,   723,   732,   735,
     738,   741,   744,   750,   750,   759,   759,   768,   777,   787,
     787,   796,   799,   802,   805,   810,   816,   822,   828,   834,
     834,   843,   843,   852,   858,   864,   870,   870,   879,   885,
     885,   894,   894,   903,   909,   915,   921,   927,   927,   939,
     939,   948,   949,   950,   955,   956,   957,   958,   959,   960,
     961,   962,   965,   965,   976,   982,   988,   994,  1000,  1000,
    1013,  1013,  1026,  1026,  1037,  1038,  1041,  1042,  1043,  1048,
    1048,  1058,  1059,  1060,  1065,  1066,  1067,  1068,  1069,  1070,
    1071,  1072,  1073,  1074,  1075,  1076,  1077,  1078,  1079,  1080,
    1081,  1082,  1083,  1084,  1085,  1086,  1087,  1088,  1091,  1091,
    1100,  1100,  1109,  1109,  1118,  1118,  1127,  1133,  1133,  1142,
    1148,  1154,  1160,  1166,  1172,  1178,  1184,  1190,  1190,  1198,
    1199,  1200,  1203,  1209,  1215,  1221,  1221,  1230,  1230,  1239,
    1239,  1248,  1248,  1256,  1259,  1262,  1265,  1268,  1273,  1273,
    1282,  1282,  1293,  1294,  1295,  1300,  1301,  1304,  1304,  1323,
    1323,  1341,  1341,  1352,  1353,  1354,  1359,  1360,  1363,  1368,
    1373,  1373,  1384,  1385,  1386,  1391,  1392,  1393,  1396,  1401,
    1408,  1408,  1421,  1421,  1434,  1435,  1436,  1441,  1442,  1443,
    1444,  1445,  1446,  1449,  1455,  1461,  1467,  1467,  1478,  1479,
    1482,  1483,  1484,  1489,  1489,  1499,  1499,  1509,  1510,  1511,
    1514,  1517,  1518,  1521,  1521,  1530,  1530,  1539,  1539,  1551,
    1552,  1553,  1558,  1559,  1560,  1561,  1562,  1563,  1566,  1572,
    1578,  1584,  1590,  1596,  1605,  1605,  1619,  1620,  1623,  1624,
    1625,  1634,  1634,  1660,  1660,  1671,  1672,  1673,  1679,  1680,
    1681,  1682,  1683,  1684,  1685,  1686,  1687,  1688,  1689,  1690,
    1691,  1692,  1693,  1694,  1695,  1696,  1697,  1698,  1699,  1700,
    1701,  1702,  1703,  1704,  1705,  1706,  1707,  1708,  1709,  1710,
    1711,  1712,  1713,  1714,  1715,  1716,  1717,  1718,  1719,  1720,
    1721,  1722,  1723,  1724,  1725,  1726,  1727,  1728,  1729,  1730,
    1733,  1733,  1742,  1742,  1751,  1751,  1760,  1760,  1770,  1770,
    1782,  1782,  1793,  1793,  1804,  1810,  1816,  1822,  1828,  1836,
    1836,  1848,  1849,  1853,  1854,  1855,  1860,  1860,  1868,  1869,
    1870,  1875,  1876,  1877,  1878,  1879,  1880,  1881,  1882,  1883,
    1884,  1885,  1886,  1887,  1888,  1889,  1890,  1891,  1892,  1893,
    1894,  1895,  1896,  1897,  1898,  1899,  1900,  1901,  1902,  1903,
    1904,  1905,  1906,  1907,  1908,  1909,  1910,  1911,  1912,  1913,
    1914,  1915,  1916,  1917,  1918,  1919,  1920,  1921,  1922,  1923,
    1930,  1930,  1944,  1944,  1953,  1954,  1957,  1958,  1959,  1966,
    1966,  1981,  1981,  1995,  1996,  1999,  2000,  2001,  2006,  2007,
    2008,  2009,  2010,  2011,  2012,  2013,  2014,  2015,  2018,  2020,
    2026,  2028,  2028,  2037,  2037,  2046,  2046,  2055,  2057,  2057,
    2066,  2076,  2076,  2089,  2090,  2095,  2096,  2097,  2104,  2104,
    2116,  2116,  2128,  2129,  2134,  2135,  2136,  2143,  2144,  2145,
    2146,  2147,  2148,  2149,  2150,  2151,  2152,  2153,  2156,  2158,
    2158,  2167,  2169,  2171,  2177,  2183,  2189,  2189,  2203,  2203,
    2216,  2217,  2220,  2221,  2222,  2227,  2227,  2237,  2237,  2247,
    2248,  2249,  2254,  2255,  2256,  2257,  2258,  2259,  2260,  2261,
    2262,  2263,  2264,  2265,  2266,  2267,  2268,  2269,  2270,  2271,
    2272,  2273,  2274,  2275,  2276,  2277,  2280,  2280,  2289,  2295,
    2295,  2320,  2320,  2350,  2350,  2363,  2364,  2367,  2368,  2369,
    2374,  2374,  2386,  2386,  2398,  2399,  2400,  2405,  2406,  2407,
    2408,  2409,  2410,  2411,  2412,  2413,  2414,  2415,  2416,  2417,
    2418,  2421,  2421,  2430,  2436,  2436,  2445,  2451,  2460,  2460,
    2471,  2472,  2475,  2476,  2477,  2482,  2482,  2491,  2491,  2500,
    2501,  2504,  2505,  2506,  2512,  2513,  2514,  2515,  2516,  2517,
    2518,  2519,  2520,  2521,  2522,  2523,  2526,  2526,  2537,  2537,
    2548,  2548,  2559,  2559,  2568,  2568,  2577,  2577,  2586,  2586,
    2595,  2595,  2609,  2609,  2620,  2626,  2626,  2637,  2638,  2641,
    2642,  2643,  2648,  2648,  2658,  2659,  2662,  2663,  2664,  2669,
    2670,  2671,  2672,  2673,  2674,  2675,  2676,  2677,  2678,  2679,
    2680,  2681,  2682,  2683,  2686,  2688,  2688,  2697,  2697,  2707,
    2713,  2722,  2722,  2735,  2736,  2737,  2742,  2743,  2744,  2745,
    2746,  2747,  2748,  2749,  2750,  2753,  2753,  2761,  2762,  2763,
    2766,  2772,  2772,  2781,  2787,  2795,  2803,  2803,  2815,  2815,
    2827,  2828,  2831,  2832,  2833,  2838,  2838,  2846,  2847,  2848,
    2853,  2854,  2855,  2856,  2857,  2858,  2859,  2860,  2861,  2862,
    2863,  2864,  2865,  2868,  2868,  2877,  2878,  2879,  2882,  2882,
    2892,  2892,  2902,  2908,  2914,  2914,  2925,  2926,  2929,  2930,
    2931,  2936,  2936,  2944,  2945,  2946,  2951,  2952,  2953,  2954,
    2955,  2958,  2958,  2969,  2969,  2982,  2983,  2984,  2989,  2990,
    2991,  2992,  2993,  2994,  2995,  2998,  2998,  3006,  3009,  3009,
    3018,  3018,  3027,  3027,  3038,  3039,  3042,  3043,  3044,  3049,
    3049,  3057,  3058,  3059,  3064,  3065,  3066,  3067,  3068,  3069,
    3070,  3073,  3073,  3082,  3082,  3093,  3093,  3106,  3107,  3108,
    3113,  3114,  3115,  3116,  3117,  3118,  3121,  3127,  3127,  3136,
    3142,  3142,  3152,  3152,  3165,  3165,  3175,  3176,  3177,  3182,
    3183,  3184,  3185,  3186,  3187,  3188,  3189,  3190,  3191,  3192,
    3195,  3201,  3201,  3210,  3216,  3216,  3225,  3231,  3237,  3237,
    3246,  3247,  3250,  3250,  3261,  3261,  3273,  3273,  3283,  3284,
    3285,  3291,  3292,  3295,  3295,  3306,  3314,  3314,  3327,  3328,
    3329,  3335,  3335,  3343,  3344,  3345,  3350,  3351,  3352,  3353,
    3354,  3355,  3356,  3359,  3365,  3365,  3374,  3374,  3385,  3386,
    3387,  3392,  3392,  3400,  3401,  3402,  3407,  3408,  3409,  3410,
    3411,  3414,  3414,  3423,  3429,  3435,  3441,  3441,  3450,  3450,
    3461,  3462,  3463,  3468,  3469,  3472
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
#line 7205 "dhcp6_parser.cc"

#line 3478 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
