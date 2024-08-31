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
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
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
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
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
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
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
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
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
#line 319 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 417 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 319 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 423 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 319 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 429 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 319 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 435 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 319 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 441 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 319 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 447 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 319 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 453 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 319 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 459 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 319 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 465 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 319 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 471 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 319 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 477 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
#line 319 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 483 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 319 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 489 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 319 "dhcp6_parser.yy"
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
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
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
#line 328 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 777 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 329 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 783 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 330 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 789 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 331 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 795 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 332 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 801 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 333 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 807 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 334 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 813 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 335 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 819 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 336 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 825 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 337 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 831 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 338 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 837 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 339 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 843 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 340 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 849 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 341 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 855 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 349 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 861 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 350 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 867 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 351 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 873 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 352 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 879 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 353 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 885 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 354 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 891 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 355 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 897 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 358 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 906 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 363 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 917 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 368 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 927 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 374 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 933 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 381 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 943 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 386 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 954 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 392 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 962 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 397 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 971 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 400 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 979 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 408 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 988 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 412 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 997 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 416 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 1005 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 422 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 1013 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 424 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1022 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 433 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1031 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 437 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1040 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 441 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1048 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 451 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1059 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 460 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1070 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 465 "dhcp6_parser.yy"
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
#line 475 "dhcp6_parser.yy"
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
#line 484 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1108 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 492 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1116 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 498 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1126 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 502 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1135 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 509 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1143 "dhcp6_parser.cc"
    break;

  case 141: // $@21: %empty
#line 587 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1152 "dhcp6_parser.cc"
    break;

  case 142: // data_directory: "data-directory" $@21 ":" "constant string"
#line 590 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1162 "dhcp6_parser.cc"
    break;

  case 143: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 596 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1172 "dhcp6_parser.cc"
    break;

  case 144: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 602 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1182 "dhcp6_parser.cc"
    break;

  case 145: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 608 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1192 "dhcp6_parser.cc"
    break;

  case 146: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 614 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1202 "dhcp6_parser.cc"
    break;

  case 147: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 620 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1212 "dhcp6_parser.cc"
    break;

  case 148: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 626 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1222 "dhcp6_parser.cc"
    break;

  case 149: // renew_timer: "renew-timer" ":" "integer"
#line 632 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1232 "dhcp6_parser.cc"
    break;

  case 150: // rebind_timer: "rebind-timer" ":" "integer"
#line 638 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1242 "dhcp6_parser.cc"
    break;

  case 151: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 644 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1252 "dhcp6_parser.cc"
    break;

  case 152: // t1_percent: "t1-percent" ":" "floating point"
#line 650 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1262 "dhcp6_parser.cc"
    break;

  case 153: // t2_percent: "t2-percent" ":" "floating point"
#line 656 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1272 "dhcp6_parser.cc"
    break;

  case 154: // cache_threshold: "cache-threshold" ":" "floating point"
#line 662 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1282 "dhcp6_parser.cc"
    break;

  case 155: // cache_max_age: "cache-max-age" ":" "integer"
#line 668 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1292 "dhcp6_parser.cc"
    break;

  case 156: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 674 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1302 "dhcp6_parser.cc"
    break;

  case 157: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 680 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1312 "dhcp6_parser.cc"
    break;

  case 158: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 686 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1322 "dhcp6_parser.cc"
    break;

  case 159: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 692 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1332 "dhcp6_parser.cc"
    break;

  case 160: // $@22: %empty
#line 698 "dhcp6_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1341 "dhcp6_parser.cc"
    break;

  case 161: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 701 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1350 "dhcp6_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "when-present"
#line 707 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1358 "dhcp6_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "never"
#line 710 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1366 "dhcp6_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "always"
#line 713 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1374 "dhcp6_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "when-not-present"
#line 716 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1382 "dhcp6_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "boolean"
#line 719 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1391 "dhcp6_parser.cc"
    break;

  case 167: // $@23: %empty
#line 725 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1400 "dhcp6_parser.cc"
    break;

  case 168: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 728 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1410 "dhcp6_parser.cc"
    break;

  case 169: // $@24: %empty
#line 734 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1419 "dhcp6_parser.cc"
    break;

  case 170: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 737 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1429 "dhcp6_parser.cc"
    break;

  case 171: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 743 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1439 "dhcp6_parser.cc"
    break;

  case 172: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 752 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.warning(yystack_[1].location, "ddns-use-conflict-resolution is deprecated. "
             "Substituting ddns-conflict-resolution-mode");
    ElementPtr mode(new StringElement(b->boolValue() ? "check-with-dhcid"
                                      : "no-check-with-dhcid"));
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", mode);
}
#line 1453 "dhcp6_parser.cc"
    break;

  case 173: // $@25: %empty
#line 762 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1462 "dhcp6_parser.cc"
    break;

  case 174: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 765 "dhcp6_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1471 "dhcp6_parser.cc"
    break;

  case 175: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 771 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1479 "dhcp6_parser.cc"
    break;

  case 176: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 774 "dhcp6_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1487 "dhcp6_parser.cc"
    break;

  case 177: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 777 "dhcp6_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1495 "dhcp6_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 780 "dhcp6_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1503 "dhcp6_parser.cc"
    break;

  case 179: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 785 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1513 "dhcp6_parser.cc"
    break;

  case 180: // $@26: %empty
#line 791 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1522 "dhcp6_parser.cc"
    break;

  case 181: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 794 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1532 "dhcp6_parser.cc"
    break;

  case 182: // $@27: %empty
#line 800 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1541 "dhcp6_parser.cc"
    break;

  case 183: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 803 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1551 "dhcp6_parser.cc"
    break;

  case 184: // store_extended_info: "store-extended-info" ":" "boolean"
#line 809 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1561 "dhcp6_parser.cc"
    break;

  case 185: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 815 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1571 "dhcp6_parser.cc"
    break;

  case 186: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 821 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1581 "dhcp6_parser.cc"
    break;

  case 187: // $@28: %empty
#line 827 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1590 "dhcp6_parser.cc"
    break;

  case 188: // server_tag: "server-tag" $@28 ":" "constant string"
#line 830 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1600 "dhcp6_parser.cc"
    break;

  case 189: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 836 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1610 "dhcp6_parser.cc"
    break;

  case 190: // $@29: %empty
#line 842 "dhcp6_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1619 "dhcp6_parser.cc"
    break;

  case 191: // allocator: "allocator" $@29 ":" "constant string"
#line 845 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1629 "dhcp6_parser.cc"
    break;

  case 192: // $@30: %empty
#line 851 "dhcp6_parser.yy"
                           {
    ctx.unique("pd-allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1638 "dhcp6_parser.cc"
    break;

  case 193: // pd_allocator: "pd-allocator" $@30 ":" "constant string"
#line 854 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-allocator", al);
    ctx.leave();
}
#line 1648 "dhcp6_parser.cc"
    break;

  case 194: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 860 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1658 "dhcp6_parser.cc"
    break;

  case 195: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 866 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1668 "dhcp6_parser.cc"
    break;

  case 196: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 872 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1678 "dhcp6_parser.cc"
    break;

  case 197: // $@31: %empty
#line 878 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1690 "dhcp6_parser.cc"
    break;

  case 198: // interfaces_config: "interfaces-config" $@31 ":" "{" interfaces_config_params "}"
#line 884 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1700 "dhcp6_parser.cc"
    break;

  case 199: // $@32: %empty
#line 890 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1710 "dhcp6_parser.cc"
    break;

  case 200: // sub_interfaces6: "{" $@32 interfaces_config_params "}"
#line 894 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1719 "dhcp6_parser.cc"
    break;

  case 203: // interfaces_config_params: interfaces_config_params ","
#line 901 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1727 "dhcp6_parser.cc"
    break;

  case 212: // $@33: %empty
#line 916 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1739 "dhcp6_parser.cc"
    break;

  case 213: // interfaces_list: "interfaces" $@33 ":" list_strings
#line 922 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1748 "dhcp6_parser.cc"
    break;

  case 214: // re_detect: "re-detect" ":" "boolean"
#line 927 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1758 "dhcp6_parser.cc"
    break;

  case 215: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 933 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1768 "dhcp6_parser.cc"
    break;

  case 216: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 939 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1778 "dhcp6_parser.cc"
    break;

  case 217: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 945 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1788 "dhcp6_parser.cc"
    break;

  case 218: // $@34: %empty
#line 951 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1800 "dhcp6_parser.cc"
    break;

  case 219: // lease_database: "lease-database" $@34 ":" "{" database_map_params "}"
#line 957 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1811 "dhcp6_parser.cc"
    break;

  case 220: // $@35: %empty
#line 964 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1823 "dhcp6_parser.cc"
    break;

  case 221: // hosts_database: "hosts-database" $@35 ":" "{" database_map_params "}"
#line 970 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1834 "dhcp6_parser.cc"
    break;

  case 222: // $@36: %empty
#line 977 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1846 "dhcp6_parser.cc"
    break;

  case 223: // hosts_databases: "hosts-databases" $@36 ":" "[" database_list "]"
#line 983 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1855 "dhcp6_parser.cc"
    break;

  case 228: // not_empty_database_list: not_empty_database_list ","
#line 994 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1863 "dhcp6_parser.cc"
    break;

  case 229: // $@37: %empty
#line 999 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1873 "dhcp6_parser.cc"
    break;

  case 230: // database: "{" $@37 database_map_params "}"
#line 1003 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1883 "dhcp6_parser.cc"
    break;

  case 233: // database_map_params: database_map_params ","
#line 1011 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1891 "dhcp6_parser.cc"
    break;

  case 257: // $@38: %empty
#line 1041 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1900 "dhcp6_parser.cc"
    break;

  case 258: // database_type: "type" $@38 ":" db_type
#line 1044 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1909 "dhcp6_parser.cc"
    break;

  case 259: // db_type: "memfile"
#line 1049 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1915 "dhcp6_parser.cc"
    break;

  case 260: // db_type: "mysql"
#line 1050 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1921 "dhcp6_parser.cc"
    break;

  case 261: // db_type: "postgresql"
#line 1051 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1927 "dhcp6_parser.cc"
    break;

  case 262: // $@39: %empty
#line 1054 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1936 "dhcp6_parser.cc"
    break;

  case 263: // user: "user" $@39 ":" "constant string"
#line 1057 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1946 "dhcp6_parser.cc"
    break;

  case 264: // $@40: %empty
#line 1063 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1955 "dhcp6_parser.cc"
    break;

  case 265: // password: "password" $@40 ":" "constant string"
#line 1066 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1965 "dhcp6_parser.cc"
    break;

  case 266: // $@41: %empty
#line 1072 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1974 "dhcp6_parser.cc"
    break;

  case 267: // host: "host" $@41 ":" "constant string"
#line 1075 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1984 "dhcp6_parser.cc"
    break;

  case 268: // port: "port" ":" "integer"
#line 1081 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1994 "dhcp6_parser.cc"
    break;

  case 269: // $@42: %empty
#line 1087 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2003 "dhcp6_parser.cc"
    break;

  case 270: // name: "name" $@42 ":" "constant string"
#line 1090 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2013 "dhcp6_parser.cc"
    break;

  case 271: // persist: "persist" ":" "boolean"
#line 1096 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2023 "dhcp6_parser.cc"
    break;

  case 272: // lfc_interval: "lfc-interval" ":" "integer"
#line 1102 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2033 "dhcp6_parser.cc"
    break;

  case 273: // readonly: "readonly" ":" "boolean"
#line 1108 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2043 "dhcp6_parser.cc"
    break;

  case 274: // connect_timeout: "connect-timeout" ":" "integer"
#line 1114 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2053 "dhcp6_parser.cc"
    break;

  case 275: // read_timeout: "read-timeout" ":" "integer"
#line 1120 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2063 "dhcp6_parser.cc"
    break;

  case 276: // write_timeout: "write-timeout" ":" "integer"
#line 1126 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2073 "dhcp6_parser.cc"
    break;

  case 277: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1132 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2083 "dhcp6_parser.cc"
    break;

  case 278: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1139 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2093 "dhcp6_parser.cc"
    break;

  case 279: // $@43: %empty
#line 1145 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2102 "dhcp6_parser.cc"
    break;

  case 280: // on_fail: "on-fail" $@43 ":" on_fail_mode
#line 1148 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2111 "dhcp6_parser.cc"
    break;

  case 281: // on_fail_mode: "stop-retry-exit"
#line 1153 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2117 "dhcp6_parser.cc"
    break;

  case 282: // on_fail_mode: "serve-retry-exit"
#line 1154 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2123 "dhcp6_parser.cc"
    break;

  case 283: // on_fail_mode: "serve-retry-continue"
#line 1155 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2129 "dhcp6_parser.cc"
    break;

  case 284: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1158 "dhcp6_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2139 "dhcp6_parser.cc"
    break;

  case 285: // max_row_errors: "max-row-errors" ":" "integer"
#line 1164 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2149 "dhcp6_parser.cc"
    break;

  case 286: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1170 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2159 "dhcp6_parser.cc"
    break;

  case 287: // $@44: %empty
#line 1176 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2168 "dhcp6_parser.cc"
    break;

  case 288: // trust_anchor: "trust-anchor" $@44 ":" "constant string"
#line 1179 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2178 "dhcp6_parser.cc"
    break;

  case 289: // $@45: %empty
#line 1185 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2187 "dhcp6_parser.cc"
    break;

  case 290: // cert_file: "cert-file" $@45 ":" "constant string"
#line 1188 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2197 "dhcp6_parser.cc"
    break;

  case 291: // $@46: %empty
#line 1194 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2206 "dhcp6_parser.cc"
    break;

  case 292: // key_file: "key-file" $@46 ":" "constant string"
#line 1197 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2216 "dhcp6_parser.cc"
    break;

  case 293: // $@47: %empty
#line 1203 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2225 "dhcp6_parser.cc"
    break;

  case 294: // cipher_list: "cipher-list" $@47 ":" "constant string"
#line 1206 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2235 "dhcp6_parser.cc"
    break;

  case 295: // $@48: %empty
#line 1212 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 2247 "dhcp6_parser.cc"
    break;

  case 296: // sanity_checks: "sanity-checks" $@48 ":" "{" sanity_checks_params "}"
#line 1218 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2256 "dhcp6_parser.cc"
    break;

  case 299: // sanity_checks_params: sanity_checks_params ","
#line 1225 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2264 "dhcp6_parser.cc"
    break;

  case 302: // $@49: %empty
#line 1234 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2273 "dhcp6_parser.cc"
    break;

  case 303: // lease_checks: "lease-checks" $@49 ":" "constant string"
#line 1237 "dhcp6_parser.yy"
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
#line 2293 "dhcp6_parser.cc"
    break;

  case 304: // $@50: %empty
#line 1253 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2302 "dhcp6_parser.cc"
    break;

  case 305: // extended_info_checks: "extended-info-checks" $@50 ":" "constant string"
#line 1256 "dhcp6_parser.yy"
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
#line 2321 "dhcp6_parser.cc"
    break;

  case 306: // $@51: %empty
#line 1271 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2333 "dhcp6_parser.cc"
    break;

  case 307: // mac_sources: "mac-sources" $@51 ":" "[" mac_sources_list "]"
#line 1277 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2342 "dhcp6_parser.cc"
    break;

  case 310: // mac_sources_list: mac_sources_list ","
#line 1284 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2350 "dhcp6_parser.cc"
    break;

  case 313: // duid_id: "duid"
#line 1293 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2359 "dhcp6_parser.cc"
    break;

  case 314: // string_id: "constant string"
#line 1298 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2368 "dhcp6_parser.cc"
    break;

  case 315: // $@52: %empty
#line 1303 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2380 "dhcp6_parser.cc"
    break;

  case 316: // host_reservation_identifiers: "host-reservation-identifiers" $@52 ":" "[" host_reservation_identifiers_list "]"
#line 1309 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2389 "dhcp6_parser.cc"
    break;

  case 319: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1316 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2397 "dhcp6_parser.cc"
    break;

  case 323: // hw_address_id: "hw-address"
#line 1326 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2406 "dhcp6_parser.cc"
    break;

  case 324: // flex_id: "flex-id"
#line 1331 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2415 "dhcp6_parser.cc"
    break;

  case 325: // $@53: %empty
#line 1338 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2427 "dhcp6_parser.cc"
    break;

  case 326: // relay_supplied_options: "relay-supplied-options" $@53 ":" "[" list_content "]"
#line 1344 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2436 "dhcp6_parser.cc"
    break;

  case 327: // $@54: %empty
#line 1351 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2448 "dhcp6_parser.cc"
    break;

  case 328: // dhcp_multi_threading: "multi-threading" $@54 ":" "{" multi_threading_params "}"
#line 1357 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2459 "dhcp6_parser.cc"
    break;

  case 331: // multi_threading_params: multi_threading_params ","
#line 1366 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2467 "dhcp6_parser.cc"
    break;

  case 338: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1379 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2477 "dhcp6_parser.cc"
    break;

  case 339: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1385 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2487 "dhcp6_parser.cc"
    break;

  case 340: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1391 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2497 "dhcp6_parser.cc"
    break;

  case 341: // $@55: %empty
#line 1397 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2509 "dhcp6_parser.cc"
    break;

  case 342: // hooks_libraries: "hooks-libraries" $@55 ":" "[" hooks_libraries_list "]"
#line 1403 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2518 "dhcp6_parser.cc"
    break;

  case 347: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1414 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2526 "dhcp6_parser.cc"
    break;

  case 348: // $@56: %empty
#line 1419 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2536 "dhcp6_parser.cc"
    break;

  case 349: // hooks_library: "{" $@56 hooks_params "}"
#line 1423 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2546 "dhcp6_parser.cc"
    break;

  case 350: // $@57: %empty
#line 1429 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2556 "dhcp6_parser.cc"
    break;

  case 351: // sub_hooks_library: "{" $@57 hooks_params "}"
#line 1433 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2566 "dhcp6_parser.cc"
    break;

  case 354: // hooks_params: hooks_params ","
#line 1441 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2574 "dhcp6_parser.cc"
    break;

  case 358: // $@58: %empty
#line 1451 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2583 "dhcp6_parser.cc"
    break;

  case 359: // library: "library" $@58 ":" "constant string"
#line 1454 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2593 "dhcp6_parser.cc"
    break;

  case 360: // $@59: %empty
#line 1460 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2602 "dhcp6_parser.cc"
    break;

  case 361: // parameters: "parameters" $@59 ":" map_value
#line 1463 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2611 "dhcp6_parser.cc"
    break;

  case 362: // $@60: %empty
#line 1469 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2623 "dhcp6_parser.cc"
    break;

  case 363: // expired_leases_processing: "expired-leases-processing" $@60 ":" "{" expired_leases_params "}"
#line 1475 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2633 "dhcp6_parser.cc"
    break;

  case 366: // expired_leases_params: expired_leases_params ","
#line 1483 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2641 "dhcp6_parser.cc"
    break;

  case 373: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1496 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2651 "dhcp6_parser.cc"
    break;

  case 374: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1502 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2661 "dhcp6_parser.cc"
    break;

  case 375: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1508 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2671 "dhcp6_parser.cc"
    break;

  case 376: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1514 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2681 "dhcp6_parser.cc"
    break;

  case 377: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1520 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2691 "dhcp6_parser.cc"
    break;

  case 378: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1526 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2701 "dhcp6_parser.cc"
    break;

  case 379: // $@61: %empty
#line 1535 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2713 "dhcp6_parser.cc"
    break;

  case 380: // subnet6_list: "subnet6" $@61 ":" "[" subnet6_list_content "]"
#line 1541 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2722 "dhcp6_parser.cc"
    break;

  case 385: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1555 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2730 "dhcp6_parser.cc"
    break;

  case 386: // $@62: %empty
#line 1564 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2740 "dhcp6_parser.cc"
    break;

  case 387: // subnet6: "{" $@62 subnet6_params "}"
#line 1568 "dhcp6_parser.yy"
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
#line 2766 "dhcp6_parser.cc"
    break;

  case 388: // $@63: %empty
#line 1590 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2776 "dhcp6_parser.cc"
    break;

  case 389: // sub_subnet6: "{" $@63 subnet6_params "}"
#line 1594 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2786 "dhcp6_parser.cc"
    break;

  case 392: // subnet6_params: subnet6_params ","
#line 1603 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2794 "dhcp6_parser.cc"
    break;

  case 439: // $@64: %empty
#line 1657 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2803 "dhcp6_parser.cc"
    break;

  case 440: // subnet: "subnet" $@64 ":" "constant string"
#line 1660 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2813 "dhcp6_parser.cc"
    break;

  case 441: // $@65: %empty
#line 1666 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2822 "dhcp6_parser.cc"
    break;

  case 442: // interface: "interface" $@65 ":" "constant string"
#line 1669 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2832 "dhcp6_parser.cc"
    break;

  case 443: // $@66: %empty
#line 1675 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2841 "dhcp6_parser.cc"
    break;

  case 444: // interface_id: "interface-id" $@66 ":" "constant string"
#line 1678 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2851 "dhcp6_parser.cc"
    break;

  case 445: // $@67: %empty
#line 1684 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2860 "dhcp6_parser.cc"
    break;

  case 446: // client_class: "client-class" $@67 ":" "constant string"
#line 1687 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2870 "dhcp6_parser.cc"
    break;

  case 447: // $@68: %empty
#line 1693 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2882 "dhcp6_parser.cc"
    break;

  case 448: // require_client_classes: "require-client-classes" $@68 ":" list_strings
#line 1699 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2891 "dhcp6_parser.cc"
    break;

  case 449: // reservations_global: "reservations-global" ":" "boolean"
#line 1704 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2901 "dhcp6_parser.cc"
    break;

  case 450: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1710 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2911 "dhcp6_parser.cc"
    break;

  case 451: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1716 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2921 "dhcp6_parser.cc"
    break;

  case 452: // id: "id" ":" "integer"
#line 1722 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2931 "dhcp6_parser.cc"
    break;

  case 453: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1728 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2941 "dhcp6_parser.cc"
    break;

  case 454: // $@69: %empty
#line 1736 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2953 "dhcp6_parser.cc"
    break;

  case 455: // shared_networks: "shared-networks" $@69 ":" "[" shared_networks_content "]"
#line 1742 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2962 "dhcp6_parser.cc"
    break;

  case 460: // shared_networks_list: shared_networks_list ","
#line 1755 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2970 "dhcp6_parser.cc"
    break;

  case 461: // $@70: %empty
#line 1760 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2980 "dhcp6_parser.cc"
    break;

  case 462: // shared_network: "{" $@70 shared_network_params "}"
#line 1764 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2988 "dhcp6_parser.cc"
    break;

  case 465: // shared_network_params: shared_network_params ","
#line 1770 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2996 "dhcp6_parser.cc"
    break;

  case 509: // $@71: %empty
#line 1824 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 3008 "dhcp6_parser.cc"
    break;

  case 510: // option_def_list: "option-def" $@71 ":" "[" option_def_list_content "]"
#line 1830 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3017 "dhcp6_parser.cc"
    break;

  case 511: // $@72: %empty
#line 1838 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3026 "dhcp6_parser.cc"
    break;

  case 512: // sub_option_def_list: "{" $@72 option_def_list "}"
#line 1841 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 3034 "dhcp6_parser.cc"
    break;

  case 517: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1853 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3042 "dhcp6_parser.cc"
    break;

  case 518: // $@73: %empty
#line 1860 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3052 "dhcp6_parser.cc"
    break;

  case 519: // option_def_entry: "{" $@73 option_def_params "}"
#line 1864 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3064 "dhcp6_parser.cc"
    break;

  case 520: // $@74: %empty
#line 1875 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3074 "dhcp6_parser.cc"
    break;

  case 521: // sub_option_def: "{" $@74 option_def_params "}"
#line 1879 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3086 "dhcp6_parser.cc"
    break;

  case 526: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1895 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3094 "dhcp6_parser.cc"
    break;

  case 538: // code: "code" ":" "integer"
#line 1914 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3104 "dhcp6_parser.cc"
    break;

  case 540: // $@75: %empty
#line 1922 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3113 "dhcp6_parser.cc"
    break;

  case 541: // option_def_type: "type" $@75 ":" "constant string"
#line 1925 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3123 "dhcp6_parser.cc"
    break;

  case 542: // $@76: %empty
#line 1931 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3132 "dhcp6_parser.cc"
    break;

  case 543: // option_def_record_types: "record-types" $@76 ":" "constant string"
#line 1934 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3142 "dhcp6_parser.cc"
    break;

  case 544: // $@77: %empty
#line 1940 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3151 "dhcp6_parser.cc"
    break;

  case 545: // space: "space" $@77 ":" "constant string"
#line 1943 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3161 "dhcp6_parser.cc"
    break;

  case 547: // $@78: %empty
#line 1951 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3170 "dhcp6_parser.cc"
    break;

  case 548: // option_def_encapsulate: "encapsulate" $@78 ":" "constant string"
#line 1954 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3180 "dhcp6_parser.cc"
    break;

  case 549: // option_def_array: "array" ":" "boolean"
#line 1960 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3190 "dhcp6_parser.cc"
    break;

  case 550: // $@79: %empty
#line 1970 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3202 "dhcp6_parser.cc"
    break;

  case 551: // option_data_list: "option-data" $@79 ":" "[" option_data_list_content "]"
#line 1976 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3211 "dhcp6_parser.cc"
    break;

  case 556: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1991 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3219 "dhcp6_parser.cc"
    break;

  case 557: // $@80: %empty
#line 1998 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3229 "dhcp6_parser.cc"
    break;

  case 558: // option_data_entry: "{" $@80 option_data_params "}"
#line 2002 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3238 "dhcp6_parser.cc"
    break;

  case 559: // $@81: %empty
#line 2010 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3248 "dhcp6_parser.cc"
    break;

  case 560: // sub_option_data: "{" $@81 option_data_params "}"
#line 2014 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3257 "dhcp6_parser.cc"
    break;

  case 565: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2030 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3265 "dhcp6_parser.cc"
    break;

  case 577: // $@82: %empty
#line 2051 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3274 "dhcp6_parser.cc"
    break;

  case 578: // option_data_data: "data" $@82 ":" "constant string"
#line 2054 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3284 "dhcp6_parser.cc"
    break;

  case 581: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2064 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3294 "dhcp6_parser.cc"
    break;

  case 582: // option_data_always_send: "always-send" ":" "boolean"
#line 2070 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3304 "dhcp6_parser.cc"
    break;

  case 583: // option_data_never_send: "never-send" ":" "boolean"
#line 2076 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3314 "dhcp6_parser.cc"
    break;

  case 584: // $@83: %empty
#line 2085 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3326 "dhcp6_parser.cc"
    break;

  case 585: // pools_list: "pools" $@83 ":" "[" pools_list_content "]"
#line 2091 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3335 "dhcp6_parser.cc"
    break;

  case 590: // not_empty_pools_list: not_empty_pools_list ","
#line 2104 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3343 "dhcp6_parser.cc"
    break;

  case 591: // $@84: %empty
#line 2109 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3353 "dhcp6_parser.cc"
    break;

  case 592: // pool_list_entry: "{" $@84 pool_params "}"
#line 2113 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3363 "dhcp6_parser.cc"
    break;

  case 593: // $@85: %empty
#line 2119 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3373 "dhcp6_parser.cc"
    break;

  case 594: // sub_pool6: "{" $@85 pool_params "}"
#line 2123 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3383 "dhcp6_parser.cc"
    break;

  case 597: // pool_params: pool_params ","
#line 2131 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3391 "dhcp6_parser.cc"
    break;

  case 606: // $@86: %empty
#line 2146 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3400 "dhcp6_parser.cc"
    break;

  case 607: // pool_entry: "pool" $@86 ":" "constant string"
#line 2149 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3410 "dhcp6_parser.cc"
    break;

  case 608: // pool_id: "pool-id" ":" "integer"
#line 2155 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3420 "dhcp6_parser.cc"
    break;

  case 609: // $@87: %empty
#line 2161 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3428 "dhcp6_parser.cc"
    break;

  case 610: // user_context: "user-context" $@87 ":" map_value
#line 2163 "dhcp6_parser.yy"
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
#line 3455 "dhcp6_parser.cc"
    break;

  case 611: // $@88: %empty
#line 2186 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3463 "dhcp6_parser.cc"
    break;

  case 612: // comment: "comment" $@88 ":" "constant string"
#line 2188 "dhcp6_parser.yy"
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
#line 3492 "dhcp6_parser.cc"
    break;

  case 613: // $@89: %empty
#line 2216 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3504 "dhcp6_parser.cc"
    break;

  case 614: // pd_pools_list: "pd-pools" $@89 ":" "[" pd_pools_list_content "]"
#line 2222 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3513 "dhcp6_parser.cc"
    break;

  case 619: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2235 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3521 "dhcp6_parser.cc"
    break;

  case 620: // $@90: %empty
#line 2240 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3531 "dhcp6_parser.cc"
    break;

  case 621: // pd_pool_entry: "{" $@90 pd_pool_params "}"
#line 2244 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3543 "dhcp6_parser.cc"
    break;

  case 622: // $@91: %empty
#line 2252 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3553 "dhcp6_parser.cc"
    break;

  case 623: // sub_pd_pool: "{" $@91 pd_pool_params "}"
#line 2256 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3565 "dhcp6_parser.cc"
    break;

  case 626: // pd_pool_params: pd_pool_params ","
#line 2266 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3573 "dhcp6_parser.cc"
    break;

  case 639: // $@92: %empty
#line 2285 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3582 "dhcp6_parser.cc"
    break;

  case 640: // pd_prefix: "prefix" $@92 ":" "constant string"
#line 2288 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3592 "dhcp6_parser.cc"
    break;

  case 641: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2294 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3602 "dhcp6_parser.cc"
    break;

  case 642: // $@93: %empty
#line 2300 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3611 "dhcp6_parser.cc"
    break;

  case 643: // excluded_prefix: "excluded-prefix" $@93 ":" "constant string"
#line 2303 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3621 "dhcp6_parser.cc"
    break;

  case 644: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2309 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3631 "dhcp6_parser.cc"
    break;

  case 645: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2315 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3641 "dhcp6_parser.cc"
    break;

  case 646: // $@94: %empty
#line 2324 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3653 "dhcp6_parser.cc"
    break;

  case 647: // reservations: "reservations" $@94 ":" "[" reservations_list "]"
#line 2330 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3662 "dhcp6_parser.cc"
    break;

  case 652: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2341 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3670 "dhcp6_parser.cc"
    break;

  case 653: // $@95: %empty
#line 2346 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3680 "dhcp6_parser.cc"
    break;

  case 654: // reservation: "{" $@95 reservation_params "}"
#line 2350 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3689 "dhcp6_parser.cc"
    break;

  case 655: // $@96: %empty
#line 2355 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3699 "dhcp6_parser.cc"
    break;

  case 656: // sub_reservation: "{" $@96 reservation_params "}"
#line 2359 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3708 "dhcp6_parser.cc"
    break;

  case 661: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2370 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3716 "dhcp6_parser.cc"
    break;

  case 673: // $@97: %empty
#line 2389 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3728 "dhcp6_parser.cc"
    break;

  case 674: // ip_addresses: "ip-addresses" $@97 ":" list_strings
#line 2395 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3737 "dhcp6_parser.cc"
    break;

  case 675: // $@98: %empty
#line 2400 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3749 "dhcp6_parser.cc"
    break;

  case 676: // prefixes: "prefixes" $@98 ":" list_strings
#line 2406 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3758 "dhcp6_parser.cc"
    break;

  case 677: // $@99: %empty
#line 2411 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3767 "dhcp6_parser.cc"
    break;

  case 678: // duid: "duid" $@99 ":" "constant string"
#line 2414 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3777 "dhcp6_parser.cc"
    break;

  case 679: // $@100: %empty
#line 2420 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3786 "dhcp6_parser.cc"
    break;

  case 680: // hw_address: "hw-address" $@100 ":" "constant string"
#line 2423 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3796 "dhcp6_parser.cc"
    break;

  case 681: // $@101: %empty
#line 2429 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3805 "dhcp6_parser.cc"
    break;

  case 682: // hostname: "hostname" $@101 ":" "constant string"
#line 2432 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3815 "dhcp6_parser.cc"
    break;

  case 683: // $@102: %empty
#line 2438 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3824 "dhcp6_parser.cc"
    break;

  case 684: // flex_id_value: "flex-id" $@102 ":" "constant string"
#line 2441 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3834 "dhcp6_parser.cc"
    break;

  case 685: // $@103: %empty
#line 2447 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3846 "dhcp6_parser.cc"
    break;

  case 686: // reservation_client_classes: "client-classes" $@103 ":" list_strings
#line 2453 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3855 "dhcp6_parser.cc"
    break;

  case 687: // $@104: %empty
#line 2461 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3867 "dhcp6_parser.cc"
    break;

  case 688: // relay: "relay" $@104 ":" "{" relay_map "}"
#line 2467 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3876 "dhcp6_parser.cc"
    break;

  case 690: // $@105: %empty
#line 2478 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3888 "dhcp6_parser.cc"
    break;

  case 691: // client_classes: "client-classes" $@105 ":" "[" client_classes_list "]"
#line 2484 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3897 "dhcp6_parser.cc"
    break;

  case 694: // client_classes_list: client_classes_list ","
#line 2491 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3905 "dhcp6_parser.cc"
    break;

  case 695: // $@106: %empty
#line 2496 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3915 "dhcp6_parser.cc"
    break;

  case 696: // client_class_entry: "{" $@106 client_class_params "}"
#line 2500 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3925 "dhcp6_parser.cc"
    break;

  case 701: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2512 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3933 "dhcp6_parser.cc"
    break;

  case 717: // $@107: %empty
#line 2535 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3942 "dhcp6_parser.cc"
    break;

  case 718: // client_class_test: "test" $@107 ":" "constant string"
#line 2538 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3952 "dhcp6_parser.cc"
    break;

  case 719: // $@108: %empty
#line 2544 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3961 "dhcp6_parser.cc"
    break;

  case 720: // client_class_template_test: "template-test" $@108 ":" "constant string"
#line 2547 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3971 "dhcp6_parser.cc"
    break;

  case 721: // only_if_required: "only-if-required" ":" "boolean"
#line 2553 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3981 "dhcp6_parser.cc"
    break;

  case 722: // $@109: %empty
#line 2562 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3993 "dhcp6_parser.cc"
    break;

  case 723: // server_id: "server-id" $@109 ":" "{" server_id_params "}"
#line 2568 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4004 "dhcp6_parser.cc"
    break;

  case 726: // server_id_params: server_id_params ","
#line 2577 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4012 "dhcp6_parser.cc"
    break;

  case 736: // $@110: %empty
#line 2593 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 4021 "dhcp6_parser.cc"
    break;

  case 737: // server_id_type: "type" $@110 ":" duid_type
#line 2596 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4030 "dhcp6_parser.cc"
    break;

  case 738: // duid_type: "LLT"
#line 2601 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4036 "dhcp6_parser.cc"
    break;

  case 739: // duid_type: "EN"
#line 2602 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4042 "dhcp6_parser.cc"
    break;

  case 740: // duid_type: "LL"
#line 2603 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4048 "dhcp6_parser.cc"
    break;

  case 741: // htype: "htype" ":" "integer"
#line 2606 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4058 "dhcp6_parser.cc"
    break;

  case 742: // $@111: %empty
#line 2612 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4067 "dhcp6_parser.cc"
    break;

  case 743: // identifier: "identifier" $@111 ":" "constant string"
#line 2615 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4077 "dhcp6_parser.cc"
    break;

  case 744: // time: "time" ":" "integer"
#line 2621 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4087 "dhcp6_parser.cc"
    break;

  case 745: // enterprise_id: "enterprise-id" ":" "integer"
#line 2627 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4097 "dhcp6_parser.cc"
    break;

  case 746: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2635 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4107 "dhcp6_parser.cc"
    break;

  case 747: // $@112: %empty
#line 2643 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4120 "dhcp6_parser.cc"
    break;

  case 748: // control_socket: "control-socket" $@112 ":" "{" control_socket_params "}"
#line 2650 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4129 "dhcp6_parser.cc"
    break;

  case 749: // $@113: %empty
#line 2655 "dhcp6_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4142 "dhcp6_parser.cc"
    break;

  case 750: // control_sockets: "control-sockets" $@113 ":" "[" control_socket_list "]"
#line 2662 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4151 "dhcp6_parser.cc"
    break;

  case 755: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2673 "dhcp6_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4159 "dhcp6_parser.cc"
    break;

  case 756: // $@114: %empty
#line 2678 "dhcp6_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4169 "dhcp6_parser.cc"
    break;

  case 757: // control_socket_entry: "{" $@114 control_socket_params "}"
#line 2682 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4177 "dhcp6_parser.cc"
    break;

  case 760: // control_socket_params: control_socket_params ","
#line 2688 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4185 "dhcp6_parser.cc"
    break;

  case 773: // $@115: %empty
#line 2707 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4194 "dhcp6_parser.cc"
    break;

  case 774: // control_socket_type: "socket-type" $@115 ":" control_socket_type_value
#line 2710 "dhcp6_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4203 "dhcp6_parser.cc"
    break;

  case 775: // control_socket_type_value: "unix"
#line 2716 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4209 "dhcp6_parser.cc"
    break;

  case 776: // control_socket_type_value: "http"
#line 2717 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4215 "dhcp6_parser.cc"
    break;

  case 777: // control_socket_type_value: "https"
#line 2718 "dhcp6_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4221 "dhcp6_parser.cc"
    break;

  case 778: // $@116: %empty
#line 2721 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4231 "dhcp6_parser.cc"
    break;

  case 779: // control_socket_name: "socket-name" $@116 ":" "constant string"
#line 2725 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4241 "dhcp6_parser.cc"
    break;

  case 780: // $@117: %empty
#line 2731 "dhcp6_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4251 "dhcp6_parser.cc"
    break;

  case 781: // control_socket_address: "socket-address" $@117 ":" "constant string"
#line 2735 "dhcp6_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4261 "dhcp6_parser.cc"
    break;

  case 782: // control_socket_port: "socket-port" ":" "integer"
#line 2741 "dhcp6_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4271 "dhcp6_parser.cc"
    break;

  case 783: // cert_required: "cert-required" ":" "boolean"
#line 2747 "dhcp6_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4281 "dhcp6_parser.cc"
    break;

  case 784: // $@118: %empty
#line 2755 "dhcp6_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4293 "dhcp6_parser.cc"
    break;

  case 785: // authentication: "authentication" $@118 ":" "{" auth_params "}"
#line 2761 "dhcp6_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4304 "dhcp6_parser.cc"
    break;

  case 788: // auth_params: auth_params ","
#line 2770 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4312 "dhcp6_parser.cc"
    break;

  case 796: // $@119: %empty
#line 2784 "dhcp6_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4321 "dhcp6_parser.cc"
    break;

  case 797: // auth_type: "type" $@119 ":" auth_type_value
#line 2787 "dhcp6_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4330 "dhcp6_parser.cc"
    break;

  case 798: // auth_type_value: "basic"
#line 2792 "dhcp6_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4336 "dhcp6_parser.cc"
    break;

  case 799: // $@120: %empty
#line 2795 "dhcp6_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4345 "dhcp6_parser.cc"
    break;

  case 800: // realm: "realm" $@120 ":" "constant string"
#line 2798 "dhcp6_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4355 "dhcp6_parser.cc"
    break;

  case 801: // $@121: %empty
#line 2804 "dhcp6_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4364 "dhcp6_parser.cc"
    break;

  case 802: // directory: "directory" $@121 ":" "constant string"
#line 2807 "dhcp6_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4374 "dhcp6_parser.cc"
    break;

  case 803: // $@122: %empty
#line 2813 "dhcp6_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4386 "dhcp6_parser.cc"
    break;

  case 804: // clients: "clients" $@122 ":" "[" clients_list "]"
#line 2819 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4395 "dhcp6_parser.cc"
    break;

  case 809: // not_empty_clients_list: not_empty_clients_list ","
#line 2830 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4403 "dhcp6_parser.cc"
    break;

  case 810: // $@123: %empty
#line 2835 "dhcp6_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4413 "dhcp6_parser.cc"
    break;

  case 811: // basic_auth: "{" $@123 clients_params "}"
#line 2839 "dhcp6_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4421 "dhcp6_parser.cc"
    break;

  case 814: // clients_params: clients_params ","
#line 2845 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4429 "dhcp6_parser.cc"
    break;

  case 822: // $@124: %empty
#line 2859 "dhcp6_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4438 "dhcp6_parser.cc"
    break;

  case 823: // user_file: "user-file" $@124 ":" "constant string"
#line 2862 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4448 "dhcp6_parser.cc"
    break;

  case 824: // $@125: %empty
#line 2868 "dhcp6_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4457 "dhcp6_parser.cc"
    break;

  case 825: // password_file: "password-file" $@125 ":" "constant string"
#line 2871 "dhcp6_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4467 "dhcp6_parser.cc"
    break;

  case 826: // $@126: %empty
#line 2879 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4479 "dhcp6_parser.cc"
    break;

  case 827: // dhcp_queue_control: "dhcp-queue-control" $@126 ":" "{" queue_control_params "}"
#line 2885 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4490 "dhcp6_parser.cc"
    break;

  case 830: // queue_control_params: queue_control_params ","
#line 2894 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4498 "dhcp6_parser.cc"
    break;

  case 837: // enable_queue: "enable-queue" ":" "boolean"
#line 2907 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4508 "dhcp6_parser.cc"
    break;

  case 838: // $@127: %empty
#line 2913 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4517 "dhcp6_parser.cc"
    break;

  case 839: // queue_type: "queue-type" $@127 ":" "constant string"
#line 2916 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4527 "dhcp6_parser.cc"
    break;

  case 840: // capacity: "capacity" ":" "integer"
#line 2922 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4537 "dhcp6_parser.cc"
    break;

  case 841: // $@128: %empty
#line 2928 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4546 "dhcp6_parser.cc"
    break;

  case 842: // arbitrary_map_entry: "constant string" $@128 ":" value
#line 2931 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4555 "dhcp6_parser.cc"
    break;

  case 843: // $@129: %empty
#line 2938 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4567 "dhcp6_parser.cc"
    break;

  case 844: // dhcp_ddns: "dhcp-ddns" $@129 ":" "{" dhcp_ddns_params "}"
#line 2944 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4578 "dhcp6_parser.cc"
    break;

  case 845: // $@130: %empty
#line 2951 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4588 "dhcp6_parser.cc"
    break;

  case 846: // sub_dhcp_ddns: "{" $@130 dhcp_ddns_params "}"
#line 2955 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4598 "dhcp6_parser.cc"
    break;

  case 849: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2963 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4606 "dhcp6_parser.cc"
    break;

  case 861: // enable_updates: "enable-updates" ":" "boolean"
#line 2981 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4616 "dhcp6_parser.cc"
    break;

  case 862: // $@131: %empty
#line 2987 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4625 "dhcp6_parser.cc"
    break;

  case 863: // server_ip: "server-ip" $@131 ":" "constant string"
#line 2990 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4635 "dhcp6_parser.cc"
    break;

  case 864: // server_port: "server-port" ":" "integer"
#line 2996 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4645 "dhcp6_parser.cc"
    break;

  case 865: // $@132: %empty
#line 3002 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4654 "dhcp6_parser.cc"
    break;

  case 866: // sender_ip: "sender-ip" $@132 ":" "constant string"
#line 3005 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4664 "dhcp6_parser.cc"
    break;

  case 867: // sender_port: "sender-port" ":" "integer"
#line 3011 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4674 "dhcp6_parser.cc"
    break;

  case 868: // max_queue_size: "max-queue-size" ":" "integer"
#line 3017 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4684 "dhcp6_parser.cc"
    break;

  case 869: // $@133: %empty
#line 3023 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4693 "dhcp6_parser.cc"
    break;

  case 870: // ncr_protocol: "ncr-protocol" $@133 ":" ncr_protocol_value
#line 3026 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4702 "dhcp6_parser.cc"
    break;

  case 871: // ncr_protocol_value: "UDP"
#line 3032 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4708 "dhcp6_parser.cc"
    break;

  case 872: // ncr_protocol_value: "TCP"
#line 3033 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4714 "dhcp6_parser.cc"
    break;

  case 873: // $@134: %empty
#line 3036 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4723 "dhcp6_parser.cc"
    break;

  case 874: // ncr_format: "ncr-format" $@134 ":" "JSON"
#line 3039 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4733 "dhcp6_parser.cc"
    break;

  case 875: // $@135: %empty
#line 3047 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4745 "dhcp6_parser.cc"
    break;

  case 876: // config_control: "config-control" $@135 ":" "{" config_control_params "}"
#line 3053 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4755 "dhcp6_parser.cc"
    break;

  case 877: // $@136: %empty
#line 3059 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4765 "dhcp6_parser.cc"
    break;

  case 878: // sub_config_control: "{" $@136 config_control_params "}"
#line 3063 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4774 "dhcp6_parser.cc"
    break;

  case 881: // config_control_params: config_control_params ","
#line 3071 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4782 "dhcp6_parser.cc"
    break;

  case 884: // $@137: %empty
#line 3081 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4794 "dhcp6_parser.cc"
    break;

  case 885: // config_databases: "config-databases" $@137 ":" "[" database_list "]"
#line 3087 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4803 "dhcp6_parser.cc"
    break;

  case 886: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3092 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4813 "dhcp6_parser.cc"
    break;

  case 887: // $@138: %empty
#line 3100 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4825 "dhcp6_parser.cc"
    break;

  case 888: // loggers: "loggers" $@138 ":" "[" loggers_entries "]"
#line 3106 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4834 "dhcp6_parser.cc"
    break;

  case 891: // loggers_entries: loggers_entries ","
#line 3115 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4842 "dhcp6_parser.cc"
    break;

  case 892: // $@139: %empty
#line 3121 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4852 "dhcp6_parser.cc"
    break;

  case 893: // logger_entry: "{" $@139 logger_params "}"
#line 3125 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4860 "dhcp6_parser.cc"
    break;

  case 896: // logger_params: logger_params ","
#line 3131 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4868 "dhcp6_parser.cc"
    break;

  case 904: // debuglevel: "debuglevel" ":" "integer"
#line 3145 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4878 "dhcp6_parser.cc"
    break;

  case 905: // $@140: %empty
#line 3151 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4887 "dhcp6_parser.cc"
    break;

  case 906: // severity: "severity" $@140 ":" "constant string"
#line 3154 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4897 "dhcp6_parser.cc"
    break;

  case 907: // $@141: %empty
#line 3160 "dhcp6_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4909 "dhcp6_parser.cc"
    break;

  case 908: // output_options_list: "output-options" $@141 ":" "[" output_options_list_content "]"
#line 3166 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4918 "dhcp6_parser.cc"
    break;

  case 911: // output_options_list_content: output_options_list_content ","
#line 3173 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4926 "dhcp6_parser.cc"
    break;

  case 912: // $@142: %empty
#line 3178 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4936 "dhcp6_parser.cc"
    break;

  case 913: // output_entry: "{" $@142 output_params_list "}"
#line 3182 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4944 "dhcp6_parser.cc"
    break;

  case 916: // output_params_list: output_params_list ","
#line 3188 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4952 "dhcp6_parser.cc"
    break;

  case 922: // $@143: %empty
#line 3200 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4961 "dhcp6_parser.cc"
    break;

  case 923: // output: "output" $@143 ":" "constant string"
#line 3203 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4971 "dhcp6_parser.cc"
    break;

  case 924: // flush: "flush" ":" "boolean"
#line 3209 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4981 "dhcp6_parser.cc"
    break;

  case 925: // maxsize: "maxsize" ":" "integer"
#line 3215 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4991 "dhcp6_parser.cc"
    break;

  case 926: // maxver: "maxver" ":" "integer"
#line 3221 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5001 "dhcp6_parser.cc"
    break;

  case 927: // $@144: %empty
#line 3227 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5010 "dhcp6_parser.cc"
    break;

  case 928: // pattern: "pattern" $@144 ":" "constant string"
#line 3230 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5020 "dhcp6_parser.cc"
    break;

  case 929: // $@145: %empty
#line 3236 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5032 "dhcp6_parser.cc"
    break;

  case 930: // compatibility: "compatibility" $@145 ":" "{" compatibility_params "}"
#line 3242 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5041 "dhcp6_parser.cc"
    break;

  case 933: // compatibility_params: compatibility_params ","
#line 3249 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5049 "dhcp6_parser.cc"
    break;

  case 936: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3258 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5059 "dhcp6_parser.cc"
    break;


#line 5063 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1350;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
      -9, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350,    69,    32,    66,    81,   113,
     122,   124,   176,   188,   251,   270,   272,   279,   282,   291,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,    32,  -139,
     143,   175,    58,   684,   336,   256,   399,   239,    91,   311,
     -86,   455,    51, -1350,   155,   318,   346,   314,   341, -1350,
      45, -1350, -1350, -1350, -1350, -1350, -1350, -1350,   366,   369,
     376,   395,   417,   419,   421,   428,   448,   449,   458,   459,
     465,   471, -1350,   474,   480,   482,   483,   486, -1350, -1350,
   -1350,   496,   507,   509,   517, -1350, -1350, -1350,   520, -1350,
   -1350, -1350, -1350, -1350, -1350,   524,   525,   526, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350,   533, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350,   537,   538,   540, -1350, -1350,
     541, -1350,    63, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350,   542,   543,   544,   547, -1350,    64, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350,   549,   550, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350,   102, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350,   552, -1350, -1350, -1350,
   -1350,   120, -1350, -1350, -1350, -1350, -1350, -1350,   553, -1350,
     554,   555, -1350, -1350, -1350, -1350, -1350, -1350, -1350,   127,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350,   345,   411, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350,   435, -1350, -1350,
     557, -1350, -1350, -1350,   564, -1350, -1350,   442,   433, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350,   565,   567,   568, -1350, -1350, -1350, -1350,   570,
     572, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350,   138, -1350, -1350, -1350,   569, -1350,
     577, -1350,   578,   579, -1350, -1350, -1350, -1350, -1350,   144,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
     582,   146, -1350, -1350, -1350, -1350,    32,    32, -1350,   358,
     584, -1350, -1350,   589,   590,   591,   593,   594,   595,   370,
     371,   374,   375,   377,   380,   381,   382,   383,   385,   386,
     387,   391,   392,   619,   394,   400,   401,   402,   403,   623,
     625,   627,   404,   405,   416,   406,   644,   645,   646,   424,
     647,   652,   667,   668,   669,   676,   450,   453,   454,   677,
     683,   685,   689,   690,   692,   693,   694,   696,   472,   697,
     699,   700,   701,   702,   703,   704,   456,   477,   479,   709,
     710, -1350,   175, -1350,   711,   484,   485,   491,   494,    58,
   -1350,   721,   722,   723,   724,   725,   500,   499,   728,   729,
     744,   684, -1350,   745,   521,   336, -1350,   746,   532,   759,
     535,   536,   256, -1350,   763,   764,   768,   771,   775,   776,
     777, -1350,   399, -1350,   778,   779,   558,   781,   783,   785,
     559, -1350,    91,   786,   571,   573,   574, -1350,   311,   798,
     800,   -34, -1350,   575,   804,   580,   807,   586,   587,   808,
     810,   455, -1350,   814,   596,    51, -1350, -1350, -1350,   815,
     813,   592,   816,   817,   818,   820,   823, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350,   600, -1350, -1350, -1350, -1350, -1350,  -137,   601,   602,
   -1350, -1350, -1350, -1350,   827,   828,   829, -1350,   606,   607,
     361,   832,   831,   610, -1350, -1350, -1350,   835,   836,   837,
     838,   839,   841,   842,   843,   844, -1350,   845,   846,   849,
     848,   850,   614,   620, -1350, -1350, -1350,   851,   852, -1350,
     855, -1350, -1350, -1350, -1350, -1350,   856,   857,   634,   635,
     636, -1350, -1350,   855,   637,   860, -1350,   639, -1350, -1350,
     640, -1350,   641, -1350, -1350, -1350,   855,   855,   855,   642,
     643,   648,   649, -1350,   650,   651, -1350,   653,   656,   657,
   -1350, -1350,   658, -1350, -1350, -1350, -1350,   659,   831, -1350,
   -1350,   660, -1350,   661, -1350, -1350,   -53,   654, -1350,   868,
   -1350, -1350,    32,   175, -1350,    51,    58,   629,   629,   867,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,   869,
     874,   884, -1350, -1350, -1350, -1350, -1350, -1350, -1350,   885,
   -1350, -1350, -1350,   -87,    32,   333,    47,   886,   887,   888,
     157,    68,   -58,   260,   889,   226,   455, -1350, -1350,   890,
    -144, -1350, -1350,   891,   892, -1350, -1350, -1350, -1350, -1350,
     743, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350,   867, -1350,   160,   170,   181,
   -1350, -1350, -1350, -1350,   896,   897,   898,   899,   900,   901,
     902,   903,   904,   905, -1350,   906,   907, -1350, -1350, -1350,
   -1350, -1350,   217, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350,   257, -1350,   908,   909,
   -1350, -1350,   910,   912, -1350, -1350,   911,   915, -1350, -1350,
     913,   917, -1350, -1350,   916,   918, -1350, -1350, -1350,    93,
   -1350, -1350, -1350,   919, -1350, -1350, -1350,   111, -1350, -1350,
   -1350, -1350, -1350,   267, -1350, -1350, -1350, -1350,   154, -1350,
   -1350,   920,   921, -1350, -1350,   922,   924, -1350,   925,   926,
     927,   928,   929,   930,   268, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350,   931,   932,   933, -1350, -1350, -1350,
   -1350,   307, -1350, -1350, -1350, -1350, -1350, -1350,   934,   935,
     936, -1350,   308, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350,   937, -1350,   938, -1350, -1350, -1350, -1350, -1350,
   -1350,   338, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
     939,   940, -1350,   942, -1350,   943, -1350, -1350, -1350,   340,
   -1350, -1350, -1350, -1350, -1350,   349, -1350,   179, -1350,   944,
   -1350,   363, -1350, -1350,   715, -1350,   945,   946, -1350, -1350,
     947,   949, -1350, -1350,   948,   951, -1350, -1350, -1350,   950,
     954,   955,   956,   720,   691,   731,   730,   733,   734,   736,
     737,   739,   740,   968,   749,   748,   971,   979,   980,   983,
     629, -1350, -1350,   629, -1350,   867,   684, -1350,   869,    91,
   -1350,   874,   311, -1350,   884,  1093, -1350,   885,   -87, -1350,
   -1350,   333, -1350,   986,   991,    47, -1350,   275,   886, -1350,
     399, -1350,   887,   -86, -1350,   888,   770,   774,   780,   788,
     792,   796,   157, -1350,   994,   997,   802,   805,   809,    68,
   -1350,   773,   825,   834,   -58, -1350,  1003,  1007,  1012,   847,
    1039,   830,   260, -1350,   260, -1350,   889,   871,  1044,   952,
    1055,   226, -1350, -1350,   204,   890, -1350,   883,  -144, -1350,
   -1350,  1068,  1123,   336, -1350,   891,   256, -1350,   892, -1350,
   -1350,   447,   726,   914,   959, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350,   347, -1350, -1350,   960,   961,
     962,   963, -1350,   364, -1350,   379, -1350,  1122, -1350,  1124,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
     397, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,   964,
     965, -1350, -1350, -1350,  1127, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350,  1125,  1133, -1350, -1350,
   -1350, -1350, -1350, -1350,  1129, -1350,   407, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350,   343,   966, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350,   351,   967,   969, -1350,  1131,
   -1350, -1350,   410, -1350, -1350,   970, -1350,    32, -1350, -1350,
    1135, -1350, -1350, -1350, -1350, -1350,   414, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350,   982,   431, -1350,   432, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,  1093,
   -1350, -1350, -1350,  1136,  1137,   981, -1350,   275, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350,    28, -1350, -1350, -1350,  1138,   953,  1153,   204, -1350,
   -1350, -1350, -1350, -1350,   985,   987, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350,   439, -1350, -1350, -1350, -1350,
   -1350,  1154, -1350,   988, -1350, -1350, -1350,  1156,  1168,  1171,
    1172,    28, -1350,  1151, -1350,  1005,   990,   992,  1173, -1350,
   -1350,   253, -1350, -1350, -1350, -1350, -1350,  1174,   -18,  1151,
   -1350, -1350,  1178,  1176, -1350, -1350,  1208,  1211,  1216, -1350,
     443, -1350, -1350, -1350, -1350, -1350, -1350, -1350,    96, -1350,
    1174,  1219,   993,   996,   999,  1220,   -18, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350,   446, -1350, -1350, -1350, -1350,
     998, -1350, -1350, -1350,  1001, -1350,  1228,  1230,    96, -1350,
   -1350, -1350,  1006,  1008, -1350, -1350, -1350
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    46,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    61,     5,    67,     7,   199,     9,   388,    11,
     593,    13,   622,    15,   655,    17,   511,    19,   520,    21,
     559,    23,   350,    25,   845,    27,   877,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   657,     0,   522,   561,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   141,   875,   197,   218,   220,   222,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   187,     0,     0,     0,     0,     0,   160,   167,
     169,     0,     0,     0,     0,   379,   509,   550,     0,   190,
     192,   173,   454,   609,   611,     0,     0,     0,   306,   325,
     315,   295,   690,   646,   341,   362,   722,     0,   327,   747,
     749,   826,   843,   180,   182,     0,     0,     0,   887,   929,
       0,   140,     0,    69,    72,    73,    74,    75,    76,    77,
      78,    79,    80,   111,   112,   113,   114,   115,    81,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   117,
     118,   129,   130,   131,   107,   137,   138,   139,   133,   134,
     135,    84,    85,    86,    87,   104,    88,    90,    89,   132,
      94,    95,    82,   108,   109,   110,    83,    92,    93,   102,
     103,   105,    91,    96,    97,    98,    99,   100,   101,   106,
     116,   136,   212,     0,     0,     0,     0,   211,     0,   201,
     204,   205,   206,   207,   208,   209,   210,   584,   613,   439,
     441,   443,     0,     0,   447,   445,   687,   438,   393,   394,
     395,   396,   397,   398,   399,   400,   418,   419,   420,   421,
     422,   425,   426,   427,   428,   429,   430,   431,   432,   433,
     434,   423,   424,   435,   436,   437,     0,   390,   404,   405,
     406,   409,   410,   412,   413,   414,   407,   408,   401,   402,
     416,   417,   403,   411,   415,   606,     0,   605,   601,   602,
     600,     0,   595,   598,   599,   603,   604,   639,     0,   642,
       0,     0,   638,   632,   633,   631,   630,   636,   637,     0,
     624,   627,   628,   634,   635,   629,   685,   673,   675,   677,
     679,   681,   683,   672,   669,   670,   671,     0,   658,   659,
     664,   665,   662,   666,   667,   668,   663,     0,   540,   269,
       0,   544,   542,   547,     0,   536,   537,     0,   523,   524,
     527,   539,   528,   529,   530,   546,   531,   532,   533,   534,
     535,   577,     0,     0,     0,   575,   576,   579,   580,     0,
     562,   563,   566,   567,   568,   569,   570,   571,   572,   573,
     574,   358,   360,   355,     0,   352,   356,   357,     0,   862,
       0,   865,     0,     0,   869,   873,   860,   858,   859,     0,
     847,   850,   851,   852,   853,   854,   855,   856,   857,   884,
       0,     0,   879,   882,   883,    47,    52,     0,    39,    45,
       0,    66,    62,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    60,    71,    68,     0,     0,     0,     0,     0,   203,
     200,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   392,   389,     0,     0,   597,   594,     0,     0,     0,
       0,     0,   626,   623,     0,     0,     0,     0,     0,     0,
       0,   656,   661,   512,     0,     0,     0,     0,     0,     0,
       0,   521,   526,     0,     0,     0,     0,   560,   565,     0,
       0,   354,   351,     0,     0,     0,     0,     0,     0,     0,
       0,   849,   846,     0,     0,   881,   878,    51,    43,     0,
       0,     0,     0,     0,     0,     0,     0,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,     0,   185,   186,   157,   158,   159,     0,     0,     0,
     171,   172,   179,   184,     0,     0,     0,   189,     0,     0,
       0,     0,     0,     0,   449,   450,   451,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   746,     0,     0,     0,
       0,     0,     0,     0,   194,   195,   196,     0,     0,    70,
       0,   214,   215,   216,   217,   202,     0,     0,     0,     0,
       0,   452,   453,     0,     0,     0,   391,     0,   608,   596,
       0,   641,     0,   644,   645,   625,     0,     0,     0,     0,
       0,     0,     0,   660,     0,     0,   538,     0,     0,     0,
     549,   525,     0,   581,   582,   583,   564,     0,     0,   353,
     861,     0,   864,     0,   867,   868,     0,     0,   848,     0,
     886,   880,     0,     0,   142,     0,     0,     0,     0,   224,
     188,   162,   163,   164,   165,   166,   161,   168,   170,   381,
     513,   552,   191,   193,   175,   176,   177,   178,   174,   456,
      40,   610,   612,     0,    48,     0,     0,     0,   648,   343,
       0,     0,     0,     0,   751,     0,     0,   181,   183,     0,
       0,    53,   213,   586,   615,   440,   442,   444,   448,   446,
       0,   607,   640,   643,   686,   674,   676,   678,   680,   682,
     684,   541,   270,   545,   543,   548,   578,   359,   361,   863,
     866,   871,   872,   870,   874,   224,    44,     0,     0,     0,
     257,   262,   264,   266,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   279,     0,     0,   287,   289,   291,
     293,   256,     0,   231,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   248,   249,   250,
     251,   247,   252,   253,   254,   255,     0,   229,     0,   225,
     226,   386,     0,   382,   383,   518,     0,   514,   515,   557,
       0,   553,   554,   461,     0,   457,   458,   313,   314,     0,
     308,   311,   312,     0,   323,   324,   320,     0,   317,   321,
     322,   302,   304,     0,   297,   300,   301,   695,     0,   692,
     653,     0,   649,   650,   348,     0,   344,   345,     0,     0,
       0,     0,     0,     0,     0,   364,   367,   368,   369,   370,
     371,   372,   736,   742,     0,     0,     0,   735,   732,   733,
     734,     0,   724,   727,   730,   728,   729,   731,     0,     0,
       0,   337,     0,   329,   332,   333,   334,   335,   336,   773,
     778,   780,     0,   784,     0,   772,   766,   767,   768,   770,
     771,     0,   758,   761,   762,   763,   764,   769,   765,   756,
       0,   752,   753,     0,   838,     0,   841,   834,   835,     0,
     828,   831,   832,   833,   836,     0,   892,     0,   889,     0,
     935,     0,   931,   934,    55,   591,     0,   587,   588,   620,
       0,   616,   617,   689,     0,     0,    64,   876,   198,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     233,   219,   221,     0,   223,   228,     0,   380,   385,   522,
     510,   517,   561,   551,   556,     0,   455,   460,   310,   307,
     326,   319,   316,     0,     0,   299,   296,   697,   694,   691,
     657,   647,   652,     0,   342,   347,     0,     0,     0,     0,
       0,     0,   366,   363,     0,     0,     0,     0,     0,   726,
     723,     0,     0,     0,   331,   328,     0,     0,     0,     0,
       0,     0,   760,   748,     0,   750,   755,     0,     0,     0,
       0,   830,   827,   844,     0,   891,   888,     0,   933,   930,
      57,     0,    56,     0,   585,   590,     0,   614,   619,   688,
     885,     0,     0,     0,     0,   268,   271,   272,   273,   274,
     275,   276,   277,   286,   278,     0,   284,   285,     0,     0,
       0,     0,   232,     0,   227,     0,   384,     0,   516,     0,
     555,   508,   479,   480,   481,   483,   484,   485,   470,   471,
     488,   489,   490,   491,   492,   495,   496,   497,   498,   499,
     500,   501,   502,   503,   504,   493,   494,   505,   506,   507,
     466,   467,   468,   469,   477,   478,   474,   475,   476,   482,
       0,   463,   472,   486,   487,   473,   459,   309,   318,     0,
       0,   298,   717,   719,     0,   715,   709,   710,   711,   712,
     713,   714,   716,   706,   707,   708,     0,   698,   699,   702,
     703,   704,   705,   693,     0,   651,     0,   346,   373,   374,
     375,   376,   377,   378,   365,     0,     0,   741,   744,   745,
     725,   338,   339,   340,   330,     0,     0,     0,   782,     0,
     783,   759,     0,   754,   837,     0,   840,     0,   829,   907,
       0,   905,   903,   897,   901,   902,     0,   894,   899,   900,
     898,   890,   936,   932,    54,    59,     0,   589,     0,   618,
     259,   260,   261,   258,   263,   265,   267,   281,   282,   283,
     280,   288,   290,   292,   294,   230,   387,   519,   558,   465,
     462,   303,   305,     0,     0,     0,   696,   701,   654,   349,
     738,   739,   740,   737,   743,   775,   776,   777,   774,   779,
     781,     0,   757,   839,   842,     0,     0,     0,   896,   893,
      58,   592,   621,   464,     0,     0,   721,   700,   796,   799,
     801,   803,   795,   794,   793,     0,   786,   789,   790,   791,
     792,     0,   904,     0,   895,   718,   720,     0,     0,     0,
       0,   788,   785,     0,   906,     0,     0,     0,     0,   787,
     912,     0,   909,   798,   797,   800,   802,   805,     0,   911,
     908,   810,     0,   806,   807,   922,     0,     0,     0,   927,
       0,   914,   917,   918,   919,   920,   921,   910,     0,   804,
     809,     0,     0,     0,     0,     0,   916,   913,   822,   824,
     821,   815,   817,   819,   820,     0,   812,   816,   818,   808,
       0,   924,   925,   926,     0,   915,     0,     0,   814,   811,
     923,   928,     0,     0,   813,   823,   825
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350,   -10, -1350,  -590, -1350,
     530, -1350, -1350, -1350, -1350,   426, -1350,  -575, -1350, -1350,
   -1350,   -71, -1350, -1350, -1350, -1350, -1350, -1350, -1350,   516,
     732, -1350, -1350,   -48,   -33,   -11,    -5,    18,    21,   -51,
     -17,   -16,    24,    31,    35,    36, -1350,    43,    46,    48,
      49, -1350, -1350,    53, -1350,    54, -1350,    59,    60,    61,
   -1350, -1350,    65,    71, -1350,    72, -1350,    75, -1350, -1350,
   -1350, -1350, -1350,    77, -1350,    78, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350,   514,   727, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,   437, -1350,
     208, -1350,  -710,   215, -1350, -1350, -1350, -1349, -1350, -1335,
   -1350, -1350, -1350, -1350,   -66, -1350,  -740, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
    -752, -1350,  -747, -1350,  -743, -1350, -1350, -1350, -1350, -1350,
   -1350,   194, -1350, -1350, -1350, -1350, -1350, -1350, -1350,   205,
    -732, -1350, -1350, -1350, -1350,   201, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350,   171, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350,   189, -1350, -1350, -1350,   195,   705, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350,   191, -1350, -1350, -1350, -1350, -1350,
   -1350, -1021, -1350, -1350, -1350,   222, -1350, -1350, -1350,   225,
     741, -1350, -1350, -1019, -1350, -1018, -1350,    84, -1350,    90,
   -1350,    82,    83,    89, -1350, -1017, -1350, -1350, -1350, -1350,
     218, -1350, -1350,   -32,  1191, -1350, -1350, -1350, -1350, -1350,
     229, -1350, -1350, -1350,   232, -1350,   713, -1350,   -65, -1350,
   -1350, -1350, -1350, -1350,   -62, -1350, -1350, -1350, -1350, -1350,
     -30, -1350, -1350, -1350,   235, -1350, -1350, -1350,   231, -1350,
     712, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350,   166, -1350, -1350, -1350,   173,   752, -1350,
   -1350,   -60,   -43, -1350,     8, -1350, -1350, -1350, -1350, -1350,
     177, -1350, -1350, -1350,   168,   747, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350,   -54, -1350, -1350, -1350,   236, -1350, -1350,
   -1350,   237, -1350,   751,   511, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1011, -1350,
   -1350, -1350, -1350, -1350,   241, -1350, -1350, -1350,    -7, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,   227, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350,   209, -1350,   207,   212, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
     -52, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350,   -92, -1350, -1350,  -118, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350,   210, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350,   546,   735, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350,   588,   753, -1350, -1350, -1350, -1350, -1350,
   -1350,   214, -1350, -1350,   -14, -1350, -1350, -1350, -1350, -1350,
   -1350,   -55, -1350, -1350,   -85, -1350, -1350, -1350, -1350, -1350,
   -1350, -1350, -1350, -1350, -1350,   223, -1350
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     751,    87,    88,    41,    68,    84,    85,   772,   994,  1111,
    1112,   831,    43,    70,    90,   440,    91,    45,    71,   162,
     163,   164,   443,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   469,   736,   183,   470,   184,   471,   185,   186,   187,
     482,   748,   188,   189,   504,   190,   505,   191,   192,   193,
     194,   463,   195,   196,   480,   197,   481,   198,   199,   200,
     201,   445,    47,    72,   238,   239,   240,   514,   241,   242,
     243,   244,   202,   446,   203,   447,   204,   448,   858,   859,
     860,  1033,   832,   833,   834,  1009,  1283,   835,  1010,   836,
    1011,   837,  1012,   838,   839,   555,   840,   841,   842,   843,
     844,   845,   846,   847,   848,  1023,  1290,   849,   850,   851,
     852,  1026,   853,  1027,   854,  1028,   855,  1029,   205,   492,
     893,   894,   895,  1053,   896,  1054,   206,   489,   879,   880,
     881,   882,   207,   491,   887,   888,   889,   890,   208,   490,
     209,   499,   942,   943,   944,   945,   946,   210,   495,   905,
     906,   907,  1063,    63,    80,   404,   405,   406,   569,   407,
     570,   211,   496,   914,   915,   916,   917,   918,   919,   920,
     921,   212,   476,   862,   863,   864,  1036,    49,    73,   286,
     287,   288,   523,   289,   524,   290,   525,   291,   529,   292,
     528,   213,   214,   215,   296,   297,   216,   483,   874,   875,
     876,  1045,  1190,  1191,   217,   477,    57,    77,   866,   867,
     868,  1039,    59,    78,   367,   368,   369,   370,   371,   372,
     373,   554,   374,   558,   375,   557,   376,   377,   559,   378,
     218,   478,   870,   871,   872,  1042,    61,    79,   389,   390,
     391,   392,   393,   563,   394,   395,   396,   397,   398,   299,
     521,   996,   997,   998,  1113,    51,    74,   311,   312,   313,
     533,   314,   219,   484,   220,   485,   302,   522,  1000,  1001,
    1002,  1116,    53,    75,   329,   330,   331,   537,   332,   333,
     539,   334,   335,   221,   494,   901,   902,   903,  1060,    55,
      76,   347,   348,   349,   350,   545,   351,   546,   352,   547,
     353,   548,   354,   549,   355,   550,   356,   544,   304,   530,
    1004,   222,   493,   898,   899,  1057,  1216,  1217,  1218,  1219,
    1220,  1303,  1221,  1304,  1222,   223,   497,   931,   932,   933,
    1074,  1313,   934,   935,  1075,   936,   937,   224,   225,   500,
     226,   501,   970,   971,   972,  1094,   961,   962,   963,  1086,
    1318,   964,  1087,   965,  1088,   966,   967,   968,  1090,  1345,
    1346,  1347,  1357,  1374,  1348,  1358,  1349,  1359,  1350,  1360,
    1382,  1383,  1384,  1398,  1415,  1416,  1417,  1426,  1418,  1427,
     227,   502,   979,   980,   981,   982,  1098,   983,   984,  1100,
     228,   503,    65,    81,   419,   420,   421,   422,   574,   423,
     424,   576,   425,   426,   427,   579,   803,   428,   580,   229,
     444,    67,    82,   431,   432,   433,   583,   434,   230,   509,
     987,   988,  1104,  1266,  1267,  1268,  1269,  1327,  1270,  1325,
    1371,  1372,  1378,  1390,  1391,  1392,  1401,  1393,  1394,  1395,
    1396,  1405,   231,   510,   991,   992,   993
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     161,   237,   257,   307,   322,   343,    38,   365,   385,   403,
     416,   956,   366,   386,   387,   326,   957,   388,   856,   303,
     958,   928,   264,   886,  1181,   258,  1182,  1183,  1189,   245,
     300,   315,   327,   345,  1195,   379,   399,    31,   417,    32,
     259,    33,   750,   298,   310,   325,   344,   877,   441,  1411,
     133,   134,  1338,   442,   401,   402,   265,   266,   731,   732,
     733,   734,   260,  1412,   429,   430,   512,   519,   261,    30,
     989,   513,   520,    42,   232,   233,   234,   235,   236,  1411,
     246,   301,   316,   328,   346,   160,   380,   400,    44,   418,
      86,   262,   922,  1412,   263,   735,  1048,   267,   778,  1049,
     815,   938,   939,   940,   268,   531,   401,   402,   269,   270,
     532,   784,   785,   786,  1051,   358,   271,  1052,   750,   272,
      46,   273,   274,   535,   811,   812,   275,   276,   536,    48,
     542,    50,   277,   278,   279,   543,   133,   134,   280,   801,
     802,   571,   878,   160,   281,   282,   572,   581,   283,   585,
     284,   285,   582,    89,   586,   293,   294,  1058,   308,   323,
    1059,   435,   295,   512,   309,   324,   133,   134,  1006,   891,
     892,   160,   359,   585,   360,   361,   133,   134,  1007,   362,
     363,   364,  1105,    52,   519,  1106,    92,    93,  1385,  1008,
      94,  1386,  1387,  1388,  1389,    54,    95,    96,    97,   133,
     134,  1339,  1340,  1341,   133,   134,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
    1030,   923,   924,   925,   926,  1031,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,  1379,   160,    56,  1380,
    1030,    34,    35,    36,    37,  1032,   128,   129,   130,   131,
    1055,  1072,  1408,  1409,   132,  1056,  1073,    58,  1181,    60,
    1182,  1183,  1189,   133,   134,   359,    62,   160,  1195,    64,
     135,   136,   137,   138,   139,   140,   141,   160,    66,   142,
     908,   909,   910,   911,   912,   913,   143,   827,   828,   829,
    1079,  1084,   133,   134,   144,  1080,  1085,   145,   126,   886,
     160,   436,   438,  1143,   146,   160,    98,    99,   100,   101,
     102,   103,   147,   148,   133,   134,   127,   149,   150,   928,
     956,  1092,   956,  1101,   439,   957,  1093,   957,  1102,   958,
     437,   958,   581,   551,   151,   127,   359,  1103,   152,   317,
     318,   319,   320,   321,   133,   134,  1108,  1030,   133,   134,
     449,  1109,  1295,   450,   153,   154,   155,   156,   157,   158,
     451,   254,   531,   133,   134,   255,   306,  1296,   159,  1287,
    1288,  1289,   359,   381,   360,   361,   382,   383,   384,   452,
    1299,  1202,  1203,  1204,   160,  1300,   973,   974,   975,  1259,
     571,  1260,  1261,  1092,   552,  1309,   127,  1328,  1322,   133,
     134,   453,  1329,   454,   949,   455,   587,   588,   950,   951,
     952,   953,   456,   160,   535,   542,   562,   305,   954,  1331,
    1332,   161,  1361,   553,   133,   134,  1406,  1362,   237,  1428,
     561,  1407,   457,   458,  1429,   976,   744,   745,   746,   747,
     257,   254,   459,   460,   307,   255,   306,   877,   884,   461,
     885,   322,  1280,  1281,  1282,   462,   245,   303,   464,   127,
     264,   343,   326,   258,   465,   160,   466,   467,   300,   160,
     468,   365,   315,  1310,  1311,  1312,   366,   385,   259,   327,
     472,   298,   386,   387,   160,   310,   388,   133,   134,   345,
     416,   473,   325,   474,   265,   266,  1315,  1316,  1317,   379,
     260,   475,   344,   336,   479,   399,   261,   246,   486,   487,
     488,   337,   338,   339,   340,   341,   342,   498,   417,   301,
     160,   506,   507,   316,   508,   511,   515,   516,   517,   262,
     328,   518,   263,   526,   527,   267,   534,   538,   540,   541,
     346,   556,   268,   133,   134,   160,   269,   270,   560,   564,
     380,   565,   566,   573,   271,   568,   400,   272,   567,   273,
     274,   575,   577,   578,   275,   276,   584,   589,   590,   418,
     277,   278,   279,   591,   592,   593,   280,   594,   595,   596,
     597,   598,   281,   282,   599,   600,   283,   601,   284,   285,
     602,   603,   604,   293,   294,   605,   606,   607,   608,   308,
     295,   609,   610,   611,   612,   309,   323,   617,   160,   618,
     613,   619,   324,   614,   615,   616,   620,   621,   623,   408,
     409,   410,   411,   412,   413,   414,   415,   622,   624,   625,
     626,   628,   161,   810,   627,   237,   629,   811,   812,   813,
     814,   815,   816,   817,   818,   819,   820,   821,   822,   823,
     824,   630,   631,   632,   825,   826,   827,   828,   829,   830,
     633,   637,   634,   245,   160,   635,   636,   638,   654,   639,
     927,   941,   955,   640,   641,   416,   642,   643,   644,   990,
     645,   647,   646,   648,   649,   650,   651,   652,   653,   655,
     359,   656,   806,   657,   658,   660,   661,   662,   929,   947,
     959,   663,   977,   417,   664,   666,   667,   668,   669,   670,
     671,   672,   673,   674,   246,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   675,   677,
     680,   678,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   681,   682,   127,   683,   684,   686,   687,   930,
     948,   960,   688,   978,   418,   689,   129,   130,   131,   690,
     691,   692,   694,   695,   247,   697,   248,   698,   696,   699,
     702,   700,   133,   134,   249,   250,   251,   252,   253,   135,
     136,   137,   707,   703,   708,   704,   705,   710,   711,   254,
     712,   713,   716,   255,   717,   143,   714,   715,   719,   722,
     723,   724,   256,   725,   726,   727,   720,   728,   729,   730,
     737,   738,   739,   740,   741,   742,   743,   749,    32,   752,
     753,   754,   755,   767,   757,   756,   758,   759,   804,   768,
     760,   761,   762,   763,   764,   765,   769,   766,   160,   770,
     771,   773,   774,   775,   776,   777,   779,   780,   781,   782,
     783,   787,   788,   805,   857,   337,   861,   789,   790,   791,
     792,   865,   793,   153,   154,   794,   795,   796,   797,   799,
     800,   869,   873,   897,   900,   904,   969,   986,   995,   999,
    1013,  1014,  1015,  1016,  1017,  1018,  1019,  1020,  1021,  1022,
    1024,  1025,  1035,   160,  1034,  1038,  1037,  1040,  1041,  1043,
    1044,  1047,  1046,  1126,  1062,  1050,  1061,  1065,  1064,  1066,
    1067,  1068,  1069,  1070,  1071,  1076,  1077,  1078,  1081,  1082,
    1083,  1089,  1091,  1096,  1110,  1095,  1097,  1099,  1107,  1115,
    1125,  1114,  1118,  1117,  1121,  1284,  1119,  1120,  1122,  1123,
    1124,  1127,  1128,  1129,  1130,   257,  1131,  1132,   365,  1133,
    1134,   385,  1135,   366,  1151,  1138,   386,   387,  1137,  1180,
     388,  1136,   303,  1139,  1140,   264,  1205,  1141,   258,   343,
    1199,  1212,   403,   300,  1158,  1200,   379,  1152,  1235,   399,
    1228,  1236,  1193,   259,  1229,  1241,   298,  1245,   927,  1206,
    1230,  1246,  1153,   941,  1214,  1192,  1247,   345,  1231,   265,
     266,   955,  1232,   955,  1207,   260,  1233,  1213,  1159,  1160,
     344,   261,  1237,  1262,  1154,  1238,   929,   990,  1263,  1239,
    1155,   947,   307,  1249,   301,   322,  1208,   380,  1255,   959,
     400,   959,  1209,  1194,   262,  1242,   326,   263,   977,  1257,
     267,  1264,  1250,  1156,  1243,  1215,  1157,   268,   346,  1161,
     315,   269,   270,   327,  1274,  1210,  1162,  1248,  1211,   271,
    1163,  1164,   272,   310,   273,   274,   325,   930,  1165,   275,
     276,  1166,   948,  1167,  1168,   277,   278,   279,  1169,  1170,
     960,   280,   960,  1254,  1171,  1172,  1173,   281,   282,   978,
    1174,   283,  1265,   284,   285,  1272,  1175,  1176,   293,   294,
    1177,   316,  1178,  1179,   328,   295,  1275,  1186,  1187,  1184,
    1297,  1305,  1298,  1306,  1188,  1185,  1307,  1308,  1321,  1326,
    1334,  1335,  1351,  1285,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,  1353,  1370,  1363,
    1365,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,  1366,   127,   359,  1367,  1368,  1373,  1377,  1400,
     883,  1381,  1256,  1352,  1399,   129,   130,   131,  1286,  1291,
    1292,  1293,  1294,  1301,  1302,  1314,  1319,   308,  1320,  1323,
     323,   133,   134,   309,   250,   251,   324,   253,   135,   136,
     137,  1330,  1402,  1336,  1355,  1403,  1356,  1364,   254,  1375,
    1404,  1376,   255,  1420,  1424,  1421,  1422,  1430,  1151,  1423,
    1431,   256,  1432,  1180,  1433,  1435,  1205,  1436,   798,   807,
     809,  1212,  1005,  1144,   659,  1142,   665,  1324,  1158,  1201,
    1342,  1152,  1198,  1197,  1227,  1244,  1193,  1262,  1226,  1206,
    1146,  1145,  1263,  1234,  1214,  1196,  1153,  1333,   357,  1192,
    1148,  1147,   676,  1149,  1207,   701,   709,  1213,  1343,  1150,
     706,  1277,  1159,  1160,  1278,  1264,  1276,   679,  1154,   685,
    1342,  1003,   153,   154,  1155,  1279,  1208,  1224,  1225,  1223,
    1337,  1252,  1209,   693,  1251,  1253,  1240,  1194,  1419,  1369,
    1434,  1258,   985,   808,  1354,  1215,   718,  1156,  1343,  1271,
    1157,  1425,   160,  1161,  1397,  1210,     0,  1410,  1211,  1344,
    1162,  1273,     0,     0,  1163,  1164,  1265,     0,   721,     0,
       0,     0,  1165,     0,     0,  1166,     0,  1167,  1168,     0,
       0,     0,  1169,  1170,     0,  1413,     0,  1410,  1171,  1172,
    1173,     0,     0,     0,  1174,     0,     0,     0,     0,  1344,
    1175,  1176,     0,     0,  1177,     0,  1178,  1179,     0,     0,
       0,  1186,  1187,  1184,     0,  1413,     0,     0,  1188,  1185,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1414,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1414
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,   763,    78,    79,    79,    75,   763,    79,   728,    73,
     763,   761,    73,   755,  1045,    73,  1045,  1045,  1045,    72,
      73,    74,    75,    76,  1045,    78,    79,     5,    81,     7,
      73,     9,   632,    73,    74,    75,    76,   134,     3,  1398,
     108,   109,    24,     8,   140,   141,    73,    73,   195,   196,
     197,   198,    73,  1398,    13,    14,     3,     3,    73,     0,
     214,     8,     8,     7,    16,    17,    18,    19,    20,  1428,
      72,    73,    74,    75,    76,   229,    78,    79,     7,    81,
     229,    73,    24,  1428,    73,   232,     3,    73,   673,     6,
      32,   159,   160,   161,    73,     3,   140,   141,    73,    73,
       8,   686,   687,   688,     3,    24,    73,     6,   708,    73,
       7,    73,    73,     3,    28,    29,    73,    73,     8,     7,
       3,     7,    73,    73,    73,     8,   108,   109,    73,   192,
     193,     3,   229,   229,    73,    73,     8,     3,    73,     3,
      73,    73,     8,    10,     8,    73,    73,     3,    74,    75,
       6,     6,    73,     3,    74,    75,   108,   109,     8,   122,
     123,   229,    81,     3,    83,    84,   108,   109,     8,    88,
      89,    90,     3,     7,     3,     6,    11,    12,   206,     8,
      15,   209,   210,   211,   212,     7,    21,    22,    23,   108,
     109,   173,   174,   175,   108,   109,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
       3,   153,   154,   155,   156,     8,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,     3,   229,     7,     6,
       3,   229,   230,   231,   232,     8,    91,    92,    93,    94,
       3,     3,   176,   177,    99,     8,     8,     7,  1299,     7,
    1299,  1299,  1299,   108,   109,    81,     7,   229,  1299,     7,
     115,   116,   117,   118,   119,   120,   121,   229,     7,   124,
     143,   144,   145,   146,   147,   148,   131,    47,    48,    49,
       3,     3,   108,   109,   139,     8,     8,   142,    79,  1051,
     229,     3,     8,  1033,   149,   229,    51,    52,    53,    54,
      55,    56,   157,   158,   108,   109,    80,   162,   163,  1079,
    1092,     3,  1094,     3,     3,  1092,     8,  1094,     8,  1092,
       4,  1094,     3,     8,   179,    80,    81,     8,   183,   103,
     104,   105,   106,   107,   108,   109,     3,     3,   108,   109,
       4,     8,     8,     4,   199,   200,   201,   202,   203,   204,
       4,   125,     3,   108,   109,   129,   130,     8,   213,    42,
      43,    44,    81,    82,    83,    84,    85,    86,    87,     4,
       3,   126,   127,   128,   229,     8,   180,   181,   182,   205,
       3,   207,   208,     3,     3,     8,    80,     3,     8,   108,
     109,     4,     8,     4,   164,     4,   436,   437,   168,   169,
     170,   171,     4,   229,     3,     3,     3,   101,   178,     8,
       8,   512,     3,     8,   108,   109,     3,     8,   519,     3,
       8,     8,     4,     4,     8,   229,    95,    96,    97,    98,
     531,   125,     4,     4,   535,   129,   130,   134,   135,     4,
     137,   542,    25,    26,    27,     4,   519,   531,     4,    80,
     531,   552,   542,   531,     4,   229,     4,     4,   531,   229,
       4,   562,   535,   150,   151,   152,   562,   568,   531,   542,
       4,   531,   568,   568,   229,   535,   568,   108,   109,   552,
     581,     4,   542,     4,   531,   531,   165,   166,   167,   562,
     531,     4,   552,   124,     4,   568,   531,   519,     4,     4,
       4,   132,   133,   134,   135,   136,   137,     4,   581,   531,
     229,     4,     4,   535,     4,     4,     4,     4,     4,   531,
     542,     4,   531,     4,     4,   531,     4,     4,     4,     4,
     552,     4,   531,   108,   109,   229,   531,   531,     4,     4,
     562,     4,     4,     4,   531,     3,   568,   531,     8,   531,
     531,     4,     4,     4,   531,   531,     4,   229,     4,   581,
     531,   531,   531,     4,     4,     4,   531,     4,     4,     4,
     230,   230,   531,   531,   230,   230,   531,   230,   531,   531,
     230,   230,   230,   531,   531,   232,   231,   231,   231,   535,
     531,   230,   230,     4,   230,   535,   542,     4,   229,     4,
     230,     4,   542,   232,   232,   232,   232,   232,   232,   184,
     185,   186,   187,   188,   189,   190,   191,   231,     4,     4,
       4,     4,   723,    24,   230,   726,     4,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,     4,     4,     4,    45,    46,    47,    48,    49,    50,
       4,     4,   232,   726,   229,   232,   232,     4,   232,     4,
     761,   762,   763,     4,     4,   766,     4,     4,     4,   770,
       4,     4,   230,     4,     4,     4,     4,     4,     4,   232,
      81,   232,   722,     4,     4,     4,   232,   232,   761,   762,
     763,   230,   765,   766,   230,     4,     4,     4,     4,     4,
     230,   232,     4,     4,   726,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,     4,     4,
       4,   230,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,   230,     4,    80,   230,   230,     4,     4,   761,
     762,   763,     4,   765,   766,     4,    92,    93,    94,     4,
       4,     4,     4,     4,   100,     4,   102,     4,   230,     4,
       4,   232,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,     4,   232,     4,   232,   232,   232,     4,   125,
     230,     4,     4,   129,     4,   131,   230,   230,     4,     4,
       7,   229,   138,     7,     7,     7,   230,     7,     5,   229,
     229,   229,     5,     5,     5,   229,   229,     5,     7,   229,
       5,     5,     5,   229,     5,     7,     5,     5,   194,   229,
       7,     7,     7,     7,     5,     7,     5,     7,   229,     7,
       5,     5,     5,   229,   229,   229,   229,     7,   229,   229,
     229,   229,   229,     5,     7,   132,     7,   229,   229,   229,
     229,     7,   229,   199,   200,   229,   229,   229,   229,   229,
     229,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     3,   229,     6,     3,     6,     6,     3,     6,
       3,     3,     6,   232,     3,     6,     6,     3,     6,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     3,   229,     6,     4,     4,     4,     3,
     230,     6,     3,     6,     4,   229,     8,     6,     4,     4,
       4,   230,   232,   230,   230,  1036,   230,   230,  1039,   230,
     230,  1042,     4,  1039,  1045,     4,  1042,  1042,   230,  1045,
    1042,   232,  1036,     4,     4,  1036,  1057,     4,  1036,  1060,
       4,  1057,  1063,  1036,  1045,     4,  1039,  1045,     4,  1042,
     230,     4,  1045,  1036,   230,   232,  1036,     4,  1079,  1057,
     230,     4,  1045,  1084,  1057,  1045,     4,  1060,   230,  1036,
    1036,  1092,   230,  1094,  1057,  1036,   230,  1057,  1045,  1045,
    1060,  1036,   230,  1104,  1045,   230,  1079,  1108,  1104,   230,
    1045,  1084,  1113,     4,  1036,  1116,  1057,  1039,     4,  1092,
    1042,  1094,  1057,  1045,  1036,   230,  1116,  1036,  1101,     4,
    1036,  1104,   232,  1045,   230,  1057,  1045,  1036,  1060,  1045,
    1113,  1036,  1036,  1116,     6,  1057,  1045,   230,  1057,  1036,
    1045,  1045,  1036,  1113,  1036,  1036,  1116,  1079,  1045,  1036,
    1036,  1045,  1084,  1045,  1045,  1036,  1036,  1036,  1045,  1045,
    1092,  1036,  1094,   232,  1045,  1045,  1045,  1036,  1036,  1101,
    1045,  1036,  1104,  1036,  1036,   232,  1045,  1045,  1036,  1036,
    1045,  1113,  1045,  1045,  1116,  1036,     3,  1045,  1045,  1045,
       8,     4,     8,     8,  1045,  1045,     3,     8,     7,     4,
       4,     4,     4,   229,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,     4,     7,     5,
       4,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,     4,    80,    81,     4,     4,   172,     5,     3,
     754,     7,   230,   230,     6,    92,    93,    94,   229,   229,
     229,   229,   229,   229,   229,   229,   229,  1113,   229,   229,
    1116,   108,   109,  1113,   111,   112,  1116,   114,   115,   116,
     117,   229,     4,   232,   229,     4,   229,   229,   125,   229,
       4,   229,   129,     4,     4,   232,   230,   229,  1299,   230,
     229,   138,     4,  1299,     4,   229,  1307,   229,   708,   723,
     726,  1307,   805,  1035,   512,  1030,   519,  1257,  1299,  1055,
    1321,  1299,  1051,  1048,  1065,  1084,  1299,  1328,  1063,  1307,
    1038,  1036,  1328,  1072,  1307,  1047,  1299,  1299,    77,  1299,
    1041,  1039,   531,  1042,  1307,   562,   571,  1307,  1321,  1044,
     568,  1115,  1299,  1299,  1116,  1328,  1113,   535,  1299,   542,
    1361,   780,   199,   200,  1299,  1118,  1307,  1060,  1062,  1058,
    1307,  1094,  1307,   552,  1092,  1096,  1079,  1299,  1400,  1361,
    1428,  1101,   766,   725,  1328,  1307,   581,  1299,  1361,  1105,
    1299,  1406,   229,  1299,  1379,  1307,    -1,  1398,  1307,  1321,
    1299,  1108,    -1,    -1,  1299,  1299,  1328,    -1,   585,    -1,
      -1,    -1,  1299,    -1,    -1,  1299,    -1,  1299,  1299,    -1,
      -1,    -1,  1299,  1299,    -1,  1398,    -1,  1428,  1299,  1299,
    1299,    -1,    -1,    -1,  1299,    -1,    -1,    -1,    -1,  1361,
    1299,  1299,    -1,    -1,  1299,    -1,  1299,  1299,    -1,    -1,
      -1,  1299,  1299,  1299,    -1,  1428,    -1,    -1,  1299,  1299,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1398,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1428
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
       0,     5,     7,     9,   229,   230,   231,   232,   249,   250,
     251,   256,     7,   265,     7,   270,     7,   325,     7,   440,
       7,   518,     7,   535,     7,   552,     7,   469,     7,   475,
       7,   499,     7,   416,     7,   655,     7,   674,   257,   252,
     266,   271,   326,   441,   519,   536,   553,   470,   476,   500,
     417,   656,   675,   249,   258,   259,   229,   254,   255,    10,
     267,   269,    11,    12,    15,    21,    22,    23,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    91,    92,
      93,    94,    99,   108,   109,   115,   116,   117,   118,   119,
     120,   121,   124,   131,   139,   142,   149,   157,   158,   162,
     163,   179,   183,   199,   200,   201,   202,   203,   204,   213,
     229,   264,   272,   273,   274,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   296,   298,   300,   301,   302,   305,   306,
     308,   310,   311,   312,   313,   315,   316,   318,   320,   321,
     322,   323,   335,   337,   339,   381,   389,   395,   401,   403,
     410,   424,   434,   454,   455,   456,   459,   467,   493,   525,
     527,   546,   574,   588,   600,   601,   603,   643,   653,   672,
     681,   705,    16,    17,    18,    19,    20,   264,   327,   328,
     329,   331,   332,   333,   334,   525,   527,   100,   102,   110,
     111,   112,   113,   114,   125,   129,   138,   264,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   290,   291,   292,   293,   296,   298,   300,   301,   302,
     305,   306,   308,   310,   316,   318,   442,   443,   444,   446,
     448,   450,   452,   454,   455,   456,   457,   458,   493,   512,
     525,   527,   529,   546,   571,   101,   130,   264,   450,   452,
     493,   520,   521,   522,   524,   525,   527,   103,   104,   105,
     106,   107,   264,   450,   452,   493,   524,   525,   527,   537,
     538,   539,   541,   542,   544,   545,   124,   132,   133,   134,
     135,   136,   137,   264,   493,   525,   527,   554,   555,   556,
     557,   559,   561,   563,   565,   567,   569,   467,    24,    81,
      83,    84,    88,    89,    90,   264,   357,   477,   478,   479,
     480,   481,   482,   483,   485,   487,   489,   490,   492,   525,
     527,    82,    85,    86,    87,   264,   357,   481,   487,   501,
     502,   503,   504,   505,   507,   508,   509,   510,   511,   525,
     527,   140,   141,   264,   418,   419,   420,   422,   184,   185,
     186,   187,   188,   189,   190,   191,   264,   525,   527,   657,
     658,   659,   660,   662,   663,   665,   666,   667,   670,    13,
      14,   676,   677,   678,   680,     6,     3,     4,     8,     3,
     268,     3,     8,   275,   673,   324,   336,   338,   340,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   314,     4,     4,     4,     4,     4,   294,
     297,   299,     4,     4,     4,     4,   435,   468,   494,     4,
     317,   319,   303,   460,   526,   528,     4,     4,     4,   390,
     402,   396,   382,   575,   547,   411,   425,   589,     4,   404,
     602,   604,   644,   654,   307,   309,     4,     4,     4,   682,
     706,     4,     3,     8,   330,     4,     4,     4,     4,     3,
       8,   513,   530,   445,   447,   449,     4,     4,   453,   451,
     572,     3,     8,   523,     4,     3,     8,   540,     4,   543,
       4,     4,     3,     8,   570,   558,   560,   562,   564,   566,
     568,     8,     3,     8,   484,   358,     4,   488,   486,   491,
       4,     8,     3,   506,     4,     4,     4,     8,     3,   421,
     423,     3,     8,     4,   661,     4,   664,     4,     4,   668,
     671,     3,     8,   679,     4,     3,     8,   249,   249,   229,
       4,     4,     4,     4,     4,     4,     4,   230,   230,   230,
     230,   230,   230,   230,   230,   232,   231,   231,   231,   230,
     230,     4,   230,   230,   232,   232,   232,     4,     4,     4,
     232,   232,   231,   232,     4,     4,     4,   230,     4,     4,
       4,     4,     4,     4,   232,   232,   232,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   230,     4,     4,     4,
       4,     4,     4,     4,   232,   232,   232,     4,     4,   273,
       4,   232,   232,   230,   230,   328,     4,     4,     4,     4,
       4,   230,   232,     4,     4,     4,   443,     4,   230,   521,
       4,   230,     4,   230,   230,   538,     4,     4,     4,     4,
       4,     4,     4,   556,     4,     4,   230,     4,     4,     4,
     232,   479,     4,   232,   232,   232,   503,     4,     4,   419,
     232,     4,   230,     4,   230,   230,     4,     4,   658,     4,
     230,   677,     4,     7,   229,     7,     7,     7,     7,     5,
     229,   195,   196,   197,   198,   232,   295,   229,   229,     5,
       5,     5,   229,   229,    95,    96,    97,    98,   304,     5,
     251,   253,   229,     5,     5,     5,     7,     5,     5,     5,
       7,     7,     7,     7,     5,     7,     7,   229,   229,     5,
       7,     5,   260,     5,     5,   229,   229,   229,   260,   229,
       7,   229,   229,   229,   260,   260,   260,   229,   229,   229,
     229,   229,   229,   229,   229,   229,   229,   229,   253,   229,
     229,   192,   193,   669,   194,     5,   249,   272,   676,   327,
      24,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    45,    46,    47,    48,    49,
      50,   264,   345,   346,   347,   350,   352,   354,   356,   357,
     359,   360,   361,   362,   363,   364,   365,   366,   367,   370,
     371,   372,   373,   375,   377,   379,   345,     7,   341,   342,
     343,     7,   436,   437,   438,     7,   471,   472,   473,     7,
     495,   496,   497,     7,   461,   462,   463,   134,   229,   391,
     392,   393,   394,   258,   135,   137,   393,   397,   398,   399,
     400,   122,   123,   383,   384,   385,   387,     7,   576,   577,
       7,   548,   549,   550,     7,   412,   413,   414,   143,   144,
     145,   146,   147,   148,   426,   427,   428,   429,   430,   431,
     432,   433,    24,   153,   154,   155,   156,   264,   359,   525,
     527,   590,   591,   592,   595,   596,   598,   599,   159,   160,
     161,   264,   405,   406,   407,   408,   409,   525,   527,   164,
     168,   169,   170,   171,   178,   264,   373,   375,   377,   525,
     527,   609,   610,   611,   614,   616,   618,   619,   620,     7,
     605,   606,   607,   180,   181,   182,   229,   525,   527,   645,
     646,   647,   648,   650,   651,   657,     7,   683,   684,   214,
     264,   707,   708,   709,   261,     7,   514,   515,   516,     7,
     531,   532,   533,   557,   573,   341,     8,     8,     8,   348,
     351,   353,   355,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   368,     4,     4,   374,   376,   378,   380,
       3,     8,     8,   344,     6,     3,   439,     6,     3,   474,
       6,     3,   498,     6,     3,   464,     6,     3,     3,     6,
       6,     3,     6,   386,   388,     3,     8,   578,     3,     6,
     551,     6,     3,   415,     6,     3,     4,     4,     4,     4,
       4,     4,     3,     8,   593,   597,     4,     4,     4,     3,
       8,     4,     4,     4,     3,     8,   612,   615,   617,     4,
     621,     4,     3,     8,   608,     6,     3,     4,   649,     4,
     652,     3,     8,     8,   685,     3,     6,     4,     3,     8,
     229,   262,   263,   517,     6,     3,   534,     6,     3,     8,
       6,     4,     4,     4,     4,   230,   232,   230,   232,   230,
     230,   230,   230,   230,   230,     4,   232,   230,     4,     4,
       4,     4,   346,   345,   343,   442,   438,   477,   473,   501,
     497,   264,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   290,   291,   292,   293,   296,
     298,   300,   301,   302,   305,   306,   308,   310,   316,   318,
     357,   434,   446,   448,   450,   452,   454,   455,   456,   458,
     465,   466,   493,   525,   527,   571,   463,   392,   398,     4,
       4,   384,   126,   127,   128,   264,   276,   277,   278,   279,
     280,   281,   357,   493,   525,   527,   579,   580,   581,   582,
     583,   585,   587,   577,   554,   550,   418,   414,   230,   230,
     230,   230,   230,   230,   427,     4,     4,   230,   230,   230,
     591,   232,   230,   230,   406,     4,     4,     4,   230,     4,
     232,   610,   609,   607,   232,     4,   230,     4,   646,   205,
     207,   208,   264,   357,   525,   527,   686,   687,   688,   689,
     691,   684,   232,   708,     6,     3,   520,   516,   537,   533,
      25,    26,    27,   349,   229,   229,   229,    42,    43,    44,
     369,   229,   229,   229,   229,     8,     8,     8,     8,     3,
       8,   229,   229,   584,   586,     4,     8,     3,     8,     8,
     150,   151,   152,   594,   229,   165,   166,   167,   613,   229,
     229,     7,     8,   229,   249,   692,     4,   690,     3,     8,
     229,     8,     8,   466,     4,     4,   232,   581,    24,   173,
     174,   175,   264,   525,   527,   622,   623,   624,   627,   629,
     631,     4,   230,     4,   687,   229,   229,   625,   628,   630,
     632,     3,     8,     5,   229,     4,     4,     4,     4,   623,
       7,   693,   694,   172,   626,   229,   229,     5,   695,     3,
       6,     7,   633,   634,   635,   206,   209,   210,   211,   212,
     696,   697,   698,   700,   701,   702,   703,   694,   636,     6,
       3,   699,     4,     4,     4,   704,     3,     8,   176,   177,
     264,   350,   352,   525,   527,   637,   638,   639,   641,   635,
       4,   232,   230,   230,     4,   697,   640,   642,     3,     8,
     229,   229,     4,     4,   638,   229,   229
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   233,   235,   234,   236,   234,   237,   234,   238,   234,
     239,   234,   240,   234,   241,   234,   242,   234,   243,   234,
     244,   234,   245,   234,   246,   234,   247,   234,   248,   234,
     249,   249,   249,   249,   249,   249,   249,   250,   252,   251,
     253,   254,   254,   255,   255,   255,   257,   256,   258,   258,
     259,   259,   259,   261,   260,   262,   262,   263,   263,   263,
     264,   266,   265,   268,   267,   267,   269,   271,   270,   272,
     272,   272,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   273,   273,
     273,   275,   274,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     294,   293,   295,   295,   295,   295,   295,   297,   296,   299,
     298,   300,   301,   303,   302,   304,   304,   304,   304,   305,
     307,   306,   309,   308,   310,   311,   312,   314,   313,   315,
     317,   316,   319,   318,   320,   321,   322,   324,   323,   326,
     325,   327,   327,   327,   328,   328,   328,   328,   328,   328,
     328,   328,   330,   329,   331,   332,   333,   334,   336,   335,
     338,   337,   340,   339,   341,   341,   342,   342,   342,   344,
     343,   345,   345,   345,   346,   346,   346,   346,   346,   346,
     346,   346,   346,   346,   346,   346,   346,   346,   346,   346,
     346,   346,   346,   346,   346,   346,   346,   348,   347,   349,
     349,   349,   351,   350,   353,   352,   355,   354,   356,   358,
     357,   359,   360,   361,   362,   363,   364,   365,   366,   368,
     367,   369,   369,   369,   370,   371,   372,   374,   373,   376,
     375,   378,   377,   380,   379,   382,   381,   383,   383,   383,
     384,   384,   386,   385,   388,   387,   390,   389,   391,   391,
     391,   392,   392,   393,   394,   396,   395,   397,   397,   397,
     398,   398,   398,   399,   400,   402,   401,   404,   403,   405,
     405,   405,   406,   406,   406,   406,   406,   406,   407,   408,
     409,   411,   410,   412,   412,   413,   413,   413,   415,   414,
     417,   416,   418,   418,   418,   418,   419,   419,   421,   420,
     423,   422,   425,   424,   426,   426,   426,   427,   427,   427,
     427,   427,   427,   428,   429,   430,   431,   432,   433,   435,
     434,   436,   436,   437,   437,   437,   439,   438,   441,   440,
     442,   442,   442,   443,   443,   443,   443,   443,   443,   443,
     443,   443,   443,   443,   443,   443,   443,   443,   443,   443,
     443,   443,   443,   443,   443,   443,   443,   443,   443,   443,
     443,   443,   443,   443,   443,   443,   443,   443,   443,   443,
     443,   443,   443,   443,   443,   443,   443,   443,   443,   445,
     444,   447,   446,   449,   448,   451,   450,   453,   452,   454,
     455,   456,   457,   458,   460,   459,   461,   461,   462,   462,
     462,   464,   463,   465,   465,   465,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   468,
     467,   470,   469,   471,   471,   472,   472,   472,   474,   473,
     476,   475,   477,   477,   478,   478,   478,   479,   479,   479,
     479,   479,   479,   479,   479,   479,   479,   480,   481,   482,
     484,   483,   486,   485,   488,   487,   489,   491,   490,   492,
     494,   493,   495,   495,   496,   496,   496,   498,   497,   500,
     499,   501,   501,   502,   502,   502,   503,   503,   503,   503,
     503,   503,   503,   503,   503,   503,   504,   506,   505,   507,
     508,   509,   510,   511,   513,   512,   514,   514,   515,   515,
     515,   517,   516,   519,   518,   520,   520,   520,   521,   521,
     521,   521,   521,   521,   521,   521,   523,   522,   524,   526,
     525,   528,   527,   530,   529,   531,   531,   532,   532,   532,
     534,   533,   536,   535,   537,   537,   537,   538,   538,   538,
     538,   538,   538,   538,   538,   538,   538,   538,   538,   540,
     539,   541,   543,   542,   544,   545,   547,   546,   548,   548,
     549,   549,   549,   551,   550,   553,   552,   554,   554,   555,
     555,   555,   556,   556,   556,   556,   556,   556,   556,   556,
     556,   556,   556,   558,   557,   560,   559,   562,   561,   564,
     563,   566,   565,   568,   567,   570,   569,   572,   571,   573,
     575,   574,   576,   576,   576,   578,   577,   579,   579,   580,
     580,   580,   581,   581,   581,   581,   581,   581,   581,   581,
     581,   581,   581,   581,   581,   581,   582,   584,   583,   586,
     585,   587,   589,   588,   590,   590,   590,   591,   591,   591,
     591,   591,   591,   591,   591,   591,   593,   592,   594,   594,
     594,   595,   597,   596,   598,   599,   600,   602,   601,   604,
     603,   605,   605,   606,   606,   606,   608,   607,   609,   609,
     609,   610,   610,   610,   610,   610,   610,   610,   610,   610,
     610,   610,   610,   612,   611,   613,   613,   613,   615,   614,
     617,   616,   618,   619,   621,   620,   622,   622,   622,   623,
     623,   623,   623,   623,   623,   623,   625,   624,   626,   628,
     627,   630,   629,   632,   631,   633,   633,   634,   634,   634,
     636,   635,   637,   637,   637,   638,   638,   638,   638,   638,
     638,   638,   640,   639,   642,   641,   644,   643,   645,   645,
     645,   646,   646,   646,   646,   646,   646,   647,   649,   648,
     650,   652,   651,   654,   653,   656,   655,   657,   657,   657,
     658,   658,   658,   658,   658,   658,   658,   658,   658,   658,
     658,   659,   661,   660,   662,   664,   663,   665,   666,   668,
     667,   669,   669,   671,   670,   673,   672,   675,   674,   676,
     676,   676,   677,   677,   679,   678,   680,   682,   681,   683,
     683,   683,   685,   684,   686,   686,   686,   687,   687,   687,
     687,   687,   687,   687,   688,   690,   689,   692,   691,   693,
     693,   693,   695,   694,   696,   696,   696,   697,   697,   697,
     697,   697,   699,   698,   700,   701,   702,   704,   703,   706,
     705,   707,   707,   707,   708,   708,   709
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
       1,     0,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       0,     4,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     3,     3,     0,     4,     1,     1,     1,     1,     3,
       0,     4,     0,     4,     3,     3,     3,     0,     4,     3,
       0,     4,     0,     4,     3,     3,     3,     0,     6,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     3,     3,     3,     0,     6,
       0,     6,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     0,
       4,     1,     1,     1,     3,     3,     3,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     1,     3,     2,
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     3,
       3,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
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
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     4,     3,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     0,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     1,
       0,     6,     1,     3,     2,     0,     4,     0,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     3,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     3,     0,     4,     3,     3,     3,     0,     6,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     0,     4,
       0,     4,     3,     3,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
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
  "\"type\"", "\"memfile\"", "\"mysql\"", "\"postgresql\"", "\"user\"",
  "\"password\"", "\"host\"", "\"port\"", "\"persist\"",
  "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
  "\"read-timeout\"", "\"write-timeout\"", "\"tcp-user-timeout\"",
  "\"max-reconnect-tries\"", "\"reconnect-wait-time\"", "\"on-fail\"",
  "\"stop-retry-exit\"", "\"serve-retry-exit\"",
  "\"serve-retry-continue\"", "\"retry-on-startup\"", "\"max-row-errors\"",
  "\"trust-anchor\"", "\"cert-file\"", "\"key-file\"", "\"cipher-list\"",
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
  "\"ddns-ttl-percent\"", "\"store-extended-info\"", "\"subnet6\"",
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
  "\"client-classes\"", "\"require-client-classes\"", "\"test\"",
  "\"template-test\"", "\"only-if-required\"", "\"client-class\"",
  "\"pool-id\"", "\"reservations\"", "\"ip-addresses\"", "\"prefixes\"",
  "\"duid\"", "\"hw-address\"", "\"hostname\"", "\"flex-id\"", "\"relay\"",
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
  "\"dhcp-queue-control\"", "\"enable-queue\"", "\"queue-type\"",
  "\"capacity\"", "\"dhcp-ddns\"", "\"enable-updates\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"", "\"UDP\"",
  "\"TCP\"", "\"JSON\"", "\"when-present\"", "\"never\"", "\"always\"",
  "\"when-not-present\"", "\"hostname-char-set\"",
  "\"hostname-char-replacement\"", "\"early-global-reservations-lookup\"",
  "\"ip-reservations-unique\"", "\"reservations-lookup-first\"",
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
  "cache_max_age", "decline_probation_period", "ddns_send_updates",
  "ddns_override_no_update", "ddns_override_client_update",
  "ddns_replace_client_name", "$@22", "ddns_replace_client_name_value",
  "ddns_generated_prefix", "$@23", "ddns_qualifying_suffix", "$@24",
  "ddns_update_on_renew", "ddns_use_conflict_resolution",
  "ddns_conflict_resolution_mode", "$@25",
  "ddns_conflict_resolution_mode_value", "ddns_ttl_percent",
  "hostname_char_set", "$@26", "hostname_char_replacement", "$@27",
  "store_extended_info", "statistic_default_sample_count",
  "statistic_default_sample_age", "server_tag", "$@28",
  "parked_packet_limit", "allocator", "$@29", "pd_allocator", "$@30",
  "early_global_reservations_lookup", "ip_reservations_unique",
  "reservations_lookup_first", "interfaces_config", "$@31",
  "sub_interfaces6", "$@32", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@33", "re_detect",
  "service_sockets_require_all", "service_sockets_retry_wait_time",
  "service_sockets_max_retries", "lease_database", "$@34",
  "hosts_database", "$@35", "hosts_databases", "$@36", "database_list",
  "not_empty_database_list", "database", "$@37", "database_map_params",
  "database_map_param", "database_type", "$@38", "db_type", "user", "$@39",
  "password", "$@40", "host", "$@41", "port", "name", "$@42", "persist",
  "lfc_interval", "readonly", "connect_timeout", "read_timeout",
  "write_timeout", "tcp_user_timeout", "reconnect_wait_time", "on_fail",
  "$@43", "on_fail_mode", "retry_on_startup", "max_row_errors",
  "max_reconnect_tries", "trust_anchor", "$@44", "cert_file", "$@45",
  "key_file", "$@46", "cipher_list", "$@47", "sanity_checks", "$@48",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@49",
  "extended_info_checks", "$@50", "mac_sources", "$@51",
  "mac_sources_list", "mac_sources_value", "duid_id", "string_id",
  "host_reservation_identifiers", "$@52",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@53",
  "dhcp_multi_threading", "$@54", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@55", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@56",
  "sub_hooks_library", "$@57", "hooks_params", "hooks_param", "library",
  "$@58", "parameters", "$@59", "expired_leases_processing", "$@60",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@61",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@62",
  "sub_subnet6", "$@63", "subnet6_params", "subnet6_param", "subnet",
  "$@64", "interface", "$@65", "interface_id", "$@66", "client_class",
  "$@67", "require_client_classes", "$@68", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "id",
  "rapid_commit", "shared_networks", "$@69", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@70",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@71", "sub_option_def_list", "$@72", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@73",
  "sub_option_def", "$@74", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@75",
  "option_def_record_types", "$@76", "space", "$@77", "option_def_space",
  "option_def_encapsulate", "$@78", "option_def_array", "option_data_list",
  "$@79", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@80", "sub_option_data", "$@81",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@82",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "option_data_never_send", "pools_list",
  "$@83", "pools_list_content", "not_empty_pools_list", "pool_list_entry",
  "$@84", "sub_pool6", "$@85", "pool_params", "pool_param", "pool_entry",
  "$@86", "pool_id", "user_context", "$@87", "comment", "$@88",
  "pd_pools_list", "$@89", "pd_pools_list_content",
  "not_empty_pd_pools_list", "pd_pool_entry", "$@90", "sub_pd_pool",
  "$@91", "pd_pool_params", "pd_pool_param", "pd_prefix", "$@92",
  "pd_prefix_len", "excluded_prefix", "$@93", "excluded_prefix_len",
  "pd_delegated_len", "reservations", "$@94", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@95", "sub_reservation",
  "$@96", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "ip_addresses", "$@97", "prefixes", "$@98", "duid",
  "$@99", "hw_address", "$@100", "hostname", "$@101", "flex_id_value",
  "$@102", "reservation_client_classes", "$@103", "relay", "$@104",
  "relay_map", "client_classes", "$@105", "client_classes_list",
  "client_class_entry", "$@106", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@107",
  "client_class_template_test", "$@108", "only_if_required", "server_id",
  "$@109", "server_id_params", "server_id_param", "server_id_type",
  "$@110", "duid_type", "htype", "identifier", "$@111", "time",
  "enterprise_id", "dhcp4o6_port", "control_socket", "$@112",
  "control_sockets", "$@113", "control_socket_list",
  "not_empty_control_socket_list", "control_socket_entry", "$@114",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@115", "control_socket_type_value", "control_socket_name", "$@116",
  "control_socket_address", "$@117", "control_socket_port",
  "cert_required", "authentication", "$@118", "auth_params", "auth_param",
  "auth_type", "$@119", "auth_type_value", "realm", "$@120", "directory",
  "$@121", "clients", "$@122", "clients_list", "not_empty_clients_list",
  "basic_auth", "$@123", "clients_params", "clients_param", "user_file",
  "$@124", "password_file", "$@125", "dhcp_queue_control", "$@126",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@127", "capacity", "arbitrary_map_entry", "$@128",
  "dhcp_ddns", "$@129", "sub_dhcp_ddns", "$@130", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@131", "server_port",
  "sender_ip", "$@132", "sender_port", "max_queue_size", "ncr_protocol",
  "$@133", "ncr_protocol_value", "ncr_format", "$@134", "config_control",
  "$@135", "sub_config_control", "$@136", "config_control_params",
  "config_control_param", "config_databases", "$@137",
  "config_fetch_wait_time", "loggers", "$@138", "loggers_entries",
  "logger_entry", "$@139", "logger_params", "logger_param", "debuglevel",
  "severity", "$@140", "output_options_list", "$@141",
  "output_options_list_content", "output_entry", "$@142",
  "output_params_list", "output_params", "output", "$@143", "flush",
  "maxsize", "maxver", "pattern", "$@144", "compatibility", "$@145",
  "compatibility_params", "compatibility_param", "lenient_option_parsing", YY_NULLPTR
  };
#endif


#if PARSER6_DEBUG
  const short
  Dhcp6Parser::yyrline_[] =
  {
       0,   328,   328,   328,   329,   329,   330,   330,   331,   331,
     332,   332,   333,   333,   334,   334,   335,   335,   336,   336,
     337,   337,   338,   338,   339,   339,   340,   340,   341,   341,
     349,   350,   351,   352,   353,   354,   355,   358,   363,   363,
     374,   377,   378,   381,   386,   392,   397,   397,   404,   405,
     408,   412,   416,   422,   422,   429,   430,   433,   437,   441,
     451,   460,   460,   475,   475,   489,   492,   498,   498,   507,
     508,   509,   516,   517,   518,   519,   520,   521,   522,   523,
     524,   525,   526,   527,   528,   529,   530,   531,   532,   533,
     534,   535,   536,   537,   538,   539,   540,   541,   542,   543,
     544,   545,   546,   547,   548,   549,   550,   551,   552,   553,
     554,   555,   556,   557,   558,   559,   560,   561,   562,   563,
     564,   565,   566,   567,   568,   569,   570,   571,   572,   573,
     574,   575,   576,   577,   578,   579,   580,   581,   582,   583,
     584,   587,   587,   596,   602,   608,   614,   620,   626,   632,
     638,   644,   650,   656,   662,   668,   674,   680,   686,   692,
     698,   698,   707,   710,   713,   716,   719,   725,   725,   734,
     734,   743,   752,   762,   762,   771,   774,   777,   780,   785,
     791,   791,   800,   800,   809,   815,   821,   827,   827,   836,
     842,   842,   851,   851,   860,   866,   872,   878,   878,   890,
     890,   899,   900,   901,   906,   907,   908,   909,   910,   911,
     912,   913,   916,   916,   927,   933,   939,   945,   951,   951,
     964,   964,   977,   977,   988,   989,   992,   993,   994,   999,
     999,  1009,  1010,  1011,  1016,  1017,  1018,  1019,  1020,  1021,
    1022,  1023,  1024,  1025,  1026,  1027,  1028,  1029,  1030,  1031,
    1032,  1033,  1034,  1035,  1036,  1037,  1038,  1041,  1041,  1049,
    1050,  1051,  1054,  1054,  1063,  1063,  1072,  1072,  1081,  1087,
    1087,  1096,  1102,  1108,  1114,  1120,  1126,  1132,  1139,  1145,
    1145,  1153,  1154,  1155,  1158,  1164,  1170,  1176,  1176,  1185,
    1185,  1194,  1194,  1203,  1203,  1212,  1212,  1223,  1224,  1225,
    1230,  1231,  1234,  1234,  1253,  1253,  1271,  1271,  1282,  1283,
    1284,  1289,  1290,  1293,  1298,  1303,  1303,  1314,  1315,  1316,
    1321,  1322,  1323,  1326,  1331,  1338,  1338,  1351,  1351,  1364,
    1365,  1366,  1371,  1372,  1373,  1374,  1375,  1376,  1379,  1385,
    1391,  1397,  1397,  1408,  1409,  1412,  1413,  1414,  1419,  1419,
    1429,  1429,  1439,  1440,  1441,  1444,  1447,  1448,  1451,  1451,
    1460,  1460,  1469,  1469,  1481,  1482,  1483,  1488,  1489,  1490,
    1491,  1492,  1493,  1496,  1502,  1508,  1514,  1520,  1526,  1535,
    1535,  1549,  1550,  1553,  1554,  1555,  1564,  1564,  1590,  1590,
    1601,  1602,  1603,  1609,  1610,  1611,  1612,  1613,  1614,  1615,
    1616,  1617,  1618,  1619,  1620,  1621,  1622,  1623,  1624,  1625,
    1626,  1627,  1628,  1629,  1630,  1631,  1632,  1633,  1634,  1635,
    1636,  1637,  1638,  1639,  1640,  1641,  1642,  1643,  1644,  1645,
    1646,  1647,  1648,  1649,  1650,  1651,  1652,  1653,  1654,  1657,
    1657,  1666,  1666,  1675,  1675,  1684,  1684,  1693,  1693,  1704,
    1710,  1716,  1722,  1728,  1736,  1736,  1748,  1749,  1753,  1754,
    1755,  1760,  1760,  1768,  1769,  1770,  1775,  1776,  1777,  1778,
    1779,  1780,  1781,  1782,  1783,  1784,  1785,  1786,  1787,  1788,
    1789,  1790,  1791,  1792,  1793,  1794,  1795,  1796,  1797,  1798,
    1799,  1800,  1801,  1802,  1803,  1804,  1805,  1806,  1807,  1808,
    1809,  1810,  1811,  1812,  1813,  1814,  1815,  1816,  1817,  1824,
    1824,  1838,  1838,  1847,  1848,  1851,  1852,  1853,  1860,  1860,
    1875,  1875,  1889,  1890,  1893,  1894,  1895,  1900,  1901,  1902,
    1903,  1904,  1905,  1906,  1907,  1908,  1909,  1912,  1914,  1920,
    1922,  1922,  1931,  1931,  1940,  1940,  1949,  1951,  1951,  1960,
    1970,  1970,  1983,  1984,  1989,  1990,  1991,  1998,  1998,  2010,
    2010,  2022,  2023,  2028,  2029,  2030,  2037,  2038,  2039,  2040,
    2041,  2042,  2043,  2044,  2045,  2046,  2049,  2051,  2051,  2060,
    2062,  2064,  2070,  2076,  2085,  2085,  2098,  2099,  2102,  2103,
    2104,  2109,  2109,  2119,  2119,  2129,  2130,  2131,  2136,  2137,
    2138,  2139,  2140,  2141,  2142,  2143,  2146,  2146,  2155,  2161,
    2161,  2186,  2186,  2216,  2216,  2229,  2230,  2233,  2234,  2235,
    2240,  2240,  2252,  2252,  2264,  2265,  2266,  2271,  2272,  2273,
    2274,  2275,  2276,  2277,  2278,  2279,  2280,  2281,  2282,  2285,
    2285,  2294,  2300,  2300,  2309,  2315,  2324,  2324,  2335,  2336,
    2339,  2340,  2341,  2346,  2346,  2355,  2355,  2364,  2365,  2368,
    2369,  2370,  2376,  2377,  2378,  2379,  2380,  2381,  2382,  2383,
    2384,  2385,  2386,  2389,  2389,  2400,  2400,  2411,  2411,  2420,
    2420,  2429,  2429,  2438,  2438,  2447,  2447,  2461,  2461,  2472,
    2478,  2478,  2489,  2490,  2491,  2496,  2496,  2506,  2507,  2510,
    2511,  2512,  2517,  2518,  2519,  2520,  2521,  2522,  2523,  2524,
    2525,  2526,  2527,  2528,  2529,  2530,  2533,  2535,  2535,  2544,
    2544,  2553,  2562,  2562,  2575,  2576,  2577,  2582,  2583,  2584,
    2585,  2586,  2587,  2588,  2589,  2590,  2593,  2593,  2601,  2602,
    2603,  2606,  2612,  2612,  2621,  2627,  2635,  2643,  2643,  2655,
    2655,  2667,  2668,  2671,  2672,  2673,  2678,  2678,  2686,  2687,
    2688,  2693,  2694,  2695,  2696,  2697,  2698,  2699,  2700,  2701,
    2702,  2703,  2704,  2707,  2707,  2716,  2717,  2718,  2721,  2721,
    2731,  2731,  2741,  2747,  2755,  2755,  2768,  2769,  2770,  2775,
    2776,  2777,  2778,  2779,  2780,  2781,  2784,  2784,  2792,  2795,
    2795,  2804,  2804,  2813,  2813,  2824,  2825,  2828,  2829,  2830,
    2835,  2835,  2843,  2844,  2845,  2850,  2851,  2852,  2853,  2854,
    2855,  2856,  2859,  2859,  2868,  2868,  2879,  2879,  2892,  2893,
    2894,  2899,  2900,  2901,  2902,  2903,  2904,  2907,  2913,  2913,
    2922,  2928,  2928,  2938,  2938,  2951,  2951,  2961,  2962,  2963,
    2968,  2969,  2970,  2971,  2972,  2973,  2974,  2975,  2976,  2977,
    2978,  2981,  2987,  2987,  2996,  3002,  3002,  3011,  3017,  3023,
    3023,  3032,  3033,  3036,  3036,  3047,  3047,  3059,  3059,  3069,
    3070,  3071,  3077,  3078,  3081,  3081,  3092,  3100,  3100,  3113,
    3114,  3115,  3121,  3121,  3129,  3130,  3131,  3136,  3137,  3138,
    3139,  3140,  3141,  3142,  3145,  3151,  3151,  3160,  3160,  3171,
    3172,  3173,  3178,  3178,  3186,  3187,  3188,  3193,  3194,  3195,
    3196,  3197,  3200,  3200,  3209,  3215,  3221,  3227,  3227,  3236,
    3236,  3247,  3248,  3249,  3254,  3255,  3258
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
#line 6803 "dhcp6_parser.cc"

#line 3264 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
