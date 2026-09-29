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

  case 177: // $@25: %empty
#line 768 "dhcp6_parser.yy"
                                     {
    ctx.unique("ddns-reverse-zone", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1449 "dhcp6_parser.cc"
    break;

  case 178: // ddns_reverse_zone: "ddns-reverse-zone" $@25 ":" "constant string"
#line 771 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-reverse-zone", s);
    ctx.leave();
}
#line 1459 "dhcp6_parser.cc"
    break;

  case 179: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 777 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1469 "dhcp6_parser.cc"
    break;

  case 180: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 786 "dhcp6_parser.yy"
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
#line 796 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1492 "dhcp6_parser.cc"
    break;

  case 182: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@26 ":" ddns_conflict_resolution_mode_value
#line 799 "dhcp6_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1501 "dhcp6_parser.cc"
    break;

  case 183: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 805 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1509 "dhcp6_parser.cc"
    break;

  case 184: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 808 "dhcp6_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1517 "dhcp6_parser.cc"
    break;

  case 185: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 811 "dhcp6_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1525 "dhcp6_parser.cc"
    break;

  case 186: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 814 "dhcp6_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1533 "dhcp6_parser.cc"
    break;

  case 187: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 819 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1543 "dhcp6_parser.cc"
    break;

  case 188: // ddns_ttl: "ddns-ttl" ":" "integer"
#line 825 "dhcp6_parser.yy"
                                 {
    ctx.unique("ddns-ttl", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl", ttl);
}
#line 1553 "dhcp6_parser.cc"
    break;

  case 189: // ddns_ttl_min: "ddns-ttl-min" ":" "integer"
#line 831 "dhcp6_parser.yy"
                                         {
    ctx.unique("ddns-ttl-min", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-min", ttl);
}
#line 1563 "dhcp6_parser.cc"
    break;

  case 190: // ddns_ttl_max: "ddns-ttl-max" ":" "integer"
#line 837 "dhcp6_parser.yy"
                                         {
    ctx.unique("ddns-ttl-max", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-max", ttl);
}
#line 1573 "dhcp6_parser.cc"
    break;

  case 191: // $@27: %empty
#line 843 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1582 "dhcp6_parser.cc"
    break;

  case 192: // hostname_char_set: "hostname-char-set" $@27 ":" "constant string"
#line 846 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1592 "dhcp6_parser.cc"
    break;

  case 193: // $@28: %empty
#line 852 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1601 "dhcp6_parser.cc"
    break;

  case 194: // hostname_char_replacement: "hostname-char-replacement" $@28 ":" "constant string"
#line 855 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1611 "dhcp6_parser.cc"
    break;

  case 195: // store_extended_info: "store-extended-info" ":" "boolean"
#line 861 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1621 "dhcp6_parser.cc"
    break;

  case 196: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 867 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1631 "dhcp6_parser.cc"
    break;

  case 197: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 873 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1641 "dhcp6_parser.cc"
    break;

  case 198: // $@29: %empty
#line 879 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1650 "dhcp6_parser.cc"
    break;

  case 199: // server_tag: "server-tag" $@29 ":" "constant string"
#line 882 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1660 "dhcp6_parser.cc"
    break;

  case 200: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 888 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1670 "dhcp6_parser.cc"
    break;

  case 201: // $@30: %empty
#line 894 "dhcp6_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1679 "dhcp6_parser.cc"
    break;

  case 202: // allocator: "allocator" $@30 ":" "constant string"
#line 897 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1689 "dhcp6_parser.cc"
    break;

  case 203: // $@31: %empty
#line 903 "dhcp6_parser.yy"
                           {
    ctx.unique("pd-allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1698 "dhcp6_parser.cc"
    break;

  case 204: // pd_allocator: "pd-allocator" $@31 ":" "constant string"
#line 906 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-allocator", al);
    ctx.leave();
}
#line 1708 "dhcp6_parser.cc"
    break;

  case 205: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 912 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1718 "dhcp6_parser.cc"
    break;

  case 206: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 918 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1728 "dhcp6_parser.cc"
    break;

  case 207: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 924 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1738 "dhcp6_parser.cc"
    break;

  case 208: // allow_address_registration: "allow-address-registration" ":" "boolean"
#line 930 "dhcp6_parser.yy"
                                                                     {
    ctx.unique("allow-address-registration", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allow-address-registration", first);
}
#line 1748 "dhcp6_parser.cc"
    break;

  case 209: // $@32: %empty
#line 936 "dhcp6_parser.yy"
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
#line 942 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1770 "dhcp6_parser.cc"
    break;

  case 211: // $@33: %empty
#line 948 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1780 "dhcp6_parser.cc"
    break;

  case 212: // sub_interfaces6: "{" $@33 interfaces_config_params "}"
#line 952 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1789 "dhcp6_parser.cc"
    break;

  case 215: // interfaces_config_params: interfaces_config_params ","
#line 959 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1797 "dhcp6_parser.cc"
    break;

  case 224: // $@34: %empty
#line 974 "dhcp6_parser.yy"
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
#line 980 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1818 "dhcp6_parser.cc"
    break;

  case 226: // re_detect: "re-detect" ":" "boolean"
#line 985 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1828 "dhcp6_parser.cc"
    break;

  case 227: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 991 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1838 "dhcp6_parser.cc"
    break;

  case 228: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 997 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1848 "dhcp6_parser.cc"
    break;

  case 229: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 1003 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1858 "dhcp6_parser.cc"
    break;

  case 230: // $@35: %empty
#line 1009 "dhcp6_parser.yy"
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
#line 1015 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1881 "dhcp6_parser.cc"
    break;

  case 232: // $@36: %empty
#line 1022 "dhcp6_parser.yy"
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
#line 1028 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1904 "dhcp6_parser.cc"
    break;

  case 234: // $@37: %empty
#line 1035 "dhcp6_parser.yy"
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
#line 1041 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1925 "dhcp6_parser.cc"
    break;

  case 240: // not_empty_database_list: not_empty_database_list ","
#line 1052 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1933 "dhcp6_parser.cc"
    break;

  case 241: // $@38: %empty
#line 1057 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1943 "dhcp6_parser.cc"
    break;

  case 242: // database: "{" $@38 database_map_params "}"
#line 1061 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1953 "dhcp6_parser.cc"
    break;

  case 245: // database_map_params: database_map_params ","
#line 1069 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1961 "dhcp6_parser.cc"
    break;

  case 271: // $@39: %empty
#line 1101 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1970 "dhcp6_parser.cc"
    break;

  case 272: // database_type: "type" $@39 ":" "constant string"
#line 1104 "dhcp6_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 1980 "dhcp6_parser.cc"
    break;

  case 273: // $@40: %empty
#line 1110 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1989 "dhcp6_parser.cc"
    break;

  case 274: // user: "user" $@40 ":" "constant string"
#line 1113 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1999 "dhcp6_parser.cc"
    break;

  case 275: // $@41: %empty
#line 1119 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2008 "dhcp6_parser.cc"
    break;

  case 276: // password: "password" $@41 ":" "constant string"
#line 1122 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2018 "dhcp6_parser.cc"
    break;

  case 277: // $@42: %empty
#line 1128 "dhcp6_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2027 "dhcp6_parser.cc"
    break;

  case 278: // password_file: "password-file" $@42 ":" "constant string"
#line 1131 "dhcp6_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 2037 "dhcp6_parser.cc"
    break;

  case 279: // $@43: %empty
#line 1137 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2046 "dhcp6_parser.cc"
    break;

  case 280: // host: "host" $@43 ":" "constant string"
#line 1140 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2056 "dhcp6_parser.cc"
    break;

  case 281: // port: "port" ":" "integer"
#line 1146 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2066 "dhcp6_parser.cc"
    break;

  case 282: // $@44: %empty
#line 1152 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2075 "dhcp6_parser.cc"
    break;

  case 283: // name: "name" $@44 ":" "constant string"
#line 1155 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2085 "dhcp6_parser.cc"
    break;

  case 284: // persist: "persist" ":" "boolean"
#line 1161 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2095 "dhcp6_parser.cc"
    break;

  case 285: // lfc_interval: "lfc-interval" ":" "integer"
#line 1167 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2105 "dhcp6_parser.cc"
    break;

  case 286: // readonly: "readonly" ":" "boolean"
#line 1173 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2115 "dhcp6_parser.cc"
    break;

  case 287: // connect_timeout: "connect-timeout" ":" "integer"
#line 1179 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2125 "dhcp6_parser.cc"
    break;

  case 288: // read_timeout: "read-timeout" ":" "integer"
#line 1185 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2135 "dhcp6_parser.cc"
    break;

  case 289: // write_timeout: "write-timeout" ":" "integer"
#line 1191 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2145 "dhcp6_parser.cc"
    break;

  case 290: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1197 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2155 "dhcp6_parser.cc"
    break;

  case 291: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1203 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2165 "dhcp6_parser.cc"
    break;

  case 292: // $@45: %empty
#line 1209 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2174 "dhcp6_parser.cc"
    break;

  case 293: // on_fail: "on-fail" $@45 ":" on_fail_mode
#line 1212 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2183 "dhcp6_parser.cc"
    break;

  case 294: // on_fail_mode: "stop-retry-exit"
#line 1217 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2189 "dhcp6_parser.cc"
    break;

  case 295: // on_fail_mode: "serve-retry-exit"
#line 1218 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2195 "dhcp6_parser.cc"
    break;

  case 296: // on_fail_mode: "serve-retry-continue"
#line 1219 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2201 "dhcp6_parser.cc"
    break;

  case 297: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1222 "dhcp6_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2211 "dhcp6_parser.cc"
    break;

  case 298: // max_row_errors: "max-row-errors" ":" "integer"
#line 1228 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2221 "dhcp6_parser.cc"
    break;

  case 299: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1234 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2231 "dhcp6_parser.cc"
    break;

  case 300: // $@46: %empty
#line 1240 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2240 "dhcp6_parser.cc"
    break;

  case 301: // trust_anchor: "trust-anchor" $@46 ":" "constant string"
#line 1243 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2250 "dhcp6_parser.cc"
    break;

  case 302: // $@47: %empty
#line 1249 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2259 "dhcp6_parser.cc"
    break;

  case 303: // cert_file: "cert-file" $@47 ":" "constant string"
#line 1252 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2269 "dhcp6_parser.cc"
    break;

  case 304: // $@48: %empty
#line 1258 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2278 "dhcp6_parser.cc"
    break;

  case 305: // key_file: "key-file" $@48 ":" "constant string"
#line 1261 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2288 "dhcp6_parser.cc"
    break;

  case 306: // $@49: %empty
#line 1267 "dhcp6_parser.yy"
                   {
    ctx.unique("ssl-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SSL_MODE);
}
#line 2297 "dhcp6_parser.cc"
    break;

  case 307: // ssl_mode: "ssl-mode" $@49 ":" ssl_mode
#line 1270 "dhcp6_parser.yy"
                 {
    ctx.stack_.back()->set("ssl-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2306 "dhcp6_parser.cc"
    break;

  case 308: // ssl_mode: "disable"
#line 1275 "dhcp6_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disable", ctx.loc2pos(yystack_[0].location)));
            }
#line 2314 "dhcp6_parser.cc"
    break;

  case 309: // ssl_mode: "prefer"
#line 1278 "dhcp6_parser.yy"
                 {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("prefer", ctx.loc2pos(yystack_[0].location)));
            }
#line 2322 "dhcp6_parser.cc"
    break;

  case 310: // ssl_mode: "require"
#line 1281 "dhcp6_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("require", ctx.loc2pos(yystack_[0].location)));
            }
#line 2330 "dhcp6_parser.cc"
    break;

  case 311: // ssl_mode: "verify-ca"
#line 1284 "dhcp6_parser.yy"
                    {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-ca", ctx.loc2pos(yystack_[0].location)));
            }
#line 2338 "dhcp6_parser.cc"
    break;

  case 312: // ssl_mode: "verify-full"
#line 1287 "dhcp6_parser.yy"
                      {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-full", ctx.loc2pos(yystack_[0].location)));
            }
#line 2346 "dhcp6_parser.cc"
    break;

  case 313: // $@50: %empty
#line 1292 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2355 "dhcp6_parser.cc"
    break;

  case 314: // cipher_list: "cipher-list" $@50 ":" "constant string"
#line 1295 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2365 "dhcp6_parser.cc"
    break;

  case 315: // $@51: %empty
#line 1301 "dhcp6_parser.yy"
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
#line 1307 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2386 "dhcp6_parser.cc"
    break;

  case 319: // sanity_checks_params: sanity_checks_params ","
#line 1314 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2394 "dhcp6_parser.cc"
    break;

  case 322: // $@52: %empty
#line 1323 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2403 "dhcp6_parser.cc"
    break;

  case 323: // lease_checks: "lease-checks" $@52 ":" "constant string"
#line 1326 "dhcp6_parser.yy"
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
#line 1342 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2432 "dhcp6_parser.cc"
    break;

  case 325: // extended_info_checks: "extended-info-checks" $@53 ":" "constant string"
#line 1345 "dhcp6_parser.yy"
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
#line 1360 "dhcp6_parser.yy"
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
#line 1366 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2472 "dhcp6_parser.cc"
    break;

  case 330: // mac_sources_list: mac_sources_list ","
#line 1373 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2480 "dhcp6_parser.cc"
    break;

  case 333: // duid_id: "duid"
#line 1382 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2489 "dhcp6_parser.cc"
    break;

  case 334: // string_id: "constant string"
#line 1387 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2498 "dhcp6_parser.cc"
    break;

  case 335: // $@55: %empty
#line 1392 "dhcp6_parser.yy"
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
#line 1398 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2519 "dhcp6_parser.cc"
    break;

  case 339: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1405 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2527 "dhcp6_parser.cc"
    break;

  case 343: // hw_address_id: "hw-address"
#line 1415 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2536 "dhcp6_parser.cc"
    break;

  case 344: // flex_id: "flex-id"
#line 1420 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2545 "dhcp6_parser.cc"
    break;

  case 345: // $@56: %empty
#line 1427 "dhcp6_parser.yy"
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
#line 1433 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2566 "dhcp6_parser.cc"
    break;

  case 347: // $@57: %empty
#line 1440 "dhcp6_parser.yy"
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
#line 1446 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2589 "dhcp6_parser.cc"
    break;

  case 351: // multi_threading_params: multi_threading_params ","
#line 1455 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2597 "dhcp6_parser.cc"
    break;

  case 358: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1468 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2607 "dhcp6_parser.cc"
    break;

  case 359: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1474 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2617 "dhcp6_parser.cc"
    break;

  case 360: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1480 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2627 "dhcp6_parser.cc"
    break;

  case 361: // $@58: %empty
#line 1486 "dhcp6_parser.yy"
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
#line 1492 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2648 "dhcp6_parser.cc"
    break;

  case 367: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1503 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2656 "dhcp6_parser.cc"
    break;

  case 368: // $@59: %empty
#line 1508 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2666 "dhcp6_parser.cc"
    break;

  case 369: // hooks_library: "{" $@59 hooks_params "}"
#line 1512 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2676 "dhcp6_parser.cc"
    break;

  case 370: // $@60: %empty
#line 1518 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2686 "dhcp6_parser.cc"
    break;

  case 371: // sub_hooks_library: "{" $@60 hooks_params "}"
#line 1522 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2696 "dhcp6_parser.cc"
    break;

  case 374: // hooks_params: hooks_params ","
#line 1530 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2704 "dhcp6_parser.cc"
    break;

  case 378: // $@61: %empty
#line 1540 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2713 "dhcp6_parser.cc"
    break;

  case 379: // library: "library" $@61 ":" "constant string"
#line 1543 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2723 "dhcp6_parser.cc"
    break;

  case 380: // $@62: %empty
#line 1549 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2732 "dhcp6_parser.cc"
    break;

  case 381: // parameters: "parameters" $@62 ":" map_value
#line 1552 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2741 "dhcp6_parser.cc"
    break;

  case 382: // $@63: %empty
#line 1558 "dhcp6_parser.yy"
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
#line 1564 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2763 "dhcp6_parser.cc"
    break;

  case 386: // expired_leases_params: expired_leases_params ","
#line 1572 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2771 "dhcp6_parser.cc"
    break;

  case 393: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1585 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2781 "dhcp6_parser.cc"
    break;

  case 394: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1591 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2791 "dhcp6_parser.cc"
    break;

  case 395: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1597 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2801 "dhcp6_parser.cc"
    break;

  case 396: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1603 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2811 "dhcp6_parser.cc"
    break;

  case 397: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1609 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2821 "dhcp6_parser.cc"
    break;

  case 398: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1615 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2831 "dhcp6_parser.cc"
    break;

  case 399: // $@64: %empty
#line 1624 "dhcp6_parser.yy"
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
#line 1630 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2852 "dhcp6_parser.cc"
    break;

  case 405: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1644 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2860 "dhcp6_parser.cc"
    break;

  case 406: // $@65: %empty
#line 1653 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2870 "dhcp6_parser.cc"
    break;

  case 407: // subnet6: "{" $@65 subnet6_params "}"
#line 1657 "dhcp6_parser.yy"
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
#line 1679 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2906 "dhcp6_parser.cc"
    break;

  case 409: // sub_subnet6: "{" $@66 subnet6_params "}"
#line 1683 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2916 "dhcp6_parser.cc"
    break;

  case 412: // subnet6_params: subnet6_params ","
#line 1692 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2924 "dhcp6_parser.cc"
    break;

  case 466: // $@67: %empty
#line 1753 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2933 "dhcp6_parser.cc"
    break;

  case 467: // subnet: "subnet" $@67 ":" "constant string"
#line 1756 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2943 "dhcp6_parser.cc"
    break;

  case 468: // $@68: %empty
#line 1762 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2952 "dhcp6_parser.cc"
    break;

  case 469: // interface: "interface" $@68 ":" "constant string"
#line 1765 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2962 "dhcp6_parser.cc"
    break;

  case 470: // $@69: %empty
#line 1771 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2971 "dhcp6_parser.cc"
    break;

  case 471: // interface_id: "interface-id" $@69 ":" "constant string"
#line 1774 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2981 "dhcp6_parser.cc"
    break;

  case 472: // $@70: %empty
#line 1780 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2990 "dhcp6_parser.cc"
    break;

  case 473: // client_class: "client-class" $@70 ":" "constant string"
#line 1783 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 3000 "dhcp6_parser.cc"
    break;

  case 474: // $@71: %empty
#line 1790 "dhcp6_parser.yy"
                                       {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3012 "dhcp6_parser.cc"
    break;

  case 475: // network_client_classes: "client-classes" $@71 ":" list_strings
#line 1796 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3021 "dhcp6_parser.cc"
    break;

  case 476: // $@72: %empty
#line 1802 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3033 "dhcp6_parser.cc"
    break;

  case 477: // require_client_classes: "require-client-classes" $@72 ":" list_strings
#line 1808 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3042 "dhcp6_parser.cc"
    break;

  case 478: // $@73: %empty
#line 1813 "dhcp6_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3054 "dhcp6_parser.cc"
    break;

  case 479: // evaluate_additional_classes: "evaluate-additional-classes" $@73 ":" list_strings
#line 1819 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3063 "dhcp6_parser.cc"
    break;

  case 480: // reservations_global: "reservations-global" ":" "boolean"
#line 1824 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 3073 "dhcp6_parser.cc"
    break;

  case 481: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1830 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 3083 "dhcp6_parser.cc"
    break;

  case 482: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1836 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 3093 "dhcp6_parser.cc"
    break;

  case 483: // id: "id" ":" "integer"
#line 1842 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 3103 "dhcp6_parser.cc"
    break;

  case 484: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1848 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 3113 "dhcp6_parser.cc"
    break;

  case 485: // $@74: %empty
#line 1856 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3125 "dhcp6_parser.cc"
    break;

  case 486: // shared_networks: "shared-networks" $@74 ":" "[" shared_networks_content "]"
#line 1862 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3134 "dhcp6_parser.cc"
    break;

  case 491: // shared_networks_list: shared_networks_list ","
#line 1875 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3142 "dhcp6_parser.cc"
    break;

  case 492: // $@75: %empty
#line 1880 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3152 "dhcp6_parser.cc"
    break;

  case 493: // shared_network: "{" $@75 shared_network_params "}"
#line 1884 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3160 "dhcp6_parser.cc"
    break;

  case 496: // shared_network_params: shared_network_params ","
#line 1890 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3168 "dhcp6_parser.cc"
    break;

  case 547: // $@76: %empty
#line 1951 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3180 "dhcp6_parser.cc"
    break;

  case 548: // option_def_list: "option-def" $@76 ":" "[" option_def_list_content "]"
#line 1957 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3189 "dhcp6_parser.cc"
    break;

  case 549: // $@77: %empty
#line 1965 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3198 "dhcp6_parser.cc"
    break;

  case 550: // sub_option_def_list: "{" $@77 option_def_list "}"
#line 1968 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 3206 "dhcp6_parser.cc"
    break;

  case 555: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1980 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3214 "dhcp6_parser.cc"
    break;

  case 556: // $@78: %empty
#line 1987 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3224 "dhcp6_parser.cc"
    break;

  case 557: // option_def_entry: "{" $@78 option_def_params "}"
#line 1991 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3236 "dhcp6_parser.cc"
    break;

  case 558: // $@79: %empty
#line 2002 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3246 "dhcp6_parser.cc"
    break;

  case 559: // sub_option_def: "{" $@79 option_def_params "}"
#line 2006 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3258 "dhcp6_parser.cc"
    break;

  case 564: // not_empty_option_def_params: not_empty_option_def_params ","
#line 2022 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3266 "dhcp6_parser.cc"
    break;

  case 576: // code: "code" ":" "integer"
#line 2041 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3276 "dhcp6_parser.cc"
    break;

  case 578: // $@80: %empty
#line 2049 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3285 "dhcp6_parser.cc"
    break;

  case 579: // option_def_type: "type" $@80 ":" "constant string"
#line 2052 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3295 "dhcp6_parser.cc"
    break;

  case 580: // $@81: %empty
#line 2058 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3304 "dhcp6_parser.cc"
    break;

  case 581: // option_def_record_types: "record-types" $@81 ":" "constant string"
#line 2061 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3314 "dhcp6_parser.cc"
    break;

  case 582: // $@82: %empty
#line 2067 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3323 "dhcp6_parser.cc"
    break;

  case 583: // space: "space" $@82 ":" "constant string"
#line 2070 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3333 "dhcp6_parser.cc"
    break;

  case 585: // $@83: %empty
#line 2078 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3342 "dhcp6_parser.cc"
    break;

  case 586: // option_def_encapsulate: "encapsulate" $@83 ":" "constant string"
#line 2081 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3352 "dhcp6_parser.cc"
    break;

  case 587: // option_def_array: "array" ":" "boolean"
#line 2087 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3362 "dhcp6_parser.cc"
    break;

  case 588: // $@84: %empty
#line 2097 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3374 "dhcp6_parser.cc"
    break;

  case 589: // option_data_list: "option-data" $@84 ":" "[" option_data_list_content "]"
#line 2103 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3383 "dhcp6_parser.cc"
    break;

  case 594: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2118 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3391 "dhcp6_parser.cc"
    break;

  case 595: // $@85: %empty
#line 2125 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3401 "dhcp6_parser.cc"
    break;

  case 596: // option_data_entry: "{" $@85 option_data_params "}"
#line 2129 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3410 "dhcp6_parser.cc"
    break;

  case 597: // $@86: %empty
#line 2137 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3420 "dhcp6_parser.cc"
    break;

  case 598: // sub_option_data: "{" $@86 option_data_params "}"
#line 2141 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3429 "dhcp6_parser.cc"
    break;

  case 603: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2157 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3437 "dhcp6_parser.cc"
    break;

  case 616: // $@87: %empty
#line 2179 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3446 "dhcp6_parser.cc"
    break;

  case 617: // option_data_data: "data" $@87 ":" "constant string"
#line 2182 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3456 "dhcp6_parser.cc"
    break;

  case 620: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2192 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3466 "dhcp6_parser.cc"
    break;

  case 621: // option_data_always_send: "always-send" ":" "boolean"
#line 2198 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3476 "dhcp6_parser.cc"
    break;

  case 622: // option_data_never_send: "never-send" ":" "boolean"
#line 2204 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3486 "dhcp6_parser.cc"
    break;

  case 623: // $@88: %empty
#line 2210 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3498 "dhcp6_parser.cc"
    break;

  case 624: // option_data_client_classes: "client-classes" $@88 ":" list_strings
#line 2216 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3507 "dhcp6_parser.cc"
    break;

  case 625: // $@89: %empty
#line 2224 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3519 "dhcp6_parser.cc"
    break;

  case 626: // pools_list: "pools" $@89 ":" "[" pools_list_content "]"
#line 2230 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3528 "dhcp6_parser.cc"
    break;

  case 631: // not_empty_pools_list: not_empty_pools_list ","
#line 2243 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3536 "dhcp6_parser.cc"
    break;

  case 632: // $@90: %empty
#line 2248 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3546 "dhcp6_parser.cc"
    break;

  case 633: // pool_list_entry: "{" $@90 pool_params "}"
#line 2252 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3556 "dhcp6_parser.cc"
    break;

  case 634: // $@91: %empty
#line 2258 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3566 "dhcp6_parser.cc"
    break;

  case 635: // sub_pool6: "{" $@91 pool_params "}"
#line 2262 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3576 "dhcp6_parser.cc"
    break;

  case 638: // pool_params: pool_params ","
#line 2270 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3584 "dhcp6_parser.cc"
    break;

  case 664: // $@92: %empty
#line 2302 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3593 "dhcp6_parser.cc"
    break;

  case 665: // pool_entry: "pool" $@92 ":" "constant string"
#line 2305 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3603 "dhcp6_parser.cc"
    break;

  case 666: // pool_id: "pool-id" ":" "integer"
#line 2311 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3613 "dhcp6_parser.cc"
    break;

  case 667: // $@93: %empty
#line 2317 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3621 "dhcp6_parser.cc"
    break;

  case 668: // user_context: "user-context" $@93 ":" map_value
#line 2319 "dhcp6_parser.yy"
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
#line 3648 "dhcp6_parser.cc"
    break;

  case 669: // $@94: %empty
#line 2342 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3656 "dhcp6_parser.cc"
    break;

  case 670: // comment: "comment" $@94 ":" "constant string"
#line 2344 "dhcp6_parser.yy"
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
#line 3685 "dhcp6_parser.cc"
    break;

  case 671: // $@95: %empty
#line 2372 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3697 "dhcp6_parser.cc"
    break;

  case 672: // pd_pools_list: "pd-pools" $@95 ":" "[" pd_pools_list_content "]"
#line 2378 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3706 "dhcp6_parser.cc"
    break;

  case 677: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2391 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3714 "dhcp6_parser.cc"
    break;

  case 678: // $@96: %empty
#line 2396 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3724 "dhcp6_parser.cc"
    break;

  case 679: // pd_pool_entry: "{" $@96 pd_pool_params "}"
#line 2400 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3736 "dhcp6_parser.cc"
    break;

  case 680: // $@97: %empty
#line 2408 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3746 "dhcp6_parser.cc"
    break;

  case 681: // sub_pd_pool: "{" $@97 pd_pool_params "}"
#line 2412 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3758 "dhcp6_parser.cc"
    break;

  case 684: // pd_pool_params: pd_pool_params ","
#line 2422 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3766 "dhcp6_parser.cc"
    break;

  case 699: // $@98: %empty
#line 2443 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3775 "dhcp6_parser.cc"
    break;

  case 700: // pd_prefix: "prefix" $@98 ":" "constant string"
#line 2446 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3785 "dhcp6_parser.cc"
    break;

  case 701: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2452 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3795 "dhcp6_parser.cc"
    break;

  case 702: // $@99: %empty
#line 2458 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3804 "dhcp6_parser.cc"
    break;

  case 703: // excluded_prefix: "excluded-prefix" $@99 ":" "constant string"
#line 2461 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3814 "dhcp6_parser.cc"
    break;

  case 704: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2467 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3824 "dhcp6_parser.cc"
    break;

  case 705: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2473 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3834 "dhcp6_parser.cc"
    break;

  case 706: // $@100: %empty
#line 2482 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3846 "dhcp6_parser.cc"
    break;

  case 707: // reservations: "reservations" $@100 ":" "[" reservations_list "]"
#line 2488 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3855 "dhcp6_parser.cc"
    break;

  case 712: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2499 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3863 "dhcp6_parser.cc"
    break;

  case 713: // $@101: %empty
#line 2504 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3873 "dhcp6_parser.cc"
    break;

  case 714: // reservation: "{" $@101 reservation_params "}"
#line 2508 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3882 "dhcp6_parser.cc"
    break;

  case 715: // $@102: %empty
#line 2513 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3892 "dhcp6_parser.cc"
    break;

  case 716: // sub_reservation: "{" $@102 reservation_params "}"
#line 2517 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3901 "dhcp6_parser.cc"
    break;

  case 721: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2528 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3909 "dhcp6_parser.cc"
    break;

  case 734: // $@103: %empty
#line 2548 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3921 "dhcp6_parser.cc"
    break;

  case 735: // ip_addresses: "ip-addresses" $@103 ":" list_strings
#line 2554 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3930 "dhcp6_parser.cc"
    break;

  case 736: // $@104: %empty
#line 2559 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3942 "dhcp6_parser.cc"
    break;

  case 737: // prefixes: "prefixes" $@104 ":" list_strings
#line 2565 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3951 "dhcp6_parser.cc"
    break;

  case 738: // $@105: %empty
#line 2570 "dhcp6_parser.yy"
                                     {
    ctx.unique("excluded-prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3963 "dhcp6_parser.cc"
    break;

  case 739: // excluded_prefixes: "excluded-prefixes" $@105 ":" list_strings
#line 2576 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3972 "dhcp6_parser.cc"
    break;

  case 740: // $@106: %empty
#line 2581 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3981 "dhcp6_parser.cc"
    break;

  case 741: // duid: "duid" $@106 ":" "constant string"
#line 2584 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3991 "dhcp6_parser.cc"
    break;

  case 742: // $@107: %empty
#line 2590 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4000 "dhcp6_parser.cc"
    break;

  case 743: // hw_address: "hw-address" $@107 ":" "constant string"
#line 2593 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 4010 "dhcp6_parser.cc"
    break;

  case 744: // $@108: %empty
#line 2599 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4019 "dhcp6_parser.cc"
    break;

  case 745: // hostname: "hostname" $@108 ":" "constant string"
#line 2602 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 4029 "dhcp6_parser.cc"
    break;

  case 746: // $@109: %empty
#line 2608 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4038 "dhcp6_parser.cc"
    break;

  case 747: // flex_id_value: "flex-id" $@109 ":" "constant string"
#line 2611 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 4048 "dhcp6_parser.cc"
    break;

  case 748: // $@110: %empty
#line 2617 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4060 "dhcp6_parser.cc"
    break;

  case 749: // reservation_client_classes: "client-classes" $@110 ":" list_strings
#line 2623 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4069 "dhcp6_parser.cc"
    break;

  case 750: // $@111: %empty
#line 2631 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 4081 "dhcp6_parser.cc"
    break;

  case 751: // relay: "relay" $@111 ":" "{" relay_map "}"
#line 2637 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4090 "dhcp6_parser.cc"
    break;

  case 753: // $@112: %empty
#line 2648 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 4102 "dhcp6_parser.cc"
    break;

  case 754: // client_classes: "client-classes" $@112 ":" "[" client_classes_list "]"
#line 2654 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4111 "dhcp6_parser.cc"
    break;

  case 759: // not_empty_classes_list: not_empty_classes_list ","
#line 2665 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4119 "dhcp6_parser.cc"
    break;

  case 760: // $@113: %empty
#line 2670 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4129 "dhcp6_parser.cc"
    break;

  case 761: // client_class_entry: "{" $@113 client_class_params "}"
#line 2674 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 4139 "dhcp6_parser.cc"
    break;

  case 766: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2686 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 4147 "dhcp6_parser.cc"
    break;

  case 783: // $@114: %empty
#line 2710 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4156 "dhcp6_parser.cc"
    break;

  case 784: // client_class_test: "test" $@114 ":" "constant string"
#line 2713 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4166 "dhcp6_parser.cc"
    break;

  case 785: // $@115: %empty
#line 2719 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4175 "dhcp6_parser.cc"
    break;

  case 786: // client_class_template_test: "template-test" $@115 ":" "constant string"
#line 2722 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4185 "dhcp6_parser.cc"
    break;

  case 787: // only_if_required: "only-if-required" ":" "boolean"
#line 2729 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4195 "dhcp6_parser.cc"
    break;

  case 788: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2735 "dhcp6_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4205 "dhcp6_parser.cc"
    break;

  case 789: // $@116: %empty
#line 2744 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 4217 "dhcp6_parser.cc"
    break;

  case 790: // server_id: "server-id" $@116 ":" "{" server_id_params "}"
#line 2750 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4228 "dhcp6_parser.cc"
    break;

  case 793: // server_id_params: server_id_params ","
#line 2759 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4236 "dhcp6_parser.cc"
    break;

  case 803: // $@117: %empty
#line 2775 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 4245 "dhcp6_parser.cc"
    break;

  case 804: // server_id_type: "type" $@117 ":" duid_type
#line 2778 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4254 "dhcp6_parser.cc"
    break;

  case 805: // duid_type: "LLT"
#line 2783 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4260 "dhcp6_parser.cc"
    break;

  case 806: // duid_type: "EN"
#line 2784 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4266 "dhcp6_parser.cc"
    break;

  case 807: // duid_type: "LL"
#line 2785 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4272 "dhcp6_parser.cc"
    break;

  case 808: // htype: "htype" ":" "integer"
#line 2788 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4282 "dhcp6_parser.cc"
    break;

  case 809: // $@118: %empty
#line 2794 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4291 "dhcp6_parser.cc"
    break;

  case 810: // identifier: "identifier" $@118 ":" "constant string"
#line 2797 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4301 "dhcp6_parser.cc"
    break;

  case 811: // time: "time" ":" "integer"
#line 2803 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4311 "dhcp6_parser.cc"
    break;

  case 812: // enterprise_id: "enterprise-id" ":" "integer"
#line 2809 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4321 "dhcp6_parser.cc"
    break;

  case 813: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2817 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4331 "dhcp6_parser.cc"
    break;

  case 814: // $@119: %empty
#line 2825 "dhcp6_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKETS);
}
#line 4343 "dhcp6_parser.cc"
    break;

  case 815: // control_sockets: "control-sockets" $@119 ":" "[" control_socket_list "]"
#line 2831 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4352 "dhcp6_parser.cc"
    break;

  case 820: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2842 "dhcp6_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4360 "dhcp6_parser.cc"
    break;

  case 821: // $@120: %empty
#line 2847 "dhcp6_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4370 "dhcp6_parser.cc"
    break;

  case 822: // control_socket_entry: "{" $@120 control_socket_params "}"
#line 2851 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4378 "dhcp6_parser.cc"
    break;

  case 825: // control_socket_params: control_socket_params ","
#line 2857 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4386 "dhcp6_parser.cc"
    break;

  case 839: // $@121: %empty
#line 2877 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4395 "dhcp6_parser.cc"
    break;

  case 840: // control_socket_type: "socket-type" $@121 ":" control_socket_type_value
#line 2880 "dhcp6_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4404 "dhcp6_parser.cc"
    break;

  case 841: // control_socket_type_value: "unix"
#line 2886 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4410 "dhcp6_parser.cc"
    break;

  case 842: // control_socket_type_value: "http"
#line 2887 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4416 "dhcp6_parser.cc"
    break;

  case 843: // control_socket_type_value: "https"
#line 2888 "dhcp6_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4422 "dhcp6_parser.cc"
    break;

  case 844: // $@122: %empty
#line 2891 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4431 "dhcp6_parser.cc"
    break;

  case 845: // control_socket_name: "socket-name" $@122 ":" "constant string"
#line 2894 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4441 "dhcp6_parser.cc"
    break;

  case 846: // $@123: %empty
#line 2900 "dhcp6_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4450 "dhcp6_parser.cc"
    break;

  case 847: // control_socket_address: "socket-address" $@123 ":" "constant string"
#line 2903 "dhcp6_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4460 "dhcp6_parser.cc"
    break;

  case 848: // control_socket_port: "socket-port" ":" "integer"
#line 2909 "dhcp6_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4470 "dhcp6_parser.cc"
    break;

  case 849: // cert_required: "cert-required" ":" "boolean"
#line 2915 "dhcp6_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4480 "dhcp6_parser.cc"
    break;

  case 850: // $@124: %empty
#line 2921 "dhcp6_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4492 "dhcp6_parser.cc"
    break;

  case 851: // http_headers: "http-headers" $@124 ":" "[" http_header_list "]"
#line 2927 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4501 "dhcp6_parser.cc"
    break;

  case 856: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2938 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4509 "dhcp6_parser.cc"
    break;

  case 857: // $@125: %empty
#line 2943 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4519 "dhcp6_parser.cc"
    break;

  case 858: // http_header: "{" $@125 http_header_params "}"
#line 2947 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4527 "dhcp6_parser.cc"
    break;

  case 861: // http_header_params: http_header_params ","
#line 2953 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4535 "dhcp6_parser.cc"
    break;

  case 867: // $@126: %empty
#line 2965 "dhcp6_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4544 "dhcp6_parser.cc"
    break;

  case 868: // header_value: "value" $@126 ":" "constant string"
#line 2968 "dhcp6_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4554 "dhcp6_parser.cc"
    break;

  case 869: // $@127: %empty
#line 2976 "dhcp6_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4566 "dhcp6_parser.cc"
    break;

  case 870: // authentication: "authentication" $@127 ":" "{" auth_params "}"
#line 2982 "dhcp6_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4577 "dhcp6_parser.cc"
    break;

  case 873: // auth_params: auth_params ","
#line 2991 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4585 "dhcp6_parser.cc"
    break;

  case 881: // $@128: %empty
#line 3005 "dhcp6_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4594 "dhcp6_parser.cc"
    break;

  case 882: // auth_type: "type" $@128 ":" auth_type_value
#line 3008 "dhcp6_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4603 "dhcp6_parser.cc"
    break;

  case 883: // auth_type_value: "basic"
#line 3013 "dhcp6_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4609 "dhcp6_parser.cc"
    break;

  case 884: // $@129: %empty
#line 3016 "dhcp6_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4618 "dhcp6_parser.cc"
    break;

  case 885: // realm: "realm" $@129 ":" "constant string"
#line 3019 "dhcp6_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4628 "dhcp6_parser.cc"
    break;

  case 886: // $@130: %empty
#line 3025 "dhcp6_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4637 "dhcp6_parser.cc"
    break;

  case 887: // directory: "directory" $@130 ":" "constant string"
#line 3028 "dhcp6_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4647 "dhcp6_parser.cc"
    break;

  case 888: // $@131: %empty
#line 3034 "dhcp6_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4659 "dhcp6_parser.cc"
    break;

  case 889: // clients: "clients" $@131 ":" "[" clients_list "]"
#line 3040 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4668 "dhcp6_parser.cc"
    break;

  case 894: // not_empty_clients_list: not_empty_clients_list ","
#line 3051 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4676 "dhcp6_parser.cc"
    break;

  case 895: // $@132: %empty
#line 3056 "dhcp6_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4686 "dhcp6_parser.cc"
    break;

  case 896: // basic_auth: "{" $@132 clients_params "}"
#line 3060 "dhcp6_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4694 "dhcp6_parser.cc"
    break;

  case 899: // clients_params: clients_params ","
#line 3066 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4702 "dhcp6_parser.cc"
    break;

  case 907: // $@133: %empty
#line 3080 "dhcp6_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4711 "dhcp6_parser.cc"
    break;

  case 908: // user_file: "user-file" $@133 ":" "constant string"
#line 3083 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4721 "dhcp6_parser.cc"
    break;

  case 909: // $@134: %empty
#line 3091 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4733 "dhcp6_parser.cc"
    break;

  case 910: // dhcp_queue_control: "dhcp-queue-control" $@134 ":" "{" queue_control_params "}"
#line 3097 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4744 "dhcp6_parser.cc"
    break;

  case 913: // queue_control_params: queue_control_params ","
#line 3106 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4752 "dhcp6_parser.cc"
    break;

  case 920: // enable_queue: "enable-queue" ":" "boolean"
#line 3119 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4762 "dhcp6_parser.cc"
    break;

  case 921: // $@135: %empty
#line 3125 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4771 "dhcp6_parser.cc"
    break;

  case 922: // queue_type: "queue-type" $@135 ":" "constant string"
#line 3128 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4781 "dhcp6_parser.cc"
    break;

  case 923: // capacity: "capacity" ":" "integer"
#line 3134 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4791 "dhcp6_parser.cc"
    break;

  case 924: // $@136: %empty
#line 3140 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4800 "dhcp6_parser.cc"
    break;

  case 925: // arbitrary_map_entry: "constant string" $@136 ":" value
#line 3143 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4809 "dhcp6_parser.cc"
    break;

  case 926: // $@137: %empty
#line 3150 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4821 "dhcp6_parser.cc"
    break;

  case 927: // dhcp_ddns: "dhcp-ddns" $@137 ":" "{" dhcp_ddns_params "}"
#line 3156 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4832 "dhcp6_parser.cc"
    break;

  case 928: // $@138: %empty
#line 3163 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4842 "dhcp6_parser.cc"
    break;

  case 929: // sub_dhcp_ddns: "{" $@138 dhcp_ddns_params "}"
#line 3167 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4852 "dhcp6_parser.cc"
    break;

  case 932: // dhcp_ddns_params: dhcp_ddns_params ","
#line 3175 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4860 "dhcp6_parser.cc"
    break;

  case 944: // enable_updates: "enable-updates" ":" "boolean"
#line 3193 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4870 "dhcp6_parser.cc"
    break;

  case 945: // $@139: %empty
#line 3199 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4879 "dhcp6_parser.cc"
    break;

  case 946: // server_ip: "server-ip" $@139 ":" "constant string"
#line 3202 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4889 "dhcp6_parser.cc"
    break;

  case 947: // server_port: "server-port" ":" "integer"
#line 3208 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4899 "dhcp6_parser.cc"
    break;

  case 948: // $@140: %empty
#line 3214 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4908 "dhcp6_parser.cc"
    break;

  case 949: // sender_ip: "sender-ip" $@140 ":" "constant string"
#line 3217 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4918 "dhcp6_parser.cc"
    break;

  case 950: // sender_port: "sender-port" ":" "integer"
#line 3223 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4928 "dhcp6_parser.cc"
    break;

  case 951: // max_queue_size: "max-queue-size" ":" "integer"
#line 3229 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4938 "dhcp6_parser.cc"
    break;

  case 952: // $@141: %empty
#line 3235 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4947 "dhcp6_parser.cc"
    break;

  case 953: // ncr_protocol: "ncr-protocol" $@141 ":" ncr_protocol_value
#line 3238 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4956 "dhcp6_parser.cc"
    break;

  case 954: // ncr_protocol_value: "UDP"
#line 3244 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4962 "dhcp6_parser.cc"
    break;

  case 955: // ncr_protocol_value: "TCP"
#line 3245 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4968 "dhcp6_parser.cc"
    break;

  case 956: // $@142: %empty
#line 3248 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4977 "dhcp6_parser.cc"
    break;

  case 957: // ncr_format: "ncr-format" $@142 ":" "JSON"
#line 3251 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4987 "dhcp6_parser.cc"
    break;

  case 958: // $@143: %empty
#line 3259 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4999 "dhcp6_parser.cc"
    break;

  case 959: // config_control: "config-control" $@143 ":" "{" config_control_params "}"
#line 3265 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5009 "dhcp6_parser.cc"
    break;

  case 960: // $@144: %empty
#line 3271 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 5019 "dhcp6_parser.cc"
    break;

  case 961: // sub_config_control: "{" $@144 config_control_params "}"
#line 3275 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 5028 "dhcp6_parser.cc"
    break;

  case 964: // config_control_params: config_control_params ","
#line 3283 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 5036 "dhcp6_parser.cc"
    break;

  case 967: // $@145: %empty
#line 3293 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 5048 "dhcp6_parser.cc"
    break;

  case 968: // config_databases: "config-databases" $@145 ":" "[" database_list "]"
#line 3299 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5057 "dhcp6_parser.cc"
    break;

  case 969: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3304 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 5067 "dhcp6_parser.cc"
    break;

  case 970: // $@146: %empty
#line 3312 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 5079 "dhcp6_parser.cc"
    break;

  case 971: // loggers: "loggers" $@146 ":" "[" loggers_entries "]"
#line 3318 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5088 "dhcp6_parser.cc"
    break;

  case 974: // loggers_entries: loggers_entries ","
#line 3327 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 5096 "dhcp6_parser.cc"
    break;

  case 975: // $@147: %empty
#line 3333 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 5106 "dhcp6_parser.cc"
    break;

  case 976: // logger_entry: "{" $@147 logger_params "}"
#line 3337 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 5114 "dhcp6_parser.cc"
    break;

  case 979: // logger_params: logger_params ","
#line 3343 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 5122 "dhcp6_parser.cc"
    break;

  case 987: // debuglevel: "debuglevel" ":" "integer"
#line 3357 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 5132 "dhcp6_parser.cc"
    break;

  case 988: // $@148: %empty
#line 3363 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5141 "dhcp6_parser.cc"
    break;

  case 989: // severity: "severity" $@148 ":" "constant string"
#line 3366 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 5151 "dhcp6_parser.cc"
    break;

  case 990: // $@149: %empty
#line 3372 "dhcp6_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 5163 "dhcp6_parser.cc"
    break;

  case 991: // output_options_list: "output-options" $@149 ":" "[" output_options_list_content "]"
#line 3378 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5172 "dhcp6_parser.cc"
    break;

  case 994: // output_options_list_content: output_options_list_content ","
#line 3385 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 5180 "dhcp6_parser.cc"
    break;

  case 995: // $@150: %empty
#line 3390 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 5190 "dhcp6_parser.cc"
    break;

  case 996: // output_entry: "{" $@150 output_params_list "}"
#line 3394 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 5198 "dhcp6_parser.cc"
    break;

  case 999: // output_params_list: output_params_list ","
#line 3400 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 5206 "dhcp6_parser.cc"
    break;

  case 1005: // $@151: %empty
#line 3412 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5215 "dhcp6_parser.cc"
    break;

  case 1006: // output: "output" $@151 ":" "constant string"
#line 3415 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5225 "dhcp6_parser.cc"
    break;

  case 1007: // flush: "flush" ":" "boolean"
#line 3421 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5235 "dhcp6_parser.cc"
    break;

  case 1008: // maxsize: "maxsize" ":" "integer"
#line 3427 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5245 "dhcp6_parser.cc"
    break;

  case 1009: // maxver: "maxver" ":" "integer"
#line 3433 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5255 "dhcp6_parser.cc"
    break;

  case 1010: // $@152: %empty
#line 3439 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5264 "dhcp6_parser.cc"
    break;

  case 1011: // pattern: "pattern" $@152 ":" "constant string"
#line 3442 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5274 "dhcp6_parser.cc"
    break;

  case 1012: // $@153: %empty
#line 3448 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5286 "dhcp6_parser.cc"
    break;

  case 1013: // compatibility: "compatibility" $@153 ":" "{" compatibility_params "}"
#line 3454 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5295 "dhcp6_parser.cc"
    break;

  case 1016: // compatibility_params: compatibility_params ","
#line 3461 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5303 "dhcp6_parser.cc"
    break;

  case 1019: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3470 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5313 "dhcp6_parser.cc"
    break;


#line 5317 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1485;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     709, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485,    60,    35,   114,   154,   194,
     234,   246,   268,   274,   281,   288,   375,   383,   384,   399,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,    35,  -175,
      68,   285,    90,   781,  1195,   308,   339,    30,   153,   650,
    -101,   263,   242, -1485,   125,   152,   129,   136,   184, -1485,
      67, -1485, -1485, -1485, -1485, -1485, -1485, -1485,   191,   305,
     400,   403,   426,   439,   446,   466,   469,   470,   471,   473,
     474,   475,   485, -1485,   490,   499,   500,   502,   503, -1485,
   -1485, -1485, -1485,   504,   506,   508,   510,   511,   512,   513,
   -1485, -1485, -1485,   519, -1485, -1485, -1485, -1485, -1485, -1485,
     520,   522,   524, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485,   526, -1485, -1485, -1485, -1485, -1485, -1485,   529,
     530,   531,   533, -1485, -1485,   534, -1485,    71, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485,   536,   540,   542,   543, -1485,    82, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485,   545,   547, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485,    96, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485,   548, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485,   131, -1485, -1485,
   -1485, -1485, -1485, -1485,   549, -1485,   551,   553, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485,   146, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485,   550,   557, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485,   555, -1485, -1485,
     562, -1485, -1485, -1485,   563, -1485, -1485,   565,   567, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485,   571,   572,   573, -1485, -1485, -1485, -1485, -1485,
     575,   576, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485,   148, -1485, -1485, -1485,
     582, -1485,   586, -1485,   587,   589, -1485, -1485, -1485, -1485,
   -1485,   161, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485,   591,   165, -1485, -1485, -1485, -1485,    35,    35,
   -1485,   338,   592, -1485, -1485,   593,   594,   596,   597,   599,
     600,   362,   365,   366,   369,   371,   372,   374,   376,   378,
     382,   389,   390,   388,   393,   398,   612,   401,   402,   405,
     406,   410,   624,   625,   626,   634,   412,   415,   404,   418,
     419,   422,   433,   639,   643,   663,   436,   667,   676,   677,
     680,   682,   683,   445,   447,   450,   687,   690,   693,   694,
     697,   698,   700,   701,   704,   467,   705,   707,   712,   713,
     714,   716,   468,   477,   478,   479,   721,   723, -1485,   285,
   -1485,   724,   484,   486,   487,   489,    90, -1485,   729,   730,
     731,   732,   733,   505,   509,   745,   746,   749,   752,   753,
     781, -1485,   754,   517,  1195, -1485,   757,   521,   758,   525,
     537,   308, -1485,   759,   761,   769,   772,   775,   777,   779,
     784, -1485,   339, -1485,   785,   786,   552,   787,   788,   789,
     554, -1485,   153,   792,   556,   558,   561,   793, -1485,   650,
     794,   796,   -49, -1485,   568,   798,   564,   808,   574,   577,
     810,   811,   263, -1485,   812,   578,   242, -1485, -1485, -1485,
     818,   816,   583,   817,   820,   821,   822,   827, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485,   584, -1485, -1485, -1485, -1485, -1485,    53,
     607,   608,   609, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
     847,   862,   863, -1485,   628,   629,   387,   874,   873,   642,
   -1485, -1485, -1485,   880,   881,   882,   883,   888,   889,   890,
     902,   903, -1485,   904,   891,   905,   909,   646,   675, -1485,
   -1485, -1485, -1485,   913,   912, -1485,   916, -1485, -1485, -1485,
   -1485, -1485,   918,   919,   684,   685,   686, -1485, -1485,   916,
     916,   916,   689,   922, -1485,   691, -1485, -1485,   692, -1485,
     710, -1485, -1485, -1485,   916,   916,   916,   916,   711,   717,
     718,   719, -1485,   720,   722, -1485,   725,   726,   727, -1485,
   -1485,   728, -1485, -1485, -1485,   916, -1485,   734,   873, -1485,
   -1485,   735, -1485,   736, -1485, -1485,   -67,   760, -1485,   920,
   -1485, -1485,    35,   285, -1485,   242,    90,   187,   187,   925,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
     944,   951,   956, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
     958, -1485, -1485, -1485,  -102,    35,   270,   137,   964,   965,
     966,   128,   155,   -52,   967,   -70,   263, -1485, -1485,   968,
    -171, -1485, -1485,   972,   973, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485,   839, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,   925,
   -1485,   177,   180,   200, -1485, -1485, -1485, -1485,   978,   979,
     980,   981,   982,   983,   984,   985,   986,   987, -1485,   990,
     991, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485,   240, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,   244,
   -1485,   992,   993, -1485, -1485,   994,   996, -1485, -1485,   995,
     999, -1485, -1485,   997,  1001, -1485, -1485,  1000,  1002, -1485,
   -1485, -1485,   110, -1485, -1485, -1485,  1003, -1485, -1485, -1485,
     124, -1485, -1485, -1485, -1485, -1485,   251, -1485, -1485, -1485,
   -1485,  1004,  1005, -1485, -1485,  1006,  1008, -1485, -1485,  1007,
    1011, -1485,  1012,  1013,  1014,  1015,  1016,  1018,   302, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,  1021,  1022,
    1024, -1485, -1485, -1485, -1485,   322, -1485, -1485, -1485, -1485,
   -1485, -1485,  1025,  1028,  1032, -1485,   323, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485,  1009,  1036, -1485,  1037, -1485,  1045,
   -1485, -1485, -1485,   326, -1485, -1485, -1485, -1485, -1485,   330,
   -1485,   168, -1485,  1052, -1485,   373, -1485, -1485,   755, -1485,
    1053,  1059, -1485, -1485,  1061,  1076, -1485, -1485,  1074,  1078,
   -1485, -1485, -1485,  1087,  1092,  1093,  1094,   764,   860,   864,
     865,   868,   869,   872,   875,   877,   879,  1104,   884,   893,
    1113,  1121,  1122,  1127,  1128,  1130,   187, -1485, -1485,   187,
   -1485,   925,   781, -1485,   944,   153, -1485,   951,   650, -1485,
     956,  1462, -1485,   958,  -102, -1485, -1485,   270, -1485,  1133,
    1136,   137, -1485,   819, -1485,   964,   339, -1485,   965,  -101,
   -1485,   966,   898,   908,   924,   931,   934,   936,   128, -1485,
    1141,  1148,   939,   948,   949,   155, -1485,   923,   953,   989,
     -52, -1485,   630, -1485,   967,   962,  1161,   998,  1218,   -70,
   -1485, -1485,   157,   968, -1485,  1010,  -171, -1485, -1485,  1219,
    1223,  1195, -1485,   972,   308, -1485,   973, -1485, -1485,  1017,
    1019,  1020,  1023, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485,   262, -1485, -1485,  1033,  1038,  1039,   265,
    1040,  1042, -1485,   385, -1485,   386, -1485,  1221, -1485,  1226,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485,   395, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485,  1043,  1044, -1485, -1485,
   -1485,  1233,  1234, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485,  1231,  1239, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485,  1235, -1485,   397, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485,    65,  1046, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485,  1240, -1485,  1242,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485,   425, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,  1047, -1485,
      35, -1485, -1485,  1244, -1485, -1485, -1485, -1485, -1485,   428,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,  1048,   429,
   -1485,   431, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485,  1462, -1485, -1485, -1485,  1245,  1247,  1050,  1056, -1485,
     819, -1485, -1485, -1485, -1485, -1485, -1485, -1485,  1248,  1249,
    1250,  1049,  1252,  1057,  1253,   630, -1485, -1485, -1485,  1254,
    1055,  1256,   157, -1485, -1485, -1485, -1485, -1485,  1051,  1063,
   -1485, -1485, -1485,   160,  1064,  1065, -1485,  1257, -1485,  1258,
   -1485,  1261, -1485,  1066, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485,    81,  1280,  1296, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485,   441, -1485, -1485, -1485, -1485, -1485,
   -1485,  1308,  1312, -1485, -1485,   188, -1485,  1313,  1314,  1317,
    1322,    81, -1485,   -40, -1485,  1280,  -131,  1296, -1485,  1155,
    1096,  1098,  1336, -1485, -1485, -1485, -1485, -1485, -1485,   443,
   -1485, -1485, -1485, -1485,  1339,  1340,  1344, -1485,   449, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
    1342,  1346,   -40, -1485,  1347,  1107,  1114,  1115,  1356,  -131,
   -1485, -1485,  1355,  1360, -1485,  1124, -1485,  1125, -1485, -1485,
   -1485,  1126, -1485,   141, -1485,  1342, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485,   464, -1485, -1485, -1485,
    1366,   141, -1485,  1129, -1485, -1485
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   211,     9,   408,    11,
     634,    13,   680,    15,   715,    17,   549,    19,   558,    21,
     597,    23,   370,    25,   928,    27,   960,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   717,     0,   560,   599,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   146,   958,   209,   230,   232,   234,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   198,     0,     0,     0,     0,     0,   166,
     173,   175,   177,     0,     0,     0,     0,     0,     0,     0,
     399,   547,   588,     0,   201,   203,   181,   485,   667,   669,
       0,     0,     0,   326,   345,   335,   315,   753,   706,   361,
     382,   789,     0,   347,   814,   909,   926,   191,   193,     0,
       0,     0,     0,   970,  1012,     0,   145,     0,    69,    72,
      73,    74,    75,    76,    77,    78,    79,    80,   110,   111,
     112,   113,   114,   115,    81,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   117,
     118,   133,   134,   135,   106,   142,   143,   144,   137,   138,
     139,   140,    84,    85,    86,    87,   103,    88,    90,    89,
     136,    94,    95,    82,   107,   108,   109,    83,    92,    93,
     101,   102,   104,    91,    96,    97,    98,    99,   100,   105,
     116,   141,   224,     0,     0,     0,     0,   223,     0,   213,
     216,   217,   218,   219,   220,   221,   222,   625,   671,   466,
     468,   470,     0,     0,   474,   476,   478,   472,   750,   465,
     413,   414,   415,   416,   417,   418,   419,   420,   440,   441,
     442,   443,   444,   445,   448,   449,   450,   451,   452,   453,
     454,   455,   456,   457,   458,   459,   460,   461,   446,   447,
     462,   463,   464,     0,   410,   424,   425,   426,   429,   430,
     431,   432,   434,   435,   436,   427,   428,   421,   422,   438,
     439,   423,   433,   437,   664,     0,   663,   646,   647,   648,
     649,   650,   651,   652,   653,   654,   655,   656,   657,   658,
     659,   660,   642,   643,   644,   645,   641,     0,   636,   639,
     640,   661,   662,   699,     0,   702,     0,     0,   698,   690,
     691,   692,   693,   689,   688,   696,   697,     0,   682,   685,
     686,   694,   695,   687,   748,   734,   736,   738,   740,   742,
     744,   746,   733,   730,   731,   732,     0,   718,   719,   724,
     725,   726,   722,   727,   728,   729,   723,     0,   578,   282,
       0,   582,   580,   585,     0,   574,   575,     0,   561,   562,
     565,   577,   566,   567,   568,   584,   569,   570,   571,   572,
     573,   616,     0,     0,     0,   623,   614,   615,   618,   619,
       0,   600,   601,   604,   605,   606,   607,   608,   609,   610,
     613,   611,   612,   378,   380,   375,     0,   372,   376,   377,
       0,   945,     0,   948,     0,     0,   952,   956,   943,   941,
     942,     0,   930,   933,   934,   935,   936,   937,   938,   939,
     940,   967,     0,     0,   962,   965,   966,    47,    52,     0,
      39,    45,     0,    66,    62,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    60,    71,
      68,     0,     0,     0,     0,     0,   215,   212,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     412,   409,     0,     0,   638,   635,     0,     0,     0,     0,
       0,   684,   681,     0,     0,     0,     0,     0,     0,     0,
       0,   716,   721,   550,     0,     0,     0,     0,     0,     0,
       0,   559,   564,     0,     0,     0,     0,     0,   598,   603,
       0,     0,   374,   371,     0,     0,     0,     0,     0,     0,
       0,     0,   932,   929,     0,     0,   964,   961,    51,    43,
       0,     0,     0,     0,     0,     0,     0,     0,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,     0,   196,   197,   163,   164,   165,     0,
       0,     0,     0,   179,   180,   187,   188,   189,   190,   195,
       0,     0,     0,   200,     0,     0,     0,     0,     0,     0,
     480,   481,   482,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   813,     0,     0,     0,     0,     0,     0,   205,
     206,   207,   208,     0,     0,    70,     0,   226,   227,   228,
     229,   214,     0,     0,     0,     0,     0,   483,   484,     0,
       0,     0,     0,     0,   411,     0,   666,   637,     0,   701,
       0,   704,   705,   683,     0,     0,     0,     0,     0,     0,
       0,     0,   720,     0,     0,   576,     0,     0,     0,   587,
     563,     0,   620,   621,   622,     0,   602,     0,     0,   373,
     944,     0,   947,     0,   950,   951,     0,     0,   931,     0,
     969,   963,     0,     0,   147,     0,     0,     0,     0,   236,
     199,   168,   169,   170,   171,   172,   167,   174,   176,   178,
     401,   551,   590,   202,   204,   183,   184,   185,   186,   182,
     487,    40,   668,   670,     0,    48,     0,     0,   755,   708,
     363,     0,     0,     0,   816,     0,     0,   192,   194,     0,
       0,    53,   225,   627,   673,   467,   469,   471,   475,   477,
     479,   473,     0,   665,   700,   703,   749,   735,   737,   739,
     741,   743,   745,   747,   579,   283,   583,   581,   586,   617,
     624,   379,   381,   946,   949,   954,   955,   953,   957,   236,
      44,     0,     0,     0,   271,   273,   275,   279,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   292,     0,
       0,   300,   302,   304,   306,   308,   309,   310,   311,   312,
     313,   277,   270,     0,   243,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   261,
     262,   263,   264,   260,   265,   266,   267,   268,   269,     0,
     241,     0,   237,   238,   406,     0,   402,   403,   556,     0,
     552,   553,   595,     0,   591,   592,   492,     0,   488,   489,
     333,   334,     0,   328,   331,   332,     0,   343,   344,   340,
       0,   337,   341,   342,   322,   324,     0,   317,   320,   321,
     760,     0,   756,   757,   713,     0,   709,   710,   368,     0,
     364,   365,     0,     0,     0,     0,     0,     0,     0,   384,
     387,   388,   389,   390,   391,   392,   803,   809,     0,     0,
       0,   802,   799,   800,   801,     0,   791,   794,   797,   795,
     796,   798,     0,     0,     0,   357,     0,   349,   352,   353,
     354,   355,   356,   821,     0,   817,   818,     0,   921,     0,
     924,   917,   918,     0,   911,   914,   915,   916,   919,     0,
     975,     0,   972,     0,  1018,     0,  1014,  1017,    55,   632,
       0,   628,   629,   678,     0,   674,   675,   752,     0,     0,
      64,   959,   210,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   245,   231,   233,     0,
     235,   240,     0,   400,   405,   560,   548,   555,   599,   589,
     594,     0,   486,   491,   330,   327,   346,   339,   336,     0,
       0,   319,   316,   762,   754,   759,   717,   707,   712,     0,
     362,   367,     0,     0,     0,     0,     0,     0,   386,   383,
       0,     0,     0,     0,     0,   793,   790,     0,     0,     0,
     351,   348,     0,   815,   820,     0,     0,     0,     0,   913,
     910,   927,     0,   974,   971,     0,  1016,  1013,    57,     0,
      56,     0,   626,   631,     0,   672,   677,   751,   968,     0,
       0,     0,     0,   281,   284,   285,   286,   287,   288,   289,
     290,   299,   291,     0,   297,   298,     0,     0,     0,     0,
       0,     0,   244,     0,   239,     0,   404,     0,   554,     0,
     593,   546,   512,   513,   514,   516,   517,   518,   501,   502,
     521,   522,   523,   524,   525,   526,   529,   530,   531,   532,
     533,   534,   535,   536,   537,   538,   539,   540,   541,   542,
     527,   528,   543,   544,   545,   497,   498,   499,   500,   508,
     509,   510,   511,   505,   506,   507,   515,     0,   494,   503,
     519,   520,   504,   490,   329,   338,     0,     0,   318,   783,
     785,     0,     0,   781,   775,   776,   777,   778,   779,   780,
     782,   772,   773,   774,     0,   763,   764,   767,   768,   769,
     770,   771,   758,     0,   711,     0,   366,   393,   394,   395,
     396,   397,   398,   385,     0,     0,   808,   811,   812,   792,
     358,   359,   360,   350,   839,   844,   846,     0,   869,     0,
     850,   838,   831,   832,   833,   836,   837,     0,   823,   826,
     827,   828,   829,   834,   835,   830,   819,   920,     0,   923,
       0,   912,   990,     0,   988,   986,   980,   984,   985,     0,
     977,   982,   983,   981,   973,  1019,  1015,    54,    59,     0,
     630,     0,   676,   272,   274,   276,   280,   294,   295,   296,
     293,   301,   303,   305,   307,   314,   278,   242,   407,   557,
     596,   496,   493,   323,   325,     0,     0,     0,     0,   761,
     766,   714,   369,   805,   806,   807,   804,   810,     0,     0,
       0,     0,     0,     0,     0,   825,   822,   922,   925,     0,
       0,     0,   979,   976,    58,   633,   679,   495,     0,     0,
     787,   788,   765,     0,     0,     0,   848,     0,   849,     0,
     824,     0,   987,     0,   978,   784,   786,   841,   842,   843,
     840,   845,   847,     0,   852,     0,   989,   881,   884,   886,
     888,   880,   879,   878,     0,   871,   874,   875,   876,   877,
     857,     0,   853,   854,   995,     0,   992,     0,     0,     0,
       0,   873,   870,     0,   851,   856,     0,   994,   991,     0,
       0,     0,     0,   872,   867,   866,   862,   864,   865,     0,
     859,   863,   855,  1005,     0,     0,     0,  1010,     0,   997,
    1000,  1001,  1002,  1003,  1004,   993,   883,   882,   885,   887,
     890,     0,   861,   858,     0,     0,     0,     0,     0,   999,
     996,   895,     0,   891,   892,     0,   860,     0,  1007,  1008,
    1009,     0,   998,     0,   889,   894,   868,  1006,  1011,   907,
     906,   900,   902,   903,   904,   905,     0,   897,   901,   893,
       0,   899,   896,     0,   898,   908
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485,   -10, -1485,  -636, -1485,
     604, -1485, -1485, -1485, -1485,   559, -1485,    40, -1485, -1485,
   -1485,   -71, -1485, -1485, -1485, -1485, -1485, -1485, -1485,   581,
     814, -1485, -1485,   -61,   -58,   -55,   -41,   -38,   -35,   -18,
      92,    97,   102,   103,   105,   108,   109, -1485,   -15,   -12,
      27,    38, -1485, -1485,    41, -1485,    52, -1485,    55, -1485,
      62,   113,    69, -1485, -1485,    72,    74,    79,    84,    86,
   -1485,    89, -1485,   116, -1485, -1485, -1485, -1485, -1485,   119,
   -1485,   120, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485,   590,   809, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485,   514, -1485,   287, -1485,  -771,
     294, -1485, -1485, -1484, -1485, -1478, -1485, -1475, -1485, -1485,
   -1485, -1485,   -25, -1485,  -811, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1106, -1485,
   -1105, -1485, -1101, -1485,   192, -1485, -1485, -1485, -1485, -1485,
   -1485,   271, -1485, -1485, -1485, -1485, -1485, -1485, -1485,   280,
    -796, -1485, -1485, -1485, -1485,   279, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485,   247, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485,   273, -1485, -1485, -1485,   272,   767, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485,   267, -1485, -1485, -1485, -1485, -1485,
   -1485, -1080, -1485, -1485, -1485,   303, -1485, -1485, -1485,   304,
     824, -1485, -1485, -1079, -1485, -1078, -1485,    -6, -1485,    -2,
   -1485,   130, -1485,   135, -1485,   123,   126,   127, -1485, -1072,
   -1485, -1485, -1485, -1485,   296, -1485, -1485,    29,  1324, -1485,
   -1485, -1485, -1485, -1485,   311, -1485, -1485, -1485,   310, -1485,
     799, -1485,   -63, -1485, -1485, -1485, -1485, -1485,   -60, -1485,
   -1485, -1485, -1485, -1485,    22, -1485, -1485, -1485,   314, -1485,
   -1485, -1485,   318, -1485,   800, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,   254,
   -1485, -1485, -1485,   257,   836, -1485, -1485,   -62,   -48, -1485,
       8, -1485, -1485, -1485, -1485, -1485,   255, -1485, -1485, -1485,
     258,   833, -1485, -1485, -1485, -1485, -1485, -1485, -1485,   -59,
   -1485, -1485, -1485,   307, -1485, -1485, -1485,   312, -1485,   825,
     588, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1067, -1485, -1485, -1485,
   -1485, -1485, -1485,   317, -1485, -1485, -1485,    49, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,   299, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485,   291, -1485, -1485,    44, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,   -29,
   -1485, -1485,   -56, -1485, -1485, -1485, -1485, -1485,   -19, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
     -81, -1485, -1485,   -94, -1485, -1485, -1485, -1485, -1485,   300,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
     622,   826, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,   666,
     823, -1485, -1485, -1485, -1485, -1485, -1485,   309, -1485, -1485,
      51, -1485, -1485, -1485, -1485, -1485, -1485,   -11, -1485, -1485,
     -45, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485, -1485,
   -1485,   316, -1485
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     812,    87,    88,    41,    68,    84,    85,   832,  1048,  1159,
    1160,   902,    43,    70,    90,   482,    91,    45,    71,   167,
     168,   169,   485,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   512,   796,   189,   513,   190,   514,   191,   515,
     192,   193,   194,   529,   809,   195,   196,   197,   198,   199,
     550,   200,   551,   201,   202,   203,   204,   506,   205,   206,
     527,   207,   528,   208,   209,   210,   211,   212,   487,    47,
      72,   248,   249,   250,   561,   251,   252,   253,   254,   213,
     488,   214,   489,   215,   490,   931,   932,   933,  1089,   903,
     904,   905,  1063,   906,  1064,   907,  1065,   908,  1085,   909,
    1066,   910,   911,   605,   912,   913,   914,   915,   916,   917,
     918,   919,   920,  1077,  1360,   921,   922,   923,   924,  1080,
     925,  1081,   926,  1082,   927,  1083,   928,  1084,   216,   539,
     966,   967,   968,  1109,   969,  1110,   217,   536,   952,   953,
     954,   955,   218,   538,   960,   961,   962,   963,   219,   537,
     220,   546,  1016,  1017,  1018,  1019,  1020,   221,   542,   979,
     980,   981,  1119,    63,    80,   446,   447,   448,   620,   449,
     621,   222,   543,   988,   989,   990,   991,   992,   993,   994,
     995,   223,   523,   935,   936,   937,  1092,    49,    73,   303,
     304,   305,   570,   306,   571,   307,   572,   308,   578,   309,
     575,   310,   576,   311,   577,   224,   225,   226,   315,   316,
     227,   530,   947,   948,   949,  1101,  1247,  1248,   228,   524,
      57,    77,   939,   940,   941,  1095,    59,    78,   407,   408,
     409,   410,   411,   412,   413,   604,   414,   608,   415,   607,
     416,   417,   609,   418,   229,   525,   943,   944,   945,  1098,
      61,    79,   430,   431,   432,   433,   434,   613,   435,   436,
     437,   438,   439,   440,   617,   318,   568,  1050,  1051,  1052,
    1161,    51,    74,   347,   348,   349,   582,   350,   230,   531,
     231,   532,   321,   569,  1054,  1055,  1056,  1164,    53,    75,
     367,   368,   369,   586,   370,   371,   588,   372,   373,   232,
     541,   975,   976,   977,  1116,    55,    76,   386,   387,   388,
     389,   594,   390,   595,   391,   596,   392,   597,   393,   598,
     394,   599,   395,   600,   396,   593,   323,   579,  1058,   233,
     540,   971,   972,   973,  1113,  1274,  1275,  1276,  1277,  1278,
    1375,  1279,  1376,  1280,  1281,   234,   544,  1005,  1006,  1007,
    1130,  1386,  1008,  1009,  1131,  1010,  1011,   235,   236,   547,
    1024,  1025,  1026,  1142,  1317,  1318,  1319,  1388,  1430,  1320,
    1389,  1321,  1390,  1322,  1323,  1324,  1394,  1451,  1452,  1453,
    1463,  1479,  1480,  1481,  1501,  1325,  1392,  1444,  1445,  1446,
    1457,  1497,  1447,  1458,  1448,  1459,  1449,  1460,  1512,  1513,
    1514,  1523,  1536,  1537,  1538,  1540,   237,   548,  1033,  1034,
    1035,  1036,  1146,  1037,  1038,  1148,   238,   549,    65,    81,
     461,   462,   463,   464,   625,   465,   466,   627,   467,   468,
     469,   630,   867,   470,   631,   239,   486,    67,    82,   473,
     474,   475,   634,   476,   240,   556,  1041,  1042,  1152,  1339,
    1340,  1341,  1342,  1401,  1343,  1399,  1455,  1456,  1466,  1488,
    1489,  1490,  1504,  1491,  1492,  1493,  1494,  1508,   241,   557,
    1045,  1046,  1047
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     166,   247,   269,   326,   358,   382,    38,   405,   426,   445,
     458,  1002,   270,   364,   322,   271,   428,   929,   272,   429,
     959,  1236,  1237,  1238,   255,   319,   351,   365,   384,  1246,
     419,   441,   273,   459,  1252,   274,  1312,  1313,   275,  1531,
      31,  1314,    32,   950,    33,  1532,   138,   139,  1533,   399,
     443,   444,   811,   406,   427,   276,  1043,  1531,   284,   327,
      30,   285,   328,  1532,   138,   139,  1533,    86,   342,   359,
     483,   165,   343,   360,   559,   484,   138,   139,    89,   560,
     256,   320,   352,   366,   385,   566,   420,   442,  1483,   460,
     567,  1484,  1485,  1486,  1487,   317,   346,   363,   383,   580,
     286,   329,   443,   444,   581,  1437,   242,   243,   244,   245,
     246,   287,   330,  1104,   288,   331,  1105,   131,  1012,  1013,
    1014,    42,  1027,  1028,  1029,   289,   332,  1107,   290,   333,
    1108,   477,   811,   479,   584,   291,   334,   865,   866,   585,
     951,   165,   293,   335,   480,   294,   336,   295,   337,   591,
    1474,   622,   296,   338,   592,   478,   623,   297,   339,   298,
     340,    44,   299,   341,   632,   277,   875,   876,   636,   633,
     278,  1153,  1030,   637,  1154,   279,   280,   398,   281,   996,
     559,   282,   283,   636,   879,  1060,   292,   481,  1061,   300,
     165,  1467,   301,   302,  1468,   491,   312,   138,   139,   313,
     314,    46,   165,   566,   344,   361,   138,   139,  1062,   345,
     362,   874,   875,   876,   877,   878,   879,   880,   881,   882,
     883,   884,   885,   886,   887,   888,  1383,  1384,  1385,   889,
     890,   891,   892,   893,   894,   895,   896,   897,   898,   899,
     900,    48,   399,  1086,   400,   401,   399,  1086,  1087,   402,
     403,   404,  1088,    50,  1111,   471,   472,   138,   139,  1112,
     791,   792,   793,   794,  1438,  1439,  1440,   964,   965,   138,
     139,   138,   139,   138,   139,    52,   399,    34,    35,    36,
      37,    54,   982,   983,   984,   985,   986,   987,    56,  1312,
    1313,  1236,  1237,  1238,  1314,    58,    92,    93,   795,  1246,
      94,  1357,  1358,  1359,  1252,  1128,    95,    96,    97,   492,
    1129,   959,   894,   895,   896,   897,   898,   899,  1193,   997,
     998,   999,  1000,   165,  1002,  1135,  1140,  1529,   901,  1149,
    1136,  1141,   165,   632,  1150,  1427,  1428,  1429,  1151,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   901,  1332,  1156,  1333,  1334,   138,
     139,  1157,    60,   165,   133,   134,   135,   136,  1086,   580,
      62,    64,   137,  1367,  1368,   165,   132,   165,  1371,   165,
     622,   138,   139,  1372,   493,  1382,    66,   494,   140,   141,
     142,   143,   144,   145,   146,   950,   957,   147,   958,   353,
     354,   355,   356,   357,   138,   139,   148,   132,  1395,   165,
     495,  1402,   584,  1396,   591,   149,  1403,  1405,   150,  1406,
     264,   265,   266,   496,  1461,   151,  1502,   267,   325,  1462,
     497,  1503,  1509,   152,   153,   138,   139,  1510,   154,   450,
     451,   452,   453,   454,   455,   456,   457,  1541,   638,   639,
     498,   374,  1542,   499,   500,   501,   155,   502,   503,   504,
     156,   375,   376,   377,   378,   379,   380,   381,   166,   505,
     805,   806,   807,   808,   507,   247,   157,   158,   159,   160,
     161,   162,   163,   508,   509,   165,   510,   511,   516,   269,
     517,   164,   518,   326,   519,   520,   521,   522,   255,   270,
     358,   322,   271,   526,   533,   272,   534,   165,   535,   364,
     545,   382,   319,   552,   553,   554,   351,   555,   558,   273,
     562,   405,   274,   365,   563,   275,   564,   565,   426,   573,
     165,   574,   583,   587,   384,   589,   428,   590,   601,   429,
     602,   458,   276,   603,   419,   284,   606,   610,   285,   327,
     612,   441,   328,   611,   256,   614,   615,   616,   342,   619,
     640,   165,   343,   618,   459,   359,   624,   406,   320,   360,
     626,   628,   352,   629,   427,   635,   641,   642,   643,   366,
     644,   645,   317,   646,   647,   648,   346,   286,   649,   650,
     385,   329,   651,   363,   652,   653,   663,   654,   287,   655,
     420,   288,   330,   656,   383,   331,   657,   442,   669,   670,
     671,   660,   289,   658,   659,   290,   332,   661,   672,   333,
     460,   662,   291,   680,   664,   665,   334,   681,   675,   293,
     666,   667,   294,   335,   295,   668,   336,   673,   337,   296,
     674,   676,   677,   338,   297,   678,   298,   682,   339,   299,
     340,   684,   277,   341,   891,   892,   893,   278,   679,   683,
     685,   686,   279,   280,   687,   281,   688,   689,   282,   283,
     690,   693,   691,   292,   694,   692,   300,   695,   696,   301,
     302,   697,   698,   312,   699,   700,   313,   314,   701,   703,
     702,   704,   166,   709,   344,   247,   705,   706,   707,   345,
     708,   361,   710,   711,   712,   713,   362,   714,   716,   717,
     719,   718,   720,   722,   723,   724,   725,   726,   255,   399,
     421,   400,   401,   422,   423,   424,   138,   139,   727,   729,
     730,  1001,  1015,   731,   728,   458,   732,   733,   735,  1044,
     736,   738,   740,   744,   739,   745,   138,   139,   741,   838,
     839,   840,   870,   746,  1003,  1021,   747,  1031,   459,   748,
     742,   749,   425,   750,   846,   847,   848,   849,   751,   753,
     754,   756,   757,   758,   256,   755,   761,   765,   767,   759,
     768,   762,   771,   763,  1304,   860,   764,   772,  1305,  1306,
    1307,  1308,   773,   770,   776,   777,   779,   774,  1309,  1310,
     775,   780,   782,   783,   785,   784,   790,   786,   787,   788,
    1004,  1022,   789,  1032,   460,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   797,
     798,   799,   800,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   801,   802,   132,
     803,   804,   165,    98,    99,   100,   101,   102,   103,   810,
      32,   134,   135,   136,   813,   814,   815,   816,   827,   257,
     817,   258,   165,   818,   819,   820,   824,   138,   139,   259,
     260,   261,   262,   263,   140,   141,   142,   132,   399,   821,
     822,   823,   825,   264,   265,   266,   826,   828,   829,   830,
     267,   831,   148,   833,   834,   869,   835,   836,   837,   842,
     268,   841,   930,   843,   844,   138,   139,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,   934,   845,   850,  1259,  1260,  1261,  1262,   938,   851,
     852,   853,   854,   942,   855,   946,   868,   856,   857,   858,
     859,   970,   974,   978,  1023,  1040,   861,   863,   864,  1049,
    1053,   375,  1067,  1068,  1069,  1070,  1071,  1072,  1073,  1074,
    1075,  1076,   157,   158,  1078,  1079,  1091,  1158,  1090,  1094,
    1093,  1096,  1097,  1099,  1100,  1103,  1102,  1173,  1115,  1106,
    1114,  1118,  1117,  1120,  1121,  1143,  1122,  1123,  1124,  1125,
    1126,   269,  1127,   165,   405,  1132,  1133,   426,  1134,  1137,
    1201,   270,  1138,   322,   271,   428,  1139,   272,   429,  1144,
    1202,  1145,  1263,  1203,   319,   382,  1204,   419,   445,  1147,
     441,   273,  1264,  1250,   274,  1265,  1155,   275,  1266,  1162,
    1205,   165,  1163,  1206,  1001,  1272,  1207,  1165,   384,  1015,
     406,  1311,  1267,   427,   276,  1268,  1235,   284,  1269,  1166,
     285,  1335,  1167,  1208,  1168,  1044,  1216,  1003,  1270,  1217,
     326,  1169,  1021,   358,  1315,  1239,  1170,  1171,  1172,  1240,
     320,  1031,   364,   420,  1337,  1174,   442,  1175,  1183,  1251,
    1176,  1177,  1178,   351,   317,  1179,   365,  1186,  1180,   286,
    1181,  1273,  1182,  1249,   385,  1187,  1188,  1336,  1218,  1184,
     287,  1189,  1190,   288,  1191,  1271,  1185,  1256,   383,  1219,
    1257,  1287,  1220,  1004,   289,  1294,   327,   290,  1022,   328,
    1316,  1288,  1295,  1221,   291,   342,  1222,  1032,   359,   343,
    1338,   293,   360,  1223,   294,  1328,   295,  1289,  1300,   352,
    1225,   296,   366,  1226,  1290,  1227,   297,  1291,   298,  1292,
    1228,   299,  1296,   346,   277,  1229,   363,  1230,   329,   278,
    1231,  1297,  1298,  1209,   279,   280,  1301,   281,  1210,   330,
     282,   283,   331,  1211,  1212,   292,  1213,  1327,   300,  1214,
    1215,   301,   302,   332,  1224,   312,   333,  1232,   313,   314,
    1233,  1234,  1330,   334,  1243,  1347,  1348,  1244,  1245,  1369,
     335,  1241,  1302,   336,  1370,   337,  1242,  1377,  1378,  1379,
     338,  1329,  1380,  1381,  1391,   339,  1393,   340,  1400,  1408,
     341,  1409,  1413,  1414,  1415,  1345,  1417,  1419,  1421,  1353,
    1423,  1354,  1355,  1434,  1433,  1356,  1435,   116,   117,   118,
     119,   120,   121,   122,   123,  1361,   125,   126,   127,   128,
    1362,  1363,  1365,   132,  1366,  1373,  1374,  1450,  1387,  1397,
    1404,   344,  1416,  1425,   361,  1410,   345,   136,  1422,   362,
    1201,  1411,  1418,  1454,   324,  1426,  1431,  1432,  1436,  1263,
    1202,   138,   139,  1203,  1464,  1465,  1204,  1469,  1470,  1264,
    1398,  1471,  1265,  1250,  1311,  1266,  1472,   264,   265,   266,
    1205,  1335,  1272,  1206,   267,   325,  1207,  1496,  1498,  1267,
    1499,  1500,  1268,  1505,  1506,  1269,  1235,  1315,  1507,  1511,
    1515,  1517,  1518,  1208,  1337,  1270,  1216,  1519,  1520,  1217,
    1521,  1524,  1441,  1525,   871,  1239,  1526,  1527,  1528,  1240,
    1543,  1545,   862,   715,   956,   721,   873,  1336,  1194,  1251,
    1192,  1364,  1258,  1059,  1254,  1442,  1255,  1303,  1273,   769,
    1441,  1285,  1475,  1249,  1286,  1293,  1195,  1196,  1218,  1253,
    1407,   397,  1271,  1316,   734,  1197,   157,   158,  1198,  1219,
    1338,   760,  1220,  1442,  1200,  1477,  1199,  1350,  1349,   766,
     737,  1352,  1351,  1221,   743,  1284,  1222,   752,  1283,  1412,
    1057,  1475,  1282,  1223,  1299,  1326,  1482,   165,  1476,  1420,
    1225,  1443,  1473,  1226,  1539,  1227,  1516,  1544,  1039,  1331,
    1228,   872,  1530,  1424,  1477,  1229,  1495,  1230,   778,   781,
    1231,     0,  1344,  1209,  1522,     0,     0,     0,  1210,  1443,
    1530,  1478,  1346,  1211,  1212,  1534,  1213,  1476,     0,  1214,
    1215,     0,     0,     0,  1224,     0,     0,  1232,     0,     0,
    1233,  1234,     0,  1534,  1243,     0,     0,  1244,  1245,     0,
       0,  1241,     0,     0,     0,     0,  1242,     0,     0,     0,
    1478,     0,     0,     0,     0,     0,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
       0,  1535,     0,     0,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,  1535,
     132,   399,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   134,   135,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   138,   139,
       0,   260,   261,     0,   263,   140,   141,   142,     0,     0,
       0,     0,     0,     0,   264,   265,   266,     0,     0,     0,
       0,   267,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   268,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   157,   158,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   165
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   822,    73,    75,    73,    73,    79,   788,    73,    79,
     816,  1101,  1101,  1101,    72,    73,    74,    75,    76,  1101,
      78,    79,    73,    81,  1101,    73,  1142,  1142,    73,  1523,
       5,  1142,     7,   145,     9,  1523,   116,   117,  1523,    89,
     151,   152,   688,    78,    79,    73,   227,  1541,    73,    74,
       0,    73,    74,  1541,   116,   117,  1541,   242,    74,    75,
       3,   242,    74,    75,     3,     8,   116,   117,    10,     8,
      72,    73,    74,    75,    76,     3,    78,    79,   219,    81,
       8,   222,   223,   224,   225,    73,    74,    75,    76,     3,
      73,    74,   151,   152,     8,    24,    16,    17,    18,    19,
      20,    73,    74,     3,    73,    74,     6,    87,   170,   171,
     172,     7,   192,   193,   194,    73,    74,     3,    73,    74,
       6,     6,   768,     4,     3,    73,    74,   204,   205,     8,
     242,   242,    73,    74,     8,    73,    74,    73,    74,     3,
     190,     3,    73,    74,     8,     3,     8,    73,    74,    73,
      74,     7,    73,    74,     3,    73,    25,    26,     3,     8,
      73,     3,   242,     8,     6,    73,    73,    24,    73,    24,
       3,    73,    73,     3,    29,     8,    73,     3,     8,    73,
     242,     3,    73,    73,     6,     4,    73,   116,   117,    73,
      73,     7,   242,     3,    74,    75,   116,   117,     8,    74,
      75,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,   161,   162,   163,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,     7,    89,     3,    91,    92,    89,     3,     8,    96,
      97,    98,     8,     7,     3,    13,    14,   116,   117,     8,
     207,   208,   209,   210,   183,   184,   185,   130,   131,   116,
     117,   116,   117,   116,   117,     7,    89,   242,   243,   244,
     245,     7,   154,   155,   156,   157,   158,   159,     7,  1395,
    1395,  1371,  1371,  1371,  1395,     7,    11,    12,   245,  1371,
      15,    39,    40,    41,  1371,     3,    21,    22,    23,     4,
       8,  1107,    47,    48,    49,    50,    51,    52,  1089,   164,
     165,   166,   167,   242,  1135,     3,     3,   186,   187,     3,
       8,     8,   242,     3,     8,   175,   176,   177,     8,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,   187,   218,     3,   220,   221,   116,
     117,     8,     7,   242,    99,   100,   101,   102,     3,     3,
       7,     7,   107,     8,     8,   242,    88,   242,     3,   242,
       3,   116,   117,     8,     4,     8,     7,     4,   123,   124,
     125,   126,   127,   128,   129,   145,   146,   132,   148,   111,
     112,   113,   114,   115,   116,   117,   141,    88,     3,   242,
       4,     3,     3,     8,     3,   150,     8,     8,   153,     8,
     132,   133,   134,     4,     3,   160,     3,   139,   140,     8,
       4,     8,     3,   168,   169,   116,   117,     8,   173,   196,
     197,   198,   199,   200,   201,   202,   203,     3,   478,   479,
       4,   132,     8,     4,     4,     4,   191,     4,     4,     4,
     195,   142,   143,   144,   145,   146,   147,   148,   559,     4,
     103,   104,   105,   106,     4,   566,   211,   212,   213,   214,
     215,   216,   217,     4,     4,   242,     4,     4,     4,   580,
       4,   226,     4,   584,     4,     4,     4,     4,   566,   580,
     591,   580,   580,     4,     4,   580,     4,   242,     4,   591,
       4,   602,   580,     4,     4,     4,   584,     4,     4,   580,
       4,   612,   580,   591,     4,   580,     4,     4,   619,     4,
     242,     4,     4,     4,   602,     4,   619,     4,     8,   619,
       3,   632,   580,     8,   612,   580,     4,     4,   580,   584,
       3,   619,   584,     8,   566,     4,     4,     4,   584,     3,
     242,   242,   584,     8,   632,   591,     4,   612,   580,   591,
       4,     4,   584,     4,   619,     4,     4,     4,     4,   591,
       4,     4,   580,     4,     4,   243,   584,   580,   243,   243,
     602,   584,   243,   591,   243,   243,     4,   243,   580,   243,
     612,   580,   584,   245,   602,   584,   244,   619,     4,     4,
       4,   243,   580,   244,   244,   580,   584,   244,     4,   584,
     632,   243,   580,     4,   243,   243,   584,     4,   244,   580,
     245,   245,   580,   584,   580,   245,   584,   245,   584,   580,
     245,   243,   243,   584,   580,   243,   580,     4,   584,   580,
     584,     4,   580,   584,    44,    45,    46,   580,   245,   243,
       4,     4,   580,   580,     4,   580,     4,     4,   580,   580,
     245,     4,   245,   580,     4,   245,   580,     4,     4,   580,
     580,     4,     4,   580,     4,     4,   580,   580,     4,     4,
     243,     4,   783,   245,   584,   786,     4,     4,     4,   584,
       4,   591,   245,   245,   245,     4,   591,     4,     4,   245,
     243,   245,   243,     4,     4,     4,     4,     4,   786,    89,
      90,    91,    92,    93,    94,    95,   116,   117,   243,     4,
       4,   822,   823,     4,   245,   826,     4,     4,     4,   830,
     243,     4,     4,     4,   243,     4,   116,   117,   243,   729,
     730,   731,   782,     4,   822,   823,     4,   825,   826,     4,
     243,     4,   132,     4,   744,   745,   746,   747,     4,     4,
       4,     4,     4,     4,   786,   243,     4,     4,     4,   245,
       4,   245,     4,   245,   174,   765,   245,   243,   178,   179,
     180,   181,     4,   245,     4,     4,     4,   243,   188,   189,
     243,   243,     4,     7,     7,   242,   242,     7,     7,     7,
     822,   823,     5,   825,   826,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,   242,
     242,   242,     5,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,     5,     5,    88,
     242,   242,   242,    54,    55,    56,    57,    58,    59,     5,
       7,   100,   101,   102,   242,     5,     5,     5,   242,   108,
       7,   110,   242,     5,     5,     5,     5,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,    88,    89,     7,
       7,     7,     7,   132,   133,   134,     7,   242,     5,     7,
     139,     5,   141,     5,     5,     5,   242,   242,   242,     7,
     149,   242,     7,   242,   242,   116,   117,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,     7,   242,   242,   135,   136,   137,   138,     7,   242,
     242,   242,   242,     7,   242,     7,   206,   242,   242,   242,
     242,     7,     7,     7,     7,     7,   242,   242,   242,     7,
       7,   142,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   211,   212,     4,     4,     3,   242,     6,     3,
       6,     6,     3,     6,     3,     3,     6,   243,     3,     6,
       6,     3,     6,     6,     3,     6,     4,     4,     4,     4,
       4,  1092,     4,   242,  1095,     4,     4,  1098,     4,     4,
    1101,  1092,     4,  1092,  1092,  1098,     4,  1092,  1098,     3,
    1101,     4,  1113,  1101,  1092,  1116,  1101,  1095,  1119,     4,
    1098,  1092,  1113,  1101,  1092,  1113,     4,  1092,  1113,     6,
    1101,   242,     3,  1101,  1135,  1113,  1101,     6,  1116,  1140,
    1095,  1142,  1113,  1098,  1092,  1113,  1101,  1092,  1113,     3,
    1092,  1152,     8,  1101,     6,  1156,  1101,  1135,  1113,  1101,
    1161,     4,  1140,  1164,  1142,  1101,     4,     4,     4,  1101,
    1092,  1149,  1164,  1095,  1152,   245,  1098,   243,     4,  1101,
     245,   243,   243,  1161,  1092,   243,  1164,     4,   243,  1092,
     243,  1113,   243,  1101,  1116,     4,     4,  1152,  1101,   245,
    1092,     4,     4,  1092,     4,  1113,   243,     4,  1116,  1101,
       4,   243,  1101,  1135,  1092,     4,  1161,  1092,  1140,  1161,
    1142,   243,     4,  1101,  1092,  1161,  1101,  1149,  1164,  1161,
    1152,  1092,  1164,  1101,  1092,     4,  1092,   243,   245,  1161,
    1101,  1092,  1164,  1101,   243,  1101,  1092,   243,  1092,   243,
    1101,  1092,   243,  1161,  1092,  1101,  1164,  1101,  1161,  1092,
    1101,   243,   243,  1101,  1092,  1092,   243,  1092,  1101,  1161,
    1092,  1092,  1161,  1101,  1101,  1092,  1101,   245,  1092,  1101,
    1101,  1092,  1092,  1161,  1101,  1092,  1161,  1101,  1092,  1092,
    1101,  1101,     4,  1161,  1101,     6,     3,  1101,  1101,     8,
    1161,  1101,   243,  1161,     8,  1161,  1101,     4,     4,     8,
    1161,   243,     3,     8,     4,  1161,     4,  1161,     4,     4,
    1161,     4,     4,     4,     4,   245,     4,     4,     4,   242,
       4,   242,   242,     5,     7,   242,     5,    72,    73,    74,
      75,    76,    77,    78,    79,   242,    81,    82,    83,    84,
     242,   242,   242,    88,   242,   242,   242,     7,   242,   242,
     242,  1161,   243,   242,  1164,   245,  1161,   102,   243,  1164,
    1371,   245,   245,     7,   109,   242,   242,   242,   242,  1380,
    1371,   116,   117,  1371,     6,     3,  1371,     4,     4,  1380,
    1330,     4,  1380,  1371,  1395,  1380,     4,   132,   133,   134,
    1371,  1402,  1380,  1371,   139,   140,  1371,   182,   242,  1380,
     242,     5,  1380,     4,     4,  1380,  1371,  1395,     4,     7,
       4,     4,   245,  1371,  1402,  1380,  1371,   243,   243,  1371,
       4,     6,  1433,     3,   783,  1371,   242,   242,   242,  1371,
       4,   242,   768,   559,   815,   566,   786,  1402,  1091,  1371,
    1086,  1189,  1111,   869,  1104,  1433,  1107,  1140,  1380,   622,
    1461,  1119,  1463,  1371,  1121,  1128,  1092,  1094,  1371,  1103,
    1371,    77,  1380,  1395,   580,  1095,   211,   212,  1097,  1371,
    1402,   612,  1371,  1461,  1100,  1463,  1098,  1163,  1161,   619,
     584,  1166,  1164,  1371,   591,  1118,  1371,   602,  1116,  1380,
     842,  1502,  1115,  1371,  1135,  1144,  1465,   242,  1463,  1395,
    1371,  1433,  1461,  1371,  1525,  1371,  1502,  1541,   826,  1149,
    1371,   785,  1523,  1402,  1502,  1371,  1467,  1371,   632,   636,
    1371,    -1,  1153,  1371,  1509,    -1,    -1,    -1,  1371,  1461,
    1541,  1463,  1156,  1371,  1371,  1523,  1371,  1502,    -1,  1371,
    1371,    -1,    -1,    -1,  1371,    -1,    -1,  1371,    -1,    -1,
    1371,  1371,    -1,  1541,  1371,    -1,    -1,  1371,  1371,    -1,
      -1,  1371,    -1,    -1,    -1,    -1,  1371,    -1,    -1,    -1,
    1502,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      -1,  1523,    -1,    -1,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,  1541,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   100,   101,   102,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   116,   117,
      -1,   119,   120,    -1,   122,   123,   124,   125,    -1,    -1,
      -1,    -1,    -1,    -1,   132,   133,   134,    -1,    -1,    -1,
      -1,   139,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   149,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   211,   212,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   242
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
       0,     5,     7,     9,   242,   243,   244,   245,   262,   263,
     264,   269,     7,   278,     7,   283,     7,   345,     7,   463,
       7,   547,     7,   564,     7,   581,     7,   496,     7,   502,
       7,   526,     7,   439,     7,   694,     7,   713,   270,   265,
     279,   284,   346,   464,   548,   565,   582,   497,   503,   527,
     440,   695,   714,   262,   271,   272,   242,   267,   268,    10,
     280,   282,    11,    12,    15,    21,    22,    23,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    99,   100,   101,   102,   107,   116,   117,
     123,   124,   125,   126,   127,   128,   129,   132,   141,   150,
     153,   160,   168,   169,   173,   191,   195,   211,   212,   213,
     214,   215,   216,   217,   226,   242,   277,   285,   286,   287,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   310,
     312,   314,   316,   317,   318,   321,   322,   323,   324,   325,
     327,   329,   330,   331,   332,   334,   335,   337,   339,   340,
     341,   342,   343,   355,   357,   359,   404,   412,   418,   424,
     426,   433,   447,   457,   481,   482,   483,   486,   494,   520,
     554,   556,   575,   605,   621,   633,   634,   682,   692,   711,
     720,   744,    16,    17,    18,    19,    20,   277,   347,   348,
     349,   351,   352,   353,   354,   554,   556,   108,   110,   118,
     119,   120,   121,   122,   132,   133,   134,   139,   149,   277,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   304,   305,   306,   307,   310,   312,
     314,   316,   317,   318,   321,   322,   323,   324,   325,   327,
     329,   335,   337,   465,   466,   467,   469,   471,   473,   475,
     477,   479,   481,   482,   483,   484,   485,   520,   541,   554,
     556,   558,   575,   602,   109,   140,   277,   304,   305,   306,
     307,   310,   312,   314,   316,   318,   321,   322,   323,   324,
     325,   327,   473,   475,   477,   479,   520,   549,   550,   551,
     553,   554,   556,   111,   112,   113,   114,   115,   277,   473,
     475,   477,   479,   520,   553,   554,   556,   566,   567,   568,
     570,   571,   573,   574,   132,   142,   143,   144,   145,   146,
     147,   148,   277,   520,   554,   556,   583,   584,   585,   586,
     588,   590,   592,   594,   596,   598,   600,   494,    24,    89,
      91,    92,    96,    97,    98,   277,   378,   504,   505,   506,
     507,   508,   509,   510,   512,   514,   516,   517,   519,   554,
     556,    90,    93,    94,    95,   132,   277,   378,   508,   514,
     528,   529,   530,   531,   532,   534,   535,   536,   537,   538,
     539,   554,   556,   151,   152,   277,   441,   442,   443,   445,
     196,   197,   198,   199,   200,   201,   202,   203,   277,   554,
     556,   696,   697,   698,   699,   701,   702,   704,   705,   706,
     709,    13,    14,   715,   716,   717,   719,     6,     3,     4,
       8,     3,   281,     3,     8,   288,   712,   344,   356,   358,
     360,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   333,     4,     4,     4,
       4,     4,   308,   311,   313,   315,     4,     4,     4,     4,
       4,     4,     4,   458,   495,   521,     4,   336,   338,   319,
     487,   555,   557,     4,     4,     4,   413,   425,   419,   405,
     606,   576,   434,   448,   622,     4,   427,   635,   683,   693,
     326,   328,     4,     4,     4,     4,   721,   745,     4,     3,
       8,   350,     4,     4,     4,     4,     3,     8,   542,   559,
     468,   470,   472,     4,     4,   476,   478,   480,   474,   603,
       3,     8,   552,     4,     3,     8,   569,     4,   572,     4,
       4,     3,     8,   601,   587,   589,   591,   593,   595,   597,
     599,     8,     3,     8,   511,   379,     4,   515,   513,   518,
       4,     8,     3,   533,     4,     4,     4,   540,     8,     3,
     444,   446,     3,     8,     4,   700,     4,   703,     4,     4,
     707,   710,     3,     8,   718,     4,     3,     8,   262,   262,
     242,     4,     4,     4,     4,     4,     4,     4,   243,   243,
     243,   243,   243,   243,   243,   243,   245,   244,   244,   244,
     243,   244,   243,     4,   243,   243,   245,   245,   245,     4,
       4,     4,     4,   245,   245,   244,   243,   243,   243,   245,
       4,     4,     4,   243,     4,     4,     4,     4,     4,     4,
     245,   245,   245,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   243,     4,     4,     4,     4,     4,     4,   245,
     245,   245,   245,     4,     4,   286,     4,   245,   245,   243,
     243,   348,     4,     4,     4,     4,     4,   243,   245,     4,
       4,     4,     4,     4,   466,     4,   243,   550,     4,   243,
       4,   243,   243,   567,     4,     4,     4,     4,     4,     4,
       4,     4,   585,     4,     4,   243,     4,     4,     4,   245,
     506,     4,   245,   245,   245,     4,   530,     4,     4,   442,
     245,     4,   243,     4,   243,   243,     4,     4,   697,     4,
     243,   716,     4,     7,   242,     7,     7,     7,     7,     5,
     242,   207,   208,   209,   210,   245,   309,   242,   242,   242,
       5,     5,     5,   242,   242,   103,   104,   105,   106,   320,
       5,   264,   266,   242,     5,     5,     5,     7,     5,     5,
       5,     7,     7,     7,     5,     7,     7,   242,   242,     5,
       7,     5,   273,     5,     5,   242,   242,   242,   273,   273,
     273,   242,     7,   242,   242,   242,   273,   273,   273,   273,
     242,   242,   242,   242,   242,   242,   242,   242,   242,   242,
     273,   242,   266,   242,   242,   204,   205,   708,   206,     5,
     262,   285,   715,   347,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,   187,   277,   365,   366,   367,   369,   371,   373,   375,
     377,   378,   380,   381,   382,   383,   384,   385,   386,   387,
     388,   391,   392,   393,   394,   396,   398,   400,   402,   365,
       7,   361,   362,   363,     7,   459,   460,   461,     7,   498,
     499,   500,     7,   522,   523,   524,     7,   488,   489,   490,
     145,   242,   414,   415,   416,   417,   271,   146,   148,   416,
     420,   421,   422,   423,   130,   131,   406,   407,   408,   410,
       7,   607,   608,   609,     7,   577,   578,   579,     7,   435,
     436,   437,   154,   155,   156,   157,   158,   159,   449,   450,
     451,   452,   453,   454,   455,   456,    24,   164,   165,   166,
     167,   277,   380,   554,   556,   623,   624,   625,   628,   629,
     631,   632,   170,   171,   172,   277,   428,   429,   430,   431,
     432,   554,   556,     7,   636,   637,   638,   192,   193,   194,
     242,   554,   556,   684,   685,   686,   687,   689,   690,   696,
       7,   722,   723,   227,   277,   746,   747,   748,   274,     7,
     543,   544,   545,     7,   560,   561,   562,   586,   604,   361,
       8,     8,     8,   368,   370,   372,   376,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   389,     4,     4,
     395,   397,   399,   401,   403,   374,     3,     8,     8,   364,
       6,     3,   462,     6,     3,   501,     6,     3,   525,     6,
       3,   491,     6,     3,     3,     6,     6,     3,     6,   409,
     411,     3,     8,   610,     6,     3,   580,     6,     3,   438,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
     626,   630,     4,     4,     4,     3,     8,     4,     4,     4,
       3,     8,   639,     6,     3,     4,   688,     4,   691,     3,
       8,     8,   724,     3,     6,     4,     3,     8,   242,   275,
     276,   546,     6,     3,   563,     6,     3,     8,     6,     4,
       4,     4,     4,   243,   245,   243,   245,   243,   243,   243,
     243,   243,   243,     4,   245,   243,     4,     4,     4,     4,
       4,     4,   366,   365,   363,   465,   461,   504,   500,   528,
     524,   277,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   304,   305,   306,   307,
     310,   312,   314,   316,   317,   318,   321,   322,   323,   324,
     325,   327,   329,   335,   337,   378,   457,   469,   471,   473,
     475,   477,   479,   481,   482,   483,   485,   492,   493,   520,
     554,   556,   602,   490,   415,   421,     4,     4,   407,   135,
     136,   137,   138,   277,   289,   290,   291,   292,   293,   294,
     378,   520,   554,   556,   611,   612,   613,   614,   615,   617,
     619,   620,   609,   583,   579,   441,   437,   243,   243,   243,
     243,   243,   243,   450,     4,     4,   243,   243,   243,   624,
     245,   243,   243,   429,   174,   178,   179,   180,   181,   188,
     189,   277,   394,   396,   398,   554,   556,   640,   641,   642,
     645,   647,   649,   650,   651,   661,   638,   245,     4,   243,
       4,   685,   218,   220,   221,   277,   378,   554,   556,   725,
     726,   727,   728,   730,   723,   245,   747,     6,     3,   549,
     545,   566,   562,   242,   242,   242,   242,    39,    40,    41,
     390,   242,   242,   242,   400,   242,   242,     8,     8,     8,
       8,     3,     8,   242,   242,   616,   618,     4,     4,     8,
       3,     8,     8,   161,   162,   163,   627,   242,   643,   646,
     648,     4,   662,     4,   652,     3,     8,   242,   262,   731,
       4,   729,     3,     8,   242,     8,     8,   493,     4,     4,
     245,   245,   613,     4,     4,     4,   243,     4,   245,     4,
     641,     4,   243,     4,   726,   242,   242,   175,   176,   177,
     644,   242,   242,     7,     5,     5,   242,    24,   183,   184,
     185,   277,   554,   556,   663,   664,   665,   668,   670,   672,
       7,   653,   654,   655,     7,   732,   733,   666,   669,   671,
     673,     3,     8,   656,     6,     3,   734,     3,     6,     4,
       4,     4,     4,   664,   190,   277,   378,   554,   556,   657,
     658,   659,   655,   219,   222,   223,   224,   225,   735,   736,
     737,   739,   740,   741,   742,   733,   182,   667,   242,   242,
       5,   660,     3,     8,   738,     4,     4,     4,   743,     3,
       8,     7,   674,   675,   676,     4,   658,     4,   245,   243,
     243,     4,   736,   677,     6,     3,   242,   242,   242,   186,
     277,   369,   371,   373,   554,   556,   678,   679,   680,   676,
     681,     3,     8,     4,   679,   242
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
     309,   309,   309,   311,   310,   313,   312,   315,   314,   316,
     317,   319,   318,   320,   320,   320,   320,   321,   322,   323,
     324,   326,   325,   328,   327,   329,   330,   331,   333,   332,
     334,   336,   335,   338,   337,   339,   340,   341,   342,   344,
     343,   346,   345,   347,   347,   347,   348,   348,   348,   348,
     348,   348,   348,   348,   350,   349,   351,   352,   353,   354,
     356,   355,   358,   357,   360,   359,   361,   361,   362,   362,
     362,   364,   363,   365,   365,   365,   366,   366,   366,   366,
     366,   366,   366,   366,   366,   366,   366,   366,   366,   366,
     366,   366,   366,   366,   366,   366,   366,   366,   366,   366,
     366,   368,   367,   370,   369,   372,   371,   374,   373,   376,
     375,   377,   379,   378,   380,   381,   382,   383,   384,   385,
     386,   387,   389,   388,   390,   390,   390,   391,   392,   393,
     395,   394,   397,   396,   399,   398,   401,   400,   400,   400,
     400,   400,   400,   403,   402,   405,   404,   406,   406,   406,
     407,   407,   409,   408,   411,   410,   413,   412,   414,   414,
     414,   415,   415,   416,   417,   419,   418,   420,   420,   420,
     421,   421,   421,   422,   423,   425,   424,   427,   426,   428,
     428,   428,   429,   429,   429,   429,   429,   429,   430,   431,
     432,   434,   433,   435,   435,   436,   436,   436,   438,   437,
     440,   439,   441,   441,   441,   441,   442,   442,   444,   443,
     446,   445,   448,   447,   449,   449,   449,   450,   450,   450,
     450,   450,   450,   451,   452,   453,   454,   455,   456,   458,
     457,   459,   459,   460,   460,   460,   462,   461,   464,   463,
     465,   465,   465,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   468,   467,   470,   469,
     472,   471,   474,   473,   476,   475,   478,   477,   480,   479,
     481,   482,   483,   484,   485,   487,   486,   488,   488,   489,
     489,   489,   491,   490,   492,   492,   492,   493,   493,   493,
     493,   493,   493,   493,   493,   493,   493,   493,   493,   493,
     493,   493,   493,   493,   493,   493,   493,   493,   493,   493,
     493,   493,   493,   493,   493,   493,   493,   493,   493,   493,
     493,   493,   493,   493,   493,   493,   493,   493,   493,   493,
     493,   493,   493,   493,   493,   493,   493,   495,   494,   497,
     496,   498,   498,   499,   499,   499,   501,   500,   503,   502,
     504,   504,   505,   505,   505,   506,   506,   506,   506,   506,
     506,   506,   506,   506,   506,   507,   508,   509,   511,   510,
     513,   512,   515,   514,   516,   518,   517,   519,   521,   520,
     522,   522,   523,   523,   523,   525,   524,   527,   526,   528,
     528,   529,   529,   529,   530,   530,   530,   530,   530,   530,
     530,   530,   530,   530,   530,   531,   533,   532,   534,   535,
     536,   537,   538,   540,   539,   542,   541,   543,   543,   544,
     544,   544,   546,   545,   548,   547,   549,   549,   549,   550,
     550,   550,   550,   550,   550,   550,   550,   550,   550,   550,
     550,   550,   550,   550,   550,   550,   550,   550,   550,   550,
     550,   550,   550,   550,   552,   551,   553,   555,   554,   557,
     556,   559,   558,   560,   560,   561,   561,   561,   563,   562,
     565,   564,   566,   566,   566,   567,   567,   567,   567,   567,
     567,   567,   567,   567,   567,   567,   567,   567,   567,   569,
     568,   570,   572,   571,   573,   574,   576,   575,   577,   577,
     578,   578,   578,   580,   579,   582,   581,   583,   583,   584,
     584,   584,   585,   585,   585,   585,   585,   585,   585,   585,
     585,   585,   585,   585,   587,   586,   589,   588,   591,   590,
     593,   592,   595,   594,   597,   596,   599,   598,   601,   600,
     603,   602,   604,   606,   605,   607,   607,   608,   608,   608,
     610,   609,   611,   611,   612,   612,   612,   613,   613,   613,
     613,   613,   613,   613,   613,   613,   613,   613,   613,   613,
     613,   613,   614,   616,   615,   618,   617,   619,   620,   622,
     621,   623,   623,   623,   624,   624,   624,   624,   624,   624,
     624,   624,   624,   626,   625,   627,   627,   627,   628,   630,
     629,   631,   632,   633,   635,   634,   636,   636,   637,   637,
     637,   639,   638,   640,   640,   640,   641,   641,   641,   641,
     641,   641,   641,   641,   641,   641,   641,   641,   641,   643,
     642,   644,   644,   644,   646,   645,   648,   647,   649,   650,
     652,   651,   653,   653,   654,   654,   654,   656,   655,   657,
     657,   657,   658,   658,   658,   658,   658,   660,   659,   662,
     661,   663,   663,   663,   664,   664,   664,   664,   664,   664,
     664,   666,   665,   667,   669,   668,   671,   670,   673,   672,
     674,   674,   675,   675,   675,   677,   676,   678,   678,   678,
     679,   679,   679,   679,   679,   679,   679,   681,   680,   683,
     682,   684,   684,   684,   685,   685,   685,   685,   685,   685,
     686,   688,   687,   689,   691,   690,   693,   692,   695,   694,
     696,   696,   696,   697,   697,   697,   697,   697,   697,   697,
     697,   697,   697,   697,   698,   700,   699,   701,   703,   702,
     704,   705,   707,   706,   708,   708,   710,   709,   712,   711,
     714,   713,   715,   715,   715,   716,   716,   718,   717,   719,
     721,   720,   722,   722,   722,   724,   723,   725,   725,   725,
     726,   726,   726,   726,   726,   726,   726,   727,   729,   728,
     731,   730,   732,   732,   732,   734,   733,   735,   735,   735,
     736,   736,   736,   736,   736,   738,   737,   739,   740,   741,
     743,   742,   745,   744,   746,   746,   746,   747,   747,   748
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
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       3,     3,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     1,     3,     2,     1,     1,     1,
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
       1,     1,     1,     1,     0,     4,     3,     0,     4,     0,
       4,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     4,     3,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     0,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     1,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     3,     3,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     3,     0,
       4,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     0,     4,     0,     4,     3,     3,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     0,     4,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     3,     0,     4,     0,     6,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     3,     0,     4,
       3,     3,     0,     4,     1,     1,     0,     4,     0,     6,
       0,     4,     1,     3,     2,     1,     1,     0,     6,     3,
       0,     6,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     6,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     0,     4,     3,     3,     3,
       0,     4,     0,     6,     1,     3,     2,     1,     1,     3
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
  "$@67", "interface", "$@68", "interface_id", "$@69", "client_class",
  "$@70", "network_client_classes", "$@71", "require_client_classes",
  "$@72", "evaluate_additional_classes", "$@73", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "id",
  "rapid_commit", "shared_networks", "$@74", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@75",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@76", "sub_option_def_list", "$@77", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@78",
  "sub_option_def", "$@79", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@80",
  "option_def_record_types", "$@81", "space", "$@82", "option_def_space",
  "option_def_encapsulate", "$@83", "option_def_array", "option_data_list",
  "$@84", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@85", "sub_option_data", "$@86",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@87",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "option_data_never_send",
  "option_data_client_classes", "$@88", "pools_list", "$@89",
  "pools_list_content", "not_empty_pools_list", "pool_list_entry", "$@90",
  "sub_pool6", "$@91", "pool_params", "pool_param", "pool_entry", "$@92",
  "pool_id", "user_context", "$@93", "comment", "$@94", "pd_pools_list",
  "$@95", "pd_pools_list_content", "not_empty_pd_pools_list",
  "pd_pool_entry", "$@96", "sub_pd_pool", "$@97", "pd_pool_params",
  "pd_pool_param", "pd_prefix", "$@98", "pd_prefix_len", "excluded_prefix",
  "$@99", "excluded_prefix_len", "pd_delegated_len", "reservations",
  "$@100", "reservations_list", "not_empty_reservations_list",
  "reservation", "$@101", "sub_reservation", "$@102", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@103", "prefixes", "$@104", "excluded_prefixes", "$@105", "duid",
  "$@106", "hw_address", "$@107", "hostname", "$@108", "flex_id_value",
  "$@109", "reservation_client_classes", "$@110", "relay", "$@111",
  "relay_map", "client_classes", "$@112", "client_classes_list",
  "not_empty_classes_list", "client_class_entry", "$@113",
  "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@114",
  "client_class_template_test", "$@115", "only_if_required",
  "only_in_additional_list", "server_id", "$@116", "server_id_params",
  "server_id_param", "server_id_type", "$@117", "duid_type", "htype",
  "identifier", "$@118", "time", "enterprise_id", "dhcp4o6_port",
  "control_sockets", "$@119", "control_socket_list",
  "not_empty_control_socket_list", "control_socket_entry", "$@120",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@121", "control_socket_type_value", "control_socket_name", "$@122",
  "control_socket_address", "$@123", "control_socket_port",
  "cert_required", "http_headers", "$@124", "http_header_list",
  "not_empty_http_header_list", "http_header", "$@125",
  "http_header_params", "http_header_param", "header_value", "$@126",
  "authentication", "$@127", "auth_params", "auth_param", "auth_type",
  "$@128", "auth_type_value", "realm", "$@129", "directory", "$@130",
  "clients", "$@131", "clients_list", "not_empty_clients_list",
  "basic_auth", "$@132", "clients_params", "clients_param", "user_file",
  "$@133", "dhcp_queue_control", "$@134", "queue_control_params",
  "queue_control_param", "enable_queue", "queue_type", "$@135", "capacity",
  "arbitrary_map_entry", "$@136", "dhcp_ddns", "$@137", "sub_dhcp_ddns",
  "$@138", "dhcp_ddns_params", "dhcp_ddns_param", "enable_updates",
  "server_ip", "$@139", "server_port", "sender_ip", "$@140", "sender_port",
  "max_queue_size", "ncr_protocol", "$@141", "ncr_protocol_value",
  "ncr_format", "$@142", "config_control", "$@143", "sub_config_control",
  "$@144", "config_control_params", "config_control_param",
  "config_databases", "$@145", "config_fetch_wait_time", "loggers",
  "$@146", "loggers_entries", "logger_entry", "$@147", "logger_params",
  "logger_param", "debuglevel", "severity", "$@148", "output_options_list",
  "$@149", "output_options_list_content", "output_entry", "$@150",
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
     738,   741,   744,   750,   750,   759,   759,   768,   768,   777,
     786,   796,   796,   805,   808,   811,   814,   819,   825,   831,
     837,   843,   843,   852,   852,   861,   867,   873,   879,   879,
     888,   894,   894,   903,   903,   912,   918,   924,   930,   936,
     936,   948,   948,   957,   958,   959,   964,   965,   966,   967,
     968,   969,   970,   971,   974,   974,   985,   991,   997,  1003,
    1009,  1009,  1022,  1022,  1035,  1035,  1046,  1047,  1050,  1051,
    1052,  1057,  1057,  1067,  1068,  1069,  1074,  1075,  1076,  1077,
    1078,  1079,  1080,  1081,  1082,  1083,  1084,  1085,  1086,  1087,
    1088,  1089,  1090,  1091,  1092,  1093,  1094,  1095,  1096,  1097,
    1098,  1101,  1101,  1110,  1110,  1119,  1119,  1128,  1128,  1137,
    1137,  1146,  1152,  1152,  1161,  1167,  1173,  1179,  1185,  1191,
    1197,  1203,  1209,  1209,  1217,  1218,  1219,  1222,  1228,  1234,
    1240,  1240,  1249,  1249,  1258,  1258,  1267,  1267,  1275,  1278,
    1281,  1284,  1287,  1292,  1292,  1301,  1301,  1312,  1313,  1314,
    1319,  1320,  1323,  1323,  1342,  1342,  1360,  1360,  1371,  1372,
    1373,  1378,  1379,  1382,  1387,  1392,  1392,  1403,  1404,  1405,
    1410,  1411,  1412,  1415,  1420,  1427,  1427,  1440,  1440,  1453,
    1454,  1455,  1460,  1461,  1462,  1463,  1464,  1465,  1468,  1474,
    1480,  1486,  1486,  1497,  1498,  1501,  1502,  1503,  1508,  1508,
    1518,  1518,  1528,  1529,  1530,  1533,  1536,  1537,  1540,  1540,
    1549,  1549,  1558,  1558,  1570,  1571,  1572,  1577,  1578,  1579,
    1580,  1581,  1582,  1585,  1591,  1597,  1603,  1609,  1615,  1624,
    1624,  1638,  1639,  1642,  1643,  1644,  1653,  1653,  1679,  1679,
    1690,  1691,  1692,  1698,  1699,  1700,  1701,  1702,  1703,  1704,
    1705,  1706,  1707,  1708,  1709,  1710,  1711,  1712,  1713,  1714,
    1715,  1716,  1717,  1718,  1719,  1720,  1721,  1722,  1723,  1724,
    1725,  1726,  1727,  1728,  1729,  1730,  1731,  1732,  1733,  1734,
    1735,  1736,  1737,  1738,  1739,  1740,  1741,  1742,  1743,  1744,
    1745,  1746,  1747,  1748,  1749,  1750,  1753,  1753,  1762,  1762,
    1771,  1771,  1780,  1780,  1790,  1790,  1802,  1802,  1813,  1813,
    1824,  1830,  1836,  1842,  1848,  1856,  1856,  1868,  1869,  1873,
    1874,  1875,  1880,  1880,  1888,  1889,  1890,  1895,  1896,  1897,
    1898,  1899,  1900,  1901,  1902,  1903,  1904,  1905,  1906,  1907,
    1908,  1909,  1910,  1911,  1912,  1913,  1914,  1915,  1916,  1917,
    1918,  1919,  1920,  1921,  1922,  1923,  1924,  1925,  1926,  1927,
    1928,  1929,  1930,  1931,  1932,  1933,  1934,  1935,  1936,  1937,
    1938,  1939,  1940,  1941,  1942,  1943,  1944,  1951,  1951,  1965,
    1965,  1974,  1975,  1978,  1979,  1980,  1987,  1987,  2002,  2002,
    2016,  2017,  2020,  2021,  2022,  2027,  2028,  2029,  2030,  2031,
    2032,  2033,  2034,  2035,  2036,  2039,  2041,  2047,  2049,  2049,
    2058,  2058,  2067,  2067,  2076,  2078,  2078,  2087,  2097,  2097,
    2110,  2111,  2116,  2117,  2118,  2125,  2125,  2137,  2137,  2149,
    2150,  2155,  2156,  2157,  2164,  2165,  2166,  2167,  2168,  2169,
    2170,  2171,  2172,  2173,  2174,  2177,  2179,  2179,  2188,  2190,
    2192,  2198,  2204,  2210,  2210,  2224,  2224,  2237,  2238,  2241,
    2242,  2243,  2248,  2248,  2258,  2258,  2268,  2269,  2270,  2275,
    2276,  2277,  2278,  2279,  2280,  2281,  2282,  2283,  2284,  2285,
    2286,  2287,  2288,  2289,  2290,  2291,  2292,  2293,  2294,  2295,
    2296,  2297,  2298,  2299,  2302,  2302,  2311,  2317,  2317,  2342,
    2342,  2372,  2372,  2385,  2386,  2389,  2390,  2391,  2396,  2396,
    2408,  2408,  2420,  2421,  2422,  2427,  2428,  2429,  2430,  2431,
    2432,  2433,  2434,  2435,  2436,  2437,  2438,  2439,  2440,  2443,
    2443,  2452,  2458,  2458,  2467,  2473,  2482,  2482,  2493,  2494,
    2497,  2498,  2499,  2504,  2504,  2513,  2513,  2522,  2523,  2526,
    2527,  2528,  2534,  2535,  2536,  2537,  2538,  2539,  2540,  2541,
    2542,  2543,  2544,  2545,  2548,  2548,  2559,  2559,  2570,  2570,
    2581,  2581,  2590,  2590,  2599,  2599,  2608,  2608,  2617,  2617,
    2631,  2631,  2642,  2648,  2648,  2659,  2660,  2663,  2664,  2665,
    2670,  2670,  2680,  2681,  2684,  2685,  2686,  2691,  2692,  2693,
    2694,  2695,  2696,  2697,  2698,  2699,  2700,  2701,  2702,  2703,
    2704,  2705,  2708,  2710,  2710,  2719,  2719,  2729,  2735,  2744,
    2744,  2757,  2758,  2759,  2764,  2765,  2766,  2767,  2768,  2769,
    2770,  2771,  2772,  2775,  2775,  2783,  2784,  2785,  2788,  2794,
    2794,  2803,  2809,  2817,  2825,  2825,  2836,  2837,  2840,  2841,
    2842,  2847,  2847,  2855,  2856,  2857,  2862,  2863,  2864,  2865,
    2866,  2867,  2868,  2869,  2870,  2871,  2872,  2873,  2874,  2877,
    2877,  2886,  2887,  2888,  2891,  2891,  2900,  2900,  2909,  2915,
    2921,  2921,  2932,  2933,  2936,  2937,  2938,  2943,  2943,  2951,
    2952,  2953,  2958,  2959,  2960,  2961,  2962,  2965,  2965,  2976,
    2976,  2989,  2990,  2991,  2996,  2997,  2998,  2999,  3000,  3001,
    3002,  3005,  3005,  3013,  3016,  3016,  3025,  3025,  3034,  3034,
    3045,  3046,  3049,  3050,  3051,  3056,  3056,  3064,  3065,  3066,
    3071,  3072,  3073,  3074,  3075,  3076,  3077,  3080,  3080,  3091,
    3091,  3104,  3105,  3106,  3111,  3112,  3113,  3114,  3115,  3116,
    3119,  3125,  3125,  3134,  3140,  3140,  3150,  3150,  3163,  3163,
    3173,  3174,  3175,  3180,  3181,  3182,  3183,  3184,  3185,  3186,
    3187,  3188,  3189,  3190,  3193,  3199,  3199,  3208,  3214,  3214,
    3223,  3229,  3235,  3235,  3244,  3245,  3248,  3248,  3259,  3259,
    3271,  3271,  3281,  3282,  3283,  3289,  3290,  3293,  3293,  3304,
    3312,  3312,  3325,  3326,  3327,  3333,  3333,  3341,  3342,  3343,
    3348,  3349,  3350,  3351,  3352,  3353,  3354,  3357,  3363,  3363,
    3372,  3372,  3383,  3384,  3385,  3390,  3390,  3398,  3399,  3400,
    3405,  3406,  3407,  3408,  3409,  3412,  3412,  3421,  3427,  3433,
    3439,  3439,  3448,  3448,  3459,  3460,  3461,  3466,  3467,  3470
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
#line 7187 "dhcp6_parser.cc"

#line 3476 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
