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
#line 320 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 417 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 320 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 423 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 320 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 429 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 320 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 435 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 320 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 441 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 320 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 447 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 320 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 453 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
#line 320 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 459 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 320 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 465 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 320 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 471 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 320 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 477 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
#line 320 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 483 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_auth_type_value: // auth_type_value
#line 320 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 489 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 320 "dhcp6_parser.yy"
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
#line 329 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 777 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 330 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 783 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 331 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 789 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 332 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 795 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 333 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 801 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 334 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 807 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 335 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 813 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 336 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 819 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 337 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 825 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 338 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 831 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 339 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 837 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 340 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 843 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 341 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 849 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 342 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 855 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 350 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 861 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 351 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 867 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 352 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 873 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 353 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 879 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 354 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 885 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 355 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 891 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 356 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 897 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 359 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 906 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 364 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 917 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 369 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 927 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 375 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 933 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 382 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 943 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 387 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 954 "dhcp6_parser.cc"
    break;

  case 45: // not_empty_map: not_empty_map ","
#line 393 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 962 "dhcp6_parser.cc"
    break;

  case 46: // $@16: %empty
#line 398 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 971 "dhcp6_parser.cc"
    break;

  case 47: // list_generic: "[" $@16 list_content "]"
#line 401 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 979 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: value
#line 409 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 988 "dhcp6_parser.cc"
    break;

  case 51: // not_empty_list: not_empty_list "," value
#line 413 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 997 "dhcp6_parser.cc"
    break;

  case 52: // not_empty_list: not_empty_list ","
#line 417 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 1005 "dhcp6_parser.cc"
    break;

  case 53: // $@17: %empty
#line 423 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 1013 "dhcp6_parser.cc"
    break;

  case 54: // list_strings: "[" $@17 list_strings_content "]"
#line 425 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1022 "dhcp6_parser.cc"
    break;

  case 57: // not_empty_list_strings: "constant string"
#line 434 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1031 "dhcp6_parser.cc"
    break;

  case 58: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 438 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1040 "dhcp6_parser.cc"
    break;

  case 59: // not_empty_list_strings: not_empty_list_strings ","
#line 442 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1048 "dhcp6_parser.cc"
    break;

  case 60: // unknown_map_entry: "constant string" ":"
#line 452 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1059 "dhcp6_parser.cc"
    break;

  case 61: // $@18: %empty
#line 461 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1070 "dhcp6_parser.cc"
    break;

  case 62: // syntax_map: "{" $@18 global_object "}"
#line 466 "dhcp6_parser.yy"
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
#line 476 "dhcp6_parser.yy"
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
#line 485 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1108 "dhcp6_parser.cc"
    break;

  case 66: // global_object_comma: global_object ","
#line 493 "dhcp6_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1116 "dhcp6_parser.cc"
    break;

  case 67: // $@20: %empty
#line 499 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1126 "dhcp6_parser.cc"
    break;

  case 68: // sub_dhcp6: "{" $@20 global_params "}"
#line 503 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1135 "dhcp6_parser.cc"
    break;

  case 71: // global_params: global_params ","
#line 510 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1143 "dhcp6_parser.cc"
    break;

  case 141: // $@21: %empty
#line 588 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1152 "dhcp6_parser.cc"
    break;

  case 142: // data_directory: "data-directory" $@21 ":" "constant string"
#line 591 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1162 "dhcp6_parser.cc"
    break;

  case 143: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 597 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1172 "dhcp6_parser.cc"
    break;

  case 144: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 603 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1182 "dhcp6_parser.cc"
    break;

  case 145: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 609 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1192 "dhcp6_parser.cc"
    break;

  case 146: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 615 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1202 "dhcp6_parser.cc"
    break;

  case 147: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 621 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1212 "dhcp6_parser.cc"
    break;

  case 148: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 627 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1222 "dhcp6_parser.cc"
    break;

  case 149: // renew_timer: "renew-timer" ":" "integer"
#line 633 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1232 "dhcp6_parser.cc"
    break;

  case 150: // rebind_timer: "rebind-timer" ":" "integer"
#line 639 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1242 "dhcp6_parser.cc"
    break;

  case 151: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 645 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1252 "dhcp6_parser.cc"
    break;

  case 152: // t1_percent: "t1-percent" ":" "floating point"
#line 651 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1262 "dhcp6_parser.cc"
    break;

  case 153: // t2_percent: "t2-percent" ":" "floating point"
#line 657 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1272 "dhcp6_parser.cc"
    break;

  case 154: // cache_threshold: "cache-threshold" ":" "floating point"
#line 663 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1282 "dhcp6_parser.cc"
    break;

  case 155: // cache_max_age: "cache-max-age" ":" "integer"
#line 669 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1292 "dhcp6_parser.cc"
    break;

  case 156: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 675 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1302 "dhcp6_parser.cc"
    break;

  case 157: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 681 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1312 "dhcp6_parser.cc"
    break;

  case 158: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 687 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1322 "dhcp6_parser.cc"
    break;

  case 159: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 693 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1332 "dhcp6_parser.cc"
    break;

  case 160: // $@22: %empty
#line 699 "dhcp6_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1341 "dhcp6_parser.cc"
    break;

  case 161: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 702 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1350 "dhcp6_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "when-present"
#line 708 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1358 "dhcp6_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "never"
#line 711 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1366 "dhcp6_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "always"
#line 714 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1374 "dhcp6_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "when-not-present"
#line 717 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1382 "dhcp6_parser.cc"
    break;

  case 166: // ddns_replace_client_name_value: "boolean"
#line 720 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the ddns-replace-client-name are "
                "no longer supported");
      }
#line 1391 "dhcp6_parser.cc"
    break;

  case 167: // $@23: %empty
#line 726 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1400 "dhcp6_parser.cc"
    break;

  case 168: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 729 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1410 "dhcp6_parser.cc"
    break;

  case 169: // $@24: %empty
#line 735 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1419 "dhcp6_parser.cc"
    break;

  case 170: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 738 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1429 "dhcp6_parser.cc"
    break;

  case 171: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 744 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1439 "dhcp6_parser.cc"
    break;

  case 172: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 753 "dhcp6_parser.yy"
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
#line 763 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ddns-conflict-resolution-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DDNS_CONFLICT_RESOLUTION_MODE);
}
#line 1462 "dhcp6_parser.cc"
    break;

  case 174: // ddns_conflict_resolution_mode: "ddns-conflict-resolution-mode" $@25 ":" ddns_conflict_resolution_mode_value
#line 766 "dhcp6_parser.yy"
                                            {
    ctx.stack_.back()->set("ddns-conflict-resolution-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1471 "dhcp6_parser.cc"
    break;

  case 175: // ddns_conflict_resolution_mode_value: "check-with-dhcid"
#line 772 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1479 "dhcp6_parser.cc"
    break;

  case 176: // ddns_conflict_resolution_mode_value: "no-check-with-dhcid"
#line 775 "dhcp6_parser.yy"
                        {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1487 "dhcp6_parser.cc"
    break;

  case 177: // ddns_conflict_resolution_mode_value: "check-exists-with-dhcid"
#line 778 "dhcp6_parser.yy"
                            {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("check-exists-with-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1495 "dhcp6_parser.cc"
    break;

  case 178: // ddns_conflict_resolution_mode_value: "no-check-without-dhcid"
#line 781 "dhcp6_parser.yy"
                           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("no-check-without-dhcid", ctx.loc2pos(yystack_[0].location)));
      }
#line 1503 "dhcp6_parser.cc"
    break;

  case 179: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 786 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1513 "dhcp6_parser.cc"
    break;

  case 180: // $@26: %empty
#line 792 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1522 "dhcp6_parser.cc"
    break;

  case 181: // hostname_char_set: "hostname-char-set" $@26 ":" "constant string"
#line 795 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1532 "dhcp6_parser.cc"
    break;

  case 182: // $@27: %empty
#line 801 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1541 "dhcp6_parser.cc"
    break;

  case 183: // hostname_char_replacement: "hostname-char-replacement" $@27 ":" "constant string"
#line 804 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1551 "dhcp6_parser.cc"
    break;

  case 184: // store_extended_info: "store-extended-info" ":" "boolean"
#line 810 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1561 "dhcp6_parser.cc"
    break;

  case 185: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 816 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1571 "dhcp6_parser.cc"
    break;

  case 186: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 822 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1581 "dhcp6_parser.cc"
    break;

  case 187: // $@28: %empty
#line 828 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1590 "dhcp6_parser.cc"
    break;

  case 188: // server_tag: "server-tag" $@28 ":" "constant string"
#line 831 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1600 "dhcp6_parser.cc"
    break;

  case 189: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 837 "dhcp6_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1610 "dhcp6_parser.cc"
    break;

  case 190: // $@29: %empty
#line 843 "dhcp6_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1619 "dhcp6_parser.cc"
    break;

  case 191: // allocator: "allocator" $@29 ":" "constant string"
#line 846 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1629 "dhcp6_parser.cc"
    break;

  case 192: // $@30: %empty
#line 852 "dhcp6_parser.yy"
                           {
    ctx.unique("pd-allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1638 "dhcp6_parser.cc"
    break;

  case 193: // pd_allocator: "pd-allocator" $@30 ":" "constant string"
#line 855 "dhcp6_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-allocator", al);
    ctx.leave();
}
#line 1648 "dhcp6_parser.cc"
    break;

  case 194: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 861 "dhcp6_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1658 "dhcp6_parser.cc"
    break;

  case 195: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 867 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1668 "dhcp6_parser.cc"
    break;

  case 196: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 873 "dhcp6_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1678 "dhcp6_parser.cc"
    break;

  case 197: // $@31: %empty
#line 879 "dhcp6_parser.yy"
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
#line 885 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1700 "dhcp6_parser.cc"
    break;

  case 199: // $@32: %empty
#line 891 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1710 "dhcp6_parser.cc"
    break;

  case 200: // sub_interfaces6: "{" $@32 interfaces_config_params "}"
#line 895 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1719 "dhcp6_parser.cc"
    break;

  case 203: // interfaces_config_params: interfaces_config_params ","
#line 902 "dhcp6_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1727 "dhcp6_parser.cc"
    break;

  case 212: // $@33: %empty
#line 917 "dhcp6_parser.yy"
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
#line 923 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1748 "dhcp6_parser.cc"
    break;

  case 214: // re_detect: "re-detect" ":" "boolean"
#line 928 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1758 "dhcp6_parser.cc"
    break;

  case 215: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 934 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1768 "dhcp6_parser.cc"
    break;

  case 216: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 940 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1778 "dhcp6_parser.cc"
    break;

  case 217: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 946 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1788 "dhcp6_parser.cc"
    break;

  case 218: // $@34: %empty
#line 952 "dhcp6_parser.yy"
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
#line 958 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1811 "dhcp6_parser.cc"
    break;

  case 220: // $@35: %empty
#line 965 "dhcp6_parser.yy"
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
#line 971 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1834 "dhcp6_parser.cc"
    break;

  case 222: // $@36: %empty
#line 978 "dhcp6_parser.yy"
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
#line 984 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1855 "dhcp6_parser.cc"
    break;

  case 228: // not_empty_database_list: not_empty_database_list ","
#line 995 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1863 "dhcp6_parser.cc"
    break;

  case 229: // $@37: %empty
#line 1000 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1873 "dhcp6_parser.cc"
    break;

  case 230: // database: "{" $@37 database_map_params "}"
#line 1004 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1883 "dhcp6_parser.cc"
    break;

  case 233: // database_map_params: database_map_params ","
#line 1012 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1891 "dhcp6_parser.cc"
    break;

  case 257: // $@38: %empty
#line 1042 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1900 "dhcp6_parser.cc"
    break;

  case 258: // database_type: "type" $@38 ":" db_type
#line 1045 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1909 "dhcp6_parser.cc"
    break;

  case 259: // db_type: "memfile"
#line 1050 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1915 "dhcp6_parser.cc"
    break;

  case 260: // db_type: "mysql"
#line 1051 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1921 "dhcp6_parser.cc"
    break;

  case 261: // db_type: "postgresql"
#line 1052 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1927 "dhcp6_parser.cc"
    break;

  case 262: // $@39: %empty
#line 1055 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1936 "dhcp6_parser.cc"
    break;

  case 263: // user: "user" $@39 ":" "constant string"
#line 1058 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1946 "dhcp6_parser.cc"
    break;

  case 264: // $@40: %empty
#line 1064 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1955 "dhcp6_parser.cc"
    break;

  case 265: // password: "password" $@40 ":" "constant string"
#line 1067 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1965 "dhcp6_parser.cc"
    break;

  case 266: // $@41: %empty
#line 1073 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1974 "dhcp6_parser.cc"
    break;

  case 267: // host: "host" $@41 ":" "constant string"
#line 1076 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1984 "dhcp6_parser.cc"
    break;

  case 268: // port: "port" ":" "integer"
#line 1082 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1994 "dhcp6_parser.cc"
    break;

  case 269: // $@42: %empty
#line 1088 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2003 "dhcp6_parser.cc"
    break;

  case 270: // name: "name" $@42 ":" "constant string"
#line 1091 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2013 "dhcp6_parser.cc"
    break;

  case 271: // persist: "persist" ":" "boolean"
#line 1097 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2023 "dhcp6_parser.cc"
    break;

  case 272: // lfc_interval: "lfc-interval" ":" "integer"
#line 1103 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2033 "dhcp6_parser.cc"
    break;

  case 273: // readonly: "readonly" ":" "boolean"
#line 1109 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2043 "dhcp6_parser.cc"
    break;

  case 274: // connect_timeout: "connect-timeout" ":" "integer"
#line 1115 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2053 "dhcp6_parser.cc"
    break;

  case 275: // read_timeout: "read-timeout" ":" "integer"
#line 1121 "dhcp6_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2063 "dhcp6_parser.cc"
    break;

  case 276: // write_timeout: "write-timeout" ":" "integer"
#line 1127 "dhcp6_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2073 "dhcp6_parser.cc"
    break;

  case 277: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1133 "dhcp6_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2083 "dhcp6_parser.cc"
    break;

  case 278: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1140 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2093 "dhcp6_parser.cc"
    break;

  case 279: // $@43: %empty
#line 1146 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2102 "dhcp6_parser.cc"
    break;

  case 280: // on_fail: "on-fail" $@43 ":" on_fail_mode
#line 1149 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2111 "dhcp6_parser.cc"
    break;

  case 281: // on_fail_mode: "stop-retry-exit"
#line 1154 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2117 "dhcp6_parser.cc"
    break;

  case 282: // on_fail_mode: "serve-retry-exit"
#line 1155 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2123 "dhcp6_parser.cc"
    break;

  case 283: // on_fail_mode: "serve-retry-continue"
#line 1156 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2129 "dhcp6_parser.cc"
    break;

  case 284: // retry_on_startup: "retry-on-startup" ":" "boolean"
#line 1159 "dhcp6_parser.yy"
                                                 {
    ctx.unique("retry-on-startup", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("retry-on-startup", n);
}
#line 2139 "dhcp6_parser.cc"
    break;

  case 285: // max_row_errors: "max-row-errors" ":" "integer"
#line 1165 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2149 "dhcp6_parser.cc"
    break;

  case 286: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1171 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2159 "dhcp6_parser.cc"
    break;

  case 287: // $@44: %empty
#line 1177 "dhcp6_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2168 "dhcp6_parser.cc"
    break;

  case 288: // trust_anchor: "trust-anchor" $@44 ":" "constant string"
#line 1180 "dhcp6_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2178 "dhcp6_parser.cc"
    break;

  case 289: // $@45: %empty
#line 1186 "dhcp6_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2187 "dhcp6_parser.cc"
    break;

  case 290: // cert_file: "cert-file" $@45 ":" "constant string"
#line 1189 "dhcp6_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2197 "dhcp6_parser.cc"
    break;

  case 291: // $@46: %empty
#line 1195 "dhcp6_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2206 "dhcp6_parser.cc"
    break;

  case 292: // key_file: "key-file" $@46 ":" "constant string"
#line 1198 "dhcp6_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2216 "dhcp6_parser.cc"
    break;

  case 293: // $@47: %empty
#line 1204 "dhcp6_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2225 "dhcp6_parser.cc"
    break;

  case 294: // cipher_list: "cipher-list" $@47 ":" "constant string"
#line 1207 "dhcp6_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2235 "dhcp6_parser.cc"
    break;

  case 295: // $@48: %empty
#line 1213 "dhcp6_parser.yy"
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
#line 1219 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2256 "dhcp6_parser.cc"
    break;

  case 299: // sanity_checks_params: sanity_checks_params ","
#line 1226 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2264 "dhcp6_parser.cc"
    break;

  case 302: // $@49: %empty
#line 1235 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2273 "dhcp6_parser.cc"
    break;

  case 303: // lease_checks: "lease-checks" $@49 ":" "constant string"
#line 1238 "dhcp6_parser.yy"
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
#line 1254 "dhcp6_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2302 "dhcp6_parser.cc"
    break;

  case 305: // extended_info_checks: "extended-info-checks" $@50 ":" "constant string"
#line 1257 "dhcp6_parser.yy"
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
#line 1272 "dhcp6_parser.yy"
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
#line 1278 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2342 "dhcp6_parser.cc"
    break;

  case 310: // mac_sources_list: mac_sources_list ","
#line 1285 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 2350 "dhcp6_parser.cc"
    break;

  case 313: // duid_id: "duid"
#line 1294 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2359 "dhcp6_parser.cc"
    break;

  case 314: // string_id: "constant string"
#line 1299 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2368 "dhcp6_parser.cc"
    break;

  case 315: // $@52: %empty
#line 1304 "dhcp6_parser.yy"
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
#line 1310 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2389 "dhcp6_parser.cc"
    break;

  case 319: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1317 "dhcp6_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2397 "dhcp6_parser.cc"
    break;

  case 323: // hw_address_id: "hw-address"
#line 1327 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2406 "dhcp6_parser.cc"
    break;

  case 324: // flex_id: "flex-id"
#line 1332 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2415 "dhcp6_parser.cc"
    break;

  case 325: // $@53: %empty
#line 1339 "dhcp6_parser.yy"
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
#line 1345 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2436 "dhcp6_parser.cc"
    break;

  case 327: // $@54: %empty
#line 1352 "dhcp6_parser.yy"
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
#line 1358 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2459 "dhcp6_parser.cc"
    break;

  case 331: // multi_threading_params: multi_threading_params ","
#line 1367 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2467 "dhcp6_parser.cc"
    break;

  case 338: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1380 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2477 "dhcp6_parser.cc"
    break;

  case 339: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1386 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2487 "dhcp6_parser.cc"
    break;

  case 340: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1392 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2497 "dhcp6_parser.cc"
    break;

  case 341: // $@55: %empty
#line 1398 "dhcp6_parser.yy"
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
#line 1404 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2518 "dhcp6_parser.cc"
    break;

  case 347: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1415 "dhcp6_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2526 "dhcp6_parser.cc"
    break;

  case 348: // $@56: %empty
#line 1420 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2536 "dhcp6_parser.cc"
    break;

  case 349: // hooks_library: "{" $@56 hooks_params "}"
#line 1424 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2546 "dhcp6_parser.cc"
    break;

  case 350: // $@57: %empty
#line 1430 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2556 "dhcp6_parser.cc"
    break;

  case 351: // sub_hooks_library: "{" $@57 hooks_params "}"
#line 1434 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2566 "dhcp6_parser.cc"
    break;

  case 354: // hooks_params: hooks_params ","
#line 1442 "dhcp6_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2574 "dhcp6_parser.cc"
    break;

  case 358: // $@58: %empty
#line 1452 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2583 "dhcp6_parser.cc"
    break;

  case 359: // library: "library" $@58 ":" "constant string"
#line 1455 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2593 "dhcp6_parser.cc"
    break;

  case 360: // $@59: %empty
#line 1461 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2602 "dhcp6_parser.cc"
    break;

  case 361: // parameters: "parameters" $@59 ":" map_value
#line 1464 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2611 "dhcp6_parser.cc"
    break;

  case 362: // $@60: %empty
#line 1470 "dhcp6_parser.yy"
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
#line 1476 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2633 "dhcp6_parser.cc"
    break;

  case 366: // expired_leases_params: expired_leases_params ","
#line 1484 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2641 "dhcp6_parser.cc"
    break;

  case 373: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1497 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2651 "dhcp6_parser.cc"
    break;

  case 374: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1503 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2661 "dhcp6_parser.cc"
    break;

  case 375: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1509 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2671 "dhcp6_parser.cc"
    break;

  case 376: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1515 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2681 "dhcp6_parser.cc"
    break;

  case 377: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1521 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2691 "dhcp6_parser.cc"
    break;

  case 378: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1527 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2701 "dhcp6_parser.cc"
    break;

  case 379: // $@61: %empty
#line 1536 "dhcp6_parser.yy"
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
#line 1542 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2722 "dhcp6_parser.cc"
    break;

  case 385: // not_empty_subnet6_list: not_empty_subnet6_list ","
#line 1556 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2730 "dhcp6_parser.cc"
    break;

  case 386: // $@62: %empty
#line 1565 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2740 "dhcp6_parser.cc"
    break;

  case 387: // subnet6: "{" $@62 subnet6_params "}"
#line 1569 "dhcp6_parser.yy"
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
#line 1591 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2776 "dhcp6_parser.cc"
    break;

  case 389: // sub_subnet6: "{" $@63 subnet6_params "}"
#line 1595 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2786 "dhcp6_parser.cc"
    break;

  case 392: // subnet6_params: subnet6_params ","
#line 1604 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2794 "dhcp6_parser.cc"
    break;

  case 439: // $@64: %empty
#line 1658 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2803 "dhcp6_parser.cc"
    break;

  case 440: // subnet: "subnet" $@64 ":" "constant string"
#line 1661 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2813 "dhcp6_parser.cc"
    break;

  case 441: // $@65: %empty
#line 1667 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2822 "dhcp6_parser.cc"
    break;

  case 442: // interface: "interface" $@65 ":" "constant string"
#line 1670 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2832 "dhcp6_parser.cc"
    break;

  case 443: // $@66: %empty
#line 1676 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2841 "dhcp6_parser.cc"
    break;

  case 444: // interface_id: "interface-id" $@66 ":" "constant string"
#line 1679 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2851 "dhcp6_parser.cc"
    break;

  case 445: // $@67: %empty
#line 1685 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2860 "dhcp6_parser.cc"
    break;

  case 446: // client_class: "client-class" $@67 ":" "constant string"
#line 1688 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2870 "dhcp6_parser.cc"
    break;

  case 447: // $@68: %empty
#line 1694 "dhcp6_parser.yy"
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
#line 1700 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2891 "dhcp6_parser.cc"
    break;

  case 449: // reservations_global: "reservations-global" ":" "boolean"
#line 1705 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2901 "dhcp6_parser.cc"
    break;

  case 450: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1711 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2911 "dhcp6_parser.cc"
    break;

  case 451: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1717 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2921 "dhcp6_parser.cc"
    break;

  case 452: // id: "id" ":" "integer"
#line 1723 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2931 "dhcp6_parser.cc"
    break;

  case 453: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1729 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2941 "dhcp6_parser.cc"
    break;

  case 454: // $@69: %empty
#line 1737 "dhcp6_parser.yy"
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
#line 1743 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2962 "dhcp6_parser.cc"
    break;

  case 460: // shared_networks_list: shared_networks_list ","
#line 1756 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2970 "dhcp6_parser.cc"
    break;

  case 461: // $@70: %empty
#line 1761 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2980 "dhcp6_parser.cc"
    break;

  case 462: // shared_network: "{" $@70 shared_network_params "}"
#line 1765 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2988 "dhcp6_parser.cc"
    break;

  case 465: // shared_network_params: shared_network_params ","
#line 1771 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2996 "dhcp6_parser.cc"
    break;

  case 509: // $@71: %empty
#line 1825 "dhcp6_parser.yy"
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
#line 1831 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3017 "dhcp6_parser.cc"
    break;

  case 511: // $@72: %empty
#line 1839 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3026 "dhcp6_parser.cc"
    break;

  case 512: // sub_option_def_list: "{" $@72 option_def_list "}"
#line 1842 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 3034 "dhcp6_parser.cc"
    break;

  case 517: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1854 "dhcp6_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3042 "dhcp6_parser.cc"
    break;

  case 518: // $@73: %empty
#line 1861 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3052 "dhcp6_parser.cc"
    break;

  case 519: // option_def_entry: "{" $@73 option_def_params "}"
#line 1865 "dhcp6_parser.yy"
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
#line 1876 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3074 "dhcp6_parser.cc"
    break;

  case 521: // sub_option_def: "{" $@74 option_def_params "}"
#line 1880 "dhcp6_parser.yy"
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
#line 1896 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3094 "dhcp6_parser.cc"
    break;

  case 538: // code: "code" ":" "integer"
#line 1915 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3104 "dhcp6_parser.cc"
    break;

  case 540: // $@75: %empty
#line 1923 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3113 "dhcp6_parser.cc"
    break;

  case 541: // option_def_type: "type" $@75 ":" "constant string"
#line 1926 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3123 "dhcp6_parser.cc"
    break;

  case 542: // $@76: %empty
#line 1932 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3132 "dhcp6_parser.cc"
    break;

  case 543: // option_def_record_types: "record-types" $@76 ":" "constant string"
#line 1935 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3142 "dhcp6_parser.cc"
    break;

  case 544: // $@77: %empty
#line 1941 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3151 "dhcp6_parser.cc"
    break;

  case 545: // space: "space" $@77 ":" "constant string"
#line 1944 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3161 "dhcp6_parser.cc"
    break;

  case 547: // $@78: %empty
#line 1952 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3170 "dhcp6_parser.cc"
    break;

  case 548: // option_def_encapsulate: "encapsulate" $@78 ":" "constant string"
#line 1955 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3180 "dhcp6_parser.cc"
    break;

  case 549: // option_def_array: "array" ":" "boolean"
#line 1961 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3190 "dhcp6_parser.cc"
    break;

  case 550: // $@79: %empty
#line 1971 "dhcp6_parser.yy"
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
#line 1977 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3211 "dhcp6_parser.cc"
    break;

  case 556: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1992 "dhcp6_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3219 "dhcp6_parser.cc"
    break;

  case 557: // $@80: %empty
#line 1999 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3229 "dhcp6_parser.cc"
    break;

  case 558: // option_data_entry: "{" $@80 option_data_params "}"
#line 2003 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3238 "dhcp6_parser.cc"
    break;

  case 559: // $@81: %empty
#line 2011 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3248 "dhcp6_parser.cc"
    break;

  case 560: // sub_option_data: "{" $@81 option_data_params "}"
#line 2015 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3257 "dhcp6_parser.cc"
    break;

  case 565: // not_empty_option_data_params: not_empty_option_data_params ","
#line 2031 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3265 "dhcp6_parser.cc"
    break;

  case 577: // $@82: %empty
#line 2052 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3274 "dhcp6_parser.cc"
    break;

  case 578: // option_data_data: "data" $@82 ":" "constant string"
#line 2055 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3284 "dhcp6_parser.cc"
    break;

  case 581: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2065 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3294 "dhcp6_parser.cc"
    break;

  case 582: // option_data_always_send: "always-send" ":" "boolean"
#line 2071 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3304 "dhcp6_parser.cc"
    break;

  case 583: // option_data_never_send: "never-send" ":" "boolean"
#line 2077 "dhcp6_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3314 "dhcp6_parser.cc"
    break;

  case 584: // $@83: %empty
#line 2086 "dhcp6_parser.yy"
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
#line 2092 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3335 "dhcp6_parser.cc"
    break;

  case 590: // not_empty_pools_list: not_empty_pools_list ","
#line 2105 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3343 "dhcp6_parser.cc"
    break;

  case 591: // $@84: %empty
#line 2110 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3353 "dhcp6_parser.cc"
    break;

  case 592: // pool_list_entry: "{" $@84 pool_params "}"
#line 2114 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3363 "dhcp6_parser.cc"
    break;

  case 593: // $@85: %empty
#line 2120 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3373 "dhcp6_parser.cc"
    break;

  case 594: // sub_pool6: "{" $@85 pool_params "}"
#line 2124 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3383 "dhcp6_parser.cc"
    break;

  case 597: // pool_params: pool_params ","
#line 2132 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3391 "dhcp6_parser.cc"
    break;

  case 606: // $@86: %empty
#line 2147 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3400 "dhcp6_parser.cc"
    break;

  case 607: // pool_entry: "pool" $@86 ":" "constant string"
#line 2150 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3410 "dhcp6_parser.cc"
    break;

  case 608: // pool_id: "pool-id" ":" "integer"
#line 2156 "dhcp6_parser.yy"
                               {
    ctx.unique("pool-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool-id", id);
}
#line 3420 "dhcp6_parser.cc"
    break;

  case 609: // $@87: %empty
#line 2162 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3428 "dhcp6_parser.cc"
    break;

  case 610: // user_context: "user-context" $@87 ":" map_value
#line 2164 "dhcp6_parser.yy"
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
#line 2187 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3463 "dhcp6_parser.cc"
    break;

  case 612: // comment: "comment" $@88 ":" "constant string"
#line 2189 "dhcp6_parser.yy"
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
#line 2217 "dhcp6_parser.yy"
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
#line 2223 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3513 "dhcp6_parser.cc"
    break;

  case 619: // not_empty_pd_pools_list: not_empty_pd_pools_list ","
#line 2236 "dhcp6_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 3521 "dhcp6_parser.cc"
    break;

  case 620: // $@90: %empty
#line 2241 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3531 "dhcp6_parser.cc"
    break;

  case 621: // pd_pool_entry: "{" $@90 pd_pool_params "}"
#line 2245 "dhcp6_parser.yy"
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
#line 2253 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3553 "dhcp6_parser.cc"
    break;

  case 623: // sub_pd_pool: "{" $@91 pd_pool_params "}"
#line 2257 "dhcp6_parser.yy"
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
#line 2267 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 3573 "dhcp6_parser.cc"
    break;

  case 639: // $@92: %empty
#line 2286 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3582 "dhcp6_parser.cc"
    break;

  case 640: // pd_prefix: "prefix" $@92 ":" "constant string"
#line 2289 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3592 "dhcp6_parser.cc"
    break;

  case 641: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2295 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3602 "dhcp6_parser.cc"
    break;

  case 642: // $@93: %empty
#line 2301 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3611 "dhcp6_parser.cc"
    break;

  case 643: // excluded_prefix: "excluded-prefix" $@93 ":" "constant string"
#line 2304 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3621 "dhcp6_parser.cc"
    break;

  case 644: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2310 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3631 "dhcp6_parser.cc"
    break;

  case 645: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2316 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3641 "dhcp6_parser.cc"
    break;

  case 646: // $@94: %empty
#line 2325 "dhcp6_parser.yy"
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
#line 2331 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3662 "dhcp6_parser.cc"
    break;

  case 652: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2342 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3670 "dhcp6_parser.cc"
    break;

  case 653: // $@95: %empty
#line 2347 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3680 "dhcp6_parser.cc"
    break;

  case 654: // reservation: "{" $@95 reservation_params "}"
#line 2351 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3689 "dhcp6_parser.cc"
    break;

  case 655: // $@96: %empty
#line 2356 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3699 "dhcp6_parser.cc"
    break;

  case 656: // sub_reservation: "{" $@96 reservation_params "}"
#line 2360 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3708 "dhcp6_parser.cc"
    break;

  case 661: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2371 "dhcp6_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3716 "dhcp6_parser.cc"
    break;

  case 674: // $@97: %empty
#line 2391 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3728 "dhcp6_parser.cc"
    break;

  case 675: // ip_addresses: "ip-addresses" $@97 ":" list_strings
#line 2397 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3737 "dhcp6_parser.cc"
    break;

  case 676: // $@98: %empty
#line 2402 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3749 "dhcp6_parser.cc"
    break;

  case 677: // prefixes: "prefixes" $@98 ":" list_strings
#line 2408 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3758 "dhcp6_parser.cc"
    break;

  case 678: // $@99: %empty
#line 2413 "dhcp6_parser.yy"
                                     {
    ctx.unique("excluded-prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3770 "dhcp6_parser.cc"
    break;

  case 679: // excluded_prefixes: "excluded-prefixes" $@99 ":" list_strings
#line 2419 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3779 "dhcp6_parser.cc"
    break;

  case 680: // $@100: %empty
#line 2424 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3788 "dhcp6_parser.cc"
    break;

  case 681: // duid: "duid" $@100 ":" "constant string"
#line 2427 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3798 "dhcp6_parser.cc"
    break;

  case 682: // $@101: %empty
#line 2433 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3807 "dhcp6_parser.cc"
    break;

  case 683: // hw_address: "hw-address" $@101 ":" "constant string"
#line 2436 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3817 "dhcp6_parser.cc"
    break;

  case 684: // $@102: %empty
#line 2442 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3826 "dhcp6_parser.cc"
    break;

  case 685: // hostname: "hostname" $@102 ":" "constant string"
#line 2445 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3836 "dhcp6_parser.cc"
    break;

  case 686: // $@103: %empty
#line 2451 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3845 "dhcp6_parser.cc"
    break;

  case 687: // flex_id_value: "flex-id" $@103 ":" "constant string"
#line 2454 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3855 "dhcp6_parser.cc"
    break;

  case 688: // $@104: %empty
#line 2460 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3867 "dhcp6_parser.cc"
    break;

  case 689: // reservation_client_classes: "client-classes" $@104 ":" list_strings
#line 2466 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3876 "dhcp6_parser.cc"
    break;

  case 690: // $@105: %empty
#line 2474 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3888 "dhcp6_parser.cc"
    break;

  case 691: // relay: "relay" $@105 ":" "{" relay_map "}"
#line 2480 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3897 "dhcp6_parser.cc"
    break;

  case 693: // $@106: %empty
#line 2491 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3909 "dhcp6_parser.cc"
    break;

  case 694: // client_classes: "client-classes" $@106 ":" "[" client_classes_list "]"
#line 2497 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3918 "dhcp6_parser.cc"
    break;

  case 697: // client_classes_list: client_classes_list ","
#line 2504 "dhcp6_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3926 "dhcp6_parser.cc"
    break;

  case 698: // $@107: %empty
#line 2509 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3936 "dhcp6_parser.cc"
    break;

  case 699: // client_class_entry: "{" $@107 client_class_params "}"
#line 2513 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3946 "dhcp6_parser.cc"
    break;

  case 704: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2525 "dhcp6_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3954 "dhcp6_parser.cc"
    break;

  case 720: // $@108: %empty
#line 2548 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3963 "dhcp6_parser.cc"
    break;

  case 721: // client_class_test: "test" $@108 ":" "constant string"
#line 2551 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3973 "dhcp6_parser.cc"
    break;

  case 722: // $@109: %empty
#line 2557 "dhcp6_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3982 "dhcp6_parser.cc"
    break;

  case 723: // client_class_template_test: "template-test" $@109 ":" "constant string"
#line 2560 "dhcp6_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3992 "dhcp6_parser.cc"
    break;

  case 724: // only_if_required: "only-if-required" ":" "boolean"
#line 2566 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 4002 "dhcp6_parser.cc"
    break;

  case 725: // $@110: %empty
#line 2575 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 4014 "dhcp6_parser.cc"
    break;

  case 726: // server_id: "server-id" $@110 ":" "{" server_id_params "}"
#line 2581 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4025 "dhcp6_parser.cc"
    break;

  case 729: // server_id_params: server_id_params ","
#line 2590 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4033 "dhcp6_parser.cc"
    break;

  case 739: // $@111: %empty
#line 2606 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 4042 "dhcp6_parser.cc"
    break;

  case 740: // server_id_type: "type" $@111 ":" duid_type
#line 2609 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4051 "dhcp6_parser.cc"
    break;

  case 741: // duid_type: "LLT"
#line 2614 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 4057 "dhcp6_parser.cc"
    break;

  case 742: // duid_type: "EN"
#line 2615 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 4063 "dhcp6_parser.cc"
    break;

  case 743: // duid_type: "LL"
#line 2616 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 4069 "dhcp6_parser.cc"
    break;

  case 744: // htype: "htype" ":" "integer"
#line 2619 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 4079 "dhcp6_parser.cc"
    break;

  case 745: // $@112: %empty
#line 2625 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4088 "dhcp6_parser.cc"
    break;

  case 746: // identifier: "identifier" $@112 ":" "constant string"
#line 2628 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 4098 "dhcp6_parser.cc"
    break;

  case 747: // time: "time" ":" "integer"
#line 2634 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 4108 "dhcp6_parser.cc"
    break;

  case 748: // enterprise_id: "enterprise-id" ":" "integer"
#line 2640 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 4118 "dhcp6_parser.cc"
    break;

  case 749: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2648 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 4128 "dhcp6_parser.cc"
    break;

  case 750: // $@113: %empty
#line 2656 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4141 "dhcp6_parser.cc"
    break;

  case 751: // control_socket: "control-socket" $@113 ":" "{" control_socket_params "}"
#line 2663 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4150 "dhcp6_parser.cc"
    break;

  case 752: // $@114: %empty
#line 2668 "dhcp6_parser.yy"
                                 {
    ctx.unique("control-sockets", ctx.loc2pos(yystack_[0].location));
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-sockets", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 4163 "dhcp6_parser.cc"
    break;

  case 753: // control_sockets: "control-sockets" $@114 ":" "[" control_socket_list "]"
#line 2675 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4172 "dhcp6_parser.cc"
    break;

  case 758: // not_empty_control_socket_list: not_empty_control_socket_list ","
#line 2686 "dhcp6_parser.yy"
                                                                   {
                                 ctx.warnAboutExtraCommas(yystack_[0].location);
                                 }
#line 4180 "dhcp6_parser.cc"
    break;

  case 759: // $@115: %empty
#line 2691 "dhcp6_parser.yy"
                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4190 "dhcp6_parser.cc"
    break;

  case 760: // control_socket_entry: "{" $@115 control_socket_params "}"
#line 2695 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 4198 "dhcp6_parser.cc"
    break;

  case 763: // control_socket_params: control_socket_params ","
#line 2701 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4206 "dhcp6_parser.cc"
    break;

  case 776: // $@116: %empty
#line 2720 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.CONTROL_SOCKET_TYPE);
}
#line 4215 "dhcp6_parser.cc"
    break;

  case 777: // control_socket_type: "socket-type" $@116 ":" control_socket_type_value
#line 2723 "dhcp6_parser.yy"
                                  {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4224 "dhcp6_parser.cc"
    break;

  case 778: // control_socket_type_value: "unix"
#line 2729 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 4230 "dhcp6_parser.cc"
    break;

  case 779: // control_socket_type_value: "http"
#line 2730 "dhcp6_parser.yy"
         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 4236 "dhcp6_parser.cc"
    break;

  case 780: // control_socket_type_value: "https"
#line 2731 "dhcp6_parser.yy"
          { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("https", ctx.loc2pos(yystack_[0].location))); }
#line 4242 "dhcp6_parser.cc"
    break;

  case 781: // $@117: %empty
#line 2734 "dhcp6_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4252 "dhcp6_parser.cc"
    break;

  case 782: // control_socket_name: "socket-name" $@117 ":" "constant string"
#line 2738 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 4262 "dhcp6_parser.cc"
    break;

  case 783: // $@118: %empty
#line 2744 "dhcp6_parser.yy"
                                       {
    ctx.unique("socket-address", ctx.loc2pos(yystack_[0].location));
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4272 "dhcp6_parser.cc"
    break;

  case 784: // control_socket_address: "socket-address" $@118 ":" "constant string"
#line 2748 "dhcp6_parser.yy"
               {
    ElementPtr address(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-address", address);
    ctx.leave();
}
#line 4282 "dhcp6_parser.cc"
    break;

  case 785: // control_socket_port: "socket-port" ":" "integer"
#line 2754 "dhcp6_parser.yy"
                                               {
    ctx.unique("socket-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr port(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-port", port);
}
#line 4292 "dhcp6_parser.cc"
    break;

  case 786: // cert_required: "cert-required" ":" "boolean"
#line 2760 "dhcp6_parser.yy"
                                           {
    ctx.unique("cert-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr req(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-required", req);
}
#line 4302 "dhcp6_parser.cc"
    break;

  case 787: // $@119: %empty
#line 2768 "dhcp6_parser.yy"
                               {
    ctx.unique("authentication", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authentication", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.AUTHENTICATION);
}
#line 4314 "dhcp6_parser.cc"
    break;

  case 788: // authentication: "authentication" $@119 ":" "{" auth_params "}"
#line 2774 "dhcp6_parser.yy"
                                                  {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4325 "dhcp6_parser.cc"
    break;

  case 791: // auth_params: auth_params ","
#line 2783 "dhcp6_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 4333 "dhcp6_parser.cc"
    break;

  case 799: // $@120: %empty
#line 2797 "dhcp6_parser.yy"
                {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.AUTH_TYPE);
}
#line 4342 "dhcp6_parser.cc"
    break;

  case 800: // auth_type: "type" $@120 ":" auth_type_value
#line 2800 "dhcp6_parser.yy"
                        {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4351 "dhcp6_parser.cc"
    break;

  case 801: // auth_type_value: "basic"
#line 2805 "dhcp6_parser.yy"
                       { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("basic", ctx.loc2pos(yystack_[0].location))); }
#line 4357 "dhcp6_parser.cc"
    break;

  case 802: // $@121: %empty
#line 2808 "dhcp6_parser.yy"
             {
    ctx.unique("realm", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4366 "dhcp6_parser.cc"
    break;

  case 803: // realm: "realm" $@121 ":" "constant string"
#line 2811 "dhcp6_parser.yy"
               {
    ElementPtr realm(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("realm", realm);
    ctx.leave();
}
#line 4376 "dhcp6_parser.cc"
    break;

  case 804: // $@122: %empty
#line 2817 "dhcp6_parser.yy"
                     {
    ctx.unique("directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4385 "dhcp6_parser.cc"
    break;

  case 805: // directory: "directory" $@122 ":" "constant string"
#line 2820 "dhcp6_parser.yy"
               {
    ElementPtr directory(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("directory", directory);
    ctx.leave();
}
#line 4395 "dhcp6_parser.cc"
    break;

  case 806: // $@123: %empty
#line 2826 "dhcp6_parser.yy"
                 {
    ctx.unique("clients", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("clients", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENTS);
}
#line 4407 "dhcp6_parser.cc"
    break;

  case 807: // clients: "clients" $@123 ":" "[" clients_list "]"
#line 2832 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4416 "dhcp6_parser.cc"
    break;

  case 812: // not_empty_clients_list: not_empty_clients_list ","
#line 2843 "dhcp6_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 4424 "dhcp6_parser.cc"
    break;

  case 813: // $@124: %empty
#line 2848 "dhcp6_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4434 "dhcp6_parser.cc"
    break;

  case 814: // basic_auth: "{" $@124 clients_params "}"
#line 2852 "dhcp6_parser.yy"
                                {
    ctx.stack_.pop_back();
}
#line 4442 "dhcp6_parser.cc"
    break;

  case 817: // clients_params: clients_params ","
#line 2858 "dhcp6_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 4450 "dhcp6_parser.cc"
    break;

  case 825: // $@125: %empty
#line 2872 "dhcp6_parser.yy"
                     {
    ctx.unique("user-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4459 "dhcp6_parser.cc"
    break;

  case 826: // user_file: "user-file" $@125 ":" "constant string"
#line 2875 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user-file", user);
    ctx.leave();
}
#line 4469 "dhcp6_parser.cc"
    break;

  case 827: // $@126: %empty
#line 2881 "dhcp6_parser.yy"
                             {
    ctx.unique("password-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4478 "dhcp6_parser.cc"
    break;

  case 828: // password_file: "password-file" $@126 ":" "constant string"
#line 2884 "dhcp6_parser.yy"
               {
    ElementPtr password(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password-file", password);
    ctx.leave();
}
#line 4488 "dhcp6_parser.cc"
    break;

  case 829: // $@127: %empty
#line 2892 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 4500 "dhcp6_parser.cc"
    break;

  case 830: // dhcp_queue_control: "dhcp-queue-control" $@127 ":" "{" queue_control_params "}"
#line 2898 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4511 "dhcp6_parser.cc"
    break;

  case 833: // queue_control_params: queue_control_params ","
#line 2907 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4519 "dhcp6_parser.cc"
    break;

  case 840: // enable_queue: "enable-queue" ":" "boolean"
#line 2920 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4529 "dhcp6_parser.cc"
    break;

  case 841: // $@128: %empty
#line 2926 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4538 "dhcp6_parser.cc"
    break;

  case 842: // queue_type: "queue-type" $@128 ":" "constant string"
#line 2929 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4548 "dhcp6_parser.cc"
    break;

  case 843: // capacity: "capacity" ":" "integer"
#line 2935 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4558 "dhcp6_parser.cc"
    break;

  case 844: // $@129: %empty
#line 2941 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4567 "dhcp6_parser.cc"
    break;

  case 845: // arbitrary_map_entry: "constant string" $@129 ":" value
#line 2944 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4576 "dhcp6_parser.cc"
    break;

  case 846: // $@130: %empty
#line 2951 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4588 "dhcp6_parser.cc"
    break;

  case 847: // dhcp_ddns: "dhcp-ddns" $@130 ":" "{" dhcp_ddns_params "}"
#line 2957 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4599 "dhcp6_parser.cc"
    break;

  case 848: // $@131: %empty
#line 2964 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4609 "dhcp6_parser.cc"
    break;

  case 849: // sub_dhcp_ddns: "{" $@131 dhcp_ddns_params "}"
#line 2968 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4619 "dhcp6_parser.cc"
    break;

  case 852: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2976 "dhcp6_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4627 "dhcp6_parser.cc"
    break;

  case 864: // enable_updates: "enable-updates" ":" "boolean"
#line 2994 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4637 "dhcp6_parser.cc"
    break;

  case 865: // $@132: %empty
#line 3000 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4646 "dhcp6_parser.cc"
    break;

  case 866: // server_ip: "server-ip" $@132 ":" "constant string"
#line 3003 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4656 "dhcp6_parser.cc"
    break;

  case 867: // server_port: "server-port" ":" "integer"
#line 3009 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4666 "dhcp6_parser.cc"
    break;

  case 868: // $@133: %empty
#line 3015 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4675 "dhcp6_parser.cc"
    break;

  case 869: // sender_ip: "sender-ip" $@133 ":" "constant string"
#line 3018 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4685 "dhcp6_parser.cc"
    break;

  case 870: // sender_port: "sender-port" ":" "integer"
#line 3024 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4695 "dhcp6_parser.cc"
    break;

  case 871: // max_queue_size: "max-queue-size" ":" "integer"
#line 3030 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4705 "dhcp6_parser.cc"
    break;

  case 872: // $@134: %empty
#line 3036 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4714 "dhcp6_parser.cc"
    break;

  case 873: // ncr_protocol: "ncr-protocol" $@134 ":" ncr_protocol_value
#line 3039 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4723 "dhcp6_parser.cc"
    break;

  case 874: // ncr_protocol_value: "UDP"
#line 3045 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4729 "dhcp6_parser.cc"
    break;

  case 875: // ncr_protocol_value: "TCP"
#line 3046 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4735 "dhcp6_parser.cc"
    break;

  case 876: // $@135: %empty
#line 3049 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4744 "dhcp6_parser.cc"
    break;

  case 877: // ncr_format: "ncr-format" $@135 ":" "JSON"
#line 3052 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4754 "dhcp6_parser.cc"
    break;

  case 878: // $@136: %empty
#line 3060 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4766 "dhcp6_parser.cc"
    break;

  case 879: // config_control: "config-control" $@136 ":" "{" config_control_params "}"
#line 3066 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4776 "dhcp6_parser.cc"
    break;

  case 880: // $@137: %empty
#line 3072 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4786 "dhcp6_parser.cc"
    break;

  case 881: // sub_config_control: "{" $@137 config_control_params "}"
#line 3076 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4795 "dhcp6_parser.cc"
    break;

  case 884: // config_control_params: config_control_params ","
#line 3084 "dhcp6_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4803 "dhcp6_parser.cc"
    break;

  case 887: // $@138: %empty
#line 3094 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4815 "dhcp6_parser.cc"
    break;

  case 888: // config_databases: "config-databases" $@138 ":" "[" database_list "]"
#line 3100 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4824 "dhcp6_parser.cc"
    break;

  case 889: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 3105 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4834 "dhcp6_parser.cc"
    break;

  case 890: // $@139: %empty
#line 3113 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4846 "dhcp6_parser.cc"
    break;

  case 891: // loggers: "loggers" $@139 ":" "[" loggers_entries "]"
#line 3119 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4855 "dhcp6_parser.cc"
    break;

  case 894: // loggers_entries: loggers_entries ","
#line 3128 "dhcp6_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4863 "dhcp6_parser.cc"
    break;

  case 895: // $@140: %empty
#line 3134 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4873 "dhcp6_parser.cc"
    break;

  case 896: // logger_entry: "{" $@140 logger_params "}"
#line 3138 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4881 "dhcp6_parser.cc"
    break;

  case 899: // logger_params: logger_params ","
#line 3144 "dhcp6_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4889 "dhcp6_parser.cc"
    break;

  case 907: // debuglevel: "debuglevel" ":" "integer"
#line 3158 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4899 "dhcp6_parser.cc"
    break;

  case 908: // $@141: %empty
#line 3164 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4908 "dhcp6_parser.cc"
    break;

  case 909: // severity: "severity" $@141 ":" "constant string"
#line 3167 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4918 "dhcp6_parser.cc"
    break;

  case 910: // $@142: %empty
#line 3173 "dhcp6_parser.yy"
                                    {
    ctx.unique("output-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4930 "dhcp6_parser.cc"
    break;

  case 911: // output_options_list: "output-options" $@142 ":" "[" output_options_list_content "]"
#line 3179 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4939 "dhcp6_parser.cc"
    break;

  case 914: // output_options_list_content: output_options_list_content ","
#line 3186 "dhcp6_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4947 "dhcp6_parser.cc"
    break;

  case 915: // $@143: %empty
#line 3191 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4957 "dhcp6_parser.cc"
    break;

  case 916: // output_entry: "{" $@143 output_params_list "}"
#line 3195 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4965 "dhcp6_parser.cc"
    break;

  case 919: // output_params_list: output_params_list ","
#line 3201 "dhcp6_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4973 "dhcp6_parser.cc"
    break;

  case 925: // $@144: %empty
#line 3213 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4982 "dhcp6_parser.cc"
    break;

  case 926: // output: "output" $@144 ":" "constant string"
#line 3216 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4992 "dhcp6_parser.cc"
    break;

  case 927: // flush: "flush" ":" "boolean"
#line 3222 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 5002 "dhcp6_parser.cc"
    break;

  case 928: // maxsize: "maxsize" ":" "integer"
#line 3228 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 5012 "dhcp6_parser.cc"
    break;

  case 929: // maxver: "maxver" ":" "integer"
#line 3234 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 5022 "dhcp6_parser.cc"
    break;

  case 930: // $@145: %empty
#line 3240 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 5031 "dhcp6_parser.cc"
    break;

  case 931: // pattern: "pattern" $@145 ":" "constant string"
#line 3243 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 5041 "dhcp6_parser.cc"
    break;

  case 932: // $@146: %empty
#line 3249 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 5053 "dhcp6_parser.cc"
    break;

  case 933: // compatibility: "compatibility" $@146 ":" "{" compatibility_params "}"
#line 3255 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 5062 "dhcp6_parser.cc"
    break;

  case 936: // compatibility_params: compatibility_params ","
#line 3262 "dhcp6_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 5070 "dhcp6_parser.cc"
    break;

  case 939: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 3271 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 5080 "dhcp6_parser.cc"
    break;


#line 5084 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -1339;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     199, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339,    70,    38,    92,    94,   100,
     104,   124,   131,   134,   138,   142,   172,   184,   206,   256,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,    38,  -156,
     119,   727,    34,  1086,   251,   263,   168,    -2,   109,   157,
     -84,   216,   233, -1339,   113,   204,   277,    76,   290, -1339,
      63, -1339, -1339, -1339, -1339, -1339, -1339, -1339,   303,   305,
     307,   346,   350,   357,   428,   440,   441,   444,   445,   450,
     451,   452, -1339,   453,   454,   455,   456,   457, -1339, -1339,
   -1339,   459,   460,   461,   464, -1339, -1339, -1339,   465, -1339,
   -1339, -1339, -1339, -1339, -1339,   466,   467,   470, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339,   472, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339,   474,   476,   481, -1339, -1339,
     482, -1339,    65, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339,   483,   484,   485,   487, -1339,   106, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339,   491,   493, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339,   114, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339,   500, -1339, -1339, -1339,
   -1339,   122, -1339, -1339, -1339, -1339, -1339, -1339,   501, -1339,
     503,   505, -1339, -1339, -1339, -1339, -1339, -1339, -1339,   145,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,   334,   372,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,   502,
   -1339, -1339,   508, -1339, -1339, -1339,   511, -1339, -1339,   510,
     513, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339,   515,   516,   517, -1339, -1339, -1339,
   -1339,   514,   520, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339,   148, -1339, -1339, -1339,
     521, -1339,   523, -1339,   527,   528, -1339, -1339, -1339, -1339,
   -1339,   154, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339,   530,   200, -1339, -1339, -1339, -1339,    38,    38,
   -1339,   294,   533, -1339, -1339,   534,   535,   538,   539,   541,
     542,   316,   317,   318,   319,   321,   324,   325,   328,   330,
     332,   335,   339,   343,   344,   553,   348,   351,   336,   352,
     355,   556,   557,   573,   356,   360,   358,   362,   579,   583,
     592,   367,   595,   597,   598,   599,   601,   602,   375,   376,
     378,   609,   612,   613,   615,   616,   617,   618,   620,   621,
     395,   623,   624,   625,   627,   628,   629,   630,   402,   403,
     404,   634,   635, -1339,   727, -1339,   636,   408,   409,   412,
     413,    34, -1339,   641,   642,   643,   644,   645,   419,   418,
     648,   649,   650,  1086, -1339,   651,   426,   251, -1339,   654,
     429,   657,   431,   432,   263, -1339,   660,   661,   662,   663,
     664,   665,   666,   667, -1339,   168, -1339,   668,   669,   443,
     671,   673,   674,   446, -1339,   109,   676,   448,   449,   458,
   -1339,   157,   679,   680,   180, -1339,   468,   681,   462,   682,
     469,   471,   683,   684,   216, -1339,   685,   473,   233, -1339,
   -1339, -1339,   686,   690,   475,   691,   699,   700,   701,   687,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339,   479, -1339, -1339, -1339, -1339, -1339,
    -137,   480,   488, -1339, -1339, -1339, -1339,   709,   712,   714,
   -1339,   490,   492,    -6,   718,   717,   495, -1339, -1339, -1339,
     721,   722,   723,   724,   725,   728,   729,   733,   734, -1339,
     736,   737,   730,   738,   739,   499,   506, -1339, -1339, -1339,
     742,   744, -1339,   747, -1339, -1339, -1339, -1339, -1339,   748,
     749,   525,   526,   529, -1339, -1339,   747,   531,   750, -1339,
     532, -1339, -1339,   536, -1339,   537, -1339, -1339, -1339,   747,
     747,   747,   747,   540,   545,   578,   580, -1339,   581,   582,
   -1339,   584,   585,   586, -1339, -1339,   587, -1339, -1339, -1339,
   -1339,   593,   717, -1339, -1339,   594, -1339,   600, -1339, -1339,
     189,   563, -1339,   755, -1339, -1339,    38,   727, -1339,   233,
      34,   135,   135,   756, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339,   757,   758,   761, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339,   762, -1339, -1339, -1339,   -91,    38,   274,
     241,   764,   802,   806,   292,    80,    69,   147,   815,    19,
     216, -1339, -1339,   818,  -143, -1339, -1339,   820,   821, -1339,
   -1339, -1339, -1339, -1339,   697, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
     756, -1339,   211,   212,   224, -1339, -1339, -1339, -1339,   827,
     828,   829,   830,   833,   834,   835,   836,   837,   845, -1339,
     846,   848, -1339, -1339, -1339, -1339, -1339,   225, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339,   259, -1339,   726,   850, -1339, -1339,   849,   851, -1339,
   -1339,   853,   854, -1339, -1339,   855,   857, -1339, -1339,   856,
     860, -1339, -1339, -1339,    72, -1339, -1339, -1339,   858, -1339,
   -1339, -1339,    97, -1339, -1339, -1339, -1339, -1339,   272, -1339,
   -1339, -1339, -1339,   112, -1339, -1339,   859,   863, -1339, -1339,
     862,   866, -1339,   852,   867,   868,   869,   870,   871,   279,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,   872,
     874,   875, -1339, -1339, -1339, -1339,   280, -1339, -1339, -1339,
   -1339, -1339, -1339,   876,   877,   878, -1339,   281, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339,   879, -1339,   880,
   -1339, -1339, -1339, -1339, -1339, -1339,   312, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339,   881,   885, -1339,   888, -1339,
     889, -1339, -1339, -1339,   320, -1339, -1339, -1339, -1339, -1339,
     326, -1339,   327, -1339,   890, -1339,   329, -1339, -1339,   659,
   -1339,   891,   892, -1339, -1339,   893,   895, -1339, -1339,   894,
     897, -1339, -1339, -1339,   896,   900,   901,   902,   670,   675,
     678,   677,   688,   689,   692,   693,   694,   695,   908,   702,
     703,   909,   910,   911,   912,   135, -1339, -1339,   135, -1339,
     756,  1086, -1339,   757,   109, -1339,   758,   157, -1339,   761,
    1343, -1339,   762,   -91, -1339, -1339,   274, -1339,   913,   914,
     241, -1339,   170,   764, -1339,   168, -1339,   802,   -84, -1339,
     806,   705,   706,   707,   708,   711,   713,   292, -1339,   917,
     918,   715,   716,   719,    80, -1339,   710,   720,   731,    69,
   -1339,   929,   936,   941,   732,   944,   735,   147, -1339,   147,
   -1339,   815,   741,   945,   740,   948,    19, -1339, -1339,   205,
     818, -1339,   745,  -143, -1339, -1339,   947,   951,   251, -1339,
     820,   263, -1339,   821, -1339, -1339,   247,   751,   765,   768,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
     353, -1339, -1339,   769,   772,   773,   775, -1339,   337, -1339,
     338, -1339,   950, -1339,   952, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339,   341, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339,   782,   792, -1339, -1339, -1339,   955,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339,   953,   961, -1339, -1339, -1339, -1339, -1339, -1339,   957,
   -1339,   354, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
     278,   793, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
     285,   795,   799, -1339,   949, -1339, -1339,   370, -1339, -1339,
     803, -1339,    38, -1339, -1339,   962, -1339, -1339, -1339, -1339,
   -1339,   371, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
     804,   381, -1339,   382, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339,  1343, -1339, -1339, -1339,   963,   965,
     753, -1339,   170, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339,    78, -1339, -1339, -1339,
     968,   746,   971,   205, -1339, -1339, -1339, -1339, -1339,   810,
     811, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
     383, -1339, -1339, -1339, -1339, -1339,   983, -1339,   819, -1339,
   -1339, -1339,  1032,  1052,  1056,  1059,    78, -1339,  1061, -1339,
     922,   903,   904,  1081, -1339, -1339,   345, -1339, -1339, -1339,
   -1339, -1339,  1092,    -1,  1061, -1339, -1339,  1113,  1127, -1339,
   -1339,  1146,  1147,  1148, -1339,   391, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339,    27, -1339,  1092,  1149,   931,   934,   937,
    1163,    -1, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
     439, -1339, -1339, -1339, -1339,   939, -1339, -1339, -1339,   940,
   -1339,  1167,  1168,    27, -1339, -1339, -1339,   943,   946, -1339,
   -1339, -1339
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
     559,    23,   350,    25,   848,    27,   880,    29,    48,    41,
       0,     0,     0,     0,     0,     0,   657,     0,   522,   561,
       0,     0,     0,    50,     0,    49,     0,     0,    42,    63,
       0,    65,   141,   878,   197,   218,   220,   222,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   187,     0,     0,     0,     0,     0,   160,   167,
     169,     0,     0,     0,     0,   379,   509,   550,     0,   190,
     192,   173,   454,   609,   611,     0,     0,     0,   306,   325,
     315,   295,   693,   646,   341,   362,   725,     0,   327,   750,
     752,   829,   846,   180,   182,     0,     0,     0,   890,   932,
       0,   140,     0,    69,    72,    73,    74,    75,    76,    77,
      78,    79,    80,   111,   112,   113,   114,   115,    81,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   117,
     118,   129,   130,   131,   107,   137,   138,   139,   133,   134,
     135,    84,    85,    86,    87,   104,    88,    90,    89,   132,
      94,    95,    82,   108,   109,   110,    83,    92,    93,   102,
     103,   105,    91,    96,    97,    98,    99,   100,   101,   106,
     116,   136,   212,     0,     0,     0,     0,   211,     0,   201,
     204,   205,   206,   207,   208,   209,   210,   584,   613,   439,
     441,   443,     0,     0,   447,   445,   690,   438,   393,   394,
     395,   396,   397,   398,   399,   400,   418,   419,   420,   421,
     422,   425,   426,   427,   428,   429,   430,   431,   432,   433,
     434,   423,   424,   435,   436,   437,     0,   390,   404,   405,
     406,   409,   410,   412,   413,   414,   407,   408,   401,   402,
     416,   417,   403,   411,   415,   606,     0,   605,   601,   602,
     600,     0,   595,   598,   599,   603,   604,   639,     0,   642,
       0,     0,   638,   632,   633,   631,   630,   636,   637,     0,
     624,   627,   628,   634,   635,   629,   688,   674,   676,   678,
     680,   682,   684,   686,   673,   670,   671,   672,     0,   658,
     659,   664,   665,   666,   662,   667,   668,   669,   663,     0,
     540,   269,     0,   544,   542,   547,     0,   536,   537,     0,
     523,   524,   527,   539,   528,   529,   530,   546,   531,   532,
     533,   534,   535,   577,     0,     0,     0,   575,   576,   579,
     580,     0,   562,   563,   566,   567,   568,   569,   570,   571,
     572,   573,   574,   358,   360,   355,     0,   352,   356,   357,
       0,   865,     0,   868,     0,     0,   872,   876,   863,   861,
     862,     0,   850,   853,   854,   855,   856,   857,   858,   859,
     860,   887,     0,     0,   882,   885,   886,    47,    52,     0,
      39,    45,     0,    66,    62,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    60,    71,    68,     0,     0,     0,     0,
       0,   203,   200,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   392,   389,     0,     0,   597,   594,     0,
       0,     0,     0,     0,   626,   623,     0,     0,     0,     0,
       0,     0,     0,     0,   656,   661,   512,     0,     0,     0,
       0,     0,     0,     0,   521,   526,     0,     0,     0,     0,
     560,   565,     0,     0,   354,   351,     0,     0,     0,     0,
       0,     0,     0,     0,   852,   849,     0,     0,   884,   881,
      51,    43,     0,     0,     0,     0,     0,     0,     0,     0,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,     0,   185,   186,   157,   158,   159,
       0,     0,     0,   171,   172,   179,   184,     0,     0,     0,
     189,     0,     0,     0,     0,     0,     0,   449,   450,   451,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   749,
       0,     0,     0,     0,     0,     0,     0,   194,   195,   196,
       0,     0,    70,     0,   214,   215,   216,   217,   202,     0,
       0,     0,     0,     0,   452,   453,     0,     0,     0,   391,
       0,   608,   596,     0,   641,     0,   644,   645,   625,     0,
       0,     0,     0,     0,     0,     0,     0,   660,     0,     0,
     538,     0,     0,     0,   549,   525,     0,   581,   582,   583,
     564,     0,     0,   353,   864,     0,   867,     0,   870,   871,
       0,     0,   851,     0,   889,   883,     0,     0,   142,     0,
       0,     0,     0,   224,   188,   162,   163,   164,   165,   166,
     161,   168,   170,   381,   513,   552,   191,   193,   175,   176,
     177,   178,   174,   456,    40,   610,   612,     0,    48,     0,
       0,     0,   648,   343,     0,     0,     0,     0,   754,     0,
       0,   181,   183,     0,     0,    53,   213,   586,   615,   440,
     442,   444,   448,   446,     0,   607,   640,   643,   689,   675,
     677,   679,   681,   683,   685,   687,   541,   270,   545,   543,
     548,   578,   359,   361,   866,   869,   874,   875,   873,   877,
     224,    44,     0,     0,     0,   257,   262,   264,   266,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   279,
       0,     0,   287,   289,   291,   293,   256,     0,   231,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   248,   249,   250,   251,   247,   252,   253,   254,
     255,     0,   229,     0,   225,   226,   386,     0,   382,   383,
     518,     0,   514,   515,   557,     0,   553,   554,   461,     0,
     457,   458,   313,   314,     0,   308,   311,   312,     0,   323,
     324,   320,     0,   317,   321,   322,   302,   304,     0,   297,
     300,   301,   698,     0,   695,   653,     0,   649,   650,   348,
       0,   344,   345,     0,     0,     0,     0,     0,     0,     0,
     364,   367,   368,   369,   370,   371,   372,   739,   745,     0,
       0,     0,   738,   735,   736,   737,     0,   727,   730,   733,
     731,   732,   734,     0,     0,     0,   337,     0,   329,   332,
     333,   334,   335,   336,   776,   781,   783,     0,   787,     0,
     775,   769,   770,   771,   773,   774,     0,   761,   764,   765,
     766,   767,   772,   768,   759,     0,   755,   756,     0,   841,
       0,   844,   837,   838,     0,   831,   834,   835,   836,   839,
       0,   895,     0,   892,     0,   938,     0,   934,   937,    55,
     591,     0,   587,   588,   620,     0,   616,   617,   692,     0,
       0,    64,   879,   198,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   233,   219,   221,     0,   223,
     228,     0,   380,   385,   522,   510,   517,   561,   551,   556,
       0,   455,   460,   310,   307,   326,   319,   316,     0,     0,
     299,   296,   700,   697,   694,   657,   647,   652,     0,   342,
     347,     0,     0,     0,     0,     0,     0,   366,   363,     0,
       0,     0,     0,     0,   729,   726,     0,     0,     0,   331,
     328,     0,     0,     0,     0,     0,     0,   763,   751,     0,
     753,   758,     0,     0,     0,     0,   833,   830,   847,     0,
     894,   891,     0,   936,   933,    57,     0,    56,     0,   585,
     590,     0,   614,   619,   691,   888,     0,     0,     0,     0,
     268,   271,   272,   273,   274,   275,   276,   277,   286,   278,
       0,   284,   285,     0,     0,     0,     0,   232,     0,   227,
       0,   384,     0,   516,     0,   555,   508,   479,   480,   481,
     483,   484,   485,   470,   471,   488,   489,   490,   491,   492,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     493,   494,   505,   506,   507,   466,   467,   468,   469,   477,
     478,   474,   475,   476,   482,     0,   463,   472,   486,   487,
     473,   459,   309,   318,     0,     0,   298,   720,   722,     0,
     718,   712,   713,   714,   715,   716,   717,   719,   709,   710,
     711,     0,   701,   702,   705,   706,   707,   708,   696,     0,
     651,     0,   346,   373,   374,   375,   376,   377,   378,   365,
       0,     0,   744,   747,   748,   728,   338,   339,   340,   330,
       0,     0,     0,   785,     0,   786,   762,     0,   757,   840,
       0,   843,     0,   832,   910,     0,   908,   906,   900,   904,
     905,     0,   897,   902,   903,   901,   893,   939,   935,    54,
      59,     0,   589,     0,   618,   259,   260,   261,   258,   263,
     265,   267,   281,   282,   283,   280,   288,   290,   292,   294,
     230,   387,   519,   558,   465,   462,   303,   305,     0,     0,
       0,   699,   704,   654,   349,   741,   742,   743,   740,   746,
     778,   779,   780,   777,   782,   784,     0,   760,   842,   845,
       0,     0,     0,   899,   896,    58,   592,   621,   464,     0,
       0,   724,   703,   799,   802,   804,   806,   798,   797,   796,
       0,   789,   792,   793,   794,   795,     0,   907,     0,   898,
     721,   723,     0,     0,     0,     0,   791,   788,     0,   909,
       0,     0,     0,     0,   790,   915,     0,   912,   801,   800,
     803,   805,   808,     0,   914,   911,   813,     0,   809,   810,
     925,     0,     0,     0,   930,     0,   917,   920,   921,   922,
     923,   924,   913,     0,   807,   812,     0,     0,     0,     0,
       0,   919,   916,   825,   827,   824,   818,   820,   822,   823,
       0,   815,   819,   821,   811,     0,   927,   928,   929,     0,
     918,     0,     0,   817,   814,   926,   931,     0,     0,   816,
     826,   828
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339,    -5, -1339,  -589, -1339,
     243, -1339, -1339, -1339, -1339,   416, -1339,  -431, -1339, -1339,
   -1339,   -71, -1339, -1339, -1339, -1339, -1339, -1339, -1339,   169,
     696, -1339, -1339,   -61,   -58,   -35,   -31,    -4,     3,   -34,
      20,    21,    25,    32,    33,    35, -1339,    37,    40,    43,
      47, -1339, -1339,    48, -1339,    51, -1339,    53,    59,    61,
   -1339, -1339,    64,    67, -1339,    71, -1339,    74, -1339, -1339,
   -1339, -1339, -1339,    77, -1339,    79, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339,   447,   672, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,   365, -1339,
     141, -1339,  -703,   149, -1339, -1339, -1339, -1338, -1339, -1336,
   -1339, -1339, -1339, -1339,   -30, -1339,  -737, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
    -761, -1339,  -744, -1339,  -741, -1339, -1339, -1339, -1339, -1339,
   -1339,   123, -1339, -1339, -1339, -1339, -1339, -1339, -1339,   129,
    -729, -1339, -1339, -1339, -1339,   133, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339,    96, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339,   117, -1339, -1339, -1339,   137,   632, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339,   115, -1339, -1339, -1339, -1339, -1339,
   -1339, -1019, -1339, -1339, -1339,   165, -1339, -1339, -1339,   150,
     698, -1339, -1339, -1014, -1339, -1013, -1339,   -11, -1339,    86,
   -1339,    81,    82,    85, -1339, -1010, -1339, -1339, -1339, -1339,
     160, -1339, -1339,  -114,  1132, -1339, -1339, -1339, -1339, -1339,
     167, -1339, -1339, -1339,   174, -1339,   655, -1339,   -65, -1339,
   -1339, -1339, -1339, -1339,   -63, -1339, -1339, -1339, -1339, -1339,
     -41, -1339, -1339, -1339,   173, -1339, -1339, -1339,   176, -1339,
     653, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339,    99, -1339, -1339, -1339,    98,   743, -1339,
   -1339,   -62,   -54, -1339,     7, -1339, -1339, -1339, -1339, -1339,
      91, -1339, -1339, -1339,   105,   704, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339,   -56, -1339, -1339, -1339,   161, -1339, -1339,
   -1339,   156, -1339,   754,   463, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1009, -1339, -1339, -1339, -1339, -1339,   164, -1339, -1339, -1339,
     -83, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
     146, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339,   136, -1339,   139,   143,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339,  -134, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339,  -171, -1339, -1339,  -198, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339,   130, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339,   486,   658, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339,   524,   656, -1339, -1339, -1339,
   -1339, -1339, -1339,   151, -1339, -1339,   -94, -1339, -1339, -1339,
   -1339, -1339, -1339,  -139, -1339, -1339,  -162, -1339, -1339, -1339,
   -1339, -1339, -1339, -1339, -1339, -1339, -1339,   152, -1339
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     755,    87,    88,    41,    68,    84,    85,   776,   999,  1116,
    1117,   836,    43,    70,    90,   442,    91,    45,    71,   162,
     163,   164,   445,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   471,   740,   183,   472,   184,   473,   185,   186,   187,
     484,   752,   188,   189,   506,   190,   507,   191,   192,   193,
     194,   465,   195,   196,   482,   197,   483,   198,   199,   200,
     201,   447,    47,    72,   238,   239,   240,   516,   241,   242,
     243,   244,   202,   448,   203,   449,   204,   450,   863,   864,
     865,  1038,   837,   838,   839,  1014,  1288,   840,  1015,   841,
    1016,   842,  1017,   843,   844,   558,   845,   846,   847,   848,
     849,   850,   851,   852,   853,  1028,  1295,   854,   855,   856,
     857,  1031,   858,  1032,   859,  1033,   860,  1034,   205,   494,
     898,   899,   900,  1058,   901,  1059,   206,   491,   884,   885,
     886,   887,   207,   493,   892,   893,   894,   895,   208,   492,
     209,   501,   947,   948,   949,   950,   951,   210,   497,   910,
     911,   912,  1068,    63,    80,   406,   407,   408,   572,   409,
     573,   211,   498,   919,   920,   921,   922,   923,   924,   925,
     926,   212,   478,   867,   868,   869,  1041,    49,    73,   286,
     287,   288,   525,   289,   526,   290,   527,   291,   531,   292,
     530,   213,   214,   215,   296,   297,   216,   485,   879,   880,
     881,  1050,  1195,  1196,   217,   479,    57,    77,   871,   872,
     873,  1044,    59,    78,   369,   370,   371,   372,   373,   374,
     375,   557,   376,   561,   377,   560,   378,   379,   562,   380,
     218,   480,   875,   876,   877,  1047,    61,    79,   391,   392,
     393,   394,   395,   566,   396,   397,   398,   399,   400,   299,
     523,  1001,  1002,  1003,  1118,    51,    74,   311,   312,   313,
     535,   314,   219,   486,   220,   487,   302,   524,  1005,  1006,
    1007,  1121,    53,    75,   329,   330,   331,   539,   332,   333,
     541,   334,   335,   221,   496,   906,   907,   908,  1065,    55,
      76,   348,   349,   350,   351,   547,   352,   548,   353,   549,
     354,   550,   355,   551,   356,   552,   357,   553,   358,   546,
     304,   532,  1009,   222,   495,   903,   904,  1062,  1221,  1222,
    1223,  1224,  1225,  1308,  1226,  1309,  1227,   223,   499,   936,
     937,   938,  1079,  1318,   939,   940,  1080,   941,   942,   224,
     225,   502,   226,   503,   975,   976,   977,  1099,   966,   967,
     968,  1091,  1323,   969,  1092,   970,  1093,   971,   972,   973,
    1095,  1350,  1351,  1352,  1362,  1379,  1353,  1363,  1354,  1364,
    1355,  1365,  1387,  1388,  1389,  1403,  1420,  1421,  1422,  1431,
    1423,  1432,   227,   504,   984,   985,   986,   987,  1103,   988,
     989,  1105,   228,   505,    65,    81,   421,   422,   423,   424,
     577,   425,   426,   579,   427,   428,   429,   582,   808,   430,
     583,   229,   446,    67,    82,   433,   434,   435,   586,   436,
     230,   511,   992,   993,  1109,  1271,  1272,  1273,  1274,  1332,
    1275,  1330,  1376,  1377,  1383,  1395,  1396,  1397,  1406,  1398,
    1399,  1400,  1401,  1410,   231,   512,   996,   997,   998
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     161,   237,   257,   307,   322,   344,   961,   367,   387,   405,
     418,    38,   258,   326,   389,   259,   390,   303,   245,   300,
     315,   327,   346,   962,   381,   401,   963,   419,   933,   861,
     891,  1186,   298,   310,   325,   345,  1187,  1188,   260,   264,
    1194,  1200,   261,    31,   882,    32,   754,    33,   368,   388,
     232,   233,   234,   235,   236,   816,   817,   403,   404,   735,
     736,   737,   738,   308,   323,  1416,   443,  1417,   514,   262,
      30,   444,   994,   515,    86,  1053,   263,   126,  1054,   246,
     301,   316,   328,   347,   440,   382,   402,   160,   420,   748,
     749,   750,   751,   265,   266,  1416,   739,  1417,   267,    42,
    1056,    44,  1343,  1057,   927,   268,   269,    46,   270,   521,
     271,    48,   820,   272,   522,  1063,   273,   533,  1064,   437,
     274,   275,   534,   754,   276,   537,   277,   133,   134,    89,
     538,    50,   278,   360,   279,   133,   134,   280,    52,   883,
     281,    54,   133,   134,   282,    56,   160,   283,   544,    58,
     284,   574,   285,   545,   293,   294,   575,   584,   295,   815,
     309,   324,   585,   816,   817,   818,   819,   820,   821,   822,
     823,   824,   825,   826,   827,   828,   829,   133,   134,    60,
     830,   831,   832,   833,   834,   835,   133,   134,   133,   134,
     361,    62,   362,   363,   832,   833,   834,   364,   365,   366,
     978,   979,   980,   588,  1413,  1414,  1390,   438,   589,  1391,
    1392,  1393,  1394,    64,   514,   588,   361,   133,   134,  1011,
    1012,    98,    99,   100,   101,   102,   103,   521,  1035,   943,
     944,   945,  1013,  1036,   928,   929,   930,   931,   361,   383,
     362,   363,   384,   385,   386,   782,   431,   432,   127,   981,
     127,   361,  1344,  1345,  1346,   133,   134,   160,   788,   789,
     790,   791,  1035,    66,   160,   133,   134,  1037,    34,    35,
      36,    37,  1285,  1286,  1287,  1060,   133,   134,   133,   134,
    1061,   439,  1077,  1084,  1089,  1186,   361,  1078,  1085,  1090,
    1187,  1188,   336,   441,  1194,  1200,  1207,  1208,  1209,   160,
     337,   338,   339,   340,   341,   342,   343,   451,   160,   452,
     160,   453,   954,   133,   134,  1097,   955,   956,   957,   958,
    1098,   403,   404,  1106,   133,   134,   959,   891,  1107,   584,
    1110,   127,  1113,  1111,  1108,  1148,   961,  1114,   961,   160,
    1035,   533,   554,   127,  1304,  1300,  1301,   933,  1384,  1305,
     454,  1385,   305,   962,   455,   962,   963,   574,   963,   133,
     134,   456,  1314,   896,   897,   160,   317,   318,   319,   320,
     321,   133,   134,  1097,  1333,   555,   254,   160,  1327,  1334,
     255,   306,   806,   807,   537,   544,  1366,   160,   254,  1336,
    1337,  1367,   255,   306,  1411,  1292,  1293,  1294,   160,  1412,
     160,   410,   411,   412,   413,   414,   415,   416,   417,   882,
     889,  1264,   890,  1265,  1266,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,  1315,
    1316,  1317,   457,   590,   591,   160,   913,   914,   915,   916,
     917,   918,  1433,   161,   458,   459,   160,  1434,   460,   461,
     237,  1320,  1321,  1322,   462,   463,   464,   466,   467,   468,
     469,   470,   257,   474,   475,   476,   307,   245,   477,   481,
     488,   489,   258,   322,   490,   259,   500,   303,   508,   300,
     509,   160,   326,   315,   344,   510,   513,   517,   518,   519,
     327,   520,   298,   160,   367,   528,   310,   529,   260,   264,
     387,   346,   261,   325,   536,   540,   389,   542,   390,   543,
     556,   381,   559,   418,   345,   563,   565,   401,   564,   567,
     568,   569,   570,   571,   592,   576,   308,   578,   246,   262,
     419,   580,   581,   323,   587,   368,   263,   593,   594,   595,
     301,   388,   596,   597,   316,   598,   599,   600,   601,   602,
     603,   328,   604,   265,   266,   605,   606,   614,   267,   607,
     620,   621,   347,   608,   609,   268,   269,   610,   270,   617,
     271,   611,   382,   272,   612,   613,   273,   622,   402,   615,
     274,   275,   616,   627,   276,   618,   277,   628,   619,   623,
     625,   420,   278,   624,   279,   626,   629,   280,   630,   631,
     281,   632,   633,   634,   282,   635,   636,   283,   637,   638,
     284,   639,   285,   640,   293,   294,   641,   642,   295,   643,
     644,   645,   646,   309,   647,   648,   649,   650,   651,   652,
     324,   653,   654,   655,   656,   657,   658,   659,   660,   661,
     663,   664,   665,   666,   667,   669,   670,   671,   672,   673,
     674,   675,   676,   677,   678,   680,   161,   681,   683,   237,
     684,   685,   686,   687,   689,   690,   691,   692,   693,   694,
     695,   696,   698,   699,   700,   701,   245,   702,   703,   704,
     706,   707,   708,   711,   712,   715,   717,   720,   721,   723,
     726,   709,   733,   716,   932,   946,   960,   727,   729,   418,
     718,   714,   719,   995,   724,   728,   730,   731,   732,   734,
     741,   934,   952,   964,   743,   982,   419,   744,   742,   745,
     746,   811,   747,   753,    32,   756,   757,   758,   759,   771,
     761,   760,  1039,   762,   763,   768,   772,   246,    92,    93,
     764,   765,    94,   766,   767,   769,   770,   773,    95,    96,
      97,   774,   775,   777,   778,   779,   780,   784,   809,   781,
     810,   783,   785,   862,   866,   870,   786,   787,   874,   878,
     792,   902,   935,   953,   965,   793,   983,   420,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   794,   905,
     795,   796,   797,   909,   798,   799,   800,   801,   128,   129,
     130,   131,   974,   802,   804,   991,   132,  1000,  1004,   337,
     805,  1018,  1019,  1020,  1021,   133,   134,  1022,  1023,  1024,
    1025,  1026,   135,   136,   137,   138,   139,   140,   141,  1027,
    1029,   142,  1030,  1040,  1043,  1042,  1071,  1046,   143,  1045,
    1049,  1048,  1051,  1052,  1055,  1066,  1067,   144,  1069,  1070,
     145,  1072,  1073,  1074,  1075,  1076,  1081,   146,  1082,  1083,
    1086,  1087,  1088,  1094,  1096,   147,   148,  1100,  1101,  1115,
     149,   150,  1102,  1104,  1112,  1120,   812,  1119,  1123,  1122,
    1126,  1130,  1124,  1125,  1127,  1128,  1129,   151,  1131,  1132,
    1133,   152,  1140,  1143,  1144,  1145,  1146,  1204,  1205,  1134,
    1135,  1240,  1241,  1136,  1137,  1138,  1139,   153,   154,   155,
     156,   157,   158,  1250,  1142,  1141,  1233,  1234,  1235,  1236,
    1251,   159,  1237,  1246,  1238,  1252,  1242,  1243,  1254,  1260,
    1244,  1247,  1262,  1279,  1280,   803,  1326,   160,  1302,  1310,
    1303,  1311,  1248,  1253,  1312,  1313,  1331,  1339,  1255,  1340,
     257,  1261,  1356,   367,  1259,  1358,   387,  1357,  1277,  1156,
     258,  1289,   389,   259,   390,   303,  1341,   300,  1368,  1157,
     381,  1210,  1158,   401,   344,  1290,  1198,   405,  1291,  1296,
     298,  1211,  1297,  1298,  1212,  1299,   260,   264,  1219,  1197,
     261,   346,  1306,   932,   368,  1159,  1163,   388,   946,  1160,
    1185,  1218,  1307,  1319,   345,  1324,   960,  1213,   960,  1325,
     934,  1214,  1217,  1328,  1335,   952,  1370,   262,  1267,  1189,
    1360,  1361,   995,   964,   263,   964,  1161,   307,   301,  1369,
     322,   382,   982,  1162,   402,  1269,  1371,  1199,  1215,   326,
    1372,   265,   266,  1373,   315,  1216,   267,   327,  1375,  1220,
    1164,  1165,   347,   268,   269,  1166,   270,   310,   271,  1268,
     325,   272,  1167,  1168,   273,  1169,  1382,  1170,   274,   275,
    1171,   935,   276,  1172,   277,  1378,   953,  1173,  1174,  1386,
     278,  1175,   279,  1176,   965,   280,   965,   308,   281,  1177,
     323,  1178,   282,   983,  1179,   283,  1270,  1180,   284,  1404,
     285,  1181,   293,   294,  1182,   316,   295,  1183,   328,  1184,
    1405,  1191,  1192,  1380,  1381,  1193,  1190,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
    1407,  1408,  1409,  1425,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,  1426,  1427,   127,  1429,  1428,  1435,
    1436,  1437,  1438,  1440,   888,  1010,  1441,   814,   129,   130,
     131,  1149,  1202,  1206,  1147,  1249,   247,  1232,   248,  1203,
    1338,  1150,  1239,   668,   133,   134,   249,   250,   251,   252,
     253,   135,   136,   137,   309,  1231,   713,   324,  1151,   359,
     662,   254,  1201,  1153,  1284,   255,  1281,   143,  1152,  1282,
     705,  1229,  1155,  1154,   710,   256,  1283,  1228,  1230,  1342,
    1245,   679,  1374,  1156,  1424,  1439,  1263,  1258,  1257,  1359,
    1256,  1210,   722,  1157,   725,  1402,  1158,  1008,   688,  1430,
    1198,  1211,     0,   813,  1212,  1347,   990,  1329,  1219,     0,
       0,  1276,  1267,  1197,     0,  1278,     0,     0,     0,  1159,
    1163,  1218,  1348,  1160,  1185,     0,     0,  1213,     0,  1269,
     682,  1214,  1217,     0,     0,     0,   153,   154,     0,     0,
       0,     0,     0,  1189,     0,  1347,     0,     0,     0,     0,
    1161,     0,     0,  1268,     0,     0,     0,  1162,  1215,   697,
       0,  1199,  1348,     0,     0,  1216,   160,     0,     0,  1220,
       0,     0,     0,     0,  1164,  1165,     0,     0,     0,  1166,
       0,     0,  1415,  1349,     0,     0,  1167,  1168,     0,  1169,
    1270,  1170,     0,     0,  1171,     0,     0,  1172,     0,  1418,
       0,  1173,  1174,     0,     0,  1175,     0,  1176,     0,     0,
       0,     0,  1415,  1177,     0,  1178,     0,     0,  1179,     0,
       0,  1180,     0,  1349,     0,  1181,     0,     0,  1182,  1418,
       0,  1183,     0,  1184,     0,  1191,  1192,     0,     0,  1193,
    1190,     0,     0,     0,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,     0,     0,     0,
    1419,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,     0,   127,   361,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   129,   130,   131,     0,     0,
    1419,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   133,   134,     0,   250,   251,     0,   253,   135,   136,
     137,     0,     0,     0,     0,     0,     0,     0,   254,     0,
       0,     0,   255,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   256,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   153,   154,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   160
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,   767,    78,    79,    80,
      81,    16,    73,    75,    79,    73,    79,    73,    72,    73,
      74,    75,    76,   767,    78,    79,   767,    81,   765,   732,
     759,  1050,    73,    74,    75,    76,  1050,  1050,    73,    73,
    1050,  1050,    73,     5,   135,     7,   635,     9,    78,    79,
      16,    17,    18,    19,    20,    28,    29,   141,   142,   196,
     197,   198,   199,    74,    75,  1403,     3,  1403,     3,    73,
       0,     8,   215,     8,   230,     3,    73,    79,     6,    72,
      73,    74,    75,    76,     8,    78,    79,   230,    81,    95,
      96,    97,    98,    73,    73,  1433,   233,  1433,    73,     7,
       3,     7,    24,     6,    24,    73,    73,     7,    73,     3,
      73,     7,    32,    73,     8,     3,    73,     3,     6,     6,
      73,    73,     8,   712,    73,     3,    73,   108,   109,    10,
       8,     7,    73,    24,    73,   108,   109,    73,     7,   230,
      73,     7,   108,   109,    73,     7,   230,    73,     3,     7,
      73,     3,    73,     8,    73,    73,     8,     3,    73,    24,
      74,    75,     8,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,   108,   109,     7,
      45,    46,    47,    48,    49,    50,   108,   109,   108,   109,
      81,     7,    83,    84,    47,    48,    49,    88,    89,    90,
     181,   182,   183,     3,   177,   178,   207,     3,     8,   210,
     211,   212,   213,     7,     3,     3,    81,   108,   109,     8,
       8,    51,    52,    53,    54,    55,    56,     3,     3,   160,
     161,   162,     8,     8,   154,   155,   156,   157,    81,    82,
      83,    84,    85,    86,    87,   676,    13,    14,    80,   230,
      80,    81,   174,   175,   176,   108,   109,   230,   689,   690,
     691,   692,     3,     7,   230,   108,   109,     8,   230,   231,
     232,   233,    25,    26,    27,     3,   108,   109,   108,   109,
       8,     4,     3,     3,     3,  1304,    81,     8,     8,     8,
    1304,  1304,   124,     3,  1304,  1304,   126,   127,   128,   230,
     132,   133,   134,   135,   136,   137,   138,     4,   230,     4,
     230,     4,   165,   108,   109,     3,   169,   170,   171,   172,
       8,   141,   142,     3,   108,   109,   179,  1056,     8,     3,
       3,    80,     3,     6,     8,  1038,  1097,     8,  1099,   230,
       3,     3,     8,    80,     3,     8,     8,  1084,     3,     8,
       4,     6,   101,  1097,     4,  1099,  1097,     3,  1099,   108,
     109,     4,     8,   122,   123,   230,   103,   104,   105,   106,
     107,   108,   109,     3,     3,     3,   125,   230,     8,     8,
     129,   130,   193,   194,     3,     3,     3,   230,   125,     8,
       8,     8,   129,   130,     3,    42,    43,    44,   230,     8,
     230,   185,   186,   187,   188,   189,   190,   191,   192,   135,
     136,   206,   138,   208,   209,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   151,
     152,   153,     4,   438,   439,   230,   144,   145,   146,   147,
     148,   149,     3,   514,     4,     4,   230,     8,     4,     4,
     521,   166,   167,   168,     4,     4,     4,     4,     4,     4,
       4,     4,   533,     4,     4,     4,   537,   521,     4,     4,
       4,     4,   533,   544,     4,   533,     4,   533,     4,   533,
       4,   230,   544,   537,   555,     4,     4,     4,     4,     4,
     544,     4,   533,   230,   565,     4,   537,     4,   533,   533,
     571,   555,   533,   544,     4,     4,   571,     4,   571,     4,
       8,   565,     4,   584,   555,     4,     3,   571,     8,     4,
       4,     4,     8,     3,   230,     4,   537,     4,   521,   533,
     584,     4,     4,   544,     4,   565,   533,     4,     4,     4,
     533,   571,     4,     4,   537,     4,     4,   231,   231,   231,
     231,   544,   231,   533,   533,   231,   231,     4,   533,   231,
       4,     4,   555,   233,   232,   533,   533,   232,   533,   233,
     533,   232,   565,   533,   231,   231,   533,     4,   571,   231,
     533,   533,   231,     4,   533,   233,   533,     4,   233,   233,
     232,   584,   533,   233,   533,   233,     4,   533,   231,     4,
     533,     4,     4,     4,   533,     4,     4,   533,   233,   233,
     533,   233,   533,     4,   533,   533,     4,     4,   533,     4,
       4,     4,     4,   537,     4,     4,   231,     4,     4,     4,
     544,     4,     4,     4,     4,   233,   233,   233,     4,     4,
       4,   233,   233,   231,   231,     4,     4,     4,     4,     4,
     231,   233,     4,     4,     4,     4,   727,   231,     4,   730,
     231,     4,   231,   231,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   231,     4,   730,     4,     4,   233,
       4,   233,   233,     4,     4,     4,     4,     4,     4,     4,
       4,   233,     5,   231,   765,   766,   767,     7,     7,   770,
     231,   233,   231,   774,   231,   230,     7,     7,     7,   230,
     230,   765,   766,   767,     5,   769,   770,     5,   230,     5,
     230,   726,   230,     5,     7,   230,     5,     5,     5,   230,
       5,     7,     6,     5,     5,     5,   230,   730,    11,    12,
       7,     7,    15,     7,     7,     7,     7,     5,    21,    22,
      23,     7,     5,     5,     5,   230,   230,     7,   195,   230,
       5,   230,   230,     7,     7,     7,   230,   230,     7,     7,
     230,     7,   765,   766,   767,   230,   769,   770,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,   230,     7,
     230,   230,   230,     7,   230,   230,   230,   230,    91,    92,
      93,    94,     7,   230,   230,     7,    99,     7,     7,   132,
     230,     4,     4,     4,     4,   108,   109,     4,     4,     4,
       4,     4,   115,   116,   117,   118,   119,   120,   121,     4,
       4,   124,     4,     3,     3,     6,     4,     3,   131,     6,
       3,     6,     6,     3,     6,     6,     3,   140,     6,     3,
     143,     4,     4,     4,     4,     4,     4,   150,     4,     4,
       4,     4,     4,     4,     4,   158,   159,     6,     3,   230,
     163,   164,     4,     4,     4,     3,   727,     6,     3,     6,
       4,   231,     8,     6,     4,     4,     4,   180,   233,   231,
     233,   184,     4,     4,     4,     4,     4,     4,     4,   231,
     231,     4,     4,   231,   231,   231,   231,   200,   201,   202,
     203,   204,   205,     4,   231,   233,   231,   231,   231,   231,
       4,   214,   231,   233,   231,     4,   231,   231,     4,     4,
     231,   231,     4,     6,     3,   712,     7,   230,     8,     4,
       8,     8,   231,   231,     3,     8,     4,     4,   233,     4,
    1041,   231,     4,  1044,   233,     4,  1047,   231,   233,  1050,
    1041,   230,  1047,  1041,  1047,  1041,   233,  1041,     5,  1050,
    1044,  1062,  1050,  1047,  1065,   230,  1050,  1068,   230,   230,
    1041,  1062,   230,   230,  1062,   230,  1041,  1041,  1062,  1050,
    1041,  1065,   230,  1084,  1044,  1050,  1050,  1047,  1089,  1050,
    1050,  1062,   230,   230,  1065,   230,  1097,  1062,  1099,   230,
    1084,  1062,  1062,   230,   230,  1089,     4,  1041,  1109,  1050,
     230,   230,  1113,  1097,  1041,  1099,  1050,  1118,  1041,   230,
    1121,  1044,  1106,  1050,  1047,  1109,     4,  1050,  1062,  1121,
       4,  1041,  1041,     4,  1118,  1062,  1041,  1121,     7,  1062,
    1050,  1050,  1065,  1041,  1041,  1050,  1041,  1118,  1041,  1109,
    1121,  1041,  1050,  1050,  1041,  1050,     5,  1050,  1041,  1041,
    1050,  1084,  1041,  1050,  1041,   173,  1089,  1050,  1050,     7,
    1041,  1050,  1041,  1050,  1097,  1041,  1099,  1118,  1041,  1050,
    1121,  1050,  1041,  1106,  1050,  1041,  1109,  1050,  1041,     6,
    1041,  1050,  1041,  1041,  1050,  1118,  1041,  1050,  1121,  1050,
       3,  1050,  1050,   230,   230,  1050,  1050,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
       4,     4,     4,     4,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,   233,   231,    80,     4,   231,   230,
     230,     4,     4,   230,   758,   810,   230,   730,    92,    93,
      94,  1040,  1053,  1060,  1035,  1089,   100,  1070,   102,  1056,
    1304,  1041,  1077,   521,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,  1118,  1068,   574,  1121,  1043,    77,
     514,   125,  1052,  1046,  1123,   129,  1118,   131,  1044,  1120,
     565,  1065,  1049,  1047,   571,   139,  1121,  1063,  1067,  1312,
    1084,   533,  1366,  1304,  1405,  1433,  1106,  1101,  1099,  1333,
    1097,  1312,   584,  1304,   588,  1384,  1304,   784,   544,  1411,
    1304,  1312,    -1,   729,  1312,  1326,   770,  1262,  1312,    -1,
      -1,  1110,  1333,  1304,    -1,  1113,    -1,    -1,    -1,  1304,
    1304,  1312,  1326,  1304,  1304,    -1,    -1,  1312,    -1,  1333,
     537,  1312,  1312,    -1,    -1,    -1,   200,   201,    -1,    -1,
      -1,    -1,    -1,  1304,    -1,  1366,    -1,    -1,    -1,    -1,
    1304,    -1,    -1,  1333,    -1,    -1,    -1,  1304,  1312,   555,
      -1,  1304,  1366,    -1,    -1,  1312,   230,    -1,    -1,  1312,
      -1,    -1,    -1,    -1,  1304,  1304,    -1,    -1,    -1,  1304,
      -1,    -1,  1403,  1326,    -1,    -1,  1304,  1304,    -1,  1304,
    1333,  1304,    -1,    -1,  1304,    -1,    -1,  1304,    -1,  1403,
      -1,  1304,  1304,    -1,    -1,  1304,    -1,  1304,    -1,    -1,
      -1,    -1,  1433,  1304,    -1,  1304,    -1,    -1,  1304,    -1,
      -1,  1304,    -1,  1366,    -1,  1304,    -1,    -1,  1304,  1433,
      -1,  1304,    -1,  1304,    -1,  1304,  1304,    -1,    -1,  1304,
    1304,    -1,    -1,    -1,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    -1,    -1,    -1,
    1403,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    -1,    80,    81,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    92,    93,    94,    -1,    -1,
    1433,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   108,   109,    -1,   111,   112,    -1,   114,   115,   116,
     117,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,    -1,
      -1,    -1,   129,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   139,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   200,   201,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   230
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
       0,     5,     7,     9,   230,   231,   232,   233,   250,   251,
     252,   257,     7,   266,     7,   271,     7,   326,     7,   441,
       7,   519,     7,   536,     7,   553,     7,   470,     7,   476,
       7,   500,     7,   417,     7,   658,     7,   677,   258,   253,
     267,   272,   327,   442,   520,   537,   554,   471,   477,   501,
     418,   659,   678,   250,   259,   260,   230,   255,   256,    10,
     268,   270,    11,    12,    15,    21,    22,    23,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    91,    92,
      93,    94,    99,   108,   109,   115,   116,   117,   118,   119,
     120,   121,   124,   131,   140,   143,   150,   158,   159,   163,
     164,   180,   184,   200,   201,   202,   203,   204,   205,   214,
     230,   265,   273,   274,   275,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   297,   299,   301,   302,   303,   306,   307,
     309,   311,   312,   313,   314,   316,   317,   319,   321,   322,
     323,   324,   336,   338,   340,   382,   390,   396,   402,   404,
     411,   425,   435,   455,   456,   457,   460,   468,   494,   526,
     528,   547,   577,   591,   603,   604,   606,   646,   656,   675,
     684,   708,    16,    17,    18,    19,    20,   265,   328,   329,
     330,   332,   333,   334,   335,   526,   528,   100,   102,   110,
     111,   112,   113,   114,   125,   129,   139,   265,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   291,   292,   293,   294,   297,   299,   301,   302,   303,
     306,   307,   309,   311,   317,   319,   443,   444,   445,   447,
     449,   451,   453,   455,   456,   457,   458,   459,   494,   513,
     526,   528,   530,   547,   574,   101,   130,   265,   451,   453,
     494,   521,   522,   523,   525,   526,   528,   103,   104,   105,
     106,   107,   265,   451,   453,   494,   525,   526,   528,   538,
     539,   540,   542,   543,   545,   546,   124,   132,   133,   134,
     135,   136,   137,   138,   265,   494,   526,   528,   555,   556,
     557,   558,   560,   562,   564,   566,   568,   570,   572,   468,
      24,    81,    83,    84,    88,    89,    90,   265,   358,   478,
     479,   480,   481,   482,   483,   484,   486,   488,   490,   491,
     493,   526,   528,    82,    85,    86,    87,   265,   358,   482,
     488,   502,   503,   504,   505,   506,   508,   509,   510,   511,
     512,   526,   528,   141,   142,   265,   419,   420,   421,   423,
     185,   186,   187,   188,   189,   190,   191,   192,   265,   526,
     528,   660,   661,   662,   663,   665,   666,   668,   669,   670,
     673,    13,    14,   679,   680,   681,   683,     6,     3,     4,
       8,     3,   269,     3,     8,   276,   676,   325,   337,   339,
     341,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   315,     4,     4,     4,     4,
       4,   295,   298,   300,     4,     4,     4,     4,   436,   469,
     495,     4,   318,   320,   304,   461,   527,   529,     4,     4,
       4,   391,   403,   397,   383,   578,   548,   412,   426,   592,
       4,   405,   605,   607,   647,   657,   308,   310,     4,     4,
       4,   685,   709,     4,     3,     8,   331,     4,     4,     4,
       4,     3,     8,   514,   531,   446,   448,   450,     4,     4,
     454,   452,   575,     3,     8,   524,     4,     3,     8,   541,
       4,   544,     4,     4,     3,     8,   573,   559,   561,   563,
     565,   567,   569,   571,     8,     3,     8,   485,   359,     4,
     489,   487,   492,     4,     8,     3,   507,     4,     4,     4,
       8,     3,   422,   424,     3,     8,     4,   664,     4,   667,
       4,     4,   671,   674,     3,     8,   682,     4,     3,     8,
     250,   250,   230,     4,     4,     4,     4,     4,     4,     4,
     231,   231,   231,   231,   231,   231,   231,   231,   233,   232,
     232,   232,   231,   231,     4,   231,   231,   233,   233,   233,
       4,     4,     4,   233,   233,   232,   233,     4,     4,     4,
     231,     4,     4,     4,     4,     4,     4,   233,   233,   233,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   231,
       4,     4,     4,     4,     4,     4,     4,   233,   233,   233,
       4,     4,   274,     4,   233,   233,   231,   231,   329,     4,
       4,     4,     4,     4,   231,   233,     4,     4,     4,   444,
       4,   231,   522,     4,   231,     4,   231,   231,   539,     4,
       4,     4,     4,     4,     4,     4,     4,   557,     4,     4,
     231,     4,     4,     4,   233,   480,     4,   233,   233,   233,
     504,     4,     4,   420,   233,     4,   231,     4,   231,   231,
       4,     4,   661,     4,   231,   680,     4,     7,   230,     7,
       7,     7,     7,     5,   230,   196,   197,   198,   199,   233,
     296,   230,   230,     5,     5,     5,   230,   230,    95,    96,
      97,    98,   305,     5,   252,   254,   230,     5,     5,     5,
       7,     5,     5,     5,     7,     7,     7,     7,     5,     7,
       7,   230,   230,     5,     7,     5,   261,     5,     5,   230,
     230,   230,   261,   230,     7,   230,   230,   230,   261,   261,
     261,   261,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   254,   230,   230,   193,   194,   672,   195,
       5,   250,   273,   679,   328,    24,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      45,    46,    47,    48,    49,    50,   265,   346,   347,   348,
     351,   353,   355,   357,   358,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   371,   372,   373,   374,   376,   378,
     380,   346,     7,   342,   343,   344,     7,   437,   438,   439,
       7,   472,   473,   474,     7,   496,   497,   498,     7,   462,
     463,   464,   135,   230,   392,   393,   394,   395,   259,   136,
     138,   394,   398,   399,   400,   401,   122,   123,   384,   385,
     386,   388,     7,   579,   580,     7,   549,   550,   551,     7,
     413,   414,   415,   144,   145,   146,   147,   148,   149,   427,
     428,   429,   430,   431,   432,   433,   434,    24,   154,   155,
     156,   157,   265,   360,   526,   528,   593,   594,   595,   598,
     599,   601,   602,   160,   161,   162,   265,   406,   407,   408,
     409,   410,   526,   528,   165,   169,   170,   171,   172,   179,
     265,   374,   376,   378,   526,   528,   612,   613,   614,   617,
     619,   621,   622,   623,     7,   608,   609,   610,   181,   182,
     183,   230,   526,   528,   648,   649,   650,   651,   653,   654,
     660,     7,   686,   687,   215,   265,   710,   711,   712,   262,
       7,   515,   516,   517,     7,   532,   533,   534,   558,   576,
     342,     8,     8,     8,   349,   352,   354,   356,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   369,     4,
       4,   375,   377,   379,   381,     3,     8,     8,   345,     6,
       3,   440,     6,     3,   475,     6,     3,   499,     6,     3,
     465,     6,     3,     3,     6,     6,     3,     6,   387,   389,
       3,     8,   581,     3,     6,   552,     6,     3,   416,     6,
       3,     4,     4,     4,     4,     4,     4,     3,     8,   596,
     600,     4,     4,     4,     3,     8,     4,     4,     4,     3,
       8,   615,   618,   620,     4,   624,     4,     3,     8,   611,
       6,     3,     4,   652,     4,   655,     3,     8,     8,   688,
       3,     6,     4,     3,     8,   230,   263,   264,   518,     6,
       3,   535,     6,     3,     8,     6,     4,     4,     4,     4,
     231,   233,   231,   233,   231,   231,   231,   231,   231,   231,
       4,   233,   231,     4,     4,     4,     4,   347,   346,   344,
     443,   439,   478,   474,   502,   498,   265,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     291,   292,   293,   294,   297,   299,   301,   302,   303,   306,
     307,   309,   311,   317,   319,   358,   435,   447,   449,   451,
     453,   455,   456,   457,   459,   466,   467,   494,   526,   528,
     574,   464,   393,   399,     4,     4,   385,   126,   127,   128,
     265,   277,   278,   279,   280,   281,   282,   358,   494,   526,
     528,   582,   583,   584,   585,   586,   588,   590,   580,   555,
     551,   419,   415,   231,   231,   231,   231,   231,   231,   428,
       4,     4,   231,   231,   231,   594,   233,   231,   231,   407,
       4,     4,     4,   231,     4,   233,   613,   612,   610,   233,
       4,   231,     4,   649,   206,   208,   209,   265,   358,   526,
     528,   689,   690,   691,   692,   694,   687,   233,   711,     6,
       3,   521,   517,   538,   534,    25,    26,    27,   350,   230,
     230,   230,    42,    43,    44,   370,   230,   230,   230,   230,
       8,     8,     8,     8,     3,     8,   230,   230,   587,   589,
       4,     8,     3,     8,     8,   151,   152,   153,   597,   230,
     166,   167,   168,   616,   230,   230,     7,     8,   230,   250,
     695,     4,   693,     3,     8,   230,     8,     8,   467,     4,
       4,   233,   584,    24,   174,   175,   176,   265,   526,   528,
     625,   626,   627,   630,   632,   634,     4,   231,     4,   690,
     230,   230,   628,   631,   633,   635,     3,     8,     5,   230,
       4,     4,     4,     4,   626,     7,   696,   697,   173,   629,
     230,   230,     5,   698,     3,     6,     7,   636,   637,   638,
     207,   210,   211,   212,   213,   699,   700,   701,   703,   704,
     705,   706,   697,   639,     6,     3,   702,     4,     4,     4,
     707,     3,     8,   177,   178,   265,   351,   353,   526,   528,
     640,   641,   642,   644,   638,     4,   233,   231,   231,     4,
     700,   643,   645,     3,     8,   230,   230,     4,     4,   641,
     230,   230
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   234,   236,   235,   237,   235,   238,   235,   239,   235,
     240,   235,   241,   235,   242,   235,   243,   235,   244,   235,
     245,   235,   246,   235,   247,   235,   248,   235,   249,   235,
     250,   250,   250,   250,   250,   250,   250,   251,   253,   252,
     254,   255,   255,   256,   256,   256,   258,   257,   259,   259,
     260,   260,   260,   262,   261,   263,   263,   264,   264,   264,
     265,   267,   266,   269,   268,   268,   270,   272,   271,   273,
     273,   273,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   276,   275,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     295,   294,   296,   296,   296,   296,   296,   298,   297,   300,
     299,   301,   302,   304,   303,   305,   305,   305,   305,   306,
     308,   307,   310,   309,   311,   312,   313,   315,   314,   316,
     318,   317,   320,   319,   321,   322,   323,   325,   324,   327,
     326,   328,   328,   328,   329,   329,   329,   329,   329,   329,
     329,   329,   331,   330,   332,   333,   334,   335,   337,   336,
     339,   338,   341,   340,   342,   342,   343,   343,   343,   345,
     344,   346,   346,   346,   347,   347,   347,   347,   347,   347,
     347,   347,   347,   347,   347,   347,   347,   347,   347,   347,
     347,   347,   347,   347,   347,   347,   347,   349,   348,   350,
     350,   350,   352,   351,   354,   353,   356,   355,   357,   359,
     358,   360,   361,   362,   363,   364,   365,   366,   367,   369,
     368,   370,   370,   370,   371,   372,   373,   375,   374,   377,
     376,   379,   378,   381,   380,   383,   382,   384,   384,   384,
     385,   385,   387,   386,   389,   388,   391,   390,   392,   392,
     392,   393,   393,   394,   395,   397,   396,   398,   398,   398,
     399,   399,   399,   400,   401,   403,   402,   405,   404,   406,
     406,   406,   407,   407,   407,   407,   407,   407,   408,   409,
     410,   412,   411,   413,   413,   414,   414,   414,   416,   415,
     418,   417,   419,   419,   419,   419,   420,   420,   422,   421,
     424,   423,   426,   425,   427,   427,   427,   428,   428,   428,
     428,   428,   428,   429,   430,   431,   432,   433,   434,   436,
     435,   437,   437,   438,   438,   438,   440,   439,   442,   441,
     443,   443,   443,   444,   444,   444,   444,   444,   444,   444,
     444,   444,   444,   444,   444,   444,   444,   444,   444,   444,
     444,   444,   444,   444,   444,   444,   444,   444,   444,   444,
     444,   444,   444,   444,   444,   444,   444,   444,   444,   444,
     444,   444,   444,   444,   444,   444,   444,   444,   444,   446,
     445,   448,   447,   450,   449,   452,   451,   454,   453,   455,
     456,   457,   458,   459,   461,   460,   462,   462,   463,   463,
     463,   465,   464,   466,   466,   466,   467,   467,   467,   467,
     467,   467,   467,   467,   467,   467,   467,   467,   467,   467,
     467,   467,   467,   467,   467,   467,   467,   467,   467,   467,
     467,   467,   467,   467,   467,   467,   467,   467,   467,   467,
     467,   467,   467,   467,   467,   467,   467,   467,   467,   469,
     468,   471,   470,   472,   472,   473,   473,   473,   475,   474,
     477,   476,   478,   478,   479,   479,   479,   480,   480,   480,
     480,   480,   480,   480,   480,   480,   480,   481,   482,   483,
     485,   484,   487,   486,   489,   488,   490,   492,   491,   493,
     495,   494,   496,   496,   497,   497,   497,   499,   498,   501,
     500,   502,   502,   503,   503,   503,   504,   504,   504,   504,
     504,   504,   504,   504,   504,   504,   505,   507,   506,   508,
     509,   510,   511,   512,   514,   513,   515,   515,   516,   516,
     516,   518,   517,   520,   519,   521,   521,   521,   522,   522,
     522,   522,   522,   522,   522,   522,   524,   523,   525,   527,
     526,   529,   528,   531,   530,   532,   532,   533,   533,   533,
     535,   534,   537,   536,   538,   538,   538,   539,   539,   539,
     539,   539,   539,   539,   539,   539,   539,   539,   539,   541,
     540,   542,   544,   543,   545,   546,   548,   547,   549,   549,
     550,   550,   550,   552,   551,   554,   553,   555,   555,   556,
     556,   556,   557,   557,   557,   557,   557,   557,   557,   557,
     557,   557,   557,   557,   559,   558,   561,   560,   563,   562,
     565,   564,   567,   566,   569,   568,   571,   570,   573,   572,
     575,   574,   576,   578,   577,   579,   579,   579,   581,   580,
     582,   582,   583,   583,   583,   584,   584,   584,   584,   584,
     584,   584,   584,   584,   584,   584,   584,   584,   584,   585,
     587,   586,   589,   588,   590,   592,   591,   593,   593,   593,
     594,   594,   594,   594,   594,   594,   594,   594,   594,   596,
     595,   597,   597,   597,   598,   600,   599,   601,   602,   603,
     605,   604,   607,   606,   608,   608,   609,   609,   609,   611,
     610,   612,   612,   612,   613,   613,   613,   613,   613,   613,
     613,   613,   613,   613,   613,   613,   615,   614,   616,   616,
     616,   618,   617,   620,   619,   621,   622,   624,   623,   625,
     625,   625,   626,   626,   626,   626,   626,   626,   626,   628,
     627,   629,   631,   630,   633,   632,   635,   634,   636,   636,
     637,   637,   637,   639,   638,   640,   640,   640,   641,   641,
     641,   641,   641,   641,   641,   643,   642,   645,   644,   647,
     646,   648,   648,   648,   649,   649,   649,   649,   649,   649,
     650,   652,   651,   653,   655,   654,   657,   656,   659,   658,
     660,   660,   660,   661,   661,   661,   661,   661,   661,   661,
     661,   661,   661,   661,   662,   664,   663,   665,   667,   666,
     668,   669,   671,   670,   672,   672,   674,   673,   676,   675,
     678,   677,   679,   679,   679,   680,   680,   682,   681,   683,
     685,   684,   686,   686,   686,   688,   687,   689,   689,   689,
     690,   690,   690,   690,   690,   690,   690,   691,   693,   692,
     695,   694,   696,   696,   696,   698,   697,   699,   699,   699,
     700,   700,   700,   700,   700,   702,   701,   703,   704,   705,
     707,   706,   709,   708,   710,   710,   710,   711,   711,   712
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
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     1,     0,     6,     1,     3,     2,     0,     4,
       0,     1,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     3,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     3,     0,     4,     3,     3,     3,
       0,     6,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     0,     4,     0,     4,     3,     3,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     0,     4,     0,     4,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
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
  "\"excluded-prefixes\"", "\"duid\"", "\"hw-address\"", "\"hostname\"",
  "\"flex-id\"", "\"relay\"", "\"hooks-libraries\"", "\"library\"",
  "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"", "\"server-id\"",
  "\"LLT\"", "\"EN\"", "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"",
  "\"enterprise-id\"", "\"dhcp4o6-port\"", "\"multi-threading\"",
  "\"enable-multi-threading\"", "\"thread-pool-size\"",
  "\"packet-queue-size\"", "\"control-socket\"", "\"control-sockets\"",
  "\"socket-type\"", "\"unix\"", "\"http\"", "\"https\"",
  "\"socket-name\"", "\"socket-address\"", "\"socket-port\"",
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
  "reservation_param", "ip_addresses", "$@97", "prefixes", "$@98",
  "excluded_prefixes", "$@99", "duid", "$@100", "hw_address", "$@101",
  "hostname", "$@102", "flex_id_value", "$@103",
  "reservation_client_classes", "$@104", "relay", "$@105", "relay_map",
  "client_classes", "$@106", "client_classes_list", "client_class_entry",
  "$@107", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@108",
  "client_class_template_test", "$@109", "only_if_required", "server_id",
  "$@110", "server_id_params", "server_id_param", "server_id_type",
  "$@111", "duid_type", "htype", "identifier", "$@112", "time",
  "enterprise_id", "dhcp4o6_port", "control_socket", "$@113",
  "control_sockets", "$@114", "control_socket_list",
  "not_empty_control_socket_list", "control_socket_entry", "$@115",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@116", "control_socket_type_value", "control_socket_name", "$@117",
  "control_socket_address", "$@118", "control_socket_port",
  "cert_required", "authentication", "$@119", "auth_params", "auth_param",
  "auth_type", "$@120", "auth_type_value", "realm", "$@121", "directory",
  "$@122", "clients", "$@123", "clients_list", "not_empty_clients_list",
  "basic_auth", "$@124", "clients_params", "clients_param", "user_file",
  "$@125", "password_file", "$@126", "dhcp_queue_control", "$@127",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@128", "capacity", "arbitrary_map_entry", "$@129",
  "dhcp_ddns", "$@130", "sub_dhcp_ddns", "$@131", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@132", "server_port",
  "sender_ip", "$@133", "sender_port", "max_queue_size", "ncr_protocol",
  "$@134", "ncr_protocol_value", "ncr_format", "$@135", "config_control",
  "$@136", "sub_config_control", "$@137", "config_control_params",
  "config_control_param", "config_databases", "$@138",
  "config_fetch_wait_time", "loggers", "$@139", "loggers_entries",
  "logger_entry", "$@140", "logger_params", "logger_param", "debuglevel",
  "severity", "$@141", "output_options_list", "$@142",
  "output_options_list_content", "output_entry", "$@143",
  "output_params_list", "output_params", "output", "$@144", "flush",
  "maxsize", "maxver", "pattern", "$@145", "compatibility", "$@146",
  "compatibility_params", "compatibility_param", "lenient_option_parsing", YY_NULLPTR
  };
#endif


#if PARSER6_DEBUG
  const short
  Dhcp6Parser::yyrline_[] =
  {
       0,   329,   329,   329,   330,   330,   331,   331,   332,   332,
     333,   333,   334,   334,   335,   335,   336,   336,   337,   337,
     338,   338,   339,   339,   340,   340,   341,   341,   342,   342,
     350,   351,   352,   353,   354,   355,   356,   359,   364,   364,
     375,   378,   379,   382,   387,   393,   398,   398,   405,   406,
     409,   413,   417,   423,   423,   430,   431,   434,   438,   442,
     452,   461,   461,   476,   476,   490,   493,   499,   499,   508,
     509,   510,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     555,   556,   557,   558,   559,   560,   561,   562,   563,   564,
     565,   566,   567,   568,   569,   570,   571,   572,   573,   574,
     575,   576,   577,   578,   579,   580,   581,   582,   583,   584,
     585,   588,   588,   597,   603,   609,   615,   621,   627,   633,
     639,   645,   651,   657,   663,   669,   675,   681,   687,   693,
     699,   699,   708,   711,   714,   717,   720,   726,   726,   735,
     735,   744,   753,   763,   763,   772,   775,   778,   781,   786,
     792,   792,   801,   801,   810,   816,   822,   828,   828,   837,
     843,   843,   852,   852,   861,   867,   873,   879,   879,   891,
     891,   900,   901,   902,   907,   908,   909,   910,   911,   912,
     913,   914,   917,   917,   928,   934,   940,   946,   952,   952,
     965,   965,   978,   978,   989,   990,   993,   994,   995,  1000,
    1000,  1010,  1011,  1012,  1017,  1018,  1019,  1020,  1021,  1022,
    1023,  1024,  1025,  1026,  1027,  1028,  1029,  1030,  1031,  1032,
    1033,  1034,  1035,  1036,  1037,  1038,  1039,  1042,  1042,  1050,
    1051,  1052,  1055,  1055,  1064,  1064,  1073,  1073,  1082,  1088,
    1088,  1097,  1103,  1109,  1115,  1121,  1127,  1133,  1140,  1146,
    1146,  1154,  1155,  1156,  1159,  1165,  1171,  1177,  1177,  1186,
    1186,  1195,  1195,  1204,  1204,  1213,  1213,  1224,  1225,  1226,
    1231,  1232,  1235,  1235,  1254,  1254,  1272,  1272,  1283,  1284,
    1285,  1290,  1291,  1294,  1299,  1304,  1304,  1315,  1316,  1317,
    1322,  1323,  1324,  1327,  1332,  1339,  1339,  1352,  1352,  1365,
    1366,  1367,  1372,  1373,  1374,  1375,  1376,  1377,  1380,  1386,
    1392,  1398,  1398,  1409,  1410,  1413,  1414,  1415,  1420,  1420,
    1430,  1430,  1440,  1441,  1442,  1445,  1448,  1449,  1452,  1452,
    1461,  1461,  1470,  1470,  1482,  1483,  1484,  1489,  1490,  1491,
    1492,  1493,  1494,  1497,  1503,  1509,  1515,  1521,  1527,  1536,
    1536,  1550,  1551,  1554,  1555,  1556,  1565,  1565,  1591,  1591,
    1602,  1603,  1604,  1610,  1611,  1612,  1613,  1614,  1615,  1616,
    1617,  1618,  1619,  1620,  1621,  1622,  1623,  1624,  1625,  1626,
    1627,  1628,  1629,  1630,  1631,  1632,  1633,  1634,  1635,  1636,
    1637,  1638,  1639,  1640,  1641,  1642,  1643,  1644,  1645,  1646,
    1647,  1648,  1649,  1650,  1651,  1652,  1653,  1654,  1655,  1658,
    1658,  1667,  1667,  1676,  1676,  1685,  1685,  1694,  1694,  1705,
    1711,  1717,  1723,  1729,  1737,  1737,  1749,  1750,  1754,  1755,
    1756,  1761,  1761,  1769,  1770,  1771,  1776,  1777,  1778,  1779,
    1780,  1781,  1782,  1783,  1784,  1785,  1786,  1787,  1788,  1789,
    1790,  1791,  1792,  1793,  1794,  1795,  1796,  1797,  1798,  1799,
    1800,  1801,  1802,  1803,  1804,  1805,  1806,  1807,  1808,  1809,
    1810,  1811,  1812,  1813,  1814,  1815,  1816,  1817,  1818,  1825,
    1825,  1839,  1839,  1848,  1849,  1852,  1853,  1854,  1861,  1861,
    1876,  1876,  1890,  1891,  1894,  1895,  1896,  1901,  1902,  1903,
    1904,  1905,  1906,  1907,  1908,  1909,  1910,  1913,  1915,  1921,
    1923,  1923,  1932,  1932,  1941,  1941,  1950,  1952,  1952,  1961,
    1971,  1971,  1984,  1985,  1990,  1991,  1992,  1999,  1999,  2011,
    2011,  2023,  2024,  2029,  2030,  2031,  2038,  2039,  2040,  2041,
    2042,  2043,  2044,  2045,  2046,  2047,  2050,  2052,  2052,  2061,
    2063,  2065,  2071,  2077,  2086,  2086,  2099,  2100,  2103,  2104,
    2105,  2110,  2110,  2120,  2120,  2130,  2131,  2132,  2137,  2138,
    2139,  2140,  2141,  2142,  2143,  2144,  2147,  2147,  2156,  2162,
    2162,  2187,  2187,  2217,  2217,  2230,  2231,  2234,  2235,  2236,
    2241,  2241,  2253,  2253,  2265,  2266,  2267,  2272,  2273,  2274,
    2275,  2276,  2277,  2278,  2279,  2280,  2281,  2282,  2283,  2286,
    2286,  2295,  2301,  2301,  2310,  2316,  2325,  2325,  2336,  2337,
    2340,  2341,  2342,  2347,  2347,  2356,  2356,  2365,  2366,  2369,
    2370,  2371,  2377,  2378,  2379,  2380,  2381,  2382,  2383,  2384,
    2385,  2386,  2387,  2388,  2391,  2391,  2402,  2402,  2413,  2413,
    2424,  2424,  2433,  2433,  2442,  2442,  2451,  2451,  2460,  2460,
    2474,  2474,  2485,  2491,  2491,  2502,  2503,  2504,  2509,  2509,
    2519,  2520,  2523,  2524,  2525,  2530,  2531,  2532,  2533,  2534,
    2535,  2536,  2537,  2538,  2539,  2540,  2541,  2542,  2543,  2546,
    2548,  2548,  2557,  2557,  2566,  2575,  2575,  2588,  2589,  2590,
    2595,  2596,  2597,  2598,  2599,  2600,  2601,  2602,  2603,  2606,
    2606,  2614,  2615,  2616,  2619,  2625,  2625,  2634,  2640,  2648,
    2656,  2656,  2668,  2668,  2680,  2681,  2684,  2685,  2686,  2691,
    2691,  2699,  2700,  2701,  2706,  2707,  2708,  2709,  2710,  2711,
    2712,  2713,  2714,  2715,  2716,  2717,  2720,  2720,  2729,  2730,
    2731,  2734,  2734,  2744,  2744,  2754,  2760,  2768,  2768,  2781,
    2782,  2783,  2788,  2789,  2790,  2791,  2792,  2793,  2794,  2797,
    2797,  2805,  2808,  2808,  2817,  2817,  2826,  2826,  2837,  2838,
    2841,  2842,  2843,  2848,  2848,  2856,  2857,  2858,  2863,  2864,
    2865,  2866,  2867,  2868,  2869,  2872,  2872,  2881,  2881,  2892,
    2892,  2905,  2906,  2907,  2912,  2913,  2914,  2915,  2916,  2917,
    2920,  2926,  2926,  2935,  2941,  2941,  2951,  2951,  2964,  2964,
    2974,  2975,  2976,  2981,  2982,  2983,  2984,  2985,  2986,  2987,
    2988,  2989,  2990,  2991,  2994,  3000,  3000,  3009,  3015,  3015,
    3024,  3030,  3036,  3036,  3045,  3046,  3049,  3049,  3060,  3060,
    3072,  3072,  3082,  3083,  3084,  3090,  3091,  3094,  3094,  3105,
    3113,  3113,  3126,  3127,  3128,  3134,  3134,  3142,  3143,  3144,
    3149,  3150,  3151,  3152,  3153,  3154,  3155,  3158,  3164,  3164,
    3173,  3173,  3184,  3185,  3186,  3191,  3191,  3199,  3200,  3201,
    3206,  3207,  3208,  3209,  3210,  3213,  3213,  3222,  3228,  3234,
    3240,  3240,  3249,  3249,  3260,  3261,  3262,  3267,  3268,  3271
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
#line 6856 "dhcp6_parser.cc"

#line 3277 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
