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

  case 269: // $@38: %empty
#line 1092 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1951 "dhcp6_parser.cc"
    break;

  case 270: // database_type: "type" $@38 ":" "constant string"
#line 1095 "dhcp6_parser.yy"
               {
    ElementPtr db_type(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", db_type);
    ctx.leave();
}
#line 1961 "dhcp6_parser.cc"
    break;

  case 271: // $@39: %empty
#line 1101 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1970 "dhcp6_parser.cc"
    break;

  case 272: // user: "user" $@39 ":" "constant string"
#line 1104 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1980 "dhcp6_parser.cc"
    break;

  case 273: // $@40: %empty
#line 1110 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1989 "dhcp6_parser.cc"
    break;

  case 274: // password: "password" $@40 ":" "constant string"
#line 1113 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1999 "dhcp6_parser.cc"
    break;

  case 275: // $@41: %empty
#line 1119 "dhcp6_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2008 "dhcp6_parser.cc"
    break;

  case 276: // password_file: "password-file" $@41 ":" "constant string"
#line 1122 "dhcp6_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 2018 "dhcp6_parser.cc"
    break;

  case 277: // $@42: %empty
#line 1128 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2027 "dhcp6_parser.cc"
    break;

  case 278: // host: "host" $@42 ":" "constant string"
#line 1131 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2037 "dhcp6_parser.cc"
    break;

  case 279: // port: "port" ":" "integer"
#line 1137 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2047 "dhcp6_parser.cc"
    break;

  case 280: // $@43: %empty
#line 1143 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2056 "dhcp6_parser.cc"
    break;

  case 281: // name: "name" $@43 ":" "constant string"
#line 1146 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2066 "dhcp6_parser.cc"
    break;

  case 282: // persist: "persist" ":" "boolean"
#line 1152 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2076 "dhcp6_parser.cc"
    break;

  case 283: // lfc_interval: "lfc-interval" ":" "integer"
#line 1158 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2086 "dhcp6_parser.cc"
    break;

  case 284: // readonly: "readonly" ":" "boolean"
#line 1164 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2096 "dhcp6_parser.cc"
    break;

  case 285: // connect_timeout: "connect-timeout" ":" "integer"
#line 1170 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2106 "dhcp6_parser.cc"
    break;

  case 286: // read_timeout: "read-timeout" ":" "integer"
#line 1176 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2116 "dhcp6_parser.cc"
    break;

  case 287: // write_timeout: "write-timeout" ":" "integer"
#line 1182 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2126 "dhcp6_parser.cc"
    break;

  case 288: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1188 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2136 "dhcp6_parser.cc"
    break;

  case 289: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1194 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2146 "dhcp6_parser.cc"
    break;

  case 290: // $@44: %empty
#line 1200 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2155 "dhcp6_parser.cc"
    break;

  case 291: // on_fail: "on-fail" $@44 ":" on_fail_mode
#line 1203 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2164 "dhcp6_parser.cc"
    break;

  case 292: // on_fail_mode: "stop-retry-exit"
#line 1208 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2170 "dhcp6_parser.cc"
    break;

  case 293: // on_fail_mode: "serve-retry-exit"
#line 1209 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2176 "dhcp6_parser.cc"
    break;

  case 294: // on_fail_mode: "serve-retry-continue"
#line 1210 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2182 "dhcp6_parser.cc"
    break;

  case 295: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1213 "dhcp6_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2192 "dhcp6_parser.cc"
    break;

  case 296: // max_row_errors: "max-row-errors" ":" "integer"
#line 1219 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2202 "dhcp6_parser.cc"
    break;

  case 297: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1225 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2212 "dhcp6_parser.cc"
    break;

  case 298: // $@45: %empty
#line 1231 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2221 "dhcp6_parser.cc"
    break;

  case 299: // trust_anchor: "trust-anchor" $@45 ":" "constant string"
#line 1234 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2231 "dhcp6_parser.cc"
    break;

  case 300: // $@46: %empty
#line 1240 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2240 "dhcp6_parser.cc"
    break;

  case 301: // cert_file: "cert-file" $@46 ":" "constant string"
#line 1243 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2250 "dhcp6_parser.cc"
    break;

  case 302: // $@47: %empty
#line 1249 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2259 "dhcp6_parser.cc"
    break;

  case 303: // key_file: "key-file" $@47 ":" "constant string"
#line 1252 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2269 "dhcp6_parser.cc"
    break;

  case 304: // $@48: %empty
#line 1258 "dhcp6_parser.yy"
                   {
    ctx.unique("ssl-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SSL_MODE);
}
#line 2278 "dhcp6_parser.cc"
    break;

  case 305: // ssl_mode: "ssl-mode" $@48 ":" ssl_mode
#line 1261 "dhcp6_parser.yy"
                 {
    ctx.stack_.back()->set("ssl-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2287 "dhcp6_parser.cc"
    break;

  case 306: // ssl_mode: "disable"
#line 1266 "dhcp6_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disable", ctx.loc2pos(yystack_[0].location)));
            }
#line 2295 "dhcp6_parser.cc"
    break;

  case 307: // ssl_mode: "prefer"
#line 1269 "dhcp6_parser.yy"
                 {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("prefer", ctx.loc2pos(yystack_[0].location)));
            }
#line 2303 "dhcp6_parser.cc"
    break;

  case 308: // ssl_mode: "require"
#line 1272 "dhcp6_parser.yy"
                  {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("require", ctx.loc2pos(yystack_[0].location)));
            }
#line 2311 "dhcp6_parser.cc"
    break;

  case 309: // ssl_mode: "verify-ca"
#line 1275 "dhcp6_parser.yy"
                    {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-ca", ctx.loc2pos(yystack_[0].location)));
            }
#line 2319 "dhcp6_parser.cc"
    break;

  case 310: // ssl_mode: "verify-full"
#line 1278 "dhcp6_parser.yy"
                      {
            yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("verify-full", ctx.loc2pos(yystack_[0].location)));
            }
#line 2327 "dhcp6_parser.cc"
    break;

  case 311: // $@49: %empty
#line 1283 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2336 "dhcp6_parser.cc"
    break;

  case 312: // cipher_list: "cipher-list" $@49 ":" "constant string"
#line 1286 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2346 "dhcp6_parser.cc"
    break;

  case 313: // $@50: %empty
#line 1292 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2358 "dhcp6_parser.cc"
    break;

  case 314: // sanity_checks: "sanity-checks" $@50 ":" "{" sanity_checks_params "}"
#line 1298 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2367 "dhcp6_parser.cc"
    break;

  case 317: // sanity_checks_params: sanity_checks_params ","
#line 1305 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2375 "dhcp6_parser.cc"
    break;

  case 320: // $@51: %empty
#line 1314 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2384 "dhcp6_parser.cc"
    break;

  case 321: // lease_checks: "lease-checks" $@51 ":" "constant string"
#line 1317 "dhcp6_parser.yy"
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

  case 322: // $@52: %empty
#line 1333 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2413 "dhcp6_parser.cc"
    break;

  case 323: // extended_info_checks: "extended-info-checks" $@52 ":" "constant string"
#line 1336 "dhcp6_parser.yy"
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

  case 324: // $@53: %empty
#line 1351 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2444 "dhcp6_parser.cc"
    break;

  case 325: // mac_sources: "mac-sources" $@53 ":" "[" mac_sources_list "]"
#line 1357 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2453 "dhcp6_parser.cc"
    break;

  case 328: // mac_sources_list: mac_sources_list ","
#line 1364 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2461 "dhcp6_parser.cc"
    break;

  case 331: // duid_id: "duid"
#line 1373 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2470 "dhcp6_parser.cc"
    break;

  case 332: // string_id: "constant string"
#line 1378 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2479 "dhcp6_parser.cc"
    break;

  case 333: // $@54: %empty
#line 1383 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2491 "dhcp6_parser.cc"
    break;

  case 334: // host_reservation_identifiers: "host-reservation-identifiers" $@54 ":" "[" host_reservation_identifiers_list "]"
#line 1389 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2500 "dhcp6_parser.cc"
    break;

  case 337: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1396 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2508 "dhcp6_parser.cc"
    break;

  case 341: // hw_address_id: "hw-address"
#line 1406 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2517 "dhcp6_parser.cc"
    break;

  case 342: // flex_id: "flex-id"
#line 1411 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2526 "dhcp6_parser.cc"
    break;

  case 343: // $@55: %empty
#line 1418 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2538 "dhcp6_parser.cc"
    break;

  case 344: // relay_supplied_options: "relay-supplied-options" $@55 ":" "[" list_content "]"
#line 1424 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2547 "dhcp6_parser.cc"
    break;

  case 345: // $@56: %empty
#line 1431 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2559 "dhcp6_parser.cc"
    break;

  case 346: // dhcp_multi_threading: "multi-threading" $@56 ":" "{" multi_threading_params "}"
#line 1437 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2570 "dhcp6_parser.cc"
    break;

  case 349: // multi_threading_params: multi_threading_params ","
#line 1446 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2578 "dhcp6_parser.cc"
    break;

  case 356: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1459 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2588 "dhcp6_parser.cc"
    break;

  case 357: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1465 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2598 "dhcp6_parser.cc"
    break;

  case 358: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1471 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2608 "dhcp6_parser.cc"
    break;

  case 359: // $@57: %empty
#line 1477 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2620 "dhcp6_parser.cc"
    break;

  case 360: // hooks_libraries: "hooks-libraries" $@57 ":" "[" hooks_libraries_list "]"
#line 1483 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2629 "dhcp6_parser.cc"
    break;

  case 365: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1494 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2637 "dhcp6_parser.cc"
    break;

  case 366: // $@58: %empty
#line 1499 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2647 "dhcp6_parser.cc"
    break;

  case 367: // hooks_library: "{" $@58 hooks_params "}"
#line 1503 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2657 "dhcp6_parser.cc"
    break;

  case 368: // $@59: %empty
#line 1509 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2667 "dhcp6_parser.cc"
    break;

  case 369: // sub_hooks_library: "{" $@59 hooks_params "}"
#line 1513 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2677 "dhcp6_parser.cc"
    break;

  case 372: // hooks_params: hooks_params ","
#line 1521 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2685 "dhcp6_parser.cc"
    break;

  case 376: // $@60: %empty
#line 1531 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2694 "dhcp6_parser.cc"
    break;

  case 377: // library: "library" $@60 ":" "constant string"
#line 1534 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2704 "dhcp6_parser.cc"
    break;

  case 378: // $@61: %empty
#line 1540 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2713 "dhcp6_parser.cc"
    break;

  case 379: // parameters: "parameters" $@61 ":" map_value
#line 1543 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2722 "dhcp6_parser.cc"
    break;

  case 380: // $@62: %empty
#line 1549 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2734 "dhcp6_parser.cc"
    break;

  case 381: // expired_leases_processing: "expired-leases-processing" $@62 ":" "{" expired_leases_params "}"
#line 1555 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2744 "dhcp6_parser.cc"
    break;

  case 384: // expired_leases_params: expired_leases_params ","
#line 1563 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2752 "dhcp6_parser.cc"
    break;

  case 391: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1576 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2762 "dhcp6_parser.cc"
    break;

  case 392: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1582 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2772 "dhcp6_parser.cc"
    break;

  case 393: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1588 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2782 "dhcp6_parser.cc"
    break;

  case 394: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1594 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2792 "dhcp6_parser.cc"
    break;

  case 395: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1600 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2802 "dhcp6_parser.cc"
    break;

  case 396: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1606 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2812 "dhcp6_parser.cc"
    break;

  case 397: // $@63: %empty
#line 1615 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2824 "dhcp6_parser.cc"
    break;

  case 398: // subnet6_list: "subnet6" $@63 ":" "[" subnet6_list_content "]"
#line 1621 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2833 "dhcp6_parser.cc"
    break;

  case 403: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1635 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2841 "dhcp6_parser.cc"
    break;

  case 404: // $@64: %empty
#line 1644 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2851 "dhcp6_parser.cc"
    break;

  case 405: // subnet6: "{" $@64 subnet6_params "}"
#line 1648 "dhcp6_parser.yy"
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

  case 406: // $@65: %empty
#line 1670 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2887 "dhcp6_parser.cc"
    break;

  case 407: // sub_subnet6: "{" $@65 subnet6_params "}"
#line 1674 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2897 "dhcp6_parser.cc"
    break;

  case 410: // subnet6_params: subnet6_params ","
#line 1683 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2905 "dhcp6_parser.cc"
    break;

  case 463: // $@66: %empty
#line 1743 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2914 "dhcp6_parser.cc"
    break;

  case 464: // subnet: "subnet" $@66 ":" "constant string"
#line 1746 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2924 "dhcp6_parser.cc"
    break;

  case 465: // $@67: %empty
#line 1752 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2933 "dhcp6_parser.cc"
    break;

  case 466: // interface: "interface" $@67 ":" "constant string"
#line 1755 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2943 "dhcp6_parser.cc"
    break;

  case 467: // $@68: %empty
#line 1761 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2952 "dhcp6_parser.cc"
    break;

  case 468: // interface_id: "interface-id" $@68 ":" "constant string"
#line 1764 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2962 "dhcp6_parser.cc"
    break;

  case 469: // $@69: %empty
#line 1770 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2971 "dhcp6_parser.cc"
    break;

  case 470: // client_class: "client-class" $@69 ":" "constant string"
#line 1773 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2981 "dhcp6_parser.cc"
    break;

  case 471: // $@70: %empty
#line 1780 "dhcp6_parser.yy"
                                       {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2993 "dhcp6_parser.cc"
    break;

  case 472: // network_client_classes: "client-classes" $@70 ":" list_strings
#line 1786 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3002 "dhcp6_parser.cc"
    break;

  case 473: // $@71: %empty
#line 1792 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3014 "dhcp6_parser.cc"
    break;

  case 474: // require_client_classes: "require-client-classes" $@71 ":" list_strings
#line 1798 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3023 "dhcp6_parser.cc"
    break;

  case 475: // $@72: %empty
#line 1803 "dhcp6_parser.yy"
                                                         {
    ctx.unique("evaluate-additional-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("evaluate-additional-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3035 "dhcp6_parser.cc"
    break;

  case 476: // evaluate_additional_classes: "evaluate-additional-classes" $@72 ":" list_strings
#line 1809 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3044 "dhcp6_parser.cc"
    break;

  case 477: // reservations_global: "reservations-global" ":" "boolean"
#line 1814 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 3054 "dhcp6_parser.cc"
    break;

  case 478: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1820 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 3064 "dhcp6_parser.cc"
    break;

  case 479: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1826 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 3074 "dhcp6_parser.cc"
    break;

  case 480: // id: "id" ":" "integer"
#line 1832 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 3084 "dhcp6_parser.cc"
    break;

  case 481: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1838 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 3094 "dhcp6_parser.cc"
    break;

  case 482: // $@73: %empty
#line 1846 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 3106 "dhcp6_parser.cc"
    break;

  case 483: // shared_networks: "shared-networks" $@73 ":" "[" shared_networks_content "]"
#line 1852 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3115 "dhcp6_parser.cc"
    break;

  case 488: // shared_networks_list: shared_networks_list ","
#line 1865 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3123 "dhcp6_parser.cc"
    break;

  case 489: // $@74: %empty
#line 1870 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3133 "dhcp6_parser.cc"
    break;

  case 490: // shared_network: "{" $@74 shared_network_params "}"
#line 1874 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 3141 "dhcp6_parser.cc"
    break;

  case 493: // shared_network_params: shared_network_params ","
#line 1880 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 3149 "dhcp6_parser.cc"
    break;

  case 543: // $@75: %empty
#line 1940 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3161 "dhcp6_parser.cc"
    break;

  case 544: // option_def_list: "option-def" $@75 ":" "[" option_def_list_content "]"
#line 1946 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3170 "dhcp6_parser.cc"
    break;

  case 545: // $@76: %empty
#line 1954 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3179 "dhcp6_parser.cc"
    break;

  case 546: // sub_option_def_list: "{" $@76 option_def_list "}"
#line 1957 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 3187 "dhcp6_parser.cc"
    break;

  case 551: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1969 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3195 "dhcp6_parser.cc"
    break;

  case 552: // $@77: %empty
#line 1976 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3205 "dhcp6_parser.cc"
    break;

  case 553: // option_def_entry: "{" $@77 option_def_params "}"
#line 1980 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3217 "dhcp6_parser.cc"
    break;

  case 554: // $@78: %empty
#line 1991 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3227 "dhcp6_parser.cc"
    break;

  case 555: // sub_option_def: "{" $@78 option_def_params "}"
#line 1995 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3239 "dhcp6_parser.cc"
    break;

  case 560: // not_empty_option_def_params: not_empty_option_def_params ","
#line 2011 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3247 "dhcp6_parser.cc"
    break;

  case 572: // code: "code" ":" "integer"
#line 2030 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3257 "dhcp6_parser.cc"
    break;

  case 574: // $@79: %empty
#line 2038 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3266 "dhcp6_parser.cc"
    break;

  case 575: // option_def_type: "type" $@79 ":" "constant string"
#line 2041 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3276 "dhcp6_parser.cc"
    break;

  case 576: // $@80: %empty
#line 2047 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3285 "dhcp6_parser.cc"
    break;

  case 577: // option_def_record_types: "record-types" $@80 ":" "constant string"
#line 2050 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3295 "dhcp6_parser.cc"
    break;

  case 578: // $@81: %empty
#line 2056 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3304 "dhcp6_parser.cc"
    break;

  case 579: // space: "space" $@81 ":" "constant string"
#line 2059 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3314 "dhcp6_parser.cc"
    break;

  case 581: // $@82: %empty
#line 2067 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3323 "dhcp6_parser.cc"
    break;

  case 582: // option_def_encapsulate: "encapsulate" $@82 ":" "constant string"
#line 2070 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3333 "dhcp6_parser.cc"
    break;

  case 583: // option_def_array: "array" ":" "boolean"
#line 2076 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3343 "dhcp6_parser.cc"
    break;

  case 584: // $@83: %empty
#line 2086 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3355 "dhcp6_parser.cc"
    break;

  case 585: // option_data_list: "option-data" $@83 ":" "[" option_data_list_content "]"
#line 2092 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3364 "dhcp6_parser.cc"
    break;

  case 590: // not_empty_option_data_list: not_empty_option_data_list ","
#line 2107 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3372 "dhcp6_parser.cc"
    break;

  case 591: // $@84: %empty
#line 2114 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3382 "dhcp6_parser.cc"
    break;

  case 592: // option_data_entry: "{" $@84 option_data_params "}"
#line 2118 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3391 "dhcp6_parser.cc"
    break;

  case 593: // $@85: %empty
#line 2126 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3401 "dhcp6_parser.cc"
    break;

  case 594: // sub_option_data: "{" $@85 option_data_params "}"
#line 2130 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3410 "dhcp6_parser.cc"
    break;

  case 599: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2146 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3418 "dhcp6_parser.cc"
    break;

  case 612: // $@86: %empty
#line 2168 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3427 "dhcp6_parser.cc"
    break;

  case 613: // option_data_data: "data" $@86 ":" "constant string"
#line 2171 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3437 "dhcp6_parser.cc"
    break;

  case 616: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2181 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3447 "dhcp6_parser.cc"
    break;

  case 617: // option_data_always_send: "always-send" ":" "boolean"
#line 2187 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3457 "dhcp6_parser.cc"
    break;

  case 618: // option_data_never_send: "never-send" ":" "boolean"
#line 2193 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3467 "dhcp6_parser.cc"
    break;

  case 619: // $@87: %empty
#line 2199 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3479 "dhcp6_parser.cc"
    break;

  case 620: // option_data_client_classes: "client-classes" $@87 ":" list_strings
#line 2205 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3488 "dhcp6_parser.cc"
    break;

  case 621: // $@88: %empty
#line 2213 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3500 "dhcp6_parser.cc"
    break;

  case 622: // pools_list: "pools" $@88 ":" "[" pools_list_content "]"
#line 2219 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3509 "dhcp6_parser.cc"
    break;

  case 627: // not_empty_pools_list: not_empty_pools_list ","
#line 2232 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3517 "dhcp6_parser.cc"
    break;

  case 628: // $@89: %empty
#line 2237 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3527 "dhcp6_parser.cc"
    break;

  case 629: // pool_list_entry: "{" $@89 pool_params "}"
#line 2241 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3537 "dhcp6_parser.cc"
    break;

  case 630: // $@90: %empty
#line 2247 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3547 "dhcp6_parser.cc"
    break;

  case 631: // sub_pool6: "{" $@90 pool_params "}"
#line 2251 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3557 "dhcp6_parser.cc"
    break;

  case 634: // pool_params: pool_params ","
#line 2259 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3565 "dhcp6_parser.cc"
    break;

  case 659: // $@91: %empty
#line 2290 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3574 "dhcp6_parser.cc"
    break;

  case 660: // pool_entry: "pool" $@91 ":" "constant string"
#line 2293 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3584 "dhcp6_parser.cc"
    break;

  case 661: // pool_id: "pool-id" ":" "integer"
#line 2299 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3594 "dhcp6_parser.cc"
    break;

  case 662: // $@92: %empty
#line 2305 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3602 "dhcp6_parser.cc"
    break;

  case 663: // user_context: "user-context" $@92 ":" map_value
#line 2307 "dhcp6_parser.yy"
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

  case 664: // $@93: %empty
#line 2330 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3637 "dhcp6_parser.cc"
    break;

  case 665: // comment: "comment" $@93 ":" "constant string"
#line 2332 "dhcp6_parser.yy"
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

  case 666: // $@94: %empty
#line 2360 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3678 "dhcp6_parser.cc"
    break;

  case 667: // pd_pools_list: "pd-pools" $@94 ":" "[" pd_pools_list_content "]"
#line 2366 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3687 "dhcp6_parser.cc"
    break;

  case 672: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2379 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3695 "dhcp6_parser.cc"
    break;

  case 673: // $@95: %empty
#line 2384 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3705 "dhcp6_parser.cc"
    break;

  case 674: // pd_pool_entry: "{" $@95 pd_pool_params "}"
#line 2388 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3717 "dhcp6_parser.cc"
    break;

  case 675: // $@96: %empty
#line 2396 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3727 "dhcp6_parser.cc"
    break;

  case 676: // sub_pd_pool: "{" $@96 pd_pool_params "}"
#line 2400 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3739 "dhcp6_parser.cc"
    break;

  case 679: // pd_pool_params: pd_pool_params ","
#line 2410 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3747 "dhcp6_parser.cc"
    break;

  case 694: // $@97: %empty
#line 2431 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3756 "dhcp6_parser.cc"
    break;

  case 695: // pd_prefix: "prefix" $@97 ":" "constant string"
#line 2434 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3766 "dhcp6_parser.cc"
    break;

  case 696: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2440 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3776 "dhcp6_parser.cc"
    break;

  case 697: // $@98: %empty
#line 2446 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3785 "dhcp6_parser.cc"
    break;

  case 698: // excluded_prefix: "excluded-prefix" $@98 ":" "constant string"
#line 2449 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3795 "dhcp6_parser.cc"
    break;

  case 699: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2455 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3805 "dhcp6_parser.cc"
    break;

  case 700: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2461 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3815 "dhcp6_parser.cc"
    break;

  case 701: // $@99: %empty
#line 2470 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3827 "dhcp6_parser.cc"
    break;

  case 702: // reservations: "reservations" $@99 ":" "[" reservations_list "]"
#line 2476 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3836 "dhcp6_parser.cc"
    break;

  case 707: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2487 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3844 "dhcp6_parser.cc"
    break;

  case 708: // $@100: %empty
#line 2492 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3854 "dhcp6_parser.cc"
    break;

  case 709: // reservation: "{" $@100 reservation_params "}"
#line 2496 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3863 "dhcp6_parser.cc"
    break;

  case 710: // $@101: %empty
#line 2501 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3873 "dhcp6_parser.cc"
    break;

  case 711: // sub_reservation: "{" $@101 reservation_params "}"
#line 2505 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3882 "dhcp6_parser.cc"
    break;

  case 716: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2516 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3890 "dhcp6_parser.cc"
    break;

  case 729: // $@102: %empty
#line 2536 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3902 "dhcp6_parser.cc"
    break;

  case 730: // ip_addresses: "ip-addresses" $@102 ":" list_strings
#line 2542 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3911 "dhcp6_parser.cc"
    break;

  case 731: // $@103: %empty
#line 2547 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3923 "dhcp6_parser.cc"
    break;

  case 732: // prefixes: "prefixes" $@103 ":" list_strings
#line 2553 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3932 "dhcp6_parser.cc"
    break;

  case 733: // $@104: %empty
#line 2558 "dhcp6_parser.yy"
                                     {
    ctx.unique("excluded-prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3944 "dhcp6_parser.cc"
    break;

  case 734: // excluded_prefixes: "excluded-prefixes" $@104 ":" list_strings
#line 2564 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3953 "dhcp6_parser.cc"
    break;

  case 735: // $@105: %empty
#line 2569 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3962 "dhcp6_parser.cc"
    break;

  case 736: // duid: "duid" $@105 ":" "constant string"
#line 2572 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3972 "dhcp6_parser.cc"
    break;

  case 737: // $@106: %empty
#line 2578 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3981 "dhcp6_parser.cc"
    break;

  case 738: // hw_address: "hw-address" $@106 ":" "constant string"
#line 2581 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3991 "dhcp6_parser.cc"
    break;

  case 739: // $@107: %empty
#line 2587 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4000 "dhcp6_parser.cc"
    break;

  case 740: // hostname: "hostname" $@107 ":" "constant string"
#line 2590 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 4010 "dhcp6_parser.cc"
    break;

  case 741: // $@108: %empty
#line 2596 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4019 "dhcp6_parser.cc"
    break;

  case 742: // flex_id_value: "flex-id" $@108 ":" "constant string"
#line 2599 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 4029 "dhcp6_parser.cc"
    break;

  case 743: // $@109: %empty
#line 2605 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4041 "dhcp6_parser.cc"
    break;

  case 744: // reservation_client_classes: "client-classes" $@109 ":" list_strings
#line 2611 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4050 "dhcp6_parser.cc"
    break;

  case 745: // $@110: %empty
#line 2619 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 4062 "dhcp6_parser.cc"
    break;

  case 746: // relay: "relay" $@110 ":" "{" relay_map "}"
#line 2625 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4071 "dhcp6_parser.cc"
    break;

  case 748: // $@111: %empty
#line 2636 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 4083 "dhcp6_parser.cc"
    break;

  case 749: // client_classes: "client-classes" $@111 ":" "[" client_classes_list "]"
#line 2642 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4092 "dhcp6_parser.cc"
    break;

  case 754: // not_empty_classes_list: not_empty_classes_list ","
#line 2653 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4100 "dhcp6_parser.cc"
    break;

  case 755: // $@112: %empty
#line 2658 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4110 "dhcp6_parser.cc"
    break;

  case 756: // client_class_entry: "{" $@112 client_class_params "}"
#line 2662 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 4120 "dhcp6_parser.cc"
    break;

  case 761: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2674 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 4128 "dhcp6_parser.cc"
    break;

  case 778: // $@113: %empty
#line 2698 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4137 "dhcp6_parser.cc"
    break;

  case 779: // client_class_test: "test" $@113 ":" "constant string"
#line 2701 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 4147 "dhcp6_parser.cc"
    break;

  case 780: // $@114: %empty
#line 2707 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4156 "dhcp6_parser.cc"
    break;

  case 781: // client_class_template_test: "template-test" $@114 ":" "constant string"
#line 2710 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 4166 "dhcp6_parser.cc"
    break;

  case 782: // only_if_required: "only-if-required" ":" "boolean"
#line 2717 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4176 "dhcp6_parser.cc"
    break;

  case 783: // only_in_additional_list: "only-in-additional-list" ":" "boolean"
#line 2723 "dhcp6_parser.yy"
                                                               {
    ctx.unique("only-in-additional-list", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-in-additional-list", b);
}
#line 4186 "dhcp6_parser.cc"
    break;

  case 784: // $@115: %empty
#line 2732 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 4198 "dhcp6_parser.cc"
    break;

  case 785: // server_id: "server-id" $@115 ":" "{" server_id_params "}"
#line 2738 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4209 "dhcp6_parser.cc"
    break;

  case 788: // server_id_params: server_id_params ","
#line 2747 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4217 "dhcp6_parser.cc"
    break;

  case 798: // $@116: %empty
#line 2763 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 4226 "dhcp6_parser.cc"
    break;

  case 799: // server_id_type: "type" $@116 ":" duid_type
#line 2766 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4235 "dhcp6_parser.cc"
    break;

  case 800: // duid_type: "LLT"
#line 2771 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4241 "dhcp6_parser.cc"
    break;

  case 801: // duid_type: "EN"
#line 2772 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4247 "dhcp6_parser.cc"
    break;

  case 802: // duid_type: "LL"
#line 2773 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4253 "dhcp6_parser.cc"
    break;

  case 803: // htype: "htype" ":" "integer"
#line 2776 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4263 "dhcp6_parser.cc"
    break;

  case 804: // $@117: %empty
#line 2782 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4272 "dhcp6_parser.cc"
    break;

  case 805: // identifier: "identifier" $@117 ":" "constant string"
#line 2785 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4282 "dhcp6_parser.cc"
    break;

  case 806: // time: "time" ":" "integer"
#line 2791 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4292 "dhcp6_parser.cc"
    break;

  case 807: // enterprise_id: "enterprise-id" ":" "integer"
#line 2797 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4302 "dhcp6_parser.cc"
    break;

  case 808: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2805 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4312 "dhcp6_parser.cc"
    break;

  case 809: // $@118: %empty
#line 2813 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4325 "dhcp6_parser.cc"
    break;

  case 810: // control_socket: "control-socket" $@118 ":" "{" control_socket_params "}"
#line 2820 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4334 "dhcp6_parser.cc"
    break;

  case 811: // $@119: %empty
#line 2825 "dhcp6_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4347 "dhcp6_parser.cc"
    break;

  case 812: // control_sockets: "control-sockets" $@119 ":" "[" control_socket_list "]"
#line 2832 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4356 "dhcp6_parser.cc"
    break;

  case 817: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2843 "dhcp6_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4364 "dhcp6_parser.cc"
    break;

  case 818: // $@120: %empty
#line 2848 "dhcp6_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4374 "dhcp6_parser.cc"
    break;

  case 819: // control_socket_entry: "{" $@120 control_socket_params "}"
#line 2852 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4382 "dhcp6_parser.cc"
    break;

  case 822: // control_socket_params: control_socket_params ","
#line 2858 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4390 "dhcp6_parser.cc"
    break;

  case 836: // $@121: %empty
#line 2878 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4399 "dhcp6_parser.cc"
    break;

  case 837: // control_socket_type: "socket-type" $@121 ":" control_socket_type_value
#line 2881 "dhcp6_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4408 "dhcp6_parser.cc"
    break;

  case 838: // control_socket_type_value: "unix"
#line 2887 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4414 "dhcp6_parser.cc"
    break;

  case 839: // control_socket_type_value: "http"
#line 2888 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4420 "dhcp6_parser.cc"
    break;

  case 840: // control_socket_type_value: "https"
#line 2889 "dhcp6_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4426 "dhcp6_parser.cc"
    break;

  case 841: // $@122: %empty
#line 2892 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4435 "dhcp6_parser.cc"
    break;

  case 842: // control_socket_name: "socket-name" $@122 ":" "constant string"
#line 2895 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4445 "dhcp6_parser.cc"
    break;

  case 843: // $@123: %empty
#line 2901 "dhcp6_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4454 "dhcp6_parser.cc"
    break;

  case 844: // control_socket_address: "socket-address" $@123 ":" "constant string"
#line 2904 "dhcp6_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4464 "dhcp6_parser.cc"
    break;

  case 845: // control_socket_port: "socket-port" ":" "integer"
#line 2910 "dhcp6_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4474 "dhcp6_parser.cc"
    break;

  case 846: // cert_required: "cert-required" ":" "boolean"
#line 2916 "dhcp6_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4484 "dhcp6_parser.cc"
    break;

  case 847: // $@124: %empty
#line 2922 "dhcp6_parser.yy"
                           {
    ctx.unique("http-headers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("http-headers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HTTP_HEADERS);
}
#line 4496 "dhcp6_parser.cc"
    break;

  case 848: // http_headers: "http-headers" $@124 ":" "[" http_header_list "]"
#line 2928 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4505 "dhcp6_parser.cc"
    break;

  case 853: // not_empty_http_header_list: not_empty_http_header_list ","
#line 2939 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 4513 "dhcp6_parser.cc"
    break;

  case 854: // $@125: %empty
#line 2944 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4523 "dhcp6_parser.cc"
    break;

  case 855: // http_header: "{" $@125 http_header_params "}"
#line 2948 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4531 "dhcp6_parser.cc"
    break;

  case 858: // http_header_params: http_header_params ","
#line 2954 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4539 "dhcp6_parser.cc"
    break;

  case 864: // $@126: %empty
#line 2966 "dhcp6_parser.yy"
                    {
    ctx.unique("value", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4548 "dhcp6_parser.cc"
    break;

  case 865: // header_value: "value" $@126 ":" "constant string"
#line 2969 "dhcp6_parser.yy"
               {
    ElementPtr value(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("value", value);
    ctx.leave();
}
#line 4558 "dhcp6_parser.cc"
    break;

  case 866: // $@127: %empty
#line 2977 "dhcp6_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4570 "dhcp6_parser.cc"
    break;

  case 867: // authentication: "authentication" $@127 ":" "{" auth_params "}"
#line 2983 "dhcp6_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4581 "dhcp6_parser.cc"
    break;

  case 870: // auth_params: auth_params ","
#line 2992 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4589 "dhcp6_parser.cc"
    break;

  case 878: // $@128: %empty
#line 3006 "dhcp6_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4598 "dhcp6_parser.cc"
    break;

  case 879: // auth_type: "type" $@128 ":" auth_type_value
#line 3009 "dhcp6_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4607 "dhcp6_parser.cc"
    break;

  case 880: // auth_type_value: "basic"
#line 3014 "dhcp6_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4613 "dhcp6_parser.cc"
    break;

  case 881: // $@129: %empty
#line 3017 "dhcp6_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4622 "dhcp6_parser.cc"
    break;

  case 882: // realm: "realm" $@129 ":" "constant string"
#line 3020 "dhcp6_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4632 "dhcp6_parser.cc"
    break;

  case 883: // $@130: %empty
#line 3026 "dhcp6_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4641 "dhcp6_parser.cc"
    break;

  case 884: // directory: "directory" $@130 ":" "constant string"
#line 3029 "dhcp6_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4651 "dhcp6_parser.cc"
    break;

  case 885: // $@131: %empty
#line 3035 "dhcp6_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4663 "dhcp6_parser.cc"
    break;

  case 886: // clients: "clients" $@131 ":" "[" clients_list "]"
#line 3041 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4672 "dhcp6_parser.cc"
    break;

  case 891: // not_empty_clients_list: not_empty_clients_list ","
#line 3052 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4680 "dhcp6_parser.cc"
    break;

  case 892: // $@132: %empty
#line 3057 "dhcp6_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4690 "dhcp6_parser.cc"
    break;

  case 893: // basic_auth: "{" $@132 clients_params "}"
#line 3061 "dhcp6_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4698 "dhcp6_parser.cc"
    break;

  case 896: // clients_params: clients_params ","
#line 3067 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4706 "dhcp6_parser.cc"
    break;

  case 904: // $@133: %empty
#line 3081 "dhcp6_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4715 "dhcp6_parser.cc"
    break;

  case 905: // user_file: "user-file" $@133 ":" "constant string"
#line 3084 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4725 "dhcp6_parser.cc"
    break;

  case 906: // $@134: %empty
#line 3092 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4737 "dhcp6_parser.cc"
    break;

  case 907: // dhcp_queue_control: "dhcp-queue-control" $@134 ":" "{" queue_control_params "}"
#line 3098 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4748 "dhcp6_parser.cc"
    break;

  case 910: // queue_control_params: queue_control_params ","
#line 3107 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4756 "dhcp6_parser.cc"
    break;

  case 917: // enable_queue: "enable-queue" ":" "boolean"
#line 3120 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4766 "dhcp6_parser.cc"
    break;

  case 918: // $@135: %empty
#line 3126 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4775 "dhcp6_parser.cc"
    break;

  case 919: // queue_type: "queue-type" $@135 ":" "constant string"
#line 3129 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4785 "dhcp6_parser.cc"
    break;

  case 920: // capacity: "capacity" ":" "integer"
#line 3135 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4795 "dhcp6_parser.cc"
    break;

  case 921: // $@136: %empty
#line 3141 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4804 "dhcp6_parser.cc"
    break;

  case 922: // arbitrary_map_entry: "constant string" $@136 ":" value
#line 3144 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4813 "dhcp6_parser.cc"
    break;

  case 923: // $@137: %empty
#line 3151 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4825 "dhcp6_parser.cc"
    break;

  case 924: // dhcp_ddns: "dhcp-ddns" $@137 ":" "{" dhcp_ddns_params "}"
#line 3157 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4836 "dhcp6_parser.cc"
    break;

  case 925: // $@138: %empty
#line 3164 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4846 "dhcp6_parser.cc"
    break;

  case 926: // sub_dhcp_ddns: "{" $@138 dhcp_ddns_params "}"
#line 3168 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4856 "dhcp6_parser.cc"
    break;

  case 929: // dhcp_ddns_params: dhcp_ddns_params ","
#line 3176 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4864 "dhcp6_parser.cc"
    break;

  case 941: // enable_updates: "enable-updates" ":" "boolean"
#line 3194 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4874 "dhcp6_parser.cc"
    break;

  case 942: // $@139: %empty
#line 3200 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4883 "dhcp6_parser.cc"
    break;

  case 943: // server_ip: "server-ip" $@139 ":" "constant string"
#line 3203 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4893 "dhcp6_parser.cc"
    break;

  case 944: // server_port: "server-port" ":" "integer"
#line 3209 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4903 "dhcp6_parser.cc"
    break;

  case 945: // $@140: %empty
#line 3215 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4912 "dhcp6_parser.cc"
    break;

  case 946: // sender_ip: "sender-ip" $@140 ":" "constant string"
#line 3218 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4922 "dhcp6_parser.cc"
    break;

  case 947: // sender_port: "sender-port" ":" "integer"
#line 3224 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4932 "dhcp6_parser.cc"
    break;

  case 948: // max_queue_size: "max-queue-size" ":" "integer"
#line 3230 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4942 "dhcp6_parser.cc"
    break;

  case 949: // $@141: %empty
#line 3236 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4951 "dhcp6_parser.cc"
    break;

  case 950: // ncr_protocol: "ncr-protocol" $@141 ":" ncr_protocol_value
#line 3239 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4960 "dhcp6_parser.cc"
    break;

  case 951: // ncr_protocol_value: "UDP"
#line 3245 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4966 "dhcp6_parser.cc"
    break;

  case 952: // ncr_protocol_value: "TCP"
#line 3246 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4972 "dhcp6_parser.cc"
    break;

  case 953: // $@142: %empty
#line 3249 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4981 "dhcp6_parser.cc"
    break;

  case 954: // ncr_format: "ncr-format" $@142 ":" "JSON"
#line 3252 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4991 "dhcp6_parser.cc"
    break;

  case 955: // $@143: %empty
#line 3260 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 5003 "dhcp6_parser.cc"
    break;

  case 956: // config_control: "config-control" $@143 ":" "{" config_control_params "}"
#line 3266 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5013 "dhcp6_parser.cc"
    break;

  case 957: // $@144: %empty
#line 3272 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 5023 "dhcp6_parser.cc"
    break;

  case 958: // sub_config_control: "{" $@144 config_control_params "}"
#line 3276 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 5032 "dhcp6_parser.cc"
    break;

  case 961: // config_control_params: config_control_params ","
#line 3284 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 5040 "dhcp6_parser.cc"
    break;

  case 964: // $@145: %empty
#line 3294 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 5052 "dhcp6_parser.cc"
    break;

  case 965: // config_databases: "config-databases" $@145 ":" "[" database_list "]"
#line 3300 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5061 "dhcp6_parser.cc"
    break;

  case 966: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3305 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 5071 "dhcp6_parser.cc"
    break;

  case 967: // $@146: %empty
#line 3313 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 5083 "dhcp6_parser.cc"
    break;

  case 968: // loggers: "loggers" $@146 ":" "[" loggers_entries "]"
#line 3319 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5092 "dhcp6_parser.cc"
    break;

  case 971: // loggers_entries: loggers_entries ","
#line 3328 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 5100 "dhcp6_parser.cc"
    break;

  case 972: // $@147: %empty
#line 3334 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 5110 "dhcp6_parser.cc"
    break;

  case 973: // logger_entry: "{" $@147 logger_params "}"
#line 3338 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 5118 "dhcp6_parser.cc"
    break;

  case 976: // logger_params: logger_params ","
#line 3344 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 5126 "dhcp6_parser.cc"
    break;

  case 984: // debuglevel: "debuglevel" ":" "integer"
#line 3358 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 5136 "dhcp6_parser.cc"
    break;

  case 985: // $@148: %empty
#line 3364 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5145 "dhcp6_parser.cc"
    break;

  case 986: // severity: "severity" $@148 ":" "constant string"
#line 3367 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 5155 "dhcp6_parser.cc"
    break;

  case 987: // $@149: %empty
#line 3373 "dhcp6_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 5167 "dhcp6_parser.cc"
    break;

  case 988: // output_options_list: "output-options" $@149 ":" "[" output_options_list_content "]"
#line 3379 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5176 "dhcp6_parser.cc"
    break;

  case 991: // output_options_list_content: output_options_list_content ","
#line 3386 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 5184 "dhcp6_parser.cc"
    break;

  case 992: // $@150: %empty
#line 3391 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 5194 "dhcp6_parser.cc"
    break;

  case 993: // output_entry: "{" $@150 output_params_list "}"
#line 3395 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 5202 "dhcp6_parser.cc"
    break;

  case 996: // output_params_list: output_params_list ","
#line 3401 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 5210 "dhcp6_parser.cc"
    break;

  case 1002: // $@151: %empty
#line 3413 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5219 "dhcp6_parser.cc"
    break;

  case 1003: // output: "output" $@151 ":" "constant string"
#line 3416 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 5229 "dhcp6_parser.cc"
    break;

  case 1004: // flush: "flush" ":" "boolean"
#line 3422 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5239 "dhcp6_parser.cc"
    break;

  case 1005: // maxsize: "maxsize" ":" "integer"
#line 3428 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5249 "dhcp6_parser.cc"
    break;

  case 1006: // maxver: "maxver" ":" "integer"
#line 3434 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5259 "dhcp6_parser.cc"
    break;

  case 1007: // $@152: %empty
#line 3440 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5268 "dhcp6_parser.cc"
    break;

  case 1008: // pattern: "pattern" $@152 ":" "constant string"
#line 3443 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5278 "dhcp6_parser.cc"
    break;

  case 1009: // $@153: %empty
#line 3449 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5290 "dhcp6_parser.cc"
    break;

  case 1010: // compatibility: "compatibility" $@153 ":" "{" compatibility_params "}"
#line 3455 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5299 "dhcp6_parser.cc"
    break;

  case 1013: // compatibility_params: compatibility_params ","
#line 3462 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5307 "dhcp6_parser.cc"
    break;

  case 1016: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3471 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5317 "dhcp6_parser.cc"
    break;


#line 5321 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1468;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     683, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468,    91,    29,    36,    77,    96,
     115,   147,   155,   159,   167,   175,   190,   192,   229,   273,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,    29,  -118,
     224,   183,    43,   751,   643,   652,   246,   214,   112,   390,
     -77,   704,    51, -1468,   295,   316,   324,   312,   341, -1468,
      50, -1468, -1468, -1468, -1468, -1468, -1468, -1468,   349,   353,
     355,   359,   365,   382,   412,   428,   445,   446,   467,   468,
     470,   483,   485, -1468,   487,   488,   504,   505,   506, -1468,
   -1468, -1468,   508,   509,   515,   518,   523,   524,   526, -1468,
   -1468, -1468,   527, -1468, -1468, -1468, -1468, -1468, -1468,   529,
     530,   534, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468,   539, -1468, -1468, -1468, -1468, -1468, -1468, -1468,   541,
     543,   544,   546, -1468, -1468,   552, -1468,    73, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468,   553,   560,   562,   563, -1468,   120, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468,   564,   565, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468,   143, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468,   566, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468,   144, -1468, -1468, -1468, -1468,
   -1468, -1468,   568, -1468,   569,   571, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468,   145, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468,   338,   574, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468,   572, -1468, -1468,   575, -1468,
   -1468, -1468,   577, -1468, -1468,   580,   582, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
     579,   585,   587, -1468, -1468, -1468, -1468, -1468,   584,   592,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468,   168, -1468, -1468, -1468,   595, -1468,
     596, -1468,   597,   599, -1468, -1468, -1468, -1468, -1468,   169,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
     600,   193, -1468, -1468, -1468, -1468,    29,    29, -1468,   354,
     603, -1468, -1468,   604,   606,   607,   609,   610,   611,   374,
     375,   378,   379,   380,   383,   384,   402,   388,   381,   385,
     397,   413,   411,   420,   615,   421,   424,   426,   429,   430,
     653,   655,   664,   431,   432,   435,   427,   438,   439,   442,
     665,   684,   685,   447,   688,   690,   692,   693,   697,   699,
     459,   460,   463,   703,   705,   707,   708,   710,   718,   723,
     724,   725,   489,   727,   729,   730,   731,   732,   733,   734,
     495,   496,   497,   498,   741,   742, -1468,   183, -1468,   743,
     507,   510,   511,   513,    43, -1468,   757,   765,   767,   768,
     769,   535,   532,   775,   776,   782,   783,   784,   751, -1468,
     785,   549,   643, -1468,   789,   551,   794,   558,   559,   652,
   -1468,   799,   817,   818,   832,   833,   838,   841,   842, -1468,
     246, -1468,   843,   844,   613,   845,   849,   853,   614, -1468,
     112,   857,   617,   618,   619,   861, -1468,   390,   882,   883,
      39, -1468,   645,   884,   649,   889,   654,   682,   891,   892,
     704, -1468,   894,   686,    51, -1468, -1468, -1468,   904,   919,
     689,   920,   921,   923,   925,   928, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468,   694, -1468, -1468, -1468, -1468, -1468,  -120,   698,   700,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468,   929,   930,   934,
   -1468,   701,   702,   392,   936,   938,   706, -1468, -1468, -1468,
     942,   944,   945,   946,   947,   949,   950,   953,   954, -1468,
     957,   958,   961,   960,   962,   709,   726, -1468, -1468, -1468,
   -1468,   965,   964, -1468,   967, -1468, -1468, -1468, -1468, -1468,
     968,   969,   735,   736,   737, -1468, -1468,   967,   967,   967,
     738,   974, -1468,   740, -1468, -1468,   744, -1468,   745, -1468,
   -1468, -1468,   967,   967,   967,   967,   746,   747,   748,   749,
   -1468,   750,   752, -1468,   753,   754,   755, -1468, -1468,   756,
   -1468, -1468, -1468,   967, -1468,   758,   938, -1468, -1468,   759,
   -1468,   760, -1468, -1468,  -125,   770, -1468,   970, -1468, -1468,
      29,   183, -1468,    51,    43,   410,   410,   976, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468,   977,   978,   992,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468,   996, -1468, -1468,
   -1468,  -109,    29,   238,    93,   997,   998,   999,   -40,    54,
     160,   233,  1000,   110,   704, -1468, -1468,  1001,  -186, -1468,
   -1468,  1002,  1003, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
     870, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468,   976, -1468,   213,
     221,   227, -1468, -1468, -1468, -1468,  1008,  1009,  1010,  1011,
    1012,  1013,  1014,  1015,  1016,  1017, -1468,  1018,  1019, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468,   309, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468,   310, -1468,  1020,
    1021, -1468, -1468,  1022,  1024, -1468, -1468,  1023,  1027, -1468,
   -1468,  1025,  1029, -1468, -1468,  1028,  1030, -1468, -1468, -1468,
      99, -1468, -1468, -1468,  1031, -1468, -1468, -1468,   331, -1468,
   -1468, -1468, -1468, -1468,   318, -1468, -1468, -1468, -1468,  1032,
    1033, -1468, -1468,  1034,  1036, -1468, -1468,  1037,  1039, -1468,
    1041,  1042,  1044,  1047,  1055,  1057,   319, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468,  1068,  1069,  1070, -1468,
   -1468, -1468, -1468,   333, -1468, -1468, -1468, -1468, -1468, -1468,
    1073,  1078,  1082, -1468,   335, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468,  1083, -1468,  1086, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468,   337, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468,  1087,  1092, -1468,  1095, -1468,  1097,
   -1468, -1468, -1468,   357, -1468, -1468, -1468, -1468, -1468,   364,
   -1468,   398, -1468,  1098, -1468,   372, -1468, -1468,   793, -1468,
    1090,  1100, -1468, -1468,  1099,  1103, -1468, -1468,  1105,  1112,
   -1468, -1468, -1468,  1107,  1116,  1119,  1122,   885,   780,   897,
     898,   901,   907,   908,   909,   916,   941,  1123,   917,   979,
    1130,  1159,  1167,  1168,  1189,  1207,   410, -1468, -1468,   410,
   -1468,   976,   751, -1468,   977,   112, -1468,   978,   390, -1468,
     992,  1461, -1468,   996,  -109, -1468, -1468,   238, -1468,  1221,
    1227,    93, -1468,   822, -1468,   997,   246, -1468,   998,   -77,
   -1468,   999,   990,   994,  1004,  1006,  1007,  1026,   -40, -1468,
    1231,  1235,  1035,  1038,  1040,    54, -1468,   995,  1043,  1045,
     160, -1468,  1237,  1238,  1240,  1046,  1241,  1048,  1248,   233,
   -1468,   233, -1468,  1000,  1049,  1249,  1052,  1251,   110, -1468,
   -1468,   209,  1001, -1468,  1051,  -186, -1468, -1468,  1252,  1254,
     643, -1468,  1002,   652, -1468,  1003, -1468, -1468,  1050,  1056,
    1058,  1063, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468,   247, -1468, -1468,  1066,  1067,  1071,   163,  1072,
    1074, -1468,   373, -1468,   376, -1468,  1255, -1468,  1256, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468,   400, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468,  1075,  1076, -1468, -1468, -1468,  1258,
    1261, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468,  1259,  1257, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468,  1260, -1468,   407, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468,   342,  1077, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468,   386,  1079,  1080, -1468,  1263, -1468,  1266, -1468,
     415, -1468, -1468,  1081, -1468,    29, -1468, -1468,  1268, -1468,
   -1468, -1468, -1468, -1468,   416, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468,  1084,   423, -1468,   425, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468,  1461, -1468, -1468, -1468,
    1269,  1270,  1085,  1088, -1468,   822, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,    48,
    1272, -1468, -1468, -1468,  1271,  1054,  1273,   209, -1468, -1468,
   -1468, -1468, -1468,  1094,  1106, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468,   461, -1468, -1468, -1468, -1468,
   -1468, -1468,  1274,  1279, -1468,  1280, -1468,  1110, -1468, -1468,
   -1468,  1283,  1286,  1287,  1307,    48, -1468,   -49, -1468,  1272,
    1277, -1468,  1143,  1111,  1113,  1322, -1468, -1468, -1468, -1468,
   -1468, -1468,   462, -1468, -1468, -1468, -1468,   414, -1468, -1468,
   -1468, -1468, -1468,  1305,  1328,   -49, -1468,  -113,  1277, -1468,
   -1468,  1333,  1338, -1468,  1114, -1468, -1468,  1343,  1345,  1350,
   -1468,   465, -1468, -1468, -1468, -1468, -1468, -1468, -1468,   290,
   -1468,  1305, -1468,  1354,  1115,  1118,  1120,  1355,  -113, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468,   482, -1468, -1468,
   -1468,  1125, -1468, -1468, -1468,  1126, -1468,  1360,   290, -1468,
   -1468, -1468,  1127, -1468, -1468
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   209,     9,   406,    11,
     630,    13,   675,    15,   710,    17,   545,    19,   554,    21,
     593,    23,   368,    25,   925,    27,   957,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   712,     0,   556,   595,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   146,   955,   207,   228,   230,   232,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   196,     0,     0,     0,     0,     0,   166,
     173,   175,     0,     0,     0,     0,     0,     0,     0,   397,
     543,   584,     0,   199,   201,   179,   482,   662,   664,     0,
       0,     0,   324,   343,   333,   313,   748,   701,   359,   380,
     784,     0,   345,   809,   811,   906,   923,   189,   191,     0,
       0,     0,     0,   967,  1009,     0,   145,     0,    69,    72,
      73,    74,    75,    76,    77,    78,    79,    80,   111,   112,
     113,   114,   115,   116,    81,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   118,   119,
     133,   134,   135,   107,   142,   143,   144,   137,   138,   139,
     140,    84,    85,    86,    87,   104,    88,    90,    89,   136,
      94,    95,    82,   108,   109,   110,    83,    92,    93,   102,
     103,   105,    91,    96,    97,    98,    99,   100,   101,   106,
     117,   141,   222,     0,     0,     0,     0,   221,     0,   211,
     214,   215,   216,   217,   218,   219,   220,   621,   666,   463,
     465,   467,     0,     0,   471,   473,   475,   469,   745,   462,
     411,   412,   413,   414,   415,   416,   417,   418,   438,   439,
     440,   441,   442,   443,   446,   447,   448,   449,   450,   451,
     452,   453,   454,   455,   456,   457,   458,   444,   445,   459,
     460,   461,     0,   408,   422,   423,   424,   427,   428,   429,
     430,   432,   433,   434,   425,   426,   419,   420,   436,   437,
     421,   431,   435,   659,     0,   658,   642,   643,   644,   645,
     646,   647,   648,   649,   650,   651,   652,   653,   654,   655,
     638,   639,   640,   641,   637,     0,   632,   635,   636,   656,
     657,   694,     0,   697,     0,     0,   693,   685,   686,   687,
     688,   684,   683,   691,   692,     0,   677,   680,   681,   689,
     690,   682,   743,   729,   731,   733,   735,   737,   739,   741,
     728,   725,   726,   727,     0,   713,   714,   719,   720,   721,
     717,   722,   723,   724,   718,     0,   574,   280,     0,   578,
     576,   581,     0,   570,   571,     0,   557,   558,   561,   573,
     562,   563,   564,   580,   565,   566,   567,   568,   569,   612,
       0,     0,     0,   619,   610,   611,   614,   615,     0,   596,
     597,   600,   601,   602,   603,   604,   605,   606,   609,   607,
     608,   376,   378,   373,     0,   370,   374,   375,     0,   942,
       0,   945,     0,     0,   949,   953,   940,   938,   939,     0,
     927,   930,   931,   932,   933,   934,   935,   936,   937,   964,
       0,     0,   959,   962,   963,    47,    52,     0,    39,    45,
       0,    66,    62,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    60,    71,    68,     0,
       0,     0,     0,     0,   213,   210,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   410,   407,
       0,     0,   634,   631,     0,     0,     0,     0,     0,   679,
     676,     0,     0,     0,     0,     0,     0,     0,     0,   711,
     716,   546,     0,     0,     0,     0,     0,     0,     0,   555,
     560,     0,     0,     0,     0,     0,   594,   599,     0,     0,
     372,   369,     0,     0,     0,     0,     0,     0,     0,     0,
     929,   926,     0,     0,   961,   958,    51,    43,     0,     0,
       0,     0,     0,     0,     0,     0,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,     0,   194,   195,   163,   164,   165,     0,     0,     0,
     177,   178,   185,   186,   187,   188,   193,     0,     0,     0,
     198,     0,     0,     0,     0,     0,     0,   477,   478,   479,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   808,
       0,     0,     0,     0,     0,     0,     0,   203,   204,   205,
     206,     0,     0,    70,     0,   224,   225,   226,   227,   212,
       0,     0,     0,     0,     0,   480,   481,     0,     0,     0,
       0,     0,   409,     0,   661,   633,     0,   696,     0,   699,
     700,   678,     0,     0,     0,     0,     0,     0,     0,     0,
     715,     0,     0,   572,     0,     0,     0,   583,   559,     0,
     616,   617,   618,     0,   598,     0,     0,   371,   941,     0,
     944,     0,   947,   948,     0,     0,   928,     0,   966,   960,
       0,     0,   147,     0,     0,     0,     0,   234,   197,   168,
     169,   170,   171,   172,   167,   174,   176,   399,   547,   586,
     200,   202,   181,   182,   183,   184,   180,   484,    40,   663,
     665,     0,    48,     0,     0,   750,   703,   361,     0,     0,
       0,     0,   813,     0,     0,   190,   192,     0,     0,    53,
     223,   623,   668,   464,   466,   468,   472,   474,   476,   470,
       0,   660,   695,   698,   744,   730,   732,   734,   736,   738,
     740,   742,   575,   281,   579,   577,   582,   613,   620,   377,
     379,   943,   946,   951,   952,   950,   954,   234,    44,     0,
       0,     0,   269,   271,   273,   277,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   290,     0,     0,   298,
     300,   302,   304,   306,   307,   308,   309,   310,   311,   275,
     268,     0,   241,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   259,   260,   261,
     262,   258,   263,   264,   265,   266,   267,     0,   239,     0,
     235,   236,   404,     0,   400,   401,   552,     0,   548,   549,
     591,     0,   587,   588,   489,     0,   485,   486,   331,   332,
       0,   326,   329,   330,     0,   341,   342,   338,     0,   335,
     339,   340,   320,   322,     0,   315,   318,   319,   755,     0,
     751,   752,   708,     0,   704,   705,   366,     0,   362,   363,
       0,     0,     0,     0,     0,     0,     0,   382,   385,   386,
     387,   388,   389,   390,   798,   804,     0,     0,     0,   797,
     794,   795,   796,     0,   786,   789,   792,   790,   791,   793,
       0,     0,     0,   355,     0,   347,   350,   351,   352,   353,
     354,   836,   841,   843,     0,   866,     0,   847,   835,   828,
     829,   830,   833,   834,     0,   820,   823,   824,   825,   826,
     831,   832,   827,   818,     0,   814,   815,     0,   918,     0,
     921,   914,   915,     0,   908,   911,   912,   913,   916,     0,
     972,     0,   969,     0,  1015,     0,  1011,  1014,    55,   628,
       0,   624,   625,   673,     0,   669,   670,   747,     0,     0,
      64,   956,   208,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   243,   229,   231,     0,
     233,   238,     0,   398,   403,   556,   544,   551,   595,   585,
     590,     0,   483,   488,   328,   325,   344,   337,   334,     0,
       0,   317,   314,   757,   749,   754,   712,   702,   707,     0,
     360,   365,     0,     0,     0,     0,     0,     0,   384,   381,
       0,     0,     0,     0,     0,   788,   785,     0,     0,     0,
     349,   346,     0,     0,     0,     0,     0,     0,     0,   822,
     810,     0,   812,   817,     0,     0,     0,     0,   910,   907,
     924,     0,   971,   968,     0,  1013,  1010,    57,     0,    56,
       0,   622,   627,     0,   667,   672,   746,   965,     0,     0,
       0,     0,   279,   282,   283,   284,   285,   286,   287,   288,
     297,   289,     0,   295,   296,     0,     0,     0,     0,     0,
       0,   242,     0,   237,     0,   402,     0,   550,     0,   589,
     542,   509,   510,   511,   513,   514,   515,   498,   499,   518,
     519,   520,   521,   522,   523,   526,   527,   528,   529,   530,
     531,   532,   533,   534,   535,   536,   537,   538,   524,   525,
     539,   540,   541,   494,   495,   496,   497,   505,   506,   507,
     508,   502,   503,   504,   512,     0,   491,   500,   516,   517,
     501,   487,   327,   336,     0,     0,   316,   778,   780,     0,
       0,   776,   770,   771,   772,   773,   774,   775,   777,   767,
     768,   769,     0,   758,   759,   762,   763,   764,   765,   766,
     753,     0,   706,     0,   364,   391,   392,   393,   394,   395,
     396,   383,     0,     0,   803,   806,   807,   787,   356,   357,
     358,   348,     0,     0,     0,   845,     0,   846,     0,   821,
       0,   816,   917,     0,   920,     0,   909,   987,     0,   985,
     983,   977,   981,   982,     0,   974,   979,   980,   978,   970,
    1016,  1012,    54,    59,     0,   626,     0,   671,   270,   272,
     274,   278,   292,   293,   294,   291,   299,   301,   303,   305,
     312,   276,   240,   405,   553,   592,   493,   490,   321,   323,
       0,     0,     0,     0,   756,   761,   709,   367,   800,   801,
     802,   799,   805,   838,   839,   840,   837,   842,   844,     0,
     849,   819,   919,   922,     0,     0,     0,   976,   973,    58,
     629,   674,   492,     0,     0,   782,   783,   760,   878,   881,
     883,   885,   877,   876,   875,     0,   868,   871,   872,   873,
     874,   854,     0,   850,   851,     0,   984,     0,   975,   779,
     781,     0,     0,     0,     0,   870,   867,     0,   848,   853,
       0,   986,     0,     0,     0,     0,   869,   864,   863,   859,
     861,   862,     0,   856,   860,   852,   992,     0,   989,   880,
     879,   882,   884,   887,     0,   858,   855,     0,   991,   988,
     892,     0,   888,   889,     0,   857,  1002,     0,     0,     0,
    1007,     0,   994,   997,   998,   999,  1000,  1001,   990,     0,
     886,   891,   865,     0,     0,     0,     0,     0,   996,   993,
     904,   903,   897,   899,   900,   901,   902,     0,   894,   898,
     890,     0,  1004,  1005,  1006,     0,   995,     0,   896,   893,
    1003,  1008,     0,   895,   905
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468,   -10, -1468,  -645, -1468,
     576, -1468, -1468, -1468, -1468,   464, -1468,  -228, -1468, -1468,
   -1468,   -71, -1468, -1468, -1468, -1468, -1468, -1468, -1468,   589,
     808, -1468, -1468,   -58,   -55,   -52,     4,     9,    27,   -42,
     -36,    82,    83,    84,    87,    88,    94, -1468,   -41,    -4,
      12,    34, -1468, -1468,    46, -1468,    53, -1468,    56,    95,
      58, -1468, -1468,    61,    64,    66,    69,    71, -1468,    76,
   -1468,   100, -1468, -1468, -1468, -1468, -1468,   102, -1468,   105,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,   588,
     809, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468,   512, -1468,   263, -1468,  -762,   269, -1468,
   -1468, -1467, -1468, -1441, -1468, -1434, -1468, -1468, -1468, -1468,
     -66, -1468,  -797, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468,  -805, -1468,  -801, -1468,
    -798, -1468,   158, -1468, -1468, -1468, -1468, -1468, -1468,   249,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468,   253,  -788, -1468,
   -1468, -1468, -1468,   251, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468,   223, -1468, -1468, -1468, -1468, -1468, -1468, -1468,   240,
   -1468, -1468, -1468,   248,   772, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468,   241, -1468, -1468, -1468, -1468, -1468, -1468, -1095,
   -1468, -1468, -1468,   274, -1468, -1468, -1468,   282,   819, -1468,
   -1468, -1094, -1468, -1093, -1468,   109, -1468,   111, -1468,   113,
   -1468,   117, -1468,   106,   107,   108, -1468, -1092, -1468, -1468,
   -1468, -1468,   277, -1468, -1468,    10,  1324, -1468, -1468, -1468,
   -1468, -1468,   285, -1468, -1468, -1468,   288, -1468,   795, -1468,
     -65, -1468, -1468, -1468, -1468, -1468,   -62, -1468, -1468, -1468,
   -1468, -1468,   -29, -1468, -1468, -1468,   287, -1468, -1468, -1468,
     291, -1468,   791, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468,   218, -1468, -1468,
   -1468,   222,   829, -1468, -1468,   -64,   -24, -1468,    20, -1468,
   -1468, -1468, -1468, -1468,   226, -1468, -1468, -1468,   225,   827,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468,   -54, -1468, -1468,
   -1468,   279, -1468, -1468, -1468,   289, -1468,   823,   586, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1091, -1468, -1468, -1468, -1468, -1468,
   -1468,   292, -1468, -1468, -1468,    33, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468,   275, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468,   261, -1468,   264,   255, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,   -23,
   -1468, -1468,   -45, -1468, -1468, -1468, -1468, -1468,   -14, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
     -68, -1468, -1468,   -93, -1468, -1468, -1468, -1468, -1468,   268,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
     624,   821, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,   666,
     820, -1468, -1468, -1468, -1468, -1468, -1468,   271, -1468, -1468,
      41, -1468, -1468, -1468, -1468, -1468, -1468,   -32, -1468, -1468,
     -59, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468, -1468,
   -1468,   278, -1468
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     809,    87,    88,    41,    68,    84,    85,   830,  1068,  1188,
    1189,   900,    43,    70,    90,   480,    91,    45,    71,   167,
     168,   169,   483,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   510,   794,   189,   511,   190,   512,   191,   192,
     193,   526,   806,   194,   195,   196,   197,   198,   548,   199,
     549,   200,   201,   202,   203,   504,   204,   205,   524,   206,
     525,   207,   208,   209,   210,   211,   485,    47,    72,   248,
     249,   250,   559,   251,   252,   253,   254,   212,   486,   213,
     487,   214,   488,   929,   930,   931,  1109,   901,   902,   903,
    1083,   904,  1084,   905,  1085,   906,  1105,   907,  1086,   908,
     909,   603,   910,   911,   912,   913,   914,   915,   916,   917,
     918,  1097,  1375,   919,   920,   921,   922,  1100,   923,  1101,
     924,  1102,   925,  1103,   926,  1104,   215,   536,   964,   965,
     966,  1129,   967,  1130,   216,   533,   950,   951,   952,   953,
     217,   535,   958,   959,   960,   961,   218,   534,   219,   543,
    1014,  1015,  1016,  1017,  1018,   220,   539,   977,   978,   979,
    1139,    63,    80,   444,   445,   446,   618,   447,   619,   221,
     540,   986,   987,   988,   989,   990,   991,   992,   993,   222,
     520,   933,   934,   935,  1112,    49,    73,   302,   303,   304,
     568,   305,   569,   306,   570,   307,   576,   308,   573,   309,
     574,   310,   575,   223,   224,   225,   314,   315,   226,   527,
     945,   946,   947,  1121,  1275,  1276,   227,   521,    57,    77,
     937,   938,   939,  1115,    59,    78,   405,   406,   407,   408,
     409,   410,   411,   602,   412,   606,   413,   605,   414,   415,
     607,   416,   228,   522,   941,   942,   943,  1118,    61,    79,
     428,   429,   430,   431,   432,   611,   433,   434,   435,   436,
     437,   438,   615,   317,   566,  1070,  1071,  1072,  1190,    51,
      74,   345,   346,   347,   580,   348,   229,   528,   230,   529,
     320,   567,  1074,  1075,  1076,  1193,    53,    75,   365,   366,
     367,   584,   368,   369,   586,   370,   371,   231,   538,   973,
     974,   975,  1136,    55,    76,   384,   385,   386,   387,   592,
     388,   593,   389,   594,   390,   595,   391,   596,   392,   597,
     393,   598,   394,   591,   322,   577,  1078,   232,   537,   969,
     970,   971,  1133,  1302,  1303,  1304,  1305,  1306,  1390,  1307,
    1391,  1308,  1309,   233,   541,  1003,  1004,  1005,  1150,  1401,
    1006,  1007,  1151,  1008,  1009,   234,   235,   544,   236,   545,
    1044,  1045,  1046,  1171,  1034,  1035,  1036,  1162,  1406,  1037,
    1163,  1038,  1164,  1039,  1040,  1041,  1168,  1442,  1443,  1444,
    1457,  1472,  1473,  1474,  1484,  1042,  1166,  1435,  1436,  1437,
    1451,  1480,  1438,  1452,  1439,  1453,  1440,  1454,  1491,  1492,
    1493,  1509,  1527,  1528,  1529,  1537,   237,   546,  1053,  1054,
    1055,  1056,  1175,  1057,  1058,  1177,   238,   547,    65,    81,
     459,   460,   461,   462,   623,   463,   464,   625,   465,   466,
     467,   628,   865,   468,   629,   239,   484,    67,    82,   471,
     472,   473,   632,   474,   240,   554,  1061,  1062,  1181,  1354,
    1355,  1356,  1357,  1416,  1358,  1414,  1477,  1478,  1487,  1501,
    1502,  1503,  1513,  1504,  1505,  1506,  1507,  1517,   241,   555,
    1065,  1066,  1067
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     166,   247,   269,   325,   356,   380,    38,   403,   424,   443,
     456,   362,   404,   425,   426,   270,  1029,   427,   271,   321,
    1030,   272,  1000,  1031,   927,   957,  1264,  1265,  1266,  1274,
    1280,   276,   284,   326,    31,   948,    32,   277,    33,   397,
     808,  1063,  1522,    42,   316,   344,   361,   381,   255,   318,
     349,   363,   382,   481,   417,   439,   165,   457,   482,   242,
     243,   244,   245,   246,   469,   470,   137,   138,  1523,   285,
     327,  1522,  1428,   441,   442,  1524,   557,   273,   994,   863,
     864,   558,   274,   877,    44,   286,   328,   789,   790,   791,
     792,    30,   256,   319,   350,   364,   383,  1523,   418,   440,
     275,   458,  1124,    46,  1524,  1125,  1496,   287,   329,  1497,
    1498,  1499,  1500,   980,   981,   982,   983,   984,   985,   288,
     330,   808,    48,   564,    86,   793,   289,   331,   565,   290,
     332,   292,   333,   949,   293,   334,   396,   294,   335,   295,
     336,  1467,   296,   337,   297,   338,   578,   582,   589,   298,
     339,   579,   583,   590,    50,   278,   279,   280,   137,   138,
     281,   282,    52,   137,   138,   165,    54,   283,   291,   137,
     138,   620,   630,   299,    56,   300,   621,   631,   301,   311,
     312,   313,    58,   340,   357,   341,   358,   342,   359,   441,
     442,   343,   360,   165,    92,    93,   634,    60,    94,    62,
     397,   635,   398,   399,    95,    96,    97,   400,   401,   402,
     892,   893,   894,   895,   896,   897,   557,   995,   996,   997,
     998,  1080,   962,   963,   634,   137,   138,   137,   138,  1081,
     564,  1429,  1430,  1431,    89,  1082,    64,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,    34,    35,    36,    37,   137,   138,   889,   890,   891,
      66,   132,   133,   134,   135,   165,  1372,  1373,  1374,   136,
     165,  1264,  1265,  1266,  1274,  1280,   165,   397,   137,   138,
     130,   475,  1047,  1048,  1049,   139,   140,   141,   142,   143,
     144,   145,  1106,  1106,   146,   873,   874,  1107,  1108,   476,
     478,  1131,  1148,   147,   137,   138,  1132,  1149,   477,  1010,
    1011,  1012,   148,   131,  1127,   149,  1155,  1128,  1160,   957,
    1169,  1156,   150,  1161,   479,  1170,   599,  1222,   137,   138,
     151,   152,  1050,   489,   165,   153,   154,   490,  1000,   491,
    1178,   137,   138,   492,  1029,  1179,  1029,   630,  1030,   493,
    1030,  1031,  1180,  1031,   155,  1185,  1106,   372,   156,   578,
    1186,  1382,   948,   955,  1383,   956,   494,   373,   374,   375,
     376,   377,   378,   379,   157,   158,   159,   160,   161,   162,
     163,  1182,   165,  1386,  1183,   137,   138,  1021,  1387,   164,
     620,  1022,  1023,  1024,  1025,  1397,   495,  1488,  1169,  1417,
    1489,  1026,  1027,  1411,  1418,   165,   582,  1347,   589,  1348,
    1349,  1420,   496,  1421,   872,   873,   874,   875,   876,   877,
     878,   879,   880,   881,   882,   883,   884,   885,   886,   497,
     498,   165,   887,   888,   889,   890,   891,   892,   893,   894,
     895,   896,   897,   898,  1455,  1485,   636,   637,  1518,  1456,
    1486,   499,   500,  1519,   501,   165,  1520,   899,   397,   419,
     398,   399,   420,   421,   422,  1538,   166,   502,   165,   503,
    1539,   505,   506,   247,   802,   803,   804,   805,   397,   836,
     837,   838,  1398,  1399,  1400,   137,   138,   269,   507,   508,
     509,   325,   513,   514,   844,   845,   846,   847,   356,   515,
     270,   423,   516,   271,   321,   362,   272,   517,   518,   380,
     519,   523,   165,   530,   531,   858,   276,   284,   532,   403,
     255,   326,   277,   542,   404,   550,   424,   551,   552,   316,
     553,   425,   426,   344,   318,   427,   556,   560,   349,   456,
     361,  1403,  1404,  1405,   561,   363,   562,   563,   571,   572,
     581,   381,   585,   587,   285,   588,   382,   600,   327,   604,
     601,   608,   273,   612,   256,   610,   417,   274,   609,   613,
     286,   614,   616,   439,   328,   617,   638,   899,   319,   622,
     624,   626,   350,   627,   633,   275,   457,   639,   640,   364,
     641,   642,   287,   643,   644,   645,   329,   646,   647,   661,
     383,   648,   649,   650,   288,   655,   651,   652,   330,   656,
     418,   289,   165,   654,   290,   331,   292,   440,   332,   293,
     333,   657,   294,   334,   295,   653,   335,   296,   336,   297,
     458,   337,   165,   338,   298,   659,   658,   667,   339,   668,
     278,   279,   280,   660,   662,   281,   282,   663,   669,   677,
     673,   664,   283,   291,   665,   666,   670,   671,   299,   672,
     300,   674,   675,   301,   311,   312,   313,   676,   678,   679,
     680,   340,   681,   341,   682,   342,   683,   684,   357,   343,
     358,   685,   359,   686,   687,   688,   360,   690,   689,   691,
     166,   692,   693,   247,   694,   116,   117,   118,   119,   120,
     121,   122,   695,   124,   125,   126,   127,   696,   697,   698,
     131,   700,   699,   701,   702,   703,   704,   705,   706,   131,
     707,   708,   709,   710,   135,   711,   712,   714,   999,  1013,
    1028,   323,   715,   456,   717,   716,   718,  1064,   137,   138,
     255,   720,   351,   352,   353,   354,   355,   137,   138,   721,
     868,   722,   723,   724,   264,   265,   266,   726,   725,   727,
     728,   267,   324,   264,   265,   266,   729,   730,   731,   733,
     267,   324,   734,   736,   737,  1001,  1019,  1032,   738,  1051,
     457,   739,   740,   742,   256,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   137,
     138,   743,   744,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   745,   746,   131,  1002,
    1020,  1033,   747,  1052,   458,   748,   749,   751,   752,   754,
     133,   134,   135,   755,   157,   158,   753,   756,   257,   757,
     258,   759,   760,   761,   762,   763,   137,   138,   259,   260,
     261,   262,   263,   139,   140,   141,    98,    99,   100,   101,
     102,   103,   264,   265,   266,   165,   765,   766,   769,   267,
     768,   147,   770,   771,   165,   774,   775,   772,   777,   268,
     448,   449,   450,   451,   452,   453,   454,   455,   780,   131,
     397,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,   773,   781,   783,   784,   778,
     785,   782,   786,   787,   797,   798,   788,   137,   138,   799,
     795,   807,   796,   800,   801,    32,   165,   811,   810,   812,
     813,   825,   815,   814,   816,   817,  1287,  1288,  1289,  1290,
     818,   819,   157,   158,   820,   821,   822,   823,   826,   824,
     827,   828,   829,   831,   832,   867,   866,   833,   834,   835,
     839,   840,   841,   928,   932,   936,   842,   843,   848,   849,
     850,   851,   852,   165,   853,   854,   855,   856,   857,   940,
     859,   861,   862,   944,   968,   972,   976,  1043,  1060,  1069,
    1073,   373,  1087,  1088,  1089,  1090,  1091,  1092,  1093,  1094,
    1095,  1096,  1098,  1099,  1111,  1203,  1110,  1114,  1113,  1116,
    1117,  1119,  1120,  1123,  1122,  1187,  1135,  1126,  1134,  1138,
    1137,   269,  1141,  1140,   403,  1142,  1143,   424,  1144,   404,
    1230,  1145,   425,   426,   270,  1263,   427,   271,   321,  1146,
     272,  1147,  1291,  1231,   165,   380,  1232,  1298,   443,  1233,
     276,   284,  1152,  1153,  1154,  1292,   277,  1157,  1293,  1237,
    1245,  1294,  1158,   316,   999,  1238,  1159,  1165,   318,  1013,
    1167,   417,  1277,  1172,   439,  1173,  1191,  1278,  1028,  1174,
    1028,  1176,  1184,  1192,  1299,  1194,  1195,   381,   285,  1300,
    1350,  1198,   382,  1196,  1064,  1351,   273,  1246,  1197,   325,
    1199,   274,   356,  1200,   286,  1234,  1201,  1212,  1202,   362,
    1235,  1001,   319,  1247,  1215,   418,  1019,  1295,   440,   275,
    1204,  1279,  1296,  1205,  1206,  1032,   287,  1032,  1236,   326,
    1207,  1208,  1209,  1301,  1051,  1248,   383,  1352,   288,  1210,
    1297,   344,  1213,  1216,   361,   289,   349,  1249,   290,   363,
     292,  1217,  1218,   293,  1250,  1002,   294,  1251,   295,  1253,
    1020,   296,  1254,   297,  1211,  1255,   327,  1256,   298,  1033,
    1257,  1033,  1258,  1219,   278,   279,   280,  1259,  1052,   281,
     282,  1353,   328,  1239,  1240,  1241,   283,   291,  1242,  1243,
     350,  1220,   299,   364,   300,  1244,  1252,   301,   311,   312,
     313,  1260,  1214,  1261,   329,  1284,  1262,  1271,  1272,  1273,
    1267,  1285,  1268,  1315,  1269,  1322,   330,  1316,  1270,  1323,
    1328,  1332,  1333,   331,  1334,  1336,   332,  1317,   333,  1318,
    1319,   334,  1338,  1343,   335,  1345,   336,  1363,  1362,   337,
    1395,   338,  1392,  1384,  1385,  1393,   339,  1394,  1396,  1320,
    1409,  1410,  1415,  1423,  1424,  1445,   954,  1447,  1324,  1441,
    1458,  1325,  1459,  1326,  1476,  1460,  1329,  1462,  1330,  1335,
    1463,  1464,  1368,  1337,  1342,  1344,  1360,  1446,  1369,   340,
    1370,   341,   357,   342,   358,  1371,   359,   343,  1376,  1377,
     360,  1465,  1490,  1378,  1380,  1230,  1381,  1388,  1389,  1402,
    1263,  1407,  1408,  1412,  1291,  1479,  1419,  1483,  1231,  1298,
    1425,  1232,  1494,  1426,  1233,  1413,  1449,  1292,  1432,  1510,
    1293,  1511,   860,  1294,  1237,  1245,  1350,  1514,  1450,  1515,
    1238,  1351,  1461,  1481,  1516,  1482,  1512,  1277,  1531,  1535,
    1532,  1533,  1278,  1534,  1542,   713,  1299,  1540,  1541,  1544,
     869,  1300,   871,   719,  1223,  1221,  1379,  1282,  1283,  1079,
    1286,  1314,  1246,  1331,  1432,  1433,  1468,  1313,  1225,  1321,
    1234,  1469,   767,  1352,  1224,  1235,  1422,   732,  1247,  1295,
    1281,   395,  1227,  1226,  1296,   758,  1279,  1229,   764,  1228,
    1365,   735,  1364,  1236,  1468,  1301,   741,  1312,  1366,  1469,
    1248,  1367,  1297,   750,  1339,  1311,  1077,  1310,  1427,  1434,
    1327,  1433,  1249,  1470,  1341,  1340,  1475,  1353,  1521,  1250,
    1495,  1466,  1251,  1530,  1253,  1543,  1346,  1254,  1059,   870,
    1255,   776,  1256,  1359,   779,  1257,  1508,  1258,  1448,  1536,
       0,  1470,  1259,  1361,     0,     0,     0,  1521,  1239,  1240,
    1241,     0,     0,  1242,  1243,  1434,     0,  1471,     0,     0,
    1244,  1252,     0,     0,     0,  1525,  1260,     0,  1261,     0,
       0,  1262,  1271,  1272,  1273,  1267,     0,  1268,     0,  1269,
       0,     0,     0,  1270,     0,  1471,     0,     0,     0,     0,
       0,     0,     0,     0,  1525,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,  1526,
       0,     0,     0,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,     0,   131,   397,
       0,     0,     0,     0,     0,     0,     0,     0,  1526,     0,
     133,   134,   135,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   137,   138,     0,   260,
     261,     0,   263,   139,   140,   141,     0,     0,     0,     0,
       0,     0,   264,   265,   266,     0,     0,     0,     0,   267,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   268,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   157,   158,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   165
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,    75,    78,    79,    79,    73,   821,    79,    73,    73,
     821,    73,   819,   821,   786,   813,  1121,  1121,  1121,  1121,
    1121,    73,    73,    74,     5,   144,     7,    73,     9,    88,
     685,   227,  1509,     7,    73,    74,    75,    76,    72,    73,
      74,    75,    76,     3,    78,    79,   242,    81,     8,    16,
      17,    18,    19,    20,    13,    14,   115,   116,  1509,    73,
      74,  1538,    24,   150,   151,  1509,     3,    73,    24,   204,
     205,     8,    73,    29,     7,    73,    74,   207,   208,   209,
     210,     0,    72,    73,    74,    75,    76,  1538,    78,    79,
      73,    81,     3,     7,  1538,     6,   219,    73,    74,   222,
     223,   224,   225,   153,   154,   155,   156,   157,   158,    73,
      74,   766,     7,     3,   242,   245,    73,    74,     8,    73,
      74,    73,    74,   242,    73,    74,    24,    73,    74,    73,
      74,   190,    73,    74,    73,    74,     3,     3,     3,    73,
      74,     8,     8,     8,     7,    73,    73,    73,   115,   116,
      73,    73,     7,   115,   116,   242,     7,    73,    73,   115,
     116,     3,     3,    73,     7,    73,     8,     8,    73,    73,
      73,    73,     7,    74,    75,    74,    75,    74,    75,   150,
     151,    74,    75,   242,    11,    12,     3,     7,    15,     7,
      88,     8,    90,    91,    21,    22,    23,    95,    96,    97,
      47,    48,    49,    50,    51,    52,     3,   163,   164,   165,
     166,     8,   129,   130,     3,   115,   116,   115,   116,     8,
       3,   183,   184,   185,    10,     8,     7,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,   242,   243,   244,   245,   115,   116,    44,    45,    46,
       7,    98,    99,   100,   101,   242,    39,    40,    41,   106,
     242,  1386,  1386,  1386,  1386,  1386,   242,    88,   115,   116,
      86,     6,   192,   193,   194,   122,   123,   124,   125,   126,
     127,   128,     3,     3,   131,    25,    26,     8,     8,     3,
       8,     3,     3,   140,   115,   116,     8,     8,     4,   169,
     170,   171,   149,    87,     3,   152,     3,     6,     3,  1127,
       3,     8,   159,     8,     3,     8,     8,  1109,   115,   116,
     167,   168,   242,     4,   242,   172,   173,     4,  1155,     4,
       3,   115,   116,     4,  1169,     8,  1171,     3,  1169,     4,
    1171,  1169,     8,  1171,   191,     3,     3,   131,   195,     3,
       8,     8,   144,   145,     8,   147,     4,   141,   142,   143,
     144,   145,   146,   147,   211,   212,   213,   214,   215,   216,
     217,     3,   242,     3,     6,   115,   116,   174,     8,   226,
       3,   178,   179,   180,   181,     8,     4,     3,     3,     3,
       6,   188,   189,     8,     8,   242,     3,   218,     3,   220,
     221,     8,     4,     8,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,     4,
       4,   242,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,     3,     3,   476,   477,     3,     8,
       8,     4,     4,     8,     4,   242,   186,   187,    88,    89,
      90,    91,    92,    93,    94,     3,   557,     4,   242,     4,
       8,     4,     4,   564,   102,   103,   104,   105,    88,   727,
     728,   729,   160,   161,   162,   115,   116,   578,     4,     4,
       4,   582,     4,     4,   742,   743,   744,   745,   589,     4,
     578,   131,     4,   578,   578,   589,   578,     4,     4,   600,
       4,     4,   242,     4,     4,   763,   578,   578,     4,   610,
     564,   582,   578,     4,   610,     4,   617,     4,     4,   578,
       4,   617,   617,   582,   578,   617,     4,     4,   582,   630,
     589,   175,   176,   177,     4,   589,     4,     4,     4,     4,
       4,   600,     4,     4,   578,     4,   600,     3,   582,     4,
       8,     4,   578,     4,   564,     3,   610,   578,     8,     4,
     578,     4,     8,   617,   582,     3,   242,   187,   578,     4,
       4,     4,   582,     4,     4,   578,   630,     4,     4,   589,
       4,     4,   578,     4,     4,     4,   582,   243,   243,     4,
     600,   243,   243,   243,   578,   244,   243,   243,   582,   244,
     610,   578,   242,   245,   578,   582,   578,   617,   582,   578,
     582,   244,   578,   582,   578,   243,   582,   578,   582,   578,
     630,   582,   242,   582,   578,   244,   243,     4,   582,     4,
     578,   578,   578,   243,   243,   578,   578,   243,     4,     4,
     243,   245,   578,   578,   245,   245,   245,   245,   578,   244,
     578,   243,   243,   578,   578,   578,   578,   245,     4,     4,
     243,   582,     4,   582,     4,   582,     4,     4,   589,   582,
     589,     4,   589,     4,   245,   245,   589,     4,   245,     4,
     781,     4,     4,   784,     4,    72,    73,    74,    75,    76,
      77,    78,     4,    80,    81,    82,    83,     4,     4,     4,
      87,     4,   243,     4,     4,     4,     4,     4,     4,    87,
     245,   245,   245,   245,   101,     4,     4,     4,   819,   820,
     821,   108,   245,   824,   243,   245,   243,   828,   115,   116,
     784,     4,   110,   111,   112,   113,   114,   115,   116,     4,
     780,     4,     4,     4,   131,   132,   133,   245,   243,     4,
       4,   138,   139,   131,   132,   133,     4,     4,     4,     4,
     138,   139,   243,     4,   243,   819,   820,   821,     4,   823,
     824,   243,   243,     4,   784,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,   115,
     116,     4,     4,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,     4,     4,    87,   819,
     820,   821,     4,   823,   824,     4,     4,     4,     4,     4,
      99,   100,   101,     4,   211,   212,   243,     4,   107,   245,
     109,     4,   245,   245,   245,     4,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,    54,    55,    56,    57,
      58,    59,   131,   132,   133,   242,     4,     4,     4,   138,
     245,   140,   243,     4,   242,     4,     4,   243,     4,   148,
     196,   197,   198,   199,   200,   201,   202,   203,     4,    87,
      88,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   243,     7,     7,     7,   243,
       7,   242,     7,     5,     5,     5,   242,   115,   116,     5,
     242,     5,   242,   242,   242,     7,   242,     5,   242,     5,
       5,   242,     5,     7,     5,     5,   134,   135,   136,   137,
       7,     7,   211,   212,     7,     7,     5,     7,   242,     7,
       5,     7,     5,     5,     5,     5,   206,   242,   242,   242,
     242,     7,   242,     7,     7,     7,   242,   242,   242,   242,
     242,   242,   242,   242,   242,   242,   242,   242,   242,     7,
     242,   242,   242,     7,     7,     7,     7,     7,     7,     7,
       7,   141,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     3,   245,     6,     3,     6,     6,
       3,     6,     3,     3,     6,   242,     3,     6,     6,     3,
       6,  1112,     3,     6,  1115,     4,     4,  1118,     4,  1115,
    1121,     4,  1118,  1118,  1112,  1121,  1118,  1112,  1112,     4,
    1112,     4,  1133,  1121,   242,  1136,  1121,  1133,  1139,  1121,
    1112,  1112,     4,     4,     4,  1133,  1112,     4,  1133,  1121,
    1121,  1133,     4,  1112,  1155,  1121,     4,     4,  1112,  1160,
       4,  1115,  1121,     6,  1118,     3,     6,  1121,  1169,     4,
    1171,     4,     4,     3,  1133,     6,     3,  1136,  1112,  1133,
    1181,     4,  1136,     8,  1185,  1181,  1112,  1121,     6,  1190,
       4,  1112,  1193,     4,  1112,  1121,     4,     4,   243,  1193,
    1121,  1155,  1112,  1121,     4,  1115,  1160,  1133,  1118,  1112,
     243,  1121,  1133,   245,   243,  1169,  1112,  1171,  1121,  1190,
     243,   243,   243,  1133,  1178,  1121,  1136,  1181,  1112,   243,
    1133,  1190,   245,     4,  1193,  1112,  1190,  1121,  1112,  1193,
    1112,     4,     4,  1112,  1121,  1155,  1112,  1121,  1112,  1121,
    1160,  1112,  1121,  1112,   243,  1121,  1190,  1121,  1112,  1169,
    1121,  1171,  1121,     4,  1112,  1112,  1112,  1121,  1178,  1112,
    1112,  1181,  1190,  1121,  1121,  1121,  1112,  1112,  1121,  1121,
    1190,     4,  1112,  1193,  1112,  1121,  1121,  1112,  1112,  1112,
    1112,  1121,   243,  1121,  1190,     4,  1121,  1121,  1121,  1121,
    1121,     4,  1121,   243,  1121,     4,  1190,   243,  1121,     4,
     245,     4,     4,  1190,     4,     4,  1190,   243,  1190,   243,
     243,  1190,     4,     4,  1190,     4,  1190,     3,     6,  1190,
       3,  1190,     4,     8,     8,     4,  1190,     8,     8,   243,
       7,     5,     4,     4,     4,     4,   812,     4,   243,     7,
       6,   243,     3,   243,     7,     5,   243,     4,   243,   243,
       4,     4,   242,   245,   245,   243,   245,   243,   242,  1190,
     242,  1190,  1193,  1190,  1193,   242,  1193,  1190,   242,   242,
    1193,     4,     7,   242,   242,  1386,   242,   242,   242,   242,
    1386,   242,   242,   242,  1395,   182,   242,     5,  1386,  1395,
     245,  1386,     4,   245,  1386,  1345,   242,  1395,  1409,     6,
    1395,     3,   766,  1395,  1386,  1386,  1417,     4,   242,     4,
    1386,  1417,   242,   242,     4,   242,   242,  1386,     4,     4,
     245,   243,  1386,   243,     4,   557,  1395,   242,   242,   242,
     781,  1395,   784,   564,  1111,  1106,  1218,  1124,  1127,   867,
    1131,  1141,  1386,  1160,  1455,  1409,  1457,  1139,  1114,  1148,
    1386,  1457,   620,  1417,  1112,  1386,  1386,   578,  1386,  1395,
    1123,    77,  1117,  1115,  1395,   610,  1386,  1120,   617,  1118,
    1192,   582,  1190,  1386,  1485,  1395,   589,  1138,  1193,  1485,
    1386,  1195,  1395,   600,  1169,  1136,   840,  1135,  1395,  1409,
    1155,  1455,  1386,  1457,  1173,  1171,  1459,  1417,  1509,  1386,
    1485,  1455,  1386,  1511,  1386,  1538,  1178,  1386,   824,   783,
    1386,   630,  1386,  1182,   634,  1386,  1488,  1386,  1417,  1518,
      -1,  1485,  1386,  1185,    -1,    -1,    -1,  1538,  1386,  1386,
    1386,    -1,    -1,  1386,  1386,  1455,    -1,  1457,    -1,    -1,
    1386,  1386,    -1,    -1,    -1,  1509,  1386,    -1,  1386,    -1,
      -1,  1386,  1386,  1386,  1386,  1386,    -1,  1386,    -1,  1386,
      -1,    -1,    -1,  1386,    -1,  1485,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1538,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,  1509,
      -1,    -1,    -1,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    -1,    87,    88,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1538,    -1,
      99,   100,   101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   115,   116,    -1,   118,
     119,    -1,   121,   122,   123,   124,    -1,    -1,    -1,    -1,
      -1,    -1,   131,   132,   133,    -1,    -1,    -1,    -1,   138,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   148,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   211,   212,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   242
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
       0,     5,     7,     9,   242,   243,   244,   245,   262,   263,
     264,   269,     7,   278,     7,   283,     7,   343,     7,   461,
       7,   545,     7,   562,     7,   579,     7,   494,     7,   500,
       7,   524,     7,   437,     7,   694,     7,   713,   270,   265,
     279,   284,   344,   462,   546,   563,   580,   495,   501,   525,
     438,   695,   714,   262,   271,   272,   242,   267,   268,    10,
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
     340,   341,   353,   355,   357,   402,   410,   416,   422,   424,
     431,   445,   455,   479,   480,   481,   484,   492,   518,   552,
     554,   573,   603,   619,   631,   632,   634,   682,   692,   711,
     720,   744,    16,    17,    18,    19,    20,   277,   345,   346,
     347,   349,   350,   351,   352,   552,   554,   107,   109,   117,
     118,   119,   120,   121,   131,   132,   133,   138,   148,   277,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   304,   305,   306,   307,   310,   312,
     314,   315,   316,   319,   320,   321,   322,   323,   325,   327,
     333,   335,   463,   464,   465,   467,   469,   471,   473,   475,
     477,   479,   480,   481,   482,   483,   518,   539,   552,   554,
     556,   573,   600,   108,   139,   277,   304,   305,   306,   307,
     310,   312,   314,   316,   319,   320,   321,   322,   323,   325,
     471,   473,   475,   477,   518,   547,   548,   549,   551,   552,
     554,   110,   111,   112,   113,   114,   277,   471,   473,   475,
     477,   518,   551,   552,   554,   564,   565,   566,   568,   569,
     571,   572,   131,   141,   142,   143,   144,   145,   146,   147,
     277,   518,   552,   554,   581,   582,   583,   584,   586,   588,
     590,   592,   594,   596,   598,   492,    24,    88,    90,    91,
      95,    96,    97,   277,   376,   502,   503,   504,   505,   506,
     507,   508,   510,   512,   514,   515,   517,   552,   554,    89,
      92,    93,    94,   131,   277,   376,   506,   512,   526,   527,
     528,   529,   530,   532,   533,   534,   535,   536,   537,   552,
     554,   150,   151,   277,   439,   440,   441,   443,   196,   197,
     198,   199,   200,   201,   202,   203,   277,   552,   554,   696,
     697,   698,   699,   701,   702,   704,   705,   706,   709,    13,
      14,   715,   716,   717,   719,     6,     3,     4,     8,     3,
     281,     3,     8,   288,   712,   342,   354,   356,   358,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   331,     4,     4,     4,     4,     4,
     308,   311,   313,     4,     4,     4,     4,     4,     4,     4,
     456,   493,   519,     4,   334,   336,   317,   485,   553,   555,
       4,     4,     4,   411,   423,   417,   403,   604,   574,   432,
     446,   620,     4,   425,   633,   635,   683,   693,   324,   326,
       4,     4,     4,     4,   721,   745,     4,     3,     8,   348,
       4,     4,     4,     4,     3,     8,   540,   557,   466,   468,
     470,     4,     4,   474,   476,   478,   472,   601,     3,     8,
     550,     4,     3,     8,   567,     4,   570,     4,     4,     3,
       8,   599,   585,   587,   589,   591,   593,   595,   597,     8,
       3,     8,   509,   377,     4,   513,   511,   516,     4,     8,
       3,   531,     4,     4,     4,   538,     8,     3,   442,   444,
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
       4,     4,   464,     4,   243,   548,     4,   243,     4,   243,
     243,   565,     4,     4,     4,     4,     4,     4,     4,     4,
     583,     4,     4,   243,     4,     4,     4,   245,   504,     4,
     245,   245,   245,     4,   528,     4,     4,   440,   245,     4,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,   187,
     277,   363,   364,   365,   367,   369,   371,   373,   375,   376,
     378,   379,   380,   381,   382,   383,   384,   385,   386,   389,
     390,   391,   392,   394,   396,   398,   400,   363,     7,   359,
     360,   361,     7,   457,   458,   459,     7,   496,   497,   498,
       7,   520,   521,   522,     7,   486,   487,   488,   144,   242,
     412,   413,   414,   415,   271,   145,   147,   414,   418,   419,
     420,   421,   129,   130,   404,   405,   406,   408,     7,   605,
     606,   607,     7,   575,   576,   577,     7,   433,   434,   435,
     153,   154,   155,   156,   157,   158,   447,   448,   449,   450,
     451,   452,   453,   454,    24,   163,   164,   165,   166,   277,
     378,   552,   554,   621,   622,   623,   626,   627,   629,   630,
     169,   170,   171,   277,   426,   427,   428,   429,   430,   552,
     554,   174,   178,   179,   180,   181,   188,   189,   277,   392,
     394,   396,   552,   554,   640,   641,   642,   645,   647,   649,
     650,   651,   661,     7,   636,   637,   638,   192,   193,   194,
     242,   552,   554,   684,   685,   686,   687,   689,   690,   696,
       7,   722,   723,   227,   277,   746,   747,   748,   274,     7,
     541,   542,   543,     7,   558,   559,   560,   584,   602,   359,
       8,     8,     8,   366,   368,   370,   374,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   387,     4,     4,
     393,   395,   397,   399,   401,   372,     3,     8,     8,   362,
       6,     3,   460,     6,     3,   499,     6,     3,   523,     6,
       3,   489,     6,     3,     3,     6,     6,     3,     6,   407,
     409,     3,     8,   608,     6,     3,   578,     6,     3,   436,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
     624,   628,     4,     4,     4,     3,     8,     4,     4,     4,
       3,     8,   643,   646,   648,     4,   662,     4,   652,     3,
       8,   639,     6,     3,     4,   688,     4,   691,     3,     8,
       8,   724,     3,     6,     4,     3,     8,   242,   275,   276,
     544,     6,     3,   561,     6,     3,     8,     6,     4,     4,
       4,     4,   243,   245,   243,   245,   243,   243,   243,   243,
     243,   243,     4,   245,   243,     4,     4,     4,     4,     4,
       4,   364,   363,   361,   463,   459,   502,   498,   526,   522,
     277,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   304,   305,   306,   307,   310,
     312,   314,   315,   316,   319,   320,   321,   322,   323,   325,
     327,   333,   335,   376,   455,   467,   469,   471,   473,   475,
     477,   479,   480,   481,   483,   490,   491,   518,   552,   554,
     600,   488,   413,   419,     4,     4,   405,   134,   135,   136,
     137,   277,   289,   290,   291,   292,   293,   294,   376,   518,
     552,   554,   609,   610,   611,   612,   613,   615,   617,   618,
     607,   581,   577,   439,   435,   243,   243,   243,   243,   243,
     243,   448,     4,     4,   243,   243,   243,   622,   245,   243,
     243,   427,     4,     4,     4,   243,     4,   245,     4,   641,
     640,   638,   245,     4,   243,     4,   685,   218,   220,   221,
     277,   376,   552,   554,   725,   726,   727,   728,   730,   723,
     245,   747,     6,     3,   547,   543,   564,   560,   242,   242,
     242,   242,    39,    40,    41,   388,   242,   242,   242,   398,
     242,   242,     8,     8,     8,     8,     3,     8,   242,   242,
     614,   616,     4,     4,     8,     3,     8,     8,   160,   161,
     162,   625,   242,   175,   176,   177,   644,   242,   242,     7,
       5,     8,   242,   262,   731,     4,   729,     3,     8,   242,
       8,     8,   491,     4,     4,   245,   245,   611,    24,   183,
     184,   185,   277,   552,   554,   663,   664,   665,   668,   670,
     672,     7,   653,   654,   655,     4,   243,     4,   726,   242,
     242,   666,   669,   671,   673,     3,     8,   656,     6,     3,
       5,   242,     4,     4,     4,     4,   664,   190,   277,   376,
     552,   554,   657,   658,   659,   655,     7,   732,   733,   182,
     667,   242,   242,     5,   660,     3,     8,   734,     3,     6,
       7,   674,   675,   676,     4,   658,   219,   222,   223,   224,
     225,   735,   736,   737,   739,   740,   741,   742,   733,   677,
       6,     3,   242,   738,     4,     4,     4,   743,     3,     8,
     186,   277,   367,   369,   371,   552,   554,   678,   679,   680,
     676,     4,   245,   243,   243,     4,   736,   681,     3,     8,
     242,   242,     4,   679,   242
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
     364,   364,   364,   364,   364,   364,   364,   364,   364,   366,
     365,   368,   367,   370,   369,   372,   371,   374,   373,   375,
     377,   376,   378,   379,   380,   381,   382,   383,   384,   385,
     387,   386,   388,   388,   388,   389,   390,   391,   393,   392,
     395,   394,   397,   396,   399,   398,   398,   398,   398,   398,
     398,   401,   400,   403,   402,   404,   404,   404,   405,   405,
     407,   406,   409,   408,   411,   410,   412,   412,   412,   413,
     413,   414,   415,   417,   416,   418,   418,   418,   419,   419,
     419,   420,   421,   423,   422,   425,   424,   426,   426,   426,
     427,   427,   427,   427,   427,   427,   428,   429,   430,   432,
     431,   433,   433,   434,   434,   434,   436,   435,   438,   437,
     439,   439,   439,   439,   440,   440,   442,   441,   444,   443,
     446,   445,   447,   447,   447,   448,   448,   448,   448,   448,
     448,   449,   450,   451,   452,   453,   454,   456,   455,   457,
     457,   458,   458,   458,   460,   459,   462,   461,   463,   463,
     463,   464,   464,   464,   464,   464,   464,   464,   464,   464,
     464,   464,   464,   464,   464,   464,   464,   464,   464,   464,
     464,   464,   464,   464,   464,   464,   464,   464,   464,   464,
     464,   464,   464,   464,   464,   464,   464,   464,   464,   464,
     464,   464,   464,   464,   464,   464,   464,   464,   464,   464,
     464,   464,   464,   466,   465,   468,   467,   470,   469,   472,
     471,   474,   473,   476,   475,   478,   477,   479,   480,   481,
     482,   483,   485,   484,   486,   486,   487,   487,   487,   489,
     488,   490,   490,   490,   491,   491,   491,   491,   491,   491,
     491,   491,   491,   491,   491,   491,   491,   491,   491,   491,
     491,   491,   491,   491,   491,   491,   491,   491,   491,   491,
     491,   491,   491,   491,   491,   491,   491,   491,   491,   491,
     491,   491,   491,   491,   491,   491,   491,   491,   491,   491,
     491,   491,   491,   493,   492,   495,   494,   496,   496,   497,
     497,   497,   499,   498,   501,   500,   502,   502,   503,   503,
     503,   504,   504,   504,   504,   504,   504,   504,   504,   504,
     504,   505,   506,   507,   509,   508,   511,   510,   513,   512,
     514,   516,   515,   517,   519,   518,   520,   520,   521,   521,
     521,   523,   522,   525,   524,   526,   526,   527,   527,   527,
     528,   528,   528,   528,   528,   528,   528,   528,   528,   528,
     528,   529,   531,   530,   532,   533,   534,   535,   536,   538,
     537,   540,   539,   541,   541,   542,   542,   542,   544,   543,
     546,   545,   547,   547,   547,   548,   548,   548,   548,   548,
     548,   548,   548,   548,   548,   548,   548,   548,   548,   548,
     548,   548,   548,   548,   548,   548,   548,   548,   548,   550,
     549,   551,   553,   552,   555,   554,   557,   556,   558,   558,
     559,   559,   559,   561,   560,   563,   562,   564,   564,   564,
     565,   565,   565,   565,   565,   565,   565,   565,   565,   565,
     565,   565,   565,   565,   567,   566,   568,   570,   569,   571,
     572,   574,   573,   575,   575,   576,   576,   576,   578,   577,
     580,   579,   581,   581,   582,   582,   582,   583,   583,   583,
     583,   583,   583,   583,   583,   583,   583,   583,   583,   585,
     584,   587,   586,   589,   588,   591,   590,   593,   592,   595,
     594,   597,   596,   599,   598,   601,   600,   602,   604,   603,
     605,   605,   606,   606,   606,   608,   607,   609,   609,   610,
     610,   610,   611,   611,   611,   611,   611,   611,   611,   611,
     611,   611,   611,   611,   611,   611,   611,   612,   614,   613,
     616,   615,   617,   618,   620,   619,   621,   621,   621,   622,
     622,   622,   622,   622,   622,   622,   622,   622,   624,   623,
     625,   625,   625,   626,   628,   627,   629,   630,   631,   633,
     632,   635,   634,   636,   636,   637,   637,   637,   639,   638,
     640,   640,   640,   641,   641,   641,   641,   641,   641,   641,
     641,   641,   641,   641,   641,   641,   643,   642,   644,   644,
     644,   646,   645,   648,   647,   649,   650,   652,   651,   653,
     653,   654,   654,   654,   656,   655,   657,   657,   657,   658,
     658,   658,   658,   658,   660,   659,   662,   661,   663,   663,
     663,   664,   664,   664,   664,   664,   664,   664,   666,   665,
     667,   669,   668,   671,   670,   673,   672,   674,   674,   675,
     675,   675,   677,   676,   678,   678,   678,   679,   679,   679,
     679,   679,   679,   679,   681,   680,   683,   682,   684,   684,
     684,   685,   685,   685,   685,   685,   685,   686,   688,   687,
     689,   691,   690,   693,   692,   695,   694,   696,   696,   696,
     697,   697,   697,   697,   697,   697,   697,   697,   697,   697,
     697,   698,   700,   699,   701,   703,   702,   704,   705,   707,
     706,   708,   708,   710,   709,   712,   711,   714,   713,   715,
     715,   715,   716,   716,   718,   717,   719,   721,   720,   722,
     722,   722,   724,   723,   725,   725,   725,   726,   726,   726,
     726,   726,   726,   726,   727,   729,   728,   731,   730,   732,
     732,   732,   734,   733,   735,   735,   735,   736,   736,   736,
     736,   736,   738,   737,   739,   740,   741,   743,   742,   745,
     744,   746,   746,   746,   747,   747,   748
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     3,     3,     3,     3,     3,     3,
       0,     4,     1,     1,     1,     3,     3,     3,     0,     4,
       0,     4,     0,     4,     0,     4,     1,     1,     1,     1,
       1,     0,     4,     0,     6,     1,     3,     2,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     0,     6,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     0,     4,
       1,     3,     2,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     3,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     6,     0,     4,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     0,     1,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     0,     4,     0,     4,     0,     4,
       1,     0,     4,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     0,     1,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     3,     3,     3,     0,
       4,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     4,     0,     4,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     4,     3,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     0,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     1,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     3,     3,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     3,     0,     4,     3,     3,     3,     0,
       6,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     0,     4,     0,     4,     3,     3,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     0,     4,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     4,     0,     4,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       3,     0,     4,     0,     6,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     3,     0,     4,     3,     3,     0,
       4,     1,     1,     0,     4,     0,     6,     0,     4,     1,
       3,     2,     1,     1,     0,     6,     3,     0,     6,     1,
       3,     2,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     6,     1,
       3,     2,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     0,     4,     3,     3,     3,     0,     4,     0,
       6,     1,     3,     2,     1,     1,     3
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
     738,   741,   744,   750,   750,   759,   759,   768,   777,   787,
     787,   796,   799,   802,   805,   810,   816,   822,   828,   834,
     834,   843,   843,   852,   858,   864,   870,   870,   879,   885,
     885,   894,   894,   903,   909,   915,   921,   927,   927,   939,
     939,   948,   949,   950,   955,   956,   957,   958,   959,   960,
     961,   962,   965,   965,   976,   982,   988,   994,  1000,  1000,
    1013,  1013,  1026,  1026,  1037,  1038,  1041,  1042,  1043,  1048,
    1048,  1058,  1059,  1060,  1065,  1066,  1067,  1068,  1069,  1070,
    1071,  1072,  1073,  1074,  1075,  1076,  1077,  1078,  1079,  1080,
    1081,  1082,  1083,  1084,  1085,  1086,  1087,  1088,  1089,  1092,
    1092,  1101,  1101,  1110,  1110,  1119,  1119,  1128,  1128,  1137,
    1143,  1143,  1152,  1158,  1164,  1170,  1176,  1182,  1188,  1194,
    1200,  1200,  1208,  1209,  1210,  1213,  1219,  1225,  1231,  1231,
    1240,  1240,  1249,  1249,  1258,  1258,  1266,  1269,  1272,  1275,
    1278,  1283,  1283,  1292,  1292,  1303,  1304,  1305,  1310,  1311,
    1314,  1314,  1333,  1333,  1351,  1351,  1362,  1363,  1364,  1369,
    1370,  1373,  1378,  1383,  1383,  1394,  1395,  1396,  1401,  1402,
    1403,  1406,  1411,  1418,  1418,  1431,  1431,  1444,  1445,  1446,
    1451,  1452,  1453,  1454,  1455,  1456,  1459,  1465,  1471,  1477,
    1477,  1488,  1489,  1492,  1493,  1494,  1499,  1499,  1509,  1509,
    1519,  1520,  1521,  1524,  1527,  1528,  1531,  1531,  1540,  1540,
    1549,  1549,  1561,  1562,  1563,  1568,  1569,  1570,  1571,  1572,
    1573,  1576,  1582,  1588,  1594,  1600,  1606,  1615,  1615,  1629,
    1630,  1633,  1634,  1635,  1644,  1644,  1670,  1670,  1681,  1682,
    1683,  1689,  1690,  1691,  1692,  1693,  1694,  1695,  1696,  1697,
    1698,  1699,  1700,  1701,  1702,  1703,  1704,  1705,  1706,  1707,
    1708,  1709,  1710,  1711,  1712,  1713,  1714,  1715,  1716,  1717,
    1718,  1719,  1720,  1721,  1722,  1723,  1724,  1725,  1726,  1727,
    1728,  1729,  1730,  1731,  1732,  1733,  1734,  1735,  1736,  1737,
    1738,  1739,  1740,  1743,  1743,  1752,  1752,  1761,  1761,  1770,
    1770,  1780,  1780,  1792,  1792,  1803,  1803,  1814,  1820,  1826,
    1832,  1838,  1846,  1846,  1858,  1859,  1863,  1864,  1865,  1870,
    1870,  1878,  1879,  1880,  1885,  1886,  1887,  1888,  1889,  1890,
    1891,  1892,  1893,  1894,  1895,  1896,  1897,  1898,  1899,  1900,
    1901,  1902,  1903,  1904,  1905,  1906,  1907,  1908,  1909,  1910,
    1911,  1912,  1913,  1914,  1915,  1916,  1917,  1918,  1919,  1920,
    1921,  1922,  1923,  1924,  1925,  1926,  1927,  1928,  1929,  1930,
    1931,  1932,  1933,  1940,  1940,  1954,  1954,  1963,  1964,  1967,
    1968,  1969,  1976,  1976,  1991,  1991,  2005,  2006,  2009,  2010,
    2011,  2016,  2017,  2018,  2019,  2020,  2021,  2022,  2023,  2024,
    2025,  2028,  2030,  2036,  2038,  2038,  2047,  2047,  2056,  2056,
    2065,  2067,  2067,  2076,  2086,  2086,  2099,  2100,  2105,  2106,
    2107,  2114,  2114,  2126,  2126,  2138,  2139,  2144,  2145,  2146,
    2153,  2154,  2155,  2156,  2157,  2158,  2159,  2160,  2161,  2162,
    2163,  2166,  2168,  2168,  2177,  2179,  2181,  2187,  2193,  2199,
    2199,  2213,  2213,  2226,  2227,  2230,  2231,  2232,  2237,  2237,
    2247,  2247,  2257,  2258,  2259,  2264,  2265,  2266,  2267,  2268,
    2269,  2270,  2271,  2272,  2273,  2274,  2275,  2276,  2277,  2278,
    2279,  2280,  2281,  2282,  2283,  2284,  2285,  2286,  2287,  2290,
    2290,  2299,  2305,  2305,  2330,  2330,  2360,  2360,  2373,  2374,
    2377,  2378,  2379,  2384,  2384,  2396,  2396,  2408,  2409,  2410,
    2415,  2416,  2417,  2418,  2419,  2420,  2421,  2422,  2423,  2424,
    2425,  2426,  2427,  2428,  2431,  2431,  2440,  2446,  2446,  2455,
    2461,  2470,  2470,  2481,  2482,  2485,  2486,  2487,  2492,  2492,
    2501,  2501,  2510,  2511,  2514,  2515,  2516,  2522,  2523,  2524,
    2525,  2526,  2527,  2528,  2529,  2530,  2531,  2532,  2533,  2536,
    2536,  2547,  2547,  2558,  2558,  2569,  2569,  2578,  2578,  2587,
    2587,  2596,  2596,  2605,  2605,  2619,  2619,  2630,  2636,  2636,
    2647,  2648,  2651,  2652,  2653,  2658,  2658,  2668,  2669,  2672,
    2673,  2674,  2679,  2680,  2681,  2682,  2683,  2684,  2685,  2686,
    2687,  2688,  2689,  2690,  2691,  2692,  2693,  2696,  2698,  2698,
    2707,  2707,  2717,  2723,  2732,  2732,  2745,  2746,  2747,  2752,
    2753,  2754,  2755,  2756,  2757,  2758,  2759,  2760,  2763,  2763,
    2771,  2772,  2773,  2776,  2782,  2782,  2791,  2797,  2805,  2813,
    2813,  2825,  2825,  2837,  2838,  2841,  2842,  2843,  2848,  2848,
    2856,  2857,  2858,  2863,  2864,  2865,  2866,  2867,  2868,  2869,
    2870,  2871,  2872,  2873,  2874,  2875,  2878,  2878,  2887,  2888,
    2889,  2892,  2892,  2901,  2901,  2910,  2916,  2922,  2922,  2933,
    2934,  2937,  2938,  2939,  2944,  2944,  2952,  2953,  2954,  2959,
    2960,  2961,  2962,  2963,  2966,  2966,  2977,  2977,  2990,  2991,
    2992,  2997,  2998,  2999,  3000,  3001,  3002,  3003,  3006,  3006,
    3014,  3017,  3017,  3026,  3026,  3035,  3035,  3046,  3047,  3050,
    3051,  3052,  3057,  3057,  3065,  3066,  3067,  3072,  3073,  3074,
    3075,  3076,  3077,  3078,  3081,  3081,  3092,  3092,  3105,  3106,
    3107,  3112,  3113,  3114,  3115,  3116,  3117,  3120,  3126,  3126,
    3135,  3141,  3141,  3151,  3151,  3164,  3164,  3174,  3175,  3176,
    3181,  3182,  3183,  3184,  3185,  3186,  3187,  3188,  3189,  3190,
    3191,  3194,  3200,  3200,  3209,  3215,  3215,  3224,  3230,  3236,
    3236,  3245,  3246,  3249,  3249,  3260,  3260,  3272,  3272,  3282,
    3283,  3284,  3290,  3291,  3294,  3294,  3305,  3313,  3313,  3326,
    3327,  3328,  3334,  3334,  3342,  3343,  3344,  3349,  3350,  3351,
    3352,  3353,  3354,  3355,  3358,  3364,  3364,  3373,  3373,  3384,
    3385,  3386,  3391,  3391,  3399,  3400,  3401,  3406,  3407,  3408,
    3409,  3410,  3413,  3413,  3422,  3428,  3434,  3440,  3440,  3449,
    3449,  3460,  3461,  3462,  3467,  3468,  3471
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
#line 7191 "dhcp6_parser.cc"

#line 3477 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
